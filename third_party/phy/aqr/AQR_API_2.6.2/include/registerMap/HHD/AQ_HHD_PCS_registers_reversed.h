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
*   for the PCS Registers block.
 */        

/*! \addtogroup registerMap
  @{
*/

/*! \defgroup PCS_registers PCS Registers
*   This module contains the data structures and doxygen comments
*   for the PCS Registers block.
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
*   This file contains the c header structures for the registers contained in the PCS Registers block.
*
*   The bit fields in this structure are from MSbit to LSbit
*
***********************************************************************/


/*@{*/
#ifndef AQ_HHD_PCS_REGS_HEADER
#define AQ_HHD_PCS_REGS_HEADER


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Control 1: 03.0000 */
/*                  PCS Standard Control 1: 03.0000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Control 1 */
  union
  {
    struct
    {
                    /*! \brief 03.0000.F R/WSC Reset
                        AQ_PcsStandardControl_1_HHD.u0.bits_0.reset

                        Default = 0x1

                        1 = PCS reset
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        Resets the entire PHY.
                        The reset bit is automatically cleared upon completion of the reset sequence by the microcontroller. This bit is set to 1 during reset. The reset is internally stretched by approximately 1.7 us. Therefore the MDIO or uP should allow for 1.7 us before writing any PCS registers after this bit is set.  */
      unsigned int   reset : 1;    /* 03.0000.F  R/WSC      Default = 0x1 */
                     /* 1 = PCS reset
                        0 = Normal operation
                          */
                    /*! \brief 03.0000.E R/WPD Loopback
                        AQ_PcsStandardControl_1_HHD.u0.bits_0.loopback

                        Provisionable Default = 0x0

                        1 = Enable loopback mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        This enables the PCS DSQ System Loopback.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   loopback : 1;    /* 03.0000.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable loopback mode
                        0 = Normal operation
                          */
                    /*! \brief 03.0000.D R/WPD Speed Selection LSB
                        AQ_PcsStandardControl_1_HHD.u0.bits_0.speedSelectionLsb

                        Provisionable Default = 0x1

                        {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s
  */
      unsigned int   speedSelectionLsb : 1;    /* 03.0000.D  R/WPD      Provisionable Default = 0x1 */
                     /* {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s  */
      unsigned int   reserved0 : 1;
                    /*! \brief 03.0000.B R/WPD Low Power
                        AQ_PcsStandardControl_1_HHD.u0.bits_0.lowPower

                        Provisionable Default = 0x0

                        1 = Low-power mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        A one written to this register causes the PCS to enter low-power mode. If a global chip low-power state is desired, use Bit B in  See PHY XS Standard Control 1 - Address 4.0 should be set.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   lowPower : 1;    /* 03.0000.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Low-power mode
                        0 = Normal operation
                          */
                    /*! \brief 03.0000.A R/WPD Clock Stop Enable
                        AQ_PcsStandardControl_1_HHD.u0.bits_0.clockStopEnable

                        Provisionable Default = 0x0

                        1 = The PHY may stop the clock during LPI
                        0 = Clock not stoppable
  */
      unsigned int   clockStopEnable : 1;    /* 03.0000.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = The PHY may stop the clock during LPI
                        0 = Clock not stoppable  */
      unsigned int   reserved1 : 3;
                    /*! \brief 03.0000.6 R/WPD Speed Selection MSB
                        AQ_PcsStandardControl_1_HHD.u0.bits_0.speedSelectionMsb

                        Provisionable Default = 0x1

                        {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s
  */
      unsigned int   speedSelectionMsb : 1;    /* 03.0000.6  R/WPD      Provisionable Default = 0x1 */
                     /* {6,D}
                        1 1 = Speed set by Bits [5:2]
                        1 0 = 1000 Mb/s
                        0 1 = 100 Mb/s
                        0 0 = 10 Mb/s  */
                    /*! \brief 03.0000.5:2 R/WPD 10G Speed Selection [3:0]
                        AQ_PcsStandardControl_1_HHD.u0.bits_0._10gSpeedSelection

                        Provisionable Default = 0x0

                        1 x x x = Reserved
                        x 1 x x = Reserved
                        x x 1 x = Reserved
                        x x x 1 = 10PASS-TS / 2BASE-TL
                        0 0 0 0 = 10 Gb/s
  */
      unsigned int   _10gSpeedSelection : 4;    /* 03.0000.5:2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 x x x = Reserved
                        x 1 x x = Reserved
                        x x 1 x = Reserved
                        x x x 1 = 10PASS-TS / 2BASE-TL
                        0 0 0 0 = 10 Gb/s  */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardControl_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Status 1: 03.0001 */
/*                  PCS Standard Status 1: 03.0001 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Status 1 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.0001.B LH Tx LPI Received
                        AQ_PcsStandardStatus_1_HHD.u0.bits_0.txLpiReceived

                        

                        1 = Tx PCS has received LPI
                        0 = LPI not received
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A2.4:0.  */
      unsigned int   txLpiReceived : 1;    /* 03.0001.B  LH       */
                     /* 1 = Tx PCS has received LPI
                        0 = LPI not received
                          */
                    /*! \brief 03.0001.A LH Rx LPI Received
                        AQ_PcsStandardStatus_1_HHD.u0.bits_0.rxLpiReceived

                        

                        1 = Rx PCS has received LPI
                        0 = LPI not received
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A1.4:0.  */
      unsigned int   rxLpiReceived : 1;    /* 03.0001.A  LH       */
                     /* 1 = Rx PCS has received LPI
                        0 = LPI not received
                          */
                    /*! \brief 03.0001.9 RO Tx LPI Indication
                        AQ_PcsStandardStatus_1_HHD.u0.bits_0.txLpiIndication

                        

                        1 = Tx PCS is currently receiving LPI
                        0 = Tx PCS is not currently receiving LPI
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A2.4:0.  */
      unsigned int   txLpiIndication : 1;    /* 03.0001.9  RO       */
                     /* 1 = Tx PCS is currently receiving LPI
                        0 = Tx PCS is not currently receiving LPI
                          */
                    /*! \brief 03.0001.8 RO Rx LPI Indication
                        AQ_PcsStandardStatus_1_HHD.u0.bits_0.rxLpiIndication

                        

                        1 = Rx PCS is currently receiving LPI
                        0 = Rx PCS is not currently receiving LPI
                        

                 <B>Notes:</B>
                        The source of the LPI signal is configured in 1E.C4A1.4:0.  */
      unsigned int   rxLpiIndication : 1;    /* 03.0001.8  RO       */
                     /* 1 = Rx PCS is currently receiving LPI
                        0 = Rx PCS is not currently receiving LPI
                          */
                    /*! \brief 03.0001.7 RO Fault
                        AQ_PcsStandardStatus_1_HHD.u0.bits_0.fault

                        

                        1 = Fault condition detected
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        This is the top-level fault indicator flag for the PCS block, This bit is set if either of the two bits 3.8.B or 3.8.A are set.  */
      unsigned int   fault : 1;    /* 03.0001.7  RO       */
                     /* 1 = Fault condition detected
                        0 = No fault detected
                          */
                    /*! \brief 03.0001.6 ROS Clock Stop Capable
                        AQ_PcsStandardStatus_1_HHD.u0.bits_0.clockStopCapable

                        Default = 0x0

                        1 = The MAC may stop the clock during LPI
                        0 = Clock not stoppable
  */
      unsigned int   clockStopCapable : 1;    /* 03.0001.6  ROS      Default = 0x0 */
                     /* 1 = The MAC may stop the clock during LPI
                        0 = Clock not stoppable  */
      unsigned int   reserved1 : 3;
                    /*! \brief 03.0001.2 LL PCS Receive Link Status
                        AQ_PcsStandardStatus_1_HHD.u0.bits_0.pcsReceiveLinkStatus

                        

                        Status of the PCS receive link
                        1 = Link up
                        0 = Link lost since last read
                        

                 <B>Notes:</B>
                        This indicates the status of the PCS receive link. This is a latching low version of Bit 3.20.C.  */
      unsigned int   pcsReceiveLinkStatus : 1;    /* 03.0001.2  LL       */
                     /* Status of the PCS receive link
                        1 = Link up
                        0 = Link lost since last read
                          */
                    /*! \brief 03.0001.1 ROS Low Power Ability
                        AQ_PcsStandardStatus_1_HHD.u0.bits_0.lowPowerAbility

                        Default = 0x1

                        1 = PCS supports low-power mode
                        0 = no low-power mode supported

                 <B>Notes:</B>
                        Indicates whether the XAUI interface supports a low-power mode  */
      unsigned int   lowPowerAbility : 1;    /* 03.0001.1  ROS      Default = 0x1 */
                     /* 1 = PCS supports low-power mode
                        0 = no low-power mode supported  */
      unsigned int   reserved2 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardStatus_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Device Identifier: 03.0002 */
/*                  PCS Standard Device Identifier: 03.0002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 03.0002.F:0 RO Device ID MSW [1F:10]
                        AQ_PcsStandardDeviceIdentifier_HHD.u0.bits_0.deviceIdMSW

                        

                        Bits 31 - 16 of Device ID
  */
      unsigned int   deviceIdMSW : 16;    /* 03.0002.F:0  RO       */
                     /* Bits 31 - 16 of Device ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 03.0003.F:0 RO Device ID LSW [F:0]
                        AQ_PcsStandardDeviceIdentifier_HHD.u1.bits_1.deviceIdLSW

                        

                        Bits 15 - 0 of Device ID
  */
      unsigned int   deviceIdLSW : 16;    /* 03.0003.F:0  RO       */
                     /* Bits 15 - 0 of Device ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardDeviceIdentifier_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Speed Ability: 03.0004 */
/*                  PCS Standard Speed Ability: 03.0004 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Speed Ability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.0004.1 ROS 10PASS-TS / 2BASE-TL Capable
                        AQ_PcsStandardSpeedAbility_HHD.u0.bits_0._10pass_ts__2base_tlCapable

                        Default = 0x0

                        1 = PCS is 10PASS-TS / 2BASE-TL capable
                        0 = PCS is not 10PASS-TS / 2BASE-TL capable

                 <B>Notes:</B>
                        This is always set to 0 in the PHY.  */
      unsigned int   _10pass_ts__2base_tlCapable : 1;    /* 03.0004.1  ROS      Default = 0x0 */
                     /* 1 = PCS is 10PASS-TS / 2BASE-TL capable
                        0 = PCS is not 10PASS-TS / 2BASE-TL capable  */
                    /*! \brief 03.0004.0 ROS 10G Capable
                        AQ_PcsStandardSpeedAbility_HHD.u0.bits_0._10gCapable

                        Default = 0x1

                        1 = PCS is 10 Gb/s capable
                        0 = PCS is not 10 Gb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.  */
      unsigned int   _10gCapable : 1;    /* 03.0004.0  ROS      Default = 0x1 */
                     /* 1 = PCS is 10 Gb/s capable
                        0 = PCS is not 10 Gb/s capable  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardSpeedAbility_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Devices in Package: 03.0005 */
/*                  PCS Standard Devices in Package: 03.0005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Devices in Package */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.0005.7 ROS Autonegotiation Present
                        AQ_PcsStandardDevicesInPackage_HHD.u0.bits_0.autonegotiationPresent

                        Default = 0x1

                        1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package

                 <B>Notes:</B>
                        This is always set to 1, as there is Autonegotiation in the PHY.  */
      unsigned int   autonegotiationPresent : 1;    /* 03.0005.7  ROS      Default = 0x1 */
                     /* 1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package  */
                    /*! \brief 03.0005.6 ROS TC Present
                        AQ_PcsStandardDevicesInPackage_HHD.u0.bits_0.tcPresent

                        Default = 0x0

                        1 = TC is present in package
                        0 = TC is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no TC functionality in the PHY.  */
      unsigned int   tcPresent : 1;    /* 03.0005.6  ROS      Default = 0x0 */
                     /* 1 = TC is present in package
                        0 = TC is not present in package  */
                    /*! \brief 03.0005.5 ROS DTE XS Present
                        AQ_PcsStandardDevicesInPackage_HHD.u0.bits_0.dteXsPresent

                        Default = 0x0

                        1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                        

                 <B>Notes:</B>
                        This is always set to 0, as there is no DTE XAUI interface in the PHY.  */
      unsigned int   dteXsPresent : 1;    /* 03.0005.5  ROS      Default = 0x0 */
                     /* 1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                          */
                    /*! \brief 03.0005.4 ROS PHY XS Present
                        AQ_PcsStandardDevicesInPackage_HHD.u0.bits_0.phyXS_Present

                        Default = 0x1

                        1 = PHY XS is present in package
                        0 = PHY XS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is a PHY XS interface in the PHY.  */
      unsigned int   phyXS_Present : 1;    /* 03.0005.4  ROS      Default = 0x1 */
                     /* 1 = PHY XS is present in package
                        0 = PHY XS is not present in package  */
                    /*! \brief 03.0005.3 ROS PCS Present
                        AQ_PcsStandardDevicesInPackage_HHD.u0.bits_0.pcsPresent

                        Default = 0x1

                        1 = PCS is present in package
                        0 = PCS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is PCS functionality in the PHY.  */
      unsigned int   pcsPresent : 1;    /* 03.0005.3  ROS      Default = 0x1 */
                     /* 1 = PCS is present in package
                        0 = PCS is not present in package  */
                    /*! \brief 03.0005.2 ROS WIS Present
                        AQ_PcsStandardDevicesInPackage_HHD.u0.bits_0.wisPresent

                        Default = 0x0

                        1 = WIS is present in package
                        0 = WIS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no WIS functionality in the PHY.  */
      unsigned int   wisPresent : 1;    /* 03.0005.2  ROS      Default = 0x0 */
                     /* 1 = WIS is present in package
                        0 = WIS is not present in package  */
                    /*! \brief 03.0005.1 ROS PMA Present
                        AQ_PcsStandardDevicesInPackage_HHD.u0.bits_0.pmaPresent

                        Default = 0x1

                        1 = PMA is present in package
                        0 = PMA is not present 

                 <B>Notes:</B>
                        This is always set to 1 as there is PMA functionality in the PHY.  */
      unsigned int   pmaPresent : 1;    /* 03.0005.1  ROS      Default = 0x1 */
                     /* 1 = PMA is present in package
                        0 = PMA is not present   */
                    /*! \brief 03.0005.0 ROS Clause 22 Registers Present
                        AQ_PcsStandardDevicesInPackage_HHD.u0.bits_0.clause_22RegistersPresent

                        Default = 0x0

                        1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package

                 <B>Notes:</B>
                        This is always set to 0 in the PHY, as there are no Clause 22 registers in the device.  */
      unsigned int   clause_22RegistersPresent : 1;    /* 03.0005.0  ROS      Default = 0x0 */
                     /* 1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Devices in Package */
  union
  {
    struct
    {
                    /*! \brief 03.0006.F ROS Vendor Specific Device #2 Present
                        AQ_PcsStandardDevicesInPackage_HHD.u1.bits_1.vendorSpecificDevice_2Present

                        Default = 0x1

                        1 = Device #2 is present in package
                        0 = Device #2 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the DSP PMA registers.  */
      unsigned int   vendorSpecificDevice_2Present : 1;    /* 03.0006.F  ROS      Default = 0x1 */
                     /* 1 = Device #2 is present in package
                        0 = Device #2 is not present in package  */
                    /*! \brief 03.0006.E ROS Vendor Specific Device #1 Present
                        AQ_PcsStandardDevicesInPackage_HHD.u1.bits_1.vendorSpecificDevice_1Present

                        Default = 0x1

                        1 = Device #1 is present in package
                        0 = Device #1 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the global control registers.  */
      unsigned int   vendorSpecificDevice_1Present : 1;    /* 03.0006.E  ROS      Default = 0x1 */
                     /* 1 = Device #1 is present in package
                        0 = Device #1 is not present in package  */
                    /*! \brief 03.0006.D ROS Clause 22 Extension Present
                        AQ_PcsStandardDevicesInPackage_HHD.u1.bits_1.clause_22ExtensionPresent

                        Default = 0x1

                        1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the GbE registers.  */
      unsigned int   clause_22ExtensionPresent : 1;    /* 03.0006.D  ROS      Default = 0x1 */
                     /* 1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package  */
      unsigned int   reserved0 : 13;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardDevicesInPackage_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Control 2: 03.0007 */
/*                  PCS Standard Control 2: 03.0007 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Control 2 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.0007.1:0 R/WPD PCS Device Type [1:0]
                        AQ_PcsStandardControl_2_HHD.u0.bits_0.pcsDeviceType

                        Provisionable Default = 0x3

                        [1:0]
                        0x3 = 10GBASE-T
                        0x2 = 10GBASE-W
                        0x1 = 10GBASE-X
                        0x0 = 10GBASE-R

                 <B>Notes:</B>
                        This defaults to 10GBASE-T  */
      unsigned int   pcsDeviceType : 2;    /* 03.0007.1:0  R/WPD      Provisionable Default = 0x3 */
                     /* [1:0]
                        0x3 = 10GBASE-T
                        0x2 = 10GBASE-W
                        0x1 = 10GBASE-X
                        0x0 = 10GBASE-R  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardControl_2_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Status 2: 03.0008 */
/*                  PCS Standard Status 2: 03.0008 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Status 2 */
  union
  {
    struct
    {
                    /*! \brief 03.0008.F:E ROS Device Present [1:0]
                        AQ_PcsStandardStatus_2_HHD.u0.bits_0.devicePresent

                        Default = 0x2

                        [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address

                 <B>Notes:</B>
                        This field is always set to 0x2, as the PCS registers reside here in the PHY.  */
      unsigned int   devicePresent : 2;    /* 03.0008.F:E  ROS      Default = 0x2 */
                     /* [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address  */
      unsigned int   reserved0 : 2;
                    /*! \brief 03.0008.B LH Transmit Fault
                        AQ_PcsStandardStatus_2_HHD.u0.bits_0.transmitFault

                        

                        1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the transmit path. This bit is duplicated at 3.CC01.0.   */
      unsigned int   transmitFault : 1;    /* 03.0008.B  LH       */
                     /* 1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                          */
                    /*! \brief 03.0008.A LH Receive Fault
                        AQ_PcsStandardStatus_2_HHD.u0.bits_0.receiveFault

                        

                        1 = Fault condition on receive path
                        0 = No fault condition on receive path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the receive path. This bit is duplicated at 3.EC04.2.  */
      unsigned int   receiveFault : 1;    /* 03.0008.A  LH       */
                     /* 1 = Fault condition on receive path
                        0 = No fault condition on receive path
                          */
      unsigned int   reserved1 : 6;
                    /*! \brief 03.0008.3 ROS 10GBASE-T capable
                        AQ_PcsStandardStatus_2_HHD.u0.bits_0._10gbase_tCapable

                        Default = 0x1

                        1 = PCS supports 10GBASE-T PCS type
                        0 = PCS does not support 10GBASE-T

                 <B>Notes:</B>
                        This field is always set to 1, as the PCS in the PHY only supports 10GBASE-T and 10GBASE-R.  */
      unsigned int   _10gbase_tCapable : 1;    /* 03.0008.3  ROS      Default = 0x1 */
                     /* 1 = PCS supports 10GBASE-T PCS type
                        0 = PCS does not support 10GBASE-T  */
                    /*! \brief 03.0008.2 ROS 10GBASE-W capable
                        AQ_PcsStandardStatus_2_HHD.u0.bits_0._10gbase_wCapable

                        Default = 0x0

                        1 = PCS supports 10GBASE-W PCS type
                        0 = PCS does not support 10GBASE-W

                 <B>Notes:</B>
                        This field is always set to 0, as the PCS in the PHY only supports 10GBASE-T and 10GBASE-R.  */
      unsigned int   _10gbase_wCapable : 1;    /* 03.0008.2  ROS      Default = 0x0 */
                     /* 1 = PCS supports 10GBASE-W PCS type
                        0 = PCS does not support 10GBASE-W  */
                    /*! \brief 03.0008.1 ROS 10GBASE-X capable
                        AQ_PcsStandardStatus_2_HHD.u0.bits_0._10gbase_xCapable

                        Default = 0x0

                        1 = PCS supports 10GBASE-X PCS type
                        0 = PCS does not support 10GBASE-X

                 <B>Notes:</B>
                        This field is always set to 0, as the PCS in the PHY only supports 10GBASE-T and 10GBASE-R.  */
      unsigned int   _10gbase_xCapable : 1;    /* 03.0008.1  ROS      Default = 0x0 */
                     /* 1 = PCS supports 10GBASE-X PCS type
                        0 = PCS does not support 10GBASE-X  */
                    /*! \brief 03.0008.0 ROS 10GBASE-R capable
                        AQ_PcsStandardStatus_2_HHD.u0.bits_0._10gbase_rCapable

                        Default = 0x1

                        1 = PCS supports 10GBASE-R PCS type
                        0 = PCS does not support 10GBASE-R
                        

                 <B>Notes:</B>
                        This field is always set to 1, as the PCS in the PHY only supports 10GBASE-T and 10GBASE-R.  */
      unsigned int   _10gbase_rCapable : 1;    /* 03.0008.0  ROS      Default = 0x1 */
                     /* 1 = PCS supports 10GBASE-R PCS type
                        0 = PCS does not support 10GBASE-R
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardStatus_2_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Package Identifier: 03.000E */
/*                  PCS Standard Package Identifier: 03.000E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 03.000E.F:0 RO Package ID MSW [1F:10]
                        AQ_PcsStandardPackageIdentifier_HHD.u0.bits_0.packageIdMSW

                        

                        Bits 31- 16 of Package ID
  */
      unsigned int   packageIdMSW : 16;    /* 03.000E.F:0  RO       */
                     /* Bits 31- 16 of Package ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 03.000F.F:0 RO Package ID LSW [F:0]
                        AQ_PcsStandardPackageIdentifier_HHD.u1.bits_1.packageIdLSW

                        

                        Bits 15 - 0 of Package ID
  */
      unsigned int   packageIdLSW : 16;    /* 03.000F.F:0  RO       */
                     /* Bits 15 - 0 of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardPackageIdentifier_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS EEE Capability Register: 03.0014 */
/*                  PCS EEE Capability Register: 03.0014 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS EEE Capability Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 9;
                    /*! \brief 03.0014.6 ROS 10GBASE-KR EEE
                        AQ_PcsEeeCapabilityRegister_HHD.u0.bits_0._10gbase_krEee

                        Default = 0x1

                        1 = Advertise that the 10GBASE-KR has EEE capability
                        0 = Do not advertise that the 10GBASE-KR has EEE capability
  */
      unsigned int   _10gbase_krEee : 1;    /* 03.0014.6  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 10GBASE-KR has EEE capability
                        0 = Do not advertise that the 10GBASE-KR has EEE capability  */
                    /*! \brief 03.0014.5 ROS 10GBASE-KX4 EEE
                        AQ_PcsEeeCapabilityRegister_HHD.u0.bits_0._10gbase_kx4Eee

                        Default = 0x1

                        1 = Advertise that the 10GBASE-KX4 has EEE capability
                        0 = Do not advertise that the 10GBASE-KX4 has EEE capability
  */
      unsigned int   _10gbase_kx4Eee : 1;    /* 03.0014.5  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 10GBASE-KX4 has EEE capability
                        0 = Do not advertise that the 10GBASE-KX4 has EEE capability  */
                    /*! \brief 03.0014.4 ROS 1000BASE-KX EEE
                        AQ_PcsEeeCapabilityRegister_HHD.u0.bits_0._1000base_kxEee

                        Default = 0x1

                        1 = Advertise that the 1000BASE-KX has EEE capability
                        0 = Do not advertise that the 1000BASE-KX has EEE capability
  */
      unsigned int   _1000base_kxEee : 1;    /* 03.0014.4  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 1000BASE-KX has EEE capability
                        0 = Do not advertise that the 1000BASE-KX has EEE capability  */
                    /*! \brief 03.0014.3 ROS 10GBASE-T EEE
                        AQ_PcsEeeCapabilityRegister_HHD.u0.bits_0._10gbase_tEee

                        Default = 0x1

                        1 = Advertise that the 10GBASE-T has EEE capability
                        0 = Do not advertise that the 10GBASE-T has EEE capability
  */
      unsigned int   _10gbase_tEee : 1;    /* 03.0014.3  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 10GBASE-T has EEE capability
                        0 = Do not advertise that the 10GBASE-T has EEE capability  */
                    /*! \brief 03.0014.2 ROS 1000BASE-T EEE
                        AQ_PcsEeeCapabilityRegister_HHD.u0.bits_0._1000base_tEee

                        Default = 0x1

                        1 = Advertise that the 1000BASE-T has EEE capability
                        0 = Do not advertise that the 1000BASE-T has EEE capability
  */
      unsigned int   _1000base_tEee : 1;    /* 03.0014.2  ROS      Default = 0x1 */
                     /* 1 = Advertise that the 1000BASE-T has EEE capability
                        0 = Do not advertise that the 1000BASE-T has EEE capability  */
                    /*! \brief 03.0014.1 ROS 100BASE-TX EEE
                        AQ_PcsEeeCapabilityRegister_HHD.u0.bits_0._100base_txEee

                        Default = 0x0

                        1 = Advertise that the 100BASE-TX has EEE capability
                        0 = Do not advertise that the 100BASE-TX has EEE capability
  */
      unsigned int   _100base_txEee : 1;    /* 03.0014.1  ROS      Default = 0x0 */
                     /* 1 = Advertise that the 100BASE-TX has EEE capability
                        0 = Do not advertise that the 100BASE-TX has EEE capability  */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsEeeCapabilityRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS EEE Wake Error Counter: 03.0016 */
/*                  PCS EEE Wake Error Counter: 03.0016 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS EEE Wake Error Counter */
  union
  {
    struct
    {
                    /*! \brief 03.0016.F:0 SCT EEE Wake Error Counter [F:0]
                        AQ_PcsEeeWakeErrorCounter_HHD.u0.bits_0.eeeWakeErrorCounter

                        Default = 0x0000

                        EEE wake error counter
                        

                 <B>Notes:</B>
                        This register is a 16-bit saturating clear on read counter. The wake error source is configured with 1E.C4A3.2:0. The default wake error source is from the RPL.  */
      unsigned int   eeeWakeErrorCounter : 16;    /* 03.0016.F:0  SCT      Default = 0x0000 */
                     /* EEE wake error counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsEeeWakeErrorCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10G Status: 03.0020 */
/*                  PCS 10G Status: 03.0020 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10G Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 3;
                    /*! \brief 03.0020.C RO 10G Receive Link Status
                        AQ_Pcs10G_Status_HHD.u0.bits_0._10gReceiveLinkStatus

                        

                        1 = 10G Receive Link Up
                        0 = 10G Receive Link Down
                        

                 <B>Notes:</B>
                        When set, this bit indicates that the 10G Receive Link is functioning properly. This is a non-latching version of bit 3.1.2.  See PHY XS Standard Status 1 - Address 4.1  The Receive Link is up when the Block Lock status is asserted and the High BER is deasserted.)  */
      unsigned int   _10gReceiveLinkStatus : 1;    /* 03.0020.C  RO       */
                     /* 1 = 10G Receive Link Up
                        0 = 10G Receive Link Down
                          */
      unsigned int   reserved1 : 8;
                    /*! \brief 03.0020.3 ROS 10GBASE-R PRBS9 Pattern Testing Ability
                        AQ_Pcs10G_Status_HHD.u0.bits_0._10gbase_rPrbs9PatternTestingAbility

                        Default = 0x1

                        1 = PCS is able to support PRBS9 pattern testing on KR Interface
                        0 = PCS is not able to support PRBS9 pattern testing on KR Interface
  */
      unsigned int   _10gbase_rPrbs9PatternTestingAbility : 1;    /* 03.0020.3  ROS      Default = 0x1 */
                     /* 1 = PCS is able to support PRBS9 pattern testing on KR Interface
                        0 = PCS is not able to support PRBS9 pattern testing on KR Interface  */
                    /*! \brief 03.0020.2 ROS 10GBASE-R PRBS31 Pattern Testing Ability
                        AQ_Pcs10G_Status_HHD.u0.bits_0._10gbase_rPrbs31PatternTestingAbility

                        Default = 0x1

                        1 = PCS is able to support PRBS31 pattern testing on KR Interface
                        0 = PCS is not able to support PRBS31 pattern testing on KR Interface
  */
      unsigned int   _10gbase_rPrbs31PatternTestingAbility : 1;    /* 03.0020.2  ROS      Default = 0x1 */
                     /* 1 = PCS is able to support PRBS31 pattern testing on KR Interface
                        0 = PCS is not able to support PRBS31 pattern testing on KR Interface  */
                    /*! \brief 03.0020.1 RO 10G High BER
                        AQ_Pcs10G_Status_HHD.u0.bits_0._10gHighBer

                        

                        1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                        

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. The interrupt for this bit is at 3.21.E. The status bit for medium BER is found in  See Global Alarms 2: Address 1E.CC01 .  */
      unsigned int   _10gHighBer : 1;    /* 03.0020.1  RO       */
                     /* 1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                          */
                    /*! \brief 03.0020.0 RO 10G PCS Block Lock
                        AQ_Pcs10G_Status_HHD.u0.bits_0._10gPcsBlockLock

                        

                        1 = 10GBASE-T PCS Framer is locked
                        0 = 10GBASE-T PCS Framer is not locked
                        
                        
                        

                 <B>Notes:</B>
                        When set, this bit indicates that 10G PCS Framer has acquired frame synchronization and is locked. The interrupt for this bit is at 3.21.F.  */
      unsigned int   _10gPcsBlockLock : 1;    /* 03.0020.0  RO       */
                     /* 1 = 10GBASE-T PCS Framer is locked
                        0 = 10GBASE-T PCS Framer is not locked
                        
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS 10G Status */
  union
  {
    struct
    {
                    /*! \brief 03.0021.F LL PCS Block Lock Latched
                        AQ_Pcs10G_Status_HHD.u1.bits_1.pcsBlockLockLatched

                        

                        1 = 10GBASE-T PCS Framer is Locked
                        0 = 10GBASE-T PCS Framer is not locked
                        

                 <B>Notes:</B>
                        When set, this bit indicates that 10G PCS Framer has acquired frame synchronization and is locked. This is the interrupt for bit 3.20.0.  See PHY XS Standard XGXS Lane Status - Address 4.18   */
      unsigned int   pcsBlockLockLatched : 1;    /* 03.0021.F  LL       */
                     /* 1 = 10GBASE-T PCS Framer is Locked
                        0 = 10GBASE-T PCS Framer is not locked
                          */
                    /*! \brief 03.0021.E LH High BER Latched
                        AQ_Pcs10G_Status_HHD.u1.bits_1.highBerLatched

                        

                        1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                        

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. This is the interrupt for bit 3.20.1.  See PHY XS Standard XGXS Lane Status - Address 4.18   */
      unsigned int   highBerLatched : 1;    /* 03.0021.E  LH       */
                     /* 1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                          */
                    /*! \brief 03.0021.D:8 SCT Errored Frame Counter [5:0]
                        AQ_Pcs10G_Status_HHD.u1.bits_1.erroredFrameCounter

                        Default = 0x00

                        A saturating count of the number of times a bad LDPC frame is received.
                        
                        

                 <B>Notes:</B>
                        Clear on read. In 10GBASE-T mode, this is taken from the state machine in Figure 55.14 in the 10GBASE-T specification. In 10GBASE-R mode, this is calculated using controls in   */
      unsigned int   erroredFrameCounter : 6;    /* 03.0021.D:8  SCT      Default = 0x00 */
                     /* A saturating count of the number of times a bad LDPC frame is received.
                        
                          */
                    /*! \brief 03.0021.7:0 SCT Errored Block Counter [7:0]
                        AQ_Pcs10G_Status_HHD.u1.bits_1.erroredBlockCounter

                        Default = 0x00

                        A saturating count of the number of times a bad 65B block is received.
                        

                 <B>Notes:</B>
                        Clear on read. In 10GBASE-T mode, this is taken from the state machine in Figure 55.16 in the 10GBASE-T specification.  */
      unsigned int   erroredBlockCounter : 8;    /* 03.0021.7:0  SCT      Default = 0x00 */
                     /* A saturating count of the number of times a bad 65B block is received.
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_Pcs10G_Status_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-R Test Pattern Seed A: 03.0022 */
/*                  PCS 10GBASE-R Test Pattern Seed A: 03.0022 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-R Test Pattern Seed A */
  union
  {
    struct
    {
                    /*! \brief 03.0022.F:0 R/WPD Test Pattern Seed A Bits 15:0 [F:0]
                        AQ_Pcs10G_base_rTestPatternSeedA_HHD.u0.bits_0.testPatternSeedABits_15_0

                        Provisionable Default = 0x0000

                        Test pattern seed A bits 15:0
  */
      unsigned int   testPatternSeedABits_15_0 : 16;    /* 03.0022.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed A bits 15:0  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS 10GBASE-R Test Pattern Seed A */
  union
  {
    struct
    {
                    /*! \brief 03.0023.F:0 R/WPD Test Pattern Seed A Bits 31:16 [1F:10]
                        AQ_Pcs10G_base_rTestPatternSeedA_HHD.u1.bits_1.testPatternSeedABits_31_16

                        Provisionable Default = 0x0000

                        Test pattern seed A bits 31:16
  */
      unsigned int   testPatternSeedABits_31_16 : 16;    /* 03.0023.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed A bits 31:16  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS 10GBASE-R Test Pattern Seed A */
  union
  {
    struct
    {
                    /*! \brief 03.0024.F:0 R/WPD Test Pattern Seed A Bits 47:32 [2F:20]
                        AQ_Pcs10G_base_rTestPatternSeedA_HHD.u2.bits_2.testPatternSeedABits_47_32

                        Provisionable Default = 0x0000

                        Test pattern seed A bits 47:32
  */
      unsigned int   testPatternSeedABits_47_32 : 16;    /* 03.0024.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed A bits 47:32  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS 10GBASE-R Test Pattern Seed A */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.0025.9:0 R/WPD Test Pattern Seed A Bits 57:48 [39:30]
                        AQ_Pcs10G_base_rTestPatternSeedA_HHD.u3.bits_3.testPatternSeedABits_57_48

                        Provisionable Default = 0x000

                        Test pattern seed A bits 57:48
  */
      unsigned int   testPatternSeedABits_57_48 : 10;    /* 03.0025.9:0  R/WPD      Provisionable Default = 0x000 */
                     /* Test pattern seed A bits 57:48  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_Pcs10G_base_rTestPatternSeedA_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-R Test Pattern Seed B: 03.0026 */
/*                  PCS 10GBASE-R Test Pattern Seed B: 03.0026 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-R Test Pattern Seed B */
  union
  {
    struct
    {
                    /*! \brief 03.0026.F:0 R/WPD Test Pattern Seed B Bits 15:0 [F:0]
                        AQ_Pcs10G_base_rTestPatternSeedB_HHD.u0.bits_0.testPatternSeedBBits_15_0

                        Provisionable Default = 0x0000

                        Test pattern seed B bits 15:0
  */
      unsigned int   testPatternSeedBBits_15_0 : 16;    /* 03.0026.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed B bits 15:0  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS 10GBASE-R Test Pattern Seed B */
  union
  {
    struct
    {
                    /*! \brief 03.0027.F:0 R/WPD Test Pattern Seed B Bits 31:16 [1F:10]
                        AQ_Pcs10G_base_rTestPatternSeedB_HHD.u1.bits_1.testPatternSeedBBits_31_16

                        Provisionable Default = 0x0000

                        Test pattern seed B bits 31:16
  */
      unsigned int   testPatternSeedBBits_31_16 : 16;    /* 03.0027.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed B bits 31:16  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS 10GBASE-R Test Pattern Seed B */
  union
  {
    struct
    {
                    /*! \brief 03.0028.F:0 R/WPD Test Pattern Seed B Bits 47:32 [2F:20]
                        AQ_Pcs10G_base_rTestPatternSeedB_HHD.u2.bits_2.testPatternSeedBBits_47_32

                        Provisionable Default = 0x0000

                        Test pattern seed B bits 47:32
  */
      unsigned int   testPatternSeedBBits_47_32 : 16;    /* 03.0028.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Test pattern seed B bits 47:32  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS 10GBASE-R Test Pattern Seed B */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.0029.9:0 R/WPD Test Pattern Seed B Bits 57:48 [39:30]
                        AQ_Pcs10G_base_rTestPatternSeedB_HHD.u3.bits_3.testPatternSeedBBits_57_48

                        Provisionable Default = 0x000

                        Test pattern seed B bits 57:48
  */
      unsigned int   testPatternSeedBBits_57_48 : 10;    /* 03.0029.9:0  R/WPD      Provisionable Default = 0x000 */
                     /* Test pattern seed B bits 57:48  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_Pcs10G_base_rTestPatternSeedB_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-R PCS Test-Pattern Control: 03.002A */
/*                  PCS 10GBASE-R PCS Test-Pattern Control: 03.002A */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-R PCS Test-Pattern Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 9;
                    /*! \brief 03.002A.6 R/WPD PRBS9 Transmit Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_HHD.u0.bits_0.prbs9TransmitTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable PRBS9 test-pattern mode on the transmit path
                        0 = Disable PRBS9 test-pattern mode on the transmit path
  */
      unsigned int   prbs9TransmitTest_patternEnable : 1;    /* 03.002A.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable PRBS9 test-pattern mode on the transmit path
                        0 = Disable PRBS9 test-pattern mode on the transmit path  */
                    /*! \brief 03.002A.5 R/WPD PRBS31 Receive Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_HHD.u0.bits_0.prbs31ReceiveTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable PRBS31 test-pattern mode on the receive path
                        0 = Enable PRBS31 test-pattern mode on the receive path
  */
      unsigned int   prbs31ReceiveTest_patternEnable : 1;    /* 03.002A.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable PRBS31 test-pattern mode on the receive path
                        0 = Enable PRBS31 test-pattern mode on the receive path  */
                    /*! \brief 03.002A.4 R/WPD PRBS31 Transmit Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_HHD.u0.bits_0.prbs31TransmitTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable PRBS31 test-pattern mode on the transmit path
                        0 = Enable PRBS31 test-pattern mode on the transmit path
  */
      unsigned int   prbs31TransmitTest_patternEnable : 1;    /* 03.002A.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable PRBS31 test-pattern mode on the transmit path
                        0 = Enable PRBS31 test-pattern mode on the transmit path  */
                    /*! \brief 03.002A.3 R/WPD Transmit Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_HHD.u0.bits_0.transmitTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable transmit test pattern
                        0 = Disable transmit test pattern
  */
      unsigned int   transmitTest_patternEnable : 1;    /* 03.002A.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable transmit test pattern
                        0 = Disable transmit test pattern  */
                    /*! \brief 03.002A.2 R/WPD Receive Test-Pattern Enable
                        AQ_Pcs10G_base_rPcsTest_patternControl_HHD.u0.bits_0.receiveTest_patternEnable

                        Provisionable Default = 0x0

                        1 = Enable receive test-pattern testing
                        0 = Disable receive test-pattern testing
  */
      unsigned int   receiveTest_patternEnable : 1;    /* 03.002A.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable receive test-pattern testing
                        0 = Disable receive test-pattern testing  */
                    /*! \brief 03.002A.1 R/WPD Test-Pattern Select
                        AQ_Pcs10G_base_rPcsTest_patternControl_HHD.u0.bits_0.test_patternSelect

                        Provisionable Default = 0x0

                        1 = Square wave test pattern
                        0 = Pseudo random test pattern
  */
      unsigned int   test_patternSelect : 1;    /* 03.002A.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Square wave test pattern
                        0 = Pseudo random test pattern  */
                    /*! \brief 03.002A.0 R/WPD Data Pattern Select
                        AQ_Pcs10G_base_rPcsTest_patternControl_HHD.u0.bits_0.dataPatternSelect

                        Provisionable Default = 0x0

                        1 = Zeros data pattern
                        0 = LF data pattern
  */
      unsigned int   dataPatternSelect : 1;    /* 03.002A.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Zeros data pattern
                        0 = LF data pattern  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pcs10G_base_rPcsTest_patternControl_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-R PCS Test-Pattern Error Counter: 03.002B */
/*                  PCS 10GBASE-R PCS Test-Pattern Error Counter: 03.002B */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-R PCS Test-Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 03.002B.F:0 R/WPD Test-Pattern Error Counter [F:0]
                        AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD.u0.bits_0.test_patternErrorCounter

                        Provisionable Default = 0x0000

                        Error Counter
  */
      unsigned int   test_patternErrorCounter : 16;    /* 03.002B.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Error Counter  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Pcs10G_base_rPcsTest_patternErrorCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PCS Capability: 03.1800 */
/*                  TimeSync PCS Capability: 03.1800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PCS Capability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.1800.1 RO TimeSync Transmit Path Data Delay
                        AQ_TimesyncPcsCapability_HHD.u0.bits_0.timesyncTransmitPathDataDelay

                        

                        1 = PCS provides information on transmit path data delay in registers 3.1801 through 3.1804
                        0 = PCS does not provide information on transmit path data delay
  */
      unsigned int   timesyncTransmitPathDataDelay : 1;    /* 03.1800.1  RO       */
                     /* 1 = PCS provides information on transmit path data delay in registers 3.1801 through 3.1804
                        0 = PCS does not provide information on transmit path data delay  */
                    /*! \brief 03.1800.0 RO TimeSync Receive Path Data Delay
                        AQ_TimesyncPcsCapability_HHD.u0.bits_0.timesyncReceivePathDataDelay

                        

                        1 = PCS provides information on receive path data delay in registers 3.1805 through 3.1808
                        0 = PCS does not provide information on receive path data delay
  */
      unsigned int   timesyncReceivePathDataDelay : 1;    /* 03.1800.0  RO       */
                     /* 1 = PCS provides information on receive path data delay in registers 3.1805 through 3.1808
                        0 = PCS does not provide information on receive path data delay  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_TimesyncPcsCapability_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PCS Transmit Path Data Delay: 03.1801 */
/*                  TimeSync PCS Transmit Path Data Delay: 03.1801 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PCS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.1801.F:0 RO Maximum PCS Transmit Path Data Delay LSW [F:0]
                        AQ_TimesyncPcsTransmitPathDataDelay_HHD.u0.bits_0.maximumPcsTransmitPathDataDelayLSW

                        

                        LSW of maximum PCS transmit delay in nanoseconds
  */
      unsigned int   maximumPcsTransmitPathDataDelayLSW : 16;    /* 03.1801.F:0  RO       */
                     /* LSW of maximum PCS transmit delay in nanoseconds  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of TimeSync PCS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.1802.F:0 RO Maximum PCS Transmit Path Data Delay MSW [F:0]
                        AQ_TimesyncPcsTransmitPathDataDelay_HHD.u1.bits_1.maximumPcsTransmitPathDataDelayMSW

                        

                        MSW of maximum PCS transmit delay in nanoseconds
  */
      unsigned int   maximumPcsTransmitPathDataDelayMSW : 16;    /* 03.1802.F:0  RO       */
                     /* MSW of maximum PCS transmit delay in nanoseconds  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of TimeSync PCS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.1803.F:0 RO Minimum PCS Transmit Path Data Delay LSW [F:0]
                        AQ_TimesyncPcsTransmitPathDataDelay_HHD.u2.bits_2.minimumPcsTransmitPathDataDelayLSW

                        

                        LSW of minimum PCS transmit delay in nanoseconds
  */
      unsigned int   minimumPcsTransmitPathDataDelayLSW : 16;    /* 03.1803.F:0  RO       */
                     /* LSW of minimum PCS transmit delay in nanoseconds  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of TimeSync PCS Transmit Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.1804.F:0 RO Minimum PCS Transmit Path Data Delay MSW [F:0]
                        AQ_TimesyncPcsTransmitPathDataDelay_HHD.u3.bits_3.minimumPcsTransmitPathDataDelayMSW

                        

                        MSW of minimum PCS transmit delay in nanoseconds
  */
      unsigned int   minimumPcsTransmitPathDataDelayMSW : 16;    /* 03.1804.F:0  RO       */
                     /* MSW of minimum PCS transmit delay in nanoseconds  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_TimesyncPcsTransmitPathDataDelay_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                TimeSync PCS Receive Path Data Delay: 03.1805 */
/*                  TimeSync PCS Receive Path Data Delay: 03.1805 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of TimeSync PCS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.1805.F:0 RO Maximum PCS Receive Path Data Delay LSW [F:0]
                        AQ_TimesyncPcsReceivePathDataDelay_HHD.u0.bits_0.maximumPcsReceivePathDataDelayLSW

                        

                        LSW of maximum PCS receive delay in nanoseconds
  */
      unsigned int   maximumPcsReceivePathDataDelayLSW : 16;    /* 03.1805.F:0  RO       */
                     /* LSW of maximum PCS receive delay in nanoseconds  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of TimeSync PCS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.1806.F:0 RO Maximum PCS Receive Path Data Delay MSW [F:0]
                        AQ_TimesyncPcsReceivePathDataDelay_HHD.u1.bits_1.maximumPcsReceivePathDataDelayMSW

                        

                        MSW of maximum PCS receive delay in nanoseconds
  */
      unsigned int   maximumPcsReceivePathDataDelayMSW : 16;    /* 03.1806.F:0  RO       */
                     /* MSW of maximum PCS receive delay in nanoseconds  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of TimeSync PCS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.1807.F:0 RO Minimum PCS Receive Path Data Delay LSW [F:0]
                        AQ_TimesyncPcsReceivePathDataDelay_HHD.u2.bits_2.minimumPcsReceivePathDataDelayLSW

                        

                        LSW of minimum PCS receive delay in nanoseconds
  */
      unsigned int   minimumPcsReceivePathDataDelayLSW : 16;    /* 03.1807.F:0  RO       */
                     /* LSW of minimum PCS receive delay in nanoseconds  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of TimeSync PCS Receive Path Data Delay */
  union
  {
    struct
    {
                    /*! \brief 03.1808.F:0 RO Minimum PCS Receive Path Data Delay MSW [F:0]
                        AQ_TimesyncPcsReceivePathDataDelay_HHD.u3.bits_3.minimumPcsReceivePathDataDelayMSW

                        

                        MSW of minimum PCS receive delay in nanoseconds
  */
      unsigned int   minimumPcsReceivePathDataDelayMSW : 16;    /* 03.1808.F:0  RO       */
                     /* MSW of minimum PCS receive delay in nanoseconds  */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_TimesyncPcsReceivePathDataDelay_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor Provisioning: 03.C400 */
/*                  PCS Transmit Vendor Provisioning: 03.C400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.C400.0 R/WPD PCS Tx Auxilliary Bit Value
                        AQ_PcsTransmitVendorProvisioning_HHD.u0.bits_0.pcsTxAuxilliaryBitValue

                        Provisionable Default = 0x0

                        The value that will be set in the auxilliary bit of the PCS transmission frame
                        

                 <B>Notes:</B>
                        This bit is currently undefined in the 802.3an standard.  */
      unsigned int   pcsTxAuxilliaryBitValue : 1;    /* 03.C400.0  R/WPD      Provisionable Default = 0x0 */
                     /* The value that will be set in the auxilliary bit of the PCS transmission frame
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitVendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Reserved Vendor Provisioning: 03.C410 */
/*                  PCS Transmit Reserved Vendor Provisioning: 03.C410 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C410.F:1 R/WPD Reserved Transmit Provisioning 1 [F:1]
                        AQ_PcsTransmitReservedVendorProvisioning_HHD.u0.bits_0.reservedTransmitProvisioning_1

                        Provisionable Default = 0x0000

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_1 : 15;    /* 03.C410.F:1  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future use
                          */
                    /*! \brief 03.C410.0 R/WPD PCS IEEE Loopback Passthrough Disable
                        AQ_PcsTransmitReservedVendorProvisioning_HHD.u0.bits_0.pcsIEEE_LoopbackPassthroughDisable

                        Provisionable Default = 0x0

                        1 = Disable data passthrough on IEEE loopback
                        

                 <B>Notes:</B>
                        When set, this bit disables the output of the PHY when IEEE loopback is set.  */
      unsigned int   pcsIEEE_LoopbackPassthroughDisable : 1;    /* 03.C410.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable data passthrough on IEEE loopback
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsTransmitReservedVendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI Vendor Provisioning: 03.C455 */
/*                  PCS Transmit XFI Vendor Provisioning: 03.C455 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C455.F:0 R/W XFI Test Pattern Seed A Word 0 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_HHD.u0.bits_0.xfiTestPatternSeedAWord_0

                        Default = 0x0000

                        XFI test pattern seed A bits 15:0
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_0 : 16;    /* 03.C455.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed A bits 15:0
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C456.F:0 R/W XFI Test Pattern Seed A Word 1 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_HHD.u1.bits_1.xfiTestPatternSeedAWord_1

                        Default = 0x0000

                        XFI test pattern seed A bits 31:16
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_1 : 16;    /* 03.C456.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed A bits 31:16
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C457.F:0 R/W XFI Test Pattern Seed A Word 2 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_HHD.u2.bits_2.xfiTestPatternSeedAWord_2

                        Default = 0x0000

                        XFI test pattern seed A bits 47:32
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_2 : 16;    /* 03.C457.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed A bits 47:32
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C458.9:0 R/W XFI Test Pattern Seed A Word 3 [9:0]
                        AQ_PcsTransmitXfiVendorProvisioning_HHD.u3.bits_3.xfiTestPatternSeedAWord_3

                        Default = 0x000

                        XFI test pattern seed A bits 57:48
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_3 : 10;    /* 03.C458.9:0  R/W      Default = 0x000 */
                     /* XFI test pattern seed A bits 57:48
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C459.F:0 R/W XFI Test Pattern Seed B Word 0 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_HHD.u4.bits_4.xfiTestPatternSeedBWord_0

                        Default = 0x0000

                        XFI test pattern seed B bits 15:0
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_0 : 16;    /* 03.C459.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed B bits 15:0
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C45A.F:0 R/W XFI Test Pattern Seed B Word 1 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_HHD.u5.bits_5.xfiTestPatternSeedBWord_1

                        Default = 0x0000

                        XFI test pattern seed B bits 31:16
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_1 : 16;    /* 03.C45A.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed B bits 31:16
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C45B.F:0 R/W XFI Test Pattern Seed B Word 2 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_HHD.u6.bits_6.xfiTestPatternSeedBWord_2

                        Default = 0x0000

                        XFI test pattern seed B bits 47:32
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_2 : 16;    /* 03.C45B.F:0  R/W      Default = 0x0000 */
                     /* XFI test pattern seed B bits 47:32
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C45C.9:0 R/W XFI Test Pattern Seed B Word 3 [9:0]
                        AQ_PcsTransmitXfiVendorProvisioning_HHD.u7.bits_7.xfiTestPatternSeedBWord_3

                        Default = 0x000

                        XFI test pattern seed B bits 57:48
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_3 : 10;    /* 03.C45C.9:0  R/W      Default = 0x000 */
                     /* XFI test pattern seed B bits 57:48
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
} AQ_PcsTransmitXfiVendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI0 Vendor Provisioning: 03.C460 */
/*                  PCS Transmit XFI0 Vendor Provisioning: 03.C460 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI0 Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.C460.1 R/WPD XFI0 PCS Scrambler Disable
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u0.bits_0.xfi0PcsScramblerDisable

                        Provisionable Default = 0x0

                        1 = Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Scrambler Disable (default: 0)  */
      unsigned int   xfi0PcsScramblerDisable : 1;    /* 03.C460.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable PCS scrambler
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI0 Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C461.9 R/W XFI0 Test Sqaure Wave Test Duration
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0TestSqaureWaveTestDuration

                        Default = 0x0

                        0 = 6 ones followed by 6 zeroes
                        1 = 11 ones followed by 11 zeroes
                        

                 <B>Notes:</B>
                        10GBASE-R Square Wave Test Duration. Repeating pattern of n ones, followed by n zeros, where n = 6 or 11 (0:n= 6, 1:n=11, default:0)
                          */
      unsigned int   xfi0TestSqaureWaveTestDuration : 1;    /* 03.C461.9  R/W      Default = 0x0 */
                     /* 0 = 6 ones followed by 6 zeroes
                        1 = 11 ones followed by 11 zeroes
                          */
                    /*! \brief 03.C461.8 R/W XFI0 Test Data Select
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0TestDataSelect

                        Default = 0x0

                        1 = Data pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Data Pattern Select (0:LF, 1:Zero, default:0)  */
      unsigned int   xfi0TestDataSelect : 1;    /* 03.C461.8  R/W      Default = 0x0 */
                     /* 1 = Data pattern select
                          */
                    /*! \brief 03.C461.7 R/W XFI0 Test Mode Select
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0TestModeSelect

                        Default = 0x0

                        1 = Test pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Select (0:Pseudo random, 1:Square wave, default:0)  */
      unsigned int   xfi0TestModeSelect : 1;    /* 03.C461.7  R/W      Default = 0x0 */
                     /* 1 = Test pattern select
                          */
                    /*! \brief 03.C461.6 R/W XFI0 Test PRBS-9 Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0TestPrbs_9Enable

                        Default = 0x0

                        1 = Test pattern PRBS-9 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 9 Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPrbs_9Enable : 1;    /* 03.C461.6  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-9 enabled
                          */
                    /*! \brief 03.C461.5 R/W XFI0 Test PRBS-31 Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0TestPrbs_31Enable

                        Default = 0x0

                        1 = Test pattern PRBS-31 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 31 Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPrbs_31Enable : 1;    /* 03.C461.5  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-31 enabled
                          */
                    /*! \brief 03.C461.4 R/W XFI0 Test Pattern Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0TestPatternEnable

                        Default = 0x0

                        1 = Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPatternEnable : 1;    /* 03.C461.4  R/W      Default = 0x0 */
                     /* 1 = Test pattern enabled
                          */
                    /*! \brief 03.C461.3 R/W XFI0 Local Fault Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0LocalFaultInject

                        Default = 0x0

                        1 = Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault (default:0)  */
      unsigned int   xfi0LocalFaultInject : 1;    /* 03.C461.3  R/W      Default = 0x0 */
                     /* 1 = Inject local fault
                          */
                    /*! \brief 03.C461.2 R/W XFI0 Inject Single Error
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0InjectSingleError

                        Default = 0x0

                        1 = Inject single Error
                        

                 <B>Notes:</B>
                        Inject single error on the 10GBASE-R Test Pattern including pseudo-random, PRB31 or PRBS9 (default:0)  */
      unsigned int   xfi0InjectSingleError : 1;    /* 03.C461.2  R/W      Default = 0x0 */
                     /* 1 = Inject single Error
                          */
                    /*! \brief 03.C461.1 R/W XFI0 PCS High BER Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0PcsHighBerInject

                        Default = 0x0

                        1 = Inject PCS High BER
                        

                 <B>Notes:</B>
                        Inject error to cause HI_BER at far-end (default:0)  */
      unsigned int   xfi0PcsHighBerInject : 1;    /* 03.C461.1  R/W      Default = 0x0 */
                     /* 1 = Inject PCS High BER
                          */
                    /*! \brief 03.C461.0 R/W XFI0 PCS Loss Of Lock Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_HHD.u1.bits_1.xfi0PcsLossOfLockInject

                        Default = 0x0

                        1 = Inject loss of lock
                        

                 <B>Notes:</B>
                        Inject error to cause loss of block_lock at far-end (default:0)  */
      unsigned int   xfi0PcsLossOfLockInject : 1;    /* 03.C461.0  R/W      Default = 0x0 */
                     /* 1 = Inject loss of lock
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitXfi0VendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI1 Vendor Provisioning: 03.C470 */
/*                  PCS Transmit XFI1 Vendor Provisioning: 03.C470 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI1 Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.C470.1 R/WPD XFI1 PCS Scrambler Disable
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u0.bits_0.xfi1PcsScramblerDisable

                        Provisionable Default = 0x0

                        1 = Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Scrambler Disable (default: 0)  */
      unsigned int   xfi1PcsScramblerDisable : 1;    /* 03.C470.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable PCS scrambler
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI1 Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C471.9 R/W XFI1 Test Sqaure Wave Test Duration
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1TestSqaureWaveTestDuration

                        Default = 0x0

                        0 = 6 ones followed by 6 zeroes
                        1 = 11 ones followed by 11 zeroes
                        

                 <B>Notes:</B>
                        10GBASE-R Square Wave Test Duration. Repeating pattern of n ones, followed by n zeros, where n = 6 or 11 (0:n= 6, 1:n=11, default:0)
                          */
      unsigned int   xfi1TestSqaureWaveTestDuration : 1;    /* 03.C471.9  R/W      Default = 0x0 */
                     /* 0 = 6 ones followed by 6 zeroes
                        1 = 11 ones followed by 11 zeroes
                          */
                    /*! \brief 03.C471.8 R/W XFI1 Test Data Select
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1TestDataSelect

                        Default = 0x0

                        1 = Data pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Data Pattern Select (0:LF, 1:Zero, default:0)  */
      unsigned int   xfi1TestDataSelect : 1;    /* 03.C471.8  R/W      Default = 0x0 */
                     /* 1 = Data pattern select
                          */
                    /*! \brief 03.C471.7 R/W XFI1 Test Mode Select
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1TestModeSelect

                        Default = 0x0

                        1 = Test pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Select (0:Pseudo random, 1:Square wave, default:0)  */
      unsigned int   xfi1TestModeSelect : 1;    /* 03.C471.7  R/W      Default = 0x0 */
                     /* 1 = Test pattern select
                          */
                    /*! \brief 03.C471.6 R/W XFI1 Test PRBS-9 Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1TestPrbs_9Enable

                        Default = 0x0

                        1 = Test pattern PRBS-9 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 9 Test Pattern Enable (0:disable, 1:enable, default:0)
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   xfi1TestPrbs_9Enable : 1;    /* 03.C471.6  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-9 enabled
                          */
                    /*! \brief 03.C471.5 R/W XFI1 Test PRBS-31 Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1TestPrbs_31Enable

                        Default = 0x0

                        1 = Test pattern PRBS-31 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 31 Test Pattern Enable (0:disable, 1:enable, default:0)
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   xfi1TestPrbs_31Enable : 1;    /* 03.C471.5  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-31 enabled
                          */
                    /*! \brief 03.C471.4 R/W XFI1 Test Pattern Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1TestPatternEnable

                        Default = 0x0

                        1 = Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi1TestPatternEnable : 1;    /* 03.C471.4  R/W      Default = 0x0 */
                     /* 1 = Test pattern enabled
                          */
                    /*! \brief 03.C471.3 R/W XFI1 Local Fault Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1LocalFaultInject

                        Default = 0x0

                        1 = Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault (default:0)  */
      unsigned int   xfi1LocalFaultInject : 1;    /* 03.C471.3  R/W      Default = 0x0 */
                     /* 1 = Inject local fault
                          */
                    /*! \brief 03.C471.2 R/W XFI1 Inject Single Error
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1InjectSingleError

                        Default = 0x0

                        1 = Inject single Error
                        

                 <B>Notes:</B>
                        Inject single error on the 10GBASE-R Test Pattern including pseudo-random, PRB31 or PRBS9 (default:0)  */
      unsigned int   xfi1InjectSingleError : 1;    /* 03.C471.2  R/W      Default = 0x0 */
                     /* 1 = Inject single Error
                          */
                    /*! \brief 03.C471.1 R/W XFI1 PCS High BER Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1PcsHighBerInject

                        Default = 0x0

                        1 = Inject PCS High BER
                        

                 <B>Notes:</B>
                        Inject error to cause HI_BER at far-end (default:0)  */
      unsigned int   xfi1PcsHighBerInject : 1;    /* 03.C471.1  R/W      Default = 0x0 */
                     /* 1 = Inject PCS High BER
                          */
                    /*! \brief 03.C471.0 R/W XFI1 PCS Loss Of Lock Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_HHD.u1.bits_1.xfi1PcsLossOfLockInject

                        Default = 0x0

                        1 = Inject loss of lock
                        

                 <B>Notes:</B>
                        Inject error to cause loss of block_lock at far-end (default:0)  */
      unsigned int   xfi1PcsLossOfLockInject : 1;    /* 03.C471.0  R/W      Default = 0x0 */
                     /* 1 = Inject loss of lock
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitXfi1VendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Memory Control Register: 03.C4C0 */
/*                  PCS USX0 Memory Control Register: 03.C4C0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Memory Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 9;
                    /*! \brief 03.C4C0.6 R/W USX0 Memory power down
                        AQ_PcsUsx0MemoryControlRegister_HHD.u0.bits_0.usx0MemoryPowerDown

                        Default = 0x0

                        USX0 Memory power down
                        
  */
      unsigned int   usx0MemoryPowerDown : 1;    /* 03.C4C0.6  R/W      Default = 0x0 */
                     /* USX0 Memory power down
                          */
                    /*! \brief 03.C4C0.5:0 R/W USX0 Memory RM [5:0]
                        AQ_PcsUsx0MemoryControlRegister_HHD.u0.bits_0.usx0MemoryRm

                        Default = 0x00

                        USX0 Memory RM bits
                        
  */
      unsigned int   usx0MemoryRm : 6;    /* 03.C4C0.5:0  R/W      Default = 0x00 */
                     /* USX0 Memory RM bits
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0MemoryControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Control Register: 03.C4C1 */
/*                  PCS USX0 Control Register: 03.C4C1 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4C1.F R/W USX0 Clock Enable
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0ClockEnable

                        Default = 0x1

                        USX0 Clock Enable
                        

                 <B>Notes:</B>
                        Enable clock of USX0 block  */
      unsigned int   usx0ClockEnable : 1;    /* 03.C4C1.F  R/W      Default = 0x1 */
                     /* USX0 Clock Enable
                          */
                    /*! \brief 03.C4C1.E R/W USX0 Bypass
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0Bypass

                        Default = 0x0

                        USX0 Bypass
                        

                 <B>Notes:</B>
                        Bypass USX0 block. This can be set to one to bypass USX for regular XFI 10G operation to reduce latency and power.   */
      unsigned int   usx0Bypass : 1;    /* 03.C4C1.E  R/W      Default = 0x0 */
                     /* USX0 Bypass
                          */
                    /*! \brief 03.C4C1.D R/W USX0 Link FIFO Mode
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0LinkFifoMode

                        Default = 0x0

                        USX0 Link FIFO Mode
                        

                 <B>Notes:</B>
                        This shall be set to one to enable frame-adaptation in USX0 for AQRate 5G/2.5G mode.   */
      unsigned int   usx0LinkFifoMode : 1;    /* 03.C4C1.D  R/W      Default = 0x0 */
                     /* USX0 Link FIFO Mode
                          */
                    /*! \brief 03.C4C1.C R/W USX0 Replication Mode
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0ReplicationMode

                        Default = 0x1

                        USX0 Replication Mode
                        

                 <B>Notes:</B>
                        Set to 1 to select word-based replication. Set to 0 to select byte-based replication. Always set this to 1 (default).  */
      unsigned int   usx0ReplicationMode : 1;    /* 03.C4C1.C  R/W      Default = 0x1 */
                     /* USX0 Replication Mode
                          */
      unsigned int   reserved0 : 4;
                    /*! \brief 03.C4C1.7 R/W USX0 PCS Reset
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0PcsReset

                        Default = 0x0

                        USX0 PCS Reset
                        

                 <B>Notes:</B>
                        PCS Reset  */
      unsigned int   usx0PcsReset : 1;    /* 03.C4C1.7  R/W      Default = 0x0 */
                     /* USX0 PCS Reset
                          */
                    /*! \brief 03.C4C1.6 R/W USX0 PCS low power
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0PcsLowPower

                        Default = 0x0

                        USX0 PCS low power
                        

                 <B>Notes:</B>
                        PCS Low Power  */
      unsigned int   usx0PcsLowPower : 1;    /* 03.C4C1.6  R/W      Default = 0x0 */
                     /* USX0 PCS low power
                          */
                    /*! \brief 03.C4C1.5 R/W USX0 Parity check sense
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0ParityCheckSense

                        Default = 0x0

                        USX0 Parity check sense (default:0)
                        

                 <B>Notes:</B>
                        Always leave to 0. Set to1 to force parity error for diagnostics.  */
      unsigned int   usx0ParityCheckSense : 1;    /* 03.C4C1.5  R/W      Default = 0x0 */
                     /* USX0 Parity check sense (default:0)
                          */
                    /*! \brief 03.C4C1.4:3 R/W USX0 Speed mode[1:0]
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0SpeedMode

                        Default = 0x0

                        USX0 Speed mode (00:based on AQRate mode, 10:1G, 11:100M)
                        

                 <B>Notes:</B>
                        Configure link speed. Set to 0 to select 10G or AQRate mode. Otherwise, set to 2 or 3 to select 1G or 100M mode.  */
      unsigned int   usx0SpeedMode : 2;    /* 03.C4C1.4:3  R/W      Default = 0x0 */
                     /* USX0 Speed mode (00:based on AQRate mode, 10:1G, 11:100M)
                          */
                    /*! \brief 03.C4C1.2:1 R/W USX0 AQRate mode[1:0]
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0AqrateMode

                        Default = 0x0

                        USX0 AQRate mode (00:10G, 10:5G, 11:2.5G)
                        

                 <B>Notes:</B>
                        This register is ignored if the USX0 Speed mode is set to non-zero (1G or 100M mode).  */
      unsigned int   usx0AqrateMode : 2;    /* 03.C4C1.2:1  R/W      Default = 0x0 */
                     /* USX0 AQRate mode (00:10G, 10:5G, 11:2.5G)
                          */
                    /*! \brief 03.C4C1.0 R/W USX0 XGS RKL mode
                        AQ_PcsUsx0ControlRegister_HHD.u0.bits_0.usx0XgsRklMode

                        Default = 0x0

                        USX0 XGS RKL mode
                        

                 <B>Notes:</B>
                        This shall be set to1 to enable XGS to support USX0.  */
      unsigned int   usx0XgsRklMode : 1;    /* 03.C4C1.0  R/W      Default = 0x0 */
                     /* USX0 XGS RKL mode
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0ControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Local fault Control Register: 03.C4C2 */
/*                  PCS USX0 Local fault Control Register: 03.C4C2 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Local fault Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 03.C4C2.8 R/W USX0 Inject Tx Local_Fault
                        AQ_PcsUsx0LocalFaultControlRegister_HHD.u0.bits_0.usx0InjectTxLocalFault

                        Default = 0x0

                        USX0 Inject Tx USXGMII Local_Fault (default:0)
                        

                 <B>Notes:</B>
                        Toggle this bit to inject single Local_Fault towards the external MAC.  */
      unsigned int   usx0InjectTxLocalFault : 1;    /* 03.C4C2.8  R/W      Default = 0x0 */
                     /* USX0 Inject Tx USXGMII Local_Fault (default:0)
                          */
                    /*! \brief 03.C4C2.7:0 R/W USX0 Local_Fault code[7:0]
                        AQ_PcsUsx0LocalFaultControlRegister_HHD.u0.bits_0.usx0LocalFaultCode

                        Default = 0x11

                        USX0 USXGMII Local_Fault code (default:0x11)
                        

                 <B>Notes:</B>
                        Configure the LSB 8-bit of the Local_Fault codeword.  */
      unsigned int   usx0LocalFaultCode : 8;    /* 03.C4C2.7:0  R/W      Default = 0x11 */
                     /* USX0 USXGMII Local_Fault code (default:0x11)
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0LocalFaultControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 MAC Local fault Control Register: 03.C4C3 */
/*                  PCS USX0 MAC Local fault Control Register: 03.C4C3 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 MAC Local fault Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4C3.F:8 R/W USX0 user define code[7:0]
                        AQ_PcsUsx0MacLocalFaultControlRegister_HHD.u0.bits_0.usx0UserDefineCode

                        Default = 0x01

                        USX0 User-defined code to replace USXGMII
                        Local_Fault received (default:0x01).
                        

                 <B>Notes:</B>
                        Configure the LSB 8-bit to replace the Rx USXGMII Local_Fault codeword if enabled.  */
      unsigned int   usx0UserDefineCode : 8;    /* 03.C4C3.F:8  R/W      Default = 0x01 */
                     /* USX0 User-defined code to replace USXGMII
                        Local_Fault received (default:0x01).
                          */
                    /*! \brief 03.C4C3.7 R/W USX0 Inject Local Fault signal
                        AQ_PcsUsx0MacLocalFaultControlRegister_HHD.u0.bits_0.usx0InjectLocalFaultSignal

                        Default = 0x0

                        USX0 Inject Local Fault signal towards the MAC in 1G/100M mode (default:0)
                        

                 <B>Notes:</B>
                        Set to1 to inject Local_Fault towards the external MAC in 1G/100M mode continuously with the progammable gap.  */
      unsigned int   usx0InjectLocalFaultSignal : 1;    /* 03.C4C3.7  R/W      Default = 0x0 */
                     /* USX0 Inject Local Fault signal towards the MAC in 1G/100M mode (default:0)
                          */
                    /*! \brief 03.C4C3.6:0 R/W USX0 Number of Idle coulmn[6:0]
                        AQ_PcsUsx0MacLocalFaultControlRegister_HHD.u0.bits_0.usx0NumberOfIdleCoulmn

                        Default = 0x1F

                        USX0 Number of Idle coulmn between Local Fault signals (0 to 127, default:31)
                        

                 <B>Notes:</B>
                        Configures the number of Idle column between Local_Fault signals during injection in 1G/100M mode.  */
      unsigned int   usx0NumberOfIdleCoulmn : 7;    /* 03.C4C3.6:0  R/W      Default = 0x1F */
                     /* USX0 Number of Idle coulmn between Local Fault signals (0 to 127, default:31)
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0MacLocalFaultControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Auto-Neg Control Register: 03.C4C4 */
/*                  PCS USX0 Auto-Neg Control Register: 03.C4C4 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Auto-Neg Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C4C4.9 R/W USX0 Restart Auto-Negotiation
                        AQ_PcsUsx0Auto_negControlRegister_HHD.u0.bits_0.usx0RestartAuto_negotiation

                        Default = 0x0

                        USX0 Restart Auto-Negotiation
                        

                 <B>Notes:</B>
                        Toggle this bit to restart USXGMII Auto-Negotiation.  */
      unsigned int   usx0RestartAuto_negotiation : 1;    /* 03.C4C4.9  R/W      Default = 0x0 */
                     /* USX0 Restart Auto-Negotiation
                          */
                    /*! \brief 03.C4C4.8 R/W USX0 Auto-neg Enable
                        AQ_PcsUsx0Auto_negControlRegister_HHD.u0.bits_0.usx0Auto_negEnable

                        Default = 0x0

                        USX0 Auto negotiation Enable
                        

                 <B>Notes:</B>
                        Set to 1 to enable USXGMII Auto-Negotiation.  */
      unsigned int   usx0Auto_negEnable : 1;    /* 03.C4C4.8  R/W      Default = 0x0 */
                     /* USX0 Auto negotiation Enable
                          */
                    /*! \brief 03.C4C4.7:0 R/W USX0 Auto neg Message code[7:0]
                        AQ_PcsUsx0Auto_negControlRegister_HHD.u0.bits_0.usx0AutoNegMessageCode

                        Default = 0x03

                        USX0 USXGMII Auto-Negotiation Message Opcode.
                        

                 <B>Notes:</B>
                        Configure the message opcode for USXGMII Auto-Negotiation.  */
      unsigned int   usx0AutoNegMessageCode : 8;    /* 03.C4C4.7:0  R/W      Default = 0x03 */
                     /* USX0 USXGMII Auto-Negotiation Message Opcode.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0Auto_negControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 PTP Control Register: 03.C4C5 */
/*                  PCS USX0 PTP Control Register: 03.C4C5 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 PTP Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.C4C5.B:8 R/W USX0 Tx Rsvd Control[3:0]
                        AQ_PcsUsx0PtpControlRegister_HHD.u0.bits_0.usx0TxRsvdControl

                        Default = 0x0

                        USX0 Transmit Reserved Control
                        

                 <B>Notes:</B>
                        Bit 0: Set to 1 to insert USXGMII Local Fault when the Link FIFO is empty
                        Bit 1: reserved
                        Bit 2: Set to 1 to swap bit-order of CRC
                        Bit 3: Set to 1 to swap byte-order of CRC  */
      unsigned int   usx0TxRsvdControl : 4;    /* 03.C4C5.B:8  R/W      Default = 0x0 */
                     /* USX0 Transmit Reserved Control
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.C4C5.6 R/W USX0 Header CRC Gen
                        AQ_PcsUsx0PtpControlRegister_HHD.u0.bits_0.usx0HeaderCrcGen

                        Default = 0x0

                        USX0 Header CRC Generation Enable
                        

                 <B>Notes:</B>
                        Set to 1 to generate CRC for the Packet Information Message and replace the SFD byte of transmit frame.  */
      unsigned int   usx0HeaderCrcGen : 1;    /* 03.C4C5.6  R/W      Default = 0x0 */
                     /* USX0 Header CRC Generation Enable
                          */
                    /*! \brief 03.C4C5.5 R/W USX0 Enable PTP timestamp
                        AQ_PcsUsx0PtpControlRegister_HHD.u0.bits_0.usx0EnablePtpTimestamp

                        Default = 0x0

                        USX0 Enable the injection of PTP timestamp into Extension Field of the Packet Information Message
                        

                 <B>Notes:</B>
                        Enable the injection of PTP timestamp into Extension Field of the Packet Information Message  */
      unsigned int   usx0EnablePtpTimestamp : 1;    /* 03.C4C5.5  R/W      Default = 0x0 */
                     /* USX0 Enable the injection of PTP timestamp into Extension Field of the Packet Information Message
                          */
                    /*! \brief 03.C4C5.4 R/W USX0 Enable Packet Information Message
                        AQ_PcsUsx0PtpControlRegister_HHD.u0.bits_0.usx0EnablePacketInformationMessage

                        Default = 0x0

                        USX0 Enable the injection of the Packet
                        Information Message
                        

                 <B>Notes:</B>
                        Enable the injection of the Packet Information Message   */
      unsigned int   usx0EnablePacketInformationMessage : 1;    /* 03.C4C5.4  R/W      Default = 0x0 */
                     /* USX0 Enable the injection of the Packet
                        Information Message
                          */
                    /*! \brief 03.C4C5.3:0 R/W USX0 GMII to XGMII Conversion Control[3:0]
                        AQ_PcsUsx0PtpControlRegister_HHD.u0.bits_0.usx0GmiiToXgmiiConversionControl

                        Default = 0x0

                        USX0 GMII/MII to XGMII Conversion Control
                        

                 <B>Notes:</B>
                        Bit 0: Disable continuous Idle insertion to
                        MAC when FIFO depth is below the IFG
                        thresh
                        Bit 1: Enable error char insertion to MAC
                        upon corrupted or missing SFD
                        Bit 2: Enable Idle deletion to MAC when
                        FIFO depth is beyond the high thresh
                        Bit 3: Reserved  */
      unsigned int   usx0GmiiToXgmiiConversionControl : 4;    /* 03.C4C5.3:0  R/W      Default = 0x0 */
                     /* USX0 GMII/MII to XGMII Conversion Control
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0PtpControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 PKT Info Message Register-0: 03.C4C6 */
/*                  PCS USX0 PKT Info Message Register-0: 03.C4C6 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 PKT Info Message Register-0 */
  union
  {
    struct
    {
                    /*! \brief 03.C4C6.F:0 R/W USX0 Packet info message 15:0 [F:0]
                        AQ_PcsUsx0PktInfoMessageRegister_0_HHD.u0.bits_0.usx0PacketInfoMessage_15_0

                        Default = 0x0000

                        USX0 Packet Information Message to be injected bits [15:0]
                        

                 <B>Notes:</B>
                        Configure the message word before enabling the injection.  */
      unsigned int   usx0PacketInfoMessage_15_0 : 16;    /* 03.C4C6.F:0  R/W      Default = 0x0000 */
                     /* USX0 Packet Information Message to be injected bits [15:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0PktInfoMessageRegister_0_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 PKT Info Message Register-1: 03.C4C7 */
/*                  PCS USX0 PKT Info Message Register-1: 03.C4C7 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 PKT Info Message Register-1 */
  union
  {
    struct
    {
                    /*! \brief 03.C4C7.F:0 R/W USX0 Packet info message 31:16 [1F:10]
                        AQ_PcsUsx0PktInfoMessageRegister_1_HHD.u0.bits_0.usx0PacketInfoMessage_31_16

                        Default = 0x0000

                        USX0 Packet Information Message to be injected bits [31:16]
                        
  */
      unsigned int   usx0PacketInfoMessage_31_16 : 16;    /* 03.C4C7.F:0  R/W      Default = 0x0000 */
                     /* USX0 Packet Information Message to be injected bits [31:16]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0PktInfoMessageRegister_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 PKT Info Message Register-2: 03.C4C8 */
/*                  PCS USX0 PKT Info Message Register-2: 03.C4C8 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 PKT Info Message Register-2 */
  union
  {
    struct
    {
                    /*! \brief 03.C4C8.F:0 R/W USX0 Packet info message 47:32 [2F:20]
                        AQ_PcsUsx0PktInfoMessageRegister_2_HHD.u0.bits_0.usx0PacketInfoMessage_47_32

                        Default = 0x0000

                        USX0 Packet Information Message to be injected bits [47:32]
                        
  */
      unsigned int   usx0PacketInfoMessage_47_32 : 16;    /* 03.C4C8.F:0  R/W      Default = 0x0000 */
                     /* USX0 Packet Information Message to be injected bits [47:32]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0PktInfoMessageRegister_2_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 link Fill Data Register-0: 03.C4C9 */
/*                  PCS USX0 link Fill Data Register-0: 03.C4C9 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 link Fill Data Register-0 */
  union
  {
    struct
    {
                    /*! \brief 03.C4C9.F:0 R/W USX0 XGMII Link Fill Word[F:0]
                        AQ_PcsUsx0LinkFillDataRegister_0_HHD.u0.bits_0.usx0XgmiiLinkFillWord

                        Default = 0xBAD1

                        USX0 XGMII data for link fill word[15:0]
                        

                 <B>Notes:</B>
                        This has to be different from
                        normal control words in standard XGMII
                        traffic.  */
      unsigned int   usx0XgmiiLinkFillWord : 16;    /* 03.C4C9.F:0  R/W      Default = 0xBAD1 */
                     /* USX0 XGMII data for link fill word[15:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0LinkFillDataRegister_0_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 link Fill Data Register-1: 03.C4CA */
/*                  PCS USX0 link Fill Data Register-1: 03.C4CA */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 link Fill Data Register-1 */
  union
  {
    struct
    {
                    /*! \brief 03.C4CA.F:0 R/W USX0 XGMII Link Fill Word[1F:10]
                        AQ_PcsUsx0LinkFillDataRegister_1_HHD.u0.bits_0.usx0XgmiiLinkFillWord

                        Default = 0xBAD2

                        USX0 XGMII data for link fill word[31:16]
                        
  */
      unsigned int   usx0XgmiiLinkFillWord : 16;    /* 03.C4CA.F:0  R/W      Default = 0xBAD2 */
                     /* USX0 XGMII data for link fill word[31:16]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0LinkFillDataRegister_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Link FIFO Control Register: 03.C4CB */
/*                  PCS USX0 Link FIFO Control Register: 03.C4CB */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Link FIFO Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4CB.F:A R/W USX0 High Threshold[5:0]
                        AQ_PcsUsx0LinkFifoControlRegister_HHD.u0.bits_0.usx0HighThreshold

                        Default = 0x14

                        USX0 Configure the high threshold for the link FIFO
                        

                 <B>Notes:</B>
                        When the link FIFO is beyond this threshold, it requests the upstream to pause traffic by inserting link fill words. When link FIFO mode is set to one, idle words can also be deleted.  */
      unsigned int   usx0HighThreshold : 6;    /* 03.C4CB.F:A  R/W      Default = 0x14 */
                     /* USX0 Configure the high threshold for the link FIFO
                          */
                    /*! \brief 03.C4CB.9:5 R/W USX0 Low Threshold[4:0]
                        AQ_PcsUsx0LinkFifoControlRegister_HHD.u0.bits_0.usx0LowThreshold

                        Default = 0x0A

                        USX0 Configure the low threshold for the link FIFO
                        

                 <B>Notes:</B>
                        When the link FIFO is below this threshold, idle words can be inserted if link FIFO mode is set to one.  */
      unsigned int   usx0LowThreshold : 5;    /* 03.C4CB.9:5  R/W      Default = 0x0A */
                     /* USX0 Configure the low threshold for the link FIFO
                          */
                    /*! \brief 03.C4CB.4 R/W USX0 Link Fifo Reset
                        AQ_PcsUsx0LinkFifoControlRegister_HHD.u0.bits_0.usx0LinkFifoReset

                        Default = 0x0

                        USX0 Set to 1 to force link FIFO to reset This FIFO is only used for AQRate
                        5G/2.5G mode.
                        
  */
      unsigned int   usx0LinkFifoReset : 1;    /* 03.C4CB.4  R/W      Default = 0x0 */
                     /* USX0 Set to 1 to force link FIFO to reset This FIFO is only used for AQRate
                        5G/2.5G mode.
                          */
                    /*! \brief 03.C4CB.3:0 R/W USX0 Link Fill Control[3:0]
                        AQ_PcsUsx0LinkFifoControlRegister_HHD.u0.bits_0.usx0LinkFillControl

                        Default = 0xF

                        USX0 XGMII control for link fill word.
                        
  */
      unsigned int   usx0LinkFillControl : 4;    /* 03.C4CB.3:0  R/W      Default = 0xF */
                     /* USX0 XGMII control for link fill word.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0LinkFifoControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 TX FIFO Control Register: 03.C4CC */
/*                  PCS USX0 TX FIFO Control Register: 03.C4CC */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 TX FIFO Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 3;
                    /*! \brief 03.C4CC.C R/W USX0 TX FIFO Reset
                        AQ_PcsUsx0TxFifoControlRegister_HHD.u0.bits_0.usx0TxFifoReset

                        Default = 0x0

                        USX0 MAC Tx FIFO reset
                        
  */
      unsigned int   usx0TxFifoReset : 1;    /* 03.C4CC.C  R/W      Default = 0x0 */
                     /* USX0 MAC Tx FIFO reset
                          */
                    /*! \brief 03.C4CC.B:8 R/W USX0 TX FIFO threshold[3:0]
                        AQ_PcsUsx0TxFifoControlRegister_HHD.u0.bits_0.usx0TxFifoThreshold

                        Default = 0x1

                        USX0 MAC Tx FIFO threshold
                        This is used to establish minimum FIFO
                        depth before starting to read.
                        
  */
      unsigned int   usx0TxFifoThreshold : 4;    /* 03.C4CC.B:8  R/W      Default = 0x1 */
                     /* USX0 MAC Tx FIFO threshold
                        This is used to establish minimum FIFO
                        depth before starting to read.
                          */
                    /*! \brief 03.C4CC.7:4 R/W USX0 Tx FIFO IFG threshold[3:0]
                        AQ_PcsUsx0TxFifoControlRegister_HHD.u0.bits_0.usx0TxFifoIfgThreshold

                        Default = 0x8

                        USX0 MAC Tx FIFO IFG threshold
                        This is used to insert Idle when FIFO depth is below this threshold.
                        
  */
      unsigned int   usx0TxFifoIfgThreshold : 4;    /* 03.C4CC.7:4  R/W      Default = 0x8 */
                     /* USX0 MAC Tx FIFO IFG threshold
                        This is used to insert Idle when FIFO depth is below this threshold.
                          */
                    /*! \brief 03.C4CC.3:0 R/W USX0 Tx FIFO hi threshold[3:0]
                        AQ_PcsUsx0TxFifoControlRegister_HHD.u0.bits_0.usx0TxFifoHiThreshold

                        Default = 0xA

                        USX0 MAC Tx FIFO High threshold
                        This is used to delete Idle when FIFO depth is beyond this threshold.
                        
  */
      unsigned int   usx0TxFifoHiThreshold : 4;    /* 03.C4CC.3:0  R/W      Default = 0xA */
                     /* USX0 MAC Tx FIFO High threshold
                        This is used to delete Idle when FIFO depth is beyond this threshold.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0TxFifoControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Local Advertisement Register: 03.C4CD */
/*                  PCS USX0 Local Advertisement Register: 03.C4CD */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Local Advertisement Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4CD.F R/W USX0 Local Advertisement Status
                        AQ_PcsUsx0LocalAdvertisementRegister_HHD.u0.bits_0.usx0LocalAdvertisementStatus

                        Default = 0x0

                        USX0 Local advertisement status.
                        0 = Link down
                        1 = Link up
                        
  */
      unsigned int   usx0LocalAdvertisementStatus : 1;    /* 03.C4CD.F  R/W      Default = 0x0 */
                     /* USX0 Local advertisement status.
                        0 = Link down
                        1 = Link up
                          */
                    /*! \brief 03.C4CD.E:D R/W Reserved USX0 Local Advertisement 0 [1:0]
                        AQ_PcsUsx0LocalAdvertisementRegister_HHD.u0.bits_0.reservedUsx0LocalAdvertisement_0

                        Default = 0x0

                        Reserved for future use.
                        
  */
      unsigned int   reservedUsx0LocalAdvertisement_0 : 2;    /* 03.C4CD.E:D  R/W      Default = 0x0 */
                     /* Reserved for future use.
                          */
                    /*! \brief 03.C4CD.C R/W USX0 Local Advertisement Duplex
                        AQ_PcsUsx0LocalAdvertisementRegister_HHD.u0.bits_0.usx0LocalAdvertisementDuplex

                        Default = 0x0

                        USX0 Local advertisement duplex.
                        0 = Half duplex
                        1 = Full duplex
                        
  */
      unsigned int   usx0LocalAdvertisementDuplex : 1;    /* 03.C4CD.C  R/W      Default = 0x0 */
                     /* USX0 Local advertisement duplex.
                        0 = Half duplex
                        1 = Full duplex
                          */
                    /*! \brief 03.C4CD.B:9 R/W USX0 Local Advertisement Speed [2:0]
                        AQ_PcsUsx0LocalAdvertisementRegister_HHD.u0.bits_0.usx0LocalAdvertisementSpeed

                        Default = 0x0

                        USX0 Local advertisement speed.
                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                        
  */
      unsigned int   usx0LocalAdvertisementSpeed : 3;    /* 03.C4CD.B:9  R/W      Default = 0x0 */
                     /* USX0 Local advertisement speed.
                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                          */
                    /*! \brief 03.C4CD.8 R/W USX0 Local Advertisement EEE Capability
                        AQ_PcsUsx0LocalAdvertisementRegister_HHD.u0.bits_0.usx0LocalAdvertisementEeeCapability

                        Default = 0x0

                        USX0 Local advertisement EEE capability.
                        0 = Not supported
                        1 = Supported
                        
  */
      unsigned int   usx0LocalAdvertisementEeeCapability : 1;    /* 03.C4CD.8  R/W      Default = 0x0 */
                     /* USX0 Local advertisement EEE capability.
                        0 = Not supported
                        1 = Supported
                          */
                    /*! \brief 03.C4CD.7 R/W USX0 Local Advertisement EEE Clock Stop Capability
                        AQ_PcsUsx0LocalAdvertisementRegister_HHD.u0.bits_0.usx0LocalAdvertisementEeeClockStopCapability

                        Default = 0x0

                        USX0 Local advertisement EEE Clock Stop capability.
                        0 = Not supported
                        1 = Supported
                        
  */
      unsigned int   usx0LocalAdvertisementEeeClockStopCapability : 1;    /* 03.C4CD.7  R/W      Default = 0x0 */
                     /* USX0 Local advertisement EEE Clock Stop capability.
                        0 = Not supported
                        1 = Supported
                          */
                    /*! \brief 03.C4CD.6:1 R/W Reserved USX0 Local Advertisement 1 [5:0]
                        AQ_PcsUsx0LocalAdvertisementRegister_HHD.u0.bits_0.reservedUsx0LocalAdvertisement_1

                        Default = 0x00

                        Reserved for future use.
                        
  */
      unsigned int   reservedUsx0LocalAdvertisement_1 : 6;    /* 03.C4CD.6:1  R/W      Default = 0x00 */
                     /* Reserved for future use.
                          */
                    /*! \brief 03.C4CD.0 R/W USX0 Local Advertisement Mode
                        AQ_PcsUsx0LocalAdvertisementRegister_HHD.u0.bits_0.usx0LocalAdvertisementMode

                        Default = 0x1

                        USX0 Local advertisement mode.
                        0 = SGMII
                        1 = USXGMII
                        
  */
      unsigned int   usx0LocalAdvertisementMode : 1;    /* 03.C4CD.0  R/W      Default = 0x1 */
                     /* USX0 Local advertisement mode.
                        0 = SGMII
                        1 = USXGMII
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0LocalAdvertisementRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Memory Control Register: 03.C4E0 */
/*                  PCS USX1 Memory Control Register: 03.C4E0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Memory Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 9;
                    /*! \brief 03.C4E0.6 R/W USX1 Memory power down
                        AQ_PcsUsx1MemoryControlRegister_HHD.u0.bits_0.usx1MemoryPowerDown

                        Default = 0x0

                        USX1 Memory power down
                        
  */
      unsigned int   usx1MemoryPowerDown : 1;    /* 03.C4E0.6  R/W      Default = 0x0 */
                     /* USX1 Memory power down
                          */
                    /*! \brief 03.C4E0.5:0 R/W USX1 Memory RM [5:0]
                        AQ_PcsUsx1MemoryControlRegister_HHD.u0.bits_0.usx1MemoryRm

                        Default = 0x00

                        USX1 Memory RM bits
                        
  */
      unsigned int   usx1MemoryRm : 6;    /* 03.C4E0.5:0  R/W      Default = 0x00 */
                     /* USX1 Memory RM bits
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1MemoryControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Control Register: 03.C4E1 */
/*                  PCS USX1 Control Register: 03.C4E1 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4E1.F R/W USX1 Clock Enable
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1ClockEnable

                        Default = 0x1

                        USX1 Clock Enable
                        

                 <B>Notes:</B>
                        Enable clock of USX1 block  */
      unsigned int   usx1ClockEnable : 1;    /* 03.C4E1.F  R/W      Default = 0x1 */
                     /* USX1 Clock Enable
                          */
                    /*! \brief 03.C4E1.E R/W USX1 Bypass
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1Bypass

                        Default = 0x0

                        USX1 Bypass
                        

                 <B>Notes:</B>
                        Bypass USX1 block. This can be set to one to bypass USX for regular XFI 10G operation to reduce latency and power.   */
      unsigned int   usx1Bypass : 1;    /* 03.C4E1.E  R/W      Default = 0x0 */
                     /* USX1 Bypass
                          */
                    /*! \brief 03.C4E1.D R/W USX1 Link FIFO Mode
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1LinkFifoMode

                        Default = 0x0

                        USX1 Link FIFO Mode
                        

                 <B>Notes:</B>
                        This can be set to one to enable frame-adaptation in USX1 for AQRate 5G/2.5G mode.   */
      unsigned int   usx1LinkFifoMode : 1;    /* 03.C4E1.D  R/W      Default = 0x0 */
                     /* USX1 Link FIFO Mode
                          */
                    /*! \brief 03.C4E1.C R/W USX1 Replication Mode
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1ReplicationMode

                        Default = 0x1

                        USX1 Replication Mode
                        

                 <B>Notes:</B>
                        Set to 1 to select word-based replication. Set to 0 to select byte-based replication. Always set this to 1 (default).  */
      unsigned int   usx1ReplicationMode : 1;    /* 03.C4E1.C  R/W      Default = 0x1 */
                     /* USX1 Replication Mode
                          */
      unsigned int   reserved0 : 4;
                    /*! \brief 03.C4E1.7 R/W USX1 PCS Reset
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1PcsReset

                        Default = 0x0

                        USX1 PCS Reset
                        
  */
      unsigned int   usx1PcsReset : 1;    /* 03.C4E1.7  R/W      Default = 0x0 */
                     /* USX1 PCS Reset
                          */
                    /*! \brief 03.C4E1.6 R/W USX1 PCS low power
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1PcsLowPower

                        Default = 0x0

                        USX1 PCS low power
                        
  */
      unsigned int   usx1PcsLowPower : 1;    /* 03.C4E1.6  R/W      Default = 0x0 */
                     /* USX1 PCS low power
                          */
                    /*! \brief 03.C4E1.5 R/W USX1 Parity check sense
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1ParityCheckSense

                        Default = 0x0

                        USX1 Parity check sense
                        
  */
      unsigned int   usx1ParityCheckSense : 1;    /* 03.C4E1.5  R/W      Default = 0x0 */
                     /* USX1 Parity check sense
                          */
                    /*! \brief 03.C4E1.4:3 R/W USX1 Speed mode[1:0]
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1SpeedMode

                        Default = 0x0

                        USX1 Speed mode (00:10G, 10:1G, 11:100M)
                        
  */
      unsigned int   usx1SpeedMode : 2;    /* 03.C4E1.4:3  R/W      Default = 0x0 */
                     /* USX1 Speed mode (00:10G, 10:1G, 11:100M)
                          */
                    /*! \brief 03.C4E1.2:1 R/W USX1 AQRate mode[1:0]
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1AqrateMode

                        Default = 0x0

                        USX1 AQRate mode (00:10G, 10:5G, 11:2.5G)
                        
  */
      unsigned int   usx1AqrateMode : 2;    /* 03.C4E1.2:1  R/W      Default = 0x0 */
                     /* USX1 AQRate mode (00:10G, 10:5G, 11:2.5G)
                          */
                    /*! \brief 03.C4E1.0 R/W USX1 XGS RKL mode
                        AQ_PcsUsx1ControlRegister_HHD.u0.bits_0.usx1XgsRklMode

                        Default = 0x0

                        USX1 XGS RKL mode
                        
  */
      unsigned int   usx1XgsRklMode : 1;    /* 03.C4E1.0  R/W      Default = 0x0 */
                     /* USX1 XGS RKL mode
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1ControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Local fault Control Register: 03.C4E2 */
/*                  PCS USX1 Local fault Control Register: 03.C4E2 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Local fault Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 03.C4E2.8 R/W USX1 Inject Tx Local_Fault
                        AQ_PcsUsx1LocalFaultControlRegister_HHD.u0.bits_0.usx1InjectTxLocalFault

                        Default = 0x0

                        USX1 Inject Tx USXGMII Local_Fault
                        
  */
      unsigned int   usx1InjectTxLocalFault : 1;    /* 03.C4E2.8  R/W      Default = 0x0 */
                     /* USX1 Inject Tx USXGMII Local_Fault
                          */
                    /*! \brief 03.C4E2.7:0 R/W USX1 Local_Fault code[7:0]
                        AQ_PcsUsx1LocalFaultControlRegister_HHD.u0.bits_0.usx1LocalFaultCode

                        Default = 0x11

                        USX1 USXGMII Local_Fault code
                        
  */
      unsigned int   usx1LocalFaultCode : 8;    /* 03.C4E2.7:0  R/W      Default = 0x11 */
                     /* USX1 USXGMII Local_Fault code
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1LocalFaultControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 MAC Local fault Control Register: 03.C4E3 */
/*                  PCS USX1 MAC Local fault Control Register: 03.C4E3 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 MAC Local fault Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4E3.F:8 R/W USX1 user define code[7:0]
                        AQ_PcsUsx1MacLocalFaultControlRegister_HHD.u0.bits_0.usx1UserDefineCode

                        Default = 0x01

                        USX1 User-defined code to replace USXGMII
                        Local_Fault received.
                        
  */
      unsigned int   usx1UserDefineCode : 8;    /* 03.C4E3.F:8  R/W      Default = 0x01 */
                     /* USX1 User-defined code to replace USXGMII
                        Local_Fault received.
                          */
                    /*! \brief 03.C4E3.7 R/W USX1 Inject Local Fault signal
                        AQ_PcsUsx1MacLocalFaultControlRegister_HHD.u0.bits_0.usx1InjectLocalFaultSignal

                        Default = 0x0

                        USX1 Inject Local Fault signal towards the MAC in 1G/100M mode
                        
  */
      unsigned int   usx1InjectLocalFaultSignal : 1;    /* 03.C4E3.7  R/W      Default = 0x0 */
                     /* USX1 Inject Local Fault signal towards the MAC in 1G/100M mode
                          */
                    /*! \brief 03.C4E3.6:0 R/W USX1 Number of Idle coulmn[6:0]
                        AQ_PcsUsx1MacLocalFaultControlRegister_HHD.u0.bits_0.usx1NumberOfIdleCoulmn

                        Default = 0x1F

                        USX1 Number of Idle coulmn between Local Fault signals
                        
  */
      unsigned int   usx1NumberOfIdleCoulmn : 7;    /* 03.C4E3.6:0  R/W      Default = 0x1F */
                     /* USX1 Number of Idle coulmn between Local Fault signals
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1MacLocalFaultControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Auto-Neg Control Register: 03.C4E4 */
/*                  PCS USX1 Auto-Neg Control Register: 03.C4E4 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Auto-Neg Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C4E4.9 R/W USX1 Restart Auto-Negotiation
                        AQ_PcsUsx1Auto_negControlRegister_HHD.u0.bits_0.usx1RestartAuto_negotiation

                        Default = 0x0

                        USX1 Restart Auto-Negotiation
                        
  */
      unsigned int   usx1RestartAuto_negotiation : 1;    /* 03.C4E4.9  R/W      Default = 0x0 */
                     /* USX1 Restart Auto-Negotiation
                          */
                    /*! \brief 03.C4E4.8 R/W USX1 Auto-neg Enable
                        AQ_PcsUsx1Auto_negControlRegister_HHD.u0.bits_0.usx1Auto_negEnable

                        Default = 0x0

                        USX1 Auto negotiation Enable
                        
  */
      unsigned int   usx1Auto_negEnable : 1;    /* 03.C4E4.8  R/W      Default = 0x0 */
                     /* USX1 Auto negotiation Enable
                          */
                    /*! \brief 03.C4E4.7:0 R/W USX1 Auto neg Message code[7:0]
                        AQ_PcsUsx1Auto_negControlRegister_HHD.u0.bits_0.usx1AutoNegMessageCode

                        Default = 0x03

                        USX1 USXGMII Auto-Negotiation Message Opcode.
                        
  */
      unsigned int   usx1AutoNegMessageCode : 8;    /* 03.C4E4.7:0  R/W      Default = 0x03 */
                     /* USX1 USXGMII Auto-Negotiation Message Opcode.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1Auto_negControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 PTP Control Register: 03.C4E5 */
/*                  PCS USX1 PTP Control Register: 03.C4E5 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 PTP Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.C4E5.B:8 R/W USX1 Tx Rsvd Control[3:0]
                        AQ_PcsUsx1PtpControlRegister_HHD.u0.bits_0.usx1TxRsvdControl

                        Default = 0x0

                        USX1 Transmit Reserved Control
                        
  */
      unsigned int   usx1TxRsvdControl : 4;    /* 03.C4E5.B:8  R/W      Default = 0x0 */
                     /* USX1 Transmit Reserved Control
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.C4E5.6 R/W USX1 Header CRC Gen
                        AQ_PcsUsx1PtpControlRegister_HHD.u0.bits_0.usx1HeaderCrcGen

                        Default = 0x0

                        USX1 Header CRC Generation Enable
                        
  */
      unsigned int   usx1HeaderCrcGen : 1;    /* 03.C4E5.6  R/W      Default = 0x0 */
                     /* USX1 Header CRC Generation Enable
                          */
                    /*! \brief 03.C4E5.5 R/W USX1 Enable PTP timestamp
                        AQ_PcsUsx1PtpControlRegister_HHD.u0.bits_0.usx1EnablePtpTimestamp

                        Default = 0x0

                        USX1 Enable the injection of PTP timestamp into Extension Field of the Packet Information Message
                        
  */
      unsigned int   usx1EnablePtpTimestamp : 1;    /* 03.C4E5.5  R/W      Default = 0x0 */
                     /* USX1 Enable the injection of PTP timestamp into Extension Field of the Packet Information Message
                          */
                    /*! \brief 03.C4E5.4 R/W USX1 Enable Packet Information Message
                        AQ_PcsUsx1PtpControlRegister_HHD.u0.bits_0.usx1EnablePacketInformationMessage

                        Default = 0x0

                        USX1 Enable the injection of the Packet
                        Information Message
                        
  */
      unsigned int   usx1EnablePacketInformationMessage : 1;    /* 03.C4E5.4  R/W      Default = 0x0 */
                     /* USX1 Enable the injection of the Packet
                        Information Message
                          */
                    /*! \brief 03.C4E5.3:0 R/W USX1 GMII to XGMII Conversion Control[3:0]
                        AQ_PcsUsx1PtpControlRegister_HHD.u0.bits_0.usx1GmiiToXgmiiConversionControl

                        Default = 0x0

                        USX1 GMII/MII to XGMII Conversion Control
                        Bit 0: Disable continuous Idle insertion to
                        MAC when FIFO depth is below the IFG
                        thresh
                        Bit 1: Enable error char insertion to MAC
                        upon corrupted or missing SFD
                        Bit 2: Enable Idle deletion to MAC when
                        FIFO depth is beyond the high thresh
                        Bit 3: Reserved
                        
  */
      unsigned int   usx1GmiiToXgmiiConversionControl : 4;    /* 03.C4E5.3:0  R/W      Default = 0x0 */
                     /* USX1 GMII/MII to XGMII Conversion Control
                        Bit 0: Disable continuous Idle insertion to
                        MAC when FIFO depth is below the IFG
                        thresh
                        Bit 1: Enable error char insertion to MAC
                        upon corrupted or missing SFD
                        Bit 2: Enable Idle deletion to MAC when
                        FIFO depth is beyond the high thresh
                        Bit 3: Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1PtpControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 PKT Info Message Register-0: 03.C4E6 */
/*                  PCS USX1 PKT Info Message Register-0: 03.C4E6 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 PKT Info Message Register-0 */
  union
  {
    struct
    {
                    /*! \brief 03.C4E6.F:0 R/W USX1 Packet info message 15:0 [F:0]
                        AQ_PcsUsx1PktInfoMessageRegister_0_HHD.u0.bits_0.usx1PacketInfoMessage_15_0

                        Default = 0x0000

                        USX1 Packet Information Message to be injected bits [15:0]
                        
  */
      unsigned int   usx1PacketInfoMessage_15_0 : 16;    /* 03.C4E6.F:0  R/W      Default = 0x0000 */
                     /* USX1 Packet Information Message to be injected bits [15:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1PktInfoMessageRegister_0_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 PKT Info Message Register-1: 03.C4E7 */
/*                  PCS USX1 PKT Info Message Register-1: 03.C4E7 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 PKT Info Message Register-1 */
  union
  {
    struct
    {
                    /*! \brief 03.C4E7.F:0 R/W USX1 Packet info message 31:16 [1F:10]
                        AQ_PcsUsx1PktInfoMessageRegister_1_HHD.u0.bits_0.usx1PacketInfoMessage_31_16

                        Default = 0x0000

                        USX1 Packet Information Message to be injected bits [31:16]
                        
  */
      unsigned int   usx1PacketInfoMessage_31_16 : 16;    /* 03.C4E7.F:0  R/W      Default = 0x0000 */
                     /* USX1 Packet Information Message to be injected bits [31:16]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1PktInfoMessageRegister_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 PKT Info Message Register-2: 03.C4E8 */
/*                  PCS USX1 PKT Info Message Register-2: 03.C4E8 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 PKT Info Message Register-2 */
  union
  {
    struct
    {
                    /*! \brief 03.C4E8.F:0 R/W USX1 Packet info message 47:32 [2F:20]
                        AQ_PcsUsx1PktInfoMessageRegister_2_HHD.u0.bits_0.usx1PacketInfoMessage_47_32

                        Default = 0x0000

                        USX1 Packet Information Message to be injected bits [47:32]
                        
  */
      unsigned int   usx1PacketInfoMessage_47_32 : 16;    /* 03.C4E8.F:0  R/W      Default = 0x0000 */
                     /* USX1 Packet Information Message to be injected bits [47:32]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1PktInfoMessageRegister_2_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 link Fill Data Register-0: 03.C4E9 */
/*                  PCS USX1 link Fill Data Register-0: 03.C4E9 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 link Fill Data Register-0 */
  union
  {
    struct
    {
                    /*! \brief 03.C4E9.F:0 R/W USX1 XGMII Link Fill Word[F:0]
                        AQ_PcsUsx1LinkFillDataRegister_0_HHD.u0.bits_0.usx1XgmiiLinkFillWord

                        Default = 0xBAD1

                        USX1 XGMII data for link fill word[15:0]
                        
  */
      unsigned int   usx1XgmiiLinkFillWord : 16;    /* 03.C4E9.F:0  R/W      Default = 0xBAD1 */
                     /* USX1 XGMII data for link fill word[15:0]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1LinkFillDataRegister_0_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 link Fill Data Register-1: 03.C4EA */
/*                  PCS USX1 link Fill Data Register-1: 03.C4EA */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 link Fill Data Register-1 */
  union
  {
    struct
    {
                    /*! \brief 03.C4EA.F:0 R/W USX1 XGMII Link Fill Word[1F:10]
                        AQ_PcsUsx1LinkFillDataRegister_1_HHD.u0.bits_0.usx1XgmiiLinkFillWord

                        Default = 0xBAD2

                        USX1 XGMII data for link fill word[31:16]
                        
  */
      unsigned int   usx1XgmiiLinkFillWord : 16;    /* 03.C4EA.F:0  R/W      Default = 0xBAD2 */
                     /* USX1 XGMII data for link fill word[31:16]
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1LinkFillDataRegister_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Link FIFO Control Register: 03.C4EB */
/*                  PCS USX1 Link FIFO Control Register: 03.C4EB */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Link FIFO Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4EB.F:A R/W USX1 High Threshold[5:0]
                        AQ_PcsUsx1LinkFifoControlRegister_HHD.u0.bits_0.usx1HighThreshold

                        Default = 0x14

                        Configure the high threshold for the link FIFO
                        

                 <B>Notes:</B>
                        When the link FIFO is beyond this threshold, it requests the upstream to pause traffic by inserting link fill words. When link FIFO mode is set to one, idle words can also be deleted.  */
      unsigned int   usx1HighThreshold : 6;    /* 03.C4EB.F:A  R/W      Default = 0x14 */
                     /* Configure the high threshold for the link FIFO
                          */
                    /*! \brief 03.C4EB.9:5 R/W USX1 Low Threshold[4:0]
                        AQ_PcsUsx1LinkFifoControlRegister_HHD.u0.bits_0.usx1LowThreshold

                        Default = 0x0A

                        Configure the low threshold for the link FIFO
                        

                 <B>Notes:</B>
                        When the link FIFO is below this threshold, idle words can be inserted if link FIFO mode is set to one.  */
      unsigned int   usx1LowThreshold : 5;    /* 03.C4EB.9:5  R/W      Default = 0x0A */
                     /* Configure the low threshold for the link FIFO
                          */
                    /*! \brief 03.C4EB.4 R/W USX1 Link Fifo Reset
                        AQ_PcsUsx1LinkFifoControlRegister_HHD.u0.bits_0.usx1LinkFifoReset

                        Default = 0x0

                        Set to 1 to force link FIFO to reset This FIFO is only used for AQRate
                        5G/2.5G mode.
                        
  */
      unsigned int   usx1LinkFifoReset : 1;    /* 03.C4EB.4  R/W      Default = 0x0 */
                     /* Set to 1 to force link FIFO to reset This FIFO is only used for AQRate
                        5G/2.5G mode.
                          */
                    /*! \brief 03.C4EB.3:0 R/W USX1 Link Fill Control[3:0]
                        AQ_PcsUsx1LinkFifoControlRegister_HHD.u0.bits_0.usx1LinkFillControl

                        Default = 0xF

                        USX1 XGMII control for link fill word. 
                        
  */
      unsigned int   usx1LinkFillControl : 4;    /* 03.C4EB.3:0  R/W      Default = 0xF */
                     /* USX1 XGMII control for link fill word. 
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1LinkFifoControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 TX FIFO Control Register: 03.C4EC */
/*                  PCS USX1 TX FIFO Control Register: 03.C4EC */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 TX FIFO Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 3;
                    /*! \brief 03.C4EC.C R/W USX1 TX FIFO Reset
                        AQ_PcsUsx1TxFifoControlRegister_HHD.u0.bits_0.usx1TxFifoReset

                        Default = 0x0

                        USX1 MAC Tx FIFO reset
                        
  */
      unsigned int   usx1TxFifoReset : 1;    /* 03.C4EC.C  R/W      Default = 0x0 */
                     /* USX1 MAC Tx FIFO reset
                          */
                    /*! \brief 03.C4EC.B:8 R/W USX1 TX FIFO threshold[3:0]
                        AQ_PcsUsx1TxFifoControlRegister_HHD.u0.bits_0.usx1TxFifoThreshold

                        Default = 0x1

                        USX1 MAC Tx FIFO threshold
                        This is used to establish minimum FIFO
                        depth before starting to read.
                        
  */
      unsigned int   usx1TxFifoThreshold : 4;    /* 03.C4EC.B:8  R/W      Default = 0x1 */
                     /* USX1 MAC Tx FIFO threshold
                        This is used to establish minimum FIFO
                        depth before starting to read.
                          */
                    /*! \brief 03.C4EC.7:4 R/W USX1 Tx FIFO IFG threshold[3:0]
                        AQ_PcsUsx1TxFifoControlRegister_HHD.u0.bits_0.usx1TxFifoIfgThreshold

                        Default = 0x8

                        USX1 MAC Tx FIFO IFG threshold
                        This is used to insert Idle when FIFO depth is below this threshold.
                        
  */
      unsigned int   usx1TxFifoIfgThreshold : 4;    /* 03.C4EC.7:4  R/W      Default = 0x8 */
                     /* USX1 MAC Tx FIFO IFG threshold
                        This is used to insert Idle when FIFO depth is below this threshold.
                          */
                    /*! \brief 03.C4EC.3:0 R/W USX1 Tx FIFO hi threshold[3:0]
                        AQ_PcsUsx1TxFifoControlRegister_HHD.u0.bits_0.usx1TxFifoHiThreshold

                        Default = 0xA

                        USX1 MAC Tx FIFO High threshold
                        This is used to delete Idle when FIFO depth is beyond this threshold.
                        
  */
      unsigned int   usx1TxFifoHiThreshold : 4;    /* 03.C4EC.3:0  R/W      Default = 0xA */
                     /* USX1 MAC Tx FIFO High threshold
                        This is used to delete Idle when FIFO depth is beyond this threshold.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1TxFifoControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Local Advertisement Register: 03.C4ED */
/*                  PCS USX1 Local Advertisement Register: 03.C4ED */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Local Advertisement Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4ED.F R/W USX1 Local Advertisement Status
                        AQ_PcsUsx1LocalAdvertisementRegister_HHD.u0.bits_0.usx1LocalAdvertisementStatus

                        Default = 0x0

                        USX1 Local advertisement status.
                        0 = Link down
                        1 = Link up
                        
  */
      unsigned int   usx1LocalAdvertisementStatus : 1;    /* 03.C4ED.F  R/W      Default = 0x0 */
                     /* USX1 Local advertisement status.
                        0 = Link down
                        1 = Link up
                          */
                    /*! \brief 03.C4ED.E:D R/W Reserved USX1 Local Advertisement 0 [1:0]
                        AQ_PcsUsx1LocalAdvertisementRegister_HHD.u0.bits_0.reservedUsx1LocalAdvertisement_0

                        Default = 0x0

                        Reserved for future use.
                        
  */
      unsigned int   reservedUsx1LocalAdvertisement_0 : 2;    /* 03.C4ED.E:D  R/W      Default = 0x0 */
                     /* Reserved for future use.
                          */
                    /*! \brief 03.C4ED.C R/W USX1 Local Advertisement Duplex
                        AQ_PcsUsx1LocalAdvertisementRegister_HHD.u0.bits_0.usx1LocalAdvertisementDuplex

                        Default = 0x0

                        USX1 Local advertisement duplex.
                        0 = Half duplex
                        1 = Full duplex
                        
  */
      unsigned int   usx1LocalAdvertisementDuplex : 1;    /* 03.C4ED.C  R/W      Default = 0x0 */
                     /* USX1 Local advertisement duplex.
                        0 = Half duplex
                        1 = Full duplex
                          */
                    /*! \brief 03.C4ED.B:9 R/W USX1 Local Advertisement Speed [2:0]
                        AQ_PcsUsx1LocalAdvertisementRegister_HHD.u0.bits_0.usx1LocalAdvertisementSpeed

                        Default = 0x0

                        USX1 Local advertisement speed.
                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                        
  */
      unsigned int   usx1LocalAdvertisementSpeed : 3;    /* 03.C4ED.B:9  R/W      Default = 0x0 */
                     /* USX1 Local advertisement speed.
                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                          */
                    /*! \brief 03.C4ED.8 R/W USX1 Local Advertisement EEE Capability
                        AQ_PcsUsx1LocalAdvertisementRegister_HHD.u0.bits_0.usx1LocalAdvertisementEeeCapability

                        Default = 0x0

                        USX1 Local advertisement EEE capability.
                        0 = Not supported
                        1 = Supported
                        
  */
      unsigned int   usx1LocalAdvertisementEeeCapability : 1;    /* 03.C4ED.8  R/W      Default = 0x0 */
                     /* USX1 Local advertisement EEE capability.
                        0 = Not supported
                        1 = Supported
                          */
                    /*! \brief 03.C4ED.7 R/W USX1 Local Advertisement EEE Clock Stop Capability
                        AQ_PcsUsx1LocalAdvertisementRegister_HHD.u0.bits_0.usx1LocalAdvertisementEeeClockStopCapability

                        Default = 0x0

                        USX1 Local advertisement EEE Clock Stop capability.
                        0 = Not supported
                        1 = Supported
                        
  */
      unsigned int   usx1LocalAdvertisementEeeClockStopCapability : 1;    /* 03.C4ED.7  R/W      Default = 0x0 */
                     /* USX1 Local advertisement EEE Clock Stop capability.
                        0 = Not supported
                        1 = Supported
                          */
                    /*! \brief 03.C4ED.6:1 R/W Reserved USX1 Local Advertisement 1 [5:0]
                        AQ_PcsUsx1LocalAdvertisementRegister_HHD.u0.bits_0.reservedUsx1LocalAdvertisement_1

                        Default = 0x00

                        Reserved for future use.
                        
  */
      unsigned int   reservedUsx1LocalAdvertisement_1 : 6;    /* 03.C4ED.6:1  R/W      Default = 0x00 */
                     /* Reserved for future use.
                          */
                    /*! \brief 03.C4ED.0 R/W USX1 Local Advertisement Mode
                        AQ_PcsUsx1LocalAdvertisementRegister_HHD.u0.bits_0.usx1LocalAdvertisementMode

                        Default = 0x1

                        USX1 Local advertisement mode.
                        0 = SGMII
                        1 = USXGMII
                        
  */
      unsigned int   usx1LocalAdvertisementMode : 1;    /* 03.C4ED.0  R/W      Default = 0x1 */
                     /* USX1 Local advertisement mode.
                        0 = SGMII
                        1 = USXGMII
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1LocalAdvertisementRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS SERDES MUX Swap TXRX Register: 03.C4F0 */
/*                  PCS SERDES MUX Swap TXRX Register: 03.C4F0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS SERDES MUX Swap TXRX Register */
  union
  {
    struct
    {
                    /*! \brief 03.C4F0.F:E R/W Serdes Mux Swap TX Lane 3 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_HHD.u0.bits_0.serdesMuxSwapTxLane_3

                        Default = 0x0

                        The lane swap setting for Lane 3, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 3, 1=lane 0, 2=lane 1, 3=lane 2  */
      unsigned int   serdesMuxSwapTxLane_3 : 2;    /* 03.C4F0.F:E  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 3, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.D:C R/W Serdes Mux Swap TX Lane 2 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_HHD.u0.bits_0.serdesMuxSwapTxLane_2

                        Default = 0x0

                        The lane swap setting for Lane 2, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 2, 1=lane 3, 2=lane 0, 3=lane 1  */
      unsigned int   serdesMuxSwapTxLane_2 : 2;    /* 03.C4F0.D:C  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 2, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.B:A R/W Serdes Mux Swap TX Lane 1 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_HHD.u0.bits_0.serdesMuxSwapTxLane_1

                        Default = 0x0

                        The lane swap setting for Lane 1, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 1, 1=lane 2, 2=lane 3, 3=lane 0  */
      unsigned int   serdesMuxSwapTxLane_1 : 2;    /* 03.C4F0.B:A  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 1, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.9:8 R/W Serdes Mux Swap TX Lane 0 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_HHD.u0.bits_0.serdesMuxSwapTxLane_0

                        Default = 0x0

                        The lane swap setting for Lane 0, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 0, 1=lane 1, 2=lane 2, 3=lane 3  */
      unsigned int   serdesMuxSwapTxLane_0 : 2;    /* 03.C4F0.9:8  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 0, in the Tx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.7:6 R/W Serdes Mux Swap RX Lane 3 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_HHD.u0.bits_0.serdesMuxSwapRxLane_3

                        Default = 0x0

                        The lane swap setting for Lane 3, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 3, 1=lane 0, 2=lane 1, 3=lane 2  */
      unsigned int   serdesMuxSwapRxLane_3 : 2;    /* 03.C4F0.7:6  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 3, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.5:4 R/W Serdes Mux Swap RX Lane 2 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_HHD.u0.bits_0.serdesMuxSwapRxLane_2

                        Default = 0x0

                        The lane swap setting for Lane 2, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 2, 1=lane 3, 2=lane 0, 3=lane 1  */
      unsigned int   serdesMuxSwapRxLane_2 : 2;    /* 03.C4F0.5:4  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 2, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.3:2 R/W Serdes Mux Swap RX Lane 1 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_HHD.u0.bits_0.serdesMuxSwapRxLane_1

                        Default = 0x0

                        The lane swap setting for Lane 1, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 1, 1=lane 2, 2=lane 3, 3=lane 0  */
      unsigned int   serdesMuxSwapRxLane_1 : 2;    /* 03.C4F0.3:2  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 1, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
                    /*! \brief 03.C4F0.1:0 R/W Serdes Mux Swap RX Lane 0 [1:0]
                        AQ_PcsSerdesMuxSwapTxrxRegister_HHD.u0.bits_0.serdesMuxSwapRxLane_0

                        Default = 0x0

                        The lane swap setting for Lane 0, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                        

                 <B>Notes:</B>
                        0=lane 0, 1=lane 1, 2=lane 2, 3=lane 3  */
      unsigned int   serdesMuxSwapRxLane_0 : 2;    /* 03.C4F0.1:0  R/W      Default = 0x0 */
                     /* The lane swap setting for Lane 0, in the Rx direction. It is implemented at the internal interface between the SerDes and digital logic.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsSerdesMuxSwapTxrxRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor FCS No Error Frame Counter: 03.C820 */
/*                  PCS Transmit Vendor FCS No Error Frame Counter: 03.C820 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor FCS No Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C820.F:0 SCTL 10GBASE-T Good Frame Counter LSW [F:0]
                        AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD.u0.bits_0._10gbase_tGoodFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterLSW : 16;    /* 03.C820.F:0  SCTL      Default = 0x0000 */
                     /* 10GBASE-T Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor FCS No Error Frame Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C821.9:0 SCTM 10GBASE-T Good Frame Counter MSW [19:10]
                        AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD.u1.bits_1._10gbase_tGoodFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterMSW : 10;    /* 03.C821.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitVendorFcsNoErrorFrameCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor FCS Error Frame Counter: 03.C822 */
/*                  PCS Transmit Vendor FCS Error Frame Counter: 03.C822 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor FCS Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.C822.F:0 SCTL 10GBASE-T Error Frame Counter LSW [F:0]
                        AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD.u0.bits_0._10gbase_tErrorFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterLSW : 16;    /* 03.C822.F:0  SCTL      Default = 0x0000 */
                     /* 10GBASE-T Bad Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor FCS Error Frame Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C823.9:0 SCTM 10GBASE-T Error Frame Counter MSW [19:10]
                        AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD.u1.bits_1._10gbase_tErrorFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterMSW : 10;    /* 03.C823.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Bad Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitVendorFcsErrorFrameCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI0 Vendor State: 03.C860 */
/*                  PCS Transmit XFI0 Vendor State: 03.C860 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C860.F:0 SCTL XFI0 Good Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi0VendorState_HHD.u0.bits_0.xfi0GoodFrameCounterLSW

                        Default = 0x0000

                        XFI0 Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterLSW : 16;    /* 03.C860.F:0  SCTL      Default = 0x0000 */
                     /* XFI0 Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C861.9:0 SCTM XFI0 Good Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi0VendorState_HHD.u1.bits_1.xfi0GoodFrameCounterMSW

                        Default = 0x000

                        XFI0 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterMSW : 10;    /* 03.C861.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C862.F:0 SCTL XFI0 Bad Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi0VendorState_HHD.u2.bits_2.xfi0BadFrameCounterLSW

                        Default = 0x0000

                        XFI0 Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterLSW : 16;    /* 03.C862.F:0  SCTL      Default = 0x0000 */
                     /* XFI0 Bad Frame Counter LSW
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C863.9:0 SCTM XFI0 Bad Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi0VendorState_HHD.u3.bits_3.xfi0BadFrameCounterMSW

                        Default = 0x000

                        XFI0 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterMSW : 10;    /* 03.C863.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Bad Frame Counter MSW
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitXfi0VendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XFI1 Vendor State: 03.C870 */
/*                  PCS Transmit XFI1 Vendor State: 03.C870 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C870.F:0 SCTL XFI1 Good Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi1VendorState_HHD.u0.bits_0.xfi1GoodFrameCounterLSW

                        Default = 0x0000

                        XFI1 Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterLSW : 16;    /* 03.C870.F:0  SCTL      Default = 0x0000 */
                     /* XFI1 Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C871.9:0 SCTM XFI1 Good Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi1VendorState_HHD.u1.bits_1.xfi1GoodFrameCounterMSW

                        Default = 0x000

                        XFI1 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterMSW : 10;    /* 03.C871.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C872.F:0 SCTL XFI1 Bad Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi1VendorState_HHD.u2.bits_2.xfi1BadFrameCounterLSW

                        Default = 0x0000

                        XFI1 Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterLSW : 16;    /* 03.C872.F:0  SCTL      Default = 0x0000 */
                     /* XFI1 Bad Frame Counter LSW
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.C873.9:0 SCTM XFI1 Bad Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi1VendorState_HHD.u3.bits_3.xfi1BadFrameCounterMSW

                        Default = 0x000

                        XFI1 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterMSW : 10;    /* 03.C873.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Bad Frame Counter MSW
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitXfi1VendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit XGS Vendor State: 03.C880 */
/*                  PCS Transmit XGS Vendor State: 03.C880 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C880.7:0 SCT XGS Collision Events Counter 0 [7:0]
                        AQ_PcsTransmitXgsVendorState_HHD.u0.bits_0.xgsCollisionEventsCounter_0

                        Default = 0x00

                        XGS collision events: Byte location from 1 to 64 bytes counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 1 to 64 counter  */
      unsigned int   xgsCollisionEventsCounter_0 : 8;    /* 03.C880.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 1 to 64 bytes counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C881.7:0 SCT XGS Collision Events Counter 1 [7:0]
                        AQ_PcsTransmitXgsVendorState_HHD.u1.bits_1.xgsCollisionEventsCounter_1

                        Default = 0x00

                        XGS collision events: Byte location from 65 to 96 bytes counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 65 to 96 counter  */
      unsigned int   xgsCollisionEventsCounter_1 : 8;    /* 03.C881.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 65 to 96 bytes counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C882.7:0 SCT XGS Collision Events Counter 2 [7:0]
                        AQ_PcsTransmitXgsVendorState_HHD.u2.bits_2.xgsCollisionEventsCounter_2

                        Default = 0x00

                        XGS collision events: Byte location from 97 to 128 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 97 to 128 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_2 : 8;    /* 03.C882.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 97 to 128 counter
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C883.7:0 SCT XGS Collision Events Counter 3 [7:0]
                        AQ_PcsTransmitXgsVendorState_HHD.u3.bits_3.xgsCollisionEventsCounter_3

                        Default = 0x00

                        XGS collision events: Byte location from 129 to 192 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 129 to 192 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_3 : 8;    /* 03.C883.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 129 to 192 counter
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C884.7:0 SCT XGS Collision Events Counter 4 [7:0]
                        AQ_PcsTransmitXgsVendorState_HHD.u4.bits_4.xgsCollisionEventsCounter_4

                        Default = 0x00

                        XGS collision events: Byte location from 193 to 320 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 193 to 320 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_4 : 8;    /* 03.C884.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 193 to 320 counter
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_PcsTransmitXgsVendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Transmit Status: 03.C8C0 */
/*                  PCS USX0 Transmit Status: 03.C8C0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Transmit Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.C8C0.B:8 LH USX0 Tx Rsvd Status[3:0]
                        AQ_PcsUsx0TransmitStatus_HHD.u0.bits_0.usx0TxRsvdStatus

                        

                        USX0 Tx Reserved Status
                        
  */
      unsigned int   usx0TxRsvdStatus : 4;    /* 03.C8C0.B:8  LH       */
                     /* USX0 Tx Reserved Status
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.C8C0.5 LH USX0 Tx Idle Insertion
                        AQ_PcsUsx0TransmitStatus_HHD.u0.bits_0.usx0TxIdleInsertion

                        

                        USX0 Tx Idle Insertion
                        

                 <B>Notes:</B>
                        Tx Link Idle insertion  */
      unsigned int   usx0TxIdleInsertion : 1;    /* 03.C8C0.5  LH       */
                     /* USX0 Tx Idle Insertion
                          */
                    /*! \brief 03.C8C0.4 LH USX0 Tx Idle Deletion
                        AQ_PcsUsx0TransmitStatus_HHD.u0.bits_0.usx0TxIdleDeletion

                        

                        USX0 Tx Idle Deletion
                        

                 <B>Notes:</B>
                        Rx Link Idle deletion  */
      unsigned int   usx0TxIdleDeletion : 1;    /* 03.C8C0.4  LH       */
                     /* USX0 Tx Idle Deletion
                          */
                    /*! \brief 03.C8C0.3:0 LH USX0 Tx GMII to XGMII convertion status[3:0]
                        AQ_PcsUsx0TransmitStatus_HHD.u0.bits_0.usx0TxGmiiToXgmiiConvertionStatus

                        

                        USX0 GMII/MII to XGMII Conversion Status
                        

                 <B>Notes:</B>
                        Bit 0: Detect FIFO empty during sending
                        packet
                        Bit 1: Inject Local_Fault to MAC
                        Bits 2-3: Reserved  */
      unsigned int   usx0TxGmiiToXgmiiConvertionStatus : 4;    /* 03.C8C0.3:0  LH       */
                     /* USX0 GMII/MII to XGMII Conversion Status
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0TransmitStatus_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Transmit Status: 03.C8D0 */
/*                  PCS USX1 Transmit Status: 03.C8D0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Transmit Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.C8D0.B:8 LH USX1 Tx Rsvd Status[3:0]
                        AQ_PcsUsx1TransmitStatus_HHD.u0.bits_0.usx1TxRsvdStatus

                        

                        USX1 Tx Reserved Status
                        
  */
      unsigned int   usx1TxRsvdStatus : 4;    /* 03.C8D0.B:8  LH       */
                     /* USX1 Tx Reserved Status
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.C8D0.5 LH USX1 Tx Idle Insertion
                        AQ_PcsUsx1TransmitStatus_HHD.u0.bits_0.usx1TxIdleInsertion

                        

                        USX1 Tx Idle Insertion
                        
  */
      unsigned int   usx1TxIdleInsertion : 1;    /* 03.C8D0.5  LH       */
                     /* USX1 Tx Idle Insertion
                          */
                    /*! \brief 03.C8D0.4 LH USX1 Tx Idle Deletion
                        AQ_PcsUsx1TransmitStatus_HHD.u0.bits_0.usx1TxIdleDeletion

                        

                        USX1 Tx Idle Deletion
                        
  */
      unsigned int   usx1TxIdleDeletion : 1;    /* 03.C8D0.4  LH       */
                     /* USX1 Tx Idle Deletion
                          */
                    /*! \brief 03.C8D0.3:0 LH USX1 TX GMII to XGMII convertion status[3:0]
                        AQ_PcsUsx1TransmitStatus_HHD.u0.bits_0.usx1TxGmiiToXgmiiConvertionStatus

                        

                        USX1 GMII/MII to XGMII Conversion Status
                        

                 <B>Notes:</B>
                        Bit 0: Detect FIFO empty during sending
                        packet
                        Bit 1: Inject Local_Fault to MAC
                        Bits 2-3: Reserved  */
      unsigned int   usx1TxGmiiToXgmiiConvertionStatus : 4;    /* 03.C8D0.3:0  LH       */
                     /* USX1 GMII/MII to XGMII Conversion Status
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1TransmitStatus_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor System Interface State: 03.C8F0 */
/*                  PCS Transmit Vendor System Interface State: 03.C8F0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor System Interface State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.C8F0.0 RO System Interface Transmit Fault
                        AQ_PcsTransmitVendorSystemInterfaceState_HHD.u0.bits_0.systemInterfaceTransmitFault

                        

                        1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                        

                 <B>Notes:</B>
                        See  See PHY XS Standard Status 1 - Address 4.1   */
      unsigned int   systemInterfaceTransmitFault : 1;    /* 03.C8F0.0  RO       */
                     /* 1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsTransmitVendorSystemInterfaceState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS PTP Vendor State: 03.C900 */
/*                  PCS PTP Vendor State: 03.C900 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C900.F:0 RO PTP Digital Clock Seconds Count Bits 15:0 [F:0]
                        AQ_PcsPtpVendorState_HHD.u0.bits_0.ptpDigitalClockSecondsCountBits_15_0

                        

                        PTP digital clock seconds count bits 15:0
                        

                 <B>Notes:</B>
                        Digital clock seconds counter current value   */
      unsigned int   ptpDigitalClockSecondsCountBits_15_0 : 16;    /* 03.C900.F:0  RO       */
                     /* PTP digital clock seconds count bits 15:0
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C901.F:0 RO PTP Digital Clock Seconds Count Bits 31:16 [1F:10]
                        AQ_PcsPtpVendorState_HHD.u1.bits_1.ptpDigitalClockSecondsCountBits_31_16

                        

                        PTP digital clock seconds count bits 31:16
                        

                 <B>Notes:</B>
                        Digital clock seconds counter current value   */
      unsigned int   ptpDigitalClockSecondsCountBits_31_16 : 16;    /* 03.C901.F:0  RO       */
                     /* PTP digital clock seconds count bits 31:16
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C902.F:0 RO PTP Digital Clock Seconds Count Bits 47:32 [2F:20]
                        AQ_PcsPtpVendorState_HHD.u2.bits_2.ptpDigitalClockSecondsCountBits_47_32

                        

                        PTP digital clock seconds count bits 47:32

                 <B>Notes:</B>
                        Digital clock seconds counter current value   */
      unsigned int   ptpDigitalClockSecondsCountBits_47_32 : 16;    /* 03.C902.F:0  RO       */
                     /* PTP digital clock seconds count bits 47:32  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C903.F:0 RO PTP Digital Clock Nanoseconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u3.bits_3.ptpDigitalClockNanosecondsCountLSW

                        

                        PTP digital clock nanoseconds count bits 15:0
                        

                 <B>Notes:</B>
                        Digital clock nano-seconds counter current value
                          */
      unsigned int   ptpDigitalClockNanosecondsCountLSW : 16;    /* 03.C903.F:0  RO       */
                     /* PTP digital clock nanoseconds count bits 15:0
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C904.F:0 RO PTP Digital Clock Nanoseconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u4.bits_4.ptpDigitalClockNanosecondsCountMSW

                        

                        PTP digital clock nanoseconds count bits 31:16
                        

                 <B>Notes:</B>
                        Digital clock nano-seconds counter current value
                          */
      unsigned int   ptpDigitalClockNanosecondsCountMSW : 16;    /* 03.C904.F:0  RO       */
                     /* PTP digital clock nanoseconds count bits 31:16
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C905.F:0 RO PTP Digital Clock Fractional Nanoseconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u5.bits_5.ptpDigitalClockFractionalNanosecondsCountLSW

                        

                        PTP digital clock fractional nanoseconds count bits 15:0
                        

                 <B>Notes:</B>
                        Digital clock fractional nano-seconds counter current value
                          */
      unsigned int   ptpDigitalClockFractionalNanosecondsCountLSW : 16;    /* 03.C905.F:0  RO       */
                     /* PTP digital clock fractional nanoseconds count bits 15:0
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C906.F:0 RO PTP Digital Clock Fractional Nanoseconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u6.bits_6.ptpDigitalClockFractionalNanosecondsCountMSW

                        

                        PTP digital clock fractional nanoseconds count bits 31:16
                        

                 <B>Notes:</B>
                        Digital clock fractional nano-seconds counter current value
                          */
      unsigned int   ptpDigitalClockFractionalNanosecondsCountMSW : 16;    /* 03.C906.F:0  RO       */
                     /* PTP digital clock fractional nanoseconds count bits 31:16
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C907.F:0 RO PTP Digital Clock Fractional Seconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u7.bits_7.ptpDigitalClockFractionalSecondsCountLSW

                        

                        PTP digital clock fractional seconds count bits 15:0
                        

                 <B>Notes:</B>
                        Digital clock fractional seconds counter current value
                          */
      unsigned int   ptpDigitalClockFractionalSecondsCountLSW : 16;    /* 03.C907.F:0  RO       */
                     /* PTP digital clock fractional seconds count bits 15:0
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C908.F:0 RO PTP Digital Clock Fractional Seconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u8.bits_8.ptpDigitalClockFractionalSecondsCountMSW

                        

                        PTP digital clock fractional seconds count bits 31:16
                        

                 <B>Notes:</B>
                        Digital clock fractional seconds counter current value
                          */
      unsigned int   ptpDigitalClockFractionalSecondsCountMSW : 16;    /* 03.C908.F:0  RO       */
                     /* PTP digital clock fractional seconds count bits 31:16
                          */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C909.F:0 RO PTP External Clock Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u9.bits_9.ptpExternalClockCountLSW

                        

                        PTP external clock count bits 15:0
                        

                 <B>Notes:</B>
                        External clock counter value  */
      unsigned int   ptpExternalClockCountLSW : 16;    /* 03.C909.F:0  RO       */
                     /* PTP external clock count bits 15:0
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of PCS PTP Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.C90A.D:0 RO PTP External Clock Count MSW [1D:10]
                        AQ_PcsPtpVendorState_HHD.u10.bits_10.ptpExternalClockCountMSW

                        

                        PTP external clock count bits 29:16
                        

                 <B>Notes:</B>
                        External clock counter value  */
      unsigned int   ptpExternalClockCountMSW : 14;    /* 03.C90A.D:0  RO       */
                     /* PTP external clock count bits 29:16
                          */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C90B.F:0 RO PTP External Clock Seconds Count Bits 15:0 [F:0]
                        AQ_PcsPtpVendorState_HHD.u11.bits_11.ptpExternalClockSecondsCountBits_15_0

                        

                        PTP external clock seconds count bits 15:0
                        

                 <B>Notes:</B>
                        External clock seconds counter value  */
      unsigned int   ptpExternalClockSecondsCountBits_15_0 : 16;    /* 03.C90B.F:0  RO       */
                     /* PTP external clock seconds count bits 15:0
                          */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C90C.F:0 RO PTP External Clock Seconds Count Bits 31:16 [1F:10]
                        AQ_PcsPtpVendorState_HHD.u12.bits_12.ptpExternalClockSecondsCountBits_31_16

                        

                        PTP external clock seconds count bits 31:16
                        

                 <B>Notes:</B>
                        External clock seconds counter value  */
      unsigned int   ptpExternalClockSecondsCountBits_31_16 : 16;    /* 03.C90C.F:0  RO       */
                     /* PTP external clock seconds count bits 31:16
                          */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C90D.F:0 RO PTP External Clock Seconds Count Bits 47:32 [2F:20]
                        AQ_PcsPtpVendorState_HHD.u13.bits_13.ptpExternalClockSecondsCountBits_47_32

                        

                        PTP external clock seconds count bits 47:32
                        

                 <B>Notes:</B>
                        External clock seconds counter value  */
      unsigned int   ptpExternalClockSecondsCountBits_47_32 : 16;    /* 03.C90D.F:0  RO       */
                     /* PTP external clock seconds count bits 47:32
                          */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C90E.F:0 RO PTP External Clock Nanoseconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u14.bits_14.ptpExternalClockNanosecondsCountLSW

                        

                        PTP external clock nanoseconds count bits 15:0
                        

                 <B>Notes:</B>
                        External clock nanoseconds counter value  */
      unsigned int   ptpExternalClockNanosecondsCountLSW : 16;    /* 03.C90E.F:0  RO       */
                     /* PTP external clock nanoseconds count bits 15:0
                          */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C90F.F:0 RO PTP External Clock Nanoseconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u15.bits_15.ptpExternalClockNanosecondsCountMSW

                        

                        PTP external clock nanoseconds count bits 31:16
                        

                 <B>Notes:</B>
                        External clock nanoseconds counter value  */
      unsigned int   ptpExternalClockNanosecondsCountMSW : 16;    /* 03.C90F.F:0  RO       */
                     /* PTP external clock nanoseconds count bits 31:16
                          */
    } bits_15;
    uint16_t word_15;
  } u15;
  /*! \brief Union for bit and word level access of word 16 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C910.F:0 RO PTP External Clock Fractional Nanoseconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u16.bits_16.ptpExternalClockFractionalNanosecondsCountLSW

                        

                        PTP external clock fractional nanoseconds count bits 15:0
                        

                 <B>Notes:</B>
                        External clock fractional nanoseconds counter value  */
      unsigned int   ptpExternalClockFractionalNanosecondsCountLSW : 16;    /* 03.C910.F:0  RO       */
                     /* PTP external clock fractional nanoseconds count bits 15:0
                          */
    } bits_16;
    uint16_t word_16;
  } u16;
  /*! \brief Union for bit and word level access of word 17 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C911.F:0 RO PTP External Clock Fractional Nanoseconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u17.bits_17.ptpExternalClockFractionalNanosecondsCountMSW

                        

                        PTP external clock fractional nanoseconds count bits 31:16
                        

                 <B>Notes:</B>
                        External clock fractional nanoseconds counter value  */
      unsigned int   ptpExternalClockFractionalNanosecondsCountMSW : 16;    /* 03.C911.F:0  RO       */
                     /* PTP external clock fractional nanoseconds count bits 31:16
                          */
    } bits_17;
    uint16_t word_17;
  } u17;
  /*! \brief Union for bit and word level access of word 18 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C912.F:0 RO PTP External Clock Fractional Seconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u18.bits_18.ptpExternalClockFractionalSecondsCountLSW

                        

                        PTP external clock fractional seconds count bits 15:0
                        

                 <B>Notes:</B>
                        External clock fractional seconds counter value  */
      unsigned int   ptpExternalClockFractionalSecondsCountLSW : 16;    /* 03.C912.F:0  RO       */
                     /* PTP external clock fractional seconds count bits 15:0
                          */
    } bits_18;
    uint16_t word_18;
  } u18;
  /*! \brief Union for bit and word level access of word 19 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C913.F:0 RO PTP External Clock Fractional Seconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u19.bits_19.ptpExternalClockFractionalSecondsCountMSW

                        

                        PTP external clock fractional seconds count bits 31:16
                        

                 <B>Notes:</B>
                        External clock fractional seconds counter value  */
      unsigned int   ptpExternalClockFractionalSecondsCountMSW : 16;    /* 03.C913.F:0  RO       */
                     /* PTP external clock fractional seconds count bits 31:16
                          */
    } bits_19;
    uint16_t word_19;
  } u19;
  /*! \brief Union for bit and word level access of word 20 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C914.F:0 RO PTP External GPIO Clock Seconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u20.bits_20.ptpExternalGpioClockSecondsCountLSW

                        

                        PTP external GPIO clock seconds count bits 15:0
                        

                 <B>Notes:</B>
                        External GPIO seconds counter value  */
      unsigned int   ptpExternalGpioClockSecondsCountLSW : 16;    /* 03.C914.F:0  RO       */
                     /* PTP external GPIO clock seconds count bits 15:0
                          */
    } bits_20;
    uint16_t word_20;
  } u20;
  /*! \brief Union for bit and word level access of word 21 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C915.F:0 RO PTP External GPIO Clock Seconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u21.bits_21.ptpExternalGpioClockSecondsCountMSW

                        

                        PTP external GPIO clock seconds count bits 31:16
                        

                 <B>Notes:</B>
                        External GPIO seconds counter value  */
      unsigned int   ptpExternalGpioClockSecondsCountMSW : 16;    /* 03.C915.F:0  RO       */
                     /* PTP external GPIO clock seconds count bits 31:16
                          */
    } bits_21;
    uint16_t word_21;
  } u21;
  /*! \brief Union for bit and word level access of word 22 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C916.F:0 RO PTP External GPIO Clock Nanoseconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u22.bits_22.ptpExternalGpioClockNanosecondsCountLSW

                        

                        PTP external GPIO clock nanosecods count bits 15:0
                        

                 <B>Notes:</B>
                        External GPIO nanosecods counter value  */
      unsigned int   ptpExternalGpioClockNanosecondsCountLSW : 16;    /* 03.C916.F:0  RO       */
                     /* PTP external GPIO clock nanosecods count bits 15:0
                          */
    } bits_22;
    uint16_t word_22;
  } u22;
  /*! \brief Union for bit and word level access of word 23 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C917.F:0 RO PTP External GPIO Clock Nanoseconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u23.bits_23.ptpExternalGpioClockNanosecondsCountMSW

                        

                        PTP external GPIO clock nanosecods count bits 31:16
                        

                 <B>Notes:</B>
                        External GPIO nanosecods counter value  */
      unsigned int   ptpExternalGpioClockNanosecondsCountMSW : 16;    /* 03.C917.F:0  RO       */
                     /* PTP external GPIO clock nanosecods count bits 31:16
                          */
    } bits_23;
    uint16_t word_23;
  } u23;
  /*! \brief Union for bit and word level access of word 24 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C918.F:0 RO PTP External GPIO Clock Fractional Nanoseconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u24.bits_24.ptpExternalGpioClockFractionalNanosecondsCountLSW

                        

                        PTP external GPIO clock fractional nanosecods count bits 15:0
                        

                 <B>Notes:</B>
                        External GPIO fractional nanosecods counter value  */
      unsigned int   ptpExternalGpioClockFractionalNanosecondsCountLSW : 16;    /* 03.C918.F:0  RO       */
                     /* PTP external GPIO clock fractional nanosecods count bits 15:0
                          */
    } bits_24;
    uint16_t word_24;
  } u24;
  /*! \brief Union for bit and word level access of word 25 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C919.F:0 RO PTP External GPIO Clock Fractional Nanoseconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u25.bits_25.ptpExternalGpioClockFractionalNanosecondsCountMSW

                        

                        PTP external GPIO clock fractional nanosecods count bits 31:16
                        

                 <B>Notes:</B>
                        External GPIO fractional nanosecods counter value  */
      unsigned int   ptpExternalGpioClockFractionalNanosecondsCountMSW : 16;    /* 03.C919.F:0  RO       */
                     /* PTP external GPIO clock fractional nanosecods count bits 31:16
                          */
    } bits_25;
    uint16_t word_25;
  } u25;
  /*! \brief Union for bit and word level access of word 26 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C91A.F:0 RO PTP External GPIO Clock Fractional Seconds Count LSW [F:0]
                        AQ_PcsPtpVendorState_HHD.u26.bits_26.ptpExternalGpioClockFractionalSecondsCountLSW

                        

                        PTP external GPIO clock fractional seconds count bits 15:0
                        

                 <B>Notes:</B>
                        External GPIO fractional seconds counter value  */
      unsigned int   ptpExternalGpioClockFractionalSecondsCountLSW : 16;    /* 03.C91A.F:0  RO       */
                     /* PTP external GPIO clock fractional seconds count bits 15:0
                          */
    } bits_26;
    uint16_t word_26;
  } u26;
  /*! \brief Union for bit and word level access of word 27 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C91B.F:0 RO PTP External GPIO Clock Fractional Seconds Count MSW [1F:10]
                        AQ_PcsPtpVendorState_HHD.u27.bits_27.ptpExternalGpioClockFractionalSecondsCountMSW

                        

                        PTP external GPIO clock fractional seconds count bits 31:16
                        

                 <B>Notes:</B>
                        External GPIO fractional seconds counter value  */
      unsigned int   ptpExternalGpioClockFractionalSecondsCountMSW : 16;    /* 03.C91B.F:0  RO       */
                     /* PTP external GPIO clock fractional seconds count bits 31:16
                          */
    } bits_27;
    uint16_t word_27;
  } u27;
  /*! \brief Union for bit and word level access of word 28 of PCS PTP Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.C91C.0 BLH PTP External GPIO Clock Update Done
                        AQ_PcsPtpVendorState_HHD.u28.bits_28.ptpExternalGpioClockUpdateDone

                        

                        PTP external GPIO clock update done
                        

                 <B>Notes:</B>
                        External GPIO fractional seconds counter value  */
      unsigned int   ptpExternalGpioClockUpdateDone : 1;    /* 03.C91C.0  BLH       */
                     /* PTP external GPIO clock update done
                          */
    } bits_28;
    uint16_t word_28;
  } u28;
  /*! \brief Union for bit and word level access of word 29 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C91D.F:0 RO PTP USX0 Rx Timestamp Bits 15:0 [F:0]
                        AQ_PcsPtpVendorState_HHD.u29.bits_29.ptpUsx0RxTimestampBits_15_0

                        

                        PTP USX0 Rx Timestamp bits 15:0
                        

                 <B>Notes:</B>
                        USX0 Rx timestamp current value   */
      unsigned int   ptpUsx0RxTimestampBits_15_0 : 16;    /* 03.C91D.F:0  RO       */
                     /* PTP USX0 Rx Timestamp bits 15:0
                          */
    } bits_29;
    uint16_t word_29;
  } u29;
  /*! \brief Union for bit and word level access of word 30 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C91E.F:0 RO PTP USX0 Rx Timestamp Bits 31:16 [1F:10]
                        AQ_PcsPtpVendorState_HHD.u30.bits_30.ptpUsx0RxTimestampBits_31_16

                        

                        PTP USX0 Rx Timestamp bits 31:16
                        

                 <B>Notes:</B>
                        USX0 Rx timestamp current value   */
      unsigned int   ptpUsx0RxTimestampBits_31_16 : 16;    /* 03.C91E.F:0  RO       */
                     /* PTP USX0 Rx Timestamp bits 31:16
                          */
    } bits_30;
    uint16_t word_30;
  } u30;
  /*! \brief Union for bit and word level access of word 31 of PCS PTP Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 03.C91F.2:0 RO PTP USX0 Rx Timestamp Bits 34:32 [22:20]
                        AQ_PcsPtpVendorState_HHD.u31.bits_31.ptpUsx0RxTimestampBits_34_32

                        

                        PTP USX0 Rx Timestamp bits 34:32
                        

                 <B>Notes:</B>
                        USX0 Rx timestamp current value   */
      unsigned int   ptpUsx0RxTimestampBits_34_32 : 3;    /* 03.C91F.2:0  RO       */
                     /* PTP USX0 Rx Timestamp bits 34:32
                          */
    } bits_31;
    uint16_t word_31;
  } u31;
  /*! \brief Union for bit and word level access of word 32 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C920.F:0 RO PTP USX1 Rx Timestamp Bits 15:0 [F:0]
                        AQ_PcsPtpVendorState_HHD.u32.bits_32.ptpUsx1RxTimestampBits_15_0

                        

                        PTP USX1 Rx Timestamp bits 15:0
                        

                 <B>Notes:</B>
                        USX1 Rx timestamp current value   */
      unsigned int   ptpUsx1RxTimestampBits_15_0 : 16;    /* 03.C920.F:0  RO       */
                     /* PTP USX1 Rx Timestamp bits 15:0
                          */
    } bits_32;
    uint16_t word_32;
  } u32;
  /*! \brief Union for bit and word level access of word 33 of PCS PTP Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C921.F:0 RO PTP USX1 Rx Timestamp Bits 31:16 [1F:10]
                        AQ_PcsPtpVendorState_HHD.u33.bits_33.ptpUsx1RxTimestampBits_31_16

                        

                        PTP USX1 Rx Timestamp bits 31:16
                        

                 <B>Notes:</B>
                        USX1 Rx timestamp current value   */
      unsigned int   ptpUsx1RxTimestampBits_31_16 : 16;    /* 03.C921.F:0  RO       */
                     /* PTP USX1 Rx Timestamp bits 31:16
                          */
    } bits_33;
    uint16_t word_33;
  } u33;
  /*! \brief Union for bit and word level access of word 34 of PCS PTP Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 03.C922.2:0 RO PTP USX1 Rx Timestamp Bits 34:32 [22:20]
                        AQ_PcsPtpVendorState_HHD.u34.bits_34.ptpUsx1RxTimestampBits_34_32

                        

                        PTP USX1 Rx Timestamp bits 34:32
                        

                 <B>Notes:</B>
                        USX1 Rx timestamp current value   */
      unsigned int   ptpUsx1RxTimestampBits_34_32 : 3;    /* 03.C922.2:0  RO       */
                     /* PTP USX1 Rx Timestamp bits 34:32
                          */
    } bits_34;
    uint16_t word_34;
  } u34;
} AQ_PcsPtpVendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS PTP Egress Vendor State: 03.C930 */
/*                  PCS PTP Egress Vendor State: 03.C930 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS PTP Egress Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 03.C930.2:0 RO PTP Egress Packet Count [2:0]
                        AQ_PcsPtpEgressVendorState_HHD.u0.bits_0.ptpEgressPacketCount

                        

                        PTP Egress packet count
                        

                 <B>Notes:</B>
                        PTP packet count (0 to 4)  */
      unsigned int   ptpEgressPacketCount : 3;    /* 03.C930.2:0  RO       */
                     /* PTP Egress packet count
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS PTP Egress Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C931.F:0 RO PTP Egress Packet Data LSW [F:0]
                        AQ_PcsPtpEgressVendorState_HHD.u1.bits_1.ptpEgressPacketDataLSW

                        

                        PTP Egress packet count
                        

                 <B>Notes:</B>
                        PTP packet data  */
      unsigned int   ptpEgressPacketDataLSW : 16;    /* 03.C931.F:0  RO       */
                     /* PTP Egress packet count
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS PTP Egress Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C932.F:0 RO PTP Egress Packet Data MSW [1F:10]
                        AQ_PcsPtpEgressVendorState_HHD.u2.bits_2.ptpEgressPacketDataMSW

                        

                        PTP Egress packet count
                        

                 <B>Notes:</B>
                        PTP packet data  */
      unsigned int   ptpEgressPacketDataMSW : 16;    /* 03.C932.F:0  RO       */
                     /* PTP Egress packet count
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS PTP Egress Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 03.C933.2 RO PTP Egress Packet Truncated
                        AQ_PcsPtpEgressVendorState_HHD.u3.bits_3.ptpEgressPacketTruncated

                        

                        PTP Egress packet EOP
                        

                 <B>Notes:</B>
                        Asserted when PTP packet has been truncated because it is longer than 128 byte.  */
      unsigned int   ptpEgressPacketTruncated : 1;    /* 03.C933.2  RO       */
                     /* PTP Egress packet EOP
                          */
                    /*! \brief 03.C933.1 RO PTP Egress Packet EOP
                        AQ_PcsPtpEgressVendorState_HHD.u3.bits_3.ptpEgressPacketEop

                        

                        PTP Egress packet EOP
                        

                 <B>Notes:</B>
                        Asserted when the PTP packet data returns the last word of packet  */
      unsigned int   ptpEgressPacketEop : 1;    /* 03.C933.1  RO       */
                     /* PTP Egress packet EOP
                          */
                    /*! \brief 03.C933.0 RO PTP Egress Packet SOP
                        AQ_PcsPtpEgressVendorState_HHD.u3.bits_3.ptpEgressPacketSop

                        

                        PTP Egress packet SOP
                        

                 <B>Notes:</B>
                        Asserted when the PTP packet data returns the first word of packet  */
      unsigned int   ptpEgressPacketSop : 1;    /* 03.C933.0  RO       */
                     /* PTP Egress packet SOP
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS PTP Egress Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 03.C934.2:0 RO PTP Egress Packet Time Stamp Count [2:0]
                        AQ_PcsPtpEgressVendorState_HHD.u4.bits_4.ptpEgressPacketTimeStampCount

                        

                        PTP Egress packet count
                        

                 <B>Notes:</B>
                        PTP packet timestamp count (0 to 4)  */
      unsigned int   ptpEgressPacketTimeStampCount : 3;    /* 03.C934.2:0  RO       */
                     /* PTP Egress packet count
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS PTP Egress Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C935.F:0 RO PTP Egress Packet Time Stamp [F:0]
                        AQ_PcsPtpEgressVendorState_HHD.u5.bits_5.ptpEgressPacketTimeStamp

                        

                        PTP Egress packet count
                        

                 <B>Notes:</B>
                        PTP packet timestamp
                        Report arrival timestamp in 8 consecutive reads for every packet (MSB first):
                        48-bit sec, 32-bit nano-sec, 16-bit fractional nano-sec, 32-bit fractional sec  */
      unsigned int   ptpEgressPacketTimeStamp : 16;    /* 03.C935.F:0  RO       */
                     /* PTP Egress packet count
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS PTP Egress Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.C936.7 RO PTP Egress Gap FIFO Error
                        AQ_PcsPtpEgressVendorState_HHD.u6.bits_6.ptpEgressGapFifoError

                        

                        PTP Egress Gap FIFO error
                        

                 <B>Notes:</B>
                        Read Egress Gap FIFO error for debug  */
      unsigned int   ptpEgressGapFifoError : 1;    /* 03.C936.7  RO       */
                     /* PTP Egress Gap FIFO error
                          */
                    /*! \brief 03.C936.6:0 RO PTP Egress Rx Packet Information [6:0]
                        AQ_PcsPtpEgressVendorState_HHD.u6.bits_6.ptpEgressRxPacketInformation

                        

                        PTP Egress packet count
                        

                 <B>Notes:</B>
                        Received PTP packet information
                        Report diagnostic information about the type of PTP packet being received.
                        Bits[1:0]: 0=L2, 1=IPv4, 2=IPv6, 3=reserved
                        Bits[3:2]: 0=1588v1, 1=1588v2, 2=NTP/SNTP, 3=reserved
                        For IEEE 1588:
                        Bits[6:4]: 0=Sync, 1=Delay_Req, 2=General, 3=PDelay_Req, 4=Pdelay_Resp, 5=User-defined, 6 to 7=reserved
                        For NTP/SNTP:
                        Bits [6:4]: 0=Non-control, 1=Control & Private, 
                        2 to 7=reserved  */
      unsigned int   ptpEgressRxPacketInformation : 7;    /* 03.C936.6:0  RO       */
                     /* PTP Egress packet count
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsPtpEgressVendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor Alarms: 03.CC00 */
/*                  PCS Transmit Vendor Alarms: 03.CC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.CC00.F:1 LH Reserved PCS Transmit Vendor Alarms 1 [F:1]
                        AQ_PcsTransmitVendorAlarms_HHD.u0.bits_0.reservedPcsTransmitVendorAlarms_1

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_1 : 15;    /* 03.CC00.F:1  LH       */
                     /* Reserved for future use  */
                    /*! \brief 03.CC00.0 LH XAUI Transmit Invalid 64B Block Detected
                        AQ_PcsTransmitVendorAlarms_HHD.u0.bits_0.xauiTransmitInvalid_64bBlockDetected

                        

                        1 = Bad 64B block detected
                        
  */
      unsigned int   xauiTransmitInvalid_64bBlockDetected : 1;    /* 03.CC00.0  LH       */
                     /* 1 = Bad 64B block detected
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.CC01.F:0 LH Reserved PCS Transmit Vendor Alarms 2 [F:0]
                        AQ_PcsTransmitVendorAlarms_HHD.u1.bits_1.reservedPcsTransmitVendorAlarms_2

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_2 : 16;    /* 03.CC01.F:0  LH       */
                     /* Reserved for future use  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.CC02.F:0 LH Reserved PCS Transmit Vendor Alarms 3 [F:0]
                        AQ_PcsTransmitVendorAlarms_HHD.u2.bits_2.reservedPcsTransmitVendorAlarms_3

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_3 : 16;    /* 03.CC02.F:0  LH       */
                     /* Reserved for future use  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.CC03.D LH XFI1 Transmit Invalid XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_HHD.u3.bits_3.xfi1TransmitInvalidXgmiiCharacterReceived

                        

                        1 = Invalid XGMII Character Received
                        
  */
      unsigned int   xfi1TransmitInvalidXgmiiCharacterReceived : 1;    /* 03.CC03.D  LH       */
                     /* 1 = Invalid XGMII Character Received
                          */
                    /*! \brief 03.CC03.C LH XFI1 Transmit Reserved XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_HHD.u3.bits_3.xfi1TransmitReservedXgmiiCharacterReceived

                        

                        1 = Reserved XGMII Character Received
                        
  */
      unsigned int   xfi1TransmitReservedXgmiiCharacterReceived : 1;    /* 03.CC03.C  LH       */
                     /* 1 = Reserved XGMII Character Received
                          */
                    /*! \brief 03.CC03.B LH XFI1 Transmit 64B Encode Error
                        AQ_PcsTransmitVendorAlarms_HHD.u3.bits_3.xfi1Transmit_64bEncodeError

                        

                        1 = 64B Encode Error
                        
  */
      unsigned int   xfi1Transmit_64bEncodeError : 1;    /* 03.CC03.B  LH       */
                     /* 1 = 64B Encode Error
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.CC03.8 LH XFI1 Transmit LOF Detected
                        AQ_PcsTransmitVendorAlarms_HHD.u3.bits_3.xfi1TransmitLofDetected

                        

                        1 = Loss of Frame detected
                        
  */
      unsigned int   xfi1TransmitLofDetected : 1;    /* 03.CC03.8  LH       */
                     /* 1 = Loss of Frame detected
                          */
      unsigned int   reserved2 : 2;
                    /*! \brief 03.CC03.5 LH XFI0 Transmit Invalid XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_HHD.u3.bits_3.xfi0TransmitInvalidXgmiiCharacterReceived

                        

                        1 = Invalid XGMII Character Received
                        
  */
      unsigned int   xfi0TransmitInvalidXgmiiCharacterReceived : 1;    /* 03.CC03.5  LH       */
                     /* 1 = Invalid XGMII Character Received
                          */
                    /*! \brief 03.CC03.4 LH XFI0 Transmit Reserved XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_HHD.u3.bits_3.xfi0TransmitReservedXgmiiCharacterReceived

                        

                        1 = Reserved XGMII Character Received
                        
  */
      unsigned int   xfi0TransmitReservedXgmiiCharacterReceived : 1;    /* 03.CC03.4  LH       */
                     /* 1 = Reserved XGMII Character Received
                          */
                    /*! \brief 03.CC03.3 LH XFI0 Transmit 64B Encode Error
                        AQ_PcsTransmitVendorAlarms_HHD.u3.bits_3.xfi0Transmit_64bEncodeError

                        

                        1 = 64B Encode Error
                        
  */
      unsigned int   xfi0Transmit_64bEncodeError : 1;    /* 03.CC03.3  LH       */
                     /* 1 = 64B Encode Error
                          */
      unsigned int   reserved3 : 2;
                    /*! \brief 03.CC03.0 LH XFI0 Transmit LOF Detected
                        AQ_PcsTransmitVendorAlarms_HHD.u3.bits_3.xfi0TransmitLofDetected

                        

                        1 = Loss of frame detected
                        
  */
      unsigned int   xfi0TransmitLofDetected : 1;    /* 03.CC03.0  LH       */
                     /* 1 = Loss of frame detected
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitVendorAlarms_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Standard Interrupt Mask: 03.D000 */
/*                  PCS Standard Interrupt Mask: 03.D000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.D000.B R/WPD Tx LPI Received Mask
                        AQ_PcsStandardInterruptMask_HHD.u0.bits_0.txLpiReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for Bit 3.1.B.  */
      unsigned int   txLpiReceivedMask : 1;    /* 03.D000.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D000.A R/WPD Rx LPI Received Mask
                        AQ_PcsStandardInterruptMask_HHD.u0.bits_0.rxLpiReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        

                 <B>Notes:</B>
                        Mask for Bit 3.1.A.  */
      unsigned int   rxLpiReceivedMask : 1;    /* 03.D000.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.D000.2 R/WPD PCS Receive Link Status Mask
                        AQ_PcsStandardInterruptMask_HHD.u0.bits_0.pcsReceiveLinkStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Mask for Bit 3.1.2. Note this bit also shows up as Bit 3.20.C, but only as a status bit.  */
      unsigned int   pcsReceiveLinkStatusMask : 1;    /* 03.D000.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.D001.B R/WPD Transmit Fault Mask
                        AQ_PcsStandardInterruptMask_HHD.u1.bits_1.transmitFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 3.8.B  */
      unsigned int   transmitFaultMask : 1;    /* 03.D001.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.D001.A R/WPD Receive Fault Mask
                        AQ_PcsStandardInterruptMask_HHD.u1.bits_1.receiveFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 3.8.A  */
      unsigned int   receiveFaultMask : 1;    /* 03.D001.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 10;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Standard Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D002.F R/WPD 10GBASE-T PCS Block Lock Latched Mask
                        AQ_PcsStandardInterruptMask_HHD.u2.bits_2._10gbase_tPcsBlockLockLatchedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        When set, this bit indicates that 10GBASE-T PCS Framer has acquired frame synchronization and is locked. This is the interrupt for bit 3.21.F  */
      unsigned int   _10gbase_tPcsBlockLockLatchedMask : 1;    /* 03.D002.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.D002.E R/WPD 10GBASE-T High BER Latched Mask
                        AQ_PcsStandardInterruptMask_HHD.u2.bits_2._10gbase_tHighBerLatchedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. This is the interrupt for bit 3.21.E  */
      unsigned int   _10gbase_tHighBerLatchedMask : 1;    /* 03.D002.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 14;
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PcsStandardInterruptMask_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor Interrupt Mask: 03.D400 */
/*                  PCS Transmit Vendor Interrupt Mask: 03.D400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D400.F:1 R/WPD Reserved PCS Transmit Vendor Alarms 1 Mask [F:1]
                        AQ_PcsTransmitVendorInterruptMask_HHD.u0.bits_0.reservedPcsTransmitVendorAlarms_1Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsTransmitVendorAlarms_1Mask : 15;    /* 03.D400.F:1  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.D400.0 R/WPD XAUI Transmit Invalid 64B Block Detected Mask
                        AQ_PcsTransmitVendorInterruptMask_HHD.u0.bits_0.xauiTransmitInvalid_64bBlockDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiTransmitInvalid_64bBlockDetectedMask : 1;    /* 03.D400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D401.F:0 R/WPD Reserved PCS Transmit Vendor Alarms 2 Mask [F:0]
                        AQ_PcsTransmitVendorInterruptMask_HHD.u1.bits_1.reservedPcsTransmitVendorAlarms_2Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsTransmitVendorAlarms_2Mask : 16;    /* 03.D401.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D402.F:0 R/WPD Reserved PCS Transmit Vendor Alarms 3 Mask [F:0]
                        AQ_PcsTransmitVendorInterruptMask_HHD.u2.bits_2.reservedPcsTransmitVendorAlarms_3Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsTransmitVendorAlarms_3Mask : 16;    /* 03.D402.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.D403.D R/WPD XFI1 Transmit Invalid XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_HHD.u3.bits_3.xfi1TransmitInvalidXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitInvalidXgmiiCharacterErrorMask : 1;    /* 03.D403.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.C R/WPD XFI1 Transmit Reserved XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_HHD.u3.bits_3.xfi1TransmitReservedXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitReservedXgmiiCharacterErrorMask : 1;    /* 03.D403.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.B R/WPD XFI1 Transmit Encode 64B Error Mask
                        AQ_PcsTransmitVendorInterruptMask_HHD.u3.bits_3.xfi1TransmitEncode_64bErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitEncode_64bErrorMask : 1;    /* 03.D403.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 5;
                    /*! \brief 03.D403.5 R/WPD XFI0 Transmit Invalid XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_HHD.u3.bits_3.xfi0TransmitInvalidXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitInvalidXgmiiCharacterErrorMask : 1;    /* 03.D403.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.4 R/WPD XFI0 Transmit Reserved XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_HHD.u3.bits_3.xfi0TransmitReservedXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitReservedXgmiiCharacterErrorMask : 1;    /* 03.D403.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.3 R/WPD XFI0 Transmit Encode 64B Error Mask
                        AQ_PcsTransmitVendorInterruptMask_HHD.u3.bits_3.xfi0TransmitEncode_64bErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitEncode_64bErrorMask : 1;    /* 03.D403.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved2 : 3;
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitVendorInterruptMask_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Transmit Vendor Debug: 03.D800 */
/*                  PCS Transmit Vendor Debug: 03.D800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Transmit Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 03.D800.F R/WPD PCS Tx Scrambler Disable
                        AQ_PcsTransmitVendorDebug_HHD.u0.bits_0.pcsTxScramblerDisable

                        Provisionable Default = 0x0

                        1 = Tx Scrambler Disabled
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        Setting this bit disables the Tx scrambler during regular data transmission (i.e. scrambler functionality during training and startup is unmodified).  */
      unsigned int   pcsTxScramblerDisable : 1;    /* 03.D800.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Tx Scrambler Disabled
                        0 = Normal Operation
                          */
                    /*! \brief 03.D800.E R/W PCS Tx Inject CRC Error
                        AQ_PcsTransmitVendorDebug_HHD.u0.bits_0.pcsTxInjectCrcError

                        Default = 0x0

                        1 = Inject CRC Error
                        

                 <B>Notes:</B>
                        Setting this bit injects a CRC error in a single frame.  */
      unsigned int   pcsTxInjectCrcError : 1;    /* 03.D800.E  R/W      Default = 0x0 */
                     /* 1 = Inject CRC Error
                          */
                    /*! \brief 03.D800.D R/W PCS Tx Inject Frame Error
                        AQ_PcsTransmitVendorDebug_HHD.u0.bits_0.pcsTxInjectFrameError

                        Default = 0x0

                        1 = Inject frame error
                        

                 <B>Notes:</B>
                        Setting this bit injects an error at the location contained in Bits C:0 in the next PCS transmission frame.  */
      unsigned int   pcsTxInjectFrameError : 1;    /* 03.D800.D  R/W      Default = 0x0 */
                     /* 1 = Inject frame error
                          */
      unsigned int   reserved0 : 13;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsTransmitVendorDebug_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Provisioning: 03.E400 */
/*                  PCS Receive Vendor Provisioning: 03.E400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.E400.0 R/WPD PCS Rx Error LDPC Frame Enable
                        AQ_PcsReceiveVendorProvisioning_HHD.u0.bits_0.pcsRxErrorLdpcFrameEnable

                        Provisionable Default = 0x1

                        1 = Enable erroring the LDPC frame payload
                        0 = Disable erroring the LDPC frame payload
                        

                 <B>Notes:</B>
                        Error the entire LDPC frame payload upon uncorrectable LDPC parity or CRC error.  */
      unsigned int   pcsRxErrorLdpcFrameEnable : 1;    /* 03.E400.0  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Enable erroring the LDPC frame payload
                        0 = Disable erroring the LDPC frame payload
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive XFI0 Provisioning: 03.E460 */
/*                  PCS Receive XFI0 Provisioning: 03.E460 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive XFI0 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.E460.1 R/W XFI0 Rx Descrambler Disable
                        AQ_PcsReceiveXfi0Provisioning_HHD.u0.bits_0.xfi0RxDescramblerDisable

                        Default = 0x0

                        1 = XFI0 Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Descrambler Disable  */
      unsigned int   xfi0RxDescramblerDisable : 1;    /* 03.E460.1  R/W      Default = 0x0 */
                     /* 1 = XFI0 Disable PCS scrambler
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI0 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 03.E461.8 R/W XFI0 Test Data Source
                        AQ_PcsReceiveXfi0Provisioning_HHD.u1.bits_1.xfi0TestDataSource

                        Default = 0x0

                        XFI0 Data pattern select
                        1 = All-zero input for pseudo-random test
                        1 = Local-fault (LF) input for pseudo-random test
                        

                 <B>Notes:</B>
                        This bit determines the source of the data for the pseudo-random test (selected by Bit 7).  */
      unsigned int   xfi0TestDataSource : 1;    /* 03.E461.8  R/W      Default = 0x0 */
                     /* XFI0 Data pattern select
                        1 = All-zero input for pseudo-random test
                        1 = Local-fault (LF) input for pseudo-random test
                          */
                    /*! \brief 03.E461.7:5 R/W XFI0 Test Mode Select [2:0]
                        AQ_PcsReceiveXfi0Provisioning_HHD.u1.bits_1.xfi0TestModeSelect

                        Default = 0x0

                        Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random

                 <B>Notes:</B>
                        Note that the source for the pseudo-random test is determined by Bit 8.  */
      unsigned int   xfi0TestModeSelect : 3;    /* 03.E461.7:5  R/W      Default = 0x0 */
                     /* Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random  */
                    /*! \brief 03.E461.4 R/W XFI0 Test Pattern Enable
                        AQ_PcsReceiveXfi0Provisioning_HHD.u1.bits_1.xfi0TestPatternEnable

                        Default = 0x0

                        1 = XFI0 Enable test pattern
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable - see the external view for an explanation  */
      unsigned int   xfi0TestPatternEnable : 1;    /* 03.E461.4  R/W      Default = 0x0 */
                     /* 1 = XFI0 Enable test pattern
                          */
                    /*! \brief 03.E461.3 R/W XFI0 Local Fault Inject
                        AQ_PcsReceiveXfi0Provisioning_HHD.u1.bits_1.xfi0LocalFaultInject

                        Default = 0x0

                        1 = XFI0 Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault  */
      unsigned int   xfi0LocalFaultInject : 1;    /* 03.E461.3  R/W      Default = 0x0 */
                     /* 1 = XFI0 Inject local fault
                          */
      unsigned int   reserved1 : 3;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveXfi0Provisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive XFI1 Provisioning: 03.E470 */
/*                  PCS Receive XFI1 Provisioning: 03.E470 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive XFI1 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.E470.1 R/W XFI1 Rx Descrambler Disable
                        AQ_PcsReceiveXfi1Provisioning_HHD.u0.bits_0.xfi1RxDescramblerDisable

                        Default = 0x0

                        1 = XFI1 Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Descrambler Disable  */
      unsigned int   xfi1RxDescramblerDisable : 1;    /* 03.E470.1  R/W      Default = 0x0 */
                     /* 1 = XFI1 Disable PCS scrambler
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI1 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 03.E471.8 R/W XFI1 Test Data Source
                        AQ_PcsReceiveXfi1Provisioning_HHD.u1.bits_1.xfi1TestDataSource

                        Default = 0x0

                        XFI1 Data pattern select
                        1 = All-zero input for pseudo-random test
                        1 = Local-fault (LF) input for pseudo-random test
                        

                 <B>Notes:</B>
                        This bit determines the source of the data for the pseudo-random test (selected by Bit 7).  */
      unsigned int   xfi1TestDataSource : 1;    /* 03.E471.8  R/W      Default = 0x0 */
                     /* XFI1 Data pattern select
                        1 = All-zero input for pseudo-random test
                        1 = Local-fault (LF) input for pseudo-random test
                          */
                    /*! \brief 03.E471.7:5 R/W XFI0 Test Mode Select [2:0]
                        AQ_PcsReceiveXfi1Provisioning_HHD.u1.bits_1.xfi0TestModeSelect

                        Default = 0x0

                        Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random

                 <B>Notes:</B>
                        Note that the source for the pseudo-random test is determined by Bit 8.  */
      unsigned int   xfi0TestModeSelect : 3;    /* 03.E471.7:5  R/W      Default = 0x0 */
                     /* Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random  */
                    /*! \brief 03.E471.4 R/W XFI1 Test Pattern Enable
                        AQ_PcsReceiveXfi1Provisioning_HHD.u1.bits_1.xfi1TestPatternEnable

                        Default = 0x0

                        1 = XFI1 Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable - see the external view for an explanation  */
      unsigned int   xfi1TestPatternEnable : 1;    /* 03.E471.4  R/W      Default = 0x0 */
                     /* 1 = XFI1 Test pattern enabled
                          */
                    /*! \brief 03.E471.3 R/W XFI1 Local Fault Inject
                        AQ_PcsReceiveXfi1Provisioning_HHD.u1.bits_1.xfi1LocalFaultInject

                        Default = 0x0

                        1 = XFI1 Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault  */
      unsigned int   xfi1LocalFaultInject : 1;    /* 03.E471.3  R/W      Default = 0x0 */
                     /* 1 = XFI1 Inject local fault
                          */
      unsigned int   reserved1 : 3;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveXfi1Provisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 RX Control Register: 03.E4D0 */
/*                  PCS USX0 RX Control Register: 03.E4D0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 RX Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.E4D0.F:C R/W USX0 Rx Rsvd Control[3:0]
                        AQ_PcsUsx0RxControlRegister_HHD.u0.bits_0.usx0RxRsvdControl

                        Default = 0x0

                        USX0 Receive Reserved Control
                        
  */
      unsigned int   usx0RxRsvdControl : 4;    /* 03.E4D0.F:C  R/W      Default = 0x0 */
                     /* USX0 Receive Reserved Control
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 03.E4D0.9 R/W USX0 Header CRC Chk
                        AQ_PcsUsx0RxControlRegister_HHD.u0.bits_0.usx0HeaderCrcChk

                        Default = 0x0

                        USX0 Header CRC Check Enable
                        
  */
      unsigned int   usx0HeaderCrcChk : 1;    /* 03.E4D0.9  R/W      Default = 0x0 */
                     /* USX0 Header CRC Check Enable
                          */
                    /*! \brief 03.E4D0.8 R/W USX0 RX PKT Info Extension Field
                        AQ_PcsUsx0RxControlRegister_HHD.u0.bits_0.usx0RxPktInfoExtensionField

                        Default = 0x0

                        Set to 1 to include the Extension Field for the detection of the change notification, otherwise the Extension Field is ignored.
                        
                        
  */
      unsigned int   usx0RxPktInfoExtensionField : 1;    /* 03.E4D0.8  R/W      Default = 0x0 */
                     /* Set to 1 to include the Extension Field for the detection of the change notification, otherwise the Extension Field is ignored.
                        
                          */
                    /*! \brief 03.E4D0.7:6 R/W USX0 RX Local Fault Mode[1:0]
                        AQ_PcsUsx0RxControlRegister_HHD.u0.bits_0.usx0RxLocalFaultMode

                        Default = 0x0

                        Rx USXGMII Local_Fault mode:
                        0=Pass-through
                        1=Replaced with Idle
                        2=Replaced with user-defined code
                        3=Reserved
                        
                        
                        
  */
      unsigned int   usx0RxLocalFaultMode : 2;    /* 03.E4D0.7:6  R/W      Default = 0x0 */
                     /* Rx USXGMII Local_Fault mode:
                        0=Pass-through
                        1=Replaced with Idle
                        2=Replaced with user-defined code
                        3=Reserved
                        
                        
                          */
                    /*! \brief 03.E4D0.5:4 R/W USX0 RX IFG mode[1:0]
                        AQ_PcsUsx0RxControlRegister_HHD.u0.bits_0.usx0RxIfgMode

                        Default = 0x0

                        Rx Inter-Frame Gap Mode [1:0]
                        Minimum IFG assured on traffic sent to
                        GMII/MII (0:12-byte, 1 to 2: reserved,
                        3:none, default:0)
                        
                        
                        
  */
      unsigned int   usx0RxIfgMode : 2;    /* 03.E4D0.5:4  R/W      Default = 0x0 */
                     /* Rx Inter-Frame Gap Mode [1:0]
                        Minimum IFG assured on traffic sent to
                        GMII/MII (0:12-byte, 1 to 2: reserved,
                        3:none, default:0)
                        
                        
                          */
                    /*! \brief 03.E4D0.3:0 R/W USX0 RX XGMII to GMII conversion control[3:0]
                        AQ_PcsUsx0RxControlRegister_HHD.u0.bits_0.usx0RxXgmiiToGmiiConversionControl

                        Default = 0x0

                        XGMII to GMII/MII Conversion Control
                        Bits 0-3: Reserved
                        
                        
  */
      unsigned int   usx0RxXgmiiToGmiiConversionControl : 4;    /* 03.E4D0.3:0  R/W      Default = 0x0 */
                     /* XGMII to GMII/MII Conversion Control
                        Bits 0-3: Reserved
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0RxControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 RX FIFO Control Register: 03.E4D1 */
/*                  PCS USX0 RX FIFO Control Register: 03.E4D1 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 RX FIFO Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 03.E4D1.8 R/W USX0 RX FIFO Reset
                        AQ_PcsUsx0RxFifoControlRegister_HHD.u0.bits_0.usx0RxFifoReset

                        Default = 0x0

                        MAC Rx FIFO reset
                        
  */
      unsigned int   usx0RxFifoReset : 1;    /* 03.E4D1.8  R/W      Default = 0x0 */
                     /* MAC Rx FIFO reset
                          */
                    /*! \brief 03.E4D1.7:4 R/W USX0 RX FIFO Threshold[3:0]
                        AQ_PcsUsx0RxFifoControlRegister_HHD.u0.bits_0.usx0RxFifoThreshold

                        Default = 0x1

                        MAC Rx FIFO threshold 
                        This is used to establish minimum FIFO
                        depth before starting to read. 
                        
  */
      unsigned int   usx0RxFifoThreshold : 4;    /* 03.E4D1.7:4  R/W      Default = 0x1 */
                     /* MAC Rx FIFO threshold 
                        This is used to establish minimum FIFO
                        depth before starting to read. 
                          */
                    /*! \brief 03.E4D1.3:0 R/W USX0 RX FIFO IFG Threshold[3:0]
                        AQ_PcsUsx0RxFifoControlRegister_HHD.u0.bits_0.usx0RxFifoIfgThreshold

                        Default = 0x8

                        MAC Rx FIFO IFG threshold (default:8)
                        This is used to delete Idle when FIFO depth is beyond this threshold.
                        
  */
      unsigned int   usx0RxFifoIfgThreshold : 4;    /* 03.E4D1.3:0  R/W      Default = 0x8 */
                     /* MAC Rx FIFO IFG threshold (default:8)
                        This is used to delete Idle when FIFO depth is beyond this threshold.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0RxFifoControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 SM Control Register: 03.E4D2 */
/*                  PCS USX0 SM Control Register: 03.E4D2 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 SM Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.E4D2.B R/W USX0 SM Freeze
                        AQ_PcsUsx0SmControlRegister_HHD.u0.bits_0.usx0SmFreeze

                        Default = 0x0

                        SAN State Machine Freeze
                        
  */
      unsigned int   usx0SmFreeze : 1;    /* 03.E4D2.B  R/W      Default = 0x0 */
                     /* SAN State Machine Freeze
                          */
                    /*! \brief 03.E4D2.A R/W USX0 SM Force
                        AQ_PcsUsx0SmControlRegister_HHD.u0.bits_0.usx0SmForce

                        Default = 0x0

                        SAN State Machine Force
                        
  */
      unsigned int   usx0SmForce : 1;    /* 03.E4D2.A  R/W      Default = 0x0 */
                     /* SAN State Machine Force
                          */
                    /*! \brief 03.E4D2.9 R/W USX0 SM Redirect
                        AQ_PcsUsx0SmControlRegister_HHD.u0.bits_0.usx0SmRedirect

                        Default = 0x0

                        SAN State Machine Redirect
                        
  */
      unsigned int   usx0SmRedirect : 1;    /* 03.E4D2.9  R/W      Default = 0x0 */
                     /* SAN State Machine Redirect
                          */
                    /*! \brief 03.E4D2.8:6 R/W USX0 SM Current State Match[2:0]
                        AQ_PcsUsx0SmControlRegister_HHD.u0.bits_0.usx0SmCurrentStateMatch

                        Default = 0x0

                        SAN State Machine Current State Match
                        
  */
      unsigned int   usx0SmCurrentStateMatch : 3;    /* 03.E4D2.8:6  R/W      Default = 0x0 */
                     /* SAN State Machine Current State Match
                          */
                    /*! \brief 03.E4D2.5:3 R/W USX0 SM Next state Match[2:0]
                        AQ_PcsUsx0SmControlRegister_HHD.u0.bits_0.usx0SmNextStateMatch

                        Default = 0x0

                        SAN State Machine Next State Match
                        
  */
      unsigned int   usx0SmNextStateMatch : 3;    /* 03.E4D2.5:3  R/W      Default = 0x0 */
                     /* SAN State Machine Next State Match
                          */
                    /*! \brief 03.E4D2.2:0 R/W USX0 SM Redirect state[2:0]
                        AQ_PcsUsx0SmControlRegister_HHD.u0.bits_0.usx0SmRedirectState

                        Default = 0x0

                        SAN State Machine redirect State.
                        
  */
      unsigned int   usx0SmRedirectState : 3;    /* 03.E4D2.2:0  R/W      Default = 0x0 */
                     /* SAN State Machine redirect State.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0SmControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Link Timer Control Register: 03.E4D3 */
/*                  PCS USX0 Link Timer Control Register: 03.E4D3 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Link Timer Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.E4D3.B R/W USX0 Link Timer Reset
                        AQ_PcsUsx0LinkTimerControlRegister_HHD.u0.bits_0.usx0LinkTimerReset

                        Default = 0x0

                        Link_timer Reset (0=Normal, 1=Reset to 0)
                        
  */
      unsigned int   usx0LinkTimerReset : 1;    /* 03.E4D3.B  R/W      Default = 0x0 */
                     /* Link_timer Reset (0=Normal, 1=Reset to 0)
                          */
                    /*! \brief 03.E4D3.A R/W USX0 Link Timer Freeze
                        AQ_PcsUsx0LinkTimerControlRegister_HHD.u0.bits_0.usx0LinkTimerFreeze

                        Default = 0x0

                        Link_timer Freeze (0=Normal, 1=Frozen)
                        
  */
      unsigned int   usx0LinkTimerFreeze : 1;    /* 03.E4D3.A  R/W      Default = 0x0 */
                     /* Link_timer Freeze (0=Normal, 1=Frozen)
                          */
                    /*! \brief 03.E4D3.9:0 R/W USX0 Link Timer Threshold[9:0]
                        AQ_PcsUsx0LinkTimerControlRegister_HHD.u0.bits_0.usx0LinkTimerThreshold

                        Default = 0x07D

                        Link timer threshold (in terms of 12.8us,
                        default=125 for 1.6ms)
                        
  */
      unsigned int   usx0LinkTimerThreshold : 10;    /* 03.E4D3.9:0  R/W      Default = 0x07D */
                     /* Link timer threshold (in terms of 12.8us,
                        default=125 for 1.6ms)
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0LinkTimerControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 RX Fault Control Register: 03.E4D4 */
/*                  PCS USX0 RX Fault Control Register: 03.E4D4 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 RX Fault Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.E4D4.F:8 R/W USX0 RX Fault Mask[7:0]
                        AQ_PcsUsx0RxFaultControlRegister_HHD.u0.bits_0.usx0RxFaultMask

                        Default = 0xFF

                        Set to 1 to compare the corresponding bit(s) against the Fault data pattern, otherwise the corresponding bit(s) are ignored.
                        
                        
  */
      unsigned int   usx0RxFaultMask : 8;    /* 03.E4D4.F:8  R/W      Default = 0xFF */
                     /* Set to 1 to compare the corresponding bit(s) against the Fault data pattern, otherwise the corresponding bit(s) are ignored.
                        
                          */
                    /*! \brief 03.E4D4.7:0 R/W USX0 RX Fault Data[7:0]
                        AQ_PcsUsx0RxFaultControlRegister_HHD.u0.bits_0.usx0RxFaultData

                        Default = 0x11

                        Data pattern with the corresponding mask to compare against the receive data for the detection of Fault signal.
                        
                        
  */
      unsigned int   usx0RxFaultData : 8;    /* 03.E4D4.7:0  R/W      Default = 0x11 */
                     /* Data pattern with the corresponding mask to compare against the receive data for the detection of Fault signal.
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0RxFaultControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 RX Control Register: 03.E4E0 */
/*                  PCS USX1 RX Control Register: 03.E4E0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 RX Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.E4E0.F:C R/W USX1 Rx Rsvd Control[3:0]
                        AQ_PcsUsx1RxControlRegister_HHD.u0.bits_0.usx1RxRsvdControl

                        Default = 0x0

                        USX0 Receive Reserved Control
                        
  */
      unsigned int   usx1RxRsvdControl : 4;    /* 03.E4E0.F:C  R/W      Default = 0x0 */
                     /* USX0 Receive Reserved Control
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 03.E4E0.9 R/W USX1 Header CRC Chk
                        AQ_PcsUsx1RxControlRegister_HHD.u0.bits_0.usx1HeaderCrcChk

                        Default = 0x0

                        USX1 Header CRC Check Enable
                        
  */
      unsigned int   usx1HeaderCrcChk : 1;    /* 03.E4E0.9  R/W      Default = 0x0 */
                     /* USX1 Header CRC Check Enable
                          */
                    /*! \brief 03.E4E0.8 R/W USX1 RX PKT Info Extension Field
                        AQ_PcsUsx1RxControlRegister_HHD.u0.bits_0.usx1RxPktInfoExtensionField

                        Default = 0x0

                        Set to 1 to include the Extension Field for the detection of the change notification, otherwise the Extension Field is ignored.
                        
                        
  */
      unsigned int   usx1RxPktInfoExtensionField : 1;    /* 03.E4E0.8  R/W      Default = 0x0 */
                     /* Set to 1 to include the Extension Field for the detection of the change notification, otherwise the Extension Field is ignored.
                        
                          */
                    /*! \brief 03.E4E0.7:6 R/W USX1 RX Local Fault Mode[1:0]
                        AQ_PcsUsx1RxControlRegister_HHD.u0.bits_0.usx1RxLocalFaultMode

                        Default = 0x0

                        Rx USXGMII Local_Fault mode:
                        0=Pass-through
                        1=Replaced with Idle
                        2=Replaced with user-defined code
                        3=Reserved
                        
                        
                        
  */
      unsigned int   usx1RxLocalFaultMode : 2;    /* 03.E4E0.7:6  R/W      Default = 0x0 */
                     /* Rx USXGMII Local_Fault mode:
                        0=Pass-through
                        1=Replaced with Idle
                        2=Replaced with user-defined code
                        3=Reserved
                        
                        
                          */
                    /*! \brief 03.E4E0.5:4 R/W USX1 RX IFG mode[1:0]
                        AQ_PcsUsx1RxControlRegister_HHD.u0.bits_0.usx1RxIfgMode

                        Default = 0x0

                        Rx Inter-Frame Gap Mode [1:0]
                        Minimum IFG assured on traffic sent to
                        GMII/MII (0:12-byte, 1 to 2: reserved,
                        3:none, default:0)
                        
                        
                        
  */
      unsigned int   usx1RxIfgMode : 2;    /* 03.E4E0.5:4  R/W      Default = 0x0 */
                     /* Rx Inter-Frame Gap Mode [1:0]
                        Minimum IFG assured on traffic sent to
                        GMII/MII (0:12-byte, 1 to 2: reserved,
                        3:none, default:0)
                        
                        
                          */
                    /*! \brief 03.E4E0.3:0 R/W USX1 RX XGMII to GMII conversion control[3:0]
                        AQ_PcsUsx1RxControlRegister_HHD.u0.bits_0.usx1RxXgmiiToGmiiConversionControl

                        Default = 0x0

                        XGMII to GMII/MII Conversion Control
                        Bits 0-3: Reserved
                        
                        
  */
      unsigned int   usx1RxXgmiiToGmiiConversionControl : 4;    /* 03.E4E0.3:0  R/W      Default = 0x0 */
                     /* XGMII to GMII/MII Conversion Control
                        Bits 0-3: Reserved
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1RxControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 RX FIFO Control Register: 03.E4E1 */
/*                  PCS USX1 RX FIFO Control Register: 03.E4E1 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 RX FIFO Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 03.E4E1.8 R/W USX1 RX FIFO Reset
                        AQ_PcsUsx1RxFifoControlRegister_HHD.u0.bits_0.usx1RxFifoReset

                        Default = 0x0

                        MAC Rx FIFO reset
                        
  */
      unsigned int   usx1RxFifoReset : 1;    /* 03.E4E1.8  R/W      Default = 0x0 */
                     /* MAC Rx FIFO reset
                          */
                    /*! \brief 03.E4E1.7:4 R/W USX1 RX FIFO Threshold[3:0]
                        AQ_PcsUsx1RxFifoControlRegister_HHD.u0.bits_0.usx1RxFifoThreshold

                        Default = 0x1

                        MAC Rx FIFO threshold 
                        This is used to establish minimum FIFO
                        depth before starting to read. 
                        
  */
      unsigned int   usx1RxFifoThreshold : 4;    /* 03.E4E1.7:4  R/W      Default = 0x1 */
                     /* MAC Rx FIFO threshold 
                        This is used to establish minimum FIFO
                        depth before starting to read. 
                          */
                    /*! \brief 03.E4E1.3:0 R/W USX1 RX FIFO IFG Threshold[3:0]
                        AQ_PcsUsx1RxFifoControlRegister_HHD.u0.bits_0.usx1RxFifoIfgThreshold

                        Default = 0x8

                        MAC Rx FIFO IFG threshold (default:8)
                        This is used to delete Idle when FIFO depth is beyond this threshold.
                        
  */
      unsigned int   usx1RxFifoIfgThreshold : 4;    /* 03.E4E1.3:0  R/W      Default = 0x8 */
                     /* MAC Rx FIFO IFG threshold (default:8)
                        This is used to delete Idle when FIFO depth is beyond this threshold.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1RxFifoControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 SM Control Register: 03.E4E2 */
/*                  PCS USX1 SM Control Register: 03.E4E2 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 SM Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.E4E2.B R/W USX0 SM Freeze
                        AQ_PcsUsx1SmControlRegister_HHD.u0.bits_0.usx0SmFreeze

                        Default = 0x0

                        SAN State Machine Freeze
                        
  */
      unsigned int   usx0SmFreeze : 1;    /* 03.E4E2.B  R/W      Default = 0x0 */
                     /* SAN State Machine Freeze
                          */
                    /*! \brief 03.E4E2.A R/W USX1 SM Force
                        AQ_PcsUsx1SmControlRegister_HHD.u0.bits_0.usx1SmForce

                        Default = 0x0

                        SAN State Machine Force
                        
  */
      unsigned int   usx1SmForce : 1;    /* 03.E4E2.A  R/W      Default = 0x0 */
                     /* SAN State Machine Force
                          */
                    /*! \brief 03.E4E2.9 R/W USX1 SM Redirect
                        AQ_PcsUsx1SmControlRegister_HHD.u0.bits_0.usx1SmRedirect

                        Default = 0x0

                        SAN State Machine Redirect
                        
  */
      unsigned int   usx1SmRedirect : 1;    /* 03.E4E2.9  R/W      Default = 0x0 */
                     /* SAN State Machine Redirect
                          */
                    /*! \brief 03.E4E2.8:6 R/W USX1 SM Current State Match[2:0]
                        AQ_PcsUsx1SmControlRegister_HHD.u0.bits_0.usx1SmCurrentStateMatch

                        Default = 0x0

                        SAN State Machine Current State Match
                        
  */
      unsigned int   usx1SmCurrentStateMatch : 3;    /* 03.E4E2.8:6  R/W      Default = 0x0 */
                     /* SAN State Machine Current State Match
                          */
                    /*! \brief 03.E4E2.5:3 R/W USX1 SM Next state Match[2:0]
                        AQ_PcsUsx1SmControlRegister_HHD.u0.bits_0.usx1SmNextStateMatch

                        Default = 0x0

                        SAN State Machine Next State Match
                        
  */
      unsigned int   usx1SmNextStateMatch : 3;    /* 03.E4E2.5:3  R/W      Default = 0x0 */
                     /* SAN State Machine Next State Match
                          */
                    /*! \brief 03.E4E2.2:0 R/W USX1 SM Redirect state[2:0]
                        AQ_PcsUsx1SmControlRegister_HHD.u0.bits_0.usx1SmRedirectState

                        Default = 0x0

                        SAN State Machine redirect State.
                        
  */
      unsigned int   usx1SmRedirectState : 3;    /* 03.E4E2.2:0  R/W      Default = 0x0 */
                     /* SAN State Machine redirect State.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1SmControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Link Timer Control Register: 03.E4E3 */
/*                  PCS USX1 Link Timer Control Register: 03.E4E3 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Link Timer Control Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.E4E3.B R/W USX1 Link Timer Reset
                        AQ_PcsUsx1LinkTimerControlRegister_HHD.u0.bits_0.usx1LinkTimerReset

                        Default = 0x0

                        Link_timer Reset (0=Normal, 1=Reset to 0)
                        
  */
      unsigned int   usx1LinkTimerReset : 1;    /* 03.E4E3.B  R/W      Default = 0x0 */
                     /* Link_timer Reset (0=Normal, 1=Reset to 0)
                          */
                    /*! \brief 03.E4E3.A R/W USX1 Link Timer Freeze
                        AQ_PcsUsx1LinkTimerControlRegister_HHD.u0.bits_0.usx1LinkTimerFreeze

                        Default = 0x0

                        Link_timer Freeze (0=Normal, 1=Frozen)
                        
  */
      unsigned int   usx1LinkTimerFreeze : 1;    /* 03.E4E3.A  R/W      Default = 0x0 */
                     /* Link_timer Freeze (0=Normal, 1=Frozen)
                          */
                    /*! \brief 03.E4E3.9:0 R/W USX1 Link Timer Threshold[9:0]
                        AQ_PcsUsx1LinkTimerControlRegister_HHD.u0.bits_0.usx1LinkTimerThreshold

                        Default = 0x07D

                        Link timer threshold (in terms of 12.8us,
                        default=125 for 1.6ms)
                        
  */
      unsigned int   usx1LinkTimerThreshold : 10;    /* 03.E4E3.9:0  R/W      Default = 0x07D */
                     /* Link timer threshold (in terms of 12.8us,
                        default=125 for 1.6ms)
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1LinkTimerControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 RX Fault Control Register: 03.E4E4 */
/*                  PCS USX1 RX Fault Control Register: 03.E4E4 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 RX Fault Control Register */
  union
  {
    struct
    {
                    /*! \brief 03.E4E4.F:8 R/W USX1 RX Fault Mask[7:0]
                        AQ_PcsUsx1RxFaultControlRegister_HHD.u0.bits_0.usx1RxFaultMask

                        Default = 0xFF

                        Set to 1 to compare the corresponding bit(s) against the Fault data pattern, otherwise the corresponding bit(s) are ignored.
                        
                        
  */
      unsigned int   usx1RxFaultMask : 8;    /* 03.E4E4.F:8  R/W      Default = 0xFF */
                     /* Set to 1 to compare the corresponding bit(s) against the Fault data pattern, otherwise the corresponding bit(s) are ignored.
                        
                          */
                    /*! \brief 03.E4E4.7:0 R/W USX1 RX Fault Data[7:0]
                        AQ_PcsUsx1RxFaultControlRegister_HHD.u0.bits_0.usx1RxFaultData

                        Default = 0x11

                        Data pattern with the corresponding mask to compare against the receive data for the detection of Fault signal.
                        
                        
  */
      unsigned int   usx1RxFaultData : 8;    /* 03.E4E4.7:0  R/W      Default = 0x11 */
                     /* Data pattern with the corresponding mask to compare against the receive data for the detection of Fault signal.
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1RxFaultControlRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS PTP Ingress Vendor Provisioning: 03.E600 */
/*                  PCS PTP Ingress Vendor Provisioning: 03.E600 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E600.F R/W PTP Ingress VLAN Tagging Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngressVlanTaggingEnable

                        Default = 0x0

                        1 = PTP Ingress VLAN tagging enabled
                        

                 <B>Notes:</B>
                        Enable VLAN tagging for IEEE1588 or NTP/SNTP packet (default:0x1)  */
      unsigned int   ptpIngressVlanTaggingEnable : 1;    /* 03.E600.F  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress VLAN tagging enabled
                          */
                    /*! \brief 03.E600.E R/W PTP Ingress IPv6/UDP Encapsulated Enabled
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngressIpv6_udpEncapsulatedEnabled

                        Default = 0x0

                        1 = PTP Ingress IPv6/UDP encapsulated enable
                        

                 <B>Notes:</B>
                        Enable IPv6/UDP encapsulated IEEE1588 or NTP/SNTP packet (default: 0)  */
      unsigned int   ptpIngressIpv6_udpEncapsulatedEnabled : 1;    /* 03.E600.E  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress IPv6/UDP encapsulated enable
                          */
                    /*! \brief 03.E600.D R/W PTP Ingress IPv4/UDP Encapsulated Enabled
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngressIpv4_udpEncapsulatedEnabled

                        Default = 0x0

                        1 = PTP Ingress IPv4/UDP encapsulated enable
                        

                 <B>Notes:</B>
                        Enable IPv4/UDP encapsulated IEEE1588 or NTP/SNTP packet (default: 0)  */
      unsigned int   ptpIngressIpv4_udpEncapsulatedEnabled : 1;    /* 03.E600.D  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress IPv4/UDP encapsulated enable
                          */
                    /*! \brief 03.E600.C R/W PTP Ingress Ethernet Encapsulated Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngressEthernetEncapsulatedEnable

                        Default = 0x0

                        1 = PTP Ingress ethernet encapsulated enable
                        

                 <B>Notes:</B>
                        Enable Ethernet encapsulated IEEE1588 packet (default: 0)  */
      unsigned int   ptpIngressEthernetEncapsulatedEnable : 1;    /* 03.E600.C  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress ethernet encapsulated enable
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 03.E600.9:8 R/W PTP Ingress NTP Configuration [1:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngressNtpConfiguration

                        Default = 0x0

                        PTP Ingress NTP/SNTP configuration
                        

                 <B>Notes:</B>
                        NTP/SNTP configuration (bit 0: 0=client, 1=server, bit 1: 0=Ingress, 1=ingress)  */
      unsigned int   ptpIngressNtpConfiguration : 2;    /* 03.E600.9:8  R/W      Default = 0x0 */
                     /* PTP Ingress NTP/SNTP configuration
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.E600.5 R/W PTP Ingress Back Pressure Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngressBackPressureEnable

                        Default = 0x0

                        1 = PTP Ingress back pressure enable
                        

                 <B>Notes:</B>
                        PTP FIFO ready enable (default: 0)
                        Set to 1 to enable the back pressure during the appending of timestamp to the end of packet
                        Set to 0 to disable the back pressue.  */
      unsigned int   ptpIngressBackPressureEnable : 1;    /* 03.E600.5  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress back pressure enable
                          */
                    /*! \brief 03.E600.4 R/W PTP Ingress NTP Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngressNtpEnable

                        Default = 0x0

                        1 = PTP Ingress NTP/SNTP enable
                        

                 <B>Notes:</B>
                        Enable NTP/SNTP  */
      unsigned int   ptpIngressNtpEnable : 1;    /* 03.E600.4  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress NTP/SNTP enable
                          */
      unsigned int   reserved2 : 2;
                    /*! \brief 03.E600.1 R/W PTP Ingress 1588 Version 2 Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngress_1588Version_2Enable

                        Default = 0x0

                        1 = PTP Ingress 1588 version 2 enable
                        

                 <B>Notes:</B>
                        Enable IEEE 1588 Version 2  */
      unsigned int   ptpIngress_1588Version_2Enable : 1;    /* 03.E600.1  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress 1588 version 2 enable
                          */
                    /*! \brief 03.E600.0 R/W PTP Ingress 1588 Version 1 Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u0.bits_0.ptpIngress_1588Version_1Enable

                        Default = 0x0

                        1 = PTP Ingress 1588 version 1 enable
                        

                 <B>Notes:</B>
                        Enable IEEE 1588 Version 1  */
      unsigned int   ptpIngress_1588Version_1Enable : 1;    /* 03.E600.0  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress 1588 version 1 enable
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 03.E601.E:C R/W PTP Ingress IPv6 Destination Address Matching Enable [2:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u1.bits_1.ptpIngressIpv6DestinationAddressMatchingEnable

                        Default = 0x3

                        PTP Ingress IPv6 destination address matching enable
                        

                 <B>Notes:</B>
                        Enable IPv6 destination address matching for IEEE1588 (default:0x3)
                        bit 0: FF0X:0:0:0:0:0:0:181 (X: 0x0 to 0xF)
                        bit 1: FF02:0:0:0:0:0:0:6B
                        bit 2: user-defined  */
      unsigned int   ptpIngressIpv6DestinationAddressMatchingEnable : 3;    /* 03.E601.E:C  R/W      Default = 0x3 */
                     /* PTP Ingress IPv6 destination address matching enable
                          */
                    /*! \brief 03.E601.B:8 R/W PTP Ingress IPv4 Destination Address Matching Enable [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u1.bits_1.ptpIngressIpv4DestinationAddressMatchingEnable

                        Default = 0x7

                        PTP Ingress IPv4 destination address matching enable
                        

                 <B>Notes:</B>
                        Enable IPv4 destination address matching for IEEE1588 (default:0x7)
                        bit 0: 224.0.1.129
                        bit 1: 224.0.1.130-132
                        bit 2: 224.0.0.107
                        bit 3: user-defiined  */
      unsigned int   ptpIngressIpv4DestinationAddressMatchingEnable : 4;    /* 03.E601.B:8  R/W      Default = 0x7 */
                     /* PTP Ingress IPv4 destination address matching enable
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.E601.6:4 R/W PTP Ingress MAC Destination Address Matching Enable [2:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u1.bits_1.ptpIngressMacDestinationAddressMatchingEnable

                        Default = 0x3

                        PTP Ingress MAC destination address matching enable
                        

                 <B>Notes:</B>
                        Enable MAC destination address matching for IEEE1588 (default:0x3)
                        bit 0: 01-1B-19-00-00-00
                        bit 1: 01-80-C2-00-00-0E
                        bit 2: user-defined  */
      unsigned int   ptpIngressMacDestinationAddressMatchingEnable : 3;    /* 03.E601.6:4  R/W      Default = 0x3 */
                     /* PTP Ingress MAC destination address matching enable
                          */
      unsigned int   reserved2 : 2;
                    /*! \brief 03.E601.1:0 R/W PTP Ingress Ethertype Matching Enable [1:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u1.bits_1.ptpIngressEthertypeMatchingEnable

                        Default = 0x1

                        PTP Ingress ethertype matching enable
                        

                 <B>Notes:</B>
                        Enable Ethertype matching for Ethernet encapsulated IEEE1588 packet (default:0x1)
                        bit 0: 0x88F7
                        bit 1: user-defined
                        This shall be configured before enable Ethernet encapsulation. At least one bit needs to be set.  */
      unsigned int   ptpIngressEthertypeMatchingEnable : 2;    /* 03.E601.1:0  R/W      Default = 0x1 */
                     /* PTP Ingress ethertype matching enable
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 03.E602.E:C R/W PTP Ingress NTP/SNTP Version [2:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u2.bits_2.ptpIngressNtp_sntpVersion

                        Default = 0x3

                        PTP Ingress NTP/SNTP version
                        

                 <B>Notes:</B>
                        Version of NTP/SNTP (default: 3)
                        It specifies the minimum value of version number of NTP/SNTP to be supported. It shall not be less than 3, but a value of 0 will disable version checking.  */
      unsigned int   ptpIngressNtp_sntpVersion : 3;    /* 03.E602.E:C  R/W      Default = 0x3 */
                     /* PTP Ingress NTP/SNTP version
                          */
                    /*! \brief 03.E602.B:8 R/W PTP Ingress 1588 Version [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u2.bits_2.ptpIngress_1588Version

                        Default = 0x2

                        PTP Ingress IEEE 1588 version
                        

                 <B>Notes:</B>
                        Latest version of IEEE1588 (default: 2)
                        It allows support of future versions of the IEEE 1588. It shall not be less than 2, but a value of 0 will disable version checking and assume to be compatible with version 2.  */
      unsigned int   ptpIngress_1588Version : 4;    /* 03.E602.B:8  R/W      Default = 0x2 */
                     /* PTP Ingress IEEE 1588 version
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.E602.5 R/W PTP Ingress 1588 2 Step Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u2.bits_2.ptpIngress_1588_2StepEnable

                        Default = 0x0

                        PTP Ingress 1588 2 step enable
                        

                 <B>Notes:</B>
                        Set to 1 to consider the two-step flag for IEEE1588v2 (or PTP_ASSIST for IEEE1588v1). It will prevent timestamp overwritten for 2-step Sync message. Set to 0 will allow timestamp update regardless of the flag (default: 0)  */
      unsigned int   ptpIngress_1588_2StepEnable : 1;    /* 03.E602.5  R/W      Default = 0x0 */
                     /* PTP Ingress 1588 2 step enable
                          */
                    /*! \brief 03.E602.4 R/W PTP Ingress 1588 Version 2 Domain Matching Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u2.bits_2.ptpIngress_1588Version_2DomainMatchingEnable

                        Default = 0x0

                        1 = PTP Ingress 1588 version 2 domain matching enable
                        

                 <B>Notes:</B>
                        Enable domain matching for IEEE1588v2 (default: 0)  */
      unsigned int   ptpIngress_1588Version_2DomainMatchingEnable : 1;    /* 03.E602.4  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress 1588 version 2 domain matching enable
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 03.E602.2:0 R/W PTP Ingress UDP Destination Port Matching Enable [2:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u2.bits_2.ptpIngressUdpDestinationPortMatchingEnable

                        Default = 0x3

                        PTP Ingress UDP destination port matching enable
                        

                 <B>Notes:</B>
                        Enable UDP destination port matching for IEEE 1588 or NTP/SNTP (default:0x3)
                        bit 0: 319 for IEEE1588, or 123 for NTP/SNTP
                        bit 1: 320 for IEEE1588, not used for NTP/SNTP
                        bit 2: user-defined  */
      unsigned int   ptpIngressUdpDestinationPortMatchingEnable : 3;    /* 03.E602.2:0  R/W      Default = 0x3 */
                     /* PTP Ingress UDP destination port matching enable
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E603.F:0 R/W PTP Ingress Ethertype [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u3.bits_3.ptpIngressEthertype

                        Default = 0x0000

                        PTP Ingress UDP destination port matching enable
                        

                 <B>Notes:</B>
                        User-defined EtherType for Ethernet encapsulated IEEE1588 packets (default: 0)  */
      unsigned int   ptpIngressEthertype : 16;    /* 03.E603.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress UDP destination port matching enable
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E604.F:0 R/W PTP Ingress MAC Destination Address Bits 15:0 [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u4.bits_4.ptpIngressMacDestinationAddressBits_15_0

                        Default = 0x0000

                        PTP Ingress MAC destination address bits 15:0
                        

                 <B>Notes:</B>
                        User-defined MAC destination address (default: 0)  */
      unsigned int   ptpIngressMacDestinationAddressBits_15_0 : 16;    /* 03.E604.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress MAC destination address bits 15:0
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E605.F:0 R/W PTP Ingress MAC Destination Address Bits 31:16 [1F:10]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u5.bits_5.ptpIngressMacDestinationAddressBits_31_16

                        Default = 0x0000

                        PTP Ingress MAC destination address bits 31:16
                        

                 <B>Notes:</B>
                        User-defined MAC destination address (default: 0)  */
      unsigned int   ptpIngressMacDestinationAddressBits_31_16 : 16;    /* 03.E605.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress MAC destination address bits 31:16
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E606.F:0 R/W PTP Ingress MAC Destination Address Bits 47:32 [2F:20]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u6.bits_6.ptpIngressMacDestinationAddressBits_47_32

                        Default = 0x0000

                        PTP Ingress MAC destination address bits 47:32
                        

                 <B>Notes:</B>
                        User-defined MAC destination address (default: 0)  */
      unsigned int   ptpIngressMacDestinationAddressBits_47_32 : 16;    /* 03.E606.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress MAC destination address bits 47:32
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E607.F:0 R/W PTP Ingress IPv4 Destination Address LSW [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u7.bits_7.ptpIngressIpv4DestinationAddressLSW

                        Default = 0x0000

                        PTP Ingress IPv4 destination address bits 15:0
                        

                 <B>Notes:</B>
                        User-defined IPv4 destination address (default: 0)  */
      unsigned int   ptpIngressIpv4DestinationAddressLSW : 16;    /* 03.E607.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv4 destination address bits 15:0
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E608.F:0 R/W PTP Ingress IPv4 Destination Address MSW [1F:10]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u8.bits_8.ptpIngressIpv4DestinationAddressMSW

                        Default = 0x0000

                        PTP Ingress IPv4 destination address bits 31:16
                        

                 <B>Notes:</B>
                        User-defined IPv4 destination address (default: 0)  */
      unsigned int   ptpIngressIpv4DestinationAddressMSW : 16;    /* 03.E608.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv4 destination address bits 31:16
                          */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E609.F:0 R/W PTP Ingress IPv6 Destination Address Bits 15:0 [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u9.bits_9.ptpIngressIpv6DestinationAddressBits_15_0

                        Default = 0x0000

                        PTP Ingress IPv6 destination address bits 15:0
                        

                 <B>Notes:</B>
                        User-defined IPv6 destination address (default: 0)  */
      unsigned int   ptpIngressIpv6DestinationAddressBits_15_0 : 16;    /* 03.E609.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv6 destination address bits 15:0
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E60A.F:0 R/W PTP Ingress IPv6 Destination Address Bits 31:16 [1F:10]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u10.bits_10.ptpIngressIpv6DestinationAddressBits_31_16

                        Default = 0x0000

                        PTP Ingress IPv6 destination address bits 31:16
                        

                 <B>Notes:</B>
                        User-defined IPv6 destination address (default: 0)  */
      unsigned int   ptpIngressIpv6DestinationAddressBits_31_16 : 16;    /* 03.E60A.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv6 destination address bits 31:16
                          */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E60B.F:0 R/W PTP Ingress IPv6 Destination Address Bits 47:32 [2F:20]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u11.bits_11.ptpIngressIpv6DestinationAddressBits_47_32

                        Default = 0x0000

                        PTP Ingress IPv6 destination address bits 47:32
                        

                 <B>Notes:</B>
                        User-defined IPv6 destination address (default: 0)  */
      unsigned int   ptpIngressIpv6DestinationAddressBits_47_32 : 16;    /* 03.E60B.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv6 destination address bits 47:32
                          */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E60C.F:0 R/W PTP Ingress IPv6 Destination Address Bits 63:48 [3F:30]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u12.bits_12.ptpIngressIpv6DestinationAddressBits_63_48

                        Default = 0x0000

                        PTP Ingress IPv6 destination address bits 63:48
                        

                 <B>Notes:</B>
                        User-defined IPv6 destination address (default: 0)  */
      unsigned int   ptpIngressIpv6DestinationAddressBits_63_48 : 16;    /* 03.E60C.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv6 destination address bits 63:48
                          */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E60D.F:0 R/W PTP Ingress IPv6 Destination Address Bits 79:64 [4F:40]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u13.bits_13.ptpIngressIpv6DestinationAddressBits_79_64

                        Default = 0x0000

                        PTP Ingress IPv6 destination address bits 79:64
                        

                 <B>Notes:</B>
                        User-defined IPv6 destination address (default: 0)  */
      unsigned int   ptpIngressIpv6DestinationAddressBits_79_64 : 16;    /* 03.E60D.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv6 destination address bits 79:64
                          */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E60E.F:0 R/W PTP Ingress IPv6 Destination Address Bits 95:80 [5F:50]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u14.bits_14.ptpIngressIpv6DestinationAddressBits_95_80

                        Default = 0x0000

                        PTP Ingress IPv6 destination address bits 95:80
                        

                 <B>Notes:</B>
                        User-defined IPv6 destination address (default: 0)  */
      unsigned int   ptpIngressIpv6DestinationAddressBits_95_80 : 16;    /* 03.E60E.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv6 destination address bits 95:80
                          */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E60F.F:0 R/W PTP Ingress IPv6 Destination Address Bits 111:96 [6F:60]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u15.bits_15.ptpIngressIpv6DestinationAddressBits_111_96

                        Default = 0x0000

                        PTP Ingress IPv6 destination address bits 111:96
                        

                 <B>Notes:</B>
                        User-defined IPv6 destination address (default: 0)  */
      unsigned int   ptpIngressIpv6DestinationAddressBits_111_96 : 16;    /* 03.E60F.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv6 destination address bits 111:96
                          */
    } bits_15;
    uint16_t word_15;
  } u15;
  /*! \brief Union for bit and word level access of word 16 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E610.F:0 R/W PTP Ingress IPv6 Destination Address Bits 127:112 [7F:70]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u16.bits_16.ptpIngressIpv6DestinationAddressBits_127_112

                        Default = 0x0000

                        PTP Ingress IPv6 destination address bits 127:112
                        

                 <B>Notes:</B>
                        User-defined IPv6 destination address (default: 0)  */
      unsigned int   ptpIngressIpv6DestinationAddressBits_127_112 : 16;    /* 03.E610.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress IPv6 destination address bits 127:112
                          */
    } bits_16;
    uint16_t word_16;
  } u16;
  /*! \brief Union for bit and word level access of word 17 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E611.F:0 R/W PTP Ingress UDP Destination Port [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u17.bits_17.ptpIngressUdpDestinationPort

                        Default = 0x0000

                        PTP Ingress UDP destination port
                        

                 <B>Notes:</B>
                        User-defined UDP destination port (default: 0)  */
      unsigned int   ptpIngressUdpDestinationPort : 16;    /* 03.E611.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress UDP destination port
                          */
    } bits_17;
    uint16_t word_17;
  } u17;
  /*! \brief Union for bit and word level access of word 18 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.E612.7:0 R/W PTP Ingress 1588 Version 2 Domain [7:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u18.bits_18.ptpIngress_1588Version_2Domain

                        Default = 0x00

                        PTP Ingress 1588 Version 2 Domain
                        

                 <B>Notes:</B>
                        User-defined domain for IEEE1588v2 (default:0)  */
      unsigned int   ptpIngress_1588Version_2Domain : 8;    /* 03.E612.7:0  R/W      Default = 0x00 */
                     /* PTP Ingress 1588 Version 2 Domain
                          */
    } bits_18;
    uint16_t word_18;
  } u18;
  /*! \brief Union for bit and word level access of word 19 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 12;
                    /*! \brief 03.E613.3 R/W PTP Ingress Correction Offset Sign
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u19.bits_19.ptpIngressCorrectionOffsetSign

                        Default = 0x0

                        1 = PTP Ingress correction offset sign
                        

                 <B>Notes:</B>
                        Correction field offset sign (0: add, 1:subtract, default: 0)
                        This indicates whether to add or subtract the correction field offset.  */
      unsigned int   ptpIngressCorrectionOffsetSign : 1;    /* 03.E613.3  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress correction offset sign
                          */
                    /*! \brief 03.E613.2 R/W PTP Ingress Time Stamp Offset Sign
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u19.bits_19.ptpIngressTimeStampOffsetSign

                        Default = 0x0

                        1 = PTP Ingress time stamp offset sign
                        

                 <B>Notes:</B>
                        Timestamp nano-/fractional-seconds offset sign (0: add, 1:subtract, default: 0)
                        This indicates whether to add or subtract the timestamp compensation offset.  */
      unsigned int   ptpIngressTimeStampOffsetSign : 1;    /* 03.E613.2  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress time stamp offset sign
                          */
                    /*! \brief 03.E613.1 R/W PTP Ingress Set Time Stamp Offset
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u19.bits_19.ptpIngressSetTimeStampOffset

                        Default = 0x0

                        1 = PTP Ingress set time stamp offset
                        

                 <B>Notes:</B>
                        Toggle to set the new offsets of the timestamp and correction field (default: 0)  */
      unsigned int   ptpIngressSetTimeStampOffset : 1;    /* 03.E613.1  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress set time stamp offset
                          */
                    /*! \brief 03.E613.0 R/W PTP Ingress Byte Swap
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u19.bits_19.ptpIngressByteSwap

                        Default = 0x0

                        1 = PTP Ingress byte swap
                        

                 <B>Notes:</B>
                        Swap byte order of the 32-bit packet data (default:0)  */
      unsigned int   ptpIngressByteSwap : 1;    /* 03.E613.0  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress byte swap
                          */
    } bits_19;
    uint16_t word_19;
  } u19;
  /*! \brief Union for bit and word level access of word 20 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E614.F:0 R/W PTP Ingress Time Stamp Nanosecond Offset [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u20.bits_20.ptpIngressTimeStampNanosecondOffset

                        Default = 0x0000

                        PTP Ingress time stamp nanosecond offset
                        

                 <B>Notes:</B>
                        Timestamp nanoseconds offset (default: 0)
                        This compensates the difference between MDI and timestamping point.  */
      unsigned int   ptpIngressTimeStampNanosecondOffset : 16;    /* 03.E614.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress time stamp nanosecond offset
                          */
    } bits_20;
    uint16_t word_20;
  } u20;
  /*! \brief Union for bit and word level access of word 21 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E615.F:0 R/W PTP Ingress Time Stamp Fractional Second Offset LSW [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u21.bits_21.ptpIngressTimeStampFractionalSecondOffsetLSW

                        Default = 0x0000

                        PTP Ingress time stamp fractional second offset
                        

                 <B>Notes:</B>
                        Timestamp fractional-seconds offset (default: 0)
                        This is the LSB 19-bit of the 32-bit fractional- seconds counter. Software shall this value is equivalent to the corresponding nanoseconds offset.  */
      unsigned int   ptpIngressTimeStampFractionalSecondOffsetLSW : 16;    /* 03.E615.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress time stamp fractional second offset
                          */
    } bits_21;
    uint16_t word_21;
  } u21;
  /*! \brief Union for bit and word level access of word 22 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 03.E616.2:0 R/W PTP Ingress Time Stamp Fractional Second Offset MSW [12:10]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u22.bits_22.ptpIngressTimeStampFractionalSecondOffsetMSW

                        Default = 0x0

                        PTP Ingress time stamp fractional second offset
                        

                 <B>Notes:</B>
                        Timestamp fractional-seconds offset (default: 0)
                        This is the LSB 19-bit of the 32-bit fractional- seconds counter. Software shall this value is equivalent to the corresponding nanoseconds offset.  */
      unsigned int   ptpIngressTimeStampFractionalSecondOffsetMSW : 3;    /* 03.E616.2:0  R/W      Default = 0x0 */
                     /* PTP Ingress time stamp fractional second offset
                          */
    } bits_22;
    uint16_t word_22;
  } u22;
  /*! \brief Union for bit and word level access of word 23 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E617.F:0 R/W PTP Ingress Correction Offset LSW [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u23.bits_23.ptpIngressCorrectionOffsetLSW

                        Default = 0x0000

                        PTP Ingress correction offset
                        

                 <B>Notes:</B>
                        Correction field offset (16-bit nano-second & 16-bit fractional nano-second, default: 0)
                        This compensates the asymmetrical Tx/Rx delay, and/or any adjustment for transparent application.  */
      unsigned int   ptpIngressCorrectionOffsetLSW : 16;    /* 03.E617.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress correction offset
                          */
    } bits_23;
    uint16_t word_23;
  } u23;
  /*! \brief Union for bit and word level access of word 24 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E618.F:0 R/W PTP Ingress Correction Offset MSW [1F:10]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u24.bits_24.ptpIngressCorrectionOffsetMSW

                        Default = 0x0000

                        PTP Ingress correction offset
                        

                 <B>Notes:</B>
                        Correction field offset (16-bit nano-second & 16-bit fractional nano-second, default: 0)
                        This compensates the asymmetrical Tx/Rx delay, and/or any adjustment for transparent application.  */
      unsigned int   ptpIngressCorrectionOffsetMSW : 16;    /* 03.E618.F:0  R/W      Default = 0x0000 */
                     /* PTP Ingress correction offset
                          */
    } bits_24;
    uint16_t word_24;
  } u24;
  /*! \brief Union for bit and word level access of word 25 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.E619.B:0 R/W PTP Ingress Packet Action [B:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u25.bits_25.ptpIngressPacketAction

                        Default = 0x000

                        PTP Ingress packet action
                        

                 <B>Notes:</B>
                        IEEE 1588v2 packet action(0=None, 1=Capture, 2=reserved, 3=Capture & forward, default: 0) 
                        Bits [1:0]: Sync message
                        Bits [3:2]: Delay_Req message
                        Bits [5:4]: Pdelay_Req message
                        Bits [7:6]: Pdelay_Resp message
                        Bits [9:8]: User-defined message
                        Bits [11:10]: General messages  */
      unsigned int   ptpIngressPacketAction : 12;    /* 03.E619.B:0  R/W      Default = 0x000 */
                     /* PTP Ingress packet action
                          */
    } bits_25;
    uint16_t word_25;
  } u25;
  /*! \brief Union for bit and word level access of word 26 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 03.E61A.D:C R/W PTP Ingress NTP/SNTP Time Stamp Action [1:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u26.bits_26.ptpIngressNtp_sntpTimeStampAction

                        Default = 0x0

                        PTP Ingress correct action
                        

                 <B>Notes:</B>
                        NTP/SNTP timestamp action (0=None, 1=Overwrite, 2=Append, 3=reserved)  */
      unsigned int   ptpIngressNtp_sntpTimeStampAction : 2;    /* 03.E61A.D:C  R/W      Default = 0x0 */
                     /* PTP Ingress correct action
                          */
                    /*! \brief 03.E61A.B:8 R/W PTP Ingress NTP/SNTP Packet Action [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u26.bits_26.ptpIngressNtp_sntpPacketAction

                        Default = 0x0

                        PTP Ingress correct action
                        

                 <B>Notes:</B>
                        NTP/SNTP packet action (0=None, 1=Capture, 2=reserved, 3=Capture & forward, 3=reserved)
                        Bits [1:0]: Non-control messages
                        Bits [3:2]: Control & Private-use messages  */
      unsigned int   ptpIngressNtp_sntpPacketAction : 4;    /* 03.E61A.B:8  R/W      Default = 0x0 */
                     /* PTP Ingress correct action
                          */
      unsigned int   reserved1 : 8;
    } bits_26;
    uint16_t word_26;
  } u26;
  /*! \brief Union for bit and word level access of word 27 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E61B.5 R/W PTP Ingress Correction Fractional Nanosecond Timestampe Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u27.bits_27.ptpIngressCorrectionFractionalNanosecondTimestampeEnable

                        Default = 0x0

                        1 = PTP Ingress CRC append enable
                        

                 <B>Notes:</B>
                        Correction fractional-nanoseconds timestamp enable (default: 0)
                        Set to 1 to allow the fractional-nanoseconds count of the timestamp to be carried by the LSB 16-bit of the original Correction field (See pif_ptp_ing_correct_act_i=3). Set to 0 to ignore the fractional-nanoseconds count during update of the Correction field.  */
      unsigned int   ptpIngressCorrectionFractionalNanosecondTimestampeEnable : 1;    /* 03.E61B.5  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress CRC append enable
                          */
                    /*! \brief 03.E61B.4 R/W PTP Ingress Correction Clear Timestamp Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u27.bits_27.ptpIngressCorrectionClearTimestampEnable

                        Default = 0x1

                        1 = PTP Ingress CRC append enable
                        

                 <B>Notes:</B>
                        Correction clear timestamp enable (default: 1)
                        Set to 1 to allow the timestamp field to be cleared to 0 by the corresponding Correction field action (See pif_ptp_ing_correct_act_i). Set to 0 to keep the timestamp field determined by the corresponding timestamp action (See pif_ptp_ing_ts_act_i)  */
      unsigned int   ptpIngressCorrectionClearTimestampEnable : 1;    /* 03.E61B.4  R/W      Default = 0x1 */
                     /* 1 = PTP Ingress CRC append enable
                          */
                    /*! \brief 03.E61B.3 R/W PTP Ingress CRC Append Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u27.bits_27.ptpIngressCrcAppendEnable

                        Default = 0x0

                        1 = PTP Ingress CRC append enable
                        

                 <B>Notes:</B>
                        Ethernet FCS appending enable (default: 0)
                        Set to 1 to append FCS into Ethernet frame.
                        Set to 0 to have no FCS at the end of frame.  */
      unsigned int   ptpIngressCrcAppendEnable : 1;    /* 03.E61B.3  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress CRC append enable
                          */
                    /*! \brief 03.E61B.2 R/W PTP Ingress UDP Append Format
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u27.bits_27.ptpIngressUdpAppendFormat

                        Default = 0x0

                        1 = PTP Ingress UDP append format
                        

                 <B>Notes:</B>
                        UDP packet appending format (default: 0)
                        This applies only for IEEE 1588v1 or NTP/SNTP packets. Set to 1 to replace the last 16-bit of appended timestamp (fractional nanoseconds) with a 16-bit word to compensate for the change of UDP checksum due to the appended timestamp. This allows timestamp removal of any packet length without the need of disabling the UDP checksum (setting to all-zeroes). See ptp_pif_egr_pkt_remove_err_o for more information. Set to 0 to append 96-bit timestamp without UDP checksum compensation.
                        There is no need for IEEE 1588v2 because the packet length shall be supported without error, and the 16-bit fractional nanoseconds are used to update the Correction field.  */
      unsigned int   ptpIngressUdpAppendFormat : 1;    /* 03.E61B.2  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress UDP append format
                          */
                    /*! \brief 03.E61B.1 R/W PTP Ingress UDP Append Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u27.bits_27.ptpIngressUdpAppendEnable

                        Default = 0x1

                        1 = PTP Ingress UDP append enable
                        

                 <B>Notes:</B>
                        UDP packet appending enable (default: 1)Set to1 to append timestamp/correction field (if enabled by the corresponding action) into UDP payload. Set to 0 to append those into L2 Ethernet payload  */
      unsigned int   ptpIngressUdpAppendEnable : 1;    /* 03.E61B.1  R/W      Default = 0x1 */
                     /* 1 = PTP Ingress UDP append enable
                          */
                    /*! \brief 03.E61B.0 R/W PTP Ingress UDP Checksum Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u27.bits_27.ptpIngressUdpChecksumEnable

                        Default = 0x1

                        1 = PTP Ingress UDP checksum enable
                        

                 <B>Notes:</B>
                        UDP checksum calculation enable (default: 1)
                        Set to 1 to recalculate the UDP checksum
                        Set to 0 to set the UDP checksum to all-zeroes  */
      unsigned int   ptpIngressUdpChecksumEnable : 1;    /* 03.E61B.0  R/W      Default = 0x1 */
                     /* 1 = PTP Ingress UDP checksum enable
                          */
    } bits_27;
    uint16_t word_27;
  } u27;
  /*! \brief Union for bit and word level access of word 28 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E61C.F R/W PTP Ingress Packet Pipeline Reset
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u28.bits_28.ptpIngressPacketPipelineReset

                        Default = 0x0

                        1 = PTP Ingress packet pipeline reset
                        

                 <B>Notes:</B>
                        PTP packet pipeline reset (default:0)
                        Set to 1 to reset PTP packet pipeline  */
      unsigned int   ptpIngressPacketPipelineReset : 1;    /* 03.E61C.F  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress packet pipeline reset
                          */
                    /*! \brief 03.E61C.E R/W PTP Ingress Packet Ready FIFO Reset
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u28.bits_28.ptpIngressPacketReadyFifoReset

                        Default = 0x0

                        1 = PTP Ingress packet ready FIFO reset
                        

                 <B>Notes:</B>
                        PTP packet ready FIFO reset (default:0)
                        Set to 1 to reset PTP packet ready FIFO  */
      unsigned int   ptpIngressPacketReadyFifoReset : 1;    /* 03.E61C.E  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress packet ready FIFO reset
                          */
      unsigned int   reserved0 : 14;
    } bits_28;
    uint16_t word_28;
  } u28;
  /*! \brief Union for bit and word level access of word 29 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 12;
                    /*! \brief 03.E61D.3:0 R/W PTP Ingress Packet Pipeline Threshold [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u29.bits_29.ptpIngressPacketPipelineThreshold

                        Default = 0x5

                        1 = PTP Ingress UDP append enable
                        

                 <B>Notes:</B>
                        PTP packet pipeline threshold (default: 0x5)
                        This is used in 1G or 100M mode to regulate packet flow. This has no effect in 10G mode.  */
      unsigned int   ptpIngressPacketPipelineThreshold : 4;    /* 03.E61D.3:0  R/W      Default = 0x5 */
                     /* 1 = PTP Ingress UDP append enable
                          */
    } bits_29;
    uint16_t word_29;
  } u29;
  /*! \brief Union for bit and word level access of word 30 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E61E.F R/W PTP Ingress Packet Buffer Reset
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u30.bits_30.ptpIngressPacketBufferReset

                        Default = 0x0

                        1 = PTP Ingress packet buffer reset
                        

                 <B>Notes:</B>
                        PTP packet buffer reset (default: 0)
                        Set to 1 to reset PTP packet extraction buffer and timestamp
                          */
      unsigned int   ptpIngressPacketBufferReset : 1;    /* 03.E61E.F  R/W      Default = 0x0 */
                     /* 1 = PTP Ingress packet buffer reset
                          */
      unsigned int   reserved0 : 14;
                    /*! \brief 03.E61E.0 R/W PTP Ingress Packet Buffer Read Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u30.bits_30.ptpIngressPacketBufferReadEnable

                        Default = 0x0

                         1 = PTP Ingress packet buffer read enable
                        

                 <B>Notes:</B>
                        PTP packet buffer read (default: 0)
                        Toggle 0->1->0 to read the next packet data out of extraction FIFO
                          */
      unsigned int   ptpIngressPacketBufferReadEnable : 1;    /* 03.E61E.0  R/W      Default = 0x0 */
                     /*  1 = PTP Ingress packet buffer read enable
                          */
    } bits_30;
    uint16_t word_30;
  } u30;
  /*! \brief Union for bit and word level access of word 31 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.E61F.1 R/W PTP Ingress Packet Pause
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u31.bits_31.ptpIngressPacketPause

                        Default = 0x0

                         PTP Ingress packet pause
                        

                 <B>Notes:</B>
                        PTP packet & timestamp extraction pause (default: 0)
                        Set to 1 to pause the extraction of packet and timestamp into the corresponding buffers. Set to 0 to resume the extraction.  */
      unsigned int   ptpIngressPacketPause : 1;    /* 03.E61F.1  R/W      Default = 0x0 */
                     /*  PTP Ingress packet pause
                          */
                    /*! \brief 03.E61F.0 R/W PTP Ingress Packet Size Limit
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u31.bits_31.ptpIngressPacketSizeLimit

                        Default = 0x0

                         PTP Ingress packet size limit
                        

                 <B>Notes:</B>
                        PTP packet size limit (default: 0)
                        Set to 1 to limit PTP packet to 128-byte to ensure packet buffer is enough to fit up to 4 packets  */
      unsigned int   ptpIngressPacketSizeLimit : 1;    /* 03.E61F.0  R/W      Default = 0x0 */
                     /*  PTP Ingress packet size limit
                          */
    } bits_31;
    uint16_t word_31;
  } u31;
  /*! \brief Union for bit and word level access of word 32 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.E620.0 R/W PTP Ingress Packet Time Stamp Read Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u32.bits_32.ptpIngressPacketTimeStampReadEnable

                        Default = 0x0

                         1 = PTP Ingress packet time stamp reset enable
                        

                 <B>Notes:</B>
                        PTP packet timestamp read (default: 0)
                        Toggle 0->1->0 to read the next word of corresponding timestamp of the extracted packet  */
      unsigned int   ptpIngressPacketTimeStampReadEnable : 1;    /* 03.E620.0  R/W      Default = 0x0 */
                     /*  1 = PTP Ingress packet time stamp reset enable
                          */
    } bits_32;
    uint16_t word_32;
  } u32;
  /*! \brief Union for bit and word level access of word 33 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.E621.B:8 R/W PTP Ingress 1588 Version 1 Time Stamp Action [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u33.bits_33.ptpIngress_1588Version_1TimeStampAction

                        Default = 0x0

                        PTP ingress 1588 version 1 time stamp action
                        

                 <B>Notes:</B>
                        IEEE 1588v1 timestamp action (0=None, 1=Overwrite, 2=Append, 3=Remove, default: 0).
                        Bits [1:0]: Sync messages
                        Bits [3:2]: All other event messages  */
      unsigned int   ptpIngress_1588Version_1TimeStampAction : 4;    /* 03.E621.B:8  R/W      Default = 0x0 */
                     /* PTP ingress 1588 version 1 time stamp action
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.E621.5:0 R/W PTP Ingress 1588 Version 1 Packet Action [5:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u33.bits_33.ptpIngress_1588Version_1PacketAction

                        Default = 0x00

                        PTP ingress 1588 version 1 packet action
                        

                 <B>Notes:</B>
                        IEEE 1588v1 packet action (0=None, 1=Capture, 2=reserved, 3=Capture & forward, default: 0). 
                        Bits [1:0]: Sync message
                        Bits [3:2]: All other event messages
                        Bits [5:4]: General messages  */
      unsigned int   ptpIngress_1588Version_1PacketAction : 6;    /* 03.E621.5:0  R/W      Default = 0x00 */
                     /* PTP ingress 1588 version 1 packet action
                          */
    } bits_33;
    uint16_t word_33;
  } u33;
  /*! \brief Union for bit and word level access of word 34 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E622.F:0 R/W PTP Ingress Stacked VLAN ID [F:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u34.bits_34.ptpIngressStackedVlanID

                        Default = 0x88A8

                        User-defined Tag Protocol Identifier (TPID) for stacked VLAN
                        

                 <B>Notes:</B>
                        User-defined Tag Protocol Identifier (TPID) for stacked VLAN (default: 0x88A8 for 802.1ad). For Q-in-Q, it can be 0x9100 or other user-defined values. In addition, 0x8100 will always be recognized as valid TPID.  */
      unsigned int   ptpIngressStackedVlanID : 16;    /* 03.E622.F:0  R/W      Default = 0x88A8 */
                     /* User-defined Tag Protocol Identifier (TPID) for stacked VLAN
                          */
    } bits_34;
    uint16_t word_34;
  } u34;
  /*! \brief Union for bit and word level access of word 35 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 03.E623.E:0 R/W PTP Ingress Correction Action [E:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u35.bits_35.ptpIngressCorrectionAction

                        Default = 0x0000

                        PTP Ingress correct action
                        

                 <B>Notes:</B>
                        IEEE 1588v2 correction field action (default:0)
                        0: No change
                        1: Correction + TS - TS(Append) + Offset 
                        2: Correction + Offset
                        3: TS - Timestamp + Offset 
                            (Timestamp field will be set to 0 if enabled.      See pif_ptp_egr_correct_clr_ts_en_i)
                        4: Correction + TS + Offset
                        5: Correction - TS + Offset
                        6 to 7: Reserved
                        Bits [2:0]: Sync messages
                        Bits [5:3]: Delay_Req message
                        Bits [8:6]: Pdelay_Req message
                        Bits [11:9]: Pdelay_Resp message
                        Bits [14:12]: User-defined message  */
      unsigned int   ptpIngressCorrectionAction : 15;    /* 03.E623.E:0  R/W      Default = 0x0000 */
                     /* PTP Ingress correct action
                          */
    } bits_35;
    uint16_t word_35;
  } u35;
  /*! \brief Union for bit and word level access of word 36 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E624.9:0 R/W PTP Ingress Time Stamp Action [9:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u36.bits_36.ptpIngressTimeStampAction

                        Default = 0x000

                        PTP Ingress packet action
                        

                 <B>Notes:</B>
                        IEEE 1588v2 timestamp action (0=None, 1=Overwrite, 2=Append, 3=Remove, default: 0).
                        Bits [1:0]: Sync messages
                        Bits [3:2]: Delay_Req message
                        Bits [5:4]: Pdelay_Req message
                        Bits [7:6]: Pdelay_Resp message
                        Bits [9:8]: User-defined message  */
      unsigned int   ptpIngressTimeStampAction : 10;    /* 03.E624.9:0  R/W      Default = 0x000 */
                     /* PTP Ingress packet action
                          */
    } bits_36;
    uint16_t word_36;
  } u36;
  /*! \brief Union for bit and word level access of word 37 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 12;
                    /*! \brief 03.E625.3:0 R/W PTP Ingress 1588 Version 2 Message Type [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u37.bits_37.ptpIngress_1588Version_2MessageType

                        Default = 0xF

                        PTP Ingress 1588 version 2 message type
                        

                 <B>Notes:</B>
                        IEEE 1588v2 User-defined Message Type
                        Bit pattern to compare against the messageType field after applying the bit mask (default:0xF)  */
      unsigned int   ptpIngress_1588Version_2MessageType : 4;    /* 03.E625.3:0  R/W      Default = 0xF */
                     /* PTP Ingress 1588 version 2 message type
                          */
    } bits_37;
    uint16_t word_37;
  } u37;
  /*! \brief Union for bit and word level access of word 38 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 12;
                    /*! \brief 03.E626.3:0 R/W PTP Ingress 1588 Version 2 Message Mask [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u38.bits_38.ptpIngress_1588Version_2MessageMask

                        Default = 0xF

                        PTP Ingress 1588 version 2 message mask
                        

                 <B>Notes:</B>
                        IEEE 1588v2 User-defined Message Mask
                        Bit mask to compare against the messageType field (for each bit, 1=compare, 0=ignore, default: 0xF)  */
      unsigned int   ptpIngress_1588Version_2MessageMask : 4;    /* 03.E626.3:0  R/W      Default = 0xF */
                     /* PTP Ingress 1588 version 2 message mask
                          */
    } bits_38;
    uint16_t word_38;
  } u38;
  /*! \brief Union for bit and word level access of word 39 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved0 : 12;
                    /*! \brief 03.E627.3:0 R/W PTP Ingress Packet IFG Threshold [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u39.bits_39.ptpIngressPacketIfgThreshold

                        Default = 0x0

                        PTP Ingress packet IFG threshold
                        

                 <B>Notes:</B>
                        PTP packet IFG threshold (default: 0x0)
                        This is used in 1G or 100M mode to insert extra idle during IFG. This has no effect in 10G mode.  */
      unsigned int   ptpIngressPacketIfgThreshold : 4;    /* 03.E627.3:0  R/W      Default = 0x0 */
                     /* PTP Ingress packet IFG threshold
                          */
    } bits_39;
    uint16_t word_39;
  } u39;
  /*! \brief Union for bit and word level access of word 40 of PCS PTP Ingress Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.E628.F:8 R/W PTP Ingress RX MAC FIFO base [7:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u40.bits_40.ptpIngressRxMacFifoBase

                        Default = 0x0A

                        PTP Ingress RX MAC FIFO Base Value
                        

                 <B>Notes:</B>
                        When = 0, the ingress Gap FIFO is bypassed.  */
      unsigned int   ptpIngressRxMacFifoBase : 8;    /* 03.E628.F:8  R/W      Default = 0x0A */
                     /* PTP Ingress RX MAC FIFO Base Value
                          */
                    /*! \brief 03.E628.7:6 R/W PTP Ingress RX MAC FIFO Correction [1:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u40.bits_40.ptpIngressRxMacFifoCorrection

                        Default = 0x3

                        PTP Ingress RX MAC FIFO Correction Amount
                        

                 <B>Notes:</B>
                        Compensates for the additional latency incurred if the MAC RX FIFO fill beyond the "base" (bits F:8) value. A value of 1 corresponds to 1ns, 2 -> 2n, 3 -> 3n, and 4 -> 4ns.  */
      unsigned int   ptpIngressRxMacFifoCorrection : 2;    /* 03.E628.7:6  R/W      Default = 0x3 */
                     /* PTP Ingress RX MAC FIFO Correction Amount
                          */
                    /*! \brief 03.E628.5 R/W PTP Ingress RX MAC FIFO Correction Enable
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u40.bits_40.ptpIngressRxMacFifoCorrectionEnable

                        Default = 0x0

                        PTP Ingress RX MAC FIFO Correction Enable
                        

                 <B>Notes:</B>
                        Enables the MAC RX FIFO latency compensation  */
      unsigned int   ptpIngressRxMacFifoCorrectionEnable : 1;    /* 03.E628.5  R/W      Default = 0x0 */
                     /* PTP Ingress RX MAC FIFO Correction Enable
                          */
                    /*! \brief 03.E628.4 R/W PTP Ingress Gap FIFO Bypass
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u40.bits_40.ptpIngressGapFifoBypass

                        Default = 0x1

                        PTP Ingress Gap FIFO bypass
                        

                 <B>Notes:</B>
                        When = 0, the ingress Gap FIFO is bypassed.  */
      unsigned int   ptpIngressGapFifoBypass : 1;    /* 03.E628.4  R/W      Default = 0x1 */
                     /* PTP Ingress Gap FIFO bypass
                          */
                    /*! \brief 03.E628.3:0 R/W PTP Ingress Packet Ready Threshold [3:0]
                        AQ_PcsPtpIngressVendorProvisioning_HHD.u40.bits_40.ptpIngressPacketReadyThreshold

                        Default = 0x2

                        PTP Ingress packet ready threshold
                        

                 <B>Notes:</B>
                        PTP packet Ready threshold (default: 0x2)
                        This is used in 1G or 100M mode to deassert ready when the pipeline FIFO is almost full. This has no effect in 10G mode.  */
      unsigned int   ptpIngressPacketReadyThreshold : 4;    /* 03.E628.3:0  R/W      Default = 0x2 */
                     /* PTP Ingress packet ready threshold
                          */
    } bits_40;
    uint16_t word_40;
  } u40;
} AQ_PcsPtpIngressVendorProvisioning_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor State: 03.E800 */
/*                  PCS Receive Vendor State: 03.E800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 03.E800.0 RO PCS Rx Current Value of Auxilliary Bit
                        AQ_PcsReceiveVendorState_HHD.u0.bits_0.pcsRxCurrentValueOfAuxilliaryBit

                        

                        The current value of the PCS Rx auxilliary bit
                        

                 <B>Notes:</B>
                        This value has a maskable interrupt associated with it in 3.EC00.0.  */
      unsigned int   pcsRxCurrentValueOfAuxilliaryBit : 1;    /* 03.E800.0  RO       */
                     /* The current value of the PCS Rx auxilliary bit
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Reserved Vendor State: 03.E808 */
/*                  PCS Receive Reserved Vendor State: 03.E808 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Reserved Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E808.F:0 RO Average LDPC Iteration Count [F:0]
                        AQ_PcsReceiveReservedVendorState_HHD.u0.bits_0.averageLdpcIterationCount

                        

                        Average Ldpc iteration for 10G, 5G, or 2.5G updated every few milliseconds in 4.12 fixed point format.
                        

                 <B>Notes:</B>
                        To obtain floating point value of LDPC iteration, divide the value in this register by 4096. For instance 0x1000 corrsponds to Average LDPC of 1.0.  */
      unsigned int   averageLdpcIterationCount : 16;    /* 03.E808.F:0  RO       */
                     /* Average Ldpc iteration for 10G, 5G, or 2.5G updated every few milliseconds in 4.12 fixed point format.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveReservedVendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor CRC-8 Error Counter: 03.E810 */
/*                  PCS Receive Vendor CRC-8 Error Counter: 03.E810 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor CRC-8 Error Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E810.F:0 SCTL CRC-8 Error Counter LSW [F:0]
                        AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD.u0.bits_0.crc_8ErrorCounterLSW

                        Default = 0x0000

                        Lower 16 bits of CRC-8 error counter
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of CRC-8 errors (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   crc_8ErrorCounterLSW : 16;    /* 03.E810.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of CRC-8 error counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor CRC-8 Error Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E811.5:0 SCTM CRC-8 Error Counter MSW [15:10]
                        AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD.u1.bits_1.crc_8ErrorCounterMSW

                        Default = 0x00

                        Upper 6 bits of CRC-8 error counter
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of CRC-8 errors (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   crc_8ErrorCounterMSW : 6;    /* 03.E811.5:0  SCTM      Default = 0x00 */
                     /* Upper 6 bits of CRC-8 error counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCrc_8ErrorCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor FCS No Error Frame Counter: 03.E812 */
/*                  PCS Receive Vendor FCS No Error Frame Counter: 03.E812 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor FCS No Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E812.F:0 SCTL 10GBASE-T Good Frame Counter LSW [F:0]
                        AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD.u0.bits_0._10gbase_tGoodFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterLSW : 16;    /* 03.E812.F:0  SCTL      Default = 0x0000 */
                     /* 10GBASE-T Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor FCS No Error Frame Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E813.9:0 SCTM 10GBASE-T Good Frame Counter MSW [19:10]
                        AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD.u1.bits_1._10gbase_tGoodFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterMSW : 10;    /* 03.E813.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorFcsNoErrorFrameCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor FCS Error Frame Counter: 03.E814 */
/*                  PCS Receive Vendor FCS Error Frame Counter: 03.E814 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor FCS Error Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E814.F:0 SCTL 10GBASE-T Error Frame Counter LSW [F:0]
                        AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD.u0.bits_0._10gbase_tErrorFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterLSW : 16;    /* 03.E814.F:0  SCTL      Default = 0x0000 */
                     /* 10GBASE-T Bad Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor FCS Error Frame Counter */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E815.9:0 SCTM 10GBASE-T Error Frame Counter MSW [19:10]
                        AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD.u1.bits_1._10gbase_tErrorFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterMSW : 10;    /* 03.E815.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Bad Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorFcsErrorFrameCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Uncorrected Frame Counter: 03.E820 */
/*                  PCS Receive Vendor Uncorrected Frame Counter: 03.E820 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Uncorrected Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E820.F:0 SCTL Uncorrected Frame Counter LSW [F:0]
                        AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD.u0.bits_0.uncorrectedFrameCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC uncorrected frames which the decoder abandoned.
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of uncorrected frames.  */
      unsigned int   uncorrectedFrameCounterLSW : 16;    /* 03.E820.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC uncorrected frames which the decoder abandoned.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Uncorrected Frame Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E821.F:0 SCTM Uncorrected Frame Counter MSW [1F:10]
                        AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD.u1.bits_1.uncorrectedFrameCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC uncorrected frames which the decoder abandoned
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of uncorrected frames.  */
      unsigned int   uncorrectedFrameCounterMSW : 16;    /* 03.E821.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC uncorrected frames which the decoder abandoned
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorUncorrectedFrameCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 1 Iteration Counter: 03.E840 */
/*                  PCS Receive Vendor Corrected Frame 1 Iteration Counter: 03.E840 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 1 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E840.F:0 SCTL Corrected Frames 1 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD.u0.bits_0.correctedFrames_1IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 1 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 1 iteration.  */
      unsigned int   correctedFrames_1IterationCounterLSW : 16;    /* 03.E840.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 1 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 1 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E841.F:0 SCTM Corrected Frames 1 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD.u1.bits_1.correctedFrames_1IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 1 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 1 iteration.  */
      unsigned int   correctedFrames_1IterationCounterMSW : 16;    /* 03.E841.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 1 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 2 Iteration Counter: 03.E842 */
/*                  PCS Receive Vendor Corrected Frame 2 Iteration Counter: 03.E842 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 2 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E842.F:0 SCTL Corrected Frames 2 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD.u0.bits_0.correctedFrames_2IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 2 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 2 iteration.  */
      unsigned int   correctedFrames_2IterationCounterLSW : 16;    /* 03.E842.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 2 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 2 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E843.F:0 SCTM Corrected Frames 2 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD.u1.bits_1.correctedFrames_2IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 2 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 2 iteration.  */
      unsigned int   correctedFrames_2IterationCounterMSW : 16;    /* 03.E843.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 2 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 3 Iteration Counter: 03.E844 */
/*                  PCS Receive Vendor Corrected Frame 3 Iteration Counter: 03.E844 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 3 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E844.F:0 SCTL Corrected Frames 3 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD.u0.bits_0.correctedFrames_3IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 3 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 3 iteration.  */
      unsigned int   correctedFrames_3IterationCounterLSW : 16;    /* 03.E844.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 3 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 3 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E845.F:0 SCTM Corrected Frames 3 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD.u1.bits_1.correctedFrames_3IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 3 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 3 iteration.  */
      unsigned int   correctedFrames_3IterationCounterMSW : 16;    /* 03.E845.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 3 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 4 Iteration Counter: 03.E846 */
/*                  PCS Receive Vendor Corrected Frame 4 Iteration Counter: 03.E846 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 4 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E846.F:0 SCTL Corrected Frames 4 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD.u0.bits_0.correctedFrames_4IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 4 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 4 iteration.  */
      unsigned int   correctedFrames_4IterationCounterLSW : 16;    /* 03.E846.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 4 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 4 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E847.F:0 SCTM Corrected Frames 4 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD.u1.bits_1.correctedFrames_4IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 4 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 4 iteration.  */
      unsigned int   correctedFrames_4IterationCounterMSW : 16;    /* 03.E847.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 4 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 5 Iteration Counter: 03.E848 */
/*                  PCS Receive Vendor Corrected Frame 5 Iteration Counter: 03.E848 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 5 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E848.F:0 SCTL Corrected Frames 5 Iteration Counter LSW [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD.u0.bits_0.correctedFrames_5IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 5 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 5 iteration.  */
      unsigned int   correctedFrames_5IterationCounterLSW : 16;    /* 03.E848.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC corrected frames which converged in 5 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Corrected Frame 5 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E849.F:0 SCTM Corrected Frames 5 Iteration Counter MSW [1F:10]
                        AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD.u1.bits_1.correctedFrames_5IterationCounterMSW

                        Default = 0x0000

                        Upper 16 bits of LDPC corrected frames which converged in 5 iteration
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of corrected frames which converged in 5 iteration.  */
      unsigned int   correctedFrames_5IterationCounterMSW : 16;    /* 03.E849.F:0  SCTM      Default = 0x0000 */
                     /* Upper 16 bits of LDPC corrected frames which converged in 5 iteration
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 6 Iteration Counter: 03.E850 */
/*                  PCS Receive Vendor Corrected Frame 6 Iteration Counter: 03.E850 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 6 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E850.F:0 SCT Corrected Frames 6 Iteration Counter [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD.u0.bits_0.correctedFrames_6IterationCounter

                        Default = 0x0000

                        LDPC corrected frames which converged in 6 iteration
                        

                 <B>Notes:</B>
                        Clear on read. A saturating counter that counts the number of corrected frames which converged in 6 iteration.  */
      unsigned int   correctedFrames_6IterationCounter : 16;    /* 03.E850.F:0  SCT      Default = 0x0000 */
                     /* LDPC corrected frames which converged in 6 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 7 Iteration Counter: 03.E851 */
/*                  PCS Receive Vendor Corrected Frame 7 Iteration Counter: 03.E851 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 7 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E851.F:0 SCT Corrected Frames 7 Iteration Counter [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD.u0.bits_0.correctedFrames_7IterationCounter

                        Default = 0x0000

                        LDPC corrected frames which converged in 7 iteration
                        

                 <B>Notes:</B>
                        Clear on read. A saturating counter that counts the number of corrected frames which converged in 7 iteration.  */
      unsigned int   correctedFrames_7IterationCounter : 16;    /* 03.E851.F:0  SCT      Default = 0x0000 */
                     /* LDPC corrected frames which converged in 7 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Corrected Frame 8 Iteration Counter: 03.E852 */
/*                  PCS Receive Vendor Corrected Frame 8 Iteration Counter: 03.E852 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Corrected Frame 8 Iteration Counter */
  union
  {
    struct
    {
                    /*! \brief 03.E852.F:0 SCT Corrected Frames 8 Iteration Counter [F:0]
                        AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD.u0.bits_0.correctedFrames_8IterationCounter

                        Default = 0x0000

                        LDPC corrected frames which converged in 8 iteration
                        

                 <B>Notes:</B>
                        Clear on read. A saturating counter that counts the number of corrected frames which converged in 8 iteration.  */
      unsigned int   correctedFrames_8IterationCounter : 16;    /* 03.E852.F:0  SCT      Default = 0x0000 */
                     /* LDPC corrected frames which converged in 8 iteration
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive XFI0 Vendor State: 03.E860 */
/*                  PCS Receive XFI0 Vendor State: 03.E860 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E860.F:0 SCTL XFI0 Good Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi0VendorState_HHD.u0.bits_0.xfi0GoodFrameCounterLSW

                        Default = 0x0000

                        XFI0 Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterLSW : 16;    /* 03.E860.F:0  SCTL      Default = 0x0000 */
                     /* XFI0 Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E861.9:0 SCTM XFI0 Good Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi0VendorState_HHD.u1.bits_1.xfi0GoodFrameCounterMSW

                        Default = 0x000

                        XFI0 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterMSW : 10;    /* 03.E861.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E862.F:0 SCTL XFI0 Bad Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi0VendorState_HHD.u2.bits_2.xfi0BadFrameCounterLSW

                        Default = 0x0000

                        XFI0 Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterLSW : 16;    /* 03.E862.F:0  SCTL      Default = 0x0000 */
                     /* XFI0 Bad Frame Counter LSW
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E863.9:0 SCTM XFI0 Bad Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi0VendorState_HHD.u3.bits_3.xfi0BadFrameCounterMSW

                        Default = 0x000

                        XFI0 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterMSW : 10;    /* 03.E863.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Bad Frame Counter MSW
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E864.5:0 SCT XFI0 BER Counter [5:0]
                        AQ_PcsReceiveXfi0VendorState_HHD.u4.bits_4.xfi0BerCounter

                        Default = 0x00

                        XFI0 BER counter
                        

                 <B>Notes:</B>
                        10GBASE-R BER Counter[5:0] saturating clear on read  */
      unsigned int   xfi0BerCounter : 6;    /* 03.E864.5:0  SCT      Default = 0x00 */
                     /* XFI0 BER counter
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.E865.7:0 SCT XFI0 Errored Block Counter [7:0]
                        AQ_PcsReceiveXfi0VendorState_HHD.u5.bits_5.xfi0ErroredBlockCounter

                        Default = 0x00

                        XFI0 errored block counter
                        

                 <B>Notes:</B>
                        10GBASE-R Errored Block Counter[7:0] saturating clear on read  */
      unsigned int   xfi0ErroredBlockCounter : 8;    /* 03.E865.7:0  SCT      Default = 0x00 */
                     /* XFI0 errored block counter
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E866.F:0 SCT XFI0 Test Pattern Error Counter [F:0]
                        AQ_PcsReceiveXfi0VendorState_HHD.u6.bits_6.xfi0TestPatternErrorCounter

                        Default = 0x0000

                        XFI0 test pattern error counter
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Error Counter[15:0] saturating clear on read  */
      unsigned int   xfi0TestPatternErrorCounter : 16;    /* 03.E866.F:0  SCT      Default = 0x0000 */
                     /* XFI0 test pattern error counter
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsReceiveXfi0VendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive XFI1 Vendor State: 03.E870 */
/*                  PCS Receive XFI1 Vendor State: 03.E870 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E870.F:0 SCTL XFI1 Good Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi1VendorState_HHD.u0.bits_0.xfi1GoodFrameCounterLSW

                        Default = 0x0000

                        XFI1 Good Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterLSW : 16;    /* 03.E870.F:0  SCTL      Default = 0x0000 */
                     /* XFI1 Good Frame Counter LSW
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E871.9:0 SCTM XFI1 Good Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi1VendorState_HHD.u1.bits_1.xfi1GoodFrameCounterMSW

                        Default = 0x000

                        XFI1 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterMSW : 10;    /* 03.E871.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Good Frame Counter MSW
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E872.F:0 SCTL XFI1 Bad Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi1VendorState_HHD.u2.bits_2.xfi1BadFrameCounterLSW

                        Default = 0x0000

                        XFI1 Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterLSW : 16;    /* 03.E872.F:0  SCTL      Default = 0x0000 */
                     /* XFI1 Bad Frame Counter LSW
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 03.E873.9:0 SCTM XFI1 Bad Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi1VendorState_HHD.u3.bits_3.xfi1BadFrameCounterMSW

                        Default = 0x000

                        XFI1 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterMSW : 10;    /* 03.E873.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Bad Frame Counter MSW
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E874.5:0 SCT XFI1 BER Counter [5:0]
                        AQ_PcsReceiveXfi1VendorState_HHD.u4.bits_4.xfi1BerCounter

                        Default = 0x00

                        XFI1 BER counter
                        

                 <B>Notes:</B>
                        10GBASE-R BER Counter[5:0] saturating clear on read  */
      unsigned int   xfi1BerCounter : 6;    /* 03.E874.5:0  SCT      Default = 0x00 */
                     /* XFI1 BER counter
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.E875.7:0 SCT XFI1 Errored Block Counter [7:0]
                        AQ_PcsReceiveXfi1VendorState_HHD.u5.bits_5.xfi1ErroredBlockCounter

                        Default = 0x00

                        XFI1 errored block counter
                        

                 <B>Notes:</B>
                        10GBASE-R Errored Block Counter[7:0] saturating clear on read  */
      unsigned int   xfi1ErroredBlockCounter : 8;    /* 03.E875.7:0  SCT      Default = 0x00 */
                     /* XFI1 errored block counter
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E876.F:0 SCT XFI1 Test Pattern Error Counter [F:0]
                        AQ_PcsReceiveXfi1VendorState_HHD.u6.bits_6.xfi1TestPatternErrorCounter

                        Default = 0x0000

                        XFI1 test pattern error counter
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Error Counter[15:0] saturating clear on read  */
      unsigned int   xfi1TestPatternErrorCounter : 16;    /* 03.E876.F:0  SCT      Default = 0x0000 */
                     /* XFI1 test pattern error counter
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsReceiveXfi1VendorState_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Receive CRC Error Counter Register: 03.E8D0 */
/*                  PCS USX0 Receive CRC Error Counter Register: 03.E8D0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Receive CRC Error Counter Register */
  union
  {
    struct
    {
                    /*! \brief 03.E8D0.F:0 SCT USX0 Header CRC Error Counter [F:0]
                        AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD.u0.bits_0.usx0HeaderCrcErrorCounter

                        Default = 0x0000

                        Rx Header CRC error counter
                        

                 <B>Notes:</B>
                        This register is a 16-bit saturating clear on read counter for USXGMII Header CRC error  */
      unsigned int   usx0HeaderCrcErrorCounter : 16;    /* 03.E8D0.F:0  SCT      Default = 0x0000 */
                     /* Rx Header CRC error counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0ReceiveCrcErrorCounterRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Receive Packet Info Message-0: 03.E8D1 */
/*                  PCS USX0 Receive Packet Info Message-0: 03.E8D1 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Receive Packet Info Message-0 */
  union
  {
    struct
    {
                    /*! \brief 03.E8D1.F:0 RO USX0 Packet Information Message to be injected 15:0 [F:0]
                        AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD.u0.bits_0.usx0PacketInformationMessageToBeInjected_15_0

                        

                         Packet Information Message to be injected15:0
                        

                 <B>Notes:</B>
                        Rx Packet Information message bit's 15:0  */
      unsigned int   usx0PacketInformationMessageToBeInjected_15_0 : 16;    /* 03.E8D1.F:0  RO       */
                     /*  Packet Information Message to be injected15:0
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0ReceivePacketInfoMessage_0_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Receive Packet Info Message-1: 03.E8D2 */
/*                  PCS USX0 Receive Packet Info Message-1: 03.E8D2 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Receive Packet Info Message-1 */
  union
  {
    struct
    {
                    /*! \brief 03.E8D2.F:0 RO USX0 Packet Information Message to be injected 31:16 [1F:10]
                        AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD.u0.bits_0.usx0PacketInformationMessageToBeInjected_31_16

                        

                         Packet Information Message to be injected 31:16
                        

                 <B>Notes:</B>
                        Rx Packet Information message bit's 31:16  */
      unsigned int   usx0PacketInformationMessageToBeInjected_31_16 : 16;    /* 03.E8D2.F:0  RO       */
                     /*  Packet Information Message to be injected 31:16
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0ReceivePacketInfoMessage_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Receive Packet Info Message-2: 03.E8D3 */
/*                  PCS USX0 Receive Packet Info Message-2: 03.E8D3 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Receive Packet Info Message-2 */
  union
  {
    struct
    {
                    /*! \brief 03.E8D3.F:0 RO USX0 Packet Information Message to be injected 47:32 [2F:20]
                        AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD.u0.bits_0.usx0PacketInformationMessageToBeInjected_47_32

                        

                         Packet Information Message to be injected 47:32
                        

                 <B>Notes:</B>
                        Rx Packet Information message bit's 47:32  */
      unsigned int   usx0PacketInformationMessageToBeInjected_47_32 : 16;    /* 03.E8D3.F:0  RO       */
                     /*  Packet Information Message to be injected 47:32
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0ReceivePacketInfoMessage_2_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Unidata and SM status Register: 03.E8D4 */
/*                  PCS USX0 Unidata and SM status Register: 03.E8D4 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Unidata and SM status Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E8D4.5:4 RO USX0 Rx_Unidata Indication[1:0]
                        AQ_PcsUsx0UnidataAndSmStatusRegister_HHD.u0.bits_0.usx0RxUnidataIndication

                        

                        Rx_Unidata Indication 
                        (0=None, 1=Invalid,
                        2=Idle, 3=Config)
                        
  */
      unsigned int   usx0RxUnidataIndication : 2;    /* 03.E8D4.5:4  RO       */
                     /* Rx_Unidata Indication 
                        (0=None, 1=Invalid,
                        2=Idle, 3=Config)
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.E8D4.2:0 RO USX0 SAN State Machine current state[2:0]
                        AQ_PcsUsx0UnidataAndSmStatusRegister_HHD.u0.bits_0.usx0SanStateMachineCurrentState

                        

                        SAN State Machine current state
                        
  */
      unsigned int   usx0SanStateMachineCurrentState : 3;    /* 03.E8D4.2:0  RO       */
                     /* SAN State Machine current state
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0UnidataAndSmStatusRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Receive Status Register: 03.E8D5 */
/*                  PCS USX0 Receive Status Register: 03.E8D5 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Receive Status Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.E8D5.7:4 BLH USX0 Rx Rsvd Status[3:0]
                        AQ_PcsUsx0ReceiveStatusRegister_HHD.u0.bits_0.usx0RxRsvdStatus

                        

                        USX0 Rx Reserved Status
                        
  */
      unsigned int   usx0RxRsvdStatus : 4;    /* 03.E8D5.7:4  BLH       */
                     /* USX0 Rx Reserved Status
                          */
                    /*! \brief 03.E8D5.3:0 BLH USX0 XGMII to GMII conversion Status[3:0]
                        AQ_PcsUsx0ReceiveStatusRegister_HHD.u0.bits_0.usx0XgmiiToGmiiConversionStatus

                        

                        XGMII to GMII/MII Conversion Status
                        Bit 0: Detect Rx min IFG error
                        Bit 1: Detect Rx Signal Ordered_set
                        Bits 2-3: Reserved
                        
  */
      unsigned int   usx0XgmiiToGmiiConversionStatus : 4;    /* 03.E8D5.3:0  BLH       */
                     /* XGMII to GMII/MII Conversion Status
                        Bit 0: Detect Rx min IFG error
                        Bit 1: Detect Rx Signal Ordered_set
                        Bits 2-3: Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0ReceiveStatusRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX0 Link Partner Adv Register: 03.E8D6 */
/*                  PCS USX0 Link Partner Adv Register: 03.E8D6 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX0 Link Partner Adv Register */
  union
  {
    struct
    {
                    /*! \brief 03.E8D6.F RO USX0 Link Partner Advertisement Status
                        AQ_PcsUsx0LinkPartnerAdvRegister_HHD.u0.bits_0.usx0LinkPartnerAdvertisementStatus

                        

                        USX0 Link Partner advertisement status.
                        0 = Link down
                        1 = Link up
                        
  */
      unsigned int   usx0LinkPartnerAdvertisementStatus : 1;    /* 03.E8D6.F  RO       */
                     /* USX0 Link Partner advertisement status.
                        0 = Link down
                        1 = Link up
                          */
                    /*! \brief 03.E8D6.E:D RO Reserved USX0 Link Partner Advertisement 0 [1:0]
                        AQ_PcsUsx0LinkPartnerAdvRegister_HHD.u0.bits_0.reservedUsx0LinkPartnerAdvertisement_0

                        

                        Reserved for future use.
                        
  */
      unsigned int   reservedUsx0LinkPartnerAdvertisement_0 : 2;    /* 03.E8D6.E:D  RO       */
                     /* Reserved for future use.
                          */
                    /*! \brief 03.E8D6.C RO USX0 Link Partner Advertisement Duplex
                        AQ_PcsUsx0LinkPartnerAdvRegister_HHD.u0.bits_0.usx0LinkPartnerAdvertisementDuplex

                        

                        USX0 Link Partner advertisement duplex.
                        0 = Half duplex
                        1 = Full duplex
                        
  */
      unsigned int   usx0LinkPartnerAdvertisementDuplex : 1;    /* 03.E8D6.C  RO       */
                     /* USX0 Link Partner advertisement duplex.
                        0 = Half duplex
                        1 = Full duplex
                          */
                    /*! \brief 03.E8D6.B:9 RO USX0 Link Partner Advertisement Speed [2:0]
                        AQ_PcsUsx0LinkPartnerAdvRegister_HHD.u0.bits_0.usx0LinkPartnerAdvertisementSpeed

                        

                        USX0 Link Partner advertisement speed.
                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                        
  */
      unsigned int   usx0LinkPartnerAdvertisementSpeed : 3;    /* 03.E8D6.B:9  RO       */
                     /* USX0 Link Partner advertisement speed.
                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                          */
                    /*! \brief 03.E8D6.8 RO USX0 Link Partner Advertisement EEE Capability
                        AQ_PcsUsx0LinkPartnerAdvRegister_HHD.u0.bits_0.usx0LinkPartnerAdvertisementEeeCapability

                        

                        USX0 Link Partner advertisement EEE capability.
                        0 = Not supported
                        1 = Supported
                        
  */
      unsigned int   usx0LinkPartnerAdvertisementEeeCapability : 1;    /* 03.E8D6.8  RO       */
                     /* USX0 Link Partner advertisement EEE capability.
                        0 = Not supported
                        1 = Supported
                          */
                    /*! \brief 03.E8D6.7 RO USX0 Link Partner Advertisement EEE Clock Stop Capability
                        AQ_PcsUsx0LinkPartnerAdvRegister_HHD.u0.bits_0.usx0LinkPartnerAdvertisementEeeClockStopCapability

                        

                        USX0 Link Partner advertisement EEE Clock Stop capability.
                        0 = Not supported
                        1 = Supported
                        
  */
      unsigned int   usx0LinkPartnerAdvertisementEeeClockStopCapability : 1;    /* 03.E8D6.7  RO       */
                     /* USX0 Link Partner advertisement EEE Clock Stop capability.
                        0 = Not supported
                        1 = Supported
                          */
                    /*! \brief 03.E8D6.6:1 RO Reserved USX0 Link Partner Advertisement 1 [5:0]
                        AQ_PcsUsx0LinkPartnerAdvRegister_HHD.u0.bits_0.reservedUsx0LinkPartnerAdvertisement_1

                        

                        Reserved for future use.
                        
  */
      unsigned int   reservedUsx0LinkPartnerAdvertisement_1 : 6;    /* 03.E8D6.6:1  RO       */
                     /* Reserved for future use.
                          */
                    /*! \brief 03.E8D6.0 RO USX0 Link Partner Advertisement Mode
                        AQ_PcsUsx0LinkPartnerAdvRegister_HHD.u0.bits_0.usx0LinkPartnerAdvertisementMode

                        

                        USX0 Link Partner advertisement mode.
                        0 = SGMII
                        1 = USXGMII
                        
                        
  */
      unsigned int   usx0LinkPartnerAdvertisementMode : 1;    /* 03.E8D6.0  RO       */
                     /* USX0 Link Partner advertisement mode.
                        0 = SGMII
                        1 = USXGMII
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx0LinkPartnerAdvRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Receive CRC Error Counter Register: 03.E8E0 */
/*                  PCS USX1 Receive CRC Error Counter Register: 03.E8E0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Receive CRC Error Counter Register */
  union
  {
    struct
    {
                    /*! \brief 03.E8E0.F:0 SCT USX1 Header CRC Error Counter [F:0]
                        AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD.u0.bits_0.usx1HeaderCrcErrorCounter

                        Default = 0x0000

                        Rx Header CRC error counter
                        

                 <B>Notes:</B>
                        This register is a 16-bit saturating clear on read counter for USXGMII Header CRC error  */
      unsigned int   usx1HeaderCrcErrorCounter : 16;    /* 03.E8E0.F:0  SCT      Default = 0x0000 */
                     /* Rx Header CRC error counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1ReceiveCrcErrorCounterRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Receive Packet Info Message-0: 03.E8E1 */
/*                  PCS USX1 Receive Packet Info Message-0: 03.E8E1 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Receive Packet Info Message-0 */
  union
  {
    struct
    {
                    /*! \brief 03.E8E1.F:0 RO USX1 Packet Information Message to be injected 15:0 [F:0]
                        AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD.u0.bits_0.usx1PacketInformationMessageToBeInjected_15_0

                        

                         Packet Information Message to be injected15:0
                        

                 <B>Notes:</B>
                        Rx Packet Information message bit's 15:0  */
      unsigned int   usx1PacketInformationMessageToBeInjected_15_0 : 16;    /* 03.E8E1.F:0  RO       */
                     /*  Packet Information Message to be injected15:0
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1ReceivePacketInfoMessage_0_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Receive Packet Info Message-1: 03.E8E2 */
/*                  PCS USX1 Receive Packet Info Message-1: 03.E8E2 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Receive Packet Info Message-1 */
  union
  {
    struct
    {
                    /*! \brief 03.E8E2.F:0 RO USX1 Packet Information Message to be injected 31:16 [1F:10]
                        AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD.u0.bits_0.usx1PacketInformationMessageToBeInjected_31_16

                        

                         Packet Information Message to be injected 31:16
                        

                 <B>Notes:</B>
                        Rx Packet Information message bit's 31:16  */
      unsigned int   usx1PacketInformationMessageToBeInjected_31_16 : 16;    /* 03.E8E2.F:0  RO       */
                     /*  Packet Information Message to be injected 31:16
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1ReceivePacketInfoMessage_1_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Receive Packet Info Message-2: 03.E8E3 */
/*                  PCS USX1 Receive Packet Info Message-2: 03.E8E3 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Receive Packet Info Message-2 */
  union
  {
    struct
    {
                    /*! \brief 03.E8E3.F:0 RO USX1 Packet Information Message to be injected 47:32 [2F:20]
                        AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD.u0.bits_0.usx1PacketInformationMessageToBeInjected_47_32

                        

                         Packet Information Message to be injected 47:32
                        

                 <B>Notes:</B>
                        Rx Packet Information message bit's 47:32  */
      unsigned int   usx1PacketInformationMessageToBeInjected_47_32 : 16;    /* 03.E8E3.F:0  RO       */
                     /*  Packet Information Message to be injected 47:32
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1ReceivePacketInfoMessage_2_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Unidata and SM status Register: 03.E8E4 */
/*                  PCS USX1 Unidata and SM status Register: 03.E8E4 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Unidata and SM status Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 03.E8E4.5:4 RO USX1 Rx_Unidata Indication[1:0]
                        AQ_PcsUsx1UnidataAndSmStatusRegister_HHD.u0.bits_0.usx1RxUnidataIndication

                        

                        Rx_Unidata Indication 
                        (0=None, 1=Invalid,
                        2=Idle, 3=Config)
                        
  */
      unsigned int   usx1RxUnidataIndication : 2;    /* 03.E8E4.5:4  RO       */
                     /* Rx_Unidata Indication 
                        (0=None, 1=Invalid,
                        2=Idle, 3=Config)
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.E8E4.2:0 RO USX1 SAN State Machine current state[2:0]
                        AQ_PcsUsx1UnidataAndSmStatusRegister_HHD.u0.bits_0.usx1SanStateMachineCurrentState

                        

                        SAN State Machine current state
                        
  */
      unsigned int   usx1SanStateMachineCurrentState : 3;    /* 03.E8E4.2:0  RO       */
                     /* SAN State Machine current state
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1UnidataAndSmStatusRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Receive Status Register: 03.E8E5 */
/*                  PCS USX1 Receive Status Register: 03.E8E5 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Receive Status Register */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.E8E5.7:4 BLH USX1 Rx Rsvd Status[3:0]
                        AQ_PcsUsx1ReceiveStatusRegister_HHD.u0.bits_0.usx1RxRsvdStatus

                        

                        USX1 Rx Reserved Status
                        
  */
      unsigned int   usx1RxRsvdStatus : 4;    /* 03.E8E5.7:4  BLH       */
                     /* USX1 Rx Reserved Status
                          */
                    /*! \brief 03.E8E5.3:0 BLH USX1 XGMII to GMII conversion Status[3:0]
                        AQ_PcsUsx1ReceiveStatusRegister_HHD.u0.bits_0.usx1XgmiiToGmiiConversionStatus

                        

                        XGMII to GMII/MII Conversion Status
                        Bit 0: Detect Rx min IFG error
                        Bit 1: Detect Rx Signal Ordered_set
                        Bits 2-3: Reserved
                        
  */
      unsigned int   usx1XgmiiToGmiiConversionStatus : 4;    /* 03.E8E5.3:0  BLH       */
                     /* XGMII to GMII/MII Conversion Status
                        Bit 0: Detect Rx min IFG error
                        Bit 1: Detect Rx Signal Ordered_set
                        Bits 2-3: Reserved
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1ReceiveStatusRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS USX1 Link Partner Adv Register: 03.E8E6 */
/*                  PCS USX1 Link Partner Adv Register: 03.E8E6 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS USX1 Link Partner Adv Register */
  union
  {
    struct
    {
                    /*! \brief 03.E8E6.F RO USX1 Link Partner Advertisement Status
                        AQ_PcsUsx1LinkPartnerAdvRegister_HHD.u0.bits_0.usx1LinkPartnerAdvertisementStatus

                        

                        USX1 Link Partner advertisement status.
                        0 = Link down
                        1 = Link up
                        
  */
      unsigned int   usx1LinkPartnerAdvertisementStatus : 1;    /* 03.E8E6.F  RO       */
                     /* USX1 Link Partner advertisement status.
                        0 = Link down
                        1 = Link up
                          */
                    /*! \brief 03.E8E6.E:D RO Reserved USX1 Link Partner Advertisement 0 [1:0]
                        AQ_PcsUsx1LinkPartnerAdvRegister_HHD.u0.bits_0.reservedUsx1LinkPartnerAdvertisement_0

                        

                        Reserved for future use.
                        
  */
      unsigned int   reservedUsx1LinkPartnerAdvertisement_0 : 2;    /* 03.E8E6.E:D  RO       */
                     /* Reserved for future use.
                          */
                    /*! \brief 03.E8E6.C RO USX1 Link Partner Advertisement Duplex
                        AQ_PcsUsx1LinkPartnerAdvRegister_HHD.u0.bits_0.usx1LinkPartnerAdvertisementDuplex

                        

                        USX1 Link Partner advertisement duplex.
                        0 = Half duplex
                        1 = Full duplex
                        
  */
      unsigned int   usx1LinkPartnerAdvertisementDuplex : 1;    /* 03.E8E6.C  RO       */
                     /* USX1 Link Partner advertisement duplex.
                        0 = Half duplex
                        1 = Full duplex
                          */
                    /*! \brief 03.E8E6.B:9 RO USX1 Link Partner Advertisement Speed [2:0]
                        AQ_PcsUsx1LinkPartnerAdvRegister_HHD.u0.bits_0.usx1LinkPartnerAdvertisementSpeed

                        

                        USX1 Link Partner advertisement speed.
                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                        
  */
      unsigned int   usx1LinkPartnerAdvertisementSpeed : 3;    /* 03.E8E6.B:9  RO       */
                     /* USX1 Link Partner advertisement speed.
                        0 = 10M
                        1 = 100M
                        2 = 1G
                        3 = 10G
                        4 = 2.5G
                        5 = 5G
                          */
                    /*! \brief 03.E8E6.8 RO USX1 Link Partner Advertisement EEE Capability
                        AQ_PcsUsx1LinkPartnerAdvRegister_HHD.u0.bits_0.usx1LinkPartnerAdvertisementEeeCapability

                        

                        USX1 Link Partner advertisement EEE capability.
                        0 = Not supported
                        1 = Supported
                        
  */
      unsigned int   usx1LinkPartnerAdvertisementEeeCapability : 1;    /* 03.E8E6.8  RO       */
                     /* USX1 Link Partner advertisement EEE capability.
                        0 = Not supported
                        1 = Supported
                          */
                    /*! \brief 03.E8E6.7 RO USX1 Link Partner Advertisement EEE Clock Stop Capability
                        AQ_PcsUsx1LinkPartnerAdvRegister_HHD.u0.bits_0.usx1LinkPartnerAdvertisementEeeClockStopCapability

                        

                        USX1 Link Partner advertisement EEE Clock Stop capability.
                        0 = Not supported
                        1 = Supported
                        
  */
      unsigned int   usx1LinkPartnerAdvertisementEeeClockStopCapability : 1;    /* 03.E8E6.7  RO       */
                     /* USX1 Link Partner advertisement EEE Clock Stop capability.
                        0 = Not supported
                        1 = Supported
                          */
                    /*! \brief 03.E8E6.6:1 RO Reserved USX1 Link Partner Advertisement 1 [5:0]
                        AQ_PcsUsx1LinkPartnerAdvRegister_HHD.u0.bits_0.reservedUsx1LinkPartnerAdvertisement_1

                        

                        Reserved for future use.
                        
  */
      unsigned int   reservedUsx1LinkPartnerAdvertisement_1 : 6;    /* 03.E8E6.6:1  RO       */
                     /* Reserved for future use.
                          */
                    /*! \brief 03.E8E6.0 RO USX1 Link Partner Advertisement Mode
                        AQ_PcsUsx1LinkPartnerAdvRegister_HHD.u0.bits_0.usx1LinkPartnerAdvertisementMode

                        

                        USX1 Link Partner advertisement mode.
                        0 = SGMII
                        1 = USXGMII
                        
                        
  */
      unsigned int   usx1LinkPartnerAdvertisementMode : 1;    /* 03.E8E6.0  RO       */
                     /* USX1 Link Partner advertisement mode.
                        0 = SGMII
                        1 = USXGMII
                        
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsUsx1LinkPartnerAdvRegister_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Alarms: 03.EC00 */
/*                  PCS Receive Vendor Alarms: 03.EC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.EC00.F LH CRC Error
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.crcError

                        

                        1 = Rx CRC Frame error
                        

                 <B>Notes:</B>
                        This bit is set when a CRC-8 error is detected on the receive PCS frame.  */
      unsigned int   crcError : 1;    /* 03.EC00.F  LH       */
                     /* 1 = Rx CRC Frame error
                          */
                    /*! \brief 03.EC00.E LH LDPC Decode Failure
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.ldpcDecodeFailure

                        

                        1 = LDPC decode failure
                        

                 <B>Notes:</B>
                        This bit is set when the LDPC decoder fails to decode an LDPC block.  */
      unsigned int   ldpcDecodeFailure : 1;    /* 03.EC00.E  LH       */
                     /* 1 = LDPC decode failure
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 03.EC00.B LH Local Fault Detect
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.localFaultDetect

                        

                        1 = RPL local fault detect
                        

                 <B>Notes:</B>
                        Local_Fault Interrupt  */
      unsigned int   localFaultDetect : 1;    /* 03.EC00.B  LH       */
                     /* 1 = RPL local fault detect
                          */
                    /*! \brief 03.EC00.A LH LOF Detect
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.lofDetect

                        

                        1 = RPL LOF detect
                        

                 <B>Notes:</B>
                        LOF Detection Interrupt  */
      unsigned int   lofDetect : 1;    /* 03.EC00.A  LH       */
                     /* 1 = RPL LOF detect
                          */
                    /*! \brief 03.EC00.9 LH 40G BIP Lock
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0._40gBipLock

                        

                        1 = RPL 40G BIP lock
                        

                 <B>Notes:</B>
                        Indicates the 40G BIP checker has achieved lock to the alignment marker  */
      unsigned int   _40gBipLock : 1;    /* 03.EC00.9  LH       */
                     /* 1 = RPL 40G BIP lock
                          */
                    /*! \brief 03.EC00.8 LH Invalid 65B Block
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.invalid_65bBlock

                        

                        1 = Invalid Rx 65B block received in PCS transmission frame
                        

                 <B>Notes:</B>
                        This bit is set when an invalid 65B block (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   invalid_65bBlock : 1;    /* 03.EC00.8  LH       */
                     /* 1 = Invalid Rx 65B block received in PCS transmission frame
                          */
                    /*! \brief 03.EC00.7 LL EEE Rx LPI Active Off
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.eeeRxLpiActiveOff

                        

                        1 = EEE Rx LPI Active Off
                        
  */
      unsigned int   eeeRxLpiActiveOff : 1;    /* 03.EC00.7  LL       */
                     /* 1 = EEE Rx LPI Active Off
                          */
                    /*! \brief 03.EC00.6 LH EEE Rx LPI Active On
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.eeeRxLpiActiveOn

                        

                        1 = EEE Rx LPI Active On
                        
  */
      unsigned int   eeeRxLpiActiveOn : 1;    /* 03.EC00.6  LH       */
                     /* 1 = EEE Rx LPI Active On
                          */
                    /*! \brief 03.EC00.5 LH LDPC Consecutive Errored Frame Exceeded
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.ldpcConsecutiveErroredFrameExceeded

                        

                        1 = Rx PCS LDPC consecutive errored frame threshold exceeded
                        
                        

                 <B>Notes:</B>
                        Indicates the consecutive LDPC errored frame has exceeded the threshold.
                          */
      unsigned int   ldpcConsecutiveErroredFrameExceeded : 1;    /* 03.EC00.5  LH       */
                     /* 1 = Rx PCS LDPC consecutive errored frame threshold exceeded
                        
                          */
                    /*! \brief 03.EC00.4 LH EEE Rx LPI Alert
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.eeeRxLpiAlert

                        

                        1 = Rx PCS received alert indication
                        
                        

                 <B>Notes:</B>
                        Indicate Rx PCS received alert indication  */
      unsigned int   eeeRxLpiAlert : 1;    /* 03.EC00.4  LH       */
                     /* 1 = Rx PCS received alert indication
                        
                          */
                    /*! \brief 03.EC00.3 LL EEE Rx LPI Received Latched Low
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.eeeRxLpiReceivedLatchedLow

                        

                        1 = Rx LPI has been detected
                        
                        

                 <B>Notes:</B>
                        Indicate LPI ordered-set is detected  */
      unsigned int   eeeRxLpiReceivedLatchedLow : 1;    /* 03.EC00.3  LL       */
                     /* 1 = Rx LPI has been detected
                        
                          */
                    /*! \brief 03.EC00.2 LH EEE Rx LPI Received Latched High
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.eeeRxLpiReceivedLatchedHigh

                        

                        1 = Rx LPI has been detected
                        
                        

                 <B>Notes:</B>
                        Indicate LPI ordered-set is detected  */
      unsigned int   eeeRxLpiReceivedLatchedHigh : 1;    /* 03.EC00.2  LH       */
                     /* 1 = Rx LPI has been detected
                        
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.EC00.0 LRF Change in Auxilliary Bit
                        AQ_PcsReceiveVendorAlarms_HHD.u0.bits_0.changeInAuxilliaryBit

                        

                        1 = Indicates a change in the value of the auxilliary bit
                        

                 <B>Notes:</B>
                        This bit is set when a change is detected in the auxilliary bit.  */
      unsigned int   changeInAuxilliaryBit : 1;    /* 03.EC00.0  LRF       */
                     /* 1 = Indicates a change in the value of the auxilliary bit
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.EC05.B LH XFI1 Invalid 66B Character Received
                        AQ_PcsReceiveVendorAlarms_HHD.u5.bits_5.xfi1Invalid_66bCharacterReceived

                        

                        1 = XFI1 Receive invalid 66B character received
                        

                 <B>Notes:</B>
                        Invalid 66B code error  */
      unsigned int   xfi1Invalid_66bCharacterReceived : 1;    /* 03.EC05.B  LH       */
                     /* 1 = XFI1 Receive invalid 66B character received
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.EC05.3 LH XFI0 Invalid 66B Character Received
                        AQ_PcsReceiveVendorAlarms_HHD.u5.bits_5.xfi0Invalid_66bCharacterReceived

                        

                        1 = XFI0 Receive invalid 66B character received
                        

                 <B>Notes:</B>
                        Invalid 66B code error  */
      unsigned int   xfi0Invalid_66bCharacterReceived : 1;    /* 03.EC05.3  LH       */
                     /* 1 = XFI0 Receive invalid 66B character received
                          */
      unsigned int   reserved2 : 3;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.EC06.7 LH XFI1 Receive Link Status Latch High
                        AQ_PcsReceiveVendorAlarms_HHD.u6.bits_6.xfi1ReceiveLinkStatusLatchHigh

                        

                        Status of the XFI1 receive link
                        

                 <B>Notes:</B>
                        This indicates the status of the XFI1 receive link.  */
      unsigned int   xfi1ReceiveLinkStatusLatchHigh : 1;    /* 03.EC06.7  LH       */
                     /* Status of the XFI1 receive link
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.EC06.5 LH XFI1 High BER Status
                        AQ_PcsReceiveVendorAlarms_HHD.u6.bits_6.xfi1HighBerStatus

                        

                        1 = XFI1 High BER condition
                        
  */
      unsigned int   xfi1HighBerStatus : 1;    /* 03.EC06.5  LH       */
                     /* 1 = XFI1 High BER condition
                          */
                    /*! \brief 03.EC06.4 LL XFI1 Block Lock Status
                        AQ_PcsReceiveVendorAlarms_HHD.u6.bits_6.xfi1BlockLockStatus

                        

                        1 = XFI1 Block Lock condition
                        
  */
      unsigned int   xfi1BlockLockStatus : 1;    /* 03.EC06.4  LL       */
                     /* 1 = XFI1 Block Lock condition
                          */
                    /*! \brief 03.EC06.3 LH XFI0 Receive Link Status Latch High
                        AQ_PcsReceiveVendorAlarms_HHD.u6.bits_6.xfi0ReceiveLinkStatusLatchHigh

                        

                        Status of the XFI0 receive link
                        

                 <B>Notes:</B>
                        This indicates the status of the XFI0 receive link.  */
      unsigned int   xfi0ReceiveLinkStatusLatchHigh : 1;    /* 03.EC06.3  LH       */
                     /* Status of the XFI0 receive link
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 03.EC06.1 LH XFI0 High BER Status
                        AQ_PcsReceiveVendorAlarms_HHD.u6.bits_6.xfi0HighBerStatus

                        

                        1 = XFI0 High BER condition
                        
  */
      unsigned int   xfi0HighBerStatus : 1;    /* 03.EC06.1  LH       */
                     /* 1 = XFI0 High BER condition
                          */
                    /*! \brief 03.EC06.0 LL XFI0 Block Lock Status
                        AQ_PcsReceiveVendorAlarms_HHD.u6.bits_6.xfi0BlockLockStatus

                        

                        1 = XFI0 Block Lock condition
                        
  */
      unsigned int   xfi0BlockLockStatus : 1;    /* 03.EC06.0  LL       */
                     /* 1 = XFI0 Block Lock condition
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Dummy union to fill space in the structure PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Dummy union to fill space in the structure PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.EC09.B LH PTP Ingress Packet Ready FIFO Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketReadyFifoError

                        

                        1 = PTP Ingress packet ready FIFO error
                        

                 <B>Notes:</B>
                        Asserted when PTP packet ready FIFO has detected FIFO error  */
      unsigned int   ptpIngressPacketReadyFifoError : 1;    /* 03.EC09.B  LH       */
                     /* 1 = PTP Ingress packet ready FIFO error
                          */
                    /*! \brief 03.EC09.A LH PTP Ingress Packet Ready FIFO Parity Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketReadyFifoParityError

                        

                        1 = PTP Ingress packet ready FIFO parity error
                        

                 <B>Notes:</B>
                        Asserted when PTP packet ready FIFO has detected parity error  */
      unsigned int   ptpIngressPacketReadyFifoParityError : 1;    /* 03.EC09.A  LH       */
                     /* 1 = PTP Ingress packet ready FIFO parity error
                          */
                    /*! \brief 03.EC09.9 LH PTP Ingress Packet Remove Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketRemoveError

                        

                        1 = PTP Ingress packet remove error
                        

                 <B>Notes:</B>
                        Asserted when the packet length is too long for the UDP checksum to be updated during removal of the timestamp appended at the end of packet. When this happens, the UDP checksum will be set to all-zeroes.  */
      unsigned int   ptpIngressPacketRemoveError : 1;    /* 03.EC09.9  LH       */
                     /* 1 = PTP Ingress packet remove error
                          */
                    /*! \brief 03.EC09.8 LH PTP Ingress Packet Received
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketReceived

                        

                        1 = PTP Ingress packet received
                        

                 <B>Notes:</B>
                        Asserted when a valid PTP packet has been received. This can be used as the valid signal for the received PTP packet information.  */
      unsigned int   ptpIngressPacketReceived : 1;    /* 03.EC09.8  LH       */
                     /* 1 = PTP Ingress packet received
                          */
                    /*! \brief 03.EC09.7 LH PTP Ingress Packet Pipeline FIFO Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketPipelineFifoError

                        

                        1 = PTP Ingress packet pipeline FIFO error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP packet buffer has detected parity error  */
      unsigned int   ptpIngressPacketPipelineFifoError : 1;    /* 03.EC09.7  LH       */
                     /* 1 = PTP Ingress packet pipeline FIFO error detected
                          */
                    /*! \brief 03.EC09.6 LH PTP Ingress Packet Pipeline Parity Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketPipelineParityError

                        

                        1 = PTP Ingress packet pipeline parity error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP timestamp buffer has detected parity error  */
      unsigned int   ptpIngressPacketPipelineParityError : 1;    /* 03.EC09.6  LH       */
                     /* 1 = PTP Ingress packet pipeline parity error detected
                          */
                    /*! \brief 03.EC09.5 LH PTP Ingress Time Stamp Buffer Parity Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressTimeStampBufferParityError

                        

                        1 = PTP Ingress time stamp buffer parity error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP packet pipeline has detected parity error  */
      unsigned int   ptpIngressTimeStampBufferParityError : 1;    /* 03.EC09.5  LH       */
                     /* 1 = PTP Ingress time stamp buffer parity error detected
                          */
                    /*! \brief 03.EC09.4 LH PTP Ingress Packet Buffer Parity Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketBufferParityError

                        

                        1 = PTP Ingress packet buffer parity error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP packet pipeline has detected FIFO error  */
      unsigned int   ptpIngressPacketBufferParityError : 1;    /* 03.EC09.4  LH       */
                     /* 1 = PTP Ingress packet buffer parity error detected
                          */
                    /*! \brief 03.EC09.3 LH PTP Ingress Packet Correction Field Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketCorrectionFieldError

                        

                        1 = PTP Ingress packet correction field error
                        

                 <B>Notes:</B>
                        Asserted when the packet length is too long for the Correction field to be updated due to the ingress timestamp appended at the end of packet. This shall not happen for IEEE1588v2 compliant packets. But when this happens, the Correction field will not be changed.  */
      unsigned int   ptpIngressPacketCorrectionFieldError : 1;    /* 03.EC09.3  LH       */
                     /* 1 = PTP Ingress packet correction field error
                          */
                    /*! \brief 03.EC09.2 LH PTP Ingress Packet Buffer Overflow Error
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketBufferOverflowError

                        

                        1 = PTP Ingress packet buffer overflow error detected
                        

                 <B>Notes:</B>
                        Asserted when PTP packet has not been captured because the buffer was full  */
      unsigned int   ptpIngressPacketBufferOverflowError : 1;    /* 03.EC09.2  LH       */
                     /* 1 = PTP Ingress packet buffer overflow error detected
                          */
                    /*! \brief 03.EC09.1 RO PTP Ingress Time Stamp Ready
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressTimeStampReady

                        

                        1 = PTP Ingress packet time stamp ready
                        

                 <B>Notes:</B>
                        Asserted when PTP packet timestamp has captured. It will be cleared when the timestamp buffer is empty
                          */
      unsigned int   ptpIngressTimeStampReady : 1;    /* 03.EC09.1  RO       */
                     /* 1 = PTP Ingress packet time stamp ready
                          */
                    /*! \brief 03.EC09.0 RO PTP Ingress Packet Ready
                        AQ_PcsReceiveVendorAlarms_HHD.u9.bits_9.ptpIngressPacketReady

                        

                        1 = PTP Ingress packet ready
                        

                 <B>Notes:</B>
                        Asserted when PTP packet has captured. It will be cleared when the buffer is empty  */
      unsigned int   ptpIngressPacketReady : 1;    /* 03.EC09.0  RO       */
                     /* 1 = PTP Ingress packet ready
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Dummy union to fill space in the structure PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Dummy union to fill space in the structure PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Dummy union to fill space in the structure PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 03.EC0D.E LH USX0 Rx Header CRC Error
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0RxHeaderCrcError

                        

                        Detect Rx Header CRC Error
                        
  */
      unsigned int   usx0RxHeaderCrcError : 1;    /* 03.EC0D.E  LH       */
                     /* Detect Rx Header CRC Error
                          */
                    /*! \brief 03.EC0D.D LH USX0 Rx USXGMII Local_Fault
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0RxUsxgmiiLocalFault

                        

                        Detect Rx USXGMII Local_Fault
                        
  */
      unsigned int   usx0RxUsxgmiiLocalFault : 1;    /* 03.EC0D.D  LH       */
                     /* Detect Rx USXGMII Local_Fault
                          */
                    /*! \brief 03.EC0D.C LH USX0 Link FIFO Overflow Error
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0LinkFifoOverflowError

                        

                        Link FIFO Overflow Error
                        
  */
      unsigned int   usx0LinkFifoOverflowError : 1;    /* 03.EC0D.C  LH       */
                     /* Link FIFO Overflow Error
                          */
                    /*! \brief 03.EC0D.B LH USX0 Link FIFO Underflow Error
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0LinkFifoUnderflowError

                        

                        Link FIFO Underflow Error
                        
  */
      unsigned int   usx0LinkFifoUnderflowError : 1;    /* 03.EC0D.B  LH       */
                     /* Link FIFO Underflow Error
                          */
                    /*! \brief 03.EC0D.A LH USX0 Link FIFO Parity Error
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0LinkFifoParityError

                        

                        Link FIFO Parity Error
                        
  */
      unsigned int   usx0LinkFifoParityError : 1;    /* 03.EC0D.A  LH       */
                     /* Link FIFO Parity Error
                          */
                    /*! \brief 03.EC0D.9 LH USX0 RX Packet Info Message
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0RxPacketInfoMessage

                        

                        Indicate the received Packet Information
                        Message has changed.
                        
  */
      unsigned int   usx0RxPacketInfoMessage : 1;    /* 03.EC0D.9  LH       */
                     /* Indicate the received Packet Information
                        Message has changed.
                          */
                    /*! \brief 03.EC0D.8 LH USX0 MAC Rx FIFO Parity Error
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacRxFifoParityError

                        

                        MAC Rx FIFO Parity Error
                        
  */
      unsigned int   usx0MacRxFifoParityError : 1;    /* 03.EC0D.8  LH       */
                     /* MAC Rx FIFO Parity Error
                          */
                    /*! \brief 03.EC0D.7 LH USX0 MAC Rx FIFO Overflow Err
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacRxFifoOverflowErr

                        

                        MAC Rx FIFO Overflow Error
                        
  */
      unsigned int   usx0MacRxFifoOverflowErr : 1;    /* 03.EC0D.7  LH       */
                     /* MAC Rx FIFO Overflow Error
                          */
                    /*! \brief 03.EC0D.6 LH USX0 MAC Rx FIFO Underflow Err
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacRxFifoUnderflowErr

                        

                        MAC Rx FIFO Underflow Error
                        
  */
      unsigned int   usx0MacRxFifoUnderflowErr : 1;    /* 03.EC0D.6  LH       */
                     /* MAC Rx FIFO Underflow Error
                          */
                    /*! \brief 03.EC0D.5 LH USX0 MAC Rx FIFO Idle deletion
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacRxFifoIdleDeletion

                        

                        MAC Rx FIFO Idle deletion
                        
  */
      unsigned int   usx0MacRxFifoIdleDeletion : 1;    /* 03.EC0D.5  LH       */
                     /* MAC Rx FIFO Idle deletion
                          */
                    /*! \brief 03.EC0D.4 LH USX0 MAC Tx FIFO Parity Err
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacTxFifoParityErr

                        

                        MAC Tx FIFO Parity Error
                        
  */
      unsigned int   usx0MacTxFifoParityErr : 1;    /* 03.EC0D.4  LH       */
                     /* MAC Tx FIFO Parity Error
                          */
                    /*! \brief 03.EC0D.3 LH USX0 MAC Tx FIFO Overflow
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacTxFifoOverflow

                        

                        MAC Tx FIFO Overflow Error
                        
  */
      unsigned int   usx0MacTxFifoOverflow : 1;    /* 03.EC0D.3  LH       */
                     /* MAC Tx FIFO Overflow Error
                          */
                    /*! \brief 03.EC0D.2 LH USX0 MAC Tx FIFO Underflow
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacTxFifoUnderflow

                        

                        MAC Tx FIFO Underflow Error
                        
  */
      unsigned int   usx0MacTxFifoUnderflow : 1;    /* 03.EC0D.2  LH       */
                     /* MAC Tx FIFO Underflow Error
                          */
                    /*! \brief 03.EC0D.1 LH USX0 MAC Tx SFD Error
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacTxSfdError

                        

                        MAC Tx SFD Error
                        
  */
      unsigned int   usx0MacTxSfdError : 1;    /* 03.EC0D.1  LH       */
                     /* MAC Tx SFD Error
                          */
                    /*! \brief 03.EC0D.0 LH USX0 MAC Tx FIFO Idle insertion
                        AQ_PcsReceiveVendorAlarms_HHD.u13.bits_13.usx0MacTxFifoIdleInsertion

                        

                        MAC Tx FIFO Idle insertion
                        
  */
      unsigned int   usx0MacTxFifoIdleInsertion : 1;    /* 03.EC0D.0  LH       */
                     /* MAC Tx FIFO Idle insertion
                          */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 03.EC0E.E LH USX1 Rx Header CRC Error
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1RxHeaderCrcError

                        

                        Detect Rx Header CRC Error
                        
  */
      unsigned int   usx1RxHeaderCrcError : 1;    /* 03.EC0E.E  LH       */
                     /* Detect Rx Header CRC Error
                          */
                    /*! \brief 03.EC0E.D LH USX1 Rx USXGMII Local_Fault
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1RxUsxgmiiLocalFault

                        

                        Detect Rx USXGMII Local_Fault
                        
  */
      unsigned int   usx1RxUsxgmiiLocalFault : 1;    /* 03.EC0E.D  LH       */
                     /* Detect Rx USXGMII Local_Fault
                          */
                    /*! \brief 03.EC0E.C LH USX1 Link FIFO Overflow Error
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1LinkFifoOverflowError

                        

                        Link FIFO Overflow Error
                        
  */
      unsigned int   usx1LinkFifoOverflowError : 1;    /* 03.EC0E.C  LH       */
                     /* Link FIFO Overflow Error
                          */
                    /*! \brief 03.EC0E.B LH USX1 Link FIFO Underflow Error
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1LinkFifoUnderflowError

                        

                        Link FIFO Underflow Error
                        
  */
      unsigned int   usx1LinkFifoUnderflowError : 1;    /* 03.EC0E.B  LH       */
                     /* Link FIFO Underflow Error
                          */
                    /*! \brief 03.EC0E.A LH USX1 Link FIFO Parity Error
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1LinkFifoParityError

                        

                        Link FIFO Parity Error
                        
  */
      unsigned int   usx1LinkFifoParityError : 1;    /* 03.EC0E.A  LH       */
                     /* Link FIFO Parity Error
                          */
                    /*! \brief 03.EC0E.9 LH USX1 RX Packet Info Message
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1RxPacketInfoMessage

                        

                        Indicate the received Packet Information
                        Message has changed.
                        
  */
      unsigned int   usx1RxPacketInfoMessage : 1;    /* 03.EC0E.9  LH       */
                     /* Indicate the received Packet Information
                        Message has changed.
                          */
                    /*! \brief 03.EC0E.8 LH USX1 MAC Rx FIFO Parity Error
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacRxFifoParityError

                        

                        MAC Rx FIFO Parity Error
                        
  */
      unsigned int   usx1MacRxFifoParityError : 1;    /* 03.EC0E.8  LH       */
                     /* MAC Rx FIFO Parity Error
                          */
                    /*! \brief 03.EC0E.7 LH USX1 MAC Rx FIFO Overflow Err
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacRxFifoOverflowErr

                        

                        MAC Rx FIFO Overflow Error
                        
  */
      unsigned int   usx1MacRxFifoOverflowErr : 1;    /* 03.EC0E.7  LH       */
                     /* MAC Rx FIFO Overflow Error
                          */
                    /*! \brief 03.EC0E.6 LH USX1 MAC Rx FIFO Underflow Err
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacRxFifoUnderflowErr

                        

                        MAC Rx FIFO Underflow Error
                        
  */
      unsigned int   usx1MacRxFifoUnderflowErr : 1;    /* 03.EC0E.6  LH       */
                     /* MAC Rx FIFO Underflow Error
                          */
                    /*! \brief 03.EC0E.5 LH USX1 MAC Rx FIFO Idle deletion
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacRxFifoIdleDeletion

                        

                        MAC Rx FIFO Idle deletion
                        
  */
      unsigned int   usx1MacRxFifoIdleDeletion : 1;    /* 03.EC0E.5  LH       */
                     /* MAC Rx FIFO Idle deletion
                          */
                    /*! \brief 03.EC0E.4 LH USX1 MAC Tx FIFO Parity Err
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacTxFifoParityErr

                        

                        MAC Tx FIFO Parity Error
                        
  */
      unsigned int   usx1MacTxFifoParityErr : 1;    /* 03.EC0E.4  LH       */
                     /* MAC Tx FIFO Parity Error
                          */
                    /*! \brief 03.EC0E.3 LH USX1 MAC Tx FIFO Overflow
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacTxFifoOverflow

                        

                        MAC Tx FIFO Overflow Error
                        
  */
      unsigned int   usx1MacTxFifoOverflow : 1;    /* 03.EC0E.3  LH       */
                     /* MAC Tx FIFO Overflow Error
                          */
                    /*! \brief 03.EC0E.2 LH USX1 MAC Tx FIFO Underflow
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacTxFifoUnderflow

                        

                        MAC Tx FIFO Underflow Error
                        
  */
      unsigned int   usx1MacTxFifoUnderflow : 1;    /* 03.EC0E.2  LH       */
                     /* MAC Tx FIFO Underflow Error
                          */
                    /*! \brief 03.EC0E.1 LH USX1 MAC Tx SFD Error
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacTxSfdError

                        

                        MAC Tx SFD Error
                        
  */
      unsigned int   usx1MacTxSfdError : 1;    /* 03.EC0E.1  LH       */
                     /* MAC Tx SFD Error
                          */
                    /*! \brief 03.EC0E.0 LH USX1 MAC Tx FIFO Idle insertion
                        AQ_PcsReceiveVendorAlarms_HHD.u14.bits_14.usx1MacTxFifoIdleInsertion

                        

                        MAC Tx FIFO Idle insertion
                        
  */
      unsigned int   usx1MacTxFifoIdleInsertion : 1;    /* 03.EC0E.0  LH       */
                     /* MAC Tx FIFO Idle insertion
                          */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 5;
                    /*! \brief 03.EC0F.A LL USX0 Auto Neg Complete Latch Low
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0AutoNegCompleteLatchLow

                        

                        Auto-Negotiation complete
                        
  */
      unsigned int   usx0AutoNegCompleteLatchLow : 1;    /* 03.EC0F.A  LL       */
                     /* Auto-Negotiation complete
                          */
                    /*! \brief 03.EC0F.9 LH USX0 Auto Neg Complete Latch High
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0AutoNegCompleteLatchHigh

                        

                        Auto-Negotiation complete
                        
  */
      unsigned int   usx0AutoNegCompleteLatchHigh : 1;    /* 03.EC0F.9  LH       */
                     /* Auto-Negotiation complete
                          */
                    /*! \brief 03.EC0F.8 LH USX0 AN State Machine Interrupt
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0AnStateMachineInterrupt

                        

                        Auto-Negotiation State Machine Interrupt
                        
  */
      unsigned int   usx0AnStateMachineInterrupt : 1;    /* 03.EC0F.8  LH       */
                     /* Auto-Negotiation State Machine Interrupt
                          */
                    /*! \brief 03.EC0F.7 LH USX0 RX Unidata Config Change
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0RxUnidataConfigChange

                        

                        Rx_Unidata or Rx_Config_Reg (Link
                        partner advertisement register) change
                        
  */
      unsigned int   usx0RxUnidataConfigChange : 1;    /* 03.EC0F.7  LH       */
                     /* Rx_Unidata or Rx_Config_Reg (Link
                        partner advertisement register) change
                          */
                    /*! \brief 03.EC0F.6 LH USX0 Invocation of the priority resolution function
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0InvocationOfThePriorityResolutionFunction

                        

                         Invocation of the priority resolution function
                        
  */
      unsigned int   usx0InvocationOfThePriorityResolutionFunction : 1;    /* 03.EC0F.6  LH       */
                     /*  Invocation of the priority resolution function
                          */
                    /*! \brief 03.EC0F.5 LH USX0 Link Timer Done
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0LinkTimerDone

                        

                        Link Timer Done
                        
  */
      unsigned int   usx0LinkTimerDone : 1;    /* 03.EC0F.5  LH       */
                     /* Link Timer Done
                          */
                    /*! \brief 03.EC0F.4 LH USX0  Ability match indication
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0AbilityMatchIndication

                        

                         Ability match indication
                        
  */
      unsigned int   usx0AbilityMatchIndication : 1;    /* 03.EC0F.4  LH       */
                     /*  Ability match indication
                          */
                    /*! \brief 03.EC0F.3 LH USX0 Acknowledgement match indication
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0AcknowledgementMatchIndication

                        

                        Acknowledgement match indication
                        
  */
      unsigned int   usx0AcknowledgementMatchIndication : 1;    /* 03.EC0F.3  LH       */
                     /* Acknowledgement match indication
                          */
                    /*! \brief 03.EC0F.2 LH USX0 Consistency match indication
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0ConsistencyMatchIndication

                        

                         Consistency match indication
                        
  */
      unsigned int   usx0ConsistencyMatchIndication : 1;    /* 03.EC0F.2  LH       */
                     /*  Consistency match indication
                          */
                    /*! \brief 03.EC0F.1 LH USX0 Idle Match Indication
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0IdleMatchIndication

                        

                        Idle Match Indication
                        
  */
      unsigned int   usx0IdleMatchIndication : 1;    /* 03.EC0F.1  LH       */
                     /* Idle Match Indication
                          */
                    /*! \brief 03.EC0F.0 LH USX0 Link Partner Adv Change
                        AQ_PcsReceiveVendorAlarms_HHD.u15.bits_15.usx0LinkPartnerAdvChange

                        

                         Link partner advertisement register change
                        
  */
      unsigned int   usx0LinkPartnerAdvChange : 1;    /* 03.EC0F.0  LH       */
                     /*  Link partner advertisement register change
                          */
    } bits_15;
    uint16_t word_15;
  } u15;
  /*! \brief Union for bit and word level access of word 16 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 5;
                    /*! \brief 03.EC10.A LL USX1 Auto Neg Complete Latch Low
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1AutoNegCompleteLatchLow

                        

                        Auto-Negotiation complete
                        
  */
      unsigned int   usx1AutoNegCompleteLatchLow : 1;    /* 03.EC10.A  LL       */
                     /* Auto-Negotiation complete
                          */
                    /*! \brief 03.EC10.9 LH USX1 Auto Neg Complete Latch High
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1AutoNegCompleteLatchHigh

                        

                        Auto-Negotiation complete
                        
  */
      unsigned int   usx1AutoNegCompleteLatchHigh : 1;    /* 03.EC10.9  LH       */
                     /* Auto-Negotiation complete
                          */
                    /*! \brief 03.EC10.8 LH USX1 AN State Machine Interrupt
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1AnStateMachineInterrupt

                        

                        Auto-Negotiation State Machine Interrupt
                        
  */
      unsigned int   usx1AnStateMachineInterrupt : 1;    /* 03.EC10.8  LH       */
                     /* Auto-Negotiation State Machine Interrupt
                          */
                    /*! \brief 03.EC10.7 LH USX1 RX Unidata Config Change
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1RxUnidataConfigChange

                        

                        Rx_Unidata or Rx_Config_Reg (Link
                        partner advertisement register) change
                        
  */
      unsigned int   usx1RxUnidataConfigChange : 1;    /* 03.EC10.7  LH       */
                     /* Rx_Unidata or Rx_Config_Reg (Link
                        partner advertisement register) change
                          */
                    /*! \brief 03.EC10.6 LH USX1 Invocation of the priority resolution function
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1InvocationOfThePriorityResolutionFunction

                        

                         Invocation of the priority resolution function
                        
  */
      unsigned int   usx1InvocationOfThePriorityResolutionFunction : 1;    /* 03.EC10.6  LH       */
                     /*  Invocation of the priority resolution function
                          */
                    /*! \brief 03.EC10.5 LH USX1 Link Timer Done
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1LinkTimerDone

                        

                        Link Timer Done
                        
  */
      unsigned int   usx1LinkTimerDone : 1;    /* 03.EC10.5  LH       */
                     /* Link Timer Done
                          */
                    /*! \brief 03.EC10.4 LH USX1  Ability match indication
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1AbilityMatchIndication

                        

                         Ability match indication
                        
  */
      unsigned int   usx1AbilityMatchIndication : 1;    /* 03.EC10.4  LH       */
                     /*  Ability match indication
                          */
                    /*! \brief 03.EC10.3 LH USX1 Acknowledgement match indication
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1AcknowledgementMatchIndication

                        

                        Acknowledgement match indication
                        
  */
      unsigned int   usx1AcknowledgementMatchIndication : 1;    /* 03.EC10.3  LH       */
                     /* Acknowledgement match indication
                          */
                    /*! \brief 03.EC10.2 LH USX1 Consistency match indication
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1ConsistencyMatchIndication

                        

                         Consistency match indication
                        
  */
      unsigned int   usx1ConsistencyMatchIndication : 1;    /* 03.EC10.2  LH       */
                     /*  Consistency match indication
                          */
                    /*! \brief 03.EC10.1 LH USX1 Idle Match Indication
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1IdleMatchIndication

                        

                        Idle Match Indication
                        
  */
      unsigned int   usx1IdleMatchIndication : 1;    /* 03.EC10.1  LH       */
                     /* Idle Match Indication
                          */
                    /*! \brief 03.EC10.0 LH USX1 Link Partner Adv Change
                        AQ_PcsReceiveVendorAlarms_HHD.u16.bits_16.usx1LinkPartnerAdvChange

                        

                         Link partner advertisement register change
                        
  */
      unsigned int   usx1LinkPartnerAdvChange : 1;    /* 03.EC10.0  LH       */
                     /*  Link partner advertisement register change
                          */
    } bits_16;
    uint16_t word_16;
  } u16;
} AQ_PcsReceiveVendorAlarms_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Internal Alarms: 03.ED0D */
/*                  PCS Receive Vendor Internal Alarms: 03.ED0D */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Internal Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 03.ED0D.E LH USX0 Rx Header CRC Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0RxHeaderCrcError

                        

                        Detect Rx Header CRC Error
                        
  */
      unsigned int   usx0RxHeaderCrcError : 1;    /* 03.ED0D.E  LH       */
                     /* Detect Rx Header CRC Error
                          */
                    /*! \brief 03.ED0D.D LH USX0 Rx USXGMII Local_Fault
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0RxUsxgmiiLocalFault

                        

                        Detect Rx USXGMII Local_Fault
                        
  */
      unsigned int   usx0RxUsxgmiiLocalFault : 1;    /* 03.ED0D.D  LH       */
                     /* Detect Rx USXGMII Local_Fault
                          */
                    /*! \brief 03.ED0D.C LH USX0 Link FIFO Overflow Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0LinkFifoOverflowError

                        

                        Link FIFO Overflow Error
                        
  */
      unsigned int   usx0LinkFifoOverflowError : 1;    /* 03.ED0D.C  LH       */
                     /* Link FIFO Overflow Error
                          */
                    /*! \brief 03.ED0D.B LH USX0 Link FIFO Underflow Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0LinkFifoUnderflowError

                        

                        Link FIFO Underflow Error
                        
  */
      unsigned int   usx0LinkFifoUnderflowError : 1;    /* 03.ED0D.B  LH       */
                     /* Link FIFO Underflow Error
                          */
                    /*! \brief 03.ED0D.A LH USX0 Link FIFO Parity Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0LinkFifoParityError

                        

                        Link FIFO Parity Error
                        
  */
      unsigned int   usx0LinkFifoParityError : 1;    /* 03.ED0D.A  LH       */
                     /* Link FIFO Parity Error
                          */
                    /*! \brief 03.ED0D.9 LH USX0 RX Packet Info Message
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0RxPacketInfoMessage

                        

                        Indicate the received Packet Information
                        Message has changed.
                        
  */
      unsigned int   usx0RxPacketInfoMessage : 1;    /* 03.ED0D.9  LH       */
                     /* Indicate the received Packet Information
                        Message has changed.
                          */
                    /*! \brief 03.ED0D.8 LH USX0 MAC Rx FIFO Parity Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacRxFifoParityError

                        

                        MAC Rx FIFO Parity Error
                        
  */
      unsigned int   usx0MacRxFifoParityError : 1;    /* 03.ED0D.8  LH       */
                     /* MAC Rx FIFO Parity Error
                          */
                    /*! \brief 03.ED0D.7 LH USX0 MAC Rx FIFO Overflow Err
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacRxFifoOverflowErr

                        

                        MAC Rx FIFO Overflow Error
                        
  */
      unsigned int   usx0MacRxFifoOverflowErr : 1;    /* 03.ED0D.7  LH       */
                     /* MAC Rx FIFO Overflow Error
                          */
                    /*! \brief 03.ED0D.6 LH USX0 MAC Rx FIFO Underflow Err
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacRxFifoUnderflowErr

                        

                        MAC Rx FIFO Underflow Error
                        
  */
      unsigned int   usx0MacRxFifoUnderflowErr : 1;    /* 03.ED0D.6  LH       */
                     /* MAC Rx FIFO Underflow Error
                          */
                    /*! \brief 03.ED0D.5 LH USX0 MAC Rx FIFO Idle deletion
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacRxFifoIdleDeletion

                        

                        MAC Rx FIFO Idle deletion
                        
  */
      unsigned int   usx0MacRxFifoIdleDeletion : 1;    /* 03.ED0D.5  LH       */
                     /* MAC Rx FIFO Idle deletion
                          */
                    /*! \brief 03.ED0D.4 LH USX0 MAC Tx FIFO Parity Err
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacTxFifoParityErr

                        

                        MAC Tx FIFO Parity Error
                        
  */
      unsigned int   usx0MacTxFifoParityErr : 1;    /* 03.ED0D.4  LH       */
                     /* MAC Tx FIFO Parity Error
                          */
                    /*! \brief 03.ED0D.3 LH USX0 MAC Tx FIFO Overflow
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacTxFifoOverflow

                        

                        MAC Tx FIFO Overflow Error
                        
  */
      unsigned int   usx0MacTxFifoOverflow : 1;    /* 03.ED0D.3  LH       */
                     /* MAC Tx FIFO Overflow Error
                          */
                    /*! \brief 03.ED0D.2 LH USX0 MAC Tx FIFO Underflow
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacTxFifoUnderflow

                        

                        MAC Tx FIFO Underflow Error
                        
  */
      unsigned int   usx0MacTxFifoUnderflow : 1;    /* 03.ED0D.2  LH       */
                     /* MAC Tx FIFO Underflow Error
                          */
                    /*! \brief 03.ED0D.1 LH USX0 MAC Tx SFD Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacTxSfdError

                        

                        MAC Tx SFD Error
                        
  */
      unsigned int   usx0MacTxSfdError : 1;    /* 03.ED0D.1  LH       */
                     /* MAC Tx SFD Error
                          */
                    /*! \brief 03.ED0D.0 LH USX0 MAC Tx FIFO Idle insertion
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u0.bits_0.usx0MacTxFifoIdleInsertion

                        

                        MAC Tx FIFO Idle insertion
                        
  */
      unsigned int   usx0MacTxFifoIdleInsertion : 1;    /* 03.ED0D.0  LH       */
                     /* MAC Tx FIFO Idle insertion
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Internal Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 03.ED0E.E LH USX1 Rx Header CRC Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1RxHeaderCrcError

                        

                        Detect Rx Header CRC Error
                        
  */
      unsigned int   usx1RxHeaderCrcError : 1;    /* 03.ED0E.E  LH       */
                     /* Detect Rx Header CRC Error
                          */
                    /*! \brief 03.ED0E.D LH USX1 Rx USXGMII Local_Fault
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1RxUsxgmiiLocalFault

                        

                        Detect Rx USXGMII Local_Fault
                        
  */
      unsigned int   usx1RxUsxgmiiLocalFault : 1;    /* 03.ED0E.D  LH       */
                     /* Detect Rx USXGMII Local_Fault
                          */
                    /*! \brief 03.ED0E.C LH USX1 Link FIFO Overflow Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1LinkFifoOverflowError

                        

                        Link FIFO Overflow Error
                        
  */
      unsigned int   usx1LinkFifoOverflowError : 1;    /* 03.ED0E.C  LH       */
                     /* Link FIFO Overflow Error
                          */
                    /*! \brief 03.ED0E.B LH USX1 Link FIFO Underflow Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1LinkFifoUnderflowError

                        

                        Link FIFO Underflow Error
                        
  */
      unsigned int   usx1LinkFifoUnderflowError : 1;    /* 03.ED0E.B  LH       */
                     /* Link FIFO Underflow Error
                          */
                    /*! \brief 03.ED0E.A LH USX1 Link FIFO Parity Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1LinkFifoParityError

                        

                        Link FIFO Parity Error
                        
  */
      unsigned int   usx1LinkFifoParityError : 1;    /* 03.ED0E.A  LH       */
                     /* Link FIFO Parity Error
                          */
                    /*! \brief 03.ED0E.9 LH USX1 RX Packet Info Message
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1RxPacketInfoMessage

                        

                        Indicate the received Packet Information
                        Message has changed.
                        
  */
      unsigned int   usx1RxPacketInfoMessage : 1;    /* 03.ED0E.9  LH       */
                     /* Indicate the received Packet Information
                        Message has changed.
                          */
                    /*! \brief 03.ED0E.8 LH USX1 MAC Rx FIFO Parity Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacRxFifoParityError

                        

                        MAC Rx FIFO Parity Error
                        
  */
      unsigned int   usx1MacRxFifoParityError : 1;    /* 03.ED0E.8  LH       */
                     /* MAC Rx FIFO Parity Error
                          */
                    /*! \brief 03.ED0E.7 LH USX1 MAC Rx FIFO Overflow Err
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacRxFifoOverflowErr

                        

                        MAC Rx FIFO Overflow Error
                        
  */
      unsigned int   usx1MacRxFifoOverflowErr : 1;    /* 03.ED0E.7  LH       */
                     /* MAC Rx FIFO Overflow Error
                          */
                    /*! \brief 03.ED0E.6 LH USX1 MAC Rx FIFO Underflow Err
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacRxFifoUnderflowErr

                        

                        MAC Rx FIFO Underflow Error
                        
  */
      unsigned int   usx1MacRxFifoUnderflowErr : 1;    /* 03.ED0E.6  LH       */
                     /* MAC Rx FIFO Underflow Error
                          */
                    /*! \brief 03.ED0E.5 LH USX1 MAC Rx FIFO Idle deletion
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacRxFifoIdleDeletion

                        

                        MAC Rx FIFO Idle deletion
                        
  */
      unsigned int   usx1MacRxFifoIdleDeletion : 1;    /* 03.ED0E.5  LH       */
                     /* MAC Rx FIFO Idle deletion
                          */
                    /*! \brief 03.ED0E.4 LH USX1 MAC Tx FIFO Parity Err
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacTxFifoParityErr

                        

                        MAC Tx FIFO Parity Error
                        
  */
      unsigned int   usx1MacTxFifoParityErr : 1;    /* 03.ED0E.4  LH       */
                     /* MAC Tx FIFO Parity Error
                          */
                    /*! \brief 03.ED0E.3 LH USX1 MAC Tx FIFO Overflow
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacTxFifoOverflow

                        

                        MAC Tx FIFO Overflow Error
                        
  */
      unsigned int   usx1MacTxFifoOverflow : 1;    /* 03.ED0E.3  LH       */
                     /* MAC Tx FIFO Overflow Error
                          */
                    /*! \brief 03.ED0E.2 LH USX1 MAC Tx FIFO Underflow
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacTxFifoUnderflow

                        

                        MAC Tx FIFO Underflow Error
                        
  */
      unsigned int   usx1MacTxFifoUnderflow : 1;    /* 03.ED0E.2  LH       */
                     /* MAC Tx FIFO Underflow Error
                          */
                    /*! \brief 03.ED0E.1 LH USX1 MAC Tx SFD Error
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacTxSfdError

                        

                        MAC Tx SFD Error
                        
  */
      unsigned int   usx1MacTxSfdError : 1;    /* 03.ED0E.1  LH       */
                     /* MAC Tx SFD Error
                          */
                    /*! \brief 03.ED0E.0 LH USX1 MAC Tx FIFO Idle insertion
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u1.bits_1.usx1MacTxFifoIdleInsertion

                        

                        MAC Tx FIFO Idle insertion
                        
  */
      unsigned int   usx1MacTxFifoIdleInsertion : 1;    /* 03.ED0E.0  LH       */
                     /* MAC Tx FIFO Idle insertion
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive Vendor Internal Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 5;
                    /*! \brief 03.ED0F.A LL USX0 Auto Neg Complete Latch Low
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0AutoNegCompleteLatchLow

                        

                        Auto-Negotiation complete
                        
  */
      unsigned int   usx0AutoNegCompleteLatchLow : 1;    /* 03.ED0F.A  LL       */
                     /* Auto-Negotiation complete
                          */
                    /*! \brief 03.ED0F.9 LH USX0 Auto Neg Complete Latch High
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0AutoNegCompleteLatchHigh

                        

                        Auto-Negotiation complete
                        
  */
      unsigned int   usx0AutoNegCompleteLatchHigh : 1;    /* 03.ED0F.9  LH       */
                     /* Auto-Negotiation complete
                          */
                    /*! \brief 03.ED0F.8 LH USX0 AN State Machine Interrupt
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0AnStateMachineInterrupt

                        

                        Auto-Negotiation State Machine Interrupt
                        
  */
      unsigned int   usx0AnStateMachineInterrupt : 1;    /* 03.ED0F.8  LH       */
                     /* Auto-Negotiation State Machine Interrupt
                          */
                    /*! \brief 03.ED0F.7 LH USX0 RX Unidata Config Change
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0RxUnidataConfigChange

                        

                        Rx_Unidata or Rx_Config_Reg (Link
                        partner advertisement register) change
                        
  */
      unsigned int   usx0RxUnidataConfigChange : 1;    /* 03.ED0F.7  LH       */
                     /* Rx_Unidata or Rx_Config_Reg (Link
                        partner advertisement register) change
                          */
                    /*! \brief 03.ED0F.6 LH USX0 Invocation of the priority resolution function
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0InvocationOfThePriorityResolutionFunction

                        

                         Invocation of the priority resolution function
                        
  */
      unsigned int   usx0InvocationOfThePriorityResolutionFunction : 1;    /* 03.ED0F.6  LH       */
                     /*  Invocation of the priority resolution function
                          */
                    /*! \brief 03.ED0F.5 LH USX0 Link Timer Done
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0LinkTimerDone

                        

                        Link Timer Done
                        
  */
      unsigned int   usx0LinkTimerDone : 1;    /* 03.ED0F.5  LH       */
                     /* Link Timer Done
                          */
                    /*! \brief 03.ED0F.4 LH USX0  Ability match indication
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0AbilityMatchIndication

                        

                         Ability match indication
                        
  */
      unsigned int   usx0AbilityMatchIndication : 1;    /* 03.ED0F.4  LH       */
                     /*  Ability match indication
                          */
                    /*! \brief 03.ED0F.3 LH USX0 Acknowledgement match indication
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0AcknowledgementMatchIndication

                        

                        Acknowledgement match indication
                        
  */
      unsigned int   usx0AcknowledgementMatchIndication : 1;    /* 03.ED0F.3  LH       */
                     /* Acknowledgement match indication
                          */
                    /*! \brief 03.ED0F.2 LH USX0 Consistency match indication
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0ConsistencyMatchIndication

                        

                         Consistency match indication
                        
  */
      unsigned int   usx0ConsistencyMatchIndication : 1;    /* 03.ED0F.2  LH       */
                     /*  Consistency match indication
                          */
                    /*! \brief 03.ED0F.1 LH USX0 Idle Match Indication
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0IdleMatchIndication

                        

                        Idle Match Indication
                        
  */
      unsigned int   usx0IdleMatchIndication : 1;    /* 03.ED0F.1  LH       */
                     /* Idle Match Indication
                          */
                    /*! \brief 03.ED0F.0 LH USX0 Link Partner Adv Change
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u2.bits_2.usx0LinkPartnerAdvChange

                        

                         Link partner advertisement register change
                        
  */
      unsigned int   usx0LinkPartnerAdvChange : 1;    /* 03.ED0F.0  LH       */
                     /*  Link partner advertisement register change
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive Vendor Internal Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 5;
                    /*! \brief 03.ED10.A LL USX1 Auto Neg Complete Latch Low
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1AutoNegCompleteLatchLow

                        

                        Auto-Negotiation complete
                        
  */
      unsigned int   usx1AutoNegCompleteLatchLow : 1;    /* 03.ED10.A  LL       */
                     /* Auto-Negotiation complete
                          */
                    /*! \brief 03.ED10.9 LH USX1 Auto Neg Complete Latch High
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1AutoNegCompleteLatchHigh

                        

                        Auto-Negotiation complete
                        
  */
      unsigned int   usx1AutoNegCompleteLatchHigh : 1;    /* 03.ED10.9  LH       */
                     /* Auto-Negotiation complete
                          */
                    /*! \brief 03.ED10.8 LH USX1 AN State Machine Interrupt
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1AnStateMachineInterrupt

                        

                        Auto-Negotiation State Machine Interrupt
                        
  */
      unsigned int   usx1AnStateMachineInterrupt : 1;    /* 03.ED10.8  LH       */
                     /* Auto-Negotiation State Machine Interrupt
                          */
                    /*! \brief 03.ED10.7 LH USX1 RX Unidata Config Change
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1RxUnidataConfigChange

                        

                        Rx_Unidata or Rx_Config_Reg (Link
                        partner advertisement register) change
                        
  */
      unsigned int   usx1RxUnidataConfigChange : 1;    /* 03.ED10.7  LH       */
                     /* Rx_Unidata or Rx_Config_Reg (Link
                        partner advertisement register) change
                          */
                    /*! \brief 03.ED10.6 LH USX1 Invocation of the priority resolution function
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1InvocationOfThePriorityResolutionFunction

                        

                         Invocation of the priority resolution function
                        
  */
      unsigned int   usx1InvocationOfThePriorityResolutionFunction : 1;    /* 03.ED10.6  LH       */
                     /*  Invocation of the priority resolution function
                          */
                    /*! \brief 03.ED10.5 LH USX1 Link Timer Done
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1LinkTimerDone

                        

                        Link Timer Done
                        
  */
      unsigned int   usx1LinkTimerDone : 1;    /* 03.ED10.5  LH       */
                     /* Link Timer Done
                          */
                    /*! \brief 03.ED10.4 LH USX1  Ability match indication
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1AbilityMatchIndication

                        

                         Ability match indication
                        
  */
      unsigned int   usx1AbilityMatchIndication : 1;    /* 03.ED10.4  LH       */
                     /*  Ability match indication
                          */
                    /*! \brief 03.ED10.3 LH USX1 Acknowledgement match indication
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1AcknowledgementMatchIndication

                        

                        Acknowledgement match indication
                        
  */
      unsigned int   usx1AcknowledgementMatchIndication : 1;    /* 03.ED10.3  LH       */
                     /* Acknowledgement match indication
                          */
                    /*! \brief 03.ED10.2 LH USX1 Consistency match indication
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1ConsistencyMatchIndication

                        

                         Consistency match indication
                        
  */
      unsigned int   usx1ConsistencyMatchIndication : 1;    /* 03.ED10.2  LH       */
                     /*  Consistency match indication
                          */
                    /*! \brief 03.ED10.1 LH USX1 Idle Match Indication
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1IdleMatchIndication

                        

                        Idle Match Indication
                        
  */
      unsigned int   usx1IdleMatchIndication : 1;    /* 03.ED10.1  LH       */
                     /* Idle Match Indication
                          */
                    /*! \brief 03.ED10.0 LH USX1 Link Partner Adv Change
                        AQ_PcsReceiveVendorInternalAlarms_HHD.u3.bits_3.usx1LinkPartnerAdvChange

                        

                         Link partner advertisement register change
                        
  */
      unsigned int   usx1LinkPartnerAdvChange : 1;    /* 03.ED10.0  LH       */
                     /*  Link partner advertisement register change
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsReceiveVendorInternalAlarms_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Interrupt Mask: 03.F400 */
/*                  PCS Receive Vendor Interrupt Mask: 03.F400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.F400.F R/WPD CRC Error Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.crcErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when a CRC-8 error is detected on the receive PCS frame.  */
      unsigned int   crcErrorMask : 1;    /* 03.F400.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F400.E R/WPD LDPC Decode Failure Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.ldpcDecodeFailureMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when the LDPC decoder fails to decode an LDPC block.  */
      unsigned int   ldpcDecodeFailureMask : 1;    /* 03.F400.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 2;
                    /*! \brief 03.F400.B R/WPD Local Fault Detect Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.localFaultDetectMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   localFaultDetectMask : 1;    /* 03.F400.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.A R/WPD LOF Detect Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.lofDetectMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   lofDetectMask : 1;    /* 03.F400.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.9 R/WPD 40G BIP Lock Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0._40gBipLockMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   _40gBipLockMask : 1;    /* 03.F400.9  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.8 R/WPD Invalid 65B Block Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.invalid_65bBlockMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when an invalid 65B block (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   invalid_65bBlockMask : 1;    /* 03.F400.8  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F400.7 R/WPD EEE Rx LPI Active Off Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.eeeRxLpiActiveOffMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiActiveOffMask : 1;    /* 03.F400.7  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.6 R/WPD EEE Rx LPI Active On Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.eeeRxLpiActiveOnMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiActiveOnMask : 1;    /* 03.F400.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.5 R/WPD LDPC Consecutive Errored Frame Exceeded Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.ldpcConsecutiveErroredFrameExceededMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   ldpcConsecutiveErroredFrameExceededMask : 1;    /* 03.F400.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.4 R/WPD EEE Rx LPI Alert Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.eeeRxLpiAlertMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiAlertMask : 1;    /* 03.F400.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.3 R/WPD EEE Rx LPI Received Latched Low Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.eeeRxLpiReceivedLatchedLowMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiReceivedLatchedLowMask : 1;    /* 03.F400.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F400.2 R/WPD EEE Rx LPI Received Latched High Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.eeeRxLpiReceivedLatchedHighMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   eeeRxLpiReceivedLatchedHighMask : 1;    /* 03.F400.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.F400.0 R/WPD Change in Auxilliary Bit Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u0.bits_0.changeInAuxilliaryBitMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when a change is detected in the auxilliary bit.  */
      unsigned int   changeInAuxilliaryBitMask : 1;    /* 03.F400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 03.F405.B R/WPD XFI1 Invalid 66B Character Received Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u5.bits_5.xfi1Invalid_66bCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1Invalid_66bCharacterReceivedMask : 1;    /* 03.F405.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.F405.3 R/WPD XFI0 Invalid 66B Character Received Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u5.bits_5.xfi0Invalid_66bCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0Invalid_66bCharacterReceivedMask : 1;    /* 03.F405.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved2 : 3;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.F406.7 R/WPD XFI1 Receive Link Status Latch High  Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u6.bits_6.xfi1ReceiveLinkStatusLatchHighMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1ReceiveLinkStatusLatchHighMask : 1;    /* 03.F406.7  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.F406.5 R/WPD XFI1 High BER Status Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u6.bits_6.xfi1HighBerStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1HighBerStatusMask : 1;    /* 03.F406.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.4 R/WPD XFI1 Block Lock Status Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u6.bits_6.xfi1BlockLockStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1BlockLockStatusMask : 1;    /* 03.F406.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.3 R/WPD XFI0 Receive Link Status Latch High  Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u6.bits_6.xfi0ReceiveLinkStatusLatchHighMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0ReceiveLinkStatusLatchHighMask : 1;    /* 03.F406.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 03.F406.1 R/WPD XFI0 High BER Status Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u6.bits_6.xfi0HighBerStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0HighBerStatusMask : 1;    /* 03.F406.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.0 R/WPD XFI0 Block Lock Status Mask
                        AQ_PcsReceiveVendorInterruptMask_HHD.u6.bits_6.xfi0BlockLockStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0BlockLockStatusMask : 1;    /* 03.F406.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsReceiveVendorInterruptMask_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Vendor Debug: 03.F800 */
/*                  PCS Receive Vendor Debug: 03.F800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 03.F800.F R/WPD PCS Rx Descrambler Disable
                        AQ_PcsReceiveVendorDebug_HHD.u0.bits_0.pcsRxDescramblerDisable

                        Provisionable Default = 0x0

                        1 = Rx Descrambler Disabled
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        Setting this bit disables the Rx descrambler during regular data transmission (i.e. descrambler functionality during training and startup is unmodified).  */
      unsigned int   pcsRxDescramblerDisable : 1;    /* 03.F800.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Rx Descrambler Disabled
                        0 = Normal Operation
                          */
      unsigned int   reserved0 : 12;
                    /*! \brief 03.F800.2 R/WPD PCS Network Loopback Merge
                        AQ_PcsReceiveVendorDebug_HHD.u0.bits_0.pcsNetworkLoopbackMerge

                        Provisionable Default = 0x1

                        When set to 1, XAUI data from the local MAC and PCS Network Loopback data will be merged.
                        

                 <B>Notes:</B>
                        If the MAC sends data, it will take priority over the PCS Network Loopback data. The loopback data will be dropped.  */
      unsigned int   pcsNetworkLoopbackMerge : 1;    /* 03.F800.2  R/WPD      Provisionable Default = 0x1 */
                     /* When set to 1, XAUI data from the local MAC and PCS Network Loopback data will be merged.
                          */
                    /*! \brief 03.F800.1 R/WPD PCS Network Loopback Pass Through
                        AQ_PcsReceiveVendorDebug_HHD.u0.bits_0.pcsNetworkLoopbackPassThrough

                        Provisionable Default = 0x1

                        When set to 1, this bit enables loopback traffic from the PCS Network Loopback to pass-through towards the System XAUI side. When set to 0, the data sent towards the system XUAI will be an IDLE ordered set data stream when in PCS Network Loopback
                        

                 <B>Notes:</B>
                        This enables traffic to pass through as well as loopback when the PCS Network Loopback is enabled.  */
      unsigned int   pcsNetworkLoopbackPassThrough : 1;    /* 03.F800.1  R/WPD      Provisionable Default = 0x1 */
                     /* When set to 1, this bit enables loopback traffic from the PCS Network Loopback to pass-through towards the System XAUI side. When set to 0, the data sent towards the system XUAI will be an IDLE ordered set data stream when in PCS Network Loopback
                          */
                    /*! \brief 03.F800.0 R/WPD PCS Network Loopback
                        AQ_PcsReceiveVendorDebug_HHD.u0.bits_0.pcsNetworkLoopback

                        Provisionable Default = 0x0

                        When set to 1, data after the Rx PCS layer will be looped back to the Tx PCS layer and transmitted back towards the network UTP line.
                        
  */
      unsigned int   pcsNetworkLoopback : 1;    /* 03.F800.0  R/WPD      Provisionable Default = 0x0 */
                     /* When set to 1, data after the Rx PCS layer will be looped back to the Tx PCS layer and transmitted back towards the network UTP line.
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorDebug_HHD;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Vendor Global Interrupt Flags: 03.FC00 */
/*                  PCS Vendor Global Interrupt Flags: 03.FC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Vendor Global Interrupt Flags */
  union
  {
    struct
    {
                    /*! \brief 03.FC00.F RO Standard Alarm 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.standardAlarm_1Interrupt

                        

                        1 = Interrupt in standard alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Standard Status 1 - Address 4.1 ) and the corresponding mask register ( See PHY XS Standard Transmit XAUI Rx Interrupt Mask 2 - Address 4.A001 ).  */
      unsigned int   standardAlarm_1Interrupt : 1;    /* 03.FC00.F  RO       */
                     /* 1 = Interrupt in standard alarms 1
                          */
                    /*! \brief 03.FC00.E RO Standard Alarm 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.standardAlarm_2Interrupt

                        

                        1 = Interrupt in standard alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Standard Vendor Devices in Package - Address 4.8 ) and the corresponding mask register ( See PHY XS Standard Transmit XAUI Rx Interrupt Mask 8 - Address 4.A008 ).  */
      unsigned int   standardAlarm_2Interrupt : 1;    /* 03.FC00.E  RO       */
                     /* 1 = Interrupt in standard alarms 2
                          */
                    /*! \brief 03.FC00.D RO Standard Alarm 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.standardAlarm_3Interrupt

                        

                        1 = Interrupt in standard alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS 10GBASE-T Status 2 - Address 3.21 ) and the corresponding mask register ( See PCS Standard Interrupt Mask 1 - Address 3.E021 ).  */
      unsigned int   standardAlarm_3Interrupt : 1;    /* 03.FC00.D  RO       */
                     /* 1 = Interrupt in standard alarms 3
                          */
      unsigned int   reserved0 : 1;
                    /*! \brief 03.FC00.B RO Vendor Specific Tx Alarms 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificTxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Vendor Alarms 3: Address 1E.CC02 ) and the corresponding mask register ( See PHY XS Transmit (XAUI Rx) Vendor LASI Interrupt Mask 3: Address 4.D402 ).  */
      unsigned int   vendorSpecificTxAlarms_1Interrupt : 1;    /* 03.FC00.B  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 1
                          */
                    /*! \brief 03.FC00.A RO Vendor Specific Tx Alarms 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificTxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Vendor XAUI Receive Alarms 1 - Address 4.B000 ) and the corresponding mask register ( See PCS Vendor Transmit PCS Interrupt Mask 1 - Address 3.A800 ).  */
      unsigned int   vendorSpecificTxAlarms_2Interrupt : 1;    /* 03.FC00.A  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 2
                          */
                    /*! \brief 03.FC00.9 RO Vendor Specific Tx Alarms 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificTxAlarms_3Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Transmit Vendor Alarms 3: Address 3.CC02 ) and the corresponding mask register ( See PCS Transmit Vendor LASI Interrupt Mask 3: Address 3.D402 ).  */
      unsigned int   vendorSpecificTxAlarms_3Interrupt : 1;    /* 03.FC00.9  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 3
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.FC00.6 RO Vendor Specific Rx Alarms 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificRxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Vendor Receive XAUI Tx Alarms 1- Address 4.D800 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 1: Address 3.F400 ).  */
      unsigned int   vendorSpecificRxAlarms_1Interrupt : 1;    /* 03.FC00.6  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 1
                          */
                    /*! \brief 03.FC00.5 RO Vendor Specific Rx Alarms 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificRxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Transmit Vendor Alarms 2: Address 3.CC00 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 1: Address 3.F400 ).  */
      unsigned int   vendorSpecificRxAlarms_2Interrupt : 1;    /* 03.FC00.5  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 2
                          */
                    /*! \brief 03.FC00.4 RO Vendor Specific Rx Alarms 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificRxAlarms_3Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 2 - Address 3.EC01 ) and the corresponding mask register ( See PCS Receive Vendor Interrupt Mask 2 - Address 3.EC01 ).  */
      unsigned int   vendorSpecificRxAlarms_3Interrupt : 1;    /* 03.FC00.4  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 3
                          */
                    /*! \brief 03.FC00.3 RO Vendor Specific Rx Alarms 4 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificRxAlarms_4Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 4
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 3 - Address 3.EC02 ) and the corresponding mask register ( See PCS Receive Vendor Interrupt Mask 3 - Address 3.F402 ).  */
      unsigned int   vendorSpecificRxAlarms_4Interrupt : 1;    /* 03.FC00.3  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 4
                          */
                    /*! \brief 03.FC00.2 RO Vendor Specific Rx Alarms 5 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u0.bits_0.vendorSpecificRxAlarms_5Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 5
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 4: Address 3.EC03 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 4: Address 3.F403 ).  */
      unsigned int   vendorSpecificRxAlarms_5Interrupt : 1;    /* 03.FC00.2  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 5
                          */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Dummy union to fill space in the structure PCS Vendor Global Interrupt Flags */
  union
  {
    struct
    {
      unsigned int   reserved : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Vendor Global Interrupt Flags */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 03.FC02.7 RO Vendor Specific Rx Alarms 6 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u2.bits_2.vendorSpecificRxAlarms_6Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 6
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 7: Address 3.EC06 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 7: Address 3.F406 ).  */
      unsigned int   vendorSpecificRxAlarms_6Interrupt : 1;    /* 03.FC02.7  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 6
                          */
                    /*! \brief 03.FC02.6 RO Vendor Specific Rx Alarms 7 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_HHD.u2.bits_2.vendorSpecificRxAlarms_7Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 7
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 7: Address 3.EC06 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 7: Address 3.F406 ).  */
      unsigned int   vendorSpecificRxAlarms_7Interrupt : 1;    /* 03.FC02.6  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 7
                          */
      unsigned int   reserved1 : 6;
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PcsVendorGlobalInterruptFlags_HHD;

#endif
/*@}*/
/*@}*/
