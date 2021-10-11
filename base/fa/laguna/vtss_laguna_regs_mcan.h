// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_MCAN_H_
#define _VTSS_LAGUNA_REGS_MCAN_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a MCAN
 *
 * \see vtss_target_MCAN_e
 *
 * The M_CAN module is the new CAN Communication Controller IP-module that can
 * be integrated as stand-alone device or as part of an ASIC. The M_CAN
 * performs communication according to ISO 11898-1:2015. Additional
 * transceiver hardware is required for connection to the physical layer.
 * The message storage is intended to be a single- or dual-ported Message
 * RAM outside of the module. It is connected to the M_CAN via the Generic
 * Master Interface. Depending on the chosen ASIC integration, multiple
 * M_CAN controllers can share the same Message RAM.
 *
 ***********************************************************************/

/**
 * Register Group: \a MCAN:MCAN_REGS
 *
 * Not documented
 */


/**
 * \brief Core Release Register
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:CREL
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_CREL(target)               VTSS_IOREG(target,0x0)

/**
 * \brief
 * Core Release.One digit, BCD-coded.
 *
 * \details
 * Field: ::VTSS_MCAN_CREL . REL
 */
#define  VTSS_F_MCAN_CREL_REL(x)              VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_MCAN_CREL_REL                 VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_MCAN_CREL_REL(x)              VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Step of Core Release.One digit, BCD-coded.
 *
 * \details
 * Field: ::VTSS_MCAN_CREL . STEP
 */
#define  VTSS_F_MCAN_CREL_STEP(x)             VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_MCAN_CREL_STEP                VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_MCAN_CREL_STEP(x)             VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Sub-step of Core Release.One digit, BCD-coded.
 *
 * \details
 * Field: ::VTSS_MCAN_CREL . SUBSTEP
 */
#define  VTSS_F_MCAN_CREL_SUBSTEP(x)          VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_MCAN_CREL_SUBSTEP             VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_MCAN_CREL_SUBSTEP(x)          VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Time Stamp Year.One digit, BCD-coded. This field is set by generic
 * parameter on M_CAN synthesis.
 *
 * \details
 * Field: ::VTSS_MCAN_CREL . YEAR
 */
#define  VTSS_F_MCAN_CREL_YEAR(x)             VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_MCAN_CREL_YEAR                VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_MCAN_CREL_YEAR(x)             VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Time Stamp Month.Two digits, BCD-coded. This field is set by generic
 * parameter on M_CAN synthesis.
 *
 * \details
 * Field: ::VTSS_MCAN_CREL . MON
 */
#define  VTSS_F_MCAN_CREL_MON(x)              VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCAN_CREL_MON                 VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCAN_CREL_MON(x)              VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Time Stamp Day.Two digits, BCD-coded. This field is set by generic
 * parameter on M_CAN synthesis.
 *
 * \details
 * Field: ::VTSS_MCAN_CREL . DAY
 */
#define  VTSS_F_MCAN_CREL_DAY(x)              VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCAN_CREL_DAY                 VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCAN_CREL_DAY(x)              VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Endian Register
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:ENDN
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_ENDN(target)               VTSS_IOREG(target,0x1)

/**
 * \brief
 * Endianness Test ValueThe endianness test value is 0x87654321.
 *
 * \details
 * Field: ::VTSS_MCAN_ENDN . ETV
 */
#define  VTSS_F_MCAN_ENDN_ETV(x)              (x)
#define  VTSS_M_MCAN_ENDN_ETV                 0xffffffff
#define  VTSS_X_MCAN_ENDN_ETV(x)              (x)


/**
 * \brief Customer Register
 *
 * \details
 * Address 0x08 is reserved for an optional 32 bit customer-specific
 * register. The Customer Register
 * is intended to hold customer-specific configuration, control, and status
 * bits. Adescr iption of the
 * functionality is not part of this document.
 *
 * Register: \a MCAN:MCAN_REGS:CUST
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_CUST(target)               VTSS_IOREG(target,0x2)

/**
 * \brief
 * Address 0x08 is reserved for an optional 32 bit customer-specific
 * register. The Customer Registeris intended to hold customer-specific
 * configuration, control, and status bits. Adescr iption of
 * thefunctionality is not part of this document.
 *
 * \details
 * Field: ::VTSS_MCAN_CUST . CUST
 */
#define  VTSS_F_MCAN_CUST_CUST(x)             (x)
#define  VTSS_M_MCAN_CUST_CUST                0xffffffff
#define  VTSS_X_MCAN_CUST_CUST(x)             (x)


/**
 * \brief Data Bit Timing & Prescaler Register
 *
 * \details
 * This register is only writable if bits CCCR.CCE and CCCR.INIT are set.
 * The CAN bit time may be
 * programed in the range of 4 to 49 time quanta. The CAN time quantum may
 * be programmed in the
 * range of 1 to 32 m_can_cclk periods. tq = (DBRP + 1) mtq
 * DTSEG1 is the sum of Prop_Seg and Phase_Seg1. DTSEG2 is Phase_Seg2.
 * Therefore the length of the bit time is (programmed values) [DTSEG1 +
 * DTSEG2 + 3] tq
 * or (functional values) [Sync_Seg + Prop_Seg + Phase_Seg1 + Phase_Seg2]
 * tq.
 * The Information Processing Time (IPT) is zero, meaning the data for the
 * next bit is available at the
 * first clock edge after the sample point.
 * Note: With a CAN clock (m_can_cclk) of 8 MHz, the reset value of
 * 0x00000A33 configures the
 * M_CAN for a data phase bit rate of 500 kBit/s.
 * Note: The bit rate configured for the CAN FD data phase via DBTP must be
 * higher or equal to
 * the bit rate configured for the arbitration phase via NBTP.

 *
 * Register: \a MCAN:MCAN_REGS:DBTP
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_DBTP(target)               VTSS_IOREG(target,0x3)

/**
 * \brief
 * Transmitter Delay CompensationAccess: Read and Protected Write
 *
 * \details
 * 0= Transmitter Delay Compensation disabled
 * 1= Transmitter Delay Compensation enabled
 *
 * Field: ::VTSS_MCAN_DBTP . TDC
 */
#define  VTSS_F_MCAN_DBTP_TDC(x)              VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_MCAN_DBTP_TDC                 VTSS_BIT(23)
#define  VTSS_X_MCAN_DBTP_TDC(x)              VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Data Bit Rate Prescaler0x00-0x1F : The value by which the oscillator
 * frequency is divided for generating the bit timequanta. The bit time is
 * built up from a multiple of this quanta. Valid values for the BitRate
 * Prescaler are 0 to 31. When TDC = 1, the range is limited to 0,1. The
 * actualinterpretation by the hardware of this value is such that one more
 * than the value programmedhere is used.Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_DBTP . DBRP
 */
#define  VTSS_F_MCAN_DBTP_DBRP(x)             VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_MCAN_DBTP_DBRP                VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_MCAN_DBTP_DBRP(x)             VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 * 0x00-0x1F : Valid values are 0 to 31. The actual interpretation by the
 * hardware of this value issuch that one more than the programmed value is
 * used.\Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_DBTP . DTSEG1
 */
#define  VTSS_F_MCAN_DBTP_DTSEG1(x)           VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_MCAN_DBTP_DTSEG1              VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_MCAN_DBTP_DTSEG1(x)           VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Data time segment after sample point0x0-0xF : Valid values are 0 to 15.
 * The actual interpretation by the hardware of this value issuch that one
 * more than the programmed value is used.Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_DBTP . DTSEG2
 */
#define  VTSS_F_MCAN_DBTP_DTSEG2(x)           VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_MCAN_DBTP_DTSEG2              VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_MCAN_DBTP_DTSEG2(x)           VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Data (Re)Synchronization Jump Width0x0-0xF : Valid values are 0 to 15.
 * The actual interpretation by the hardware of this value issuch that one
 * more than the value programmed here is used.Access: Read and Protected
 * Write
 *
 * \details
 * Field: ::VTSS_MCAN_DBTP . DSJW
 */
#define  VTSS_F_MCAN_DBTP_DSJW(x)             VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MCAN_DBTP_DSJW                VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MCAN_DBTP_DSJW(x)             VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Test Register
 *
 * \details
 * Write access to the Test Register has to be enabled by setting bit
 * CCCR.TEST to 1. All Test Register functions are set to their reset
 * values when bit CCCR.TEST is reset.
 * Loop Back Mode and software control of pin m_can_tx are hardware test
 * modes. Programming of TX is not equal to 00 may disturb the message
 * transfer on the CAN bus.
 *
 * Register: \a MCAN:MCAN_REGS:TEST
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TEST(target)               VTSS_IOREG(target,0x4)

/**
 * \brief
 * Receive PinMonitors the actual value of pin m_can_rx
 *
 * \details
 * 0= The CAN bus is dominant (m_can_rx = 0)
 * 1= The CAN bus is recessive (m_can_rx = 1)
 *
 * Field: ::VTSS_MCAN_TEST . RX
 */
#define  VTSS_F_MCAN_TEST_RX(x)               VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_TEST_RX                  VTSS_BIT(7)
#define  VTSS_X_MCAN_TEST_RX(x)               VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Control of Transmit PinAccess: Read and Protected Write
 *
 * \details
 * 00 Reset value, m_can_tx controlled by the CAN Core, updated at the end
 * of the CAN bit time
 * 01 Sample Point can be monitored at pin m_can_tx
 * 10 Dominant (0) level at pin m_can_tx
 * 11 Recessive (1) at pin m_can_tx
 *
 * Field: ::VTSS_MCAN_TEST . TX
 */
#define  VTSS_F_MCAN_TEST_TX(x)               VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_MCAN_TEST_TX                  VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_MCAN_TEST_TX(x)               VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * Loop Back ModeThe M_CAN can be set in External Loop Back Mode by
 * programming TEST.LBCK to one. In LoopBack Mode, the M_CAN treats its own
 * transmitted messages as received messages and storesthem (if they pass
 * acceptance filtering) into an Rx Buffer or an Rx FIFO. Figure 5 shows
 * theconnection of signals m_can_tx and m_can_rx to the M_CAN in External
 * Loop Back Mode.This mode is provided for hardware self-test. To be
 * independent from external stimulation, theM_CAN ignores acknowledge
 * errors (recessive bit sampled in the acknowledge slot of a
 * data/remoteframe) in Loop Back Mode. In this mode the M_CAN performs an
 * internal feedback from its Txoutput to its Rx input. The actual value of
 * the m_can_rx input pin is disregarded by the M_CAN. Thetransmitted
 * messages can be monitored at the m_can_tx pin.Access: Read and Protected
 * Write
 *
 * \details
 * 0= Reset value, Loop Back Mode is disabled
 * 1= Loop Back Mode is enabled
 *
 * Field: ::VTSS_MCAN_TEST . LBCK
 */
#define  VTSS_F_MCAN_TEST_LBCK(x)             VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_TEST_LBCK                VTSS_BIT(4)
#define  VTSS_X_MCAN_TEST_LBCK(x)             VTSS_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief RAM Watchdog
 *
 * \details
 * The RAM Watchdog monitors the READY output of the Message RAM
 * (m_can_aeim_ready). A
 * Message RAM access via the M_CANs Generic Master Interface
 * (m_can_aeim_sel active) starts
 * the Message RAM Watchdog Counter with the value configured by RWD.WDC.
 * The counter is
 * reloaded with RWD.WDC when the Message RAM signals successful completion
 * by activating its
 * READY output. In case there is no response from the Message RAM until
 * the counter has counted
 * down to zero, the counter stops and interrupt flag IR.WDI is set. The
 * RAM Watchdog Counter is
 * clocked by the Host clock (m_can_hclk).
 *
 * Register: \a MCAN:MCAN_REGS:RWD
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RWD(target)                VTSS_IOREG(target,0x5)

/**
 * \brief
 * Watchdog ValueActual Message RAM Watchdog Counter Value.
 *
 * \details
 * Field: ::VTSS_MCAN_RWD . WDV
 */
#define  VTSS_F_MCAN_RWD_WDV(x)               VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCAN_RWD_WDV                  VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCAN_RWD_WDV(x)               VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Watchdog Configuration.Start value of the Message RAM Watchdog Counter.
 * With the reset value of 00 the counter isdisabled.Access: Read and
 * Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_RWD . WDC
 */
#define  VTSS_F_MCAN_RWD_WDC(x)               VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCAN_RWD_WDC                  VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCAN_RWD_WDC(x)               VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CC Control Register
 *
 * \details
 * CC Control Register
 * Software initialization is started by setting bit CCCR.INIT, either by
 * software or by a hardware reset,
 * when an uncorrected bit error was detected in the Message RAM, or by
 * going Bus_Off. While
 * CCCR.INIT is set, message transfer from and to the CAN bus is stopped,
 * the status of the CAN bus
 * output m_can_tx is recessive (HIGH). The counters of the Error
 * Management Logic EML are
 * unchanged. Setting CCCR.INIT does not change any configuration register.
 * Resetting CCCR.INIT
 * finishes the software initialization. Afterwards the Bit Stream
 * Processor BSP synchronizes itself to
 * the data transfer on the CAN bus by waiting for the occurrence of a
 * sequence of 11 consecutive
 * recessive bits (=Bus_Idle) before it can take part in bus activities and
 * start the message transfer.
 * Access to the M_CAN configuration registers is only enabled when both
 * bits CCCR.INIT and
 * CCCR.CCE are set (protected write).
 * CCCR.CCE can only be set/reset while CCCR.INIT = 1. CCCR.CCE is
 * automatically reset when
 * CCCR.INIT is reset.
 * For details about setting and resetting of single bits see Section
 * 3.1.1. in mcan user manual.
 *
 * Register: \a MCAN:MCAN_REGS:CCCR
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_CCCR(target)               VTSS_IOREG(target,0x6)

/**
 * \brief
 * Non ISO OperationIf this bit is set, the M_CAN uses the CAN FD frame
 * format as specified by the Bosch CAN FDSpecification V1.0.Access: Read
 * and Protected Write
 *
 * \details
 * 0= CAN FD frame format according to ISO 11898-1:2015
 * 1= CAN FD frame format according to Bosch CAN FD Specification V1.0
 *
 * Field: ::VTSS_MCAN_CCCR . NISO
 */
#define  VTSS_F_MCAN_CCCR_NISO(x)             VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_CCCR_NISO                VTSS_BIT(15)
#define  VTSS_X_MCAN_CCCR_NISO(x)             VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Transmit PauseIf this bit is set, the M_CAN pauses for two CAN bit times
 * before starting the next transmission afteritself has successfully
 * transmitted a frame (see Section 3.5 in mcan user manual).Access: Read
 * and Protected Write
 *
 * \details
 * 0= Transmit pause disabled
 * 1= Transmit pause enabled
 *
 * Field: ::VTSS_MCAN_CCCR . TXP
 */
