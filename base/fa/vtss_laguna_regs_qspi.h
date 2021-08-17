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

#ifndef _VTSS_LAGUNA_REGS_QSPI_H_
#define _VTSS_LAGUNA_REGS_QSPI_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a QSPI
 *
 * \see vtss_target_QSPI_e
 *
 * The Quad SPI Interface (QSPI) circuit is a synchronous serial data link
 * that provides
 * communication with external devices in initiator mode.
 * The QSPI can be used in SPI mode to interface serial peripherals (such
 * as ADCs,
 * DACs, LCD controllers, CAN controllers and sensors), or in Serial Memory
 * Mode to
 * interface serial flash memories.
 * The QSPI allows the system to execute code directly from a serial flash
 * memory (XIP)
 * without code shadowing to RAM. The serial flash memory mapping is seen
 * in the system
 * as other memories (ROM, SRAM, DRAM, embedded Flash memory, etc.).
 * With the support of the Quad SPI protocol, the QSPI allows the system to
 * use high performance
 * serial flash memories which are small and inexpensive, in place of
 * larger and
 * more expensive parallel flash memories.
 *
 ***********************************************************************/

/**
 * Register Group: \a QSPI:QSPI_REGS
 *
 * Quad SPI Interface (QSPI) User Interface
 */


/**
 * \brief Control Register
 *
 * \details
 * Control Register
 * Write-only Register
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_CR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_CR(target)            VTSS_IOREG(target,0x0)

/**
 * \brief
 * Last TransferAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: The chip select will be deasserted after the character written in TD
 * has been transferred.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . LASTXFER
 */
#define  VTSS_F_QSPI_QSPI_CR_LASTXFER(x)      VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_QSPI_QSPI_CR_LASTXFER         VTSS_BIT(24)
#define  VTSS_X_QSPI_QSPI_CR_LASTXFER(x)      VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Reset Time-outAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Request a TOUT flag reset.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . RTOUT
 */
#define  VTSS_F_QSPI_QSPI_CR_RTOUT(x)         VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_QSPI_QSPI_CR_RTOUT            VTSS_BIT(10)
#define  VTSS_X_QSPI_QSPI_CR_RTOUT(x)         VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Start TransferAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Starts the transfer when TFRTYP = 0 and SMRM = 1 or when DATAEN = 0.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . STTFR
 */
#define  VTSS_F_QSPI_QSPI_CR_STTFR(x)         VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_QSPI_QSPI_CR_STTFR            VTSS_BIT(9)
#define  VTSS_X_QSPI_QSPI_CR_STTFR(x)         VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Update ConfigurationAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Requests an update of the QSPI Controller core configuration.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . UPDCFG
 */
#define  VTSS_F_QSPI_QSPI_CR_UPDCFG(x)        VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_QSPI_QSPI_CR_UPDCFG           VTSS_BIT(8)
#define  VTSS_X_QSPI_QSPI_CR_UPDCFG(x)        VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * QSPI Software ResetAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Resets the QSPI. A software-triggered hardware reset of the QSPI
 * interface is performed.
 * DMA channels state, DLL state (see DLL) and QSPI_PADCTRL are not
 * affected by a software reset.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . SWRST
 */
#define  VTSS_F_QSPI_QSPI_CR_SWRST(x)         VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_QSPI_QSPI_CR_SWRST            VTSS_BIT(7)
#define  VTSS_X_QSPI_QSPI_CR_SWRST(x)         VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Start REFRESHAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Starts a refresh sequence. QSPI_ISR.RFRSHD_ISR indicates when the
 * refresh sequence is over.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . SRFRSH
 */
#define  VTSS_F_QSPI_QSPI_CR_SRFRSH(x)        VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_QSPI_QSPI_CR_SRFRSH           VTSS_BIT(5)
#define  VTSS_X_QSPI_QSPI_CR_SRFRSH(x)        VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Start Pad CalibrationAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Starts a QSPI pad calibration. QSPI_SR.CALBSY indicates the state of
 * the calibration.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . STPCAL
 */
#define  VTSS_F_QSPI_QSPI_CR_STPCAL(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_QSPI_QSPI_CR_STPCAL           VTSS_BIT(4)
#define  VTSS_X_QSPI_QSPI_CR_STPCAL(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * DLL Off RequestAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Disables the DLL. When the DLL is not locked (DLOCK flags in
 * QSPI_SR), the QSPI Core does not receive a clock and
 * is not functional.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . DLLOFF
 */
#define  VTSS_F_QSPI_QSPI_CR_DLLOFF(x)        VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSPI_QSPI_CR_DLLOFF           VTSS_BIT(3)
#define  VTSS_X_QSPI_QSPI_CR_DLLOFF(x)        VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DLL On RequestAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Enables the DLL. When the DLL is locked (DLOCK flags in QSPI_SR), the
 * QSPI Core receives a clock and is functional.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . DLLON
 */
#define  VTSS_F_QSPI_QSPI_CR_DLLON(x)         VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_CR_DLLON            VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_CR_DLLON(x)         VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * QSPI DisableAs soon as QSPIDIS is set, QSPI finishes its transfer.All
 * pins are set in input mode and no data is received or transmitted.If a
 * transfer is in progress, the transfer is finished before the QSPI is
 * disabled.If both QSPIEN and QSPIDIS are equal to one when the control
 * register is written, the QSPI is disabled.Access: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Disables the QSPI.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . QSPIDIS
 */
#define  VTSS_F_QSPI_QSPI_CR_QSPIDIS(x)       VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_CR_QSPIDIS          VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_CR_QSPIDIS(x)       VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * QSPI EnableAccess: Write-only
 *
 * \details
 * 0: No effect.
 * 1: Enables the QSPI to transfer and receive data.
 *
 * Field: ::VTSS_QSPI_QSPI_CR . QSPIEN
 */
#define  VTSS_F_QSPI_QSPI_CR_QSPIEN(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_CR_QSPIEN           VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_CR_QSPIEN(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Mode Register
 *
 * \details
 * This register can only be written if the bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.

 *
 * Register: \a QSPI:QSPI_REGS:QSPI_MR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_MR(target)            VTSS_IOREG(target,0x1)

/**
 * \brief
 * Minimum Inactive QCS DelayThis field defines the minimum delay between
 * the deactivation and the activation of QCS. The DLYCS time guarantees
 * thetarget minimum deselect time.If DLYCS written to 0, one GCK period is
 * inserted by default.Otherwise, the following equation determines the
 * delay:DLYCS = Minimum inactive x fGCK
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_MR . DLYCS
 */
#define  VTSS_F_QSPI_QSPI_MR_DLYCS(x)         VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_QSPI_QSPI_MR_DLYCS            VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_QSPI_QSPI_MR_DLYCS(x)         VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Delay Between Consecutive Transfers-- SMM = 0This field defines the
 * delay between two consecutive transfers with the same peripheral without
 * removing the chip select.The delay is always inserted after each
 * transfer and before removing the chip select if needed.The following
 * equation determines the delay:DLYBCT = (Delay Between Consecutive
 * Transfers ? fGCK)/32-- SMM = 1This field defines the delay between last
 * QSCK pulse and QCS rise.When DLYBCT is written to 0, no delay is
 * inserted and the clock keeps its duty cycle over the character
 * transfers.The following equation determines the delay:DLYBCT = Delay
 * Between Consecutive Transfers ? fGCK
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_MR . DLYBCT
 */
#define  VTSS_F_QSPI_QSPI_MR_DLYBCT(x)        VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_QSPI_QSPI_MR_DLYBCT           VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_QSPI_QSPI_MR_DLYBCT(x)        VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Output Enable Shift Disabled
 *
 * \details
 * 0: By default, the pad output enable signal is held for one QSCK period
 * during the dummy cycles if QSPI_IFR.NBDUM is
 * not equal to 0.
 * 1: The pad output enable signal is not held for one QSCK period during
 * the dummy cycles.
 *
 * Field: ::VTSS_QSPI_QSPI_MR . OENSD
 */
#define  VTSS_F_QSPI_QSPI_MR_OENSD(x)         VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_QSPI_QSPI_MR_OENSD            VTSS_BIT(15)
#define  VTSS_X_QSPI_QSPI_MR_OENSD(x)         VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Physical Interface Clock Ratio
 *
 * \details
 * 0 RATIO_1_1 The physical interface clock is at the same speed as the
 * QSPI Controller clock.
 * 1 RATIO_1_2 The physical interface clock is twice as fast as the QSPI
 * Controller clock.
 *
 * Field: ::VTSS_QSPI_QSPI_MR . PHYCR
 */
