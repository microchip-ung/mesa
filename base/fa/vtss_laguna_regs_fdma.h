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

#ifndef _VTSS_LAGUNA_REGS_FDMA_H_
#define _VTSS_LAGUNA_REGS_FDMA_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a FDMA
 *
 * This target contains registers for configuring and controlling the logic
 * related to the parallel Frame DMA engine.
 *
 ***********************************************************************/

/**
 * Register Group: \a FDMA:FDMA
 *
 * Parallel Frame DMA
 */


/**
 * \brief Activate specific channels
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_ACTIVATE
 */
#define VTSS_FDMA_FDMA_CH_ACTIVATE           VTSS_IOREG(VTSS_TO_FDMA,0x2)

/**
 * \brief
 * Set to activate specific FDMA channels, there is one bit per channel.
 * The corresponding LLP pointer must be configured prior to activating a
 * channel, see FDMA:FDMA:FDMA_DCB_LLP for more information. Bits in this
 * field are cleared immediately when set.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_ACTIVATE . CH_ACTIVATE
 */
#define  VTSS_F_FDMA_FDMA_CH_ACTIVATE_CH_ACTIVATE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_ACTIVATE_CH_ACTIVATE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_ACTIVATE_CH_ACTIVATE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Add DCBs to specific channels
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_RELOAD
 */
#define VTSS_FDMA_FDMA_CH_RELOAD             VTSS_IOREG(VTSS_TO_FDMA,0x3)

/**
 * \brief
 * Set to schedule reload of DCB for specific FDMA channels, there is one
 * bit per channel. Reload is used when adding new DCBs to an active
 * channel. See documentation for how to safely add DCBs to active channels
 * by using memory modifications and a single write to the RELOAD field.
 * Bits in this field are cleared when the corresponding channel reloads or
 * receives a DCB containing a valid next pointer.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_RELOAD . CH_RELOAD
 */
#define  VTSS_F_FDMA_FDMA_CH_RELOAD_CH_RELOAD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_RELOAD_CH_RELOAD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_RELOAD_CH_RELOAD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Disable specific channels
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_DISABLE
 */
#define VTSS_FDMA_FDMA_CH_DISABLE            VTSS_IOREG(VTSS_TO_FDMA,0x4)

/**
 * \brief
 * Set to schedule disable of specific FDMA channels, there is one bit per
 * channel. The channel will finish the current DCB, write the DONE bit to
 * the DCB status and then disable. Bits in this field is cleared when the
 * channel disables.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_DISABLE . CH_DISABLE
 */
#define  VTSS_F_FDMA_FDMA_CH_DISABLE_CH_DISABLE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_DISABLE_CH_DISABLE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_DISABLE_CH_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Ungraceful disable of specific channels
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_FORCEDIS
 */
#define VTSS_FDMA_FDMA_CH_FORCEDIS           VTSS_IOREG(VTSS_TO_FDMA,0x5)

/**
 * \brief
 * Immediately disable specific FDMA channels, there is one bit per
 * channel. Unlike FDMA:FDMA:FDMA_CH_DISABLE, using this field will not
 * take the state of the channel into account. It is meant to be used only
 * as part of an error recovery process. Bits in this field are cleared
 * immediately when set.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_FORCEDIS . CH_FORCEDIS
 */
#define  VTSS_F_FDMA_FDMA_CH_FORCEDIS_CH_FORCEDIS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_FORCEDIS_CH_FORCEDIS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_FORCEDIS_CH_FORCEDIS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Discard buffered DBs
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_DB_DISCARD
 */
#define VTSS_FDMA_FDMA_CH_DB_DISCARD         VTSS_IOREG(VTSS_TO_FDMA,0x6)

/**
 * \brief
 * This field has one bit per channel. It may be used to discard the
 * buffered DBs. The programmer must use this field with caution. The
 * programmer must first disable the respective channel through
 * FDMA_CH_DISABLE. Depending on the direction (injection/extraction)
 * additional actions are required.Extraction: The programmer must disable
 * incoming traffic from the switch core and wait until the internal buffer
 * of the extraction engine is empty. The programmer may have to provide
 * DBs in order to empty the buffer (XTR_BUF_IS_EMPTY). Once the buffer is
 * empty, it is recommended that the extraction is stopped with XTR_STOP
 * and the buffer is checked again for being empty.  The programmer must
 * disable the respective channel through FDMA_CH_DISABLE before discarding
 * the DBs by asserting this field.Injection: It is the responsibility of
 * the programmer to disable the channel, edit the DCBs and maybe
 * temporarily re-enable the channel to meet frame boundaries. The
 * programmer must wait for the DB status to be written back before
 * de-allocating the DB in memory. No DB discarding is supported for
 * injection channels.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_DB_DISCARD . DB_DISCARD
 */
#define  VTSS_F_FDMA_FDMA_CH_DB_DISCARD_DB_DISCARD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_DB_DISCARD_DB_DISCARD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_DB_DISCARD_DB_DISCARD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Channel counters
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_CNT
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_CNT (??), 0-7
 */
#define VTSS_FDMA_FDMA_CH_CNT(ri)            VTSS_IOREG(VTSS_TO_FDMA,0x7 + (ri))

/**
 * \brief
 * This field is incremented every time the channel saves status for a DB
 * that has EOF.This counter can only be modified safely when the
 * corresponding channel is disabled (FDMA_CH_ACTIVE.CH_ACTIVE).
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_CNT . CH_CNT_FRM
 */
