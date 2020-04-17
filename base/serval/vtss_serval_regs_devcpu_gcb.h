// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVAL_REGS_DEVCPU_GCB_H_
#define _VTSS_SERVAL_REGS_DEVCPU_GCB_H_


#include "vtss_serval_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a DEVCPU_GCB
 *
 * CPU device configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a DEVCPU_GCB:CHIP_REGS
 *
 * Software/hardware interaction
 */


/** 
 * \brief Chip ID register
 *
 * \details
 * JTAG encoded Chip ID register.
 *
 * Register: \a DEVCPU_GCB:CHIP_REGS:CHIP_ID
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x0)

/** 
 * \brief
 * Revision ID.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID . REV_ID
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Part ID.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID . PART_ID
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID(x)  VTSS_ENCODE_BITFIELD(x,12,16)
#define  VTSS_M_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID     VTSS_ENCODE_BITMASK(12,16)
#define  VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID(x)  VTSS_EXTRACT_BITFIELD(x,12,16)

/** 
 * \brief
 * Manufactor ID.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID . MFG_ID
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_CHIP_ID_MFG_ID(x)  VTSS_ENCODE_BITFIELD(x,1,11)
#define  VTSS_M_DEVCPU_GCB_CHIP_REGS_CHIP_ID_MFG_ID     VTSS_ENCODE_BITMASK(1,11)
#define  VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_MFG_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,11)

/** 
 * \brief
 * Always 1.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID . ONE
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_CHIP_ID_ONE  VTSS_BIT(0)


/** 
 * \brief General purpose register
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:GPR
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_GPR        VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1)


/** 
 * \brief Reset control register
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:SOFT_RST
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_SOFT_RST   VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x2)

/** 
 * \brief
 * Set this field to reset the whole chip. This field is automatically
 * cleared by the reset.
 * Note: It is possible for the VCore System to protect itself from this
 * soft-reset, for more info see ICPU_CFG::RESET.CORE_RST_PROTECT inside
 * the VCore register space.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_SOFT_RST . SOFT_CHIP_RST
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_SOFT_RST_SOFT_CHIP_RST  VTSS_BIT(0)


/** 
 * \brief Various status indications
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:HW_STAT
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_HW_STAT    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x4)

/** 
 * \brief
 * This field is set if a hardware fail has been detected in any of the
 * memories during startup-initialization of the chip. This field is valid
 * after release of reset.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_HW_STAT . MEM_FAIL
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_HW_STAT_MEM_FAIL  VTSS_BIT(0)


/** 
 * \brief Encoded features
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:FEA_STAT
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_FEA_STAT   VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x5)

/**
 * Register Group: \a DEVCPU_GCB:SW_REGS
 *
 * Software/software interaction
 */


/** 
 * \brief Manually assert software interrupt
 *
 * \details
 * This register provides a simple interface for interrupting on either
 * sofware interrupt 0 or 1, without implementing semaphore support.
 *
 * Register: \a DEVCPU_GCB:SW_REGS:SW_INTR
 */
#define VTSS_DEVCPU_GCB_SW_REGS_SW_INTR      VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x7)

/** 
 * \brief
 * Set this field to inject software interrupt 1. This field is
 * automatically cleared after interrupt has been generated.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SW_INTR . SW1_INTR
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SW_INTR_SW1_INTR  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to assert software interrupt 0. This field is
 * automatically cleared after interrupt has been generated.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SW_INTR . SW0_INTR
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SW_INTR_SW0_INTR  VTSS_BIT(0)

/**
 * Register Group: \a DEVCPU_GCB:VCORE_ACCESS
 *
 *  VCore SBA access
 */


/** 
 * \brief Control register for VCore accesses
 *
 * \details
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_CTRL
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x8)

/** 
 * \brief
 * If the VCore access logic detects an error this field is set based on
 * the nature of the error. This is a read-only field which is cleared by
 * the VCore access logic when a new access is (sucessfully) accepted.
 *
 * \details 
 * 0: No errors detected.
 * 1: SBA not ready when accessed.
 * 2: SBA reported error.
 * 3: New data or address written during active access.
 *
 * Field: ::VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL . VA_ERR
 */
#define  VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_ERR(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_ERR     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * This field is set to the value of DEVCPU_GCB::VA_CTRL.VA_BUSY whenever
 * one of the data registers DEVCPU_GCB::VA_DATA, DEVCPU_GCB::VA_DATA_INCR,
 * or DEVCPU_GCB::VA_DATA_RO is read. By examining this field it is
 * possible to determine if DEVCPU_GCB::VA_CTRL.VA_BUSY was set at the time
 * a read from one of these registers was performed.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL . VA_BUSY_RD
 */
#define  VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_BUSY_RD  VTSS_BIT(1)

/** 
 * \brief
 * This field is set by hardware when an access into VCore domain is
 * started, and cleared when the access is done.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL . VA_BUSY
 */
#define  VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_BUSY  VTSS_BIT(0)


