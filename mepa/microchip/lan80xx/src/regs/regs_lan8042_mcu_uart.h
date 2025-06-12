// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU25G_REGS_MCU_UART_H_
#define _VTSS_MALIBU25G_REGS_MCU_UART_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a MCU_UART
 *
 * UART registers
 *
 ***********************************************************************/

/**
 * Register Group: \a MCU_UART:UART
 *
 * UART Registers
 */


/**
 * \brief UART_RX_DATA, UART_TX_DATA or UART_DIV_LAT_LO
 *
 * \details
 * if DLAB=0
 * Received Buffer Register (RB) UART_RX_DATA
 * Transmit Buffer Register (TB) UART_TX_DATA
 * if DLAB=1
 * Divisor Latch Low (DLL) UART_DIV_LAT_LO
 *
 * Note: DLAB is bit 7 of the Line Control Register
 *
 * Register: \a MCU_UART:UART:UART_RX_TX_DATA_DLL
 */
#define VTSS_MCU_UART_UART_RX_TX_DATA_DLL    VTSS_IOREG(VTSS_TO_MCU_UART,0x0)

/**
 * \brief
 * if DLAB=0, UART_RX_DATA[7:0] or UART_TX_DATA[7:0]if DLAB=1,
 * baud_divisor[7:0] Note: DLAB is bit 7 of the Line Control Register.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_RX_TX_DATA_DLL . DATA
 */
#define  VTSS_F_MCU_UART_UART_RX_TX_DATA_DLL_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCU_UART_UART_RX_TX_DATA_DLL_DATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCU_UART_UART_RX_TX_DATA_DLL_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief UART_DIV_LAT_HI or UART_INTERRUPT_EN
 *
 * \details
 * if DLAB=1, Divisor Latch High (DHL) UART_DIV_LAT_HI
 * if DLAB=0, Interrupt Enable Register (IER) UART_INTERRUPT_EN
 *
 * Register: \a MCU_UART:UART:UART_IER_DHL
 */
#define VTSS_MCU_UART_UART_IER_DHL           VTSS_IOREG(VTSS_TO_MCU_UART,0x1)

/**
 * \brief
 * if IER, Reserved.if DHL, when the baud reference clock is generated
 * internally in the UART, this bit selects between 30MHz and 1.8519MHz.
 *
 * \details
 * 0 = 1.8519MHz
 * 1 = 30MHz
 * Note: The frequencies are based on an MCU clock of 300 MHz.
 *
 * Field: ::VTSS_MCU_UART_UART_IER_DHL . BAUD_CLK_SEL
 */
#define  VTSS_F_MCU_UART_UART_IER_DHL_BAUD_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_UART_UART_IER_DHL_BAUD_CLK_SEL  VTSS_BIT(7)
#define  VTSS_X_MCU_UART_UART_IER_DHL_BAUD_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * if IER, always read 0if DHL, baud_divisor[14:12]
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_IER_DHL . RESERVED_14_12
 */
#define  VTSS_F_MCU_UART_UART_IER_DHL_RESERVED_14_12(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_MCU_UART_UART_IER_DHL_RESERVED_14_12     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_MCU_UART_UART_IER_DHL_RESERVED_14_12(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * if IER, enable Modem status Interrruptif DHL, baud_divisor[11]
 *
 * \details
 * if IER
 *     1: interrupt enabled
 *  0: interrupt disabled

 *
 * Field: ::VTSS_MCU_UART_UART_IER_DHL . EMSI
 */
#define  VTSS_F_MCU_UART_UART_IER_DHL_EMSI(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_UART_UART_IER_DHL_EMSI    VTSS_BIT(3)
#define  VTSS_X_MCU_UART_UART_IER_DHL_EMSI(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * if IER, enable Receiver Line Status Interrruptif DHL, baud_divisor[10]
 *
 * \details
 * if IER
 *     1: interrupt enabled
 *  0: interrupt disabled

 *
 * Field: ::VTSS_MCU_UART_UART_IER_DHL . ELSI
 */
