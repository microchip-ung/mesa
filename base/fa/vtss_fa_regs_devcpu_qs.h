/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_FA_REGS_DEVCPU_QS_H_
#define _VTSS_FA_REGS_DEVCPU_QS_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a DEVCPU_QS
 *
 * CPU Device Queue System
 *
 ***********************************************************************/

/**
 * Register Group: \a DEVCPU_QS:XTR
 *
 * Frame extraction
 */


/** 
 * \brief Extraction group configuration
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_GRP_CFG
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_GRP_CFG(ri)       VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x0 + (ri))

/** 
 * \brief
 * Configures mode of the extraction group. Each extraction group can be
 * assigned to one of three owners.Note: The VRAP block support only one
 * context, if more than one extraction group is assigned the lowest
 * group-number will be used.
 *
 * \details 
 * 0: VRAP block
 * 1: Manual extraction (via DEVCPU_QS registers)
 * 2: FDMA extraction and manual extraction via SBA registers
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_GRP_CFG . MODE
 */
#define  VTSS_F_DEVCPU_QS_XTR_GRP_CFG_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_QS_XTR_GRP_CFG_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_QS_XTR_GRP_CFG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Select order of last data and status words.This field only applies to
 * manual extraction mode (see DEVCPU_QS::XTR_GRP_CFG.MODE).
 *
 * \details 
 * 0: Status just before last data
 * 1: Status just after last data
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_GRP_CFG . STATUS_WORD_POS
 */
#define  VTSS_F_DEVCPU_QS_XTR_GRP_CFG_STATUS_WORD_POS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEVCPU_QS_XTR_GRP_CFG_STATUS_WORD_POS  VTSS_BIT(1)
#define  VTSS_X_DEVCPU_QS_XTR_GRP_CFG_STATUS_WORD_POS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This field allows swapping the endianness of DEVCPU_QS::XTR_RD. Most
 * software will want to read extraction data in network order (big-endian
 * mode), i.e. the first byte of the destiantion MAC address to be placed
 * on byte-address 0 of DEVCPU_QS::XTR_RD. In order to do this a little
 * endian CPU must set this field, a big endian CPU must clear this
 * field.This field only applies to manual extraction mode (see
 * DEVCPU_QS::XTR_GRP_CFG.MODE).
 *
 * \details 
 * 0: Same endianness
 * 1: Swap endianness
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_GRP_CFG . BYTE_SWAP
 */
#define  VTSS_F_DEVCPU_QS_XTR_GRP_CFG_BYTE_SWAP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_QS_XTR_GRP_CFG_BYTE_SWAP  VTSS_BIT(0)
#define  VTSS_X_DEVCPU_QS_XTR_GRP_CFG_BYTE_SWAP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Manual extraction data
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_RD
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_RD(ri)            VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x2 + (ri))

/** 
 * \brief
 * Frame Data. Read from this register to obtain the next 32 bits of the
 * frame data currently stored in the CPU queue system. Each read must
 * check for the special values "0x8000000n", 0<=n<=7, as described by the
 * encoding.Note: The encoding is presented in little endian format, if
 * swapping is used (see DEVCPU_QS::XTR_GRP_CFG.BYTE_SWAP), then the
 * special values are swapped as well. I.e. a little endian CPU using
 * BYTE_SWAP=1 has to look for "0x0n000080" instead of "0x8000000n".The
 * position of the unused/valid bytes follows the endianness encoding and
 * swapping.
 *
 * \details 
 * n=0-3: EOF. Unused bytes in end-of-frame word is 'n'
 * n=4	 : EOF, but truncated
 * n=5	 : EOF Aborted. Frame invalid
 * n=6	 : Escape. Next read is packet data
 * n=7	 : Data not ready for reading out
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_RD . DATA
 */
#define  VTSS_F_DEVCPU_QS_XTR_RD_DATA(x)      (x)
#define  VTSS_M_DEVCPU_QS_XTR_RD_DATA         0xffffffff
#define  VTSS_X_DEVCPU_QS_XTR_RD_DATA(x)      (x)


