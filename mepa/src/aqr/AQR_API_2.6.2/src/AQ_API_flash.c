/*AQ_API_flash.c*/

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

/************************************************************************************
*                     Copyright Aquantia Corp.
*                             Freeware
*
* Description:
*
*   This file contains the code for the API flash functions defined in AQ_API.h
*
************************************************************************************/


/*! \file
*   This file contains the code for the API flash functions defined in AQ_API.h
 */

#include <string.h>
#include <stdlib.h>

#include "AQ_API.h"
#include <AQ_User.h>
#include <AQ_RegMacro.h>
#include "AQ_PlatformRoutines.h"
#ifndef ATL_FLASH
  #include "AQ_RegMaps.h"
#endif
#include "AQ_ReturnCodes.h"
#include "AQ_Load.h"
#include "AQ_Flash_Internal.h"

#if defined(AQ_VERBOSE)
  #include <stdio.h>
#endif


#ifdef AQ_TIME_T_EXISTS
  #include <time.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*! The maximum number of polling cycles ever required before the FLASH interface is ready. */
#define AQ_FLASH_INTERFACE_MAX_POLL_COUNT 20

#ifdef ATL_FLASH
AQ_boolean suppressOutput_ = False;

uint64_t getSysTime();
#endif

/* REGDOC_START */

/**********************************************************************************************************************
*                                               FLASH Load
**********************************************************************************************************************/

/*! \defgroup flash FLASH Access
  @{
*/

/*! The table used to compute CRC's within the PHY. */
const uint16_t AQ_CRC16Table[256] = {0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
                                         0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
                                         0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
                                         0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
                                         0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
                                         0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
                                         0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
                                         0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
                                         0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
                                         0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
                                         0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
                                         0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
                                         0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
                                         0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
                                         0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
                                         0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
                                         0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
                                         0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
                                         0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
                                         0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
                                         0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
                                         0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
                                         0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
                                         0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
                                         0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
                                         0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
                                         0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
                                         0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
                                         0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
                                         0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
                                         0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
                                         0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0};

/*! Calculate CRC-16 on specified data */
uint16_t calculateCRC(const uint8_t *buf, uint32_t startByte, uint32_t stopByte)
{
  uint16_t crc16Calculated = 0x0000;
  uint32_t i;
  for (i = startByte; i < stopByte; i++)
  {
    crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ buf[i]];
  }
  return crc16Calculated;
}

/* Flash calculates CRC Dword by Dword using big endian format, so we have to do this too */
static uint16_t calculateDwordCRC(uint32_t *buf, uint32_t startByte, uint32_t stopByte)
{
  uint16_t crc16Calculated = 0x0000;
  uint32_t startDword = startByte / sizeof(uint32_t);
  uint32_t endDword = stopByte / sizeof(uint32_t);

  /* calculate CRC for all DWORDs (assumes data is DWORD aligned) */
  uint32_t i;
  for (i = startDword; i < endDword; i++)
  {
    uint32_t dword = buf[i];
    /* get 4 bytes of each dword and use them to calculate running crc total (start with MSB) */
    int byte_ct;
    for (byte_ct = sizeof(uint32_t) - 1; byte_ct >= 0; byte_ct--)
    {
      uint8_t byte = ((dword >> (byte_ct * 8)) & 0xFF);
      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ byte];
    }
  }

  return crc16Calculated;
}

static AQ_boolean verifyImageCrc(uint32_t * buf, uint32_t imageSizeBytes, AQ_API_Port* port)
{
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface)

  uint16_t mailBoxCrc, crc16Calculated;
  AQ_boolean correctImageCrc;

  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 1,
      /* REGDOC: Read register (HHD/APPIA/EUR: 1E.0100 + 1) */
      AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 1));
               /* REGDOC: Get local representation of bitfield (HHD/APPIA/EUR: 1E.0101.F:0) */
  mailBoxCrc = AQ_API_BitfieldOfLocalStruct(AQ_GlobalNvrInterface,
        globalNVR_Interface, nvrMailboxCrc);
  /* DWORD for both PHY and MAC NVR interfaces */
  crc16Calculated = calculateDwordCRC(buf, 0, imageSizeBytes);
  correctImageCrc = mailBoxCrc == crc16Calculated;
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf ("%s CRC for loaded flash image (mailBoxCrc == 0x%X and crc16Calculated == 0x%X)\n",
      (correctImageCrc ? "Correct" : "Incorrect"),
      mailBoxCrc, crc16Calculated);
#endif
  return correctImageCrc;
}

/*! This function performs the polling operation for the FLASH control
 * interface, and returns AQ_RET_FLASHINTF_READY when it is ready, or
 * AQ_RET_FLASHINTF_READINESS_TIMEOUT on a time-out */
unsigned int AQ_FLASH_InterfaceReady
(
    /*! The target PHY port.*/
  AQ_API_Port* port
)
{
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface)

  uint16_t i;


  /* poll the PHY FLASH (aka NVR) interface for readiness to start polling */
  i = 0;
  while (1)
  {
    AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0,
        /* REGDOC: Read register (HHD/APPIA/EUR: 1E.0100) */
        AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0));
        /* REGDOC: Get local representation of bitfield (HHD/APPIA/EUR: 1E.0100.8) */
    if (AQ_API_BitfieldOfLocalStruct(AQ_GlobalNvrInterface,
          globalNVR_Interface, nvrBusy) == 0) break;
    if (++i > AQ_FLASH_INTERFACE_MAX_POLL_COUNT) return AQ_RET_FLASHINTF_READINESS_TIMEOUT;  /* time out */
  }
  return AQ_RET_FLASHINTF_READY;
}


/*! This function is used to take control of the FLASH from the PHY.  It stores
 * the values that previously existed in the 4 registers that count:
 * - AQ_GlobalNvrInterface.u0.word_0
 * - AQ_GlobalNvrProvisioning.u0.word_0,
 * - AQ_GlobalNvrProvisioning.u1.word_1,
 * - AQ_GlobalControl.u1.word_1
 * It then stalls the processor, sets the address length override to allow
 * control of the address length, and sets the FLASH clock frequency. */
void AQ_TakeControlOfFLASH
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! OUT: A pointer to uint16_t for storing the state of AQ_GlobalNvrInterface.u0.word_0 */
  uint16_t *globalNVR_InterfacePrevious_word0,
    /*! OUT: A pointer to uint16_t for storing the state of AQ_GlobalNvrProvisioning.u0.word_0 */
  uint16_t *globalNVR_ProvisioningPrevious_word0,
    /*! OUT: A pointer to uint16_t for storing the state of AQ_GlobalNvrProvisioning.u1.word_1 */
  uint16_t *globalNVR_ProvisioningPrevious_word1,
    /*! OUT: A pointer to uint16_t for storing the state of AQ_GlobalControl.u1.word_1 */
  uint16_t *globalControlPrevious_word1,
    /*! Identifies whether processor stall should be executed. */
  AQ_boolean upStallRequired,
    /*! NVR clock divide. Clock frequency is divided by the NVR clock divide + 1.*/
  uint16_t clockDiv
)
{
  AQ_API_Variable(AQ_GlobalStandardControl_1)
  AQ_API_Variable(AQ_GlobalResetControl)

  AQ_API_DeclareLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning)
  AQ_API_DeclareLocalStruct(AQ_GlobalControl, globalControl)

  unsigned int i;

  /* disable the daisy-chain and enable the clock divider over-ride */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 2, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C452.0) */
  AQ_API_AssignBitfieldOfLocalStruct_DeviceRestricted(APPIA_HHD_EUR, AQ_GlobalNvrProvisioning,
      globalNVR_Provisioning, nvrDaisyChainDisable, 1);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C452.1) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning,
      globalNVR_Provisioning, nvrDaisyChainClockDivideOverride, 1);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450 + 2) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 2,
      AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 2));

  /* read the defaults to save for later, write the stall, then enable it */
  (*globalControlPrevious_word1) =
    /* REGDOC: Read register (HHD/APPIA/EUR: 1E.C000 + 1) */
    AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalControl, 1);
  (*globalNVR_ProvisioningPrevious_word0) =
    /* REGDOC: Read register (HHD/APPIA/EUR: 1E.C450) */
    AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0);
  (*globalNVR_ProvisioningPrevious_word1) =
    /* REGDOC: Read register (HHD/APPIA/EUR: 1E.C450 + 1) */
    AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 1);
  (*globalNVR_InterfacePrevious_word0) =
    /* REGDOC: Read register (HHD/APPIA/EUR: 1E.0100) */
    AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0);

  /* If you want to use NVR CRC control, reset it in that way */
     /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0100.C) */
  /* AQ_API_Set(port->PHY_ID, AQ_GlobalNvrInterface, resetNvrCrc, 1); */

  if (upStallRequired == True)
  {
    /* write the stall and enable it */
    AQ_API_AssignWordOfLocalStruct(globalControl, 1, 0x0000);
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C001.0) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalControl, globalControl, upRunStall, 1);
    /* REGDOC: Assign to local representation of bitfield (APPIA/HHD/EUR: 1E.C001.6) */
    AQ_API_AssignBitfieldOfLocalStruct_DeviceRestricted(APPIA_HHD_EUR, AQ_GlobalControl, globalControl, upRunStallOverride, 1);
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C000 + 1) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalControl, 1,
        AQ_API_WordOfLocalStruct(globalControl, 1));

    /* force a reset of the daisy-chain machinery */
    /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.C006.E) */
    AQ_API_Set(port->PHY_ID, AQ_GlobalResetControl, globalMMD_ResetDisable, 1);    /* lock out reset of register map */
    /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0000.F) */
    AQ_API_Set(port->PHY_ID, AQ_GlobalStandardControl_1, softReset, 0);            /* toggle soft reset */
    /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0000.F) */
    AQ_API_Set(port->PHY_ID, AQ_GlobalStandardControl_1, softReset, 1);
    /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0000.F) */
    AQ_API_Set(port->PHY_ID, AQ_GlobalStandardControl_1, softReset, 0);

    /* wait 100us:  given a 20 MHz MDIO with preamble suppression and a preset address pointer, one write delays
       a minimum of 32 * (1/20 MHz) = 1.6 us = ~64 writes.  Use the global scratchpad as it does nothing */
    for (i = 0; i < 64; i++)
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0300) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalMicroprocessorScratchPad, 0, 0x0000);

    /* re-enable the reset machinery for the register map */
    /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.C006.E) */
    AQ_API_Set(port->PHY_ID, AQ_GlobalResetControl, globalMMD_ResetDisable, 0);
  }

  /* set the clock speed on the SPI and set the address length override so we can control the FLASH */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 1, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C451.8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning,
      globalNVR_Provisioning, nvrAddressLengthOverride, 1);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C451.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning,
      globalNVR_Provisioning, nvrClockDivide, clockDiv);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450 + 1) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 1,
      AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 1));

  return;
}


/*! Release the PHY's control of the FLASH.  Rre-write the values that
 * previously were read from the 4 registers that count when
 * AQ_TakeControlOfFLASH was called:
 * - AQ_GlobalNvrInterface.u0.word_0
 * - AQ_GlobalNvrProvisioning.u0.word_0,
 * - AQ_GlobalNvrProvisioning.u1.word_1,
 * - AQ_GlobalControl.u1.word_1
 */
void AQ_ReturnControlOfFLASH
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! IN: A pointer to the value of AQ_GlobalNvrInterface.u0.word_0 that will be restored.*/
  uint16_t *globalNVR_InterfacePrevious_word0,
    /*! IN: A pointer to the value of AQ_GlobalNvrProvisioning.u0.word_0 that will be restored.*/
  uint16_t *globalNVR_ProvisioningPrevious_word0,
    /*! IN: A pointer to the value of AQ_GlobalNvrProvisioning.u1.word_1 that will be restored.*/
  uint16_t *globalNVR_ProvisioningPrevious_word1,
    /*! IN: A pointer to the value of AQ_GlobalControl.u1.word_1 that will be restored.*/
  uint16_t *globalControlPrevious_word1
)
{
  AQ_API_Variable_DeviceRestricted(APPIA_HHD_EUR, AQ_GlobalNvrProvisioning)


  /* restore the NVR provisioning */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0,
      *globalNVR_InterfacePrevious_word0);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450 + 1) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 1,
      *globalNVR_ProvisioningPrevious_word1);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0,
      *globalNVR_ProvisioningPrevious_word0);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C000 + 1) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalControl, 1,
      *globalControlPrevious_word1);

  /* re-enable the daisy-chain */
  /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.C452.0) */
  AQ_API_Set_DeviceRestricted(APPIA_HHD_EUR, port->PHY_ID, AQ_GlobalNvrProvisioning, nvrDaisyChainDisable ,0);

  return;
}


/*! Poll the FLASH and the FLASH interface to determine if the device is ready.
 * In order to do this, the user must provide the appropriate register
 * settings, mask, and polarity for the specific FLASH that is being polled. */
unsigned int AQ_FLASH_Ready (
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams
)
{
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface)

  uint16_t i;
  uint16_t statusRegister;
#ifdef AQ_TIME_T_EXISTS
  time_t startTime;
#else
  uint32_t count;
  uint16_t secondsCounter;
#endif


  /* poll the PHY FLASH (aka NVR) interface for readiness to start polling */
  if (AQ_FLASH_InterfaceReady(port) == AQ_RET_FLASHINTF_READINESS_TIMEOUT)
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

#ifdef AQ_TIME_T_EXISTS
  startTime = time (NULL);
#else
  /* set up the counter appropriately:  if the maxTime is zero, set the start to the limit, otherwise start at zero */
  if (flashParams->maxOperationTime) count = 0;
  else count = AQ_MDIO_READS_PER_SECOND;
  secondsCounter = 0;
