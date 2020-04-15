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
*   for the PMA Registers block.
 */        

/*! \addtogroup registerMap
  @{
*/

/*! \defgroup PMA_registers PMA Registers
*   This module contains the data structures and doxygen comments
*   for the PMA Registers block.
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
*   This file contains the c header structures for the registers contained in the PMA Registers block.
*
*   The bit fields in this structure are from MSbit to LSbit
*
***********************************************************************/


/*@{*/
#ifndef AQ_EUR_PMA_REGS_HEADER
#define AQ_EUR_PMA_REGS_HEADER


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Standard Control 1: 01.0000 */
/*                  PMA Standard Control 1: 01.0000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Standard Control 1 */
  union
  {
    struct
    {
                    /*! \brief 01.0000.F R/WSC Reset
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.reset

                        Default = 0x1

                        1 = PMA reset
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        The reset bit is automatically cleared upon completion of the reset sequence by the microcontroller. This bit is set to 1 during reset. The reset is internally stretched by approximately 1.7 us. Therefore the MDIO or uP should allow for 1.7 us before writing any PMA registers after this bit is set.
                        
                          */
      unsigned int   reset : 1;    /* 01.0000.F  R/WSC      Default = 0x1 */
                     /* 1 = PMA reset
                        0 = Normal operation
                          */
                    /*! \brief 01.0000.E R/WPD Reserved_0a
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.reserved0a

                        Provisionable Default = 0x0

                        Reserved bit 14
  */
      unsigned int   reserved0a : 1;    /* 01.0000.E  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 14  */
                    /*! \brief 01.0000.D R/WPD Speed Selection LSB
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.speedSelectionLsb

                        Provisionable Default = 0x1

                        {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s
  */
      unsigned int   speedSelectionLsb : 1;    /* 01.0000.D  R/WPD      Provisionable Default = 0x1 */
                     /* {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s  */
                    /*! \brief 01.0000.C R/WPD Reserved_0b
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.reserved0b

                        Provisionable Default = 0x0

                        Reserved bit 12
  */
      unsigned int   reserved0b : 1;    /* 01.0000.C  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 12  */
                    /*! \brief 01.0000.B R/WPD Low Power
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.lowPower

                        Provisionable Default = 0x0

                        1 = Low-power mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        A one written to this register causes the PMA to enter low-power mode. If a global chip low-power state is desired, use Bit B in "Global Standard Control 1: Address 1E.0" 
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   lowPower : 1;    /* 01.0000.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Low-power mode
                        0 = Normal operation
                          */
                    /*! \brief 01.0000.A:7 R/WPD Reserved_0c [A:7]
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.reserved0c

                        Provisionable Default = 0x0

                        Reserved bits 10 to 7
  */
      unsigned int   reserved0c : 4;    /* 01.0000.A:7  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bits 10 to 7  */
                    /*! \brief 01.0000.6 R/WPD Speed Selection MSB
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.speedSelectionMsb

                        Provisionable Default = 0x1

                        {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s
  */
      unsigned int   speedSelectionMsb : 1;    /* 01.0000.6  R/WPD      Provisionable Default = 0x1 */
                     /* {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s  */
                    /*! \brief 01.0000.5:2 R/WPD 10G Speed Selection [3:0]
                        AQ_PmaStandardControl_1_EUR.u0.bits_0._10gSpeedSelection

                        Provisionable Default = 0x0

                        1 x x x = Reserved
                        0 1 1 1 = 5Gb/s
                        0 1 1 0 =2.5Gb/s
                        0 1 0 1 = 400Gb/s
                        0 1 0 0 = 25Gb/s
                        0 0 1 1 = 100Gb/s
                        0 0 1 0 = 40Gb/s
                        0 0 0 1 = 10PASS-TS / 2BASE-TL
                        0 0 0 0 = 10 Gb/s
  */
      unsigned int   _10gSpeedSelection : 4;    /* 01.0000.5:2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 x x x = Reserved
                        0 1 1 1 = 5Gb/s
                        0 1 1 0 =2.5Gb/s
                        0 1 0 1 = 400Gb/s
                        0 1 0 0 = 25Gb/s
                        0 0 1 1 = 100Gb/s
                        0 0 1 0 = 40Gb/s
                        0 0 0 1 = 10PASS-TS / 2BASE-TL
                        0 0 0 0 = 10 Gb/s  */
                    /*! \brief 01.0000.1 R/WPD Reserved_0d
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.reserved0d

                        Provisionable Default = 0x0

                        Reserved bit 1
  */
      unsigned int   reserved0d : 1;    /* 01.0000.1  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 1  */
                    /*! \brief 01.0000.0 R/WPD Loopback
                        AQ_PmaStandardControl_1_EUR.u0.bits_0.loopback

                        Provisionable Default = 0x0

                        1 = Enable loopback mode
                        0 = Normal operation

                 <B>Notes:</B>
                        This enables the PMA Analog System Loopback.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   loopback : 1;    /* 01.0000.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable loopback mode
                        0 = Normal operation  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaStandardControl_1_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Standard Status 1: 01.0001 */
/*                  PMA Standard Status 1: 01.0001 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Standard Status 1 */
  union
  {
    struct
    {
                    /*! \brief 01.0001.F:8 R/WPD Reserved_1a [F:8]
                        AQ_PmaStandardStatus_1_EUR.u0.bits_0.reserved1a

                        Provisionable Default = 0x00

                        Reserved bits 15 to 8
  */
      unsigned int   reserved1a : 8;    /* 01.0001.F:8  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved bits 15 to 8  */
                    /*! \brief 01.0001.7 RO Fault
                        AQ_PmaStandardStatus_1_EUR.u0.bits_0.fault

                        

                        1 = Fault condition detected
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        This is the top-level fault indicator flag for the PMA. This bit is set if either of the two bits 1.8.B or 1.8.A are set.  */
      unsigned int   fault : 1;    /* 01.0001.7  RO       */
                     /* 1 = Fault condition detected
                        0 = No fault detected
                          */
                    /*! \brief 01.0001.6:3 R/WPD Reserved_1b [6:3]
                        AQ_PmaStandardStatus_1_EUR.u0.bits_0.reserved1b

                        Provisionable Default = 0x0

                        Reserved bits 6 to 3
  */
      unsigned int   reserved1b : 4;    /* 01.0001.6:3  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bits 6 to 3  */
                    /*! \brief 01.0001.2 LL PMA Receive Link Status
                        AQ_PmaStandardStatus_1_EUR.u0.bits_0.pmaReceiveLinkStatus

                        

                        Status of the PMA receive link
                        1 = Link up
                        0 = Link lost since last read
                        

                 <B>Notes:</B>
                        This indicates the status of the PMA receive link. This is the latch version of 1.E800.0. Note that this is latching low, so it can only be used to detect link drops, and not the current status of the link without performing back-to-back reads.  */
      unsigned int   pmaReceiveLinkStatus : 1;    /* 01.0001.2  LL       */
                     /* Status of the PMA receive link
                        1 = Link up
                        0 = Link lost since last read
                          */
                    /*! \brief 01.0001.1 ROS Low Power Ability
                        AQ_PmaStandardStatus_1_EUR.u0.bits_0.lowPowerAbility

                        Default = 0x1

                        1 = PMA supports low-power mode
                        0 = no low-power mode supported

                 <B>Notes:</B>
                        Indicates whether the PHY supports a low-power mode  */
      unsigned int   lowPowerAbility : 1;    /* 01.0001.1  ROS      Default = 0x1 */
                     /* 1 = PMA supports low-power mode
                        0 = no low-power mode supported  */
                    /*! \brief 01.0001.0 R/WPD Reserved_1c
                        AQ_PmaStandardStatus_1_EUR.u0.bits_0.reserved1c

                        Provisionable Default = 0x0

                        Reserved bit 0
  */
      unsigned int   reserved1c : 1;    /* 01.0001.0  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 0  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaStandardStatus_1_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Standard Device Identifier: 01.0002 */
/*                  PMA Standard Device Identifier: 01.0002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 01.0002.F:0 RO Device ID MSW [1F:10]
                        AQ_PmaStandardDeviceIdentifier_EUR.u0.bits_0.deviceIdMSW

                        

                        Bits 31 - 16 of Device ID
  */
      unsigned int   deviceIdMSW : 16;    /* 01.0002.F:0  RO       */
                     /* Bits 31 - 16 of Device ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 01.0003.F:0 RO Device ID LSW [F:0]
                        AQ_PmaStandardDeviceIdentifier_EUR.u1.bits_1.deviceIdLSW

                        

                        Bits 15 - 0 of Device ID
  */
      unsigned int   deviceIdLSW : 16;    /* 01.0003.F:0  RO       */
                     /* Bits 15 - 0 of Device ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PmaStandardDeviceIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Standard Speed Ability: 01.0004 */
/*                  PMA Standard Speed Ability: 01.0004 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Standard Speed Ability */
  union
  {
    struct
    {
                    /*! \brief 01.0004.F ROS Reserved_4a
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.reserved4a

                        Default = 0x0

                        Reserved bit 15
  */
      unsigned int   reserved4a : 1;    /* 01.0004.F  ROS      Default = 0x0 */
                     /* Reserved bit 15  */
                    /*! \brief 01.0004.E ROS PMA 5G Capable
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.pma_5gCapable

                        Default = 0x1

                        1 = PMA is 5 Gb/s capable
                        0 = PMA is not 5 Gb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.
                          */
      unsigned int   pma_5gCapable : 1;    /* 01.0004.E  ROS      Default = 0x1 */
                     /* 1 = PMA is 5 Gb/s capable
                        0 = PMA is not 5 Gb/s capable  */
                    /*! \brief 01.0004.D ROS PMA 2.5G Capable
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.pma_2_5gCapable

                        Default = 0x1

                        1 = PMA is 2.5 Gb/s capable
                        0 = PMA is not 2.5 Gb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.
                          */
      unsigned int   pma_2_5gCapable : 1;    /* 01.0004.D  ROS      Default = 0x1 */
                     /* 1 = PMA is 2.5 Gb/s capable
                        0 = PMA is not 2.5 Gb/s capable  */
                    /*! \brief 01.0004.C:7 ROS Reserved_4b [C:7]
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.reserved4b

                        Default = 0x00

                        Reserved bits 12 to 7
  */
      unsigned int   reserved4b : 6;    /* 01.0004.C:7  ROS      Default = 0x00 */
                     /* Reserved bits 12 to 7  */
                    /*! \brief 01.0004.6 ROS PMA 10M Capable
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.pma10M_Capable

                        Default = 0x0

                        1 = PMA is 10 Mb/s capable
                        0 = PMA is not 10 Mb/s capable

                 <B>Notes:</B>
                        This is always set to 0 in the PHY.  */
      unsigned int   pma10M_Capable : 1;    /* 01.0004.6  ROS      Default = 0x0 */
                     /* 1 = PMA is 10 Mb/s capable
                        0 = PMA is not 10 Mb/s capable  */
                    /*! \brief 01.0004.5 ROS PMA 100M Capable
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.pma100M_Capable

                        Default = 0x1

                        1 = PMA is 100 Mb/s capable
                        0 = PMA is not 100 Mb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.  */
      unsigned int   pma100M_Capable : 1;    /* 01.0004.5  ROS      Default = 0x1 */
                     /* 1 = PMA is 100 Mb/s capable
                        0 = PMA is not 100 Mb/s capable  */
                    /*! \brief 01.0004.4 ROS PMA 1G Capable
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.pma1G_Capable

                        Default = 0x1

                        1 = PMA is 1 Gb/s capable
                        0 = PMA is not 1 Gb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.  */
      unsigned int   pma1G_Capable : 1;    /* 01.0004.4  ROS      Default = 0x1 */
                     /* 1 = PMA is 1 Gb/s capable
                        0 = PMA is not 1 Gb/s capable  */
                    /*! \brief 01.0004.3 ROS Reserved_4c
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.reserved4c

                        Default = 0x0

                        Reserved bit 3
  */
      unsigned int   reserved4c : 1;    /* 01.0004.3  ROS      Default = 0x0 */
                     /* Reserved bit 3  */
                    /*! \brief 01.0004.2 ROS 10PASS-TS Capable
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0._10pass_tsCapable

                        Default = 0x0

                        1 = PMA is 10PASS-TS capable
                        0 = PMA is not 10PASS-TS capable

                 <B>Notes:</B>
                        This is always set to 0 in the PHY.  */
      unsigned int   _10pass_tsCapable : 1;    /* 01.0004.2  ROS      Default = 0x0 */
                     /* 1 = PMA is 10PASS-TS capable
                        0 = PMA is not 10PASS-TS capable  */
                    /*! \brief 01.0004.1 ROS 2BASE-TL Capable
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0._2base_tlCapable

                        Default = 0x0

                        1 = PMA is 2BASE-TL capable
                        0 = PMA is not 2BASE-TL capable

                 <B>Notes:</B>
                        This is always set to 0 in the PHY.  */
      unsigned int   _2base_tlCapable : 1;    /* 01.0004.1  ROS      Default = 0x0 */
                     /* 1 = PMA is 2BASE-TL capable
                        0 = PMA is not 2BASE-TL capable  */
                    /*! \brief 01.0004.0 ROS PMA 10G Capable
                        AQ_PmaStandardSpeedAbility_EUR.u0.bits_0.pma10G_Capable

                        Default = 0x1

                        1 = PMA is 10 Gb/s capable
                        0 = PMA is not 10 Gb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.  */
      unsigned int   pma10G_Capable : 1;    /* 01.0004.0  ROS      Default = 0x1 */
                     /* 1 = PMA is 10 Gb/s capable
                        0 = PMA is not 10 Gb/s capable  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaStandardSpeedAbility_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Standard Devices in Package: 01.0005 */
/*                  PMA Standard Devices in Package: 01.0005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Standard Devices in Package */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.0005.7 ROS Autonegotiation Present
                        AQ_PmaStandardDevicesInPackage_EUR.u0.bits_0.autonegotiationPresent

                        Default = 0x1

                        1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package

                 <B>Notes:</B>
                        This is always set to 1, as there is Autonegotiation in the PHY.  */
      unsigned int   autonegotiationPresent : 1;    /* 01.0005.7  ROS      Default = 0x1 */
                     /* 1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package  */
                    /*! \brief 01.0005.6 ROS TC Present
                        AQ_PmaStandardDevicesInPackage_EUR.u0.bits_0.tcPresent

                        Default = 0x0

                        1 = TC is present in package
                        0 = TC is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no TC functionality in the PHY.  */
      unsigned int   tcPresent : 1;    /* 01.0005.6  ROS      Default = 0x0 */
                     /* 1 = TC is present in package
                        0 = TC is not present in package  */
                    /*! \brief 01.0005.5 ROS DTE XS Present
                        AQ_PmaStandardDevicesInPackage_EUR.u0.bits_0.dteXsPresent

                        Default = 0x0

                        1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                        

                 <B>Notes:</B>
                        This is always set to 0, as there is no DTE XAUI interface in the PHY.  */
      unsigned int   dteXsPresent : 1;    /* 01.0005.5  ROS      Default = 0x0 */
                     /* 1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                          */
                    /*! \brief 01.0005.4 ROS PHY XS Present
                        AQ_PmaStandardDevicesInPackage_EUR.u0.bits_0.phyXS_Present

                        Default = 0x1

                        1 = PHY XS is present in package
                        0 = PHY XS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is a PHY XS interface in the PHY.  */
      unsigned int   phyXS_Present : 1;    /* 01.0005.4  ROS      Default = 0x1 */
                     /* 1 = PHY XS is present in package
                        0 = PHY XS is not present in package  */
                    /*! \brief 01.0005.3 ROS PCS Present
                        AQ_PmaStandardDevicesInPackage_EUR.u0.bits_0.pcsPresent

                        Default = 0x1

                        1 = PCS is present in package
                        0 = PCS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is PCS functionality in the PHY.  */
      unsigned int   pcsPresent : 1;    /* 01.0005.3  ROS      Default = 0x1 */
                     /* 1 = PCS is present in package
                        0 = PCS is not present in package  */
                    /*! \brief 01.0005.2 ROS WIS Present
                        AQ_PmaStandardDevicesInPackage_EUR.u0.bits_0.wisPresent

                        Default = 0x0

                        1 = WIS is present in package
                        0 = WIS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no WIS functionality in the PHY.  */
      unsigned int   wisPresent : 1;    /* 01.0005.2  ROS      Default = 0x0 */
                     /* 1 = WIS is present in package
                        0 = WIS is not present in package  */
                    /*! \brief 01.0005.1 ROS PMA Present
                        AQ_PmaStandardDevicesInPackage_EUR.u0.bits_0.pmaPresent

                        Default = 0x1

                        1 = PMA is present in package
                        0 = PMA is not present 

                 <B>Notes:</B>
                        This is always set to 1 as there is PMA functionality in the PHY.  */
      unsigned int   pmaPresent : 1;    /* 01.0005.1  ROS      Default = 0x1 */
                     /* 1 = PMA is present in package
                        0 = PMA is not present   */
                    /*! \brief 01.0005.0 ROS Clause 22 Registers Present
                        AQ_PmaStandardDevicesInPackage_EUR.u0.bits_0.clause_22RegistersPresent

                        Default = 0x0

                        1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package

                 <B>Notes:</B>
                        This is always set to 0 in the PHY, as there are no Clause 22 registers in the device.  */
      unsigned int   clause_22RegistersPresent : 1;    /* 01.0005.0  ROS      Default = 0x0 */
                     /* 1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA Standard Devices in Package */
  union
  {
    struct
    {
                    /*! \brief 01.0006.F ROS Vendor Specific Device #2 Present
                        AQ_PmaStandardDevicesInPackage_EUR.u1.bits_1.vendorSpecificDevice_2Present

                        Default = 0x1

                        1 = Device #2 is present in package
                        0 = Device #2 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the DSP PMA registers.  */
      unsigned int   vendorSpecificDevice_2Present : 1;    /* 01.0006.F  ROS      Default = 0x1 */
                     /* 1 = Device #2 is present in package
                        0 = Device #2 is not present in package  */
                    /*! \brief 01.0006.E ROS Vendor Specific Device #1 Present
                        AQ_PmaStandardDevicesInPackage_EUR.u1.bits_1.vendorSpecificDevice_1Present

                        Default = 0x1

                        1 = Device #1 is present in package
                        0 = Device #1 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the Global registers.  */
      unsigned int   vendorSpecificDevice_1Present : 1;    /* 01.0006.E  ROS      Default = 0x1 */
                     /* 1 = Device #1 is present in package
                        0 = Device #1 is not present in package  */
                    /*! \brief 01.0006.D ROS Clause 22 Extension Present
                        AQ_PmaStandardDevicesInPackage_EUR.u1.bits_1.clause_22ExtensionPresent

                        Default = 0x1

                        1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the GbE registers.  */
      unsigned int   clause_22ExtensionPresent : 1;    /* 01.0006.D  ROS      Default = 0x1 */
                     /* 1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package  */
      unsigned int   reserved0 : 13;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PmaStandardDevicesInPackage_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Standard Control 2: 01.0007 */
/*                  PMA Standard Control 2: 01.0007 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Standard Control 2 */
  union
  {
    struct
    {
                    /*! \brief 01.0007.F:6 R/WPD Reserved_7 [F:6]
                        AQ_PmaStandardControl_2_EUR.u0.bits_0.reserved7

                        Provisionable Default = 0x000

                        Reserved bits 15 to 6
  */
      unsigned int   reserved7 : 10;    /* 01.0007.F:6  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved bits 15 to 6  */
                    /*! \brief 01.0007.5:0 R/WPD PMA Device Type [5:0]
                        AQ_PmaStandardControl_2_EUR.u0.bits_0.pmaDeviceType

                        Provisionable Default = 0x09

                        [5:0]
                        5 4 3 2 1 0
                        1 1 0 0 0 1 = 5GBASE-T PMA/PMD type
                        1 1 0 0 0 0 = 2.5GBASE-T PMA/PMD type
                        0 0 1 1 1 1 = 10BASE-T PMA/PMD type
                        0 0 1 1 1 0 = 100BASE-TX PMA/PMD type
                        0 0 1 1 0 1 = 1000BASE-KX PMA/PMD type
                        0 0 1 1 0 0 = 1000BASE-T PMA/PMD type
                        0 0 1 0 1 1 = 10GBASE-KR PMA/PMD type
                        0 0 1 0 1 0 = 10GBASE-KX4 PMA/PMD type
                        0 0 1 0 0 1 = 10GBASE-T PMA type
                        0 0 1 0 0 0 = 10GBASE-LRM PMA/PMD type
                        0 0 0 1 1 1 = 10GBASE-SR PMA/PMD type
                        0 0 0 1 1 0 = 10GBASE-LR PMA/PMD type
                        0 0 0 1 0 1 = 10GBASE-ER PMA/PMD type
                        0 0 0 1 0 0 = 10GBASE-LX4 PMA/PMD type
                        0 0 0 0 1 1 = 10GBASE-SW PMA/PMD type
                        0 0 0 0 1 0 = 10GBASE-LW PMA/PMD type
                        0 0 0 0 0 1 = 10GBASE-EW PMA/PMD type
                        0 0 0 0 0 0 = 10GBASE-CX4 PMA/PMD type

                 <B>Notes:</B>
                        This is always set to 0x09 as the PHY is a 10GBASE-T device.
                        
                          */
      unsigned int   pmaDeviceType : 6;    /* 01.0007.5:0  R/WPD      Provisionable Default = 0x09 */
                     /* [5:0]
                        5 4 3 2 1 0
                        1 1 0 0 0 1 = 5GBASE-T PMA/PMD type
                        1 1 0 0 0 0 = 2.5GBASE-T PMA/PMD type
                        0 0 1 1 1 1 = 10BASE-T PMA/PMD type
                        0 0 1 1 1 0 = 100BASE-TX PMA/PMD type
                        0 0 1 1 0 1 = 1000BASE-KX PMA/PMD type
                        0 0 1 1 0 0 = 1000BASE-T PMA/PMD type
                        0 0 1 0 1 1 = 10GBASE-KR PMA/PMD type
                        0 0 1 0 1 0 = 10GBASE-KX4 PMA/PMD type
                        0 0 1 0 0 1 = 10GBASE-T PMA type
                        0 0 1 0 0 0 = 10GBASE-LRM PMA/PMD type
                        0 0 0 1 1 1 = 10GBASE-SR PMA/PMD type
                        0 0 0 1 1 0 = 10GBASE-LR PMA/PMD type
                        0 0 0 1 0 1 = 10GBASE-ER PMA/PMD type
                        0 0 0 1 0 0 = 10GBASE-LX4 PMA/PMD type
                        0 0 0 0 1 1 = 10GBASE-SW PMA/PMD type
                        0 0 0 0 1 0 = 10GBASE-LW PMA/PMD type
                        0 0 0 0 0 1 = 10GBASE-EW PMA/PMD type
                        0 0 0 0 0 0 = 10GBASE-CX4 PMA/PMD type  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaStandardControl_2_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Standard Status 2: 01.0008 */
/*                  PMA Standard Status 2: 01.0008 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Standard Status 2 */
  union
  {
    struct
    {
                    /*! \brief 01.0008.F:E ROS Device Present [1:0]
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.devicePresent

                        Default = 0x2

                        [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address

                 <B>Notes:</B>
                        This field is always set to 0x2, as the PMA is present in the PHY.  */
      unsigned int   devicePresent : 2;    /* 01.0008.F:E  ROS      Default = 0x2 */
                     /* [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address  */
                    /*! \brief 01.0008.D ROS Transmit Fault Location Ability
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.transmitFaultLocationAbility

                        Default = 0x1

                        1 = PMA has the capability to detect a fault condition on the transmit path
                        0= PMA does not have the capability to detect a fault condition on the transmit path

                 <B>Notes:</B>
                        This bit indicates whether the PMA has the ability to locate faults along the transmit path.  */
      unsigned int   transmitFaultLocationAbility : 1;    /* 01.0008.D  ROS      Default = 0x1 */
                     /* 1 = PMA has the capability to detect a fault condition on the transmit path
                        0= PMA does not have the capability to detect a fault condition on the transmit path  */
                    /*! \brief 01.0008.C ROS Receive Fault Location Ability
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.receiveFaultLocationAbility

                        Default = 0x1

                        1 = PMA has the capability to detect a fault condition on the receive path
                        0= PMA does not have the capability to detect a fault condition on the receive path

                 <B>Notes:</B>
                        This bit indicates whether the PMA has the ability to locate faults along the receive path.  */
      unsigned int   receiveFaultLocationAbility : 1;    /* 01.0008.C  ROS      Default = 0x1 */
                     /* 1 = PMA has the capability to detect a fault condition on the receive path
                        0= PMA does not have the capability to detect a fault condition on the receive path  */
                    /*! \brief 01.0008.B LH Transmit Fault
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.transmitFault

                        

                        1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the transmit path. This is a hardware fault and should never occur during normal operation.  */
      unsigned int   transmitFault : 1;    /* 01.0008.B  LH       */
                     /* 1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                          */
                    /*! \brief 01.0008.A LH Receive Fault
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.receiveFault

                        

                        1 = Fault condition on receive path
                        0 = No fault condition on receive path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the receive path.This is a hardware fault and should never occur during normal operation.  */
      unsigned int   receiveFault : 1;    /* 01.0008.A  LH       */
                     /* 1 = Fault condition on receive path
                        0 = No fault condition on receive path
                          */
                    /*! \brief 01.0008.9 ROS Extended Abilities
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.extendedAbilities

                        Default = 0x1

                        1 = PMA has extended abilities listed in regsister 1.11
                        0= PMA does not have extended abilities

                 <B>Notes:</B>
                        This field is set to 1, as the PMA in PHY has extended abilities.  */
      unsigned int   extendedAbilities : 1;    /* 01.0008.9  ROS      Default = 0x1 */
                     /* 1 = PMA has extended abilities listed in regsister 1.11
                        0= PMA does not have extended abilities  */
                    /*! \brief 01.0008.8 ROS PMD Transmit Disable Ability
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pmdTransmitDisableAbility

                        Default = 0x1

                        1 = PMD has the capability of disabling the transmitter
                        0= PMD does not have the capability of disabling the transmitter

                 <B>Notes:</B>
                        This bit indicates whether the PMD has the capability of disabling its transmitter. This field is always set to 0x1, as the PMD in the PHY has this ability.  */
      unsigned int   pmdTransmitDisableAbility : 1;    /* 01.0008.8  ROS      Default = 0x1 */
                     /* 1 = PMD has the capability of disabling the transmitter
                        0= PMD does not have the capability of disabling the transmitter  */
                    /*! \brief 01.0008.7 ROS PMA 10GBASE-SR Capable
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pma10GBaseSR_Capable

                        Default = 0x0

                        1 = PMA supports 10GBASE-SR
                        0 = PMA does not support 10GBASE-SR

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY only supports 10GBASE-T.  */
      unsigned int   pma10GBaseSR_Capable : 1;    /* 01.0008.7  ROS      Default = 0x0 */
                     /* 1 = PMA supports 10GBASE-SR
                        0 = PMA does not support 10GBASE-SR  */
                    /*! \brief 01.0008.6 ROS PMA 10GBASE-LR Capable
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pma10GBaseLR_Capable

                        Default = 0x0

                        1 = PMA supports 10GBASE-LR
                        0 = PMA does not support 10GBASE-LR

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY only supports 10GBASE-T.  */
      unsigned int   pma10GBaseLR_Capable : 1;    /* 01.0008.6  ROS      Default = 0x0 */
                     /* 1 = PMA supports 10GBASE-LR
                        0 = PMA does not support 10GBASE-LR  */
                    /*! \brief 01.0008.5 ROS PMA 10GBASE-ER Capable
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pma10GBaseER_Capable

                        Default = 0x0

                        1 = PMA supports 10GBASE-ER
                        0 = PMA does not support 10GBASE-ER

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY only supports 10GBASE-T.  */
      unsigned int   pma10GBaseER_Capable : 1;    /* 01.0008.5  ROS      Default = 0x0 */
                     /* 1 = PMA supports 10GBASE-ER
                        0 = PMA does not support 10GBASE-ER  */
                    /*! \brief 01.0008.4 ROS PMA 10GBASE-LX4 Capable
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pma10G_base_lx4Capable

                        Default = 0x0

                        1 = PMA supports 10GBASE-LX4
                        0 = PMA does not support 10GBASE-LX4

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY only supports 10GBASE-T.  */
      unsigned int   pma10G_base_lx4Capable : 1;    /* 01.0008.4  ROS      Default = 0x0 */
                     /* 1 = PMA supports 10GBASE-LX4
                        0 = PMA does not support 10GBASE-LX4  */
                    /*! \brief 01.0008.3 ROS PMA 10GBASE-SW Capable
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pma10GBaseSW_Capable

                        Default = 0x0

                        1 = PMA supports 10GBASE-SW
                        0 = PMA does not support 10GBASE-SW

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY only supports 10GBASE-T.  */
      unsigned int   pma10GBaseSW_Capable : 1;    /* 01.0008.3  ROS      Default = 0x0 */
                     /* 1 = PMA supports 10GBASE-SW
                        0 = PMA does not support 10GBASE-SW  */
                    /*! \brief 01.0008.2 ROS PMA 10GBASE-LW Capable
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pma10GBaseLW_Capable

                        Default = 0x0

                        1 = PMA supports 10GBASE-LW
                        0 = PMA does not support 10GBASE-LW

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY only supports 10GBASE-T.  */
      unsigned int   pma10GBaseLW_Capable : 1;    /* 01.0008.2  ROS      Default = 0x0 */
                     /* 1 = PMA supports 10GBASE-LW
                        0 = PMA does not support 10GBASE-LW  */
                    /*! \brief 01.0008.1 ROS PMA 10GBASE-EW Capable
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pma10GBaseEW_Capable

                        Default = 0x0

                        1 = PMA supports 10GBASE-EW
                        0 = PMA does not support 10GBASE-EW

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY only supports 10GBASE-T.  */
      unsigned int   pma10GBaseEW_Capable : 1;    /* 01.0008.1  ROS      Default = 0x0 */
                     /* 1 = PMA supports 10GBASE-EW
                        0 = PMA does not support 10GBASE-EW  */
                    /*! \brief 01.0008.0 ROS PMA Loopback Ability
                        AQ_PmaStandardStatus_2_EUR.u0.bits_0.pmaLoopbackAbility

                        Default = 0x1

                        1 = PMA supports loopback
                        0 = PMA does not support loopback
                        
                        

                 <B>Notes:</B>
                        This is always set to 1, as the PMA in the PHY supports loopback.  */
      unsigned int   pmaLoopbackAbility : 1;    /* 01.0008.0  ROS      Default = 0x1 */
                     /* 1 = PMA supports loopback
                        0 = PMA does not support loopback
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaStandardStatus_2_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMD Standard Transmit Disable Control: 01.0009 */
/*                  PMD Standard Transmit Disable Control: 01.0009 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMD Standard Transmit Disable Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 11;
                    /*! \brief 01.0009.4 R/WPD PMD Channel 3 Transmit Disable
                        AQ_PmdStandardTransmitDisableControl_EUR.u0.bits_0.pmdChannel_3TransmitDisable

                        Provisionable Default = 0x0

                        1 = Disable output on transmit channel 3
                        0 = Normal operation

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        When disabled, the average launch power on a pair is set to less than -53 dBm
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   pmdChannel_3TransmitDisable : 1;    /* 01.0009.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable output on transmit channel 3
                        0 = Normal operation  */
                    /*! \brief 01.0009.3 R/WPD PMD Channel 2 Transmit Disable
                        AQ_PmdStandardTransmitDisableControl_EUR.u0.bits_0.pmdChannel_2TransmitDisable

                        Provisionable Default = 0x0

                        1 = Disable output on transmit channel 2
                        0 = Normal operation

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        When disabled, the average launch power on a pair is set to less than -53 dBm
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   pmdChannel_2TransmitDisable : 1;    /* 01.0009.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable output on transmit channel 2
                        0 = Normal operation  */
                    /*! \brief 01.0009.2 R/WPD PMD Channel 1 Transmit Disable
                        AQ_PmdStandardTransmitDisableControl_EUR.u0.bits_0.pmdChannel_1TransmitDisable

                        Provisionable Default = 0x0

                        1 = Disable output on transmit channel 1
                        0 = Normal operation

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        When disabled, the average launch power on a pair is set to less than -53 dBm
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   pmdChannel_1TransmitDisable : 1;    /* 01.0009.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable output on transmit channel 1
                        0 = Normal operation  */
                    /*! \brief 01.0009.1 R/WPD PMD Channel 0 Transmit Disable
                        AQ_PmdStandardTransmitDisableControl_EUR.u0.bits_0.pmdChannel_0TransmitDisable

                        Provisionable Default = 0x0

                        1 = Disable output on transmit channel 0
                        0 = Normal operation

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        When disabled, the average launch power on a pair is set to less than -53 dBm
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   pmdChannel_0TransmitDisable : 1;    /* 01.0009.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable output on transmit channel 0
                        0 = Normal operation  */
                    /*! \brief 01.0009.0 R/WPD PMD Global Transmit Disable
                        AQ_PmdStandardTransmitDisableControl_EUR.u0.bits_0.pmdGlobalTransmitDisable

                        Provisionable Default = 0x0

                        1 = Disable output on all channels
                        0 = Normal operation

                 <B>Notes:</B>
                        When set, this bit disables (and overrides) all four channels, and sets the average launch power on all pairs to less than -53 dBm
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   pmdGlobalTransmitDisable : 1;    /* 01.0009.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable output on all channels
                        0 = Normal operation  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmdStandardTransmitDisableControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMD Standard Signal Detect: 01.000A */
/*                  PMD Standard Signal Detect: 01.000A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMD Standard Signal Detect */
  union
  {
    struct
    {
      unsigned int   reserved0 : 11;
                    /*! \brief 01.000A.4 RO PMD Channel 3 Signal Detect
                        AQ_PmdStandardSignalDetect_EUR.u0.bits_0.pmdChannel_3SignalDetect

                        

                        1 = Signal detected on receive channel 3
                        0 = No signal detected

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        These bits are used to indicate the presence of signals on a given pair. A signal is defined as an autonegotiation pulse or Ethernet signals.  */
      unsigned int   pmdChannel_3SignalDetect : 1;    /* 01.000A.4  RO       */
                     /* 1 = Signal detected on receive channel 3
                        0 = No signal detected  */
                    /*! \brief 01.000A.3 RO PMD Channel 2 Signal Detect
                        AQ_PmdStandardSignalDetect_EUR.u0.bits_0.pmdChannel_2SignalDetect

                        

                        1 = Signal detected on receive channel 2
                        0 = No signal detected

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        These bits are used to indicate the presence of signals on a given pair. A signal is defined as an autonegotiation pulse or Ethernet signals.  */
      unsigned int   pmdChannel_2SignalDetect : 1;    /* 01.000A.3  RO       */
                     /* 1 = Signal detected on receive channel 2
                        0 = No signal detected  */
                    /*! \brief 01.000A.2 RO PMD Channel 1 Signal Detect
                        AQ_PmdStandardSignalDetect_EUR.u0.bits_0.pmdChannel_1SignalDetect

                        

                        1 = Signal detected on receive channel 1
                        0 = No signal detected

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        These bits are used to indicate the presence of signals on a given pair. A signal is defined as an autonegotiation pulse or Ethernet signals.  */
      unsigned int   pmdChannel_1SignalDetect : 1;    /* 01.000A.2  RO       */
                     /* 1 = Signal detected on receive channel 1
                        0 = No signal detected  */
                    /*! \brief 01.000A.1 RO PMD Channel 0 Signal Detect
                        AQ_PmdStandardSignalDetect_EUR.u0.bits_0.pmdChannel_0SignalDetect

                        

                        1 = Signal detected on receive channel 0
                        0 = No signal detected

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        These bits are used to indicate the presence of signals on a given pair. A signal is defined as an autonegotiation pulse or Ethernet signals.  */
      unsigned int   pmdChannel_0SignalDetect : 1;    /* 01.000A.1  RO       */
                     /* 1 = Signal detected on receive channel 0
                        0 = No signal detected  */
                    /*! \brief 01.000A.0 RO PMD Global Signal Detect
                        AQ_PmdStandardSignalDetect_EUR.u0.bits_0.pmdGlobalSignalDetect

                        

                        1 = Signals detected on all required channels
                        0 = No signal detected
                        

                 <B>Notes:</B>
                        This bit is marked when all required, valid Ethernet signals to create a connection are present on the line.  */
      unsigned int   pmdGlobalSignalDetect : 1;    /* 01.000A.0  RO       */
                     /* 1 = Signals detected on all required channels
                        0 = No signal detected
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmdStandardSignalDetect_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMD Standard 10G Extended Ability Register: 01.000B */
/*                  PMD Standard 10G Extended Ability Register: 01.000B */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMD Standard 10G Extended Ability Register */
  union
  {
    struct
    {
                    /*! \brief 01.000B.F ROS Reserved_b0
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.reservedB0

                        Default = 0x0

                        Reserved bit 15
  */
      unsigned int   reservedB0 : 1;    /* 01.000B.F  ROS      Default = 0x0 */
                     /* Reserved bit 15  */
                    /*! \brief 01.000B.E ROS PMA 2.5/5GBASE-T Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma_2_5_5gbase_tCapable

                        Default = 0x1

                        1 = PMA capable of 2.5/5GBASE-T
                        0 = PMA incapable of 2.5/5GBASE-T

                 <B>Notes:</B>
                        This field is set to 1, as the PMA in the PHY supports 2.5/5GBASE-T
                          */
      unsigned int   pma_2_5_5gbase_tCapable : 1;    /* 01.000B.E  ROS      Default = 0x1 */
                     /* 1 = PMA capable of 2.5/5GBASE-T
                        0 = PMA incapable of 2.5/5GBASE-T  */
                    /*! \brief 01.000B.D:9 ROS Reserved_b1 [D:9]
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.reservedB1

                        Default = 0x00

                        Reserved bits 13 to 9
  */
      unsigned int   reservedB1 : 5;    /* 01.000B.D:9  ROS      Default = 0x00 */
                     /* Reserved bits 13 to 9  */
                    /*! \brief 01.000B.8 ROS PMA 10BASE-T Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma10BaseT_Capable

                        Default = 0x0

                        1 = PMA capable of 10BASE-T
                        0 = PMA incapable of 10BASE-T

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY does not support 10BASE-TX.  */
      unsigned int   pma10BaseT_Capable : 1;    /* 01.000B.8  ROS      Default = 0x0 */
                     /* 1 = PMA capable of 10BASE-T
                        0 = PMA incapable of 10BASE-T  */
                    /*! \brief 01.000B.7 ROS PMA 100BASE-TX Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma_100base_txCapable

                        Default = 0x1

                        1 = PMA capable of 100BASE-TX
                        0 = PMA incapable of 100BASE-TX

                 <B>Notes:</B>
                        This field is always set to 1, as the PMA in the PHY supports 100BASE-TX.  */
      unsigned int   pma_100base_txCapable : 1;    /* 01.000B.7  ROS      Default = 0x1 */
                     /* 1 = PMA capable of 100BASE-TX
                        0 = PMA incapable of 100BASE-TX  */
                    /*! \brief 01.000B.6 ROS PMA 1000BASE-KX Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma_1000base_kxCapable

                        Default = 0x1

                        1 = PMA capable of 1000BASE-KX
                        0 = PMA incapable of 1000BASE-KX

                 <B>Notes:</B>
                        This field is always set to 1, as the PMA in the PHY supports 1000BASE-KX.  */
      unsigned int   pma_1000base_kxCapable : 1;    /* 01.000B.6  ROS      Default = 0x1 */
                     /* 1 = PMA capable of 1000BASE-KX
                        0 = PMA incapable of 1000BASE-KX  */
                    /*! \brief 01.000B.5 ROS PMA 1000BASE-T Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma1000BaseT_Capable

                        Default = 0x1

                        1 = PMA capable of 1000BASE-T
                        0 = PMA incapable of 1000BASE-T

                 <B>Notes:</B>
                        This field is set to 1, as the PMA in the PHY supports 1000BASE-T.  */
      unsigned int   pma1000BaseT_Capable : 1;    /* 01.000B.5  ROS      Default = 0x1 */
                     /* 1 = PMA capable of 1000BASE-T
                        0 = PMA incapable of 1000BASE-T  */
                    /*! \brief 01.000B.4 ROS PMA 10GBASE-KR Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma10GBaseK_rCapable

                        Default = 0x1

                        1 = PMA capable of 10GBASE-KR
                        0 = PMA incapable of 10GBASE-KR

                 <B>Notes:</B>
                        This field is set to 1, as the PMA in the PHY supports 10GBASE-KR  */
      unsigned int   pma10GBaseK_rCapable : 1;    /* 01.000B.4  ROS      Default = 0x1 */
                     /* 1 = PMA capable of 10GBASE-KR
                        0 = PMA incapable of 10GBASE-KR  */
                    /*! \brief 01.000B.3 ROS PMA 10GBASE-KX4 Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma10GBaseK_x4Capable

                        Default = 0x1

                        1 = PMA capable of 10GBASE-KX4
                        0 = PMA incapable of 10GBASE-KX4

                 <B>Notes:</B>
                        This field is set to 1, as the PMA in the PHY supports 10GBASE-KX4  */
      unsigned int   pma10GBaseK_x4Capable : 1;    /* 01.000B.3  ROS      Default = 0x1 */
                     /* 1 = PMA capable of 10GBASE-KX4
                        0 = PMA incapable of 10GBASE-KX4  */
                    /*! \brief 01.000B.2 ROS PMA 10GBASE-T Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma10GBaseT_Capable

                        Default = 0x1

                        1 = PMA capable of 10GBASE-T
                        0 = PMA incapable of 10GBASE-T

                 <B>Notes:</B>
                        This field is set to 1, as the PMA in the PHY supports 10GBASE-T  */
      unsigned int   pma10GBaseT_Capable : 1;    /* 01.000B.2  ROS      Default = 0x1 */
                     /* 1 = PMA capable of 10GBASE-T
                        0 = PMA incapable of 10GBASE-T  */
                    /*! \brief 01.000B.1 ROS PMA 10GBASE-LRM Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma10GBaseLR_mCapable

                        Default = 0x0

                        1 = PMA capable of 10GBASE-LRM
                        0 = PMA incapable of 10GBASE-LRM

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY does not support 10GBASE-LRM.  */
      unsigned int   pma10GBaseLR_mCapable : 1;    /* 01.000B.1  ROS      Default = 0x0 */
                     /* 1 = PMA capable of 10GBASE-LRM
                        0 = PMA incapable of 10GBASE-LRM  */
                    /*! \brief 01.000B.0 ROS PMA 10GBASE-CX4 Capable
                        AQ_PmdStandard10G_ExtendedAbilityRegister_EUR.u0.bits_0.pma10GBaseCX4_Capable

                        Default = 0x0

                        1 = PMA capable of 10GBASE-CX4
                        0 = PMA incapable of 10GBASE-CX4

                 <B>Notes:</B>
                        This field is always set to 0, as the PMA in the PHY does not support 10GBASE-CX4.  */
      unsigned int   pma10GBaseCX4_Capable : 1;    /* 01.000B.0  ROS      Default = 0x0 */
                     /* 1 = PMA capable of 10GBASE-CX4
                        0 = PMA incapable of 10GBASE-CX4  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmdStandard10G_ExtendedAbilityRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Standard Package Identifier: 01.000E */
/*                  PMA Standard Package Identifier: 01.000E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 01.000E.F:0 RO Package ID MSW [1F:10]
                        AQ_PmaStandardPackageIdentifier_EUR.u0.bits_0.packageIdMSW

                        

                        Bits 31- 16 of Package ID
  */
      unsigned int   packageIdMSW : 16;    /* 01.000E.F:0  RO       */
                     /* Bits 31- 16 of Package ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 01.000F.F:0 RO Package ID LSW [F:0]
                        AQ_PmaStandardPackageIdentifier_EUR.u1.bits_1.packageIdLSW

                        

                        Bits 15 - 0 of Package ID
  */
      unsigned int   packageIdLSW : 16;    /* 01.000F.F:0  RO       */
                     /* Bits 15 - 0 of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PmaStandardPackageIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Reserved 14 Register: 01.0014 */
/*                  PMA Reserved 14 Register: 01.0014 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Reserved 14 Register */
  union
  {
    struct
    {
                    /*! \brief 01.0014.F:0 R/W Reserved_14 [F:0]
                        AQ_PmaReserved_14Register_EUR.u0.bits_0.reserved14

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved14 : 16;    /* 01.0014.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaReserved_14Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Extended Ability Register: 01.0015 */
/*                  PMA Extended Ability Register: 01.0015 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Extended Ability Register */
  union
  {
    struct
    {
                    /*! \brief 01.0015.F:2 ROS Reserved_15 [F:2]
                        AQ_PmaExtendedAbilityRegister_EUR.u0.bits_0.reserved15

                        Default = 0x0000

                        Reserved bits [15:2]
  */
      unsigned int   reserved15 : 14;    /* 01.0015.F:2  ROS      Default = 0x0000 */
                     /* Reserved bits [15:2]  */
                    /*! \brief 01.0015.1 ROS 5GBASE-T Ability
                        AQ_PmaExtendedAbilityRegister_EUR.u0.bits_0._5gbase_tAbility

                        Default = 0x1

                        1 = PMA/PMD is able to perform 5GBASE-T
                        0 = PMA/PMD is not able to perform 5GBASE-T
  */
      unsigned int   _5gbase_tAbility : 1;    /* 01.0015.1  ROS      Default = 0x1 */
                     /* 1 = PMA/PMD is able to perform 5GBASE-T
                        0 = PMA/PMD is not able to perform 5GBASE-T  */
                    /*! \brief 01.0015.0 ROS 2.5GBASE-T Ability
                        AQ_PmaExtendedAbilityRegister_EUR.u0.bits_0._2_5gbase_tAbility

                        Default = 0x1

                        1 = PMA/PMD is able to perform 2.5GBASE-T
                        0 = PMA/PMD is not able to perform 2.5GBASE-T
  */
      unsigned int   _2_5gbase_tAbility : 1;    /* 01.0015.0  ROS      Default = 0x1 */
                     /* 1 = PMA/PMD is able to perform 2.5GBASE-T
                        0 = PMA/PMD is not able to perform 2.5GBASE-T  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaExtendedAbilityRegister_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Reserved 16 Register: 01.0016 */
/*                  PMA Reserved 16 Register: 01.0016 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Reserved 16 Register */
  union
  {
    struct
    {
                    /*! \brief 01.0016.F:0 R/W Reserved_16 [F:0]
                        AQ_PmaReserved_16Register_EUR.u0.bits_0.reserved16

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved16 : 16;    /* 01.0016.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaReserved_16Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Reserved 17 Register: 01.0017 */
/*                  PMA Reserved 17 Register: 01.0017 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Reserved 17 Register */
  union
  {
    struct
    {
                    /*! \brief 01.0017.F:0 R/W Reserved_17 [F:0]
                        AQ_PmaReserved_17Register_EUR.u0.bits_0.reserved17

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved17 : 16;    /* 01.0017.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaReserved_17Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Reserved 18 Register: 01.0018 */
/*                  PMA Reserved 18 Register: 01.0018 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Reserved 18 Register */
  union
  {
    struct
    {
                    /*! \brief 01.0018.F:0 R/W Reserved_18 [F:0]
                        AQ_PmaReserved_18Register_EUR.u0.bits_0.reserved18

                        Default = 0x0000

                        Reserved bits [15:0]
  */
      unsigned int   reserved18 : 16;    /* 01.0018.F:0  R/W      Default = 0x0000 */
                     /* Reserved bits [15:0]  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaReserved_18Register_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Status: 01.0081 */
/*                  PMA 10GBASE-T Status: 01.0081 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 01.0081.0 RO Link Partner Information Valid
                        AQ_Pma10GBaseT_Status_EUR.u0.bits_0.linkPartnerInformationValid

                        

                        1 = 10GBASE-T Link Partner information is valid
                        0 = 10GBASE-T Link Partner information is not valid

                 <B>Notes:</B>
                        When set, this bit indicates that the startup protocol (55.4.2.5) has completed.  */
      unsigned int   linkPartnerInformationValid : 1;    /* 01.0081.0  RO       */
                     /* 1 = 10GBASE-T Link Partner information is valid
                        0 = 10GBASE-T Link Partner information is not valid  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_Status_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Pair Swap and Polarity Status: 01.0082 */
/*                  PMA 10GBASE-T Pair Swap and Polarity Status: 01.0082 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Pair Swap and Polarity Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 01.0082.B:8 RO Pair Polarity [3:0]
                        AQ_Pma10GBaseT_PairSwapAndPolarityStatus_EUR.u0.bits_0.pairPolarity

                        

                        1 = Polarity of Pair is reversed
                        0 = Polarity of Pair is normal
                        [3] = Pair D Polarity
                        [2] = Pair C Polarity
                        [1] = Pair B Polarity
                        [0] = Pair A Polarity
                        

                 <B>Notes:</B>
                        When set, this bit indicates that the wires on the respective pair are reversed.  */
      unsigned int   pairPolarity : 4;    /* 01.0082.B:8  RO       */
                     /* 1 = Polarity of Pair is reversed
                        0 = Polarity of Pair is normal
                        [3] = Pair D Polarity
                        [2] = Pair C Polarity
                        [1] = Pair B Polarity
                        [0] = Pair A Polarity
                          */
      unsigned int   reserved1 : 6;
                    /*! \brief 01.0082.1:0 RO MDI / MD-X Connection State [1:0]
                        AQ_Pma10GBaseT_PairSwapAndPolarityStatus_EUR.u0.bits_0.mdi_Md_xConnectionState

                        

                        [1:0]
                        1 1 = No crossover
                        1 0 = Pair A / B crossover
                        0 1 = Pair C / D crossover
                        0 0 = Pair A / B and C / D crossover
                        

                 <B>Notes:</B>
                        These two bits indicate the current status of pair swaps at the MDI / MD-X  */
      unsigned int   mdi_Md_xConnectionState : 2;    /* 01.0082.1:0  RO       */
                     /* [1:0]
                        1 1 = No crossover
                        1 0 = Pair A / B crossover
                        0 1 = Pair C / D crossover
                        0 0 = Pair A / B and C / D crossover
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_PairSwapAndPolarityStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Tx Power Backoff and Short Reach Setting: 01.0083 */
/*                  PMA 10GBASE-T Tx Power Backoff and Short Reach Setting: 01.0083 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Tx Power Backoff and Short Reach Setting */
  union
  {
    struct
    {
                    /*! \brief 01.0083.F:D RO Link Partner Tx Power Backoff [2:0]
                        AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_EUR.u0.bits_0.linkPartnerTxPowerBackoff

                        

                        [F:D]
                        0x7 = 14 dB
                        0x6 = 12 dB
                        0x5 = 10 dB
                        0x4 = 8 dB
                        0x3 = 6 dB
                        0x2 = 4 dB
                        0x1 = 2 dB
                        0x0 = 0 dB

                 <B>Notes:</B>
                        The power backoff of the link partner  */
      unsigned int   linkPartnerTxPowerBackoff : 3;    /* 01.0083.F:D  RO       */
                     /* [F:D]
                        0x7 = 14 dB
                        0x6 = 12 dB
                        0x5 = 10 dB
                        0x4 = 8 dB
                        0x3 = 6 dB
                        0x2 = 4 dB
                        0x1 = 2 dB
                        0x0 = 0 dB  */
                    /*! \brief 01.0083.C:A RO Tx Power Backoff [2:0]
                        AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_EUR.u0.bits_0.txPowerBackoff

                        

                        [C:A]
                        0x7 = 14 dB
                        0x6 = 12 dB
                        0x5 = 10 dB
                        0x4 = 8 dB
                        0x3 = 6 dB
                        0x2 = 4 dB
                        0x1 = 2 dB
                        0x0 = 0 dB

                 <B>Notes:</B>
                        The power backoff of the PMA  */
      unsigned int   txPowerBackoff : 3;    /* 01.0083.C:A  RO       */
                     /* [C:A]
                        0x7 = 14 dB
                        0x6 = 12 dB
                        0x5 = 10 dB
                        0x4 = 8 dB
                        0x3 = 6 dB
                        0x2 = 4 dB
                        0x1 = 2 dB
                        0x0 = 0 dB  */
                    /*! \brief 01.0083.9:1 R/WPD Reserved_83 [9:1]
                        AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_EUR.u0.bits_0.reserved83

                        Provisionable Default = 0x000

                        Reserved bits 9 to 1
  */
      unsigned int   reserved83 : 9;    /* 01.0083.9:1  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved bits 9 to 1  */
                    /*! \brief 01.0083.0 R/WPD Short Reach Mode
                        AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_EUR.u0.bits_0.shortReachMode

                        Provisionable Default = 0x0

                        1 = Set PMA to operate in short-reach mode
                        0 = PMA is in normal operation

                 <B>Notes:</B>
                        When set, this bit places the PMA into short-reach mode  */
      unsigned int   shortReachMode : 1;    /* 01.0083.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Set PMA to operate in short-reach mode
                        0 = PMA is in normal operation  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_TxPowerBackoffAndShortReachSetting_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Test Modes: 01.0084 */
/*                  PMA 10GBASE-T Test Modes: 01.0084 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Test Modes */
  union
  {
    struct
    {
                    /*! \brief 01.0084.F:D R/WPD Test Mode Control [2:0]
                        AQ_Pma10GBaseT_TestModes_EUR.u0.bits_0.testModeControl

                        Provisionable Default = 0x0

                        [F:D]
                        0x7 = Pseudo random test mode for BER Monitor
                        0x6 = Transmitter Droop test
                        0x5 = PSD and power level test
                        0x4 = Transmitter distortion test
                        0x3 = Slave mode jitter test
                        0x2 = Master mode jitter test
                        0x1 = Master source for slave mode jitter test
                        0x0 = Normal operation
                        

                 <B>Notes:</B>
                        Test mode control for the PMA as defined in Section 55.5.2 of 802.3an.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   testModeControl : 3;    /* 01.0084.F:D  R/WPD      Provisionable Default = 0x0 */
                     /* [F:D]
                        0x7 = Pseudo random test mode for BER Monitor
                        0x6 = Transmitter Droop test
                        0x5 = PSD and power level test
                        0x4 = Transmitter distortion test
                        0x3 = Slave mode jitter test
                        0x2 = Master mode jitter test
                        0x1 = Master source for slave mode jitter test
                        0x0 = Normal operation
                          */
                    /*! \brief 01.0084.C:A R/WPD Transmitter Test Frequencies [2:0]
                        AQ_Pma10GBaseT_TestModes_EUR.u0.bits_0.transmitterTestFrequencies

                        Provisionable Default = 0x0

                        [C:A]
                        0x7 = Reserved
                        0x6 = Dual Tone #5
                        0x5 = Dual Tone #4
                        0x4 = Dual Tone #3
                        0x3 = Reserved
                        0x2 = Dual Tone #2
                        0x1 = Dual Tone #1
                        0x0 = Reserved

                 <B>Notes:</B>
                        The test frequencies associated with Test Mode #4 in [F:D].  */
      unsigned int   transmitterTestFrequencies : 3;    /* 01.0084.C:A  R/WPD      Provisionable Default = 0x0 */
                     /* [C:A]
                        0x7 = Reserved
                        0x6 = Dual Tone #5
                        0x5 = Dual Tone #4
                        0x4 = Dual Tone #3
                        0x3 = Reserved
                        0x2 = Dual Tone #2
                        0x1 = Dual Tone #1
                        0x0 = Reserved  */
      unsigned int   reserved0 : 10;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_TestModes_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T SNR Operating Margin Channel A: 01.0085 */
/*                  PMA 10GBASE-T SNR Operating Margin Channel A: 01.0085 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T SNR Operating Margin Channel A */
  union
  {
    struct
    {
                    /*! \brief 01.0085.F:0 RO Channel A Operating Margin [F:0]
                        AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_EUR.u0.bits_0.channelAOperatingMargin

                        

                        Operating margin (dB) of Channel A
                        

                 <B>Notes:</B>
                        The excess SNR that is enjoyed by the channel, over and above the minimum SNR required to operate at a BER of 10-12. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -12.7 dB to 12.7 dB. The number is in offset binary, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelAOperatingMargin : 16;    /* 01.0085.F:0  RO       */
                     /* Operating margin (dB) of Channel A
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_SNR_OperatingMarginChannelA_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T SNR Operating Margin Channel B: 01.0086 */
/*                  PMA 10GBASE-T SNR Operating Margin Channel B: 01.0086 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T SNR Operating Margin Channel B */
  union
  {
    struct
    {
                    /*! \brief 01.0086.F:0 RO Channel B Operating Margin [F:0]
                        AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_EUR.u0.bits_0.channelBOperatingMargin

                        

                        Operating margin (dB) of Channel B
                        

                 <B>Notes:</B>
                        The excess SNR that is enjoyed by the channel, over and above the minimum SNR required to operate at a BER of 10-12. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -12.7 dB to 12.7 dB. The number is in offset binary, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelBOperatingMargin : 16;    /* 01.0086.F:0  RO       */
                     /* Operating margin (dB) of Channel B
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_SNR_OperatingMarginChannelB_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T SNR Operating Margin Channel C: 01.0087 */
/*                  PMA 10GBASE-T SNR Operating Margin Channel C: 01.0087 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T SNR Operating Margin Channel C */
  union
  {
    struct
    {
                    /*! \brief 01.0087.F:0 RO Channel C Operating Margin [F:0]
                        AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_EUR.u0.bits_0.channelCOperatingMargin

                        

                        Operating margin (dB) of Channel C
                        

                 <B>Notes:</B>
                        The excess SNR that is enjoyed by the channel, over and above the minimum SNR required to operate at a BER of 10-12. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -12.7 dB to 12.7 dB. The number is in offset binary, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelCOperatingMargin : 16;    /* 01.0087.F:0  RO       */
                     /* Operating margin (dB) of Channel C
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_SNR_OperatingMarginChannelC_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T SNR Operating Margin Channel D: 01.0088 */
/*                  PMA 10GBASE-T SNR Operating Margin Channel D: 01.0088 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T SNR Operating Margin Channel D */
  union
  {
    struct
    {
                    /*! \brief 01.0088.F:0 RO Channel D Operating Margin [F:0]
                        AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_EUR.u0.bits_0.channelDOperatingMargin

                        

                        Operating margin (dB) of Channel D
                        

                 <B>Notes:</B>
                        The excess SNR that is enjoyed by the channel, over and above the minimum SNR required to operate at a BER of 10-12. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -12.7 dB to 12.7 dB. The number is in offset binary, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelDOperatingMargin : 16;    /* 01.0088.F:0  RO       */
                     /* Operating margin (dB) of Channel D
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_SNR_OperatingMarginChannelD_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T SNR Minimum Operating Margin Channel A: 01.0089 */
/*                  PMA 10GBASE-T SNR Minimum Operating Margin Channel A: 01.0089 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T SNR Minimum Operating Margin Channel A */
  union
  {
    struct
    {
                    /*! \brief 01.0089.F:0 RO Channel A Minimum Operating Margin [F:0]
                        AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_EUR.u0.bits_0.channelAMinimumOperatingMargin

                        

                        Minimum operating margin (dB) of Channel A since last link up

                 <B>Notes:</B>
                        The excess SNR that is enjoyed by the channel, over and above the minimum SNR required to operate at a BER of 10-12. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -12.7 dB to 12.7 dB. The number is in offset binary, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelAMinimumOperatingMargin : 16;    /* 01.0089.F:0  RO       */
                     /* Minimum operating margin (dB) of Channel A since last link up  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelA_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T SNR Minimum Operating Margin Channel B: 01.008A */
/*                  PMA 10GBASE-T SNR Minimum Operating Margin Channel B: 01.008A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T SNR Minimum Operating Margin Channel B */
  union
  {
    struct
    {
                    /*! \brief 01.008A.F:0 RO Channel B Minimum Operating Margin [F:0]
                        AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_EUR.u0.bits_0.channelBMinimumOperatingMargin

                        

                        Minimum operating margin (dB) of Channel B since last link up

                 <B>Notes:</B>
                        The excess SNR that is enjoyed by the channel, over and above the minimum SNR required to operate at a BER of 10-12. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -12.7 dB to 12.7 dB. The number is in offset binary, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelBMinimumOperatingMargin : 16;    /* 01.008A.F:0  RO       */
                     /* Minimum operating margin (dB) of Channel B since last link up  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelB_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T SNR Minimum Operating Margin Channel C: 01.008B */
/*                  PMA 10GBASE-T SNR Minimum Operating Margin Channel C: 01.008B */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T SNR Minimum Operating Margin Channel C */
  union
  {
    struct
    {
                    /*! \brief 01.008B.F:0 RO Channel C Minimum Operating Margin [F:0]
                        AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_EUR.u0.bits_0.channelCMinimumOperatingMargin

                        

                        Minimum operating margin (dB) of Channel C since last link up

                 <B>Notes:</B>
                        The excess SNR that is enjoyed by the channel, over and above the minimum SNR required to operate at a BER of 10-12. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -12.7 dB to 12.7 dB. The number is in offset binary, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelCMinimumOperatingMargin : 16;    /* 01.008B.F:0  RO       */
                     /* Minimum operating margin (dB) of Channel C since last link up  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelC_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T SNR Minimum Operating Margin Channel D: 01.008C */
/*                  PMA 10GBASE-T SNR Minimum Operating Margin Channel D: 01.008C */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T SNR Minimum Operating Margin Channel D */
  union
  {
    struct
    {
                    /*! \brief 01.008C.F:0 RO Channel D Minimum Operating Margin [F:0]
                        AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_EUR.u0.bits_0.channelDMinimumOperatingMargin

                        

                        Minimum operating margin (dB) of Channel D since last link up

                 <B>Notes:</B>
                        The excess SNR that is enjoyed by the channel, over and above the minimum SNR required to operate at a BER of 10-12. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -12.7 dB to 12.7 dB. The number is in offset binary, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelDMinimumOperatingMargin : 16;    /* 01.008C.F:0  RO       */
                     /* Minimum operating margin (dB) of Channel D since last link up  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_SNR_MinimumOperatingMarginChannelD_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Receive Signal Power Channel A: 01.008D */
/*                  PMA 10GBASE-T Receive Signal Power Channel A: 01.008D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Receive Signal Power Channel A */
  union
  {
    struct
    {
                    /*! \brief 01.008D.F:0 RO Channel A Received Signal Power [F:0]
                        AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_EUR.u0.bits_0.channelAReceivedSignalPower

                        

                        Received signal power (dBm) for Channel A

                 <B>Notes:</B>
                        The received signal power on the channel. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -20.0 dB to +5.5dB. The number is in offset two's complement notation, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelAReceivedSignalPower : 16;    /* 01.008D.F:0  RO       */
                     /* Received signal power (dBm) for Channel A  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_ReceiveSignalPowerChannelA_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Receive Signal Power Channel B: 01.008E */
/*                  PMA 10GBASE-T Receive Signal Power Channel B: 01.008E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Receive Signal Power Channel B */
  union
  {
    struct
    {
                    /*! \brief 01.008E.F:0 RO Channel B Received Signal Power [F:0]
                        AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_EUR.u0.bits_0.channelBReceivedSignalPower

                        

                        Received signal power (dBm) for Channel B

                 <B>Notes:</B>
                        The received signal power on the channel. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -20.0 dB to +5.5dB. The number is in offset two's complement notation, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelBReceivedSignalPower : 16;    /* 01.008E.F:0  RO       */
                     /* Received signal power (dBm) for Channel B  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_ReceiveSignalPowerChannelB_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Receive Signal Power Channel C: 01.008F */
/*                  PMA 10GBASE-T Receive Signal Power Channel C: 01.008F */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Receive Signal Power Channel C */
  union
  {
    struct
    {
                    /*! \brief 01.008F.F:0 RO Channel C Received Signal Power [F:0]
                        AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_EUR.u0.bits_0.channelCReceivedSignalPower

                        

                        Received signal power (dBm) for Channel C

                 <B>Notes:</B>
                        The received signal power on the channel. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -20.0 dB to +5.5dB. The number is in offset two's complement notation, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelCReceivedSignalPower : 16;    /* 01.008F.F:0  RO       */
                     /* Received signal power (dBm) for Channel C  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_ReceiveSignalPowerChannelC_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Receive Signal Power Channel D: 01.0090 */
/*                  PMA 10GBASE-T Receive Signal Power Channel D: 01.0090 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Receive Signal Power Channel D */
  union
  {
    struct
    {
                    /*! \brief 01.0090.F:0 RO Channel D Received Signal Power [F:0]
                        AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_EUR.u0.bits_0.channelDReceivedSignalPower

                        

                        Received signal power (dBm) for Channel D

                 <B>Notes:</B>
                        The received signal power on the channel. It is reported with 0.1 dB of resolution to an accuracy of 0.5 dB within the range of -20.0 dB to +5.5dB. The number is in offset two's complement notation, with 0.0 dB represented by 0x8000.  */
      unsigned int   channelDReceivedSignalPower : 16;    /* 01.0090.F:0  RO       */
                     /* Received signal power (dBm) for Channel D  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_ReceiveSignalPowerChannelD_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Skew Delay: 01.0091 */
/*                  PMA 10GBASE-T Skew Delay: 01.0091 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Skew Delay */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 01.0091.E:8 RO Skew Delay B [6:0]
                        AQ_Pma10GBaseT_SkewDelay_EUR.u0.bits_0.skewDelayB

                        

                        Skew delay for pair B
                        

                 <B>Notes:</B>
                        The skew delay reports the current skew delay on each of the pair with respect to physical pair A. It is reported with 1.25 ns resolution to an accuracy of 2.5 ns. The number is in two's complement notation with positive values representing delay and negative values representing advance with respect to physical pair A. If the delay exceed the maximum amount that can be represented by the range (-80 ns to +78.75 ns), the field displays the maximum respective value.  */
      unsigned int   skewDelayB : 7;    /* 01.0091.E:8  RO       */
                     /* Skew delay for pair B
                          */
      unsigned int   reserved1 : 8;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA 10GBASE-T Skew Delay */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 01.0092.E:8 RO Skew Delay D [6:0]
                        AQ_Pma10GBaseT_SkewDelay_EUR.u1.bits_1.skewDelayD

                        

                        Skew delay for pair D
                        

                 <B>Notes:</B>
                        The skew delay reports the current skew delay on each of the pair with respect to physical pair A. It is reported with 1.25 ns resolution to an accuracy of 2.5 ns. The number is in two's complement notation with positive values representing delay and negative values representing advance with respect to physical pair A. If the delay exceed the maximum amount that can be represented by the range (-80 ns to +78.75 ns), the field displays the maximum respective value.  */
      unsigned int   skewDelayD : 7;    /* 01.0092.E:8  RO       */
                     /* Skew delay for pair D
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 01.0092.6:0 RO Skew Delay C [6:0]
                        AQ_Pma10GBaseT_SkewDelay_EUR.u1.bits_1.skewDelayC

                        

                        Skew delay for pair C
                        

                 <B>Notes:</B>
                        The skew delay reports the current skew delay on each of the pair with respect to physical pair A. It is reported with 1.25 ns resolution to an accuracy of 2.5 ns. The number is in two's complement notation with positive values representing delay and negative values representing advance with respect to physical pair A. If the delay exceed the maximum amount that can be represented by the range (-80 ns to +78.75 ns), the field displays the maximum respective value.  */
      unsigned int   skewDelayC : 7;    /* 01.0092.6:0  RO       */
                     /* Skew delay for pair C
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_Pma10GBaseT_SkewDelay_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA 10GBASE-T Fast Retrain Status and Control: 01.0093 */
/*                  PMA 10GBASE-T Fast Retrain Status and Control: 01.0093 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA 10GBASE-T Fast Retrain Status and Control */
  union
  {
    struct
    {
                    /*! \brief 01.0093.F:B SCT LP Fast Retrain Count [4:0]
                        AQ_Pma10GBaseT_FastRetrainStatusAndControl_EUR.u0.bits_0.lpFastRetrainCount

                        Default = 0x00

                        Counts the number of fast retrains requested by the link partner
                        

                 <B>Notes:</B>
                        Saturating clear on read counter.  */
      unsigned int   lpFastRetrainCount : 5;    /* 01.0093.F:B  SCT      Default = 0x00 */
                     /* Counts the number of fast retrains requested by the link partner
                          */
                    /*! \brief 01.0093.A:6 SCT LD Fast Retrain Count [4:0]
                        AQ_Pma10GBaseT_FastRetrainStatusAndControl_EUR.u0.bits_0.ldFastRetrainCount

                        Default = 0x00

                        Counts the number of fast retrains requested by the local device
                        

                 <B>Notes:</B>
                        Saturating clear on read counter.  */
      unsigned int   ldFastRetrainCount : 5;    /* 01.0093.A:6  SCT      Default = 0x00 */
                     /* Counts the number of fast retrains requested by the local device
                          */
                    /*! \brief 01.0093.5 R/WPD Reserved_93
                        AQ_Pma10GBaseT_FastRetrainStatusAndControl_EUR.u0.bits_0.reserved93

                        Provisionable Default = 0x0

                        Reserved bit 5
  */
      unsigned int   reserved93 : 1;    /* 01.0093.5  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved bit 5  */
                    /*! \brief 01.0093.4 RO Fast Retrain Ability
                        AQ_Pma10GBaseT_FastRetrainStatusAndControl_EUR.u0.bits_0.fastRetrainAbility

                        

                        1 = Fast retrain capability is supported
                        0 = Fast retrain capability is not supported
  */
      unsigned int   fastRetrainAbility : 1;    /* 01.0093.4  RO       */
                     /* 1 = Fast retrain capability is supported
                        0 = Fast retrain capability is not supported  */
                    /*! \brief 01.0093.3 RO Fast Retrain Negotiated
                        AQ_Pma10GBaseT_FastRetrainStatusAndControl_EUR.u0.bits_0.fastRetrainNegotiated

                        

                        1 = Fast retrain capability was negotiated
                        0 = Fast retrain capability was not negotiated
  */
      unsigned int   fastRetrainNegotiated : 1;    /* 01.0093.3  RO       */
                     /* 1 = Fast retrain capability was negotiated
                        0 = Fast retrain capability was not negotiated  */
                    /*! \brief 01.0093.2:1 R/W Fast Retrain Signal Type [1:0]
                        AQ_Pma10GBaseT_FastRetrainStatusAndControl_EUR.u0.bits_0.fastRetrainSignalType

                        Default = 0x0

                        11 = Reserved
                        10 = PHY signals Link Interruption during fast retrain
                        01 = PHY signals Local Fault during fast retrain
                        00 = PHY signals IDLE during fast retrain
  */
      unsigned int   fastRetrainSignalType : 2;    /* 01.0093.2:1  R/W      Default = 0x0 */
                     /* 11 = Reserved
                        10 = PHY signals Link Interruption during fast retrain
                        01 = PHY signals Local Fault during fast retrain
                        00 = PHY signals IDLE during fast retrain  */
                    /*! \brief 01.0093.0 R/W Fast Retrain Enable
                        AQ_Pma10GBaseT_FastRetrainStatusAndControl_EUR.u0.bits_0.fastRetrainEnable

                        Default = 0x0

                        1 = Fast retrain capability is enabled
                        0 = Fast retrain capability is disabled
  */
      unsigned int   fastRetrainEnable : 1;    /* 01.0093.0  R/W      Default = 0x0 */
                     /* 1 = Fast retrain capability is enabled
                        0 = Fast retrain capability is disabled  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pma10GBaseT_FastRetrainStatusAndControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PMA Capability: 01.0708 */
/*                  TimeSync PMA Capability: 01.0708 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PMA Capability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 01.0708.1 RO TimeSync Transmit Path Data Delay
                        AQ_TimesyncPmaCapability_EUR.u0.bits_0.timesyncTransmitPathDataDelay

                        

                        1 = PMA provides information on transmit path data delay in registers 1.1801 through 1.1804
                        0 = PMA does not provide information on transmit path data delay
  */
      unsigned int   timesyncTransmitPathDataDelay : 1;    /* 01.0708.1  RO       */
                     /* 1 = PMA provides information on transmit path data delay in registers 1.1801 through 1.1804
                        0 = PMA does not provide information on transmit path data delay  */
                    /*! \brief 01.0708.0 RO TimeSync Receive Path Data Delay
                        AQ_TimesyncPmaCapability_EUR.u0.bits_0.timesyncReceivePathDataDelay

                        

                        1 = PMA provides information on receive path data delay in registers 1.1805 through 1.1808
                        0 = PMA does not provide information on receive path data delay
  */
      unsigned int   timesyncReceivePathDataDelay : 1;    /* 01.0708.0  RO       */
                     /* 1 = PMA provides information on receive path data delay in registers 1.1805 through 1.1808
                        0 = PMA does not provide information on receive path data delay  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_TimesyncPmaCapability_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PMA Transmit Path Data Delay: 01.0709 */
/*                  TimeSync PMA Transmit Path Data Delay: 01.0709 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PMA Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 01.0709.F:0 RO Maximum PMA Transmit Path Data Delay LSW [F:0]
                        AQ_TimesyncPmaTransmitPathDataDelay_EUR.u0.bits_0.maximumPmaTransmitPathDataDelayLSW

                        

                        LSW of maximum PMA transmit delay in nanoseconds
  */
      unsigned int   maximumPmaTransmitPathDataDelayLSW : 16;    /* 01.0709.F:0  RO       */
                     /* LSW of maximum PMA transmit delay in nanoseconds  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of TimeSync PMA Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 01.070A.F:0 RO Maximum PMA Transmit Path Data Delay MSW [F:0]
                        AQ_TimesyncPmaTransmitPathDataDelay_EUR.u1.bits_1.maximumPmaTransmitPathDataDelayMSW

                        

                        MSW of maximum PMA transmit delay in nanoseconds
  */
      unsigned int   maximumPmaTransmitPathDataDelayMSW : 16;    /* 01.070A.F:0  RO       */
                     /* MSW of maximum PMA transmit delay in nanoseconds  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of TimeSync PMA Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 01.070B.F:0 RO Minimum PMA Transmit Path Data Delay LSW [F:0]
                        AQ_TimesyncPmaTransmitPathDataDelay_EUR.u2.bits_2.minimumPmaTransmitPathDataDelayLSW

                        

                        LSW of minimum PMA transmit delay in nanoseconds
  */
      unsigned int   minimumPmaTransmitPathDataDelayLSW : 16;    /* 01.070B.F:0  RO       */
                     /* LSW of minimum PMA transmit delay in nanoseconds  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of TimeSync PMA Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 01.070C.F:0 RO Minimum PMA Transmit Path Data Delay MSW [F:0]
                        AQ_TimesyncPmaTransmitPathDataDelay_EUR.u3.bits_3.minimumPmaTransmitPathDataDelayMSW

                        

                        MSW of minimum PMA transmit delay in nanoseconds
  */
      unsigned int   minimumPmaTransmitPathDataDelayMSW : 16;    /* 01.070C.F:0  RO       */
                     /* MSW of minimum PMA transmit delay in nanoseconds  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_TimesyncPmaTransmitPathDataDelay_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PMA Receive Path Data Delay: 01.070D */
/*                  TimeSync PMA Receive Path Data Delay: 01.070D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PMA Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 01.070D.F:0 RO Maximum PMA Receive Path Data Delay LSW [F:0]
                        AQ_TimesyncPmaReceivePathDataDelay_EUR.u0.bits_0.maximumPmaReceivePathDataDelayLSW

                        

                        LSW of maximum PMA receive delay in nanoseconds
  */
      unsigned int   maximumPmaReceivePathDataDelayLSW : 16;    /* 01.070D.F:0  RO       */
                     /* LSW of maximum PMA receive delay in nanoseconds  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of TimeSync PMA Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 01.070E.F:0 RO Maximum PMA Receive Path Data Delay MSW [F:0]
                        AQ_TimesyncPmaReceivePathDataDelay_EUR.u1.bits_1.maximumPmaReceivePathDataDelayMSW

                        

                        MSW of maximum PMA receive delay in nanoseconds
  */
      unsigned int   maximumPmaReceivePathDataDelayMSW : 16;    /* 01.070E.F:0  RO       */
                     /* MSW of maximum PMA receive delay in nanoseconds  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of TimeSync PMA Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 01.070F.F:0 RO Minimum PMA Receive Path Data Delay LSW [F:0]
                        AQ_TimesyncPmaReceivePathDataDelay_EUR.u2.bits_2.minimumPmaReceivePathDataDelayLSW

                        

                        LSW of minimum PMA receive delay in nanoseconds
  */
      unsigned int   minimumPmaReceivePathDataDelayLSW : 16;    /* 01.070F.F:0  RO       */
                     /* LSW of minimum PMA receive delay in nanoseconds  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of TimeSync PMA Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 01.0710.F:0 RO Minimum PMA Receive Path Data Delay MSW [F:0]
                        AQ_TimesyncPmaReceivePathDataDelay_EUR.u3.bits_3.minimumPmaReceivePathDataDelayMSW

                        

                        MSW of minimum PMA receive delay in nanoseconds
  */
      unsigned int   minimumPmaReceivePathDataDelayMSW : 16;    /* 01.0710.F:0  RO       */
                     /* MSW of minimum PMA receive delay in nanoseconds  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_TimesyncPmaReceivePathDataDelay_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Control: 01.8000 */
/*                  XENPAK Control: 01.8000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Control */
  union
  {
    struct
    {
                    /*! \brief 01.8000.F:9 R/W Vendor Specific [6:0]
                        AQ_XenpakControl_EUR.u0.bits_0.vendorSpecific

                        Default = 0x00

                        Reserved
  */
      unsigned int   vendorSpecific : 7;    /* 01.8000.F:9  R/W      Default = 0x00 */
                     /* Reserved  */
      unsigned int   reserved0 : 3;
                    /*! \brief 01.8000.5 R/W Command
                        AQ_XenpakControl_EUR.u0.bits_0.command

                        Default = 0x0

                        1 = Read NVR
                        0 = Write NVR

                 <B>Notes:</B>
                        Writing to this register initiates the command indicated by the value that is written. These commands are used in conjunction with regular MDIO reads and writes to burn the value permanently into the NVR, versus just altering a volatile copy of the register.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   command : 1;    /* 01.8000.5  R/W      Default = 0x0 */
                     /* 1 = Read NVR
                        0 = Write NVR  */
      unsigned int   reserved1 : 1;
                    /*! \brief 01.8000.3:2 RO Command Status [1:0]
                        AQ_XenpakControl_EUR.u0.bits_0.commandStatus

                        

                        [3:2]
                        0x3 = Command failed
                        0x2 = Command in progress
                        0x1 = Command succeeded
                        0x0 = Idle
                        

                 <B>Notes:</B>
                        Status of command. When a command has completed, the read returns either 0x3 or 0x1, depending on the outcome of the command. Subsequent reads return Idle (0x0), until a new command is initiated. This field is RO by the MDIO and is R/W by the uP and will automatically clear to 0x0 when the value is either 0x3 or 0x1 when read by the MDIO.  */
      unsigned int   commandStatus : 2;    /* 01.8000.3:2  RO       */
                     /* [3:2]
                        0x3 = Command failed
                        0x2 = Command in progress
                        0x1 = Command succeeded
                        0x0 = Idle
                          */
                    /*! \brief 01.8000.1:0 R/W Extended Commands [1:0]
                        AQ_XenpakControl_EUR.u0.bits_0.extendedCommands

                        Default = 0x0

                        [1:0]
                        0x3 = Read all NVR contents
                        0x2 = Vendor Specific
                        0x1 = Vendor Specific
                        0x0 = Vendor Specific

                 <B>Notes:</B>
                        If the extended command bits are set to 0x3 when a read command is issued, all of the NVR volatile registers will have their values re-initialized to the default values stored in the NVR. This is similar to a reset.  */
      unsigned int   extendedCommands : 2;    /* 01.8000.1:0  R/W      Default = 0x0 */
                     /* [1:0]
                        0x3 = Read all NVR contents
                        0x2 = Vendor Specific
                        0x1 = Vendor Specific
                        0x0 = Vendor Specific  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Header - XENPAK MSA Version Supported: 01.8007 */
/*                  XENPAK Header - XENPAK MSA Version Supported: 01.8007 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Header - XENPAK MSA Version Supported */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8007.7:0 RO Version [7:0]
                        AQ_XenpakHeader_XenpakMsaVersionSupported_EUR.u0.bits_0.version

                        

                        [7:0] = Version * 10

                 <B>Notes:</B>
                        Version * 10: i.e Maximum version = 25.5.  */
      unsigned int   version : 8;    /* 01.8007.7:0  RO       */
                     /* [7:0] = Version * 10  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakHeader_XenpakMsaVersionSupported_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Header - NVR Size: 01.8008 */
/*                  XENPAK Header - NVR Size: 01.8008 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Header - NVR Size */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8008.7:0 ROS NVR Size MSW [F:8]
                        AQ_XenpakHeader_NvrSize_EUR.u0.bits_0.nvrSizeMSW

                        Default = 0x01

                        [7:0] = Bits [F:8] of NVR size in bytes

                 <B>Notes:</B>
                        256 Bytes synthetic NVR  */
      unsigned int   nvrSizeMSW : 8;    /* 01.8008.7:0  ROS      Default = 0x01 */
                     /* [7:0] = Bits [F:8] of NVR size in bytes  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Header - NVR Size */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8009.7:0 ROS NVR Size LSW [7:0]
                        AQ_XenpakHeader_NvrSize_EUR.u1.bits_1.nvrSizeLSW

                        Default = 0x00

                        [7:0] = Bits [7:0] of NVR size in bytes

                 <B>Notes:</B>
                        256 Bytes synthetic NVR  */
      unsigned int   nvrSizeLSW : 8;    /* 01.8009.7:0  ROS      Default = 0x00 */
                     /* [7:0] = Bits [7:0] of NVR size in bytes  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_XenpakHeader_NvrSize_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Header - Memory Used: 01.800A */
/*                  XENPAK Header - Memory Used: 01.800A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Header - Memory Used */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.800A.7:0 ROS Memory Used MSW [7:0]
                        AQ_XenpakHeader_MemoryUsed_EUR.u0.bits_0.memoryUsedMSW

                        Default = 0x01

                        [7:0] = Bits [F:8] of memory used in bytes
  */
      unsigned int   memoryUsedMSW : 8;    /* 01.800A.7:0  ROS      Default = 0x01 */
                     /* [7:0] = Bits [F:8] of memory used in bytes  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Header - Memory Used */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.800B.7:0 ROS Memory Used LSW [7:0]
                        AQ_XenpakHeader_MemoryUsed_EUR.u1.bits_1.memoryUsedLSW

                        Default = 0x00

                        [7:0] = Bits [7:0] of memory used in bytes
  */
      unsigned int   memoryUsedLSW : 8;    /* 01.800B.7:0  ROS      Default = 0x00 */
                     /* [7:0] = Bits [7:0] of memory used in bytes  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_XenpakHeader_MemoryUsed_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Header - Basic Memory Start Address: 01.800C */
/*                  XENPAK Header - Basic Memory Start Address: 01.800C */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Header - Basic Memory Start Address */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.800C.7:0 ROS Basic Memory Offset [7:0]
                        AQ_XenpakHeader_BasicMemoryStartAddress_EUR.u0.bits_0.basicMemoryOffset

                        Default = 0x0C

                        [7:0] = Basic memory start address

                 <B>Notes:</B>
                        The address where the basic memory starts in the NVR.  */
      unsigned int   basicMemoryOffset : 8;    /* 01.800C.7:0  ROS      Default = 0x0C */
                     /* [7:0] = Basic memory start address  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakHeader_BasicMemoryStartAddress_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Header - Customer Memory Offset: 01.800D */
/*                  XENPAK Header - Customer Memory Offset: 01.800D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Header - Customer Memory Offset */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.800D.7:0 ROS Customer Memory Offset [7:0]
                        AQ_XenpakHeader_CustomerMemoryOffset_EUR.u0.bits_0.customerMemoryOffset

                        Default = 0x7E

                        [7:0] = Customer memory start address

                 <B>Notes:</B>
                        The address where the customer memory starts.  */
      unsigned int   customerMemoryOffset : 8;    /* 01.800D.7:0  ROS      Default = 0x7E */
                     /* [7:0] = Customer memory start address  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakHeader_CustomerMemoryOffset_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Header - Vendor Memory Start Address: 01.800E */
/*                  XENPAK Header - Vendor Memory Start Address: 01.800E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Header - Vendor Memory Start Address */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.800E.7:0 ROS Vendor Memory Offset [7:0]
                        AQ_XenpakHeader_VendorMemoryStartAddress_EUR.u0.bits_0.vendorMemoryOffset

                        Default = 0xAE

                        [7:0] = Vendor memory start address

                 <B>Notes:</B>
                        The address where the vendor memory starts.  */
      unsigned int   vendorMemoryOffset : 8;    /* 01.800E.7:0  ROS      Default = 0xAE */
                     /* [7:0] = Vendor memory start address  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakHeader_VendorMemoryStartAddress_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Header - Extended Vendor Memory Offset: 01.800F */
/*                  XENPAK Header - Extended Vendor Memory Offset: 01.800F */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Header - Extended Vendor Memory Offset */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.800F.7:0 ROS Extended Vendor Offset LSW [7:0]
                        AQ_XenpakHeader_ExtendedVendorMemoryOffset_EUR.u0.bits_0.extendedVendorOffsetLSW

                        Default = 0x07

                        [7:0] = Bits [7:0] of extended vendor memory start address

                 <B>Notes:</B>
                        The LSW of the address where the extended vendor memory starts.  */
      unsigned int   extendedVendorOffsetLSW : 8;    /* 01.800F.7:0  ROS      Default = 0x07 */
                     /* [7:0] = Bits [7:0] of extended vendor memory start address  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Header - Extended Vendor Memory Offset */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8010.7:0 ROS Extended Vendor Offset MSW [7:0]
                        AQ_XenpakHeader_ExtendedVendorMemoryOffset_EUR.u1.bits_1.extendedVendorOffsetMSW

                        Default = 0x01

                        [7:0] = Bits [F:8] of extended vendor memory start address

                 <B>Notes:</B>
                        The MSW of the address where the extended vendor memory starts.  */
      unsigned int   extendedVendorOffsetMSW : 8;    /* 01.8010.7:0  ROS      Default = 0x01 */
                     /* [7:0] = Bits [F:8] of extended vendor memory start address  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_XenpakHeader_ExtendedVendorMemoryOffset_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Reserved 0x11: 01.8011 */
/*                  XENPAK Basic - Reserved 0x11: 01.8011 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Reserved 0x11 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8011.7:0 ROS Basic Reserved 0x11 [7:0]
                        AQ_XenpakBasic_Reserved_0x11_EUR.u0.bits_0.basicReserved_0x11

                        Default = 0x00
  */
      unsigned int   basicReserved_0x11 : 8;    /* 01.8011.7:0  ROS      Default = 0x00 */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_Reserved_0x11_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Transceiver Type: 01.8012 */
/*                  XENPAK Basic - Transceiver Type: 01.8012 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Transceiver Type */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8012.7:0 ROS Transceiver Type [7:0]
                        AQ_XenpakBasic_TransceiverType_EUR.u0.bits_0.transceiverType

                        Default = 0x01

                        [7:0]
                        0x8  0x2 = Reserved
                        0x1 = XENPAK
                        0x0 = Unspecified

                 <B>Notes:</B>
                        All non-power of 2 values are invalid.  */
      unsigned int   transceiverType : 8;    /* 01.8012.7:0  ROS      Default = 0x01 */
                     /* [7:0]
                        0x8  0x2 = Reserved
                        0x1 = XENPAK
                        0x0 = Unspecified  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_TransceiverType_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Connector Type: 01.8013 */
/*                  XENPAK Basic - Connector Type: 01.8013 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Connector Type */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8013.7:0 ROS Connector Type [7:0]
                        AQ_XenpakBasic_ConnectorType_EUR.u0.bits_0.connectorType

                        Default = 0x40

                        [7:0]
                        0x80 = Reserved
                        0x40 = RJ-45
                        0x20 = Pigtail
                        0x10 = FC / PC
                        0x08 = MU
                        0x04 = MT-RJ
                        0x02 = LC
                        0x01 = SC
                        0x00 = Unspecified

                 <B>Notes:</B>
                        The connector type used. Note the power of 2 encoding. All non-power of 2 values are invalid.  */
      unsigned int   connectorType : 8;    /* 01.8013.7:0  ROS      Default = 0x40 */
                     /* [7:0]
                        0x80 = Reserved
                        0x40 = RJ-45
                        0x20 = Pigtail
                        0x10 = FC / PC
                        0x08 = MU
                        0x04 = MT-RJ
                        0x02 = LC
                        0x01 = SC
                        0x00 = Unspecified  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_ConnectorType_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Encoding: 01.8014 */
/*                  XENPAK Basic - Encoding: 01.8014 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Encoding */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8014.7:0 ROS Encoding [7:0]
                        AQ_XenpakBasic_Encoding_EUR.u0.bits_0.encoding

                        Default = 0x04

                        [7:0]
                        0x8 = Reserved
                        0x4 = 128 DSQ
                        0x2 = FEC
                        0x1 = NRZ
                        0x0 = Unspecified

                 <B>Notes:</B>
                        All non-power of 2 values are invalid.  */
      unsigned int   encoding : 8;    /* 01.8014.7:0  ROS      Default = 0x04 */
                     /* [7:0]
                        0x8 = Reserved
                        0x4 = 128 DSQ
                        0x2 = FEC
                        0x1 = NRZ
                        0x0 = Unspecified  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_Encoding_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Bit Rate: 01.8015 */
/*                  XENPAK Basic - Bit Rate: 01.8015 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Bit Rate */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8015.7:0 ROS Bit Rate MSW [F:8]
                        AQ_XenpakBasic_BitRate_EUR.u0.bits_0.bitRateMSW

                        Default = 0x27

                        [7:0] = [7:0] of bit rate in Mb/s

                 <B>Notes:</B>
                        0x2710 = 10,000 Mb/s  */
      unsigned int   bitRateMSW : 8;    /* 01.8015.7:0  ROS      Default = 0x27 */
                     /* [7:0] = [7:0] of bit rate in Mb/s  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Bit Rate */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8016.7:0 ROS Bit Rate LSW [7:0]
                        AQ_XenpakBasic_BitRate_EUR.u1.bits_1.bitRateLSW

                        Default = 0x10

                        [7:0] = [F:8] of bit rate in Mb/s

                 <B>Notes:</B>
                        0x2710 = 10,000 Mb/s  */
      unsigned int   bitRateLSW : 8;    /* 01.8016.7:0  ROS      Default = 0x10 */
                     /* [7:0] = [F:8] of bit rate in Mb/s  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_XenpakBasic_BitRate_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Protocol: 01.8017 */
/*                  XENPAK Basic - Protocol: 01.8017 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Protocol */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8017.7:0 ROS Protocol [7:0]
                        AQ_XenpakBasic_Protocol_EUR.u0.bits_0.protocol

                        Default = 0x01

                        [7:0]
                        0x80  0x20 = Reserved
                        0x10 = SONET / SDH
                        0x08 = LSS
                        0x04 = WIS
                        0x02 = 10GFC
                        0x01 = 10 GbE
                        0x0 = Unspecified

                 <B>Notes:</B>
                        All non-power of 2 values are invalid.  */
      unsigned int   protocol : 8;    /* 01.8017.7:0  ROS      Default = 0x01 */
                     /* [7:0]
                        0x80  0x20 = Reserved
                        0x10 = SONET / SDH
                        0x08 = LSS
                        0x04 = WIS
                        0x02 = 10GFC
                        0x01 = 10 GbE
                        0x0 = Unspecified  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_Protocol_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Standards Compliance Codes: 01.8018 */
/*                  XENPAK Basic - Standards Compliance Codes: 01.8018 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Standards Compliance Codes */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8018.7:0 ROS Standard Code [7:0]
                        AQ_XenpakBasic_StandardsComplianceCodes_EUR.u0.bits_0.standardCode

                        Default = 0x80

                        [7:0]
                        0x80 = 10GBASE-T
                        0x40 = 10GBASE-EW
                        0x20 = 10GBASE-LW
                        0x10 = 10GBASE-SW
                        0x08 = 10GBASE-LX4
                        0x04 = 10GBASE-ER
                        0x02 = 10GBASE-LR
                        0x01 = 10GBASE-SR
                        0x0 = Unspecified

                 <B>Notes:</B>
                        All non-power of 2 values are invalid.  */
      unsigned int   standardCode : 8;    /* 01.8018.7:0  ROS      Default = 0x80 */
                     /* [7:0]
                        0x80 = 10GBASE-T
                        0x40 = 10GBASE-EW
                        0x20 = 10GBASE-LW
                        0x10 = 10GBASE-SW
                        0x08 = 10GBASE-LX4
                        0x04 = 10GBASE-ER
                        0x02 = 10GBASE-LR
                        0x01 = 10GBASE-SR
                        0x0 = Unspecified  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_StandardsComplianceCodes_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Reserved 0x19: 01.8019 */
/*                  XENPAK Basic - Reserved 0x19: 01.8019 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8019.7:0 ROS Basic Reserved 0x19 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u0.bits_0.basicReserved_0x19

                        Default = 0x00
  */
      unsigned int   basicReserved_0x19 : 8;    /* 01.8019.7:0  ROS      Default = 0x00 */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.801A.7:0 ROS Basic Reserved 0x1A [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u1.bits_1.basicReserved_0x1a

                        Default = 0x00
  */
      unsigned int   basicReserved_0x1a : 8;    /* 01.801A.7:0  ROS      Default = 0x00 */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.801B.7:0 ROS Basic Reserved 0x1B [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u2.bits_2.basicReserved_0x1b

                        Default = 0x00
  */
      unsigned int   basicReserved_0x1b : 8;    /* 01.801B.7:0  ROS      Default = 0x00 */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.801C.7:0 ROS Basic Reserved 0x1C [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u3.bits_3.basicReserved_0x1c

                        Default = 0x00
  */
      unsigned int   basicReserved_0x1c : 8;    /* 01.801C.7:0  ROS      Default = 0x00 */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.801D.7:0 ROS Basic Reserved 0x1D [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u4.bits_4.basicReserved_0x1d

                        Default = 0x00
  */
      unsigned int   basicReserved_0x1d : 8;    /* 01.801D.7:0  ROS      Default = 0x00 */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.801E.7:0 ROS Basic Reserved 0x1E [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u5.bits_5.basicReserved_0x1e

                        Default = 0x00
  */
      unsigned int   basicReserved_0x1e : 8;    /* 01.801E.7:0  ROS      Default = 0x00 */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.801F.7:0 ROS Basic Reserved 0x1F [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u6.bits_6.basicReserved_0x1f

                        Default = 0x00
  */
      unsigned int   basicReserved_0x1f : 8;    /* 01.801F.7:0  ROS      Default = 0x00 */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8020.7:0 ROS Basic Reserved 0x20 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u7.bits_7.basicReserved_0x20

                        Default = 0x00
  */
      unsigned int   basicReserved_0x20 : 8;    /* 01.8020.7:0  ROS      Default = 0x00 */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8021.7:0 ROS Basic Reserved 0x21 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u8.bits_8.basicReserved_0x21

                        Default = 0x00
  */
      unsigned int   basicReserved_0x21 : 8;    /* 01.8021.7:0  ROS      Default = 0x00 */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8022.7:0 ROS Basic Reserved 0x22 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u9.bits_9.basicReserved_0x22

                        Default = 0x00
  */
      unsigned int   basicReserved_0x22 : 8;    /* 01.8022.7:0  ROS      Default = 0x00 */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8023.7:0 ROS Basic Reserved 0x23 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u10.bits_10.basicReserved_0x23

                        Default = 0x00
  */
      unsigned int   basicReserved_0x23 : 8;    /* 01.8023.7:0  ROS      Default = 0x00 */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8024.7:0 ROS Basic Reserved 0x24 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u11.bits_11.basicReserved_0x24

                        Default = 0x00
  */
      unsigned int   basicReserved_0x24 : 8;    /* 01.8024.7:0  ROS      Default = 0x00 */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8025.7:0 ROS Basic Reserved 0x25 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u12.bits_12.basicReserved_0x25

                        Default = 0x00
  */
      unsigned int   basicReserved_0x25 : 8;    /* 01.8025.7:0  ROS      Default = 0x00 */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8026.7:0 ROS Basic Reserved 0x26 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u13.bits_13.basicReserved_0x26

                        Default = 0x00
  */
      unsigned int   basicReserved_0x26 : 8;    /* 01.8026.7:0  ROS      Default = 0x00 */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8027.7:0 ROS Basic Reserved 0x27 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u14.bits_14.basicReserved_0x27

                        Default = 0x00
  */
      unsigned int   basicReserved_0x27 : 8;    /* 01.8027.7:0  ROS      Default = 0x00 */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8028.7:0 ROS Basic Reserved 0x28 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u15.bits_15.basicReserved_0x28

                        Default = 0x00
  */
      unsigned int   basicReserved_0x28 : 8;    /* 01.8028.7:0  ROS      Default = 0x00 */
    } bits_15;
    uint16_t word_15;
  } u15;
  /*! \brief Union for bit and word level access of word 16 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8029.7:0 ROS Basic Reserved 0x29 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u16.bits_16.basicReserved_0x29

                        Default = 0x00
  */
      unsigned int   basicReserved_0x29 : 8;    /* 01.8029.7:0  ROS      Default = 0x00 */
    } bits_16;
    uint16_t word_16;
  } u16;
  /*! \brief Union for bit and word level access of word 17 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.802A.7:0 ROS Basic Reserved 0x2A [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u17.bits_17.basicReserved_0x2a

                        Default = 0x00
  */
      unsigned int   basicReserved_0x2a : 8;    /* 01.802A.7:0  ROS      Default = 0x00 */
    } bits_17;
    uint16_t word_17;
  } u17;
  /*! \brief Union for bit and word level access of word 18 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.802B.7:0 ROS Basic Reserved 0x2B [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u18.bits_18.basicReserved_0x2b

                        Default = 0x00
  */
      unsigned int   basicReserved_0x2b : 8;    /* 01.802B.7:0  ROS      Default = 0x00 */
    } bits_18;
    uint16_t word_18;
  } u18;
  /*! \brief Union for bit and word level access of word 19 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.802C.7:0 ROS Basic Reserved 0x2C [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u19.bits_19.basicReserved_0x2c

                        Default = 0x00
  */
      unsigned int   basicReserved_0x2c : 8;    /* 01.802C.7:0  ROS      Default = 0x00 */
    } bits_19;
    uint16_t word_19;
  } u19;
  /*! \brief Union for bit and word level access of word 20 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.802D.7:0 ROS Basic Reserved 0x2D [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u20.bits_20.basicReserved_0x2d

                        Default = 0x00
  */
      unsigned int   basicReserved_0x2d : 8;    /* 01.802D.7:0  ROS      Default = 0x00 */
    } bits_20;
    uint16_t word_20;
  } u20;
  /*! \brief Union for bit and word level access of word 21 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.802E.7:0 ROS Basic Reserved 0x2E [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u21.bits_21.basicReserved_0x2e

                        Default = 0x00
  */
      unsigned int   basicReserved_0x2e : 8;    /* 01.802E.7:0  ROS      Default = 0x00 */
    } bits_21;
    uint16_t word_21;
  } u21;
  /*! \brief Union for bit and word level access of word 22 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.802F.7:0 ROS Basic Reserved 0x2F [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u22.bits_22.basicReserved_0x2f

                        Default = 0x00
  */
      unsigned int   basicReserved_0x2f : 8;    /* 01.802F.7:0  ROS      Default = 0x00 */
    } bits_22;
    uint16_t word_22;
  } u22;
  /*! \brief Union for bit and word level access of word 23 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8030.7:0 ROS Basic Reserved 0x30 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u23.bits_23.basicReserved_0x30

                        Default = 0x00
  */
      unsigned int   basicReserved_0x30 : 8;    /* 01.8030.7:0  ROS      Default = 0x00 */
    } bits_23;
    uint16_t word_23;
  } u23;
  /*! \brief Union for bit and word level access of word 24 of XENPAK Basic - Reserved 0x19 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8031.7:0 ROS Basic Reserved 0x31 [7:0]
                        AQ_XenpakBasic_Reserved_0x19_EUR.u24.bits_24.basicReserved_0x31

                        Default = 0x00
  */
      unsigned int   basicReserved_0x31 : 8;    /* 01.8031.7:0  ROS      Default = 0x00 */
    } bits_24;
    uint16_t word_24;
  } u24;
} AQ_XenpakBasic_Reserved_0x19_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Package Identifier: 01.8032 */
/*                  XENPAK Basic - Package Identifier: 01.8032 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Package Identifier */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8032.7:0 RO Package ID 1 [1F:18]
                        AQ_XenpakBasic_PackageIdentifier_EUR.u0.bits_0.packageID_1

                        

                        [7:0] = [1F:18] of Package ID

                 <B>Notes:</B>
                        Clone of Registers 1.E:F  */
      unsigned int   packageID_1 : 8;    /* 01.8032.7:0  RO       */
                     /* [7:0] = [1F:18] of Package ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Package Identifier */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8033.7:0 RO Package ID 2 [17:10]
                        AQ_XenpakBasic_PackageIdentifier_EUR.u1.bits_1.packageID_2

                        

                        [7:0] = [17:10] of Package ID

                 <B>Notes:</B>
                        Clone of Registers 1.E:F  */
      unsigned int   packageID_2 : 8;    /* 01.8033.7:0  RO       */
                     /* [7:0] = [17:10] of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Basic - Package Identifier */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8034.7:0 RO Package ID 3 [F:8]
                        AQ_XenpakBasic_PackageIdentifier_EUR.u2.bits_2.packageID_3

                        

                        [7:0] = [F:8] of Package ID

                 <B>Notes:</B>
                        Clone of Registers 1.E:F  */
      unsigned int   packageID_3 : 8;    /* 01.8034.7:0  RO       */
                     /* [7:0] = [F:8] of Package ID  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Basic - Package Identifier */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8035.7:0 RO Package ID 4 [7:0]
                        AQ_XenpakBasic_PackageIdentifier_EUR.u3.bits_3.packageID_4

                        

                        [7:0] = [7:0] of Package ID

                 <B>Notes:</B>
                        Clone of Registers 1.E:F  */
      unsigned int   packageID_4 : 8;    /* 01.8035.7:0  RO       */
                     /* [7:0] = [7:0] of Package ID  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_XenpakBasic_PackageIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Vendor Identifier: 01.8036 */
/*                  XENPAK Basic - Vendor Identifier: 01.8036 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Vendor Identifier */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8036.7:0 RO Vendor ID 1 [1F:18]
                        AQ_XenpakBasic_VendorIdentifier_EUR.u0.bits_0.vendorID_1

                        

                        [7:0] = [1F:18] of Vendor ID
  */
      unsigned int   vendorID_1 : 8;    /* 01.8036.7:0  RO       */
                     /* [7:0] = [1F:18] of Vendor ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Vendor Identifier */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8037.7:0 RO Vendor ID 2 [17:10]
                        AQ_XenpakBasic_VendorIdentifier_EUR.u1.bits_1.vendorID_2

                        

                        [7:0] = [17:10] of Package ID
  */
      unsigned int   vendorID_2 : 8;    /* 01.8037.7:0  RO       */
                     /* [7:0] = [17:10] of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Basic - Vendor Identifier */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8038.7:0 RO Vendor ID 3 [F:8]
                        AQ_XenpakBasic_VendorIdentifier_EUR.u2.bits_2.vendorID_3

                        

                        [7:0] = [F:8] of Package ID
  */
      unsigned int   vendorID_3 : 8;    /* 01.8038.7:0  RO       */
                     /* [7:0] = [F:8] of Package ID  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Basic - Vendor Identifier */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8039.7:0 RO Vendor ID 4 [7:0]
                        AQ_XenpakBasic_VendorIdentifier_EUR.u3.bits_3.vendorID_4

                        

                        [7:0] = [7:0] of Package ID
  */
      unsigned int   vendorID_4 : 8;    /* 01.8039.7:0  RO       */
                     /* [7:0] = [7:0] of Package ID  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_XenpakBasic_VendorIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Vendor Name: 01.803A */
/*                  XENPAK Basic - Vendor Name: 01.803A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.803A.7:0 RO Vendor Name 1 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u0.bits_0.vendorName_1

                        

                        [7:0] = 1st Character
  */
      unsigned int   vendorName_1 : 8;    /* 01.803A.7:0  RO       */
                     /* [7:0] = 1st Character  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.803B.7:0 RO Vendor Name 2 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u1.bits_1.vendorName_2

                        

                        [7:0] = 2nd Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_2 : 8;    /* 01.803B.7:0  RO       */
                     /* [7:0] = 2nd Character  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.803C.7:0 RO Vendor Name 3 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u2.bits_2.vendorName_3

                        

                        [7:0] = 3rd Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_3 : 8;    /* 01.803C.7:0  RO       */
                     /* [7:0] = 3rd Character  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.803D.7:0 RO Vendor Name 4 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u3.bits_3.vendorName_4

                        

                        [7:0] = 4th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_4 : 8;    /* 01.803D.7:0  RO       */
                     /* [7:0] = 4th Character  */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.803E.7:0 RO Vendor Name 5 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u4.bits_4.vendorName_5

                        

                        [7:0] = 5th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_5 : 8;    /* 01.803E.7:0  RO       */
                     /* [7:0] = 5th Character  */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.803F.7:0 RO Vendor Name 6 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u5.bits_5.vendorName_6

                        

                        [7:0] = 6th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_6 : 8;    /* 01.803F.7:0  RO       */
                     /* [7:0] = 6th Character  */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8040.7:0 RO Vendor Name 7 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u6.bits_6.vendorName_7

                        

                        [7:0] = 7th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_7 : 8;    /* 01.8040.7:0  RO       */
                     /* [7:0] = 7th Character  */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8041.7:0 RO Vendor Name 8 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u7.bits_7.vendorName_8

                        

                        [7:0] = 8th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_8 : 8;    /* 01.8041.7:0  RO       */
                     /* [7:0] = 8th Character  */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8042.7:0 RO Vendor Name 9 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u8.bits_8.vendorName_9

                        

                        [7:0] = 9th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_9 : 8;    /* 01.8042.7:0  RO       */
                     /* [7:0] = 9th Character  */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8043.7:0 RO Vendor Name 10 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u9.bits_9.vendorName_10

                        

                        [7:0] = 10th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_10 : 8;    /* 01.8043.7:0  RO       */
                     /* [7:0] = 10th Character  */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8044.7:0 RO Vendor Name 11 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u10.bits_10.vendorName_11

                        

                        [7:0] = 11th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_11 : 8;    /* 01.8044.7:0  RO       */
                     /* [7:0] = 11th Character  */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8045.7:0 RO Vendor Name 12 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u11.bits_11.vendorName_12

                        

                        [7:0] = 12th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_12 : 8;    /* 01.8045.7:0  RO       */
                     /* [7:0] = 12th Character  */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8046.7:0 RO Vendor Name 13 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u12.bits_12.vendorName_13

                        

                        [7:0] = 13th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_13 : 8;    /* 01.8046.7:0  RO       */
                     /* [7:0] = 13th Character  */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8047.7:0 RO Vendor Name 14 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u13.bits_13.vendorName_14

                        

                        [7:0] = 14th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_14 : 8;    /* 01.8047.7:0  RO       */
                     /* [7:0] = 14th Character  */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8048.7:0 RO Vendor Name 15 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u14.bits_14.vendorName_15

                        

                        [7:0] = 15th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_15 : 8;    /* 01.8048.7:0  RO       */
                     /* [7:0] = 15th Character  */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of XENPAK Basic - Vendor Name */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8049.7:0 RO Vendor Name 16 [7:0]
                        AQ_XenpakBasic_VendorName_EUR.u15.bits_15.vendorName_16

                        

                        [7:0] = 16th Character

                 <B>Notes:</B>
                        Vendor name in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorName_16 : 8;    /* 01.8049.7:0  RO       */
                     /* [7:0] = 16th Character  */
    } bits_15;
    uint16_t word_15;
  } u15;
} AQ_XenpakBasic_VendorName_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Vendor Part Number: 01.804A */
/*                  XENPAK Basic - Vendor Part Number: 01.804A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.804A.7:0 RO Vendor PN 1 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u0.bits_0.vendorPN_1

                        

                        [7:0] = 1st Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_1 : 8;    /* 01.804A.7:0  RO       */
                     /* [7:0] = 1st Character  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.804B.7:0 RO Vendor PN 2 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u1.bits_1.vendorPN_2

                        

                        [7:0] = 2nd Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_2 : 8;    /* 01.804B.7:0  RO       */
                     /* [7:0] = 2nd Character  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.804C.7:0 RO Vendor PN 3 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u2.bits_2.vendorPN_3

                        

                        [7:0] = 3rd Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_3 : 8;    /* 01.804C.7:0  RO       */
                     /* [7:0] = 3rd Character  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.804D.7:0 RO Vendor PN 4 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u3.bits_3.vendorPN_4

                        

                        [7:0] = 4th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_4 : 8;    /* 01.804D.7:0  RO       */
                     /* [7:0] = 4th Character  */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.804E.7:0 RO Vendor PN 5 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u4.bits_4.vendorPN_5

                        

                        [7:0] = 5th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_5 : 8;    /* 01.804E.7:0  RO       */
                     /* [7:0] = 5th Character  */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.804F.7:0 RO Vendor PN 6 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u5.bits_5.vendorPN_6

                        

                        [7:0] = 6th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_6 : 8;    /* 01.804F.7:0  RO       */
                     /* [7:0] = 6th Character  */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8050.7:0 RO Vendor PN 7 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u6.bits_6.vendorPN_7

                        

                        [7:0] = 7th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_7 : 8;    /* 01.8050.7:0  RO       */
                     /* [7:0] = 7th Character  */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8051.7:0 RO Vendor PN 8 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u7.bits_7.vendorPN_8

                        

                        [7:0] = 8th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_8 : 8;    /* 01.8051.7:0  RO       */
                     /* [7:0] = 8th Character  */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8052.7:0 RO Vendor PN 9 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u8.bits_8.vendorPN_9

                        

                        [7:0] = 9th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_9 : 8;    /* 01.8052.7:0  RO       */
                     /* [7:0] = 9th Character  */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8053.7:0 RO Vendor PN 10 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u9.bits_9.vendorPN_10

                        

                        [7:0] = 10th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_10 : 8;    /* 01.8053.7:0  RO       */
                     /* [7:0] = 10th Character  */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8054.7:0 RO Vendor PN 11 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u10.bits_10.vendorPN_11

                        

                        [7:0] = 11th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_11 : 8;    /* 01.8054.7:0  RO       */
                     /* [7:0] = 11th Character  */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8055.7:0 RO Vendor PN 12 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u11.bits_11.vendorPN_12

                        

                        [7:0] = 12th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_12 : 8;    /* 01.8055.7:0  RO       */
                     /* [7:0] = 12th Character  */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8056.7:0 RO Vendor PN 13 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u12.bits_12.vendorPN_13

                        

                        [7:0] = 13th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_13 : 8;    /* 01.8056.7:0  RO       */
                     /* [7:0] = 13th Character  */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8057.7:0 RO Vendor PN 14 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u13.bits_13.vendorPN_14

                        

                        [7:0] = 14th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_14 : 8;    /* 01.8057.7:0  RO       */
                     /* [7:0] = 14th Character  */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8058.7:0 RO Vendor PN 15 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u14.bits_14.vendorPN_15

                        

                        [7:0] = 15th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_15 : 8;    /* 01.8058.7:0  RO       */
                     /* [7:0] = 15th Character  */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of XENPAK Basic - Vendor Part Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8059.7:0 RO Vendor PN 16 [7:0]
                        AQ_XenpakBasic_VendorPartNumber_EUR.u15.bits_15.vendorPN_16

                        

                        [7:0] = 16th Character

                 <B>Notes:</B>
                        Vendor part number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPN_16 : 8;    /* 01.8059.7:0  RO       */
                     /* [7:0] = 16th Character  */
    } bits_15;
    uint16_t word_15;
  } u15;
} AQ_XenpakBasic_VendorPartNumber_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Vendor Part Revision Number: 01.805A */
/*                  XENPAK Basic - Vendor Part Revision Number: 01.805A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Vendor Part Revision Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.805A.7:0 RO Vendor Part RN 1 [7:0]
                        AQ_XenpakBasic_VendorPartRevisionNumber_EUR.u0.bits_0.vendorPartRN_1

                        

                        [7:0] = 1st Character

                 <B>Notes:</B>
                        Vendor part revision number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPartRN_1 : 8;    /* 01.805A.7:0  RO       */
                     /* [7:0] = 1st Character  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Vendor Part Revision Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.805B.7:0 RO Vendor Part RN 2 [7:0]
                        AQ_XenpakBasic_VendorPartRevisionNumber_EUR.u1.bits_1.vendorPartRN_2

                        

                        [7:0] = 2nd Character

                 <B>Notes:</B>
                        Vendor part revision number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorPartRN_2 : 8;    /* 01.805B.7:0  RO       */
                     /* [7:0] = 2nd Character  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_XenpakBasic_VendorPartRevisionNumber_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Vendor Serial Number: 01.805C */
/*                  XENPAK Basic - Vendor Serial Number: 01.805C */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.805C.7:0 RO Vendor SN 1 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u0.bits_0.vendorSN_1

                        

                        [7:0] = 1st Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_1 : 8;    /* 01.805C.7:0  RO       */
                     /* [7:0] = 1st Character  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.805D.7:0 RO Vendor SN 2 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u1.bits_1.vendorSN_2

                        

                        [7:0] = 2nd Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_2 : 8;    /* 01.805D.7:0  RO       */
                     /* [7:0] = 2nd Character  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.805E.7:0 RO Vendor SN 3 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u2.bits_2.vendorSN_3

                        

                        [7:0] = 3rd Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_3 : 8;    /* 01.805E.7:0  RO       */
                     /* [7:0] = 3rd Character  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.805F.7:0 RO Vendor SN 4 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u3.bits_3.vendorSN_4

                        

                        [7:0] = 4th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_4 : 8;    /* 01.805F.7:0  RO       */
                     /* [7:0] = 4th Character  */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8060.7:0 RO Vendor SN 5 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u4.bits_4.vendorSN_5

                        

                        [7:0] = 5th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_5 : 8;    /* 01.8060.7:0  RO       */
                     /* [7:0] = 5th Character  */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8061.7:0 RO Vendor SN 6 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u5.bits_5.vendorSN_6

                        

                        [7:0] = 6th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_6 : 8;    /* 01.8061.7:0  RO       */
                     /* [7:0] = 6th Character  */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8062.7:0 RO Vendor SN 7 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u6.bits_6.vendorSN_7

                        

                        [7:0] = 7th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_7 : 8;    /* 01.8062.7:0  RO       */
                     /* [7:0] = 7th Character  */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8063.7:0 RO Vendor SN 8 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u7.bits_7.vendorSN_8

                        

                        [7:0] = 8th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_8 : 8;    /* 01.8063.7:0  RO       */
                     /* [7:0] = 8th Character  */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8064.7:0 RO Vendor SN 9 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u8.bits_8.vendorSN_9

                        

                        [7:0] = 9th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_9 : 8;    /* 01.8064.7:0  RO       */
                     /* [7:0] = 9th Character  */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8065.7:0 RO Vendor SN 10 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u9.bits_9.vendorSN_10

                        

                        [7:0] = 10th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_10 : 8;    /* 01.8065.7:0  RO       */
                     /* [7:0] = 10th Character  */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8066.7:0 RO Vendor SN 11 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u10.bits_10.vendorSN_11

                        

                        [7:0] = 11th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_11 : 8;    /* 01.8066.7:0  RO       */
                     /* [7:0] = 11th Character  */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8067.7:0 RO Vendor SN 12 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u11.bits_11.vendorSN_12

                        

                        [7:0] = 12th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_12 : 8;    /* 01.8067.7:0  RO       */
                     /* [7:0] = 12th Character  */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8068.7:0 RO Vendor SN 13 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u12.bits_12.vendorSN_13

                        

                        [7:0] = 13th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_13 : 8;    /* 01.8068.7:0  RO       */
                     /* [7:0] = 13th Character  */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8069.7:0 RO Vendor SN 14 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u13.bits_13.vendorSN_14

                        

                        [7:0] = 14th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_14 : 8;    /* 01.8069.7:0  RO       */
                     /* [7:0] = 14th Character  */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.806A.7:0 RO Vendor SN 15 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u14.bits_14.vendorSN_15

                        

                        [7:0] = 15th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_15 : 8;    /* 01.806A.7:0  RO       */
                     /* [7:0] = 15th Character  */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of XENPAK Basic - Vendor Serial Number */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.806B.7:0 RO Vendor SN 16 [7:0]
                        AQ_XenpakBasic_VendorSerialNumber_EUR.u15.bits_15.vendorSN_16

                        

                        [7:0] = 16th Character

                 <B>Notes:</B>
                        Vendor serial number in ASCII, left aligned, and zero padded on the right.  */
      unsigned int   vendorSN_16 : 8;    /* 01.806B.7:0  RO       */
                     /* [7:0] = 16th Character  */
    } bits_15;
    uint16_t word_15;
  } u15;
} AQ_XenpakBasic_VendorSerialNumber_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Vendor Date Code: 01.806C */
/*                  XENPAK Basic - Vendor Date Code: 01.806C */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.806C.7:0 RO Year 1 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u0.bits_0.year_1

                        

                        [7:0] = 1st character of year

                 <B>Notes:</B>
                        ASCII 1000's character  */
      unsigned int   year_1 : 8;    /* 01.806C.7:0  RO       */
                     /* [7:0] = 1st character of year  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.806D.7:0 RO Year 2 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u1.bits_1.year_2

                        

                        [7:0] = 2nd character of year

                 <B>Notes:</B>
                        ASCII 100's character  */
      unsigned int   year_2 : 8;    /* 01.806D.7:0  RO       */
                     /* [7:0] = 2nd character of year  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.806E.7:0 RO Year 3 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u2.bits_2.year_3

                        

                        [7:0] = 3rd character of year

                 <B>Notes:</B>
                        ASCII 10's character  */
      unsigned int   year_3 : 8;    /* 01.806E.7:0  RO       */
                     /* [7:0] = 3rd character of year  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.806F.7:0 RO Year 4 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u3.bits_3.year_4

                        

                        [7:0] = 4th character of year

                 <B>Notes:</B>
                        ASCII 1's character  */
      unsigned int   year_4 : 8;    /* 01.806F.7:0  RO       */
                     /* [7:0] = 4th character of year  */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8070.7:0 RO Month 1 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u4.bits_4.month_1

                        

                        [7:0] = 1st character of month

                 <B>Notes:</B>
                        ASCII 10's character  */
      unsigned int   month_1 : 8;    /* 01.8070.7:0  RO       */
                     /* [7:0] = 1st character of month  */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8071.7:0 RO Month 2 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u5.bits_5.month_2

                        

                        [7:0] = 2nd character of month

                 <B>Notes:</B>
                        ASCII 1's character  */
      unsigned int   month_2 : 8;    /* 01.8071.7:0  RO       */
                     /* [7:0] = 2nd character of month  */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8072.7:0 RO Day 1 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u6.bits_6.day_1

                        

                        [7:0] = 1st character of day

                 <B>Notes:</B>
                        ASCII 10's character  */
      unsigned int   day_1 : 8;    /* 01.8072.7:0  RO       */
                     /* [7:0] = 1st character of day  */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8073.7:0 RO Day 2 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u7.bits_7.day_2

                        

                        [7:0] = 2nd character of day

                 <B>Notes:</B>
                        ASCII 1's character  */
      unsigned int   day_2 : 8;    /* 01.8073.7:0  RO       */
                     /* [7:0] = 2nd character of day  */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8074.7:0 RO Lot 1 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u8.bits_8.lot_1

                        

                        [7:0] = 1st character of lot

                 <B>Notes:</B>
                        ASCII 10's character  */
      unsigned int   lot_1 : 8;    /* 01.8074.7:0  RO       */
                     /* [7:0] = 1st character of lot  */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of XENPAK Basic - Vendor Date Code */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8075.7:0 RO Lot 2 [7:0]
                        AQ_XenpakBasic_VendorDateCode_EUR.u9.bits_9.lot_2

                        

                        [7:0] = 2nd character of lot

                 <B>Notes:</B>
                        ASCII 1's character  */
      unsigned int   lot_2 : 8;    /* 01.8075.7:0  RO       */
                     /* [7:0] = 2nd character of lot  */
    } bits_9;
    uint16_t word_9;
  } u9;
} AQ_XenpakBasic_VendorDateCode_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - 5V Loading: 01.8076 */
/*                  XENPAK Basic - 5V Loading: 01.8076 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - 5V Loading */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8076.7:0 RO 5V Loading [7:0]
                        AQ_XenpakBasic__5vLoading_EUR.u0.bits_0._5vLoading

                        

                        [7:0]
                        0x80 = 90% - 99%
                        0x40 = 80% - 89%
                        0x20 = 70% - 79%
                        0x10 = 60% - 69%
                        0x08 = 50% - 59%
                        0x04 = 40% - 49%
                        0x02 = 30% - 39%
                        0x01 = 20% - 29%
                        0x0 = 5V not used

                 <B>Notes:</B>
                        All non-power of 2 values are invalid.  */
      unsigned int   _5vLoading : 8;    /* 01.8076.7:0  RO       */
                     /* [7:0]
                        0x80 = 90% - 99%
                        0x40 = 80% - 89%
                        0x20 = 70% - 79%
                        0x10 = 60% - 69%
                        0x08 = 50% - 59%
                        0x04 = 40% - 49%
                        0x02 = 30% - 39%
                        0x01 = 20% - 29%
                        0x0 = 5V not used  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic__5vLoading_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - 3.3V Loading: 01.8077 */
/*                  XENPAK Basic - 3.3V Loading: 01.8077 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - 3.3V Loading */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8077.7:0 RO 3.3V Loading [7:0]
                        AQ_XenpakBasic__3_3vLoading_EUR.u0.bits_0._3_3vLoading

                        

                        [7:0]
                        0x80 = 90% - 99%
                        0x40 = 80% - 89%
                        0x20 = 70% - 79%
                        0x10 = 60% - 69%
                        0x08 = 50% - 59%
                        0x04 = 40% - 49%
                        0x02 = 30% - 39%
                        0x01 = 20% - 29%
                        0x0 = 3.3V not used

                 <B>Notes:</B>
                        All non-power of 2 values are invalid.  */
      unsigned int   _3_3vLoading : 8;    /* 01.8077.7:0  RO       */
                     /* [7:0]
                        0x80 = 90% - 99%
                        0x40 = 80% - 89%
                        0x20 = 70% - 79%
                        0x10 = 60% - 69%
                        0x08 = 50% - 59%
                        0x04 = 40% - 49%
                        0x02 = 30% - 39%
                        0x01 = 20% - 29%
                        0x0 = 3.3V not used  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic__3_3vLoading_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - APS Loading: 01.8078 */
/*                  XENPAK Basic - APS Loading: 01.8078 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - APS Loading */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8078.7:0 RO APS Loading [7:0]
                        AQ_XenpakBasic_ApsLoading_EUR.u0.bits_0.apsLoading

                        

                        [7:0]
                        0x80 = 90% - 99%
                        0x40 = 80% - 89%
                        0x20 = 70% - 89%
                        0x10 = 60% - 89%
                        0x08 = 50% - 89%
                        0x04 = 40% - 89%
                        0x02 = 30% - 89%
                        0x01 = 20% - 89%
                        0x0 = APS not used

                 <B>Notes:</B>
                        All non-power of 2 values are invalid.  */
      unsigned int   apsLoading : 8;    /* 01.8078.7:0  RO       */
                     /* [7:0]
                        0x80 = 90% - 99%
                        0x40 = 80% - 89%
                        0x20 = 70% - 89%
                        0x10 = 60% - 89%
                        0x08 = 50% - 89%
                        0x04 = 40% - 89%
                        0x02 = 30% - 89%
                        0x01 = 20% - 89%
                        0x0 = APS not used  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_ApsLoading_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - APS Voltage: 01.8079 */
/*                  XENPAK Basic - APS Voltage: 01.8079 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - APS Voltage */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8079.7:0 RO APS Voltage [7:0]
                        AQ_XenpakBasic_ApsVoltage_EUR.u0.bits_0.apsVoltage

                        

                        [7:0]
                        0x80 = Reserved
                        0x40 = C
                        0x20 = 1.8V
                        0x10 = 1.5V
                        0x08 = 1.3V
                        0x04 = 1.2V
                        0x02 = 1V
                        0x01 = 0.9V
                        0x0 = Unspecified

                 <B>Notes:</B>
                        All non-power of 2 values are invalid.  */
      unsigned int   apsVoltage : 8;    /* 01.8079.7:0  RO       */
                     /* [7:0]
                        0x80 = Reserved
                        0x40 = C
                        0x20 = 1.8V
                        0x10 = 1.5V
                        0x08 = 1.3V
                        0x04 = 1.2V
                        0x02 = 1V
                        0x01 = 0.9V
                        0x0 = Unspecified  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_ApsVoltage_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - DOM Capability: 01.807A */
/*                  XENPAK Basic - DOM Capability: 01.807A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - DOM Capability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.807A.7 ROS DOM Control Capability
                        AQ_XenpakBasic_DomCapability_EUR.u0.bits_0.domControlCapability

                        Default = 0x1

                        1 = Implemented
                        0 = Not implemented

                 <B>Notes:</B>
                        When set this bit indicates whether the XENPAK supports DOM control and status registers.  */
      unsigned int   domControlCapability : 1;    /* 01.807A.7  ROS      Default = 0x1 */
                     /* 1 = Implemented
                        0 = Not implemented  */
                    /*! \brief 01.807A.6 ROS DOM Capability
                        AQ_XenpakBasic_DomCapability_EUR.u0.bits_0.domCapability

                        Default = 0x1

                        1 = Implemented
                        0 = Not implemented

                 <B>Notes:</B>
                        When set this bit indicates whether the XENPAK supports DOM.  */
      unsigned int   domCapability : 1;    /* 01.807A.6  ROS      Default = 0x1 */
                     /* 1 = Implemented
                        0 = Not implemented  */
      unsigned int   reserved1 : 6;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_DomCapability_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Low-Power Startup Capability: 01.807B */
/*                  XENPAK Basic - Low-Power Startup Capability: 01.807B */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Low-Power Startup Capability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 01.807B.0 ROS Low Power Start-up Capability
                        AQ_XenpakBasic_Low_powerStartupCapability_EUR.u0.bits_0.lowPowerStart_upCapability

                        Default = 0x1

                        1 = Low-power start-up capable
                        0 = Not capable

                 <B>Notes:</B>
                        When set this bit indicates whether the XENPAK can come up in a low-power mode.  */
      unsigned int   lowPowerStart_upCapability : 1;    /* 01.807B.0  ROS      Default = 0x1 */
                     /* 1 = Low-power start-up capable
                        0 = Not capable  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_Low_powerStartupCapability_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Reserved 0x7C: 01.807C */
/*                  XENPAK Basic - Reserved 0x7C: 01.807C */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Reserved 0x7C */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.807C.7:0 ROS Basic Reserved 0x7C [7:0]
                        AQ_XenpakBasic_Reserved_0x7c_EUR.u0.bits_0.basicReserved_0x7c

                        Default = 0x00
  */
      unsigned int   basicReserved_0x7c : 8;    /* 01.807C.7:0  ROS      Default = 0x00 */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_Reserved_0x7c_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Basic - Checksum: 01.807D */
/*                  XENPAK Basic - Checksum: 01.807D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Basic - Checksum */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.807D.7:0 RO Checksum [7:0]
                        AQ_XenpakBasic_Checksum_EUR.u0.bits_0.checksum

                        

                        [7:0] = Checksum

                 <B>Notes:</B>
                        The checksum over the LSBs of all the registers from 1.8007 to 1.807C.  */
      unsigned int   checksum : 8;    /* 01.807D.7:0  RO       */
                     /* [7:0] = Checksum  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakBasic_Checksum_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Customer - Reserved 0x7E: 01.807E */
/*                  XENPAK Customer - Reserved 0x7E: 01.807E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.807E.7:0 RO Customer Reserved 0x7E [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u0.bits_0.customerReserved_0x7e

                        
  */
      unsigned int   customerReserved_0x7e : 8;    /* 01.807E.7:0  RO       */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.807F.7:0 RO Customer Reserved 0x7F [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u1.bits_1.customerReserved_0x7f

                        
  */
      unsigned int   customerReserved_0x7f : 8;    /* 01.807F.7:0  RO       */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8080.7:0 RO Customer Reserved 0x80 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u2.bits_2.customerReserved_0x80

                        
  */
      unsigned int   customerReserved_0x80 : 8;    /* 01.8080.7:0  RO       */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8081.7:0 RO Customer Reserved 0x81 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u3.bits_3.customerReserved_0x81

                        
  */
      unsigned int   customerReserved_0x81 : 8;    /* 01.8081.7:0  RO       */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8082.7:0 RO Customer Reserved 0x82 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u4.bits_4.customerReserved_0x82

                        
  */
      unsigned int   customerReserved_0x82 : 8;    /* 01.8082.7:0  RO       */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8083.7:0 RO Customer Reserved 0x83 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u5.bits_5.customerReserved_0x83

                        
  */
      unsigned int   customerReserved_0x83 : 8;    /* 01.8083.7:0  RO       */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8084.7:0 RO Customer Reserved 0x84 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u6.bits_6.customerReserved_0x84

                        
  */
      unsigned int   customerReserved_0x84 : 8;    /* 01.8084.7:0  RO       */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8085.7:0 RO Customer Reserved 0x85 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u7.bits_7.customerReserved_0x85

                        
  */
      unsigned int   customerReserved_0x85 : 8;    /* 01.8085.7:0  RO       */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8086.7:0 RO Customer Reserved 0x86 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u8.bits_8.customerReserved_0x86

                        
  */
      unsigned int   customerReserved_0x86 : 8;    /* 01.8086.7:0  RO       */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8087.7:0 RO Customer Reserved 0x87 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u9.bits_9.customerReserved_0x87

                        
  */
      unsigned int   customerReserved_0x87 : 8;    /* 01.8087.7:0  RO       */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8088.7:0 RO Customer Reserved 0x88 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u10.bits_10.customerReserved_0x88

                        
  */
      unsigned int   customerReserved_0x88 : 8;    /* 01.8088.7:0  RO       */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8089.7:0 RO Customer Reserved 0x89 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u11.bits_11.customerReserved_0x89

                        
  */
      unsigned int   customerReserved_0x89 : 8;    /* 01.8089.7:0  RO       */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.808A.7:0 RO Customer Reserved 0x8A [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u12.bits_12.customerReserved_0x8a

                        
  */
      unsigned int   customerReserved_0x8a : 8;    /* 01.808A.7:0  RO       */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.808B.7:0 RO Customer Reserved 0x8B [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u13.bits_13.customerReserved_0x8b

                        
  */
      unsigned int   customerReserved_0x8b : 8;    /* 01.808B.7:0  RO       */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.808C.7:0 RO Customer Reserved 0x8C [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u14.bits_14.customerReserved_0x8c

                        
  */
      unsigned int   customerReserved_0x8c : 8;    /* 01.808C.7:0  RO       */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.808D.7:0 RO Customer Reserved 0x8D [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u15.bits_15.customerReserved_0x8d

                        
  */
      unsigned int   customerReserved_0x8d : 8;    /* 01.808D.7:0  RO       */
    } bits_15;
    uint16_t word_15;
  } u15;
  /*! \brief Union for bit and word level access of word 16 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.808E.7:0 RO Customer Reserved 0x8E [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u16.bits_16.customerReserved_0x8e

                        
  */
      unsigned int   customerReserved_0x8e : 8;    /* 01.808E.7:0  RO       */
    } bits_16;
    uint16_t word_16;
  } u16;
  /*! \brief Union for bit and word level access of word 17 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.808F.7:0 RO Customer Reserved 0x8F [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u17.bits_17.customerReserved_0x8f

                        
  */
      unsigned int   customerReserved_0x8f : 8;    /* 01.808F.7:0  RO       */
    } bits_17;
    uint16_t word_17;
  } u17;
  /*! \brief Union for bit and word level access of word 18 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8090.7:0 RO Customer Reserved 0x90 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u18.bits_18.customerReserved_0x90

                        
  */
      unsigned int   customerReserved_0x90 : 8;    /* 01.8090.7:0  RO       */
    } bits_18;
    uint16_t word_18;
  } u18;
  /*! \brief Union for bit and word level access of word 19 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8091.7:0 RO Customer Reserved 0x91 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u19.bits_19.customerReserved_0x91

                        
  */
      unsigned int   customerReserved_0x91 : 8;    /* 01.8091.7:0  RO       */
    } bits_19;
    uint16_t word_19;
  } u19;
  /*! \brief Union for bit and word level access of word 20 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8092.7:0 RO Customer Reserved 0x92 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u20.bits_20.customerReserved_0x92

                        
  */
      unsigned int   customerReserved_0x92 : 8;    /* 01.8092.7:0  RO       */
    } bits_20;
    uint16_t word_20;
  } u20;
  /*! \brief Union for bit and word level access of word 21 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8093.7:0 RO Customer Reserved 0x93 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u21.bits_21.customerReserved_0x93

                        
  */
      unsigned int   customerReserved_0x93 : 8;    /* 01.8093.7:0  RO       */
    } bits_21;
    uint16_t word_21;
  } u21;
  /*! \brief Union for bit and word level access of word 22 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8094.7:0 RO Customer Reserved 0x94 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u22.bits_22.customerReserved_0x94

                        
  */
      unsigned int   customerReserved_0x94 : 8;    /* 01.8094.7:0  RO       */
    } bits_22;
    uint16_t word_22;
  } u22;
  /*! \brief Union for bit and word level access of word 23 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8095.7:0 RO Customer Reserved 0x95 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u23.bits_23.customerReserved_0x95

                        
  */
      unsigned int   customerReserved_0x95 : 8;    /* 01.8095.7:0  RO       */
    } bits_23;
    uint16_t word_23;
  } u23;
  /*! \brief Union for bit and word level access of word 24 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8096.7:0 RO Customer Reserved 0x96 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u24.bits_24.customerReserved_0x96

                        
  */
      unsigned int   customerReserved_0x96 : 8;    /* 01.8096.7:0  RO       */
    } bits_24;
    uint16_t word_24;
  } u24;
  /*! \brief Union for bit and word level access of word 25 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8097.7:0 RO Customer Reserved 0x97 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u25.bits_25.customerReserved_0x97

                        
  */
      unsigned int   customerReserved_0x97 : 8;    /* 01.8097.7:0  RO       */
    } bits_25;
    uint16_t word_25;
  } u25;
  /*! \brief Union for bit and word level access of word 26 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8098.7:0 RO Customer Reserved 0x98 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u26.bits_26.customerReserved_0x98

                        
  */
      unsigned int   customerReserved_0x98 : 8;    /* 01.8098.7:0  RO       */
    } bits_26;
    uint16_t word_26;
  } u26;
  /*! \brief Union for bit and word level access of word 27 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8099.7:0 RO Customer Reserved 0x99 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u27.bits_27.customerReserved_0x99

                        
  */
      unsigned int   customerReserved_0x99 : 8;    /* 01.8099.7:0  RO       */
    } bits_27;
    uint16_t word_27;
  } u27;
  /*! \brief Union for bit and word level access of word 28 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.809A.7:0 RO Customer Reserved 0x9A [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u28.bits_28.customerReserved_0x9a

                        
  */
      unsigned int   customerReserved_0x9a : 8;    /* 01.809A.7:0  RO       */
    } bits_28;
    uint16_t word_28;
  } u28;
  /*! \brief Union for bit and word level access of word 29 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.809B.7:0 RO Customer Reserved 0x9B [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u29.bits_29.customerReserved_0x9b

                        
  */
      unsigned int   customerReserved_0x9b : 8;    /* 01.809B.7:0  RO       */
    } bits_29;
    uint16_t word_29;
  } u29;
  /*! \brief Union for bit and word level access of word 30 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.809C.7:0 RO Customer Reserved 0x9C [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u30.bits_30.customerReserved_0x9c

                        
  */
      unsigned int   customerReserved_0x9c : 8;    /* 01.809C.7:0  RO       */
    } bits_30;
    uint16_t word_30;
  } u30;
  /*! \brief Union for bit and word level access of word 31 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.809D.7:0 RO Customer Reserved 0x9D [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u31.bits_31.customerReserved_0x9d

                        
  */
      unsigned int   customerReserved_0x9d : 8;    /* 01.809D.7:0  RO       */
    } bits_31;
    uint16_t word_31;
  } u31;
  /*! \brief Union for bit and word level access of word 32 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.809E.7:0 RO Customer Reserved 0x9E [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u32.bits_32.customerReserved_0x9e

                        
  */
      unsigned int   customerReserved_0x9e : 8;    /* 01.809E.7:0  RO       */
    } bits_32;
    uint16_t word_32;
  } u32;
  /*! \brief Union for bit and word level access of word 33 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.809F.7:0 RO Customer Reserved 0x9F [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u33.bits_33.customerReserved_0x9f

                        
  */
      unsigned int   customerReserved_0x9f : 8;    /* 01.809F.7:0  RO       */
    } bits_33;
    uint16_t word_33;
  } u33;
  /*! \brief Union for bit and word level access of word 34 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A0.7:0 RO Customer Reserved 0xA0 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u34.bits_34.customerReserved_0xa0

                        
  */
      unsigned int   customerReserved_0xa0 : 8;    /* 01.80A0.7:0  RO       */
    } bits_34;
    uint16_t word_34;
  } u34;
  /*! \brief Union for bit and word level access of word 35 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A1.7:0 RO Customer Reserved 0xA1 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u35.bits_35.customerReserved_0xa1

                        
  */
      unsigned int   customerReserved_0xa1 : 8;    /* 01.80A1.7:0  RO       */
    } bits_35;
    uint16_t word_35;
  } u35;
  /*! \brief Union for bit and word level access of word 36 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A2.7:0 RO Customer Reserved 0xA2 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u36.bits_36.customerReserved_0xa2

                        
  */
      unsigned int   customerReserved_0xa2 : 8;    /* 01.80A2.7:0  RO       */
    } bits_36;
    uint16_t word_36;
  } u36;
  /*! \brief Union for bit and word level access of word 37 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A3.7:0 RO Customer Reserved 0xA3 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u37.bits_37.customerReserved_0xa3

                        
  */
      unsigned int   customerReserved_0xa3 : 8;    /* 01.80A3.7:0  RO       */
    } bits_37;
    uint16_t word_37;
  } u37;
  /*! \brief Union for bit and word level access of word 38 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A4.7:0 RO Customer Reserved 0xA4 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u38.bits_38.customerReserved_0xa4

                        
  */
      unsigned int   customerReserved_0xa4 : 8;    /* 01.80A4.7:0  RO       */
    } bits_38;
    uint16_t word_38;
  } u38;
  /*! \brief Union for bit and word level access of word 39 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A5.7:0 RO Customer Reserved 0xA5 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u39.bits_39.customerReserved_0xa5

                        
  */
      unsigned int   customerReserved_0xa5 : 8;    /* 01.80A5.7:0  RO       */
    } bits_39;
    uint16_t word_39;
  } u39;
  /*! \brief Union for bit and word level access of word 40 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A6.7:0 RO Customer Reserved 0xA6 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u40.bits_40.customerReserved_0xa6

                        
  */
      unsigned int   customerReserved_0xa6 : 8;    /* 01.80A6.7:0  RO       */
    } bits_40;
    uint16_t word_40;
  } u40;
  /*! \brief Union for bit and word level access of word 41 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A7.7:0 RO Customer Reserved 0xA7 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u41.bits_41.customerReserved_0xa7

                        
  */
      unsigned int   customerReserved_0xa7 : 8;    /* 01.80A7.7:0  RO       */
    } bits_41;
    uint16_t word_41;
  } u41;
  /*! \brief Union for bit and word level access of word 42 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A8.7:0 RO Customer Reserved 0xA8 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u42.bits_42.customerReserved_0xa8

                        
  */
      unsigned int   customerReserved_0xa8 : 8;    /* 01.80A8.7:0  RO       */
    } bits_42;
    uint16_t word_42;
  } u42;
  /*! \brief Union for bit and word level access of word 43 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80A9.7:0 RO Customer Reserved 0xA9 [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u43.bits_43.customerReserved_0xa9

                        
  */
      unsigned int   customerReserved_0xa9 : 8;    /* 01.80A9.7:0  RO       */
    } bits_43;
    uint16_t word_43;
  } u43;
  /*! \brief Union for bit and word level access of word 44 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80AA.7:0 RO Customer Reserved 0xAA [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u44.bits_44.customerReserved_0xaa

                        
  */
      unsigned int   customerReserved_0xaa : 8;    /* 01.80AA.7:0  RO       */
    } bits_44;
    uint16_t word_44;
  } u44;
  /*! \brief Union for bit and word level access of word 45 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80AB.7:0 RO Customer Reserved 0xAB [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u45.bits_45.customerReserved_0xab

                        
  */
      unsigned int   customerReserved_0xab : 8;    /* 01.80AB.7:0  RO       */
    } bits_45;
    uint16_t word_45;
  } u45;
  /*! \brief Union for bit and word level access of word 46 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80AC.7:0 RO Customer Reserved 0xAC [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u46.bits_46.customerReserved_0xac

                        
  */
      unsigned int   customerReserved_0xac : 8;    /* 01.80AC.7:0  RO       */
    } bits_46;
    uint16_t word_46;
  } u46;
  /*! \brief Union for bit and word level access of word 47 of XENPAK Customer - Reserved 0x7E */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80AD.7:0 RO Customer Reserved 0xAD [7:0]
                        AQ_XenpakCustomer_Reserved_0x7e_EUR.u47.bits_47.customerReserved_0xad

                        
  */
      unsigned int   customerReserved_0xad : 8;    /* 01.80AD.7:0  RO       */
    } bits_47;
    uint16_t word_47;
  } u47;
} AQ_XenpakCustomer_Reserved_0x7e_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Vendor - Reserved 0xAE: 01.80AE */
/*                  XENPAK Vendor - Reserved 0xAE: 01.80AE */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80AE.7:0 RO Vendor Reserved 0xAE [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u0.bits_0.vendorReserved_0xae

                        
  */
      unsigned int   vendorReserved_0xae : 8;    /* 01.80AE.7:0  RO       */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80AF.7:0 RO Vendor Reserved 0xAF [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u1.bits_1.vendorReserved_0xaf

                        
  */
      unsigned int   vendorReserved_0xaf : 8;    /* 01.80AF.7:0  RO       */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B0.7:0 RO Vendor Reserved 0xBO [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u2.bits_2.vendorReserved_0xbo

                        
  */
      unsigned int   vendorReserved_0xbo : 8;    /* 01.80B0.7:0  RO       */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B1.7:0 RO Vendor Reserved 0xB1 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u3.bits_3.vendorReserved_0xb1

                        
  */
      unsigned int   vendorReserved_0xb1 : 8;    /* 01.80B1.7:0  RO       */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B2.7:0 RO Vendor Reserved 0xB2 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u4.bits_4.vendorReserved_0xb2

                        
  */
      unsigned int   vendorReserved_0xb2 : 8;    /* 01.80B2.7:0  RO       */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B3.7:0 RO Vendor Reserved 0xB3 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u5.bits_5.vendorReserved_0xb3

                        
  */
      unsigned int   vendorReserved_0xb3 : 8;    /* 01.80B3.7:0  RO       */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B4.7:0 RO Vendor Reserved 0xB4 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u6.bits_6.vendorReserved_0xb4

                        
  */
      unsigned int   vendorReserved_0xb4 : 8;    /* 01.80B4.7:0  RO       */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B5.7:0 RO Vendor Reserved 0xB5 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u7.bits_7.vendorReserved_0xb5

                        
  */
      unsigned int   vendorReserved_0xb5 : 8;    /* 01.80B5.7:0  RO       */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B6.7:0 RO Vendor Reserved 0xB6 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u8.bits_8.vendorReserved_0xb6

                        
  */
      unsigned int   vendorReserved_0xb6 : 8;    /* 01.80B6.7:0  RO       */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B7.7:0 RO Vendor Reserved 0xB7 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u9.bits_9.vendorReserved_0xb7

                        
  */
      unsigned int   vendorReserved_0xb7 : 8;    /* 01.80B7.7:0  RO       */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B8.7:0 RO Vendor Reserved 0xB8 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u10.bits_10.vendorReserved_0xb8

                        
  */
      unsigned int   vendorReserved_0xb8 : 8;    /* 01.80B8.7:0  RO       */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80B9.7:0 RO Vendor Reserved 0xB9 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u11.bits_11.vendorReserved_0xb9

                        
  */
      unsigned int   vendorReserved_0xb9 : 8;    /* 01.80B9.7:0  RO       */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80BA.7:0 RO Vendor Reserved 0xBA [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u12.bits_12.vendorReserved_0xba

                        
  */
      unsigned int   vendorReserved_0xba : 8;    /* 01.80BA.7:0  RO       */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80BB.7:0 RO Vendor Reserved 0xBB [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u13.bits_13.vendorReserved_0xbb

                        
  */
      unsigned int   vendorReserved_0xbb : 8;    /* 01.80BB.7:0  RO       */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80BC.7:0 RO Vendor Reserved 0xBC [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u14.bits_14.vendorReserved_0xbc

                        
  */
      unsigned int   vendorReserved_0xbc : 8;    /* 01.80BC.7:0  RO       */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80BD.7:0 RO Vendor Reserved 0xBD [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u15.bits_15.vendorReserved_0xbd

                        
  */
      unsigned int   vendorReserved_0xbd : 8;    /* 01.80BD.7:0  RO       */
    } bits_15;
    uint16_t word_15;
  } u15;
  /*! \brief Union for bit and word level access of word 16 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80BE.7:0 RO Vendor Reserved 0xBE [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u16.bits_16.vendorReserved_0xbe

                        
  */
      unsigned int   vendorReserved_0xbe : 8;    /* 01.80BE.7:0  RO       */
    } bits_16;
    uint16_t word_16;
  } u16;
  /*! \brief Union for bit and word level access of word 17 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80BF.7:0 RO Vendor Reserved 0xBF [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u17.bits_17.vendorReserved_0xbf

                        
  */
      unsigned int   vendorReserved_0xbf : 8;    /* 01.80BF.7:0  RO       */
    } bits_17;
    uint16_t word_17;
  } u17;
  /*! \brief Union for bit and word level access of word 18 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C0.7:0 RO Vendor Reserved 0xC0 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u18.bits_18.vendorReserved_0xc0

                        
  */
      unsigned int   vendorReserved_0xc0 : 8;    /* 01.80C0.7:0  RO       */
    } bits_18;
    uint16_t word_18;
  } u18;
  /*! \brief Union for bit and word level access of word 19 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C1.7:0 RO Vendor Reserved 0xC1 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u19.bits_19.vendorReserved_0xc1

                        
  */
      unsigned int   vendorReserved_0xc1 : 8;    /* 01.80C1.7:0  RO       */
    } bits_19;
    uint16_t word_19;
  } u19;
  /*! \brief Union for bit and word level access of word 20 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C2.7:0 RO Vendor Reserved 0xC2 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u20.bits_20.vendorReserved_0xc2

                        
  */
      unsigned int   vendorReserved_0xc2 : 8;    /* 01.80C2.7:0  RO       */
    } bits_20;
    uint16_t word_20;
  } u20;
  /*! \brief Union for bit and word level access of word 21 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C3.7:0 RO Vendor Reserved 0xC3 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u21.bits_21.vendorReserved_0xc3

                        
  */
      unsigned int   vendorReserved_0xc3 : 8;    /* 01.80C3.7:0  RO       */
    } bits_21;
    uint16_t word_21;
  } u21;
  /*! \brief Union for bit and word level access of word 22 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C4.7:0 RO Vendor Reserved 0xC4 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u22.bits_22.vendorReserved_0xc4

                        
  */
      unsigned int   vendorReserved_0xc4 : 8;    /* 01.80C4.7:0  RO       */
    } bits_22;
    uint16_t word_22;
  } u22;
  /*! \brief Union for bit and word level access of word 23 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C5.7:0 RO Vendor Reserved 0xC5 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u23.bits_23.vendorReserved_0xc5

                        
  */
      unsigned int   vendorReserved_0xc5 : 8;    /* 01.80C5.7:0  RO       */
    } bits_23;
    uint16_t word_23;
  } u23;
  /*! \brief Union for bit and word level access of word 24 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C6.7:0 RO Vendor Reserved 0xC6 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u24.bits_24.vendorReserved_0xc6

                        
  */
      unsigned int   vendorReserved_0xc6 : 8;    /* 01.80C6.7:0  RO       */
    } bits_24;
    uint16_t word_24;
  } u24;
  /*! \brief Union for bit and word level access of word 25 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C7.7:0 RO Vendor Reserved 0xC7 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u25.bits_25.vendorReserved_0xc7

                        
  */
      unsigned int   vendorReserved_0xc7 : 8;    /* 01.80C7.7:0  RO       */
    } bits_25;
    uint16_t word_25;
  } u25;
  /*! \brief Union for bit and word level access of word 26 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C8.7:0 RO Vendor Reserved 0xC8 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u26.bits_26.vendorReserved_0xc8

                        
  */
      unsigned int   vendorReserved_0xc8 : 8;    /* 01.80C8.7:0  RO       */
    } bits_26;
    uint16_t word_26;
  } u26;
  /*! \brief Union for bit and word level access of word 27 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80C9.7:0 RO Vendor Reserved 0xC9 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u27.bits_27.vendorReserved_0xc9

                        
  */
      unsigned int   vendorReserved_0xc9 : 8;    /* 01.80C9.7:0  RO       */
    } bits_27;
    uint16_t word_27;
  } u27;
  /*! \brief Union for bit and word level access of word 28 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80CA.7:0 RO Vendor Reserved 0xCA [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u28.bits_28.vendorReserved_0xca

                        
  */
      unsigned int   vendorReserved_0xca : 8;    /* 01.80CA.7:0  RO       */
    } bits_28;
    uint16_t word_28;
  } u28;
  /*! \brief Union for bit and word level access of word 29 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80CB.7:0 RO Vendor Reserved 0xCB [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u29.bits_29.vendorReserved_0xcb

                        
  */
      unsigned int   vendorReserved_0xcb : 8;    /* 01.80CB.7:0  RO       */
    } bits_29;
    uint16_t word_29;
  } u29;
  /*! \brief Union for bit and word level access of word 30 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80CC.7:0 RO Vendor Reserved 0xCC [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u30.bits_30.vendorReserved_0xcc

                        
  */
      unsigned int   vendorReserved_0xcc : 8;    /* 01.80CC.7:0  RO       */
    } bits_30;
    uint16_t word_30;
  } u30;
  /*! \brief Union for bit and word level access of word 31 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80CD.7:0 RO Vendor Reserved 0xCD [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u31.bits_31.vendorReserved_0xcd

                        
  */
      unsigned int   vendorReserved_0xcd : 8;    /* 01.80CD.7:0  RO       */
    } bits_31;
    uint16_t word_31;
  } u31;
  /*! \brief Union for bit and word level access of word 32 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80CE.7:0 RO Vendor Reserved 0xCE [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u32.bits_32.vendorReserved_0xce

                        
  */
      unsigned int   vendorReserved_0xce : 8;    /* 01.80CE.7:0  RO       */
    } bits_32;
    uint16_t word_32;
  } u32;
  /*! \brief Union for bit and word level access of word 33 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80CF.7:0 RO Vendor Reserved 0xCF [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u33.bits_33.vendorReserved_0xcf

                        
  */
      unsigned int   vendorReserved_0xcf : 8;    /* 01.80CF.7:0  RO       */
    } bits_33;
    uint16_t word_33;
  } u33;
  /*! \brief Union for bit and word level access of word 34 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D0.7:0 RO Vendor Reserved 0xD0 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u34.bits_34.vendorReserved_0xd0

                        
  */
      unsigned int   vendorReserved_0xd0 : 8;    /* 01.80D0.7:0  RO       */
    } bits_34;
    uint16_t word_34;
  } u34;
  /*! \brief Union for bit and word level access of word 35 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D1.7:0 RO Vendor Reserved 0xD1 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u35.bits_35.vendorReserved_0xd1

                        
  */
      unsigned int   vendorReserved_0xd1 : 8;    /* 01.80D1.7:0  RO       */
    } bits_35;
    uint16_t word_35;
  } u35;
  /*! \brief Union for bit and word level access of word 36 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D2.7:0 RO Vendor Reserved 0xD2 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u36.bits_36.vendorReserved_0xd2

                        
  */
      unsigned int   vendorReserved_0xd2 : 8;    /* 01.80D2.7:0  RO       */
    } bits_36;
    uint16_t word_36;
  } u36;
  /*! \brief Union for bit and word level access of word 37 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D3.7:0 RO Vendor Reserved 0xD3 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u37.bits_37.vendorReserved_0xd3

                        
  */
      unsigned int   vendorReserved_0xd3 : 8;    /* 01.80D3.7:0  RO       */
    } bits_37;
    uint16_t word_37;
  } u37;
  /*! \brief Union for bit and word level access of word 38 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D4.7:0 RO Vendor Reserved 0xD4 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u38.bits_38.vendorReserved_0xd4

                        
  */
      unsigned int   vendorReserved_0xd4 : 8;    /* 01.80D4.7:0  RO       */
    } bits_38;
    uint16_t word_38;
  } u38;
  /*! \brief Union for bit and word level access of word 39 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D5.7:0 RO Vendor Reserved 0xD5 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u39.bits_39.vendorReserved_0xd5

                        
  */
      unsigned int   vendorReserved_0xd5 : 8;    /* 01.80D5.7:0  RO       */
    } bits_39;
    uint16_t word_39;
  } u39;
  /*! \brief Union for bit and word level access of word 40 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D6.7:0 RO Vendor Reserved 0xD6 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u40.bits_40.vendorReserved_0xd6

                        
  */
      unsigned int   vendorReserved_0xd6 : 8;    /* 01.80D6.7:0  RO       */
    } bits_40;
    uint16_t word_40;
  } u40;
  /*! \brief Union for bit and word level access of word 41 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D7.7:0 RO Vendor Reserved 0xD7 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u41.bits_41.vendorReserved_0xd7

                        
  */
      unsigned int   vendorReserved_0xd7 : 8;    /* 01.80D7.7:0  RO       */
    } bits_41;
    uint16_t word_41;
  } u41;
  /*! \brief Union for bit and word level access of word 42 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D8.7:0 RO Vendor Reserved 0xD8 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u42.bits_42.vendorReserved_0xd8

                        
  */
      unsigned int   vendorReserved_0xd8 : 8;    /* 01.80D8.7:0  RO       */
    } bits_42;
    uint16_t word_42;
  } u42;
  /*! \brief Union for bit and word level access of word 43 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80D9.7:0 RO Vendor Reserved 0xD9 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u43.bits_43.vendorReserved_0xd9

                        
  */
      unsigned int   vendorReserved_0xd9 : 8;    /* 01.80D9.7:0  RO       */
    } bits_43;
    uint16_t word_43;
  } u43;
  /*! \brief Union for bit and word level access of word 44 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80DA.7:0 RO Vendor Reserved 0xDA [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u44.bits_44.vendorReserved_0xda

                        
  */
      unsigned int   vendorReserved_0xda : 8;    /* 01.80DA.7:0  RO       */
    } bits_44;
    uint16_t word_44;
  } u44;
  /*! \brief Union for bit and word level access of word 45 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80DB.7:0 RO Vendor Reserved 0xDB [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u45.bits_45.vendorReserved_0xdb

                        
  */
      unsigned int   vendorReserved_0xdb : 8;    /* 01.80DB.7:0  RO       */
    } bits_45;
    uint16_t word_45;
  } u45;
  /*! \brief Union for bit and word level access of word 46 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80DC.7:0 RO Vendor Reserved 0xDC [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u46.bits_46.vendorReserved_0xdc

                        
  */
      unsigned int   vendorReserved_0xdc : 8;    /* 01.80DC.7:0  RO       */
    } bits_46;
    uint16_t word_46;
  } u46;
  /*! \brief Union for bit and word level access of word 47 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80DD.7:0 RO Vendor Reserved 0xDD [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u47.bits_47.vendorReserved_0xdd

                        
  */
      unsigned int   vendorReserved_0xdd : 8;    /* 01.80DD.7:0  RO       */
    } bits_47;
    uint16_t word_47;
  } u47;
  /*! \brief Union for bit and word level access of word 48 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80DE.7:0 RO Vendor Reserved 0xDE [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u48.bits_48.vendorReserved_0xde

                        
  */
      unsigned int   vendorReserved_0xde : 8;    /* 01.80DE.7:0  RO       */
    } bits_48;
    uint16_t word_48;
  } u48;
  /*! \brief Union for bit and word level access of word 49 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80DF.7:0 RO Vendor Reserved 0xDF [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u49.bits_49.vendorReserved_0xdf

                        
  */
      unsigned int   vendorReserved_0xdf : 8;    /* 01.80DF.7:0  RO       */
    } bits_49;
    uint16_t word_49;
  } u49;
  /*! \brief Union for bit and word level access of word 50 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E0.7:0 RO Vendor Reserved 0xE0 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u50.bits_50.vendorReserved_0xe0

                        
  */
      unsigned int   vendorReserved_0xe0 : 8;    /* 01.80E0.7:0  RO       */
    } bits_50;
    uint16_t word_50;
  } u50;
  /*! \brief Union for bit and word level access of word 51 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E1.7:0 RO Vendor Reserved 0xE1 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u51.bits_51.vendorReserved_0xe1

                        
  */
      unsigned int   vendorReserved_0xe1 : 8;    /* 01.80E1.7:0  RO       */
    } bits_51;
    uint16_t word_51;
  } u51;
  /*! \brief Union for bit and word level access of word 52 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E2.7:0 RO Vendor Reserved 0xE2 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u52.bits_52.vendorReserved_0xe2

                        
  */
      unsigned int   vendorReserved_0xe2 : 8;    /* 01.80E2.7:0  RO       */
    } bits_52;
    uint16_t word_52;
  } u52;
  /*! \brief Union for bit and word level access of word 53 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E3.7:0 RO Vendor Reserved 0xE3 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u53.bits_53.vendorReserved_0xe3

                        
  */
      unsigned int   vendorReserved_0xe3 : 8;    /* 01.80E3.7:0  RO       */
    } bits_53;
    uint16_t word_53;
  } u53;
  /*! \brief Union for bit and word level access of word 54 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E4.7:0 RO Vendor Reserved 0xE4 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u54.bits_54.vendorReserved_0xe4

                        
  */
      unsigned int   vendorReserved_0xe4 : 8;    /* 01.80E4.7:0  RO       */
    } bits_54;
    uint16_t word_54;
  } u54;
  /*! \brief Union for bit and word level access of word 55 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E5.7:0 RO Vendor Reserved 0xE5 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u55.bits_55.vendorReserved_0xe5

                        
  */
      unsigned int   vendorReserved_0xe5 : 8;    /* 01.80E5.7:0  RO       */
    } bits_55;
    uint16_t word_55;
  } u55;
  /*! \brief Union for bit and word level access of word 56 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E6.7:0 RO Vendor Reserved 0xE6 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u56.bits_56.vendorReserved_0xe6

                        
  */
      unsigned int   vendorReserved_0xe6 : 8;    /* 01.80E6.7:0  RO       */
    } bits_56;
    uint16_t word_56;
  } u56;
  /*! \brief Union for bit and word level access of word 57 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E7.7:0 RO Vendor Reserved 0xE7 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u57.bits_57.vendorReserved_0xe7

                        
  */
      unsigned int   vendorReserved_0xe7 : 8;    /* 01.80E7.7:0  RO       */
    } bits_57;
    uint16_t word_57;
  } u57;
  /*! \brief Union for bit and word level access of word 58 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E8.7:0 RO Vendor Reserved 0xE8 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u58.bits_58.vendorReserved_0xe8

                        
  */
      unsigned int   vendorReserved_0xe8 : 8;    /* 01.80E8.7:0  RO       */
    } bits_58;
    uint16_t word_58;
  } u58;
  /*! \brief Union for bit and word level access of word 59 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80E9.7:0 RO Vendor Reserved 0xE9 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u59.bits_59.vendorReserved_0xe9

                        
  */
      unsigned int   vendorReserved_0xe9 : 8;    /* 01.80E9.7:0  RO       */
    } bits_59;
    uint16_t word_59;
  } u59;
  /*! \brief Union for bit and word level access of word 60 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80EA.7:0 RO Vendor Reserved 0xEA [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u60.bits_60.vendorReserved_0xea

                        
  */
      unsigned int   vendorReserved_0xea : 8;    /* 01.80EA.7:0  RO       */
    } bits_60;
    uint16_t word_60;
  } u60;
  /*! \brief Union for bit and word level access of word 61 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80EB.7:0 RO Vendor Reserved 0xEB [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u61.bits_61.vendorReserved_0xeb

                        
  */
      unsigned int   vendorReserved_0xeb : 8;    /* 01.80EB.7:0  RO       */
    } bits_61;
    uint16_t word_61;
  } u61;
  /*! \brief Union for bit and word level access of word 62 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80EC.7:0 RO Vendor Reserved 0xEC [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u62.bits_62.vendorReserved_0xec

                        
  */
      unsigned int   vendorReserved_0xec : 8;    /* 01.80EC.7:0  RO       */
    } bits_62;
    uint16_t word_62;
  } u62;
  /*! \brief Union for bit and word level access of word 63 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80ED.7:0 RO Vendor Reserved 0xED [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u63.bits_63.vendorReserved_0xed

                        
  */
      unsigned int   vendorReserved_0xed : 8;    /* 01.80ED.7:0  RO       */
    } bits_63;
    uint16_t word_63;
  } u63;
  /*! \brief Union for bit and word level access of word 64 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80EE.7:0 RO Vendor Reserved 0xEE [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u64.bits_64.vendorReserved_0xee

                        
  */
      unsigned int   vendorReserved_0xee : 8;    /* 01.80EE.7:0  RO       */
    } bits_64;
    uint16_t word_64;
  } u64;
  /*! \brief Union for bit and word level access of word 65 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80EF.7:0 RO Vendor Reserved 0xEF [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u65.bits_65.vendorReserved_0xef

                        
  */
      unsigned int   vendorReserved_0xef : 8;    /* 01.80EF.7:0  RO       */
    } bits_65;
    uint16_t word_65;
  } u65;
  /*! \brief Union for bit and word level access of word 66 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F0.7:0 RO Vendor Reserved 0xF0 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u66.bits_66.vendorReserved_0xf0

                        
  */
      unsigned int   vendorReserved_0xf0 : 8;    /* 01.80F0.7:0  RO       */
    } bits_66;
    uint16_t word_66;
  } u66;
  /*! \brief Union for bit and word level access of word 67 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F1.7:0 RO Vendor Reserved 0xF1 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u67.bits_67.vendorReserved_0xf1

                        
  */
      unsigned int   vendorReserved_0xf1 : 8;    /* 01.80F1.7:0  RO       */
    } bits_67;
    uint16_t word_67;
  } u67;
  /*! \brief Union for bit and word level access of word 68 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F2.7:0 RO Vendor Reserved 0xF2 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u68.bits_68.vendorReserved_0xf2

                        
  */
      unsigned int   vendorReserved_0xf2 : 8;    /* 01.80F2.7:0  RO       */
    } bits_68;
    uint16_t word_68;
  } u68;
  /*! \brief Union for bit and word level access of word 69 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F3.7:0 RO Vendor Reserved 0xF3 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u69.bits_69.vendorReserved_0xf3

                        
  */
      unsigned int   vendorReserved_0xf3 : 8;    /* 01.80F3.7:0  RO       */
    } bits_69;
    uint16_t word_69;
  } u69;
  /*! \brief Union for bit and word level access of word 70 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F4.7:0 RO Vendor Reserved 0xF4 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u70.bits_70.vendorReserved_0xf4

                        
  */
      unsigned int   vendorReserved_0xf4 : 8;    /* 01.80F4.7:0  RO       */
    } bits_70;
    uint16_t word_70;
  } u70;
  /*! \brief Union for bit and word level access of word 71 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F5.7:0 RO Vendor Reserved 0xF5 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u71.bits_71.vendorReserved_0xf5

                        
  */
      unsigned int   vendorReserved_0xf5 : 8;    /* 01.80F5.7:0  RO       */
    } bits_71;
    uint16_t word_71;
  } u71;
  /*! \brief Union for bit and word level access of word 72 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F6.7:0 RO Vendor Reserved 0xF6 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u72.bits_72.vendorReserved_0xf6

                        
  */
      unsigned int   vendorReserved_0xf6 : 8;    /* 01.80F6.7:0  RO       */
    } bits_72;
    uint16_t word_72;
  } u72;
  /*! \brief Union for bit and word level access of word 73 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F7.7:0 RO Vendor Reserved 0xF7 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u73.bits_73.vendorReserved_0xf7

                        
  */
      unsigned int   vendorReserved_0xf7 : 8;    /* 01.80F7.7:0  RO       */
    } bits_73;
    uint16_t word_73;
  } u73;
  /*! \brief Union for bit and word level access of word 74 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F8.7:0 RO Vendor Reserved 0xF8 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u74.bits_74.vendorReserved_0xf8

                        
  */
      unsigned int   vendorReserved_0xf8 : 8;    /* 01.80F8.7:0  RO       */
    } bits_74;
    uint16_t word_74;
  } u74;
  /*! \brief Union for bit and word level access of word 75 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80F9.7:0 RO Vendor Reserved 0xF9 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u75.bits_75.vendorReserved_0xf9

                        
  */
      unsigned int   vendorReserved_0xf9 : 8;    /* 01.80F9.7:0  RO       */
    } bits_75;
    uint16_t word_75;
  } u75;
  /*! \brief Union for bit and word level access of word 76 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80FA.7:0 RO Vendor Reserved 0xFA [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u76.bits_76.vendorReserved_0xfa

                        
  */
      unsigned int   vendorReserved_0xfa : 8;    /* 01.80FA.7:0  RO       */
    } bits_76;
    uint16_t word_76;
  } u76;
  /*! \brief Union for bit and word level access of word 77 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80FB.7:0 RO Vendor Reserved 0xFB [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u77.bits_77.vendorReserved_0xfb

                        
  */
      unsigned int   vendorReserved_0xfb : 8;    /* 01.80FB.7:0  RO       */
    } bits_77;
    uint16_t word_77;
  } u77;
  /*! \brief Union for bit and word level access of word 78 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80FC.7:0 RO Vendor Reserved 0xFC [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u78.bits_78.vendorReserved_0xfc

                        
  */
      unsigned int   vendorReserved_0xfc : 8;    /* 01.80FC.7:0  RO       */
    } bits_78;
    uint16_t word_78;
  } u78;
  /*! \brief Union for bit and word level access of word 79 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80FD.7:0 RO Vendor Reserved 0xFD [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u79.bits_79.vendorReserved_0xfd

                        
  */
      unsigned int   vendorReserved_0xfd : 8;    /* 01.80FD.7:0  RO       */
    } bits_79;
    uint16_t word_79;
  } u79;
  /*! \brief Union for bit and word level access of word 80 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80FE.7:0 RO Vendor Reserved 0xFE [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u80.bits_80.vendorReserved_0xfe

                        
  */
      unsigned int   vendorReserved_0xfe : 8;    /* 01.80FE.7:0  RO       */
    } bits_80;
    uint16_t word_80;
  } u80;
  /*! \brief Union for bit and word level access of word 81 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.80FF.7:0 RO Vendor Reserved 0xFF [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u81.bits_81.vendorReserved_0xff

                        
  */
      unsigned int   vendorReserved_0xff : 8;    /* 01.80FF.7:0  RO       */
    } bits_81;
    uint16_t word_81;
  } u81;
  /*! \brief Union for bit and word level access of word 82 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8100.7:0 RO Vendor Reserved 0x100 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u82.bits_82.vendorReserved_0x100

                        
  */
      unsigned int   vendorReserved_0x100 : 8;    /* 01.8100.7:0  RO       */
    } bits_82;
    uint16_t word_82;
  } u82;
  /*! \brief Union for bit and word level access of word 83 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8101.7:0 RO Vendor Reserved 0x101 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u83.bits_83.vendorReserved_0x101

                        
  */
      unsigned int   vendorReserved_0x101 : 8;    /* 01.8101.7:0  RO       */
    } bits_83;
    uint16_t word_83;
  } u83;
  /*! \brief Union for bit and word level access of word 84 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8102.7:0 RO Vendor Reserved 0x102 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u84.bits_84.vendorReserved_0x102

                        
  */
      unsigned int   vendorReserved_0x102 : 8;    /* 01.8102.7:0  RO       */
    } bits_84;
    uint16_t word_84;
  } u84;
  /*! \brief Union for bit and word level access of word 85 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8103.7:0 RO Vendor Reserved 0x103 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u85.bits_85.vendorReserved_0x103

                        
  */
      unsigned int   vendorReserved_0x103 : 8;    /* 01.8103.7:0  RO       */
    } bits_85;
    uint16_t word_85;
  } u85;
  /*! \brief Union for bit and word level access of word 86 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8104.7:0 RO Vendor Reserved 0x104 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u86.bits_86.vendorReserved_0x104

                        
  */
      unsigned int   vendorReserved_0x104 : 8;    /* 01.8104.7:0  RO       */
    } bits_86;
    uint16_t word_86;
  } u86;
  /*! \brief Union for bit and word level access of word 87 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8105.7:0 RO Vendor Reserved 0x105 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u87.bits_87.vendorReserved_0x105

                        
  */
      unsigned int   vendorReserved_0x105 : 8;    /* 01.8105.7:0  RO       */
    } bits_87;
    uint16_t word_87;
  } u87;
  /*! \brief Union for bit and word level access of word 88 of XENPAK Vendor - Reserved 0xAE */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.8106.7:0 RO Vendor Reserved 0x106 [7:0]
                        AQ_XenpakVendor_Reserved_0xae_EUR.u88.bits_88.vendorReserved_0x106

                        
  */
      unsigned int   vendorReserved_0x106 : 8;    /* 01.8106.7:0  RO       */
    } bits_88;
    uint16_t word_88;
  } u88;
} AQ_XenpakVendor_Reserved_0xae_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Rx_Alarm - Control: 01.9000 */
/*                  XENPAK Rx_Alarm - Control: 01.9000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Rx_Alarm - Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 01.9000.5 R/WPD Reserved 1
                        AQ_XenpakRxAlarm_Control_EUR.u0.bits_0.reserved_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_1 : 1;    /* 01.9000.5  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 01.9000.4 R/WPD PMA Receive Fault Enable
                        AQ_XenpakRxAlarm_Control_EUR.u0.bits_0.pmaReceiveFaultEnable

                        Provisionable Default = 0x1

                        Setting this bit high enables generation of interrupts on PMA Receive Fault

                 <B>Notes:</B>
                        This bit is mirrored to 1E.C473.2
                        
                        Note F/W performs mirror. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   pmaReceiveFaultEnable : 1;    /* 01.9000.4  R/WPD      Provisionable Default = 0x1 */
                     /* Setting this bit high enables generation of interrupts on PMA Receive Fault  */
                    /*! \brief 01.9000.3 R/WPD PCS Receive Fault Enable
                        AQ_XenpakRxAlarm_Control_EUR.u0.bits_0.pcsReceiveFaultEnable

                        Provisionable Default = 0x1

                        Setting this bit high enables generation of interrupts on PCS Receive Fault

                 <B>Notes:</B>
                        This bit is mirrored to 1E.C473.1
                        
                        Note F/W performs mirror. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   pcsReceiveFaultEnable : 1;    /* 01.9000.3  R/WPD      Provisionable Default = 0x1 */
                     /* Setting this bit high enables generation of interrupts on PCS Receive Fault  */
      unsigned int   reserved1 : 2;
                    /*! \brief 01.9000.0 R/WPD PHY XS Receive Fault Enable
                        AQ_XenpakRxAlarm_Control_EUR.u0.bits_0.phyXS_ReceiveFaultEnable

                        Provisionable Default = 0x1

                        Setting this bit high enables generation of interrupts on PHY XS Receive Fault

                 <B>Notes:</B>
                        This bit is mirrored to 1E.C473.0
                        
                        Note F/W performs mirror. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   phyXS_ReceiveFaultEnable : 1;    /* 01.9000.0  R/WPD      Provisionable Default = 0x1 */
                     /* Setting this bit high enables generation of interrupts on PHY XS Receive Fault  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakRxAlarm_Control_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Tx_Alarm - Control: 01.9001 */
