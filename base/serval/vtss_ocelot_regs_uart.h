// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_OCELOT_REGS_UART_H_
#define _VTSS_OCELOT_REGS_UART_H_


#include "vtss_ocelot_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a UART
 *
 * \see vtss_target_UART_e
 *
 * UART Controller
 *
 ***********************************************************************/

/**
 * Register Group: \a UART:UART
 *
 * UART
 */


/** 
 * \brief Receive buffer / transmit holding / divisor (low)
 *
 * \details
 * When the LCR.DLAB is set, this register is the lower 8 bits of the
 * 16-bit Divisor register that contains the baud rate divisor for the
 * UART.
 * The output baud rate is equal to the VCore system clock frequency
 * divided by sixteen times the value of the baud rate divisor, as follows:
 * baud rate = (VCore clock freq) / (16 * divisor). Note that with the
 * Divisor set to zero, the baud clock is disabled and no serial
 * communications occur. In addition, once this register is set, wait at
 * least 0.1us before transmitting or receiving data.
 *
 * Register: \a UART:UART:RBR_THR
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_RBR_THR(target)       VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Use this register to access the Rx and Tx FIFOs.
 * When reading: The data in this register is valid only if LSR.DR is set.
 * If FIFOs are disabled (IIR_FCR.FIFOE), the data in this register must be
 * read before the next data arrives, otherwise it is overwritten,
 * resulting in an overrun error. When FIFOs are enabled (IIR_FCR.FIFOE),
 * this register accesses the head of the receive FIFO. If the receive FIFO
 * is full and this register is not read before the next data character
 * arrives, then the data already in the FIFO is preserved, but any
 * incoming data is lost and an overrun error occurs.
 * When writing: Data should only be written to this register when the
 * LSR.THRE indicates that there is room in the FIFO. If FIFOs are disabled
 * (IIR_FCR.FIFOE), writes to this register while LSR.THRE is zero, causes
 * the register to be overwritten. When FIFOs are enabled (IIR_FCR.FIFOE)
 * and LSR.THRE is set, 16 characters may be written to this register
 * before the FIFO is full. Any attempt to write data when the FIFO is full
 * results in the write data being lost.
 *
 * \details 
 * Field: ::VTSS_UART_UART_RBR_THR . RBR_THR
 */
#define  VTSS_F_UART_UART_RBR_THR_RBR_THR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_UART_UART_RBR_THR_RBR_THR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_UART_UART_RBR_THR_RBR_THR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Interrupt enable / divisor (high)
 *
 * \details
 * When the LCR.DLAB is set, this register is the upper 8 bits of the
 * 16-bit Divisor register that contains the baud rate divisor for the
 * UART. For more information and a description of how to calculate the
 * baud rate, see RBR_THR.
 *
 * Register: \a UART:UART:IER
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_IER(target)           VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Programmable THRE interrupt mode enable. This is used to enable or
 * disable the generation of THRE interrupt.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_UART_UART_IER . PTIME
 */
#define  VTSS_F_UART_UART_IER_PTIME           VTSS_BIT(7)

/** 
 * \brief
 * Enable modem status interrupt. This is used to enable or disable the
 * generation of Modem Status interrupt. This is the fourth highest
 * priority interrupt.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_UART_UART_IER . EDSSI
 */
#define  VTSS_F_UART_UART_IER_EDSSI           VTSS_BIT(3)

/** 
 * \brief
 * Enable receiver line status interrupt. This is used to enable or disable
 * the generation of Receiver Line Status interrupt. This is the highest
 * priority interrupt.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_UART_UART_IER . ELSI
 */
#define  VTSS_F_UART_UART_IER_ELSI            VTSS_BIT(2)

/** 
 * \brief
 * Enable transmit holding register empty interrupt. This is used to enable
 * or disable the generation of Transmitter Holding Register Empty
 * interrupt. This is the third highest priority interrupt.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_UART_UART_IER . ETBEI
 */
#define  VTSS_F_UART_UART_IER_ETBEI           VTSS_BIT(1)