/** 
 * \brief Address register for VCore accesses
 *
 * \details
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_ADDR
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_ADDR  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x9)


/** 
 * \brief Data register for VCore accesses
 *
 * \details
 * The VA_DATA, VA_DATA_INCR, and VA_DATA_INERT registers are used for
 * indirect access into the VCore domain. The functionality of the
 * VA_DATA_INCR and VA_DATA_INERT registers are similar to this register -
 * but with minor exceptions. These exceptions are fleshed out in the
 * description of the respective registers.
 *
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_DATA
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0xa)


/** 
 * \brief Data register for VCore accesses (w. auto increment of address)
 *
 * \details
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_DATA_INCR
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA_INCR  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0xb)


/** 
 * \brief Data register for VCore accesses (will not initiate access)
 *
 * \details
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_DATA_INERT
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA_INERT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0xc)

/**
 * Register Group: \a DEVCPU_GCB:GPIO
 *
 * GPIO configuration/status
 */


/** 
 * \brief Atomic set of GPIO output value
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_OUT_SET
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_SET    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0xd)


/** 
 * \brief Atomic clear of GPIO output value
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_OUT_CLR
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_CLR    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0xe)


/** 
 * \brief GPIO output value
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_OUT
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_OUT        VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0xf)


/** 
 * \brief Current value at GPIO pins
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_IN
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_IN         VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x10)


/** 
 * \brief Direction of GPIOs (output enable)
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_OE
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_OE         VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x11)


/** 
 * \brief Interrupt (GPIO input value change event)
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_INTR
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_INTR       VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x12)


/** 
 * \brief GPIO interrupt enable
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_INTR_ENA
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA   VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x13)


/** 
 * \brief Currently interrupting GPIOs
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_INTR_IDENT
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_IDENT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x14)


/** 
 * \brief GPIO alternate functions
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_ALT
 *
 * @param ri Register: GPIO_ALT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(ri)    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x15 + (ri))

/**
 * Register Group: \a DEVCPU_GCB:MIIM
 *
 * MIIM master controller
 */


/** 
 * \brief MIIM status
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_STATUS
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_STATUS(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x17,gi,9,0,0)

/** 
 * \brief
 * Indicates the current state of the MIIM controller. When read operations
 * are done (no longer busy), then read data is available via the
 * DEVCPU_GCB::MII_DATA register.
 *
 * \details 
 * 0: MIIM controller is in idle state
 * 1: MIIM controller is busy performing MIIM cmd (either read or write
 * cmd)
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_STAT_BUSY
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_BUSY  VTSS_BIT(3)

/** 
 * \brief
 * The MIIM controller has a CMD fifo of depth one. When this field is 0,
 * then it is safe to write another MIIM command to the MIIM controller.
 *
 * \details 
 * 0: Read or write not pending
 * 1: Read or write pending
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_STAT_OPR_PEND
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_OPR_PEND  VTSS_BIT(2)

/** 
 * \brief
 * Indicates whether a read operation via the MIIM interface is in progress
 * or not.
 *
 * \details 
 * 0: Read not in progress
 * 1: Read in progress
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_STAT_PENDING_RD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_PENDING_RD  VTSS_BIT(1)

/** 
 * \brief
 * Indicates whether a write operation via the MIIM interface is in
 * progress or not.
 *
 * \details 
 * 0: Write not in progress
 * 1: Write in progress
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_STAT_PENDING_WR
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_PENDING_WR  VTSS_BIT(0)

/** 
 * \brief
 * Signals if all PHYs have been scanned (with auto scan) at least once.
 *
 * \details 
 * 0: Auto scan has not scanned all PHYs
 * 1: PHYs has been scanned at least once
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_SCAN_COMPLETE
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_SCAN_COMPLETE  VTSS_BIT(4)


/** 
 * \brief MIIM command
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_CMD
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_CMD(gi)     VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x17,gi,9,0,2)

/** 
 * \brief
 * Must be set for starting a new PHY access. This bit is automatically
 * cleared.
 *
 * \details 
 * 0: Write to this register is ignored
 * 1: Write to this register is processed
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_VLD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD  VTSS_BIT(31)

/** 
 * \brief
 * Indicates the addressed PHY number.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_PHYAD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(x)  VTSS_ENCODE_BITFIELD(x,25,5)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD     VTSS_ENCODE_BITMASK(25,5)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(x)  VTSS_EXTRACT_BITFIELD(x,25,5)

/** 
 * \brief
 * Indicates the addressed of the register within the PHY that shall be
 * accessed.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_REGAD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/** 
 * \brief
 * Data to be written in the PHY register.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_WRDATA
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(x)  VTSS_ENCODE_BITFIELD(x,4,16)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA     VTSS_ENCODE_BITMASK(4,16)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(x)  VTSS_EXTRACT_BITFIELD(x,4,16)

/** 
 * \brief
 * Select if scanning of the PHY shall be done once, or scanning should be
 * done continuously.
 *
 * \details 
 * 0: Do continuously PHY scanning 
 * 1: Stop once all PHY have been scanned
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_SINGLE_SCAN
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_SINGLE_SCAN  VTSS_BIT(3)

/** 
 * \brief
 * Indicates type of operation.
 *
 * \details 
 * Clause 22:
 * 
 * 1: Write
 * 2: Read
 * 
 * Clause 45:
 * 
 * 0: Address
 * 1: Write
 * 2: Read inc
 * 3: Read
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_OPR_FIELD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Indicates whether automatic scanning of PHY registers is enabled. When
 * enabled, the PHY-number for each automatic read is continuously
 * round-robined from DEVCPU_GCB::PHY_ADDR_LOW through
 * DEVCPU_GCB::PHY_ADDR_HIGH. This function is started upon a read
 * operation. Scan shall be disabled before reconfiguring the MIIM
 * controller.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_SCAN
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_SCAN  VTSS_BIT(0)


/** 
 * \brief MIIM reply data
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_DATA
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_DATA(gi)    VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x17,gi,9,0,3)

/** 
 * \brief
 * Indicates whether a read operation failed or succeeded.
 *
 * \details 
 * 0: OK
 * 3: Error
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_DATA . MIIM_DATA_SUCCESS
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Data read from PHY register.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_DATA . MIIM_DATA_RDDATA
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MIIM configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_CFG
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x17,gi,9,0,4)

/** 
 * \brief
 * Configures the MIIM clock frequency. This is computed as
 * system_clk/(2*(1+X)), where X is the value written to this register.
 * Note : Setting X to 0 is invalid and will result in the same frequency
 * as setting X to 1.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CFG . MIIM_CFG_PRESCALE
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_CFG_PRESCALE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CFG_MIIM_CFG_PRESCALE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CFG_MIIM_CFG_PRESCALE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * The ST (start-of-frame) field of the MIIM frame format adopts the value
 * of this field. This must be configured for either clause 22 or 45 MIIM
 * operation.
 *
 * \details 
 * 0: Clause 45
 * 1: Clause 22
 * Other values are reserved.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CFG . MIIM_ST_CFG_FIELD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,9,2)


/** 
 * \brief MIIM scan 0
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_0
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_SCAN_0(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x17,gi,9,0,5)

/** 
 * \brief
 * Indicates the high PHY number to scan during automatic scanning.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_SCAN_0 . MIIM_SCAN_PHYADHI
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADHI(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADHI     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADHI(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Indicates the low PHY number to scan during automatic scanning.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_SCAN_0 . MIIM_SCAN_PHYADLO
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADLO(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADLO     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADLO(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief MIIM scan 1
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_1
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_SCAN_1(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x17,gi,9,0,6)

/** 
 * \brief
 * Indicates the mask for comparing the PHY registers during automatic
 * scan.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_SCAN_1 . MIIM_SCAN_MASK
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_MASK(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_MASK     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Indicates the expected value for comparing the PHY registers during
 * automatic scan.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_SCAN_1 . MIIM_SCAN_EXPECT
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_EXPECT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_EXPECT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_EXPECT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MIIM results
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_LAST_RSLTS
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_SCAN_LAST_RSLTS(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x17,gi,9,0,7)


/** 
 * \brief MIIM results valid
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_LAST_RSLTS_VLD
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_SCAN_LAST_RSLTS_VLD(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x17,gi,9,0,8)

/**
 * Register Group: \a DEVCPU_GCB:MIIM_READ_SCAN
 *
 * MIIM master controller scan results
 */


