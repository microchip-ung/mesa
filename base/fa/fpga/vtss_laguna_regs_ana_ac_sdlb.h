// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_ANA_AC_SDLB_H_
#define _VTSS_LAGUNA_REGS_ANA_AC_SDLB_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a ANA_AC_SDLB
 *
 * Service policers supporting
 * - MEF 10.2.
 * - MEF 10.3, including envelope support with CIRmax and EIRmax.
 * - RFC 2697 "Single Rate Three Color Marker".
 * - RFC 2698 "Two Rate Three Color Marker".
 *
 ***********************************************************************/

/**
 * Register Group: \a ANA_AC_SDLB:MISC
 *
 * Miscellaneous parameters
 */


/**
 * \brief XLB pointer translation control
 *
 * \details
 * Register: \a ANA_AC_SDLB:MISC:XLB_NEXT_TR_CTRL
 */
#define VTSS_ANA_AC_SDLB_XLB_NEXT_TR_CTRL    VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f00)

/**
 * \brief
 * Enable XLB pointer translation.Use during removal of XLB from LB Group.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_XLB_NEXT_TR_CTRL . XLB_NEXT_TR_ENA
 */
#define  VTSS_F_ANA_AC_SDLB_XLB_NEXT_TR_CTRL_XLB_NEXT_TR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_SDLB_XLB_NEXT_TR_CTRL_XLB_NEXT_TR_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_SDLB_XLB_NEXT_TR_CTRL_XLB_NEXT_TR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Original XLB pointer value
 *
 * \details
 * Use during removal of XLB from LB Group.
 *
 * Register: \a ANA_AC_SDLB:MISC:XLB_NEXT_TR_ORG
 */
#define VTSS_ANA_AC_SDLB_XLB_NEXT_TR_ORG     VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f01)

/**
 * \brief
 * Original LB Set address for LB pointer translation.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_XLB_NEXT_TR_ORG . LBSET_NEXT_TR_ORG
 */
#define  VTSS_F_ANA_AC_SDLB_XLB_NEXT_TR_ORG_LBSET_NEXT_TR_ORG(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_SDLB_XLB_NEXT_TR_ORG_LBSET_NEXT_TR_ORG     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_SDLB_XLB_NEXT_TR_ORG_LBSET_NEXT_TR_ORG(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief New XLB pointer value
 *
 * \details
 * Use during removal of XLB from LB Group.
 *
 * Register: \a ANA_AC_SDLB:MISC:XLB_NEXT_TR_NEW
 */
#define VTSS_ANA_AC_SDLB_XLB_NEXT_TR_NEW     VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f02)

/**
 * \brief
 * New LB Set address for LB pointer translation.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_XLB_NEXT_TR_NEW . LBSET_NEXT_TR_NEW
 */
#define  VTSS_F_ANA_AC_SDLB_XLB_NEXT_TR_NEW_LBSET_NEXT_TR_NEW(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_SDLB_XLB_NEXT_TR_NEW_LBSET_NEXT_TR_NEW     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_SDLB_XLB_NEXT_TR_NEW_LBSET_NEXT_TR_NEW(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Translate to end of list.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_XLB_NEXT_TR_NEW . XLB_NEXT_TR_END
 */
#define  VTSS_F_ANA_AC_SDLB_XLB_NEXT_TR_NEW_XLB_NEXT_TR_END(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ANA_AC_SDLB_XLB_NEXT_TR_NEW_XLB_NEXT_TR_END  VTSS_BIT(24)
#define  VTSS_X_ANA_AC_SDLB_XLB_NEXT_TR_NEW_XLB_NEXT_TR_END(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief Miscellaneous control parameters.
 *
 * \details
 * Register: \a ANA_AC_SDLB:MISC:MISC_CTRL
 */
#define VTSS_ANA_AC_SDLB_MISC_CTRL           VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f03)

/**
 * \brief
 * Allow new PUPs to start even through inh_tokens_fifo has reached
 * watermark.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_MISC_CTRL . PUP_IGNORE_INH_TOKENS_FIFO_WMARK
 */
#define  VTSS_F_ANA_AC_SDLB_MISC_CTRL_PUP_IGNORE_INH_TOKENS_FIFO_WMARK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_SDLB_MISC_CTRL_PUP_IGNORE_INH_TOKENS_FIFO_WMARK  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_SDLB_MISC_CTRL_PUP_IGNORE_INH_TOKENS_FIFO_WMARK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief Miscellaneous rate control parameters.
 *
 * \details
 * Register: \a ANA_AC_SDLB:MISC:MISC_RATE_CTRL
 */
#define VTSS_ANA_AC_SDLB_MISC_RATE_CTRL      VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f04)

/**
 * \brief
 * Enable frame rate mode.FRM_RATE_ENA must be set if FRM_RATE_ENA is set
 * for any XLB.FRM_RATE_ENA must be cleared if FRM_RATE_ENA is not set for
 * any XLB.Related
 * parameters:ANA_AC_SDLB:LBGRP_TBL:FRM_RATE_TOKENS.FRM_RATE_TOKENS
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_MISC_RATE_CTRL . FRM_RATE_ENA
 */
