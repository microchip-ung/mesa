// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_VOP_MRP_H_
#define _VTSS_LAGUNA_REGS_VOP_MRP_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a VOP_MRP
 *
 * The OAM MEP Processor block implements the HW support for Versatile OAM
 * Endpoints (VOE), MRP endpoints, and DLR endpoints.
 *
 ***********************************************************************/

/**
 * Register Group: \a VOP_MRP:VOE_CONF_MRP
 *
 * Media Redundancy Protocol endpoint
 */


/**
 * \brief VOE configuration common between VOE types
 *
 * \details
 * This register is identical in VOE_CONF, VOE_CONF_MPLS, and VOE_CONF_L3.
 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:VOE_COMMON_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_VOE_COMMON_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,0)

/**
 * \brief
 * Configures VOE for Down-MEP or Up-MEP operation.Note:Port VOEs only
 * support Down-MEP functionality. UPMEP_ENA must be set to 0.L3 VOEs only
 * support Up-MEP functionality. UPMEP_ENA must be set to 1.
 *
 * \details
 * 0: Configure VOE for Down-MEP functionality.
 * 1: Configure VOE for Up-MEP functionality.
 *
 * Field: ::VTSS_VOP_MRP_VOE_COMMON_CFG . UPMEP_ENA
 */
#define  VTSS_F_VOP_MRP_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_MRP_VOE_COMMON_CFG_UPMEP_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_MRP_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

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
 * Field: ::VTSS_VOP_MRP_VOE_COMMON_CFG . VOE_IS_PATH
 */
#define  VTSS_F_VOP_MRP_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_MRP_VOE_COMMON_CFG_VOE_IS_PATH  VTSS_BIT(12)
#define  VTSS_X_VOP_MRP_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

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
 * Field: ::VTSS_VOP_MRP_VOE_COMMON_CFG . PATH_VOE_ENA
 */
#define  VTSS_F_VOP_MRP_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_MRP_VOE_COMMON_CFG_PATH_VOE_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_MRP_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Assigns a Path VOE to the VOE. See description in PATH_VOE_ENA.Must
 * point to a VOE in the pool of Service VOEs (0 - 7).
 *
 * \details
 * Field: ::VTSS_VOP_MRP_VOE_COMMON_CFG . PATH_VOEID
 */
#define  VTSS_F_VOP_MRP_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_VOP_MRP_VOE_COMMON_CFG_PATH_VOEID     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_VOP_MRP_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * If ESDX counter control is enabled, the VOP will signal disabling of
 * ESDX counting to the REW for OAM frames.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_VOE_COMMON_CFG . ESDX_CNT_CTRL_ENA
 */
#define  VTSS_F_VOP_MRP_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MRP_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_MRP_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configures miscellaneous parameters
 *
 * \details
 * Basic MRP configuration.
 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:MRP_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_MRP_CTRL(gi)            VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,1)