#define  VTSS_F_QSPI_QSPI_MR_PHYCR(x)         VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_QSPI_QSPI_MR_PHYCR            VTSS_BIT(14)
#define  VTSS_X_QSPI_QSPI_MR_PHYCR(x)         VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * QSPI Inter-chip Mode Enable
 *
 * \details
 * 0 (DISABLED): QSPI_WICR.WROPT and QSPI_RICR.RDOPT define the transfer
 * options and QSPI_IFR.NBDUM defines
 * the number of dummy cycles.
 * 1 (ENABLED): No dummy cycles are inserted for write accesses, whatever
 * the value configured in QSPI_IFR.NBDUM. The
 * option field of the frame is automatically generated by the QSPI
 * depending on the type of system bus transfer (the fields
 * QSPI_RICR.RDOPT and QSPI_WICR.WROPT have no effect).
 *
 * Field: ::VTSS_QSPI_QSPI_MR . QICMEN
 */
#define  VTSS_F_QSPI_QSPI_MR_QICMEN(x)        VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_QSPI_QSPI_MR_QICMEN           VTSS_BIT(13)
#define  VTSS_X_QSPI_QSPI_MR_QICMEN(x)        VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Number Of Bits Per Transfer.The NBBITS field determines the number of
 * data bits transferred. Reserved values should not be used.
 *
 * \details
 * 0: 8_BIT  - 8   bits for transfer
 * 8: 16_BIT - 16 bits for transfer
 *
 * Field: ::VTSS_QSPI_QSPI_MR . NBBITS
 */
#define  VTSS_F_QSPI_QSPI_MR_NBBITS(x)        VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_QSPI_QSPI_MR_NBBITS           VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_QSPI_QSPI_MR_NBBITS(x)        VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Tamper Clear Enable
 *
 * \details
 * 0: A tamper detection event has no effect on QSPI scrambling keys.
 * 1: A tamper detection event immediately clears QSPI scrambling keys.
 *
 * Field: ::VTSS_QSPI_QSPI_MR . TAMPCLR
 */
#define  VTSS_F_QSPI_QSPI_MR_TAMPCLR(x)       VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_QSPI_QSPI_MR_TAMPCLR          VTSS_BIT(7)
#define  VTSS_X_QSPI_QSPI_MR_TAMPCLR(x)       VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Chip Select Mode.The CSMODE field determines how the chip select is
 * deasserted.
 *
 * \details
 * 0: NOT_RELOADED   - The chip select is deasserted if QSPI_TDR.TD has not
 * been reloaded before the end of the current
 * transfer.
 * 1: LASTXFER		    - The chip select is deasserted when the bit
 * LASTXFER is written to 1 and the character written in
 * QSPI_TDR.TD has been transferred.
 * 2: SYSTEMATICALLY - The chip select is deasserted systematically after
 * each transfer.
 *
 * Note: This field is forced to LASTXFER when SMM is written to 1
 *
 * Field: ::VTSS_QSPI_QSPI_MR . CSMODE
 */
#define  VTSS_F_QSPI_QSPI_MR_CSMODE(x)        VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_QSPI_QSPI_MR_CSMODE           VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_QSPI_QSPI_MR_CSMODE(x)        VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * DQS Delay Enable
 *
 * \details
 * (DISABLED): DQS Delay cell is disabled.
 * 1 (ENABLED): DQS Delay cell is enabled. The DQS Delay cell automatic
 * refresh is triggered according to the configuration
 * of QSPI_REFRESH.
 *
 * Field: ::VTSS_QSPI_QSPI_MR . DQSDLYEN
 */
#define  VTSS_F_QSPI_QSPI_MR_DQSDLYEN(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSPI_QSPI_MR_DQSDLYEN         VTSS_BIT(3)
#define  VTSS_X_QSPI_QSPI_MR_DQSDLYEN(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Wait Data Read Before Transfer
 *
 * \details
 * 0 (DISABLED): No effect. In SPI mode, a transfer can be initiated
 * whatever the state of QSPI_RDR is.
 * 1 (ENABLED): In SPI mode, a transfer can start only if QSPI_RDR is
 * empty, i.e., does not contain any unread data. This
 * mode prevents overrun error in reception.
 *
 * Field: ::VTSS_QSPI_QSPI_MR . WDRBT
 */
#define  VTSS_F_QSPI_QSPI_MR_WDRBT(x)         VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_MR_WDRBT            VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_MR_WDRBT(x)         VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Serial Memory Mode
 *
 * \details
 * 0 (SPI): The QSPI is in SPI Mode.
 * 1 (MEMORY): The QSPI is in Serial Memory Mode.
 *
 * Field: ::VTSS_QSPI_QSPI_MR . SMM
 */
#define  VTSS_F_QSPI_QSPI_MR_SMM(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_MR_SMM              VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_MR_SMM(x)           VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Receive Data Register
 *
 * \details
 * Register: \a QSPI:QSPI_REGS:QSPI_RDR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_RDR(target)           VTSS_IOREG(target,0x2)

/**
 * \brief
 * Receive DataData received by the QSPI is stored in this register
 * right-justified. Unused bits read zero.QSPI_MR.SMM = 0RD is defined by
 * QSPI_MR.NBBITS.QSPI_MR.SMM = 1RD is 8 bits or 16 bits in Octal DDR Mode.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_RDR . RD
 */
#define  VTSS_F_QSPI_QSPI_RDR_RD(x)           VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSPI_QSPI_RDR_RD              VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSPI_QSPI_RDR_RD(x)           VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief QSPI Transmit Data Register
 *
 * \details
 * QSPI Transmit Data Register
 * Access: Write-only
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_TDR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_TDR(target)           VTSS_IOREG(target,0x3)

/**
 * \brief
 * Transmit DataData to be transmitted by the QSPI is stored in this
 * register. Information to be transmitted must be written to the
 * transmitdata register in a right-justified format.QSPI_MR.SMM = 0TD is
 * defined by QSPI_MR.NBBITS field.QSPI_MR.SMM = 1TD is 8 bits or 16 bits
 * in Octal DDR Mode.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_TDR . TD
 */
#define  VTSS_F_QSPI_QSPI_TDR_TD(x)           VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSPI_QSPI_TDR_TD              VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSPI_QSPI_TDR_TD(x)           VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Interrupt Status Register
 *
 * \details
 * Interrupt Status Register
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_ISR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_ISR(target)           VTSS_IOREG(target,0x4)

