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
    This file contains the AQ_API function and datatype declarations. */


#ifndef AQ_API_TOKEN
#define AQ_API_TOKEN

#include <stdint.h>

#include <AQ_User.h>
#include "AQ_ReturnCodes.h"

/*******************************************************************
                         General
*******************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! This typedef defines the bool datatype which takes the values 
true and false.*/
typedef enum {False = 0, True = 1} AQ_boolean;


/*@}*/


/*******************************************************************
                        Device Identity
*******************************************************************/

/*! \defgroup deviceIdentity Device Identity
All AQ_API functions accept a parameter identifying the target PHY that
should be acted upon. */
/*@{*/


/*! This enumeration is used to describe the different types of
    Aquantia PHY.*/
typedef enum    
{    
  /*! 1/2/4-port package, 40nm architechture.*/
 AQ_DEVICE_APPIA,   
  /*! 1/2/4-port package, first-generation 28nm architechture.*/
 AQ_DEVICE_HHD,   
  /*! 1/2/4-port package, second-generation 28nm architechture.*/
 AQ_DEVICE_EUR   
}  AQ_API_Device;  

/*! This structure is used to specify a particular Aquantia PHY port
    within the system.*/
typedef struct    
{    
  /*! The type of Aquantia PHY*/
 AQ_API_Device  device; 
  /*! Uniquely identifies the port within the system. AQ_Port must be
      defined to whatever data type is suitable for the platform.
      AQ_API functions will never do anything with PHY_ID other than
      pass it down to the platform's PHY register read/write
      functions.*/
 AQ_Port  PHY_ID; 
} AQ_API_Port;    

/*@}*/


/*******************************************************************
                        Configuration
*******************************************************************/

/*! \defgroup configuration Configuration
Control of an Aquantia PHY is provided via the following enumerations and
structures. These parameters are divided into AQ_API_Configuration, and
AQ_API_StaticConfiguration. AQ_API_Configuration contains settings that may
be dynamically changed during regular operation, whereas
AQ_API_StaticConfiguration is used to report the state of settings that
would typically be changed only by provisioning, as well as the state of
pins as they are connected on a printed circuit board. Functions are
provided to control all of these structures. */
/*@{*/


/*! This enumeration is used to define the amount of LED activity
    stretching to apply.*/
typedef enum    
{    
  /*! This indicates that no pulse stretching is applied to selected
      LED activity.*/
 AQ_API_LS_Off,   
  /*! This indicates that 28ms of pulse stretching is applied to
      selected LED activity.*/
 AQ_API_LS_28ms,   
  /*! This indicates that 60ms of pulse stretching is applied to
      selected LED activity.*/
 AQ_API_LS_60ms,   
  /*! This indicates that 100ms of pulse stretching is applied to
      selected LED activity.*/
 AQ_API_LS_100ms   
}  AQ_API_LED_Stretch;  

/*! This structure is used by the API to control how an LED within a
    target Aquantia PHY is to behave. It is used within the structure
    AQ_API_Configuration.*/
typedef struct    
{    
  /*! When set, this manually turns on the LED.*/
 AQ_boolean  LED_On; 
  /*! When set, the LED is turned on when a link is established at
      10G.*/
 AQ_boolean  LED_On_When10G_LinkEstablished; 
  /*! When set, the LED is turned on when a link is established at
      5G.*/
 AQ_boolean  LED_On_When5G_LinkEstablished; 
  /*! When set, the LED is turned on when a link is established at
      2.5G.*/
 AQ_boolean  LED_On_When2_5G_LinkEstablished; 
  /*! When set, the LED is turned on when a link is established at
      1G.*/
 AQ_boolean  LED_On_When1G_LinkEstablished; 
  /*! When set, the LED is turned on when a link is established at
      100M.*/
 AQ_boolean  LED_On_When100M_LinkEstablished; 
  /*! When set, the LED is turned on when establishing a link.*/
 AQ_boolean  LED_On_WhenConnecting; 
  /*! When set, the LED state toggles on detecting a received packet,
      for an amount of time determined by either the length of the
      packet, or the value set in the enumeration, LED_Stretch.*/
 AQ_boolean  LED_TogglesOnReceiveActivity; 
  /*! When set, the LED state toggles on detecting a transmitted
      packet, for an amount of time determined by either the length of
      the packet, or the value set in the enumeration, LED_Stretch.*/
 AQ_boolean  LED_TogglesOnTransmitActivity; 
  /*! This enumeration sets how much longer an LED is turned on when
      configured to detect receive and /or transmit activity.*/
 AQ_API_LED_Stretch   LED_Stretch;
} AQ_API_LED_Control;    

/*! This enumeration is used to define the FLASH memory device that is
    attached, if the Aquantia PHY is provisioned to run from FLASH. It
    is used in the structure AQ_API_StaticConfiguration.*/
typedef enum    
{    
  /*! Atmel 64K byte FLASH.*/
 AQ_API_F_AT25F512A,   
  /*! Atmel Smart (Adesto) 512K byte FLASH.*/
 AQ_API_F_AT45DB041D,   
  /*! Atmel Smart (Adesto) 512K byte FLASH new revision.*/
 AQ_API_F_AT45DB041E,   
  /*! Numonyx Microelectronics 64K byte FLASH.*/
 AQ_API_F_M25P05A,   
  /*! Atmel 256K byte byte FLASH.*/
 AQ_API_F_AT25DF021A,   
  /*! Atmel 512K byte byte FLASH.*/
 AQ_API_F_AT25DF041A,   
  /*! Numonyx 512K byte FLASH.*/
 AQ_API_F_M25P40,   
  /*! Macronix 512K byte FLASH (MX25V4005C, MX25V4006).*/
 AQ_API_F_MX25V400,   
  /*! Macronix 512K byte FLASH.*/
 AQ_API_F_MX25V4035F,   
  /*! Adesto Smart 4M byte FLASH.*/
 AQ_API_F_AT45DB321E,   
  /*! Macronix 4M byte FLASH.*/
 AQ_API_F_MX25L32,   
  /*! Winbond 4M byte FLASH.*/
 AQ_API_F_W25Q32,   
  /*! Winbond 2M byte FLASH.*/
 AQ_API_F_W25Q16DW,   
  /*! Winbond 512K byte FLASH.*/
 AQ_API_F_W25X40,   
  /*! FLASH is not present as this is a daisy-chain slave device.*/
 AQ_API_F_DaisyChainSlave = 100,   
  /*! FLASH is either absent or the type is unknown.*/
 AQ_API_F_Indeterminate   
} AQ_API_FLASH;   

/*! This structure is used to specify image information from the
    FLASH.*/
typedef struct    
{    
  /*! This bit indicates whether the FLASH is programmed. Errors
      reading the FLASH, or reading an all 0xFF version string
      indicate an unprogrammed state.*/
 AQ_boolean  programmed; 
  /*! The 61 character firmware ID string stored in the FLASH image
      (the NUL terminator makes 62 bytes).*/
 char  imageID_String[62]; 
  /*! The firmware major revision number from the FLASH image*/
 uint8_t  imageMajorRevisionNumber; 
  /*! The firmware minor revision number from the FLASH image*/
 uint8_t  imageMinorRevisionNumber; 
  /*! The ROM ID of the FLASH image, used to disambiguate images with
      different provisioned defaults.*/
 uint8_t  imageROM_ID_Number; 
} AQ_API_ImageInformation;    

/*! This enumeration is used to define the start mode of the SERDES
    system interface on the Aquantia PHY. It is used in the structure
    AQ_API_Configuration.*/
typedef enum    
{    
  /*!  The Aquantia PHY comes out of reset with the selected 10G
       interface on and automatic rate selection enabled.*/
 AQ_API_SSSM_10G_On,   
  /*! The Aquantia PHY comes out of reset with SGMII on with automatic
      rate selection enabled and SGMII autonegotiation (XSGMII mode)*/
 AQ_API_SSSM_XSGMII_On,   
  /*! The Aquantia PHY comes out of reset with 1000BASE-X on with
      automatic rate selection enabled and no SGMII autonegotiation.*/
 AQ_API_SSSM_1000BASE_X_On,   
  /*! The Aquantia PHY comes out of reset with all interfaces off with
      automatic rate selection enabled.*/
 AQ_API_SSSM_Off,   
  /*! The Aquantia PHY comes out of reset with USXGMII on.
      Compatibility: 28nm PHYs only.*/
 AQ_API_SSSM_UXSGMII_On,   
  /*! Unrecognized mode*/
 AQ_API_SSSM_Other   
} AQ_API_10G_StartMode;   

/*! This enumeration is used to define the system-side 10G operating
    mode of the Aquantia PHY. It is used in the structure
    AQ_API_StaticConfiguration.*/
typedef enum    
{    
  /*! XFI*/
 AQ_API_10G_SOM_XFI,   
  /*! RXAUI - Marvell version*/
 AQ_API_10G_SOM_RXAUI_Marvell,   
  /*! RXAUI - Dune version*/
 AQ_API_10G_SOM_RXAUI_Dune,   
  /*! XAUI*/
 AQ_API_10G_SOM_XAUI,   
  /*! Unrecognized mode*/
 AQ_API_10G_SOM_Other   
} AQ_API_10G_SystemOperatingMode;   

/*! This enumeration is used to define the network-side 10G operating
    mode of the Aquantia PHY. It is used in the structure
    AQ_API_StaticConfiguration.*/
typedef enum    
{    
  /*! The MDI (RJ-45) serves as the network interface*/
 AQ_API_10G_NOM_10GBASE_T,   
  /*! The XFI lookaside interface serves as the network interface*/
 AQ_API_10G_NOM_XFI,   
  /*! Unrecognized mode*/
 AQ_API_10G_NOM_Other   
} AQ_API_10G_NetworkOperatingMode;   

/*! This enumeration is used to define the network-side 1G/100M
    operating mode of the Aquantia PHY. It is used in the structure
    AQ_API_StaticConfiguration.*/
typedef enum    
{    
  /*! The MDI (RJ-45) serves as the network interface (1000BASE-T when
      connected at 1G, 100BASE-TX when connected at 100M)*/
 AQ_API_1G_NOM_1000BASE_T,   
  /*! The SGMII lookaside interface serves as the network interface*/
 AQ_API_1G_NOM_1000BASE_X,   
  /*! Unrecognized mode*/
 AQ_API_1G_NOM_Other   
} AQ_API_1G_NetworkOperatingMode;   

/*! This enumeration is used to define the Wake-On-LAN connection rate
    of the Aquantia PHY. It is used in the structure
    AQ_API_Configuration.*/
typedef enum    
{    
  /*! 100BASE-TX.*/
 AQ_API_WOL_100BASE_TX,   
  /*! 1000BASE-T.*/
 AQ_API_WOL_1000BASE_T,   
  /*! Wake On LAN is not enabled.*/
 AQ_API_WOL_None   
} AQ_API_WoLRate;   

/*! This structure is used to specify a 128-bit Wake-On-LAN frame
    filter. Each bit corresponds to the number of a byte to be matched
    in a received Ethernet packet, with bit 0 corresponding to the
    first received byte (the MSB) of the Ethernet frame's destination
    MAC address. A CRC-32 (the same CRC-32 used by the IEEE to
    calculate the Ethernet FCS in 802.3) of these selected bytes is
    calculated and compared against the CRC-32 provided for this
    filter. If a match occurs and Wake-On-LAN operation is enabled,
    then a wake-up event will occur.*/
typedef struct    
{    
  /*! Bits 127:96 of the 128-bit Wake-On-LAN frame filter.*/
 uint32_t  filter3; 
  /*! Bits 95:64 of the 128-bit Wake-On-LAN frame filter.*/
 uint32_t  filter2; 
  /*! Bits 63:32 of the 128-bit Wake-On-LAN frame filter.*/
 uint32_t  filter1; 
  /*! Bits 31:0 of the 128-bit Wake-On-LAN frame filter.*/
 uint32_t  filter0; 
  /*! The CRC-32 signature to match for this filter.*/
 uint32_t  crc32; 
  /*! Setting this bit enables the filter operation.*/
 AQ_boolean  enable; 
} AQ_API_WakeUpFrame;    

/*! This structure is used to specify a magic packet Wake-On-LAN frame
    filter. A magic packet is defined as a sequence of 6 bytes of
    0xFF, followed by 16 repititions of the programmable MAC address
    (6 bytes).*/
typedef struct    
{    
  /*! Bits 47:32 of the 48-bit MAC address used in the magic packet
      filter.*/
 uint16_t  filter2; 
  /*! Bits 31:16 of the 48-bit MAC address used in the magic packet
      filter.*/
 uint32_t  filter1; 
  /*! Bits 15:0 of the 48-bit MAC address used in the magic packet
      filter.*/
 uint32_t  filter0; 
  /*! Setting this bit enables the CRC-32.*/
 AQ_boolean  enable; 
} AQ_API_MagicPacketFrame;    

/*! This structure is used by the API to control an Aquantia PHY.*/
typedef struct    
{    
 /*thermal*/   
  /*! The temperature, in Celsius, below which a low temperature
      warning alarm will be generated, if enabled. LSB = 1 degree
      Celsius.*/
 int16_t  lowTemperatureWarningThreshold; 
  /*! The temperature, in Celsius, below which a low temperature alarm
      will be generated, if enabled. LSB = 1 degree Celsius.*/
 int16_t  lowTemperatureFailureThreshold; 
  /*! The temperature, in Celsius, above which a high temperature
      warning alarm will be generated, if enabled. LSB = 1 degree
      Celsius.*/
 int16_t  highTemperatureWarningThreshold; 
  /*! The temperature, in Celsius, above which a high temperature
      alarm will be generated, if enabled. LSB = 1 degree Celsius.*/
 int16_t  highTemperatureFailureThreshold; 
 /*10G operating mode*/   
  /*! Setting this prevents the Aquantia PHY from performing LDPC
      error correction on the received 10GBASE-T data stream.
      Disabling this minimizes the delay through the Aquantia PHY
      receive path, but in exchange for no error correction capability
      on to the link.
      Compatibility: 40nm PHYs only.*/
 AQ_boolean  disableErrorCorrection; 
  /*! Setting this prevents the Aquantia PHY, upon detection of either
      an LDPC decoding failure, or a CRC8 failure, from marking
      packets within a 10GBASE-T transport frame as bad. Disabling
      this removes 320 ns of delay from the receive path, but now
      places the responsibility for bad data detection entirely on the
      MAC.*/
 AQ_boolean  disableCRC8_FrameTrashing; 
 /*LEDs*/   
  /*! Controls the operation of the 6 LEDs on the target Aquantia PHY
      (0 corresponds to Channel 0). See the structure
      AQ_API_LED_Control for details.*/
 AQ_API_LED_Control   LED_Control[6];
 /*Wake on LAN*/   
  /*! This enumeration controls Wake-On-LAN operation.*/
 AQ_API_WoLRate   wolControl;
  /*! The wake-up Wake-On LAN frames for the Aquantia PHY.*/
 AQ_API_WakeUpFrame   wakeUpFrame[8];
  /*! The magic packet Wake-On LAN frame for the Aquantia PHY.*/
 AQ_API_MagicPacketFrame   magicPacketFrame;
} AQ_API_Configuration;    

/*! This enumeration is used to identify what the boot method is.*/
typedef enum    
{    
  /*! Daisy-chain slave*/
 AQ_API_DC_Slave,   
  /*! Daisy-chain master*/
 AQ_API_DC_Master   
} AQ_API_DaisyChainSetting;   

/*! This structure is used to read unsettable parameters associated
    with the Aquantia PHY.*/