#endif

  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->readStatusRegisterProv);
  while (1)
  {
    /* execute the status register instruction */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams->readStatusRegisterIF);

    /* poll the PHY NVR interface for readiness */
    i = 0;
    while (1)
    {
      AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0,
          /* REGDOC: Read register (HHD/APPIA/EUR: 1E.0100) */
          AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0));
          /* REGDOC: Get local representation of bitfield (HHD/APPIA/EUR: 1E.0100.8) */
      if (AQ_API_BitfieldOfLocalStruct(AQ_GlobalNvrInterface,
            globalNVR_Interface, nvrBusy) == 0) break;
      if (++i > AQ_FLASH_INTERFACE_MAX_POLL_COUNT) return AQ_RET_FLASH_READINESS_TIMEOUT;  /* time out */
    }

    /* read the status register */
                     /* REGDOC: Read register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 5) */
    statusRegister = AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalNvrInterface,
                            AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW));
    if (flashParams->readStatusRegisterPolarity)
    {
      /* busy when bit is zero */
      if ((statusRegister & flashParams->readStatusRegisterMask) != 0) break;
    }
    else
    {
      /* busy when bit is one */
      if ((statusRegister & flashParams->readStatusRegisterMask) == 0) break;
    }

  #ifdef AQ_TIME_T_EXISTS
    if ((time(NULL) - startTime) >= flashParams->maxOperationTime) return AQ_RET_FLASH_READINESS_TIMEOUT;  /* time out */
  #else
    /* Check if we have exceeded our alloted time.  Note that we increment by 4+i as we perform 4+i MDIO operations
       in this loop:
       2 Ops: AQ_API_WriteRegister (port->PHY_ID, AQ_GlobalNvrInterface, 0, readStatusRegisterIF) = Write address and data
       i Ops: AQ_API_ReadRegister (port->PHY_ID, AQ_GlobalNvrInterface, 0) = Read data (address already set)
       2 Ops: AQ_API_ReadRegister (port->PHY_ID, AQ_GlobalNvrInterface, 5) = Write address and data
    */
    if ((count += 4+i) > AQ_MDIO_READS_PER_SECOND)
    {
      if (++secondsCounter >= flashParams->maxOperationTime) return AQ_RET_FLASH_READINESS_TIMEOUT;  /* time out */
      count = 0;
    }
  #endif
  }

  return AQ_RET_FLASH_READY;
}


/*! Determine and return the FLASH type from the list of recognized devices
 * recognizes.
 * \pre Prior call to AQ_TakeControlOfFLASH() called prior to calling this function.
 * \retval AQ_RET_OK Success
 * \retval AQ_RET_FLASHINTF_READINESS_TIMEOUT Error: Timed out while waiting for the
 * FLASH interface to indicate readiness
 * \retval AQ_RET_FLASH_TYPE_UNKNOWN The FLASH type could not be determined
*/
AQ_Retcode AQ_API_DetermineFLASH_Type
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! OUT: a pointer to the FLASH type */
  AQ_API_FLASH *flashType,
    /*! OUT: a pointer to jedecId */
  uint32_t* jedecId
)
{
  AQ_API_Variable(AQ_GlobalNvrInterface)
  AQ_API_Variable_DeviceRestricted(APPIA_HHD_EUR, AQ_GlobalPinStatus)
  AQ_API_Variable_DeviceRestricted(APPIA, AQ_GlobalPrimaryStatus)

  AQ_API_DeclareLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface)
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning)

  uint16_t lsw;
  uint16_t msw;
  uint16_t deviceID;
  uint16_t manufacturerID;
  uint16_t bootLoad = 0;
  uint16_t primary = 0;
  uint16_t readDeviceID_IF;
  uint16_t readDeviceID_Prov;


  if (jedecId != NULL)
    *jedecId = 0;
  /* check if this is a daisy-chain slave, in which case there is no FLASH */
  switch (port->device)
  {
    case AQ_DEVICE_APPIA:
      /* REGDOC: Read bitfield (APPIA: 1E.C840.E:D) */
      AQ_API_Get_DeviceRestricted(APPIA, port->PHY_ID, AQ_GlobalPinStatus, mdioBootLoad, bootLoad);
      /* REGDOC: Read bitfield (APPIA: 1E.C851.0) */
      AQ_API_Get_DeviceRestricted(APPIA, port->PHY_ID, AQ_GlobalPrimaryStatus, primaryStatus, primary);
      if ((bootLoad == 0x3) || !primary)
      {
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = This (APPIA) PHY is a DC Slave\n");
    #endif
        *flashType = AQ_API_F_DaisyChainSlave;
        return AQ_RET_FLASH_TYPE_UNKNOWN;
      }
      break;

    case AQ_DEVICE_HHD:
    case AQ_DEVICE_EUR:
      /* REGDOC: Read bitfield (HHD/EUR: 1E.C840.D) */
      AQ_API_Get_DeviceRestricted(HHD_EUR, port->PHY_ID, AQ_GlobalPinStatus, dcMasterN, bootLoad);
      if (bootLoad == 0x1)
      {
      #ifdef AQ_VERBOSE
        #ifdef ATL_FLASH
        if (False == suppressOutput_)
        #endif
          printf("FLASH type = This (HHD/EUR) PHY is a DC Slave\n");
      #endif
        *flashType = AQ_API_F_DaisyChainSlave;
        return AQ_RET_FLASH_TYPE_UNKNOWN;
      }
      break;
  }

  /*------------------------------------- Determine the FLASH type --------------------------------------------------*/
  /* Note: the PHY is controlled primarily through word_0 of AQ_GlobalNvrInterface and
     AQ_GlobalNvrProvisioning.  Thus to simplify programming, default values for these two words for all desired
     operations are pre-calculated and stored in the appropriate variables.  To use them, the provisioning word is
     written first, followed by the interface word.  Then after the FLASH is ready any data can be read and a new
     operation performed. */


  /*------------------------------------- Atmel AT25F512A  -----------------------------------------------------------*/

  /* read device ID - this is a legacy part, and only supplies a single byte device ID*/
  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 2);
  readDeviceID_Prov = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, 0x15);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  readDeviceID_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  /* poll the PHY NVR interface for readiness to start */
  if (AQ_FLASH_InterfaceReady(port) == AQ_RET_FLASHINTF_READINESS_TIMEOUT)
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

  /* execute the Device ID read operation */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, readDeviceID_Prov);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, readDeviceID_IF);

  /* poll the PHY FLASH interface for readiness to continue */
  if (AQ_FLASH_InterfaceReady(port) == AQ_RET_FLASHINTF_READY)
  {
    /* read the device ID */
    /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
    AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, manufacturerID);
    if (jedecId != NULL)
      *jedecId = manufacturerID;
    deviceID = manufacturerID >> 8;
    manufacturerID &= 0xFF;

    /* check for match */
    if ((manufacturerID == 0x1F) && (deviceID == 0x65))
    {
      /* match is confirmed: exit */
      *flashType = AQ_API_F_AT25F512A;
  #ifdef AQ_VERBOSE
    #ifdef ATL_FLASH
    if (False == suppressOutput_)
    #endif
      printf("FLASH type = Atmel AT25F512A\n");
  #endif
      return AQ_RET_OK;
    }
  }
  else
  {
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf("FLASH interface ready timeout while trying to read the FLASH device ID (Atmel AT25F512A style read).\n");
#endif
    *flashType = AQ_API_F_Indeterminate;
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;
  }


  /*------------------------------------- Others ----------------------------------------------*/

  /* read device ID */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 4);            /* newer devices use 2-byte Device ID, followed by optional Extended Device ID */
  readDeviceID_Prov = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, 0x9F);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  readDeviceID_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  /* poll the PHY NVR interface for readiness to start */
  if (AQ_FLASH_InterfaceReady (port) != AQ_RET_FLASHINTF_READY)
  {
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf("FLASH interface ready timeout while preparing to read the FLASH device ID.\n");
#endif
    *flashType = AQ_API_F_Indeterminate;
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;
  }

  /* execute the Device ID read operation */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, readDeviceID_Prov);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, readDeviceID_IF);

  /* poll the PHY FLASH interface for readiness to continue */
  if (AQ_FLASH_InterfaceReady (port) == AQ_RET_FLASHINTF_READY)
  {
    /* read the device ID - the first byte (Manufacturer ID) read out goes into LSW[7:0],
       the second (DeviceID MSB) into LSW[15:8], and the third (Device ID LSB) into MSW[7:0] */
    /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
    AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, lsw);
    /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0104.F:0) */
    AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW, msw);

    if (jedecId != NULL)
      *jedecId = ((uint32_t)msw) << 16 | lsw;
    deviceID = (lsw & 0xFF00) | (msw & 0xFF);
    manufacturerID = lsw & 0xFF;

    /* check for match */
    if (manufacturerID == 0x20)
    {
      /* ST / Numonyx - use full 16-bit Device ID */
      if (deviceID == 0x2010)
      {
        /* 512K bit - match is confirmed: exit */
        *flashType = AQ_API_F_M25P05A;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Numonyx M25P05-A\n");
    #endif
        return AQ_RET_OK;
      }
      else if (deviceID == 0x2013)
      {
        /* 4M bit - match is confirmed: exit */
        *flashType = AQ_API_F_M25P40;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Numonyx M25P40\n");
    #endif
        return AQ_RET_OK;
      }
    }
    else if (manufacturerID == 0xC2)
    {
      /* Macronix - use full 16-bit Device ID */
      if (deviceID == 0x2013)
      {
        /* 4M bit - match is confirmed: exit */
        *flashType = AQ_API_F_MX25V400;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Macronix MX25V400XX\n");
    #endif
        return AQ_RET_OK;
      }
      else if (deviceID == 0x2313)
      {
        /* 4M bit - match is confirmed: exit */
        *flashType = AQ_API_F_MX25V4035F;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Macronix MX25V4035F\n");
    #endif
        return AQ_RET_OK;
      }
      else if (deviceID == 0x2016)
      {
        /* 32M bit (4M byte) - match is confirmed: exit */
        *flashType = AQ_API_F_MX25L32;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Macronix MX25L32\n");
    #endif
        return AQ_RET_OK;
      }
    }
    else if (manufacturerID == 0xEF)
    {
      /* Winbond - use full 16-bit Device ID */
      if (deviceID == 0x4016)
      {
        /* 32M bit (4M byte) - match is confirmed: exit */
        *flashType = AQ_API_F_W25Q32;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Winbond W25Q32\n");
    #endif
        return AQ_RET_OK;
      }
      if (deviceID == 0x6015)
      {
        /* 16M bit (2M byte) - match is confirmed: exit */
        *flashType = AQ_API_F_W25Q16DW;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Winbond W25Q16DW\n");
    #endif
        return AQ_RET_OK;
      }
      if (deviceID == 0x3013)
      {
        /* 4M bit (512K byte) - match is confirmed: exit */
        *flashType = AQ_API_F_W25X40;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Winbond W25X40\n");
    #endif
        return AQ_RET_OK;
      }
    }
    else if (manufacturerID == 0x01)
    {
      /* Cypress - use full 16-bit Device ID */
      if (deviceID == 0x4016)
      {
        /* 32M bit (4M byte) - match is confirmed: exit */
        *flashType = AQ_API_F_S25FL132K;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Cypress S25FL132K\n");
    #endif
        return AQ_RET_OK;
      }
    }
    else if (manufacturerID == 0x1F)
    {
      /* Atmel - use first 8-bits of Device ID, as remainder is manufacturing specific */
      deviceID >>= 8;
      if (deviceID == 0x24)
      {
        /* 4M bit - match is confirmed: exit */
        if (((msw >> 8) & 0xFF) == 0x00)
        {
          *flashType = AQ_API_F_AT45DB041D;
      #ifdef AQ_VERBOSE
        #ifdef ATL_FLASH
        if (False == suppressOutput_)
        #endif
          printf("FLASH type = Atmel AT45DB041D\n");
      #endif
        }
        else
        {
          *flashType = AQ_API_F_AT45DB041E;
      #ifdef AQ_VERBOSE
        #ifdef ATL_FLASH
        if (False == suppressOutput_)
        #endif
          printf("FLASH type = Atmel AT45DB041E\n");
      #endif
        }
        return AQ_RET_OK;
      }
      else if (deviceID == 0x27)
      {
        /* 32M bit (4M byte) - match is confirmed: exit */
        *flashType = AQ_API_F_AT45DB321E;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Atmel AT45DB321E\n");
    #endif
        return AQ_RET_OK;
      }
      else if (deviceID == 0x43)
      {
        /* 2M bit - match is confirmed: exit */
        *flashType = AQ_API_F_AT25DF021A;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Atmel AT25DF021A\n");
    #endif
        return AQ_RET_OK;
      }
      else if (deviceID == 0x44)
      {
        /* 4M bit - match is confirmed: exit */
        *flashType = AQ_API_F_AT25DF041A;
    #ifdef AQ_VERBOSE
      #ifdef ATL_FLASH
      if (False == suppressOutput_)
      #endif
        printf("FLASH type = Atmel AT25DF041A\n");
    #endif
        return AQ_RET_OK;
      }
    }

    /* Device not recognized or no device present */
    *flashType = AQ_API_F_Indeterminate;
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf("FLASH type = Unknown; manufacturerID = 0x%x; deviceID = 0x%x\n", manufacturerID, deviceID);
#endif
    return AQ_RET_FLASH_TYPE_UNKNOWN;

  }
  else
  {
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf("FLASH interface ready timeout while trying to read the FLASH device ID (standard style read).\n");
#endif
    *flashType = AQ_API_F_Indeterminate;
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;
  }
}


