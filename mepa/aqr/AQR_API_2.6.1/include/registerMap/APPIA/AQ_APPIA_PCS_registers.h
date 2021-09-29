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
*   The bit fields in this structure are from LSbit to MSbit
*
***********************************************************************/


/*@{*/
#ifndef AQ_APPIA_PCS_REGS_HEADER
#define AQ_APPIA_PCS_REGS_HEADER


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
      unsigned int   reserved2 : 2;
                    /*! \brief 03.0000.5:2 ROS 10G Speed Selection [3:0]
                        AQ_PcsStandardControl_1_APPIA.u0.bits_0._10gSpeedSelection

                        Default = 0x0

                        1 x x x = Reserved
                        x 1 x x = Reserved
                        x x 1 x = Reserved
                        x x x 1 = Reserved
                        0 0 0 0 = 10 Gb/s
  */
      unsigned int   _10gSpeedSelection : 4;    /* 03.0000.5:2  ROS      Default = 0x0 */
                     /* 1 x x x = Reserved
                        x 1 x x = Reserved
                        x x 1 x = Reserved
                        x x x 1 = Reserved
                        0 0 0 0 = 10 Gb/s  */
                    /*! \brief 03.0000.6 R/WPD Speed Selection MSB
                        AQ_PcsStandardControl_1_APPIA.u0.bits_0.speedSelectionMsb

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
      unsigned int   reserved1 : 4;
                    /*! \brief 03.0000.B R/WPD Low Power
                        AQ_PcsStandardControl_1_APPIA.u0.bits_0.lowPower

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
      unsigned int   reserved0 : 1;
                    /*! \brief 03.0000.D R/WPD Speed Selection LSB
                        AQ_PcsStandardControl_1_APPIA.u0.bits_0.speedSelectionLsb

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
                    /*! \brief 03.0000.E R/WPD Loopback
                        AQ_PcsStandardControl_1_APPIA.u0.bits_0.loopback

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
                    /*! \brief 03.0000.F R/WSC Reset
                        AQ_PcsStandardControl_1_APPIA.u0.bits_0.reset

                        Default = 0x1

                        1 = PCS reset
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        The reset bit is automatically cleared upon completion of the reset sequence by the microcontroller. This bit is set to 1 during reset. The reset is internally stretched by approximately 1.7 us. Therefore the MDIO or uP should allow for 1.7 us before writing any PCS registers after this bit is set.  */
      unsigned int   reset : 1;    /* 03.0000.F  R/WSC      Default = 0x1 */
                     /* 1 = PCS reset
                        0 = Normal operation
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardControl_1_APPIA;


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
      unsigned int   reserved2 : 1;
                    /*! \brief 03.0001.1 ROS Low Power Ability
                        AQ_PcsStandardStatus_1_APPIA.u0.bits_0.lowPowerAbility

                        Default = 0x1

                        1 = PCS supports low-power mode
                        0 = no low-power mode supported

                 <B>Notes:</B>
                        Indicates whether the XAUI interface supports a low-power mode  */
      unsigned int   lowPowerAbility : 1;    /* 03.0001.1  ROS      Default = 0x1 */
                     /* 1 = PCS supports low-power mode
                        0 = no low-power mode supported  */
                    /*! \brief 03.0001.2 LL PCS Receive Link Status
                        AQ_PcsStandardStatus_1_APPIA.u0.bits_0.pcsReceiveLinkStatus

                        

                        Status of the PCS receive link
                        1 = Link up
                        0 = Link lost since last read
                        

                 <B>Notes:</B>
                        This indicates the status of the PCS receive link. This is a latching low version of Bit 3.20.C.  See PHY XS Standard XGXS Lane Status - Address 4.18   */
      unsigned int   pcsReceiveLinkStatus : 1;    /* 03.0001.2  LL       */
                     /* Status of the PCS receive link
                        1 = Link up
                        0 = Link lost since last read
                          */
      unsigned int   reserved1 : 4;
                    /*! \brief 03.0001.7 RO Fault
                        AQ_PcsStandardStatus_1_APPIA.u0.bits_0.fault

                        

                        1 = Fault condition detected
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        This is the top-level fault indicator flag for the PCS (aka XAUI) block, This bit is set if either of the two bits 3.8.B or 3.8.A are set.  */
      unsigned int   fault : 1;    /* 03.0001.7  RO       */
                     /* 1 = Fault condition detected
                        0 = No fault detected
                          */
      unsigned int   reserved0 : 8;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardStatus_1_APPIA;


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
                        AQ_PcsStandardDeviceIdentifier_APPIA.u0.bits_0.deviceIdMSW

                        

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
                        AQ_PcsStandardDeviceIdentifier_APPIA.u1.bits_1.deviceIdLSW

                        

                        Bits 15 - 0 of Device ID
  */
      unsigned int   deviceIdLSW : 16;    /* 03.0003.F:0  RO       */
                     /* Bits 15 - 0 of Device ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardDeviceIdentifier_APPIA;


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
                    /*! \brief 03.0004.0 ROS 10G Capable
                        AQ_PcsStandardSpeedAbility_APPIA.u0.bits_0._10gCapable

                        Default = 0x1

                        1 = PCS is 10 Gb/s capable
                        0 = PCS is not 10 Gb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.  */
      unsigned int   _10gCapable : 1;    /* 03.0004.0  ROS      Default = 0x1 */
                     /* 1 = PCS is 10 Gb/s capable
                        0 = PCS is not 10 Gb/s capable  */
      unsigned int   reserved0 : 15;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardSpeedAbility_APPIA;


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
                    /*! \brief 03.0005.0 ROS Clause 22 Registers Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u0.bits_0.clause_22RegistersPresent

                        Default = 0x0

                        1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package

                 <B>Notes:</B>
                        This is always set to 0 in the PHY, as there are no Clause 22 registers in the device.  */
      unsigned int   clause_22RegistersPresent : 1;    /* 03.0005.0  ROS      Default = 0x0 */
                     /* 1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package  */
                    /*! \brief 03.0005.1 ROS PMA Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u0.bits_0.pmaPresent

                        Default = 0x1

                        1 = PMA is present in package
                        0 = PMA is not present 

                 <B>Notes:</B>
                        This is always set to 1 as there is PMA functionality in the PHY.  */
      unsigned int   pmaPresent : 1;    /* 03.0005.1  ROS      Default = 0x1 */
                     /* 1 = PMA is present in package
                        0 = PMA is not present   */
                    /*! \brief 03.0005.2 ROS WIS Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u0.bits_0.wisPresent

                        Default = 0x0

                        1 = WIS is present in package
                        0 = WIS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no WIS functionality in the PHY.  */
      unsigned int   wisPresent : 1;    /* 03.0005.2  ROS      Default = 0x0 */
                     /* 1 = WIS is present in package
                        0 = WIS is not present in package  */
                    /*! \brief 03.0005.3 ROS PCS Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u0.bits_0.pcsPresent

                        Default = 0x1

                        1 = PCS is present in package
                        0 = PCS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is PCS functionality in the PHY.  */
      unsigned int   pcsPresent : 1;    /* 03.0005.3  ROS      Default = 0x1 */
                     /* 1 = PCS is present in package
                        0 = PCS is not present in package  */
                    /*! \brief 03.0005.4 ROS PHY XS Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u0.bits_0.phyXS_Present

                        Default = 0x1

                        1 = PHY XS is present in package
                        0 = PHY XS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is a PHY XS interface in the PHY.  */
      unsigned int   phyXS_Present : 1;    /* 03.0005.4  ROS      Default = 0x1 */
                     /* 1 = PHY XS is present in package
                        0 = PHY XS is not present in package  */
                    /*! \brief 03.0005.5 ROS DTE XS Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u0.bits_0.dteXsPresent

                        Default = 0x0

                        1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                        

                 <B>Notes:</B>
                        This is always set to 0, as there is no DTE XAUI interface in the PHY.  */
      unsigned int   dteXsPresent : 1;    /* 03.0005.5  ROS      Default = 0x0 */
                     /* 1 = DTE XS is present in package
                        0 = DTE XS is not present in package
                          */
                    /*! \brief 03.0005.6 ROS TC Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u0.bits_0.tcPresent

                        Default = 0x0

                        1 = TC is present in package
                        0 = TC is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no TC functionality in the PHY.  */
      unsigned int   tcPresent : 1;    /* 03.0005.6  ROS      Default = 0x0 */
                     /* 1 = TC is present in package
                        0 = TC is not present in package  */
                    /*! \brief 03.0005.7 ROS Autonegotiation Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u0.bits_0.autonegotiationPresent

                        Default = 0x1

                        1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package

                 <B>Notes:</B>
                        This is always set to 1, as there is Autonegotiation in the PHY.  */
      unsigned int   autonegotiationPresent : 1;    /* 03.0005.7  ROS      Default = 0x1 */
                     /* 1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package  */
      unsigned int   reserved0 : 8;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Standard Devices in Package */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 03.0006.D ROS Clause 22 Extension Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u1.bits_1.clause_22ExtensionPresent

                        Default = 0x1

                        1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the GbE registers.  */
      unsigned int   clause_22ExtensionPresent : 1;    /* 03.0006.D  ROS      Default = 0x1 */
                     /* 1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package  */
                    /*! \brief 03.0006.E ROS Vendor Specific Device #1 Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u1.bits_1.vendorSpecificDevice_1Present

                        Default = 0x1

                        1 = Device #1 is present in package
                        0 = Device #1 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the global control registers.  */
      unsigned int   vendorSpecificDevice_1Present : 1;    /* 03.0006.E  ROS      Default = 0x1 */
                     /* 1 = Device #1 is present in package
                        0 = Device #1 is not present in package  */
                    /*! \brief 03.0006.F ROS Vendor Specific Device #2 Present
                        AQ_PcsStandardDevicesInPackage_APPIA.u1.bits_1.vendorSpecificDevice_2Present

                        Default = 0x1

                        1 = Device #2 is present in package
                        0 = Device #2 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the DSP PMA registers.  */
      unsigned int   vendorSpecificDevice_2Present : 1;    /* 03.0006.F  ROS      Default = 0x1 */
                     /* 1 = Device #2 is present in package
                        0 = Device #2 is not present in package  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardDevicesInPackage_APPIA;


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
                    /*! \brief 03.0007.1:0 ROS PCS Device Type [1:0]
                        AQ_PcsStandardControl_2_APPIA.u0.bits_0.pcsDeviceType

                        Default = 0x3

                        [1:0]
                        0x3 = 10GBASE-T
                        0x2 = 10GBASE-W
                        0x1 = 10GBASE-X
                        0x0 = 10GBASE-R

                 <B>Notes:</B>
                        This is always set to 0x3 as the PHY only supports 10GBASE-T operation.  */
      unsigned int   pcsDeviceType : 2;    /* 03.0007.1:0  ROS      Default = 0x3 */
                     /* [1:0]
                        0x3 = 10GBASE-T
                        0x2 = 10GBASE-W
                        0x1 = 10GBASE-X
                        0x0 = 10GBASE-R  */
      unsigned int   reserved0 : 14;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardControl_2_APPIA;


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
                    /*! \brief 03.0008.0 ROS 10GBASE-R capable
                        AQ_PcsStandardStatus_2_APPIA.u0.bits_0._10gbase_rCapable

                        Default = 0x0

                        1 = PCS supports 10GBASE-R PCS type
                        0 = PCS does not support 10GBASE-R

                 <B>Notes:</B>
                        This field is always set to 0, as the PCS in the PHY only supports 10GBASE-T.  */
      unsigned int   _10gbase_rCapable : 1;    /* 03.0008.0  ROS      Default = 0x0 */
                     /* 1 = PCS supports 10GBASE-R PCS type
                        0 = PCS does not support 10GBASE-R  */
                    /*! \brief 03.0008.1 ROS 10GBASE-X capable
                        AQ_PcsStandardStatus_2_APPIA.u0.bits_0._10gbase_xCapable

                        Default = 0x0

                        1 = PCS supports 10GBASE-X PCS type
                        0 = PCS does not support 10GBASE-X

                 <B>Notes:</B>
                        This field is always set to 0, as the PCS in the PHY only supports 10GBASE-T.  */
      unsigned int   _10gbase_xCapable : 1;    /* 03.0008.1  ROS      Default = 0x0 */
                     /* 1 = PCS supports 10GBASE-X PCS type
                        0 = PCS does not support 10GBASE-X  */
                    /*! \brief 03.0008.2 ROS 10GBASE-W capable
                        AQ_PcsStandardStatus_2_APPIA.u0.bits_0._10gbase_wCapable

                        Default = 0x0

                        1 = PCS supports 10GBASE-W PCS type
                        0 = PCS does not support 10GBASE-W

                 <B>Notes:</B>
                        This field is always set to 0, as the PCS in the PHY only supports 10GBASE-T.  */
      unsigned int   _10gbase_wCapable : 1;    /* 03.0008.2  ROS      Default = 0x0 */
                     /* 1 = PCS supports 10GBASE-W PCS type
                        0 = PCS does not support 10GBASE-W  */
                    /*! \brief 03.0008.3 ROS 10GBASE-T capable
                        AQ_PcsStandardStatus_2_APPIA.u0.bits_0._10gbase_tCapable

                        Default = 0x1

                        1 = PCS supports 10GBASE-T PCS type
                        0 = PCS does not support 10GBASE-T

                 <B>Notes:</B>
                        This field is always set to 1, as the PCS in the PHY only supports 10GBASE-T.  */
      unsigned int   _10gbase_tCapable : 1;    /* 03.0008.3  ROS      Default = 0x1 */
                     /* 1 = PCS supports 10GBASE-T PCS type
                        0 = PCS does not support 10GBASE-T  */
      unsigned int   reserved1 : 6;
                    /*! \brief 03.0008.A LH Receive Fault
                        AQ_PcsStandardStatus_2_APPIA.u0.bits_0.receiveFault

                        

                        1 = Fault condition on receive path
                        0 = No fault condition on receive path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the receive path. This bit is duplicated at 3.EC04.2.  */
      unsigned int   receiveFault : 1;    /* 03.0008.A  LH       */
                     /* 1 = Fault condition on receive path
                        0 = No fault condition on receive path
                          */
                    /*! \brief 03.0008.B LH Transmit Fault
                        AQ_PcsStandardStatus_2_APPIA.u0.bits_0.transmitFault

                        

                        1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the transmit path. This bit is duplicated at 3.CC01.0.   */
      unsigned int   transmitFault : 1;    /* 03.0008.B  LH       */
                     /* 1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 03.0008.F:E ROS Device Present [1:0]
                        AQ_PcsStandardStatus_2_APPIA.u0.bits_0.devicePresent

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
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsStandardStatus_2_APPIA;


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
                        AQ_PcsStandardPackageIdentifier_APPIA.u0.bits_0.packageIdMSW

                        

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
                        AQ_PcsStandardPackageIdentifier_APPIA.u1.bits_1.packageIdLSW

                        

                        Bits 15 - 0 of Package ID
  */
      unsigned int   packageIdLSW : 16;    /* 03.000F.F:0  RO       */
                     /* Bits 15 - 0 of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsStandardPackageIdentifier_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS 10GBASE-T Status: 03.0020 */