typedef struct    
{    
 /*ID*/   
  /*! The OUI of the Aquantia PHY taken from the PMA Device ID.*/
 uint32_t  OUI; 
  /*! The IEEE model number of the Aquantia PHY taken from the PMA
      Device ID.*/
 uint8_t  IEEE_ModelNumber; 
  /*! The IEEE revision number of the Aquantia PHY taken from the PMA
      Device ID.*/
 uint8_t  IEEE_RevisionNumber; 
  /*! The Firmware major revision number*/
 uint8_t  firmwareMajorRevisionNumber; 
  /*! The Firmware minor revision number*/
 uint8_t  firmwareMinorRevisionNumber; 
  /*! The ROM ID of the image, used to disambiguate images with
      different provisioned defaults.*/
 uint8_t  firmwareROM_ID_Number; 
 /*memory*/   
  /*! This indicates whether the current PHY is set to be daisy-chain
      master or daisy-chain slave.*/
 AQ_API_DaisyChainSetting   daisyChainSetting;
 /*connectivity*/   
  /*! The pull-up or pull-down state of the Tx Enable pin.*/
 AQ_boolean  txEnable; 
  /*! The pull-up or pull-down state of the six LEDs. LED[x] = LED x).
      1 = pulled high.*/
 AQ_boolean  LED[6]; 
 /*system interface configuration*/   
  /*! The system interface operating mode for 10G operation.*/
 AQ_API_10G_SystemOperatingMode   _10G_SystemOperatingMode;
 /*network interface configuration*/   
  /*! The system interface operating mode for 10G operation.*/
 AQ_API_10G_NetworkOperatingMode   _10G_NetworkOperatingMode;
  /*! The network interface operating mode for 1G/100M operation.*/
 AQ_API_1G_NetworkOperatingMode   _1G_NetworkOperatingMode;
 /*FLASH*/   
  /*! The frequency of the FLASH clock in MHz is equal to the value:
      160 MHz divided by the (flashClockDivisor + 1).*/
 uint16_t  flashClockDivisor; 
 /*clocks*/   
  /*! If true, the 25 MHz output will be disabled.
      Compatibility: 40nm PHYs only.*/
 AQ_boolean  _25MHzOutputDisable; 
 /*MDIO*/   
  /*! If true, the MDIO data line on the Aquantia PHY functions as an
      open-drain driver (which in general is much slower as it relies
      on pull-ups on the interface). If false, the MDIO interface
      enables a push-pull CMOS driver.*/
 AQ_boolean  mdioOpenDrain; 
  /*! If true, the MDIO input Aquantia PHY allows preamble suppression
      (i.e. it only needs to see a single 1 prior to the start of the
      MDIO data frame). if false, the Aquantia PHY expects to see the
      prescribed 32 bits of preamble on each MDIO data frame.*/
 AQ_boolean  mdioPreambleSuppression; 
  /*! If true, the Aquantia PHY treats PHY address 0 as a broadcast
      address for writes, and reads on this address are ignored.*/
 AQ_boolean  address0_BroadcastEnable; 
  /*! If true, registers spanning more than 16 bits should have their
      MSW read first to create the appropriate snap-shot behavior for
      the register pair. If false, the LSW of the pair should be read
      first.*/
 AQ_boolean  MSW_ReadFirst; 
 /*MDI*/   
  /*! If true, the MDI interface is swapped so that A <-> D and B<->
      C.*/
 AQ_boolean  mdiSwap; 
 /*XFI*/   
  /*! Setting this to one inverts the data that goes out on XFI0
      (lookaside) Tx.*/
 AQ_boolean  XFI0_TxInvert; 
  /*! Setting this to one inverts the data that comes in on XFI0
      (lookaside) Rx.*/
 AQ_boolean  XFI0_RxInvert; 
  /*! Setting this to one inverts the data that goes out on XFI1
      (system) Tx.*/
 AQ_boolean  XFI1_TxInvert; 
  /*! Setting this to one inverts the data that comes in on XFI1
      (system) Rx.*/
 AQ_boolean  XFI1_RxInvert; 
 /*RXAUI*/   
  /*! The physical SERDES lane to use for RXAUI Tx Lane 0.*/
 uint8_t  RXAUI_TxLane0_SERDES; 
  /*! The physical SERDES lane to use for RXAUI Tx Lane 1.*/
 uint8_t  RXAUI_TxLane1_SERDES; 
  /*! Setting this to one inverts the data that goes out on RXAUI Tx
      Lane 0.*/
 AQ_boolean  RXAUI_TxLane0_Invert; 
  /*! Setting this to one inverts the data that goes out on RXAUI Tx
      Lane 1.*/
 AQ_boolean  RXAUI_TxLane1_Invert; 
  /*! The physical SERDES lane to use for RXAUI Lane 0.*/
 uint8_t  RXAUI_RxLane0_SERDES; 
  /*! The physical SERDES lane to use for RXAUI Rx Lane 1.*/
 uint8_t  RXAUI_RxLane1_SERDES; 
  /*! Setting this to one inverts the data that comes in on RXAUI Rx
      Lane 0.*/
 AQ_boolean  RXAUI_RxLane0_Invert; 
  /*! Setting this to one inverts the data that comes in on RXAUI Rx
      Lane 1.*/
 AQ_boolean  RXAUI_RxLane1_Invert; 
 /*XAUI*/   
  /*! The physical SERDES lane to use for XAUI Tx Lane 0.*/
 uint8_t  XAUI_TxLane0_SERDES; 
  /*! The physical SERDES lane to use for XAUI Tx Lane 1.*/
 uint8_t  XAUI_TxLane1_SERDES; 
  /*! The physical SERDES lane to use for XAUI Tx Lane 2.*/
 uint8_t  XAUI_TxLane2_SERDES; 
  /*! The physical SERDES lane to use for XAUI Tx Lane 3.*/
 uint8_t  XAUI_TxLane3_SERDES; 
  /*! Setting this to one inverts the data that goes out on XAUI Tx
      Lane 0.*/
 AQ_boolean  XAUI_TxLane0_Invert; 
  /*! Setting this to one inverts the data that goes out on XAUI Tx
      Lane 1.*/
 AQ_boolean  XAUI_TxLane1_Invert; 
  /*! Setting this to one inverts the data that goes out on XAUI Tx
      Lane 2.*/
 AQ_boolean  XAUI_TxLane2_Invert; 
  /*! Setting this to one inverts the data that goes out on XAUI Tx
      Lane 3.*/
 AQ_boolean  XAUI_TxLane3_Invert; 
  /*! The physical SERDES lane to use for XAUI Lane 0.*/
 uint8_t  XAUI_RxLane0_SERDES; 
  /*! The physical SERDES lane to use for XAUI Rx Lane 1.*/
 uint8_t  XAUI_RxLane1_SERDES; 
  /*! The physical SERDES lane to use for XAUI Rx Lane 2.*/
 uint8_t  XAUI_RxLane2_SERDES; 
  /*! The physical SERDES lane to use for XAUI Rx Lane 3.*/
 uint8_t  XAUI_RxLane3_SERDES; 
  /*! Setting this to one inverts the data that comes in on XAUI Rx
      Lane 0.*/
 AQ_boolean  XAUI_RxLane0_Invert; 
  /*! Setting this to one inverts the data that comes in on XAUI Rx
      Lane 1.*/
 AQ_boolean  XAUI_RxLane1_Invert; 
  /*! Setting this to one inverts the data that comes in on XAUI Rx
      Lane 2.*/
 AQ_boolean  XAUI_RxLane2_Invert; 
  /*! Setting this to one inverts the data that comes in on XAUI Rx
      Lane 3.*/
 AQ_boolean  XAUI_RxLane3_Invert; 
 /*SGMII*/   
  /*! The physical SERDES lane to use for SGMII Tx.*/
 uint8_t  SGMII_TxSERDES; 
  /*! The physical SERDES lane to use for SGMII Rx.*/
 uint8_t  SGMII_RxSERDES; 
  /*! Setting this to one inverts the data that goes out on SGMII
      Tx.*/
 AQ_boolean  SGMII_TxInvert; 
  /*! Setting this to one inverts the data that comes in on SGMII
      Rx.*/
 AQ_boolean  SGMII_RxInvert; 
 /*10G Start Mode*/   
  /*! This enumeration controls the start-up operation of the selected
      10G interface.*/
 AQ_API_10G_StartMode   _10G_StartMode;
} AQ_API_StaticConfiguration;    

/*! This structure is used to read the parameters with the FLASH on an
    Aquantia PHY.*/
typedef struct    
{    
  /*! This tells the Aquantia PHY what sort of FLASH it is operating
      with. See the enumeration AQ_API_FLASH for details.*/
 AQ_API_FLASH   flashType;
 AQ_API_ImageInformation   imageInformation;
} AQ_API_FlashInformation;    

/*! This function reads the operating control settings from an
    Aquantia PHY into a user provided AQ_API_Configuration
    structure.*/
AQ_Retcode   AQ_API_GetConfiguration
 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The configuration settings of an Aquantia PHY.*/
 AQ_API_Configuration*   configuration
);    

/*! This function writes the operating control settings to an Aquantia
    PHY from a user provided AQ_API_Configuration structure.*/
AQ_Retcode   AQ_API_SetConfiguration 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! The configuration settings for an Aquantia PHY.*/
 AQ_API_Configuration*   configuration
);    

/*! This function reads the static configuration settings of an
    Aquantia PHY into a user provided AQ_API_StaticConfiguration
    structure.*/
AQ_Retcode   AQ_API_GetStaticConfiguration 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! The board configuration settings for an Aquantia PHY.*/
 AQ_API_StaticConfiguration*   configuration
);    

/*! This function reads the FLASH information from an Aquantia PHY
    into a user provided AQ_API_FlashInformation structure. Note that
    this halts the processor.
    Return codes:
    AQ_RET_FLASHINTF_READINESS_TIMEOUT: The timout period elapsed
    while waiting for the PHY's NVR interface to indicate readiness
    for reading.
    AQ_RET_FLASH_READINESS_TIMEOUT: The timout period elapsed while
    waiting for the FLASH to indicate readiness for reading.
    AQ_RET_FLASH_TYPE_UNKNOWN: The type of FLASH could not be
    determined.
    AQ_RET_FLASH_TYPE_BAD: The type of FLASH was determined to be of
    an unsuitable type for reading. This can happen if port does not
    indicate the daisy-chain master.
    */
AQ_Retcode   AQ_API_GetFlashInformation 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! The FLASH information for an Aquantia PHY.*/
 AQ_API_FlashInformation*   information
);    

/*@}*/


/*******************************************************************
                        Chip Status
*******************************************************************/

/*! \defgroup chipStatus Chip Status
These functions are used by the API to control the state of the Aquantia
PHYs that are deployed in a system. */
/*@{*/


/*! This structure is used by the API to report the status of an
    Aquantia PHY.*/
typedef struct    
{    
 /*thermal*/   
  /*! The temperature in Celsius, accurate to +/- 5 degrees, of the
      on-chip sensor, offset by the temperatureOffset provisioned in
      the AQ_API_Configuration. A return value of -100 indicates that
      the temperature measurement is not available.*/
 int16_t  temperature; 
 /*firmware*/   
  /*! This provides details about the image loaded in the DRAM.*/
 AQ_API_ImageInformation   loadedImageInformation;
} AQ_API_Status;    

/*! This function gets the status of an Aquantia PHY. The user must
    provide a pointer to an AQ_API_Status structure for this function
    to return the results into.*/
AQ_Retcode   AQ_API_GetStatus 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! The status of the PHY being addressed.*/
 AQ_API_Status*   status
);    

/*! This function initiates a hard reset of an Aquantia PHY.
    Compatibility: 40nm PHYs only.*/
AQ_Retcode   AQ_API_HardReset 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port
);    

/*! This function initiates a soft reset of an Aquantia PHY.*/
AQ_Retcode   AQ_API_SoftReset 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port
);    

/*! This function places the target Aquantia PHY into the low-power
    state. In this state, the Aquantia PHY's internal processor and
    MDIO is functional, but all other circuitry is powered down, along
    with the LVDD supply.*/
AQ_Retcode   AQ_API_SetLowPower 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port
);    

/*! This function places the target Aquantia PHY into the high-
    impedance state and clears any individual power-down bits. In this
    state, the output of the Aquantia PHY is powered down, but the
    rest of the Aquantia PHY remains active.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.*/
AQ_Retcode   AQ_API_SetHighImpedance 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port
);    

/*! This function places the target Aquantia PHY into the active
    state, and restarts autonegotiation.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.*/
AQ_Retcode   AQ_API_RestartAutonegotiation 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port
);    

/*! This function places the target Aquantia PHY into the operational
    state, which will cause it to attempt to connect with a far-end
    device. If any loopbacks or test-patterns are set, they will be
    cleared.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.*/
AQ_Retcode   AQ_API_SetActive 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port
);    

/*@}*/


/*******************************************************************
                        Connection Status
*******************************************************************/

/*! \defgroup connectionStatus Connection Status
The following structures and functions are used to report the connection
status of an Aquantia PHY. Through these tools, all of the information
about the connection from SNR to noise power is provided, as well as the
number of connection attempts associated with the current connection. */
/*@{*/


/*! This enumeration is used report whether an Aquantia PHY was chosen
    to be the master or the slave as the result of the autonegotiation
    process.*/
typedef enum    
{    
  /*! Identifies that the Aquantia PHY was configured as the master
      during autonegotiation.*/
 AQ_API_MSS_Master,   
  /*! Identifies that the Aquantia PHY was configured as the slave
      during autonegotiation.*/
 AQ_API_MSS_Slave   
} AQ_API_MasterSlaveStatus;   

/*! This enumeration is used report the Pair connection and inversion
    status for the MDI of an Aquantia PHY.*/
typedef enum    
{    
  /*! Indicates a connection to Pair A.*/
 AQ_API_PS_PairA,   
  /*! Indicates a connection to inverted Pair A.*/
 AQ_API_PS_PairA_Inverted,   
  /*! Indicates a connection to Pair B.*/
 AQ_API_PS_PairB,   
  /*! Indicates a connection to inverted Pair B.*/
 AQ_API_PS_PairB_Inverted,   
  /*! Indicates a connection to Pair C.*/
 AQ_API_PS_PairC,   
  /*! Indicates a connection to inverted Pair C.*/
 AQ_API_PS_PairC_Inverted,   
  /*! Indicates a connection to Pair D.*/
 AQ_API_PS_PairD,   
  /*! Indicates a connection to inverted Pair D.*/
 AQ_API_PS_PairD_Inverted   
} AQ_API_PairStatus;   

/*! This enumeration is used to report what the current connection
    state an Aquantia PHY is in.*/
typedef enum    
{    
  /*! This indicates that the target Aquantia PHY is in the process of
      performing a reset. This may be triggered by either a power-
      supply fluctuation event, a soft-reset event, a hard-reset
      event, or by pulling the Reset* pin on the Aquantia PHY low.*/
 AQ_API_ConnS_Reset,   
  /*! This indicates that the target Aquantia PHY's processor is
      stalled, so it is incapable of operation. This state occurs when
      the target Aquantia PHY is operating in boot-load mode, and is
      waiting to have an image loaded into its IRAM and DRAM.*/
 AQ_API_ConnS_Stall,   
  /*! This indicates that the target Aquantia PHY is in an inactive
      state and is not connected to a far-end device, nor is it
      attempting to. This occurs when the Aquantia PHY is in low-power
      mode, high-impedance mode, is advertising no connection
      capability, or being reset.*/
 AQ_API_ConnS_Inactive,   
  /*! This indicates that the target Aquantia PHY is in the process of
      performing cable diagnostics during the MDI / MDI-X phase of the
      link connection.*/
 AQ_API_ConnS_CableDiagnostics,   
  /*! This indicates that the target Aquantia PHY is in the process of
      attempting to connect with 10G as the highest advertised rate.*/
 AQ_API_ConnS_10G_Autoneg,   
  /*! This indicates that the target Aquantia PHY is in the process of
      attempting to connect with 5G as the highest advertised rate.
      Compatibility: 28nm PHYs only.*/
 AQ_API_ConnS_5G_Autoneg,   
  /*! This indicates that the target Aquantia PHY is in the process of
      attempting to connect with 2.5G as the highest advertised rate.
      Compatibility: 28nm PHYs only.*/
 AQ_API_ConnS_2_5G_Autoneg,   
  /*! This indicates that the target Aquantia PHY is in the process of
      attempting to connect with 1G as the highest advertised rate.*/
 AQ_API_ConnS_1G_Autoneg,   
  /*! This indicates that the target Aquantia PHY is in the process of
      attempting to connect with 100M as the highest advertised
      rate.*/
 AQ_API_ConnS_100M_Autoneg,   
  /*! This indicates that the target Aquantia PHY is attempting to
      connect with the far-end device at 10G, and is in the training
      phase of the process.*/
 AQ_API_ConnS_10G_Training,   
  /*! This indicates that the target Aquantia PHY is attempting to
      connect with the far-end device at 5G, and is in the training
      phase of the process.
      Compatibility: 28nm PHYs only.*/
 AQ_API_ConnS_5G_Training,   
  /*! This indicates that the target Aquantia PHY is attempting to
      connect with the far-end device at 2.5G, and is in the training
      phase of the process.
      Compatibility: 28nm PHYs only.*/
 AQ_API_ConnS_2_5G_Training,   
  /*! This indicates that the target Aquantia PHY is attempting to
      connect with the far-end device at 1G, and is in the training
      phase of the process.*/
 AQ_API_ConnS_1G_Training,   
  /*! This indicates that the target Aquantia PHY is attempting to
      connect with the far-end device at 100M, and is initializing the
      1G/100M core.*/
 AQ_API_ConnS_100M_Training,   
  /*! This indicates that the target Aquantia PHY is connected to a
      far-end device at 10G.*/
 AQ_API_ConnS_10G_Connected,   
  /*! This indicates that the target Aquantia PHY is connected to a
      far-end device at 5G.
      Compatibility: 28nm PHYs only.*/
 AQ_API_ConnS_5G_Connected,   
  /*! This indicates that the target Aquantia PHY is connected to a
      far-end device at 2.5G.
      Compatibility: 28nm PHYs only.*/
 AQ_API_ConnS_2_5G_Connected,   
  /*! This indicates that the target Aquantia PHY is connected to a
      far-end device at 1G.*/
 AQ_API_ConnS_1G_Connected,   
  /*! This indicates that the target Aquantia PHY is connected to a
      far-end device at 1G and Wake On LAN is enabled.*/
 AQ_API_ConnS_1G_WoL_Connected,   
  /*! This indicates that the target Aquantia PHY is connected to a
      far-end device at 100M.*/
 AQ_API_ConnS_100M_Connected,   
  /*! This indicates that the target Aquantia PHY is connected to a
      far-end device at 100M and Wake On LAN is enabled.*/
 AQ_API_ConnS_100M_WoL_Connected,   
  /*! This indicates that the target Aquantia PHY is in the 2 second
      time-out in order to complete link break.*/
 AQ_API_ConnS_LinkBreak,   
  /*! This indicates that the target Aquantia PHY is in a test mode.*/
 AQ_API_ConnS_TestMode,   
  /*! This indicates that the target Aquantia PHY is in a loopback
      mode.*/
 AQ_API_ConnS_LoopbackMode,   
  /*! This indicates that the target Aquantia PHY is in a low power
      mode.*/
 AQ_API_ConnS_LowPowerMode,   
  /*! This state typically indicates that the target Aquantia PHY is
      not functioning properly (i.e. not powered on, etc.).*/
 AQ_API_ConnS_Invalid   
} AQ_API_ConnectionState;   

/*! This enumeration is used to report the current MDI / MDI-X state
    an Aquantia PHY.*/
typedef enum    
{    
  /*! This indicates that the target Aquantia PHY has not resolved the
      MDI / MDI-X state.*/
 AQ_API_MS_None,   
  /*! This indicates that the target Aquantia PHY has resolved the MDI
      / MDI-X state as MDI.*/
 AQ_API_MS_MDI,   
  /*! This indicates that the target Aquantia PHY has resolved the MDI
      / MDI-X state as MDI-X.*/
 AQ_API_MS_MDI_X   
} AQ_API_MDI_State;   

/*! Enumerates the system interface's various operating modes.*/
typedef enum    
{    
  /*! XFI mode.*/
 AQ_API_SIOM_XFI,   
  /*! Backplane KR mode.*/
 AQ_API_SIOM_BackplaneKR,   
  /*! Backplane KX mode.*/
 AQ_API_SIOM_BackplaneKX,   
  /*! XAUI mode.*/
 AQ_API_SIOM_XAUI,   
  /*! XAUI Pause Based mode.*/
 AQ_API_SIOM_XAUI_PauseBased,   
  /*! RXAUI mode.*/
 AQ_API_SIOM_RXAUI,   
  /*! SGMII mode.*/
 AQ_API_SIOM_SGMII,   
  /*! USXGMII mode.*/
 AQ_API_SIOM_USXGMII,   
  /*! MAC mode.*/
 AQ_API_SIOM_MAC,   
  /*! System interface is off.*/
 AQ_API_SIOM_OFF,   
  /*! Unrecognized system interface mode.*/
 AQ_API_SIOM_Other   
} AQ_API_SysIntfOpMode;   

/*! Enumerates the system interface's various data rates.*/
typedef enum    
{    
  /*! 10M data rate.*/
 AQ_API_SIR_10M,   
  /*! 100M data rate.*/
 AQ_API_SIR_100M,   
  /*! 1G data rate.*/
 AQ_API_SIR_1G,   
  /*! 10G data rate.*/
 AQ_API_SIR_10G,   
  /*! 2.5G data rate.*/
 AQ_API_SIR_2_5G,   
  /*! 5G data rate.*/
 AQ_API_SIR_5G,   
  /*! System interface is powered down.*/
 AQ_API_SIR_PowerDown,   
  /*! Unrecognized system interface rate.*/
 AQ_API_SIR_Other   
} AQ_API_SysIntfRate;   

/*! Describes the system interface's autonegotiation completion
    status.*/
typedef enum    
{    
  /*! Autonegotiation not applicable based on the current system
      interface operating mode.*/
 AQ_API_SIAS_NA,   
  /*! Autonegotiation has not been completed.*/
 AQ_API_SIAS_NotComplete,   
  /*! Autonegotiation has been completed.*/
 AQ_API_SIAS_Complete,   
  /*! Unrecognized system interface autonegotiation completion
      status.*/
 AQ_API_SIAS_Other   
} AQ_API_SysIntfAutonegStatus;   

/*! This structure is used to convey the connection status an Aquantia
    PHY.*/
