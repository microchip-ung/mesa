// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_OTP_H_
#define _VTSS_LAGUNA_REGS_OTP_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a OTP
 *
 * One Time Programmable
 *
 ***********************************************************************/

/**
 * Register Group: \a OTP:OTP_REGS
 *
 * One Time Programmable Controller Registers
 */


/**
 * \brief Power Down Register
 *
 * \details
 * Power Down Register

 *
 * Register: \a OTP:OTP_REGS:OTP_PWR_DN
 */
#define VTSS_OTP_OTP_PWR_DN                  VTSS_IOREG(VTSS_TO_OTP,0x0)

/**
 * \brief
 * This active-low bit directly controls the CEB input into the OTP
 * IP.Note: This bit is cleared before performing OTP operations. Thebit
 * should stay cleared until all planned OTP programmingand read operations
 * have completed.
 *
 * \details
 * 0: OTP is operational
 * 1: OTP is in power down
 *
 * Field: ::VTSS_OTP_OTP_PWR_DN . OTP_PWRDN_N
 */
#define  VTSS_F_OTP_OTP_PWR_DN_OTP_PWRDN_N(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_PWR_DN_OTP_PWRDN_N    VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_PWR_DN_OTP_PWRDN_N(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_ADDR_HI Register
 *
 * \details
 * OTP_ADDR_HI Register
 * Address input. Programs the address targeted by OTP operation. These
 * bits are directly connected to the Kilopass IP
 * address input.
 * APPLICATION NOTE: This field can not be altered while read and
 * programming operations are pending.
 *
 * Register: \a OTP:OTP_REGS:OTP_ADDR_HI
 */
#define VTSS_OTP_OTP_ADDR_HI                 VTSS_IOREG(VTSS_TO_OTP,0x1)

/**
 * \brief
 * OTP Address
 *
 * \details
 * Field: ::VTSS_OTP_OTP_ADDR_HI . OTP_ADDR_16_11
 */
#define  VTSS_F_OTP_OTP_ADDR_HI_OTP_ADDR_16_11(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_OTP_OTP_ADDR_HI_OTP_ADDR_16_11     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_OTP_OTP_ADDR_HI_OTP_ADDR_16_11(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief OTP_ADDR_LO Register
 *
 * \details
 * OTP_ADDR_LO Register
 * Address input. Programs the address targeted by OTP operation. These
 * bits are directly connected to the Kilopass IP
 * address input.
 * APPLICATION NOTE: This field can not be altered while read and
 * programming operations are pending.

 *
 * Register: \a OTP:OTP_REGS:OTP_ADDR_LO
 */
#define VTSS_OTP_OTP_ADDR_LO                 VTSS_IOREG(VTSS_TO_OTP,0x2)

/**
 * \brief
 * OTP Address
 *
 * \details
 * Field: ::VTSS_OTP_OTP_ADDR_LO . OTP_ADDR_10_3
 */
#define  VTSS_F_OTP_OTP_ADDR_LO_OTP_ADDR_10_3(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_ADDR_LO_OTP_ADDR_10_3     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_ADDR_LO_OTP_ADDR_10_3(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_ADDR_BITS Register
 *
 * \details
 * OTP_ADDR_BITS Register
 * Address input. Programs the address targeted by OTP operation. These
 * bits are directly connected to the Kilopass IP
 * address input.
 * APPLICATION NOTE: When a read operation or byte wide program operation
 * occurs bits OTP_ADDR[2:0] are ignored
 * APPLICATION NOTE: This field can not be altered while read and
 * programming operations are pending.

 *
 * Register: \a OTP:OTP_REGS:OTP_ADDR_BITS
 */
#define VTSS_OTP_OTP_ADDR_BITS               VTSS_IOREG(VTSS_TO_OTP,0x3)

/**
 * \brief
 * OTP Address
 *
 * \details
 * Field: ::VTSS_OTP_OTP_ADDR_BITS . OTP_ADDR_2_0
 */
#define  VTSS_F_OTP_OTP_ADDR_BITS_OTP_ADDR_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_OTP_OTP_ADDR_BITS_OTP_ADDR_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_OTP_OTP_ADDR_BITS_OTP_ADDR_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief OTP_PRGM_DATA Register
 *
 * \details
 * OTP_PRGM_DATA Register

 *
 * Register: \a OTP:OTP_REGS:OTP_PRGM_DATA
 */
#define VTSS_OTP_OTP_PRGM_DATA               VTSS_IOREG(VTSS_TO_OTP,0x4)

/**
 * \brief
 * Parallel data to be written to the OTP internal DATA register. TheDATA
 * register contents are then transferred to the OTP at theOTP_ADDR_HI
 * location with a program command.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_PRGM_DATA . OTP_WR_DATA
 */
#define  VTSS_F_OTP_OTP_PRGM_DATA_OTP_WR_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_PRGM_DATA_OTP_WR_DATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_PRGM_DATA_OTP_WR_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_PRGM_MODE Register
 *
 * \details
 * OTP_PRGM_MODE Register
 * The OTP IP can only be programmed on a bit basis. The OTP controller
 * adjusts for this by issuing eight programming
 * commands to implement byte programming.
 *
 * Register: \a OTP:OTP_REGS:OTP_PRGM_MODE
 */
#define VTSS_OTP_OTP_PRGM_MODE               VTSS_IOREG(VTSS_TO_OTP,0x5)

/**
 * \brief
 * Program Mode Byte.This indicates the units of a programming
 * operation.Note: OTP reads are always byte wide.
 *
 * \details
 * 0 - Bit programming
 * 1 - Byte programming
 *
 * Field: ::VTSS_OTP_OTP_PRGM_MODE . OTP_PGM_MODE_BYTE
 */
#define  VTSS_F_OTP_OTP_PRGM_MODE_OTP_PGM_MODE_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_PRGM_MODE_OTP_PGM_MODE_BYTE  VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_PRGM_MODE_OTP_PGM_MODE_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_RD_DATA Register
 *
 * \details
 * OTP_RD_DATA Register
 *
 * Register: \a OTP:OTP_REGS:OTP_RD_DATA
 */
#define VTSS_OTP_OTP_RD_DATA                 VTSS_IOREG(VTSS_TO_OTP,0x6)

/**
 * \brief
 * This is the data from the OTP at the location pointed to
 * byOTP_ADDR_HI.To get fresh data a READ, or PROGRAM command operation
 * mustbe issue before reading this register.Note: PROGRAM commands update
 * this register as well as thedata bus output from OTP holds the value
 * stored at thepreviously programmed location after the deassertion
 * ofPGMEN.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_RD_DATA . OTP_RD_DATA_FLD
 */