/*! Takes control of the FLASH prior to calling, calls
 * AQ_API_DetermineFLASH_Type, and returns control of the FLASH.
 * \retval AQ_RET_OK Success
 * \retval AQ_RET_FLASHINTF_READINESS_TIMEOUT Error: Timed out while waiting for the
 * FLASH interface to indicate readiness
 * \retval AQ_RET_FLASH_TYPE_UNKNOWN The FLASH type could not be determined
*/
AQ_Retcode AQ_API_DetermineFLASH_TypeStandalone
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! OUT: A pointer to the FLASH type */
  AQ_API_FLASH *flashType
)
{
  uint16_t globalNVR_InterfacePrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word1;
  uint16_t globalControlPrevious_word1;
  AQ_Retcode retval;


  /* take control of the FLASH, determine the type, and return control of the FLASH */
  AQ_TakeControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1, True, AQ_FLASH_NVR_CLOCK_DIVIDE);
  retval = AQ_API_DetermineFLASH_Type(port, flashType, NULL);
  AQ_ReturnControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1);

  return retval;
}


/*! Determine/construct the parameters and command words appropriately
 * for the specific FLASH type
 * \retval AQ_RET_OK Success
 * \retval AQ_RET_FLASH_TYPE_BAD The FLASH parameters and command words
 * could not be determined/constructed for the specific FLASH type */
AQ_Retcode AQ_API_GetFlashParametersForKnownFLASH
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! The FLASH type */
  AQ_API_FLASH flashType,
  AQ_API_FlashParams *flashParams      /*!< OUT */
)
{
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface)
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning)


  flashParams->flashType = flashType;
  /* Initialize the FLASH parameters so that no compiler uninitialized errors are generated */
  flashParams->chipEraseOpcode = 0x62;
  flashParams->writeEnableOpcode = 0x06;
  flashParams->writeStatusOpcode = 0x01;
  flashParams->disableProtData = 0x00;
  flashParams->readStatusOpcode = 0x05;
  flashParams->readStatusRegisterMask = 0x01;
  flashParams->readStatusRegisterPolarity = 0;
  flashParams->readOpcode = 0x03;
  flashParams->programOpcode = 0x02;
  flashParams->pageSize = 0x80;
  /* Followed 6 fields are determined only for AQ_API_F_AT45DB041D_E, AQ_API_F_AT45DB321E,
     AQ_API_F_W25Q16DW, AQ_API_F_W25Q32 and AQ_API_F_MX25L32 now. */
  flashParams->pageErasePageCount = 0;   /* number of pages in page erase area
                                            0 - not supported, 1 - supported (only AT45DB now) */
  flashParams->sectorErasePageCount = 0; /* number of pages in sector erase area
                                            @note Adesto (Atmel) names smaller erasable area "block"
                                              and larger erasable area - "sector", while other
                                              flash manufacturers usually call smaller erasable area "sector"
                                              and larger erasable area - "block".
                                            We use common practice and sector means smaller erasable area */
  flashParams->blockAdditionalErasePageCount = 0;/* number of pages in block additional erasable area
                                                    0 - not supported, 1 - supported (only W25Q32 now; MX25L3233F also supports,
                                                    but we can't differ it from MX25L3206E which does not support) */
  flashParams->blockErasePageCount = 0;          /* number of pages in block erasable area */
  flashParams->sectorEraseOpcode = 0x00;
  flashParams->blockEraseOpcode = 0x00;
  flashParams->maxOperationTime = 10;     /* The maximum operation time in seconds.  The estimated maximum time is 3 */
  flashParams->writeEnableIF = 0x00;
  flashParams->writeEnableProv = 0x00;
  flashParams->chipEraseIF = 0x00;
  flashParams->chipEraseProv = 0x00;
  flashParams->disableProtIF = 0x00;
  flashParams->disableProtProv = 0x00;
  flashParams->readStatusRegisterIF = 0x00;
  flashParams->readStatusRegisterProv = 0x00;
  flashParams->nonburstRead4_IF = 0x00;
  flashParams->nonburstRead4_Prov = 0x00;
  flashParams->burstRead4_IF = 0x00;
  flashParams->burstRead4_Prov = 0x00;
  flashParams->burstWrite4_IF = 0x00;
  flashParams->burstWrite4_Prov = 0x00;
  flashParams->read1_IF = 0x00;
  flashParams->read1_Prov = 0x00;
  flashParams->endBurst_IF = 0x00;
  flashParams->execOp_IF = 0x00;
  flashParams->flashSize = 0x00;

  /* set the FLASH parameters according to the FLASH type */
  switch (flashType)
  {
    case AQ_API_F_AT25F512A:
      /* Atmel 64K */
      flashParams->chipEraseOpcode = 0x62;
      flashParams->writeStatusOpcode = 0x01;
      flashParams->disableProtData = 0x00;
      flashParams->writeEnableOpcode = 0x06;
      flashParams->readStatusOpcode = 0x05;
      flashParams->readStatusRegisterMask = 0x01;
      flashParams->readStatusRegisterPolarity = 0;
      flashParams->readOpcode = 0x03;
      flashParams->programOpcode = 0x02;
      flashParams->pageSize = 0x80;       /* 128 */
      flashParams->maxOperationTime = 10;  /* Maximum time should be 2.2s */
      flashParams->flashSize = 0x10000;    /* 64K */
      break;

    case AQ_API_F_AT45DB041D:
    case AQ_API_F_AT45DB041E:
      /* Atmel smart (Adesto) 512KB = 4Mb */
      flashParams->chipEraseOpcode = 0xC7;
      flashParams->readStatusOpcode = 0xD7;
      flashParams->readStatusRegisterMask = 0x80;
      flashParams->readStatusRegisterPolarity = 1;
      flashParams->readOpcode = 0x03;
    #ifdef AQ_FLASH_ADESTO_FULL_ERASE
      flashParams->programOpcode = 0x02; /* AQ_API_F_OPCODE_AT45DB_PAGE_PROGRAM */
    #else
      flashParams->programOpcode = 0x82;   /* using buffer write with direct program and erase */
    #endif
      flashParams->pageSize = 0x100;       /* 256 */
      flashParams->pageErasePageCount = 1;
      flashParams->sectorErasePageCount = 8;
      flashParams->blockAdditionalErasePageCount = 0;
      flashParams->blockErasePageCount = 256;
      flashParams->sectorEraseOpcode = 0x50;
      flashParams->blockEraseOpcode = 0x7C;
      flashParams->maxOperationTime = 17;   /* Maximum time should be 35 ms */
      flashParams->flashSize = 0x80000;    /* 512K */
      break;

    case AQ_API_F_AT45DB321E:
      /* Atmel smart 4MB = 32Mb */
      flashParams->chipEraseOpcode = 0xC7;
      flashParams->readStatusOpcode = 0xD7;
      flashParams->readStatusRegisterMask = 0x80;
      flashParams->readStatusRegisterPolarity = 1;
      flashParams->readOpcode = 0x03;
    #ifdef AQ_FLASH_ADESTO_FULL_ERASE
      flashParams->programOpcode = 0x02; /* AQ_API_F_OPCODE_AT45DB_PAGE_PROGRAM */
    #else
      flashParams->programOpcode = 0x82;   /* using buffer write with direct program and erase */
    #endif
      flashParams->pageSize = 0x200;       /* 512 */
      flashParams->pageErasePageCount = 1;
      flashParams->sectorErasePageCount = 8;
      flashParams->blockAdditionalErasePageCount = 0;
      flashParams->blockErasePageCount = 128;
      flashParams->sectorEraseOpcode = 0x50;
      flashParams->blockEraseOpcode = 0x7C;
      flashParams->maxOperationTime = 80;   /* Maximum time should be 35 ms */
      flashParams->flashSize = 0x400000;    /* 4MB */
      break;

    case AQ_API_F_M25P05A:
      /* ST 64K */
      flashParams->chipEraseOpcode = 0xC7;
      flashParams->writeStatusOpcode = 0x01;
      flashParams->disableProtData = 0x00;
      flashParams->writeEnableOpcode = 0x06;
      flashParams->readStatusOpcode = 0x05;
      flashParams->readStatusRegisterMask = 0x01;
      flashParams->readStatusRegisterPolarity = 0;
      flashParams->readOpcode = 0x03;
      flashParams->programOpcode = 0x02;
      flashParams->pageSize = 0x100;       /* 256 */
      flashParams->maxOperationTime = 10;   /* Maximum time should be 6s */
      flashParams->flashSize = 0x10000;    /* 64K */
      break;

    case AQ_API_F_AT25DF021A:
      /* Quasi-generic 256Kbyte */
      flashParams->chipEraseOpcode = 0xC7;
      flashParams->writeStatusOpcode = 0x01;
      flashParams->disableProtData = 0x00;
      flashParams->writeEnableOpcode = 0x06;
      flashParams->readStatusOpcode = 0x05;
      flashParams->readStatusRegisterMask = 0x01;
      flashParams->readStatusRegisterPolarity = 0;
      flashParams->readOpcode = 0x03;
      flashParams->programOpcode = 0x02;
      flashParams->pageSize = 0x100;       /* 256 */
      flashParams->maxOperationTime = 10;
      flashParams->flashSize = 0x40000;    /* 256K */
      break;

    case AQ_API_F_AT25DF041A:
    case AQ_API_F_M25P40:
    case AQ_API_F_MX25V400:
    case AQ_API_F_MX25V4035F:
    case AQ_API_F_W25X40:
      /* Quasi-generic 512Kbyte */
      flashParams->chipEraseOpcode = 0xC7;
      flashParams->writeStatusOpcode = 0x01;
      flashParams->disableProtData = 0x00;
      flashParams->writeEnableOpcode = 0x06;
      flashParams->readStatusOpcode = 0x05;
      flashParams->readStatusRegisterMask = 0x01;
      flashParams->readStatusRegisterPolarity = 0;
      flashParams->readOpcode = 0x03;
      flashParams->programOpcode = 0x02;
      flashParams->pageSize = 0x100;       /* 256 */
      flashParams->maxOperationTime = 10;   /* AQ_API_F_MX25V4005C is 7.5s and AQ_API_F_W25X40 is 4s,
                                               the rest are 10s */
      flashParams->flashSize = 0x80000;    /* 512K */
      break;

    case AQ_API_F_MX25L32:
    case AQ_API_F_W25Q32:
    case AQ_API_F_S25FL132K:
      /* Quasi-generic 4Mbyte */
      flashParams->chipEraseOpcode = 0xC7;
      flashParams->writeStatusOpcode = 0x01;
      flashParams->disableProtData = 0x00;
      flashParams->writeEnableOpcode = 0x06;
      flashParams->readStatusOpcode = 0x05;
      flashParams->readStatusRegisterMask = 0x01;
      flashParams->readStatusRegisterPolarity = 0;
      flashParams->readOpcode = 0x03;
      flashParams->programOpcode = 0x02;
      flashParams->pageSize = 0x100;       /* 256 */
      flashParams->pageErasePageCount = 0;
      flashParams->sectorErasePageCount = 16;
      flashParams->blockAdditionalErasePageCount = flashType == AQ_API_F_W25Q32 ? 128 : 0;
      flashParams->blockErasePageCount = 256;
      flashParams->sectorEraseOpcode = 0x20;
      flashParams->blockEraseOpcode = 0xD8;
      flashParams->maxOperationTime = 50;   /* AQ_API_F_W25Q32 is 50s, AQ_API_F_MX25L32 is 30 - 40s */
      flashParams->flashSize = 0x200000;    /* 4M */
      break;

    case AQ_API_F_W25Q16DW:
      /* Quasi-generic 2Mbyte */
      flashParams->chipEraseOpcode = 0xC7;
      flashParams->writeStatusOpcode = 0x01;
      flashParams->disableProtData = 0x00;
      flashParams->writeEnableOpcode = 0x06;
      flashParams->readStatusOpcode = 0x05;
      flashParams->readStatusRegisterMask = 0x01;
      flashParams->readStatusRegisterPolarity = 0;
      flashParams->readOpcode = 0x03;
      flashParams->programOpcode = 0x02;
      flashParams->pageSize = 0x100;       /* 256 */
      flashParams->pageErasePageCount = 0;
      flashParams->sectorErasePageCount = 16;
      flashParams->blockAdditionalErasePageCount = 128;
      flashParams->blockErasePageCount = 256;
      flashParams->sectorEraseOpcode = 0x20;
      flashParams->blockEraseOpcode = 0xD8;
      flashParams->maxOperationTime = 10;   /* AQ_API_F_W25Q16DW is 10s */
      flashParams->flashSize = 0x200000;    /* 2M */
      break;

    case AQ_API_F_DaisyChainSlave:
    case AQ_API_F_Indeterminate:
      return AQ_RET_FLASH_TYPE_BAD;
  }

  /*------------------------------------- Set up the command words -------------------------------------------------*/
  /* Note: the PHY is controlled primarily through word_0 of AQ_GlobalNvrInterface and
     AQ_GlobalNvrProvisioning.  Thus to simplify programming, default values for these two words for all desired
     operations are pre-calculated and stored in the appropriate variables.  To use them, the provisioning word is
     written first, followed by the interface word.  Then after the FLASH is ready any data ca be read and a new
     operation performed. */
  /* Description: This is done to streamline the execution of the various commands and limit the read - modify write
     operations by precomputing the two words that always change from command to command.  Note that the series of
     bytes that are sent are:  opcode, 0-4 address bytes (read mode), 1-4 data bytes (write mode).  Thus is you are
     sending an opcode followed by 0-4 address bytes, you use read mode.  Only if you have to send 5 or more bytes
     do you use write mode. */

  if ((flashType != AQ_API_F_AT45DB041D) && (flashType != AQ_API_F_AT45DB041E) && (flashType != AQ_API_F_AT45DB321E))
  {
    /* disable protection */
    AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->writeStatusOpcode);
       /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
    /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0); */
       /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
    /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read, as we only need one address byte (which is sent after the read) */
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
    flashParams->disableProtIF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

    AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 1);
       /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
    /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 0);
    flashParams->disableProtProv = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

    /* write enable */
    AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->writeEnableOpcode);
       /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
    /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0); */
       /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
    /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
    flashParams->writeEnableIF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

    AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
       /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
    /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 0); */
       /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
    /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
       /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
    /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 0); */
    flashParams->writeEnableProv = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);
  }

  /* chip erase */
  /* will not be used in AQ_API_WriteAndVerifyFlashImage() if AQ_FLASH_ADESTO_FULL_ERASE is not defined,
     but set up it anaway for standalone flash erase. */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->chipEraseOpcode);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  flashParams->chipEraseIF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
  if ((flashType == AQ_API_F_AT45DB041D) || (flashType == AQ_API_F_AT45DB041E) || (flashType == AQ_API_F_AT45DB321E))
  {
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 3);
  }
  else
  {
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 0); */
  }
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 0); */
  flashParams->chipEraseProv = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  /* read status register */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->readStatusOpcode);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  flashParams->readStatusRegisterIF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 1);
  flashParams->readStatusRegisterProv = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  /* burst read 4 bytes */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->readOpcode);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 1);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  flashParams->burstRead4_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 3);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 4);
  flashParams->burstRead4_Prov = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  /* non-burst read 4 bytes */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->readOpcode);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  flashParams->nonburstRead4_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);
  flashParams->nonburstRead4_Prov = flashParams->burstRead4_Prov;

  /* burst write 4 bytes */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->programOpcode);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 1);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 1);       /* 1 = write */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  flashParams->burstWrite4_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 3);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 4);
  flashParams->burstWrite4_Prov = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  /* read 1 byte */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->readOpcode);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  flashParams->read1_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 3);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 1);
  flashParams->read1_Prov = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  /* turn off burst write mode */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->programOpcode);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 1);       /* 1 = write */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 0);
  flashParams->endBurst_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  /* execute operation at the end of writing a page */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, flashParams->programOpcode);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 1);       /* 1 = write */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  flashParams->execOp_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  /* Set up for 256/512 byte mode programming.  Send the sequence 0x3D, 0x2A, 0x80, 0xA6 as Opcode, followed by a
   3 byte address, and then wait until done.  Note this is done as a read, as address is sent first */
  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, 0x3D);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, 0); */       /* 0 = read */
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  flashParams->set256_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, 3);
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, 0); */
     /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  /* AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 0); */
  flashParams->set256_Prov = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  return AQ_RET_OK;
}

