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

#ifndef _VTSS_LAGUNA_REGS_FLEXCOM_H_
#define _VTSS_LAGUNA_REGS_FLEXCOM_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a FLEXCOM
 *
 * \see vtss_target_FLEXCOM_e
 *
 * The Flexible Serial Communication Controller (FLEXCOM) offers several
 * serial communication protocols that are managed by the three submodules:
 *
 * 1. Universal Synchronous Asynchronous Receiver Transceiver (USART)
 * 2. Serial Peripheral Interface (SPI)
 * 3. Two-wire Interface (TWI)
 *
 ***********************************************************************/

/**
 * Register Group: \a FLEXCOM:FLEXCOM_REG
 *
 * Flexible Serial Communication Unit
 */


/**
 * \brief FLEXCOM Mode Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_REG:FLEX_MR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_MR(target)         VTSS_IOREG(target,0x0)

/**
 * \brief
 * OPMODE: FLEXCOM Operating Mode
 *
 * \details
 * 0 (NO_COM): No Communication
 * 1 (USART): All UART related protocols are selected (RS232, RS485, IrDA,
 * ISO7816, LIN, LON)
 *		      SPI/TWI related registers are not accessible and have
 * no impact on IOs.
 * 2 (SPI): SPI operating mode is selected.
 *		USART/TWI related registers are not accessible and have no
 * impact on IOs.
 * 3 (TWI): All TWI related protocol are selected (TWI, SMBus).
 *		 USART/SPI related registers are not accessible and have no
 * impace on IOs.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_MR . OPMODE
 */
#define  VTSS_F_FLEXCOM_FLEX_MR_OPMODE(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_FLEXCOM_FLEX_MR_OPMODE        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_FLEXCOM_FLEX_MR_OPMODE(x)     VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief FLEXCOM Receive Holding Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_REG:FLEX_RHR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_RHR(target)        VTSS_IOREG(target,0x4)

/**
 * \brief
 * RXDATA: Receive DataThis register is a mirror of:USART Receive Holding
 * Register (FLEX_US_RHR) if FLEX_MR.OPMODE field equals 1SPI Receive Data
 * Register (FLEX_SPI_RDR) if FLEX_MR.OPMODE field equals 2TWI Transmit
 * Holding Register (FLEX_TWI_RHR) if FLEX_MR.OPMODE field equals 3
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_RHR . RXDATA
 */
#define  VTSS_F_FLEXCOM_FLEX_RHR_RXDATA(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FLEXCOM_FLEX_RHR_RXDATA       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FLEXCOM_FLEX_RHR_RXDATA(x)    VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief FLEXCOM Transmit Holding Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_REG:FLEX_THR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_THR(target)        VTSS_IOREG(target,0x8)

/**
 * \brief
 * TXDATA: Transmit DataThis register is a mirror of:USART Transmit Holding
 * Register (FLEX_US_THR) if FLEX_MR.OPMODE field equals 1SPI Transmit Data
 * Register (FLEX_SPI_TDR) if FLEX_MR.OPMODE field equals 2TWI Transmit
 * Holding Register (FLEX_TWI_THR) if FLEX_MR.OPMODE field equals 3
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_THR . TXDATA
 */
#define  VTSS_F_FLEXCOM_FLEX_THR_TXDATA(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FLEXCOM_FLEX_THR_TXDATA       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FLEXCOM_FLEX_THR_TXDATA(x)    VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief FLEXCOM Version Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_REG:FLEX_VERSION
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_VERSION(target)    VTSS_IOREG(target,0x3f)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_VERSION . MFN
 */
#define  VTSS_F_FLEXCOM_FLEX_VERSION_MFN(x)   VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_VERSION_MFN      VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_VERSION_MFN(x)   VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Hardware Module VersionReserved. Value subject to change. No
 * functionality associated. This is the internal version of the macrocell.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_VERSION . VERSION
 */
#define  VTSS_F_FLEXCOM_FLEX_VERSION_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_FLEXCOM_FLEX_VERSION_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_FLEXCOM_FLEX_VERSION_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * Register Group: \a FLEXCOM:FLEXCOM_USART_REG
 *
 * USART Register Group
 */


/**
 * \brief USART Control Register
 *
 * \details
 * This register can only be written if the WPCREN bit is cleared in the
 * USART Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_CR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_CR(target)      VTSS_IOREG(target,0x80)

/**
 * \brief
 * FIFODIS: FIFO Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the Transmit and Receive FIFOs.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . FIFODIS
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_FIFODIS(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_FIFODIS    VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_FIFODIS(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * FIFOEN: FIFO Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the Transmit and Receive FIFOs.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . FIFOEN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_FIFOEN(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_FIFOEN     VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_FIFOEN(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * USART_REQCLR: Request to Clear the Comparison Trigger
 *
 * \details
 * SleepWalking enabled:
 * 0: No effect.
 * 1: Clears the potential clock request currently issued by USART, thus
 * the potential system wakeup is cancelled.
 *
 * SleepWalking disabled:
 * 0: No effect.
 * 1: Restarts the comparison trigger to enable FLEX_US_RHR loading.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . USART_REQCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_USART_REQCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_USART_REQCLR  VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_USART_REQCLR(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * TXFLCLR: Transmit FIFO Lock CLEAR
 *
 * \details
 * 0: No effect.
 * 1: Clears the Transmit FIFO Lock
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . TXFLCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_TXFLCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_TXFLCLR    VTSS_BIT(26)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_TXFLCLR(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * RXFCLR: Receive FIFO Clear
 *
 * \details
 * 0: No effect.
 * 1: Empties the Receive FIFO.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RXFCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RXFCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RXFCLR     VTSS_BIT(25)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RXFCLR(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * TXFCLR: Transmit FIFO Clear
 *
 * \details
 * 0: No effect.
 * 1: Empties the Transmit FIFO.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . TXFCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_TXFCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_TXFCLR     VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_TXFCLR(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * LINWKUP: Send LIN Wakeup Signal
 *
 * \details
 * 0: No effect
 * 1: Sends a wakeup signal on the LIN bus.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . LINWKUP
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_LINWKUP(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_LINWKUP    VTSS_BIT(21)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_LINWKUP(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * LINABT: Abort LIN Transmission
 *
 * \details
 * 0: No effect.
 * 1: Aborts the current LIN transmission.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . LINABT
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_LINABT(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_LINABT     VTSS_BIT(20)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_LINABT(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * RTSDIS: Request to Send Disable
 *
 * \details
 * 0: No effect.
 * 1: Drives the RTS pin to 0 if FLEX_US_MR.USART_MODE field = 2, else
 * drives the RTS pin to 1 if
 * FLEX_US_MR.USART_MODE field = 0.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RTSDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RTSDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RTSDIS     VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RTSDIS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * RTSEN: Request to Send Enable
 *
 * \details
 * 0: No effect.
 * 1: Drives the RTS pin to 1 if FLEX_US_MR.USART_MODE field = 2, else
 * drives the RTS pin to 0 if
 * FLEX_US_MR.USART_MODE field = 0.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RTSEN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RTSEN(x)   VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RTSEN      VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RTSEN(x)   VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * DTRDIS: Data Terminal Ready Disable
 *
 * \details
 * 0: No effect.
 * 1: Drives the DTR pin to 1.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . DTRDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_DTRDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_DTRDIS     VTSS_BIT(17)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_DTRDIS(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * DTREN: Data Terminal Ready Enable
 *
 * \details
 * 0: No effect.
 * 1: Drives the DTR pin to 0.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . DTREN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_DTREN(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_DTREN      VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_DTREN(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * RETTO: Start Timeout Immediately
 *
 * \details
 * 0: No effect
 * 1: Immediately restarts timeout period.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RETTO
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RETTO(x)   VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RETTO      VTSS_BIT(15)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RETTO(x)   VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * RSTNACK: Reset Non Acknowledge
 *
 * \details
 * 0: No effect
 * 1: Resets FLEX_US_CSR.NACK.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RSTNACK
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RSTNACK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RSTNACK    VTSS_BIT(14)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RSTNACK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * RSTIT: Reset Iterations
 *
 * \details
 * 0: No effect.
 * 1: Resets FLEX_US_CSR.ITER. No effect if the ISO7816 is not enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RSTIT
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RSTIT(x)   VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RSTIT      VTSS_BIT(13)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RSTIT(x)   VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * SENDA: Send Address
 *
 * \details
 * 0: No effect.
 * 1: In Multidrop mode only, the next character written to FLEX_US_THR is
 * sent with the address bit set.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . SENDA
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_SENDA(x)   VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_SENDA      VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_SENDA(x)   VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * STTTO: Clear TIMEOUT Flag and Start Timeout After Next Character
 * Received
 *
 * \details
 * 0: No effect.
 * 1: Starts waiting for a character before clocking the timeout counter.
 * Immediately disables a timeout period in progress.
 * Resets the FLEX_US_CSR.TIMEOUT status bit.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . STTTO
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_STTTO(x)   VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_STTTO      VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_STTTO(x)   VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * STPBRK: Stop Break
 *
 * \details
 * 0: No effect.
 * 1: Stops transmission of the break after a minimum of one character
 * length and transmits a high level during 12-bit periods.
 * No effect if no break is being transmitted.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . STPBRK
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_STPBRK(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_STPBRK     VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_STPBRK(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * STTBRK: Start Break
 *
 * \details
 * 0: No effect.
 * 1: Starts transmission of a break after the characters present in
 * FLEX_US_THR and the Transmit Shift Register have been
 * transmitted. No effect if a break is already being transmitted.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . STTBRK
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_STTBRK(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_STTBRK     VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_STTBRK(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * RSTSTA: Reset Status Bits
 *
 * \details
 * 0: No effect.
 * 1: Resets the status bits PARE, FRAME, OVRE, MANE, LINBE, LINISFE,
 * LINIPE, LINCE, LINSNRE, LINSTE, LINHTE,
 * LINID, LINTC, LINBK, CMP and RXBRK in FLEX_US_CSR. Also resets the
 * status bits TXFEF, TXFFF, TXFTHF, RXFEF,
 * RXFFF, RXFTHF, TXFPTEF, RXFPTEF in FLEX_US_FESR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RSTSTA
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RSTSTA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RSTSTA     VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RSTSTA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * TXDIS: Transmitter Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the transmitter.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . TXDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_TXDIS(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_TXDIS      VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_TXDIS(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXEN: Transmitter Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the transmitter if TXDIS is 0.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . TXEN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_TXEN(x)    VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_TXEN       VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_TXEN(x)    VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXDIS: Receiver Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the receiver.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RXDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RXDIS(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RXDIS      VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RXDIS(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXEN: Receiver Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the receiver, if RXDIS is 0.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RXEN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RXEN(x)    VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RXEN       VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RXEN(x)    VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RSTTX: Reset Transmitter
 *
 * \details
 * 0: No effect.
 * 1: Resets the transmitter.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RSTTX
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RSTTX(x)   VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RSTTX      VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RSTTX(x)   VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RSTRX: Reset Receiver
 *
 * \details
 * 0: No effect.
 * 1: Resets the receiver.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CR . RSTRX
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CR_RSTRX(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CR_RSTRX      VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_CR_RSTRX(x)   VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief USART Mode Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * USART Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_MR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_MR(target)      VTSS_IOREG(target,0x81)

/**
 * \brief
 * ONEBIT: Start Frame Delimiter Selector
 *
 * \details
 * 0: Start frame delimiter is COMMAND or DATA SYNC.
 * 1: Start frame delimiter is one bit.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . ONEBIT
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_ONEBIT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_ONEBIT     VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_ONEBIT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * MODSYNC: Manchester Synchronization Mode
 *
 * \details
 * 0: The Manchester start bit is a 0 to 1 transition
 * 1: The Manchester start bit is a 1 to 0 transition.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . MODSYNC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_MODSYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_MODSYNC    VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_MODSYNC(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MAN: Manchester Encoder/Decoder Enable
 *
 * \details
 * 0: Manchester encoder/decoder are disabled.
 * 1: Manchester encoder/decoder are enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . MAN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_MAN(x)     VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_MAN        VTSS_BIT(29)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_MAN(x)     VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * FILTER: Receive Line Filter
 *
 * \details
 * 0: The USART does not filter the receive line.
 * 1: The USART filters the receive line using a three-sample filter
 * (1/16-bit clock) (2 over 3 majority).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . FILTER
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_FILTER(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_FILTER     VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_FILTER(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * 0-7: Defines the maximum number of iterations in mode ISO7816, protocol
 * T = 0.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . MAX_ITERATION
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_MAX_ITERATION(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_MAX_ITERATION     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_MAX_ITERATION(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/**
 * \brief
 * INVDATA: Inverted Data
 *
 * \details
 * 0: The data field transmitted on TXD line is the same as the one written
 * in FLEX_US_THR or the content read in
 * FLEX_US_RHR is the same as RXD line. Normal mode of operation.
 * 1: The data field transmitted on TXD line is inverted (voltage polarity
 * only) compared to the value written in FLEX_US_THR
 * or the content read in FLEX_US_RHR is inverted compared to what is
 * received on RXD line (or ISO7816 IO line). Inverted
 * mode of operation, useful for contactless card application. To be used
 * with configuration bit MSBF.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . INVDATA
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_INVDATA(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_INVDATA    VTSS_BIT(23)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_INVDATA(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * VAR_SYNC: Variable Synchronization of Command/Data Sync Start Frame
 * Delimiter
 *
 * \details
 * 0: User defined configuration of command or data sync field depending on
 * MODSYNC value.
 * 1: The sync field is updated when a character is written into
 * FLEX_US_THR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . VAR_SYNC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_VAR_SYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_VAR_SYNC   VTSS_BIT(22)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_VAR_SYNC(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * DSNACK: Disable Successive NACK
 *
 * \details
 * 0: NACK is sent on the ISO line as soon as a parity error occurs in the
 * received character (unless INACK is set).
 * 1: Successive parity errors are counted up to the value specified in the
 * MAX_ITERATION field. These parity errors generate
 * a NACK on the ISO line. As soon as this value is reached, no additional
 * NACK is sent on the ISO line. The flag ITER is
 * asserted.
 * Note: The MAX_ITERATION field must be cleared if DSNACK is cleared.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . DSNACK
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_DSNACK(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_DSNACK     VTSS_BIT(21)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_DSNACK(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * INACK: Inhibit Non Acknowledge
 *
 * \details
 * 0: The NACK is generated.
 * 1: The NACK is not generated.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . INACK
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_INACK(x)   VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_INACK      VTSS_BIT(20)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_INACK(x)   VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * OVER: Oversampling Mode
 *
 * \details
 * 0: 16x Oversampling.
 * 1: 8x Oversampling.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . OVER
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_OVER(x)    VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_OVER       VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_OVER(x)    VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * CLKO: Clock Output Select
 *
 * \details
 * 0: The USART does not drive the SCK pin (Synchronous Target mode or
 * Asynchronous mode with external baud rate clock source).
 * 1: The USART drives the SCK pin if USCLKS does not select the external
 * clock SCK (USART Synchronous Initiator mode).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . CLKO
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_CLKO(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_CLKO       VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_CLKO(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MODE9: 9-bit Character Length
 *
 * \details
 * 0: CHRL defines character length.
 * 1: 9-bit character length.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . MODE9
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_MODE9(x)   VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_MODE9      VTSS_BIT(17)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_MODE9(x)   VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * MSBF: Bit Order
 *
 * \details
 * 0: Least significant bit is sent/received first.
 * 1: Most significant bit is sent/received first.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . MSBF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_MSBF(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_MSBF       VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_MSBF(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * CHMODE: Channel Mode
 *
 * \details
 * 0 (NORMAL): Normal mode
 * 1 (AUTOMATIC): Automatic Echo. Receiver input is connected to the TXD
 * pin.
 * 2 (LOCAL_LOOPBACK): Local Loopback. Transmitter output is connected to
 * the Receiver Input.
 * 3 (REMOTE_LOOPBACK): Remote Loopback. RXD pin is internally connected to
 * the TXD pin.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . CHMODE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_CHMODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_CHMODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_CHMODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * NBSTOP: Number of Stop Bits
 *
 * \details
 * 0 (1_BIT): 1 stop bit
 * 1 (1_5_BIT): 1.5 stop bit (SYNC = 0) or reserved (SYNC = 1)
 * 2 (2_BIT): 2 stop bits
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . NBSTOP
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_NBSTOP(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_NBSTOP     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_NBSTOP(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * PAR: Parity Type
 *
 * \details
 * 0 (EVEN): Even parity
 * 1 (ODD): Odd parity
 * 2 (SPACE): Parity forced to 0 (Space)
 * 3 (MARK): Parity forced to 1 (Mark)
 * 4 (NO): No parity
 * 6 (MULTIDROP): Multidrop mode
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . PAR
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_PAR(x)     VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_PAR        VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_PAR(x)     VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * SYNC: Synchronous Mode Select
 *
 * \details
 * 0: USART operates in Asynchronous mode (UART).
 * 1: USART operates in Synchronous mode.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . SYNC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_SYNC(x)    VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_SYNC       VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_SYNC(x)    VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * CHRL: Character Length
 *
 * \details
 * 0 (5_BIT): Character length is 5 bits
 * 1 (6_BIT): Character length is 6 bits
 * 2 (7_BIT): Character length is 7 bits
 * 3 (8_BIT); Character length is 8 bits
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . CHRL
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_CHRL(x)    VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_CHRL       VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_CHRL(x)    VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * USCLKS: Clock Selection
 *
 * \details
 * 0 (MCK): Peripheral clock is selected
 * 1 (DIV): Peripheral clock divided (DIV = xx) is selected
 * 2 (GCLKPMC_PCK): PMC generic programmable clock is selected. If the SCK
 * pin is driven (CLKO = 1), the CD field must be greater than 1.
 * 3 (SCK): External pin SCK is selected
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . USCLKS
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_USCLKS(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_USCLKS     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_USCLKS(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * USART_MODE: USART Mode of Operation
 *
 * \details
 * 0x0 (NORMAL): Normal mode
 * 0x1 (RS485): RS485
 * 0x2 (HW_HANDSHAKING): Hardware handshaking
 * 0x3 (MODEM); Modem
 * 0x4 (IS07816_T_0): IS07816 Protocol: T = 0
 * 0x6 (IS07816_T_1): IS07816 Protocol: T = 1
 * 0x8 (IRDA): IrDA
 * 0x9 (LON): LON
 * 0xA (LIN_INITIATOR): LIN Initiator mode
 * 0xB (LIN_TARGET): LIN Target mode
 * 0xC (DATA16BIT_INITIATOR): 16-bit data initiator
 * 0xD (DATA16BIT_TARGET): 16-bit data target
 * 0xE (SPI_INITIATOR): SPI Initiator mode (CLKO must be written to 1 and
 * USCLKS = 0, 1 or 2)
 * 0xF (SPI_TARGET): SPI Target mode
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MR . USART_MODE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MR_USART_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_FLEXCOM_FLEX_US_MR_USART_MODE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_FLEXCOM_FLEX_US_MR_USART_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief USART Interrupt Enable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * USART Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_IER
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_IER(target)     VTSS_IOREG(target,0x82)

/**
 * \brief
 * MANE_IE: Manchester Error Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . MANE_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_MANE_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_MANE_IE   VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_MANE_IE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CMP_IE: Comparison Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . CMP_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_CMP_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_CMP_IE    VTSS_BIT(22)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_CMP_IE(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * CTSIC_IE: Clear to Send Input Change Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . CTSIC_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_CTSIC_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_CTSIC_IE  VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_CTSIC_IE(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * DCDIC_IE: Data Carrier Detect Input Change Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . DCDIC_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_DCDIC_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_DCDIC_IE  VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_DCDIC_IE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * DSRIC_IE: Data Set Ready Input Change Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . DSRIC_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_DSRIC_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_DSRIC_IE  VTSS_BIT(17)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_DSRIC_IE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * RIIC_IE: Ring Indicator Input Change Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . RIIC_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_RIIC_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_RIIC_IE   VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_RIIC_IE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * NACK_IE: Non Acknowledge Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . NACK_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_NACK_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_NACK_IE   VTSS_BIT(13)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_NACK_IE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * RXBUFF_IE: Buffer Full Interrupt Enable (available in all USART modes of
 * operation)
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . RXBUFF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_RXBUFF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_RXBUFF_IE  VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_RXBUFF_IE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * TXBUFE_IE: Buffer Empty Interrupt Enable (available in all USART modes
 * of operation)
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . TXBUFE_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_TXBUFE_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_TXBUFE_IE  VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_TXBUFE_IE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * ITER_IE: Max number of Repetitions Reached Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . ITER_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_ITER_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_ITER_IE   VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_ITER_IE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TXEMPTY_IE: TXEMPTY Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . TXEMPTY_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_TXEMPTY_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_TXEMPTY_IE  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_TXEMPTY_IE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * TIMEOUT_IE: Timeout Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . TIMEOUT_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_TIMEOUT_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_TIMEOUT_IE  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_TIMEOUT_IE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * PARE_IE: Parity Error Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . PARE_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_PARE_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_PARE_IE   VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_PARE_IE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * FRAME_IE: Framing Error Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . FRAME_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_FRAME_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_FRAME_IE  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_FRAME_IE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * OVRE_IE: Overrun Error Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . OVRE_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_OVRE_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_OVRE_IE   VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_OVRE_IE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * ENDTX_IE: End of Transmit Interrupt Enable (available in all USART modes
 * of operation)
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . ENDTX_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_ENDTX_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_ENDTX_IE  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_ENDTX_IE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * ENDRX_IE: End of Receive Transfer Interrupt Enable (available in all
 * USART modes of operation)
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . ENDRX_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_ENDRX_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_ENDRX_IE  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_ENDRX_IE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RXBRK_IE: Receiver Break Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . RXBRK_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_RXBRK_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_RXBRK_IE  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_RXBRK_IE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXRDY_IE: TXRDY Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . TXRDY_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_TXRDY_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_TXRDY_IE  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_TXRDY_IE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RXRDY_IE: RXRDY Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IER . RXRDY_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IER_RXRDY_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IER_RXRDY_IE  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_IER_RXRDY_IE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART Interrupt Disable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * USART Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_IDR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_IDR(target)     VTSS_IOREG(target,0x83)

/**
 * \brief
 * MANE_ID: Manchester Error Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . MANE_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_MANE_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_MANE_ID   VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_MANE_ID(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CMP_ID: Comparison Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . CMP_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_CMP_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_CMP_ID    VTSS_BIT(22)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_CMP_ID(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * CTSIC_ID: Clear to Send Input Change Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . CTSIC_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_CTSIC_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_CTSIC_ID  VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_CTSIC_ID(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * DCDIC_ID: Data Carrier Detect Input Change Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . DCDIC_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_DCDIC_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_DCDIC_ID  VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_DCDIC_ID(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * DSRIC_ID: Data Set Ready Input Change Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . DSRIC_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_DSRIC_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_DSRIC_ID  VTSS_BIT(17)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_DSRIC_ID(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * RIIC_ID: Ring Indicator Input Change Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . RIIC_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_RIIC_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_RIIC_ID   VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_RIIC_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * NACK_ID: Non Acknowledge Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . NACK_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_NACK_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_NACK_ID   VTSS_BIT(13)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_NACK_ID(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * RXBUFF_ID: Buffer Full Interrupt Disable (available in all USART modes
 * of operation)
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . RXBUFF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_RXBUFF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_RXBUFF_ID  VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_RXBUFF_ID(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * TXBUFE_ID: Buffer Empty Interrupt Disable (available in all USART modes
 * of operation)
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . TXBUFE_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_TXBUFE_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_TXBUFE_ID  VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_TXBUFE_ID(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * ITER_ID: Max number of Repetitions Reached Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . ITER_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_ITER_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_ITER_ID   VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_ITER_ID(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TXEMPTY_ID: TXEMPTY Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . TXEMPTY_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_TXEMPTY_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_TXEMPTY_ID  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_TXEMPTY_ID(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * TIMEOUT_ID: Timeout Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . TIMEOUT_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_TIMEOUT_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_TIMEOUT_ID  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_TIMEOUT_ID(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * PARE_ID: Parity Error Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . PARE_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_PARE_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_PARE_ID   VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_PARE_ID(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * FRAME_ID: Framing Error Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . FRAME_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_FRAME_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_FRAME_ID  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_FRAME_ID(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * OVRE_ID: Overrun Error Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . OVRE_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_OVRE_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_OVRE_ID   VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_OVRE_ID(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * ENDTX_ID: End of Transmit Interrupt Disable (available in all USART
 * modes of operation)
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . ENDTX_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_ENDTX_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_ENDTX_ID  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_ENDTX_ID(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * ENDRX_ID: End of Receive Transfer Interrupt Disable (available in all
 * USART modes of operation)
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . ENDRX_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_ENDRX_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_ENDRX_ID  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_ENDRX_ID(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RXBRK_ID: Receiver Break Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . RXBRK_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_RXBRK_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_RXBRK_ID  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_RXBRK_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXRDY_ID: TXRDY Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . TXRDY_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_TXRDY_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_TXRDY_ID  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_TXRDY_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RXRDY_ID: RXRDY Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IDR . RXRDY_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IDR_RXRDY_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IDR_RXRDY_ID  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_IDR_RXRDY_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART Interrupt Mask Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * USART Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_IMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_IMR(target)     VTSS_IOREG(target,0x84)

/**
 * \brief
 * MANE_IM: Manchester Error Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . MANE_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_MANE_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_MANE_IM   VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_MANE_IM(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CMP_IM: Comparison Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . CMP_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_CMP_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_CMP_IM    VTSS_BIT(22)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_CMP_IM(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * CTSIC_IM: Clear to Send Input Change Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . CTSIC_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_CTSIC_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_CTSIC_IM  VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_CTSIC_IM(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * DCDIC_IM: Data Carrier Detect Input Change Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . DCDIC_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_DCDIC_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_DCDIC_IM  VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_DCDIC_IM(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * DSRIC_IM: Data Set Ready Input Change Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . DSRIC_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_DSRIC_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_DSRIC_IM  VTSS_BIT(17)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_DSRIC_IM(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * RIIC_IM: Ring Indicator Input Change Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . RIIC_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_RIIC_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_RIIC_IM   VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_RIIC_IM(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * NACK_IM: Non Acknowledge Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . NACK_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_NACK_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_NACK_IM   VTSS_BIT(13)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_NACK_IM(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * RXBUFF_IM: Buffer Full Interrupt Mask (available in all USART modes of
 * operation)
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . RXBUFF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_RXBUFF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_RXBUFF_IM  VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_RXBUFF_IM(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * TXBUFE_IM: Buffer Empty Interrupt Mask (available in all USART modes of
 * operation)
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . TXBUFE_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_TXBUFE_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_TXBUFE_IM  VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_TXBUFE_IM(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * ITER_IM: Max number of Repetitions Reached Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . ITER_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_ITER_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_ITER_IM   VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_ITER_IM(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TXEMPTY_IM: TXEMPTY Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . TXEMPTY_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_TXEMPTY_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_TXEMPTY_IM  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_TXEMPTY_IM(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * TIMEOUT_IM: Timeout Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . TIMEOUT_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_TIMEOUT_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_TIMEOUT_IM  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_TIMEOUT_IM(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * PARE_IM: Parity Error Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . PARE_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_PARE_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_PARE_IM   VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_PARE_IM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * FRAME_IM: Framing Error Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . FRAME_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_FRAME_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_FRAME_IM  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_FRAME_IM(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * OVRE_IM: Overrun Error Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . OVRE_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_OVRE_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_OVRE_IM   VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_OVRE_IM(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * ENDTX_IM: End of Transmit Interrupt Mask (available in all USART modes
 * of operation)
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . ENDTX_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_ENDTX_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_ENDTX_IM  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_ENDTX_IM(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * ENDRX_IM: End of Receive Transfer Interrupt Mask (available in all USART
 * modes of operation)
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . ENDRX_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_ENDRX_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_ENDRX_IM  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_ENDRX_IM(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RXBRK_IM: Receiver Break Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . RXBRK_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_RXBRK_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_RXBRK_IM  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_RXBRK_IM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXRDY_IM: TXRDY Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . TXRDY_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_TXRDY_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_TXRDY_IM  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_TXRDY_IM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RXRDY_IM: RXRDY Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_IMR . RXRDY_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_IMR_RXRDY_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_IMR_RXRDY_IM  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_IMR_RXRDY_IM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART Channel Status Register
 *
 * \details
 * Note: If enabled in the SFR module (default is disabled), a debugger
 * read access does not clear the flag CTSIC.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_CSR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_CSR(target)     VTSS_IOREG(target,0x85)

/**
 * \brief
 * MANE: Manchester Error
 *
 * \details
 * 0: No Manchester error has been detected since the last RSTSTA command
 * was issued.
 * 1: At least one Manchester error has been detected since the last RSTSTA
 * command was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . MANE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_MANE(x)   VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_MANE      VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_MANE(x)   VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CTS: Image of CTS Input
 *
 * \details
 * 0: CTS input is driven low.
 * 1: CTS input is driven high.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . CTS
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_CTS(x)    VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_CTS       VTSS_BIT(23)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_CTS(x)    VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * CMP: Comparison Status
 *
 * \details
 * 0: No received character matched the comparison criteria programmed in
 * VAL1, VAL2 fields and CMPPAR bit in since the
 * last RSTSTA command was issued.
 * 1: A received character matched the comparison criteria since the last
 * RSTSTA command was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . CMP
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_CMP(x)    VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_CMP       VTSS_BIT(22)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_CMP(x)    VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * CTSIC: Clear to Send Input Change Flag
 *
 * \details
 * 0: No input change has been detected on the CTS pin since the last read
 * of FLEX_US_CSR.
 * 1: At least one input change has been detected on the CTS pin since the
 * last read of FLEX_US_CSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . CTSIC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_CTSIC(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_CTSIC     VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_CTSIC(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * DCDIC: Data Carrier Detect Input Change Flag
 *
 * \details
 * 0: No input change has been detected on the DCD pin since the last read
 * of FLEX_US_CSR.
 * 1: At least one input change has been detected on the DCD pin since the
 * last read of FLEX_US_CSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . DCDIC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_DCDIC(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_DCDIC     VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_DCDIC(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * DSRIC: Data Set Ready Input Change Flag
 *
 * \details
 * 0: No input change has been detected on the DSR pin since the last read
 * of FLEX_US_CSR.
 * 1: At least one input change has been detected on the DSR pin since the
 * last read of FLEX_US_CSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . DSRIC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_DSRIC(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_DSRIC     VTSS_BIT(17)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_DSRIC(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * RIIC: Ring Indicator Input Change Flag
 *
 * \details
 * 0: No input change has been detected on the RI pin since the last read
 * of FLEX_US_CSR.
 * 1: At least one input change has been detected on the RI pin since the
 * last read of FLEX_US_CSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . RIIC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_RIIC(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_RIIC      VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_RIIC(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * NACK: Non Acknowledge Interrupt
 *
 * \details
 * 0: Non acknowledge has not been detected since the last RSTNACK.
 * 1: At least one non acknowledge has been detected since the last
 * RSTNACK.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . NACK
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_NACK(x)   VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_NACK      VTSS_BIT(13)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_NACK(x)   VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * RXBUFF: RX Buffer Full (cleared by writing FLEX_US_RCR or FLEX_US_RNCR)
 *
 * \details
 * 0: FLEX_US_RCR or FLEX_US_RNCR has a value other than 0.
 * 1: Both FLEX_US_RCR and FLEX_US_RNCR have a value of 0.
 * Note: FLEX_US_RCR and FLEX_US_RNCR are PDC registers.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . RXBUFF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_RXBUFF(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_RXBUFF    VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_RXBUFF(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * TXBUFE: TX Buffer Empty (cleared by writing FLEX_US_TCR or FLEX_US_TNCR)
 *
 * \details
 * 0: FLEX_US_TCR or FLEX_US_TNCR has a value other than 0.
 * 1: Both FLEX_US_TCR and FLEX_US_TNCR have a value of 0.
 * Note: FLEX_US_RCR and FLEX_US_RNCR are PDC registers.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . TXBUFE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_TXBUFE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_TXBUFE    VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_TXBUFE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * ITER: Max number of Repetitions Reached
 *
 * \details
 * 0: Maximum number of repetitions has not been reached since the last
 * RSTIT command was issued.
 * 1: Maximum number of repetitions has been reached since the last RSTIT
 * command was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . ITER
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_ITER(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_ITER      VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_ITER(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TXEMPTY: Transmitter Empty (cleared by writing FLEX_US_THR)
 *
 * \details
 * 0: There are characters in either FLEX_US_THR or the Transmit Shift
 * Register, or the transmitter is disabled.
 * 1: There are no characters in FLEX_US_THR, nor in the Transmit Shift
 * Register.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . TXEMPTY
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_TXEMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_TXEMPTY   VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_TXEMPTY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * TIMEOUT: Receiver Timeout
 *
 * \details
 * 0: There has not been a timeout since the last Start Timeout command
 * (FLEX_US_CR.STTTO) or the Timeout Register is 0.
 * 1: There has been a timeout since the last Start Timeout command
 * (FLEX_US_CR.STTTO).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . TIMEOUT
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_TIMEOUT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_TIMEOUT   VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_TIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * PARE: Parity Error
 *
 * \details
 * 0: No parity error has been detected since the last RSTSTA command was
 * issued.
 * 1: At least one parity error has been detected since the last RSTSTA
 * command was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . PARE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_PARE(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_PARE      VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_PARE(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * FRAME: Framing Error
 *
 * \details
 * 0: No parity error has been detected since the last RSTSTA command was
 * issued.
 * 1: At least one parity error has been detected since the last RSTSTA
 * command was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . FRAME
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_FRAME(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_FRAME     VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_FRAME(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * OVRE: Overrun Error
 *
 * \details
 * 0: No overrun error has occurred since the last RSTSTA command was
 * issued.
 * 1: At least one overrun error has occurred since the last RSTSTA command
 * was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . OVRE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_OVRE(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_OVRE      VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_OVRE(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * ENDTX: End of TX Buffer (cleared by writing FLEX_US_TCR or FLEX_US_TNCR)
 *
 * \details
 * 0: The Transmit Counter Register has not reached 0 since the last write
 * in FLEX_US_TCR or FLEX_US_TNCR.
 * 1: The Transmit Counter Register has reached 0 since the last write in
 * FLEX_US_TCR or FLEX_US_TNCR.
 * Note: FLEX_US_RCR and FLEX_US_RNCR are PDC registers.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . ENDTX
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_ENDTX(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_ENDTX     VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_ENDTX(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * ENDRX: End of RX Buffer (cleared by writing FLEX_US_RCR or FLEX_US_RNCR)
 *
 * \details
 * 0: The Receive Counter Register has not reached 0 since the last write
 * in FLEX_US_RCR or FLEX_US_RNCR.
 * 1: The Receive Counter Register has not reached 0 since the last write
 * in FLEX_US_RCR or FLEX_US_RNCR.
 * Note: FLEX_US_RCR and FLEX_US_RNCR are PDC registers.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . ENDRX
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_ENDRX(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_ENDRX     VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_ENDRX(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RXBRK: Break Received/End of Break
 *
 * \details
 * 0: No break received or end of break detected since the last RSTSTA
 * command was issued.
 * 1: Break received or end of break detected since the last RSTSTA command
 * was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . RXBRK
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_RXBRK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_RXBRK     VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_RXBRK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXRDY: Transmitter Ready (cleared by writing FLEX_US_THR)
 *
 * \details
 * When FIFOs are disabled:
 * 0: A character in FLEX_US_THR is waiting to be transferred to the
 * Transmit Shift Register, or an STTBRK command has
 * been requested, or the transmitter is disabled. As soon as the
 * transmitter is enabled, TXRDY becomes 1.
 * 1: There is no character in FLEX_US_THR.
 *
 * When FIFOs are enabled:
 * 0: Transmit FIFO is full and cannot accept more data
 * 1: Transmit FIFO is not full; one or more data can be written according
 * to TXRDYM field configuration
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . TXRDY
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_TXRDY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_TXRDY     VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_TXRDY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RXRDY: Receiver Ready (cleared by reading FLEX_US_RHR)
 *
 * \details
 * When FIFOs are disabled:
 * 0: No complete character has been received since the last read of
 * FLEX_US_RHR or the receiver is disabled. If characters
 * were received when the receiver was disabled, RXRDY changes to 1 when
 * the receiver is enabled.
 * 1: At least one complete character has been received and FLEX_US_RHR has
 * not yet been read.
 *
 * When FIFOs are enabled:
 * 0: Receive FIFO is empty; no data to read
 * 1: At least one unread data is in the Receive FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CSR . RXRDY
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CSR_RXRDY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CSR_RXRDY     VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_CSR_RXRDY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART Receive Holding Register
 *
 * \details
 * Note: If FIFO is enabled (FLEX_US_CR.FIFOEN bit) and FLEX_US_FMR.RXRDYM
 * = 0, the Receive FIFO operates in Single Data mode.

 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_RHR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_RHR(target)     VTSS_IOREG(target,0x86)

/**
 * \brief
 * RXSYNH: Received Sync
 *
 * \details
 * 0: Last character received is a data.
 * 1: Last character received is a command.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_RHR . RXSYNH
 */