#define  VTSS_F_FDMA_FDMA_CH_CNT_CH_CNT_FRM(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FDMA_FDMA_CH_CNT_CH_CNT_FRM     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FDMA_FDMA_CH_CNT_CH_CNT_FRM(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * This field is incremented every time the channel saves status for a DB
 * that has INTR set.This counter can only be modified safely when the
 * corresponding channel is disabled (FDMA_CH_ACTIVE.CH_ACTIVE).
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_CNT . CH_CNT_DB_INTR
 */
#define  VTSS_F_FDMA_FDMA_CH_CNT_CH_CNT_DB_INTR(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_FDMA_CH_CNT_CH_CNT_DB_INTR     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_FDMA_CH_CNT_CH_CNT_DB_INTR(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * This field is incremented every time the channel loads a DCB.This
 * counter can be modified safely while the corresponding channel is not
 * pending (see FDMA_CH_PENDING.CH_PENDING for more information).
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_CNT . CH_CNT_DCB
 */
#define  VTSS_F_FDMA_FDMA_CH_CNT_CH_CNT_DCB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_CNT_CH_CNT_DCB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_CNT_CH_CNT_DCB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Pointer to next DCB
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_DCB_LLP
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_CNT (??), 0-7
 */
#define VTSS_FDMA_FDMA_DCB_LLP(ri)           VTSS_IOREG(VTSS_TO_FDMA,0xf + (ri))

/**
 * \brief
 * Set prior to activating a specific channel, there is one replication per
 * channel. The LLP field is a 64bit pointer to current head of DCB chain,
 * software manually write this field prior to activating a channel using
 * FDMA_CH_ACTIVATE.CH_ACTIVATE. While a channel is activate software must
 * not update the field, it is automatically updated by the FDMA as it
 * progress through the list of DCBs. See FDMA_CH_RELOAD.CH_RELOAD for
 * information about adding additional DCBs to an active channel.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_DCB_LLP . LLP
 */
#define  VTSS_F_FDMA_FDMA_DCB_LLP_LLP(x)      (x)
#define  VTSS_M_FDMA_FDMA_DCB_LLP_LLP         0xffffffff
#define  VTSS_X_FDMA_FDMA_DCB_LLP_LLP(x)      (x)


/**
 * \brief Pointer to next DCB
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_DCB_LLP1
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_CNT (??), 0-7
 */
#define VTSS_FDMA_FDMA_DCB_LLP1(ri)          VTSS_IOREG(VTSS_TO_FDMA,0x17 + (ri))

/**
 * \brief
 * Bit 32-63 of field LLP.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_DCB_LLP1 . LLP1
 */
#define  VTSS_F_FDMA_FDMA_DCB_LLP1_LLP1(x)    (x)
#define  VTSS_M_FDMA_FDMA_DCB_LLP1_LLP1       0xffffffff
#define  VTSS_X_FDMA_FDMA_DCB_LLP1_LLP1(x)    (x)


/**
 * \brief Pointer to current DCB
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_DCB_LLP_PREV
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_CNT (??), 0-7
 */
#define VTSS_FDMA_FDMA_DCB_LLP_PREV(ri)      VTSS_IOREG(VTSS_TO_FDMA,0x1f + (ri))

/**
 * \brief
 * This field holds the pointer to current DCB, there is one replication
 * per channel.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_DCB_LLP_PREV . LLP_PREV
 */
#define  VTSS_F_FDMA_FDMA_DCB_LLP_PREV_LLP_PREV(x)  (x)
#define  VTSS_M_FDMA_FDMA_DCB_LLP_PREV_LLP_PREV     0xffffffff
#define  VTSS_X_FDMA_FDMA_DCB_LLP_PREV_LLP_PREV(x)  (x)


/**
 * \brief Pointer to current DCB
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_DCB_LLP_PREV1
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_CNT (??), 0-7
 */
#define VTSS_FDMA_FDMA_DCB_LLP_PREV1(ri)     VTSS_IOREG(VTSS_TO_FDMA,0x27 + (ri))

/**
 * \brief
 * Bit 32-63 of field LLP_PREV.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_DCB_LLP_PREV1 . LLP_PREV1
 */
#define  VTSS_F_FDMA_FDMA_DCB_LLP_PREV1_LLP_PREV1(x)  (x)
#define  VTSS_M_FDMA_FDMA_DCB_LLP_PREV1_LLP_PREV1     0xffffffff
#define  VTSS_X_FDMA_FDMA_DCB_LLP_PREV1_LLP_PREV1(x)  (x)


/**
 * \brief Read-only channel status indication fields
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_ACTIVE
 */
#define VTSS_FDMA_FDMA_CH_ACTIVE             VTSS_IOREG(VTSS_TO_FDMA,0x2f)

/**
 * \brief
 * Indication on per-channel status.
 *
 * \details
 * 0: Disabled
 * 1: Active
 *
 * Field: ::VTSS_FDMA_FDMA_CH_ACTIVE . CH_ACTIVE
 */
#define  VTSS_F_FDMA_FDMA_CH_ACTIVE_CH_ACTIVE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_ACTIVE_CH_ACTIVE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_ACTIVE_CH_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Per channel pending flag
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_PENDING
 */