/**
 * \brief
 * If set, the MRP_InTest frame's MRP_SequenceID is checked against the
 * expected sequence identifier and frames for which the sequenceID does
 * not match the expected value are forwarded using ERR_FWD_SEL. For frames
 * failing the check,
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.ITST_RX_SEQ_ERR_STICKY is set. The
 * expected value is calculated as
 * VOP_MRP:VOE_STAT_MRP:MRP_RX_SEQ_CFG[1]+1. The frame's MRP_SequenceID is
 * stored in VOP_MRP:VOE_STAT_MRP:MRP_RX_SEQ_CFG[1] as the latest valid
 * sequence identifier.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.TST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.ITST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU- VOP_MRP:VOE_CONF_MRP:MRP_RX_SEQ_CFG-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.RX_SEQ_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . ITST_CHK_SEQ_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_ITST_CHK_SEQ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_MRP_MRP_CTRL_ITST_CHK_SEQ_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_MRP_MRP_CTRL_ITST_CHK_SEQ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * If set, the MRP_Test frame's MRP_SequenceID is checked against the
 * expected sequence identifier and frames for which the sequenceID does
 * not match the expected value are forwarded using ERR_FWD_SEL. For frames
 * failing the check, VOP_MRP:VOE_STAT_MRP:MRP_STICKY.RX_SEQ_ERR_STICKY is
 * set. The expected value is calculated as
 * VOP_MRP:VOE_CONF_MRP:MRP_RX_SEQ_CFG[0]+1. The frame's MRP_SequenceID is
 * stored in VOP_MRP:VOE_CONF_MRP:MRP_RX_SEQ_CFG[0] as the latest valid
 * sequence identifier.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.TST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.ITST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU- VOP_MRP:VOE_CONF_MRP:MRP_RX_SEQ_CFG-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.RX_SEQ_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . TST_CHK_SEQ_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_TST_CHK_SEQ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_MRP_MRP_CTRL_TST_CHK_SEQ_ENA  VTSS_BIT(10)
#define  VTSS_X_VOP_MRP_MRP_CTRL_TST_CHK_SEQ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * If set, the DMACs of MRP frames are checked against MRP_Type.DMAC =
 * MC_TEST: Used by MRP_Test, MRP_TestMgrNAck and MRP_TestPropagate
 * frames.DMAC = MC_CONTROL: Used by MRP_LinkChange, MRP_TopologyChange and
 * MRP_Option frames.DMAC = MC_INTEST: Used by MRP_InTest frames.DMAC =
 * MC_INCONTROL: Used by MRP_InLinkChange, MRP_InTopologyChange and
 * MRP_InLinkStatusPoll frames.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.CHK_DMAC_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.ALLOW_MRP_OUIS_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.DMAC_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . CHK_DMAC_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_CHK_DMAC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_MRP_MRP_CTRL_CHK_DMAC_ENA  VTSS_BIT(9)
#define  VTSS_X_VOP_MRP_MRP_CTRL_CHK_DMAC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * By default, the MRP OUI must be 01-15-4E. If ALLOW_MRP_OUIS_ENA is set,
 * the MRP OUI check allows the following 4 OUIs:- 00-15-4E- 01-15-4E-
 * 02-15-4E- 03-15-4ERelated parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.CHK_DMAC_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.ALLOW_MRP_OUIS_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.DMAC_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . ALLOW_MRP_OUIS_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_ALLOW_MRP_OUIS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_MRP_MRP_CTRL_ALLOW_MRP_OUIS_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_MRP_MRP_CTRL_ALLOW_MRP_OUIS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * If set, the MRP frame's MRP_Version must be according to
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.MRP_VERSION.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.CHK_VERSION_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.MRP_VERSION-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.VERSION_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . CHK_VERSION_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_CHK_VERSION_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_MRP_MRP_CTRL_CHK_VERSION_ENA  VTSS_BIT(7)
#define  VTSS_X_VOP_MRP_MRP_CTRL_CHK_VERSION_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * The 4 least significant bits of the expected MRP_Version. The most
 * significant bits are set to 0.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.CHK_VERSION_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.MRP_VERSION-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.VERSION_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . MRP_VERSION
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_MRP_VERSION(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_VOP_MRP_MRP_CTRL_MRP_VERSION     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_VOP_MRP_MRP_CTRL_MRP_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/**
 * \brief
 * If set, MRP_Test frames are checked by the MRP endpoint and valid
 * MRP_Test frames clear the associated MRP_MISS_CNT. If cleared, MRP_Test
 * frames are forwarded using MRP_FWD_CTRL but detailed processing and LOC
 * checking is disabled.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . MRP_TST_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_MRP_TST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MRP_MRP_CTRL_MRP_TST_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_MRP_MRP_CTRL_MRP_TST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If set, MRP_InTest frames are checked by the MRP endpoint and valid
 * MRP_InTest frames clear the associated MRP_MISS_CNT. If cleared,
 * MRP_InTest frames are forwarded using MRP_FWD_CTRL but detailed
 * processing and LOC checking is disabled.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . MRP_ITST_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_MRP_ITST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MRP_MRP_CTRL_MRP_ITST_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_MRP_MRP_CTRL_MRP_ITST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Configures whether the MRP endpoint is active.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_CTRL . MRP_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_CTRL_MRP_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MRP_MRP_CTRL_MRP_ENA      VTSS_BIT(0)
#define  VTSS_X_VOP_MRP_MRP_CTRL_MRP_ENA(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Forward selection for various MRP PDUs
 *
 * \details
 * Forward selection for various MRP PDUs, all using the following
 * encoding:
 * 0: No changes to forwarding (NOP)
 * 1: Copy frame to CPU (COPY)
 * 2: Redirect frame to CPU (REDIR)
 * 3: Discard frame (DISC)
 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_MRP_FWD_CTRL(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,2)

/**
 * \brief
 * If set, MRP Interconnection frames (MRP_InTest, MRP_InLinkChange,
 * MRP_InTopologyChange, MRP_InLinkStatusPoll) are forwarded using
 * VOP_MRP:VOE_CONF_MRP:ICON_MASK_CFG. Note, FWD_SEL is also applied and
 * the port mask is not applied when the frame is redirected or discarded.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . ICON_MASK_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_ICON_MASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_ICON_MASK_ENA  VTSS_BIT(25)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_ICON_MASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * If set, MRP ring frames (MRP_Test, MRP_LinkChange, MRP_TopologyChange,
 * MRP_Option) are forwarded using VOP_MRP:VOE_CONF_MRP:RING_MASK_CFG.
 * Note, FWD_SEL is also applied and the port mask is not applied when the
 * frame is redirected or discarded.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . RING_MASK_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_RING_MASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_RING_MASK_ENA  VTSS_BIT(24)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_RING_MASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Forward selection for MRP frames failing one of the optional PDU
 * checks:- MRP Version- MRP DMAC - MRP SequenceIDRelated paramenters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.TST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.ITST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.CHK_VERSION_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.CHK_DMAC_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU- VOP_MRP:VOE_STAT_MRP:MRP_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . ERR_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_ERR_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_ERR_FWD_SEL     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_ERR_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/**
 * \brief
 * Forward selection for MRP_Test frames. The CPU queue is configured in
 * VOP::CPU_EXTR_MRP.MRP_TST_CPU_QU. Only applicable when hardware
 * processing of MRP_Test frames is disabled
 * (VOP_MRP:VOE_CONF_MRP:MRP_CTRL.MRP_TST_ENA). When hardware processing of
 * MRP_Test frames is enabled, setting MRP_TST_FWD_SEL > 0 triggers a CPU
 * copy after the hardware processing is done. Effectively, a NOP is
 * changed to a COPY and a DISC is changed to a REDIR. The CPU queue is set
 * to MRP_CPU_CFG.MRP_TST_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_TST_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_TST_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_TST_FWD_SEL     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_TST_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * Forward selection for MRP_TestPropagate and MRP_TestMgrNAck frames. The
 * CPU queue is configured in VOP::CPU_EXTR_MRP.MRP_TST_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_TPM_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_TPM_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_TPM_FWD_SEL     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_TPM_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * Forward selection for MRP_LinkDown frames. The CPU queue is configured
 * in VOP::CPU_EXTR_MRP.MRP_CTRL_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_LD_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_LD_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_LD_FWD_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_LD_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Forward selection for MRP_LinkUp frames. The CPU queue is configured in
 * VOP::CPU_EXTR_MRP.MRP_CTRL_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_LU_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_LU_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_LU_FWD_SEL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_LU_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * Forward selection for MRP_TopologyChange frames. The CPU queue is
 * configured in VOP::CPU_EXTR_MRP.MRP_CTRL_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_TC_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_TC_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_TC_FWD_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_TC_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * Forward selection for MRP_InTest. The CPU queue is configured in
 * VOP::CPU_EXTR_MRP.MRP_ITST_CPU_QU.When hardware processing of MRP_InTest
 * frames is enabled, setting MRP_ITST_FWD_SEL > 0 triggers a CPU copy
 * after the hardware processing is done. Effectively, a NOP is changed to
 * a COPY and a DISC is changed to a REDIR. The CPU queue is set to
 * MRP_CPU_CFG.MRP_ITST_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_ITST_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ITST_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ITST_FWD_SEL     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_ITST_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * Forward selection for MRP_InTopologyChange frames. The CPU queue is
 * configured in VOP::CPU_EXTR_MRP.MRP_ICTRL_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_ITC_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ITC_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ITC_FWD_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_ITC_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Forward selection for MRP_InLinkDown frames. The CPU queue is configured
 * in VOP::CPU_EXTR_MRP.MRP_ICTRL_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_ILD_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ILD_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ILD_FWD_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_ILD_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Forward selection for MRP_InLinkUp frames. The CPU queue is configured
 * in VOP::CPU_EXTR_MRP.MRP_ICTRL_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_ILU_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ILU_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ILU_FWD_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_ILU_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Forward selection for MRP_InLinkStatusPoll frames. The CPU queue is
 * configured in VOP::CPU_EXTR_MRP.MRP_ICTRL_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . MRP_ILSP_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_MRP_ILSP_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_MRP_ILSP_FWD_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_MRP_ILSP_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Forward selection for MRP frames not covered by other selections. The
 * CPU queue is configured in VOP::CPU_EXTR_MRP.MRP_OTHER_CPU_QU.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_FWD_CTRL . OTHER_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_MRP_FWD_CTRL_OTHER_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_MRP_MRP_FWD_CTRL_OTHER_FWD_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_MRP_MRP_FWD_CTRL_OTHER_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Port mask for MRP ring frames
 *
 * \details
 * Register: \a VOP_MRP:VOE_CONF_MRP:RING_MASK_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_RING_MASK_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,3)

/**
 * \brief
 * Port mask used when VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.RING_MASK_ENA is
 * set.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_RING_MASK_CFG . RING_PORTMASK
 */
