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
*   for the GbE Registers block.
 */        

/*! \addtogroup registerMap
  @{
*/

/*! \defgroup GbE_registers GbE Registers
*   This module contains the data structures and doxygen comments
*   for the GbE Registers block.
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
*   This file contains the c header structures for the registers contained in the GbE Registers block.
*
*   The bit fields in this structure are from MSbit to LSbit
*
***********************************************************************/


/*@{*/
#ifndef AQ_EUR_GBE_REGS_HEADER
#define AQ_EUR_GBE_REGS_HEADER


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE Standard Device Identifier: 1D.0002 */
/*                  GbE Standard Device Identifier: 1D.0002 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 1D.0002.F:0 RO Device ID MSW [1F:10]
                        AQ_GbeStandardDeviceIdentifier_EUR.u0.bits_0.deviceIdMSW

                        

                        Bits 31 - 16 of Device ID
  */
      unsigned int   deviceIdMSW : 16;    /* 1D.0002.F:0  RO       */
                     /* Bits 31 - 16 of Device ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE Standard Device Identifier */
  union
  {
    struct
    {
                    /*! \brief 1D.0003.F:0 RO Device ID LSW [F:0]
                        AQ_GbeStandardDeviceIdentifier_EUR.u1.bits_1.deviceIdLSW

                        

                        Bits 15 - 0 of Device ID
  */
      unsigned int   deviceIdLSW : 16;    /* 1D.0003.F:0  RO       */
                     /* Bits 15 - 0 of Device ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_GbeStandardDeviceIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE Standard Devices in Package: 1D.0005 */
/*                  GbE Standard Devices in Package: 1D.0005 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE Standard Devices in Package */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 1D.0005.7 ROS Autonegotiation Present
                        AQ_GbeStandardDevicesInPackage_EUR.u0.bits_0.autonegotiationPresent

                        Default = 0x1

                        1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package

                 <B>Notes:</B>
                        This is always set to 1, as there is Autonegotiation in the PHY.  */
      unsigned int   autonegotiationPresent : 1;    /* 1D.0005.7  ROS      Default = 0x1 */
                     /* 1 = Autonegotiation is present in package
                        0 = Autonegotiation is not present in package  */
                    /*! \brief 1D.0005.6 ROS TC Present
                        AQ_GbeStandardDevicesInPackage_EUR.u0.bits_0.tcPresent

                        Default = 0x0

                        1 = TC is present in package
                        0 = TC is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no TC functionality in the PHY.  */
      unsigned int   tcPresent : 1;    /* 1D.0005.6  ROS      Default = 0x0 */
                     /* 1 = TC is present in package
                        0 = TC is not present in package  */
                    /*! \brief 1D.0005.5 ROS DTE XS Present
                        AQ_GbeStandardDevicesInPackage_EUR.u0.bits_0.dteXsPresent

                        Default = 0x0

                        1 = DTE XS is present in package
                        0 = DTE XS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no MAC XAUI interface in the PHY.  */
      unsigned int   dteXsPresent : 1;    /* 1D.0005.5  ROS      Default = 0x0 */
                     /* 1 = DTE XS is present in package
                        0 = DTE XS is not present in package  */
                    /*! \brief 1D.0005.4 ROS Control Present
                        AQ_GbeStandardDevicesInPackage_EUR.u0.bits_0.controlPresent

                        Default = 0x1

                        1 = Control is present in package
                        0 = Control is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is a PHY XAUI interface in the PHY.  */
      unsigned int   controlPresent : 1;    /* 1D.0005.4  ROS      Default = 0x1 */
                     /* 1 = Control is present in package
                        0 = Control is not present in package  */
                    /*! \brief 1D.0005.3 ROS PCS Present
                        AQ_GbeStandardDevicesInPackage_EUR.u0.bits_0.pcsPresent

                        Default = 0x1

                        1 = PCS is present in package
                        0 = PCS is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as there is PCS functionality in the PHY.  */
      unsigned int   pcsPresent : 1;    /* 1D.0005.3  ROS      Default = 0x1 */
                     /* 1 = PCS is present in package
                        0 = PCS is not present in package  */
                    /*! \brief 1D.0005.2 ROS WIS Present
                        AQ_GbeStandardDevicesInPackage_EUR.u0.bits_0.wisPresent

                        Default = 0x0

                        1 = WIS is present in package
                        0 = WIS is not present in package

                 <B>Notes:</B>
                        This is always set to 0, as there is no WIS functionality in the PHY.  */
      unsigned int   wisPresent : 1;    /* 1D.0005.2  ROS      Default = 0x0 */
                     /* 1 = WIS is present in package
                        0 = WIS is not present in package  */
                    /*! \brief 1D.0005.1 ROS PMA Present
                        AQ_GbeStandardDevicesInPackage_EUR.u0.bits_0.pmaPresent

                        Default = 0x1

                        1 = PMA is present in package
                        0 = PMA is not present 

                 <B>Notes:</B>
                        This is always set to 1 as there is PMA functionality in the PHY.  */
      unsigned int   pmaPresent : 1;    /* 1D.0005.1  ROS      Default = 0x1 */
                     /* 1 = PMA is present in package
                        0 = PMA is not present   */
                    /*! \brief 1D.0005.0 ROS Clause 22 Registers Present
                        AQ_GbeStandardDevicesInPackage_EUR.u0.bits_0.clause_22RegistersPresent

                        Default = 0x0

                        1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package

                 <B>Notes:</B>
                        This is always set to 0 in the PHY, as there are no Clause 22 registers in the device.  */
      unsigned int   clause_22RegistersPresent : 1;    /* 1D.0005.0  ROS      Default = 0x0 */
                     /* 1 = Clause 22 registers are present in package
                        0 = Clause 22 registers are not present in package  */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbeStandardDevicesInPackage_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE Standard Vendor Devices in Package: 1D.0006 */
/*                  GbE Standard Vendor Devices in Package: 1D.0006 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE Standard Vendor Devices in Package */
  union
  {
    struct
    {
                    /*! \brief 1D.0006.F ROS Vendor Specific Device #2 Present
                        AQ_GbeStandardVendorDevicesInPackage_EUR.u0.bits_0.vendorSpecificDevice_2Present

                        Default = 0x1

                        1 = Device #2 is present in package
                        0 = Device #2 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the DSP PMA registers.  */
      unsigned int   vendorSpecificDevice_2Present : 1;    /* 1D.0006.F  ROS      Default = 0x1 */
                     /* 1 = Device #2 is present in package
                        0 = Device #2 is not present in package  */
                    /*! \brief 1D.0006.E ROS Vendor Specific Device #1 Present
                        AQ_GbeStandardVendorDevicesInPackage_EUR.u0.bits_0.vendorSpecificDevice_1Present

                        Default = 0x1

                        1 = Device #1 is present in package
                        0 = Device #1 is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the global control registers.  */
      unsigned int   vendorSpecificDevice_1Present : 1;    /* 1D.0006.E  ROS      Default = 0x1 */
                     /* 1 = Device #1 is present in package
                        0 = Device #1 is not present in package  */
                    /*! \brief 1D.0006.D ROS Clause 22 Extension Present
                        AQ_GbeStandardVendorDevicesInPackage_EUR.u0.bits_0.clause_22ExtensionPresent

                        Default = 0x1

                        1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package

                 <B>Notes:</B>
                        This is always set to 1 as the PHY utilizes this device for the global control registers.  */
      unsigned int   clause_22ExtensionPresent : 1;    /* 1D.0006.D  ROS      Default = 0x1 */
                     /* 1 = Clause 22 Extension is present in package
                        0 = Clause 22 Extension is not present in package  */
      unsigned int   reserved0 : 13;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbeStandardVendorDevicesInPackage_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE Standard Status 2: 1D.0008 */
/*                  GbE Standard Status 2: 1D.0008 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE Standard Status 2 */
  union
  {
    struct
    {
                    /*! \brief 1D.0008.F:E ROS Device Present [1:0]
                        AQ_GbeStandardStatus_2_EUR.u0.bits_0.devicePresent

                        Default = 0x2

                        [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address

                 <B>Notes:</B>
                        This field is always set to 2, as the Control is present in the PHY.  */
      unsigned int   devicePresent : 2;    /* 1D.0008.F:E  ROS      Default = 0x2 */
                     /* [F:E]
                        0x3 = No device at this address
                        0x2 = Device present at this address
                        0x1 = No device at this address
                        0x0 = No device at this address  */
      unsigned int   reserved0 : 14;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbeStandardStatus_2_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE Standard Package Identifier: 1D.000E */
/*                  GbE Standard Package Identifier: 1D.000E */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 1D.000E.F:0 RO Package ID MSW [1F:10]
                        AQ_GbeStandardPackageIdentifier_EUR.u0.bits_0.packageIdMSW

                        

                        Bits 31- 16 of Package ID
  */
      unsigned int   packageIdMSW : 16;    /* 1D.000E.F:0  RO       */
                     /* Bits 31- 16 of Package ID  */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE Standard Package Identifier */
  union
  {
    struct
    {
                    /*! \brief 1D.000F.F:0 RO Package ID LSW [F:0]
                        AQ_GbeStandardPackageIdentifier_EUR.u1.bits_1.packageIdLSW

                        

                        Bits 15 - 0 of Package ID
  */
      unsigned int   packageIdLSW : 16;    /* 1D.000F.F:0  RO       */
                     /* Bits 15 - 0 of Package ID  */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_GbeStandardPackageIdentifier_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII Test Control: 1D.C282 */
/*                  GbE PHY SGMII Test Control: 1D.C282 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII Test Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbePhySgmiiTestControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY WoL Control: 1D.C300 */
/*                  GbE PHY WoL Control: 1D.C300 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY WoL Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE PHY WoL Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of GbE PHY WoL Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of GbE PHY WoL Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of GbE PHY WoL Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of GbE PHY WoL Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C306.F:0 R/W Wake Up Frame Mask 0 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u6.bits_6.wakeUpFrameMask_0Word_0

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 0 bits 15:0
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 0 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_0Word_0 : 16;    /* 1D.C306.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 0 bits 15:0
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C307.F:0 R/W Wake Up Frame Mask 0 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u7.bits_7.wakeUpFrameMask_0Word_1

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 0 bits 31:16
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 0 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_0Word_1 : 16;    /* 1D.C307.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 0 bits 31:16
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C308.F:0 R/W Wake Up Frame Mask 0 Word 2 [F:0]
                        AQ_GbePhyWolControl_EUR.u8.bits_8.wakeUpFrameMask_0Word_2

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 0 bits 47:32
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 0 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_0Word_2 : 16;    /* 1D.C308.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 0 bits 47:32
                          */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C309.F:0 R/W Wake Up Frame Mask 0 Word 3 [F:0]
                        AQ_GbePhyWolControl_EUR.u9.bits_9.wakeUpFrameMask_0Word_3

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 0 bits 63:48
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 0 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_0Word_3 : 16;    /* 1D.C309.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 0 bits 63:48
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C30A.F:0 R/W Wake Up Frame Mask 0 Word 4 [F:0]
                        AQ_GbePhyWolControl_EUR.u10.bits_10.wakeUpFrameMask_0Word_4

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 0 bits 79:64
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 0 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_0Word_4 : 16;    /* 1D.C30A.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 0 bits 79:64
                          */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C30B.F:0 R/W Wake Up Frame Mask 0 Word 5 [F:0]
                        AQ_GbePhyWolControl_EUR.u11.bits_11.wakeUpFrameMask_0Word_5

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 0 bits 95:80
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 0 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_0Word_5 : 16;    /* 1D.C30B.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 0 bits 95:80
                          */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C30C.F:0 R/W Wake Up Frame Mask 0 Word 6 [F:0]
                        AQ_GbePhyWolControl_EUR.u12.bits_12.wakeUpFrameMask_0Word_6

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 0 bits 111:96
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 0 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_0Word_6 : 16;    /* 1D.C30C.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 0 bits 111:96
                          */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C30D.F:0 R/W Wake Up Frame Mask 0 Word 7 [F:0]
                        AQ_GbePhyWolControl_EUR.u13.bits_13.wakeUpFrameMask_0Word_7

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 0 bits 127:112
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 0 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_0Word_7 : 16;    /* 1D.C30D.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 0 bits 127:112
                          */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C30E.F:0 R/W Wake Up Frame CRC 0 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u14.bits_14.wakeUpFrameCrc_0Word_0

                        Default = 0x0000

                        Wake Up Frame CRC 0 bits 15:0
                        
  */
      unsigned int   wakeUpFrameCrc_0Word_0 : 16;    /* 1D.C30E.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 0 bits 15:0
                          */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C30F.F:0 R/W Wake Up Frame CRC 0 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u15.bits_15.wakeUpFrameCrc_0Word_1

                        Default = 0x0000

                        Wake Up Frame CRC 0 bits 31:16
                        
  */
      unsigned int   wakeUpFrameCrc_0Word_1 : 16;    /* 1D.C30F.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 0 bits 31:16
                          */
    } bits_15;
    uint16_t word_15;
  } u15;
  /*! \brief Union for bit and word level access of word 16 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C310.F:0 R/W Wake Up Frame Mask 1 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u16.bits_16.wakeUpFrameMask_1Word_0

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 1 bits 15:0
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 1 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_1Word_0 : 16;    /* 1D.C310.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 1 bits 15:0
                          */
    } bits_16;
    uint16_t word_16;
  } u16;
  /*! \brief Union for bit and word level access of word 17 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C311.F:0 R/W Wake Up Frame Mask 1 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u17.bits_17.wakeUpFrameMask_1Word_1

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 1 bits 31:16
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 1 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_1Word_1 : 16;    /* 1D.C311.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 1 bits 31:16
                          */
    } bits_17;
    uint16_t word_17;
  } u17;
  /*! \brief Union for bit and word level access of word 18 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C312.F:0 R/W Wake Up Frame Mask 1 Word 2 [F:0]
                        AQ_GbePhyWolControl_EUR.u18.bits_18.wakeUpFrameMask_1Word_2

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 1 bits 47:32
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 1 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_1Word_2 : 16;    /* 1D.C312.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 1 bits 47:32
                          */
    } bits_18;
    uint16_t word_18;
  } u18;
  /*! \brief Union for bit and word level access of word 19 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C313.F:0 R/W Wake Up Frame Mask 1 Word 3 [F:0]
                        AQ_GbePhyWolControl_EUR.u19.bits_19.wakeUpFrameMask_1Word_3

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 1 bits 63:48
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 1 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_1Word_3 : 16;    /* 1D.C313.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 1 bits 63:48
                          */
    } bits_19;
    uint16_t word_19;
  } u19;
  /*! \brief Union for bit and word level access of word 20 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C314.F:0 R/W Wake Up Frame Mask 1 Word 4 [F:0]
                        AQ_GbePhyWolControl_EUR.u20.bits_20.wakeUpFrameMask_1Word_4

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 1 bits 79:64
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 1 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_1Word_4 : 16;    /* 1D.C314.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 1 bits 79:64
                          */
    } bits_20;
    uint16_t word_20;
  } u20;
  /*! \brief Union for bit and word level access of word 21 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C315.F:0 R/W Wake Up Frame Mask 1 Word 5 [F:0]
                        AQ_GbePhyWolControl_EUR.u21.bits_21.wakeUpFrameMask_1Word_5

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 1 bits 95:80
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 1 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_1Word_5 : 16;    /* 1D.C315.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 1 bits 95:80
                          */
    } bits_21;
    uint16_t word_21;
  } u21;
  /*! \brief Union for bit and word level access of word 22 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C316.F:0 R/W Wake Up Frame Mask 1 Word 6 [F:0]
                        AQ_GbePhyWolControl_EUR.u22.bits_22.wakeUpFrameMask_1Word_6

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 1 bits 111:96
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 1 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_1Word_6 : 16;    /* 1D.C316.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 1 bits 111:96
                          */
    } bits_22;
    uint16_t word_22;
  } u22;
  /*! \brief Union for bit and word level access of word 23 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C317.F:0 R/W Wake Up Frame Mask 1 Word 7 [F:0]
                        AQ_GbePhyWolControl_EUR.u23.bits_23.wakeUpFrameMask_1Word_7

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 1 bits 127:112
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 1 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_1Word_7 : 16;    /* 1D.C317.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 1 bits 127:112
                          */
    } bits_23;
    uint16_t word_23;
  } u23;
  /*! \brief Union for bit and word level access of word 24 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C318.F:0 R/W Wake Up Frame CRC 1 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u24.bits_24.wakeUpFrameCrc_1Word_0

                        Default = 0x0000

                        Wake Up Frame CRC 1 bits 15:0
                        
  */
      unsigned int   wakeUpFrameCrc_1Word_0 : 16;    /* 1D.C318.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 1 bits 15:0
                          */
    } bits_24;
    uint16_t word_24;
  } u24;
  /*! \brief Union for bit and word level access of word 25 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C319.F:0 R/W Wake Up Frame CRC 1 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u25.bits_25.wakeUpFrameCrc_1Word_1

                        Default = 0x0000

                        Wake Up Frame CRC 1 bits 31:16
                        
  */
      unsigned int   wakeUpFrameCrc_1Word_1 : 16;    /* 1D.C319.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 1 bits 31:16
                          */
    } bits_25;
    uint16_t word_25;
  } u25;
  /*! \brief Union for bit and word level access of word 26 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C31A.F:0 R/W Wake Up Frame Mask 2 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u26.bits_26.wakeUpFrameMask_2Word_0

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 2 bits 15:0
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 2 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_2Word_0 : 16;    /* 1D.C31A.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 2 bits 15:0
                          */
    } bits_26;
    uint16_t word_26;
  } u26;
  /*! \brief Union for bit and word level access of word 27 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C31B.F:0 R/W Wake Up Frame Mask 2 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u27.bits_27.wakeUpFrameMask_2Word_1

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 2 bits 31:16
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 2 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_2Word_1 : 16;    /* 1D.C31B.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 2 bits 31:16
                          */
    } bits_27;
    uint16_t word_27;
  } u27;
  /*! \brief Union for bit and word level access of word 28 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C31C.F:0 R/W Wake Up Frame Mask 2 Word 2 [F:0]
                        AQ_GbePhyWolControl_EUR.u28.bits_28.wakeUpFrameMask_2Word_2

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 2 bits 47:32
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 2 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_2Word_2 : 16;    /* 1D.C31C.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 2 bits 47:32
                          */
    } bits_28;
    uint16_t word_28;
  } u28;
  /*! \brief Union for bit and word level access of word 29 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C31D.F:0 R/W Wake Up Frame Mask 2 Word 3 [F:0]
                        AQ_GbePhyWolControl_EUR.u29.bits_29.wakeUpFrameMask_2Word_3

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 2 bits 63:48
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 2 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_2Word_3 : 16;    /* 1D.C31D.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 2 bits 63:48
                          */
    } bits_29;
    uint16_t word_29;
  } u29;
  /*! \brief Union for bit and word level access of word 30 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C31E.F:0 R/W Wake Up Frame Mask 2 Word 4 [F:0]
                        AQ_GbePhyWolControl_EUR.u30.bits_30.wakeUpFrameMask_2Word_4

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 2 bits 79:64
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 2 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_2Word_4 : 16;    /* 1D.C31E.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 2 bits 79:64
                          */
    } bits_30;
    uint16_t word_30;
  } u30;
  /*! \brief Union for bit and word level access of word 31 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C31F.F:0 R/W Wake Up Frame Mask 2 Word 5 [F:0]
                        AQ_GbePhyWolControl_EUR.u31.bits_31.wakeUpFrameMask_2Word_5

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 2 bits 95:80
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 2 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_2Word_5 : 16;    /* 1D.C31F.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 2 bits 95:80
                          */
    } bits_31;
    uint16_t word_31;
  } u31;
  /*! \brief Union for bit and word level access of word 32 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C320.F:0 R/W Wake Up Frame Mask 2 Word 6 [F:0]
                        AQ_GbePhyWolControl_EUR.u32.bits_32.wakeUpFrameMask_2Word_6

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 2 bits 111:96
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 2 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_2Word_6 : 16;    /* 1D.C320.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 2 bits 111:96
                          */
    } bits_32;
    uint16_t word_32;
  } u32;
  /*! \brief Union for bit and word level access of word 33 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C321.F:0 R/W Wake Up Frame Mask 2 Word 7 [F:0]
                        AQ_GbePhyWolControl_EUR.u33.bits_33.wakeUpFrameMask_2Word_7

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 2 bits 127:112
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 2 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_2Word_7 : 16;    /* 1D.C321.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 2 bits 127:112
                          */
    } bits_33;
    uint16_t word_33;
  } u33;
  /*! \brief Union for bit and word level access of word 34 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C322.F:0 R/W Wake Up Frame CRC 2 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u34.bits_34.wakeUpFrameCrc_2Word_0

                        Default = 0x0000

                        Wake Up Frame CRC 2 bits 15:0
                        
  */
      unsigned int   wakeUpFrameCrc_2Word_0 : 16;    /* 1D.C322.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 2 bits 15:0
                          */
    } bits_34;
    uint16_t word_34;
  } u34;
  /*! \brief Union for bit and word level access of word 35 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C323.F:0 R/W Wake Up Frame CRC 2 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u35.bits_35.wakeUpFrameCrc_2Word_1

                        Default = 0x0000

                        Wake Up Frame CRC 2 bits 31:16
                        
  */
      unsigned int   wakeUpFrameCrc_2Word_1 : 16;    /* 1D.C323.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 2 bits 31:16
                          */
    } bits_35;
    uint16_t word_35;
  } u35;
  /*! \brief Union for bit and word level access of word 36 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C324.F:0 R/W Wake Up Frame Mask 3 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u36.bits_36.wakeUpFrameMask_3Word_0

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 3 bits 15:0
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 3 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_3Word_0 : 16;    /* 1D.C324.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 3 bits 15:0
                          */
    } bits_36;
    uint16_t word_36;
  } u36;
  /*! \brief Union for bit and word level access of word 37 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C325.F:0 R/W Wake Up Frame Mask 3 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u37.bits_37.wakeUpFrameMask_3Word_1

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 3 bits 31:16
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 3 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_3Word_1 : 16;    /* 1D.C325.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 3 bits 31:16
                          */
    } bits_37;
    uint16_t word_37;
  } u37;
  /*! \brief Union for bit and word level access of word 38 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C326.F:0 R/W Wake Up Frame Mask 3 Word 2 [F:0]
                        AQ_GbePhyWolControl_EUR.u38.bits_38.wakeUpFrameMask_3Word_2

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 3 bits 47:32
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 3 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_3Word_2 : 16;    /* 1D.C326.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 3 bits 47:32
                          */
    } bits_38;
    uint16_t word_38;
  } u38;
  /*! \brief Union for bit and word level access of word 39 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C327.F:0 R/W Wake Up Frame Mask 3 Word 3 [F:0]
                        AQ_GbePhyWolControl_EUR.u39.bits_39.wakeUpFrameMask_3Word_3

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 3 bits 63:48
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 3 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_3Word_3 : 16;    /* 1D.C327.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 3 bits 63:48
                          */
    } bits_39;
    uint16_t word_39;
  } u39;
  /*! \brief Union for bit and word level access of word 40 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C328.F:0 R/W Wake Up Frame Mask 3 Word 4 [F:0]
                        AQ_GbePhyWolControl_EUR.u40.bits_40.wakeUpFrameMask_3Word_4

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 3 bits 79:64
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 3 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_3Word_4 : 16;    /* 1D.C328.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 3 bits 79:64
                          */
    } bits_40;
    uint16_t word_40;
  } u40;
  /*! \brief Union for bit and word level access of word 41 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C329.F:0 R/W Wake Up Frame Mask 3 Word 5 [F:0]
                        AQ_GbePhyWolControl_EUR.u41.bits_41.wakeUpFrameMask_3Word_5

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 3 bits 95:80
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 3 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_3Word_5 : 16;    /* 1D.C329.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 3 bits 95:80
                          */
    } bits_41;
    uint16_t word_41;
  } u41;
  /*! \brief Union for bit and word level access of word 42 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C32A.F:0 R/W Wake Up Frame Mask 3 Word 6 [F:0]
                        AQ_GbePhyWolControl_EUR.u42.bits_42.wakeUpFrameMask_3Word_6

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 3 bits 111:96
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 3 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_3Word_6 : 16;    /* 1D.C32A.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 3 bits 111:96
                          */
    } bits_42;
    uint16_t word_42;
  } u42;
  /*! \brief Union for bit and word level access of word 43 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C32B.F:0 R/W Wake Up Frame Mask 3 Word 7 [F:0]
                        AQ_GbePhyWolControl_EUR.u43.bits_43.wakeUpFrameMask_3Word_7

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 3 bits 127:112
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 3 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_3Word_7 : 16;    /* 1D.C32B.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 3 bits 127:112
                          */
    } bits_43;
    uint16_t word_43;
  } u43;
  /*! \brief Union for bit and word level access of word 44 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C32C.F:0 R/W Wake Up Frame CRC 3 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u44.bits_44.wakeUpFrameCrc_3Word_0

                        Default = 0x0000

                        Wake Up Frame CRC 3 bits 15:0
                        
  */
      unsigned int   wakeUpFrameCrc_3Word_0 : 16;    /* 1D.C32C.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 3 bits 15:0
                          */
    } bits_44;
    uint16_t word_44;
  } u44;
  /*! \brief Union for bit and word level access of word 45 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C32D.F:0 R/W Wake Up Frame CRC 3 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u45.bits_45.wakeUpFrameCrc_3Word_1

                        Default = 0x0000

                        Wake Up Frame CRC 3 bits 31:16
                        
  */
      unsigned int   wakeUpFrameCrc_3Word_1 : 16;    /* 1D.C32D.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 3 bits 31:16
                          */
    } bits_45;
    uint16_t word_45;
  } u45;
  /*! \brief Union for bit and word level access of word 46 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C32E.F:0 R/W Wake Up Frame Mask 4 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u46.bits_46.wakeUpFrameMask_4Word_0

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 4 bits 15:0
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 4 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_4Word_0 : 16;    /* 1D.C32E.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 4 bits 15:0
                          */
    } bits_46;
    uint16_t word_46;
  } u46;
  /*! \brief Union for bit and word level access of word 47 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C32F.F:0 R/W Wake Up Frame Mask 4 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u47.bits_47.wakeUpFrameMask_4Word_1

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 4 bits 31:16
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 4 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_4Word_1 : 16;    /* 1D.C32F.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 4 bits 31:16
                          */
    } bits_47;
    uint16_t word_47;
  } u47;
  /*! \brief Union for bit and word level access of word 48 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C330.F:0 R/W Wake Up Frame Mask 4 Word 2 [F:0]
                        AQ_GbePhyWolControl_EUR.u48.bits_48.wakeUpFrameMask_4Word_2

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 4 bits 47:32
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 4 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_4Word_2 : 16;    /* 1D.C330.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 4 bits 47:32
                          */
    } bits_48;
    uint16_t word_48;
  } u48;
  /*! \brief Union for bit and word level access of word 49 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C331.F:0 R/W Wake Up Frame Mask 4 Word 3 [F:0]
                        AQ_GbePhyWolControl_EUR.u49.bits_49.wakeUpFrameMask_4Word_3

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 4 bits 63:48
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 4 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_4Word_3 : 16;    /* 1D.C331.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 4 bits 63:48
                          */
    } bits_49;
    uint16_t word_49;
  } u49;
  /*! \brief Union for bit and word level access of word 50 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C332.F:0 R/W Wake Up Frame Mask 4 Word 4 [F:0]
                        AQ_GbePhyWolControl_EUR.u50.bits_50.wakeUpFrameMask_4Word_4

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 4 bits 79:64
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 4 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_4Word_4 : 16;    /* 1D.C332.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 4 bits 79:64
                          */
    } bits_50;
    uint16_t word_50;
  } u50;
  /*! \brief Union for bit and word level access of word 51 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C333.F:0 R/W Wake Up Frame Mask 4 Word 5 [F:0]
                        AQ_GbePhyWolControl_EUR.u51.bits_51.wakeUpFrameMask_4Word_5

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 4 bits 95:80
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 4 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_4Word_5 : 16;    /* 1D.C333.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 4 bits 95:80
                          */
    } bits_51;
    uint16_t word_51;
  } u51;
  /*! \brief Union for bit and word level access of word 52 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C334.F:0 R/W Wake Up Frame Mask 4 Word 6 [F:0]
                        AQ_GbePhyWolControl_EUR.u52.bits_52.wakeUpFrameMask_4Word_6

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 4 bits 111:96
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 4 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_4Word_6 : 16;    /* 1D.C334.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 4 bits 111:96
                          */
    } bits_52;
    uint16_t word_52;
  } u52;
  /*! \brief Union for bit and word level access of word 53 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C335.F:0 R/W Wake Up Frame Mask 4 Word 7 [F:0]
                        AQ_GbePhyWolControl_EUR.u53.bits_53.wakeUpFrameMask_4Word_7

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 4 bits 127:112
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 4 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_4Word_7 : 16;    /* 1D.C335.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 4 bits 127:112
                          */
    } bits_53;
    uint16_t word_53;
  } u53;
  /*! \brief Union for bit and word level access of word 54 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C336.F:0 R/W Wake Up Frame CRC 4 Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u54.bits_54.wakeUpFrameCrc_4Word_0

                        Default = 0x0000

                        Wake Up Frame CRC 4 bits 15:0
                        
  */
      unsigned int   wakeUpFrameCrc_4Word_0 : 16;    /* 1D.C336.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 4 bits 15:0
                          */
    } bits_54;
    uint16_t word_54;
  } u54;
  /*! \brief Union for bit and word level access of word 55 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C337.F:0 R/W Wake Up Frame CRC 4 Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u55.bits_55.wakeUpFrameCrc_4Word_1

                        Default = 0x0000

                        Wake Up Frame CRC 4 bits 31:16
                        
  */
      unsigned int   wakeUpFrameCrc_4Word_1 : 16;    /* 1D.C337.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 4 bits 31:16
                          */
    } bits_55;
    uint16_t word_55;
  } u55;
  /*! \brief Union for bit and word level access of word 56 of GbE PHY WoL Control */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_56;
    uint16_t word_56;
  } u56;
  /*! \brief Union for bit and word level access of word 57 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C339.F:0 R/W Magic Packet Frame Pattern Word 0 [F:0]
                        AQ_GbePhyWolControl_EUR.u57.bits_57.magicPacketFramePatternWord_0

                        Default = 0x0000

                        Magic Packet Frame Pattern bits 15:0
                        

                 <B>Notes:</B>
                        Magic packet frame pattern (MAC address)  */
      unsigned int   magicPacketFramePatternWord_0 : 16;    /* 1D.C339.F:0  R/W      Default = 0x0000 */
                     /* Magic Packet Frame Pattern bits 15:0
                          */
    } bits_57;
    uint16_t word_57;
  } u57;
  /*! \brief Union for bit and word level access of word 58 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C33A.F:0 R/W Magic Packet Frame Pattern Word 1 [F:0]
                        AQ_GbePhyWolControl_EUR.u58.bits_58.magicPacketFramePatternWord_1

                        Default = 0x0000

                        Magic Packet Frame Pattern bits 31:16
                        

                 <B>Notes:</B>
                        Magic packet frame pattern (MAC address)  */
      unsigned int   magicPacketFramePatternWord_1 : 16;    /* 1D.C33A.F:0  R/W      Default = 0x0000 */
                     /* Magic Packet Frame Pattern bits 31:16
                          */
    } bits_58;
    uint16_t word_58;
  } u58;
  /*! \brief Union for bit and word level access of word 59 of GbE PHY WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C33B.F:0 R/W Magic Packet Frame Pattern Word 2 [F:0]
                        AQ_GbePhyWolControl_EUR.u59.bits_59.magicPacketFramePatternWord_2

                        Default = 0x0000

                        Magic Packet Frame Pattern bits 47:32
                        

                 <B>Notes:</B>
                        Magic packet frame pattern (MAC address)  */
      unsigned int   magicPacketFramePatternWord_2 : 16;    /* 1D.C33B.F:0  R/W      Default = 0x0000 */
                     /* Magic Packet Frame Pattern bits 47:32
                          */
    } bits_59;
    uint16_t word_59;
  } u59;
} AQ_GbePhyWolControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY Extended WoL Control: 1D.C420 */
/*                  GbE PHY Extended WoL Control: 1D.C420 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C420.F:0 R/W Wake Up Frame Mask 5 Word 0 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u0.bits_0.wakeUpFrameMask_5Word_0

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 5 bits 15:0
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 5 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_5Word_0 : 16;    /* 1D.C420.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 5 bits 15:0
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C421.F:0 R/W Wake Up Frame Mask 5 Word 1 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u1.bits_1.wakeUpFrameMask_5Word_1

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 55 bits 31:16
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 5 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_5Word_1 : 16;    /* 1D.C421.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 55 bits 31:16
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C422.F:0 R/W Wake Up Frame Mask 5 Word 2 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u2.bits_2.wakeUpFrameMask_5Word_2

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 5 bits 47:32
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 5 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_5Word_2 : 16;    /* 1D.C422.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 5 bits 47:32
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C423.F:0 R/W Wake Up Frame Mask 5 Word 3 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u3.bits_3.wakeUpFrameMask_5Word_3

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 5 bits 63:48
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 5 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_5Word_3 : 16;    /* 1D.C423.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 5 bits 63:48
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C424.F:0 R/W Wake Up Frame Mask 5 Word 4 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u4.bits_4.wakeUpFrameMask_5Word_4

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 5 bits 79:64
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 5 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_5Word_4 : 16;    /* 1D.C424.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 5 bits 79:64
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C425.F:0 R/W Wake Up Frame Mask 5 Word 5 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u5.bits_5.wakeUpFrameMask_5Word_5

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 5 bits 95:80
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 5 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_5Word_5 : 16;    /* 1D.C425.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 5 bits 95:80
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C426.F:0 R/W Wake Up Frame Mask 5 Word 6 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u6.bits_6.wakeUpFrameMask_5Word_6

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 5 bits 111:96
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 5 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_5Word_6 : 16;    /* 1D.C426.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 5 bits 111:96
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C427.F:0 R/W Wake Up Frame Mask 5 Word 7 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u7.bits_7.wakeUpFrameMask_5Word_7

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 5 bits 127:112
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 5 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_5Word_7 : 16;    /* 1D.C427.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 5 bits 127:112
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C428.F:0 R/W Wake Up Frame CRC 5 Word 0 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u8.bits_8.wakeUpFrameCrc_5Word_0

                        Default = 0x0000

                        Wake Up Frame CRC 5 bits 15:0
                        
  */
      unsigned int   wakeUpFrameCrc_5Word_0 : 16;    /* 1D.C428.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 5 bits 15:0
                          */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C429.F:0 R/W Wake Up Frame CRC 5 Word 1 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u9.bits_9.wakeUpFrameCrc_5Word_1

                        Default = 0x0000

                        Wake Up Frame CRC 5 bits 31:16
                        
  */
      unsigned int   wakeUpFrameCrc_5Word_1 : 16;    /* 1D.C429.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 5 bits 31:16
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
  /*! \brief Union for bit and word level access of word 10 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C42A.F:0 R/W Wake Up Frame Mask 6 Word 0 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u10.bits_10.wakeUpFrameMask_6Word_0

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 6 bits 15:0
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 6 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_6Word_0 : 16;    /* 1D.C42A.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 6 bits 15:0
                          */
    } bits_10;
    uint16_t word_10;
  } u10;
  /*! \brief Union for bit and word level access of word 11 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C42B.F:0 R/W Wake Up Frame Mask 6 Word 1 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u11.bits_11.wakeUpFrameMask_6Word_1

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 65 bits 31:16
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 6 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_6Word_1 : 16;    /* 1D.C42B.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 65 bits 31:16
                          */
    } bits_11;
    uint16_t word_11;
  } u11;
  /*! \brief Union for bit and word level access of word 12 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C42C.F:0 R/W Wake Up Frame Mask 6 Word 2 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u12.bits_12.wakeUpFrameMask_6Word_2

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 6 bits 47:32
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 6 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_6Word_2 : 16;    /* 1D.C42C.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 6 bits 47:32
                          */
    } bits_12;
    uint16_t word_12;
  } u12;
  /*! \brief Union for bit and word level access of word 13 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C42D.F:0 R/W Wake Up Frame Mask 6 Word 3 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u13.bits_13.wakeUpFrameMask_6Word_3

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 6 bits 63:48
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 6 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_6Word_3 : 16;    /* 1D.C42D.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 6 bits 63:48
                          */
    } bits_13;
    uint16_t word_13;
  } u13;
  /*! \brief Union for bit and word level access of word 14 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C42E.F:0 R/W Wake Up Frame Mask 6 Word 4 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u14.bits_14.wakeUpFrameMask_6Word_4

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 6 bits 79:64
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 6 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_6Word_4 : 16;    /* 1D.C42E.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 6 bits 79:64
                          */
    } bits_14;
    uint16_t word_14;
  } u14;
  /*! \brief Union for bit and word level access of word 15 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C42F.F:0 R/W Wake Up Frame Mask 6 Word 5 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u15.bits_15.wakeUpFrameMask_6Word_5

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 6 bits 95:80
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 6 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_6Word_5 : 16;    /* 1D.C42F.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 6 bits 95:80
                          */
    } bits_15;
    uint16_t word_15;
  } u15;
  /*! \brief Union for bit and word level access of word 16 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C430.F:0 R/W Wake Up Frame Mask 6 Word 6 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u16.bits_16.wakeUpFrameMask_6Word_6

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 6 bits 111:96
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 6 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_6Word_6 : 16;    /* 1D.C430.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 6 bits 111:96
                          */
    } bits_16;
    uint16_t word_16;
  } u16;
  /*! \brief Union for bit and word level access of word 17 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C431.F:0 R/W Wake Up Frame Mask 6 Word 7 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u17.bits_17.wakeUpFrameMask_6Word_7

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 6 bits 127:112
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 6 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_6Word_7 : 16;    /* 1D.C431.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 6 bits 127:112
                          */
    } bits_17;
    uint16_t word_17;
  } u17;
  /*! \brief Union for bit and word level access of word 18 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C432.F:0 R/W Wake Up Frame CRC 6 Word 0 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u18.bits_18.wakeUpFrameCrc_6Word_0

                        Default = 0x0000

                        Wake Up Frame CRC 6 bits 15:0
                        
  */
      unsigned int   wakeUpFrameCrc_6Word_0 : 16;    /* 1D.C432.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 6 bits 15:0
                          */
    } bits_18;
    uint16_t word_18;
  } u18;
  /*! \brief Union for bit and word level access of word 19 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C433.F:0 R/W Wake Up Frame CRC 6 Word 1 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u19.bits_19.wakeUpFrameCrc_6Word_1

                        Default = 0x0000

                        Wake Up Frame CRC 6 bits 31:16
                        
  */
      unsigned int   wakeUpFrameCrc_6Word_1 : 16;    /* 1D.C433.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 6 bits 31:16
                          */
    } bits_19;
    uint16_t word_19;
  } u19;
  /*! \brief Union for bit and word level access of word 20 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C434.F:0 R/W Wake Up Frame Mask 7 Word 0 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u20.bits_20.wakeUpFrameMask_7Word_0

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 7 bits 15:0
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 7 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_7Word_0 : 16;    /* 1D.C434.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 7 bits 15:0
                          */
    } bits_20;
    uint16_t word_20;
  } u20;
  /*! \brief Union for bit and word level access of word 21 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C435.F:0 R/W Wake Up Frame Mask 7 Word 1 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u21.bits_21.wakeUpFrameMask_7Word_1

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 75 bits 31:16
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 7 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_7Word_1 : 16;    /* 1D.C435.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 75 bits 31:16
                          */
    } bits_21;
    uint16_t word_21;
  } u21;
  /*! \brief Union for bit and word level access of word 22 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C436.F:0 R/W Wake Up Frame Mask 7 Word 2 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u22.bits_22.wakeUpFrameMask_7Word_2

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 7 bits 47:32
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 7 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_7Word_2 : 16;    /* 1D.C436.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 7 bits 47:32
                          */
    } bits_22;
    uint16_t word_22;
  } u22;
  /*! \brief Union for bit and word level access of word 23 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C437.F:0 R/W Wake Up Frame Mask 7 Word 3 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u23.bits_23.wakeUpFrameMask_7Word_3

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 7 bits 63:48
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 7 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_7Word_3 : 16;    /* 1D.C437.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 7 bits 63:48
                          */
    } bits_23;
    uint16_t word_23;
  } u23;
  /*! \brief Union for bit and word level access of word 24 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C438.F:0 R/W Wake Up Frame Mask 7 Word 4 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u24.bits_24.wakeUpFrameMask_7Word_4

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 7 bits 79:64
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 7 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_7Word_4 : 16;    /* 1D.C438.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 7 bits 79:64
                          */
    } bits_24;
    uint16_t word_24;
  } u24;
  /*! \brief Union for bit and word level access of word 25 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C439.F:0 R/W Wake Up Frame Mask 7 Word 5 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u25.bits_25.wakeUpFrameMask_7Word_5

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 7 bits 95:80
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 7 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_7Word_5 : 16;    /* 1D.C439.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 7 bits 95:80
                          */
    } bits_25;
    uint16_t word_25;
  } u25;
  /*! \brief Union for bit and word level access of word 26 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C43A.F:0 R/W Wake Up Frame Mask 7 Word 6 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u26.bits_26.wakeUpFrameMask_7Word_6

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 7 bits 111:96
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 7 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_7Word_6 : 16;    /* 1D.C43A.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 7 bits 111:96
                          */
    } bits_26;
    uint16_t word_26;
  } u26;
  /*! \brief Union for bit and word level access of word 27 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C43B.F:0 R/W Wake Up Frame Mask 7 Word 7 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u27.bits_27.wakeUpFrameMask_7Word_7

                        Default = 0x0000

                        Wake Up Frame Pattern Mask 7 bits 127:112
                        

                 <B>Notes:</B>
                        Wake-up Frame Pattern Mask 7 (0=disable, 1=enable, bit 0 for the first byte, default:all-zeroes)  */
      unsigned int   wakeUpFrameMask_7Word_7 : 16;    /* 1D.C43B.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame Pattern Mask 7 bits 127:112
                          */
    } bits_27;
    uint16_t word_27;
  } u27;
  /*! \brief Union for bit and word level access of word 28 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C43C.F:0 R/W Wake Up Frame CRC 7 Word 0 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u28.bits_28.wakeUpFrameCrc_7Word_0

                        Default = 0x0000

                        Wake Up Frame CRC 7 bits 15:0
                        
  */
      unsigned int   wakeUpFrameCrc_7Word_0 : 16;    /* 1D.C43C.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 7 bits 15:0
                          */
    } bits_28;
    uint16_t word_28;
  } u28;
  /*! \brief Union for bit and word level access of word 29 of GbE PHY Extended WoL Control */
  union
  {
    struct
    {
                    /*! \brief 1D.C43D.F:0 R/W Wake Up Frame CRC 7 Word 1 [F:0]
                        AQ_GbePhyExtendedWolControl_EUR.u29.bits_29.wakeUpFrameCrc_7Word_1

                        Default = 0x0000

                        Wake Up Frame CRC 7 bits 31:16
                        
  */
      unsigned int   wakeUpFrameCrc_7Word_1 : 16;    /* 1D.C43D.F:0  R/W      Default = 0x0000 */
                     /* Wake Up Frame CRC 7 bits 31:16
                          */
    } bits_29;
    uint16_t word_29;
  } u29;
} AQ_GbePhyExtendedWolControl_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE Reserved Provisioning: 1D.C500 */
/*                  GbE Reserved Provisioning: 1D.C500 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE Reserved Provisioning */
  union
  {
    struct
    {
                    /*! \brief 1D.C500.F R/WPD 100M System Loopback
                        AQ_GbeReservedProvisioning_EUR.u0.bits_0._100mSystemLoopback

                        Provisionable Default = 0x0

                        1 = Enable System Loopback
                        

                 <B>Notes:</B>
                        Setting this bit enables the 100M system loopback.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   _100mSystemLoopback : 1;    /* 1D.C500.F  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable System Loopback
                          */
                    /*! \brief 1D.C500.E R/WPD GbE System Loopback
                        AQ_GbeReservedProvisioning_EUR.u0.bits_0.gbeSystemLoopback

                        Provisionable Default = 0x0

                        1 = Enable System Loopback
                        

                 <B>Notes:</B>
                        Setting this bit enables the 1G system loopback.
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   gbeSystemLoopback : 1;    /* 1D.C500.E  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable System Loopback
                          */
                    /*! \brief 1D.C500.D:0 R/WPD Reserved Provisioning 1 [D:0]
                        AQ_GbeReservedProvisioning_EUR.u0.bits_0.reservedProvisioning_1

                        Provisionable Default = 0x0000

                        Reserved for future use
                        
  */
      unsigned int   reservedProvisioning_1 : 14;    /* 1D.C500.D:0  R/WPD      Provisionable Default = 0x0000 */
                     /* Reserved for future use
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE Reserved Provisioning */
  union
  {
    struct
    {
                    /*! \brief 1D.C501.F:D R/W Test Mode [2:0]
                        AQ_GbeReservedProvisioning_EUR.u1.bits_1.testMode

                        Default = 0x0

                        000 = Normal mode
                        001 = Test Mode 1 - Transmit waveform test
                        010 = Test Mode 2 - Master transmit jitter test
                        011 = Test Mode 3 - Slave transmit jitter test
                        100 = Test Mode 4 - Transmitter distortion test
                        101 -> 1111 = Reserved
                        

                 <B>Notes:</B>
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   testMode : 3;    /* 1D.C501.F:D  R/W      Default = 0x0 */
                     /* 000 = Normal mode
                        001 = Test Mode 1 - Transmit waveform test
                        010 = Test Mode 2 - Master transmit jitter test
                        011 = Test Mode 3 - Slave transmit jitter test
                        100 = Test Mode 4 - Transmitter distortion test
                        101 -> 1111 = Reserved
                          */
                    /*! \brief 1D.C501.C:2 R/WPD Reserved Provisioning 2 [A:0]
                        AQ_GbeReservedProvisioning_EUR.u1.bits_1.reservedProvisioning_2

                        Provisionable Default = 0x000

                        Reserved for future use
                        
                        
  */
      unsigned int   reservedProvisioning_2 : 11;    /* 1D.C501.C:2  R/WPD      Provisionable Default = 0x000 */
                     /* Reserved for future use
                        
                          */
                    /*! \brief 1D.C501.1:0 R/W 100BASE-TX Test Mode [1:0]
                        AQ_GbeReservedProvisioning_EUR.u1.bits_1._100base_txTestMode

                        Default = 0x0

                        00 = Normal mode
                        01 = 100BASE-TX IEEE Test Mode
                        10 = 100BASE-TX ANSI Jitter Test
                        11 = 100BASE-TX ANSI Droop Test
                        

                 <B>Notes:</B>
                        100BASE-TX IEEE Test Mode = MLT-3 Idle Sequence
                        ANSI Jitter Test = FDDI - Clause 9.1.3 Fig. 12
                        ANSI Droop Test = FDDI - Clause 9.1.8 Fig. 14
                        
                        NOTE!! This is a processor intensive operation. Completion of this operation can be monitored via 1E.C831.F  */
      unsigned int   _100base_txTestMode : 2;    /* 1D.C501.1:0  R/W      Default = 0x0 */
                     /* 00 = Normal mode
                        01 = 100BASE-TX IEEE Test Mode
                        10 = 100BASE-TX ANSI Jitter Test
                        11 = 100BASE-TX ANSI Droop Test
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
} AQ_GbeReservedProvisioning_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII1 Rx Status: 1D.D280 */
/*                  GbE PHY SGMII1 Rx Status: 1D.D280 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of GbE PHY SGMII1 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_8;
    uint16_t word_8;
  } u8;
} AQ_GbePhySgmii1RxStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII0 Rx Status: 1D.D290 */
/*                  GbE PHY SGMII0 Rx Status: 1D.D290 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 7;
                    /*! \brief 1D.D290.8 RO SGMII0 Rx Synchronization Status
                        AQ_GbePhySgmii0RxStatus_EUR.u0.bits_0.sgmii0RxSynchronizationStatus

                        

                        1 = SGMII0 Rx is Synchronized
                        
  */
      unsigned int   sgmii0RxSynchronizationStatus : 1;    /* 1D.D290.8  RO       */
                     /* 1 = SGMII0 Rx is Synchronized
                          */
                    /*! \brief 1D.D290.7 LH SGMII0 Rx Loopback Idle Insertion Detected
                        AQ_GbePhySgmii0RxStatus_EUR.u0.bits_0.sgmii0RxLoopbackIdleInsertionDetected

                        

                        1 = SGMII0 Rx Idle Insertion Detected
                        
  */
      unsigned int   sgmii0RxLoopbackIdleInsertionDetected : 1;    /* 1D.D290.7  LH       */
                     /* 1 = SGMII0 Rx Idle Insertion Detected
                          */
                    /*! \brief 1D.D290.6 LH SGMII0 Rx Loopback Idle Deletion Detected
                        AQ_GbePhySgmii0RxStatus_EUR.u0.bits_0.sgmii0RxLoopbackIdleDeletionDetected

                        

                        1 = SGMII0 Rx Idle Deletion Detected
                        
  */
      unsigned int   sgmii0RxLoopbackIdleDeletionDetected : 1;    /* 1D.D290.6  LH       */
                     /* 1 = SGMII0 Rx Idle Deletion Detected
                          */
                    /*! \brief 1D.D290.5 LH SGMII0 Rx Idle Insertion Detected
                        AQ_GbePhySgmii0RxStatus_EUR.u0.bits_0.sgmii0RxIdleInsertionDetected

                        

                        1 = SGMII0 Rx Idle Insertion Detected
                        
  */
      unsigned int   sgmii0RxIdleInsertionDetected : 1;    /* 1D.D290.5  LH       */
                     /* 1 = SGMII0 Rx Idle Insertion Detected
                          */
                    /*! \brief 1D.D290.4 LH SGMII0 Rx Idle Deletion Detected
                        AQ_GbePhySgmii0RxStatus_EUR.u0.bits_0.sgmii0RxIdleDeletionDetected

                        

                        1 = SGMII0 Rx Idle Deletion Detected
                        
  */
      unsigned int   sgmii0RxIdleDeletionDetected : 1;    /* 1D.D290.4  LH       */
                     /* 1 = SGMII0 Rx Idle Deletion Detected
                          */
      unsigned int   reserved1 : 2;
                    /*! \brief 1D.D290.1 LH SGMII0 Rx TX_ER Suppression
                        AQ_GbePhySgmii0RxStatus_EUR.u0.bits_0.sgmii0RxTxErSuppression

                        

                        1 = SGMII0 Rx TX_ER suppressed
                        

                 <B>Notes:</B>
                        Indicate TX_ER has been suppressed when TX_EN was not asserted  */
      unsigned int   sgmii0RxTxErSuppression : 1;    /* 1D.D290.1  LH       */
                     /* 1 = SGMII0 Rx TX_ER suppressed
                          */
                    /*! \brief 1D.D290.0 LH SGMII0 Rx Rx Link Activity
                        AQ_GbePhySgmii0RxStatus_EUR.u0.bits_0.sgmii0RxRxLinkActivity

                        

                        1 = SGMII0 Rx Rx Link Activity
                        

                 <B>Notes:</B>
                        SGMII Start Character K27_7 detected  */
      unsigned int   sgmii0RxRxLinkActivity : 1;    /* 1D.D290.0  LH       */
                     /* 1 = SGMII0 Rx Rx Link Activity
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
                    /*! \brief 1D.D292.F:0 SCTL SGMII0 Rx Frame Counter LSW [F:0]
                        AQ_GbePhySgmii0RxStatus_EUR.u2.bits_2.sgmii0RxFrameCounterLSW

                        Default = 0x0000

                        SGMII0 Rx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 100M / GbE Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   sgmii0RxFrameCounterLSW : 16;    /* 1D.D292.F:0  SCTL      Default = 0x0000 */
                     /* SGMII0 Rx Good Frame Counter
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 1D.D293.9:0 SCTM SGMII0 Rx Frame Counter MSW [9:0]
                        AQ_GbePhySgmii0RxStatus_EUR.u3.bits_3.sgmii0RxFrameCounterMSW

                        Default = 0x000

                        SGMII0 Rx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 100M / GbE Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   sgmii0RxFrameCounterMSW : 10;    /* 1D.D293.9:0  SCTM      Default = 0x000 */
                     /* SGMII0 Rx Good Frame Counter
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
                    /*! \brief 1D.D294.F:0 SCTL SGMII0 Rx Frame Error Counter LSW [F:0]
                        AQ_GbePhySgmii0RxStatus_EUR.u4.bits_4.sgmii0RxFrameErrorCounterLSW

                        Default = 0x0000

                        SGMII0 Rx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 100M / GbE Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   sgmii0RxFrameErrorCounterLSW : 16;    /* 1D.D294.F:0  SCTL      Default = 0x0000 */
                     /* SGMII0 Rx Bad Frame Counter
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 1D.D295.9:0 SCTM SGMII0 Rx Frame Error Counter MSW [9:0]
                        AQ_GbePhySgmii0RxStatus_EUR.u5.bits_5.sgmii0RxFrameErrorCounterMSW

                        Default = 0x000

                        SGMII0 Rx Bad Frame Counter
                        

                 <B>Notes:</B>
                        This counts 100M / GbE Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   sgmii0RxFrameErrorCounterMSW : 10;    /* 1D.D295.9:0  SCTM      Default = 0x000 */
                     /* SGMII0 Rx Bad Frame Counter
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 15;
                    /*! \brief 1D.D296.0 LH SGMII0 Rx Comma Detect
                        AQ_GbePhySgmii0RxStatus_EUR.u6.bits_6.sgmii0RxCommaDetect

                        

                        1 = SGMII0 Rx Comma Detected
                        

                 <B>Notes:</B>
                        Indicates when Rx has detected a comma character  */
      unsigned int   sgmii0RxCommaDetect : 1;    /* 1D.D296.0  LH       */
                     /* 1 = SGMII0 Rx Comma Detected
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 1D.D297.7:0 SCT SGMII0 Rx False Carrier Counter [7:0]
                        AQ_GbePhySgmii0RxStatus_EUR.u7.bits_7.sgmii0RxFalseCarrierCounter

                        Default = 0x00

                        SGMII0 Rx False Carrier Counter
                        

                 <B>Notes:</B>
                        False carrier events on XFI0 SGMII interface.  */
      unsigned int   sgmii0RxFalseCarrierCounter : 8;    /* 1D.D297.7:0  SCT      Default = 0x00 */
                     /* SGMII0 Rx False Carrier Counter
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of GbE PHY SGMII0 Rx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 4;
                    /*! \brief 1D.D298.B:8 RO SGMII0 Rx EEE Rx LPI State Machine [3:0]
                        AQ_GbePhySgmii0RxStatus_EUR.u8.bits_8.sgmii0RxEeeRxLpiStateMachine

                        

                        SGMII0 Rx EEE Rx LPI state machine
                        

                 <B>Notes:</B>
                        Rx LPI state machine
                          */
      unsigned int   sgmii0RxEeeRxLpiStateMachine : 4;    /* 1D.D298.B:8  RO       */
                     /* SGMII0 Rx EEE Rx LPI state machine
                          */
      unsigned int   reserved1 : 3;
                    /*! \brief 1D.D298.4 LH SGMII0 Rx EEE Rx LPI Ordered Set Dectected
                        AQ_GbePhySgmii0RxStatus_EUR.u8.bits_8.sgmii0RxEeeRxLpiOrderedSetDectected

                        

                        1 = SGMII0 Rx LPI ordered set detected
                        

                 <B>Notes:</B>
                        Indicate LPI ordered_set is detected  */
      unsigned int   sgmii0RxEeeRxLpiOrderedSetDectected : 1;    /* 1D.D298.4  LH       */
                     /* 1 = SGMII0 Rx LPI ordered set detected
                          */
                    /*! \brief 1D.D298.3 LH SGMII0 Rx EEE Rx LPI Wake Timer Fault Error
                        AQ_GbePhySgmii0RxStatus_EUR.u8.bits_8.sgmii0RxEeeRxLpiWakeTimerFaultError

                        

                        1 = SGMII0 Rx Rx LPI detected wake timer fault
                        

                 <B>Notes:</B>
                        Indicate Rx LPI detected wake timer fault  */
      unsigned int   sgmii0RxEeeRxLpiWakeTimerFaultError : 1;    /* 1D.D298.3  LH       */
                     /* 1 = SGMII0 Rx Rx LPI detected wake timer fault
                          */
                    /*! \brief 1D.D298.2 RO SGMII0 Rx EEE Rx LPI Wake Done State
                        AQ_GbePhySgmii0RxStatus_EUR.u8.bits_8.sgmii0RxEeeRxLpiWakeDoneState

                        

                        1 = SGMII0 Rx Rx LPI is in wake done state
                        

                 <B>Notes:</B>
                        Indicate Rx LPI is in wake done state  */
      unsigned int   sgmii0RxEeeRxLpiWakeDoneState : 1;    /* 1D.D298.2  RO       */
                     /* 1 = SGMII0 Rx Rx LPI is in wake done state
                          */
                    /*! \brief 1D.D298.1 RO SGMII0 Rx EEE Rx LPI Quiet State
                        AQ_GbePhySgmii0RxStatus_EUR.u8.bits_8.sgmii0RxEeeRxLpiQuietState

                        

                        1 = SGMII0 Rx Rx LPI is in quiet state
                        

                 <B>Notes:</B>
                        Indicate Rx LPI is in quiet state  */
      unsigned int   sgmii0RxEeeRxLpiQuietState : 1;    /* 1D.D298.1  RO       */
                     /* 1 = SGMII0 Rx Rx LPI is in quiet state
                          */
                    /*! \brief 1D.D298.0 RO SGMII0 Rx EEE Rx LPI Active State
                        AQ_GbePhySgmii0RxStatus_EUR.u8.bits_8.sgmii0RxEeeRxLpiActiveState

                        

                        1 = SGMII0 Rx Rx LPI is in active state
                        

                 <B>Notes:</B>
                        Indicate Rx LPI is in active state  */
      unsigned int   sgmii0RxEeeRxLpiActiveState : 1;    /* 1D.D298.0  RO       */
                     /* 1 = SGMII0 Rx Rx LPI is in active state
                          */
    } bits_8;
    uint16_t word_8;
  } u8;
} AQ_GbePhySgmii0RxStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII1 WoL Status: 1D.D302 */
/*                  GbE PHY SGMII1 WoL Status: 1D.D302 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII1 WoL Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbePhySgmii1WolStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII1 Tx Status: 1D.D303 */
/*                  GbE PHY SGMII1 Tx Status: 1D.D303 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of GbE PHY SGMII1 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_9;
    uint16_t word_9;
  } u9;
} AQ_GbePhySgmii1TxStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                SGMII0 WoL Status: 1D.D312 */
/*                  SGMII0 WoL Status: 1D.D312 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of SGMII0 WoL Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 13;
                    /*! \brief 1D.D312.2:0 RO SGMII0 Wake Up Frame Type [2:0]
                        AQ_Sgmii0WolStatus_EUR.u0.bits_0.sgmii0WakeUpFrameType

                        

                        SGMII0 Wake Up Frame Type
                        

                 <B>Notes:</B>
                        Wake-up Frame type detected (0 to 7: Wake-up Frame 0 to 7)  */
      unsigned int   sgmii0WakeUpFrameType : 3;    /* 1D.D312.2:0  RO       */
                     /* SGMII0 Wake Up Frame Type
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_Sgmii0WolStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII0 Tx Status: 1D.D313 */
/*                  GbE PHY SGMII0 Tx Status: 1D.D313 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
                    /*! \brief 1D.D313.F:0 SCTL SGMII0 Tx Frame Counter LSW [F:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u0.bits_0.sgmii0TxFrameCounterLSW

                        Default = 0x0000

                        SGMII0 Tx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 100M / GbE Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   sgmii0TxFrameCounterLSW : 16;    /* 1D.D313.F:0  SCTL      Default = 0x0000 */
                     /* SGMII0 Tx Good Frame Counter
                          */
    } bits_0;
    uint16_t word_0;
  } u0;
  /*! \brief Union for bit and word level access of word 1 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 1D.D314.9:0 SCTM SGMII0 Tx Frame Counter MSW [9:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u1.bits_1.sgmii0TxFrameCounterMSW

                        Default = 0x000

                        SGMII0 Tx Good Frame Counter
                        

                 <B>Notes:</B>
                        This counts 100M / GbE Ethernet good frames (i.e. no Ethernet CRC-32 / FCS errors).  */
      unsigned int   sgmii0TxFrameCounterMSW : 10;    /* 1D.D314.9:0  SCTM      Default = 0x000 */
                     /* SGMII0 Tx Good Frame Counter
                          */
    } bits_1;
    uint16_t word_1;
  } u1;
  /*! \brief Union for bit and word level access of word 2 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
                    /*! \brief 1D.D315.F:0 SCTL SGMII0 Tx Frame Error Counter LSW [F:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u2.bits_2.sgmii0TxFrameErrorCounterLSW

                        Default = 0x0000

                        SGMII0 Tx Bad Frame Error Counter
                        

                 <B>Notes:</B>
                        This counts 100M / GbE Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   sgmii0TxFrameErrorCounterLSW : 16;    /* 1D.D315.F:0  SCTL      Default = 0x0000 */
                     /* SGMII0 Tx Bad Frame Error Counter
                          */
    } bits_2;
    uint16_t word_2;
  } u2;
  /*! \brief Union for bit and word level access of word 3 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 6;
                    /*! \brief 1D.D316.9:0 SCTM SGMII0 Tx Frame Error Counter MSW [9:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u3.bits_3.sgmii0TxFrameErrorCounterMSW

                        Default = 0x000

                        SGMII0 Tx Bad Frame Error Counter
                        

                 <B>Notes:</B>
                        This counts 100M / GbE Ethernet frames with a bad FCS (aka CRC-32).  */
      unsigned int   sgmii0TxFrameErrorCounterMSW : 10;    /* 1D.D316.9:0  SCTM      Default = 0x000 */
                     /* SGMII0 Tx Bad Frame Error Counter
                          */
    } bits_3;
    uint16_t word_3;
  } u3;
  /*! \brief Union for bit and word level access of word 4 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 1D.D317.7:0 SCT SGMII0 Tx False Carrier Counter [7:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u4.bits_4.sgmii0TxFalseCarrierCounter

                        Default = 0x00

                        SGMII0 Tx False Carrier Counter
                        

                 <B>Notes:</B>
                        SGMII0 Tx detected false carrier on the GMII/MII interface.  */
      unsigned int   sgmii0TxFalseCarrierCounter : 8;    /* 1D.D317.7:0  SCT      Default = 0x00 */
                     /* SGMII0 Tx False Carrier Counter
                          */
    } bits_4;
    uint16_t word_4;
  } u4;
  /*! \brief Union for bit and word level access of word 5 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 1D.D318.7:0 SCT SGMII0 Tx Collision Counter [7:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u5.bits_5.sgmii0TxCollisionCounter

                        Default = 0x00

                        SGMII0 Tx Collision Counter
                        

                 <B>Notes:</B>
                        SGMII0 Tx detected a collision on the SGMII interface.  */
      unsigned int   sgmii0TxCollisionCounter : 8;    /* 1D.D318.7:0  SCT      Default = 0x00 */
                     /* SGMII0 Tx Collision Counter
                          */
    } bits_5;
    uint16_t word_5;
  } u5;
  /*! \brief Union for bit and word level access of word 6 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 1D.D319.7:0 SCT SGMII0 Tx Line Collision Counter [7:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u6.bits_6.sgmii0TxLineCollisionCounter

                        Default = 0x00

                        SGMII0 Tx Line Collision Counter
                        

                 <B>Notes:</B>
                        SGMII0 Tx detected a collision on the GMII/MII interface.  */
      unsigned int   sgmii0TxLineCollisionCounter : 8;    /* 1D.D319.7:0  SCT      Default = 0x00 */
                     /* SGMII0 Tx Line Collision Counter
                          */
    } bits_6;
    uint16_t word_6;
  } u6;
  /*! \brief Union for bit and word level access of word 7 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
                    /*! \brief 1D.D31A.F:0 SCT SGMII0 Tx Frame Alignment Counter [F:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u7.bits_7.sgmii0TxFrameAlignmentCounter

                        Default = 0x0000

                        SGMII0 Tx Frame Alignment Counter
                        

                 <B>Notes:</B>
                        SGMII0 Tx Frame Count with alignment error. This is detected by CRC error with an extra nibble on the MII interface (100M mode) on the GMII/MII interface.  */
      unsigned int   sgmii0TxFrameAlignmentCounter : 16;    /* 1D.D31A.F:0  SCT      Default = 0x0000 */
                     /* SGMII0 Tx Frame Alignment Counter
                          */
    } bits_7;
    uint16_t word_7;
  } u7;
  /*! \brief Union for bit and word level access of word 8 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
                    /*! \brief 1D.D31B.F:0 SCTL SGMII0 Tx Runt Frame Counter LSW [F:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u8.bits_8.sgmii0TxRuntFrameCounterLSW

                        Default = 0x0000

                        SGMII0 Tx Runt Frame Counter
                        

                 <B>Notes:</B>
                        SGMII0 Tx Runt Frame (less than 64 byte long) Count on the GMII/MII interface.  */
      unsigned int   sgmii0TxRuntFrameCounterLSW : 16;    /* 1D.D31B.F:0  SCTL      Default = 0x0000 */
                     /* SGMII0 Tx Runt Frame Counter
                          */
    } bits_8;
    uint16_t word_8;
  } u8;
  /*! \brief Union for bit and word level access of word 9 of GbE PHY SGMII0 Tx Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 10;
                    /*! \brief 1D.D31C.5:0 SCTM SGMII0 Tx Runt Frame Counter MSW [5:0]
                        AQ_GbePhySgmii0TxStatus_EUR.u9.bits_9.sgmii0TxRuntFrameCounterMSW

                        Default = 0x00

                        SGMII0 Tx Runt Frame Counter
                        

                 <B>Notes:</B>
                        SGMII0 Tx Runt Frame (less than 64 byte long) Count on the GMII/MII interface.  */
      unsigned int   sgmii0TxRuntFrameCounterMSW : 6;    /* 1D.D31C.5:0  SCTM      Default = 0x00 */
                     /* SGMII0 Tx Runt Frame Counter
                          */
    } bits_9;
    uint16_t word_9;
  } u9;
} AQ_GbePhySgmii0TxStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII WoL Status: 1D.D322 */
/*                  GbE PHY SGMII WoL Status: 1D.D322 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII WoL Status */
  union
  {
    struct
    {
      unsigned int   reserved0 : 16;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbePhySgmiiWolStatus_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII Rx Alarms: 1D.EC10 */
/*                  GbE PHY SGMII Rx Alarms: 1D.EC10 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII Rx Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 1D.EC10.7 LH SGMII0 Rx Loss of Signal
                        AQ_GbePhySgmiiRxAlarms_EUR.u0.bits_0.sgmii0RxLossOfSignal

                        

                        1 = SGMII0 Loss of Signal
                        
  */
      unsigned int   sgmii0RxLossOfSignal : 1;    /* 1D.EC10.7  LH       */
                     /* 1 = SGMII0 Loss of Signal
                          */
                    /*! \brief 1D.EC10.6 LH SGMII0 Rx Invalid Character Error
                        AQ_GbePhySgmiiRxAlarms_EUR.u0.bits_0.sgmii0RxInvalidCharacterError

                        

                        1 = SGMII0 Rx Invalid Character Error
                        
  */
      unsigned int   sgmii0RxInvalidCharacterError : 1;    /* 1D.EC10.6  LH       */
                     /* 1 = SGMII0 Rx Invalid Character Error
                          */
                    /*! \brief 1D.EC10.5 LH SGMII0 Rx Running Disparity Error
                        AQ_GbePhySgmiiRxAlarms_EUR.u0.bits_0.sgmii0RxRunningDisparityError

                        

                        1 = SGMII0 Rx Running Disparity Error
                        
  */
      unsigned int   sgmii0RxRunningDisparityError : 1;    /* 1D.EC10.5  LH       */
                     /* 1 = SGMII0 Rx Running Disparity Error
                          */
                    /*! \brief 1D.EC10.4 LH SGMII0 Rx Code Violation Error
                        AQ_GbePhySgmiiRxAlarms_EUR.u0.bits_0.sgmii0RxCodeViolationError

                        

                        1 = SGMII0 Rx Code Violation Error
                        
  */
      unsigned int   sgmii0RxCodeViolationError : 1;    /* 1D.EC10.4  LH       */
                     /* 1 = SGMII0 Rx Code Violation Error
                          */
      unsigned int   reserved1 : 4;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbePhySgmiiRxAlarms_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII Tx Alarms: 1D.EC20 */
/*                  GbE PHY SGMII Tx Alarms: 1D.EC20 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII Tx Alarms */
  union
  {
    struct
    {
      unsigned int   reserved0 : 9;
                    /*! \brief 1D.EC20.6 LH SGMII0 Tx Invalid GMII Character Detected
                        AQ_GbePhySgmiiTxAlarms_EUR.u0.bits_0.sgmii0TxInvalidGmiiCharacterDetected

                        

                        1 = SGMII0 Tx Invalid GMII Character Detected
                        
  */
      unsigned int   sgmii0TxInvalidGmiiCharacterDetected : 1;    /* 1D.EC20.6  LH       */
                     /* 1 = SGMII0 Tx Invalid GMII Character Detected
                          */
                    /*! \brief 1D.EC20.5 LH SGMII0 Magic Packet Frame Detected
                        AQ_GbePhySgmiiTxAlarms_EUR.u0.bits_0.sgmii0MagicPacketFrameDetected

                        

                        1 = SGMII0 Magic Packet Frame Detected
                        
  */
      unsigned int   sgmii0MagicPacketFrameDetected : 1;    /* 1D.EC20.5  LH       */
                     /* 1 = SGMII0 Magic Packet Frame Detected
                          */
                    /*! \brief 1D.EC20.4 LH SGMII0 Wake Up Frame Detected
                        AQ_GbePhySgmiiTxAlarms_EUR.u0.bits_0.sgmii0WakeUpFrameDetected

                        

                        1 = SGMII0 Wake Up Frame Detected
                        
  */
      unsigned int   sgmii0WakeUpFrameDetected : 1;    /* 1D.EC20.4  LH       */
                     /* 1 = SGMII0 Wake Up Frame Detected
                          */
      unsigned int   reserved1 : 4;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbePhySgmiiTxAlarms_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII Rx Interrupt Mask: 1D.F410 */
/*                  GbE PHY SGMII Rx Interrupt Mask: 1D.F410 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII Rx Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 8;
                    /*! \brief 1D.F410.7 R/WPD SGMII0 Rx Loss of Signal Mask
                        AQ_GbePhySgmiiRxInterruptMask_EUR.u0.bits_0.sgmii0RxLossOfSignalMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   sgmii0RxLossOfSignalMask : 1;    /* 1D.F410.7  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 1D.F410.6 R/WPD SGMII0 Rx Invalid Character Error Mask
                        AQ_GbePhySgmiiRxInterruptMask_EUR.u0.bits_0.sgmii0RxInvalidCharacterErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   sgmii0RxInvalidCharacterErrorMask : 1;    /* 1D.F410.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 1D.F410.5 R/WPD SGMII0 Rx Running Disparity Error Mask
                        AQ_GbePhySgmiiRxInterruptMask_EUR.u0.bits_0.sgmii0RxRunningDisparityErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   sgmii0RxRunningDisparityErrorMask : 1;    /* 1D.F410.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 1D.F410.4 R/WPD SGMII0 Rx Code Violation Error Mask
                        AQ_GbePhySgmiiRxInterruptMask_EUR.u0.bits_0.sgmii0RxCodeViolationErrorMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   sgmii0RxCodeViolationErrorMask : 1;    /* 1D.F410.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 4;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbePhySgmiiRxInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY SGMII Tx Interrupt Mask: 1D.F420 */
/*                  GbE PHY SGMII Tx Interrupt Mask: 1D.F420 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY SGMII Tx Interrupt Mask */
  union
  {
    struct
    {
      unsigned int   reserved0 : 9;
                    /*! \brief 1D.F420.6 R/WPD SGMII0 Tx Invalid GMII Character Detected Mask
                        AQ_GbePhySgmiiTxInterruptMask_EUR.u0.bits_0.sgmii0TxInvalidGmiiCharacterDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   sgmii0TxInvalidGmiiCharacterDetectedMask : 1;    /* 1D.F420.6  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 1D.F420.5 R/WPD SGMII0 Magic Packet Frame Detected Mask
                        AQ_GbePhySgmiiTxInterruptMask_EUR.u0.bits_0.sgmii0MagicPacketFrameDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   sgmii0MagicPacketFrameDetectedMask : 1;    /* 1D.F420.5  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
                    /*! \brief 1D.F420.4 R/WPD SGMII0 Wake Up Frame Detected Mask
                        AQ_GbePhySgmiiTxInterruptMask_EUR.u0.bits_0.sgmii0WakeUpFrameDetectedMask

                        Provisionable Default = 0x0

                        1 = Enable interrupt generation
                        0 = Disable interrupt generation
                        
  */
      unsigned int   sgmii0WakeUpFrameDetectedMask : 1;    /* 1D.F420.4  R/WPD      Provisionable Default = 0x0 */
                     /* 1 = Enable interrupt generation
                        0 = Disable interrupt generation
                          */
      unsigned int   reserved1 : 4;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbePhySgmiiTxInterruptMask_EUR;


/*---------------------------------------------------------------------------------*/
/*! \brief                GbE PHY Vendor Global Interrupt Flags: 1D.FC00 */
/*                  GbE PHY Vendor Global Interrupt Flags: 1D.FC00 */
/*---------------------------------------------------------------------------------*/
typedef struct 
{
  /*! \brief Union for bit and word level access of word 0 of GbE PHY Vendor Global Interrupt Flags */
  union
  {
    struct
    {
      unsigned int   reserved0 : 11;
                    /*! \brief 1D.FC00.4 RO Vendor Specific SGMII Tx Alarms 1 Interrupt
                        AQ_GbePhyVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificSgmiiTxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific SGMII Tx Alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificSgmiiTxAlarms_1Interrupt : 1;    /* 1D.FC00.4  RO       */
                     /* 1 = Interrupt in vendor specific SGMII Tx Alarms 1
                          */
                    /*! \brief 1D.FC00.3 RO Vendor Specific SGMII Tx Alarms 2 Interrupt
                        AQ_GbePhyVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificSgmiiTxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific SGMII Tx Alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificSgmiiTxAlarms_2Interrupt : 1;    /* 1D.FC00.3  RO       */
                     /* 1 = Interrupt in vendor specific SGMII Tx Alarms 2
                          */
                    /*! \brief 1D.FC00.2 RO Vendor Specific SGMII Rx Alarms 1 Interrupt
                        AQ_GbePhyVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificSgmiiRxAlarms_1Interrupt

                        

                        1 = Interrupt in vendor specific SGMII Tx Alarms 1
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificSgmiiRxAlarms_1Interrupt : 1;    /* 1D.FC00.2  RO       */
                     /* 1 = Interrupt in vendor specific SGMII Tx Alarms 1
                          */
                    /*! \brief 1D.FC00.1 RO Vendor Specific SGMII Rx Alarms 2 Interrupt
                        AQ_GbePhyVendorGlobalInterruptFlags_EUR.u0.bits_0.vendorSpecificSgmiiRxAlarms_2Interrupt

                        

                        1 = Interrupt in vendor specific SGMII Tx Alarms 2
                        

                 <B>Notes:</B>
                        An interrupt was generated from the status register and the corresponding mask register.  */
      unsigned int   vendorSpecificSgmiiRxAlarms_2Interrupt : 1;    /* 1D.FC00.1  RO       */
                     /* 1 = Interrupt in vendor specific SGMII Tx Alarms 2
                          */
      unsigned int   reserved1 : 1;
    } bits_0;
    uint16_t word_0;
  } u0;
} AQ_GbePhyVendorGlobalInterruptFlags_EUR;

#endif
/*@}*/
/*@}*/