/**
 * \brief
 * QSPI Time-out
 *
 * \details
 * 0: No QSPI time-out occurred since the last write of RTOUT bit on
 * QSPI_CR.
 * 1: At least one QSPI time-out occurred since the last write of RTOUT bit
 * on QSPI_CR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . TOUT_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_TOUT_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_QSPI_QSPI_ISR_TOUT_ISR        VTSS_BIT(17)
#define  VTSS_X_QSPI_QSPI_ISR_TOUT_ISR(x)     VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Refresh Done
 *
 * \details
 * 0: No refresh done event occurred since the last read of QSPI_ISR.
 * 1: One refresh done event has been detected since the end of the last
 * refresh command or the last read of QSPI_ISR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . RFRSHD_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_RFRSHD_ISR(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_QSPI_QSPI_ISR_RFRSHD_ISR      VTSS_BIT(16)
#define  VTSS_X_QSPI_QSPI_ISR_RFRSHD_ISR(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Chip Select Rise Autoclear
 *
 * \details
 * 0: No chip select rise has been detected since beginning of the last
 * command or the last read of QSPI_ISR.
 * 1: One chip select rise has been detected since the beginning of the
 * last command or the last read of QSPI_ISR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . CSRA_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_CSRA_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_QSPI_QSPI_ISR_CSRA_ISR        VTSS_BIT(15)
#define  VTSS_X_QSPI_QSPI_ISR_CSRA_ISR(x)     VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Chip Select Fall Autoclear
 *
 * \details
 * 0: No chip select fall has been detected since end of the last command
 * or the last read of QSPI_ISR.
 * 1: One chip select fall has been detected since the end of the last
 * command or the last read of QSPI_ISR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . CSFA_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_CSFA_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_QSPI_QSPI_ISR_CSFA_ISR        VTSS_BIT(14)
#define  VTSS_X_QSPI_QSPI_ISR_CSFA_ISR(x)     VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * QSPI Interrupt Rise
 *
 * \details
 * 0: No rising of the QSPI memory interrupt line has been detected since
 * the last read of QSPI_ISR.
 * 1: At least one QSPI memory interrupt line rising edge occurred since
 * the last read of QSPI_ISR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . QITR_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_QITR_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_QSPI_QSPI_ISR_QITR_ISR        VTSS_BIT(13)
#define  VTSS_X_QSPI_QSPI_ISR_QITR_ISR(x)     VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * QSPI Interrupt Fall
 *
 * \details
 * 0: No falling of the QSPI memory interrupt line has been detected since
 * the last read of QSPI_ISR.
 * 1: At least one QSPI memory interrupt line falling edge occurred since
 * the last read of QSPI_ISR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . QITF_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_QITF_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_QSPI_QSPI_ISR_QITF_ISR        VTSS_BIT(12)
#define  VTSS_X_QSPI_QSPI_ISR_QITF_ISR(x)     VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Last Write Access (cleared on read)
 *
 * \details
 * 0: Last write access has not been sent since the last read of QSPI_SR or
 * NBWRA = 0.
 * 1: At least one last write access has been sent since the last read of
 * QSPI_SR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . LWRA_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_LWRA_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_QSPI_QSPI_ISR_LWRA_ISR        VTSS_BIT(11)
#define  VTSS_X_QSPI_QSPI_ISR_LWRA_ISR(x)     VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Instruction End Status (cleared on read)
 *
 * \details
 * 0: No instruction end has been detected since the last read of QSPI_SR.
 * 1: At least one instruction end has been detected since the last read of
 * QSPI_SR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . INSTRE_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_INSTRE_ISR(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_QSPI_QSPI_ISR_INSTRE_ISR      VTSS_BIT(10)
#define  VTSS_X_QSPI_QSPI_ISR_INSTRE_ISR(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Chip Select Rise (cleared on read)
 *
 * \details
 * 0: No chip select rise has been detected since the last read of QSPI_SR.
 * 1: At least one chip select rise has been detected since the last read
 * of QSPI_SR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . CSR_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_CSR_ISR(x)      VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_QSPI_QSPI_ISR_CSR_ISR         VTSS_BIT(8)
#define  VTSS_X_QSPI_QSPI_ISR_CSR_ISR(x)      VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Overrun Error Status (cleared on read)An overrun occurs when QSPI_RDR is
 * loaded at least twice from the serializer since the last read of the
 * QSPI_RDR.
 *
 * \details
 * 0: No overrun has been detected since the last read of QSPI_ISR.
 * 1: At least one overrun error has occurred since the last read of
 * QSPI_ISR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . OVRES_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_OVRES_ISR(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSPI_QSPI_ISR_OVRES_ISR       VTSS_BIT(3)
#define  VTSS_X_QSPI_QSPI_ISR_OVRES_ISR(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Transmission Registers Empty (cleared by writing QSPI_TDR)
 *
 * \details
 * 0: As soon as data is written in QSPI_TDR.
 * 1: QSPI_TDR and the internal shifter are empty. If a transfer delay has
 * been defined, TXEMPTY is set after the completion
 * of such delay.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . TXEMPTY_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_TXEMPTY_ISR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_ISR_TXEMPTY_ISR     VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_ISR_TXEMPTY_ISR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Transmit Data Register Empty (cleared by writing QSPI_TDR)
 *
 * \details
 * 0: Data has been written to QSPI_TDR and not yet transferred to the
 * serializer.
 * 1: The last data written in the QSPI_TDR has been transferred to the
 * serializer.
 * TDRE equals zero when the QSPI is disabled or at reset. The QSPI enable
 * command sets this bit to one.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . TDRE_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_TDRE_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_ISR_TDRE_ISR        VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_ISR_TDRE_ISR(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Receive Data Register Full (cleared by reading QSPI_RDR)
 *
 * \details
 * 0: No data has been received since the last read of QSPI_RDR.
 * 1: Data has been received and the received data has been transferred
 * from the serializer to QSPI_RDR since the last read
 * of QSPI_RDR.
 *
 * Field: ::VTSS_QSPI_QSPI_ISR . RDRF_ISR
 */
#define  VTSS_F_QSPI_QSPI_ISR_RDRF_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_ISR_RDRF_ISR        VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_ISR_RDRF_ISR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Interrupt Enable Register
 *
 * \details
 * Access: Write-only
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_IER
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_IER(target)           VTSS_IOREG(target,0x5)

/**
 * \brief
 * QSPI Time-out Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the TOUT interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IER . TOUT_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_TOUT_IER(x)     VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_QSPI_QSPI_IER_TOUT_IER        VTSS_BIT(17)
#define  VTSS_X_QSPI_QSPI_IER_TOUT_IER(x)     VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Refresh Done Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the RFRSHD interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IER . RFRSHD_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_RFRSHD_IER(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_QSPI_QSPI_IER_RFRSHD_IER      VTSS_BIT(16)
#define  VTSS_X_QSPI_QSPI_IER_RFRSHD_IER(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Chip Select Rise Autoclear Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables the CSRA interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IER . CSRA_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_CSRA_IER(x)     VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_QSPI_QSPI_IER_CSRA_IER        VTSS_BIT(15)
#define  VTSS_X_QSPI_QSPI_IER_CSRA_IER(x)     VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Chip Select Fall Autoclear Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables CSFA Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . CSFA_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_CSFA_IER(x)     VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_QSPI_QSPI_IER_CSFA_IER        VTSS_BIT(14)
#define  VTSS_X_QSPI_QSPI_IER_CSFA_IER(x)     VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * QSPI Interrupt Rise Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables QITR Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . QITR_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_QITR_IER(x)     VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_QSPI_QSPI_IER_QITR_IER        VTSS_BIT(13)
#define  VTSS_X_QSPI_QSPI_IER_QITR_IER(x)     VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Last Write Access Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables QITF Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . QITF_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_QITF_IER(x)     VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_QSPI_QSPI_IER_QITF_IER        VTSS_BIT(12)
#define  VTSS_X_QSPI_QSPI_IER_QITF_IER(x)     VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Last Write Access Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables LWRA Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . LWRA_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_LWRA_IER(x)     VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_QSPI_QSPI_IER_LWRA_IER        VTSS_BIT(11)
#define  VTSS_X_QSPI_QSPI_IER_LWRA_IER(x)     VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Instruction End Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables Instruction End Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . INSTRE_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_INSTRE_IER(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_QSPI_QSPI_IER_INSTRE_IER      VTSS_BIT(10)
#define  VTSS_X_QSPI_QSPI_IER_INSTRE_IER(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Overrun Error Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enables Chip Select Rise Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . CSR_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_CSR_IER(x)      VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_QSPI_QSPI_IER_CSR_IER         VTSS_BIT(8)
#define  VTSS_X_QSPI_QSPI_IER_CSR_IER(x)      VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Overrun Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables Overrun Error interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IER . OVRES_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_OVRES_IER(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSPI_QSPI_IER_OVRES_IER       VTSS_BIT(3)
#define  VTSS_X_QSPI_QSPI_IER_OVRES_IER(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Transmission Registers Empty Enable
 *
 * \details
 * 0: No effect
 * 1: EnableTransmission Registers Empty Ineterrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . TXEMPTY_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_TXEMPTY_IER(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_IER_TXEMPTY_IER     VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_IER_TXEMPTY_IER(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Transmit Data Register Empty Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enable Transmit Data Register. Empty Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . TDRE_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_TDRE_IER(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_IER_TDRE_IER        VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_IER_TDRE_IER(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Receive Data Register Full Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: Enable Receive Data Register Full Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IER . RDRF_IER
 */
#define  VTSS_F_QSPI_QSPI_IER_RDRF_IER(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_IER_RDRF_IER        VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_IER_RDRF_IER(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Interrupt Disable Register
 *
 * \details
 * Access: Write-only
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_IDR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_IDR(target)           VTSS_IOREG(target,0x6)

