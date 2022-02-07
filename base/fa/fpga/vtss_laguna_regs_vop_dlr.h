// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_VOP_DLR_H_
#define _VTSS_LAGUNA_REGS_VOP_DLR_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a VOP_DLR
 *
 * The OAM MEP Processor block implements the HW support for Versatile OAM
 * Endpoints (VOE), MRP endpoints, and DLR endpoints.
 *
 ***********************************************************************/

/**
 * Register Group: \a VOP_DLR:VOE_CONF_DLR
 *
 * Device Level Ring endpoint
 */


/**
 * \brief VOE configuration common between VOE types
 *
 * \details
 * This register is identical in VOE_CONF, VOE_CONF_MPLS, and VOE_CONF_L3.
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:VOE_COMMON_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_VOE_COMMON_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,0)

/**
 * \brief
 * Configures VOE for Down-MEP or Up-MEP operation.Note:Port VOEs only
 * support Down-MEP functionality. UPMEP_ENA must be set to 0.DLR VOEs only
 * support Down-MEP functionality. UPMEP_ENA must be set to 0.
 *
 * \details
 * 0: Configure VOE for Down-MEP functionality.
 * 1: Configure VOE for Up-MEP functionality.
 *
 * Field: ::VTSS_VOP_DLR_VOE_COMMON_CFG . UPMEP_ENA
 */
#define  VTSS_F_VOP_DLR_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_DLR_VOE_COMMON_CFG_UPMEP_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_DLR_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * If another VOE is pointing to this VOE as a Path VOE using the following
 * configuration: * PATH_VOEID * PATH_VOE_ENAthis register MUST be set to
 * '1'.If not this register must be set to '0'.
 *
 * \details
 * '0': This VOE is not configured as PATH VOE in another VOE.
 * '1': This VOE is configured as PATH VOE in another VOE.
 *
 * Field: ::VTSS_VOP_DLR_VOE_COMMON_CFG . VOE_IS_PATH
 */
#define  VTSS_F_VOP_DLR_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_DLR_VOE_COMMON_CFG_VOE_IS_PATH  VTSS_BIT(12)
#define  VTSS_X_VOP_DLR_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * The VOE supports hierarchical LM counting.This implies that when a VOE
 * is processing a frame, it can update the LM counter of the VOE
 * configured at the Server Layer, if a Server Layer exists.Within the
 * scope of the register list, a VOE configured at the Server Layer is
 * referred to as Path VOE.This register is used to assign a Path VOE to
 * the current service VOE.Port VOEs are considered as Server Layer VOEs
 * per default, and can not be assigned at Path VOEs.Assigning a Path VOE
 * to the VOE implies that all frames received by this VOE, will also be
 * counted by the Path VOE indicated by the following register: *
 * PATH_VOEIDThe path VOE must be enabled by asserting the following field:
 *  * PATH_VOE_ENANote, that the VOE assigned as Path VOP must be enabled
 * for Path VOE operation: * VOE_IS_PATH
 *
 * \details
 * Field: ::VTSS_VOP_DLR_VOE_COMMON_CFG . PATH_VOE_ENA
 */
#define  VTSS_F_VOP_DLR_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_DLR_VOE_COMMON_CFG_PATH_VOE_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_DLR_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Assigns a Path VOE to the VOE. See description in PATH_VOE_ENA.Must
 * point to a VOE in the pool of Service VOEs (0 - 7).
 *
 * \details
 * Field: ::VTSS_VOP_DLR_VOE_COMMON_CFG . PATH_VOEID
 */
#define  VTSS_F_VOP_DLR_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_VOP_DLR_VOE_COMMON_CFG_PATH_VOEID     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_VOP_DLR_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * If ESDX counter control is enabled, the VOP will signal disabling of
 * ESDX counting to the REW for OAM frames.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_VOE_COMMON_CFG . ESDX_CNT_CTRL_ENA
 */
#define  VTSS_F_VOP_DLR_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_DLR_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_DLR_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configures miscellaneous parameters
 *
 * \details
 * Basic DLR configuration.
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:DLR_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_DLR_CTRL(gi)            VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,1)

/**
 * \brief
 * If set, the DLR Advertise frame's Sequence ID is checked against the
 * expected sequence identifier and frames for which the Sequence ID does
 * not match the expected value are copied to the CPU using the
 * VOP::CPU_EXTR_DLR.ACT_CPU_QU queue.For frames failing the check,
 * VOP_DLR:VOE_STAT_DLR:DLR_STICKY.ADV_SEQ_ERR_STICKY is set. The expected
 * value is calculated as VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ[1]+1. The frame's
 * Sequence ID is stored in VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ[1] as the
 * latest valid sequence identifier.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.ADV_CHK_SEQ_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.BCN_CHK_SEQ_ENA-
 * VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ-
 * VOP_DLR:VOE_STAT_DLR:DLR_STICKY.RX_SEQ_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_CTRL . ADV_CHK_SEQ_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_CTRL_ADV_CHK_SEQ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_DLR_DLR_CTRL_ADV_CHK_SEQ_ENA  VTSS_BIT(14)
#define  VTSS_X_VOP_DLR_DLR_CTRL_ADV_CHK_SEQ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * If set, the DLR Beacon frame's Sequence ID is checked against the
 * expected sequence identifier and frames for which the Sequence ID does
 * not match the expected value are copied to the CPU using the
 * VOP::CPU_EXTR_DLR.ACT_CPU_QU queue. For frames failing the check,
 * VOP_DLR:VOE_STAT_DLR:DLR_STICKY.BCN_SEQ_ERR_STICKY is set. The expected
 * value is calculated as VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ[0]+1. The frame's
 * Sequence ID is stored in VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ[0] as the
 * latest valid sequence identifier.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.ADV_CHK_SEQ_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.BCN_CHK_SEQ_ENA-
 * VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ-
 * VOP_DLR:VOE_STAT_DLR:DLR_STICKY.BCN_SEQ_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_CTRL . BCN_CHK_SEQ_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_CTRL_BCN_CHK_SEQ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_DLR_DLR_CTRL_BCN_CHK_SEQ_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_DLR_DLR_CTRL_BCN_CHK_SEQ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * If set, the DMACs of DLR frames are checked against DLR frame type.DMAC
 * = 01-21-6C-00-00-01: Used by Beacon frames.DMAC = 01-21-6C-00-00-02:
 * Used by Neighbor_Check_Request, Neighbor_Check_Response, and Sign_On
 * frames.DMAC = 01-21-6C-00-00-03: Used by Announce, Locate_Fault, and
 * Flush_Tables frames.DMAC = 01-21-6C-00-00-04: Used by Advertise
 * frames.DMAC = 01-21-6C-00-00-05: Used by Learning_Update frames.Related
 * parameters:- VOP_DLR:VOE_CONF_DLR:DLR_CTRL.CHK_DMAC_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_DLR:VOE_STAT_DLR:DLR_STICKY.DMAC_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_CTRL . CHK_DMAC_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_CTRL_CHK_DMAC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_DLR_DLR_CTRL_CHK_DMAC_ENA  VTSS_BIT(12)
#define  VTSS_X_VOP_DLR_DLR_CTRL_CHK_DMAC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * If set, DLR Ring Protocol Version must be according to
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.DLR_VERSION.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.CHK_VERSION_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.DLR_VERSION-
 * VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_DLR:VOE_STAT_DLR:DLR_STICKY.VERSION_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_CTRL . CHK_VERSION_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_CTRL_CHK_VERSION_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_DLR_DLR_CTRL_CHK_VERSION_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_DLR_DLR_CTRL_CHK_VERSION_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * The expected DLR Ring Protocol Version.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.CHK_VERSION_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.DLR_VERSION
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_CTRL . DLR_VERSION
 */