#define  VTSS_F_FLEXCOM_FLEX_US_RHR_RXSYNH(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_FLEXCOM_FLEX_US_RHR_RXSYNH    VTSS_BIT(15)
#define  VTSS_X_FLEXCOM_FLEX_US_RHR_RXSYNH(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * RXCHR: Received CharacterLast character received if RXRDY is set.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_RHR . RXCHR
 */
#define  VTSS_F_FLEXCOM_FLEX_US_RHR_RXCHR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_US_RHR_RXCHR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_US_RHR_RXCHR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief USART Receive Holding Register (FIFO Multi Data)
 *
 * \details
 * Note: If FIFO is enabled (FLEX_US_CR.FIFOEN bit) and FLEX_US_FMR.TXRDYM
 * > 0, the Transmit FIFO operates in Multi Data mode.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_FMT_RHR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_FMT_RHR(target)  VTSS_IOREG(target,0x86)

/**
 * \brief
 * RXCHR3: Received CharacterFirst unread character in the Receive FIFO if
 * RXRDY is set.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMT_RHR . RXCHR3
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMT_RHR_RXCHR3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_US_FMT_RHR_RXCHR3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_US_FMT_RHR_RXCHR3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * RXCHR2: Received CharacterFirst unread character in the Receive FIFO if
 * RXRDY is set.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMT_RHR . RXCHR2
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMT_RHR_RXCHR2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_US_FMT_RHR_RXCHR2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_US_FMT_RHR_RXCHR2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RXCHR1 Received CharacterFirst unread character in the Receive FIFO if
 * RXRDY is set.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMT_RHR . RXCHR1
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMT_RHR_RXCHR1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_US_FMT_RHR_RXCHR1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_US_FMT_RHR_RXCHR1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * RXCHR0: Received CharacterFirst unread character in the Receive FIFO if
 * RXRDY is set.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMT_RHR . RXCHR0
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMT_RHR_RXCHR0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_US_FMT_RHR_RXCHR0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_US_FMT_RHR_RXCHR0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief USART Transmit Holding Register
 *
 * \details
 * Note: If FIFO is enabled (FLEX_US_CR.FIFOEN bit) and FLEX_US_FMR.TXRDYM
 * = 0, the Transmit FIFO operates in Single Data mode.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_THR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_THR(target)     VTSS_IOREG(target,0x87)

/**
 * \brief
 * TXSYNC: Sync Field to be Transmitted.
 *
 * \details
 * 0: The next character sent is encoded as a data. Start frame delimiter
 * is DATA SYNC.
 * 1: The next character sent is encoded as a command. Start frame
 * delimiter is COMMAND SYNC.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_THR . TXSYNH
 */
#define  VTSS_F_FLEXCOM_FLEX_US_THR_TXSYNH(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_FLEXCOM_FLEX_US_THR_TXSYNH    VTSS_BIT(15)
#define  VTSS_X_FLEXCOM_FLEX_US_THR_TXSYNH(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * TXCHR: Character to be TransmittedNext character to be transmitted after
 * the current character if TXRDY is not set.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_THR . TXCHR
 */
#define  VTSS_F_FLEXCOM_FLEX_US_THR_TXCHR(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_FLEXCOM_FLEX_US_THR_TXCHR     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_FLEXCOM_FLEX_US_THR_TXCHR(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief USART Transmit Holding Register (FIFO Multi Data)
 *
 * \details
 * Note: If FIFO is enabled (FLEX_US_CR.FIFOEN bit) and FLEX_US_FMR.TXRDYM
 * > 0, the Transmit FIFO operates in Multi Data mode.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_FMT_THR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_FMT_THR(target)  VTSS_IOREG(target,0x87)

/**
 * \brief
 * TXCHR3 Character to be TransmittedNext character to be transmitted.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMT_THR . TXCHR3
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMT_THR_TXCHR3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_US_FMT_THR_TXCHR3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_US_FMT_THR_TXCHR3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * TXCHR2: Character to be TransmittedNext character to be transmitted
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMT_THR . TXCHR2
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMT_THR_TXCHR2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_US_FMT_THR_TXCHR2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_US_FMT_THR_TXCHR2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * TXCHR1: Character to be TransmittedNext character to be transmitted.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMT_THR . TXCHR1
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMT_THR_TXCHR1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_US_FMT_THR_TXCHR1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_US_FMT_THR_TXCHR1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TXCHR0: Character to be TransmittedNext character to be transmitted
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMT_THR . TXCHR0
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMT_THR_TXCHR0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_US_FMT_THR_TXCHR0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_US_FMT_THR_TXCHR0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief USART Baud Rate Generator Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * USART Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_BRGR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_BRGR(target)    VTSS_IOREG(target,0x88)

/**
 * \brief
 * FP: Fractional Part
 *
 * \details
 * 0: Fractional divider is disabled.
 * 1 - 7: Baud rate resolution, defined by FP x 1/8.
 *
 * Warning: When the value of field FP is greater than 0, the SCK
 * (oversampling clock) generates nonconstant duty cycles.
 * The SCK high duration is increased by "selected clock" period from time
 * to time. The duty cycle depends on the value of
 * the CD field.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_BRGR . FP
 */
#define  VTSS_F_FLEXCOM_FLEX_US_BRGR_FP(x)    VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_US_BRGR_FP       VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_US_BRGR_FP(x)    VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * CD: Clock Divider
 *
 * \details
 * CD = 0 (Baud Rate Clock Disabled)
 * CD = Selected Clock / (16 x Baud Rate) if FLEX_US_MR.OVER = 0 and
 * FLEX_US_MR.SYNC = 0.
 * CD = Selected Clock / (8 x Baud Rate) if FLEX_US_MR.OVER = 1 and
 * FLEX_US_MR.SYNC = 0.
 * CD = Selected Clock / Baud Rate if FLEX_US_MR.SYNC = 1.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_BRGR . CD
 */
#define  VTSS_F_FLEXCOM_FLEX_US_BRGR_CD(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FLEXCOM_FLEX_US_BRGR_CD       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FLEXCOM_FLEX_US_BRGR_CD(x)    VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief USART Receiver Timeout Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * USART Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_RTOR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_RTOR(target)    VTSS_IOREG(target,0x89)

/**
 * \brief
 * TO: Timeout Value
 *
 * \details
 * 0: The receiver timeout is disabled.
 * 1 - 255: The receiver timeout is enabled and the timeout delay is TO x
 * bit period.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_RTOR . TO
 */
#define  VTSS_F_FLEXCOM_FLEX_US_RTOR_TO(x)    VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_US_RTOR_TO       VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_US_RTOR_TO(x)    VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief USART Transmitter Timeguard Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * USART Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_TTGR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_TTGR(target)    VTSS_IOREG(target,0x8a)