/**
 * \brief
 * QSPI Time-out Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables Time-out Interrupt interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . TOUT_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_TOUT_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_QSPI_QSPI_IDR_TOUT_IDR        VTSS_BIT(17)
#define  VTSS_X_QSPI_QSPI_IDR_TOUT_IDR(x)     VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Refresh Done Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables Refresh Done Interrupt interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . RFRSHD_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_RFRSHD_IDR(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_QSPI_QSPI_IDR_RFRSHD_IDR      VTSS_BIT(16)
#define  VTSS_X_QSPI_QSPI_IDR_RFRSHD_IDR(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Chip Select Rise Autoclear Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables Chip Select Rise Autoclear Interrupt interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . CSRA_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_CSRA_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_QSPI_QSPI_IDR_CSRA_IDR        VTSS_BIT(15)
#define  VTSS_X_QSPI_QSPI_IDR_CSRA_IDR(x)     VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Chip Select Fall Autoclear Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables Chip Select Fall Autoclear Interrupt interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . CSFA_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_CSFA_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_QSPI_QSPI_IDR_CSFA_IDR        VTSS_BIT(14)
#define  VTSS_X_QSPI_QSPI_IDR_CSFA_IDR(x)     VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * QSPI Interrupt Rise Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the corresponding interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . QITR_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_QITR_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_QSPI_QSPI_IDR_QITR_IDR        VTSS_BIT(13)
#define  VTSS_X_QSPI_QSPI_IDR_QITR_IDR(x)     VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * QSPI Interrupt Fall Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the corresponding interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . QITF_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_QITF_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_QSPI_QSPI_IDR_QITF_IDR        VTSS_BIT(12)
#define  VTSS_X_QSPI_QSPI_IDR_QITF_IDR(x)     VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Last Write Access Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables the corresponding interrupt.
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . LWRA_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_LWRA_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_QSPI_QSPI_IDR_LWRA_IDR        VTSS_BIT(11)
#define  VTSS_X_QSPI_QSPI_IDR_LWRA_IDR(x)     VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Instruction End Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables Instruction End Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . INSTRE_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_INSTRE_IDR(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_QSPI_QSPI_IDR_INSTRE_IDR      VTSS_BIT(10)
#define  VTSS_X_QSPI_QSPI_IDR_INSTRE_IDR(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Chip Select Rise Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables Chip Select Rise Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . CSR_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_CSR_IDR(x)      VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_QSPI_QSPI_IDR_CSR_IDR         VTSS_BIT(8)
#define  VTSS_X_QSPI_QSPI_IDR_CSR_IDR(x)      VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Overrun Error Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables Overrun Error Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . OVRES_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_OVRES_IDR(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSPI_QSPI_IDR_OVRES_IDR       VTSS_BIT(3)
#define  VTSS_X_QSPI_QSPI_IDR_OVRES_IDR(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Transmission Registers Empty Disable
 *
 * \details
 * 0: No effect
 * 1: Disables Transmission Registers Empty
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . TXEMPTY_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_TXEMPTY_IDR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_IDR_TXEMPTY_IDR     VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_IDR_TXEMPTY_IDR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Transmit Data Register Empty Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables Transmit Data Register Empty Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . TDRE_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_TDRE_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_IDR_TDRE_IDR        VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_IDR_TDRE_IDR(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Receive Data Register Full Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Disables Receive Data Register Full Interrupt
 *
 * Field: ::VTSS_QSPI_QSPI_IDR . RDRF_IDR
 */
#define  VTSS_F_QSPI_QSPI_IDR_RDRF_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_IDR_RDRF_IDR        VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_IDR_RDRF_IDR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Interrupt Mask Register
 *
 * \details
 * Register: \a QSPI:QSPI_REGS:QSPI_IMR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_IMR(target)           VTSS_IOREG(target,0x7)

/**
 * \brief
 * QSPI Time-out Interrupt Mask
 *
 * \details
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . TOUT_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_TOUT_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_QSPI_QSPI_IMR_TOUT_IMR        VTSS_BIT(17)
#define  VTSS_X_QSPI_QSPI_IMR_TOUT_IMR(x)     VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Refresh Done Interrupt Mask
 *
 * \details
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . RFRSHD_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_RFRSHD_IMR(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_QSPI_QSPI_IMR_RFRSHD_IMR      VTSS_BIT(16)
#define  VTSS_X_QSPI_QSPI_IMR_RFRSHD_IMR(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Chip Select Rise Autoclear Interrupt Mask
 *
 * \details
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . CSRA_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_CSRA_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_QSPI_QSPI_IMR_CSRA_IMR        VTSS_BIT(15)
#define  VTSS_X_QSPI_QSPI_IMR_CSRA_IMR(x)     VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Chip Select Fall Autoclear Interrupt Mask
 *
 * \details
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . CSFA_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_CSFA_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_QSPI_QSPI_IMR_CSFA_IMR        VTSS_BIT(14)
#define  VTSS_X_QSPI_QSPI_IMR_CSFA_IMR(x)     VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * QSPI Interrupt Rise Interrupt Mask
 *
 * \details
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . QITR_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_QITR_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_QSPI_QSPI_IMR_QITR_IMR        VTSS_BIT(13)
#define  VTSS_X_QSPI_QSPI_IMR_QITR_IMR(x)     VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * QSPI Interrupt Fall Interrupt Mask
 *
 * \details
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . QITF_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_QITF_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_QSPI_QSPI_IMR_QITF_IMR        VTSS_BIT(12)
#define  VTSS_X_QSPI_QSPI_IMR_QITF_IMR(x)     VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Last Write Access Interrupt Mask
 *
 * \details
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . LWRA_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_LWRA_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_QSPI_QSPI_IMR_LWRA_IMR        VTSS_BIT(11)
#define  VTSS_X_QSPI_QSPI_IMR_LWRA_IMR(x)     VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Instruction End Interrupt Mask
 *
 * \details
 * 0: Instruction End Interrupt is not enabled
 * 1: Instruction End Interrupt is enabled
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . INSTRE_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_INSTRE_IMR(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_QSPI_QSPI_IMR_INSTRE_IMR      VTSS_BIT(10)
#define  VTSS_X_QSPI_QSPI_IMR_INSTRE_IMR(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Chip Select Rise Interrupt Mask
 *
 * \details
 * 0: Chip Select Rise Interrupt is not enabled
 * 1: Chip Select Rise Interrupt is enabled
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . CSR_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_CSR_IMR(x)      VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_QSPI_QSPI_IMR_CSR_IMR         VTSS_BIT(8)
#define  VTSS_X_QSPI_QSPI_IMR_CSR_IMR(x)      VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Overrun Error Interrupt Mask
 *
 * \details
 * 0: Overrun Error Interrupt is not enabled
 * 1: Overrun Error Interrupt is enabled
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . OVRES_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_OVRES_IMR(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSPI_QSPI_IMR_OVRES_IMR       VTSS_BIT(3)
#define  VTSS_X_QSPI_QSPI_IMR_OVRES_IMR(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Transmission Registers Empty Mask
 *
 * \details
 * 0: Transmission Registers Empty Interrupt is not enabled
 * 1: Transmission Registers Empty Interrupt is enabled
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . TXEMPTY_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_TXEMPTY_IMR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_IMR_TXEMPTY_IMR     VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_IMR_TXEMPTY_IMR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Transmit Data Register Empty Interrupt Mask
 *
 * \details
 * 0: Transmit Data Register Empty Interrupt is not enabled
 * 1: Transmit Data Register Empty Interrupt is enabled
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . TDRE_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_TDRE_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_IMR_TDRE_IMR        VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_IMR_TDRE_IMR(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Receive Data Register Full Interrupt Mask
 *
 * \details
 * 0: Receive Data Register Full Interrupt  is not enabled.
 * 1: Receive Data Register Full Interrupt is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IMR . RDRF_IMR
 */
#define  VTSS_F_QSPI_QSPI_IMR_RDRF_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_IMR_RDRF_IMR        VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_IMR_RDRF_IMR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Serial Clock Register
 *
 * \details
 * QSPI Serial Clock Register
 * This register can only be written if the bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_SCR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_SCR(target)           VTSS_IOREG(target,0x8)

/**
 * \brief
 * Delay Before QSCK.This field defines the delay from QCS valid to the
 * first valid QSCK transition.When DLYBS equals zero, the QCS valid to
 * QSCK transition is 1/2 the QSCK clock period.Otherwise, the following
 * equation determines the delay:DLYBS = Delay Before QSCK x fGCK
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_SCR . DLYBS
 */
#define  VTSS_F_QSPI_QSPI_SCR_DLYBS(x)        VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_QSPI_QSPI_SCR_DLYBS           VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_QSPI_QSPI_SCR_DLYBS(x)        VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Clock Phase.CPHA determines which edge of SPCK causes data to change and
 * which edge causes data to be captured. CPHA is usedwith CPOL to produce
 * the required clock/data relationship between initiator and target
 * devices.
 *
 * \details
 * 0: Data is captured on the leading edge of SPCK and changed on the
 * following edge of SPCK.
 * 1: Data is changed on the leading edge of SPCK and captured on the
 * following edge of SPCK.
 *
 * Field: ::VTSS_QSPI_QSPI_SCR . CPHA
 */