/*                  XENPAK Tx_Alarm - Control: 01.9001 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Tx_Alarm - Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 01.9001.8 R/WPD Temperature Fault Enable
                        AQ_XenpakTxAlarm_Control_EUR.u0.bits_0.temperatureFaultEnable

                        Provisionable Default = 0x0

                        Setting this bit high enables generation of interrupts on Temperature Fault

                 <B>Notes:</B>
                        Setting this bit enables the generation of interrupt for the temperature high and low alarms (1.A070.7:6). The generation of interrupt for the temperature high and low warnings is not supported.  */
      unsigned int   temperatureFaultEnable : 1;    /* 01.9001.8  R/WPD      Provisionable Default = 0x0 */
                     /* Setting this bit high enables generation of interrupts on Temperature Fault  */
      unsigned int   reserved1 : 1;
                    /*! \brief 01.9001.6 R/WPD Reserved 1
                        AQ_XenpakTxAlarm_Control_EUR.u0.bits_0.reserved_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_1 : 1;    /* 01.9001.6  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 01.9001.4 R/WPD PMA Transmit Fault Enable
                        AQ_XenpakTxAlarm_Control_EUR.u0.bits_0.pmaTransmitFaultEnable

                        Provisionable Default = 0x1

                        Setting this bit high enables generation of interrupts on PMA Transmit Fault
  */
      unsigned int   pmaTransmitFaultEnable : 1;    /* 01.9001.4  R/WPD      Provisionable Default = 0x1 */
                     /* Setting this bit high enables generation of interrupts on PMA Transmit Fault  */
                    /*! \brief 01.9001.3 R/WPD PCS Transmit Fault Enable
                        AQ_XenpakTxAlarm_Control_EUR.u0.bits_0.pcsTransmitFaultEnable

                        Provisionable Default = 0x1

                        Setting this bit high enables generation of interrupts on PCS Transmit Fault
  */
      unsigned int   pcsTransmitFaultEnable : 1;    /* 01.9001.3  R/WPD      Provisionable Default = 0x1 */
                     /* Setting this bit high enables generation of interrupts on PCS Transmit Fault  */
      unsigned int   reserved3 : 2;
                    /*! \brief 01.9001.0 R/WPD PHY XS Transmit Fault Enable
                        AQ_XenpakTxAlarm_Control_EUR.u0.bits_0.phyXS_TransmitFaultEnable

                        Provisionable Default = 0x1

                        Setting this bit high enables generation of interrupts on PHY XS Transmit Fault
  */
      unsigned int   phyXS_TransmitFaultEnable : 1;    /* 01.9001.0  R/WPD      Provisionable Default = 0x1 */
                     /* Setting this bit high enables generation of interrupts on PHY XS Transmit Fault  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakTxAlarm_Control_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK LASI - Control: 01.9002 */
