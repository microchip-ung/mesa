// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_PCIE_DBI_H_
#define _VTSS_LAGUNA_REGS_PCIE_DBI_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a PCIE_DBI
 *
 * DWC PCIE-EP Memory Map
 *
 ***********************************************************************/

/**
 * Register Group: \a PCIE_DBI:PF0_TYPE0_HDR
 *
 * PF PCI-Compatible Configuration Space Header Type0
 */


/**
 * \brief This register holds the device ID, next offset pointer for RCRB mode and vendor ID.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:DEVICE_ID_VENDOR_ID_REG
 */
#define VTSS_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x0)

/**
 * \brief
 * Vendor ID.
 * The Vendor ID register identifies the manufacturer of the Function.
 * Valid vendor identifiers are allocated by the PCI-SIG to ensure
 * uniqueness. It is not permitted to populate this register with a value
 * of FFFFh, which is an invalid value for Vendor ID.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG . PCI_TYPE0_VENDOR_ID
 */
#define  VTSS_F_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG_PCI_TYPE0_VENDOR_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG_PCI_TYPE0_VENDOR_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG_PCI_TYPE0_VENDOR_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 *  - DEVICE_ID [31:16]
 *  - The Device ID register identifies the particular Function for PCIe
 * Type0 and Type1 configuration header. This identifier is allocated by
 * the vendor.
 * Databook.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG . PCI_TYPE0_DEVICE_ID
 */
#define  VTSS_F_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG_PCI_TYPE0_DEVICE_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG_PCI_TYPE0_DEVICE_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_DEVICE_ID_VENDOR_ID_REG_PCI_TYPE0_DEVICE_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register provides the status and controls the behavior of a function.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:STATUS_COMMAND_REG
 */
#define VTSS_PCIE_DBI_STATUS_COMMAND_REG     VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1)

/**
 * \brief
 * IO Space Enable.
 * Controls a Function's response to I/O Space accesses.
 *  - When this bit is set, the Function is enabled to decode the address
 * and further process I/O Space accesses.
 *  - When this bit is clear, all received I/O accesses are caused to be
 * handled as Unsupported Requests.
 * For a Function that does not support I/O Space accesses, the controller
 * hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: !has_io_bar ? RO : RW
 *  - Dbi: !has_io_bar ? RO : RW
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE0_IO_EN
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_IO_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_IO_EN  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_IO_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Memory Space Enable.
 * Controls a Function's response to Memory Space accesses.
 *  - When this bit is set, the Function is enabled to decode the address
 * and further process Memory Space accesses.
 *  - When this bit is clear, all received Memory Space accesses are caused
 * to be handled as Unsupported Requests.
 * For a Function does not support Memory Space accesses, the controller
 * hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: !has_mem_bar ? RO : RW
 *  - Dbi: !has_mem_bar ? RO : RW
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE0_MEM_SPACE_EN
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_MEM_SPACE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_MEM_SPACE_EN  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_MEM_SPACE_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Bus Master Enable.
 * Controls the ability of a Function to issue Memory and I/O Read/Write
 * requests.
 *  - When this bit is set, the Function is allowed to issue Memory or I/O
 * Requests.
 *  - When this bit is clear, the Function is not allowed to issue any
 * Memory or I/O Requests.
 * Requests other than Memory or I/O Requests are not controlled by this
 * bit.
 *
 * Note: MSI/MSI-X interrupt Messages are in-band memory writes, setting
 * the Bus Master Enable bit to 0b disables MSI/MSI-X interrupt Messages as
 * well.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE0_BUS_MASTER_EN
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_BUS_MASTER_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_BUS_MASTER_EN  VTSS_BIT(2)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_BUS_MASTER_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Special Cycle Enable.
 * This bit was originally described in the PCI Local Bus Specification.
 * Its functionality does not apply to PCI Express. The controller
 * hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE0_SPECIAL_CYCLE_OPERATION
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_SPECIAL_CYCLE_OPERATION(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_SPECIAL_CYCLE_OPERATION  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_SPECIAL_CYCLE_OPERATION(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Memory Write and Invalidate.
 * This bit was originally described in the PCI Local Bus Specification and
 * the
 * PCI-to-PCI Bridge architecture specification. Its functionality does not
 * apply
 * to PCI Express, the controller hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE_MWI_ENABLE
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_MWI_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_MWI_ENABLE  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_MWI_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * VGA Palette Snoop.
 * This bit was originally described in the PCI Local Bus Specification and
 * the PCI-to-PCI Bridge architecture specification. Its functionality does
 * not apply to PCI Express, the controller hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE_VGA_PALETTE_SNOOP
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_VGA_PALETTE_SNOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_VGA_PALETTE_SNOOP  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_VGA_PALETTE_SNOOP(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Parity Error Response.
 * This bit controls the logging of poisoned TLPs in the Master Data Parity
 * Error bit in the Status register.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE0_PARITY_ERR_EN
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_PARITY_ERR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_PARITY_ERR_EN  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_PARITY_ERR_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * IDSEL Stepping/Wait Cycle Control.
 * This bit was originally described in the PCI Local Bus Specification.
 * Its functionality does not apply to PCI Express. The controller
 * hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE_IDSEL_STEPPING
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_IDSEL_STEPPING(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_IDSEL_STEPPING  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_IDSEL_STEPPING(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SERR# Enable.
 * When set, this bit enables reporting upstream of Non-fatal and Fatal
 * errors detected by the Function.
 *
 * Note: The errors are reported if enabled either through this bit or
 * through the PCI Express specific bits in the Device Control register.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE0_SERREN
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_SERREN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_SERREN  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_SERREN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Interrupt Disable.
 * Controls the ability of a Function to generate INTx emulation
 * interrupts.
 *
 *  When set, Functions are prevented from asserting INTx interrupts.
 *
 * Note:
 *
 *  Any INTx emulation interrupts already asserted by the Function must be
 * de-asserted when this bit is Set. INTx interrupts use virtual wires that
 * must, if asserted, be de-asserted using the appropriate Deassert_INTx
 * message(s) when this bit is set.
 *
 *  Only the INTx virtual wire interrupt(s) associated with the Function(s)
 * for which this bit is set are affected.
 *
 *  For functions that generate INTx interrupts, this bit is required. For
 * functions that do not generate INTx interrupts, this bit is optional.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE0_INT_EN
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_INT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_INT_EN  VTSS_BIT(10)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE0_INT_EN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Reserved.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . PCI_TYPE_RESERV
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_RESERV(x)  VTSS_ENCODE_BITFIELD(x,11,5)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_RESERV     VTSS_ENCODE_BITMASK(11,5)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_PCI_TYPE_RESERV(x)  VTSS_EXTRACT_BITFIELD(x,11,5)

/**
 * \brief
 * Emulation interrupt pending.
 * When set, indicates that an INTx emulation interrupt is pending
 * internally in the Function. Setting the Interrupt Disable bit has no
 * effect on the state of this bit. For Functions that do not generate INTx
 * interrupts, the controller hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . INT_STATUS
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_INT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_INT_STATUS  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_INT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Capabilities List.
 * Indicates the presence of an Extended Capability list item. Since all
 * PCI Express device Functions are required to implement the PCI Express
 * Capability structure, the controller hardwires this bit to 1b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . CAP_LIST
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_CAP_LIST(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_CAP_LIST  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_CAP_LIST(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * 66MHz Capable.
 * This bit was originally described in the PCI Local Bus Specification.
 * Its functionality does not apply to PCI Express. The controller
 * hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . FAST_66MHZ_CAP
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_FAST_66MHZ_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_FAST_66MHZ_CAP  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_FAST_66MHZ_CAP(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Fast Back to Back Transaction Capable.
 * This bit was originally described in the PCI Local Bus Specification.
 * Its functionality does not apply to PCI Express. The controller
 * hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . FAST_B2B_CAP
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_FAST_B2B_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_FAST_B2B_CAP  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_FAST_B2B_CAP(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Master Data Parity Error.
 * This bit is set by a Function if the Parity Error Response bit in the
 * Command register is 1b and either of the following two conditions
 * occurs:
 *  - Function receives a Poisoned Completion
 *  - Function transmits a Poisoned Request
 * If the Parity Error Response bit is 0b, this bit is never set.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . MASTER_DPE
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_MASTER_DPE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_MASTER_DPE  VTSS_BIT(24)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_MASTER_DPE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * DEVSEL Timing.
 * This field was originally described in the PCI Local Bus Specification.
 * Its functionality does not apply to PCI Express. The controller
 * hardwires this field to 00b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . DEV_SEL_TIMING
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_DEV_SEL_TIMING(x)  VTSS_ENCODE_BITFIELD(x,25,2)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_DEV_SEL_TIMING     VTSS_ENCODE_BITMASK(25,2)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_DEV_SEL_TIMING(x)  VTSS_EXTRACT_BITFIELD(x,25,2)

/**
 * \brief
 * Signaled Target Abort.

 *
 * \details
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . SIGNALED_TARGET_ABORT
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_SIGNALED_TARGET_ABORT(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_SIGNALED_TARGET_ABORT  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_SIGNALED_TARGET_ABORT(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Received Target Abort.

 *
 * \details
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . RCVD_TARGET_ABORT
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_RCVD_TARGET_ABORT(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_RCVD_TARGET_ABORT  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_RCVD_TARGET_ABORT(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Received Master Abort.

 *
 * \details
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . RCVD_MASTER_ABORT
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_RCVD_MASTER_ABORT(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_RCVD_MASTER_ABORT  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_RCVD_MASTER_ABORT(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Signaled System Error.

 *
 * \details
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . SIGNALED_SYS_ERR
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_SIGNALED_SYS_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_SIGNALED_SYS_ERR  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_SIGNALED_SYS_ERR(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Detected Parity Error.

 *
 * \details
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_STATUS_COMMAND_REG . DETECTED_PARITY_ERR
 */
#define  VTSS_F_PCIE_DBI_STATUS_COMMAND_REG_DETECTED_PARITY_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_STATUS_COMMAND_REG_DETECTED_PARITY_ERR  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_STATUS_COMMAND_REG_DETECTED_PARITY_ERR(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief This register specifies the class code and revision ID of a function.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:CLASS_CODE_REVISION_ID
 */
#define VTSS_PCIE_DBI_CLASS_CODE_REVISION_ID  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2)

/**
 * \brief
 * Revision ID.
 * The value in this register specifies a Function specific revision
 * identifier. The value is chosen by the vendor. Zero is an acceptable
 * value. The Revision ID should be viewed as a vendor defined extension to
 * the Device ID.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CLASS_CODE_REVISION_ID . REVISION_ID
 */
#define  VTSS_F_PCIE_DBI_CLASS_CODE_REVISION_ID_REVISION_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_CLASS_CODE_REVISION_ID_REVISION_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_CLASS_CODE_REVISION_ID_REVISION_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Programming Interface.
 * This field identifies a specific register-level programming interface
 * (if any) so that device independent software can interact with the
 * Function.
 * Encodings for interface are provided in the PCI Code and ID Assignment
 * Specification. All unspecified encodings are Reserved.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CLASS_CODE_REVISION_ID . PROGRAM_INTERFACE
 */
#define  VTSS_F_PCIE_DBI_CLASS_CODE_REVISION_ID_PROGRAM_INTERFACE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_CLASS_CODE_REVISION_ID_PROGRAM_INTERFACE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_CLASS_CODE_REVISION_ID_PROGRAM_INTERFACE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Sub-Class Code.
 * Specifies a base class sub-class, which identifies more specifically the
 * operation of the Function.
 * Encodings for sub-class are provided in the PCI Code and ID Assignment
 * Specification. All unspecified encodings are Reserved.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CLASS_CODE_REVISION_ID . SUBCLASS_CODE
 */
#define  VTSS_F_PCIE_DBI_CLASS_CODE_REVISION_ID_SUBCLASS_CODE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_CLASS_CODE_REVISION_ID_SUBCLASS_CODE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_CLASS_CODE_REVISION_ID_SUBCLASS_CODE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Base Class Code.
 * A code that broadly classifies the type of operation the Function
 * performs.
 * Encodings for base class, are provided in the PCI Code and ID Assignment
 * Specification. All unspecified encodings are Reserved.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CLASS_CODE_REVISION_ID . BASE_CLASS_CODE
 */
#define  VTSS_F_PCIE_DBI_CLASS_CODE_REVISION_ID_BASE_CLASS_CODE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_CLASS_CODE_REVISION_ID_BASE_CLASS_CODE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_CLASS_CODE_REVISION_ID_BASE_CLASS_CODE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief This register provides the status and controls BIST. It also holds information regarding the header layout, latency timer, and cache line size.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG
 */
#define VTSS_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x3)

/**
 * \brief
 * Cache Line Size.
 * The Cache Line Size register is programmed by the system firmware or the
 * operating system to system cache line size. However, legacy conventional
 * PCI software may not always be able to program this register correctly
 * especially in the case of Hot-Plug devices. This read-write register is
 * implemented for legacy compatibility purposes but has no effect on any
 * PCI Express device
 * behavior.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG . CACHE_LINE_SIZE
 */
#define  VTSS_F_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_CACHE_LINE_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_CACHE_LINE_SIZE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_CACHE_LINE_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Latency Timer.
 * The Latency Timer was originally described in the PCI Local Bus
 * Specification and the PCI-to-PCI Bridge Architecture Specification. Its
 * functionality does not apply to PCI Express. The controller hardwires
 * this register to 00h.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG . LATENCY_MASTER_TIMER
 */
#define  VTSS_F_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_LATENCY_MASTER_TIMER(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_LATENCY_MASTER_TIMER     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_LATENCY_MASTER_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Header Layout.
 * This field identifies the layout of the second part of the predefined
 * header.
 * The controller uses 000 0000b encoding.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG . HEADER_TYPE
 */
#define  VTSS_F_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_HEADER_TYPE(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_HEADER_TYPE     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_HEADER_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Multi-Function Device.
 * Except where stated otherwise, it is recommended that this bit be set if
 * there are multiple Functions, and clear if there is only one Function.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG . MULTI_FUNC
 */
#define  VTSS_F_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_MULTI_FUNC(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_MULTI_FUNC  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_MULTI_FUNC(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * BIST.
 * This register is used for control and status of BIST. For Functions that
 * do not support BIST the controller hardwires the register to 00h. A
 * Function whose BIST is invoked must not prevent normal operation of the
 * PCI Express Link.
 * Bit descriptions:
 *  - [31]: BIST Capable.
 * When Set, this bit indicates that the Function supports BIST. When
 * Clear, the Function does not support BIST.
 *  - [30]: Start BIST.
 * If BIST Capable is Set, Set this bit to invoke BIST. The Function resets
 * the bit when BIST is complete. Software is permitted to fail the device
 * if this bit is not Clear (BIST is not complete) 2 seconds after it had
 * been Set. Writing this bit to 0b has no effect. This bit must be
 * hardwired to 0b if BIST Capable is Clear.
 *  - [29:28]: Reserved.
 *  - [27:24]: Completion Code.
 * This field encodes the status of the most recent test. A value of 0000b
 * means that the Function has passed its test. Non-zero values mean the
 * Function failed. Function-specific failure codes can be encoded in the
 * non-zero values. This field's value is only meaningful when BIST Capable
 * is Set and Start BIST is Clear. This field must be hardwired to 0000b if
 * BIST Capable is clear.

 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG . BIST
 */
#define  VTSS_F_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_BIST(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_BIST     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG_BIST(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief System software must build a consistent address map before booting the machine to an operating system. This means it has to determine how much memory is in the system, and how much address space the Functions in the system require. After determining this information, system software can map the Functions into reasonable locations and proceed with system boot. In order to do this mapping in a device-independent manner, the base registers for this mapping are placed in the predefined header portion of Configuration Space. It is strongly recommended that power-up firmware/software also support the optional Enhanced Configuration Access Mechanism (ECAM).
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:BAR0_REG
 */
#define VTSS_PCIE_DBI_BAR0_REG               VTSS_IOREG(VTSS_TO_PCIE_DBI,0x4)

/**
 * \brief
 *  - BAR0 Memory Space Indicator.
 *  - This bit is used to determine whether the register maps into Memory
 * or I/O Space. Base Address registers that map to Memory Space must
 * return a 0b.
 *  - Base Address registers that map to I/O Space must return a 1b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR0_REG . BAR0_MEM_IO
 */
#define  VTSS_F_PCIE_DBI_BAR0_REG_BAR0_MEM_IO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR0_REG_BAR0_MEM_IO  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR0_REG_BAR0_MEM_IO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 *  -  BAR0 Type.
 *  - Memory Space: Base Address registers that map into Memory Space can
 * be 32 bits or 64 bits wide (to support mapping into a 64-bit address
 * space). The encodings defined in Values: apply.
 *  - IO Space: Bit 1 is reserved and must return 0b on reads. Bits[31:2]
 * are used to map the function into IO space. The encodings defined in
 * Values: do not apply.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h2:
 * 'h1:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_BAR0_REG . BAR0_TYPE
 */
#define  VTSS_F_PCIE_DBI_BAR0_REG_BAR0_TYPE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_PCIE_DBI_BAR0_REG_BAR0_TYPE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_PCIE_DBI_BAR0_REG_BAR0_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 *  - BAR0 Prefetchable.
 *
 * Memory Space: Set to one if data is prefetchable.
 *
 * A Function is permitted to mark a range as prefetchable. If there are no
 * side effects on reads, the function returns all bytes on reads
 * regardless of the byte enables, and host bridges can merge processor
 * writes into this range without causing errors. Bit must me clear
 * otherwise.
 *
 * IO Space: Not applicable.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR0_REG . BAR0_PREFETCH
 */
#define  VTSS_F_PCIE_DBI_BAR0_REG_BAR0_PREFETCH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_BAR0_REG_BAR0_PREFETCH  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_BAR0_REG_BAR0_PREFETCH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 *  - BAR0_START. BAR0 Base Address.
 *  - Memory Space: Base Address.
 *  - IO Space: bits[31:2] are used to map the function into IO space/Base
 * Address.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 *  - Dbi: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR0_REG . BAR0_START
 */
#define  VTSS_F_PCIE_DBI_BAR0_REG_BAR0_START(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_PCIE_DBI_BAR0_REG_BAR0_START     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_PCIE_DBI_BAR0_REG_BAR0_START(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/**
 * \brief System software must build a consistent address map before booting the machine to an operating system. This means it has to determine how much memory is in the system, and how much address space the Functions in the system require. After determining this information, system software can map the Functions into reasonable locations and proceed with system boot. In order to do this mapping in a device-independent manner, the base registers for this mapping are placed in the predefined header portion of Configuration Space. It is strongly recommended that power-up firmware/software also support the optional Enhanced Configuration Access Mechanism (ECAM).
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:BAR1_REG
 */
#define VTSS_PCIE_DBI_BAR1_REG               VTSS_IOREG(VTSS_TO_PCIE_DBI,0x5)

/**
 * \brief
 *  - BAR1 Memory Space Indicator.
 *  - This bit is used to determine whether the register maps into Memory
 * or I/O Space. Base Address registers that map to Memory Space must
 * return a 0b.
 *  - Base Address registers that map to I/O Space must return a 1b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR1_REG . BAR1_MEM_IO
 */
#define  VTSS_F_PCIE_DBI_BAR1_REG_BAR1_MEM_IO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR1_REG_BAR1_MEM_IO  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR1_REG_BAR1_MEM_IO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 *  - BAR1 Type.
 *  - Memory Space: Base Address registers that map into Memory Space can
 * be 32 bits or 64 bits wide (to support mapping into a 64-bit address
 * space). The encodings defined in Values: apply.
 *  - IO Space: Bit 1 is reserved and must return 0b on reads. Bits[31:2]
 * are used to map the function into IO space. The encodings defined in
 * Values: do not apply.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h2:
 * 'h1:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_BAR1_REG . BAR1_TYPE
 */
#define  VTSS_F_PCIE_DBI_BAR1_REG_BAR1_TYPE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_PCIE_DBI_BAR1_REG_BAR1_TYPE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_PCIE_DBI_BAR1_REG_BAR1_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 *  - BAR1 Prefetchable.
 *
 * Memory Space: Set to one if data is prefetchable.
 *
 * A Function is permitted to mark a range as prefetchable. If there are no
 * side effects on reads, the function returns all bytes on reads
 * regardless of the byte enables, and host bridges can merge processor
 * writes into this range without causing errors. Bit must me clear
 * otherwise.
 *
 * IO Space: Not applicable.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR1_REG . BAR1_PREFETCH
 */
#define  VTSS_F_PCIE_DBI_BAR1_REG_BAR1_PREFETCH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_BAR1_REG_BAR1_PREFETCH  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_BAR1_REG_BAR1_PREFETCH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 *  - BAR1 Base Address.
 *  - Memory Space: Base Address.
 *  - IO Space: bits[31:2] are used to map the function into IO space/Base
 * Address.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 *  - Dbi: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR1_REG . BAR1_START
 */
#define  VTSS_F_PCIE_DBI_BAR1_REG_BAR1_START(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_PCIE_DBI_BAR1_REG_BAR1_START     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_PCIE_DBI_BAR1_REG_BAR1_START(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/**
 * \brief System software must build a consistent address map before booting the machine to an operating system. This means it has to determine how much memory is in the system, and how much address space the Functions in the system require. After determining this information, system software can map the Functions into reasonable locations and proceed with system boot. In order to do this mapping in a device-independent manner, the base registers for this mapping are placed in the predefined header portion of Configuration Space. It is strongly recommended that power-up firmware/software also support the optional Enhanced Configuration Access Mechanism (ECAM).
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:BAR2_REG
 */
#define VTSS_PCIE_DBI_BAR2_REG               VTSS_IOREG(VTSS_TO_PCIE_DBI,0x6)

/**
 * \brief
 * BAR2 Memory Space Indicator.
 * This bit is used to determine whether the register maps into Memory or
 * I/O Space. Base Address registers that map to Memory Space must return a
 * 0b.
 * Base Address registers that map to I/O Space must return a 1b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR2_REG . BAR2_MEM_IO
 */
#define  VTSS_F_PCIE_DBI_BAR2_REG_BAR2_MEM_IO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR2_REG_BAR2_MEM_IO  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR2_REG_BAR2_MEM_IO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BAR2 Type.
 *  - Memory Space: Base Address registers that map into Memory Space can
 * be 32 bits or 64 bits wide (to support mapping into a 64-bit address
 * space). The encodings defined in Values: apply.
 *  - IO Space: Bit 1 is reserved and must return 0b on reads. Bits[31:2]
 * are used to map the function into IO space. The encodings defined in
 * Values: do not apply.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h2:
 * 'h1:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_BAR2_REG . BAR2_TYPE
 */
#define  VTSS_F_PCIE_DBI_BAR2_REG_BAR2_TYPE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_PCIE_DBI_BAR2_REG_BAR2_TYPE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_PCIE_DBI_BAR2_REG_BAR2_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * BAR2 Prefetchable.
 *  - Memory Space: Set to one if data is prefetchable.
 * A Function is permitted to mark a range as prefetchable. If there are no
 * side effects on reads, the function returns all bytes on reads
 * regardless of the byte enables, and host bridges can merge processor
 * writes into this range without causing errors. Bit must me clear
 * otherwise.
 *  - IO Space: Not applicable
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR2_REG . BAR2_PREFETCH
 */
#define  VTSS_F_PCIE_DBI_BAR2_REG_BAR2_PREFETCH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_BAR2_REG_BAR2_PREFETCH  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_BAR2_REG_BAR2_PREFETCH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * BAR2 Base Address.
 *  - Memory Space: Base Address.
 *  - IO Space: bits[31:2] are used to map the function into IO space/Base.
 * Address.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 *  - Dbi: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR2_REG . BAR2_START
 */
#define  VTSS_F_PCIE_DBI_BAR2_REG_BAR2_START(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_PCIE_DBI_BAR2_REG_BAR2_START     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_PCIE_DBI_BAR2_REG_BAR2_START(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/**
 * \brief System software must build a consistent address map before booting the machine to an operating system. This means it has to determine how much memory is in the system, and how much address space the Functions in the system require. After determining this information, system software can map the Functions into reasonable locations and proceed with system boot. In order to do this mapping in a device-independent manner, the base registers for this mapping are placed in the predefined header portion of Configuration Space. It is strongly recommended that power-up firmware/software also support the optional Enhanced Configuration Access Mechanism (ECAM).
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:BAR3_REG
 */
#define VTSS_PCIE_DBI_BAR3_REG               VTSS_IOREG(VTSS_TO_PCIE_DBI,0x7)

/**
 * \brief
 * BAR3 Memory Space Indicator.
 * This bit is used to determine whether the register maps into Memory or
 * I/O Space. Base Address registers that map to Memory Space must return a
 * 0b.
 * Base Address registers that map to I/O Space must return a 1b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR3_REG . BAR3_MEM_IO
 */
#define  VTSS_F_PCIE_DBI_BAR3_REG_BAR3_MEM_IO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR3_REG_BAR3_MEM_IO  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR3_REG_BAR3_MEM_IO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BAR3 Type.
 *  - Memory Space: Base Address registers that map into Memory Space can
 * be 32 bits or 64 bits wide (to support mapping into a 64-bit address
 * space). The encodings defined in Values: apply.
 *  - IO Space: Bit 1 is reserved and must return 0b on reads. Bits[31:2]
 * are used to map the function into IO space. The encodings defined in
 * Values: do not apply.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h2:
 * 'h1:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_BAR3_REG . BAR3_TYPE
 */
#define  VTSS_F_PCIE_DBI_BAR3_REG_BAR3_TYPE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_PCIE_DBI_BAR3_REG_BAR3_TYPE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_PCIE_DBI_BAR3_REG_BAR3_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * BAR3 Prefetchable.
 *  - Memory Space: Set to one if data is prefetchable.
 * A Function is permitted to mark a range as prefetchable. If there are no
 * side effects on reads, the function returns all bytes on reads
 * regardless of the byte enables, and host bridges can merge processor
 * writes into this range without causing errors. Bit must me clear
 * otherwise.
 *  - IO Space: Not applicable
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR3_REG . BAR3_PREFETCH
 */
#define  VTSS_F_PCIE_DBI_BAR3_REG_BAR3_PREFETCH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_BAR3_REG_BAR3_PREFETCH  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_BAR3_REG_BAR3_PREFETCH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * BAR3 Base Address.
 *  - Memory Space: Base Address.
 *  - IO Space: bits[31:2] are used to map the function into IO space/Base.
 * Address.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 *  - Dbi: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR3_REG . BAR3_START
 */
#define  VTSS_F_PCIE_DBI_BAR3_REG_BAR3_START(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_PCIE_DBI_BAR3_REG_BAR3_START     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_PCIE_DBI_BAR3_REG_BAR3_START(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/**
 * \brief System software must build a consistent address map before booting the machine to an operating system. This means it has to determine how much memory is in the system, and how much address space the Functions in the system require. After determining this information, system software can map the Functions into reasonable locations and proceed with system boot. In order to do this mapping in a device-independent manner, the base registers for this mapping are placed in the predefined header portion of Configuration Space. It is strongly recommended that power-up firmware/software also support the optional Enhanced Configuration Access Mechanism (ECAM).
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:BAR4_REG
 */
#define VTSS_PCIE_DBI_BAR4_REG               VTSS_IOREG(VTSS_TO_PCIE_DBI,0x8)

/**
 * \brief
 * BAR4 Memory Space Indicator.
 * This bit is used to determine whether the register maps into Memory or
 * I/O Space. Base Address registers that map to Memory Space must return a
 * 0b.
 * Base Address registers that map to I/O Space must return a 1b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR4_REG . BAR4_MEM_IO
 */
#define  VTSS_F_PCIE_DBI_BAR4_REG_BAR4_MEM_IO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR4_REG_BAR4_MEM_IO  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR4_REG_BAR4_MEM_IO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BAR4 Type.
 *  - Memory Space: Base Address registers that map into Memory Space can
 * be 32 bits or 64 bits wide (to support mapping into a 64-bit address
 * space). The encodings defined in Values: apply.
 *  - IO Space: Bit 1 is reserved and must return 0b on reads. Bits[31:2]
 * are used to map the function into IO space. The encodings defined in
 * Values: do not apply.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h2:
 * 'h1:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_BAR4_REG . BAR4_TYPE
 */
#define  VTSS_F_PCIE_DBI_BAR4_REG_BAR4_TYPE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_PCIE_DBI_BAR4_REG_BAR4_TYPE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_PCIE_DBI_BAR4_REG_BAR4_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * BAR4 Prefetchable.
 *  - Memory Space: Set to one if data is prefetchable.
 * A Function is permitted to mark a range as prefetchable. If there are no
 * side effects on reads, the function returns all bytes on reads
 * regardless of the byte enables, and host bridges can merge processor
 * writes into this range without causing errors. Bit must me clear
 * otherwise.
 *  - IO Space: Not applicable
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR4_REG . BAR4_PREFETCH
 */
#define  VTSS_F_PCIE_DBI_BAR4_REG_BAR4_PREFETCH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_BAR4_REG_BAR4_PREFETCH  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_BAR4_REG_BAR4_PREFETCH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * BAR4 Base Address.
 *  - Memory Space: Base Address.
 *  - IO Space: bits[31:2] are used to map the function into IO space/Base.
 * Address.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 *  - Dbi: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR4_REG . BAR4_START
 */
#define  VTSS_F_PCIE_DBI_BAR4_REG_BAR4_START(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_PCIE_DBI_BAR4_REG_BAR4_START     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_PCIE_DBI_BAR4_REG_BAR4_START(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/**
 * \brief System software must build a consistent address map before booting the machine to an operating system. This means it has to determine how much memory is in the system, and how much address space the Functions in the system require. After determining this information, system software can map the Functions into reasonable locations and proceed with system boot. In order to do this mapping in a device-independent manner, the base registers for this mapping are placed in the predefined header portion of Configuration Space. It is strongly recommended that power-up firmware/software also support the optional Enhanced Configuration Access Mechanism (ECAM).
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:BAR5_REG
 */
#define VTSS_PCIE_DBI_BAR5_REG               VTSS_IOREG(VTSS_TO_PCIE_DBI,0x9)

/**
 * \brief
 * BAR5 Memory Space Indicator.
 * This bit is used to determine whether the register maps into Memory or
 * I/O Space. Base Address registers that map to Memory Space must return a
 * 0b.
 * Base Address registers that map to I/O Space must return a 1b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR5_REG . BAR5_MEM_IO
 */
#define  VTSS_F_PCIE_DBI_BAR5_REG_BAR5_MEM_IO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR5_REG_BAR5_MEM_IO  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR5_REG_BAR5_MEM_IO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BAR5 Type.
 *  - Memory Space: Base Address registers that map into Memory Space can
 * be 32 bits or 64 bits wide (to support mapping into a 64-bit address
 * space). The encodings defined in Values: apply.
 *  - IO Space: Bit 1 is reserved and must return 0b on reads. Bits[31:2]
 * are used to map the function into IO space. The encodings defined in
 * Values: do not apply.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h2:
 * 'h1:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_BAR5_REG . BAR5_TYPE
 */
#define  VTSS_F_PCIE_DBI_BAR5_REG_BAR5_TYPE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_PCIE_DBI_BAR5_REG_BAR5_TYPE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_PCIE_DBI_BAR5_REG_BAR5_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * BAR5 Prefetchable.
 *  - Memory Space: Set to one if data is prefetchable.
 * A Function is permitted to mark a range as prefetchable. If there are no
 * side effects on reads, the function returns all bytes on reads
 * regardless of the byte enables, and host bridges can merge processor
 * writes into this range without causing errors. Bit must me clear
 * otherwise.
 *  - IO Space: Not applicable
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (BAR_ENABLED == 1) then (if [DBI_RO_WR_EN == 1] then
 * R(Sticky)/W(Sticky) else R(Sticky)) else RO(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR5_REG . BAR5_PREFETCH
 */
#define  VTSS_F_PCIE_DBI_BAR5_REG_BAR5_PREFETCH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_BAR5_REG_BAR5_PREFETCH  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_BAR5_REG_BAR5_PREFETCH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * BAR5 Base Address.
 *  - Memory Space: Base Address.
 *  - IO Space: bits[31:2] are used to map the function into IO space/Base.
 * Address.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 *  - Dbi: R(Sticky)/W(Sticky) if enabled else R(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR5_REG . BAR5_START
 */
#define  VTSS_F_PCIE_DBI_BAR5_REG_BAR5_START(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_PCIE_DBI_BAR5_REG_BAR5_START     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_PCIE_DBI_BAR5_REG_BAR5_START(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/**
 * \brief This register holds the CardBus CIS pointer.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:CARDBUS_CIS_PTR_REG
 */
#define VTSS_PCIE_DBI_CARDBUS_CIS_PTR_REG    VTSS_IOREG(VTSS_TO_PCIE_DBI,0xa)

/**
 * \brief
 * CardBus CIS Pointer.
 * Its functionality does not apply to PCI Express. It must be hardwired to
 * 0000 0000h.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CARDBUS_CIS_PTR_REG . CARDBUS_CIS_POINTER
 */
#define  VTSS_F_PCIE_DBI_CARDBUS_CIS_PTR_REG_CARDBUS_CIS_POINTER(x)  (x)
#define  VTSS_M_PCIE_DBI_CARDBUS_CIS_PTR_REG_CARDBUS_CIS_POINTER     0xffffffff
#define  VTSS_X_PCIE_DBI_CARDBUS_CIS_PTR_REG_CARDBUS_CIS_POINTER(x)  (x)


/**
 * \brief These registers are used to uniquely identify the add-in card or subsystem where the PCI Express component resides. They provide a mechanism for vendors to distinguish their products from one another even though the assemblies may have the same PCI Express component on them (and, therefore, the same Vendor ID and Device ID).
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG
 */
#define VTSS_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xb)

/**
 * \brief
 * Subsystem Vendor ID.
 * Subsystem Vendor IDs can be obtained from the PCI SIG and are used to
 * identify the vendor of the add-in card or subsystem. Values for the
 * Subsystem ID are vendor-specific.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG . SUBSYS_VENDOR_ID
 */
#define  VTSS_F_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG_SUBSYS_VENDOR_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG_SUBSYS_VENDOR_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG_SUBSYS_VENDOR_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Subsystem ID.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG . SUBSYS_DEV_ID
 */
#define  VTSS_F_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG_SUBSYS_DEV_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG_SUBSYS_DEV_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID_REG_SUBSYS_DEV_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register handles the base address and size information for this expansion ROM.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:EXP_ROM_BASE_ADDR_REG
 */
#define VTSS_PCIE_DBI_EXP_ROM_BASE_ADDR_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc)

/**
 * \brief
 * Expansion ROM Enable.
 * This bit controls whether or not the Function accepts accesses to its
 * expansion ROM.
 * The Memory Space Enable bit in the Command register has precedence over
 * the Expansion ROM Enable bit. A Function must claim accesses to its
 * expansion ROM only if both the Memory Space Enable bit and the Expansion
 * ROM Enable bit are set.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: if (EXP_ROM_BAR_MASK_REG.ROM_BAR_ENABLED == 1) then R/W else R
 *  - Dbi: if (EXP_ROM_BAR_MASK_REG.ROM_BAR_ENABLED == 1) then R/W else R
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_EXP_ROM_BASE_ADDR_REG . ROM_BAR_ENABLE
 */
#define  VTSS_F_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_ENABLE  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Expansion ROM Validation Status.
 * When this field is non-zero, it indicates the status of hardware
 * validation of the Expansion ROM contents.
 *  - If the Function does not support validation, this field must be
 * hardwired to 000b.
 *  - It is optional whether an implementation is capable of returning
 * Validation Status values 011b, 101b, 110b, or 111b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: if (EXP_ROM_BAR_MASK_REG.ROM_BAR_ENABLED == 1) then R/W else R
 *  - Dbi: if (EXP_ROM_BAR_MASK_REG.ROM_BAR_ENABLED == 1 && DBI_RO_WR_EN ==
 * 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h5:
 * 'h4:
 * 'h1:
 * 'h7:
 * 'h6:
 * 'h3:
 * 'h2:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_EXP_ROM_BASE_ADDR_REG . ROM_BAR_VALIDATION_STATUS
 */
#define  VTSS_F_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_VALIDATION_STATUS(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_VALIDATION_STATUS     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_VALIDATION_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * Expansion ROM Validation Details.
 * The field contains optional, implementation-specific details associated
 * with Expansion ROM Validation.
 *  - If validation is in progress (Expansion ROM Validation Status is
 * 001b), non-zero values of this field represent implementation-specific
 * indications of the phase of the validation progress (for example, 50%
 * complete). The value 0000b indicates that no validation progress
 * information is provided.
 *  - If validation is completed (Expansion ROM Validation Status 010b to
 * 111b inclusive), non-zero values in this field represent additional
 * implementation-specific information. The value 0000b indicates that no
 * information is provided.
 *  - When validation is supported and this field is not implemented, this
 * field must be hardwired to 0000b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: if (EXP_ROM_BAR_MASK_REG.ROM_BAR_ENABLED == 1) then R/W else R
 *  - Dbi: if (EXP_ROM_BAR_MASK_REG.ROM_BAR_ENABLED == 1 &&  DBI_RO_WR_EN
 * == 1 ) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_EXP_ROM_BASE_ADDR_REG . ROM_BAR_VALIDATION_DETAILS
 */
#define  VTSS_F_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_VALIDATION_DETAILS(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_VALIDATION_DETAILS     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_ROM_BAR_VALIDATION_DETAILS(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Expansion ROM Base Address.
 * Upper 21 bits of the Expansion ROM base address. The number of bits (out
 * of these 21) that a Function actually implements depends on how much
 * address space the Function requires.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: if (EXP_ROM_BAR_MASK_REG.ROM_BAR_ENABLED == 1) then R/W else R
 *  - Dbi: if (EXP_ROM_BAR_MASK_REG.ROM_BAR_ENABLED == 1) then R/W else R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_EXP_ROM_BASE_ADDR_REG . EXP_ROM_BASE_ADDRESS
 */
#define  VTSS_F_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_EXP_ROM_BASE_ADDRESS(x)  VTSS_ENCODE_BITFIELD(x,11,21)
#define  VTSS_M_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_EXP_ROM_BASE_ADDRESS     VTSS_ENCODE_BITMASK(11,21)
#define  VTSS_X_PCIE_DBI_EXP_ROM_BASE_ADDR_REG_EXP_ROM_BASE_ADDRESS(x)  VTSS_EXTRACT_BITFIELD(x,11,21)


/**
 * \brief This register is used to point to a linked list of capabilities implemented by a Function.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:PCI_CAP_PTR_REG
 */
#define VTSS_PCIE_DBI_PCI_CAP_PTR_REG        VTSS_IOREG(VTSS_TO_PCIE_DBI,0xd)

/**
 * \brief
 * Capabilities Pointer. This register points to a valid capability
 * structure. Either this structure is the PCI Express Capability
 * structure, or a subsequent list item points to the PCI Express
 * Capability structure. The bottom two bits are reserved, the controller
 * sets it to 00b. Software must mask these bits off before using this
 * register as a pointer in Configuration Space to the first entry of a
 * linked list of new capabilities.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCI_CAP_PTR_REG . CAP_POINTER
 */
#define  VTSS_F_PCIE_DBI_PCI_CAP_PTR_REG_CAP_POINTER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_PCI_CAP_PTR_REG_CAP_POINTER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_PCI_CAP_PTR_REG_CAP_POINTER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief The Interrupt Line register communicates interrupt line routing information. The Interrupt Pin register identifies the legacy interrupt Message(s) the Function uses.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR:MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG
 */
#define VTSS_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xf)

/**
 * \brief
 * Interrupt Line.
 * The Interrupt Line register communicates interrupt line routing
 * information. The register must be implemented by any Function that uses
 * an interrupt pin.
 * Values in this register are programmed by system software and are system
 * architecture specific. The Function itself does not use this value;
 * rather the value in this register is used by device drivers and
 * operating systems.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG . INT_LINE
 */
#define  VTSS_F_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG_INT_LINE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG_INT_LINE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG_INT_LINE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Interrupt Pin.
 * The Interrupt Pin register identifies the legacy interrupt Message(s)
 * the Function uses. All encodings other than the defined encodings are
 * reserved.
 * PCI Express defines one legacy interrupt Message for a single Function
 * device and up to four legacy interrupt Messages for a multi-Function
 * device. For a single Function device, only INTA may be used.
 *
 * Any Function on a multi-Function device can use any of the INTx
 * Messages. If a device implements a single legacy interrupt Message, it
 * must be INTA; if it implements two legacy interrupt Messages, they must
 * be INTA and INTB; and so forth.
 * For a multi-Function device, all Functions may use the same INTx Message
 * or each may have its own (up to a maximum of four Functions) or any
 * combination thereof. A single Function can never generate an interrupt
 * request on more than one INTx Message.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG . INT_PIN
 */
#define  VTSS_F_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG_INT_PIN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG_INT_PIN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE_REG_INT_PIN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * Register Group: \a PCIE_DBI:PF0_TYPE0_HDR_DBI2
 *
 * DBI2 Shadow Block: PF PCI-Compatible Configuration Space Header Type0
 */


/**
 * \brief This register is the mask for BAR$_REG. If implemented, it exists as a shadow register at the BAR$_REG address.
Normally, the BAR masks are used for indicating the amount of address space that each BAR requests from host software. The BAR masks determine which bits in each BAR are non-writable by host software, which determines the size of the address space claimed by each BAR. The BAR mask values indicate the range of low-order bits, in each implemented BAR, not to use for address matching. The BAR mask value also indicates the range of low-order bits in the BAR that cannot be written from the host. The application can write to all BAR bits to allow setting of memory, I/O, and other standard BAR options.

Your local CPU can change the mask at runtime using the DBI. The mask register is invisible to the PCIe wire but visible to your local CPU through the DBI. You cannot read the mask register but you can write to it. It is accessed by asserting dbi_cs2 and dbi_cs. If you only assert dbi_cs then you will access the BAR which is the primary register at that location. Use CS2 instead of dbi_cs2 when you are using the AHB/AXI bridge.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR_DBI2:BAR0_MASK_REG
 */
#define VTSS_PCIE_DBI_BAR0_MASK_REG          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x40004)

/**
 * \brief
 *  - BAR0 Mask Enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR0_MASK_REG . PCI_TYPE0_BAR0_ENABLED
 */
#define  VTSS_F_PCIE_DBI_BAR0_MASK_REG_PCI_TYPE0_BAR0_ENABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR0_MASK_REG_PCI_TYPE0_BAR0_ENABLED  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR0_MASK_REG_PCI_TYPE0_BAR0_ENABLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 *  - BAR0 Mask.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: No access
 *  - Dbi: No access
 *  - Dbi2: W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR0_MASK_REG . PCI_TYPE0_BAR0_MASK
 */
#define  VTSS_F_PCIE_DBI_BAR0_MASK_REG_PCI_TYPE0_BAR0_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,31)
#define  VTSS_M_PCIE_DBI_BAR0_MASK_REG_PCI_TYPE0_BAR0_MASK     VTSS_ENCODE_BITMASK(1,31)
#define  VTSS_X_PCIE_DBI_BAR0_MASK_REG_PCI_TYPE0_BAR0_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,31)


/**
 * \brief This register is the mask for BAR$_REG. If implemented, it exists as a shadow register at the BAR$_REG address.
Normally, the BAR masks are used for indicating the amount of address space that each BAR requests from host software. The BAR masks determine which bits in each BAR are non-writable by host software, which determines the size of the address space claimed by each BAR. The BAR mask values indicate the range of low-order bits, in each implemented BAR, not to use for address matching. The BAR mask value also indicates the range of low-order bits in the BAR that cannot be written from the host. The application can write to all BAR bits to allow setting of memory, I/O, and other standard BAR options.

Your local CPU can change the mask at runtime using the DBI. The mask register is invisible to the PCIe wire but visible to your local CPU through the DBI. You cannot read the mask register but you can write to it. It is accessed by asserting dbi_cs2 and dbi_cs. If you only assert dbi_cs then you will access the BAR which is the primary register at that location. Use CS2 instead of dbi_cs2 when you are using the AHB/AXI bridge.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR_DBI2:BAR1_MASK_REG
 */
#define VTSS_PCIE_DBI_BAR1_MASK_REG          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x40005)

/**
 * \brief
 *  - BAR1 Mask Enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR1_MASK_REG . PCI_TYPE0_BAR1_ENABLED
 */
#define  VTSS_F_PCIE_DBI_BAR1_MASK_REG_PCI_TYPE0_BAR1_ENABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR1_MASK_REG_PCI_TYPE0_BAR1_ENABLED  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR1_MASK_REG_PCI_TYPE0_BAR1_ENABLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 *  - BAR1 Mask.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: No access
 *  - Dbi: No access
 *  - Dbi2: W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR1_MASK_REG . PCI_TYPE0_BAR1_MASK
 */
#define  VTSS_F_PCIE_DBI_BAR1_MASK_REG_PCI_TYPE0_BAR1_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,31)
#define  VTSS_M_PCIE_DBI_BAR1_MASK_REG_PCI_TYPE0_BAR1_MASK     VTSS_ENCODE_BITMASK(1,31)
#define  VTSS_X_PCIE_DBI_BAR1_MASK_REG_PCI_TYPE0_BAR1_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,31)


/**
 * \brief This register is the mask for BAR2_REG. If implemented, it exists as a shadow register at the BAR$_REG address.
Normally, the BAR masks are used for indicating the amount of address space that each BAR requests from host software. The BAR masks determine which bits in each BAR are non-writable by host software, which determines the size of the address space claimed by each BAR. The BAR mask values indicate the range of low-order bits, in each implemented BAR, not to use for address matching. The BAR mask value also indicates the range of low-order bits in the BAR that cannot be written from the host. The application can write to all BAR bits to allow setting of memory, I/O, and other standard BAR options.

Your local CPU can change the mask at runtime using the DBI. The mask register is invisible to the PCIe wire but visible to your local CPU through the DBI. You cannot read the mask register but you can write to it. It is accessed by asserting dbi_cs2 and dbi_cs. If you only assert dbi_cs then you will access the BAR which is the primary register at that location. Use CS2 instead of dbi_cs2 when you are using the AHB/AXI bridge.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR_DBI2:BAR2_MASK_REG
 */
#define VTSS_PCIE_DBI_BAR2_MASK_REG          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x40006)

/**
 * \brief
 * BAR2 Mask Enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR2_MASK_REG . PCI_TYPE0_BAR2_ENABLED
 */
#define  VTSS_F_PCIE_DBI_BAR2_MASK_REG_PCI_TYPE0_BAR2_ENABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR2_MASK_REG_PCI_TYPE0_BAR2_ENABLED  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR2_MASK_REG_PCI_TYPE0_BAR2_ENABLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BAR2 Mask.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: No access
 *  - Dbi: No access
 *  - Dbi2: W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR2_MASK_REG . PCI_TYPE0_BAR2_MASK
 */
#define  VTSS_F_PCIE_DBI_BAR2_MASK_REG_PCI_TYPE0_BAR2_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,31)
#define  VTSS_M_PCIE_DBI_BAR2_MASK_REG_PCI_TYPE0_BAR2_MASK     VTSS_ENCODE_BITMASK(1,31)
#define  VTSS_X_PCIE_DBI_BAR2_MASK_REG_PCI_TYPE0_BAR2_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,31)


/**
 * \brief This register is the mask for BAR3_REG. If implemented, it exists as a shadow register at the BAR$_REG address.
Normally, the BAR masks are used for indicating the amount of address space that each BAR requests from host software. The BAR masks determine which bits in each BAR are non-writable by host software, which determines the size of the address space claimed by each BAR. The BAR mask values indicate the range of low-order bits, in each implemented BAR, not to use for address matching. The BAR mask value also indicates the range of low-order bits in the BAR that cannot be written from the host. The application can write to all BAR bits to allow setting of memory, I/O, and other standard BAR options.

Your local CPU can change the mask at runtime using the DBI. The mask register is invisible to the PCIe wire but visible to your local CPU through the DBI. You cannot read the mask register but you can write to it. It is accessed by asserting dbi_cs2 and dbi_cs. If you only assert dbi_cs then you will access the BAR which is the primary register at that location. Use CS2 instead of dbi_cs2 when you are using the AHB/AXI bridge.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR_DBI2:BAR3_MASK_REG
 */
#define VTSS_PCIE_DBI_BAR3_MASK_REG          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x40007)

/**
 * \brief
 * BAR3 Mask Enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR3_MASK_REG . PCI_TYPE0_BAR3_ENABLED
 */
#define  VTSS_F_PCIE_DBI_BAR3_MASK_REG_PCI_TYPE0_BAR3_ENABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR3_MASK_REG_PCI_TYPE0_BAR3_ENABLED  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR3_MASK_REG_PCI_TYPE0_BAR3_ENABLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BAR3 Mask.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: No access
 *  - Dbi: No access
 *  - Dbi2: W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR3_MASK_REG . PCI_TYPE0_BAR3_MASK
 */
#define  VTSS_F_PCIE_DBI_BAR3_MASK_REG_PCI_TYPE0_BAR3_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,31)
#define  VTSS_M_PCIE_DBI_BAR3_MASK_REG_PCI_TYPE0_BAR3_MASK     VTSS_ENCODE_BITMASK(1,31)
#define  VTSS_X_PCIE_DBI_BAR3_MASK_REG_PCI_TYPE0_BAR3_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,31)


/**
 * \brief This register is the mask for BAR4_REG. If implemented, it exists as a shadow register at the BAR$_REG address.
Normally, the BAR masks are used for indicating the amount of address space that each BAR requests from host software. The BAR masks determine which bits in each BAR are non-writable by host software, which determines the size of the address space claimed by each BAR. The BAR mask values indicate the range of low-order bits, in each implemented BAR, not to use for address matching. The BAR mask value also indicates the range of low-order bits in the BAR that cannot be written from the host. The application can write to all BAR bits to allow setting of memory, I/O, and other standard BAR options.

Your local CPU can change the mask at runtime using the DBI. The mask register is invisible to the PCIe wire but visible to your local CPU through the DBI. You cannot read the mask register but you can write to it. It is accessed by asserting dbi_cs2 and dbi_cs. If you only assert dbi_cs then you will access the BAR which is the primary register at that location. Use CS2 instead of dbi_cs2 when you are using the AHB/AXI bridge.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR_DBI2:BAR4_MASK_REG
 */
#define VTSS_PCIE_DBI_BAR4_MASK_REG          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x40008)

/**
 * \brief
 * BAR4 Mask Enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR4_MASK_REG . PCI_TYPE0_BAR4_ENABLED
 */
#define  VTSS_F_PCIE_DBI_BAR4_MASK_REG_PCI_TYPE0_BAR4_ENABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR4_MASK_REG_PCI_TYPE0_BAR4_ENABLED  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR4_MASK_REG_PCI_TYPE0_BAR4_ENABLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BAR4 Mask.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: No access
 *  - Dbi: No access
 *  - Dbi2: W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR4_MASK_REG . PCI_TYPE0_BAR4_MASK
 */
#define  VTSS_F_PCIE_DBI_BAR4_MASK_REG_PCI_TYPE0_BAR4_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,31)
#define  VTSS_M_PCIE_DBI_BAR4_MASK_REG_PCI_TYPE0_BAR4_MASK     VTSS_ENCODE_BITMASK(1,31)
#define  VTSS_X_PCIE_DBI_BAR4_MASK_REG_PCI_TYPE0_BAR4_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,31)


/**
 * \brief This register is the mask for BAR5_REG. If implemented, it exists as a shadow register at the BAR$_REG address.
Normally, the BAR masks are used for indicating the amount of address space that each BAR requests from host software. The BAR masks determine which bits in each BAR are non-writable by host software, which determines the size of the address space claimed by each BAR. The BAR mask values indicate the range of low-order bits, in each implemented BAR, not to use for address matching. The BAR mask value also indicates the range of low-order bits in the BAR that cannot be written from the host. The application can write to all BAR bits to allow setting of memory, I/O, and other standard BAR options.

Your local CPU can change the mask at runtime using the DBI. The mask register is invisible to the PCIe wire but visible to your local CPU through the DBI. You cannot read the mask register but you can write to it. It is accessed by asserting dbi_cs2 and dbi_cs. If you only assert dbi_cs then you will access the BAR which is the primary register at that location. Use CS2 instead of dbi_cs2 when you are using the AHB/AXI bridge.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR_DBI2:BAR5_MASK_REG
 */
#define VTSS_PCIE_DBI_BAR5_MASK_REG          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x40009)

/**
 * \brief
 * BAR5 Mask Enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR5_MASK_REG . PCI_TYPE0_BAR5_ENABLED
 */
#define  VTSS_F_PCIE_DBI_BAR5_MASK_REG_PCI_TYPE0_BAR5_ENABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_BAR5_MASK_REG_PCI_TYPE0_BAR5_ENABLED  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_BAR5_MASK_REG_PCI_TYPE0_BAR5_ENABLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BAR5 Mask.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: No access
 *  - Dbi: No access
 *  - Dbi2: W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_BAR5_MASK_REG . PCI_TYPE0_BAR5_MASK
 */
#define  VTSS_F_PCIE_DBI_BAR5_MASK_REG_PCI_TYPE0_BAR5_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,31)
#define  VTSS_M_PCIE_DBI_BAR5_MASK_REG_PCI_TYPE0_BAR5_MASK     VTSS_ENCODE_BITMASK(1,31)
#define  VTSS_X_PCIE_DBI_BAR5_MASK_REG_PCI_TYPE0_BAR5_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,31)


/**
 * \brief This register is the mask for EXP_ROM_BASE_ADDR_REG register. If implemented, it exists as a shadow register at EXP_ROM_BAR_MASK_REG address. The assertion of CS2 (that is, assert the dbi_cs2 input, or the CS2 address bit for the AXI bridge) is required to write to this register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_TYPE0_HDR_DBI2:EXP_ROM_BAR_MASK_REG
 */
#define VTSS_PCIE_DBI_EXP_ROM_BAR_MASK_REG   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x4000c)

/**
 * \brief
 * Expansion ROM Bar Mask Register Enabled.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: No access
 *  - Dbi: No access
 *  - Dbi2: if ROM_MASK_WRITABLE then W
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_EXP_ROM_BAR_MASK_REG . ROM_BAR_ENABLED
 */
#define  VTSS_F_PCIE_DBI_EXP_ROM_BAR_MASK_REG_ROM_BAR_ENABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_EXP_ROM_BAR_MASK_REG_ROM_BAR_ENABLED  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_EXP_ROM_BAR_MASK_REG_ROM_BAR_ENABLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Expansion ROM Mask.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: No access
 *  - Dbi: No access
 *  - Dbi2: if ROM_BAR_ENABLED && ROM_MASK_WRITABLE then W
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_EXP_ROM_BAR_MASK_REG . ROM_MASK
 */
#define  VTSS_F_PCIE_DBI_EXP_ROM_BAR_MASK_REG_ROM_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,31)
#define  VTSS_M_PCIE_DBI_EXP_ROM_BAR_MASK_REG_ROM_MASK     VTSS_ENCODE_BITMASK(1,31)
#define  VTSS_X_PCIE_DBI_EXP_ROM_BAR_MASK_REG_ROM_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,31)

/**
 * Register Group: \a PCIE_DBI:PF0_SPCIE_CAP
 *
 * Secondary PCI Express Capability Structure
 */


/**
 * \brief This Register provides Capability Id, Capability Version, and next Offset of SPCIE Structure.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_SPCIE_CAP:SPCIE_CAP_HEADER_REG
 */
#define VTSS_PCIE_DBI_SPCIE_CAP_HEADER_REG   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x52)

/**
 * \brief
 * Secondary PCI Express Extended Capability ID.
 * This field is a PCI-SIG defined ID number that indicates the nature and
 * format of the Extended Capability.
 * PCI Express Extended Capability ID for the Secondary PCI Express
 * Extended Capability is 0019h.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_SPCIE_CAP_HEADER_REG . EXTENDED_CAP_ID
 */
#define  VTSS_F_PCIE_DBI_SPCIE_CAP_HEADER_REG_EXTENDED_CAP_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_SPCIE_CAP_HEADER_REG_EXTENDED_CAP_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_SPCIE_CAP_HEADER_REG_EXTENDED_CAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Capability Version.
 * This field is a PCI-SIG defined version number that indicates the
 * version of the Capability structure present.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hf:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_SPCIE_CAP_HEADER_REG . CAP_VERSION
 */
#define  VTSS_F_PCIE_DBI_SPCIE_CAP_HEADER_REG_CAP_VERSION(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_PCIE_DBI_SPCIE_CAP_HEADER_REG_CAP_VERSION     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_PCIE_DBI_SPCIE_CAP_HEADER_REG_CAP_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Next Capability Offset.
 * This field contains the offset to the next PCI Express Extended
 * Capability structure or 000h if no other items exist in the linked list
 * of Capabilities.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hfff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_SPCIE_CAP_HEADER_REG . NEXT_OFFSET
 */
#define  VTSS_F_PCIE_DBI_SPCIE_CAP_HEADER_REG_NEXT_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,20,12)
#define  VTSS_M_PCIE_DBI_SPCIE_CAP_HEADER_REG_NEXT_OFFSET     VTSS_ENCODE_BITMASK(20,12)
#define  VTSS_X_PCIE_DBI_SPCIE_CAP_HEADER_REG_NEXT_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,20,12)


/**
 * \brief This Register controls equilization and equilization interrupt.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_SPCIE_CAP:LINK_CONTROL3_REG
 */
#define VTSS_PCIE_DBI_LINK_CONTROL3_REG      VTSS_IOREG(VTSS_TO_PCIE_DBI,0x53)

/**
 * \brief
 * Perform Equalization.
 * This bit is RW for Downstream Ports and for Upstream Ports when
 * Crosslink Supported is 1b.
 * This bit is not applicable and is RsvdP for Upstream Ports when the
 * Crosslink Supported bit is 0b.
 * If the Port does not support 8.0 GT/s, this bit is permitted to be
 * hardwired to 0b by the controller.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: RSVDP
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL3_REG . PERFORM_EQ
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL3_REG_PERFORM_EQ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL3_REG_PERFORM_EQ  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL3_REG_PERFORM_EQ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Link Equalization Request Interrupt Enable.
 * This bit is RW for Downstream Ports and for Upstream Ports when
 * Crosslink Supported is 1b.
 * This bit is not applicable and is RsvdP for Upstream Ports when the
 * Crosslink Supported bit is 0b.
 * If the Port does not support 8.0 GT/s, this bit is permitted to be
 * hardwired to 0b by the controller.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: RSVDP
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL3_REG . EQ_REQ_INT_EN
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL3_REG_EQ_REQ_INT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL3_REG_EQ_REQ_INT_EN  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL3_REG_EQ_REQ_INT_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief This Register contains Lane Error Status Bits per Lane.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_SPCIE_CAP:LANE_ERR_STATUS_REG
 */
#define VTSS_PCIE_DBI_LANE_ERR_STATUS_REG    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x54)

/**
 * \brief
 * Lane Error Status Bits per Lane.
 * Each bit indicates if the corresponding Lane detected a Lane-based
 * error. A value of 1b indicates that a Lane based-error was detected on
 * the corresponding Lane Number.
 * For Ports that are narrower than 32 Lanes, the unused upper bits [31:
 * Maximum Link Width] are RsvdZ.
 * For Ports that do not support 8.0 GT/s and do not set these bits based
 * on 8b/10b errors , this field is permitted to be hardwired to 0 by the
 * controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LANE_ERR_STATUS_REG . LANE_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_LANE_ERR_STATUS_REG_LANE_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_LANE_ERR_STATUS_REG_LANE_ERR_STATUS  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_LANE_ERR_STATUS_REG_LANE_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief This register provides Transmitter Preset and Receiver Preset Hint for Downstream Port and Upstream Port.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_SPCIE_CAP:SPCIE_CAP_OFF_0CH_REG
 */
#define VTSS_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x55)

/**
 * \brief
 * Downstream Port 8.0 GT/s Transmitter Preset 0.
 * Transmitter preset 0 value used for 8.0 GT/s equalization by this Port
 * when the Port is operating as a Downstream Port. This field is ignored
 * when the Port is operating as an Upstream Port.
 * For an Upstream Port if Crosslink Supported is 0b, this field is RsvdP.
 * Otherwise, this field is HwInit.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: RSVDP
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG . DSP_TX_PRESET0
 */
#define  VTSS_F_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_DSP_TX_PRESET0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_DSP_TX_PRESET0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_DSP_TX_PRESET0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Downstream Port 8.0 GT/s Receiver Preset Hint 0.
 * Receiver preset hint 0 value that may be used as a suggested setting for
 * 8.0 GT/s receiver equalization by this Port when the Port is operating
 * as a Downstream Port.
 * This field is ignored when the Port is operating as an Upstream Port.
 * For an Upstream Port if Crosslink Supported is 0b, this field is RsvdP.
 * Otherwise, this field is HwInit.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: RSVDP
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG . DSP_RX_PRESET_HINT0
 */
#define  VTSS_F_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_DSP_RX_PRESET_HINT0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_DSP_RX_PRESET_HINT0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_DSP_RX_PRESET_HINT0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Upstream Port 8.0 GT/s Transmitter Preset 0.
 *
 * The write value is gated with the PCIE_CAP_CROSS_LINK_SUPPORT field of
 * LINK_CAPABILITIES2_REG.
 * Field contains the Transmitter preset 0 value sent or received during
 * 8.0 GT/s Link Equalization.
 *  - Case A: When Operating port is Downstream port and whether the
 * Crosslink is supported or not, this field representss the value sent on
 * Lane 0 during 8.0 GT/s equalization.
 *  - Case B: When Operating port is Upstream port and Crosslink Supported
 * bit is 0, this field is intended for debug and diagnostics. It contains
 * the value captured from Lane 0 during Link Equalization.
 *  - Case C: When Operating port is Upstream port and Crosslink Supported
 * bit is 1, Field is not used or affected by the current Link
 * Equalization. Field value will be used if a future crosslink negotiation
 * switches the Operating Port Direction so that case A applies.
 * For case A and C, Field is HwInit. For case B, Field is RO.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG . USP_TX_PRESET0
 */
#define  VTSS_F_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_USP_TX_PRESET0(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_USP_TX_PRESET0     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_USP_TX_PRESET0(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Upstream Port 8.0 GT/s Receiver Preset Hint 0.
 *
 * The write value is gated with the PCIE_CAP_CROSS_LINK_SUPPORT field of
 * LINK_CAPABILITIES2_REG.
 * Field contains the Receiver preset hint 0 value sent or received during
 * 8.0 GT/s Link Equalization.
 *  - Case A: When Operating port is Downstream port and whether the
 * Crosslink is supported or not, this field representss the value sent on
 * Lane 0 during 8.0 GT/s equalization.
 *  - Case B: When Operating port is Upstream port and Crosslink Supported
 * bit is 0, this field is intended for debug and diagnostics. It contains
 * the value captured from Lane 0 during Link Equalization.
 *  - Case C: When Operating port is Upstream port and Crosslink Supported
 * bit is 1, Field is not used or affected by the current Link
 * Equalization. Field value will be used if a future crosslink negotiation
 * switches the Operating Port Direction so that case A applies.
 * For case A and C, Field is HwInit. For case B, Field is RO.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG . USP_RX_PRESET_HINT0
 */
#define  VTSS_F_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_USP_RX_PRESET_HINT0(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_USP_RX_PRESET_HINT0     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_PCIE_DBI_SPCIE_CAP_OFF_0CH_REG_USP_RX_PRESET_HINT0(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * Register Group: \a PCIE_DBI:PF0_PM_CAP
 *
 * PF PCI Power Management Capability Structure
 */


/**
 * \brief This register provides information refarding the Power Management Capabilities.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PM_CAP:CAP_ID_NXT_PTR_REG
 */
#define VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG     VTSS_IOREG(VTSS_TO_PCIE_DBI,0x10)

/**
 * \brief
 * Capability ID.
 * This field returns 01h to indicate that this is the PCI Power Management
 * Capability. Each function may have only one item in its capability list
 * with Capability ID set to 01h.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . PM_CAP_ID
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_CAP_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_CAP_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_CAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Next Capability Pointer.
 * This field provides an offset into the function's configuration space
 * pointing to the location of next item in the capabilities list. If there
 * are no additional items in the capabilities list, this field is set to
 * 00h.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . PM_NEXT_POINTER
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_NEXT_POINTER(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_NEXT_POINTER     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_NEXT_POINTER(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Version.
 * This field provides the Power Management specification version. The
 * controller hardwires this field to 011b for functions compliant to PCI
 * Express Base Specification, Revision 4.0, Version 1.0>.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . PM_SPEC_VER
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_SPEC_VER(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_SPEC_VER     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_PM_SPEC_VER(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * PME Clock.
 * Does not apply to PCI Express, the controller hardwires it to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . PME_CLK
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_PME_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_PME_CLK  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_PME_CLK(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Device Specific Initialization.
 * The DSI bit indicates whether special initialization of this function is
 * required.
 *
 * When set, indicates that the function requires a device specific
 * initialization sequence following a transition to the D0uninitialized
 * state.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . DSI
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_DSI(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_DSI  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_DSI(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Aux_Current.
 * This 3 bit field reports the Vaux auxiliary current requirements for the
 * function.
 *
 * If this function implements the Data Register, the controller hardwires
 * this field to 000b.
 *
 * If PME_Support is 0 xxxxb (PME assertion from D3cold is not supported),
 * the controller hardwires this field to 0000b.
 *
 * For functions where PME_Support is 1 xxxxb (PME assertion from D3cold is
 * supported), and which do not implement the Data field, the encodings
 * defined in Values: apply:
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . AUX_CURR
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_AUX_CURR(x)  VTSS_ENCODE_BITFIELD(x,22,3)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_AUX_CURR     VTSS_ENCODE_BITMASK(22,3)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_AUX_CURR(x)  VTSS_EXTRACT_BITFIELD(x,22,3)

/**
 * \brief
 * D1_Support.
 * If this bit is set, this function supports the D1 Power Management
 * state. Functions that do not support D1 must always return a value of 0b
 * for this bit.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . D1_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_D1_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_D1_SUPPORT  VTSS_BIT(25)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_D1_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * D2_Support.
 * If this bit is set, this function supports the D2 Power Management
 * state. Functions that do not support D2 must always return a value of 0b
 * for this bit.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . D2_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_D2_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_D2_SUPPORT  VTSS_BIT(26)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_D2_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * PME_Support.
 * This 5-bit field indicates the power states in which the function may
 * generate a PME and/or forward PME messages.
 * A value of 0b for any bit indicates that the function is not capable of
 * asserting PME while in that power state.
 *  - bit(27) X XXX1b - PME can be generated from D0
 *  - bit(28) X XX1Xb - PME can be generated from D1
 *  - bit(29) X X1XXb - PME can be generated from D2
 *  - bit(30) X 1XXXb - PME can be generated from D3hot
 *  - bit(31) 1 XXXXb - PME can be generated from D3cold
 * Bit 31 (PME can be asserted from D3cold) represents a special case.
 * Functions that set this bit require some sort of auxiliary power source.
 * Implementation specific mechanisms are recommended to validate that the
 * power source is available before setting this bit.
 *
 *
 *
 * The read value from this field is the write value && (sys_aux_pwr_det,
 * 1'b1, D2_SUPPORT, D1_SUPPORT, 1'b1), where D1_SUPPORT and D2_SUPPORT are
 * fields in this register.
 *
 * The reset value PME_SUPPORT_n && (sys_aux_pwr_det, 1'b1, D2_SUPPORT,
 * D1_SUPPORT, 1'b1), where PME_SUPPORT_n is a configuration parameter.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CAP_ID_NXT_PTR_REG . PME_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_CAP_ID_NXT_PTR_REG_PME_SUPPORT(x)  VTSS_ENCODE_BITFIELD(x,27,5)
#define  VTSS_M_PCIE_DBI_CAP_ID_NXT_PTR_REG_PME_SUPPORT     VTSS_ENCODE_BITMASK(27,5)
#define  VTSS_X_PCIE_DBI_CAP_ID_NXT_PTR_REG_PME_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,27,5)


/**
 * \brief This register is used to manage the PCI function's power management state as well as to enable/monitor PMEs.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PM_CAP:CON_STATUS_REG
 */
#define VTSS_PCIE_DBI_CON_STATUS_REG         VTSS_IOREG(VTSS_TO_PCIE_DBI,0x11)

/**
 * \brief
 * PowerState.
 * This 2-bit field is used both to determine the current power state of a
 * function and to set the function into a new power state.
 * You can write to this register; however, the read-back value is the
 * actual power state, not the write value. If you attempt to write an
 * unsupported, optional state to this field, the write operation completes
 * normally; however, the data is discarded and no state change occurs.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . POWER_STATE
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_POWER_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_POWER_STATE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_POWER_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * No_Soft_Reset.
 * This bit indicates the state of the function after writing the
 * PowerState field to transition the function from D3hot to D0.
 *  - When set, this transition preserves internal function state. The
 * function is in D0Active and no additional software intervention is
 * required.
 *  - When clear, this transition results in undefined internal function
 * state.
 * Regardless of this bit, functions that transition from D3hot to D0 by
 * Fundamental Reset will return to D0Uninitialized with only PME context
 * preserved if PME is supported and enabled.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . NO_SOFT_RST
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_NO_SOFT_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_NO_SOFT_RST  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_NO_SOFT_RST(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * PME_En.
 *  - When set, the function is permitted to generate a PME.
 *  - When clear, the function is not permitted to generate a PME.
 * If PME_Support is 1 xxxxb (PME generation from D3cold) or the function
 * consumes Aux power and Aux power is available this bit is RWS and the
 * bit is not modified by Conventional Reset or FLR.
 *
 * If PME_Support is 0 xxxxb, this field is not sticky (RW).
 *
 * If PME_Support is 0 0000b, the controller hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . PME_ENABLE
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_PME_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_PME_ENABLE  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_PME_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Data_Select.
 * This 4-bit field is used to select which data is to be reported through
 * the Data and Data_Scale field. If the Data field is not implemented,
 * this field must be hardwired to 0000b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . DATA_SELECT
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_DATA_SELECT(x)  VTSS_ENCODE_BITFIELD(x,9,4)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_DATA_SELECT     VTSS_ENCODE_BITMASK(9,4)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_DATA_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,9,4)

/**
 * \brief
 * Data_Scale.
 * This field indicates the scaling factor to be used when interpreting the
 * value of the Data field. The value and meaning of this field varies
 * depending on which data value has been selected by the Data_Select
 * field. For more information, see 7.5.2.3 section of PCI Express Base
 * Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . DATA_SCALE
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_DATA_SCALE(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_DATA_SCALE     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_DATA_SCALE(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * PME_Status.
 * This bit is set when the function normally generates a PME signal. The
 * value of this bit is not affected by the value of the PME_En bit.
 * If PME_Support bit 31 of the Power Management Capabilities register is
 * clear, this bit is permitted to be hardwired to 0b.
 * Functions that consume Aux power must preserve the value of this sticky
 * register when Aux power is available. In such functions, this register
 * value is not modified by Conventional Reset or FLR.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . PME_STATUS
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_PME_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_PME_STATUS  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_PME_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * B2B3 Support for D3hot.
 * If this field is set, B2B3 support for D3hot is available.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . B2_B3_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_B2_B3_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_B2_B3_SUPPORT  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_B2_B3_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Bus Power/Clock Control Enable.
 * If this field is set, Bus Power/Clock Control is Enable.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . BUS_PWR_CLK_CON_EN
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_BUS_PWR_CLK_CON_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_BUS_PWR_CLK_CON_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_BUS_PWR_CLK_CON_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Data.
 * This field is used to report the state dependent data requested by the
 * Data_Select field. The value of this field is scaled by the value
 * reported by the Data_Scale field.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CON_STATUS_REG . DATA_REG_ADD_INFO
 */
#define  VTSS_F_PCIE_DBI_CON_STATUS_REG_DATA_REG_ADD_INFO(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_CON_STATUS_REG_DATA_REG_ADD_INFO     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_CON_STATUS_REG_DATA_REG_ADD_INFO(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * Register Group: \a PCIE_DBI:PF0_PCIE_CAP
 *
 * PF PCI Express Capability Structure
 */


/**
 * \brief This is the PCI Express Capabilities, ID, and Next Pointer Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG
 */
#define VTSS_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c)

/**
 * \brief
 * Capability ID. Indicates the PCI Express Capability structure. This
 * field must return a Capability ID of 10h indicating that this is a PCI
 * Express Capability structure.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG . PCIE_CAP_ID
 */
#define  VTSS_F_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Next Capability Pointer. This field contains the offset to the next PCI
 * Capability structure or 00h if no other items exist in the linked list
 * of Capabilities.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG . PCIE_CAP_NEXT_PTR
 */
#define  VTSS_F_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_NEXT_PTR(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_NEXT_PTR     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_NEXT_PTR(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Capability Version.
 * Indicates PCI-SIG defined PCI Express Capability structure version
 * number.
 * A version of the specification that changes the PCI Express Capability
 * structure in a way that is not otherwise identifiable (for example,
 * through a new Capability field) is permitted to increment this field.
 * All such changes to the PCI Express Capability structure must be
 * software-compatible. Software must check for Capability Version numbers
 * that are greater than or equal to the highest number defined when the
 * software is written, as functions reporting any such Capability Version
 * numbers will contain a PCI Express Capability structure that is
 * compatible with that piece of software.
 * The controller hardwires this field to 2h for functions compliant to PCI
 * Express Base Specification, Revision 4.0, Version 1.0.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG . PCIE_CAP_REG
 */
#define  VTSS_F_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_REG(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_REG     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_REG(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Device/Port Type. Indicates the specific type of this PCI Express
 * function.
 *
 * Note: Different functions in a Multi-Function Device can generally be of
 * different types.
 * Defined encodings for functions that implement a Type 00h PCI
 * Configuration Space header are:
 * Defined encodings for functions that implement a Type 01h PCI
 * Configuration Space header are:
 * All other encodings are Reserved.
 *
 * Note: Different Endpoint types have notably different requirements in
 * Section 1.3.2 of PCI Express Base Specification regarding I/O resources,
 * Extended Configuration Space, and other capabilities.
 *
 * \details
 * 'h6:
 * 'h0:
 * 'h1:
 * 'h4:
 * 'h5:

 *
 * Field: ::VTSS_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG . PCIE_DEV_PORT_TYPE
 */
#define  VTSS_F_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_DEV_PORT_TYPE(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_DEV_PORT_TYPE     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_DEV_PORT_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Slot Implemented. When set, this bit indicates that the Link associated
 * with this Port is connected to a slot (as compared to being connected to
 * a system-integrated device or being disabled). This bit is valid for
 * Downstream Ports. This bit is undefined for Upstream Ports.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: HWINIT
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG . PCIE_SLOT_IMP
 */
#define  VTSS_F_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_SLOT_IMP(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_SLOT_IMP  VTSS_BIT(24)
#define  VTSS_X_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_SLOT_IMP(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * PCIE Interrupt Message Number.
 * Interrupt Message Number. This field indicates which MSI/MSI-X vector is
 * used for the interrupt message generated in association with any of the
 * status bits of this Capability structure.
 *
 * For MSI, the value in this field indicates the offset between the base
 * Message Data and the interrupt message that is generated. Hardware is
 * required to update this field so that it is correct if the number of MSI
 * Messages assigned to the Function changes when software writes to the
 * Multiple Message Enable field in the MSI Message Control register.
 *
 * For MSI-X, the value in this field indicates which MSI-X Table entry is
 * used to generate the interrupt message. The entry must be one of the
 * first 32 entries even if the Function implements more than 32 entries.
 * For a given MSI-X implementation, the entry must remain constant.
 *
 * If both MSI and MSI-X are implemented, they are permitted to use
 * different vectors, though software is permitted to enable only one
 * mechanism at a time. If MSI-X is enabled, the value in this field must
 * indicate the vector for MSI-X. If MSI is enabled or neither is enabled,
 * the value in this field must indicate the vector for MSI. If software
 * enables both MSI and MSI-X at the same time, the value in this field is
 * undefined.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG . PCIE_INT_MSG_NUM
 */
#define  VTSS_F_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_INT_MSG_NUM(x)  VTSS_ENCODE_BITFIELD(x,25,5)
#define  VTSS_M_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_INT_MSG_NUM     VTSS_ENCODE_BITMASK(25,5)
#define  VTSS_X_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_INT_MSG_NUM(x)  VTSS_EXTRACT_BITFIELD(x,25,5)

/**
 * \brief
 * Reserved.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG . RSVD
 */
#define  VTSS_F_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RSVD(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RSVD  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RSVD(x)  VTSS_EXTRACT_BITFIELD(x,30,1)


/**
 * \brief The Device Capabilities register identifies PCI Express device function specific capabilities.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:DEVICE_CAPABILITIES_REG
 */
#define VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1d)

/**
 * \brief
 * Max_Payload_Size Supported.
 * This field indicates the maximum payload size that the function can
 * support for TLPs.
 * All encodings other than the defined encodings are reserved.
 * The functions of a Multi-Function Device are permitted to report
 * different values for this field.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h3:
 * 'h0:
 * 'h4:
 * 'h1:
 * 'h5:
 * 'h2:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_MAX_PAYLOAD_SIZE
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_MAX_PAYLOAD_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_MAX_PAYLOAD_SIZE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_MAX_PAYLOAD_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Phantom Functions Supported.
 * This field indicates the support for use of unclaimed function numbers
 * to extend the number of outstanding transactions allowed by logically
 * combining unclaimed function numbers (called Phantom Functions) with the
 * Tag identifier (see Section 2.2.6.2 of PCI Express Base Specification
 * for a description of Tag Extensions).
 *
 * With every Function in an ARI Device, the Phantom Functions Supported
 * field must be set to 00b. The remainder of this field description
 * applies only to non-ARI Multi-Function Devices.
 *
 * This field indicates the number of most significant bits of the Function
 * Number portion of Requester ID that are logically combined with the Tag
 * identifier.
 * Note: Phantom Function support for the function must be enabled by the
 * Phantom Functions Enable field in the Device Control register before the
 * Function is permitted to use the Function Number field in the Requester
 * ID for Phantom Functions.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h2:
 * 'h0:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_PHANTOM_FUNC_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_PHANTOM_FUNC_SUPPORT(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_PHANTOM_FUNC_SUPPORT     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_PHANTOM_FUNC_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Extended Tag Field Supported.
 * This bit, in combination with the 10-Bit Tag Requester Supported bit in
 * the Device Capabilities 2 register, indicates the maximum supported size
 * of the Tag field as a Requester. This bit must be set if the 10-Bit Tag
 * Requester Supported bit is set.
 * Note: 8-bit Tag field generation must be enabled by the Extended Tag
 * Field Enable bit in the Device Control register of the Requester
 * Function before 8-bit Tags can be generated by the Requester. See
 * Section 2.2.6.2 of PCI Express Base Specification for interactions with
 * enabling the use of 10-Bit Tags.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_EXT_TAG_SUPP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EXT_TAG_SUPP(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EXT_TAG_SUPP  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EXT_TAG_SUPP(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Endpoint L0s Acceptable Latency. This field indicates the acceptable
 * total latency that an Endpoint can withstand due to the transition from
 * L0s state to the L0 state. It is essentially an indirect measure of the
 * Endpoint's internal buffering.
 *
 * Power management software uses the reported L0s Acceptable Latency
 * number to compare against the L0s exit latencies reported by all
 * components comprising the data path from this Endpoint to the Root
 * Complex Root Port to determine whether ASPM L0s entry can be used with
 * no loss of performance.
 * For functions other than Endpoints, this field is Reserved and the
 * controller hardwires it to 000b.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h4:
 * 'h2:
 * 'h5:
 * 'h6:
 * 'h3:
 * 'h0:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_EP_L0S_ACCPT_LATENCY
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EP_L0S_ACCPT_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EP_L0S_ACCPT_LATENCY     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EP_L0S_ACCPT_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Endpoint L1 Acceptable Latency. This field indicates the acceptable
 * latency that an Endpoint can withstand due to the transition from L1
 * state to the L0 state. It is essentially an indirect measure of the
 * Endpoint's internal buffering.
 * Power management software uses the reported L1 Acceptable Latency number
 * to compare against the L1 Exit Latencies reported (see below) by all
 * components comprising the data path from this Endpoint to the Root
 * Complex Root Port to determine whether ASPM L1 entry can be used with no
 * loss of performance.
 * For functions other than Endpoints, this field is Reserved and the
 * controller hardwires it to 000b.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W (Sticky) else R(Sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h4:
 * 'h0:
 * 'h1:
 * 'h5:
 * 'h2:
 * 'h6:
 * 'h3:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_EP_L1_ACCPT_LATENCY
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EP_L1_ACCPT_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EP_L1_ACCPT_LATENCY     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_EP_L1_ACCPT_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Role-Based Error Reporting. When set, this bit indicates that the
 * function implements the functionality originally defined in the Error
 * Reporting ECN for PCI Express Base Specification, Revision 1.0a, and
 * later incorporated into PCI Express Base Specification, Revision 1.1.
 * This bit must be set by all functions conforming to the ECN, PCI Express
 * Base Specification, Revision 1.1., or subsequent PCI Express Base
 * Specification revisions.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_ROLE_BASED_ERR_REPORT
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_ROLE_BASED_ERR_REPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_ROLE_BASED_ERR_REPORT  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_ROLE_BASED_ERR_REPORT(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Captured Slot Power Limit Value.
 * Captured Slot Power Limit Value (Upstream Ports only). In combination
 * with the Captured Slot Power Limit Scale value, specifies the upper
 * limit on power available to the adapter.
 * Power limit (in Watts) is calculated by multiplying the value in this
 * field by the value in the Captured Slot Power Limit Scale field except
 * when the Captured Slot Power Limit Scale field equals 00b (1.0x) and the
 * Captured Slot Power Limit Value exceeds EFh, then alternative encodings
 * are used (for more details, see section 7.5.3.9 of PCI Express Base
 * Specification).
 * This value is set by the Set_Slot_Power_Limit Message or hardwired to
 * 00h (for more details, see section 6.9 of PCI Express Base
 * Specification).

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_CAP_SLOT_PWR_LMT_VALUE
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_CAP_SLOT_PWR_LMT_VALUE(x)  VTSS_ENCODE_BITFIELD(x,18,8)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_CAP_SLOT_PWR_LMT_VALUE     VTSS_ENCODE_BITMASK(18,8)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_CAP_SLOT_PWR_LMT_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,18,8)

/**
 * \brief
 * Captured Slot Power Limit Scale.
 * Captured Slot Power Limit Scale (Upstream Ports only). Specifies the
 * scale used for the Slot Power Limit Value.
 * This value is set by the Set_Slot_Power_Limit Message or hardwired to
 * 00b (for more details, see section 6.9 of PCI Express Base
 * Specification).
 *
 * \details
 * 'h3:
 * 'h2:
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_CAP_SLOT_PWR_LMT_SCALE
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_CAP_SLOT_PWR_LMT_SCALE(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_CAP_SLOT_PWR_LMT_SCALE     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_CAP_SLOT_PWR_LMT_SCALE(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * Function Level Reset Capability. A value of 1b indicates the function
 * supports the optional Function Level Reset mechanism described in
 * section 6.6.2 of the PCI Express Base Specification.
 *
 * This bit applies to Endpoints only. For all other function types the
 * controller hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES_REG . PCIE_CAP_FLR_CAP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_FLR_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_FLR_CAP  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES_REG_PCIE_CAP_FLR_CAP(x)  VTSS_EXTRACT_BITFIELD(x,28,1)


/**
 * \brief This register controls PCI Express device specific parameters and provides information about PCI Express device (function) specific parameters.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:DEVICE_CONTROL_DEVICE_STATUS
 */
#define VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1e)

/**
 * \brief
 * Correctable Error Reporting Enable.
 * This bit, in conjunction with other bits, controls sending ERR_COR
 * Messages (for more details, see section 6.2.5, section 6.2.6, and
 * section 6.2.10.2 of PCI Express Base Specification). For a
 * Multi-Function device, this bit controls error reporting for each
 * function from point-of-view of the respective function.
 *
 * For a Root Port, the reporting of correctable errors is internal to the
 * root. No external ERR_COR Message is generated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_CORR_ERR_REPORT_EN
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_REPORT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_REPORT_EN  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_REPORT_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Non-Fatal Error Reporting Enable.
 * This bit, in conjunction with other bits, controls sending ERR_NONFATAL
 * Messages (for more details, see section 6.2.5 and Section 6.2.6 of PCI
 * Express Base Specification). For a Multi-Function Device, this bit
 * controls error reporting for each function from point-of-view of the
 * respective Function.
 *
 * For a Root Port, the reporting of Non-fatal errors is internal to the
 * root. No external ERR_NONFATAL Message is generated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_NON_FATAL_ERR_REPORT_EN
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_REPORT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_REPORT_EN  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_REPORT_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Fatal Error Reporting Enable.
 * This bit, in conjunction with other bits, controls sending ERR_FATAL
 * Messages (for more details, see section 6.2.5 and section 6.2.6 of of
 * PCI Express Base Specification). For a Multi-Function device, this bit
 * controls error reporting for each function from point-of-view of the
 * respective function.
 *
 * For a Root Port, the reporting of Fatal errors is internal to the root.
 * No external ERR_FATAL Message is generated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_FATAL_ERR_REPORT_EN
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_REPORT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_REPORT_EN  VTSS_BIT(2)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_REPORT_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Unsupported Request Reporting Enable.
 * This bit, in conjunction with other bits, controls the signaling of
 * Unsupported Request Errors by sending error Messages (for more details,
 * see section 6.2.5 and section 6.2.6 of PCI Express Base Specification).
 * For a Multi-Function Device, this bit controls error reporting for each
 * Function from point-of-view of the respective Function.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_UNSUPPORT_REQ_REP_EN
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORT_REQ_REP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORT_REQ_REP_EN  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORT_REQ_REP_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable Relaxed Ordering.
 * If this bit is set, the function is permitted to set the Relaxed
 * Ordering bit in the Attributes field of transactions it initiates that
 * do not require strong write ordering (for more details, see section
 * 2.2.6.4 and section 2.4 of PCI Express Base Specification).
 *
 * For a function that never sets the Relaxed Ordering attribute in
 * transactions it initiates as a Requester, the controller hardwires this
 * bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_EN_REL_ORDER
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_REL_ORDER(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_REL_ORDER  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_REL_ORDER(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Max_Payload_Size.
 * This field sets maximum TLP payload size for the Function. As a
 * Receiver, the Function must handle TLPs as large as the set value. As a
 * Transmitter, the Function must not generate TLPs exceeding the set
 * value. Permissible values that can be programmed are indicated by the
 * Max_Payload_Size Supported field (PCIE_CAP_MAX_PAYLOAD_SIZE) in the
 * Device Capabilities (DEVICE_CAPABILITIES_REG) register (for more
 * details, see section 7.5.3.3 of PCI Express Base Specification).
 * This field sets the maximum Read Request size for the function as a
 * Requester. The function must not generate Read Requests with a size
 * exceeding the set value.
 * For Functions that support only the 128-byte max payload size, the
 * controller hardwires this field to 000b.
 *
 * System software is not required to program the same value for this field
 * for all the Functions of a Multi-Function device (for more details, see
 * section 2.2.2 of PCI Express Base Specification).
 *
 * For ARI Devices, Max_Payload_Size is determined solely by the setting in
 * Function0. The settings in the other Functions always return whatever
 * value software programmed for each, but otherwise are ignored by the
 * component.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * 'h3:
 * 'h0:
 * 'h4:
 * 'h1:
 * 'h5:
 * 'h2:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_MAX_PAYLOAD_SIZE_CS
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_PAYLOAD_SIZE_CS(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_PAYLOAD_SIZE_CS     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_PAYLOAD_SIZE_CS(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * Extended Tag Field Enable.
 * This bit, in combination with the 10-Bit Tag Requester Enable bit in the
 * Device Control 2 register, determines how many Tag field bits a
 * Requester is permitted to use.
 *
 * When the 10-Bit Tag Requester Enable bit is clear,
 *  - If the Extended Tag Field Enable bit is set, the function is
 * permitted to use an 8-bit Tag field as a Requester
 *  - If the Extended Tag Field Enable bit is clear, the Function is
 * restricted to a 5-bit Tag field
 * See section 2.2.6.2 of PCI Express Base Specification for required
 * behavior when the 10-Bit Tag Requester Enable bit is set.
 *
 * If software changes the value of the Extended Tag Field Enable bit while
 * the function has outstanding Non-Posted Requests, the result is
 * undefined.
 *
 * For functions that do not implement this capability, the controller
 * hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: DEVICE_CAPABILITIES_REG.PCIE_CAP_EXT_TAG_SUPP ? RW : RO
 *  - Dbi: DEVICE_CAPABILITIES_REG.PCIE_CAP_EXT_TAG_SUPP ? RW : RO
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_EXT_TAG_EN
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EXT_TAG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EXT_TAG_EN  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EXT_TAG_EN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Phantom Functions Enable.
 * This bit, in combination with the 10-Bit Tag Requester Enable bit in the
 * Device Control 2 register, determines how many Tag field bits a
 * Requester is permitted to use.
 *
 * When the 10-Bit Tag Requester Enable bit is clear,
 *  - If this bit is set, it enables a function to use unclaimed functions
 * as Phantom functions to extend the number of outstanding transaction
 * identifiers
 *  - If this bit is clear, the function is not allowed to use Phantom
 * functions
 * For more information, see section 2.2.6.2 of PCI Express Base
 * Specification.
 *
 * Software should not change the value of this bit while the function has
 * outstanding Non-Posted Requests; otherwise, the result is undefined.
 *
 * For functions that do not implement this capability, the controller
 * hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: DEVICE_CAPABILITIES_REG.PCIE_CAP_PHANTOM_FUNC_SUPPORT ? RW : RO
 *
 *  - Dbi: DEVICE_CAPABILITIES_REG.PCIE_CAP_PHANTOM_FUNC_SUPPORT ? RW : RO
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_PHANTOM_FUNC_EN
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_PHANTOM_FUNC_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_PHANTOM_FUNC_EN  VTSS_BIT(9)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_PHANTOM_FUNC_EN(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Aux Power PM Enable.
 * This bit is derived by sampling the sys_aux_pwr_det input.
 * When set this bit, enables a function to draw Aux power independent of
 * PME Aux power. Functions that require Aux power on legacy operating
 * systems should continue to indicate PME Aux power requirements. Aux
 * power is allocated as requested in the Aux_Current field of the Power
 * Management Capabilities register (PMC), independent of the PME_En bit in
 * the Power Management Control/Status register (PMCSR). For Multi-Function
 * devices, a component is allowed to draw Aux power if at least one of the
 * functions has this bit set.
 * Note: Functions that consume Aux power must preserve the value of this
 * sticky register when Aux power is available. In such functions, this bit
 * is not modified by Conventional Reset.
 *
 * For functions that do not implement this capability, the controller
 * hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_AUX_POWER_PM_EN
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_PM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_PM_EN  VTSS_BIT(10)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_PM_EN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Enable No Snoop.
 * If this bit is set, the function is permitted to Set the No Snoop bit in
 * the Requester Attributes of transactions it initiates that do not
 * require hardware enforced cache coherency (see section 2.2.6.5 in PCI
 * Express Base Specification).
 * Note: Setting this bit to 1b should not cause a function to set the No
 * Snoop attribute on all transactions that it initiates. Even when this
 * bit is set, a function is only permitted to set the No Snoop attribute
 * on a transaction when it can guarantee that the address of the
 * transaction is not stored in any cache in the system.
 *
 * The controller hardwires this bit 0b if a function would never set the
 * No Snoop attribute in transactions it initiates.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_EN_NO_SNOOP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_NO_SNOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_NO_SNOOP  VTSS_BIT(11)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_NO_SNOOP(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Max_Read_Request_Size.
 * This field sets the maximum Read Request size for the function as a
 * Requester. The function must not generate Read Requests with a size
 * exceeding the set value.
 * For functions that do not generate Read Requests larger than 128 bytes
 * and functions that do not generate Read Requests on their own behalf,
 * the controller implements this field as Read Only (RO) with a value of
 * 000b.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * 'h3:
 * 'h0:
 * 'h4:
 * 'h1:
 * 'h5:
 * 'h2:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_MAX_READ_REQ_SIZE
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_READ_REQ_SIZE(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_READ_REQ_SIZE     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_READ_REQ_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Correctable Error Detected.
 * This bit indicates status of correctable errors detected. Errors are
 * logged in this register regardless of whether error reporting is enabled
 * or not in the Device Control register. For a Multi-Function device, each
 * function indicates status of errors as perceived by the respective
 * function.
 *
 * For functions supporting Advanced Error Handling, errors are logged in
 * this register regardless of the settings of the Correctable Error Mask
 * register.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_CORR_ERR_DETECTED
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_DETECTED(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_DETECTED  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_DETECTED(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Non-Fatal Error Detected. This bit indicates status of Non-fatal errors
 * detected. Errors are logged in this register regardless of whether error
 * reporting is enabled or not in the Device Control register. For a
 * Multi-Function device, each function indicates status of errors as
 * perceived by the respective Function.
 *
 * For functions supporting Advanced Error Handling, errors are logged in
 * this register regardless of the settings of the Uncorrectable Error Mask
 * register.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_NON_FATAL_ERR_DETECTED
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_DETECTED(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_DETECTED  VTSS_BIT(17)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_DETECTED(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Fatal Error Detected. This bit indicates status of Fatal errors
 * detected. Errors are logged in this register regardless of whether error
 * reporting is enabled or not in the Device Control register. For a
 * Multi-Function device, each function indicates status of errors as
 * perceived by the respective Function.
 *
 * For Functions supporting Advanced Error Handling, errors are logged in
 * this register regardless of the settings of the Uncorrectable Error Mask
 * register.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_FATAL_ERR_DETECTED
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_DETECTED(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_DETECTED  VTSS_BIT(18)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_DETECTED(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Unsupported Request Detected.
 * This bit indicates that the function received an Unsupported Request.
 * Errors are logged in this register regardless of whether error reporting
 * is enabled or not in the Device Control register. For a Multi-Function
 * Device, each function indicates status of errors as perceived by the
 * respective function.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_UNSUPPORTED_REQ_DETECTED
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORTED_REQ_DETECTED(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORTED_REQ_DETECTED  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORTED_REQ_DETECTED(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * AUX Power Detected.
 * Functions that require Aux power report this bit as set if Aux power is
 * detected by the function.
 *
 * This bit is derived by sampling the sys_aux_pwr_det input.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_AUX_POWER_DETECTED
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_DETECTED(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_DETECTED  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_DETECTED(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Transactions Pending.
 *
 * Endpoints:
 *
 * When set, this bit indicates that the function has issued Non-Posted
 * Requests that have not been completed. A Function reports this bit
 * cleared only when all outstanding Non-Posted Requests have completed or
 * have been terminated by the Completion Timeout mechanism. This bit must
 * also be cleared upon the completion of an FLR.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS . PCIE_CAP_TRANS_PENDING
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_TRANS_PENDING(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_TRANS_PENDING  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_TRANS_PENDING(x)  VTSS_EXTRACT_BITFIELD(x,21,1)


/**
 * \brief The Link Capabilities register identifies PCI Express Link specific capabilities and CXL-RCRB link specific capabilities.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:LINK_CAPABILITIES_REG
 */
#define VTSS_PCIE_DBI_LINK_CAPABILITIES_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1f)

/**
 * \brief
 * Max Link Speed.
 * This field indicates the maximum Link speed of the associated Port.
 * The encoded value specifies a bit location in the Supported Link Speeds
 * Vector (in the Link Capabilities 2 register) that corresponds to the
 * maximum Link speed. All encodings other than the defined encodings are
 * reserved.
 *
 * Multi-Function Devices associated with an Upstream Port must report the
 * same value in this field for all functions.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_MAX_LINK_SPEED
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_SPEED(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_SPEED     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Maximum Link Width.
 * This field indicates the maximum Link width (xN - corresponding to N
 * Lanes) implemented by the component. This value is permitted to exceed
 * the number of Lanes routed to the slot (Downstream Port), adapter
 * connector (Upstream Port), or in the case of component-to-component
 * connections, the actual wired connection width.
 * All encodings other than the defined encodings are reserved.
 * Multi-Function devices associated with an Upstream Port must report the
 * same value in this field for all functions.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'hc:
 * 'h10:
 * 'h2:
 * 'h20:
 * 'h4:
 * 'h8:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_MAX_LINK_WIDTH
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_WIDTH     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/**
 * \brief
 * Active State Power Management (ASPM) Support.
 * This field indicates the level of ASPM supported on the given PCI
 * Express Link. For more information on ASPM support requirements, see
 * section 5.4.1 of PCI Express Base Specification.
 * Multi-Function devices associated with an Upstream Port must report the
 * same value in this field for all functions.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h3:
 * 'h1:
 * 'h2:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * L0s Exit Latency.
 * This field indicates the L0s exit latency for the given PCI Express
 * Link. The value reported indicates the length of time this Port requires
 * to complete transition from L0s to L0. If L0s is not supported, the
 * value is undefined; however, see the Implementation Note "Potential
 * Issues With Legacy Software When L0s is Not Supported" in section
 * 5.4.1.1 of PCI Express Base Specification for the recommended value.
 *
 * Note: Exit latencies may be influenced by PCI Express reference clock
 * configuration depending upon whether a component uses a common or
 * separate reference clock.
 *
 * Multi-Function Devices associated with an Upstream Port must report the
 * same value in this field for all functions.
 *
 * There are two each of these register fields, this one and a shadow one
 * at the same address.
 * The Common Clock bit (PCIE_CAP_COMMON_CLK_CONFIG) of the Link Control
 * Register (LINK_CONTROL_LINK_STATUS_REG) determines which one is used by
 * the controller and which one is accessed by a read request.
 * Common Clock operation is supported (possible) in the controller when
 * one or more of the following expressions is true:
 *  - CX_NFTS !=CX_COMM_NFTS
 *  - DEFAULT_L0S_EXIT_LATENCY !=DEFAULT_COMM_L0S_EXIT_LATENCY
 *  - DEFAULT_L1_EXIT_LATENCY !=DEFAULT_COMM_L1_EXIT_LATENCY
 * Common Clock operation is enabled in the controller when you set the
 * Common Clock bit (PCIE_CAP_COMMON_CLK_CONFIG) of the Link Control
 * Register (LINK_CONTROL_LINK_STATUS_REG).
 * The assertion of CS2 (that is, assert the dbi_cs2 input, or the CS2
 * address bit for the AXI bridge) is required to write to the shadow field
 * at this location.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h7:
 * 'h0:
 * 'h2:
 * 'h5:
 * 'h3:
 * 'h6:
 * 'h4:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_L0S_EXIT_LATENCY
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * L1 Exit Latency. This field indicates the L1 exit latency for the given
 * PCI Express Link. The value reported indicates the length of time this
 * Port requires to complete transition from ASPM L1 to L0. If ASPM L1 is
 * not supported, the value is undefined.
 *
 * Note: Exit latencies may be influenced by PCI Express reference clock
 * configuration depending upon whether a component uses a common or
 * separate reference clock.
 *
 * Multi-Function Devices associated with an Upstream Port must report the
 * same value in this field for all functions.
 *
 * There are two each of these register fields, this one and a shadow one
 * at the same address.
 * The Common Clock bit (PCIE_CAP_COMMON_CLK_CONFIG) of the Link Control
 * Register (LINK_CONTROL_LINK_STATUS_REG) determines which one is used by
 * the controller and which one is accessed by a read request.
 * Common Clock operation is supported (possible) in the controller when
 * one or more of the following expressions is true:
 *  - CX_NFTS !=CX_COMM_NFTS
 *  - DEFAULT_L0S_EXIT_LATENCY !=DEFAULT_COMM_L0S_EXIT_LATENCY
 *  - DEFAULT_L1_EXIT_LATENCY !=DEFAULT_COMM_L1_EXIT_LATENCY
 * Common Clock operation is enabled in the controller when you set the
 * Common Clock bit (PCIE_CAP_COMMON_CLK_CONFIG) of the Link Control
 * Register (LINK_CONTROL_LINK_STATUS_REG).
 * The assertion of CS2 (that is, assert the dbi_cs2 input, or the CS2
 * address bit for the AXI bridge) is required to write to the shadow field
 * at this location.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h7:
 * 'h0:
 * 'h5:
 * 'h1:
 * 'h2:
 * 'h6:
 * 'h3:
 * 'h4:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_L1_EXIT_LATENCY
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Clock Power Management.
 * For Upstream Ports, a value of 1b in this bit indicates that the
 * component tolerates the removal of any reference clock(s) through the
 * "clock request" (CLKREQ#) mechanism when the Link is in the L1 and L2/L3
 * Ready Link states. A value of 0b indicates the component does not have
 * this capability and that reference clock(s) must not be removed in these
 * Link states.
 *
 * L1 PM Substates defines other semantics for the CLKREQ# signal, which
 * are managed independently of Clock Power Management.
 *
 * This Capability is applicable only in form factors that support "clock
 * request" (CLKREQ#) capability.
 *
 * For a Multi-Function device associated with an Upstream Port, each
 * Function indicates its capability independently. Power Management
 * configuration software must only permit reference clock removal if all
 * functions of the Multi-Function device indicate a 1b in this bit. For
 * ARI Devices, all Functions must indicate the same value in this bit.
 *
 * Note:  The controller does not support this feature with PIPE 4.2
 * configuration if L1 Substate is not enabled.
 *
 * For Downstream Ports, the controller hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_CLOCK_POWER_MAN
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_CLOCK_POWER_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_CLOCK_POWER_MAN  VTSS_BIT(18)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_CLOCK_POWER_MAN(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Surprise Down Error Reporting Capable.
 * For a Downstream Port, this bit must be set if the component supports
 * the optional capability of detecting and reporting a Surprise Down error
 * condition.
 *
 * For Upstream Ports and components that do not support this optional
 * capability, the controller hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_SURPRISE_DOWN_ERR_REP_CAP
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_SURPRISE_DOWN_ERR_REP_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_SURPRISE_DOWN_ERR_REP_CAP  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_SURPRISE_DOWN_ERR_REP_CAP(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Data Link Layer Link Active Reporting Capable.
 * For a Downstream Port, the controller hardwires this bit to 1b if the
 * component supports the optional capability of reporting the DL_Active
 * state of the Data Link Control and Management State Machine. For a
 * hot-plug capable Downstream Port (as indicated by the Hot-Plug Capable
 * bit of the Slot Capabilities register) or a Downstream Port that
 * supports Link speeds greater than 5.0 GT/s, the controller hardwires
 * this bit to 1b.
 *
 * For Upstream Ports and components that do not support this optional
 * capability, the controller hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_DLL_ACTIVE_REP_CAP
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_DLL_ACTIVE_REP_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_DLL_ACTIVE_REP_CAP  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_DLL_ACTIVE_REP_CAP(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Link Bandwidth Notification Capability.
 * A value of 1b indicates support for the Link Bandwidth Notification
 * status and interrupt mechanisms. This capability is required for all
 * Root Ports and Switch Downstream Ports supporting Links wider than x1
 * and/or multiple Link speeds.
 *
 * This field is not applicable and is Reserved for Endpoints, PCI Express
 * to PCI/PCI-X bridges, and Upstream Ports of Switches.
 *
 * For functions that do not implement the Link Bandwidth Notification
 * Capability the controller hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_LINK_BW_NOT_CAP
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_LINK_BW_NOT_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_LINK_BW_NOT_CAP  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_LINK_BW_NOT_CAP(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * ASPM Optionality Compliance.
 * This field must be set to 1b in all functions. Components implemented
 * against certain earlier versions of this specification will have this
 * bit set to 0b.
 *
 * Software is permitted to use the value of this bit to help determine
 * whether to enable ASPM or whether to run ASPM compliance tests.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: HWINIT
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_ASPM_OPT_COMPLIANCE
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_ASPM_OPT_COMPLIANCE(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_ASPM_OPT_COMPLIANCE  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_ASPM_OPT_COMPLIANCE(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Port Number.
 * This field indicates the PCI Express Port number for the given PCI
 * Express Link.
 * Multi-Function Devices associated with an Upstream Port must report the
 * same value in this field for all functions.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: HWINIT
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES_REG . PCIE_CAP_PORT_NUM
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_PORT_NUM(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_PORT_NUM     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES_REG_PCIE_CAP_PORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief This register controls and provides information about PCI Express Link specific parameters as well as RCRB link associated parameters.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:LINK_CONTROL_LINK_STATUS_REG
 */
#define VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x20)

/**
 * \brief
 * Active State Power Management (ASPM) Control.
 * This field controls the level of ASPM enabled on the given PCI Express
 * Link. See section 5.4.1.3 of PCI Express Base Specification for
 * requirements on when and how to enable ASPM.
 *
 * Note: "L0s Entry Enabled" enables the Transmitter to enter L0s. If L0s
 * is supported, the Receiver must be capable of entering L0s even when the
 * Transmitter is disabled from entering L0s (00b or 10b).
 *
 * ASPM L1 must be enabled by software in the Upstream component on a Link
 * prior to enabling ASPM L1 in the Downstream component on that Link. When
 * disabling ASPM L1, software must disable ASPM L1 in the Downstream
 * component on a Link prior to disabling ASPM L1 in the Upstream component
 * on that Link. ASPM L1 must only be enabled on the Downstream component
 * if both components on a Link support ASPM L1.
 *
 * For Multi-Function Devices (including ARI Devices), it is recommended
 * that software program the same value for this field in all Functions.
 * For non-ARI Multi-Function Devices, only capabilities enabled in all
 * Functions are enabled for the component as a whole.
 *
 * For ARI Devices, ASPM Control is determined solely by the setting in
 * Function0, regardless of Function 0's D-state. The settings in the other
 * Functions always return whatever value software programmed for each, but
 * otherwise are ignored by the component.
 *
 * Software must not enable L0s in either direction on a given Link unless
 * components on both sides of the Link each support L0s; otherwise, the
 * result is undefined.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h3:
 * 'h2:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_ACTIVE_STATE_LINK_PM_CONTROL
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_CONTROL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Read Completion Boundary (RCB).
 *
 *
 * Endpoints and Bridges:
 * Optionally set by configuration software to indicate the RCB value of
 * the Root Port Upstream from the Endpoint or Bridge. Refer to Section
 * 2.3.1.1 of PCI Express Base Specification for the definition of the
 * parameter RCB is same as Root Port.
 * Configuration software must only set this bit if the Root Port Upstream
 * from the Endpoint or Bridge reports an RCB value of 128 bytes (a value
 * of 1b in the Read Completion Boundary bit).
 * For functions that do not implement this feature, the controller
 * hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_RCB
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RCB(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RCB  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RCB(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Link Disable.
 * This bit disables the Link by directing the LTSSM to the Disabled state
 * when set; this bit is Reserved on Endpoints, PCI Express to PCI/PCI-X
 * bridges, and Upstream Ports of Switches.
 *
 * Writes to this bit are immediately reflected in the value read from the
 * bit, regardless of actual Link state.
 *
 * After clearing this bit, software must honor timing requirements defined
 * in Section 6.6.1 with respect to the first Configuration Read following
 * a Conventional Reset.
 *
 * In a DSP that supports crosslink, the controller gates the write value
 * with the CROSS_LINK_EN field in PORT_LINK_CTRL_OFF.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: CX_CROSSLINK_ENABLE=1 &&
 * PORT_LINK_CTRL_OFF.CROSS_LINK_EN=1||CX_CROSSLINK_ENABLE=0 && dsp=1 ? RW
 * : RO
 *  - Dbi: CX_CROSSLINK_ENABLE=1 &&
 * PORT_LINK_CTRL_OFF.CROSS_LINK_EN=1||CX_CROSSLINK_ENABLE=0 && dsp=1? RW :
 * RO
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_LINK_DISABLE
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_DISABLE  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Retrain Link.
 * A write of 1b to this bit initiates Link retraining by directing the
 * Physical Layer LTSSM to the Recovery state. If the LTSSM is already in
 * Recovery or Configuration, re-entering Recovery is permitted but not
 * required. If the Port is in DPC when a write of 1b to this bit occurs,
 * the result is undefined. Reads of this bit always return 0b.
 *
 * It is permitted to write 1b to this bit while simultaneously writing
 * modified values to other fields in this register. If the LTSSM is not
 * already in Recovery or Configuration, the resulting Link training must
 * use the modified values. If the LTSSM is already in Recovery or
 * Configuration, the modified values are not required to affect the Link
 * training that's already in progress.
 *
 * This bit is not applicable and is Reserved for Endpoints, PCI Express to
 * PCI/PCI-X bridges, and Upstream Ports of Switches.
 *
 * This bit always returns 0b when read.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: see description
 *  - Dbi: see description
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_RETRAIN_LINK
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RETRAIN_LINK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RETRAIN_LINK  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RETRAIN_LINK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Common Clock Configuration. When set, this bit indicates that this
 * component and the component at the opposite end of this Link are
 * operating with a distributed common reference clock.
 *
 * A value of 0b indicates that this component and the component at the
 * opposite end of this Link are operating with asynchronous reference
 * clock.
 *
 * For non-ARI Multi-Function Devices, software must program the same value
 * for this bit in all Functions. If not all Functions are Set, then the
 * component must as a whole assume that its reference clock is not common
 * with the Upstream component.
 *
 * For ARI Devices, Common Clock Configuration is determined solely by the
 * setting in Function 0. The settings in the other Functions always return
 * whatever value software programmed for each, but otherwise are ignored
 * by the component.
 *
 * Components utilize this common clock configuration information to report
 * the correct L0s and L1 Exit Latencies.
 *
 * After changing the value in this bit in both components on a Link,
 * software must trigger the Link to retrain by writing a 1b to the Retrain
 * Link bit of the Downstream Port.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_COMMON_CLK_CONFIG
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_COMMON_CLK_CONFIG(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_COMMON_CLK_CONFIG  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_COMMON_CLK_CONFIG(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Extended Synch. When set, this bit forces the transmission of additional
 * Ordered Sets when exiting the L0s state (see section 4.2.4.5 of PCI
 * Express Base Specification) and when in the Recovery state (see section
 * 4.2.6.4.1 of PCI Express Base Specification). This mode provides
 * external devices (for example, logic analyzers) monitoring the Link time
 * to achieve bit and Symbol lock before the Link enters the L0 state and
 * resumes communication.
 *
 * For Multi-Function devices if any function has this bit set, then the
 * component must transmit the additional Ordered Sets when exiting L0s or
 * when in Recovery.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_EXTENDED_SYNCH
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EXTENDED_SYNCH(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EXTENDED_SYNCH  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EXTENDED_SYNCH(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable Clock Power Management.
 * Applicable only for Upstream Ports and with form factors that support a
 * "Clock Request" (CLKREQ#) mechanism, this bit operates as follows:
 * For a non-ARI Multi-Function Device, power-management-configuration
 * software must only Set this bit if all Functions of the Multi-Function
 * Device indicate a 1b in the Clock Power Management bit of the Link
 * Capabilities register. The component is permitted to use the CLKREQ#
 * signal to power manage Link clock only if this bit is Set for all
 * Functions.
 *
 * For ARI Devices, Clock Power Management is enabled solely by the setting
 * in Function 0. The settings in the other Functions always return
 * whatever value software programmed for each, but otherwise are ignored
 * by the component.
 * The CLKREQ# signal may also be controlled through the L1 PM Substates
 * mechanism. Such control is not affected by the setting of this bit.
 *
 * For Downstream Ports and components that do not support Clock Power
 * Management (as indicated by a 0b value in the Clock Power Management bit
 * of the Link Capabilities register), the controller hardwires this bit to
 * 0b.
 *
 * The write value is gated with the PCIE_CAP_CLOCK_POWER_MAN field in
 * LINK_CAPABILITIES_REG.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: LINK_CAPABILITIES_REG.PCIE_CAP_CLOCK_POWER_MAN ? RWS : ROS
 *  - Dbi: LINK_CAPABILITIES_REG.PCIE_CAP_CLOCK_POWER_MAN ? RWS : ROS
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_EN_CLK_POWER_MAN
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EN_CLK_POWER_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EN_CLK_POWER_MAN  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EN_CLK_POWER_MAN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Hardware Autonomous Width Disable.
 * When set, this bit disables hardware from changing the Link width for
 * reasons other than attempting to correct unreliable Link operation by
 * reducing Link width.
 *
 * For a Multi-Function Device associated with an Upstream Port, the bit in
 * Function 0 is of type RW, and only Function 0 controls the component's
 * Link behavior. In all other Functions of that device, this bit is of
 * type RsvdP.
 *
 * For components that do not implement the ability autonomously to change
 * Link width, the ciontroller hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_HW_AUTO_WIDTH_DISABLE
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_HW_AUTO_WIDTH_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_HW_AUTO_WIDTH_DISABLE  VTSS_BIT(9)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_HW_AUTO_WIDTH_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Link Bandwidth Management Interrupt Enable. When set, this bit enables
 * the generation of an interrupt to indicate that the Link Bandwidth
 * Management Status bit has been set. The write value is gated with the
 * PCIE_CAP_LINK_BW_NOT_CAP field in LINK_CAPABILITIES_REG.
 *
 * This bit is not applicable and is Reserved for Endpoints, PCI
 * Express-to-PCI/PCI-X bridges, and Upstream Ports of Switches.
 *
 * For functions that do not implement the Link Bandwidth Notification
 * Capability, the controller hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: LINK_CAPABILITIES_REG.PCIE_CAP_LINK_BW_NOT_CAP ? RW : RO
 *  - Dbi: LINK_CAPABILITIES_REG.PCIE_CAP_LINK_BW_NOT_CAP ? RW : RO
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_LINK_BW_MAN_INT_EN
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_INT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_INT_EN  VTSS_BIT(10)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_INT_EN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Link Autonomous Bandwidth Management Interrupt Enable.
 * When set, this bit enables the generation of an interrupt to indicate
 * that the Link Autonomous Bandwidth Status bit has been set. The write
 * value is gated with the PCIE_CAP_LINK_BW_NOT_CAP field in
 * LINK_CAPABILITIES_REG.
 *
 * This bit is not applicable and is Reserved for Endpoints, PCI
 * Express-to-PCI/PCI-X bridges, and Upstream Ports of Switches.
 *
 * For functions that do not implement the Link Bandwidth Notification
 * Capability, the controller hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: LINK_CAPABILITIES_REG.PCIE_CAP_LINK_BW_NOT_CAP ? RW : RO
 *  - Dbi: LINK_CAPABILITIES_REG.PCIE_CAP_LINK_BW_NOT_CAP ? RW : RO
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_LINK_AUTO_BW_INT_EN
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_INT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_INT_EN  VTSS_BIT(11)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_INT_EN(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * DRS Signaling Control. Indicates the mechanism used to report reception
 * of a DRS message. Must be implemented for Downstream Ports with the DRS
 * Supported bit Set in the Link Capabilities 2 Register. Encodings are:
 *
 * If DRS Supported is set, receiving a DRS Message will set DRS Message
 * Received in the Link Status 2 Register but will otherwise have no effect
 *
 * If the DRS Message Received bit in the Link Status 2 Register
 * transitions from 0 to 1, and either MSI or MSI-X is enabled, an MSI or
 * MSI-X interrupt is generated using the vector in Interrupt Message
 * Number (section 7.5.3.2)
 *
 * If the DRS Message Received bit in the Link Status 2 Register
 * transitions from 0 to 1, the Port must send an FRS Message Upstream with
 * the FRS Reason field set to DRS Message Received.
 *
 * Behavior is undefined if this field is set to 10b and the FRS Supported
 * bit in the Device Capabilities 2 Register is Clear.
 *
 * Behavior is undefined if this field is set to 11b.
 * For Downstream Ports with the DRS Supported bit clear in the Link
 * Capabilities 2 register, the controller hardwires this field to 00b.
 * This field is Reserved for Upstream Ports.
 *
 * \details
 * 'h1:
 * 'h0:
 * 'h2:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_DRS_SIGNALING_CONTROL
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DRS_SIGNALING_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DRS_SIGNALING_CONTROL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DRS_SIGNALING_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * Current Link Speed. This field indicates the negotiated Link speed of
 * the given PCI Express Link.
 * The encoded value specifies a bit location in the Supported Link Speeds
 * Vector (in the Link Capabilities 2 register) that corresponds to the
 * current Link speed.
 * All encodings other than the defined encodings are reserved.
 * The value in this field is undefined when the Link is not up.

 *
 * \details
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_LINK_SPEED
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Negotiated Link Width. This field indicates the negotiated width of the
 * given PCI Express Link.
 * All encodings other than the defined encodings are reserved.
 * The value in this field is undefined when the Link is not up.
 *
 * \details
 * 'h1:
 * 'hc:
 * 'h10:
 * 'h2:
 * 'h20:
 * 'h4:
 * 'h8:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_NEGO_LINK_WIDTH
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/**
 * \brief
 * Link Training. This read-only bit indicates that the Physical Layer
 * LTSSM is in the Configuration or Recovery state, or that 1b was written
 * to the Retrain Link bit but Link training has not yet begun. Hardware
 * clears this bit when the LTSSM exits the Configuration/Recovery state.
 *
 * This bit is not applicable and Reserved for Endpoints, PCI Express to
 * PCI/PCI-X bridges, and Upstream Ports of Switches, and the controller
 * hardwires it to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_LINK_TRAINING
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_TRAINING(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_TRAINING  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_TRAINING(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Slot Clock Configuration. This bit indicates that the component uses the
 * same physical reference clock that the platform provides on the
 * connector. If the device uses an independent clock irrespective of the
 * presence of a reference clock on the connector, this bit must be clear.
 *
 * For a Multi-Function Device, each Function must report the same value
 * for this bit.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: HWINIT
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_SLOT_CLK_CONFIG
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_SLOT_CLK_CONFIG(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_SLOT_CLK_CONFIG  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_SLOT_CLK_CONFIG(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Data Link Layer Link Active. This bit indicates the status of the Data
 * Link Control and Management State Machine. It returns a 1b to indicate
 * the DL_Active state, 0b otherwise.
 *
 * This bit must be implemented if the Data Link Layer Link Active
 * Reporting Capable bit is 1b. Otherwise, the controller hardwires it to
 * 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_DLL_ACTIVE
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DLL_ACTIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DLL_ACTIVE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DLL_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Link Bandwidth Management Status. This bit is set by hardware to
 * indicate that either of the following has occurred without the Port
 * transitioning through DL_Down status:
 *
 *  A Link retraining has completed following a write of 1b to the Retrain
 * Link bit.
 *
 * Note: This bit is set following any write of 1b to the Retrain Link bit,
 * including when the Link is in the process of retraining for some other
 * reason.
 *
 *  Hardware has changed Link speed or width to attempt to correct
 * unreliable Link operation, either through an LTSSM timeout or a higher
 * level process.
 *
 *  This bit must be set if the Physical Layer reports a speed or width
 * change was initiated by the Downstream component that was not indicated
 * as an autonomous change.
 * This bit is not applicable and is Reserved for Endpoints, PCI
 * Express-to-PCI/PCI-X bridges, and Upstream Ports of Switches.
 *
 * For functions that do not implement the Link Bandwidth Notification
 * Capability, the controller hardwires this bit to 0b.
 * The default value of this bit is 0b.
 *
 * The write value is gated with the PCIE_CAP_LINK_BW_NOT_CAP field in
 * LINK_CAPABILITIES_REG.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_LINK_BW_MAN_STATUS
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_STATUS  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Link Autonomous Bandwidth Status. This bit is set by hardware to
 * indicate that hardware has autonomously changed Link speed or width,
 * without the Port transitioning through DL_Down status, for reasons other
 * than to attempt to correct unreliable Link operation.
 *
 * This bit must be set if the Physical Layer reports a speed or width
 * change was initiated by the Downstream component that was indicated as
 * an autonomous change.
 *
 * The write value is gated with the PCIE_CAP_LINK_BW_NOT_CAP field in
 * LINK_CAPABILITIES_REG.
 *
 * This bit is not applicable and is Reserved for Endpoints, PCI
 * Express-to-PCI/PCI-X bridges, and Upstream Ports of Switches.
 *
 * For functions that do not implement the Link Bandwidth Notification
 * Capability, the controller hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG . PCIE_CAP_LINK_AUTO_BW_STATUS
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_STATUS  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief This register identifies PCI Express device specific capabilities; in addition to the Device Capabilities Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:DEVICE_CAPABILITIES2_REG
 */
#define VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x25)

/**
 * \brief
 * Completion Timeout Ranges Supported. This field indicates device
 * Function support for the optional Completion Timeout programmability
 * mechanism. This mechanism allows system software to modify the
 * Completion Timeout value.
 * This field is applicable only to Root Ports, Endpoints that issue
 * Requests on their own behalf, and PCI Express to PCI/PCI-X Bridges that
 * take ownership of Requests issued on PCI Express. For all other
 * Functions this field is Reserved and must be hardwired to 0000b.
 * Four time value ranges are defined:
 *  - Range A: 50 us to 10 ms
 *  - Range B: 10 ms to 250 ms
 *  - Range C: 250 ms to 4 s
 *  - Range D: 4 s to 64 s
 * Bits are set according to the list below to show timeout value ranges
 * supported.
 * All encodings other than the defined encodings are reserved.
 * It is strongly recommended that the Completion Timeout mechanism not
 * expire in less than 10 ms.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h3:
 * 'h7:
 * 'hf:
 * 'h2:
 * 'h6:
 * 'he:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_CPL_TIMEOUT_RANGE
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_RANGE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_RANGE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_RANGE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Completion Timeout Disable Supported. A value of 1b indicates support
 * for the Completion Timeout Disable mechanism.
 * The Completion Timeout Disable mechanism is required for Endpoints that
 * issue Requests on their own behalf and PCI Express to PCI/PCI-X Bridges
 * that take ownership of Requests issued on PCI Express.
 *
 * This mechanism is optional for Root Ports.
 *
 * For all other Functions this field is Reserved and the controller
 * hardwires this bit to 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_CPL_TIMEOUT_DISABLE_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE_SUPPORT  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * ARI Forwarding Supported. Applicable only to Switch Downstream Ports and
 * Root Ports; must be 0b for other Function types. This bit must be set to
 * 1b if a Switch Downstream Port or Root Port supports this optional
 * capability. For more information, see section 6.13 of PCI Express Base
 * Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_ARI_FORWARD_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * AtomicOp Routing Supported. Applicable only to Switch Upstream Ports,
 * Switch Downstream Ports, and Root Ports; must be 0b for other Function
 * types. This bit must be set to 1b if the Port supports this optional
 * capability. For more information, see section 6.15 of PCI Express Base
 * Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_ATOMIC_ROUTING_SUPP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ATOMIC_ROUTING_SUPP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ATOMIC_ROUTING_SUPP  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ATOMIC_ROUTING_SUPP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * 32-bit AtomicOp Completer Supported. Applicable to Functions with Memory
 * Space BARs as well as all Root Ports; must be 0b otherwise. Includes
 * FetchAdd, Swap, and CAS AtomicOps. This bit must be set to 1b if the
 * Function supports this optional capability.	For more information on
 * additional RC requirements, see section 6.15.3.1 of PCI Express Base
 * Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_32_ATOMIC_CPL_SUPP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_32_ATOMIC_CPL_SUPP(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_32_ATOMIC_CPL_SUPP  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_32_ATOMIC_CPL_SUPP(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * 64-bit AtomicOp Completer Supported. Applicable to Functions with Memory
 * Space BARs as well as all Root Ports; must be 0b otherwise. Includes
 * FetchAdd, Swap, and CAS AtomicOps. This bit must be set to 1b if the
 * Function supports this optional capability.	For more information on
 * additional RC requirements, see section 6.15.3.1 of PCI Express Base
 * Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_64_ATOMIC_CPL_SUPP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_64_ATOMIC_CPL_SUPP(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_64_ATOMIC_CPL_SUPP  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_64_ATOMIC_CPL_SUPP(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * 128-bit CAS Completer Supported. Applicable to Functions with Memory
 * Space BARs as well as all Root Ports; must be 0b otherwise. This bit
 * must be set to 1b if the Function supports this optional capability. For
 * more information, see section 6.15 of PCI Express Base Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_128_CAS_CPL_SUPP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_128_CAS_CPL_SUPP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_128_CAS_CPL_SUPP  VTSS_BIT(9)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_128_CAS_CPL_SUPP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * No RO-enabled PR-PR Passing. If this bit is set, the routing element
 * never carries out the passing permitted by Table 2-39 of PCI Express
 * Base Specification entry A2b that is associated with the Relaxed
 * Ordering Attribute field being Set.
 * This bit applies only for Switches and RCs that support peer-to-peer
 * traffic between Root Ports. This bit applies only to Posted Requests
 * being forwarded through the Switch or RC and does not apply to traffic
 * originating or terminating within the Switch or RC itself. All Ports on
 * a Switch or RC must report the same value for this bit.
 * For all other functions, this bit must be 0b.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_NO_RO_EN_PR2PR_PAR
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_NO_RO_EN_PR2PR_PAR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_NO_RO_EN_PR2PR_PAR  VTSS_BIT(10)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_NO_RO_EN_PR2PR_PAR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * TPH Completer Supported Bit 0.
 * Value of this bit along with TPH Completer Supported Bit 1 indicates
 * Completer support for TPH or Extended TPH. Applicable only to Root Ports
 * and Endpoints. For all other Functions, this field is Reserved.
 * For more information, see section 6.17 of PCI Express Base
 * Specification.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_TPH_CMPLT_SUPPORT_0
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_0(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_0  VTSS_BIT(12)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_0(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * TPH Completer Supported Bit 1.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_TPH_CMPLT_SUPPORT_1
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_1(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_1  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_1(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * LN System CLS.
 * Applicable only to Root Ports and RCRBs; must be 00b for all other
 * Function types. This field indicates if the Root Port or RCRB supports
 * LN protocol as an LN Completer, and if so, what cacheline size is in
 * effect.
 * All encodings other than the defined encodings are reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h2:
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP2_LN_SYS_CLS
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_LN_SYS_CLS(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_LN_SYS_CLS     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_LN_SYS_CLS(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * 10-Bit Tag Completer Supported. If this bit is set, the Function
 * supports 10-Bit Tag Completer capability; otherwise, the Function does
 * not. For more information, see section 2.2.6.2. of PCI Express Base
 * Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP2_10_BIT_TAG_COMP_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_10_BIT_TAG_COMP_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_10_BIT_TAG_COMP_SUPPORT  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_10_BIT_TAG_COMP_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * 10-Bit Tag Requester Supported. If this bit is set, the Function
 * supports 10-Bit Tag Requester capability; otherwise, the Function does
 * not.
 *
 * This bit must not be set if the 10-Bit Tag Completer Supported bit is
 * clear.
 *
 * Note: 10-Bit Tag field generation must be enabled by the 10-Bit Tag
 * Requester Enable bit in the Device Control 2 register of the Requester
 * Function before 10-Bit Tags can be generated by the Requester. For more
 * information, see section 2.2.6.2. of PCI Express Base Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP2_10_BIT_TAG_REQ_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_10_BIT_TAG_REQ_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_10_BIT_TAG_REQ_SUPPORT  VTSS_BIT(17)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_10_BIT_TAG_REQ_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Deferrable Memory Write (DMWr) Completer Supported. Applicable to
 * Functions with Memory Space BARs as well as all Root Ports; This bit
 * must be Set if the Function can serve as a DMWr Completer. For more
 * information, see Section 6.30 of PCI Express Base Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_DMWR_CPL_SUPP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_DMWR_CPL_SUPP(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_DMWR_CPL_SUPP  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_DMWR_CPL_SUPP(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Deferrable Memory Write (DMWr) Lengths Supported. Applicable to
 * Functions with either the DMWr Routing Supported bit Set or the DMWR
 * Completer Supported bit Set (or both). This field indicates the largest
 * DMWr TLP that this Function can receive.
 * When applicable, all Functions in a Multi-Function Device associated
 * with an Upstream Port must report the same value in this field.
 * This field is RsvdP if both DMWr Completer Supported and DMWr Routing
 * Supported are Clear.
 * For more information, see Section 6.30 of PCI Express Base
 * Specification.

 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CAPABILITIES2_REG . PCIE_CAP_DMWR_LEN_SUPP
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_DMWR_LEN_SUPP(x)  VTSS_ENCODE_BITFIELD(x,29,2)
#define  VTSS_M_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_DMWR_LEN_SUPP     VTSS_ENCODE_BITMASK(29,2)
#define  VTSS_X_PCIE_DBI_DEVICE_CAPABILITIES2_REG_PCIE_CAP_DMWR_LEN_SUPP(x)  VTSS_EXTRACT_BITFIELD(x,29,2)


/**
 * \brief This register controls PCI Express device specific parameters and provides information about PCI Express device (function) specific parameters; in addition to the Device Control and Device Status Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:DEVICE_CONTROL2_DEVICE_STATUS2_REG
 */
#define VTSS_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x26)

/**
 * \brief
 * Completion Timeout Value. In device Functions that support Completion
 * Timeout programmability, this field allows system software to modify the
 * Completion Timeout value. This field is applicable to Root Ports,
 * Endpoints that issue Requests on their own behalf, and PCI Express to
 * PCI/PCI-X Bridges that take ownership of Requests issued on PCI Express.
 * For all other Functions this field is Reserved and controller hardwires
 * it to 0000b.
 * A Function that does not support this optional capability must hardwire
 * this field to 0000b and is required to implement a timeout value in the
 * range 50 us to 50 ms. Functions that support Completion Timeout
 * programmability must support the values given below corresponding to the
 * programmability ranges indicated in the Completion Timeout Ranges
 * Supported field.
 * All encodings other than the defined encodings are reserved.
 *
 * It is strongly recommended that the Completion Timeout mechanism not
 * expire in less than 10 ms.
 *
 * Values available if Range A (50 us to 10 ms) programmability range is
 * supported:
 * Values available if Range B (10 ms to 250 ms) programmability range is
 * supported:
 * Values available if Range C (250 ms to 4 s) programmability range is
 * supported:
 * Values available if the Range D (4 s to 64 s) programmability range is
 * supported:
 *
 * Software is permitted to change the value in this field at any time. For
 * Requests already pending when the Completion Timeout Value is changed,
 * hardware is permitted to use either the new or the old value for the
 * outstanding Requests, and is permitted to base the start time for each
 * Request either on when this value was changed or on when each request
 * was issued.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * 'h0:
 * 'h5:
 * 'he:
 * 'h2:
 * 'ha:
 * 'h9:
 * 'hd:
 * 'h1:
 * 'h6:

 *
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG . PCIE_CAP_CPL_TIMEOUT_VALUE
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_VALUE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Completion Timeout Disable. When set, this bit disables the Completion
 * Timeout mechanism.
 * This bit is required for all Functions that support the Completion
 * Timeout Disable Capability. Functions that do not support this optional
 * capability are permitted to hardwire this bit to 0b
 *
 * Software is permitted to set or clear this bit at any time. When set,
 * the Completion Timeout detection mechanism is disabled. If there are
 * outstanding Requests when the bit is cleared, it is permitted but not
 * required for hardware to apply the completion timeout mechanism to the
 * outstanding Requests. If this is done, it is permitted to base the start
 * time for each Request on either the time this bit was cleared or the
 * time each Request was issued.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG . PCIE_CAP_CPL_TIMEOUT_DISABLE
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * ARI Forwarding Enable.
 * When set, the Downstream Port disables its traditional Device Number
 * field being 0 enforcement when turning a Type 1 Configuration Request
 * into a Type 0 Configuration Request, permitting access to Extended
 * Functions in an ARI Device immediately below the Port. For more
 * information, see Section 6.13 of PCI Express Base Specification.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG . PCIE_CAP_ARI_FORWARD_SUPPORT_CS
 */
#define  VTSS_F_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT_CS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT_CS  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT_CS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief This register identifies PCI Express Link specific capabilities and CXL-RCRB link specific capabilities; in addition to the Link Capabilities Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:LINK_CAPABILITIES2_REG
 */
#define VTSS_PCIE_DBI_LINK_CAPABILITIES2_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x27)

/**
 * \brief
 * Supported Link Speeds Vector. This field indicates the supported Link
 * speed(s) of the associated Port. For each bit, a value of 1b indicates
 * that the corresponding Link speed is supported; otherwise, the Link
 * speed is not supported. For more information, see section 8.2.1 of PCI
 * Express Base Specification.
 * Bit definitions within this field are:
 *  - 0: 2.5 GT/s
 *  - 1: 5.0 GT/s
 *  - 2: 8.0 GT/s
 *  - 3: 16.0 GT/s
 *  - 4: 32.0 GT/s
 *  - 6:5 RsvdP
 * Multi-Function Devices associated with an Upstream Port must report the
 * same value in this field for all Functions.
 *
 * This field has a default of (PCIE_CAP_MAX_LINK_SPEED == 0101) ? 0011111
 * : (PCIE_CAP_MAX_LINK_SPEED == 0100) ? 0001111 : (PCIE_CAP_MAX_LINK_SPEED
 * == 0011) ? 0000111 : (PCIE_CAP_MAX_LINK_SPEED == 0010) ? 0000011 :
 * 0000001 where PCIE_CAP_MAX_LINK_SPEED is a field in the
 * LINK_CAPABILITIES_REG register.

 *
 * \details
 * 'h7f:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES2_REG . PCIE_CAP_SUPPORT_LINK_SPEED_VECTOR
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES2_REG_PCIE_CAP_SUPPORT_LINK_SPEED_VECTOR(x)  VTSS_ENCODE_BITFIELD(x,1,7)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES2_REG_PCIE_CAP_SUPPORT_LINK_SPEED_VECTOR     VTSS_ENCODE_BITMASK(1,7)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES2_REG_PCIE_CAP_SUPPORT_LINK_SPEED_VECTOR(x)  VTSS_EXTRACT_BITFIELD(x,1,7)

/**
 * \brief
 * Crosslink Supported. When set to 1b, this bit indicates that the
 * associated Port supports crosslinks (for more details, see section
 * 4.2.6.3.1 of PCI Express Base Specification). When set to 0b on a Port
 * that supports Link speeds of 8.0 GT/s or higher, this bit indicates that
 * the associated Port does not support crosslinks. When set to 0b on a
 * Port that only supports Link speeds of 2.5 GT/s or 5.0 GT/s, this bit
 * provides no information regarding the Port's level of crosslink support.
 * It is recommended that this bit be Set in any Port that supports
 * crosslinks even though doing so is only required for Ports that also
 * support operating at 8.0 GT/s or higher Link speeds.
 *
 * Note: Software should use this bit when referencing fields whose
 * definition depends on whether or not the Port supports crosslinks (for
 * more details, see section 7.7.3.4 of PCI Express Base Specification).
 *
 * Multi-Function Devices associated with an Upstream Port must report the
 * same value in this field for all Functions.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CAPABILITIES2_REG . PCIE_CAP_CROSS_LINK_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_LINK_CAPABILITIES2_REG_PCIE_CAP_CROSS_LINK_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_LINK_CAPABILITIES2_REG_PCIE_CAP_CROSS_LINK_SUPPORT  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_LINK_CAPABILITIES2_REG_PCIE_CAP_CROSS_LINK_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief This register controls and provides information about PCI Express Link specific parameters as well as RCRB link associated parameters; in addition to the Link Control and Link Status Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PCIE_CAP:LINK_CONTROL2_LINK_STATUS2_REG
 */
#define VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x28)

/**
 * \brief
 * Target Link Speed. For Downstream Ports, this field sets an upper limit
 * on Link operational speed by restricting the values advertised by the
 * Upstream component in its training sequences.
 * The encoded value specifies a bit location in the Supported Link Speeds
 * Vector (in the Link Capabilities 2 register) that corresponds to the
 * desired target Link speed.
 * All encodings other than the defined encodings are reserved.
 *
 * If a value is written to this field that does not correspond to a
 * supported speed (as indicated by the Supported Link Speeds Vector), the
 * result is undefined.
 *
 * If either of the Enter Compliance or Enter Modified Compliance bits are
 * implemented, then this field must also be implemented.
 *
 * The default value of this field is the highest Link speed supported by
 * the component (as reported in the Max Link Speed field of the Link
 * Capabilities register) unless the corresponding platform/form factor
 * requires a different default value.
 *
 * For both Upstream and Downstream Ports, this field is used to set the
 * target compliance mode speed when software is using the Enter Compliance
 * bit to force a Link into compliance mode.
 *
 * For Upstream Ports, if the Enter Compliance bit is Clear, this field is
 * permitted to have no effect.
 *
 * For a Multi-Function Device associated with an Upstream Port, the field
 * in Function 0 is of type RWS, and only Function 0 controls the
 * component's Link behavior. In all other Functions of that device, this
 * field is of type RsvdP.
 *
 * Components that support only the 2.5 GT/s speed are permitted to
 * hardwire this field to 0000b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_TARGET_LINK_SPEED
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Enter Compliance. Software is permitted to force a Link to enter
 * Compliance mode (at the speed indicated in the Target Link Speed field
 * and the de-emphasis/preset level indicated by the Compliance
 * Preset/De-emphasis field) by setting this bit to 1b in both components
 * on a Link and then initiating a hot reset on the Link.
 *
 * Default value of this bit following Fundamental Reset is 0b.
 *
 * For a Multi-Function Device associated with an Upstream Port, the bit in
 * Function 0 is of type RWS, and only Function 0 controls the component's
 * Link behavior. In all other Functions of that device, this bit is of
 * type RsvdP.
 *
 * Components that support only the 2.5 GT/s speed are permitted to
 * hardwire this bit to 0b.
 *
 * This bit is intended for debug, compliance testing purposes only. System
 * firmware and software is allowed to modify this bit only during debug or
 * compliance testing. In all other cases, the system must ensure that this
 * bit is set to the default value.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_ENTER_COMPLIANCE
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_COMPLIANCE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_COMPLIANCE  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_COMPLIANCE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Hardware Autonomous Speed Disable. When set, this bit disables hardware
 * from changing the Link speed for device-specific reasons other than
 * attempting to correct unreliable Link operation by reducing Link speed.
 * Initial transition to the highest supported common link speed is not
 * blocked by this bit.
 *
 * For a Multi-Function Device associated with an Upstream Port, the bit in
 * Function 0 is of type RWS, and only Function 0 controls the component's
 * Link behavior. In all other Functions of that device, this bit is of
 * type RsvdP.
 *
 * Functions that do not implement the associated mechanism are permitted
 * to hardwire this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_HW_AUTO_SPEED_DISABLE
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_HW_AUTO_SPEED_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_HW_AUTO_SPEED_DISABLE  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_HW_AUTO_SPEED_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Selectable De-emphasis. When the Link is operating at 5.0 GT/s speed,
 * this bit is used to control the transmit de-emphasis of the link in
 * specific situations. For more information, see section 4.2.6 of PCI
 * Express Base Specification.
 * When the Link is not operating at 5.0 GT/s speed, the setting of this
 * bit has no effect. Components that support only the 2.5 GT/s speed are
 * permitted to hardwire this bit to 0b.
 *
 * This bit is not applicable and Reserved for Endpoints, PCI Express to
 * PCI/PCI-X bridges, and Upstream Ports of Switches.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_SEL_DEEMPHASIS
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_SEL_DEEMPHASIS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_SEL_DEEMPHASIS  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_SEL_DEEMPHASIS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Transmit Margin, This field controls the value of the non-deemphasized
 * voltage level at the Transmitter pins. This field is reset to 000b on
 * entry to the LTSSM Polling.Configuration substate (see Chapter 4 of PCI
 * Express Base Specification for details of how the Transmitter voltage
 * level is determined in various states).
 *  - 001b-111b: As defined in Section 8.3.4 not all encodings are required
 * to be implemented.
 * For a Multi-Function Device associated with an Upstream Port, the field
 * in Function 0 is of type RWS, and only Function 0 controls the
 * component's Link behavior. In all other Functions of that device, this
 * field is of type RsvdP.
 *
 * For components that support only the 2.5 GT/s speed, the controller
 * hardwires this bit to 000b.
 *
 * This field is intended for debug, compliance testing purposes only.
 * System firmware and software is allowed to modify this field only during
 * debug or compliance testing. In all other cases, the system must ensure
 * that this field is set to the default value.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_TX_MARGIN
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TX_MARGIN(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TX_MARGIN     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TX_MARGIN(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/**
 * \brief
 * Enter Modified Compliance. When this bit is set to 1b, the device
 * transmits Modified Compliance Pattern if the LTSSM enters
 * Polling.Compliance substate.
 * Components that support only the 2.5 GT/s speed are permitted to
 * hardwire this bit to 0b.
 *
 * For a Multi-Function Device associated with an Upstream Port, the bit in
 * Function 0 is of type RWS, and only Function 0 controls the component's
 * Link behavior. In all other Functions of that device, this bit is of
 * type RsvdP.
 *
 * This bit is intended for debug, compliance testing purposes only. System
 * firmware and software is allowed to modify this bit only during debug or
 * compliance testing. In all other cases, the system must ensure that this
 * bit is set to the default value.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_ENTER_MODIFIED_COMPLIANCE
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_MODIFIED_COMPLIANCE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_MODIFIED_COMPLIANCE  VTSS_BIT(10)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_MODIFIED_COMPLIANCE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Compliance SOS. When set to 1b, the LTSSM is required to send SKP
 * Ordered Sets between sequences when sending the Compliance Pattern or
 * Modified Compliance Pattern.
 *
 * For a Multi-Function Device associated with an Upstream Port, the bit in
 * Function 0 is of type RWS, and only Function 0 controls the component's
 * Link behavior. In all other Functions of that device, this bit is of
 * type RsvdP.
 *
 * This bit is applicable when the Link is operating at 2.5 GT/s or 5.0
 * GT/s data rates only.
 *
 * For components that support only the 2.5 GT/s speed, the controller
 * hardwires this bit to 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_COMPLIANCE_SOS
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_SOS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_SOS  VTSS_BIT(11)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_SOS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Compliance Preset/De-emphasis.
 *  - For 8.0 GT/s and higher Data Rate: This field sets the Transmitter
 * Preset in Polling.Compliance state if the entry occurred due to the
 * Enter Compliance bit being 1b. The encodings are defined in section
 * 4.2.3.2 of PCI Express Base Specification . Results are undefined if a
 * reserved preset encoding is used when entering Polling.Compliance in
 * this way.
 *  - For 5.0 GT/s Data Rate: This field sets the de-emphasis level in
 * Polling.Compliance state if the entry occurred due to the Enter
 * Compliance bit being 1b.
 *  - When the Link is operating at 2.5 GT/s, the setting of this field has
 * no effect. Components that support only 2.5 GT/s speed are permitted to
 * hardwire this field to 0000b.
 *  - For a Multi-Function Device associated with an Upstream Port, the
 * field in Function 0 is of type RWS, and only Function 0 controls the
 * component's Link behavior. In all other Functions of that device, this
 * field is of type RsvdP.
 *  - This field is intended for debug and compliance testing purposes.
 * System firmware and software is allowed to modify this field only during
 * debug or compliance testing. In all other cases, the system must ensure
 * that this field is set to the default value.
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_COMPLIANCE_PRESET
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_PRESET(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_PRESET     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_PRESET(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Current De-emphasis Level. When the Link is operating at 5.0 GT/s speed,
 * this bit reflects the level of de-emphasis.
 * The value in this bit is undefined when the Link is not operating at 5.0
 * GT/s speed.
 * Components that support only the 2.5 GT/s speed are permitted to
 * hardwire this bit to 0b.
 * For components that support speeds greater than 2.5 GT/s, Multi-Function
 * Devices associated with an Upstream Port must report the same value in
 * this field for all Functions of the Port.
 *
 *  In C-PCIe mode, its contents are derived by sampling the PIPE.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_CURR_DEEMPHASIS
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_CURR_DEEMPHASIS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_CURR_DEEMPHASIS  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_CURR_DEEMPHASIS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Equalization 8.0 GT/s Complete. When set to 1b, this bit indicates that
 * the Transmitter Equalization procedure at the 8.0 GT/s data rate has
 * completed. Details of the Transmitter Equalization process and when this
 * bit needs to be set to 1b is provided in section 4.2.6.4.2 of PCI
 * Express Base Specification.
 *
 * For Multi-Function Upstream Port, this bit must be implemented in
 * Function 0 and RsvdZ in other Functions. For components that only
 * support speeds below 8.0 GT/s, the controller hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_EQ_CPL
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL  VTSS_BIT(17)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Equalization 8.0 GT/s Phase 1 Successful. When set to 1b, this bit
 * indicates that Phase 1 of the 8.0 GT/s Transmitter Equalization
 * procedure has successfully completed. Details of the Transmitter
 * Equalization process and when this bit needs to be set to 1b is provided
 * in section 4.2.6.4.2 of PCI Express Base Specification.
 *
 * For Multi-Function Upstream Port, this bit must be implemented in
 * Function 0 and RsvdZ in other Functions. For components that only
 * support speeds below 8.0 GT/s, the controller hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_EQ_CPL_P1
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P1(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P1  VTSS_BIT(18)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P1(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Equalization 8.0 GT/s Phase 2 Successful. When set to 1b, this bit
 * indicates that Phase 2 of the 8.0 GT/s Transmitter Equalization
 * procedure has successfully completed. Details of the Transmitter
 * Equalization process and when this bit needs to be set to 1b is provided
 * in section 4.2.6.4.2 of PCI Express Base Specification.
 *
 * For Multi-Function Upstream Port, this bit must be implemented in
 * Function 0 and RsvdZ in other Functions. For components that only
 * support speeds below 8.0 GT/s, the controller hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_EQ_CPL_P2
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P2(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P2  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P2(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * EEqualization 8.0 GT/s Phase 3 Successful. When set to 1b, this bit
 * indicates that Phase 3 of the 8.0 GT/s Transmitter Equalization
 * procedure has successfully completed. Details of the Transmitter
 * Equalization process and when this bit needs to be set to 1b is provided
 * in section 4.2.6.4.2 of PCI Express Base Specification.
 *
 * For Multi-Function Upstream Port, this bit must be implemented in
 * Function 0 and RsvdZ in other Functions. For components that only
 * support speeds below 8.0 GT/s, the controller hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_EQ_CPL_P3
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P3(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P3  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P3(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Link Equalization Request 8.0 GT/s. This bit is set by hardware to
 * request the 8.0 GT/s Link equalization process to be performed on the
 * Link. For more information, see sections 4.2.3 and 4.2.6.4.2 of PCI
 * Express Base Specification.
 *
 * For Multi-Function Upstream Port, this bit must be implemented in
 * Function 0 and RsvdZ in other Functions. For components that only
 * support speeds below 8.0 GT/s, the controller hardwires this bit to 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG . PCIE_CAP_LINK_EQ_REQ
 */
#define  VTSS_F_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_LINK_EQ_REQ(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_LINK_EQ_REQ  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_LINK_EQ_REQ(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * Register Group: \a PCIE_DBI:PF0_AER_CAP
 *
 * PF Advanced Error Reporting Capability Structure
 */


/**
 * \brief Advanced Error Reporting Extended Capability Header provides information about Capability ID, Version, and next offset.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:AER_EXT_CAP_HDR_OFF
 */
#define VTSS_PCIE_DBI_AER_EXT_CAP_HDR_OFF    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x40)

/**
 * \brief
 * AER Extended Capability ID.
 * This field is a PCI-SIG defined ID number that indicates the nature and
 * format of the Extended Capability.
 * The Extended Capability ID for the Advanced Error Reporting Capability
 * is 0001h.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_AER_EXT_CAP_HDR_OFF . CAP_ID
 */
#define  VTSS_F_PCIE_DBI_AER_EXT_CAP_HDR_OFF_CAP_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_AER_EXT_CAP_HDR_OFF_CAP_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_AER_EXT_CAP_HDR_OFF_CAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Capability Version.
 * This field is a PCI-SIG defined version number that indicates the
 * version of the Capability structure present.
 * This field must be 2h if the End-End TLP Prefix Supported bit is set and
 * must be 1h or 2h otherwise.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_AER_EXT_CAP_HDR_OFF . CAP_VERSION
 */
#define  VTSS_F_PCIE_DBI_AER_EXT_CAP_HDR_OFF_CAP_VERSION(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_PCIE_DBI_AER_EXT_CAP_HDR_OFF_CAP_VERSION     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_PCIE_DBI_AER_EXT_CAP_HDR_OFF_CAP_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Next Capability Offset.
 * This field contains the offset to the next PCI Express Capability
 * structure or 000h if no other items exist in the linked list of
 * Capabilities.
 * For Extended Capabilities implemented in Configuration Space, this
 * offset is relative to the beginning of PCI-compatible Configuration
 * Space and
 * thus must always be either 000h (for terminating list of Capabilities)
 * or greater than 0FFh.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W(sticky) else R(sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_AER_EXT_CAP_HDR_OFF . NEXT_OFFSET
 */
#define  VTSS_F_PCIE_DBI_AER_EXT_CAP_HDR_OFF_NEXT_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,20,12)
#define  VTSS_M_PCIE_DBI_AER_EXT_CAP_HDR_OFF_NEXT_OFFSET     VTSS_ENCODE_BITMASK(20,12)
#define  VTSS_X_PCIE_DBI_AER_EXT_CAP_HDR_OFF_NEXT_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,20,12)


/**
 * \brief The Uncorrectable Error Status Register (Offset 04h) indicates error detection status of individual errors on a PCI Express device Function.
An individual error status bit that is Set indicates that a particular error was detected; software may clear an error status by writing a 1b to the respective bit.
Register bits not implemented by the Function are hardwired to 0b.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:UNCORR_ERR_STATUS_OFF
 */
#define VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x41)

/**
 * \brief
 * Data Link Protocol Error Status.
 * Status bit for Data Link Protocol Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . DL_PROTOCOL_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_DL_PROTOCOL_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_DL_PROTOCOL_ERR_STATUS  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_DL_PROTOCOL_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Surprise Down Error Status (Optional).
 * Status bit for Surprise Down Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . SURPRISE_DOWN_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_SURPRISE_DOWN_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_SURPRISE_DOWN_ERR_STATUS  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_SURPRISE_DOWN_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Poisoned TLP Status.
 * Status bit for Poisoned TLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . POIS_TLP_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_POIS_TLP_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_POIS_TLP_ERR_STATUS  VTSS_BIT(12)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_POIS_TLP_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Flow Control Protocol Error Status.
 * Status bit for Flow Control Protocol Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . FC_PROTOCOL_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_FC_PROTOCOL_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_FC_PROTOCOL_ERR_STATUS  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_FC_PROTOCOL_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Completion Timeout Status.
 * Status for Completion Timeout.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . CMPLT_TIMEOUT_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_CMPLT_TIMEOUT_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_CMPLT_TIMEOUT_ERR_STATUS  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_CMPLT_TIMEOUT_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Completer Abort Status.
 * Status bit for Completer Abort.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . CMPLT_ABORT_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_CMPLT_ABORT_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_CMPLT_ABORT_ERR_STATUS  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_CMPLT_ABORT_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Unexpected Completion Status.
 * Status bit for Unexpected Completion.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . UNEXP_CMPLT_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_UNEXP_CMPLT_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_UNEXP_CMPLT_ERR_STATUS  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_UNEXP_CMPLT_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Receiver Overflow Status.
 * Status bit for Receiver Overflow.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . REC_OVERFLOW_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_REC_OVERFLOW_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_REC_OVERFLOW_ERR_STATUS  VTSS_BIT(17)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_REC_OVERFLOW_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Malformed TLP Status.
 * This field represents status of Malformed TLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . MALF_TLP_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_MALF_TLP_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_MALF_TLP_ERR_STATUS  VTSS_BIT(18)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_MALF_TLP_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * ECRC Error Status.
 * This field represents status of ECRC Error.
 *
 * Note:If CX_ECRC_ENABLE=0 the register field always reads 0.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . ECRC_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_ECRC_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_ECRC_ERR_STATUS  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_ECRC_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Unsupported Request Error Status.
 * This field represents status of Unsupported Request Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . UNSUPPORTED_REQ_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_UNSUPPORTED_REQ_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_UNSUPPORTED_REQ_ERR_STATUS  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_UNSUPPORTED_REQ_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Uncorrectable Internal Error Status.
 * This field gives status of the Uncorrectable Internal Error.
 *
 * The controller sets this bit when your application asserts
 * app_err_bus[9]. It does not set this bit when it detects internal
 * uncorrectable internal errors such as parity and ECC failures. You
 * should use the outputs from these errors to drive the app_err_bus[9]
 * input. For more information, see the "Data Integrity (Wire, Datapath,
 * and RAM Protection)" section in the Databook.
 *
 * This register field is reserved for VFs.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_STATUS_OFF . INTERNAL_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_STATUS_OFF_INTERNAL_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_STATUS_OFF_INTERNAL_ERR_STATUS  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_STATUS_OFF_INTERNAL_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,22,1)


/**
 * \brief The Uncorrectable Error Mask Register controls reporting of individual errors by the device Function to the PCI Express Root Complex through a PCI Express error Message.
A masked error (respective bit Set in the mask register) is not recorded or reported in the Header Log, TLP Prefix Log, or First Error Pointer, and is not reported to the PCI Express Root Complex by this Function.
There is a mask bit per error bit of the Uncorrectable Error Status register. Register fields for bits not implemented by the Function are hardwired to 0b.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:UNCORR_ERR_MASK_OFF
 */
#define VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x42)

/**
 * \brief
 * Data Link Protocol Error Mask.
 * This field informs whether Data Link Protocol Error is masked or not.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . DL_PROTOCOL_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_DL_PROTOCOL_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_DL_PROTOCOL_ERR_MASK  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_DL_PROTOCOL_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Surprise Down Error Mask.
 * Mask bit for Surprise Down Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . SURPRISE_DOWN_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_SURPRISE_DOWN_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_SURPRISE_DOWN_ERR_MASK  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_SURPRISE_DOWN_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Poisoned TLP Error Mask.
 * Mask bit for Poisoned TLP Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . POIS_TLP_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_POIS_TLP_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_POIS_TLP_ERR_MASK  VTSS_BIT(12)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_POIS_TLP_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Flow Control Protocol Error Mask.
 * Mask bit for Flow Control Protocol Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . FC_PROTOCOL_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_FC_PROTOCOL_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_FC_PROTOCOL_ERR_MASK  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_FC_PROTOCOL_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Completion Timeout Error Mask.
 * Mask bit for Completion Timeout Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . CMPLT_TIMEOUT_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_CMPLT_TIMEOUT_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_CMPLT_TIMEOUT_ERR_MASK  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_CMPLT_TIMEOUT_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Completer Abort Error Mask (Optional).
 * Mask bit for Completer Abort Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . CMPLT_ABORT_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_CMPLT_ABORT_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_CMPLT_ABORT_ERR_MASK  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_CMPLT_ABORT_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Unexpected Completion Mask.
 * Mask bit for Unexpected Completion Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . UNEXP_CMPLT_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_UNEXP_CMPLT_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_UNEXP_CMPLT_ERR_MASK  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_UNEXP_CMPLT_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Receiver Overflow Mask (Optional).
 * This field represents Receiver Overflow Mask.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . REC_OVERFLOW_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_REC_OVERFLOW_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_REC_OVERFLOW_ERR_MASK  VTSS_BIT(17)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_REC_OVERFLOW_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Malformed TLP Mask.
 * Mask bit for Malformed TLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . MALF_TLP_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_MALF_TLP_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_MALF_TLP_ERR_MASK  VTSS_BIT(18)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_MALF_TLP_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * ECRC Error Mask (Optional).
 * Mask bit for ECRC Error.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . ECRC_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_ECRC_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_ECRC_ERR_MASK  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_ECRC_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Unsupported Request Error Mask.
 * Mask bit for Unsupported Request Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . UNSUPPORTED_REQ_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_UNSUPPORTED_REQ_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_UNSUPPORTED_REQ_ERR_MASK  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_UNSUPPORTED_REQ_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Uncorrectable Internal Error Mask (Optional).
 * Mask bit for Uncorrectable Internal Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . INTERNAL_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_INTERNAL_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_INTERNAL_ERR_MASK  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_INTERNAL_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * AtomicOp Egress Block Mask (Optional).
 * Mask bit for AtomicOp Egress Block Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . ATOMIC_EGRESS_BLOCKED_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_ATOMIC_EGRESS_BLOCKED_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_ATOMIC_EGRESS_BLOCKED_ERR_MASK  VTSS_BIT(24)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_ATOMIC_EGRESS_BLOCKED_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * TLP Prefix Blocked Error Mask.
 * Mask bit for TLP Prefix Blocked Error.
 *
 * Note: Not supported.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . TLP_PRFX_BLOCKED_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_TLP_PRFX_BLOCKED_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_TLP_PRFX_BLOCKED_ERR_MASK  VTSS_BIT(25)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_TLP_PRFX_BLOCKED_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Deferrable Memory Write Egress Block Mask (Optional).
 * Mask bit for Deferrable Memory Write Egress Block Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_MASK_OFF . DMWR_EGRESS_BLOCKED_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_MASK_OFF_DMWR_EGRESS_BLOCKED_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_MASK_OFF_DMWR_EGRESS_BLOCKED_ERR_MASK  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_MASK_OFF_DMWR_EGRESS_BLOCKED_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,27,1)


/**
 * \brief The Uncorrectable Error Severity Register controls whether an individual error is reported as a Non-fatal or Fatal error.
An error is reported as fatal when the corresponding error bit in the severity register is Set. If the bit is Clear, the corresponding error is considered non-fatal.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:UNCORR_ERR_SEV_OFF
 */
#define VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF     VTSS_IOREG(VTSS_TO_PCIE_DBI,0x43)

/**
 * \brief
 * Data Link Protocol Error Severity.
 * Severity bit for Data Link Protocol Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . DL_PROTOCOL_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_DL_PROTOCOL_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_DL_PROTOCOL_ERR_SEVERITY  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_DL_PROTOCOL_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Surprise Down Error Severity (Optional).
 * Severity bit for Surprise Down Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . SURPRISE_DOWN_ERR_SVRITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_SURPRISE_DOWN_ERR_SVRITY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_SURPRISE_DOWN_ERR_SVRITY  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_SURPRISE_DOWN_ERR_SVRITY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Poisoned TLP Severity.
 * Severity bit for Poisoned TLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . POIS_TLP_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_POIS_TLP_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_POIS_TLP_ERR_SEVERITY  VTSS_BIT(12)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_POIS_TLP_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Flow Control Protocol Error Severity (Optional).
 * Severity bit for Flow Control Protocol Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . FC_PROTOCOL_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_FC_PROTOCOL_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_FC_PROTOCOL_ERR_SEVERITY  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_FC_PROTOCOL_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Completion Timeout Error Severity.
 * Severity bit for Completion Timeout Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . CMPLT_TIMEOUT_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_CMPLT_TIMEOUT_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_CMPLT_TIMEOUT_ERR_SEVERITY  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_CMPLT_TIMEOUT_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Completer Abort Error Severity (Optional).
 * Severity bit for Completer Abort Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . CMPLT_ABORT_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_CMPLT_ABORT_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_CMPLT_ABORT_ERR_SEVERITY  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_CMPLT_ABORT_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Unexpected Completion Error Severity.
 * Severity bit for Unexpected Completion Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . UNEXP_CMPLT_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_UNEXP_CMPLT_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_UNEXP_CMPLT_ERR_SEVERITY  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_UNEXP_CMPLT_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Receiver Overflow Error Severity (Optional).
 * Severity bit for Receiver Overflow Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . REC_OVERFLOW_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_REC_OVERFLOW_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_REC_OVERFLOW_ERR_SEVERITY  VTSS_BIT(17)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_REC_OVERFLOW_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Malformed TLP Severity.
 * Severity bit for Malformed TLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . MALF_TLP_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_MALF_TLP_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_MALF_TLP_ERR_SEVERITY  VTSS_BIT(18)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_MALF_TLP_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * ECRC Error Severity (Optional).
 * Severity bit for ECRC Error.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . ECRC_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_ECRC_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_ECRC_ERR_SEVERITY  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_ECRC_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Unsupported Request Error Severity.
 * Severity bit for Unsupported Request Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . UNSUPPORTED_REQ_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_UNSUPPORTED_REQ_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_UNSUPPORTED_REQ_ERR_SEVERITY  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_UNSUPPORTED_REQ_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Uncorrectable Internal Error Severity (Optional).
 * Severity bit for Uncorrectable Internal Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . INTERNAL_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_INTERNAL_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_INTERNAL_ERR_SEVERITY  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_INTERNAL_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * TLP Prefix Blocked Error Severity (Optional).
 * Severity bit for TLP Prefix Blocked Error.
 *
 * Note: Not supported.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . TLP_PRFX_BLOCKED_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_TLP_PRFX_BLOCKED_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_TLP_PRFX_BLOCKED_ERR_SEVERITY  VTSS_BIT(25)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_TLP_PRFX_BLOCKED_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Deferrable Memory Write Egress Blocked Severity (Optional).
 * Severity bit for Deferrable Memory Write Egress Blocked Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UNCORR_ERR_SEV_OFF . DMWR_EGRESS_BLOCKED_ERR_SEVERITY
 */
#define  VTSS_F_PCIE_DBI_UNCORR_ERR_SEV_OFF_DMWR_EGRESS_BLOCKED_ERR_SEVERITY(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_UNCORR_ERR_SEV_OFF_DMWR_EGRESS_BLOCKED_ERR_SEVERITY  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_UNCORR_ERR_SEV_OFF_DMWR_EGRESS_BLOCKED_ERR_SEVERITY(x)  VTSS_EXTRACT_BITFIELD(x,27,1)


/**
 * \brief The Correctable Error Status register reports error status of individual correctable error sources on a PCI Express device Function.
When an individual error status bit is Set, it indicates that a particular error occurred; software may clear an error status by writing a 1b to the respective bit.
Register bits not implemented by the Function are hardwired to 0b by the controller.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:CORR_ERR_STATUS_OFF
 */
#define VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x44)

/**
 * \brief
 * Receiver Error Status (Optional).
 * This field provides status of Receiver Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF . RX_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_STATUS_OFF_RX_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_STATUS_OFF_RX_ERR_STATUS  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_CORR_ERR_STATUS_OFF_RX_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Bad TLP Status.
 * Status bit for Bad TLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF . BAD_TLP_STATUS
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_STATUS_OFF_BAD_TLP_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_STATUS_OFF_BAD_TLP_STATUS  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_CORR_ERR_STATUS_OFF_BAD_TLP_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Bad DLLP Status.
 * Status bit for Bad DLLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF . BAD_DLLP_STATUS
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_STATUS_OFF_BAD_DLLP_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_STATUS_OFF_BAD_DLLP_STATUS  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_CORR_ERR_STATUS_OFF_BAD_DLLP_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * REPLAY_NUM Rollover Status.
 * Status bit for REPLAY_NUM Rollover.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF . REPLAY_NO_ROLEOVER_STATUS
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_STATUS_OFF_REPLAY_NO_ROLEOVER_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_STATUS_OFF_REPLAY_NO_ROLEOVER_STATUS  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_CORR_ERR_STATUS_OFF_REPLAY_NO_ROLEOVER_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Replay Timer Timeout Status.
 * Status bit for Replay Timer Timeout.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF . RPL_TIMER_TIMEOUT_STATUS
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_STATUS_OFF_RPL_TIMER_TIMEOUT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_STATUS_OFF_RPL_TIMER_TIMEOUT_STATUS  VTSS_BIT(12)
#define  VTSS_X_PCIE_DBI_CORR_ERR_STATUS_OFF_RPL_TIMER_TIMEOUT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Advisory Non-Fatal Error Status.
 * Status bit for Advisory Non-Fatal Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF . ADVISORY_NON_FATAL_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_STATUS_OFF_ADVISORY_NON_FATAL_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_STATUS_OFF_ADVISORY_NON_FATAL_ERR_STATUS  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_CORR_ERR_STATUS_OFF_ADVISORY_NON_FATAL_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Corrected Internal Error Status (Optional).
 * This field provides status of Corrected Internal Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF . CORRECTED_INT_ERR_STATUS
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_STATUS_OFF_CORRECTED_INT_ERR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_STATUS_OFF_CORRECTED_INT_ERR_STATUS  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_CORR_ERR_STATUS_OFF_CORRECTED_INT_ERR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Header Log Overflow Error Status (Optional).
 * This field provides status of Header Log Overflow Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_STATUS_OFF . HEADER_LOG_OVERFLOW_STATUS
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_STATUS_OFF_HEADER_LOG_OVERFLOW_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_STATUS_OFF_HEADER_LOG_OVERFLOW_STATUS  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_CORR_ERR_STATUS_OFF_HEADER_LOG_OVERFLOW_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/**
 * \brief The Correctable Error Mask Register controls reporting of individual correctable errors by this Function to the PCI Express Root Complex through a PCI Express error Message.
A masked error (respective bit Set in the mask register) is not reported to the PCI Express Root Complex by this Function.
There is a mask bit per error bit in the Correctable Error Status register. Register fields for bits not implemented by the Function are hardwired to 0b by the controller.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:CORR_ERR_MASK_OFF
 */
#define VTSS_PCIE_DBI_CORR_ERR_MASK_OFF      VTSS_IOREG(VTSS_TO_PCIE_DBI,0x45)

/**
 * \brief
 * Receiver Error Mask (Optional).
 * Masking bit for Receiver Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_MASK_OFF . RX_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_MASK_OFF_RX_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_MASK_OFF_RX_ERR_MASK  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_CORR_ERR_MASK_OFF_RX_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Bad TLP Mask.
 * Masking bit for Bad TLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_MASK_OFF . BAD_TLP_MASK
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_MASK_OFF_BAD_TLP_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_MASK_OFF_BAD_TLP_MASK  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_CORR_ERR_MASK_OFF_BAD_TLP_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Bad DLLP Mask.
 * Masking bit for Bad DLLP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_MASK_OFF . BAD_DLLP_MASK
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_MASK_OFF_BAD_DLLP_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_MASK_OFF_BAD_DLLP_MASK  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_CORR_ERR_MASK_OFF_BAD_DLLP_MASK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * REPLAY_NUM Rollover Mask.
 * Masking bit for REPLAY_NUM Rollover.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_MASK_OFF . REPLAY_NO_ROLEOVER_MASK
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_MASK_OFF_REPLAY_NO_ROLEOVER_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_MASK_OFF_REPLAY_NO_ROLEOVER_MASK  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_CORR_ERR_MASK_OFF_REPLAY_NO_ROLEOVER_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Replay Timer Timeout Mask.
 * Masking bit for Replay Timer Timeout.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_MASK_OFF . RPL_TIMER_TIMEOUT_MASK
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_MASK_OFF_RPL_TIMER_TIMEOUT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_MASK_OFF_RPL_TIMER_TIMEOUT_MASK  VTSS_BIT(12)
#define  VTSS_X_PCIE_DBI_CORR_ERR_MASK_OFF_RPL_TIMER_TIMEOUT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Advisory Non-Fatal Error Mask.
 * Masking bit for Advisory Non-Fatal Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_MASK_OFF . ADVISORY_NON_FATAL_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_MASK_OFF_ADVISORY_NON_FATAL_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_MASK_OFF_ADVISORY_NON_FATAL_ERR_MASK  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_CORR_ERR_MASK_OFF_ADVISORY_NON_FATAL_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Corrected Internal Error Mask (Optional).
 * Masking bit for Corrected Internal Error Mask.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_MASK_OFF . CORRECTED_INT_ERR_MASK
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_MASK_OFF_CORRECTED_INT_ERR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_MASK_OFF_CORRECTED_INT_ERR_MASK  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_CORR_ERR_MASK_OFF_CORRECTED_INT_ERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Header Log Overflow Error Mask (Optional).
 * Masking bit for Header Log Overflow Error.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_CORR_ERR_MASK_OFF . HEADER_LOG_OVERFLOW_MASK
 */
#define  VTSS_F_PCIE_DBI_CORR_ERR_MASK_OFF_HEADER_LOG_OVERFLOW_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_CORR_ERR_MASK_OFF_HEADER_LOG_OVERFLOW_MASK  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_CORR_ERR_MASK_OFF_HEADER_LOG_OVERFLOW_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/**
 * \brief Advanced Error Capabilities and Control Register provides information whether the individual capability is supported or not. If the capability is supported then it is enabled or not.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:ADV_ERR_CAP_CTRL_OFF
 */
#define VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x46)

/**
 * \brief
 * First Error Pointer.
 * The First Error Pointer is a field that identifies the bit position of
 * the first error reported in the Uncorrectable Error Status register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF . FIRST_ERR_POINTER
 */
#define  VTSS_F_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_FIRST_ERR_POINTER(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_FIRST_ERR_POINTER     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_FIRST_ERR_POINTER(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * ECRC Generation Capable.
 * If Set, this bit indicates that the Function is capable of generating
 * ECRC.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF . ECRC_GEN_CAP
 */
#define  VTSS_F_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_CAP  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_CAP(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * ECRC Generation Enable.
 * When Set, ECRC generation is enabled. Functions that do not implement
 * the associated mechanism are permitted to hardwire this bit to 0b.
 * Default value of this bit is 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF . ECRC_GEN_EN
 */
#define  VTSS_F_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_EN  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * ECRC Check Capable.
 * If Set, this bit indicates that the Function is capable of checking
 * ECRC.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF . ECRC_CHECK_CAP
 */
#define  VTSS_F_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_CAP  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_CAP(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ECRC Check Enable.
 * When Set, ECRC checking is enabled. Functions that do not implement the
 * associated mechanism are permitted to hardwire this bit to 0b.
 * Default value of this bit is 0b.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF . ECRC_CHECK_EN
 */
#define  VTSS_F_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_EN  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_EN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Multiple Header Recording Capable.
 * If Set, this bit indicates that the Function is capable of recording
 * more than one error header.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF . MULTIPLE_HEADER_CAP
 */
#define  VTSS_F_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_CAP  VTSS_BIT(9)
#define  VTSS_X_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_CAP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Multiple Header Recording Enable.
 * When Set, this bit enables the Function to record more than one error
 * header. Functions that do not implement the associated mechanism are
 * permitted to hardwire this bit to 0b.
 * Default value of this bit is 0b.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF . MULTIPLE_HEADER_EN
 */
#define  VTSS_F_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_EN  VTSS_BIT(10)
#define  VTSS_X_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_EN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Completion Timeout Prefix/Header Log Capable.
 * If Set, this bit indicates that the Function records the prefix/header
 * of Request TLPs that experience a Completion Timeout error.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF . CTO_PRFX_HDR_LOG_CAP
 */
#define  VTSS_F_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_CTO_PRFX_HDR_LOG_CAP(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_CTO_PRFX_HDR_LOG_CAP  VTSS_BIT(12)
#define  VTSS_X_PCIE_DBI_ADV_ERR_CAP_CTRL_OFF_CTO_PRFX_HDR_LOG_CAP(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/**
 * \brief The Header Log Register 0 contains the header for the TLP corresponding to a detected error; The header is captured such that, when read using DW accesses, the fields of the header are laid out in the same way the headers are presented in the specification.
Therefore, byte 0 of the header is located in byte 3 of the Header Log Register 0, byte 1 of the header is in byte 2 of the Header Log Register 0, and so forth. For 12-byte headers, only bytes 0 through 11 of the Header Log Register are used and values in bytes 12 through 15 are undefined.
In certain cases where a Malformed TLP is reported, the Header Log Register may contain TLP Prefix information.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:HDR_LOG_0_OFF
 */
#define VTSS_PCIE_DBI_HDR_LOG_0_OFF          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x47)

/**
 * \brief
 * Byte 0 of Header log register of First 32-bit Data Word.
 * This field represents first byte of First DW of Header.
 * This field maps to:
 *
 * HDR_LOG_0_OFF[7:0] = app_hdr_valid? app_hdr_log[31:24] :
 * radm_hdr_log[31:24].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_0_OFF . FIRST_DWORD_FIRST_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_FIRST_BYTE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_FIRST_BYTE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_FIRST_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Byte 1 of Header log register of First 32-bit Data Word.
 * This field represents second byte of First DW of Header.
 * This field maps to:
 *
 * HDR_LOG_0_OFF[15:8] = app_hdr_valid? app_hdr_log[23:16] :
 * radm_hdr_log[23:16].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_0_OFF . FIRST_DWORD_SECOND_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_SECOND_BYTE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_SECOND_BYTE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_SECOND_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Byte 2 of Header log register of First 32-bit Data Word.
 * This field represents third byte of First DW of Header.
 * This field maps to:
 *
 * HDR_LOG_0_OFF[23:16] = app_hdr_valid? app_hdr_log[15:8] :
 * radm_hdr_log[15:8].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_0_OFF . FIRST_DWORD_THIRD_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_THIRD_BYTE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_THIRD_BYTE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_THIRD_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Byte 3 of Header log register of First 32-bit Data Word.
 * This field represents fourth byte of First DW of Header.
 * This field maps to:
 *
 * HDR_LOG_0_OFF[31:24] = app_hdr_valid? app_hdr_log[7:0] :
 * radm_hdr_log[7:0].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_0_OFF . FIRST_DWORD_FOURTH_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_FOURTH_BYTE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_FOURTH_BYTE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_0_OFF_FIRST_DWORD_FOURTH_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief The Header Log Register 1 contains the header for the TLP corresponding to a detected error; The header is captured such that, when read using DW accesses, the fields of the header are laid out in the same way the headers are presented in the specification.
Therefore, byte 0 of the header is located in byte 3 of the Header Log Register 1, byte 1 of the header is in byte 2 of the Header Log Register 1 and so forth. For 12-byte headers, only bytes 0 through 11 of the Header Log Register are used and values in bytes 12 through 15 are undefined.
In certain cases where a Malformed TLP is reported, the Header Log Register may contain TLP Prefix information.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:HDR_LOG_1_OFF
 */
#define VTSS_PCIE_DBI_HDR_LOG_1_OFF          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x48)

/**
 * \brief
 * Byte 0 of Header log register of Second 32-bit Data Word.
 * This field represents first byte of Second DW of Header.
 * This field maps to:
 *
 * HDR_LOG_1_OFF[7:0] = app_hdr_valid? app_hdr_log[63:56] :
 * radm_hdr_log[63:56].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_1_OFF . SECOND_DWORD_FIRST_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_FIRST_BYTE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_FIRST_BYTE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_FIRST_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Byte 1 of Header log register of Second 32-bit Data Word.
 * This field represents second byte of Second DW of Header.
 * This field maps to:
 *
 * HDR_LOG_1_OFF[15:8] = app_hdr_valid? app_hdr_log[55:48] :
 * radm_hdr_log[55:48].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_1_OFF . SECOND_DWORD_SECOND_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_SECOND_BYTE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_SECOND_BYTE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_SECOND_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Byte 2 of Header log register of Second 32-bit Data Word.
 * This field represents third byte of Second DW of Header.
 * This field maps to:
 *
 * HDR_LOG_1_OFF[23:16] = app_hdr_valid? app_hdr_log[47:40] :
 * radm_hdr_log[47:40].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_1_OFF . SECOND_DWORD_THIRD_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_THIRD_BYTE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_THIRD_BYTE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_THIRD_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Byte 3 of Header log register of Second 32-bit Data Word.
 * This field represents fourth byte of Second DW of Header.
 * This field maps to:
 *
 * HDR_LOG_1_OFF[31:24] = app_hdr_valid? app_hdr_log[39:32] :
 * radm_hdr_log[39:32].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_1_OFF . SECOND_DWORD_FOURTH_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_FOURTH_BYTE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_FOURTH_BYTE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_1_OFF_SECOND_DWORD_FOURTH_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief The Header Log Register 2 contains the header for the TLP corresponding to a detected error; The header is captured such that, when read using DW accesses, the fields of the header are laid out in the same way the headers are presented in the specification.
Therefore, byte 0 of the header is located in byte 3 of the Header Log Register 2, byte 1 of the header is in byte 2 of the Header Log Register 2 and so forth. For 12-byte headers, only bytes 0 through 11 of the Header Log Register are used and values in bytes 12 through 15 are undefined.
In certain cases where a Malformed TLP is reported, the Header Log Register may contain TLP Prefix information.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:HDR_LOG_2_OFF
 */
#define VTSS_PCIE_DBI_HDR_LOG_2_OFF          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x49)

/**
 * \brief
 * Byte 0 of Header log register of Third 32-bit Data Word.
 * This field represents first byte of Third DW of Header.
 * This field maps to:
 *
 * HDR_LOG_2_OFF[7:0] = app_hdr_valid? app_hdr_log[95:88] :
 * radm_hdr_log[95:88].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_2_OFF . THIRD_DWORD_FIRST_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_FIRST_BYTE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_FIRST_BYTE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_FIRST_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Byte 1 of Header log register of Third 32-bit Data Word.
 * This field represents second byte of Third DW of Header.
 * This field maps to:
 *
 * HDR_LOG_2_OFF[15:8] = app_hdr_valid? app_hdr_log[87:80] :
 * radm_hdr_log[87:80].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_2_OFF . THIRD_DWORD_SECOND_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_SECOND_BYTE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_SECOND_BYTE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_SECOND_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Byte 2 of Header log register of Third 32-bit Data Word.
 * This field represents third byte of Third DW of Header.
 * This field maps to:
 *
 * HDR_LOG_2_OFF[23:16] = app_hdr_valid? app_hdr_log[79:72] :
 * radm_hdr_log[79:72].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_2_OFF . THIRD_DWORD_THIRD_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_THIRD_BYTE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_THIRD_BYTE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_THIRD_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Byte 3 of Header log register of Third 32-bit Data Word.
 * This field represents fourth byte of Third DW of Header.
 * This field maps to:
 *
 * HDR_LOG_2_OFF[31:24] = app_hdr_valid? app_hdr_log[71:64] :
 * radm_hdr_log[71:64].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_2_OFF . THIRD_DWORD_FOURTH_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_FOURTH_BYTE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_FOURTH_BYTE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_2_OFF_THIRD_DWORD_FOURTH_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief The Header Log Register 3 contains the header for the TLP corresponding to a detected error; The header is captured such that, when read using DW accesses, the fields of the header are laid out in the same way the headers are presented in the specification.
Therefore, byte 0 of the header is located in byte 3 of the Header Log Register 3, byte 1 of the header is in byte 2 of the Header Log Register 3 and so forth. For 12-byte headers, only bytes 0 through 11 of the Header Log Register are used and values in bytes 12 through 15 are undefined.
In certain cases where a Malformed TLP is reported, the Header Log Register may contain TLP Prefix information.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:HDR_LOG_3_OFF
 */
#define VTSS_PCIE_DBI_HDR_LOG_3_OFF          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x4a)

/**
 * \brief
 * Byte 0 of Header log register of Fourth 32-bit Data Word.
 * This field represents first byte of Fourth DW of Header.
 * This field maps to:
 *
 * HDR_LOG_3_OFF[7:0] = app_hdr_valid? app_hdr_log[127:120] :
 * radm_hdr_log[127:120].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_3_OFF . FOURTH_DWORD_FIRST_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_FIRST_BYTE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_FIRST_BYTE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_FIRST_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Byte 1 of Header log register of Fourth 32-bit Data Word.
 * This field represents second byte of Fourth DW of Header.
 * This field maps to:
 *
 * HDR_LOG_3_OFF[15:8] = app_hdr_valid? app_hdr_log[119:112] :
 * radm_hdr_log[119:112].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_3_OFF . FOURTH_DWORD_SECOND_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_SECOND_BYTE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_SECOND_BYTE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_SECOND_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Byte 2 of Header log register of Fourth 32-bit Data Word.
 * This field represents third byte of Fourth DW of Header.
 * This field maps to:
 *
 * HDR_LOG_3_OFF[23:16] = app_hdr_valid? app_hdr_log[111:104] :
 * radm_hdr_log[111:104].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_3_OFF . FOURTH_DWORD_THIRD_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_THIRD_BYTE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_THIRD_BYTE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_THIRD_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Byte 3 of Header log register of Fourth 32-bit Data Word.
 * This field represents fourth byte of Fourth DW of Header.
 * This field maps to:
 *
 * HDR_LOG_3_OFF[31:24] = app_hdr_valid? app_hdr_log[103:96] :
 * radm_hdr_log[103:96].
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_HDR_LOG_3_OFF . FOURTH_DWORD_FOURTH_BYTE
 */
#define  VTSS_F_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_FOURTH_BYTE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_FOURTH_BYTE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_HDR_LOG_3_OFF_FOURTH_DWORD_FOURTH_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief The First TLP Prefix Log Register contains the first End-End TLP Prefix from the TLP corresponding to the detected error.  The TLP Prefix Log Register is only meaningful when the TLP Prefix Log Present bit is Set.
The TLP Prefixes are captured such that, when read using DW accesses, the fields of the TLP Prefix are laid out in the same way the fields of the TLP Prefix are described.
Therefore, byte 0 of a TLP Prefix is located in byte 3 of the associated TLP Prefix Log Register; byte 1 of a TLP Prefix is located in byte 2; and so forth. The TLP Prefix Log Registers beyond the number supported by the Function are hardwired to zero by controller.
If the End-End TLP Prefix Supported bit is Clear, the TLP Prefix Log Register is not required to be implemented.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:TLP_PREFIX_LOG_1_OFF
 */
#define VTSS_PCIE_DBI_TLP_PREFIX_LOG_1_OFF   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x4e)

/**
 * \brief
 * Byte 0 of Error TLP Prefix Log 1.
 * This field contains first byte of First DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_1_OFF . CFG_TLP_PFX_LOG_1_FIRST_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FIRST_BYTE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FIRST_BYTE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FIRST_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Byte 1 of Error TLP Prefix Log 1.
 * This field contains second byte of First DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_1_OFF . CFG_TLP_PFX_LOG_1_SECOND_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_SECOND_BYTE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_SECOND_BYTE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_SECOND_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Byte 2 of Error TLP Prefix Log 1.
 * This field contains third byte of First DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_1_OFF . CFG_TLP_PFX_LOG_1_THIRD_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_THIRD_BYTE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_THIRD_BYTE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_THIRD_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Byte 3 of Error TLP Prefix Log 1.
 * This field contains fourth byte of First DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_1_OFF . CFG_TLP_PFX_LOG_1_FOURTH_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FOURTH_BYTE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FOURTH_BYTE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FOURTH_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief The Second TLP Prefix Log Register contains the second End-End TLP Prefix from the TLP corresponding to the detected error. The TLP Prefix Log Register is only meaningful when the TLP Prefix Log Present bit is Set.
The TLP Prefixes are captured such that, when read using DW accesses, the fields of the TLP Prefix are laid out in the same way the fields of the TLP Prefix are described.
Therefore, byte 0 of a TLP Prefix is located in byte 3 of the associated TLP Prefix Log Register; byte 1 of a TLP Prefix is located in byte 2; and so forth. The TLP Prefix Log Registers beyond the number supported by the Function are hardwired to zero by controller.
If the End-End TLP Prefix Supported bit is Clear, the TLP Prefix Log Register is not required to be implemented.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:TLP_PREFIX_LOG_2_OFF
 */
#define VTSS_PCIE_DBI_TLP_PREFIX_LOG_2_OFF   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x4f)

/**
 * \brief
 * Byte 0 Error TLP Prefix Log 2.
 * This field contains first byte of Second DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_2_OFF . CFG_TLP_PFX_LOG_2_FIRST_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FIRST_BYTE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FIRST_BYTE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FIRST_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Byte 1 Error TLP Prefix Log 2.
 * This field contains second byte of Second DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_2_OFF . CFG_TLP_PFX_LOG_2_SECOND_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_SECOND_BYTE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_SECOND_BYTE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_SECOND_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Byte 2 Error TLP Prefix Log 2.
 * This field contains third byte of Second DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_2_OFF . CFG_TLP_PFX_LOG_2_THIRD_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_THIRD_BYTE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_THIRD_BYTE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_THIRD_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Byte 3 Error TLP Prefix Log 2.
 * This field contains fourth byte of Second DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_2_OFF . CFG_TLP_PFX_LOG_2_FOURTH_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FOURTH_BYTE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FOURTH_BYTE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FOURTH_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief The Third TLP Prefix Log Register contains the third End-End TLP Prefix from the TLP corresponding to the detected error.  The TLP Prefix Log Register is only meaningful when the TLP Prefix Log Present bit is Set.
The TLP Prefixes are captured such that, when read using DW accesses, the fields of the TLP Prefix are laid out in the same way the fields of the TLP Prefix are described.
Therefore, byte 0 of a TLP Prefix is located in byte 3 of the associated TLP Prefix Log Register; byte 1 of a TLP Prefix is located in byte 2; and so forth. The TLP Prefix Log Registers beyond the number supported by the Function are hardwired to zero by controller.
If the End-End TLP Prefix Supported bit is Clear, the TLP Prefix Log Register is not required to be implemented.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:TLP_PREFIX_LOG_3_OFF
 */
#define VTSS_PCIE_DBI_TLP_PREFIX_LOG_3_OFF   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x50)

/**
 * \brief
 * Byte 0 Error TLP Prefix Log 3.
 * This field contains first byte of Third DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_3_OFF . CFG_TLP_PFX_LOG_3_FIRST_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FIRST_BYTE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FIRST_BYTE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FIRST_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Byte 1 Error TLP Prefix Log 3.
 * This field contains second byte of Third DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_3_OFF . CFG_TLP_PFX_LOG_3_SECOND_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_SECOND_BYTE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_SECOND_BYTE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_SECOND_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Byte 2 Error TLP Prefix Log 3.
 * This field contains third byte of Third DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_3_OFF . CFG_TLP_PFX_LOG_3_THIRD_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_THIRD_BYTE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_THIRD_BYTE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_THIRD_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Byte 3 Error TLP Prefix Log 3.
 * This field contains fourth byte of Third DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_3_OFF . CFG_TLP_PFX_LOG_3_FOURTH_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FOURTH_BYTE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FOURTH_BYTE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FOURTH_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief The Fourth TLP Prefix Log Register contains the fourth End-End TLP Prefix from the TLP corresponding to the detected error.  The TLP Prefix Log Register is only meaningful when the TLP Prefix Log Present bit is Set.
The TLP Prefixes are captured such that, when read using DW accesses, the fields of the TLP Prefix are laid out in the same way the fields of the TLP Prefix are described.
Therefore, byte 0 of a TLP Prefix is located in byte 3 of the associated TLP Prefix Log Register; byte 1 of a TLP Prefix is located in byte 2; and so forth. The TLP Prefix Log Registers beyond the number supported by the Function are hardwired to zero by controller.
If the End-End TLP Prefix Supported bit is Clear, the TLP Prefix Log Register is not required to be implemented.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_AER_CAP:TLP_PREFIX_LOG_4_OFF
 */
#define VTSS_PCIE_DBI_TLP_PREFIX_LOG_4_OFF   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x51)

/**
 * \brief
 * Byte 0 Error TLP Prefix Log 4.
 * This field contains first byte of Fourth DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_4_OFF . CFG_TLP_PFX_LOG_4_FIRST_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FIRST_BYTE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FIRST_BYTE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FIRST_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Byte 1 Error TLP Prefix Log 4.
 * This field contains second byte of Fourth DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_4_OFF . CFG_TLP_PFX_LOG_4_SECOND_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_SECOND_BYTE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_SECOND_BYTE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_SECOND_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Byte 2 Error TLP Prefix Log 4.
 * This field contains third byte of Fourth DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_4_OFF . CFG_TLP_PFX_LOG_4_THIRD_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_THIRD_BYTE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_THIRD_BYTE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_THIRD_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Byte 3 Error TLP Prefix Log 4.
 * This field contains fourth byte of Fourth DW of TLP Prefix.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TLP_PREFIX_LOG_4_OFF . CFG_TLP_PFX_LOG_4_FOURTH_BYTE
 */
#define  VTSS_F_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FOURTH_BYTE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FOURTH_BYTE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FOURTH_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * Register Group: \a PCIE_DBI:PF0_MSIX_CAP
 *
 * PF MSI-X Capability Structure
 */


/**
 * \brief This Register holds MSI-X Capability ID, Next Capability pointer. It also controls the MSI-X behaviour.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_MSIX_CAP:PCI_MSIX_CAP_ID_NEXT_CTRL_REG
 */
#define VTSS_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2c)

/**
 * \brief
 * MSI-X Capability ID.
 * This field indicates the MSI-X Capability structure. This field must
 * return a Capability ID of 11h indicating that this is an MSI-X
 * Capability structure.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG . PCI_MSIX_CAP_ID
 */
#define  VTSS_F_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_CAP_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_CAP_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_CAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * MSI-X Next Capability Pointer.
 * This field contains the offset to the next PCI Capability structure or
 * 00h if no other items exist in the linked list of Capabilities.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG . PCI_MSIX_CAP_NEXT_OFFSET
 */
#define  VTSS_F_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_CAP_NEXT_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_CAP_NEXT_OFFSET     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_CAP_NEXT_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * MSI-X Table Size.
 * System software reads this field to determine the MSI-X Table Size N,
 * which is encoded as N-1. For example, a returned value of 000 0000 0011b
 * indicates a table size of 4.
 *
 * SRIOV Note: All VFs in a single PF have the same value for "MSI-X Table
 * Size" (PCI_MSIX_TABLE_SIZE field in
 * SHADOW_PCI_MSIX_CAP_ID_NEXT_CTRL_REG). To write this common value, you
 * must perform a
 * DBI_CS2 write (that is, assert the dbi_cs2 input, or the CS2 address bit
 * for the AXI bridge) while accessing the PCI_MSIX_TABLE_SIZE field in the
 * PF PCI_MSIX_CAP_ID_NEXT_CTRL_REG register.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG . PCI_MSIX_TABLE_SIZE
 */
#define  VTSS_F_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_TABLE_SIZE(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_TABLE_SIZE     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_TABLE_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,16,11)

/**
 * \brief
 * Function Mask.
 * If Set, all of the vectors associated with the Function are masked,
 * regardless of their per-vector Mask bit values.
 * If Clear, each vector's Mask bit determines whether the vector is masked
 * or not.
 * Setting or Clearing the MSI-X Function Mask bit has no effect on the
 * value of the per-vector Mask bits.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG . PCI_MSIX_FUNCTION_MASK
 */
#define  VTSS_F_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_FUNCTION_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_FUNCTION_MASK  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_FUNCTION_MASK(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MSI-X Enable.
 * If Set and the MSI Enable bit in the MSI Message Control Register for
 * MSI is Clear, the Function is permitted to use MSI-X to request service
 * and is prohibited from using INTx interrupts (if implemented).
 * System configuration software Sets this bit to enable MSI-X. A device
 * driver is prohibited from writing this bit to mask a Function's service
 * request.
 * If Clear, the Function is prohibited from using MSI-X to request
 * service.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG . PCI_MSIX_ENABLE
 */
#define  VTSS_F_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_ENABLE  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_PCI_MSIX_CAP_ID_NEXT_CTRL_REG_PCI_MSIX_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief This register provides Table BIR and MSI-x Table offset select.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_MSIX_CAP:MSIX_TABLE_OFFSET_REG
 */
#define VTSS_PCIE_DBI_MSIX_TABLE_OFFSET_REG  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2d)

/**
 * \brief
 * MSI-X Table BAR Indicator Register Field.
 * This field indicates which one of a Function's Base Address Registers ,
 * located beginning at 10h in Configuration Space, or entry in the
 * Enhanced Allocation capability with a matching BEI , is used to map the
 * Function's MSI-X Table into Memory Space.
 * All encodings other than the defined encodings are reserved.
 * For a 64-bit Base Address Register , the Table BIR indicates the lower
 * DWORD. For Functions with Type 1 Configuration Space headers, BIR values
 * 2 through 5 are also Reserved.
 *
 * SRIOV Note: All VFs in a single PF have the same value for "MSI-X Table
 * BAR Indicator Register" (PCI_MSIX_BIR field in
 * SHADOW_MSIX_TABLE_OFFSET_REG). To write this common value, you must
 * perform a
 * DBI_CS2 write (that is, assert the dbi_cs2 input, or the CS2 address bit
 * for the AXI bridge) while accessing the PCI_MSIX_BIR field in the PF
 * MSIX_TABLE_OFFSET_REG register.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_TABLE_OFFSET_REG . PCI_MSIX_BIR
 */
#define  VTSS_F_PCIE_DBI_MSIX_TABLE_OFFSET_REG_PCI_MSIX_BIR(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCIE_DBI_MSIX_TABLE_OFFSET_REG_PCI_MSIX_BIR     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCIE_DBI_MSIX_TABLE_OFFSET_REG_PCI_MSIX_BIR(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * MSI-X Table Offset.
 * Used as an offset from the address contained by one of the Function's
 * Base Address Registers to point to the base of the MSI-X Table.
 * The lower 3 Table BIR bits are masked off (set to zero) by software to
 * form a 32-bit QWORD-aligned offset.
 *
 * SRIOV Note: All VFs in a single PF have the same value for "MSI-X Table
 * Offset" (PCI_MSIX_TABLE_OFFSET field in SHADOW_MSIX_TABLE_OFFSET_REG).
 * To write this common value, you must perform a
 * DBI_CS2 write (that is, assert the dbi_cs2 input, or the CS2 address bit
 * for the AXI bridge) while accessing the PCI_MSIX_TABLE_OFFSET field in
 * the PF MSIX_TABLE_OFFSET_REG register.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_TABLE_OFFSET_REG . PCI_MSIX_TABLE_OFFSET
 */
#define  VTSS_F_PCIE_DBI_MSIX_TABLE_OFFSET_REG_PCI_MSIX_TABLE_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,3,29)
#define  VTSS_M_PCIE_DBI_MSIX_TABLE_OFFSET_REG_PCI_MSIX_TABLE_OFFSET     VTSS_ENCODE_BITMASK(3,29)
#define  VTSS_X_PCIE_DBI_MSIX_TABLE_OFFSET_REG_PCI_MSIX_TABLE_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,3,29)


/**
 * \brief This register provides PBA Offset and PBA BIR value.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_MSIX_CAP:MSIX_PBA_OFFSET_REG
 */
#define VTSS_PCIE_DBI_MSIX_PBA_OFFSET_REG    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2e)

/**
 * \brief
 * MSI-X PBA BIR.
 * This field indicates which one of a Function's Base Address Registers ,
 * located beginning at 10h in Configuration Space, or entry in the
 * Enhanced Allocation capability with a matching BEI, is used to map the
 * Function's MSI-X PBA into Memory Space.
 * The PBA BIR value definitions are identical to those for the Table BIR .
 *
 * SRIOV Note: All VFs in a single PF have the same value for "MSI-X PBA
 * BIR" (PCI_MSIX_PBA_BIR field in SHADOW_MSIX_PBA_OFFSET_REG). To write
 * this common value, you must perform a
 * DBI_CS2 write (that is, assert the dbi_cs2 input, or the CS2 address bit
 * for the AXI bridge) while accessing the PCI_MSIX_PBA_BIR field in the PF
 * MSIX_PBA_OFFSET_REG register.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_PBA_OFFSET_REG . PCI_MSIX_PBA_BIR
 */
#define  VTSS_F_PCIE_DBI_MSIX_PBA_OFFSET_REG_PCI_MSIX_PBA_BIR(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCIE_DBI_MSIX_PBA_OFFSET_REG_PCI_MSIX_PBA_BIR     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCIE_DBI_MSIX_PBA_OFFSET_REG_PCI_MSIX_PBA_BIR(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * MSI-X PBA Offset.
 * Used as an offset from the address contained by one of the Function's
 * Base Address Registers to point to the base of the MSI-X PBA.
 * The lower 3 PBA BIR bits are masked off (set to zero) by software to
 * form a 32-bit QWORD-aligned offset.
 *
 * SRIOV Note: All VFs in a single PF have the same value for "MSI-X PBA
 * Offset" (PCI_MSIX_PBA_OFFSET field in SHADOW_MSIX_PBA_OFFSET_REG). To
 * write this common value, you must perform a
 * DBI_CS2 write (that is, assert the dbi_cs2 input, or the CS2 address bit
 * for the AXI bridge) while accessing the PCI_MSIX_PBA_OFFSET field in the
 * PF MSIX_PBA_OFFSET_REG register.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: if (DBI_RO_WR_EN == 1) then R/W else R
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_PBA_OFFSET_REG . PCI_MSIX_PBA_OFFSET
 */
#define  VTSS_F_PCIE_DBI_MSIX_PBA_OFFSET_REG_PCI_MSIX_PBA_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,3,29)
#define  VTSS_M_PCIE_DBI_MSIX_PBA_OFFSET_REG_PCI_MSIX_PBA_OFFSET     VTSS_ENCODE_BITMASK(3,29)
#define  VTSS_X_PCIE_DBI_MSIX_PBA_OFFSET_REG_PCI_MSIX_PBA_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,3,29)

/**
 * Register Group: \a PCIE_DBI:PF0_ATU_CAP
 *
 * ATU Unroll Structure
 */


/**
 * \brief This register controls the iATU outbound region access based on the optional iATU outbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_OUTBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0000)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TYPE field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0 . IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TC field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0 . IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * This is a reserved field. Do not use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0 . IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * ATTR field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0 . IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0 . IATU_REGION_CTRL_1_OFF_OUTBOUND_0_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * When the address of an outbound TLP is matched to this region and the
 * FUNC_BYPASS field in the "iATU Region Control 2 Register" is '0', then
 * the function number used in generating the function part of the
 * requester ID (RID) field of the TLP is taken from this 5-bit register.
 * The value in this register must be 0x0 unless multifunction operation in
 * the controller is enabled (CX_NFUNC > 1).
 *
 * When you are using the AXI Bridge, then this field is swapped before AXI
 * decomposition occurs so that the correct "Max_Read_Request_Size" and
 * "Max_Payload_Size" values are used.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0 . IATU_REGION_CTRL_1_OFF_OUTBOUND_0_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the outbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_OUTBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0001)

/**
 * \brief
 * MSG TLPs (Message Code). When the address of an outbound TLP is matched
 * to this region, and the translated TLP TYPE field is Msg or MsgD; then
 * the message field of the TLP is changed to the value in this register.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an outbound TLP is
 * matched to this region, and the translated TLP TYPE field targets memory
 * space; then the ST field of the TLP is changed to the value in this
 * register. Only Valid when the CX_TPH_ENABLE configuration parameter is
 * 1.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * TAG.
 *
 * The substituted TAG field (byte 6) in the outgoing TLP header when
 * TAG_SUBSTITUTE_EN is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TAG Substitute Enable.
 * When enabled and region address is matched, the iATU substitutes the TAG
 * field of the outbound TLP header with the contents of the TAG field in
 * this register. The expected usage scenario is translation from AXI MWr
 * to Vendor Defined Msg/MsgD.
 *
 * Note (CX_TPH_ENABLE=1): TAG substitution for MWr will not occur because
 * this field (byte 6) in the TLP header is the ST field. ST substitution
 * can still take place using the MSG_CODE field in
 * IATU_REGION_CTRL_2_OFF_OUTBOUND_i.
 *
 * Note (CX_10BIT_TAG =1): For 10-bit tags, TAG substitution only applies
 * to the 8 least significant bits of the TAG field (bits 7:0 of Byte 4 of
 * the TLP Header). T9 and T8 of the Header are not substituted.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG_SUBSTITUTE_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Translation Bypass.
 * In this mode, the function number of the translated TLP is taken from
 * your application transmit interface and not from the CTRL_1_FUNC_NUM
 * field of the "iATU Region Control 1 Register" or the VF_NUMBER field of
 * the "iATU Control 3 Register."
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_FUNC_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_FUNC_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_FUNC_BYPASS  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_FUNC_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Serialize Non-Posted Requests.
 * In this mode, when the AXI Bridge is populated, same AXI ID Non-Posted
 * Read/Write Requests are transmitted on the wire if there are no other
 * same ID Non-Posted Requests outstanding.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_SNP
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_SNP(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_SNP  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_SNP(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * TLP Header Fields Translation Bypass.  In this mode header fields of the
 * translated TLP is taken from your application transmit interface or, if
 * AMBA is configured,	from the AMBA sideband bus (slv_awmisc_info) and
 * not from the corresponding fields of the
 * IATU_REGION_CTRL_1_OFF_OUTBOUND_i  or IATU_REGION_CTRL_2_OFF_OUTBOUND_i
 * registers. The header fields are
 *  - TC
 *  - PH
 *  - TH
 *  - ST
 *  - AT
 *  - Attr (IDO, RO and NS).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TLP_HEADER_FIELDS_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TLP_HEADER_FIELDS_BYPASS  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Inhibit TLP Payload Data for TLP's in Matched Region; assign iATU region
 * to be TLP without data.
 * When enabled and region address is matched, the iATU marks all TLPs as
 * having no payload data by forcing the TLP header Fmt[1] bit =0,
 * regardless of the application inputs such as slv_wstrb.
 * Encoding are define as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INHIBIT_PAYLOAD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INHIBIT_PAYLOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INHIBIT_PAYLOAD  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INHIBIT_PAYLOAD(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Header Substitute Enable.
 *
 * When enabled and region address is matched, the iATU fully substitutes
 * bytes 8-11 (for 3 DWORD header) or bytes 12-15 (for 4 DWORD header) of
 * the outbound TLP header with the contents of the LWR_TARGET_RW field in
 * IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_i.
 * Encodings are as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_HEADER_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_HEADER_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_HEADER_SUBSTITUTE_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_HEADER_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * CFG Shift Mode.
 *
 * The iATU uses bits [27:12] of the untranslated address (on the XALI0/1/2
 * interface or AXI slave interface address) to form the BDF number of the
 * outgoing CFG TLP.
 *
 * This supports the Enhanced Configuration Address Mapping (ECAM)
 * mechanism (Section 7.2.2 of the PCI Express Base 3.1 Specification,
 * revision 1.0) by allowing all outgoing I/O and MEM TLPs (that have been
 * translated to CFG) to be mapped from memory space into any 256 MB region
 * of the PCIe configuration space.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Region Enable. This bit must be set to '1' for address translation to
 * take place.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0 . IATU_REGION_CTRL_2_OFF_OUTBOUND_0_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0002)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32-bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0003)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated. In systems with a 32-bit address space, this register
 * is not used and therefore writing to this register has no effect.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0 . IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_OUTBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0004)

/**
 * \brief
 * Circular Buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0 . IATU_LIMIT_ADDR_OFF_OUTBOUND_0_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0 . IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0 . IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region, or the outbound TLP header information, depending on the setting  of HEADER_SUBSTITUTE_EN field of IATU_REGION_CTRL_2_VIEWPORT_OFF_OUTBOUND_i register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0005)

/**
 * \brief
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_ is '0'
 * (normal operation):
 *  - LWR_TARGET_RW[31:n] forms MSB's of the Lower Target part of the new
 * address of the translated region;
 *  - LWR_TARGET_RW[n-1:0] are not used. (The start address must be aligned
 * to a CX_ATU_MIN_REGION_SIZE kB boundary, so the lower bits of the start
 * address of the new address of the translated region (bits n-1:0) are
 * always '0').
 *  - n is log2(CX_ATU_MIN_REGION_SIZE).
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_i is '1':
 *  - LWR_TARGET_RW[31:0] forms bytes 8-11 (for 3 dword header) or bytes
 * 12-15 (for 4 dword header) of the outbound TLP header. Usage scenarios
 * include the transmission of Vendor Defined Messages where the controller
 * determines the content of bytes 12 to 15 of the TLP header.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0 . IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_LWR_TARGET_RW_OUTBOUND
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_LWR_TARGET_RW_OUTBOUND(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_LWR_TARGET_RW_OUTBOUND     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_LWR_TARGET_RW_OUTBOUND(x)  (x)


/**
 * \brief This register holds the upper 32 bits of the start address (Upper Target part) of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0006)

/**
 * \brief
 * Forms bits [63:32] of the start address (Upper Target part) of the new
 * address of the translated region.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0 . IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_UPPER_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_UPPER_TARGET_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_UPPER_TARGET_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_UPPER_TARGET_RW(x)  (x)


/**
 * \brief This register controls the iATU inbound region access based on the optional iATU inbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_INBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0040)

/**
 * \brief
 * When the TYPE field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0 . IATU_REGION_CTRL_1_OFF_INBOUND_0_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the TC field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TC Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0 . IATU_REGION_CTRL_1_OFF_INBOUND_0_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * When the TD field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TD Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0 . IATU_REGION_CTRL_1_OFF_INBOUND_0_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the ATTR field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "ATTR Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0 . IATU_REGION_CTRL_1_OFF_INBOUND_0_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0 . IATU_REGION_CTRL_1_OFF_INBOUND_0_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * MEM-I/O: When the Address and BAR matching logic in the controller
 * indicate that a MEM-I/O transaction matches a BAR in the function
 * corresponding to this value, then address translation proceeds. This
 * check is only performed if the "Function Number Match Enable" bit of the
 * "iATU Region Control 2 Register" is set.
 *
 * CFG0/CFG1: When the destination function number as specified in the
 * routing ID of the TLP header matches the function, then address
 * translation proceeds. This check is only performed if the "Function
 * Number Match Enable" bit of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0 . IATU_REGION_CTRL_1_OFF_INBOUND_0_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_0_IATU_REGION_CTRL_1_OFF_INBOUND_0_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the inbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_INBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0041)

/**
 * \brief
 * MSG TLPs: (Message Code). When the MSG_CODE field of an inbound Msg/MsgD
 * TLP is matched to this value, then address translation proceeds (when
 * all other enabled field-matches are successful). This check is only
 * performed if the "Message Code Match Enable" bit of the "iATU Region
 * Control 2 Register" is set and the TYPE field of the inbound TLP is
 * Msg/MsgD.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an inbound TLP is
 * matched to this value, then address translation proceeds. This check is
 * only performed if the "ST Match Enable" bit of the "iATU Region Control
 * 2 Register" is set. The setting is independent of the setting of the TH
 * field. Only Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * BAR Number. When the BAR number of an inbound MEM or IO TLP " that is
 * matched by the normal internal BAR address matching mechanism " is the
 * same as this field, address translation proceeds (when all other enabled
 * field-matches are successful). This check is only performed if the
 * "Match Mode" bit of the "iATU Region Control 2 Register" is set.
 * IO translation would require either 00100b or 00101b in the inbound TLP
 * TYPE; the BAR Number set in the range 000b - 101b and that BAR
 * configured as an IO BAR.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_BAR_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_BAR_NUM(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_BAR_NUM     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_BAR_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Message Type Match Mode.
 * When enabled, and if single address location translate enable is set,
 * then inbound TLPs of type MSG/MSGd which match the type field of the
 * IATU_REGION_CTRL_1_VIEWPORT_OFF_INBOUND_i register (TYPE[4:3]=2'b10)
 * will be translated.
 * Message type match mode overrides any value of MATCH_MODE field in this
 * register. Usage scenarios for this are translation of VDM or ATS
 * messages when AXI bridge is configured on client interface.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_TYPE_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_TYPE_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_TYPE_MATCH_MODE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_TYPE_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * TC Match Enable.
 * Ensures that a successful TC TLP field comparison match (see TC field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_TC_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_TC_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_TC_MATCH_EN  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_TC_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * TD Match Enable.
 * Ensures that a successful TD TLP field comparison match (see TD field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_TD_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_TD_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_TD_MATCH_EN  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_TD_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * ATTR Match Enable.
 * Ensures that a successful ATTR TLP field comparison match (see ATTR
 * field of the "iATU Region Control 1 Register") occurs for address
 * translation to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_ATTR_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_ATTR_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_ATTR_MATCH_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_ATTR_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Match Enable.
 * Ensures that a successful Function Number TLP field comparison match
 * (see Function Number field of the "iATU Region Control 1 Register")
 * occurs (in MEM-I/O and CFG0/CFG1 transactions) for address translation
 * to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_FUNC_NUM_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_FUNC_NUM_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_FUNC_NUM_MATCH_EN  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_FUNC_NUM_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Message Code Match Enable (Msg TLPS). Ensures that a successful message
 * Code TLP field comparison match (see Message Code field of the "iATU
 * Region Control 2 Register") occurs (in MSG transactions) for address
 * translation to proceed.
 *
 * ST Match Enable (Mem TLPs). Ensures that a successful ST TLP field
 * comparison match (see ST field of the "iATU Region Control 2 Register")
 * occurs (in MEM transactions) for address translation to proceed. Only
 * Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_CODE_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_CODE_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_CODE_MATCH_EN  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MSG_CODE_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Single Address Location Translate Enable.
 *
 * When enabled, Rx TLPs can be translated to a single address location as
 * determined by the target address register of the iATU region.
 * The main usage scenario is translation of Messages (such as Vendor
 * Defined or ATS Messages) to MWr TLPs when the AXI bridge is enabled.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_SINGLE_ADDR_LOC_TRANS_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_SINGLE_ADDR_LOC_TRANS_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Response Code.
 * Defines the type of response to give for accesses matching this region.
 * This overrides the normal RADM filter response. Note that this feature
 * is not available for any region where Single Address Location Translate
 * is enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h2:
 * 'h0:
 * 'h3:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_RESPONSE_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_RESPONSE_CODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_RESPONSE_CODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_RESPONSE_CODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Fuzzy Type Match Enable.
 * When enabled, the iATU relaxes the matching of the TLP TYPE field
 * against the expected TYPE field so that
 *  - CfgRd0 and CfgRd1 TLPs are seen as identical. Similarly with CfgWr0
 * and CfgWr1.
 *  - MWr, MRd, and MRdLk TLPs are seen as identical
 *  - The Routing field of Msg/MsgD TLPs is ignored
 *  - FetchAdd, Swap, and CAS are seen as identical.
 * For example, CFG0 in the TYPE field in the "iATU Region Control 1
 * Register" matches against an inbound CfgRd0, CfgRd1, CfgWr0, or CfgWr1
 * TLP.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_FUZZY_TYPE_MATCH_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_FUZZY_TYPE_MATCH_CODE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_FUZZY_TYPE_MATCH_CODE  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_FUZZY_TYPE_MATCH_CODE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * CFG Shift Enable.
 * This is useful for CFG transactions where the PCIe configuration
 * mechanism maps bits [27:12] of the address to the bus/device and
 * function number. This allows a CFG configuration space to be located in
 * any 256MB window of your application memory space using a 28-bit
 * effective address. Shifts bits [31:16] of the untranslated address to
 * form bits [27:12] of the translated address.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode Enable.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address). When set all regions of
 * that type must use address match mode.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Match Mode.
 * Determines Inbound matching mode for TLPs. The mode depends on the type
 * of TLP that is received as follows:
 *
 *  For MEM I/O TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU operates using addresses as in the
 * outbound direction. The Region Base and Limit Registers must be setup.
 *  - 1: BAR Match Mode. BAR matching is used. The "BAR Number" field is
 * relevant. Not used for RC.
 * For CFG0 TLPs, this field is interpreted as follows:
 *  - 0: Routing ID Match Mode. The iATU interprets the Routing ID (Bytes 8
 * to 11 of TLP header) as an address. This corresponds to the upper 16
 * bits of the address in MEM-I/O transactions. The Routing ID of the TLP
 * must be within the base and limit of the iATU region for matching to
 * proceed.
 *  - 1: Accept Mode. The iATU accepts all CFG0 transactions as address
 * matches. The routing ID in the CFG0 TLP is ignored. This is useful as
 * all received CFG0 TLPs should be processed regardless of the Bus number.
 * For MSG/MSGD TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU treats the third dword and fourth
 * dword of the inbound MSG/MSGD TLP as an address and it is matched
 * against the Region Base and Limit Registers.
 *  - 1: Vendor ID Match Mode. This mode is relevant for ID-routed Vendor
 * Defined Messages. The iATU ignores the Routing ID (Bus, Device,
 * Function) in bits [31:16] of the third dword of the TLP header, but
 * matches against the Vendor ID in bits [15:0] of the third dword of the
 * TLP header. Bits [15:0] of the Region Upper Base register should be
 * programmed with the required Vendor ID. The lower Base and Limit
 * Register should be programmed to translate TLPs based on vendor specific
 * information in the fourth dword of the TLP header.
 *  - If SINGLE_ADDRESS_LOCATION_TRANSLATE_EN = 1 AND MSG_TYPE_MATCH_MODE
 * =1, then Match Mode is ignored.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MATCH_MODE  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Region Enable.
 * This bit must be set to '1' for address translation to take place.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0 . IATU_REGION_CTRL_2_OFF_INBOUND_0_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_0_IATU_REGION_CTRL_2_OFF_INBOUND_0_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_INBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0042)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0 . IATU_LWR_BASE_ADDR_OFF_INBOUND_0_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0 . IATU_LWR_BASE_ADDR_OFF_INBOUND_0_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32 bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_INBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0043)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0 . IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_INBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0044)

/**
 * \brief
 * Circular Buffer Increment.
 * When CX_ATU_SLOC_CBUF = 0, then this field is Read-only and forms the
 * lowest bits of the end address of the address region to be translated.
 * When CX_ATU_SLOC_CBUF = 1, then this field is R/W and forms the upper
 * bits of the Circular Buffer Increment size (CBUF_INCR) field for Single
 * Location Address translation. The increment value (in bytes) is decoded
 * as follows:
 * Note: A write to any bit in the CBUF_INCR field resets the circular
 * buffer
 * pointer - that is, the next matched received Message will be translated
 * to the start address of the Circular Buffer. This field must be written
 * to AFTER the target and limit registers have been updated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h9:
 * 'h6:
 * 'h3:
 * 'ha:
 * 'h7:
 * 'h4:
 * 'h1:
 * 'hb:
 * 'h8:
 * 'h5:
 * 'h2:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0 . IATU_LIMIT_ADDR_OFF_INBOUND_0_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones. When
 * SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1, and CBUF_INCR > 0
 * then this field forms lower bits of the limit address for the circular
 * buffer.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0 . IATU_LIMIT_ADDR_OFF_INBOUND_0_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated. When SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1,
 * and CBUF_INCR > 0 then this field forms the upper bits of the limit
 * address for the circular buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0 . IATU_LIMIT_ADDR_OFF_INBOUND_0_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_0_IATU_LIMIT_ADDR_OFF_INBOUND_0_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_INBOUND_0
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0045)

/**
 * \brief
 * Forms the LSB's of the Lower Target part of the new address of the
 * translated region. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary (in address match mode); and to the
 * Bar size boundary (in BAR match mode) so that these bits are always '0'.
 * If the BAR is smaller than the iATU region size, then the iATU target
 * address must align to the iATU region size; otherwise it must align to
 * the BAR size.
 *
 * A write to this location is ignored by the PCIe controller.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_LWR_TARGET_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_LWR_TARGET_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_LWR_TARGET_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_LWR_TARGET_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms MSB's of the Lower Target part of the new address of the
 * translated region. These bits are always '0'.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_LWR_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_LWR_TARGET_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_LWR_TARGET_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_LWR_TARGET_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register controls the iATU outbound region access based on the optional iATU outbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_OUTBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0080)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TYPE field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1 . IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TC field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1 . IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * This is a reserved field. Do not use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1 . IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * ATTR field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1 . IATU_REGION_CTRL_1_OFF_OUTBOUND_1_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1 . IATU_REGION_CTRL_1_OFF_OUTBOUND_1_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * When the address of an outbound TLP is matched to this region and the
 * FUNC_BYPASS field in the "iATU Region Control 2 Register" is '0', then
 * the function number used in generating the function part of the
 * requester ID (RID) field of the TLP is taken from this 5-bit register.
 * The value in this register must be 0x0 unless multifunction operation in
 * the controller is enabled (CX_NFUNC > 1).
 *
 * When you are using the AXI Bridge, then this field is swapped before AXI
 * decomposition occurs so that the correct "Max_Read_Request_Size" and
 * "Max_Payload_Size" values are used.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1 . IATU_REGION_CTRL_1_OFF_OUTBOUND_1_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the outbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_OUTBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0081)

/**
 * \brief
 * MSG TLPs (Message Code). When the address of an outbound TLP is matched
 * to this region, and the translated TLP TYPE field is Msg or MsgD; then
 * the message field of the TLP is changed to the value in this register.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an outbound TLP is
 * matched to this region, and the translated TLP TYPE field targets memory
 * space; then the ST field of the TLP is changed to the value in this
 * register. Only Valid when the CX_TPH_ENABLE configuration parameter is
 * 1.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * TAG.
 *
 * The substituted TAG field (byte 6) in the outgoing TLP header when
 * TAG_SUBSTITUTE_EN is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TAG
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TAG(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TAG     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TAG(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TAG Substitute Enable.
 * When enabled and region address is matched, the iATU substitutes the TAG
 * field of the outbound TLP header with the contents of the TAG field in
 * this register. The expected usage scenario is translation from AXI MWr
 * to Vendor Defined Msg/MsgD.
 *
 * Note (CX_TPH_ENABLE=1): TAG substitution for MWr will not occur because
 * this field (byte 6) in the TLP header is the ST field. ST substitution
 * can still take place using the MSG_CODE field in
 * IATU_REGION_CTRL_2_OFF_OUTBOUND_i.
 *
 * Note (CX_10BIT_TAG =1): For 10-bit tags, TAG substitution only applies
 * to the 8 least significant bits of the TAG field (bits 7:0 of Byte 4 of
 * the TLP Header). T9 and T8 of the Header are not substituted.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TAG_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TAG_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TAG_SUBSTITUTE_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TAG_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Translation Bypass.
 * In this mode, the function number of the translated TLP is taken from
 * your application transmit interface and not from the CTRL_1_FUNC_NUM
 * field of the "iATU Region Control 1 Register" or the VF_NUMBER field of
 * the "iATU Control 3 Register."
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_FUNC_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_FUNC_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_FUNC_BYPASS  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_FUNC_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Serialize Non-Posted Requests.
 * In this mode, when the AXI Bridge is populated, same AXI ID Non-Posted
 * Read/Write Requests are transmitted on the wire if there are no other
 * same ID Non-Posted Requests outstanding.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_SNP
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_SNP(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_SNP  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_SNP(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * TLP Header Fields Translation Bypass.  In this mode header fields of the
 * translated TLP is taken from your application transmit interface or, if
 * AMBA is configured,	from the AMBA sideband bus (slv_awmisc_info) and
 * not from the corresponding fields of the
 * IATU_REGION_CTRL_1_OFF_OUTBOUND_i  or IATU_REGION_CTRL_2_OFF_OUTBOUND_i
 * registers. The header fields are
 *  - TC
 *  - PH
 *  - TH
 *  - ST
 *  - AT
 *  - Attr (IDO, RO and NS).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TLP_HEADER_FIELDS_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TLP_HEADER_FIELDS_BYPASS  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Inhibit TLP Payload Data for TLP's in Matched Region; assign iATU region
 * to be TLP without data.
 * When enabled and region address is matched, the iATU marks all TLPs as
 * having no payload data by forcing the TLP header Fmt[1] bit =0,
 * regardless of the application inputs such as slv_wstrb.
 * Encoding are define as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_INHIBIT_PAYLOAD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_INHIBIT_PAYLOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_INHIBIT_PAYLOAD  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_INHIBIT_PAYLOAD(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Header Substitute Enable.
 *
 * When enabled and region address is matched, the iATU fully substitutes
 * bytes 8-11 (for 3 DWORD header) or bytes 12-15 (for 4 DWORD header) of
 * the outbound TLP header with the contents of the LWR_TARGET_RW field in
 * IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_i.
 * Encodings are as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_HEADER_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_HEADER_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_HEADER_SUBSTITUTE_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_HEADER_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * CFG Shift Mode.
 *
 * The iATU uses bits [27:12] of the untranslated address (on the XALI0/1/2
 * interface or AXI slave interface address) to form the BDF number of the
 * outgoing CFG TLP.
 *
 * This supports the Enhanced Configuration Address Mapping (ECAM)
 * mechanism (Section 7.2.2 of the PCI Express Base 3.1 Specification,
 * revision 1.0) by allowing all outgoing I/O and MEM TLPs (that have been
 * translated to CFG) to be mapped from memory space into any 256 MB region
 * of the PCIe configuration space.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Region Enable. This bit must be set to '1' for address translation to
 * take place.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1 . IATU_REGION_CTRL_2_OFF_OUTBOUND_1_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0082)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32-bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0083)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated. In systems with a 32-bit address space, this register
 * is not used and therefore writing to this register has no effect.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1 . IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_OUTBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0084)

/**
 * \brief
 * Circular Buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1 . IATU_LIMIT_ADDR_OFF_OUTBOUND_1_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1 . IATU_LIMIT_ADDR_OFF_OUTBOUND_1_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1 . IATU_LIMIT_ADDR_OFF_OUTBOUND_1_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region, or the outbound TLP header information, depending on the setting  of HEADER_SUBSTITUTE_EN field of IATU_REGION_CTRL_2_VIEWPORT_OFF_OUTBOUND_i register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0085)

/**
 * \brief
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_ is '0'
 * (normal operation):
 *  - LWR_TARGET_RW[31:n] forms MSB's of the Lower Target part of the new
 * address of the translated region;
 *  - LWR_TARGET_RW[n-1:0] are not used. (The start address must be aligned
 * to a CX_ATU_MIN_REGION_SIZE kB boundary, so the lower bits of the start
 * address of the new address of the translated region (bits n-1:0) are
 * always '0').
 *  - n is log2(CX_ATU_MIN_REGION_SIZE).
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_i is '1':
 *  - LWR_TARGET_RW[31:0] forms bytes 8-11 (for 3 dword header) or bytes
 * 12-15 (for 4 dword header) of the outbound TLP header. Usage scenarios
 * include the transmission of Vendor Defined Messages where the controller
 * determines the content of bytes 12 to 15 of the TLP header.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1 . IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_LWR_TARGET_RW_OUTBOUND
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_LWR_TARGET_RW_OUTBOUND(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_LWR_TARGET_RW_OUTBOUND     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_LWR_TARGET_RW_OUTBOUND(x)  (x)


/**
 * \brief This register holds the upper 32 bits of the start address (Upper Target part) of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0086)

/**
 * \brief
 * Forms bits [63:32] of the start address (Upper Target part) of the new
 * address of the translated region.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1 . IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_UPPER_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_UPPER_TARGET_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_UPPER_TARGET_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_UPPER_TARGET_RW(x)  (x)


/**
 * \brief This register controls the iATU inbound region access based on the optional iATU inbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_INBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc00c0)

/**
 * \brief
 * When the TYPE field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1 . IATU_REGION_CTRL_1_OFF_INBOUND_1_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the TC field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TC Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1 . IATU_REGION_CTRL_1_OFF_INBOUND_1_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * When the TD field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TD Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1 . IATU_REGION_CTRL_1_OFF_INBOUND_1_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the ATTR field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "ATTR Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1 . IATU_REGION_CTRL_1_OFF_INBOUND_1_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1 . IATU_REGION_CTRL_1_OFF_INBOUND_1_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * MEM-I/O: When the Address and BAR matching logic in the controller
 * indicate that a MEM-I/O transaction matches a BAR in the function
 * corresponding to this value, then address translation proceeds. This
 * check is only performed if the "Function Number Match Enable" bit of the
 * "iATU Region Control 2 Register" is set.
 *
 * CFG0/CFG1: When the destination function number as specified in the
 * routing ID of the TLP header matches the function, then address
 * translation proceeds. This check is only performed if the "Function
 * Number Match Enable" bit of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1 . IATU_REGION_CTRL_1_OFF_INBOUND_1_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_1_IATU_REGION_CTRL_1_OFF_INBOUND_1_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the inbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_INBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc00c1)

/**
 * \brief
 * MSG TLPs: (Message Code). When the MSG_CODE field of an inbound Msg/MsgD
 * TLP is matched to this value, then address translation proceeds (when
 * all other enabled field-matches are successful). This check is only
 * performed if the "Message Code Match Enable" bit of the "iATU Region
 * Control 2 Register" is set and the TYPE field of the inbound TLP is
 * Msg/MsgD.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an inbound TLP is
 * matched to this value, then address translation proceeds. This check is
 * only performed if the "ST Match Enable" bit of the "iATU Region Control
 * 2 Register" is set. The setting is independent of the setting of the TH
 * field. Only Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * BAR Number. When the BAR number of an inbound MEM or IO TLP " that is
 * matched by the normal internal BAR address matching mechanism " is the
 * same as this field, address translation proceeds (when all other enabled
 * field-matches are successful). This check is only performed if the
 * "Match Mode" bit of the "iATU Region Control 2 Register" is set.
 * IO translation would require either 00100b or 00101b in the inbound TLP
 * TYPE; the BAR Number set in the range 000b - 101b and that BAR
 * configured as an IO BAR.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_BAR_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_BAR_NUM(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_BAR_NUM     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_BAR_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Message Type Match Mode.
 * When enabled, and if single address location translate enable is set,
 * then inbound TLPs of type MSG/MSGd which match the type field of the
 * IATU_REGION_CTRL_1_VIEWPORT_OFF_INBOUND_i register (TYPE[4:3]=2'b10)
 * will be translated.
 * Message type match mode overrides any value of MATCH_MODE field in this
 * register. Usage scenarios for this are translation of VDM or ATS
 * messages when AXI bridge is configured on client interface.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_TYPE_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_TYPE_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_TYPE_MATCH_MODE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_TYPE_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * TC Match Enable.
 * Ensures that a successful TC TLP field comparison match (see TC field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_TC_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_TC_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_TC_MATCH_EN  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_TC_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * TD Match Enable.
 * Ensures that a successful TD TLP field comparison match (see TD field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_TD_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_TD_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_TD_MATCH_EN  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_TD_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * ATTR Match Enable.
 * Ensures that a successful ATTR TLP field comparison match (see ATTR
 * field of the "iATU Region Control 1 Register") occurs for address
 * translation to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_ATTR_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_ATTR_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_ATTR_MATCH_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_ATTR_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Match Enable.
 * Ensures that a successful Function Number TLP field comparison match
 * (see Function Number field of the "iATU Region Control 1 Register")
 * occurs (in MEM-I/O and CFG0/CFG1 transactions) for address translation
 * to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_FUNC_NUM_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_FUNC_NUM_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_FUNC_NUM_MATCH_EN  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_FUNC_NUM_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Message Code Match Enable (Msg TLPS). Ensures that a successful message
 * Code TLP field comparison match (see Message Code field of the "iATU
 * Region Control 2 Register") occurs (in MSG transactions) for address
 * translation to proceed.
 *
 * ST Match Enable (Mem TLPs). Ensures that a successful ST TLP field
 * comparison match (see ST field of the "iATU Region Control 2 Register")
 * occurs (in MEM transactions) for address translation to proceed. Only
 * Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_CODE_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_CODE_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_CODE_MATCH_EN  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MSG_CODE_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Single Address Location Translate Enable.
 *
 * When enabled, Rx TLPs can be translated to a single address location as
 * determined by the target address register of the iATU region.
 * The main usage scenario is translation of Messages (such as Vendor
 * Defined or ATS Messages) to MWr TLPs when the AXI bridge is enabled.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_SINGLE_ADDR_LOC_TRANS_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_SINGLE_ADDR_LOC_TRANS_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Response Code.
 * Defines the type of response to give for accesses matching this region.
 * This overrides the normal RADM filter response. Note that this feature
 * is not available for any region where Single Address Location Translate
 * is enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h2:
 * 'h0:
 * 'h3:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_RESPONSE_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_RESPONSE_CODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_RESPONSE_CODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_RESPONSE_CODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Fuzzy Type Match Enable.
 * When enabled, the iATU relaxes the matching of the TLP TYPE field
 * against the expected TYPE field so that
 *  - CfgRd0 and CfgRd1 TLPs are seen as identical. Similarly with CfgWr0
 * and CfgWr1.
 *  - MWr, MRd, and MRdLk TLPs are seen as identical
 *  - The Routing field of Msg/MsgD TLPs is ignored
 *  - FetchAdd, Swap, and CAS are seen as identical.
 * For example, CFG0 in the TYPE field in the "iATU Region Control 1
 * Register" matches against an inbound CfgRd0, CfgRd1, CfgWr0, or CfgWr1
 * TLP.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_FUZZY_TYPE_MATCH_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_FUZZY_TYPE_MATCH_CODE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_FUZZY_TYPE_MATCH_CODE  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_FUZZY_TYPE_MATCH_CODE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * CFG Shift Enable.
 * This is useful for CFG transactions where the PCIe configuration
 * mechanism maps bits [27:12] of the address to the bus/device and
 * function number. This allows a CFG configuration space to be located in
 * any 256MB window of your application memory space using a 28-bit
 * effective address. Shifts bits [31:16] of the untranslated address to
 * form bits [27:12] of the translated address.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode Enable.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address). When set all regions of
 * that type must use address match mode.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Match Mode.
 * Determines Inbound matching mode for TLPs. The mode depends on the type
 * of TLP that is received as follows:
 *
 *  For MEM I/O TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU operates using addresses as in the
 * outbound direction. The Region Base and Limit Registers must be setup.
 *  - 1: BAR Match Mode. BAR matching is used. The "BAR Number" field is
 * relevant. Not used for RC.
 * For CFG0 TLPs, this field is interpreted as follows:
 *  - 0: Routing ID Match Mode. The iATU interprets the Routing ID (Bytes 8
 * to 11 of TLP header) as an address. This corresponds to the upper 16
 * bits of the address in MEM-I/O transactions. The Routing ID of the TLP
 * must be within the base and limit of the iATU region for matching to
 * proceed.
 *  - 1: Accept Mode. The iATU accepts all CFG0 transactions as address
 * matches. The routing ID in the CFG0 TLP is ignored. This is useful as
 * all received CFG0 TLPs should be processed regardless of the Bus number.
 * For MSG/MSGD TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU treats the third dword and fourth
 * dword of the inbound MSG/MSGD TLP as an address and it is matched
 * against the Region Base and Limit Registers.
 *  - 1: Vendor ID Match Mode. This mode is relevant for ID-routed Vendor
 * Defined Messages. The iATU ignores the Routing ID (Bus, Device,
 * Function) in bits [31:16] of the third dword of the TLP header, but
 * matches against the Vendor ID in bits [15:0] of the third dword of the
 * TLP header. Bits [15:0] of the Region Upper Base register should be
 * programmed with the required Vendor ID. The lower Base and Limit
 * Register should be programmed to translate TLPs based on vendor specific
 * information in the fourth dword of the TLP header.
 *  - If SINGLE_ADDRESS_LOCATION_TRANSLATE_EN = 1 AND MSG_TYPE_MATCH_MODE
 * =1, then Match Mode is ignored.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MATCH_MODE  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Region Enable.
 * This bit must be set to '1' for address translation to take place.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1 . IATU_REGION_CTRL_2_OFF_INBOUND_1_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_1_IATU_REGION_CTRL_2_OFF_INBOUND_1_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_INBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc00c2)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1 . IATU_LWR_BASE_ADDR_OFF_INBOUND_1_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1 . IATU_LWR_BASE_ADDR_OFF_INBOUND_1_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32 bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_INBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc00c3)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1 . IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_INBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc00c4)

/**
 * \brief
 * Circular Buffer Increment.
 * When CX_ATU_SLOC_CBUF = 0, then this field is Read-only and forms the
 * lowest bits of the end address of the address region to be translated.
 * When CX_ATU_SLOC_CBUF = 1, then this field is R/W and forms the upper
 * bits of the Circular Buffer Increment size (CBUF_INCR) field for Single
 * Location Address translation. The increment value (in bytes) is decoded
 * as follows:
 * Note: A write to any bit in the CBUF_INCR field resets the circular
 * buffer
 * pointer - that is, the next matched received Message will be translated
 * to the start address of the Circular Buffer. This field must be written
 * to AFTER the target and limit registers have been updated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h9:
 * 'h6:
 * 'h3:
 * 'ha:
 * 'h7:
 * 'h4:
 * 'h1:
 * 'hb:
 * 'h8:
 * 'h5:
 * 'h2:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1 . IATU_LIMIT_ADDR_OFF_INBOUND_1_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones. When
 * SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1, and CBUF_INCR > 0
 * then this field forms lower bits of the limit address for the circular
 * buffer.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1 . IATU_LIMIT_ADDR_OFF_INBOUND_1_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated. When SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1,
 * and CBUF_INCR > 0 then this field forms the upper bits of the limit
 * address for the circular buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1 . IATU_LIMIT_ADDR_OFF_INBOUND_1_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_1_IATU_LIMIT_ADDR_OFF_INBOUND_1_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_INBOUND_1
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc00c5)

/**
 * \brief
 * Forms the LSB's of the Lower Target part of the new address of the
 * translated region. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary (in address match mode); and to the
 * Bar size boundary (in BAR match mode) so that these bits are always '0'.
 * If the BAR is smaller than the iATU region size, then the iATU target
 * address must align to the iATU region size; otherwise it must align to
 * the BAR size.
 *
 * A write to this location is ignored by the PCIe controller.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_LWR_TARGET_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_LWR_TARGET_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_LWR_TARGET_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_LWR_TARGET_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms MSB's of the Lower Target part of the new address of the
 * translated region. These bits are always '0'.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_LWR_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_LWR_TARGET_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_LWR_TARGET_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_LWR_TARGET_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register controls the iATU outbound region access based on the optional iATU outbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_OUTBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0100)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TYPE field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2 . IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TC field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2 . IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * This is a reserved field. Do not use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2 . IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * ATTR field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2 . IATU_REGION_CTRL_1_OFF_OUTBOUND_2_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2 . IATU_REGION_CTRL_1_OFF_OUTBOUND_2_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * When the address of an outbound TLP is matched to this region and the
 * FUNC_BYPASS field in the "iATU Region Control 2 Register" is '0', then
 * the function number used in generating the function part of the
 * requester ID (RID) field of the TLP is taken from this 5-bit register.
 * The value in this register must be 0x0 unless multifunction operation in
 * the controller is enabled (CX_NFUNC > 1).
 *
 * When you are using the AXI Bridge, then this field is swapped before AXI
 * decomposition occurs so that the correct "Max_Read_Request_Size" and
 * "Max_Payload_Size" values are used.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2 . IATU_REGION_CTRL_1_OFF_OUTBOUND_2_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the outbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_OUTBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0101)

/**
 * \brief
 * MSG TLPs (Message Code). When the address of an outbound TLP is matched
 * to this region, and the translated TLP TYPE field is Msg or MsgD; then
 * the message field of the TLP is changed to the value in this register.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an outbound TLP is
 * matched to this region, and the translated TLP TYPE field targets memory
 * space; then the ST field of the TLP is changed to the value in this
 * register. Only Valid when the CX_TPH_ENABLE configuration parameter is
 * 1.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * TAG.
 *
 * The substituted TAG field (byte 6) in the outgoing TLP header when
 * TAG_SUBSTITUTE_EN is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TAG
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TAG(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TAG     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TAG(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TAG Substitute Enable.
 * When enabled and region address is matched, the iATU substitutes the TAG
 * field of the outbound TLP header with the contents of the TAG field in
 * this register. The expected usage scenario is translation from AXI MWr
 * to Vendor Defined Msg/MsgD.
 *
 * Note (CX_TPH_ENABLE=1): TAG substitution for MWr will not occur because
 * this field (byte 6) in the TLP header is the ST field. ST substitution
 * can still take place using the MSG_CODE field in
 * IATU_REGION_CTRL_2_OFF_OUTBOUND_i.
 *
 * Note (CX_10BIT_TAG =1): For 10-bit tags, TAG substitution only applies
 * to the 8 least significant bits of the TAG field (bits 7:0 of Byte 4 of
 * the TLP Header). T9 and T8 of the Header are not substituted.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TAG_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TAG_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TAG_SUBSTITUTE_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TAG_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Translation Bypass.
 * In this mode, the function number of the translated TLP is taken from
 * your application transmit interface and not from the CTRL_1_FUNC_NUM
 * field of the "iATU Region Control 1 Register" or the VF_NUMBER field of
 * the "iATU Control 3 Register."
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_FUNC_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_FUNC_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_FUNC_BYPASS  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_FUNC_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Serialize Non-Posted Requests.
 * In this mode, when the AXI Bridge is populated, same AXI ID Non-Posted
 * Read/Write Requests are transmitted on the wire if there are no other
 * same ID Non-Posted Requests outstanding.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_SNP
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_SNP(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_SNP  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_SNP(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * TLP Header Fields Translation Bypass.  In this mode header fields of the
 * translated TLP is taken from your application transmit interface or, if
 * AMBA is configured,	from the AMBA sideband bus (slv_awmisc_info) and
 * not from the corresponding fields of the
 * IATU_REGION_CTRL_1_OFF_OUTBOUND_i  or IATU_REGION_CTRL_2_OFF_OUTBOUND_i
 * registers. The header fields are
 *  - TC
 *  - PH
 *  - TH
 *  - ST
 *  - AT
 *  - Attr (IDO, RO and NS).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TLP_HEADER_FIELDS_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TLP_HEADER_FIELDS_BYPASS  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Inhibit TLP Payload Data for TLP's in Matched Region; assign iATU region
 * to be TLP without data.
 * When enabled and region address is matched, the iATU marks all TLPs as
 * having no payload data by forcing the TLP header Fmt[1] bit =0,
 * regardless of the application inputs such as slv_wstrb.
 * Encoding are define as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_INHIBIT_PAYLOAD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_INHIBIT_PAYLOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_INHIBIT_PAYLOAD  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_INHIBIT_PAYLOAD(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Header Substitute Enable.
 *
 * When enabled and region address is matched, the iATU fully substitutes
 * bytes 8-11 (for 3 DWORD header) or bytes 12-15 (for 4 DWORD header) of
 * the outbound TLP header with the contents of the LWR_TARGET_RW field in
 * IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_i.
 * Encodings are as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_HEADER_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_HEADER_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_HEADER_SUBSTITUTE_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_HEADER_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * CFG Shift Mode.
 *
 * The iATU uses bits [27:12] of the untranslated address (on the XALI0/1/2
 * interface or AXI slave interface address) to form the BDF number of the
 * outgoing CFG TLP.
 *
 * This supports the Enhanced Configuration Address Mapping (ECAM)
 * mechanism (Section 7.2.2 of the PCI Express Base 3.1 Specification,
 * revision 1.0) by allowing all outgoing I/O and MEM TLPs (that have been
 * translated to CFG) to be mapped from memory space into any 256 MB region
 * of the PCIe configuration space.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Region Enable. This bit must be set to '1' for address translation to
 * take place.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2 . IATU_REGION_CTRL_2_OFF_OUTBOUND_2_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0102)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32-bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0103)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated. In systems with a 32-bit address space, this register
 * is not used and therefore writing to this register has no effect.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2 . IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_OUTBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0104)

/**
 * \brief
 * Circular Buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2 . IATU_LIMIT_ADDR_OFF_OUTBOUND_2_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2 . IATU_LIMIT_ADDR_OFF_OUTBOUND_2_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2 . IATU_LIMIT_ADDR_OFF_OUTBOUND_2_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region, or the outbound TLP header information, depending on the setting  of HEADER_SUBSTITUTE_EN field of IATU_REGION_CTRL_2_VIEWPORT_OFF_OUTBOUND_i register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0105)

/**
 * \brief
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_ is '0'
 * (normal operation):
 *  - LWR_TARGET_RW[31:n] forms MSB's of the Lower Target part of the new
 * address of the translated region;
 *  - LWR_TARGET_RW[n-1:0] are not used. (The start address must be aligned
 * to a CX_ATU_MIN_REGION_SIZE kB boundary, so the lower bits of the start
 * address of the new address of the translated region (bits n-1:0) are
 * always '0').
 *  - n is log2(CX_ATU_MIN_REGION_SIZE).
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_i is '1':
 *  - LWR_TARGET_RW[31:0] forms bytes 8-11 (for 3 dword header) or bytes
 * 12-15 (for 4 dword header) of the outbound TLP header. Usage scenarios
 * include the transmission of Vendor Defined Messages where the controller
 * determines the content of bytes 12 to 15 of the TLP header.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2 . IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_LWR_TARGET_RW_OUTBOUND
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_LWR_TARGET_RW_OUTBOUND(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_LWR_TARGET_RW_OUTBOUND     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_LWR_TARGET_RW_OUTBOUND(x)  (x)


/**
 * \brief This register holds the upper 32 bits of the start address (Upper Target part) of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0106)

/**
 * \brief
 * Forms bits [63:32] of the start address (Upper Target part) of the new
 * address of the translated region.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2 . IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_UPPER_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_UPPER_TARGET_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_UPPER_TARGET_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_UPPER_TARGET_RW(x)  (x)


/**
 * \brief This register controls the iATU inbound region access based on the optional iATU inbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_INBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0140)

/**
 * \brief
 * When the TYPE field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2 . IATU_REGION_CTRL_1_OFF_INBOUND_2_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the TC field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TC Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2 . IATU_REGION_CTRL_1_OFF_INBOUND_2_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * When the TD field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TD Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2 . IATU_REGION_CTRL_1_OFF_INBOUND_2_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the ATTR field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "ATTR Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2 . IATU_REGION_CTRL_1_OFF_INBOUND_2_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2 . IATU_REGION_CTRL_1_OFF_INBOUND_2_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * MEM-I/O: When the Address and BAR matching logic in the controller
 * indicate that a MEM-I/O transaction matches a BAR in the function
 * corresponding to this value, then address translation proceeds. This
 * check is only performed if the "Function Number Match Enable" bit of the
 * "iATU Region Control 2 Register" is set.
 *
 * CFG0/CFG1: When the destination function number as specified in the
 * routing ID of the TLP header matches the function, then address
 * translation proceeds. This check is only performed if the "Function
 * Number Match Enable" bit of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2 . IATU_REGION_CTRL_1_OFF_INBOUND_2_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_2_IATU_REGION_CTRL_1_OFF_INBOUND_2_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the inbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_INBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0141)

/**
 * \brief
 * MSG TLPs: (Message Code). When the MSG_CODE field of an inbound Msg/MsgD
 * TLP is matched to this value, then address translation proceeds (when
 * all other enabled field-matches are successful). This check is only
 * performed if the "Message Code Match Enable" bit of the "iATU Region
 * Control 2 Register" is set and the TYPE field of the inbound TLP is
 * Msg/MsgD.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an inbound TLP is
 * matched to this value, then address translation proceeds. This check is
 * only performed if the "ST Match Enable" bit of the "iATU Region Control
 * 2 Register" is set. The setting is independent of the setting of the TH
 * field. Only Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * BAR Number. When the BAR number of an inbound MEM or IO TLP " that is
 * matched by the normal internal BAR address matching mechanism " is the
 * same as this field, address translation proceeds (when all other enabled
 * field-matches are successful). This check is only performed if the
 * "Match Mode" bit of the "iATU Region Control 2 Register" is set.
 * IO translation would require either 00100b or 00101b in the inbound TLP
 * TYPE; the BAR Number set in the range 000b - 101b and that BAR
 * configured as an IO BAR.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_BAR_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_BAR_NUM(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_BAR_NUM     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_BAR_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Message Type Match Mode.
 * When enabled, and if single address location translate enable is set,
 * then inbound TLPs of type MSG/MSGd which match the type field of the
 * IATU_REGION_CTRL_1_VIEWPORT_OFF_INBOUND_i register (TYPE[4:3]=2'b10)
 * will be translated.
 * Message type match mode overrides any value of MATCH_MODE field in this
 * register. Usage scenarios for this are translation of VDM or ATS
 * messages when AXI bridge is configured on client interface.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_TYPE_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_TYPE_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_TYPE_MATCH_MODE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_TYPE_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * TC Match Enable.
 * Ensures that a successful TC TLP field comparison match (see TC field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_TC_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_TC_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_TC_MATCH_EN  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_TC_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * TD Match Enable.
 * Ensures that a successful TD TLP field comparison match (see TD field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_TD_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_TD_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_TD_MATCH_EN  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_TD_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * ATTR Match Enable.
 * Ensures that a successful ATTR TLP field comparison match (see ATTR
 * field of the "iATU Region Control 1 Register") occurs for address
 * translation to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_ATTR_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_ATTR_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_ATTR_MATCH_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_ATTR_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Match Enable.
 * Ensures that a successful Function Number TLP field comparison match
 * (see Function Number field of the "iATU Region Control 1 Register")
 * occurs (in MEM-I/O and CFG0/CFG1 transactions) for address translation
 * to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_FUNC_NUM_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_FUNC_NUM_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_FUNC_NUM_MATCH_EN  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_FUNC_NUM_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Message Code Match Enable (Msg TLPS). Ensures that a successful message
 * Code TLP field comparison match (see Message Code field of the "iATU
 * Region Control 2 Register") occurs (in MSG transactions) for address
 * translation to proceed.
 *
 * ST Match Enable (Mem TLPs). Ensures that a successful ST TLP field
 * comparison match (see ST field of the "iATU Region Control 2 Register")
 * occurs (in MEM transactions) for address translation to proceed. Only
 * Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_CODE_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_CODE_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_CODE_MATCH_EN  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MSG_CODE_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Single Address Location Translate Enable.
 *
 * When enabled, Rx TLPs can be translated to a single address location as
 * determined by the target address register of the iATU region.
 * The main usage scenario is translation of Messages (such as Vendor
 * Defined or ATS Messages) to MWr TLPs when the AXI bridge is enabled.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_SINGLE_ADDR_LOC_TRANS_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_SINGLE_ADDR_LOC_TRANS_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Response Code.
 * Defines the type of response to give for accesses matching this region.
 * This overrides the normal RADM filter response. Note that this feature
 * is not available for any region where Single Address Location Translate
 * is enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h2:
 * 'h0:
 * 'h3:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_RESPONSE_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_RESPONSE_CODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_RESPONSE_CODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_RESPONSE_CODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Fuzzy Type Match Enable.
 * When enabled, the iATU relaxes the matching of the TLP TYPE field
 * against the expected TYPE field so that
 *  - CfgRd0 and CfgRd1 TLPs are seen as identical. Similarly with CfgWr0
 * and CfgWr1.
 *  - MWr, MRd, and MRdLk TLPs are seen as identical
 *  - The Routing field of Msg/MsgD TLPs is ignored
 *  - FetchAdd, Swap, and CAS are seen as identical.
 * For example, CFG0 in the TYPE field in the "iATU Region Control 1
 * Register" matches against an inbound CfgRd0, CfgRd1, CfgWr0, or CfgWr1
 * TLP.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_FUZZY_TYPE_MATCH_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_FUZZY_TYPE_MATCH_CODE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_FUZZY_TYPE_MATCH_CODE  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_FUZZY_TYPE_MATCH_CODE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * CFG Shift Enable.
 * This is useful for CFG transactions where the PCIe configuration
 * mechanism maps bits [27:12] of the address to the bus/device and
 * function number. This allows a CFG configuration space to be located in
 * any 256MB window of your application memory space using a 28-bit
 * effective address. Shifts bits [31:16] of the untranslated address to
 * form bits [27:12] of the translated address.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode Enable.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address). When set all regions of
 * that type must use address match mode.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Match Mode.
 * Determines Inbound matching mode for TLPs. The mode depends on the type
 * of TLP that is received as follows:
 *
 *  For MEM I/O TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU operates using addresses as in the
 * outbound direction. The Region Base and Limit Registers must be setup.
 *  - 1: BAR Match Mode. BAR matching is used. The "BAR Number" field is
 * relevant. Not used for RC.
 * For CFG0 TLPs, this field is interpreted as follows:
 *  - 0: Routing ID Match Mode. The iATU interprets the Routing ID (Bytes 8
 * to 11 of TLP header) as an address. This corresponds to the upper 16
 * bits of the address in MEM-I/O transactions. The Routing ID of the TLP
 * must be within the base and limit of the iATU region for matching to
 * proceed.
 *  - 1: Accept Mode. The iATU accepts all CFG0 transactions as address
 * matches. The routing ID in the CFG0 TLP is ignored. This is useful as
 * all received CFG0 TLPs should be processed regardless of the Bus number.
 * For MSG/MSGD TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU treats the third dword and fourth
 * dword of the inbound MSG/MSGD TLP as an address and it is matched
 * against the Region Base and Limit Registers.
 *  - 1: Vendor ID Match Mode. This mode is relevant for ID-routed Vendor
 * Defined Messages. The iATU ignores the Routing ID (Bus, Device,
 * Function) in bits [31:16] of the third dword of the TLP header, but
 * matches against the Vendor ID in bits [15:0] of the third dword of the
 * TLP header. Bits [15:0] of the Region Upper Base register should be
 * programmed with the required Vendor ID. The lower Base and Limit
 * Register should be programmed to translate TLPs based on vendor specific
 * information in the fourth dword of the TLP header.
 *  - If SINGLE_ADDRESS_LOCATION_TRANSLATE_EN = 1 AND MSG_TYPE_MATCH_MODE
 * =1, then Match Mode is ignored.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MATCH_MODE  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Region Enable.
 * This bit must be set to '1' for address translation to take place.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2 . IATU_REGION_CTRL_2_OFF_INBOUND_2_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_2_IATU_REGION_CTRL_2_OFF_INBOUND_2_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_INBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0142)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2 . IATU_LWR_BASE_ADDR_OFF_INBOUND_2_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2 . IATU_LWR_BASE_ADDR_OFF_INBOUND_2_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32 bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_INBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0143)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2 . IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_INBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0144)

/**
 * \brief
 * Circular Buffer Increment.
 * When CX_ATU_SLOC_CBUF = 0, then this field is Read-only and forms the
 * lowest bits of the end address of the address region to be translated.
 * When CX_ATU_SLOC_CBUF = 1, then this field is R/W and forms the upper
 * bits of the Circular Buffer Increment size (CBUF_INCR) field for Single
 * Location Address translation. The increment value (in bytes) is decoded
 * as follows:
 * Note: A write to any bit in the CBUF_INCR field resets the circular
 * buffer
 * pointer - that is, the next matched received Message will be translated
 * to the start address of the Circular Buffer. This field must be written
 * to AFTER the target and limit registers have been updated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h9:
 * 'h6:
 * 'h3:
 * 'ha:
 * 'h7:
 * 'h4:
 * 'h1:
 * 'hb:
 * 'h8:
 * 'h5:
 * 'h2:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2 . IATU_LIMIT_ADDR_OFF_INBOUND_2_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones. When
 * SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1, and CBUF_INCR > 0
 * then this field forms lower bits of the limit address for the circular
 * buffer.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2 . IATU_LIMIT_ADDR_OFF_INBOUND_2_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated. When SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1,
 * and CBUF_INCR > 0 then this field forms the upper bits of the limit
 * address for the circular buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2 . IATU_LIMIT_ADDR_OFF_INBOUND_2_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_2_IATU_LIMIT_ADDR_OFF_INBOUND_2_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_INBOUND_2
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0145)

/**
 * \brief
 * Forms the LSB's of the Lower Target part of the new address of the
 * translated region. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary (in address match mode); and to the
 * Bar size boundary (in BAR match mode) so that these bits are always '0'.
 * If the BAR is smaller than the iATU region size, then the iATU target
 * address must align to the iATU region size; otherwise it must align to
 * the BAR size.
 *
 * A write to this location is ignored by the PCIe controller.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_LWR_TARGET_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_LWR_TARGET_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_LWR_TARGET_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_LWR_TARGET_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms MSB's of the Lower Target part of the new address of the
 * translated region. These bits are always '0'.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_LWR_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_LWR_TARGET_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_LWR_TARGET_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_LWR_TARGET_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register controls the iATU outbound region access based on the optional iATU outbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_OUTBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0180)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TYPE field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3 . IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TC field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3 . IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * This is a reserved field. Do not use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3 . IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * ATTR field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3 . IATU_REGION_CTRL_1_OFF_OUTBOUND_3_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3 . IATU_REGION_CTRL_1_OFF_OUTBOUND_3_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * When the address of an outbound TLP is matched to this region and the
 * FUNC_BYPASS field in the "iATU Region Control 2 Register" is '0', then
 * the function number used in generating the function part of the
 * requester ID (RID) field of the TLP is taken from this 5-bit register.
 * The value in this register must be 0x0 unless multifunction operation in
 * the controller is enabled (CX_NFUNC > 1).
 *
 * When you are using the AXI Bridge, then this field is swapped before AXI
 * decomposition occurs so that the correct "Max_Read_Request_Size" and
 * "Max_Payload_Size" values are used.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3 . IATU_REGION_CTRL_1_OFF_OUTBOUND_3_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the outbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_OUTBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0181)

/**
 * \brief
 * MSG TLPs (Message Code). When the address of an outbound TLP is matched
 * to this region, and the translated TLP TYPE field is Msg or MsgD; then
 * the message field of the TLP is changed to the value in this register.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an outbound TLP is
 * matched to this region, and the translated TLP TYPE field targets memory
 * space; then the ST field of the TLP is changed to the value in this
 * register. Only Valid when the CX_TPH_ENABLE configuration parameter is
 * 1.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * TAG.
 *
 * The substituted TAG field (byte 6) in the outgoing TLP header when
 * TAG_SUBSTITUTE_EN is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TAG
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TAG(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TAG     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TAG(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TAG Substitute Enable.
 * When enabled and region address is matched, the iATU substitutes the TAG
 * field of the outbound TLP header with the contents of the TAG field in
 * this register. The expected usage scenario is translation from AXI MWr
 * to Vendor Defined Msg/MsgD.
 *
 * Note (CX_TPH_ENABLE=1): TAG substitution for MWr will not occur because
 * this field (byte 6) in the TLP header is the ST field. ST substitution
 * can still take place using the MSG_CODE field in
 * IATU_REGION_CTRL_2_OFF_OUTBOUND_i.
 *
 * Note (CX_10BIT_TAG =1): For 10-bit tags, TAG substitution only applies
 * to the 8 least significant bits of the TAG field (bits 7:0 of Byte 4 of
 * the TLP Header). T9 and T8 of the Header are not substituted.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TAG_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TAG_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TAG_SUBSTITUTE_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TAG_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Translation Bypass.
 * In this mode, the function number of the translated TLP is taken from
 * your application transmit interface and not from the CTRL_1_FUNC_NUM
 * field of the "iATU Region Control 1 Register" or the VF_NUMBER field of
 * the "iATU Control 3 Register."
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_FUNC_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_FUNC_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_FUNC_BYPASS  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_FUNC_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Serialize Non-Posted Requests.
 * In this mode, when the AXI Bridge is populated, same AXI ID Non-Posted
 * Read/Write Requests are transmitted on the wire if there are no other
 * same ID Non-Posted Requests outstanding.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_SNP
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_SNP(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_SNP  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_SNP(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * TLP Header Fields Translation Bypass.  In this mode header fields of the
 * translated TLP is taken from your application transmit interface or, if
 * AMBA is configured,	from the AMBA sideband bus (slv_awmisc_info) and
 * not from the corresponding fields of the
 * IATU_REGION_CTRL_1_OFF_OUTBOUND_i  or IATU_REGION_CTRL_2_OFF_OUTBOUND_i
 * registers. The header fields are
 *  - TC
 *  - PH
 *  - TH
 *  - ST
 *  - AT
 *  - Attr (IDO, RO and NS).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TLP_HEADER_FIELDS_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TLP_HEADER_FIELDS_BYPASS  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Inhibit TLP Payload Data for TLP's in Matched Region; assign iATU region
 * to be TLP without data.
 * When enabled and region address is matched, the iATU marks all TLPs as
 * having no payload data by forcing the TLP header Fmt[1] bit =0,
 * regardless of the application inputs such as slv_wstrb.
 * Encoding are define as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_INHIBIT_PAYLOAD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_INHIBIT_PAYLOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_INHIBIT_PAYLOAD  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_INHIBIT_PAYLOAD(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Header Substitute Enable.
 *
 * When enabled and region address is matched, the iATU fully substitutes
 * bytes 8-11 (for 3 DWORD header) or bytes 12-15 (for 4 DWORD header) of
 * the outbound TLP header with the contents of the LWR_TARGET_RW field in
 * IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_i.
 * Encodings are as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_HEADER_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_HEADER_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_HEADER_SUBSTITUTE_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_HEADER_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * CFG Shift Mode.
 *
 * The iATU uses bits [27:12] of the untranslated address (on the XALI0/1/2
 * interface or AXI slave interface address) to form the BDF number of the
 * outgoing CFG TLP.
 *
 * This supports the Enhanced Configuration Address Mapping (ECAM)
 * mechanism (Section 7.2.2 of the PCI Express Base 3.1 Specification,
 * revision 1.0) by allowing all outgoing I/O and MEM TLPs (that have been
 * translated to CFG) to be mapped from memory space into any 256 MB region
 * of the PCIe configuration space.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Region Enable. This bit must be set to '1' for address translation to
 * take place.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3 . IATU_REGION_CTRL_2_OFF_OUTBOUND_3_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0182)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32-bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0183)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated. In systems with a 32-bit address space, this register
 * is not used and therefore writing to this register has no effect.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3 . IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_OUTBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0184)

/**
 * \brief
 * Circular Buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3 . IATU_LIMIT_ADDR_OFF_OUTBOUND_3_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3 . IATU_LIMIT_ADDR_OFF_OUTBOUND_3_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3 . IATU_LIMIT_ADDR_OFF_OUTBOUND_3_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region, or the outbound TLP header information, depending on the setting  of HEADER_SUBSTITUTE_EN field of IATU_REGION_CTRL_2_VIEWPORT_OFF_OUTBOUND_i register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0185)

/**
 * \brief
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_ is '0'
 * (normal operation):
 *  - LWR_TARGET_RW[31:n] forms MSB's of the Lower Target part of the new
 * address of the translated region;
 *  - LWR_TARGET_RW[n-1:0] are not used. (The start address must be aligned
 * to a CX_ATU_MIN_REGION_SIZE kB boundary, so the lower bits of the start
 * address of the new address of the translated region (bits n-1:0) are
 * always '0').
 *  - n is log2(CX_ATU_MIN_REGION_SIZE).
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_i is '1':
 *  - LWR_TARGET_RW[31:0] forms bytes 8-11 (for 3 dword header) or bytes
 * 12-15 (for 4 dword header) of the outbound TLP header. Usage scenarios
 * include the transmission of Vendor Defined Messages where the controller
 * determines the content of bytes 12 to 15 of the TLP header.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3 . IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_LWR_TARGET_RW_OUTBOUND
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_LWR_TARGET_RW_OUTBOUND(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_LWR_TARGET_RW_OUTBOUND     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_LWR_TARGET_RW_OUTBOUND(x)  (x)


/**
 * \brief This register holds the upper 32 bits of the start address (Upper Target part) of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0186)

/**
 * \brief
 * Forms bits [63:32] of the start address (Upper Target part) of the new
 * address of the translated region.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3 . IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_UPPER_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_UPPER_TARGET_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_UPPER_TARGET_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_UPPER_TARGET_RW(x)  (x)


/**
 * \brief This register controls the iATU inbound region access based on the optional iATU inbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_INBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc01c0)

/**
 * \brief
 * When the TYPE field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3 . IATU_REGION_CTRL_1_OFF_INBOUND_3_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the TC field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TC Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3 . IATU_REGION_CTRL_1_OFF_INBOUND_3_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * When the TD field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TD Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3 . IATU_REGION_CTRL_1_OFF_INBOUND_3_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the ATTR field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "ATTR Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3 . IATU_REGION_CTRL_1_OFF_INBOUND_3_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3 . IATU_REGION_CTRL_1_OFF_INBOUND_3_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * MEM-I/O: When the Address and BAR matching logic in the controller
 * indicate that a MEM-I/O transaction matches a BAR in the function
 * corresponding to this value, then address translation proceeds. This
 * check is only performed if the "Function Number Match Enable" bit of the
 * "iATU Region Control 2 Register" is set.
 *
 * CFG0/CFG1: When the destination function number as specified in the
 * routing ID of the TLP header matches the function, then address
 * translation proceeds. This check is only performed if the "Function
 * Number Match Enable" bit of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3 . IATU_REGION_CTRL_1_OFF_INBOUND_3_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_3_IATU_REGION_CTRL_1_OFF_INBOUND_3_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the inbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_INBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc01c1)

/**
 * \brief
 * MSG TLPs: (Message Code). When the MSG_CODE field of an inbound Msg/MsgD
 * TLP is matched to this value, then address translation proceeds (when
 * all other enabled field-matches are successful). This check is only
 * performed if the "Message Code Match Enable" bit of the "iATU Region
 * Control 2 Register" is set and the TYPE field of the inbound TLP is
 * Msg/MsgD.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an inbound TLP is
 * matched to this value, then address translation proceeds. This check is
 * only performed if the "ST Match Enable" bit of the "iATU Region Control
 * 2 Register" is set. The setting is independent of the setting of the TH
 * field. Only Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * BAR Number. When the BAR number of an inbound MEM or IO TLP " that is
 * matched by the normal internal BAR address matching mechanism " is the
 * same as this field, address translation proceeds (when all other enabled
 * field-matches are successful). This check is only performed if the
 * "Match Mode" bit of the "iATU Region Control 2 Register" is set.
 * IO translation would require either 00100b or 00101b in the inbound TLP
 * TYPE; the BAR Number set in the range 000b - 101b and that BAR
 * configured as an IO BAR.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_BAR_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_BAR_NUM(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_BAR_NUM     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_BAR_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Message Type Match Mode.
 * When enabled, and if single address location translate enable is set,
 * then inbound TLPs of type MSG/MSGd which match the type field of the
 * IATU_REGION_CTRL_1_VIEWPORT_OFF_INBOUND_i register (TYPE[4:3]=2'b10)
 * will be translated.
 * Message type match mode overrides any value of MATCH_MODE field in this
 * register. Usage scenarios for this are translation of VDM or ATS
 * messages when AXI bridge is configured on client interface.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_TYPE_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_TYPE_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_TYPE_MATCH_MODE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_TYPE_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * TC Match Enable.
 * Ensures that a successful TC TLP field comparison match (see TC field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_TC_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_TC_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_TC_MATCH_EN  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_TC_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * TD Match Enable.
 * Ensures that a successful TD TLP field comparison match (see TD field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_TD_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_TD_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_TD_MATCH_EN  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_TD_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * ATTR Match Enable.
 * Ensures that a successful ATTR TLP field comparison match (see ATTR
 * field of the "iATU Region Control 1 Register") occurs for address
 * translation to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_ATTR_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_ATTR_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_ATTR_MATCH_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_ATTR_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Match Enable.
 * Ensures that a successful Function Number TLP field comparison match
 * (see Function Number field of the "iATU Region Control 1 Register")
 * occurs (in MEM-I/O and CFG0/CFG1 transactions) for address translation
 * to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_FUNC_NUM_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_FUNC_NUM_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_FUNC_NUM_MATCH_EN  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_FUNC_NUM_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Message Code Match Enable (Msg TLPS). Ensures that a successful message
 * Code TLP field comparison match (see Message Code field of the "iATU
 * Region Control 2 Register") occurs (in MSG transactions) for address
 * translation to proceed.
 *
 * ST Match Enable (Mem TLPs). Ensures that a successful ST TLP field
 * comparison match (see ST field of the "iATU Region Control 2 Register")
 * occurs (in MEM transactions) for address translation to proceed. Only
 * Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_CODE_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_CODE_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_CODE_MATCH_EN  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MSG_CODE_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Single Address Location Translate Enable.
 *
 * When enabled, Rx TLPs can be translated to a single address location as
 * determined by the target address register of the iATU region.
 * The main usage scenario is translation of Messages (such as Vendor
 * Defined or ATS Messages) to MWr TLPs when the AXI bridge is enabled.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_SINGLE_ADDR_LOC_TRANS_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_SINGLE_ADDR_LOC_TRANS_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Response Code.
 * Defines the type of response to give for accesses matching this region.
 * This overrides the normal RADM filter response. Note that this feature
 * is not available for any region where Single Address Location Translate
 * is enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h2:
 * 'h0:
 * 'h3:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_RESPONSE_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_RESPONSE_CODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_RESPONSE_CODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_RESPONSE_CODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Fuzzy Type Match Enable.
 * When enabled, the iATU relaxes the matching of the TLP TYPE field
 * against the expected TYPE field so that
 *  - CfgRd0 and CfgRd1 TLPs are seen as identical. Similarly with CfgWr0
 * and CfgWr1.
 *  - MWr, MRd, and MRdLk TLPs are seen as identical
 *  - The Routing field of Msg/MsgD TLPs is ignored
 *  - FetchAdd, Swap, and CAS are seen as identical.
 * For example, CFG0 in the TYPE field in the "iATU Region Control 1
 * Register" matches against an inbound CfgRd0, CfgRd1, CfgWr0, or CfgWr1
 * TLP.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_FUZZY_TYPE_MATCH_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_FUZZY_TYPE_MATCH_CODE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_FUZZY_TYPE_MATCH_CODE  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_FUZZY_TYPE_MATCH_CODE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * CFG Shift Enable.
 * This is useful for CFG transactions where the PCIe configuration
 * mechanism maps bits [27:12] of the address to the bus/device and
 * function number. This allows a CFG configuration space to be located in
 * any 256MB window of your application memory space using a 28-bit
 * effective address. Shifts bits [31:16] of the untranslated address to
 * form bits [27:12] of the translated address.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode Enable.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address). When set all regions of
 * that type must use address match mode.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Match Mode.
 * Determines Inbound matching mode for TLPs. The mode depends on the type
 * of TLP that is received as follows:
 *
 *  For MEM I/O TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU operates using addresses as in the
 * outbound direction. The Region Base and Limit Registers must be setup.
 *  - 1: BAR Match Mode. BAR matching is used. The "BAR Number" field is
 * relevant. Not used for RC.
 * For CFG0 TLPs, this field is interpreted as follows:
 *  - 0: Routing ID Match Mode. The iATU interprets the Routing ID (Bytes 8
 * to 11 of TLP header) as an address. This corresponds to the upper 16
 * bits of the address in MEM-I/O transactions. The Routing ID of the TLP
 * must be within the base and limit of the iATU region for matching to
 * proceed.
 *  - 1: Accept Mode. The iATU accepts all CFG0 transactions as address
 * matches. The routing ID in the CFG0 TLP is ignored. This is useful as
 * all received CFG0 TLPs should be processed regardless of the Bus number.
 * For MSG/MSGD TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU treats the third dword and fourth
 * dword of the inbound MSG/MSGD TLP as an address and it is matched
 * against the Region Base and Limit Registers.
 *  - 1: Vendor ID Match Mode. This mode is relevant for ID-routed Vendor
 * Defined Messages. The iATU ignores the Routing ID (Bus, Device,
 * Function) in bits [31:16] of the third dword of the TLP header, but
 * matches against the Vendor ID in bits [15:0] of the third dword of the
 * TLP header. Bits [15:0] of the Region Upper Base register should be
 * programmed with the required Vendor ID. The lower Base and Limit
 * Register should be programmed to translate TLPs based on vendor specific
 * information in the fourth dword of the TLP header.
 *  - If SINGLE_ADDRESS_LOCATION_TRANSLATE_EN = 1 AND MSG_TYPE_MATCH_MODE
 * =1, then Match Mode is ignored.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MATCH_MODE  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Region Enable.
 * This bit must be set to '1' for address translation to take place.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3 . IATU_REGION_CTRL_2_OFF_INBOUND_3_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_3_IATU_REGION_CTRL_2_OFF_INBOUND_3_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_INBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc01c2)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3 . IATU_LWR_BASE_ADDR_OFF_INBOUND_3_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3 . IATU_LWR_BASE_ADDR_OFF_INBOUND_3_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32 bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_INBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc01c3)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3 . IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_INBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc01c4)

/**
 * \brief
 * Circular Buffer Increment.
 * When CX_ATU_SLOC_CBUF = 0, then this field is Read-only and forms the
 * lowest bits of the end address of the address region to be translated.
 * When CX_ATU_SLOC_CBUF = 1, then this field is R/W and forms the upper
 * bits of the Circular Buffer Increment size (CBUF_INCR) field for Single
 * Location Address translation. The increment value (in bytes) is decoded
 * as follows:
 * Note: A write to any bit in the CBUF_INCR field resets the circular
 * buffer
 * pointer - that is, the next matched received Message will be translated
 * to the start address of the Circular Buffer. This field must be written
 * to AFTER the target and limit registers have been updated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h9:
 * 'h6:
 * 'h3:
 * 'ha:
 * 'h7:
 * 'h4:
 * 'h1:
 * 'hb:
 * 'h8:
 * 'h5:
 * 'h2:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3 . IATU_LIMIT_ADDR_OFF_INBOUND_3_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones. When
 * SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1, and CBUF_INCR > 0
 * then this field forms lower bits of the limit address for the circular
 * buffer.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3 . IATU_LIMIT_ADDR_OFF_INBOUND_3_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated. When SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1,
 * and CBUF_INCR > 0 then this field forms the upper bits of the limit
 * address for the circular buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3 . IATU_LIMIT_ADDR_OFF_INBOUND_3_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_3_IATU_LIMIT_ADDR_OFF_INBOUND_3_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_INBOUND_3
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc01c5)

/**
 * \brief
 * Forms the LSB's of the Lower Target part of the new address of the
 * translated region. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary (in address match mode); and to the
 * Bar size boundary (in BAR match mode) so that these bits are always '0'.
 * If the BAR is smaller than the iATU region size, then the iATU target
 * address must align to the iATU region size; otherwise it must align to
 * the BAR size.
 *
 * A write to this location is ignored by the PCIe controller.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_LWR_TARGET_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_LWR_TARGET_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_LWR_TARGET_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_LWR_TARGET_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms MSB's of the Lower Target part of the new address of the
 * translated region. These bits are always '0'.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_LWR_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_LWR_TARGET_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_LWR_TARGET_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_LWR_TARGET_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register controls the iATU outbound region access based on the optional iATU outbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_OUTBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0200)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TYPE field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4 . IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TC field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4 . IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * This is a reserved field. Do not use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4 . IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * ATTR field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4 . IATU_REGION_CTRL_1_OFF_OUTBOUND_4_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4 . IATU_REGION_CTRL_1_OFF_OUTBOUND_4_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * When the address of an outbound TLP is matched to this region and the
 * FUNC_BYPASS field in the "iATU Region Control 2 Register" is '0', then
 * the function number used in generating the function part of the
 * requester ID (RID) field of the TLP is taken from this 5-bit register.
 * The value in this register must be 0x0 unless multifunction operation in
 * the controller is enabled (CX_NFUNC > 1).
 *
 * When you are using the AXI Bridge, then this field is swapped before AXI
 * decomposition occurs so that the correct "Max_Read_Request_Size" and
 * "Max_Payload_Size" values are used.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4 . IATU_REGION_CTRL_1_OFF_OUTBOUND_4_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the outbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_OUTBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0201)

/**
 * \brief
 * MSG TLPs (Message Code). When the address of an outbound TLP is matched
 * to this region, and the translated TLP TYPE field is Msg or MsgD; then
 * the message field of the TLP is changed to the value in this register.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an outbound TLP is
 * matched to this region, and the translated TLP TYPE field targets memory
 * space; then the ST field of the TLP is changed to the value in this
 * register. Only Valid when the CX_TPH_ENABLE configuration parameter is
 * 1.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * TAG.
 *
 * The substituted TAG field (byte 6) in the outgoing TLP header when
 * TAG_SUBSTITUTE_EN is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TAG
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TAG(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TAG     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TAG(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TAG Substitute Enable.
 * When enabled and region address is matched, the iATU substitutes the TAG
 * field of the outbound TLP header with the contents of the TAG field in
 * this register. The expected usage scenario is translation from AXI MWr
 * to Vendor Defined Msg/MsgD.
 *
 * Note (CX_TPH_ENABLE=1): TAG substitution for MWr will not occur because
 * this field (byte 6) in the TLP header is the ST field. ST substitution
 * can still take place using the MSG_CODE field in
 * IATU_REGION_CTRL_2_OFF_OUTBOUND_i.
 *
 * Note (CX_10BIT_TAG =1): For 10-bit tags, TAG substitution only applies
 * to the 8 least significant bits of the TAG field (bits 7:0 of Byte 4 of
 * the TLP Header). T9 and T8 of the Header are not substituted.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TAG_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TAG_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TAG_SUBSTITUTE_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TAG_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Translation Bypass.
 * In this mode, the function number of the translated TLP is taken from
 * your application transmit interface and not from the CTRL_1_FUNC_NUM
 * field of the "iATU Region Control 1 Register" or the VF_NUMBER field of
 * the "iATU Control 3 Register."
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_FUNC_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_FUNC_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_FUNC_BYPASS  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_FUNC_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Serialize Non-Posted Requests.
 * In this mode, when the AXI Bridge is populated, same AXI ID Non-Posted
 * Read/Write Requests are transmitted on the wire if there are no other
 * same ID Non-Posted Requests outstanding.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_SNP
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_SNP(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_SNP  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_SNP(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * TLP Header Fields Translation Bypass.  In this mode header fields of the
 * translated TLP is taken from your application transmit interface or, if
 * AMBA is configured,	from the AMBA sideband bus (slv_awmisc_info) and
 * not from the corresponding fields of the
 * IATU_REGION_CTRL_1_OFF_OUTBOUND_i  or IATU_REGION_CTRL_2_OFF_OUTBOUND_i
 * registers. The header fields are
 *  - TC
 *  - PH
 *  - TH
 *  - ST
 *  - AT
 *  - Attr (IDO, RO and NS).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TLP_HEADER_FIELDS_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TLP_HEADER_FIELDS_BYPASS  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Inhibit TLP Payload Data for TLP's in Matched Region; assign iATU region
 * to be TLP without data.
 * When enabled and region address is matched, the iATU marks all TLPs as
 * having no payload data by forcing the TLP header Fmt[1] bit =0,
 * regardless of the application inputs such as slv_wstrb.
 * Encoding are define as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_INHIBIT_PAYLOAD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_INHIBIT_PAYLOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_INHIBIT_PAYLOAD  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_INHIBIT_PAYLOAD(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Header Substitute Enable.
 *
 * When enabled and region address is matched, the iATU fully substitutes
 * bytes 8-11 (for 3 DWORD header) or bytes 12-15 (for 4 DWORD header) of
 * the outbound TLP header with the contents of the LWR_TARGET_RW field in
 * IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_i.
 * Encodings are as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_HEADER_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_HEADER_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_HEADER_SUBSTITUTE_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_HEADER_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * CFG Shift Mode.
 *
 * The iATU uses bits [27:12] of the untranslated address (on the XALI0/1/2
 * interface or AXI slave interface address) to form the BDF number of the
 * outgoing CFG TLP.
 *
 * This supports the Enhanced Configuration Address Mapping (ECAM)
 * mechanism (Section 7.2.2 of the PCI Express Base 3.1 Specification,
 * revision 1.0) by allowing all outgoing I/O and MEM TLPs (that have been
 * translated to CFG) to be mapped from memory space into any 256 MB region
 * of the PCIe configuration space.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Region Enable. This bit must be set to '1' for address translation to
 * take place.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4 . IATU_REGION_CTRL_2_OFF_OUTBOUND_4_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0202)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32-bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0203)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated. In systems with a 32-bit address space, this register
 * is not used and therefore writing to this register has no effect.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4 . IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_OUTBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0204)

/**
 * \brief
 * Circular Buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4 . IATU_LIMIT_ADDR_OFF_OUTBOUND_4_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4 . IATU_LIMIT_ADDR_OFF_OUTBOUND_4_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4 . IATU_LIMIT_ADDR_OFF_OUTBOUND_4_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region, or the outbound TLP header information, depending on the setting  of HEADER_SUBSTITUTE_EN field of IATU_REGION_CTRL_2_VIEWPORT_OFF_OUTBOUND_i register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0205)

/**
 * \brief
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_ is '0'
 * (normal operation):
 *  - LWR_TARGET_RW[31:n] forms MSB's of the Lower Target part of the new
 * address of the translated region;
 *  - LWR_TARGET_RW[n-1:0] are not used. (The start address must be aligned
 * to a CX_ATU_MIN_REGION_SIZE kB boundary, so the lower bits of the start
 * address of the new address of the translated region (bits n-1:0) are
 * always '0').
 *  - n is log2(CX_ATU_MIN_REGION_SIZE).
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_i is '1':
 *  - LWR_TARGET_RW[31:0] forms bytes 8-11 (for 3 dword header) or bytes
 * 12-15 (for 4 dword header) of the outbound TLP header. Usage scenarios
 * include the transmission of Vendor Defined Messages where the controller
 * determines the content of bytes 12 to 15 of the TLP header.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4 . IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_LWR_TARGET_RW_OUTBOUND
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_LWR_TARGET_RW_OUTBOUND(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_LWR_TARGET_RW_OUTBOUND     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_LWR_TARGET_RW_OUTBOUND(x)  (x)


/**
 * \brief This register holds the upper 32 bits of the start address (Upper Target part) of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0206)

/**
 * \brief
 * Forms bits [63:32] of the start address (Upper Target part) of the new
 * address of the translated region.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4 . IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_UPPER_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_UPPER_TARGET_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_UPPER_TARGET_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_UPPER_TARGET_RW(x)  (x)


/**
 * \brief This register controls the iATU inbound region access based on the optional iATU inbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_INBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0240)

/**
 * \brief
 * When the TYPE field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4 . IATU_REGION_CTRL_1_OFF_INBOUND_4_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the TC field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TC Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4 . IATU_REGION_CTRL_1_OFF_INBOUND_4_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * When the TD field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TD Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4 . IATU_REGION_CTRL_1_OFF_INBOUND_4_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the ATTR field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "ATTR Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4 . IATU_REGION_CTRL_1_OFF_INBOUND_4_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4 . IATU_REGION_CTRL_1_OFF_INBOUND_4_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * MEM-I/O: When the Address and BAR matching logic in the controller
 * indicate that a MEM-I/O transaction matches a BAR in the function
 * corresponding to this value, then address translation proceeds. This
 * check is only performed if the "Function Number Match Enable" bit of the
 * "iATU Region Control 2 Register" is set.
 *
 * CFG0/CFG1: When the destination function number as specified in the
 * routing ID of the TLP header matches the function, then address
 * translation proceeds. This check is only performed if the "Function
 * Number Match Enable" bit of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4 . IATU_REGION_CTRL_1_OFF_INBOUND_4_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_4_IATU_REGION_CTRL_1_OFF_INBOUND_4_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the inbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_INBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0241)

/**
 * \brief
 * MSG TLPs: (Message Code). When the MSG_CODE field of an inbound Msg/MsgD
 * TLP is matched to this value, then address translation proceeds (when
 * all other enabled field-matches are successful). This check is only
 * performed if the "Message Code Match Enable" bit of the "iATU Region
 * Control 2 Register" is set and the TYPE field of the inbound TLP is
 * Msg/MsgD.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an inbound TLP is
 * matched to this value, then address translation proceeds. This check is
 * only performed if the "ST Match Enable" bit of the "iATU Region Control
 * 2 Register" is set. The setting is independent of the setting of the TH
 * field. Only Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * BAR Number. When the BAR number of an inbound MEM or IO TLP " that is
 * matched by the normal internal BAR address matching mechanism " is the
 * same as this field, address translation proceeds (when all other enabled
 * field-matches are successful). This check is only performed if the
 * "Match Mode" bit of the "iATU Region Control 2 Register" is set.
 * IO translation would require either 00100b or 00101b in the inbound TLP
 * TYPE; the BAR Number set in the range 000b - 101b and that BAR
 * configured as an IO BAR.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_BAR_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_BAR_NUM(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_BAR_NUM     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_BAR_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Message Type Match Mode.
 * When enabled, and if single address location translate enable is set,
 * then inbound TLPs of type MSG/MSGd which match the type field of the
 * IATU_REGION_CTRL_1_VIEWPORT_OFF_INBOUND_i register (TYPE[4:3]=2'b10)
 * will be translated.
 * Message type match mode overrides any value of MATCH_MODE field in this
 * register. Usage scenarios for this are translation of VDM or ATS
 * messages when AXI bridge is configured on client interface.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_TYPE_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_TYPE_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_TYPE_MATCH_MODE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_TYPE_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * TC Match Enable.
 * Ensures that a successful TC TLP field comparison match (see TC field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_TC_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_TC_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_TC_MATCH_EN  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_TC_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * TD Match Enable.
 * Ensures that a successful TD TLP field comparison match (see TD field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_TD_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_TD_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_TD_MATCH_EN  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_TD_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * ATTR Match Enable.
 * Ensures that a successful ATTR TLP field comparison match (see ATTR
 * field of the "iATU Region Control 1 Register") occurs for address
 * translation to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_ATTR_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_ATTR_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_ATTR_MATCH_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_ATTR_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Match Enable.
 * Ensures that a successful Function Number TLP field comparison match
 * (see Function Number field of the "iATU Region Control 1 Register")
 * occurs (in MEM-I/O and CFG0/CFG1 transactions) for address translation
 * to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_FUNC_NUM_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_FUNC_NUM_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_FUNC_NUM_MATCH_EN  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_FUNC_NUM_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Message Code Match Enable (Msg TLPS). Ensures that a successful message
 * Code TLP field comparison match (see Message Code field of the "iATU
 * Region Control 2 Register") occurs (in MSG transactions) for address
 * translation to proceed.
 *
 * ST Match Enable (Mem TLPs). Ensures that a successful ST TLP field
 * comparison match (see ST field of the "iATU Region Control 2 Register")
 * occurs (in MEM transactions) for address translation to proceed. Only
 * Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_CODE_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_CODE_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_CODE_MATCH_EN  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MSG_CODE_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Single Address Location Translate Enable.
 *
 * When enabled, Rx TLPs can be translated to a single address location as
 * determined by the target address register of the iATU region.
 * The main usage scenario is translation of Messages (such as Vendor
 * Defined or ATS Messages) to MWr TLPs when the AXI bridge is enabled.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_SINGLE_ADDR_LOC_TRANS_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_SINGLE_ADDR_LOC_TRANS_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Response Code.
 * Defines the type of response to give for accesses matching this region.
 * This overrides the normal RADM filter response. Note that this feature
 * is not available for any region where Single Address Location Translate
 * is enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h2:
 * 'h0:
 * 'h3:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_RESPONSE_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_RESPONSE_CODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_RESPONSE_CODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_RESPONSE_CODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Fuzzy Type Match Enable.
 * When enabled, the iATU relaxes the matching of the TLP TYPE field
 * against the expected TYPE field so that
 *  - CfgRd0 and CfgRd1 TLPs are seen as identical. Similarly with CfgWr0
 * and CfgWr1.
 *  - MWr, MRd, and MRdLk TLPs are seen as identical
 *  - The Routing field of Msg/MsgD TLPs is ignored
 *  - FetchAdd, Swap, and CAS are seen as identical.
 * For example, CFG0 in the TYPE field in the "iATU Region Control 1
 * Register" matches against an inbound CfgRd0, CfgRd1, CfgWr0, or CfgWr1
 * TLP.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_FUZZY_TYPE_MATCH_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_FUZZY_TYPE_MATCH_CODE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_FUZZY_TYPE_MATCH_CODE  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_FUZZY_TYPE_MATCH_CODE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * CFG Shift Enable.
 * This is useful for CFG transactions where the PCIe configuration
 * mechanism maps bits [27:12] of the address to the bus/device and
 * function number. This allows a CFG configuration space to be located in
 * any 256MB window of your application memory space using a 28-bit
 * effective address. Shifts bits [31:16] of the untranslated address to
 * form bits [27:12] of the translated address.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode Enable.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address). When set all regions of
 * that type must use address match mode.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Match Mode.
 * Determines Inbound matching mode for TLPs. The mode depends on the type
 * of TLP that is received as follows:
 *
 *  For MEM I/O TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU operates using addresses as in the
 * outbound direction. The Region Base and Limit Registers must be setup.
 *  - 1: BAR Match Mode. BAR matching is used. The "BAR Number" field is
 * relevant. Not used for RC.
 * For CFG0 TLPs, this field is interpreted as follows:
 *  - 0: Routing ID Match Mode. The iATU interprets the Routing ID (Bytes 8
 * to 11 of TLP header) as an address. This corresponds to the upper 16
 * bits of the address in MEM-I/O transactions. The Routing ID of the TLP
 * must be within the base and limit of the iATU region for matching to
 * proceed.
 *  - 1: Accept Mode. The iATU accepts all CFG0 transactions as address
 * matches. The routing ID in the CFG0 TLP is ignored. This is useful as
 * all received CFG0 TLPs should be processed regardless of the Bus number.
 * For MSG/MSGD TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU treats the third dword and fourth
 * dword of the inbound MSG/MSGD TLP as an address and it is matched
 * against the Region Base and Limit Registers.
 *  - 1: Vendor ID Match Mode. This mode is relevant for ID-routed Vendor
 * Defined Messages. The iATU ignores the Routing ID (Bus, Device,
 * Function) in bits [31:16] of the third dword of the TLP header, but
 * matches against the Vendor ID in bits [15:0] of the third dword of the
 * TLP header. Bits [15:0] of the Region Upper Base register should be
 * programmed with the required Vendor ID. The lower Base and Limit
 * Register should be programmed to translate TLPs based on vendor specific
 * information in the fourth dword of the TLP header.
 *  - If SINGLE_ADDRESS_LOCATION_TRANSLATE_EN = 1 AND MSG_TYPE_MATCH_MODE
 * =1, then Match Mode is ignored.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MATCH_MODE  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Region Enable.
 * This bit must be set to '1' for address translation to take place.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4 . IATU_REGION_CTRL_2_OFF_INBOUND_4_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_4_IATU_REGION_CTRL_2_OFF_INBOUND_4_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_INBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0242)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4 . IATU_LWR_BASE_ADDR_OFF_INBOUND_4_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4 . IATU_LWR_BASE_ADDR_OFF_INBOUND_4_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32 bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_INBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0243)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4 . IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_INBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0244)

/**
 * \brief
 * Circular Buffer Increment.
 * When CX_ATU_SLOC_CBUF = 0, then this field is Read-only and forms the
 * lowest bits of the end address of the address region to be translated.
 * When CX_ATU_SLOC_CBUF = 1, then this field is R/W and forms the upper
 * bits of the Circular Buffer Increment size (CBUF_INCR) field for Single
 * Location Address translation. The increment value (in bytes) is decoded
 * as follows:
 * Note: A write to any bit in the CBUF_INCR field resets the circular
 * buffer
 * pointer - that is, the next matched received Message will be translated
 * to the start address of the Circular Buffer. This field must be written
 * to AFTER the target and limit registers have been updated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h9:
 * 'h6:
 * 'h3:
 * 'ha:
 * 'h7:
 * 'h4:
 * 'h1:
 * 'hb:
 * 'h8:
 * 'h5:
 * 'h2:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4 . IATU_LIMIT_ADDR_OFF_INBOUND_4_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones. When
 * SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1, and CBUF_INCR > 0
 * then this field forms lower bits of the limit address for the circular
 * buffer.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4 . IATU_LIMIT_ADDR_OFF_INBOUND_4_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated. When SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1,
 * and CBUF_INCR > 0 then this field forms the upper bits of the limit
 * address for the circular buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4 . IATU_LIMIT_ADDR_OFF_INBOUND_4_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_4_IATU_LIMIT_ADDR_OFF_INBOUND_4_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_INBOUND_4
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0245)

/**
 * \brief
 * Forms the LSB's of the Lower Target part of the new address of the
 * translated region. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary (in address match mode); and to the
 * Bar size boundary (in BAR match mode) so that these bits are always '0'.
 * If the BAR is smaller than the iATU region size, then the iATU target
 * address must align to the iATU region size; otherwise it must align to
 * the BAR size.
 *
 * A write to this location is ignored by the PCIe controller.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_LWR_TARGET_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_LWR_TARGET_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_LWR_TARGET_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_LWR_TARGET_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms MSB's of the Lower Target part of the new address of the
 * translated region. These bits are always '0'.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_LWR_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_LWR_TARGET_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_LWR_TARGET_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_LWR_TARGET_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register controls the iATU outbound region access based on the optional iATU outbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_OUTBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0280)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TYPE field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5 . IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * TC field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5 . IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * This is a reserved field. Do not use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5 . IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the address of an outbound TLP is matched to this region, then the
 * ATTR field of the TLP is changed to the value in this register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5 . IATU_REGION_CTRL_1_OFF_OUTBOUND_5_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5 . IATU_REGION_CTRL_1_OFF_OUTBOUND_5_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * When the address of an outbound TLP is matched to this region and the
 * FUNC_BYPASS field in the "iATU Region Control 2 Register" is '0', then
 * the function number used in generating the function part of the
 * requester ID (RID) field of the TLP is taken from this 5-bit register.
 * The value in this register must be 0x0 unless multifunction operation in
 * the controller is enabled (CX_NFUNC > 1).
 *
 * When you are using the AXI Bridge, then this field is swapped before AXI
 * decomposition occurs so that the correct "Max_Read_Request_Size" and
 * "Max_Payload_Size" values are used.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5 . IATU_REGION_CTRL_1_OFF_OUTBOUND_5_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the outbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_OUTBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0281)

/**
 * \brief
 * MSG TLPs (Message Code). When the address of an outbound TLP is matched
 * to this region, and the translated TLP TYPE field is Msg or MsgD; then
 * the message field of the TLP is changed to the value in this register.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an outbound TLP is
 * matched to this region, and the translated TLP TYPE field targets memory
 * space; then the ST field of the TLP is changed to the value in this
 * register. Only Valid when the CX_TPH_ENABLE configuration parameter is
 * 1.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * TAG.
 *
 * The substituted TAG field (byte 6) in the outgoing TLP header when
 * TAG_SUBSTITUTE_EN is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TAG
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TAG(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TAG     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TAG(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * TAG Substitute Enable.
 * When enabled and region address is matched, the iATU substitutes the TAG
 * field of the outbound TLP header with the contents of the TAG field in
 * this register. The expected usage scenario is translation from AXI MWr
 * to Vendor Defined Msg/MsgD.
 *
 * Note (CX_TPH_ENABLE=1): TAG substitution for MWr will not occur because
 * this field (byte 6) in the TLP header is the ST field. ST substitution
 * can still take place using the MSG_CODE field in
 * IATU_REGION_CTRL_2_OFF_OUTBOUND_i.
 *
 * Note (CX_10BIT_TAG =1): For 10-bit tags, TAG substitution only applies
 * to the 8 least significant bits of the TAG field (bits 7:0 of Byte 4 of
 * the TLP Header). T9 and T8 of the Header are not substituted.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TAG_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TAG_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TAG_SUBSTITUTE_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TAG_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Translation Bypass.
 * In this mode, the function number of the translated TLP is taken from
 * your application transmit interface and not from the CTRL_1_FUNC_NUM
 * field of the "iATU Region Control 1 Register" or the VF_NUMBER field of
 * the "iATU Control 3 Register."
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_FUNC_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_FUNC_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_FUNC_BYPASS  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_FUNC_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Serialize Non-Posted Requests.
 * In this mode, when the AXI Bridge is populated, same AXI ID Non-Posted
 * Read/Write Requests are transmitted on the wire if there are no other
 * same ID Non-Posted Requests outstanding.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_SNP
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_SNP(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_SNP  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_SNP(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * TLP Header Fields Translation Bypass.  In this mode header fields of the
 * translated TLP is taken from your application transmit interface or, if
 * AMBA is configured,	from the AMBA sideband bus (slv_awmisc_info) and
 * not from the corresponding fields of the
 * IATU_REGION_CTRL_1_OFF_OUTBOUND_i  or IATU_REGION_CTRL_2_OFF_OUTBOUND_i
 * registers. The header fields are
 *  - TC
 *  - PH
 *  - TH
 *  - ST
 *  - AT
 *  - Attr (IDO, RO and NS).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TLP_HEADER_FIELDS_BYPASS
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TLP_HEADER_FIELDS_BYPASS  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_TLP_HEADER_FIELDS_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Inhibit TLP Payload Data for TLP's in Matched Region; assign iATU region
 * to be TLP without data.
 * When enabled and region address is matched, the iATU marks all TLPs as
 * having no payload data by forcing the TLP header Fmt[1] bit =0,
 * regardless of the application inputs such as slv_wstrb.
 * Encoding are define as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_INHIBIT_PAYLOAD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_INHIBIT_PAYLOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_INHIBIT_PAYLOAD  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_INHIBIT_PAYLOAD(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Header Substitute Enable.
 *
 * When enabled and region address is matched, the iATU fully substitutes
 * bytes 8-11 (for 3 DWORD header) or bytes 12-15 (for 4 DWORD header) of
 * the outbound TLP header with the contents of the LWR_TARGET_RW field in
 * IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_i.
 * Encodings are as above.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_HEADER_SUBSTITUTE_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_HEADER_SUBSTITUTE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_HEADER_SUBSTITUTE_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_HEADER_SUBSTITUTE_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * CFG Shift Mode.
 *
 * The iATU uses bits [27:12] of the untranslated address (on the XALI0/1/2
 * interface or AXI slave interface address) to form the BDF number of the
 * outgoing CFG TLP.
 *
 * This supports the Enhanced Configuration Address Mapping (ECAM)
 * mechanism (Section 7.2.2 of the PCI Express Base 3.1 Specification,
 * revision 1.0) by allowing all outgoing I/O and MEM TLPs (that have been
 * translated to CFG) to be mapped from memory space into any 256 MB region
 * of the PCIe configuration space.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Region Enable. This bit must be set to '1' for address translation to
 * take place.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5 . IATU_REGION_CTRL_2_OFF_OUTBOUND_5_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0282)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5 . IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32-bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0283)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated. In systems with a 32-bit address space, this register
 * is not used and therefore writing to this register has no effect.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5 . IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_OUTBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0284)

/**
 * \brief
 * Circular Buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5 . IATU_LIMIT_ADDR_OFF_OUTBOUND_5_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5 . IATU_LIMIT_ADDR_OFF_OUTBOUND_5_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5 . IATU_LIMIT_ADDR_OFF_OUTBOUND_5_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region, or the outbound TLP header information, depending on the setting  of HEADER_SUBSTITUTE_EN field of IATU_REGION_CTRL_2_VIEWPORT_OFF_OUTBOUND_i register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0285)

/**
 * \brief
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_ is '0'
 * (normal operation):
 *  - LWR_TARGET_RW[31:n] forms MSB's of the Lower Target part of the new
 * address of the translated region;
 *  - LWR_TARGET_RW[n-1:0] are not used. (The start address must be aligned
 * to a CX_ATU_MIN_REGION_SIZE kB boundary, so the lower bits of the start
 * address of the new address of the translated region (bits n-1:0) are
 * always '0').
 *  - n is log2(CX_ATU_MIN_REGION_SIZE).
 * When HEADER_SUBSTITUTE_EN in IATU_REGION_CTRL_2_OFF_OUTBOUND_i is '1':
 *  - LWR_TARGET_RW[31:0] forms bytes 8-11 (for 3 dword header) or bytes
 * 12-15 (for 4 dword header) of the outbound TLP header. Usage scenarios
 * include the transmission of Vendor Defined Messages where the controller
 * determines the content of bytes 12 to 15 of the TLP header.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5 . IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_LWR_TARGET_RW_OUTBOUND
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_LWR_TARGET_RW_OUTBOUND(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_LWR_TARGET_RW_OUTBOUND     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_LWR_TARGET_RW_OUTBOUND(x)  (x)


/**
 * \brief This register holds the upper 32 bits of the start address (Upper Target part) of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc0286)

/**
 * \brief
 * Forms bits [63:32] of the start address (Upper Target part) of the new
 * address of the translated region.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5 . IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_UPPER_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_UPPER_TARGET_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_UPPER_TARGET_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_UPPER_TARGET_RW(x)  (x)


/**
 * \brief This register controls the iATU inbound region access based on the optional iATU inbound features enabled using iATU Region Control 2 Register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_1_OFF_INBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc02c0)

/**
 * \brief
 * When the TYPE field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5 . IATU_REGION_CTRL_1_OFF_INBOUND_5_TYPE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * When the TC field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TC Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5 . IATU_REGION_CTRL_1_OFF_INBOUND_5_TC
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TC(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TC     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TC(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * When the TD field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "TD Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5 . IATU_REGION_CTRL_1_OFF_INBOUND_5_TD
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TD  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_TD(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the ATTR field of an inbound TLP is matched to this value, then
 * address translation proceeds (when all other enabled field-matches are
 * successful). This check is only performed if the "ATTR Match Enable" bit
 * of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5 . IATU_REGION_CTRL_1_OFF_INBOUND_5_ATTR
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_ATTR(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_ATTR     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Increase the maximum ATU Region size.
 * When set, the maximum ATU Region size is determined by
 * CX_ATU_MAX_REGION_SIZE. When clear, the maximum ATU Region size is 4 GB
 * (default).
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5 . IATU_REGION_CTRL_1_OFF_INBOUND_5_INCREASE_REGION_SIZE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_INCREASE_REGION_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_INCREASE_REGION_SIZE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_INCREASE_REGION_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Function Number.
 *
 * MEM-I/O: When the Address and BAR matching logic in the controller
 * indicate that a MEM-I/O transaction matches a BAR in the function
 * corresponding to this value, then address translation proceeds. This
 * check is only performed if the "Function Number Match Enable" bit of the
 * "iATU Region Control 2 Register" is set.
 *
 * CFG0/CFG1: When the destination function number as specified in the
 * routing ID of the TLP header matches the function, then address
 * translation proceeds. This check is only performed if the "Function
 * Number Match Enable" bit of the "iATU Region Control 2 Register" is set.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5 . IATU_REGION_CTRL_1_OFF_INBOUND_5_CTRL_1_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_CTRL_1_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_CTRL_1_FUNC_NUM     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_1_OFF_INBOUND_5_IATU_REGION_CTRL_1_OFF_INBOUND_5_CTRL_1_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,20,3)


/**
 * \brief Using this register you can enable/disable the inbound iATU optional features.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_REGION_CTRL_2_OFF_INBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc02c1)

/**
 * \brief
 * MSG TLPs: (Message Code). When the MSG_CODE field of an inbound Msg/MsgD
 * TLP is matched to this value, then address translation proceeds (when
 * all other enabled field-matches are successful). This check is only
 * performed if the "Message Code Match Enable" bit of the "iATU Region
 * Control 2 Register" is set and the TYPE field of the inbound TLP is
 * Msg/MsgD.
 *
 * Memory TLPs: (ST: Steering Tag). When the ST field of an inbound TLP is
 * matched to this value, then address translation proceeds. This check is
 * only performed if the "ST Match Enable" bit of the "iATU Region Control
 * 2 Register" is set. The setting is independent of the setting of the TH
 * field. Only Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_CODE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * BAR Number. When the BAR number of an inbound MEM or IO TLP " that is
 * matched by the normal internal BAR address matching mechanism " is the
 * same as this field, address translation proceeds (when all other enabled
 * field-matches are successful). This check is only performed if the
 * "Match Mode" bit of the "iATU Region Control 2 Register" is set.
 * IO translation would require either 00100b or 00101b in the inbound TLP
 * TYPE; the BAR Number set in the range 000b - 101b and that BAR
 * configured as an IO BAR.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_BAR_NUM
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_BAR_NUM(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_BAR_NUM     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_BAR_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Message Type Match Mode.
 * When enabled, and if single address location translate enable is set,
 * then inbound TLPs of type MSG/MSGd which match the type field of the
 * IATU_REGION_CTRL_1_VIEWPORT_OFF_INBOUND_i register (TYPE[4:3]=2'b10)
 * will be translated.
 * Message type match mode overrides any value of MATCH_MODE field in this
 * register. Usage scenarios for this are translation of VDM or ATS
 * messages when AXI bridge is configured on client interface.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_TYPE_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_TYPE_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_TYPE_MATCH_MODE  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_TYPE_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * TC Match Enable.
 * Ensures that a successful TC TLP field comparison match (see TC field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_TC_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_TC_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_TC_MATCH_EN  VTSS_BIT(14)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_TC_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * TD Match Enable.
 * Ensures that a successful TD TLP field comparison match (see TD field of
 * the "iATU Region Control 1 Register") occurs for address translation to
 * proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_TD_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_TD_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_TD_MATCH_EN  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_TD_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * ATTR Match Enable.
 * Ensures that a successful ATTR TLP field comparison match (see ATTR
 * field of the "iATU Region Control 1 Register") occurs for address
 * translation to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_ATTR_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_ATTR_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_ATTR_MATCH_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_ATTR_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Function Number Match Enable.
 * Ensures that a successful Function Number TLP field comparison match
 * (see Function Number field of the "iATU Region Control 1 Register")
 * occurs (in MEM-I/O and CFG0/CFG1 transactions) for address translation
 * to proceed.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_FUNC_NUM_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_FUNC_NUM_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_FUNC_NUM_MATCH_EN  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_FUNC_NUM_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Message Code Match Enable (Msg TLPS). Ensures that a successful message
 * Code TLP field comparison match (see Message Code field of the "iATU
 * Region Control 2 Register") occurs (in MSG transactions) for address
 * translation to proceed.
 *
 * ST Match Enable (Mem TLPs). Ensures that a successful ST TLP field
 * comparison match (see ST field of the "iATU Region Control 2 Register")
 * occurs (in MEM transactions) for address translation to proceed. Only
 * Valid when the CX_TPH_ENABLE configuration parameter is '1'.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_CODE_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_CODE_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_CODE_MATCH_EN  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MSG_CODE_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Single Address Location Translate Enable.
 *
 * When enabled, Rx TLPs can be translated to a single address location as
 * determined by the target address register of the iATU region.
 * The main usage scenario is translation of Messages (such as Vendor
 * Defined or ATS Messages) to MWr TLPs when the AXI bridge is enabled.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_SINGLE_ADDR_LOC_TRANS_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_SINGLE_ADDR_LOC_TRANS_EN  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_SINGLE_ADDR_LOC_TRANS_EN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Response Code.
 * Defines the type of response to give for accesses matching this region.
 * This overrides the normal RADM filter response. Note that this feature
 * is not available for any region where Single Address Location Translate
 * is enabled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h2:
 * 'h0:
 * 'h3:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_RESPONSE_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_RESPONSE_CODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_RESPONSE_CODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_RESPONSE_CODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Fuzzy Type Match Enable.
 * When enabled, the iATU relaxes the matching of the TLP TYPE field
 * against the expected TYPE field so that
 *  - CfgRd0 and CfgRd1 TLPs are seen as identical. Similarly with CfgWr0
 * and CfgWr1.
 *  - MWr, MRd, and MRdLk TLPs are seen as identical
 *  - The Routing field of Msg/MsgD TLPs is ignored
 *  - FetchAdd, Swap, and CAS are seen as identical.
 * For example, CFG0 in the TYPE field in the "iATU Region Control 1
 * Register" matches against an inbound CfgRd0, CfgRd1, CfgWr0, or CfgWr1
 * TLP.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_FUZZY_TYPE_MATCH_CODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_FUZZY_TYPE_MATCH_CODE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_FUZZY_TYPE_MATCH_CODE  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_FUZZY_TYPE_MATCH_CODE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * CFG Shift Enable.
 * This is useful for CFG transactions where the PCIe configuration
 * mechanism maps bits [27:12] of the address to the bus/device and
 * function number. This allows a CFG configuration space to be located in
 * any 256MB window of your application memory space using a 28-bit
 * effective address. Shifts bits [31:16] of the untranslated address to
 * form bits [27:12] of the translated address.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_CFG_SHIFT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_CFG_SHIFT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_CFG_SHIFT_MODE  VTSS_BIT(28)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_CFG_SHIFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Invert Mode Enable.
 * When set the address matching region is inverted. Therefore, an address
 * match occurs when the untranslated address is in the region outside the
 * defined range (Base Address to Limit Address). When set all regions of
 * that type must use address match mode.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_INVERT_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_INVERT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_INVERT_MODE  VTSS_BIT(29)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_INVERT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Match Mode.
 * Determines Inbound matching mode for TLPs. The mode depends on the type
 * of TLP that is received as follows:
 *
 *  For MEM I/O TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU operates using addresses as in the
 * outbound direction. The Region Base and Limit Registers must be setup.
 *  - 1: BAR Match Mode. BAR matching is used. The "BAR Number" field is
 * relevant. Not used for RC.
 * For CFG0 TLPs, this field is interpreted as follows:
 *  - 0: Routing ID Match Mode. The iATU interprets the Routing ID (Bytes 8
 * to 11 of TLP header) as an address. This corresponds to the upper 16
 * bits of the address in MEM-I/O transactions. The Routing ID of the TLP
 * must be within the base and limit of the iATU region for matching to
 * proceed.
 *  - 1: Accept Mode. The iATU accepts all CFG0 transactions as address
 * matches. The routing ID in the CFG0 TLP is ignored. This is useful as
 * all received CFG0 TLPs should be processed regardless of the Bus number.
 * For MSG/MSGD TLPs, this field is interpreted as follows:
 *  - 0: Address Match Mode. The iATU treats the third dword and fourth
 * dword of the inbound MSG/MSGD TLP as an address and it is matched
 * against the Region Base and Limit Registers.
 *  - 1: Vendor ID Match Mode. This mode is relevant for ID-routed Vendor
 * Defined Messages. The iATU ignores the Routing ID (Bus, Device,
 * Function) in bits [31:16] of the third dword of the TLP header, but
 * matches against the Vendor ID in bits [15:0] of the third dword of the
 * TLP header. Bits [15:0] of the Region Upper Base register should be
 * programmed with the required Vendor ID. The lower Base and Limit
 * Register should be programmed to translate TLPs based on vendor specific
 * information in the fourth dword of the TLP header.
 *  - If SINGLE_ADDRESS_LOCATION_TRANSLATE_EN = 1 AND MSG_TYPE_MATCH_MODE
 * =1, then Match Mode is ignored.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_MATCH_MODE
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MATCH_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MATCH_MODE  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_MATCH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Region Enable.
 * This bit must be set to '1' for address translation to take place.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5 . IATU_REGION_CTRL_2_OFF_INBOUND_5_REGION_EN
 */
#define  VTSS_F_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_REGION_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_REGION_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_IATU_REGION_CTRL_2_OFF_INBOUND_5_IATU_REGION_CTRL_2_OFF_INBOUND_5_REGION_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief The CX_ATU_MIN_REGION_SIZE configuration parameter (Value Range: 4 kB, 8 kB, 16 kB, 32 kB, 64 kB defaults to 64 kB) specifies the minimum size of an address translation region. For example, if set to 64 kB; the lower 16 bits of the Base, Limit and Target registers are zero and all address regions are aligned on 64 kB boundaries. More precisely, the lower log2(CX_ATU_MIN_REGION_SIZE) bits are zero.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_BASE_ADDR_OFF_INBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc02c2)

/**
 * \brief
 * Forms bits [n-1:0] of the start address of the address region to be
 * translated. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary, so these bits are always 0.
 * A write to this location is ignored by the PCIe controller.
 *
 * n is log2(CX_ATU_MIN_REGION_SIZE)

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5 . IATU_LWR_BASE_ADDR_OFF_INBOUND_5_LWR_BASE_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_LWR_BASE_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_LWR_BASE_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_LWR_BASE_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms bits [31:n] of the start address of the address region to be
 * translated.
 * n is log2(CX_ATU_MIN_REGION_SIZE)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5 . IATU_LWR_BASE_ADDR_OFF_INBOUND_5_LWR_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_LWR_BASE_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_LWR_BASE_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_LWR_BASE_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the upper 32 bits of the start (and end) address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_UPPER_BASE_ADDR_OFF_INBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc02c3)

/**
 * \brief
 * Forms bits [63:32] of the start (and end) address of the address region
 * to be translated.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5 . IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_UPPER_BASE_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_UPPER_BASE_RW(x)  (x)
#define  VTSS_M_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_UPPER_BASE_RW     0xffffffff
#define  VTSS_X_PCIE_DBI_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_UPPER_BASE_RW(x)  (x)


/**
 * \brief This register holds the end address of the address region to be translated.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LIMIT_ADDR_OFF_INBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc02c4)

/**
 * \brief
 * Circular Buffer Increment.
 * When CX_ATU_SLOC_CBUF = 0, then this field is Read-only and forms the
 * lowest bits of the end address of the address region to be translated.
 * When CX_ATU_SLOC_CBUF = 1, then this field is R/W and forms the upper
 * bits of the Circular Buffer Increment size (CBUF_INCR) field for Single
 * Location Address translation. The increment value (in bytes) is decoded
 * as follows:
 * Note: A write to any bit in the CBUF_INCR field resets the circular
 * buffer
 * pointer - that is, the next matched received Message will be translated
 * to the start address of the Circular Buffer. This field must be written
 * to AFTER the target and limit registers have been updated.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h9:
 * 'h6:
 * 'h3:
 * 'ha:
 * 'h7:
 * 'h4:
 * 'h1:
 * 'hb:
 * 'h8:
 * 'h5:
 * 'h2:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5 . IATU_LIMIT_ADDR_OFF_INBOUND_5_CBUF_INCR
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_CBUF_INCR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_CBUF_INCR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_CBUF_INCR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Forms lower bits of the end address of the address region to be
 * translated. The end address must be aligned to a CX_ATU_MIN_REGION_SIZE
 * kB boundary, so these bits are always all ones. When
 * SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1, and CBUF_INCR > 0
 * then this field forms lower bits of the limit address for the circular
 * buffer.
 * A write to this location is ignored by the PCIe controller.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5 . IATU_LIMIT_ADDR_OFF_INBOUND_5_LIMIT_ADDR_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_LIMIT_ADDR_HW(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_LIMIT_ADDR_HW     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_LIMIT_ADDR_HW(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * Forms upper bits of the end address of the address region to be
 * translated. When SINGLE_ADDR_LOC_TRANS_EN = 1, MSG_TYPE_MATCH_MODE = 1,
 * and CBUF_INCR > 0 then this field forms the upper bits of the limit
 * address for the circular buffer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5 . IATU_LIMIT_ADDR_OFF_INBOUND_5_LIMIT_ADDR_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_LIMIT_ADDR_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_LIMIT_ADDR_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LIMIT_ADDR_OFF_INBOUND_5_IATU_LIMIT_ADDR_OFF_INBOUND_5_LIMIT_ADDR_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the Lower Target part of the new address of the translated region.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_ATU_CAP:IATU_LWR_TARGET_ADDR_OFF_INBOUND_5
 */
#define VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5  VTSS_IOREG(VTSS_TO_PCIE_DBI,0xc02c5)

/**
 * \brief
 * Forms the LSB's of the Lower Target part of the new address of the
 * translated region. The start address must be aligned to a
 * CX_ATU_MIN_REGION_SIZE kB boundary (in address match mode); and to the
 * Bar size boundary (in BAR match mode) so that these bits are always '0'.
 * If the BAR is smaller than the iATU region size, then the iATU target
 * address must align to the iATU region size; otherwise it must align to
 * the BAR size.
 *
 * A write to this location is ignored by the PCIe controller.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_LWR_TARGET_HW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_LWR_TARGET_HW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_LWR_TARGET_HW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_LWR_TARGET_HW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Forms MSB's of the Lower Target part of the new address of the
 * translated region. These bits are always '0'.
 *  - Field size depends on log2(CX_ATU_MIN_REGION_SIZE) in address match
 * mode.
 *  - Field size depends on log2(BAR_MASK+1) in BAR match mode.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5 . IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_LWR_TARGET_RW
 */
#define  VTSS_F_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_LWR_TARGET_RW(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_LWR_TARGET_RW     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_LWR_TARGET_RW(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a PCIE_DBI:PF0_PORT_LOGIC
 *
 * Port Logic
 */


/**
 * \brief This register holds the ack latency timer limit and replay timer limit values.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:ACK_LATENCY_TIMER_OFF
 */
#define VTSS_PCIE_DBI_ACK_LATENCY_TIMER_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c0)

/**
 * \brief
 * Ack Latency Timer Limit. The Ack latency timer expires when it reaches
 * this limit. For more information, see "ACK/NAK Scheduling" in the
 * Databook.
 *  - You can modify the effective timer limit through the
 * TIMER_MOD_ACK_NAK field of the TIMER_CTRL_MAX_FUNC_NUM_OFF register.
 *  - After reset, the controller updates the default according to the
 * Negotiated Link Width, Max_Payload_Size, and speed.
 * The value is determined from Tables 3-7, 3-8, and 3-9 of the PCI Express
 * Base Specification.
 *  - The limit must reflect the round trip latency from requester to
 * completer.
 *  - If there is a change in the payload size or link width, the
 * controller overrides any value that you have written to this register
 * field, and resets the field back to the specification-defined value. The
 * controller does not change the value in the TIMER_MOD_ACK_NAK field of
 * the TIMER_CTRL_MAX_FUNC_NUM_OFF register.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ACK_LATENCY_TIMER_OFF . ROUND_TRIP_LATENCY_TIME_LIMIT
 */
#define  VTSS_F_PCIE_DBI_ACK_LATENCY_TIMER_OFF_ROUND_TRIP_LATENCY_TIME_LIMIT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_ACK_LATENCY_TIMER_OFF_ROUND_TRIP_LATENCY_TIME_LIMIT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_ACK_LATENCY_TIMER_OFF_ROUND_TRIP_LATENCY_TIME_LIMIT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Replay Timer Limit. The replay timer expires when it reaches this limit.
 * The controller initiates a replay upon reception of a NAK or when the
 * replay timer expires. For more information, see "Transmit Replay" in the
 * Databook.
 *  - You can modify the effective timer limit through the
 * TIMER_MOD_REPLAY_TIMER field of the TIMER_CTRL_MAX_FUNC_NUM_OFF
 * register.
 *  - After reset, the controller updates the default according to the
 * Negotiated Link Width, Max_Payload_Size, and speed.
 * The value is determined from Tables 3-4, 3-5, and 3-6 of the PCI Express
 * Base Specification.
 *  - If there is a change in the payload size or link speed, the
 * controller overrides any value that you have written to this register
 * field, and resets the field back to the specification-defined value. The
 * controller does not change the value in the TIMER_MOD_REPLAY_TIMER field
 * of the TIMER_CTRL_MAX_FUNC_NUM_OFF register.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_ACK_LATENCY_TIMER_OFF . REPLAY_TIME_LIMIT
 */
#define  VTSS_F_PCIE_DBI_ACK_LATENCY_TIMER_OFF_REPLAY_TIME_LIMIT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_ACK_LATENCY_TIMER_OFF_REPLAY_TIME_LIMIT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_ACK_LATENCY_TIMER_OFF_REPLAY_TIME_LIMIT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register holds the vendor specific DLLP.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:VENDOR_SPEC_DLLP_OFF
 */
#define VTSS_PCIE_DBI_VENDOR_SPEC_DLLP_OFF   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c1)

/**
 * \brief
 * Vendor Specific DLLP Register. You can use this register to send a
 * specific PCI Express DLLP.
 * Your application can write 8-bit DLLP Type and 24-bit Payload data into
 * this register, and set the VENDOR_SPECIFIC_DLLP_REQ field of the
 * PORT_LINK_CTRL_OFF, to send the DLLP.
 *  - Bits[7:0]: DLLP Type
 *  - Bits[31:8]: Vendor Defined Payload (24 bits)
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VENDOR_SPEC_DLLP_OFF . VENDOR_SPEC_DLLP
 */
#define  VTSS_F_PCIE_DBI_VENDOR_SPEC_DLLP_OFF_VENDOR_SPEC_DLLP(x)  (x)
#define  VTSS_M_PCIE_DBI_VENDOR_SPEC_DLLP_OFF_VENDOR_SPEC_DLLP     0xffffffff
#define  VTSS_X_PCIE_DBI_VENDOR_SPEC_DLLP_OFF_VENDOR_SPEC_DLLP(x)  (x)


/**
 * \brief This register can be used for testing and debuggong the link.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PORT_FORCE_OFF
 */
#define VTSS_PCIE_DBI_PORT_FORCE_OFF         VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c2)

/**
 * \brief
 * Link Number. Not used for endpoint.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_FORCE_OFF . LINK_NUM
 */
#define  VTSS_F_PCIE_DBI_PORT_FORCE_OFF_LINK_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_PORT_FORCE_OFF_LINK_NUM     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_PORT_FORCE_OFF_LINK_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Forced Link Command. The link command that the controller is forced to
 * transmit when you set FORCE_EN bit (Force Link).
 * Link command encoding is defined by the ltssm_cmd variable in
 * workspace/src/Layer1/smlh_ltssm.v.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_FORCE_OFF . FORCED_LTSSM
 */
#define  VTSS_F_PCIE_DBI_PORT_FORCE_OFF_FORCED_LTSSM(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PCIE_DBI_PORT_FORCE_OFF_FORCED_LTSSM     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PCIE_DBI_PORT_FORCE_OFF_FORCED_LTSSM(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Force Link. The controller supports a testing and debug capability to
 * allow your software to force the LTSSM state machine into a specific
 * state, and to force the controller to transmit a specific Link Command.
 * Asserting this bit triggers the following actions:
 *  - Forces the LTSSM to the state specified by the Forced LTSSM State
 * field.
 *  - Forces the controller to transmit the command specified by the Forced
 * Link Command field.
 * This is a self-clearing register field. Reading from this register field
 * always returns a '0'.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_FORCE_OFF . FORCE_EN
 */
#define  VTSS_F_PCIE_DBI_PORT_FORCE_OFF_FORCE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_PORT_FORCE_OFF_FORCE_EN  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_PORT_FORCE_OFF_FORCE_EN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Forced LTSSM State. The LTSSM state that the controller is forced to
 * when you set the FORCE_EN bit (Force Link).
 * LTSSM state encoding is defined by the lts_state variable in
 * workspace/src/Layer1/smlh_ltssm.v.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_FORCE_OFF . LINK_STATE
 */
#define  VTSS_F_PCIE_DBI_PORT_FORCE_OFF_LINK_STATE(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_PCIE_DBI_PORT_FORCE_OFF_LINK_STATE     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_PCIE_DBI_PORT_FORCE_OFF_LINK_STATE(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Support LTSSM transition from Polling.Active to Polling.Config based on
 * Rx 8 TSs on any lanes which are Rx EI exit too from base spec after 24ms
 * timeout. This prevents some lanes detected but not Rx EI exit and LTSSM
 * cannot move to Polling.Config. You must set the parameter
 * CX_AUTO_LANE_FLIP_CTRL_EN true for the auto lanes reversal.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_FORCE_OFF . SUPPORT_PART_LANES_RXEI_EXIT
 */
#define  VTSS_F_PCIE_DBI_PORT_FORCE_OFF_SUPPORT_PART_LANES_RXEI_EXIT(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_PORT_FORCE_OFF_SUPPORT_PART_LANES_RXEI_EXIT  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_PORT_FORCE_OFF_SUPPORT_PART_LANES_RXEI_EXIT(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Use the transitions from TS2 to Logical Idle Symbol, SKP OS to Logical
 * Idle Symbol, EIEOS to Logical Idle Symbol, and FTS Sequence to SKP OS to
 * do deskew instead of using received SKP OS or TS1 to TS2 transition if
 * DO_DESKEW_FOR_SRIS is set to '1'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_FORCE_OFF . DO_DESKEW_FOR_SRIS
 */
#define  VTSS_F_PCIE_DBI_PORT_FORCE_OFF_DO_DESKEW_FOR_SRIS(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_PORT_FORCE_OFF_DO_DESKEW_FOR_SRIS  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_PORT_FORCE_OFF_DO_DESKEW_FOR_SRIS(x)  VTSS_EXTRACT_BITFIELD(x,23,1)


/**
 * \brief This register is used to control ack frequency and L0-L1 ASPM behaviour.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:ACK_F_ASPM_CTRL_OFF
 */
#define VTSS_PCIE_DBI_ACK_F_ASPM_CTRL_OFF    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c3)

/**
 * \brief
 * Ack Frequency. The controller accumulates the number of pending ACKs
 * specified here (up to 255) before scheduling an ACK DLLP.
 *  - 0: Indicates that this Ack Frequency Counter feature is turned off.
 * The controller generates a low-priority ACK request for every TLP that
 * it receives. The controller waits until the ACK Latency Timer expires,
 * then converts the current low-priority ACK request to a high-priority
 * ACK request and schedules the DLLP for transmission to the remote link
 * partner.
 *  - 1-255: Indicates that the controller will schedule a high-priority
 * ACK after receiving this number of TLPs. It might schedule the ACK
 * before receiving this number of TLPs if the ACK Latency Timer expires,
 * but never later.
 * For a typical system, you do not have to modify the default setting. For
 * more information, see "ACK/NAK Scheduling" in the Databook.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_ACK_F_ASPM_CTRL_OFF . ACK_FREQ
 */
#define  VTSS_F_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ACK_FREQ(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ACK_FREQ     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ACK_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * The number of Fast Training Sequence(N_FTS) ordered sets to be
 * transmitted when transitioning from L0s to L0.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_ACK_F_ASPM_CTRL_OFF . ACK_N_FTS
 */
#define  VTSS_F_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Common Clock N_FTS. This is the N_FTS when common clock is used.
 * The number of Fast Training Sequence ordered sets to be transmitted when
 * transitioning from L0s to L0. This field is only writable (sticky) when
 * all of the following configuration parameter equations are true:
 *  - CX_NFTS !=CX_COMM_NFTS
 *  - DEFAULT_L0S_EXIT_LATENCY !=DEFAULT_COMM_L0S_EXIT_LATENCY
 *  - DEFAULT_L1_EXIT_LATENCY !=DEFAULT_COMM_L1_EXIT_LATENCY
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_ACK_F_ASPM_CTRL_OFF . COMMON_CLK_N_FTS
 */
#define  VTSS_F_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * L0s Entrance Latency.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h7:
 * 'h6:

 *
 * Field: ::VTSS_PCIE_DBI_ACK_F_ASPM_CTRL_OFF . L0S_ENTRANCE_LATENCY
 */
#define  VTSS_F_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_L0S_ENTRANCE_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_L0S_ENTRANCE_LATENCY     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_L0S_ENTRANCE_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/**
 * \brief
 * L1 Entrance Latency.
 * Note: Programming this timer with a value greater that 32us has no
 * effect unless extended sync is used, or all of the credits are infinite.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h4:
 * 'h0:
 * 'h1:
 * 'h5:
 * 'h2:
 * 'h7:
 * 'h6:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_ACK_F_ASPM_CTRL_OFF . L1_ENTRANCE_LATENCY
 */
#define  VTSS_F_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_L1_ENTRANCE_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_L1_ENTRANCE_LATENCY     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_L1_ENTRANCE_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/**
 * \brief
 * ASPM L1 Entry Control.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_ACK_F_ASPM_CTRL_OFF . ENTER_ASPM
 */
#define  VTSS_F_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ENTER_ASPM(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ENTER_ASPM  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ENTER_ASPM(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * ASPM L1 Timer Enable. This register controls the behaviour of the
 * controller ASPM L1 Entry Timer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_ACK_F_ASPM_CTRL_OFF . ASPM_L1_TIMER_ENABLE
 */
#define  VTSS_F_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ASPM_L1_TIMER_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ASPM_L1_TIMER_ENABLE  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_ACK_F_ASPM_CTRL_OFF_ASPM_L1_TIMER_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Using this register you can control the port link behaviour.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PORT_LINK_CTRL_OFF
 */
#define VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF     VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c4)

/**
 * \brief
 * Vendor Specific DLLP Request.
 *
 * Reading from this self-clearing register field always returns a '0'.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . VENDOR_SPECIFIC_DLLP_REQ
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_VENDOR_SPECIFIC_DLLP_REQ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_VENDOR_SPECIFIC_DLLP_REQ  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_VENDOR_SPECIFIC_DLLP_REQ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Scramble Disable. Turns off data scrambling.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . SCRAMBLE_DISABLE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_SCRAMBLE_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_SCRAMBLE_DISABLE  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_SCRAMBLE_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Loopback Enable. Turns on loopback. For more information, see "Loopback"
 * in the Databook.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . LOOPBACK_ENABLE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_LOOPBACK_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_LOOPBACK_ENABLE  VTSS_BIT(2)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_LOOPBACK_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Reset Assert. Triggers a recovery and forces the LTSSM to the hot reset
 * state (downstream port only).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . RESET_ASSERT
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_RESET_ASSERT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_RESET_ASSERT  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_RESET_ASSERT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DLL Link Enable.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . DLL_LINK_EN
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_DLL_LINK_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_DLL_LINK_EN  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_DLL_LINK_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * LINK_DISABLE is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . LINK_DISABLE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_DISABLE  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Fast Link Mode. Sets all internal LTSSM millisecond timers to Fast Mode
 * for speeding up simulation. Forces the LTSSM training (link
 * initialization) to use shorter time-outs and to link up faster.
 *  - The default scaling factor can be changed using the
 * DEFAULT_FAST_LINK_SCALING_FACTOR parameter or through the
 * FAST_LINK_SCALING_FACTOR field in the TIMER_CTRL_MAX_FUNC_NUM_OFF
 * register.
 *  - Fast Link Mode can also be activated by setting the diag_ctrl_bus[2]
 * pin to '1'.
 * For more information, see the "Fast Link Simulation Mode" section in the
 * "Integrating the Controller with the PHY or Application RTL or
 * Verification IP" chapter of the User Guide.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . FAST_LINK_MODE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_FAST_LINK_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_FAST_LINK_MODE  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_FAST_LINK_MODE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * LINK_RATE is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . LINK_RATE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_RATE(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_RATE     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_RATE(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Link Mode Enable. Sets the number of lanes in the link that you want to
 * connect to the link partner. When you have unused lanes in your system,
 * then you must change the value in this register to reflect the number of
 * lanes. You must also change the value in the "Predetermined Number of
 * Lanes" field of the "Link Width and Speed Change Control Register". For
 * more information, see "How to Tie Off Unused Lanes". For information on
 * upsizing and downsizing the link width, see "Link Establishment".
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h1f:
 * 'h3:
 * 'h3f:
 * 'h7:
 * 'hf:

 *
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . LINK_CAPABLE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_CAPABLE(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_CAPABLE     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_LINK_CAPABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * BEACON_ENABLE is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . BEACON_ENABLE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_BEACON_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_BEACON_ENABLE  VTSS_BIT(24)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_BEACON_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CORRUPT_LCRC_ENABLE is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . CORRUPT_LCRC_ENABLE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_CORRUPT_LCRC_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_CORRUPT_LCRC_ENABLE  VTSS_BIT(25)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_CORRUPT_LCRC_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * EXTENDED_SYNCH is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . EXTENDED_SYNCH
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_EXTENDED_SYNCH(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_EXTENDED_SYNCH  VTSS_BIT(26)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_EXTENDED_SYNCH(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * TRANSMIT_LANE_REVERSALE_ENABLE is an internally reserved field. Do not
 * use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PORT_LINK_CTRL_OFF . TRANSMIT_LANE_REVERSALE_ENABLE
 */
#define  VTSS_F_PCIE_DBI_PORT_LINK_CTRL_OFF_TRANSMIT_LANE_REVERSALE_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_PCIE_DBI_PORT_LINK_CTRL_OFF_TRANSMIT_LANE_REVERSALE_ENABLE  VTSS_BIT(27)
#define  VTSS_X_PCIE_DBI_PORT_LINK_CTRL_OFF_TRANSMIT_LANE_REVERSALE_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)


/**
 * \brief This register is used to control the lane skew behaviour.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:LANE_SKEW_OFF
 */
#define VTSS_PCIE_DBI_LANE_SKEW_OFF          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c5)

/**
 * \brief
 * INSERT_LANE_SKEW is an internally reserved field. Do not use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LANE_SKEW_OFF . INSERT_LANE_SKEW
 */
#define  VTSS_F_PCIE_DBI_LANE_SKEW_OFF_INSERT_LANE_SKEW(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_PCIE_DBI_LANE_SKEW_OFF_INSERT_LANE_SKEW     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_PCIE_DBI_LANE_SKEW_OFF_INSERT_LANE_SKEW(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * \brief
 * Flow Control Disable. Prevents the controller from sending FC DLLPs.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_LANE_SKEW_OFF . FLOW_CTRL_DISABLE
 */
#define  VTSS_F_PCIE_DBI_LANE_SKEW_OFF_FLOW_CTRL_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PCIE_DBI_LANE_SKEW_OFF_FLOW_CTRL_DISABLE  VTSS_BIT(24)
#define  VTSS_X_PCIE_DBI_LANE_SKEW_OFF_FLOW_CTRL_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Ack/Nak Disable. Prevents the controller from sending ACK and NAK DLLPs.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_LANE_SKEW_OFF . ACK_NAK_DISABLE
 */
#define  VTSS_F_PCIE_DBI_LANE_SKEW_OFF_ACK_NAK_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PCIE_DBI_LANE_SKEW_OFF_ACK_NAK_DISABLE  VTSS_BIT(25)
#define  VTSS_X_PCIE_DBI_LANE_SKEW_OFF_ACK_NAK_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Selects Elasticity Buffer operating mode:
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_LANE_SKEW_OFF . ELASTIC_BUFFER_MODE
 */
#define  VTSS_F_PCIE_DBI_LANE_SKEW_OFF_ELASTIC_BUFFER_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_PCIE_DBI_LANE_SKEW_OFF_ELASTIC_BUFFER_MODE  VTSS_BIT(26)
#define  VTSS_X_PCIE_DBI_LANE_SKEW_OFF_ELASTIC_BUFFER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Implementation-specific Number of Lanes. Set the implementation-specific
 * number of lanes.
 * The number of lanes to be used when in Loopback Master. The number of
 * lanes programmed must be equal to or less than the valid number of lanes
 * set in LINK_CAPABLE field. You must configure this field before
 * initiating Loopback by writing in the LOOPBACK_ENABLE field.
 * The controller will transition from Loopback.Entry to Loopback.Active
 * after receiving two consecutive TS1 Ordered Sets with the Loopback bit
 * asserted on the implementation specific number of lanes configured in
 * this field.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hf:
 * 'h0:
 * 'h1:
 * 'h3:
 * 'h7:

 *
 * Field: ::VTSS_PCIE_DBI_LANE_SKEW_OFF . IMPLEMENT_NUM_LANES
 */
#define  VTSS_F_PCIE_DBI_LANE_SKEW_OFF_IMPLEMENT_NUM_LANES(x)  VTSS_ENCODE_BITFIELD(x,27,4)
#define  VTSS_M_PCIE_DBI_LANE_SKEW_OFF_IMPLEMENT_NUM_LANES     VTSS_ENCODE_BITMASK(27,4)
#define  VTSS_X_PCIE_DBI_LANE_SKEW_OFF_IMPLEMENT_NUM_LANES(x)  VTSS_EXTRACT_BITFIELD(x,27,4)

/**
 * \brief
 * Disable Lane-to-Lane Deskew. Causes the controller to disable the
 * internal Lane-to-Lane deskew logic.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_LANE_SKEW_OFF . DISABLE_LANE_TO_LANE_DESKEW
 */
#define  VTSS_F_PCIE_DBI_LANE_SKEW_OFF_DISABLE_LANE_TO_LANE_DESKEW(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_LANE_SKEW_OFF_DISABLE_LANE_TO_LANE_DESKEW  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_LANE_SKEW_OFF_DISABLE_LANE_TO_LANE_DESKEW(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief This register holds the ack frequency, latency, replay, fast link scaling timers,
 and max function number values.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:TIMER_CTRL_MAX_FUNC_NUM_OFF
 */
#define VTSS_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c6)

/**
 * \brief
 * Maximum function number that can be used in a request. Configuration
 * requests targeted at function numbers above this value are returned with
 * UR (unsupported request).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF . MAX_FUNC_NUM
 */
#define  VTSS_F_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_MAX_FUNC_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_MAX_FUNC_NUM     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_MAX_FUNC_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Replay Timer Limit Modifier. Increases the time-out value for the replay
 * timer in increments of 64 clock cycles at Gen1 or Gen2 speed, and in
 * increments of 256 clock cycles at Gen3 speed. A value of '0' represents
 * no modification to the timer limit. For more information, see the
 * REPLAY_TIME_LIMIT field of the ACK_LATENCY_TIMER_OFF register.
 * At Gen3 speed, the controller automatically changes the value of this
 * field to DEFAULT_GEN3_REPLAY_ADJ.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF . TIMER_MOD_REPLAY_TIMER
 */
#define  VTSS_F_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_REPLAY_TIMER(x)  VTSS_ENCODE_BITFIELD(x,14,5)
#define  VTSS_M_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_REPLAY_TIMER     VTSS_ENCODE_BITMASK(14,5)
#define  VTSS_X_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_REPLAY_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,14,5)

/**
 * \brief
 * Ack Latency Timer Modifier. Increases the timer value for the Ack
 * latency timer in increments of 64 clock cycles. A value of '0'
 * represents no modification to the timer value. For more information, see
 * the ROUND_TRIP_LATENCY_TIME_LIMIT field of the ACK_LATENCY_TIMER_OFF
 * register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF . TIMER_MOD_ACK_NAK
 */
#define  VTSS_F_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_ACK_NAK(x)  VTSS_ENCODE_BITFIELD(x,19,5)
#define  VTSS_M_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_ACK_NAK     VTSS_ENCODE_BITMASK(19,5)
#define  VTSS_X_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_ACK_NAK(x)  VTSS_EXTRACT_BITFIELD(x,19,5)

/**
 * \brief
 * UPDATE_FREQ_TIMER is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF . UPDATE_FREQ_TIMER
 */
#define  VTSS_F_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_UPDATE_FREQ_TIMER(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_UPDATE_FREQ_TIMER     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_UPDATE_FREQ_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,24,5)

/**
 * \brief
 * Fast Link Timer Scaling Factor. Sets the scaling factor of LTSSM timer
 * when FAST_LINK_MODE field in PORT_LINK_CTRL_OFF is set to '1'.
 * Default is set by the hidden configuration parameter
 * DEFAULT_FAST_LINK_SCALING_FACTOR which defaults to '0'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h3:
 * 'h1:
 * 'h2:

 *
 * Field: ::VTSS_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF . FAST_LINK_SCALING_FACTOR
 */
#define  VTSS_F_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_FAST_LINK_SCALING_FACTOR(x)  VTSS_ENCODE_BITFIELD(x,29,2)
#define  VTSS_M_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_FAST_LINK_SCALING_FACTOR     VTSS_ENCODE_BITMASK(29,2)
#define  VTSS_X_PCIE_DBI_TIMER_CTRL_MAX_FUNC_NUM_OFF_FAST_LINK_SCALING_FACTOR(x)  VTSS_EXTRACT_BITFIELD(x,29,2)


/**
 * \brief The Filter Mask 1 Register modifies the RADM filtering and error handling rules. For more information, see the "Receive Filtering" section. In each case, '0' applies the associated filtering rule and '1' masks the associated filtering rule.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:SYMBOL_TIMER_FILTER_1_OFF
 */
#define VTSS_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c7)

/**
 * \brief
 * SKP Interval Value. The number of symbol times to wait between
 * transmitting SKP ordered sets. The controller waits the number of symbol
 * times in this register plus 1, between transmitting SKP ordered sets.
 * Your application must program this register accordingly.
 *
 * For example, if 1536 were programmed into this register (in a 250 MHz
 * controller), then the controller actually transmits SKP ordered sets
 * once every 1537 symbol times.
 *
 * The value programmed to this register is actually clock ticks and not
 * symbol times. In a 125 MHz controller, programming the value programmed
 * to this register should be scaled down by a factor of 2 (because one
 * clock tick =two symbol times in this case).
 *
 * Note: This value is not used at Gen3 speed; the skip interval is
 * hardcoded to 370 blocks.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF . SKP_INT_VAL
 */
#define  VTSS_F_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_SKP_INT_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_SKP_INT_VAL     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_SKP_INT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * EIDLE_TIMER is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF . EIDLE_TIMER
 */
#define  VTSS_F_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_EIDLE_TIMER(x)  VTSS_ENCODE_BITFIELD(x,11,4)
#define  VTSS_M_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_EIDLE_TIMER     VTSS_ENCODE_BITMASK(11,4)
#define  VTSS_X_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_EIDLE_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,11,4)

/**
 * \brief
 * Disable FC Watchdog Timer.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF . DISABLE_FC_WD_TIMER
 */
#define  VTSS_F_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_DISABLE_FC_WD_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_DISABLE_FC_WD_TIMER  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_DISABLE_FC_WD_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Filter Mask 1. The Filter Mask 1 Register modifies the RADM filtering
 * and error handling rules. For more information, see the "Receive
 * Filtering" section. In each case, '0' applies the associated filtering
 * rule and '1' masks the associated filtering rule.
 *
 * 31: CX_FLT_MASK_RC_CFG_DISCARD
 *  - 0x0: For RADM RC filter to not allow CFG transaction being received
 *  - 0x1: For RADM RC filter to allow CFG transaction being received
 * 30: CX_FLT_MASK_RC_IO_DISCARD
 *  - 0x0: For RADM RC filter to not allow IO transaction being received
 *  - 0x1: For RADM RC filter to allow IO transaction being received
 * 29: CX_FLT_MASK_MSG_DROP
 *  - 0x0: Drop MSG TLP (except for Vendor MSG). Send decoded message on
 * the SII.
 *  - 0x1: Do not Drop MSG (except for Vendor MSG). Send message TLPs to
 * your application on TRGT1 and send decoded message on the SII.
 *  - The default for this bit is the inverse of FLT_DROP_MSG. That is, if
 * FLT_DROP_MSG =1, then the default of this bit is '0' (drop message
 * TLPs). This bit only controls message TLPs other than Vendor MSGs.
 * Vendor MSGs are controlled by Filter Mask Register 2, bits [1:0].
 * The controller never passes ATS Invalidate messages to the SII interface
 * regardless of this filter rule setting. The controller passes all ATS
 * Invalidate messages to TRGT1 (or AXI bridge master), as they are too big
 * for the SII.
 * 28: CX_FLT_MASK_CPL_ECRC_DISCARD
 *  - Only used when completion queue is advertised with infinite credits
 * and is in store-and-forward mode.
 *  - 0x0: Discard completions with ECRC errors
 *  - 0x1: Allow completions with ECRC errors to be passed up
 *  - Reserved field for SW.
 * 27: CX_FLT_MASK_ECRC_DISCARD
 *  - 0x0: Discard TLPs with ECRC errors
 *  - 0x1: Allow TLPs with ECRC errors to be passed up
 * 26: CX_FLT_MASK_CPL_LEN_MATCH
 *  - 0x0: Enforce length match for completions; a violation results in
 * cpl_abort, and possibly AER of unexp_cpl_err
 *  - 0x1: Mask length match for completions
 * 25: CX_FLT_MASK_CPL_ATTR_MATCH
 *  - 0x0: Enforce attribute match for completions; a violation results in
 * a malformed TLP error, and possibly AER of unexp_cpl_err, cpl_rcvd_ur,
 * cpl_rcvd_ca
 *  - 0x1: Mask attribute match for completions
 * 24: CX_FLT_MASK_CPL_TC_MATCH
 *  - 0x0: Enforce Traffic Class match for completions; a violation results
 * in a malformed TLP error, and possibly AER of unexp_cpl_err,
 * cpl_rcvd_ur, cpl_rcvd_ca
 *  - 0x1: Mask Traffic Class match for completions
 * 23: CX_FLT_MASK_CPL_FUNC_MATCH
 *  - 0x0: Enforce function match for completions; a violation results in
 * cpl_abort, and possibly AER of unexp_cpl_err, cpl_rcvd_ur, cpl_rcvd_ca
 *  - 0x1: Mask function match for completions
 * 22: CX_FLT_MASK_CPL_REQID_MATCH
 *  - 0x0: Enforce Req. Id match for completions; a violation result in
 * cpl_abort, and possibly AER of unexp_cpl_err, cpl_rcvd_ur, cpl_rcvd_ca
 *  - 0x1: Mask Req. Id match for completions
 * 21: CX_FLT_MASK_CPL_TAGERR_MATCH
 *  - 0x0: Enforce Tag Error Rules for completions; a violation result in
 * cpl_abort, and possibly AER of unexp_cpl_err, cpl_rcvd_ur, cpl_rcvd_ca
 *  - 0x1: Mask Tag Error Rules for completions
 * 20: CX_FLT_MASK_LOCKED_RD_AS_UR
 *  - 0x0: Treat locked Read TLPs as UR for EP; Supported for RC
 *  - 0x1: Treat locked Read TLPs as Supported for EP; UR for RC
 * 19: CX_FLT_MASK_CFG_TYPE1_REQ_AS_UR
 *  - 0x0: Treat CFG type1 TLPs as UR for EP; Supported for RC
 *  - 0x1: Treat CFG type1 TLPs as Supported for EP; UR for RC
 *  - When CX_SRIOV_ENABLE is set then this bit is set to allow the filter
 * to process Type 1 Config requests if the EP consumes more than one bus
 * number.
 * 18: CX_FLT_MASK_UR_OUTSIDE_BAR
 *  - 0x0: Treat out-of-bar TLPs as UR
 *  - 0x1: Do not treat out-of-bar TLPs as UR
 * 17: CX_FLT_MASK_UR_POIS
 *  - 0x0: Treat poisoned request TLPs as UR
 *  - 0x1: Do not treat poisoned request TLPs as UR
 *  - The native controller always passes poisoned completions to your
 * application except when you are using the DMA read channel.
 * 16: CX_FLT_MASK_UR_FUNC_MISMATCH
 *  - 0x0: Treat Function MisMatched TLPs as UR
 *  - 0x1: Do not treat Function MisMatched TLPs as UR
 *  - CX_FLT_MASK_UR_FUNC_MISMATCH is not allowed to be set unless
 * CONFIG_LIMIT_REG =0 and TARGET_ABOVE_CONFIG_LIMIT_REG =2 in
 * MISC_CONTROL_1_OFF register or CFG_TLP_BYPASS_EN_REG =1 and
 * TARGET_ABOVE_CONFIG_LIMIT_REG =2 in MISC_CONTROL_1_OFF register.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF . MASK_RADM_1
 */
#define  VTSS_F_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_DBI_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief This register modifies the RADM filtering and error handling rules. For more information, see the "Receive Filtering" section. In each case, '0' applies the associated filtering rule and '1' masks the associated filtering rule.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:FILTER_MASK_2_OFF
 */
#define VTSS_PCIE_DBI_FILTER_MASK_2_OFF      VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1c8)

/**
 * \brief
 * Filter Mask 2. This field modifies the RADM filtering and error handling
 * rules. For more information, see the "Receive Filtering" in the
 * Databook. In each case, '0' applies the associated filtering rule and
 * '1' masks the associated filtering rule.
 *
 * 31:12: Reserved
 *
 * 11: CX_FLT_UNMASK_ATOMIC_SPECIFIC_RULES
 *  - 0x0: Lower Address is checked for Cpls related to AtomicOps Requests.
 *  - 0x1: Lower Address is not checked for Cpls related to AtomicOps
 * Requests.
 * 10: CX_FLT_UNMASK_ATS_SPECIFIC_RULES
 *  - 0x0: Cpls for ATS Requests are processed as MemRd-related Cpl.
 *  - 0x1: Lower Address is not checked for Cpls related to ATS Requests.
 * An ATS-related Cpl completes the request if it has a Byte Count that is
 * equal to four times the Length field.
 * 9: CX_FLT_MASK_CPL_IN_LUT_CHECK
 *  - 0x0: Disable masking of checking if the tag of CPL is registered in
 * LUT
 *  - 0x1: Enable masking of checking if the tag of CPL is registered in
 * LUT
 * 8: CX_FLT_MASK_POIS_ERROR_REPORTING
 *  - 0x0: Disable masking of error reporting for Poisoned TLPs
 *  - 0x1: Enable masking of error reporting for Poisoned TLPs
 * 7: CX_FLT_MASK_PRS_DROP
 *  - 0x0: Allow PRS message to pass through
 *  - 0x1: Drop PRS Messages silently
 *  - This bit is ignored when the CX_FLT_MASK_MSG_DROP bit in the
 * MASK_RADM_1 field of the SYMBOL_TIMER_FILTER_1_OFF register is set to
 * '1'.
 * 6: CX_FLT_UNMASK_TD
 *  - 0x0: Disable unmask TD bit if CX_STRIP_ECRC_ENABLE
 *  - 0x1: Enable unmask TD bit if CX_STRIP_ECRC_ENABLE
 * 5: CX_FLT_UNMASK_UR_POIS_TRGT0
 *  - 0x0: Disable unmask CX_FLT_MASK_UR_POIS with TRGT0 destination
 *  - 0x1: Enable unmask CX_FLT_MASK_UR_POIS with TRGT0 destination
 * 4: CX_FLT_MASK_LN_VENMSG1_DROP
 *  - 0x0: Allow LN message to pass through
 *  - 0x1: Drop LN Messages silently
 * 3: CX_FLT_MASK_HANDLE_FLUSH
 *  - 0x0: Disable controller Filter to handle flush request
 *  - 0x1: Enable controller Filter to handle flush request
 * 2: CX_FLT_MASK_DABORT_4UCPL
 *  - 0x0: Enable DLLP abort for unexpected completion
 *  - 0x1: Do not enable DLLP abort for unexpected completion
 * 1: CX_FLT_MASK_VENMSG1_DROP
 *  - 0x0: Vendor MSG Type 1 dropped silently
 *  - 0x1: Vendor MSG Type 1 not dropped
 * 0: CX_FLT_MASK_VENMSG0_DROP
 *  - 0x0: Vendor MSG Type 0 dropped with UR error reporting
 *  - 0x1: Vendor MSG Type 0 not dropped
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_FILTER_MASK_2_OFF . MASK_RADM_2
 */
#define  VTSS_F_PCIE_DBI_FILTER_MASK_2_OFF_MASK_RADM_2(x)  (x)
#define  VTSS_M_PCIE_DBI_FILTER_MASK_2_OFF_MASK_RADM_2     0xffffffff
#define  VTSS_X_PCIE_DBI_FILTER_MASK_2_OFF_MASK_RADM_2(x)  (x)


/**
 * \brief This register holds cxpl_debug_info[31:0].
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PL_DEBUG0_OFF
 */
#define VTSS_PCIE_DBI_PL_DEBUG0_OFF          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1ca)

/**
 * \brief
 * The value on cxpl_debug_info[31:0].

 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PL_DEBUG0_OFF . DEB_REG_0
 */
#define  VTSS_F_PCIE_DBI_PL_DEBUG0_OFF_DEB_REG_0(x)  (x)
#define  VTSS_M_PCIE_DBI_PL_DEBUG0_OFF_DEB_REG_0     0xffffffff
#define  VTSS_X_PCIE_DBI_PL_DEBUG0_OFF_DEB_REG_0(x)  (x)


/**
 * \brief This register holds cxpl_debug_info[63:32].
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PL_DEBUG1_OFF
 */
#define VTSS_PCIE_DBI_PL_DEBUG1_OFF          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1cb)

/**
 * \brief
 * The value on cxpl_debug_info[63:32].

 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PL_DEBUG1_OFF . DEB_REG_1
 */
#define  VTSS_F_PCIE_DBI_PL_DEBUG1_OFF_DEB_REG_1(x)  (x)
#define  VTSS_M_PCIE_DBI_PL_DEBUG1_OFF_DEB_REG_1     0xffffffff
#define  VTSS_X_PCIE_DBI_PL_DEBUG1_OFF_DEB_REG_1(x)  (x)


/**
 * \brief This register provides transmit posted FC credit status.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:TX_P_FC_CREDIT_STATUS_OFF
 */
#define VTSS_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1cc)

/**
 * \brief
 * Transmit Posted Data FC Credits.
 *  - The posted Data credits advertised by the receiver at the other end
 * of the link, updated with each UpdateFC DLLP.
 *  - Default value depends on the number of advertised credits for header
 * and data
 *  - Scaled Flow Control: [4'b0, xtlh_xadm_ph_cdts, xtlh_xadm_pd_cdts];
 * When the number of advertised posted credits (both header and data) are
 * infinite, then the default would be [4'b0, 12'hFFF, 16'hFFFF].
 *  - No Scaling: [12'b0, xtlh_xadm_ph_cdts, xtlh_xadm_pd_cdts]; When the
 * number of advertised posted credits (both header and data) are infinite,
 * then the default would be [12'b0, 8'hFF, 12'hFFF].

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF . TX_P_DATA_FC_CREDIT
 */
#define  VTSS_F_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF_TX_P_DATA_FC_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF_TX_P_DATA_FC_CREDIT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF_TX_P_DATA_FC_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Transmit Posted Header FC Credits.
 *  - The posted Header credits advertised by the receiver at the other end
 * of the link, updated with each UpdateFC DLLP.
 *  - Default value depends on the number of advertised credits for header
 * and data
 *  - Scaled Flow Control: [4'b0, xtlh_xadm_ph_cdts, xtlh_xadm_pd_cdts];
 * When the number of advertised posted credits (both header and data) are
 * infinite, then the default would be [4'b0, 12'hFFF, 16'hFFFF].
 *  - No Scaling: [12'b0, xtlh_xadm_ph_cdts, xtlh_xadm_pd_cdts]; When the
 * number of advertised posted credits (both header and data) are infinite,
 * then the default would be [12'b0, 8'hFF, 12'hFFF].

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF . TX_P_HEADER_FC_CREDIT
 */
#define  VTSS_F_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF_TX_P_HEADER_FC_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF_TX_P_HEADER_FC_CREDIT     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_PCIE_DBI_TX_P_FC_CREDIT_STATUS_OFF_TX_P_HEADER_FC_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,12,8)


/**
 * \brief This register provides the transmit Non-Posted FC credit status.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:TX_NP_FC_CREDIT_STATUS_OFF
 */
#define VTSS_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1cd)

/**
 * \brief
 * Transmit Non-Posted Data FC Credits.
 *  - The non-posted Data credits advertised by the receiver at the other
 * end of the link, updated with each UpdateFC DLLP.
 *  - Default value depends on the number of advertised credits for header
 * and data
 *  - Scaled Flow Control: [4'b0, xtlh_xadm_nph_cdts, xtlh_xadm_npd_cdts];
 * When the number of advertised non-posted credits (both header and data)
 * are infinite, then the default would be [4'b0, 12'hFFF, 16'hFFFF].
 *  - No Scaling: [12'b0, xtlh_xadm_nph_cdts, xtlh_xadm_npd_cdts]; When the
 * number of advertised non-posted credits (both header and data) are
 * infinite, then the default would be [12'b0, 8'hFF, 12'hFFF].

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF . TX_NP_DATA_FC_CREDIT
 */
#define  VTSS_F_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_DATA_FC_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_DATA_FC_CREDIT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_DATA_FC_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Transmit Non-Posted Header FC Credits.
 *  - The non-posted Header credits advertised by the receiver at the other
 * end of the link, updated with each UpdateFC DLLP.
 *  - Default value depends on the number of advertised credits for header
 * and data
 *  - Scaled Flow Control: [4'b0, xtlh_xadm_nph_cdts, xtlh_xadm_npd_cdts];
 * When the number of advertised non-posted credits (both header and data)
 * are infinite, then the default would be [4'b0, 12'hFFF, 16'hFFFF].
 *  - No Scaling: [12'b0, xtlh_xadm_nph_cdts, xtlh_xadm_npd_cdts]; When the
 * number of advertised non-posted credits (both header and data) are
 * infinite, then the default would be [12'b0, 8'hFF, 12'hFFF].

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF . TX_NP_HEADER_FC_CREDIT
 */
#define  VTSS_F_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_HEADER_FC_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_HEADER_FC_CREDIT     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_PCIE_DBI_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_HEADER_FC_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,12,8)


/**
 * \brief This register provides transmit completion FC credit status.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:TX_CPL_FC_CREDIT_STATUS_OFF
 */
#define VTSS_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1ce)

/**
 * \brief
 * Transmit Completion Data FC Credits.
 *  - The Completion Data credits advertised by the receiver at the other
 * end of the link, updated with each UpdateFC DLLP.
 *  - Default value depends on the number of advertised credits for header
 * and data
 *  - Scaled Flow Control: [4'b0, xtlh_xadm_cplh_cdts,
 * xtlh_xadm_cpld_cdts]; When the number of advertised completion credits
 * (both header and data) are infinite, then the default would be [4'b0,
 * 12'hFFF, 16'hFFFF].
 *  - No Scaling: [12'b0, xtlh_xadm_cplh_cdts, xtlh_xadm_cpld_cdts]; When
 * the number of advertised completion credits (both header and data) are
 * infinite, then the default would be [12'b0, 8'hFF, 12'hFFF].

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF . TX_CPL_DATA_FC_CREDIT
 */
#define  VTSS_F_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_DATA_FC_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_DATA_FC_CREDIT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_DATA_FC_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Transmit Completion Header FC Credits.
 *  - The Completion Header credits advertised by the receiver at the other
 * end of the link, updated with each UpdateFC DLLP.
 *  - Default value depends on the number of advertised credits for header
 * and data
 *  - Scaled Flow Control: [4'b0, xtlh_xadm_cplh_cdts,
 * xtlh_xadm_cpld_cdts]; When the number of advertised completion credits
 * (both header and data) are infinite, then the default would be [4'b0,
 * 12'hFFF, 16'hFFFF].
 *  - No Scaling: [12'b0, xtlh_xadm_cplh_cdts, xtlh_xadm_cpld_cdts]; When
 * the number of advertised completion credits (both header and data) are
 * infinite, then the default would be [12'b0, 8'hFF, 12'hFFF].

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF . TX_CPL_HEADER_FC_CREDIT
 */
#define  VTSS_F_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_HEADER_FC_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_HEADER_FC_CREDIT     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_PCIE_DBI_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_HEADER_FC_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,12,8)


/**
 * \brief This register provides the queue status.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:QUEUE_STATUS_OFF
 */
#define VTSS_PCIE_DBI_QUEUE_STATUS_OFF       VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1cf)

/**
 * \brief
 * Received TLP FC Credits Not Returned.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_QUEUE_STATUS_OFF . RX_TLP_FC_CREDIT_NON_RETURN
 */
#define  VTSS_F_PCIE_DBI_QUEUE_STATUS_OFF_RX_TLP_FC_CREDIT_NON_RETURN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_QUEUE_STATUS_OFF_RX_TLP_FC_CREDIT_NON_RETURN  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_QUEUE_STATUS_OFF_RX_TLP_FC_CREDIT_NON_RETURN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Transmit Retry Buffer Not Empty.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_QUEUE_STATUS_OFF . TX_RETRY_BUFFER_NE
 */
#define  VTSS_F_PCIE_DBI_QUEUE_STATUS_OFF_TX_RETRY_BUFFER_NE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_QUEUE_STATUS_OFF_TX_RETRY_BUFFER_NE  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_QUEUE_STATUS_OFF_TX_RETRY_BUFFER_NE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Receive Credit Queue Not Empty.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_QUEUE_STATUS_OFF . RX_QUEUE_NON_EMPTY
 */
#define  VTSS_F_PCIE_DBI_QUEUE_STATUS_OFF_RX_QUEUE_NON_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_DBI_QUEUE_STATUS_OFF_RX_QUEUE_NON_EMPTY  VTSS_BIT(2)
#define  VTSS_X_PCIE_DBI_QUEUE_STATUS_OFF_RX_QUEUE_NON_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Receive Credit Queue Overflow.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_QUEUE_STATUS_OFF . RX_QUEUE_OVERFLOW
 */
#define  VTSS_F_PCIE_DBI_QUEUE_STATUS_OFF_RX_QUEUE_OVERFLOW(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_QUEUE_STATUS_OFF_RX_QUEUE_OVERFLOW  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_QUEUE_STATUS_OFF_RX_QUEUE_OVERFLOW(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Receive Serialization Queue Not Empty.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_QUEUE_STATUS_OFF . RX_SERIALIZATION_Q_NON_EMPTY
 */
#define  VTSS_F_PCIE_DBI_QUEUE_STATUS_OFF_RX_SERIALIZATION_Q_NON_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_QUEUE_STATUS_OFF_RX_SERIALIZATION_Q_NON_EMPTY  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_QUEUE_STATUS_OFF_RX_SERIALIZATION_Q_NON_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * FC Latency Timer Override Value. When you set the "FC Latency Timer
 * Override Enable" in this register, the value in this field will override
 * the FC latency timer value that the controller calculates according to
 * the PCIe specification. For more information, see "Flow Control" in the
 * Databook.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_QUEUE_STATUS_OFF . TIMER_MOD_FLOW_CONTROL
 */
#define  VTSS_F_PCIE_DBI_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,16,13)
#define  VTSS_M_PCIE_DBI_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL     VTSS_ENCODE_BITMASK(16,13)
#define  VTSS_X_PCIE_DBI_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,16,13)

/**
 * \brief
 * FC Latency Timer Override Enable.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_QUEUE_STATUS_OFF . TIMER_MOD_FLOW_CONTROL_EN
 */
#define  VTSS_F_PCIE_DBI_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief This register is used for setting the WRR weights for VC0 - VC3.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:VC_TX_ARBI_1_OFF
 */
#define VTSS_PCIE_DBI_VC_TX_ARBI_1_OFF       VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1d0)

/**
 * \brief
 * WRR Weight for VC0.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC_TX_ARBI_1_OFF . WRR_WEIGHT_VC_0
 */
#define  VTSS_F_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * WRR Weight for VC1.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC_TX_ARBI_1_OFF . WRR_WEIGHT_VC_1
 */
#define  VTSS_F_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * WRR Weight for VC2.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC_TX_ARBI_1_OFF . WRR_WEIGHT_VC_2
 */
#define  VTSS_F_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * WRR Weight for VC3.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC_TX_ARBI_1_OFF . WRR_WEIGHT_VC_3
 */
#define  VTSS_F_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief This register is used for setting the WRR weights for VC4 - VC7.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:VC_TX_ARBI_2_OFF
 */
#define VTSS_PCIE_DBI_VC_TX_ARBI_2_OFF       VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1d1)

/**
 * \brief
 * WRR Weight for VC4.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC_TX_ARBI_2_OFF . WRR_WEIGHT_VC_4
 */
#define  VTSS_F_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * WRR Weight for VC5.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC_TX_ARBI_2_OFF . WRR_WEIGHT_VC_5
 */
#define  VTSS_F_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * WRR Weight for VC6.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC_TX_ARBI_2_OFF . WRR_WEIGHT_VC_6
 */
#define  VTSS_F_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_6(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_6     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_6(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * WRR Weight for VC7.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC_TX_ARBI_2_OFF . WRR_WEIGHT_VC_7
 */
#define  VTSS_F_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_7(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_7     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_7(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief This register controls segmented-buffer VC0 posted receive queue operation.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:VC0_P_RX_Q_CTRL_OFF
 */
#define VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1d2)

/**
 * \brief
 * VC0 Posted Data Credits. The number of initial posted data credits for
 * VC0, used only in the segmented-buffer configuration.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hfff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . VC0_P_DATA_CREDIT
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_DATA_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_DATA_CREDIT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_DATA_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * VC0 Posted Header Credits. The number of initial posted header credits
 * for VC0, used only in the segmented-buffer configuration.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . VC0_P_HEADER_CREDIT
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_HEADER_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_HEADER_CREDIT     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_HEADER_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,12,8)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . RESERVED4
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_RESERVED4(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_RESERVED4  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_RESERVED4(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . VC0_P_TLP_Q_MODE
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_TLP_Q_MODE(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_TLP_Q_MODE     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_TLP_Q_MODE(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/**
 * \brief
 * VC0 Scale Posted Header Credits.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . VC0_P_HDR_SCALE
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_HDR_SCALE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_HDR_SCALE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_HDR_SCALE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * VC0 Scale Posted Data Credits.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . VC0_P_DATA_SCALE
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_DATA_SCALE(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_DATA_SCALE     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC0_P_DATA_SCALE(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . RESERVED5
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_RESERVED5(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_RESERVED5     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_RESERVED5(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * TLP Type Ordering for VC0. Determines the TLP type ordering rule for VC0
 * receive queues, used only in the segmented-buffer configuration:
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . TLP_TYPE_ORDERING_VC0
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_TLP_TYPE_ORDERING_VC0(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_TLP_TYPE_ORDERING_VC0  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_TLP_TYPE_ORDERING_VC0(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * VC Ordering for Receive Queues. Determines the VC ordering rule for the
 * receive queues, used only in the segmented-buffer configuration:
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF . VC_ORDERING_RX_Q
 */
#define  VTSS_F_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC_ORDERING_RX_Q(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC_ORDERING_RX_Q  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_VC0_P_RX_Q_CTRL_OFF_VC_ORDERING_RX_Q(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief This register controls the segmented-buffer VC0 non-posted receive queue operation.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:VC0_NP_RX_Q_CTRL_OFF
 */
#define VTSS_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1d3)

/**
 * \brief
 * VC0 Non-Posted Data Credits. The number of initial non-posted data
 * credits for VC0, used only in the segmented-buffer configuration.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hfff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF . VC0_NP_DATA_CREDIT
 */
#define  VTSS_F_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_DATA_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_DATA_CREDIT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_DATA_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * VC0 Non-Posted Header Credits. The number of initial non-posted header
 * credits for VC0, used only in the segmented-buffer configuration.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF . VC0_NP_HEADER_CREDIT
 */
#define  VTSS_F_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_HEADER_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_HEADER_CREDIT     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_HEADER_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,12,8)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF . RESERVED6
 */
#define  VTSS_F_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_RESERVED6(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_RESERVED6  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_RESERVED6(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF . VC0_NP_TLP_Q_MODE
 */
#define  VTSS_F_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_TLP_Q_MODE(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_TLP_Q_MODE     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_TLP_Q_MODE(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/**
 * \brief
 * VC0 Scale Non-Posted Header Credits.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF . VC0_NP_HDR_SCALE
 */
#define  VTSS_F_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_HDR_SCALE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_HDR_SCALE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_HDR_SCALE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * VC0 Scale Non-Posted Data Credits.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF . VC0_NP_DATA_SCALE
 */
#define  VTSS_F_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_DATA_SCALE(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_DATA_SCALE     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_DATA_SCALE(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF . RESERVED7
 */
#define  VTSS_F_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_RESERVED7(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_RESERVED7     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_PCIE_DBI_VC0_NP_RX_Q_CTRL_OFF_RESERVED7(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief This register controls the segmented-buffer VC0 completion receive queue operation.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:VC0_CPL_RX_Q_CTRL_OFF
 */
#define VTSS_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x1d4)

/**
 * \brief
 * VC0 Completion Data Credits. The number of initial Completion data
 * credits for VC0, used only in the segmented-buffer configuration.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hfff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF . VC0_CPL_DATA_CREDIT
 */
#define  VTSS_F_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_DATA_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_DATA_CREDIT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_DATA_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * VC0 Completion Header Credits. The number of initial Completion header
 * credits for VC0, used only in the segmented-buffer configuration.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'hff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF . VC0_CPL_HEADER_CREDIT
 */
#define  VTSS_F_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_HEADER_CREDIT(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_HEADER_CREDIT     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_HEADER_CREDIT(x)  VTSS_EXTRACT_BITFIELD(x,12,8)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF . RESERVED8
 */
#define  VTSS_F_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_RESERVED8(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_RESERVED8  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_RESERVED8(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF . VC0_CPL_TLP_Q_MODE
 */
#define  VTSS_F_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_TLP_Q_MODE(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_TLP_Q_MODE     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_TLP_Q_MODE(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/**
 * \brief
 * VC0 Scale CPL Header Credits.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF . VC0_CPL_HDR_SCALE
 */
#define  VTSS_F_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_HDR_SCALE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_HDR_SCALE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_HDR_SCALE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * VC0 Scale CPL Data Credits.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF . VC0_CPL_DATA_SCALE
 */
#define  VTSS_F_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_DATA_SCALE(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_DATA_SCALE     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_DATA_SCALE(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF . RESERVED9
 */
#define  VTSS_F_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_RESERVED9(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_RESERVED9     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_PCIE_DBI_VC0_CPL_RX_Q_CTRL_OFF_RESERVED9(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief This register controls various functions of the controller related to link training, lane reversal, and equalization.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:GEN2_CTRL_OFF
 */
#define VTSS_PCIE_DBI_GEN2_CTRL_OFF          VTSS_IOREG(VTSS_TO_PCIE_DBI,0x203)

/**
 * \brief
 * Sets the Number of Fast Training Sequences (N_FTS) that the controller
 * advertises as its N_FTS during Gen2 or Gen3 link training. This value is
 * used to inform the link partner about the PHY's ability to recover
 * synchronization after a low power state. The number should be provided
 * by the PHY vendor. Do not set N_FTS to zero; doing so can cause the
 * LTSSM to go into the recovery state when exiting from L0s.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . FAST_TRAINING_SEQ
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_FAST_TRAINING_SEQ(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_FAST_TRAINING_SEQ     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_FAST_TRAINING_SEQ(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Predetermined Number of Lanes. Defines the number of lanes which are
 * connected and not bad. Used to limit the effective link width to ignore
 * 'broken" or "unused" lanes that detect a receiver. Indicates the number
 * of lanes to check for exit from Electrical Idle in Polling.Active and
 * L2.Idle. It is possible that the LTSSM might detect a receiver on a bad
 * or broken lane during the Detect Substate. However, it is also possible
 * that such a lane might also fail to exit Electrical Idle and therefore
 * prevent a valid link from being configured. This value is referred to as
 * the "Predetermined Number of Lanes" in section 4.2.6.2.1 of the PCI
 * Express Base Specification.
 * When you have unused lanes in your system, then you must change the
 * value in this register to reflect the number of lanes. You must also
 * change the value in the "Link Mode Enable" field of PORT_LINK_CTRL_OFF.
 * The value in this register is normally the same as the encoded value in
 * PORT_LINK_CTRL_OFF. If you find that one of your used lanes is bad then
 * you must reduce the value in this register. For more information, see
 * "How to Tie Off Unused Lanes" in the Databook. For information on
 * upsizing and downsizing the link width, see "Link Establishment" in the
 * Databook.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . NUM_OF_LANES
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_NUM_OF_LANES(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_NUM_OF_LANES     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_NUM_OF_LANES(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Predetermined Lane for Auto Flip. This field defines which physical lane
 * is connected to logical Lane0 by the flip operation performed in Detect.
 * This field is used to restrict the receiver detect procedure to a
 * particular lane when the default detect and polling procedure performed
 * on all lanes cannot be successful. A notable example of when it is
 * useful to program this field to a value different from the default, is
 * when a lane is asymmetrically broken, that is, it is detected in Detect
 * LTSSM state but it cannot exit Electrical Idle in Polling LTSSM state.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h4:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . PRE_DET_LANE
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_PRE_DET_LANE(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_PRE_DET_LANE     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_PRE_DET_LANE(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief
 * Enable Auto flipping of the lanes. You must set the
 * CX_AUTO_LANE_FLIP_CTRL_EN configuration parameter to include the
 * hardware for this feature in the controller. For more information, see
 * the 'Lane Reversal' appendix in the Databook.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . AUTO_LANE_FLIP_CTRL_EN
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_AUTO_LANE_FLIP_CTRL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_AUTO_LANE_FLIP_CTRL_EN  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_AUTO_LANE_FLIP_CTRL_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Directed Speed Change.
 *
 * When the speed change occurs, the controller will clear the contents of
 * this field; and a read to this field by your software will return a '0'.
 * To manually initiate the speed change:
 *  - Write to LINK_CONTROL2_LINK_STATUS2_REG.PCIE_CAP_TARGET_LINK_SPEED in
 * the local device
 *  - De-assert this field
 *  - Assert this field
 * If you set the default of this field using the DEFAULT_GEN2_SPEED_CHANGE
 * configuration parameter to '1', then the speed change is initiated
 * automatically after link up, and the controller clears the contents of
 * this field. If you want to prevent this automatic speed change, then
 * write a lower speed value to the Target Link Speed field of the Link
 * Control 2 register
 * (LINK_CONTROL2_LINK_STATUS2_OFF.PCIE_CAP_TARGET_LINK_SPEED) through the
 * DBI before link up.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . DIRECT_SPEED_CHANGE
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_DIRECT_SPEED_CHANGE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_DIRECT_SPEED_CHANGE  VTSS_BIT(17)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_DIRECT_SPEED_CHANGE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Config PHY Tx Swing. Controls the PHY transmitter voltage swing level.
 * The controller drives the mac_phy_txswing output from this register bit
 * field.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . CONFIG_PHY_TX_CHANGE
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_CONFIG_PHY_TX_CHANGE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_CONFIG_PHY_TX_CHANGE  VTSS_BIT(18)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_CONFIG_PHY_TX_CHANGE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Config Tx Compliance Receive Bit.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . CONFIG_TX_COMP_RX
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_CONFIG_TX_COMP_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_CONFIG_TX_COMP_RX  VTSS_BIT(19)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_CONFIG_TX_COMP_RX(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Used to set the de-emphasis level for upstream ports. This bit selects
 * the level of de-emphasis the link operates at.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . SEL_DEEMPHASIS
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_SEL_DEEMPHASIS(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_SEL_DEEMPHASIS  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_SEL_DEEMPHASIS(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Electrical Idle Inference Mode at Gen1 Rate. Programmable mode to
 * determine inferred electrical idle (EI) in Recovery.Speed or
 * Loopback.Active (as slave) state at Gen1 speed by looking for a '1'
 * value on RxElecIdle instead of looking for a '0' on RxValid. If the PHY
 * fails to de-assert the RxValid signal in Recovery.Speed or
 * Loopback.Active (because of corrupted EIOS for example), then EI cannot
 * be inferred successfully in the controller by just detecting the
 * condition RxValid=0.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . GEN1_EI_INFERENCE
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_GEN1_EI_INFERENCE(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_GEN1_EI_INFERENCE  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_GEN1_EI_INFERENCE(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * The select_deemphasis variable for DSP on entry to Recovery.RcvrCfg
 * state is muxed between the Selectable De-emphasis field in the Link
 * Control 2 register and the value requested by the Upstream Port in the
 * eight consecutive TS1 Ordered Sets it received.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . SELECT_DEEMPH_VAR_MUX
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_SELECT_DEEMPH_VAR_MUX(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_SELECT_DEEMPH_VAR_MUX  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_SELECT_DEEMPH_VAR_MUX(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * The selectable deemphasis bit (Symbol 4 bit 6) of the transmitted TS2
 * Ordered Sets for DSP in Recovery.RcvrCfg state is muxed between the
 * Selectable De-emphasis field in the Link Control 2 register and the
 * value requested by USP in Recovery.RcvrLock state through Tx TS1s from
 * USP.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN2_CTRL_OFF . SELECTABLE_DEEMPH_BIT_MUX
 */
#define  VTSS_F_PCIE_DBI_GEN2_CTRL_OFF_SELECTABLE_DEEMPH_BIT_MUX(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_GEN2_CTRL_OFF_SELECTABLE_DEEMPH_BIT_MUX  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_GEN2_CTRL_OFF_SELECTABLE_DEEMPH_BIT_MUX(x)  VTSS_EXTRACT_BITFIELD(x,23,1)


/**
 * \brief Memory mapped register from phy_cfg_status GPIO input pins.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PHY_STATUS_OFF
 */
#define VTSS_PCIE_DBI_PHY_STATUS_OFF         VTSS_IOREG(VTSS_TO_PCIE_DBI,0x204)

/**
 * \brief
 * PHY Status. Data received directly from the phy_cfg_status bus.
 * These is a GPIO register reflecting the values on the static
 * phy_cfg_status input signals. The usage is left completely to the user
 * and does not in any way influence controller functionality. You can use
 * it for any static sideband status signalling requirements that you have
 * for your PHY.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_STATUS_OFF . PHY_STATUS
 */
#define  VTSS_F_PCIE_DBI_PHY_STATUS_OFF_PHY_STATUS(x)  (x)
#define  VTSS_M_PCIE_DBI_PHY_STATUS_OFF_PHY_STATUS     0xffffffff
#define  VTSS_X_PCIE_DBI_PHY_STATUS_OFF_PHY_STATUS(x)  (x)


/**
 * \brief Memory mapped register to cfg_phy_control GPIO output pins.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PHY_CONTROL_OFF
 */
#define VTSS_PCIE_DBI_PHY_CONTROL_OFF        VTSS_IOREG(VTSS_TO_PCIE_DBI,0x205)

/**
 * \brief
 *
 * PHY Control. Data sent directly to the cfg_phy_control bus.
 * This is a GPIO register driving the values on the static cfg_phy_control
 * output signals, and does not in any way influence controller
 * functionality. It can be used for any static sideband control signaling
 * requirements that you have for your PHY. Usage of this register and the
 * associated GPIO bus is RESERVED when the controller is connected to a
 * Synopsys PHY.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_CONTROL_OFF . PHY_CONTROL
 */
#define  VTSS_F_PCIE_DBI_PHY_CONTROL_OFF_PHY_CONTROL(x)  (x)
#define  VTSS_M_PCIE_DBI_PHY_CONTROL_OFF_PHY_CONTROL     0xffffffff
#define  VTSS_X_PCIE_DBI_PHY_CONTROL_OFF_PHY_CONTROL(x)  (x)


/**
 * \brief This register controls the target map.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:TRGT_MAP_CTRL_OFF
 */
#define VTSS_PCIE_DBI_TRGT_MAP_CTRL_OFF      VTSS_IOREG(VTSS_TO_PCIE_DBI,0x207)

/**
 * \brief
 * Target Values for each BAR on the PF Function selected by the index
 * number. This register does not respect the Byte Enable setting, any
 * write will affect all register bits.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TRGT_MAP_CTRL_OFF . TARGET_MAP_PF
 */
#define  VTSS_F_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_PF(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_PF     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_PF(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Target Value for the ROM page of the PF Function selected by the index
 * number. This register does not respect the Byte Enable setting, any
 * write will affect all register bits.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TRGT_MAP_CTRL_OFF . TARGET_MAP_ROM
 */
#define  VTSS_F_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_ROM(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_ROM  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_ROM(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: R (sticky)
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TRGT_MAP_CTRL_OFF . TARGET_MAP_RESERVED_13_15
 */
#define  VTSS_F_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_RESERVED_13_15(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_RESERVED_13_15     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_RESERVED_13_15(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief
 * The number of the PF Function on which the Target Values are set. This
 * register does not respect the Byte Enable setting, any write will affect
 * all register bits.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TRGT_MAP_CTRL_OFF . TARGET_MAP_INDEX
 */
#define  VTSS_F_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_INDEX(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_INDEX     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_INDEX(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: RSVDP
 *  - Dbi: R (sticky)
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TRGT_MAP_CTRL_OFF . TARGET_MAP_RESERVED_21_31
 */
#define  VTSS_F_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_RESERVED_21_31(x)  VTSS_ENCODE_BITFIELD(x,21,11)
#define  VTSS_M_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_RESERVED_21_31     VTSS_ENCODE_BITMASK(21,11)
#define  VTSS_X_PCIE_DBI_TRGT_MAP_CTRL_OFF_TARGET_MAP_RESERVED_21_31(x)  VTSS_EXTRACT_BITFIELD(x,21,11)


/**
 * \brief This register enables you to disable dynamic clock gating. By default dynamic clock gating is on, allowing the controller to autonomously enable and disable its clocks. The clock gating is performed in the clock and reset module, DWC_pcie_clk_rst.v, and is initiated by the controllers clock enable signals. The following modules support dynamic clock gating:
 - AXI Bridge
 - RADM
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:CLOCK_GATING_CTRL_OFF
 */
#define VTSS_PCIE_DBI_CLOCK_GATING_CTRL_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x223)

/**
 * \brief
 * RADM Clock Gating Enable.
 * This register, if set, enables the RADM to autonomously enable and
 * disable its clock. The DWC_pcie_clk_rst.v module provides the gated
 * clock, radm_clk_g, to the RADM and is enabled when the controllers clock
 * enable signal, en_radm_clk_g, is asserted. The RADM clock is a gated
 * version of the controller clock, core_clk. The controller de-asserts
 * en_radm_clk_g when there is no Rx traffic, Rx queues and pre/post-queue
 * pipelines are empty, RADM completion LUT is empty, and there are no FLR
 * actions pending.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_CLOCK_GATING_CTRL_OFF . RADM_CLK_GATING_EN
 */
#define  VTSS_F_PCIE_DBI_CLOCK_GATING_CTRL_OFF_RADM_CLK_GATING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_CLOCK_GATING_CTRL_OFF_RADM_CLK_GATING_EN  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_CLOCK_GATING_CTRL_OFF_RADM_CLK_GATING_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * AXI Clock Gating Enable.
 * This register enables the AXI Bridge to autonomously enable and disable
 * the AXI Master clock, the AXI Slave clock and the AXI DBI slave clock.
 * The DWC_pcie_clk_rst.v module provides the gated clock,
 * mstr_axi_aclk_gated, to the AXI Bridge and is enabled when the
 * controllers clock enable signal, mstr_aclk_active, is asserted. For the
 * AXI Slave this module provides the gated clock, slv_axi_aclk_gated, to
 * the AXI Bridge and is enabled when the controllers clock enable signal,
 * slv_aclk_active, is asserted. If the AXI DBI Slave is enabled
 * (DBI_4SLAVE_POPULATED=1) the module provides the gated clock,
 * dbi_axi_aclk_gated, to the AXI Bridge and is enabled when the
 * controllers clock enable signal, dbi_aclk_active, is asserted. The
 * controller de-asserts the clock enable signals when the respective AXI
 * Master/Slave interfaces are idle.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_CLOCK_GATING_CTRL_OFF . AXI_CLK_GATING_EN
 */
#define  VTSS_F_PCIE_DBI_CLOCK_GATING_CTRL_OFF_AXI_CLK_GATING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_CLOCK_GATING_CTRL_OFF_AXI_CLK_GATING_EN  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_CLOCK_GATING_CTRL_OFF_AXI_CLK_GATING_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief There is no Gen3-specific N_FTS field. The N_FTS field in the "Link Width and Speed Change Control Register" is used for both Gen2 and Gen3 speed modes. There is no Gen3-specific "Directed Speed Change" field. The "Directed Speed Change" field in the "Link Width and Speed Change Control Register" is used to change to Gen2 or Gen3 speed. A speed change to Gen3 occurs if (1) the "Directed Speed Change" field is set to '1' and (2) the "Target Link Speed" field in the Link Control 2 Register is set to Gen3. Gen3 support is advertised by both sides of the link during link training.

 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:GEN3_RELATED_OFF
 */
#define VTSS_PCIE_DBI_GEN3_RELATED_OFF       VTSS_IOREG(VTSS_TO_PCIE_DBI,0x224)

/**
 * \brief
 * Gen3 Receiver Impedance ZRX-DC Not Compliant. Receivers that operate at
 * 8.0 GT/s with an impedance other than the range defined by the ZRX-DC
 * parameter for 2.5 GT/s (40-60 Ohms) must meet additional behavior
 * requirements in the following LTSSM states: Polling, Rx_L0s, L1, L2, and
 * Disabled.
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shared for Gen3
 * and Gen4/Gen5 data rates.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . GEN3_ZRXDC_NONCOMPL
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * If this bit is set to 1, the seed value of LFSR for scrambler at Gen3
 * rate does not change after LinkUp = 1. This bit takes effect only when
 * CX_AUTO_LANE_FLIP_CTRL_EN is supported. This feature requires both sides
 * of the link support it.
 *
 * Note: this register is shared for Gen3 and Gen4/Gen5 data rates.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . NO_SEED_VALUE_CHANGE
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_NO_SEED_VALUE_CHANGE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_NO_SEED_VALUE_CHANGE  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_NO_SEED_VALUE_CHANGE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Disable Scrambler for Gen3 and Gen4 Data Rate. The Gen3 and Gen4
 * scrambler/descrambler within the controller needs to be disabled when
 * the scrambling function is implemented outside of the controller (for
 * example within the PHY).
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shared for Gen3
 * and Gen4/Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . DISABLE_SCRAMBLER_GEN_3
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_DISABLE_SCRAMBLER_GEN_3(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_DISABLE_SCRAMBLER_GEN_3  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_DISABLE_SCRAMBLER_GEN_3(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Equalization Phase 2 and Phase 3 Disable. This applies to downstream
 * ports only.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate. If RATE_SHADOW_SEL==00b, this register
 * is for Gen3 data rate. If RATE_SHADOW_SEL==01b, this register is for
 * Gen4 data rate. If RATE_SHADOW_SEL==10b, this register is for Gen5 data
 * rate.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: see description
 *  - Dbi: see description
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . EQ_PHASE_2_3
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_EQ_PHASE_2_3(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_EQ_PHASE_2_3  VTSS_BIT(9)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_EQ_PHASE_2_3(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Equalization EIEOS Count Reset Disable. Disable requesting reset of
 * EIEOS count during equalization.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shared for Gen3
 * and Gen4/Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . EQ_EIEOS_CNT
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_EQ_EIEOS_CNT(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_EQ_EIEOS_CNT  VTSS_BIT(10)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_EQ_EIEOS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Equalization Redo Disable. Disable autonomous mechanism for requesting
 * to redo the equalization process. The received presets or coefficients
 * mismatch in Recovery.RcvrLock after Recovery EQ phases causes the EQ
 * redo requests. If the EQ redo is infinite or you do not want eq requests
 * and redo, setting this bit to 1 will stop the EQ requests and EQ redo so
 * that the link can go ahead to L0 state for packet trasmissions.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shared for Gen3
 * and Gen4/Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . EQ_REDO
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_EQ_REDO(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_EQ_REDO  VTSS_BIT(11)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_EQ_REDO(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Rx Equalization Phase 0/Phase 1 Hold Enable. When this bit is set the
 * upstream port holds phase 0 (the downstream port holds phase 1) for
 * 10ms. Holding phase 0 or phase 1 can be used to allow sufficient time
 * for Rx Equalization to be performed by the PHY. This bit is used during
 * Virtex-7 Gen3 equalization. The programmable bits [RXEQ_PH01_EN,
 * EQ_PHASE_2_3] can be used to obtain the following variations of the
 * equalization procedure:
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate. If RATE_SHADOW_SEL==00b, this register
 * is for Gen3 data rate. If RATE_SHADOW_SEL==01b, this register is for
 * Gen4 data rate. If RATE_SHADOW_SEL==10b, this register is for Gen5 data
 * rate.
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: see description
 *  - Dbi: see description
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . RXEQ_PH01_EN
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_RXEQ_PH01_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_RXEQ_PH01_EN  VTSS_BIT(12)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_RXEQ_PH01_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * When set to '1', the controller as Gen3 EQ master asserts RxEqEval to
 * instruct the PHY to do Rx adaptation and evaluation after a 500ns
 * timeout from a new preset request.
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate. If RATE_SHADOW_SEL==00b, this register
 * is for Gen3 data rate. If RATE_SHADOW_SEL==01b, this register is for
 * Gen4 data rate. If RATE_SHADOW_SEL==10b, this register is for Gen5 data
 * rate.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: see description
 *  - Dbi: see description
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . RXEQ_RGRDLESS_RXTS
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_RXEQ_RGRDLESS_RXTS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_RXEQ_RGRDLESS_RXTS  VTSS_BIT(13)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_RXEQ_RGRDLESS_RXTS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Equalization Disable. Disable equalization feature. This bit cannot be
 * changed once the LTSSM starts link training.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shared for Gen3
 * and Gen4/Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . GEN3_EQUALIZATION_DISABLE
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_GEN3_EQUALIZATION_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_GEN3_EQUALIZATION_DISABLE  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_GEN3_EQUALIZATION_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * DLLP Transmission Delay Disable. Disable delay transmission of DLLPs
 * before equalization.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shared for Gen3
 * and Gen4/Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . GEN3_DLLP_XMT_DELAY_DISABLE
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_GEN3_DLLP_XMT_DELAY_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_GEN3_DLLP_XMT_DELAY_DISABLE  VTSS_BIT(17)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_GEN3_DLLP_XMT_DELAY_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * DC Balance Disable. Disable DC Balance feature.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shared for Gen3
 * and Gen4/Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . GEN3_DC_BALANCE_DISABLE
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_GEN3_DC_BALANCE_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_GEN3_DC_BALANCE_DISABLE  VTSS_BIT(18)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_GEN3_DC_BALANCE_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Eq InvalidRequest and RxEqEval Different Time Assertion Disable. Disable
 * the assertion of Eq InvalidRequest and RxEqEval at different time.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shared for Gen3
 * and Gen4/Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_GEN3_RELATED_OFF . GEN3_EQ_INVREQ_EVAL_DIFF_DISABLE
 */
#define  VTSS_F_PCIE_DBI_GEN3_RELATED_OFF_GEN3_EQ_INVREQ_EVAL_DIFF_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PCIE_DBI_GEN3_RELATED_OFF_GEN3_EQ_INVREQ_EVAL_DIFF_DISABLE  VTSS_BIT(23)
#define  VTSS_X_PCIE_DBI_GEN3_RELATED_OFF_GEN3_EQ_INVREQ_EVAL_DIFF_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,23,1)


/**
 * \brief This register controls equalization for Phase2 in an upstream port (USP), or Phase3 in a downstream port (DSP).

 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:GEN3_EQ_CONTROL_OFF
 */
#define VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x22a)

/**
 * \brief
 * Feedback Mode.
 * Other values are reserved.
 * Note:
 *  - When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is a shadow register
 * for Gen3 and Gen4/Gen5 data rate.
 *  - If RATE_SHADOW_SEL==00b, this register is for Gen3 data rate.
 *  - If RATE_SHADOW_SEL==01b, this register is for Gen4 data rate.
 *  - If RATE_SHADOW_SEL==10b, this register is for Gen5 data rate.
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_EQ_FB_MODE
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FB_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FB_MODE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FB_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Behavior After 24 ms Timeout (when optimal settings are not found).
 *  For a USP: Determine next LTSSM state from Phase2 after 24ms Timeout
 *  - 0: Recovery.Speed
 *  - 1: Recovery.Equalization.Phase3
 * When optimal settings are not found then:
 *  - Equalization Phase 2 Successful status bit is not set in the "Link
 * Status Register 2" when GEN3_EQ_PHASE23_EXIT_MODE = 0
 *  - Equalization Phase 2 Successful status bit is set in the "Link Status
 * Register 2" when GEN3_EQ_PHASE23_EXIT_MODE = 1
 *  - Equalization Phase 2 Complete status bit is set in the "Link Status
 * Register 2"
 * For a DSP: Determine next LTSSM state from Phase3 after 24ms Timeout
 *  - 0: Recovery.Speed
 *  - 1: Recovery.Equalization.RcvrLock
 * When optimal settings are not found then:
 *  - Equalization Phase 3 Successful status bit is not set in the "Link
 * Status Register 2" when GEN3_EQ_PHASE23_EXIT_MODE = 0
 *  - Equalization Phase 3 Successful status bit is set in the "Link Status
 * Register 2" when GEN3_EQ_PHASE23_EXIT_MODE = 1
 *  - Equalization Phase 3 Complete status bit is set in the "Link Status
 * Register 2"
 * Note: GEN3_EQ_PHASE23_EXIT_MODE = 1 affects Direction Change feed back
 * mode. EQ requests for Figure Of Merit mode complete before 24ms timeout.
 * For more information, see GEN3_EQ_PSET_REQ_VEC Register.
 *
 * Note:
 *  - When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate.
 *  - If RATE_SHADOW_SEL==00b, this register is for Gen3 data rate.
 *  - If RATE_SHADOW_SEL==01b, this register is for Gen4 data rate.
 *  - If RATE_SHADOW_SEL==10b, this register is for Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_EQ_PHASE23_EXIT_MODE
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PHASE23_EXIT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PHASE23_EXIT_MODE  VTSS_BIT(4)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PHASE23_EXIT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Phase2_3 2 ms Timeout Disable. Determine behavior in Phase2 for USP
 * (Phase3 if DSP) when the PHY does not respond within 2ms to the
 * assertion of RxEqEval.
 * Note:
 *  - When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate.
 *  - If RATE_SHADOW_SEL==00b, this register is for Gen3 data rate.
 *  - If RATE_SHADOW_SEL==01b, this register is for Gen4 data rate.
 *  - If RATE_SHADOW_SEL==10b, this register is for Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_EQ_EVAL_2MS_DISABLE
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_EVAL_2MS_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_EVAL_2MS_DISABLE  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_EVAL_2MS_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Support EQ redo and lower rate change. To access this field,
 * RATE_SHADOW_SEL should be set to 0.
 * Note: Gen3 and Gen4 share the same register bit and have the same
 * feature.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_LOWER_RATE_EQ_REDO_ENABLE
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_LOWER_RATE_EQ_REDO_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_LOWER_RATE_EQ_REDO_ENABLE  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_LOWER_RATE_EQ_REDO_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Preset Request Vector. Requesting of Presets during the initial part of
 * the EQ Master Phase. Encoding scheme is as follows:
 *
 *  Bit [15:0] =0x0: No preset is requested and evaluated in EQ Master
 * Phase.
 *
 *  Bit [i] =1: "Preset=i" is requested and evaluated in EQ Master Phase.
 *  - 0x0000000000000000: No preset be requested and evaluated in EQ Master
 * Phase
 *  - 0x000000xxxxxxxxx1: Preset 0 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000000xxxxxxxx1x: Preset 1 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000000xxxxxxx1xx: Preset 2 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000000xxxxxx1xxx: Preset 3 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000000xxxxx1xxxx: Preset 4 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000000xxxx1xxxxx: Preset 5 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000000xxx1xxxxxx: Preset 6 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000000xx1xxxxxxx: Preset 7 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000000x1xxxxxxxx: Preset 8 is requested and evaluated in EQ Master
 * Phase
 *  - 0x00000x1xxxxxxxxx: Preset 9 is requested and evaluated in EQ Master
 * Phase
 *  - 0x000001xxxxxxxxxx: Preset 10 is requested and evaluated in EQ Master
 * Phase
 *  - All other encodings: Reserved
 * Note: You must contact your PHY vendor to ensure 24 ms timeout does not
 * occur in presets requests in EQ master phase, that is, you must set a
 * proper value to the GEN3_EQ_PSET_REQ_VEC register so that the EQ tunning
 * for Figure of Merit in the EQ master phase completes before 24 ms
 * timeout.
 * Note:
 *  - When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate.
 *  - If RATE_SHADOW_SEL==00b, this register is for Gen3 data rate.
 *  - If RATE_SHADOW_SEL==01b, this register is for Gen4 data rate.
 *  - If RATE_SHADOW_SEL==10b, this register is for Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_EQ_PSET_REQ_VEC
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_VEC(x)  VTSS_ENCODE_BITFIELD(x,8,16)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_VEC     VTSS_ENCODE_BITMASK(8,16)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_VEC(x)  VTSS_EXTRACT_BITFIELD(x,8,16)

/**
 * \brief
 * Include Initial FOM. Include or not the FOM feedback from the initial
 * preset evaluation performed in the EQ Master, when finding the highest
 * FOM among all preset evaluations.
 * Note:
 *  - When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate.
 *  - If RATE_SHADOW_SEL==00b, this register is for Gen3 data rate.
 *  - If RATE_SHADOW_SEL==01b, this register is for Gen4 data rate.
 *  - If RATE_SHADOW_SEL==10b, this register is for Gen5 data rate.
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_EQ_FOM_INC_INITIAL_EVAL
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FOM_INC_INITIAL_EVAL(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FOM_INC_INITIAL_EVAL  VTSS_BIT(24)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FOM_INC_INITIAL_EVAL(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * GEN3_EQ_PSET_REQ_AS_COEF is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_EQ_PSET_REQ_AS_COEF
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_AS_COEF(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_AS_COEF  VTSS_BIT(25)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_AS_COEF(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Request controller to send back-to-back EIEOS in Recovery.RcvrLock state
 * until presets to coefficients mapping is complete.
 * Note: Gen3 and Gen4 share the same register bit and have the same
 * feature.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_REQ_SEND_CONSEC_EIEOS_FOR_PSET_MAP
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_REQ_SEND_CONSEC_EIEOS_FOR_PSET_MAP(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_REQ_SEND_CONSEC_EIEOS_FOR_PSET_MAP  VTSS_BIT(26)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_REQ_SEND_CONSEC_EIEOS_FOR_PSET_MAP(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * The number of back-to-back equalization redo requests at a given Gen3,
 * Gen4 and Gen5 data rate for USP. After counting the EQ redo requests
 * which are equal to or larger than the number set, the USP stops any EQ
 * redo requests at the data rate. If changing speed, the USP controller
 * clears the counter to 0. Then re-start to count the requests after
 * changing speed back to the data rate for the USP.
 * Note: Gen3, Gen4 and Gen5 share the same register bits and have the same
 * feature.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h7:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_EQ_REQ_NUM
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_REQ_NUM(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_REQ_NUM     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_EQ_REQ_NUM(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/**
 * \brief
 * Support finite EQ requests for USP.
 * Note: Gen3, Gen4 and Gen5 share the same register bit and have the same
 * feature.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_CONTROL_OFF . GEN3_SUPPORT_FINITE_EQ_REQUEST
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_SUPPORT_FINITE_EQ_REQUEST(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_SUPPORT_FINITE_EQ_REQUEST  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_CONTROL_OFF_GEN3_SUPPORT_FINITE_EQ_REQUEST(x)  VTSS_EXTRACT_BITFIELD(x,30,1)


/**
 * \brief Equalization controls to be used in Phase2 (USP) or Phase 3 (DSP), when you set the Feedback Mode in "Gen3 EQ Control Register" to "Direction Change." These fields allow control over the initial starting point for the search of optimal coefficient settings, and allow control over the criteria used to determine when the optimal settings have been achieved. The values are applied to all the lanes.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:GEN3_EQ_FB_MODE_DIR_CHANGE_OFF
 */
#define VTSS_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x22b)

/**
 * \brief
 * Minimum Time (in ms) To Remain in EQ Master Phase. The LTSSM stays in EQ
 * Master phase for at least this amount of time, before starting to check
 * for convergence of the coefficients.
 * Allowed values 0,1,...,24.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate. If RATE_SHADOW_SEL==00b, this register
 * is for Gen3 data rate. If RATE_SHADOW_SEL==01b, this register is for
 * Gen4 data rate. If RATE_SHADOW_SEL==10b, this register is for Gen5 data
 * rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h18:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF . GEN3_EQ_FMDC_T_MIN_PHASE23
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_T_MIN_PHASE23(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_T_MIN_PHASE23     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_T_MIN_PHASE23(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Convergence Window Depth. Number of consecutive evaluations considered
 * in Phase 2/3 when determining if optimal coefficients have been found.
 * Allowed range: 0,1,2,..16 up to a maximum of CX_GEN3_EQ_COEFQ_DEPTH.
 *
 * When set to 0, EQ Master is performed without sending any requests to
 * the remote partner in Phase 2 for USP and Phase 3 for DSP. Therefore,
 * the remote partner will not change its transmitter coefficients and will
 * move to the next state.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate. If RATE_SHADOW_SEL==00b, this register
 * is for Gen3 data rate. If RATE_SHADOW_SEL==01b, this register is for
 * Gen4 data rate. If RATE_SHADOW_SEL==10b, this register is for Gen5 data
 * rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1f:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF . GEN3_EQ_FMDC_N_EVALS
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_N_EVALS(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_N_EVALS     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_N_EVALS(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/**
 * \brief
 * Convergence Window Aperture for C-1. Pre-cursor coefficients maximum
 * delta within the convergence window depth.
 * Allowed range: 0,1,2,..15.
 *
 * Note: When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate. If RATE_SHADOW_SEL==00b, this register
 * is for Gen3 data rate. If RATE_SHADOW_SEL==01b, this register is for
 * Gen4 data rate. If RATE_SHADOW_SEL==10b, this register is for Gen5 data
 * rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hf:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF . GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \brief
 * Convergence Window Aperture for C+1. Post-cursor coefficients maximum
 * delta within the convergence window depth. Allowed range: 0,1,2,..15.
 *
 * Note:
 *  - When CX_GEN4_SPEED/CX_GEN5_SPEED, this register is shadow register
 * for Gen3 and Gen4/Gen5 data rate.
 *  - If RATE_SHADOW_SEL==00b, this register is for Gen3 data rate.
 *  - If RATE_SHADOW_SEL==01b, this register is for Gen4 data rate.
 *  - If RATE_SHADOW_SEL==10b, this register is for Gen5 data rate.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hf:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF . GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA
 */
#define  VTSS_F_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA(x)  VTSS_ENCODE_BITFIELD(x,14,4)
#define  VTSS_M_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA     VTSS_ENCODE_BITMASK(14,4)
#define  VTSS_X_PCIE_DBI_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA(x)  VTSS_EXTRACT_BITFIELD(x,14,4)


/**
 * \brief This register controls the order rule.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:ORDER_RULE_CTRL_OFF
 */
#define VTSS_PCIE_DBI_ORDER_RULE_CTRL_OFF    VTSS_IOREG(VTSS_TO_PCIE_DBI,0x22d)

/**
 * \brief
 * Non-Posted Passing Posted Ordering Rule Control.
 *
 *  Determines if NP can pass halted P queue.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_ORDER_RULE_CTRL_OFF . NP_PASS_P
 */
#define  VTSS_F_PCIE_DBI_ORDER_RULE_CTRL_OFF_NP_PASS_P(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_ORDER_RULE_CTRL_OFF_NP_PASS_P     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_ORDER_RULE_CTRL_OFF_NP_PASS_P(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Completion Passing Posted Ordering Rule Control.
 *
 *  Determines if CPL can pass halted P queue.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_ORDER_RULE_CTRL_OFF . CPL_PASS_P
 */
#define  VTSS_F_PCIE_DBI_ORDER_RULE_CTRL_OFF_CPL_PASS_P(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_ORDER_RULE_CTRL_OFF_CPL_PASS_P     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_ORDER_RULE_CTRL_OFF_CPL_PASS_P(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/**
 * \brief This register controls the PIPE Loopback.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PIPE_LOOPBACK_CONTROL_OFF
 */
#define VTSS_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x22e)

/**
 * \brief
 * LPBK_RXVALID is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF . LPBK_RXVALID
 */
#define  VTSS_F_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_LPBK_RXVALID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_LPBK_RXVALID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_LPBK_RXVALID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * RXSTATUS_LANE is an internally reserved field. Do not use.
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF . RXSTATUS_LANE
 */
#define  VTSS_F_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_LANE(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_LANE     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_LANE(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * RXSTATUS_VALUE is an internally reserved field. Do not use.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF . RXSTATUS_VALUE
 */
#define  VTSS_F_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_VALUE(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_VALUE     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/**
 * \brief
 * PIPE Loopback Enable.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF . PIPE_LOOPBACK
 */
#define  VTSS_F_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_PIPE_LOOPBACK(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_PIPE_LOOPBACK  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_PIPE_LOOPBACK_CONTROL_OFF_PIPE_LOOPBACK(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief This is the DBI Read-Only write enable register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:MISC_CONTROL_1_OFF
 */
#define VTSS_PCIE_DBI_MISC_CONTROL_1_OFF     VTSS_IOREG(VTSS_TO_PCIE_DBI,0x22f)

/**
 * \brief
 * Write to RO Registers Using DBI.
 * For more information, see "Writing to Read-Only Registers" in "Register
 * Module, LBC, and DBI" section in the "Controller Operations" chapter of
 * the Databook.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . DBI_RO_WR_EN
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_DBI_RO_WR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_DBI_RO_WR_EN  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_DBI_RO_WR_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Default target for an IO or MEM request with UR/CA/CRS received. Based
 * on the value of this field the controller either drops or forwards these
 * requests to your application.
 * For more information, see "ECRC Handling" and "Request TLP Routing
 * Rules" in "Receive Routing" section of the "Controller Operations"
 * chapter of the Databook.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . DEFAULT_TARGET
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_DEFAULT_TARGET(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_DEFAULT_TARGET  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_DEFAULT_TARGET(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this field is set to '1', the controller suppresses error logging,
 * error message generation, and CPL generation for non-posted requests
 * TLPs (with UR filtering status) forwarded to your application (that is,
 * when DEFAULT_TARGET =1). For more information, see "Advanced Error
 * Handling For Received TLPs" chapter of the Databook.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . UR_CA_MASK_4_TRGT1
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_UR_CA_MASK_4_TRGT1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_UR_CA_MASK_4_TRGT1  VTSS_BIT(2)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_UR_CA_MASK_4_TRGT1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enables Simplified Replay Timer (Gen4). For more information, see
 * "Transmit Replay" in "Transmit TLP Processing" section in the
 * "Controller Operations" chapter of the Databook.
 * Simplified Replay Timer can have the following Values:
 *  - A value from 24,000 to 31,000 Symbol Times when Extended Synch is 0b.
 *  - A value from 80,000 to 100,000 Symbol Times when Extended Synch is
 * 1b.
 * The Simplified Replay Timer value must not be changed while the link is
 * in use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . SIMPLIFIED_REPLAY_TIMER
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_SIMPLIFIED_REPLAY_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_SIMPLIFIED_REPLAY_TIMER  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_SIMPLIFIED_REPLAY_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * When ARI is enabled, this field enables use of the device ID.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . ARI_DEVICE_NUMBER
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_ARI_DEVICE_NUMBER(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_ARI_DEVICE_NUMBER  VTSS_BIT(5)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_ARI_DEVICE_NUMBER(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * This field enables the Completion Queue Management feature.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . CPLQ_MNG_EN
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_CPLQ_MNG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_CPLQ_MNG_EN  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_CPLQ_MNG_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Setting of this field defines how to decide the destination of
 * Configuration requests.
 * Note: When app_req_retry_en is asserted, the setting of this field is
 * ignored.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . CFG_TLP_BYPASS_EN_REG
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_CFG_TLP_BYPASS_EN_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_CFG_TLP_BYPASS_EN_REG  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_CFG_TLP_BYPASS_EN_REG(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Configuration requests are directed either to CDM or ELBI/RTRGT1 based
 * on the value of this field.
 *  - Configuration requests with an address less CONFIG_LIMIT_REG are
 * directed to the CDM
 *  - Configuration requests with an address greater than CONFIG_LIMIT_REG
 * are directed to either ELBI or TRGT1 interface based on the setting of
 * TARGET_ABOVE_CONFIG_LIMIT_REG field.
 * Your application must set a proper value for this field based on your
 * extended configuration registers. For more information, see the
 * "CDM/ELBI Register Space Access Through CFG Request" in "Register
 * Module, LBC, and DBI" section in the "Controller Operations" chapter of
 * the Databook.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . CONFIG_LIMIT_REG
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_CONFIG_LIMIT_REG(x)  VTSS_ENCODE_BITFIELD(x,8,10)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_CONFIG_LIMIT_REG     VTSS_ENCODE_BITMASK(8,10)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_CONFIG_LIMIT_REG(x)  VTSS_EXTRACT_BITFIELD(x,8,10)

/**
 * \brief
 * Configuration requests with an address greater than CONFIG_LIMIT_REG are
 * directed to either ELBI or TRGT1 interface based on the setting of this
 * field. This field can have the following values:
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h2:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . TARGET_ABOVE_CONFIG_LIMIT_REG
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_TARGET_ABOVE_CONFIG_LIMIT_REG(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_TARGET_ABOVE_CONFIG_LIMIT_REG     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_TARGET_ABOVE_CONFIG_LIMIT_REG(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * Determines whether to track completion of transmitted Non-Posted TLPs in
 * P2P mode.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . P2P_TRACK_CPL_TO_REG
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_P2P_TRACK_CPL_TO_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_P2P_TRACK_CPL_TO_REG  VTSS_BIT(20)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_P2P_TRACK_CPL_TO_REG(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Determines whether to enable Peer to Peer (P2P) error reporting.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . P2P_ERR_RPT_CTRL
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_P2P_ERR_RPT_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_P2P_ERR_RPT_CTRL  VTSS_BIT(21)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_P2P_ERR_RPT_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Disable port logic register write from wire side.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MISC_CONTROL_1_OFF . PORT_LOGIC_WR_DISABLE
 */
#define  VTSS_F_PCIE_DBI_MISC_CONTROL_1_OFF_PORT_LOGIC_WR_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PCIE_DBI_MISC_CONTROL_1_OFF_PORT_LOGIC_WR_DISABLE  VTSS_BIT(22)
#define  VTSS_X_PCIE_DBI_MISC_CONTROL_1_OFF_PORT_LOGIC_WR_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,22,1)


/**
 * \brief Used when upsizing or downsizing the link width through Configuration state without bringing the link down.
For more information, see the "Link Establishment" section in the "Controller
Operations" chapter of the Databook.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:MULTI_LANE_CONTROL_OFF
 */
#define VTSS_PCIE_DBI_MULTI_LANE_CONTROL_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x230)

/**
 * \brief
 * Target Link Width.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h10:
 * 'h2:
 * 'h20:
 * 'h4:
 * 'h8:

 *
 * Field: ::VTSS_PCIE_DBI_MULTI_LANE_CONTROL_OFF . TARGET_LINK_WIDTH
 */
#define  VTSS_F_PCIE_DBI_MULTI_LANE_CONTROL_OFF_TARGET_LINK_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_PCIE_DBI_MULTI_LANE_CONTROL_OFF_TARGET_LINK_WIDTH     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_PCIE_DBI_MULTI_LANE_CONTROL_OFF_TARGET_LINK_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Directed Link Width Change.
 *  - If the upconfigure_capable variable is '1' and the
 * PCIE_CAP_HW_AUTO_WIDTH_DISABLE bit in LINK_CONTROL_LINK_STATUS_REG is
 * '0', the controller starts upconfigure or autonomous width downsizing
 * (to the TARGET_LINK_WIDTH value) in the Configuration state.
 *  - If TARGET_LINK_WIDTH value is 0x0, the controller does not start
 * upconfigure or autonomous width downsizing in the Configuration state.
 * The controller self-clears this field when the controller accepts this
 * request.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W
 *  - Dbi: R/W
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MULTI_LANE_CONTROL_OFF . DIRECT_LINK_WIDTH_CHANGE
 */
#define  VTSS_F_PCIE_DBI_MULTI_LANE_CONTROL_OFF_DIRECT_LINK_WIDTH_CHANGE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_DBI_MULTI_LANE_CONTROL_OFF_DIRECT_LINK_WIDTH_CHANGE  VTSS_BIT(6)
#define  VTSS_X_PCIE_DBI_MULTI_LANE_CONTROL_OFF_DIRECT_LINK_WIDTH_CHANGE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Upconfigure Support.
 * The controller sends this value as the Link Upconfigure Capability in
 * TS2 Ordered Sets in Configuration.Complete state.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MULTI_LANE_CONTROL_OFF . UPCONFIGURE_SUPPORT
 */
#define  VTSS_F_PCIE_DBI_MULTI_LANE_CONTROL_OFF_UPCONFIGURE_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_MULTI_LANE_CONTROL_OFF_UPCONFIGURE_SUPPORT  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_MULTI_LANE_CONTROL_OFF_UPCONFIGURE_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief This register controls controller PHY dependent behavior.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PHY_INTEROP_CTRL_OFF
 */
#define VTSS_PCIE_DBI_PHY_INTEROP_CTRL_OFF   VTSS_IOREG(VTSS_TO_PCIE_DBI,0x231)

/**
 * \brief
 * Rxstandby Control. Bits 0..5 determine if the controller asserts the
 * RxStandby signal (mac_phy_rxstandby) in the indicated condition. Bit 6
 * enables the controller to perform the RxStandby/RxStandbyStatus
 * handshake.
 *
 * This field is reserved for internal use.
 *
 * You should not write to this field and change the default unless
 * specifically instructed by Synopsys support.
 *  - [0]: Rx EIOS and subsequent T TX-IDLE-MIN
 *  - [1]: Rate Change
 *  - [2]: Inactive lane for upconfigure/downconfigure
 *  - [3]: PowerDown=P1orP2
 *  - [4]: RxL0s.Idle
 *  - [5]: EI Infer in L0
 *  - [6]: Execute RxStandby/RxStandbyStatus Handshake
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h7f:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_INTEROP_CTRL_OFF . RXSTANDBY_CONTROL
 */
#define  VTSS_F_PCIE_DBI_PHY_INTEROP_CTRL_OFF_RXSTANDBY_CONTROL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_PCIE_DBI_PHY_INTEROP_CTRL_OFF_RXSTANDBY_CONTROL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_PCIE_DBI_PHY_INTEROP_CTRL_OFF_RXSTANDBY_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * \brief
 * L1 entry control bit.
 *
 * This field is reserved for internal use.
 *
 * You should not write to this field and change the default unless
 * specifically instructed by Synopsys support.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R/W (sticky)
 *  - Dbi: R/W (sticky)
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_INTEROP_CTRL_OFF . L1_NOWAIT_P1
 */
#define  VTSS_F_PCIE_DBI_PHY_INTEROP_CTRL_OFF_L1_NOWAIT_P1(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCIE_DBI_PHY_INTEROP_CTRL_OFF_L1_NOWAIT_P1  VTSS_BIT(9)
#define  VTSS_X_PCIE_DBI_PHY_INTEROP_CTRL_OFF_L1_NOWAIT_P1(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * L1 Clock control bit.
 *
 * This field is reserved for internal use.
 *
 * You should not write to this field and change the default unless
 * specifically instructed by Synopsys support.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_INTEROP_CTRL_OFF . L1_CLK_SEL
 */
#define  VTSS_F_PCIE_DBI_PHY_INTEROP_CTRL_OFF_L1_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_DBI_PHY_INTEROP_CTRL_OFF_L1_CLK_SEL  VTSS_BIT(10)
#define  VTSS_X_PCIE_DBI_PHY_INTEROP_CTRL_OFF_L1_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Control the duration of the PHY reset (PIPE and PMA). Duration is in aux
 * clock cycles (0 to 262,142).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3ffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_INTEROP_CTRL_OFF . PHY_RST_TIMER
 */
#define  VTSS_F_PCIE_DBI_PHY_INTEROP_CTRL_OFF_PHY_RST_TIMER(x)  VTSS_ENCODE_BITFIELD(x,12,18)
#define  VTSS_M_PCIE_DBI_PHY_INTEROP_CTRL_OFF_PHY_RST_TIMER     VTSS_ENCODE_BITMASK(12,18)
#define  VTSS_X_PCIE_DBI_PHY_INTEROP_CTRL_OFF_PHY_RST_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,12,18)

/**
 * \brief
 * Control whether the Power Management Controller will drive
 * pm_req_phy_perst during a Warm Reset (PERST# assertion without cycling
 * of power).
 *
 * Note: This register field is sticky.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_INTEROP_CTRL_OFF . PHY_PERST_ON_WARM_RESET
 */
#define  VTSS_F_PCIE_DBI_PHY_INTEROP_CTRL_OFF_PHY_PERST_ON_WARM_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PCIE_DBI_PHY_INTEROP_CTRL_OFF_PHY_PERST_ON_WARM_RESET  VTSS_BIT(30)
#define  VTSS_X_PCIE_DBI_PHY_INTEROP_CTRL_OFF_PHY_PERST_ON_WARM_RESET(x)  VTSS_EXTRACT_BITFIELD(x,30,1)


/**
 * \brief Using this register you can delete one entry in the target completion LUT. You should only use this register when you know that your application will never send the completion because of an FLR or any other reason.

Note:: The target completion LUT (and associated target completion timeout event) is watching for completions (from your application on XALI0/1/2 or AXI master read channel) corresponding to previously received non-posted requests from the PCIe wire.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:TRGT_CPL_LUT_DELETE_ENTRY_OFF
 */
#define VTSS_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x232)

/**
 * \brief
 * This number selects one entry to delete of the TRGT_CPL_LUT.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF . LOOK_UP_ID
 */
#define  VTSS_F_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF_LOOK_UP_ID(x)  VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF_LOOK_UP_ID     VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF_LOOK_UP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,31)

/**
 * \brief
 * This is a one-shot bit.
 * This is a self-clearing register field. Reading from this register field
 * always returns a '0'.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF . DELETE_EN
 */
#define  VTSS_F_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF_DELETE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF_DELETE_EN  VTSS_BIT(31)
#define  VTSS_X_PCIE_DBI_TRGT_CPL_LUT_DELETE_ENTRY_OFF_DELETE_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief This register controls link reset request flush behaviour.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:LINK_FLUSH_CONTROL_OFF
 */
#define VTSS_PCIE_DBI_LINK_FLUSH_CONTROL_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x233)

/**
 * \brief
 * Enables automatic flushing of pending requests before sending the reset
 * request to the application logic to reset the PCIe controller and the
 * AXI Bridge.
 * The flushing process is initiated if any of the following events occur:
 *  - Hot reset request. A downstream port (DSP) can "hot reset" an
 * upstream port (USP) by sending two consecutive TS1 ordered sets with the
 * hot reset bit asserted.
 *  - Warm (Soft) reset request. Generated when exiting from D3 to D0 and
 * cfg_pm_no_soft_rst=0.
 *  - Link down reset request. A high to low transition on smlh_req_rst_not
 * indicates the link has gone down and the controller is requesting a
 * reset.
 * If you disable automatic flushing, your application is responsible for
 * resetting the PCIe controller and the AXI Bridge. For more information
 * see "Warm and Hot Resets" section in the Architecture chapter of the
 * Databook.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_LINK_FLUSH_CONTROL_OFF . AUTO_FLUSH_EN
 */
#define  VTSS_F_PCIE_DBI_LINK_FLUSH_CONTROL_OFF_AUTO_FLUSH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_LINK_FLUSH_CONTROL_OFF_AUTO_FLUSH_EN  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_LINK_FLUSH_CONTROL_OFF_AUTO_FLUSH_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * This is an internally reserved field. Do not use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_LINK_FLUSH_CONTROL_OFF . RSVD_I_8
 */
#define  VTSS_F_PCIE_DBI_LINK_FLUSH_CONTROL_OFF_RSVD_I_8(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCIE_DBI_LINK_FLUSH_CONTROL_OFF_RSVD_I_8     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCIE_DBI_LINK_FLUSH_CONTROL_OFF_RSVD_I_8(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief This register holds the AXI bridge slave error responses.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:AMBA_ERROR_RESPONSE_DEFAULT_OFF
 */
#define VTSS_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x234)

/**
 * \brief
 * Global Slave Error Response Mapping. Determines the AXI slave response
 * for all error scenarios on non-posted requests. For more information see
 * "Error Handling" in the AXI chapter of the Databook.
 * The error response mapping is not applicable to Non-existent Vendor ID
 * register reads.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF . AMBA_ERROR_RESPONSE_GLOBAL
 */
#define  VTSS_F_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_GLOBAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_GLOBAL  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_GLOBAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Vendor ID Non-existent Slave Error Response Mapping. Determines the AXI
 * slave response for errors on reads to non-existent Vendor ID register.
 * For more information see "Error Handling" in the AXI chapter of the
 * Databook.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF . AMBA_ERROR_RESPONSE_VENDORID
 */
#define  VTSS_F_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_VENDORID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_VENDORID  VTSS_BIT(2)
#define  VTSS_X_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_VENDORID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CRS Slave Error Response Mapping. Determines the AXI slave response for
 * CRS completions. For more information see "Error Handling" in the AXI
 * chapter of the Databook.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF . AMBA_ERROR_RESPONSE_CRS
 */
#define  VTSS_F_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_CRS(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_CRS     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_CRS(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * AXI Slave Response Error Map. Allows you to selectively map the errors
 * received from the PCIe completion (for non-posted requests) to the AXI
 * slave responses, slv_rresp or slv_bresp. The recommended setting is
 * SLVERR. CRS is always mapped to OKAY.
 *  - 0
 *  -- 0x0: UR (unsupported request) -> DECERR
 *  -- 0x1: UR (unsupported request) -> SLVERR
 *  - 1
 *  -- 0x0: CRS (configuration retry status) -> DECERR
 *  -- 0x1: CRS (configuration retry status) -> SLVERR
 *  - 2
 *  -- 0x0: CA (completer abort) -> DECERR
 *  -- 0x1: CA (completer abort) -> SLVERR
 *  - 3: RESERVED (0x0)
 *  - 4: RESERVED (0x0)
 *  - 5
 *  -- 0x0: Completion Timeout -> DECERR
 *  -- 0x1: Completion Timeout -> SLVERR. The AXI bridge internally drops
 * (processes internally but not passed to your application) a completion
 * that has been marked by the Rx filter as UC or MLF, and does not pass
 * its status directly down to the slave interface. It waits for a timeout
 * and then signals "Completion Timeout" to the slave interface.
 * The controller sets the AXI slave read databus to 0xFFFF for all error
 * responses.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3f:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF . AMBA_ERROR_RESPONSE_MAP
 */
#define  VTSS_F_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_MAP(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_MAP     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_PCIE_DBI_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_MAP(x)  VTSS_EXTRACT_BITFIELD(x,10,6)


/**
 * \brief If your application AXI master issues outbound requests to the AXI bridge slave interface before the PCIe link is operational, the controller starts a "flush" timer. The timeout value of the timer is set by this register. If the timer times out before the PCIe link is operational, the bridge TX request queues are flushed. For more information, see the "AXI Bridge Initialization, Clocking and Reset" section in the AXI chapter of the Databook.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:AMBA_LINK_TIMEOUT_OFF
 */
#define VTSS_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x235)

/**
 * \brief
 * Timeout Value (ms). The timer will timeout and then flush the bridge TX
 * request queues after this amount of time. The timer counts when there
 * are pending outbound AXI slave interface requests and the PCIe TX link
 * is not transmitting any of these requests.
 * The timer is clocked by core_clk.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF . LINK_TIMEOUT_PERIOD_DEFAULT
 */
#define  VTSS_F_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_PERIOD_DEFAULT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_PERIOD_DEFAULT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_PERIOD_DEFAULT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Disable Flush.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF . LINK_TIMEOUT_ENABLE_DEFAULT
 */
#define  VTSS_F_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_ENABLE_DEFAULT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_ENABLE_DEFAULT  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_ENABLE_DEFAULT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief This register controls the AXI Bridge Ordering.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:AMBA_ORDERING_CTRL_OFF
 */
#define VTSS_PCIE_DBI_AMBA_ORDERING_CTRL_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x236)

/**
 * \brief
 * AXI Serialize Non-Posted Requests Enable. This field enables the AXI
 * Bridge to serialize same ID Non-Posted Read/Write Requests on the wire.
 * Serialization implies one outstanding same ID NP Read or Write on the
 * wire and used to avoid AXI RAR and WAW hazards at the remote link
 * partner. For more information, see the "Optional Serialization of AXI
 * Slave Non-posted Requests" section in the AXI chapter of the Databook.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_AMBA_ORDERING_CTRL_OFF . AX_SNP_EN
 */
#define  VTSS_F_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_SNP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_SNP_EN  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_SNP_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * AXI Master Posted Ordering Event Selector.
 *
 *  This field selects how the master interface determines when a P write
 * is completed when enforcing the PCIe ordering rule, "NP must not pass P"
 * at the AXI Master Interface.
 * The AXI protocol does not support ordering between channels. Therefore,
 * NP reads can pass P on your AXI bus fabric. This can result in an
 * ordering violation when the read overtakes a P that is going to the same
 * address. Therefore, the bridge master does not issue any NP requests
 * until all outstanding P writes reach their destination. It does this by
 * waiting for the all of the write responses on the B channel. This can
 * affect the performance of the master read channel.
 * For scenarios where the interconnect serializes the AXI master "AW", "W"
 * and "AR" channels,you can increase the performance by reducing the need
 * to wait until the complete Posted transaction has effectively reached
 * the application slave.
 *
 * Note: This setting will not affect:
 *  - MSI interrupt catcher and P data ordering. This is always driven by
 * the B'last event.
 *  - DMA read engine TLP ordering. This is always driven by the B'last
 * event.
 *  - NP write transactions which are always serialized with P write
 * transactions.
 *
 * \details
 * 'h1:
 * 'h0:
 * 'h3:
 * 'h2:

 *
 * Field: ::VTSS_PCIE_DBI_AMBA_ORDERING_CTRL_OFF . AX_MSTR_ORDR_P_EVENT_SEL
 */
#define  VTSS_F_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_MSTR_ORDR_P_EVENT_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_MSTR_ORDR_P_EVENT_SEL     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_MSTR_ORDR_P_EVENT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * AXI Master Zero Length Read Forward to the application.
 *
 * The DW PCIe controller AXI bridge is able to terminate in order with the
 * Posted transactions the zero length read, implementing the PCIe express
 * flush semantics of the Posted transactions.

 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_AMBA_ORDERING_CTRL_OFF . AX_MSTR_ZEROLREAD_FW
 */
#define  VTSS_F_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_MSTR_ZEROLREAD_FW(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_MSTR_ZEROLREAD_FW  VTSS_BIT(7)
#define  VTSS_X_PCIE_DBI_AMBA_ORDERING_CTRL_OFF_AX_MSTR_ZEROLREAD_FW(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief This register controls the cache coherency operation.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:COHERENCY_CONTROL_1_OFF
 */
#define VTSS_PCIE_DBI_COHERENCY_CONTROL_1_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x238)

/**
 * \brief
 * Sets the memory type for the lower and upper parts of the address space:
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_COHERENCY_CONTROL_1_OFF . CFG_MEMTYPE_VALUE
 */
#define  VTSS_F_PCIE_DBI_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_VALUE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_VALUE  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Boundary Lower Address For Memory Type. Bits [31:0] of dword-aligned
 * address of the boundary for Memory type. The two lower address LSBs are
 * '00'. Addresses up to but not including this value are in the lower
 * address space region; addresses equal or greater than this value are in
 * the upper address space region.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_COHERENCY_CONTROL_1_OFF . CFG_MEMTYPE_BOUNDARY_LOW_ADDR
 */
#define  VTSS_F_PCIE_DBI_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_BOUNDARY_LOW_ADDR(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_PCIE_DBI_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_BOUNDARY_LOW_ADDR     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_PCIE_DBI_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_BOUNDARY_LOW_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief This register controls the cache coherency operation.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:COHERENCY_CONTROL_3_OFF
 */
#define VTSS_PCIE_DBI_COHERENCY_CONTROL_3_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x23a)

/**
 * \brief
 * Master Read CACHE Signal Behavior.
 * Defines how the individual bits in mstr_arcache are controlled.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_COHERENCY_CONTROL_3_OFF . CFG_MSTR_ARCACHE_MODE
 */
#define  VTSS_F_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_MODE(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_MODE     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/**
 * \brief
 * Master Write CACHE Signal Behavior.
 * Defines how the individual bits in mstr_awcache are controlled.
 *
 * Note: for message requests the value of mstr_awcache is always "0000"
 * regardless of the value of this bit.
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_COHERENCY_CONTROL_3_OFF . CFG_MSTR_AWCACHE_MODE
 */
#define  VTSS_F_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_MODE(x)  VTSS_ENCODE_BITFIELD(x,11,4)
#define  VTSS_M_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_MODE     VTSS_ENCODE_BITMASK(11,4)
#define  VTSS_X_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,4)

/**
 * \brief
 * Master Read CACHE Signal Value.
 * Value of the individual bits in mstr_arcache when CFG_MSTR_ARCACHE_MODE
 * is '1'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_COHERENCY_CONTROL_3_OFF . CFG_MSTR_ARCACHE_VALUE
 */
#define  VTSS_F_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_VALUE(x)  VTSS_ENCODE_BITFIELD(x,19,4)
#define  VTSS_M_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_VALUE     VTSS_ENCODE_BITMASK(19,4)
#define  VTSS_X_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,19,4)

/**
 * \brief
 * Master Write CACHE Signal Value.
 * Value of the individual bits in mstr_awcache when CFG_MSTR_AWCACHE_MODE
 * is '1'.
 *
 * Note: Not applicable to message requests; for message requests the value
 * of mstr_awcache is always '0000'.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_COHERENCY_CONTROL_3_OFF . CFG_MSTR_AWCACHE_VALUE
 */
#define  VTSS_F_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_VALUE(x)  VTSS_ENCODE_BITFIELD(x,27,4)
#define  VTSS_M_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_VALUE     VTSS_ENCODE_BITMASK(27,4)
#define  VTSS_X_PCIE_DBI_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,27,4)


/**
 * \brief Lower 20 bits of the programmable AXI address to which Messages coming from wire are mapped. Bits [11:0] of the register are tied to zero for the address to be 4k-aligned. In previous releases, the third and fourth DWORDs of a message (Msg/MsgD) TLP header were delivered though the AXI master address bus (mstr_awaddr). These DWORDS are now supplied through the mstr_awmisc_info_hdr_34dw[63:0] output; and the value on mstr_awaddr is driven to the value you have programmed into the AXI_MSTR_MSG_ADDR_LOW_OFF and AXI_MSTR_MSG_ADDR_HIGH_OFF registers.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:AXI_MSTR_MSG_ADDR_LOW_OFF
 */
#define VTSS_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x23c)

/**
 * \brief
 * Reserved for future use.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF . CFG_AXIMSTR_MSG_ADDR_LOW_RESERVED
 */
#define  VTSS_F_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF_CFG_AXIMSTR_MSG_ADDR_LOW_RESERVED(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF_CFG_AXIMSTR_MSG_ADDR_LOW_RESERVED     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF_CFG_AXIMSTR_MSG_ADDR_LOW_RESERVED(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Lower 20-bits of the programmable AXI address for Messages.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF . CFG_AXIMSTR_MSG_ADDR_LOW
 */
#define  VTSS_F_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF_CFG_AXIMSTR_MSG_ADDR_LOW(x)  VTSS_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF_CFG_AXIMSTR_MSG_ADDR_LOW     VTSS_ENCODE_BITMASK(12,20)
#define  VTSS_X_PCIE_DBI_AXI_MSTR_MSG_ADDR_LOW_OFF_CFG_AXIMSTR_MSG_ADDR_LOW(x)  VTSS_EXTRACT_BITFIELD(x,12,20)


/**
 * \brief Upper 32 bits of the programmable AXI address to which Messages coming from wire are mapped.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:AXI_MSTR_MSG_ADDR_HIGH_OFF
 */
#define VTSS_PCIE_DBI_AXI_MSTR_MSG_ADDR_HIGH_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x23d)

/**
 * \brief
 * Upper 32 bits of the programmable AXI address for Messages.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_AXI_MSTR_MSG_ADDR_HIGH_OFF . CFG_AXIMSTR_MSG_ADDR_HIGH
 */
#define  VTSS_F_PCIE_DBI_AXI_MSTR_MSG_ADDR_HIGH_OFF_CFG_AXIMSTR_MSG_ADDR_HIGH(x)  (x)
#define  VTSS_M_PCIE_DBI_AXI_MSTR_MSG_ADDR_HIGH_OFF_CFG_AXIMSTR_MSG_ADDR_HIGH     0xffffffff
#define  VTSS_X_PCIE_DBI_AXI_MSTR_MSG_ADDR_HIGH_OFF_CFG_AXIMSTR_MSG_ADDR_HIGH(x)  (x)


/**
 * \brief The version number is given in hex format. You should convert each pair of hex characters to ASCII to interpret.

Using 4.70a (GA) as an example:
 - VERSION_NUMBER = 0x3437302a which translates to 470*
 - VERSION_TYPE = 0x67612a2a which translates to ga**
Using 4.70a-ea01 as an example:
 - VERSION_NUMBER = 0x3437302a which translates to 470*
 - VERSION_TYPE = 0x65613031 which translates to ea01
GA is a general release available on www.designware.com

EA is an early release available on a per-customer basis.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PCIE_VERSION_NUMBER_OFF
 */
#define VTSS_PCIE_DBI_PCIE_VERSION_NUMBER_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x23e)

/**
 * \brief
 * Version Number.

 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PCIE_VERSION_NUMBER_OFF . VERSION_NUMBER
 */
#define  VTSS_F_PCIE_DBI_PCIE_VERSION_NUMBER_OFF_VERSION_NUMBER(x)  (x)
#define  VTSS_M_PCIE_DBI_PCIE_VERSION_NUMBER_OFF_VERSION_NUMBER     0xffffffff
#define  VTSS_X_PCIE_DBI_PCIE_VERSION_NUMBER_OFF_VERSION_NUMBER(x)  (x)


/**
 * \brief The type is given in hex format. You should convert each pair of hex characters to ASCII to interpret.

Using 4.70a (GA) as an example:
 - VERSION_NUMBER = 0x3437302a which translates to 470*
 - VERSION_TYPE = 0x67612a2a which translates to ga**
Using 4.70a-ea01 as an example:
 - VERSION_NUMBER = 0x3437302a which translates to 470*
 - VERSION_TYPE = 0x65613031 which translates to ea01
GA is a general release available on www.designware.com

EA is an early release available on a per-customer basis.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PCIE_VERSION_TYPE_OFF
 */
#define VTSS_PCIE_DBI_PCIE_VERSION_TYPE_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x23f)

/**
 * \brief
 * Version Type.

 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PCIE_VERSION_TYPE_OFF . VERSION_TYPE
 */
#define  VTSS_F_PCIE_DBI_PCIE_VERSION_TYPE_OFF_VERSION_TYPE(x)  (x)
#define  VTSS_M_PCIE_DBI_PCIE_VERSION_TYPE_OFF_VERSION_TYPE     0xffffffff
#define  VTSS_X_PCIE_DBI_PCIE_VERSION_TYPE_OFF_VERSION_TYPE(x)  (x)


/**
 * \brief When you enable the MSI-X Table RAM feature (MSIX_TABLE_EN=1), the controller implements the logic and RAM required to generate MSI-X requests. For more information, see the Interrupts section in the "Controller Operations" chapter of the Databook. This register is only used in AXI configurations. When your local AXI application writes (MWr) to the address defined in this register (and MSIX_ADDRESS_MATCH_HIGH_OFF), the controller will load the MSIX_DOORBELL_OFF register with the contents of the MWr and subsequently create and send MSI-X TLPs
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:MSIX_ADDRESS_MATCH_LOW_OFF
 */
#define VTSS_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x250)

/**
 * \brief
 * MSI-X Match Enable. Enable the MSI-X Address Match feature when the AXI
 * bridge is present.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF . MSIX_ADDRESS_MATCH_EN
 */
#define  VTSS_F_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_EN  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF . MSIX_ADDRESS_MATCH_RESERVED_1
 */
#define  VTSS_F_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_RESERVED_1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_RESERVED_1  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_RESERVED_1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * MSI-X Address Match Low Address.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF . MSIX_ADDRESS_MATCH_LOW
 */
#define  VTSS_F_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_LOW(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_LOW     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_PCIE_DBI_MSIX_ADDRESS_MATCH_LOW_OFF_MSIX_ADDRESS_MATCH_LOW(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief MSI-X Address Match High Register. When you enable the MSI-X Table RAM feature (MSIX_TABLE_EN=1), the controller implements the logic and RAM required to generate MSI-X requests. For more information, see the Interrupts section in the "Controller Operations" chapter of the Databook. This register is only used in AXI configurations. When your local AXI application writes (MWr) to the address defined in this register (and MSIX_ADDRESS_MATCH_LOW_OFF), the controller will load the MSIX_DOORBELL_OFF register with the contents of the MWr and subsequently create and send MSI-X TLPs
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:MSIX_ADDRESS_MATCH_HIGH_OFF
 */
#define VTSS_PCIE_DBI_MSIX_ADDRESS_MATCH_HIGH_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x251)

/**
 * \brief
 * MSI-X Address Match High Address.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hffffffff:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_ADDRESS_MATCH_HIGH_OFF . MSIX_ADDRESS_MATCH_HIGH
 */
#define  VTSS_F_PCIE_DBI_MSIX_ADDRESS_MATCH_HIGH_OFF_MSIX_ADDRESS_MATCH_HIGH(x)  (x)
#define  VTSS_M_PCIE_DBI_MSIX_ADDRESS_MATCH_HIGH_OFF_MSIX_ADDRESS_MATCH_HIGH     0xffffffff
#define  VTSS_X_PCIE_DBI_MSIX_ADDRESS_MATCH_HIGH_OFF_MSIX_ADDRESS_MATCH_HIGH(x)  (x)


/**
 * \brief When you enable the MSI-X Table RAM feature (MSIX_TABLE_EN=1), the controller implements the logic and RAM required to generate MSI-X requests. For more information, see the Interrupts section in the "Controller Operations" chapter of the Databook.
 - For AXI configurations: when your local application writes (MWr) to the address defined in MSIX_ADDRESS_MATCH_LOW_OFF, the controller will load this register with the contents of the MWr and subsequently create and send MSI-X TLPs.
 - For non-AMBA configurations: when your local application writes to this register, the controller will create and send MSI-X TLPs.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:MSIX_DOORBELL_OFF
 */
#define VTSS_PCIE_DBI_MSIX_DOORBELL_OFF      VTSS_IOREG(VTSS_TO_PCIE_DBI,0x252)

/**
 * \brief
 * MSI-X Doorbell Vector. This register determines which vector to generate
 * the MSI-X transaction for.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_DOORBELL_OFF . MSIX_DOORBELL_VECTOR
 */
#define  VTSS_F_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VECTOR(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VECTOR     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VECTOR(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * Reserved.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_DOORBELL_OFF . MSIX_DOORBELL_RESERVED_11
 */
#define  VTSS_F_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_RESERVED_11(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_RESERVED_11  VTSS_BIT(11)
#define  VTSS_X_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_RESERVED_11(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * MSIX Doorbell Traffic Class. This register determines which traffic
 * class to generate the MSI-X transaction with.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_DOORBELL_OFF . MSIX_DOORBELL_TC
 */
#define  VTSS_F_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_TC(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_TC     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_TC(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * MSIX Doorbell Virtual Function Active. This register determines whether
 * a Virtual Function is used to generate the MSI-X transaction.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_DOORBELL_OFF . MSIX_DOORBELL_VF_ACTIVE
 */
#define  VTSS_F_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VF_ACTIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VF_ACTIVE  VTSS_BIT(15)
#define  VTSS_X_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VF_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * MSIX Doorbell Virtual Function. This register determines the Virtual
 * Function for the MSI-X transaction.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_DOORBELL_OFF . MSIX_DOORBELL_VF
 */
#define  VTSS_F_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VF(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VF     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_VF(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * MSIX Doorbell Physical Function. This register determines the Physical
 * Function for the MSI-X transaction.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_DOORBELL_OFF . MSIX_DOORBELL_PF
 */
#define  VTSS_F_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_PF(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_PF     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_PF(x)  VTSS_EXTRACT_BITFIELD(x,24,5)

/**
 * \brief
 * Reserved.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_DOORBELL_OFF . MSIX_DOORBELL_RESERVED_29_31
 */
#define  VTSS_F_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_RESERVED_29_31(x)  VTSS_ENCODE_BITFIELD(x,29,3)
#define  VTSS_M_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_RESERVED_29_31     VTSS_ENCODE_BITMASK(29,3)
#define  VTSS_X_PCIE_DBI_MSIX_DOORBELL_OFF_MSIX_DOORBELL_RESERVED_29_31(x)  VTSS_EXTRACT_BITFIELD(x,29,3)


/**
 * \brief When you enable the MSI-X Table RAM feature (MSIX_TABLE_EN=1), the controller implements the logic and RAM required to generate MSI-X requests. For more information, see the Interrupts section in the "Controller Operations" chapter of the Databook.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:MSIX_RAM_CTRL_OFF
 */
#define VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF      VTSS_IOREG(VTSS_TO_PCIE_DBI,0x253)

/**
 * \brief
 * MSIX Table RAM Deep Sleep.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_TABLE_DS
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_TABLE_DS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_TABLE_DS  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_TABLE_DS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * MSIX Table RAM Shut Down.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_TABLE_SD
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_TABLE_SD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_TABLE_SD  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_TABLE_SD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_RESERVED_2_7
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_2_7(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_2_7     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_2_7(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * MSIX PBA RAM Deep Sleep.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_PBA_DS
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_PBA_DS(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_PBA_DS  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_PBA_DS(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * MSIX PBA RAM Shut Down.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_PBA_SD
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_PBA_SD(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_PBA_SD  VTSS_BIT(9)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_PBA_SD(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_RESERVED_10_15
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_10_15(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_10_15     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_10_15(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/**
 * \brief
 * MSIX RAM Control Bypass.
 * It is up to the application to ensure the RAMs are in the proper power
 * state before trying to access them. Moreover, the application needs to
 * observe all timing requirements of the RAM low power signals before
 * trying to use the MSIX functionality.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_BYPASS
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_BYPASS  VTSS_BIT(16)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_RESERVED_17_23
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_17_23(x)  VTSS_ENCODE_BITFIELD(x,17,7)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_17_23     VTSS_ENCODE_BITMASK(17,7)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_17_23(x)  VTSS_EXTRACT_BITFIELD(x,17,7)

/**
 * \brief
 * MSIX Table RAM Debug Mode. You can also use the dbg_table input to
 * activate debug mode. Debug mode turns off the PF/VF/Offset-based
 * addressing into the RAM and maps the entire table linearly from the base
 * address of the BAR (indicated by the BIR) in function 0.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_DBG_TABLE
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_DBG_TABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_DBG_TABLE  VTSS_BIT(24)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_DBG_TABLE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * MSIX PBA RAM Debug Mode. You can also use the dbg_pba input to activate
 * debug mode. Debug mode turns off the PF/VF/Offset-based addressing into
 * the RAM and maps the entire table linearly from the base address of the
 * BAR (indicated by the BIR) in function 0.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_DBG_PBA
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_DBG_PBA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_DBG_PBA  VTSS_BIT(25)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_DBG_PBA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_MSIX_RAM_CTRL_OFF . MSIX_RAM_CTRL_RESERVED_26_31
 */
#define  VTSS_F_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_26_31(x)  VTSS_ENCODE_BITFIELD(x,26,6)
#define  VTSS_M_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_26_31     VTSS_ENCODE_BITMASK(26,6)
#define  VTSS_X_PCIE_DBI_MSIX_RAM_CTRL_OFF_MSIX_RAM_CTRL_RESERVED_26_31(x)  VTSS_EXTRACT_BITFIELD(x,26,6)


/**
 * \brief This register reflects the application driven bus and device number.

 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PL_APP_BUS_DEV_NUM_STATUS_OFF
 */
#define VTSS_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2c4)

/**
 * \brief
 * This field reflects the value of device number driven on app_device_num
 * input signal by your application.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF . RC_DSW_DEV_NUM
 */
#define  VTSS_F_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF_RC_DSW_DEV_NUM(x)  VTSS_ENCODE_BITFIELD(x,3,5)
#define  VTSS_M_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF_RC_DSW_DEV_NUM     VTSS_ENCODE_BITMASK(3,5)
#define  VTSS_X_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF_RC_DSW_DEV_NUM(x)  VTSS_EXTRACT_BITFIELD(x,3,5)

/**
 * \brief
 * This field reflects the value of bus number driven on app_bus_num input
 * signal by your application.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF . RC_DSW_BUS_NUM
 */
#define  VTSS_F_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF_RC_DSW_BUS_NUM(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF_RC_DSW_BUS_NUM     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCIE_DBI_PL_APP_BUS_DEV_NUM_STATUS_OFF_RC_DSW_BUS_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/**
 * \brief This register provides control over TLP Traffic during Non-D0 States.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PCIPM_TRAFFIC_CTRL_OFF
 */
#define VTSS_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2c7)

/**
 * \brief
 * This field indicates that VDM Message TLPs are blocked during non-D0
 * states.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF . PCIPM_VDM_TRAFFIC_BLOCKED
 */
#define  VTSS_F_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_VDM_TRAFFIC_BLOCKED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_VDM_TRAFFIC_BLOCKED  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_VDM_TRAFFIC_BLOCKED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * This field indicates that all TLPs transmitted by Client 0 interface are
 * blocked during non-D0 states.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF . PCIPM_NEW_TLP_CLIENT0_BLOCKED
 */
#define  VTSS_F_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT0_BLOCKED(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT0_BLOCKED  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT0_BLOCKED(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This field indicates that all TLPs transmitted by Client 1 interface are
 * blocked during non-D0 states.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF . PCIPM_NEW_TLP_CLIENT1_BLOCKED
 */
#define  VTSS_F_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT1_BLOCKED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT1_BLOCKED  VTSS_BIT(2)
#define  VTSS_X_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT1_BLOCKED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This field indicates that all TLPs transmitted by Client 2 interface are
 * blocked during non-D0 states.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF . PCIPM_NEW_TLP_CLIENT2_BLOCKED
 */
#define  VTSS_F_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT2_BLOCKED(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT2_BLOCKED  VTSS_BIT(3)
#define  VTSS_X_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_NEW_TLP_CLIENT2_BLOCKED(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF . PCIPM_RESERVED_4_7
 */
#define  VTSS_F_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_RESERVED_4_7(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_RESERVED_4_7     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_PCIE_DBI_PCIPM_TRAFFIC_CTRL_OFF_PCIPM_RESERVED_4_7(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief This register controls the auxiliary clock frequency.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:AUX_CLK_FREQ_OFF
 */
#define VTSS_PCIE_DBI_AUX_CLK_FREQ_OFF       VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2d0)

/**
 * \brief
 * The aux_clk frequency in MHz. This value is used to provide a 1 us
 * reference for counting time during low-power states with aux_clk when
 * the PHY has removed the pipe_clk.
 * Frequencies lower than 1 MHz are possible but with a loss of accuracy in
 * the time counted.
 * If the actual frequency (f) of aux_clk does not exactly match the
 * programmed frequency (f_prog), then there is an error in the time
 * counted by the controller that can be expressed in percentage as: err% =
 * (f_prog/f-1)*100. For example if f=2.5 MHz and f_prog=3 MHz, then err%
 * =(3/2.5-1)*100 =20%, meaning that the time counted by the controller on
 * aux_clk will be 20% greater than the time in us programmed in the
 * corresponding time register (for example T_POWER_ON).
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_AUX_CLK_FREQ_OFF . AUX_CLK_FREQ
 */
#define  VTSS_F_PCIE_DBI_AUX_CLK_FREQ_OFF_AUX_CLK_FREQ(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCIE_DBI_AUX_CLK_FREQ_OFF_AUX_CLK_FREQ     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCIE_DBI_AUX_CLK_FREQ_OFF_AUX_CLK_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief This is the Powerdown Control and Status register.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:POWERDOWN_CTRL_STATUS_OFF
 */
#define VTSS_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2d2)

/**
 * \brief
 * This field is a one shot field. This field could be used for debug
 * purposes in event that the P2 Powerdown transition does not complete. It
 * will allow the controller to proceed with the transition to the P1
 * Powerdown state. This field always reads back as 1'b0.

 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF . POWERDOWN_FORCE
 */
#define  VTSS_F_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_FORCE  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Set this bit to 1 if you do not want to perform the handshake with the
 * power-switch after PERST# assertion. By default the controller will
 * perform the handshake with the power-switch if L1 power gating is
 * enabled
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF . POWERDOWN_VMAIN_ACK
 */
#define  VTSS_F_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_VMAIN_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_VMAIN_ACK  VTSS_BIT(1)
#define  VTSS_X_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_VMAIN_ACK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This field represents the Powerdown value driven by the controller to
 * the PHY.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF . POWERDOWN_MAC_POWERDOWN
 */
#define  VTSS_F_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_MAC_POWERDOWN(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_MAC_POWERDOWN     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_MAC_POWERDOWN(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * This field represents the Powerdown value that has been acknowledged by
 * the PHY. It is updated with the value of Powerdown driven by the
 * controller, when the PHY has returned the Phystatus acknowledgment for
 * the Powerdown transition.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF . POWERDOWN_PHY_POWERDOWN
 */
#define  VTSS_F_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_PHY_POWERDOWN(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_PHY_POWERDOWN     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PCIE_DBI_POWERDOWN_CTRL_STATUS_OFF_POWERDOWN_PHY_POWERDOWN(x)  VTSS_EXTRACT_BITFIELD(x,8,4)


/**
 * \brief This register controls controller PHY dependent behavior.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PHY_INTEROP_CTRL_2_OFF
 */
#define VTSS_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2d3)

/**
 * \brief
 * Control how long the controller should wait to release a PIPE reset
 * (pm_req_phy_rst) after releasing a PMA reset (pm_req_phy_perst). This
 * register should only be used to ensure a correct sequencing of the
 * resets into the PHY. If the application needs to delay the PIPE reset
 * arbitrarily, for example to configure the PHY firmware, Synopsys
 * recommends using the app_hold_phy_rst control signal. There is no need
 * to modify the value of this register when using Synopsys PHYs. Duration
 * is in aux clock cycles.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h3f:
 * 'ha:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF . PMA_PIPE_RST_DELAY_TIMER
 */
#define  VTSS_F_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF_PMA_PIPE_RST_DELAY_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF_PMA_PIPE_RST_DELAY_TIMER     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF_PMA_PIPE_RST_DELAY_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * For a DSP component, this register field controls the delay between the
 * reception of PM_Enter_L1 DLLP and the start of PCI-PM L1 entry
 * negotiation in aux clock cycles (1 to 15). When using this feature on
 * legacy DMA configurations, the configured value must be greater than
 * three.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'hf:
 * 'h0:

 *
 * Field: ::VTSS_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF . DSP_PCIPM_L1_ENTER_DELAY
 */
#define  VTSS_F_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF_DSP_PCIPM_L1_ENTER_DELAY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF_DSP_PCIPM_L1_ENTER_DELAY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PCIE_DBI_PHY_INTEROP_CTRL_2_OFF_DSP_PCIPM_L1_ENTER_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)


/**
 * \brief This register controls the PIPE's capabitity, control, and status parameters.
 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PIPE_RELATED_OFF
 */
#define VTSS_PCIE_DBI_PIPE_RELATED_OFF       VTSS_IOREG(VTSS_TO_PCIE_DBI,0x2e4)

/**
 * \brief
 * PIPE Garbage Data Mode.
 *  - RxValid is de-asserted
 *  - a valid RxStartBlock is received at 128b/130b encoding
 *  - a valid COM symbol is received at 8b/10b encoding
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_PIPE_RELATED_OFF . PIPE_GARBAGE_DATA_MODE
 */
#define  VTSS_F_PCIE_DBI_PIPE_RELATED_OFF_PIPE_GARBAGE_DATA_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_DBI_PIPE_RELATED_OFF_PIPE_GARBAGE_DATA_MODE  VTSS_BIT(8)
#define  VTSS_X_PCIE_DBI_PIPE_RELATED_OFF_PIPE_GARBAGE_DATA_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief This register is used to select the PF which is accessable either from lower or upper bank of PFs from DBI.

 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:DBI_FUNCTION_BANK_CTRL_REG_OFF
 */
#define VTSS_PCIE_DBI_DBI_FUNCTION_BANK_CTRL_REG_OFF  VTSS_IOREG(VTSS_TO_PCIE_DBI,0x31f)

/**
 * \brief
 * DBI Function Bank Select.
 *
 *
 * Note: The access attributes of this field are as follows:
 *  - Wire: R
 *  - Dbi: R
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_PCIE_DBI_DBI_FUNCTION_BANK_CTRL_REG_OFF . DBI_FUNCTION_BANK_CTRL_REG
 */
#define  VTSS_F_PCIE_DBI_DBI_FUNCTION_BANK_CTRL_REG_OFF_DBI_FUNCTION_BANK_CTRL_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_DBI_DBI_FUNCTION_BANK_CTRL_REG_OFF_DBI_FUNCTION_BANK_CTRL_REG  VTSS_BIT(0)
#define  VTSS_X_PCIE_DBI_DBI_FUNCTION_BANK_CTRL_REG_OFF_DBI_FUNCTION_BANK_CTRL_REG(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief This is a reserved register.

 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:UTILITY_OFF
 */
#define VTSS_PCIE_DBI_UTILITY_OFF            VTSS_IOREG(VTSS_TO_PCIE_DBI,0x320)

/**
 * \brief
 * Reserved.
 *
 *
 * Note: This register field is sticky.
 *
 * \details
 * Field: ::VTSS_PCIE_DBI_UTILITY_OFF . UTILITY
 */
#define  VTSS_F_PCIE_DBI_UTILITY_OFF_UTILITY(x)  (x)
#define  VTSS_M_PCIE_DBI_UTILITY_OFF_UTILITY     0xffffffff
#define  VTSS_X_PCIE_DBI_UTILITY_OFF_UTILITY(x)  (x)


/**
 * \brief This is the PM shadow copy of the UTILITY register.

 *
 * \details
 * Register: \a PCIE_DBI:PF0_PORT_LOGIC:PM_UTILITY_OFF
 */
#define VTSS_PCIE_DBI_PM_UTILITY_OFF         VTSS_IOREG(VTSS_TO_PCIE_DBI,0x322)

/**
 * \brief
 * Reserved.

 *
 * \details
 * Field: ::VTSS_PCIE_DBI_PM_UTILITY_OFF . PM_UTILITY
 */
#define  VTSS_F_PCIE_DBI_PM_UTILITY_OFF_PM_UTILITY(x)  (x)
#define  VTSS_M_PCIE_DBI_PM_UTILITY_OFF_PM_UTILITY     0xffffffff
#define  VTSS_X_PCIE_DBI_PM_UTILITY_OFF_PM_UTILITY(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_PCIE_DBI_H_ */
