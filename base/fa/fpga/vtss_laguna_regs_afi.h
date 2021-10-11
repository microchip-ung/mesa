// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_AFI_H_
#define _VTSS_LAGUNA_REGS_AFI_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a AFI
 *
 * The Automatic Frame Injector (AFI) provides mechanisms for periodic
 * injection of PDUs. E.g. injection of
 * - OAM PDUs for continuity check, loss and delay measurement
 * - OAM PDUs for high bandwidth service activation test, ref. ITU Y.1564.
 * - IEEE 1588 PDUs
 *
 * With regards to the injection bandwidth supported by AFI, refer to
 * AFI:DTI_TBL.
 *
 ***********************************************************************/

/**
 * Register Group: \a AFI:MISC
 *
 * Miscellaneous AFI configuration
 */


/**
 * \brief Miscellaneous AFI control parameters
 *
 * \details
 * Register: \a AFI:MISC:MISC_CTRL
 */
#define VTSS_AFI_MISC_CTRL                   VTSS_IOREG(VTSS_TO_AFI,0xc146)

/**
 * \brief
 * Enable AFI.Must be set to 1 before any use of AFI.
 *
 * \details
 * Field: ::VTSS_AFI_MISC_CTRL . AFI_ENA
 */
#define  VTSS_F_AFI_MISC_CTRL_AFI_ENA(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_MISC_CTRL_AFI_ENA         VTSS_BIT(0)
#define  VTSS_X_AFI_MISC_CTRL_AFI_ENA(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Control information about new frame received by AFI for injection.
 *
 * \details
 * Register: \a AFI:MISC:NEW_FRM_CTRL
 */
#define VTSS_AFI_NEW_FRM_CTRL                VTSS_IOREG(VTSS_TO_AFI,0xc147)

/**
 * \brief
 * Valid bit for NEW_FRM_INFO.FRM_INFO.
 *
 * \details
 * Field: ::VTSS_AFI_NEW_FRM_CTRL . VLD
 */
#define  VTSS_F_AFI_NEW_FRM_CTRL_VLD(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_NEW_FRM_CTRL_VLD          VTSS_BIT(0)
#define  VTSS_X_AFI_NEW_FRM_CTRL_VLD(x)       VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Frame information about new frame received by AFI for injection.
 *
 * \details
 * Register: \a AFI:MISC:NEW_FRM_INFO
 */
#define VTSS_AFI_NEW_FRM_INFO                VTSS_IOREG(VTSS_TO_AFI,0xc148)

/**
 * \brief
 * Frame information for new frame received by AFI.The inforrmation must be
 * copied to FRM_INFO bits in FRM_ENTRY_PART0 and FRM_ENTRY_PART1.Once
 * FRM_INFO has been copied to FRM_TBL, then NEW_FRM_CTRL.VLD must be
 * cleared.Related
 * parameters:AFI:FRM_TBL:FRM_ENTRY_PART0.PART0AFI:FRM_TBL:FRM_ENTRY_PART1.
 * PART1
 *
 * \details
 * Bit 0-9: fp
 * Bit 10-15: dstp
 * Bit 16-18: eprio
 * Bit 19: short

 *
 * Field: ::VTSS_AFI_NEW_FRM_INFO . FRM_INFO
 */
#define  VTSS_F_AFI_NEW_FRM_INFO_FRM_INFO(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_AFI_NEW_FRM_INFO_FRM_INFO     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_AFI_NEW_FRM_INFO_FRM_INFO(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/**
 * \brief Errors from AFI block
 *
 * \details
 * These bits shall never get set.
 *
 * Register: \a AFI:MISC:ERR
 */
#define VTSS_AFI_ERR                         VTSS_IOREG(VTSS_TO_AFI,0xc149)

/**
 * \brief
 * FRM_OUT_CNT for a port was zero while an ack from FRD was received.If
 * enabled in STICKY_INFO_ENA.FRM_OUT_NEG_INFO_ENA, the corresponding port
 * number is stored in STICKY_INFO.PORT_NUM.
 *
 * \details
 * Field: ::VTSS_AFI_ERR . ERR_FRM_OUT_NEG_STICKY
 */
#define  VTSS_F_AFI_ERR_ERR_FRM_OUT_NEG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_ERR_ERR_FRM_OUT_NEG_STICKY  VTSS_BIT(0)
#define  VTSS_X_AFI_ERR_ERR_FRM_OUT_NEG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Warnings from AFI block
 *
 * \details
 * These bits shall normally not get set.
 *
 * Register: \a AFI:MISC:WARN
 */
#define VTSS_AFI_WARN                        VTSS_IOREG(VTSS_TO_AFI,0xc14a)

/**
 * \brief
 * A new frame for injection was received by AFI, but NEW_FRM_CTRL.VLD was
 * still 1.Check that NEW_FRM_CTRL.VLD is cleared upon copying
 * NEW_FRM_INFO.FRM_INFO to FRM_TBL.
 *
 * \details
 * Field: ::VTSS_AFI_WARN . WARN_NEW_FRM_VLD_STICKY
 */
#define  VTSS_F_AFI_WARN_WARN_NEW_FRM_VLD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_WARN_WARN_NEW_FRM_VLD_STICKY  VTSS_BIT(0)
#define  VTSS_X_AFI_WARN_WARN_NEW_FRM_VLD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * FRM_OUT_MAX has been reached for port.This is unusual, but may occur
 * when a large number of frames are successively injected to queues of the
 * same port or if the port flow controlled or is shaped to a low
 * bandwidth.The number of injections that can be outstanding (i.e. waiting
 * to be transmitted out of QSYS) for a port  at a time is configured in
 * AFI:PORT_TBL:PORT_CFG.FRM_OUT_MAX.If enabled in
 * STICKY_INFO_ENA.FRM_OUT_MAX_INFO_ENA, the corresponding port number is
 * stored in STICKY_INFO.PORT_NUM.
 *
 * \details
 * Field: ::VTSS_AFI_WARN . WARN_FRM_OUT_MAX_STICKY
 */
#define  VTSS_F_AFI_WARN_WARN_FRM_OUT_MAX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AFI_WARN_WARN_FRM_OUT_MAX_STICKY  VTSS_BIT(1)
#define  VTSS_X_AFI_WARN_WARN_FRM_OUT_MAX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * QSYS has asserted enq_stop. i.e. requested AFI to stop injecting
 * frames.This should normally not occur.If enabled in
 * STICKY_INFO_ENA.ENQ_STOP_INFO_ENA, the affected port number is stored in
 * STICKY_INFO.PORT_NUM.
 *
 * \details
 * Field: ::VTSS_AFI_WARN . WARN_ENQ_STOP_STICKY
 */
#define  VTSS_F_AFI_WARN_WARN_ENQ_STOP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_AFI_WARN_WARN_ENQ_STOP_STICKY  VTSS_BIT(2)
#define  VTSS_X_AFI_WARN_WARN_ENQ_STOP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * A TTI in TTI_TBL was elected to be processed, but was already being
 * processed.This may indicate that the length of a calendar slot is too
 * short (ref. AFI:TTI_MISC:TTI_CAL_SLOT_PTRS).If enabled in
 * STICKY_INFO_ENA.TTI_BUSY_INFO_ENA, the corresponding TTI pointer is
 * stored in STICKY_INFO.TTI_PTR.
 *
 * \details
 * Field: ::VTSS_AFI_WARN . WARN_TTI_BUSY_STICKY
 */
#define  VTSS_F_AFI_WARN_WARN_TTI_BUSY_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_AFI_WARN_WARN_TTI_BUSY_STICKY  VTSS_BIT(3)
#define  VTSS_X_AFI_WARN_WARN_TTI_BUSY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DTI_CNT_DOWN has reached its maximum negative value.
 *
 * \details
 * Field: ::VTSS_AFI_WARN . WARN_DTI_CNT_DOWN_MAX_NEG_STICKY
 */
#define  VTSS_F_AFI_WARN_WARN_DTI_CNT_DOWN_MAX_NEG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_AFI_WARN_WARN_DTI_CNT_DOWN_MAX_NEG_STICKY  VTSS_BIT(4)
#define  VTSS_X_AFI_WARN_WARN_DTI_CNT_DOWN_MAX_NEG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief Additional information about sticky bit events.
 *
 * \details
 * The information is updated if
 * a) Enabled in STICKY_INFO_ENA
 * and
 * b) STICKY_INFO_WR_CNT is > 0
 *
 * Register: \a AFI:MISC:STICKY_INFO
 */
#define VTSS_AFI_STICKY_INFO                 VTSS_IOREG(VTSS_TO_AFI,0xc14b)

/**
 * \brief
 * Port number corresponding to sticky bit event.
 *
 * \details
 * Field: ::VTSS_AFI_STICKY_INFO . PORT_NUM
 */
#define  VTSS_F_AFI_STICKY_INFO_PORT_NUM(x)   VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_AFI_STICKY_INFO_PORT_NUM      VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_AFI_STICKY_INFO_PORT_NUM(x)   VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * TTI pointer corresponding to sticky bit event.
 *
 * \details
 * Field: ::VTSS_AFI_STICKY_INFO . TTI_PTR
 */