/** 
 * \brief
 * Enable received data available interrupt. This is used to enable or
 * disable the generation of Received Data Available interrupt and the
 * Character Timeout interrupt (if FIFOs are enabled). These are the second
 * highest priority interrupts.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_UART_UART_IER . ERBFI
 */
#define  VTSS_F_UART_UART_IER_ERBFI           VTSS_BIT(0)


/** 
 * \brief Interrupt identification / FIFO control register
 *
 * \details
 * This register has special meaning when reading, here the lowest 4 bits
 * indicate interrupting sources. The encoding is as follows:
 * 0110; type: Receiver line status, priority: Highest. Overrun/parity/
 * framing errors or break interrupt. Cleared by reading LSR.
 * 0100; type: Received data available, priority: Second. RCVR FIFO trigger
 * level reached. Cleared when FIFO drops below the trigger level.
 * 1100; type: Character timeout indication, priority: Second. No
 * characters in or out of the RCVR FIFO during the last four character
 * times and there is at least 1 character in it during this time. Cleared
 * by reading the receiver buffer register.
 * 0010; type: Transmit holding register empty, priority: Third.
 * Transmitter holding register empty (Prog. THRE Mode disabled) or XMIT
 * FIFO at or below threshold (Prog. THRE Mode enabled). Cleared by reading
 * the IIR register (if source of interrupt); or, writing into THR (THRE
 * Mode disabled) or XMIT FIFO above threshold (THRE Mode enabled).
 * 0000; type: Modem status, priority: Fourth. Clear to send. Note that if
 * auto flow control mode is enabled, a change in CTS (that is, DCTS set)
 * does not cause an interrupt. Cleared by reading the Modem status
 * register.
 * 0111; type: Busy detect indication, priority: Fifth. Master has tried to
 * write to the Line Control register while the UART is busy (USR[0] is set
 * to one). Cleared by reading the UART status register.
 * 0001: No interrupting sources.
 *
 * Register: \a UART:UART:IIR_FCR
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_IIR_FCR(target)       VTSS_IOREG(target,0x2)

/** 
 * \brief
 * When reading this field, the current status of the FIFO is returned; 00
 * for disabled or 11 for enabled. Writing this field selects the trigger
 * level in the receive FIFO at which the Received Data Available interrupt
 * is generated (see encoding.) In auto flow control mode, it is used to
 * determine when to generate back-pressure using the RTS signal.
 *
 * \details 
 * 00: 1 character in the Rx FIFO
 * 01: Rx FIFO 1/4 full
 * 10: Rx FIFO 1/2 full
 * 11: Rx FIFO 2 less than full
 *
 * Field: ::VTSS_UART_UART_IIR_FCR . FIFOSE_RT
 */
#define  VTSS_F_UART_UART_IIR_FCR_FIFOSE_RT(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_UART_UART_IIR_FCR_FIFOSE_RT     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_UART_UART_IIR_FCR_FIFOSE_RT(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Tx empty trigger. When the THRE mode is enabled (IER.PTIME), this field
 * selects the empty threshold level at which the THRE Interrupts are
 * generated.
 *
 * \details 
 * 00: Tx FIFO empty
 * 01: 2 characters in the Tx FIFO
 * 10: Tx FIFO 1/4 full
 * 11: Tx FIFO 1/2 full
 *
 * Field: ::VTSS_UART_UART_IIR_FCR . TET
 */
#define  VTSS_F_UART_UART_IIR_FCR_TET(x)      VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_UART_UART_IIR_FCR_TET         VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_UART_UART_IIR_FCR_TET(x)      VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * This description is valid for writes only. Reading this field has
 * special meaning; for more information, see the general register
 * description.
 * Tx FIFO Reset. This resets the control portion of the transmit FIFO and
 * treats the FIFO as empty. Note that this bit is self-clearing. It is not
 * necessary to clear this bit.
 *
 * \details 
 * Field: ::VTSS_UART_UART_IIR_FCR . XFIFOR
 */