#define  VTSS_F_VOP_MRP_RING_MASK_CFG_RING_PORTMASK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_VOP_MRP_RING_MASK_CFG_RING_PORTMASK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_VOP_MRP_RING_MASK_CFG_RING_PORTMASK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Port mask for MRP interconnection frames
 *
 * \details
 * Register: \a VOP_MRP:VOE_CONF_MRP:ICON_MASK_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ICON_MASK_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,4)

/**
 * \brief
 * Port mask used when VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ICON_MASK_ENA is
 * set.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_ICON_MASK_CFG . ICON_PORTMASK
 */
#define  VTSS_F_VOP_MRP_ICON_MASK_CFG_ICON_PORTMASK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_VOP_MRP_ICON_MASK_CFG_ICON_PORTMASK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_VOP_MRP_ICON_MASK_CFG_ICON_PORTMASK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Configuration of MRP_Test forward handling
 *
 * \details
 * Forward selection for MRP_Test frames when hardware processing is
 * enabled, all using the following encoding:
 * 0: No changes to forwarding (NOP)
 * 1: Copy frame to CPU (COPY)
 * 2: Redirect frame to CPU (REDIR)
 * 3: Discard frame (DISC)
 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_FWD_CTRL(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,5)

/**
 * \brief
 * Forward selection for MRP_Test frames for which the frame's priority is
 * better than MRP endpoint's own priority.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:TST_CFG.CHK_REM_PRIO_ENA-
 * VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.HI_PRIO_FWD_SEL-
 * VOP::CPU_EXTR_MRP.REM_CPU_QU-
 * VOP_MRP:VOE_CONF_MRP:TST_PRIO_CFG.OWN_PRIO-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_FWD_CTRL . HI_PRIO_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_TST_FWD_CTRL_HI_PRIO_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_VOP_MRP_TST_FWD_CTRL_HI_PRIO_FWD_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_VOP_MRP_TST_FWD_CTRL_HI_PRIO_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Forward selection for MRP_Test frames for which the frame's priority is
 * worse than MRP endpoint's own priority.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:TST_CFG.CHK_REM_PRIO_ENA-
 * VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.LO_PRIO_FWD_SEL-
 * VOP::CPU_EXTR_MRP.REM_CPU_QU-
 * VOP_MRP:VOE_CONF_MRP:TST_PRIO_CFG.OWN_PRIO-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_FWD_CTRL . LO_PRIO_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_TST_FWD_CTRL_LO_PRIO_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_MRP_TST_FWD_CTRL_LO_PRIO_FWD_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_MRP_TST_FWD_CTRL_LO_PRIO_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Default forward selection for MRP_Test frames from a remote MRP (MRP_SA
 * does not match MRP_MAC). The CPU queue is configured in
 * MRP_CPU_CFG.REM_CPU_QU. More filters may be applied to further process
 * the MRP_Test frame, see TST_CFG.CHK_REM_PRIO_ENA and
 * TST_CFG.CHK_BEST_MRM_ENA.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.REM_FWD_SEL-
 * VOP::CPU_EXTR_MRP.REM_CPU_QU-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_FWD_CTRL . REM_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_TST_FWD_CTRL_REM_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VOP_MRP_TST_FWD_CTRL_REM_FWD_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VOP_MRP_TST_FWD_CTRL_REM_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Forward selection for MRP_Test frames for which MRP_SA matches MRP_MAC.
 * The CPU queue is configured in MRP_CPU_CFG.OWN_CPU_QU.Related
 * parameters:- VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.OWN_FWD_SEL-
 * VOP::CPU_EXTR_MRP.OWN_CPU_QU-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_FWD_CTRL . OWN_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_TST_FWD_CTRL_OWN_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_MRP_TST_FWD_CTRL_OWN_FWD_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_MRP_TST_FWD_CTRL_OWN_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Configuration of MRP_Test handling
 *
 * \details
 * Processing of valid MRP_Test frames:
 * 1) When frame's MRP_SA matches MRP_MAC:
 * - Use OWN_FWD_SEL for forwarding. Clear MISS_CNT when CLR_MISS_CNT_ENA
 * is set.
 *
 * 2) When frame's MRP_SA does not match MRP_MAC:
 *
 * 2a) When CHK_REM_PRIO_ENA is cleared:
 * - Use REM_FWD_SEL as forwarding.
 *
 * 2b) When CHK_REM_PRIO_ENA is set and CHK_BEST_MRM_ENA is cleared:
 * - Use REM_FWD_SEL as default forwarding.
 * - Use LO_PRIO_FWD_SEL when frame's priority is worse.
 *
 * 2c) When both CHK_REM_PRIO_ENA and CHK_BEST_MRM_ENA are set:
 * - Use REM_FWD_SEL as default forwarding.
 * - Use LO_PRIO_FWD_SEL when frame's priority is worse. Store frame's
 * priority if SAMPLE_LO_ENA is set.
 * - Use HI_PRIO_FWD_SEL when frame's priority is better and frame's MRP_SA
 * matches BEST_MAC. Store frame's priority if SAMPLE_LO_ENA is set. Clear
 * MISS_CNT when CLR_MISS_CNT_ENA is set.
 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:TST_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_CFG(gi)             VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,6)

/**
 * \brief
 * If set, the TST_PRIO_CFG.BEST_PRIO is updated with the frame's MRP_PRIO
 * for valid MRP_Test frames when the frame's priority is worse than MRP
 * endpoint's own priority.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_CFG . SAMPLE_LO_PRIO_ENA
 */
#define  VTSS_F_VOP_MRP_TST_CFG_SAMPLE_LO_PRIO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_MRP_TST_CFG_SAMPLE_LO_PRIO_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_MRP_TST_CFG_SAMPLE_LO_PRIO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * If set, the TST_PRIO_CFG.BEST_PRIO is updated with the frame's MRP_PRIO
 * for valid MRP_Test frames when the frame's priority is better than MRP
 * endpoint's own priority.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_CFG . SAMPLE_HI_PRIO_ENA
 */