#define VTSS_FDMA_FDMA_CH_PENDING            VTSS_IOREG(VTSS_TO_FDMA,0x30)

/**
 * \brief
 * A channel is considered to be pending if all of the following conditions
 * apply:- it is active- without disabling process initiated- either the
 * DCB list is not finished or it is set for reloading
 *
 * \details
 * 0: Disabled or about to disable, or the DCB list is finished and no
 * reloading is scheduled.
 * 1: Active, with DCBs pending to be fetched or with reloading scheduled.
 *
 * Field: ::VTSS_FDMA_FDMA_CH_PENDING . CH_PENDING
 */
#define  VTSS_F_FDMA_FDMA_CH_PENDING_CH_PENDING(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_PENDING_CH_PENDING     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_PENDING_CH_PENDING(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Idle state per channel
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_IDLE
 */
#define VTSS_FDMA_FDMA_CH_IDLE               VTSS_IOREG(VTSS_TO_FDMA,0x31)

/**
 * \brief
 * Idle is considered to be a channel which is not currently fetching or
 * waiting a DCB. This can be either because it has no more DCBs or because
 * the channel is between DCBS (finished last and not started next).Each
 * bit is associated to a channel. Each bit is expected to toggle as the
 * channel traverses through DCBs.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_IDLE . CH_IDLE
 */
#define  VTSS_F_FDMA_FDMA_CH_IDLE_CH_IDLE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_IDLE_CH_IDLE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_IDLE_CH_IDLE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Status fields per channel.
 *
 * \details
 * The register is replicated for all channels.
 *
 * Register: \a FDMA:FDMA:FDMA_CH_STATUS
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_CNT (??), 0-7
 */
#define VTSS_FDMA_FDMA_CH_STATUS(ri)         VTSS_IOREG(VTSS_TO_FDMA,0x32 + (ri))

/**
 * \brief
 * Channel's DB fill level in DCB reader buffer memory.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_STATUS . CH_FILL_LVL
 */
#define  VTSS_F_FDMA_FDMA_CH_STATUS_CH_FILL_LVL(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_FDMA_FDMA_CH_STATUS_CH_FILL_LVL     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_FDMA_FDMA_CH_STATUS_CH_FILL_LVL(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/**
 * \brief
 * The index of the 128bit word inside a DCB, during the loading of which
 * the error ERR_DCB_RD occurred.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_STATUS . CH_ERR_DCB_WRD128_IDX
 */
#define  VTSS_F_FDMA_FDMA_CH_STATUS_CH_ERR_DCB_WRD128_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_FDMA_FDMA_CH_STATUS_CH_ERR_DCB_WRD128_IDX     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_FDMA_FDMA_CH_STATUS_CH_ERR_DCB_WRD128_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Channel configuration
 *
 * \details
 * This register is replicated per channel.
 *
 * Register: \a FDMA:FDMA:FDMA_CH_CFG
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_CNT (??), 0-7
 */
#define VTSS_FDMA_FDMA_CH_CFG(ri)            VTSS_IOREG(VTSS_TO_FDMA,0x3a + (ri))

/**
 * \brief
 * Set to enable safe write of extraction status word. This configuration
 * only applies to extraction channels. This field can be set if the PCIe
 * system might split up 32bit writes to PCIe memory, in this case software
 * could accidentally read a partially populated status word and make
 * incorrect decisions.
 *
 * \details
 * 0: FDMA write STATUS word once with DONE=1.
 * 1: FDMA write STATUS word twice, first with DONE=0 and then with DONE=1.
 *
 * Field: ::VTSS_FDMA_FDMA_CH_CFG . CH_XTR_STATUS_MODE
 */
#define  VTSS_F_FDMA_FDMA_CH_CFG_CH_XTR_STATUS_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_FDMA_FDMA_CH_CFG_CH_XTR_STATUS_MODE  VTSS_BIT(5)
#define  VTSS_X_FDMA_FDMA_CH_CFG_CH_XTR_STATUS_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If this field is set, then the INTR_DB will be set only when saving
 * complete frames.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_CFG . CH_INTR_DB_EOF_ONLY
 */
#define  VTSS_F_FDMA_FDMA_CH_CFG_CH_INTR_DB_EOF_ONLY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FDMA_FDMA_CH_CFG_CH_INTR_DB_EOF_ONLY  VTSS_BIT(4)
#define  VTSS_X_FDMA_FDMA_CH_CFG_CH_INTR_DB_EOF_ONLY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Configure mapping of injection channel to port-number. This
 * configuration only applies to injection channels.
 *
 * \details
 * 0-1: FDMA port number.
 * Other values are reserved.
 *
 * Field: ::VTSS_FDMA_FDMA_CH_CFG . CH_INJ_PORT
 */
#define  VTSS_F_FDMA_FDMA_CH_CFG_CH_INJ_PORT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FDMA_FDMA_CH_CFG_CH_INJ_PORT  VTSS_BIT(3)
#define  VTSS_X_FDMA_FDMA_CH_CFG_CH_INJ_PORT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * The number of data blocks per DCB. This field controls the amount of
 * data that is fetched for each DCB. The default value is set to maximum,
 * this is a high value which will cause a lot of bandwidth to be used for
 * fetching of DCBs. Software should configure an optimized value
 * appropriate to the scenario they are working in, see documentation for
 * more information about FDMA scenarios.
 *
 * \details
 * 1 through 3
 * Other values are reserved
 *
 * Field: ::VTSS_FDMA_FDMA_CH_CFG . CH_DCB_DB_CNT
 */