#define  VTSS_F_UART_UART_IIR_FCR_XFIFOR      VTSS_BIT(2)

/** 
 * \brief
 * This description is valid for writes only. Reading this field has
 * special meaning; for more information, see the general register
 * description.
 * Rx FIFO Reset. This resets the control portion of the receive FIFO and
 * treats the FIFO as empty. Note that this bit is self-clearing. It is not
 * necessary to clear this bit.
 *
 * \details 
 * Field: ::VTSS_UART_UART_IIR_FCR . RFIFOR
 */
#define  VTSS_F_UART_UART_IIR_FCR_RFIFOR      VTSS_BIT(1)

/** 
 * \brief
 * This description is valid for writes only. Reading this field has
 * special meaning; for more information, see the general register
 * description.
 * FIFO Enable. This enables or disables the transmit (XMIT) and receive
 * (RCVR) FIFOs. Whenever the value of this bit is changed, both the XMIT
 * and RCVR controller portion of FIFOs are reset.
 *
 * \details 
 * Field: ::VTSS_UART_UART_IIR_FCR . FIFOE
 */
#define  VTSS_F_UART_UART_IIR_FCR_FIFOE       VTSS_BIT(0)


/** 
 * \brief Line control
 *
 * \details
 * Writes can be made to this register, with the exception of the BC field,
 * only when UART is not busy, that is, when USR.BUSY is zero. This
 * register can always be read. 
 *
 * Register: \a UART:UART:LCR
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_LCR(target)           VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Divisor latch access bit. This bit is used to enable reading and writing
 * of the Divisor registers (RBR_THR and IER) to set the baud rate of the
 * UART. To access other registers, this bit must be cleared after initial
 * baud rate setup.
 *
 * \details 
 * Field: ::VTSS_UART_UART_LCR . DLAB
 */
#define  VTSS_F_UART_UART_LCR_DLAB            VTSS_BIT(7)

/** 
 * \brief
 * Break control bit.This bit is used to cause a break condition to be
 * transmitted to the receiving device. If set to one, the serial output is
 * forced to the spacing (logic 0) state. When not in Loopback Mode, as
 * determined by MCR[4], the serial output is forced low until the Break
 * bit is cleared.
 *
 * \details 
 * Field: ::VTSS_UART_UART_LCR . BC
 */
#define  VTSS_F_UART_UART_LCR_BC              VTSS_BIT(6)

/** 
 * \brief
 * Even parity select. This bit is used to select between even and odd
 * parity, when parity is enabled (PEN set to one). If set to one, an even
 * number of logic 1s is transmitted or checked. If set to zero, an odd
 * number of logic 1s is transmitted or checked.
 *
 * \details 
 * Field: ::VTSS_UART_UART_LCR . EPS
 */
#define  VTSS_F_UART_UART_LCR_EPS             VTSS_BIT(4)

/** 
 * \brief
 * Parity enable. This bit is used to enable or disable parity generation
 * and detection in both transmitted and received serial characters.
 *
 * \details 
 * 0: Parity disabled
 * 1: Parity enabled
 *
 * Field: ::VTSS_UART_UART_LCR . PEN
 */
#define  VTSS_F_UART_UART_LCR_PEN             VTSS_BIT(3)

/** 
 * \brief
 * Number of stop bits. This is used to select the number of stop bits per
 * character that the peripheral transmits and receives. If set to zero,
 * one stop bit is transmitted in the serial data.
 * If set to one and the data bits are set to 5 (LCR.DLS), one and a half
 * stop bits are transmitted. Otherwise, two stop bits are transmitted.
 * Note that regardless of the number of stop bits selected, the receiver
 * checks only the first stop bit.
 *
 * \details 
 * 0: 1 stop bit
 * 1: 1.5 stop bits when LCR.DLS is zero, otherwise, 2 stop bits
 *
 * Field: ::VTSS_UART_UART_LCR . STOP
 */
#define  VTSS_F_UART_UART_LCR_STOP            VTSS_BIT(2)