#define  VTSS_F_OTP_OTP_RD_DATA_OTP_RD_DATA_FLD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_RD_DATA_OTP_RD_DATA_FLD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_RD_DATA_OTP_RD_DATA_FLD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_FUNC_CMD Register
 *
 * \details
 * OTP_FUNC_CMD Register
 *
 * Register: \a OTP:OTP_REGS:OTP_FUNC_CMD
 */
#define VTSS_OTP_OTP_FUNC_CMD                VTSS_IOREG(VTSS_TO_OTP,0x8)

/**
 * \brief
 * 1- Indicates the next PROGRAM command initiates the firstprogramming
 * pulse in smart programming algorithm.Note: Note: This bit clears after
 * programming command iscomplete.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_FUNC_CMD . OTP_FW_SMART_PGM_INIT_ACCESS
 */
#define  VTSS_F_OTP_OTP_FUNC_CMD_OTP_FW_SMART_PGM_INIT_ACCESS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_OTP_OTP_FUNC_CMD_OTP_FW_SMART_PGM_INIT_ACCESS  VTSS_BIT(4)
#define  VTSS_X_OTP_OTP_FUNC_CMD_OTP_FW_SMART_PGM_INIT_ACCESS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * 1-  FW Controlled SMART programming Support Enable.0 - HW controlled
 * SMART programming support Enable.Note: Note:: This bit clears after
 * programming command iscomplete.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_FUNC_CMD . OTP_FW_SMART_PGM_EN
 */
#define  VTSS_F_OTP_OTP_FUNC_CMD_OTP_FW_SMART_PGM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_OTP_OTP_FUNC_CMD_OTP_FW_SMART_PGM_EN  VTSS_BIT(3)
#define  VTSS_X_OTP_OTP_FUNC_CMD_OTP_FW_SMART_PGM_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RESET Command. Pulses the RSTB input into the OPT for a lengthspecified
 * in OTP_PGM_PW_HI.Note: This bit clears after command is accepted by the
 * OTPcontroller.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_FUNC_CMD . OTP_RESET
 */
#define  VTSS_F_OTP_OTP_FUNC_CMD_OTP_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_OTP_OTP_FUNC_CMD_OTP_RESET    VTSS_BIT(2)
#define  VTSS_X_OTP_OTP_FUNC_CMD_OTP_RESET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Program OTP commandNote: This bit clears after command is accepted by
 * the OTPcontroller.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_FUNC_CMD . OTP_PROGRAM
 */
#define  VTSS_F_OTP_OTP_FUNC_CMD_OTP_PROGRAM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_OTP_OTP_FUNC_CMD_OTP_PROGRAM  VTSS_BIT(1)
#define  VTSS_X_OTP_OTP_FUNC_CMD_OTP_PROGRAM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read OTP commandNote: This bit clears after command is accepted by the
 * OTPcontroller
 *
 * \details
 * Field: ::VTSS_OTP_OTP_FUNC_CMD . OTP_READ
 */
#define  VTSS_F_OTP_OTP_FUNC_CMD_OTP_READ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_FUNC_CMD_OTP_READ     VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_FUNC_CMD_OTP_READ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_TEST_CMD Register
 *
 * \details
 * OTP_TEST_CMD Register
 * Only a single bit in the OTP_FUNC_CMD or OTP_TEST_CMD register must be
 * set before initiating the OTP operation
 * via the OTP_GO bit in the OTP_CMD_GO register.
 *
 * Register: \a OTP:OTP_REGS:OTP_TEST_CMD
 */
#define VTSS_OTP_OTP_TEST_CMD                VTSS_IOREG(VTSS_TO_OTP,0x9)

/**
 * \brief
 * TESTDEC is valid only for un-programmed units.If TESTDEC isperformed on
 * a programmed unit, the result is undefined.
 *
 * \details
 * 0 - Selects main memory for TESTDEC operation
 * 1 - Selects redundant memory for TESTDEC operation
 *
 * Field: ::VTSS_OTP_OTP_TEST_CMD . OTP_TEST_DEC_SEL
 */
#define  VTSS_F_OTP_OTP_TEST_CMD_OTP_TEST_DEC_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_OTP_OTP_TEST_CMD_OTP_TEST_DEC_SEL  VTSS_BIT(4)
#define  VTSS_X_OTP_OTP_TEST_CMD_OTP_TEST_DEC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * WRTEST Command (Pre-program Test).WRTEST enables an end user to screen
 * out gross defects inprogramming circuitry before programming of the
 * actual XPMmemory array is done.This is enabled by availability of two
 * spare rows for programming. Itis performed by latching test mode word
 * 0x04 into the testcommand register, programming the spare rows and
 * verifying thatspare rows can be programmed correctly.Note: This bit self
 * clears after the command is completed.Note: This bit clears after
 * command is accepted by the OTPcontroller.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TEST_CMD . OTP_WRTEST
 */
#define  VTSS_F_OTP_OTP_TEST_CMD_OTP_WRTEST(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_OTP_OTP_TEST_CMD_OTP_WRTEST   VTSS_BIT(2)
#define  VTSS_X_OTP_OTP_TEST_CMD_OTP_WRTEST(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * TESTDEC Command (Word-line and Bit-line Integrity Test)TESTDEC is a
 * built-in test mode. It enables an end user to verifythe integrity of
 * wordlines and bitlines as well as screen out the grossdefects in the
 * peripheral logic. It is performed on an unprogrammedunit.The Test Mode
 * Code for TESTDEC is "0x68 with DLE=1" followedby "0x21 with DLE=0."
 * After entering into the TESTDEC Test Mode,make subsequent read
 * operations to successive addresses till theentire OTP memory is read
 * out. The expected test pattern is avariation of a checkerboard
 * pattern.Note: This bit self clears after the command is completed.Note:
 * This bit clears after command is accepted by the OTPcontroller.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TEST_CMD . OTP_TESTDEC
 */
#define  VTSS_F_OTP_OTP_TEST_CMD_OTP_TESTDEC(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_OTP_OTP_TEST_CMD_OTP_TESTDEC  VTSS_BIT(1)
#define  VTSS_X_OTP_OTP_TEST_CMD_OTP_TESTDEC(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Blank Check Command (Defective Bit Screen Test).Blank Check verifies
 * that OTP memory is preloaded with "0" beforeactual programming. Blank
 * Check is performed by reading every bitlocation at nominal VDD and
 * nominal VDDIO before any other testsor any programming is performed on
 * the XPM memory. Thecommand is enabled by latching test mode word "0x28"
 * into the testcommand register,Note: This bit self clears after the
 * command is completed.Note: This bit clears after command is accepted by
 * the OTPcontroller.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TEST_CMD . OTP_BLANKCHECK
 */