/* Construct command words by specified parameters */
void AQ_API_SetupFlashCommandWords
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
  uint16_t opcode,
  uint16_t burstMode,     /* 1 = burst operation */
  uint16_t writeMode,     /* 1 = write */
  uint16_t addressLength,
  uint16_t dummyLength,
  uint16_t dataLength,
  uint16_t* wordIF,       /*!< OUT the 16-bit setting for AQ_GlobalNvrInterface.u0.word_0 */
  uint16_t* wordProv      /*!< OUT the 16-bit setting for AQ_GlobalNvrProvisioning.u0.word_0 */
)
{
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface)
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning)

  AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, opcode);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrBurst, burstMode);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.E) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrWriteMode, writeMode);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 1);
  *wordIF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.1:0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrAddressLength, addressLength);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.6:4) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDummyLength, dummyLength);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, dataLength);
  *wordProv = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);
}

/* Execute specified operation */
AQ_Retcode AQ_API_ExecuteNvrOperation
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams,
  const uint16_t wordIF,
  const uint16_t wordProv,
  uint32_t* address
)
{
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, wordProv);
  if (address != NULL)
  {
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 2) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
            AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressMSW), (((*address) >> 16) & 0xFF)); /* nvrAddressMSW */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
            AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW), ((*address) & 0xFFFF));       /* nvrAddressLSW */
  }
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, wordIF);

  if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
    return AQ_RET_FLASH_READINESS_TIMEOUT;
  return AQ_RET_OK;
}

/* Read status register by specified command */
AQ_Retcode AQ_API_GetStatusRegister_Common
(
  AQ_API_Port* port,
  const uint16_t wordIF,
  const uint16_t wordProv,
  uint16_t* statusRegister
)
{
  /* make sure the interface is ready */
  if (AQ_FLASH_InterfaceReady(port) != AQ_RET_FLASHINTF_READY)
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

  /* execute the read status register instruction */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, wordProv);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, wordIF);

  /* wait until the interface is ready */
  if (AQ_FLASH_InterfaceReady(port) != AQ_RET_FLASHINTF_READY)
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

  /* read the status register */
                    /* REGDOC: Read register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 5) */
  *statusRegister = AQ_API_ReadRegister(port->PHY_ID, AQ_GlobalNvrInterface,
                          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW));

  return AQ_RET_OK;
}

/* Read 16bit-width status register */
AQ_Retcode AQ_API_GetStatusRegister_16
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams,
  uint16_t* statusRegister
)
{
  AQ_API_DeclareLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning)
  uint16_t readStatusRegisterProv;

  AQ_API_AssignWordOfLocalStruct(globalNVR_Provisioning, 0, flashParams->readStatusRegisterProv);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrProvisioning, globalNVR_Provisioning, nvrDataLength, 2);
  readStatusRegisterProv = AQ_API_WordOfLocalStruct(globalNVR_Provisioning, 0);

  return AQ_API_GetStatusRegister_Common(port,
      flashParams->readStatusRegisterIF, readStatusRegisterProv, statusRegister);
}

/* Writes status register if supported for specified flash type */
AQ_Retcode AQ_API_SetStatusRegister
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams,
  uint16_t statusRegister
)
{
  uint16_t setStatus_IF;
  uint16_t setStatus_Prov;

  if ((flashParams->flashType != AQ_API_F_W25Q16DW) && (flashParams->flashType != AQ_API_F_W25Q32))
    return AQ_RET_FLASH_TYPE_BAD;

  AQ_API_SetupFlashCommandWords(port, flashParams->writeStatusOpcode, 0, 0, 2, 0, 0, &setStatus_IF, &setStatus_Prov);

  /* check if the interface is ready */
  if (AQ_FLASH_InterfaceReady(port) != AQ_RET_FLASHINTF_READY)
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, setStatus_Prov);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW),
          statusRegister);       /* nvrAddressLSW */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, setStatus_IF);

  if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
    return AQ_RET_FLASH_READINESS_TIMEOUT;
  return AQ_RET_OK;
}

/* Determines whether flash page size is a power of 2 bytes (eg, 256, 512, etc) */
AQ_Retcode AQ_API_IsPageSizePower2
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams
)
{
  uint16_t statusRegister;
  AQ_Retcode retcode;

  /* Atmel AT45DB041D or AT45DB041E or AT45DB321E*/
  /* check to make sure the device is in 256/512 byte page mode by looking at the status register */

  retcode = AQ_API_GetStatusRegister_Common(port,
     flashParams->readStatusRegisterIF, flashParams->readStatusRegisterProv, &statusRegister);
  if (retcode != AQ_RET_OK)
    return retcode;

  if ((statusRegister & 0x01) == 0)
    return AQ_RET_FLASH_PAGE_SIZE_NEED_CHANGE;
  return AQ_RET_OK;
}

/* Sets flash page size to power of 2 bytes (eg, 256, 512, etc) */
AQ_Retcode AQ_API_SetPageSizePower2
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams
)
{
  /* execute the command */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->set256_Prov);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 2) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressMSW), 0x002A);       /* nvrAddressMSW */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW), 0x80A6);       /* nvrAddressLSW */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams->set256_IF);

  /* wait for the reprogramming to be complete */
  if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
    return AQ_RET_FLASH_READINESS_TIMEOUT;

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf("Device page size is now set to 256 /512 bytes\n");
  if (flashParams->flashType == AQ_API_F_AT45DB041D)
  {
    printf("  - complete this operation by cycling the FLASH power supply\n");
  }
#endif

  return AQ_RET_FLASH_PAGE_SIZE_CHANGED;
}

/* Erases the flash starting from address and using preconstructed command words
  (which determine erase size) */
AQ_Retcode AQ_API_EraseWithCommandWords
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams,
  uint16_t eraseIF,
  uint16_t eraseProv,
  uint32_t address
)
{
  uint32_t* eraseAddress = NULL;
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  uint64_t startTime;

  startTime = getSysTime();
  #endif
#endif
  if ((flashParams->flashType != AQ_API_F_AT45DB041D) &&
      (flashParams->flashType != AQ_API_F_AT45DB041E) &&
      (flashParams->flashType != AQ_API_F_AT45DB321E))
  {
    /* Description: standard FLASH devices incorporate a protection scheme into their status register.  Typically there is a protection bit
       (usually bit 7) and then some sector protection bits (usually bits 2, 3, etc.).  All of these must be cleared in order to alter the
       FLASH.  However, in order to clear the section protection bits, the protection bit must first be cleared.  Once it is cleared, then the
       sector protection bits can be cleared.  Also - all of these commands require a WREN prior to execution. */

    /* check if the interface is ready */
    if (AQ_FLASH_InterfaceReady(port) != AQ_RET_FLASHINTF_READY)
      return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

    /* perform the WREN command for the first disable protection */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->writeEnableProv);
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams->writeEnableIF);

    if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
      return AQ_RET_FLASH_READINESS_TIMEOUT;

    /* perform the disable protection command the first time to ensure the Sector Protection Lock is off*/
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->disableProtProv);
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
            AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW),
            flashParams->disableProtData);       /* nvrAddressLSW */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams->disableProtIF);

    if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
      return AQ_RET_FLASH_READINESS_TIMEOUT;

    if (AQ_FLASH_InterfaceReady(port) != AQ_RET_FLASHINTF_READY)
      return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

    /* perform the WREN command for the second disable protection */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->writeEnableProv);
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams->writeEnableIF);

    if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
      return AQ_RET_FLASH_READINESS_TIMEOUT;

    /* perform the second disable protection command to clear any protection bits */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->disableProtProv);
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
            AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW),
            flashParams->disableProtData);       /* nvrAddressLSW */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams->disableProtIF);

    if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
      return AQ_RET_FLASH_READINESS_TIMEOUT;

    /* wait until ready */
    if (AQ_FLASH_InterfaceReady(port) != AQ_RET_FLASHINTF_READY)
      return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

    /* issue another WREN command for the (chip) erase*/
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->writeEnableProv);
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams->writeEnableIF);

    if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
      return AQ_RET_FLASH_READINESS_TIMEOUT;
  }

  /* perform the (Chip) Erase command */
  if (eraseIF == flashParams->chipEraseIF)
  {
    if ((flashParams->flashType == AQ_API_F_AT45DB041D) ||
        (flashParams->flashType == AQ_API_F_AT45DB041E) ||
        (flashParams->flashType == AQ_API_F_AT45DB321E))
    {
      address = 0x0094809A;
      eraseAddress = &address;
    }
  }
  else
  {
      eraseAddress = &address;
  }
  if (AQ_API_ExecuteNvrOperation(port, flashParams, eraseIF, eraseProv, eraseAddress) ==
      AQ_RET_FLASH_READINESS_TIMEOUT)
    return AQ_RET_FLASH_READINESS_TIMEOUT;

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (eraseIF == flashParams->chipEraseIF && False == suppressOutput_)
    printf("Erase duration %I64d us\n", (getSysTime() - startTime) / 10);
  #endif
#endif

  return AQ_RET_OK;
}

AQ_Retcode AQ_API_Erase
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams,
  uint16_t eraseOpcode,
  uint32_t address
)
{
  uint16_t eraseIF;       /*!< the 16-bit setting for AQ_GlobalNvrInterface.u0.word_0 */
  uint16_t eraseProv;     /*!< the 16-bit setting for AQ_GlobalNvrProvisioning.u0.word_0 */

  AQ_API_SetupFlashCommandWords(port, eraseOpcode, 0, 0, 3, 0, 0, &eraseIF, &eraseProv);

  if (((flashParams->flashType == AQ_API_F_AT45DB041D) ||
       (flashParams->flashType == AQ_API_F_AT45DB041E) ||
       (flashParams->flashType == AQ_API_F_AT45DB321E)) &&
      eraseOpcode == flashParams->blockEraseOpcode &&
      address == 0)
  {
    /* Adesto has special sectors 0a (8 pages) and 0b (248(120) pages) that need to be erased separately
       This assumes that user will want to erase sectors 0a and 0b together as if they were 1 sector */
    AQ_Retcode retcode = AQ_API_EraseWithCommandWords(port, flashParams, eraseIF, eraseProv, address);
    if (retcode != AQ_RET_OK)
      return retcode;
    address = flashParams->pageSize * 8;
  }
  return AQ_API_EraseWithCommandWords(port, flashParams, eraseIF, eraseProv, address);
}

/* Erases the whole flash chip */
AQ_Retcode AQ_API_ChipErase
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams
)
{
  return AQ_API_EraseWithCommandWords(port, flashParams,
    flashParams->chipEraseIF, flashParams->chipEraseProv, 0);
}

/* Programs the flash starting from specified address.
  If programOpcode is specified it is used insterad of burstWrite */