#define  VTSS_F_QSPI_QSPI_SCR_CPHA(x)         VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_SCR_CPHA            VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_SCR_CPHA(x)         VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Clock PolarityCPOL is used to determine the inactive state value of the
 * serial clock (SPCK). It is used with CPHA to produce the
 * requiredclock/data relationship between initiator and target devices.
 *
 * \details
 * 0: The inactive state value of SPCK is logic level zero.
 * 1: The inactive state value of SPCK is logic level one.
 *
 * Field: ::VTSS_QSPI_QSPI_SCR . CPOL
 */
#define  VTSS_F_QSPI_QSPI_SCR_CPOL(x)         VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_SCR_CPOL            VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_SCR_CPOL(x)         VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Status Register
 *
 * \details
 * QSPI Status Register
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_SR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_SR(target)            VTSS_IOREG(target,0x9)

/**
 * \brief
 * HQSPI_VERSIONThis field will be set in case HQSPI VERSION is greater
 * than 0x200.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_SR . HQSPI_VERSION
 */
#define  VTSS_F_QSPI_QSPI_SR_HQSPI_VERSION(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_QSPI_QSPI_SR_HQSPI_VERSION    VTSS_BIT(31)
#define  VTSS_X_QSPI_QSPI_SR_HQSPI_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * Pad Calibration Busy
 *
 * \details
 * 0: Pad calibration is not ongoing.
 * 1: Pad calibration is ongoing.
 *
 * Field: ::VTSS_QSPI_QSPI_SR . CALBSY
 */
#define  VTSS_F_QSPI_QSPI_SR_CALBSY(x)        VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_QSPI_QSPI_SR_CALBSY           VTSS_BIT(6)
#define  VTSS_X_QSPI_QSPI_SR_CALBSY(x)        VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * DLL Lock
 *
 * \details
 * 0: DLL is not locked. The QSPI Controller and physical interface have
 * not received a clock yet.
 * 1: DLL is locked. The QSPI Controller and physical interface have
 * received a clock.
 *
 * Field: ::VTSS_QSPI_QSPI_SR . DLOCK
 */
#define  VTSS_F_QSPI_QSPI_SR_DLOCK(x)         VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_QSPI_QSPI_SR_DLOCK            VTSS_BIT(5)
#define  VTSS_X_QSPI_QSPI_SR_DLOCK(x)         VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * QSPI Idle
 *
 * \details
 * 0: The QSPI is not in Idle state (either transmitting or Chip Select is
 * active).
 * 1: The QSPI is in Idle state (not transmitting and Chip Select is
 * inactive).
 *
 * Field: ::VTSS_QSPI_QSPI_SR . HIDLE
 */
#define  VTSS_F_QSPI_QSPI_SR_HIDLE(x)         VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_QSPI_QSPI_SR_HIDLE            VTSS_BIT(4)
#define  VTSS_X_QSPI_QSPI_SR_HIDLE(x)         VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Read Busy
 *
 * \details
 * 0: The AHB interface has no activity.
 * 1: The AHB interface is currently processing accesses.
 *
 * Field: ::VTSS_QSPI_QSPI_SR . RBUSY
 */
#define  VTSS_F_QSPI_QSPI_SR_RBUSY(x)         VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSPI_QSPI_SR_RBUSY            VTSS_BIT(3)
#define  VTSS_X_QSPI_QSPI_SR_RBUSY(x)         VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Chip Select Status
 *
 * \details
 * 0: The chip select is asserted.
 * 1: The chip select is not asserted.
 *
 * Field: ::VTSS_QSPI_QSPI_SR . CSS
 */
#define  VTSS_F_QSPI_QSPI_SR_CSS(x)           VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_SR_CSS              VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_SR_CSS(x)           VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * QSPI Enable Status
 *
 * \details
 * 0: The QSPI is disabled.
 * 1: The QSPI is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_SR . QSPIENS
 */
#define  VTSS_F_QSPI_QSPI_SR_QSPIENS(x)       VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_SR_QSPIENS          VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_SR_QSPIENS(x)       VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Synchronization Busy
 *
 * \details
 * 0: No event synchronization between the QSPI Controller interface and
 * QSPI Controller core is ongoing. Register accesses
 * requiring synchronization are allowed, see Register Synchronization.
 * 1: Event synchronization between the QSPI Controller interface and QSPI
 * Controller core is ongoing. Register accesses
 * requiring synchronization are not allowed, see Register Synchronization.
 *
 * Field: ::VTSS_QSPI_QSPI_SR . SYNCBSY
 */
#define  VTSS_F_QSPI_QSPI_SR_SYNCBSY(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_SR_SYNCBSY          VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_SR_SYNCBSY(x)       VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Instruction Address Register
 *
 * \details
 * QSPI Instruction Address Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_IAR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_IAR(target)           VTSS_IOREG(target,0xc)

/**
 * \brief
 * Address.Address to send to the serial flash memory in the instruction
 * frame.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_IAR . ADDR
 */
#define  VTSS_F_QSPI_QSPI_IAR_ADDR(x)         (x)
#define  VTSS_M_QSPI_QSPI_IAR_ADDR            0xffffffff
#define  VTSS_X_QSPI_QSPI_IAR_ADDR(x)         (x)


/**
 * \brief Write Instruction Code Register
 *
 * \details
 * Write Instruction Code Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_WICR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_WICR(target)          VTSS_IOREG(target,0xd)

/**
 * \brief
 * Write Option CodeOption code to send to the serial Flash memory in case
 * of write transfer.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_WICR . WROPT
 */
#define  VTSS_F_QSPI_QSPI_WICR_WROPT(x)       VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_QSPI_QSPI_WICR_WROPT          VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_QSPI_QSPI_WICR_WROPT(x)       VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Write Instruction CodeInstruction code to send to the serial Flash
 * memory in case of write transfer.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_WICR . WRINST
 */
#define  VTSS_F_QSPI_QSPI_WICR_WRINST(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSPI_QSPI_WICR_WRINST         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSPI_QSPI_WICR_WRINST(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief QSPI Instruction Frame Register
 *
 * \details
 * QSPI Instruction Frame Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_IFR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_IFR(target)           VTSS_IOREG(target,0xe)

/**
 * \brief
 * Protocol Type
 *
 * \details
 * 0: STD_SPI Standard (Q)SPI Protocol
 * 1: TWIN_QUAD Twin-Quad Protocol
 * 2: OCTAFLASH OctaFlash Protocol
 * 3: HYPERFLASH HyperFlash Protocol
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . PROTTYP
 */
#define  VTSS_F_QSPI_QSPI_IFR_PROTTYP(x)      VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_QSPI_QSPI_IFR_PROTTYP         VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_QSPI_QSPI_IFR_PROTTYP(x)      VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * HyperFlash Write Buffer Enable
 *
 * \details
 * 0: No effect.
 * 1: Each write access received on the AHB interface generates a new
 * command. IMPORTANT: Mandatory if HyperFlash
 * Write Buffer feature is used.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . HFWBEN
 */
#define  VTSS_F_QSPI_QSPI_IFR_HFWBEN(x)       VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_QSPI_QSPI_IFR_HFWBEN          VTSS_BIT(27)
#define  VTSS_X_QSPI_QSPI_IFR_HFWBEN(x)       VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * DDR Mode Command Enable
 *
 * \details
 * 0 (DISABLED): Transfer of instruction field is performed in Single Data
 * Rate mode even if DDREN is written to 1.
 * 1 (ENABLED): Transfer of instruction field is performed in Double Data
 * Rate mode if DDREN bit is written to 1. If DDREN
 * is written to 0, the instruction field is sent in Single Data Rate mode.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . DDRCMDEN
 */
#define  VTSS_F_QSPI_QSPI_IFR_DDRCMDEN(x)     VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_QSPI_QSPI_IFR_DDRCMDEN        VTSS_BIT(26)
#define  VTSS_X_QSPI_QSPI_IFR_DDRCMDEN(x)     VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * DQS Sampling Enable
 *
 * \details
 * 0: Data from the memory are not sampled with DQS signal.
 * 1: Data from the memory are sampled with DQS signal.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . DQSEN
 */
#define  VTSS_F_QSPI_QSPI_IFR_DQSEN(x)        VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_QSPI_QSPI_IFR_DQSEN           VTSS_BIT(25)
#define  VTSS_X_QSPI_QSPI_IFR_DQSEN(x)        VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * APB Transfer Type
 *
 * \details
 * 0: APB register transfer to the memory is a write transfer. Used when
 * TRFTYP is written to 0 and SMRM to 1.
 * 1: APB register transfer to the memory is a read transfer. Used when
 * TRFTYP is written to 0 and SMRM to 1.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . APBTFRTYP
 */