typedef struct    
{    
 /*MDI connection state*/   
  /*! If true, a far-end Ethernet device exists, as valid link pulses
      have been detected in the most recent autonegotiation session,
      or a valid Ethernet connection has been established. If false,
      no connection is established, and the most recent attempt at
      autonegotiation failed to detect any valid link pulses. This
      field is duplicated for convenience in
      AQ_API_LinkPartnerStatus.*/
 AQ_boolean  farEndDeviceExists; 
  /*! If true, energy greater than -15 dBm is present on the line.
      This may or may not be a valid Ethernet signal, depending on the
      connection status.*/
 AQ_boolean  energyOnLine; 
  /*! The number of autonegotiation attempts that have been made since
      power-up or a valid connection was lost. If a connection is
      established, this is the number of autonegotiation attempts that
      were made before the link was established. If a connection is
      not established, this is the number of autonegotiation attempts
      that have been tried so far. Upon reaching saturation, the value
      wraps back to zero.*/
 uint16_t  numberOfConnectionAttempts; 
 /*state*/   
  /*! The current state of the Aquantia PHY.*/
 AQ_API_ConnectionState   state;
  /*! If true, the connection is a duplex connection.Otherwise the
      connection is simplex (or non-existent).*/
 AQ_boolean   duplex;
  /*! The current MDI / MDI-X state of the connection.*/
 AQ_API_MDI_State   MDI_MDI_X;
  /*! The result of the master / slave resolution from autonegotiation
      process.*/
 AQ_API_MasterSlaveStatus   masterSlaveStatus;
 /*system interface state*/   
  /*! Identifies the current operating mode of the system interface.
      Compatibility: 28nm PHYs only.*/
 AQ_API_SysIntfOpMode   sysIntfCurrentMode;
  /*! The current data rate of system interface.
      Compatibility: 28nm PHYs only.*/
 AQ_API_SysIntfRate   sysIntfCurrentRate;
  /*! If true, system interface is ready to transmit.
      Compatibility: 28nm PHYs only.*/
 AQ_boolean   txReady;
  /*! If true, system interface is linked and ready to receive.
      Compatibility: 28nm PHYs only.*/
 AQ_boolean   rxLinkUp;
  /*! Reports the completion progress of the system interface's
      autonegotiation.
      Compatibility: 28nm PHYs only.*/
 AQ_API_SysIntfAutonegStatus   sysIntfAutonegStatus;
} AQ_API_ConnectionStatus;    

/*! This structure is used to convey the 10G connection status an
    Aquantia PHY.*/
typedef struct    
{    
 /*connection state*/   
  /*! If true, the target Aquantia PHY is connected to a far end
      device at 10G. If this bit is not set, none of the other
      information in this structure is valid.*/
 AQ_boolean  connected; 
 /*errors*/   
  /*! The number of 10GBASE-T transmission frames with uncorrectable
      LDPC errors seen since the last read.*/
 uint32_t  erroredLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames with no LDPC errors,
      but failing CRC-8 frame checks seen since the last read.*/
 uint32_t  erroredCRC_Frames; 
 /*LDPC*/   
  /*! The number of 10GBASE-T transmission frames that took only 1
      LDPC iteration to correct since the last read.*/
 uint32_t  Iteration1_CorrectedLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames that took 2 LDPC
      iterations to correct since the last read.*/
 uint32_t  Iteration2_CorrectedLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames that took 3 LDPC
      iterations to correct since the last read.*/
 uint32_t  Iteration3_CorrectedLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames that took 4 LDPC
      iterations to correct since the last read.*/
 uint32_t  Iteration4_CorrectedLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames that took 5 LDPC
      iterations to correct since the last read.*/
 uint32_t  Iteration5_CorrectedLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames that took 6 LDPC
      iterations to correct since the last read.*/
 uint16_t  Iteration6_CorrectedLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames that took 7 LDPC
      iterations to correct since the last read.*/
 uint16_t  Iteration7_CorrectedLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames that took 8 LDPC
      iterations to correct since the last read.*/
 uint16_t  Iteration8_CorrectedLDPC_Frames; 
  /*! The total number of good 10GBASE-T transmission frames seen
      since the last read.*/
 uint32_t  goodLDPC_Frames; 
  /*! The average number of LDPC iterations required to correct a
      10GBASE-T transmission frame (in tenths of an iteration) since
      the last read.*/
 uint8_t  averageNumberOfIterations; 
 /*transmit power*/   
  /*! The transmit power of the target Aquantia PHY in tenths of a
      dBm, as reported from either the 10G power backoff from a
      nominal +4.2 dBm, or operating rate below 10G. LSB = 1/10 dBm.*/
 int16_t   transmitPower;
  /*! The transmit power of the target Aquantia PHY's link partner in
      tenths of a dBm, as reported from either the 10G power backoff
      from a nominal +4.2 dBm, or operating rate below 10G. LSB = 1/10
      dBm.*/
 int16_t   linkPartnerTransmitPower;
 /*10G network interface frames*/   
  /*! The number of good Ethernet frames passing through the network
      interface since the last read. Counts frames SENT TOWARDS the
      network side.*/
 uint32_t   netIntfGoodTxEthernetFrames;
  /*! The number of good Ethernet frames passing through the network
      interface since the last read. Counts frames RECEIVED FROM the
      network side.*/
 uint32_t   netIntfGoodRxEthernetFrames;
  /*! The number of bad Ethernet frames (i.e. bad FCS) passing through
      the network interface since the last read. Counts frames SENT
      TOWARDS the network side.*/
 uint32_t   netIntfBadTxEthernetFrames;
  /*! The number of bad Ethernet frames (i.e. bad FCS) passing through
      the network interface since the last read. Counts frames
      RECEIVED FROM the network side.*/
 uint32_t   netIntfBadRxEthernetFrames;
 /*10G system interface frames*/   
  /*! The number of good Ethernet frames passing through the system
      interface since the last read. Counts frames RECEIVED FROM the
      system side.*/
 uint32_t   sysIntfGoodTxEthernetFrames;
  /*! The number of good Ethernet frames passing through the system
      interface since the last read. Counts frames SENT TOWARDS the
      system side.*/
 uint32_t   sysIntfGoodRxEthernetFrames;
  /*! The number of bad Ethernet frames (i.e. bad FCS) passing through
      the system interface since the last read. Counts frames RECEIVED
      FROM the system side.*/
 uint32_t   sysIntfBadTxEthernetFrames;
  /*! The number of bad Ethernet frames (i.e. bad FCS) passing through
      the system interface since the last read. Counts frames SENT
      TOWARDS the system side.*/
 uint32_t   sysIntfBadRxEthernetFrames;
 /*noise environment*/   
  /*! The excess SNR that is enjoyed by the channel, over and above
      the minimum SNR required to operate at a BER of 10-12. It is
      reported with 0.1 dB of resolution to an accuracy of 0.5 dB
      within the range of -12.7 dB to 12.7 dB. The number is in tenths
      of a dB, so the LSB = 1/10 dB.*/
 uint16_t   pairA_OperatingMargin;
  /*! The excess SNR that is enjoyed by the channel, over and above
      the minimum SNR required to operate at a BER of 10-12. It is
      reported with 0.1 dB of resolution to an accuracy of 0.5 dB
      within the range of -12.7 dB to 12.7 dB. The number is in tenths
      of a dB, so the LSB = 1/10 dB.*/
 uint16_t   pairB_OperatingMargin;
  /*! The excess SNR that is enjoyed by the channel, over and above
      the minimum SNR required to operate at a BER of 10-12. It is
      reported with 0.1 dB of resolution to an accuracy of 0.5 dB
      within the range of -12.7 dB to 12.7 dB. The number is in tenths
      of a dB, so the LSB = 1/10 dB.*/
 uint16_t   pairC_OperatingMargin;
  /*! The excess SNR that is enjoyed by the channel, over and above
      the minimum SNR required to operate at a BER of 10-12. It is
      reported with 0.1 dB of resolution to an accuracy of 0.5 dB
      within the range of -12.7 dB to 12.7 dB. The number is in tenths
      of a dB, so the LSB = 1/10 dB.*/
 uint16_t   pairD_OperatingMargin;
 /*connectivity*/   
  /*! The physical cable connectivity for Pair A.*/
 AQ_API_PairStatus   pairA_LogicalConnectivity;
  /*! The physical cable connectivity for Pair B.*/
 AQ_API_PairStatus   pairB_LogicalConnectivity;
  /*! The physical cable connectivity for Pair C.*/
 AQ_API_PairStatus   pairC_LogicalConnectivity;
  /*! The physical cable connectivity for Pair D.*/
 AQ_API_PairStatus   pairD_LogicalConnectivity;
 /*skew*/   
  /*! The physical delay skew of Pair B relative to Pair A in
      nanoseconds, with an absolute accuracy of 2.5 ns.*/
 int16_t  pairB_RelativeSkew; 
  /*! The physical delay skew of Pair C relative to Pair A in
      nanoseconds, with an absolute accuracy of 2.5 ns.*/
 int16_t  pairC_RelativeSkew; 
  /*! The physical delay skew of Pair D relative to Pair A in
      nanoseconds, with an absolute accuracy of 2.5 ns.*/
 int16_t  pairD_RelativeSkew; 
} AQ_API_10G_ConnectionStatus;    

/*! This structure is used to convey the 1G/100M connection status an
    Aquantia PHY.*/
typedef struct    
{    
 /*connection state*/   
  /*! If true, the target Aquantia PHY is connected to a far end
      device at 1G or 100M. If this bit is not set, none of the other
      information in this structure is valid.*/
 AQ_boolean  connected; 
 /*100M / 1G frames*/   
  /*! The number of good Ethernet frames passing through the system
      interface since the last read. Counts frames RECEIVED FROM the
      system side.*/
 uint32_t   sysIntfGoodTxEthernetFrames;
  /*! The number of good Ethernet frames passing through the system
      interface since the last read. Counts frames SENT TOWARDS the
      system side.*/
 uint32_t   sysIntfGoodRxEthernetFrames;
  /*! The number of bad Ethernet frames (i.e. bad FCS) passing through
      the system interface since the last read. Counts frames RECEIVED
      FROM the system side.*/
 uint32_t   sysIntfBadTxEthernetFrames;
  /*! The number of bad Ethernet frames (i.e. bad FCS) passing through
      the system interface since the last read. Counts frames SENT
      TOWARDS the system side.*/
 uint32_t   sysIntfBadRxEthernetFrames;
 /*SGMII errors*/   
  /*! The number of false carrier events received by the Aquantia PHY
      on the SGMII interface since the last read.*/
 uint16_t   sgmiiRxFalseCarrierEvents;
  /*! The number of collision events seen by the Aquantia PHY on the
      SGMII interface since the last read.*/
 uint16_t   sgmiiCollisionEvents;
 /*line errors*/   
  /*! The number of false carrier events received by the Aquantia PHY
      on the line since the last read.*/
 uint16_t   rxFalseCarrierEvents;
  /*! The number of collision events received by the Aquantia PHY on
      the line since the last read.*/
 uint16_t   collisionEvents;
  /*! The number of frame alignment errors (i.e. misaligned nibble)
      received by the Aquantia PHY on the line since the last read.*/
 uint32_t   frameAlignmentEvents;
  /*! The number of runt frames (i.e. frames less than 64 bytes long)
      received by the Aquantia PHY on the line since the last read.*/
 uint32_t   runtFrameEvents;
} AQ_API_100M_1G_ConnectionStatus;    

/*! This function reads the current connection status of an Aquantia
    PHY. The user must provide a pointer to an AQ_API_ConnectionStatus
    structure for this function to return the results into.*/
AQ_Retcode   AQ_API_GetConnectionStatus 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! The connection status of the target Aquantia PHY.*/
 AQ_API_ConnectionStatus*   connectionStatus
);    

/*! This function reads the current connection status of an Aquantia
    PHY. The user must provide a pointer to an
    AQ_API_10G_ConnectionStatus structure for this function to return
    the results into.*/
AQ_Retcode   AQ_API_Get10G_ConnectionStatus 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! The 10G connection status of the target Aquantia PHY.*/
 AQ_API_10G_ConnectionStatus*   connectionStatus
);    

/*! This function reads the current connection status of an Aquantia
    PHY. The user must provide a pointer to an
    AQ_API_100M_1G_ConnectionStatus structure for this function to
    return the results into.*/
AQ_Retcode   AQ_API_Get100M_1G_ConnectionStatus 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! The 1G/100M connection status of the target Aquantia PHY.*/
 AQ_API_100M_1G_ConnectionStatus*   connectionStatus
);    

#define AQ_API_LDPC_ITERATION_MAX 10    
#define AQ_API_PAIR_COUNT 4    
/*! This structure is used to convey the Tx Phase apply results of an
    Aquantia PHY.*/
typedef struct    
{    
 /*connection state*/   
  /*! Result code.*/
 AQ_Retcode   resultCode;
  /*! Tx Phase.*/
 uint16_t   txPhase;
  /*! Identifies whether the Aquantia PHY was configured as the master
      or as the slave during autonegotiation.*/
 AQ_API_MasterSlaveStatus   masterSlaveStatus;
  /*! If true, the target Aquantia PHY is connected to a far end
      device at 10G. If this bit is not set, none of the other
      information in this structure is valid.*/
 AQ_boolean   connected;
  /*! IThe estimated length of cable in meters.*/
 uint16_t   cableLength;
 /*LDPC*/   
  /*! The number of 10GBASE-T transmission frames with uncorrectable
      LDPC errors seen since the last read.*/
 uint32_t  erroredLDPC_Frames; 
  /*! The number of 10GBASE-T transmission frames with no LDPC errors,
      but failing CRC-8 frame checks seen since the last read.*/
 uint32_t  erroredCRC_Frames; 
  /*! Average LDPC iteration (divide the value by 4096 to obtain
      floating point value).*/
 uint16_t  averageLDPC_IterationsCount; 
  /*! The number of 10GBASE-T transmission frames that took (i + 1)
      LDPC iterations to correct since the last read.*/
 uint32_t  IterationN_CorrectedLDPC_Frames[AQ_API_LDPC_ITERATION_MAX]; 
 /*SNR*/   
  /*! Channel N operating margin.*/
 int16_t  SNR_Avg[AQ_API_PAIR_COUNT]; 
  /*! Channel N minimum margin.*/
 int16_t  SNR_Min[AQ_API_PAIR_COUNT]; 
} AQ_API_TxPhaseResults;    

#define AQ_API_TXPHASE_COUNT 8    
#define AQ_API_TXPHASE_ITERATION_COUNT 10    
/*! This function tries 8 different versions of Tx Phase and returns
    the results.
    Compatibility: 28nm PHYs only.
    Return codes:
    AQ_RET_ERROR: Invalid device or iteration count.
    AQ_RET_TXPHASE_PROV_CHECK_FAILED: Failed to check provisioning
    table size or not enough space in provosioning table to append Tx
    Phase.
    AQ_RET_TXPHASE_SANITYCHECK_FAILED: Link is not up in 10G or has
    less than 90m cable connected.
    AQ_RET_TXPHASE_PROV_PREPARE_FAILED: Failed to prepare provisioning
    table to append Tx Phase.*/
AQ_Retcode   AQ_API_GetTxPhaseStatistics 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! Consider link partner as one on the same chip as the target
      port.*/
 AQ_boolean   commonClock,
  /*! The number of iterations for each Tx Phase not more than
      AQ_API_TXPHASE_ITERATION_COUNT.*/
 int32_t   iterationCount,
  /*! The obtained statistics for each of 8 Tx Phases repeated
      iterationCount times.*/
 AQ_API_TxPhaseResults   txPhaseResults[AQ_API_TXPHASE_COUNT][AQ_API_TXPHASE_ITERATION_COUNT]
);    

/*@}*/


/*******************************************************************
                        Autonegotiation
*******************************************************************/

/*! \defgroup autonegotiation Autonegotiation
The Aquantia PHY is designed to support both 10GBASE-T, 1000BASE-T, and
legacy 100BASE-TX autonegotiation. This is to support forward compatibility
with future Aquantia devices that will support lower rates.l */
/*@{*/


/*! This enumeration is used to control setting whether an Aquantia
    PHY is the master of the slave in the autonegotiation.*/
typedef enum    
{    
  /*! Identifies that the Aquantia PHY should be automatically
      configured to be either the master or the slave, based on the
      results of the autonegotiation.*/
 AQ_API_AN_Automatic,   
  /*! Identifies that the Aquantia PHY should be configured to be the
      master during autonegotiation.*/
 AQ_API_AN_Master,   
  /*! Identifies that the Aquantia PHY should be configured to be the
      slave during autonegotiation.*/
 AQ_API_AN_Slave   
} AQ_API_MasterSlaveControl;   

/*! This enumeration is used to specify the port type of an Aquantia
    PHY during autonegotiation.*/
typedef enum    
{    
  /*! Identifies that the Aquantia PHY is a single port device.*/
 AQ_API_AN_SinglePort,   
  /*! Identifies that the Aquantia PHY is a multi-port device.*/
 AQ_API_AN_MultiPort   
} AQ_API_PortType;   

/*! This enumeration is used to control setting whether an Aquantia
    PHY is the master of the slave in the autonegotiation.*/
typedef enum    
{    
  /*! Identifies that the Aquantia PHY should enable automatic MDI /
      MDI-X operation.*/
 AQ_API_MDC_Automatic,   
  /*! Identifies that the Aquantia PHY should be hard configured
      during autonegotiation as MDI.*/
 AQ_API_MDC_MDI,   
  /*! Identifies that the Aquantia PHY should be hard configured
      during autonegotiation as MDI-X.*/
 AQ_API_MDC_MDI_X   
} AQ_API_MDI_MDI_X_Control;   

/*! This enumeration is used to control setting whether an Aquantia
    PHY performs autonegotiation, or is manually forced to connect at
    a specified rate.*/
typedef enum    
{    
  /*! Identifies that the Aquantia PHY should perform
      autonegotiation.*/
 AQ_API_ForceConnRate_Autonegotiate,   
  /*! Identifies that the Aquantia PHY should connect at 100M, without
      performing autonegotiation.*/
 AQ_API_ForceConnRate_100M,   
  /*! Unrecognized mode- do not use.*/
 AQ_API_ForceConnRate_Other   
} AQ_API_ForceConnRate;   

/*! This structure is used to control IEEE 802.3bz capabilities which
    Aquantia PHY will advertise during autonegotiation and to report
    the capabilities of an Aquantia PHY's link partner.*/
typedef struct    
{    
  /*! If true, the Aquantia PHY is 2.5GBASE-T capable.*/
 AQ_boolean  _2_5G; 
  /*! If true, the Aquantia PHY is 5GBASE-T capable.*/
 AQ_boolean  _5G; 
  /*! If true, the Aquantia PHY 2.5GBASE-T has EEE capability.*/
 AQ_boolean  _2_5G_EEE; 
  /*! If true, the Aquantia PHY 5GBASE-T has EEE capability.*/
 AQ_boolean  _5G_EEE; 
  /*! If true, the Aquantia PHY is 2.5GBASE-T fast retrain capable.*/
 AQ_boolean  _2_5G_fastRetrain; 
  /*! If true, the Aquantia PHY is 5GBASE-T fast retrain capable.*/
 AQ_boolean  _5G_fastRetrain; 
  /*! If true, the Aquantia PHY requests to reset THP during fast
      retrain for 2.5GBASE-T.*/
 AQ_boolean  _2_5G_THP_BypassRequest; 
  /*! If true, the Aquantia PHY requests to reset THP during fast
      retrain for 5GBASE-T.*/
 AQ_boolean  _5G_THP_BypassRequest; 
} AQ_API_bzCapabilities;   

/*! This structure is used by the API to control how the Aquantia PHY
    connects with a link partner.*/
