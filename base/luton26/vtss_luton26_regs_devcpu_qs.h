// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LUTON26_REGS_DEVCPU_QS_H_
#define _VTSS_LUTON26_REGS_DEVCPU_QS_H_


#include "vtss_luton26_regs_common.h"

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
 * Frame Extraction Related Registers
 */


/** 
 * \brief Frame Pruning
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_FRM_PRUNING
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_QUEUES (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_XTR_FRM_PRUNING(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x0 + (ri))

/** 
 * \brief
 * Extracted frames for the corresponding queue are pruned PRUNE_SIZE
 * 32-bit words.
 * 
 * Note :  PRUNE_SIZE is the frame data size, including the IFH.
 *
 * \details 
 * 0 : No pruning
 * 1:  Frames extracted are pruned to 8 bytes.
 * 2:  Frames extracted are pruned to 12 bytes.
 * .
 * '0xFF':  Frames extracted are pruned to 1024 bytes
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_FRM_PRUNING . PRUNE_SIZE
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_FRM_PRUNING_PRUNE_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_QS_XTR_XTR_FRM_PRUNING_PRUNE_SIZE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_QS_XTR_XTR_FRM_PRUNING_PRUNE_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Group Configuration
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_GRP_CFG
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG(ri)   VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x2 + (ri))

/** 
 * \brief
 * Controls - per extraction group - the byte order of the data word read
 * in XTR_RD. When using little-Endian mode, then the first byte of the
 * destination MAC address is placed at XTR_RD[7:0]. When using
 * network-order, then the first byte of the destination MAC address is
 * placed at XTR_RD[31:25].
 *
 * \details 
 * 0: Network-order (big-endian).
 * 1: Little-endian.
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG . BYTE_SWAP
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_BYTE_SWAP  VTSS_BIT(0)

/** 
 * \brief
 * Select order of last data and status words.
 *
 * \details 
 * 0: Status just before last data.
 * 1: Status just after last data.
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG . STATUS_WORD_POS
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_STATUS_WORD_POS  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to add a 4 byte header in front of the frame data,
 * containing the origin cpu queue the extracted frames come from.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_GRP_CFG . XTR_HDR_ENA
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_GRP_CFG_XTR_HDR_ENA  VTSS_BIT(2)


/** 
 * \brief Map Queue to Group
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_MAP
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_QUEUES (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_XTR_MAP(ri)       VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x4 + (ri))

/** 
 * \brief
 * Maps a queue to a certain extractor group
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_MAP . GRP
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_MAP_GRP     VTSS_BIT(4)

/** 
 * \brief
 * Enables extraction of a queue.
 * 
 * Disabling of extraction for a queue happens upon next frame boundary.
 * That is, a frame being extracted at the time of queue disabling is not
 * affected.
 *
 * \details 
 * '0' : Queue is not mapped to a queue group ( queue is disabled )
 * '1' : Queue is mapped to the queue group defined by XTR::XTR_MAP ( queue
 * is enabled )
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_MAP . MAP_ENA
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_MAP_MAP_ENA  VTSS_BIT(0)


/** 
 * \brief Read from Group FIFO
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_RD
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_GROUPS_MUL_PCI_BURST_SIZE (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_XTR_RD(ri)        VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x6 + (ri))


/** 
 * \brief Software Controlled Queue Selection
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_QU_SEL
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_XTR_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_XTR_XTR_QU_SEL(ri)    VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x8 + (ri))


/** 
 * \brief Queue Flush
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_QU_FLUSH
 */
#define VTSS_DEVCPU_QS_XTR_XTR_QU_FLUSH      VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xa)

/** 
 * \brief
 * Enable software flushing of a CPU queue.
 * Note that before flushing the a CPU queue it may be necessary to stop
 * the OQS from sending data into the CPU queues.

 *
 * \details 
 * '0': No action
 * '1': Do CPU queue flushing
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_QU_FLUSH . FLUSH
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_QU_FLUSH_FLUSH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_XTR_XTR_QU_FLUSH_FLUSH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_XTR_XTR_QU_FLUSH_FLUSH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Extraction Status
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_DATA_PRESENT
 */
#define VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT  VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xb)

/** 
 * \brief
 * When a frame, which should be forwarded to software has been received by
 * the CPU queue system, the corresponding bit is set. When software has
 * extracted all frames from a CPU queue the bit is cleared, i.e. the bit
 * remains set as long as at least one byte of frame data for the
 * corresponding queue is present in the queue system.
 * 
 * Note : If a queue isn't map to a group DATA_PRESENT will be '0'
 *
 * \details 
 * '0': No data available for this CPU queue
 * '1': At least one frame is available for this cpu queue
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT . DATA_PRESENT
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * When a queue group has a frame present, the bit corresponding to the
 * queue group number gets set. It remains set until all frame data have
 * been extracted.
 *
 * \details 
 * '0': No frames available for this CPU queue group.
 * '1': At least one frame is available for this CPU queue group.
 *
 * Field: ::VTSS_DEVCPU_QS_XTR_XTR_DATA_PRESENT . DATA_PRESENT_GRP
 */
#define  VTSS_F_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT_GRP(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT_GRP     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_XTR_XTR_DATA_PRESENT_DATA_PRESENT_GRP(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Queue Debug
 *
 * \details
 * Register: \a DEVCPU_QS:XTR:XTR_QU_DBG
 */