#define  VTSS_F_OTP_OTP_TEST_CMD_OTP_BLANKCHECK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_TEST_CMD_OTP_BLANKCHECK  VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_TEST_CMD_OTP_BLANKCHECK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_CMD_GO Register
 *
 * \details
 * OTP_CMD_GO Register
 *
 * Register: \a OTP:OTP_REGS:OTP_CMD_GO
 */
#define VTSS_OTP_OTP_CMD_GO                  VTSS_IOREG(VTSS_TO_OTP,0xa)

/**
 * \brief
 * Go Command Bit.Setting this bit initiates the OTP command defined in
 * either theOTP_FUNC_CMD or OTP_TEST_CMD register.Note: This bit clears
 * after command is accepted by the OTPcontroller.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_CMD_GO . OTP_GO
 */
#define  VTSS_F_OTP_OTP_CMD_GO_OTP_GO(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_CMD_GO_OTP_GO         VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_CMD_GO_OTP_GO(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_PASS_FAIL Register
 *
 * \details
 * OTP_PASS_FAIL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_PASS_FAIL
 */
#define VTSS_OTP_OTP_PASS_FAIL               VTSS_IOREG(VTSS_TO_OTP,0xb)

/**
 * \brief
 * Read skip.This bit asserts when a read is attempted from any of the
 * protectedregions [see Section "HW OTP Memory").Note: This bit
 * automatically clears when the OTP_GO bit is set.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_PASS_FAIL . OTP_READ_PROHIBITED
 */
#define  VTSS_F_OTP_OTP_PASS_FAIL_OTP_READ_PROHIBITED(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_OTP_OTP_PASS_FAIL_OTP_READ_PROHIBITED  VTSS_BIT(3)
#define  VTSS_X_OTP_OTP_PASS_FAIL_OTP_READ_PROHIBITED(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Write skip.This bit asserts when a write is attempted to any of the
 * protectedregions (see Section "HW OTP Memory").Note: This bit
 * automatically clears when the OTP_GO bit is set.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_PASS_FAIL . OTP_WRITE_PROHIBITED
 */
#define  VTSS_F_OTP_OTP_PASS_FAIL_OTP_WRITE_PROHIBITED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_OTP_OTP_PASS_FAIL_OTP_WRITE_PROHIBITED  VTSS_BIT(2)
#define  VTSS_X_OTP_OTP_PASS_FAIL_OTP_WRITE_PROHIBITED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Pass Status Bit.This bit asserts after the completion of an OTP test
 * command toindicate that the command passed.Note: This bit automatically
 * clears when the OTP_GO bit is set.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_PASS_FAIL . OTP_PASS
 */
#define  VTSS_F_OTP_OTP_PASS_FAIL_OTP_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_OTP_OTP_PASS_FAIL_OTP_PASS    VTSS_BIT(1)
#define  VTSS_X_OTP_OTP_PASS_FAIL_OTP_PASS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Fail status Bit.This bit asserts after the completion of an OTP test
 * command toindicate that the command failed.Note: This bit automatically
 * clears when the OTP_GO bit is set.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_PASS_FAIL . OTP_FAIL
 */
#define  VTSS_F_OTP_OTP_PASS_FAIL_OTP_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_PASS_FAIL_OTP_FAIL    VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_PASS_FAIL_OTP_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_STATUS Register
 *
 * \details
 * OTP_STATUS Register
 *
 * Register: \a OTP:OTP_REGS:OTP_STATUS
 */
#define VTSS_OTP_OTP_STATUS                  VTSS_IOREG(VTSS_TO_OTP,0xc)

/**
 * \brief
 * OTP Loaded Status.Indicates that HW readout of OTP after reset is
 * completed.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_STATUS . OTP_LOADED
 */
#define  VTSS_F_OTP_OTP_STATUS_OTP_LOADED(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_OTP_OTP_STATUS_OTP_LOADED     VTSS_BIT(7)
#define  VTSS_X_OTP_OTP_STATUS_OTP_LOADED(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * OTP MEM Lock status.This is a direct read of the LOCK output of the OTP.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_STATUS . OTP_LOCK
 */
#define  VTSS_F_OTP_OTP_STATUS_OTP_LOCK(x)    VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_OTP_OTP_STATUS_OTP_LOCK       VTSS_BIT(4)
#define  VTSS_X_OTP_OTP_STATUS_OTP_LOCK(x)    VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * OTP Write Enable.This is a direct read of the WEB input to the OTP.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_STATUS . OTP_WEB
 */
#define  VTSS_F_OTP_OTP_STATUS_OTP_WEB(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_OTP_OTP_STATUS_OTP_WEB        VTSS_BIT(3)
#define  VTSS_X_OTP_OTP_STATUS_OTP_WEB(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Programming Enable.This is a direct read of the PGMEN input to the OTP.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_STATUS . OTP_PGMEN
 */
#define  VTSS_F_OTP_OTP_STATUS_OTP_PGMEN(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_OTP_OTP_STATUS_OTP_PGMEN      VTSS_BIT(2)
#define  VTSS_X_OTP_OTP_STATUS_OTP_PGMEN(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Charge pump is on.This is a direct read of the CPUMPEN input to the OTP.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_STATUS . OTP_CPUMPEN
 */
#define  VTSS_F_OTP_OTP_STATUS_OTP_CPUMPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_OTP_OTP_STATUS_OTP_CPUMPEN    VTSS_BIT(1)
#define  VTSS_X_OTP_OTP_STATUS_OTP_CPUMPEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * OTP operation is in progress.This bit clears after OTP command has
 * completed.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_STATUS . OTP_BUSY
 */
#define  VTSS_F_OTP_OTP_STATUS_OTP_BUSY(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_STATUS_OTP_BUSY       VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_STATUS_OTP_BUSY(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_MAX_PRG Register
 *
 * \details
 * OTP_MAX_PRG Register
 *
 * Register: \a OTP:OTP_REGS:OTP_MAX_PRG
 */
#define VTSS_OTP_OTP_MAX_PRG                 VTSS_IOREG(VTSS_TO_OTP,0xd)

/**
 * \brief
 * Maximum Programming.Specifies the number of attempts made by the Program
 * commandto program an OTP bit cell.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_MAX_PRG . OTP_MAX_PROG
 */
#define  VTSS_F_OTP_OTP_MAX_PRG_OTP_MAX_PROG(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_OTP_OTP_MAX_PRG_OTP_MAX_PROG     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_OTP_OTP_MAX_PRG_OTP_MAX_PROG(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief OTP_INTR_STATUS Regisgter
 *
 * \details
 * OTP_INTR_STATUS Regisgter
 *
 * Register: \a OTP:OTP_REGS:OTP_INTR_STATUS
 */
