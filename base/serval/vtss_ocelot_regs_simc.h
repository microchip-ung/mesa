// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_OCELOT_REGS_SIMC_H_
#define _VTSS_OCELOT_REGS_SIMC_H_


#include "vtss_ocelot_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a SIMC
 *
 * SI Master Controller
 *
 ***********************************************************************/

/**
 * Register Group: \a SIMC:SIMC
 *
 * SI Master Controller
 */


/** 
 * \brief Control Register 0
 *
 * \details
 * This register controls the serial data transfer. This register can only
 * be written when master is disabled (SIMC::SIMCEN.SIMCEN = 0).
 *
 * Register: \a SIMC:SIMC:CTRLR0
 */
#define VTSS_SIMC_SIMC_CTRLR0                VTSS_IOREG(VTSS_TO_SIMC,0x0)

/** 
 * \brief
 * Control Frame Size. Selects the length of the control word for the
 * Microwire frame format.
 *
 * \details 
 * n: n+1 bit control word.
 *
 * Field: ::VTSS_SIMC_SIMC_CTRLR0 . CFS
 */
#define  VTSS_F_SIMC_SIMC_CTRLR0_CFS(x)       VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_SIMC_SIMC_CTRLR0_CFS          VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_SIMC_SIMC_CTRLR0_CFS(x)       VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Shift Register Loop. Used for testing purposes only. Set to connect the
 * transmit shift register output to the receive shift register input.
 *
 * \details 
 * 0: Normal Mode Operation
 * 1: Test Mode Operation
 *
 * Field: ::VTSS_SIMC_SIMC_CTRLR0 . SRL
 */
#define  VTSS_F_SIMC_SIMC_CTRLR0_SRL          VTSS_BIT(11)

/** 
 * \brief
 * Selects the mode of transfer for serial communication. In transmit-only
 * mode, data received from the external device is not valid and is not
 * stored in the receive FIFO memory; it is overwritten on the next
 * transfer. In receive-only mode, transmitted data are not valid. After
 * the first write to the transmit FIFO, the same word is retransmitted for
 * the duration of the transfer. In transmit-and-receive mode, both
 * transmit and receive data are valid. The transfer continues until the
 * transmit FIFO is empty. Data received from the external device are
 * stored into the receive FIFO memory, where it can be accessed by the
 * host processor.
 *
 * \details 
 * 0: Transmit and Receive.
 * 1: Transmit Only.
 * 2: Receive Only.
 * 3: Reserved.
 *
 * Field: ::VTSS_SIMC_SIMC_CTRLR0 . TMOD
 */
#define  VTSS_F_SIMC_SIMC_CTRLR0_TMOD(x)      VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_SIMC_SIMC_CTRLR0_TMOD         VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_SIMC_SIMC_CTRLR0_TMOD(x)      VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Valid when the frame format (FRF) is set to Motorola SPI. Used to select
 * the polarity of the inactive serial clock, which is held inactive when
 * the master is not actively transferring data on the serial bus.
 *
 * \details 
 * 0: Inactive state of serial clock is low.
 * 1: Inactive state of serial clock is high.
 *
 * Field: ::VTSS_SIMC_SIMC_CTRLR0 . SCPOL
 */
#define  VTSS_F_SIMC_SIMC_CTRLR0_SCPOL        VTSS_BIT(7)

/** 
 * \brief
 * Valid when the frame format (FRF) is set to Motorola SPI. The serial
 * clock phase selects the relationship of the serial clock with the slave
 * select signal. When SCPH = 0, data are captured on the first edge of the
 * serial clock. When SCPH = 1, the serial clock starts toggling one cycle
 * after the slave select line is activated, and data are captured on the
 * second edge of the serial clock.
 *
 * \details 
 * 0: Serial clock toggles in middle of first data bit.
 * 1: Serial clock toggles at start of first data bit.
 *
 * Field: ::VTSS_SIMC_SIMC_CTRLR0 . SCPH
 */
#define  VTSS_F_SIMC_SIMC_CTRLR0_SCPH         VTSS_BIT(6)

/** 
 * \brief
 * Selects which serial protocol transfers the data.
 * Note: In addition to this field, software must also configure
 * ICPU_CFG::GENERAL_CTRL.SIMC_SSP_ENA.
 *
 * \details 
 * 0: Motorola SPI
 * 1: Texas Instruments SSP
 * 2-3: Reserved
 *
 * Field: ::VTSS_SIMC_SIMC_CTRLR0 . FRF
 */