#define  VTSS_F_VOP_DLR_DLR_CTRL_DLR_VERSION(x)  VTSS_ENCODE_BITFIELD(x,3,8)
#define  VTSS_M_VOP_DLR_DLR_CTRL_DLR_VERSION     VTSS_ENCODE_BITMASK(3,8)
#define  VTSS_X_VOP_DLR_DLR_CTRL_DLR_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,3,8)

/**
 * \brief
 * If set, Advertise frames are checked by the DLR endpoint and valid
 * Advertise frames may clear the associated miss counter.Related
 * parameters:- VOP_DLR:VOE_CONF_DLR:ADV_FWD_CTRL-
 * VOP_DLR:VOE_CONF_DLR:ADV_CFG
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_CTRL . DLR_ADV_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_CTRL_DLR_ADV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_DLR_DLR_CTRL_DLR_ADV_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_DLR_DLR_CTRL_DLR_ADV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If set, Beacon frames are checked by the DLR endpoint and valid Beacon
 * frames may clear the associated miss counter.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL- VOP_DLR:VOE_CONF_DLR:BCN_CFG
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_CTRL . DLR_BCN_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_CTRL_DLR_BCN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_DLR_DLR_CTRL_DLR_BCN_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_DLR_DLR_CTRL_DLR_BCN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Configures whether the DLR endpoint is active.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_CTRL . DLR_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_CTRL_DLR_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_DLR_DLR_CTRL_DLR_ENA      VTSS_BIT(0)
#define  VTSS_X_VOP_DLR_DLR_CTRL_DLR_ENA(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Forward selection for various DLR PDUs
 *
 * \details
 * Forward selection for various DLR PDUs, all using the following
 * encoding:
 * 0: No changes to forwarding (NOP)
 * 1: Copy frame to CPU (COPY)
 * 2: Redirect frame to CPU (REDIR)
 * 3: Discard frame (DISC)
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_DLR_FWD_CTRL(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,2)

/**
 * \brief
 * If set, DLR frames except Learning_Update frames are forwarded using
 * VOP_DLR:VOE_CONF_DLR:DLR_MASK_CFG. Note, settings in DLR_FWD_CTRL or
 * BCN_FWD_CTRL/ADV_FWD_CTRL are also applied and the port mask is not
 * applied when the frame is redirected or discarded.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_MASK_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_MASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_MASK_ENA  VTSS_BIT(24)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_MASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Forward selection for DLR frames failing one of the optional PDU
 * checks:- DLR version- DLR DMACFrames not failing these checks are
 * considered valid frames.Related paramenters:-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.CHK_DMAC_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.CHK_VERSION_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU- VOP_DLR:VOE_STAT_DLR:DLR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . ERR_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_ERR_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_ERR_FWD_SEL     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_ERR_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/**
 * \brief
 * Forward selection for Beacon frames. The CPU queue is configured in
 * VOP::CPU_EXTR_DLR.DLR_BCN_CPU_QU. Only applicable when hardware
 * processing of Beacon frames is disabled (DLR_CTRL.DLR_BCN_ENA). When
 * hardware processing of Beacon frames is enabled, setting DLR_BCN_FWD_SEL
 * > 0 triggers a CPU copy after the hardware processing is done.
 * Effectively, a NOP is changed to a COPY and a DISC is changed to a
 * REDIR. The CPU queue is set to VOP::CPU_EXTR_DLR.DLR_BCN_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_BCN_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_BCN_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_BCN_FWD_SEL     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_BCN_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * Forward selection for Neighbor_Check_Request and frames. The CPU queue
 * is configured in VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_NCREQ_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_NCREQ_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_NCREQ_FWD_SEL     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_NCREQ_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * Forward selection for Neighbor_Check_Response frames. The CPU queue is
 * configured in VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_NCRSP_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_NCRSP_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_NCRSP_FWD_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_NCRSP_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Forward selection for Link_Status/Neighbor_Status frames. The CPU queue
 * is configured in VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_LINK_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_LINK_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_LINK_FWD_SEL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_LINK_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * Forward selection for Locate_Fault frames. The CPU queue is configured
 * in VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_LOC_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_LOC_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_LOC_FWD_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_LOC_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * Forward selection for Announce frames. The CPU queue is configured in
 * VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_ANN_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_ANN_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_ANN_FWD_SEL     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_ANN_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * Forward selection for Sign_On frames. The CPU queue is configured in
 * VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_SIGN_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_SIGN_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_SIGN_FWD_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_SIGN_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Forward selection for Advertise frames. The CPU queue is configured in
 * VOP::CPU_EXTR_DLR.DLR_ADV_CPU_QU. Only applicable when hardware
 * processing of Advertise frames is disabled (DLR_CTRL.DLR_ADV_ENA). When
 * hardware processing of Advertise frames is enabled, setting
 * DLR_ADV_FWD_SEL > 0 triggers a CPU copy after the hardware processing is
 * done. Effectively, a NOP is changed to a COPY and a DISC is changed to a
 * REDIR. The CPU queue is set to VOP::CPU_EXTR_DLR.DLR_ADV_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_ADV_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_ADV_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_ADV_FWD_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_ADV_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Forward selection for Flush_Tables frames. The CPU queue is configured
 * in VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_FLSH_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_FLSH_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_FLSH_FWD_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_FLSH_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Forward selection for Learning_Update frames. The CPU queue is
 * configured in VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . DLR_LRN_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_DLR_LRN_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_DLR_LRN_FWD_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_DLR_LRN_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Forward selection for DLR frames not covered by other selections. The
 * CPU queue is configured in VOP::CPU_EXTR_DLR.DLR_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_FWD_CTRL . OTHER_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_DLR_FWD_CTRL_OTHER_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_DLR_DLR_FWD_CTRL_OTHER_FWD_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_DLR_DLR_FWD_CTRL_OTHER_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Port mask for DLR frames
 *
 * \details
 * Note, Learning_Update frames are not using this port mask.
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:DLR_MASK_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_DLR_MASK_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,3)

/**
 * \brief
 * Port mask used when PORTMASK_ENA is set.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_MASK_CFG . PORTMASK
 */