#define  VTSS_F_FDMA_FDMA_CH_CFG_CH_DCB_DB_CNT(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_FDMA_FDMA_CH_CFG_CH_DCB_DB_CNT     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_FDMA_FDMA_CH_CFG_CH_DCB_DB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Set to configure working memory for channel. The FDMA has 64bit
 * visibility inside the working memory.When configured for PCIe memory,
 * accesses in the low 4Gbyte region translates to 32bit PCIe accesses,
 * accesses above low 4Gbyte translates to 64bit PCIe accesses.
 *
 * \details
 * 0: Local DDR memory
 * 1: PCIe memory
 *
 * Field: ::VTSS_FDMA_FDMA_CH_CFG . CH_MEM
 */
#define  VTSS_F_FDMA_FDMA_CH_CFG_CH_MEM(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FDMA_FDMA_CH_CFG_CH_MEM       VTSS_BIT(0)
#define  VTSS_X_FDMA_FDMA_CH_CFG_CH_MEM(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Channel translation offset
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_TRANSLATE
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_CNT (??), 0-7
 */
#define VTSS_FDMA_FDMA_CH_TRANSLATE(ri)      VTSS_IOREG(VTSS_TO_FDMA,0x42 + (ri))

/**
 * \brief
 * Translation offset that is added to DCB, status and DB pointers of the
 * respective channel. Write 0 to disable translation.The configured offset
 * is always a multiple of 1MB.
 *
 * \details
 * Value = (offset in bytes) / 1048576
 *
 * Field: ::VTSS_FDMA_FDMA_CH_TRANSLATE . OFFSET
 */
#define  VTSS_F_FDMA_FDMA_CH_TRANSLATE_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FDMA_FDMA_CH_TRANSLATE_OFFSET     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FDMA_FDMA_CH_TRANSLATE_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Injection channel token counter
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_INJ_TOKEN_CNT
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_INJ_CNT (??), 0-5
 */
#define VTSS_FDMA_FDMA_CH_INJ_TOKEN_CNT(ri)  VTSS_IOREG(VTSS_TO_FDMA,0x4a + (ri))

/**
 * \brief
 * Every time a channel activates with a DCB that has the TOKEN field set
 * this counter is decremented by one. Channels that loads a DCB with the
 * TOKEN field set cannot activate unless this counter is different from
 * zero.This counter can be written by software, or incremented
 * automatically by using the token tick counter (see
 * FDMA_CH_INJ_TOKEN_TICK_CNT for more information). This counter can be
 * modified safely when automatic incrementing is not enabled (see
 * FDMA:FDMA:FDMA_CH_INJ_TOKEN_CNT  for more information).
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_INJ_TOKEN_CNT . CH_INJ_TOKEN_CNT
 */
#define  VTSS_F_FDMA_FDMA_CH_INJ_TOKEN_CNT_CH_INJ_TOKEN_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_CH_INJ_TOKEN_CNT_CH_INJ_TOKEN_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_CH_INJ_TOKEN_CNT_CH_INJ_TOKEN_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Injection channel token tick counter reload value
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_INJ_TOKEN_TICK_RLD
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_INJ_CNT (??), 0-5
 */
#define VTSS_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD(ri)  VTSS_IOREG(VTSS_TO_FDMA,0x50 + (ri))

/**
 * \brief
 * Automatic incrementing of the token counter is enabled by setting this
 * field different from 0. This field holds the reload value for the
 * FDMA_CH_INJ_TOKEN_TICK_CNT.Note: When changing the value of this field
 * the same value should also be written to the FDMA_CH_INJ_TOKEN_TICK_CNT
 * field, this is needed for speeding up token counter increments when
 * changing from a high reload value to a low reload value.
 *
 * \details
 * 0: Token tick counter is disabled
 * n: Add one token every n * 200ns clock cycles
 *
 * Field: ::VTSS_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD . CH_INJ_TOKEN_TICK_RLD
 */
#define  VTSS_F_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD_CH_INJ_TOKEN_TICK_RLD(x)  (x)
#define  VTSS_M_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD_CH_INJ_TOKEN_TICK_RLD     0xffffffff
#define  VTSS_X_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD_CH_INJ_TOKEN_TICK_RLD(x)  (x)


/**
 * \brief Injection channel token tick counter
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CH_INJ_TOKEN_TICK_CNT
 *
 * @param ri Replicator: x_VCORE_FDMA_CH_INJ_CNT (??), 0-5
 */
#define VTSS_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT(ri)  VTSS_IOREG(VTSS_TO_FDMA,0x56 + (ri))

/**
 * \brief
 * Down-counter, decremented by one every 200ns. The counter is enabled
 * when the token scheme is enabled through
 * FDMA:FDMA:FDMA_CH_INJ_TOKEN_TICK_RLD. When zero is reached one token
 * will be added to FDMA:FDMA:FDMA_CH_INJ_TOKEN_CNT and the down-counter
 * will load the value from FDMA:FDMA:FDMA_CH_INJ_TOKEN_TICK_RLD (subtract
 * one and continue decrementing from that value).
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT . CH_INJ_TOKEN_TICK_CNT
 */