#define  VTSS_F_VOP_MRP_TST_CFG_SAMPLE_HI_PRIO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_MRP_TST_CFG_SAMPLE_HI_PRIO_ENA  VTSS_BIT(7)
#define  VTSS_X_VOP_MRP_TST_CFG_SAMPLE_HI_PRIO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * If set, the priority of MRP_Test frames from a remote MRM is checked
 * against the MRP endpoint's own priority.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:TST_CFG.CHK_REM_PRIO_ENA-
 * VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.LO_PRIO_FWD_SEL-
 * VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.HI_PRIO_FWD_SEL-
 * VOP::CPU_EXTR_MRP.REM_CPU_QU-
 * VOP_MRP:VOE_CONF_MRP:TST_PRIO_CFG.OWN_PRIO-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_CFG . CHK_REM_PRIO_ENA
 */
#define  VTSS_F_VOP_MRP_TST_CFG_CHK_REM_PRIO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_MRP_TST_CFG_CHK_REM_PRIO_ENA  VTSS_BIT(6)
#define  VTSS_X_VOP_MRP_TST_CFG_CHK_REM_PRIO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * If set, the MRP_Test frame's MRP_SA is checked against the best MRP_SA
 * known by the endpoint.Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:TST_CFG.CHK_BEST_MRM_ENA-
 * VOP::CPU_EXTR_MRP.REM_CPU_QU-
 * VOP_MRP:VOE_CONF_MRP:BEST_MAC_LSB.BEST_MAC_LSB-
 * VOP_MRP:VOE_CONF_MRP:BEST_MAC_MSB.BEST_MAC_MSB
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_CFG . CHK_BEST_MRM_ENA
 */
#define  VTSS_F_VOP_MRP_TST_CFG_CHK_BEST_MRM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_MRP_TST_CFG_CHK_BEST_MRM_ENA  VTSS_BIT(5)
#define  VTSS_X_VOP_MRP_TST_CFG_CHK_BEST_MRM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If set, valid MRP_Test frames clear the MRP_MISS_CNT.For an MRM, a valid
 * MRP_Test frame is from the MRP endpoint itself.For an MRA in MRC role, a
 * valid MRP_Test frame is from the current best MRM.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_CFG . CLR_MISS_CNT_ENA
 */
#define  VTSS_F_VOP_MRP_TST_CFG_CLR_MISS_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_MRP_TST_CFG_CLR_MISS_CNT_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_MRP_TST_CFG_CLR_MISS_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * LOC period used by endpoint. Related parameters:- VOP::LOC_PERIOD_CFG
 *
 * \details
 * 0: No LOC period in use.
 * n>0: LOC period configured in VOP::LOC_PERIOD_CFG[n-1] in use.
 *
 * Field: ::VTSS_VOP_MRP_TST_CFG . LOC_PERIOD
 */
#define  VTSS_F_VOP_MRP_TST_CFG_LOC_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_MRP_TST_CFG_LOC_PERIOD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_MRP_TST_CFG_LOC_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief MRP priority configuration
 *
 * \details
 * Register: \a VOP_MRP:VOE_CONF_MRP:TST_PRIO_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_PRIO_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,7)

/**
 * \brief
 * MRP endpoint's priority.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_PRIO_CFG . OWN_PRIO
 */
#define  VTSS_F_VOP_MRP_TST_PRIO_CFG_OWN_PRIO(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_MRP_TST_PRIO_CFG_OWN_PRIO     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_MRP_TST_PRIO_CFG_OWN_PRIO(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configuration of MRP_InTest forward handling
 *
 * \details
 * Forward selection for MRP_InTest frames when hardware processing is
 * enabled.
 * 0: No changes to forwarding (NOP)
 * 1: Copy frame to CPU (COPY)
 * 2: Redirect frame to CPU (REDIR)
 * 3: Discard frame (DISC)
 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:ITST_FWD_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_FWD_CTRL(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,8)

/**
 * \brief
 * Forward selection for MRP_InTest frames from a remote MIM (MRP_SA does
 * not match MRP_MAC). The CPU queue is configured in
 * MRP_CPU_CFG.REM_CPU_QU. The RING_PORTMASK may be applied when no changes
 * to forwarding or frame is copied to the CPU. Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:ITST_FWD_CTRL.ITST_REM_FWD_SEL-
 * VOP::CPU_EXTR_MRP.REM_CPU_QU-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * \details
 * 0: No changes to forwarding (NOP)
 * 1: Copy frame to CPU (COPY)
 * 2: Redirect frame to CPU (REDIR)
 * 3: Discard frame (DISC)
 *
 * Field: ::VTSS_VOP_MRP_ITST_FWD_CTRL . ITST_REM_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_ITST_FWD_CTRL_ITST_REM_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VOP_MRP_ITST_FWD_CTRL_ITST_REM_FWD_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VOP_MRP_ITST_FWD_CTRL_ITST_REM_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Forward selection for MRP_InTest frames for which MRP_SA matches
 * MRP_MAC. The CPU queue is configured in MRP_CPU_CFG.OWN_CPU_QU.Related
 * parameters:- VOP_MRP:VOE_CONF_MRP:ITST_FWD_CTRL.ITST_OWN_FWD_SEL-
 * VOP::CPU_EXTR_MRP.OWN_CPU_QU-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB-
 * VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * \details
 * 0: No changes to forwarding (NOP)
 * 1: Copy frame to CPU (COPY)
 * 2: Redirect frame to CPU (REDIR)
 * 3: Discard frame (DISC)
 *
 * Field: ::VTSS_VOP_MRP_ITST_FWD_CTRL . ITST_OWN_FWD_SEL
 */
#define  VTSS_F_VOP_MRP_ITST_FWD_CTRL_ITST_OWN_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_MRP_ITST_FWD_CTRL_ITST_OWN_FWD_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_MRP_ITST_FWD_CTRL_ITST_OWN_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Configuration of MRP_InTest handling
 *
 * \details
 * Processing of valid MRP_InTest frames:
 * 1) When frame's MRP_SA matches MRP_MAC:
 * - Use ITST_FWD_CTRL.ITST_OWN_FWD_SEL for forwarding. Clear ITST_MISS_CNT
 * when ITST_CLR_MISS_CNT_ENA is set.
 *
 * 2) When frame's MRP_SA does not match MRP_MAC:
 * - Use ITST_FWD_CTRL.ITST_REM_FWD_SEL for forwarding.

 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:ITST_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,9)

/**
 * \brief
 * If set, valid MRP_InTest frames clear the MRP_MISS_CNT.For an MIM, a
 * valid MRP_InTest frame is from the MRP endpoint itself.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_ITST_CFG . ITST_CLR_MISS_CNT_ENA
 */