#define  VTSS_F_MCU_UART_UART_IER_DHL_ELSI(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_UART_UART_IER_DHL_ELSI    VTSS_BIT(2)
#define  VTSS_X_MCU_UART_UART_IER_DHL_ELSI(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * if IER, enable Transmitter Holding Register Empty Interruptif DHL,
 * baud_divisor[9]
 *
 * \details
 * if IER
 *     1: interrupt enabled
 *  0: interrupt disabled

 *
 * Field: ::VTSS_MCU_UART_UART_IER_DHL . ETHREI
 */
#define  VTSS_F_MCU_UART_UART_IER_DHL_ETHREI(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_UART_UART_IER_DHL_ETHREI  VTSS_BIT(1)
#define  VTSS_X_MCU_UART_UART_IER_DHL_ETHREI(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * if IER, enable Received Data  Available Interruptif DHL, baud_divisor[8]
 *
 * \details
 * if IER
 *     1: interrupt enabled
 *  0: interrupt disabled

 *
 * Field: ::VTSS_MCU_UART_UART_IER_DHL . ERDAI
 */
#define  VTSS_F_MCU_UART_UART_IER_DHL_ERDAI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_UART_UART_IER_DHL_ERDAI   VTSS_BIT(0)
#define  VTSS_X_MCU_UART_UART_IER_DHL_ERDAI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief UART_IIR or UART_FIFO_CTL
 *
 * \details
 * if read, UART_IIR
 * if write, UART_FIFO_CTL

 *
 * Register: \a MCU_UART:UART:UART_IIR_FCR
 */
#define VTSS_MCU_UART_UART_IIR_FCR           VTSS_IOREG(VTSS_TO_MCU_UART,0x2)

/**
 * \brief
 * if IIR, FIFOs Enabled, always zero in the non-FIFO modeif FCR, RCVR
 * Trigger MSB
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_IIR_FCR . IIR_FIFO_EN_FCTL_RX_TRIG_MSB
 */
#define  VTSS_F_MCU_UART_UART_IIR_FCR_IIR_FIFO_EN_FCTL_RX_TRIG_MSB(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_UART_UART_IIR_FCR_IIR_FIFO_EN_FCTL_RX_TRIG_MSB  VTSS_BIT(7)
#define  VTSS_X_MCU_UART_UART_IIR_FCR_IIR_FIFO_EN_FCTL_RX_TRIG_MSB(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * if IIR, FIFOs Enabled, always zero in the non-FIFO modeif FCR, RCVR
 * Trigger MSB
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_IIR_FCR . IIR_FIFO_EN_FCTL_RX_TRIG_LSB
 */
#define  VTSS_F_MCU_UART_UART_IIR_FCR_IIR_FIFO_EN_FCTL_RX_TRIG_LSB(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCU_UART_UART_IIR_FCR_IIR_FIFO_EN_FCTL_RX_TRIG_LSB  VTSS_BIT(6)
#define  VTSS_X_MCU_UART_UART_IIR_FCR_IIR_FIFO_EN_FCTL_RX_TRIG_LSB(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * always read 0
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_IIR_FCR . RESERVED_21_20
 */
#define  VTSS_F_MCU_UART_UART_IIR_FCR_RESERVED_21_20(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_MCU_UART_UART_IIR_FCR_RESERVED_21_20     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_MCU_UART_UART_IIR_FCR_RESERVED_21_20(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * if IIR, Interrupt ID bitif FCR, write a 1 to this bit has no effect.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_IIR_FCR . IIR_INTID_FCTL_DMA_MODE_SEL
 */
#define  VTSS_F_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_DMA_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_DMA_MODE_SEL  VTSS_BIT(3)
#define  VTSS_X_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_DMA_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * if IIR, Interrupt ID bitif FCR, TX FIFO Reset
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_IIR_FCR . IIR_INTID_FCTL_TX_FIFO_RESET
 */