/** 
 * \brief
 * Data length select. This is used to select the number of data bits per
 * character that the peripheral transmits and receives. The following
 * settings specify the number of bits that may be selected.
 *
 * \details 
 * 00: 5 bits
 * 01: 6 bits
 * 10: 7 bits
 * 11: 8 bits
 *
 * Field: ::VTSS_UART_UART_LCR . DLS
 */
#define  VTSS_F_UART_UART_LCR_DLS(x)          VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_UART_UART_LCR_DLS             VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_UART_UART_LCR_DLS(x)          VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Modem control
 *
 * \details
 * Register: \a UART:UART:MCR
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_MCR(target)           VTSS_IOREG(target,0x4)

/** 
 * \brief
 * Auto flow control enable. This mode requires that FIFOs are enabled and
 * that MCR.RTS is set.
 *
 * \details 
 * 0: Auto flow control mode disabled
 * 1: Auto flow control mode enabled
 *
 * Field: ::VTSS_UART_UART_MCR . AFCE
 */
#define  VTSS_F_UART_UART_MCR_AFCE            VTSS_BIT(5)

/** 
 * \brief
 * Loopback Bit. This is used to put the UART into a diagnostic mode for
 * test purposes.
 * The transmit line is held high, while serial transmit data is looped
 * back to the receive line internally. In this mode, all the interrupts
 * are fully functional. In addition, in loopback mode, the modem control
 * input CTS is disconnected, and the modem control output RTS is looped
 * back to the input internally.
 *
 * \details 
 * Field: ::VTSS_UART_UART_MCR . LB
 */
#define  VTSS_F_UART_UART_MCR_LB              VTSS_BIT(4)

/** 
 * \brief
 * Request to send. This is used to directly control the Request to Send
 * (RTS) output. The RTS output is used to inform the partner that the UART
 * is ready to exchange data.
 * The RTS is still controlled from this field when Auto RTS Flow Control
 * is enabled (MCR.AFCE), but the output can be forced high by the flow
 * control mechanism. If this field is cleared, the UART permanently
 * indicates backpressure to the partner.
 *
 * \details 
 * 0: RTS is set high
 * 1: RTS is set low
 *
 * Field: ::VTSS_UART_UART_MCR . RTS
 */
#define  VTSS_F_UART_UART_MCR_RTS             VTSS_BIT(1)


/** 
 * \brief Line status
 *
 * \details
 * Register: \a UART:UART:LSR
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_LSR(target)           VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Receiver FIFO error bit. This bit is only valid when FIFOs are enabled.
 * This is used to indicate whether there is at least one parity error,
 * framing error, or break indication in the FIFO.
 * This bit is cleared when the LSR is read, the character with the error
 * is at the top of the receiver FIFO, and there are no subsequent errors
 * in the FIFO.
 *
 * \details 
 * 0: No error in Rx FIFO
 * 1: Error in Rx FIFO
 *
 * Field: ::VTSS_UART_UART_LSR . RFE
 */
#define  VTSS_F_UART_UART_LSR_RFE             VTSS_BIT(7)

/** 
 * \brief
 * Transmitter empty bit. If FIFOs are enabled, this bit is set whenever
 * the Transmitter Shift Register and the FIFO are both empty.
 *
 * \details 
 * Field: ::VTSS_UART_UART_LSR . TEMT
 */
#define  VTSS_F_UART_UART_LSR_TEMT            VTSS_BIT(6)

/** 
 * \brief
 * If FIFO (IIR_FCR.FIFOE) and THRE mode are enabled (IER.PTIME), this bit
 * indicates that the Tx FIFO is full. Otherwise, this bit indicates that
 * the Tx FIFO is empty.
 *
 * \details 
 * Field: ::VTSS_UART_UART_LSR . THRE
 */
#define  VTSS_F_UART_UART_LSR_THRE            VTSS_BIT(5)