#define  VTSS_F_VOP_MRP_ITST_CFG_ITST_CLR_MISS_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_MRP_ITST_CFG_ITST_CLR_MISS_CNT_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_MRP_ITST_CFG_ITST_CLR_MISS_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * LOC period used by endpoint. Related parameters:- VOP::LOC_PERIOD_CFG
 *
 * \details
 * 0: No LOC period in use.
 * n>0: LOC period configured in VOP::LOC_PERIOD_CFG[n-1] in use.
 *
 * Field: ::VTSS_VOP_MRP_ITST_CFG . ITST_LOC_PERIOD
 */
#define  VTSS_F_VOP_MRP_ITST_CFG_ITST_LOC_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_MRP_ITST_CFG_ITST_LOC_PERIOD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_MRP_ITST_CFG_ITST_LOC_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief MRP endpoint's MAC address configuration (LSB)
 *
 * \details
 * Related parameters:
 * - VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.OWN_FWD_SEL
 * - VOP::CPU_EXTR_MRP.OWN_CPU_QU
 * - VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB
 * - VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_MRP_MAC_LSB(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,10)

/**
 * \brief
 * MRP endpoint's MAC address
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_MAC_LSB . MRP_MAC_LSB
 */
#define  VTSS_F_VOP_MRP_MRP_MAC_LSB_MRP_MAC_LSB(x)  (x)
#define  VTSS_M_VOP_MRP_MRP_MAC_LSB_MRP_MAC_LSB     0xffffffff
#define  VTSS_X_VOP_MRP_MRP_MAC_LSB_MRP_MAC_LSB(x)  (x)


/**
 * \brief MRP endpoint's MAC address configuration (MSB)
 *
 * \details
 * Related parameters:
 * - VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.OWN_FWD_SEL
 * - VOP::CPU_EXTR_MRP.OWN_CPU_QU
 * - VOP_MRP:VOE_CONF_MRP:MRP_MAC_LSB.MRP_MAC_LSB
 * - VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB.MRP_MAC_MSB
 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:MRP_MAC_MSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_MRP_MAC_MSB(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,11)

/**
 * \brief
 * MRP endpoint's MAC address
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_MAC_MSB . MRP_MAC_MSB
 */
#define  VTSS_F_VOP_MRP_MRP_MAC_MSB_MRP_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_MRP_MRP_MAC_MSB_MRP_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_MRP_MRP_MAC_MSB_MRP_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Best MRM's MAC address configuration (LSB)
 *
 * \details
 * Register: \a VOP_MRP:VOE_CONF_MRP:BEST_MAC_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_BEST_MAC_LSB(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,12)

/**
 * \brief
 * Best MRM MAC address
 *
 * \details
 * Field: ::VTSS_VOP_MRP_BEST_MAC_LSB . BEST_MAC_LSB
 */
#define  VTSS_F_VOP_MRP_BEST_MAC_LSB_BEST_MAC_LSB(x)  (x)
#define  VTSS_M_VOP_MRP_BEST_MAC_LSB_BEST_MAC_LSB     0xffffffff
#define  VTSS_X_VOP_MRP_BEST_MAC_LSB_BEST_MAC_LSB(x)  (x)


/**
 * \brief Best MRM's MAC address configuration (MSB)
 *
 * \details
 * Register: \a VOP_MRP:VOE_CONF_MRP:BEST_MAC_MSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_BEST_MAC_MSB(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,0,13)

/**
 * \brief
 * Best MRM MAC address
 *
 * \details
 * Field: ::VTSS_VOP_MRP_BEST_MAC_MSB . BEST_MAC_MSB
 */
#define  VTSS_F_VOP_MRP_BEST_MAC_MSB_BEST_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_MRP_BEST_MAC_MSB_BEST_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_MRP_BEST_MAC_MSB_BEST_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief MRP_Test and MRP_InTest Tx configuration
 *
 * \details
 * Configuration for MRP_Test and MRP_InTest Tx frame handling.
 * Index 0: Configuration applies to MRP_Test frames.
 * Index 1: Configuration applies to MRP_InTest frames.
 *
 * To use the configuration, IFH field REW_OAM must be set and IFH field
 * OAM_TYPE must be set to MRP PDU type.

 *
 * Register: \a VOP_MRP:VOE_CONF_MRP:MRP_TX_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 * @param ri Register: MRP_TX_CFG (??), 0-1
 */
#define VTSS_VOP_MRP_MRP_TX_CFG(gi,ri)       VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x800,gi,16,ri,14)

/**
 * \brief
 * If set, the time stamps in MRP_Test/MRP_InTest frames transmitted on
 * this port are updated with the value in MRP_TX_TS_CFG.MRP_TX_TS.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_TX_CFG . MRP_TIMESTAMP_UPD_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_TIMESTAMP_UPD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_TIMESTAMP_UPD_ENA  VTSS_BIT(22)
#define  VTSS_X_VOP_MRP_MRP_TX_CFG_MRP_TIMESTAMP_UPD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * If set, the sequence numbers in MRP_Test/MRP_InTest frames transmitted
 * on this port are updated with the value in PTP_SEQ_NO selected by
 * frame's IFH field SEQ_NUM. The sequence number is auto-incremented after
 * use.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_TX_CFG . MRP_SEQ_UPD_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_SEQ_UPD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_SEQ_UPD_ENA  VTSS_BIT(21)
#define  VTSS_X_VOP_MRP_MRP_TX_CFG_MRP_SEQ_UPD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * If set, the transistion number, portrole, and ringstate/instate in
 * MRP_Test/MRP_InTest frames transmitted on this port are updated with the
 * values in MRP_TX_CFG.MRP_TRANS, MRP_TX_CFG.MRP_PORTROLE, and
 * MRP_TX_CFG.MRP_STATE.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_TX_CFG . MRP_MISC_UPD_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_MISC_UPD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_MISC_UPD_ENA  VTSS_BIT(20)
#define  VTSS_X_VOP_MRP_MRP_TX_CFG_MRP_MISC_UPD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Configures least significant bits for the ring or in state to be
 * transmitted in the next MRP_Test/MRP_InTest frame. Other bits in the
 * state are set to 0. Used when MRP_TX_CFG.MRP_MISC_UPD_ENA is set.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_TX_CFG . MRP_STATE
 */
#define  VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_STATE(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_STATE     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_VOP_MRP_MRP_TX_CFG_MRP_STATE(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * Configures least significant bits for the port role to be transmitted in
 * the next MRP_Test/MRP_InTest frame. Other bits in the state are set to
 * 0. Used when MRP_TX_CFG.MRP_MISC_UPD_ENA is set.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_TX_CFG . MRP_PORTROLE
 */