#define  VTSS_F_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_TX_FIFO_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_TX_FIFO_RESET  VTSS_BIT(2)
#define  VTSS_X_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_TX_FIFO_RESET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * if IIR, Interrupt ID bitif FCR, RX FIFO Reset
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_IIR_FCR . IIR_INTID_FCTL_RX_FIFO_RESET
 */
#define  VTSS_F_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_RX_FIFO_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_RX_FIFO_RESET  VTSS_BIT(1)
#define  VTSS_X_MCU_UART_UART_IIR_FCR_IIR_INTID_FCTL_RX_FIFO_RESET(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * if IIR, Interrupt pending bitif FCR, FIFO enable
 *
 * \details
 * if IIR,
 *   0: interrupt pending
 * if FCR
 *   1: FIFO enabled
 *    0: FIFO disabled
 *
 * Field: ::VTSS_MCU_UART_UART_IIR_FCR . IIR_IPEND_FCTL_FIFO_EN
 */
#define  VTSS_F_MCU_UART_UART_IIR_FCR_IIR_IPEND_FCTL_FIFO_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_UART_UART_IIR_FCR_IIR_IPEND_FCTL_FIFO_EN  VTSS_BIT(0)
#define  VTSS_X_MCU_UART_UART_IIR_FCR_IIR_IPEND_FCTL_FIFO_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Line Control Register
 *
 * \details
 * UART_LINE_CTL (dlab=X)
 * This register contains the format information of the serial line.
 *
 * Register: \a MCU_UART:UART:UART_LCR
 */
#define VTSS_MCU_UART_UART_LCR               VTSS_IOREG(VTSS_TO_MCU_UART,0x3)

/**
 * \brief
 * Divisor Latch Access Bit (DLAB). It must be set high (logic 1) to access
 * the DivisorLatches of the Baud Rate Generator during read or write
 * operations. It mustbe set low (logic 0) to access the Receiver Buffer
 * Register, the Transmitter HoldingRegister or the Interrupt Enable
 * Register.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LCR . DLAB
 */
#define  VTSS_F_MCU_UART_UART_LCR_DLAB(x)     VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_UART_UART_LCR_DLAB        VTSS_BIT(7)
#define  VTSS_X_MCU_UART_UART_LCR_DLAB(x)     VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set Break Control bit. When bit 6 is a logic 1, the transmit data output
 * (TXD) isforced to the Spacing or logic 0 state and remains there (until
 * reset by a lowlevel bit 6) regardless of other transmitter activity.
 * This feature enables the SerialPort to alert a terminal in a
 * communications system.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LCR . BREAK_CTL
 */
#define  VTSS_F_MCU_UART_UART_LCR_BREAK_CTL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCU_UART_UART_LCR_BREAK_CTL   VTSS_BIT(6)
#define  VTSS_X_MCU_UART_UART_LCR_BREAK_CTL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Stick Parity bit. When parity is enabled it is used in conjunction with
 * bit 4 to selectMark or Space Parity. When LCR bits 3, 4 and 5 are 1 the
 * Parity bit is transmittedand checked as a 0 (Space Parity). If bits 3
 * and 5 are 1 and bit 4 is a 0, then theParity bit is transmitted and
 * checked as 1 (Mark Parity). If bit 5 is 0 Stick Parity isdisabled.Bit 3
 * is a logic 1 and bit 5 is a logic 1, the parity bit is transmitted and
 * thendetected by the receiver in the opposite state indicated by bit 4.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LCR . STICK_PARITY
 */
#define  VTSS_F_MCU_UART_UART_LCR_STICK_PARITY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCU_UART_UART_LCR_STICK_PARITY  VTSS_BIT(5)
#define  VTSS_X_MCU_UART_UART_LCR_STICK_PARITY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Even Parity Select bit. When bit 3 is a logic 1 and bit 4 is a logic 0,
 * an oddnumber of logic 1's is transmitted or checked in the data word
 * bits and the paritybit. When bit 3 is a logic 1 and bit 4 is a logic 1
 * an even number of bits is transmittedand checked.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LCR . PARITY_SEL
 */