#define  VTSS_F_VOP_DLR_DLR_MASK_CFG_PORTMASK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_VOP_DLR_DLR_MASK_CFG_PORTMASK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_VOP_DLR_DLR_MASK_CFG_PORTMASK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Configuration of Beacon forward handling
 *
 * \details
 * Forward selection for Beacon frames when hardware processing is enabled,
 * all using the following encoding:
 * 0: No changes to forwarding (NOP)
 * 1: Copy frame to CPU (COPY)
 * 2: Redirect frame to CPU (REDIR)
 * 3: Discard frame (DISC)
 *
 * Related parameters:
 * - VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.DLR_MASK_ENA
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_BCN_FWD_CTRL(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,4)

/**
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_FWD_CTRL . HI_PRIO_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_BCN_FWD_CTRL_HI_PRIO_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_VOP_DLR_BCN_FWD_CTRL_HI_PRIO_FWD_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_VOP_DLR_BCN_FWD_CTRL_HI_PRIO_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_FWD_CTRL . LO_PRIO_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_BCN_FWD_CTRL_LO_PRIO_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_DLR_BCN_FWD_CTRL_LO_PRIO_FWD_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_DLR_BCN_FWD_CTRL_LO_PRIO_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Forward selection for Beacon frames for which frame's SMAC matches
 * DLR_MAC and the DLR ring state is not RING_FAULT_STATE. The CPU queue is
 * configured in VOP::CPU_EXTR_DLR.ACT_CPU_QU.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL.ACT_FWD_SEL-
 * VOP::CPU_EXTR_DLR.ACT_CPU_QU-
 * VOP_DLR:VOE_CONF_DLR:DLR_MAC_LSB.DLR_MAC_LSB-
 * VOP_DLR:VOE_CONF_DLR:DLR_MAC_MSB.DLR_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_FWD_CTRL . ACT_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_BCN_FWD_CTRL_ACT_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VOP_DLR_BCN_FWD_CTRL_ACT_FWD_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VOP_DLR_BCN_FWD_CTRL_ACT_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Forward selection for Beacon frames for which frame's SMAC matches
 * DLR_MAC and the DLR ring state is set to RING_FAULT_STATE. The CPU queue
 * is configured in VOP::CPU_EXTR_DLR.ACT_CPU_QU.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL.ACT_FAULT_FWD_SEL-
 * VOP::CPU_EXTR_DLR.ACT_CPU_QU-
 * VOP_DLR:VOE_CONF_DLR:DLR_MAC_LSB.DLR_MAC_LSB-
 * VOP_DLR:VOE_CONF_DLR:DLR_MAC_MSB.DLR_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_FWD_CTRL . ACT_FAULT_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_BCN_FWD_CTRL_ACT_FAULT_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_DLR_BCN_FWD_CTRL_ACT_FAULT_FWD_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_DLR_BCN_FWD_CTRL_ACT_FAULT_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Configuration of Beacon frame handling
 *
 * \details
 * Processing of valid Beacon frames:
 * 1) When frame's SMAC matches DLR_MAC and frame's ring state equals
 * FAULT_STATE:
 * - Use BCN_FWD_CTRL.ACT_FAULT_FWD_SEL for forwarding. Clear MISS_CNT when
 * FAULT_ENA and CLR_MISS_CNT_ENA are set.
 * - Hit-me-once when BCN_FWD_CTRL.NXT_FAULT_CPU_HITME_ONCE is set.
 *
 * 2) When frame's SMAC matches DLR_MAC and frame's ring state is different
 * from FAULT_STATE:
 * - Use BCN_FWD_CTRL.ACT_FWD_SEL for forwarding. Clear MISS_CNT when
 * CLR_MISS_CNT_ENA are set.
 *
 * 3) When frame's SMAC does not match DLR_MAC:
 * - Use BCN_FWD_CTRL.HI_PRIO_FWD_SEL when frame's precedence is better
 * than current active ring supervisor.
 * - Use BCN_FWD_CTRL.LO_PRIO_FWD_SEL when frame's precedence is worse than
 * current active ring supervisor.
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:BCN_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_BCN_CFG(gi)             VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,5)

/**
 * \brief
 * If set, Beacon frames with ring state RING_FAULT_STATE are subject to
 * clearing the LOC miss counter. CLR_MISS_CNT_ENA must still be set.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_CFG . FAULT_ENA
 */