/** 
 * \brief Extraction frame pruning
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_FRM_PRUNING
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_FRM_PRUNING(ri)   VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x4 + (ri))

/** 
 * \brief
 * Extracted frames for the corresponding queue are pruned to
 * (PRUNE_SIZE+1) 32-bit words.Note :  PRUNE_SIZE includes the IFH when
 * this present in the frame.
 *
 * \details 
 * 0 : No pruning
 * 1:  Frames extracted are pruned to 8 bytes
 * 2:  Frames extracted are pruned to 12 bytes
 * ...
 * 255:  Frames extracted are pruned to 1024 bytes
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_FRM_PRUNING . PRUNE_SIZE
 */
#define  VTSS_F_DEVCPU_QS_XTR_FRM_PRUNING_PRUNE_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_QS_XTR_FRM_PRUNING_PRUNE_SIZE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_QS_XTR_FRM_PRUNING_PRUNE_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Extraction group flush
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_FLUSH
 */
#define VTSS_DEVCPU_QS_XTR_FLUSH             VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x6)

/** 
 * \brief
 * Enable software flushing of a CPU queue.Note the queue will continue to
 * be flushed until this field is cleared by SW. The flushing will
 * automatically stop on frame boundary so OQS is allowed to transmit to
 * the CPU queue during flushing.
 *
 * \details 
 * 0: No action
 * 1: Do CPU queue flushing
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_FLUSH . FLUSH
 */
#define  VTSS_F_DEVCPU_QS_XTR_FLUSH_FLUSH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_XTR_FLUSH_FLUSH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_XTR_FLUSH_FLUSH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Extraction status
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_DATA_PRESENT
 */
#define VTSS_DEVCPU_QS_XTR_DATA_PRESENT      VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x7)

/** 
 * \brief
 * Shows if data is available for a specific group. It remains set until
 * all frame data have been extracted. This field is only set if the mode
 * of the group is set to manual extraction via DEVCPU_QS registers.
 *
 * \details 
 * 0: No frames available for this CPU queue group
 * 1: At least one frame is available for this CPU queue group
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_DATA_PRESENT . DATA_PRESENT
 */
#define  VTSS_F_DEVCPU_QS_XTR_DATA_PRESENT_DATA_PRESENT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_XTR_DATA_PRESENT_DATA_PRESENT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_XTR_DATA_PRESENT_DATA_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief General extraction configuration and status
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_CFG
 */
#define VTSS_DEVCPU_QS_XTR_CFG               VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x8)

/** 
 * \brief
 * Watermark, when filling of extraction FIFO exceeds this (or EOF is
 * present in the xtraction buffer) the DEVCPU_QS::XTR_DATA_PRESENT
 * register will indicate that data is available.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_XTR_CFG . DP_WM
 */
#define  VTSS_F_DEVCPU_QS_XTR_CFG_DP_WM(x)    VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_DEVCPU_QS_XTR_CFG_DP_WM       VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_DEVCPU_QS_XTR_CFG_DP_WM(x)    VTSS_EXTRACT_BITFIELD(x,7,5)

/** 
 * \brief
 * Watermark, when filling of extraction buffer exceeds this backpressure
 * is generated towards the QS.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_XTR_CFG . SCH_WM
 */
#define  VTSS_F_DEVCPU_QS_XTR_CFG_SCH_WM(x)   VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_DEVCPU_QS_XTR_CFG_SCH_WM      VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_DEVCPU_QS_XTR_CFG_SCH_WM(x)   VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * Overflow in extraction FIFO. If this happens, SCH_WM must be decreased.
 *
 * \details 
 * 0: No buffer overruns detected
 * 1: Buffer has overrruned at least once
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_CFG . OFLW_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_QS_XTR_CFG_OFLW_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_XTR_CFG_OFLW_ERR_STICKY     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_XTR_CFG_OFLW_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a DEVCPU_QS:INJ
 *
 * Frame injection
 */