/*                  PCS 10GBASE-T Status: 03.0020 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS 10GBASE-T Status */
  union
  {
    struct
    {
                    /*! \brief 03.0020.0 RO 10GBASE-T PCS Block Lock
                        AQ_Pcs10GBaseT_Status_APPIA.u0.bits_0._10gbase_tPcsBlockLock

                        

                        1 = 10GBASE-T PCS Framer is locked
                        0 = 10GBASE-T PCS Framer is not locked
                        

                 <B>Notes:</B>
                        When set, this bit indicates that 10GBASE-T PCS Framer has acquired frame synchronization and is locked. The interrupt for this bit is at 3.21.F.  */
      unsigned int   _10gbase_tPcsBlockLock : 1;    /* 03.0020.0  RO       */
                     /* 1 = 10GBASE-T PCS Framer is locked
                        0 = 10GBASE-T PCS Framer is not locked
                          */
                    /*! \brief 03.0020.1 RO 10GBASE-T High BER
                        AQ_Pcs10GBaseT_Status_APPIA.u0.bits_0._10gbase_tHighBer

                        

                        1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                        

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. The interrupt for this bit is at 3.21.E. The status bit for medium BER is found in  See Global Alarms 2: Address 1E.CC01 .  */
      unsigned int   _10gbase_tHighBer : 1;    /* 03.0020.1  RO       */
                     /* 1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                          */
      unsigned int   reserved1 : 10;
                    /*! \brief 03.0020.C RO 10GBASE-T Receive Link Status
                        AQ_Pcs10GBaseT_Status_APPIA.u0.bits_0._10gbase_tReceiveLinkStatus

                        

                        1 = 10GBASE-T Receive Link Up
                        0 = 10GBASE-T Receive Link Down
                        

                 <B>Notes:</B>
                        When set, this bit indicates that the 10GBASE-T Receive Link is functioning properly. This is a non-latching version of bit 3.1.2.  See PHY XS Standard Status 1 - Address 4.1  The Receive Link is up when the Block Lock status is asserted and the High BER is deasserted.)  */
      unsigned int   _10gbase_tReceiveLinkStatus : 1;    /* 03.0020.C  RO       */
                     /* 1 = 10GBASE-T Receive Link Up
                        0 = 10GBASE-T Receive Link Down
                          */
      unsigned int   reserved0 : 3;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS 10GBASE-T Status */
  union
  {
    struct
    {
                    /*! \brief 03.0021.7:0 SCT Errored 65B Block Counter [7:0]
                        AQ_Pcs10GBaseT_Status_APPIA.u1.bits_1.errored_65bBlockCounter

                        Default = 0x00

                        A saturating count of the number of times a bad 65B block is received
                        

                 <B>Notes:</B>
                        Clear on read. This is taken from the state machine in Figure 55.16 in the 10GBASE-T specification.  */
      unsigned int   errored_65bBlockCounter : 8;    /* 03.0021.7:0  SCT      Default = 0x00 */
                     /* A saturating count of the number of times a bad 65B block is received
                          */
                    /*! \brief 03.0021.D:8 SCT LDPC Errored Frame Counter [5:0]
                        AQ_Pcs10GBaseT_Status_APPIA.u1.bits_1.ldpcErroredFrameCounter

                        Default = 0x00

                        A saturating count of the number of times a bad LDPC frame is received
                        

                 <B>Notes:</B>
                        Clear on read. This is taken from the state machine in Figure 55.14 in the 10GBASE-T specification.  */
      unsigned int   ldpcErroredFrameCounter : 6;    /* 03.0021.D:8  SCT      Default = 0x00 */
                     /* A saturating count of the number of times a bad LDPC frame is received
                          */
                    /*! \brief 03.0021.E LH 10GBASE-T High BER Latched
                        AQ_Pcs10GBaseT_Status_APPIA.u1.bits_1._10gbase_tHighBerLatched

                        

                        1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                        

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. This is the interrupt for bit 3.20.1.  See PHY XS Standard XGXS Lane Status - Address 4.18   */
      unsigned int   _10gbase_tHighBerLatched : 1;    /* 03.0021.E  LH       */
                     /* 1 = PCS is reporting a BER  10-4
                        0 = PCS is reporting a BER < 10-4
                          */
                    /*! \brief 03.0021.F LL 10GBASE-T PCS Block Lock Latched
                        AQ_Pcs10GBaseT_Status_APPIA.u1.bits_1._10gbase_tPcsBlockLockLatched

                        

                        1 = 10GBASE-T PCS Framer is Locked
                        0 = 10GBASE-T PCS Framer is not locked
                        

                 <B>Notes:</B>
                        When set, this bit indicates that 10GBASE-T PCS Framer has acquired frame synchronization and is locked. This is the interrupt for bit 3.20.0.  See PHY XS Standard XGXS Lane Status - Address 4.18   */
      unsigned int   _10gbase_tPcsBlockLockLatched : 1;    /* 03.0021.F  LL       */
                     /* 1 = 10GBASE-T PCS Framer is Locked
                        0 = 10GBASE-T PCS Framer is not locked
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_Pcs10GBaseT_Status_APPIA;


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
                    /*! \brief 03.C400.0 R/WPD PCS Tx Auxilliary Bit Value
                        AQ_PcsTransmitVendorProvisioning_APPIA.u0.bits_0.pcsTxAuxilliaryBitValue

                        Provisionable Default = 0x0

                        The value that will be set in the auxilliary bit of the PCS transmission frame
                        

                 <B>Notes:</B>
                        This bit is currently undefined in the 802.3an standard.  */
      unsigned int   pcsTxAuxilliaryBitValue : 1;    /* 03.C400.0  R/WPD      Provisionable Default = 0x0 */
                     /* The value that will be set in the auxilliary bit of the PCS transmission frame
                          */
      unsigned int   reserved0 : 15;
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
} AQ_PcsTransmitVendorProvisioning_APPIA;


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
                    /*! \brief 03.C410.0 R/WPD PCS IEEE Loopback Passthrough Disable
                        AQ_PcsTransmitReservedVendorProvisioning_APPIA.u0.bits_0.pcsIEEE_LoopbackPassthroughDisable

                        Provisionable Default = 0x0

                        1 = Disable data passthrough on IEEE loopback
                        

                 <B>Notes:</B>
                        When set, this bit disables the output of the PHY when IEEE loopback is set.  */
      unsigned int   pcsIEEE_LoopbackPassthroughDisable : 1;    /* 03.C410.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable data passthrough on IEEE loopback
                          */
                    /*! \brief 03.C410.F:1 R/WPD Reserved Transmit Provisioning 1 [F:1]
                        AQ_PcsTransmitReservedVendorProvisioning_APPIA.u0.bits_0.reservedTransmitProvisioning_1

                        Provisionable Default = 0x0000

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_1 : 15;    /* 03.C410.F:1  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsTransmitReservedVendorProvisioning_APPIA;


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
                        AQ_PcsTransmitXfiVendorProvisioning_APPIA.u0.bits_0.xfiTestPatternSeedAWord_0

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
                        AQ_PcsTransmitXfiVendorProvisioning_APPIA.u1.bits_1.xfiTestPatternSeedAWord_1

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
                        AQ_PcsTransmitXfiVendorProvisioning_APPIA.u2.bits_2.xfiTestPatternSeedAWord_2

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
                    /*! \brief 03.C458.9:0 R/W XFI Test Pattern Seed A Word 3 [9:0]
                        AQ_PcsTransmitXfiVendorProvisioning_APPIA.u3.bits_3.xfiTestPatternSeedAWord_3

                        Default = 0x000

                        XFI test pattern seed A bits 57:48
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed A
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedAWord_3 : 10;    /* 03.C458.9:0  R/W      Default = 0x000 */
                     /* XFI test pattern seed A bits 57:48
                          */
      unsigned int   reserved0 : 6;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Transmit XFI Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C459.F:0 R/W XFI Test Pattern Seed B Word 0 [F:0]
                        AQ_PcsTransmitXfiVendorProvisioning_APPIA.u4.bits_4.xfiTestPatternSeedBWord_0

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
                        AQ_PcsTransmitXfiVendorProvisioning_APPIA.u5.bits_5.xfiTestPatternSeedBWord_1

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
                        AQ_PcsTransmitXfiVendorProvisioning_APPIA.u6.bits_6.xfiTestPatternSeedBWord_2

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
                    /*! \brief 03.C45C.9:0 R/W XFI Test Pattern Seed B Word 3 [9:0]
                        AQ_PcsTransmitXfiVendorProvisioning_APPIA.u7.bits_7.xfiTestPatternSeedBWord_3

                        Default = 0x000

                        XFI test pattern seed B bits 57:48
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Seed B
                        Used for both XFI0 and XFI1.  */
      unsigned int   xfiTestPatternSeedBWord_3 : 10;    /* 03.C45C.9:0  R/W      Default = 0x000 */
                     /* XFI test pattern seed B bits 57:48
                          */
      unsigned int   reserved0 : 6;
    } bits_7;
    uint16_t word_7;
  } u7;
} AQ_PcsTransmitXfiVendorProvisioning_APPIA;


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
      unsigned int   reserved1 : 1;
                    /*! \brief 03.C460.1 R/WPD XFI0 PCS Scrambler Disable
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u0.bits_0.xfi0PcsScramblerDisable

                        Provisionable Default = 0x0

                        1 = Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Scrambler Disable (default: 0)  */
      unsigned int   xfi0PcsScramblerDisable : 1;    /* 03.C460.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable PCS scrambler
                          */
      unsigned int   reserved0 : 14;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI0 Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C461.0 R/W XFI0 PCS Loss Of Lock Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0PcsLossOfLockInject

                        Default = 0x0

                        1 = Inject loss of lock
                        

                 <B>Notes:</B>
                        Inject error to cause loss of block_lock at far-end (default:0)  */
      unsigned int   xfi0PcsLossOfLockInject : 1;    /* 03.C461.0  R/W      Default = 0x0 */
                     /* 1 = Inject loss of lock
                          */
                    /*! \brief 03.C461.1 R/W XFI0 PCS High BER Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0PcsHighBerInject

                        Default = 0x0

                        1 = Inject PCS High BER
                        

                 <B>Notes:</B>
                        Inject error to cause HI_BER at far-end (default:0)  */
      unsigned int   xfi0PcsHighBerInject : 1;    /* 03.C461.1  R/W      Default = 0x0 */
                     /* 1 = Inject PCS High BER
                          */
                    /*! \brief 03.C461.2 R/W XFI0 Inject Single Error
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0InjectSingleError

                        Default = 0x0

                        1 = Inject single Error
                        

                 <B>Notes:</B>
                        Inject single error on the 10GBASE-R Test Pattern including pseudo-random, PRB31 or PRBS9 (default:0)  */
      unsigned int   xfi0InjectSingleError : 1;    /* 03.C461.2  R/W      Default = 0x0 */
                     /* 1 = Inject single Error
                          */
                    /*! \brief 03.C461.3 R/W XFI0 Local Fault Inject
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0LocalFaultInject

                        Default = 0x0

                        1 = Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault (default:0)  */
      unsigned int   xfi0LocalFaultInject : 1;    /* 03.C461.3  R/W      Default = 0x0 */
                     /* 1 = Inject local fault
                          */
                    /*! \brief 03.C461.4 R/W XFI0 Test Pattern Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0TestPatternEnable

                        Default = 0x0

                        1 = Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPatternEnable : 1;    /* 03.C461.4  R/W      Default = 0x0 */
                     /* 1 = Test pattern enabled
                          */
                    /*! \brief 03.C461.5 R/W XFI0 Test PRBS-31 Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0TestPrbs_31Enable

                        Default = 0x0

                        1 = Test pattern PRBS-31 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 31 Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPrbs_31Enable : 1;    /* 03.C461.5  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-31 enabled
                          */
                    /*! \brief 03.C461.6 R/W XFI0 Test PRBS-9 Enable
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0TestPrbs_9Enable

                        Default = 0x0

                        1 = Test pattern PRBS-9 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 9 Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi0TestPrbs_9Enable : 1;    /* 03.C461.6  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-9 enabled
                          */
                    /*! \brief 03.C461.7 R/W XFI0 Test Mode Select
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0TestModeSelect

                        Default = 0x0

                        1 = Test pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Select (0:Pseudo random, 1:Square wave, default:0)  */
      unsigned int   xfi0TestModeSelect : 1;    /* 03.C461.7  R/W      Default = 0x0 */
                     /* 1 = Test pattern select
                          */
                    /*! \brief 03.C461.8 R/W XFI0 Test Data Select
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0TestDataSelect

                        Default = 0x0

                        1 = Data pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Data Pattern Select (0:LF, 1:Zero, default:0)  */
      unsigned int   xfi0TestDataSelect : 1;    /* 03.C461.8  R/W      Default = 0x0 */
                     /* 1 = Data pattern select
                          */
                    /*! \brief 03.C461.9 R/W XFI0 Test Sqaure Wave Test Duration
                        AQ_PcsTransmitXfi0VendorProvisioning_APPIA.u1.bits_1.xfi0TestSqaureWaveTestDuration

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
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitXfi0VendorProvisioning_APPIA;


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
      unsigned int   reserved1 : 1;
                    /*! \brief 03.C470.1 R/WPD XFI1 PCS Scrambler Disable
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u0.bits_0.xfi1PcsScramblerDisable

                        Provisionable Default = 0x0

                        1 = Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Scrambler Disable (default: 0)  */
      unsigned int   xfi1PcsScramblerDisable : 1;    /* 03.C470.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable PCS scrambler
                          */
      unsigned int   reserved0 : 14;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XFI1 Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 03.C471.0 R/W XFI1 PCS Loss Of Lock Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1PcsLossOfLockInject

                        Default = 0x0

                        1 = Inject loss of lock
                        

                 <B>Notes:</B>
                        Inject error to cause loss of block_lock at far-end (default:0)  */
      unsigned int   xfi1PcsLossOfLockInject : 1;    /* 03.C471.0  R/W      Default = 0x0 */
                     /* 1 = Inject loss of lock
                          */
                    /*! \brief 03.C471.1 R/W XFI1 PCS High BER Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1PcsHighBerInject

                        Default = 0x0

                        1 = Inject PCS High BER
                        

                 <B>Notes:</B>
                        Inject error to cause HI_BER at far-end (default:0)  */
      unsigned int   xfi1PcsHighBerInject : 1;    /* 03.C471.1  R/W      Default = 0x0 */
                     /* 1 = Inject PCS High BER
                          */
                    /*! \brief 03.C471.2 R/W XFI1 Inject Single Error
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1InjectSingleError

                        Default = 0x0

                        1 = Inject single Error
                        

                 <B>Notes:</B>
                        Inject single error on the 10GBASE-R Test Pattern including pseudo-random, PRB31 or PRBS9 (default:0)  */
      unsigned int   xfi1InjectSingleError : 1;    /* 03.C471.2  R/W      Default = 0x0 */
                     /* 1 = Inject single Error
                          */
                    /*! \brief 03.C471.3 R/W XFI1 Local Fault Inject
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1LocalFaultInject

                        Default = 0x0

                        1 = Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault (default:0)  */
      unsigned int   xfi1LocalFaultInject : 1;    /* 03.C471.3  R/W      Default = 0x0 */
                     /* 1 = Inject local fault
                          */
                    /*! \brief 03.C471.4 R/W XFI1 Test Pattern Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1TestPatternEnable

                        Default = 0x0

                        1 = Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable (0:disable, 1:enable, default:0)  */
      unsigned int   xfi1TestPatternEnable : 1;    /* 03.C471.4  R/W      Default = 0x0 */
                     /* 1 = Test pattern enabled
                          */
                    /*! \brief 03.C471.5 R/W XFI1 Test PRBS-31 Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1TestPrbs_31Enable

                        Default = 0x0

                        1 = Test pattern PRBS-31 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 31 Test Pattern Enable (0:disable, 1:enable, default:0)
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   xfi1TestPrbs_31Enable : 1;    /* 03.C471.5  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-31 enabled
                          */
                    /*! \brief 03.C471.6 R/W XFI1 Test PRBS-9 Enable
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1TestPrbs_9Enable

                        Default = 0x0

                        1 = Test pattern PRBS-9 enabled
                        

                 <B>Notes:</B>
                        10GBASE-R PRBS 9 Test Pattern Enable (0:disable, 1:enable, default:0)
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   xfi1TestPrbs_9Enable : 1;    /* 03.C471.6  R/W      Default = 0x0 */
                     /* 1 = Test pattern PRBS-9 enabled
                          */
                    /*! \brief 03.C471.7 R/W XFI1 Test Mode Select
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1TestModeSelect

                        Default = 0x0

                        1 = Test pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Test Pattern Select (0:Pseudo random, 1:Square wave, default:0)  */
      unsigned int   xfi1TestModeSelect : 1;    /* 03.C471.7  R/W      Default = 0x0 */
                     /* 1 = Test pattern select
                          */
                    /*! \brief 03.C471.8 R/W XFI1 Test Data Select
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1TestDataSelect

                        Default = 0x0

                        1 = Data pattern select
                        

                 <B>Notes:</B>
                        10GBASE-R Data Pattern Select (0:LF, 1:Zero, default:0)  */
      unsigned int   xfi1TestDataSelect : 1;    /* 03.C471.8  R/W      Default = 0x0 */
                     /* 1 = Data pattern select
                          */
                    /*! \brief 03.C471.9 R/W XFI1 Test Sqaure Wave Test Duration
                        AQ_PcsTransmitXfi1VendorProvisioning_APPIA.u1.bits_1.xfi1TestSqaureWaveTestDuration

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
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitXfi1VendorProvisioning_APPIA;


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
                        AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA.u0.bits_0._10gbase_tGoodFrameCounterLSW

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
                    /*! \brief 03.C821.9:0 SCTM 10GBASE-T Good Frame Counter MSW [19:10]
                        AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA.u1.bits_1._10gbase_tGoodFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterMSW : 10;    /* 03.C821.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Good Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitVendorFcsNoErrorFrameCounter_APPIA;


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
                        AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA.u0.bits_0._10gbase_tErrorFrameCounterLSW

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
                    /*! \brief 03.C823.9:0 SCTM 10GBASE-T Error Frame Counter MSW [19:10]
                        AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA.u1.bits_1._10gbase_tErrorFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterMSW : 10;    /* 03.C823.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Bad Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsTransmitVendorFcsErrorFrameCounter_APPIA;


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
                        AQ_PcsTransmitXfi0VendorState_APPIA.u0.bits_0.xfi0GoodFrameCounterLSW

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
                    /*! \brief 03.C861.9:0 SCTM XFI0 Good Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi0VendorState_APPIA.u1.bits_1.xfi0GoodFrameCounterMSW

                        Default = 0x000

                        XFI0 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterMSW : 10;    /* 03.C861.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Good Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C862.F:0 SCTL XFI0 Bad Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi0VendorState_APPIA.u2.bits_2.xfi0BadFrameCounterLSW

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
                    /*! \brief 03.C863.9:0 SCTM XFI0 Bad Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi0VendorState_APPIA.u3.bits_3.xfi0BadFrameCounterMSW

                        Default = 0x000

                        XFI0 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterMSW : 10;    /* 03.C863.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Bad Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitXfi0VendorState_APPIA;


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
                        AQ_PcsTransmitXfi1VendorState_APPIA.u0.bits_0.xfi1GoodFrameCounterLSW

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
                    /*! \brief 03.C871.9:0 SCTM XFI1 Good Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi1VendorState_APPIA.u1.bits_1.xfi1GoodFrameCounterMSW

                        Default = 0x000

                        XFI1 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterMSW : 10;    /* 03.C871.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Good Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C872.F:0 SCTL XFI1 Bad Frame Counter LSW [F:0]
                        AQ_PcsTransmitXfi1VendorState_APPIA.u2.bits_2.xfi1BadFrameCounterLSW

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
                    /*! \brief 03.C873.9:0 SCTM XFI1 Bad Frame Counter MSW [9:0]
                        AQ_PcsTransmitXfi1VendorState_APPIA.u3.bits_3.xfi1BadFrameCounterMSW

                        Default = 0x000

                        XFI1 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterMSW : 10;    /* 03.C873.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Bad Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PcsTransmitXfi1VendorState_APPIA;


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
                    /*! \brief 03.C880.7:0 SCT XGS Collision Events Counter 0 [7:0]
                        AQ_PcsTransmitXgsVendorState_APPIA.u0.bits_0.xgsCollisionEventsCounter_0

                        Default = 0x00

                        XGS collision events: Byte location from 1 to 64 bytes counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 1 to 64 counter  */
      unsigned int   xgsCollisionEventsCounter_0 : 8;    /* 03.C880.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 1 to 64 bytes counter
                          */
      unsigned int   reserved0 : 8;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C881.7:0 SCT XGS Collision Events Counter 1 [7:0]
                        AQ_PcsTransmitXgsVendorState_APPIA.u1.bits_1.xgsCollisionEventsCounter_1

                        Default = 0x00

                        XGS collision events: Byte location from 65 to 96 bytes counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 65 to 96 counter  */
      unsigned int   xgsCollisionEventsCounter_1 : 8;    /* 03.C881.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 65 to 96 bytes counter
                          */
      unsigned int   reserved0 : 8;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C882.7:0 SCT XGS Collision Events Counter 2 [7:0]
                        AQ_PcsTransmitXgsVendorState_APPIA.u2.bits_2.xgsCollisionEventsCounter_2

                        Default = 0x00

                        XGS collision events: Byte location from 97 to 128 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 97 to 128 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_2 : 8;    /* 03.C882.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 97 to 128 counter
                          */
      unsigned int   reserved0 : 8;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C883.7:0 SCT XGS Collision Events Counter 3 [7:0]
                        AQ_PcsTransmitXgsVendorState_APPIA.u3.bits_3.xgsCollisionEventsCounter_3

                        Default = 0x00

                        XGS collision events: Byte location from 129 to 192 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 129 to 192 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_3 : 8;    /* 03.C883.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 129 to 192 counter
                          */
      unsigned int   reserved0 : 8;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Transmit XGS Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.C884.7:0 SCT XGS Collision Events Counter 4 [7:0]
                        AQ_PcsTransmitXgsVendorState_APPIA.u4.bits_4.xgsCollisionEventsCounter_4

                        Default = 0x00

                        XGS collision events: Byte location from 193 to 320 counter
                        

                 <B>Notes:</B>
                        1G/100M PHY collision events: Byte location from 193 to 320 bytes counter  */
      unsigned int   xgsCollisionEventsCounter_4 : 8;    /* 03.C884.7:0  SCT      Default = 0x00 */
                     /* XGS collision events: Byte location from 193 to 320 counter
                          */
      unsigned int   reserved0 : 8;
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_PcsTransmitXgsVendorState_APPIA;


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
                    /*! \brief 03.CC00.0 LH XAUI Transmit Invalid 64B Block Detected
                        AQ_PcsTransmitVendorAlarms_APPIA.u0.bits_0.xauiTransmitInvalid_64bBlockDetected

                        

                        1 = Bad 64B block detected
                        
  */
      unsigned int   xauiTransmitInvalid_64bBlockDetected : 1;    /* 03.CC00.0  LH       */
                     /* 1 = Bad 64B block detected
                          */
                    /*! \brief 03.CC00.F:1 LH Reserved PCS Transmit Vendor Alarms 1 [F:1]
                        AQ_PcsTransmitVendorAlarms_APPIA.u0.bits_0.reservedPcsTransmitVendorAlarms_1

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_1 : 15;    /* 03.CC00.F:1  LH       */
                     /* Reserved for future use  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.CC01.F:0 LH Reserved PCS Transmit Vendor Alarms 2 [F:0]
                        AQ_PcsTransmitVendorAlarms_APPIA.u1.bits_1.reservedPcsTransmitVendorAlarms_2

                        

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
                        AQ_PcsTransmitVendorAlarms_APPIA.u2.bits_2.reservedPcsTransmitVendorAlarms_3

                        

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
                    /*! \brief 03.CC03.0 LH XFI0 Transmit LOF Detected
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.xfi0TransmitLofDetected

                        

                        1 = Loss of frame detected
                        
  */
      unsigned int   xfi0TransmitLofDetected : 1;    /* 03.CC03.0  LH       */
                     /* 1 = Loss of frame detected
                          */
      unsigned int   reserved2 : 2;
                    /*! \brief 03.CC03.3 LH XFI0 Transmit 64B Encode Error
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.xfi0Transmit_64bEncodeError

                        

                        1 = 64B Encode Error
                        
  */
      unsigned int   xfi0Transmit_64bEncodeError : 1;    /* 03.CC03.3  LH       */
                     /* 1 = 64B Encode Error
                          */
                    /*! \brief 03.CC03.4 LH XFI0 Transmit Reserved XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.xfi0TransmitReservedXgmiiCharacterReceived

                        

                        1 = Reserved XGMII Character Received
                        
  */
      unsigned int   xfi0TransmitReservedXgmiiCharacterReceived : 1;    /* 03.CC03.4  LH       */
                     /* 1 = Reserved XGMII Character Received
                          */
                    /*! \brief 03.CC03.5 LH XFI0 Transmit Invalid XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.xfi0TransmitInvalidXgmiiCharacterReceived

                        

                        1 = Invalid XGMII Character Received
                        
  */
      unsigned int   xfi0TransmitInvalidXgmiiCharacterReceived : 1;    /* 03.CC03.5  LH       */
                     /* 1 = Invalid XGMII Character Received
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.CC03.8 LH XFI1 Transmit LOF Detected
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.xfi1TransmitLofDetected

                        

                        1 = Loss of Frame detected
                        
  */
      unsigned int   xfi1TransmitLofDetected : 1;    /* 03.CC03.8  LH       */
                     /* 1 = Loss of Frame detected
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 03.CC03.B LH XFI1 Transmit 64B Encode Error
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.xfi1Transmit_64bEncodeError

                        

                        1 = 64B Encode Error
                        
  */
      unsigned int   xfi1Transmit_64bEncodeError : 1;    /* 03.CC03.B  LH       */
                     /* 1 = 64B Encode Error
                          */
                    /*! \brief 03.CC03.C LH XFI1 Transmit Reserved XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.xfi1TransmitReservedXgmiiCharacterReceived

                        

                        1 = Reserved XGMII Character Received
                        
  */
      unsigned int   xfi1TransmitReservedXgmiiCharacterReceived : 1;    /* 03.CC03.C  LH       */
                     /* 1 = Reserved XGMII Character Received
                          */
                    /*! \brief 03.CC03.D LH XFI1 Transmit Invalid XGMII Character Received
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.xfi1TransmitInvalidXgmiiCharacterReceived

                        

                        1 = Invalid XGMII Character Received
                        
  */
      unsigned int   xfi1TransmitInvalidXgmiiCharacterReceived : 1;    /* 03.CC03.D  LH       */
                     /* 1 = Invalid XGMII Character Received
                          */
                    /*! \brief 03.CC03.F:E LH Reserved PCS Transmit Vendor Alarms 4 [1:0]
                        AQ_PcsTransmitVendorAlarms_APPIA.u3.bits_3.reservedPcsTransmitVendorAlarms_4

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_4 : 2;    /* 03.CC03.F:E  LH       */
                     /* Reserved for future use  */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Transmit Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.CC04.F:0 LH Reserved PCS Transmit Vendor Alarms 5 [F:0]
                        AQ_PcsTransmitVendorAlarms_APPIA.u4.bits_4.reservedPcsTransmitVendorAlarms_5

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsTransmitVendorAlarms_5 : 16;    /* 03.CC04.F:0  LH       */
                     /* Reserved for future use  */
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_PcsTransmitVendorAlarms_APPIA;


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
                    /*! \brief 03.D400.0 R/WPD XAUI Transmit Invalid 64B Block Detected Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u0.bits_0.xauiTransmitInvalid_64bBlockDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiTransmitInvalid_64bBlockDetectedMask : 1;    /* 03.D400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.D400.F:1 R/WPD Reserved PCS Transmit Vendor Alarms 1 Mask [F:1]
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u0.bits_0.reservedPcsTransmitVendorAlarms_1Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsTransmitVendorAlarms_1Mask : 15;    /* 03.D400.F:1  R/WPD      Provisionable Default = 0x0000 */
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
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u1.bits_1.reservedPcsTransmitVendorAlarms_2Mask

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
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u2.bits_2.reservedPcsTransmitVendorAlarms_3Mask

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
                    /*! \brief 03.D403.0 R/WPD XFI0 Transmit LOF Detected Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u3.bits_3.xfi0TransmitLofDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitLofDetectedMask : 1;    /* 03.D403.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved3 : 2;
                    /*! \brief 03.D403.3 R/WPD XFI0 Transmit Encode 64B Error Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u3.bits_3.xfi0TransmitEncode_64bErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitEncode_64bErrorMask : 1;    /* 03.D403.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.4 R/WPD XFI0 Transmit Reserved XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u3.bits_3.xfi0TransmitReservedXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitReservedXgmiiCharacterErrorMask : 1;    /* 03.D403.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.5 R/WPD XFI0 Transmit Invalid XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u3.bits_3.xfi0TransmitInvalidXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0TransmitInvalidXgmiiCharacterErrorMask : 1;    /* 03.D403.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved2 : 2;
                    /*! \brief 03.D403.8 R/WPD XFI1 Transmit LOF Detected Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u3.bits_3.xfi1TransmitLofDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitLofDetectedMask : 1;    /* 03.D403.8  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 03.D403.B R/WPD XFI1 Transmit Encode 64B Error Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u3.bits_3.xfi1TransmitEncode_64bErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitEncode_64bErrorMask : 1;    /* 03.D403.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.C R/WPD XFI1 Transmit Reserved XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u3.bits_3.xfi1TransmitReservedXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitReservedXgmiiCharacterErrorMask : 1;    /* 03.D403.C  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.D403.D R/WPD XFI1 Transmit Invalid XGMII Character Error Mask
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u3.bits_3.xfi1TransmitInvalidXgmiiCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1TransmitInvalidXgmiiCharacterErrorMask : 1;    /* 03.D403.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved0 : 2;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Transmit Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.D404.F:0 R/WPD Reserved PCS Transmit Vendor Alarms 5 Mask [F:0]
                        AQ_PcsTransmitVendorInterruptMask_APPIA.u4.bits_4.reservedPcsTransmitVendorAlarms_5Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsTransmitVendorAlarms_5Mask : 16;    /* 03.D404.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_PcsTransmitVendorInterruptMask_APPIA;


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
      unsigned int   reserved0 : 13;
                    /*! \brief 03.D800.D R/W PCS Tx Inject Frame Error
                        AQ_PcsTransmitVendorDebug_APPIA.u0.bits_0.pcsTxInjectFrameError

                        Default = 0x0

                        1 = Inject frame error
                        

                 <B>Notes:</B>
                        Setting this bit injects an error at the location contained in Bits C:0 in the next PCS transmission frame.  */
      unsigned int   pcsTxInjectFrameError : 1;    /* 03.D800.D  R/W      Default = 0x0 */
                     /* 1 = Inject frame error
                          */
                    /*! \brief 03.D800.E R/W PCS Tx Inject CRC Error
                        AQ_PcsTransmitVendorDebug_APPIA.u0.bits_0.pcsTxInjectCrcError

                        Default = 0x0

                        1 = Inject CRC Error
                        

                 <B>Notes:</B>
                        Setting this bit injects a CRC error in a single frame.  */
      unsigned int   pcsTxInjectCrcError : 1;    /* 03.D800.E  R/W      Default = 0x0 */
                     /* 1 = Inject CRC Error
                          */
                    /*! \brief 03.D800.F R/WPD PCS Tx Scrambler Disable
                        AQ_PcsTransmitVendorDebug_APPIA.u0.bits_0.pcsTxScramblerDisable

                        Provisionable Default = 0x0

                        1 = Tx Scrambler Disabled
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        Setting this bit disables the Tx scrambler during regular data transmission (i.e. scrambler functionality during training and startup is unmodified).  */
      unsigned int   pcsTxScramblerDisable : 1;    /* 03.D800.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Tx Scrambler Disabled
                        0 = Normal Operation
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsTransmitVendorDebug_APPIA;


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
                    /*! \brief 03.E400.0 R/WPD PCS Rx Error LDPC Frame Enable
                        AQ_PcsReceiveVendorProvisioning_APPIA.u0.bits_0.pcsRxErrorLdpcFrameEnable

                        Provisionable Default = 0x1

                        1 = Enable erroring the LDPC frame payload
                        0 = Disable erroring the LDPC frame payload
                        

                 <B>Notes:</B>
                        Error the entire LDPC frame payload upon uncorrectable LDPC parity or CRC error.
                          */
      unsigned int   pcsRxErrorLdpcFrameEnable : 1;    /* 03.E400.0  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = Enable erroring the LDPC frame payload
                        0 = Disable erroring the LDPC frame payload
                          */
      unsigned int   reserved0 : 14;
                    /*! \brief 03.E400.F R/WPD PCS Rx LDPC Decoder Control
                        AQ_PcsReceiveVendorProvisioning_APPIA.u0.bits_0.pcsRxLdpcDecoderControl

                        Provisionable Default = 0x1

                        1 = LDPC with Elastic store
                        0 = No LDPC decode
                        

                 <B>Notes:</B>
                        If the LDPC decoder is disabled, the LDPC decoder latency is eliminated, but there is no longer any error correction. This bit disables the clock when set to 0.   */
      unsigned int   pcsRxLdpcDecoderControl : 1;    /* 03.E400.F  R/WPD      Provisionable Default = 0x1 */
                     /* 1 = LDPC with Elastic store
                        0 = No LDPC decode
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorProvisioning_APPIA;


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
      unsigned int   reserved1 : 1;
                    /*! \brief 03.E460.1 R/W XFI0 Rx Descrambler Disable
                        AQ_PcsReceiveXfi0Provisioning_APPIA.u0.bits_0.xfi0RxDescramblerDisable

                        Default = 0x0

                        1 = XFI0 Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Descrambler Disable  */
      unsigned int   xfi0RxDescramblerDisable : 1;    /* 03.E460.1  R/W      Default = 0x0 */
                     /* 1 = XFI0 Disable PCS scrambler
                          */
      unsigned int   reserved0 : 14;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI0 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved1 : 3;
                    /*! \brief 03.E461.3 R/W XFI0 Local Fault Inject
                        AQ_PcsReceiveXfi0Provisioning_APPIA.u1.bits_1.xfi0LocalFaultInject

                        Default = 0x0

                        1 = XFI0 Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault  */
      unsigned int   xfi0LocalFaultInject : 1;    /* 03.E461.3  R/W      Default = 0x0 */
                     /* 1 = XFI0 Inject local fault
                          */
                    /*! \brief 03.E461.4 R/W Test Pattern Enable
                        AQ_PcsReceiveXfi0Provisioning_APPIA.u1.bits_1.testPatternEnable

                        Default = 0x0

                        1 = Enable test pattern
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable - see the external view for an explanation  */
      unsigned int   testPatternEnable : 1;    /* 03.E461.4  R/W      Default = 0x0 */
                     /* 1 = Enable test pattern
                          */
                    /*! \brief 03.E461.7:5 R/W XFI0 Test Mode Select [2:0]
                        AQ_PcsReceiveXfi0Provisioning_APPIA.u1.bits_1.xfi0TestModeSelect

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
                    /*! \brief 03.E461.8 R/W XFI0 Test Data Source
                        AQ_PcsReceiveXfi0Provisioning_APPIA.u1.bits_1.xfi0TestDataSource

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
      unsigned int   reserved0 : 7;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveXfi0Provisioning_APPIA;


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
      unsigned int   reserved1 : 1;
                    /*! \brief 03.E470.1 R/W XFI1 Rx Descrambler Disable
                        AQ_PcsReceiveXfi1Provisioning_APPIA.u0.bits_0.xfi1RxDescramblerDisable

                        Default = 0x0

                        1 = XFI1 Disable PCS scrambler
                        

                 <B>Notes:</B>
                        PCS Descrambler Disable  */
      unsigned int   xfi1RxDescramblerDisable : 1;    /* 03.E470.1  R/W      Default = 0x0 */
                     /* 1 = XFI1 Disable PCS scrambler
                          */
      unsigned int   reserved0 : 14;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive XFI1 Provisioning */
  union
  {
    struct
    {
      unsigned int   reserved1 : 3;
                    /*! \brief 03.E471.3 R/W XFI1 Local Fault Inject
                        AQ_PcsReceiveXfi1Provisioning_APPIA.u1.bits_1.xfi1LocalFaultInject

                        Default = 0x0

                        1 = XFI1 Inject local fault
                        

                 <B>Notes:</B>
                        Inject Local_Fault  */
      unsigned int   xfi1LocalFaultInject : 1;    /* 03.E471.3  R/W      Default = 0x0 */
                     /* 1 = XFI1 Inject local fault
                          */
                    /*! \brief 03.E471.4 R/W Test Pattern Enable
                        AQ_PcsReceiveXfi1Provisioning_APPIA.u1.bits_1.testPatternEnable

                        Default = 0x0

                        1 = Test pattern enabled
                        

                 <B>Notes:</B>
                        10GBASE-R Pseudo-Random Test Pattern Enable - see the external view for an explanation  */
      unsigned int   testPatternEnable : 1;    /* 03.E471.4  R/W      Default = 0x0 */
                     /* 1 = Test pattern enabled
                          */
                    /*! \brief 03.E471.7:5 R/W XFI1 Test Mode Select [2:0]
                        AQ_PcsReceiveXfi1Provisioning_APPIA.u1.bits_1.xfi1TestModeSelect

                        Default = 0x0

                        Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random

                 <B>Notes:</B>
                        Note that the source for the pseudo-random test is determined by Bit 8.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   xfi1TestModeSelect : 3;    /* 03.E471.7:5  R/W      Default = 0x0 */
                     /* Test Pattern Select:
                        xx1 = PRBS-31
                        x10 = PRBS-9
                        100 = Square-wave
                        000 = Pseudo-random  */
                    /*! \brief 03.E471.8 R/W XFI1 Test Data Source
                        AQ_PcsReceiveXfi1Provisioning_APPIA.u1.bits_1.xfi1TestDataSource

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
      unsigned int   reserved0 : 7;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveXfi1Provisioning_APPIA;


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
                    /*! \brief 03.E800.0 RO PCS Rx Current Value of Auxilliary Bit
                        AQ_PcsReceiveVendorState_APPIA.u0.bits_0.pcsRxCurrentValueOfAuxilliaryBit

                        

                        The current value of the PCS Rx auxilliary bit
                        

                 <B>Notes:</B>
                        This value has a maskable interrupt associated with it in 3.EC00.0.  */
      unsigned int   pcsRxCurrentValueOfAuxilliaryBit : 1;    /* 03.E800.0  RO       */
                     /* The current value of the PCS Rx auxilliary bit
                          */
      unsigned int   reserved0 : 15;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorState_APPIA;


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
                        AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA.u0.bits_0.crc_8ErrorCounterLSW

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
                    /*! \brief 03.E811.5:0 SCTM CRC-8 Error Counter MSW [15:10]
                        AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA.u1.bits_1.crc_8ErrorCounterMSW

                        Default = 0x00

                        Upper 6 bits of CRC-8 error counter
                        

                 <B>Notes:</B>
                        The MSW of the counter must be read immediately after the LSW of the counter is read. The MSW is actually a shadow copy of the MSW of the counter and is loaded after the LSW of the counter is read. A saturating counter that counts the number of CRC-8 errors (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   crc_8ErrorCounterMSW : 6;    /* 03.E811.5:0  SCTM      Default = 0x00 */
                     /* Upper 6 bits of CRC-8 error counter
                          */
      unsigned int   reserved0 : 10;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorCrc_8ErrorCounter_APPIA;


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
                        AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA.u0.bits_0._10gbase_tGoodFrameCounterLSW

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
                    /*! \brief 03.E813.9:0 SCTM 10GBASE-T Good Frame Counter MSW [19:10]
                        AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA.u1.bits_1._10gbase_tGoodFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tGoodFrameCounterMSW : 10;    /* 03.E813.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Good Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorFcsNoErrorFrameCounter_APPIA;


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
                        AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA.u0.bits_0._10gbase_tErrorFrameCounterLSW

                        Default = 0x0000

                        10GBASE-T Bad Frame Counter LSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. no Ethernet CRC-32 / FCS errors).  */
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
                    /*! \brief 03.E815.9:0 SCTM 10GBASE-T Error Frame Counter MSW [19:10]
                        AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA.u1.bits_1._10gbase_tErrorFrameCounterMSW

                        Default = 0x000

                        10GBASE-T Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   _10gbase_tErrorFrameCounterMSW : 10;    /* 03.E815.9:0  SCTM      Default = 0x000 */
                     /* 10GBASE-T Bad Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PcsReceiveVendorFcsErrorFrameCounter_APPIA;


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
                        AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA.u0.bits_0.uncorrectedFrameCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC uncorrected frames which the decoder abandoned
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of uncorrected frames.  */
      unsigned int   uncorrectedFrameCounterLSW : 16;    /* 03.E820.F:0  SCTL      Default = 0x0000 */
                     /* Lower 16 bits of LDPC uncorrected frames which the decoder abandoned
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
                        AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA.u1.bits_1.uncorrectedFrameCounterMSW

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
} AQ_PcsReceiveVendorUncorrectedFrameCounter_APPIA;


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
                        AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA.u0.bits_0.correctedFrames_1IterationCounterLSW

                        Default = 0x0000

                        Lower 16 bits of LDPC corrected frames which converged in 1 iteration
                        

                 <B>Notes:</B>
                        When the LSW is read, the MSW will be copied to a shadow register and then both the LSW and MSW are cleared. The LSW of the counter must be read first. The MSW of the counter must be read immediately after the LSW is read. A saturating counter that counts the number of corrected frames which converged in 1 iteration.bit.  */
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
                        AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA.u1.bits_1.correctedFrames_1IterationCounterMSW

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
} AQ_PcsReceiveVendorCorrectedFrame_1IterationCounter_APPIA;


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
                        AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA.u0.bits_0.correctedFrames_2IterationCounterLSW

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
                        AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA.u1.bits_1.correctedFrames_2IterationCounterMSW

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
} AQ_PcsReceiveVendorCorrectedFrame_2IterationCounter_APPIA;


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
                        AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA.u0.bits_0.correctedFrames_3IterationCounterLSW

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
                        AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA.u1.bits_1.correctedFrames_3IterationCounterMSW

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
} AQ_PcsReceiveVendorCorrectedFrame_3IterationCounter_APPIA;


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
                        AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA.u0.bits_0.correctedFrames_4IterationCounterLSW

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
                        AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA.u1.bits_1.correctedFrames_4IterationCounterMSW

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
} AQ_PcsReceiveVendorCorrectedFrame_4IterationCounter_APPIA;


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
                        AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA.u0.bits_0.correctedFrames_5IterationCounterLSW

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
                        AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA.u1.bits_1.correctedFrames_5IterationCounterMSW

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
} AQ_PcsReceiveVendorCorrectedFrame_5IterationCounter_APPIA;


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
                        AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA.u0.bits_0.correctedFrames_6IterationCounter

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
} AQ_PcsReceiveVendorCorrectedFrame_6IterationCounter_APPIA;


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
                        AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA.u0.bits_0.correctedFrames_7IterationCounter

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
} AQ_PcsReceiveVendorCorrectedFrame_7IterationCounter_APPIA;


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
                        AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA.u0.bits_0.correctedFrames_8IterationCounter

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
} AQ_PcsReceiveVendorCorrectedFrame_8IterationCounter_APPIA;


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
                        AQ_PcsReceiveXfi0VendorState_APPIA.u0.bits_0.xfi0GoodFrameCounterLSW

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
                    /*! \brief 03.E861.9:0 SCTM XFI0 Good Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi0VendorState_APPIA.u1.bits_1.xfi0GoodFrameCounterMSW

                        Default = 0x000

                        XFI0 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0GoodFrameCounterMSW : 10;    /* 03.E861.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Good Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E862.F:0 SCTL XFI0 Bad Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi0VendorState_APPIA.u2.bits_2.xfi0BadFrameCounterLSW

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
                    /*! \brief 03.E863.9:0 SCTM XFI0 Bad Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi0VendorState_APPIA.u3.bits_3.xfi0BadFrameCounterMSW

                        Default = 0x000

                        XFI0 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi0BadFrameCounterMSW : 10;    /* 03.E863.9:0  SCTM      Default = 0x000 */
                     /* XFI0 Bad Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E864.5:0 SCT XFI0 BER Counter [5:0]
                        AQ_PcsReceiveXfi0VendorState_APPIA.u4.bits_4.xfi0BerCounter

                        Default = 0x00

                        XFI0 BER counter
                        

                 <B>Notes:</B>
                        10GBASE-R BER Counter[5:0] saturating clear on read  */
      unsigned int   xfi0BerCounter : 6;    /* 03.E864.5:0  SCT      Default = 0x00 */
                     /* XFI0 BER counter
                          */
      unsigned int   reserved0 : 10;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E865.7:0 SCT XFI0 Errored Block Counter [7:0]
                        AQ_PcsReceiveXfi0VendorState_APPIA.u5.bits_5.xfi0ErroredBlockCounter

                        Default = 0x00

                        XFI0 High BER counter
                        

                 <B>Notes:</B>
                        10GBASE-R Errored Block Counter[7:0] saturating clear on read  */
      unsigned int   xfi0ErroredBlockCounter : 8;    /* 03.E865.7:0  SCT      Default = 0x00 */
                     /* XFI0 High BER counter
                          */
      unsigned int   reserved0 : 8;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive XFI0 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E866.F:0 SCT XFI0 Test Pattern Error Counter [F:0]
                        AQ_PcsReceiveXfi0VendorState_APPIA.u6.bits_6.xfi0TestPatternErrorCounter

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
} AQ_PcsReceiveXfi0VendorState_APPIA;


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
                        AQ_PcsReceiveXfi1VendorState_APPIA.u0.bits_0.xfi1GoodFrameCounterLSW

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
                    /*! \brief 03.E871.9:0 SCTM XFI1 Good Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi1VendorState_APPIA.u1.bits_1.xfi1GoodFrameCounterMSW

                        Default = 0x000

                        XFI1 Good Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1GoodFrameCounterMSW : 10;    /* 03.E871.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Good Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E872.F:0 SCTL XFI1 Bad Frame Counter LSW [F:0]
                        AQ_PcsReceiveXfi1VendorState_APPIA.u2.bits_2.xfi1BadFrameCounterLSW

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
                    /*! \brief 03.E873.9:0 SCTM XFI1 Bad Frame Counter MSW [9:0]
                        AQ_PcsReceiveXfi1VendorState_APPIA.u3.bits_3.xfi1BadFrameCounterMSW

                        Default = 0x000

                        XFI1 Bad Frame Counter MSW
                        

                 <B>Notes:</B>
                        This counts Ethernet bad frames (i.e. Ethernet CRC-32 / FCS errors).  */
      unsigned int   xfi1BadFrameCounterMSW : 10;    /* 03.E873.9:0  SCTM      Default = 0x000 */
                     /* XFI1 Bad Frame Counter MSW
                          */
      unsigned int   reserved0 : 6;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E874.5:0 SCT XFI1 BER Counter [5:0]
                        AQ_PcsReceiveXfi1VendorState_APPIA.u4.bits_4.xfi1BerCounter

                        Default = 0x00

                        XFI1 BER counter
                        

                 <B>Notes:</B>
                        10GBASE-R BER Counter[5:0] saturating clear on read  */
      unsigned int   xfi1BerCounter : 6;    /* 03.E874.5:0  SCT      Default = 0x00 */
                     /* XFI1 BER counter
                          */
      unsigned int   reserved0 : 10;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E875.7:0 SCT XFI1 Errored Block Counter [7:0]
                        AQ_PcsReceiveXfi1VendorState_APPIA.u5.bits_5.xfi1ErroredBlockCounter

                        Default = 0x00

                        XFI1 High BER counter
                        

                 <B>Notes:</B>
                        10GBASE-R Errored Block Counter[7:0] saturating clear on read  */
      unsigned int   xfi1ErroredBlockCounter : 8;    /* 03.E875.7:0  SCT      Default = 0x00 */
                     /* XFI1 High BER counter
                          */
      unsigned int   reserved0 : 8;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive XFI1 Vendor State */
  union
  {
    struct
    {
                    /*! \brief 03.E876.F:0 SCT XFI1 Test Pattern Error Counter [F:0]
                        AQ_PcsReceiveXfi1VendorState_APPIA.u6.bits_6.xfi1TestPatternErrorCounter

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
} AQ_PcsReceiveXfi1VendorState_APPIA;


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
                    /*! \brief 03.EC00.0 LRF Change in Auxilliary Bit
                        AQ_PcsReceiveVendorAlarms_APPIA.u0.bits_0.changeInAuxilliaryBit

                        

                        1 = Indicates a change in the value of the auxilliary bit
                        

                 <B>Notes:</B>
                        This bit is set when a change is detected in the auxilliary bit.  */
      unsigned int   changeInAuxilliaryBit : 1;    /* 03.EC00.0  LRF       */
                     /* 1 = Indicates a change in the value of the auxilliary bit
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.EC00.8 LH Invalid 65B Block
                        AQ_PcsReceiveVendorAlarms_APPIA.u0.bits_0.invalid_65bBlock

                        

                        1 = Invalid Rx 65B block received in PCS transmission frame
                        

                 <B>Notes:</B>
                        This bit is set when an invalid 65B block (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   invalid_65bBlock : 1;    /* 03.EC00.8  LH       */
                     /* 1 = Invalid Rx 65B block received in PCS transmission frame
                          */
      unsigned int   reserved0 : 5;
                    /*! \brief 03.EC00.E LH LDPC Decode Failure
                        AQ_PcsReceiveVendorAlarms_APPIA.u0.bits_0.ldpcDecodeFailure

                        

                        1 = LDPC decode failure
                        

                 <B>Notes:</B>
                        This bit is set when the LDPC decoder fails to decode an LDPC block.  */
      unsigned int   ldpcDecodeFailure : 1;    /* 03.EC00.E  LH       */
                     /* 1 = LDPC decode failure
                          */
                    /*! \brief 03.EC00.F LH CRC Error
                        AQ_PcsReceiveVendorAlarms_APPIA.u0.bits_0.crcError

                        

                        1 = Rx CRC Frame error
                        

                 <B>Notes:</B>
                        This bit is set when a CRC-8 error is detected on the receive PCS frame.  */
      unsigned int   crcError : 1;    /* 03.EC00.F  LH       */
                     /* 1 = Rx CRC Frame error
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.EC01.F:0 LH Reserved PCS Receive Vendor Alarms 2 [F:0]
                        AQ_PcsReceiveVendorAlarms_APPIA.u1.bits_1.reservedPcsReceiveVendorAlarms_2

                        

                        Reserved for future use
                        
  */
      unsigned int   reservedPcsReceiveVendorAlarms_2 : 16;    /* 03.EC01.F:0  LH       */
                     /* Reserved for future use
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.EC02.F:0 LH Reserved PCS Receive Vendor Alarms 3 [F:0]
                        AQ_PcsReceiveVendorAlarms_APPIA.u2.bits_2.reservedPcsReceiveVendorAlarms_3

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsReceiveVendorAlarms_3 : 16;    /* 03.EC02.F:0  LH       */
                     /* Reserved for future use  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.EC03.F:0 LH Reserved PCS Receive Vendor Alarms 4 [F:0]
                        AQ_PcsReceiveVendorAlarms_APPIA.u3.bits_3.reservedPcsReceiveVendorAlarms_4

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsReceiveVendorAlarms_4 : 16;    /* 03.EC03.F:0  LH       */
                     /* Reserved for future use  */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.EC04.F:0 LH Reserved PCS Receive Vendor Alarms 5 [F:0]
                        AQ_PcsReceiveVendorAlarms_APPIA.u4.bits_4.reservedPcsReceiveVendorAlarms_5

                        

                        Reserved for future use
  */
      unsigned int   reservedPcsReceiveVendorAlarms_5 : 16;    /* 03.EC04.F:0  LH       */
                     /* Reserved for future use  */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved2 : 3;
                    /*! \brief 03.EC05.3 LH XFI0 Invalid 66B Character Received
                        AQ_PcsReceiveVendorAlarms_APPIA.u5.bits_5.xfi0Invalid_66bCharacterReceived

                        

                        1 = XFI0 Receive invalid 66B character received
                        

                 <B>Notes:</B>
                        Invalid 66B code error  */
      unsigned int   xfi0Invalid_66bCharacterReceived : 1;    /* 03.EC05.3  LH       */
                     /* 1 = XFI0 Receive invalid 66B character received
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.EC05.B LH XFI1 Invalid 66B Character Received
                        AQ_PcsReceiveVendorAlarms_APPIA.u5.bits_5.xfi1Invalid_66bCharacterReceived

                        

                        1 = XFI1 Receive invalid 66B character received
                        

                 <B>Notes:</B>
                        Invalid 66B code error  */
      unsigned int   xfi1Invalid_66bCharacterReceived : 1;    /* 03.EC05.B  LH       */
                     /* 1 = XFI1 Receive invalid 66B character received
                          */
      unsigned int   reserved0 : 4;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 03.EC06.0 LL XFI0 Block Lock Status
                        AQ_PcsReceiveVendorAlarms_APPIA.u6.bits_6.xfi0BlockLockStatus

                        

                        1 = XFI0 Block Lock condition
                        
  */
      unsigned int   xfi0BlockLockStatus : 1;    /* 03.EC06.0  LL       */
                     /* 1 = XFI0 Block Lock condition
                          */
                    /*! \brief 03.EC06.1 LH XFI0 High BER Status
                        AQ_PcsReceiveVendorAlarms_APPIA.u6.bits_6.xfi0HighBerStatus

                        

                        1 = XFI0 High BER condition
                        
  */
      unsigned int   xfi0HighBerStatus : 1;    /* 03.EC06.1  LH       */
                     /* 1 = XFI0 High BER condition
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 03.EC06.3 LH XFI0 Receive Link Status Latch High
                        AQ_PcsReceiveVendorAlarms_APPIA.u6.bits_6.xfi0ReceiveLinkStatusLatchHigh

                        

                        Status of the XFI0 receive link

                 <B>Notes:</B>
                        This indicates the status of the XFI0 receive link.  */
      unsigned int   xfi0ReceiveLinkStatusLatchHigh : 1;    /* 03.EC06.3  LH       */
                     /* Status of the XFI0 receive link  */
                    /*! \brief 03.EC06.4 LL XFI1 Block Lock Status
                        AQ_PcsReceiveVendorAlarms_APPIA.u6.bits_6.xfi1BlockLockStatus

                        

                        1 = XFI1 Block Lock condition
                        
  */
      unsigned int   xfi1BlockLockStatus : 1;    /* 03.EC06.4  LL       */
                     /* 1 = XFI1 Block Lock condition
                          */
                    /*! \brief 03.EC06.5 LH XFI1 High BER Status
                        AQ_PcsReceiveVendorAlarms_APPIA.u6.bits_6.xfi1HighBerStatus

                        

                        1 = XFI1 High BER condition
                        
  */
      unsigned int   xfi1HighBerStatus : 1;    /* 03.EC06.5  LH       */
                     /* 1 = XFI1 High BER condition
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.EC06.7 LH XFI1 Receive Link Status Latch High
                        AQ_PcsReceiveVendorAlarms_APPIA.u6.bits_6.xfi1ReceiveLinkStatusLatchHigh

                        

                        Status of the XFI1 receive link

                 <B>Notes:</B>
                        This indicates the status of the XFI1 receive link.  */
      unsigned int   xfi1ReceiveLinkStatusLatchHigh : 1;    /* 03.EC06.7  LH       */
                     /* Status of the XFI1 receive link  */
      unsigned int   reserved0 : 8;
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsReceiveVendorAlarms_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PCS Receive Standard Interrupt Mask: 03.F000 */
/*                  PCS Receive Standard Interrupt Mask: 03.F000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PCS Receive Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved1 : 2;
                    /*! \brief 03.F000.2 R/WPD PCS Receive Link Status Mask
                        AQ_PcsReceiveStandardInterruptMask_APPIA.u0.bits_0.pcsReceiveLinkStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Mask for Bit 3.1.2. Note this bit also shows up as Bit 3.20.C, but only as a status bit.  */
      unsigned int   pcsReceiveLinkStatusMask : 1;    /* 03.F000.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 13;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PCS Receive Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved1 : 10;
                    /*! \brief 03.F001.A R/WPD Receive Fault Mask
                        AQ_PcsReceiveStandardInterruptMask_APPIA.u1.bits_1.receiveFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 3.8.A  */
      unsigned int   receiveFaultMask : 1;    /* 03.F001.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F001.B R/WPD Transmit Fault Mask
                        AQ_PcsReceiveStandardInterruptMask_APPIA.u1.bits_1.transmitFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 3.8.B  */
      unsigned int   transmitFaultMask : 1;    /* 03.F001.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 4;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 14;
                    /*! \brief 03.F002.E R/WPD 10GBASE-T High BER Latched Mask
                        AQ_PcsReceiveStandardInterruptMask_APPIA.u2.bits_2._10gbase_tHighBerLatchedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        When set, this bit indicates a high BER is being seen at the PCS. This is the interrupt for bit 3.21.E  */
      unsigned int   _10gbase_tHighBerLatchedMask : 1;    /* 03.F002.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F002.F R/WPD 10GBASE-T PCS Block Lock Latched Mask
                        AQ_PcsReceiveStandardInterruptMask_APPIA.u2.bits_2._10gbase_tPcsBlockLockLatchedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        NOTE!! There is a gap in this register set, which causes a dummy word to be inserted in the C structure!!!!
                        
                        When set, this bit indicates that 10GBASE-T PCS Framer has acquired frame synchronization and is locked. This is the interrupt for bit 3.21.F  */
      unsigned int   _10gbase_tPcsBlockLockLatchedMask : 1;    /* 03.F002.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PcsReceiveStandardInterruptMask_APPIA;


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
                    /*! \brief 03.F400.0 R/WPD Change in Auxilliary Bit Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u0.bits_0.changeInAuxilliaryBitMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when a change is detected in the auxilliary bit.  */
      unsigned int   changeInAuxilliaryBitMask : 1;    /* 03.F400.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.F400.8 R/WPD Invalid 65B Block Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u0.bits_0.invalid_65bBlockMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when an invalid 65B block (but without LDPC frame parity error) has been detected on the received LDPC frame.  */
      unsigned int   invalid_65bBlockMask : 1;    /* 03.F400.8  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 5;
                    /*! \brief 03.F400.E R/WPD LDPC Decode Failure Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u0.bits_0.ldpcDecodeFailureMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when the LDPC decoder fails to decode an LDPC block.  */
      unsigned int   ldpcDecodeFailureMask : 1;    /* 03.F400.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 03.F400.F R/WPD CRC Error Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u0.bits_0.crcErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        This bit is set when a CRC-8 error is detected on the receive PCS frame.  */
      unsigned int   crcErrorMask : 1;    /* 03.F400.F  R/WPD      Provisionable Default = 0x0 */
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
                    /*! \brief 03.F401.F:0 R/WPD Reserved PCS Receive Vendor Alarms 2 Mask[F:0]
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u1.bits_1.reservedPcsReceiveVendorAlarms_2Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   reservedPcsReceiveVendorAlarms_2Mask : 16;    /* 03.F401.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.F402.F:0 R/WPD Reserved PCS Receive Vendor Alarms 3 Mask [F:0]
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u2.bits_2.reservedPcsReceiveVendorAlarms_3Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsReceiveVendorAlarms_3Mask : 16;    /* 03.F402.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.F403.F:0 R/WPD Reserved PCS Receive Vendor Alarms 4 Mask[F:0]
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u3.bits_3.reservedPcsReceiveVendorAlarms_4Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsReceiveVendorAlarms_4Mask : 16;    /* 03.F403.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.F404.F:0 R/WPD Reserved PCS Receive Vendor Alarms 5 Mask[F:0]
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u4.bits_4.reservedPcsReceiveVendorAlarms_5Mask

                        Provisionable Default = 0x0000

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedPcsReceiveVendorAlarms_5Mask : 16;    /* 03.F404.F:0  R/WPD      Provisionable Default = 0x0000 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved2 : 3;
                    /*! \brief 03.F405.3 R/WPD XFI0 Invalid 66B Character Received Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u5.bits_5.xfi0Invalid_66bCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0Invalid_66bCharacterReceivedMask : 1;    /* 03.F405.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 7;
                    /*! \brief 03.F405.B R/WPD XFI1 Invalid 66B Character Received Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u5.bits_5.xfi1Invalid_66bCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1Invalid_66bCharacterReceivedMask : 1;    /* 03.F405.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved0 : 4;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of PCS Receive Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 03.F406.0 R/WPD XFI0 Block Lock Status Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u6.bits_6.xfi0BlockLockStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0BlockLockStatusMask : 1;    /* 03.F406.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.1 R/WPD XFI0 High BER Status Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u6.bits_6.xfi0HighBerStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0HighBerStatusMask : 1;    /* 03.F406.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved2 : 1;
                    /*! \brief 03.F406.3 R/WPD XFI0 Receive Link Status Latch High  Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u6.bits_6.xfi0ReceiveLinkStatusLatchHighMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi0ReceiveLinkStatusLatchHighMask : 1;    /* 03.F406.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.4 R/WPD XFI1 Block Lock Status Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u6.bits_6.xfi1BlockLockStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1BlockLockStatusMask : 1;    /* 03.F406.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 03.F406.5 R/WPD XFI1 High BER Status Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u6.bits_6.xfi1HighBerStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1HighBerStatusMask : 1;    /* 03.F406.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 03.F406.7 R/WPD XFI1 Receive Link Status Latch High  Mask
                        AQ_PcsReceiveVendorInterruptMask_APPIA.u6.bits_6.xfi1ReceiveLinkStatusLatchHighMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xfi1ReceiveLinkStatusLatchHighMask : 1;    /* 03.F406.7  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved0 : 8;
    } bits_6;
    uint16_t word_6;
  } u6;
} AQ_PcsReceiveVendorInterruptMask_APPIA;


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
                    /*! \brief 03.F800.0 R/WPD PCS Network Loopback
                        AQ_PcsReceiveVendorDebug_APPIA.u0.bits_0.pcsNetworkLoopback

                        Provisionable Default = 0x0

                        When set to 1, data after the Rx PCS layer will be looped back to the Tx PCS layer and transmitted back towards the network UTP line
                        
  */
      unsigned int   pcsNetworkLoopback : 1;    /* 03.F800.0  R/WPD      Provisionable Default = 0x0 */
                     /* When set to 1, data after the Rx PCS layer will be looped back to the Tx PCS layer and transmitted back towards the network UTP line
                          */
                    /*! \brief 03.F800.1 R/WPD PCS Network Loopback Pass Through
                        AQ_PcsReceiveVendorDebug_APPIA.u0.bits_0.pcsNetworkLoopbackPassThrough

                        Provisionable Default = 0x1

                        When set to 1, this bit enables loopback traffic from the PCS Network Loopback to pass-through towards the System XAUI side. When set to 0, the data sent towards the system XUAI will be an IDLE ordered set data stream when in PCS Network Loopback
                        

                 <B>Notes:</B>
                        This enables traffic to pass through as well as loopback when the PCS Network Loopback is enabled.  */
      unsigned int   pcsNetworkLoopbackPassThrough : 1;    /* 03.F800.1  R/WPD      Provisionable Default = 0x1 */
                     /* When set to 1, this bit enables loopback traffic from the PCS Network Loopback to pass-through towards the System XAUI side. When set to 0, the data sent towards the system XUAI will be an IDLE ordered set data stream when in PCS Network Loopback
                          */
                    /*! \brief 03.F800.2 R/WPD PCS Network Loopback Merge
                        AQ_PcsReceiveVendorDebug_APPIA.u0.bits_0.pcsNetworkLoopbackMerge

                        Provisionable Default = 0x1

                        When set to 1, XAUI data from the local MAC and PCS Network Loopback data will be merged
                        

                 <B>Notes:</B>
                        If the MAC sends data, it will take priority over the PCS Network Loopback data. The loopback data will be dropped.  */
      unsigned int   pcsNetworkLoopbackMerge : 1;    /* 03.F800.2  R/WPD      Provisionable Default = 0x1 */
                     /* When set to 1, XAUI data from the local MAC and PCS Network Loopback data will be merged
                          */
      unsigned int   reserved0 : 12;
                    /*! \brief 03.F800.F R/WPD PCS Rx Descrambler Disable
                        AQ_PcsReceiveVendorDebug_APPIA.u0.bits_0.pcsRxDescramblerDisable

                        Provisionable Default = 0x0

                        1 = Rx Descrambler Disabled
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        Setting this bit disables the Rx descrambler during regular data transmission (i.e. descrambler functionality during training and startup is unmodified).  */
      unsigned int   pcsRxDescramblerDisable : 1;    /* 03.F800.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Rx Descrambler Disabled
                        0 = Normal Operation
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsReceiveVendorDebug_APPIA;


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
                    /*! \brief 03.FC00.0 RO Vendor Specific Rx Alarms 7 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificRxAlarms_7Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 7
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 7: Address 3.EC06 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 7: Address 3.F406 ).  */
      unsigned int   vendorSpecificRxAlarms_7Interrupt : 1;    /* 03.FC00.0  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 7
                          */
                    /*! \brief 03.FC00.1 RO Vendor Specific Rx Alarms 6 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificRxAlarms_6Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 6
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 7: Address 3.EC06 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 7: Address 3.F406 ).  */
      unsigned int   vendorSpecificRxAlarms_6Interrupt : 1;    /* 03.FC00.1  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 6
                          */
                    /*! \brief 03.FC00.2 RO Vendor Specific Rx Alarms 5 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificRxAlarms_5Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 5
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 4: Address 3.EC03 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 4: Address 3.F403 ).  */
      unsigned int   vendorSpecificRxAlarms_5Interrupt : 1;    /* 03.FC00.2  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 5
                          */
                    /*! \brief 03.FC00.3 RO Vendor Specific Rx Alarms 4 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificRxAlarms_4Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 4
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 3 - Address 3.EC02 ) and the corresponding mask register ( See PCS Receive Vendor Interrupt Mask 3 - Address 3.F402 ).  */
      unsigned int   vendorSpecificRxAlarms_4Interrupt : 1;    /* 03.FC00.3  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 4
                          */
                    /*! \brief 03.FC00.4 RO Vendor Specific Rx Alarms 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificRxAlarms_3Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Receive Vendor Alarms 2 - Address 3.EC01 ) and the corresponding mask register ( See PCS Receive Vendor Interrupt Mask 2 - Address 3.EC01 ).  */
      unsigned int   vendorSpecificRxAlarms_3Interrupt : 1;    /* 03.FC00.4  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 3
                          */
                    /*! \brief 03.FC00.5 RO Vendor Specific Rx Alarms 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificRxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Transmit Vendor Alarms 2: Address 3.CC00 ) and the corresponding mask register ( See PCS Receive Vendor LASI Interrupt Mask 1: Address 3.F400 ).  */
      unsigned int   vendorSpecificRxAlarms_2Interrupt : 1;    /* 03.FC00.5  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 2
                          */
                    /*! \brief 03.FC00.6 RO Vendor Specific Rx Alarms 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificRxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Vendor Receive XAUI Tx Alarms 1- Address 4.D800 ) and the corresponding mask register ( See PCS Vendor Receive PCS Interrupt Mask 1 - Address 3.E000 ).  */
      unsigned int   vendorSpecificRxAlarms_1Interrupt : 1;    /* 03.FC00.6  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 1
                          */
                    /*! \brief 03.FC00.7 RO Vendor Specific Tx Alarms 5 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificTxAlarms_5Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 5
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Transmit Vendor Alarms 5: Address 3.CC04 ) and the corresponding mask register ( See PCS Transmit Vendor LASI Interrupt Mask 5: Address 3.D404 ).  */
      unsigned int   vendorSpecificTxAlarms_5Interrupt : 1;    /* 03.FC00.7  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 5
                          */
                    /*! \brief 03.FC00.8 RO Vendor Specific Tx Alarms 4 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificTxAlarms_4Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 4
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Transmit Vendor Alarms 4: Address 3.CC03 ) and the corresponding mask register ( See PCS Transmit Vendor LASI Interrupt Mask 4: Address 3.D403 ).  */
      unsigned int   vendorSpecificTxAlarms_4Interrupt : 1;    /* 03.FC00.8  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 4
                          */
                    /*! \brief 03.FC00.9 RO Vendor Specific Tx Alarms 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificTxAlarms_3Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS Transmit Vendor Alarms 3: Address 3.CC02 ) and the corresponding mask register ( See PCS Transmit Vendor LASI Interrupt Mask 3: Address 3.D402 ).  */
      unsigned int   vendorSpecificTxAlarms_3Interrupt : 1;    /* 03.FC00.9  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 3
                          */
                    /*! \brief 03.FC00.A RO Vendor Specific Tx Alarms 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificTxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Vendor XAUI Receive Alarms 1 - Address 4.B000 ) and the corresponding mask register ( See PCS Vendor Transmit PCS Interrupt Mask 1 - Address 3.A800 ).  */
      unsigned int   vendorSpecificTxAlarms_2Interrupt : 1;    /* 03.FC00.A  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 2
                          */
                    /*! \brief 03.FC00.B RO Vendor Specific Tx Alarms 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificTxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See Autonegotiation Vendor Alarms 3: Address 1E.CC02 ) and the corresponding mask register ( See PHY XS Transmit (XAUI Rx) Vendor LASI Interrupt Mask 3: Address 4.D402 ).  */
      unsigned int   vendorSpecificTxAlarms_1Interrupt : 1;    /* 03.FC00.B  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 1
                          */
      unsigned int   reserved0 : 1;
                    /*! \brief 03.FC00.D RO Standard Alarm 3 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.standardAlarm_3Interrupt

                        

                        1 = Interrupt in standard alarms 3
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PCS 10GBASE-T Status 2 - Address 3.21 ) and the corresponding mask register ( See PCS Standard Interrupt Mask 1 - Address 3.E021 ).  */
      unsigned int   standardAlarm_3Interrupt : 1;    /* 03.FC00.D  RO       */
                     /* 1 = Interrupt in standard alarms 3
                          */
                    /*! \brief 03.FC00.E RO Standard Alarm 2 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.standardAlarm_2Interrupt

                        

                        1 = Interrupt in standard alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Standard Vendor Devices in Package - Address 4.8 ) and the corresponding mask register ( See PHY XS Standard Transmit XAUI Rx Interrupt Mask 8 - Address 4.A008 ).  */
      unsigned int   standardAlarm_2Interrupt : 1;    /* 03.FC00.E  RO       */
                     /* 1 = Interrupt in standard alarms 2
                          */
                    /*! \brief 03.FC00.F RO Standard Alarm 1 Interrupt
                        AQ_PcsVendorGlobalInterruptFlags_APPIA.u0.bits_0.standardAlarm_1Interrupt

                        

                        1 = Interrupt in standard alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from status register ( See PHY XS Standard Status 1 - Address 4.1 ) and the corresponding mask register ( See PHY XS Standard Transmit XAUI Rx Interrupt Mask 2 - Address 4.A001 ).  */
      unsigned int   standardAlarm_1Interrupt : 1;    /* 03.FC00.F  RO       */
                     /* 1 = Interrupt in standard alarms 1
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PcsVendorGlobalInterruptFlags_APPIA;

#endif
/*@}*/
/*@}*/