/** 
 * \brief
 * Break interrupt bit. This is used to indicate the detection of a break
 * sequence on the serial input data.
 * It is set whenever the serial input is held in a logic 0 state for
 * longer than the sum of start time + data bits + parity + stop bits.
 * A break condition on serial input causes one and only one character,
 * consisting of all-zeros, to be received by the UART.
 * In the FIFO mode, the character associated with the break condition is
 * carried through the FIFO and is revealed when the character is at the
 * top of the FIFO. Reading the LSR clears the BI bit. In the non-FIFO
 * mode, the BI indication occurs immediately and persists until the LSR is
 * read.
 *
 * \details 
 * Field: ::VTSS_UART_UART_LSR . BI
 */
#define  VTSS_F_UART_UART_LSR_BI              VTSS_BIT(4)

/** 
 * \brief
 * Framing error bit. This is used to indicate the a framing error in the
 * receiver. A framing error occurs when the receiver does not detect a
 * valid STOP bit in the received data.
 * A framing error is associated with a received character. Therefore, in
 * FIFO mode, an error is revealed when the character with the framing
 * error is at the top of the FIFO. When a framing error occurs, the UART
 * tries to resynchronize. It does this by assuming that the error was due
 * to the start bit of the next character and then continues to receive the
 * other bit, that is, data and/or parity, and then stops. Note that this
 * field is set if a break interrupt has occurred, as indicated by Break
 * Interrupt (LSR.BI).
 * This field is cleared on read.
 *
 * \details 
 * 0: No framing error
 * 1: Framing error
 *
 * Field: ::VTSS_UART_UART_LSR . FE
 */
#define  VTSS_F_UART_UART_LSR_FE              VTSS_BIT(3)

/** 
 * \brief
 * Parity error bit. This is used to indicate the occurrence of a parity
 * error in the receiver if the Parity Enable bit (LCR.PEN) is set.
 * A parity error is associated with a received character. Therefore, in
 * FIFO mode, an error is revealed when the character with the parity error
 * arrives at the top of the FIFO. Note that this field is set if a break
 * interrupt has occurred, as indicated by Break Interrupt (LSR.BI).
 * This field is cleared on read.
 *
 * \details 
 * 0: No parity error
 * 1: Parity error
 *
 * Field: ::VTSS_UART_UART_LSR . PE
 */
#define  VTSS_F_UART_UART_LSR_PE              VTSS_BIT(2)

/** 
 * \brief
 * Overrun error bit. This is used to indicate the occurrence of an overrun
 * error. This occurs if a new data character was received before the
 * previous data was read.
 * In non-FIFO mode, the OE bit is set when a new character arrives before
 * the previous character was read. When this happens, the data in the RBR
 * is overwritten. 
 * In FIFO mode, an overrun error occurs when the FIFO is full and a new
 * character arrives at the receiver. The data in the FIFO is retained and
 * the data in the receive shift register is lost.
 * This field is cleared on read.
 *
 * \details 
 * 0: No overrun error
 * 1: Overrun error
 *
 * Field: ::VTSS_UART_UART_LSR . OE
 */
#define  VTSS_F_UART_UART_LSR_OE              VTSS_BIT(1)

/** 
 * \brief
 * Data ready. This is used to indicate that the receiver contains at least
 * one character in the receiver FIFO. This bit is cleared when the RX FIFO
 * is empty.
 *
 * \details 
 * 0: No data ready
 * 1: Data ready
 *
 * Field: ::VTSS_UART_UART_LSR . DR
 */
#define  VTSS_F_UART_UART_LSR_DR              VTSS_BIT(0)


/** 
 * \brief Modem status
 *
 * \details
 * Register: \a UART:UART:MSR
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_MSR(target)           VTSS_IOREG(target,0x6)

/** 
 * \brief
 * Clear to send. This field indicates the current state of the modem
 * control line, CTS. When the Clear to Send input (CTS) is asserted, it is
 * an indication that the partner is ready to exchange data with the UART.
 *
 * \details 
 * 0: CTS input is deasserted (logic 0)
 * 1: CTS input is asserted (logic 1)
 *
 * Field: ::VTSS_UART_UART_MSR . CTS
 */