#define  VTSS_F_MCAN_CCCR_TXP(x)              VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_MCAN_CCCR_TXP                 VTSS_BIT(14)
#define  VTSS_X_MCAN_CCCR_TXP(x)              VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Edge Filtering during Bus IntegrationAccess: Read and Protected Write
 *
 * \details
 * 0= Edge filtering disabled
 * 1= Two consecutive dominant tq required to detect an edge for hard
 * synchronization
 *
 * Field: ::VTSS_MCAN_CCCR . EFBI
 */
#define  VTSS_F_MCAN_CCCR_EFBI(x)             VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_MCAN_CCCR_EFBI                VTSS_BIT(13)
#define  VTSS_X_MCAN_CCCR_EFBI(x)             VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Protocol Exception Handling Disable.Access: Read and Protected
 * WriteNote: When protocol exception handling is disabled, the M_CAN will
 * transmit an error framewhen it detects a protocol exception condition.
 *
 * \details
 * 0= Protocol exception handling enabled
 * 1= Protocol exception handling disabled
 *
 * Field: ::VTSS_MCAN_CCCR . PXHD
 */
#define  VTSS_F_MCAN_CCCR_PXHD(x)             VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_MCAN_CCCR_PXHD                VTSS_BIT(12)
#define  VTSS_X_MCAN_CCCR_PXHD(x)             VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Bit Rate Switch EnableNote: When CAN FD operation is disabled FDOE = 0,
 * BRSE is not evaluated.Access: Read and Protected Write
 *
 * \details
 * 0= Bit rate switching for transmissions disabled
 * 1= Bit rate switching for transmissions enabled
 *
 * Field: ::VTSS_MCAN_CCCR . BRSE
 */
#define  VTSS_F_MCAN_CCCR_BRSE(x)             VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_MCAN_CCCR_BRSE                VTSS_BIT(9)
#define  VTSS_X_MCAN_CCCR_BRSE(x)             VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * FD Operation EnableAccess: Read and Protected Write
 *
 * \details
 * 0= FD operation disabled
 * 1= FD operation enabled
 *
 * Field: ::VTSS_MCAN_CCCR . FDOE
 */
#define  VTSS_F_MCAN_CCCR_FDOE(x)             VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_MCAN_CCCR_FDOE                VTSS_BIT(8)
#define  VTSS_X_MCAN_CCCR_FDOE(x)             VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Test Mode EnableAccess: Read and Protected Set.
 *
 * \details
 * 0= Normal operation, register TEST holds reset values
 * 1= Test Mode, write access to register TEST enabled
 *
 * Field: ::VTSS_MCAN_CCCR . TEST
 */
#define  VTSS_F_MCAN_CCCR_TEST(x)             VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_CCCR_TEST                VTSS_BIT(7)
#define  VTSS_X_MCAN_CCCR_TEST(x)             VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Disable Automatic RetransmissionAccess: Read and Protected Write
 *
 * \details
 * 0= Automatic retransmission of messages not transmitted successfully
 * enabled
 * 1= Automatic retransmission disabled
 *
 * Field: ::VTSS_MCAN_CCCR . DAR
 */
#define  VTSS_F_MCAN_CCCR_DAR(x)              VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_CCCR_DAR                 VTSS_BIT(6)
#define  VTSS_X_MCAN_CCCR_DAR(x)              VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Bus Monitoring ModeBit MON can only be set by the Host when both CCE and
 * INIT are set to 1. The bit can be reset bythe Host at any time.Access:
 * Read and Protected set.
 *
 * \details
 * 0= Bus Monitoring Mode is disabled
 * 1= Bus Monitoring Mode is enabled
 *
 * Field: ::VTSS_MCAN_CCCR . MON_CCCR
 */
#define  VTSS_F_MCAN_CCCR_MON_CCCR(x)         VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_CCCR_MON_CCCR            VTSS_BIT(5)
#define  VTSS_X_MCAN_CCCR_MON_CCCR(x)         VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Clock Stop RequestAccess: Read and Write
 *
 * \details
 * 0= No clock stop is requested
 * 1= Clock stop requested. When clock stop is requested, first INIT and
 * then CSA will be set after
 * all pending transfer requests have been completed and the CAN bus
 * reached idle.
 *
 * Field: ::VTSS_MCAN_CCCR . CSR
 */
#define  VTSS_F_MCAN_CCCR_CSR(x)              VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_CCCR_CSR                 VTSS_BIT(4)
#define  VTSS_X_MCAN_CCCR_CSR(x)              VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Clock Stop AcknowledgeAccess: Read
 *
 * \details
 * 0= No clock stop acknowledged
 * 1= M_CAN may be set in power down by stopping m_can_hclk and m_can_cclk
 *
 * Field: ::VTSS_MCAN_CCCR . CSA
 */
#define  VTSS_F_MCAN_CCCR_CSA(x)              VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_CCCR_CSA                 VTSS_BIT(3)
#define  VTSS_X_MCAN_CCCR_CSA(x)              VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Restricted Operation ModeBit ASM can only be set by the Host when both
 * CCE and INIT are set to 1. The bit can be reset bythe Host at any time.
 * For a description of the Restricted Operation Mode see Section
 * 3.1.5(mcan user manual).
 *
 * \details
 * 0= Normal CAN operation
 * 1= Restricted Operation Mode active
 *
 * Field: ::VTSS_MCAN_CCCR . ASM
 */
#define  VTSS_F_MCAN_CCCR_ASM(x)              VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_CCCR_ASM                 VTSS_BIT(2)
#define  VTSS_X_MCAN_CCCR_ASM(x)              VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Configuration Change EnableAccess: Read and Protected Write
 *
 * \details
 * 0= The CPU has no write access to the protected configuration registers
 * 1= The CPU has write access to the protected configuration registers
 * (while CCCR.INIT = 1)
 *
 * Field: ::VTSS_MCAN_CCCR . CCE
 */
#define  VTSS_F_MCAN_CCCR_CCE(x)              VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_CCCR_CCE                 VTSS_BIT(1)
#define  VTSS_X_MCAN_CCCR_CCE(x)              VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * InitializationAccess: Read and WriteNote: Due to the synchronization
 * mechanism between the two clock domains, there may be adelay until the
 * value written to INIT can be read back. Therefore the programmer has
 * toassure that the previous value written to INIT has been accepted by
 * reading INIT beforesetting INIT to a new value.
 *
 * \details
 * 0= Normal Operation
 * 1= Initialization is started
 *
 * Field: ::VTSS_MCAN_CCCR . INIT
 */
#define  VTSS_F_MCAN_CCCR_INIT(x)             VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_CCCR_INIT                VTSS_BIT(0)
#define  VTSS_X_MCAN_CCCR_INIT(x)             VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Nominal Bit Timing & Prescaler Register
 *
 * \details
 * Nominal Bit Timing & Prescaler Register
 * This register is only writable if bits CCCR.CCE and CCCR.INIT are set.
 * The CAN bit time may be
 * programed in the range of 4 to 385 time quanta. The CAN time quantum may
 * be programmed in the
 * range of 1 to 512 m_can_cclk periods. tq = (NBRP + 1) mtq.
 * NTSEG1 is the sum of Prop_Seg and Phase_Seg1. NTSEG2 is Phase_Seg2.
 * Therefore the length of the bit time is (programmed values) [NTSEG1 +
 * NTSEG2 + 3] tq
 * or (functional values) [Sync_Seg + Prop_Seg + Phase_Seg1 + Phase_Seg2]
 * tq.
 * The Information Processing Time (IPT) is zero, meaning the data for the
 * next bit is available at the
 * first clock edge after the sample point.
 *
 * Register: \a MCAN:MCAN_REGS:NBTP
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_NBTP(target)               VTSS_IOREG(target,0x7)

/**
 * \brief
 * Nominal (Re)Synchronization Jump Width0x00-0x7F :  Valid values are 0 to
 * 127. The actual interpretation by the hardware of this value is such
 * that one more than the value programmed here is used.Access: Read and
 * Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_NBTP . NSJW
 */
#define  VTSS_F_MCAN_NBTP_NSJW(x)             VTSS_ENCODE_BITFIELD(x,25,7)
#define  VTSS_M_MCAN_NBTP_NSJW                VTSS_ENCODE_BITMASK(25,7)
#define  VTSS_X_MCAN_NBTP_NSJW(x)             VTSS_EXTRACT_BITFIELD(x,25,7)

/**
 * \brief
 * Nominal Bit Rate Prescaler0x000-0x1FF : The value by which the
 * oscillator frequency is divided for generating the bit timequanta. The
 * bit time is built up from a multiple of this quanta. Valid values for
 * the BitRate Prescaler are 0 to 511. The actual interpretation by the
 * hardware of this value issuch that one more than the value programmed
 * here is used.Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_NBTP . NBRP
 */
#define  VTSS_F_MCAN_NBTP_NBRP(x)             VTSS_ENCODE_BITFIELD(x,16,9)
#define  VTSS_M_MCAN_NBTP_NBRP                VTSS_ENCODE_BITMASK(16,9)
#define  VTSS_X_MCAN_NBTP_NBRP(x)             VTSS_EXTRACT_BITFIELD(x,16,9)

/**
 * \brief
 * Nominal Time segment before sample point0x01-0xFF: Valid values are 1 to
 * 255. The actual interpretation by the hardware of this value issuch that
 * one more than the programmed value is used.Access: Read and Protected
 * Write
 *
 * \details
 * Field: ::VTSS_MCAN_NBTP . NTSEG1
 */
#define  VTSS_F_MCAN_NBTP_NTSEG1(x)           VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCAN_NBTP_NTSEG1              VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCAN_NBTP_NTSEG1(x)           VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Nominal Time segment after sample point0x01-0x7F: Valid values are 1 to
 * 127. The actual interpretation by the hardware of this value issuch that
 * one more than the programmed value is used.Note: With a CAN clock
 * (m_can_cclk) of 8 MHz, the reset value of 0x06000A03 configures theM_CAN
 * for a bit rate of 500 kBit/s.Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_NBTP . NTSEG2
 */
#define  VTSS_F_MCAN_NBTP_NTSEG2(x)           VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_MCAN_NBTP_NTSEG2              VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_MCAN_NBTP_NTSEG2(x)           VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Time stamp Counter Configuration
 *
 * \details
 * For a description of the Time stamp Counter see Section 3.2, Time stamp
 * Generation
 *
 * Register: \a MCAN:MCAN_REGS:TSCC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TSCC(target)               VTSS_IOREG(target,0x8)

/**
 * \brief
 * Time stamp Counter Prescaler0x0-0xF: Configures the time stamp and
 * timeout counters time unit in multiples of CAN bit times[1 to 16]. The
 * actual interpretation by the hardware of this value is such that one
 * morethan the value programmed here is used.Note: With CAN FD an external
 * counter is required for time stamp generation (TSS = 10)Access: Read and
 * Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_TSCC . TCP
 */
#define  VTSS_F_MCAN_TSCC_TCP(x)              VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_MCAN_TSCC_TCP                 VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_MCAN_TSCC_TCP(x)              VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Time stamp SelectAccess: Read and Protected Write
 *
 * \details
 * 00= Time stamp counter value always 0x0000
 * 01= Time stamp counter value incremented according to TCP
 * 10= External time stamp counter value used
 * 11= Same as 00
 *
 * Field: ::VTSS_MCAN_TSCC . TSS
 */
#define  VTSS_F_MCAN_TSCC_TSS(x)              VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MCAN_TSCC_TSS                 VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MCAN_TSCC_TSS(x)              VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Time stamp Counter Value
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TSCV
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TSCV(target)               VTSS_IOREG(target,0x9)

/**
 * \brief
 * Time stamp CounterThe internal/external Time stamp Counter value is
 * captured on start of frame (both Rx and Tx).When TSCC.TSS = 01, the Time
 * stamp Counter is incremented in multiples of CAN bit times[1 ... 16]
 * depending on the configuration of TSCC.TCP. Awr ap around sets interrupt
 * flag IR.TSW.Write access resets the counter to zero. When TSCC.TSS =
 * "10", TSC reflects the externalTime stamp Counter value. A write access
 * has no impact.Note: A wrap around is a change of the Time stamp Counter
 * value from non-zero to zero notcaused by write access to TSCV.Access:
 * Read and Clear/preset on write
 *
 * \details
 * Field: ::VTSS_MCAN_TSCV . TSC
 */
#define  VTSS_F_MCAN_TSCV_TSC(x)              VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MCAN_TSCV_TSC                 VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MCAN_TSCV_TSC(x)              VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Timeout Counter Configuration
 *
 * \details
 * For a description of the Timeout Counter see Section 3.3, Timeout
 * Counter.
 *
 * Register: \a MCAN:MCAN_REGS:TOCC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TOCC(target)               VTSS_IOREG(target,0xa)

/**
 * \brief
 * Timeout PeriodStart value of the Timeout Counter (down-counter).
 * Configures the Timeout Period.Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_TOCC . TOP
 */
#define  VTSS_F_MCAN_TOCC_TOP(x)              VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_MCAN_TOCC_TOP                 VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_MCAN_TOCC_TOP(x)              VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Timeout SelectWhen operating in Continuous mode, a write to TOCV presets
 * the counter to the value configuredby TOCC.TOP and continues
 * down-counting. When the Timeout Counter is controlled by one of
 * theFIFOs, an empty FIFO presets the counter to the value configured by
 * TOCC.TOP. Down-countingis started when the first FIFO element is
 * stored.Access: Read and Protected Write
 *
 * \details
 * 00= Continuous operation
 * 01= Timeout controlled by Tx Event FIFO
 * 10= Timeout controlled by Rx FIFO 0
 * 11= Timeout controlled by Rx FIFO 1
 *
 * Field: ::VTSS_MCAN_TOCC . TOS
 */
#define  VTSS_F_MCAN_TOCC_TOS(x)              VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_MCAN_TOCC_TOS                 VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_MCAN_TOCC_TOS(x)              VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Enable Timeout CounterNote: For use of timeout function with CAN FD see
 * Section 3.3. in CAN user manualAccess: Read and Protected Write
 *
 * \details
 * 0= Timeout Counter disabled
 * 1= Timeout Counter enabled
 *
 * Field: ::VTSS_MCAN_TOCC . ETOC
 */
#define  VTSS_F_MCAN_TOCC_ETOC(x)             VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TOCC_ETOC                VTSS_BIT(0)
#define  VTSS_X_MCAN_TOCC_ETOC(x)             VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Timeout Counter Value
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TOCV
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TOCV(target)               VTSS_IOREG(target,0xb)

/**
 * \brief
 * Timeout CounterThe Timeout Counter is decremented in multiples of CAN
 * bit times [1...16] depending on theconfiguration of TSCC.TCP. When
 * decremented to zero, interrupt flag IR.TOO is set and theTimeout Counter
 * is stopped. Start and reset/restart conditions are configured via
 * TOCC.TOS.Access: Read and Clear/preset on write
 *
 * \details
 * Field: ::VTSS_MCAN_TOCV . TOC
 */