#define VTSS_OTP_OTP_INTR_STATUS             VTSS_IOREG(VTSS_TO_OTP,0x10)

/**
 * \brief
 * This bit is set whenever OTP_BUSY in the OTP_STATUS registertransitions
 * from '1' to '0'. A one in this bit causes an OTP interruptto the
 * .CPUWrite a . '1' to clear this bit. Writes of '0' have no effect.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_INTR_STATUS . OTP_READY_INTR_STATUS
 */
#define  VTSS_F_OTP_OTP_INTR_STATUS_OTP_READY_INTR_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_INTR_STATUS_OTP_READY_INTR_STATUS  VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_INTR_STATUS_OTP_READY_INTR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_INTR_MASK Register
 *
 * \details
 * OTP_INTR_MASK Register
 *
 * Register: \a OTP:OTP_REGS:OTP_INTR_MASK
 */
#define VTSS_OTP_OTP_INTR_MASK               VTSS_IOREG(VTSS_TO_OTP,0x11)

/**
 * \brief
 * When '1' , prevents the generation of this interrupt.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_INTR_MASK . OTP_READY_INTR_MASK
 */
#define  VTSS_F_OTP_OTP_INTR_MASK_OTP_READY_INTR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_OTP_OTP_INTR_MASK_OTP_READY_INTR_MASK  VTSS_BIT(0)
#define  VTSS_X_OTP_OTP_INTR_MASK_OTP_READY_INTR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OTP_RSTB_PW_HI Register
 *
 * \details
 * OTP_RSTB_PW_HI Register
 *
 * Register: \a OTP:OTP_REGS:OTP_RSTB_PW_HI
 */
#define VTSS_OTP_OTP_RSTB_PW_HI              VTSS_IOREG(VTSS_TO_OTP,0x14)

/**
 * \brief
 * RSTB Pulse Width in terms of system clocks.This corresponds to RSTB.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_RSTB_PW_HI . OTP_RSTW_15_8
 */
#define  VTSS_F_OTP_OTP_RSTB_PW_HI_OTP_RSTW_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_RSTB_PW_HI_OTP_RSTW_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_RSTB_PW_HI_OTP_RSTW_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_RSTB_PW_LO Register
 *
 * \details
 * OTP_RSTB_PW_LO Register
 *
 * Register: \a OTP:OTP_REGS:OTP_RSTB_PW_LO
 */
#define VTSS_OTP_OTP_RSTB_PW_LO              VTSS_IOREG(VTSS_TO_OTP,0x15)

/**
 * \brief
 * RSTB Pulse Width in terms of system clocks.This corresponds to RSTB.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_RSTB_PW_LO . OTP_RSTW_7_0
 */
#define  VTSS_F_OTP_OTP_RSTB_PW_LO_OTP_RSTW_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_RSTB_PW_LO_OTP_RSTW_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_RSTB_PW_LO_OTP_RSTW_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_PGM_PW_HI Register
 *
 * \details
 * OTP_PGM_PW_HI Register
 *
 * Register: \a OTP:OTP_REGS:OTP_PGM_PW_HI
 */
#define VTSS_OTP_OTP_PGM_PW_HI               VTSS_IOREG(VTSS_TO_OTP,0x18)

/**
 * \brief
 * Programming Pulse Width in terms of system clocks. The minimumvalue to
 * be used is 300 (~5?s).Note: Assumes 25 MHz system clock.Note: OTP
 * programming is not supported when operating off ofthe ring oscillator.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_PGM_PW_HI . OTP_PPW_HI
 */
#define  VTSS_F_OTP_OTP_PGM_PW_HI_OTP_PPW_HI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_PGM_PW_HI_OTP_PPW_HI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_PGM_PW_HI_OTP_PPW_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_PGM_PW_LO Register
 *
 * \details
 * OTP_PGM_PW_LO Register
 *
 * Register: \a OTP:OTP_REGS:OTP_PGM_PW_LO
 */
#define VTSS_OTP_OTP_PGM_PW_LO               VTSS_IOREG(VTSS_TO_OTP,0x19)

/**
 * \brief
 * Programming Pulse Width in terms of system clocks. The minimumvalue to
 * be used is 300 (~5?s).Note: Assumes 25 MHz system clock.Note: OTP
 * programming is not supported when operating off ofthe ring oscillator.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_PGM_PW_LO . OTP_PPW_LO
 */
#define  VTSS_F_OTP_OTP_PGM_PW_LO_OTP_PPW_LO(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_PGM_PW_LO_OTP_PPW_LO     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_PGM_PW_LO_OTP_PPW_LO(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_READ_PW_HI Register
 *
 * \details
 * OTP_READ_PW_HI Register
 *
 * Register: \a OTP:OTP_REGS:OTP_READ_PW_HI
 */
#define VTSS_OTP_OTP_READ_PW_HI              VTSS_IOREG(VTSS_TO_OTP,0x1c)

/**
 * \brief
 * Read pulse width in terms of system clock.This corresponds to tRWHNote:
 * Default value for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_READ_PW_HI . OTP_RPW_HI
 */
#define  VTSS_F_OTP_OTP_READ_PW_HI_OTP_RPW_HI(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_READ_PW_HI_OTP_RPW_HI     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_READ_PW_HI_OTP_RPW_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_READ_PW_LO Register
 *
 * \details
 * OTP_READ_PW_LO Register
 *
 * Register: \a OTP:OTP_REGS:OTP_READ_PW_LO
 */
#define VTSS_OTP_OTP_READ_PW_LO              VTSS_IOREG(VTSS_TO_OTP,0x1d)

/**
 * \brief
 * Read pulse width in terms of system clock.This corresponds to tRWH.Note:
 * Default value for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_READ_PW_LO . OTP_RPW_LO
 */
#define  VTSS_F_OTP_OTP_READ_PW_LO_OTP_RPW_LO(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_READ_PW_LO_OTP_RPW_LO     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_READ_PW_LO_OTP_RPW_LO(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TCRST_VAL Register
 *
 * \details
 * OTP_TCRST_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TCRST_VAL
 */
#define VTSS_OTP_OTP_TCRST_VAL               VTSS_IOREG(VTSS_TO_OTP,0x20)

/**
 * \brief
 * CEB Setup Time before RSTB.Note: Default value for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TCRST_VAL . OTP_TCRST
 */
#define  VTSS_F_OTP_OTP_TCRST_VAL_OTP_TCRST(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TCRST_VAL_OTP_TCRST     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TCRST_VAL_OTP_TCRST(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TRSRD_VAL Register
 *
 * \details
 * OTP_TRSRD_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TRSRD_VAL
 */