#define  VTSS_F_AFI_STICKY_INFO_TTI_PTR(x)    VTSS_ENCODE_BITFIELD(x,8,12)
#define  VTSS_M_AFI_STICKY_INFO_TTI_PTR       VTSS_ENCODE_BITMASK(8,12)
#define  VTSS_X_AFI_STICKY_INFO_TTI_PTR(x)    VTSS_EXTRACT_BITFIELD(x,8,12)

/**
 * \brief
 * Number of times STICKY_INFO.PORT_NUM and  STICKY_INFO.TTI_PTR is allowed
 * to be updated.
 *
 * \details
 * 0: Illegal
 * 1: Max one update of STICKY_INFO allowed (decremented for each update).
 * 2: Max two updates of STICKY_INFO allowed (decremented for each update).
 * ...
 * 15: Any number of updates of STICKY_INFO allowed (not decremented).
 *
 * Field: ::VTSS_AFI_STICKY_INFO . STICKY_INFO_WR_CNT
 */
#define  VTSS_F_AFI_STICKY_INFO_STICKY_INFO_WR_CNT(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_AFI_STICKY_INFO_STICKY_INFO_WR_CNT     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_AFI_STICKY_INFO_STICKY_INFO_WR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Enabling of additional information about sticky bit events.
 *
 * \details
 * Register: \a AFI:MISC:STICKY_INFO_ENA
 */
#define VTSS_AFI_STICKY_INFO_ENA             VTSS_IOREG(VTSS_TO_AFI,0xc14c)

/**
 * \brief
 * Enable updating of STICKY_INFO.PORT_NUM for ERR_FRM_OUT_NEG_STICKY.
 *
 * \details
 * Field: ::VTSS_AFI_STICKY_INFO_ENA . FRM_OUT_NEG_INFO_ENA
 */
#define  VTSS_F_AFI_STICKY_INFO_ENA_FRM_OUT_NEG_INFO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_STICKY_INFO_ENA_FRM_OUT_NEG_INFO_ENA  VTSS_BIT(0)
#define  VTSS_X_AFI_STICKY_INFO_ENA_FRM_OUT_NEG_INFO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enable updating of STICKY_INFO.PORT_NUM for WARN_FRM_OUT_MAX_STICKY.
 *
 * \details
 * Field: ::VTSS_AFI_STICKY_INFO_ENA . FRM_OUT_MAX_INFO_ENA
 */
#define  VTSS_F_AFI_STICKY_INFO_ENA_FRM_OUT_MAX_INFO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AFI_STICKY_INFO_ENA_FRM_OUT_MAX_INFO_ENA  VTSS_BIT(1)
#define  VTSS_X_AFI_STICKY_INFO_ENA_FRM_OUT_MAX_INFO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable updating of STICKY_INFO.PORT_NUM for WARN_ENQ_STOP_STICKY.
 *
 * \details
 * Field: ::VTSS_AFI_STICKY_INFO_ENA . ENQ_STOP_INFO_ENA
 */
#define  VTSS_F_AFI_STICKY_INFO_ENA_ENQ_STOP_INFO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_AFI_STICKY_INFO_ENA_ENQ_STOP_INFO_ENA  VTSS_BIT(2)
#define  VTSS_X_AFI_STICKY_INFO_ENA_ENQ_STOP_INFO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable updating of STICKY_INFO.TTI_PTR for WARN_TTI_BUSY_STICKY.
 *
 * \details
 * Field: ::VTSS_AFI_STICKY_INFO_ENA . TTI_BUSY_INFO_ENA
 */
#define  VTSS_F_AFI_STICKY_INFO_ENA_TTI_BUSY_INFO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_AFI_STICKY_INFO_ENA_TTI_BUSY_INFO_ENA  VTSS_BIT(3)
#define  VTSS_X_AFI_STICKY_INFO_ENA_TTI_BUSY_INFO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/**
 * \brief Lenght of DTI Duration Tick
 *
 * \details
 * Register: \a AFI:MISC:DTI_DURATION_TICK_LEN
 */
#define VTSS_AFI_DTI_DURATION_TICK_LEN       VTSS_IOREG(VTSS_TO_AFI,0xc14d)

/**
 * \brief
 * Lenght of DTI Duration Tick in clock cycles.Default value corresponds to
 * 0.1ms.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_DURATION_TICK_LEN . DTI_DURATION_TICK_LEN
 */
#define  VTSS_F_AFI_DTI_DURATION_TICK_LEN_DTI_DURATION_TICK_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,17)
#define  VTSS_M_AFI_DTI_DURATION_TICK_LEN_DTI_DURATION_TICK_LEN     VTSS_ENCODE_BITMASK(0,17)
#define  VTSS_X_AFI_DTI_DURATION_TICK_LEN_DTI_DURATION_TICK_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,17)

/**
 * Register Group: \a AFI:FRM_TBL
 *
 * Frame Table
 */


/**
 * \brief Entry type and pointer to next Frame Table entry.
 *
 * \details
 * Note:
 * Write operations to entries in the frame table, which are in the process
 * of being removed (FRM_RM=1, see FRM_ENTRY_PART0) are not allowed.
 *
 * Register: \a AFI:FRM_TBL:FRM_NEXT_AND_TYPE
 *
 * @param gi Replicator: x_GAZ_AFI_FRM_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_FRM_NEXT_AND_TYPE(gi)       VTSS_IOREG_IX(VTSS_TO_AFI,0x8000,gi,4,0,0)

/**
 * \brief
 * Pointer to next Frame Table entry.Only applicable for frames used for
 * DTI.
 *
 * \details
 * Field: ::VTSS_AFI_FRM_NEXT_AND_TYPE . NEXT_PTR
 */
#define  VTSS_F_AFI_FRM_NEXT_AND_TYPE_NEXT_PTR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_AFI_FRM_NEXT_AND_TYPE_NEXT_PTR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_AFI_FRM_NEXT_AND_TYPE_NEXT_PTR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Entry Type.Delay entries are only applicable to DTI.The Entry Type
 * controls the use of FRM_ENTRY_PART0.PART0.
 *
 * \details
 * 0: Frame
 * 1: Delay
 *
 * Field: ::VTSS_AFI_FRM_NEXT_AND_TYPE . ENTRY_TYPE
 */
#define  VTSS_F_AFI_FRM_NEXT_AND_TYPE_ENTRY_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AFI_FRM_NEXT_AND_TYPE_ENTRY_TYPE  VTSS_BIT(16)
#define  VTSS_X_AFI_FRM_NEXT_AND_TYPE_ENTRY_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)


/**
 * \brief Frame Table entry configuration, part 0
 *
 * \details
 * Note:
 * Write operations to entries in the frame table, which are in the process
 * of being removed (FRM_RM=1, see FRM_ENTRY_PART1) are not allowed.
 *
 * Register: \a AFI:FRM_TBL:FRM_ENTRY_PART0
 *
 * @param gi Replicator: x_GAZ_AFI_FRM_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_FRM_ENTRY_PART0(gi)         VTSS_IOREG_IX(VTSS_TO_AFI,0x8000,gi,4,0,1)

/**
 * \brief
 * Configuration of frame or delay entry in Frame Table.Delay entries are
 * only used for DTI.Delay entry fields:DELAY: Delay between injection of
 * start of frames. Unit: One system clock cycle.Frame entry
 * fields:FRM_INFO.fp:FRM_INFO.dstp:Frame information, ref.
 * AFI:MISC:NEW_FRM_INFO.FRM_INFO.INJ_CNT: Injection count. Number times to
 * inject frame.Frame is ignored if INJ_CNT=0 or FRM_RM=1.Only applicable
 * for DTI.Related parameters:AFI:FRM_TBL:FRM_ENTRY_PART1.PART1
 *
 * \details
 * Delay entry type:
 * Bit 0-29: DELAY
 *
 * Frame entry type:
 * Bit 0-9: fp
 * Bit 10-15: dstp
 * Bit 16-23: inj_cnt
 *
 * Field: ::VTSS_AFI_FRM_ENTRY_PART0 . PART0
 */
#define  VTSS_F_AFI_FRM_ENTRY_PART0_PART0(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_AFI_FRM_ENTRY_PART0_PART0     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_AFI_FRM_ENTRY_PART0_PART0(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Frame Table entry configuration, part 1
 *
 * \details
 * Note:
 * Write operations to entries in the frame table, which are in the process
 * of being removed (FRM_RM=1) are not allowed.
 *
 * Register: \a AFI:FRM_TBL:FRM_ENTRY_PART1
 *
 * @param gi Replicator: x_GAZ_AFI_FRM_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_FRM_ENTRY_PART1(gi)         VTSS_IOREG_IX(VTSS_TO_AFI,0x8000,gi,4,0,2)

