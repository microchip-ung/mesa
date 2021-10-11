/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef _VTSS_LAGUNA_REGS_SDMMC_H_
#define _VTSS_LAGUNA_REGS_SDMMC_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a SDMMC
 *
 * Secure Digital MultiMedia Card Controller
 *
 ***********************************************************************/

/**
 * Register Group: \a SDMMC:SDMMC_REG
 *
 * Secure Digital MultiMedia Card Controller Register Group
 */


/**
 * \brief SDMA System Address / Argument 2 Register
 *
 * \details
 * This register contains the physical system memory address used for SDMA
 * transfers or the second argument for Auto CMD23.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_SSAR
 */
#define VTSS_SDMMC_SDMMC_SSAR                VTSS_IOREG(VTSS_TO_SDMMC,0x0)

/**
 * \brief
 * ADDR: SDMA System AddressThis field is the system memory address for a
 * SDMA transfer. When the SDMMC stops an SDMA transfer, this field
 * pointsto the system address of the next contiguous data position. This
 * field can be accessed only if no transaction is executing(i.e., after a
 * transaction has stopped). Read operations during transfers may return an
 * invalid value. An interrupt can begenerated to instruct the software to
 * update this field. Writing the next system address of the next data
 * position restarts theSDMA transfer.ARG2: Argument 2This field is used
 * with Auto CMD23 to set a 32-bit block count value to the CMD23 argument
 * while executing Auto CMD23.If Auto CMD23 is used with ADMA, the full
 * 32-bit block count value can be used. If Auto CMD23 is used without
 * ADMA, theavailable block count value is limited by SDMMC_BCR. In this
 * case, 65535 blocks is the maximum value.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_SSAR . ADDR_OR_ARG2
 */
#define  VTSS_F_SDMMC_SDMMC_SSAR_ADDR_OR_ARG2(x)  (x)
#define  VTSS_M_SDMMC_SDMMC_SSAR_ADDR_OR_ARG2     0xffffffff
#define  VTSS_X_SDMMC_SDMMC_SSAR_ADDR_OR_ARG2(x)  (x)


/**
 * \brief SDMMC Block Size and Block Count Register
 *
 * \details
 * This register is a combination of SDMMC_BSR and SDMMC_BCR registers.
 * SDMMC_BSBCR = {SDMMC_BCR[15:0], SDMMC_BSR[15:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_BSBCR
 */
#define VTSS_SDMMC_SDMMC_BSBCR               VTSS_IOREG(VTSS_TO_SDMMC,0x1)

/**
 * \brief
 * BLKCNT: Block Count for Current TransferThis field is used only if
 * SDMMC_TMCR.BCEN (Block Count Enable) is set to 1 and is valid only for
 * multiple block transfers.BLKCNT is the number of blocks to be
 * transferred and it must be set to a value between 1 and the maximum
 * block count.The SDMMC decrements the block count after each block
 * transfer and stops when the count reaches 0. When this field isset to 0,
 * no data block is transferred.This register should be accessed only when
 * no transaction is executing (i.e., after transactions are stopped).
 * During datatransfer, read operations on this register may return an
 * invalid value and write operations are ignored.When a suspend command is
 * completed, the number of blocks yet to be transferred can be determined
 * by reading this register.Before issuing a resume command, the previously
 * saved block count is restored.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_BSBCR . BLKCNT
 */
#define  VTSS_F_SDMMC_SDMMC_BSBCR_BLKCNT(x)   VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SDMMC_SDMMC_BSBCR_BLKCNT      VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SDMMC_SDMMC_BSBCR_BLKCNT(x)   VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * BOUNDARY: SDMA Buffer BoundaryThis field specifies the size of the
 * contiguous buffer in the system memory. The SDMA transfer waits at every
 * boundaryspecified by this field and the SDMMC generates the DMA
 * Interrupt to instruct the software to update SDMMC_SSAR. Ifthis field is
 * set to 0 (buffer size = 4 Kbytes), the lowest 12 bits of
 * SDMMC_SSAR.ADDR_OR_ARG2 point to data in the contiguousbuffer, and the
 * upper 20 bits point to the location of the buffer in the system memory.
 * This function is active whenSDMMC_TMCR.DMAEN is set.
 *
 * \details
 * Value = 0; Name = 4K; Description = 4-Kbyte boundary
 * Value = 1; Name = 8K; Description = 8-Kbyte boundary
 * Value = 2; Name = 16K; Description = 16-Kbyte boundary
 * Value = 3; Name = 32K; Description = 32-Kbyte boundary
 * Value = 4; Name = 64K; Description = 64-Kbyte boundary
 * Value = 5; Name = 128K; Description = 128-Kbyte boundary
 * Value = 6; Name = 256K; Description = 256-Kbyte boundary
 * Value = 7; Name = 512K; Description = 512-Kbyte boundary
 *
 * Field: ::VTSS_SDMMC_SDMMC_BSBCR . BOUNDARY
 */
#define  VTSS_F_SDMMC_SDMMC_BSBCR_BOUNDARY(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_SDMMC_SDMMC_BSBCR_BOUNDARY     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_SDMMC_SDMMC_BSBCR_BOUNDARY(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * BLKSIZE: Transfer Block SizeThis field specifies the block size of data
 * transfers for CMD14, CMD17, CMD18, CMD19, CMD24, CMD25, CMD53 andother
 * data transfer commands such as CMD6, CMD8, ACMD13 and ACMD51. Values
 * ranging from 1 toMAX_BLOCK_SIZE can be set. It can be accessed only if
 * no transaction is executing (i.e., after a transaction has stopped).Read
 * operations during transfers may return an invalid value, and write
 * operations are ignored.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_BSBCR . BLKSIZE
 */
#define  VTSS_F_SDMMC_SDMMC_BSBCR_BLKSIZE(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SDMMC_SDMMC_BSBCR_BLKSIZE     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SDMMC_SDMMC_BSBCR_BLKSIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief SDMMC Argument 1 Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_ARG1R
 */
#define VTSS_SDMMC_SDMMC_ARG1R               VTSS_IOREG(VTSS_TO_SDMMC,0x2)

/**
 * \brief
 * ARG1: Argument 1This register contains the SD command argument which is
 * specified as the bit 39-8 of Command-Format in the PhysicalLayer
 * Simplified Specification V3.01 or Embedded MultiMedia Card (e.MMC)
 * Electrical Standard 4.51.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_ARG1R . ARG1
 */
#define  VTSS_F_SDMMC_SDMMC_ARG1R_ARG1(x)     (x)
#define  VTSS_M_SDMMC_SDMMC_ARG1R_ARG1        0xffffffff
#define  VTSS_X_SDMMC_SDMMC_ARG1R_ARG1(x)     (x)


/**
 * \brief SDMMC Transfer Mode and Command Register
 *
 * \details
 * This register is a combination of SDMMC_TMR and SDMMC_CR registers.
 * SDMMC_TMCR = {SDMMC_CR[15:0], SDMMC_TMR[15:0]}
 *
 * This register is used to control data transfers. The user shall set this
 * register before issuing a command which transfers
 * data [see SDMMC_TMCR.DPSEL], or before issuing a Resume command. The
 * user must save the value of this register when
 * the data transfer is suspended (as a result of a Suspend command) and
 * restore it before issuing a Resume command. To
 * prevent data loss, this register cannot be written while data
 * transactions are in progress. Writes to this register are ignored
 * when SDMMC_PSR.CMDINHD is 1.
 *
 * Determining the Transfer Type:
 *
 * MSBSEL, BCEN, BLKCNT[SDMMC_BCR], Function
 * 0 , Don't care, Don't care, Single Transfer
 * 1 , 0, Don't care, Infinite Transfer
 * 1,  1, Not Zero, Multiple Transfer
 * 1,  1, Zero. Stop Multiple Transfer
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_TMCR
 */
#define VTSS_SDMMC_SDMMC_TMCR                VTSS_IOREG(VTSS_TO_SDMMC,0x3)

/**
 * \brief
 * CMDIDX: Command IndexThis bit shall be set to the command number
 * (CMD0-63, ACMD0-63) that is specified in bits 45-40 of the
 * Command-Formatin the Physical Layer Simplified Specification V3.01, SDIO
 * Simplified Specification V3.00, and Embedded MultiMedia Card(e.MMC)
 * Electrical Standard 4.51.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . CMDIDX
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_CMDIDX(x)    VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_SDMMC_SDMMC_TMCR_CMDIDX       VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_SDMMC_SDMMC_TMCR_CMDIDX(x)    VTSS_EXTRACT_BITFIELD(x,24,6)

/**
 * \details
 * Value = 0, Name = NORMAL, Description = Other commands
 * Value = 1, Name = SUSPEND, Description = CMD52 to write "Bus Suspend" in
 * the Card Common Control Registers (CCCR) (for SDIO only)
 * Value = 2, Name = RESUME, Description = CMD52 to write "Function Select"
 * in the Card Common Control Registers (CCCR) (for SDIO only)
 * Value = 3, Nmae = ABORT, Description = CMD12, CMD52 to write "I/O Abort"
 * in the Card Common Control Registers (CCCR) (for SDIO only)
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . CMDTYP
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_CMDTYP(x)    VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_SDMMC_SDMMC_TMCR_CMDTYP       VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_SDMMC_SDMMC_TMCR_CMDTYP(x)    VTSS_EXTRACT_BITFIELD(x,22,2)

/**
 * \brief
 * DPSEL: Data Present SelectThis bit is set to 1 to indicate that data is
 * present and shall be transferred using the DAT lines. It is set to 0 for
 * the following:1. Commands using only CMD line (Ex. CMD52)2. Commands
 * with no data transfer but using Busy signal on DAT[0] line (Ex. CMD38)3.
 * Resume command
 *
 * \details
 * 0: No data present
 * 1: Data present
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . DPSEL
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_DPSEL(x)     VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SDMMC_SDMMC_TMCR_DPSEL        VTSS_BIT(21)
#define  VTSS_X_SDMMC_SDMMC_TMCR_DPSEL(x)     VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * CMDICEN: Command Index Check EnableIf this bit is set to 1, the SDMMC
 * checks the Index field in the response to see if it has the same value
 * as the commandindex. If it has not, it is reported as a Command Index
 * Error (CMDIDX) in SDMMC_NIEI_STR. If this bit is set to 0, the
 * Indexfield of the response is not checked.
 *
 * \details
 * 0 (DISABLED): The Command Index Check is disabled.
 * 1 (ENABLED):  The Command Index Check is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . CMDICEN
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_CMDICEN(x)   VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SDMMC_SDMMC_TMCR_CMDICEN      VTSS_BIT(20)
#define  VTSS_X_SDMMC_SDMMC_TMCR_CMDICEN(x)   VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * CMDCCEN: Command CRC Check EnableIf this bit is set to 1, the SDMMC
 * checks the CRC field in the response. If an error is detected, it is
 * reported as a CommandCRC Error (CMDCRC) in SDMMC_NIEI_STR. If this bit
 * is set to 0, the CRC field is not checked. The position of the CRC
 * fieldis determined according to the length of the response.
 *
 * \details
 * 0 (DISABLED): The Command CRC Check is disabled.
 * 1 (ENABLED): The Command CRC Check is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . CMDCCEN
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_CMDCCEN(x)   VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_TMCR_CMDCCEN      VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_TMCR_CMDCCEN(x)   VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * This field is set according to the response type expected for the
 * command index (CMDIDX).
 *
 * \details
 * Value = 0; Name = NORESP; Description = No Response
 * Value = 1; Name = RL136; Description = Response Length 136
 * Value = 2; Name = CMD23; Description = Response Length 48
 * Value = 3; Name = RL48BUSY; Description = Response Length 48 with Busy
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . RESPTYP
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_RESPTYP(x)   VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SDMMC_SDMMC_TMCR_RESPTYP      VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SDMMC_SDMMC_TMCR_RESPTYP(x)   VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * MSBSEL: Multi/Single Block SelectionThis bit is set to 1 when issuing
 * multiple-block transfer commands using DAT line(s). For any other
 * commands, set this bitto 0. If this bit is 0, it is not necessary to set
 * SDMMC_BCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . MSBSEL
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_MSBSEL(x)    VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_TMCR_MSBSEL       VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_TMCR_MSBSEL(x)    VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DTDSEL: Data Transfer Direction SelectionThis bit defines the direction
 * of the DAT lines data transfers. Set this bit to 1 to transfer data from
 * the device (SDCard/SDIO/e.MMC) to the SDMMC, and to 0 for all other
 * commands.
 *
 * \details
 * 0 (WRITE): Writes data from the SDMMC to the device.
 * 1 (READ):   Reads data from the device to the SDMMC.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . DTDSEL
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_DTDSEL(x)    VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_TMCR_DTDSEL       VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_TMCR_DTDSEL(x)    VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Two methods can be used to stop Multiple-block read and write
 * operation:Auto CMD12: when the ACMDEN field is set to 1, the SDMMC
 * issues CMD12 automatically when the last block transferis completed. An
 * Auto CMD12 error is indicated to SDMMC_ACESR. Auto CMD12 is not enabled
 * if the command doesnot require CMD12.Auto CMD23: when the ACMDEN field
 * is set to 2, the SDMMC issues a CMD23 automatically before issuing
 * acommand specified in SDMMC_CR.The following conditions are required to
 * use Auto CMD23:1. A memory card that supports CMD23 (SCR[33] = 1).2. If
 * DMA is used, it must be ADMA (SDMA not supported).3. Only CMD18 or CMD25
 * is issued.Note: The SDMMC does not check the command index.Auto CMD23
 * can be used with or without ADMA. By writing SDMMC_CR, the SDMMC issues
 * a CMD23 first and thenissues a command specified by the
 * SDMMC_TMCR.CMDIDX field. If CMD23 response errors are detected, the
 * secondcommand is not issued. A CMD23 error is indicated in SDMMC_ACESR.
 * The CMD23 argument (32-bit block countvalue) is set in SDMMC_SSAR.
 *
 * \details
 * This field determines the use of auto command functions.
 *
 * Value = 0; Name = DISABLED; Description = Auto Command Disabled
 * Value = 1; Name = CMD12; Description = Auto CMD12 Enabled
 * Value = 2; Name = CMD23; Description = Auto CMD23 Enabled
 * Value = 3; Name = Reserved; Description = Reserved
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . ACMDEN
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_ACMDEN(x)    VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SDMMC_SDMMC_TMCR_ACMDEN       VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SDMMC_SDMMC_TMCR_ACMDEN(x)    VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * BCEN: Block Count EnableThis bit is used to enable SDMMC_BCR, which is
 * only relevant for multiple block transfers. When this bit is 0,SDMMC_BCR
 * is disabled, which is useful when executing an infinite transfer. If an
 * ADMA2 transfer ismore than 65535 blocks, this bit is set to 0 and the
 * data transfer length is designated by the Descriptor Table.
 *
 * \details
 * 0 [DISABLED]: Block count is disabled.
 * 1 [ENABLED]:  Block count is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . BCEN
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_BCEN(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_TMCR_BCEN         VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_TMCR_BCEN(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * DMAEN: DMA EnableThis bit enables the DMA functionality described in
 * section "Supporting DMA" in SD Host Controller Simplified
 * SpecificationV3.00. DMA can be enabled only if it is supported as
 * indicated by the bit SDMMC_CA0R.ADMA2SUP. One of the DMAmodes can be
 * selected using the field SDMMC_HC1R.DMASEL. If DMA is not supported,
 * this bit is meaningless and thenalways reads 0. When this bit is set to
 * 1, a DMA operation begins when the user writes to the upper byte of
 * SDMMC_CR.
 *
 * \details
 * 0 [DISABLED]: DMA functionality is disabled.
 * 1 [ENABLED]:  DMA functionality is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TMCR . DMAEN
 */
#define  VTSS_F_SDMMC_SDMMC_TMCR_DMAEN(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_TMCR_DMAEN        VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_TMCR_DMAEN(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Response Register 0
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_RR0
 */
#define VTSS_SDMMC_SDMMC_RR0                 VTSS_IOREG(VTSS_TO_SDMMC,0x4)

/**
 * \brief
 * CMDRESP0: Command ResponseThe table below describes the mapping of
 * command responses from the SD_SDIO/e.MMC bus to these registers for
 * eachresponses type.
 *
 * \details
 * In this table, R[] refers to a bit range of the response data as
 * transmitted on the SD_SDIO/e.MMC bus.
 *
 * Type of response =  R1, R1b (normal response); Meaning of response =
 * Card Status; Response field =  R[39:8], Response register =
 * SDMMC_RR0[31:0]
 * Type of response = R1b (Auto CMD12 response); Meaning of response = Card
 * Status for Auto CMD12; Response field = R[39:8]; Response register =
 * SDMMC_RR3[31:0]
 * Type of response = R1 (Auto CMD23 response); Meaning of response = Card
 * Status for Auto CMD23; Response field = R[39:8]; Response register =
 * SDMMC_RR3[31:0]
 * Type of response = R2 (CID, CSD register); Meaning of response = CID or
 * CSD Register; Response field = R[127:8]; Response register =
 * SDMMC_RR0/1/2 [31:0], SDMMC_RR3[23:0]
 * Type of response = R3 (OCR register); Meaning of response = OCR register
 * for memory; Response field = R[39:8]; Response register =
 * SDMMC_RR0[31:0]
 * Type of response = R4 (OCR register); Meaning of response = OCR register
 * for I/O; Response field = R[39:8]; Response register =  SDMMC_RR0[31:0]
 * Type of response = R5, R5b; Meaning of response = SDIO response;
 * Response field = R[39:8]; Response register =  SDMMC_RR0[31:0]
 * Type of response = R6 (Published RCA response); Meaning of response =
 * New published RCA[31:16] and card status bits; Response field = R[39:8];
 * Response register =	SDMMC_RR0[31:0]
 *
 * Field: ::VTSS_SDMMC_SDMMC_RR0 . CMDRESP0
 */
#define  VTSS_F_SDMMC_SDMMC_RR0_CMDRESP0(x)   (x)
#define  VTSS_M_SDMMC_SDMMC_RR0_CMDRESP0      0xffffffff
#define  VTSS_X_SDMMC_SDMMC_RR0_CMDRESP0(x)   (x)


/**
 * \brief SDMMC Response Register 1
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_RR1
 */
#define VTSS_SDMMC_SDMMC_RR1                 VTSS_IOREG(VTSS_TO_SDMMC,0x5)

/**
 * \brief
 * CMDRESP1: Command ResponseThe table below describes the mapping of
 * command responses from the SD_SDIO/e.MMC bus to these registers for
 * eachresponses type.
 *
 * \details
 * In this table, R[] refers to a bit range of the response data as
 * transmitted on the SD_SDIO/e.MMC bus.
 *
 * Type of response =  R1, R1b (normal response); Meaning of response =
 * Card Status; Response field =  R[39:8], Response register =
 * SDMMC_RR0[31:0]
 * Type of response = R1b (Auto CMD12 response); Meaning of response = Card
 * Status for Auto CMD12; Response field = R[39:8]; Response register =
 * SDMMC_RR3[31:0]
 * Type of response = R1 (Auto CMD23 response); Meaning of response = Card
 * Status for Auto CMD23; Response field = R[39:8]; Response register =
 * SDMMC_RR3[31:0]
 * Type of response = R2 (CID, CSD register); Meaning of response = CID or
 * CSD Register; Response field = R[127:8]; Response register =
 * SDMMC_RR0/1/2 [31:0], SDMMC_RR3[23:0]
 * Type of response = R3 (OCR register); Meaning of response = OCR register
 * for memory; Response field = R[39:8]; Response register =
 * SDMMC_RR0[31:0]
 * Type of response = R4 (OCR register); Meaning of response = OCR register
 * for I/O; Response field = R[39:8]; Response register =  SDMMC_RR0[31:0]
 * Type of response = R5, R5b; Meaning of response = SDIO response;
 * Response field = R[39:8]; Response register =  SDMMC_RR0[31:0]
 * Type of response = R6 (Published RCA response); Meaning of response =
 * New published RCA[31:16] and card status bits; Response field = R[39:8];
 * Response register =	SDMMC_RR0[31:0]
 *
 * Field: ::VTSS_SDMMC_SDMMC_RR1 . CMDRESP1
 */
#define  VTSS_F_SDMMC_SDMMC_RR1_CMDRESP1(x)   (x)
#define  VTSS_M_SDMMC_SDMMC_RR1_CMDRESP1      0xffffffff
#define  VTSS_X_SDMMC_SDMMC_RR1_CMDRESP1(x)   (x)


/**
 * \brief SDMMC Response Register 2
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_RR2
 */
#define VTSS_SDMMC_SDMMC_RR2                 VTSS_IOREG(VTSS_TO_SDMMC,0x6)

/**
 * \brief
 * CMDRESP2: Command ResponseThe table below describes the mapping of
 * command responses from the SD_SDIO/e.MMC bus to these registers for
 * eachresponses type.
 *
 * \details
 * In this table, R[] refers to a bit range of the response data as
 * transmitted on the SD_SDIO/e.MMC bus.
 *
 * Type of response =  R1, R1b (normal response); Meaning of response =
 * Card Status; Response field =  R[39:8], Response register =
 * SDMMC_RR0[31:0]
 * Type of response = R1b (Auto CMD12 response); Meaning of response = Card
 * Status for Auto CMD12; Response field = R[39:8]; Response register =
 * SDMMC_RR3[31:0]
 * Type of response = R1 (Auto CMD23 response); Meaning of response = Card
 * Status for Auto CMD23; Response field = R[39:8]; Response register =
 * SDMMC_RR3[31:0]
 * Type of response = R2 (CID, CSD register); Meaning of response = CID or
 * CSD Register; Response field = R[127:8]; Response register =
 * SDMMC_RR0/1/2 [31:0], SDMMC_RR3[23:0]
 * Type of response = R3 (OCR register); Meaning of response = OCR register
 * for memory; Response field = R[39:8]; Response register =
 * SDMMC_RR0[31:0]
 * Type of response = R4 (OCR register); Meaning of response = OCR register
 * for I/O; Response field = R[39:8]; Response register =  SDMMC_RR0[31:0]
 * Type of response = R5, R5b; Meaning of response = SDIO response;
 * Response field = R[39:8]; Response register =  SDMMC_RR0[31:0]
 * Type of response = R6 (Published RCA response); Meaning of response =
 * New published RCA[31:16] and card status bits; Response field = R[39:8];
 * Response register =	SDMMC_RR0[31:0]
 *
 * Field: ::VTSS_SDMMC_SDMMC_RR2 . CMDRESP2
 */
#define  VTSS_F_SDMMC_SDMMC_RR2_CMDRESP2(x)   (x)
#define  VTSS_M_SDMMC_SDMMC_RR2_CMDRESP2      0xffffffff
#define  VTSS_X_SDMMC_SDMMC_RR2_CMDRESP2(x)   (x)


/**
 * \brief SDMMC Response Register 2
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_RR3
 */
#define VTSS_SDMMC_SDMMC_RR3                 VTSS_IOREG(VTSS_TO_SDMMC,0x7)

/**
 * \brief
 * CMDRESP3: Command ResponseThe table below describes the mapping of
 * command responses from the SD_SDIO/e.MMC bus to these registers for
 * eachresponses type.
 *
 * \details
 * In this table, R[] refers to a bit range of the response data as
 * transmitted on the SD_SDIO/e.MMC bus.
 *
 * Type of response =  R1, R1b (normal response); Meaning of response =
 * Card Status; Response field =  R[39:8], Response register =
 * SDMMC_RR0[31:0]
 * Type of response = R1b (Auto CMD12 response); Meaning of response = Card
 * Status for Auto CMD12; Response field = R[39:8]; Response register =
 * SDMMC_RR3[31:0]
 * Type of response = R1 (Auto CMD23 response); Meaning of response = Card
 * Status for Auto CMD23; Response field = R[39:8]; Response register =
 * SDMMC_RR3[31:0]
 * Type of response = R2 (CID, CSD register); Meaning of response = CID or
 * CSD Register; Response field = R[127:8]; Response register =
 * SDMMC_RR0/1/2 [31:0], SDMMC_RR3[23:0]
 * Type of response = R3 (OCR register); Meaning of response = OCR register
 * for memory; Response field = R[39:8]; Response register =
 * SDMMC_RR0[31:0]
 * Type of response = R4 (OCR register); Meaning of response = OCR register
 * for I/O; Response field = R[39:8]; Response register =  SDMMC_RR0[31:0]
 * Type of response = R5, R5b; Meaning of response = SDIO response;
 * Response field = R[39:8]; Response register =  SDMMC_RR0[31:0]
 * Type of response = R6 (Published RCA response); Meaning of response =
 * New published RCA[31:16] and card status bits; Response field = R[39:8];
 * Response register =	SDMMC_RR0[31:0]
 *
 * Field: ::VTSS_SDMMC_SDMMC_RR3 . CMDRESP3
 */
#define  VTSS_F_SDMMC_SDMMC_RR3_CMDRESP3(x)   (x)
#define  VTSS_M_SDMMC_SDMMC_RR3_CMDRESP3      0xffffffff
#define  VTSS_X_SDMMC_SDMMC_RR3_CMDRESP3(x)   (x)


/**
 * \brief SDMMC Buffer Data Port Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_BDPR
 */
#define VTSS_SDMMC_SDMMC_BDPR                VTSS_IOREG(VTSS_TO_SDMMC,0x8)

