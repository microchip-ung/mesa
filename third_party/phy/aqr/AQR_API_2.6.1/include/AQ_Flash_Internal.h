/* AQ_Flash_Internal.h */

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
*                      Copyright Aquantia Corp.
*                              Freeware
*
* Description:
*
*   This file defines internal flash types and functions.
*
*
************************************************************************************/

/*! \file
  This file defines internal flash types and functions.
*/

#ifndef _AQ_FLASH_INTERNAL_H
#define _AQ_FLASH_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*! Recommended NVR clock divide. Sets the clock speed on the SPI to ~10 MHz.*/
#define AQ_FLASH_NVR_CLOCK_DIVIDE  0x10

/*! Some flash specific additional opcodes */
#define AQ_API_F_OPCODE_AT45DB_RMW               0x58
#define AQ_API_F_OPCODE_AT45DB_PAGE_ERASE        0x81
#define AQ_API_F_OPCODE_AT45DB_RESET             0xF0
#define AQ_API_F_OPCODE_COMMON_BLOCK_ADDIT_ERASE 0x52
#define AQ_API_F_OPCODE_COMMON_ENABLE_RESET      0x66
#define AQ_API_F_OPCODE_COMMON_RESET             0x99
#define AQ_API_F_OPCODE_WINBOND_GET_STATUS2      0x35

/*! Structure represents flash parameters and prepared NVR Interface and
   NVR Provisioning words for common used commands. */
typedef struct AQ_API_FlashParams_
{
    /*! The FLASH type */
  AQ_API_FLASH flashType;
  uint16_t chipEraseOpcode;
  uint16_t writeEnableOpcode;
  uint16_t writeStatusOpcode;
  uint16_t disableProtData;
  uint16_t readStatusOpcode;
  uint16_t readStatusRegisterMask;     /*!< the 8 bit status register mask to isolate the RDY/BUSY* bit */
  uint16_t readStatusRegisterPolarity; /*!< the polarity of the ready answer: 1 = Ready, 0 = Ready* */
  uint16_t readOpcode;
  uint16_t programOpcode;
  uint16_t sectorEraseOpcode;
  uint16_t blockEraseOpcode;
  uint16_t pageSize;
  uint16_t pageErasePageCount;           /*!< number of pages in page erase area 
                                              0 - not supported, 1 - supported (only AT45DB now) */
  uint16_t sectorErasePageCount;         /*!< number of pages in sector erase area 
                                              @note Adesto (Atmel) names smaller erasable area "block"
                                                and larger erasable area - "sector", while other 
                                                flash manufacturers usually call smaller erasable area "sector"
                                                and larger erasable area - "block".
                                              We use common practice and sector means smaller erasable area */
  uint16_t blockAdditionalErasePageCount;/*!< number of pages in block additional erasable area
                                              0 - not supported, 1 - supported (only W25Q32 now; MX25L3233F also supports,
                                              but we can't differ it from MX25L3206E which does not support) */
  uint16_t blockErasePageCount;          /*!< number of pages in block erasable area */
  uint16_t maxOperationTime;             /*!< the maximum amount of time in seconds for the operation to take */
  uint16_t writeEnableIF;
  uint16_t writeEnableProv;
  uint16_t chipEraseIF;
  uint16_t chipEraseProv;
  uint16_t disableProtIF;
  uint16_t disableProtProv;
  uint16_t readStatusRegisterIF;       /*!< the 16-bit setting for AQ_GlobalNvrInterface.u0.word_0 to read the status register */
  uint16_t readStatusRegisterProv;     /*!< the 16-bit setting for AQ_GlobalNvrProvisioning.u0.word_0 to read the status register */
  uint16_t nonburstRead4_IF;
  uint16_t nonburstRead4_Prov;
  uint16_t burstRead4_IF;
  uint16_t burstRead4_Prov;
  uint16_t burstWrite4_IF;
  uint16_t burstWrite4_Prov;
  uint16_t read1_IF;
  uint16_t read1_Prov;
  uint16_t endBurst_IF;
  uint16_t execOp_IF;
  uint16_t set256_IF;
  uint16_t set256_Prov;
  uint32_t flashSize;
} AQ_API_FlashParams;

/*! Calculate CRC-16 on specified data */
uint16_t calculateCRC(const uint8_t *buf, uint32_t startByte, uint32_t stopByte);

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
);

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
);

/*! Determine and return the FLASH type from the list of recognized devices 
 * recognizes.  
 * \pre Prior call to AQ_TakeControlOfFLASH() called prior to calling this function.
*/
AQ_Retcode AQ_API_DetermineFLASH_Type
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! OUT: a pointer to the FLASH type */
  AQ_API_FLASH *flashType, 
    /*! OUT: a pointer to jedecId */
  uint32_t* jedecId
);

/*! Determine/construct the parameters and command words appropriately
 * for the specific FLASH type */
AQ_Retcode AQ_API_GetFlashParametersForKnownFLASH
(  
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! The FLASH type */
  AQ_API_FLASH flashType,
    /*! OUT: FLASH parameters and command words */
  AQ_API_FlashParams *flashParams
);

/*! Determines whether flash page size is a power of 2 bytes (eg, 256, 512, etc) */
AQ_Retcode AQ_API_IsPageSizePower2
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams
);

/*! Sets flash page size to power of 2 bytes (eg, 256, 512, etc) */
AQ_Retcode AQ_API_SetPageSizePower2
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams
);

/*! Erases the flash starting from address and using specified erase opcode 
   (which determine erase size) */