/**
 * \brief
 * Configuration of frame entry in Frame Table.Delay entry fields:PART1 is
 * not used for delay entries.Frame entry
 * fields:FRM_INFO.short:FRM_INFO.eprio:Frame information, ref.
 * AFI:MISC:NEW_FRM_INFO.FRM_INFO.FRM_RM:When set, next frame injection
 * causes frame to be removed from buffer memory. This injection will not
 * be transmitted on the destination port.Once removed, HW sets
 * FRM_GONE=1.FRM_GONE:Set by AFI when frame has been removed from buffer
 * memory.Related parameters:AFI:FRM_TBL:FRM_ENTRY_PART0.PART0
 *
 * \details
 * Bit 0: FRM_INFO.short
 * Bit 1-3: FRM_INFO.eprio
 * Bit 4: FRM_RM
 * Bit 5: FRM_GONE
 *
 * Field: ::VTSS_AFI_FRM_ENTRY_PART1 . PART1
 */
#define  VTSS_F_AFI_FRM_ENTRY_PART1_PART1(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_AFI_FRM_ENTRY_PART1_PART1     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_AFI_FRM_ENTRY_PART1_PART1(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a AFI:DTI_TBL
 *
 * Delay Triggered Injection Table
 */


/**
 * \brief Configuration of DTI Mode.
 *
 * \details
 * Register: \a AFI:DTI_TBL:DTI_MODE
 *
 * @param gi Replicator: x_GAZ_AFI_DTI_TBL_DEPTH (??), 0-31
 */
#define VTSS_AFI_DTI_MODE(gi)                VTSS_IOREG_IX(VTSS_TO_AFI,0xc000,gi,8,0,0)

/**
 * \brief
 * Configuration of DTI mode.
 *
 * \details
 * 0:  Frame sequence shall be injected DTI_CNT.CNT times.
 *
 * 1:
 * Frame sequence shall be injected until stopped (DTI_CTRL.ENA=0).
 * Number of frames injected is counted in DTI_CNT.CNT.
 *
 * 2:
 * Frame sequence shall be injected DTI_CNT.CNT times. Once this is done,
 * the DTI pointed to by AFI:DTI_TBL:DTI_MODE.DTI_NEXT will be enabled.
 * This can be used to concatenate DTIs.
 *
 * 3:
 * Reserved.
 *
 * Field: ::VTSS_AFI_DTI_MODE . MODE
 */
#define  VTSS_F_AFI_DTI_MODE_MODE(x)          VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_AFI_DTI_MODE_MODE             VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_AFI_DTI_MODE_MODE(x)          VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * If the last frame table entry of a DTI sequence is a delay, then this is
 * termed a "trailing delay".By setting TRAILING_DELAY_SEQ_CNT=N a trailing
 * delay is only applied for every Nth sequence injection.This can be used
 * to "fine tune" the bandwidth of a DTI sequence.TRAILING_DELAY_SEQ_CNT=0
 * disables this feature.If a DTI sequence (in the frame table) has no
 * trailing delay, then TRAILING_DELAY_SEQ_CNT has no effect.
 *
 * \details
 * 0: Disable feature.
 * 1: Apply trailing delay for every sequence injected.
 * 2: Apply trailing delay for every 2nd sequence injected.
 * 3: Apply trailing delay for every 3rd sequence injected.
 * ...
 *
 * Field: ::VTSS_AFI_DTI_MODE . TRAILING_DELAY_SEQ_CNT
 */
#define  VTSS_F_AFI_DTI_MODE_TRAILING_DELAY_SEQ_CNT(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_AFI_DTI_MODE_TRAILING_DELAY_SEQ_CNT     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_AFI_DTI_MODE_TRAILING_DELAY_SEQ_CNT(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Number of remaining injections of current frame in frame sequence
 * (NEXT_FRM_PTR).Must be set to 0 when (re)starting DTI.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_MODE . FRM_INJ_CNT
 */
#define  VTSS_F_AFI_DTI_MODE_FRM_INJ_CNT(x)   VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_AFI_DTI_MODE_FRM_INJ_CNT      VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_AFI_DTI_MODE_FRM_INJ_CNT(x)   VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Number of clock cycles the DTI shall be postponed after experiencing
 * flow control from FRD.Such DTIs may have to be postponed to avoid
 * blocking frame table access for TTIs.To account for a worst-case
 * situation, where all DTIs are flow controlled, a value of 4x<number of
 * active DTIs> suffices.The default value corresponds to all DTIs
 * active.The configured value is counted down in DTI_FC_CNT_DOWN and when
 * zero is reached, another injection attempt is made. In the meantime
 * DTI_CNT_DOWN goes negative, such that the additional delay is subtracted
 * from the next delay in the DTI sequence.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_MODE . FC_POSTPONE_LEN
 */
#define  VTSS_F_AFI_DTI_MODE_FC_POSTPONE_LEN(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_AFI_DTI_MODE_FC_POSTPONE_LEN     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_AFI_DTI_MODE_FC_POSTPONE_LEN(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * See AFI:DTI_TBL:DTI_MODE.MODE, encoding 2.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_MODE . DTI_NEXT
 */
#define  VTSS_F_AFI_DTI_MODE_DTI_NEXT(x)      VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_AFI_DTI_MODE_DTI_NEXT         VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_AFI_DTI_MODE_DTI_NEXT(x)      VTSS_EXTRACT_BITFIELD(x,24,5)

/**
 * \brief
 * Controls whether FC_POSTPONE_LEN is added to DTI_FC_CNT_DOWN or
 * DTI_CNT_DOWN when flow control from FRD is encountered.
 *
 * \details
 * 0: Add FC_POSTPONE_LEN to DTI_FC_CNT_DOWN when FC is encountered.
 * 1: Add FC_POSTPONE_LEN to DTI_CNT_DOWN when FC is encountered.
 *
 * Field: ::VTSS_AFI_DTI_MODE . FC_POSTPONE_MODE
 */
#define  VTSS_F_AFI_DTI_MODE_FC_POSTPONE_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_AFI_DTI_MODE_FC_POSTPONE_MODE  VTSS_BIT(31)
#define  VTSS_X_AFI_DTI_MODE_FC_POSTPONE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Port and queue for injected frames.
 *
 * \details
 * Register: \a AFI:DTI_TBL:DTI_PORT_QU
 *
 * @param gi Replicator: x_GAZ_AFI_DTI_TBL_DEPTH (??), 0-31
 */
#define VTSS_AFI_DTI_PORT_QU(gi)             VTSS_IOREG_IX(VTSS_TO_AFI,0xc000,gi,8,0,1)

/**
 * \brief
 * Port number which injection queue transmits on.Injection queue is
 * selected by QU_NUM.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_PORT_QU . PORT_NUM
 */
#define  VTSS_F_AFI_DTI_PORT_QU_PORT_NUM(x)   VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_AFI_DTI_PORT_QU_PORT_NUM      VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_AFI_DTI_PORT_QU_PORT_NUM(x)   VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * QU_NUM selects the queue, which the frame is injected into.For details,
 * refer to the functional description of the queue system in the
 * datasheet.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_PORT_QU . QU_NUM
 */
#define  VTSS_F_AFI_DTI_PORT_QU_QU_NUM(x)     VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_AFI_DTI_PORT_QU_QU_NUM        VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_AFI_DTI_PORT_QU_QU_NUM(x)     VTSS_EXTRACT_BITFIELD(x,8,14)


/**
 * \brief DTI Frame Table pointers
 *
 * \details
 * Register: \a AFI:DTI_TBL:DTI_FRM
 *
 * @param gi Replicator: x_GAZ_AFI_DTI_TBL_DEPTH (??), 0-31
 */
#define VTSS_AFI_DTI_FRM(gi)                 VTSS_IOREG_IX(VTSS_TO_AFI,0xc000,gi,8,0,2)

/**
 * \brief
 * Pointer to first frame in frame sequence.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_FRM . FIRST_FRM_PTR
 */
#define  VTSS_F_AFI_DTI_FRM_FIRST_FRM_PTR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_AFI_DTI_FRM_FIRST_FRM_PTR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_AFI_DTI_FRM_FIRST_FRM_PTR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Pointer to next frame in frame sequence.Must be set to same value as
 * FIRST_FRM_PTR when (re)starting DTI.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_FRM . NEXT_FRM_PTR
 */
#define  VTSS_F_AFI_DTI_FRM_NEXT_FRM_PTR(x)   VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_AFI_DTI_FRM_NEXT_FRM_PTR      VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_AFI_DTI_FRM_NEXT_FRM_PTR(x)   VTSS_EXTRACT_BITFIELD(x,16,12)


/**
 * \brief DTI counter
 *
 * \details
 * Register: \a AFI:DTI_TBL:DTI_CNT
 *
 * @param gi Replicator: x_GAZ_AFI_DTI_TBL_DEPTH (??), 0-31
 */
#define VTSS_AFI_DTI_CNT(gi)                 VTSS_IOREG_IX(VTSS_TO_AFI,0xc000,gi,8,0,3)

/**
 * \brief
 * DTI_MODE.MODE=0, 2:Number of remaining frame sequences to inject.
 * Configured by SW, decremented by AFI.DTI_MODE.MODE=1:Number of frames
 * injected.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_CNT . CNT
 */