AQ_Retcode AQ_API_ProgramKnownFLASH
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams,
  uint16_t* programOpcode,
  const uint32_t address,
  const uint32_t imageSize,
  const uint8_t *image,
  uint32_t* writtenSize
)
{
  AQ_API_Variable(AQ_GlobalNvrInterface)
  AQ_API_Variable(AQ_GlobalNvrProvisioning)

  uint32_t addressPointer;
  uint32_t pagePointer;
  uint32_t bytesLeftInPage;
#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
  uint32_t countPendingOps;
  const uint32_t numOpsPerDwordWrite = 3;
#endif
  uint16_t dataWord;
  uint16_t dataMSW;
  uint16_t dataLSW;
  uint16_t burstWrite4_IF = flashParams->burstWrite4_IF;
  uint16_t endBurst_IF = flashParams->endBurst_IF;


  if (programOpcode != NULL)
  {
    AQ_API_DeclareLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface)

    AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, burstWrite4_IF);
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, *programOpcode);
    burstWrite4_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

    AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, endBurst_IF);
    /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.7:0) */
    AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrOpcode, *programOpcode);
    endBurst_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);
  }

  /* write the image file in blocks of pageSize */
  addressPointer = 0;
  pagePointer = (addressPointer + address) % flashParams->pageSize;
  *writtenSize = 0;

#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
  countPendingOps = 0;
#endif

  while (addressPointer < imageSize)
  {
    /*
     * Prepare to write the page of data
     */
    if (AQ_FLASH_Ready(port, flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
      return AQ_RET_FLASH_READINESS_TIMEOUT;

    /* Write the WREN & Program instruction */
    if ((flashParams->flashType != AQ_API_F_AT45DB041D) &&
        (flashParams->flashType != AQ_API_F_AT45DB041E) &&
        (flashParams->flashType != AQ_API_F_AT45DB321E))
    {
      /* perform a WREN for legacy devices */
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->writeEnableProv);
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams->writeEnableIF);
#ifdef AQ_MDIO_CLOCK_EXCEEDS_NVR
      AQ_FLASH_InterfaceReady(port);
#endif
    }

    /* set up for the Program command */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams->burstWrite4_Prov);

    /* set the page start address: note this directly tracks the bytes in the image, so it is directly usable here */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 2) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
            AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressMSW), (((addressPointer + address) >> 16) & 0xFF)); /* nvrAddressMSW */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
            AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW), ((addressPointer + address) & 0xFFFF));       /* nvrAddressLSW */

    /*
     * Write the page of data
     */

    while ((pagePointer + 4 < flashParams->pageSize) && (addressPointer + 4 < imageSize))
    {
      /* load the data "backwards" for big/little endian cross */
      dataMSW = (image[addressPointer+3] << 8) | image[addressPointer+2];
      dataLSW = (image[addressPointer+1] << 8) | image[addressPointer];
      addressPointer += 4;
      pagePointer += 4;

    #ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
      AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 4, dataMSW);
      AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 5, dataLSW);
      AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, burstWrite4_IF);

      countPendingOps += numOpsPerDwordWrite;
      /* Check if we've filled our output buffer, and if so, flush. */
      if (countPendingOps >= AQ_API_MDIO_MaxBlockOperations() - numOpsPerDwordWrite )
      {
        AQ_API_MDIO_BlockOperationExecute(port->PHY_ID);
        countPendingOps = 0;
      }
    #else
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 4) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
              AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW), dataMSW);
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 5) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
              AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW), dataLSW);
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, burstWrite4_IF);
#ifdef AQ_MDIO_CLOCK_EXCEEDS_NVR
      AQ_FLASH_InterfaceReady(port);
#endif
    #endif
    }

  #ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
    /* flush the output buffer one last time. */
    AQ_API_MDIO_BlockOperationExecute(port->PHY_ID);
    countPendingOps = 0;
  #endif

    /* Prepare to write the last bytes in the page in non-burst mode. */
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, endBurst_IF);

    /* Write the last bytes of the page.*/
    /* Note: this final write right-justifies non-dWord data in the final dWord */
    bytesLeftInPage = (pagePointer + 4 >= flashParams->pageSize) ?
                      (flashParams->pageSize - pagePointer) : (imageSize - addressPointer);
    switch (bytesLeftInPage)
    {
      case 1:
        dataWord = image[addressPointer++];
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 5) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
                AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW), dataWord);
        /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
        AQ_API_Set(port->PHY_ID, AQ_GlobalNvrProvisioning, nvrDataLength, 1);
        break;

      case 2:
        dataWord = (image[addressPointer+1] << 8) | image[addressPointer];
        addressPointer += 2;
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 5) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
                AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW), dataWord);
        /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
        AQ_API_Set(port->PHY_ID, AQ_GlobalNvrProvisioning, nvrDataLength, 2);
        break;

      case 3:
        dataWord = image[addressPointer+2];
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 4) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
                AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW), dataWord);
        dataWord = (image[addressPointer+1] << 8) | image[addressPointer];
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 5) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
                AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW), dataWord);
        addressPointer += 3;
        /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
        AQ_API_Set(port->PHY_ID, AQ_GlobalNvrProvisioning, nvrDataLength, 3);
        break;

      case 4:
        dataWord = (image[addressPointer+3] << 8) | image[addressPointer+2];
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 4) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
                AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW), dataWord);
        dataWord = (image[addressPointer+1] << 8) | image[addressPointer];
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 5) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
                AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW), dataWord);
        addressPointer += 4;
        /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.C450.A:8) */
        AQ_API_Set(port->PHY_ID, AQ_GlobalNvrProvisioning, nvrDataLength, 4);
        break;
    }

    /* set the end of the burst write and zero the page pointer*/
    pagePointer = 0;

    /* write the data: no need to check for readiness, as this is done at the top of the loop */
    /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0100.F) */
    AQ_API_Set(port->PHY_ID, AQ_GlobalNvrInterface, nvrExecuteOperation, 1);
#ifdef AQ_MDIO_CLOCK_EXCEEDS_NVR
    AQ_FLASH_InterfaceReady(port);
#endif

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    if (!(addressPointer % AQ_VERBOSE_FLASH_PROGRESS))
      printf("  Bytes: 0x%X\n", addressPointer);
#endif
  }

  *writtenSize = addressPointer;
  return AQ_RET_OK;
}


/* Writes the full image to the flash. Controls image CRC16 if it is specified.
   Reads image back and verifies if requested, controls NVR Mailbox CRC if requested */
AQ_Retcode AQ_API_WriteAndVerifyFlashImageOfKnownFLASH
(
  AQ_API_Port* port,
  AQ_API_FLASH flashType,
  const uint32_t imageSize,
  const uint8_t* image,
  const uint16_t* crc16,
  AQ_boolean verify,
  AQ_boolean skipVerbose,           /*!< Skip verbose mismatches on verify process */
  AQ_boolean verifyNvrMailboxCrc
)
{
  AQ_API_Variable(AQ_GlobalNvrInterface)
  AQ_API_DeclareLocalStruct(AQ_GlobalControl, globalControl)

  uint32_t i;
  uint16_t crc16Calculated;
  uint32_t writtenSize;
  AQ_Retcode retval;
  /* FLASH parameters and command words for use with the PHY's FLASH
   * interface registers */
  AQ_API_FlashParams flashParams;
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  uint64_t startTime;
  #endif
#endif


  /*
   *  Check the image integrity
   */
  if (crc16 != NULL)
  {
    crc16Calculated = calculateCRC(image, 0, imageSize);

    if (crc16Calculated != *crc16) return AQ_RET_FLASH_IMAGE_CORRUPT;

  #ifdef AQ_VERBOSE
    printf ("CRC check good on image file (0x%X)\n", crc16Calculated);
  #endif
  }

  /*
   * Determine FLASH parameters and instructions
   */
  if (AQ_API_GetFlashParametersForKnownFLASH(
        port,
        flashType,
        &flashParams) == AQ_RET_FLASH_TYPE_BAD) return AQ_RET_FLASH_TYPE_BAD;

  /* check to make sure the image size minus the 2 CRC bytes is not greater than the size of the FLASH */
  if (imageSize > flashParams.flashSize) return AQ_RET_FLASH_IMAGE_TOO_LARGE;

  if ((flashType == AQ_API_F_AT45DB041D) || (flashType == AQ_API_F_AT45DB041E) || (flashType == AQ_API_F_AT45DB321E))
  {
    /* Check to make sure the device is in 256/512 byte page mode */
    retval = AQ_API_IsPageSizePower2(port, &flashParams);
    if (retval == AQ_RET_FLASH_PAGE_SIZE_NEED_CHANGE)
    {
      /* page size is set to 264/528 bytes */
  #ifdef AQ_VERBOSE
    #ifdef ATL_FLASH
    if (False == suppressOutput_)
    #endif
      printf("Device page size is set to 264 /528 bytes\n  - setting page size to 256 /512bytes\n");
  #endif
      retval = AQ_API_SetPageSizePower2(port, &flashParams);
      /* AT45DB041D page configuration is one-time programmable and requires power cycling;
         AT45DB041E and AT45DB321E are reconfigurable and don't require power cycling */
      if (flashType != AQ_API_F_AT45DB041D && retval == AQ_RET_FLASH_PAGE_SIZE_CHANGED)
        retval = AQ_RET_OK;
    }
    if (retval != AQ_RET_OK)
      return retval;
  }


  /*
   *  Erase the FLASH
   */
#ifdef AQ_FLASH_ADESTO_FULL_ERASE
  if (True)
#else
  if ((flashType != AQ_API_F_AT45DB041D) && (flashType != AQ_API_F_AT45DB041E) && (flashType != AQ_API_F_AT45DB321E))
#endif
  {
    retval = AQ_API_ChipErase(port, &flashParams);
    if (retval != AQ_RET_OK)
      return retval;
  }


  /*
   *  Write the FLASH
   */

  if (verifyNvrMailboxCrc == True)
  {
    /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0100.C) */
    AQ_API_Set(port->PHY_ID, AQ_GlobalNvrInterface, resetNvrCrc, 1);
  }

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf("Bytes in file 0x%X\n", imageSize);
  #ifdef ATL_FLASH
  startTime = getSysTime();
  #endif
#endif
  retval = AQ_API_ProgramKnownFLASH(port, &flashParams, NULL, 0, imageSize, image, &writtenSize);
  if (retval != AQ_RET_OK)
    return retval;

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
    if (False == suppressOutput_)
      printf("Program duration %I64d us\n", (getSysTime() - startTime) / 10);
  #endif
#endif

  if (verifyNvrMailboxCrc == True)
  {
    /* just execute with verbose, don't return on failure */
    verifyImageCrc((uint32_t*)image, imageSize, port);
  }

  /*
   * Verify the written data. If the verification fails, return the
   * failure code.
   */
  if (verify == True)
  {
    retval = AQ_API_VerifyFlashImageOfKnownFLASH(port, flashType, imageSize, image, crc16, skipVerbose);
    if (retval != AQ_RET_OK) return retval;
  }

  /* reset the processor to force a reload */
  AQ_API_AssignWordOfLocalStruct(globalControl, 1, 0x0000);
  /* REGDOC: Assign to local representation of bitfield (APPIA/HHD/EUR: 1E.C001.6) */
  AQ_API_AssignBitfieldOfLocalStruct_DeviceRestricted(APPIA_HHD_EUR, AQ_GlobalControl, globalControl, upRunStallOverride, 1);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C001.0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalControl, globalControl, upRunStall, 1);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C000 + 1) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalControl, 1,
      AQ_API_WordOfLocalStruct(globalControl, 1));
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C001.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalControl, globalControl, upReset, 1);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C000 + 1) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalControl, 1,
      AQ_API_WordOfLocalStruct(globalControl, 1));

  /* wait 100us:  given a 20 MHz MDIO with preamble suppression and a preset address pointer, one write delays
     a minimum of 32 * (1/20 MHz) = 1.6 us = ~64 writes.  Use the global scratchpad as it does nothing */
  for (i = 0; i < 64; i++)
    /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0300) */
    AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalMicroprocessorScratchPad, 0, 0x0000);

  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C001.F) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalControl, globalControl, upReset, 0);
  /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.C001.0) */
  AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalControl, globalControl, upRunStall, 0);
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C000 + 1) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalControl, 1,
      AQ_API_WordOfLocalStruct(globalControl, 1));

  return AQ_RET_OK;
}


AQ_Retcode AQ_API_WriteAndVerifyFlashImage
(
  AQ_API_Port* port,
  const uint32_t* imageSizePointer,
  const uint8_t* image
)
{
  uint16_t globalNVR_InterfacePrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word1;
  uint16_t globalControlPrevious_word1;
  AQ_API_FLASH flashType;
  uint32_t imageSize;
  uint16_t crc16;
  AQ_Retcode retcode;

  /* Take control of the FLASH and determine its type */
  AQ_TakeControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1, True, AQ_FLASH_NVR_CLOCK_DIVIDE);
  retcode = AQ_API_DetermineFLASH_Type(port, &flashType, NULL);
  if (AQ_RET_OK != retcode)
  {
    /* bail on error */
    AQ_ReturnControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
        &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
        &globalControlPrevious_word1);
    return retcode;
  }

  /* store the CRC-16 for the image, which is the last two bytes */
  imageSize = *imageSizePointer;
  crc16 = image[imageSize - 2] << 8 | image[imageSize - 1];
  /* Write and Verify the FLASH image. */
  retcode = AQ_API_WriteAndVerifyFlashImageOfKnownFLASH(port, flashType, imageSize - 2, image, &crc16, True, False, False);

  /* Return the PHY to its previous state */
  AQ_ReturnControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1);

  return retcode;
}


/* Reads image and verifies it throw CRC-16 calculation.
   Check crc16 might be specified or calcuated inside the function */