#define VTSS_OTP_OTP_TRSRD_VAL               VTSS_IOREG(VTSS_TO_OTP,0x21)

/**
 * \brief
 * OTP RSTB Setup Time before READEN.Note: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TRSRD_VAL . OTP_TRSRD
 */
#define  VTSS_F_OTP_OTP_TRSRD_VAL_OTP_TRSRD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TRSRD_VAL_OTP_TRSRD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TRSRD_VAL_OTP_TRSRD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TREADEN_VAL Register
 *
 * \details
 * OTP_TREADEN_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TREADEN_VAL
 */
#define VTSS_OTP_OTP_TREADEN_VAL             VTSS_IOREG(VTSS_TO_OTP,0x22)

/**
 * \brief
 * (Not currently used) READEN to Output Delay.Note: Default value for 25
 * MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TREADEN_VAL . OTP_TREADEN
 */
#define  VTSS_F_OTP_OTP_TREADEN_VAL_OTP_TREADEN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TREADEN_VAL_OTP_TREADEN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TREADEN_VAL_OTP_TREADEN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TDLES_VAL Register
 *
 * \details
 * OTP_TDLES_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TDLES_VAL
 */
#define VTSS_OTP_OTP_TDLES_VAL               VTSS_IOREG(VTSS_TO_OTP,0x23)

/**
 * \brief
 * DLE Setup Time before WEBNote: Default value for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TDLES_VAL . OTP_TDLES
 */
#define  VTSS_F_OTP_OTP_TDLES_VAL_OTP_TDLES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TDLES_VAL_OTP_TDLES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TDLES_VAL_OTP_TDLES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TWWL_VAL Register
 *
 * \details
 * OTP_TWWL_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TWWL_VAL
 */
#define VTSS_OTP_OTP_TWWL_VAL                VTSS_IOREG(VTSS_TO_OTP,0x24)

/**
 * \brief
 * Minimum WEB Low Pulse WidthNote: Default value for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TWWL_VAL . OTP_TWWL
 */
#define  VTSS_F_OTP_OTP_TWWL_VAL_OTP_TWWL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TWWL_VAL_OTP_TWWL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TWWL_VAL_OTP_TWWL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TDLEH_VAL Register
 *
 * \details
 * OTP_TDLEH_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TDLEH_VAL
 */
#define VTSS_OTP_OTP_TDLEH_VAL               VTSS_IOREG(VTSS_TO_OTP,0x25)

/**
 * \brief
 * DLE Hold Time after WEBNote: Default value for 25 MHz system clock
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TDLEH_VAL . OTP_TDLEH
 */
#define  VTSS_F_OTP_OTP_TDLEH_VAL_OTP_TDLEH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TDLEH_VAL_OTP_TDLEH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TDLEH_VAL_OTP_TDLEH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TWPED_VAL Register
 *
 * \details
 * OTP_TWPED_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TWPED_VAL
 */
#define VTSS_OTP_OTP_TWPED_VAL               VTSS_IOREG(VTSS_TO_OTP,0x26)

/**
 * \brief
 * WEB deassert to PGMEN assert DelayNote: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TWPED_VAL . OTP_TWPED
 */
#define  VTSS_F_OTP_OTP_TWPED_VAL_OTP_TWPED(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TWPED_VAL_OTP_TWPED     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TWPED_VAL_OTP_TWPED(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TPES_VAL Register
 *
 * \details
 * OTP_TPES_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TPES_VAL
 */
#define VTSS_OTP_OTP_TPES_VAL                VTSS_IOREG(VTSS_TO_OTP,0x27)

/**
 * \brief
 * PGMEN Setup Time before CPUMPENNote: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TPES_VAL . OTP_TPES
 */
#define  VTSS_F_OTP_OTP_TPES_VAL_OTP_TPES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TPES_VAL_OTP_TPES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TPES_VAL_OTP_TPES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TCPS_VAL Register
 *
 * \details
 * OTP_TCPS_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TCPS_VAL
 */
#define VTSS_OTP_OTP_TCPS_VAL                VTSS_IOREG(VTSS_TO_OTP,0x28)

/**
 * \brief
 * CPUMPEN Setup Time before WEB.Note: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TCPS_VAL . OTP_TCPS
 */
#define  VTSS_F_OTP_OTP_TCPS_VAL_OTP_TCPS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TCPS_VAL_OTP_TCPS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TCPS_VAL_OTP_TCPS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TCPH_VAL Register
 *
 * \details
 * OTP_TCPH_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TCPH_VAL
 */
#define VTSS_OTP_OTP_TCPH_VAL                VTSS_IOREG(VTSS_TO_OTP,0x29)

/**
 * \brief
 * W CPUMPEN Hold Time after WEB.Note: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TCPH_VAL . OTP_TCPH
 */
#define  VTSS_F_OTP_OTP_TCPH_VAL_OTP_TCPH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TCPH_VAL_OTP_TCPH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TCPH_VAL_OTP_TCPH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TPGMVFY_VAL Register
 *
 * \details
 * OTP_TPGMVFY_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TPGMVFY_VAL
 */
#define VTSS_OTP_OTP_TPGMVFY_VAL             VTSS_IOREG(VTSS_TO_OTP,0x2a)

/**
 * \brief
 * CPUMPEN deassert to Data Output Delay WEB value.Note: Default value for
 * 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TPGMVFY_VAL . OTP_TPGMVFY
 */
#define  VTSS_F_OTP_OTP_TPGMVFY_VAL_OTP_TPGMVFY(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TPGMVFY_VAL_OTP_TPGMVFY     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TPGMVFY_VAL_OTP_TPGMVFY(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TPEH_VAL Register
 *
 * \details
 * OTP_TPEH_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TPEH_VAL
 */
#define VTSS_OTP_OTP_TPEH_VAL                VTSS_IOREG(VTSS_TO_OTP,0x2b)

/**
 * \brief
 * PGMEN Hold time after CPUMPEN.Note: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TPEH_VAL . OTP_TPEH
 */
#define  VTSS_F_OTP_OTP_TPEH_VAL_OTP_TPEH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TPEH_VAL_OTP_TPEH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TPEH_VAL_OTP_TPEH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TPGRST_VAL Register
 *
 * \details
 * OTP_TPGRST_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TPGRST_VAL
 */
#define VTSS_OTP_OTP_TPGRST_VAL              VTSS_IOREG(VTSS_TO_OTP,0x2c)

/**
 * \brief
 * PGMEN Setup Time before RSTBNote: Default value for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TPGRST_VAL . OTP_TPGRST
 */