/*                  XENPAK LASI - Control: 01.9002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK LASI - Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 01.9002.2 R/WPD Rx Alarm Enable
                        AQ_XenpakLASI__Control_EUR.u0.bits_0.rxAlarmEnable

                        Provisionable Default = 0x0

                        Setting this bit high enables generation of interrupts on Rx Fault
                        

                 <B>Notes:</B>
                        This bit is copied to 1E.C473.6
                        
                        Note F/W performs the copy. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   rxAlarmEnable : 1;    /* 01.9002.2  R/WPD      Provisionable Default = 0x0 */
                     /* Setting this bit high enables generation of interrupts on Rx Fault
                          */
                    /*! \brief 01.9002.1 R/WPD Tx Alarm Enable
                        AQ_XenpakLASI__Control_EUR.u0.bits_0.txAlarmEnable

                        Provisionable Default = 0x0

                        Setting this bit high enables generation of interrupts on Tx Fault
                        

                 <B>Notes:</B>
                        This bit is copied to 1E.C473.5
                        
                        Note F/W performs the copy. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   txAlarmEnable : 1;    /* 01.9002.1  R/WPD      Provisionable Default = 0x0 */
                     /* Setting this bit high enables generation of interrupts on Tx Fault
                          */
                    /*! \brief 01.9002.0 R/WPD Link Status Alarm Enable
                        AQ_XenpakLASI__Control_EUR.u0.bits_0.linkStatusAlarmEnable

                        Provisionable Default = 0x0

                        Setting this bit high enables generation of interrupts on Link Status Change
                        

                 <B>Notes:</B>
                        This enables the generation of interrupts on link status change. Specifically if the AND of 1.A.0, 3.20.0, and 4.18.C changes, an alarm is generated.
                        
                        This bit is copied to 1E.C473.4
                        
                        Note F/W performs copy. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   linkStatusAlarmEnable : 1;    /* 01.9002.0  R/WPD      Provisionable Default = 0x0 */
                     /* Setting this bit high enables generation of interrupts on Link Status Change
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakLASI__Control_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Rx_Alarm - Status: 01.9003 */
/*                  XENPAK Rx_Alarm - Status: 01.9003 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Rx_Alarm - Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 01.9003.5 LH Reserved 1
                        AQ_XenpakRxAlarm_Status_EUR.u0.bits_0.reserved_1

                        

                        Reserved for future use
                        
  */
      unsigned int   reserved_1 : 1;    /* 01.9003.5  LH       */
                     /* Reserved for future use
                          */
                    /*! \brief 01.9003.4 LH PMA Receive Fault
                        AQ_XenpakRxAlarm_Status_EUR.u0.bits_0.pmaReceiveFault

                        

                        1 = PMA Receive Fault
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if bit 1.8.A is set.
                        
                        This bit is automatically mirrored by H/W to 1.8.B, i.e. if 1.8.B is cleared, this bit will be automatically cleared and vice versa.  */
      unsigned int   pmaReceiveFault : 1;    /* 01.9003.4  LH       */
                     /* 1 = PMA Receive Fault
                          */
                    /*! \brief 01.9003.3 LH PCS Receive Fault
                        AQ_XenpakRxAlarm_Status_EUR.u0.bits_0.pcsReceiveFault

                        

                        1 = PCS Receive Fault
                        
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if bit 3.8.A is set.
                        
                        This bit is automatically mirrored by H/W to 1.8.B, i.e. if 1.8.B is cleared, this bit will be automatically cleared and vice versa.  */
      unsigned int   pcsReceiveFault : 1;    /* 01.9003.3  LH       */
                     /* 1 = PCS Receive Fault
                        
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 01.9003.0 LH PHY XS Receive Fault
                        AQ_XenpakRxAlarm_Status_EUR.u0.bits_0.phyXS_ReceiveFault

                        

                        1 = PHY XS Receive Fault
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if bit 4.8.A is set.
                        
                        This bit is automatically mirrored by H/W to 1.8.B, i.e. if 1.8.B is cleared, this bit will be automatically cleared and vice versa.  */
      unsigned int   phyXS_ReceiveFault : 1;    /* 01.9003.0  LH       */
                     /* 1 = PHY XS Receive Fault
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakRxAlarm_Status_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK Tx_Alarm - Status: 01.9004 */
/*                  XENPAK Tx_Alarm - Status: 01.9004 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK Tx_Alarm - Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 01.9004.8 LH Temperature Fault
                        AQ_XenpakTxAlarm_Status_EUR.u0.bits_0.temperatureFault

                        

                        1 = Temperature Fault
                        

                 <B>Notes:</B>
                        This bit is set if either a high or low temperature alarm (1.A070.7:6) is set and the corresponding temperature interrupt enable (1.900.7:6) is set.
                        
                        This bit reverts to RO behavior if bit 1E.C441.1 is set.  */
      unsigned int   temperatureFault : 1;    /* 01.9004.8  LH       */
                     /* 1 = Temperature Fault
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 01.9004.6 LH Reserved 1
                        AQ_XenpakTxAlarm_Status_EUR.u0.bits_0.reserved_1

                        

                        Reserved for future use
                        
  */
      unsigned int   reserved_1 : 1;    /* 01.9004.6  LH       */
                     /* Reserved for future use
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 01.9004.4 LH PMA Transmit Fault
                        AQ_XenpakTxAlarm_Status_EUR.u0.bits_0.pmaTransmitFault

                        

                        1 = PMA Transmit Fault
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if bit 1.8.B is set.
                        
                        This bit is automatically mirrored by H/W to 1.8.B, i.e. if 1.8.B is cleared, this bit will be automatically cleared and vice versa.  */
      unsigned int   pmaTransmitFault : 1;    /* 01.9004.4  LH       */
                     /* 1 = PMA Transmit Fault
                          */
                    /*! \brief 01.9004.3 LH PCS Transmit Fault
                        AQ_XenpakTxAlarm_Status_EUR.u0.bits_0.pcsTransmitFault

                        

                        1 = PCS Transmit Fault
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if bit 3.8.B is set.
                        
                        This bit is automatically mirrored by H/W to 1.8.B, i.e. if 1.8.B is cleared, this bit will be automatically cleared and vice versa.  */
      unsigned int   pcsTransmitFault : 1;    /* 01.9004.3  LH       */
                     /* 1 = PCS Transmit Fault
                          */
      unsigned int   reserved3 : 2;
                    /*! \brief 01.9004.0 LH PHY XS Transmit Fault
                        AQ_XenpakTxAlarm_Status_EUR.u0.bits_0.phyXS_TransmitFault

                        

                        1 = PHY XS Transmit Fault
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if bit 4.8.B is set.
                        
                        This bit is automatically mirrored by H/W to 1.8.B, i.e. if 1.8.B is cleared, this bit will be automatically cleared and vice versa.  */
      unsigned int   phyXS_TransmitFault : 1;    /* 01.9004.0  LH       */
                     /* 1 = PHY XS Transmit Fault
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakTxAlarm_Status_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK LASI - Status: 01.9005 */
/*                  XENPAK LASI - Status: 01.9005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK LASI - Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 01.9005.2 RO Rx Alarm
                        AQ_XenpakLASI__Status_EUR.u0.bits_0.rxAlarm

                        

                        1 = Rx Fault
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if any of the Rx fault bits (1.9003.0, 1.9003.3, or 1.9003.4) are set and mask is enabled.  */
      unsigned int   rxAlarm : 1;    /* 01.9005.2  RO       */
                     /* 1 = Rx Fault
                          */
                    /*! \brief 01.9005.1 RO Tx Alarm
                        AQ_XenpakLASI__Status_EUR.u0.bits_0.txAlarm

                        

                        1 = Tx Fault
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if any of the Tx fault bits (1.9004.0, 1.9004.3, or 1.9004.4) are set and mask is enabled.
                          */
      unsigned int   txAlarm : 1;    /* 01.9005.1  RO       */
                     /* 1 = Tx Fault
                          */
                    /*! \brief 01.9005.0 LRF Link Status Alarm
                        AQ_XenpakLASI__Status_EUR.u0.bits_0.linkStatusAlarm

                        

                        1 = Link Status Change
                        

                 <B>Notes:</B>
                        This bit is automatically set by H/W if the AND of 1.A.0, 3.20.0, and 4.18.C has changed state (i.e. this bit is set if a rising or falling edge is detected on the AND).  */
      unsigned int   linkStatusAlarm : 1;    /* 01.9005.0  LRF       */
                     /* 1 = Link Status Change
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakLASI__Status_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Tx Control: 01.9006 */
/*                  XENPAK DOM - Tx Control: 01.9006 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Tx Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.9006.7 R/WPD High Temperature Alarm Enable
                        AQ_XenpakDom_TxControl_EUR.u0.bits_0.highTemperatureAlarmEnable

                        Provisionable Default = 0x0

                        Setting this bit high enables generation of alarms on the temperature exceeding the high temperature threshold.
                        

                 <B>Notes:</B>
                        This enables the generation of interrupt for the high temperature alarm. The generation for high temperature warning is not supported.  */
      unsigned int   highTemperatureAlarmEnable : 1;    /* 01.9006.7  R/WPD      Provisionable Default = 0x0 */
                     /* Setting this bit high enables generation of alarms on the temperature exceeding the high temperature threshold.
                          */
                    /*! \brief 01.9006.6 R/WPD Low Temperature Alarm Enable
                        AQ_XenpakDom_TxControl_EUR.u0.bits_0.lowTemperatureAlarmEnable

                        Provisionable Default = 0x0

                        Setting this bit high enables generation of alarms on the temperature exceeding the low temperature threshold.
                        

                 <B>Notes:</B>
                        This enables the generation of interrupt for the low temperature alarm. The generation for low temperature warning is not supported.  */
      unsigned int   lowTemperatureAlarmEnable : 1;    /* 01.9006.6  R/WPD      Provisionable Default = 0x0 */
                     /* Setting this bit high enables generation of alarms on the temperature exceeding the low temperature threshold.
                          */
      unsigned int   reserved1 : 6;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_TxControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - High Temperature Alarm Threshold LSW: 01.A000 */