AQ_Retcode AQ_API_VerifyFlashImageOfKnownFLASH
(
  AQ_API_Port* port,
  AQ_API_FLASH flashType,
  const uint32_t imageSize,
  const uint8_t *image,
  const uint16_t *crc16,
  AQ_boolean skipVerbose            /*!< Skip verbose mismatches on verify process */
)
{
  AQ_API_Variable(AQ_GlobalNvrInterface)

  uint32_t i;
  uint32_t imageDWordSize;
  uint32_t image_readBack_index;
  uint16_t crc16Calculated;
#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
  unsigned int * asyncReadResults;
  uint32_t countPendingOps;
  uint32_t countPendingReadResults;
  uint32_t numOpsPerDwordRead = 0;
  uint16_t j;
#endif
  uint16_t dataMSW;
  uint16_t dataLSW;
  /* FLASH parameters and command words for use with the PHY's FLASH interface registers */
  AQ_API_FlashParams flashParams;
  AQ_boolean mismatch = False;
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  uint64_t startTime;
  #endif
#endif


  /*
   *  Check the image integrity
   */
  if (crc16 != NULL)
  {
    crc16Calculated = calculateCRC(image, 0, imageSize);

    if (crc16Calculated != *crc16) return AQ_RET_FLASH_IMAGE_CORRUPT;

  #ifdef AQ_VERBOSE
    printf ("CRC check good on image file (0x%X)\n", crc16Calculated);
  #endif
  }

  /*
   * Determine FLASH parameters and instructions
   */
  if (AQ_API_GetFlashParametersForKnownFLASH(
        port,
        flashType,
        &flashParams) == AQ_RET_FLASH_TYPE_BAD) return AQ_RET_FLASH_TYPE_BAD;

  /* check to make sure the image size minus the 2 CRC bytes is not greater than the size of the FLASH */
  if (imageSize > flashParams.flashSize) return AQ_RET_FLASH_IMAGE_TOO_LARGE;


  /*
   *  Verify the image data
   */

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf("\nStarting read of FLASH data\n");
#endif

  /* Poll the FLASH for readiness to start the read */
  if (AQ_FLASH_Ready(port, &flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
    return AQ_RET_FLASH_READINESS_TIMEOUT;

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  startTime = getSysTime();
  #endif
#endif

  /* set up to read the FLASH */
  switch (port->device)
  {
    case AQ_DEVICE_APPIA:
    case AQ_DEVICE_EUR:
#ifdef ATL_FLASH
    case AQ_DEVICE_ATL:
#endif
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams.burstRead4_Prov);
      break;

    case AQ_DEVICE_HHD:
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams.nonburstRead4_Prov);
      break;
  }

  /* set the starting read address */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 2) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressMSW), 0x0000);      /* nvrAddressMSW */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW), 0x0000);      /* nvrAddressLSW */

  /* verify the written image */

  crc16Calculated = 0x0000;

  /* set the number of DWords to read prior to the last block of 4 bytes (so the burst write can be ended).
     the -1 is to knock off the last even block of 4 if there are a multiple of four bytes: i.e. we want
     1 -> 4 bytes left, not 0 -> 3 bytes. */
  imageDWordSize = (imageSize - 1) >> 2;

  image_readBack_index = 0;
#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
  countPendingOps = 0;
  countPendingReadResults = 0;
#endif
  for (i = 0; i < imageDWordSize; i++)      /* stop one prior to the end to allow the burst flag to be lowered */
  {
  #ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE

    switch (port->device)
    {
      case AQ_DEVICE_APPIA:
      case AQ_DEVICE_EUR:
        /* burst read method */
        AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams.burstRead4_IF);
        AQ_API_BlockReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 5);      /* LSW */
        AQ_API_BlockReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 4);      /* MSW */
        numOpsPerDwordRead = 3;
        countPendingOps += numOpsPerDwordRead;
        countPendingReadResults += 2;
        break;

      case AQ_DEVICE_HHD:
        /* non-burst read method */
        AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 2, (i * 4) >> 16);
        AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 3, (i * 4) & 0xFFFF);

        AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams.nonburstRead4_IF);
        AQ_API_BlockReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 5);      /* LSW */
        AQ_API_BlockReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 4);      /* MSW */
        numOpsPerDwordRead = 5;
        countPendingOps += numOpsPerDwordRead;
        countPendingReadResults += 2;
        break;
    }

    /* Once we've filled up the block operations buffer, flush and compare
     * the read results to the original image. */
    if (countPendingOps >= AQ_API_MDIO_MaxBlockOperations() - numOpsPerDwordRead)
    {
      asyncReadResults = AQ_API_MDIO_BlockOperationExecute(port->PHY_ID);
      countPendingOps = 0;
      /* For each word that we've read back from FLASH, compare both
       * bytes to the original image, and calculate running CRC16. */
      for (j = 0; j < countPendingReadResults; j++)
      {
        if (image[image_readBack_index] != (asyncReadResults[j] & 0xff))
        {
          mismatch = True;
          if (skipVerbose == False)
          {
          #ifdef AQ_VERBOSE
            printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", image_readBack_index, asyncReadResults[j] & 0xff, image[image_readBack_index]);
          #endif
          }
        }
        crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (asyncReadResults[j] & 0xff)];
        image_readBack_index++;

        if (image[image_readBack_index] != ((asyncReadResults[j] >> 8) & 0xff))
        {
          mismatch = True;
          if (skipVerbose == False)
          {
          #ifdef AQ_VERBOSE
            printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", image_readBack_index, (asyncReadResults[j] >> 8) & 0xff, image[image_readBack_index]);
          #endif
          }
        }
        crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ ((asyncReadResults[j] >> 8) & 0xff)];
        image_readBack_index++;
      }
      countPendingReadResults = 0;
    }

  #else

    switch (port->device)
    {
      case AQ_DEVICE_APPIA:
      case AQ_DEVICE_EUR:
#ifdef ATL_FLASH
    case AQ_DEVICE_ATL:
#endif
        /* burst read method */
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams.burstRead4_IF);
        break;

      case AQ_DEVICE_HHD:
        /* non-burst read method */
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100 + 2) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 2, (i * 4) >> 16);
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100 + 3) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 3, (i * 4) & 0xFFFF);

        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams.nonburstRead4_IF);
        break;
    }

#ifdef AQ_MDIO_CLOCK_EXCEEDS_NVR
    AQ_FLASH_InterfaceReady(port);
#endif
    /* Read LSW */
    /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
    AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);
    /* Read MSW */
    /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0104.F:0) */
    AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW, dataMSW);

    /* Compare both bytes of LSW to original image, and calculate running CRC16 */
    if (image[image_readBack_index] != (dataLSW & 0xff))
    {
      mismatch = True;
      if (skipVerbose == False)
      {
      #ifdef AQ_VERBOSE
        printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", image_readBack_index, dataLSW & 0xff, image[image_readBack_index]);
      #endif
      }
    }
    crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW & 0xff)];
    image_readBack_index++;

    if (image[image_readBack_index] != (dataLSW >> 8))
    {
      mismatch = True;
      if (skipVerbose == False)
      {
      #ifdef AQ_VERBOSE
        printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", image_readBack_index, dataLSW >> 8, image[image_readBack_index]);
      #endif
      }
    }
    crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW >> 8)];
    image_readBack_index++;

    /* Compare both bytes of MSW to original image, and calculate running CRC16 */
    if (image[image_readBack_index] != (dataMSW & 0xff))
    {
      mismatch = True;
      if (skipVerbose == False)
      {
      #ifdef AQ_VERBOSE
        printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", image_readBack_index, dataMSW & 0xff, image[image_readBack_index]);
      #endif
      }
    }
    crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataMSW & 0xff)];
    image_readBack_index++;

    if (image[image_readBack_index] != (dataMSW >> 8))
    {
      mismatch = True;
      if (skipVerbose == False)
      {
      #ifdef AQ_VERBOSE
        printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", image_readBack_index, dataMSW >> 8, image[image_readBack_index]);
      #endif
      }
    }
    crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataMSW >> 8)];
    image_readBack_index++;

  #endif

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    if (i && ((i % (flashParams.pageSize / 4)) == 0))
      if (!((i << 2) % AQ_VERBOSE_FLASH_PROGRESS))
        printf("  Bytes: 0x%X\n", (i << 2));
#endif
  }

#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
  /* We're done with the DWORD-reading loop, but we still need to fetch any
   * asynchronous-read results */
  asyncReadResults = AQ_API_MDIO_BlockOperationExecute(port->PHY_ID);
  countPendingOps = 0;
  for (j = 0; j < countPendingReadResults; j++)
  {
    if (image[image_readBack_index] != (asyncReadResults[j] & 0xff))
    {
      mismatch = True;
      if (skipVerbose == False)
      {
      #ifdef AQ_VERBOSE
        printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", image_readBack_index, asyncReadResults[j] & 0xff, image[image_readBack_index]);
      #endif
      }
    }
    crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (asyncReadResults[j] & 0xff)];
    image_readBack_index++;

    if (image[image_readBack_index] != ((asyncReadResults[j] >> 8) & 0xff))
    {
      mismatch = True;
      if (skipVerbose == False)
      {
      #ifdef AQ_VERBOSE
        printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", image_readBack_index, (asyncReadResults[j] >> 8) & 0xff, image[image_readBack_index]);
      #endif
      }
    }
    crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ ((asyncReadResults[j] >> 8) & 0xff)];
    image_readBack_index++;
  }
  countPendingReadResults = 0;
#endif

  /* set the end of the burst write and read the last bytes (note just read
   * 4 bytes regardless and sort out which are valid afterwards) */
  /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0100.A) */
  AQ_API_Set(port->PHY_ID, AQ_GlobalNvrInterface, nvrBurst, 0);

  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 2) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressMSW), ((imageDWordSize * 4) >> 16));
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW), ((imageDWordSize * 4) & 0xFFFF));
  /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_Set(port->PHY_ID, AQ_GlobalNvrInterface, nvrExecuteOperation, 1);

  if (AQ_FLASH_InterfaceReady(port) != AQ_RET_FLASHINTF_READY)
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

  i = imageDWordSize;
  /* this final read expects non-dWord data to be right-justified in the final dWord */
  switch (imageSize & 0x3)
  {
    case 0x0:     /* this is actually 0x4! */
      /* read the 4 bytes of data and update the CRC-16*/
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);

      if (image[4*i] != (dataLSW & 0xFF))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i), (dataLSW & 0xFF), image[4*i]);
        #endif
        }
      }
      if (image[4*i+1] != (dataLSW >> 8))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i+1), (dataLSW >> 8), image[4*i+1]);
        #endif
        }
      }

      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW & 0xFF)];
      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW >> 8)];
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0104.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW, dataMSW);

      if (image[4*i+2] != (dataMSW & 0xFF))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i+2), (dataMSW & 0xFF), image[4*i+2]);
        #endif
        }
      }
      if (image[4*i+3] != (dataMSW >> 8))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i+3), (dataMSW >> 8), image[4*i+3]);
        #endif
        }
      }

      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataMSW & 0xFF)];
      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataMSW >> 8)];
      break;

    case 0x1:
      /* read the byte of data and update the CRC-16*/
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);

      if (image[4*i] != (dataLSW & 0xFF))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i), (dataLSW & 0xFF), image[4*i]);
        #endif
        }
      }

      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW & 0xFF)];
      break;

    case 0x2:
      /* read the 2 bytes of data and update the CRC-16*/
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);

      if (image[4*i] != (dataLSW & 0xFF))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i), (dataLSW & 0xFF), image[4*i]);
        #endif
        }
      }
      if (image[4*i+1] != (dataLSW >> 8))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i+1), (dataLSW >> 8), image[4*i+1]);
        #endif
        }
      }

      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW & 0xFF)];
      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW >> 8)];
      break;

    case 0x3:
      /* read the 3 bytes of data and update the CRC-16*/
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);
      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW & 0xFF)];
      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataLSW >> 8)];

      if (image[4*i] != (dataLSW & 0xFF))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i), (dataLSW & 0xFF), image[4*i]);
        #endif
        }
      }
      if (image[4*i+1] != (dataLSW >> 8))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i+1), (dataLSW >> 8), image[4*i+1]);
        #endif
        }
      }

      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0104.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW, dataMSW);

      if (image[4*i+2] != (dataMSW & 0xFF))
      {
        mismatch = True;
        if (skipVerbose == False)
        {
        #ifdef AQ_VERBOSE
          printf("  Mismatch on byte 0x%X: Read 0x%X - Should be: 0x%X\n", (4*i+2), (dataMSW & 0xFF), image[4*i+2]);
        #endif
        }
      }

      crc16Calculated = ((crc16Calculated & 0xFF) << 8) ^ AQ_CRC16Table[(crc16Calculated >> 8) ^ (dataMSW & 0xFF)];
      break;
  }

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    if (!(imageSize % AQ_VERBOSE_FLASH_PROGRESS))
      printf("  Bytes: 0x%X\n", imageSize);
#endif

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
    if (False == suppressOutput_)
      printf("Read duration %I64d us\n", (getSysTime() - startTime) / 10);
  #endif
#endif

  if (((crc16 != NULL) && (crc16Calculated != *crc16)) ||
      ((crc16 == NULL) && (crc16Calculated != calculateCRC(image, 0, imageSize))))
    return AQ_RET_FLASH_IMAGE_MISMATCH;     /* error on burning FLASH */
  if (mismatch == True)
  {
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf ("(CRC 0x%X) is OK but images differ\n", crc16Calculated);
#endif
    return AQ_RET_FLASH_IMAGE_MISMATCH;
  }

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  if (False == suppressOutput_)
  #endif
    printf ("OK (CRC 0x%X)\n", crc16Calculated);
#endif

  return AQ_RET_OK;
}