#define  VTSS_F_MCAN_TOCV_TOC(x)              VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MCAN_TOCV_TOC                 VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MCAN_TOCV_TOC(x)              VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Error Counter Register
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:ECR
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_ECR(target)                VTSS_IOREG(target,0x10)

/**
 * \brief
 * CAN Error LoggingThe counter is incremented each time when a CAN
 * protocol error causes the Transmit Error Counteror the Receive Error
 * Counter to be incremented. It is reset by read access to CEL. The
 * counter stopsat 0xFF; the next increment of TEC or REC sets interrupt
 * flag IR.ELO.Access: Reset on read;
 *
 * \details
 * Field: ::VTSS_MCAN_ECR . CEL
 */
#define  VTSS_F_MCAN_ECR_CEL(x)               VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_MCAN_ECR_CEL                  VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_MCAN_ECR_CEL(x)               VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Receive Error PassiveAccess: Read
 *
 * \details
 * 0= The Receive Error Counter is below the error passive level of 128
 * 1= The Receive Error Counter has reached the error passive level of 128
 *
 * Field: ::VTSS_MCAN_ECR . RP
 */
#define  VTSS_F_MCAN_ECR_RP(x)                VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_ECR_RP                   VTSS_BIT(15)
#define  VTSS_X_MCAN_ECR_RP(x)                VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Receive Error CounterActual state of the Receive Error Counter, values
 * between 0 and 127Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_ECR . REC
 */
#define  VTSS_F_MCAN_ECR_REC(x)               VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_MCAN_ECR_REC                  VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_MCAN_ECR_REC(x)               VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * Transmit Error CounterActual state of the Transmit Error Counter, values
 * between 0 and 255Note: When CCCR.ASM is set, the CAN protocol controller
 * does not increment TEC and RECwhen a CAN protocol error is detected, but
 * CEL is still incremented.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_ECR . TEC
 */
#define  VTSS_F_MCAN_ECR_TEC(x)               VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCAN_ECR_TEC                  VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCAN_ECR_TEC(x)               VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Protocol Status Register
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:PSR
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_PSR(target)                VTSS_IOREG(target,0x11)

/**
 * \brief
 * Transmitter Delay Compensation Value0x00-0x7F: Position of the secondary
 * sample point, defined by the sum of the measured delayfrom m_can_tx to
 * m_can_rx and TDCR.TDCO. The SSP position is, in the dataphase, the
 * number of mtq between the start of the transmitted bit and the
 * secondarysample point. Valid values are 0 to 127 mtq.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_PSR . TDCV
 */
#define  VTSS_F_MCAN_PSR_TDCV(x)              VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_MCAN_PSR_TDCV                 VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_MCAN_PSR_TDCV(x)              VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Protocol Exception EventAccess: Reset on read
 *
 * \details
 * 0= No protocol exception event occurred since last read access
 * 1= Protocol exception event occurred
 *
 * Field: ::VTSS_MCAN_PSR . PXE
 */
#define  VTSS_F_MCAN_PSR_PXE(x)               VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_MCAN_PSR_PXE                  VTSS_BIT(14)
#define  VTSS_X_MCAN_PSR_PXE(x)               VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Received a CAN FD MessageThis bit is set independent of acceptance
 * filtering.Access: Reset on read
 *
 * \details
 * 0= Since this bit was reset by the CPU, no CAN FD message has been
 * received
 * 1= Message in CAN FD format with FDF flag set has been received
 *
 * Field: ::VTSS_MCAN_PSR . RFDF
 */
#define  VTSS_F_MCAN_PSR_RFDF(x)              VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_MCAN_PSR_RFDF                 VTSS_BIT(13)
#define  VTSS_X_MCAN_PSR_RFDF(x)              VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * BRS flag of last received CAN FD MessageThis bit is set together with
 * RFDF, independent of acceptance filtering.Access: Reset on read
 *
 * \details
 * 0= Last received CAN FD message did not have its BRS flag set
 * 1= Last received CAN FD message had its BRS flag set
 *
 * Field: ::VTSS_MCAN_PSR . RBRS
 */
#define  VTSS_F_MCAN_PSR_RBRS(x)              VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_MCAN_PSR_RBRS                 VTSS_BIT(12)
#define  VTSS_X_MCAN_PSR_RBRS(x)              VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * ESI flag of last received CAN FD MessageThis bit is set together with
 * RFDF, independent of acceptance filtering.Access: Reset on read
 *
 * \details
 * 0= Last received CAN FD message did not have its ESI flag set
 * 1= Last received CAN FD message had its ESI flag set
 *
 * Field: ::VTSS_MCAN_PSR . RESI
 */
#define  VTSS_F_MCAN_PSR_RESI(x)              VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_MCAN_PSR_RESI                 VTSS_BIT(11)
#define  VTSS_X_MCAN_PSR_RESI(x)              VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Data Phase Last Error CodeType of last error that occurred in the data
 * phase of a CAN FD format frame with its BRS flag set.Coding is the same
 * as for LEC. This field will be cleared to zero when a CAN FD format
 * frame withits BRS flag set has been transferred (reception or
 * transmission) without error.Access: Set on read
 *
 * \details
 * Field: ::VTSS_MCAN_PSR . DLEC
 */
#define  VTSS_F_MCAN_PSR_DLEC(x)              VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_MCAN_PSR_DLEC                 VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_MCAN_PSR_DLEC(x)              VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Bus_Off StatusAccess: Read
 *
 * \details
 * 0= The M_CAN is not Bus_Off
 * 1= The M_CAN is in Bus_Off state
 *
 * Field: ::VTSS_MCAN_PSR . BO
 */
#define  VTSS_F_MCAN_PSR_BO(x)                VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_PSR_BO                   VTSS_BIT(7)
#define  VTSS_X_MCAN_PSR_BO(x)                VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Warning StatusAccess: Read
 *
 * \details
 * 0= Both error counters are below the Error_Warning limit of 96
 * 1= At least one of error counter has reached the Error_Warning limit of
 * 96
 *
 * Field: ::VTSS_MCAN_PSR . EW
 */
#define  VTSS_F_MCAN_PSR_EW(x)                VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_PSR_EW                   VTSS_BIT(6)
#define  VTSS_X_MCAN_PSR_EW(x)                VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Error PassiveAccess: Read
 *
 * \details
 * 0= The M_CAN is in the Error_Active state. It normally takes part in bus
 * communication and
 * sends an active error flag when an error has been detected
 * 1= The M_CAN is in the Error_Passive state
 *
 * Field: ::VTSS_MCAN_PSR . EP
 */
#define  VTSS_F_MCAN_PSR_EP(x)                VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_PSR_EP                   VTSS_BIT(5)
#define  VTSS_X_MCAN_PSR_EP(x)                VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * ActivityMonitors the module's CAN communication state.Note: ACT is set
 * to "00' by a Protocol Exception Event.Access: Read
 *
 * \details
 * 00= Synchronizing  node is synchronizing on CAN communication
 * 01= Idle node is neither receiver nor transmitter
 * 10= Receiver node is operating as receiver
 * 11= Transmitter node is operating as transmitter
 *
 * Field: ::VTSS_MCAN_PSR . ACT
 */
#define  VTSS_F_MCAN_PSR_ACT(x)               VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_MCAN_PSR_ACT                  VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_MCAN_PSR_ACT(x)               VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Last Error CodeThe LEC indicates the type of the last error to occur on
 * the CAN bus. This field will be cleared to '0'when a message has been
 * transferred (reception or transmission) without error.Note: When a frame
 * in CAN FD format has reached the data phase with BRS flag set, the
 * nextCAN event (error or valid frame) will be shown in DLEC instead of
 * LEC. An error in a fixedstuff bit of a CAN FD CRC sequence will be shown
 * as a Form Error, not Stuff Error.Note: The Bus_Off recovery sequence
 * (see ISO 11898-1:2015) cannot be shortened by settingor resetting
 * CCCR.INIT. If the device goes Bus_Off, it will set CCCR.INIT of its own
 * accord,stopping all bus activities. Once CCCR.INIT has been cleared by
 * the CPU, the device willthen wait for 129 occurrences of Bus Idle (129 *
 * 11 consecutive recessive bits) beforeresuming normal operation. At the
 * end of the Bus_Off recovery sequence, the ErrorManagement Counters will
 * be reset. During the waiting time after the resetting ofCCCR.INIT, each
 * time a sequence of 11 recessive bits has been monitored, a Bit0Errorcode
 * is written to PSR.LEC, enabling the CPU to readily check up whether the
 * CAN busis stuck at dominant or continuously disturbed and to monitor the
 * Bus_Off recoverysequence. ECR.REC is used to count these
 * sequences.Access: Set on read
 *
 * \details
 * 0= No Error: No error occurred since LEC has been reset by successful
 * reception or transmission.
 * 1= Stuff Error: More than 5 equal bits in a sequence have occurred in a
 * part of a received message
 * where this is not allowed.
 * 2= Form Error: A fixed format part of a received frame has the wrong
 * format.
 * 3= AckError: The message transmitted by the M_CAN was not acknowledged
 * by another node.
 * 4= Bit1Error: During the transmission of a message (with the exception
 * of the arbitration field),
 * the device wanted to send a recessive level (bit of logical value 1),
 * but the monitored bus
 * value was dominant.
 * 5= Bit0Error: During the transmission of a message (or acknowledge bit,
 * or active error flag, or
 * overload flag), the device wanted to send a dominant level (data or
 * identifier bit logical value
 * 0), but the monitored bus value was recessive. During Bus_Off recovery
 * this status is set
 * each time a sequence of 11 recessive bits has been monitored. This
 * enables the CPU to
 * monitor the proceeding of the Bus_Off recovery sequence (indicating the
 * bus is not stuck at
 * dominant or continuously disturbed).
 * 6= CRCError: The CRC check sum of a received message was incorrect. The
 * CRC of an incoming
 * message does not match with the CRC calculated from the received data.
 * 7= NoChange: Any read access to the Protocol Status Register
 * re-initializes the LEC to 7.
 * When the LEC shows the value 7, no CAN bus event was detected since the
 * last CPU read
 * access to the Protocol Status Register.
 *
 * Field: ::VTSS_MCAN_PSR . LEC
 */
#define  VTSS_F_MCAN_PSR_LEC(x)               VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_MCAN_PSR_LEC                  VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_MCAN_PSR_LEC(x)               VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Transmitter Delay Compensation Register
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TDCR
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TDCR(target)               VTSS_IOREG(target,0x12)

/**
 * \brief
 * Transmitter Delay Compensation OffsetAccess: Read and Protected Write
 *
 * \details
 * 0x00-0x7F: Offset value defining the distance between the measured delay
 * from m_can_tx to
 * m_can_rx and the secondary sample point. Valid values are 0 to 127 mtq.
 *
 * Field: ::VTSS_MCAN_TDCR . TDCO
 */
#define  VTSS_F_MCAN_TDCR_TDCO(x)             VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_MCAN_TDCR_TDCO                VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_MCAN_TDCR_TDCO(x)             VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * Transmitter Delay Compensation Filter Window LengthAccess: Read and
 * Protected Write
 *
 * \details
 * 0x00-0x7F: Defines the minimum value for the SSP position, dominant
 * edges on m_can_rx that
 * would result in an earlier SSP position are ignored for transmitter
 * delay measurement.
 * The feature is enabled when TDCF is configured to a value greater than
 * TDCO. Valid values are 0 to 127 mtq.
 *
 * Field: ::VTSS_MCAN_TDCR . TDCF
 */
#define  VTSS_F_MCAN_TDCR_TDCF(x)             VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_MCAN_TDCR_TDCF                VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_MCAN_TDCR_TDCF(x)             VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Interrupt Register
 *
 * \details
 * The flags are set when one of the listed conditions is detected
 * (edge-sensitive). The flags remain
 * set until the Host clears them. Aflag is cleared by writing a 1 to the
 * corresponding bit position.
 * Writing a 0 has no effect. Ahard reset will clear the register. The
 * configuration of IE controls
 * whether an interrupt is generated. The configuration of ILS controls on
 * which interrupt line an
 * interrupt is signaled.
 *
 * Register: \a MCAN:MCAN_REGS:IR
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_IR(target)                 VTSS_IOREG(target,0x14)

/**
 * \brief
 * Access to Reserved AddressAccess: Read and Write
 *
 * \details
 * 0= No access to reserved address occurred
 * 1= Access to reserved address occurred
 *
 * Field: ::VTSS_MCAN_IR . ARA
 */
#define  VTSS_F_MCAN_IR_ARA(x)                VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_MCAN_IR_ARA                   VTSS_BIT(29)
#define  VTSS_X_MCAN_IR_ARA(x)                VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Protocol Error in Data Phase (Data Bit Time is used)Access: Read and
 * Write
 *
 * \details
 * 0= No protocol error in data phase
 * 1= Protocol error in data phase detected  (PSR.DLEC is not equal to 0,
 * 7)
 *
 * Field: ::VTSS_MCAN_IR . PED
 */
#define  VTSS_F_MCAN_IR_PED(x)                VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_MCAN_IR_PED                   VTSS_BIT(28)
#define  VTSS_X_MCAN_IR_PED(x)                VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Protocol Error in Arbitration Phase (Nominal Bit Time is used)Access:
 * Read and Write
 *
 * \details
 * 0= No protocol error in arbitration phase
 * 1= Protocol error in arbitration phase detected (PSR.LEC is not equal to
 *  0, 7)
 *
 * Field: ::VTSS_MCAN_IR . PEA
 */
#define  VTSS_F_MCAN_IR_PEA(x)                VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_MCAN_IR_PEA                   VTSS_BIT(27)
#define  VTSS_X_MCAN_IR_PEA(x)                VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Watchdog InterruptAccess: Read and Write
 *
 * \details
 * 0= No Message RAM Watchdog event occurred
 * 1= Message RAM Watchdog event due to missing READY
 *
 * Field: ::VTSS_MCAN_IR . WDI
 */
#define  VTSS_F_MCAN_IR_WDI(x)                VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_MCAN_IR_WDI                   VTSS_BIT(26)
#define  VTSS_X_MCAN_IR_WDI(x)                VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Bus_Off StatusAccess: Read and Write
 *
 * \details
 * 0= Bus_Off status unchanged
 * 1= Bus_Off status changed
 *
 * Field: ::VTSS_MCAN_IR . BO_IR
 */
#define  VTSS_F_MCAN_IR_BO_IR(x)              VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_MCAN_IR_BO_IR                 VTSS_BIT(25)
#define  VTSS_X_MCAN_IR_BO_IR(x)              VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Warning StatusAccess: Read and Write
 *
 * \details
 * 0= Error_Warning status unchanged
 * 1= Error_Warning status changed
 *
 * Field: ::VTSS_MCAN_IR . EW_IR
 */
