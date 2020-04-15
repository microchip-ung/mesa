#ifndef _VTSS_SERVALT_REGS_TWI_H_
#define _VTSS_SERVALT_REGS_TWI_H_

/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

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

#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a TWI
 *
 * \see vtss_target_TWI_e
 *
 * Two-Wire Interface Controller
 *
 ***********************************************************************/

/**
 * Register Group: \a TWI:TWI
 *
 * Two-Wire Interface controller
 */


/** 
 * \brief TWI configuration
 *
 * \details
 * Register: \a TWI:TWI:CFG
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CFG(target)             VTSS_IOREG(target,0x0)

/** 
 * \brief
 * This bit controls whether the TWI controller has its slave disabled. If
 * this bit is set (slave is disabled), the controller functions only as a
 * master and does not perform any action that requires a slave.
 *
 * \details 
 * '0': slave is enabled
 * '1': slave is disabled
 *
 * Field: ::VTSS_TWI_TWI_CFG . SLAVE_DIS
 */
#define  VTSS_F_TWI_TWI_CFG_SLAVE_DIS(x)      VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TWI_TWI_CFG_SLAVE_DIS         VTSS_BIT(6)
#define  VTSS_X_TWI_TWI_CFG_SLAVE_DIS(x)      VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Determines whether RESTART conditions may be sent when acting as a
 * master. Some older slaves do not support handling RESTART conditions;
 * however, RESTART conditions are used in several operations.
 * When RESTART is disabled, the master is prohibited from performing the
 * following functions:
 *  * Change direction within a transfer (split)
 *  * Send a START BYTE
 *  * Combined format transfers in 7-bit addressing modes
 *  * Read operation with a 10-bit address
 *  * Send multiple bytes per transfer
 * By replacing RESTART condition followed by a STOP and a subsequent START
 * condition, split operations are  broken down into multiple transfers. If
 * the above operations are performed, it will result in setting
 * RAW_INTR_STAT.R_TX_ABRT.
 *
 * \details 
 * '0': disable
 * '1': enable
 *
 * Field: ::VTSS_TWI_TWI_CFG . RESTART_ENA
 */
#define  VTSS_F_TWI_TWI_CFG_RESTART_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TWI_TWI_CFG_RESTART_ENA       VTSS_BIT(5)
#define  VTSS_X_TWI_TWI_CFG_RESTART_ENA(x)    VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Controls whether transfers starts in 7- or 10-bit addressing mode when
 * acting as a master.
 *
 * \details 
 * '0': 7-bit addressing
 * '1': 10-bit addressing
 *
 * Field: ::VTSS_TWI_TWI_CFG . MASTER_10BITADDR
 */
#define  VTSS_F_TWI_TWI_CFG_MASTER_10BITADDR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TWI_TWI_CFG_MASTER_10BITADDR  VTSS_BIT(4)
#define  VTSS_X_TWI_TWI_CFG_MASTER_10BITADDR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Controls whether the the TWI controller responds to 7- or 10-bit
 * addresses in slave mode. In 7-bit mode; transactions that involve 10-bit
 * addressing are ignored and only the lower 7 bits of the SAR register are
 * compared. 
 *
 * \details 
 * '0': 7-bit addressing. 
 * '1': 10-bit addressing.
 *
 * Field: ::VTSS_TWI_TWI_CFG . SLAVE_10BITADDR
 */
#define  VTSS_F_TWI_TWI_CFG_SLAVE_10BITADDR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TWI_TWI_CFG_SLAVE_10BITADDR   VTSS_BIT(3)
#define  VTSS_X_TWI_TWI_CFG_SLAVE_10BITADDR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * These bits control at which speed the TWI controller operates; its
 * setting is relevant only in master mode. Hardware protects against
 * illegal values being programmed by software.
 *
 * \details 
 * '1': standard mode (100 kbit/s)
 * '2': fast mode (400 kbit/s)
 *
 * Field: ::VTSS_TWI_TWI_CFG . SPEED
 */
#define  VTSS_F_TWI_TWI_CFG_SPEED(x)          VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_TWI_TWI_CFG_SPEED             VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_TWI_TWI_CFG_SPEED(x)          VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * This bit controls whether the TWI master is enabled.
 *
 * \details 
 * '0': master disabled
 * '1': master enabled
 *
 * Field: ::VTSS_TWI_TWI_CFG . MASTER_ENA
 */
#define  VTSS_F_TWI_TWI_CFG_MASTER_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CFG_MASTER_ENA        VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CFG_MASTER_ENA(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Target address
 *
 * \details
 * Register: \a TWI:TWI:TAR
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_TAR(target)             VTSS_IOREG(target,0x1)

/** 
 * \brief
 * This bit indicates whether software performs a General Call or START
 * BYTE command.
 *
 * \details 
 * '0': ignore bit 10 GC_OR_START and use TAR normally
 * '1': perform special TWI command as specified in GC_OR_START bit
 *
 * Field: ::VTSS_TWI_TWI_TAR . GC_OR_START_ENA
 */
#define  VTSS_F_TWI_TWI_TAR_GC_OR_START_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_TWI_TWI_TAR_GC_OR_START_ENA   VTSS_BIT(11)
#define  VTSS_X_TWI_TWI_TAR_GC_OR_START_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * If TAR.GC_OR_START_ENA is set to 1, then this bit indicates whether a
 * General Call or START byte command is to be performed.
 *
 * \details 
 * '0': General Call Address - after issuing a General Call, only writes
 * may be performed. Attempting to issue a read command results in setting
 * RAW_INTR_STAT.R_TX_ABRT. The TWI controller remains in General Call mode
 * until the TAR.GC_OR_START_ENA field is cleared.
 * '1': START BYTE
 *
 * Field: ::VTSS_TWI_TWI_TAR . GC_OR_START
 */
#define  VTSS_F_TWI_TWI_TAR_GC_OR_START(x)    VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_TWI_TWI_TAR_GC_OR_START       VTSS_BIT(10)
#define  VTSS_X_TWI_TWI_TAR_GC_OR_START(x)    VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * This is the target address for any master transaction. When transmitting
 * a General Call, these bits are ignored. To generate a START BYTE, the
 * CPU needs to write only once into these bits.
 * If the TAR and SAR are the same, loopback exists but the FIFOs are
 * shared between master and slave, so full loopback is not feasible. Only
 * one direction loopback mode is supported (simplex), not duplex. A master
 * cannot transmit to itself; it can transmit to only a slave.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TAR . TAR
 */
#define  VTSS_F_TWI_TWI_TAR_TAR(x)            VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_TWI_TWI_TAR_TAR               VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_TWI_TWI_TAR_TAR(x)            VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Slave address
 *
 * \details
 * Register: \a TWI:TWI:SAR
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_SAR(target)             VTSS_IOREG(target,0x2)

/** 
 * \brief
 * The SAR holds the slave address when the TWI is operating as a slave.
 * For 7-bit addressing, only SAR[6:0] is used.
 * This register can be written only when the TWI interface is disabled
 * (ENABLE = 0).
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_SAR . SAR
 */