#define  VTSS_F_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT_CH_INJ_TOKEN_TICK_CNT(x)  (x)
#define  VTSS_M_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT_CH_INJ_TOKEN_TICK_CNT     0xffffffff
#define  VTSS_X_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT_CH_INJ_TOKEN_TICK_CNT(x)  (x)


/**
 * \brief FDMA injection configuration
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_INJ_CFG
 */
#define VTSS_FDMA_FDMA_INJ_CFG               VTSS_IOREG(VTSS_TO_FDMA,0x5c)

/**
 * \brief
 * Configure minimum spacing between frames on the TAXI towards the SwC,
 * this is the number of TAXI words from EOF to SOF during FDMA injection.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INJ_CFG . TAXI_EOF_SOF_MIN_WRD
 */
#define  VTSS_F_FDMA_FDMA_INJ_CFG_TAXI_EOF_SOF_MIN_WRD(x)  VTSS_ENCODE_BITFIELD(x,11,4)
#define  VTSS_M_FDMA_FDMA_INJ_CFG_TAXI_EOF_SOF_MIN_WRD     VTSS_ENCODE_BITMASK(11,4)
#define  VTSS_X_FDMA_FDMA_INJ_CFG_TAXI_EOF_SOF_MIN_WRD(x)  VTSS_EXTRACT_BITFIELD(x,11,4)

/**
 * \brief
 * Saturation value for injection arbitration scheme.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INJ_CFG . INJ_ARB_SAT
 */
#define  VTSS_F_FDMA_FDMA_INJ_CFG_INJ_ARB_SAT(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_FDMA_FDMA_INJ_CFG_INJ_ARB_SAT     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_FDMA_FDMA_INJ_CFG_INJ_ARB_SAT(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief FDMA extraction configuration
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_XTR_CFG
 */
#define VTSS_FDMA_FDMA_XTR_CFG               VTSS_IOREG(VTSS_TO_FDMA,0x5d)

/**
 * \brief
 * Configure extraction FIFO watermark.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_XTR_CFG . XTR_FIFO_WM
 */
#define  VTSS_F_FDMA_FDMA_XTR_CFG_XTR_FIFO_WM(x)  VTSS_ENCODE_BITFIELD(x,11,5)
#define  VTSS_M_FDMA_FDMA_XTR_CFG_XTR_FIFO_WM     VTSS_ENCODE_BITMASK(11,5)
#define  VTSS_X_FDMA_FDMA_XTR_CFG_XTR_FIFO_WM(x)  VTSS_EXTRACT_BITFIELD(x,11,5)

/**
 * \brief
 * Saturation value for extraction arbitration scheme.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_XTR_CFG . XTR_ARB_SAT
 */
#define  VTSS_F_FDMA_FDMA_XTR_CFG_XTR_ARB_SAT(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_FDMA_FDMA_XTR_CFG_XTR_ARB_SAT     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_FDMA_FDMA_XTR_CFG_XTR_ARB_SAT(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Port-specific configuration
 *
 * \details
 * Replicated register. Per port configuration.
 *
 * Register: \a FDMA:FDMA:FDMA_PORT_CFG
 *
 * @param ri Replicator: x_VCORE_FDMA_PORT_CNT (??), 0-1
 */
#define VTSS_FDMA_FDMA_PORT_CFG(ri)          VTSS_IOREG(VTSS_TO_FDMA,0x5e + (ri))

/**
 * \brief
 * Enable FCS padding for all injected frames. Padding with zeros is
 * performed on all frame-sizes by extending the frame by 4 bytes.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_PORT_CFG . INJ_FCS_PAD_EN
 */
#define  VTSS_F_FDMA_FDMA_PORT_CFG_INJ_FCS_PAD_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_FDMA_FDMA_PORT_CFG_INJ_FCS_PAD_EN  VTSS_BIT(8)
#define  VTSS_X_FDMA_FDMA_PORT_CFG_INJ_FCS_PAD_EN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * The minimum size of injection frames in bytes. Undersized frames are
 * 0-padded to this size.The zero-padding of undersized frames is performed
 * after the FCS padding.
 *
 * \details
 * 0 : Disabled
 * 1-63 : Invalid
 * 64-255 : Minimum frame size in bytes
 *
 * Field: ::VTSS_FDMA_FDMA_PORT_CFG . INJ_FRM_MIN_LEN
 */
#define  VTSS_F_FDMA_FDMA_PORT_CFG_INJ_FRM_MIN_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_PORT_CFG_INJ_FRM_MIN_LEN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_PORT_CFG_INJ_FRM_MIN_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Control of FDMA ports
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_PORT_CTRL
 *
 * @param ri Replicator: x_VCORE_FDMA_PORT_CNT (??), 0-1
 */
#define VTSS_FDMA_FDMA_PORT_CTRL(ri)         VTSS_IOREG(VTSS_TO_FDMA,0x60 + (ri))

/**
 * \brief
 * This field when set, it performs three functions:1. it prevents the
 * injection engine from accessing the buffered DBs2. it blocks any new
 * memory read accesses by the injection engine3. it stops frame injection
 * towards the switch core at frame boundary
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_PORT_CTRL . INJ_STOP
 */