#define  VTSS_F_AFI_DTI_CNT_CNT(x)            VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_AFI_DTI_CNT_CNT               VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_AFI_DTI_CNT_CNT(x)            VTSS_EXTRACT_BITFIELD(x,0,31)


/**
 * \brief Duration of last DTI run
 *
 * \details
 * Register: \a AFI:DTI_TBL:DTI_DURATION
 *
 * @param gi Replicator: x_GAZ_AFI_DTI_TBL_DEPTH (??), 0-31
 */
#define VTSS_AFI_DTI_DURATION(gi)            VTSS_IOREG_IX(VTSS_TO_AFI,0xc000,gi,8,0,4)

/**
 * \brief
 * Duration of last DTI run in DTI Duration Ticks.Before starting a DTI,
 * DURATION must be set to 0.When AFI:DTI_MISC:DTI_CTRL.ENA becomes 0,
 * DURATION is updated with the duration of the DTI run.While a DTI is
 * running DURATION holds an internal time stamp of when the DTI was
 * started. This value is not intended for SW usage.Related
 * parameters:AFI:MISC:DTI_DURATION_TICK_LEN.DTI_DURATION_TICK_LEN
 *
 * \details
 * Field: ::VTSS_AFI_DTI_DURATION . DURATION
 */
#define  VTSS_F_AFI_DTI_DURATION_DURATION(x)  VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_AFI_DTI_DURATION_DURATION     VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_AFI_DTI_DURATION_DURATION(x)  VTSS_EXTRACT_BITFIELD(x,0,31)

/**
 * Register Group: \a AFI:DTI_MISC
 *
 * Miscellaneous DTI configuration and status information
 */


/**
 * \brief DTI flow control count down counters
 *
 * \details
 * When FC is experienced between AFI and FRD, then DTI an injecting DTI
 * must "backoff" for FC_POSTPONE_LEN clock cycles. This is handled by this
 * counter.
 *
 * Register: \a AFI:DTI_MISC:DTI_FC_CNT_DOWN
 *
 * @param gi Replicator: x_GAZ_AFI_DTI_TBL_DEPTH (??), 0-31
 */
#define VTSS_AFI_DTI_FC_CNT_DOWN(gi)         VTSS_IOREG_IX(VTSS_TO_AFI,0xc14e,gi,3,0,0)

/**
 * \brief
 * Remaining number of clock cycles before DTI is allowed to attempt
 * injection again after experiencing FC from FRD.This field is set to
 * FC_POSTPONE_LEN when FC from FRD is experienced.Note:Unlike CNT_DOWN,
 * FC_CNT_DOWN is always >=0 (so no two's complement encoding).
 *
 * \details
 * Field: ::VTSS_AFI_DTI_FC_CNT_DOWN . FC_CNT_DOWN
 */
#define  VTSS_F_AFI_DTI_FC_CNT_DOWN_FC_CNT_DOWN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_DTI_FC_CNT_DOWN_FC_CNT_DOWN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_DTI_FC_CNT_DOWN_FC_CNT_DOWN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief DTI count down counters
 *
 * \details
 * Register: \a AFI:DTI_MISC:DTI_CNT_DOWN
 *
 * @param gi Replicator: x_GAZ_AFI_DTI_TBL_DEPTH (??), 0-31
 */
#define VTSS_AFI_DTI_CNT_DOWN(gi)            VTSS_IOREG_IX(VTSS_TO_AFI,0xc14e,gi,3,0,1)

/**
 * \brief
 * Remaining number of clock cycles before next injection.May become
 * negative while waiting for table/injection access. Two's complement
 * encoded.Should be set to 0 when (re)starting DTI (unless an initial
 * delay is desirable).
 *
 * \details
 * Field: ::VTSS_AFI_DTI_CNT_DOWN . CNT_DOWN
 */
#define  VTSS_F_AFI_DTI_CNT_DOWN_CNT_DOWN(x)  VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_AFI_DTI_CNT_DOWN_CNT_DOWN     VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_AFI_DTI_CNT_DOWN_CNT_DOWN(x)  VTSS_EXTRACT_BITFIELD(x,0,31)


/**
 * \brief DTI control
 *
 * \details
 * Register: \a AFI:DTI_MISC:DTI_CTRL
 *
 * @param gi Replicator: x_GAZ_AFI_DTI_TBL_DEPTH (??), 0-31
 */
#define VTSS_AFI_DTI_CTRL(gi)                VTSS_IOREG_IX(VTSS_TO_AFI,0xc14e,gi,3,0,2)

/**
 * \brief
 * Enable DTI.If MODE=0 or MODE=2, then ENA is cleared by AFI when
 * configured number of sequences have been injected.Before (re)starting a
 * DTI the following initialization should be done:DURATION must be set to
 * 0.NEXT_FRM_PTR should be set to FIRST_FRM_PTR.DTI_CNT_DOWN.CNT_DOWN
 * should be set to 0.FRM_INJ_CNT should be set to 0AFI::MISC_CTRL.AFI_ENA
 * must be set to 1.If MODE=2, then the AFI will set ENA=1 for the DTI
 * pointed to by DTI_NEXT once the DTI with MODE=2 completes.
 *
 * \details
 * Field: ::VTSS_AFI_DTI_CTRL . ENA
 */
#define  VTSS_F_AFI_DTI_CTRL_ENA(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_DTI_CTRL_ENA              VTSS_BIT(0)
#define  VTSS_X_AFI_DTI_CTRL_ENA(x)           VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * DTI bandwidth.Used to give arbitration precedence to high bandwidth
 * DTIs.
 *
 * \details
 * 0: <5Gbps
 * 1: >=5Gbps
 *
 * Field: ::VTSS_AFI_DTI_CTRL . BW
 */
#define  VTSS_F_AFI_DTI_CTRL_BW(x)            VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AFI_DTI_CTRL_BW               VTSS_BIT(1)
#define  VTSS_X_AFI_DTI_CTRL_BW(x)            VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * Register Group: \a AFI:TTI_TBL
 *
 * Timer Triggered Injection Table
 */


/**
 * \brief Port and queue for injected frames.
 *
 * \details
 * Register: \a AFI:TTI_TBL:TTI_PORT_QU
 *
 * @param gi Replicator: x_GAZ_AFI_TTI_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_TTI_PORT_QU(gi)             VTSS_IOREG_IX(VTSS_TO_AFI,0x0,gi,8,0,0)

/**
 * \brief
 * Port number which injection queue transmits on.Injection queue is
 * selected by QU_NUM.PORT_NUM must not be changed when timer is enabled.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_PORT_QU . PORT_NUM
 */
#define  VTSS_F_AFI_TTI_PORT_QU_PORT_NUM(x)   VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_AFI_TTI_PORT_QU_PORT_NUM      VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_AFI_TTI_PORT_QU_PORT_NUM(x)   VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * QU_NUM selects the queue, which the frame is injected into.For details,
 * refer to the functional description of the queue system in the
 * datasheet.QU_NUM must not be changed when timer is enabled.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_PORT_QU . QU_NUM
 */
#define  VTSS_F_AFI_TTI_PORT_QU_QU_NUM(x)     VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_AFI_TTI_PORT_QU_QU_NUM        VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_AFI_TTI_PORT_QU_QU_NUM(x)     VTSS_EXTRACT_BITFIELD(x,8,14)


/**
 * \brief TTI Timer configuration
 *
 * \details
 * Register: \a AFI:TTI_TBL:TTI_TIMER
 *
 * @param gi Replicator: x_GAZ_AFI_TTI_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_TTI_TIMER(gi)               VTSS_IOREG_IX(VTSS_TO_AFI,0x0,gi,8,0,1)

/**
 * \brief
 * Timer Tick, which TTI shall use.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TIMER . TICK_IDX
 */
#define  VTSS_F_AFI_TTI_TIMER_TICK_IDX(x)     VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_AFI_TTI_TIMER_TICK_IDX        VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_AFI_TTI_TIMER_TICK_IDX(x)     VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Configuration of injection time jitter for TTI.
 *
 * \details
 * 0: No jitter
 * 1: Timer is set to a random value in the range [TIMER_LEN*0.75;
 * TIMER_LEN]
 * 2: Timer is set to a random value in the range [TIMER_LEN*0.50;
 * TIMER_LEN]
 * 3: Timer is set to a random value in the range [1;TIMER_LEN]

 *
 * Field: ::VTSS_AFI_TTI_TIMER . JITTER
 */
#define  VTSS_F_AFI_TTI_TIMER_JITTER(x)       VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_AFI_TTI_TIMER_JITTER          VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_AFI_TTI_TIMER_JITTER(x)       VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Enable timer.Note that disabling a timer can also be achieved by setting
 * TIMER_LEN to 0.Before enabling a timer AFI::MISC_CTRL.AFI_ENA must be
 * set to 1.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TIMER . TIMER_ENA
 */