#define  VTSS_F_SIMC_SIMC_CTRLR0_FRF(x)       VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SIMC_SIMC_CTRLR0_FRF          VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SIMC_SIMC_CTRLR0_FRF(x)       VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Selects the data frame length. See SIMC::DR register description for how
 * to read/write words of less than 16 bit.
 *
 * \details 
 * 0-2: Reserved.
 * n: n+1 bit serial data transfer.
 *
 * Field: ::VTSS_SIMC_SIMC_CTRLR0 . DFS
 */
#define  VTSS_F_SIMC_SIMC_CTRLR0_DFS(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SIMC_SIMC_CTRLR0_DFS          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SIMC_SIMC_CTRLR0_DFS(x)       VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Control Register 1
 *
 * \details
 * Control register 1 controls the end of serial transfers when in
 * receive-only mode. This register can only be written when master is
 * disabled (SIMC::SIMCEN.SIMCEN = 0).
 *
 * Register: \a SIMC:SIMC:CTRLR1
 */
#define VTSS_SIMC_SIMC_CTRLR1                VTSS_IOREG(VTSS_TO_SIMC,0x1)

/** 
 * \brief
 * When SIMC::CTRLR0.TMOD = 2, this register field sets the number of data
 * frames to be continuously received by the master. The master continues
 * to receive serial data until the number of data frames received is equal
 * to this register value plus 1, which enables receiving up to 64 KB of
 * data in a continuous transfer.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_CTRLR1 . NDF
 */
#define  VTSS_F_SIMC_SIMC_CTRLR1_NDF(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SIMC_SIMC_CTRLR1_NDF          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SIMC_SIMC_CTRLR1_NDF(x)       VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SIMC Enable
 *
 * \details
 * Register: \a SIMC:SIMC:SIMCEN
 */
#define VTSS_SIMC_SIMC_SIMCEN                VTSS_IOREG(VTSS_TO_SIMC,0x2)

/** 
 * \brief
 * Set to enable master operations. When disabled, all serial transfers are
 * halted immediately. Transmit and receive FIFO buffers are cleared when
 * disabled. It is impossible to program some of the master control
 * registers when enabled.
 * Note: The SI Master Controller must own the SI interface before it is
 * enabled, see ICPU_CFG::GENERAL_CTRL.IF_SI_OWNER for more information. 
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_SIMCEN . SIMCEN
 */
#define  VTSS_F_SIMC_SIMC_SIMCEN_SIMCEN       VTSS_BIT(0)


/** 
 * \brief Microwire Control Register
 *
 * \details
 * This register controls the direction of the data word for the
 * half-duplex Microwire serial protocol. This register can only be written
 * when master is disabled (SIMC::SIMCEN.SIMCEN = 0).
 *
 * Register: \a SIMC:SIMC:MWCR
 */
#define VTSS_SIMC_SIMC_MWCR                  VTSS_IOREG(VTSS_TO_SIMC,0x3)

/** 
 * \brief
 * Set to enable the busy/ready handshaking interface for the Microwire
 * protocol. When enabled, the master checks for a ready status from the
 * target slave, after the transfer of the last data/control bit, before
 * clearing the BUSY status in the SR register.
 *
 * \details 
 * 0: handshaking interface is disabled
 * 1: handshaking interface is enabled
 *
 * Field: ::VTSS_SIMC_SIMC_MWCR . MHS
 */
#define  VTSS_F_SIMC_SIMC_MWCR_MHS            VTSS_BIT(2)

/** 
 * \brief
 * Defines the direction of the data word when the Microwire serial
 * protocol is used. When this bit is set to 0, the data word is received
 * by the master from the external serial device. When this bit is set to
 * 1, the data word is transmitted from the master to the external serial
 * device.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_MWCR . MDD
 */
#define  VTSS_F_SIMC_SIMC_MWCR_MDD            VTSS_BIT(1)

/** 
 * \brief
 * Defines whether the Microwire transfer is sequential or non-sequential.
 * When sequential mode is used, only one control word is needed to
 * transmit or receive a block of data words. When non-sequential mode is
 * used, there must be a control word for each data word that is
 * transmitted or received.
 *
 * \details 
 * 0: non-sequential transfer
 * 1: sequential transfer
 *
 * Field: ::VTSS_SIMC_SIMC_MWCR . MWMOD
 */