typedef struct    
{    
 /*autonegotiation*/   
  /*! If true, the target Aquantia PHY will advertise 10GBASE-T full
      duplex (only option) capabilities during autonegotiation.*/
 AQ_boolean  advertise10GBASE_T; 
  /*! If true, the target Aquantia PHY will advertise short reach
      capabilities in the 10GBASE-T extended capabilities word.*/
 AQ_boolean  shortReach; 
  /*! IEEE 802.3bz capabilities which target Aquantia PHY will
      advertise.
      Compatibility: 28nm PHYs only.*/
 AQ_API_bzCapabilities  bzCapabilities; 
  /*! If true, the target Aquantia PHY will advertise AQRate 5G
      capabilities during autonegotiation.
      Compatibility: 28nm PHYs only.*/
 AQ_boolean  advertise5G; 
  /*! If true, the target Aquantia PHY will advertise AQRate 2.5G
      capabilities during autonegotiation.
      Compatibility: 28nm PHYs only.*/
 AQ_boolean  advertise2_5G; 
  /*! If true, the target Aquantia PHY will advertise 1000BASE-T full
      duplex capabilities during autonegotiation.*/
 AQ_boolean  advertise1000BASE_T_FullDuplex; 
  /*! If true, the target Aquantia PHY will advertise 1000BASE-T half
      duplex capabilities during autonegotiation.*/
 AQ_boolean  advertise1000BASE_T_HalfDuplex; 
  /*! If true, the target Aquantia PHY will advertise 100BASE-TX full
      duplex capabilities during autonegotiation.*/
 AQ_boolean  advertise100BASE_TX_FullDuplex; 
  /*! If true, the target Aquantia PHY will advertise 100BASE-TX half-
      duplex capabilities during autonegotiation.*/
 AQ_boolean  advertise100BASE_TX_HalfDuplex; 
  /*! If true, the target Aquantia PHY will advertise 10BASE-T full
      duplex capabilities during autonegotiation.*/
 AQ_boolean  advertise10BASE_T_FullDuplex; 
  /*! If true, the target Aquantia PHY will advertise 10BASE-T half
      duplex capabilities during autonegotiation.*/
 AQ_boolean  advertise10BASE_T_HalfDuplex; 
  /*! If true, the target Aquantia PHY will advertise symmetric PAUSE
      capabilities during autonegotiation.*/
 AQ_boolean  advertiseSymmetricPAUSE; 
  /*! If true, the target Aquantia PHY will advertise asymmetric PAUSE
      capabilities during autonegotiation.*/
 AQ_boolean  advertiseAsymmetricPAUSE; 
  /*! Setting this enables the Aquantia PHY to perform automatic
      downshifting to a lower rate if it cannot connect at the highest
      advertised rate. It does this by disabling the highest
      advertised rate prior to the next autonegotiation attempt after
      automaticDownshiftRetryAttempts connect attempts.*/
 AQ_boolean  enableAutomaticDownshift; 
  /*! The number of attempts the Aquantia PHY will attempt before
      disabling the highest advertised rate and attempting to connect
      at the next highest rate available.*/
 uint16_t  automaticDownshiftRetryAttempts; 
  /*! The master / slave control settings for an Aquantia PHY during
      autonegotiation.*/
 AQ_API_MasterSlaveControl   masterSlaveControl;
  /*! The port type of the Aquantia PHY to be used during
      autonegotiation.*/
 AQ_API_PortType   portType;
  /*! The MDI / MDI-X control settings for an Aquantia PHY during
      autonegotiation.*/
 AQ_API_MDI_MDI_X_Control   MDI_MDI_X_Control;
  /*! Specifies whether or not the PHY will perform autonegotiation.*/
 AQ_API_ForceConnRate   forceConnRate;
} AQ_API_AutonegotiationControl;    

/*! This function gets the autonegotiation control settings of an
    Aquantia PHY. The user must provide a pointer to an
    AQ_API_AutonegotiationControl structure that will be used to store
    the autonegotiation settings.*/
AQ_Retcode   AQ_API_GetAutonegotiationControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The autonegotiation control settings for an Aquantia PHY.*/
 AQ_API_AutonegotiationControl*   autonegotiationControl
);    

/*! This function writes the autonegotiation control settings to an
    Aquantia PHY. The user must provide a pointer to an
    AQ_API_AutonegotiationControl structure that contains the desired
    autonegotiation settings.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.*/
AQ_Retcode   AQ_API_SetAutonegotiationControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The autonegotiation control settings for an Aquantia PHY.*/
 AQ_API_AutonegotiationControl*   autonegotiationControl
);    

/*@}*/


/*******************************************************************
                        Link Partner Status
*******************************************************************/

/*! \defgroup linkPartnerStatus Link Partner Status
The Aquantia PHY is capable of determining a great deal of information
about the far-end link partner by observing its behavior and responses
during autonegotiation. The following structures and functions are designed
to present that status information. */
/*@{*/


/*! This structure is used by the API to report the status of an
    Aquantia PHY's link partner. The information in this structure is
    only valid if the far-end device exists and autonegotiation has
    been completed.*/
typedef struct    
{    
 /*knowledge about far-end device*/   
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 10G capability.*/
 AQ_boolean  _10GBASE_T; 
  /*! If farEndDeviceExists is true, this field reports IEEE 802.3bz
      capabilities which the far-end device is advertising.
      Compatibility: 28nm PHYs only.*/
 AQ_API_bzCapabilities  bzCapabilities; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 5G capability.
      Compatibility: 28nm PHYs only.*/
 AQ_boolean  _5G; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 2.5G capability.
      Compatibility: 28nm PHYs only.*/
 AQ_boolean  _2_5G; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 1G full-duplex capability.*/
 AQ_boolean  _1000BASE_T_FullDuplex; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 1G half-duplex capability.*/
 AQ_boolean  _1000BASE_T_HalfDuplex; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 100M full-duplex capability.*/
 AQ_boolean  _100BASE_TX_FullDuplex; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 100M half-duplex capability.*/
 AQ_boolean  _100BASE_TX_HalfDuplex; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 10M full-duplex capability.*/
 AQ_boolean  _10BASE_T_FullDuplex; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device is advertising 10M half-duplex capability.*/
 AQ_boolean  _10BASE_T_HalfDuplex; 
  /*! If farEndDeviceExists is true, and this field is set, this field
      indicates that the far-end device is operating in short-reach
      mode. This is the 10GBASE-T defined "short-reach" bit.*/
 AQ_boolean  shortReach; 
  /*! If farEndDeviceExists is true, and this field is set, the far-
      end device has symmetric PAUSE capabilities.*/
 AQ_boolean  symmetricPAUSE; 
  /*! If farEndDeviceExists is true, and this field is set, this field
      indicates that the far-end device has asymmetric PAUSE
      capabilities.*/
 AQ_boolean  asymmetricPAUSE; 
 /*remote identification*/   
  /*! If true, the far-end device is an Aquantia device, and its
      information is listed below. If false, the far-end device is not
      an Aquantia part, and the information listed below will be all
      zeroes.*/
 AQ_boolean  aquantiaDevice; 
  /*! The six bit chip ID of the remote PHY, read from the Device ID.
      This should be ignored, unless the remote PHY is an AQ1002
      Aquantia PHY.*/
 uint8_t  chipID; 
  /*! The four bit chip version of the remote PHY, read from the
      Device ID. This should be ignored, unless the remote PHY is an
      AQ1002 Aquantia PHY.*/
 uint8_t  chipVersion; 
  /*! The major firmware version of the remote PHY.*/
 uint8_t  firmwareVersionMajor; 
  /*! The minor firmware version of the remote PHY.*/
 uint8_t  firmwareVersionMinor; 
} AQ_API_LinkPartnerStatus;    

/*! This function reads the link partner status information from an
    Aquantia PHY. The user must provide a pointer to an
    AQ_API_LinkPartnerStatus structure for this function to return the
    results into.*/
AQ_Retcode   AQ_API_GetLinkPartnerStatus 
(    
  /*! The target PHY port.*/
 AQ_API_Port*   port,
  /*! The link partner status of the far-end device.*/
 AQ_API_LinkPartnerStatus*   linkPartnerStatus
);    

/*@}*/


/*******************************************************************
                        Alarms
*******************************************************************/

/*! \defgroup alarms Alarms
It is assumed that the system designer will connect the interrupts from the
individual PHYs into the board processor's interrupt structure.
Consequently the board processor will be independently notified of an
interrupt within an Aquantia PHY, and then will be able to read it via the
AQ_API_GetAlarmStatus() function, which will return the alarms via the
user's instantiation of AQ_API_AlarmStatus. Masking of alarms is done via
the structures Alarm Control. */
/*@{*/


/*! This structure is used by the API to report alarm status for the
    Autonegotiation MMD within an Aquantia PHY. The alarms that are
    not represented here are:
    1) The page received interrupts in 7.1 and 7.EC01, as these are
    primarily for autonegotiation debug, and it is anticipated that
    these will never be used in normal operation, as autonegotiation
    will always be handled by the Aquantia PHY.
    2) The link status alarm in 7.1 is not represented here, as it is
    a duplicate of the PMA link status bit.
    3) The reset complete alarm, as it is anticipated that only the
    global reset complete is of interest.*/
typedef struct    
{    
 /*alarms*/   
   /*! If true, the target Aquantia PHY has experienced loss of
       link.*/
 AQ_boolean  linkFail; 
   /*! If true, the target Aquantia PHY has received a remote fault
       indication from the link partner PHY.*/
 AQ_boolean  remoteFault; 
   /*! If true, the target Aquantia PHY has experienced a master slave
       configuration fault.*/
 AQ_boolean  masterSlaveConfigurationFault; 
   /*! If true, the target Aquantia PHY has completed autonegotiation
       with the far-end PHY and has not been able to negotiate a
       mutually supported link rate.*/
 AQ_boolean  autonegotiationCompletedForNonSupportedRate; 
   /*! If true, the target Aquantia PHY has completed autonegotiation
       with the far-end PHY and has negotiated a mutually supported
       link rate.*/
 AQ_boolean  autonegotiationCompletedForSupportedRate; 
   /*! If true, the target Aquantia PHY has automatically downshifted
       to a lower advertised rate. This occurs when automatic
       downshifting is enabled, and the PHY has not been able to
       connect within the allowed number of attempts.*/
 AQ_boolean  automaticDownshift; 
   /*! If true, the target Aquantia PHY has detected the presence of a
       legacy 10BASE-T device on the line.*/
 AQ_boolean  _10BASE_T_Detect; 
   /*! If true, the target Aquantia PHY has received a wake-up
       frame.*/
 AQ_boolean  wakeUpFrameDetected; 
   /*! If true, the target Aquantia PHY has received a wake-up
       packet.*/
 AQ_boolean  wakeUpPacketDetected; 
   /*! If true, the target Aquantia PHY has established link, or was
       in a linked state and has disconnected.*/
 AQ_boolean  linkConnectOrDisconnect; 
} AQ_API_AutonegotiationAlarms;    

/*! This structure is used by the API to report alarm status for the
    10GBASE-T interface within an Aquantia PHY.*/
typedef struct    
{    
 /*alarms*/   
   /*! If true, the target Aquantia PHY is operating with a BER of
       greater than 10-4.*/
 AQ_boolean  highBER; 
   /*! If true, the target Aquantia PHY has experienced loss of frame
       on the received 10GBASE-T data stream.*/
 AQ_boolean  lossOfBlockLock; 
   /*! If true, the target Aquantia PHY has experienced a CRC error on
       the received 10GBASE-T frame.*/
 AQ_boolean  CRC8_Error; 
   /*! If true, the target Aquantia PHY has received a 10GBASE-T frame
       that contains uncorrectable bit errors.*/
 AQ_boolean  LDPC_Error; 
   /*! If true, the target Aquantia PHY has received a 10GBASE-T frame
       that contains an invalid 65B block.*/
 AQ_boolean  invalid65B_Block; 
   /*! If true, the target Aquantia PHY has experienced loss of
       link.*/
 AQ_boolean  PMA_LinkFail; 
   /*! If true, the target Aquantia PHY has experienced a transmit
       fault in the PMA. This is a hardware fault and should not occur
       under normal operation.*/
 AQ_boolean  PMA_TransmitFault; 
   /*! If true, the target Aquantia PHY has experienced a receive
       fault in the PMA. This is a hardware fault and should not occur
       under normal operation.*/
 AQ_boolean  PMA_ReceiveFault; 
   /*! If true, the target Aquantia PHY PCS has experienced loss of
       link.*/
 AQ_boolean  PCS_LinkFail; 
   /*! If true, the target Aquantia PHY has experienced a transmit
       fault in the PCS. This is a hardware fault and should not occur
       under normal operation.*/
 AQ_boolean  PCS_TransmitFault; 
   /*! If true, the target Aquantia PHY has experienced a receive
       fault in the PCS. This is a hardware fault and should not occur
       under normal operation.*/
 AQ_boolean  PCS_ReceiveFault; 
} AQ_API_10GBASE_T_Alarms;    

/*! This structure is used by the API to report alarm status for the
    SGMII interface within an Aquantia PHY.*/
typedef struct    
{    
 /*alarms*/   
   /*! If true, the target Aquantia PHY has received an invalid code
       on the SGMII receive interface.*/
 AQ_boolean  codeViolationError; 
   /*! If true, the target Aquantia PHY has lost the signal on the
       SGMII receive interface.*/
 AQ_boolean  lossOfSignal; 
   /*! If true, the target Aquantia PHY has received a running
       disparity error on the SGMII receive interface.*/
 AQ_boolean  runningDisparityError; 
} AQ_API_SGMII_Alarms;    

/*! This structure is used by the API to report alarm status for the
    XAUI / RXAUI interface within an Aquantia PHY.*/
typedef struct    
{    
 /*alarms*/   
   /*! If true, the target Aquantia PHY has lost lane alignment on the
       XAUI or RXAUI receive interface.*/
 AQ_boolean  lossOfLaneAlignment; 
   /*! If true, the target Aquantia PHY has lost the signal on the
       corresponding XAUI or RXAUI receive lane.*/
 AQ_boolean  lossOfSignal[4]; 
   /*! If true, the target Aquantia PHY has deleted a sequence ordered
       set on the XAUI receive interface.*/
 AQ_boolean  sequenceOrderedSetDeletion; 
   /*! If true, the target Aquantia PHY has received a code violation
       error on the corresponding XAUI or RXAUI receive lane.*/
 AQ_boolean  codeViolationError[4]; 
   /*! If true, the target Aquantia PHY has received a running
       disparity error on the corresponding XAUI or RXAUI receive
       lane.*/
 AQ_boolean  runningDisparityError[4]; 
   /*! If true, the target Aquantia PHY has experienced a transmit
       fault in the PHY_XS. This is a hardware fault and should not
       occur under normal operation.*/
 AQ_boolean  PHY_XS_TransmitFault; 
   /*! If true, the target Aquantia PHY has experienced a receive
       fault in the PHY_XS. This is a hardware fault and should not
       occur under normal operation.*/
 AQ_boolean  PHY_XS_ReceiveFault; 
} AQ_API_XAUI_Alarms;    

/*! This structure is used by the API to report alarm status for the
    XFI interface within an Aquantia PHY.*/
typedef struct    
{    
 /*alarms*/   
   /*! If true, the XFI interface has received an invalid 66B block.*/
 AQ_boolean  invalid66B_Block; 
   /*! If true, the XFI interface has lost block lock on the 66B
       framer.*/
 AQ_boolean  lossOfBlockLock; 
   /*! If true, the XFI interface is experiencing high BER on the
       received signal.*/
 AQ_boolean  highBer; 
} AQ_API_XFI_Alarms;    

/*! This structure is used by the API to report the status of the
    alarms that apply to the system interface regardless of the
    operating mode.*/
typedef struct    
{    
 /*alarms*/   
   /*! If true, the system interface receive link has gone down.
       Compatibility: 28nm PHYs only.*/
 AQ_boolean  sysIntfRxLinkDown; 
   /*! If true, the system interface receive link has come up.
       Compatibility: 28nm PHYs only.*/
 AQ_boolean  sysIntfRxLinkUp; 
} AQ_API_SERDES_Alarms;    

/*! This structure is used by the API to report alarm status for the
    CRPAT and XAUI or RXAUI PRBS test blocks within an Aquantia PHY.*/
typedef struct    
{    
 /*alarms*/   
   /*! If true, the target Aquantia PHY has experienced loss of
       synchronization on the CRPAT test signal.*/
 AQ_boolean  CRPAT_LossOfSynchronization; 
   /*! If true, the target Aquantia PHY has experienced loss of
       synchronization on PRBS pattern on the corresponding XAUI or
       RXAUI receive lane.*/
 AQ_boolean  XAUI_PRBS_LossOfSynchronization[4]; 
} AQ_API_TestAlarms;    

/*! This structure is used by the API to report alarm status for the
    Global MMD within an Aquantia PHY.*/
typedef struct    
{    
 /*alarms*/   
   /*! If true, the temperature of the target Aquantia PHY has
       exceeded the high temperature failure threshold.*/
 AQ_boolean  highTemperatureFailure; 
   /*! If true, the temperature of the target Aquantia PHY has fallen
       below the low temperature failure threshold.*/
 AQ_boolean  lowTemperatureFailure; 
   /*! If true, the temperature of the target Aquantia PHY has
       exceeded the high temperature warning threshold.*/
 AQ_boolean  highTemperatureWarning; 
   /*! If true, the temperature of the target Aquantia PHY has fallen
       below the low temperature warning threshold.*/
 AQ_boolean  lowTemperatureWarning; 
   /*! If true, the target Aquantia PHY has completed its reset
       sequence.*/
 AQ_boolean  resetComplete; 
   /*! If true, the target Aquantia PHY has changed state as reported
       in AQ_API_ConnectionStatus.*/
 AQ_boolean  stateChange; 
   /*! If true, the target Aquantia PHY has experienced a device
       fault.*/
 AQ_boolean  deviceFault; 
   /*! If true, the target Aquantia PHY has detected the presence of
       an IP phone device.
       Compatibility: 28nm PHYs only.*/
 AQ_boolean  ipPhone; 
   /*! If true, the MDIO command handling buffer has overflowed.*/
 AQ_boolean  MDIOCommandOverflow; 
   /*! If true, an MDIO operation has timed out.*/
 AQ_boolean  MDIOTimeout; 
   /*! If true, the PHY has entered the smart power-down state.*/
 AQ_boolean  smartPowerDown; 
   /*! If true, the PHY's watchdog timer has expired.*/
 AQ_boolean  watchdogTimer; 
} AQ_API_GlobalAlarms;    

/*! This structure is used by the API to report alarm status for an
    Aquantia PHY. All interrupts are self-clearing, and latching,
    meaning that once set they stay set until the alarm status is read
    via AQ_API_GetAlarmStatus().
    The alarm status is reported as a series of structures, each with
    a corresponding summary bit to reduce the length of the alarm
    processing sieve.*/