#define  VTSS_F_AFI_TTI_TIMER_TIMER_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_AFI_TTI_TIMER_TIMER_ENA       VTSS_BIT(6)
#define  VTSS_X_AFI_TTI_TIMER_TIMER_ENA(x)    VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Number of ticks of configured TICK_IDX between frame injections.The
 * period between each injection becomes   tick_period x TIMER_LENSetting
 * TIMER_LEN to non-zero value enables TTI, provided that TIMER_ENA is set
 * to 1.TTIs can be disabled by either setting TIMER_LEN=0 or by setting
 * TIMER_ENA=0.0x1FF (= Inject ASAP) is intended for removal of frame from
 * buffer memory. Upon injection, HW sets TIMER_LEN to 0 (=Disable).Before
 * setting TIMER_LEN, TICK_CNT should be set to a random value in range
 * 1-TIMER_LEN (unless a specific initial timer value is desirable).
 *
 * \details
 * 0 => Disable TTI (can also be achieved by setting TIMER_ENA=0).
 * 1 => 1 tick
 * 2 => 2 ticks
 * ...
 * 0x1ff => Inject ASAP, then set to TIMER_LEN=0 by AFI.
 *
 * Field: ::VTSS_AFI_TTI_TIMER . TIMER_LEN
 */
#define  VTSS_F_AFI_TTI_TIMER_TIMER_LEN(x)    VTSS_ENCODE_BITFIELD(x,16,9)
#define  VTSS_M_AFI_TTI_TIMER_TIMER_LEN       VTSS_ENCODE_BITMASK(16,9)
#define  VTSS_X_AFI_TTI_TIMER_TIMER_LEN(x)    VTSS_EXTRACT_BITFIELD(x,16,9)


/**
 * \brief Frame pointer for TTI
 *
 * \details
 * Register: \a AFI:TTI_TBL:TTI_FRM
 *
 * @param gi Replicator: x_GAZ_AFI_TTI_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_TTI_FRM(gi)                 VTSS_IOREG_IX(VTSS_TO_AFI,0x0,gi,8,0,2)

/**
 * \brief
 * Pointer to the frame in Frame Table, which TTI shall inject.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_FRM . FRM_PTR
 */
#define  VTSS_F_AFI_TTI_FRM_FRM_PTR(x)        VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_AFI_TTI_FRM_FRM_PTR           VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_AFI_TTI_FRM_FRM_PTR(x)        VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief Current state of TTI's tick counter
 *
 * \details
 * Register: \a AFI:TTI_TBL:TTI_TICKS
 *
 * @param gi Replicator: x_GAZ_AFI_TTI_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_TTI_TICKS(gi)               VTSS_IOREG_IX(VTSS_TO_AFI,0x0,gi,8,0,3)

/**
 * \brief
 * Number of ticks until next injection.Frame is injected when TICK_CNT=0.
 * Upon injection TICK_CNT gets set to TIMER_LEN.Should be set to a random
 * value in range 1-TIMER_LEN before starting TTI.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICKS . TICK_CNT
 */
#define  VTSS_F_AFI_TTI_TICKS_TICK_CNT(x)     VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_AFI_TTI_TICKS_TICK_CNT        VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_AFI_TTI_TICKS_TICK_CNT(x)     VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Ticks era value last time TTI was processed.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICKS . LAST_TICK_ERA
 */
#define  VTSS_F_AFI_TTI_TICKS_LAST_TICK_ERA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AFI_TTI_TICKS_LAST_TICK_ERA   VTSS_BIT(16)
#define  VTSS_X_AFI_TTI_TICKS_LAST_TICK_ERA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)


/**
 * \brief Miscellaneous TTI parameters
 *
 * \details
 * Register: \a AFI:TTI_TBL:TTI_MISC_CFG
 *
 * @param gi Replicator: x_GAZ_AFI_TTI_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_TTI_MISC_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_AFI,0x0,gi,8,0,4)

/**
 * \brief
 * Enable counting of injected frames in
 * AFI:TTI_MISC:TTI_INJ_CNT.TTI_INJ_CNT.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_MISC_CFG . INJ_CNT_ENA
 */
#define  VTSS_F_AFI_TTI_MISC_CFG_INJ_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_TTI_MISC_CFG_INJ_CNT_ENA  VTSS_BIT(0)
#define  VTSS_X_AFI_TTI_MISC_CFG_INJ_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TUPE Control
 *
 * \details
 * Control value for Table UPdate Engine (TUPE).
 *
 * See AFI:TUPE.
 *
 * Register: \a AFI:TTI_TBL:TTI_TUPE_CTRL
 *
 * @param gi Replicator: x_GAZ_AFI_TTI_TBL_DEPTH (??), 0-4095
 */
#define VTSS_AFI_TTI_TUPE_CTRL(gi)           VTSS_IOREG_IX(VTSS_TO_AFI,0x0,gi,8,0,5)

/**
 * \brief
 * Control value for Table UPdate Engine (TUPE).See AFI:TUPE.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TUPE_CTRL . TUPE_CTRL
 */
#define  VTSS_F_AFI_TTI_TUPE_CTRL_TUPE_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_TTI_TUPE_CTRL_TUPE_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_TTI_TUPE_CTRL_TUPE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a AFI:TTI_TICKS
 *
 * TTI Tick configuration
 */


/**
 * \brief Base Tick configuration.
 *
 * \details
 * Register: \a AFI:TTI_TICKS:TTI_TICK_BASE
 */
#define VTSS_AFI_TTI_TICK_BASE               VTSS_IOREG(VTSS_TO_AFI,0xc1ae)

/**
 * \brief
 * Length of TTI Base Tick.Unit: One system clock cycle.In default
 * configuration and a clock cycle of 11875 ps, the tick length corresponds
 * to 52us.If the device is uses a longer clock cycle, then the value of
 * BASE_LEN must be reconfigured accordingly.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_BASE . BASE_LEN
 */
#define  VTSS_F_AFI_TTI_TICK_BASE_BASE_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_AFI_TTI_TICK_BASE_BASE_LEN     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_AFI_TTI_TICK_BASE_BASE_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,13)

/**
 * \brief
 * Current value of Base Tick counter.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_BASE . BASE_CNT
 */
#define  VTSS_F_AFI_TTI_TICK_BASE_BASE_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,13)
#define  VTSS_M_AFI_TTI_TICK_BASE_BASE_CNT     VTSS_ENCODE_BITMASK(16,13)
#define  VTSS_X_AFI_TTI_TICK_BASE_BASE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,13)


/**
 * \brief Length of TTI Ticks 0-3
 *
 * \details
 * Register: \a AFI:TTI_TICKS:TTI_TICK_LEN_0_3
 */
#define VTSS_AFI_TTI_TICK_LEN_0_3            VTSS_IOREG(VTSS_TO_AFI,0xc1af)

/**
 * \brief
 * Length of TTI Tick 0.Unit: Base Ticks, as configured in
 * TTI_TICK_BASE.BASE_LEN.In default configuration the tick length
 * corresponds to 52us.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_LEN_0_3 . LEN0
 */
#define  VTSS_F_AFI_TTI_TICK_LEN_0_3_LEN0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_TTI_TICK_LEN_0_3_LEN0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Length of TTI Tick 1.Unit: TTI Tick 0, as configured in
 * TTI_TICK_LEN_0_3.LEN0.In default configuration the tick length
 * corresponds to 416us.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_LEN_0_3 . LEN1
 */
#define  VTSS_F_AFI_TTI_TICK_LEN_0_3_LEN1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_AFI_TTI_TICK_LEN_0_3_LEN1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Length of TTI Tick 2.Unit: TTI Tick 1, as configured in
 * TTI_TICK_LEN_0_3.LEN1.In default configuration the tick length
 * corresponds to 3.3ms.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_LEN_0_3 . LEN2
 */
#define  VTSS_F_AFI_TTI_TICK_LEN_0_3_LEN2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_AFI_TTI_TICK_LEN_0_3_LEN2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Length of TTI Tick 3.Unit: TTI Tick 2, as configured in
 * TTI_TICK_LEN_0_3.LEN2.In default configuration the tick length
 * corresponds to 10ms.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_LEN_0_3 . LEN3
 */
#define  VTSS_F_AFI_TTI_TICK_LEN_0_3_LEN3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_AFI_TTI_TICK_LEN_0_3_LEN3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_AFI_TTI_TICK_LEN_0_3_LEN3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Length of TTI Ticks 4-7
 *
 * \details
 * Register: \a AFI:TTI_TICKS:TTI_TICK_LEN_4_7
 */
#define VTSS_AFI_TTI_TICK_LEN_4_7            VTSS_IOREG(VTSS_TO_AFI,0xc1b0)

/**
 * \brief
 * Length of TTI Tick 4.Unit: TTI Tick 3, as configured in
 * TTI_TICK_LEN_0_3.LEN3.In default configuration the tick length
 * corresponds to 100ms.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_LEN_4_7 . LEN4
 */