#define  VTSS_F_MCAN_IR_EW_IR(x)              VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_MCAN_IR_EW_IR                 VTSS_BIT(24)
#define  VTSS_X_MCAN_IR_EW_IR(x)              VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Error PassiveAccess: Read and Write
 *
 * \details
 * 0= Error_Passive status unchanged
 * 1= Error_Passive status changed
 *
 * Field: ::VTSS_MCAN_IR . EP_IR
 */
#define  VTSS_F_MCAN_IR_EP_IR(x)              VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_MCAN_IR_EP_IR                 VTSS_BIT(23)
#define  VTSS_X_MCAN_IR_EP_IR(x)              VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Error Logging OverflowAccess: Read and Write
 *
 * \details
 * 0= CAN Error Logging Counter did not overflow
 * 1= Overflow of CAN Error Logging Counter occurred
 *
 * Field: ::VTSS_MCAN_IR . ELO
 */
#define  VTSS_F_MCAN_IR_ELO(x)                VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_MCAN_IR_ELO                   VTSS_BIT(22)
#define  VTSS_X_MCAN_IR_ELO(x)                VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Bit Error UncorrectedMessage RAM bit error detected, uncorrected.
 * Controlled by input signal m_can_aeim_berr[1]generated by an optional
 * external parity / ECC logic attached to the Message RAM. An
 * uncorrectedMessage RAM bit error sets CCCR.INIT to 1. This is done to
 * avoid transmission of corrupted data.Access: Read and Write
 *
 * \details
 * 0= No bit error detected when reading from Message RAM
 * 1= Bit error detected, uncorrected (e.g. parity logic)
 *
 * Field: ::VTSS_MCAN_IR . BEU
 */
#define  VTSS_F_MCAN_IR_BEU(x)                VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_MCAN_IR_BEU                   VTSS_BIT(21)
#define  VTSS_X_MCAN_IR_BEU(x)                VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Bit Error CorrectedMessage RAM bit error detected and corrected.
 * Controlled by input signal m_can_aeim_berr[0]generated by an optional
 * external parity / ECC logic attached to the Message RAM.Access: Read and
 * Write
 *
 * \details
 * 0= No bit error detected when reading from Message RAM
 * 1= Bit error detected and corrected (e.g. ECC)
 *
 * Field: ::VTSS_MCAN_IR . BEC
 */
#define  VTSS_F_MCAN_IR_BEC(x)                VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_MCAN_IR_BEC                   VTSS_BIT(20)
#define  VTSS_X_MCAN_IR_BEC(x)                VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Message stored to Dedicated Rx BufferThe flag is set whenever a received
 * message has been stored into a dedicated Rx Buffer.Access: Read and
 * Write
 *
 * \details
 * 0= No Rx Buffer updated
 * 1= At least one received message stored into an Rx Buffer
 *
 * Field: ::VTSS_MCAN_IR . DRX
 */
#define  VTSS_F_MCAN_IR_DRX(x)                VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_MCAN_IR_DRX                   VTSS_BIT(19)
#define  VTSS_X_MCAN_IR_DRX(x)                VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Timeout OccurredAccess: Read and Write
 *
 * \details
 * 0= No timeout
 * 1= Timeout reached
 *
 * Field: ::VTSS_MCAN_IR . TOO
 */
#define  VTSS_F_MCAN_IR_TOO(x)                VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_MCAN_IR_TOO                   VTSS_BIT(18)
#define  VTSS_X_MCAN_IR_TOO(x)                VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Message RAM Access FailureThe flag is set, when the Rx Handler- Has not
 * completed acceptance filtering or storage of an accepted message until
 * the arbitrationfield of the following message has been received. In this
 * case acceptance filtering or messagestorage is aborted and the Rx
 * Handler starts processing of the following message.- Was not able to
 * write a message to the Message RAM. In this case message storage is
 * aborted.In both cases the FIFO put index is not updated resp. the New
 * Data flag for a dedicated Rx Bufferis not set, a partly stored message
 * is overwritten when the next message is stored to this location.The flag
 * is also set when the Tx Handler was not able to read a message from the
 * Message RAMin time. In this case message transmission is aborted. In
 * case of a Tx Handler access failure theM_CAN is switched into Restricted
 * Operation Mode (see Section 3.1.5). To leave RestrictedOperation Mode,
 * the Host CPU has to reset CCCR.ASM.Access: Read and Write
 *
 * \details
 * 0= No Message RAM access failure occurred
 * 1= Message RAM access failure occurred
 *
 * Field: ::VTSS_MCAN_IR . MRAF
 */
#define  VTSS_F_MCAN_IR_MRAF(x)               VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_MCAN_IR_MRAF                  VTSS_BIT(17)
#define  VTSS_X_MCAN_IR_MRAF(x)               VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Time stamp WraparoundAccess: Read and Write
 *
 * \details
 * 0= No time stamp counter wrap-around
 * 1= Time stamp counter wrapped around
 *
 * Field: ::VTSS_MCAN_IR . TSW
 */
#define  VTSS_F_MCAN_IR_TSW(x)                VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_MCAN_IR_TSW                   VTSS_BIT(16)
#define  VTSS_X_MCAN_IR_TSW(x)                VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Tx Event FIFO Element LostAccess: Read and Write
 *
 * \details
 * 0= No Tx Event FIFO element lost
 * 1= Tx Event FIFO element lost, also set after write attempt to Tx Event
 * FIFO of size zero
 *
 * Field: ::VTSS_MCAN_IR . TEFL
 */
#define  VTSS_F_MCAN_IR_TEFL(x)               VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_IR_TEFL                  VTSS_BIT(15)
#define  VTSS_X_MCAN_IR_TEFL(x)               VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Tx Event FIFO FullAccess: Read and Write
 *
 * \details
 * 0= Tx Event FIFO not full
 * 1= Tx Event FIFO full
 *
 * Field: ::VTSS_MCAN_IR . TEFF
 */
#define  VTSS_F_MCAN_IR_TEFF(x)               VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_MCAN_IR_TEFF                  VTSS_BIT(14)
#define  VTSS_X_MCAN_IR_TEFF(x)               VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Tx Event FIFO Watermark ReachedAccess: Read and Write
 *
 * \details
 * 0= Tx Event FIFO fill level below watermark
 * 1= Tx Event FIFO fill level reached watermark
 *
 * Field: ::VTSS_MCAN_IR . TEFW
 */
#define  VTSS_F_MCAN_IR_TEFW(x)               VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_MCAN_IR_TEFW                  VTSS_BIT(13)
#define  VTSS_X_MCAN_IR_TEFW(x)               VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Tx Event FIFO New EntryAccess: Read and Write
 *
 * \details
 * 0= Tx Event FIFO unchanged
 * 1= Tx Handler wrote Tx Event FIFO element
 *
 * Field: ::VTSS_MCAN_IR . TEFN
 */
#define  VTSS_F_MCAN_IR_TEFN(x)               VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_MCAN_IR_TEFN                  VTSS_BIT(12)
#define  VTSS_X_MCAN_IR_TEFN(x)               VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Tx FIFO EmptyAccess: Read and Write
 *
 * \details
 * 0= Tx FIFO non-empty
 * 1= Tx FIFO empty
 *
 * Field: ::VTSS_MCAN_IR . TFE
 */
#define  VTSS_F_MCAN_IR_TFE(x)                VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_MCAN_IR_TFE                   VTSS_BIT(11)
#define  VTSS_X_MCAN_IR_TFE(x)                VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Transmission Cancellation FinishedAccess: Read and Write
 *
 * \details
 * 0= No transmission cancellation finished
 * 1= Transmission cancellation finished
 *
 * Field: ::VTSS_MCAN_IR . TCF
 */
#define  VTSS_F_MCAN_IR_TCF(x)                VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_MCAN_IR_TCF                   VTSS_BIT(10)
#define  VTSS_X_MCAN_IR_TCF(x)                VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Transmission CompletedAccess: Read and Write
 *
 * \details
 * 0= No transmission completed
 * 1= Transmission completed
 *
 * Field: ::VTSS_MCAN_IR . TC
 */
#define  VTSS_F_MCAN_IR_TC(x)                 VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_MCAN_IR_TC                    VTSS_BIT(9)
#define  VTSS_X_MCAN_IR_TC(x)                 VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * High Priority MessageAccess: Read and Write
 *
 * \details
 * 0= No high priority message received
 * 1= High priority message received
 *
 * Field: ::VTSS_MCAN_IR . HPM
 */
#define  VTSS_F_MCAN_IR_HPM(x)                VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_MCAN_IR_HPM                   VTSS_BIT(8)
#define  VTSS_X_MCAN_IR_HPM(x)                VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Rx FIFO 1 Message LostAccess: Read and Write
 *
 * \details
 * 0= No Rx FIFO 1 message lost
 * 1= Rx FIFO 1 message lost, also set after write attempt to Rx FIFO 1 of
 * size zero
 *
 * Field: ::VTSS_MCAN_IR . RF1L
 */
#define  VTSS_F_MCAN_IR_RF1L(x)               VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_IR_RF1L                  VTSS_BIT(7)
#define  VTSS_X_MCAN_IR_RF1L(x)               VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Rx FIFO 1 FullAccess: Read and Write
 *
 * \details
 * 0= Rx FIFO 1 not full
 * 1= Rx FIFO 1 full
 *
 * Field: ::VTSS_MCAN_IR . RF1F
 */
#define  VTSS_F_MCAN_IR_RF1F(x)               VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_IR_RF1F                  VTSS_BIT(6)
#define  VTSS_X_MCAN_IR_RF1F(x)               VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Rx FIFO 1 Watermark ReachedAccess: Read and Write
 *
 * \details
 * 0= Rx FIFO 1 fill level below watermark
 * 1= Rx FIFO 1 fill level reached watermark
 *
 * Field: ::VTSS_MCAN_IR . RF1W
 */
#define  VTSS_F_MCAN_IR_RF1W(x)               VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_IR_RF1W                  VTSS_BIT(5)
#define  VTSS_X_MCAN_IR_RF1W(x)               VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Rx FIFO 1 New MessageAccess: Read and Write
 *
 * \details
 * 0= No new message written to Rx FIFO 1
 * 1= New message written to Rx FIFO 1
 *
 * Field: ::VTSS_MCAN_IR . RF1N
 */
#define  VTSS_F_MCAN_IR_RF1N(x)               VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_IR_RF1N                  VTSS_BIT(4)
#define  VTSS_X_MCAN_IR_RF1N(x)               VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Rx FIFO 0 Message LostAccess: Read and Write
 *
 * \details
 * 0= No Rx FIFO 0 message lost
 * 1= Rx FIFO 0 message lost, also set after write attempt to Rx FIFO 0 of
 * size zero
 *
 * Field: ::VTSS_MCAN_IR . RF0L
 */
#define  VTSS_F_MCAN_IR_RF0L(x)               VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_IR_RF0L                  VTSS_BIT(3)
#define  VTSS_X_MCAN_IR_RF0L(x)               VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Rx FIFO 0 FullAccess: Read and Write
 *
 * \details
 * 0= Rx FIFO 0 not full
 * 1= Rx FIFO 0 full
 *
 * Field: ::VTSS_MCAN_IR . RF0F
 */
#define  VTSS_F_MCAN_IR_RF0F(x)               VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_IR_RF0F                  VTSS_BIT(2)
#define  VTSS_X_MCAN_IR_RF0F(x)               VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Rx FIFO 0 Watermark ReachedAccess: Read and Write
 *
 * \details
 * 0= Rx FIFO 0 fill level below watermark
 * 1= Rx FIFO 0 fill level reached watermark
 *
 * Field: ::VTSS_MCAN_IR . RF0W
 */
#define  VTSS_F_MCAN_IR_RF0W(x)               VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_IR_RF0W                  VTSS_BIT(1)
#define  VTSS_X_MCAN_IR_RF0W(x)               VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Rx FIFO 0 New MessageAccess: Read and Write
 *
 * \details
 * 0= No new message written to Rx FIFO 0
 * 1= New message written to Rx FIFO 0
 *
 * Field: ::VTSS_MCAN_IR . RF0N
 */
#define  VTSS_F_MCAN_IR_RF0N(x)               VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_IR_RF0N                  VTSS_BIT(0)
#define  VTSS_X_MCAN_IR_RF0N(x)               VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Interrupt Enable
 *
 * \details
 * The settings in the Interrupt Enable register determine which status
 * changes in the Interrupt
 * Register will be signaled on an interrupt line.
 * 0= Interrupt disabled
 * 1= Interrupt enabled
 *
 * Register: \a MCAN:MCAN_REGS:IE
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_IE(target)                 VTSS_IOREG(target,0x15)

/**
 * \brief
 * Access to Reserved Address Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . ARAE
 */
#define  VTSS_F_MCAN_IE_ARAE(x)               VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_MCAN_IE_ARAE                  VTSS_BIT(29)
#define  VTSS_X_MCAN_IE_ARAE(x)               VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Protocol Error in Data Phase Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . PEDE
 */
#define  VTSS_F_MCAN_IE_PEDE(x)               VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_MCAN_IE_PEDE                  VTSS_BIT(28)
#define  VTSS_X_MCAN_IE_PEDE(x)               VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Protocol Error in Arbitration Phase Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . PEAE
 */
#define  VTSS_F_MCAN_IE_PEAE(x)               VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_MCAN_IE_PEAE                  VTSS_BIT(27)
#define  VTSS_X_MCAN_IE_PEAE(x)               VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Watchdog Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . WDIE
 */
#define  VTSS_F_MCAN_IE_WDIE(x)               VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_MCAN_IE_WDIE                  VTSS_BIT(26)
#define  VTSS_X_MCAN_IE_WDIE(x)               VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Bus_Off Status Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . BOE
 */
#define  VTSS_F_MCAN_IE_BOE(x)                VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_MCAN_IE_BOE                   VTSS_BIT(25)
#define  VTSS_X_MCAN_IE_BOE(x)                VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Warning Status Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . EWE
 */
#define  VTSS_F_MCAN_IE_EWE(x)                VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_MCAN_IE_EWE                   VTSS_BIT(24)
#define  VTSS_X_MCAN_IE_EWE(x)                VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Error Passive Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . EPE
 */
#define  VTSS_F_MCAN_IE_EPE(x)                VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_MCAN_IE_EPE                   VTSS_BIT(23)
#define  VTSS_X_MCAN_IE_EPE(x)                VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Error Logging Overflow Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . ELOE
 */
#define  VTSS_F_MCAN_IE_ELOE(x)               VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_MCAN_IE_ELOE                  VTSS_BIT(22)
#define  VTSS_X_MCAN_IE_ELOE(x)               VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Bit Error Uncorrected Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . BEUE
 */