/** 
 * \brief MIIM results sticky
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM_READ_SCAN:MII_SCAN_RSLTS_STICKY
 *
 * @param ri Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_READ_SCAN_MII_SCAN_RSLTS_STICKY(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x29 + (ri))

/**
 * Register Group: \a DEVCPU_GCB:TEMP_SENSOR
 *
 * Temperature sensor control
 */


/** 
 * \brief Temperature sensor control
 *
 * \details
 * Register: \a DEVCPU_GCB:TEMP_SENSOR:TEMP_SENSOR_CTRL
 */
#define VTSS_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_CTRL  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x2b)

/** 
 * \brief
 * Set to power down the temperature sensor.
 *
 * \details 
 * 0: Normal operation
 * 1: Power down mode
 *
 * Field: ::VTSS_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_CTRL . TEMP_SENSOR_POWER_DOWN
 */
#define  VTSS_F_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_CTRL_TEMP_SENSOR_POWER_DOWN  VTSS_BIT(1)

/** 
 * \brief
 * Set to release temperature sensor from reset.
 *
 * \details 
 * 0: Reset state
 * 1: Normal operation
 *
 * Field: ::VTSS_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_CTRL . TEMP_SENSOR_RESET_N
 */
#define  VTSS_F_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_CTRL_TEMP_SENSOR_RESET_N  VTSS_BIT(0)


/** 
 * \brief Temperature sensor data
 *
 * \details
 * Register: \a DEVCPU_GCB:TEMP_SENSOR:TEMP_SENSOR_DATA
 */
#define VTSS_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_DATA  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x2c)

/** 
 * \brief
 * Set when data from the temperature sensor is valid.
 * It will take some time after enabling the temperature sensor until it
 * returns valid data.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_DATA . TEMP_SENSOR_DATA_VALID
 */
#define  VTSS_F_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_DATA_TEMP_SENSOR_DATA_VALID  VTSS_BIT(8)

/** 
 * \brief
 * Temperature data readout, this field is valid when
 * DEVCPU_GCB::TEMP_SENSOR_DATA.TEMP_SENSOR_DATA_VALID is set. Once valid
 * data is returned then it will continually be updated until the
 * temperature sensor is put into power down or reset (see
 * DEVCPU_GCB::TEMP_SENSOR_CTRL for more information). This value is read
 * directly from another clock domain, keep reading field value until same
 * value is returned on two sucessive reads.
 *
 * \details 
 * TEMP = 42.5 - ((2*(TEMP_SENSOR_DATA-169))/1.88) 
 *
 * Field: ::VTSS_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_DATA . TEMP_SENSOR_DATA
 */