#define  VTSS_F_AFI_TTI_TICK_LEN_4_7_LEN4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_TTI_TICK_LEN_4_7_LEN4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Length of TTI Tick 5.Unit: TTI Tick 4, as configured in
 * TTI_TICK_LEN_4_7.LEN4.In default configuration the tick length
 * corresponds to 1s.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_LEN_4_7 . LEN5
 */
#define  VTSS_F_AFI_TTI_TICK_LEN_4_7_LEN5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_AFI_TTI_TICK_LEN_4_7_LEN5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Length of TTI Tick 6.Unit: TTI Tick 5, as configured in
 * TTI_TICK_LEN_4_7.LEN5.In default configuration the tick length
 * corresponds to 10s.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_LEN_4_7 . LEN6
 */
#define  VTSS_F_AFI_TTI_TICK_LEN_4_7_LEN6(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_AFI_TTI_TICK_LEN_4_7_LEN6     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN6(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Length of TTI Tick 7.Unit: TTI Tick 6, as configured in
 * TTI_TICK_LEN_4_7.LEN6.In default configuration the tick length
 * corresponds to 1min.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_LEN_4_7 . LEN7
 */
#define  VTSS_F_AFI_TTI_TICK_LEN_4_7_LEN7(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_AFI_TTI_TICK_LEN_4_7_LEN7     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_AFI_TTI_TICK_LEN_4_7_LEN7(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Current state of TTI Tick counters
 *
 * \details
 * The TTI Tick counters are permanently running.
 *
 * Their current state (CNT and ERA) can be inspected and written to
 * through these registers.
 *
 * Register: \a AFI:TTI_TICKS:TTI_TICK_STATE
 *
 * @param ri Replicator: x_GAZ_AFI_TTI_TICK_DEPTH (??), 0-7
 */
#define VTSS_AFI_TTI_TICK_STATE(ri)          VTSS_IOREG(VTSS_TO_AFI,0xc1b1 + (ri))

/**
 * \brief
 * Tick's current counter value.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_STATE . TICK_CNT
 */
#define  VTSS_F_AFI_TTI_TICK_STATE_TICK_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_TTI_TICK_STATE_TICK_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_TTI_TICK_STATE_TICK_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Tick's current era.Each tick counts up to its configured LEN. When LEN
 * is reached TICK_ERA toggles and the tick restarts counting from 0.When a
 * TTI in TTI_TBL is processed, then the LAST_TICK_ERA of the TTI is
 * compared with the TICK_ERA of the tick used by the TTI and if they
 * differ the TTI's TICK_CNT is decremented.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_TICK_STATE . TICK_ERA
 */
#define  VTSS_F_AFI_TTI_TICK_STATE_TICK_ERA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AFI_TTI_TICK_STATE_TICK_ERA   VTSS_BIT(16)
#define  VTSS_X_AFI_TTI_TICK_STATE_TICK_ERA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * Register Group: \a AFI:TTI_MISC
 *
 * Miscellaneous TTI configration
 */


/**
 * \brief Start and end Frame Table pointers for Calendar Slot
 *
 * \details
 * Register: \a AFI:TTI_MISC:TTI_CAL_SLOT_PTRS
 *
 * @param ri Replicator: x_GAZ_AFI_TTI_CAL_DEPTH (??), 0-3
 */
#define VTSS_AFI_TTI_CAL_SLOT_PTRS(ri)       VTSS_IOREG(VTSS_TO_AFI,0xc1b9 + (ri))

/**
 * \brief
 * Calendar Slot's Frame Table start pointer.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CAL_SLOT_PTRS . SLOT_START_PTR
 */
#define  VTSS_F_AFI_TTI_CAL_SLOT_PTRS_SLOT_START_PTR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_AFI_TTI_CAL_SLOT_PTRS_SLOT_START_PTR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_AFI_TTI_CAL_SLOT_PTRS_SLOT_START_PTR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Calendar Slot's Frame Table end pointer.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CAL_SLOT_PTRS . SLOT_END_PTR
 */
#define  VTSS_F_AFI_TTI_CAL_SLOT_PTRS_SLOT_END_PTR(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_AFI_TTI_CAL_SLOT_PTRS_SLOT_END_PTR     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_AFI_TTI_CAL_SLOT_PTRS_SLOT_END_PTR(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/**
 * \brief Number of TTIs to service in slot before moving to next TTI Calendar slot.
 *
 * \details
 * Register: \a AFI:TTI_MISC:TTI_CAL_SLOT_CNT
 *
 * @param ri Replicator: x_GAZ_AFI_TTI_CAL_DEPTH (??), 0-3
 */
#define VTSS_AFI_TTI_CAL_SLOT_CNT(ri)        VTSS_IOREG(VTSS_TO_AFI,0xc1bd + (ri))

/**
 * \brief
 * Number of TTIs to service in slot before moving to next TTI Calendar
 * Slot.
 *
 * \details
 * 0: 1
 * 1: 1
 * 2: 2
 * ...
 *
 * Field: ::VTSS_AFI_TTI_CAL_SLOT_CNT . SLOT_CNT
 */
#define  VTSS_F_AFI_TTI_CAL_SLOT_CNT_SLOT_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_TTI_CAL_SLOT_CNT_SLOT_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_TTI_CAL_SLOT_CNT_SLOT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TTI Calendar state information
 *
 * \details
 * Register: \a AFI:TTI_MISC:TTI_CAL_STATE
 *
 * @param ri Replicator: x_GAZ_AFI_TTI_CAL_DEPTH (??), 0-3
 */
#define VTSS_AFI_TTI_CAL_STATE(ri)           VTSS_IOREG(VTSS_TO_AFI,0xc1c1 + (ri))

/**
 * \brief
 * Maximum number of clock cycles it has taken to service all TTIs covered
 * from SLOT_START_PTR to SLOT_END_PTR.The counter saturates at
 * all-ones.This may be useful for debugging problems caused by TTIs
 * serviced with too big interval, such that an era is being
 * missed.SLOT_TIME_MAX only increments when TTI_ENA=1.Related
 * parameters:AFI:TTI_MISC:TTI_CTRL.TTI_ENA
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CAL_STATE . SLOT_TIME_MAX
 */
#define  VTSS_F_AFI_TTI_CAL_STATE_SLOT_TIME_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_AFI_TTI_CAL_STATE_SLOT_TIME_MAX     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_AFI_TTI_CAL_STATE_SLOT_TIME_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Current value of Calendar Slot's TTI Table Pointer.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CAL_STATE . SLOT_TTI_TBL_PTR
 */
#define  VTSS_F_AFI_TTI_CAL_STATE_SLOT_TTI_TBL_PTR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_AFI_TTI_CAL_STATE_SLOT_TTI_TBL_PTR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_AFI_TTI_CAL_STATE_SLOT_TTI_TBL_PTR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief TTI Control
 *
 * \details
 * Register: \a AFI:TTI_MISC:TTI_CTRL
 */
#define VTSS_AFI_TTI_CTRL                    VTSS_IOREG(VTSS_TO_AFI,0xc1c5)

/**
 * \brief
 * Enable TTIs.Before enabling TTIs, TTI_INIT should be used to initialize
 * Calendar state.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CTRL . TTI_ENA
 */
#define  VTSS_F_AFI_TTI_CTRL_TTI_ENA(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_TTI_CTRL_TTI_ENA          VTSS_BIT(0)
#define  VTSS_X_AFI_TTI_CTRL_TTI_ENA(x)       VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * When set, initialize Calendar to start at Calendar Slot 0.Cleared by AFI
 * when done.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CTRL . TTI_INIT
 */
#define  VTSS_F_AFI_TTI_CTRL_TTI_INIT(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AFI_TTI_CTRL_TTI_INIT         VTSS_BIT(1)
#define  VTSS_X_AFI_TTI_CTRL_TTI_INIT(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If set only one TTI is processed at-a-time.This imposes some TTI
 * limitations and is only intended to be used as work around for
 * unexpected RTL bugs.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CTRL . TTI_SERIAL_ENA
 */
#define  VTSS_F_AFI_TTI_CTRL_TTI_SERIAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_AFI_TTI_CTRL_TTI_SERIAL_ENA   VTSS_BIT(2)
#define  VTSS_X_AFI_TTI_CTRL_TTI_SERIAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Length of TTI Calendar.
 *
 * \details
 * 0: Length=1 (Slot 0)
 * 1: Length=2 (Slot 0-1)
 * 2: Length=3 (Slot 0-2)
 * 3: Length=4 (Slot 0-3)
 *
 * Field: ::VTSS_AFI_TTI_CTRL . TTI_CAL_LEN
 */
#define  VTSS_F_AFI_TTI_CTRL_TTI_CAL_LEN(x)   VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_AFI_TTI_CTRL_TTI_CAL_LEN      VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_AFI_TTI_CTRL_TTI_CAL_LEN(x)   VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Maximum number of clock cycles that CSR accesses have to wait before
 * gaining access to TTI table.Note that writes need two accesses and may
 * thus have to await 2x the configured number of clock cycles.Setting this
 * parameter too low while doing excessive TTI Table CSR accesses may cause
 * TTIs (in TTI Table) to be serviced too infrequently for their configured
 * timer values.
 *
 * \details
 * 0 => CSR accesses takes precedence.
 * 1 => 1 clock cycle
 * ...

 *
 * Field: ::VTSS_AFI_TTI_CTRL . TTI_CSR_RSV
 */