#define  VTSS_F_ANA_AC_SDLB_MISC_RATE_CTRL_FRM_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_SDLB_MISC_RATE_CTRL_FRM_RATE_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_SDLB_MISC_RATE_CTRL_FRM_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Register for signaling LB having entered MARK_ALL_FRMS_RED=1 state
 *
 * \details
 * Register: \a ANA_AC_SDLB:MISC:MARK_ALL_FRMS_RED_SET
 */
#define VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET  VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f05)

/**
 * \brief
 * LB Set address of DLB having entered MARK_ALL_FRMS_RED=1 state.Only
 * valid when MARK_ALL_FRMS_RED_SET_VLD=1.Related
 * parameters:ANA_AC_SDLB:MISC:MARK_ALL_FRMS_RED_SET.MARK_ALL_FRMS_RED_SET_
 * VLD
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET . MARK_ALL_FRMS_RED_SET_LBSET
 */
#define  VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_LBSET(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_LBSET     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_LBSET(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Set by HW when a new DLB has entered MARK_ALL_FRMS_RED=1 state.Must be
 * cleared by SW when the information has been received.To get notified of
 * any DLBs having entered MARK_ALL_FRMS_RED=1 state, SW must reguarly poll
 * this bit.Related
 * parameters:ANA_AC_SDLB:MISC:MARK_ALL_FRMS_RED_SET.MARK_ALL_FRMS_RED_SET_
 * LBSET
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET . MARK_ALL_FRMS_RED_SET_VLD
 */
#define  VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_VLD  VTSS_BIT(24)
#define  VTSS_X_ANA_AC_SDLB_MARK_ALL_FRMS_RED_SET_MARK_ALL_FRMS_RED_SET_VLD(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief Register for clearing MARK_ALL_FRMS_RED=1 state for a DLB.
 *
 * \details
 * Register: \a ANA_AC_SDLB:MISC:MARK_ALL_FRMS_RED_CLR
 */
#define VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR  VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f06)

/**
 * \brief
 * LB Set to be processed when MARK_ALL_FRMS_RED_CLR=1.Related
 * parameters:ANA_AC_SDLB:MISC:MARK_ALL_FRMS_RED_CLR.MARK_ALL_FRMS_RED_CLR_
 * VLD
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR . MARK_ALL_FRMS_RED_CLR_LBSET
 */
#define  VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR_MARK_ALL_FRMS_RED_CLR_LBSET(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR_MARK_ALL_FRMS_RED_CLR_LBSET     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR_MARK_ALL_FRMS_RED_CLR_LBSET(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Set this bit to clear MARK_ALL_FRMS_RED in the state table for the LB
 * Set specified in MARK_ALL_FRMS_RED_CLR_LBSET.This bit is cleared when
 * the operation has been completed.Related
 * parameters:ANA_AC_SDLB:MISC:MARK_ALL_FRMS_RED_CLR.MARK_ALL_FRMS_RED_CLR_
 * LBSETANA_AC_SDLB:LBSET_TBL:DLB_MISC.MARK_ALL_FRMS_RED_ENA
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR . MARK_ALL_FRMS_RED_CLR_VLD
 */
#define  VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR_MARK_ALL_FRMS_RED_CLR_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR_MARK_ALL_FRMS_RED_CLR_VLD  VTSS_BIT(24)
#define  VTSS_X_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR_MARK_ALL_FRMS_RED_CLR_VLD(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief Warning sticky bits.
 *
 * \details
 * These bits shall normally not get set.
 *
 * Register: \a ANA_AC_SDLB:MISC:WARN
 */
#define VTSS_ANA_AC_SDLB_WARN                VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f07)