/**
 * \brief
 * TG: Timeguard Value
 *
 * \details
 * 0: The transmitter timeguard is disabled.
 * 1 - 255: The transmitter timeguard is enabled and TG is timeguard delay
 * / bit period.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_TTGR . TG
 */
#define  VTSS_F_FLEXCOM_FLEX_US_TTGR_TG(x)    VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_US_TTGR_TG       VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_US_TTGR_TG(x)    VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief USART Manchester Configuration Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * USART Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_MAN
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_MAN(target)     VTSS_IOREG(target,0x94)

/**
 * \brief
 * RXIDLEV: Receiver Idle Value
 *
 * \details
 * 0: Receiver line idle value is 0.
 * 1: Receiver line idle value is 1.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . RXIDLEV
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_RXIDLEV(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_RXIDLEV   VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_RXIDLEV(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * DRIFT: Drift Compensation
 *
 * \details
 * 0: The USART cannot recover from an important clock drift.
 * 1: The USART can recover from clock drift. The 16X Clock mode must be
 * enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . DRIFT
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_DRIFT(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_DRIFT     VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_DRIFT(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * ONE: Must Be Set to 1Bit 29 must always be set to 1 when programming the
 * FLEX_US_MAN register.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . ONE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_ONE(x)    VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_ONE       VTSS_BIT(29)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_ONE(x)    VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * RX_MPOL: Receiver Manchester Polarity
 *
 * \details
 * 0: Logic zero is coded as a zero-to-one transition, Logic one is coded
 * as a one-to-zero transition.
 * 1: Logic zero is coded as a one-to-zero transition, Logic one is coded
 * as a zero-to-one transition.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . RX_MPOL
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_RX_MPOL(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_RX_MPOL   VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_RX_MPOL(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * RX_PP: Receiver Preamble Pattern detected
 *
 * \details
 * The following values assume that RX_MPOL field is not set:
 * 0 (ALL_ONE): The preamble is composed of 1's,
 * 1 (ALL_ZERO): The preamble is composed of 0's.
 * 2 (ZERO_ONE): The preamble is composed of '01's.
 * 3 (ONE_ZERO): THe preamble is composed of '10's.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . RX_PP
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_RX_PP(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_RX_PP     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_RX_PP(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * RX_PL: Receiver Preamble Length
 *
 * \details
 * 0: The receiver preamble pattern detection is disabled
 * 1 - 15: The detected preamble length is RX_PL x Bit Period
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . RX_PL
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_RX_PL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_RX_PL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_RX_PL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * TX_MPOL: Transmitter Manchester Polarity
 *
 * \details
 * 0: Logic zero is coded as a zero-to-one transition, Logic one is coded
 * as a one-to-zero transition.
 * 1: Logic zero is coded as a one-to-zero transition, Logic one is coded
 * as a zero-to-one transition.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . TX_MPOL
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_TX_MPOL(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_TX_MPOL   VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_TX_MPOL(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * TX_PP: Transmitter Preamble Pattern
 *
 * \details
 * The following values assume that TX_MPOL field is not set:
 * 0 (ALL_ONE): The preamble is composed of 1's,
 * 1 (ALL_ZERO): The preamble is composed of 0's.
 * 2 (ZERO_ONE): The preamble is composed of '01's.
 * 3 (ONE_ZERO): THe preamble is composed of '10's.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . TX_PP
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_TX_PP(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_TX_PP     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_TX_PP(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * TX_PL: Transmitter Preamble Length
 *
 * \details
 * 0: The transmitter preamble pattern generation is disabled
 * 1 - 15: The preamble length is TX_PL x Bit Period
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_MAN . TX_PL
 */
#define  VTSS_F_FLEXCOM_FLEX_US_MAN_TX_PL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_FLEXCOM_FLEX_US_MAN_TX_PL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_FLEXCOM_FLEX_US_MAN_TX_PL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief USART Comparison Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * USART Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_CMPR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_CMPR(target)    VTSS_IOREG(target,0xa4)

/**
 * \brief
 * VAL2: Second Comparison Value for Received Character
 *
 * \details
 * 0 - 511: The received character must be lower than or equal to the value
 * of VAL2 and higher than or equal to VAL1 to set
 * the FLEX_US_CSR.CMP flag.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CMPR . VAL2
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CMPR_VAL2(x)  VTSS_ENCODE_BITFIELD(x,16,9)
#define  VTSS_M_FLEXCOM_FLEX_US_CMPR_VAL2     VTSS_ENCODE_BITMASK(16,9)
#define  VTSS_X_FLEXCOM_FLEX_US_CMPR_VAL2(x)  VTSS_EXTRACT_BITFIELD(x,16,9)

/**
 * \brief
 * CMPPAR: Compare Parity
 *
 * \details
 * 0: The parity is not checked and a bad parity cannot prevent from waking
 * up the system.
 * 1: The parity is checked and a matching condition on data can be
 * cancelled by an error on parity bit, so no wakeup is performed.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CMPR . CMPPAR
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CMPR_CMPPAR(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_FLEXCOM_FLEX_US_CMPR_CMPPAR   VTSS_BIT(14)
#define  VTSS_X_FLEXCOM_FLEX_US_CMPR_CMPPAR(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * CMPMODE: Comparison Mode
 *
 * \details
 * 0 (FLAG_ONLY): Any character is received and comparison function drives
 * CMP flag.
 * 1 (START_CONDITION): Comparison condition must be met to start
 * reception.
 * 2 (FILTER): Comparison must be met to receive the current data only.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CMPR . CMPMODE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CMPR_CMPMODE(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_FLEXCOM_FLEX_US_CMPR_CMPMODE     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_FLEXCOM_FLEX_US_CMPR_CMPMODE(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * VAL1: First Comparison Value for Received Character
 *
 * \details
 * 0 - 511: The received character must be higher than or equal to the
 * value of VAL1 and lower than or equal to VAL2 to set
 * the FLEX_US_CSR.CMP flag.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_CMPR . VAL1
 */
#define  VTSS_F_FLEXCOM_FLEX_US_CMPR_VAL1(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_FLEXCOM_FLEX_US_CMPR_VAL1     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_FLEXCOM_FLEX_US_CMPR_VAL1(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief USART FIFO Mode Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_FMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_FMR(target)     VTSS_IOREG(target,0xa8)

/**
 * \brief
 * RXFTHRES2: Receive FIFO Threshold 20 - FIFO_DEPTH_USART: Defines the
 * Receive FIFO threshold 2 value (number of data). The
 * FLEX_US_FESR.RXFTHF2flag will be set when Receive FIFO goes from "above"
 * threshold state to "equal to or below" threshold state.FIFO_DEPTH_USART:
 * Size of the USART FIFOs (4, 8, 16, 32...)
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMR . RXFTHRES2
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMR_RXFTHRES2(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_FLEXCOM_FLEX_US_FMR_RXFTHRES2     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_FLEXCOM_FLEX_US_FMR_RXFTHRES2(x)  VTSS_EXTRACT_BITFIELD(x,24,6)

/**
 * \brief
 * RXFTHRES: Receive FIFO Threshold0 - FIFO_DEPTH_USART: Defines the
 * Receive FIFO threshold value (number of data). The
 * FLEX_US_FESR.RXFTHFflag will be set when Receive FIFO goes from "below"
 * threshold state to "equal to or above" threshold state.FIFO_DEPTH_USART:
 * Size of the USART FIFOs (4, 8, 16, 32...)
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMR . RXFTHRES
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMR_RXFTHRES(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_FLEXCOM_FLEX_US_FMR_RXFTHRES     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_FLEXCOM_FLEX_US_FMR_RXFTHRES(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * TXFTHRES: Transmit FIFO Threshold0 - FIFO_DEPTH_USART: Defines the
 * Transmit FIFO threshold value (number of data). The
 * FLEX_US_FESR.TXFTHFflag will be set when Transmit FIFO goes from "above"
 * threshold state to "equal to or below" threshold state.FIFO_DEPTH_USART:
 * Size of the USART FIFOs (4, 8, 16, 32...)
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMR . TXFTHRES
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMR_TXFTHRES(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_FLEXCOM_FLEX_US_FMR_TXFTHRES     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_FLEXCOM_FLEX_US_FMR_TXFTHRES(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * FRTSC: FIFO RTS Pin Control enable (Hardware Handshaking mode only)
 *
 * \details
 * 0: RTS pin is not controlled by Receive FIFO thresholds.
 * 1: RTS pin is controlled by Receive FIFO thresholds.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMR . FRTSC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMR_FRTSC(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FMR_FRTSC     VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_FMR_FRTSC(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * RXRDYM: Receiver Ready Mode
 *
 * \details
 * If FIFOs are enabled, the FLEX_US_CSR.RXRDY flag behaves as follows.
 * 0 (ONE_DATA):   RXRDY will be at level '1' when at least one unread data
 * is in the receive FIFO
 * 1 (TWO_DATA)   RXRDY will be at level '1' when at least two unread data
 * is in the receive FIFO
 * 2 (FOUR_DATA): RXRDY will be at level '1' when at least four unread data
 * is in the receive FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMR . RXRDYM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMR_RXRDYM(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_FLEXCOM_FLEX_US_FMR_RXRDYM     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_FLEXCOM_FLEX_US_FMR_RXRDYM(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * TXRDYM: Transmitter Ready Mode
 *
 * \details
 * If FIFOs are enabled, the FLEX_US_CSR.TXRDY flag behaves as follows.
 * 0 (ONE_DATA):   TXRDY will be at level '1' when at least one data can be
 * written in the Transmit FIFO
 * 1 (TWO_DATA)   TXRDY will be at level '1' when at least two data can be
 * written in the Transmit FIFO
 * 2 (FOUR_DATA): TXRDY will be at level '1' when at least four data can be
 * written in the Transmit FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FMR . TXRDYM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FMR_TXRDYM(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_FLEXCOM_FLEX_US_FMR_TXRDYM     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_FLEXCOM_FLEX_US_FMR_TXRDYM(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief USART FIFO Level Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_FLR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_FLR(target)     VTSS_IOREG(target,0xa9)

/**
 * \brief
 * RXFL: Receive FIFO Level
 *
 * \details
 * 0: There is no unread data in the Receive FIFO
 * 1- FIFO_DEPTH_USART: Indicates the number of unread data in the Receive
 * FIFO
 *
 * FIFO_DEPTH_USART: Size of the USART FIFOs (4, 8, 16, 32...)
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FLR . RXFL
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FLR_RXFL(x)   VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_FLEXCOM_FLEX_US_FLR_RXFL      VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_FLEXCOM_FLEX_US_FLR_RXFL(x)   VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * TXFL: Transmit FIFO Level
 *
 * \details
 * 0: There is no data in the Transmit FIFO
 * 1 - FIFO_DEPTH_USART: Indicates the number of data in the Transmit FIFO
 *
 * FIFO_DEPTH_USART: Size of the USART FIFOs (4, 8, 16, 32...)
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FLR . TXFL
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FLR_TXFL(x)   VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_FLEXCOM_FLEX_US_FLR_TXFL      VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_FLEXCOM_FLEX_US_FLR_TXFL(x)   VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief USART FIFO Interrupt Enable Register
 *
 * \details
 * Write-only
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_FIER
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_FIER(target)    VTSS_IOREG(target,0xaa)

/**
 * \brief
 * RXFTHF2_IE: RXFTHF2 Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . RXFTHF2_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_RXFTHF2_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_RXFTHF2_IE  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_RXFTHF2_IE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * RXFPTEF_IE: RXFPTEF Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . RXFPTEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_RXFPTEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_RXFPTEF_IE  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_RXFPTEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXFPTEF_IE: TXFPTEF Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . TXFPTEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_TXFPTEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_TXFPTEF_IE  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_TXFPTEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXFTHF_IE: RXFTHF Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . RXFTHF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_RXFTHF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_RXFTHF_IE  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_RXFTHF_IE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXFFF_IE: RXFFF Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . RXFFF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_RXFFF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_RXFFF_IE  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_RXFFF_IE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RXFEF_IE: RXFEF Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . RXFEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_RXFEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_RXFEF_IE  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_RXFEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXFTHF_IE: TXFTHF Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . TXFTHF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_TXFTHF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_TXFTHF_IE  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_TXFTHF_IE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXFFF_IE: TXFFF Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . TXFFF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_TXFFF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_TXFFF_IE  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_TXFFF_IE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXFEF_IE: TXFEF Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIER . TXFEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIER_TXFEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIER_TXFEF_IE  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_FIER_TXFEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART FIFO Interrupt Disable Register
 *
 * \details
 * This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_FIDR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_FIDR(target)    VTSS_IOREG(target,0xab)

/**
 * \brief
 * RXFTHF2_ID: RXFTHF2 Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . RXFTHF2_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_RXFTHF2_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_RXFTHF2_ID  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_RXFTHF2_ID(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * RXFPTEF_ID: RXFPTEF Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . RXFPTEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_RXFPTEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_RXFPTEF_ID  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_RXFPTEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXFPTEF_ID: TXFPTEF Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . TXFPTEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_TXFPTEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_TXFPTEF_ID  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_TXFPTEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXFTHF_ID: RXFTHF Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . RXFTHF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_RXFTHF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_RXFTHF_ID  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_RXFTHF_ID(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXFFF_ID: RXFFF Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . RXFFF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_RXFFF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_RXFFF_ID  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_RXFFF_ID(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RXFEF_ID: RXFEF Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . RXFEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_RXFEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_RXFEF_ID  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_RXFEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXFTHF_ID: TXFTHF Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . TXFTHF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_TXFTHF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_TXFTHF_ID  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_TXFTHF_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXFFF_ID: TXFFF Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . TXFFF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_TXFFF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_TXFFF_ID  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_TXFFF_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXFEF_ID: TXFEF Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIDR . TXFEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIDR_TXFEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIDR_TXFEF_ID  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_FIDR_TXFEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART FIFO Interrupt Mask Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_FIMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_FIMR(target)    VTSS_IOREG(target,0xac)

/**
 * \brief
 * RXFTHF2_IM: RXFTHF2 Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . RXFTHF2_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_RXFTHF2_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_RXFTHF2_IM  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_RXFTHF2_IM(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * RXFPTEF_IM: RXFPTEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . RXFPTEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_RXFPTEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_RXFPTEF_IM  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_RXFPTEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXFPTEF_IM: TXFPTEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . TXFPTEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_TXFPTEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_TXFPTEF_IM  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_TXFPTEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXFTHF_IM: RXFTHF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . RXFTHF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_RXFTHF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_RXFTHF_IM  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_RXFTHF_IM(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXFFF_IM: RXFFF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . RXFFF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_RXFFF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_RXFFF_IM  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_RXFFF_IM(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RXFEF_IM: RXFEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . RXFEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_RXFEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_RXFEF_IM  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_RXFEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXFTHF_IM: TXFTHF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . TXFTHF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_TXFTHF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_TXFTHF_IM  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_TXFTHF_IM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXFFF_IM: TXFFF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . TXFFF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_TXFFF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_TXFFF_IM  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_TXFFF_IM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXFEF_IM: TXFEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FIMR . TXFEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FIMR_TXFEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FIMR_TXFEF_IM  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_FIMR_TXFEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART FIFO Event Status Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_FESR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_FESR(target)    VTSS_IOREG(target,0xad)

/**
 * \brief
 * RXFTHF2: Receive FIFO Threshold Flag 2 (cleared by writing the
 * FLEX_US_CR.RSTSTA bit)
 *
 * \details
 * 0: Number of unread data in Receive FIFO is above RXFTHRES threshold.
 * 1: Number of unread data in Receive FIFO has reached RXFTHRES2 threshold
 *
 * since the last RSTSTA command was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . RXFTHF2
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_RXFTHF2(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_RXFTHF2  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_RXFTHF2(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * TXFLOCK: Transmit FIFO Lock
 *
 * \details
 * 0: The Transmit FIFO is not locked.
 * 1: The Transmit FIFO is locked.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . TXFLOCK
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_TXFLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_TXFLOCK  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_TXFLOCK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * RXFPTEF: Receive FIFO Pointer Error Flag
 *
 * \details
 * 0: No Receive FIFO pointer occurred
 * 1: Receive FIFO pointer error occurred. Receiver must be reset
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . RXFPTEF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_RXFPTEF(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_RXFPTEF  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_RXFPTEF(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXFPTEF: Transmit FIFO Pointer Error Flag
 *
 * \details
 * 0: No Transmit FIFO pointer occurred
 * 1: Transmit FIFO pointer error occurred. Transceiver must be reset
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . TXFPTEF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_TXFPTEF(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_TXFPTEF  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_TXFPTEF(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXFTHF: Receive FIFO Threshold Flag (cleared by writing the
 * FLEX_US_CR.RSTSTA bit)
 *
 * \details
 * 0: Number of unread data in Receive FIFO is below RXFTHRES threshold.
 * 1: Number of unread data in Receive FIFO has reached RXFTHRES threshold
 * since the last RSTSTA command was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . RXFTHF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_RXFTHF(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_RXFTHF   VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_RXFTHF(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXFFF: Receive FIFO Full Flag (cleared by writing the FLEX_US_CR.RSTSTA
 * bit)
 *
 * \details
 * 0: Receive FIFO is not full.
 * 1: Receive FIFO has been filled since the last RSTSTA command was
 * issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . RXFFF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_RXFFF(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_RXFFF    VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_RXFFF(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RXFEF: Receive FIFO Empty Flag (cleared by writing the FLEX_US_CR.RSTSTA
 * bit)
 *
 * \details
 * 0: Receive FIFO is not empty.
 * 1: Receive FIFO has been emptied since the last RSTSTA command was
 * issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . RXFEF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_RXFEF(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_RXFEF    VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_RXFEF(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXFTHF: Transmit FIFO Threshold Flag (cleared by writing the
 * FLEX_US_CR.RSTSTA bit)
 *
 * \details
 * 0: Number of data in Transmit FIFO is above TXFTHRES threshold.
 * 1: Number of data in Transmit FIFO has reached TXFTHRES threshold since
 * the last RSTSTA command was issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . TXFTHF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_TXFTHF(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_TXFTHF   VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_TXFTHF(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXFFF: Transmit FIFO Full Flag (cleared by writing the FLEX_US_CR.RSTSTA
 * bit)
 *
 * \details
 * 0: Transmit FIFO is not full.
 * 1: Transmit FIFO has been filled since the last RSTSTA command was
 * issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . TXFFF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_TXFFF(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_TXFFF    VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_TXFFF(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXFEF: Transmit FIFO Empty Flag (cleared by writing the
 * FLEX_US_CR.RSTSTA bit)
 *
 * \details
 * 0: Transmit FIFO is not empty.
 * 1: Transmit FIFO has been emptied since the last RSTSTA command was
 * issued.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_FESR . TXFEF
 */
#define  VTSS_F_FLEXCOM_FLEX_US_FESR_TXFEF(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_FESR_TXFEF    VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_FESR_TXFEF(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART Write Protection Mode Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_WPMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_WPMR(target)    VTSS_IOREG(target,0xb9)

/**
 * \brief
 * WPKEY: Write Protection Key (PASSWD)
 *
 * \details
 * Value = 0x555341 (PASSWD) Writing any other value in this field aborts
 * the write operation of bits WPEN, WPITEN and WPCREN.
 * Always reads as 0.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_WPMR . WPKEY
 */