#define  VTSS_F_VOP_DLR_BCN_CFG_FAULT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_DLR_BCN_CFG_FAULT_ENA     VTSS_BIT(5)
#define  VTSS_X_VOP_DLR_BCN_CFG_FAULT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If set, valid Beacon frames clear the DLR_MISS_CNT.For a ring
 * supervisor, a valid Beacon frame is from the ring supervisor itself.For
 * a ring node, a valid Beacon frame is from the active ring supervisor.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_CFG . CLR_MISS_CNT_ENA
 */
#define  VTSS_F_VOP_DLR_BCN_CFG_CLR_MISS_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_DLR_BCN_CFG_CLR_MISS_CNT_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_DLR_BCN_CFG_CLR_MISS_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * LOC period used by endpoint. Related parameters:- VOP::LOC_PERIOD_CFG
 *
 * \details
 * 0: No LOC period in use.
 * 1-7: Reserved by CCM if CCM is enabled. Can be used if CCM is not
 * enabled.
 * 8-10: LOC period configured in VOP::LOC_PERIOD_CFG[n-1] in use.
 * 11-15: Reserved
 *
 * Field: ::VTSS_VOP_DLR_BCN_CFG . LOC_PERIOD
 */
#define  VTSS_F_VOP_DLR_BCN_CFG_LOC_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_DLR_BCN_CFG_LOC_PERIOD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_DLR_BCN_CFG_LOC_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Configuration of Advertise forward handling
 *
 * \details
 * Forward selection for Advertise frames when hardware processing is
 * enabled, all using the following encoding:
 * 0: No changes to forwarding (NOP)
 * 1: Copy frame to CPU (COPY)
 * 2: Redirect frame to CPU (REDIR)
 * 3: Discard frame (DISC)
 *
 * Related parameters:
 * - VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.DLR_MASK_ENA
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:ADV_FWD_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_ADV_FWD_CTRL(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,6)

/**
 * \brief
 * Forward selection for Advertise frame from gateway with higher
 * precedence. The CPU queue is configured in
 * VOP::CPU_EXTR_DLR.NEW_CPU_QU.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:ADV_FWD_CTRL.GW_HI_PRIO_FWD_SEL-
 * VOP::CPU_EXTR_DLR.NEW_CPU_QU-
 * VOP_DLR:VOE_CONF_DLR:GW_MAC_LSB.GW_MAC_LSB-
 * VOP_DLR:VOE_CONF_DLR:GW_MAC_MSB.GW_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_DLR_ADV_FWD_CTRL . GW_HI_PRIO_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_ADV_FWD_CTRL_GW_HI_PRIO_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_DLR_ADV_FWD_CTRL_GW_HI_PRIO_FWD_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_DLR_ADV_FWD_CTRL_GW_HI_PRIO_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Forward selection for Advertise frame from gateway with lower
 * precedence. The CPU queue is configured in
 * VOP::CPU_EXTR_DLR.NEW_CPU_QU.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:ADV_FWD_CTRL.GW_LO_PRIO_FWD_SEL-
 * VOP::CPU_EXTR_DLR.NEW_CPU_QU-
 * VOP_DLR:VOE_CONF_DLR:GW_MAC_LSB.GW_MAC_LSB-
 * VOP_DLR:VOE_CONF_DLR:GW_MAC_MSB.GW_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_DLR_ADV_FWD_CTRL . GW_LO_PRIO_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_ADV_FWD_CTRL_GW_LO_PRIO_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VOP_DLR_ADV_FWD_CTRL_GW_LO_PRIO_FWD_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VOP_DLR_ADV_FWD_CTRL_GW_LO_PRIO_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Forward selection for Advertise frame for which frame's SMAC matches
 * GW_MAC and the gateway state is not FAULT_STATE. The CPU queue is
 * configured in VOP::CPU_EXTR_DLR.ACT_CPU_QU.Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:ADV_FWD_CTRL.GW_FWD_SEL-
 * VOP::CPU_EXTR_DLR.ACT_CPU_QU-
 * VOP_DLR:VOE_CONF_DLR:GW_MAC_LSB.GW_MAC_LSB-
 * VOP_DLR:VOE_CONF_DLR:GW_MAC_MSB.GW_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_DLR_ADV_FWD_CTRL . GW_FWD_SEL
 */
#define  VTSS_F_VOP_DLR_ADV_FWD_CTRL_GW_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_DLR_ADV_FWD_CTRL_GW_FWD_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_DLR_ADV_FWD_CTRL_GW_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Configuration of Advertise frame handling
 *
 * \details
 * Processing of valid Advertise frames:
 * 1) When frame's SMAC matches GW_MAC:
 * - Use ADV_FWD_CTRL.GW_FWD_SEL for forwarding. Clear ADV_MISS_CNT when
 * ADV_CLR_MISS_CNT_ENA are set.
 *
 * 2) When frame's SMAC does not match GW_MAC:
 * - Use ADV_FWD_CTRL.GW_HI_PRIO_FWD_SEL when frame's precedence is better
 * than current active gateway and gateway state is different from
 * FAULT_STATE
 * - Use ADV_FWD_CTRL.GW_LO_PRIO_FWD_SEL when frame's precedence is worse
 * than current active ring gateway or gateway state equals FAULT_STATE
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:ADV_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_ADV_CFG(gi)             VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,7)

/**
 * \brief
 * If set, valid Advertise frames clear the ADV_MISS_CNT.For a gateway, a
 * valid Advertise frame is from the active gateway.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_ADV_CFG . ADV_CLR_MISS_CNT_ENA
 */