#define  VTSS_F_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_DATA_TEMP_SENSOR_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_DATA_TEMP_SENSOR_DATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_TEMP_SENSOR_TEMP_SENSOR_DATA_TEMP_SENSOR_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a DEVCPU_GCB:SIO_CTRL
 *
 * Serial IO control configuration
 */


/** 
 * \brief Last value at SGPIO pins
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INPUT_DATA
 *
 * @param ri Replicator: x_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INPUT_DATA(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x2d + (ri))


/** 
 * \brief SGPIO interrupt polarity
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INT_POL
 *
 * @param ri Replicator: x_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INT_POL(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x31 + (ri))


/** 
 * \brief SGPIO interrupt enable per port
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PORT_INT_ENA
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_INT_ENA  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x35)


/** 
 * \brief Output configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PORT_CONFIG
 *
 * @param ri Replicator: x_SIO_PORT_CNT (??), 0-31
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x36 + (ri))

/** 
 * \brief
 * Output source select for the four outputs from each port.The source
 * select is encoded using three bits for each output bit: Output bit0 is
 * defined by (2 downto 0), output bit1 is defined by (5 downto 3), output
 * bit2 is defined by (8 downto 6), and output bit3 is defined by (11
 * downto 9).
 *
 * \details 
 * 0: Forced 0
 * 1: Forced 1
 * 2: Blink mode 0
 * 3: Blink mode 1
 * 4: Link activity blink mode 0
 * 5: Link activity blink mode 1
 * 6: Link activity blink mode 0 inversed polarity
 * 7: Link activity blink mode 1 inversed polarity
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG . BIT_SOURCE
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG_BIT_SOURCE(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG_BIT_SOURCE     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG_BIT_SOURCE(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Port enable
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PORT_ENABLE
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_ENABLE  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x56)


/** 
 * \brief General configurations
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_CONFIG
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x57)

/** 
 * \brief
 * Configuration for blink mode 1.
 * Supports three different blink modes and a "burst toggle" mode in which
 * blink mode 1 will alternate for each burst.
 *
 * \details 
 * 0: Blink freq appr. 20Hz
 * 1: Blink freq appr. 10Hz
 * 2: Blink freq appr. 5Hz
 * 3: Burst toggle
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BMODE_1
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Configuration of blink mode 0. Supports four different blink modes.
 *
 * \details 
 * 0: Blink freq appr. 20Hz
 * 1: Blink freq appr. 10Hz
 * 2: Blink freq appr. 5Hz
 * 3: Blink freq appr. 2.5Hz
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BMODE_0
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_0(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_0     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_0(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Reset the blink counters. Used to synchronize the blink modes between
 * different chips.
 *
 * \details 
 * 0: Blink counter is running
 * 1: Blink counter is reset until sio_blink_reset is unset again
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BLINK_RESET
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BLINK_RESET  VTSS_BIT(17)

/** 
 * \brief
 * Bit interrupt enable. Enables interrupts for the four gpios in a port.
 * Is applied to all ports.
 *
 * \details 
 * 0: Interrupt is disabled for bit n for all ports
 * 1: Interrupt is enabled for bit n for all ports
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_INT_ENA
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * Set to disable burst gap.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BURST_GAP_DIS
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP_DIS  VTSS_BIT(12)

/** 
 * \brief
 * Configures the length of burst gap in steps of approx. 1 ms. Burst gap
 * can be disabled by setting DEVCPU_GCB::SIO_CONFIG.SIO_BURST_GAP_DIS.
 *
 * \details 
 * 0: 1.05 ms burst gap
 * 1: 2.10 ms burst gap
 * ...
 * 31: 33.55 ms burst gap
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BURST_GAP
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP(x)  VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP     VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP(x)  VTSS_EXTRACT_BITFIELD(x,7,5)

/** 
 * \brief
 * Use this to output a single burst. Will be cleared by hardware when the
 * burst has finished.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_SINGLE_SHOT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_SINGLE_SHOT  VTSS_BIT(6)

/** 
 * \brief
 * Use this to output repeated bursts interleaved with burst gaps. Must be
 * manually reset again to stop output of bursts.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_AUTO_REPEAT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_AUTO_REPEAT  VTSS_BIT(5)

/** 
 * \brief
 * Polarity of the "Ld" signal
 *
 * \details 
 * 0: load signal is active low
 * 1: load signal is active high
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_LD_POLARITY
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_LD_POLARITY  VTSS_BIT(4)

/** 
 * \brief
 * Number of SGPIOs pr. port.
 *
 * \details 
 * 0: 1 gpio pr. port
 * 1: 2 gpios pr. port
 * 2: 3 gpios pr. port
 * 3: 4 gpios pr. port
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_PORT_WIDTH
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_PORT_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_PORT_WIDTH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_PORT_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Reverse the output bitstream.
 * The default order of the output bit stream is (displayed in transmitted
 * order):
 * (portN bit3, portN bit2, ...., port0 bit1, port0 bit0)
 * The reverse order of the output bit stream is (displayed in transmitted
 * order):
 * (port0 bit0, port0 bit1, ...., portN bit2, portN bit3)
 *
 * \details 
 * 0: Do not reverse
 * 1: Reverse
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_REVERSE_OUTPUT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_REVERSE_OUTPUT  VTSS_BIT(1)

/** 
 * \brief
 * Reverse the input bitstream.
 * The default order of the input bit stream is (displayed in received
 * order):
 * (port0 bit0, port0 bit1, ...., portN bit2, portN bit3)
 * The reverse order of the input bit stream is (displayed in received
 * order):
 * (portN bit3, portN bit2, ...., port0 bit1, port0 bit0)
 *
 * \details 
 * 0: Do not reverse
 * 1: Reverse
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_REVERSE_INPUT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_REVERSE_INPUT  VTSS_BIT(0)


/** 
 * \brief SGPIO shift clock frequency
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_CLOCK
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK   VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x58)

/** 
 * \brief
 * SIO controller clock frequency. Divides the 156.25 MHz system clk with
 * value of this field. E.g. the system clk is 156.25 MHz and this field is
 * set to 10, the output frequency will be 15.625 MHz.
 *
 * \details 
 * 0: Disable clock
 * 1: Reserved, do not use
 * Others : Clock divider value.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK . SIO_CLK_FREQ
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Currently interrupting SGPIOs
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INT_REG
 *
 * @param ri Replicator: x_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INT_REG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x59 + (ri))

/**
 * Register Group: \a DEVCPU_GCB:FAN_CFG
 *
 * Fan controller configuration
 */