/**
 * \brief
 * sub_fifo has reached its watermark.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_WARN . SUB_FIFO_WMARK_REACHED_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_WARN_SUB_FIFO_WMARK_REACHED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_SDLB_WARN_SUB_FIFO_WMARK_REACHED_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_SDLB_WARN_SUB_FIFO_WMARK_REACHED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * A translation match was found.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_WARN . NEXT_TR_MATCH_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_WARN_NEXT_TR_MATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_SDLB_WARN_NEXT_TR_MATCH_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_SDLB_WARN_NEXT_TR_MATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Watermark has been reached in inh_tokens_fifo.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_WARN . INH_TOKENS_FIFO_WMARK_REACHED_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_WARN_INH_TOKENS_FIFO_WMARK_REACHED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_SDLB_WARN_INH_TOKENS_FIFO_WMARK_REACHED_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_SDLB_WARN_INH_TOKENS_FIFO_WMARK_REACHED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * inh_tokens_fifo has overflown.This must not happen unless
 * PUP_IGNORE_INH_TOKENS_FIFO_WMARK=1.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_WARN . INH_TOKENS_FIFO_OFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_WARN_INH_TOKENS_FIFO_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_AC_SDLB_WARN_INH_TOKENS_FIFO_OFLW_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_AC_SDLB_WARN_INH_TOKENS_FIFO_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * PUPs within 2 clock cycles after one-another wanted to update the same
 * LB Set address. The second PUP was thus held back.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_WARN . PUP_TO_PUP_LBSET_COLLISION_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_WARN_PUP_TO_PUP_LBSET_COLLISION_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_AC_SDLB_WARN_PUP_TO_PUP_LBSET_COLLISION_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_AC_SDLB_WARN_PUP_TO_PUP_LBSET_COLLISION_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * PUP followed by a SUB within 2 clock cycles wanted to update the same LB
 * Set address. The SUB was thus held back.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_WARN . PUP_TO_SUB_LBSET_COLLISION_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_WARN_PUP_TO_SUB_LBSET_COLLISION_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_AC_SDLB_WARN_PUP_TO_SUB_LBSET_COLLISION_STICKY  VTSS_BIT(5)
#define  VTSS_X_ANA_AC_SDLB_WARN_PUP_TO_SUB_LBSET_COLLISION_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * SUB and PUP was available within the same clock cycle and wanted to
 * update the same LB set address. SUB was selected first
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_WARN . SUB_SELECTED_BEFORE_PUP_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_WARN_SUB_SELECTED_BEFORE_PUP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_AC_SDLB_WARN_SUB_SELECTED_BEFORE_PUP_STICKY  VTSS_BIT(6)
#define  VTSS_X_ANA_AC_SDLB_WARN_SUB_SELECTED_BEFORE_PUP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief Failure sticky bits.
 *
 * \details
 * These bits are never expected to get set.
 *
 * Register: \a ANA_AC_SDLB:MISC:FAIL
 */
#define VTSS_ANA_AC_SDLB_FAIL                VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f08)

/**
 * \brief
 * sub_fifo has overflowed.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . SUB_FIFO_OFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_SUB_FIFO_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_SUB_FIFO_OFLW_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_SDLB_FAIL_SUB_FIFO_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * sub_fifo has underflowed
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . SUB_FIFO_UFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_SUB_FIFO_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_SUB_FIFO_UFLW_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_SDLB_FAIL_SUB_FIFO_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * sub_info_fifo has overflowed.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . SUB_INFO_FIFO_OFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_SUB_INFO_FIFO_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_SUB_INFO_FIFO_OFLW_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_SDLB_FAIL_SUB_INFO_FIFO_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * sub_info_fifo has underflowed
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . SUB_INFO_FIFO_UFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_SUB_INFO_FIFO_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_SUB_INFO_FIFO_UFLW_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_AC_SDLB_FAIL_SUB_INFO_FIFO_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * The queue of pending PUPs has overflowed.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . PND_PUP_QU_OFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_PND_PUP_QU_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_PND_PUP_QU_OFLW_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_AC_SDLB_FAIL_PND_PUP_QU_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * The queue of pending PUPs underflowed
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . PND_PUP_QU_UFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_PND_PUP_QU_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_PND_PUP_QU_UFLW_STICKY  VTSS_BIT(5)
#define  VTSS_X_ANA_AC_SDLB_FAIL_PND_PUP_QU_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * The queue of precalculated PUPs has overflowed.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . PRE_PUP_QU_OFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_PRE_PUP_QU_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_PRE_PUP_QU_OFLW_STICKY  VTSS_BIT(6)
#define  VTSS_X_ANA_AC_SDLB_FAIL_PRE_PUP_QU_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * The queue of precalculated PUPs underflowed
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . PRE_PUP_QU_UFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_PRE_PUP_QU_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_PRE_PUP_QU_UFLW_STICKY  VTSS_BIT(7)
#define  VTSS_X_ANA_AC_SDLB_FAIL_PRE_PUP_QU_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * inh_tokens_fifo has underflowed
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FAIL . INH_TOKENS_FIFO_UFLW_STICKY
 */
#define  VTSS_F_ANA_AC_SDLB_FAIL_INH_TOKENS_FIFO_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_SDLB_FAIL_INH_TOKENS_FIFO_UFLW_STICKY  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_SDLB_FAIL_INH_TOKENS_FIFO_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief Indirect access to state tables
 *
 * \details
 * Using this register it is possible to read and write the state tables
 *
 * Register: \a ANA_AC_SDLB:MISC:TBL_ACC_CTRL
 */
#define VTSS_ANA_AC_SDLB_TBL_ACC_CTRL        VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f09)

/**
 * \brief
 * Configure read or write command and select table to access.Related
 * parameters:ANA_AC_SDLB:MISC:TBL_ACC_VAL.TBL_ACC_VALNote:When the
 * MARK_ALL_FRMS_RED=1 state functionality is supported, the token state
 * table contains two extra state bits located at bit position 24 and
 * forward:bit all_red: The LB Set is in MARK_ALL_FRMS_RED=1 statebit
 * all_red_notify_done: SW has been notified about the state of this LB Set
 *
 * \details
 * 0: No operation
 * 1: Write tokens table (24 bits per bucket, two complements encoded)
 * 2: Read tokens table (24 bits per bucket, two complements encoded)
 * 3: Write closed table
 * 4: Read closed table
 * 5: Write inh tokens table (15 bits per bucket)
 * 6: Read inh tokens table (15 bits per bucket)

 *
 * Field: ::VTSS_ANA_AC_SDLB_TBL_ACC_CTRL . TBL_CMD
 */