#define  VTSS_F_MCU_UART_UART_LCR_PARITY_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCU_UART_UART_LCR_PARITY_SEL  VTSS_BIT(4)
#define  VTSS_X_MCU_UART_UART_LCR_PARITY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Parity Enable bit. When bit 3 is a logic 1, a parity bit is generated
 * (transmit data)or checked (receive data) between the last data word bit
 * and the first stop bit ofthe serial data. (The parity bit is used to
 * generate an even or odd number of 1swhen the data word bits and the
 * parity bit are summed).
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LCR . PARITY_EN
 */
#define  VTSS_F_MCU_UART_UART_LCR_PARITY_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_UART_UART_LCR_PARITY_EN   VTSS_BIT(3)
#define  VTSS_X_MCU_UART_UART_LCR_PARITY_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This bit specifies the number of stop bits in each transmitted or
 * received serialcharacter.
 *
 * \details
 * 0: 1 bit
 * 1: 1.5 bit if word length= 5 bits
 *  2 bits if word length = 6, 7 or 8 bits
 *
 * Field: ::VTSS_MCU_UART_UART_LCR . STOP_BITS
 */
#define  VTSS_F_MCU_UART_UART_LCR_STOP_BITS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_UART_UART_LCR_STOP_BITS   VTSS_BIT(2)
#define  VTSS_X_MCU_UART_UART_LCR_STOP_BITS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * These two bits specify the number of bits in each transmitted or
 * received serialcharacter.
 *
 * \details
 * The encoding of bits 0 and 1 is as follows:
 * Value - Word Length
 * 00 - 5 bits
 * 01 - 6 bits
 * 10 - 7 bits
 * 11 - 8 bits
 * The Start, Stop and Parity bits are not included in the word length
 *
 * Field: ::VTSS_MCU_UART_UART_LCR . WORD_LEN
 */
#define  VTSS_F_MCU_UART_UART_LCR_WORD_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MCU_UART_UART_LCR_WORD_LEN     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MCU_UART_UART_LCR_WORD_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Modem Control Register
 *
 * \details
 * UART_MODEM_CTL (dlab=X)
 * This 8-bit register controls the interface with the MODEM or data set
 * (or device emulating a MODEM).
 *
 * Register: \a MCU_UART:UART:UART_MCR
 */
#define VTSS_MCU_UART_UART_MCR               VTSS_IOREG(VTSS_TO_MCU_UART,0x4)

/**
 * \brief
 * This bit provides the loopback feature for diagnostic testing of the
 * Serial Port.When bit 4 is set to logic 1, the following occur:The TXD is
 * set to the Marking State (logic 1).The receiver Serial Input (RXD) is
 * disconnected.The output of the Transmitter Shift Register is looped back
 * into the Receiver ShiftRegister input.All MODEM Control inputs (nCTS,
 * nDSR, nRI and nDCD) are disconnected.The four MODEM Control outputs
 * (nDTR, nRTS, OUT1 and OUT2) are internallyconnected to the four MODEM
 * Control inputs (nDSR, nCTS, RI, DCD).The Modem Control output pins are
 * forced inactive high.Data that is transmitted is immediately
 * received.This feature allows the processor to verify the transmit and
 * receive data paths ofthe Serial Port. In the diagnostic mode, the
 * receiver and the transmitter interruptsare fully operational. The MODEM
 * Control Interrupts are also operational but theinterrupts' sources are
 * now the lower four bits of the MODEM Control Registerinstead of the
 * MODEM Control inputs. The interrupts are still controlled by
 * theInterrupt Enable Register
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MCR . LOOPBACK
 */
#define  VTSS_F_MCU_UART_UART_MCR_LOOPBACK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCU_UART_UART_MCR_LOOPBACK    VTSS_BIT(4)
#define  VTSS_X_MCU_UART_UART_MCR_LOOPBACK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Output 2 (OUT2). This bit is used to enable an UART interrupt. When OUT2
 * is alogic 0, the serial port interrupt output is forced to a high
 * impedance state - disabled.When OUT2 is a logic 1, the serial port
 * interrupt outputs are enabled.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MCR . OUT2
 */