typedef struct    
{    
 /*alarm flags*/   
   /*! If true, the target Aquantia PHY has an autonegotiation alarm
       set in the structure autonegotiationAlarms.*/
 AQ_boolean  autonegotiationAlarmSet; 
   /*! If true, the target Aquantia PHY has a 10GBASE-T alarm set in
       the structure _10GBASE_T_Alarms.*/
 AQ_boolean  _10GBASE_T_AlarmSet; 
   /*! If true, the target Aquantia PHY has a XAUI or RXAUI alarm set
       in the structure XAUI_Alarms.*/
 AQ_boolean  XAUI_AlarmSet; 
   /*! If true, the target Aquantia PHY has a XFI alarm set in the
       XFI0_Alarms field.*/
 AQ_boolean  XFI0_AlarmSet; 
   /*! If true, the target Aquantia PHY has a XFI alarm set in the
       XFI1_Alarms field.*/
 AQ_boolean  XFI1_AlarmSet; 
   /*! If true, the target Aquantia PHY has an SGMII alarm set in the
       SGMII0_Alarms field.*/
 AQ_boolean  SGMII0_AlarmSet; 
   /*! If true, the target Aquantia PHY has an SGMII alarm set in the
       SGMII1_Alarms field.*/
 AQ_boolean  SGMII1_AlarmSet; 
   /*! If true, the target Aquantia PHY has a SERDES alarm set in the
       SERDES_Alarms field.*/
 AQ_boolean  SERDES_AlarmSet; 
   /*! If true, the target Aquantia PHY has a test alarm set in the
       structure testAlarms.*/
 AQ_boolean  testAlarmSet; 
   /*! If true, the target Aquantia PHY has a global alarm set in the
       structure globalAlarms.*/
 AQ_boolean  globalAlarmSet; 
 /*alarms*/   
   /*! Autonegotiation alarms for the target Aquantia PHY.*/
 AQ_API_AutonegotiationAlarms   autonegotiationAlarms;
   /*! 10GBASE-T alarms for the target Aquantia PHY.*/
 AQ_API_10GBASE_T_Alarms   _10GBASE_T_Alarms;
   /*! XAUI or RXAUI alarms for the target Aquantia PHY.*/
 AQ_API_XAUI_Alarms   XAUI_Alarms;
   /*! XFI0 (lookaside port) alarms for the target Aquantia PHY.*/
 AQ_API_XFI_Alarms   XFI0_Alarms;
   /*! XFI1 (system interface) alarms for the target Aquantia PHY.*/
 AQ_API_XFI_Alarms   XFI1_Alarms;
   /*! SGMII0 alarms for the target Aquantia PHY.*/
 AQ_API_SGMII_Alarms   SGMII0_Alarms;
   /*! SGMII1 alarms for the target Aquantia PHY.*/
 AQ_API_SGMII_Alarms   SGMII1_Alarms;
   /*! SERDES alarms for the target Aquantia PHY.*/
 AQ_API_SERDES_Alarms   SERDES_Alarms;
   /*! Test alarms for the target Aquantia PHY.*/
 AQ_API_TestAlarms   testAlarms;
   /*! Global alarms for the target Aquantia PHY.*/
 AQ_API_GlobalAlarms   globalAlarms;
 /*diagnostic code*/   
   /*! If the hardware alarm deviceFault is true, this register
       contains the 16-bit diagnostic code associated with the
       deviceFault.*/
 uint16_t  deviceFaultCode; 
} AQ_API_AlarmStatus;    

/*! This function gets the alarm status for an Aquantia PHY. Calling
    this function clears any of the set interrupts. The user must
    provide a pointer to the AQ_API_AlarmStatus structure that they
    want the alarms to be returned in.*/
AQ_Retcode   AQ_API_GetAlarmStatus 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The alarm status for an Aquantia PHY.*/
 AQ_API_AlarmStatus*   alarmStatus
);    

/*@}*/


/*******************************************************************
                        Raw Alarms
*******************************************************************/

/*! \defgroup rawAlarms Raw Alarms
This structures is designed to report the state of all of the alarms within
the Aquantia PHY, regardless of whether they are masked or not. */
/*@{*/


/*! This function gets the raw (unmasked) alarm status for an Aquantia
    PHY. Calling this function clears any of the set interrupts. The
    user must provide a pointer to the AQ_API_AlarmStatus structure
    that they want the alarms to be returned in.*/
AQ_Retcode   AQ_API_GetRawAlarmStatus 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The raw alarm status for an Aquantia PHY.*/
 AQ_API_AlarmStatus*   alarmStatus
);    

/*@}*/


/*******************************************************************
                        Alarm Control
*******************************************************************/

/*! \defgroup alarmControl Alarm Control
These structures and functions provide the capability to masking the alarms
reported by the Aquantia PHY. */
/*@{*/


/*! This structure is used by the API to control alarm masking for an
    Aquantia PHY. By default, all masks are set so that alarms are
    only generated when a specific alarm is enabled.*/
typedef struct    
{    
 /*masks*/   
   /*! Autonegotiation alarms for the target Aquantia PHY.*/
 AQ_API_AutonegotiationAlarms   autonegotiationAlarmMask;
   /*! 10GBASE-T alarms for the target Aquantia PHY.*/
 AQ_API_10GBASE_T_Alarms   _10GBASE_T_AlarmMask;
   /*! XAUI or RXAUI alarms for the target Aquantia PHY.*/
 AQ_API_XAUI_Alarms   XAUI_AlarmMask;
   /*! XFI0 (lookaside port) alarms for the target Aquantia PHY.*/
 AQ_API_XFI_Alarms   XFI0_AlarmMask;
   /*! XFI1 (system interface) alarms for the target Aquantia PHY.*/
 AQ_API_XFI_Alarms   XFI1_AlarmMask;
   /*! SGMII0 alarms for the target Aquantia PHY.*/
 AQ_API_SGMII_Alarms   SGMII0_AlarmMask;
   /*! SGMII1 alarms for the target Aquantia PHY.*/
 AQ_API_SGMII_Alarms   SGMII1_AlarmMask;
   /*! SERDES alarms for the target Aquantia PHY.*/
 AQ_API_SERDES_Alarms   SERDES_AlarmMask;
   /*! Test alarms for the target Aquantia PHY.*/
 AQ_API_TestAlarms   testAlarmMask;
   /*! Global alarms for the target Aquantia PHY.*/
 AQ_API_GlobalAlarms   globalAlarmMask;
} AQ_API_AlarmControl;    

/*! This function gets the current alarm masking for an Aquantia PHY.
    The user must provide a pointer to the desired instantiation of
    AQ_API_AlarmControl that they wish to use to return this
    information in.*/
AQ_Retcode   AQ_API_GetAlarmControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The alarm control settings for an Aquantia PHY.*/
 AQ_API_AlarmControl*   alarmControl
);    

/*! This function sets the alarm masking for an Aquantia PHY. The user
    must provide a pointer to the desired instantiation of
    AQ_API_AlarmControl that they wish to use to control the alarm
    masking. This function intelligently sets and unsets the summary
    register masks, based on the presence of lower level interrupts.*/
AQ_Retcode   AQ_API_SetAlarmControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The alarm control settings for an Aquantia PHY.*/
 AQ_API_AlarmControl*   alarmControl
);    

/*! This function masks all of the alarms within an Aquantia PHY at
    the global summary register, allowing the user to halt interrupts,
    and rapidly get to the bottom of a failure.*/
AQ_Retcode   AQ_API_MaskAllAlarms 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port 
);    

/*! This function unmasks all of the alarms within an Aquantia PHY at
    the global summary register, allowing the user to halt interrupts,
    and rapidly get to the bottom of a failure.*/
AQ_Retcode   AQ_API_UnMaskAllAlarms 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port 
);    

/*@}*/


/*******************************************************************
                        10G Test Patterns
*******************************************************************/

/*! \defgroup _10GTestPatterns 10G Test Patterns
This set of data structures provides an interface for generating and
checking 10GBASE-T line test patterns. If a 10G line test is selected, it
can be the only test operational. */
/*@{*/


/*! This enumeration is used to select a line test pattern for an
    Aquantia PHY line interface.*/
typedef enum    
{    
  /*! This indicates that no line test pattern is selected.*/
 AQ_API_10G_LTP_None,   
  /*! This selects the 10GBASE-T Test Mode #1, which outputs the PAM-2
      training sequence (PRBS-33 variants) on all four channels.*/
 AQ_API_10G_LTP_10G_TestMode1,   
  /*! This selects the 10GBASE-T Test Mode #2, which outputs a full
      amplitude 200 MHz square wave on all four channels.*/
 AQ_API_10G_LTP_10G_TestMode2,   
  /*! This selects the 10GBASE-T Test Mode #3, which is used to
      receive the PAM-2 training sequences on Pairs A -> C from
      another part in 10GBASE-T Test Mode #1, and from this output a
      full amplitude 200 MHz square wave on Pair D.*/
 AQ_API_10G_LTP_10G_TestMode3,   
  /*! This selects the 10GBASE-T Test Mode #4.1, which outputs two
      sine waves on all four channels that complete 47 and 53 cycles
      per 1024 samples (at 800 Msample/s).*/
 AQ_API_10G_LTP_10G_TestMode4_1,   
  /*! This selects the 10GBASE-T Test Mode #4.2, which outputs two
      sine waves on all four channels that complete 101 and 103 cycles
      per 1024 samples (at 800 Msample/s).*/
 AQ_API_10G_LTP_10G_TestMode4_2,   
  /*! This selects the 10GBASE-T Test Mode #4.4, which outputs two
      sine waves on all four channels that complete 179 and 181 cycles
      per 1024 samples (at 800 Msample/s).*/
 AQ_API_10G_LTP_10G_TestMode4_4,   
  /*! This selects the 10GBASE-T Test Mode #4.5, which outputs two
      sine waves on all four channels that complete 277 and 281 cycles
      per 1024 samples (at 800 Msample/s).*/
 AQ_API_10G_LTP_10G_TestMode4_5,   
  /*! This selects the 10GBASE-T Test Mode #4.6, which outputs two
      sine waves on all four channels that complete 397 and 401 cycles
      per 1024 samples (at 800 Msample/s).*/
 AQ_API_10G_LTP_10G_TestMode4_6,   
  /*! This selects the 10GBASE-T Test Mode #5, which outputs full
      amplitude 10GBASE-T frames at full power. This uses the self-
      synchronizing scrambler to produce the data stream, as in
      10GBASE-T Test Mode #7.*/
 AQ_API_10G_LTP_10G_TestMode5,   
  /*! This selects the 10GBASE-T Test Mode #6, which outputs a full-
      amplitude 3.26 MHz square-wave on all four channels (256 symbols
      at 800 Msample/s).*/
 AQ_API_10G_LTP_10G_TestMode6,   
  /*! This selects the 10GBASE-T Test Mode #7, which outputs 10GBASE-T
      frames using a zero input to the self-synchronizing scrambler as
      the data source. This has a checker associated with it.*/
 AQ_API_10G_LTP_10G_TestMode7   
} AQ_API_10G_LineTestPattern;   

/*! This function gets the 10G line test pattern generation settings
    for an Aquantia PHY. The user must provide a pointer to the
    desired AQ_API_10G_LineTestPattern to return the values in.*/
AQ_Retcode   AQ_API_Get10G_LineTestPattern 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The current 10G line test pattern for the Aquantia PHY.*/
 AQ_API_10G_LineTestPattern*   testPattern
);    

/*! This function sets the 10G line test pattern generation for an
    Aquantia PHY. The user must provide the desired
    AQ_API_10G_LineTestPattern value.
    Clearing of the test modes is done either via disabling the tests
    in testPatternControl or via calling the function
    AQ_API_SetActive().
    Note that when AQ_API_10G_LTP_10G_TestMode3 is set, the firmware
    may not respond to MDIO events if the PHY is not connected to a
    suitable test partner. Therefore, the recommended method for
    exiting test mode 3 is to reset the PHY.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    */
AQ_Retcode   AQ_API_Set10G_LineTestPattern 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The desired 10G line test pattern for the Aquantia PHY.*/
 AQ_API_10G_LineTestPattern   testPattern
);    

/*! This enumeration is used to select an AQRate data rate for use
    with 10GBase-T line test patterm.*/
typedef enum    
{    
  /*! Indicates that the data rate used with 10GBasep-T line test
      patterns is 10G.*/
 AQ_API_AQRate_LTDR_10G,   
  /*! Indicates that the data rate used with 10GBase-T line test
      patterns is 5G.*/
 AQ_API_AQRate_LTDR_5G,   
  /*! Indicates that the data rate used with 10GBasep-T line test
      patterns is 2.5G.*/
 AQ_API_AQRate_LTDR_2_5G,   
  /*! Unrecognized mode- do not use.*/
 AQ_API_AQRate_LTDR_Other   
} AQ_API_AQRate_LineTestDataRate;   

/*! This function gets the 10G/5G/2.5 line test pattern generation,
    and the associated data rate, settings for an Aquantia PHY. The
    user must provide a pointer to the desired
    AQ_API_10G_LineTestPattern and AQ_API_AQRate_LineTestDataRate to
    return the values in.*/
AQ_Retcode   AQ_API_GetAQRate_LineTestPattern 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The current 10G line test pattern for the Aquantia PHY.*/
 AQ_API_10G_LineTestPattern*   testPattern,
  /*! The current data rate associated with the 10G line test
      pattern.*/
 AQ_API_AQRate_LineTestDataRate*   dataRate
);    

/*! This function sets the 10G/5G/2.5G line test pattern generation,
    and the associated data rate, for an Aquantia PHY. The user must
    provide the desired AQ_API_10G_LineTestPattern and
    AQ_API_AQRate_LineTestDataRate value.
    Clearing of the test modes is done either via disabling the tests
    in testPatternControl or via calling the function
    AQ_API_SetActive().
    Note that when AQ_API_10G_LTP_10G_TestMode3 is set, the firmware
    may not respond to MDIO events if the PHY is not connected to a
    suitable test partner. Therefore, the recommended method for
    exiting test mode 3 is to reset the PHY.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    */
AQ_Retcode   AQ_API_SetAQRate_LineTestPattern 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The desired 10G line test pattern for the Aquantia PHY.*/
 AQ_API_10G_LineTestPattern   testPattern,
  /*! The desired data rate used withn for the 10G line test
      pattern.*/
 AQ_API_AQRate_LineTestDataRate   dataRate
);    

/*@}*/


/*******************************************************************
                        1G Test Patterns
*******************************************************************/

/*! \defgroup _1GTestPatterns 1G Test Patterns
This set of data structures provides an interface for generating 1000BASE-T
line test patterns. If a 1G line test is selected, it can be the only test
operational. */
/*@{*/


/*! This enumeration is used to select a line test pattern for an
    Aquantia PHY line interface.*/
typedef enum    
{    
  /*! This indicates that no line test pattern is selected.*/
 AQ_API_1G_LTP_None,   
  /*! This selects the 1000BASE-T Test Mode #1, which outputs the
      transmit waveform test.*/
 AQ_API_1G_LTP_TestMode1,   
  /*! This selects the 1000BASE-T Test Mode #2, which outputs the
      master transmit jitter test.*/
 AQ_API_1G_LTP_TestMode2,   
  /*! This selects the 1000BASE-T Test Mode #3, which outputs the
      slave transmit jitter test.*/
 AQ_API_1G_LTP_TestMode3,   
  /*! This selects the 1000BASE-T Test Mode #4, which outputs the
      transmitter distortion test.*/
 AQ_API_1G_LTP_TestMode4   
} AQ_API_1G_LineTestPattern;   

/*! This function gets the 1G test pattern generation settings for an
    Aquantia PHY. The user must provide a pointer to the desired
    AQ_API_1G_LineTestPattern structure to return the value in.*/
AQ_Retcode   AQ_API_Get1G_LineTestPattern 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The current 1G line test pattern for the Aquantia PHY.*/
 AQ_API_1G_LineTestPattern*   testPattern
);    

/*! This function sets the 1G line test pattern generation for an
    Aquantia PHY. The user must provide the desired
    AQ_API_1G_LineTestPattern value.
    Clearing of the test modes is done either via disabling the tests
    in testPattern or via calling the function AQ_API_SetActive().
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    */
AQ_Retcode   AQ_API_Set1G_LineTestPattern 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The desired 1G line test pattern for the Aquantia PHY.*/
 AQ_API_1G_LineTestPattern   testPattern
);    

/*@}*/


/*******************************************************************
                        100M Test Patterns
*******************************************************************/

/*! \defgroup _100MTestPatterns 100M Test Patterns
This set of data structures provides an interface for generating 100BASE-TX
line test patterns. If a 100M line test is selected, it can be the only
test operational. */
/*@{*/


/*! This enumeration is used to select a line test pattern for an
    Aquantia PHY line interface.*/
typedef enum    
{    
  /*! This indicates that no line test pattern is selected.*/
 AQ_API_100M_LTP_None,   
  /*! This selects the 100BASE-TX IEEE test mode.*/
 AQ_API_100M_LTP_IEEE_TestMode,   
  /*! This selects the 100BASE-TX ANSI Jitter test mode.*/
 AQ_API_100M_LTP_ANSI_Jitter_TestMode,   
  /*! This selects the 100BASE-TX ANSI Droop test mode.*/
 AQ_API_100M_LTP_ANSI_Droop_TestMode   
} AQ_API_100M_LineTestPattern;   

/*! This function gets the 100M test pattern generation settings for
    an Aquantia PHY. The user must provide a pointer to the desired
    AQ_API_100M_LineTestPattern structure to return the value in.*/
AQ_Retcode   AQ_API_Get100M_LineTestPattern 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The current 100M line test pattern for the Aquantia PHY.*/
 AQ_API_100M_LineTestPattern*   testPattern
);    

/*! This function sets the 100M line test pattern generation for an
    Aquantia PHY. The user must provide the desired
    AQ_API_100M_LineTestPattern value.
    Clearing of the test modes is done either via disabling the tests
    in testPattern or via calling the function AQ_API_SetActive().
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    */
AQ_Retcode   AQ_API_Set100M_LineTestPattern 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The desired 100M line test pattern for the Aquantia PHY.*/
 AQ_API_100M_LineTestPattern   testPattern
);    

/*@}*/


/*******************************************************************
                        Loopbacks
*******************************************************************/

/*! \defgroup loopbacks Loopbacks
The Aquantia PHY is capable of providing a wide range of loopbacks on both
the network and system side (i.e. line and MAC). Control of these loopbacks
is accomplished via the two SetLoopbackControl () functions. Clearing of a
loopback is done either by marking the loopbacks as clear in the
appropriate SetLoopbackControl () functions, or by calling the function
AQ_API_SetActive(). */
/*@{*/


/*! This enumeration is used to select a loopback mode for an Aquantia
    PHY.*/
typedef enum    
{    
  /*! This indicates that no loopback mode is selected.*/
 No_Loopback,   
  /*! This selects the network loopback test mode within the system
      interface.*/
 SystemInterface_NetworkLoopback,   
  /*! This selects the system loopback test mode within the network
      interface.*/
 NetworkInterface_SystemLoopback   
} AQ_API_LoopbackControl;   

/*! This function gets the loopback settings within an Aquantia PHY.
    Clearing of a loopback is done either by marking the loopbacks as
    clear in AQ_API_SetLoopbackControl, or by calling the function
    AQ_API_SetActive().*/
AQ_Retcode   AQ_API_GetLoopbackControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*!  Returns the current loopback settings.*/
 AQ_API_LoopbackControl*   loopback
);    