#define  VTSS_F_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_CMD(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_CMD     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_CMD(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Execute the read or write command. This bit is cleared by the HW when
 * the command is done.  Read results will be present in the corresponding
 * value register.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_TBL_ACC_CTRL . TBL_CMD_EXEC
 */
#define  VTSS_F_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_CMD_EXEC(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_CMD_EXEC  VTSS_BIT(3)
#define  VTSS_X_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_CMD_EXEC(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Address of the LBSET to access
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_TBL_ACC_CTRL . TBL_LBSET_ADDR
 */
#define  VTSS_F_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_LBSET_ADDR(x)  VTSS_ENCODE_BITFIELD(x,5,9)
#define  VTSS_M_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_LBSET_ADDR     VTSS_ENCODE_BITMASK(5,9)
#define  VTSS_X_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_LBSET_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,5,9)

/**
 * \brief
 * LB within LBSET to access for all the access commands
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_TBL_ACC_CTRL . TBL_LB_IDX
 */
#define  VTSS_F_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_LB_IDX(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_LB_IDX  VTSS_BIT(4)
#define  VTSS_X_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_LB_IDX(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief Indirect access to tables
 *
 * \details
 * Using this register it is possible to read and write the state tables
 *
 * Register: \a ANA_AC_SDLB:MISC:TBL_ACC_VAL
 */
#define VTSS_ANA_AC_SDLB_TBL_ACC_VAL         VTSS_IOREG(VTSS_TO_ANA_AC_SDLB,0x1f0a)

/**
 * \brief
 * Contains data to be written to the selected state table or the result of
 * a state table read command.The value of
 * ANA_AC_SDLB:MISC:TBL_ACC_CTRL.TBL_CMD determines the encoding.Related
 * parameters:ANA_AC_SDLB:MISC:TBL_ACC_CTRL.TBL_CMDANA_AC_SDLB:MISC:TBL_ACC
 * _CTRL.TBL_LBSET_ADDRANA_AC_SDLB:MISC:TBL_ACC_CTRL.TBL_LB_IDX
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_TBL_ACC_VAL . TBL_ACC_VAL
 */
#define  VTSS_F_ANA_AC_SDLB_TBL_ACC_VAL_TBL_ACC_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_ANA_AC_SDLB_TBL_ACC_VAL_TBL_ACC_VAL     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_ANA_AC_SDLB_TBL_ACC_VAL_TBL_ACC_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,26)

/**
 * Register Group: \a ANA_AC_SDLB:LBGRP_TBL
 *
 * LB Group configuration table
 */


/**
 * \brief Pointer to first XLB in LB Group.
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBGRP_TBL:XLB_START
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBGRP_CNT (??), 0-4
 */
#define VTSS_ANA_AC_SDLB_XLB_START(gi)       VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x1f0b,gi,6,0,0)

/**
 * \brief
 * Address of LB Set containing first LB of LB Group.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_XLB_START . LBSET_START
 */
#define  VTSS_F_ANA_AC_SDLB_XLB_START_LBSET_START(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_SDLB_XLB_START_LBSET_START     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_SDLB_XLB_START_LBSET_START(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Number of clock cycles between each PUP for LBs in LB Group.
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBGRP_TBL:PUP_INTERVAL
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBGRP_CNT (??), 0-4
 */
#define VTSS_ANA_AC_SDLB_PUP_INTERVAL(gi)    VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x1f0b,gi,6,0,1)

/**
 * \brief
 * Number of clock cycles between each Periodic UPdate (PUP) for LBs in LB
 * Group. Together with PUP_TOKENS (configured per LB) this controls the
 * rate of the LB.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_PUP_INTERVAL . PUP_INTERVAL
 */
#define  VTSS_F_ANA_AC_SDLB_PUP_INTERVAL_PUP_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_ANA_AC_SDLB_PUP_INTERVAL_PUP_INTERVAL     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_ANA_AC_SDLB_PUP_INTERVAL_PUP_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/**
 * \brief Various PUP related parameters.
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBGRP_TBL:PUP_CTRL
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBGRP_CNT (??), 0-4
 */
#define VTSS_ANA_AC_SDLB_PUP_CTRL(gi)        VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x1f0b,gi,6,0,2)

/**
 * \brief
 * Delta time between updating LBs within an LB Set, i.e. PUP_LB_DT
 * specifies the number of clock cycles between each LB update within LB
 * Set. Can be used to avoid many LBs opening concurrently.Should be set to
 * PUP_INTERVAL/<number of LBs in LB Group>.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_PUP_CTRL . PUP_LB_DT
 */
#define  VTSS_F_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT(x)  VTSS_EXTRACT_BITFIELD(x,0,19)

/**
 * \brief
 * Enable Periodic UPdate (PUP).
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_PUP_CTRL . PUP_ENA
 */