#define  VTSS_F_QSPI_QSPI_IFR_APBTFRTYP(x)    VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_QSPI_QSPI_IFR_APBTFRTYP       VTSS_BIT(24)
#define  VTSS_X_QSPI_QSPI_IFR_APBTFRTYP(x)    VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Serial Memory Register Mode
 *
 * \details
 * 0: Serial Memory registers are written via AHB access. See Instruction
 * Frame Transmission in QSPI DOS for details.
 * 1: Serial Memory registers are written via APB access. See Instruction
 * Frame Transmission in QSPI DOS for details.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . SMRM
 */
#define  VTSS_F_QSPI_QSPI_IFR_SMRM(x)         VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_QSPI_QSPI_IFR_SMRM            VTSS_BIT(23)
#define  VTSS_X_QSPI_QSPI_IFR_SMRM(x)         VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Endianness
 *
 * \details
 * 0: Data are sent in little-endian format to the memory.
 * 1: Data are sent in big-endian format to the memory.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . END
 */
#define  VTSS_F_QSPI_QSPI_IFR_END(x)          VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_QSPI_QSPI_IFR_END             VTSS_BIT(22)
#define  VTSS_X_QSPI_QSPI_IFR_END(x)          VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Number Of Dummy Cycles.The NBDUM field defines the number of dummy
 * cycles required by the serial flash memory before data transfer.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_IFR . NBDUM
 */
#define  VTSS_F_QSPI_QSPI_IFR_NBDUM(x)        VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_QSPI_QSPI_IFR_NBDUM           VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_QSPI_QSPI_IFR_NBDUM(x)        VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 * DDR Mode EnableNote: DDRCMDEN defines how the instruction field is sent
 * when Double Data Rate mode is enabled. If DDRCMDEN is at 0,
 * theinstruction field is sent in Single Data Rate mode.
 *
 * \details
 * 0 (DISABLED): Transfers are performed in Single Data Rate mode.
 * 1 (ENABLED): Transfers are performed in Double Data Rate mode, whereas
 * the instruction field is still transferred in Single
 * Data Rate mode.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . DDREN
 */
#define  VTSS_F_QSPI_QSPI_IFR_DDREN(x)        VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_QSPI_QSPI_IFR_DDREN           VTSS_BIT(15)
#define  VTSS_X_QSPI_QSPI_IFR_DDREN(x)        VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Continuous Read Mode
 *
 * \details
 * 0: (DISABLED): The Continuous Read Mode is disabled.
 * 1: (ENABLED): The Continuous Read Mode is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . CRM
 */
#define  VTSS_F_QSPI_QSPI_IFR_CRM(x)          VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_QSPI_QSPI_IFR_CRM             VTSS_BIT(14)
#define  VTSS_X_QSPI_QSPI_IFR_CRM(x)          VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Data Transfer Type
 *
 * \details
 * 0: TRSFR_REGISTER Read/Write transfer from the serial memory. Read at
 * random location (fetch) in the serial
 * Flash memory is not possible.
 * 1 TRSFR_MEMORY Read/Write data transfer from the serial memory. If
 * enabled, scrambling is performed. Read
 * at random location (fetch) in the serial Flash memory is possible.
 * Transfers are launched only
 * through AHB interface.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . TFRTYP
 */
#define  VTSS_F_QSPI_QSPI_IFR_TFRTYP(x)       VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_QSPI_QSPI_IFR_TFRTYP          VTSS_BIT(12)
#define  VTSS_X_QSPI_QSPI_IFR_TFRTYP(x)       VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Address Length.The ADDRL bit determines the length of the address.
 *
 * \details
 * 0:	8_BIT 8-bit address size
 * 1:  16_BIT 16-bit address size
 * 2:  24_BIT 24-bit address size
 * 3:  32_BIT 32-bit address size
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . ADDRL
 */
#define  VTSS_F_QSPI_QSPI_IFR_ADDRL(x)        VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_QSPI_QSPI_IFR_ADDRL           VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_QSPI_QSPI_IFR_ADDRL(x)        VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * Option Code Length.The OPTL field determines the length of the option
 * code. The value written in OPTL must be coherent with value written
 * inthe field WIDTH. For example: OPTL = 0 (1-bit option code) is not
 * coherent with WIDTH = 6 (option code sent with Quad-SPI protocol, thus
 * the minimum length of the option code is 4-bit).
 *
 * \details
 * 0: OPTION_1BIT The option code is 1 bit long.
 * 1: OPTION_2BIT The option code is 2 bits long.
 * 2: OPTION_4BIT The option code is 4 bits long.
 * 3: OPTION_8BIT The option code is 8 bits long.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . OPTL
 */
#define  VTSS_F_QSPI_QSPI_IFR_OPTL(x)         VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_QSPI_QSPI_IFR_OPTL            VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_QSPI_QSPI_IFR_OPTL(x)         VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Data Enable
 *
 * \details
 * 0: No data is sent/received to/from the serial flash memory.
 * 1: Data is sent/received to/from the serial flash memory.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . DATAEN
 */
#define  VTSS_F_QSPI_QSPI_IFR_DATAEN(x)       VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_QSPI_QSPI_IFR_DATAEN          VTSS_BIT(7)
#define  VTSS_X_QSPI_QSPI_IFR_DATAEN(x)       VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Option Enable
 *
 * \details
 * 0: The option is not sent to the serial flash memory.
 * 1: The option is sent to the serial flash memory.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . OPTEN
 */
#define  VTSS_F_QSPI_QSPI_IFR_OPTEN(x)        VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_QSPI_QSPI_IFR_OPTEN           VTSS_BIT(6)
#define  VTSS_X_QSPI_QSPI_IFR_OPTEN(x)        VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Address Enable
 *
 * \details
 * 0: The transfer address is not sent to the serial flash memory.
 * 1: The transfer address is sent to the serial flash memory.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . ADDREN
 */
#define  VTSS_F_QSPI_QSPI_IFR_ADDREN(x)       VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_QSPI_QSPI_IFR_ADDREN          VTSS_BIT(5)
#define  VTSS_X_QSPI_QSPI_IFR_ADDREN(x)       VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Instruction Enable
 *
 * \details
 * 0: The instruction is not sent to the serial flash memory.
 * 1: The instruction is not sent to the serial flash memory.
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . INSTEN
 */
#define  VTSS_F_QSPI_QSPI_IFR_INSTEN(x)       VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_QSPI_QSPI_IFR_INSTEN          VTSS_BIT(4)
#define  VTSS_X_QSPI_QSPI_IFR_INSTEN(x)       VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Width of Instruction Code, Address, Option Code and DataOctal mode is
 * not supported.
 *
 * \details
 * 0: SINGLE_BIT_SPI Instruction: Single-bit SPI / Address-Option:
 * Single-bit SPI / Data: Single-bit SPI
 * 1: DUAL_OUTPUT    Instruction: Single-bit SPI / Address-Option:
 * Single-bit SPI / Data: Dual SPI
 * 2: QUAD_OUTPUT    Instruction: Single-bit SPI / Address-Option:
 * Single-bit SPI / Data: Quad SPI
 * 3: DUAL_IO	     Instruction: Single-bit SPI / Address-Option: Dual SPI
 *	 / Data: Dual SPI
 * 4: QUAD_IO	     Instruction: Single-bit SPI / Address-Option: Quad SPI
 *	 / Data: Quad SPI
 * 5: DUAL_CMD	     Instruction: Dual SPI	 / Address-Option: Dual SPI
 *	 / Data: Dual SPI
 * 6: QUAD_CMD	     Instruction: Quad SPI	 / Address-Option: Quad SPI
 *	 / Data: Quad SPI
 *
 * Field: ::VTSS_QSPI_QSPI_IFR . WIDTH
 */
#define  VTSS_F_QSPI_QSPI_IFR_WIDTH(x)        VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_QSPI_QSPI_IFR_WIDTH           VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_QSPI_QSPI_IFR_WIDTH(x)        VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief QSPI Read Instruction Code Register
 *
 * \details
 * QSPI Read Instruction Code Register
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_RICR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_RICR(target)          VTSS_IOREG(target,0xf)

/**
 * \brief
 * Read Option CodeOption code to send to the serial Flash memory in case
 * of read transfer.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_RICR . RDOPT
 */
#define  VTSS_F_QSPI_QSPI_RICR_RDOPT(x)       VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_QSPI_QSPI_RICR_RDOPT          VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_QSPI_QSPI_RICR_RDOPT(x)       VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Read Instruction CodeInstruction code to send to the serial Flash memory
 * in case of read transfer.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_RICR . RDINST
 */