/*! This function sets up loopbacks within an Aquantia PHY. Clearing
    of a loopback is done either by marking the loopbacks as clear in
    AQ_API_SetLoopbackControl, or by calling the function
    AQ_API_SetActive().
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    AQ_RET_LOOPBACK_BAD_ENTRY_STATE: The state of the PHY was not
    suitable for entering bootload (for example, if the PHY is in
    reset)*/
AQ_Retcode   AQ_API_SetLoopbackControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The desired loopback settings.*/
 AQ_API_LoopbackControl   loopback
);    

/*! This enumeration is used to select a loopback mode for an Aquantia
    PHY. The selected loopback mode will be maintained by the PHY's FW
    across state changes.
    Compatibility: 28nm PHYs only.*/
typedef enum    
{    
  /*! This indicates that no loopback mode is selected.*/
 AQ_FWMLC_No_LB,   
  /*! This selects the system loopback test mode within the system
      interface. Traffic from the system will be redirected towards
      the system.*/
 AQ_FWMLC_SysIntf_SysLB,   
  /*! This selects the system loopback test mode within the system
      interface. Traffic from the system will be redirected towards
      the system, and also will be passed through towards the
      network.*/
 AQ_FWMLC_SysIntf_SysLB_Passthrough,   
  /*! This selects the network loopback test mode within the system
      interface. Traffic from the network will be redirected towards
      the network.*/
 AQ_FWMLC_SysIntf_NetLB,   
  /*! This selects the network loopback test mode within the system
      interface. Traffic from the network will be redirected towards
      the network, and also will be passed through towards the
      system.*/
 AQ_FWMLC_SysIntf_NetLB_Passthrough,   
  /*! This selects the network loopback test mode within the system
      interface. Traffic from the network will be redirected towards
      the network, and also will be passed through towards the system.
      The redirected traffic will be non-destructively merged with
      traffic from the system.*/
 AQ_FWMLC_SysIntf_NetLB_PassthroughMerge,   
  /*! This selects the system loopback test mode within the network
      interface. Traffic from the system will be redirected towards
      the system.*/
 AQ_FWMLC_NetIntf_SysLB,   
  /*! This selects the system loopback test mode within the network
      interface. Traffic from the system will be redirected towards
      the system, and also will be passed through towards the
      network.*/
 AQ_FWMLC_NetIntf_SysLB_Passthrough,   
  /*! This selects the system loopback test mode within the network
      interface. Traffic from the system will be redirected towards
      the system. A loopback plug must be inserted in the MDI port.*/
 AQ_FWMLC_NetIntf_SysLB_Plug,   
  /*! This selects the network loopback test mode within the network
      interface. Traffic from the network will be redirected towards
      the network.*/
 AQ_FWMLC_NetIntf_NetLB,   
  /*! This selects the network loopback test mode within the network
      interface. Traffic from the network will be redirected towards
      the network, and also will be passed through towards the
      system.*/
 AQ_FWMLC_NetIntf_NetLB_Passthrough,   
  /*! This selects the system loopback test mode within the cross-
      connect (between the network and system interfaces). Traffic
      from the system will be redirected towards the system.*/
 AQ_FWMLC_CrossConnect_SysLB,   
  /*! This selects the network loopback test mode within the cross-
      connect (between the network and system interfaces). Traffic
      from the network will be redirected towards the network.*/
 AQ_FWMLC_CrossConnect_NetLB,   
  /*! Unrecognized mode- do not use.*/
 AQ_FWMLC_Other   
} AQ_API_FWManagedLoopbackControl;   

/*! This enumeration is used to select a packet generation data rate
    for an Aquantia PHY.*/
typedef enum    
{    
  /*! This indicates that a loopback will be automatically chosen,
      based on the currently active system/network interface.*/
 AQ_FWMLRate_Auto,   
  /*! This indicates that a loopback in the 10G data path will be
      set.*/
 AQ_FWMLRate_10G,   
  /*! This indicates that a loopback in the 5G data path will be
      set.*/
 AQ_FWMLRate_5G,   
  /*! This indicates that a loopback in the 2.5G data path will be
      set.*/
 AQ_FWMLRate_2_5G,   
  /*! This indicates that a loopback in the 1G data path will be
      set.*/
 AQ_FWMLRate_1G,   
  /*! This indicates that a loopback in the 100M data path will be
      set.*/
 AQ_FWMLRate_100M,   
  /*! Unrecognized mode- do not use.*/
 AQ_FWMLRate_Other   
} AQ_API_FWManagedLoopbackRate;   

/*! This function gets the loopback mode within the Aquantia PHY. The
    selected loopback mode will be maintained by the PHY's FW across
    state changes. Clearing of a loopback is done either by marking
    the loopbacks as clear in AQ_API_SetFWManagedLoopbackControl, or
    by calling the function AQ_API_SetActive().
    Compatibility: 28nm PHYs only.*/
AQ_Retcode   AQ_API_GetFWManagedLoopbackControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*!  Returns the current loopback mode.*/
 AQ_API_FWManagedLoopbackControl*   loopback,
  /*!  Returns the current loopback rate setting.*/
 AQ_API_FWManagedLoopbackRate*   rate
);    

/*! This function selects a loopback mode within the Aquantia PHY. The
    selected loopback mode will be maintained by the PHY's FW across
    state changes. Clearing of a loopback is done either by marking
    the loopbacks as clear in AQ_API_SetFWManagedLoopbackControl, or
    by calling the function AQ_API_SetActive().
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    Compatibility: 28nm PHYs only.*/
AQ_Retcode   AQ_API_SetFWManagedLoopbackControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The desired loopback mode.*/
 AQ_API_FWManagedLoopbackControl   loopback,
  /*! The desired loopback rate setting.*/
 AQ_API_FWManagedLoopbackRate   rate
);    

/*@}*/


/*******************************************************************
                        Packet Generation
*******************************************************************/

/*! \defgroup packetGeneration Packet Generation
These controls enable/disable generation of CRPAT packets towards the
desired interface. The selected packet generation mode will be maintained
by the PHY's firmware across state changes. */
/*@{*/


/*! This enumeration is used to select a packet generation mode for an
    Aquantia PHY.*/
typedef enum    
{    
  /*! This indicates that packet generation is enabled, and the
      packets are directed towards the system interface.*/
 AQ_PktGen_Enable_ToSysIntf,   
  /*! This indicates that packet generation is enabled, and the
      packets are directed towards the network interface.*/
 AQ_PktGen_Enable_ToNetIntf,   
  /*! This indicates that packet generation is disabled.*/
 AQ_PktGen_Disable,   
  /*! Unrecognized mode- do not use.*/
 AQ_PktGen_Other   
} AQ_API_PktGenControl;   

/*! This enumeration is used to select a packet generation data rate
    for an Aquantia PHY.*/
typedef enum    
{    
  /*! This indicates thatthe packet generation rate will be
      automatically chosen, based on the currently active
      system/network interface.*/
 AQ_PktGenRate_Auto,   
  /*! This indicates that packets generation will be generated at a
      data rate of 10G.*/
 AQ_PktGenRate_10G,   
  /*! This indicates that packets generation will be generated at a
      data rate of 5G.*/
 AQ_PktGenRate_5G,   
  /*! This indicates that packets generation will be generated at a
      data rate of 2.5G.*/
 AQ_PktGenRate_2_5G,   
  /*! This indicates that packets generation will be generated at a
      data rate of 1G.*/
 AQ_PktGenRate_1G,   
  /*! This indicates that packets generation will be generated at a
      data rate of 100M.*/
 AQ_PktGenRate_100M,   
  /*! Unrecognized mode- do not use.*/
 AQ_PktGenRate_Other   
} AQ_API_PktGenRate;   

/*! This function gets the packet generation settings within an
    Aquantia PHY.*/
AQ_Retcode   AQ_API_GetPktGenControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*!  Returns the current packet generation settings.*/
 AQ_API_PktGenControl*   pktGen,
  /*!  Returns the current packet generation rate.*/
 AQ_API_PktGenRate*   pktGenRate
);    

/*! This function selects the packet generation settings within an
    Aquantia PHY. The selected packet generation mode mode will be
    maintained by the PHY's FW across state changes.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    */
AQ_Retcode   AQ_API_SetPktGenControl 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*!  The desired packet generation settings.*/
 AQ_API_PktGenControl   pktGen,
  /*!  The desired packet generation rate.*/
 AQ_API_PktGenRate   pktGenRate
);    

/*@}*/


/*******************************************************************
                        Writing Images
*******************************************************************/

/*! \defgroup writingImages Writing Images
The Aquantia PHY provides the user the capability of writing code images
either to FLASH or to the internal RAM of the Aquantia PHY. This is
designed to allow: */
/*@{*/


/*! This function programs the FLASH memory of an Aquantia PHY and
    after loading, verifies the FLASH image against the original. To
    program the FLASH, the processor is halted, and then after
    programming is complete, the Aquantia PHY is restored to its
    former state.
    Return codes:
    AQ_RET_FLASHINTF_READINESS_TIMEOUT: The timout period elapsed
    while waiting for the PHY's NVR interface to indicate readiness
    for writing.
    AQ_RET_FLASH_READINESS_TIMEOUT: The timout period elapsed while
    waiting for the FLASH to indicate readiness for writing.
    AQ_RET_FLASH_TYPE_UNKNOWN: The type of FLASH could not be
    determined.
    AQ_RET_FLASH_TYPE_BAD: The type of FLASH was determined to be of
    an unsuitable type for writing. This can happen if port does not
    indicate the daisy-chain master.
    AQ_RET_FLASH_IMAGE_CORRUPT: The checksum in the image did not
    match the image data.
    AQ_RET_FLASH_IMAGE_TOO_LARGE: The image is too large to fit in the
    FLASH.
    AQ_RET_FLASH_PAGE_SIZE_CHANGED: The FLASH needed to have its page
    size changed before writing could be performed successfully, and
    so it was changed. If this result occurs, the PHY state will not
    be modified, and this function should be called again after the
    FLASH power supply has been cycled.
    AQ_RET_FLASH_IMAGE_MISMATCH: The checksum of the image that is
    read back from the FLASH after writing does not match that of the
    specified image. This indicates that the image was not
    successfully written to the FLASH, or that it was written
    successfully but there was a problem reading it back.
    */
AQ_Retcode   AQ_API_WriteAndVerifyFlashImage 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! A pointer to the size of the image (in bytes) that is being
      loaded into the Aquantia PHY.*/
 const uint32_t*  imageSizePointer, 
  /*! The image being loaded into the Aquantia PHY. This is the same
      regardless of whether the target is internal RAM or FLASH.*/
 const uint8_t*  image 
);    

/*! This function verifies the FLASH image in an Aquantia PHY against
    the original. To verify the FLASH, the processor is halted, and
    then after verification is complete, the Aquantia PHY is restored
    to its former state.
    Return codes:
    AQ_RET_FLASHINTF_READINESS_TIMEOUT: The timout period elapsed
    while waiting for the PHY's NVR interface to indicate readiness
    for reading.
    AQ_RET_FLASH_READINESS_TIMEOUT: The timout period elapsed while
    waiting for the FLASH to indicate readiness for reading.
    AQ_RET_FLASH_TYPE_UNKNOWN: The type of FLASH could not be
    determined.
    AQ_RET_FLASH_TYPE_BAD: The type of FLASH was determined to be of
    an unsuitable type for reading. This can happen if port does not
    indicate the daisy-chain master.
    AQ_RET_FLASH_IMAGE_CORRUPT: The checksum in the image did not
    match the image data.
    AQ_RET_FLASH_IMAGE_TOO_LARGE: The image is too large to fit in the
    FLASH.
    AQ_RET_FLASH_IMAGE_MISMATCH: The checksum of the image that is
    read back from the FLASH after writing does not match that of the
    specified image. This indicates that the image was not
    successfully written to the FLASH, or that it was written
    successfully but there was a problem reading it back.
    */
AQ_Retcode   AQ_API_VerifyFlashImage 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! A pointer to the size of the image (in bytes) that is being
      loaded into the Aquantia PHY.*/
 const uint32_t*  imageSizePointer, 
  /*! The image being loaded into the Aquantia PHY. This is the same
      regardless of whether the target is internal RAM or FLASH.*/
 const uint8_t*  image 
);    

/*! This function reads a certain number of bytes from a FLASH image
    in an Aquantia PHY. During the read of the FLASH, the processor is
    halted, and then after the read is complete, the Aquantia PHY is
    restored to its former state.
    Note that this function will only read the FLASH up to its maximum
    size. After that the image will be zero filled if more bytes are
    specified to be read than the FLASH contains.
    Return codes:
    AQ_RET_FLASHINTF_READINESS_TIMEOUT: The timout period elapsed
    while waiting for the PHY's NVR interface to indicate readiness
    for reading.
    AQ_RET_FLASH_READINESS_TIMEOUT: The timout period elapsed while
    waiting for the FLASH to indicate readiness for reading.
    AQ_RET_FLASH_TYPE_UNKNOWN: The type of FLASH could not be
    determined.
    AQ_RET_FLASH_TYPE_BAD: The type of FLASH was determined to be of
    an unsuitable type for reading. This can happen if port does not
    indicate the daisy-chain master.
    */
AQ_Retcode   AQ_API_ReadFlashImage 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The starting address from which to read the bytes from the
      Aquantia PHY's FLASH.*/
 const uint32_t*  startAddress, 
  /*! The number of bytes to be loaded from the Aquantia PHY's FLASH
      into the image array.*/
 const uint32_t*  imageSizePointer, 
  /*! The image being loaded from the Aquantia PHY's FLASH.*/
 uint8_t*  image 
);    

/*! This function boot-loads the instruction and data memory (IRAM and
    DRAM) of a set of Aquantia PHYs from a .cld format image file (the
    same image file used to burn the FLASH). During boot-load of each
    Aquantia PHY, the processor is halted, and after programming is
    complete the processor is released. Note that calling this
    function leaves the daisy-chain disabled to prevent RAM over-
    write. To exit MDIO boot-load mode, use the function
    AQ_API_EnableDaisyChain.
    Unlike most of the other functions in this API, this function can
    operate on a group of PHYs simultaneously. This is referred to as
    gang-loading. To facilitate this, this function takes as
    parameters 3 parallel arrays: PHY_IDs, provisioningAddresses, and
    resultCodes. The length of these arrays must be identical, and is
    specified by the num_PHY_IDs parameter.
    In order to check the integrity of the boot-load operation, a
    CRC-16 value is calculated over the IRAM and DRAM. After the image
    has been loaded, this value is directly compared against each
    PHY's Mailbox CRC-16 in 1E.0201.
    The value of register 1E.C441 must be the same for all the boot-
    loaded PHYs. This will be checked before the boot-load is
    performed, and if a non-uniform value is read from any of the
    PHYs, the function will fail before any writes are performed.
    A separate result code is returned for each of the boot-loaded
    PHYs, in the OUT parameter, resultCodes.
    Individual Port Return codes:
    AQ_RET_BOOTLOAD_PROVADDR_OOR: The specified provisioning address
    was outside of the permitted range.
    AQ_RET_BOOTLOAD_NONUNIFORM_REGVALS: The values of the register(s)
    that must be uniform across the ports being bootloaded were not
    uniform.
    AQ_RET_BOOTLOAD_CRC_MISMATCH: The image was completely loaded into
    memory, but the after the port exited bootload the running
    checksum that was read from the uP memory mailbox was not the
    expected value. This indicates that the memory has potentially
    been corrupted, and the PHY should be reset before trying the
    bootload again.
    Overall Return codes (the return value from the function call):
    AQ_RET_OK: all ports were successfully bootloaded.
    AQ_RET_ERROR: One or more ports were not successfully bootloaded.
    */
AQ_Retcode   AQ_API_WriteBootLoadImage 
(    
  /*! An array identifying the target PHY ports.*/
 AQ_API_Port**  ports, 
  /*! The length of the arrays ports, provisioningAddresses, and
      resultCodes. These are parallel arrays, and must all be of the
      same length.*/
 unsigned int  numPorts, 
  /*! The provisioning addresses of each of the PHYs specified in
      ports. This can range from 0 through 47, and is also known as
      the daisy-chain address or the hop-count. If the PHYs are
      connected to a FLASH using the daisy-chain, this is the distance
      from the PHY to the FLASH, and is used to identify customized
      provisioning for each PHY from the provisioning data within the
      image. Otherwise, it is an arbitrary number. The length of this
      array must match the length of ports.*/
 const unsigned int*  provisioningAddresses, 
  /*! OUT: The result code indicating success or failure of boot-
      loading each of the PHYs specified in ports.*/
 AQ_Retcode*  resultCodes, 
  /*! A pointer to the size of the image (in bytes) that is being
      loaded into the Aquantia PHY.*/
 const uint32_t*  imageSizePointer, 
  /*! The image being loaded into the Aquantia PHY. This is the same
      regardless of whether the target is internal RAM or FLASH.*/
 const uint8_t*  image, 
  /*! The 5-bit address to be used during the gang-loading operation.
      During the boot-loading process, each of the PHYs specified in
      ports will be changed such that they are addressed on the MDIO
      bus at gangloadAddress. This allows all the PHYs to be loaded
      simultaneously. Before returning, each PHY will be moved back to
      its original MDIO address. If ports contains only a single
      element, callers will probably want to use the PHY's original
      MDIO address for this parameter.*/
 uint8_t  gangload_MDIO_address, 
  /*! The address of the PHYs while in gangload mode.  This is
      ultimately some combination of the system address and the
      gangload MDIO address, specified by gangload_MDIO_address.  For
      most platforms, gangload_MDIO_address and gangload_PHY_ID should
      have the same value.*/
 AQ_API_Port*  gangloadPort 
);    

/*! This function boot-loads the instruction and data memory (IRAM and
    DRAM) of a set of Aquantia PHYs from a .cld format image file (the
    same image file used to burn the FLASH), as well as a separately
    provided provisioning table image file.The provisioning table
    image allows additional provisioning to be provided, beyond what
    is built in to the .cld image. If provTableSizePointer or
    provTableImage are NULL, this function behaves like
    AQ_API_WriteBootLoadImage.
    Aside from the additional provisioning table, this function
    behaves exactly the same as AQ_API_WriteBootLoadImage. For
    additional documentation and information on return codes, refer to
    AQ_API_WriteBootLoadImage.
    Individual Port Return codes (same as AQ_API_WriteBootLoadImage,
    plus):
    AQ_RET_BOOTLOAD_PROVTABLE_TOO_LARGE: The supplied provisioning
    table image does not fit within the alloted space.*/