#define  VTSS_F_VOP_DLR_ADV_CFG_ADV_CLR_MISS_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_DLR_ADV_CFG_ADV_CLR_MISS_CNT_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_DLR_ADV_CFG_ADV_CLR_MISS_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * LOC period used by endpoint. Related parameters:- VOP::LOC_PERIOD_CFG
 *
 * \details
 * 0: No LOC period in use.
 * 1-7: Reserved by CCM if CCM is enabled. Can be used if CCM is not
 * enabled.
 * 8-10: LOC period configured in VOP::LOC_PERIOD_CFG[n-1] in use.
 * 11-15: Reserved
 *
 * Field: ::VTSS_VOP_DLR_ADV_CFG . ADV_LOC_PERIOD
 */
#define  VTSS_F_VOP_DLR_ADV_CFG_ADV_LOC_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_DLR_ADV_CFG_ADV_LOC_PERIOD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_DLR_ADV_CFG_ADV_LOC_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief DLR precedence configuration
 *
 * \details
 * Register: \a VOP_DLR:VOE_CONF_DLR:DLR_PREC_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_DLR_PREC_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,8)

/**
 * \brief
 * Gateway precedence.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_PREC_CFG . GW_PREC
 */
#define  VTSS_F_VOP_DLR_DLR_PREC_CFG_GW_PREC(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_DLR_DLR_PREC_CFG_GW_PREC     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_DLR_DLR_PREC_CFG_GW_PREC(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Supervisor precedence.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_PREC_CFG . ACT_PREC
 */
#define  VTSS_F_VOP_DLR_DLR_PREC_CFG_ACT_PREC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_DLR_DLR_PREC_CFG_ACT_PREC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_DLR_DLR_PREC_CFG_ACT_PREC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Active ring supervisor's MAC address configuration (LSB)
 *
 * \details
 * Related parameters:
 * - VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL.ACT_FWD_SEL
 * - VOP::CPU_EXTR_DLR.ACT_CPU_QU
 * - VOP_DLR:VOE_CONF_DLR:DLR_MAC_LSB.DLR_MAC_LSB
 * - VOP_DLR:VOE_CONF_DLR:DLR_MAC_MSB.DLR_MAC_MSB
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:DLR_MAC_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_DLR_MAC_LSB(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,9)

/**
 * \brief
 * Active ring supervisor's MAC address
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_MAC_LSB . DLR_MAC_LSB
 */
#define  VTSS_F_VOP_DLR_DLR_MAC_LSB_DLR_MAC_LSB(x)  (x)
#define  VTSS_M_VOP_DLR_DLR_MAC_LSB_DLR_MAC_LSB     0xffffffff
#define  VTSS_X_VOP_DLR_DLR_MAC_LSB_DLR_MAC_LSB(x)  (x)


/**
 * \brief Active ring supervisor's MAC address configuration (MSB)
 *
 * \details
 * Related parameters:
 * - VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL.ACT_FWD_SEL
 * - VOP::CPU_EXTR_DLR.ACT_CPU_QU
 * - VOP_DLR:VOE_CONF_DLR:DLR_MAC_LSB.DLR_MAC_LSB
 * - VOP_DLR:VOE_CONF_DLR:DLR_MAC_MSB.DLR_MAC_MSB
 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:DLR_MAC_MSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_DLR_MAC_MSB(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,10)

/**
 * \brief
 * Active ring supervisor's MAC address
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_MAC_MSB . DLR_MAC_MSB
 */
#define  VTSS_F_VOP_DLR_DLR_MAC_MSB_DLR_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_DLR_DLR_MAC_MSB_DLR_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_DLR_DLR_MAC_MSB_DLR_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Active gateway's MAC address configuration (LSB)
 *
 * \details
 * Related parameters:

 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:GW_MAC_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_GW_MAC_LSB(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,11)

/**
 * \brief
 * Active gateway's MAC address
 *
 * \details
 * Field: ::VTSS_VOP_DLR_GW_MAC_LSB . GW_MAC_LSB
 */
#define  VTSS_F_VOP_DLR_GW_MAC_LSB_GW_MAC_LSB(x)  (x)
#define  VTSS_M_VOP_DLR_GW_MAC_LSB_GW_MAC_LSB     0xffffffff
#define  VTSS_X_VOP_DLR_GW_MAC_LSB_GW_MAC_LSB(x)  (x)


/**
 * \brief Active gateway's MAC address configuration (MSB)
 *
 * \details
 * Related parameters:

 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:GW_MAC_MSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_GW_MAC_MSB(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,0,12)

/**
 * \brief
 * Active gateway's MAC address
 *
 * \details
 * Field: ::VTSS_VOP_DLR_GW_MAC_MSB . GW_MAC_MSB
 */
#define  VTSS_F_VOP_DLR_GW_MAC_MSB_GW_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_DLR_GW_MAC_MSB_GW_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_DLR_GW_MAC_MSB_GW_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief DLR Beacon and Advertise Tx configuration
 *
 * \details
 * Configuration for Beacon and Advertise Tx frame handling.
 * Index 0: Configuration applies to Beacon frames.
 * Index 1: Configuration applies to Advertise frames.
 *
 * To use the configuration, IFH field REW_OAM must be set and IFH field
 * OAM_TYPE must be set to DLR PDU type.

 *
 * Register: \a VOP_DLR:VOE_CONF_DLR:DLR_TX_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 * @param ri Register: DLR_TX_CFG (??), 0-1
 */
#define VTSS_VOP_DLR_DLR_TX_CFG(gi,ri)       VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x0,gi,16,ri,13)

/**
 * \brief
 * If set, the sequence numbers in Beacon/Advertise frames transmitted on
 * this port are updated with the value in PTP_SEQ_NO selected by frame's
 * IFH field SEQ_NUM. The sequence number is auto-incremented after use.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_TX_CFG . DLR_SEQ_UPD_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_TX_CFG_DLR_SEQ_UPD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_DLR_DLR_TX_CFG_DLR_SEQ_UPD_ENA  VTSS_BIT(5)
#define  VTSS_X_VOP_DLR_DLR_TX_CFG_DLR_SEQ_UPD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If set, the ring state/gateway state in Beacon/Advertise frames
 * transmitted on this port are updated with the values in
 * DLR_TX_CFG.DLR_STATE.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_TX_CFG . DLR_STATE_UPD_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_TX_CFG_DLR_STATE_UPD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_DLR_DLR_TX_CFG_DLR_STATE_UPD_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_DLR_DLR_TX_CFG_DLR_STATE_UPD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Configures least significant bits for the ring or gateway state to be
 * transmitted in the next Beacon/Advertise frame. Other bits in the state
 * are set to 0. Used when DLR_TX_CFG.DLR_STATE_UPD_ENA is set.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_TX_CFG . DLR_STATE
 */