#define  VTSS_F_MCU_UART_UART_MCR_OUT2(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_UART_UART_MCR_OUT2        VTSS_BIT(3)
#define  VTSS_X_MCU_UART_UART_MCR_OUT2(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This bit controls the Output 1 (OUT1) bit. This bit does not have an
 * output pin andcan only be read or written by the CPU.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MCR . OUT1
 */
#define  VTSS_F_MCU_UART_UART_MCR_OUT1(x)     VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_UART_UART_MCR_OUT1        VTSS_BIT(2)
#define  VTSS_X_MCU_UART_UART_MCR_OUT1(x)     VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This bit controls the Request To Send (nRTS) output. Bit 1 affects the
 * nRTS outputin a manner identical to that described above for bit 0.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MCR . RTS
 */
#define  VTSS_F_MCU_UART_UART_MCR_RTS(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_UART_UART_MCR_RTS         VTSS_BIT(1)
#define  VTSS_X_MCU_UART_UART_MCR_RTS(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This bit controls the Data Terminal Ready (nDTR) output. When bit 0 is
 * set to alogic 1, the nDTR output is forced to a logic 0. When bit 0 is a
 * logic 0, thenDTR output is forced to a logic 1.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MCR . DTR
 */
#define  VTSS_F_MCU_UART_UART_MCR_DTR(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_UART_UART_MCR_DTR         VTSS_BIT(0)
#define  VTSS_X_MCU_UART_UART_MCR_DTR(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Line Status Register
 *
 * \details
 * UART_LINE_STAT (dlab=X)
 *
 * Register: \a MCU_UART:UART:UART_LSR
 */
#define VTSS_MCU_UART_UART_LSR               VTSS_IOREG(VTSS_TO_MCU_UART,0x5)

/**
 * \brief
 * This bit is permanently set to logic 0 in the 450 mode. In the FIFO
 * mode, thisbit is set to a logic 1 when there is at least one parity
 * error, framing error orbreak indication in the FIFO. This bit is cleared
 * when the LSR is read if thereare no subsequent errors in the FIFO.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LSR . FIFO_ERROR
 */
#define  VTSS_F_MCU_UART_UART_LSR_FIFO_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_UART_UART_LSR_FIFO_ERROR  VTSS_BIT(7)
#define  VTSS_X_MCU_UART_UART_LSR_FIFO_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Transmitter Empty. Bit 6 is set to a logic 1 whenever the Transmitter
 * HoldingRegister (THR) and Transmitter Shift Register (TSR) are both
 * empty. It is resetto logic 0 whenever either the THR or TSR contains a
 * data character. Bit 6 is aread only bit. In the FIFO mode this bit is
 * set whenever the THR and TSR areboth empty
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LSR . XMIT_EMPTY
 */
#define  VTSS_F_MCU_UART_UART_LSR_XMIT_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCU_UART_UART_LSR_XMIT_EMPTY  VTSS_BIT(6)
#define  VTSS_X_MCU_UART_UART_LSR_XMIT_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Transmitter Holding Register Empty (THRE). Bit 5 indicates that the
 * Serial Portis ready to accept a new character for transmission. In
 * addition, this bit causesthe Serial Port to issue an interrupt when the
 * Transmitter Holding Register interruptenable is set high. The THRE bit
 * is set to a logic 1 when a character istransferred from the Transmitter
 * Holding Register into the Transmitter ShiftRegister. The bit is reset to
 * logic 0 whenever the CPU loads the TransmitterHolding Register. In the
 * FIFO mode this bit is set when the XMIT FIFO is empty,it is cleared when
 * at least 1 byte is written to the XMIT FIFO. Bit 5 is a read onlybit.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LSR . THRE
 */