#define  VTSS_F_OTP_OTP_TPGRST_VAL_OTP_TPGRST(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TPGRST_VAL_OTP_TPGRST     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TPGRST_VAL_OTP_TPGRST(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TCLES_VAL Register
 *
 * \details
 * OTP_TCLES_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TCLES_VAL
 */
#define VTSS_OTP_OTP_TCLES_VAL               VTSS_IOREG(VTSS_TO_OTP,0x2d)

/**
 * \brief
 * CLE Setup Time before WEB.Note: Default value for 25 MHz system
 * clock.APPLICATION NOTE: The minimum value of this register must be large
 * enough to cover the value of tTWS.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TCLES_VAL . OTP_TCLES
 */
#define  VTSS_F_OTP_OTP_TCLES_VAL_OTP_TCLES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TCLES_VAL_OTP_TCLES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TCLES_VAL_OTP_TCLES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TCLEH_VAL Register
 *
 * \details
 * OTP_TCLEH_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TCLEH_VAL
 */
#define VTSS_OTP_OTP_TCLEH_VAL               VTSS_IOREG(VTSS_TO_OTP,0x2e)

/**
 * \brief
 * CLE Hold Time after WEB.Note: Default value for 25 MHz system
 * clock.APPLICATION NOTE: The minimum value of this register must be large
 * enough to cover the value of tTWH.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TCLEH_VAL . OTP_TCLEH
 */
#define  VTSS_F_OTP_OTP_TCLEH_VAL_OTP_TCLEH(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TCLEH_VAL_OTP_TCLEH     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TCLEH_VAL_OTP_TCLEH(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TRDES_VAL Register
 *
 * \details
 * OTP_TRDES_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TRDES_VAL
 */
#define VTSS_OTP_OTP_TRDES_VAL               VTSS_IOREG(VTSS_TO_OTP,0x2f)

/**
 * \brief
 * CPUMPEN Setup Time after WEB tCPS delay.This register is also used for
 * READEN setup time after WEB tRDESdelay.Note: Default value for 25 MHz
 * system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TRDES_VAL . OTP_TRDES
 */
#define  VTSS_F_OTP_OTP_TRDES_VAL_OTP_TRDES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TRDES_VAL_OTP_TRDES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TRDES_VAL_OTP_TRDES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TBCAAC_VAL Register
 *
 * \details
 * OTP_TBCAAC_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TBCAAC_VAL
 */
#define VTSS_OTP_OTP_TBCAAC_VAL              VTSS_IOREG(VTSS_TO_OTP,0x30)

/**
 * \brief
 * Address to Output Delay.Note: Default value for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TBCAAC_VAL . OTP_TBCAAC
 */
#define  VTSS_F_OTP_OTP_TBCAAC_VAL_OTP_TBCAAC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TBCAAC_VAL_OTP_TBCAAC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TBCAAC_VAL_OTP_TBCAAC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TAAC_VAL Register
 *
 * \details
 * OTP_TAAC_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TAAC_VAL
 */
#define VTSS_OTP_OTP_TAAC_VAL                VTSS_IOREG(VTSS_TO_OTP,0x31)

/**
 * \brief
 * Blank Check Address to Address change.Note: Default value for 25 MHz
 * system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TAAC_VAL . OTP_TAAC
 */
#define  VTSS_F_OTP_OTP_TAAC_VAL_OTP_TAAC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TAAC_VAL_OTP_TAAC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TAAC_VAL_OTP_TAAC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TACCT_VAL Register
 *
 * \details
 * OTP_TACCT_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TACCT_VAL
 */
#define VTSS_OTP_OTP_TACCT_VAL               VTSS_IOREG(VTSS_TO_OTP,0x32)

/**
 * \brief
 * Address to Test Output Delay.Note: Default value for 25 MHz system clock
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TACCT_VAL . OTP_TACCT
 */
#define  VTSS_F_OTP_OTP_TACCT_VAL_OTP_TACCT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TACCT_VAL_OTP_TACCT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TACCT_VAL_OTP_TACCT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TPWAD_VAL Register
 *
 * \details
 * OTP_TPWAD_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TPWAD_VAL
 */
#define VTSS_OTP_OTP_TPWAD_VAL               VTSS_IOREG(VTSS_TO_OTP,0x33)

/**
 * \brief
 * PWRRDY assertion to WAKEUP assertion DelayNote: Default value for 25 MHz
 * system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TPWAD_VAL . OTP_TPWAD
 */
#define  VTSS_F_OTP_OTP_TPWAD_VAL_OTP_TPWAD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TPWAD_VAL_OTP_TPWAD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TPWAD_VAL_OTP_TPWAD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TWCAD_VAL_HI Register
 *
 * \details
 * OTP_TWCAD_VAL_HI Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TWCAD_VAL_HI
 */
#define VTSS_OTP_OTP_TWCAD_VAL_HI            VTSS_IOREG(VTSS_TO_OTP,0x34)

/**
 * \brief
 * WAKEUP setup time for CEB assertionNote: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TWCAD_VAL_HI . OTP_TWCAD_15_8
 */
#define  VTSS_F_OTP_OTP_TWCAD_VAL_HI_OTP_TWCAD_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TWCAD_VAL_HI_OTP_TWCAD_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TWCAD_VAL_HI_OTP_TWCAD_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TWCAD_VAL_LO Register
 *
 * \details
 * OTP_TWCAD_VAL_LO Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TWCAD_VAL_LO
 */
#define VTSS_OTP_OTP_TWCAD_VAL_LO            VTSS_IOREG(VTSS_TO_OTP,0x35)

/**
 * \brief
 * WAKEUP setup time for CEB assertionNote: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TWCAD_VAL_LO . OTP_TWCAD_7_0
 */
#define  VTSS_F_OTP_OTP_TWCAD_VAL_LO_OTP_TWCAD_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TWCAD_VAL_LO_OTP_TWCAD_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TWCAD_VAL_LO_OTP_TWCAD_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TAS_VAL Register
 *
 * \details
 * OTP_TAS_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TAS_VAL
 */
#define VTSS_OTP_OTP_TAS_VAL                 VTSS_IOREG(VTSS_TO_OTP,0x36)

/**
 * \brief
 * (Not currently used) Address Setup Time before WEBNote: Default value
 * for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TAS_VAL . OTP_TAS
 */
#define  VTSS_F_OTP_OTP_TAS_VAL_OTP_TAS(x)    VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TAS_VAL_OTP_TAS       VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TAS_VAL_OTP_TAS(x)    VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TDS_VAL Register
 *
 * \details
 * OTP_TDS_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TDS_VAL
 */