#define  VTSS_F_VOP_DLR_DLR_TX_CFG_DLR_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_DLR_DLR_TX_CFG_DLR_STATE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_DLR_DLR_TX_CFG_DLR_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a VOP_DLR:VOE_STAT_DLR
 *
 * Per VOE statistics and counters (DLR)
 */


/**
 * \brief DLR sequence identifier
 *
 * \details
 * Configures the expected value of the sequence identifier for the next
 * Beacon/Advertise frame (DLR sequence Id). The value is incremented every
 * time a valid frame is received.
 *
 * Index 0: Configuration applies to DLR_BCN frames.
 * Index 1: Configuration applies to DLR_ADV frames.
 *
 * Related parameters:
 * - VOP_DLR:VOE_CONF_DLR:DLR_CTRL.ADV_CHK_SEQ_ENA
 * - VOP_DLR:VOE_CONF_DLR:DLR_CTRL.BCN_CHK_SEQ_ENA
 * - VOP::CPU_EXTR_CFG.CPU_ERR_QU
 * - VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ.RX_SEQ
 * - VOP_DLR:VOE_STAT_DLR:DLR_STICKY.RX_SEQ_ERR_STICKY
 *
 * Register: \a VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 * @param ri Register: DLR_RX_SEQ (??), 0-1
 */
#define VTSS_VOP_DLR_DLR_RX_SEQ(gi,ri)       VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,ri,0)

/**
 * \brief
 * Configures DLR frame's sequence identifier.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_RX_SEQ . RX_SEQ
 */
#define  VTSS_F_VOP_DLR_DLR_RX_SEQ_RX_SEQ(x)  (x)
#define  VTSS_M_VOP_DLR_DLR_RX_SEQ_RX_SEQ     0xffffffff
#define  VTSS_X_VOP_DLR_DLR_RX_SEQ_RX_SEQ(x)  (x)


/**
 * \brief DLR sequence identifier
 *
 * \details
 * Configures the expected value of the sequence identifier for the next
 * Beacon/Advertise frame (DLR sequence Id). The value is incremented every
 * time a frame is transmitted.
 *
 * Index 0: Configuration applies to DLR_BCN frames.
 * Index 1: Configuration applies to DLR_ADV frames.
 *
 * Related parameters:
 * - VOP_DLR:VOE_CONF_DLR:DLR_CTRL.ADV_CHK_SEQ_ENA
 * - VOP_DLR:VOE_CONF_DLR:DLR_CTRL.BCN_CHK_SEQ_ENA
 * - VOP::CPU_EXTR_CFG.CPU_ERR_QU
 * - VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ.RX_SEQ
 * - VOP_DLR:VOE_STAT_DLR:DLR_STICKY.RX_SEQ_ERR_STICKY
 *
 * Register: \a VOP_DLR:VOE_STAT_DLR:DLR_TX_SEQ
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 * @param ri Register: DLR_TX_SEQ (??), 0-1
 */
#define VTSS_VOP_DLR_DLR_TX_SEQ(gi,ri)       VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,ri,2)

/**
 * \brief
 * Configures DLR frame's sequence identifier.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_TX_SEQ . TX_SEQ
 */
#define  VTSS_F_VOP_DLR_DLR_TX_SEQ_TX_SEQ(x)  (x)
#define  VTSS_M_VOP_DLR_DLR_TX_SEQ_TX_SEQ     0xffffffff
#define  VTSS_X_VOP_DLR_DLR_TX_SEQ_TX_SEQ(x)  (x)


/**
 * \brief Status of DLR BCN handling
 *
 * \details
 * Register: \a VOP_DLR:VOE_STAT_DLR:BCN_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_BCN_STAT(gi)            VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,4)

/**
 * \brief
 * Specifies the maximum number of timeout periods without Beacon frames
 * from the supervisor.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_STAT . MAX_MISS_CNT
 */
#define  VTSS_F_VOP_DLR_BCN_STAT_MAX_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VOP_DLR_BCN_STAT_MAX_MISS_CNT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VOP_DLR_BCN_STAT_MAX_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Specifies the number of timeout periods without Beacon frames received
 * from the supervisor. Cleared by HW when receiving a valid Beacon frame.
 *
 * \details
 * n<MAX_MISS_CNT: No Loss of continuity
 * n==MAX_MISS_CNT: Loss of continuity
 *
 * Field: ::VTSS_VOP_DLR_BCN_STAT . MISS_CNT
 */
#define  VTSS_F_VOP_DLR_BCN_STAT_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_DLR_BCN_STAT_MISS_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_DLR_BCN_STAT_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Configuration of BCN_FAULT hit me once
 *
 * \details
 * Register: \a VOP_DLR:VOE_STAT_DLR:BCN_FAULT_HMO
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_BCN_FAULT_HMO(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,5)

/**
 * \brief
 * Extract next valid DLR Beacon frame from active supervisor with ring
 * state RING_FAULT_STATE to CPU according to configuration in
 * VOP::CPU_EXTR_DLR.ACT_CPU_QU.
 *
 * \details
 * 0: Disable (no CPU hitme once copy)
 * 1: Enable the next frame to be sent to CPU.
 *
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_VOP_DLR_BCN_FAULT_HMO . NXT_FAULT_CPU_HITME_ONCE
 */