#define VTSS_DEVCPU_QS_XTR_XTR_QU_DBG        VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xc)

/**
 * Register Group: \a DEVCPU_QS:INJ
 *
 * Frame Injection Related Registers
 */


/** 
 * \brief Group Configuration
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_GRP_CFG
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG(ri)   VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xd + (ri))

/** 
 * \brief
 * Controls - per injection group - the byte order of the data word in
 * INJ_WR.
 *
 * \details 
 * 0: Network-order (big-endian).
 * 1: Little-endian.
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_GRP_CFG . BYTE_SWAP
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_GRP_CFG_BYTE_SWAP  VTSS_BIT(8)


/** 
 * \brief Write to Group FIFO
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_WR
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS_MUL_PCI_BURST_SIZE (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_INJ_WR(ri)        VTSS_IOREG(VTSS_TO_DEVCPU_QS,0xf + (ri))


/** 
 * \brief Injection Control
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_CTRL
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_INJ_CTRL(ri)      VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x11 + (ri))

/** 
 * \brief
 * It is allowed to inject a number of "dummy" bytes in front of a frame
 * before the actual frame data. The number of bytes that should be
 * discarded is specified with this field.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . GAP_SIZE
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(x)  VTSS_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE     VTSS_ENCODE_BITMASK(21,8)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_CTRL_GAP_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,21,8)

/** 
 * \brief
 * Abort frame currently injected.
 *
 * \details 
 * Write:
 * '0': No action
 * '1': Frame currently injected is aborted  (Bit is automatically cleared)
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . ABORT
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_ABORT  VTSS_BIT(20)

/** 
 * \brief
 * EOF must be set before last data of a frame is injected.
 *
 * \details 
 * '0': No action
 * '1': Next word is the last word of the frame injected
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . EOF
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_EOF    VTSS_BIT(19)

/** 
 * \brief
 * SOF must be set before injecting a frame.
 *
 * \details 
 * Write:
 * '0': No action
 * '1': Start of new frame injection
 * 
 * Read:
 * '0': First data word has been moved to the IQS.
 * '1': First data word has not been moved to the IQS.
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . SOF
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_SOF    VTSS_BIT(18)

/** 
 * \brief
 * The number of valid bytes in the last word must be set before last data
 * of a frame is injected.
 *
 * \details 
 * 0: Bits 31-0 in the last word are valid.
 * 1: Bits 31-24 in the last word are valid.
 * 2: Bits 31-16 in the last word are valid.
 * 3: Bits 31-7 in the last word are valid.
 * This encoding applies when big-endian is used for INJ_WR.
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_CTRL . VLD_BYTES
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_CTRL_VLD_BYTES(x)  VTSS_EXTRACT_BITFIELD(x,16,2)


/** 
 * \brief Injection Status
 *
 * \details
 * Register: \a DEVCPU_QS:INJ:INJ_STATUS
 */
#define VTSS_DEVCPU_QS_INJ_INJ_STATUS        VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x13)

/** 
 * \brief
 * Before the CPU injects a frame, software may check if the input queue
 * has reached high watermark. If the watermark in the IQS has been reached
 * this bit will be set.
 *
 * \details 
 * '0': Input queue has not reached high watermark
 * '1': Input queue has reached high watermark, and frames injected may be
 * dropped due to buffer overflow.
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_STATUS . WMARK_REACHED
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_WMARK_REACHED(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * When '1' the injector group's FIFO is ready for additional data written
 * through the INJ_WR register.
 *
 * \details 
 * '0': The injector group cannot accept additional data.
 * '1': The injector group is able to accept additional data.
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
 * '0': A frame injection is not in progress.
 * '1': A frame injection is in progress.
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_STATUS . INJ_IN_PROGRESS
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_STATUS_INJ_IN_PROGRESS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_QS_INJ_INJ_STATUS_INJ_IN_PROGRESS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_QS_INJ_INJ_STATUS_INJ_IN_PROGRESS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Injection Errors
 *
 * \details
 * The bits in this register are cleared by writing a '1' to the relevant
 * bit-positions.
 *
 * Register: \a DEVCPU_QS:INJ:INJ_ERR
 *
 * @param ri Replicator: x_DEVCPU_QS_NUM_INJ_GROUPS (??), 0-1
 */
#define VTSS_DEVCPU_QS_INJ_INJ_ERR(ri)       VTSS_IOREG(VTSS_TO_DEVCPU_QS,0x14 + (ri))

/** 
 * \brief
 * If the CPU aborts an on-going frame injection by a '1' to
 * INJ_CTRL::ABORT, the on-going frame injection is aborted and the
 * injection controller prepares for a new injection. This situation could
 * indicate a software error.
 *
 * \details 
 * '0': No error.
 * '1': Previous frame was aborted with a write to INJ_CTRL::ABORT or due
 * to an internal error.
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_ERR . ABORT_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_ERR_ABORT_ERR_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * If the CPU writes to INJ_WR without having initiated a frame injection
 * with INJ_CTRL, this sticky bit gets set.
 *
 * \details 
 * '0': No error.
 * '1': Erroneous write to INJ_WR has been made.
 *
 * Field: ::VTSS_DEVCPU_QS_INJ_INJ_ERR . WR_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_QS_INJ_INJ_ERR_WR_ERR_STICKY  VTSS_BIT(0)


#endif /* _VTSS_LUTON26_REGS_DEVCPU_QS_H_ */