#define  VTSS_F_FDMA_FDMA_PORT_CTRL_INJ_STOP(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_FDMA_FDMA_PORT_CTRL_INJ_STOP  VTSS_BIT(4)
#define  VTSS_X_FDMA_FDMA_PORT_CTRL_INJ_STOP(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * This field when set, it performs three functions:1. it prevents the
 * injection engine from accessing the buffered DBs2. it blocks any new
 * memory read accesses by the injection engine3. it stops frame injection
 * towards the switch core
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_PORT_CTRL . INJ_STOP_FORCE
 */
#define  VTSS_F_FDMA_FDMA_PORT_CTRL_INJ_STOP_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_FDMA_FDMA_PORT_CTRL_INJ_STOP_FORCE  VTSS_BIT(3)
#define  VTSS_X_FDMA_FDMA_PORT_CTRL_INJ_STOP_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This field when set, it performs two functions:1. it prevents the
 * extraction engine from accessing the buffered DBs2. it blocks any new
 * memory write accesses by the extraction engine
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_PORT_CTRL . XTR_STOP
 */
#define  VTSS_F_FDMA_FDMA_PORT_CTRL_XTR_STOP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_FDMA_FDMA_PORT_CTRL_XTR_STOP  VTSS_BIT(2)
#define  VTSS_X_FDMA_FDMA_PORT_CTRL_XTR_STOP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This field indicates whether the extraction buffer of the port is empty.
 *
 * \details
 * 1: empty
 * 0: not empty
 *
 * Field: ::VTSS_FDMA_FDMA_PORT_CTRL . XTR_BUF_IS_EMPTY
 */
#define  VTSS_F_FDMA_FDMA_PORT_CTRL_XTR_BUF_IS_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_FDMA_FDMA_PORT_CTRL_XTR_BUF_IS_EMPTY  VTSS_BIT(1)
#define  VTSS_X_FDMA_FDMA_PORT_CTRL_XTR_BUF_IS_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_FDMA_FDMA_PORT_CTRL . XTR_BUF_RST
 */
#define  VTSS_F_FDMA_FDMA_PORT_CTRL_XTR_BUF_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FDMA_FDMA_PORT_CTRL_XTR_BUF_RST  VTSS_BIT(0)
#define  VTSS_X_FDMA_FDMA_PORT_CTRL_XTR_BUF_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief DCB-event
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_INTR_DCB
 */
#define VTSS_FDMA_FDMA_INTR_DCB              VTSS_IOREG(VTSS_TO_FDMA,0x62)

/**
 * \brief
 * Set by FDMA when reading a DCB that has INTR field set in the DCB's INFO
 * word, there is one bit per channel.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_DCB . INTR_DCB
 */
#define  VTSS_F_FDMA_FDMA_INTR_DCB_INTR_DCB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_INTR_DCB_INTR_DCB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_INTR_DCB_INTR_DCB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief DCB-event interrupt enable
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_INTR_DCB_ENA
 */
#define VTSS_FDMA_FDMA_INTR_DCB_ENA          VTSS_IOREG(VTSS_TO_FDMA,0x63)

/**
 * \brief
 * Enables DCB read-event to be propagated as interrupt, there is one bit
 * per channel. See FDMA:FDMA:FDMA_INTR_DCB.INTR_DCB for additional
 * information.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_DCB_ENA . INTR_DCB_ENA
 */
#define  VTSS_F_FDMA_FDMA_INTR_DCB_ENA_INTR_DCB_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_INTR_DCB_ENA_INTR_DCB_ENA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_INTR_DCB_ENA_INTR_DCB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief DB-event
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_INTR_DB
 */
#define VTSS_FDMA_FDMA_INTR_DB               VTSS_IOREG(VTSS_TO_FDMA,0x64)

/**
 * \brief
 * Set by FDMA when saving status for a DB that has INTR field set in the
 * DB's STATUS word, there is one bit per channel. For injection channels
 * it is possible to gate interrupt with EOF in the status word, see
 * FDMA_CH_CFG.CH_INTR_DB_EOF_ONLY for more information. For extraction
 * channels the interrupt is emitted when saving DONE=1 in the status word,
 * this is related to the FDMA_CH_CFG.CH_XTR_STATUS_MODE setting.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_DB . INTR_DB
 */
#define  VTSS_F_FDMA_FDMA_INTR_DB_INTR_DB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_INTR_DB_INTR_DB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_INTR_DB_INTR_DB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief DB-event interrupt enable
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_INTR_DB_ENA
 */
#define VTSS_FDMA_FDMA_INTR_DB_ENA           VTSS_IOREG(VTSS_TO_FDMA,0x65)

/**
 * \brief
 * Enables DB-event to be propagated as interrupt, there is one bit per
 * channel. See FDMA:FDMA:FDMA_INTR_DB.INTR_DB for additional information.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_DB_ENA . INTR_DB_ENA
 */
#define  VTSS_F_FDMA_FDMA_INTR_DB_ENA_INTR_DB_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_INTR_DB_ENA_INTR_DB_ENA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_INTR_DB_ENA_INTR_DB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief ERR-event
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_INTR_ERR
 */
#define VTSS_FDMA_FDMA_INTR_ERR              VTSS_IOREG(VTSS_TO_FDMA,0x66)

/**
 * \brief
 * Shows if an ERR-event has occurred, there is one bit per port. It
 * signals errors related only to injection ports that the injection
 * channel source cannot be retrieved.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_ERR . INTR_PORT_ERR
 */