AQ_Retcode   AQ_API_WriteBootLoadImageWithProvTable 
(    
  /*! An array identifying the target PHY ports.*/
 AQ_API_Port**  ports, 
  /*! The length of the arrays ports, provisioningAddresses, and
      resultCodes. These are parallel arrays, and must all be of the
      same length.*/
 unsigned int  numPorts, 
  /*! The provisioning addresses of each of the PHYs specified in
      ports. This can range from 0 through 47, and is also known as
      the daisy-chain address or the hop-count. If the PHYs are
      connected to a FLASH using the daisy-chain, this is the distance
      from the PHY to the FLASH, and is used to identify customized
      provisioning for each PHY from the provisioning data within the
      image. Otherwise, it is an arbitrary number. The length of this
      array must match the length of ports.*/
 const unsigned int*  provisioningAddresses, 
  /*! OUT: The result code indicating success or failure of boot-
      loading each of the PHYs specified in ports.*/
 AQ_Retcode*  resultCodes, 
  /*! A pointer to the size of the image (in bytes) that is being
      loaded into the Aquantia PHY.*/
 const uint32_t*  imageSizePointer, 
  /*! The image being loaded into the Aquantia PHY. This is the same
      regardless of whether the target is internal RAM or FLASH.*/
 const uint8_t*  image, 
  /*! The 5-bit address to be used during the gang-loading operation.
      During the boot-loading process, each of the PHYs specified in
      ports will be changed such that they are addressed on the MDIO
      bus at gangloadAddress. This allows all the PHYs to be loaded
      simultaneously. Before returning, each PHY will be moved back to
      its original MDIO address. If ports contains only a single
      element, callers will probably want to use the PHY's original
      MDIO address for this parameter.*/
 uint8_t  gangload_MDIO_address, 
  /*! The address of the PHYs while in gangload mode.  This is
      ultimately some combination of the system address and the
      gangload MDIO address, specified by gangload_MDIO_address.  For
      most platforms, gangload_MDIO_address and gangload_PHY_ID should
      have the same value.*/
 AQ_API_Port*  gangloadPort, 
  /*! A pointer to the size of the provTableImage (in bytes) that is
      being loaded into the Aquantia PHY.*/
 const uint32_t*  provTableSizePointer, 
  /*! The additional provisioning table image being loaded into the
      Aquantia PHY.*/
 const uint8_t*  provTableImage 
);    

/*! This function boot-loads the data memory (DRAM) of a set of
    Aquantia PHYs from a .cld format image file (the same image file
    used to burn the FLASH). The instruction memory (IRAM) is NOT
    loaded.
    Aside from skipping the IRAM loading, this function behaves
    exactly the same as AQ_API_WriteBootLoadImage. For complete
    documentation and information on return codes, refer to
    AQ_API_WriteBootLoadImage.
    */
AQ_Retcode   AQ_API_WriteBootLoadImageDRAMOnly 
(    
  /*! An array identifying the target PHY ports.*/
 AQ_API_Port**  ports, 
  /*! The length of the arrays ports, provisioningAddresses, and
      resultCodes. These are parallel arrays, and must all be of the
      same length.*/
 unsigned int  numPorts, 
  /*! The provisioning addresses of each of the PHYs specified in
      ports. This can range from 0 through 47, and is also known as
      the daisy-chain address or the hop-count. If the PHYs are
      connected to a FLASH using the daisy-chain, this is the distance
      from the PHY to the FLASH, and is used to identify customized
      provisioning for each PHY from the provisioning data within the
      image. Otherwise, it is an arbitrary number. The length of this
      array must match the length of ports.*/
 const unsigned int*  provisioningAddresses, 
  /*! OUT: The result code indicating success or failure of boot-
      loading each of the PHYs specified in ports.*/
 AQ_Retcode*  resultCodes, 
  /*! A pointer to the size of the image (in bytes) that is being
      loaded into the Aquantia PHY.*/
 const uint32_t*  imageSizePointer, 
  /*! The image being loaded into the Aquantia PHY. This is the same
      regardless of whether the target is internal RAM or FLASH.*/
 const uint8_t*  image, 
  /*! The 5-bit address to be used during the gang-loading operation.
      During the boot-loading process, each of the PHYs specified in
      ports will be changed such that they are addressed on the MDIO
      bus at gangloadAddress. This allows all the PHYs to be loaded
      simultaneously. Before returning, each PHY will be moved back to
      its original MDIO address. If ports contains only a single
      element, callers will probably want to use the PHY's original
      MDIO address for this parameter.*/
 uint8_t  gangload_MDIO_address, 
  /*! The address of the PHYs while in gangload mode.  This is
      ultimately some combination of the system address and the
      gangload MDIO address, specified by gangload_MDIO_address.  For
      most platforms, gangload_MDIO_address and gangload_PHY_ID should
      have the same value.*/
 AQ_API_Port*  gangloadPort 
);    

/*! This function boot-loads the data memory (DRAM) of a set of
    Aquantia PHYs from a .cld format image file (the same image file
    used to burn the FLASH), as well as a separately provided
    provisioning table image file. The instruction memory (IRAM) is
    NOT loaded.
    Aside from skipping the IRAM loading, this function behaves
    exactly the same as AQ_API_WriteBootLoadImageWithProvTable. For
    complete documentation and information on return codes, refer to
    AQ_API_WriteBootLoadImageWithProvTable.*/
AQ_Retcode   AQ_API_WriteBootLoadImageWithProvTableDRAMOnly 
(    
  /*! An array identifying the target PHY ports.*/
 AQ_API_Port**  ports, 
  /*! The length of the arrays ports, provisioningAddresses, and
      resultCodes. These are parallel arrays, and must all be of the
      same length.*/
 unsigned int  numPorts, 
  /*! The provisioning addresses of each of the PHYs specified in
      ports. This can range from 0 through 47, and is also known as
      the daisy-chain address or the hop-count. If the PHYs are
      connected to a FLASH using the daisy-chain, this is the distance
      from the PHY to the FLASH, and is used to identify customized
      provisioning for each PHY from the provisioning data within the
      image. Otherwise, it is an arbitrary number. The length of this
      array must match the length of ports.*/
 const unsigned int*  provisioningAddresses, 
  /*! OUT: The result code indicating success or failure of boot-
      loading each of the PHYs specified in ports.*/
 AQ_Retcode*  resultCodes, 
  /*! A pointer to the size of the image (in bytes) that is being
      loaded into the Aquantia PHY.*/
 const uint32_t*  imageSizePointer, 
  /*! The image being loaded into the Aquantia PHY. This is the same
      regardless of whether the target is internal RAM or FLASH.*/
 const uint8_t*  image, 
  /*! The 5-bit address to be used during the gang-loading operation.
      During the boot-loading process, each of the PHYs specified in
      ports will be changed such that they are addressed on the MDIO
      bus at gangloadAddress. This allows all the PHYs to be loaded
      simultaneously. Before returning, each PHY will be moved back to
      its original MDIO address. If ports contains only a single
      element, callers will probably want to use the PHY's original
      MDIO address for this parameter.*/
 uint8_t  gangload_MDIO_address, 
  /*! The address of the PHYs while in gangload mode.  This is
      ultimately some combination of the system address and the
      gangload MDIO address, specified by gangload_MDIO_address.  For
      most platforms, gangload_MDIO_address and gangload_PHY_ID should
      have the same value.*/
 AQ_API_Port*  gangloadPort, 
  /*! A pointer to the size of the provTableImage (in bytes) that is
      being loaded into the Aquantia PHY.*/
 const uint32_t*  provTableSizePointer, 
  /*! The additional provisioning table image being loaded into the
      Aquantia PHY.*/
 const uint8_t*  provTableImage 
);    

/*! Calling this function disables boot-loading and enables the daisy-
    chain. This would typically be called after using MDIO boot-
    loading on a daisy-chain enabled PHY. Re-enabling the daisy-chain
    after performing an MDIO bootload will cause the PHY to reboot
    from FLASH.*/
AQ_Retcode   AQ_API_EnableDaisyChain 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port 
);    

/*@}*/


/*******************************************************************
                        Memory Access
*******************************************************************/

/*! \defgroup memoryAccess Memory Access
Functions providing indirect access the PHY's internal memory. */
/*@{*/


/*! This function performs a series of indirect writes to write a
    contiguous block of memory.*/
AQ_Retcode   AQ_API_MemoryWrite 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The data to be written to memory.*/
 uint8_t*  data, 
  /*! The number of bytes that will be written to memory.*/
 uint32_t  numBytesToWrite, 
  /*! The starting address of the block of memory that will be
      written.*/
 uint32_t  startAddress 
);    

/*! This function performs a series of indirect reads to read a
    contiguous block of memory.*/
AQ_Retcode   AQ_API_MemoryRead 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The buffer into which the memory contents will be read.*/
 uint8_t*  data, 
  /*! The number of bytes to read from memory.*/
 uint32_t  numBytesToRead, 
  /*! The starting address of the block of memory that will be read.*/
 uint32_t  startAddress 
);    

/*@}*/


/*******************************************************************
                        Debug Assistance
*******************************************************************/

/*! \defgroup debugAssistance Debug Assistance
Functions that retrieve information useful for troubleshooting hardware or
integration problems. While not necessary during normal operation, it is
recommended that these functions be exposed by platform software, at least
during the development process, should problems arise. */
/*@{*/


/*! Reads many PHY registers useful for troubleshooting problems, and
    writes them to regDump. Several registers are read and printed
    repeatedly at 100ms intervals, so this function will take several
    seconds to return.*/
AQ_Retcode   AQ_API_PrintDebugRegisters 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The register addresses and values will be formatted as a null-
      terminated string and written to this buffer. The buffer
      capacity must be at least 5025 characters.*/
 char*  regDump 
);    

/*! The firmware's trace buffer and related parameters will be
    retrieved from the PHY, and written to traceDump. The trace buffer
    can be post-processed by Aquantia to retrieve information useful
    when troubleshooting problems.
    Return codes:
    AQ_RET_DEBUGTRACE_FREEZE_TIMEOUT: Trace freeze request not
    acknowledged. traceDump will not contain valid trace buffer data.
    AQ_RET_DEBUGTRACE_UNFREEZE_TIMEOUT: Trace unfreeze request not
    acknowledged. traceDump will contain valid trace buffer data, but
    FW state may be unusual.*/
AQ_Retcode   AQ_API_PrintDebugTrace 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The trace parameters and buffer contents will be formatted as a
      null-terminated string and written to this buffer. The buffer
      capacity should be at least 18550 characters, though generally
      the trace dump will be much shorter than this.*/
 char*  traceDump 
);    

/*@}*/


/*******************************************************************
                        Diagnostics
*******************************************************************/

/*! \defgroup diagnostics Diagnostics
MDI diagnostic routines useful for troubleshooting problems with the cable
or board traces. */
/*@{*/


/*! This enumeration is used to describe the basic cable diagnostic
    status for a single pair.*/
typedef enum    
{    
  /*! No problems detected.*/
 AQ_API_BasicPairStatus_OK,   
  /*! The pair is shorted.*/
 AQ_API_BasicPairStatus_Short,   
  /*! The pair has lower than expected impedance.*/
 AQ_API_BasicPairStatus_LowMismatch,   
  /*! The pair has higher than expected impedance.*/
 AQ_API_BasicPairStatus_HighMismatch,   
  /*! The pair is open.*/
 AQ_API_BasicPairStatus_Open,   
  /*! The pair is crossed-over with pair A.*/
 AQ_API_BasicPairStatus_CrossoverA,   
  /*! The pair is crossed-over with pair B.*/
 AQ_API_BasicPairStatus_CrossoverB,   
  /*! The pair is crossed-over with pair C.*/
 AQ_API_BasicPairStatus_CrossoverC,   
  /*! The pair is crossed-over with pair D.*/
 AQ_API_BasicPairStatus_CrossoverD   
} AQ_API_BasicPairStatus;   

/*! This structure is used by the API to report the information
    obtained about a single pair by the PHY's basic cable diagnostic
    routine. While the basic cable diags routine is running, the link
    will be dropped. Note: the 40nm PHY firmware only the first
    reflection distance. The others will always be reported as 0.*/
typedef struct    
{    
   /*! Pair status reported by the basic cable diagnostic routine.*/
 AQ_API_BasicPairStatus   status;
   /*! Approximate distance, in meters, to the first of the four worst
       reflections recorded during the basic cable diagnostic
       routine.*/
 unsigned int  reflection_1_Distance; 
   /*! Approximate distance, in meters, to the second of the four
       worst reflections recorded during the basic cable diagnostic
       routine.*/
 unsigned int  reflection_2_Distance; 
   /*! Approximate distance, in meters, to the third of the four worst
       reflections recorded during the basic cable diagnostic
       routine.*/
 unsigned int  reflection_3_Distance; 
   /*! Approximate distance, in meters, to the fourth of the four
       worst reflections recorded during the basic cable diagnostic
       routine.*/
 unsigned int  reflection_4_Distance; 
} AQ_API_BasicPairResult;    

/*! This structure is used by the API to report the information
    obtained about the four pairs by the PHY's basic cable diagnostic
    routine.*/
typedef struct    
{    
   /*! The basic cable diagnostic results for pair A.*/
 AQ_API_BasicPairResult   pairAResult;
   /*! The basic cable diagnostic results for pair B.*/
 AQ_API_BasicPairResult   pairBResult;
   /*! The basic cable diagnostic results for pair C.*/
 AQ_API_BasicPairResult   pairCResult;
   /*! The basic cable diagnostic results for pair D.*/
 AQ_API_BasicPairResult   pairDResult;
} AQ_API_BasicCableDiagResults;    

/*! Instructs the PHY to begin collecting basic cable diagnostic
    information. The PHY's basic cable diagnostic routine will take
    several seconds to complete. Should be followed by a subsequent
    call to AQ_API_GetBasicCableDiagsResults to retrieve the results.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.*/
AQ_Retcode   AQ_API_RunBasicCableDiags 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port 
);    

/*! Retrieves the results of the PHY's basic cable dianostic routine.
    AQ_API_RunBasicCableDiags must have been called previously to
    start the diagnostic routine. The routine will take several
    seconds to complete. The routine has completed when this function
    returns 0. A return value of AQ_RET_CABLEDIAG_STILL_RUNNING
    indicates that the PHY is still performing the basic cable
    diagnostics.
    Return codes:
    AQ_RET_CABLEDIAG_BAD_PAIRSTATUS: An unexpected value was read from
    the PHY while collecting the diagnostic results. results will NOT
    contain valid diagnostic results, and should be ignored.
    AQ_RET_CABLEDIAG_STILL_RUNNING: The PHY is still performing its
    basic cable diagnostics routine. The caller should try again
    later. results will NOT contain valid diagnostic results, and
    should be ignored.
    */
AQ_Retcode   AQ_API_GetBasicCableDiagsResults 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! OUT: If the return code is 0, this structure will be filled out
      to indicate the results of the basic cable dianostic routine.*/
 AQ_API_BasicCableDiagResults*   results
);    

#define MAX_NUM_TDR_SAMPLES 1000    
/*! This structure is used by the API to report the TDR data obtained
    by the PHY's extended cable diagnostic routine, when transmitting
    on a particular pair. Includes the TDR data received on all four
    pairs.*/
typedef struct    
{    
   /*! The TDR data received on pair A.*/
 int16_t  pairA_TDRSamples[MAX_NUM_TDR_SAMPLES]; 
   /*! The number of samples recorded for pair A.*/
 unsigned int  pairA_numSamples; 
   /*! The TDR data received on pair B.*/
 int16_t  pairB_TDRSamples[MAX_NUM_TDR_SAMPLES]; 
   /*! The number of samples recorded for pair B.*/
 unsigned int  pairB_numSamples; 
   /*! The TDR data received on pair C.*/
 int16_t  pairC_TDRSamples[MAX_NUM_TDR_SAMPLES]; 
   /*! The number of samples recorded for pair C.*/
 unsigned int  pairC_numSamples; 
   /*! The TDR data received on pair D.*/
 int16_t  pairD_TDRSamples[MAX_NUM_TDR_SAMPLES]; 
   /*! The number of samples recorded for pair D.*/
 unsigned int  pairD_numSamples; 
} AQ_API_TDRPairResult;    

/*! This structure is used to report the TDR data obtained by the
    PHY's extended cable diagnostic routine. Includes the data
    recorded while transmitting on each of the four pairs.*/
typedef struct    
{    
   /*! If true, the TDR extended diags have been successfully
       performed while transmitting on pair A.*/
 AQ_boolean  pairAResultsCollected; 
   /*! The TDR data recorded while transmitting on pair A. Invalid if
       pairAResultsCollected is false.*/
 AQ_API_TDRPairResult   pairAResult;
   /*! If true, the TDR extended diags have been successfully
       performed while transmitting on pair B.*/
 AQ_boolean  pairBResultsCollected; 
   /*! The TDR data recorded while transmitting on pair B. Invalid if
       pairBResultsCollected is false.*/
 AQ_API_TDRPairResult   pairBResult;
   /*! If true, the TDR extended diags have been successfully
       performed while transmitting on pair C.*/
 AQ_boolean  pairCResultsCollected; 
   /*! The TDR data recorded while transmitting on pair C. Invalid if
       pairCResultsCollected is false.*/
 AQ_API_TDRPairResult   pairCResult;
   /*! If true, the TDR extended diags have been successfully
       performed while transmitting on pair D.*/
 AQ_boolean  pairDResultsCollected; 
   /*! The TDR data recorded while transmitting on pair D. Invalid if
       pairAResultsCollected is false.*/
 AQ_API_TDRPairResult   pairDResult;
} AQ_API_TDRCableDiagResults;    

/*! Instructs the PHY to begin collecting TDR cable diagnostic
    information. The PHY's extended cable diagnostic routine will take
    several seconds to complete. This function should be called only
    once, to kick off the diagnostic sequence, and should be followed
    by several subsequents calls to AQ_API_GetTDRCableDiagsResults to
    retrieve the results and proceed to the next pair.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    AQ_RET_CABLEDIAG_ALREADY_RUNNING: The port is already performing
    cable diagnostics. AQ_API_GetTDRCableDiagsResults should be called
    to retrieve the results.*/
AQ_Retcode   AQ_API_RunTDRCableDiags 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port 
);    

/*! Retrieves the results of the PHY's TDR cable dianostic routine.
    AQ_API_RunTDRCableDiags must have been called previously to start
    the diagnostic routine. Each time this function is called, the TDR
    data for transmitting on a single pair will be retrieved from the
    PHY, and the TDR diags for the next pair will be started. So, this
    function should be called at least four times after
    AQ_API_RunTDRCableDiags is called, once for each pair. A return
    code of AQ_RET_CABLEDIAG_STILL_RUNNING that diags are currently
    running.
    Return codes:
    AQ_RET_OK: Success: the PHY has completed the entire TDR extended
    cable diagnostics sequence, and the results argument has been
    populated with TDR data for transmitting on each of the four
    pairs.
    AQ_RET_CABLEDIAG_STARTED_PAIR_B: Success: TDR data for tx pair A
    has been recorded, and diags are now being run for tx pair B.
    AQ_RET_CABLEDIAG_STARTED_PAIR_C: Success: TDR data for tx pair B
    has been recorded, and diags are now being run for tx pair C.
    AQ_RET_CABLEDIAG_STARTED_PAIR_D: Success: TDR data for tx pair C
    has been recorded, and diags are now being run for tx pair D.
    AQ_RET_CABLEDIAG_STILL_RUNNING: The PHY is still performing its
    basic cable diagnostics routine. The caller should try again
    later. results will NOT contain valid diagnostic results, and
    should be ignored.
    AQ_RET_CABLEDIAG_RESULTS_ALREDY_COLLECTED: Error: The completion
    flag fields in results indicate that data for all four pairs has
    already been collected.
    AQ_RET_CABLEDIAG_BAD_NUM_SAMPLES: Error: The PHY did not record
    the expected number of TDR samples for some pair.
    AQ_RET_CABLEDIAG_REPORTEDPAIR_MISMATCH: Error: Mismatch between
    the tx pair indicated by the PHY and the completion flag fields in
    results.
    AQ_RET_CABLEDIAG_REPORTEDPAIR_OOR: Error: tx pair out of range.
    */