#define  VTSS_F_ANA_AC_SDLB_PUP_CTRL_PUP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ANA_AC_SDLB_PUP_CTRL_PUP_ENA  VTSS_BIT(24)
#define  VTSS_X_ANA_AC_SDLB_PUP_CTRL_PUP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief Miscellaneous LB Group parameters
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBGRP_TBL:LBGRP_MISC
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBGRP_CNT (??), 0-4
 */
#define VTSS_ANA_AC_SDLB_LBGRP_MISC(gi)      VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x1f0b,gi,6,0,3)

/**
 * \brief
 * Number of positions to right-shift LB's threshold value.May be used for
 * supporting smaller threshold values, e.g. for AVB.Related
 * parameters:ANA_AC_SDLB:LBSET_TBL:THRES.THRES
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_LBGRP_MISC . THRES_SHIFT
 */
#define  VTSS_F_ANA_AC_SDLB_LBGRP_MISC_THRES_SHIFT(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_ANA_AC_SDLB_LBGRP_MISC_THRES_SHIFT     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_ANA_AC_SDLB_LBGRP_MISC_THRES_SHIFT(x)  VTSS_EXTRACT_BITFIELD(x,8,3)


/**
 * \brief Tokens to subtract per frame, when DLB_FRM_RATE_ENA=1.
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBGRP_TBL:FRM_RATE_TOKENS
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBGRP_CNT (??), 0-4
 */
#define VTSS_ANA_AC_SDLB_FRM_RATE_TOKENS(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x1f0b,gi,6,0,4)

/**
 * \brief
 * Number of tokens to subtract from bucket on SoF events for LBs with
 * FRM_RATE_ENA=1.Only used if FRM_RATE_ENA=1 for LB.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_FRM_RATE_TOKENS . FRM_RATE_TOKENS
 */
#define  VTSS_F_ANA_AC_SDLB_FRM_RATE_TOKENS_FRM_RATE_TOKENS(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ANA_AC_SDLB_FRM_RATE_TOKENS_FRM_RATE_TOKENS     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ANA_AC_SDLB_FRM_RATE_TOKENS_FRM_RATE_TOKENS(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/**
 * \brief LB Group current state
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBGRP_TBL:LBGRP_STATE_TBL
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBGRP_CNT (??), 0-4
 */
#define VTSS_ANA_AC_SDLB_LBGRP_STATE_TBL(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x1f0b,gi,6,0,5)

/**
 * \brief
 * PUP is ongoing for this group
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_LBGRP_STATE_TBL . PUP_ONGOING
 */
#define  VTSS_F_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_ONGOING(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_ONGOING  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_ONGOING(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * The LBSET selected for PUP is waiting for configuration read out from
 * the LBSET_TBL
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_LBGRP_STATE_TBL . PUP_WAIT_ACK
 */
#define  VTSS_F_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_WAIT_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_WAIT_ACK  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_WAIT_ACK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Address of current LB Set in LB Group
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_LBGRP_STATE_TBL . PUP_LBSET_NEXT
 */
#define  VTSS_F_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_LBSET_NEXT(x)  VTSS_ENCODE_BITFIELD(x,16,9)
#define  VTSS_M_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_LBSET_NEXT     VTSS_ENCODE_BITMASK(16,9)
#define  VTSS_X_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_LBSET_NEXT(x)  VTSS_EXTRACT_BITFIELD(x,16,9)

/**
 * Register Group: \a ANA_AC_SDLB:LBSET_TBL
 *
 * Not documented
 */


/**
 * \brief Number of tokens to add to bucket each time it is subject to a periodic update (PUP).
 *
 * \details
 * For DLBs replication 0 is CIR bucket and replication 1 is EIR bucket.
 *
 * Register: \a ANA_AC_SDLB:LBSET_TBL:PUP_TOKENS
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBSET_CNT (??), 0-495
 * @param ri Replicator: x_LB_2CYCLES_TYPE2_LBSET_LB_CNT (??), 0-1
 */
#define VTSS_ANA_AC_SDLB_PUP_TOKENS(gi,ri)   VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x0,gi,16,ri,0)

/**
 * \brief
 * Number of tokens to add to bucket each time it is subject to a periodic
 * update (PUP).The rate (tokens per second) with which tokens are added to
 * the bucket is:   PUP_TOKENS x clk_frequency / PUP_INTERVAL A bucket can
 * be configured to be permanently open by settingPUP_TOKENS=0x1fffWhen
 * permanently open, no tokens are subtracted from the bucket and PUP will
 * set the number of tokens in the bucket to THRES. No inheritance will
 * occur when a bucket is permanently open.To configure a DLB to be
 * permanently open, PUP_TOKENS must be set to 0x1fff for both the CIR
 * bucket and the EIR bucket. Setting only CIR bucket or only EIR bucket to
 * 0x1fff is not a valid configuration.Related
 * parameters:ANA_AC_SDLB:LBGRP_TBL:PUP_INTERVAL.PUP_INTERVAL
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_PUP_TOKENS . PUP_TOKENS
 */
#define  VTSS_F_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/**
 * \brief Bucket thresholds
 *
 * \details
 * For DLBs replication 0 is CIR bucket and replication 1 is EIR bucket.
 *
 * Register: \a ANA_AC_SDLB:LBSET_TBL:THRES
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBSET_CNT (??), 0-495
 * @param ri Replicator: x_LB_2CYCLES_TYPE2_LBSET_LB_CNT (??), 0-1
 */
