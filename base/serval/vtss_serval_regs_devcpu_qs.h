#ifndef _VTSS_SERVAL_REGS_DEVCPU_QS_H_
#define _VTSS_SERVAL_REGS_DEVCPU_QS_H_

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

#include "vtss_serval_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a DEVCPU_QS
 *
 * CPU device queue system
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
#define VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(ri)   VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x0 + (ri))

/** 
 * \brief
 * Configures mode of the extraction group. Each extraction group can be
 * assigned to one of three owners.
 * Note: The VRAP block support only one context, if more than one
 * extraction group is assigned the lowest group-number will be used.
 *
 * \details 
 * 0: VRAP block
 * 1: Manual extraction (via DEVCPU_QS registers)
 * 2: FDMA extraction and manual extraction via SBA registers
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG . MODE
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_QS_XTR_XTR_GRP_CFG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Select order of last data and status words.
 * This field only applies to manual extraction mode (see
 * DEVCPU_QS::XTR_GRP_CFG.MODE).
 *
 * \details 
 * 0: Status just before last data
 * 1: Status just after last data
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG . STATUS_WORD_POS
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_STATUS_WORD_POS  VTSS_BIT(1)

/** 
 * \brief
 * This field allows swapping the endianess of DEVCPU_QS::XTR_RD. Most
 * software will want to read extraction data in network order (big-endian
 * mode), i.e. the first byte of the destiantion MAC address to be placed
 * on byte-address 0 of DEVCPU_QS::XTR_RD. In order to do this a little
 * endian CPU must set this field, a big endian CPU must clear this field.
 * This field only applies to manual extraction mode (see
 * DEVCPU_QS::XTR_GRP_CFG.MODE).
 *
 * \details 
 * 0: Same endianess
 * 1: Swap endianness
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG . BYTE_SWAP
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP  VTSS_BIT(0)


/** 
 * \brief Manual extraction data
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_RD
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_XTR_RD(ri)        VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x2 + (ri))


/** 
 * \brief Extraction frame pruning
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_FRM_PRUNING
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_XTR_FRM_PRUNING(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x4 + (ri))

/** 
 * \brief
 * Extracted frames for the corresponding queue are pruned to
 * (PRUNE_SIZE+1) 32-bit words.
 * Note :  PRUNE_SIZE is the frame data size + optional IFH (see
 * SYS::PORT_MODE.INCL_XTR_HDR for more information on enabling IFH for
 * extraction frames).
 *
 * \details 
 * 0 : No pruning
 * 1:  Frames extracted are pruned to 8 bytes
 * 2:  Frames extracted are pruned to 12 bytes
 * ...
 * 255:  Frames extracted are pruned to 1024 bytes
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_FRM_PRUNING . PRUNE_SIZE
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_FRM_PRUNING_PRUNE_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_QS_XTR_XTR_FRM_PRUNING_PRUNE_SIZE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_QS_XTR_XTR_FRM_PRUNING_PRUNE_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Extraction group flush
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_FLUSH
 */
#define VTSS_DEVCPU_QS_XTR_XTR_FLUSH         VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x6)

/** 
 * \brief
 * Enable software flushing of a CPU queue.
 * Note that before flushing the a CPU queue it may be necessary to stop
 * the OQS from sending data into the CPU queues.
 *
 * \details 
 * 0: No action
 * 1: Do CPU queue flushing
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_FLUSH . FLUSH
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_FLUSH_FLUSH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_XTR_XTR_FLUSH_FLUSH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_XTR_XTR_FLUSH_FLUSH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Extraction status
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_DATA_PRESENT
 */
#define VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT  VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x7)

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
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT . DATA_PRESENT
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

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
#define VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(ri)   VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x9 + (ri))

/** 
 * \brief
 * Configures mode of the injection group. Each injection group can be
 * assigned to one of three owners.
 * Note: The VRAP block support only one context, if more than one
 * injection group is assigned the lowest group-number will be used.
 *
 * \details 
 * 0: VRAP block
 * 1: Manual injection (via DEVCPU_QS registers)
 * 2: FDMA injection and manual injection via SBA registers
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG . MODE
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_GRP_CFG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * This field allows swapping the endianess of the DEVCPU_QS::INJ_WR
 * register. Most software will want to write injection data in network
 * order (big-endian mode), i.e. the first byte of the destiantion MAC
 * address to be placed on byte-address 0 of DEVCPU_QS::INJ_WR. In order to
 * do this a little endian CPU must set this field, a big endian CPU must
 * clear this field.
 * This field only applies to manual extraction mode (see
 * DEVCPU_QS::INJ_GRP_CFG.MODE).
 *
 * \details 
 * 0: Same endianess as CPU
 * 1: Swap endianness
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG . BYTE_SWAP
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_BYTE_SWAP  VTSS_BIT(0)


/** 
 * \brief Manual injection data
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_WR
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_INJ_WR(ri)        VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xb + (ri))


/** 
 * \brief Injection control
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_CTRL
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_INJ_CTRL(ri)      VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xd + (ri))

/** 
 * \brief
 * Set this field to configure a minimum delay after each frame EOF when
 * injecting to the QS. 0 though 15 additional 32-bit word delays can be
 * inserted after eof. The number if delays is configured by setting low 2
 * bit in replication 0 and high two 2 in repliction 1. So that the number
 * of delays to insert is {INJ_CTRL[1].GAP_SIZE, INJ_CTRL[0].GAP_SIZE}.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . GAP_SIZE
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * Set to abort the current frame.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . ABORT
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_ABORT  VTSS_BIT(20)

/** 
 * \brief
 * Set to indicate that the next data written to DEVCPU_Qs::INJ_WR is
 * end-of-frame. At the same time as setting this field, also set
 * DEVCPU_QS::INJ_CTRL.VLD_BYTES to indicate the number of valid data bytes
 * in the end-of-frame word.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . EOF
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_EOF    VTSS_BIT(19)

/** 
 * \brief
 * Set to indicate that the next data written to DEVCPU_QS::INJ_WR is
 * start-of-frame.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . SOF
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_SOF    VTSS_BIT(18)

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
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . VLD_BYTES
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES(x)  VTSS_EXTRACT_BITFIELD(x,16,2)


/** 
 * \brief Injection status
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_STATUS
 */
#define VTSS_DEVCPU_QS_INJ_INJ_STATUS        VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xf)

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
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_STATUS . WMARK_REACHED
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * When '1' the injector group's FIFO is ready for additional data written
 * through the DEVCPU_QS::INJ_WR register.
 *
 * \details 
 * 0: The injector group cannot accept additional data
 * 1: The injector group is able to accept additional data
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_STATUS . FIFO_RDY
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_STATUS_FIFO_RDY(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_STATUS_FIFO_RDY     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_FIFO_RDY(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

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
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_STATUS . INJ_IN_PROGRESS
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_STATUS_INJ_IN_PROGRESS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_STATUS_INJ_IN_PROGRESS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_INJ_IN_PROGRESS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Injection errors
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_ERR
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_INJ_ERR(ri)       VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x10 + (ri))

/** 
 * \brief
 * Set if a frame has been aborted because of double-SOF injection (missing
 * EOF).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_ERR . ABORT_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_ERR_ABORT_ERR_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Set in case of overflow as a result of not obeying FIFO-ready
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_ERR . WR_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_ERR_WR_ERR_STICKY  VTSS_BIT(0)


#endif /* _VTSS_SERVAL_REGS_DEVCPU_QS_H_ */