/** 
 * \brief Injection group configuration
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_GRP_CFG
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_GRP_CFG(ri)       VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x9 + (ri))

/** 
 * \brief
 * Configures mode of the injection group. Each injection group can be
 * assigned to one of three owners.Note: The VRAP block support only one
 * context, if more than one injection group is assigned the lowest
 * group-number will be used.
 *
 * \details 
 * 0: VRAP block
 * 1: Manual injection (via DEVCPU_QS registers)
 * 2: FDMA injection and manual injection via SBA registers
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_GRP_CFG . MODE
 */
#define  VTSS_F_DEVCPU_QS_INJ_GRP_CFG_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_QS_INJ_GRP_CFG_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_QS_INJ_GRP_CFG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * This field allows swapping the endianness of the DEVCPU_QS::INJ_WR
 * register. Most software will want to write injection data in network
 * order (big-endian mode), i.e. the first byte of the destiantion MAC
 * address to be placed on byte-address 0 of DEVCPU_QS::INJ_WR. In order to
 * do this a little endian CPU must set this field, a big endian CPU must
 * clear this field.This field only applies to manual extraction mode (see
 * DEVCPU_QS::INJ_GRP_CFG.MODE).
 *
 * \details 
 * 0: Same endianness as CPU
 * 1: Swap endianness
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_GRP_CFG . BYTE_SWAP
 */
#define  VTSS_F_DEVCPU_QS_INJ_GRP_CFG_BYTE_SWAP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_QS_INJ_GRP_CFG_BYTE_SWAP  VTSS_BIT(0)
#define  VTSS_X_DEVCPU_QS_INJ_GRP_CFG_BYTE_SWAP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Manual injection data
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_WR
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_WR(ri)            VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xb + (ri))

/** 
 * \brief
 * Frame Write. Write to this register inject  the next 32 bits of the
 * frame data currently injected into the chip.Reading from this register
 * returns 0.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_WR . DATA
 */
#define  VTSS_F_DEVCPU_QS_INJ_WR_DATA(x)      (x)
#define  VTSS_M_DEVCPU_QS_INJ_WR_DATA         0xffffffff
#define  VTSS_X_DEVCPU_QS_INJ_WR_DATA(x)      (x)


/** 
 * \brief Injection control
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_CTRL
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_CTRL(ri)          VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xd + (ri))

/** 
 * \brief
 * Controls the min-spacing from EOF to SOF on injected frames, the default
 * value emulates the delay of standard preamble/IFG setting on a
 * front-port. Set this field to zero when injecting with IFH.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_CTRL . GAP_SIZE
 */
#define  VTSS_F_DEVCPU_QS_INJ_CTRL_GAP_SIZE(x)  VTSS_ENCODE_BITFIELD(x,21,4)
#define  VTSS_M_DEVCPU_QS_INJ_CTRL_GAP_SIZE     VTSS_ENCODE_BITMASK(21,4)
#define  VTSS_X_DEVCPU_QS_INJ_CTRL_GAP_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,21,4)

/** 
 * \brief
 * Set to abort the current frame.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_CTRL . ABORT
 */
#define  VTSS_F_DEVCPU_QS_INJ_CTRL_ABORT(x)   VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DEVCPU_QS_INJ_CTRL_ABORT      VTSS_BIT(20)
#define  VTSS_X_DEVCPU_QS_INJ_CTRL_ABORT(x)   VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set to indicate that the next data written to DEVCPU_Qs::INJ_WR is
 * end-of-frame. At the same time as setting this field, also set
 * DEVCPU_QS::INJ_CTRL.VLD_BYTES to indicate the number of valid data bytes
 * in the end-of-frame word.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_CTRL . EOF
 */
#define  VTSS_F_DEVCPU_QS_INJ_CTRL_EOF(x)     VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DEVCPU_QS_INJ_CTRL_EOF        VTSS_BIT(19)
#define  VTSS_X_DEVCPU_QS_INJ_CTRL_EOF(x)     VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Set to indicate that the next data written to DEVCPU_QS::INJ_WR is
 * start-of-frame.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_CTRL . SOF
 */
