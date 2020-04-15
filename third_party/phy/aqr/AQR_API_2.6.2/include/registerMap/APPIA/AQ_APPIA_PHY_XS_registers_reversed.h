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
*   for the PHY_XS Registers block.
 */        

/*! \addtogroup registerMap
  @{
*/

/*! \defgroup PHY_XS_registers PHY_XS Registers
*   This module contains the data structures and doxygen comments
*   for the PHY_XS Registers block.
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
*   This file contains the c header structures for the registers contained in the PHY_XS Registers block.
*
*   The bit fields in this structure are from MSbit to LSbit
*
***********************************************************************/


/*@{*/
#ifndef AQ_APPIA_PHY_XS_REGS_HEADER
#define AQ_APPIA_PHY_XS_REGS_HEADER


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Control 1: 04.0000 */
/*                  PHY XS Standard Control 1: 04.0000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Control 1 */
  union
  {
    struct
    {
                    /*! \brief 04.0000.F R/WSC Reset
                        AQ_PhyXS_StandardControl_1_APPIA.u0.bits_0.reset

                        Default = 0x1

                        1 = PHY XS reset
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        The reset bit is automatically cleared upon completion of the reset sequence by the microcontroller. This bit is set to 1 during reset. The reset is internally stretched by approximately 1.7 us. Therefore the MDIO or uP should allow for 1.7 us before writing any PHY XS registers after this bit is set.
                          */
      unsigned int   reset : 1;    /* 04.0000.F  R/WSC      Default = 0x1 */
                     /* 1 = PHY XS reset
                        0 = Normal operation
                          */
                    /*! \brief 04.0000.E R/W Loopback
                        AQ_PhyXS_StandardControl_1_APPIA.u0.bits_0.loopback

                        Default = 0x0

                        1 = System Interface Network Loopback
                        0 = Normal operation

                 <B>Notes:</B>
                        This enables network loopback on the designated system interface.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   loopback : 1;    /* 04.0000.E  R/W      Default = 0x0 */
                     /* 1 = System Interface Network Loopback
                        0 = Normal operation  */
                    /*! \brief 04.0000.D ROS Speed Selection 0
                        AQ_PhyXS_StandardControl_1_APPIA.u0.bits_0.speedSelection_0

                        Default = 0x1

                        1 = 10Gb/s and above
                        0 = Unspecified

                 <B>Notes:</B>
                        This should always be set to 1  */
      unsigned int   speedSelection_0 : 1;    /* 04.0000.D  ROS      Default = 0x1 */
                     /* 1 = 10Gb/s and above
                        0 = Unspecified  */
      unsigned int   reserved0 : 1;
                    /*! \brief 04.0000.B R/W Low Power
                        AQ_PhyXS_StandardControl_1_APPIA.u0.bits_0.lowPower

                        Default = 0x0

                        1 = Low-power mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        A one written to this register causes the PHY XS to enter low-power mode. If a global chip low-power state is desired, use Bit B in  See PHY XS Standard Control 1 - Address 4.0 should be set.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F
                          */
      unsigned int   lowPower : 1;    /* 04.0000.B  R/W      Default = 0x0 */
                     /* 1 = Low-power mode
                        0 = Normal operation
                          */
      unsigned int   reserved1 : 4;
                    /*! \brief 04.0000.6 ROS Speed Selection 1
                        AQ_PhyXS_StandardControl_1_APPIA.u0.bits_0.speedSelection_1

                        Default = 0x1

                        1 = 10Gb/s and above
                        0 = Unspecified

                 <B>Notes:</B>
                        This should always be set to 1  */
      unsigned int   speedSelection_1 : 1;    /* 04.0000.6  ROS      Default = 0x1 */
                     /* 1 = 10Gb/s and above
                        0 = Unspecified  */
                    /*! \brief 04.0000.5:2 ROS Speed Selection 2 [3:0]
                        AQ_PhyXS_StandardControl_1_APPIA.u0.bits_0.speedSelection_2

                        Default = 0x0

                        1 x x x = Reserved
                        x 1 x x = Reserved
                        x x 1 x = Reserved
                        x x x 1 = Reserved
                        0 0 0 0 = 10 Gb/s

                 <B>Notes:</B>
                        This should always be set to 0  */
      unsigned int   speedSelection_2 : 4;    /* 04.0000.5:2  ROS      Default = 0x0 */
                     /* 1 x x x = Reserved
                        x 1 x x = Reserved
                        x x 1 x = Reserved
                        x x x 1 = Reserved
                        0 0 0 0 = 10 Gb/s  */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardControl_1_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Status 1: 04.0001 */
/*                  PHY XS Standard Status 1: 04.0001 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Status 1 */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 04.0001.7 RO Fault
                        AQ_PhyXS_StandardStatus_1_APPIA.u0.bits_0.fault

                        

                        1 = Fault condition detected
                        0 = No fault detected
                        

                 <B>Notes:</B>
                        This is the top-level fault indicator flag for the PHY XS (aka XAUI) block, This bit is set if either of the two bits 4.8.B or 4.8.A are set.  */
      unsigned int   fault : 1;    /* 04.0001.7  RO       */
                     /* 1 = Fault condition detected
                        0 = No fault detected
                          */
      unsigned int   reserved1 : 4;
                    /*! \brief 04.0001.2 LL PHY XS Transmit Link Alignment Status
                        AQ_PhyXS_StandardStatus_1_APPIA.u0.bits_0.phyXS_TransmitLinkAlignmentStatus

                        

                        Status of receive XAUI interface alignment:
                        
                        1 = XAUI receiver is aligned correctly
                        0 = XAUI receiver is not aligned
                        

                 <B>Notes:</B>
                        This indicates the status of the lane alignment function on the receive XAUI interface. This is a latching low version of Bit 4.18.C.  */
      unsigned int   phyXS_TransmitLinkAlignmentStatus : 1;    /* 04.0001.2  LL       */
                     /* Status of receive XAUI interface alignment:
                        
                        1 = XAUI receiver is aligned correctly
                        0 = XAUI receiver is not aligned
                          */
                    /*! \brief 04.0001.1 ROS Low Power Ability
                        AQ_PhyXS_StandardStatus_1_APPIA.u0.bits_0.lowPowerAbility

                        Default = 0x1

                        1 = PHY XS supports low-power mode
                        0 = no low-power mode supported

                 <B>Notes:</B>
                        Indicates whether the XAUI interface supports a low-power mode  */
      unsigned int   lowPowerAbility : 1;    /* 04.0001.1  ROS      Default = 0x1 */
                     /* 1 = PHY XS supports low-power mode
                        0 = no low-power mode supported  */
      unsigned int   reserved2 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardStatus_1_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Device Identifier: 04.0002 */
/*                  PHY XS Standard Device Identifier: 04.0002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 04.0002.F:0 RO Device ID MSW [1F:10]
                        AQ_PhyXS_StandardDeviceIdentifier_APPIA.u0.bits_0.deviceIdMSW

                        

                        Bits 31 - 16 of Device ID
  */
      unsigned int   deviceIdMSW : 16;    /* 04.0002.F:0  RO       */
                     /* Bits 31 - 16 of Device ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 04.0003.F:0 RO Device ID LSW [F:0]
                        AQ_PhyXS_StandardDeviceIdentifier_APPIA.u1.bits_1.deviceIdLSW

                        

                        Bits 15 - 0 of Device ID
  */
      unsigned int   deviceIdLSW : 16;    /* 04.0003.F:0  RO       */
                     /* Bits 15 - 0 of Device ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_StandardDeviceIdentifier_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Speed Ability: 04.0004 */
/*                  PHY XS Standard Speed Ability: 04.0004 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Speed Ability */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.0004.0 ROS 10G Capable
                        AQ_PhyXS_StandardSpeedAbility_APPIA.u0.bits_0._10gCapable

                        Default = 0x1

                        1 = PHY XS is 10 Gb/s capable
                        0 = PHY XS is not 10 Gb/s capable

                 <B>Notes:</B>
                        This is always set to 1 in the PHY.  */
      unsigned int   _10gCapable : 1;    /* 04.0004.0  ROS      Default = 0x1 */
                     /* 1 = PHY XS is 10 Gb/s capable
                        0 = PHY XS is not 10 Gb/s capable  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardSpeedAbility_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Devices in Package: 04.0005 */
/*                  PHY XS Standard Devices in Package: 04.0005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Devices in Package */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 04.0005.7 ROS Autonegotiation Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u0.bits_0.autonegotiationPresent

                        Default = 0x1

                        1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package

                 <B>Notes:</B>
                        This is always set to 1, as there is Autonegotiation in the PHY.  */
      unsigned int   autonegotiationPresent : 1;    /* 04.0005.7  ROS      Default = 0x1 */
                     /* 1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package  */
                    /*! \brief 04.0005.6 ROS TC Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u0.bits_0.tcPresent

                        Default = 0x0

                        1 = TC is present in package
                        0 = TC is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no TC functionality in the PHY.  */
      unsigned int   tcPresent : 1;    /* 04.0005.6  ROS      Default = 0x0 */
                     /* 1 = TC is present in package
                        0 = TC is not present in package  */
                    /*! \brief 04.0005.5 ROS DTE XS Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u0.bits_0.dteXsPresent

                        Default = 0x0

                        1 = DTE XS is present in package
                        0 = DTE XS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no DTE XAUI interface in the PHY.  */
      unsigned int   dteXsPresent : 1;    /* 04.0005.5  ROS      Default = 0x0 */
                     /* 1 = DTE XS is present in package
                        0 = DTE XS is not present in package  */
                    /*! \brief 04.0005.4 ROS PHY XS Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u0.bits_0.phyXS_Present

                        Default = 0x1

                        1 = PHY XS is present in package
                        0 = PHY XS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is a PHY XS interface in the PHY.  */
      unsigned int   phyXS_Present : 1;    /* 04.0005.4  ROS      Default = 0x1 */
                     /* 1 = PHY XS is present in package
                        0 = PHY XS is not present in package  */
                    /*! \brief 04.0005.3 ROS PCS Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u0.bits_0.pcsPresent

                        Default = 0x1

                        1 = PCS is present in package
                        0 = PCS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is PCS functionality in the PHY.  */
      unsigned int   pcsPresent : 1;    /* 04.0005.3  ROS      Default = 0x1 */
                     /* 1 = PCS is present in package
                        0 = PCS is not present in package  */
                    /*! \brief 04.0005.2 ROS WIS Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u0.bits_0.wisPresent

                        Default = 0x0

                        1 = WIS is present in package
                        0 = WIS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no WIS functionality in the PHY.  */
      unsigned int   wisPresent : 1;    /* 04.0005.2  ROS      Default = 0x0 */
                     /* 1 = WIS is present in package
                        0 = WIS is not present in package  */
                    /*! \brief 04.0005.1 ROS PMA Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u0.bits_0.pmaPresent

                        Default = 0x1

                        1 = PMA is present in package
                        0 = PMA is not present 

                 <B>Notes:</B>
                        This is always set to 1 as there is PMA functionality in the PHY.  */
      unsigned int   pmaPresent : 1;    /* 04.0005.1  ROS      Default = 0x1 */
                     /* 1 = PMA is present in package
                        0 = PMA is not present   */
                    /*! \brief 04.0005.0 ROS Clause 22 Registers Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u0.bits_0.clause_22RegistersPresent

                        Default = 0x0

                        1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package

                 <B>Notes:</B>
                        This is always set to 0 in the PHY, as there are no Clause 22 registers in the device.  */
      unsigned int   clause_22RegistersPresent : 1;    /* 04.0005.0  ROS      Default = 0x0 */
                     /* 1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Standard Devices in Package */
  union
  {
    struct
    {
                    /*! \brief 04.0006.F ROS Vendor Specific Device #2 Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u1.bits_1.vendorSpecificDevice_2Present

                        Default = 0x1

                        1 = Device #2 is present in package
                        0 = Device #2 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the DSP PMA registers.  */
      unsigned int   vendorSpecificDevice_2Present : 1;    /* 04.0006.F  ROS      Default = 0x1 */
                     /* 1 = Device #2 is present in package
                        0 = Device #2 is not present in package  */
                    /*! \brief 04.0006.E ROS Vendor Specific Device #1 Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u1.bits_1.vendorSpecificDevice_1Present

                        Default = 0x1

                        1 = Device #1 is present in package
                        0 = Device #1 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the Global registers.  */
      unsigned int   vendorSpecificDevice_1Present : 1;    /* 04.0006.E  ROS      Default = 0x1 */
                     /* 1 = Device #1 is present in package
                        0 = Device #1 is not present in package  */
                    /*! \brief 04.0006.D ROS Clause 22 Extension Present
                        AQ_PhyXS_StandardDevicesInPackage_APPIA.u1.bits_1.clause_22ExtensionPresent

                        Default = 0x1

                        1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the GbE registers.  */
      unsigned int   clause_22ExtensionPresent : 1;    /* 04.0006.D  ROS      Default = 0x1 */
                     /* 1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package  */
      unsigned int   reserved0 : 13;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_StandardDevicesInPackage_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Status 2: 04.0008 */
/*                  PHY XS Standard Status 2: 04.0008 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Status 2 */
  union
  {
    struct
    {
                    /*! \brief 04.0008.F:E ROS Device Present [1:0]
                        AQ_PhyXS_StandardStatus_2_APPIA.u0.bits_0.devicePresent

                        Default = 0x2

                        [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address

                 <B>Notes:</B>
                        This field is always set to 2, as the PHY XS is present in the PHY.
                          */
      unsigned int   devicePresent : 2;    /* 04.0008.F:E  ROS      Default = 0x2 */
                     /* [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address  */
      unsigned int   reserved0 : 2;
                    /*! \brief 04.0008.B LH Transmit Fault
                        AQ_PhyXS_StandardStatus_2_APPIA.u0.bits_0.transmitFault

                        

                        1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the transmit path. A fault will be indicated if there is an alignment fault, a synchronization fault on any lane, or a FIFO underflow/overflow error.  */
      unsigned int   transmitFault : 1;    /* 04.0008.B  LH       */
                     /* 1 = Fault condition on transmit path
                        0 = No fault condition on transmit path
                          */
                    /*! \brief 04.0008.A LH Receive Fault
                        AQ_PhyXS_StandardStatus_2_APPIA.u0.bits_0.receiveFault

                        

                        1 = Fault condition on receive path
                        0 = No fault condition on receive path
                        

                 <B>Notes:</B>
                        This bit indicates whether there is a fault somewhere along the receive path. A fault will be indicated if there is a FIFO underflow/overflow error.  */
      unsigned int   receiveFault : 1;    /* 04.0008.A  LH       */
                     /* 1 = Fault condition on receive path
                        0 = No fault condition on receive path
                          */
      unsigned int   reserved1 : 10;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardStatus_2_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard Package Identifier: 04.000E */
/*                  PHY XS Standard Package Identifier: 04.000E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 04.000E.F:0 RO Package ID MSW [1F:10]
                        AQ_PhyXS_StandardPackageIdentifier_APPIA.u0.bits_0.packageIdMSW

                        

                        Bits 31- 16 of Package ID
  */
      unsigned int   packageIdMSW : 16;    /* 04.000E.F:0  RO       */
                     /* Bits 31- 16 of Package ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 04.000F.F:0 RO Package ID LSW [F:0]
                        AQ_PhyXS_StandardPackageIdentifier_APPIA.u1.bits_1.packageIdLSW

                        

                        Bits 15 - 0 of Package ID
  */
      unsigned int   packageIdLSW : 16;    /* 04.000F.F:0  RO       */
                     /* Bits 15 - 0 of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_StandardPackageIdentifier_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard XGXS Lane Status: 04.0018 */
/*                  PHY XS Standard XGXS Lane Status: 04.0018 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard XGXS Lane Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 3;
                    /*! \brief 04.0018.C RO PHY XGXS Lane Alignment Status
                        AQ_PhyXS_StandardXGXS_LaneStatus_APPIA.u0.bits_0.phyXGXS_LaneAlignmentStatus

                        

                        1 = XAUI Rx lanes aligned
                        0 = XAUI Rx lanes not aligned
                        

                 <B>Notes:</B>
                        When set, this bit indicates that the four XAUI Rx lanes are properly aligned. This is a non-latching version of bit 4.1.2.  */
      unsigned int   phyXGXS_LaneAlignmentStatus : 1;    /* 04.0018.C  RO       */
                     /* 1 = XAUI Rx lanes aligned
                        0 = XAUI Rx lanes not aligned
                          */
                    /*! \brief 04.0018.B ROS PHY XGXS Pattern Testing Ability
                        AQ_PhyXS_StandardXGXS_LaneStatus_APPIA.u0.bits_0.phyXGXS_PatternTestingAbility

                        Default = 0x1

                        1 = XAUI has the ability to generate XAUI Tx test patterns
                        0 = XAUI does not have the ability to generate XAUI Tx test patterns

                 <B>Notes:</B>
                        This is always set to 1 as the PHY is capable of generating test patterns at the XAUI interface.  */
      unsigned int   phyXGXS_PatternTestingAbility : 1;    /* 04.0018.B  ROS      Default = 0x1 */
                     /* 1 = XAUI has the ability to generate XAUI Tx test patterns
                        0 = XAUI does not have the ability to generate XAUI Tx test patterns  */
                    /*! \brief 04.0018.A ROS PHY XGXS Loopback Ability
                        AQ_PhyXS_StandardXGXS_LaneStatus_APPIA.u0.bits_0.phyXGXS_LoopbackAbility

                        Default = 0x1

                        1 = XAUI has the ability to perform a loopback function
                        0 = XAUI does not have the ability to perform a loopback function

                 <B>Notes:</B>
                        This is always set to 1 as the PHY is capable of performing loopback at the XAUI interface.  */
      unsigned int   phyXGXS_LoopbackAbility : 1;    /* 04.0018.A  ROS      Default = 0x1 */
                     /* 1 = XAUI has the ability to perform a loopback function
                        0 = XAUI does not have the ability to perform a loopback function  */
      unsigned int   reserved1 : 6;
                    /*! \brief 04.0018.3:0 RO Lane Sync [3:0]
                        AQ_PhyXS_StandardXGXS_LaneStatus_APPIA.u0.bits_0.laneSync

                        

                        1 = Lane is synchronized
                        0 = Lane is not synchronized
                        Bit 0 corresponds to Lane 0 and so on
                        

                 <B>Notes:</B>
                        When set, these bits indicates that the corresponding lane of the XAUI interface is synchronized.  */
      unsigned int   laneSync : 4;    /* 04.0018.3:0  RO       */
                     /* 1 = Lane is synchronized
                        0 = Lane is not synchronized
                        Bit 0 corresponds to Lane 0 and so on
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardXGXS_LaneStatus_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Standard XGXS Test Control: 04.0019 */
/*                  PHY XS Standard XGXS Test Control: 04.0019 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Standard XGXS Test Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 04.0019.2 R/WPD Receive Test- Pattern Enable
                        AQ_PhyXS_StandardXGXS_TestControl_APPIA.u0.bits_0.receiveTest_PatternEnable

                        Provisionable Default = 0x0

                        1 = Receive test pattern enabled
                        0 = Receive test pattern not enabled
                        

                 <B>Notes:</B>
                        When set, this bit places the transmitters of the XAUI interface into test pattern mode.  */
      unsigned int   receiveTest_PatternEnable : 1;    /* 04.0019.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Receive test pattern enabled
                        0 = Receive test pattern not enabled
                          */
                    /*! \brief 04.0019.1:0 R/WPD Test-Pattern Select [1:0]
                        AQ_PhyXS_StandardXGXS_TestControl_APPIA.u0.bits_0.test_patternSelect

                        Provisionable Default = 0x2

                        0x3 = Reserved
                        0x2 = Mixed-frequency test pattern
                        0x1 = Low-frequency test pattern
                        0x0 = High-frequency test pattern
                        

                 <B>Notes:</B>
                        These test patterns are described in Annex 48A of 802.3ae. These bits also interact with the Extended Test Pattern Control bits [C:B] in  See PHY XS Vendor Transmit Control - Address 4.8800 . The full range of options is described there, but for these functions to correspond to the test-patterns described here, bits [C:B] must be set to zero.
                          */
      unsigned int   test_patternSelect : 2;    /* 04.0019.1:0  R/WPD      Provisionable Default = 0x2 */
                     /* 0x3 = Reserved
                        0x2 = Mixed-frequency test pattern
                        0x1 = Low-frequency test pattern
                        0x0 = High-frequency test pattern
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_StandardXGXS_TestControl_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Configuration: 04.C180 */
/*                  PHY XS SERDES Configuration: 04.C180 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 11;
                    /*! \brief 04.C180.4 R/W SERDES AHB Address 8
                        AQ_PhyXS_SerdesConfiguration_APPIA.u0.bits_0.serdesAhbAddress_8

                        Default = 0x0

                        Sets the AHB address bit 8 for the SERDES
                        

                 <B>Notes:</B>
                        Currently unused. Always write a 0 to this bit.  */
      unsigned int   serdesAhbAddress_8 : 1;    /* 04.C180.4  R/W      Default = 0x0 */
                     /* Sets the AHB address bit 8 for the SERDES
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 04.C180.2:0 R/W SERDES Device Selection [2:0]
                        AQ_PhyXS_SerdesConfiguration_APPIA.u0.bits_0.serdesDeviceSelection

                        Default = 0x0

                        Sets the SERDES device selection (AHB address bits 11:9)
                        

                 <B>Notes:</B>
                        0x0 : Common CMU
                        0x1 : Lane 0
                        0x2 : Lane 1
                        0x3 : Lane 2
                        0x4 : Lane 3
                        0x5 : Common Lane Block  */
      unsigned int   serdesDeviceSelection : 3;    /* 04.C180.2:0  R/W      Default = 0x0 */
                     /* Sets the SERDES device selection (AHB address bits 11:9)
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesConfiguration_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Lane 0 Configuration: 04.C1C0 */
/*                  PHY XS SERDES Lane 0 Configuration: 04.C1C0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Lane 0 Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.C1C0.0 R/W SERDES Lane 0 Reset
                        AQ_PhyXS_SerdesLane_0Configuration_APPIA.u0.bits_0.serdesLane_0Reset

                        Default = 0x1

                        0 = Reset SERDES corresponding lane
                        

                 <B>Notes:</B>
                        Active low. Asynchronous. When all channels are being reset, CMU is reset. Separate reset for CMU reset does not exist.  */
      unsigned int   serdesLane_0Reset : 1;    /* 04.C1C0.0  R/W      Default = 0x1 */
                     /* 0 = Reset SERDES corresponding lane
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLane_0Configuration_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Lane 1 Configuration: 04.C1D0 */
/*                  PHY XS SERDES Lane 1 Configuration: 04.C1D0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Lane 1 Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.C1D0.0 R/W SERDES Lane 1 Reset
                        AQ_PhyXS_SerdesLane_1Configuration_APPIA.u0.bits_0.serdesLane_1Reset

                        Default = 0x1

                        0 = Reset SERDES corresponding lane
                        

                 <B>Notes:</B>
                        Active low. Asynchronous. When all channels are being reset, CMU is reset. Separate reset for CMU reset does not exist.  */
      unsigned int   serdesLane_1Reset : 1;    /* 04.C1D0.0  R/W      Default = 0x1 */
                     /* 0 = Reset SERDES corresponding lane
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLane_1Configuration_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Lane 2 Configuration: 04.C1E0 */
/*                  PHY XS SERDES Lane 2 Configuration: 04.C1E0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Lane 2 Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.C1E0.0 R/W SERDES Lane 2 Reset
                        AQ_PhyXS_SerdesLane_2Configuration_APPIA.u0.bits_0.serdesLane_2Reset

                        Default = 0x1

                        0 = Reset SERDES corresponding lane
                        

                 <B>Notes:</B>
                        Active low. Asynchronous. When all channels are being reset, CMU is reset. Separate reset for CMU reset does not exist.  */
      unsigned int   serdesLane_2Reset : 1;    /* 04.C1E0.0  R/W      Default = 0x1 */
                     /* 0 = Reset SERDES corresponding lane
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLane_2Configuration_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES Lane 3 Configuration: 04.C1F0 */
/*                  PHY XS SERDES Lane 3 Configuration: 04.C1F0 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES Lane 3 Configuration */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 04.C1F0.0 R/W SERDES Lane 3 Reset
                        AQ_PhyXS_SerdesLane_3Configuration_APPIA.u0.bits_0.serdesLane_3Reset

                        Default = 0x1

                        0 = Reset SERDES corresponding lane
                        

                 <B>Notes:</B>
                        Active low. Asynchronous. When all channels are being reset, CMU is reset. Separate reset for CMU reset does not exist.  */
      unsigned int   serdesLane_3Reset : 1;    /* 04.C1F0.0  R/W      Default = 0x1 */
                     /* 0 = Reset SERDES corresponding lane
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLane_3Configuration_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS SERDES LUT: 04.C200 */
/*                  PHY XS SERDES LUT: 04.C200 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS SERDES LUT */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 04.C200.7:0 R/W SERDES AHB Data [7:0]
                        AQ_PhyXS_SerdesLut_APPIA.u0.bits_0.serdesAhbData

                        Default = 0x00

                        SERDES AHB Data
                        

                 <B>Notes:</B>
                        The SERDES registers mappings are mapped to valid addresses from 0xC200 to 0xC2FF. Read and write to these address to read and write the registers inside the SERDES. 
                        
                        The SERDES Device Mapping is configured by setting the  See SERDES AHB Address MSB [2:0]  bits in 4.C180.  */
      unsigned int   serdesAhbData : 8;    /* 04.C200.7:0  R/W      Default = 0x00 */
                     /* SERDES AHB Data
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_SerdesLut_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning: 04.C440 */
/*                  PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning: 04.C440 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C440.F:E R/WPD High-speed Clock Output Select [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u0.bits_0.high_speedClockOutputSelect

                        Provisionable Default = 0x0

                        These bits select the output frequency of the high-speed clock output on the primary PHY (PHY0):
                        0x3 = 400 MHz output
                        0x2 = 156.25 MHz output
                        0x1 = 125 MHz output
                        0x0 = Output Disabled
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        These fields can only be changed through the primary PHY only (i.e. PHY 0)!!
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   high_speedClockOutputSelect : 2;    /* 04.C440.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* These bits select the output frequency of the high-speed clock output on the primary PHY (PHY0):
                        0x3 = 400 MHz output
                        0x2 = 156.25 MHz output
                        0x1 = 125 MHz output
                        0x0 = Output Disabled
                          */
                    /*! \brief 04.C440.D R/WPD High-speed Clock Output Source
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u0.bits_0.high_speedClockOutputSource

                        Provisionable Default = 0x0

                        This bit selects whether the output comes from primary PHY (PHY0) or the secondary PHY (PHY1)
                        0 = Primary PHY is source
                        1 = Secondary PHY is source
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        These fields can only be changed through the primary PHY only (i.e. PHY 0)!!
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   high_speedClockOutputSource : 1;    /* 04.C440.D  R/WPD      Provisionable Default = 0x0 */
                     /* This bit selects whether the output comes from primary PHY (PHY0) or the secondary PHY (PHY1)
                        0 = Primary PHY is source
                        1 = Secondary PHY is source
                          */
                    /*! \brief 04.C440.C R/WPD 25 MHz Disable
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u0.bits_0._25MhzDisable

                        Provisionable Default = 0x0

                        This bit disables the output of the 25 MHz reference clock:
                        1 = Disable the 25 MHz output
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        These fields can only be changed through the primary PHY only (i.e. PHY 0)!!
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   _25MhzDisable : 1;    /* 04.C440.C  R/WPD      Provisionable Default = 0x0 */
                     /* This bit disables the output of the 25 MHz reference clock:
                        1 = Disable the 25 MHz output
                          */
                    /*! \brief 04.C440.B R/WPD 25 MHz Clock Output Source
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u0.bits_0._25MhzClockOutputSource

                        Provisionable Default = 0x0

                        This bit selects whether the output comes from primary PHY (PHY0) or the secondary PHY (PHY1)
                        0 = Primary PHY is source
                        1 = Secondary PHY is source
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        These fields can only be changed through the primary PHY only (i.e. PHY 0)!!
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   _25MhzClockOutputSource : 1;    /* 04.C440.B  R/WPD      Provisionable Default = 0x0 */
                     /* This bit selects whether the output comes from primary PHY (PHY0) or the secondary PHY (PHY1)
                        0 = Primary PHY is source
                        1 = Secondary PHY is source
                          */
                    /*! \brief 04.C440.A:1 R/WPD Reserved Transmit Provisioning 1 [9:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u0.bits_0.reservedTransmitProvisioning_1

                        Provisionable Default = 0x000

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_1 : 10;    /* 04.C440.A:1  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C440.0 R/WSC Load SERDES Parameters
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u0.bits_0.loadSerdesParameters

                        Default = 0x0

                        1 = Load SERDES parameters
                        0 = Load completed

                 <B>Notes:</B>
                        This self-clearing register initiates a load of all of the SERDES related parameters for both the Tx and Rx direction. These are:
                        
                        Rx and Tx Termination Impedance
                        Rx Attenuation
                        Rx Boost
                        Tx Pre-Emphasis
                        Tx Slew Rate Control
                        Tx Power-Down
                        
                        NOTE! This bit will not self-clear in the absence of a valid Rx signal that can be used to perform Rx autocal
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   loadSerdesParameters : 1;    /* 04.C440.0  R/WSC      Default = 0x0 */
                     /* 1 = Load SERDES parameters
                        0 = Load completed  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C441.F:E R/WPD System I/F 10G Operating Mode [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u1.bits_1.systemI_f10G_OperatingMode

                        Provisionable Default = 0x0

                        This field sets the 10G configuration of the system I/F:
                        0x0 = XAUI
                        0x1 = RXAUI
                        0x2 = XFI (SERDES2 = XFI1)
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.  */
      unsigned int   systemI_f10G_OperatingMode : 2;    /* 04.C441.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* This field sets the 10G configuration of the system I/F:
                        0x0 = XAUI
                        0x1 = RXAUI
                        0x2 = XFI (SERDES2 = XFI1)
                          */
                    /*! \brief 04.C441.D:9 R/WPD Reserved Transmit Provisioning 2a [4:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u1.bits_1.reservedTransmitProvisioning_2a

                        Provisionable Default = 0x00

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_2a : 5;    /* 04.C441.D:9  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C441.8:6 R/WPD PHY Operating Mode [2:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u1.bits_1.phyOperatingMode

                        Provisionable Default = 0x0

                        This field sets the connectivity of the PHY:
                        0x0 = Selected 10G mode on System I/F
                        UTP (RJ-45) is Network I/F
                        0x1 = Look-aside Mode: XFI1 is System I/F (SERDES 2 = XFI1 / SGMII1)
                        XFI0 is Network I/F (SERDES 0 = SFI0 / SGMII0)
                        0x2 = 1+ 1 (SERDES 2 = XFI1 / SGMII1 of the selected PHY (see Bit 5) is the System I/F)
                        0x3 = Split XFI
                        

                 <B>Notes:</B>
                        This register selects the basic PHY configuration. This field can only be changed via provisioning.  */
      unsigned int   phyOperatingMode : 3;    /* 04.C441.8:6  R/WPD      Provisionable Default = 0x0 */
                     /* This field sets the connectivity of the PHY:
                        0x0 = Selected 10G mode on System I/F
                        UTP (RJ-45) is Network I/F
                        0x1 = Look-aside Mode: XFI1 is System I/F (SERDES 2 = XFI1 / SGMII1)
                        XFI0 is Network I/F (SERDES 0 = SFI0 / SGMII0)
                        0x2 = 1+ 1 (SERDES 2 = XFI1 / SGMII1 of the selected PHY (see Bit 5) is the System I/F)
                        0x3 = Split XFI
                          */
                    /*! \brief 04.C441.5 R/WPD RXAUI Operating Mode
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u1.bits_1.rxauiOperatingMode

                        Provisionable Default = 0x0

                        1 = Dune
                        0 = Marvell
                        

                 <B>Notes:</B>
                        This bit governs whether the RXAUI functions in Marvell mode (default) or Dune mode.  */
      unsigned int   rxauiOperatingMode : 1;    /* 04.C441.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Dune
                        0 = Marvell
                          */
                    /*! \brief 04.C441.4 R/WPD 1+1 Working Channel
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u1.bits_1._1_1WorkingChannel

                        Provisionable Default = 0x0

                        0 = Even PHY is the working PHY in 1+1 mode
                        1 = Odd PHY is the working PHY in 1+1 mode
                        
  */
      unsigned int   _1_1WorkingChannel : 1;    /* 04.C441.4  R/WPD      Provisionable Default = 0x0 */
                     /* 0 = Even PHY is the working PHY in 1+1 mode
                        1 = Odd PHY is the working PHY in 1+1 mode
                          */
                    /*! \brief 04.C441.3:2 R/WPD Reserved Transmit Provisioning 2b [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u1.bits_1.reservedTransmitProvisioning_2b

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_2b : 2;    /* 04.C441.3:2  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C441.1:0 R/WPD Lookaside Port Operating Mode [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u1.bits_1.lookasidePortOperatingMode

                        Provisionable Default = 0x0

                        0x0 = 10GBASE-R (XFI0)
                        0x1 = 1000BASE-X (SGMII0)
                        0x2 = XSGMII (10G / 1G only)
                        0x3 = Reserved
                        

                 <B>Notes:</B>
                        This field is used to control the start-up behavior of the PHY's lookaside port I/F, when the PHY Operation Mode (Bits 7:6) is set to 0x1.  */
      unsigned int   lookasidePortOperatingMode : 2;    /* 04.C441.1:0  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = 10GBASE-R (XFI0)
                        0x1 = 1000BASE-X (SGMII0)
                        0x2 = XSGMII (10G / 1G only)
                        0x3 = Reserved
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C442.F:E R/WPD XAUI Rx Lane 3 SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u2.bits_2.xauiRxLane_3Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 3
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiRxLane_3Serdes : 2;    /* 04.C442.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 3
                          */
                    /*! \brief 04.C442.D:C R/WPD XAUI Rx Lane 2 SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u2.bits_2.xauiRxLane_2Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 2
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiRxLane_2Serdes : 2;    /* 04.C442.D:C  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 2
                          */
                    /*! \brief 04.C442.B:A R/WPD XAUI Rx Lane 1 SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u2.bits_2.xauiRxLane_1Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 1
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiRxLane_1Serdes : 2;    /* 04.C442.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 1
                          */
                    /*! \brief 04.C442.9:8 R/WPD XAUI Rx Lane 0 SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u2.bits_2.xauiRxLane_0Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 0
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiRxLane_0Serdes : 2;    /* 04.C442.9:8  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 0
                          */
                    /*! \brief 04.C442.7:4 R/WPD XAUI Rx Lane Invert [3:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u2.bits_2.xauiRxLaneInvert

                        Provisionable Default = 0x0

                        A 1 inverts the selected XAUI lane(s), with Bit 0 = Lane 0, etc.
                        
  */
      unsigned int   xauiRxLaneInvert : 4;    /* 04.C442.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* A 1 inverts the selected XAUI lane(s), with Bit 0 = Lane 0, etc.
                          */
                    /*! \brief 04.C442.3:2 R/WPD System SGMII Rx SERDES [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u2.bits_2.systemSgmiiRxSerdes

                        Provisionable Default = 0x0

                        This sets the lane to be used for System SGMII Rx Interface (GbE Tx path):
                        0x0 = SERDES 0
                        0x1 = SERDES 1
                        0x2 = SERDES 2
                        0x3 = SERDES 3
                        

                 <B>Notes:</B>
                        This selection is independent of what rate / format the system 10G interface is running at, except if look-aside mode (Bits 4.C441.7:6) . In this case, Lane 2 must be used as the SGMII interface. This field can only be changed via provisioning.  */
      unsigned int   systemSgmiiRxSerdes : 2;    /* 04.C442.3:2  R/WPD      Provisionable Default = 0x0 */
                     /* This sets the lane to be used for System SGMII Rx Interface (GbE Tx path):
                        0x0 = SERDES 0
                        0x1 = SERDES 1
                        0x2 = SERDES 2
                        0x3 = SERDES 3
                          */
                    /*! \brief 04.C442.1 R/WPD System SGMII Rx Invert
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u2.bits_2.systemSgmiiRxInvert

                        Provisionable Default = 0x0

                        1 = Invert the System SGMII Rx Interface
                        

                 <B>Notes:</B>
                        This inverts the SGMII Rx interface. This field can only be changed via provisioning.  */
      unsigned int   systemSgmiiRxInvert : 1;    /* 04.C442.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert the System SGMII Rx Interface
                          */
      unsigned int   reserved0 : 1;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C443.F R/WPD RXAUI Rx Lane 1 SERDES
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u3.bits_3.rxauiRxLane_1Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for RXAUI Lane1
                        

                 <B>Notes:</B>
                        These are used to change the mapping of the SERDES to the RXAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   rxauiRxLane_1Serdes : 1;    /* 04.C443.F  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for RXAUI Lane1
                          */
                    /*! \brief 04.C443.E R/WPD RXAUI Rx Lane 0 SERDES
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u3.bits_3.rxauiRxLane_0Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for RXAUI Lane0
                        

                 <B>Notes:</B>
                        These are used to change the mapping of the SERDES to the RXAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   rxauiRxLane_0Serdes : 1;    /* 04.C443.E  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for RXAUI Lane0
                          */
                    /*! \brief 04.C443.D:C R/WPD RXAUI Rx Lane Invert [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u3.bits_3.rxauiRxLaneInvert

                        Provisionable Default = 0x0

                        A 1 inverts the selected RXAUI lane(s), with Bit 0 = Lane 0, etc.
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   rxauiRxLaneInvert : 2;    /* 04.C443.D:C  R/WPD      Provisionable Default = 0x0 */
                     /* A 1 inverts the selected RXAUI lane(s), with Bit 0 = Lane 0, etc.
                          */
                    /*! \brief 04.C443.B R/WPD System XFI Rx Invert
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u3.bits_3.systemXfiRxInvert

                        Provisionable Default = 0x0

                        1 = Invert System XFI Rx (SERDES2 = XFI1)
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   systemXfiRxInvert : 1;    /* 04.C443.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert System XFI Rx (SERDES2 = XFI1)
                          */
                    /*! \brief 04.C443.A R/WPD Lookaside Port Rx Invert
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u3.bits_3.lookasidePortRxInvert

                        Provisionable Default = 0x0

                        1 = Invert XFI0 / SGMII0 Rx
                        

                 <B>Notes:</B>
                        SERDES0 = XFI0 / SGMII0 is the network interface. This field can only be changed via provisioning.  */
      unsigned int   lookasidePortRxInvert : 1;    /* 04.C443.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert XFI0 / SGMII0 Rx
                          */
                    /*! \brief 04.C443.9:2 R/WPD Reserved Transmit Provisioning 4 [7:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u3.bits_3.reservedTransmitProvisioning_4

                        Provisionable Default = 0x00

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_4 : 8;    /* 04.C443.9:2  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C443.1:0 R/WPD SERDES Rx Termination Impedance Control [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u3.bits_3.serdesRxTerminationImpedanceControl

                        Provisionable Default = 0x0

                        0x0 = -10%
                        0x1 = Nominal
                        0x2 = +10%
                        0x3 = Nominal
                        

                 <B>Notes:</B>
                        This sets the termination impedance for all of the SERDES. NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   serdesRxTerminationImpedanceControl : 2;    /* 04.C443.1:0  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = -10%
                        0x1 = Nominal
                        0x2 = +10%
                        0x3 = Nominal
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C444.F:B R/WPD Loopback Control [4:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u4.bits_4.loopbackControl

                        Provisionable Default = 0x00

                        0x00 = No loopback
                        0x01 = System Interface - System Loopback
                        0x02 = System Interface - System Loopback with Passthrough
                        0x03 = System Interface - Network Loopback
                        0x04 = System Interface - Network Loopback with Passthrough
                        0x05 = System Interface - Network Loopback with Passthrough and Merge
                        0x06 = System Interface - Peer-to-peer loopback
                        0x07 - 0x08 = Reserved
                        0x09 = Network Interface - System Loopback
                        0x0A = Network Interface - System Loopback with Passthrough
                        0x0B = Network Interface - Network Loopback
                        0x0C = Network Interface - Network Loopback with Passthrough
                        0x0D = Network Interface - Peer-to-peer loopback
                        0x0E - 0x0F = Reserved
                        0x10 = Cross-connect System Loopback
                        0x11 = Cross-connect Network Loopback
                        0x12 - 0x13 = Reserved
                        0x14 = Network Interface - System Loopback via Loopback Plug
                        0x15 - 0x1F = Reserved
                        

                 <B>Notes:</B>
                        These bits, in conjunction with the chip configuration and the rate (Bits 1:0), select the loopback to configure for the chip. Setting one of these loopbacks provisions the chip for the specified loopback. Upon clearing the loopback, the chip returns to it's configuration prior to entering loopback (irregardless of whether other loopbacks were selected after the initial loopback).
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   loopbackControl : 5;    /* 04.C444.F:B  R/WPD      Provisionable Default = 0x00 */
                     /* 0x00 = No loopback
                        0x01 = System Interface - System Loopback
                        0x02 = System Interface - System Loopback with Passthrough
                        0x03 = System Interface - Network Loopback
                        0x04 = System Interface - Network Loopback with Passthrough
                        0x05 = System Interface - Network Loopback with Passthrough and Merge
                        0x06 = System Interface - Peer-to-peer loopback
                        0x07 - 0x08 = Reserved
                        0x09 = Network Interface - System Loopback
                        0x0A = Network Interface - System Loopback with Passthrough
                        0x0B = Network Interface - Network Loopback
                        0x0C = Network Interface - Network Loopback with Passthrough
                        0x0D = Network Interface - Peer-to-peer loopback
                        0x0E - 0x0F = Reserved
                        0x10 = Cross-connect System Loopback
                        0x11 = Cross-connect Network Loopback
                        0x12 - 0x13 = Reserved
                        0x14 = Network Interface - System Loopback via Loopback Plug
                        0x15 - 0x1F = Reserved
                          */
                    /*! \brief 04.C444.A:5 R/WPD Reserved Transmit Provisioning 5 [5:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u4.bits_4.reservedTransmitProvisioning_5

                        Provisionable Default = 0x00

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_5 : 6;    /* 04.C444.A:5  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C444.4 R/WPD MDI Packet Generation
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u4.bits_4.mdiPacketGeneration

                        Provisionable Default = 0x0

                        1 = CRPAT packet generation out MDI interface
                        0 = No CRPAT packet generation out MDI interface
                        

                 <B>Notes:</B>
                        Selecting this mode of operation causes the CRPAT packet generator in the PHY to output on the MDI interface at the selected rate.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   mdiPacketGeneration : 1;    /* 04.C444.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = CRPAT packet generation out MDI interface
                        0 = No CRPAT packet generation out MDI interface
                          */
                    /*! \brief 04.C444.3 R/WPD Look-Aside Port Packet Generation
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u4.bits_4.look_asidePortPacketGeneration

                        Provisionable Default = 0x0

                        1 = CRPAT packet generation out 10G look-aside interface (XFI0)
                        0 = No CRPAT packet generation out 10G look-aside interface (XFI0)
                        

                 <B>Notes:</B>
                        Selecting this mode of operation causes the CRPAT packet generator in the PHY to output on XFI0.
                        
                        NOTE!! This only functions if XFI1 (SERDES2) is selected as the system interface in (4.C441.F:E).
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   look_asidePortPacketGeneration : 1;    /* 04.C444.3  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = CRPAT packet generation out 10G look-aside interface (XFI0)
                        0 = No CRPAT packet generation out 10G look-aside interface (XFI0)
                          */
                    /*! \brief 04.C444.2 R/WPD System I/F Packet Generation
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u4.bits_4.systemI_fPacketGeneration

                        Provisionable Default = 0x0

                        1 = CRPAT packet generation out 10G system interface
                        0 = No CRPAT packet generation out 10G system interface
                        

                 <B>Notes:</B>
                        Selecting this mode of operation causes the CRPAT packet generator in the PHY to output CRPAT packets on the selected 10G system interface (4.C441.F:E)
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   systemI_fPacketGeneration : 1;    /* 04.C444.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = CRPAT packet generation out 10G system interface
                        0 = No CRPAT packet generation out 10G system interface
                          */
                    /*! \brief 04.C444.1:0 R/WPD Rate [1:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u4.bits_4.rate

                        Provisionable Default = 0x0

                        0x3 = 10G
                        0x2 = 1G
                        0x1 = 100M
                        0x0 = reserved
                        

                 <B>Notes:</B>
                        These bits select the rate for the loopback and packet generation. SERDES configuration, as well autonegotiation is controlled accordingly when a loopback is selected. For instance, if 100M system loopback on the network interface is selected, SGMII on the system interface is enabled to connect at 100M, and if passthrough is enabled 100BASE-TX will be the only advertised rate and will force a re-autonegotiation if not already connected at 100M.  */
      unsigned int   rate : 2;    /* 04.C444.1:0  R/WPD      Provisionable Default = 0x0 */
                     /* 0x3 = 10G
                        0x2 = 1G
                        0x1 = 100M
                        0x0 = reserved
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PHY XS Transmit (XAUI Rx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.C445.F R/WPD Disable Automatic Attenuation Calibration
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u5.bits_5.disableAutomaticAttenuationCalibration

                        Provisionable Default = 0x0

                        1 = Disable automatic attenuation calibration
                        

                 <B>Notes:</B>
                        If this is set, the values specified for attenuation in 4.C445 will be written. Otherwise these values will be determined by the internal autocal algorithm.  */
      unsigned int   disableAutomaticAttenuationCalibration : 1;    /* 04.C445.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable automatic attenuation calibration
                          */
                    /*! \brief 04.C445.E R/WPD Disable Automatic Boost Calibration
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u5.bits_5.disableAutomaticBoostCalibration

                        Provisionable Default = 0x0

                        1 = Disable automatic boost calibration
                        

                 <B>Notes:</B>
                        If this is set, the values specified for boost in 4.C445 will be written. Otherwise these values will be determined by the internal autocal algorithm.  */
      unsigned int   disableAutomaticBoostCalibration : 1;    /* 04.C445.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable automatic boost calibration
                          */
                    /*! \brief 04.C445.D R/WPD Disable Automatic Termination Calibration
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u5.bits_5.disableAutomaticTerminationCalibration

                        Provisionable Default = 0x0

                        1 = Disable automatic Rx and Tx termination calibration
                        

                 <B>Notes:</B>
                        If this is set, the values specified for the termination in 4.C443 and 4.E411 will be written. Otherwise these values will be determined by the internal autocal algorithm.  */
      unsigned int   disableAutomaticTerminationCalibration : 1;    /* 04.C445.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Disable automatic Rx and Tx termination calibration
                          */
                    /*! \brief 04.C445.C R/WSC Force Rx Re-Calibration
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u5.bits_5.forceRxRe_calibration

                        Default = 0x0

                        1 = When set, this bit initiates a re-calibration of the SERDES Rx path
                        

                 <B>Notes:</B>
                        Upon completion of the re-calibration, this bit will be set low.
                        
                        NOTE! This bit will not self-clear in the absence of a valid Rx signal that can be used to perform Rx autocal
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   forceRxRe_calibration : 1;    /* 04.C445.C  R/WSC      Default = 0x0 */
                     /* 1 = When set, this bit initiates a re-calibration of the SERDES Rx path
                          */
                    /*! \brief 04.C445.B:8 R/WPD Reserved Transmit Provisioning 6 [3:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u5.bits_5.reservedTransmitProvisioning_6

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedTransmitProvisioning_6 : 4;    /* 04.C445.B:8  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.C445.7:4 R/WPD Common Rx Attenuation [3:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u5.bits_5.commonRxAttenuation

                        Provisionable Default = 0x0

                        The common attenuation to apply to all of the receive SERDES lanes if attenuation calibration is disabled:
                        (Bit F = 1).
                        

                 <B>Notes:</B>
                        NOTE!! This register requires that bit 4.C440.0
                        be written in order to commit this value!  */
      unsigned int   commonRxAttenuation : 4;    /* 04.C445.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* The common attenuation to apply to all of the receive SERDES lanes if attenuation calibration is disabled:
                        (Bit F = 1).
                          */
                    /*! \brief 04.C445.3:0 R/WPD Common Rx Boost [3:0]
                        AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA.u5.bits_5.commonRxBoost

                        Provisionable Default = 0x0

                        The common boost to apply to all of the receive SERDES lanes if boost calibration is disabled:
                        (Bit E = 1).
                        

                 <B>Notes:</B>
                        NOTE!! This register requires that bit 4.C440.0
                        be written in order to commit this value!  */
      unsigned int   commonRxBoost : 4;    /* 04.C445.3:0  R/WPD      Provisionable Default = 0x0 */
                     /* The common boost to apply to all of the receive SERDES lanes if boost calibration is disabled:
                        (Bit E = 1).
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
} AQ_PhyXS_Transmit_xauiRx_ReservedVendorProvisioning_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) PCS Status: 04.C802 */
/*                  PHY XS Transmit (XAUI Rx) PCS Status: 04.C802 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) PCS Status */
  union
  {
    struct
    {
                    /*! \brief 04.C802.F:0 SCTL Tx Frame Counter LSW [F:0]
                        AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA.u0.bits_0.txFrameCounterLSW

                        Default = 0x0000

                        Tx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   txFrameCounterLSW : 16;    /* 04.C802.F:0  SCTL      Default = 0x0000 */
                     /* Tx Good Frame Counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) PCS Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 04.C803.9:0 SCTM Tx Frame Counter MSW [9:0]
                        AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA.u1.bits_1.txFrameCounterMSW

                        Default = 0x000

                        Tx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   txFrameCounterMSW : 10;    /* 04.C803.9:0  SCTM      Default = 0x000 */
                     /* Tx Good Frame Counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) PCS Status */
  union
  {
    struct
    {
                    /*! \brief 04.C804.F:0 SCTL Tx Frame Error Counter LSW [F:0]
                        AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA.u2.bits_2.txFrameErrorCounterLSW

                        Default = 0x0000

                        Tx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   txFrameErrorCounterLSW : 16;    /* 04.C804.F:0  SCTL      Default = 0x0000 */
                     /* Tx Bad Frame Counter
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Transmit (XAUI Rx) PCS Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 04.C805.9:0 SCTM Tx Frame Error Counter MSW [9:0]
                        AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA.u3.bits_3.txFrameErrorCounterMSW

                        Default = 0x000

                        Tx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   txFrameErrorCounterMSW : 10;    /* 04.C805.9:0  SCTM      Default = 0x000 */
                     /* Tx Bad Frame Counter
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PhyXS_Transmit_xauiRx_PcsStatus_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Vendor Alarms: 04.CC00 */
/*                  PHY XS Transmit (XAUI Rx) Vendor Alarms: 04.CC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 04.CC00.F LH CRPAT Test Pattern Checker Sync Error
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u0.bits_0.crpatTestPatternCheckerSyncError

                        

                        1 = Test pattern checker is out of sync
                        0 = Test pattern checker is in sync
                        
  */
      unsigned int   crpatTestPatternCheckerSyncError : 1;    /* 04.CC00.F  LH       */
                     /* 1 = Test pattern checker is out of sync
                        0 = Test pattern checker is in sync
                          */
                    /*! \brief 04.CC00.E:B LH PRBS Test Pattern Checker Sync Error [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u0.bits_0.prbsTestPatternCheckerSyncError

                        

                        1 = Test pattern checker is out of sync
                        0 = Test pattern checker is in sync
                        
                        Bit 0 corresponds to lane 0 and so on
                        
  */
      unsigned int   prbsTestPatternCheckerSyncError : 4;    /* 04.CC00.E:B  LH       */
                     /* 1 = Test pattern checker is out of sync
                        0 = Test pattern checker is in sync
                        
                        Bit 0 corresponds to lane 0 and so on
                          */
      unsigned int   reserved0 : 11;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Vendor Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 04.CC01.D LH XAUI Rx Sequence Ordered Set Deletion
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u1.bits_1.xauiRxSequenceOrderedSetDeletion

                        

                        1 = Sequence ordered set was deleted on the XAUI Rx interface
                        
  */
      unsigned int   xauiRxSequenceOrderedSetDeletion : 1;    /* 04.CC01.D  LH       */
                     /* 1 = Sequence ordered set was deleted on the XAUI Rx interface
                          */
      unsigned int   reserved1 : 1;
                    /*! \brief 04.CC01.B:A LL XAUI Rx RXAUI Lane Alignment Lock Status [1:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u1.bits_1.xauiRxRxauiLaneAlignmentLockStatus

                        

                        1 = Lanes locked
                        

                 <B>Notes:</B>
                        Bit 0 is lock status for RXAUI lanes 0 & 1
                        Bit 1 is lock status for RXAUI lanes 2 & 3  */
      unsigned int   xauiRxRxauiLaneAlignmentLockStatus : 2;    /* 04.CC01.B:A  LL       */
                     /* 1 = Lanes locked
                          */
                    /*! \brief 04.CC01.9 LH XAUI Rx Reserved XGMII Character Received
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u1.bits_1.xauiRxReservedXgmiiCharacterReceived

                        

                        1 = Reserved XGMII character was received on the XAUI Rx interface
                        
  */
      unsigned int   xauiRxReservedXgmiiCharacterReceived : 1;    /* 04.CC01.9  LH       */
                     /* 1 = Reserved XGMII character was received on the XAUI Rx interface
                          */
                    /*! \brief 04.CC01.8 LH XAUI Rx Invalid XGMII Character Received
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u1.bits_1.xauiRxInvalidXgmiiCharacterReceived

                        

                        1 = Invalid XGMII character was received on the XAUI Rx interface
                        
  */
      unsigned int   xauiRxInvalidXgmiiCharacterReceived : 1;    /* 04.CC01.8  LH       */
                     /* 1 = Invalid XGMII character was received on the XAUI Rx interface
                          */
                    /*! \brief 04.CC01.7:4 LH XAUI Rx Code Violation Error [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u1.bits_1.xauiRxCodeViolationError

                        

                        1 = A code violation error was detected on the corresponding lane of the XAUI Rx interface.
                        
                        Bit 0 corresponds to lane 0 and so on
                        
  */
      unsigned int   xauiRxCodeViolationError : 4;    /* 04.CC01.7:4  LH       */
                     /* 1 = A code violation error was detected on the corresponding lane of the XAUI Rx interface.
                        
                        Bit 0 corresponds to lane 0 and so on
                          */
                    /*! \brief 04.CC01.3:0 LH XAUI Rx Running Disparity Error [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u1.bits_1.xauiRxRunningDisparityError

                        

                        1 = A running disparity error was detected on the corresponding lane of the XAUI Rx interface.
                        
                        Bit 0 corresponds to lane 0 and so on
                        
  */
      unsigned int   xauiRxRunningDisparityError : 4;    /* 04.CC01.3:0  LH       */
                     /* 1 = A running disparity error was detected on the corresponding lane of the XAUI Rx interface.
                        
                        Bit 0 corresponds to lane 0 and so on
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 04.CC02.F:C LH Loss of Signal [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u2.bits_2.lossOfSignal

                        

                        1 = Loss of Signal on associated logical lane:
                        Bit 0: XFI0, RXAUI Lane 0, XAUI Lane 0, SGMII
                        Bit 1: XAUI Lane 1
                        Bit 2: XFI1, RXAUI Lane 1, XAUI Lane 2
                        Bit 3: XAUI Lane 3
                        

                 <B>Notes:</B>
                        These bits provide the Loss of Signal indication for the logical SERDES lane that loses signal.
                          */
      unsigned int   lossOfSignal : 4;    /* 04.CC02.F:C  LH       */
                     /* 1 = Loss of Signal on associated logical lane:
                        Bit 0: XFI0, RXAUI Lane 0, XAUI Lane 0, SGMII
                        Bit 1: XAUI Lane 1
                        Bit 2: XFI1, RXAUI Lane 1, XAUI Lane 2
                        Bit 3: XAUI Lane 3
                          */
                    /*! \brief 04.CC02.B:0 LH Reserved PHY XS Transmit Alarms [B:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA.u2.bits_2.reservedPhyXsTransmitAlarms

                        

                        Reserved
                        
  */
      unsigned int   reservedPhyXsTransmitAlarms : 12;    /* 04.CC02.B:0  LH       */
                     /* Reserved
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PhyXS_Transmit_xauiRx_VendorAlarms_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Standard Interrupt Mask: 04.D000 */
/*                  PHY XS Transmit (XAUI Rx) Standard Interrupt Mask: 04.D000 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 04.D000.2 R/WPD PHY XS Transmit Link Alignment Status Mask
                        AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA.u0.bits_0.phyXS_TransmitLinkAlignmentStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Mask for Bit 4.1.2. Note this bit also shows up as Bit 4.24.C, but only as a status bit.  */
      unsigned int   phyXS_TransmitLinkAlignmentStatusMask : 1;    /* 04.D000.2  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Standard Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 04.D001.B R/WPD Transmit Fault Mask
                        AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA.u1.bits_1.transmitFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 4.8.B  */
      unsigned int   transmitFaultMask : 1;    /* 04.D001.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D001.A R/WPD Receive Fault Mask
                        AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA.u1.bits_1.receiveFaultMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation

                 <B>Notes:</B>
                        Bit 4.8.A  */
      unsigned int   receiveFaultMask : 1;    /* 04.D001.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 10;
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_Transmit_xauiRx_StandardInterruptMask_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask: 04.D400 */
/*                  PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask: 04.D400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 04.D400.F R/WPD CRPAT Test Pattern Checker Sync Error Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u0.bits_0.crpatTestPatternCheckerSyncErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   crpatTestPatternCheckerSyncErrorMask : 1;    /* 04.D400.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D400.E:B R/WPD PRBS Test Pattern Checker Sync Error Mask [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u0.bits_0.prbsTestPatternCheckerSyncErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   prbsTestPatternCheckerSyncErrorMask : 4;    /* 04.D400.E:B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 11;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 2;
                    /*! \brief 04.D401.D R/WPD XAUI Rx Sequence Ordered Set Deletion Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u1.bits_1.xauiRxSequenceOrderedSetDeletionMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxSequenceOrderedSetDeletionMask : 1;    /* 04.D401.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved1 : 1;
                    /*! \brief 04.D401.B:A R/WPD XAUI Rx RXAUI Lane Alignment Lock Status Mask [1:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u1.bits_1.xauiRxRxauiLaneAlignmentLockStatusMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   xauiRxRxauiLaneAlignmentLockStatusMask : 2;    /* 04.D401.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.D401.9 R/WPD XAUI Rx Reserved XGMII Character Received Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u1.bits_1.xauiRxReservedXgmiiCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxReservedXgmiiCharacterReceivedMask : 1;    /* 04.D401.9  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D401.8 R/WPD XAUI Rx Invalid XGMII Character Received Mask
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u1.bits_1.xauiRxInvalidXgmiiCharacterReceivedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxInvalidXgmiiCharacterReceivedMask : 1;    /* 04.D401.8  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D401.7:4 R/WPD XAUI Rx Code Violation Error Mask [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u1.bits_1.xauiRxCodeViolationErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxCodeViolationErrorMask : 4;    /* 04.D401.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.D401.3:0 R/WPD XAUI Rx Running Disparity Error Mask [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u1.bits_1.xauiRxRunningDisparityErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   xauiRxRunningDisparityErrorMask : 4;    /* 04.D401.3:0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 04.D402.F:C R/W Loss of Signal Mask [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u2.bits_2.lossOfSignalMask

                        Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   lossOfSignalMask : 4;    /* 04.D402.F:C  R/W      Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 04.D402.B:0 R/W Reserved PHY XS Transmit Alarms Mask [B:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA.u2.bits_2.reservedPhyXsTransmitAlarmsMask

                        Default = 0x000

                        Reserved for future use
                        
  */
      unsigned int   reservedPhyXsTransmitAlarmsMask : 12;    /* 04.D402.B:0  R/W      Default = 0x000 */
                     /* Reserved for future use
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PhyXS_Transmit_xauiRx_VendorInterruptMask_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Vendor Debug: 04.D800 */
/*                  PHY XS Transmit (XAUI Rx) Vendor Debug: 04.D800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 04.D800.F R/W Test Pattern Force Error
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.testPatternForceError

                        Default = 0x0

                        1 = Force test pattern error
                        

                 <B>Notes:</B>
                        This injects 10 PRBS Errors or 32 CRPAT errors  */
      unsigned int   testPatternForceError : 1;    /* 04.D800.F  R/W      Default = 0x0 */
                     /* 1 = Force test pattern error
                          */
                    /*! \brief 04.D800.E R/W Test Pattern Mode 7 Force Error
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.testPatternMode_7ForceError

                        Default = 0x0

                        1 = Force test pattern #7 error
                        

                 <B>Notes:</B>
                        This injects 32 errors  */
      unsigned int   testPatternMode_7ForceError : 1;    /* 04.D800.E  R/W      Default = 0x0 */
                     /* 1 = Force test pattern #7 error
                          */
                    /*! \brief 04.D800.D R/W XAUI Rx Local Fault Injection
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.xauiRxLocalFaultInjection

                        Default = 0x0

                        1 = Inject local fault towards UTP Line
                        
  */
      unsigned int   xauiRxLocalFaultInjection : 1;    /* 04.D800.D  R/W      Default = 0x0 */
                     /* 1 = Inject local fault towards UTP Line
                          */
                    /*! \brief 04.D800.C:B R/WPD Test-Pattern Extended Select [1:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.test_patternExtendedSelect

                        Provisionable Default = 0x0

                        {Test-Pattern Extended Select [C:B],
                        Test-Pattern Select[1:0]}
                        0x0 = Annex 48A.1 High Frequency
                        0x1 = Annex 48A.2 Low Frequency
                        0x2 = Annex 48A.3 Mixed Frequency
                        0x4 = Annex 48A.4 CRPAT
                        0x5 = Annex 48A.5 CJPAT
                        0x6 = At speed CRPAT out the line
                        0x7 = PRBS-31 (x^31+x^28+1)
                        0x8 = PRBS-23 (x^23+x^18+1)
                        0x9 = PRBS-7 (x^7+x^6+1)
                        0xA = PRBS-15 (x^15+x^14+1)
                        0x3, 0xC -> 0xF = Reserved
                        

                 <B>Notes:</B>
                        These bits combine with the standard defined bits [1:0] in "PHY XS Standard XGXS Test Control: Address 4.19" on page 10 to define a broader suite of tests. 
                        
                          */
      unsigned int   test_patternExtendedSelect : 2;    /* 04.D800.C:B  R/WPD      Provisionable Default = 0x0 */
                     /* {Test-Pattern Extended Select [C:B],
                        Test-Pattern Select[1:0]}
                        0x0 = Annex 48A.1 High Frequency
                        0x1 = Annex 48A.2 Low Frequency
                        0x2 = Annex 48A.3 Mixed Frequency
                        0x4 = Annex 48A.4 CRPAT
                        0x5 = Annex 48A.5 CJPAT
                        0x6 = At speed CRPAT out the line
                        0x7 = PRBS-31 (x^31+x^28+1)
                        0x8 = PRBS-23 (x^23+x^18+1)
                        0x9 = PRBS-7 (x^7+x^6+1)
                        0xA = PRBS-15 (x^15+x^14+1)
                        0x3, 0xC -> 0xF = Reserved
                          */
                    /*! \brief 04.D800.A R/WPD Test Pattern Check Enable
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.testPatternCheckEnable

                        Provisionable Default = 0x0

                        1 = Test pattern checker enabled
                        0 = Test pattern checker not enabled
                        

                 <B>Notes:</B>
                        Test pattern checker enable. (Used for PRBS, Annex 48.4, and datapath error checking.) This should only be enabled after the test mode is selected.  */
      unsigned int   testPatternCheckEnable : 1;    /* 04.D800.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Test pattern checker enabled
                        0 = Test pattern checker not enabled
                          */
      unsigned int   reserved0 : 2;
                    /*! \brief 04.D800.7 R/WPD Test Pattern Check Point
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.testPatternCheckPoint

                        Provisionable Default = 0x0

                        Test pattern check point for CRPAT and data path tests.
                        

                 <B>Notes:</B>
                        This is latched on the rising edge of  See Test Pattern Check Enable   */
      unsigned int   testPatternCheckPoint : 1;    /* 04.D800.7  R/WPD      Provisionable Default = 0x0 */
                     /* Test pattern check point for CRPAT and data path tests.
                          */
                    /*! \brief 04.D800.6 R/WPD Test Pattern Mode 7 Check Enable
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.testPatternMode_7CheckEnable

                        Provisionable Default = 0x0

                        Enable checking for Test Mode 7
                        
  */
      unsigned int   testPatternMode_7CheckEnable : 1;    /* 04.D800.6  R/WPD      Provisionable Default = 0x0 */
                     /* Enable checking for Test Mode 7
                          */
                    /*! \brief 04.D800.5 R/WPD Test Pattern Invert
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.testPatternInvert

                        Provisionable Default = 0x1

                        Inverts the PRBS generation and checking
                        

                 <B>Notes:</B>
                        Inversion can also be done using the individual Tx and Rx lane inversion bits.  */
      unsigned int   testPatternInvert : 1;    /* 04.D800.5  R/WPD      Provisionable Default = 0x1 */
                     /* Inverts the PRBS generation and checking
                          */
                    /*! \brief 04.D800.4:0 R/WPD Test Pattern Synchronization Threshold [4:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u0.bits_0.testPatternSynchronizationThreshold

                        Provisionable Default = 0x0A

                        PRBS synchronization threshold configuration. If the number of PRBS bit errors is greater than or equal to the threshold within a 4 clock cycle window, the PRBS checker will declare a synchronization error and attempt to resynchronize to the incoming PRBS pattern. Setting this to 0, disables the resynchronization
                        
  */
      unsigned int   testPatternSynchronizationThreshold : 5;    /* 04.D800.4:0  R/WPD      Provisionable Default = 0x0A */
                     /* PRBS synchronization threshold configuration. If the number of PRBS bit errors is greater than or equal to the threshold within a 4 clock cycle window, the PRBS checker will declare a synchronization error and attempt to resynchronize to the incoming PRBS pattern. Setting this to 0, disables the resynchronization
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Vendor Debug */
  union
  {
    struct
    {
      unsigned int   reserved0 : 1;
                    /*! \brief 04.D801.E:C R/W Test Pattern Insert Extra Idles [2:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u1.bits_1.testPatternInsertExtraIdles

                        Default = 0x0

                        Number of extra 4 Idle Octets to insert
                        

                 <B>Notes:</B>
                        Number of extra 4 idle octets to insert in CRPAT and CJPAT generation.  */
      unsigned int   testPatternInsertExtraIdles : 3;    /* 04.D801.E:C  R/W      Default = 0x0 */
                     /* Number of extra 4 Idle Octets to insert
                          */
                    /*! \brief 04.D801.B:8 R/W Test Pattern Check Select [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u1.bits_1.testPatternCheckSelect

                        Default = 0x0

                        1 = Enable PRBS checking on the corresponding XAUI Rx Lane
                        
  */
      unsigned int   testPatternCheckSelect : 4;    /* 04.D801.B:8  R/W      Default = 0x0 */
                     /* 1 = Enable PRBS checking on the corresponding XAUI Rx Lane
                          */
      unsigned int   reserved1 : 4;
                    /*! \brief 04.D801.3:0 R/W Test Pattern Channel Select [3:0]
                        AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA.u1.bits_1.testPatternChannelSelect

                        Default = 0x0

                        1 = Test Pattern enabled
                        

                 <B>Notes:</B>
                        Used to select which XAUI channel(s) the PRBSis inserted on.   */
      unsigned int   testPatternChannelSelect : 4;    /* 04.D801.3:0  R/W      Default = 0x0 */
                     /* 1 = Test Pattern enabled
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_PhyXS_Transmit_xauiRx_VendorDebug_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Transmit (XAUI Rx) Test Pattern Error Counter: 04.D810 */
/*                  PHY XS Transmit (XAUI Rx) Test Pattern Error Counter: 04.D810 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D810.F:0 SCT Channel 0 Test Pattern Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA.u0.bits_0.channel_0TestPatternErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                        

                 <B>Notes:</B>
                        Clear on read. This is a saturating 16-bit counter which accumulates the number of test errors during pattern test. Note that the API must be used to read the x^15 error counts.  */
      unsigned int   channel_0TestPatternErrorCounter : 16;    /* 04.D810.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D811.F:0 SCT Channel 1 Test Pattern Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA.u1.bits_1.channel_1TestPatternErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                        

                 <B>Notes:</B>
                        Clear on read. This is a saturating 16-bit counter which accumulates the number of test errors during pattern test. Note that the API must be used to read the x^15 error counts.  */
      unsigned int   channel_1TestPatternErrorCounter : 16;    /* 04.D811.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D812.F:0 SCT Channel 2 Test Pattern Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA.u2.bits_2.channel_2TestPatternErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                        

                 <B>Notes:</B>
                        Clear on read. This is a saturating 16-bit counter which accumulates the number of test errors during pattern test. Note that the API must be used to read the x^15 error counts.  */
      unsigned int   channel_2TestPatternErrorCounter : 16;    /* 04.D812.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D813.F:0 SCT Channel 3 Test Pattern Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA.u3.bits_3.channel_3TestPatternErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                        

                 <B>Notes:</B>
                        Clear on read. This is a saturating 16-bit counter which accumulates the number of test errors during pattern test. Note that the API must be used to read the x^15 error counts.  */
      unsigned int   channel_3TestPatternErrorCounter : 16;    /* 04.D813.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode. Error counters for CRPAT, CJPAT, XAUI PRBS7,23,31 (for channel(s) selected). Note that CRPAT and CJPAT only use channel 0
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PHY XS Transmit (XAUI Rx) Test Pattern Error Counter */
  union
  {
    struct
    {
                    /*! \brief 04.D814.F:0 SCT Test Pattern Mode 7 Error Counter [F:0]
                        AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA.u4.bits_4.testPatternMode_7ErrorCounter

                        Default = 0x0000

                        A saturating 16 bit counter for errors detected from the test mode #7
                        

                 <B>Notes:</B>
                        This is a saturating 16-bit counter which accumulates the number of test errors during pattern test as specified in test mode #7 Clause 55 test.  */
      unsigned int   testPatternMode_7ErrorCounter : 16;    /* 04.D814.F:0  SCT      Default = 0x0000 */
                     /* A saturating 16 bit counter for errors detected from the test mode #7
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
} AQ_PhyXS_Transmit_xauiRx_TestPatternErrorCounter_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning: 04.E410 */
/*                  PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning: 04.E410 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E410.F:E R/WPD XAUI Tx Lane 3 SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u0.bits_0.xauiTxLane_3Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 3
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiTxLane_3Serdes : 2;    /* 04.E410.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 3
                          */
                    /*! \brief 04.E410.D:C R/WPD XAUI Tx Lane 2 SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u0.bits_0.xauiTxLane_2Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 2
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiTxLane_2Serdes : 2;    /* 04.E410.D:C  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 2
                          */
                    /*! \brief 04.E410.B:A R/WPD XAUI Tx Lane 1 SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u0.bits_0.xauiTxLane_1Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 1
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiTxLane_1Serdes : 2;    /* 04.E410.B:A  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 1
                          */
                    /*! \brief 04.E410.9:8 R/WPD XAUI Tx Lane 0 SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u0.bits_0.xauiTxLane_0Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for XAUI Lane 0
                        

                 <B>Notes:</B>
                        
                        
                        
                        
                        
                        
                        These are used to change the mapping of the SERDES to the XAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   xauiTxLane_0Serdes : 2;    /* 04.E410.9:8  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for XAUI Lane 0
                          */
                    /*! \brief 04.E410.7:4 R/WPD XAUI Tx Lane Invert [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u0.bits_0.xauiTxLaneInvert

                        Provisionable Default = 0x0

                        A 1 inverts the selected XAUI lane(s), with Bit 0 = Lane 0, etc.
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   xauiTxLaneInvert : 4;    /* 04.E410.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* A 1 inverts the selected XAUI lane(s), with Bit 0 = Lane 0, etc.
                          */
                    /*! \brief 04.E410.3:2 R/WPD System SGMII Tx SERDES [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u0.bits_0.systemSgmiiTxSerdes

                        Provisionable Default = 0x0

                        This sets the lane to be used for System SGMII Tx (GbE Rx path):
                        0x0 = SERDES 0
                        0x1 = SERDES 1
                        0x2 = SERDES 2
                        0x3 = SERDES 3
                        

                 <B>Notes:</B>
                        This selection is independent of what rate / format the system 10G interface is running at, except if look-aside mode (Bits 4.C441.7:6) . In this case, Lane 2 must be used as the SGMII interface. This field can only be changed via provisioning.
                          */
      unsigned int   systemSgmiiTxSerdes : 2;    /* 04.E410.3:2  R/WPD      Provisionable Default = 0x0 */
                     /* This sets the lane to be used for System SGMII Tx (GbE Rx path):
                        0x0 = SERDES 0
                        0x1 = SERDES 1
                        0x2 = SERDES 2
                        0x3 = SERDES 3
                          */
                    /*! \brief 04.E410.1 R/WPD System SGMII Tx Invert
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u0.bits_0.systemSgmiiTxInvert

                        Provisionable Default = 0x0

                        1 = Invert System SGMII Tx Interface
                        

                 <B>Notes:</B>
                        This inverts the System SGMII Tx interface. This field can only be changed via provisioning.  */
      unsigned int   systemSgmiiTxInvert : 1;    /* 04.E410.1  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert System SGMII Tx Interface
                          */
                    /*! \brief 04.E410.0 R/WPD Reserved Receive Provisioning 1
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u0.bits_0.reservedReceiveProvisioning_1

                        Provisionable Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveProvisioning_1 : 1;    /* 04.E410.0  R/WPD      Provisionable Default = 0x0 */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E411.F R/WPD RXAUI Tx Lane 1 SERDES
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u1.bits_1.rxauiTxLane_1Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for RXAUI Lane 1
                        

                 <B>Notes:</B>
                        These are used to change the mapping of the SERDES to the RXAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   rxauiTxLane_1Serdes : 1;    /* 04.E411.F  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for RXAUI Lane 1
                          */
                    /*! \brief 04.E411.E R/WPD RXAUI Tx Lane 0 SERDES
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u1.bits_1.rxauiTxLane_0Serdes

                        Provisionable Default = 0x0

                        Designates the SERDES for RXAUI Lane 0
                        

                 <B>Notes:</B>
                        These are used to change the mapping of the SERDES to the RXAUI lanes, allowing for flexible PCB layout. This field can only be changed via provisioning.  */
      unsigned int   rxauiTxLane_0Serdes : 1;    /* 04.E411.E  R/WPD      Provisionable Default = 0x0 */
                     /* Designates the SERDES for RXAUI Lane 0
                          */
                    /*! \brief 04.E411.D:C R/WPD RXAUI Tx Lane Invert [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u1.bits_1.rxauiTxLaneInvert

                        Provisionable Default = 0x0

                        A 1 inverts the selected RXAUI lane(s), with Bit 0 = Lane 0, etc.
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   rxauiTxLaneInvert : 2;    /* 04.E411.D:C  R/WPD      Provisionable Default = 0x0 */
                     /* A 1 inverts the selected RXAUI lane(s), with Bit 0 = Lane 0, etc.
                          */
                    /*! \brief 04.E411.B R/WPD System XFI Tx Invert
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u1.bits_1.systemXfiTxInvert

                        Provisionable Default = 0x0

                        1 = Invert System XFI Tx (SERDES2 = XFI1)
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   systemXfiTxInvert : 1;    /* 04.E411.B  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert System XFI Tx (SERDES2 = XFI1)
                          */
                    /*! \brief 04.E411.A R/WPD Lookaside Port Tx Invert
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u1.bits_1.lookasidePortTxInvert

                        Provisionable Default = 0x0

                        1 = Invert SERDES0 = XFI0 / SGMII0 Tx
                        

                 <B>Notes:</B>
                        This field can only be changed via provisioning.   */
      unsigned int   lookasidePortTxInvert : 1;    /* 04.E411.A  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Invert SERDES0 = XFI0 / SGMII0 Tx
                          */
                    /*! \brief 04.E411.9:2 R/WPD Reserved Receive Provisioning 2 [7:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u1.bits_1.reservedReceiveProvisioning_2

                        Provisionable Default = 0x00

                        Reserved for future use
                        
  */
      unsigned int   reservedReceiveProvisioning_2 : 8;    /* 04.E411.9:2  R/WPD      Provisionable Default = 0x00 */
                     /* Reserved for future use
                          */
                    /*! \brief 04.E411.1:0 R/WPD SERDES Tx Termination Impedance Control [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u1.bits_1.serdesTxTerminationImpedanceControl

                        Provisionable Default = 0x0

                        0x0 = -10%
                        0x1 = Nominal
                        0x2 = +10%
                        0x3 = Nominal
                        

                 <B>Notes:</B>
                        This sets the termination impedance for all of the SERDES. NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   serdesTxTerminationImpedanceControl : 2;    /* 04.E411.1:0  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = -10%
                        0x1 = Nominal
                        0x2 = +10%
                        0x3 = Nominal
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E412.F:E R/WPD Lane 0 Pre-Cursor Tap Weight [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u2.bits_2.lane_0Pre_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N+1pre-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_0Pre_cursorTapWeight : 2;    /* 04.E412.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N+1pre-cursor
                          */
                    /*! \brief 04.E412.D:B R/WPD Lane 0 N-1 Post-Cursor Tap Weight [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u2.bits_2.lane_0N_1Post_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N-1 post-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_0N_1Post_cursorTapWeight : 3;    /* 04.E412.D:B  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N-1 post-cursor
                          */
                    /*! \brief 04.E412.A:8 R/WPD Lane 0 N-2 Post-Cursor Tap Weight [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u2.bits_2.lane_0N_2Post_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N-2 post-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_0N_2Post_cursorTapWeight : 3;    /* 04.E412.A:8  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N-2 post-cursor
                          */
                    /*! \brief 04.E412.7:4 R/WPD Lane 0 Differential Output Voltage [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u2.bits_2.lane_0DifferentialOutputVoltage

                        Provisionable Default = 0x0

                        0x0 = Minimum
                        0xD = Maximum
                        0xE, 0xF = Reserved
                        

                 <B>Notes:</B>
                        This provides a continuous range of 14 levels from minimum to maximum output voltage. Minimum is nominally 200mV, and maximum is nominally 1V. Recommended settings are:
                        XFI = 0xD
                        RXAUI = 0x8
                        XAUI = 0x7
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_0DifferentialOutputVoltage : 4;    /* 04.E412.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Minimum
                        0xD = Maximum
                        0xE, 0xF = Reserved
                          */
                    /*! \brief 04.E412.3:1 R/WPD Lane 0 Slew Rate Control [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u2.bits_2.lane_0SlewRateControl

                        Provisionable Default = 0x0

                        0x0 = Fastest
                        0x7 = Slowest
                        

                 <B>Notes:</B>
                        This provides a continuous range of 8 levels from fastest to slowest slew rate
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_0SlewRateControl : 3;    /* 04.E412.3:1  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Fastest
                        0x7 = Slowest
                          */
                    /*! \brief 04.E412.0 R/WPD Lane 0 Power Down
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u2.bits_2.lane_0PowerDown

                        Provisionable Default = 0x0

                        1 = Power Down SERDES
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        This is used for debugging cross-talk issues in the link and forces this SERDES to remain powered down
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_0PowerDown : 1;    /* 04.E412.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Power Down SERDES
                        0 = Normal Operation
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E413.F:E R/WPD Lane 1 Pre-Cursor Tap Weight [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u3.bits_3.lane_1Pre_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N+1pre-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_1Pre_cursorTapWeight : 2;    /* 04.E413.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N+1pre-cursor
                          */
                    /*! \brief 04.E413.D:B R/WPD Lane 1 N-1 Post-Cursor Tap Weight [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u3.bits_3.lane_1N_1Post_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N-1 post-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_1N_1Post_cursorTapWeight : 3;    /* 04.E413.D:B  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N-1 post-cursor
                          */
                    /*! \brief 04.E413.A:8 R/WPD Lane 1 N-2 Post-Cursor Tap Weight [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u3.bits_3.lane_1N_2Post_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N-2 post-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_1N_2Post_cursorTapWeight : 3;    /* 04.E413.A:8  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N-2 post-cursor
                          */
                    /*! \brief 04.E413.7:4 R/WPD Lane 1 Differential Output Voltage [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u3.bits_3.lane_1DifferentialOutputVoltage

                        Provisionable Default = 0x0

                        0x0 = Minimum
                        0xD = Maximum
                        0xE, 0xF = Reserved
                        

                 <B>Notes:</B>
                        This provides a continuous range of 14 levels from minimum to maximum output voltage. Minimum is nominally 200mV, and maximum is nominally 1V. Recommended settings are:
                        XFI = 0xD
                        RXAUI = 0x8
                        XAUI = 0x7
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_1DifferentialOutputVoltage : 4;    /* 04.E413.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Minimum
                        0xD = Maximum
                        0xE, 0xF = Reserved
                          */
                    /*! \brief 04.E413.3:1 R/WPD Lane 1 Slew Rate Control [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u3.bits_3.lane_1SlewRateControl

                        Provisionable Default = 0x0

                        0x0 = Fastest
                        0x7 = Slowest
                        

                 <B>Notes:</B>
                        This provides a continuous range of 8 levels from fastest to slowest slew rate
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_1SlewRateControl : 3;    /* 04.E413.3:1  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Fastest
                        0x7 = Slowest
                          */
                    /*! \brief 04.E413.0 R/WPD Lane 1 Power Down
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u3.bits_3.lane_1PowerDown

                        Provisionable Default = 0x0

                        1 = Power Down SERDES
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        This is used for debugging cross-talk issues in the link and forces this SERDES to remain powered down
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_1PowerDown : 1;    /* 04.E413.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Power Down SERDES
                        0 = Normal Operation
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E414.F:E R/WPD Lane 2 Pre-Cursor Tap Weight [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u4.bits_4.lane_2Pre_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N+1pre-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_2Pre_cursorTapWeight : 2;    /* 04.E414.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N+1pre-cursor
                          */
                    /*! \brief 04.E414.D:B R/WPD Lane 2 N-1 Post-Cursor Tap Weight [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u4.bits_4.lane_2N_1Post_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N-1 post-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_2N_1Post_cursorTapWeight : 3;    /* 04.E414.D:B  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N-1 post-cursor
                          */
                    /*! \brief 04.E414.A:8 R/WPD Lane 2 N-2 Post-Cursor Tap Weight [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u4.bits_4.lane_2N_2Post_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N-2 post-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_2N_2Post_cursorTapWeight : 3;    /* 04.E414.A:8  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N-2 post-cursor
                          */
                    /*! \brief 04.E414.7:4 R/WPD Lane 2 Differential Output Voltage [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u4.bits_4.lane_2DifferentialOutputVoltage

                        Provisionable Default = 0x0

                        0x0 = Minimum
                        0xD = Maximum
                        0xE, 0xF = Reserved
                        

                 <B>Notes:</B>
                        This provides a continuous range of 14 levels from minimum to maximum output voltage. Minimum is nominally 200mV, and maximum is nominally 1V. Recommended settings are:
                        XFI = 0xD
                        RXAUI = 0x8
                        XAUI = 0x7
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_2DifferentialOutputVoltage : 4;    /* 04.E414.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Minimum
                        0xD = Maximum
                        0xE, 0xF = Reserved
                          */
                    /*! \brief 04.E414.3:1 R/WPD Lane 2 Slew Rate Control [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u4.bits_4.lane_2SlewRateControl

                        Provisionable Default = 0x0

                        0x0 = Fastest
                        0x7 = Slowest
                        

                 <B>Notes:</B>
                        This provides a continuous range of 8 levels from fastest to slowest slew rate
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_2SlewRateControl : 3;    /* 04.E414.3:1  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Fastest
                        0x7 = Slowest
                          */
                    /*! \brief 04.E414.0 R/WPD Lane 2 Power Down
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u4.bits_4.lane_2PowerDown

                        Provisionable Default = 0x0

                        1 = Power Down SERDES
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        This is used for debugging cross-talk issues in the link and forces this SERDES to remain powered down
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_2PowerDown : 1;    /* 04.E414.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Power Down SERDES
                        0 = Normal Operation
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of PHY XS Receive (XAUI Tx) Reserved Vendor Provisioning */
  union
  {
    struct
    {
                    /*! \brief 04.E415.F:E R/WPD Lane 3 Pre-Cursor Tap Weight [1:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u5.bits_5.lane_3Pre_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N+1pre-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_3Pre_cursorTapWeight : 2;    /* 04.E415.F:E  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N+1pre-cursor
                          */
                    /*! \brief 04.E415.D:B R/WPD Lane 3 N-1 Post-Cursor Tap Weight [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u5.bits_5.lane_3N_1Post_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N-1 post-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_3N_1Post_cursorTapWeight : 3;    /* 04.E415.D:B  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N-1 post-cursor
                          */
                    /*! \brief 04.E415.A:8 R/WPD Lane 3 N-2 Post-Cursor Tap Weight [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u5.bits_5.lane_3N_2Post_cursorTapWeight

                        Provisionable Default = 0x0

                        This indicates how many of the 16 SERDES drivers are assigned to the N-2 post-cursor
                        

                 <B>Notes:</B>
                        Each SERDES has a four-tap FIR structure consisting of an N+1 pre-cursor, a cursor (N), an N-1 post-cursor, and an N-2 post-cursor. Amongst these taps, there are 16 drivers that can be assigned, which determine the effective weight of each tap. These fields govern the assignment of drivers to the non-cursor taps, with the left-over drivers being assigned to the cursor tap.
                        
                        NOTE!! These registers require that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_3N_2Post_cursorTapWeight : 3;    /* 04.E415.A:8  R/WPD      Provisionable Default = 0x0 */
                     /* This indicates how many of the 16 SERDES drivers are assigned to the N-2 post-cursor
                          */
                    /*! \brief 04.E415.7:4 R/WPD Lane 3 Differential Output Voltage [3:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u5.bits_5.lane_3DifferentialOutputVoltage

                        Provisionable Default = 0x0

                        0x0 = Minimum
                        0xD = Maximum
                        0xE, 0xF = Reserved
                        

                 <B>Notes:</B>
                        This provides a continuous range of 14 levels from minimum to maximum output voltage. Minimum is nominally 200mV, and maximum is nominally 1V. Recommended settings are:
                        XFI = 0xD
                        RXAUI = 0x8
                        XAUI = 0x7
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_3DifferentialOutputVoltage : 4;    /* 04.E415.7:4  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Minimum
                        0xD = Maximum
                        0xE, 0xF = Reserved
                          */
                    /*! \brief 04.E415.3:1 R/WPD Lane 3 Slew Rate Control [2:0]
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u5.bits_5.lane_3SlewRateControl

                        Provisionable Default = 0x0

                        0x0 = Fastest
                        0x7 = Slowest
                        

                 <B>Notes:</B>
                        This provides a continuous range of 8 levels from fastest to slowest slew rate
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_3SlewRateControl : 3;    /* 04.E415.3:1  R/WPD      Provisionable Default = 0x0 */
                     /* 0x0 = Fastest
                        0x7 = Slowest
                          */
                    /*! \brief 04.E415.0 R/WPD Lane 3 Power Down
                        AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA.u5.bits_5.lane_3PowerDown

                        Provisionable Default = 0x0

                        1 = Power Down SERDES
                        0 = Normal Operation
                        

                 <B>Notes:</B>
                        This is used for debugging cross-talk issues in the link and forces this SERDES to remain powered down
                        
                        NOTE!! This register requires that bit 4.C440.0 be written in order to commit this value!  */
      unsigned int   lane_3PowerDown : 1;    /* 04.E415.0  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Power Down SERDES
                        0 = Normal Operation
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
} AQ_PhyXS_Receive_xauiTx_ReservedVendorProvisioning_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) PCS Status: 04.E802 */
/*                  PHY XS Receive (XAUI Tx) PCS Status: 04.E802 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) PCS Status */
  union
  {
    struct
    {
                    /*! \brief 04.E802.F:0 SCTL Rx Frame Counter LSW [F:0]
                        AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA.u0.bits_0.rxFrameCounterLSW

                        Default = 0x0000

                        Rx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   rxFrameCounterLSW : 16;    /* 04.E802.F:0  SCTL      Default = 0x0000 */
                     /* Rx Good Frame Counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Receive (XAUI Tx) PCS Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 04.E803.9:0 SCTM Rx Frame Counter MSW [9:0]
                        AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA.u1.bits_1.rxFrameCounterMSW

                        Default = 0x000

                        Rx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   rxFrameCounterMSW : 10;    /* 04.E803.9:0  SCTM      Default = 0x000 */
                     /* Rx Good Frame Counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Receive (XAUI Tx) PCS Status */
  union
  {
    struct
    {
                    /*! \brief 04.E804.F:0 SCTL Rx Frame Error Counter LSW [F:0]
                        AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA.u2.bits_2.rxFrameErrorCounterLSW

                        Default = 0x0000

                        Rx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   rxFrameErrorCounterLSW : 16;    /* 04.E804.F:0  SCTL      Default = 0x0000 */
                     /* Rx Bad Frame Counter
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of PHY XS Receive (XAUI Tx) PCS Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 04.E805.9:0 SCTM Rx Frame Error Counter MSW [9:0]
                        AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA.u3.bits_3.rxFrameErrorCounterMSW

                        Default = 0x000

                        Rx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 10G Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   rxFrameErrorCounterMSW : 10;    /* 04.E805.9:0  SCTM      Default = 0x000 */
                     /* Rx Bad Frame Counter
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
} AQ_PhyXS_Receive_xauiTx_PcsStatus_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Vendor Alarms: 04.EC00 */
/*                  PHY XS Receive (XAUI Tx) Vendor Alarms: 04.EC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Vendor Alarms */
  union
  {
    struct
    {
                    /*! \brief 04.EC00.F LH Reserved XGMII Character Received from PCS
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA.u0.bits_0.reservedXgmiiCharacterReceivedFromPcs

                        

                        1 = Reserved XGMII character was received from the PCS
                        
  */
      unsigned int   reservedXgmiiCharacterReceivedFromPcs : 1;    /* 04.EC00.F  LH       */
                     /* 1 = Reserved XGMII character was received from the PCS
                          */
                    /*! \brief 04.EC00.E LH Invalid XGMII Character Received from PCS
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA.u0.bits_0.invalidXgmiiCharacterReceivedFromPcs

                        

                        1 = Invalid XGMII character was received from the PCS
                        
  */
      unsigned int   invalidXgmiiCharacterReceivedFromPcs : 1;    /* 04.EC00.E  LH       */
                     /* 1 = Invalid XGMII character was received from the PCS
                          */
                    /*! \brief 04.EC00.D LH Link status Message Received from PCS
                        AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA.u0.bits_0.linkStatusMessageReceivedFromPcs

                        

                        1 = Link status message was received from the PCS
                        
  */
      unsigned int   linkStatusMessageReceivedFromPcs : 1;    /* 04.EC00.D  LH       */
                     /* 1 = Link status message was received from the PCS
                          */
      unsigned int   reserved0 : 13;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_Receive_xauiTx_VendorAlarms_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Vendor Interrupt Mask: 04.F400 */
/*                  PHY XS Receive (XAUI Tx) Vendor Interrupt Mask: 04.F400 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Vendor Interrupt Mask */
  union
  {
    struct
    {
                    /*! \brief 04.F400.F R/WPD Reserved XGMII Character Received from PCS Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA.u0.bits_0.reservedXgmiiCharacterReceivedFromPcsMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   reservedXgmiiCharacterReceivedFromPcsMask : 1;    /* 04.F400.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.F400.E R/WPD Invalid XGMII Character Received from PCS Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA.u0.bits_0.invalidXgmiiCharacterReceivedFromPcsMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   invalidXgmiiCharacterReceivedFromPcsMask : 1;    /* 04.F400.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
                    /*! \brief 04.F400.D R/WPD Link status Message Received from PCS Mask
                        AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA.u0.bits_0.linkStatusMessageReceivedFromPcsMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
  */
      unsigned int   linkStatusMessageReceivedFromPcsMask : 1;    /* 04.F400.D  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation  */
      unsigned int   reserved0 : 13;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_Receive_xauiTx_VendorInterruptMask_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Receive (XAUI Tx) Vendor Debug: 04.F800 */
/*                  PHY XS Receive (XAUI Tx) Vendor Debug: 04.F800 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Receive (XAUI Tx) Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 04.F800.F:D R/W XAUI Tx Error Injection Lane Select [2:0]
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u0.bits_0.xauiTxErrorInjectionLaneSelect

                        Default = 0x0

                        [F:D]
                        0x0 = Lane 0
                        0x1 = Lane 1
                        0x2 = Lane 2
                        0x3 = Lane 3
                        0x4 = All four lanes
                        

                 <B>Notes:</B>
                        This controls which of the 4 Tx XAUI lanes debug error injection occurs on.  */
      unsigned int   xauiTxErrorInjectionLaneSelect : 3;    /* 04.F800.F:D  R/W      Default = 0x0 */
                     /* [F:D]
                        0x0 = Lane 0
                        0x1 = Lane 1
                        0x2 = Lane 2
                        0x3 = Lane 3
                        0x4 = All four lanes
                          */
                    /*! \brief 04.F800.C R/W XAUI Tx Inject Synchronization Error
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u0.bits_0.xauiTxInjectSynchronizationError

                        Default = 0x0

                        1 = Inject a synchronization error
                        

                 <B>Notes:</B>
                        This injects a synchronization error on the lanes selected in F:D  */
      unsigned int   xauiTxInjectSynchronizationError : 1;    /* 04.F800.C  R/W      Default = 0x0 */
                     /* 1 = Inject a synchronization error
                          */
                    /*! \brief 04.F800.B R/W XAUI Tx Inject Alignment Error
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u0.bits_0.xauiTxInjectAlignmentError

                        Default = 0x0

                        1 = Inject an alignment error
                        

                 <B>Notes:</B>
                        This injects an alignment error on the lanes selected in F:D  */
      unsigned int   xauiTxInjectAlignmentError : 1;    /* 04.F800.B  R/W      Default = 0x0 */
                     /* 1 = Inject an alignment error
                          */
                    /*! \brief 04.F800.A R/W XAUI Tx Inject Code Violation
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u0.bits_0.xauiTxInjectCodeViolation

                        Default = 0x0

                        1 = Inject code violation error
                        

                 <B>Notes:</B>
                        This injects the 10B codeword on the lanes selected in F:D  */
      unsigned int   xauiTxInjectCodeViolation : 1;    /* 04.F800.A  R/W      Default = 0x0 */
                     /* 1 = Inject code violation error
                          */
                    /*! \brief 04.F800.9:0 R/W XAUI Tx 10B Violation Codeword [9:0]
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u0.bits_0.xauiTx_10bViolationCodeword

                        Default = 0x000

                        [9:0] = 10B violation codeword to be injected by writing a 1 to Bit A
                        
  */
      unsigned int   xauiTx_10bViolationCodeword : 10;    /* 04.F800.9:0  R/W      Default = 0x000 */
                     /* [9:0] = 10B violation codeword to be injected by writing a 1 to Bit A
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of PHY XS Receive (XAUI Tx) Vendor Debug */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of PHY XS Receive (XAUI Tx) Vendor Debug */
  union
  {
    struct
    {
                    /*! \brief 04.F802.F R/W PHY XS System Loopback Pass Through
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u2.bits_2.phyXS_SystemLoopbackPassThrough

                        Default = 0x0

                        When set to 1, this bit enables loopback traffic from the PHY XS System Loopback to pass-through towards the network UTP line.
                        When set to 0, the data sent towards the network UTP line will be all IDLEs when in PHY XS System Loopback
                        

                 <B>Notes:</B>
                        This enables traffic to pass through as well as loopback when the PHY XS System Loopback is enabled.  */
      unsigned int   phyXS_SystemLoopbackPassThrough : 1;    /* 04.F802.F  R/W      Default = 0x0 */
                     /* When set to 1, this bit enables loopback traffic from the PHY XS System Loopback to pass-through towards the network UTP line.
                        When set to 0, the data sent towards the network UTP line will be all IDLEs when in PHY XS System Loopback
                          */
                    /*! \brief 04.F802.E R/W PHY XS System Loopback Enable
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u2.bits_2.phyXS_SystemLoopbackEnable

                        Default = 0x0

                        1 = Enable PHY XS System Loopback mode
                        0 = Normal operation
                        

                 <B>Notes:</B>
                        This bit enables the PHY XS System Loopback from the Tx XAUI Interface after lane alignment to the Rx XAUI interface.  */
      unsigned int   phyXS_SystemLoopbackEnable : 1;    /* 04.F802.E  R/W      Default = 0x0 */
                     /* 1 = Enable PHY XS System Loopback mode
                        0 = Normal operation
                          */
                    /*! \brief 04.F802.D R/W XAUI Tx Local Fault Injection
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u2.bits_2.xauiTxLocalFaultInjection

                        Default = 0x0

                        1 = Inject local fault towards XAUI system side
                        0 = Normal operation
                        
  */
      unsigned int   xauiTxLocalFaultInjection : 1;    /* 04.F802.D  R/W      Default = 0x0 */
                     /* 1 = Inject local fault towards XAUI system side
                        0 = Normal operation
                          */
                    /*! \brief 04.F802.C R/W Reserved 4
                        AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA.u2.bits_2.reserved_4

                        Default = 0x0

                        Reserved for future use
                        
  */
      unsigned int   reserved_4 : 1;    /* 04.F802.C  R/W      Default = 0x0 */
                     /* Reserved for future use
                          */
      unsigned int   reserved0 : 12;
    } bits_2;
    uint16_t word_2;
  } u2;
} AQ_PhyXS_Receive_xauiTx_VendorDebug_APPIA;


/*---------------------------------------------------------------------------------*/
/*! \brief                PHY XS Vendor Global Interrupt Flags: 04.FC00 */
/*                  PHY XS Vendor Global Interrupt Flags: 04.FC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of PHY XS Vendor Global Interrupt Flags */
  union
  {
    struct
    {
                    /*! \brief 04.FC00.F RO Standard Alarms 1 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_APPIA.u0.bits_0.standardAlarms_1Interrupt

                        

                        1 = Interrupt in standard alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   standardAlarms_1Interrupt : 1;    /* 04.FC00.F  RO       */
                     /* 1 = Interrupt in standard alarms 1
                          */
                    /*! \brief 04.FC00.E RO Standard Alarms 2 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_APPIA.u0.bits_0.standardAlarms_2Interrupt

                        

                        1 = Interrupt in standard alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   standardAlarms_2Interrupt : 1;    /* 04.FC00.E  RO       */
                     /* 1 = Interrupt in standard alarms 2
                          */
      unsigned int   reserved0 : 3;
                    /*! \brief 04.FC00.A RO Vendor Specific Tx Alarms 1 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificTxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificTxAlarms_1Interrupt : 1;    /* 04.FC00.A  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 1
                          */
                    /*! \brief 04.FC00.9 RO Vendor Specific Tx Alarms 2 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificTxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificTxAlarms_2Interrupt : 1;    /* 04.FC00.9  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 2
                          */
                    /*! \brief 04.FC00.8 RO Vendor Specific Tx Alarms 3 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificTxAlarms_3Interrupt

                        

                        1 = Interrupt in vendor specific Tx alarms 
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificTxAlarms_3Interrupt : 1;    /* 04.FC00.8  RO       */
                     /* 1 = Interrupt in vendor specific Tx alarms 
                          */
      unsigned int   reserved1 : 5;
                    /*! \brief 04.FC00.2 RO Vendor Specific Rx Alarms 1 Interrupt
                        AQ_PhyXS_VendorGlobalInterruptFlags_APPIA.u0.bits_0.vendorSpecificRxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific Rx alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificRxAlarms_1Interrupt : 1;    /* 04.FC00.2  RO       */
                     /* 1 = Interrupt in vendor specific Rx alarms 1
                          */
      unsigned int   reserved2 : 2;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_PhyXS_VendorGlobalInterruptFlags_APPIA;

#endif
/*@}*/
/*@}*/