#define  VTSS_F_MCU_UART_UART_LSR_THRE(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCU_UART_UART_LSR_THRE        VTSS_BIT(5)
#define  VTSS_X_MCU_UART_UART_LSR_THRE(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Break Interrupt. Bit 4 is set to a logic 1 whenever the received data
 * input isheld in the Spacing state (logic 0) for longer than a full word
 * transmission time(that is, the total time of the start bit + data bits +
 * parity bits + stop bits). The BIis reset after the CPU reads the
 * contents of the Line Status Register. In theFIFO mode this error is
 * associated with the particular character in the FIFO itapplies to. This
 * error is indicated when the associated character is at the top ofthe
 * FIFO. When break occurs only one zero character is loaded into the
 * FIFO.Restarting after a break is received, requires the serial data
 * (RXD) to be logic1 for at least 1/2 bit time.Bits 1 through 4 are the
 * error conditions that produce a Receiver Line StatusInterrupt BIT 3
 * whenever any of the corresponding conditions are detected andthe
 * interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LSR . BREAK_INT
 */
#define  VTSS_F_MCU_UART_UART_LSR_BREAK_INT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCU_UART_UART_LSR_BREAK_INT   VTSS_BIT(4)
#define  VTSS_X_MCU_UART_UART_LSR_BREAK_INT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Framing Error. Bit 3 indicates that the received character did not have
 * a validstop bit. Bit 3 is set to a logic 1 whenever the stop bit
 * following the last data bitor parity bit is detected as a zero bit
 * (Spacing level). The FE is reset to a logic0 whenever the Line Status
 * Register is read. In the FIFO mode this error isassociated with the
 * particular character in the FIFO it applies to. This error isindicated
 * when the associated character is at the top of the FIFO. The SerialPort
 * will try to resynchronize after a framing error. To do this, it assumes
 * that theframing error was due to the next start bit, so it samples this
 * 'start' bit twice andthen takes in the 'data'
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LSR . FRAME_ERROR
 */
#define  VTSS_F_MCU_UART_UART_LSR_FRAME_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_UART_UART_LSR_FRAME_ERROR  VTSS_BIT(3)
#define  VTSS_X_MCU_UART_UART_LSR_FRAME_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Parity Error. Bit 2 indicates that the received data character does not
 * have thecorrect even or odd parity, as selected by the even parity
 * select bit. The PE isset to a logic 1 upon detection of a parity error
 * and is reset to a logic 0 wheneverthe Line Status Register is read. In
 * the FIFO mode this error is associatedwith the particular character in
 * the FIFO it applies to. This error is indicatedwhen the associated
 * character is at the top of the FIFO.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LSR . PARITY_ERROR
 */
#define  VTSS_F_MCU_UART_UART_LSR_PARITY_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_UART_UART_LSR_PARITY_ERROR  VTSS_BIT(2)
#define  VTSS_X_MCU_UART_UART_LSR_PARITY_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Overrun Error. Bit 1 indicates that data in the Receiver Buffer Register
 * was notread before the next character was transferred into the register,
 * therebydestroying the previous character. In FIFO mode, an overrun error
 * will occuronly when the FIFO is full and the next character has been
 * completely receivedin the shift register, the character in the shift
 * register is overwritten but not transferredto the FIFO. The OE indicator
 * is set to a logic 1 immediately upondetection of an overrun condition
 * and is reset whenever the Line Status Registeris read
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LSR . OVERRUN_ERROR
 */
#define  VTSS_F_MCU_UART_UART_LSR_OVERRUN_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_UART_UART_LSR_OVERRUN_ERROR  VTSS_BIT(1)
#define  VTSS_X_MCU_UART_UART_LSR_OVERRUN_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Data Ready. It is set to a logic 1 whenever a complete incoming
 * character hasbeen received and transferred into the Receiver Buffer
 * Register or the FIFO. Bit0 is reset to a logic 0 by reading all of the
 * data in the Receive Buffer Registeror the FIFO
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_LSR . DATA_READY
 */