AQ_Retcode AQ_API_VerifyFlashImage
(
  AQ_API_Port* port,
  const uint32_t* imageSizePointer,
  const uint8_t* image
)
{
  uint16_t globalNVR_InterfacePrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word1;
  uint16_t globalControlPrevious_word1;
  AQ_API_FLASH flashType;
  uint32_t imageSize;
  uint16_t crc16;
  AQ_Retcode retcode;


  /* Take control of the FLASH and determine its type */
  AQ_TakeControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1, True, AQ_FLASH_NVR_CLOCK_DIVIDE);
  retcode = AQ_API_DetermineFLASH_Type(port, &flashType, NULL);
  if (AQ_RET_OK != retcode)
  {
    /* bail on error */
    AQ_ReturnControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
        &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
        &globalControlPrevious_word1);
    return retcode;
  }

  /* store the CRC-16 for the image, which is the last two bytes */
  imageSize = *imageSizePointer;
  crc16 = image[imageSize - 2] << 8 | image[imageSize - 1];
  /* Verify the FLASH image. */
  retcode = AQ_API_VerifyFlashImageOfKnownFLASH(port, flashType, imageSize - 2, image, &crc16, False);

  /* Return the PHY to its previous state */
  AQ_ReturnControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1);

  return retcode;
}


AQ_Retcode AQ_API_ReadFlashImage
(
  AQ_API_Port* port,
  const uint32_t* startAddress,
  const uint32_t* imageSizePointer,
  uint8_t* image
)
{
  uint16_t globalNVR_InterfacePrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word1;
  uint16_t globalControlPrevious_word1;
  AQ_API_FLASH flashType;
  uint32_t readSize;
  AQ_Retcode retcode;


  /* Take control of the FLASH and determine its type */
  AQ_TakeControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1, True, AQ_FLASH_NVR_CLOCK_DIVIDE);
  retcode = AQ_API_DetermineFLASH_Type(port, &flashType, NULL);
  if (AQ_RET_OK != retcode)
  {
    /* bail on error */
    AQ_ReturnControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
        &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
        &globalControlPrevious_word1);
    return retcode;
  }

  /* Read the image from the FLASH. */
  retcode = AQ_API_ReadFlashImageOfKnownFLASH(port, flashType, *startAddress, *imageSizePointer, image, &readSize, False);

  /* Return the PHY to its previous state */
  AQ_ReturnControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1);

  return retcode;
}

/* Read the data from the FLASH. */
AQ_Retcode AQ_API_ReadFlashImageOfKnownFLASH
(
  AQ_API_Port* port,
  AQ_API_FLASH flashType,
  const uint32_t startAddress,
  const uint32_t imageSize,
  uint8_t *image,
  uint32_t* readSize,
  AQ_boolean skipVerbose            /*!< Skip verbose read process */
)
{
  AQ_API_Variable(AQ_GlobalNvrInterface)

  uint32_t i;
  uint32_t imageDWordSize;
  uint32_t image_readBack_index;
#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
  unsigned int * asyncReadResults;
  uint32_t countPendingOps;
  uint32_t countPendingReadResults;
  uint32_t numOpsPerDwordRead = 0;
  uint16_t j;
#endif
  uint16_t dataMSW;
  uint16_t dataLSW;
  /* FLASH parameters and command words for use with the PHY's FLASH
   * interface registers */
  AQ_API_FlashParams flashParams;
#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  uint64_t startTime;
  #endif
#endif


  *readSize = 0;

  /*
   * Determine FLASH parameters and instructions
   */
  if (AQ_API_GetFlashParametersForKnownFLASH(
        port,
        flashType,
        &flashParams) == AQ_RET_FLASH_TYPE_BAD) return AQ_RET_FLASH_TYPE_BAD;

  /*
   * Read the FLASH
   */

  if (skipVerbose == False)
  {
  #ifdef AQ_VERBOSE
    printf("\nStarting read of FLASH data\n");
  #endif
  }

  /* Poll the FLASH for readiness to start the read */
  if (AQ_FLASH_Ready(port, &flashParams) == AQ_RET_FLASH_READINESS_TIMEOUT)
    return AQ_RET_FLASH_READINESS_TIMEOUT;

#ifdef AQ_VERBOSE
  #ifdef ATL_FLASH
  startTime = getSysTime();
  #endif
#endif

  /* set up to read the FLASH */
  switch (port->device)
  {
    case AQ_DEVICE_APPIA:
    case AQ_DEVICE_EUR:
#ifdef ATL_FLASH
    case AQ_DEVICE_ATL:
#endif
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams.burstRead4_Prov);
      break;

    case AQ_DEVICE_HHD:
      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.C450) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrProvisioning, 0, flashParams.nonburstRead4_Prov);
      break;
  }

  /* set the starting read address */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 2) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressMSW), startAddress >> 16);    /* nvrAddressMSW */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW), startAddress & 0xffff); /* nvrAddressLSW */

  /* set the number of DWords to read prior to the last block of 4 bytes (so the burst write can be ended).
     the -1 is to knock off the last even block of 4 if there are a multiple of four bytes: i.e. we want
     1 -> 4 bytes left, not 0 -> 3 bytes. */
  imageDWordSize = (imageSize - 1) >> 2;

  image_readBack_index = 0;
#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
  countPendingOps = 0;
  countPendingReadResults = 0;
#endif
  for (i = 0; i < imageDWordSize; i++)      /* stop one prior to the end to allow the burst flag to be lowered */
  {
  #ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE

    switch (port->device)
    {
      case AQ_DEVICE_APPIA:
      case AQ_DEVICE_EUR:
        /* burst read method */
        AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams.burstRead4_IF);
        AQ_API_BlockReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 5);      /* LSW */
        AQ_API_BlockReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 4);      /* MSW */
        numOpsPerDwordRead = 3;
        countPendingOps += numOpsPerDwordRead;
        countPendingReadResults += 2;
        break;

      case AQ_DEVICE_HHD:
        /* non-burst read method */
        AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 2, (startAddress + (i * 4)) >> 16);
        AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 3, (startAddress + (i * 4)) & 0xFFFF);

        AQ_API_BlockWriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams.nonburstRead4_IF);
        AQ_API_BlockReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 5);      /* LSW */
        AQ_API_BlockReadRegister(port->PHY_ID, AQ_GlobalNvrInterface, 4);      /* MSW */
        numOpsPerDwordRead = 5;
        countPendingOps += numOpsPerDwordRead;
        countPendingReadResults += 2;
        break;
    }

    /* Once we've filled up the output buffer, flush and store the image. */
    if (countPendingOps >= AQ_API_MDIO_MaxBlockOperations() - numOpsPerDwordRead)
    {
      asyncReadResults = AQ_API_MDIO_BlockOperationExecute(port->PHY_ID);
      countPendingOps = 0;
      for (j = 0; j < countPendingReadResults; j++)
      {
        image[image_readBack_index++] = (asyncReadResults[j] & 0xff);
        image[image_readBack_index++] = (asyncReadResults[j] >> 8);
      }
      countPendingReadResults = 0;
    }

  #else

    switch (port->device)
    {
      case AQ_DEVICE_APPIA:
      case AQ_DEVICE_EUR:
#ifdef ATL_FLASH
      case AQ_DEVICE_ATL:
#endif
        /* burst read method */
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams.burstRead4_IF);
        break;

      case AQ_DEVICE_HHD:
        /* non-burst read method */
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100 + 2) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 2, (startAddress + (i * 4)) >> 16);
        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100 + 3) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 3, (startAddress + (i * 4)) & 0xFFFF);

        /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
        AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, flashParams.nonburstRead4_IF);
        break;
    }

#ifdef AQ_MDIO_CLOCK_EXCEEDS_NVR
    AQ_FLASH_InterfaceReady(port);
#endif
    /* Read LSW */
    /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
    AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);
    image[image_readBack_index++] = (dataLSW & 0xff);
    image[image_readBack_index++] = (dataLSW >> 8);

    /* Read MSW */
    /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0104.F:0) */
    AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW, dataMSW);
    image[image_readBack_index++] = (dataMSW & 0xff);
    image[image_readBack_index++] = (dataMSW >> 8);

  #endif
  }

#ifdef AQ_PHY_SUPPORTS_BLOCK_READ_WRITE
  /* We're done with the DWORD-reading loop, but we still need to fetch any
   * asynchronous-read results */
  asyncReadResults = AQ_API_MDIO_BlockOperationExecute(port->PHY_ID);
  countPendingOps = 0;
  for (j = 0; j < countPendingReadResults; j++)
  {
    image[image_readBack_index++] = (asyncReadResults[j] & 0xff);
    image[image_readBack_index++] = (asyncReadResults[j] >> 8);
  }
  countPendingReadResults = 0;
#endif
  *readSize = image_readBack_index;

  if (imageDWordSize == 0)
  {
      /* nvrOpcode have not been set. Just use non-burst read method with nvrExecuteOperation cleared */
      AQ_API_DeclareLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface)
      uint16_t nonburstRead4Prepare_IF;

      AQ_API_AssignWordOfLocalStruct(globalNVR_Interface, 0, flashParams.nonburstRead4_IF);
      /* REGDOC: Assign to local representation of bitfield (HHD/APPIA/EUR: 1E.0100.F) */
      AQ_API_AssignBitfieldOfLocalStruct(AQ_GlobalNvrInterface, globalNVR_Interface, nvrExecuteOperation, 0);
      nonburstRead4Prepare_IF = AQ_API_WordOfLocalStruct(globalNVR_Interface, 0);

      /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) */
      AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface, 0, nonburstRead4Prepare_IF);
  }
  else
  {
    /* set the end of the burst write and read the last bytes (note just read
     * 4 bytes regardless and sort out which are valid afterwards) */
    /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0100.A) */
    AQ_API_Set(port->PHY_ID, AQ_GlobalNvrInterface, nvrBurst, 0);
  }

  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 2) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressMSW),
      (startAddress + (imageDWordSize * 4)) >> 16);    /* nvrAddressMSW */
  /* REGDOC: Write register (HHD/APPIA/EUR: 1E.0100) + (HHD/APPIA/EUR: 3) */
  AQ_API_WriteRegister(port->PHY_ID, AQ_GlobalNvrInterface,
          AQ_API_Field(port->PHY_ID, AQ_GlobalNvrInterface, nvrAddressLSW),
      (startAddress + (imageDWordSize * 4)) & 0xFFFF); /* nvrAddressLSW */
  /* REGDOC: Read-Modify-Write bitfield (HHD/APPIA/EUR: 1E.0100.F) */
  AQ_API_Set(port->PHY_ID, AQ_GlobalNvrInterface, nvrExecuteOperation, 1);

  /* poll the PHY FLASH interface for readiness */
  if (AQ_FLASH_InterfaceReady(port) != AQ_RET_FLASHINTF_READY)
    return AQ_RET_FLASHINTF_READINESS_TIMEOUT;

  i = imageDWordSize;
  /* this final read expects non-dWord data to be right-justified in the final dWord */
  switch (imageSize & 0x3)
  {
    case 0x0:     /* this is actually 0x4! */
      /* read the 4 bytes of data*/
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);
      image[4*i] = (dataLSW & 0xFF);
      image[4*i+1] = (dataLSW >> 8);

      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0104.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW, dataMSW);
      image[4*i+2] = (dataMSW & 0xFF);
      image[4*i+3] = (dataMSW >> 8);
      break;

    case 0x1:
      /* read the byte of data*/
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);
      image[4*i] = (dataLSW & 0xFF);
      break;

    case 0x2:
      /* read the 2 bytes of data*/
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);
      image[4*i] = (dataLSW & 0xFF);
      image[4*i+1] = (dataLSW >> 8);
      break;

    case 0x3:
      /* read the 3 bytes of data*/
      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0105.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataLSW, dataLSW);
      image[4*i] = (dataLSW & 0xFF);
      image[4*i+1] = (dataLSW >> 8);

      /* REGDOC: Read bitfield (HHD/APPIA/EUR: 1E.0104.F:0) */
      AQ_API_Get(port->PHY_ID, AQ_GlobalNvrInterface, nvrDataMSW, dataMSW);
      image[4*i+2] = (dataMSW & 0xFF);
      break;
  }

#ifdef ATL_FLASH
  if (skipVerbose == False)
  {
  #ifdef AQ_VERBOSE
    printf("Read duration %I64d us\n", (getSysTime() - startTime) / 10);
  #endif
  }
#endif

  *readSize = imageSize;
  return AQ_RET_OK;
}