AQ_Retcode   AQ_API_GetTDRCableDiagsResults 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! OUT: This structure will be filled out to indicate the results
      of the TDR cable dianostic routine.*/
 AQ_API_TDRCableDiagResults*   results
);    

#define MAX_NUM_NOISE_PSD_SAMPLES 1024    
/*! This structure is used to report the noise PSD data obtained by
    the PHY's extended cable diagnostic routine. Includes the samples
    recorded for each of the four pairs.*/
typedef struct    
{    
   /*! If true, the noise PSD extended diags routine was run with the
       transmitter enabled.*/
 AQ_boolean  txEnabled; 
   /*! If true, the noise PSD extended diags have been successfully
       performed on pair A.*/
 AQ_boolean  pairAResultsCollected; 
   /*! The noise PSD samples recorded for pair A. Invalid if
       pairAResultsCollected is false.*/
 int16_t  pairA_NoisePSDSamples[MAX_NUM_NOISE_PSD_SAMPLES]; 
   /*! The number of samples stored in pairA_NoisePSDSamples. Invalid
       if pairAResultsCollected is false.*/
 unsigned int  pairA_numSamples; 
   /*! If true, the noise PSD extended diags have been successfully
       performed on pair B.*/
 AQ_boolean  pairBResultsCollected; 
   /*! The noise PSD samples recorded for pair B. Invalid if
       pairBResultsCollected is false.*/
 int16_t  pairB_NoisePSDSamples[MAX_NUM_NOISE_PSD_SAMPLES]; 
   /*! The number of samples stored in pairB_NoisePSDSamples. Invalid
       if pairBResultsCollected is false.*/
 unsigned int  pairB_numSamples; 
   /*! If true, the noise PSD extended diags have been successfully
       performed on pair C.*/
 AQ_boolean  pairCResultsCollected; 
   /*! The noise PSD samples recorded for pair C. Invalid if
       pairCResultsCollected is false.*/
 int16_t  pairC_NoisePSDSamples[MAX_NUM_NOISE_PSD_SAMPLES]; 
   /*! The number of samples stored in pairC_NoisePSDSamples. Invalid
       if pairCResultsCollected is false.*/
 unsigned int  pairC_numSamples; 
   /*! If true, the noise PSD extended diags have been successfully
       performed on pair D.*/
 AQ_boolean  pairDResultsCollected; 
   /*! The noise PSD samples recorded for pair D. Invalid if
       pairDResultsCollected is false.*/
 int16_t  pairD_NoisePSDSamples[MAX_NUM_NOISE_PSD_SAMPLES]; 
   /*! The number of samples stored in pairD_NoisePSDSamples. Invalid
       if pairDResultsCollected is false.*/
 unsigned int  pairD_numSamples; 
} AQ_API_NoisePSDCableDiagResults;    

/*! Instructs the PHY to begin collecting noise PSD cable diagnostic
    information, with or without the transmitter enabled. The PHY's
    extended cable diagnostic routine will take several seconds to
    complete. This function should be called only once, to kick off
    the diagnostic sequence, and should be followed by several
    subsequents calls to AQ_API_GetNoisePSDCableDiagsResults to
    retrieve the results and proceed to the next pair.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    AQ_RET_CABLEDIAG_ALREADY_RUNNING: The port is already performing
    cable diagnostics. AQ_API_GetNoisePSDCableDiagsResults should be
    called to retrieve the results.*/
AQ_Retcode   AQ_API_RunNoisePSDCableDiags 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! If true, the transmitter will be enabled while the PSD samples
      are collected.*/
 AQ_boolean  txEnable 
);    

/*! Retrieves the results of the PHY's noise PSD cable dianostic
    routine. AQ_API_RunNoisePSDCableDiags must have been called
    previously to start the diagnostic routine. Each time this
    function is called, the PSD data for a single pair will be
    retrieved from the PHY, and the noise PSD diags for the next pair
    will be started. So, this function should be called at least four
    times after AQ_API_RunNoisePSDCableDiags is called, once for each
    pair. A return code of AQ_RET_CABLEDIAG_STILL_RUNNINGindicates
    that diags are currently running.
    Return codes:
    AQ_RET_OK: Success: the PHY has completed the entire noise PSD
    extended cable diagnostics sequence, and the results argument has
    been populated with noise PSD data for transmitting on each of the
    four pairs.
    AQ_RET_CABLEDIAG_STARTED_PAIR_B: Success: noise PSD data for tx
    pair A has been recorded, and diags are now being run for tx pair
    B.
    AQ_RET_CABLEDIAG_STARTED_PAIR_C: Success: noise PSD data for tx
    pair B has been recorded, and diags are now being run for tx pair
    C.
    AQ_RET_CABLEDIAG_STARTED_PAIR_D: Success: noise PSD data for tx
    pair C has been recorded, and diags are now being run for tx pair
    D.
    AQ_RET_CABLEDIAG_STILL_RUNNING: The PHY is still performing its
    cable diagnostics routine. The caller should try again later.
    results will NOT contain valid diagnostic results, and should be
    ignored.
    AQ_RET_CABLEDIAG_RESULTS_ALREDY_COLLECTED: Error: The completion
    flag fields in results indicate that data for all four pairs has
    already been collected.
    AQ_RET_CABLEDIAG_BAD_NUM_SAMPLES: Error: The PHY did not record
    the expected number of noise PSD samples for some pair.
    AQ_RET_CABLEDIAG_REPORTEDPAIR_MISMATCH: Error: Mismatch between
    the tx pair indicated by the PHY and the completion flag fields in
    results.
    AQ_RET_CABLEDIAG_REPORTEDPAIR_OOR: Error: tx pair out of range.
    AQ_RET_CABLEDIAG_TXENABLE_MISMATCH: Error: tx-enabled flag
    reported by PHY does not match txEnable argument.
    */
AQ_Retcode   AQ_API_GetNoisePSDCableDiagsResults 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! Should match the txEnable argument of the prior call to
      AQ_API_RunNoisePSDCableDiags.*/
 AQ_boolean  txEnable, 
  /*! OUT: This structure will be filled out to indicate the results
      of the noise PSD cable dianostic routine.*/
 AQ_API_NoisePSDCableDiagResults*   results
);    

#define MAX_NUM_RFI_PSD_SAMPLES 1024    
/*! This structure is used to report the RFI PSD data obtained by the
    PHY's extended cable diagnostic routine.*/
typedef struct    
{    
   /*! The noise PSD samples recorded for the RFI channel. */
 int16_t  RFIPSDSamples[MAX_NUM_RFI_PSD_SAMPLES]; 
 unsigned int  RFInumSamples; 
} AQ_API_RFIPSDCableDiagResults;    

/*! Instructs the PHY to begin collecting noise PSD cable diagnostic
    information for the RFI (5th) channel. The PHY's extended cable
    diagnostic routine will take several seconds to complete. This
    function should be called only once, to kick off the diagnostic
    sequence, and should be followed by subsequents calls to
    AQ_API_GetRFIPSDCableDiagsResults to retrieve the results.
    Return codes:
    AQ_RET_UP_BUSY_TIMEOUT: The time limit was exceeded while waiting
    for the uP-busy flag to clear after writing a bit that triggers a
    uP-intensive operation.
    AQ_RET_CABLEDIAG_ALREADY_RUNNING: The port is already performing
    cable diagnostics. AQ_API_GetRFIPSDCableDiagsResults should be
    called to retrieve the results.*/
AQ_Retcode   AQ_API_RunRFIPSDCableDiags 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port 
);    

/*! Retrieves the results of the PHY's RFI PSD cable dianostic
    routine. AQ_API_RunRFIPSDCableDiags must have been called
    previously to start the diagnostic routine. A return code of
    AQ_RET_CABLEDIAG_STILL_RUNNING indicates that diags are currently
    running.
    Return codes:
    AQ_RET_OK: Success: the PHY has completed the entire RFI PSD
    extended cable diagnostics sequence, and the results argument has
    been populated with noise PSD data for transmitting on each of the
    four pairs.
    AQ_RET_CABLEDIAG_STILL_RUNNING: The PHY is still performing its
    cable diagnostics routine. The caller should try again later.
    results will NOT contain valid diagnostic results, and should be
    ignored.
    AQ_RET_CABLEDIAG_BAD_NUM_SAMPLES: Error: The PHY did not record
    the expected number of RFI PSD samples for some pair.
    AQ_RET_CABLEDIAG_REPORTEDPAIR_MISMATCH: Error: Mismatch between
    the tx pair indicated by the PHY and the completion flag fields in
    results.
    */
AQ_Retcode   AQ_API_GetRFIPSDCableDiagsResults 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! OUT: This structure will be filled out to indicate the results
      of the RFI PSD cable dianostic routine.*/
 AQ_API_RFIPSDCableDiagResults *   results
);    

/*@}*/


/*******************************************************************
                        SERDES Tuning
*******************************************************************/

/*! \defgroup sERDESTuning SERDES Tuning
Functions providing assistance in tuning the SERDES transmitters and
receivers during system integration. */
/*@{*/


/*! Prepares the SERDES receiver for the specified lane to perform Rx
    eye diagram measurements. After calling
    AQ_API_BeginSERDESRxEyeDiagram, calls to
    AQ_API_GetSERDESRxEyeMeasurement can be made.
    AQ_API_EndSERDESRxEyeDiagram should subsequently be called to
    return the receiver to its ordinary operating state.
    Compatibility: HHD PHYs only.
    Return codes:
    AQ_RET_OK: Success.
    AQ_RET_SERDESEYE_LANE_OOR: Error: Lane argument was outside the
    allowed range.
    AQ_RET_PIFMAILBOX_ERROR: Error: The PIF mailbox register indicated
    an error occurred.
    AQ_RET_PIFMAILBOX_TIMEOUT: Error: The PIF mailbox register did not
    indicate 'done' within the timeout period.*/
AQ_Retcode   AQ_API_BeginSERDESRxEyeDiagram 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The SERDES lane (0 through 3).*/
 const uint8_t  lane 
);    

/*! Returns the SERDES receiver for the specified lane to its ordinary
    operating state. Should always be called aftyer eye diagram
    measurements have been completed, regardless of success.
    Compatibility: HHD PHYs only.
    Return codes:
    AQ_RET_OK: Success.
    AQ_RET_SERDESEYE_LANE_OOR: Error: Lane argument was outside the
    allowed range.
    AQ_RET_PIFMAILBOX_ERROR: Error: The PIF mailbox register indicated
    an error occurred.
    AQ_RET_PIFMAILBOX_TIMEOUT: Error: The PIF mailbox register did not
    indicate 'done' within the timeout period.*/
AQ_Retcode   AQ_API_EndSERDESRxEyeDiagram 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The SERDES lane (0 through 3).*/
 const uint8_t  lane 
);    

#define AQ_API_SERDESEYE_GRIDSIZE_X 32    
#define AQ_API_SERDESEYE_GRIDSIZE_Y 64    
/*! Measures the number of errors observed at the specified X/Y
    coordinates of the eye diagram grid for the specified SERDES lane.
    AQ_API_BeginSERDESRxEyeDiagram must have been called prior to this
    function. The number of observed bits that were errored is
    returned in the numErrors parameter. The maximum number of bits
    that could be errored is returned in the maxErrors parameter.
    numErrors/maxErrors gives the error percentage. The (0,0)
    coordinate represents the upper-left corner of the eye diagram
    grid, and the (31, 63) coordinate represents the lower-right
    corner. The current system interface operating mode (e.g. XFI,
    SGMII) must be appropriate for eye diagram measurement prior to
    calling AQ_API_GetSERDESRxEyeMeasurement.
    Compatibility: HHD PHYs only.
    Return codes:
    AQ_RET_OK: Success.
    AQ_RET_SERDESEYE_BAD_SERDES_MODE: Error: The current system
    interface mode is not appropriate for performing eye measurements.
    AQ_RET_SERDESEYE_BAD_MEAS_COUNT: Error: The preconfigured
    measurement count was 0.
    AQ_RET_SERDESEYE_MEAS_TIMEOUT: Error: The SERDES receiver failed
    to indicate that it had finished performing the eye measurements
    within the alloted number of checks.
    AQ_RET_SERDESEYE_LANE_OOR: Error: Lane argument was outside the
    allowed range.
    AQ_RET_SERDESEYE_COORD_OOR: Error: x or y argument was outside the
    allowed range.
    AQ_RET_PIFMAILBOX_ERROR: Error: The PIF mailbox register indicated
    an error occurred.
    AQ_RET_PIFMAILBOX_TIMEOUT: Error: The PIF mailbox register did not
    indicate 'done' within the timeout period.*/
AQ_Retcode   AQ_API_GetSERDESRxEyeMeasurement 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The SERDES lane (0 through 3).*/
 const uint8_t  lane, 
  /*! The X coordinate of the eye diagram grid (0 through 31).*/
 const uint8_t  x, 
  /*! The Y coordinate of the eye diagram grid (0 through 63).*/
 const uint8_t  y, 
  /*! OUT: The number of observed bits that were errors.*/
 uint16_t *  numErrors, 
  /*! OUT: The number of observed bits.*/
 uint16_t *  maxErrors 
);    

/*! Prepares the SERDES receiver to perform Rx eye diagram
    measurements. After calling AQ_API_EUR_BeginSERDESRxEyeDiagram,
    calls to AQ_API_EUR_GetSERDESRxEyeMeasurement can be made.
    AQ_API_EUR_EndSERDESRxEyeDiagram should subsequently be called to
    return the receiver to its ordinary operating state.
    Compatibility: EUR PHYs only.
    Return codes:
    AQ_RET_OK: Success.
    AQ_RET_ERROR: Error: Invalid device.
    AQ_RET_PIFMAILBOX_ERROR: Error: The PIF mailbox register indicated
    an error occurred.
    AQ_RET_PIFMAILBOX_TIMEOUT: Error: The PIF mailbox register did not
    indicate 'done' within the timeout period.*/
AQ_Retcode   AQ_API_EUR_BeginSERDESRxEyeDiagram 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! OUT: The original level offset.*/
 uint8_t*  levelOffset, 
  /*! OUT: The original phase offset.*/
 uint8_t*  phaseOffset 
);    

/*! Returns the SERDES receiver for the specified lane to its ordinary
    operating state. Should always be called aftyer eye diagram
    measurements have been completed, regardless of success.
    Compatibility: EUR PHYs only.
    Return codes:
    AQ_RET_OK: Success.
    AQ_RET_ERROR: Error: Invalid device.
    AQ_RET_PIFMAILBOX_ERROR: Error: The PIF mailbox register indicated
    an error occurred.
    AQ_RET_PIFMAILBOX_TIMEOUT: Error: The PIF mailbox register did not
    indicate 'done' within the timeout period.*/
AQ_Retcode   AQ_API_EUR_EndSERDESRxEyeDiagram 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The original level offset.*/
 const uint8_t  levelOffset, 
  /*! The original phase offset.*/
 const uint8_t  phaseOffset 
);    

#define AQ_API_EUR_SERDESEYE_GRIDSIZE_X 64    
#define AQ_API_EUR_SERDESEYE_GRIDSIZE_Y 128    
/*! Measures the number of errors observed at the specified X/Y
    coordinates of the eye diagram grid.
    AQ_API_EUR_BeginSERDESRxEyeDiagram must have been called prior to
    this function. The number of observed bits that were errored is
    returned in the numErrors parameter. The maximum number of bits
    that could be errored is returned in the maxErrors parameter.
    numErrors/maxErrors gives the error percentage. The (0,0)
    coordinate represents the upper-left corner of the eye diagram
    grid, and the (31, 63) coordinate represents the lower-right
    corner. The current system interface operating mode (e.g. XFI,
    SGMII) must be appropriate for eye diagram measurement prior to
    calling AQ_API_EUR_GetSERDESRxEyeMeasurement.
    Compatibility: EUR PHYs only.
    Return codes:
    AQ_RET_OK: Success.
    AQ_RET_ERROR: Error: Invalid device.
    AQ_RET_SERDESEYE_COORD_OOR: Error: x or y argument was outside the
    allowed range.
    AQ_RET_PIFMAILBOX_ERROR: Error: The PIF mailbox register indicated
    an error occurred.
    AQ_RET_PIFMAILBOX_TIMEOUT: Error: The PIF mailbox register did not
    indicate 'done' within the timeout period.*/
AQ_Retcode   AQ_API_EUR_GetSERDESRxEyeMeasurement 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The original phase offset.*/
 const uint8_t  phaseOffset, 
  /*! The X coordinate of the eye diagram grid (0 through 31).*/
 const uint8_t  x, 
  /*! The Y coordinate of the eye diagram grid (0 through 63).*/
 const uint8_t  y, 
  /*! OUT: The number of observed bits that were errors.*/
 uint16_t*  numErrors, 
  /*! OUT: The number of observed bits.*/
 uint16_t*  maxErrors 
);    

/*! Measures the number of errors observed at the X/Y coordinates of
    the eye diagram grid with specified steps. This function is enough
    to obtain the eye diagram, AQ_API_EUR_BeginSERDESRxEyeDiagram and
    AQ_API_EUR_EndSERDESRxEyeDiagram must not have been called. The
    percentages of bits that were errored are returned in the
    numErrors parameter. The maximum number of bits that could be
    errored is returned in the maxErrors parameter. The (0,0)
    coordinate represents the upper-left corner of the eye diagram
    grid, and the (31, 63) coordinate represents the lower-right
    corner. The current system interface operating mode (e.g. XFI,
    SGMII) must be appropriate for eye diagram measurement prior to
    calling AQ_API_EUR_CaptureSERDESRxEyeDiagram.
    Compatibility: EUR PHYs only.
    Return codes:
    AQ_RET_OK: Success.
    AQ_RET_ERROR: Error: Invalid device.
    AQ_RET_SERDESEYE_COORD_OOR: Error. The buffer size is not enouth
    for specified step sizes.
    AQ_RET_PIFMAILBOX_ERROR: Error: The PIF mailbox register indicated
    an error occurred.
    AQ_RET_PIFMAILBOX_TIMEOUT: Error: The PIF mailbox register did not
    indicate 'done' within the timeout period.*/
AQ_Retcode   AQ_API_EUR_CaptureSERDESRxEyeDiagram 
(    
  /*! The target PHY port.*/
 AQ_API_Port*  port, 
  /*! The buffer for obtained error counters.*/
 uint16_t*  numErrors, 
  /*! The buffer for codes returned by every measurement.*/
 AQ_Retcode*  retCodes, 
  /*! The Y size of the buffer (not less than
      AQ_API_EUR_SERDESEYE_GRIDSIZE_Y for maximal resolution).*/
 const uint8_t  yBufferSize, 
  /*! The X size of the buffer (not less than
      AQ_API_EUR_SERDESEYE_GRIDSIZE_X for maximal resolution.*/
 const uint8_t  xBufferSize, 
  /*! The Y step of the grid.*/
 const uint8_t  yStepSize, 
  /*! The X step of the grid.*/
 const uint8_t  xStepSize, 
  /*! OUT: The number of points by Y.*/
 uint8_t*  yCount, 
  /*! OUT: The number of points by X.*/
 uint8_t*  xCount, 
  /*! OUT: The number of observed bits.*/
 uint16_t*  maxErrors 
);    

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