#define VTSS_OTP_OTP_TDS_VAL                 VTSS_IOREG(VTSS_TO_OTP,0x37)

/**
 * \brief
 * (Not currently used) Data Setup Time before WEBNote: Default value for
 * 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TDS_VAL . OTP_TDS
 */
#define  VTSS_F_OTP_OTP_TDS_VAL_OTP_TDS(x)    VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TDS_VAL_OTP_TDS       VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TDS_VAL_OTP_TDS(x)    VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TPVSR_VAL Register
 *
 * \details
 * OTP_TPVSR_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TPVSR_VAL
 */
#define VTSS_OTP_OTP_TPVSR_VAL               VTSS_IOREG(VTSS_TO_OTP,0x3a)

/**
 * \brief
 * Setup Time Before READEN.Note: Default value for 25 MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TPVSR_VAL . OTP_TPVSR
 */
#define  VTSS_F_OTP_OTP_TPVSR_VAL_OTP_TPVSR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TPVSR_VAL_OTP_TPVSR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TPVSR_VAL_OTP_TPVSR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TVHR_VAL Register
 *
 * \details
 * OTP_TVHR_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TVHR_VAL
 */
#define VTSS_OTP_OTP_TVHR_VAL                VTSS_IOREG(VTSS_TO_OTP,0x3b)

/**
 * \brief
 * OTP PGMVFY Hold Time After READEN.Note: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TVHR_VAL . OTP_TPVHR
 */
#define  VTSS_F_OTP_OTP_TVHR_VAL_OTP_TPVHR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TVHR_VAL_OTP_TPVHR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TVHR_VAL_OTP_TPVHR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TPGMAS_VAL Register
 *
 * \details
 * OTP_TPGMAS_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TPGMAS_VAL
 */
#define VTSS_OTP_OTP_TPGMAS_VAL              VTSS_IOREG(VTSS_TO_OTP,0x3c)

/**
 * \brief
 * PGMEN Setup Time before Next Address.Note: Default value for 25 MHz
 * system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TPGMAS_VAL . OTP_TPGMAS
 */
#define  VTSS_F_OTP_OTP_TPGMAS_VAL_OTP_TPGMAS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TPGMAS_VAL_OTP_TPGMAS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TPGMAS_VAL_OTP_TPGMAS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TCWDD_VAL Register
 *
 * \details
 * OTP_TCWDD_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TCWDD_VAL
 */
#define VTSS_OTP_OTP_TCWDD_VAL               VTSS_IOREG(VTSS_TO_OTP,0x3d)

/**
 * \brief
 * CEB Deassertion to WAKEUP deassertion DelayNote: Default value for 25
 * MHz system clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TCWDD_VAL . OTP_TCWDD
 */
#define  VTSS_F_OTP_OTP_TCWDD_VAL_OTP_TCWDD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TCWDD_VAL_OTP_TCWDD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TCWDD_VAL_OTP_TCWDD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TCPRD_VAL Register
 *
 * \details
 * OTP_TCPRD_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TCPRD_VAL
 */
#define VTSS_OTP_OTP_TCPRD_VAL               VTSS_IOREG(VTSS_TO_OTP,0x40)

/**
 * \brief
 * CPUMPEN Setup Time before READENNote: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TCPRD_VAL . OTP_TCPRD
 */
#define  VTSS_F_OTP_OTP_TCPRD_VAL_OTP_TCPRD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TCPRD_VAL_OTP_TCPRD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TCPRD_VAL_OTP_TCPRD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_TRDCP_VAL Register
 *
 * \details
 * OTP_TRDCP_VAL Register
 *
 * Register: \a OTP:OTP_REGS:OTP_TRDCP_VAL
 */
#define VTSS_OTP_OTP_TRDCP_VAL               VTSS_IOREG(VTSS_TO_OTP,0x41)

/**
 * \brief
 * CPUMPEN Hold Time after READENNote: Default value for 25 MHz system
 * clock.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_TRDCP_VAL . OTP_TRDCP
 */
#define  VTSS_F_OTP_OTP_TRDCP_VAL_OTP_TRDCP(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_TRDCP_VAL_OTP_TRDCP     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_TRDCP_VAL_OTP_TRDCP(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_NP1_VAL Register
 *
 * \details
 * OTP_NP1_VAL Register
 * (RESET=0X0002)
 *
 * Register: \a OTP:OTP_REGS:OTP_NP1_VAL
 */
#define VTSS_OTP_OTP_NP1_VAL                 VTSS_IOREG(VTSS_TO_OTP,0x45)

/**
 * \brief
 * (NP1 +1) = Number of initial programming pulses.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_NP1_VAL . OTP_NP1
 */
#define  VTSS_F_OTP_OTP_NP1_VAL_OTP_NP1(x)    VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OTP_OTP_NP1_VAL_OTP_NP1       VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_OTP_OTP_NP1_VAL_OTP_NP1(x)    VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief OTP_NP2_VAL Register
 *
 * \details
 * OTP_NP2_VAL Register
 * (RESET=0X0000)
 *
 * Register: \a OTP:OTP_REGS:OTP_NP2_VAL
 */
#define VTSS_OTP_OTP_NP2_VAL                 VTSS_IOREG(VTSS_TO_OTP,0x46)

/**
 * \brief
 * (NP2 +1) = Number of additional programming pulses
 *
 * \details
 * Field: ::VTSS_OTP_OTP_NP2_VAL . OTP_NP2
 */
#define  VTSS_F_OTP_OTP_NP2_VAL_OTP_NP2(x)    VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OTP_OTP_NP2_VAL_OTP_NP2       VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_OTP_OTP_NP2_VAL_OTP_NP2(x)    VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief OTP_READ_PROTECT Register
 *
 * \details
 * OTP_READ_PROTECT Register
 * (RESET=0X0000_0000)
 * OTP read locking is used to protect private keys stored in OTP such as
 * the JTAG key after the Boot ROM has accessed
 * them.
 *
 * Register: \a OTP:OTP_REGS:OTP_READ_PROTECT0
 */
#define VTSS_OTP_OTP_READ_PROTECT0           VTSS_IOREG(VTSS_TO_OTP,0x80)

/**
 * \brief
 * Each bit in the OTP_READ_PROTECT[7:0] field corresponds to aregion of
 * OTP memory with bit 0 = region 0, bit 1 = region 1 etc.Writing a '1' to
 * a bit in the OTP_READ_PROTECT[7:0] field blocksthe corresponding OTP
 * region from being read.A value of zero is returned when a protected area
 * is read.Note: The bits in theOTP_READ_PROTECT.OTP_WRITE_PROTECT[7:0]
 * fieldare only valid if the corresponding bits in
 * theOTP_WRITE_PROTECT.OTP_WRITE_PROTECT[7:0]field are also set.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_READ_PROTECT0 . OTP_READ_PROTECT_7_0
 */