#define  VTSS_F_MCAN_IE_BEUE(x)               VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_MCAN_IE_BEUE                  VTSS_BIT(21)
#define  VTSS_X_MCAN_IE_BEUE(x)               VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Bit Error Corrected Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . BECE
 */
#define  VTSS_F_MCAN_IE_BECE(x)               VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_MCAN_IE_BECE                  VTSS_BIT(20)
#define  VTSS_X_MCAN_IE_BECE(x)               VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Message stored to Dedicated Rx Buffer Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . DRXE
 */
#define  VTSS_F_MCAN_IE_DRXE(x)               VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_MCAN_IE_DRXE                  VTSS_BIT(19)
#define  VTSS_X_MCAN_IE_DRXE(x)               VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Timeout Occurred Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TOOE
 */
#define  VTSS_F_MCAN_IE_TOOE(x)               VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_MCAN_IE_TOOE                  VTSS_BIT(18)
#define  VTSS_X_MCAN_IE_TOOE(x)               VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Message RAM Access Failure Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . MRAFE
 */
#define  VTSS_F_MCAN_IE_MRAFE(x)              VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_MCAN_IE_MRAFE                 VTSS_BIT(17)
#define  VTSS_X_MCAN_IE_MRAFE(x)              VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Time stamp Wraparound Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TSWE
 */
#define  VTSS_F_MCAN_IE_TSWE(x)               VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_MCAN_IE_TSWE                  VTSS_BIT(16)
#define  VTSS_X_MCAN_IE_TSWE(x)               VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Tx Event FIFO Event Lost Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TEFLE
 */
#define  VTSS_F_MCAN_IE_TEFLE(x)              VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_IE_TEFLE                 VTSS_BIT(15)
#define  VTSS_X_MCAN_IE_TEFLE(x)              VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Tx Event FIFO Full Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TEFFE
 */
#define  VTSS_F_MCAN_IE_TEFFE(x)              VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_MCAN_IE_TEFFE                 VTSS_BIT(14)
#define  VTSS_X_MCAN_IE_TEFFE(x)              VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Tx Event FIFO Watermark Reached Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TEFWE
 */
#define  VTSS_F_MCAN_IE_TEFWE(x)              VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_MCAN_IE_TEFWE                 VTSS_BIT(13)
#define  VTSS_X_MCAN_IE_TEFWE(x)              VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Tx Event FIFO New Entry Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TEFNE
 */
#define  VTSS_F_MCAN_IE_TEFNE(x)              VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_MCAN_IE_TEFNE                 VTSS_BIT(12)
#define  VTSS_X_MCAN_IE_TEFNE(x)              VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Tx FIFO Empty Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TFEE
 */
#define  VTSS_F_MCAN_IE_TFEE(x)               VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_MCAN_IE_TFEE                  VTSS_BIT(11)
#define  VTSS_X_MCAN_IE_TFEE(x)               VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Transmission Cancellation Finished Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TCFE
 */
#define  VTSS_F_MCAN_IE_TCFE(x)               VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_MCAN_IE_TCFE                  VTSS_BIT(10)
#define  VTSS_X_MCAN_IE_TCFE(x)               VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Transmission Completed Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . TCE
 */
#define  VTSS_F_MCAN_IE_TCE(x)                VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_MCAN_IE_TCE                   VTSS_BIT(9)
#define  VTSS_X_MCAN_IE_TCE(x)                VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * High Priority Message Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . HPME
 */
#define  VTSS_F_MCAN_IE_HPME(x)               VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_MCAN_IE_HPME                  VTSS_BIT(8)
#define  VTSS_X_MCAN_IE_HPME(x)               VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Rx FIFO 1 Message Lost Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . RF1LE
 */
#define  VTSS_F_MCAN_IE_RF1LE(x)              VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_IE_RF1LE                 VTSS_BIT(7)
#define  VTSS_X_MCAN_IE_RF1LE(x)              VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Rx FIFO 1 Full Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . RF1FE
 */
#define  VTSS_F_MCAN_IE_RF1FE(x)              VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_IE_RF1FE                 VTSS_BIT(6)
#define  VTSS_X_MCAN_IE_RF1FE(x)              VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Rx FIFO 1 Watermark Reached Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . RF1WE
 */
#define  VTSS_F_MCAN_IE_RF1WE(x)              VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_IE_RF1WE                 VTSS_BIT(5)
#define  VTSS_X_MCAN_IE_RF1WE(x)              VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Rx FIFO 1 New Message Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . RF1NE
 */
#define  VTSS_F_MCAN_IE_RF1NE(x)              VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_IE_RF1NE                 VTSS_BIT(4)
#define  VTSS_X_MCAN_IE_RF1NE(x)              VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Rx FIFO 0 Message Lost Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . RF0LE
 */
#define  VTSS_F_MCAN_IE_RF0LE(x)              VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_IE_RF0LE                 VTSS_BIT(3)
#define  VTSS_X_MCAN_IE_RF0LE(x)              VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Rx FIFO 0 Full Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . RF0FE
 */
#define  VTSS_F_MCAN_IE_RF0FE(x)              VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_IE_RF0FE                 VTSS_BIT(2)
#define  VTSS_X_MCAN_IE_RF0FE(x)              VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Rx FIFO 0 Watermark Reached Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . RF0WE
 */
#define  VTSS_F_MCAN_IE_RF0WE(x)              VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_IE_RF0WE                 VTSS_BIT(1)
#define  VTSS_X_MCAN_IE_RF0WE(x)              VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Rx FIFO 0 New Message Interrupt Enable
 *
 * \details
 * Field: ::VTSS_MCAN_IE . RF0NE
 */
#define  VTSS_F_MCAN_IE_RF0NE(x)              VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_IE_RF0NE                 VTSS_BIT(0)
#define  VTSS_X_MCAN_IE_RF0NE(x)              VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Interrupt Line Select
 *
 * \details
 * The Interrupt Line Select register assigns an interrupt generated by a
 * specific interrupt flag from the
 * Interrupt Register to one of the two module interrupt lines. For
 * interrupt generation the respective
 * interrupt line has to be enabled via ILE.EINT0 and ILE.EINT1.
 * 0= Interrupt assigned to interrupt line m_can_int0
 * 1= Interrupt assigned to interrupt line m_can_int1
 *
 * Register: \a MCAN:MCAN_REGS:ILS
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_ILS(target)                VTSS_IOREG(target,0x16)

/**
 * \brief
 * Access to Reserved Address Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . ARAL
 */
#define  VTSS_F_MCAN_ILS_ARAL(x)              VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_MCAN_ILS_ARAL                 VTSS_BIT(29)
#define  VTSS_X_MCAN_ILS_ARAL(x)              VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Protocol Error in Data Phase Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . PEDL
 */
#define  VTSS_F_MCAN_ILS_PEDL(x)              VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_MCAN_ILS_PEDL                 VTSS_BIT(28)
#define  VTSS_X_MCAN_ILS_PEDL(x)              VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Protocol Error in Arbitration Phase Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . PEAL
 */
#define  VTSS_F_MCAN_ILS_PEAL(x)              VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_MCAN_ILS_PEAL                 VTSS_BIT(27)
#define  VTSS_X_MCAN_ILS_PEAL(x)              VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Watchdog Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . WDIL
 */
#define  VTSS_F_MCAN_ILS_WDIL(x)              VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_MCAN_ILS_WDIL                 VTSS_BIT(26)
#define  VTSS_X_MCAN_ILS_WDIL(x)              VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Bus_Off Status Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . BOL
 */
#define  VTSS_F_MCAN_ILS_BOL(x)               VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_MCAN_ILS_BOL                  VTSS_BIT(25)
#define  VTSS_X_MCAN_ILS_BOL(x)               VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Warning Status Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . EWL
 */
#define  VTSS_F_MCAN_ILS_EWL(x)               VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_MCAN_ILS_EWL                  VTSS_BIT(24)
#define  VTSS_X_MCAN_ILS_EWL(x)               VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Error Passive Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . EPL
 */
#define  VTSS_F_MCAN_ILS_EPL(x)               VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_MCAN_ILS_EPL                  VTSS_BIT(23)
#define  VTSS_X_MCAN_ILS_EPL(x)               VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Error Logging Overflow Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . ELOL
 */
#define  VTSS_F_MCAN_ILS_ELOL(x)              VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_MCAN_ILS_ELOL                 VTSS_BIT(22)
#define  VTSS_X_MCAN_ILS_ELOL(x)              VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Bit Error Uncorrected Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . BEUL
 */
#define  VTSS_F_MCAN_ILS_BEUL(x)              VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_MCAN_ILS_BEUL                 VTSS_BIT(21)
#define  VTSS_X_MCAN_ILS_BEUL(x)              VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Bit Error Corrected Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . BECL
 */
#define  VTSS_F_MCAN_ILS_BECL(x)              VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_MCAN_ILS_BECL                 VTSS_BIT(20)
#define  VTSS_X_MCAN_ILS_BECL(x)              VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Message stored to Dedicated Rx Buffer Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . DRXL
 */
#define  VTSS_F_MCAN_ILS_DRXL(x)              VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_MCAN_ILS_DRXL                 VTSS_BIT(19)
#define  VTSS_X_MCAN_ILS_DRXL(x)              VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Timeout Occurred Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TOOL
 */
#define  VTSS_F_MCAN_ILS_TOOL(x)              VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_MCAN_ILS_TOOL                 VTSS_BIT(18)
#define  VTSS_X_MCAN_ILS_TOOL(x)              VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Message RAM Access Failure Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . MRAFL
 */
#define  VTSS_F_MCAN_ILS_MRAFL(x)             VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_MCAN_ILS_MRAFL                VTSS_BIT(17)
#define  VTSS_X_MCAN_ILS_MRAFL(x)             VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Time stamp Wraparound Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TSWL
 */
#define  VTSS_F_MCAN_ILS_TSWL(x)              VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_MCAN_ILS_TSWL                 VTSS_BIT(16)
#define  VTSS_X_MCAN_ILS_TSWL(x)              VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Tx Event FIFO Event Lost Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TEFLL
 */
#define  VTSS_F_MCAN_ILS_TEFLL(x)             VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_ILS_TEFLL                VTSS_BIT(15)
#define  VTSS_X_MCAN_ILS_TEFLL(x)             VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Tx Event FIFO Full Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TEFFL
 */
#define  VTSS_F_MCAN_ILS_TEFFL(x)             VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_MCAN_ILS_TEFFL                VTSS_BIT(14)
#define  VTSS_X_MCAN_ILS_TEFFL(x)             VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Tx Event FIFO Watermark Reached Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TEFWL
 */
#define  VTSS_F_MCAN_ILS_TEFWL(x)             VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_MCAN_ILS_TEFWL                VTSS_BIT(13)
#define  VTSS_X_MCAN_ILS_TEFWL(x)             VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Tx Event FIFO New Entry Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TEFNL
 */
#define  VTSS_F_MCAN_ILS_TEFNL(x)             VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_MCAN_ILS_TEFNL                VTSS_BIT(12)
#define  VTSS_X_MCAN_ILS_TEFNL(x)             VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Tx FIFO Empty Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TFEL
 */
#define  VTSS_F_MCAN_ILS_TFEL(x)              VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_MCAN_ILS_TFEL                 VTSS_BIT(11)
#define  VTSS_X_MCAN_ILS_TFEL(x)              VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Transmission Cancellation Finished Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TCFL
 */
#define  VTSS_F_MCAN_ILS_TCFL(x)              VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_MCAN_ILS_TCFL                 VTSS_BIT(10)
#define  VTSS_X_MCAN_ILS_TCFL(x)              VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Transmission Completed Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . TCL
 */
#define  VTSS_F_MCAN_ILS_TCL(x)               VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_MCAN_ILS_TCL                  VTSS_BIT(9)
#define  VTSS_X_MCAN_ILS_TCL(x)               VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * High Priority Message Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . HPML
 */
#define  VTSS_F_MCAN_ILS_HPML(x)              VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_MCAN_ILS_HPML                 VTSS_BIT(8)
#define  VTSS_X_MCAN_ILS_HPML(x)              VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Rx FIFO 1 Message Lost Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . RF1LL
 */
#define  VTSS_F_MCAN_ILS_RF1LL(x)             VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_ILS_RF1LL                VTSS_BIT(7)
#define  VTSS_X_MCAN_ILS_RF1LL(x)             VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Rx FIFO 1 Full Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . RF1FL
 */
#define  VTSS_F_MCAN_ILS_RF1FL(x)             VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_ILS_RF1FL                VTSS_BIT(6)
#define  VTSS_X_MCAN_ILS_RF1FL(x)             VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Rx FIFO 1 Watermark Reached Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . RF1WL
 */
#define  VTSS_F_MCAN_ILS_RF1WL(x)             VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_ILS_RF1WL                VTSS_BIT(5)
#define  VTSS_X_MCAN_ILS_RF1WL(x)             VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Rx FIFO 1 New Message Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . RF1NL
 */
#define  VTSS_F_MCAN_ILS_RF1NL(x)             VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_ILS_RF1NL                VTSS_BIT(4)
#define  VTSS_X_MCAN_ILS_RF1NL(x)             VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Rx FIFO 0 Message Lost Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . RF0LL
 */
#define  VTSS_F_MCAN_ILS_RF0LL(x)             VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_ILS_RF0LL                VTSS_BIT(3)
#define  VTSS_X_MCAN_ILS_RF0LL(x)             VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Rx FIFO 0 Full Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . RF0FL
 */
#define  VTSS_F_MCAN_ILS_RF0FL(x)             VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_ILS_RF0FL                VTSS_BIT(2)
#define  VTSS_X_MCAN_ILS_RF0FL(x)             VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Rx FIFO 0 Watermark Reached Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . RF0WL
 */
#define  VTSS_F_MCAN_ILS_RF0WL(x)             VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_ILS_RF0WL                VTSS_BIT(1)
#define  VTSS_X_MCAN_ILS_RF0WL(x)             VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Rx FIFO 0 New Message Interrupt Line
 *
 * \details
 * Field: ::VTSS_MCAN_ILS . RF0NL
 */
#define  VTSS_F_MCAN_ILS_RF0NL(x)             VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_ILS_RF0NL                VTSS_BIT(0)
#define  VTSS_X_MCAN_ILS_RF0NL(x)             VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Interrupt Line Enable
 *
 * \details
 * Each of the two interrupt lines to the CPU can be enabled / disabled
 * separately by programming bits
 * EINT0 and EINT1.
 *
 * Register: \a MCAN:MCAN_REGS:ILE
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_ILE(target)                VTSS_IOREG(target,0x17)

/**
 * \brief
 * Enable Interrupt Line 1
 *
 * \details
 * 0= Interrupt line m_can_int1 disabled
 * 1= Interrupt line m_can_int1 enabled
 *
 * Field: ::VTSS_MCAN_ILE . EINT1
 */