/*                  XENPAK DOM - High Temperature Alarm Threshold LSW: 01.A000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - High Temperature Alarm Threshold LSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A000.7:0 R/WPD High Temp Threshold [7:0]
                        AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_EUR.u0.bits_0.highTempThreshold

                        Provisionable Default = 0x00

                        [7:0] of high temperature
                        

                 <B>Notes:</B>
                        In XENPAK mode, F/W will use 1.A000 and 1.A001 registers instead of 1E.C421.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD8. Default is 70 degreesC.  */
      unsigned int   highTempThreshold : 8;    /* 01.A000.7:0  R/WPD      Provisionable Default = 0x00 */
                     /* [7:0] of high temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_HighTemperatureAlarmThresholdLSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - High Temperature Alarm Threshold MSW: 01.A001 */
/*                  XENPAK DOM - High Temperature Alarm Threshold MSW: 01.A001 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - High Temperature Alarm Threshold MSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A001.7:0 R/WPD High Temp Threshold [F:8]
                        AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_EUR.u0.bits_0.highTempThreshold

                        Provisionable Default = 0x46

                        [F:8] of high temperature
                        

                 <B>Notes:</B>
                        In XENPAK mode, F/W will use 1.A000 and 1.A001 registers instead of 1E.C421.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD8. Default is 70 degreesC.  */
      unsigned int   highTempThreshold : 8;    /* 01.A001.7:0  R/WPD      Provisionable Default = 0x46 */
                     /* [F:8] of high temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_HighTemperatureAlarmThresholdMSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Low Temperature Alarm Threshold LSW: 01.A002 */