#define  VTSS_F_TWI_TWI_SAR_SAR(x)            VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_TWI_TWI_SAR_SAR               VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_TWI_TWI_SAR_SAR(x)            VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a TWI:TWI:RESERVED1
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RESERVED1(target)       VTSS_IOREG(target,0x3)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_RESERVED1 . RESERVED1
 */
#define  VTSS_F_TWI_TWI_RESERVED1_RESERVED1(x)  (x)
#define  VTSS_M_TWI_TWI_RESERVED1_RESERVED1     0xffffffff
#define  VTSS_X_TWI_TWI_RESERVED1_RESERVED1(x)  (x)


/** 
 * \brief Rx/Tx data buffer and command
 *
 * \details
 * Register: \a TWI:TWI:DATA_CMD
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_DATA_CMD(target)        VTSS_IOREG(target,0x4)

/** 
 * \brief
 * This bit controls whether a read or a write is performed. This bit does
 * not control the direction when the TWI acts as a slave. It controls only
 * the direction when it acts as a master.
 * When a command is entered in the TX FIFO, this bit distinguishes the
 * write and read commands. In slave-receiver mode, this bit is a "don't
 * care" because writes to this register are not required. In
 * slave-transmitter mode, a "0" indicates that CPU data is to be
 * transmitted and as DATA. 
 * When programming this bit, remember the following: attempting to perform
 * a read operation after a General Call command has been sent results in a
 * TX_ABRT interrupt (RAW_INTR_STAT.R_TX_ABRT), unless TAR.GC_OR_START_ENA
 * has been cleared.
 * If a "1" is written to this bit after receiving a RD_REQ interrupt, then
 * a TX_ABRT interrupt occurs.
 * NOTE: It is possible that while attempting a master TWI read transfer, a
 * RD_REQ interrupt may have occurred simultaneously due to a remote TWI
 * master addressing this controller. In this type of scenario, the TWI
 * controller ignores the DATA_CMD write, generates a TX_ABRT interrupt,
 * and waits to service the RD_REQ interrupt.
 *
 * \details 
 * '1' = Read
 * '0' = Write
 *
 * Field: ::VTSS_TWI_TWI_DATA_CMD . CMD
 */
#define  VTSS_F_TWI_TWI_DATA_CMD_CMD(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TWI_TWI_DATA_CMD_CMD          VTSS_BIT(8)
#define  VTSS_X_TWI_TWI_DATA_CMD_CMD(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * This register contains the data to be transmitted or received on the TWI
 * bus. If you are writing to this register and want to perform a read,
 * this field is ignored by the controller. However, when you read this
 * register, these bits return the value of data received on the TWI
 * interface.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_DATA_CMD . DATA
 */
#define  VTSS_F_TWI_TWI_DATA_CMD_DATA(x)      VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_TWI_TWI_DATA_CMD_DATA         VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_TWI_TWI_DATA_CMD_DATA(x)      VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Standard speed TWI clock SCL high count
 *
 * \details
 * The clock for the TWI controller is the VCore system clock. This field
 * must be set accordingly to the VCore system frequency; value = (4us /
 * VCore clock period) - 8.
 * Example: a 178.6MHz clock correspond to a period of 5.6ns, for this
 * frequency this field must not be set lower than (round up): 707 = (4us /
 * 5.6ns) - 8.
 *
 * Register: \a TWI:TWI:SS_SCL_HCNT
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_SS_SCL_HCNT(target)     VTSS_IOREG(target,0x5)

/** 
 * \brief
 * This register sets the SCL clock divider for the high-period in standard
 * speed. This value must result in a high period of no less than 4us.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_SS_SCL_HCNT . SS_SCL_HCNT
 */
#define  VTSS_F_TWI_TWI_SS_SCL_HCNT_SS_SCL_HCNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_TWI_TWI_SS_SCL_HCNT_SS_SCL_HCNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_TWI_TWI_SS_SCL_HCNT_SS_SCL_HCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Standard speed TWI clock SCL low count
 *
 * \details
 * The clock for the TWI controller is the VCore system clock. This field
 * must be set accordingly to the VCore system frequency; value = (4.7us /
 * VCore clock period) - 1.
 * Example: a 178.6MHz clock correspond to a period of 5.6ns, for this
 * frequency this field must not be set lower than (round up): 839 = (4.7us
 * / 5.6ns) - 1.
 *
 * Register: \a TWI:TWI:SS_SCL_LCNT
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_SS_SCL_LCNT(target)     VTSS_IOREG(target,0x6)

/** 
 * \brief
 * This register sets the SCL clock divider for the low-period in standard
 * speed. This value must result in a value no less than 4.7us.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_SS_SCL_LCNT . SS_SCL_LCNT
 */
#define  VTSS_F_TWI_TWI_SS_SCL_LCNT_SS_SCL_LCNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_TWI_TWI_SS_SCL_LCNT_SS_SCL_LCNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_TWI_TWI_SS_SCL_LCNT_SS_SCL_LCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Fast speed TWI clock SCL high count
 *
 * \details
 * The clock for the TWI controller is the VCore system clock. This field
 * must be set accordingly to the VCore system frequency; value = (0.6us /
 * VCore clock period) - 8.
 * Example: a 178.6MHz clock correspond to a period of 5.6ns, for this
 * frequency this field must not be set lower than (round up): 100 = (0.6us
 * / 5.6ns) - 8.
 *
 * Register: \a TWI:TWI:FS_SCL_HCNT
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_FS_SCL_HCNT(target)     VTSS_IOREG(target,0x7)

/** 
 * \brief
 * This register sets the SCL clock divider for the high-period in fast
 * speed. This value must result in a value no less than 0.6us.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_FS_SCL_HCNT . FS_SCL_HCNT
 */
#define  VTSS_F_TWI_TWI_FS_SCL_HCNT_FS_SCL_HCNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_TWI_TWI_FS_SCL_HCNT_FS_SCL_HCNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_TWI_TWI_FS_SCL_HCNT_FS_SCL_HCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Fast speed TWI clock SCL low count
 *
 * \details
 * The clock for the TWI controller is the VCore system clock. This field
 * must be set accordingly to the VCore system frequency; value = (1.3us /
 * VCore clock period) - 1.
 * Example: a 178.6MHz clock correspond to a period of 5.6ns, for this
 * frequency this field must not be set lower than (round up): 232 = (1.3us
 * / 5.6ns) - 1.
 *
 * Register: \a TWI:TWI:FS_SCL_LCNT
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_FS_SCL_LCNT(target)     VTSS_IOREG(target,0x8)

/** 
 * \brief
 * This register sets the SCL clock divider for the low-period in fast
 * speed. This value must result in a value no less than 1.3us.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_FS_SCL_LCNT . FS_SCL_LCNT
 */
#define  VTSS_F_TWI_TWI_FS_SCL_LCNT_FS_SCL_LCNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_TWI_TWI_FS_SCL_LCNT_FS_SCL_LCNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_TWI_TWI_FS_SCL_LCNT_FS_SCL_LCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a TWI:TWI:RESERVED2
 *
 * @param target A \a ::vtss_target_TWI_e target
 * @param ri Register: RESERVED2 (??), 0-1
 */