#define  VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_PORTROLE(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_PORTROLE     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_VOP_MRP_MRP_TX_CFG_MRP_PORTROLE(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Configures the transistion to be transmitted in the next
 * MRP_Test/MRP_InTest frame. Used when MRP_TX_CFG.MRP_MISC_UPD_ENA is set.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_TX_CFG . MRP_TRANS
 */
#define  VTSS_F_VOP_MRP_MRP_TX_CFG_MRP_TRANS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_MRP_MRP_TX_CFG_MRP_TRANS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_MRP_MRP_TX_CFG_MRP_TRANS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VOP_MRP:VOE_STAT_MRP
 *
 * Not documented
 */


/**
 * \brief Counts number of received valid MRP_Test frames subject to MRP_Test processing
 *
 * \details
 * Counts number of received valid MRP_Test PDUs that are subject to
 * MRP_Test processing.
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:TST_RX_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_RX_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,0)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_RX_CNT . TST_RX_CNT
 */
#define  VTSS_F_VOP_MRP_TST_RX_CNT_TST_RX_CNT(x)  (x)
#define  VTSS_M_VOP_MRP_TST_RX_CNT_TST_RX_CNT     0xffffffff
#define  VTSS_X_VOP_MRP_TST_RX_CNT_TST_RX_CNT(x)  (x)


/**
 * \brief Delta time stamp for valid MRP_Test frames
 *
 * \details
 * Latest delta time stamp for valid MRP_Test frame
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:TST_DELTA_TS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_DELTA_TS(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,1)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_DELTA_TS . TST_DELTA_TS
 */
#define  VTSS_F_VOP_MRP_TST_DELTA_TS_TST_DELTA_TS(x)  (x)
#define  VTSS_M_VOP_MRP_TST_DELTA_TS_TST_DELTA_TS     0xffffffff
#define  VTSS_X_VOP_MRP_TST_DELTA_TS_TST_DELTA_TS(x)  (x)


/**
 * \brief Status of MRP_Test handling
 *
 * \details
 * Register: \a VOP_MRP:VOE_STAT_MRP:TST_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_STAT(gi)            VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,2)

/**
 * \brief
 * Maximum number of miss counts before timeout.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_STAT . MAX_MISS_CNT
 */
#define  VTSS_F_VOP_MRP_TST_STAT_MAX_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VOP_MRP_TST_STAT_MAX_MISS_CNT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VOP_MRP_TST_STAT_MAX_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Specifies the number of MRP retries without MRP_Test frames received
 * from the MRM. Cleared by HW when receiving a valid MRP_Test message.
 *
 * \details
 * n<MAX_MISS_CNT: No Loss of continuity
 * n==MAX_MISS_CNT: Loss of continuity
 *
 * Field: ::VTSS_VOP_MRP_TST_STAT . MISS_CNT
 */
#define  VTSS_F_VOP_MRP_TST_STAT_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_MRP_TST_STAT_MISS_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_MRP_TST_STAT_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Configuration of MRP_Test hit me once
 *
 * \details
 * Register: \a VOP_MRP:VOE_STAT_MRP:NXT_LOC_HMO
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_NXT_LOC_HMO(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,3)

/**
 * \brief
 * Extract next MRP_Test PDU frame subject to clearing the LOC miss counter
 * to CPU according to configuration in VOP::CPU_EXTR_MRP.OWN_CPU_QU or
 * VOP::CPU_EXTR_MRP.REM_CPU_QU.
 *
 * \details
 * 0: Disable (no CPU hitme once copy)
 * 1: Enable the next frame to be sent to CPU.
 *
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_VOP_MRP_NXT_LOC_HMO . NXT_LOC_CPU_HITME_ONCE
 */
#define  VTSS_F_VOP_MRP_NXT_LOC_HMO_NXT_LOC_CPU_HITME_ONCE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MRP_NXT_LOC_HMO_NXT_LOC_CPU_HITME_ONCE  VTSS_BIT(0)
#define  VTSS_X_VOP_MRP_NXT_LOC_HMO_NXT_LOC_CPU_HITME_ONCE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MRP priority status
 *
 * \details
 * Register: \a VOP_MRP:VOE_STAT_MRP:TST_PRIO_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_PRIO_STAT(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,4)

/**
 * \brief
 * Best known priority.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_PRIO_STAT . BEST_PRIO
 */
#define  VTSS_F_VOP_MRP_TST_PRIO_STAT_BEST_PRIO(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_MRP_TST_PRIO_STAT_BEST_PRIO     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_MRP_TST_PRIO_STAT_BEST_PRIO(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Status of MRP_InTest handling
 *
 * \details
 * Register: \a VOP_MRP:VOE_STAT_MRP:ITST_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_STAT(gi)           VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,5)

/**
 * \brief
 * Maximum number of miss counts before timeout.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_ITST_STAT . ITST_MAX_MISS_CNT
 */
#define  VTSS_F_VOP_MRP_ITST_STAT_ITST_MAX_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VOP_MRP_ITST_STAT_ITST_MAX_MISS_CNT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VOP_MRP_ITST_STAT_ITST_MAX_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Specifies the number of MRP retries without MRP_InTest frames received
 * from the MIM. Cleared by HW when receiving a valid MRP_InTest message.
 *
 * \details
 * n<ITST_MAX_MISS_CNT: No Loss of continuity
 * n==ITST_MAX_MISS_CNT: Loss of continuity
 *
 * Field: ::VTSS_VOP_MRP_ITST_STAT . ITST_MISS_CNT
 */
#define  VTSS_F_VOP_MRP_ITST_STAT_ITST_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VOP_MRP_ITST_STAT_ITST_MISS_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VOP_MRP_ITST_STAT_ITST_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Configuration of MRP_InTest hit me once
 *
 * \details
 * Register: \a VOP_MRP:VOE_STAT_MRP:ITST_NXT_LOC_HMO
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_NXT_LOC_HMO(gi)    VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,6)

/**
 * \brief
 * Extract next MRP_InTest PDU frame subject to clearing the LOC miss
 * counter to CPU according to configuration in
 * VOP::CPU_EXTR_MRP.OWN_CPU_QU.
 *
 * \details
 * 0: Disable (no CPU hitme once copy)
 * 1: Enable the next frame to be sent to CPU.
 *
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_VOP_MRP_ITST_NXT_LOC_HMO . ITST_NXT_LOC_CPU_HITME_ONCE
 */