#define  VTSS_F_MCAN_ILE_EINT1(x)             VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_ILE_EINT1                VTSS_BIT(1)
#define  VTSS_X_MCAN_ILE_EINT1(x)             VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable Interrupt Line 0
 *
 * \details
 * 0= Interrupt line m_can_int0 disabled
 * 1= Interrupt line m_can_int0 enabled
 *
 * Field: ::VTSS_MCAN_ILE . EINT0
 */
#define  VTSS_F_MCAN_ILE_EINT0(x)             VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_ILE_EINT0                VTSS_BIT(0)
#define  VTSS_X_MCAN_ILE_EINT0(x)             VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Global Filter Configuration
 *
 * \details
 * Global settings for Message ID filtering. The Global Filter
 * Configuration controls the filter path for
 * standard and extended messages
 *
 * Register: \a MCAN:MCAN_REGS:GFC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_GFC(target)                VTSS_IOREG(target,0x20)

/**
 * \brief
 * Accept Non-matching Frames StandardDefines how received messages with
 * 11-bit IDs that do not match any element of the filter list
 * aretreated.Access: Read and Protected Write
 *
 * \details
 * 00= Accept in Rx FIFO 0
 * 01= Accept in Rx FIFO 1
 * 10= Reject
 * 11= Reject
 *
 * Field: ::VTSS_MCAN_GFC . ANFS
 */
#define  VTSS_F_MCAN_GFC_ANFS(x)              VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_MCAN_GFC_ANFS                 VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_MCAN_GFC_ANFS(x)              VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Accept Non-matching Frames ExtendedDefines how received messages with
 * 29-bit IDs that do not match any element of the filter list
 * aretreated.Access: Read and Protected Write
 *
 * \details
 * 00= Accept in Rx FIFO 0
 * 01= Accept in Rx FIFO 1
 * 10= Reject
 * 11= Reject
 *
 * Field: ::VTSS_MCAN_GFC . ANFE
 */
#define  VTSS_F_MCAN_GFC_ANFE(x)              VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MCAN_GFC_ANFE                 VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MCAN_GFC_ANFE(x)              VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Reject Remote Frames StandardAccess: Read and Protected Write
 *
 * \details
 * 0= Filter remote frames with 11-bit standard IDs
 * 1= Reject all remote frames with 11-bit standard IDs
 *
 * Field: ::VTSS_MCAN_GFC . RRFS
 */
#define  VTSS_F_MCAN_GFC_RRFS(x)              VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_GFC_RRFS                 VTSS_BIT(1)
#define  VTSS_X_MCAN_GFC_RRFS(x)              VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reject Remote Frames ExtendedAccess: Read and Protected Write
 *
 * \details
 * 0= Filter remote frames with 29-bit extended IDs
 * 1= Reject all remote frames with 29-bit extended IDs

 *
 * Field: ::VTSS_MCAN_GFC . RRFE
 */
#define  VTSS_F_MCAN_GFC_RRFE(x)              VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_GFC_RRFE                 VTSS_BIT(0)
#define  VTSS_X_MCAN_GFC_RRFE(x)              VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Standard ID Filter Configuration
 *
 * \details
 * Settings for 11-bit standard Message ID filtering. The Standard ID
 * Filter Configuration controls the
 * filter path for standard messages as described in Figure 6 in mcan user
 * manual
 *
 * Register: \a MCAN:MCAN_REGS:SIDFC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_SIDFC(target)              VTSS_IOREG(target,0x21)

/**
 * \brief
 * List Size StandardAccess: Read and Protected Write
 *
 * \details
 * 0= No standard Message ID filter
 * 1-128= Number of standard Message ID filter elements
 * >128= Values greater than 128 are interpreted as 128
 *
 * Field: ::VTSS_MCAN_SIDFC . LSS
 */
#define  VTSS_F_MCAN_SIDFC_LSS(x)             VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_MCAN_SIDFC_LSS                VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_MCAN_SIDFC_LSS(x)             VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Filter List Standard Start AddressStart address of standard Message ID
 * filter list (32-bit word address, see Figure 2 in mcan user manual)
 * .Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_SIDFC . FLSSA
 */
#define  VTSS_F_MCAN_SIDFC_FLSSA(x)           VTSS_ENCODE_BITFIELD(x,2,14)
#define  VTSS_M_MCAN_SIDFC_FLSSA              VTSS_ENCODE_BITMASK(2,14)
#define  VTSS_X_MCAN_SIDFC_FLSSA(x)           VTSS_EXTRACT_BITFIELD(x,2,14)


/**
 * \brief Extended ID Filter Configuration
 *
 * \details
 * Settings for 29-bit extended Message ID filtering. The Extended ID
 * Filter Configuration controls the
 * filter path for standard messages as described in Figure 7 in mcan user
 * manual.
 *
 * Register: \a MCAN:MCAN_REGS:XIDFC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_XIDFC(target)              VTSS_IOREG(target,0x22)

/**
 * \brief
 * List Size ExtendedAccess: Read and Protected Write
 *
 * \details
 * 0= No extended Message ID filter
 * 1-64= Number of extended Message ID filter elements
 * >64= Values greater than 64 are interpreted as 64
 *
 * Field: ::VTSS_MCAN_XIDFC . LSE
 */
#define  VTSS_F_MCAN_XIDFC_LSE(x)             VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_MCAN_XIDFC_LSE                VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_MCAN_XIDFC_LSE(x)             VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Filter List Extended Start AddressStart address of extended Message ID
 * filter list (32-bit word address, see Figure 2 in mcan user
 * manual).Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_XIDFC . FLESA
 */
#define  VTSS_F_MCAN_XIDFC_FLESA(x)           VTSS_ENCODE_BITFIELD(x,2,14)
#define  VTSS_M_MCAN_XIDFC_FLESA              VTSS_ENCODE_BITMASK(2,14)
#define  VTSS_X_MCAN_XIDFC_FLESA(x)           VTSS_EXTRACT_BITFIELD(x,2,14)


/**
 * \brief Extended ID AND Mask
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:XIDAM
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_XIDAM(target)              VTSS_IOREG(target,0x24)

/**
 * \brief
 * Extended ID MaskFor acceptance filtering of extended frames the Extended
 * ID AND Mask is ANDed with the MessageID of a received frame. Intended
 * for masking of 29-bit IDs in SAE J1939. With the reset value of allbits
 * set to one the mask is not active.Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_XIDAM . EIDM
 */
#define  VTSS_F_MCAN_XIDAM_EIDM(x)            VTSS_ENCODE_BITFIELD(x,0,29)
#define  VTSS_M_MCAN_XIDAM_EIDM               VTSS_ENCODE_BITMASK(0,29)
#define  VTSS_X_MCAN_XIDAM_EIDM(x)            VTSS_EXTRACT_BITFIELD(x,0,29)


/**
 * \brief High Priority Message Status
 *
 * \details
 * This register is updated every time a Message ID filter element
 * configured to generate a priority
 * event matches. This can be used to monitor the status of incoming high
 * priority messages and to
 * enable fast access to these messages.
 *
 * Register: \a MCAN:MCAN_REGS:HPMS
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_HPMS(target)               VTSS_IOREG(target,0x25)

/**
 * \brief
 * Filter ListIndicates the filter list of the matching filter
 * element.Access: Read
 *
 * \details
 * 0= Standard Filter List
 * 1= Extended Filter List
 *
 * Field: ::VTSS_MCAN_HPMS . FLST
 */
#define  VTSS_F_MCAN_HPMS_FLST(x)             VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_HPMS_FLST                VTSS_BIT(15)
#define  VTSS_X_MCAN_HPMS_FLST(x)             VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Filter IndexIndex of matching filter element. Range is 0 to SIDFC.LSS -
 * 1 resp. XIDFC.LSE - 1.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_HPMS . FIDX
 */
#define  VTSS_F_MCAN_HPMS_FIDX(x)             VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_MCAN_HPMS_FIDX                VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_MCAN_HPMS_FIDX(x)             VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * Message Storage IndicatorAccess: Read
 *
 * \details
 * 00= No FIFO selected
 * 01= FIFO message lost
 * 10= Message stored in FIFO 0
 * 11= Message stored in FIFO 1
 *
 * Field: ::VTSS_MCAN_HPMS . MSI
 */
#define  VTSS_F_MCAN_HPMS_MSI(x)              VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_MCAN_HPMS_MSI                 VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_MCAN_HPMS_MSI(x)              VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Buffer IndexIndex of Rx FIFO element to which the message was stored.
 * Only valid when MSI[1] = 1.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_HPMS . BIDX
 */
#define  VTSS_F_MCAN_HPMS_BIDX(x)             VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MCAN_HPMS_BIDX                VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MCAN_HPMS_BIDX(x)             VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief New Data 1
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:NDAT1
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_NDAT1(target)              VTSS_IOREG(target,0x26)

/**
 * \brief
 * New DataThe register holds the New Data flags of Rx Buffers 0 to 31. The
 * flags are set when the respectiveRx Buffer has been updated from a
 * received frame. The flags remain set until the Host clears them.Aflag is
 * cleared by writing a 1 to the corresponding bit position. Writing a 0
 * has no effect. Ahardreset will clear the register.Access: Read and Write
 *
 * \details
 * 0= Rx Buffer not updated
 * 1= Rx Buffer updated from new message
 *
 * Field: ::VTSS_MCAN_NDAT1 . ND_NDAT1
 */
#define  VTSS_F_MCAN_NDAT1_ND_NDAT1(x)        (x)
#define  VTSS_M_MCAN_NDAT1_ND_NDAT1           0xffffffff
#define  VTSS_X_MCAN_NDAT1_ND_NDAT1(x)        (x)


/**
 * \brief New Data 2
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:NDAT2
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_NDAT2(target)              VTSS_IOREG(target,0x27)

/**
 * \brief
 * New DataThe register holds the New Data flags of Rx Buffers 32 to 63.
 * The flags are set when the respectiveRx Buffer has been updated from a
 * received frame. The flags remain set until the Host clears them.Aflag is
 * cleared by writing a 1 to the corresponding bit position. Writing a 0
 * has no effect. Ahardreset will clear the register.Access: Read and Write
 *
 * \details
 * 0= Rx Buffer not updated
 * 1= Rx Buffer updated from new message
 *
 * Field: ::VTSS_MCAN_NDAT2 . ND_NDAT2
 */
#define  VTSS_F_MCAN_NDAT2_ND_NDAT2(x)        (x)
#define  VTSS_M_MCAN_NDAT2_ND_NDAT2           0xffffffff
#define  VTSS_X_MCAN_NDAT2_ND_NDAT2(x)        (x)


/**
 * \brief Rx FIFO 0 Configuration
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:RXF0C
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RXF0C(target)              VTSS_IOREG(target,0x28)

/**
 * \brief
 * FIFO 0 Operation ModeFIFO 0 can be operated in blocking or in overwrite
 * mode (see Section 3.4.2 in mcan user manual).Access: Read and Protected
 * Write
 *
 * \details
 * 0= FIFO 0 blocking mode
 * 1= FIFO 0 overwrite mode
 *
 * Field: ::VTSS_MCAN_RXF0C . F0OM
 */
#define  VTSS_F_MCAN_RXF0C_F0OM(x)            VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_MCAN_RXF0C_F0OM               VTSS_BIT(31)
#define  VTSS_X_MCAN_RXF0C_F0OM(x)            VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * Rx FIFO 0 WatermarkAccess: Read and Protected Write
 *
 * \details
 * 0= Watermark interrupt disabled
 * 1-64= Level for Rx FIFO 0 watermark interrupt (IR.RF0W)
 * >64= Watermark interrupt disabled
 *
 * Field: ::VTSS_MCAN_RXF0C . F0WM
 */
#define  VTSS_F_MCAN_RXF0C_F0WM(x)            VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_MCAN_RXF0C_F0WM               VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_MCAN_RXF0C_F0WM(x)            VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * Rx FIFO 0 SizeAccess: Read and Protected Write
 *
 * \details
 * 0= No Rx FIFO 0
 * 1-64= Number of Rx FIFO 0 elements
 * >64= Values greater than 64 are interpreted as 64
 * The Rx FIFO 0 elements are indexed from 0 to F0S-1
 *
 * Field: ::VTSS_MCAN_RXF0C . F0S
 */
#define  VTSS_F_MCAN_RXF0C_F0S(x)             VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_MCAN_RXF0C_F0S                VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_MCAN_RXF0C_F0S(x)             VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Rx FIFO 0 Start AddressStart address of Rx FIFO 0 in Message RAM (32-bit
 * word address, see Figure 2 in mcan user manual).Access: Read and
 * Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_RXF0C . F0SA
 */
#define  VTSS_F_MCAN_RXF0C_F0SA(x)            VTSS_ENCODE_BITFIELD(x,2,14)
#define  VTSS_M_MCAN_RXF0C_F0SA               VTSS_ENCODE_BITMASK(2,14)
#define  VTSS_X_MCAN_RXF0C_F0SA(x)            VTSS_EXTRACT_BITFIELD(x,2,14)


/**
 * \brief 2.3.28 Rx FIFO 0 Status
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:RXF0S
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RXF0S(target)              VTSS_IOREG(target,0x29)

/**
 * \brief
 * Rx FIFO 0 Message LostThis bit is a copy of interrupt flag IR.RF0L. When
 * IR.RF0L is reset, this bit is also reset.Note: Overwriting the oldest
 * message when RXF0C.F0OM = 1 will not set this flag.Access: Read
 *
 * \details
 * 0= No Rx FIFO 0 message lost
 * 1= Rx FIFO 0 message lost, also set after write attempt to Rx FIFO 0 of
 * size zero
 *
 * Field: ::VTSS_MCAN_RXF0S . RF0L_RXF0S
 */
#define  VTSS_F_MCAN_RXF0S_RF0L_RXF0S(x)      VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_MCAN_RXF0S_RF0L_RXF0S         VTSS_BIT(25)
#define  VTSS_X_MCAN_RXF0S_RF0L_RXF0S(x)      VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Rx FIFO 0 FullAccess: Read
 *
 * \details
 * 0= Rx FIFO 0 not full
 * 1= Rx FIFO 0 full
 *
 * Field: ::VTSS_MCAN_RXF0S . F0F
 */
#define  VTSS_F_MCAN_RXF0S_F0F(x)             VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_MCAN_RXF0S_F0F                VTSS_BIT(24)
#define  VTSS_X_MCAN_RXF0S_F0F(x)             VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Rx FIFO 0 Put IndexRx FIFO 0 write index pointer, range 0 to 63.Access:
 * Read
 *
 * \details
 * Field: ::VTSS_MCAN_RXF0S . F0PI
 */
#define  VTSS_F_MCAN_RXF0S_F0PI(x)            VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_MCAN_RXF0S_F0PI               VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_MCAN_RXF0S_F0PI(x)            VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Rx FIFO 0 Get IndexRx FIFO 0 read index pointer, range 0 to 63.Access:
 * Read
 *
 * \details
 * Field: ::VTSS_MCAN_RXF0S . F0GI
 */