#define  VTSS_F_VOP_DLR_BCN_FAULT_HMO_NXT_FAULT_CPU_HITME_ONCE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_DLR_BCN_FAULT_HMO_NXT_FAULT_CPU_HITME_ONCE  VTSS_BIT(0)
#define  VTSS_X_VOP_DLR_BCN_FAULT_HMO_NXT_FAULT_CPU_HITME_ONCE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of BCN_LOC hit me once
 *
 * \details
 * Register: \a VOP_DLR:VOE_STAT_DLR:BCN_LOC_HMO
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_BCN_LOC_HMO(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,6)

/**
 * \brief
 * Extract next DLR Beacon frame subject to clearing the LOC miss counter
 * to CPU according to configuration in VOP::CPU_EXTR_DLR.ACT_CPU_QU.
 *
 * \details
 * 0: Disable (no CPU hitme once copy)
 * 1: Enable the next frame to be sent to CPU.
 *
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_VOP_DLR_BCN_LOC_HMO . NXT_LOC_CPU_HITME_ONCE
 */
#define  VTSS_F_VOP_DLR_BCN_LOC_HMO_NXT_LOC_CPU_HITME_ONCE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_DLR_BCN_LOC_HMO_NXT_LOC_CPU_HITME_ONCE  VTSS_BIT(0)
#define  VTSS_X_VOP_DLR_BCN_LOC_HMO_NXT_LOC_CPU_HITME_ONCE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Counts number of received valid DLR Beacon frames subject to DLR Beacon processing
 *
 * \details
 * Counts number of received valid DLR Beacon frames that are subject to
 * DLR Beacon processing.
 *
 * Register: \a VOP_DLR:VOE_STAT_DLR:BCN_RX_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_BCN_RX_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,7)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_RX_CNT . BCN_RX_CNT
 */
#define  VTSS_F_VOP_DLR_BCN_RX_CNT_BCN_RX_CNT(x)  (x)
#define  VTSS_M_VOP_DLR_BCN_RX_CNT_BCN_RX_CNT     0xffffffff
#define  VTSS_X_VOP_DLR_BCN_RX_CNT_BCN_RX_CNT(x)  (x)


/**
 * \brief Counts number of received valid DLR Beacon frames that clear the LOC miss counter
 *
 * \details
 * Counts number of received DLR Beacon frames that pass requred ingress
 * checks and when enabled (BCN_CFG.CLR_MISS_CNT_ENA) clear the LOC miss
 * counter.
 *
 * Register: \a VOP_DLR:VOE_STAT_DLR:BCN_RX_LOC_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_BCN_RX_LOC_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,8)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_BCN_RX_LOC_CNT . BCN_RX_LOC_CNT
 */
#define  VTSS_F_VOP_DLR_BCN_RX_LOC_CNT_BCN_RX_LOC_CNT(x)  (x)
#define  VTSS_M_VOP_DLR_BCN_RX_LOC_CNT_BCN_RX_LOC_CNT     0xffffffff
#define  VTSS_X_VOP_DLR_BCN_RX_LOC_CNT_BCN_RX_LOC_CNT(x)  (x)


/**
 * \brief Status of DLR ADV handling
 *
 * \details
 * Register: \a VOP_DLR:VOE_STAT_DLR:ADV_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_ADV_STAT(gi)            VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,9)

/**
 * \brief
 * Specifies the maximum number of timeout periods without Advertise frames
 * from the gateway.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_ADV_STAT . ADV_MAX_MISS_CNT
 */
#define  VTSS_F_VOP_DLR_ADV_STAT_ADV_MAX_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VOP_DLR_ADV_STAT_ADV_MAX_MISS_CNT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VOP_DLR_ADV_STAT_ADV_MAX_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Specifies the number of timeout periods without Advertise frames
 * received from the gateway. Cleared by HW when receiving a valid
 * Advertise frame.
 *
 * \details
 * n<TBD: No Loss of continuity
 * n==TBD: Loss of continuity
 *
 * Field: ::VTSS_VOP_DLR_ADV_STAT . ADV_MISS_CNT
 */
#define  VTSS_F_VOP_DLR_ADV_STAT_ADV_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_DLR_ADV_STAT_ADV_MISS_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_DLR_ADV_STAT_ADV_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Configuration of ADV_LOC hit me once
 *
 * \details
 * Register: \a VOP_DLR:VOE_STAT_DLR:ADV_LOC_HMO
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_ADV_LOC_HMO(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,10)

/**
 * \brief
 * Extract next DLR Advertise frame subject to clearing the LOC miss
 * counter to CPU according to configuration in
 * VOP::CPU_EXTR_DLR.ACT_CPU_QU.
 *
 * \details
 * 0: Disable (no CPU hitme once copy)
 * 1: Enable the next frame to be sent to CPU.
 *
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_VOP_DLR_ADV_LOC_HMO . NXT_ADV_LOC_CPU_HITME_ONCE
 */
#define  VTSS_F_VOP_DLR_ADV_LOC_HMO_NXT_ADV_LOC_CPU_HITME_ONCE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_DLR_ADV_LOC_HMO_NXT_ADV_LOC_CPU_HITME_ONCE  VTSS_BIT(0)
#define  VTSS_X_VOP_DLR_ADV_LOC_HMO_NXT_ADV_LOC_CPU_HITME_ONCE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Counts number of received valid DLR Advertise frames subject to DLR Advertise processing
 *
 * \details
 * Counts number of received valid DLR Advertise frames that are subject to
 * DLR Advertise processing.
 *
 * Register: \a VOP_DLR:VOE_STAT_DLR:ADV_RX_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_ADV_RX_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,11)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_ADV_RX_CNT . ADV_RX_CNT
 */
#define  VTSS_F_VOP_DLR_ADV_RX_CNT_ADV_RX_CNT(x)  (x)
#define  VTSS_M_VOP_DLR_ADV_RX_CNT_ADV_RX_CNT     0xffffffff
#define  VTSS_X_VOP_DLR_ADV_RX_CNT_ADV_RX_CNT(x)  (x)