#define  VTSS_F_VOP_MRP_ITST_NXT_LOC_HMO_ITST_NXT_LOC_CPU_HITME_ONCE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MRP_ITST_NXT_LOC_HMO_ITST_NXT_LOC_CPU_HITME_ONCE  VTSS_BIT(0)
#define  VTSS_X_VOP_MRP_ITST_NXT_LOC_HMO_ITST_NXT_LOC_CPU_HITME_ONCE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Counts number of received valid MRP_InTest frames subject to MRP_InTest processing
 *
 * \details
 * Counts number of received valid MRP_InTest PDUs that are subject to
 * MRP_InTest processing.
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:ITST_RX_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_RX_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,7)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_ITST_RX_CNT . ITST_RX_CNT
 */
#define  VTSS_F_VOP_MRP_ITST_RX_CNT_ITST_RX_CNT(x)  (x)
#define  VTSS_M_VOP_MRP_ITST_RX_CNT_ITST_RX_CNT     0xffffffff
#define  VTSS_X_VOP_MRP_ITST_RX_CNT_ITST_RX_CNT(x)  (x)


/**
 * \brief Delta time stamp for valid MRP_InTest frames
 *
 * \details
 * Latest delta time stamp for valid MRP_InTest frame
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:ITST_DELTA_TS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_DELTA_TS(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,8)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_ITST_DELTA_TS . ITST_DELTA_TS
 */
#define  VTSS_F_VOP_MRP_ITST_DELTA_TS_ITST_DELTA_TS(x)  (x)
#define  VTSS_M_VOP_MRP_ITST_DELTA_TS_ITST_DELTA_TS     0xffffffff
#define  VTSS_X_VOP_MRP_ITST_DELTA_TS_ITST_DELTA_TS(x)  (x)


/**
 * \brief MRP sequence identifier
 *
 * \details
 * Configures the expected value of the sequence identifier for the next
 * MRP frame (MRP_SequenceID). The value is after checking set to the value
 * in the incoming frame plus one.
 *
 * Index 0: Configuration applies to MRP_Test frames.
 * Index 1: Configuration applies to MRP_InTest frames.
 *
 * Related parameters:
 * - VOP_MRP:VOE_CONF_MRP:MRP_CTRL.TST_CHK_SEQ_ENA
 * - VOP_MRP:VOE_CONF_MRP:MRP_CTRL.ITST_CHK_SEQ_ENA
 * - VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL
 * - VOP::CPU_EXTR_CFG.CPU_ERR_QU
 * - VOP_MRP:VOE_CONF_MRP:MRP_RX_SEQ_CFG
 * - VOP_MRP:VOE_STAT_MRP:MRP_STICKY.RX_SEQ_ERR_STICKY
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:MRP_RX_SEQ
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 * @param ri Register: MRP_RX_SEQ (??), 0-1
 */
#define VTSS_VOP_MRP_MRP_RX_SEQ(gi,ri)       VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,ri,9)

/**
 * \brief
 * Configuration for MRP_Test and MRP_InTest Rx frame sequence number
 * checker
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_RX_SEQ . RX_SEQ
 */
#define  VTSS_F_VOP_MRP_MRP_RX_SEQ_RX_SEQ(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_MRP_MRP_RX_SEQ_RX_SEQ     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_MRP_MRP_RX_SEQ_RX_SEQ(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief MRP sequence identifier
 *
 * \details
 * Configuration for MRP_Test and MRP_InTest Tx frame sequence number
 * generation
 * Index 0: Configuration applies to MRP_Test frames.
 * Index 1: Configuration applies to MRP_InTest frames.
 *
 * The values are auto updated when MRP_Test and MRP_InTest frames are
 * transmitted.

 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:MRP_TX_SEQ
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 * @param ri Register: MRP_TX_SEQ (??), 0-1
 */
#define VTSS_VOP_MRP_MRP_TX_SEQ(gi,ri)       VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,ri,11)

/**
 * \brief
 * Configures MRP sequence identifiers for TST and ITST frames
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_TX_SEQ . TX_SEQ
 */
#define  VTSS_F_VOP_MRP_MRP_TX_SEQ_TX_SEQ(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_MRP_MRP_TX_SEQ_TX_SEQ     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_MRP_MRP_TX_SEQ_TX_SEQ(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Sticky bits for MRP processing
 *
 * \details
 * Sticky bits for MRP processing
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:MRP_STICKY
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_MRP_STICKY(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,13)

/**
 * \brief
 * Set if MRP frame was received.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_STICKY . MRP_RX_STICKY
 */
#define  VTSS_F_VOP_MRP_MRP_STICKY_MRP_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_MRP_MRP_STICKY_MRP_RX_STICKY  VTSS_BIT(7)
#define  VTSS_X_VOP_MRP_MRP_STICKY_MRP_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set if MRP frame was received and processing is enabled.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_STICKY . MRP_RX_PROC_STICKY
 */
#define  VTSS_F_VOP_MRP_MRP_STICKY_MRP_RX_PROC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_MRP_MRP_STICKY_MRP_RX_PROC_STICKY  VTSS_BIT(6)
#define  VTSS_X_VOP_MRP_MRP_STICKY_MRP_RX_PROC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set if frame with unexpected DMAC was received. Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.CHK_DMAC_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.DMAC_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_STICKY . DMAC_ERR_STICKY
 */
#define  VTSS_F_VOP_MRP_MRP_STICKY_DMAC_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_MRP_MRP_STICKY_DMAC_ERR_STICKY  VTSS_BIT(5)
#define  VTSS_X_VOP_MRP_MRP_STICKY_DMAC_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set if frame with version error was received. Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.CHK_VERSION_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.MRP_VERSION-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.VERSION_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_STICKY . VERSION_ERR_STICKY
 */
#define  VTSS_F_VOP_MRP_MRP_STICKY_VERSION_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_MRP_MRP_STICKY_VERSION_ERR_STICKY  VTSS_BIT(4)
#define  VTSS_X_VOP_MRP_MRP_STICKY_VERSION_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set if TST frame with sequence error was received. Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.TST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.ITST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU- VOP_MRP:VOE_CONF_MRP:MRP_RX_SEQ_CFG-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.RX_SEQ_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_STICKY . TST_RX_SEQ_ERR_STICKY
 */
#define  VTSS_F_VOP_MRP_MRP_STICKY_TST_RX_SEQ_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_MRP_MRP_STICKY_TST_RX_SEQ_ERR_STICKY  VTSS_BIT(3)
#define  VTSS_X_VOP_MRP_MRP_STICKY_TST_RX_SEQ_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if ITST frame with sequence error was received. Related parameters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.TST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_CTRL.ITST_CHK_SEQ_ENA-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.ERR_FWD_SEL-
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU- VOP_MRP:VOE_CONF_MRP:MRP_RX_SEQ_CFG-
 * VOP_MRP:VOE_STAT_MRP:MRP_STICKY.RX_SEQ_ERR_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_STICKY . ITST_RX_SEQ_ERR_STICKY
 */