#define  VTSS_F_MCAN_RXF0S_F0GI(x)            VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_MCAN_RXF0S_F0GI               VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_MCAN_RXF0S_F0GI(x)            VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * Rx FIFO 0 Fill LevelNumber of elements stored in Rx FIFO 0, range 0 to
 * 64.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_RXF0S . F0FL
 */
#define  VTSS_F_MCAN_RXF0S_F0FL(x)            VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_MCAN_RXF0S_F0FL               VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_MCAN_RXF0S_F0FL(x)            VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Rx FIFO 0 Acknowledge
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:RXF0A
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RXF0A(target)              VTSS_IOREG(target,0x2a)

/**
 * \brief
 * Rx FIFO 0 Acknowledge IndexAfter the Host has read a message or a
 * sequence of messages from Rx FIFO 0 it has to write thebuffer index of
 * the last element read from Rx FIFO 0 to F0AI. This will set the Rx FIFO
 * 0 Get IndexRXF0S.F0GI to F0AI + 1 and update the FIFO 0 Fill Level
 * RXF0S.F0FL.Access: Read and Write
 *
 * \details
 * Field: ::VTSS_MCAN_RXF0A . F0AI
 */
#define  VTSS_F_MCAN_RXF0A_F0AI(x)            VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MCAN_RXF0A_F0AI               VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MCAN_RXF0A_F0AI(x)            VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Rx Buffer Configuration
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:RXBC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RXBC(target)               VTSS_IOREG(target,0x2b)

/**
 * \brief
 * Rx Buffer Start AddressConfigures the start address of the Rx Buffers
 * section in the Message RAM (32-bit word address).Also used to reference
 * debug messages A,B,C.Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_RXBC . RBSA
 */
#define  VTSS_F_MCAN_RXBC_RBSA(x)             VTSS_ENCODE_BITFIELD(x,2,14)
#define  VTSS_M_MCAN_RXBC_RBSA                VTSS_ENCODE_BITMASK(2,14)
#define  VTSS_X_MCAN_RXBC_RBSA(x)             VTSS_EXTRACT_BITFIELD(x,2,14)


/**
 * \brief Rx FIFO 1 Configuration
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:RXF1C
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RXF1C(target)              VTSS_IOREG(target,0x2c)

/**
 * \brief
 * FIFO 1 Operation ModeFIFO 1 can be operated in blocking or in overwrite
 * mode (see Section 3.4.2 in mcan user manual).Access: Read and Protected
 * Write
 *
 * \details
 * 0= FIFO 1 blocking mode
 * 1= FIFO 1 overwrite mode
 *
 * Field: ::VTSS_MCAN_RXF1C . F1OM
 */
#define  VTSS_F_MCAN_RXF1C_F1OM(x)            VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_MCAN_RXF1C_F1OM               VTSS_BIT(31)
#define  VTSS_X_MCAN_RXF1C_F1OM(x)            VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * Rx FIFO 1 WatermarkAccess: Read and Protected Write
 *
 * \details
 * 0= Watermark interrupt disabled
 * 1-64= Level for Rx FIFO 1 watermark interrupt (IR.RF1W)
 * >64= Watermark interrupt disabled

 *
 * Field: ::VTSS_MCAN_RXF1C . F1WM
 */
#define  VTSS_F_MCAN_RXF1C_F1WM(x)            VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_MCAN_RXF1C_F1WM               VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_MCAN_RXF1C_F1WM(x)            VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * Rx FIFO 1 Size.Access: Read and Protected Write
 *
 * \details
 * 0= No Rx FIFO 1
 * 1-64= Number of Rx FIFO 1 elements
 * >64= Values greater than 64 are interpreted as 64
 * The Rx FIFO 1 elements are indexed from 0 to F1S - 1

 *
 * Field: ::VTSS_MCAN_RXF1C . F1S
 */
#define  VTSS_F_MCAN_RXF1C_F1S(x)             VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_MCAN_RXF1C_F1S                VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_MCAN_RXF1C_F1S(x)             VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Rx FIFO 1 Start AddressStart address of Rx FIFO 1 in Message RAM (32-bit
 * word address, see Figure 2 in mcan user manual).Access: Read and
 * Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_RXF1C . F1SA
 */
#define  VTSS_F_MCAN_RXF1C_F1SA(x)            VTSS_ENCODE_BITFIELD(x,2,14)
#define  VTSS_M_MCAN_RXF1C_F1SA               VTSS_ENCODE_BITMASK(2,14)
#define  VTSS_X_MCAN_RXF1C_F1SA(x)            VTSS_EXTRACT_BITFIELD(x,2,14)


/**
 * \brief Rx FIFO 1 Status
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:RXF1S
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RXF1S(target)              VTSS_IOREG(target,0x2d)

/**
 * \brief
 * Debug Message StatusAccess: Read
 *
 * \details
 * 00= Idle state, wait for reception of debug messages, DMA request is
 * cleared
 * 01= Debug message A received
 * 10= Debug messages A, B received
 * 11= Debug messages A, B, C received, DMA request is set
 *
 * Field: ::VTSS_MCAN_RXF1S . DMS
 */
#define  VTSS_F_MCAN_RXF1S_DMS(x)             VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_MCAN_RXF1S_DMS                VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_MCAN_RXF1S_DMS(x)             VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * Rx FIFO 1 Message LostThis bit is a copy of interrupt flag IR.RF1L. When
 * IR.RF1L is reset, this bit is also reset.Note: Overwriting the oldest
 * message when RXF1C.F1OM = 1 will not set this flag.Access: Read
 *
 * \details
 * 0= No Rx FIFO 1 message lost
 * 1= Rx FIFO 1 message lost, also set after write attempt to Rx FIFO 1 of
 * size zero
 *
 * Field: ::VTSS_MCAN_RXF1S . RF1L_RXF1S
 */
#define  VTSS_F_MCAN_RXF1S_RF1L_RXF1S(x)      VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_MCAN_RXF1S_RF1L_RXF1S         VTSS_BIT(25)
#define  VTSS_X_MCAN_RXF1S_RF1L_RXF1S(x)      VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Rx FIFO 1 FullAccess: Read
 *
 * \details
 * 0= Rx FIFO 1 not full
 * 1= Rx FIFO 1 full
 *
 * Field: ::VTSS_MCAN_RXF1S . F1F_RXF1S
 */
#define  VTSS_F_MCAN_RXF1S_F1F_RXF1S(x)       VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_MCAN_RXF1S_F1F_RXF1S          VTSS_BIT(24)
#define  VTSS_X_MCAN_RXF1S_F1F_RXF1S(x)       VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Rx FIFO 1 Put IndexRx FIFO 1 write index pointer, range 0 to 63.Access:
 * Read
 *
 * \details
 * Field: ::VTSS_MCAN_RXF1S . F1PI
 */
#define  VTSS_F_MCAN_RXF1S_F1PI(x)            VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_MCAN_RXF1S_F1PI               VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_MCAN_RXF1S_F1PI(x)            VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Rx FIFO 1 Get IndexRx FIFO 1 read index pointer, range 0 to 63.
 *
 * \details
 * Field: ::VTSS_MCAN_RXF1S . F1GI
 */
#define  VTSS_F_MCAN_RXF1S_F1GI(x)            VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_MCAN_RXF1S_F1GI               VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_MCAN_RXF1S_F1GI(x)            VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * Rx FIFO 1 Fill LevelNumber of elements stored in Rx FIFO 1, range 0 to
 * 64.
 *
 * \details
 * Field: ::VTSS_MCAN_RXF1S . F1FL
 */
#define  VTSS_F_MCAN_RXF1S_F1FL(x)            VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_MCAN_RXF1S_F1FL               VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_MCAN_RXF1S_F1FL(x)            VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Rx FIFO 1 Acknowledge
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:RXF1A
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RXF1A(target)              VTSS_IOREG(target,0x2e)

/**
 * \brief
 * Rx FIFO 1 Acknowledge IndexAfter the Host has read a message or a
 * sequence of messages from Rx FIFO 1 it has to write the buffer index of
 * the last element read from Rx FIFO 1 to F1AI. This will set the Rx FIFO
 * 1 Get Index RXF1S.F1GI to F1AI + 1 and update the FIFO 1 Fill Level
 * RXF1S.F1FL
 *
 * \details
 * Field: ::VTSS_MCAN_RXF1A . F1AI
 */
#define  VTSS_F_MCAN_RXF1A_F1AI(x)            VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MCAN_RXF1A_F1AI               VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MCAN_RXF1A_F1AI(x)            VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Rx Buffer / FIFO Element Size Configuration
 *
 * \details
 * Configures the number of data bytes belonging to an Rx Buffer / Rx FIFO
 * element. Data field sizes > 8 bytes are intended for CAN FD operation
 * only.
 *
 * Register: \a MCAN:MCAN_REGS:RXESC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_RXESC(target)              VTSS_IOREG(target,0x2f)

/**
 * \brief
 * Rx Buffer Data Field SizeAccess: Read and Protected Write
 *
 * \details
 * 000= 8 byte data field
 * 001= 12 byte data field
 * 010= 16 byte data field
 * 011= 20 byte data field
 * 100= 24 byte data field
 * 101= 32 byte data field
 * 110= 48 byte data field
 * 111= 64 byte data field
 *
 * Field: ::VTSS_MCAN_RXESC . RBDS
 */
#define  VTSS_F_MCAN_RXESC_RBDS(x)            VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_MCAN_RXESC_RBDS               VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_MCAN_RXESC_RBDS(x)            VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Rx FIFO 1 Data Field SizeAccess: Read and Protected Write
 *
 * \details
 * 000= 8 byte data field
 * 001= 12 byte data field
 * 010= 16 byte data field
 * 011= 20 byte data field
 * 100= 24 byte data field
 * 101= 32 byte data field
 * 110= 48 byte data field
 * 111= 64 byte data field
 *
 * Field: ::VTSS_MCAN_RXESC . F1DS
 */
#define  VTSS_F_MCAN_RXESC_F1DS(x)            VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_MCAN_RXESC_F1DS               VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_MCAN_RXESC_F1DS(x)            VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Rx FIFO 0 Data Field SizeAccess: Read and Protected Write
 *
 * \details
 * 000= 8 byte data field
 * 001= 12 byte data field
 * 010= 16 byte data field
 * 011= 20 byte data field
 * 100= 24 byte data field
 * 101= 32 byte data field
 * 110= 48 byte data field
 * 111= 64 byte data field
 *
 * Field: ::VTSS_MCAN_RXESC . F0DS
 */
#define  VTSS_F_MCAN_RXESC_F0DS(x)            VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_MCAN_RXESC_F0DS               VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_MCAN_RXESC_F0DS(x)            VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Tx Buffer Configuration
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXBC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXBC(target)               VTSS_IOREG(target,0x30)

/**
 * \brief
 * Tx FIFO/Queue ModeAccess: Read and Protected Write
 *
 * \details
 * 0= Tx FIFO operation
 * 1= Tx Queue operation
 *
 * Field: ::VTSS_MCAN_TXBC . TFQM
 */
#define  VTSS_F_MCAN_TXBC_TFQM(x)             VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_MCAN_TXBC_TFQM                VTSS_BIT(30)
#define  VTSS_X_MCAN_TXBC_TFQM(x)             VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Transmit FIFO/Queue SizeAccess: Read and Protected Write
 *
 * \details
 * 0= No Tx FIFO/Queue
 * 1-32= Number of Tx Buffers used for Tx FIFO/Queue
 * >32= Values greater than 32 are interpreted as 32
 *
 * Field: ::VTSS_MCAN_TXBC . TFQS
 */
#define  VTSS_F_MCAN_TXBC_TFQS(x)             VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_MCAN_TXBC_TFQS                VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_MCAN_TXBC_TFQS(x)             VTSS_EXTRACT_BITFIELD(x,24,6)

/**
 * \brief
 * Number of Dedicated Transmit BuffersAccess: Read and Protected Write
 *
 * \details
 * 0= No Dedicated Tx Buffers
 * 1-32= Number of Dedicated Tx Buffers
 * >32= Values greater than 32 are interpreted as 32
 *
 * Field: ::VTSS_MCAN_TXBC . NDTB
 */
#define  VTSS_F_MCAN_TXBC_NDTB(x)             VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_MCAN_TXBC_NDTB                VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_MCAN_TXBC_NDTB(x)             VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Tx Buffers Start AddressStart address of Tx Buffers section in Message
 * RAM (32-bit word address, see Figure 2).Note: Be aware that the sum of
 * TFQS and NDTB may be not greater thatn 32. There is no check for
 * erroneous configurations. The  Tx Buffers section iin the Message RAM
 * starts with the dedicated Tx Buffers.Access: Read and Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_TXBC . TBSA
 */
#define  VTSS_F_MCAN_TXBC_TBSA(x)             VTSS_ENCODE_BITFIELD(x,2,14)
#define  VTSS_M_MCAN_TXBC_TBSA                VTSS_ENCODE_BITMASK(2,14)
#define  VTSS_X_MCAN_TXBC_TBSA(x)             VTSS_EXTRACT_BITFIELD(x,2,14)


/**
 * \brief Tx FIFO/Queue Status
 *
 * \details
 * The Tx FIFO/Queue status is related to the pending Tx requests listed in
 * register TXBRP. Therefore
 * the effect of Add/Cancellation requests may be delayed due to a running
 * Tx scan (TXBRP not yet
 * updated).
 *
 * Register: \a MCAN:MCAN_REGS:TXFQS
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXFQS(target)              VTSS_IOREG(target,0x31)

/**
 * \brief
 * Tx FIFO/Queue FullAccess: Read
 *
 * \details
 * 0= Tx FIFO/Queue not full
 * 1= Tx FIFO/Queue full
 *
 * Field: ::VTSS_MCAN_TXFQS . TFQF
 */
#define  VTSS_F_MCAN_TXFQS_TFQF(x)            VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_MCAN_TXFQS_TFQF               VTSS_BIT(21)
#define  VTSS_X_MCAN_TXFQS_TFQF(x)            VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Tx FIFO/Queue Put IndexTx FIFO/Queue write index pointer, range 0 to
 * 31.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_TXFQS . TFQPI
 */
#define  VTSS_F_MCAN_TXFQS_TFQPI(x)           VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_MCAN_TXFQS_TFQPI              VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_MCAN_TXFQS_TFQPI(x)           VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 * Tx FIFO Get IndexTx FIFO read index pointer, range 0 to 31. Read as zero
 * when Tx Queue operation is configured (TXBC.TFQM = 1).Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_TXFQS . TFGI
 */