#define  VTSS_F_MCU_UART_UART_LSR_DATA_READY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_UART_UART_LSR_DATA_READY  VTSS_BIT(0)
#define  VTSS_X_MCU_UART_UART_LSR_DATA_READY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Modem Status Register
 *
 * \details
 * UART_MSR
 * This 8 bit register provides the current state of the control lines from
 * the MODEM (or peripheral device). In addition to this current state
 * information, four bits of the MODEM Status Register (MSR) provide change
 * information.
 * These bits are set to logic 1 whenever a control input from the MODEM
 * changes state. They are reset to logic 0 whenever the MODEM Status
 * Register is read.
 *
 * Register: \a MCU_UART:UART:UART_MSR
 */
#define VTSS_MCU_UART_UART_MSR               VTSS_IOREG(VTSS_TO_MCU_UART,0x6)

/**
 * \brief
 * This bit is the complement of the Data Carrier Detect (nDCD) input. If
 * bit 4 of theMCR is set to logic 1, this bit is equivalent to OUT2 in the
 * MCR.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MSR . DCD
 */
#define  VTSS_F_MCU_UART_UART_MSR_DCD(x)      VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_UART_UART_MSR_DCD         VTSS_BIT(7)
#define  VTSS_X_MCU_UART_UART_MSR_DCD(x)      VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This bit is the complement of the Ring Indicator (nRI) input. If bit 4
 * of the MCR isset to logic 1, this bit is equivalent to OUT1 in the MCR.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MSR . RI
 */
#define  VTSS_F_MCU_UART_UART_MSR_RI(x)       VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCU_UART_UART_MSR_RI          VTSS_BIT(6)
#define  VTSS_X_MCU_UART_UART_MSR_RI(x)       VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This bit is the complement of the Data Set Ready (nDSR) input. If bit 4
 * of the MCRis set to logic 1, this bit is equivalent to DTR in the MCR.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MSR . DSR
 */
#define  VTSS_F_MCU_UART_UART_MSR_DSR(x)      VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCU_UART_UART_MSR_DSR         VTSS_BIT(5)
#define  VTSS_X_MCU_UART_UART_MSR_DSR(x)      VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * This bit is the complement of the Clear To Send (nCTS) input. If bit 4
 * of the MCR isset to logic 1, this bit is equivalent to nRTS in the MCR.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MSR . CTS
 */
#define  VTSS_F_MCU_UART_UART_MSR_CTS(x)      VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCU_UART_UART_MSR_CTS         VTSS_BIT(4)
#define  VTSS_X_MCU_UART_UART_MSR_CTS(x)      VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Delta Data Carrier Detect (DDCD). Bit 3 indicates that the nDCD input to
 * the chiphas changed state.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MSR . DDCD
 */
#define  VTSS_F_MCU_UART_UART_MSR_DDCD(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_UART_UART_MSR_DDCD        VTSS_BIT(3)
#define  VTSS_X_MCU_UART_UART_MSR_DDCD(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Trailing Edge of Ring Indicator (TERI). Bit 2 indicates that the nRI
 * input haschanged from logic 0 to logic 1.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MSR . TERI
 */
#define  VTSS_F_MCU_UART_UART_MSR_TERI(x)     VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_UART_UART_MSR_TERI        VTSS_BIT(2)
#define  VTSS_X_MCU_UART_UART_MSR_TERI(x)     VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Delta Data Set Ready (DDSR). Bit 1 indicates that the nDSR input has
 * changedstate since the last time the MSR was read.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MSR . DDSR
 */
#define  VTSS_F_MCU_UART_UART_MSR_DDSR(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_UART_UART_MSR_DDSR        VTSS_BIT(1)
#define  VTSS_X_MCU_UART_UART_MSR_DDSR(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Delta Clear To Send (DCTS). Bit 0 indicates that the nCTS input to the
 * chip haschanged state since the last time the MSR was read.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_MSR . DCTS
 */
#define  VTSS_F_MCU_UART_UART_MSR_DCTS(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_UART_UART_MSR_DCTS        VTSS_BIT(0)
#define  VTSS_X_MCU_UART_UART_MSR_DCTS(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Scratch Pad Register
 *
 * \details
 * UART_SCRATCH (dlab=x)
 *
 * Register: \a MCU_UART:UART:UART_SCR
 */
