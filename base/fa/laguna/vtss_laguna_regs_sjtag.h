// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_SJTAG_H_
#define _VTSS_LAGUNA_REGS_SJTAG_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a SJTAG
 *
 * Provides secure access over JTAG through authentication
 *
 ***********************************************************************/

/**
 * Register Group: \a SJTAG:SJTAG_REGS
 *
 * Not documented
 */


/**
 * \brief Secure JTAG Control Register
 *
 * \details
 * Register: \a SJTAG:SJTAG_REGS:CTL
 */
#define VTSS_SJTAG_CTL                       VTSS_IOREG(VTSS_TO_SJTAG,0x0)

/**
 * \brief
 * When set the SJTAG block is not affected by a chiplevel reset.The state
 * of SJTAG is maintained.The state of the SJTAG CSRs does not change.This
 * bit shall only be set by FW when the SJTAG controller is in the Open
 * state.Note: TRST and TMS reset do not affect the SJTAG registers.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . BLOCK_RESET
 */
#define  VTSS_F_SJTAG_CTL_BLOCK_RESET(x)      VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SJTAG_CTL_BLOCK_RESET         VTSS_BIT(31)
#define  VTSS_X_SJTAG_CTL_BLOCK_RESET(x)      VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * Indicates the lock status of SJTAG.
 *
 * \details
 * 0: Locked
 * 1: Unlocked
 *
 * Field: ::VTSS_SJTAG_CTL . SJTAG_UNLOCK_STS
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_UNLOCK_STS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SJTAG_CTL_SJTAG_UNLOCK_STS    VTSS_BIT(11)
#define  VTSS_X_SJTAG_CTL_SJTAG_UNLOCK_STS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Indicates the status of SJTAG.
 *
 * \details
 * 00: Open
 * 01: Secure Mode 1
 * 10: Secure Mode 2
 * 11: Closed
 *
 * Field: ::VTSS_SJTAG_CTL . SJTAG_MODE_STS
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_MODE_STS(x)   VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_SJTAG_CTL_SJTAG_MODE_STS      VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_SJTAG_CTL_SJTAG_MODE_STS(x)   VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * When set the units for the SJTAG_HC_TO register is reduced to us.This
 * value is locked after the SJTAG_FREEZE bit is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . SJTAG_HC_TO_UNITS_DBG
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_HC_TO_UNITS_DBG(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SJTAG_CTL_SJTAG_HC_TO_UNITS_DBG  VTSS_BIT(8)
#define  VTSS_X_SJTAG_CTL_SJTAG_HC_TO_UNITS_DBG(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When set the SJTAG controller implements a time-out between the
 * reception of the READ_NONCE command and HC_RESP command.This value is
 * locked after the SJTAG_FREEZE bit is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . SJTAG_HC_TO_EN
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_HC_TO_EN(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SJTAG_CTL_SJTAG_HC_TO_EN      VTSS_BIT(7)
#define  VTSS_X_SJTAG_CTL_SJTAG_HC_TO_EN(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * When set HW automatically compares the received host digest
 * (SJTAG_HOST_DIGEST) to the programmed device digest (SJTAG_DEV_DIGEST)
 * and unlocks both JTAG controllers automatically ifboth values match.This
 * value is locked after the SJTAG_FREEZE bit is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . SJTAG_DIGEST_CMP
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_DIGEST_CMP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SJTAG_CTL_SJTAG_DIGEST_CMP    VTSS_BIT(6)
#define  VTSS_X_SJTAG_CTL_SJTAG_DIGEST_CMP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * When set the following bits and fields can not be modified by FW.-
 * SJTAG_CPU_EN bit- SJTAG_TST_EN bit- SJTAG_HC_TO_UNITS_DBG bit-
 * SJTAG_HC_TO_EN bit- SJTAG_DIGEST_CMP bit- SJTAG_MODE field- SJTAG_NONCE
 * register- SJTAG_DEVICE_DIGEST register- SJTAG_UID register- SJTAG_HC_TO
 * registerThis bit can only be set by FW. FW can not clear this bit. The
 * only way toclear this bit is via a chip level reset.The SJTAG_CPU_EN and
 * SJTAG_TST_EN bits can still have their statechanged by the SJTAG
 * controller.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . SJTAG_FREEZE
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_FREEZE(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SJTAG_CTL_SJTAG_FREEZE        VTSS_BIT(5)
#define  VTSS_X_SJTAG_CTL_SJTAG_FREEZE(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * the secure JTAG mode programmed in OTP.SJTAG controller uses this value
 * to determine how to configure SJTAG_CPU_EN and SJTAG_TST_EN when secure
 * JTAG is enabled and a successful authentication has occurred.This value
 * is locked after the SJTAG_FREEZE bit is set.Note: The SJTAG_MODE
 * register is also be updated directly via the HW_IF for products that use
 * this function.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . SJTAG_MODE
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_MODE(x)       VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_SJTAG_CTL_SJTAG_MODE          VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_SJTAG_CTL_SJTAG_MODE(x)       VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * When set the secure JTAG function is enabled by FW. The secure JTAG
 * controlled is able to process the SJTAG commands.This bit shall only be
 * set after the NONCE value, UUID and digest result have been programmed.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . SJTAG_EN
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_EN(x)         VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SJTAG_CTL_SJTAG_EN            VTSS_BIT(2)
#define  VTSS_X_SJTAG_CTL_SJTAG_EN(x)         VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * When set the CPU JTAG controller is enabled.The state of this bit can
 * automatically be set by HW when SJTAG_DIGEST_CMP is set and the
 * comparison is successful.This value is locked from FW updated after the
 * SJTAG_FREEZE bit is set.Note: When the SJTAG_MODE register is updated
 * directly via the HW_IF this bit shall also be automatically updated by
 * HW.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . SJTAG_CPU_EN
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_CPU_EN(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SJTAG_CTL_SJTAG_CPU_EN        VTSS_BIT(1)
#define  VTSS_X_SJTAG_CTL_SJTAG_CPU_EN(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When set the test JTAG controller is enabled.The state of this bit can
 * automatically be set by HW when SJTAG_DIGEST_CMP is set and the
 * comparison is successful.This value is locked from FW updated after the
 * SJTAG_FREEZE bit is set.Note: When the SJTAG_MODE register is updated
 * directly via the HW_IF this bit shall also be automatically updated by
 * HW.
 *
 * \details
 * Field: ::VTSS_SJTAG_CTL . SJTAG_TST_EN
 */
#define  VTSS_F_SJTAG_CTL_SJTAG_TST_EN(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SJTAG_CTL_SJTAG_TST_EN        VTSS_BIT(0)
#define  VTSS_X_SJTAG_CTL_SJTAG_TST_EN(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Secure JTAG Interrupt Status Register
 *
 * \details
 * Register: \a SJTAG:SJTAG_REGS:INT_STATUS
 */
#define VTSS_SJTAG_INT_STATUS                VTSS_IOREG(VTSS_TO_SJTAG,0x1)

/**
 * \brief
 * Set when the TO enforcement between issuing READ_NONCE and HC_RESP has
 * been violated.Note: This bit will not be updated by HW until SJTAG_EN is
 * set.
 *
 * \details
 * Field: ::VTSS_SJTAG_INT_STATUS . SJTAG_TO_STS
 */
#define  VTSS_F_SJTAG_INT_STATUS_SJTAG_TO_STS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SJTAG_INT_STATUS_SJTAG_TO_STS  VTSS_BIT(7)
#define  VTSS_X_SJTAG_INT_STATUS_SJTAG_TO_STS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set by HW to indicate a READ_UUID command has been received by the
 * Secure JTAG controller.Note: This bit will not be updated by HW until
 * SJTAG_EN is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_INT_STATUS . SJTAG_READ_UUID_RX
 */
#define  VTSS_F_SJTAG_INT_STATUS_SJTAG_READ_UUID_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SJTAG_INT_STATUS_SJTAG_READ_UUID_RX  VTSS_BIT(6)
#define  VTSS_X_SJTAG_INT_STATUS_SJTAG_READ_UUID_RX(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set by HW to indicate an READ_MODE command has been received by the
 * secure JTAG controller.Note: This bit will not be updated by HW until
 * SJTAG_EN is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_INT_STATUS . SJTAG_READ_MODE_RX
 */
#define  VTSS_F_SJTAG_INT_STATUS_SJTAG_READ_MODE_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SJTAG_INT_STATUS_SJTAG_READ_MODE_RX  VTSS_BIT(5)
#define  VTSS_X_SJTAG_INT_STATUS_SJTAG_READ_MODE_RX(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set by HW to indicate that the HC digest received from the host, stored
 * in SJTAG_HOST_DIGEST, does not match the pre-calculated HC' stored in
 * the SJTAG_DEV_DIGEST.
 *
 * \details
 * Field: ::VTSS_SJTAG_INT_STATUS . SJTAG_DIGEST_FAIL
 */
#define  VTSS_F_SJTAG_INT_STATUS_SJTAG_DIGEST_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SJTAG_INT_STATUS_SJTAG_DIGEST_FAIL  VTSS_BIT(4)
#define  VTSS_X_SJTAG_INT_STATUS_SJTAG_DIGEST_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set by HW to indicate that the HC digest received from the host, stored
 * in SJTAG_HOST_DIGEST, matches the pre-calculated HC' stored in the
 * SJTAG_DEV_DIGEST.When SJTAG is enabled this results in HW automatically
 * updating the SJTAG_CPU_EN and SJTAG_TST_EN bits as well as the
 * SJTAG_UNLOCK_STS field.Note: This bit will not be updated by HW until
 * SJTAG_EN is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_INT_STATUS . SJTAG_DIGEST_PASS
 */
#define  VTSS_F_SJTAG_INT_STATUS_SJTAG_DIGEST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SJTAG_INT_STATUS_SJTAG_DIGEST_PASS  VTSS_BIT(3)
#define  VTSS_X_SJTAG_INT_STATUS_SJTAG_DIGEST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set by HW to indicate a READ_NONCE command has been received by the JTAG
 * controller and responded to.Note: This bit will not be updated by HW
 * until SJTAG_EN is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_INT_STATUS . SJTAG_READ_NONCE_RX
 */
#define  VTSS_F_SJTAG_INT_STATUS_SJTAG_READ_NONCE_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SJTAG_INT_STATUS_SJTAG_READ_NONCE_RX  VTSS_BIT(2)
#define  VTSS_X_SJTAG_INT_STATUS_SJTAG_READ_NONCE_RX(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set by HW to indicate the HC_RESP command and host digest have been
 * received over JTAG and stored in the SJTAG_HOST_DIGEST registers.Note:
 * This bit will not be updated by HW until SJTAG_EN is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_INT_STATUS . SJTAG_DIGEST_RX
 */
#define  VTSS_F_SJTAG_INT_STATUS_SJTAG_DIGEST_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SJTAG_INT_STATUS_SJTAG_DIGEST_RX  VTSS_BIT(1)
#define  VTSS_X_SJTAG_INT_STATUS_SJTAG_DIGEST_RX(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set by HW to indicate an UNLOCK command has been received by the secure
 * JTAG controller.Note: This bit will not be updated by HW until SJTAG_EN
 * is set. The UNLOCK command will be responded to regardless of the
 * SJTAG_EN state.
 *
 * \details
 * Field: ::VTSS_SJTAG_INT_STATUS . SJTAG_UNLOCK_RX
 */
#define  VTSS_F_SJTAG_INT_STATUS_SJTAG_UNLOCK_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SJTAG_INT_STATUS_SJTAG_UNLOCK_RX  VTSS_BIT(0)
#define  VTSS_X_SJTAG_INT_STATUS_SJTAG_UNLOCK_RX(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Secure JTAG Interrupt Mask Register
 *
 * \details
 * Register: \a SJTAG:SJTAG_REGS:INT_MASK
 */
#define VTSS_SJTAG_INT_MASK                  VTSS_IOREG(VTSS_TO_SJTAG,0x2)

/**
 * \details
 * 0 = Interrupt enabled
 * 1 = Interrupt disabled
 *
 * Field: ::VTSS_SJTAG_INT_MASK . SJTAG_TO_STS_MSK
 */
#define  VTSS_F_SJTAG_INT_MASK_SJTAG_TO_STS_MSK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SJTAG_INT_MASK_SJTAG_TO_STS_MSK  VTSS_BIT(7)
#define  VTSS_X_SJTAG_INT_MASK_SJTAG_TO_STS_MSK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * 0 = Interrupt enabled
 * 1 = Interrupt disabled
 *
 * Field: ::VTSS_SJTAG_INT_MASK . SJTAG_UUID_RX_MSK
 */
#define  VTSS_F_SJTAG_INT_MASK_SJTAG_UUID_RX_MSK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SJTAG_INT_MASK_SJTAG_UUID_RX_MSK  VTSS_BIT(6)
#define  VTSS_X_SJTAG_INT_MASK_SJTAG_UUID_RX_MSK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * 0 = Interrupt enabled
 * 1 = Interrupt disabled
 *
 * Field: ::VTSS_SJTAG_INT_MASK . SJTAG_READ_MODE_RX_MSK
 */
#define  VTSS_F_SJTAG_INT_MASK_SJTAG_READ_MODE_RX_MSK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SJTAG_INT_MASK_SJTAG_READ_MODE_RX_MSK  VTSS_BIT(5)
#define  VTSS_X_SJTAG_INT_MASK_SJTAG_READ_MODE_RX_MSK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * 0 = Interrupt enabled
 * 1 = Interrupt disabled
 *
 * Field: ::VTSS_SJTAG_INT_MASK . SJTAG_DIGEST_FAIL_MSK
 */
#define  VTSS_F_SJTAG_INT_MASK_SJTAG_DIGEST_FAIL_MSK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SJTAG_INT_MASK_SJTAG_DIGEST_FAIL_MSK  VTSS_BIT(4)
#define  VTSS_X_SJTAG_INT_MASK_SJTAG_DIGEST_FAIL_MSK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * 0 = Interrupt enabled
 * 1 = Interrupt disabled
 *
 * Field: ::VTSS_SJTAG_INT_MASK . SJTAG_DIGEST_PASS_MSK
 */
#define  VTSS_F_SJTAG_INT_MASK_SJTAG_DIGEST_PASS_MSK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SJTAG_INT_MASK_SJTAG_DIGEST_PASS_MSK  VTSS_BIT(3)
#define  VTSS_X_SJTAG_INT_MASK_SJTAG_DIGEST_PASS_MSK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * 0 = Interrupt enabled
 * 1 = Interrupt disabled
 *
 * Field: ::VTSS_SJTAG_INT_MASK . SJTAG_NONCE_RX_MSK
 */
#define  VTSS_F_SJTAG_INT_MASK_SJTAG_NONCE_RX_MSK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SJTAG_INT_MASK_SJTAG_NONCE_RX_MSK  VTSS_BIT(2)
#define  VTSS_X_SJTAG_INT_MASK_SJTAG_NONCE_RX_MSK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * 0 = Interrupt enabled
 * 1 = Interrupt disabled
 *
 * Field: ::VTSS_SJTAG_INT_MASK . SJTAG_DIGEST_RX_MSK
 */
#define  VTSS_F_SJTAG_INT_MASK_SJTAG_DIGEST_RX_MSK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SJTAG_INT_MASK_SJTAG_DIGEST_RX_MSK  VTSS_BIT(1)
#define  VTSS_X_SJTAG_INT_MASK_SJTAG_DIGEST_RX_MSK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * 0 = Interrupt enabled
 * 1 = Interrupt disabled
 *
 * Field: ::VTSS_SJTAG_INT_MASK . SJTAG_UNLOCK_RX_MSK
 */
#define  VTSS_F_SJTAG_INT_MASK_SJTAG_UNLOCK_RX_MSK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SJTAG_INT_MASK_SJTAG_UNLOCK_RX_MSK  VTSS_BIT(0)
#define  VTSS_X_SJTAG_INT_MASK_SJTAG_UNLOCK_RX_MSK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Secure JTAG NONCE Register
 *
 * \details
 * NONCE[0]: 31:0
 * NONCE[1]: 63:32
 * NONCE[2]: 95:64
 * NONCE[3]: 127:96
 * NONCE[4]: 159:128
 * NONCE[5]: 191:160
 * NONCE[6]: 223:192
 * NONCE[7]: 255:224
 *
 * Register: \a SJTAG:SJTAG_REGS:NONCE
 *
 * @param ri Register: NONCE (??), 0-7
 */
#define VTSS_SJTAG_NONCE(ri)                 VTSS_IOREG(VTSS_TO_SJTAG,0x4 + (ri))

/**
 * \brief
 * Random number used in the host challenge.This value is locked after the
 * SJTAG_FREEZE bit is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_NONCE . SJTAG_NONCE
 */
#define  VTSS_F_SJTAG_NONCE_SJTAG_NONCE(x)    (x)
#define  VTSS_M_SJTAG_NONCE_SJTAG_NONCE       0xffffffff
#define  VTSS_X_SJTAG_NONCE_SJTAG_NONCE(x)    (x)


/**
 * \brief Secure JTAG Host Digest Register
 *
 * \details
 * HOST_DIGEST[0]: 31:0
 * HOST_DIGEST[1]: 63:32
 * HOST_DIGEST[2]: 95:64
 * HOST_DIGEST[3]: 127:96
 * HOST_DIGEST[4]: 159:128
 * HOST_DIGEST[5]: 191:160
 * HOST_DIGEST[6]: 223:192
 * HOST_DIGEST[7]: 255:224
 *
 * Register: \a SJTAG:SJTAG_REGS:HOST_DIGEST
 *
 * @param ri Register: HOST_DIGEST (??), 0-7
 */
#define VTSS_SJTAG_HOST_DIGEST(ri)           VTSS_IOREG(VTSS_TO_SJTAG,0xc + (ri))

/**
 * \brief
 * This register stores the digest received from the host in response to
 * the HC_RESP command.The value in this register is valid after the
 * SJTAG_DIGEST_RX status bit is set by the SJTAG controller.
 *
 * \details
 * Field: ::VTSS_SJTAG_HOST_DIGEST . SJTAG_HOST_DIGEST
 */
#define  VTSS_F_SJTAG_HOST_DIGEST_SJTAG_HOST_DIGEST(x)  (x)
#define  VTSS_M_SJTAG_HOST_DIGEST_SJTAG_HOST_DIGEST     0xffffffff
#define  VTSS_X_SJTAG_HOST_DIGEST_SJTAG_HOST_DIGEST(x)  (x)


/**
 * \brief Secure JTAG Device Digest Register
 *
 * \details
 * DEVICE_DIGEST[0]: 31:0
 * DEVICE_DIGEST[1]: 63:32
 * DEVICE_DIGEST[2]: 95:64
 * DEVICE_DIGEST[3]: 127:96
 * DEVICE_DIGEST[4]: 159:128
 * DEVICE_DIGEST[5]: 191:160
 * DEVICE_DIGEST[6]: 223:192
 * DEVICE_DIGEST[7]: 255:224
 *
 * Register: \a SJTAG:SJTAG_REGS:DEVICE_DIGEST
 *
 * @param ri Register: DEVICE_DIGEST (??), 0-7
 */
#define VTSS_SJTAG_DEVICE_DIGEST(ri)         VTSS_IOREG(VTSS_TO_SJTAG,0x14 + (ri))

/**
 * \brief
 * This register stores the pre-calculated digest, HR', by FW.This value is
 * locked after the SJTAG_FREEZE bit is set by FW.This register shall
 * always read-back 0h after the SJTAG_FREEZE bit is set by FW.
 *
 * \details
 * Field: ::VTSS_SJTAG_DEVICE_DIGEST . SJTAG_DEVICE_DIGEST
 */
#define  VTSS_F_SJTAG_DEVICE_DIGEST_SJTAG_DEVICE_DIGEST(x)  (x)
#define  VTSS_M_SJTAG_DEVICE_DIGEST_SJTAG_DEVICE_DIGEST     0xffffffff
#define  VTSS_X_SJTAG_DEVICE_DIGEST_SJTAG_DEVICE_DIGEST(x)  (x)


/**
 * \brief Secure JTAG UUID Register
 *
 * \details
 * UUID[0]: 31:0
 * UUID[1]: 63:32
 * UUID[2]: 79:64
 *
 * Register: \a SJTAG:SJTAG_REGS:UUID
 *
 * @param ri Register: UUID (??), 0-2
 */
#define VTSS_SJTAG_UUID(ri)                  VTSS_IOREG(VTSS_TO_SJTAG,0x1c + (ri))

/**
 * \brief
 * This register stores the device's UUID.This value is locked after the
 * SJTAG_FREEZE bit is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_UUID . SJTAG_UUID
 */
#define  VTSS_F_SJTAG_UUID_SJTAG_UUID(x)      (x)
#define  VTSS_M_SJTAG_UUID_SJTAG_UUID         0xffffffff
#define  VTSS_X_SJTAG_UUID_SJTAG_UUID(x)      (x)


/**
 * \brief Secure JTAG Host Challenge TO Register
 *
 * \details
 * Register: \a SJTAG:SJTAG_REGS:HC_TO
 */
#define VTSS_SJTAG_HC_TO                     VTSS_IOREG(VTSS_TO_SJTAG,0x20)

/**
 * \brief
 * This register indicate the amount of time in which the host must send
 * the HC_RESP command after READ_NONCE command has been responded to by
 * the SJTAG controller.This register has unit of 1 ms.This value is locked
 * after the SJTAG_FREEZE bit is set.
 *
 * \details
 * Field: ::VTSS_SJTAG_HC_TO . SJTAG_HC_TO
 */
#define  VTSS_F_SJTAG_HC_TO_SJTAG_HC_TO(x)    (x)
#define  VTSS_M_SJTAG_HC_TO_SJTAG_HC_TO       0xffffffff
#define  VTSS_X_SJTAG_HC_TO_SJTAG_HC_TO(x)    (x)


#endif /* _VTSS_LAGUNA_REGS_SJTAG_H_ */