#define  VTSS_F_AFI_TTI_CTRL_TTI_CSR_RSV(x)   VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_AFI_TTI_CTRL_TTI_CSR_RSV      VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_AFI_TTI_CTRL_TTI_CSR_RSV(x)   VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Current TTI Calendar slot.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CTRL . TTI_CAL_PTR
 */
#define  VTSS_F_AFI_TTI_CTRL_TTI_CAL_PTR(x)   VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_AFI_TTI_CTRL_TTI_CAL_PTR      VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_AFI_TTI_CTRL_TTI_CAL_PTR(x)   VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Number of remaining TTI Table entries to service for current Calendar
 * Slot.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CTRL . TTI_CAL_CNT
 */
#define  VTSS_F_AFI_TTI_CTRL_TTI_CAL_CNT(x)   VTSS_ENCODE_BITFIELD(x,20,8)
#define  VTSS_M_AFI_TTI_CTRL_TTI_CAL_CNT      VTSS_ENCODE_BITMASK(20,8)
#define  VTSS_X_AFI_TTI_CTRL_TTI_CAL_CNT(x)   VTSS_EXTRACT_BITFIELD(x,20,8)


/**
 * \brief TTI Control
 *
 * \details
 * Register: \a AFI:TTI_MISC:TTI_CTRL2
 */
#define VTSS_AFI_TTI_CTRL2                   VTSS_IOREG(VTSS_TO_AFI,0xc1c6)

/**
 * \brief
 * Minium number of clock cycles between TUPE accessing TTI Table.TUPE
 * access to TTI Table takes precedence over both CSR accesses and normal
 * TTI processing.TUPE will at least consume 4 clock cycles per processed
 * TTI, so setting TTI_TUPE_RSV<4 results in same behavior as setting it to
 * 4.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_CTRL2 . TTI_TUPE_RSV
 */
#define  VTSS_F_AFI_TTI_CTRL2_TTI_TUPE_RSV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_TTI_CTRL2_TTI_TUPE_RSV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_TTI_CTRL2_TTI_TUPE_RSV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TTI Injection Counter
 *
 * \details
 * Register: \a AFI:TTI_MISC:TTI_INJ_CNT
 */
#define VTSS_AFI_TTI_INJ_CNT                 VTSS_IOREG(VTSS_TO_AFI,0xc1c7)

/**
 * \brief
 * Number of TTI frame injections.Enabled per TTI using
 * AFI:TTI_TBL:TTI_MISC_CFG.INJ_CNT_ENA.Frames injected for removal are
 * also counted.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_INJ_CNT . TTI_INJ_CNT
 */
#define  VTSS_F_AFI_TTI_INJ_CNT_TTI_INJ_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_AFI_TTI_INJ_CNT_TTI_INJ_CNT     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_AFI_TTI_INJ_CNT_TTI_INJ_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief State of random algorithm used for TTI jitter calculation
 *
 * \details
 * Register: \a AFI:TTI_MISC:TTI_RAND_STATE
 */
#define VTSS_AFI_TTI_RAND_STATE              VTSS_IOREG(VTSS_TO_AFI,0xc1c8)

/**
 * \brief
 * State of random algorithm used for TTI jitter calculation.Updated by AFI
 * for each jitter calculation.Should be initialized by SW to a random,
 * non-zero value.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_RAND_STATE . TTI_RAND_STATE
 */
#define  VTSS_F_AFI_TTI_RAND_STATE_TTI_RAND_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_AFI_TTI_RAND_STATE_TTI_RAND_STATE     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_AFI_TTI_RAND_STATE_TTI_RAND_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/**
 * \brief Outstanding TTI injections per port
 *
 * \details
 * Register: \a AFI:TTI_MISC:TTI_PORT_FRM_OUT
 */
#define VTSS_AFI_TTI_PORT_FRM_OUT            VTSS_IOREG(VTSS_TO_AFI,0xc1c9)

/**
 * \brief
 * See AFI:PORT_TBL:PORT_CFG.FRM_OUT_MAX.
 *
 * \details
 * Field: ::VTSS_AFI_TTI_PORT_FRM_OUT . TTI_FRM_OUT_MAX
 */
#define  VTSS_F_AFI_TTI_PORT_FRM_OUT_TTI_FRM_OUT_MAX(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_AFI_TTI_PORT_FRM_OUT_TTI_FRM_OUT_MAX     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_AFI_TTI_PORT_FRM_OUT_TTI_FRM_OUT_MAX(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a AFI:PORT_TBL
 *
 * Port parameter configuration
 */


/**
 * \brief Number of outstanding injections per port
 *
 * \details
 * Register: \a AFI:PORT_TBL:PORT_FRM_OUT
 *
 * @param gi Replicator: x_GAZ_AFI_PORT_CNT (??), 0-34
 */
#define VTSS_AFI_PORT_FRM_OUT(gi)            VTSS_IOREG_IX(VTSS_TO_AFI,0xc100,gi,2,0,0)

/**
 * \brief
 * Current number of injections (TTI or DTI) outstanding per port. This
 * parameter should not be written to.If the parameter is written to and a
 * TTI injection occurs concurrently, then the written value may get
 * overwritten by the AFI block.Note that "removal injections" (for
 * removing frames from buffer memory) are not included in the number of
 * outstanding injections per port.
 *
 * \details
 * Field: ::VTSS_AFI_PORT_FRM_OUT . FRM_OUT_CNT
 */
#define  VTSS_F_AFI_PORT_FRM_OUT_FRM_OUT_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_AFI_PORT_FRM_OUT_FRM_OUT_CNT     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_AFI_PORT_FRM_OUT_FRM_OUT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,11)


/**
 * \brief Port configuration parameters
 *
 * \details
 * Register: \a AFI:PORT_TBL:PORT_CFG
 *
 * @param gi Replicator: x_GAZ_AFI_PORT_CNT (??), 0-34
 */
#define VTSS_AFI_PORT_CFG(gi)                VTSS_IOREG_IX(VTSS_TO_AFI,0xc100,gi,2,0,1)

/**
 * \brief
 * Maximum number of injections that can be outstanding at a time per
 * port.DTI injections are held back if FRM_OUT_MAX is exceeded.TTI
 * injections are held back if FRM_OUT_MAX+TTI_FRM_OUT_MAX is
 * exceeded.TTI_FRM_OUT_MAX ensures that TTI injections are still possible
 * when a DTI flow is configured slightly above port speed.If FRM_OUT_MAX
 * is set to 0 to disable injections for port, then it is recommended to
 * first set FC_SKIP_TTI_INJ=1 to avoid a burst of injections when
 * injections are later enabled.Upon setting FRM_OUT_MAX back to non-zero
 * value, then FC_SKIP_TTI_INJ must be set back to its original value.Note
 * that "removal injections" (for removing frames from buffer memory) are
 * not included in the number of outstanding injections per port and are
 * therefore also allowed when FRM_OUT_MAX=0.
 *
 * \details
 * 0: Injection disabled for port (both TTI and DTI injections, regardless
 * of TTI_FRM_OUT_MAX value)
 * 1: Maximum 1 outstanding injection.
 * 2: Maximum 2 outstanding injections.
 * ...
 * 1022: Maximum 1022 outstanding injections.
 * 1023: Illegal.
 *
 * Field: ::VTSS_AFI_PORT_CFG . FRM_OUT_MAX
 */
#define  VTSS_F_AFI_PORT_CFG_FRM_OUT_MAX(x)   VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_AFI_PORT_CFG_FRM_OUT_MAX      VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_AFI_PORT_CFG_FRM_OUT_MAX(x)   VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Controls what action to take if TTI injection cannot be performed due to
 * FRM_OUT_MAX reached or injection stop from QSYS. FC_SKIP_TTI_INJ should
 * be set when disabling a port using FRM_OUT_MAX. See
 * PORT_CFG.FRM_OUT_MAX.
 *
 * \details
 * 0: Postpone injection until injection is again allowed.
 * 1: Skip this injection.
 *
 * Field: ::VTSS_AFI_PORT_CFG . FC_SKIP_TTI_INJ
 */
#define  VTSS_F_AFI_PORT_CFG_FC_SKIP_TTI_INJ(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AFI_PORT_CFG_FC_SKIP_TTI_INJ  VTSS_BIT(16)
#define  VTSS_X_AFI_PORT_CFG_FC_SKIP_TTI_INJ(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * Register Group: \a AFI:TUPE
 *
 * AFI Table UPdata Engine (AFI TUPE)
 */


/**
 * \brief Miscellaneous TUPE parameters
 *
 * \details
 * Register: \a AFI:TUPE:TUPE_MISC
 */
#define VTSS_AFI_TUPE_MISC                   VTSS_IOREG(VTSS_TO_AFI,0xc1ca)