/*                  XENPAK DOM - Low Temperature Alarm Threshold LSW: 01.A002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Low Temperature Alarm Threshold LSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A002.7:0 R/WPD Low Temp Threshold [7:0]
                        AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_EUR.u0.bits_0.lowTempThreshold

                        Provisionable Default = 0x00

                        [7:0] of low temperature
                        

                 <B>Notes:</B>
                        In XENPAK mode, F/W will use 1.A002 and 1.A003 registers instead of 1E.C422.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD800. Default is 0 degreesC.  */
      unsigned int   lowTempThreshold : 8;    /* 01.A002.7:0  R/WPD      Provisionable Default = 0x00 */
                     /* [7:0] of low temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_LowTemperatureAlarmThresholdLSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Low Temperature Alarm Threshold MSW: 01.A003 */
/*                  XENPAK DOM - Low Temperature Alarm Threshold MSW: 01.A003 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Low Temperature Alarm Threshold MSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A003.7:0 R/WPD Low Temp Threshold [F:8]
                        AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_EUR.u0.bits_0.lowTempThreshold

                        Provisionable Default = 0x00

                        [F:8] of low temperature
                        

                 <B>Notes:</B>
                        In XENPAK mode, F/W will use 1.A002 and 1.A003 registers instead of 1E.C422.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD800. Default is 0 degreesC.  */
      unsigned int   lowTempThreshold : 8;    /* 01.A003.7:0  R/WPD      Provisionable Default = 0x00 */
                     /* [F:8] of low temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_LowTemperatureAlarmThresholdMSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - High Temperature Warning Threshold LSW: 01.A004 */