/** 
 * \brief Fan controller configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:FAN_CFG:FAN_CFG
 */
#define VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG      VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x5d)

/** 
 * \brief
 * Define the duty cycle
 *
 * \details 
 * 0x00: Always "off"
 * 0xFF: Always "on"
 *
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . DUTY_CYCLE
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Set the frquency of the PWM output 
 *
 * \details 
 * 
 * 0: 25 kHz
 * 1: 120 Hz
 * 2: 100 Hz
 * 3: 80 Hz
 * 4: 60 Hz
 * 5: 40 Hz
 * 6: 20 Hz
 * 7: 10 Hz
 *
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . PWM_FREQ
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_FREQ(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_FREQ     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Define the polarity of the PWM output.
 *
 * \details 
 * 0: PWM is logic 1 when "on"
 * 1: PWM is logic 0 when "on"
 *
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . INV_POL
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_INV_POL  VTSS_BIT(3)

/** 
 * \brief
 * Enable gating of the TACH input by the PWM output so that only TACH
 * pulses received when PWM is "on" are counted.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . GATE_ENA
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_GATE_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Configure the PWM output to be open collector
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . PWM_OPEN_COL_ENA
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_OPEN_COL_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Configure behavior of TACH input tick counter, see DEVCPU_GCB::FAN_CNT
 * for more infromation.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . FAN_STAT_CFG
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_FAN_STAT_CFG  VTSS_BIT(0)

/**
 * Register Group: \a DEVCPU_GCB:FAN_STAT
 *
 * Fan controller status
 */


/** 
 * \brief TACH counter
 *
 * \details
 * Register: \a DEVCPU_GCB:FAN_STAT:FAN_CNT
 */
#define VTSS_DEVCPU_GCB_FAN_STAT_FAN_CNT     VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x5e)

/** 
 * \brief
 * Counts the number of TACH input ticks. If
 * DEVCPU_GCB::FAN_CFG.FAN_STAT_CFG is set then this is a wrapping counter
 * that shows the total number of registered TACH ticks. If
 * DEVCPU_GCB::FAN_CFG.FAN_STAT_CFG is cleared then this counter is updated
 * once every second with the number of TACH ticks registered during the
 * last second.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_FAN_STAT_FAN_CNT . FAN_CNT
 */
#define  VTSS_F_DEVCPU_GCB_FAN_STAT_FAN_CNT_FAN_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_FAN_STAT_FAN_CNT_FAN_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_FAN_STAT_FAN_CNT_FAN_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a DEVCPU_GCB:PTP_CFG
 *
 * PTP controller configuation
 */