#define  VTSS_F_FDMA_FDMA_INTR_ERR_INTR_PORT_ERR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_FDMA_FDMA_INTR_ERR_INTR_PORT_ERR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_FDMA_FDMA_INTR_ERR_INTR_PORT_ERR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Shows if an ERR-event has occurred, there is one bit per channel. See
 * the data sheet for information on when this event can occur.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_ERR . INTR_CH_ERR
 */
#define  VTSS_F_FDMA_FDMA_INTR_ERR_INTR_CH_ERR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_INTR_ERR_INTR_CH_ERR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_INTR_ERR_INTR_CH_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Channel interrupt enable
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_INTR_ENA
 */
#define VTSS_FDMA_FDMA_INTR_ENA              VTSS_IOREG(VTSS_TO_FDMA,0x67)

/**
 * \brief
 * Enables propagation of  ERR-event as interrupt, there is one bit per
 * injection port.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_ENA . INTR_PORT_ENA
 */
#define  VTSS_F_FDMA_FDMA_INTR_ENA_INTR_PORT_ENA(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_FDMA_FDMA_INTR_ENA_INTR_PORT_ENA     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_FDMA_FDMA_INTR_ENA_INTR_PORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Enables propagation of DCB-event, DB-event, and ERR-event as interrupt,
 * there is one bit per channel.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_ENA . INTR_CH_ENA
 */
#define  VTSS_F_FDMA_FDMA_INTR_ENA_INTR_CH_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_INTR_ENA_INTR_CH_ENA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_INTR_ENA_INTR_CH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Currently interrupting channels
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_INTR_IDENT
 */
#define VTSS_FDMA_FDMA_INTR_IDENT            VTSS_IOREG(VTSS_TO_FDMA,0x68)

/**
 * \brief
 * Shows currently interrupting injection ports, there is one bit per port.
 * When a bit is set in this register the FDMA is generating interrupt
 * towards the VCore interrupt controller.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_IDENT . INTR_PORT_IDENT
 */
#define  VTSS_F_FDMA_FDMA_INTR_IDENT_INTR_PORT_IDENT(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_FDMA_FDMA_INTR_IDENT_INTR_PORT_IDENT     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_FDMA_FDMA_INTR_IDENT_INTR_PORT_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Shows currently interrupting channels, there is one bit per channel.
 * When a bit is set in this register the FDMA is generating interrupt
 * towards the VCore interrupt controller.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_INTR_IDENT . INTR_CH_IDENT
 */
#define  VTSS_F_FDMA_FDMA_INTR_IDENT_INTR_CH_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_INTR_IDENT_INTR_CH_IDENT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_INTR_IDENT_INTR_CH_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Error sticky flags
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_ERRORS
 */
#define VTSS_FDMA_FDMA_ERRORS                VTSS_IOREG(VTSS_TO_FDMA,0x69)

/**
 * \brief
 * Error indicator per extraction channel regarding writing of erroneous
 * data in the DBs. The error signals that the internal buffer has gone out
 * of sync with the posted write of AXI. As a result, the data that is
 * extracted in the data blocks is corrupted. When this error happens, the
 * FDMA will not initiate any new write operations for the erroneous
 * channel. Due to possible posted-write though, some blocks will be
 * written, depending on how many outstanding write operations the targeted
 * memory supports.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS . ERR_XTR_WR
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_ERR_XTR_WR(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_FDMA_FDMA_ERRORS_ERR_XTR_WR     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_FDMA_FDMA_ERRORS_ERR_XTR_WR(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * Error indicator per extraction channel. When set, the extraction buffer
 * of the channel has been overflowed. When this error happens, the FDMA
 * will not initiate any new write operations for the erroneous channel.
 * Due to possible posted-write though, some blocks will be written,
 * depending on how many outstanding write operations the targeted memory
 * supports.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS . ERR_XTR_OVF
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_ERR_XTR_OVF(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_FDMA_FDMA_ERRORS_ERR_XTR_OVF     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_FDMA_FDMA_ERRORS_ERR_XTR_OVF(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * Error indicator per extraction channel. When set, the taxi buffer of the
 * channel has been overflowed. When this error happens, the FDMA will not
 * initiate any new write operations for the erroneous channel. Due to
 * possible posted-write though, some blocks will be written, depending on
 * how many outstanding write operations the targeted memory supports.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS . ERR_XTR_TAXI32_OVF
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_ERR_XTR_TAXI32_OVF(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_FDMA_FDMA_ERRORS_ERR_XTR_TAXI32_OVF     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_FDMA_FDMA_ERRORS_ERR_XTR_TAXI32_OVF(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * Error indication per extraction channel regarding illegal value of DATAL
 * field of DCB_INFO of a DCB. The error is triggered when the DATAL is not
 * a multiple of 128bytes. Once this error has been set, the FDMA stops
 * decoding the DCB and accepting data blocks for this channel, and the
 * channel is disabled automatically. The channel cannot be re-enabled
 * unless the error is cleared by writing 1 to the respective bit of this
 * field. FDMA_DCB_LLP_PREV[ch] holds in this case the pointer to the DCB
 * that caused the error.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS . ERR_DCB_XTR_DATAL
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_ERR_DCB_XTR_DATAL(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_FDMA_FDMA_ERRORS_ERR_DCB_XTR_DATAL     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_FDMA_FDMA_ERRORS_ERR_DCB_XTR_DATAL(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Error indicator per channel regarding erroneous read of DCB. This error
 * is delivered to the FDMA from the AXI fabric. As soon as the error
 * occurs, the FDMA stops decoding the DCB and accepting new data blocks
 * for this channel. The data blocks that were accepted before are
 * processed normally. The channel is disabled automatically, and it cannot
 * be re-enabled until the error has been cleared. The error is cleared by
 * writing 1 to the respective bit of this field.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS . ERR_DCB_RD
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_ERR_DCB_RD(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_FDMA_FDMA_ERRORS_ERR_DCB_RD     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_FDMA_FDMA_ERRORS_ERR_DCB_RD(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Error indicator per port regarding erroneous read of DB. This error is
 * delivered to the FDMA from the AXI fabric. The frame that the erroneous
 * data belong to is dropped. The error is cleared by writing 1 to the
 * respective bit of this field.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS . ERR_INJ_RD
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_ERR_INJ_RD(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_FDMA_FDMA_ERRORS_ERR_INJ_RD     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_FDMA_FDMA_ERRORS_ERR_INJ_RD(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/**
 * \brief
 * Error indicator per port regarding the loss of synchronization between
 * buffering data and forwarding them to the switch core. The FDMA gets
 * automatically back in sync. All the data between getting out of sync and
 * back in sync is dropped. The error is cleared by writing 1 to the
 * respective bit of this field.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS . ERR_INJ_OUT_OF_SYNC
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_ERR_INJ_OUT_OF_SYNC(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_FDMA_FDMA_ERRORS_ERR_INJ_OUT_OF_SYNC     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_FDMA_FDMA_ERRORS_ERR_INJ_OUT_OF_SYNC(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Error indicator per channel regarding write operations. This error is
 * delivered to the FDMA from the AXI fabric when it fails to complete a
 * write operation. When this error is triggered, the FDMA cuts the supply
 * of DBs to the respective channel. Moreover, for extraction channels
 * only, the FDMA will not initiate any new write operations with extracted
 * frame data. However, additional transactions of the erroneous channel
 * can be pending. Channel activity shall stop when the respective pipeline
 * is drained. The error is cleared by writing 1 to the respective bit of
 * this field.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS . ERR_CH_WR
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_ERR_CH_WR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_FDMA_ERRORS_ERR_CH_WR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_FDMA_ERRORS_ERR_CH_WR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Error sticky flags
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_ERRORS_2
 */