/*                  XENPAK DOM - High Temperature Warning Threshold LSW: 01.A004 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - High Temperature Warning Threshold LSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A004.7:0 R/WPD High Temp Warning Threshold [7:0]
                        AQ_XenpakDom_HighTemperatureWarningThresholdLSW_EUR.u0.bits_0.highTempWarningThreshold

                        Provisionable Default = 0x00

                        [7:0] of high temperature
                        

                 <B>Notes:</B>
                        In XENPAK mode, F/W will use 1.A004 and 1.A005 registers instead of 1E.C423.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD800. Default is 60 degreesC.  */
      unsigned int   highTempWarningThreshold : 8;    /* 01.A004.7:0  R/WPD      Provisionable Default = 0x00 */
                     /* [7:0] of high temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_HighTemperatureWarningThresholdLSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - High Temperature Warning Threshold MSW: 01.A005 */
/*                  XENPAK DOM - High Temperature Warning Threshold MSW: 01.A005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - High Temperature Warning Threshold MSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A005.7:0 R/WPD High Temp Warning Threshold [F:8]
                        AQ_XenpakDom_HighTemperatureWarningThresholdMSW_EUR.u0.bits_0.highTempWarningThreshold

                        Provisionable Default = 0x3C

                        [F:8] of high temperature
                        

                 <B>Notes:</B>
                        In XENPAK mode, F/W will use 1.A004 and 1.A005 registers instead of 1E.C423.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD800. Default is 60 degreesC.  */
      unsigned int   highTempWarningThreshold : 8;    /* 01.A005.7:0  R/WPD      Provisionable Default = 0x3C */
                     /* [F:8] of high temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_HighTemperatureWarningThresholdMSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Low Temperature Warning Threshold LSW: 01.A006 */