#define  VTSS_F_SIMC_SIMC_MWCR_MWMOD          VTSS_BIT(0)


/** 
 * \brief Slave Enable
 *
 * \details
 * The register enables the individual slave select output lines from the
 * master. 16 slave-select output pins are available on the master. This
 * register can only be written when master is disabled and not busy.
 *
 * Register: \a SIMC:SIMC:SER
 */
#define VTSS_SIMC_SIMC_SER                   VTSS_IOREG(VTSS_TO_SIMC,0x4)

/** 
 * \brief
 * Each bit in this register corresponds to a slave select line from the
 * master. When a bit in this register is set, the corresponding slave
 * select line from the master is activated when a serial transfer begins.
 * Setting or clearing bits in this register have no effect on the
 * corresponding slave select outputs until a transfer is started. Before
 * beginning a transfer, enable the bit in this register that corresponds
 * to the slave device with which the master wants to communicate. When not
 * operating in broadcast mode, only one bit in this field should be set.
 *
 * \details 
 * 1: Selected
 * 0: Not Selected
 *
 * Field: ::VTSS_SIMC_SIMC_SER . SER
 */
#define  VTSS_F_SIMC_SIMC_SER_SER(x)          VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SIMC_SIMC_SER_SER             VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SIMC_SIMC_SER_SER(x)          VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Baud Rate Select
 *
 * \details
 * The register derives the frequency of the serial clock that regulates
 * the data transfer. The 16-bit field in this register defines the SI
 * divider value. This register can only be written when master is disabled
 * (SIMC::SIMCEN.SIMCEN = 0).
 *
 * Register: \a SIMC:SIMC:BAUDR
 */
#define VTSS_SIMC_SIMC_BAUDR                 VTSS_IOREG(VTSS_TO_SIMC,0x5)

/** 
 * \brief
 * The LSB for this field is always set to 0 and is unaffected by a write
 * operation, which ensures an even value is held in this register. If the
 * value is 0, the serial output clock (si_clk) is disabled. The frequency
 * of the si_clk is derived from the following equation: Fsclk_out =
 * Fsystem_clk/SCKDV where SCKDV is any even value between 2 and 65534 and
 * Fsystem_clk is 250MHz.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_BAUDR . SCKDV
 */
#define  VTSS_F_SIMC_SIMC_BAUDR_SCKDV(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SIMC_SIMC_BAUDR_SCKDV         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SIMC_SIMC_BAUDR_SCKDV(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Transmit FIFO Threshold Level
 *
 * \details
 * Register: \a SIMC:SIMC:TXFTLR
 */
#define VTSS_SIMC_SIMC_TXFTLR                VTSS_IOREG(VTSS_TO_SIMC,0x6)

/** 
 * \brief
 * When the number of transmit FIFO entries is less than or equal to this
 * value, the transmit FIFO empty interrupt is triggered. The transmit FIFO
 * depth is 8, do not program value exceeding 7.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_TXFTLR . TFT
 */
#define  VTSS_F_SIMC_SIMC_TXFTLR_TFT(x)       VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SIMC_SIMC_TXFTLR_TFT          VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SIMC_SIMC_TXFTLR_TFT(x)       VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Receive FIFO Threshold level
 *
 * \details
 * Register: \a SIMC:SIMC:RXFTLR
 */
#define VTSS_SIMC_SIMC_RXFTLR                VTSS_IOREG(VTSS_TO_SIMC,0x7)

/** 
 * \brief
 * When the number of receive FIFO entries is greater than or equal to this
 * value + 1, the receive FIFO full interrupt is triggered. The receive
 * FIFO depth is 40, do not program value exceeding 39. 
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RXFTLR . RFT
 */
#define  VTSS_F_SIMC_SIMC_RXFTLR_RFT(x)       VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SIMC_SIMC_RXFTLR_RFT          VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SIMC_SIMC_RXFTLR_RFT(x)       VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Transmit FIFO Level
 *
 * \details
 * Register: \a SIMC:SIMC:TXFLR
 */
#define VTSS_SIMC_SIMC_TXFLR                 VTSS_IOREG(VTSS_TO_SIMC,0x8)

/** 
 * \brief
 * Contains the number of valid data entries in the transmit FIFO.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_TXFLR . TXTFL
 */