#define  VTSS_F_DEVCPU_QS_INJ_CTRL_SOF(x)     VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DEVCPU_QS_INJ_CTRL_SOF        VTSS_BIT(18)
#define  VTSS_X_DEVCPU_QS_INJ_CTRL_SOF(x)     VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set to indicate how many bytes of the next data written to
 * DEVCPU_QS::INJ_WR which are valid. This field is only used during
 * end-of-frame words (see DEVCPU_QS::INJ_CTRL.EOF for more information).
 * The position of the valid bytes follows the endianness encoding and
 * swapping.
 *
 * \details 
 * 0: All bytes are valid
 * n: 'n' byte are valid
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_CTRL . VLD_BYTES
 */
#define  VTSS_F_DEVCPU_QS_INJ_CTRL_VLD_BYTES(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DEVCPU_QS_INJ_CTRL_VLD_BYTES     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DEVCPU_QS_INJ_CTRL_VLD_BYTES(x)  VTSS_EXTRACT_BITFIELD(x,16,2)


/** 
 * \brief Injection status
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_STATUS
 */
#define VTSS_DEVCPU_QS_INJ_STATUS            VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xf)

/** 
 * \brief
 * Before the CPU injects a frame, software may check if the input queue
 * has reached high watermark. If wathermark in the IQS has been reached
 * this bit will be set.
 *
 * \details 
 * 0: Input queue has not reached high watermark
 * 1: Input queue has reached high watermark, and frames injected may be
 * dropped due to buffer overflow
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_STATUS . WMARK_REACHED
 */
#define  VTSS_F_DEVCPU_QS_INJ_STATUS_WMARK_REACHED(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DEVCPU_QS_INJ_STATUS_WMARK_REACHED     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DEVCPU_QS_INJ_STATUS_WMARK_REACHED(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * When '1' the injector group's FIFO is ready for additional data written
 * through the DEVCPU_QS::INJ_WR register.
 *
 * \details 
 * 0: The injector group cannot accept additional data
 * 1: The injector group is able to accept additional data
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_STATUS . FIFO_RDY
 */
#define  VTSS_F_DEVCPU_QS_INJ_STATUS_FIFO_RDY(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_QS_INJ_STATUS_FIFO_RDY     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_QS_INJ_STATUS_FIFO_RDY(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * When '1' the injector group is in the process of receiving a frame, and
 * at least one write to INJ_WR remains before the frame is forwarded to
 * the front ports. When '0' the injector group is waiting for an
 * initiation of a frame injection.
 *
 * \details 
 * 0: A frame injection is not in progress
 * 1: A frame injection is in progress
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_STATUS . INJ_IN_PROGRESS
 */
#define  VTSS_F_DEVCPU_QS_INJ_STATUS_INJ_IN_PROGRESS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_INJ_STATUS_INJ_IN_PROGRESS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_INJ_STATUS_INJ_IN_PROGRESS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Injection errors
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_ERR
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_ERR(ri)           VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x10 + (ri))

/** 
 * \brief
 * Set if a frame has been aborted because of double-SOF injection (missing
 * EOF).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_ERR . ABORT_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_QS_INJ_ERR_ABORT_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEVCPU_QS_INJ_ERR_ABORT_ERR_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEVCPU_QS_INJ_ERR_ABORT_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set in case of overflow as a result of not obeying FIFO-ready
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_ERR . WR_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_QS_INJ_ERR_WR_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_QS_INJ_ERR_WR_ERR_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEVCPU_QS_INJ_ERR_WR_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Injection debug
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:VTSS_DBG
 */
#define VTSS_DEVCPU_QS_VTSS_DBG              VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x12)

/** 
 * \brief
 * For debugging purpose, frames injected are counted with a small wrapping
 * counter.
 *
 * \details 
 * 0: No frames has been injected
 * 1: 1 frame has been injected
 * ...
 * 15: 15 frames have been injected
 *
 * Field: ::VTSS_DEVCPU_QS_VTSS_DBG . FRM_CNT
 */
#define  VTSS_F_DEVCPU_QS_VTSS_DBG_FRM_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_QS_VTSS_DBG_FRM_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_QS_VTSS_DBG_FRM_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


#endif /* _VTSS_FA_REGS_DEVCPU_QS_H_ */