#define  VTSS_F_QSPI_QSPI_RICR_RDINST(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSPI_QSPI_RICR_RDINST         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSPI_QSPI_RICR_RDINST(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief QSPI Scrambling Mode Register
 *
 * \details
 * Register: \a QSPI:QSPI_REGS:QSPI_SMR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_SMR(target)           VTSS_IOREG(target,0x10)

/**
 * \brief
 * Scrambling Key Lock
 *
 * \details
 * 0: No action.
 * 1: QSPI_SKR.USRK cannot be written until the next VDDCORE reset.
 *
 * Field: ::VTSS_QSPI_QSPI_SMR . SCRKL
 */
#define  VTSS_F_QSPI_QSPI_SMR_SCRKL(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_SMR_SCRKL           VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_SMR_SCRKL(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Scrambling/Unscrambling Random Value Disable
 *
 * \details
 * 0: The scrambling/unscrambling algorithm includes the scrambling user
 * key plus a random value that may differ from chip to chip.
 * 1: The scrambling/unscrambling algorithm includes only the scrambling
 * user key.
 *
 * Field: ::VTSS_QSPI_QSPI_SMR . RVDIS
 */
#define  VTSS_F_QSPI_QSPI_SMR_RVDIS(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_SMR_RVDIS           VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_SMR_RVDIS(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Scrambling/Unscrambling Enable
 *
 * \details
 * 0: (DISABLED): The scrambling/unscrambling is disabled.
 * 1: (ENABLED): The scrambling/unscrambling is enabled.
 *
 * Field: ::VTSS_QSPI_QSPI_SMR . SCREN
 */
#define  VTSS_F_QSPI_QSPI_SMR_SCREN(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_SMR_SCREN           VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_SMR_SCREN(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Scrambling Key Register
 *
 * \details
 * QSPI Scrambling Key Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_SKR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_SKR(target)           VTSS_IOREG(target,0x11)

/**
 * \brief
 * Scrambling User Key
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_SKR . USRK
 */
#define  VTSS_F_QSPI_QSPI_SKR_USRK(x)         (x)
#define  VTSS_M_QSPI_QSPI_SKR_USRK            0xffffffff
#define  VTSS_X_QSPI_QSPI_SKR_USRK(x)         (x)


/**
 * \brief QSPI Refresh Register
 *
 * \details
 * QSPI Refresh Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_REFRESH
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_REFRESH(target)       VTSS_IOREG(target,0x14)

/**
 * \brief
 * REFRESH Delay CounterDefines in GCK clock periods the delay between two
 * refreshes of analog blocks.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_REFRESH . REFRESH
 */
#define  VTSS_F_QSPI_QSPI_REFRESH_REFRESH(x)  (x)
#define  VTSS_M_QSPI_QSPI_REFRESH_REFRESH     0xffffffff
#define  VTSS_X_QSPI_QSPI_REFRESH_REFRESH(x)  (x)


/**
 * \brief QSPI Write Access Counter Register
 *
 * \details
 * QSPI Write Access Counter Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_WRACNT
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_WRACNT(target)        VTSS_IOREG(target,0x15)

/**
 * \brief
 * Number of Write AccessesDefines the number of write accesses before the
 * rise of QSPI_ISR.LWRA_ISR.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_WRACNT . NBWRA
 */
#define  VTSS_F_QSPI_QSPI_WRACNT_NBWRA(x)     (x)
#define  VTSS_M_QSPI_QSPI_WRACNT_NBWRA        0xffffffff
#define  VTSS_X_QSPI_QSPI_WRACNT_NBWRA(x)     (x)


/**
 * \brief QSPI DLL Configuration Register
 *
 * \details
 * QSPI DLL Configuration Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 * This register is not affected by a software reset (QSPI_CR.SWRST).
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_DLLCFG
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_DLLCFG(target)        VTSS_IOREG(target,0x16)

/**
 * \brief
 * DLL Range
 *
 * \details
 * 0: The QSPI Core clock is between 25 MHz and 100 MHz.
 * 1: The QSPI Core clock is between 50 MHz and 208 MHz.
 *
 * Field: ::VTSS_QSPI_QSPI_DLLCFG . RANGE
 */
#define  VTSS_F_QSPI_QSPI_DLLCFG_RANGE(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_DLLCFG_RANGE        VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_DLLCFG_RANGE(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Pad Calibration Configuration Register
 *
 * \details
 * QSPI Pad Calibration Configuration Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 * This register is not affected by a software reset (QSPI_CR.SWRST)
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_PCALCFG
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_PCALCFG(target)       VTSS_IOREG(target,0x17)

/**
 * \brief
 * Calibration Code for N-channel
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_PCALCFG . CALN
 */
#define  VTSS_F_QSPI_QSPI_PCALCFG_CALN(x)     VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_QSPI_QSPI_PCALCFG_CALN        VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_QSPI_QSPI_PCALCFG_CALN(x)     VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Calibration Code for P-channel
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_PCALCFG . CALP
 */
#define  VTSS_F_QSPI_QSPI_PCALCFG_CALP(x)     VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_QSPI_QSPI_PCALCFG_CALP        VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_QSPI_QSPI_PCALCFG_CALP(x)     VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Pad Calibration CounterDefines in Peripheral Clock periods the delay
 * between the start of pad calibration analog circuitry and the
 * calibrationrequest.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_PCALCFG . CALCNT
 */
#define  VTSS_F_QSPI_QSPI_PCALCFG_CALCNT(x)   VTSS_ENCODE_BITFIELD(x,8,9)
#define  VTSS_M_QSPI_QSPI_PCALCFG_CALCNT      VTSS_ENCODE_BITMASK(8,9)
#define  VTSS_X_QSPI_QSPI_PCALCFG_CALCNT(x)   VTSS_EXTRACT_BITFIELD(x,8,9)

/**
 * \brief
 * Calibration Clock DivisionThe clock applied to the calibration cell is
 * divided by CLKDIV + 1.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_PCALCFG . CLKDIV
 */
#define  VTSS_F_QSPI_QSPI_PCALCFG_CLKDIV(x)   VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_QSPI_QSPI_PCALCFG_CLKDIV      VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_QSPI_QSPI_PCALCFG_CLKDIV(x)   VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Differential Pad ModeThis bit is not used by the QSPI core. Therefore it
 * does not need to be synchronized using QSPI_CR.UPDCFG.
 *
 * \details
 * 0: Pad differential mode is not enabled.
 * 1: Pad differential mode is enabled
 *
 * Field: ::VTSS_QSPI_QSPI_PCALCFG . DIFFPM
 */
#define  VTSS_F_QSPI_QSPI_PCALCFG_DIFFPM(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_PCALCFG_DIFFPM      VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_PCALCFG_DIFFPM(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Disable Automatic Pad Calibration
 *
 * \details
 * 0: Pad calibration is started automatically depending on the
 * configuration of QSPI_REFRESH.
 * 1: Pad calibration is not started automatically.
 *
 * Field: ::VTSS_QSPI_QSPI_PCALCFG . DAPCAL
 */
#define  VTSS_F_QSPI_QSPI_PCALCFG_DAPCAL(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_PCALCFG_DAPCAL      VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_PCALCFG_DAPCAL(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Analog Always On
 *
 * \details
 * 0: The analog part of the pad calibration circuitry is switched off
 * after each calibration (long delay for each calibration).
 * 1: The analog part of the pad calibration circuitry is not switched off
 * after each calibration (shorter delay after the first
 * calibration).
 *
 * Field: ::VTSS_QSPI_QSPI_PCALCFG . AAON
 */
#define  VTSS_F_QSPI_QSPI_PCALCFG_AAON(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_PCALCFG_AAON        VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_PCALCFG_AAON(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Pad Calibration Bypass Register
 *
 * \details
 * QSPI Pad Calibration Bypass Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 * This register is not affected by a software reset (QSPI_CR.SWRST).
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_PCALBP
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_PCALBP(target)        VTSS_IOREG(target,0x18)

/**
 * \brief
 * Calibration Code Bypass for N-channel
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_PCALBP . CALNBP
 */
#define  VTSS_F_QSPI_QSPI_PCALBP_CALNBP(x)    VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_QSPI_QSPI_PCALBP_CALNBP       VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_QSPI_QSPI_PCALBP_CALNBP(x)    VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Calibration Code Bypass for P-channel
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_PCALBP . CALPBP
 */
#define  VTSS_F_QSPI_QSPI_PCALBP_CALPBP(x)    VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_QSPI_QSPI_PCALBP_CALPBP       VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_QSPI_QSPI_PCALBP_CALPBP(x)    VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Bypass Enable
 *
 * \details
 * 0: Calibration code is not overridden by values of CALNBP and CALPBP.
 * 1: Calibration code is overridden by values of CALNBP and CALPBP.
 *
 * Field: ::VTSS_QSPI_QSPI_PCALBP . BPEN
 */