/*                  XENPAK DOM - Low Temperature Warning Threshold LSW: 01.A006 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Low Temperature Warning Threshold LSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A006.7:0 R/WPD Low Temp Warning Threshold [7:0]
                        AQ_XenpakDom_LowTemperatureWarningThresholdLSW_EUR.u0.bits_0.lowTempWarningThreshold

                        Provisionable Default = 0x00

                        [7:0] of low temperature
                        

                 <B>Notes:</B>
                        In XENPAK mode, F/W will use 1.A006 and 1.A007 registers instead of 1E.C424.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD800. Default is 10 degreesC.  */
      unsigned int   lowTempWarningThreshold : 8;    /* 01.A006.7:0  R/WPD      Provisionable Default = 0x00 */
                     /* [7:0] of low temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_LowTemperatureWarningThresholdLSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Low Temperature Warning Threshold MSW: 01.A007 */
/*                  XENPAK DOM - Low Temperature Warning Threshold MSW: 01.A007 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Low Temperature Warning Threshold MSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A007.7:0 R/WPD Low Temp Warning Threshold [F:8]
                        AQ_XenpakDom_LowTemperatureWarningThresholdMSW_EUR.u0.bits_0.lowTempWarningThreshold

                        Provisionable Default = 0x0A

                        [F:8] of low temperature
                        

                 <B>Notes:</B>
                        In XENPAK mode, F/W will use 1.A006 and 1.A007 registers instead of 1E.C424.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD800. Default is 10 degreesC.  */
      unsigned int   lowTempWarningThreshold : 8;    /* 01.A007.7:0  R/WPD      Provisionable Default = 0x0A */
                     /* [F:8] of low temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_LowTemperatureWarningThresholdMSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Temperature LSW: 01.A060 */
/*                  XENPAK DOM - Temperature LSW: 01.A060 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Temperature LSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A060.7:0 RO Temperature [7:0]
                        AQ_XenpakDom_TemperatureLSW_EUR.u0.bits_0.temperature

                        

                        [7:0] of temperature
                        

                 <B>Notes:</B>
                        1.A060 and 1.A061 combine to form the 16-bit temperature. This register is connected to and driven by the register 1E.C820.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD800.  */
      unsigned int   temperature : 8;    /* 01.A060.7:0  RO       */
                     /* [7:0] of temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_TemperatureLSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Temperature MSW: 01.A061 */