/**
 * \brief Counts number of received valid DLR Advertise frames that clear the LOC miss counter
 *
 * \details
 * Counts number of received DLR Advertise frames that pass requred ingress
 * checks and when enabled (ADV_CFG.ADV_CLR_MISS_CNT_ENA) clear the LOC
 * miss counter.
 *
 * Register: \a VOP_DLR:VOE_STAT_DLR:ADV_RX_LOC_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_ADV_RX_LOC_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,12)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_ADV_RX_LOC_CNT . ADV_RX_LOC_CNT
 */
#define  VTSS_F_VOP_DLR_ADV_RX_LOC_CNT_ADV_RX_LOC_CNT(x)  (x)
#define  VTSS_M_VOP_DLR_ADV_RX_LOC_CNT_ADV_RX_LOC_CNT     0xffffffff
#define  VTSS_X_VOP_DLR_ADV_RX_LOC_CNT_ADV_RX_LOC_CNT(x)  (x)


/**
 * \brief Sticky bits for DLR processing
 *
 * \details
 * Register: \a VOP_DLR:VOE_STAT_DLR:DLR_STICKY
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_DLR_STICKY(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,13)

/**
 * \brief
 * Set if DLR frame was received.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_STICKY . DLR_RX_STICKY
 */
#define  VTSS_F_VOP_DLR_DLR_STICKY_DLR_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_DLR_DLR_STICKY_DLR_RX_STICKY  VTSS_BIT(7)
#define  VTSS_X_VOP_DLR_DLR_STICKY_DLR_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set if DLR frame was received and processing is enabled.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_STICKY . DLR_RX_PROC_STICKY
 */
#define  VTSS_F_VOP_DLR_DLR_STICKY_DLR_RX_PROC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_DLR_DLR_STICKY_DLR_RX_PROC_STICKY  VTSS_BIT(6)
#define  VTSS_X_VOP_DLR_DLR_STICKY_DLR_RX_PROC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set if frame with unexpected DMAC was received. Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.CHK_DMAC_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_DLR:VOE_STAT_DLR:DLR_STICKY.DMAC_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_STICKY . DMAC_ERR_STICKY
 */
#define  VTSS_F_VOP_DLR_DLR_STICKY_DMAC_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_DLR_DLR_STICKY_DMAC_ERR_STICKY  VTSS_BIT(5)
#define  VTSS_X_VOP_DLR_DLR_STICKY_DMAC_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set if frame with unexpected version was received. Related parameters:-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.CHK_VERSION_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.DLR_VERSION-
 * VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_DLR:VOE_STAT_DLR:DLR_STICKY.VERSION_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_STICKY . VERSION_ERR_STICKY
 */
#define  VTSS_F_VOP_DLR_DLR_STICKY_VERSION_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_DLR_DLR_STICKY_VERSION_ERR_STICKY  VTSS_BIT(4)
#define  VTSS_X_VOP_DLR_DLR_STICKY_VERSION_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Related parameters:- VOP_DLR:VOE_CONF_DLR:DLR_CTRL.BCN_CHK_SEQ_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.ADV_CHK_SEQ_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU- VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ.RX_SEQ
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_STICKY . BCN_SEQ_ERR_STICKY
 */
#define  VTSS_F_VOP_DLR_DLR_STICKY_BCN_SEQ_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_DLR_DLR_STICKY_BCN_SEQ_ERR_STICKY  VTSS_BIT(3)
#define  VTSS_X_VOP_DLR_DLR_STICKY_BCN_SEQ_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Related parameters:- VOP_DLR:VOE_CONF_DLR:DLR_CTRL.BCN_CHK_SEQ_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_CTRL.ADV_CHK_SEQ_ENA-
 * VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU- VOP_DLR:VOE_STAT_DLR:DLR_RX_SEQ.RX_SEQ
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_STICKY . ADV_SEQ_ERR_STICKY
 */
#define  VTSS_F_VOP_DLR_DLR_STICKY_ADV_SEQ_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_DLR_DLR_STICKY_ADV_SEQ_ERR_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_DLR_DLR_STICKY_ADV_SEQ_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Indicates changed Loss of Continuity (LOC) state.
 *
 * \details
 * 0: LOC has not changed state
 * 1: Changed LOC state (ADV_MISS_CNT equals ADV_MAX_MISS_CNT)
 *
 * Field: ::VTSS_VOP_DLR_DLR_STICKY . ADV_LOC_STICKY
 */
#define  VTSS_F_VOP_DLR_DLR_STICKY_ADV_LOC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_DLR_DLR_STICKY_ADV_LOC_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_DLR_DLR_STICKY_ADV_LOC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates changed Loss of Continuity (LOC) state.
 *
 * \details
 * 0: LOC has not changed state
 * 1: Changed LOC state (MISS_CNT equals MAX_MISS_CNT)
 *
 * Field: ::VTSS_VOP_DLR_DLR_STICKY . BCN_LOC_STICKY
 */
#define  VTSS_F_VOP_DLR_DLR_STICKY_BCN_LOC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_DLR_DLR_STICKY_BCN_LOC_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_DLR_DLR_STICKY_BCN_LOC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief DLR interrupts
 *
 * \details
 * DLR interrupts
 *
 * Register: \a VOP_DLR:VOE_STAT_DLR:DLR_INTR_ENA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_DLR_DLR_INTR_ENA(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_DLR,0x400,gi,16,0,14)

/**
 * \brief
 * Configures interrupt based on ADV_LOC_STICKY.
 *
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_INTR_ENA . ADV_LOC_INTR_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_INTR_ENA_ADV_LOC_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_DLR_DLR_INTR_ENA_ADV_LOC_INTR_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_DLR_DLR_INTR_ENA_ADV_LOC_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_DLR_DLR_INTR_ENA . BCN_LOC_INTR_ENA
 */
#define  VTSS_F_VOP_DLR_DLR_INTR_ENA_BCN_LOC_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_DLR_DLR_INTR_ENA_BCN_LOC_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_DLR_DLR_INTR_ENA_BCN_LOC_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_LAGUNA_REGS_VOP_DLR_H_ */