#define VTSS_ANA_AC_SDLB_THRES(gi,ri)        VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x0,gi,16,ri,2)

/**
 * \brief
 * Maximum number of tokens the bucket is allowed to contain, i.e. the
 * maximum burst size for the LB.The unit for THRES is	2 ^ (13 -
 * THRES_SHIFT) tokensRelated
 * parameters:ANA_AC_SDLB:LBGRP_TBL:LBGRP_MISC.THRES_SHIFT
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_THRES . THRES
 */
#define  VTSS_F_ANA_AC_SDLB_THRES_THRES(x)    VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ANA_AC_SDLB_THRES_THRES       VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ANA_AC_SDLB_THRES_THRES(x)    VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Minimum number of tokens, which the bucket shall contain before it is
 * allowed to reopen.This can be used to configure hysteresis.The unit for
 * THRES_HYS is  2 ^ (13 - THRES_SHIFT) tokensRelated
 * parameters:ANA_AC_SDLB:LBGRP_TBL:LBGRP_MISC.THRES_SHIFT
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_THRES . THRES_HYS
 */
#define  VTSS_F_ANA_AC_SDLB_THRES_THRES_HYS(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_ANA_AC_SDLB_THRES_THRES_HYS     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_ANA_AC_SDLB_THRES_THRES_HYS(x)  VTSS_EXTRACT_BITFIELD(x,16,10)


/**
 * \brief Pointer to next XLB in LB Group.
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBSET_TBL:XLB_NEXT
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBSET_CNT (??), 0-495
 */
#define VTSS_ANA_AC_SDLB_XLB_NEXT(gi)        VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x0,gi,16,0,4)

/**
 * \brief
 * Address of LB Set containing next LB in LB Group.To mark the end of LB
 * Group's LB list, set LBSET_NEXT and LB_NEXT to point to current
 * LB.Related parameters:ANA_AC_SDLB:LBGRP_TBL:XLB_START
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_XLB_NEXT . LBSET_NEXT
 */
#define  VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Index of XLB's LB Group.Related parameters:ANA_AC_SDLB:LBGRP_TBL
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_XLB_NEXT . LBGRP
 */
#define  VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBGRP(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_ANA_AC_SDLB_XLB_NEXT_LBGRP     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_ANA_AC_SDLB_XLB_NEXT_LBGRP(x)  VTSS_EXTRACT_BITFIELD(x,24,3)


/**
 * \brief Inheritance related parameters.
 *
 * \details
 * For DLBs replication 0 is CIR bucket and replication 1 is EIR bucket.
 *
 * Register: \a ANA_AC_SDLB:LBSET_TBL:INH_CTRL
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBSET_CNT (??), 0-495
 * @param ri Replicator: x_LB_2CYCLES_TYPE2_LBSET_LB_CNT (??), 0-1
 */
#define VTSS_ANA_AC_SDLB_INH_CTRL(gi,ri)     VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x0,gi,16,ri,5)

/**
 * \brief
 * Maximum number of tokens to add to bucket for each PUP, including
 * inherited tokens.If the bucket is configured to inherit tokens, then it
 * is recommended to configure PUP_TOKENS_MAX, since that ensures that the
 * bucket is updated sufficiently frequently to absorb the inherited
 * tokens.PUP_TOKENS_MAX should not be set to a higher value than the
 * amount of tokens that the bucket can actually receive (i.e. it should
 * not just be set to all-ones).Can be used to implement MEF 10.3 CIRmax
 * and EIRmax.
 *
 * \details
 * 0: Disable PUP_TOKENS_MAX feature.
 *
 * Field: ::VTSS_ANA_AC_SDLB_INH_CTRL . PUP_TOKENS_MAX
 */
#define  VTSS_F_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX(x)  VTSS_EXTRACT_BITFIELD(x,0,13)

/**
 * \brief
 * Inheritance mode.Inheritance may be used for implementing MEF 10.2 and
 * 10.3 bandwidth profiles.Related
 * parameters:ANA_AC_SDLB:LBSET_TBL:INH_CTRL.INH_LB (only applicable if LB
 * Set has two or more
 * LBs)ANA_AC_SDLB:LBSET_TBL:INH_LBSET_ADDR.INH_LBSET_ADDR
 *
 * \details
 * 0 (INH_MODE_NONE):
 * No inheritor, i.e. any excess tokens are lost.
 *
 * 1 (INH_MODE_OTHER_LBSET):
 * Spill over into LB pointed to by INH_LBSET_ADDR and INH_LB.
 * INH_LB is only applicable if LB Set has two ore more LBs.
 *
 * 2 (INH_MODE_NEXT_LB):
 * Spill over into next LB in current LB Set.
 * This mode is only allowed for the first LB in a DLB (e.g. CIR LB
 * spilling into EIR LB).
 *
 * 3: Reserved
 *
 * Field: ::VTSS_ANA_AC_SDLB_INH_CTRL . INH_MODE
 */