/**
 * \brief
 * BUFDATA: Buffer DataThe SDMMC data buffer can be accessed through this
 * 32-bit Data Port register.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_BDPR . BUFDATA
 */
#define  VTSS_F_SDMMC_SDMMC_BDPR_BUFDATA(x)   (x)
#define  VTSS_M_SDMMC_SDMMC_BDPR_BUFDATA      0xffffffff
#define  VTSS_X_SDMMC_SDMMC_BDPR_BUFDATA(x)   (x)


/**
 * \brief SDMMC Present State Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_PSR
 */
#define VTSS_SDMMC_SDMMC_PSR                 VTSS_IOREG(VTSS_TO_SDMMC,0x9)

/**
 * \brief
 * CMDLL: CMD Line LevelThis status is used to check the CMD line level to
 * recover from errors, and for debugging.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PSR . CMDLL
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_CMDLL(x)      VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_CMDLL         VTSS_BIT(24)
#define  VTSS_X_SDMMC_SDMMC_PSR_CMDLL(x)      VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * DATLL: DAT[3:0] Line LevelThis status is used to check the DAT line
 * level to recover from errors, and for debugging. This is especially
 * useful in detectingthe Busy signal level from DAT[0].
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PSR . DATLL
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_DATLL(x)      VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_SDMMC_SDMMC_PSR_DATLL         VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_SDMMC_SDMMC_PSR_DATLL(x)      VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * WRPPL: Write Protect Pin LevelThe Write Protect Switch is supported for
 * memory and combo cards. This bit reflects the inverse value of the
 * SDMMC_WP pin.
 *
 * \details
 * 0: Write protected (SDMMC_WP = 1)
 * 1: Write enabled (SDMMC_WP = 0)
 *
 * Field: ::VTSS_SDMMC_SDMMC_PSR . WRPPL
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_WRPPL(x)      VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_WRPPL         VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_PSR_WRPPL(x)      VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * CARDDPL: Card Detect Pin LevelThis bit reflects the inverse value of the
 * SDMMC_CD pin. Debouncing is not performed on this bit. This bit may be
 * validwhen CARDSS is set to 1, but it is not guaranteed because of the
 * propagation delay. Use of this bit is limited to testingsince it must be
 * debounced by software.
 *
 * \details
 * 0: No card present (SDMMC_CD = 1).
 * 1: Card present (SDMMC_CD = 0).
 *
 * Field: ::VTSS_SDMMC_SDMMC_PSR . CARDDPL
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_CARDDPL(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_CARDDPL       VTSS_BIT(18)
#define  VTSS_X_SDMMC_SDMMC_PSR_CARDDPL(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * CARDSS: Card State StableThis bit is used for testing. If it is 0, the
 * CARDDPL is not stable. If this bit is set to 1, it means that the
 * CARDDPL is stable.No Card state can be detected if this bit is set to 1
 * and CARDINS is set to 0.The Software Reset For All (SWRSTALL) in
 * SDMMC_SRR does not affect this bit.
 *
 * \details
 * 0: Reset or debouncing.
 * 1: No card or card inserted.
 *
 * Field: ::VTSS_SDMMC_SDMMC_PSR . CARDSS
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_CARDSS(x)     VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_CARDSS        VTSS_BIT(17)
#define  VTSS_X_SDMMC_SDMMC_PSR_CARDSS(x)     VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * CARDINS: Card InsertedThis bit indicates whether a card has been
 * inserted. The SDMMC debounces this signal so that the user does not need
 * towait for it to stabilize.A change from 0 to 1 raises the Card
 * Insertion (CINS) status flag in SDMMC_NIEI_STR if
 * SDMMC_NIEI_STER.CINS_STA_EN is set to 1.An interrupt is generated if
 * SDMMC_NIEI_SIGER.CINS_SIG_EN is set to 1.A change from 1 to 0 raises the
 * Card Removal (CREM) status flag in SDMMC_NIEI_STR if
 * SDMMC_NIEI_STER.CREM_STA_EN is set to1. An interrupt is generated if
 * SDMMC_NIEI_SIGER.CREM_SIG_EN is set to 1.The Software Reset For All
 * (SWRSTALL) in SDMMC_SRR does not affect this bit.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PSR . CARDINS
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_CARDINS(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_CARDINS       VTSS_BIT(16)
#define  VTSS_X_SDMMC_SDMMC_PSR_CARDINS(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * BUFRDEN: Buffer Read EnableThis bit is used for nonDMA read transfers.
 * This flag indicates that valid data exists in the SDMMC data buffer. If
 * this bit is1, readable data exists in the buffer.A change from 1 to 0
 * occurs when all the block data is read from the buffer.A change from 0
 * to 1 occurs when block data is ready in the buffer. This raises the
 * Buffer Read Ready (BRDRDY) statusflag in SDMMC_NIEI_STR if
 * SDMMC_NIEI_STER.BRDRDY_STA_EN is set to 1. An interrupt is generated if
 * SDMMC_NIEI_SIGER.BRDRDY_SIG_EN isset to 1.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PSR . BUFRDEN
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_BUFRDEN(x)    VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_BUFRDEN       VTSS_BIT(11)
#define  VTSS_X_SDMMC_SDMMC_PSR_BUFRDEN(x)    VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * BUFWREN: Buffer Write EnableThis bit is used for nonDMA write transfers.
 * This flag indicates if space is available for write data. If this bit is
 * 1, data can bewritten to the buffer.A change from 1 to 0 occurs when all
 * the block data are written to the buffer.A change from 0 to 1 occurs
 * when top of block data can be written to the buffer. This raises the
 * Buffer Write Ready(BWRRDY) status flag in SDMMC_NIEI_STR if
 * SDMMC_NIEI_STER.BWRRDY_STA_EN is set to 1. An interrupt is generated
 * ifSDMMC_NIEI_SIGER.BWRRDY_SIG_EN is set to 1.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PSR . BUFWREN
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_BUFWREN(x)    VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_BUFWREN       VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_PSR_BUFWREN(x)    VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * RTACT: Read Transfer ActiveThis bit is used to detect completion of a
 * read transfer. See section "Read Transaction Wait / Continue Timing" in
 * the SDHost Controller Simplified Specification V3.00 for more details on
 * the sequence of events.This bit is set to 1 in either of the following
 * conditions:1. After the end bit of the read command.2. When a read
 * operation is restarted by writing a 1 to SDMMC_HC1R.CONTR (Continue
 * Request).This bit is cleared to 0 in either of the following
 * conditions:1. When the last data block as specified by Transfer Block
 * Size (BLKSIZE) is transferred to the system.2. In case of ADMA2, end of
 * read is designated by the descriptor table.3. When all valid data blocks
 * in the SDMMC have been transferred to the system and no current block
 * transfersare being sent as a result of the Stop At Block Gap Request
 * (STPBGR) of SDMMC_BGCR being set to 1.A change from 1 to 0 raises the
 * Transfer Complete (TRFC) status flag in SDMMC_NIEI_STR if
 * SDMMC_NIEI_STER.TRFC_STA_EN is setto 1. An interrupt is generated if
 * SDMMC_NIEI_SIGER.TRFC_SIG_EN is set to 1.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PSR . RTACT
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_RTACT(x)      VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_RTACT         VTSS_BIT(9)
#define  VTSS_X_SDMMC_SDMMC_PSR_RTACT(x)      VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * WTACT: Write Transfer ActiveThis bit indicates a write transfer is
 * active. If this bit is 0, it means no valid write data exists in the
 * SDMMC. See section"Write Transaction Wait / Continue Timing" in the SD
 * Host Controller Simplified Specification V3.00 for more details on
 * thesequence of events.This bit is set to 1 in either of the following
 * conditions:1. After the end bit of the write command.2. When a write
 * operation is restarted by writing a 1 to SDMMC_HC1R.CONTR (Continue
 * Request).This bit is cleared to 0 in either of the following
 * conditions:1. After getting the CRC status of the last data block as
 * specified by the transfer count (single and multiple). Incase of ADMA2,
 * transfer count is designated by the descriptor table.2. After getting
 * the CRC status of any block where a data transmission is about to be
 * stopped by a Stop At BlockGap Request (STPBGR) of SDMMC_BGCR.During a
 * write transaction and as the result of the Stop At Block Gap Request
 * (STPBGR) being set, a change from 1 to 0raises the Block Gap Event
 * (BLKGE) status flag in SDMMC_NIEI_STR if SDMMC_NIEI_STER.BLKGE_STA_EN is
 * set to 1. An interrupt isgenerated if BLKGE is set to 1 in
 * SDMMC_NIEI_SIGER. This status is useful to determine whether nonDAT line
 * commands canbe issued during Write Busy.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PSR . WTACT
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_WTACT(x)      VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_WTACT         VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_PSR_WTACT(x)      VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * RTREQ: Retuning RequestThe SDMMC can instruct the software to execute a
 * retuning sequence by setting this bit when the data window is shifted
 * bya temperature drift and a tuned sampling point does not have a good
 * margin to receive correct data.This bit is cleared to 0 when a command
 * is issued by setting Execute Tuning (EXTUN) in SDMMC_HC2R.A change from
 * 0 to 1 raises the Retuning Event (RTEVT) status flag in SDMMC_NIEI_STR
 * if RTEVT is setto 1. An interrupt is generated if RTEVT is set to 1.This
 * bit is not set to 1 if Sampling Clock Select (SCLKSEL) in SDMMC_HC2R is
 * set to 0 (using a fixed sampling clock). SeeRetuning Modes (RTMOD) in
 * SDMMC_CA1R.
 *
 * \details
 * 0: Fixed or well-tuned sampling clock.
 * 1: Sampling clock needs retuning.
 *
 * Field: ::VTSS_SDMMC_SDMMC_PSR . RTREQ
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_RTREQ(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_RTREQ         VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_PSR_RTREQ(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DLACT: DAT Line ActiveThis bit indicates whether one of the DAT lines on
 * the bus is in use.In the case of read transactions:This status indicates
 * whether a read transfer is executing on the bus. A change from 1 to 0
 * resulting from setting theStop At Block Gap Request (STPBGR) raises the
 * Block Gap Event (BLKGE) status flag in SDMMC_NIEI_STR if
 * SDMMC_NIEI_STER.BLKGE_STA_EN is set to 1. An interrupt is generated if
 * SDMMC_NIEI_SIGER.BLKGE_SIG_EN is set to 1. See the section"Read
 * Transaction Wait / Continue Timing" in the SD Host Controller Simplified
 * Specification V3.00 for details on timing.This bit is set in either of
 * the following cases:1. After the end bit of the read command.2. When
 * writing 1 to SDMMC_HC1R.CONTR (Continue Request) to restart a read
 * transfer.This bit is SDMMC cleared in either of the following cases:1.
 * When the end bit of the last data block is sent from the bus to the
 * SDMMC. In case of ADMA2, the last block isdesignated by the last
 * transfer of the Descriptor Table.2. When a read transfer is stopped at
 * the block gap initiated by a Stop At Block Gap Request (STPBGR).The
 * SDMMC stops a read operation at the start of the interrupt cycle by
 * driving the Read Wait (DAT[2] line) or by stoppingthe SD Clock. If the
 * Read Wait signal is already driven (due to the fact that the data buffer
 * cannot receive data), theSDMMC can continue to stop the read operation
 * by driving the Read Wait signal. It is necessary to support the ReadWait
 * in order to use the Suspend/Resume operation.In the case of write
 * transactions:This status indicates that a write transfer is executing on
 * the bus. A change from 1 to 0 raises the Transfer Complete(TRFC) status
 * flag in SDMMC_NIEI_STR if SDMMC_NIEI_STER.TRFC_STA_EN is set to 1. An
 * interrupt is generated ifSDMMC_NIEI_SIGER.TRFC_SIG_EN is set to 1. See
 * the section "Write Transaction Wait / Continue Timing" in the SD Host
 * ControllerSimplified Specification V3.00 for details on timing.This bit
 * is set in either of the following cases:1. After the end bit of the
 * write command.2. When writing 1 to SDMMC_HC1R.CONTR (Continue Request)
 * to continue a write transfer.This bit is cleared in either of the
 * following cases:1. When the card releases Write Busy of the last data
 * block. If the card does not drive a Busy signal for 8 SDCLK,the SDMMC
 * considers the card drive "Not Busy". In the case of ADMA2, the last
 * block is designated by the lasttransfer of the Descriptor Table.2. When
 * the card releases Write Busy prior to wait for write transfer as a
 * result of a Stop At Block Gap Request(STPBGR).Command with Busy:This
 * status indicates whether a command that indicates Busy (ex. erase
 * command for memory) is executing on the bus.This bit is set to 1 after
 * the end bit of the command with Busy and cleared when Busy is
 * deasserted. A change from 1 to 0raises the Transfer Complete (TRFC)
 * status flag in SDMMC_NIEI_STR if SDMMC_NIEI_STER.TRFC_STA_EN is set to
 * 1. An interrupt isgenerated if SDMMC_NIEI_SIGER.TRFC_SIG_EN is set to 1.
 * See Figures 2.11 to 2.13 in the SD Host Controller Simplified
 * SpecificationV3.00.
 *
 * \details
 * 0: DAT line inactive.
 * 1: DAT line active.
 *
 * Field: ::VTSS_SDMMC_SDMMC_PSR . DLACT
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_DLACT(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_DLACT         VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_PSR_DLACT(x)      VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CMDINHD: Command Inhibit (DAT)This status bit is 1 if either the DAT
 * Line Active (DLACT) or the Read Transfer Active (RTACT) is set to 1. If
 * this bit is 0, itindicates that the SDMMC can issue the next command.
 * Commands with a Busy signal belong to Command Inhibit (DAT)(ex. R1b, R5b
 * type). A change from 1 to 0 raises the Transfer Complete (TRFC) status
 * flag in SDMMC_NIEI_STR ifSDMMC_NIEI_STER.TRFC_STA_EN is set to 1. An
 * interrupt is generated if SDMMC_NIEI_SIGER.TRFC_SIG_EN is set to 1.Note:
 * The software can save registers in the 000-00Dh range for a suspend
 * transaction after this bit has changed from 1 to 0.
 *
 * \details
 * 0: Can issue a command which uses the DAT line(s).
 * 1: Cannot issue a command which uses the DAT line(s).
 *
 * Field: ::VTSS_SDMMC_SDMMC_PSR . CMDINHD
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_CMDINHD(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_CMDINHD       VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_PSR_CMDINHD(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CMDINHC: Command Inhibit (CMD)If this bit is 0, it indicates the CMD
 * line is not in use and the SDMMC can issue a command using the CMD line.
 * This bit isset to 1 immediately after SDMMC_CR is written. This bit is
 * cleared when the command response is received. Auto CMD12and Auto CMD23
 * consist of two responses. In this case, this bit is not cleared by the
 * CMD12 or CMD23 response, but bythe Read/Write command response.Status
 * issuing Auto CMD12 is not read from this bit. So, if a command is issued
 * during Auto CMD12 operation, theSDMMC manages to issue both commands:
 * CMD12 and a command set by SDMMC_CR.Even if the Command Inhibit (DAT) is
 * set to 1, commands using only the CMD line can be issued if this bit is
 * 0.A change from 1 to 0 raises the Command Complete (CMDC) status flag in
 * SDMMC_NIEI_STR if SDMMC_NIEI_STER.CMDC_STA_EN isset to 1. An interrupt
 * is generated if SDMMC_NIEI_SIGER.CMDC_SIG_EN is set to 1.If the SDMMC
 * cannot issue the command because of a command conflict error (see
 * SDMMC_NIEI_STR.CMDCRC) orbecause of a 'Command Not Issued By Auto CMD12'
 * error (see Section 15.31 "SDMMC Auto CMD Error Status Register"),this
 * bit remains 1 and Command Complete is not set.
 *
 * \details
 * 0: Can issue a command using only CMD line.
 * 1: Cannot issue a command.
 *
 * Field: ::VTSS_SDMMC_SDMMC_PSR . CMDINHC
 */