#define  VTSS_F_VOP_MRP_MRP_STICKY_ITST_RX_SEQ_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MRP_MRP_STICKY_ITST_RX_SEQ_ERR_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_MRP_MRP_STICKY_ITST_RX_SEQ_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Indicates changed Loss of Continuity (LOC) state.
 *
 * \details
 * 0: LOC has not changed state
 * 1: Changed LOC state (ITST_MISS_CNT equals ADV_MAX_MISS_CNT)
 *
 * Field: ::VTSS_VOP_MRP_MRP_STICKY . ITST_LOC_STICKY
 */
#define  VTSS_F_VOP_MRP_MRP_STICKY_ITST_LOC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MRP_MRP_STICKY_ITST_LOC_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_MRP_MRP_STICKY_ITST_LOC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates changed Loss of Continuity (LOC) state.
 *
 * \details
 * 0: LOC has not changed state
 * 1: Changed LOC state (MISS_CNT equals MAX_MISS_CNT)
 *
 * Field: ::VTSS_VOP_MRP_MRP_STICKY . TST_LOC_STICKY
 */
#define  VTSS_F_VOP_MRP_MRP_STICKY_TST_LOC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MRP_MRP_STICKY_TST_LOC_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_MRP_MRP_STICKY_TST_LOC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MRP interrupts
 *
 * \details
 * MRP interrupts
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:MRP_INTR_ENA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_MRP_INTR_ENA(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,14)

/**
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_INTR_ENA . ITST_LOC_INTR_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_INTR_ENA_ITST_LOC_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MRP_MRP_INTR_ENA_ITST_LOC_INTR_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_MRP_MRP_INTR_ENA_ITST_LOC_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_MRP_MRP_INTR_ENA . TST_LOC_INTR_ENA
 */
#define  VTSS_F_VOP_MRP_MRP_INTR_ENA_TST_LOC_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MRP_MRP_INTR_ENA_TST_LOC_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_MRP_MRP_INTR_ENA_TST_LOC_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Counts number of received valid MRP_Test frames that clear the LOC miss counter
 *
 * \details
 * Counts number of received MRP_Test PDUs that pass required ingress
 * checks and when enabled (TST_CFG.CLR_MISS_CNT_ENA) clear the LOC miss
 * counter.
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:TST_RX_LOC_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_RX_LOC_CNT(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,15)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_RX_LOC_CNT . TST_RX_LOC_CNT
 */
#define  VTSS_F_VOP_MRP_TST_RX_LOC_CNT_TST_RX_LOC_CNT(x)  (x)
#define  VTSS_M_VOP_MRP_TST_RX_LOC_CNT_TST_RX_LOC_CNT     0xffffffff
#define  VTSS_X_VOP_MRP_TST_RX_LOC_CNT_TST_RX_LOC_CNT(x)  (x)


/**
 * \brief Counts number of received valid MRP_InTest frames that clear the LOC miss counter
 *
 * \details
 * Counts number of received MRP_InTest PDUs that pass required ingress
 * checks and when enabled (ITST_CFG.ITST_CLR_MISS_CNT_ENA) clear the LOC
 * miss counter.
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:ITST_RX_LOC_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_RX_LOC_CNT(gi)     VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,16)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_ITST_RX_LOC_CNT . ITST_RX_LOC_CNT
 */
#define  VTSS_F_VOP_MRP_ITST_RX_LOC_CNT_ITST_RX_LOC_CNT(x)  (x)
#define  VTSS_M_VOP_MRP_ITST_RX_LOC_CNT_ITST_RX_LOC_CNT     0xffffffff
#define  VTSS_X_VOP_MRP_ITST_RX_LOC_CNT_ITST_RX_LOC_CNT(x)  (x)


/**
 * \brief Debug only
 *
 * \details
 * Latest Rx time stamp for valid MRP_Test frame
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:TST_RX_TS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_RX_TS(gi)           VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,17)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_RX_TS . TST_RX_TS
 */
#define  VTSS_F_VOP_MRP_TST_RX_TS_TST_RX_TS(x)  (x)
#define  VTSS_M_VOP_MRP_TST_RX_TS_TST_RX_TS     0xffffffff
#define  VTSS_X_VOP_MRP_TST_RX_TS_TST_RX_TS(x)  (x)


/**
 * \brief Debug only
 *
 * \details
 * Latest Tx time stamp from valid MRP_Test frame
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:TST_TX_TS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_TST_TX_TS(gi)           VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,18)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TST_TX_TS . TST_TX_TS
 */
#define  VTSS_F_VOP_MRP_TST_TX_TS_TST_TX_TS(x)  (x)
#define  VTSS_M_VOP_MRP_TST_TX_TS_TST_TX_TS     0xffffffff
#define  VTSS_X_VOP_MRP_TST_TX_TS_TST_TX_TS(x)  (x)


/**
 * \brief Debug only
 *
 * \details
 * Latest Rx time stamp from valid MRP_InTest frame
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:ITST_RX_TS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_RX_TS(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,19)

/**
 * \details
 * Field: ::VTSS_VOP_MRP_ITST_RX_TS . ITST_RX_TS
 */
#define  VTSS_F_VOP_MRP_ITST_RX_TS_ITST_RX_TS(x)  (x)
#define  VTSS_M_VOP_MRP_ITST_RX_TS_ITST_RX_TS     0xffffffff
#define  VTSS_X_VOP_MRP_ITST_RX_TS_ITST_RX_TS(x)  (x)


/**
 * \brief Debug only
 *
 * \details
 * Latest Tx time stamp from valid MRP_InTest frame
 *
 * Register: \a VOP_MRP:VOE_STAT_MRP:ITST_TX_TS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-37
 */
#define VTSS_VOP_MRP_ITST_TX_TS(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_MRP,0x0,gi,32,0,20)

/**
 * \brief
 * See Register description.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_ITST_TX_TS . ITST_TX_TS
 */
#define  VTSS_F_VOP_MRP_ITST_TX_TS_ITST_TX_TS(x)  (x)
#define  VTSS_M_VOP_MRP_ITST_TX_TS_ITST_TX_TS     0xffffffff
#define  VTSS_X_VOP_MRP_ITST_TX_TS_ITST_TX_TS(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_VOP_MRP_H_ */