AQ_Retcode AQ_API_GetFlashInformation
(
  AQ_API_Port* port,
  AQ_API_FlashInformation* information
)
{
  uint32_t startAddress;
  uint32_t size;
  uint32_t readSize;
  uint32_t primaryHeaderPtr = 0x00000000;
  uint32_t primaryDramPtr = 0x00000000;
  uint32_t pointer = 0x00000000;
  uint16_t globalNVR_InterfacePrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word0;
  uint16_t globalNVR_ProvisioningPrevious_word1;
  uint16_t globalControlPrevious_word1;
  uint16_t i;
  uint8_t image[256];
  uint8_t nullTerminatorFound = 0;
  uint8_t versionString[AQ_VERSION_STRING_SIZE];
  AQ_Retcode retval;


  /* zero out the information prior to attempting to fill it */
  for (i = 0; i < 61; i++) information->imageInformation.imageID_String[i] = 0x0;
  information->imageInformation.imageMajorRevisionNumber = 0x0;
  information->imageInformation.imageMinorRevisionNumber = 0x0;
  information->imageInformation.imageROM_ID_Number = 0x00;
  information->imageInformation.programmed = False;

  /* Take control of the FLASH interface */
  AQ_TakeControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1, True, AQ_FLASH_NVR_CLOCK_DIVIDE);

  /* get the FLASH type */
  retval = AQ_API_DetermineFLASH_Type(port, &information->flashType, NULL);

  if (retval == AQ_RET_OK && (information->flashType != AQ_API_F_DaisyChainSlave) &&
      (information->flashType != AQ_API_F_Indeterminate))
  {
    /* get the primary image pointer */
    size = 0x20;
    startAddress = 0x0;
    if ((retval = AQ_API_ReadFlashImageOfKnownFLASH(port, information->flashType,
          startAddress, size, image, &readSize, True)) == AQ_RET_OK)
    {
      primaryHeaderPtr = (((image[0x9] & 0x0F) << 8) | image[0x8]) << 12;

      /* get the primary image header */
      size = 0x20;
      switch (port->device)
      {
        case AQ_DEVICE_APPIA:
          startAddress = primaryHeaderPtr + AQ_PHY_IMAGE_HEADER_CONTENT_OFFSET_APPIA;
          break;

        case AQ_DEVICE_HHD:
        case AQ_DEVICE_EUR:
          startAddress = primaryHeaderPtr + AQ_PHY_IMAGE_HEADER_CONTENT_OFFSET_HHD;
          break;
      }

      if ((retval = AQ_API_ReadFlashImageOfKnownFLASH(port, information->flashType,
            startAddress, size, image, &readSize, True)) == AQ_RET_OK)
      {
        primaryDramPtr = (image[0xA + 2] << 16) | (image[0xA + 1] << 8) | image[0xA + 0];
        switch (port->device)
        {
          case AQ_DEVICE_APPIA:
            break;

          case AQ_DEVICE_HHD:
          case AQ_DEVICE_EUR:
            primaryDramPtr += primaryHeaderPtr;
            break;
        }

        /* load the version string */
        size = AQ_VERSION_STRING_SIZE;
        pointer = primaryDramPtr + AQ_VERSION_STRING_BLOCK_OFFSET;

        if ((retval = AQ_API_ReadFlashImageOfKnownFLASH(port, information->flashType,
              pointer, size, versionString, &readSize, True)) == AQ_RET_OK)
        {
          /* success */
          for (i = 0; i < 61; i++)
          {
            information->imageInformation.imageID_String[i] = (char) (versionString[i]);
            if (versionString[i] == 0x0) nullTerminatorFound = 1;      /* check for the existance of a NULL terminator */
          }
          if (!nullTerminatorFound) information->imageInformation.imageID_String[61] = 0x0;       /* write the NULL terminator if required */

          information->imageInformation.imageMajorRevisionNumber = versionString[62];
          information->imageInformation.imageMinorRevisionNumber = versionString[63];
          information->imageInformation.imageROM_ID_Number = versionString[61];
          for (i = 0; i < AQ_VERSION_STRING_SIZE; i++)
          {
            if (versionString[i] != 0xFF)
            {
              information->imageInformation.programmed = True;
              break;
            }
          }
        }
      }
    }
  }
  else
  {
    if (retval == AQ_RET_OK)
      retval = AQ_RET_FLASH_TYPE_BAD;
  }

  /* Return the PHY to its previous state */
  AQ_ReturnControlOfFLASH(port, &globalNVR_InterfacePrevious_word0,
      &globalNVR_ProvisioningPrevious_word0, &globalNVR_ProvisioningPrevious_word1,
      &globalControlPrevious_word1);

  return retval;
}

/*! Sector erase approximately from eraseStart to eraseEnd.
    Actual erase will performed in sector bounds with restoring affected data */
static AQ_Retcode AQ_API_EraseBySectors
(
  AQ_API_Port* port,
  AQ_API_FlashParams* flashParams,
  uint16_t* programOpcode,
  uint32_t eraseStart,
  uint32_t eraseEnd
)
{
  AQ_Retcode retcode;
  uint32_t sectorSize;
  uint32_t sectorEraseStart;
  uint32_t sectorEraseEnd;
  uint32_t preDataSize;
  uint32_t postDataSize;
  uint8_t* preData = NULL;
  uint8_t* postData = NULL;
  uint32_t actualSize;
  uint32_t sectorEraseAddress;

  if (eraseStart >= eraseEnd)
    return AQ_RET_OK;

  sectorSize = flashParams->sectorErasePageCount * flashParams->pageSize;
  sectorEraseStart = eraseStart;
  preDataSize = sectorEraseStart % sectorSize; /* startAddressWithinSector */
  if (preDataSize)
  {
    sectorEraseStart = sectorEraseStart - preDataSize;
    preData = (uint8_t*)malloc(preDataSize);
    retcode = AQ_API_ReadFlashImageOfKnownFLASH(port, flashParams->flashType,
      sectorEraseStart, preDataSize, preData, &actualSize, True);
    if (retcode != AQ_RET_OK)
    {
  #ifdef AQ_VERBOSE
    #ifdef ATL_FLASH
    if (False == suppressOutput_)
    #endif
      printf("Flash data save failed on address 0x%08X\n", sectorEraseStart);
  #endif
      free(preData);
      return retcode;
    }
  }

  sectorEraseEnd = eraseEnd;
  postDataSize = sectorEraseEnd % sectorSize; /* endAddressWithinSector */
  if (postDataSize)
  {
    postDataSize = sectorSize - postDataSize;
    sectorEraseEnd = sectorEraseEnd + postDataSize;
    postData = (uint8_t*)malloc(postDataSize);
    retcode = AQ_API_ReadFlashImageOfKnownFLASH(port, flashParams->flashType,
      sectorEraseEnd - postDataSize, postDataSize, postData, &actualSize, True);
    if (retcode != AQ_RET_OK)
    {
  #ifdef AQ_VERBOSE
    #ifdef ATL_FLASH
    if (False == suppressOutput_)
    #endif
      printf("Flash data save failed on address 0x%08X\n", sectorEraseEnd - postDataSize);
  #endif
      if (preDataSize)
        free(preData);
      free(postData);
      return retcode;
    }
  }

  /* Sector erase */
  for (sectorEraseAddress = sectorEraseStart;
       sectorEraseAddress < sectorEraseEnd;
       sectorEraseAddress += sectorSize)
  {
    retcode = AQ_API_Erase(port, flashParams, flashParams->sectorEraseOpcode, sectorEraseAddress);
    if (retcode != AQ_RET_OK)
    {
  #ifdef AQ_VERBOSE
    #ifdef ATL_FLASH
    if (False == suppressOutput_)
    #endif
      printf("Flash sector erase failed on address 0x%08X\n", sectorEraseAddress);
  #endif
      if (preDataSize)
        free(preData);
      if (postDataSize)
        free(postData);
      return retcode;
    }
  }

  /* Write data back */
  /* printf("preDataSize = 0x%06X postDataSize = 0x%06X\n", preDataSize, postDataSize); */
  if (preDataSize)
  {
    retcode = AQ_API_ProgramKnownFLASH(port, flashParams, programOpcode,
        sectorEraseStart, preDataSize, preData, &actualSize);
    if (retcode != AQ_RET_OK)
    {
  #ifdef AQ_VERBOSE
    #ifdef ATL_FLASH
    if (False == suppressOutput_)
    #endif
      printf("Flash data restore failed on address 0x%08X\n", sectorEraseStart);
  #endif
    }
    free(preData);
  }
  if (postDataSize)
  {
    AQ_Retcode retcode2 = AQ_API_ProgramKnownFLASH(port, flashParams, programOpcode,
        sectorEraseEnd - postDataSize, postDataSize, postData, &actualSize);
    if (retcode2 != AQ_RET_OK)
    {
  #ifdef AQ_VERBOSE
    #ifdef ATL_FLASH
    if (False == suppressOutput_)
    #endif
      printf("Flash data restore failed on address 0x%08X\n", sectorEraseEnd - postDataSize);
  #endif
      retcode = retcode2;
    }
    free(postData);
  }

  return retcode;
}

AQ_Retcode AQ_API_ModifyKnownFLASH
(
  AQ_API_Port* port,
  AQ_API_FLASH flashType,
  AQ_boolean readModifyWrite,   /*!< Use read-modify-write if applicable (AT45DB) */
  uint32_t startAddress,
  uint32_t modifySize,
  uint8_t *data,
  uint32_t* modifiedSize
)
{
  /* FLASH parameters and command words for use with the PHY's FLASH
   * interface registers */
  AQ_API_FlashParams flashParams;
  AQ_Retcode retcode;

  uint16_t writeOpcode;
  uint16_t* pWriteOpcode = &writeOpcode;
  uint32_t sectorEraseStart, sectorEraseEnd, sectorEraseStart2, sectorEraseEnd2;

  *modifiedSize = 0;

  /* Determine FLASH parameters and instructions */
  if ((retcode = AQ_API_GetFlashParametersForKnownFLASH(port, flashType, &flashParams))
      != AQ_RET_OK)
    return retcode;

  if (startAddress >= flashParams.flashSize)
    return AQ_RET_FLASH_INVALID_PARAMETERS;
  if (startAddress + modifySize > flashParams.flashSize)
    modifySize = flashParams.flashSize - startAddress;
  if (modifySize == 0)
    return AQ_RET_OK;

  if (modifySize == flashParams.flashSize)
  {
    /* Full flash modify */
    if ((retcode = AQ_API_ChipErase(port, &flashParams)) != AQ_RET_OK)
      return retcode;
    return AQ_API_ProgramKnownFLASH(port, &flashParams, NULL, startAddress, modifySize, data, modifiedSize);
  }

  /* Actual modify within flash size */
  if ((flashType == AQ_API_F_AT45DB041D) ||
      (flashType == AQ_API_F_AT45DB041E) ||
      (flashType == AQ_API_F_AT45DB321E))
  {
    /* Flash supports read-modify-write */
    if (readModifyWrite == True)
    {
      /* Actually it may be slower than erase and write - for some sizes */
      writeOpcode = AQ_API_F_OPCODE_AT45DB_RMW;
      return AQ_API_ProgramKnownFLASH(port, &flashParams, pWriteOpcode, startAddress, modifySize, data, modifiedSize);
    }
    /* Generic erase and write */
    if (flashType == AQ_API_F_AT45DB041D)
    {
      /* requires special handling, because performs FULL page (buffer) program
         and doesn't support generic 0x02 (AQ_API_F_OPCODE_AT45DB_PAGE_PROGRAM) page program
         (which can be less than page).
         BTW, 0x58 (AQ_API_F_OPCODE_AT45DB_RMW) "Auto Page Rewrite" is limited in comparison
         with AQ_API_F_AT45DB041E and might fail as well.
       Hopefully is replaced with AQ_API_F_AT45DB041E */
      return AQ_RET_FLASH_TYPE_BAD;
    }
    writeOpcode = AQ_API_F_OPCODE_AT45DB_PAGE_PROGRAM;
  }
  else
  {
    /* Regardless of readModifyWrite flag, use the only possible
       generic erase and write way */
    pWriteOpcode = NULL;
  }

  /* Try to erase blocks (i.e. larger erasable area) first - whole blocks within
     the specified area,
     then sectors (i.e. smaller erasable area) - with possible out of borders
     of the specified area; keep the nearest area content at the temp buffer. */
  /* Block additional (usually 32K in addition to 64K for some flashes) is ignored anyway. */
  sectorEraseStart = startAddress;
  sectorEraseEnd = startAddress + modifySize;
  sectorEraseStart2 = 0;
  sectorEraseEnd2 = 0;
  if (flashParams.blockErasePageCount)
  {
    /* Whole block count */
    uint32_t blockSize = flashParams.blockErasePageCount * flashParams.pageSize;
    uint32_t blockEraseStart = startAddress;
    uint32_t startAddressWithinBlock = blockEraseStart % blockSize;
    if (startAddressWithinBlock)
      blockEraseStart = blockEraseStart - startAddressWithinBlock + blockSize;
    if (blockEraseStart < startAddress + modifySize)
    {
      uint32_t blockEraseAddress;
      uint32_t blockEraseEnd = startAddress + modifySize;
      uint32_t endAddressWithinBlock = blockEraseEnd % blockSize;
      if (endAddressWithinBlock)
        blockEraseEnd = blockEraseEnd - endAddressWithinBlock;

      /* printf("blockEraseStart = 0x%06X blockEraseEnd = 0x%06X\n", blockEraseStart, blockEraseEnd); */
      if (blockEraseStart < blockEraseEnd)
      {
        /* Block erase */
        for (blockEraseAddress = blockEraseStart;
             blockEraseAddress < blockEraseEnd;
             blockEraseAddress += blockSize)
        {
          retcode = AQ_API_Erase(port, &flashParams, flashParams.blockEraseOpcode, blockEraseAddress);
          if (retcode != AQ_RET_OK)
          {
        #ifdef AQ_VERBOSE
          #ifdef ATL_FLASH
          if (False == suppressOutput_)
          #endif
            printf("Flash block erase failed on address 0x%08X\n", blockEraseAddress);
        #endif
            return retcode;
          }
        }

        sectorEraseEnd2 = sectorEraseEnd;
        sectorEraseEnd = blockEraseStart;
        sectorEraseStart2 = blockEraseEnd;
      }
    }
  }

  if (flashParams.sectorErasePageCount)
  {
    /* Erase could affect nearest area, store it before */
    /* Sector erase approximately from sectorEraseStart to sectorEraseEnd */
    retcode = AQ_API_EraseBySectors(port, &flashParams, pWriteOpcode, sectorEraseStart, sectorEraseEnd);
    if (retcode != AQ_RET_OK)
      return retcode;
    /* Sector erase approximately from sectorEraseStart2 to sectorEraseEnd2 */
    retcode = AQ_API_EraseBySectors(port, &flashParams, pWriteOpcode, sectorEraseStart2, sectorEraseEnd2);
    if (retcode != AQ_RET_OK)
      return retcode;
  }
  else
  {
    /* Check if sector erase is required */
    if (sectorEraseStart < sectorEraseEnd ||
        sectorEraseStart2 < sectorEraseEnd2)
      return AQ_RET_FLASH_ERASE_NOT_SUPPORTED;
  }

  /* Write the data on the erased area */
  return AQ_API_ProgramKnownFLASH(port, &flashParams, pWriteOpcode, startAddress, modifySize, data, modifiedSize);
}


/*@}*/

#ifdef __cplusplus
}
#endif