#define VTSS_FDMA_FDMA_ERRORS_2              VTSS_IOREG(VTSS_TO_FDMA,0x6a)

/**
 * \brief
 * Error indicating that frame data were received without having received
 * SOF. The FDMA skips over this data.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_ERRORS_2 . ERR_XTR_FRAG
 */
#define  VTSS_F_FDMA_FDMA_ERRORS_2_ERR_XTR_FRAG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_FDMA_FDMA_ERRORS_2_ERR_XTR_FRAG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_FDMA_FDMA_ERRORS_2_ERR_XTR_FRAG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief FDMA idle Counter
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_IDLECNT
 */
#define VTSS_FDMA_FDMA_IDLECNT               VTSS_IOREG(VTSS_TO_FDMA,0x6b)

/**
 * \brief
 * This counter shows for how long the FDMA has been idle. The counter is
 * incremented once every 200ns, and reset whenever the FDMA moves frame
 * data to or from the queuing system. The counter saturates at maximum
 * value (approx 3.3 seconds of idle time).
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_IDLECNT . IDLECNT
 */
#define  VTSS_F_FDMA_FDMA_IDLECNT_IDLECNT(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_FDMA_FDMA_IDLECNT_IDLECNT     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_FDMA_FDMA_IDLECNT_IDLECNT(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief Control fields
 *
 * \details
 * Register: \a FDMA:FDMA:FDMA_CTRL
 */
#define VTSS_FDMA_FDMA_CTRL                  VTSS_IOREG(VTSS_TO_FDMA,0x6c)

/**
 * \brief
 * This field resets the internal control registers of the FDMA (not the
 * configuration registers).
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_CTRL . NRESET
 */
#define  VTSS_F_FDMA_FDMA_CTRL_NRESET(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_FDMA_FDMA_CTRL_NRESET         VTSS_BIT(0)
#define  VTSS_X_FDMA_FDMA_CTRL_NRESET(x)      VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a FDMA:FDMA_HA
 *
 * Not documented
 */


/**
 * \brief FDMA port statistics.
 *
 * \details
 * Register: \a FDMA:FDMA_HA:FDMA_PORT_STAT
 *
 * @param ri Replicator: x_VCORE_FDMA_PORT_CNT (??), 0-1
 */
#define VTSS_FDMA_FDMA_PORT_STAT(ri)         VTSS_IOREG(VTSS_TO_FDMA,0x0 + (ri))

/**
 * \brief
 * Per-port counter of frames that are injected to the switch core.
 *
 * \details
 * Field: ::VTSS_FDMA_FDMA_PORT_STAT . PORT_INJ_FRM_CNT
 */
#define  VTSS_F_FDMA_FDMA_PORT_STAT_PORT_INJ_FRM_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FDMA_FDMA_PORT_STAT_PORT_INJ_FRM_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FDMA_FDMA_PORT_STAT_PORT_INJ_FRM_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_LAGUNA_REGS_FDMA_H_ */