#define  VTSS_F_ANA_AC_SDLB_INH_CTRL_INH_MODE(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_ANA_AC_SDLB_INH_CTRL_INH_MODE     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_ANA_AC_SDLB_INH_CTRL_INH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * Index of inheritor LB within inheritor LB Set.Only applicable if LB Set
 * has two ore more LBs.Related
 * parameters:ANA_AC_SDLB:LBSET_TBL:INH_CTRL.INH_MODEANA_AC_SDLB:LBSET_TBL:
 * INH_LBSET_ADDR.INH_LBSET_ADDR
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_INH_CTRL . INH_LB
 */
#define  VTSS_F_ANA_AC_SDLB_INH_CTRL_INH_LB(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ANA_AC_SDLB_INH_CTRL_INH_LB   VTSS_BIT(24)
#define  VTSS_X_ANA_AC_SDLB_INH_CTRL_INH_LB(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief Address of inheritor LB Set.
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBSET_TBL:INH_LBSET_ADDR
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBSET_CNT (??), 0-495
 */
#define VTSS_ANA_AC_SDLB_INH_LBSET_ADDR(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x0,gi,16,0,7)

/**
 * \brief
 * Address of inheritor LB Set.Related
 * parameters:ANA_AC_SDLB:LBSET_TBL:INH_CTRL.INH_MODEANA_AC_SDLB:LBSET_TBL:
 * INH_CTRL.INH_LB (only applicable if LB Set has two or more LBs)
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_INH_LBSET_ADDR . INH_LBSET_ADDR
 */
#define  VTSS_F_ANA_AC_SDLB_INH_LBSET_ADDR_INH_LBSET_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_SDLB_INH_LBSET_ADDR_INH_LBSET_ADDR     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_SDLB_INH_LBSET_ADDR_INH_LBSET_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Miscellaneous parameters per DLB
 *
 * \details
 * Miscellaneous parameters for each pair of two LBs.
 * LB n (even) is CIR, LB n+1 (odd) is EIR.
 *
 * Register: \a ANA_AC_SDLB:LBSET_TBL:DLB_MISC
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBSET_CNT (??), 0-495
 */
#define VTSS_ANA_AC_SDLB_DLB_MISC(gi)        VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x0,gi,16,0,8)

/**
 * \brief
 * Enable frame rate mode for both LBs in DLB.Frame rate related
 * parameters:ANA_AC_SDLB:MISC:MISC_RATE_CTRL.FRM_RATE_ENAANA_AC_SDLB:LBGRP
 * _TBL:FRM_RATE_TOKENS.FRM_RATE_TOKENS
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_DLB_MISC . DLB_FRM_RATE_ENA
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_MISC_DLB_FRM_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_SDLB_DLB_MISC_DLB_FRM_RATE_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_SDLB_DLB_MISC_DLB_FRM_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Once a single red frame has been observed (and thus dropped), then drop
 * all subsequent frames regardless of number of tokens in DLB's
 * buckets.Related
 * parameters:ANA_AC_SDLB:MISC:MARK_ALL_FRMS_RED_SETANA_AC_SDLB:MISC:MARK_A
 * LL_FRMS_RED_CLRANA_AC_SDLB:LBSET_TBL:DLB_MISC.MARK_ALL_FRMS_RED_MODE
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_DLB_MISC . MARK_ALL_FRMS_RED_ENA
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_MISC_MARK_ALL_FRMS_RED_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_AC_SDLB_DLB_MISC_MARK_ALL_FRMS_RED_ENA  VTSS_BIT(6)
#define  VTSS_X_ANA_AC_SDLB_DLB_MISC_MARK_ALL_FRMS_RED_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Criteria for when to set MarkAllFramesRed=1 (i.e. drop all frames).This
 * parameter is only applicable if MARK_ALL_FRMS_RED_ENA=1.Mode 0 should be
 * used if DLB is used as a single LB, i.e. EIR bucket is always closed and
 * only CIR bucket is used to police traffic.Mode 1 should be used if both
 * LBs are used.Related
 * parameters:ANA_AC_SDLB:LBSET_TBL:DLB_MISC.MARK_ALL_FRMS_RED_ENA
 *
 * \details
 * 0: Enter state MarkAllFramesRed=1 if both buckets of DLB are closed.
 * 1: Enter state MarkAllFramesRed=1 EIR bucket is closed.
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_MISC . MARK_ALL_FRMS_RED_MODE
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_MISC_MARK_ALL_FRMS_RED_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_AC_SDLB_DLB_MISC_MARK_ALL_FRMS_RED_MODE  VTSS_BIT(7)
#define  VTSS_X_ANA_AC_SDLB_DLB_MISC_MARK_ALL_FRMS_RED_MODE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Number of tokens to subtract from bucket, when SoF is encountered.A
 * value of 20 will correspond to inclusion of preamble and interframe gap
 * in rate.
 *
 * \details
 * Two complements encoded.
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_MISC . DLB_FRM_ADJ
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_MISC_DLB_FRM_ADJ(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_ANA_AC_SDLB_DLB_MISC_DLB_FRM_ADJ     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_ANA_AC_SDLB_DLB_MISC_DLB_FRM_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,8,7)


/**
 * \brief DLB configuration
 *
 * \details
 * Register: \a ANA_AC_SDLB:LBSET_TBL:DLB_CFG
 *
 * @param gi Replicator: x_LB_2CYCLES_TYPE2_LBSET_CNT (??), 0-495
 */