/** 
 * \brief Misc PTP configurations
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_MISC_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x5f)

/** 
 * \brief
 * Inversion of external sync output.
 *
 * \details 
 * 0: External sync output is not inverted
 * 1: External sync output is inverted
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_OUTP_INV
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_INV(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_INV     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_INV(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * GPIO selection of external sync output.
 *
 * \details 
 * 0: Use generated external clock as external sync output on GPIO 1588
 * PPS0/1
 * 1: Use Master counter reset as external sync output on GPIO 1588 PPS0/1
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_OUTP_SEL
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * External sync output enable.
 *
 * \details 
 * 0: External sync output is disabled
 * 1: External sync output is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_OUTP_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/** 
 * \brief
 * Inversion of external sync input.
 *
 * \details 
 * 0: External sync input is not inverted
 * 1: External sync input is inverted
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_INP_INV
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_INV(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_INV     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_INV(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/** 
 * \brief
 * External sync input enable.
 *
 * \details 
 * 0: External sync input is disabled
 * 1: External sync input is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_INP_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Configure if a synchronization input pulse stores current Master counter
 * value in EXT_SYNC_CURRENT_TIME_STAT.
 *
 * \details 
 * 0: Current Master counter value is not captured
 * 1: Current Master counter value is captured
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_CAP_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_CAP_ENA(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_CAP_ENA     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_CAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Enable synchronization to external sync. If set, the Master counter is
 * reset to the value set in PTP_EXT_SYNC_TIME_CFG.
 *
 * \details 
 * 0: Sync on external signal is disabled
 * 1: Sync on external signal is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Enable master counter.
 *
 * \details 
 * 0: Master counter disabled
 * 1: Master counter enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . PTP_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_PTP_ENA  VTSS_BIT(0)


/** 
 * \brief Master counter upper limit
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_UPPER_LIMIT_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x60)

/** 
 * \brief
 * Counter value where the Master counter should be reset.
 *
 * \details 
 * Unit is ns.

 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG . PTP_UPPER_LIMIT
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG_PTP_UPPER_LIMIT(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG_PTP_UPPER_LIMIT     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG_PTP_UPPER_LIMIT(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief Master counter upper limit one time adjust
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_UPPER_LIMIT_1_TIME_ADJ_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x61)

/** 
 * \brief
 * One time enable for PTP_UPPER_LIMIT_1_TIME_ADJ
 *
 * \details 
 * 0: Normal operation
 * 1: Timer is adjusted by usage of PTP_UPPER_LIMIT_1_TIME_ADJ
 * Bit is cleared by HW
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG . PTP_UPPER_LIMIT_1_TIME_ADJ_SHOT
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_SHOT  VTSS_BIT(30)

/** 
 * \brief
 * Counter value where the Master counter should be reset.
 *
 * \details 
 * Unit is ns.

 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG . PTP_UPPER_LIMIT_1_TIME_ADJ
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief Sync Interrupt enable
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_SYNC_INTR_ENA_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x62)

/** 
 * \brief
 * Interrupt mask. Masks interrupt generation when a synchronization pulse
 * is received on external sync input pin.
 *
 * \details 
 * 0: Interrupt is not generated
 * 1: Interrupt is generated
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG . EXT_SYNC_CURRENT_TIME_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_EXT_SYNC_CURRENT_TIME_ENA(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_EXT_SYNC_CURRENT_TIME_ENA     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_EXT_SYNC_CURRENT_TIME_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Interrupt mask. Masks interrupt generation when Master Timer generates a
 * synchronization pulse.
 *
 * \details 
 * 0: Interrupt is not generated
 * 1: Interrupt is generated
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG . SYNC_STAT_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_SYNC_STAT_ENA  VTSS_BIT(0)


/** 
 * \brief Generated external clock high period
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:GEN_EXT_CLK_HIGH_PERIOD_CFG
 *
 * @param ri Replicator: x_NUM_PTP_GEN_CLKS (??), 0-1
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x63 + (ri))

/** 
 * \brief
 * High period for generated external clock in system clock cycles.
 *
 * \details 
 * N: External clock signal is high for (N+1)*system_clk cycles.
 * E.g. N=999, system clock = 250 MHz which means 4 ns clk period.
 * High Phase is 4 us.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG . GEN_EXT_CLK_HIGH_PERIOD
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief Generated external clock low period
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:GEN_EXT_CLK_LOW_PERIOD_CFG
 *
 * @param ri Replicator: x_NUM_PTP_GEN_CLKS (??), 0-1
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x65 + (ri))

/** 
 * \brief
 * Low period for generated external clock in system clock cycles.
 *
 * \details 
 * N: External clock signal is low for (N+1)*system_clk cycles.
 * E.g. N=999, system clock = 250 MHz which means 4 ns clk period.
 * Low Phase is 4 us.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG . GEN_EXT_CLK_LOW_PERIOD
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief External clock to internal master synchronization configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:GEN_EXT_CLK_CFG
 *
 * @param ri Replicator: x_NUM_PTP_GEN_CLKS (??), 0-1
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x67 + (ri))

/** 
 * \brief
 * Enable sync of generated external clock to PTP sync master.
 *
 * \details 
 * 0: Synchronization is disabled
 * 1: Synchronization is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG . GEN_EXT_CLK_SYNC_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_SYNC_ENA  VTSS_BIT(2)

/** 
 * \brief
 * External clock frequency adjustment enable.
 *
 * \details 
 * 0: Adjustment Disabled
 * 1: Adjustment Enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG . GEN_EXT_CLK_ADJ_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ADJ_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable generated external clock.
 *
 * \details 
 * 0: Generated external clock disabled.
 * 1: Generated external clock enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG . GEN_EXT_CLK_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA  VTSS_BIT(0)


/** 
 * \brief Generated clock adjustment configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:CLK_ADJ_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x69)

/** 
 * \brief
 * Clock frequency adjustment direction.
 *
 * \details 
 * 0: Positive adjustment. Every N system clock cycles, a 1 is added to the
 * counter. => clock period is decreased, clock frequency is increased
 * 1: Negative adjustment. Every N system clock cycles, a 1 is subtracted
 * from the counter. => clock period is increased, clock frequency is
 * decreased
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG . CLK_ADJ_DIR
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_DIR  VTSS_BIT(2)

/** 
 * \brief
 * Clock frequency adjust enable.
 *
 * \details 
 * 0: Adjustment Disabled
 * 1: Adjustment Enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG . CLK_ADJ_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Defines when the updated adjustment value and direction takes effect.
 *
 * \details 
 * 0: updated values take immediate effect
 * 1: updated values take effect after the next sync pulse
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG . CLK_ADJ_UPD
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_UPD  VTSS_BIT(0)


/** 
 * \brief Generated clock frequency adjustment
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:CLK_ADJ_FRQ
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_FRQ  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x6a)

/** 
 * \brief
 * Clock frequency adjust.
 *
 * \details 
 * N: Number of system clock cycles after which the counter for the clock
 * must be adjusted.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_FRQ . CLK_ADJ
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_FRQ_CLK_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_CLK_ADJ_FRQ_CLK_ADJ     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_CLK_ADJ_FRQ_CLK_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief External sync time configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_EXT_SYNC_TIME_CFG
 *
 * @param ri Register: PTP_EXT_SYNC_TIME_CFG (??), 0-1
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_EXT_SYNC_TIME_CFG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x6b + (ri))

/** 
 * \brief
 * The current time is set to the value of this field when a rising edge is
 * seen on the associated external sync input.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_EXT_SYNC_TIME_CFG . EXT_SYNC_TIME
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_EXT_SYNC_TIME_CFG_EXT_SYNC_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_EXT_SYNC_TIME_CFG_EXT_SYNC_TIME     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_EXT_SYNC_TIME_CFG_EXT_SYNC_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,30)

/**
 * Register Group: \a DEVCPU_GCB:PTP_STAT
 *
 * PTP controller status
 */