#define  VTSS_F_FLEXCOM_FLEX_US_WPMR_WPKEY(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_FLEXCOM_FLEX_US_WPMR_WPKEY     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_FLEXCOM_FLEX_US_WPMR_WPKEY(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * WPCREN: Write Protection Control Enable
 *
 * \details
 * 0: Disables the write protection on control register if WPKEY
 * corresponds to 0x555341 ("USA" in ASCII).
 * 1: Enables the write protection on control register if WPKEY corresponds
 * to 0x555341 ("USA" in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_WPMR . WPCREN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_WPMR_WPCREN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_US_WPMR_WPCREN   VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_US_WPMR_WPCREN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * WPITEN: Write Protection Interrupt Enable
 *
 * \details
 * 0: Disables the write protection on interrupt registers if WPKEY
 * corresponds to 0x555341 ("USA" in ASCII).
 * 1: Enables the write protection on interrupt registers if WPKEY
 * corresponds to 0x555341 ("USA" in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_WPMR . WPITEN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_WPMR_WPITEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_US_WPMR_WPITEN   VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_US_WPMR_WPITEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPEN: Write Protection Enable
 *
 * \details
 * 0: Disables the write protection on configuration registers if WPKEY
 * corresponds to 0x555341 ("USA" in ASCII).
 * 1: Enables the write protection on configuration registers if WPKEY
 * corresponds to 0x555341 ("USA" in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_WPMR . WPEN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_WPMR_WPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_WPMR_WPEN     VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_WPMR_WPEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART Write Protection Status Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_WPSR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_WPSR(target)    VTSS_IOREG(target,0xba)

/**
 * \brief
 * WPVSRC: Write Protection Violation Source
 *
 * \details
 * When WPVS = 1, WPVSRC indicates the register address offset at which a
 * write access has been attempted.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_WPSR . WPVSRC
 */
#define  VTSS_F_FLEXCOM_FLEX_US_WPSR_WPVSRC(x)  VTSS_ENCODE_BITFIELD(x,8,16)
#define  VTSS_M_FLEXCOM_FLEX_US_WPSR_WPVSRC     VTSS_ENCODE_BITMASK(8,16)
#define  VTSS_X_FLEXCOM_FLEX_US_WPSR_WPVSRC(x)  VTSS_EXTRACT_BITFIELD(x,8,16)

/**
 * \brief
 * WPVS: Write Protection Violation Status
 *
 * \details
 * 0: No write protection violation has occurred since the last read of
 * FLEX_US_WPSR.
 * 1: A write protection violation has occurred since the last read of
 * FLEX_US_WPSR. If this violation is an unauthorized
 * attempt to write a protected register, the associated violation is
 * reported into field WPVSRC.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_US_WPSR . WPVS
 */
#define  VTSS_F_FLEXCOM_FLEX_US_WPSR_WPVS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_US_WPSR_WPVS     VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_US_WPSR_WPVS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USART Version Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_USART_REG:FLEX_US_VERSION
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_US_VERSION(target)  VTSS_IOREG(target,0xbf)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_VERSION . USART_MFN
 */
#define  VTSS_F_FLEXCOM_FLEX_US_VERSION_USART_MFN(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_US_VERSION_USART_MFN     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_US_VERSION_USART_MFN(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Hardware Module VersionReserved. Value subject to change. No
 * functionality associated. This is the internal version of the macrocell.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_US_VERSION . USART_VERSION
 */
#define  VTSS_F_FLEXCOM_FLEX_US_VERSION_USART_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_FLEXCOM_FLEX_US_VERSION_USART_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_FLEXCOM_FLEX_US_VERSION_USART_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * Register Group: \a FLEXCOM:FLEXCOM_SPI_REG
 *
 * SPI Register Group
 */


/**
 * \brief SPI Control Register
 *
 * \details
 * This register can only be written if the WPCREN bit is cleared in the
 * SPI Write Protection Mode Register. This register has Write-only access.
 * Note: This register has Write-only access.

 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_CR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_CR(target)     VTSS_IOREG(target,0x100)

/**
 * \brief
 * FIFODIS: FIFO Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the Transmit and Receive FIFOs
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . FIFODIS
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_FIFODIS(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_FIFODIS   VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_FIFODIS(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * FIFOEN: FIFO Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the Transmit and Receive FIFOs
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . FIFOEN
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_FIFOEN(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_FIFOEN    VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_FIFOEN(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * LASTXFER: Last Transfer
 *
 * \details
 * 0: No effect.
 * 1: The current NPCS will be deasserted after the character written in TD
 * has been transferred. When FLEX_SPI_CSRx.CSAAT
 * is set, the communication with the current serial peripheral can be
 * closed by raising the corresponding NPCS line as soon as TD
 * transfer is completed.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . LASTXFER
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_LASTXFER(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_LASTXFER  VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_LASTXFER(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * RXFCLR: Receive FIFO Clear
 *
 * \details
 * 0: No effect.
 * 1: Empties the Receive FIFO.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . RXFCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_RXFCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_RXFCLR    VTSS_BIT(17)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_RXFCLR(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * TXFCLR: Transmit FIFO Clear
 *
 * \details
 * 0: No effect.
 * 1: Empties the Transmit FIFO.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . TXFCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_TXFCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_TXFCLR    VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_TXFCLR(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * REQCLR: Request to Clear the Comparison Trigger
 *
 * \details
 * 0: No effect.
 * 1: Restarts the comparison trigger to enable FLEX_SPI_RDR loading.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . REQCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_REQCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_REQCLR    VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_REQCLR(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * SWRST: SPI Software Reset
 *
 * \details
 * 0: No effect.
 * 1: Reset the SPI. A software-triggered hardware reset of the SPI
 * interface is performed.
 * The SPI is in Target mode after software reset.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . SWRST
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_SWRST(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_SWRST     VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_SWRST(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SPIDIS: SPI Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the SPI.
 *
 * If a transfer is in progress when SPIDIS is set, the SPI completes the
 * transmission of the shifter register and does not start
 * any new transfer, even if the FLEX_US_THR is loaded.
 * All pins are set in Input mode after completion of the transmission in
 * progress, if any.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . SPIDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_SPIDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_SPIDIS    VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_SPIDIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * SPIEN: SPI Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the SPI to transfer and receive data.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CR . SPIEN
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CR_SPIEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CR_SPIEN     VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CR_SPIEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Mode Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the SPI
 * Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_MR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_MR(target)     VTSS_IOREG(target,0x101)

/**
 * \brief
 * DLYBCS: Delay Between Chip Selects
 *
 * \details
 * This field defines the delay between the inactivation and the activation
 * of NPCS. The DLYBCS time guarantees nonoverlapping
 * chip selects and solves bus contentions in case of peripherals having
 * long data float times.
 * If DLYBCS is less than or equal to 6, six peripheral clock periods are
 * inserted by default.
 *
 * Otherwise, the following equations determine the delay:
 * If FLEX_SPI_MR.BRSRCCLK = 0: DLYBCS = Delay Between Chip Selects x
 * fperipheral clock
 * If FLEX_SPI_MR.BRSRCCLK = 1: DLYBCS = Delay Between Chip Selects x
 * fGCLKPCKx
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . DLYBCS
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_DLYBCS(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_DLYBCS     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_DLYBCS(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * PCS_MR: Peripheral Chip Select
 *
 * \details
 * This field is only used if fixed peripheral select is active (PS = 0).
 * If PCSDEC = 0:
 * PCS_MR = xxx0 NPCS[1:0] = 10 if NB_CHIP_SELECT = 2
 * PCS_MR = xx01 NPCS[1:0] = 01 if NB_CHIP_SELECT = 2
 * PCS_MR = 1111 forbidden (no peripheral is selected)
 * (x = don't care)
 *
 * If PCSDEC = 1:
 * NPCS[1:0] output signals = PCS_MR if NB_CHIP_SELECT = 2

 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . PCS_MR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_PCS_MR(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_PCS_MR     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_PCS_MR(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * CMPMODE: Comparison Mode
 *
 * \details
 * 0 (FLAG_ONLY): Any character is received and comparison function drives
 * CMP flag.
 * 1 (START_CONDITION): Comparison condition must be met to start reception
 * of all incoming characters until REQCLR is set.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . CMPMODE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_CMPMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_CMPMODE   VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_CMPMODE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * LBHPC: Last Bit Half Period Compatibility
 *
 * \details
 * 0: Normal SPI mode of operation (all bits have 1-bit time duration,
 * standard SPI mode)
 * 1: Compatibility mode when connected to an SPI target having only half
 * bit period duration time for the last bit of the frame
 * (not a standard SPI mode)
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . LBHPC
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_LBHPC(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_LBHPC     VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_LBHPC(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * LLB: Local Loopback Enable
 *
 * \details
 * 0: Local loopback path disabled.
 * 1: Local loopback path enabled.
 * LLB controls the local loopback on the data shift register for testing
 * in Initiator mode only (MISO is internally connected on MOSI).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . LLB
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_LLB(x)    VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_LLB       VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_LLB(x)    VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * WDRBT: Wait Data Read Before Transfer
 *
 * \details
 * 0: No Effect. In Initiator mode, a transfer can be initiated regardless
 * of the FLEX_SPI_RDR state.
 * 1: In Initiator mode, a transfer can start only if FLEX_SPI_RDR is
 * empty, i.e., does not contain any unread data. This mode
 * prevents overrun error in reception.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . WDRBT
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_WDRBT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_WDRBT     VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_WDRBT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * MODFDIS: Mode Fault Detection
 *
 * \details
 * 0: Mode fault detection is enabled.
 * 1: Mode fault detection is disabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . MODFDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_MODFDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_MODFDIS   VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_MODFDIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * BRSRCCLK: Bit Rate Source Clock
 *
 * \details
 * 0 (PERIPH_CLK): The peripheral clock is the source clock for the bit
 * rate generation.
 * 1 (GCLKPMC_PCK): GCLKPMC_PCKx is the source clock for the bit rate
 * generation, thus the bit rate can be independent
 * of the core/peripheral clock.
 * Note: If the bit BRSRCCLK = 1, the FLEX_US_CSRx.SCBR field must be
 * programmed with a value greater than 1.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . BRSRCCLK
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_BRSRCCLK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_BRSRCCLK  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_BRSRCCLK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * PCSDEC: Chip Select Decode
 *
 * \details
 * 0: The chip selects are directly connected to a peripheral device.
 * 1: The two NPCS chip select lines are connected to a 2- to 4 bit
 * decoder.
 * When PCSDEC equals one, up to 3 Chip Select signals can be generated
 * with the two NPCS lines using an external
 * 2- to 4 bit decoder. The Chip Select registers define the
 * characteristics of the 3 chip selects, with the following rules:
 * FLEX_SPI_CSR0 defines peripheral chip select signals 0 to 1.
 * FLEX_SPI_CSR1 defines peripheral chip select signal 2.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . PCSDEC
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_PCSDEC(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_PCSDEC    VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_PCSDEC(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * PS: Peripheral Select
 *
 * \details
 * 0: Fixed Peripheral Select
 * 1: Variable Peripheral Select
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . PS
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_PS(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_PS        VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_PS(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * MSTR: Initiator/Target Mode
 *
 * \details
 * 0: SPI is in Target mode.
 * 1: SPI is in Initiator mode.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_MR . MSTR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_MR_MSTR(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_MR_MSTR      VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_MR_MSTR(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Receive Data Register
 *
 * \details
 * Note: If FIFO is enabled (FLEX_SPI_CR.FIFOEN) and FLEX_SPI_FMR.RXRDYM =
 * 0, the Receive FIFO operates in Single Data mode.
 * Note: If FIFO is enabled (FLEX_SPI_CR.FIFOEN) and FLEX_SPI_FMR.RXRDYM >
 * 0, the Receive FIFO operates in Multi Data mode.
 * Note: If Initiator mode is used (FLEX_SPI_MR.MSTR=1), the Receive FIFO
 * must operate in Single Data mode.
 * Note: If Variable Peripheral Select mode is used (FLEX_SPI_MR.PS=1), the
 * Transmit FIFO must operate in Single Data mode.
 * Note: By default, any debugger or software read access to FLEX_SPI_RDR
 * clears the FLEX_SPI_SR.RDRF flag. To prevent this flag
 * from being cleared on debugger read access, a specific bit must be
 * enabled in the SFR module.

 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_RDR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_RDR(target)    VTSS_IOREG(target,0x102)

/**
 * \brief
 * PCS_RDR: Peripheral Chip SelectIn Initiator mode only, these bits
 * indicate the value on the NPCS pins at the end of a transfer. Otherwise,
 * these bits are read as zero.Note: When using Variable Peripheral Select
 * mode (FLEX_SPI_MR.PS = 1), it is mandatory to set the FLEX_SPI_MR.WDRBT
 * bitto 1 if the PCS field must be processed in FLEX_SPI_RDR.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_RDR . PCS_RDR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_RDR_PCS_RDR(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_SPI_RDR_PCS_RDR     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_RDR_PCS_RDR(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * RD: Receive DataData received by the SPI Interface is stored in this
 * register in a right-justified format. Unused bits are read as zero.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_RDR . RD
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_RDR_RD(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FLEXCOM_FLEX_SPI_RDR_RD       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_RDR_RD(x)    VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief SPI Receive Data Register (FIFO Multiple Data, 8-bit)
 *
 * \details
 * Note: This register will be used when FIFO is enabled
 * (FLEX_SPI_CR.FIFOEN), FLEX_SPI_FMR.RXRDYM > 0, FLEX_SPI_MR.MSTR = 0, and
 * FLEX_SPI_CSRx.BITS = 0.
 * Note: If FIFO is enabled (FLEX_SPI_CR.FIFOEN) and FLEX_SPI_FMR.RXRDYM >
 * 0, the Receive FIFO operates in Multi Data mode.
 * Note: If Initiator mode is used (FLEX_SPI_MR.MSTR=1), the Receive FIFO
 * must operate in Single Data mode.
 * Note: If Variable Peripheral Select mode is used (FLEX_SPI_MR.PS=1), the
 * Transmit FIFO must operate in Single Data mode.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_FMT_RDR_8
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_FMT_RDR_8(target)  VTSS_IOREG(target,0x102)

/**
 * \brief
 * RD3: Receive DataFirst unread data in the Receive FIFO. Data received by
 * the SPI Interface is stored in this register in a right-justified
 * format.Unused bits are read as zero.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMT_RDR_8 . RD3
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * RD2: Receive DataFirst unread data in the Receive FIFO. Data received by
 * the SPI Interface is stored in this register in a right-justified
 * format.Unused bits are read as zero.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMT_RDR_8 . RD2
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RD1: Receive DataFirst unread data in the Receive FIFO. Data received by
 * the SPI Interface is stored in this register in a right-justified
 * format.Unused bits are read as zero.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMT_RDR_8 . RD1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * RD0: Receive DataFirst unread data in the Receive FIFO. Data received by
 * the SPI Interface is stored in this register in a right-justified
 * format.Unused bits are read as zero.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMT_RDR_8 . RD0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMT_RDR_8_RD0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief SPI Receive Data Register (FIFO Multiple Data, 16-bit)
 *
 * \details
 * Note: This register will be used when FIFO is enabled
 * (FLEX_SPI_CR.FIFOEN), FLEX_SPI_FMR.RXRDYM > 0, FLEX_SPI_MR.MSTR = 0, and
 * FLEX_SPI_CSRx.BITS = 8.
 * Note: If FIFO is enabled (FLEX_SPI_CR.FIFOEN) and FLEX_SPI_FMR.RXRDYM >
 * 0, the Receive FIFO operates in Multi Data mode.
 * Note: If Initiator mode is used (FLEX_SPI_MR.MSTR=1), the Receive FIFO
 * must operate in Single Data mode.
 * Note: If Variable Peripheral Select mode is used (FLEX_SPI_MR.PS=1), the
 * Transmit FIFO must operate in Single Data mode.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_FMT_RDR_16
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_FMT_RDR_16(target)  VTSS_IOREG(target,0x102)

/**
 * \brief
 * RD1_16: Receive DataFirst unread data in the Receive FIFO. Data received
 * by the SPI Interface is stored in this register in a right-justified
 * format.Unused bits are read as zero.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMT_RDR_16 . RD1_16
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMT_RDR_16_RD1_16(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMT_RDR_16_RD1_16     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMT_RDR_16_RD1_16(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * RD0_16: Receive DataFirst unread data in the Receive FIFO. Data received
 * by the SPI Interface is stored in this register in a right-justified
 * format.Unused bits are read as zero.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMT_RDR_16 . RD0_16
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMT_RDR_16_RD0_16(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMT_RDR_16_RD0_16     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMT_RDR_16_RD0_16(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief SPI Transmit Data Register
 *
 * \details
 * Note: If FIFO is enabled (FLEX_SPI_CR.FIFOEN) and FLEX_SPI_FMR.TXRDYM =
 * 0, the Transmit FIFO operates in Single Data mode.
 * Note: If FIFO is enabled (FLEX_SPI_CR.FIFOEN) and FLEX_SPI_FMR.TXRDYM >
 * 0, the Transmit FIFO operates in Multi Data mode.
 * Note: The Transmit FIFO can be loaded with multiple data in the same
 * access by configuring TXRDYM > 0 and when FLEX_SPI_MR.PS = 0.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_TDR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_TDR(target)    VTSS_IOREG(target,0x103)

/**
 * \brief
 * LASTXFER_TDR: Last Transfer
 *
 * \details
 * 0: No effect.
 * 1: The current NPCS is deasserted after the transfer of the character
 * written in TD. When FLEX_SPI_CSRx.CSAAT is set,
 * the communication with the current serial peripheral can be closed by
 * raising the corresponding NPCS line as soon as TD
 * transfer is completed.
 * This field is only used if variable peripheral select is active
 * (FLEX_SPI_MR.PS = 1).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_TDR . LASTXFER_TDR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_TDR_LASTXFER_TDR(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_TDR_LASTXFER_TDR  VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_SPI_TDR_LASTXFER_TDR(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * PCS_TDR: Peripheral Chip SelectThis field is only used if variable
 * peripheral select is active (FLEX_SPI_MR.PS = 1).
 *
 * \details
 * If FLEX_SPI_MR.PCSDEC = 0:
 * PCS_TDR = xxx0 NPCS[1:0] = 10 if NB_CHIP_SELECT = 2
 * PCS_TDR = xx01 NPCS[1:0] = 01 if NB_CHIP_SELECT = 2
 * PCS_TDR = 1111 forbidden (no peripheral is selected)
 * (x = don't care)
 *
 * If FLEX_SPI_MR.PCSDEC = 1:
 * NPCS[1:0] output signals = PCS_TDR if NB_CHIP_SELECT = 2
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_TDR . PCS_TDR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_TDR_PCS_TDR(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_SPI_TDR_PCS_TDR     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_TDR_PCS_TDR(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * TD: Transmit DataData to be transmitted by the SPI Interface is stored
 * in this register. Information to be transmitted must be written to
 * thetransmit data register in a right-justified format.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_TDR . TD
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_TDR_TD(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FLEXCOM_FLEX_SPI_TDR_TD       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_TDR_TD(x)    VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief SPI Transmit Data Register (FIFO Multiple Data, 16-bit)
 *
 * \details
 * Note: If FIFO is enabled (FLEX_SPI_CR.FIFOEN) and FLEX_SPI_FMR.TXRDYM >
 * 0, the Transmit FIFO operates in Multi Data mode.
 * Note: The Transmit FIFO can be loaded with multiple data in the same
 * access by configuring TXRDYM > 0 and when FLEX_SPI_MR.PS = 0.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_FMT_TDR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_FMT_TDR(target)  VTSS_IOREG(target,0x103)

/**
 * \brief
 * TD1, Transmit DataNext data to write in the Transmit FIFO. Information
 * to be transmitted must be written to this register in a right-justified
 * format.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMT_TDR . TD1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMT_TDR_TD1(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMT_TDR_TD1     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMT_TDR_TD1(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * TD0: Transmit DataNext data to write in the Transmit FIFO. Information
 * to be transmitted must be written to this register in a right-justified
 * format.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMT_TDR . TD0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMT_TDR_TD0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMT_TDR_TD0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMT_TDR_TD0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief SPI Status Register
 *
 * \details
 * Note: By default, any debugger or software read access to FLEX_SPI_SR
 * clears the MODF, OVRES, NSSR, UNDES, and CMP flags.
 * To prevent these flags from being cleared on debugger read access, a
 * specific bit must be enabled in the SFR module.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_SR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_SR(target)     VTSS_IOREG(target,0x104)

/**
 * \brief
 * RXFPTEF: Receive FIFO Pointer Error Flag
 *
 * \details
 * 0: No Receive FIFO pointer occurred
 * 1: Receive FIFO pointer error occurred. Receiver must be reset
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . RXFPTEF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_RXFPTEF(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_RXFPTEF   VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_RXFPTEF(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * TXFPTEF: Transmit FIFO Pointer Error Flag
 *
 * \details
 * 0: No Transmit FIFO pointer occurred
 * 1: Transmit FIFO pointer error occurred. Transceiver must be reset
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . TXFPTEF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_TXFPTEF(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_TXFPTEF   VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_TXFPTEF(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * RXFTHF: Receive FIFO Threshold Flag
 *
 * \details
 * 0: Number of unread data in Receive FIFO is below RXFTHRES threshold or
 * RXFTHF_SPI flag has been cleared.
 * 1: Number of unread data in Receive FIFO has reached RXFTHRES threshold
 * (changing states from "below threshold" to
 * "equal to or above threshold").
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . RXFTHF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_RXFTHF(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_RXFTHF    VTSS_BIT(29)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_RXFTHF(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * RXFFF: Receive FIFO Full Flag
 *
 * \details
 * 0: Receive FIFO is not empty or RXFFF_SPI flag has been cleared.
 * 1: Receive FIFO has been filled (changing states from "not full" to
 * "full").
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . RXFFF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_RXFFF(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_RXFFF     VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_RXFFF(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * RXFEF: Receive FIFO Empty Flag
 *
 * \details
 * 0: Receive FIFO is not empty or RXFEF_SPI flag has been cleared.
 * 1: Receive FIFO has been emptied (changing states from "not empty" to
 * "empty").
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . RXFEF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_RXFEF(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_RXFEF     VTSS_BIT(27)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_RXFEF(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * TXFTHF: Transmit FIFO Threshold Flag (cleared on read)
 *
 * \details
 * 0: Number of data in Transmit FIFO is above TXFTHRES threshold.
 * 1: Number of data in Transmit FIFO has reached TXFTHRES threshold since
 * the last read of FLEX_SPI_SR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . TXFTHF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_TXFTHF(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_TXFTHF    VTSS_BIT(26)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_TXFTHF(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * TXFFF: Transmit FIFO Full Flag (cleared on read)
 *
 * \details
 * 0: Transmit FIFO is not full or TXFF flag has been cleared.
 * 1: Transmit FIFO has been filled since the last read of FLEX_SPI_SR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . TXFFF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_TXFFF(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_TXFFF     VTSS_BIT(25)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_TXFFF(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * TXFEF: Transmit FIFO Empty Flag (cleared on read)
 *
 * \details
 * 0: Transmit FIFO is not empty.
 * 1: Transmit FIFO has been emptied since the last read of FLEX_SPI_SR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . TXFEF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_TXFEF(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_TXFEF     VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_TXFEF(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * SFERR: Target Frame Error (cleared on read)
 *
 * \details
 * 0: There is no frame error detected for a target access since the last
 * read of FLEX_SPI_SR.
 * 1: In Target mode, the chip select raised while the character defined in
 * FLEX_SPI_CSR0.BITS_CS0 was not complete.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . SFERR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_SFERR(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_SFERR     VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_SFERR(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * CMP: Comparison Status (cleared on read)
 *
 * \details
 * 0: No received character matched the comparison criteria programmed in
 * VAL1 and VAL2 fields in FLEX_SPI_CMPR
 * since the last read of FLEX_SPI_SR.
 * 1: A received character matched the comparison criteria since the last
 * read of FLEX_SPI_SR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . CMP
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_CMP(x)    VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_CMP       VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_CMP(x)    VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * SPIENS: SPI Enable Status
 *
 * \details
 * 0: SPI is disabled.
 * 1: SPI is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . SPIENS
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_SPIENS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_SPIENS    VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_SPIENS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * UNDES: Underrun Error Status (Target mode only) (cleared on read)0: No
 * underrun has been detected since the last read of FLEX_SPI_SR.1: A
 * transfer starts whereas no data has been loaded in FLEX_SPI_TDR, cleared
 * when FLEX_SPI_SR is read.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . UNDES
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_UNDES(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_UNDES     VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_UNDES(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TXEMPTY: Transmission Registers Empty (cleared by writing FLEX_SPI_TDR)
 *
 * \details
 * 0: As soon as data is written in FLEX_SPI_TDR.
 * 1: FLEX_SPI_TDR and internal shift register are empty.
 * If a transfer delay has been defined, TXEMPTY is set
 * after the end of this delay.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . TXEMPTY
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_TXEMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_TXEMPTY   VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_TXEMPTY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * NSSR: NSS Rising (cleared on read)
 *
 * \details
 * 0: No rising edge detected on NSS pin since the last read of
 * FLEX_SPI_SR.
 * 1: A rising edge occurred on NSS pin since the last read of FLEX_SPI_SR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . NSSR
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_NSSR(x)   VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_NSSR      VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_NSSR(x)   VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * OVRES: Overrun Error Status (cleared on read)
 *
 * \details
 * 0: No overrun has been detected since the last read of FLEX_SPI_SR.
 * 1: An overrun has occurred since the last read of FLEX_SPI_SR.
 * An overrun occurs when FLEX_SPI_RDR is loaded at least twice from
 * the shift register since the last read of FLEX_SPI_RDR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . OVRES
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_OVRES(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_OVRES     VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_OVRES(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * MODF: Mode Fault Error (cleared on read)
 *
 * \details
 * 0: No mode fault has been detected since the last read of FLEX_SPI_SR.
 * 1: A mode fault occurred since the last read of FLEX_SPI_SR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . MODF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_MODF(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_MODF      VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_MODF(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TDRE: Transmit Data Register Empty (cleared by writing FLEX_SPI_TDR)
 *
 * \details
 * When FIFOs are disabled:
 * 0: Data has been written to FLEX_SPI_TDR and not yet transferred to the
 * internal shift register.
 * 1: The last data written to FLEX_SPI_TDR has been transferred to the
 * internal shift register.
 * TDRE_SPI is cleared when the SPI is disabled or at reset. Enabling the
 * SPI sets the TDRE_SPI flag.
 *
 * When FIFOs are enabled:
 * 0: Transmit FIFO cannot accept more data.
 * 1: Transmit FIFO can accept data; one or more data can be written
 * according to TXRDYM field configuration.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . TDRE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_TDRE(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_TDRE      VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_TDRE(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RDRF: Receive Data Register Full (cleared by reading FLEX_SPI_RDR)
 *
 * \details
 * When FIFOs are disabled:
 * 0: No data has been received since the last read of FLEX_SPI_RDR.
 * 1: Data has been received and the received data has been transferred
 * from the internal shift register to FLEX_SPI_RDR since the last read of
 * FLEX_SPI_RDR.
 *
 * When FIFOs are enabled:
 * 0: Receive FIFO is empty; no data to read
 * 1: At least one unread data is in the Receive FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_SR . RDRF
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_SR_RDRF(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_SR_RDRF      VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_SR_RDRF(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Interrupt Enable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * SPI Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_IER
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_IER(target)    VTSS_IOREG(target,0x105)

/**
 * \brief
 * RXFPTEF_IE: RXFPTEF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . RXFPTEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_RXFPTEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_RXFPTEF_IE  VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_RXFPTEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * TXFPTEF_IE: TXFPTEF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . TXFPTEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_TXFPTEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_TXFPTEF_IE  VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_TXFPTEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * RXFTHF_IE: RXFTHF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . RXFTHF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_RXFTHF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_RXFTHF_IE  VTSS_BIT(29)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_RXFTHF_IE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * RXFFF_IE: RXFFF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . RXFFF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_RXFFF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_RXFFF_IE  VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_RXFFF_IE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * RXFEF_IE: RXFEF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . RXFEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_RXFEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_RXFEF_IE  VTSS_BIT(27)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_RXFEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * TXFTHF_IE: TXFTHF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . TXFTHF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_TXFTHF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_TXFTHF_IE  VTSS_BIT(26)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_TXFTHF_IE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * TXFFF_IE: TXFFF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . TXFFF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_TXFFF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_TXFFF_IE  VTSS_BIT(25)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_TXFFF_IE(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * TXFEF_IE: TXFEF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . TXFEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_TXFEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_TXFEF_IE  VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_TXFEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CMP_IE: Comparison Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . CMP_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_CMP_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_CMP_IE   VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_CMP_IE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * UNDES_IE: Underrun Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . UNDES_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_UNDES_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_UNDES_IE  VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_UNDES_IE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TXEMPTY_IE: Transmission Registers Empty Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . TXEMPTY_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_TXEMPTY_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_TXEMPTY_IE  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_TXEMPTY_IE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * NSSR_IE: NSS Rising Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . NSSR_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_NSSR_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_NSSR_IE  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_NSSR_IE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * OVRES_IE: Overrun Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . OVRES_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_OVRES_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_OVRES_IE  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_OVRES_IE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * MODF_IE: Mode Fault Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . MODF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_MODF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_MODF_IE  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_MODF_IE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TDRE_IE: SPI Transmit Data Register Empty Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . TDRE_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_TDRE_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_TDRE_IE  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_TDRE_IE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RDRF_IE: Receive Data Register Full Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IER . RDRF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IER_RDRF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IER_RDRF_IE  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IER_RDRF_IE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Interrupt Disable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * SPI Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_IDR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_IDR(target)    VTSS_IOREG(target,0x106)

/**
 * \brief
 * RXFPTEF_ID: RXFPTEF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . RXFPTEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_RXFPTEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_RXFPTEF_ID  VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_RXFPTEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * TXFPTEF_ID: TXFPTEF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . TXFPTEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_TXFPTEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_TXFPTEF_ID  VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_TXFPTEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * RXFTHF_ID: RXFTHF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . RXFTHF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_RXFTHF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_RXFTHF_ID  VTSS_BIT(29)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_RXFTHF_ID(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * RXFFF_ID: RXFFF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . RXFFF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_RXFFF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_RXFFF_ID  VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_RXFFF_ID(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * RXFEF_ID: RXFEF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . RXFEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_RXFEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_RXFEF_ID  VTSS_BIT(27)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_RXFEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * TXFTHF_ID: TXFTHF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . TXFTHF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_TXFTHF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_TXFTHF_ID  VTSS_BIT(26)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_TXFTHF_ID(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * TXFFF_ID: TXFFF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . TXFFF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_TXFFF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_TXFFF_ID  VTSS_BIT(25)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_TXFFF_ID(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * TXFEF_ID: TXFEF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . TXFEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_TXFEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_TXFEF_ID  VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_TXFEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CMP_ID: Comparison Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . CMP_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_CMP_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_CMP_ID   VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_CMP_ID(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * UNDES_ID: Underrun Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . UNDES_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_UNDES_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_UNDES_ID  VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_UNDES_ID(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TXEMPTY_ID: Transmission Registers Empty Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . TXEMPTY_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_TXEMPTY_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_TXEMPTY_ID  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_TXEMPTY_ID(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * NSSR_ID: NSS Rising Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . NSSR_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_NSSR_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_NSSR_ID  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_NSSR_ID(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * OVRES_ID: Overrun Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . OVRES_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_OVRES_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_OVRES_ID  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_OVRES_ID(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * MODF_ID: Mode Fault Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . MODF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_MODF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_MODF_ID  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_MODF_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TDRE_ID: SPI Transmit Data Register Empty Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . TDRE_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_TDRE_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_TDRE_ID  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_TDRE_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RDRF_ID: Receive Data Register Full Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IDR . RDRF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IDR_RDRF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IDR_RDRF_ID  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IDR_RDRF_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Interrupt Mask Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_IMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_IMR(target)    VTSS_IOREG(target,0x107)

/**
 * \brief
 * RXFPTEF_IM: RXFPTEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . RXFPTEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_RXFPTEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_RXFPTEF_IM  VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_RXFPTEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * TXFPTEF_IM: TXFPTEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . TXFPTEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_TXFPTEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_TXFPTEF_IM  VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_TXFPTEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * RXFTHF_IM: RXFTHF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . RXFTHF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_RXFTHF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_RXFTHF_IM  VTSS_BIT(29)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_RXFTHF_IM(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * RXFFF_IM: RXFFF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . RXFFF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_RXFFF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_RXFFF_IM  VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_RXFFF_IM(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * RXFEF_IM: RXFEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . RXFEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_RXFEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_RXFEF_IM  VTSS_BIT(27)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_RXFEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * TXFTHF_IM: TXFTHF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . TXFTHF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_TXFTHF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_TXFTHF_IM  VTSS_BIT(26)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_TXFTHF_IM(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * TXFFF_IM: TXFFF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . TXFFF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_TXFFF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_TXFFF_IM  VTSS_BIT(25)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_TXFFF_IM(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * TXFEF_IM: TXFEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . TXFEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_TXFEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_TXFEF_IM  VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_TXFEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CMP_IM: Comparison Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . CMP_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_CMP_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_CMP_IM   VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_CMP_IM(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * UNDES_IM: Underrun Error Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . UNDES_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_UNDES_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_UNDES_IM  VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_UNDES_IM(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TXEMPTY_IM: Transmission Registers Empty Disable
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . TXEMPTY_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_TXEMPTY_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_TXEMPTY_IM  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_TXEMPTY_IM(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * NSSR_IM: NSS Rising Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . NSSR_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_NSSR_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_NSSR_IM  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_NSSR_IM(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * OVRES_IM: Overrun Error Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . OVRES_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_OVRES_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_OVRES_IM  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_OVRES_IM(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * MODF_IM: Mode Fault Error Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . MODF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_MODF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_MODF_IM  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_MODF_IM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TDRE_IM: SPI Transmit Data Register Empty Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . TDRE_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_TDRE_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_TDRE_IM  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_TDRE_IM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RDRF_IM: Receive Data Register Full Interrupt Mask
 *
 * \details
 * 0: The interrupt is not enabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_IMR . RDRF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_IMR_RDRF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_IMR_RDRF_IM  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_IMR_RDRF_IM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Chip Select (CS0) Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the SPI
 * Write Protection Mode Register.
 * Note: FLEX_SPI_CSRx must be written even if the user wants to use the
 * default reset values. The BITS field is not updated with the
 * translated value unless the register is written.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_CSR0
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_CSR0(target)   VTSS_IOREG(target,0x10c)

/**
 * \brief
 * DLYBCT_CS0: Delay Between Consecutive TransfersThis field defines the
 * delay between two consecutive transfers with the same peripheral without
 * removing the chip select.The delay is always inserted after each
 * transfer and before removing the chip select if needed.
 *
 * \details
 * When DLYBCT = 0, no delay between consecutive transfers is inserted and
 * the clock keeps its duty cycle over the character
 * transfers.
 * Otherwise, the following equations determine the delay:
 * If FLEX_SPI_MR.BRSRCCLK = 0: DLYBCT = Delay Between Consecutive
 * Transfers x fperipheral clock / 32
 * If FLEX_SPI_MR.BRSRCCLK = 1: DLYBCT = Delay Between Consecutive
 * Transfers x fGCLKPCKx / 32
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR0 . DLYBCT_CS0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR0_DLYBCT_CS0(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR0_DLYBCT_CS0     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR0_DLYBCT_CS0(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * DLYBS_CS0: Delay Before SPCKThis field defines the delay from NPCS
 * falling edge (activation) to the first valid SPCK transition.
 *
 * \details
 * When DLYBS = 0, the delay is half the SPCK clock period.
 * Otherwise, the following equations determine the delay:
 * If FLEX_SPI_MR.BRSRCCLK = 0: DLYBS = Delay Before SPCK x fperipheral
 * clock
 * If FLEX_SPI_MR.BRSRCCLK = 1: DLYBS = Delay Before SPCK x fGCLKPCKx
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR0 . DLYBS_CS0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR0_DLYBS_CS0(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR0_DLYBS_CS0     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR0_DLYBS_CS0(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * SCBR_CS0: Serial Clock Bit Rate
 *
 * \details
 * In Initiator mode, the SPI Interface uses a modulus counter to derive
 * the SPCK bit rate from the clock defined by the bit
 * BRSRCCLK. The bit rate is selected by writing a value from 1 to 255 in
 * the SCBR field. The following equations determine
 * the SPCK bit rate:
 *
 * If FLEX_SPI_MR.BRSRCCLK = 0: SCBR = fperipheral clock / SPCK Bit Rate
 * If FLEX_SPI_MR.BRSRCCLK = 1: SCBR = fGCLKPCKx / SPCK Bit Rate
 *
 * Programming the SCBR field to 0 is forbidden. Triggering a transfer
 * while SCBR is at 0 can lead to unpredictable results.
 *
 * If BRSRCCLK = 1 in FLEX_SPI_MR, SCBR must be programmed with a value
 * greater than 1.
 * At reset, SCBR is 0 and the user has to program it at a valid value
 * before performing the first transfer.
 *
 * Note: If one of the FLEX_SPI_CSRx.SCBR fields is set to 1, the other
 * FLEX_SPI_CSRx.SCBR fields must be set to 1 as well, if they
 * are used to process transfers. If they are not used to transfer data,
 * they can be set at any value.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR0 . SCBR_CS0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR0_SCBR_CS0(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR0_SCBR_CS0     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR0_SCBR_CS0(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * BITS_CS0: The BITS field determines the number of data bits transferred.
 * Reserved values should not be used.
 *
 * \details
 * 0 (8_BIT): 8 bits for transfer
 * 1 (9_BIT): 9 bits for transfer
 * 2 (10_BIT): 10 bits for transfer
 * 3 (11_BIT): 11 bits for transfer
 * 4 (12_BIT): 12 bits for transfer
 * 5 (13_BIT): 13 bits for transfer
 * 6 (14_BIT): 14 bits for transfer
 * 7 (15_BIT): 15 bits for transfer
 * 8 (16_BIT): 16 bits for transfer
 * 9-15 - Reserved
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR0 . BITS_CS0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR0_BITS_CS0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR0_BITS_CS0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR0_BITS_CS0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * CSAAT_CS0: Chip Select Active After Transfer
 *
 * \details
 * 0: The Peripheral Chip Select Line rises as soon as the last transfer is
 * achieved.
 * 1: The Peripheral Chip Select does not rise after the last transfer is
 * achieved. It remains active until a new transfer is
 * requested on a different chip select.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR0 . CSAAT_CS0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR0_CSAAT_CS0(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR0_CSAAT_CS0  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR0_CSAAT_CS0(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * CSNAAT_CS0: Chip Select Not Active After Transfer (Ignored if CSAAT = 1)
 *
 * \details
 * 0: The Peripheral Chip Select does not rise between two transfers if the
 * FLEX_SPI_TDR is reloaded before the end of the
 * first transfer and if the two transfers occur on the same Chip Select.
 * 1: The Peripheral Chip Select rises systematically after each transfer
 * performed on the same target. It remains inactive after
 * the end of transfer for a minimal duration of:
 *
 * If FLEX_SPI_MR.BRSRCCLK = 0: DLYBCS / fperipheral clock (if DLYBCS !=
 * 0).
 * If FLEX_SPI_MR.BRSRCCLK = 1: DLYBCS / fGCLK DLYBCS / fPCKx
 * If DLYBCS < 6, a minimum of six periods is introduced.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR0 . CSNAAT_CS0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR0_CSNAAT_CS0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR0_CSNAAT_CS0  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR0_CSNAAT_CS0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NCPHA_CS0: Clock Phase
 *
 * \details
 * 0: Data are changed on the leading edge of SPCK and captured on the
 * following edge of SPCK.
 * 1: Data are captured on the leading edge of SPCK and changed on the
 * following edge of SPCK.
 * NCPHA determines which edge of SPCK causes data to change and which edge
 * causes data to be captured. NCPHA is
 * used with CPOL to produce the required clock/data relationship between
 * initiator and target devices.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR0 . NCPHA_CS0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR0_NCPHA_CS0(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR0_NCPHA_CS0  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR0_NCPHA_CS0(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CPOL_CS0: Clock Polarity
 *
 * \details
 * 0: The inactive state value of SPCK is logic level zero.
 * 1: The inactive state value of SPCK is logic level one.
 * CPOL is used to determine the inactive state value of the serial clock
 * (SPCK). It is used with NCPHA to produce the
 * required clock/data relationship between initiator and target devices.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR0 . CPOL_CS0
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR0_CPOL_CS0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR0_CPOL_CS0  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR0_CPOL_CS0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Chip Select (CS1) Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the SPI
 * Write Protection Mode Register.
 * Note: FLEX_SPI_CSRx must be written even if the user wants to use the
 * default reset values. The BITS field is not updated with the
 * translated value unless the register is written.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_CSR1
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_CSR1(target)   VTSS_IOREG(target,0x10d)

/**
 * \brief
 * DLYBCT_CS1: Delay Between Consecutive TransfersThis field defines the
 * delay between two consecutive transfers with the same peripheral without
 * removing the chip select.The delay is always inserted after each
 * transfer and before removing the chip select if needed.
 *
 * \details
 * When DLYBCT = 0, no delay between consecutive transfers is inserted and
 * the clock keeps its duty cycle over the character
 * transfers.
 * Otherwise, the following equations determine the delay:
 * If FLEX_SPI_MR.BRSRCCLK = 0: DLYBCT = Delay Between Consecutive
 * Transfers x fperipheral clock / 32
 * If FLEX_SPI_MR.BRSRCCLK = 1: DLYBCT = Delay Between Consecutive
 * Transfers x fGCLKPCKx / 32
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR1 . DLYBCT_CS1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR1_DLYBCT_CS1(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR1_DLYBCT_CS1     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR1_DLYBCT_CS1(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * DLYBS_CS1: Delay Before SPCKThis field defines the delay from NPCS
 * falling edge (activation) to the first valid SPCK transition.
 *
 * \details
 * When DLYBS = 0, the delay is half the SPCK clock period.
 * Otherwise, the following equations determine the delay:
 * If FLEX_SPI_MR.BRSRCCLK = 0: DLYBS = Delay Before SPCK x fperipheral
 * clock
 * If FLEX_SPI_MR.BRSRCCLK = 1: DLYBS = Delay Before SPCK x fGCLKPCKx
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR1 . DLYBS_CS1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR1_DLYBS_CS1(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR1_DLYBS_CS1     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR1_DLYBS_CS1(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * SCBR_CS1: Serial Clock Bit Rate
 *
 * \details
 * In Initiator mode, the SPI Interface uses a modulus counter to derive
 * the SPCK bit rate from the clock defined by the bit
 * BRSRCCLK. The bit rate is selected by writing a value from 1 to 255 in
 * the SCBR field. The following equations determine
 * the SPCK bit rate:
 *
 * If FLEX_SPI_MR.BRSRCCLK = 0: SCBR = fperipheral clock / SPCK Bit Rate
 * If FLEX_SPI_MR.BRSRCCLK = 1: SCBR = fGCLKPCKx / SPCK Bit Rate
 *
 * Programming the SCBR field to 0 is forbidden. Triggering a transfer
 * while SCBR is at 0 can lead to unpredictable results.
 *
 * If BRSRCCLK = 1 in FLEX_SPI_MR, SCBR must be programmed with a value
 * greater than 1.
 * At reset, SCBR is 0 and the user has to program it at a valid value
 * before performing the first transfer.
 *
 * Note: If one of the FLEX_SPI_CSRx.SCBR fields is set to 1, the other
 * FLEX_SPI_CSRx.SCBR fields must be set to 1 as well, if they
 * are used to process transfers. If they are not used to transfer data,
 * they can be set at any value.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR1 . SCBR_CS1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR1_SCBR_CS1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR1_SCBR_CS1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR1_SCBR_CS1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * BITS_CS1: The BITS field determines the number of data bits transferred.
 * Reserved values should not be used.
 *
 * \details
 * 0 (8_BIT): 8 bits for transfer
 * 1 (9_BIT): 9 bits for transfer
 * 2 (10_BIT): 10 bits for transfer
 * 3 (11_BIT): 11 bits for transfer
 * 4 (12_BIT): 12 bits for transfer
 * 5 (13_BIT): 13 bits for transfer
 * 6 (14_BIT): 14 bits for transfer
 * 7 (15_BIT): 15 bits for transfer
 * 8 (16_BIT): 16 bits for transfer
 * 9-15 - Reserved
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR1 . BITS_CS1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR1_BITS_CS1(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR1_BITS_CS1     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR1_BITS_CS1(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * CSAAT_CS1: Chip Select Active After Transfer
 *
 * \details
 * 0: The Peripheral Chip Select Line rises as soon as the last transfer is
 * achieved.
 * 1: The Peripheral Chip Select does not rise after the last transfer is
 * achieved. It remains active until a new transfer is
 * requested on a different chip select.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR1 . CSAAT_CS1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR1_CSAAT_CS1(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR1_CSAAT_CS1  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR1_CSAAT_CS1(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * CSNAAT_CS1: Chip Select Not Active After Transfer (Ignored if CSAAT = 1)
 *
 * \details
 * 0: The Peripheral Chip Select does not rise between two transfers if the
 * FLEX_SPI_TDR is reloaded before the end of the
 * first transfer and if the two transfers occur on the same Chip Select.
 * 1: The Peripheral Chip Select rises systematically after each transfer
 * performed on the same target. It remains inactive after
 * the end of transfer for a minimal duration of:
 *
 * If FLEX_SPI_MR.BRSRCCLK = 0: DLYBCS / fperipheral clock (if DLYBCS !=
 * 0).
 * If FLEX_SPI_MR.BRSRCCLK = 1: DLYBCS / fGCLK DLYBCS / fPCKx
 * If DLYBCS < 6, a minimum of six periods is introduced.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR1 . CSNAAT_CS1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR1_CSNAAT_CS1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR1_CSNAAT_CS1  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR1_CSNAAT_CS1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NCPHA_CS1: Clock Phase
 *
 * \details
 * 0: Data are changed on the leading edge of SPCK and captured on the
 * following edge of SPCK.
 * 1: Data are captured on the leading edge of SPCK and changed on the
 * following edge of SPCK.
 * NCPHA determines which edge of SPCK causes data to change and which edge
 * causes data to be captured. NCPHA is
 * used with CPOL to produce the required clock/data relationship between
 * initiator and target devices.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR1 . NCPHA_CS1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR1_NCPHA_CS1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR1_NCPHA_CS1  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR1_NCPHA_CS1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CPOL_CS1: Clock Polarity
 *
 * \details
 * 0: The inactive state value of SPCK is logic level zero.
 * 1: The inactive state value of SPCK is logic level one.
 * CPOL is used to determine the inactive state value of the serial clock
 * (SPCK). It is used with NCPHA to produce the
 * required clock/data relationship between initiator and target devices.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CSR1 . CPOL_CS1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CSR1_CPOL_CS1(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CSR1_CPOL_CS1  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CSR1_CPOL_CS1(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI FIFO Mode Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_FMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_FMR(target)    VTSS_IOREG(target,0x110)

/**
 * \brief
 * RXFTHRES: Receive FIFO Threshold
 *
 * \details
 * 0 - FIFO_DEPTH_SPI: Defines the Receive FIFO threshold value (number of
 * data). The FLEX_SPI_SR.RXFTHF flag will be
 * set when Receive FIFO goes from "below" threshold state to "equal to or
 * above" threshold state.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMR . RXFTHRES
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMR_RXFTHRES(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMR_RXFTHRES     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMR_RXFTHRES(x)  VTSS_EXTRACT_BITFIELD(x,24,6)

/**
 * \brief
 * TXFTHRES: Transmit FIFO Threshold
 *
 * \details
 * 0 - FIFO_DEPTH_SPI: Defines the Transmit FIFO threshold value (number of
 * data). The FLEX_SPI_SR.TXFTHF flag will be
 * set when Transmit FIFO goes from "above" threshold state to "equal to or
 * below" threshold state.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMR . TXFTHRES
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMR_TXFTHRES(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMR_TXFTHRES     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMR_TXFTHRES(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * RXRDYM: Receive Data Register Full Mode
 *
 * \details
 * If FIFOs are enabled, the FLEX_SPI_SR.RDRF flag behaves as follows.
 * 0 (ONE_DATA): FLEX_SPI_SR.RDRF will be at level '1' when at least one
 * unread data is in the Receive FIFO.
 * 1 (TWO_DATA): FLEX_SPI_SR.RDRF will be at level '1' when at least two
 * unread data are in the Receive FIFO.
 * Cannot be used when FLEX_SPI_MR.MSTR = 1, or if FLEX_SPI_MR.PS = 1.
 * 2 (FOUR_DATA): FLEX_SPI_SR.RDRF will be at level '1' when at least four
 * unread data are in the Receive FIFO.
 * Cannot be used when FLEX_SPI_CSRx.BITS is greater than 0, or if
 * FLEX_SPI_MR.MSTR = 1, or if FLEX_SPI_MR.PS = 1.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMR . RXRDYM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMR_RXRDYM(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMR_RXRDYM     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMR_RXRDYM(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * TXRDYM: Transmit Data Register Empty Mode
 *
 * \details
 * If FIFOs are enabled, the FLEX_SPI_SR.TDRE flag behaves as follows.
 * 0 (ONE_DATA): FLEX_SPI_SR.TDRE will be at level '1' when at least one
 * data can be written in the Transmit FIFO.
 * 1 (TWO_DATA): FLEX_SPI_SR.TDRE will be at level '1' when at least two
 * data can be written in the Transmit FIFO.
 * Cannot be used if FLEX_SPI_MR.PS = 1.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FMR . TXRDYM
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FMR_TXRDYM(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FMR_TXRDYM     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FMR_TXRDYM(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief SPI FIFO Level Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_FLR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_FLR(target)    VTSS_IOREG(target,0x111)

/**
 * \brief
 * RXFL: Receive FIFO Level
 *
 * \details
 * 0: There is no unread data in the Receive FIFO.
 * 1- FIFO_DEPTH_SPI: Indicates the number of unread data in the Receive
 * FIFO.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FLR . RXFL
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FLR_RXFL(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FLR_RXFL     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FLR_RXFL(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * TXFL: Transmit FIFO Level
 *
 * \details
 * 0: There is no data in the Transmit FIFO.
 * 1- FIFO_DEPTH_SPI: Indicates the number of data in the Transmit FIFO.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_FLR . TXFL
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_FLR_TXFL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_FLEXCOM_FLEX_SPI_FLR_TXFL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_FLEXCOM_FLEX_SPI_FLR_TXFL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief SPI Comparison Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the SPI
 * Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_CMPR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_CMPR(target)   VTSS_IOREG(target,0x112)

/**
 * \brief
 * VAL2: Second Comparison Value for Received Character
 *
 * \details
 * 0 - 65535: The received character must be lower than or equal to the
 * value of VAL2 and higher than or equal to VAL1 to set
 * the FLEX_SPI_SR.CMP flag.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CMPR . VAL2
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CMPR_VAL2(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CMPR_VAL2     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CMPR_VAL2(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * VAL1: First Comparison Value for Received Character
 *
 * \details
 * 0 - 65535: The received character must be higher than or equal to the
 * value of VAL1 and lower than or equal to VAL2 to set
 * the FLEX_SPI_SR.CMP flag.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_CMPR . VAL1
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_CMPR_VAL1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FLEXCOM_FLEX_SPI_CMPR_VAL1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FLEXCOM_FLEX_SPI_CMPR_VAL1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief SPI Write Protection Mode Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_WPMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_WPMR(target)   VTSS_IOREG(target,0x139)

/**
 * \brief
 * WPKEY: Write Protection Key
 *
 * \details
 * Value = 0x535049 (PASSWD) Writing any other value in this field aborts
 * the write operation of bits WPEN, WPITEN and WPCREN.
 * Always reads as 0
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_WPMR . WPKEY
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_WPMR_WPKEY(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_FLEXCOM_FLEX_SPI_WPMR_WPKEY     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_FLEXCOM_FLEX_SPI_WPMR_WPKEY(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * WPCREN: Write Protection Control Enable
 *
 * \details
 * 0: Disables the write protection on control register if WPKEY
 * corresponds to 0x535049 ("SPI" in ASCII).
 * 1: Enables the write protection on control register if WPKEY corresponds
 * to 0x535049 ("SPI" in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_WPMR . WPCREN
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_WPMR_WPCREN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_WPMR_WPCREN  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_SPI_WPMR_WPCREN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * WPITEN: Write Protection Interrupt Enable
 *
 * \details
 * WPITEN: Write Protection Interrupt Enable
 * 0: Disables the write protection on interrupt registers if WPKEY
 * corresponds to 0x535049 ("SPI" in ASCII).
 * 1: Enables the write protection on interrupt registers if WPKEY
 * corresponds to 0x535049 ("SPI" in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_WPMR . WPITEN
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_WPMR_WPITEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_WPMR_WPITEN  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_SPI_WPMR_WPITEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPEN: Write Protection Enable
 *
 * \details
 * 0: Disables the write protection if WPKEY corresponds to 0x535049 ("SPI"
 * in ASCII).
 * 1: Enables the write protection if WPKEY corresponds to 0x535049 ("SPI"
 * in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_WPMR . WPEN
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_WPMR_WPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_WPMR_WPEN    VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_WPMR_WPEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Write Protection Status Register
 *
 * \details
 * Note: By default, any debugger or software read access to FLEX_US_WPSR
 * clears the WPVS flag. To prevent this flag from being
 * cleared on debugger read access, a specific bit must be enabled in the
 * SFR module.
 *
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_WPSR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_WPSR(target)   VTSS_IOREG(target,0x13a)

/**
 * \brief
 * WPVSRC: Write Protection Violation SourceWhen WPVS = 1, WPVSRC indicates
 * the register address offset at which a write access has been attempted.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_WPSR . WPVSRC
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_WPSR_WPVSRC(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_SPI_WPSR_WPVSRC     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_SPI_WPSR_WPVSRC(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * WPVS: Write Protection Violation Status
 *
 * \details
 * 0: No write protect violation has occurred since the last read of
 * FLEX_SPI_WPSR.
 * 1: A write protect violation has occurred since the last read of
 * FLEX_SPI_WPSR. If this violation is an unauthorized
 * attempt to write a protected register, the associated violation is
 * reported into field WPVSRC.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_WPSR . WPVS
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_WPSR_WPVS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_SPI_WPSR_WPVS    VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_SPI_WPSR_WPVS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Version Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_SPI_REG:FLEX_SPI_VERSION
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_SPI_VERSION(target)  VTSS_IOREG(target,0x13f)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_VERSION . MFN
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_VERSION_MFN(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_SPI_VERSION_MFN     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_SPI_VERSION_MFN(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the internal version of the
 * macrocell.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_SPI_VERSION . VERSION
 */
#define  VTSS_F_FLEXCOM_FLEX_SPI_VERSION_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_FLEXCOM_FLEX_SPI_VERSION_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_FLEXCOM_FLEX_SPI_VERSION_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * Register Group: \a FLEXCOM:FLEXCOM_TWI_REG
 *
 * TWI Register Group
 */


/**
 * \brief TWI Control Register
 *
 * \details
 * This register can only be written if the WPCREN bit is cleared in the
 * TWI Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_CR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_CR(target)     VTSS_IOREG(target,0x180)

/**
 * \brief
 * FIFODIS: FIFO Disable
 *
 * \details
 * 0: No effect.
 * 1: Disable the Transmit and Receive FIFOs
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . FIFODIS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_FIFODIS(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_FIFODIS   VTSS_BIT(29)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_FIFODIS(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * FIFOEN: FIFO Enable
 *
 * \details
 * 0: No effect.
 * 1: Enable the Transmit and Receive FIFOs
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . FIFOEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_FIFOEN(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_FIFOEN    VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_FIFOEN(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * LOCKCLR: Lock Clear
 *
 * \details
 * 0: No effect.
 * 1: Clear the TWI FSM lock.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . LOCKCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_LOCKCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_LOCKCLR   VTSS_BIT(26)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_LOCKCLR(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * THRCLR: Transmit Holding Register Clear
 *
 * \details
 * 0: No effect.
 * 1: Clear the Transmit Holding Register and set TXRDY, TXCOMP flags.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . THRCLR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_THRCLR(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_THRCLR    VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_THRCLR(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * ACMDIS: Alternative Command Mode Disable
 *
 * \details
 * 0: No effect.
 * 1: Alternative Command mode disabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . ACMDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_ACMDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_ACMDIS    VTSS_BIT(17)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_ACMDIS(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * ACMEN: Alternative Command Mode Enable
 *
 * \details
 * 0: No effect.
 * 1: Alternative Command mode enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . ACMEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_ACMEN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_ACMEN     VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_ACMEN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * CLEAR: Bus CLEAR Command
 *
 * \details
 * 0: No effect.
 * 1: If Initiator mode is enabled, send a bus clear command.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . CLEAR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_CLEAR(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_CLEAR     VTSS_BIT(15)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_CLEAR(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * PECRQ: PEC Request
 *
 * \details
 * 0: No effect.
 * 1: A PEC check or transmission is requested.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . PECRQ
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_PECRQ(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_PECRQ     VTSS_BIT(14)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_PECRQ(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * PECDIS: Packet Error Checking Disable
 *
 * \details
 * 0: No effect.
 * 1: SMBus PEC (CRC) generation and check disabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . PECDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_PECDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_PECDIS    VTSS_BIT(13)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_PECDIS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * PECEN: Packet Error Checking Enable
 *
 * \details
 * 0: No effect.
 * 1: SMBus PEC (CRC) generation and check enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . PECEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_PECEN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_PECEN     VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_PECEN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * SMBDIS: SMBus Mode Disabled
 *
 * \details
 * 0: No effect.
 * 1: SMBus mode disabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . SMBDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_SMBDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_SMBDIS    VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_SMBDIS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * SMBEN: SMBus Mode Enabled
 *
 * \details
 * 0: No effect.
 * 1: If SMBDIS = 0, SMBus mode enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . SMBEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_SMBEN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_SMBEN     VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_SMBEN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * HSDIS: TWI High-Speed Mode Disabled
 *
 * \details
 * 0: No effect.
 * 1: High-speed mode disabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . HSDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_HSDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_HSDIS     VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_HSDIS(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * HSEN: TWI High-Speed Mode Enabled
 *
 * \details
 * 0: No effect.
 * 1: High-speed mode enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . HSEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_HSEN(x)   VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_HSEN      VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_HSEN(x)   VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * SWRST: Software Reset
 *
 * \details
 * 0: No effect.
 * 1: Equivalent to a system reset.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . SWR_RST
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_SWR_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_SWR_RST   VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_SWR_RST(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * QUICK: SMBus Quick Command
 *
 * \details
 * 0: No effect.
 * 1: If Initiator mode is enabled, a SMBus Quick Command is sent.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . QUICK
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_QUICK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_QUICK     VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_QUICK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * SVDIS: TWI Target Mode Disabled
 *
 * \details
 * 0: No effect.
 * 1: The Target mode is disabled. The shifter and holding characters (if
 * it contains data) are transmitted in case of read operation.
 * In write operation, the character being transferred must be completely
 * received before disabling.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . SVDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_SVDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_SVDIS     VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_SVDIS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * SVEN: TWI Target Mode Enabled
 *
 * \details
 * 0: No effect.
 * 1: Enables the Target mode (SVDIS must be written to 0).
 * Note: Switching from Initiator to Target mode is only permitted when
 * TXCOMP = 1.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . SVEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_SVEN(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_SVEN      VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_SVEN(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MSDIS: TWI Initiator Mode Disabled
 *
 * \details
 * 0: No effect.
 * 1: The Initiator mode is disabled, all pending data is transmitted. The
 * shifter and holding characters (if it contains data) are
 * transmitted in case of write operation. In read operation, the character
 * being transferred must be completely received
 * before disabling.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . MSDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_MSDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_MSDIS     VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_MSDIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * MSEN: TWI Initiator Mode Enabled
 *
 * \details
 * 0: No effect.
 * 1: Enables the Initiator mode (MSDIS must be written to 0).
 * Note: Switching from Target to Initiator mode is only permitted when
 * TXCOMP = 1.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . MSEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_MSEN(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_MSEN      VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_MSEN(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * STOP: Send a STOP Condition
 *
 * \details
 * 0: No effect.
 * 1: STOP condition is sent just after completing the current byte
 * transmission in Initiator Read mode.
 *     - In single data byte initiator read, both START and STOP must be
 * set.
 *     - In multiple data bytes initiator read, the STOP must be set after
 * the last data received but one.
 *     - In Initiator Read mode, if a NACK bit is received, the STOP is
 * automatically performed.
 *     - In initiator data write operation, a STOP condition will be sent
 * after the transmission of the current data is finished.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . STOP
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_STOP(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_STOP      VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_STOP(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * START: Send a START Condition
 *
 * \details
 * 0: No effect.
 * 1: A frame beginning with a START bit is transmitted according to the
 * features defined in the TWI Initiator Mode Register (FLEX_TWI_MMR).
 * This action is necessary when the TWI peripheral needs to read data from
 * a target. When configured in Initiator mode with a
 * write operation, a frame is sent as soon as the user writes a character
 * in the Transmit Holding Register (FLEX_TWI_THR).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CR . START
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CR_START(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CR_START     VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CR_START(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Initiator Mode Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_MMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_MMR(target)    VTSS_IOREG(target,0x181)

/**
 * \brief
 * NOAP: No Auto-Stop On NACK Error
 *
 * \details
 * 0: A stop condition is sent automatically upon Not-Acknowledge error
 * detection.
 * 1: No automatic action is performed upon Not-Acknowledge error
 * detection.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_MMR . NOAP
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_MMR_NOAP(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_MMR_NOAP     VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_TWI_MMR_NOAP(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * DADR: Device AddressThe device address is used to access target devices
 * in Read or Write mode. Those bits are only used in Initiator mode.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_MMR . DADR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_MMR_DADR(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_FLEXCOM_FLEX_TWI_MMR_DADR     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_MMR_DADR(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * SCLRBL: SCL Rise Boost LevelNumber of clock periods during which SCL
 * rise is boosted (meaning line drived to level '1').
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_MMR . SCLRBL
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_MMR_SCLRBL(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_FLEXCOM_FLEX_TWI_MMR_SCLRBL     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_MMR_SCLRBL(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * MREAD: Initiator Read Direction
 *
 * \details
 * 0: Initiator write direction.
 * 1: Initiator read direction.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_MMR . MREAD
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_MMR_MREAD(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_MMR_MREAD    VTSS_BIT(12)
#define  VTSS_X_FLEXCOM_FLEX_TWI_MMR_MREAD(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * IADRSZ: Internal Device Address Size
 *
 * \details
 * 0 (NONE): No internal device address.
 * 1 (1_BYTE): One-byte internal device address.
 * 2 (2_BYTE): Two-byte internal device address.
 * 3 (3_BYTE): Three-byte internal device address.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_MMR . IADRSZ
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_MMR_IADRSZ(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_FLEXCOM_FLEX_TWI_MMR_IADRSZ     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_MMR_IADRSZ(x)  VTSS_EXTRACT_BITFIELD(x,8,2)


/**
 * \brief TWI Target Mode Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the TWI
 * Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_SMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_SMR(target)    VTSS_IOREG(target,0x182)

/**
 * \brief
 * DATAMEN: Data Matching Enable
 *
 * \details
 * 0: Data matching on first received data is disabled.
 * 1: Data matching on first received data is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . DATAMEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_DATAMEN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_DATAMEN  VTSS_BIT(31)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_DATAMEN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * SADR3EN: Target Address 3 Enable
 *
 * \details
 * 0: Target address 3 matching is disabled.
 * 1: Target address 3 matching is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SADR3EN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SADR3EN(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SADR3EN  VTSS_BIT(30)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SADR3EN(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * SADR2EN: Target Address 2 Enable
 *
 * \details
 * 0: Target address 2 matching is disabled.
 * 1: Target address 2 matching is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SADR2EN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SADR2EN(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SADR2EN  VTSS_BIT(29)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SADR2EN(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * SADR1EN: Target Address 1 Enable
 *
 * \details
 * 0: Target address 1 matching is disabled.
 * 1: Target address 1 matching is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SADR1EN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SADR1EN(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SADR1EN  VTSS_BIT(28)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SADR1EN(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * SADR: Target AddressThe target device address is used in Target mode in
 * order to be accessed by initiator devices in Read or Write mode.SADR
 * must be programmed before enabling the Target mode or after a general
 * call. Writes at other times have no effect.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SADR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SADR(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SADR     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SADR(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * MASK: Target Address MaskA mask can be applied on the target device
 * address in Target mode in order to allow multiple address answer. For
 * each bitof the MASK field set to one, the corresponding SADR bit will be
 * masked.If the MASK field is set to 0, no mask is applied to the SADR
 * field.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . MASK
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_MASK     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * SNIFF: Target Sniffer Mode
 *
 * \details
 * 0: Target Sniffer mode is disabled.
 * 1: Target Sniffer mode is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SNIFF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SNIFF(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SNIFF    VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SNIFF(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SCLWSDIS: Clock Wait State Disable
 *
 * \details
 * 0: No effect.
 * 1: Clock stretching disabled in Target mode, OVRE and UNRE will indicate
 * overrun and underrun.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SCLWSDIS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SCLWSDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SCLWSDIS  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SCLWSDIS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * SADAT: Target Address Treated as Data
 *
 * \details
 * 0: Target address is handled normally (will not trig RXRDY flag and will
 * not fill FLEX_TWI_RHR upon reception).
 * 1: Target address is handled as data field, RXRDY will be set and
 * FLEX_TWI_RHR filled upon target address reception.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SADAT
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SADAT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SADAT    VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SADAT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * SMHH: SMBus Host Header
 *
 * \details
 * 0: Acknowledge of the SMBus Host Header disabled.
 * 1: Acknowledge of the SMBus Host Header enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SMHH
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SMHH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SMHH     VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SMHH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * SMDA: SMBus Default Address
 *
 * \details
 * 0: Acknowledge of the SMBus Default Address disabled.
 * 1: Acknowledge of the SMBus Default Address enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . SMDA
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_SMDA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_SMDA     VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_SMDA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NACKEN: Target Receiver Data Phase NACK Enable
 *
 * \details
 * 0: Normal value to be returned in the ACK cycle of the data phase in
 * Target Receiver mode.
 * 1: NACK value to be returned in the ACK cycle of the data phase in
 * Target Receiver mode.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMR . NACKEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMR_NACKEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMR_NACKEN   VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMR_NACKEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Internal Address Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_IADR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_IADR(target)   VTSS_IOREG(target,0x183)

/**
 * \brief
 * IADR: Internal Address0, 1, 2 or 3 bytes depending on IADRSZ.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IADR . IADR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IADR_IADR(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IADR_IADR     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IADR_IADR(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief TWI Clock Waveform Generator Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the TWI
 * Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_CWGR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_CWGR(target)   VTSS_IOREG(target,0x184)

/**
 * \brief
 * HOLD: TWD Hold Time Versus TWCK FallingIf High-speed mode is selected
 * TWD is internally modified on the TWCK falling edge to meet the I2C
 * specified maximumhold time, else if High-speed mode is not configured
 * TWD is kept unchanged after TWCK falling edge for a period of(HOLD + 3)
 * x tperipheral clock.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CWGR . HOLD
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CWGR_HOLD(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CWGR_HOLD     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CWGR_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,24,6)

/**
 * \brief
 * BRSRCCLK: Bit Rate Source Clock
 *
 * \details
 * 0 (PERIPH_CLK): The peripheral clock is the source clock for the bit
 * rate generation.
 * 1 (GCLKPMC_PCK): GCLKPMC_PCKx is the source clock for the bit rate
 * generation, thus the bit rate can be independent
 * of the core/peripheral clock.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CWGR . BRSRCCLK
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CWGR_BRSRCCLK(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CWGR_BRSRCCLK  VTSS_BIT(20)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CWGR_BRSRCCLK(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * CKDIV: Clock DividerThe CKDIV is used to increase both SCL high and low
 * periods.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CWGR . CKDIV
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CWGR_CKDIV(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CWGR_CKDIV     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CWGR_CKDIV(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * CHDIV: Clock High Divider
 *
 * \details
 * The SCL high period is defined as follows:
 * If BRSRCCLK = 0: CHDIV = ((thigh / tperipheral clock) - 3) / 2 ^ CKDIV
 * If BRSRCCLK = 1: CHDIV = (thigh / text_ck) / 2 ^ CKDIV
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CWGR . CHDIV
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CWGR_CHDIV(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CWGR_CHDIV     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CWGR_CHDIV(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * CLDIV: Clock Low Divider
 *
 * \details
 * The SCL low period is defined as follows:
 * If BRSRCCLK = 0: CLDIV = ((tlow / tperipheral clock) - 3) / 2 ^ CKDIV
 * If BRSRCCLK = 1: CLDIV = (tlow / text_ck) / 2 ^ CKDIV
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_CWGR . CLDIV
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_CWGR_CLDIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_CWGR_CLDIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_CWGR_CLDIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TWI Status Register
 *
 * \details
 * Note: If enabled in the SFR module (default is disabled), a debugger
 * read access does not clear the clear-on-read flags.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_SR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_SR(target)     VTSS_IOREG(target,0x188)

/**
 * \brief
 * SR: Start Repeated
 *
 * \details
 * 0: No repeated start has been detected since last FLEX_TWI_SR read.
 * 1: At least one repeated start has been detected since last FLEX_TWI_SR
 * read.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . SR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_SR(x)     VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_SR        VTSS_BIT(26)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_SR(x)     VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * SDA: SDA Line Value
 *
 * \details
 * 0: SDA line sampled value is '0'.
 * 1: SDA line sampled value is '1'.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . SDA
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_SDA(x)    VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_SDA       VTSS_BIT(25)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_SDA(x)    VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * SCL: SCL Line Value
 *
 * \details
 * 0: SCL line sampled value is '0'.
 * 1: SCL line sampled value is '1'.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . SCL
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_SCL(x)    VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_SCL       VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_SCL(x)    VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * LOCK: TWI Lock Due to Frame Errors
 *
 * \details
 * 0: The TWI is not locked.
 * 1: The TWI is locked due to frame errors.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . LOCK
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_LOCK(x)   VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_LOCK      VTSS_BIT(23)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_LOCK(x)   VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * SMBHHM: SMBus Host Header Address Match (cleared on read)
 *
 * \details
 * 0: No SMBus Host Header Address received.
 * 1: A SMBus Host Header Address was received.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . SMBHHM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_SMBHHM(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_SMBHHM    VTSS_BIT(21)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_SMBHHM(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * SMBDAM: SMBus Default Address Match (cleared on read)
 *
 * \details
 * 0: No SMBus Host Header Address received.
 * 1: A SMBus Host Header Address was received.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . SMBDAM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_SMBDAM(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_SMBDAM    VTSS_BIT(20)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_SMBDAM(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * PECERR: PEC Error (cleared on read)
 *
 * \details
 * 0: No SMBus PEC error occurred.
 * 1: A SMBus PEC error occurred.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . PECERR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_PECERR(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_PECERR    VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_PECERR(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * TOUT: Timeout Error (cleared on read)
 *
 * \details
 * 0: No SMBus timeout occurred.
 * 1: SMBus timeout occurred.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . TOUT
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_TOUT(x)   VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_TOUT      VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_TOUT(x)   VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MCACK: Initiator Code Acknowledge (cleared on read)
 *
 * \details
 * MACK used in Target mode:
 * 0: No initiator code has been received.
 * 1: A initiator code has been received.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . MCACK
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_MCACK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_MCACK     VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_MCACK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * EOSACC: End Of Target Access (cleared on read)
 *
 * \details
 * This bit is only used in Target mode.
 * 0: A target access is being performing.
 * 1: The Target Access is finished. End Of Target Access is automatically
 * set as soon as SVACC is reset.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . EOASACC
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_EOASACC(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_EOASACC   VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_EOASACC(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * SCLWS: Clock Wait State
 *
 * \details
 * This bit is only used in Target mode.
 * 0: The clock is not stretched.
 * 1: The clock is stretched. FLEX_TWI_THR / FLEX_TWI_RHR buffer is not
 * filled / emptied before the transmission / reception
 * of a new character.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . SCLWS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_SCLWS(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_SCLWS     VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_SCLWS(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * ARBLST: Arbitration Lost (cleared on read)
 *
 * \details
 * This bit is only used in Initiator mode.
 * 0: Arbitration won.
 * 1: Arbitration lost. Another initiator of the TWI bus has won the
 * multi-initiator arbitration. TXCOMP is set at the same time.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . ARBLST
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_ARBLST(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_ARBLST    VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_ARBLST(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * NACK: Not Acknowledged (cleared on read)
 *
 * \details
 * NACK used in Initiator mode:
 * 0: Each data byte has been correctly received by the far-end side TWI
 * target component.
 * 1: A data or address byte has not been acknowledged by the target
 * component. Set at the same time as TXCOMP.
 *
 * NACK used in Target Read mode:
 * 0: Each data byte has been correctly received by the initiator.
 * 1: In Read mode, a data byte has not been acknowledged by the initiator.
 * When NACK is set, the user must not fill
 * FLEX_TWI_THR even if TXRDY is set, because it means that the initiator
 * will stop the data transfer or reinitiate it.
 *
 * Note that in Target Write mode all data are acknowledged by the TWI.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . NACK
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_NACK(x)   VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_NACK      VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_NACK(x)   VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * UNRE: Underrun Error (cleared on read)
 *
 * \details
 * This bit is only used in Target mode if clock stretching is disabled.
 * 0: FLEX_TWI_THR has been filled on time.
 * 1: FLEX_TWI_THR has not been filled on time.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . UNRE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_UNRE(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_UNRE      VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_UNRE(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * OVRE: Overrun Error (cleared on read)
 *
 * \details
 * This bit is only used in Target mode if clock stretching is disabled.
 * 0: FLEX_TWI_RHR has not been loaded while RXRDY was set.
 * 1: FLEX_TWI_RHR has been loaded while RXRDY was set. Reset by read in
 * FLEX_TWI_SR when TXCOMP is set.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . OVRE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_OVRE(x)   VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_OVRE      VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_OVRE(x)   VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * GACC: General Call Access (cleared on read)
 *
 * \details
 * This bit is only used in Target mode.
 * 0: No general call has been detected.
 * 1: A general call has been detected. After the detection of general
 * call, if need be, the user may acknowledge this access
 * and decode the following bytes and respond according to the value of the
 * bytes.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . GACC
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_GACC(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_GACC      VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_GACC(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * SVACC: Target Access
 *
 * \details
 * This bit is only used in Target mode.
 * 0: TWI is not addressed. SVACC is automatically cleared after a NACK or
 * a STOP condition is detected.
 * 1: Indicates that the address decoding sequence has matched (a initiator
 * has sent SADR). SVACC remains high until a
 * NACK or a STOP condition is detected.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . SVACC
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_SVACC(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_SVACC     VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_SVACC(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * SVREAD: Target Read
 *
 * \details
 * This bit is only used in Target mode. When SVACC is low (no target
 * access has been detected) SVREAD is irrelevant.
 * 0: Indicates that a write access is performed by a initiator.
 * 1: Indicates that a read access is performed by a initiator.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . SVREAD
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_SVREAD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_SVREAD    VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_SVREAD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXRDY: Transmit Holding Register Ready (cleared by writing FLEX_TWI_THR)
 *
 * \details
 * TXRDY used in Initiator mode:
 * 0: The transmit holding register has not been transferred into the
 * internal shifter. Set to 0 when writing into
 * FLEX_TWI_THR.
 * 1: As soon as a data byte is transferred from FLEX_TWI_THR to internal
 * shifter or if a NACK error is detected, TXRDY is
 * set at the same time as TXCOMP and NACK. TXRDY is also set when MSEN is
 * set (enables TWI).
 *
 * TXRDY used in Target mode:
 * 0: As soon as data is written in FLEX_TWI_THR, until this data has been
 * transmitted and acknowledged (ACK or NACK).
 * 1: Indicates that FLEX_TWI_THR is empty and that data has been
 * transmitted and acknowledged.
 * If TXRDY is high and if a NACK has been detected, the transmission will
 * be stopped. Thus when TRDY = NACK = 1, the
 * user must not fill FLEX_TWI_THR to avoid losing it.
 *
 * When FIFOs are enabled:
 * 0: Transmit FIFO is full and cannot accept more data
 * 1: Transmit FIFO is not full; one or more data can be written according
 * to TXRDYM field configuration
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . TXRDY
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_TXRDY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_TXRDY     VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_TXRDY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * RXRDY: Receive Holding Register Ready (cleared when reading
 * FLEX_TWI_RHR)
 *
 * \details
 * When FIFOs are disabled:
 * 0: No character has been received since the last FLEX_TWI_RHR read
 * operation.
 * 1: A byte has been received in FLEX_TWI_RHR since the last read.
 *
 * When FIFOs are enabled:
 * 0: Receive FIFO is empty; no data to read
 * 1: At least one unread data is in the Receive FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . RXRDY
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_RXRDY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_RXRDY     VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_RXRDY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXCOMP: Transmission Completed (cleared by writing FLEX_TWI_THR)
 *
 * \details
 * TXCOMP used in Initiator mode:
 * 0: During the length of the current frame.
 * 1: When both the holding register and the internal shifter are empty and
 * STOP condition has been sent.
 *
 * TXCOMP used in Target mode:
 * 0: As soon as a Start is detected.
 * 1: After a Stop or a Repeated Start + an address different from SADR is
 * detected.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SR . TXCOMP
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SR_TXCOMP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SR_TXCOMP    VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SR_TXCOMP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Interrupt Enable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * TWI Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_IER
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_IER(target)    VTSS_IOREG(target,0x189)

/**
 * \brief
 * SMBHHM_IE: SMBus Host Header Address Match Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . SMBHHM_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_SMBHHM_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_SMBHHM_IE  VTSS_BIT(21)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_SMBHHM_IE(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * SMBDAM_IE: SMBus Default Address Match Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . SMBDAM_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_SMBDAM_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_SMBDAM_IE  VTSS_BIT(20)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_SMBDAM_IE(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * PECERR_IE: PEC Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . PECERR_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_PECERR_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_PECERR_IE  VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_PECERR_IE(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * TOUT_IE: Timeout Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . TOUT_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_TOUT_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_TOUT_IE  VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_TOUT_IE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MCACK_IE: Initiator Code Acknowledge Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . MCACK_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_MCACK_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_MCACK_IE  VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_MCACK_IE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * EOSACC_IE: End Of Target Access Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . EOASACC_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_EOASACC_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_EOASACC_IE  VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_EOASACC_IE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * SCLWS_IE: Clock Wait State Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . SCLWS_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_SCLWS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_SCLWS_IE  VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_SCLWS_IE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * ARBLST_IE: Arbitration Lost Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . ARBLST_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_ARBLST_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_ARBLST_IE  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_ARBLST_IE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * NACK_IE: Not Acknowledged Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . NACK_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_NACK_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_NACK_IE  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_NACK_IE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * UNRE_IE: Underrun Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . UNRE_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_UNRE_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_UNRE_IE  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_UNRE_IE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * OVRE_IE: Overrun Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . OVRE_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_OVRE_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_OVRE_IE  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_OVRE_IE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * GACC_IE: General Call Access Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . GACC_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_GACC_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_GACC_IE  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_GACC_IE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * SVACC_IE: Target Access Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . SVACC_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_SVACC_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_SVACC_IE  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_SVACC_IE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * TXRDY_IE: Transmit Holding Register Ready Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . TXRDY_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_TXRDY_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_TXRDY_IE  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_TXRDY_IE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * RXRDY_IE: Receive Holding Register Ready Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . RXRDY_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_RXRDY_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_RXRDY_IE  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_RXRDY_IE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXCOMP_IE: Transmission Completed Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IER . TXCOMP_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IER_TXCOMP_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IER_TXCOMP_IE  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IER_TXCOMP_IE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Interrupt Disable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * TWI Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_IDR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_IDR(target)    VTSS_IOREG(target,0x18a)

/**
 * \brief
 * SMBHHM_ID: SMBus Host Header Address Match Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . SMBHHM_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_SMBHHM_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_SMBHHM_ID  VTSS_BIT(21)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_SMBHHM_ID(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * SMBDAM_ID: SMBus Default Address Match Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . SMBDAM_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_SMBDAM_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_SMBDAM_ID  VTSS_BIT(20)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_SMBDAM_ID(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * PECERR_ID: PEC Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . PECERR_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_PECERR_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_PECERR_ID  VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_PECERR_ID(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * TOUT_ID: Timeout Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . TOUT_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_TOUT_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_TOUT_ID  VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_TOUT_ID(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MCACK_ID: Initiator Code Acknowledge Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . MCACK_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_MCACK_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_MCACK_ID  VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_MCACK_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * EOSACC_ID: End Of Target Access Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . EOASACC_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_EOASACC_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_EOASACC_ID  VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_EOASACC_ID(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * SCLWS_ID: Clock Wait State Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . SCLWS_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_SCLWS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_SCLWS_ID  VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_SCLWS_ID(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * ARBLST_ID: Arbitration Lost Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . ARBLST_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_ARBLST_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_ARBLST_ID  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_ARBLST_ID(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * NACK_ID: Not Acknowledged Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . NACK_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_NACK_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_NACK_ID  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_NACK_ID(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * UNRE_ID: Underrun Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . UNRE_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_UNRE_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_UNRE_ID  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_UNRE_ID(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * OVRE_ID: Overrun Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . OVRE_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_OVRE_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_OVRE_ID  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_OVRE_ID(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * GACC_ID: General Call Access Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . GACC_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_GACC_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_GACC_ID  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_GACC_ID(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * SVACC_ID: Target Access Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . SVACC_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_SVACC_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_SVACC_ID  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_SVACC_ID(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * TXRDY_ID: Transmit Holding Register Ready Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . TXRDY_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_TXRDY_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_TXRDY_ID  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_TXRDY_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * RXRDY_ID: Receive Holding Register Ready Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . RXRDY_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_RXRDY_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_RXRDY_ID  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_RXRDY_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXCOMP_ID: Transmission Completed Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IDR . TXCOMP_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IDR_TXCOMP_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IDR_TXCOMP_ID  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IDR_TXCOMP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Interrupt Mask Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_IMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_IMR(target)    VTSS_IOREG(target,0x18b)

/**
 * \brief
 * SMBHHM_IM: SMBus Host Header Address Match Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . SMBHHM_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_SMBHHM_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_SMBHHM_IM  VTSS_BIT(21)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_SMBHHM_IM(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * SMBDAM_IM: SMBus Default Address Match Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . SMBDAM_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_SMBDAM_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_SMBDAM_IM  VTSS_BIT(20)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_SMBDAM_IM(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * PECERR_IM: PEC Error Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . PECERR_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_PECERR_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_PECERR_IM  VTSS_BIT(19)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_PECERR_IM(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * TOUT_IM: Timeout Error Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . TOUT_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_TOUT_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_TOUT_IM  VTSS_BIT(18)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_TOUT_IM(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MCACK_IM: Initiator Code Acknowledge Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . MCACK_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_MCACK_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_MCACK_IM  VTSS_BIT(16)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_MCACK_IM(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * EOSACC_IM: End Of Target Access Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . EOASACC_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_EOASACC_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_EOASACC_IM  VTSS_BIT(11)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_EOASACC_IM(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * SCLWS_IM: Clock Wait State Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . SCLWS_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_SCLWS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_SCLWS_IM  VTSS_BIT(10)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_SCLWS_IM(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * ARBLST_IM: Arbitration Lost Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . ARBLST_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_ARBLST_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_ARBLST_IM  VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_ARBLST_IM(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * NACK_IM: Not Acknowledged Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . NACK_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_NACK_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_NACK_IM  VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_NACK_IM(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * UNRE_IM: Underrun Error Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . UNRE_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_UNRE_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_UNRE_IM  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_UNRE_IM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * OVRE_IM: Overrun Error Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . OVRE_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_OVRE_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_OVRE_IM  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_OVRE_IM(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * GACC_IM: General Call Access Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . GACC_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_GACC_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_GACC_IM  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_GACC_IM(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * SVACC_IM: Target Access Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . SVACC_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_SVACC_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_SVACC_IM  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_SVACC_IM(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * TXRDY_IM: Transmit Holding Register Ready Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . TXRDY_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_TXRDY_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_TXRDY_IM  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_TXRDY_IM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * RXRDY_IM: Receive Holding Register Ready Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . RXRDY_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_RXRDY_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_RXRDY_IM  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_RXRDY_IM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXCOMP_IM: Transmission Completed Interrupt Disable
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_IMR . TXCOMP_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_IMR_TXCOMP_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_IMR_TXCOMP_IM  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_IMR_TXCOMP_IM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Receive Holding Register
 *
 * \details
 * Note: If FIFO is enabled (FLEX_TWI_CR.FIFOEN bit) and
 * FLEX_TWI_FMR.RXRDYM = 0, the Receive FIFO operates in Single Data Mode.
 * Note: If FIFO is enabled (FLEX_TWI_CR.FIFOEN bit) and
 * FLEX_TWI_FMR.RXRDYM > 0, the Receive FIFO operates in Multi Data Mode.
 * Note: If enabled in the SFR module (default is disabled), a debugger
 * read access does not clear the FLEX_TWI_SR.RXRDY flag.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_RHR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_RHR(target)    VTSS_IOREG(target,0x18c)

/**
 * \brief
 * RXDATA: Initiator or Target Receive Holding Data
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_RHR . RXDATA
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_RHR_RXDATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_RHR_RXDATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_RHR_RXDATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TWI Receive Holding Register (FIFO Enabled)
 *
 * \details
 * Note: If FIFO is enabled (FLEX_TWI_CR.FIFOEN bit) and
 * FLEX_TWI_FMR.RXRDYM > 0, the Receive FIFO operates in Multi Data Mode.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FMT_RHR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FMT_RHR(target)  VTSS_IOREG(target,0x18c)

/**
 * \brief
 * RXDATA3: Initiator or Target Receive Holding Data 3
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMT_RHR . RXDATA3
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * RXDATA2: Initiator or Target Receive Holding Data 2
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMT_RHR . RXDATA2
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RXDATA1: Initiator or Target Receive Holding Data 1
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMT_RHR . RXDATA1
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * RXDATA0: Initiator or Target Receive Holding Data 0
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMT_RHR . RXDATA0
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMT_RHR_RXDATA0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TWI Transmit Holding Register
 *
 * \details
 * Note: If FIFO is enabled (FIFOEN bit in FLEX_TWI_CR) and
 * FLEX_TWI_FMR.TXRDYM = 0, the Transmit FIFO operates in Single Data Mode.
 * Note: If FIFO is enabled (FLEX_US_CR.FIFOEN bit) and FLEX_TWI_FMR.TXRDYM
 * > 0, the Trasmit FIFO operates in Multi Data Mode.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_THR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_THR(target)    VTSS_IOREG(target,0x18d)

/**
 * \brief
 * TXDATA: Initiator or Target Transmit Holding Data
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_THR . TXDATA
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_THR_TXDATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_THR_TXDATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_THR_TXDATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TWI Transmit Holding Register (FIFO Enabled)
 *
 * \details
 * Note: If FIFO is enabled (FLEX_US_CR.FIFOEN bit) and FLEX_TWI_FMR.TXRDYM
 * > 0, the Trasmit FIFO operates in Multi Data Mode.
 * Note: If FIFO is enabled (FIFOEN bit in FLEX_TWI_CR) and
 * FLEX_TWI_FMR.TXRDYM = 0, the Transmit FIFO operates in Single Data Mode.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FMT_THR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FMT_THR(target)  VTSS_IOREG(target,0x18d)

/**
 * \brief
 * TXDATA3: Initiator or Target Transmit Holding Data 3
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMT_THR . TXDATA3
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * TXDATA2: Initiator or Target Transmit Holding Data 2
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMT_THR . TXDATA2
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * TXDATA1: Initiator or Target Transmit Holding Data 1
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMT_THR . TXDATA1
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TXDATA0: Initiator or Target Transmit Holding Data 0
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMT_THR . TXDATA0
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMT_THR_TXDATA0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TWI SMBus Timing Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_SMBTR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_SMBTR(target)  VTSS_IOREG(target,0x18e)

/**
 * \brief
 * THMAX: Clock High Maximum CyclesClock cycles in clock high maximum
 * count. Prescaled by PRESC. Used for bus free detection. Used to time
 * THIGH MAX.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMBTR . THMAX
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMBTR_THMAX(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMBTR_THMAX     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMBTR_THMAX(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * TLOWM: Initiator Clock Stretch Maximum Cycles
 *
 * \details
 * 0: TLOW Initiator EXT timeout check disabled.
 * 1- 255: Clock cycles in initiator maximum clock stretch count. Prescaled
 * by PRESC. Used to time TLOW Initiator EXT.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMBTR . TLOWM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMBTR_TLOWM(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMBTR_TLOWM     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMBTR_TLOWM(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * TLOWS: Target Clock Stretch Maximum Cycles
 *
 * \details
 * 0: TLOW Target EXT timeout check disabled.
 * 1- 255: Clock cycles in target maximum clock stretch count. Prescaled by
 * PRESC. Used to time TLOW Target EXT.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMBTR . TLOWS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMBTR_TLOWS(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMBTR_TLOWS     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMBTR_TLOWS(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * PRESC: SMBus Clock PrescalerUsed to specify how to prescale the TLOWS,
 * TLOWM and THMAX counters in SMBTR. Counters are prescaled accordingto
 * the following formula: PRESC = Log(fMCK / fPrescaled) / Log(2) - 1
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SMBTR . PRESC
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SMBTR_PRESC(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SMBTR_PRESC     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SMBTR_PRESC(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief TWI High Speed Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_HSR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_HSR(target)    VTSS_IOREG(target,0x18f)

/**
 * \brief
 * MCODE: TWI High Speed Initiator Code
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_HSR . MCODE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_HSR_MCODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_HSR_MCODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_HSR_MCODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TWI Alternative Command Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_ACR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_ACR(target)    VTSS_IOREG(target,0x190)

/**
 * \brief
 * NPEC: Next PEC Request (SMBus Mode only)
 *
 * \details
 * 0: The next transfer does not use a PEC byte.
 * 1: The next transfer uses a PEC byte.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_ACR . NPEC
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_ACR_NPEC(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_ACR_NPEC     VTSS_BIT(25)
#define  VTSS_X_FLEXCOM_FLEX_TWI_ACR_NPEC(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * NDIR: Next Transfer Direction
 *
 * \details
 * 0: Write direction.
 * 1: Read direction.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_ACR . NDIR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_ACR_NDIR(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_ACR_NDIR     VTSS_BIT(24)
#define  VTSS_X_FLEXCOM_FLEX_TWI_ACR_NDIR(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * NDATAL: Next Data Length
 *
 * \details
 * 0: No data to send
 * 1- 255: Number of bytes to send for the next transfer.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_ACR . NDATAL
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_ACR_NDATAL(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_ACR_NDATAL     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_ACR_NDATAL(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * PEC: PEC Request (SMBus Mode only)
 *
 * \details
 * 0: The transfer does not use a PEC byte.
 * 1: The transfer uses a PEC byte.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_ACR . PEC
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_ACR_PEC(x)   VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_ACR_PEC      VTSS_BIT(9)
#define  VTSS_X_FLEXCOM_FLEX_TWI_ACR_PEC(x)   VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * DIR: Transfer Direction
 *
 * \details
 * 0: Write direction.
 * 1: Read direction.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_ACR . DIR
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_ACR_DIR(x)   VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_ACR_DIR      VTSS_BIT(8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_ACR_DIR(x)   VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DATAL: Data Length
 *
 * \details
 * 0: No data to send.
 * 1 - 255: Number of bytes to send during the transfer.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_ACR . DATAL
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_ACR_DATAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_ACR_DATAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_ACR_DATAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TWI Filter Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FILTR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FILTR(target)  VTSS_IOREG(target,0x191)

/**
 * \brief
 * THRES: Digital Filter Threshold
 *
 * \details
 * 0: No filtering applied on TWI inputs.
 * 1- 7: Maximum pulse width of spikes which will be suppressed by the
 * input filter, defined in peripheral clock cycles.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FILTR . THRES
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FILTR_THRES(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FILTR_THRES     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FILTR_THRES(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * PADFCFG: PAD Filter ConfigRefer to the section "Electrical
 * Characteristics" for filter configuration details.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FILTR . PADFCFG
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FILTR_PADFCFG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FILTR_PADFCFG  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FILTR_PADFCFG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * PADFEN: PAD Filter Enable
 *
 * \details
 * 0: PAD analog filter is disabled.
 * 1: PAD analog filter is enabled. (The analog filter must be enabled if
 * High-speed mode is enabled.)
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FILTR . PADFEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FILTR_PADFEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FILTR_PADFEN  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FILTR_PADFEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * FILT: RX Digital Filter
 *
 * \details
 * 0: No filtering applied on TWI inputs.
 * 1: TWI input filtering is active. (Only in Standard and Fast modes)
 * Note: TWI digital input filtering follows a majority decision based on
 * three samples from SDA/SCL lines at peripheral clock frequency.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FILTR . FILT
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FILTR_FILT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FILTR_FILT   VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FILTR_FILT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI High Speed Clock Waveform Generator Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the TWI
 * Write Protection Mode Register.
 * FLEX_TWI_HSCWGR is only used in High Speed Initiator mode.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_HSCWGR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_HSCWGR(target)  VTSS_IOREG(target,0x192)

/**
 * \brief
 * HSCKDIV: High Speed Clock DividerThe CKDIV is used to increase both SCL
 * high and low periods.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_HSCWGR . HSCKDIV
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_HSCWGR_HSCKDIV(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_TWI_HSCWGR_HSCKDIV     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_HSCWGR_HSCKDIV(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * HSCHDIV: High Speed Clock High Divider
 *
 * \details
 * The SCL high period is defined as follows:
 * If BRSRCCLK = 0: CHDIV = ((thigh / tperipheral clock) - 3) / 2 ^ CKDIV
 * If BRSRCCLK = 1: CHDIV = (thigh / text_ck) / 2 ^ CKDIV
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_HSCWGR . HSCHDIV
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_HSCWGR_HSCHDIV(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_HSCWGR_HSCHDIV     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_HSCWGR_HSCHDIV(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * HSCLDIV: High Speed Clock Low Divider
 *
 * \details
 * The SCL low period is defined as follows:
 * If BRSRCCLK = 0: CLDIV = ((tlow / tperipheral clock) - 3) / 2 ^ CKDIV
 * If BRSRCCLK = 1: CLDIV = (tlow / text_ck) / 2 ^ CKDIV
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_HSCWGR . HSCLDIV
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_HSCWGR_HSCLDIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_HSCWGR_HSCLDIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_HSCWGR_HSCLDIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TWI SleepWalking Matching Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_SWMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_SWMR(target)   VTSS_IOREG(target,0x193)

/**
 * \brief
 * DATAM: Data MatchThe TWI module will extend the SleepWalking matching
 * process to the first received data comparing it with DATAM if DATAMEN
 * bit is enabled.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SWMR . DATAM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SWMR_DATAM(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SWMR_DATAM     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SWMR_DATAM(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * SADR3: Target Address 3Target address 3. The TWI module will match on
 * this additional address if SADR3EN bit is enabled.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SWMR . SADR3
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SWMR_SADR3(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SWMR_SADR3     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SWMR_SADR3(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * SADR2: Target Address 2Target address 2. The TWI module will match on
 * this additional address if SADR2EN bit is enabled.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SWMR . SADR2
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SWMR_SADR2(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SWMR_SADR2     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SWMR_SADR2(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * SADR1: Target Address 1Target address 1. The TWI module will match on
 * this additional address if SADR1EN bit is enabled.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_SWMR . SADR1
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_SWMR_SADR1(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_FLEXCOM_FLEX_TWI_SWMR_SADR1     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_SWMR_SADR1(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief TWI FIFO Mode Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the TWI
 * Write Protection Mode Register.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FMR(target)    VTSS_IOREG(target,0x194)

/**
 * \brief
 * RXFTHRES: Receive FIFO Threshold
 *
 * \details
 * 0 - FIFO_DEPTH_TWI: Defines the Receive FIFO threshold value (number of
 * data). The FLEX_TWI_FSR.RXFTHF flag will
 * be set when Receive FIFO goes from "below" threshold state to "equal to
 * or above" threshold state.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMR . RXFTHRES
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMR_RXFTHRES(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMR_RXFTHRES     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMR_RXFTHRES(x)  VTSS_EXTRACT_BITFIELD(x,24,6)

/**
 * \brief
 * TXFTHRES: Transmit FIFO Threshold
 *
 * \details
 * 0 - FIFO_DEPTH_TWI: Defines the Transmit FIFO threshold value (number of
 * data). The FLEX_TWI_FSR.TXFTHF flag will
 * be set when Transmit FIFO goes from "above" threshold state to "equal to
 * or below" threshold state.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMR . TXFTHRES
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMR_TXFTHRES(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMR_TXFTHRES     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMR_TXFTHRES(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * RXRDYM: Receiver Ready Mode
 *
 * \details
 * If FIFOs are enabled, the FLEX_TWI_SR.RXRDY flag behaves as follows.
 * 0 (ONE_DATA): RXRDY will be at level '1' when at least one unread data
 * is in the Receive FIFO
 * 1 (TWO_DATA): RXRDY will be at level '1' when at least one unread data
 * is in the Receive FIFO
 * 2 (FOUR_DATA): RXRDY will be at level '1' when at least one unread data
 * is in the Receive FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMR . RXRDYM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMR_RXRDYM(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMR_RXRDYM     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMR_RXRDYM(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * TXRDYM: Transmitter Ready Mode
 *
 * \details
 * If FIFOs are enabled, the FLEX_TWI_SR.TXRDY flag behaves as follows.
 * 0 (ONE_DATA): TXRDY will be at level '1' when at least one data can be
 * written in the Transmit FIFO
 * 1 (TWO_DATA): TXRDY will be at level '1' when at least one data can be
 * written in the Transmit FIFO
 * 2 (FOUR_DATA): TXRDY will be at level '1' when at least one data can be
 * written in the Transmit FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FMR . TXRDYM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FMR_TXRDYM(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FMR_TXRDYM     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FMR_TXRDYM(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief TWI FIFO Level Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FLR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FLR(target)    VTSS_IOREG(target,0x195)

/**
 * \brief
 * RXFL: Receive FIFO Level
 *
 * \details
 * 0: There is no unread data in the Receive FIFO
 * 1 - FIFO_DEPTH_TWI: Indicates the number of unread data in the Receive
 * FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FLR . RXFL
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FLR_RXFL(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FLR_RXFL     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FLR_RXFL(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * TXFL: Transmit FIFO Level
 *
 * \details
 * 0: There is no data in the Transmit FIFO
 * 1- FIFO_DEPTH_TWI: Indicates the number of data in the Transmit FIFO
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FLR . TXFL
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FLR_TXFL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FLR_TXFL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FLR_TXFL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief TWI FIFO Status Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FSR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FSR(target)    VTSS_IOREG(target,0x198)

/**
 * \brief
 * RXFPTEF: Receive FIFO Pointer Error Flag
 *
 * \details
 * 0: No Receive FIFO pointer occurred
 * 1: Receive FIFO pointer error occurred. Receiver must be reset
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FSR . RXFPTEF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FSR_RXFPTEF(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FSR_RXFPTEF  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FSR_RXFPTEF(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXFPTEF: Transmit FIFO Pointer Error Flag
 *
 * \details
 * 0: No Transmit FIFO pointer occurred
 * 1: Transmit FIFO pointer error occurred. Transceiver must be reset
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FSR . TXFPTEF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FSR_TXFPTEF(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FSR_TXFPTEF  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FSR_TXFPTEF(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXFTHF: Receive FIFO Threshold Flag
 *
 * \details
 * 0: Number of unread data in Receive FIFO is below RXFTHRES threshold.
 * 1: Number of unread data in Receive FIFO has reached RXFTHRES threshold
 * since the last read of FLEX_TWI_FSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FSR . RXFTHF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FSR_RXFTHF(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FSR_RXFTHF   VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FSR_RXFTHF(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXFFF: Receive FIFO Full Flag
 *
 * \details
 * 0: Receive FIFO is not empty.
 * 1: Receive FIFO has been filled since the last read of FLEX_TWI_FSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FSR . RXFFF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FSR_RXFFF(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FSR_RXFFF    VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FSR_RXFFF(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RXFEF: Receive FIFO Empty Flag
 *
 * \details
 * 0: Receive FIFO is not empty.
 * 1: Receive FIFO has been emptied since the last read of FLEX_TWI_FSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FSR . RXFEF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FSR_RXFEF(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FSR_RXFEF    VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FSR_RXFEF(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXFTHF: Transmit FIFO Threshold Flag (cleared on read)
 *
 * \details
 * 0: Number of data in Transmit FIFO is above TXFTHRES threshold.
 * 1: Number of data in Transmit FIFO has reached TXFTHRES threshold since
 * the last read of FLEX_TWI_FSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FSR . TXFTHF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FSR_TXFTHF(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FSR_TXFTHF   VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FSR_TXFTHF(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXFFF: Transmit FIFO Full Flag (cleared on read)
 *
 * \details
 * 0: Transmit FIFO is not full.
 * 1: Transmit FIFO has been filled since the last read of FLEX_TWI_FSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FSR . TXFFF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FSR_TXFFF(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FSR_TXFFF    VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FSR_TXFFF(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXFEF: Transmit FIFO Empty Flag (cleared on read)
 *
 * \details
 * 0: Transmit FIFO is not empty.
 * 1: Transmit FIFO has been emptied since the last read of FLEX_TWI_FSR.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FSR . TXFEF
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FSR_TXFEF(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FSR_TXFEF    VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FSR_TXFEF(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI FIFO Interrupt Enable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * TWI Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FIER
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FIER(target)   VTSS_IOREG(target,0x199)

/**
 * \brief
 * RXFPTEF_IE: RXFPTEF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIER . RXFPTEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIER_RXFPTEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIER_RXFPTEF_IE  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIER_RXFPTEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXFPTEF_IE: TXFPTEF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIER . TXFPTEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIER_TXFPTEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIER_TXFPTEF_IE  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIER_TXFPTEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXFTHF_IE: RXFTHF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIER . RXFTHF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIER_RXFTHF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIER_RXFTHF_IE  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIER_RXFTHF_IE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXFFF_IE: RXFFF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIER . RXFFF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIER_RXFFF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIER_RXFFF_IE  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIER_RXFFF_IE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RXFEF_IE: RXFEF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIER . RXFEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIER_RXFEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIER_RXFEF_IE  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIER_RXFEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXFTHF_IE: TXFTHF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIER . TXFTHF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIER_TXFTHF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIER_TXFTHF_IE  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIER_TXFTHF_IE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXFFF_IE: TXFFF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIER . TXFFF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIER_TXFFF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIER_TXFFF_IE  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIER_TXFFF_IE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXFEF_IE: TXFEF Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIER . TXFEF_IE
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIER_TXFEF_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIER_TXFEF_IE  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIER_TXFEF_IE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI FIFO Interrupt Enable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * TWI Write Protection Mode Register.
 * Note: This register has Write-only access.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FIDR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FIDR(target)   VTSS_IOREG(target,0x19a)

/**
 * \brief
 * RXFPTEF_ID: RXFPTEF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIDR . RXFPTEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIDR_RXFPTEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIDR_RXFPTEF_ID  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIDR_RXFPTEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXFPTEF_ID: TXFPTEF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIDR . TXFPTEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIDR_TXFPTEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIDR_TXFPTEF_ID  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIDR_TXFPTEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXFTHF_ID: RXFTHF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIDR . RXFTHF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIDR_RXFTHF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIDR_RXFTHF_ID  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIDR_RXFTHF_ID(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXFFF_ID: RXFFF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIDR . RXFFF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIDR_RXFFF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIDR_RXFFF_ID  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIDR_RXFFF_ID(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RXFEF_ID: RXFEF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIDR . RXFEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIDR_RXFEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIDR_RXFEF_ID  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIDR_RXFEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXFTHF_ID: TXFTHF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIDR . TXFTHF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIDR_TXFTHF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIDR_TXFTHF_ID  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIDR_TXFTHF_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXFFF_ID: TXFFF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIDR . TXFFF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIDR_TXFFF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIDR_TXFFF_ID  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIDR_TXFFF_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXFEF_ID: TXFEF Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the interrupt.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIDR . TXFEF_ID
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIDR_TXFEF_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIDR_TXFEF_ID  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIDR_TXFEF_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI FIFO Interrupt Mask Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_FIMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_FIMR(target)   VTSS_IOREG(target,0x19b)

/**
 * \brief
 * RXFPTEF_IM: RXFPTEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIMR . RXFPTEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIMR_RXFPTEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIMR_RXFPTEF_IM  VTSS_BIT(7)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIMR_RXFPTEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * TXFPTEF_IM: TXFPTEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIMR . TXFPTEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIMR_TXFPTEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIMR_TXFPTEF_IM  VTSS_BIT(6)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIMR_TXFPTEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RXFTHF_IM: RXFTHF Interrupt Mask
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIMR . RXFTHF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIMR_RXFTHF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIMR_RXFTHF_IM  VTSS_BIT(5)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIMR_RXFTHF_IM(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RXFFF_IM: RXFFF Interrupt Mask
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIMR . RXFFF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIMR_RXFFF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIMR_RXFFF_IM  VTSS_BIT(4)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIMR_RXFFF_IM(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RXFEF_IM: RXFEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIMR . RXFEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIMR_RXFEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIMR_RXFEF_IM  VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIMR_RXFEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * TXFTHF_IM: TXFTHF Interrupt Mask
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIMR . TXFTHF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIMR_TXFTHF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIMR_TXFTHF_IM  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIMR_TXFTHF_IM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TXFFF_IM: TXFFF Interrupt Mask
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIMR . TXFFF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIMR_TXFFF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIMR_TXFFF_IM  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIMR_TXFFF_IM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TXFEF_IM: TXFEF Interrupt Mask
 *
 * \details
 * 0: The interrupt is disabled.
 * 1: The interrupt is enabled.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_FIMR . TXFEF_IM
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_FIMR_TXFEF_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_FIMR_TXFEF_IM  VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_FIMR_TXFEF_IM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Debug Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_DR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_DR(target)     VTSS_IOREG(target,0x1b4)

/**
 * \brief
 * TRP: Transfer Pending
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_DR . TRP
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_DR_TRP(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_DR_TRP       VTSS_BIT(3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_DR_TRP(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * SWMATCH: SleepWalking Match
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_DR . SWMATCH
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_DR_SWMATCH(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_DR_SWMATCH   VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_DR_SWMATCH(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CLKRQ: Clock Request
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_DR . CLKRQ
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_DR_CLKRQ(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_DR_CLKRQ     VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_DR_CLKRQ(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * SWEN: SleepWalking Enable
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_DR . SWEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_DR_SWEN(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_DR_SWEN      VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_DR_SWEN(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Write Protection Mode Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_WPMR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_WPMR(target)   VTSS_IOREG(target,0x1b9)

/**
 * \brief
 * WPKEY: Write Protection Key
 *
 * \details
 * Value = 0x545749 (PASSWD) Writing any other value in this field aborts
 * the write operation of bits WPEN, WPITEN and WPCREN.
 * Always reads as 0
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_WPMR . WPKEY
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_WPMR_WPKEY(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_FLEXCOM_FLEX_TWI_WPMR_WPKEY     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_FLEXCOM_FLEX_TWI_WPMR_WPKEY(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * WPCREN: Write Protection Control Enable
 *
 * \details
 * 0: Disables the write protection on control register if WPKEY
 * corresponds to 0x545749 ("TWI" in ASCII).
 * 1: Enables the write protection on control register if WPKEY corresponds
 * to 0x545749 ("TWI" in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_WPMR . WPCREN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_WPMR_WPCREN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_WPMR_WPCREN  VTSS_BIT(2)
#define  VTSS_X_FLEXCOM_FLEX_TWI_WPMR_WPCREN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * WPITEN: Write Protection Interrupt Enable
 *
 * \details
 * 0: Disables the write protection on interrupt registers if WPKEY
 * corresponds to 0x545749 ("TWI" in ASCII).
 * 1: Enables the write protection on interrupt registers if WPKEY
 * corresponds to 0x545749 ("TWI" in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_WPMR . WPITEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_WPMR_WPITEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_WPMR_WPITEN  VTSS_BIT(1)
#define  VTSS_X_FLEXCOM_FLEX_TWI_WPMR_WPITEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPEN: Write Protection Enable
 *
 * \details
 * 0: Disables the write protection if WPKEY corresponds to 0x545749 ("TWI"
 * in ASCII).
 * 1: Enables the write protection if WPKEY corresponds to 0x545749 ("TWI"
 * in ASCII).
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_WPMR . WPEN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_WPMR_WPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_WPMR_WPEN    VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_WPMR_WPEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Write Protection Status Register
 *
 * \details
 * Note: If enabled in the SFR module (default is disabled), a debugger
 * read access does not clear the WPVS flag.
 *
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_WPSR
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_WPSR(target)   VTSS_IOREG(target,0x1ba)

/**
 * \brief
 * WPVSRC: Write Protection Violation SourceWhen WPVS = 1, WPVSRC indicates
 * the register address offset at which a write access has been attempted.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_WPSR . WPVSRC
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_WPSR_WPVSRC(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_FLEXCOM_FLEX_TWI_WPSR_WPVSRC     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_FLEXCOM_FLEX_TWI_WPSR_WPVSRC(x)  VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * WPVS: Write Protect Violation Status
 *
 * \details
 * 0: No Write Protection Violation has occurred since the last read of
 * FLEX_TWI_WPSR.
 * 1: A Write Protection Violation has occurred since the last read of
 * FLEX_TWI_WPSR. If this violation is an unauthorized
 * attempt to write a protected register, the associated violation is
 * reported into field WPVSRC.
 *
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_WPSR . WPVS
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_WPSR_WPVS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FLEXCOM_FLEX_TWI_WPSR_WPVS    VTSS_BIT(0)
#define  VTSS_X_FLEXCOM_FLEX_TWI_WPSR_WPVS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TWI Version Register
 *
 * \details
 * Register: \a FLEXCOM:FLEXCOM_TWI_REG:FLEX_TWI_VER
 *
 * @param target A \a ::vtss_target_FLEXCOM_e target
 */
#define VTSS_FLEXCOM_FLEX_TWI_VER(target)    VTSS_IOREG(target,0x1bf)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_VER . MFN
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_VER_MFN(x)   VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_FLEXCOM_FLEX_TWI_VER_MFN      VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_FLEXCOM_FLEX_TWI_VER_MFN(x)   VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the internal version of the
 * macrocell.
 *
 * \details
 * Field: ::VTSS_FLEXCOM_FLEX_TWI_VER . VERSION
 */
#define  VTSS_F_FLEXCOM_FLEX_TWI_VER_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_FLEXCOM_FLEX_TWI_VER_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_FLEXCOM_FLEX_TWI_VER_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_FLEXCOM_H_ */