#define VTSS_ANA_AC_SDLB_DLB_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_ANA_AC_SDLB,0x0,gi,16,0,9)

/**
 * \brief
 * Configuration of the drop precedence change for yellow frames being
 * remarked to red. By default, such frames are discarded. When
 * EIR_INC_DP_VAL > 0, the DP level will be incremented with EIR_INC_DP_VAL
 * instead of discarding.
 *
 * \details
 * 0: Frame is discarded.
 * n: DP is increased with n for traffic exceeding PIR.
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . EIR_INC_DP_VAL
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_EIR_INC_DP_VAL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_EIR_INC_DP_VAL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_EIR_INC_DP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * Drop yellow frames.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . DROP_ON_YELLOW_ENA
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_DROP_ON_YELLOW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_DROP_ON_YELLOW_ENA  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_DROP_ON_YELLOW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Configuration of Drop Precedence bypass level. Frames with DP below
 * DP_BYPASS_LVL bypass the policer (frames are never policed and the
 * bucket is not updated with the frames).
 *
 * \details
 * 0: No frames bypass the policer
 * 1: Frames with DP = 0 bypass the policer
 * 2: Frames with DP = 0 or 1 bypass the policer
 * 3: Frames with DP = 0, 1 or 2 bypass the policer
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . DP_BYPASS_LVL
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_DP_BYPASS_LVL(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_DP_BYPASS_LVL     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_DP_BYPASS_LVL(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * If set, BDLB policing is disabled.
 *
 * \details
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . HIER_DLB_DIS
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_HIER_DLB_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_HIER_DLB_DIS  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_HIER_DLB_DIS(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Configures if stripped encapsulation data (normalized data) is policed
 * by the policer.
 *
 * \details
 * 0: Encapsulation data is counted as frame data.
 * 1: Encapsulation data in not counted as frame data.
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . ENCAP_DATA_DIS
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_ENCAP_DATA_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_ENCAP_DATA_DIS  VTSS_BIT(7)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_ENCAP_DATA_DIS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Configuration of dual leaky bucket color awareness.Frames with DP below
 * or equal to COLOR_AWARE_LVL is treated as green. Frames with DP above
 * COLOR_AWARE_LVL are treated as yellow.
 *
 * \details
 * 0: DLB policer is color aware. Incoming frames with DP=0 are green and
 * frames with DP>0 are yellow.
 * 1: DLB policer is color aware. Incoming frames with DP<=1 are green and
 * frames with DP>1 are yellow.
 * 2: DLB policer is color aware. Incoming frames with DP<=2 are green and
 * frames with DP>2 are yellow.
 * 3: DLB policer is color unaware. All incoming frames are green.
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . COLOR_AWARE_LVL
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_COLOR_AWARE_LVL(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_COLOR_AWARE_LVL     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_COLOR_AWARE_LVL(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * Configuration of the drop precedence change for green frames being
 * remarked to yellow. For such frames, the DP level will be incremented
 * with CIR_INC_DP_VAL.
 *
 * \details
 * 0: DP is not increased.
 * n: DP is increased with n for PIR traffic.
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . CIR_INC_DP_VAL
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_CIR_INC_DP_VAL(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_CIR_INC_DP_VAL     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_CIR_INC_DP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Control the algorithm for dual leaky buckets.The following algorithms
 * are supported:Single Rate Three Color Marker, RFC2697 (SR TCM)Two Rate
 * Three Color Marker, RFC2698 (TR TCM)MEF 10.2MEF 10.3 (only supported if
 * instantiation includes INH_CTRL register).To configure SR TCM use the
 * following configuration:1) Set DLB_MODE=MEF2) Configure rate of bucket 0
 * to CIR3) Configure the inheritor of bucket 0 to be bucket 1 (INH_MODE=1,
 * INH_LB=1 or DLB_COUPLING_MODE=1)4) Configure rate of bucket 1 to 0
 * (PUP_TOKENS=0)To configure TR TCM use the following configuration:Set
 * DLB_MODE=TR_TCMConfigure rate+threshold of bucket 0/1 to CIR/EIR+CBS/EBS
 *
 * \details
 * 0: MEF
 * 1: TR_TCM
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . DLB_MODE
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_DLB_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_DLB_MODE  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_DLB_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Configures action to be applied to policed frames.
 *
 * \details
 * 0: No action.
 * 1: Remove front ports from frame's destination port set.
 * 2: Remove CPU ports from frame's destination port set.
 * 3: Remove both front ports and CPU ports from frame's destination port
 * set.
 *
 * Field: ::VTSS_ANA_AC_SDLB_DLB_CFG . TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_ANA_AC_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_AC_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_AC_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_LAGUNA_REGS_ANA_AC_SDLB_H_ */