#define VTSS_MCU_UART_UART_SCR               VTSS_IOREG(VTSS_TO_MCU_UART,0x7)

/**
 * \brief
 * This 8 bit read/write register has no effect on the operation of the
 * Serial Port. It isintended as a scratch pad register to be used by the
 * programmer to hold data temporarily.
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_SCR . SCRATCH
 */
#define  VTSS_F_MCU_UART_UART_SCR_SCRATCH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCU_UART_UART_SCR_SCRATCH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCU_UART_UART_SCR_SCRATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Control Register
 *
 * \details
 * UART_CTL
 *
 * Register: \a MCU_UART:UART:UART_CTL
 */
#define VTSS_MCU_UART_UART_CTL               VTSS_IOREG(VTSS_TO_MCU_UART,0x3f0)

/**
 * \brief
 * UART external reference clock selection.
 *
 * \details
 * 0 : Baud clock is 48 MHz
 * 1 : Baud clock is 24 MHz
 *
 * Field: ::VTSS_MCU_UART_UART_CTL . BAUD_CLK_SRC_ALT
 */
#define  VTSS_F_MCU_UART_UART_CTL_BAUD_CLK_SRC_ALT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_UART_UART_CTL_BAUD_CLK_SRC_ALT  VTSS_BIT(3)
#define  VTSS_X_MCU_UART_UART_CTL_BAUD_CLK_SRC_ALT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * 1 = UART_TX and UART_RX pins functions are inverted.
 * 0 = UART_TX and UART_RX pins functions are not inverted.
 *
 * Field: ::VTSS_MCU_UART_UART_CTL . POLARITY
 */
#define  VTSS_F_MCU_UART_UART_CTL_POLARITY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_UART_UART_CTL_POLARITY    VTSS_BIT(2)
#define  VTSS_X_MCU_UART_UART_CTL_POLARITY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * For this device, this bit should always be 0
 *
 * \details
 * Field: ::VTSS_MCU_UART_UART_CTL . POWER
 */
#define  VTSS_F_MCU_UART_UART_CTL_POWER(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_UART_UART_CTL_POWER       VTSS_BIT(1)
#define  VTSS_X_MCU_UART_UART_CTL_POWER(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * UART Clock Select
 *
 * \details
 * 0 = Baud reference clock is generated internally in the UART and is
 * approximately 1.8519 MHz or 30 MHz as chosen by BAUD_CLK_SEL in the
 * UART_DIV_LAT_HI register.
 * Note: The frequencies are based on an MCU clock of 300 MHz.
 * 1 = Baud reference clock is generated external to the UART and is 24 or
 * 48 MHz as chosen by BAUD_CLK_SRC_ALT.
 *
 * Field: ::VTSS_MCU_UART_UART_CTL . BAUD_CLK_SRC
 */
#define  VTSS_F_MCU_UART_UART_CTL_BAUD_CLK_SRC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_UART_UART_CTL_BAUD_CLK_SRC  VTSS_BIT(0)
#define  VTSS_X_MCU_UART_UART_CTL_BAUD_CLK_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration Active Register
 *
 * \details
 * UART_ACTV

 *
 * Register: \a MCU_UART:UART:UART_ACTV
 */
#define VTSS_MCU_UART_UART_ACTV              VTSS_IOREG(VTSS_TO_MCU_UART,0x330)

/**
 * \brief
 * UART Active, This bit needs to be set to enable the block
 *
 * \details
 * 0 (default) = The UART block is inactive
 * 1 = The UART block is active.
 *
 * Field: ::VTSS_MCU_UART_UART_ACTV . ACTV
 */
#define  VTSS_F_MCU_UART_UART_ACTV_ACTV(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_UART_UART_ACTV_ACTV       VTSS_BIT(0)
#define  VTSS_X_MCU_UART_UART_ACTV_ACTV(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_MALIBU25G_REGS_MCU_UART_H_ */