#define  VTSS_F_SIMC_SIMC_TXFLR_TXTFL(x)      VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SIMC_SIMC_TXFLR_TXTFL         VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SIMC_SIMC_TXFLR_TXTFL(x)      VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Receive FIFO Level
 *
 * \details
 * Register: \a SIMC:SIMC:RXFLR
 */
#define VTSS_SIMC_SIMC_RXFLR                 VTSS_IOREG(VTSS_TO_SIMC,0x9)

/** 
 * \brief
 * Contains the number of valid data entries in the receive FIFO.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RXFLR . RXTFL
 */
#define  VTSS_F_SIMC_SIMC_RXFLR_RXTFL(x)      VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SIMC_SIMC_RXFLR_RXTFL         VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SIMC_SIMC_RXFLR_RXTFL(x)      VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Status Register
 *
 * \details
 * Register: \a SIMC:SIMC:SR
 */
#define VTSS_SIMC_SIMC_SR                    VTSS_IOREG(VTSS_TO_SIMC,0xa)

/** 
 * \brief
 * Set when receive FIFO is full.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_SR . RFF
 */
#define  VTSS_F_SIMC_SIMC_SR_RFF              VTSS_BIT(4)

/** 
 * \brief
 * Set when receive FIFO has one or more data-word.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_SR . RFNE
 */
#define  VTSS_F_SIMC_SIMC_SR_RFNE             VTSS_BIT(3)

/** 
 * \brief
 * Set when transmit FIFO is empty.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_SR . TFE
 */
#define  VTSS_F_SIMC_SIMC_SR_TFE              VTSS_BIT(2)

/** 
 * \brief
 * Set when transmit FIFO has room for one or more data-word.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_SR . TFNF
 */
#define  VTSS_F_SIMC_SIMC_SR_TFNF             VTSS_BIT(1)

/** 
 * \brief
 * Set when serial transfer is in progress. Cleared when master is idle or
 * disabled.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_SR . BUSY
 */
#define  VTSS_F_SIMC_SIMC_SR_BUSY             VTSS_BIT(0)


/** 
 * \brief Interrupt Mask
 *
 * \details
 * Register: \a SIMC:SIMC:IMR
 */
#define VTSS_SIMC_SIMC_IMR                   VTSS_IOREG(VTSS_TO_SIMC,0xb)

/** 
 * \brief
 * Set to enable Multi-Master Contention Interrupt
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_IMR . MSTIM
 */
#define  VTSS_F_SIMC_SIMC_IMR_MSTIM           VTSS_BIT(5)

/** 
 * \brief
 * Set to enable Receive FIFO Full Interrupt
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_IMR . RXFIM
 */
#define  VTSS_F_SIMC_SIMC_IMR_RXFIM           VTSS_BIT(4)

/** 
 * \brief
 * Set to enable Receive FIFO Overflow Interrupt
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_IMR . RXOIM
 */
#define  VTSS_F_SIMC_SIMC_IMR_RXOIM           VTSS_BIT(3)

/** 
 * \brief
 * Set to enable Receive FIFO Underflow Interrupt
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_IMR . RXUIM
 */
#define  VTSS_F_SIMC_SIMC_IMR_RXUIM           VTSS_BIT(2)

/** 
 * \brief
 * Set to enable Transmit FIFO Overflow Interrupt
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_IMR . TXOIM
 */
#define  VTSS_F_SIMC_SIMC_IMR_TXOIM           VTSS_BIT(1)

/** 
 * \brief
 * Set to enable Transmit FIFO Empty Interrupt
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_IMR . TXEIM
 */
#define  VTSS_F_SIMC_SIMC_IMR_TXEIM           VTSS_BIT(0)


/** 
 * \brief Interrupt Status
 *
 * \details
 * If any bit is set in this register, then the SI Master Controller is
 * indicating interrupt towards the VCore Interrupt Controller.
 *
 * Register: \a SIMC:SIMC:ISR
 */
#define VTSS_SIMC_SIMC_ISR                   VTSS_IOREG(VTSS_TO_SIMC,0xc)

/** 
 * \brief
 * Multi-Master Contention Interrupt Status, this field is masked by
 * SIMC::IMR.MSTIM.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_ISR . MSTIS
 */
#define  VTSS_F_SIMC_SIMC_ISR_MSTIS           VTSS_BIT(5)