#define  VTSS_F_SDMMC_SDMMC_PSR_CMDINHC(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_PSR_CMDINHC       VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_PSR_CMDINHC(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Host Control 1 Register (SD_SDIO)
 *
 * \details
 * This register is a combination of SDMMC_HC1R, SDMMC_PCR, SDMMC_BGCR,
 * SDMMC_WCR registers.
 * SDMMC_H1CR = {SDMMC_WCR[7:0], SDMMC_BGCR[7:0], SDMMC_PCR[7:0],
 * SDMMC_HC1R[7:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_HC1R
 */
#define VTSS_SDMMC_SDMMC_HC1R                VTSS_IOREG(VTSS_TO_SDMMC,0xa)

/**
 * \brief
 * WKENCREM: Wakeup Event Enable on Card RemovalThis bit enables a wakeup
 * event via Card Removal (CREM) in SDMMC_NIEI_STR. FN_WUS (Wakeup Support)
 * in the CIS(Card Information Structure) does not affect this bit.
 *
 * \details
 * 0 (DISABLED): Wakeup Event disabled.
 * 1 (ENABLED): Wakeup Event enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . WKENCREM
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_WKENCREM(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_WKENCREM     VTSS_BIT(26)
#define  VTSS_X_SDMMC_SDMMC_HC1R_WKENCREM(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * WKENCINS: Wakeup Event Enable on Card Insertion (SD_SDIO specific)This
 * bit enables a wakeup event via Card Insertion (CINS) in SDMMC_NIEI_STR.
 * FN_WUS (Wakeup Support) in the CIS(Card Information Structure) does not
 * affect this bit.
 *
 * \details
 * 0 (DISABLED): Wakeup Event disabled.
 * 1 (ENABLED): Wakeup Event enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . WKENCINS
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_WKENCINS(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_WKENCINS     VTSS_BIT(25)
#define  VTSS_X_SDMMC_SDMMC_HC1R_WKENCINS(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * WKENCINT: Wakeup Event Enable on Card Interrupt (SD_SDIO specific)This
 * bit enables a wakeup event via Card Interrupt (CINT) in SDMMC_NIEI_STR.
 * This bit can be set to 1 if FN_WUS (WakeupSupport) in the CIS (Card
 * Information Structure) is set to 1 in the SDIO card.
 *
 * \details
 * 0 (DISABLED): Wakeup Event disabled.
 * 1 (ENABLED): Wakeup Event enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . WKENCINT
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_WKENCINT(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_WKENCINT     VTSS_BIT(24)
#define  VTSS_X_SDMMC_SDMMC_HC1R_WKENCINT(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * INTBG: Interrupt at Block Gap (SD_SDIO specific)This bit is valid only
 * in 4-bit mode of the SDIO card and selects a sample point in the
 * interrupt cycle. Setting to 1 enablesinterrupt detection at the block
 * gap for a multiple block transfer. If the SDIO card cannot signal an
 * interrupt during a multipleblock transfer, this bit should be set to 0.
 * When the software detects an SDIO card insertion, it sets this bit
 * according to theCCCR of the SDIO card.
 *
 * \details
 * 0 (DISABLED): Interrupt detection disabled.
 * 1 (ENABLED): Interrupt detection enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . INTBG
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_INTBG(x)     VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_INTBG        VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_HC1R_INTBG(x)     VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * RWCTRL: Read Wait Control (SD_SDIO specific)The Read Wait control is
 * optional for SDIO cards. If the card supports Read Wait, set this bit to
 * enable use of the ReadWait protocol to stop read data using the
 * SDMMC_DAT[2] line. Otherwise, the SDMMC stops the SDCLK to hold
 * readdata, which restricts command generation. When the software detects
 * an SD card insertion, this bit must be set accordingto the CCCR of the
 * SDIO card. If the card does not support Read Wait, this bit shall never
 * be set to 1, otherwise anSDMMC_DAT line conflict may occur. If this bit
 * is set to 0, Suspend/Resume cannot be supported.
 *
 * \details
 * 0: Disables Read Wait control.
 * 1: Enables Read Wait control.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . RWCTRL
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_RWCTRL(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_RWCTRL       VTSS_BIT(18)
#define  VTSS_X_SDMMC_SDMMC_HC1R_RWCTRL(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * CONTR: Continue RequestThis bit is used to restart a transaction which
 * was stopped using a Stop At Block Gap Request (STPBGR). To cancel stopat
 * the block gap, set STPBGR to 0 and set this bit to 1 to restart the
 * transfer.The SDMMC automatically clears this bit in either of the
 * following cases:1. In the case of a read transaction, the DAT Line
 * Active (DLACT) changes from 0 to 1 as a read transactionrestarts.2. In
 * the case of a write transaction, the Write Transfer Active (WTACT)
 * changes from 0 to 1 as the writetransaction restarts.Therefore, it is
 * not necessary to set this bit to 0. If STPBGR is set to 1, any write to
 * this bit is ignored.See the "Abort Transaction" and "Suspend/Resume"
 * sections in the SD Host Controller Simplified Specification V3.00
 * formore details.
 *
 * \details
 * 0: No effect.
 * 1: Restart.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . CONTR
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_CONTR(x)     VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_CONTR        VTSS_BIT(17)
#define  VTSS_X_SDMMC_SDMMC_HC1R_CONTR(x)     VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * STPBGR: Stop At Block Gap RequestThis bit is used to stop executing read
 * and write transactions at the next block gap for nonDMA, SDMA, and ADMA
 * transfers.The user must leave this bit set to 1 until Transfer Complete
 * (TRFC) in SDMMC_NIEI_STR. Clearing both Stop At BlockGap Request and
 * Continue Request does not cause the transaction to restart. This bit can
 * be set whether the card supportsthe Read Wait signal or not.During read
 * transfers, the SDMMC stops the transaction by using the Read Wait signal
 * (SDMMC_DAT[2]) if supported, orby stopping the SD clock otherwise.In
 * case of write transfers in which the user writes data to SDMMC_BDPR,
 * this bit must be set to 1 after all the block of datais written. If this
 * bit is set to 1, the user does not write data to SDMMC_BDPR.This bit
 * affects Read Transfer Active (RTACT), Write Transfer Active (WTACT), DAT
 * Line Active (DLACT) and CommandInhibit (DAT) (CMDINHD) in SDMMC_PSR.See
 * the "Abort Transaction" and "Suspend/Resume" sections in the SD Host
 * Controller Simplified Specification V3.00 formore details.
 *
 * \details
 * 0: Transfer
 * 1: Stop
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . STPBGR
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_STPBGR(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_STPBGR       VTSS_BIT(16)
#define  VTSS_X_SDMMC_SDMMC_HC1R_STPBGR(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * SDBVSEL: SD Bus Voltage SelectBy setting this bit, the user selects the
 * voltage level for the card. Before setting this register, the user must
 * check the VoltageSupport in SDMMC_CA0R. If an unsupported voltage is
 * selected, the system does not supply the bus voltage.
 *
 * \details
 * 0 - 4 = Reserved
 * 5 = 1.8 Volt (Typical)
 * 6 = 3.0 Volt (Typical)
 * 7 = 3.3 Volt (Typical)
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . SDBVSEL
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_SDBVSEL(x)   VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_SDMMC_SDMMC_HC1R_SDBVSEL      VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_SDMMC_SDMMC_HC1R_SDBVSEL(x)   VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * SDBPWR: SD Bus PowerBefore setting this bit, the user must set the SD
 * Bus Voltage Select (SDBVSEL). This bit is automatically cleared by
 * theSDMMC if the card is removed. If this bit is cleared, the SDMMC stops
 * driving SDMMC_CMD and SDMMC_DAT[7:0] (tristate)and drives SDMMC_CK to
 * low level.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . SDBPWR
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_SDBPWR(x)    VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_SDBPWR       VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_HC1R_SDBPWR(x)    VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * CARDDSEL: Card Detect Signal SelectionThis bit selects the source for
 * the card detection.
 *
 * \details
 * 0: The SDMMC_CD pin is selected.
 * 1: The Card Detect Test Level (CARDDTL) is selected (for test purpose).
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . CARDDSEL
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_CARDDSEL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_CARDDSEL     VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_HC1R_CARDDSEL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * CARDDTL: Card Detect Test LevelThis bit is enabled while the Card Detect
 * Signal Selection (CARDDSEL) is set to 1 and it indicates whether the
 * card isinserted or not.
 *
 * \details
 * 0: No card.
 * 1: Card inserted.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . CARDDTL
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_CARDDTL(x)   VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_CARDDTL      VTSS_BIT(6)
#define  VTSS_X_SDMMC_SDMMC_HC1R_CARDDTL(x)   VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * EXTDW: Extended Data Width (e.MMC specific)This bit controls the 8-bit
 * Bus Width mode for embedded devices. Support of this function is
 * indicated in 8-bit Support forEmbedded Device in SDMMC_CA0R. If a device
 * supports the 8-bit mode, this may be set to 1. If this bit is 0, the bus
 * widthis controlled by Data Width (DW).This bit is not effective when
 * multiple devices are installed on a bus slot (Slot Type (SLTYPE) is set
 * to 10b inSDMMC_CA0R). In this case, each device bus width is controlled
 * by Bus Width Preset (BWDTPRE) in SDMMC_SBCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . EXTDW
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_EXTDW(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_EXTDW        VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_HC1R_EXTDW(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DMASEL: DMA SelectOne of the supported DMA modes can be selected. The
 * DMA modes supported are given in SDMMC_CA0R. Use of aselected DMA is
 * determined by DMA Enable (DMAEN) in SDMMC_TMR.
 *
 * \details
 * 0 = SDMA is selected
 * 1 = Reserved
 * 2 = 32-bit Address ADMA2 is selected
 * 3 = 64-bit Address ADMA2 is selected
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . DMASEL
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_DMASEL(x)    VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_SDMMC_SDMMC_HC1R_DMASEL       VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_SDMMC_SDMMC_HC1R_DMASEL(x)    VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * HSEN: High Speed EnableBefore setting this bit, the user must check High
 * Speed Support (HSSUP) in SDMMC_CA0R.If this bit is set to 0 (default),
 * the SDMMC outputs CMD line and DAT lines at the falling edge of the SD
 * clock (up to25 MHz). If this bit is set to 1, the SDMMC outputs the CMD
 * line and the DAT lines at the rising edge of the SD clock (up to50
 * MHz).If Preset Value Enable (PVALEN) in SDMMC_HC2R is set to 1, the user
 * needs to reset SD Clock Enable (SDCLKEN)before changing this bit to
 * avoid generating clock glitches. After setting this bit to 1, the user
 * sets SDCLEN to 1 again.
 *
 * \details
 * 0: Normal Speed mode.
 * 1: High Speed mode.
 *
 * Note:
 * 1. This bit is effective only if SDMMC_MCR_DEBR.DDR is set to 0.
 * 2. The clock divider (DIV) in SDMMC_CCR must be set to a value different
 * from 0 when HSEN is 1.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . HSEN
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_HSEN(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_HSEN         VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_HC1R_HSEN(x)      VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * DW: Data WidthThis bit selects the data width of the SDMMC. It must be
 * set to match the data width of the card.
 *
 * \details
 * (1_BIT): 1-bit mode.
 * 1 (4_BIT): 4-bit mode.
 * Note: If the Extended Data Transfer Width is 1, this bit has no effect
 * and the data width is 8-bit mode.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . DW
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_DW(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_DW           VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_HC1R_DW(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * LEDCTRL: LED ControlThis bit is used to caution the user not to remove
 * the card while it is being accessed. If the software is going to issue
 * multiplecommands, this bit is set to 1 during all transactions.
 *
 * \details
 * 0 (OFF): LED off.
 * 1 (ON): LED on.
 *
 * Field: ::VTSS_SDMMC_SDMMC_HC1R . LEDCTRL
 */
#define  VTSS_F_SDMMC_SDMMC_HC1R_LEDCTRL(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_HC1R_LEDCTRL      VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_HC1R_LEDCTRL(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Clock Control, Timeout Control, and Software Reset Register
 *
 * \details
 * This register is a combination of SDMMC_CCR, SDMMC_TCR, and SDMMC_SRR
 * registers.
 * SDMMC_CTSR = {SDMMC_SRR[7:0], SDMMC_TCR[7:0], SDMMC_CCR[15:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_CTSR
 */
#define VTSS_SDMMC_SDMMC_CTSR                VTSS_IOREG(VTSS_TO_SDMMC,0xb)

/**
 * \brief
 * SWRSTDAT: Software reset for DAT lineOnly part of a data circuit is
 * reset. The DMA circuit is also reset.The following registers and bits
 * are cleared by this bit:SDMMC Buffer Data Port Register- Buffer is
 * cleared and initialized.SDMMC Present State Register- Buffer Read Enable
 * (BUFRDEN)- Buffer Write Enable (BUFWREN)- Read Transfer Active (RTACT)-
 * Write Transfer Active (WTACT)- DAT Line Active (DATLL)- Command Inhibit
 * (DAT) (CMDINHD)SDMMC Block Gap Control Register (SD_SDIO)- Continue
 * Request (CONTR)- Stop At Block Gap Request (STPBGR)SDMMC Normal
 * Interrupt Status Register (SD_SDIO)- Buffer Read Ready (BRDRDY)- Buffer
 * Write Ready (BWRRDY)- DMA Interrupt (DMAINT)- Block Gap Event (BLKGE)-
 * Transfer Complete (TRFC)
 *
 * \details
 * 0: Work
 * 1: Reset
 *
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . SWRSTDAT
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_SWRSTDAT(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SDMMC_SDMMC_CTSR_SWRSTDAT     VTSS_BIT(26)
#define  VTSS_X_SDMMC_SDMMC_CTSR_SWRSTDAT(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * SWRSTCMD: Software reset for CMD lineOnly part of a command circuit is
 * reset.The following registers and bits are cleared by this bit:SDMMC
 * Present State Register- Command Inhibit (CMD) (CMDINHC)SDMMC Normal
 * Interrupt Status Register (SD_SDIO) and SDMMC Normal Interrupt Status
 * Register (e.MMC)- Command Complete (CMDC)
 *
 * \details
 * 0: Work
 * 1: Reset
 *
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . SWRSTCMD
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_SWRSTCMD(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SDMMC_SDMMC_CTSR_SWRSTCMD     VTSS_BIT(25)
#define  VTSS_X_SDMMC_SDMMC_CTSR_SWRSTCMD(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * SWRSTALL: Software reset for AllThis reset affects the entire SDMMC
 * except the card detection circuit. During initialization, the SDMMC must
 * be reset bysetting this bit to 1. This bit is automatically cleared to 0
 * when SDMMC_CA0R and SDMMC_CA1R are valid and the usercan read them. If
 * this bit is set to 1, the user should issue a reset command and
 * reinitialize the card.List of registers cleared to 0:- SDMMC SDMA System
 * Address / Argument 2 Register- SDMMC Block Size Register- SDMMC Block
 * Count Register- SDMMC Argument 1 Register- SDMMC Command Register- SDMMC
 * Transfer Mode Register- SDMMC Response Register- SDMMC Buffer Data Port
 * Register- SDMMC Present State Register (except CMDLL, DATLL, WRPPL,
 * CARDDDPL, CARDSS, CARDINS)- SDMMC Host Control 1 Register (SD_SDIO)-
 * SDMMC Host Control 1 Register (e.MMC)- SDMMC Power Control Register-
 * SDMMC Block Gap Control Register (SD_SDIO)- SDMMC Block Gap Control
 * Register (e.MMC)- SDMMC Wakeup Control Register (SD_SDIO)- SDMMC Clock
 * Control Register- SDMMC Timeout Control Register- SDMMC Normal Interrupt
 * Status Register (SD_SDIO)- SDMMC Error Interrupt Status Register
 * (SD_SDIO)- SDMMC Normal Interrupt Status Enable Register (SD_SDIO)-
 * SDMMC Error Interrupt Status Enable Register (SD_SDIO)- SDMMC Normal
 * Interrupt Signal Enable Register (SD_SDIO)- SDMMC Error Interrupt Signal
 * Enable Register (SD_SDIO)- SDMMC Auto CMD Error Status Register- SDMMC
 * Host Control 2 Register (SD_SDIO)- SDMMC ADMA Error Status Register-
 * SDMMC ADMA System Address Register- SDMMC Shared Bus Control Register
 * (SD_SDIO) (except NBCLKP, NBINTP, BWTPRE)- SDMMC Slot Interrupt Status
 * Register- SDMMC e.MMC Control 1 Register- SDMMC e.MMC Control 2
 * Register- SDMMC AHB Control Register- SDMMC Clock Control 2 Register-
 * SDMMC Retuning Control 1 Register- SDMMC Retuning Counter Value
 * Register- SDMMC Retuning Interrupt Status Enable Register- SDMMC
 * Retuning Interrupt Signal Enable Register- SDMMC Retuning Interrupt
 * Status Register- SDMMC Tuning Control Register- SDMMC Tuning Status
 * Register- SDMMC Capabilities Control Register (except KEY)- SDMMC
 * Calibration Control Register (except CALN, CALP)
 *
 * \details
 * 0: Work
 * 1: Reset
 *
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . SWRSTALL
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_SWRSTALL(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SDMMC_SDMMC_CTSR_SWRSTALL     VTSS_BIT(24)
#define  VTSS_X_SDMMC_SDMMC_CTSR_SWRSTALL(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * DTCVAL: Data Timeout Counter ValueThis value determines the interval at
 * which DAT line timeouts are detected. For more information about timeout
 * generation,see Data Timeout Error (DATTEO) in SDMMC_NIEI_STR. When
 * setting this register, the user can prevent inadvertent timeoutevents by
 * clearing the Data Timeout Error Status Enable (in
 * SDMMC_NIEI_STER).TIMEOUT (us) = 2 ^ (13 + DTVAL) / fFTEOCLK(MHz)Note:
 * DTCVAL = fHEXA is reserved
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . DTCVAL
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_DTCVAL(x)    VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SDMMC_SDMMC_CTSR_DTCVAL       VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SDMMC_SDMMC_CTSR_DTCVAL(x)    VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * This register is used to select the frequency of the SDCLK pin. There
 * are two SDCLK Frequency modes according to ClockGenerator Select
 * (CLKGSEL).The length of the clock divider (DIV) is extended to 10 bits
 * (DIV[9:8] = USDCLKFSEL, DIV[7:0] = SDCLKFSEL)1. 10-bit Divided Clock
 * Mode (CLKGSEL = 0):	fSDCLK = fBASECLK / (2 x DIV). If DIV = 0 then
 * fSDCLK = fBASECLK2. Programmable Clock Mode (CLKGSEL = 1): fSDCLK =
 * fMULTCLK / (DIV + 1)This field depends on the setting of Preset Value
 * Enable (PVALEN) in SDMMC_HC2R.If PVALEN = 0, this field is set by the
 * user.If PVALEN = 1, this field is automatically set to a value specified
 * in one of the SDMMC_PVR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . SDCLKFSEL
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_SDCLKFSEL(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SDMMC_SDMMC_CTSR_SDCLKFSEL     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SDMMC_SDMMC_CTSR_SDCLKFSEL(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * USDCLKFSEL: Upper Bits of SDCLK Frequency SelectThese bits expand the
 * SDCLK Frequency Select (SDCLKFSEL) to 10 bits. These two bits are
 * assigned to bit 09-08 of theclock divider as described in SDCLKFSEL.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . USDCLKFSEL
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_USDCLKFSEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_SDMMC_SDMMC_CTSR_USDCLKFSEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_SDMMC_SDMMC_CTSR_USDCLKFSEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * CLKGSEL: Clock Generator SelectThis bit is used to select the clock
 * generator mode in the SDCLK Frequency Select field. If the Programmable
 * mode is notsupported (SDMMC_CA1R.CLKMULT (Clock Multiplier) set to 0),
 * then this bit cannot be written and is always read at 0.This bit depends
 * on the setting of Preset Value Enable (PVALEN) in SDMMC_HC2R.If PVALEN =
 * 0, this bit is set by the user.If PVALEN = 1, this bit is automatically
 * set to a value specified in one of the SDMMC_PVRx.
 *
 * \details
 * 0: Divided Clock mode (BASECLK is used to generate SDCLK).
 * 1: Programmable Clock mode (MULTCLK is used to generate SDCLK).
 *
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . CLKGSEL
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_CLKGSEL(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_CTSR_CLKGSEL      VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_CTSR_CLKGSEL(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * SDCLKEN: SD Clock EnableThe SDMMC stops the SD Clock when writing this
 * bit to 0. SDCLK Frequency Select (SDCLKFSEL) can be changed whenthis bit
 * is 0. Then, the SDMMC maintains the same clock frequency until SDCLK is
 * stopped (Stop at SDCLK = 0). If CardInserted (CARDINS) in SDMMC_PSR is
 * cleared, this bit is also cleared.
 *
 * \details
 * 0: SD Clock disabled
 * 1: SD Clock enabled
 *
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . SDCLKEN
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_SDCLKEN(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_CTSR_SDCLKEN      VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_CTSR_SDCLKEN(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * INTCLKS: Internal Clock StableThis bit is set to 1 when the SD clock is
 * stable after setting SDMMC_CTSR.INTCLKEN (Internal Clock Enable) to 1.
 * Theuser must wait to set SD Clock Enable (SDCLKEN) until this bit is set
 * to 1.
 *
 * \details
 * 0: Internal clock not ready.
 * 1: Internal clock ready.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . INTCLKS
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_INTCLKS(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_CTSR_INTCLKS      VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_CTSR_INTCLKS(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * INTCLKEN: Internal Clock EnableThis bit is set to 0 when the SDMMC is
 * not used or is awaiting a wakeup interrupt. In this case, its internal
 * clock is stoppedto reach a very low power state. Registers are still
 * able to be read and written. The clock starts to oscillate when this bit
 * isset to 1. Once the clock oscillation is stable, the SDMMC sets
 * Internal Clock Stable (INTCLKS) in this register to 1.This bit does not
 * affect card detection.
 *
 * \details
 * 0: The internal clock stops.
 * 1: The internal clock oscillates.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CTSR . INTCLKEN
 */
#define  VTSS_F_SDMMC_SDMMC_CTSR_INTCLKEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_CTSR_INTCLKEN     VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_CTSR_INTCLKEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Normal Interrupt and Error Interrupt Status Register
 *
 * \details
 * This register is a combination of SDMMC_NISTR and SDMMC_EISTR registers.
 * SDMMC_NIEI_STR = {SDMMC_EISTR[15:0], SDMMC_NISTR[15:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_NIEI_STR
 */
#define VTSS_SDMMC_SDMMC_NIEI_STR            VTSS_IOREG(VTSS_TO_SDMMC,0xc)

/**
 * \brief
 * BOOTAE: Boot Acknowledge ErrorThis bit is set to 1 when detecting that
 * the e.MMC Boot Acknowledge Status has a value other than "010".This bit
 * can only be set to 1 if SDMMC_NIEI_STER.BOOTAE_STA_EN is set to 1. An
 * interrupt can only be generated ifSDMMC_NIEI_SIGER.BOOTAE_SIG_EN is set
 * to 1.Writing this bit to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . BOOTAE
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_BOOTAE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_BOOTAE   VTSS_BIT(28)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_BOOTAE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * ADMA: ADMA ErrorThis bit is set to 1 when the SDMMC detects errors
 * during an ADMA-based data transfer. The state of the ADMA at anerror
 * occurrence is saved in SDMMC_AESR.In addition, the SDMMC raises this
 * status flag when it detects some invalid description data (Valid = 0) at
 * the ST_FDS state(see section "Advanced DMA" in the SD Host Controller
 * Simplified Specification V3.00). ADMA Error Status (ERRST) inSDMMC_AESR
 * indicates that an error occurred in ST_FDS state. The user may find that
 * the Valid bit is not set at the errordescriptor.This bit can only be set
 * to 1 if SDMMC_NIEI_STER.ADMA_STA_EN is set to 1. An interrupt can only
 * be generated ifSDMMC_NIEI_SIGER.ADMA_SIG_EN is set to 1.Writing this bit
 * to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . ADMA
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_ADMA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_ADMA     VTSS_BIT(25)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_ADMA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * ACMD: Auto CMD ErrorAuto CMD12 and Auto CMD23 use this error status.
 * This bit is set to 1 when detecting that one of the 0 to 4 bits
 * inSDMMC_ACESR[4:0] has changed from 0 to 1. In the case of Auto CMD12,
 * this bit is set to 1, not only when errors occurin Auto CMD12, but also
 * when Auto CMD12 is not executed due to the previous command error.This
 * bit can only be set to 1 if SDMMC_NIEI_STER.ACMD_STA_EN is set to 1. An
 * interrupt can only be generated ifSDMMC_NIEI_SIGER.ACMD_SIG_EN is set to
 * 1.Writing this bit to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . ACMD
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_ACMD(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_ACMD     VTSS_BIT(24)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_ACMD(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CURLIM: Current Limit ErrorBy setting SD Bus Power (SDBPWR) in
 * SDMMC_PCR, the SDMMC is requested to supply power for the SD Bus.
 * TheSDMMC is protected from an illegal card by stopping power supply to
 * the card, in which case this bit indicates a failure status.Reading 1
 * means the SDMMC is not supplying power to the card due to some failure.
 * Reading 0 means that theSDMMC is supplying power and no error has
 * occurred. The SDMMC may require some sampling time to detect the
 * currentlimit.This bit can only be set to 1 if
 * SDMMC_NIEI_STER.CURLIM_STA_EN is set to 1. An interrupt can only be
 * generated ifSDMMC_NIEI_SIGER.CURLIM_SIG_EN is set to 1.Writing this bit
 * to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CURLIM
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CURLIM(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CURLIM   VTSS_BIT(23)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CURLIM(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * DATEND: Data End Bit ErrorThis bit is set to 1 either when detecting 0
 * at the end bit position of read data which uses the DAT line or at the
 * end bit positionof the CRC Status.This bit can only be set to 1 if
 * SDMMC_NIEI_STER.DATEND_STA_EN is set to 1. An interrupt can only be
 * generated ifSDMMC_NIEI_SIGER.DATEND_SIG_EN is set to 1.Writing this bit
 * to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . DATEND
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_DATEND(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_DATEND   VTSS_BIT(22)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_DATEND(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * DATCRC: Data CRC errorThis bit is set to 1 when detecting a CRC error
 * when transferring read data which uses the DAT line or when detecting
 * thatthe Write CRC Status has a value other than "010".This bit can only
 * be set to 1 if SDMMC_NIEI_STER.DATCRC_STA_EN is set to 1. An interrupt
 * can only be generated ifSDMMC_NIEI_SIGER.DATCRC_SIG_EN is set to
 * 1.Writing this bit to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . DATCRC
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_DATCRC(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_DATCRC   VTSS_BIT(21)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_DATCRC(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DATTEO: Data Timeout ErrorThis bit is set to 1 when detecting one of
 * following timeout conditions.- Busy timeout for R1b, R5b response type
 * (see Physical Layer Simplified Specification V3.01 and SDIOSimplified
 * Specification V3.00).- Busy timeout after Write CRC status.- Write CRC
 * Status timeout.- Read data timeoutThis bit can only be set to 1 if
 * SDMMC_NIEI_STER.DATTEO_STA_EN is set to 1. An interrupt can only be
 * generated ifSDMMC_NIEI_SIGER.DATTEO_SIG_EN is set to 1.Writing this bit
 * to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . DATTEO
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_DATTEO(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_DATTEO   VTSS_BIT(20)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_DATTEO(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * CMDIDXE: Command Index ErrorThis bit is set to 1 if a Command Index
 * error occurs in the command response.This bit can only be set to 1 if
 * SDMMC_NIEI_STER.CMDIDXE_STA_EN is set to 1. An interrupt can only be
 * generated ifSDMMC_NIEI_SIGER.CMDIDXE_SIG_EN is set to 1.Writing this bit
 * to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CMDIDXE
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CMDIDXE(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CMDIDXE  VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CMDIDXE(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * CMDEND: Command End Bit ErrorThis bit is set to 1 when detecting that
 * the end bit of a command response is 0.`This bit can only be set to 1 if
 * SDMMC_NIEI_STER.CMDEND_STA_EN is set to 1. An interrupt can only be
 * generated ifSDMMC_NIEI_SIGER.CMDEND_SIG_EN is set to 1.Writing this bit
 * to 1 clears this bit.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CMDEND
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CMDEND(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CMDEND   VTSS_BIT(18)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CMDEND(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * CMDCRC: Command CRC ErrorThe Command CRC Error is generated in two
 * cases.If a response is returned and the Command Timeout Error (CMDTEO)
 * is set to 0 (indicating no command timeout), this bitis set to 1 when
 * detecting a CRC error in the command response.The SDMMC detects a CMD
 * line conflict by monitoring the CMD line when a command is issued. If
 * the SDMMC drives theCMD line to 1 level, but detects 0 level on the CMD
 * line at the next SDCLK edge, then the SDMMC aborts the command(stops
 * driving the CMD line) and sets this bit to 1. CMDTEO is also set to 1 to
 * indicate a CMD line conflict (see Table 15-3).This bit can only be set
 * to 1 if SDMMC_NIEI_STER.CMDCRC_STA_EN is set to 1. An interrupt can only
 * be generated ifSDMMC_NIEI_SIGER.CMDCRC_SIG_EN is set to 1.Writing this
 * bit to 1 clears this bit.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CMDCRC
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CMDCRC(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CMDCRC   VTSS_BIT(17)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CMDCRC(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * CMDTEO: Command Timeout ErrorThis bit is set to 1 only if no response is
 * returned within 64 SDCLK cycles from the end bit of the command. If the
 * SDMMCdetects a CMD line conflict, in which case Command CRC Error
 * (CMDCRC) is also set to 1 as shown in Table 15-3, this bitis set without
 * waiting for 64 SDCLK cycles because the command is aborted by the
 * SDMMC.This bit can only be set to 1 if SDMMC_NIEI_STER.CMDTEO_STA_EN is
 * set to 1. An interrupt can only be generated
 * ifSDMMC_NIEI_SIGER.CMDTEO_SIG_EN is set to 1.Writing this bit to 1
 * clears this bit.Relations between CMDCRC and CMDTEO:CMDCRC = 0; CMDTEO =
 * 1; Types of error = No errorCMDCRC = 0; CMDTEO = 1; Types of error =
 * Response timeout errorCMDCRC = 1; CMDTEO = 0; Types of error = Response
 * CRC errorCMDCRC = 1; CMDTEO = 1; Types of error = Response CRC error
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CMDTEO
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CMDTEO(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CMDTEO   VTSS_BIT(16)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CMDTEO(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * ERRINT: Error InterruptIf any of the bits in SDMMC_NIEI_STR are set,
 * then this bit is set. Therefore, the user can efficiently test for an
 * error by checkingthis bit first. This bit is read-only.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . ERRINT
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_ERRINT(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_ERRINT   VTSS_BIT(15)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_ERRINT(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * BOOTAR: Boot Acknowledge Received (e.MMC specific)This bit is set to 1
 * when the SDMMC received a Boot Acknowledge pattern from the e.MMC.This
 * bit can only be set to 1 if SDMMC_NIEI_STER.BOOTAR_STA_EN is set to 1.
 * An interrupt can only be generated ifSDMMC_NIEI_SIGER.BOOTAR_SIG_EN is
 * set to 1.Writing this bit to 1 clears this bit.
 *
 * \details
 * 0: Boot Acknowledge pattern not received.
 * 1: Boot Acknowledge pattern received.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . BOOTAR
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_BOOTAR(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_BOOTAR   VTSS_BIT(14)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_BOOTAR(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * INTC: INT_C (SD_SDIO specific)This status is set if INT_C is set to 1 in
 * SDMMC_SBCR and the INT_C pin is at a in low level. Writing this bit to 1
 * does notclear this bit. It is cleared by resetting the INT_C interrupt
 * factor.This bit can only be set to 1 if SDMMC_NIEI_STER.INTC_STA_EN is
 * set to 1. An interrupt can only be generated
 * ifSDMMC_NIEI_SIGER.INTC_SIG_EN is set to 1.
 *
 * \details
 * 0: No interrupt is detected.
 * 1: INT_C is detected.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . INTC
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_INTC(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_INTC     VTSS_BIT(11)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_INTC(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * INTB: INT_BThis status is set if INT_B is set to 1 in SDMMC_SBCR and the
 * INT_B pin is at a low level. Writing this bit to 1 does notclear this
 * bit. It is cleared by resetting the INT_B interrupt factor.This bit can
 * only be set to 1 if SDMMC_NIEI_STER.INTB_STA_EN is set to 1. An
 * interrupt can only be generated ifSDMMC_NIEI_SIGER.INTB_SIG_EN is set to
 * 1.
 *
 * \details
 * 0: No interrupt is detected.
 * 1: INT_B is detected.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . INTB
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_INTB(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_INTB     VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_INTB(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * INTA: INT_A (SD_SDIO specific)This status is set if INT_A is set to 1 in
 * SDMMC_SBCR and the INT_A pin is at a low level. Writing this bit to 1
 * does notclear this bit. It is cleared by resetting the INT_A interrupt
 * factor.This bit can only be set to 1 if SDMMC_NIEI_STER.INTA_STA_EN is
 * set to 1. An interrupt can only be generated
 * ifSDMMC_NIEI_SIGER.INTA_SIG_EN is set to 1.
 *
 * \details
 * 0: No interrupt is detected.
 * 1: INT_A is detected.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . INTA
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_INTA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_INTA     VTSS_BIT(9)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_INTA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * CINT: Card Interrupt (SD_SDIO specific)Writing this bit to 1 does not
 * clear this bit. It is cleared by resetting the SD card interrupt factor.
 * In 1-bit mode, the SDMMCdetects the Card Interrupt without SDCLK to
 * support wakeup. In 4-bit mode, the Card Interrupt signal is sampled
 * during theinterrupt cycle, so there are some sample delays between the
 * interrupt signal from the SD card and the interrupt to thesystem.When
 * this bit has been set to 1 and the user needs to start this interrupt
 * service, Card Interrupt Status Enable (CINT) inSDMMC_NIEI_STER may be
 * set to 0 in order to clear the card interrupt statuses latched in the
 * SDMMC and to stop driving theinterrupt signal to the system. After
 * completion of the card interrupt service (it should reset interrupt
 * factors in the SD cardand the interrupt signal may not be asserted), set
 * SDMMC_NIEI_STER.CINT_STA_EN to 1 and start sampling the interrupt signal
 * again.Interrupt detected by DAT[1] is supported when there is one card
 * per slot. In case of a shared bus, interrupt pins are usedto detect
 * interrupts. If 0 is set to Interrupt Pin Select (INTPSEL) in SDMMC_SBCR,
 * this status is effective. If a nonzerovalue is set to INTPSEL, INT_A,
 * INT_B or INT_C is used as device interrupts.This bit can only be set to
 * 1 if SDMMC_NIEI_STER.CREM_STA_EN is set to 1. An interrupt can only be
 * generated ifSDMMC_NIEI_SIGER.CREM_SIG_EN is set to 1.
 *
 * \details
 * 0: No card interrupt.
 * 1: Card interrupt.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CINT
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CINT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CINT     VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CINT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * CREM: Card Removal (SD_SDIO specific)This status is set to 1 if Card
 * Inserted (CARDINS) in SDMMC_PSR changes from 1 to 0. When the user
 * writes this bit to 1to clear this status, the status of
 * SDMMC_PSR.CARDINS must be confirmed because the card detect state may
 * possiblybe changed when the user clears this bit and no interrupt event
 * can be generated.This bit can only be set to 1 if
 * SDMMC_NIEI_STER.CREM_STA_EN is set to 1. An interrupt can only be
 * generated ifSDMMC_NIEI_SIGER.CREM_SIG_EN is set to 1.Writing this bit to
 * 1 clears this bit.
 *
 * \details
 * 0: Card state unstable or card inserted.
 * 1: Card removed.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CREM
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CREM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CREM     VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CREM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * CINS: Card Insertion (SD_SDIO specific)This status is set if Card
 * Inserted (CARDINS) in SDMMC_PSR changes from 0 to 1. When the user
 * writes this bit to 1 toclear this status, the status of
 * SDMMC_PSR.CARDINS must be confirmed because the card detect state may
 * possibly bechanged when the user clears this bit and no interrupt event
 * can be generated.This bit can only be set to 1 if
 * SDMMC_NIEI_STER.CINS_STA_EN is set to 1. An interrupt can only be
 * generated ifSDMMC_NIEI_SIGER.CINS_SIG_EN is set to 1.Writing this bit to
 * 1 clears this bit.
 *
 * \details
 * 0: Card state unstable or card removed.
 * 1: Card inserted.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CINS
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CINS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CINS     VTSS_BIT(6)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CINS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * BRDRDY: Buffer Read ReadyThis status is set to 1 if the Buffer Read
 * Enable (BUFRDEN) changes from 0 to 1. See BUFRDEN in SDMMC_PSR.
 * Whileprocessing the tuning procedure (Execute Tuning (EXTUN) in
 * SDMMC_HC2R is set to 1), BRDRDY is set to 1 for everyCMD19
 * execution.This bit can only be set to 1 if SDMMC_NIEI_STER.BRDRDY_STA_EN
 * is set to 1. An interrupt can only be generated
 * ifSDMMC_NIEI_SIGER.BRDRDY_SIG_EN is set to 1.Writing this bit to 1
 * clears this bit.
 *
 * \details
 * 0: Not ready to read buffer.
 * 1: Ready to read buffer.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . BRDRDY
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_BRDRDY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_BRDRDY   VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_BRDRDY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * BWRRDY: Buffer Write ReadyThis status is set to 1 if the Buffer Write
 * Enable (BUFWREN) changes from 0 to 1. See BUFWREN in SDMMC_PSR.This bit
 * can only be set to 1 if SDMMC_NIEI_STER.BWRRDY_STA_EN is set to 1. An
 * interrupt can only be generated ifSDMMC_NIEI_SIGER.BWRRDY_SIG_EN is set
 * to 1.Writing this bit to 1 clears this bit.
 *
 * \details
 * 0: Not ready to write buffer.
 * 1: Ready to write buffer.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . BWRRDY
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_BWRRDY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_BWRRDY   VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_BWRRDY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * DMAINT: DMA InterruptThis status is set if the SDMMC detects the Host
 * SDMA Buffer boundary during transfer. See SDMA Buffer Boundary(BOUNDARY)
 * in SDMMC_BSR.In case of ADMA, by setting the "int" field in the
 * descriptor table, the SDMMC raises this status flag when the descriptor
 * lineis completed. This status flag does not rise after Transfer Complete
 * (TRFC).This bit can only be set to 1 if SDMMC_NIEI_STER.DMAINT_STA_EN is
 * set to 1. An interrupt can only be generated
 * ifSDMMC_NIEI_SIGER.DMAINT_SIG_EN is set to 1.Writing this bit to 1
 * clears this bit.
 *
 * \details
 * 0: No DMA Interrupt.
 * 1: DMA Interrupt.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . DMAINT
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_DMAINT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_DMAINT   VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_DMAINT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * BLKGE: Block Gap EventIf the Stop At Block Gap Request (STPBGR) in
 * SDMMC_BGCR is set to 1, this bit is set when either a read or a write
 * transactionis stopped at a block gap. If STPBGR is not set to 1, this
 * bit is not set to 1.In the case of a Read transaction:This bit is set at
 * the falling edge of the DAT Line Active (DLACT) status (when the
 * transaction is stopped at SD bus timing).The Read Wait must be supported
 * in order to use this function. See section "Read Transaction Wait /
 * ContinueTiming" in the SD Host Controller Simplified Specification V3.00
 * about the detailed timing.In the case of a Write transaction:This bit is
 * set at the falling edge of the Write Transfer Active (WTACT) status
 * (after getting the CRC status at SD bustiming). See section "Write
 * Transaction Wait / Continue Timing" in the SD Host Controller Simplified
 * Specification V3.00for more details on the sequence of events.This bit
 * can only be set to 1 if SDMMC_NIEI_STER.BLKGE_STA_EN is set to 1. An
 * interrupt can only be generated ifSDMMC_NIEI_SIGER.BLKGE_SIG_EN is set
 * to 1.Writing this bit to 1 clears this bit.
 *
 * \details
 * 0: No block gap event.
 * 1: Transaction stopped at block gap.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . BLKGE
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_BLKGE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_BLKGE    VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_BLKGE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TRFC: Transfer CompleteThis bit is set when a read/write transfer and a
 * command with Busy is completed.In the case of a Read Transaction:This
 * bit is set at the falling edge of the Read Transfer Active Status. The
 * interrupt is generated in two cases. The first iswhen a data transfer is
 * completed as specified by the data length (after the last data has been
 * read to the system). Thesecond is when data has stopped at the block gap
 * and completed the data transfer by setting the Stop At Block GapRequest
 * (STPBGR) in SDMMC_BGCR (after valid data has been read to the system).
 * See section "Read TransactionWait / Continue Timing" in the SD Host
 * Controller Simplified Specification V3.00 for more details on the
 * sequence ofevents.In the case of a Write Transaction:This bit is set at
 * the falling edge of the DAT Line Active (DLACT) status. This interrupt
 * is generated in two cases. Thefirst is when the last data is written to
 * the card as specified by the data length and the Busy signal is
 * released. The secondis when data transfers are stopped at the block gap
 * by setting Stop At Block Gap Request (STPBGR) inSDMMC_BGCR and data
 * transfers are completed. (After valid data is written to the card and
 * the Busy signal isreleased). See section "Write Transaction Wait /
 * Continue Timing" in the SD Host Controller Simplified SpecificationV3.00
 * for more details on the sequence of events.In the case of command with
 * Busy:This bit is set when Busy is deasserted. See DAT Line Active
 * (DLACT) and Command Inhibit (DAT) (CMDINHD) inSDMMC_PSR.This bit can
 * only be set to 1 if SDMMC_NIEI_STER.TRFC_STA_EN is set to 1. An
 * interrupt can only be generated ifSDMMC_NIEI_SIGER.TRFC_SIG_EN is set to
 * 1.Writing this bit to 1 clears this bit.The table below shows that
 * Transfer Complete (TRFC) has a higher priority than Data Timeout Error
 * (DATTEO). If both bitsare set to 1, execution of a command can be
 * considered to be completed.TRFC = 0; DATTEO = 0; Meaning of the status =
 * Interrupted by another factorTRFC = 0; DATTEO = 1; Meaning of the status
 * = Timeout occurred during transferTRFC = 1; DATTEO = Don't Care; Meaning
 * of the status = Command execution complete
 *
 * \details
 * 0: Command execution is not complete.
 * 1: Command execution is complete.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . TRFC
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_TRFC(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_TRFC     VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_TRFC(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CMDC: Command CompleteThis bit is set when getting the end bit of the
 * command response. Auto CMD12 and Auto CMD23 consist of two
 * responses.Command Complete is not generated by the response of CMD12 or
 * CMD23, but it is generated by the response of aread/write command. See
 * Command Inhibit (CMD) in SDMMC_PSR for details on how to control this
 * bit.This bit can only be set to 1 if SDMMC_NIEI_STER.CMDC_STA_EN is set
 * to 1. An interrupt can only be generated ifSDMMC_NIEI_SIGER.CMDC_SIG_EN
 * is set to 1.Writing this bit to 1 clears this bit.The table below shows
 * that Command Timeout Error (CMDTEO) has a higher priority than Command
 * Complete (CMDC).If both bits are set to 1, it can be considered that the
 * response was not received correctly.CMDC = 0; CMDTEO = 0; Meaning of the
 * status = Interrupted by another factorCMDC = Don't care; CMDTEO = 1;
 * Meaning of the status = Response not received within 64 SDCLK cycles
 * CMDC = 1; CMDTEO = 0; Meaning of the status = Response received
 *
 * \details
 * 0: No command complete.
 * 1: Command complete.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STR . CMDC
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STR_CMDC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STR_CMDC     VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STR_CMDC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Normal Interrupt and Error Interrupt Status Enable Register
 *
 * \details
 * This register is a combination of SDMMC_NISTER and SDMMC_EISTER
 * registers.
 * SDMMC_NIEI_STER = {SDMMC_EISTER[15:0], SDMMC_NISTER[15:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_NIEI_STER
 */
#define VTSS_SDMMC_SDMMC_NIEI_STER           VTSS_IOREG(VTSS_TO_SDMMC,0xd)

/**
 * \brief
 * BOOTAE_STA_EN: Boot Acknowledge Error Status Enable (e.MMC specific)
 *
 * \details
 * 0 (MASKED): The BOOTAE status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The BOOTAE status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . BOOTAE_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_BOOTAE_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_BOOTAE_STA_EN  VTSS_BIT(28)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_BOOTAE_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * ADMA_STA_EN: ADMA Error Status Enable
 *
 * \details
 * 0 (MASKED): The ADMA status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The ADMA status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . ADMA_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_ADMA_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_ADMA_STA_EN  VTSS_BIT(25)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_ADMA_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * ACMD_STA_EN: Auto CMD Error Status Enable
 *
 * \details
 * 0 (MASKED): The ADMA status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The ADMA status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . ACMD_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_ACMD_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_ACMD_STA_EN  VTSS_BIT(24)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_ACMD_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CURLIM_STA_EN: Current Limit Error Status Enable
 *
 * \details
 * 0 (MASKED): The CURLIM status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CURLIM status flag in SDMMC_NIEI_STR is enabled..
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CURLIM_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CURLIM_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CURLIM_STA_EN  VTSS_BIT(23)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CURLIM_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * DATEND_STA_EN: Data End Bit Error Status Enable
 *
 * \details
 * 0 (Masked): The DATEND status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The DATEND status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . DATEND_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_DATEND_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_DATEND_STA_EN  VTSS_BIT(22)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_DATEND_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * DATCRC_STA_EN: Data CRC Error Status Enable
 *
 * \details
 * 0 (Masked): The DATCRC status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The DATCRC status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . DATCRC_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_DATCRC_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_DATCRC_STA_EN  VTSS_BIT(21)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_DATCRC_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DATTEO_STA_EN: Data Timeout Error Status Enable
 *
 * \details
 * 0 (Masked): The DATTEO status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The DATTEO status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . DATTEO_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_DATTEO_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_DATTEO_STA_EN  VTSS_BIT(20)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_DATTEO_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * CMDIDXE_STA_EN: Command Index Error Status Enable
 *
 * \details
 * 0 (Masked): The CMDIDXE status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CMDIDXE status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CMDIDXE_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CMDIDXE_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CMDIDXE_STA_EN  VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CMDIDXE_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * CMDEND_STA_EN: Command End Bit Error Status Enable
 *
 * \details
 * 0 (Masked): The CMDEND status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CNDEND status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CMDEND_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CMDEND_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CMDEND_STA_EN  VTSS_BIT(18)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CMDEND_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * CMDCRC_STA_EN: Command CRC Error Status Enable
 *
 * \details
 * 0 (Masked): The CMDCRC status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CNDCRC status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CMDCRC_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CMDCRC_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CMDCRC_STA_EN  VTSS_BIT(17)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CMDCRC_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * CMDTEO_STA_EN: Command Timeout Error Status Enable
 *
 * \details
 * 0 (Masked): The CMDTEO status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CNDTEO status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CMDTEO_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CMDTEO_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CMDTEO_STA_EN  VTSS_BIT(16)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CMDTEO_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * BOOTAR_STA_EN: Boot Acknowledge Received Status Enabled (e.MMC specific)
 *
 * \details
 * 0 (MASKED): The BOOTAR status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The BOOTAR status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . BOOTAR_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_BOOTAR_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_BOOTAR_STA_EN  VTSS_BIT(14)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_BOOTAR_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * INTC_STA_EN: INT_C Status Enable (SD_SDIO specific)If this bit is set to
 * 0, the SDMMC clears interrupt requests to the system. The user may clear
 * this bit before servicing INT_Cand may set this bit again after all
 * interrupt requests to the INT_C pin are cleared to prevent inadvertent
 * interrupts.
 *
 * \details
 * 0 (MASKED): The INTC status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The INTC status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . INTC_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_INTC_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_INTC_STA_EN  VTSS_BIT(11)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_INTC_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * INTB_STA_EN: INT_B Status EnableIf this bit is set to 0, the SDMMC
 * clears interrupt requests to the system. The user may clear this bit
 * before servicing INT_Band may set this bit again after all interrupt
 * requests to the INT_B pin are cleared to prevent inadvertent interrupts.
 *
 * \details
 * 0 (MASKED): The INTB status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The INTB status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . INTB_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_INTB_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_INTB_STA_EN  VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_INTB_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * INTA_STA_EN: INT_A Status Enable (SD_SDIO specific)If this bit is set
 * to 0, the SDMMC clears interrupt requests to the system. The user may
 * clear this bit before servicing INT_Aand may set this bit again after
 * all interrupt requests to the INT_A pin are cleared to prevent
 * inadvertent interrupts.
 *
 * \details
 * 0 (MASKED): The INTA status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The INTA status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . INTA_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_INTA_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_INTA_STA_EN  VTSS_BIT(9)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_INTA_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * CINT_STA_EN: Card Interrupt Status Enable (SD_SDIO specific)If this bit
 * is set to 0, the SDMMC clears interrupt requests to the system. The Card
 * Interrupt detection is stopped when thisbit is cleared and restarted
 * when this bit is set to 1. The user may clear this bit before servicing
 * the Card Interrupt and mayset this bit again after all interrupt
 * requests from the card are cleared to prevent inadvertent interrupts.
 *
 * \details
 * 0 (MASKED): The CINT status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CINT status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CINT_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CINT_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CINT_STA_EN  VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CINT_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * CREM_STA_EN: Card Removal Status Enable (SD_SDIO specific)
 *
 * \details
 * 0 (MASKED): The CREM status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CREM status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CREM_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CREM_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CREM_STA_EN  VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CREM_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * CINS_STA_EN: Card Insertion Status Enable(SD_SDIO specific)
 *
 * \details
 * 0 (MASKED): The CINS status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CINS status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CINS_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CINS_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CINS_STA_EN  VTSS_BIT(6)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CINS_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * BRDRDY_STA_EN: Buffer Read Ready Status Enable
 *
 * \details
 * 0 (MASKED): The BRDRDY status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The BRDRDY status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . BRDRDY_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_BRDRDY_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_BRDRDY_STA_EN  VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_BRDRDY_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * BWRRDY_STA_EN: Buffer Write Ready Status Enable
 *
 * \details
 * 0 (MASKED): The BWRRDY status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The BWRRDY status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . BWRRDY_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_BWRRDY_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_BWRRDY_STA_EN  VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_BWRRDY_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * DMAINT_STA_EN: DMA Interrup Status Enablet
 *
 * \details
 * 0 (MASKED): The DMAINT status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The DMAINT status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . DMAINT_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_DMAINT_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_DMAINT_STA_EN  VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_DMAINT_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * BLKGE_STA_EN: Block Gap Event Status Enable
 *
 * \details
 * 0 (MASKED): The BLKGE status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The BLKGE status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . BLKGE_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_BLKGE_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_BLKGE_STA_EN  VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_BLKGE_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TRFC_STA_EN: Transfer Complete Status Enable
 *
 * \details
 * 0 (MASKED): The TRFC status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The TRFC status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . TRFC_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_TRFC_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_TRFC_STA_EN  VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_TRFC_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CMDC_STA_EN: Command Complete Status Enable
 *
 * \details
 * 0 (MASKED): The CMDC status flag in SDMMC_NIEI_STR is masked.
 * 1 (ENABLED): The CMDC status flag in SDMMC_NIEI_STR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_STER . CMDC_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_STER_CMDC_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_STER_CMDC_STA_EN  VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_NIEI_STER_CMDC_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Normal Interrupt and Error Interrupt Signal Enable Register
 *
 * \details
 * This register is a combination of SDMMC_NISIER and SDMMC_EISIER
 * registers.
 * SDMMC_NIEI_SIGER = {SDMMC_EISIER[15:0], SDMMC_NISIER[15:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_NIEI_SIGER
 */
#define VTSS_SDMMC_SDMMC_NIEI_SIGER          VTSS_IOREG(VTSS_TO_SDMMC,0xe)

/**
 * \brief
 * BOOTAE_SIG_EN: Boot Acknowledge Error Signal Enable (e.MMC specific)
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the BOOTAE status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the BOOTAE status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . BOOTAE_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_BOOTAE_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_BOOTAE_SIG_EN  VTSS_BIT(28)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_BOOTAE_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * ADMA_SIG_EN: ADMA Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the ADMA status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the ADMA status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . ADMA_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_ADMA_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_ADMA_SIG_EN  VTSS_BIT(25)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_ADMA_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * ACMD_SIG_EN: Auto CMD Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the ACMD status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the ACMD status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . ACMD_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_ACMD_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_ACMD_SIG_EN  VTSS_BIT(24)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_ACMD_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CURLIM_SIG_EN: Current Limit Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CURLIM status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CURLIM status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CURLIM_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CURLIM_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CURLIM_SIG_EN  VTSS_BIT(23)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CURLIM_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * DATEND_SIG_EN: Data End Bit Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the DATEND status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the DATEND status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . DATEND_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_DATEND_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_DATEND_SIG_EN  VTSS_BIT(22)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_DATEND_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * DATCRC_SIG_EN: Data CRC Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the DATCRC status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the DATCRC status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . DATCRC_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_DATCRC_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_DATCRC_SIG_EN  VTSS_BIT(21)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_DATCRC_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DATTEO_SIG_EN: Data Timeout Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the DATTEO status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the DATTEO status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . DATTEO_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_DATTEO_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_DATTEO_SIG_EN  VTSS_BIT(20)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_DATTEO_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * CMDIDXE_SIG_EN: Command Index Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CMDIDX status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CMDIDX status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CMDIDXE_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CMDIDXE_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CMDIDXE_SIG_EN  VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CMDIDXE_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * CMDEND_SIG_EN: Command End Bit Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CDMCRC status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CMDCRC status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CMDEND_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CMDEND_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CMDEND_SIG_EN  VTSS_BIT(18)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CMDEND_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * CMDCRC_SIG_EN: Command CRC Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CDMCRC status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CMDCRC status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CMDCRC_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CMDCRC_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CMDCRC_SIG_EN  VTSS_BIT(17)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CMDCRC_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * CMDTEO_SIG_EN: Command Timeout Error Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CMDTEO status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CMDTEO status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CMDTEO_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CMDTEO_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CMDTEO_SIG_EN  VTSS_BIT(16)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CMDTEO_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * BOOTAR_SIG_EN: Boot Acknowledge Received Signal Enabled (e.MMC specific)
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the BOOTAR status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the BOOTAR status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . BOOTAR_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_BOOTAR_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_BOOTAR_SIG_EN  VTSS_BIT(14)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_BOOTAR_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * INTC_SIG_EN: INT_C Signal Enable (SD_SDIO specific)
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the INTC status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the INTC status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . INTC_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_INTC_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_INTC_SIG_EN  VTSS_BIT(11)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_INTC_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * INTB_SIG_EN: INT_B Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the INTB status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the INTB status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . INTB_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_INTB_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_INTB_SIG_EN  VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_INTB_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * INTA_SIG_EN: INT_A Signal Enable (SD_SDIO specific)
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the INTA status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the INTA status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . INTA_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_INTA_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_INTA_SIG_EN  VTSS_BIT(9)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_INTA_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * CINT_SIG_EN: Card Interrupt Signal Enable (SD_SDIO specific)
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CINT status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CINT status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CINT_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CINT_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CINT_SIG_EN  VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CINT_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * CREM_SIG_EN: Card Removal Signal Enable (SD_SDIO specific)
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CREM status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CREM status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CREM_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CREM_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CREM_SIG_EN  VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CREM_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * CINS_SIG_EN: Card Insertion Signal Enable(SD_SDIO specific)
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CINS status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CINS status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CINS_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CINS_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CINS_SIG_EN  VTSS_BIT(6)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CINS_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * BRDRDY_SIG_EN: Buffer Read Ready Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the BRDRDY status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the BRDRDY status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . BRDRDY_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_BRDRDY_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_BRDRDY_SIG_EN  VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_BRDRDY_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * BWRRDY_SIG_EN: Buffer Write Ready Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the BWRRDY status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the BWRRDY status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . BWRRDY_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_BWRRDY_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_BWRRDY_SIG_EN  VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_BWRRDY_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * DMAINT_SIG_EN: DMA Interrup Signal Enablet
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the DMAINT status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the DMAINT status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . DMAINT_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_DMAINT_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_DMAINT_SIG_EN  VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_DMAINT_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * BLKGE_SIG_EN: Block Gap Event Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the BLKGE status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the BLKGE status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . BLKGE_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_BLKGE_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_BLKGE_SIG_EN  VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_BLKGE_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TRFC_SIG_EN: Transfer Complete Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the TRFC status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the TRFC status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . TRFC_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_TRFC_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_TRFC_SIG_EN  VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_TRFC_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CMDC_SIG_EN: Command Complete Signal Enable
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the CMDC status rises in
 * SDMMC_NIEI_STR.
 * 1 (ENABLED): An interrupt is generated when the CMDC status rises in
 * SDMMC_NIEI_STR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_NIEI_SIGER . CMDC_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_NIEI_SIGER_CMDC_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_NIEI_SIGER_CMDC_SIG_EN  VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_NIEI_SIGER_CMDC_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Auto CMD Error Status Register and SDMMC Host Control 2 Register
 *
 * \details
 * This register is a combination of SDMMC_ACESR and SDMMC_HC2R registers.
 * SDMMC_ACESR_HC2R = {SDMMC_HC2R [15:0], SDMMC_ACESR[15:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_ACESR_HC2R
 */
#define VTSS_SDMMC_SDMMC_ACESR_HC2R          VTSS_IOREG(VTSS_TO_SDMMC,0xf)

/**
 * \brief
 * PVALEN: Preset Value EnableAs the operating SDCLK frequency and I/O
 * driver strength depend on the system implementation, it is difficult to
 * determinethese parameters in the standard host driver. When PVALEN is
 * set to 1, automatic SDCLK frequency generation and driverstrength
 * selection are performed without considering system-specific conditions.
 * This bit enables the functions defined inSDMMC_PVR.If this bit is set to
 * 0, SDCLKFSEL, CLKGSEL in SDMMC_CCR and DRVSEL in SDMMC_HC2R are set by
 * the user.If this bit is set to 1, SDCLKFSEL, CLKGSEL in SDMMC_CCR and
 * DRVSEL in SDMMC_HC2R are set by the SDMMC asspecified in SDMMC_PVR.
 *
 * \details
 * 0: SDCLK and Driver strength are controlled by the user.
 * 1: Automatic selection by Preset Value is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . PVALEN
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_PVALEN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_PVALEN  VTSS_BIT(31)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_PVALEN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * ASINTEN: Asynchronous Interrupt EnableThis bit can be set to 1 if a card
 * supports asynchronous interrupts and Asynchronous Interrupt Support
 * (ASINTSUP) is setto 1 in SDMMC_CA0R. Asynchronous interrupt is effective
 * when DAT[1] interrupt is used in 4-bit SD mode (and zero is setto
 * Interrupt Pin Select (INTPSEL) in SDMMC_SBCR). If this bit is set to 1,
 * the user can stop the SDCLK during the asynchronousinterrupt period to
 * save power. During this period, the SDMMC continues to deliver the Card
 * Interrupt to the hostwhen it is asserted by the card.
 *
 * \details
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . ASINTEN
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_ASINTEN(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_ASINTEN  VTSS_BIT(30)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_ASINTEN(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * SCLKSEL: Sampling Clock SelectThe SDMMC uses this bit to select the
 * sampling clock to receive CMD and DAT.This bit is set by the tuning
 * procedure and is valid after completion of tuning (when EXTUN is
 * cleared). Setting 1 meansthat tuning is completed successfully and
 * setting 0 means that tuning has failed.Writing 1 to this bit is
 * meaningless and ignored. A tuning circuit is reset by writing to 0. This
 * bit can be cleared by settingEXTUN to 1. Once the tuning circuit is
 * reset, it takes time to complete the tuning sequence. Therefore, the
 * user shouldkeep this bit to 1 to perform a retuning sequence to complete
 * a retuning sequence in a short time. Changing this bit is notallowed
 * while the SDMMC is receiving a response or a read data block. See Figure
 * 2.29 in the SD Host Controller SimplifiedSpecification V3.00.
 *
 * \details
 * 0: The fixed clock is used to sample data.
 * 1: The tuned clock is used to sample data.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . SCLKSEL
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_SCLKSEL(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_SCLKSEL  VTSS_BIT(23)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_SCLKSEL(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * EXTUN: Execute TuningThis bit is set to 1 to start the tuning procedure
 * and is automatically cleared when the tuning procedure is completed.
 * Theresult of tuning is indicated to Sampling Clock Select (SCLKSEL). The
 * tuning procedure is aborted by writing 0. See Figure2.29 in the SD Host
 * Controller Simplified Specification V3.00.
 *
 * \details
 * 0: Not tuned or tuning completed.
 * 1: Execute tuning.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . EXTUN
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_EXTUN(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_EXTUN  VTSS_BIT(22)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_EXTUN(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * DRVSEL: Driver Strength SelectThe SDMMC output driver in 1.8V signaling
 * is selected by this bit. In 3.3V signaling, this field is not effective.
 * This field canbe set according to the Driver Type A, C and D support
 * bits in SDMMC_CA1R.This field depends on the setting of Preset Value
 * Enable (PVALEN):- PVALEN = 0: This field is set by the user.- PVALEN =
 * 1: This field is automatically set by a value specified in one of the
 * SDMMC_PVRx.
 *
 * \details
 * 0 = Driver Type B is selected (Default)
 * 1 = Driver Type A is selected
 * 2 = Driver Type C is selected
 * 3 = Driver Type D is selected
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . DRVSEL
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_DRVSEL(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_DRVSEL     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_DRVSEL(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * VS18EN: 1.8V Signaling EnableThis bit controls the SDMMC_1V8SEL output,
 * which in turn may control an external voltage regulator for the I/O cell
 * andcard I/Os. 3.3V or some other fixed voltage is supplied to the
 * card/device regardless of the signaling voltage.Setting this bit from 0
 * to 1 starts changing the signal voltage from 3.3V to 1.8V. The 1.8V
 * regulator output must be stablewithin 5 ms.The SDMMC clears this bit if
 * switching to 1.8V signaling fails.Clearing this bit from 1 to 0 starts
 * changing the signal voltage from 1.8V to 3.3V. The 3.3V regulator output
 * must be stablewithin 5 ms.The user can set this bit to 1 when the SDMMC
 * supports 1.8V signaling (one of the support bits is set to 1:
 * SDR50SUP,SDR104SUP or DDR50SUP in SDMMC_CA1R) and the card or device
 * supports UHS-I (S18A = 1. See "Bus Switch VoltageSwitch Sequence" in the
 * Physical Layer Simplified Specification V3.01).
 *
 * \details
 * 0: 3.3V signaling.
 * 1: 1.8V signaling.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . VS18EN
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_VS18EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_VS18EN  VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_VS18EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * UHSMS: UHS Mode SelectThis field is used to select one of the UHS-I
 * modes and is effective when 1.8V Signal Enable (VS18EN) is set to 1.If
 * Preset Value Enable is set to 1, the SDMMC sets SDCLK Frequency Select
 * (SDCLKFSEL), Clock Generator Select(CLKGSEL) in SDMMC_CCR and Driver
 * Strength Select (DRVSEL) according to SDMMC_PVR. In this case, one of
 * thepreset value registers is selected by this field. The user needs to
 * reset SD Clock Enable (SDCLKEN) before changing thisfield to avoid
 * generating a clock glitch. After setting this field, the user sets
 * SDCLKEN to 1 again.
 *
 * \details
 * 0 = UHS SDR12 Mode
 * 1 = UHS SDR25 Mode
 * 2 = UHS SDR50 Mode
 * 3 = UHS SDR104 Mode
 * 4 = UHS DDR50 Mode
 *
 * Note: This field is effective only if SDMMC_MCR_DEBR.DDR is set to 0.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . UHSMS
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_UHSMS(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_UHSMS     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_UHSMS(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * CMDNI: Command Not Issued by Auto CMD12 ErrorThis bit is set to 1 when
 * CMD_wo_DAT is not executed due to an Auto CMD12 error
 * (SDMMC_ACESR[4:1]). This bit is setto 0 when Auto CMD Error is generated
 * by Auto CMD23.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . CMDNI
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_CMDNI(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_CMDNI  VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_CMDNI(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This bit is set to 1 when the Command Index error occurs in response to
 * a command.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . ACMDIDX
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_ACMDIDX(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_ACMDIDX  VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_ACMDIDX(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * ACMDEND: Auto CMD End Bit ErrorThis bit is set to 1 when detecting that
 * the end bit of the command response is 0.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . ACMDEND
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_ACMDEND(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_ACMDEND  VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_ACMDEND(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * ACMDCRC: Auto CMD CRC ErrorThis bit is set to 1 when detecting a CRC
 * error in the command response (see Table 15-5 for more details).
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . ACMDCRC
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_ACMDCRC(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_ACMDCRC  VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_ACMDCRC(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * ACMDTEO: Auto CMD Timeout ErrorThis bit is set to 1 if no response is
 * returned within 64 SDCLK cycles from the end bit of the command. If this
 * bit is set to 1,the other error status bits (SDMMC_ACESR[4:2]) are
 * meaningless.Relations between ACMDCRC and ACMDTEOACMDCRC = 0; ACMDTEO =
 * 0; Types of error = No errorACMDCRC = 0; ACMDTEO = 1; Types of error =
 * Response Timeout errorACMDCRC = 1; ACMDTEO = 0; Types of error =
 * Response CRC errorACMDCRC = 1; ACMDTEO = 1; Types of error = CMD line
 * conflict
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . ACMDTEO
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_ACMDTEO(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_ACMDTEO  VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_ACMDTEO(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * ACMD12NE: Auto CMD12 Not ExecutedIf a memory multiple block data
 * transfer is not started due to a command error, this bit is not set to 1
 * because it is not necessaryto issue Auto CMD12. Setting this bit to 1
 * means the SDMMC cannot issue Auto CMD12 to stop a memory multipleblock
 * data transfer due to some error. If this bit is set to 1, other error
 * status bits (SDMMC_ACESR[4:1]) are meaningless.This bit is set to 0 when
 * an Auto CMD error is generated by Auto CMD23.
 *
 * \details
 * 0: No error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACESR_HC2R . ACMD12NE
 */
#define  VTSS_F_SDMMC_SDMMC_ACESR_HC2R_ACMD12NE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_ACESR_HC2R_ACMD12NE  VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_ACESR_HC2R_ACMD12NE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Capabilities 0 Register
 *
 * \details
 * Note: The Capabilities 0 Register is not supposed to be written by the
 * user. However, the user can modify preset values only if Capabilities
 * Write Enable (CAPWREN) is set to 1 in SDMMC_CACR.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_CA0R
 */
#define VTSS_SDMMC_SDMMC_CA0R                VTSS_IOREG(VTSS_TO_SDMMC,0x10)

/**
 * \brief
 * SLTYPE: Slot TypeThis field indicates usage of a slot by a specific
 * system. An SDMMC control register set is defined per slot.Embedded Slot
 * for One Device means that only one nonremovable device is connected to a
 * bus slot.The Standard Host Driver controls only a removable card (SLTYPE
 * = 0) or one embedded device (SLTYPE = 1) connectedto an SD bus slot. If
 * a slot is configured for a shared bus (SLTYPE = 2), the Standard Host
 * Driver does not control embeddeddevices connected to a shared bus.
 * Shared bus slot is controlled by a specific host driver developed by a
 * host system.
 *
 * \details
 * 0 = Removable Card Slot
 * 1 = Embedded Slot for One Device
 * 2 = Shared Bus Slot
 * 3 = Reserved
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . SLTYPE
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_SLTYPE(x)    VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_SDMMC_SDMMC_CA0R_SLTYPE       VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_SDMMC_SDMMC_CA0R_SLTYPE(x)    VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * ASINTSUP: Asynchronous Interrupt SupportSee section "Asynchronous
 * Interrupt" in the SDIO Simplified Specification V3.00.
 *
 * \details
 * 0: Asynchronous interrupt not supported.
 * 1: Asynchronous interrupt supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . ASINTSUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_ASINTSUP(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_ASINTSUP     VTSS_BIT(29)
#define  VTSS_X_SDMMC_SDMMC_CA0R_ASINTSUP(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * SB64SUP: 64-Bit System Bus SupportReading this bit to 1 means that the
 * SDMMC supports the 64-bit Address Descriptor mode and is connected to
 * the 64-bitaddress system bus.
 *
 * \details
 * 0: 64-bit address bus not supported.
 * 1: 64-bit address bus supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . SB64SUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_SB64SUP(x)   VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_SB64SUP      VTSS_BIT(28)
#define  VTSS_X_SDMMC_SDMMC_CA0R_SB64SUP(x)   VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * V18VSUP: Voltage Support 1.8V
 *
 * \details
 * 0: 1.8V Voltage supply not supported.
 * 1: 1.8V Voltage supply supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . V18VSUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_V18VSUP(x)   VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_V18VSUP      VTSS_BIT(26)
#define  VTSS_X_SDMMC_SDMMC_CA0R_V18VSUP(x)   VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * V30VSUP: Voltage Support 3.0V
 *
 * \details
 * 0: 3.0V Voltage supply not supported.
 * 1: 3.0V Voltage supply supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . V30VSUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_V30VSUP(x)   VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_V30VSUP      VTSS_BIT(25)
#define  VTSS_X_SDMMC_SDMMC_CA0R_V30VSUP(x)   VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * V33VSUP: Voltage Support 3.3V
 *
 * \details
 * 0: 3.3V Voltage supply not supported.
 * 1: 3.3V Voltage supply supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . V33VSUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_V33VSUP(x)   VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_V33VSUP      VTSS_BIT(24)
#define  VTSS_X_SDMMC_SDMMC_CA0R_V33VSUP(x)   VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * SRSUP: Suspend/Resume SupportThis bit indicates whether the SDMMC
 * supports the Suspend/Resume functionality. If this bit is set to 0, the
 * user does notissue either Suspend or Resume commands because the Suspend
 * and Resume mechanism (see "Suspend and ResumeMechanism" in the SD Host
 * Controller Simplified Specification V3.00) is not supported.
 *
 * \details
 * 0: Suspend/Resume not supported.
 * 1: Suspend/Resume supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . SRSUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_SRSUP(x)     VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_SRSUP        VTSS_BIT(23)
#define  VTSS_X_SDMMC_SDMMC_CA0R_SRSUP(x)     VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * SDMASUP: SDMA SupportThis bit indicates whether the SDMMC is capable of
 * using SDMA to transfer data between system memory and theSDMMC directly.
 *
 * \details
 * 0: SDMA not supported.
 * 1: SDMA supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . SDMASUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_SDMASUP(x)   VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_SDMASUP      VTSS_BIT(22)
#define  VTSS_X_SDMMC_SDMMC_CA0R_SDMASUP(x)   VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * This bit indicates whether the SDMMC and the system support High Speed
 * mode and they can supply SDCLK frequencyfrom 25 MHz to 50 MHz.
 *
 * \details
 * 0: High Speed not supported.
 * 1: High Speed supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . HSSUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_HSSUP(x)     VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_HSSUP        VTSS_BIT(21)
#define  VTSS_X_SDMMC_SDMMC_CA0R_HSSUP(x)     VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * ADMA2SUP: ADMA2 SupportThis bit indicates whether the SDMMC is capable
 * of using ADMA2.
 *
 * \details
 * 0: ADMA2 not supported.
 * 1: ADMA2 supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . ADMA2SUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_ADMA2SUP(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_ADMA2SUP     VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_CA0R_ADMA2SUP(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * ED8SUP: 8-Bit Support for Embedded DeviceThis bit indicates whether the
 * SDMMC is capable of using the 8-bit Bus Width mode. This bit is not
 * effective when SlotType (SLTYPE) is set to 2. In this case, see Bus
 * Width Preset (BWTPRE) in SDMMC_SBCR.
 *
 * \details
 * 0: 8-bit bus width not supported.
 * 1: 8-bit bus width supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . ED8SUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_ED8SUP(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_ED8SUP       VTSS_BIT(18)
#define  VTSS_X_SDMMC_SDMMC_CA0R_ED8SUP(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * This field indicates the maximum block size that the user can read and
 * write to the buffer in the SDMMC. Three sizes canbe defined, as shown
 * below. It is noted that the transfer block length is always 512 bytes
 * for SD Memory Cards regardlessof this field.
 *
 * \details
 * 0 = 512 bytes
 * 1 = 1024 bytes
 * 2 = 2048 bytes
 * 3 = Reserved
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . MAXBLKL
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_MAXBLKL(x)   VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SDMMC_SDMMC_CA0R_MAXBLKL      VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SDMMC_SDMMC_CA0R_MAXBLKL(x)   VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * BASECLKF: Base Clock FrequencyThis value indicates the frequency of the
 * base clock (BASECLK). The user uses this value to calculate the clock
 * dividervalue (see SDCLK Frequency Select (SDCLKFSEL) in SDMMC_CCR).If
 * this field is set to 0, the user must get the information via another
 * method.fBASECLK = BASECLKF MHz
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . BASECLKF
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_BASECLKF(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SDMMC_SDMMC_CA0R_BASECLKF     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SDMMC_SDMMC_CA0R_BASECLKF(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TEOCLKU: Timeout Clock UnitThis bit shows the unit of the base clock
 * frequency used to detect Data Timeout Error.
 *
 * \details
 * 0: KHz
 * 1: MHz
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . TEOCLKU
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_TEOCLKU(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_CA0R_TEOCLKU      VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_CA0R_TEOCLKU(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TEOCLKF: Timeout Clock FrequencyThis bit shows the timeout clock
 * frequency (TEOCLK) used to detect Data Timeout Error.If this field is
 * set to 0, the user must get the information via another method.The
 * Timeout Clock Unit (TEOCLKU) defines the unit of this field's value.-
 * TEOCLKU = 0: fTEOCLK = TEOCLKF KHz- TEOCLKU = 1: fTEOCLK = TEOCLKF MHz
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CA0R . TEOCLKF
 */
#define  VTSS_F_SDMMC_SDMMC_CA0R_TEOCLKF(x)   VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDMMC_SDMMC_CA0R_TEOCLKF      VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDMMC_SDMMC_CA0R_TEOCLKF(x)   VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief SDMMC Capabilities 1 Register
 *
 * \details
 * Note: The Capabilities 1 Register is not supposed to be written by the
 * user. However, the user can modify preset values only if Capabilities
 * Write Enable (CAPWREN) is set to 1 in SDMMC_CACR.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_CA1R
 */
#define VTSS_SDMMC_SDMMC_CA1R                VTSS_IOREG(VTSS_TO_SDMMC,0x11)

/**
 * \brief
 * CLKMULT: Clock MultiplierThis field indicates the multiplier factor
 * between the Base Clock (BASECLK) used for the Divided Clock Mode and the
 * MultipliedClock (MULTCLK) used for the Programmable Clock mode (see
 * SDMMC_CCR).Reading this field to 0 means that the Programmable Clock
 * mode is not supported.fMULTCLK = fBASECLK x (CLKMULT + 1)
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . CLKMULT
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_CLKMULT(x)   VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SDMMC_SDMMC_CA1R_CLKMULT      VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SDMMC_SDMMC_CA1R_CLKMULT(x)   VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RTMOD: Retuning ModesThis field selects the retuning method and limits
 * the maximum data length.There are two retuning timings: Retuning Request
 * (RTREQ) controlled by the SDMMC, and expiration of a Retuning
 * timercontrolled by the user. By receiving either timing, the user
 * executes the retuning procedure just before a next commandissue.The
 * maximum data length per read/write command is restricted so that
 * retuning procedures can be inserted during datatransfers.Retuning Mode
 * 1:The SDMMC does not have any internal logic to detect when retuning
 * needs to be performed. In this case, the usershould maintain all
 * retuning timings by using the Retuning Timer. To enable inserting the
 * retuning procedure duringdata transfers, the data length per Read/Write
 * command must be limited to 4 Mbytes.Retuning Mode 2:The SDMMC has the
 * capability to indicate the retuning timing by Retuning Request (RTREQ)
 * during data transfers.Then the data length per Read/Write command must
 * be limited to 4 Mbytes.During nondata transfer, retuning timing is
 * determined by either Retuning Request or Retuning Timer. If
 * RetuningRequest is used, Retuning Timer should be disabled.Retuning Mode
 * 3:The SDMMC has the capability to take care of the retuning during data
 * transfer (Auto Retuning). Retuning Request isnot generated during data
 * transfers and there is no limitation to data length per Read/Write
 * command.During nondata transfer, retuning timing is determined either by
 * Retuning Request or Retuning Timer. If RetuningRequest is used, Retuning
 * Timer should be disabled.
 *
 * \details
 * 0 (MODE1) = TImer, 4 MB (Max) Data Length
 * 1 (MODE2) = Timer and Retuning Request, 4 MB (Max) Data Length
 * 2 (MODE3) = Auto Retuning (for transfer) Timer and Retuning Request, Any
 * Data Length
 * 0 (MODE1) = Reseved
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . RTMOD
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_RTMOD(x)     VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SDMMC_SDMMC_CA1R_RTMOD        VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SDMMC_SDMMC_CA1R_RTMOD(x)     VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * TSDR50: Use Tuning for SDR50If this bit is set to 1, the SDMMC requires
 * tuning to operate SDR50 (tuning is always required to operate SDR104).
 *
 * \details
 * 0: SDR50 does not require tuning.
 * 1: SDR50 requires tuning.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . TSDR50
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_TSDR50(x)    VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_SDMMC_SDMMC_CA1R_TSDR50       VTSS_BIT(13)
#define  VTSS_X_SDMMC_SDMMC_CA1R_TSDR50(x)    VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Timer Count For RetuningThis field indicates an initial value of the
 * Retuning Timer for Retuning Mode (RTMOD) 1 to 3. Reading this field at 0
 * meansthat the Retuning Timer is disabled. The Retuning Timer initial
 * value ranges from 0 to 1024 seconds.tTIMER = 2(TCNTRT - 1) Seconds
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . TCNTRT
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_TCNTRT(x)    VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_SDMMC_SDMMC_CA1R_TCNTRT       VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_SDMMC_SDMMC_CA1R_TCNTRT(x)    VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * DRVDSUP: Driver Type D Support
 *
 * \details
 * 0: Driver type D is not supported.
 * 1: Driver type D is supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . DRVDSUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_DRVDSUP(x)   VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDMMC_SDMMC_CA1R_DRVDSUP      VTSS_BIT(6)
#define  VTSS_X_SDMMC_SDMMC_CA1R_DRVDSUP(x)   VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * DRVCSUP: Driver Type C Support
 *
 * \details
 * 0: Driver type C is not supported.
 * 1: Driver type C is supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . DRVCSUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_DRVCSUP(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_CA1R_DRVCSUP      VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_CA1R_DRVCSUP(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DRVASUP: Driver Type A Support
 *
 * \details
 * 0: Driver type A is not supported.
 * 1: Driver type A is supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . DRVASUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_DRVASUP(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_CA1R_DRVASUP      VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_CA1R_DRVASUP(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * DDR50SUP: DDR50 Support
 *
 * \details
 * 0: DDR50 mode is not supported.
 * 1: DDR50 mode is supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . DDR50SUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_DDR50SUP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_CA1R_DDR50SUP     VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_CA1R_DDR50SUP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * SDR104SUP: SDR104 Support
 *
 * \details
 * 0: SDR104 mode is not supported.
 * 1: SDR104 mode is supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . SDR104SUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_SDR104SUP(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_CA1R_SDR104SUP    VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_CA1R_SDR104SUP(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * SDR50SUP: SDR50 Support
 *
 * \details
 * 0: SDR50 mode is not supported.
 * 1: SDR50 mode is supported.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CA1R . SDR50SUP
 */
#define  VTSS_F_SDMMC_SDMMC_CA1R_SDR50SUP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_CA1R_SDR50SUP     VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_CA1R_SDR50SUP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Maximum Current Capabilities Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_MCCAR
 */
#define VTSS_SDMMC_SDMMC_MCCAR               VTSS_IOREG(VTSS_TO_SDMMC,0x12)

/**
 * \brief
 * MAXCUR18V: Maximum Current for 1.8VThis field indicates the maximum
 * current capability for 1.8V voltage. This value is meaningful only if
 * V18VSUP is set to 1 inSDMMC_CA0R. Reading MAXCUR18V at 0 means that the
 * user must get information via another method.Imax mA = 4 x MAXCURR18V
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_MCCAR . MAXCUR18V
 */
#define  VTSS_F_SDMMC_SDMMC_MCCAR_MAXCUR18V(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SDMMC_SDMMC_MCCAR_MAXCUR18V     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SDMMC_SDMMC_MCCAR_MAXCUR18V(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * MAXCUR30V: Maximum Current for 3.0VThis field indicates the maximum
 * current capability for 3.0V voltage. This value is meaningful only if
 * V30VSUP is set to 1 inSDMMC_CA0R. Reading MAXCUR30V at 0 means that the
 * user must get information via another method.Imax mA = 4 x MAXCURR30V
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_MCCAR . MAXCUR30V
 */
#define  VTSS_F_SDMMC_SDMMC_MCCAR_MAXCUR30V(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SDMMC_SDMMC_MCCAR_MAXCUR30V     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SDMMC_SDMMC_MCCAR_MAXCUR30V(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * MAXCUR33V: Maximum Current for 3.3VThis field indicates the maximum
 * current capability for 3.3V voltage. This value is meaningful only if
 * V33VSUP is set to 1 inSDMMC_CA0R. Reading MAXCUR33V at 0 means that the
 * user must get information via another method.Imax mA = 4 x MAXCURR33V
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_MCCAR . MAXCUR33V
 */
#define  VTSS_F_SDMMC_SDMMC_MCCAR_MAXCUR33V(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDMMC_SDMMC_MCCAR_MAXCUR33V     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDMMC_SDMMC_MCCAR_MAXCUR33V(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief SDMMC Force Event Register for Auto CMD Error Status
 *
 * \details
 * This register is a combination of SDMMC_FERACES and SDMMC_FEREIS
 * registers.
 * SDMMC_FCES_FEIS = {SDMMC_FEREIS[15:0], SDMMC_FERACES[15:0]}
 *
 * Note: This register has write-only access.

 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_FCES_FEIS
 */
#define VTSS_SDMMC_SDMMC_FCES_FEIS           VTSS_IOREG(VTSS_TO_SDMMC,0x14)

/**
 * \brief
 * FE_BOOTAE: Force Event for Boot Acknowledge ErrorFor test purposes, the
 * user can write this bit to 1 to raise the BOOTAE status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_BOOTAE
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_BOOTAE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_BOOTAE  VTSS_BIT(28)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_BOOTAE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * FE_ADMA: Force Event for ADMA ErrorFor test purposes, the user can write
 * this bit to 1 to raise the ADMA status flag in SDMMC_EISTR.Writing this
 * bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_ADMA
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_ADMA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_ADMA  VTSS_BIT(25)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_ADMA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * FE_ACMD: Force Event for Auto CMD ErrorFor test purposes, the user can
 * write this bit to 1 to raise the ACMD status flag in SDMMC_EISTR.Writing
 * this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_ACMD
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_ACMD(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_ACMD  VTSS_BIT(24)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_ACMD(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * FE_CURLIM: Force Event for Current Limit ErrorFor test purposes, the
 * user can write this bit to 1 to raise the CURLIM status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_CURLIM
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_CURLIM(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_CURLIM  VTSS_BIT(23)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_CURLIM(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * FE_DATEND: Force Event for Data End Bit ErrorFor test purposes, the user
 * can write this bit to 1 to raise the DATEND status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_DATEND
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_DATEND(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_DATEND  VTSS_BIT(22)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_DATEND(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * FE_DATCRC: Force Event for Data CRC errorFor test purposes, the user can
 * write this bit to 1 to raise the DATCRC status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_DATCRC
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_DATCRC(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_DATCRC  VTSS_BIT(21)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_DATCRC(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * FE_DATTEO: Force Event for Data Timeout errorFor test purposes, the user
 * can write this bit to 1 to raise the DATTEO status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_DATTEO
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_DATTEO(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_DATTEO  VTSS_BIT(20)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_DATTEO(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * FE_CMDIDX: Force Event for Command Index ErrorFor test purposes, the
 * user can write this bit to 1 to raise the CMDIDX status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_CMDIDX
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_CMDIDX(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_CMDIDX  VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_CMDIDX(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * FE_CMDEND: Force Event for Command End Bit ErrorFor test purposes, the
 * user can write this bit to 1 to raise the CDMEND status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_CMDEND
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_CMDEND(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_CMDEND  VTSS_BIT(18)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_CMDEND(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * FE_CMDCRC: Force Event for Command CRC ErrorFor test purposes, the user
 * can write this bit to 1 to raise the CMDCRC status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_CMDCRC
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_CMDCRC(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_CMDCRC  VTSS_BIT(17)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_CMDCRC(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * FE_CMDTEO: Force Event for Command Timeout ErrorFor test purposes, the
 * user can write this bit to 1 to raise the CMDTEO status flag in
 * SDMMC_EISTR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_CMDTEO
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_CMDTEO(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_CMDTEO  VTSS_BIT(16)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_CMDTEO(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * FE_CMDNI: Force Event for Command Not Issued by Auto CMD12 ErrorFor test
 * purposes, the user can write this bit to 1 to raise the CMDNI status
 * flag in SDMMC_ACESR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_CMDNI
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_CMDNI(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_CMDNI  VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_CMDNI(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * FE_ACMDIDX: Force Event for Auto CMD Index ErrorFor test purposes, the
 * user can write this bit to 1 to raise the ACMDIDX status flag in
 * SDMMC_ACESR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_ACMDIDX
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_ACMDIDX(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_ACMDIDX  VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_ACMDIDX(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FE_ACMDEND: Force Event for Auto CMD End Bit ErrorFor test purposes, the
 * user can write this bit to 1 to raise the ACMDEND status flag in
 * SDMMC_ACESR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_ACMDEND
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_ACMDEND(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_ACMDEND  VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_ACMDEND(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * FE_ACMDCRC: Force Event for Auto CMD CRC ErrorFor test purposes, the
 * user can write this bit to 1 to raise the ACMDCRC status flag in
 * SDMMC_ACESR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_ACMDCRC
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_ACMDCRC(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_ACMDCRC  VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_ACMDCRC(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * FE_ACMDTEO: Force Event for Auto CMD Timeout ErrorFor test purposes, the
 * user can write this bit to 1 to raise the ACMDTEO status flag in
 * SDMMC_ACESR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_ACMDTEO
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_ACMDTEO(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_ACMDTEO  VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_ACMDTEO(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * FE_ACMD12NE: Force Event for Auto CMD12 Not ExecutedFor test purposes,
 * the user can write this bit to 1 to raise the ACMD12NE status flag in
 * SDMMC_ACESR.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_FCES_FEIS . FE_ACMD12NE
 */
#define  VTSS_F_SDMMC_SDMMC_FCES_FEIS_FE_ACMD12NE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_FCES_FEIS_FE_ACMD12NE  VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_FCES_FEIS_FE_ACMD12NE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC ADMA Error Status Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_AESR
 */
#define VTSS_SDMMC_SDMMC_AESR                VTSS_IOREG(VTSS_TO_SDMMC,0x15)

/**
 * \brief
 * LMIS: ADMA Length Mismatch ErrorThis error occurs in the following two
 * cases:- While Block Count Enable (BCEN) is being set, the total data
 * length specified by the Descriptor table is differentfrom that specified
 * by the Block Count (BLKCNT) and Transfer Block Size (BLKSIZE).- The
 * total data length cannot be divided by the Transfer Block Size
 * (BLKSIZE).
 *
 * \details
 * 0: No Error.
 * 1: Error.
 *
 * Field: ::VTSS_SDMMC_SDMMC_AESR . LMIS
 */
#define  VTSS_F_SDMMC_SDMMC_AESR_LMIS(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_AESR_LMIS         VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_AESR_LMIS(x)      VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * ERRST: ADMA Error StateThis field indicates the state of ADMA when an
 * error has occurred during an ADMA data transfer. This field never reads
 * 2because ADMA never stops in this state.
 *
 * \details
 * Value = 0; ADMA Error State =  ST_STOP (Stop DMA); SDMMC_ASARx Registers
 * = Points to the descriptor following the error descriptor
 * Value = 1; ADMA Error State =  ST_FDS (Fetch Descriptor); SDMMC_ASARx
 * Registers = Points to the error descriptor
 * Value = 2; ADMA Error State =  Not Used; SDMMC_ASARx Registers = Not
 * Used
 * Value = 3; ADMA Error State =  ST_TRF (Transfer Data); SDMMC_ASARx
 * Registers = Points to the descriptor following the error descriptor
 *
 * Field: ::VTSS_SDMMC_SDMMC_AESR . ERRST
 */
#define  VTSS_F_SDMMC_SDMMC_AESR_ERRST(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDMMC_SDMMC_AESR_ERRST        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDMMC_SDMMC_AESR_ERRST(x)     VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief SDMMC ADMA System Address Register 0
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_ASAR0
 */
#define VTSS_SDMMC_SDMMC_ASAR0               VTSS_IOREG(VTSS_TO_SDMMC,0x16)

/**
 * \brief
 * ADMASA0: ADMA System Address 0This field holds the byte address of the
 * executing command of the descriptor table. The 32-bit address descriptor
 * usesSDMMC_ASAR0 and the 64-bit address descriptor uses both SDMMC_ASAR0
 * (lower 32 bits) and SDMMC_ASAR1(higher 32 bits). At the start of ADMA,
 * the user must set the start address of the descriptor table. The ADMA
 * increments thisregister address, which points to the next Descriptor
 * line to be fetched.When the ADMA Error (ADMA) status flag rises, this
 * field holds a valid descriptor address depending on the ADMA ErrorState
 * (ERRST). The user must program Descriptor Table on 32-bit boundary and
 * set 32-bit boundary address to this register.ADMA2 ignores the lower 2
 * bits of this register and assumes it to be 0.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_ASAR0 . ADMASA0
 */
#define  VTSS_F_SDMMC_SDMMC_ASAR0_ADMASA0(x)  (x)
#define  VTSS_M_SDMMC_SDMMC_ASAR0_ADMASA0     0xffffffff
#define  VTSS_X_SDMMC_SDMMC_ASAR0_ADMASA0(x)  (x)


/**
 * \brief SDMMC ADMA System Address Register 1
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_ASAR1
 */
#define VTSS_SDMMC_SDMMC_ASAR1               VTSS_IOREG(VTSS_TO_SDMMC,0x17)

/**
 * \brief
 * ADMASA1: ADMA System Address 1This field holds the byte address of the
 * executing command of the descriptor table. The 32-bit address descriptor
 * usesSDMMC_ASAR0 and the 64-bit address descriptor uses both SDMMC_ASAR0
 * (lower 32 bits) and SDMMC_ASAR1(higher 32 bits). At the start of ADMA,
 * the user must set the start address of the descriptor table. The ADMA
 * increments thisregister address, which points to the next Descriptor
 * line to be fetched.When the ADMA Error (ADMA) status flag rises, this
 * field holds a valid descriptor address depending on the ADMA ErrorState
 * (ERRST). The user must program Descriptor Table on 32-bit boundary and
 * set 32-bit boundary address to this register.ADMA2 ignores the lower 2
 * bits of this register and assumes it to be 0.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_ASAR1 . ADMASA1
 */
#define  VTSS_F_SDMMC_SDMMC_ASAR1_ADMASA1(x)  (x)
#define  VTSS_M_SDMMC_SDMMC_ASAR1_ADMASA1     0xffffffff
#define  VTSS_X_SDMMC_SDMMC_ASAR1_ADMASA1(x)  (x)


/**
 * \brief SDMMC Preset Value Register (for initialization)
 *
 * \details
 * One of the Preset Value Registers is effective based on the selected bus
 * speed mode. Below Table defines the conditions to select one of the
 * SDMMC_PVRs.
 *
 * Selected Bus Speed Mode = Default Speed; VS18EN (SDMMC_HC2R) = 0; HSEN
 * (SDMMC_HC1R) = 0; UHSMS (SDMMC_HC2R) = Don't care;
 * Selected Bus Speed Mode = High Speed; VS18EN (SDMMC_HC2R) = 0; HSEN
 * (SDMMC_HC1R) = 1; UHSMS (SDMMC_HC2R) = Don't care;
 * Selected Bus Speed Mode = SDR12; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 0;
 * Selected Bus Speed Mode = SDR25; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 1;
 * Selected Bus Speed Mode = SDR50; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 2;
 * Selected Bus Speed Mode = SDR104/HS200; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 3;
 * Selected Bus Speed Mode = DDR50; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 4;
 * Selected Bus Speed Mode = Reserved; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = Other values;
 *
 * Preset Value Register Select Condition:
 * Default Speed Mode = SDMMC_HC1R.HSEN = 0.
 * High Speed Mode = SDMMC_HC1R.HSEN = 1.
 *
 * Below Table shows the effective Preset Value Register according to the
 * Selected Bus Speed mode.
 *
 * SDMMC_PVRx = SDMMC_PVR0; Selected Bus Speed Mode = Intilization; Signal
 * Voltage = 3.3V or 1.8V
 * SDMMC_PVRx = SDMMC_PVR1; Selected Bus Speed Mode = Default Speed; Signal
 * Voltage = 3.3V
 * SDMMC_PVRx = SDMMC_PVR2; Selected Bus Speed Mode = High Speed; Signal
 * Voltage = 3.3V
 * SDMMC_PVRx = SDMMC_PVR3; Selected Bus Speed Mode = SDR12; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR4; Selected Bus Speed Mode = SDR25; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR5; Selected Bus Speed Mode = SDR50; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR6; Selected Bus Speed Mode = SDR104/HS200; Signal
 * Voltage = 1.8V
 * SDMMC_PVRx = SDMMC_PVR7; Selected Bus Speed Mode = DDR50; Signal Voltage
 * = 1.8V
 *
 * When Preset Value Enable (PVALEN) in SDMMC_HC2R is set to 1, SDCLK
 * Frequency Select (SDLCKFSEL) and Clock
 * Generator Select (CLKGSEL) in SDMMC_CCR, and Driver Strength Select
 * (DRVSEL) in SDMMC_HC2R are automatically
 * set based on the Selected Bus Speed mode. This means that the user does
 * not need to set these fields when preset
 * is enabled. A Preset Value Register for Initialization (SDMMC_PVR0) is
 * not selected by Bus Speed mode. Before starting
 * the initialization sequence, the user needs to set a clock preset value
 * to SDCLKFSEL in SDMMC_CCR. PVALEN can be
 * set to 1 after the initialization is completed.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_PVR01
 */
#define VTSS_SDMMC_SDMMC_PVR01               VTSS_IOREG(VTSS_TO_SDMMC,0x18)

/**
 * \brief
 * DRVSEL1: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR01 . DRVSEL1
 */
#define  VTSS_F_SDMMC_SDMMC_PVR01_DRVSEL1(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_SDMMC_SDMMC_PVR01_DRVSEL1     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_SDMMC_SDMMC_PVR01_DRVSEL1(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * CLKGSEL1: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR01 . CLKGSEL1
 */
#define  VTSS_F_SDMMC_SDMMC_PVR01_CLKGSEL1(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SDMMC_SDMMC_PVR01_CLKGSEL1    VTSS_BIT(26)
#define  VTSS_X_SDMMC_SDMMC_PVR01_CLKGSEL1(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * SDCLKFSEL1: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR01 . SDCLKFSEL1
 */
#define  VTSS_F_SDMMC_SDMMC_PVR01_SDCLKFSEL1(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SDMMC_SDMMC_PVR01_SDCLKFSEL1     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SDMMC_SDMMC_PVR01_SDCLKFSEL1(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/**
 * \brief
 * DRVSEL0: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR01 . DRVSEL0
 */
#define  VTSS_F_SDMMC_SDMMC_PVR01_DRVSEL0(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SDMMC_SDMMC_PVR01_DRVSEL0     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SDMMC_SDMMC_PVR01_DRVSEL0(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * CLKGSEL0: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR01 . CLKGSEL0
 */
#define  VTSS_F_SDMMC_SDMMC_PVR01_CLKGSEL0(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_PVR01_CLKGSEL0    VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_PVR01_CLKGSEL0(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * SDCLKFSEL0: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR01 . SDCLKFSEL0
 */
#define  VTSS_F_SDMMC_SDMMC_PVR01_SDCLKFSEL0(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SDMMC_SDMMC_PVR01_SDCLKFSEL0     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SDMMC_SDMMC_PVR01_SDCLKFSEL0(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief SDMMC Preset Value Register (for initialization)
 *
 * \details
 * One of the Preset Value Registers is effective based on the selected bus
 * speed mode. Below Table defines the conditions to select one of the
 * SDMMC_PVRs.
 *
 * Selected Bus Speed Mode = Default Speed; VS18EN (SDMMC_HC2R) = 0; HSEN
 * (SDMMC_HC1R) = 0; UHSMS (SDMMC_HC2R) = Don't care;
 * Selected Bus Speed Mode = High Speed; VS18EN (SDMMC_HC2R) = 0; HSEN
 * (SDMMC_HC1R) = 1; UHSMS (SDMMC_HC2R) = Don't care;
 * Selected Bus Speed Mode = SDR12; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 0;
 * Selected Bus Speed Mode = SDR25; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 1;
 * Selected Bus Speed Mode = SDR50; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 2;
 * Selected Bus Speed Mode = SDR104/HS200; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 3;
 * Selected Bus Speed Mode = DDR50; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 4;
 * Selected Bus Speed Mode = Reserved; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = Other values;
 *
 * Preset Value Register Select Condition:
 * Default Speed Mode = SDMMC_HC1R.HSEN = 0.
 * High Speed Mode = SDMMC_HC1R.HSEN = 1.
 *
 * Below Table shows the effective Preset Value Register according to the
 * Selected Bus Speed mode.
 *
 * SDMMC_PVRx = SDMMC_PVR0; Selected Bus Speed Mode = Intilization; Signal
 * Voltage = 3.3V or 1.8V
 * SDMMC_PVRx = SDMMC_PVR1; Selected Bus Speed Mode = Default Speed; Signal
 * Voltage = 3.3V
 * SDMMC_PVRx = SDMMC_PVR2; Selected Bus Speed Mode = High Speed; Signal
 * Voltage = 3.3V
 * SDMMC_PVRx = SDMMC_PVR3; Selected Bus Speed Mode = SDR12; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR4; Selected Bus Speed Mode = SDR25; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR5; Selected Bus Speed Mode = SDR50; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR6; Selected Bus Speed Mode = SDR104/HS200; Signal
 * Voltage = 1.8V
 * SDMMC_PVRx = SDMMC_PVR7; Selected Bus Speed Mode = DDR50; Signal Voltage
 * = 1.8V
 *
 * When Preset Value Enable (PVALEN) in SDMMC_HC2R is set to 1, SDCLK
 * Frequency Select (SDLCKFSEL) and Clock
 * Generator Select (CLKGSEL) in SDMMC_CCR, and Driver Strength Select
 * (DRVSEL) in SDMMC_HC2R are automatically
 * set based on the Selected Bus Speed mode. This means that the user does
 * not need to set these fields when preset
 * is enabled. A Preset Value Register for Initialization (SDMMC_PVR0) is
 * not selected by Bus Speed mode. Before starting
 * the initialization sequence, the user needs to set a clock preset value
 * to SDCLKFSEL in SDMMC_CCR. PVALEN can be
 * set to 1 after the initialization is completed.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_PVR23
 */
#define VTSS_SDMMC_SDMMC_PVR23               VTSS_IOREG(VTSS_TO_SDMMC,0x19)

/**
 * \brief
 * DRVSEL3: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR23 . DRVSEL3
 */
#define  VTSS_F_SDMMC_SDMMC_PVR23_DRVSEL3(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_SDMMC_SDMMC_PVR23_DRVSEL3     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_SDMMC_SDMMC_PVR23_DRVSEL3(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * CLKGSEL3: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR23 . CLKGSEL3
 */
#define  VTSS_F_SDMMC_SDMMC_PVR23_CLKGSEL3(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SDMMC_SDMMC_PVR23_CLKGSEL3    VTSS_BIT(26)
#define  VTSS_X_SDMMC_SDMMC_PVR23_CLKGSEL3(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * SDCLKFSEL3: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR23 . SDCLKFSEL3
 */
#define  VTSS_F_SDMMC_SDMMC_PVR23_SDCLKFSEL3(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SDMMC_SDMMC_PVR23_SDCLKFSEL3     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SDMMC_SDMMC_PVR23_SDCLKFSEL3(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/**
 * \brief
 * DRVSEL2: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR23 . DRVSEL2
 */
#define  VTSS_F_SDMMC_SDMMC_PVR23_DRVSEL2(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SDMMC_SDMMC_PVR23_DRVSEL2     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SDMMC_SDMMC_PVR23_DRVSEL2(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * CLKGSEL2: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR23 . CLKGSEL2
 */
#define  VTSS_F_SDMMC_SDMMC_PVR23_CLKGSEL2(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_PVR23_CLKGSEL2    VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_PVR23_CLKGSEL2(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * SDCLKFSEL2: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR23 . SDCLKFSEL2
 */
#define  VTSS_F_SDMMC_SDMMC_PVR23_SDCLKFSEL2(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SDMMC_SDMMC_PVR23_SDCLKFSEL2     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SDMMC_SDMMC_PVR23_SDCLKFSEL2(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief SDMMC Preset Value Register (for initialization)
 *
 * \details
 * One of the Preset Value Registers is effective based on the selected bus
 * speed mode. Below Table defines the conditions to select one of the
 * SDMMC_PVRs.
 *
 * Selected Bus Speed Mode = Default Speed; VS18EN (SDMMC_HC2R) = 0; HSEN
 * (SDMMC_HC1R) = 0; UHSMS (SDMMC_HC2R) = Don't care;
 * Selected Bus Speed Mode = High Speed; VS18EN (SDMMC_HC2R) = 0; HSEN
 * (SDMMC_HC1R) = 1; UHSMS (SDMMC_HC2R) = Don't care;
 * Selected Bus Speed Mode = SDR12; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 0;
 * Selected Bus Speed Mode = SDR25; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 1;
 * Selected Bus Speed Mode = SDR50; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 2;
 * Selected Bus Speed Mode = SDR104/HS200; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 3;
 * Selected Bus Speed Mode = DDR50; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 4;
 * Selected Bus Speed Mode = Reserved; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = Other values;
 *
 * Preset Value Register Select Condition:
 * Default Speed Mode = SDMMC_HC1R.HSEN = 0.
 * High Speed Mode = SDMMC_HC1R.HSEN = 1.
 *
 * Below Table shows the effective Preset Value Register according to the
 * Selected Bus Speed mode.
 *
 * SDMMC_PVRx = SDMMC_PVR0; Selected Bus Speed Mode = Intilization; Signal
 * Voltage = 3.3V or 1.8V
 * SDMMC_PVRx = SDMMC_PVR1; Selected Bus Speed Mode = Default Speed; Signal
 * Voltage = 3.3V
 * SDMMC_PVRx = SDMMC_PVR2; Selected Bus Speed Mode = High Speed; Signal
 * Voltage = 3.3V
 * SDMMC_PVRx = SDMMC_PVR3; Selected Bus Speed Mode = SDR12; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR4; Selected Bus Speed Mode = SDR25; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR5; Selected Bus Speed Mode = SDR50; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR6; Selected Bus Speed Mode = SDR104/HS200; Signal
 * Voltage = 1.8V
 * SDMMC_PVRx = SDMMC_PVR7; Selected Bus Speed Mode = DDR50; Signal Voltage
 * = 1.8V
 *
 * When Preset Value Enable (PVALEN) in SDMMC_HC2R is set to 1, SDCLK
 * Frequency Select (SDLCKFSEL) and Clock
 * Generator Select (CLKGSEL) in SDMMC_CCR, and Driver Strength Select
 * (DRVSEL) in SDMMC_HC2R are automatically
 * set based on the Selected Bus Speed mode. This means that the user does
 * not need to set these fields when preset
 * is enabled. A Preset Value Register for Initialization (SDMMC_PVR0) is
 * not selected by Bus Speed mode. Before starting
 * the initialization sequence, the user needs to set a clock preset value
 * to SDCLKFSEL in SDMMC_CCR. PVALEN can be
 * set to 1 after the initialization is completed.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_PVR45
 */
#define VTSS_SDMMC_SDMMC_PVR45               VTSS_IOREG(VTSS_TO_SDMMC,0x1a)

/**
 * \brief
 * DRVSEL5: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR45 . DRVSEL5
 */
#define  VTSS_F_SDMMC_SDMMC_PVR45_DRVSEL5(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_SDMMC_SDMMC_PVR45_DRVSEL5     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_SDMMC_SDMMC_PVR45_DRVSEL5(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * CLKGSEL5: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR45 . CLKGSEL5
 */
#define  VTSS_F_SDMMC_SDMMC_PVR45_CLKGSEL5(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SDMMC_SDMMC_PVR45_CLKGSEL5    VTSS_BIT(26)
#define  VTSS_X_SDMMC_SDMMC_PVR45_CLKGSEL5(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * SDCLKFSEL5: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR45 . SDCLKFSEL5
 */
#define  VTSS_F_SDMMC_SDMMC_PVR45_SDCLKFSEL5(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SDMMC_SDMMC_PVR45_SDCLKFSEL5     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SDMMC_SDMMC_PVR45_SDCLKFSEL5(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/**
 * \brief
 * DRVSEL4: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR45 . DRVSEL4
 */
#define  VTSS_F_SDMMC_SDMMC_PVR45_DRVSEL4(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SDMMC_SDMMC_PVR45_DRVSEL4     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SDMMC_SDMMC_PVR45_DRVSEL4(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * CLKGSEL4: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR45 . CLKGSEL4
 */
#define  VTSS_F_SDMMC_SDMMC_PVR45_CLKGSEL4(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_PVR45_CLKGSEL4    VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_PVR45_CLKGSEL4(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * SDCLKFSEL4: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR45 . SDCLKFSEL4
 */
#define  VTSS_F_SDMMC_SDMMC_PVR45_SDCLKFSEL4(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SDMMC_SDMMC_PVR45_SDCLKFSEL4     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SDMMC_SDMMC_PVR45_SDCLKFSEL4(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief SDMMC Preset Value Register (for initialization)
 *
 * \details
 * One of the Preset Value Registers is effective based on the selected bus
 * speed mode. Below Table defines the conditions to select one of the
 * SDMMC_PVRs.
 *
 * Selected Bus Speed Mode = Default Speed; VS18EN (SDMMC_HC2R) = 0; HSEN
 * (SDMMC_HC1R) = 0; UHSMS (SDMMC_HC2R) = Don't care;
 * Selected Bus Speed Mode = High Speed; VS18EN (SDMMC_HC2R) = 0; HSEN
 * (SDMMC_HC1R) = 1; UHSMS (SDMMC_HC2R) = Don't care;
 * Selected Bus Speed Mode = SDR12; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 0;
 * Selected Bus Speed Mode = SDR25; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 1;
 * Selected Bus Speed Mode = SDR50; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 2;
 * Selected Bus Speed Mode = SDR104/HS200; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 3;
 * Selected Bus Speed Mode = DDR50; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = 4;
 * Selected Bus Speed Mode = Reserved; VS18EN (SDMMC_HC2R) = 1; HSEN
 * (SDMMC_HC1R) = Don't care; UHSMS (SDMMC_HC2R) = Other values;
 *
 * Preset Value Register Select Condition:
 * Default Speed Mode = SDMMC_HC1R.HSEN = 0.
 * High Speed Mode = SDMMC_HC1R.HSEN = 1.
 *
 * Below Table shows the effective Preset Value Register according to the
 * Selected Bus Speed mode.
 *
 * SDMMC_PVRx = SDMMC_PVR0; Selected Bus Speed Mode = Intilization; Signal
 * Voltage = 3.3V or 1.8V
 * SDMMC_PVRx = SDMMC_PVR1; Selected Bus Speed Mode = Default Speed; Signal
 * Voltage = 3.3V
 * SDMMC_PVRx = SDMMC_PVR2; Selected Bus Speed Mode = High Speed; Signal
 * Voltage = 3.3V
 * SDMMC_PVRx = SDMMC_PVR3; Selected Bus Speed Mode = SDR12; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR4; Selected Bus Speed Mode = SDR25; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR5; Selected Bus Speed Mode = SDR50; Signal Voltage
 * = 1.8V
 * SDMMC_PVRx = SDMMC_PVR6; Selected Bus Speed Mode = SDR104/HS200; Signal
 * Voltage = 1.8V
 * SDMMC_PVRx = SDMMC_PVR7; Selected Bus Speed Mode = DDR50; Signal Voltage
 * = 1.8V
 *
 * When Preset Value Enable (PVALEN) in SDMMC_HC2R is set to 1, SDCLK
 * Frequency Select (SDLCKFSEL) and Clock
 * Generator Select (CLKGSEL) in SDMMC_CCR, and Driver Strength Select
 * (DRVSEL) in SDMMC_HC2R are automatically
 * set based on the Selected Bus Speed mode. This means that the user does
 * not need to set these fields when preset
 * is enabled. A Preset Value Register for Initialization (SDMMC_PVR0) is
 * not selected by Bus Speed mode. Before starting
 * the initialization sequence, the user needs to set a clock preset value
 * to SDCLKFSEL in SDMMC_CCR. PVALEN can be
 * set to 1 after the initialization is completed.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_PVR67
 */
#define VTSS_SDMMC_SDMMC_PVR67               VTSS_IOREG(VTSS_TO_SDMMC,0x1b)

/**
 * \brief
 * DRVSEL7: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR67 . DRVSEL7
 */
#define  VTSS_F_SDMMC_SDMMC_PVR67_DRVSEL7(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_SDMMC_SDMMC_PVR67_DRVSEL7     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_SDMMC_SDMMC_PVR67_DRVSEL7(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * CLKGSEL7: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR67 . CLKGSEL7
 */
#define  VTSS_F_SDMMC_SDMMC_PVR67_CLKGSEL7(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SDMMC_SDMMC_PVR67_CLKGSEL7    VTSS_BIT(26)
#define  VTSS_X_SDMMC_SDMMC_PVR67_CLKGSEL7(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * SDCLKFSEL7: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR67 . SDCLKFSEL7
 */
#define  VTSS_F_SDMMC_SDMMC_PVR67_SDCLKFSEL7(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SDMMC_SDMMC_PVR67_SDCLKFSEL7     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SDMMC_SDMMC_PVR67_SDCLKFSEL7(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/**
 * \brief
 * DRVSEL6: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR67 . DRVSEL6
 */
#define  VTSS_F_SDMMC_SDMMC_PVR67_DRVSEL6(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SDMMC_SDMMC_PVR67_DRVSEL6     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SDMMC_SDMMC_PVR67_DRVSEL6(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * CLKGSEL6: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR67 . CLKGSEL6
 */
#define  VTSS_F_SDMMC_SDMMC_PVR67_CLKGSEL6(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_PVR67_CLKGSEL6    VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_PVR67_CLKGSEL6(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * SDCLKFSEL6: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_PVR67 . SDCLKFSEL6
 */
#define  VTSS_F_SDMMC_SDMMC_PVR67_SDCLKFSEL6(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SDMMC_SDMMC_PVR67_SDCLKFSEL6     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SDMMC_SDMMC_PVR67_SDCLKFSEL6(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief SDMMC Shared Bus Control Register (SD_SDIO)
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_SBCR
 */
#define VTSS_SDMMC_SDMMC_SBCR                VTSS_IOREG(VTSS_TO_SDMMC,0x38)

/**
 * \brief
 * BEPCTRL: Backup Power Control
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_SBCR . BEPCTRL
 */
#define  VTSS_F_SDMMC_SDMMC_SBCR_BEPCTRL(x)   VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_SDMMC_SDMMC_SBCR_BEPCTRL      VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_SDMMC_SDMMC_SBCR_BEPCTRL(x)   VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * INTPSEL: Interrupt Pin Select
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_SBCR . INTPSEL
 */
#define  VTSS_F_SDMMC_SDMMC_SBCR_INTPSEL(x)   VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_SDMMC_SDMMC_SBCR_INTPSEL      VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_SDMMC_SDMMC_SBCR_INTPSEL(x)   VTSS_EXTRACT_BITFIELD(x,20,3)

/**
 * \brief
 * CLKPSEL: Clock Pin Select
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_SBCR . CLKPSEL
 */
#define  VTSS_F_SDMMC_SDMMC_SBCR_CLKPSEL(x)   VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_SDMMC_SDMMC_SBCR_CLKPSEL      VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_SDMMC_SDMMC_SBCR_CLKPSEL(x)   VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * BWDTPRE: Bus Width Preset
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_SBCR . BWDTPRE
 */
#define  VTSS_F_SDMMC_SDMMC_SBCR_BWDTPRE(x)   VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_SDMMC_SDMMC_SBCR_BWDTPRE      VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_SDMMC_SDMMC_SBCR_BWDTPRE(x)   VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * NBINTP: Number of Interrupt Input Pins
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_SBCR . NBINTP
 */
#define  VTSS_F_SDMMC_SDMMC_SBCR_NBINTP(x)    VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDMMC_SDMMC_SBCR_NBINTP       VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDMMC_SDMMC_SBCR_NBINTP(x)    VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * NBCLKP: Number of Clock Pins
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_SBCR . NBCLKP
 */
#define  VTSS_F_SDMMC_SDMMC_SBCR_NBCLKP(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDMMC_SDMMC_SBCR_NBCLKP       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDMMC_SDMMC_SBCR_NBCLKP(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief SDMMC Slot Interrupt Status Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_SISR
 */
#define VTSS_SDMMC_SDMMC_SISR                VTSS_IOREG(VTSS_TO_SDMMC,0x3f)

/**
 * \brief
 * VVER: Vendor Version NumberReserved. Value subject to change. No
 * functionality associated. This is the internal version of the
 * module.Note: The default value field holds the version number of SDMMC
 * ASIC controller (0x31).
 *
 * \details
 * In case of FPGA MODE, VVER = 0x20
 * In case of ASIC MODE, VVER = 0x31

 *
 * Field: ::VTSS_SDMMC_SDMMC_SISR . VVER
 */
#define  VTSS_F_SDMMC_SDMMC_SISR_VVER(x)      VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_SDMMC_SDMMC_SISR_VVER         VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_SDMMC_SDMMC_SISR_VVER(x)      VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * SVER: Specification Version NumberThis status indicates the SD Host
 * Controller Specification Version.
 *
 * \details
 * 0 = SD Host Specification Version 1.00
 * 1 = SD Host Specification Version 2.00, including the feature of the
 * ADMA and Test Register
 * 2 = SD Host Specification Version 3.00
 *
 * Field: ::VTSS_SDMMC_SDMMC_SISR . SVER
 */
#define  VTSS_F_SDMMC_SDMMC_SISR_SVER(x)      VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SDMMC_SDMMC_SISR_SVER         VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SDMMC_SDMMC_SISR_SVER(x)      VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * INTSSL: Interrupt Signal for Each SlotThese status bits indicate the
 * logical OR of Interrupt Signals and Wakeup Signal for each SDMMC
 * instance in the product(INTSSL[x] corresponds to SDMMCx instance in the
 * product).
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_SISR . INTSSL
 */
#define  VTSS_F_SDMMC_SDMMC_SISR_INTSSL(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_SISR_INTSSL       VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_SISR_INTSSL(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Additional Present State Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_APSR
 */
#define VTSS_SDMMC_SDMMC_APSR                VTSS_IOREG(VTSS_TO_SDMMC,0x80)

/**
 * \brief
 * HDATLL: DAT[7:4] High Line LevelThis status is used to check the
 * DAT[7:4] line level to recover from errors, and for debugging.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_APSR . HDATLL
 */
#define  VTSS_F_SDMMC_SDMMC_APSR_HDATLL(x)    VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDMMC_SDMMC_APSR_HDATLL       VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDMMC_SDMMC_APSR_HDATLL(x)    VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief SDMMC e.MMC Control 1/2/3 Register and Debounce Register
 *
 * \details
 * This register is a combination of SDMMC_MC1R, SDMMC_MC2R, SDMMC_MC3R,
 * and SDMMC_DEBR.
 * SDMMC_MCR_DEBR = {SDMMC_DEBR[7:0], SDMMC_MC3R[7:0], SDMMC_MC2R[7:0],
 * SDMMC_MC1R[7:0]}
 *
 * Note: SDMMC_MCR_DEBR[15:8] bits have write-only access.

 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_MCR_DEBR
 */
#define VTSS_SDMMC_SDMMC_MCR_DEBR            VTSS_IOREG(VTSS_TO_SDMMC,0x81)

/**
 * \brief
 * CDDVAL: Card Detect Debounce ValueDefines the debounce delay for card
 * insertion/removal.
 *
 * \details
 * 0 = 1 (Number of Slow Clock Cycles)
 * 1 = 8 (Number of Slow Clock Cycles)
 * 2 = 33 (Number of Slow Clock Cycles)
 * 3 = SDCD_DEBOUNCE_PERIOD
 *
 * Debounce = N x tSLCK
 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . CDDVAL
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_CDDVAL(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_CDDVAL     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_CDDVAL(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * DQSUPVAL: DQS Delay Update Timer Value
 *
 * \details
 * 0: DQS delay update is performed each time a command is sent to the
 * device.
 * n: DQS delay update is performed before sending the command only if a
 * timer delay is elapsed. The timer delay t is defined
 * as follows:
 *
 * t = (2 ^ (n+1) - 1) x tSLCK
 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . DQSUPVAL
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_DQSUPVAL(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_DQSUPVAL     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_DQSUPVAL(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/**
 * \brief
 * ESMEN: Enhanced Strobe Mode EnableThis field is used to enable the
 * Enhanced Strobe Mode. User must ensure that this mode is supported by
 * the eMMC device(Only devices compliant with the Embedded Multimedia Card
 * (e.MMC) Electrical Standard 5.1 and further support thismode).
 *
 * \details
 * 0 (DISABLED): Enhanced Strobe mode is disabled.
 * 1 (ENABLED): Enhanced Strobe mode is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . ESMEN
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_ESMEN(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_ESMEN    VTSS_BIT(17)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_ESMEN(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * HS400EN: HS400 Mode EnableThis field is used to select the e.MMC HS400
 * mode.If Preset Value Enable is set to 1, SDMMC sets SDCLK Frequency
 * Select (SDCLKFSEL), Clock Generator Select (CLKGSEL)in SDMMC_CCR and
 * Driver Strength Select (DRVSEL) according to SDMMC_PVR. In this case,
 * SDMMC_EPVR8register is selected by this bit. The user needs to reset SD
 * Clock Enable (SDCLKEN) before changing this field to avoidgenerating a
 * clock glitch. After setting this field, the user sets SDCLKEN to 1
 * again.
 *
 * \details
 * 0 (DISABLED): HS400 mode is disabled.
 * 1 (ENABLED): HS400 mode is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . HS400EN
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_HS400EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_HS400EN  VTSS_BIT(16)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_HS400EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * ABOOT: e.MMC Abort BootThis bit is used to exit from Boot mode. Writing
 * this bit to 1 exits the Boot Operation mode. Writing 0 is ignored.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . ABOOT
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_ABOOT(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_ABOOT    VTSS_BIT(9)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_ABOOT(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * SRESP: e.MMC Abort Wait IRQThis bit is used to exit from the Interrupt
 * mode. When this bit is written to 1, the SDMMC sends the CMD40 response
 * automatically.This brings the e.MMC from Interrupt mode to the standard
 * Data Transfer mode. Writing this bit to 0 is ignored.Note: This bit is
 * only effective when CMD_TYP in SDMMC_MC1R is set to WAITIRQ.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . SRESP
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_SRESP(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_SRESP    VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_SRESP(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * FCD: e.MMC Force Card DetectWhen using e.MMC, the user can set this bit
 * to 1 to bypass the card detection procedure using the SDMMC_CD signal.
 *
 * \details
 * 0(DISABLED): e.MMC Forced Card Detect is disabled. The SDMMC_CD signal
 * is used and debounce timing is applied.
 * 1(ENABLED): e.MMC Forced Card Detect is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . FCD
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_FCD(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_FCD      VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_FCD(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * RSTN: e.MMC Reset SignalThis bit controls the e.MMC reset signal.
 *
 * \details
 * 0: Reset signal is inactive.
 * 1: Reset signal is active.
 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . RSTN
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_RSTN     VTSS_BIT(6)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * e.MMC Boot Acknowledge EnableThis bit must be set according to the value
 * of BOOT_ACK in the Extended CSD Register (see Embedded MultiMedia
 * Card(e.MMC) Electrical Standard 4.51).When this bit is set to 1, the
 * SDMMC waits for boot acknowledge pattern from the e.MMC before receiving
 * boot data.If the boot acknowledge pattern is wrong, the BOOTAE status
 * flag rises in SDMMC_EISTR if BOOTAE is set inSDMMC_EISTER. An interrupt
 * is generated if BOOTAE is set in SDMMC_EISIER.If the no boot acknowledge
 * pattern is received, the DATTEO status flag rises in SDMMC_EISTR if
 * DATTEO is set inSDMMC_EISTER. An interrupt is generated if DATTEO is set
 * in SDMMC_EISIER.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . BOOTA
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_BOOTA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_BOOTA    VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_BOOTA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * OPD: e.MMC Open Drain ModeThis bit sets the command line in open drain.
 *
 * \details
 * 0: The command line is in push-pull.
 * 1: The command line is in open drain.
 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . OPD
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_OPD(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_OPD      VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_OPD(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * DDR: e.MMC HSDDR ModeThis bit selects the High Speed DDR mode.
 *
 * \details
 * 0: High Speed DDR is not selected.
 * 1: High Speed DDR is selected.
 *
 * Note: The clock divider (DIV) in SDMMC_CCR must be set to a value
 * different from 0 when DDR is 1.
 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . DDR
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_DDR(x)   VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_DDR      VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_DDR(x)   VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * MMC_CMDTYP: e.MMC Command Type
 *
 * \details
 * 0 (NORMAL) = The command is not an e.MMC specific command.
 *
 * 1 (WAITRQ) = This bit must be set to 1 when the e.MMC is in Interrupt
 * mode (CMD40). See "Interrupt Mode" in the
 * Embedded MultiMedia Card (e.MMC) Electrical Standard 4.51.
 *
 * 2 (STREAM) = This bit must be set to 1 in the case of Stream Read(CMD11)
 * or Stream Write (CMD20). Only effective for
 * e.MMC up to revision 4.41.
 *
 * 3 (BOOT) = Starts a Boot Operation mode at the next write to SDMMC_CR.
 * Boot data are read directly from e.MMC device.

 *
 * Field: ::VTSS_SDMMC_SDMMC_MCR_DEBR . MMC_CMDTYP
 */
#define  VTSS_F_SDMMC_SDMMC_MCR_DEBR_MMC_CMDTYP(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDMMC_SDMMC_MCR_DEBR_MMC_CMDTYP     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDMMC_SDMMC_MCR_DEBR_MMC_CMDTYP(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief SDMMC AHB Control Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_ACR
 */
#define VTSS_SDMMC_SDMMC_ACR                 VTSS_IOREG(VTSS_TO_SDMMC,0x82)

/**
 * \brief
 * DFQOS: Descriptor Fetch QOSThis field defines the QOS value of ADMA AHB
 * access when fetching descriptor. For all other accesses, the QOS is
 * fixedto 0.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_ACR . DFQOS
 */
#define  VTSS_F_SDMMC_SDMMC_ACR_DFQOS(x)      VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_SDMMC_SDMMC_ACR_DFQOS         VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_SDMMC_SDMMC_ACR_DFQOS(x)      VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * BUFM: AHB Bufferable ModeThis field defines if last access of data
 * transfer is bufferable or not.
 *
 * \details
 * 0 (NEVER) = All SDMA/ADMA AHB accesses are not bufferable
 * 1 (ALWAYS) = All SDMA/ADMA AHB accesses are bufferable
 * 2 (BLOCK) = All SDMA/ADMA AHB accesses are bufferable except the last
 * access of a data block
 * 3 (TRANSFER) = All SDMA/ADMA AHB accesses are bufferable except the last
 * access of a data transfer
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACR . BUFM
 */
#define  VTSS_F_SDMMC_SDMMC_ACR_BUFM(x)       VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_SDMMC_SDMMC_ACR_BUFM          VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_SDMMC_SDMMC_ACR_BUFM(x)       VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * B1KBDIS: 1kB Boundary DisableOnly significant when the xKBBoundary is
 * not supported by the HMATRIX. Used for debug.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_ACR . B1KBDIS
 */
#define  VTSS_F_SDMMC_SDMMC_ACR_B1KBDIS(x)    VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_ACR_B1KBDIS       VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_ACR_B1KBDIS(x)    VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * HNBRDIS: HNBREQ DisableUsed for debug to modulate the SDMMC master
 * interface bandwidth. Set to 1 to reduce the SDMMC bandwidth.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_ACR . HNBRDIS
 */
#define  VTSS_F_SDMMC_SDMMC_ACR_HNBRDIS(x)    VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_ACR_HNBRDIS       VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_ACR_HNBRDIS(x)    VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * BMAX: AHB Maximum BurstThis field selects the maximum burst size in case
 * of DMA transfer.
 *
 * \details
 * 0 = The maximum burst size is INCR16.
 * 1 = The maximum burst size is INCR8.
 * 2 = The maximum burst size is INCR4.
 * 3 = Only SINGLE transfers are performed.
 *
 * Field: ::VTSS_SDMMC_SDMMC_ACR . BMAX
 */
#define  VTSS_F_SDMMC_SDMMC_ACR_BMAX(x)       VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDMMC_SDMMC_ACR_BMAX          VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDMMC_SDMMC_ACR_BMAX(x)       VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief SDMMC Clock Control 2 Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_CC2R
 */
#define VTSS_SDMMC_SDMMC_CC2R                VTSS_IOREG(VTSS_TO_SDMMC,0x83)

/**
 * \brief
 * FSDCLKD: Force SDCLK DisabledThe user can choose to maintain the SDCLK
 * during 8 SDCLK cycles after the end bit of the last data block in case
 * of a readtransaction, or after the end bit of the CRC status in case of
 * a write transaction.
 *
 * \details
 * 0: The SDCLK is forced and it cannot be stopped immediately after the
 * transaction.
 * 1: The SDCLK is not forced and it can be stopped immediately after the
 * transaction.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CC2R . FSDCLKD
 */
#define  VTSS_F_SDMMC_SDMMC_CC2R_FSDCLKD(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_CC2R_FSDCLKD      VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_CC2R_FSDCLKD(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Retuning Control 1 and 2 Register
 *
 * \details
 * This register is combination of SDMMC_RTC1R and SDMMC_RTC2R registers.
 * SDMMC_RTC_1R2R = {16'h0, SDMMC_RTC2R[7:0], SDMMC_RTC1R[7:0]}
 *
 * Note: SDMMC_RTC_1R2R[15:8] bits have write-only access.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_RTC_1R2R
 */
#define VTSS_SDMMC_SDMMC_RTC_1R2R            VTSS_IOREG(VTSS_TO_SDMMC,0x84)

/**
 * \brief
 * RLD: Retuning Timer ReloadThis bit is only efficient if the Retuning
 * timer is enabled (SDMMC_RTC1R.TMREN set to 1). Once the Timer Counter
 * Value(TCVAL) is set to a nonzero value in SDMMC_RTCVR, setting this bit
 * to 1 starts the timer count. The retuning timer countrestarts each time
 * this bit is written to 1.Writing this bit to 0 has no effect.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_RTC_1R2R . RLD
 */
#define  VTSS_F_SDMMC_SDMMC_RTC_1R2R_RLD(x)   VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_RTC_1R2R_RLD      VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_RTC_1R2R_RLD(x)   VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * TMREN: Retuning Timer EnableEnable the retuning timer.
 *
 * \details
 * 0 (DISABLED): The retuning timer is disabled.
 * 1 (ENABLED): The retuning timer is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_RTC_1R2R . TMREN
 */
#define  VTSS_F_SDMMC_SDMMC_RTC_1R2R_TMREN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_RTC_1R2R_TMREN    VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_RTC_1R2R_TMREN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Retuning Counter Value Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_RTCVR
 */
#define VTSS_SDMMC_SDMMC_RTCVR               VTSS_IOREG(VTSS_TO_SDMMC,0x85)

/**
 * \brief
 * TCVAL: Retuning Timer Counter ValueThe TCVAL value is used to define the
 * time before expiration of the retuning timer where:Time = 2 ^ (TCVAL -
 * 1) secondsThis value must range between 1 and 11. Any other value
 * results in the retuning timer being disabled.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_RTCVR . TCVAL
 */
#define  VTSS_F_SDMMC_SDMMC_RTCVR_TCVAL(x)    VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDMMC_SDMMC_RTCVR_TCVAL       VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDMMC_SDMMC_RTCVR_TCVAL(x)    VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief SDMMC Retuning Interrupt Status Enable and Signal Enable Register
 *
 * \details
 * This register is a combination of SDMMC_RTISTER and SDMMC_RTISIER
 * registers.
 * SDMMC_RTI_STSIER = {16'h0, SDMMC_RTISIER[7:0], SDMMC_RTISTER[7:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_RTI_STSIER
 */
#define VTSS_SDMMC_SDMMC_RTI_STSIER          VTSS_IOREG(VTSS_TO_SDMMC,0x86)

/**
 * \brief
 * TEVT_SIG_EN: Retuning Timer Event
 *
 * \details
 * 0 (MASKED): No interrupt is generated when the TEVT status rises in
 * SDMMC_RTISTR.
 * 1 (ENABLED): An interrupt is generated when the TEVT status rises in
 * SDMMC_RTISTR.
 *
 * Field: ::VTSS_SDMMC_SDMMC_RTI_STSIER . TEVT_SIG_EN
 */
#define  VTSS_F_SDMMC_SDMMC_RTI_STSIER_TEVT_SIG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_RTI_STSIER_TEVT_SIG_EN  VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_RTI_STSIER_TEVT_SIG_EN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * TEVT_STA_EN: Retuning Timer Event
 *
 * \details
 * 0 (MASKED): The TEVT status flag in SDMMC_RTISTR is masked.
 * 1 (ENABLED): The TEVT status flag in SDMMC_RTISTR is enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_RTI_STSIER . TEVT_STA_EN
 */
#define  VTSS_F_SDMMC_SDMMC_RTI_STSIER_TEVT_STA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_RTI_STSIER_TEVT_STA_EN  VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_RTI_STSIER_TEVT_STA_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Retuning Interrupt Status Register and Retuning Status Slots Register
 *
 * \details
 * This register is a combination of SDMMC_RTISTR and SDMMC_RTSSR
 * registers.
 * SDMMC_RTISTR_RTSSR = {16'h0, SDMMC_RTSSR[7:0], SDMMC_RTISTR[7:0]}
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_RTISTR_RTSSR
 */
#define VTSS_SDMMC_SDMMC_RTISTR_RTSSR        VTSS_IOREG(VTSS_TO_SDMMC,0x87)

/**
 * \brief
 * TEVTSLOT: Retuning Timer Event SlotsThese status bits indicate the TEVT
 * status for each SDMMC instance in the product (TEVTSLOT[x] corresponds
 * toSDMMCx instance in the product).
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_RTISTR_RTSSR . TEVTSLOT
 */
#define  VTSS_F_SDMMC_SDMMC_RTISTR_RTSSR_TEVTSLOT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_RTISTR_RTSSR_TEVTSLOT  VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_RTISTR_RTSSR_TEVTSLOT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * TEVT_STA: Retuning Timer EventThis bit is set to 1 when the retuning
 * timer count is elapsed if SDMMC_RTI_STSIER.TEVT_STA_EN is set to 1. An
 * interrupt is generatedif SDMMC_RTI_STSIER.TEVT_SIG_EN is set to
 * 1.Writing this bit to 1 clears this bit.
 *
 * \details
 * 0: No retuning timer event.
 * 1: Retuning timer event.
 *
 * Field: ::VTSS_SDMMC_SDMMC_RTISTR_RTSSR . TEVT_STA
 */
#define  VTSS_F_SDMMC_SDMMC_RTISTR_RTSSR_TEVT_STA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_RTISTR_RTSSR_TEVT_STA  VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_RTISTR_RTSSR_TEVT_STA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Tuning Control Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_TUNCR
 */
#define VTSS_SDMMC_SDMMC_TUNCR               VTSS_IOREG(VTSS_TO_SDMMC,0x88)

/**
 * \brief
 * SMPLPT: Sampling PointThis bit selects the position of the sampling
 * point into the data window for SDR104 and HS200 modes.
 *
 * \details
 * 0: Sampling point is set at 50% of the data window.
 * 1: Sampling point is set at 75% of the data window.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TUNCR . SMPLPT
 */
#define  VTSS_F_SDMMC_SDMMC_TUNCR_SMPLPT(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_TUNCR_SMPLPT      VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_TUNCR_SMPLPT(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Tuning Status Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_TUNSR
 */
#define VTSS_SDMMC_SDMMC_TUNSR               VTSS_IOREG(VTSS_TO_SDMMC,0x89)

/**
 * \brief
 * SMPLES: Tuning Sampling SDCLK Edge StatusThis bit is only significant
 * when the SDMMC is operating in UHS SDR104 or HS200 mode. This bit
 * indicates which edge ofthe sampling clock is used to read the data from
 * the device.
 *
 * \details
 * 0: Rising edge
 * 1: Falling edge
 *
 * Field: ::VTSS_SDMMC_SDMMC_TUNSR . SMPLES
 */
#define  VTSS_F_SDMMC_SDMMC_TUNSR_SMPLES(x)   VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SDMMC_SDMMC_TUNSR_SMPLES      VTSS_BIT(8)
#define  VTSS_X_SDMMC_SDMMC_TUNSR_SMPLES(x)   VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DLLPS: Tuning DLL Phase StatusThis bit is only significant when the
 * SDMMC is operating in UHS SDR104 or HS200 mode. This field indicates the
 * phaseshift value of the internal DLL.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_TUNSR . DLLPS
 */
#define  VTSS_F_SDMMC_SDMMC_TUNSR_DLLPS(x)    VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDMMC_SDMMC_TUNSR_DLLPS       VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDMMC_SDMMC_TUNSR_DLLPS(x)    VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief SDMMC FSM Timings Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_FSMTR
 */
#define VTSS_SDMMC_SDMMC_FSMTR               VTSS_IOREG(VTSS_TO_SDMMC,0x8a)

/**
 * \brief
 * NDATTI: Data Turn-around IncrementUsed for debug in case of FSM issue.
 *
 * \details
 * 0 (DECREMENT): Decrement Data Turn-around cycles defined in the SDMMC
 * FSM with NDATTO value.
 * 1 (INCREMENT): Increment Data Turn-around cycles defined in the SDMMC
 * FSM with NDATTO value.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NDATTI
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NDATTI(x)   VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NDATTI      VTSS_BIT(31)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NDATTI(x)   VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * NDATTO: Data Turn-around offsetUsed for debug in case of FSM issue.
 *
 * \details
 * NDATTI = 0: Subtract NDATTO value from the number of Data Turn-around
 * cycles defined in the SDMMC FSM.
 * NDATTI = 1: Add NDATTO value to the number of Data Turn-around cycles
 * define in the SDMMC FSM.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NDATTO
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NDATTO(x)   VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NDATTO      VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NDATTO(x)   VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * NCMDTI: Command Turn-around IncrementUsed for debug in case of FSM
 * issue.
 *
 * \details
 * 0 (DECREMENT): Decrement Command Turn-around cycles defined in the SDMMC
 * FSM with NCMDTO value.
 * 1 (INCREMENT): Increment Command Turn-around cycles defined in the SDMMC
 * FSM with NCMDTO value.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCMDTI
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCMDTI(x)   VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCMDTI      VTSS_BIT(27)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCMDTI(x)   VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * NCMDTO: Command Turn-around offsetUsed for debug in case of FSM issue.
 *
 * \details
 * NCMDTI = 0: Subtract NCMDTO value from the number of Command Turn-around
 * cycles defined in the SDMMC FSM.
 * NCMDTI = 1: Add NCMDTO value to the number of Command Turn-around cycles
 * define in the SDMMC FSM.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCMDTO
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCMDTO(x)   VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCMDTO      VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCMDTO(x)   VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * NCRCUHSI: Ncrc_uhs IncrementUsed for debug in case of FSM issue.
 *
 * \details
 * 0 (DECREMENT): Decrement Ncrc_uhs cycles defined in the SDMMC FSM with
 * NCRCUHSO value.
 * 1 (INCREMENT): Increment Ncrc_uhs cycles defined in the SDMMC FSM with
 * NCRCUHSO value.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCRCUHSI
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCRCUHSI(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCRCUHSI    VTSS_BIT(23)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCRCUHSI(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * NCRCUHSO: Ncrc_uhs offsetUsed for debug in case of FSM issue.
 *
 * \details
 * NCRCUHSI = 0: Subtract NCRCUHSO value from the number of Ncrc_uhs cycles
 * defined in the SDMMC FSM.
 * NCRCUHSI = 1: Add NCRCUHSO value to the number of Ncrc_uhs cycles define
 * in the SDMMC FSM.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCRCUHSO
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCRCUHSO(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCRCUHSO     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCRCUHSO(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * NCRCI: Ncrc IncrementUsed for debug in case of FSM issue.
 *
 * \details
 * 0 (DECREMENT): Decrement Ncrc cycles defined in the SDMMC FSM with NCRCO
 * value.
 * 1 (INCREMENT): Increment Ncrc cycles defined in the SDMMC FSM with NCRCO
 * value.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCRCI
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCRCI(x)    VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCRCI       VTSS_BIT(19)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCRCI(x)    VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * NCRCO: Ncrc offsetUsed for debug in case of FSM issue.
 *
 * \details
 * NSBI = 0: Subtract NCRCO value from the number of Ncrc cycles defined in
 * the SDMMC FSM.
 * NSBI = 1: Add NCRCO value to the number of Ncrc cycles define in the
 * SDMMC FSM.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCRCO
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCRCO(x)    VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCRCO       VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCRCO(x)    VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * NSBUHSI: Nsb_uhs IncrementUsed for debug in case of FSM issue.
 *
 * \details
 * 0 (DECREMENT): Decrement Nsb_uhs cycles defined in the SDMMC FSM with
 * NSBUHSO value.
 * 1 (INCREMENT): Increment Nsb_uhs cycles defined in the SDMMC FSM with
 * NSBUHSO value.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NSBUHSI
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NSBUHSI(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NSBUHSI     VTSS_BIT(15)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NSBUHSI(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * NSBUHSO: Nsb_uhs offsetUsed for debug in case of FSM issue.
 *
 * \details
 * NSBUHSI = 0: Subtract NSBUHSO value from the number of Nsb_uhs cycles
 * defined in the SDMMC FSM.
 * NSBUHSI = 1: Add NSBUHSO value to the number of Nsb_uhs cycles define in
 * the SDMMC FSM.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NSBUHSO
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NSBUHSO(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NSBUHSO     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NSBUHSO(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * NSBI: Nsb IncrementUsed for debug in case of FSM issue.
 *
 * \details
 * 0 (DECREMENT): Decrement Nsb cycles defined in the SDMMC FSM with NSBO
 * value.
 * 1 (INCREMENT): Increment Nsb cycles defined in the SDMMC FSM with NSBO
 * value.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NSBI
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NSBI(x)     VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NSBI        VTSS_BIT(11)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NSBI(x)     VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * NSBO: Nsb offsetUsed for debug in case of FSM issue.
 *
 * \details
 * NSBI = 0: Subtract NSBO value from the number of Nsb cycles defined in
 * the SDMMC FSM.
 * NSBI = 1: Add NSBO value to the number of Nsb cycles define in the SDMMC
 * FSM.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NSBO
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NSBO(x)     VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NSBO        VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NSBO(x)     VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * NCRMINI: Ncr Min IncrementUsed for debug in case of FSM issue.
 *
 * \details
 * 0 (DECREMENT): Decrement Ncr_min cycles defined in the SDMMC FSM with
 * NCRMINO value.
 * 1 (INCREMENT): Increment Ncr_min cycles defined in the SDMMC FSM with
 * NCRMINO value.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCRMINI
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCRMINI(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCRMINI     VTSS_BIT(7)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCRMINI(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * NCRMINO: Ncr Min offsetUsed for debug in case of FSM issue.
 *
 * \details
 * NCRMINI = 0: Subtract NCRMINO value from the number of Ncr_min cycles
 * defined in the SDMMC FSM.
 * NCRMINI = 1: Add NCRMINO value to the number of Ncr_min cycles define in
 * the SDMMC FSM.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCRMINO
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCRMINO(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCRMINO     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCRMINO(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * NCRMAXI: Ncr Max IncrementUsed for debug in case of FSM issue.
 *
 * \details
 * 0 (DECREMENT): Decrement Ncr_max cycles defined in the SDMMC FSM with
 * NCRMAXO value.
 * 1 (INCREMENT): Increment Ncr_max cycles defined in the SDMMC FSM with
 * NCRMAXO value.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCRMAXI
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCRMAXI(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCRMAXI     VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCRMAXI(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * NCRMAXO: Ncr Max offsetUsed for debug in case of FSM issue.
 *
 * \details
 * NCRMAXI = 0: Subtract NCRMAXO value from the number of Ncr_max cycles
 * defined in the SDMMC FSM.
 * NCRMAXI = 1: Add NCRMAXO value to the number of Ncr_max cycles defined
 * in the SDMMC FSM.
 *
 * Field: ::VTSS_SDMMC_SDMMC_FSMTR . NCRMAXO
 */
#define  VTSS_F_SDMMC_SDMMC_FSMTR_NCRMAXO(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDMMC_SDMMC_FSMTR_NCRMAXO     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDMMC_SDMMC_FSMTR_NCRMAXO(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief SDMMC Capabilities Control Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_CACR
 */
#define VTSS_SDMMC_SDMMC_CACR                VTSS_IOREG(VTSS_TO_SDMMC,0x8c)

/**
 * \brief
 * CACR_KEY: Key
 *
 * \details
 * Value = 46th;
 * Writing any other value in this field aborts the write operation of the
 * CAPWREN bit.
 * Always reads as 0.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CACR . CACR_KEY
 */
#define  VTSS_F_SDMMC_SDMMC_CACR_CACR_KEY(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SDMMC_SDMMC_CACR_CACR_KEY     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SDMMC_SDMMC_CACR_CACR_KEY(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * CAPWREN: Capabilities Write EnableThis bit can only be written if KEY
 * correspond to 46h.
 *
 * \details
 * 0: Capabilities registers (SDMMC_CA0R and SDMMC_CA1R) cannot be written.
 * 1: Capabilities registers (SDMMC_CA0R and SDMMC_CA1R) can be written.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CACR . CAPWREN
 */
#define  VTSS_F_SDMMC_SDMMC_CACR_CAPWREN(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_CACR_CAPWREN      VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_CACR_CAPWREN(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Debug Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_DBGR
 */
#define VTSS_SDMMC_SDMMC_DBGR                VTSS_IOREG(VTSS_TO_SDMMC,0x8d)

/**
 * \brief
 * NIDBG: Nonintrusive Debug
 *
 * \details
 * 0 (DISABLED): Reading the SDMMC_BDPR via debugger increments the dual
 * port RAM read pointer.
 * 1 (ENABLED): Reading the SDMMC_BDPR via debugger does not increment the
 * dual port RAM read pointer.
 *
 * Field: ::VTSS_SDMMC_SDMMC_DBGR . NIDBG
 */
#define  VTSS_F_SDMMC_SDMMC_DBGR_NIDBG(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_DBGR_NIDBG        VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_DBGR_NIDBG(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Enhanced Debug Register (ASIC specific)
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_EDBGR
 */
#define VTSS_SDMMC_SDMMC_EDBGR               VTSS_IOREG(VTSS_TO_SDMMC,0x8e)

/**
 * \brief
 * EDBGR_KEY: Key
 *
 * \details
 * Value = 46th;
 * Writing any other value in this field aborts the write operation of the
 * SDMMC_EDBGR[3:0] bits.
 * Always reads as 0.
 *
 * Field: ::VTSS_SDMMC_SDMMC_EDBGR . EDBGR_KEY
 */
#define  VTSS_F_SDMMC_SDMMC_EDBGR_EDBGR_KEY(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_SDMMC_SDMMC_EDBGR_EDBGR_KEY     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_SDMMC_SDMMC_EDBGR_EDBGR_KEY(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * INU: Interrupt Not UsedThis bit can only be written if KEY corresponds
 * to 46h.
 *
 * \details
 * 0: SDMMC_DAT[1] used for SDIO interrupt feature.
 * 1: SDMMC_DAT[1] not used for SDIO interrupt feature.
 *
 * Field: ::VTSS_SDMMC_SDMMC_EDBGR . INU
 */
#define  VTSS_F_SDMMC_SDMMC_EDBGR_INU(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDMMC_SDMMC_EDBGR_INU         VTSS_BIT(3)
#define  VTSS_X_SDMMC_SDMMC_EDBGR_INU(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * CEFEN: Consecutive Event Filter EnableThis bit can only be written if
 * KEY corresponds to 46h.
 *
 * \details
 * 0: Consecutive events are not filtered in the controller synchronization
 * modules. Can lead to a system lock.
 * 1: Consecutive events are filtered in the controller synchronization
 * modules. (Default value)
 *
 * Field: ::VTSS_SDMMC_SDMMC_EDBGR . CEFEN
 */
#define  VTSS_F_SDMMC_SDMMC_EDBGR_CEFEN(x)    VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDMMC_SDMMC_EDBGR_CEFEN       VTSS_BIT(2)
#define  VTSS_X_SDMMC_SDMMC_EDBGR_CEFEN(x)    VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TIMWEN: Timings Write EnableThis bit can only be written if KEY
 * corresponds to 46h.
 *
 * \details
 * 0: SDMMC_FSMTR cannot be written.
 * 1: SDMMC_FSMTR can be written.
 *
 * Field: ::VTSS_SDMMC_SDMMC_EDBGR . TIMWEN
 */
#define  VTSS_F_SDMMC_SDMMC_EDBGR_TIMWEN(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDMMC_SDMMC_EDBGR_TIMWEN      VTSS_BIT(1)
#define  VTSS_X_SDMMC_SDMMC_EDBGR_TIMWEN(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXPHWEN: Tx Phase Write EnableThis bit can only be written if KEY
 * corresponds to 46h.
 *
 * \details
 * 0: SDMMC_TXPHTR cannot be written.
 * 1: SDMMC_TXPHTR can be written.
 *
 * Field: ::VTSS_SDMMC_SDMMC_EDBGR . TXPHWEN
 */
#define  VTSS_F_SDMMC_SDMMC_EDBGR_TXPHWEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_EDBGR_TXPHWEN     VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_EDBGR_TXPHWEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Calibration Control Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_CALCR
 */
#define VTSS_SDMMC_SDMMC_CALCR               VTSS_IOREG(VTSS_TO_SDMMC,0x90)

/**
 * \brief
 * CALPBP: Calibration PBypass valueCalibration code applied for the
 * p-channel transistors when BPEN is set to 1. This field is ignored if
 * BPEN is 0.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . CALPBP
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_CALPBP(x)   VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_SDMMC_SDMMC_CALCR_CALPBP      VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_SDMMC_SDMMC_CALCR_CALPBP(x)   VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * CALP: Calibration P StatusCalibration code for the p-channel transistors
 * to match the required output impedance.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . CALP
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_CALP(x)     VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_SDMMC_SDMMC_CALCR_CALP        VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_SDMMC_SDMMC_CALCR_CALP(x)     VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * CALNBP: Calibration N Bypass valueCalibration code applied for the
 * n-channel transistors when BPEN is set to 1. This field is ignored if
 * BPEN is 0.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . CALNBP
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_CALNBP(x)   VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_SDMMC_SDMMC_CALCR_CALNBP      VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_SDMMC_SDMMC_CALCR_CALNBP(x)   VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * CALN: Calibration N StatusCalibration code for the n-channel transistors
 * to match the required output impedance.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . CALN
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_CALN(x)     VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SDMMC_SDMMC_CALCR_CALN        VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SDMMC_SDMMC_CALCR_CALN(x)     VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Defines the number of HCLOCK cycles (divided by 4) required to cover the
 * I/O calibration cell startup time.CNTVAL(Minimum) = tSTARTUP / 4 x
 * tHCLOCKtSTARTUP = CALIB_STARTUP_TIME
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . CNTVAL
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_CNTVAL(x)   VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SDMMC_SDMMC_CALCR_CNTVAL      VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SDMMC_SDMMC_CALCR_CNTVAL(x)   VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * BPEN: Calibration Bypass Enabled
 *
 * \details
 * 0: Calibration bypass is not enabled.
 * 1: Calibration bypass is enabled. CALPBP and CALNBP codes are applied to
 * the calibration cell.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . BPEN
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_BPEN(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDMMC_SDMMC_CALCR_BPEN        VTSS_BIT(6)
#define  VTSS_X_SDMMC_SDMMC_CALCR_BPEN(x)     VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * TUNDIS: Calibration During Tuning Disabled
 *
 * \details
 * 0: Calibration is launched before each tuning.
 * 1: Calibration is not launched at tuning.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . TUNDIS
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_TUNDIS(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDMMC_SDMMC_CALCR_TUNDIS      VTSS_BIT(5)
#define  VTSS_X_SDMMC_SDMMC_CALCR_TUNDIS(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * ALWYSON: Calibration Analog Always ON
 *
 * \details
 * 0: Calibration analog is shut down after each calibration.
 * 1: Calibration analog remains powered after calibration.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . ALWYSON
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_ALWYSON(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_CALCR_ALWYSON     VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_CALCR_ALWYSON(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * CLKDIV: Calibration Clock DivisionThe clock applied to the calibration
 * cell is divided by CLKDIV + 1
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . CLKDIV
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_CLKDIV(x)   VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_SDMMC_SDMMC_CALCR_CLKDIV      VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_SDMMC_SDMMC_CALCR_CLKDIV(x)   VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * EN: PADs Calibration EnableThis bit is automatically cleared once the
 * calibration is done.
 *
 * \details
 * 0: SDMMC I/O calibration disabled.
 * 1: SDMMC I/O calibration enabled.
 *
 * Field: ::VTSS_SDMMC_SDMMC_CALCR . EN
 */
#define  VTSS_F_SDMMC_SDMMC_CALCR_EN(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDMMC_SDMMC_CALCR_EN          VTSS_BIT(0)
#define  VTSS_X_SDMMC_SDMMC_CALCR_EN(x)       VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SDMMC Extended Preset Value Register 8 (ASIC specific)
 *
 * \details
 * Preset Value Register 8 is effective based on the selected bus speed
 * mode. Table 15-9 defines the conditions to select the
 * SDMMC_EPVR8.
 *
 * Preset Value Register Select Condition:
 * Selected Bus Speed Mode = HS400; SDMMC_MCR_DEBR.HS400EN = 1;
 *
 * When Preset Value Enable (PVALEN) in SDMMC_HC2R is set to 1, SDCLK
 * Frequency Select (SDLCKFSEL) and Clock
 * Generator Select (CLKGSEL) in SDMMC_CCR, and Driver Strength Select
 * (DRVSEL) in SDMMC_HC2R are automatically
 * set based on the selected bus speed mode. This means that the user does
 * not need to set these fields when preset is
 * enabled. Before starting the initialization sequence, the user needs to
 * set a clock preset value to SDCLKFSEL in
 * SDMMC_CCR. Bit PVALEN can be set to 1 after the initialization is
 * completed.
 *
 * Register: \a SDMMC:SDMMC_REG:SDMMC_EPVR8
 */
#define VTSS_SDMMC_SDMMC_EPVR8               VTSS_IOREG(VTSS_TO_SDMMC,0x91)

/**
 * \brief
 * EPVR8_DRVSEL: Driver Strength SelectSee DRVSEL in SDMMC_HC2R.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_EPVR8 . EPVR8_DRVSEL
 */
#define  VTSS_F_SDMMC_SDMMC_EPVR8_EPVR8_DRVSEL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SDMMC_SDMMC_EPVR8_EPVR8_DRVSEL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SDMMC_SDMMC_EPVR8_EPVR8_DRVSEL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * EPVR8_CLKGSEL: Clock Generator SelectSee CLKGSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_EPVR8 . EPVR8_CLKGSEL
 */
#define  VTSS_F_SDMMC_SDMMC_EPVR8_EPVR8_CLKGSEL(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SDMMC_SDMMC_EPVR8_EPVR8_CLKGSEL  VTSS_BIT(10)
#define  VTSS_X_SDMMC_SDMMC_EPVR8_EPVR8_CLKGSEL(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * EPVR8_SDCLKFSEL: SDCLK Frequency SelectSee SDCLKFSEL in SDMMC_CCR.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_EPVR8 . EPVR8_SDCLKFSEL
 */
#define  VTSS_F_SDMMC_SDMMC_EPVR8_EPVR8_SDCLKFSEL(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SDMMC_SDMMC_EPVR8_EPVR8_SDCLKFSEL     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SDMMC_SDMMC_EPVR8_EPVR8_SDCLKFSEL(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief SDMMC Tx Phase Tuning Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_TXPHTR
 */
#define VTSS_SDMMC_SDMMC_TXPHTR              VTSS_IOREG(VTSS_TO_SDMMC,0x9c)

/**
 * \brief
 * PH104EN: UHS-I SDR104 Tx Phase Enable
 *
 * \details
 * 0: Hardware value on "in_ph_tx_sdr104" input is applied as transmitted
 * clock phase when UHS-I SDR104 mode is selected.
 * 1: Software value PH104 is applied as transmitted clock phase when UHS-I
 * SDR104 mode is selected.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TXPHTR . PH104EN
 */
#define  VTSS_F_SDMMC_SDMMC_TXPHTR_PH104EN(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SDMMC_SDMMC_TXPHTR_PH104EN    VTSS_BIT(28)
#define  VTSS_X_SDMMC_SDMMC_TXPHTR_PH104EN(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * PH104: Selected Tx phase for UHS-I SDR104When PH104EN is 1, this field
 * selects the clock phase used to transmit command and data when UHS-I
 * SDR104 mode is selected.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_TXPHTR . PH104
 */
#define  VTSS_F_SDMMC_SDMMC_TXPHTR_PH104(x)   VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_SDMMC_SDMMC_TXPHTR_PH104      VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_SDMMC_SDMMC_TXPHTR_PH104(x)   VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * PH50EN: UHS-I SDR50 Tx Phase Enable
 *
 * \details
 * 0: Hardware value on "in_ph_tx_sdr50" input is applied as transmitted
 * clock phase when UHS-I SDR50 mode is selected.
 * 1: Software value PH50 is applied as transmitted clock phase when UHS-I
 * SDR50 mode is selected.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TXPHTR . PH50EN
 */
#define  VTSS_F_SDMMC_SDMMC_TXPHTR_PH50EN(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SDMMC_SDMMC_TXPHTR_PH50EN     VTSS_BIT(20)
#define  VTSS_X_SDMMC_SDMMC_TXPHTR_PH50EN(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * PH50: Selected Tx phase for UHS-I SDR50When PH50EN is 1, this field
 * selects the clock phase used to transmit command and data when UHS-I
 * SDR50 mode is selected.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_TXPHTR . PH50
 */
#define  VTSS_F_SDMMC_SDMMC_TXPHTR_PH50(x)    VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SDMMC_SDMMC_TXPHTR_PH50       VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SDMMC_SDMMC_TXPHTR_PH50(x)    VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * PH25EN: UHS-I SDR25 Tx Phase Enable
 *
 * \details
 * 0: Hardware value on "in_ph_tx_sdr25" input is applied as transmitted
 * clock phase when UHS-I SDR25 mode is selected.
 * 1: Software value PH25 is applied as transmitted clock phase when UHS-I
 * SDR25 mode is selected.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TXPHTR . PH25EN
 */
#define  VTSS_F_SDMMC_SDMMC_TXPHTR_PH25EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SDMMC_SDMMC_TXPHTR_PH25EN     VTSS_BIT(12)
#define  VTSS_X_SDMMC_SDMMC_TXPHTR_PH25EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * PH25: Selected Tx phase for UHS-I SDR25When PH25EN is 1, this field
 * selects the clock phase used to transmit command and data when UHS-I
 * SDR25 mode is selected.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_TXPHTR . PH25
 */
#define  VTSS_F_SDMMC_SDMMC_TXPHTR_PH25(x)    VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_SDMMC_SDMMC_TXPHTR_PH25       VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_SDMMC_SDMMC_TXPHTR_PH25(x)    VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * PHHSEN: High Speed Tx Phase Enable
 *
 * \details
 * 0: Hardware value on "in_ph_tx_hs" input is applied as transmitted clock
 * phase when high speed mode is selected.
 * 1: Software value PHHS is applied as transmitted clock phase when high
 * speed mode is selected.
 *
 * Field: ::VTSS_SDMMC_SDMMC_TXPHTR . PHHSEN
 */
#define  VTSS_F_SDMMC_SDMMC_TXPHTR_PHHSEN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDMMC_SDMMC_TXPHTR_PHHSEN     VTSS_BIT(4)
#define  VTSS_X_SDMMC_SDMMC_TXPHTR_PHHSEN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * PHHS: Selected Tx phase for High speedWhen PHHSEN is 1, this field
 * selects the clock phase used to transmit command and data when High
 * speed mode is selected.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_TXPHTR . PHHS
 */
#define  VTSS_F_SDMMC_SDMMC_TXPHTR_PHHS(x)    VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDMMC_SDMMC_TXPHTR_PHHS       VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDMMC_SDMMC_TXPHTR_PHHS(x)    VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief SDMMC Version 1 Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_VERSION1
 */
#define VTSS_SDMMC_SDMMC_VERSION1            VTSS_IOREG(VTSS_TO_SDMMC,0xba)

/**
 * \brief
 * VERSION1: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the internal version of the
 * macrocell.Note: This register displays the version number (0x28432920)
 * only if SDMMC_TMCR.CMDIDX = 'd59, SDMMC_TMCR.CMDTYP = 1,
 * SDMMC_TMCR.DPSEL = 1, and SDMMC_TMCR.RESPTYP =  1. Otherwise, it returns
 * zero value.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_VERSION1 . VERSION1
 */
#define  VTSS_F_SDMMC_SDMMC_VERSION1_VERSION1(x)  (x)
#define  VTSS_M_SDMMC_SDMMC_VERSION1_VERSION1     0xffffffff
#define  VTSS_X_SDMMC_SDMMC_VERSION1_VERSION1(x)  (x)


/**
 * \brief SDMMC Version 2 Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_VERSION2
 */
#define VTSS_SDMMC_SDMMC_VERSION2            VTSS_IOREG(VTSS_TO_SDMMC,0xbb)

/**
 * \brief
 * VERSION2: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the internal version of the
 * macrocell.Note: This register displays the version number (0x32303134)
 * only if SDMMC_TMCR.CMDIDX = 'd59, SDMMC_TMCR.CMDTYP = 1,
 * SDMMC_TMCR.DPSEL = 1, and SDMMC_TMCR.RESPTYP =  1. Otherwise, it returns
 * zero value.
 *
 * \details
 * Field: ::VTSS_SDMMC_SDMMC_VERSION2 . VERSION2
 */
#define  VTSS_F_SDMMC_SDMMC_VERSION2_VERSION2(x)  (x)
#define  VTSS_M_SDMMC_SDMMC_VERSION2_VERSION2     0xffffffff
#define  VTSS_X_SDMMC_SDMMC_VERSION2_VERSION2(x)  (x)


/**
 * \brief SDMMC Version 3 Register
 *
 * \details
 * Register: \a SDMMC:SDMMC_REG:SDMMC_VERSION3
 */
#define VTSS_SDMMC_SDMMC_VERSION3            VTSS_IOREG(VTSS_TO_SDMMC,0xbf)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the internal version of the
 * macrocell.Note: 1.The default value field holds the version number of
 * SDMMC ASIC controller (0x311).2. This register displays the version
 * number (0x2E465241) only if SDMMC_TMCR.CMDIDX = 'd59, SDMMC_TMCR.CMDTYP
 * = 1, SDMMC_TMCR.DPSEL = 1, and SDMMC_TMCR.RESPTYP =	1. Otherwise, it
 * returns a default value.
 *
 * \details
 * In case of FPGA mode, VERSION3 = 0x200
 * In case of ASIC mode, VERSION3 = 0x311
 *
 * Field: ::VTSS_SDMMC_SDMMC_VERSION3 . VERSION3
 */
#define  VTSS_F_SDMMC_SDMMC_VERSION3_VERSION3(x)  (x)
#define  VTSS_M_SDMMC_SDMMC_VERSION3_VERSION3     0xffffffff
#define  VTSS_X_SDMMC_SDMMC_VERSION3_VERSION3(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_SDMMC_H_ */