#define  VTSS_F_UART_UART_MSR_CTS             VTSS_BIT(4)

/** 
 * \brief
 * Delta clear to send. This is used to indicate that the modem control
 * line, CTS, has changed since the last time the MSR was read. Reading the
 * MSR clears the DCTS bit.
 * Note: If the DCTS bit is not set, the CTS signal is asserted, and a
 * reset occurs (software or otherwise), then the DCTS bit is set when the
 * reset is removed, if the CTS signal remains asserted. A read of the MSR
 * after reset can be performed to prevent unwanted interrupts.
 *
 * \details 
 * 0: No change on CTS since the last read of the MSR
 * 1: Change on CTS since the last read of the MSR
 *
 * Field: ::VTSS_UART_UART_MSR . DCTS
 */
#define  VTSS_F_UART_UART_MSR_DCTS            VTSS_BIT(0)


/** 
 * \brief Scratchpad
 *
 * \details
 * Register: \a UART:UART:SCR
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_SCR(target)           VTSS_IOREG(target,0x7)

/** 
 * \brief
 * This register is for programmers to use as a temporary storage space. It
 * has no functional purpose for the UART.
 *
 * \details 
 * Field: ::VTSS_UART_UART_SCR . SCR
 */
#define  VTSS_F_UART_UART_SCR_SCR(x)          VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_UART_UART_SCR_SCR             VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_UART_UART_SCR_SCR(x)          VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a UART:UART:RESERVED1
 *
 * @param target A \a ::vtss_target_UART_e target
 * @param ri Register: RESERVED1 (??), 0-22
 */
#define VTSS_UART_UART_RESERVED1(target,ri)  VTSS_IOREG(target,0x8 + (ri))

/** 
 * \details 
 * Field: ::VTSS_UART_UART_RESERVED1 . RESERVED1
 */
#define  VTSS_F_UART_UART_RESERVED1_RESERVED1(x)  (x)
#define  VTSS_M_UART_UART_RESERVED1_RESERVED1     0xffffffff
#define  VTSS_X_UART_UART_RESERVED1_RESERVED1(x)  (x)


/** 
 * \brief UART status
 *
 * \details
 * Register: \a UART:UART:USR
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_USR(target)           VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * UART busy.
 *
 * \details 
 * 0: UART is idle or inactive
 * 1: UART is busy (actively transferring data)
 *
 * Field: ::VTSS_UART_UART_USR . BUSY
 */
#define  VTSS_F_UART_UART_USR_BUSY            VTSS_BIT(0)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a UART:UART:RESERVED2
 *
 * @param target A \a ::vtss_target_UART_e target
 * @param ri Register: RESERVED2 (??), 0-8
 */
#define VTSS_UART_UART_RESERVED2(target,ri)  VTSS_IOREG(target,0x20 + (ri))

/** 
 * \details 
 * Field: ::VTSS_UART_UART_RESERVED2 . RESERVED2
 */
#define  VTSS_F_UART_UART_RESERVED2_RESERVED2(x)  (x)
#define  VTSS_M_UART_UART_RESERVED2_RESERVED2     0xffffffff
#define  VTSS_X_UART_UART_RESERVED2_RESERVED2(x)  (x)


/** 
 * \brief Halt tx
 *
 * \details
 * Register: \a UART:UART:HTX
 *
 * @param target A \a ::vtss_target_UART_e target
 */
#define VTSS_UART_UART_HTX(target)           VTSS_IOREG(target,0x29)

/** 
 * \brief
 * This register is use to halt transmissions for testing, so that the
 * transmit FIFO can be filled by the master when FIFOs are enabled.
 *
 * \details 
 * 0: Halt tx disabled
 * 1: Halt tx enabled
 *
 * Field: ::VTSS_UART_UART_HTX . HTX
 */
#define  VTSS_F_UART_UART_HTX_HTX             VTSS_BIT(0)


#endif /* _VTSS_OCELOT_REGS_UART_H_ */