/** 
 * \brief Current PTP master timer value
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_STAT:PTP_CURRENT_TIME_STAT
 */
#define VTSS_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x6d)

/** 
 * \brief
 * Current master counter value. Unit is 1 ns.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT . PTP_CURRENT_TIME
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT_PTP_CURRENT_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT_PTP_CURRENT_TIME     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT_PTP_CURRENT_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief External sync time status
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_STAT:EXT_SYNC_CURRENT_TIME_STAT
 *
 * @param ri Register: EXT_SYNC_CURRENT_TIME_STAT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x6e + (ri))

/** 
 * \brief
 * Snapshot of current time, when a rising edge was seen in on the external
 * sync input.
 * Note: A new value is only captured when the associated sticky bit is not
 * set.
 *
 * \details 
 * Current time in clock_ticks when the rising edge on the external sync
 * input was seen.
 * Note: This has to be adjusted by 3 clock ticks for synchronizing the
 * signal to core clock.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT . EXT_SYNC_CURRENT_TIME
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT_EXT_SYNC_CURRENT_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT_EXT_SYNC_CURRENT_TIME     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT_EXT_SYNC_CURRENT_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief External sync time events
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_STAT:PTP_EVT_STAT
 */
#define VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x70)

/** 
 * \brief
 * Identifies if the adjust value update has already happened in case the
 * adjustment is only allowed to take place at sync.
 * If update is allowed to take place immediately the sticky bit is unused.
 *
 * \details 
 * 0: updated has not yet happened
 * 1: updated has happened
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT . CLK_ADJ_UPD_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_CLK_ADJ_UPD_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * Sticky bit that indicates a synchronization pulse has been captured on
 * external sync input pin.
 *
 * \details 
 * 0: No Timestamp has been captured
 * 1: New Timestamp has been captured
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT . EXT_SYNC_CURRENT_TIME_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_EXT_SYNC_CURRENT_TIME_STICKY(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_EXT_SYNC_CURRENT_TIME_STICKY     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_EXT_SYNC_CURRENT_TIME_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Master timer has generated a synchronization pulse to the Slave Timers.
 *
 * \details 
 * 0: No master timer wrap happened
 * 1: Master timer wrap happened
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT . SYNC_STAT
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_SYNC_STAT  VTSS_BIT(0)

/**
 * Register Group: \a DEVCPU_GCB:MEMITGR
 *
 * Memory integrity monitor
 */


/** 
 * \brief Monitor control
 *
 * \details
 * Register: \a DEVCPU_GCB:MEMITGR:MEMITGR_CTRL
 */
#define VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_CTRL  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x71)

/** 
 * \brief
 * Setting this field transitions the integrity monitor between operating
 * modes. Transitioning between modes takes time, this field remains set
 * until the new mode is reached. During this time the monitor also reports
 * busy (MEMITGR_MODE.MODE_BUSY is set).
 * From IDLE (MEMITGR_MODE.MODE_IDLE is set) the monitor can transition
 * into either DETECT or LISTEN mode, the DETECT mode is entered if a
 * memory reports an indication - the LISTEN mode is entered if no
 * indications are reported. The first time after reset the monitor will
 * not detect indications, that is; it will transition directly from IDLE
 * to LISTEN mode.
 * From DETECT (MEMITGR_MODE.MODE_DETECT is set) the monitor can transition
 * into either DETECT or LISTEN mode, the DETECT mode is entered if more
 * indications are reported - the LISTEN mode is entered if no more
 * indications are reported.
 * From LISTEN (MEMITGR_MODE.MODE_LISTEN is set) the monitor can transition
 * into IDLE mode.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_CTRL . ACTIVATE
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_CTRL_ACTIVATE  VTSS_BIT(0)


/** 
 * \brief Monitor status
 *
 * \details
 * Register: \a DEVCPU_GCB:MEMITGR:MEMITGR_STAT
 */
#define VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x72)