AQ_Retcode AQ_API_Erase
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams,
    /*! Opcode to erase (sector, block, chip) */
  uint16_t eraseOpcode,
    /*! Start address to erase (size is determined by opcode),
        lsb-s are ignored */
  uint32_t address
);

/*! Erases the whole flash chip */
AQ_Retcode AQ_API_ChipErase
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams
);

/*! Programs the flash starting from specified address.
   If programOpcode is specified it is used instead of burstWrite */
AQ_Retcode AQ_API_ProgramKnownFLASH
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams,
    /*! Opcode to program (optional, default is used if not specified) */
  uint16_t *programOpcode,
    /*! Start address to program */
  const uint32_t address,
    /*! Size of the image (in bytes) that is being loaded into the Aquantia PHY.*/
  const uint32_t imageSize, 
    /*! The image being loaded into the Aquantia PHY.*/
  const uint8_t *image,
    /*! OUT: The number of actually written bytes */
  uint32_t* writtenSize
);

/*! Read the data from the FLASH. */
AQ_Retcode AQ_API_ReadFlashImageOfKnownFLASH
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! The FLASH type */
  AQ_API_FLASH flashType,
    /*! The starting address from which to read the bytes from the
      Aquantia PHY's FLASH.*/
  const uint32_t startAddress,
    /*! The number of bytes to be loaded from the Aquantia PHY's FLASH
      into the image array.*/
  const uint32_t imageSize,
    /*! The image being loaded from the Aquantia PHY's FLASH.*/
  uint8_t *image,
    /*! OUT: The number of actually read bytes */
  uint32_t* readSize,
    /*! Verbose read process */
  AQ_boolean verbose 
);

AQ_Retcode AQ_API_ModifyKnownFLASH
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! The FLASH type */
  AQ_API_FLASH flashType,
    /*! Use read-modify-write if applicable (AT45DB) */
  AQ_boolean readModifyWrite,
    /*! The starting address from which to modify the FLASH.*/
  uint32_t startAddress,
    /*! The number of bytes to be modified */
  uint32_t modifySize,
    /*! The data array being written to the FLASH.*/
  uint8_t *data,
    /*! OUT: The number of actually modified bytes */
  uint32_t* modifiedSize
);

/*! Writes the full image to the flash. Controls image CRC16 if it is specified.
   Reads image back and verifies if requested, controls NVR Mailbox CRC if requested */
AQ_Retcode AQ_API_WriteAndVerifyFlashImageOfKnownFLASH
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! The FLASH type */
  AQ_API_FLASH flashType,
    /*! The number of bytes to be loaded from the Aquantia PHY's FLASH
      into the image array.*/
  const uint32_t imageSize,
    /*! The image being loaded from the Aquantia PHY's FLASH.*/
  const uint8_t* image,
    /*! CRC16 calculated on image (if NULL, then would be calculated inside) */
  const uint16_t* crc16,
    /*! Should image been verified after loading? */
  AQ_boolean verify,
    /*! Verbose mismatches on verify process */
  AQ_boolean verbose,
    /*! Should NVR Mailbox CRC been verified after loading? */
  AQ_boolean verifyNvrMailboxCrc
);

/*! Reads image and verifies it throw CRC-16 calculation.
   Check crc16 might be specified or calcuated inside the function */
AQ_Retcode AQ_API_VerifyFlashImageOfKnownFLASH
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! The FLASH type */
  AQ_API_FLASH flashType,
    /*! The number of bytes to be loaded from the Aquantia PHY's FLASH
      into the image array.*/
  const uint32_t imageSize, 
    /*! The image being loaded from the Aquantia PHY's FLASH.*/
  const uint8_t *image,
    /*! CRC16 calculated on image (if NULL, then would be calculated inside) */
  const uint16_t *crc16,
    /*! Verbose mismatches on verify process */
  AQ_boolean verbose
);

/*! Construct command words by specified parameters */
void AQ_API_SetupFlashCommandWords
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
  uint16_t opcode,        /*!< NVR instruction */
  uint16_t burstMode,     /*!< 1 = burst operation */
  uint16_t writeMode,     /*!< 1 = write */
  uint16_t addressLength, /*!< the length of the address field */
  uint16_t dummyLength,   /*!< the length of the dummy field used in some operations */
  uint16_t dataLength,    /*!< the length of the data burst */
  uint16_t* wordIF,       /*!< OUT the 16-bit setting for AQ_GlobalNvrInterface.u0.word_0 */
  uint16_t* wordProv      /*!< OUT the 16-bit setting for AQ_GlobalNvrProvisioning.u0.word_0 */
);

/*! Execute specified operation */
AQ_Retcode AQ_API_ExecuteNvrOperation
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams,
    /*! NVR Interface register value */
  const uint16_t wordIF, 
    /*! NVR Provisioning register value */
  const uint16_t wordProv, 
    /*! Optional address */
  uint32_t* address
);

/*! Read status register by specified command */
AQ_Retcode AQ_API_GetStatusRegister_Common
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! NVR Interface register value */
  const uint16_t wordIF, 
    /*! NVR Provisioning register value */
  const uint16_t wordProv, 
    /*! OUT: read value */
  uint16_t* statusRegister
);

/* Read 16bit-width status register */
AQ_Retcode AQ_API_GetStatusRegister_16
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams,
    /*! OUT: read value */
  uint16_t* statusRegister
);

/*! Writes status register if supported for specified flash type */
AQ_Retcode AQ_API_SetStatusRegister
(
    /*! The target PHY port.*/
  AQ_API_Port* port,
    /*! FLASH parameters and command words */
  AQ_API_FlashParams* flashParams,
    /*! Value to write */
  uint16_t statusRegister
);

#ifdef __cplusplus
}
#endif

#endif