#define  VTSS_F_QSPI_QSPI_PCALBP_BPEN(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_PCALBP_BPEN         VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_PCALBP_BPEN(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Timeout Register
 *
 * \details
 * QSPI Timeout Register
 * This register can only be written if bit WPEN is cleared in the QSPI
 * Write Protection Mode Register.
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_TOUT
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_TOUT(target)          VTSS_IOREG(target,0x19)

/**
 * \brief
 * Time-out Counter Maximum ValueIndicates the time in GCK clock periods
 * when the connected target does not answer and before the TOUT flag is
 * set.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_TOUT . TCNTM
 */
#define  VTSS_F_QSPI_QSPI_TOUT_TCNTM(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSPI_QSPI_TOUT_TCNTM          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSPI_QSPI_TOUT_TCNTM(x)       VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief QSPI Debug Register
 *
 * \details
 * QSPI Debug Register

 *
 * Register: \a QSPI:QSPI_REGS:QSPI_DEBUG
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_DEBUG(target)         VTSS_IOREG(target,0x34)

/**
 * \brief
 * Disable Error Response on Time-out
 *
 * \details
 * 0: Pending AHB access will receive error response when TOUT flag is set
 * (this automatically releases the system bus).
 * 1: Pending AHB access will not receive error response when TOUT flag is
 * set (IP reset will be required to release the system
 * bus).
 *
 * Field: ::VTSS_QSPI_QSPI_DEBUG . DERT
 */
#define  VTSS_F_QSPI_QSPI_DEBUG_DERT(x)       VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSPI_QSPI_DEBUG_DERT          VTSS_BIT(3)
#define  VTSS_X_QSPI_QSPI_DEBUG_DERT(x)       VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Force Error Response
 *
 * \details
 * 0: SPLIT response is used in case of unexpected read.
 * 1: ERROR response is used in case of unexpected read.
 *
 * Field: ::VTSS_QSPI_QSPI_DEBUG . FERR
 */
#define  VTSS_F_QSPI_QSPI_DEBUG_FERR(x)       VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_DEBUG_FERR          VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_DEBUG_FERR(x)       VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Force AHB Lite behavior
 *
 * \details
 * 0: QSPI IP uses AHB Full protocol and uses SPLIT or ERROR responses when
 * required.
 * 1: QSPI IP uses AHB Lite protocol (only OK response).
 *
 * Field: ::VTSS_QSPI_QSPI_DEBUG . FAHBL
 */
#define  VTSS_F_QSPI_QSPI_DEBUG_FAHBL(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_DEBUG_FAHBL         VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_DEBUG_FAHBL(x)      VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief QSPI Write Protection Mode Register
 *
 * \details
 * QSPI Write Protection Mode Register
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_WPMR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_WPMR(target)          VTSS_IOREG(target,0x39)

/**
 * \brief
 * Write Protection Key.0x515350 PASSWD Writing any other value in this
 * field aborts the write operation of the WPEN bit.Always reads as 0.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_WPMR . WPKEY
 */
#define  VTSS_F_QSPI_QSPI_WPMR_WPKEY(x)       VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_QSPI_QSPI_WPMR_WPKEY          VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_QSPI_QSPI_WPMR_WPKEY(x)       VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * Write Protection Control Register Enable
 *
 * \details
 * 0: Disables the write protection on the Control register if WPKEY
 * corresponds to 0x515350.
 * 1: Enables the write protection on the Control register if WPKEY
 * corresponds to 0x515350.
 *
 * Field: ::VTSS_QSPI_QSPI_WPMR . WPCREN
 */
#define  VTSS_F_QSPI_QSPI_WPMR_WPCREN(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QSPI_QSPI_WPMR_WPCREN         VTSS_BIT(2)
#define  VTSS_X_QSPI_QSPI_WPMR_WPCREN(x)      VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Write Protection Interrupt Enable
 *
 * \details
 * 0: Disables the write protection on Interrupt registers if WPKEY
 * corresponds to 0x515350.
 * 1: Enables the write protection on Interrupt registers if WPKEY
 * corresponds to 0x515350.
 *
 * Field: ::VTSS_QSPI_QSPI_WPMR . WPITEN
 */
#define  VTSS_F_QSPI_QSPI_WPMR_WPITEN(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSPI_QSPI_WPMR_WPITEN         VTSS_BIT(1)
#define  VTSS_X_QSPI_QSPI_WPMR_WPITEN(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * To prevent any single software error from corrupting QSPI behavior,
 * certain registers in theaddress space can be write-protected by setting
 * the WPEN bit in the QSPI Write ProtectionMode Register (QSPI_WPMR).If a
 * write access to a write-protected register is detected, the WPVS flag in
 * the QSPI WriteProtection Status Register (QSPI_WPSR) is set and the
 * field WPVSRC indicates the registerin which the write access has been
 * attempted.The WPVS bit is automatically cleared after reading the
 * QSPI_WPSR.The following registers can be write-protected when WPEN is
 * set in QSPI_WPMR:- QSPI Mode Register- QSPI Serial Clock Register- QSPI
 * Instruction Address Register- QSPI Write Instruction Code Register- QSPI
 * Instruction Frame Register- QSPI Read Instruction Code Register- QSPI
 * Scrambling Mode Register- QSPI Scrambling Key Register- QSPI Refresh
 * Register- QSPI Write Access Counter Register- QSPI Pad Calibration
 * Configuration Register- QSPI Timeout RegisterThe following registers can
 * be write-protected when WPCREN is set in QSPI_WPMR:- QSPI Control
 * RegisterThe following registers can be write-protected when WPITEN is
 * set in QSPI_WPMR:- QSPI Interrupt Enable Register- QSPI Interrupt
 * Disable Register
 *
 * \details
 * 0: Disables the write protection if WPKEY corresponds to 0x515350 (QSP
 * in ASCII)
 * 1: Enables the write protection if WPKEY corresponds to 0x515350 (QSP in
 * ASCII)
 *
 * Field: ::VTSS_QSPI_QSPI_WPMR . WPEN
 */
#define  VTSS_F_QSPI_QSPI_WPMR_WPEN(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_WPMR_WPEN           VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_WPMR_WPEN(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Write Protection Status Register
 *
 * \details
 * Register: \a QSPI:QSPI_REGS:QSPI_WPSR
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_WPSR(target)          VTSS_IOREG(target,0x3a)

/**
 * \brief
 * Write Protection Violation Source.When WPVS = 1, WPVSRC indicates the
 * register address offset at which a write access has been attempted.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_WPSR . WPVSRC
 */
#define  VTSS_F_QSPI_QSPI_WPSR_WPVSRC(x)      VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_QSPI_QSPI_WPSR_WPVSRC         VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_QSPI_QSPI_WPSR_WPVSRC(x)      VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Write Protection Violation Status
 *
 * \details
 * 0: No write protection violation has occurred since the last read of the
 * QSPI_WPSR.
 * 1: A write protection violation has occurred since the last read of the
 * QSPI_WPSR. If this violation is an unauthorized
 * attempt to write a protected register, the associated violation is
 * reported into field WPVSRC.
 *
 * Field: ::VTSS_QSPI_QSPI_WPSR . WPVS
 */
#define  VTSS_F_QSPI_QSPI_WPSR_WPVS(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSPI_QSPI_WPSR_WPVS           VTSS_BIT(0)
#define  VTSS_X_QSPI_QSPI_WPSR_WPVS(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSPI Version Register
 *
 * \details
 * QSPI Version Register
 *
 * Register: \a QSPI:QSPI_REGS:QSPI_VERSION
 *
 * @param target A \a ::vtss_target_QSPI_e target
 */
#define VTSS_QSPI_QSPI_VERSION(target)       VTSS_IOREG(target,0x3f)

/**
 * \brief
 * Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_VERSION . MFN
 */
#define  VTSS_F_QSPI_QSPI_VERSION_MFN(x)      VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_QSPI_QSPI_VERSION_MFN         VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_QSPI_QSPI_VERSION_MFN(x)      VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * Hardware Module Version.Reserved. Value subject to change. No
 * functionality associated. This is the Microchip internal version of the
 * macrocell.
 *
 * \details
 * Field: ::VTSS_QSPI_QSPI_VERSION . VERSION
 */
#define  VTSS_F_QSPI_QSPI_VERSION_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QSPI_QSPI_VERSION_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QSPI_QSPI_VERSION_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_QSPI_H_ */