#define  VTSS_F_OTP_OTP_READ_PROTECT0_OTP_READ_PROTECT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_READ_PROTECT0_OTP_READ_PROTECT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_READ_PROTECT0_OTP_READ_PROTECT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_READ_PROTECT Register
 *
 * \details
 * OTP_READ_PROTECT Register
 * (RESET=0X0000_0000)
 * OTP read locking is used to protect private keys stored in OTP such as
 * the JTAG key after the Boot ROM has accessed
 * them.
 *
 * Register: \a OTP:OTP_REGS:OTP_READ_PROTECT1
 */
#define VTSS_OTP_OTP_READ_PROTECT1           VTSS_IOREG(VTSS_TO_OTP,0x81)

/**
 * \brief
 * Each bit in the OTP_READ_PROTECT[15:8] field corresponds to aregion of
 * OTP memory with bit 0 = region 0, bit 1 = region 1 etc.Writing a '1' to
 * a bit in the OTP_READ_PROTECT[15:8] field blocksthe corresponding OTP
 * region from being read.A value of zero is returned when a protected area
 * is read.Note: The bits in theOTP_READ_PROTECT.OTP_WRITE_PROTECT[15:8]
 * fieldare only valid if the corresponding bits in
 * theOTP_WRITE_PROTECT.OTP_WRITE_PROTECT[15:8]field are also set.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_READ_PROTECT1 . OTP_READ_PROTECT_15_8
 */
#define  VTSS_F_OTP_OTP_READ_PROTECT1_OTP_READ_PROTECT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_READ_PROTECT1_OTP_READ_PROTECT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_READ_PROTECT1_OTP_READ_PROTECT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_READ_PROTECT Register
 *
 * \details
 * OTP_READ_PROTECT Register
 * (RESET=0X0000_0000)
 * OTP read locking is used to protect private keys stored in OTP such as
 * the JTAG key after the Boot ROM has accessed
 * them.
 *
 * Register: \a OTP:OTP_REGS:OTP_READ_PROTECT2
 */
#define VTSS_OTP_OTP_READ_PROTECT2           VTSS_IOREG(VTSS_TO_OTP,0x82)

/**
 * \brief
 * Each bit in the OTP_READ_PROTECT[23:16] field corresponds to aregion of
 * OTP memory with bit 0 = region 0, bit 1 = region 1 etc.Writing a '1' to
 * a bit in the OTP_READ_PROTECT[23:16] field blocksthe corresponding OTP
 * region from being read.A value of zero is returned when a protected area
 * is read.Note: The bits in theOTP_READ_PROTECT.OTP_WRITE_PROTECT[23:16]
 * fieldare only valid if the corresponding bits in
 * theOTP_WRITE_PROTECT.OTP_WRITE_PROTECT[23:16]field are also set.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_READ_PROTECT2 . OTP_READ_PROTECT_23_16
 */
#define  VTSS_F_OTP_OTP_READ_PROTECT2_OTP_READ_PROTECT_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_READ_PROTECT2_OTP_READ_PROTECT_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_READ_PROTECT2_OTP_READ_PROTECT_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OTP_READ_PROTECT Register
 *
 * \details
 * OTP_READ_PROTECT Register
 * (RESET=0X0000_0000)
 * OTP read locking is used to protect private keys stored in OTP such as
 * the JTAG key after the Boot ROM has accessed
 * them.
 *
 * Register: \a OTP:OTP_REGS:OTP_READ_PROTECT3
 */
#define VTSS_OTP_OTP_READ_PROTECT3           VTSS_IOREG(VTSS_TO_OTP,0x83)

/**
 * \brief
 * Each bit in the OTP_READ_PROTECT[31:24] field corresponds to aregion of
 * OTP memory with bit 0 = region 0, bit 1 = region 1 etc.Writing a '1' to
 * a bit in the OTP_READ_PROTECT[31:24] field blocksthe corresponding OTP
 * region from being read.A value of zero is returned when a protected area
 * is read.Note: The bits in theOTP_READ_PROTECT.OTP_WRITE_PROTECT[31:24]
 * fieldare only valid if the corresponding bits in
 * theOTP_WRITE_PROTECT.OTP_WRITE_PROTECT[31:24]field are also set.
 *
 * \details
 * Field: ::VTSS_OTP_OTP_READ_PROTECT3 . OTP_READ_PROTECT_31_24
 */
#define  VTSS_F_OTP_OTP_READ_PROTECT3_OTP_READ_PROTECT_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OTP_OTP_READ_PROTECT3_OTP_READ_PROTECT_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OTP_OTP_READ_PROTECT3_OTP_READ_PROTECT_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Control for OTP emulation model
 *
 * \details
 * Register: \a OTP:OTP_REGS:OTP_FPGA_PROM_CTL
 */
#define VTSS_OTP_OTP_FPGA_PROM_CTL           VTSS_IOREG(VTSS_TO_OTP,0xc0)

/**
 * \brief
 * Control for OTP emulation model - prom is busy
 *
 * \details
 * Field: ::VTSS_OTP_OTP_FPGA_PROM_CTL . FPGA_OTP_PROM_BUSY
 */
#define  VTSS_F_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_PROM_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_PROM_BUSY  VTSS_BIT(3)
#define  VTSS_X_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_PROM_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Control for OTP emulation model - clear all OTP data
 *
 * \details
 * Field: ::VTSS_OTP_OTP_FPGA_PROM_CTL . FPGA_OTP_CLR_PROM
 */
#define  VTSS_F_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_CLR_PROM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_CLR_PROM  VTSS_BIT(2)
#define  VTSS_X_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_CLR_PROM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Control for OTP emulation model - Error injection control
 *
 * \details
 * fpga_otp_prom_err_ctl[1:0]	Error
 *	   2'b00		 No errors. If tPGM > OTP_PROG_TIME all
 * writes
 *				    will be successful.
 *	   2'b01		 Inject (pseudo) random errors at normal
 * rate
 *	   2'b10		 Inject (pseudo) random errors at higher
 * rate
 *	   2'b11		 All writes will fail regardless of tPGM.
 *
 * Field: ::VTSS_OTP_OTP_FPGA_PROM_CTL . FPGA_OTP_PROM_ERR_CTL
 */
#define  VTSS_F_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_PROM_ERR_CTL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_PROM_ERR_CTL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_OTP_OTP_FPGA_PROM_CTL_FPGA_OTP_PROM_ERR_CTL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_LAGUNA_REGS_OTP_H_ */