/*                  XENPAK DOM - Temperature MSW: 01.A061 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Temperature MSW */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A061.7:0 RO Temperature [F:8]
                        AQ_XenpakDom_TemperatureMSW_EUR.u0.bits_0.temperature

                        

                        [F:8] of temperature
                        

                 <B>Notes:</B>
                        1.A060 and 1.A061 combine to form the 16-bit temperature. This register is connected to and driven by the output of 1E.C820.
                        
                        2's complement value with the LSB representing 1/256 of a degree Celsius. This corresponds to -40 degreesC = 0xD800.  */
      unsigned int   temperature : 8;    /* 01.A061.7:0  RO       */
                     /* [F:8] of temperature
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_TemperatureMSW_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Status: 01.A06E */
/*                  XENPAK DOM - Status: 01.A06E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 01.A06E.0 RO Temperature Ready
                        AQ_XenpakDom_Status_EUR.u0.bits_0.temperatureReady

                        

                        1 = temperature measurement is valid
                        

                 <B>Notes:</B>
                        This register is connected to and driven by the register 1E.C821.  */
      unsigned int   temperatureReady : 1;    /* 01.A06E.0  RO       */
                     /* 1 = temperature measurement is valid
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_Status_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Capability: 01.A06F */
/*                  XENPAK DOM - Capability: 01.A06F */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Capability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A06F.7 ROS Temperature Capability
                        AQ_XenpakDom_Capability_EUR.u0.bits_0.temperatureCapability

                        Default = 0x1

                        1 = device supports temperature measurement capability
  */
      unsigned int   temperatureCapability : 1;    /* 01.A06F.7  ROS      Default = 0x1 */
                     /* 1 = device supports temperature measurement capability  */
      unsigned int   reserved1 : 7;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_XenpakDom_Capability_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                XENPAK DOM - Alarms: 01.A070 */
/*                  XENPAK DOM - Alarms: 01.A070 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of XENPAK DOM - Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A070.7 LH High Temperature Alarm
                        AQ_XenpakDom_Alarms_EUR.u0.bits_0.highTemperatureAlarm

                        

                        1 = High temperature alarm
                        

                 <B>Notes:</B>
                        This register is set when the temperature in register (1.A060 and 1.A061) is greater than the high temperature alarm threshold (1.A000 and 1.A001).
                        
                        Note this bit is set by F/W.  */
      unsigned int   highTemperatureAlarm : 1;    /* 01.A070.7  LH       */
                     /* 1 = High temperature alarm
                          */
                    /*! \brief 01.A070.6 LH Low Temperature Alarm
                        AQ_XenpakDom_Alarms_EUR.u0.bits_0.lowTemperatureAlarm

                        

                        1 = Low temperature alarm
                        

                 <B>Notes:</B>
                        This register is set when the temperature in register (1.A060 and 1.A061) is less than the high temperature alarm threshold (1.A002 and 1.A003).
                        
                        Note this bit is set by F/W.  */
      unsigned int   lowTemperatureAlarm : 1;    /* 01.A070.6  LH       */
                     /* 1 = Low temperature alarm
                          */
      unsigned int   reserved1 : 6;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of XENPAK DOM - Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of XENPAK DOM - Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of XENPAK DOM - Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of XENPAK DOM - Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 01.A074.7 LH High Temperature Warning
                        AQ_XenpakDom_Alarms_EUR.u4.bits_4.highTemperatureWarning

                        

                        1 = High temperature warning
                        

                 <B>Notes:</B>
                        This register is set when the temperature in register (1.A060 and 1.A061) is greater than the high temperature alarm threshold (1.A003 and 1.A005).
                        
                        Note this bit is set by F/W.  */
      unsigned int   highTemperatureWarning : 1;    /* 01.A074.7  LH       */
                     /* 1 = High temperature warning
                          */
                    /*! \brief 01.A074.6 LH Low Temperature Warning
                        AQ_XenpakDom_Alarms_EUR.u4.bits_4.lowTemperatureWarning

                        

                        1 = Low temperature warning
                        

                 <B>Notes:</B>
                        This register is set when the temperature in register (1.A060 and 1.A061) is less than the high temperature alarm threshold (1.A006 and 1.A007).
                        
                        Note this bit is set by F/W.  */
      unsigned int   lowTemperatureWarning : 1;    /* 01.A074.6  LH       */
                     /* 1 = Low temperature warning
                          */
      unsigned int   reserved1 : 6;
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_XenpakDom_Alarms_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Transmit Clock Phase Selection Control: 01.C142 */
/*                  PMA Transmit Clock Phase Selection Control: 01.C142 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Transmit Clock Phase Selection Control */
  union
  {
    struct
    {
                    /*! \brief 01.C142.F:C ROPD Channel 3 Tx Clock Phase Selection [3:0]
                        AQ_PmaTransmitClockPhaseSelectionControl_EUR.u0.bits_0.channel_3TxClockPhaseSelection

                        Provisionable Default = 0xE

                        Channel 3 Tx clock phase selection
                        RTL_PIF_END="afe10gblk.pif_clkdelay_txphsel_ch3_i"

                 <B>Notes:</B>
                        Asynchronous phase select for gmux clock for TXDAC. Lower 3 bits used for selecting 1 out of 8 phases in 10G/AQrate mode. All 4 bits used to select 1 of 16 phases in 1G mode. Phase separation is 45 deg in 10G/AQrate mode. Phase separation is 22.5 deg in 1G mode.
                        
                        The defaults indicated here is in Binary but will be converted to Gray code in H/W. Here is the Binary to Gray code LUT:
                        Binary     Gray
                        0000        1111 => 0 deg
                        0001        1110 => 22.5deg
                        0010        1100 => 45 deg
                        0011        1101 => 67.5 deg
                        0100        1001 => 90 deg
                        0101        1000 => 112.5 deg
                        0110        1010 => 135 deg
                        0111        1011 => 157.5 deg
                        1000        0011 => 180 deg
                        1001        0010 => 202.5 deg
                        1010        0000 => 225 deg
                        1011        0001 => 247.5 deg
                        1100        0101 => 270 deg
                        1101        0100 => 292.5 deg
                        1110        0110 => 315 deg
                        1111        0111 => 337.5 deg  */
      unsigned int   channel_3TxClockPhaseSelection : 4;    /* 01.C142.F:C  ROPD      Provisionable Default = 0xE */
                     /* Channel 3 Tx clock phase selection
                        RTL_PIF_END="afe10gblk.pif_clkdelay_txphsel_ch3_i"  */
                    /*! \brief 01.C142.B:8 ROPD Channel 2 Tx Clock Phase Selection [3:0]
                        AQ_PmaTransmitClockPhaseSelectionControl_EUR.u0.bits_0.channel_2TxClockPhaseSelection

                        Provisionable Default = 0xA

                        Channel 2 Tx clock phase selection
                        RTL_PIF_END="afe10gblk.pif_clkdelay_txphsel_ch2_i"

                 <B>Notes:</B>
                        Asynchronous phase select for gmux clock for TXDAC. Lower 3 bits used for selecting 1 out of 8 phases in 10G/AQrate mode. All 4 bits used to select 1 of 16 phases in 1G mode. Phase separation is 45 deg in 10G/AQrate mode. Phase separation is 22.5 deg in 1G mode.
                        
                        The defaults indicated here is in Binary but will be converted to Gray code in H/W. Here is the Binary to Gray code LUT:
                        Binary     Gray
                        0000        1111 => 0 deg
                        0001        1110 => 22.5deg
                        0010        1100 => 45 deg
                        0011        1101 => 67.5 deg
                        0100        1001 => 90 deg
                        0101        1000 => 112.5 deg
                        0110        1010 => 135 deg
                        0111        1011 => 157.5 deg
                        1000        0011 => 180 deg
                        1001        0010 => 202.5 deg
                        1010        0000 => 225 deg
                        1011        0001 => 247.5 deg
                        1100        0101 => 270 deg
                        1101        0100 => 292.5 deg
                        1110        0110 => 315 deg
                        1111        0111 => 337.5 deg  */
      unsigned int   channel_2TxClockPhaseSelection : 4;    /* 01.C142.B:8  ROPD      Provisionable Default = 0xA */
                     /* Channel 2 Tx clock phase selection
                        RTL_PIF_END="afe10gblk.pif_clkdelay_txphsel_ch2_i"  */
                    /*! \brief 01.C142.7:4 ROPD Channel 1 Tx Clock Phase Selection [3:0]
                        AQ_PmaTransmitClockPhaseSelectionControl_EUR.u0.bits_0.channel_1TxClockPhaseSelection

                        Provisionable Default = 0x6

                        Channel 1 Tx clock phase selection
                        RTL_PIF_END="afe10gblk.pif_clkdelay_txphsel_ch1_i"

                 <B>Notes:</B>
                        Asynchronous phase select for gmux clock for TXDAC. Lower 3 bits used for selecting 1 out of 8 phases in 10G/AQrate mode. All 4 bits used to select 1 of 16 phases in 1G mode. Phase separation is 45 deg in 10G/AQrate mode. Phase separation is 22.5 deg in 1G mode.
                        
                        The defaults indicated here is in Binary but will be converted to Gray code in H/W. Here is the Binary to Gray code LUT:
                        Binary     Gray
                        0000        1111 => 0 deg
                        0001        1110 => 22.5deg
                        0010        1100 => 45 deg
                        0011        1101 => 67.5 deg
                        0100        1001 => 90 deg
                        0101        1000 => 112.5 deg
                        0110        1010 => 135 deg
                        0111        1011 => 157.5 deg
                        1000        0011 => 180 deg
                        1001        0010 => 202.5 deg
                        1010        0000 => 225 deg
                        1011        0001 => 247.5 deg
                        1100        0101 => 270 deg
                        1101        0100 => 292.5 deg
                        1110        0110 => 315 deg
                        1111        0111 => 337.5 deg  */
      unsigned int   channel_1TxClockPhaseSelection : 4;    /* 01.C142.7:4  ROPD      Provisionable Default = 0x6 */
                     /* Channel 1 Tx clock phase selection
                        RTL_PIF_END="afe10gblk.pif_clkdelay_txphsel_ch1_i"  */
                    /*! \brief 01.C142.3:0 ROPD Channel 0 Tx Clock Phase Selection [3:0]
                        AQ_PmaTransmitClockPhaseSelectionControl_EUR.u0.bits_0.channel_0TxClockPhaseSelection

                        Provisionable Default = 0x2

                        Channel 0 Tx clock phase selection
                        RTL_PIF_END="afe10gblk.pif_clkdelay_txphsel_ch0_i"

                 <B>Notes:</B>
                        Asynchronous phase select for gmux clock for TXDAC. Lower 3 bits used for selecting 1 out of 8 phases in 10G/AQrate mode. All 4 bits used to select 1 of 16 phases in 1G mode. Phase separation is 45 deg in 10G/AQrate mode. Phase separation is 22.5 deg in 1G mode.
                        
                        The defaults indicated here is in Binary but will be converted to Gray code in H/W. Here is the Binary to Gray code LUT:
                        Binary     Gray
                        0000        1111 => 0 deg
                        0001        1110 => 22.5deg
                        0010        1100 => 45 deg
                        0011        1101 => 67.5 deg
                        0100        1001 => 90 deg
                        0101        1000 => 112.5 deg
                        0110        1010 => 135 deg
                        0111        1011 => 157.5 deg
                        1000        0011 => 180 deg
                        1001        0010 => 202.5 deg
                        1010        0000 => 225 deg
                        1011        0001 => 247.5 deg
                        1100        0101 => 270 deg
                        1101        0100 => 292.5 deg
                        1110        0110 => 315 deg
                        1111        0111 => 337.5 deg  */
      unsigned int   channel_0TxClockPhaseSelection : 4;    /* 01.C142.3:0  ROPD      Provisionable Default = 0x2 */
                     /* Channel 0 Tx clock phase selection
                        RTL_PIF_END="afe10gblk.pif_clkdelay_txphsel_ch0_i"  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaTransmitClockPhaseSelectionControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Transmit Reserved Vendor Provisioning: 01.C412 */
/*                  PMA Transmit Reserved Vendor Provisioning: 01.C412 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Transmit Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 01.C412.F:E R/WPD Test Mode Rate [1:0]
                        AQ_PmaTransmitReservedVendorProvisioning_EUR.u0.bits_0.testModeRate

                        Provisionable Default = 0x0

                        2 = 2.5G Test Modes 
                        1 = 5G Test Modes
                        0 = 10G Test Mode
                        

                 <B>Notes:</B>
                        This field controls the  data rate for the test mode activated with register 1.84.  */
      unsigned int   testModeRate : 2;    /* 01.C412.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* 2 = 2.5G Test Modes 
                        1 = 5G Test Modes
                        0 = 10G Test Mode
                          */
                    /*! \brief 01.C412.D:4 R/WPD Reserved Spare Transmit Provisioning 0 [9:0]
                        AQ_PmaTransmitReservedVendorProvisioning_EUR.u0.bits_0.reservedSpareTransmitProvisioning_0

                        Provisionable Default = 0x000

                        Reserved for future use
                        
  */
      unsigned int   reservedSpareTransmitProvisioning_0 : 10;    /* 01.C412.D:4  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                          */
                    /*! \brief 01.C412.3:0 R/W Tx Polarity Invert Enable [3:0]
                        AQ_PmaTransmitReservedVendorProvisioning_EUR.u0.bits_0.txPolarityInvertEnable

                        Default = 0x0

                        1 = Invert corresponding Tx lane
                        

                 <B>Notes:</B>
                        Bit 0 corresponds to Lane A, Bit 1 to Lane B, etc.  */
      unsigned int   txPolarityInvertEnable : 4;    /* 01.C412.3:0  R/W      Default = 0x0 */
                     /* 1 = Invert corresponding Tx lane
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA Transmit Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 01.C413.F:C R/WPD Channel Mask[3:0]
                        AQ_PmaTransmitReservedVendorProvisioning_EUR.u1.bits_1.channelMask

                        Provisionable Default = 0x0

                        Channel mask specifying which channels will be affected by the TX PSD target.
                        
  */
      unsigned int   channelMask : 4;    /* 01.C413.F:C  R/WPD      Provisionable Default = 0x0 */
                     /* Channel mask specifying which channels will be affected by the TX PSD target.
                          */
                    /*! \brief 01.C413.B:8 R/WPD Reserved Spare Transmit Provisioning 1 [3:0]
                        AQ_PmaTransmitReservedVendorProvisioning_EUR.u1.bits_1.reservedSpareTransmitProvisioning_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedSpareTransmitProvisioning_1 : 4;    /* 01.C413.B:8  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 01.C413.7:0 R/WPD Incremental Tx PSD Target [7:0]
                        AQ_PmaTransmitReservedVendorProvisioning_EUR.u1.bits_1.incrementalTxPsdTarget

                        Provisionable Default = 0x00

                        Deviation from the current TX PSD target based on registers A.A and A.B in 2's complement form s7.
                        
  */
      unsigned int   incrementalTxPsdTarget : 8;    /* 01.C413.7:0  R/WPD      Provisionable Default = 0x00 */
                     /* Deviation from the current TX PSD target based on registers A.A and A.B in 2's complement form s7.
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PmaTransmitReservedVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Transmit Vendor Alarms: 01.CC00 */
/*                  PMA Transmit Vendor Alarms: 01.CC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Transmit Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA Transmit Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PMA Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 01.CC02.F:2 LH Reserved PMA Transmit Alarms 3 [D:0]
                        AQ_PmaTransmitVendorAlarms_EUR.u2.bits_2.reservedPmaTransmitAlarms_3

                        

                        Reserved for internal use
                        
  */
      unsigned int   reservedPmaTransmitAlarms_3 : 14;    /* 01.CC02.F:2  LH       */
                     /* Reserved for internal use
                          */
                    /*! \brief 01.CC02.1 ROS Zero
                        AQ_PmaTransmitVendorAlarms_EUR.u2.bits_2.zero

                        Default = 0x0

                        Defined as 0
                        

                 <B>Notes:</B>
                        Used to provide a guaranteed zero location in the same register as Reset Complete  */
      unsigned int   zero : 1;    /* 01.CC02.1  ROS      Default = 0x0 */
                     /* Defined as 0
                          */
                    /*! \brief 01.CC02.0 LH Reset Complete
                        AQ_PmaTransmitVendorAlarms_EUR.u2.bits_2.resetComplete

                        

                        1 = Hardware and Firmware reset has completed
                        

                 <B>Notes:</B>
                        This bit is a mirror of 1E.CC00.6, but has associated with it a known zero bit that can be used to ascertain that HW reset has completed, enabling Reset Complete to be read in one shot without double polling and dealing with tristate MDIO issues. It avoids of problem of not knowing if / when the HW complete phase of a reset has occurred when double-polling  */
      unsigned int   resetComplete : 1;    /* 01.CC02.0  LH       */
                     /* 1 = Hardware and Firmware reset has completed
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PmaTransmitVendorAlarms_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Transmit Standard Interrupt Mask: 01.D000 */
/*                  PMA Transmit Standard Interrupt Mask: 01.D000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Transmit Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 01.D000.2 R/WPD PMA Receive Link Status Mask
                        AQ_PmaTransmitStandardInterruptMask_EUR.u0.bits_0.pmaReceiveLinkStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Mask for Bit 1.1.2.  */
      unsigned int   pmaReceiveLinkStatusMask : 1;    /* 01.D000.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA Transmit Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 01.D001.B R/WPD Transmit Fault Mask
                        AQ_PmaTransmitStandardInterruptMask_EUR.u1.bits_1.transmitFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 1.8.B  */
      unsigned int   transmitFaultMask : 1;    /* 01.D001.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 01.D001.A R/WPD Receive Fault Mask
                        AQ_PmaTransmitStandardInterruptMask_EUR.u1.bits_1.receiveFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 1.8.A  */
      unsigned int   receiveFaultMask : 1;    /* 01.D001.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 10;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PmaTransmitStandardInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Transmit Vendor Interrupt Mask: 01.D400 */
/*                  PMA Transmit Vendor Interrupt Mask: 01.D400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PMA Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 01.D402.0 R/WPD Reset Complete Mask
                        AQ_PmaTransmitVendorInterruptMask_EUR.u2.bits_2.resetCompleteMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   resetCompleteMask : 1;    /* 01.D402.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PmaTransmitVendorInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Transmit Vendor Debug: 01.D800 */
/*                  PMA Transmit Vendor Debug: 01.D800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Transmit Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 01.D800.F R/WPD PMA Digital System Loopback
                        AQ_PmaTransmitVendorDebug_EUR.u0.bits_0.pmaDigitalSystemLoopback

                        Provisionable Default = 0x0

                        1 = Enable PMA digital system loopback
  */
      unsigned int   pmaDigitalSystemLoopback : 1;    /* 01.D800.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable PMA digital system loopback  */
      unsigned int   reserved0 : 15;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaTransmitVendorDebug_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Receive Reserved Vendor Provisioning: 01.E400 */
/*                  PMA Receive Reserved Vendor Provisioning: 01.E400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Receive Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 01.E400.F R/WPD External PHY Loopback
                        AQ_PmaReceiveReservedVendorProvisioning_EUR.u0.bits_0.externalPhyLoopback

                        Provisionable Default = 0x0

                        1 = Enable external PHY loopback
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        External PHY loopback expects a loopback connector such that Pair A is connected to Pair B, and Pair C is connected to Pair D.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   externalPhyLoopback : 1;    /* 01.E400.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable external PHY loopback
                        0 = Normal operation
                          */
                    /*! \brief 01.E400.E:3 R/WPD Reserved Receive Provisioning 1 [B:0]
                        AQ_PmaReceiveReservedVendorProvisioning_EUR.u0.bits_0.reservedReceiveProvisioning_1

                        Provisionable Default = 0x000

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveProvisioning_1 : 12;    /* 01.E400.E:3  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                          */
                    /*! \brief 01.E400.2 R/WPD Enable Aquantia Fast Retrain
                        AQ_PmaReceiveReservedVendorProvisioning_EUR.u0.bits_0.enableAquantiaFastRetrain

                        Provisionable Default = 0x0

                        1 = Enable PMA Fast Link Retrain
                        0 = Disable PMA Fast Link Retrain
                        

                 <B>Notes:</B>
                        If the link partner is an Aquantia PHY and also has Fast Retrain enabled use a special retrain sequence to bring the link back up without going back through the Autonegotiation sequence.  */
      unsigned int   enableAquantiaFastRetrain : 1;    /* 01.E400.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable PMA Fast Link Retrain
                        0 = Disable PMA Fast Link Retrain
                          */
                    /*! \brief 01.E400.1 R/WPD Force MDI Configuration
                        AQ_PmaReceiveReservedVendorProvisioning_EUR.u0.bits_0.forceMdiConfiguration

                        Provisionable Default = 0x0

                        1 = Ignore state of MDI_CFG pin
                        0 = Set MDI Configuration based on state of MDI_CFG
                        

                 <B>Notes:</B>
                        Normally the MDI reversal configuration is taken from the MDI_CFG pin. If the Force MDI Configuration bit is asserted, the MDI_CFG pin is ignored and the current provisioned value of the MDI configuration bit is used instead  */
      unsigned int   forceMdiConfiguration : 1;    /* 01.E400.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Ignore state of MDI_CFG pin
                        0 = Set MDI Configuration based on state of MDI_CFG
                          */
                    /*! \brief 01.E400.0 R/WPD MDI Configuration
                        AQ_PmaReceiveReservedVendorProvisioning_EUR.u0.bits_0.mdiConfiguration

                        Provisionable Default = 0x0

                        1 = MDI Reversed (ABCD -> DCBA)
                        0 = MDI Normal (ABCD -> ABCD)
                        

                 <B>Notes:</B>
                        The setting of this bit determines whether the MDI is reversed or not. Note that the reversal does not change pair polarity - i.e. A+ maps to D+, etc. The value of this bit is set during autonegotiation to the value of the MDI_CFG pin unless the Force MDI Configuration bit (1.E400.1) is asserted, When the Force MDI Configuration bit is asserted the MDI_CFG pin is ignored and this bit is unchanged from its default or provisioned value. If this bit is changed manually after autonegotiation completes, autonegotiation must be restarted to achieve the desired MDI configuration.   */
      unsigned int   mdiConfiguration : 1;    /* 01.E400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = MDI Reversed (ABCD -> DCBA)
                        0 = MDI Normal (ABCD -> ABCD)
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaReceiveReservedVendorProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Receive Vendor State: 01.E800 */
/*                  PMA Receive Vendor State: 01.E800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Receive Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 01.E800.0 RO PMA Receive Link Current Status
                        AQ_PmaReceiveVendorState_EUR.u0.bits_0.pmaReceiveLinkCurrentStatus

                        

                        1 = Rx link good

                 <B>Notes:</B>
                        This is the current state of 1.1.2  */
      unsigned int   pmaReceiveLinkCurrentStatus : 1;    /* 01.E800.0  RO       */
                     /* 1 = Rx link good  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaReceiveVendorState_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Receive Reserved Vendor State: 01.E810 */
/*                  PMA Receive Reserved Vendor State: 01.E810 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Receive Reserved Vendor State */
  union
  {
    struct
    {
                    /*! \brief 01.E810.F:0 RO Accumulated Fast Retrain Time[F:0]
                        AQ_PmaReceiveReservedVendorState_EUR.u0.bits_0.accumulatedFastRetrainTime

                        

                        Accumulated time in milliseconds spent in fast retrain since the last auto-negotiation sequence
                        

                 <B>Notes:</B>
                        This is a saturating register.  */
      unsigned int   accumulatedFastRetrainTime : 16;    /* 01.E810.F:0  RO       */
                     /* Accumulated time in milliseconds spent in fast retrain since the last auto-negotiation sequence
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PMA Receive Reserved Vendor State */
  union
  {
    struct
    {
                    /*! \brief 01.E811.F:8 RO Total Number Of Link Recovery Events Since Last AutoNeg [7:0]
                        AQ_PmaReceiveReservedVendorState_EUR.u1.bits_1.totalNumberOfLinkRecoveryEventsSinceLastAutoneg

                        

                        The count of the cumulative number of Link Recovery Events since last autonegotiation
                        

                 <B>Notes:</B>
                        This register is automatically reset to 0 during Auto-negotiation. It increments once for each series of back-to-back Fast Retrain events. The result is reported modulo 256 (wrap around).  */
      unsigned int   totalNumberOfLinkRecoveryEventsSinceLastAutoneg : 8;    /* 01.E811.F:8  RO       */
                     /* The count of the cumulative number of Link Recovery Events since last autonegotiation
                          */
                    /*! \brief 01.E811.7:0 RO Total Number Of RFI Training Link Recovery Events Since Last AutoNeg [7:0]
                        AQ_PmaReceiveReservedVendorState_EUR.u1.bits_1.totalNumberOfRfiTrainingLinkRecoveryEventsSinceLastAutoneg

                        

                        The count of the cumulative number of RFI Training Link Recovery Events since last autonegotiation
                        

                 <B>Notes:</B>
                        This register is automatically reset to 0 during Auto-negotiation. The result is reported modulo 256 (wrap around).  */
      unsigned int   totalNumberOfRfiTrainingLinkRecoveryEventsSinceLastAutoneg : 8;    /* 01.E811.7:0  RO       */
                     /* The count of the cumulative number of RFI Training Link Recovery Events since last autonegotiation
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PmaReceiveReservedVendorState_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                PMA Vendor Global Interrupt Flags: 01.FC00 */
/*                  PMA Vendor Global Interrupt Flags: 01.FC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PMA Vendor Global Interrupt Flags */
  union
  {
    struct
    {
                    /*! \brief 01.FC00.F RO Vendor Specific Tx Alarms 1 Interrupt
                        AQ_PmaVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificTxAlarms_1Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register (See "PMA Transmit Vendor Alarms 1: Address 1.CC00" on page 129.) and the corresponding mask register (See "PMA Transmit Vendor Interrupt Mask 1: Address 1.D400" on page 132.)  */
      unsigned int   vendorSpecificTxAlarms_1Interrupt : 1;    /* 01.FC00.F  RO       */
                     /* 1 = Interrupt
                          */
                    /*! \brief 01.FC00.E RO Vendor Specific Tx Alarms 2 Interrupt
                        AQ_PmaVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificTxAlarms_2Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register (See "PMA Transmit Vendor Alarms 2: Address 1.CC01" on page 129.) and the corresponding mask register (See "PMA Transmit Vendor Interrupt Mask 2: Address 1.D401" on page 132.)  */
      unsigned int   vendorSpecificTxAlarms_2Interrupt : 1;    /* 01.FC00.E  RO       */
                     /* 1 = Interrupt
                          */
                    /*! \brief 01.FC00.D RO Vendor Specific Tx Alarms 3 Interrupt
                        AQ_PmaVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificTxAlarms_3Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register (See "PMA Transmit Vendor Alarms 3: Address 1.CC02" on page 130.) and the corresponding mask register (See "PMA Transmit Vendor Interrupt Mask 3: Address 1.D402" on page 133.)  */
      unsigned int   vendorSpecificTxAlarms_3Interrupt : 1;    /* 01.FC00.D  RO       */
                     /* 1 = Interrupt
                          */
      unsigned int   reserved0 : 1;
                    /*! \brief 01.FC00.B RO Standard Alarm 1 Interrupt
                        AQ_PmaVendorGlobalInterruptFlags_EUR.u0.bits_0.standardAlarm_1Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from bit 1.1.2.
                        An interrupt was generated from status register (See "PMA Standard Status 1: Address 1.1" on page 2.) and the corresponding mask register (See "PMA Transmit Standard Interrupt Mask 1: Address 1.D000" on page 131.)  */
      unsigned int   standardAlarm_1Interrupt : 1;    /* 01.FC00.B  RO       */
                     /* 1 = Interrupt
                          */
                    /*! \brief 01.FC00.A RO Standard Alarm 2 Interrupt
                        AQ_PmaVendorGlobalInterruptFlags_EUR.u0.bits_0.standardAlarm_2Interrupt

                        

                        1 = Interrupt
                        

                 <B>Notes:</B>
                        An interrupt was generated from either bit 1.8.B or 1.8.A.
                        An interrupt was generated from status register (See "PMA Standard Status 2: Address 1.8" on page 8.) and the corresponding mask register (See "PMA Transmit Standard Interrupt Mask 2: Address 1.D001" on page 131.)  */
      unsigned int   standardAlarm_2Interrupt : 1;    /* 01.FC00.A  RO       */
                     /* 1 = Interrupt
                          */
      unsigned int   reserved1 : 10;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PmaVendorGlobalInterruptFlags_EUR;

#endif
/*@}*/
/*@}*/