#define VTSS_TWI_TWI_RESERVED2(target,ri)    VTSS_IOREG(target,0x9 + (ri))

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_RESERVED2 . RESERVED2
 */
#define  VTSS_F_TWI_TWI_RESERVED2_RESERVED2(x)  (x)
#define  VTSS_M_TWI_TWI_RESERVED2_RESERVED2     0xffffffff
#define  VTSS_X_TWI_TWI_RESERVED2_RESERVED2(x)  (x)


/** 
 * \brief Interrupt status
 *
 * \details
 * Each field in this register has a corresponding mask field in the
 * INTR_MASK register. These fields are cleared by reading the matching
 * interrupt clear register. The unmasked raw versions of these fields are
 * available in the RAW_INTR_STAT register.
 * See RAW_INTR_STAT for a description of these fields
 *
 * Register: \a TWI:TWI:INTR_STAT
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_INTR_STAT(target)       VTSS_IOREG(target,0xb)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . GEN_CALL
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_GEN_CALL(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_GEN_CALL    VTSS_BIT(11)
#define  VTSS_X_TWI_TWI_INTR_STAT_GEN_CALL(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . START_DET
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_START_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_START_DET   VTSS_BIT(10)
#define  VTSS_X_TWI_TWI_INTR_STAT_START_DET(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . STOP_DET
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_STOP_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_STOP_DET    VTSS_BIT(9)
#define  VTSS_X_TWI_TWI_INTR_STAT_STOP_DET(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . ACTIVITY
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_ACTIVITY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_ACTIVITY    VTSS_BIT(8)
#define  VTSS_X_TWI_TWI_INTR_STAT_ACTIVITY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . RX_DONE
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_RX_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_RX_DONE     VTSS_BIT(7)
#define  VTSS_X_TWI_TWI_INTR_STAT_RX_DONE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . TX_ABRT
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_TX_ABRT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_TX_ABRT     VTSS_BIT(6)
#define  VTSS_X_TWI_TWI_INTR_STAT_TX_ABRT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . RD_REQ
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_RD_REQ(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_RD_REQ      VTSS_BIT(5)
#define  VTSS_X_TWI_TWI_INTR_STAT_RD_REQ(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . TX_EMPTY
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_TX_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_TX_EMPTY    VTSS_BIT(4)
#define  VTSS_X_TWI_TWI_INTR_STAT_TX_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . TX_OVER
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_TX_OVER(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_TX_OVER     VTSS_BIT(3)
#define  VTSS_X_TWI_TWI_INTR_STAT_TX_OVER(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . RX_FULL
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_RX_FULL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_RX_FULL     VTSS_BIT(2)
#define  VTSS_X_TWI_TWI_INTR_STAT_RX_FULL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . RX_OVER
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_RX_OVER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_RX_OVER     VTSS_BIT(1)
#define  VTSS_X_TWI_TWI_INTR_STAT_RX_OVER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_STAT . RX_UNDER
 */