/** 
 * \brief
 * If this field is set then there is an indication from one of the
 * memories that needs to be analyzed. An indication is either a parity
 * detection or an error correction.
 * This field is only set when the monitor is in LISTEN mode
 * (MEMITGR_MODE.MODE_LISTEN is set), in all other states (including BUSY)
 * this field returns 0.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . INDICATION
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_INDICATION  VTSS_BIT(4)

/** 
 * \brief
 * This field is set when the monitor is in LISTEN mode, during listen mode
 * the monitor continually check for parity/correction indications from the
 * memories.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . MODE_LISTEN
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_MODE_LISTEN  VTSS_BIT(3)

/** 
 * \brief
 * This field is set when the monitor is in DETECT mode, during detect mode
 * the MEMITGR_INFO register contains valid information about one
 * indication.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . MODE_DETECT
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_MODE_DETECT  VTSS_BIT(2)

/** 
 * \brief
 * This field is set when the monitor is in IDLE mode.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . MODE_IDLE
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_MODE_IDLE  VTSS_BIT(1)

/** 
 * \brief
 * The busy signal is a copy of the MEMITGR_CTRL.ACTIVATE field, see
 * description of that field for more information about the different
 * states/modes of the monitor.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . MODE_BUSY
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_MODE_BUSY  VTSS_BIT(0)


/** 
 * \brief Memory indication
 *
 * \details
 * This field is only valid when the monitor is in the DETECT
 * (MEMITGR_MODE.MODE_DETECT is set) mode.
 *
 * Register: \a DEVCPU_GCB:MEMITGR:MEMITGR_INFO
 */
#define VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x73)

/** 
 * \brief
 * This field is set if the monitor has detected a parity indication (or an
 * unrecoverable correction).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_ERR
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ERR  VTSS_BIT(31)

/** 
 * \brief
 * This field is set if the monitor has detected a correction.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_COR
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_COR  VTSS_BIT(30)

/** 
 * \brief
 * This field is set if the monitor has detected a parity indication (or an
 * unrecoverable correction) for which the address has not been recorded.
 * If MEMITGR_INFO.MEM_ERR is set then there has been more than one
 * indication, then only the address of the newest indication has been
 * kept. 
 * If MEMITGR_INFO.MEM_ERR is cleared then an indication has occurred for
 * which the address could not be stored, this is a very rare situation
 * that can only happen if an indication is detected just as the memory is
 * talking to the monitor.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_ERR_OVF
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ERR_OVF  VTSS_BIT(29)

/** 
 * \brief
 * This field is set if the monitor has correction indication for which the
 * address has not been recorded.
 * If MEMITGR_INFO.MEM_ERR is set then there has also been a parity
 * indication (or an unrecoverable correction) which takes priority over
 * correction indications.
 * If MEMITGR_INFO.MEM_ERR is cleared and MEMITGR_INFO.MEM_COR is set then
 * there has been more than one correction indication, then only the
 * address of the newest correction indication has been kept.
 * If MEMITGR_INFO.MEM_ERR and MEMITGR_INFO.MEM_COR is both cleared then a
 * correction indication has occurred for which the address could not be
 * stored, this is a very rare situaltion that can only happen if an
 * indication is detected just as the memory is talking to the monitor.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_COR_OVF
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_COR_OVF  VTSS_BIT(28)

/** 
 * \brief
 * This field is valid only when MEMITGR.MEM_ERR or MEMITGR.MEM_COR is set.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_ADDR
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ADDR     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Memory index
 *
 * \details
 * This field is only valid when the monitor is in the DETECT
 * (MEMITGR_MODE.MODE_DETECT is set) mode.
 *
 * Register: \a DEVCPU_GCB:MEMITGR:MEMITGR_IDX
 */
#define VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_IDX  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x74)

/** 
 * \brief
 * This field contains a unique index for the memory for which info is
 * currently provided in MEMITGR_MEMINFO. Indexes are counted from 1 (not
 * 0).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_IDX . MEM_IDX
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_IDX_MEM_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_MEMITGR_MEMITGR_IDX_MEM_IDX     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_MEMITGR_MEMITGR_IDX_MEM_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a DEVCPU_GCB:VRAP
 *
 * VRAP controller
 */


/** 
 * \brief VRAP events
 *
 * \details
 * Register: \a DEVCPU_GCB:VRAP:VRAP_ACCESS_STAT
 */
#define VTSS_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x77)

/** 
 * \brief
 * This field is set if a valid VRAP (Vitesse Register Access Protocol)
 * frame has been received.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT . FRM_RECV_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT_FRM_RECV_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * This field is set if an invalid command inside a valid VRAP frame has
 * been received. The VRAP engine has ignored the command.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT . CMD_INVALID_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT_CMD_INVALID_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * This field is set if an invalid VRAP frame has been received and
 * discarded by the VRAP-engine. Frames with a VRAP header different from
 * V1 are considered invalid.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT . FRM_INVALID_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT_FRM_INVALID_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * This field is set if a VRAP reply frame has been aborted. This my happen
 * if a protocol violation is detected during VRAP request frame
 * processing.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT . REPLY_ABORT_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_VRAP_VRAP_ACCESS_STAT_REPLY_ABORT_STICKY  VTSS_BIT(0)


#endif /* _VTSS_SERVAL_REGS_DEVCPU_GCB_H_ */