/**
 * \brief
 * Start TUPE.Write 1 to start TUPE.Set to 0 by TUPE when done.Before
 * running TUPE, AFI::MISC_CTRL.AFI_ENA must be set to 1.Note:While TUPE is
 * running (i.e. TUPE_START=1) CPU must not write to TTI Table.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_MISC . TUPE_START
 */
#define  VTSS_F_AFI_TUPE_MISC_TUPE_START(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AFI_TUPE_MISC_TUPE_START      VTSS_BIT(0)
#define  VTSS_X_AFI_TUPE_MISC_TUPE_START(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enable use of CRIT_PORT_NUM_VAL.For further information refer
 * toAFI:TUPE:TUPE_CRIT1.CRIT_PORT_NUM_VAL
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_MISC . CRIT_PORT_NUM_ENA
 */
#define  VTSS_F_AFI_TUPE_MISC_CRIT_PORT_NUM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AFI_TUPE_MISC_CRIT_PORT_NUM_ENA  VTSS_BIT(1)
#define  VTSS_X_AFI_TUPE_MISC_CRIT_PORT_NUM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable use of CRIT_QU_NUM_ENA.For further information refer
 * toAFI:TUPE:TUPE_CRIT1.CRIT_QU_NUM_VAL
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_MISC . CRIT_QU_NUM_ENA
 */
#define  VTSS_F_AFI_TUPE_MISC_CRIT_QU_NUM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_AFI_TUPE_MISC_CRIT_QU_NUM_ENA  VTSS_BIT(2)
#define  VTSS_X_AFI_TUPE_MISC_CRIT_QU_NUM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable use of CMD_TIMER_ENA_VAL.For further information refer
 * toAFI:TUPE:TUPE_MISC.CMD_TIMER_ENA_VAL
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_MISC . CMD_TIMER_ENA_ENA
 */
#define  VTSS_F_AFI_TUPE_MISC_CMD_TIMER_ENA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_AFI_TUPE_MISC_CMD_TIMER_ENA_ENA  VTSS_BIT(4)
#define  VTSS_X_AFI_TUPE_MISC_CMD_TIMER_ENA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * New value for TIMER_ENA for any TTIs matching TUPE criteria.Must be
 * enabled by AFI:TUPE:TUPE_MISC.CMD_TIMER_ENA_ENA.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_MISC . CMD_TIMER_ENA_VAL
 */
#define  VTSS_F_AFI_TUPE_MISC_CMD_TIMER_ENA_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_AFI_TUPE_MISC_CMD_TIMER_ENA_VAL  VTSS_BIT(5)
#define  VTSS_X_AFI_TUPE_MISC_CMD_TIMER_ENA_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable use of CMD_PORT_NUM_VAL.For further information refer
 * toAFI:TUPE:TUPE_CMD1.CMD_PORT_NUM_VAL
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_MISC . CMD_PORT_NUM_ENA
 */
#define  VTSS_F_AFI_TUPE_MISC_CMD_PORT_NUM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_AFI_TUPE_MISC_CMD_PORT_NUM_ENA  VTSS_BIT(6)
#define  VTSS_X_AFI_TUPE_MISC_CMD_PORT_NUM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable use of CMD_QU_NUM_VAL.For further information refer
 * toAFI:TUPE:TUPE_CMD1.CMD_QU_NUM_VAL
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_MISC . CMD_QU_NUM_ENA
 */
#define  VTSS_F_AFI_TUPE_MISC_CMD_QU_NUM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_AFI_TUPE_MISC_CMD_QU_NUM_ENA  VTSS_BIT(7)
#define  VTSS_X_AFI_TUPE_MISC_CMD_QU_NUM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief Address range for TUPE to process
 *
 * \details
 * Register: \a AFI:TUPE:TUPE_ADDR
 */
#define VTSS_AFI_TUPE_ADDR                   VTSS_IOREG(VTSS_TO_AFI,0xc1cb)

/**
 * \brief
 * First address in TTI Table for TUPE to process.Must be <=
 * TUPE_START_ADDR.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_ADDR . TUPE_START_ADDR
 */
#define  VTSS_F_AFI_TUPE_ADDR_TUPE_START_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_AFI_TUPE_ADDR_TUPE_START_ADDR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_AFI_TUPE_ADDR_TUPE_START_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Last address in TTI Table for TUPE to process.Must be >=
 * TUPE_START_ADDR.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_ADDR . TUPE_END_ADDR
 */
#define  VTSS_F_AFI_TUPE_ADDR_TUPE_END_ADDR(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_AFI_TUPE_ADDR_TUPE_END_ADDR     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_AFI_TUPE_ADDR_TUPE_END_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/**
 * \brief TUPE Criteria
 *
 * \details
 * Register: \a AFI:TUPE:TUPE_CRIT1
 */
#define VTSS_AFI_TUPE_CRIT1                  VTSS_IOREG(VTSS_TO_AFI,0xc1cc)

/**
 * \brief
 * If enabled by AFI:TUPE:TUPE_MISC.CRIT_PORT_NUM_ENA, then PORT_NUM in
 * TTIs must match this value in order to be processed by TUPE.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_CRIT1 . CRIT_PORT_NUM_VAL
 */
#define  VTSS_F_AFI_TUPE_CRIT1_CRIT_PORT_NUM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_AFI_TUPE_CRIT1_CRIT_PORT_NUM_VAL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_AFI_TUPE_CRIT1_CRIT_PORT_NUM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * If enabled by AFI:TUPE:TUPE_MISC.CRIT_QU_NUM_ENA, then QU_NUM in TTIs
 * must match this value in order to be processed by TUPE.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_CRIT1 . CRIT_QU_NUM_VAL
 */
#define  VTSS_F_AFI_TUPE_CRIT1_CRIT_QU_NUM_VAL(x)  VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_AFI_TUPE_CRIT1_CRIT_QU_NUM_VAL     VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_AFI_TUPE_CRIT1_CRIT_QU_NUM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,14)


/**
 * \brief TUPE Criteria
 *
 * \details
 * Register: \a AFI:TUPE:TUPE_CRIT2
 */
#define VTSS_AFI_TUPE_CRIT2                  VTSS_IOREG(VTSS_TO_AFI,0xc1cd)

/**
 * \brief
 * Refer to AFI:TUPE:TUPE_CRIT3.CRIT_TUPE_CTRL_VAL.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_CRIT2 . CRIT_TUPE_CTRL_MASK
 */
#define  VTSS_F_AFI_TUPE_CRIT2_CRIT_TUPE_CTRL_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_TUPE_CRIT2_CRIT_TUPE_CTRL_MASK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_TUPE_CRIT2_CRIT_TUPE_CTRL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TUPE Criteria
 *
 * \details
 * Register: \a AFI:TUPE:TUPE_CRIT3
 *
 * @param ri Replicator: x_GAZ_AFI_TTI_TUPE_CTRL_CRIT_CNT (??), 0-1
 */
#define VTSS_AFI_TUPE_CRIT3(ri)              VTSS_IOREG(VTSS_TO_AFI,0xc1ce + (ri))

/**
 * \brief
 * For one or more of the configured CRIT_TUPE_CTRL_VALs, TUPE_CTRL in TTIs
 * must match the following criteria in order to be processed by
 * TUPE:(TTI.TUPE_CTRL & CRIT_TUPE_CTRL_MASK) == CRIT_TUPE_CTRL_VAL[i]
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_CRIT3 . CRIT_TUPE_CTRL_VAL
 */
#define  VTSS_F_AFI_TUPE_CRIT3_CRIT_TUPE_CTRL_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_AFI_TUPE_CRIT3_CRIT_TUPE_CTRL_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_AFI_TUPE_CRIT3_CRIT_TUPE_CTRL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief TUPE Command Parameters
 *
 * \details
 * Register: \a AFI:TUPE:TUPE_CMD1
 */
#define VTSS_AFI_TUPE_CMD1                   VTSS_IOREG(VTSS_TO_AFI,0xc1d0)

/**
 * \brief
 * New value for PORT_NUM for any TTIs matching TUPE criteria.Must be
 * enabled by AFI:TUPE:TUPE_MISC.CMD_PORT_NUM_ENA.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_CMD1 . CMD_PORT_NUM_VAL
 */
#define  VTSS_F_AFI_TUPE_CMD1_CMD_PORT_NUM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_AFI_TUPE_CMD1_CMD_PORT_NUM_VAL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_AFI_TUPE_CMD1_CMD_PORT_NUM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * New value for QU_NUM for any TTIs matching TUPE criteria.Must be enabled
 * by AFI:TUPE:TUPE_MISC.CMD_QU_NUM_ENA.
 *
 * \details
 * Field: ::VTSS_AFI_TUPE_CMD1 . CMD_QU_NUM_VAL
 */
#define  VTSS_F_AFI_TUPE_CMD1_CMD_QU_NUM_VAL(x)  VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_AFI_TUPE_CMD1_CMD_QU_NUM_VAL     VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_AFI_TUPE_CMD1_CMD_QU_NUM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,14)


#endif /* _VTSS_LAGUNA_REGS_AFI_H_ */