/** 
 * \brief
 * Receive FIFO Full Interrupt Status, this field is masked by
 * SIMC::IMR.RXFIM. This interrupt is based on programmable fill level, see
 * SIMC::RXFTLR for more information.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_ISR . RXFIS
 */
#define  VTSS_F_SIMC_SIMC_ISR_RXFIS           VTSS_BIT(4)

/** 
 * \brief
 * Receive FIFO Overflow Interrupt Status, this field is masked by
 * SIMC::IMR.RXOIM.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_ISR . RXOIS
 */
#define  VTSS_F_SIMC_SIMC_ISR_RXOIS           VTSS_BIT(3)

/** 
 * \brief
 * Receive FIFO Underflow Interrupt Status, this field is masked by
 * SIMC::IMR.RXUIM.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_ISR . RXUIS
 */
#define  VTSS_F_SIMC_SIMC_ISR_RXUIS           VTSS_BIT(2)

/** 
 * \brief
 * Transmit FIFO Overflow Interrupt Status, this field is masked by
 * SIMC::IMR.TXOIM.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_ISR . TXOIS
 */
#define  VTSS_F_SIMC_SIMC_ISR_TXOIS           VTSS_BIT(1)

/** 
 * \brief
 * Transmit FIFO Empty Interrupt Status, this field is masked by
 * SIMC::IMR.TXEIM. This interrupt is based on programmable fill level, see
 * SIMC::TXFTLR for more information.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_ISR . TXEIS
 */
#define  VTSS_F_SIMC_SIMC_ISR_TXEIS           VTSS_BIT(0)


/** 
 * \brief Raw Interrupt Status
 *
 * \details
 * Register: \a SIMC:SIMC:RISR
 */
#define VTSS_SIMC_SIMC_RISR                  VTSS_IOREG(VTSS_TO_SIMC,0xd)

/** 
 * \brief
 * Current status of Multi-Master Contention Interrupt before masking.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RISR . MSTIR
 */
#define  VTSS_F_SIMC_SIMC_RISR_MSTIR          VTSS_BIT(5)

/** 
 * \brief
 * Current status of Receive FIFO Full Interrupt before masking
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RISR . RXFIR
 */
#define  VTSS_F_SIMC_SIMC_RISR_RXFIR          VTSS_BIT(4)

/** 
 * \brief
 * Current status of Receive FIFO Overflow Interrupt before masking
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RISR . RXOIR
 */
#define  VTSS_F_SIMC_SIMC_RISR_RXOIR          VTSS_BIT(3)

/** 
 * \brief
 * Current status of Receive FIFO Underflow Interrupt before masking
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RISR . RXUIR
 */
#define  VTSS_F_SIMC_SIMC_RISR_RXUIR          VTSS_BIT(2)

/** 
 * \brief
 * Current status of Transmit FIFO Overflow Interrupt before masking
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RISR . TXOIR
 */
#define  VTSS_F_SIMC_SIMC_RISR_TXOIR          VTSS_BIT(1)

/** 
 * \brief
 * Current status of Transmit FIFO Empty Interrupt before masking
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RISR . TXEIR
 */
#define  VTSS_F_SIMC_SIMC_RISR_TXEIR          VTSS_BIT(0)


/** 
 * \brief Transmit FIFO Overflow Interrupt Clear
 *
 * \details
 * Register: \a SIMC:SIMC:TXOICR
 */
#define VTSS_SIMC_SIMC_TXOICR                VTSS_IOREG(VTSS_TO_SIMC,0xe)

/** 
 * \brief
 * This field is set when Transmit FIFO Overflow Interrupt is active,
 * interrupt is cleared by reading this register.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_TXOICR . TXOICR
 */
#define  VTSS_F_SIMC_SIMC_TXOICR_TXOICR       VTSS_BIT(0)


/** 
 * \brief Receive FIFO Overflow Interrupt Clear
 *
 * \details
 * Register: \a SIMC:SIMC:RXOICR
 */
#define VTSS_SIMC_SIMC_RXOICR                VTSS_IOREG(VTSS_TO_SIMC,0xf)

/** 
 * \brief
 * This field is set when Receive FIFO Overflow Interrupt is active,
 * interrupt is cleared by reading this register.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RXOICR . RXOICR
 */
#define  VTSS_F_SIMC_SIMC_RXOICR_RXOICR       VTSS_BIT(0)