#define  VTSS_F_MCAN_TXFQS_TFGI(x)            VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_MCAN_TXFQS_TFGI               VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_MCAN_TXFQS_TFGI(x)            VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Tx FIFO Free LevelNumber of consecutive free Tx FIFO elements starting
 * from TFGI, range 0 to 32. Read as zero when Tx Queue operation is
 * configured (TXBC.TFQM = 1)Note: In case of mixed configurations where
 * dedicated Tx Buffers are combined with a Tx FIFO or a Tx Queue, the Put
 * and Get Indices indicate the number of the Tx Buffer starting with the
 * first dedicated Tx Buffers. Example: For a configuration of 12 dedicated
 * Tx Buffers and a Tx FIFO of 20 Buffers a Put Index of 15 points to the
 * fourth buffer of the Tx FIFO.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_TXFQS . TFFL
 */
#define  VTSS_F_MCAN_TXFQS_TFFL(x)            VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MCAN_TXFQS_TFFL               VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MCAN_TXFQS_TFFL(x)            VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Tx Buffer Element Size Configuration
 *
 * \details
 * Configures the number of data bytes belonging to a Tx Buffer element.
 * Data field sizes > 8 bytes are
 * intended for CAN FD operation only.
 *
 * Register: \a MCAN:MCAN_REGS:TXESC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXESC(target)              VTSS_IOREG(target,0x32)

/**
 * \brief
 * Tx Buffer Data Field SizeNote: In case the data length code DLC of a Tx
 * Buffer element is configured to a value higher than the Tx Buffer data
 * field size TXESC.TBDS, the bytes not defined by the Tx Buffer are
 * transmitted as 0xCC (padding bytes).Access: Read and Protected Write
 *
 * \details
 * 000= 8 byte data field
 * 001= 12 byte data field
 * 010= 16 byte data field
 * 011= 20 byte data field
 * 100= 24 byte data field
 * 101= 32 byte data field
 * 110= 48 byte data field
 * 111= 64 byte data field
 *
 * Field: ::VTSS_MCAN_TXESC . TBDS
 */
#define  VTSS_F_MCAN_TXESC_TBDS(x)            VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_MCAN_TXESC_TBDS               VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_MCAN_TXESC_TBDS(x)            VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Tx Buffer Request Pending
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXBRP
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXBRP(target)              VTSS_IOREG(target,0x33)

/**
 * \brief
 * Transmission Request PendingEach Tx Buffer has its own Transmission
 * Request Pending bit. The bits are set via register TXBAR. The bits are
 * reset after a requested transmission has completed or has been cancelled
 * via register TXBCR.TXBRP bits are set only for those Tx Buffers
 * configured via TXBC. After a TXBRP bit has been set,a Tx scan (see
 * Section 3.5, Tx Handling) is started to check for the pending Tx request
 * with thehighest priority (Tx Buffer with lowest Message
 * ID).Acancellation request resets the corresponding transmission request
 * pending bit of registerTXBRP. In case a transmission has already been
 * started when a cancellation is requested, this isdone at the end of the
 * transmission, regardless whether the transmission was successful or not.
 * Thecancellation request bits are reset directly after the corresponding
 * TXBRP bit has been reset.After a cancellation has been requested, a
 * finished cancellation is signaled via TXBCFafter successful transmission
 * together with the corresponding TXBTO bitwhen the transmission has not
 * yet been started at the point of cancellationwhen the transmission has
 * been aborted due to lost arbitrationwhen an error occurred during frame
 * transmissionIn DAR mode all transmissions are automatically cancelled if
 * they are not successful. Thecorresponding TXBCF bit is set for all
 * unsuccessful transmissions.Note: TXBRP bits which are set while a Tx
 * scan is in progress are not considered during thisparticular Tx scan. In
 * case a cancellation is requested for such a Tx Buffer, this AddRequest
 * is cancelled immediately, the corresponding TXBRP bit is reset.Access:
 * Read
 *
 * \details
 * 0= No transmission request pending
 * 1= Transmission request pending
 *
 * Field: ::VTSS_MCAN_TXBRP . TRP
 */
#define  VTSS_F_MCAN_TXBRP_TRP(x)             (x)
#define  VTSS_M_MCAN_TXBRP_TRP                0xffffffff
#define  VTSS_X_MCAN_TXBRP_TRP(x)             (x)


/**
 * \brief Tx Buffer Add Request
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXBAR
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXBAR(target)              VTSS_IOREG(target,0x34)

/**
 * \brief
 * Add RequestEach Tx Buffer has its own Add Request bit. Writing a 1 will
 * set the corresponding Add Requestbit; writing a 0 has no impact. This
 * enables the Host to set transmission requests for multiple TxBuffers
 * with one write to TXBAR. TXBAR bits are set only for those Tx Buffers
 * configured via TXBC.When no Tx scan is running, the bits are reset
 * immediately, else the bits remain set until the Tx scanprocess has
 * completed.Note: If an add request is applied for a Tx Buffer with
 * pending transmission request (correspondingTXBRP bit already set), this
 * add request is ignored.Access: Read and Write
 *
 * \details
 * 0= No transmission request added
 * 1= Transmission requested added
 *
 * Field: ::VTSS_MCAN_TXBAR . AR
 */
#define  VTSS_F_MCAN_TXBAR_AR(x)              (x)
#define  VTSS_M_MCAN_TXBAR_AR                 0xffffffff
#define  VTSS_X_MCAN_TXBAR_AR(x)              (x)


/**
 * \brief Tx Buffer Cancellation Request
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXBCR
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXBCR(target)              VTSS_IOREG(target,0x35)

/**
 * \brief
 * Cancellation RequestEach Tx Buffer has its own Cancellation Request bit.
 * Writing a 1 will set the correspondingCancellation Request bit; writing
 * a 0 has no impact. This enables the Host to set cancellationrequests for
 * multiple Tx Buffers with one write to TXBCR. TXBCR bits are set only for
 * those TxBuffers configured via TXBC. The bits remain set until the
 * corresponding bit of TXBRP is reset.Access: Read and Write
 *
 * \details
 * 0= No cancellation pending
 * 1= Cancellation pending
 *
 * Field: ::VTSS_MCAN_TXBCR . CR
 */
#define  VTSS_F_MCAN_TXBCR_CR(x)              (x)
#define  VTSS_M_MCAN_TXBCR_CR                 0xffffffff
#define  VTSS_X_MCAN_TXBCR_CR(x)              (x)


/**
 * \brief Tx Buffer Transmission Occurred
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXBTO
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXBTO(target)              VTSS_IOREG(target,0x36)

/**
 * \brief
 * Transmission OccurredEach Tx Buffer has its own Transmission Occurred
 * bit. The bits are set when the correspondingTXBRP bit is cleared after a
 * successful transmission. The bits are reset when a new transmissionis
 * requested by writing a 1 to the corresponding bit of register
 * TXBARAccess: Read.
 *
 * \details
 * 0= No transmission occurred
 * 1= Transmission occurred
 *
 * Field: ::VTSS_MCAN_TXBTO . TO
 */
#define  VTSS_F_MCAN_TXBTO_TO(x)              (x)
#define  VTSS_M_MCAN_TXBTO_TO                 0xffffffff
#define  VTSS_X_MCAN_TXBTO_TO(x)              (x)


/**
 * \brief Tx Buffer Cancellation Finished
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXBCF
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXBCF(target)              VTSS_IOREG(target,0x37)

/**
 * \brief
 * Cancellation FinishedEach Tx Buffer has its own Cancellation Finished
 * bit. The bits are set when the correspondingTXBRP bit is cleared after a
 * cancellation was requested via TXBCR. In case the correspondingTXBRP bit
 * was not set at the point of cancellation, CF is set immediately. The
 * bits are reset when anew transmission is requested by writing a 1 to the
 * corresponding bit of register TXBAR.Access: Read
 *
 * \details
 * 0= No transmit buffer cancellation
 * 1= Transmit buffer cancellation finished
 *
 * Field: ::VTSS_MCAN_TXBCF . CF
 */
#define  VTSS_F_MCAN_TXBCF_CF(x)              (x)
#define  VTSS_M_MCAN_TXBCF_CF                 0xffffffff
#define  VTSS_X_MCAN_TXBCF_CF(x)              (x)


/**
 * \brief Tx Buffer Transmission Interrupt Enable
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXBTIE
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXBTIE(target)             VTSS_IOREG(target,0x38)

/**
 * \brief
 * Each Tx Buffer has its own Transmission Interrupt Enable bit.Access:
 * Read and Write
 *
 * \details
 * 0= Transmission interrupt disabled
 * 1= Transmission interrupt enable
 *
 * Field: ::VTSS_MCAN_TXBTIE . TIE
 */
#define  VTSS_F_MCAN_TXBTIE_TIE(x)            (x)
#define  VTSS_M_MCAN_TXBTIE_TIE               0xffffffff
#define  VTSS_X_MCAN_TXBTIE_TIE(x)            (x)


/**
 * \brief Tx Buffer Cancellation Finished Interrupt Enable
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXBCIE
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXBCIE(target)             VTSS_IOREG(target,0x39)

/**
 * \brief
 * Cancellation Finished Interrupt EnableEach Tx Buffer has its own
 * Cancellation Finished Interrupt Enable bit.Access: Read and Write
 *
 * \details
 * 0= Cancellation finished interrupt disabled
 * 1= Cancellation finished interrupt enabled
 *
 * Field: ::VTSS_MCAN_TXBCIE . CFIE
 */
#define  VTSS_F_MCAN_TXBCIE_CFIE(x)           (x)
#define  VTSS_M_MCAN_TXBCIE_CFIE              0xffffffff
#define  VTSS_X_MCAN_TXBCIE_CFIE(x)           (x)


/**
 * \brief Tx Event FIFO Configuration
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXEFC
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXEFC(target)              VTSS_IOREG(target,0x3c)

/**
 * \brief
 * Event FIFO WatermarkAccess: Read and Protected Write
 *
 * \details
 * 0= Watermark interrupt disabled
 * 1-32= Level for Tx Event FIFO watermark interrupt (IR.TEFW)
 * >32= Watermark interrupt disabled
 *
 * Field: ::VTSS_MCAN_TXEFC . EFWM
 */
#define  VTSS_F_MCAN_TXEFC_EFWM(x)            VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_MCAN_TXEFC_EFWM               VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_MCAN_TXEFC_EFWM(x)            VTSS_EXTRACT_BITFIELD(x,24,6)

/**
 * \brief
 * Event FIFO Size0= Tx Event FIFO disabled1-32= Number of Tx Event FIFO
 * elements>32= Values greater than 32 are interpreted as 32The Tx Event
 * FIFO elements are indexed from 0 to EFS - 1Access: Read and Protected
 * Write
 *
 * \details
 * Field: ::VTSS_MCAN_TXEFC . EFS
 */
#define  VTSS_F_MCAN_TXEFC_EFS(x)             VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_MCAN_TXEFC_EFS                VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_MCAN_TXEFC_EFS(x)             VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Event FIFO Start AddressStart address of Tx Event FIFO in Message RAM
 * (32-bit word address, see Figure 2 in mcan user manual).Access: Read and
 * Protected Write
 *
 * \details
 * Field: ::VTSS_MCAN_TXEFC . EFSA
 */
#define  VTSS_F_MCAN_TXEFC_EFSA(x)            VTSS_ENCODE_BITFIELD(x,2,14)
#define  VTSS_M_MCAN_TXEFC_EFSA               VTSS_ENCODE_BITMASK(2,14)
#define  VTSS_X_MCAN_TXEFC_EFSA(x)            VTSS_EXTRACT_BITFIELD(x,2,14)


/**
 * \brief Tx Event FIFO Status
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXEFS
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXEFS(target)              VTSS_IOREG(target,0x3d)

/**
 * \brief
 * Tx Event FIFO Element LostThis bit is a copy of interrupt flag IR.TEFL.
 * When IR.TEFL is reset, this bit is also reset.Access: Read
 *
 * \details
 * 0= No Tx Event FIFO element lost
 * 1= Tx Event FIFO element lost, also set after write attempt to Tx Event
 * FIFO of size zero.
 *
 * Field: ::VTSS_MCAN_TXEFS . TEFL_TXEFS
 */
#define  VTSS_F_MCAN_TXEFS_TEFL_TXEFS(x)      VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_MCAN_TXEFS_TEFL_TXEFS         VTSS_BIT(25)
#define  VTSS_X_MCAN_TXEFS_TEFL_TXEFS(x)      VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Event FIFO FullAccess: Read
 *
 * \details
 * 0= Tx Event FIFO not full
 * 1= Tx Event FIFO full
 *
 * Field: ::VTSS_MCAN_TXEFS . EFF
 */
#define  VTSS_F_MCAN_TXEFS_EFF(x)             VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_MCAN_TXEFS_EFF                VTSS_BIT(24)
#define  VTSS_X_MCAN_TXEFS_EFF(x)             VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Event FIFO Put IndexTx Event FIFO write index pointer, range 0 to
 * 31.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_TXEFS . EFPI
 */
#define  VTSS_F_MCAN_TXEFS_EFPI(x)            VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_MCAN_TXEFS_EFPI               VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_MCAN_TXEFS_EFPI(x)            VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 * Event FIFO Get IndexTx Event FIFO read index pointer, range 0 to
 * 31.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_TXEFS . EFGI
 */
#define  VTSS_F_MCAN_TXEFS_EFGI(x)            VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_MCAN_TXEFS_EFGI               VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_MCAN_TXEFS_EFGI(x)            VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Event FIFO Fill LevelNumber of elements stored in Tx Event FIFO, range 0
 * to 32.Access: Read
 *
 * \details
 * Field: ::VTSS_MCAN_TXEFS . EFFL
 */
#define  VTSS_F_MCAN_TXEFS_EFFL(x)            VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_MCAN_TXEFS_EFFL               VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_MCAN_TXEFS_EFFL(x)            VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Tx Event FIFO Acknowledge
 *
 * \details
 * Register: \a MCAN:MCAN_REGS:TXEFA
 *
 * @param target A \a ::vtss_target_MCAN_e target
 */
#define VTSS_MCAN_TXEFA(target)              VTSS_IOREG(target,0x3e)

/**
 * \brief
 * Event FIFO Acknowledge IndexAfter the Host has read an element or a
 * sequence of elements from the Tx Event FIFO it has to writethe index of
 * the last element read from Tx Event FIFO to EFAI. This will set the Tx
 * Event FIFO GetIndex TXEFS.EFGI to EFAI + 1 and update the Event FIFO
 * Fill Level TXEFS.EFFL.Access: Read and Write
 *
 * \details
 * Field: ::VTSS_MCAN_TXEFA . EFAI
 */
#define  VTSS_F_MCAN_TXEFA_EFAI(x)            VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_MCAN_TXEFA_EFAI               VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_MCAN_TXEFA_EFAI(x)            VTSS_EXTRACT_BITFIELD(x,0,5)


#endif /* _VTSS_LAGUNA_REGS_MCAN_H_ */