#define  VTSS_F_TWI_TWI_INTR_STAT_RX_UNDER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_INTR_STAT_RX_UNDER    VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_INTR_STAT_RX_UNDER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Interrupt mask
 *
 * \details
 * These fields mask the corresponding interrupt status fields
 * (RAW_INTR_STAT). They are active high; a value of 0 prevents the
 * corresponding field in RAW_INTR_STAT from generating an interrupt.
 *
 * Register: \a TWI:TWI:INTR_MASK
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_INTR_MASK(target)       VTSS_IOREG(target,0xc)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_GEN_CALL
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_GEN_CALL(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_GEN_CALL  VTSS_BIT(11)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_GEN_CALL(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_START_DET
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_START_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_START_DET  VTSS_BIT(10)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_START_DET(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_STOP_DET
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_STOP_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_STOP_DET  VTSS_BIT(9)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_STOP_DET(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_ACTIVITY
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_ACTIVITY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_ACTIVITY  VTSS_BIT(8)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_ACTIVITY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_RX_DONE
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_RX_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_RX_DONE   VTSS_BIT(7)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_RX_DONE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_TX_ABRT
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_TX_ABRT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_TX_ABRT   VTSS_BIT(6)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_TX_ABRT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_RD_REQ
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_RD_REQ(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_RD_REQ    VTSS_BIT(5)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_RD_REQ(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_TX_EMPTY
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_TX_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_TX_EMPTY  VTSS_BIT(4)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_TX_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_TX_OVER
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_TX_OVER(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_TX_OVER   VTSS_BIT(3)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_TX_OVER(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_RX_FULL
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_RX_FULL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_RX_FULL   VTSS_BIT(2)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_RX_FULL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_RX_OVER
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_RX_OVER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_RX_OVER   VTSS_BIT(1)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_RX_OVER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_INTR_MASK . M_RX_UNDER
 */
#define  VTSS_F_TWI_TWI_INTR_MASK_M_RX_UNDER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_INTR_MASK_M_RX_UNDER  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_INTR_MASK_M_RX_UNDER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Raw interrupt status
 *
 * \details
 * Unlike the INTR_STAT register, these fields are not masked so they
 * always show the true status of the TWI controller.
 *
 * Register: \a TWI:TWI:RAW_INTR_STAT
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RAW_INTR_STAT(target)   VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Set only when a General Call address is received and it is acknowledged.
 * It stays set until it is cleared either by disabling TWI controller or
 * when the CPU reads bit 0 of the CLR_GEN_CALL register. The TWI
 * controller stores the received data in the Rx buffer.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_GEN_CALL
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_GEN_CALL(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_GEN_CALL  VTSS_BIT(11)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_GEN_CALL(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Indicates whether a START or RESTART condition has occurred on the TWI
 * regardless of whether the TWI controller is operating in slave or master
 * mode.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_START_DET
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_START_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_START_DET  VTSS_BIT(10)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_START_DET(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Indicates whether a STOP condition has occurred on the TWI controller
 * regardless of whether the TWI controller is operating in slave or master
 * mode.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_STOP_DET
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_STOP_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_STOP_DET  VTSS_BIT(9)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_STOP_DET(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * This bit captures TWI activity and stays set until it is cleared. There
 * are four ways to clear it:
 * * Disabling the TWI controller
 * * Reading the CLR_ACTIVITY register
 * * Reading the CLR_INTR register
 * * VCore system reset
 * Once this bit is set, it stays set unless one of the four methods is
 * used to clear it. Even if the TWI controller module is idle, this bit
 * remains set until cleared, indicating that there was activity on the
 * bus.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_ACTIVITY
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_ACTIVITY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_ACTIVITY  VTSS_BIT(8)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_ACTIVITY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * When the TWI controller is acting as a slave-transmitter, this bit is
 * set to 1 if the master does not acknowledge a transmitted byte. This
 * occurs on the last byte of the transmission, indicating that the
 * transmission is done.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_RX_DONE
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_RX_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_RX_DONE  VTSS_BIT(7)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_RX_DONE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This bit is set to 1 when the TWI controller is acting as a master is
 * unable to complete a command that the processor has sent. The conditions
 * that set this field are:
 * * No slave acknowledges the address byte.
 * * The addressed slave receiver does not acknowledge a byte of data.
 * * Attempting to send a master command when configured only to be a
 * slave.
 * * When CFG.RESTART_ENA is set to 0 (RESTART condition disabled), and the
 * processor attempts to issue a TWI function that is impossible to perform
 * without using RESTART conditions.
 * * High-speed master code is acknowledged (this controller does not
 * support high-speed).
 * * START BYTE is acknowledged.
 * * General Call address is not acknowledged.
 * * When a read request interrupt occurs and the processor has previously
 * placed data in the Tx buffer that has not been transmitted yet. This
 * data could have been intended to service a multi-byte RD_REQ that ended
 * up having fewer numbers of bytes requested.
 * *The TWI controller loses arbitration of the bus between transfers and
 * is then accessed as a slave-transmitter.
 * * If a read command is issued after a General Call command has been
 * issued. Disabling the TWI reverts it back to normal operation.
 * * If the CPU attempts to issue read command before a RD_REQ is serviced.
 * Anytime this bit is set, the contents of the transmit and receive
 * buffers are flushed.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_TX_ABRT
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_TX_ABRT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_TX_ABRT  VTSS_BIT(6)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_TX_ABRT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * This bit is set to 1 when the TWI controller acts as a slave and another
 * TWI master is attempting to read data from this controller. The TWI
 * controller holds the TWI bus in a wait state (SCL=0) until this
 * interrupt is serviced, which means that the slave has been addressed by
 * a remote master that is asking for data to be transferred. The processor
 * must respond to this interrupt and then write the requested data to the
 * DATA_CMD register. This bit is set to 0 just after the required data is
 * written to the DATA_CMD register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_RD_REQ
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_RD_REQ(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_RD_REQ  VTSS_BIT(5)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_RD_REQ(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This bit is set to 1 when the transmit buffer is at or below the
 * threshold value set in the TX_TL register. It is automatically cleared
 * by hardware when the buffer level goes above the threshold. When ENABLE
 * is 0, the TX FIFO is flushed and held in reset. There the TX FIFO looks
 * like it has no data within it, so this bit is set to 1, provided there
 * is activity in the master or slave state machines. When there is no
 * longer activity, then with ENABLE_STATUS.BUSY=0, this bit is set to 0.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_TX_EMPTY
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_TX_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_TX_EMPTY  VTSS_BIT(4)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_TX_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set during transmit if the transmit buffer is filled to TX_BUFFER_DEPTH
 * and the processor attempts to issue another TWI command by writing to
 * the DATA_CMD register. When the module is disabled, this bit keeps its
 * level until the master or slave state machines go into idle, and when
 * ENABLE_STATUS.BUSY goes to 0, this interrupt is cleared.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_TX_OVER
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_TX_OVER(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_TX_OVER  VTSS_BIT(3)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_TX_OVER(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set when the receive buffer reaches or goes above the RX_TL threshold in
 * the RX_TL register. It is automatically cleared by hardware when buffer
 * level goes below the threshold. If the module is disabled (ENABLE=0),
 * the RX FIFO is flushed and held in reset; therefore the RX FIFO is not
 * full. So this bit is cleared once the ENABLE field is programmed with a
 * 0, regardless of the activity that continues.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_RX_FULL
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_RX_FULL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_RX_FULL  VTSS_BIT(2)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_RX_FULL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set if the receive buffer is completely filled to RX_BUFFER_DEPTH and an
 * additional byte is received from an external TWI device. The TWI
 * controller acknowledges this, but any data bytes received after the FIFO
 * is full are lost. If the module is disabled (ENABLE=0), this bit keeps
 * its level until the master or slave state machines go into idle, and
 * when ENABLE_STATUS.BUSY goes to 0, this interrupt is cleared.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_RX_OVER
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_RX_OVER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_RX_OVER  VTSS_BIT(1)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_RX_OVER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if the processor attempts to read the receive buffer when it is
 * empty by reading from the DATA_CMD register. If the module is disabled
 * (ENABLE=0), this bit keeps its level until the master or slave state
 * machines go into idle, and when ENABLE_STATUS.BUSY goes to 0, this
 * interrupt is cleared.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RAW_INTR_STAT . R_RX_UNDER
 */
#define  VTSS_F_TWI_TWI_RAW_INTR_STAT_R_RX_UNDER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_RAW_INTR_STAT_R_RX_UNDER  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_RAW_INTR_STAT_R_RX_UNDER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Receive FIFO threshold
 *
 * \details
 * Register: \a TWI:TWI:RX_TL
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RX_TL(target)           VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Controls the level of entries (or above) that triggers the RX_FULL
 * interrupt (bit 2 in RAW_INTR_STAT register). The valid range is 0-7. A
 * value of 0 sets the threshold for 1 entry, and a value of 7 sets the
 * threshold for 8 entries.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RX_TL . RX_TL
 */
#define  VTSS_F_TWI_TWI_RX_TL_RX_TL(x)        VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_TWI_TWI_RX_TL_RX_TL           VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_TWI_TWI_RX_TL_RX_TL(x)        VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Transmit FIFO threshold
 *
 * \details
 * Register: \a TWI:TWI:TX_TL
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_TX_TL(target)           VTSS_IOREG(target,0xf)

/** 
 * \brief
 * Controls the level of entries (or below) that trigger the TX_EMPTY
 * interrupt (bit 4 in RAW_INTR_STAT register). The valid range is 0-7. A
 * value of 0 sets the threshold for 0 entries, and a value of 7 sets the
 * threshold for 7 entries.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_TL . TX_TL
 */
#define  VTSS_F_TWI_TWI_TX_TL_TX_TL(x)        VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_TWI_TWI_TX_TL_TX_TL           VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_TWI_TWI_TX_TL_TX_TL(x)        VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Clear combined and individual interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_INTR
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_INTR(target)        VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Read this register to clear the combined interrupt, all individual
 * interrupts, and the TX_ABRT_SOURCE register. This bit does not clear
 * hardware clearable interrupts but software clearable interrupts. Refer
 * to Bit 9 of the TX_ABRT_SOURCE register for an exception to clearing
 * TX_ABRT_SOURCE.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_INTR . CLR_INTR
 */
#define  VTSS_F_TWI_TWI_CLR_INTR_CLR_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_INTR_CLR_INTR     VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_INTR_CLR_INTR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear RX_UNDER interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_RX_UNDER
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_RX_UNDER(target)    VTSS_IOREG(target,0x11)

/** 
 * \brief
 * Read this register to clear the R_RX_UNDER interrupt (bit 0) of the
 * RAW_INTR_STAT register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_RX_UNDER . CLR_RX_UNDER
 */
#define  VTSS_F_TWI_TWI_CLR_RX_UNDER_CLR_RX_UNDER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_RX_UNDER_CLR_RX_UNDER  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_RX_UNDER_CLR_RX_UNDER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear RX_OVER interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_RX_OVER
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_RX_OVER(target)     VTSS_IOREG(target,0x12)

/** 
 * \brief
 * Read this register to clear the R_RX_OVER interrupt (bit 1) of the
 * RAW_INTR_STAT register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_RX_OVER . CLR_RX_OVER
 */
#define  VTSS_F_TWI_TWI_CLR_RX_OVER_CLR_RX_OVER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_RX_OVER_CLR_RX_OVER  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_RX_OVER_CLR_RX_OVER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear TX_OVER interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_TX_OVER
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_TX_OVER(target)     VTSS_IOREG(target,0x13)

/** 
 * \brief
 * Read this register to clear the R_TX_OVER interrupt (bit 3) of the
 * RAW_INTR_STAT register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_TX_OVER . CLR_TX_OVER
 */
#define  VTSS_F_TWI_TWI_CLR_TX_OVER_CLR_TX_OVER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_TX_OVER_CLR_TX_OVER  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_TX_OVER_CLR_TX_OVER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear RD_REQ interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_RD_REQ
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_RD_REQ(target)      VTSS_IOREG(target,0x14)

/** 
 * \brief
 * Read this register to clear the R_RD_REQ interrupt (bit 5) of the
 * RAW_INTR_STAT register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_RD_REQ . CLR_RD_REQ
 */
#define  VTSS_F_TWI_TWI_CLR_RD_REQ_CLR_RD_REQ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_RD_REQ_CLR_RD_REQ  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_RD_REQ_CLR_RD_REQ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear TX_ABRT interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_TX_ABRT
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_TX_ABRT(target)     VTSS_IOREG(target,0x15)

/** 
 * \brief
 * Read this register to clear the R_TX_ABRT interrupt (bit 6) of the
 * RAW_INTR_STAT register, and the TX_ABRT_SOURCE register. Refer to Bit 9
 * of the TX_ABRT_SOURCE register for an exception to clearing
 * TX_ABRT_SOURCE.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_TX_ABRT . CLR_TX_ABRT
 */
#define  VTSS_F_TWI_TWI_CLR_TX_ABRT_CLR_TX_ABRT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_TX_ABRT_CLR_TX_ABRT  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_TX_ABRT_CLR_TX_ABRT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear RX_DONE interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_RX_DONE
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_RX_DONE(target)     VTSS_IOREG(target,0x16)

/** 
 * \brief
 * Read this register to clear the R_RX_DONE interrupt (bit 7) of the
 * RAW_INTR_STAT register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_RX_DONE . CLR_RX_DONE
 */
#define  VTSS_F_TWI_TWI_CLR_RX_DONE_CLR_RX_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_RX_DONE_CLR_RX_DONE  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_RX_DONE_CLR_RX_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear ACTIVITY interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_ACTIVITY
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_ACTIVITY(target)    VTSS_IOREG(target,0x17)

/** 
 * \brief
 * Reading this register clears the ACTIVITY interrupt if the TWI
 * controller is not active anymore. If the TWI  controller is still active
 * on the bus, the ACTIVITY interrupt bit continues to be set. It is
 * automatically cleared by hardware if the module is disabled and if there
 * is no further activity on the bus. The value read from this register to
 * get status of the R_ACTIVITY interrupt (bit 8) of the RAW_INTR_STAT
 * register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_ACTIVITY . CLR_ACTIVITY
 */
#define  VTSS_F_TWI_TWI_CLR_ACTIVITY_CLR_ACTIVITY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_ACTIVITY_CLR_ACTIVITY  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_ACTIVITY_CLR_ACTIVITY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear STOP_DET interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_STOP_DET
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_STOP_DET(target)    VTSS_IOREG(target,0x18)

/** 
 * \brief
 * Read this register to clear the R_STOP_DET interrupt (bit 9) of the
 * RAW_INTR_STAT register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_STOP_DET . CLR_STOP_DET
 */
#define  VTSS_F_TWI_TWI_CLR_STOP_DET_CLR_STOP_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_STOP_DET_CLR_STOP_DET  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_STOP_DET_CLR_STOP_DET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear START_DET interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_START_DET
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_START_DET(target)   VTSS_IOREG(target,0x19)

/** 
 * \brief
 * Read this register to clear the R_START_DET interrupt (bit 10) of the
 * RAW_INTR_STAT register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_START_DET . CLR_START_DET
 */
#define  VTSS_F_TWI_TWI_CLR_START_DET_CLR_START_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_START_DET_CLR_START_DET  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_START_DET_CLR_START_DET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Clear GEN_CALL interrupt
 *
 * \details
 * Register: \a TWI:TWI:CLR_GEN_CALL
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CLR_GEN_CALL(target)    VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * Read this register to clear the R_GEN_CALL interrupt (bit 11) of
 * RAW_INTR_STAT register.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_CLR_GEN_CALL . CLR_GEN_CALL
 */
#define  VTSS_F_TWI_TWI_CLR_GEN_CALL_CLR_GEN_CALL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CLR_GEN_CALL_CLR_GEN_CALL  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CLR_GEN_CALL_CLR_GEN_CALL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TWI control
 *
 * \details
 * Register: \a TWI:TWI:CTRL
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_CTRL(target)            VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * Controls whether the TWI controller is enabled. Software can disable the
 * controller while it is active. However, it is important that care be
 * taken to ensure that the controller is disabled properly.
 * When TWI controller is disabled, the following occurs:
 * * The TX FIFO and RX FIFO get flushed.
 * * The interrupt bits in the RAW_INTR_STAT register are cleared.
 * * Status bits in the INTR_STAT register are still active until the TWI
 * controller goes into IDLE state.
 * If the module is transmitting, it stops as well as deletes the contents
 * of the transmit buffer after the current transfer is complete. If the
 * module is receiving, the controller stops the current transfer at the
 * end of the current byte and does not acknowledge the transfer.
 *
 * \details 
 * '0': Disables TWI controller
 * '1': Enables TWI controller
 *
 * Field: ::VTSS_TWI_TWI_CTRL . ENABLE
 */
#define  VTSS_F_TWI_TWI_CTRL_ENABLE(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_CTRL_ENABLE           VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_CTRL_ENABLE(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TWI status
 *
 * \details
 * Register: \a TWI:TWI:STAT
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_STAT(target)            VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * Slave FSM Activity Status. When the Slave Finite State Machine (FSM) is
 * not in the IDLE state, this bit is set.
 *
 * \details 
 * '0': Slave FSM is in IDLE state so the Slave part of the controller is
 * not Active
 * '1': Slave FSM is not in IDLE state so the Slave part of the controller
 * is Active
 *
 * Field: ::VTSS_TWI_TWI_STAT . SLV_ACTIVITY
 */
#define  VTSS_F_TWI_TWI_STAT_SLV_ACTIVITY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TWI_TWI_STAT_SLV_ACTIVITY     VTSS_BIT(6)
#define  VTSS_X_TWI_TWI_STAT_SLV_ACTIVITY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Master FSM Activity Status. When the Master Finite State Machine (FSM)
 * is not in the IDLE state, this bit is set.
 *
 * \details 
 * '0': Master FSM is in IDLE state so the Master part of the controller is
 * not Active
 * '1': Master FSM is not in IDLE state so the Master part of the
 * controller is Active
 *
 * Field: ::VTSS_TWI_TWI_STAT . MST_ACTIVITY
 */
#define  VTSS_F_TWI_TWI_STAT_MST_ACTIVITY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TWI_TWI_STAT_MST_ACTIVITY     VTSS_BIT(5)
#define  VTSS_X_TWI_TWI_STAT_MST_ACTIVITY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Receive FIFO Completely Full. When the receive FIFO is completely full,
 * this bit is set. When the receive FIFO contains one or more empty
 * location, this bit is cleared.
 *
 * \details 
 * '0': Receive FIFO is not full
 * '1': Receive FIFO is full
 *
 * Field: ::VTSS_TWI_TWI_STAT . RFF
 */
#define  VTSS_F_TWI_TWI_STAT_RFF(x)           VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TWI_TWI_STAT_RFF              VTSS_BIT(4)
#define  VTSS_X_TWI_TWI_STAT_RFF(x)           VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Receive FIFO Not Empty. Set when the receive FIFO contains one or more
 * entries and is cleared when the receive FIFO is empty. This bit can be
 * polled by software to completely empty the receive FIFO.
 *
 * \details 
 * '0': Receive FIFO is empty
 * '1': Receive FIFO is not empty
 *
 * Field: ::VTSS_TWI_TWI_STAT . RFNE
 */
#define  VTSS_F_TWI_TWI_STAT_RFNE(x)          VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TWI_TWI_STAT_RFNE             VTSS_BIT(3)
#define  VTSS_X_TWI_TWI_STAT_RFNE(x)          VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Transmit FIFO Completely Empty. When the transmit FIFO is completely
 * empty, this bit is set. When it contains one or more valid entries, this
 * bit is cleared. This bit field does not request an interrupt.
 *
 * \details 
 * '0': Transmit FIFO is not empty
 * '1': Transmit FIFO is empty
 *
 * Field: ::VTSS_TWI_TWI_STAT . TFE
 */
#define  VTSS_F_TWI_TWI_STAT_TFE(x)           VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TWI_TWI_STAT_TFE              VTSS_BIT(2)
#define  VTSS_X_TWI_TWI_STAT_TFE(x)           VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Transmit FIFO Not Full. Set when the transmit FIFO contains one or more
 * empty locations, and is cleared when the FIFO is full.
 *
 * \details 
 * '0': Transmit FIFO is full
 * '1': Transmit FIFO is not full
 *
 * Field: ::VTSS_TWI_TWI_STAT . TFNF
 */
#define  VTSS_F_TWI_TWI_STAT_TFNF(x)          VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TWI_TWI_STAT_TFNF             VTSS_BIT(1)
#define  VTSS_X_TWI_TWI_STAT_TFNF(x)          VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * TWI Activity Status.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_STAT . BUS_ACTIVITY
 */
#define  VTSS_F_TWI_TWI_STAT_BUS_ACTIVITY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_STAT_BUS_ACTIVITY     VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_STAT_BUS_ACTIVITY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Transmit FIFO level
 *
 * \details
 * Register: \a TWI:TWI:TXFLR
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_TXFLR(target)           VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * Transmit FIFO Level. Contains the number of valid data entries in the
 * transmit FIFO.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TXFLR . TXFLR
 */
#define  VTSS_F_TWI_TWI_TXFLR_TXFLR(x)        VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_TWI_TWI_TXFLR_TXFLR           VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_TWI_TWI_TXFLR_TXFLR(x)        VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Receive FIFO level
 *
 * \details
 * Register: \a TWI:TWI:RXFLR
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RXFLR(target)           VTSS_IOREG(target,0x1e)

/** 
 * \brief
 * Receive FIFO Level. Contains the number of valid data entries in the
 * receive FIFO.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_RXFLR . RXFLR
 */
#define  VTSS_F_TWI_TWI_RXFLR_RXFLR(x)        VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_TWI_TWI_RXFLR_RXFLR           VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_TWI_TWI_RXFLR_RXFLR(x)        VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a TWI:TWI:RESERVED3
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RESERVED3(target)       VTSS_IOREG(target,0x1f)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_RESERVED3 . RESERVED3
 */
#define  VTSS_F_TWI_TWI_RESERVED3_RESERVED3(x)  (x)
#define  VTSS_M_TWI_TWI_RESERVED3_RESERVED3     0xffffffff
#define  VTSS_X_TWI_TWI_RESERVED3_RESERVED3(x)  (x)


/** 
 * \brief Transmit abort source
 *
 * \details
 * Register: \a TWI:TWI:TX_ABRT_SOURCE
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_TX_ABRT_SOURCE(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * When the processor side responds to a slave mode request for data to be
 * transmitted to a remote master and user writes a 1 to DATA_CMD.CMD.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_SLVRD_INTX
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLVRD_INTX(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLVRD_INTX  VTSS_BIT(15)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLVRD_INTX(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Slave lost the bus while transmitting data to a remote master.
 * TX_ABRT_SOURCE[12] is set at the same time.
 * Note: Even though the slave never "owns" the bus, something could go
 * wrong on the bus. This is a fail safe check. For instance, during a data
 * transmission at the low-to-high transition of SCL, if what is on the
 * data bus is not what is supposed to be transmitted, then the TWI
 * controller no longer own the bus.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_SLV_ARBLOST
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST  VTSS_BIT(14)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Slave has received a read command and some data exists in the TX FIFO so
 * the slave issues a TX_ABRT interrupt to flush old data in TX FIFO.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_SLVFLUSH_TXFIFO
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO  VTSS_BIT(13)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Master has lost arbitration, or if TX_ABRT_SOURCE[14] is also set, then
 * the slave transmitter has lost arbitration.
 * Note: the TWI controller can be both master and slave at the same time.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ARB_LOST
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ARB_LOST(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ARB_LOST  VTSS_BIT(12)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ARB_LOST(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * User tries to initiate a Master operation with the Master mode disabled.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_MASTER_DIS
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_MASTER_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_MASTER_DIS  VTSS_BIT(11)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_MASTER_DIS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * The restart is disabled (RESTART_ENA bit (CFG[5]) = 0) and the master
 * sends a read command in 10-bit addressing mode.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_10B_RD_NORSTRT
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT  VTSS_BIT(10)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * To clear Bit 9, the source of the ABRT_SBYTE_NORSTRT must be fixed
 * first; restart must be enabled (CFG[5]=1), the SPECIAL bit must be
 * cleared (TAR[11]), or the GC_OR_START bit must be cleared (TAR[10]).
 * Once the source of the ABRT_SBYTE_NORSTRT is fixed, then this bit can be
 * cleared in the same manner as other bits in this register. If the source
 * of the ABRT_SBYTE_NORSTRT is not fixed before attempting to clear this
 * bit, bit 9 clears for one cycle and then gets re-asserted.
 *
 * \details 
 * '1': The restart is disabled (RESTART_ENA bit (CFG[5]) = 0) and the user
 * is trying to send a START Byte.
 *
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_SBYTE_NORSTRT
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT  VTSS_BIT(9)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * The restart is disabled (RESTART_ENA bit (CFG[5]) = 0) and the user is
 * trying to use the master to transfer data in High Speed mode.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_HS_NORSTRT
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_HS_NORSTRT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_HS_NORSTRT  VTSS_BIT(8)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_HS_NORSTRT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Master has sent a START Byte and the START Byte was acknowledged (wrong
 * behavior).
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_SBYTE_ACKDET
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET  VTSS_BIT(7)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Master is in High Speed mode and the High Speed Master code was
 * acknowledged (wrong behavior).
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_HS_ACKDET
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_HS_ACKDET(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_HS_ACKDET  VTSS_BIT(6)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_HS_ACKDET(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * TWI controller in master mode sent a General Call but the user
 * programmed the byte following the General Call to be a read from the bus
 * (DATA_CMD[9] is set to 1).
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_GCALL_READ
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_GCALL_READ(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_GCALL_READ  VTSS_BIT(5)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_GCALL_READ(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * TWI controller in master mode sent a General Call and no slave on the
 * bus acknowledged the General Call.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_GCALL_NOACK
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_GCALL_NOACK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_GCALL_NOACK  VTSS_BIT(4)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_GCALL_NOACK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * This is a master-mode only bit. Master has received an acknowledgement
 * for the address, but when it sent data byte(s) following the address, it
 * did not receive an acknowledge from the remote slave(s).
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_TXDATA_NOACK
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK  VTSS_BIT(3)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Master is in 10-bit address mode and the second address byte of the
 * 10-bit address was not acknowledged by any slave.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_10ADDR2_NOACK
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK  VTSS_BIT(2)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Master is in 10-bit address mode and the first 10-bit address byte was
 * not acknowledged by any slave.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_10ADDR1_NOACK
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK  VTSS_BIT(1)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Master is in 7-bit addressing mode and the address sent was not
 * acknowledged by any slave.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_TX_ABRT_SOURCE . ABRT_7B_ADDR_NOACK
 */
#define  VTSS_F_TWI_TWI_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a TWI:TWI:RESERVED8
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RESERVED8(target)       VTSS_IOREG(target,0x21)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_RESERVED8 . RESERVED8
 */
#define  VTSS_F_TWI_TWI_RESERVED8_RESERVED8(x)  (x)
#define  VTSS_M_TWI_TWI_RESERVED8_RESERVED8     0xffffffff
#define  VTSS_X_TWI_TWI_RESERVED8_RESERVED8(x)  (x)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a TWI:TWI:RESERVED4
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RESERVED4(target)       VTSS_IOREG(target,0x22)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_RESERVED4 . RESERVED4
 */
#define  VTSS_F_TWI_TWI_RESERVED4_RESERVED4(x)  (x)
#define  VTSS_M_TWI_TWI_RESERVED4_RESERVED4     0xffffffff
#define  VTSS_X_TWI_TWI_RESERVED4_RESERVED4(x)  (x)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a TWI:TWI:RESERVED5
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RESERVED5(target)       VTSS_IOREG(target,0x23)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_RESERVED5 . RESERVED5
 */
#define  VTSS_F_TWI_TWI_RESERVED5_RESERVED5(x)  (x)
#define  VTSS_M_TWI_TWI_RESERVED5_RESERVED5     0xffffffff
#define  VTSS_X_TWI_TWI_RESERVED5_RESERVED5(x)  (x)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a TWI:TWI:RESERVED6
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_RESERVED6(target)       VTSS_IOREG(target,0x24)

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_RESERVED6 . RESERVED6
 */
#define  VTSS_F_TWI_TWI_RESERVED6_RESERVED6(x)  (x)
#define  VTSS_M_TWI_TWI_RESERVED6_RESERVED6     0xffffffff
#define  VTSS_X_TWI_TWI_RESERVED6_RESERVED6(x)  (x)


/** 
 * \brief SDA setup
 *
 * \details
 * This field must be set accordingly to the VCore system frequency; value
 * = 100ns / VCore clock period.
 * Example: a 178.6MHz clock correspond to a period of 5.6ns, for this
 * frequency and fast TWI speed this field must not be set lower than
 * (round up): 18 = 100ns / 5.6ns. For normal TWI speed this field must not
 * be set lower than (round up): 45 = 250ns / 5.6ns.
 *
 * Register: \a TWI:TWI:SDA_SETUP
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_SDA_SETUP(target)       VTSS_IOREG(target,0x25)

/** 
 * \brief
 * This register controls the amount of time delay (in terms of number of
 * VCore clock periods) introduced in the rising edge of SCL, relative to
 * SDA changing, when the TWI controller services a read request in a
 * slave-receiver operation. The minimum for fast mode is 100ns, for nomal
 * mode the minimum is 250ns.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_SDA_SETUP . SDA_SETUP
 */
#define  VTSS_F_TWI_TWI_SDA_SETUP_SDA_SETUP(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_TWI_TWI_SDA_SETUP_SDA_SETUP     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_TWI_TWI_SDA_SETUP_SDA_SETUP(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Acknowledge general call
 *
 * \details
 * Register: \a TWI:TWI:ACK_GEN_CALL
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_ACK_GEN_CALL(target)    VTSS_IOREG(target,0x26)

/** 
 * \brief
 * ACK General Call. When set to 1, the TWI controller responds with a ACK
 * when it receives a General Call. Otherwise, the controller responds with
 * a NACK.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_ACK_GEN_CALL . ACK_GEN_CALL
 */
#define  VTSS_F_TWI_TWI_ACK_GEN_CALL_ACK_GEN_CALL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_ACK_GEN_CALL_ACK_GEN_CALL  VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_ACK_GEN_CALL_ACK_GEN_CALL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Enable status
 *
 * \details
 * Register: \a TWI:TWI:ENABLE_STATUS
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_ENABLE_STATUS(target)   VTSS_IOREG(target,0x27)

/** 
 * \brief
 * Slave FIFO Filled and Flushed. This bit indicates if a Slave-Receiver
 * operation has been aborted with at least 1 data byte received from a TWI
 * transfer due to the setting of ENABLE from 1 to 0.
 * When read as 1, the TWI controller is deemed to have been actively
 * engaged in an aborted TWI transfer (with matching address) and the data
 * phase of the TWI transfer has been entered, even though the data byte
 * has been responded with a NACK.
 * When read as 0, the TWI controller is deemed to have been disabled when
 * the TWI bus is idle.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_ENABLE_STATUS . SLV_FIFO_FILLED_AND_FLUSHED
 */
#define  VTSS_F_TWI_TWI_ENABLE_STATUS_SLV_FIFO_FILLED_AND_FLUSHED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TWI_TWI_ENABLE_STATUS_SLV_FIFO_FILLED_AND_FLUSHED  VTSS_BIT(2)
#define  VTSS_X_TWI_TWI_ENABLE_STATUS_SLV_FIFO_FILLED_AND_FLUSHED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Slave-Receiver Operation Aborted. This bit indicates if a Slave-Receiver
 * operation has been aborted due to the setting of the ENABLE register
 * from 1 to 0.
 * When read as 1, the TWI controller is deemed to have forced a NACK
 * during any part of a TWI transfer, irrespective of whether the TWI
 * address matches the slave address set in the TWI controller (SAR
 * register).
 * When read as 0, the TWI controller is deemed to have been disabled when
 * the TWI bus is idle.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_ENABLE_STATUS . SLV_RX_ABORTED
 */
#define  VTSS_F_TWI_TWI_ENABLE_STATUS_SLV_RX_ABORTED(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TWI_TWI_ENABLE_STATUS_SLV_RX_ABORTED  VTSS_BIT(1)
#define  VTSS_X_TWI_TWI_ENABLE_STATUS_SLV_RX_ABORTED(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When read as 1, the TWI controller is deemed to be actively involved in
 * an TWI transfer, irrespective of whether being in an address or data
 * phase for all master or slave modes. When read as 0, the TWI controller
 * is deemed completely inactive.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_ENABLE_STATUS . BUSY
 */
#define  VTSS_F_TWI_TWI_ENABLE_STATUS_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TWI_TWI_ENABLE_STATUS_BUSY    VTSS_BIT(0)
#define  VTSS_X_TWI_TWI_ENABLE_STATUS_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Reserved
 *
 * \details
 * Register: \a TWI:TWI:RESERVED7
 *
 * @param target A \a ::vtss_target_TWI_e target
 * @param ri Register: RESERVED7 (??), 0-20
 */
#define VTSS_TWI_TWI_RESERVED7(target,ri)    VTSS_IOREG(target,0x28 + (ri))

/** 
 * \details 
 * Field: ::VTSS_TWI_TWI_RESERVED7 . RESERVED7
 */
#define  VTSS_F_TWI_TWI_RESERVED7_RESERVED7(x)  (x)
#define  VTSS_M_TWI_TWI_RESERVED7_RESERVED7     0xffffffff
#define  VTSS_X_TWI_TWI_RESERVED7_RESERVED7(x)  (x)


/** 
 * \brief Component parameter
 *
 * \details
 * Register: \a TWI:TWI:COMP_PARAM_1
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_COMP_PARAM_1(target)    VTSS_IOREG(target,0x3d)

/** 
 * \brief
 * The depth of the TX buffer.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_COMP_PARAM_1 . TX_BUFFER_DEPTH
 */
#define  VTSS_F_TWI_TWI_COMP_PARAM_1_TX_BUFFER_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_TWI_TWI_COMP_PARAM_1_TX_BUFFER_DEPTH     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_TWI_TWI_COMP_PARAM_1_TX_BUFFER_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * The depth of the RX buffer.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_COMP_PARAM_1 . RX_BUFFER_DEPTH
 */
#define  VTSS_F_TWI_TWI_COMP_PARAM_1_RX_BUFFER_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_TWI_TWI_COMP_PARAM_1_RX_BUFFER_DEPTH     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_TWI_TWI_COMP_PARAM_1_RX_BUFFER_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * This value indicates if this register is valid or not.
 *
 * \details 
 * '0': Dones not have encoded parameters.
 * '1': Has encoded parameters.
 *
 * Field: ::VTSS_TWI_TWI_COMP_PARAM_1 . ADD_ENCODED_PARAMS
 */
#define  VTSS_F_TWI_TWI_COMP_PARAM_1_ADD_ENCODED_PARAMS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TWI_TWI_COMP_PARAM_1_ADD_ENCODED_PARAMS  VTSS_BIT(7)
#define  VTSS_X_TWI_TWI_COMP_PARAM_1_ADD_ENCODED_PARAMS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \details 
 * '0': Does not have DMA interface.
 * '1': Has DMA interface.
 *
 * Field: ::VTSS_TWI_TWI_COMP_PARAM_1 . HAS_DMA
 */
#define  VTSS_F_TWI_TWI_COMP_PARAM_1_HAS_DMA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TWI_TWI_COMP_PARAM_1_HAS_DMA  VTSS_BIT(6)
#define  VTSS_X_TWI_TWI_COMP_PARAM_1_HAS_DMA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * The value of this register is derived from the IC_INTR_IO coreConsultant
 * parameter.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_COMP_PARAM_1 . INTR_IO
 */
#define  VTSS_F_TWI_TWI_COMP_PARAM_1_INTR_IO(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TWI_TWI_COMP_PARAM_1_INTR_IO  VTSS_BIT(5)
#define  VTSS_X_TWI_TWI_COMP_PARAM_1_INTR_IO(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * The value of this register is derived from the HC_COUNT_VALUES
 * coreConsultant parameter.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_COMP_PARAM_1 . HC_COUNT_VALUES
 */
#define  VTSS_F_TWI_TWI_COMP_PARAM_1_HC_COUNT_VALUES(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TWI_TWI_COMP_PARAM_1_HC_COUNT_VALUES  VTSS_BIT(4)
#define  VTSS_X_TWI_TWI_COMP_PARAM_1_HC_COUNT_VALUES(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * The maximum TWI speed of the controller.
 *
 * \details 
 * 1: Standard
 * 2: Fast
 * 3: High
 *
 * Field: ::VTSS_TWI_TWI_COMP_PARAM_1 . MAX_SPEED_MODE
 */
#define  VTSS_F_TWI_TWI_COMP_PARAM_1_MAX_SPEED_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_TWI_TWI_COMP_PARAM_1_MAX_SPEED_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_TWI_TWI_COMP_PARAM_1_MAX_SPEED_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * The value of this register is derived from the APB_DATA_WIDTH
 * coreConsultant parameter.
 *
 * \details 
 * 0: 8 bits
 * 1: 16 bits
 * 2: 32 bits
 *
 * Field: ::VTSS_TWI_TWI_COMP_PARAM_1 . APB_DATA_WIDTH
 */
#define  VTSS_F_TWI_TWI_COMP_PARAM_1_APB_DATA_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_TWI_TWI_COMP_PARAM_1_APB_DATA_WIDTH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_TWI_TWI_COMP_PARAM_1_APB_DATA_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Component version
 *
 * \details
 * Register: \a TWI:TWI:COMP_VERSION
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_COMP_VERSION(target)    VTSS_IOREG(target,0x3e)

/** 
 * \brief
 * Specific values for this register are described in the Releases Table in
 * the Release Notes.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_COMP_VERSION . COMP_VERSION
 */
#define  VTSS_F_TWI_TWI_COMP_VERSION_COMP_VERSION(x)  (x)
#define  VTSS_M_TWI_TWI_COMP_VERSION_COMP_VERSION     0xffffffff
#define  VTSS_X_TWI_TWI_COMP_VERSION_COMP_VERSION(x)  (x)


/** 
 * \brief Component type
 *
 * \details
 * Register: \a TWI:TWI:COMP_TYPE
 *
 * @param target A \a ::vtss_target_TWI_e target
 */
#define VTSS_TWI_TWI_COMP_TYPE(target)       VTSS_IOREG(target,0x3f)

/** 
 * \brief
 * Component Type number = 0x44_57_01_40, this assigned unique hex value is
 * constant.
 *
 * \details 
 * Field: ::VTSS_TWI_TWI_COMP_TYPE . COMP_TYPE
 */
#define  VTSS_F_TWI_TWI_COMP_TYPE_COMP_TYPE(x)  (x)
#define  VTSS_M_TWI_TWI_COMP_TYPE_COMP_TYPE     0xffffffff
#define  VTSS_X_TWI_TWI_COMP_TYPE_COMP_TYPE(x)  (x)


#endif /* _VTSS_SERVALT_REGS_TWI_H_ */