/** 
 * \brief Receive FIFO Underflow Interrupt Clear
 *
 * \details
 * Register: \a SIMC:SIMC:RXUICR
 */
#define VTSS_SIMC_SIMC_RXUICR                VTSS_IOREG(VTSS_TO_SIMC,0x10)

/** 
 * \brief
 * This field is set when Receive FIFO Underflow Interrupt is active,
 * interrupt is cleared by reading this register.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RXUICR . RXUICR
 */
#define  VTSS_F_SIMC_SIMC_RXUICR_RXUICR       VTSS_BIT(0)


/** 
 * \brief Multi-Master Contention Interrupt Clear
 *
 * \details
 * Register: \a SIMC:SIMC:MSTICR
 */
#define VTSS_SIMC_SIMC_MSTICR                VTSS_IOREG(VTSS_TO_SIMC,0x11)

/** 
 * \brief
 * This field is set when Multi-Master Contention Interrupt is active,
 * interrupt is cleared by reading this register.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_MSTICR . MSTICR
 */
#define  VTSS_F_SIMC_SIMC_MSTICR_MSTICR       VTSS_BIT(0)


/** 
 * \brief SIMC Combined Interrupt Clear
 *
 * \details
 * Register: \a SIMC:SIMC:ICR
 */
#define VTSS_SIMC_SIMC_ICR                   VTSS_IOREG(VTSS_TO_SIMC,0x12)

/** 
 * \brief
 * This field is set when any of the master's TXO, RXO, RXU, or MST
 * interrupts are active. Reading from this register clears all interrupts,
 * as reading from SIMC::TXOICR, SIMC::RXOICR, SIMC::RXUICR, and
 * SIMC::MSTICR registers.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_ICR . ICR
 */
#define  VTSS_F_SIMC_SIMC_ICR_ICR             VTSS_BIT(0)


/** 
 * \brief Transmit/Receive FIFO
 *
 * \details
 * 16-bit read/write buffer for the transmit/receive FIFOs. When the
 * register is read, data in the receive FIFO buffer is accessed. When it
 * is written to, data are moved into the transmit FIFO buffer; a write can
 * occur only when SIMC::SIMCEN.SIMCEN = 1. FIFOs are reset when
 * SIMC::SIMCEN.SIMCEN = 0. This register is replicated to allow burst
 * access to fifo's; the replication index is not used when accessing the
 * FIFO.
 *
 * Register: \a SIMC:SIMC:DR
 *
 * @param ri Register: DR (??), 0-35
 */
#define VTSS_SIMC_SIMC_DR(ri)                VTSS_IOREG(VTSS_TO_SIMC,0x18 + (ri))

/** 
 * \brief
 * Data is aligned to bit 0 (right-justified) when accessing less than 16
 * bit data-words. Read = Receive FIFO buffer. Write = Transmit FIFO
 * buffer.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_DR . DR
 */
#define  VTSS_F_SIMC_SIMC_DR_DR(x)            VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SIMC_SIMC_DR_DR               VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SIMC_SIMC_DR_DR(x)            VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief RXD Sample Delay
 *
 * \details
 * This register controls the number of VCore system clock cycles that are
 * delayed -from the default sample time- before the actual sample of the
 * rxd input signal occurs. It is impossible to write to this register when
 * the SSI is enabled; the SSI is enabled and disabled by writing to the
 * SIMCEN register.
 *
 * Register: \a SIMC:SIMC:RX_SAMPLE_DLY
 */
#define VTSS_SIMC_SIMC_RX_SAMPLE_DLY         VTSS_IOREG(VTSS_TO_SIMC,0x3c)

/** 
 * \brief
 * This field is used to delay the sample of the rxd input signal. Each
 * value represents a single VCore system clock delay on the sample of the
 * rxd signal. If this field is programmed with a value that exceeds 25, a
 * zero (0) delay will be applied to the rxd sample.
 *
 * \details 
 * Field: ::VTSS_SIMC_SIMC_RX_SAMPLE_DLY . RSD
 */
#define  VTSS_F_SIMC_SIMC_RX_SAMPLE_DLY_RSD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SIMC_SIMC_RX_SAMPLE_DLY_RSD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SIMC_SIMC_RX_SAMPLE_DLY_RSD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_OCELOT_REGS_SIMC_H_ */
