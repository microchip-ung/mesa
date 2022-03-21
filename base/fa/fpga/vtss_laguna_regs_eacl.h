// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_EACL_H_
#define _VTSS_LAGUNA_REGS_EACL_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a EACL
 *
 * Egress Access Control Lists
 *
 ***********************************************************************/

/**
 * Register Group: \a EACL:COMMON
 *
 * Common configuration and status for all egress ACL ports
 */


/**
 * \brief General options for EACLs
 *
 * \details
 * General configuration option of egress ACL
 *
 * Register: \a EACL:COMMON:OPTIONS
 */
#define VTSS_EACL_OPTIONS                    VTSS_IOREG(VTSS_TO_EACL,0x1488)

/**
 * \brief
 * Frame information to be used in matching is extracted fro SOF cells The
 * number of SOF cells that can be stored is limited. In case no SOF cell
 * could be stored and the frame copy has EACL lookup enabled, the frame
 * will normally be discarded for security reasons. This field allows to
 * disable the discard mechanism.See
 * also:QSYS:SOFDATA_POOL:SOFDATA_WM_VAL.SOFDATA_WM_VAL
 *
 * \details
 * 0: A frame copy for which the SOF cell could not be stored and for a
 * which EACL lookup is enabled is discarded.
 * 1: All frame copies are forwarded. In case the SOF cell could not be
 * stored, the rrespective EACL rule will not be applied.
 *
 * Field: ::VTSS_EACL_OPTIONS . ALLOW_FWD_AT_INVALID_SOF_DATA
 */
#define  VTSS_F_EACL_OPTIONS_ALLOW_FWD_AT_INVALID_SOF_DATA(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_EACL_OPTIONS_ALLOW_FWD_AT_INVALID_SOF_DATA  VTSS_BIT(19)
#define  VTSS_X_EACL_OPTIONS_ALLOW_FWD_AT_INVALID_SOF_DATA(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Selects the source of the source port added to the COPY_QUEUE_NUM.
 *
 * \details
 * 0: Source port number is taken from IFH.FWD.SRC_PORT
 * 1: Source port number is taken from cellbus sideband info
 *
 * Field: ::VTSS_EACL_OPTIONS . COPY_QUEUE_NUM_SRC_PORT_SEL
 */
#define  VTSS_F_EACL_OPTIONS_COPY_QUEUE_NUM_SRC_PORT_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_EACL_OPTIONS_COPY_QUEUE_NUM_SRC_PORT_SEL  VTSS_BIT(18)
#define  VTSS_X_EACL_OPTIONS_COPY_QUEUE_NUM_SRC_PORT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * If set the source port number will be added to the copy_queue_num action
 * response.
 *
 * \details
 * 0: Source port number will not be added to the COPY_QUEUE_NUM in EACL
 * response.
 * 1: COPY_QUEUE_NUM in EACL response is incremented by source port number
 * taken from IFH.FWD.SRC_PORT.
 *
 * Field: ::VTSS_EACL_OPTIONS . INCLUDE_SRC_PORT_IN_COPY_QUEUE_NUM
 */
#define  VTSS_F_EACL_OPTIONS_INCLUDE_SRC_PORT_IN_COPY_QUEUE_NUM(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_EACL_OPTIONS_INCLUDE_SRC_PORT_IN_COPY_QUEUE_NUM  VTSS_BIT(17)
#define  VTSS_X_EACL_OPTIONS_INCLUDE_SRC_PORT_IN_COPY_QUEUE_NUM(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Selects the source of the priority added to the COPY_QUEUE_NUM. See also
 * XQS:QMAP_QOS_TBL:QMAP_QOS_TBL.QMAP_QOS_SEL.Note: If IFH.VSTAX.MISC.COSID
 * is used as source for the priority to be added, it must be ensured that
 * the IFH.VSTAX2.MISC field contains ISDX and COSID.Related
 * parameters:ANA_AC:PS_COMMON:COMMON_VSTAX_CFG.VSTAX2_MISC_ISDX_ENAEACL:CO
 * MMON:ES2_CTRL.VSTAX2_MISC_ISDX_ENAREW:COMMON:PORT_CTRL.VSTAX2_MISC_ISDX_
 * ENA
 *
 * \details
 * 0: Use IPRIO as input selector (SRCP for normal queue mode)
 * 1: Use COSID as input selector
 * 2: Use TC as input selector
 * 3: Use PCP as input selector
 *
 * Field: ::VTSS_EACL_OPTIONS . COPY_QUEUE_NUM_PRIO_SEL
 */
#define  VTSS_F_EACL_OPTIONS_COPY_QUEUE_NUM_PRIO_SEL(x)  VTSS_ENCODE_BITFIELD(x,15,2)
#define  VTSS_M_EACL_OPTIONS_COPY_QUEUE_NUM_PRIO_SEL     VTSS_ENCODE_BITMASK(15,2)
#define  VTSS_X_EACL_OPTIONS_COPY_QUEUE_NUM_PRIO_SEL(x)  VTSS_EXTRACT_BITFIELD(x,15,2)

/**
 * \brief
 * If set the priority will be added to the copy_queue_num action response.
 * How the priority is generated is defined in COPY_QUEUE_NUM_PRIO_SEL.
 *
 * \details
 * 0: Priority will not be added to the COPY_QUEUE_NUM in EACL response.
 * 1: COPY_QUEUE_NUM in EACL response is incremented by 64*prio.
 *
 * Field: ::VTSS_EACL_OPTIONS . INCLUDE_PRIO_IN_COPY_QUEUE_NUM
 */
#define  VTSS_F_EACL_OPTIONS_INCLUDE_PRIO_IN_COPY_QUEUE_NUM(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_EACL_OPTIONS_INCLUDE_PRIO_IN_COPY_QUEUE_NUM  VTSS_BIT(14)
#define  VTSS_X_EACL_OPTIONS_INCLUDE_PRIO_IN_COPY_QUEUE_NUM(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Per defalt the EACL predicts the MAC address change of the REW in case
 * of routing or looping. Setting this bit keeps the original MAC address
 * the frame was received with.
 *
 * \details
 * 0: MAC addresses are updated when matched in EACL.
 * 1: Original MAC addresses are kept.
 *
 * Field: ::VTSS_EACL_OPTIONS . KEEP_ORIGINAL_MAC_ADDR
 */
#define  VTSS_F_EACL_OPTIONS_KEEP_ORIGINAL_MAC_ADDR(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_EACL_OPTIONS_KEEP_ORIGINAL_MAC_ADDR  VTSS_BIT(13)
#define  VTSS_X_EACL_OPTIONS_KEEP_ORIGINAL_MAC_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Selects the source of the COSID field inside the ES2 entry.Note: If
 * IFH.VSTAX.MISC.COSID is used as source for the COSID value, it must be
 * ensured that the IFH.VSTAX2.MISC field contains ISDX and COSID.Related
 * parameters:ANA_AC:PS_COMMON:COMMON_VSTAX_CFG.VSTAX2_MISC_ISDX_ENAEACL:CO
 * MMON:ES2_CTRL.VSTAX2_MISC_ISDX_ENAREW:COMMON:PORT_CTRL.VSTAX2_MISC_ISDX_
 * ENA
 *
 * \details
 * 0: Use IFH.VSTAX.MISC.COSID as source for the COSID value.
 * 1: Use IFH.VSTAX.QOS.IPRIO as source for the COSID value.
 * 2: Use cell_bus.prio as source for the COSID value.
 * 3: Reserved.
 *
 * Field: ::VTSS_EACL_OPTIONS . ES2_COSID_SRC_SEL
 */
#define  VTSS_F_EACL_OPTIONS_ES2_COSID_SRC_SEL(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_EACL_OPTIONS_ES2_COSID_SRC_SEL     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_EACL_OPTIONS_ES2_COSID_SRC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * Selects the source of the PCP field inside the ES2 entry.
 *
 * \details
 * 0: Use IFH.VSTAX.TAG.UPRIO as source for the PCP value.
 * 1: Use IFH.VSTAX.QOS.IPRIO as source  for the PCP value.
 * 2: Use cell_bus.prio as source  for the PCP value.
 * 3: Reserved.
 *
 * Field: ::VTSS_EACL_OPTIONS . ES2_PCP_SRC_SEL
 */
#define  VTSS_F_EACL_OPTIONS_ES2_PCP_SRC_SEL(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_EACL_OPTIONS_ES2_PCP_SRC_SEL     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_EACL_OPTIONS_ES2_PCP_SRC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * If this bit is set, the port_num field from the cell bus is used as
 * ingress port number instead of the SRC_PORT field from IFH.FWD.
 *
 * \details
 * 0: Use IFH.FWD.SRC_PORT as ingress port number. This should be the
 * logical port number.
 * 1: Use port_num from cell_bus. Thos should be the physical port number.
 *
 * Field: ::VTSS_EACL_OPTIONS . USE_CELL_BUS_IGR_PORT_NUM
 */
#define  VTSS_F_EACL_OPTIONS_USE_CELL_BUS_IGR_PORT_NUM(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_EACL_OPTIONS_USE_CELL_BUS_IGR_PORT_NUM  VTSS_BIT(8)
#define  VTSS_X_EACL_OPTIONS_USE_CELL_BUS_IGR_PORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * If bit FORCE_SINGLE_CYCLE_FWD is set, this field defines the hreshold
 * abive which the QS is throttled down to two cycle forward to avoid an
 * overflow.
 *
 * \details
 * N: Maximum number of entries allowed before the QSYS forwarding process
 * is throttled to forward frame requests only every 2nd clock cycle.
 *
 * Field: ::VTSS_EACL_OPTIONS . SINGLE_CYCLE_FWD_STATS_FIFO_THRES
 */
#define  VTSS_F_EACL_OPTIONS_SINGLE_CYCLE_FWD_STATS_FIFO_THRES(x)  VTSS_ENCODE_BITFIELD(x,3,5)
#define  VTSS_M_EACL_OPTIONS_SINGLE_CYCLE_FWD_STATS_FIFO_THRES     VTSS_ENCODE_BITMASK(3,5)
#define  VTSS_X_EACL_OPTIONS_SINGLE_CYCLE_FWD_STATS_FIFO_THRES(x)  VTSS_EXTRACT_BITFIELD(x,3,5)

/**
 * \brief
 * If bit FORCE_SINGLE_CYCLE_FWD is set, this bit selects whether only a
 * common default rule is hit like for the first ES2 access or if a per
 * port default rule is hit like for the second ES2 access.
 *
 * \details
 * 0: The common default rule is hit.
 * 1: The per port default rule is hit.
 *
 * Field: ::VTSS_EACL_OPTIONS . SINGLE_CYCLE_FWD_DEFAULT_SEL
 */
#define  VTSS_F_EACL_OPTIONS_SINGLE_CYCLE_FWD_DEFAULT_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_EACL_OPTIONS_SINGLE_CYCLE_FWD_DEFAULT_SEL  VTSS_BIT(2)
#define  VTSS_X_EACL_OPTIONS_SINGLE_CYCLE_FWD_DEFAULT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If this bit is set, the FWD in the QSYS is allowed to forward frames
 * with every clock cycle. EACL has only one lookup.Related
 * parameters:QFWD::FWD_CTRL.FWD_ONECYC_ENA
 *
 * \details
 * 0: Two lookups are available.
 * 1: Only the first lookup is available.
 *
 * Field: ::VTSS_EACL_OPTIONS . FORCE_SINGLE_CYCLE_FWD
 */
#define  VTSS_F_EACL_OPTIONS_FORCE_SINGLE_CYCLE_FWD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_OPTIONS_FORCE_SINGLE_CYCLE_FWD  VTSS_BIT(1)
#define  VTSS_X_EACL_OPTIONS_FORCE_SINGLE_CYCLE_FWD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Disable using the virtual interface number for key matching. It means if
 * the valid bit is set in EACL::IF_MAP_TBL.VIRT_IF_NUM_VLD, the virtual
 * interface number is only used for the key profile selection
 *
 * \details
 * 0: Use virtual interface number in key matching
 * 1: Do not use virtual interface number in key matching
 *
 * Field: ::VTSS_EACL_OPTIONS . VIRT_INT_NUM_MATCH_DIS
 */
#define  VTSS_F_EACL_OPTIONS_VIRT_INT_NUM_MATCH_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_OPTIONS_VIRT_INT_NUM_MATCH_DIS  VTSS_BIT(0)
#define  VTSS_X_EACL_OPTIONS_VIRT_INT_NUM_MATCH_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configure custom TPID values
 *
 * \details
 * Register: \a EACL:COMMON:TPID_CFG
 *
 * @param ri Register: TPID_CFG (??), 0-2
 */
#define VTSS_EACL_TPID_CFG(ri)               VTSS_IOREG(VTSS_TO_EACL,0x1489 + (ri))

/**
 * \brief
 * Configure 3 custom TPID values.These must be configured identically in
 * ANA_CL::VLAN_STAG_CFG.STAG_ETYPE_VAL.Related
 * parameters:ANA_CL::VLAN_STAG_CFG.STAG_ETYPE_VAL
 *
 * \details
 * n: TPID value
 *
 * Field: ::VTSS_EACL_TPID_CFG . TPID_VAL
 */
#define  VTSS_F_EACL_TPID_CFG_TPID_VAL(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_EACL_TPID_CFG_TPID_VAL        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_EACL_TPID_CFG_TPID_VAL(x)     VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief E-tag configuration
 *
 * \details
 * Register: \a EACL:COMMON:ETAG_CFG
 */
#define VTSS_EACL_ETAG_CFG                   VTSS_IOREG(VTSS_TO_EACL,0x148c)

/**
 * \brief
 * Enable E-tag awareness.This field must be configured identical to
 * ANA_CL::ETAG_CFG.ETAG_TPID_ENA.
 *
 * \details
 * Field: ::VTSS_EACL_ETAG_CFG . ETAG_TPID_ENA
 */
#define  VTSS_F_EACL_ETAG_CFG_ETAG_TPID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_ETAG_CFG_ETAG_TPID_ENA   VTSS_BIT(0)
#define  VTSS_X_EACL_ETAG_CFG_ETAG_TPID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Redundancy tag configuration
 *
 * \details
 * Register: \a EACL:COMMON:RTAG_CFG
 */
#define VTSS_EACL_RTAG_CFG                   VTSS_IOREG(VTSS_TO_EACL,0x148d)

/**
 * \brief
 * Enable HSR-tag awareness.This field must be configured identical to
 * ANA_CL::RTAG_CFG.HSR_TPID_ENA.
 *
 * \details
 * Field: ::VTSS_EACL_RTAG_CFG . HSR_TPID_ENA
 */
#define  VTSS_F_EACL_RTAG_CFG_HSR_TPID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_RTAG_CFG_HSR_TPID_ENA    VTSS_BIT(1)
#define  VTSS_X_EACL_RTAG_CFG_HSR_TPID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable R-tag awareness.This field must be configured identical to
 * ANA_CL::RTAG_CFG.RTAG_TPID_ENA.
 *
 * \details
 * Field: ::VTSS_EACL_RTAG_CFG . RTAG_TPID_ENA
 */
#define  VTSS_F_EACL_RTAG_CFG_RTAG_TPID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_RTAG_CFG_RTAG_TPID_ENA   VTSS_BIT(0)
#define  VTSS_X_EACL_RTAG_CFG_RTAG_TPID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Various configuration of ES2 in egress ACL module
 *
 * \details
 * Register: \a EACL:COMMON:ES2_CTRL
 */
#define VTSS_EACL_ES2_CTRL                   VTSS_IOREG(VTSS_TO_EACL,0x148e)

/**
 * \brief
 * Configure VSTAX MISC field decoding. Should be configured consistent
 * with ANA_AC and REW.Related
 * parameters:ANA_AC:PS_COMMON:COMMON_VSTAX_CFG.VSTAX2_MISC_ISDX_ENAREW:COM
 * MON:PORT_CTRL.VSTAX2_MISC_ISDX_ENA
 *
 * \details
 * 0: VSTAX MISC contains aggregation code
 * 1: VSTAX MISC contains ISDX and COSID
 *
 * Field: ::VTSS_EACL_ES2_CTRL . VSTAX2_MISC_ISDX_ENA
 */
#define  VTSS_F_EACL_ES2_CTRL_VSTAX2_MISC_ISDX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_EACL_ES2_CTRL_VSTAX2_MISC_ISDX_ENA  VTSS_BIT(16)
#define  VTSS_X_EACL_ES2_CTRL_VSTAX2_MISC_ISDX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Selects ES2 action to combine the REW_CMD fields from the two lookups.
 *
 * \details
 * 0: Select REW_CMD of first lookup if both lookups are valid else only
 * REW_CMD from valid lookup is selected.
 * 1: Select REW_CMD of second lookup if both lookups are valid else only
 * REW_CMD from valid lookup is selected.
 * 2: Logical OR the REW_CMD of first and second lookup if both lookups are
 * valid else only REW_CMD from valid lookup is selected.
 * 3: Logical AND the REW_CMD of first and second lookup if both lookups
 * are valid else only REW_CMD from valid lookup is selected.
 *
 * Field: ::VTSS_EACL_ES2_CTRL . ACTION_REW_CMD_SEL
 */
#define  VTSS_F_EACL_ES2_CTRL_ACTION_REW_CMD_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_EACL_ES2_CTRL_ACTION_REW_CMD_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_EACL_ES2_CTRL_ACTION_REW_CMD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Selects ES2 action to use when a DISCARD action result clashed with a
 * redir REDIRECT result.
 *
 * \details
 * Two bits, one per DISCARD result.
 * Bit 0 regards to first action result is DISCARD and second action result
 * is REDIRECT.
 * Bit 1 regards to first action result is REDIRECT and second action
 * result is DISCARD.
 * 0: DISCARD takes priority.
 * 1: REDIRECT takes priority.
 *
 * Field: ::VTSS_EACL_ES2_CTRL . ACTION_REDIR_DISCARD_SEL
 */
#define  VTSS_F_EACL_ES2_CTRL_ACTION_REDIR_DISCARD_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_EACL_ES2_CTRL_ACTION_REDIR_DISCARD_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_EACL_ES2_CTRL_ACTION_REDIR_DISCARD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Selects which queue_num and port number to use, when both ES2 actions
 * result in COPY or both ES2 actions result in REDIRECT.
 *
 * \details
 * 0: Use queue_num and port_num from first action result
 * 1: Use queue_num and port_num from second action result
 *
 * Field: ::VTSS_EACL_ES2_CTRL . ACTION_REDIR_COPY_SEL
 */
#define  VTSS_F_EACL_ES2_CTRL_ACTION_REDIR_COPY_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_EACL_ES2_CTRL_ACTION_REDIR_COPY_SEL  VTSS_BIT(4)
#define  VTSS_X_EACL_ES2_CTRL_ACTION_REDIR_COPY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Selects which queue_num to use, when both ES2 actions result in CPU
 * COPY.
 *
 * \details
 * 0: Use CPU queue_num from first action result
 * 1: Use CPU queue_num from second action result
 *
 * Field: ::VTSS_EACL_ES2_CTRL . ACTION_CPU_COPY_SEL
 */
#define  VTSS_F_EACL_ES2_CTRL_ACTION_CPU_COPY_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_EACL_ES2_CTRL_ACTION_CPU_COPY_SEL  VTSS_BIT(3)
#define  VTSS_X_EACL_ES2_CTRL_ACTION_CPU_COPY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable ES2 router mode lookup when IFH.ENCAP.RT_FWD indicates
 * routing.When enabled and IFH.FWD.DST_MODE = ENCAP, IFH.ENCAP.RT_FWD = 1,
 * and IFH.ENCAP_ID_RLEG_MODE = 3, then IFH.ENCAP.ENCAP_ID_RLEG field is
 * decoded and used as ERLEG in the lookup keysIf IFH.ENCAP.RT_FWD does not
 * indicate routing, the lookup is done normally regardless of the
 * ES2_BY_RT_FWD configuration.
 *
 * \details
 * 0: Normal ES2 lookup
 * 1: Enable router mode ES2 lookup
 *
 * Field: ::VTSS_EACL_ES2_CTRL . ES2_IGR_PORT_BY_RT_FWD
 */
#define  VTSS_F_EACL_ES2_CTRL_ES2_IGR_PORT_BY_RT_FWD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_EACL_ES2_CTRL_ES2_IGR_PORT_BY_RT_FWD  VTSS_BIT(2)
#define  VTSS_X_EACL_ES2_CTRL_ES2_IGR_PORT_BY_RT_FWD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable ES2 router mode lookup when IFH.FWD.DST_MODE indicates
 * routing.When enabled and IFH.FWD.DST_MODE = L3UC_ROUTING or
 * IFH.FWD.DST_MODE = L3MC_ROUTING, the IFH.DST.ERLEG is used in ES2
 * lookup.If IFH_FWD.DST_MODE does not indicate routing, the lookup is done
 * normally regardless of the ES2_BY_RLEG configuration.
 *
 * \details
 * 0: Normal ES2 lookup
 * 1: Enable router mode ES2 lookup
 *
 * Field: ::VTSS_EACL_ES2_CTRL . ES2_IGR_PORT_BY_RLEG
 */
#define  VTSS_F_EACL_ES2_CTRL_ES2_IGR_PORT_BY_RLEG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_ES2_CTRL_ES2_IGR_PORT_BY_RLEG  VTSS_BIT(1)
#define  VTSS_X_EACL_ES2_CTRL_ES2_IGR_PORT_BY_RLEG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief Map drop precedence to drop eligible value
 *
 * \details
 * Drop precedence level for the frame is translated to a drop eligible
 * value 0 or 1, selecting between _DE0 or _DE1 mapping tables, when
 * translating the internal prio to TAG priorities. Mapped drop
 * precedence/internal priority is used when selected by TAG control
 * configuration (see TAG ctrl)
 *
 * Register: \a EACL:COMMON:DP_MAP
 */
#define VTSS_EACL_DP_MAP                     VTSS_IOREG(VTSS_TO_EACL,0x148f)

/**
 * \brief
 * Drop precedence N uses mapping table given by bit N in this field.
 *
 * \details
 * xxx0: Map DP value 0 to DE value 0
 * xxx1: Map DP value 0 to DE value 1
 * ...
 * 0xxx: Map DP value 3 to DE value 0
 * 1xxx: Map DP value 3 to DE value 1

 *
 * Field: ::VTSS_EACL_DP_MAP . DP
 */
#define  VTSS_F_EACL_DP_MAP_DP(x)             VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_EACL_DP_MAP_DP                VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_EACL_DP_MAP_DP(x)             VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Global CPU configuration
 *
 * \details
 * Selected local CPU queues can be redirected to a global CPU (GCPU)
 * located on front- and/or stack ports. Each of the eight local CPU queues
 * are configured individually.
 *
 * CPU queue redirection is enabled in QFWD::FRAME_COPY_CFG.FRMC_PORT_VAL
 *
 * The CPU queue number assigned to a frame is the highest priority CPU
 * queue bit set in IFH.MISC.CPU_MASK. The CPU queue number is used to
 * select configuration per queue.
 *
 * The GCPU forward frame modifications are not done, if no bits are set in
 * IFH.MISC.CPU_MASK.

 *
 * Register: \a EACL:COMMON:GCPU_CFG
 *
 * @param ri Register: GCPU_CFG (??), 0-7
 */
#define VTSS_EACL_GCPU_CFG(ri)               VTSS_IOREG(VTSS_TO_EACL,0x1490 + (ri))

/**
 * \brief
 * Used when GCPU frames are forwarded to a front port. Frame are not
 * modified when forwarded to the GCPU expect for the optional tags
 * configured REW:COMMON:GCPU_CFG[0-7].GCPU_TAG_SEL.The field
 * IFH.DST.ENCAP.W16_POP_CNT is set to 0 for these frames.This register
 * must be set in accordance to REW:COMMON:GCPU_CFG[0-7].GCPU_DO_NOT_REW
 *
 * \details
 * 0: Allow normal rewrites of GCPU frames forwarded to front ports
 * 1: Allow only addition of GCPU_TAGS to GCPU frames
 *
 * Field: ::VTSS_EACL_GCPU_CFG . GCPU_DO_NOT_REW
 */
#define  VTSS_F_EACL_GCPU_CFG_GCPU_DO_NOT_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_GCPU_CFG_GCPU_DO_NOT_REW  VTSS_BIT(0)
#define  VTSS_X_EACL_GCPU_CFG_GCPU_DO_NOT_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Rewriter router leg configuration.
 *
 * \details
 * Register: \a EACL:COMMON:RLEG_CFG_0
 */
#define VTSS_EACL_RLEG_CFG_0                 VTSS_IOREG(VTSS_TO_EACL,0x1498)

/**
 * \brief
 * Router leg base MAC address, least significant bits.In order to have
 * different MAC addresses per router leg, the base address may be
 * incremented using VID or VMID, ref. RLEG_MAC_TYPE_SEL.This must be
 * configured consistently in ANA_L3::RLEG_CFG_0.RLEG_MAC_LSB.
 *
 * \details
 * Bit 0: MAC address, bit 0
 * ...
 * Bit 23: MAC address, bit 23
 *
 * Field: ::VTSS_EACL_RLEG_CFG_0 . RLEG_MAC_LSB
 */
#define  VTSS_F_EACL_RLEG_CFG_0_RLEG_MAC_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_EACL_RLEG_CFG_0_RLEG_MAC_LSB     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_EACL_RLEG_CFG_0_RLEG_MAC_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief Rewriter router leg configuration.
 *
 * \details
 * Register: \a EACL:COMMON:RLEG_CFG_1
 */
#define VTSS_EACL_RLEG_CFG_1                 VTSS_IOREG(VTSS_TO_EACL,0x1499)

/**
 * \brief
 * Configuration of router leg specific MAC address.Related
 * parameters:ANA_L3::RLEG_CFG_1.RLEG_MAC_TYPE_SELREW::RLEG_CFG_1.RLEG_MAC_
 * TYPE_SEL
 *
 * \details
 * 0: RLEG used to increment base MAC address:
 * RLEG_MAC = RLEG_MAC_MSB(23:0) & ((RLEG_MAC_LSB(23:0) + IFH.ERLEG) mod
 * 2**24)
 *
 * 1: RLEG_EVID (IFH.VSTAX.TAG.VID) used to increment base MAC address:
 * RLEG_MAC = RLEG_MAC_MSB(23:0) & ((RLEG_MAC_LSB(23:0) + RLEG_EVID) mod
 * 2**24)
 *
 * 2: Base MAC address used for all router legs
 * RLEG_MAC = RLEG_MAC_MSB[23:0] & RLEG_MAC_LSB[23:0]
 *
 * 3: Reserved
 *
 * Field: ::VTSS_EACL_RLEG_CFG_1 . RLEG_MAC_TYPE_SEL
 */
#define  VTSS_F_EACL_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_EACL_RLEG_CFG_1_RLEG_MAC_TYPE_SEL     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_EACL_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Router leg base MAC address, least significant bits.In order to have
 * different MAC addresses per router leg, the base address may be
 * incremented using VID or VMID, ref. RLEG_MAC_TYPE_SEL.This must be
 * configured consistently in ANA_L3::RLEG_CFG_1.RLEG_MAC_MSB.
 *
 * \details
 * Bit 0: MAC address, bit 24
 * ...
 * Bit 23: MAC address, bit 47
 *
 * Field: ::VTSS_EACL_RLEG_CFG_1 . RLEG_MAC_MSB
 */
#define  VTSS_F_EACL_RLEG_CFG_1_RLEG_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_EACL_RLEG_CFG_1_RLEG_MAC_MSB     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_EACL_RLEG_CFG_1_RLEG_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief Fragment configuration
 *
 * \details
 * Register: \a EACL:COMMON:VCAP_ES2_FRAGMENT_CFG
 */
#define VTSS_EACL_VCAP_ES2_FRAGMENT_CFG      VTSS_IOREG(VTSS_TO_EACL,0x149a)

/**
 * \brief
 * If set, ES2 key field L3_FRAGMENT_TYPE encodes Jaguar2-style
 * fragmentation information in CLM:L3_FRAGMENT_TYPE[0]: Set if IPv4 frame
 * is fragmented (MF==1 or FO>0).L3_FRAGMENT_TYPE[1]: Set if IPv4 frame is
 * fragmented but not the first fragment (FO>0),If cleared, ES2 key field
 * L3_FRAGMENT_TYPE encodes the following values:0: No Fragments: MF==0 and
 * FO==01: Initial Fragments: MF==1 and FO == 02: Suspicious Fragment:
 * FO!=0 and FO <= VCAP_ES2_FRAGMENT_CFG.FRAGMENT_OFFSET_THRES.3: Valid
 * Follow-up Fragment: FO > VCAP_ES2_FRAGMENT_CFG.FRAGMENT_OFFSET_THRES.MF:
 * More Fragments flag in IPv4 header.FO: Fragment offset in IPv4 header.
 *
 * \details
 * 0: Fragment offset threshold is used.
 * 1: Fragment offset threshold is not used.
 *
 * Field: ::VTSS_EACL_VCAP_ES2_FRAGMENT_CFG . FRAGMENT_OFFSET_THRES_DIS
 */
#define  VTSS_F_EACL_VCAP_ES2_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_EACL_VCAP_ES2_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES_DIS  VTSS_BIT(4)
#define  VTSS_X_EACL_VCAP_ES2_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Threshold used for encoding of the L3_FRAGMENT_TYPE field in ES2.
 *
 * \details
 * Field: ::VTSS_EACL_VCAP_ES2_FRAGMENT_CFG . FRAGMENT_OFFSET_THRES
 */
#define  VTSS_F_EACL_VCAP_ES2_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_EACL_VCAP_ES2_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_EACL_VCAP_ES2_FRAGMENT_CFG_FRAGMENT_OFFSET_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Configuration of TCP range generation
 *
 * \details
 * Register: \a EACL:COMMON:VCAP_ES2_RNG_CTRL
 *
 * @param ri Replicator: x_FFL_EACL_NUM_RNG_CHKRS (??), 0-15
 */
#define VTSS_EACL_VCAP_ES2_RNG_CTRL(ri)      VTSS_IOREG(VTSS_TO_EACL,0x149b + (ri))

/**
 * \brief
 * Selected field matched against the range
 *
 * \details
 * 0: Idle (No match)
 * 1: TCP / UDP dport value is matched against range
 * 2: TCP / UDP sport value is matched against range
 * 3: TCP / UDP dport or sport values are matched against range
 * 4: Classified VID value is matched against range
 * 5: Classified DSCP value is matched against range
 * 7: Reserved
 *
 * Field: ::VTSS_EACL_VCAP_ES2_RNG_CTRL . RNG_TYPE_SEL
 */
#define  VTSS_F_EACL_VCAP_ES2_RNG_CTRL_RNG_TYPE_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_EACL_VCAP_ES2_RNG_CTRL_RNG_TYPE_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_EACL_VCAP_ES2_RNG_CTRL_RNG_TYPE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuration of  matcher range generation
 *
 * \details
 * Register: \a EACL:COMMON:VCAP_ES2_RNG_VALUE_CFG
 *
 * @param ri Replicator: x_FFL_EACL_NUM_TCP_RANGES (??), 0-15
 */
#define VTSS_EACL_VCAP_ES2_RNG_VALUE_CFG(ri)  VTSS_IOREG(VTSS_TO_EACL,0x14ab + (ri))

/**
 * \brief
 * Upper range value
 *
 * \details
 * Field: ::VTSS_EACL_VCAP_ES2_RNG_VALUE_CFG . RNG_MAX_VALUE
 */
#define  VTSS_F_EACL_VCAP_ES2_RNG_VALUE_CFG_RNG_MAX_VALUE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_EACL_VCAP_ES2_RNG_VALUE_CFG_RNG_MAX_VALUE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_EACL_VCAP_ES2_RNG_VALUE_CFG_RNG_MAX_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Lower range value
 *
 * \details
 * Field: ::VTSS_EACL_VCAP_ES2_RNG_VALUE_CFG . RNG_MIN_VALUE
 */
#define  VTSS_F_EACL_VCAP_ES2_RNG_VALUE_CFG_RNG_MIN_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_EACL_VCAP_ES2_RNG_VALUE_CFG_RNG_MIN_VALUE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_EACL_VCAP_ES2_RNG_VALUE_CFG_RNG_MIN_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief EACL Interrupt events
 *
 * \details
 * EACL Interrupt events if interrupt enable is set in EACL::INTR_ENA and
 * the corresponding event is triggered in EACL::INTR_IDENT
 *
 * Register: \a EACL:COMMON:INTR
 */
#define VTSS_EACL_INTR                       VTSS_IOREG(VTSS_TO_EACL,0x14bb)

/**
 * \brief
 * Set if a frame was discarded due to an invalid SOF pointer. I.e. the SOF
 * cell could not be stored due to resource limitations. To enable this
 * interrupt, set EACL::INTR_ENA.VCAP_ES2_INTR_ENA
 *
 * \details
 * 0: No event
 * 1: Event
 *
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_EACL_INTR . INVLD_SOF_PTR_DISCARD_INTR
 */
#define  VTSS_F_EACL_INTR_INVLD_SOF_PTR_DISCARD_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_INTR_INVLD_SOF_PTR_DISCARD_INTR  VTSS_BIT(1)
#define  VTSS_X_EACL_INTR_INVLD_SOF_PTR_DISCARD_INTR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if VCAP_ES2 triggered an interrupt. To enable this interrupt, set
 * EACL::INTR_ENA.VCAP_ES2_INTR_ENA
 *
 * \details
 * 0: No event
 * 1: Event
 *
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_EACL_INTR . VCAP_ES2_INTR
 */
#define  VTSS_F_EACL_INTR_VCAP_ES2_INTR(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_INTR_VCAP_ES2_INTR       VTSS_BIT(0)
#define  VTSS_X_EACL_INTR_VCAP_ES2_INTR(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief EACL interrupt enable mask
 *
 * \details
 * Controls interrupt of CPU.
 *
 * Events can be found in EACL::INTR
 * Identity of interrupt events can be found in EACL::INTR_IDENT

 *
 * Register: \a EACL:COMMON:INTR_ENA
 */
#define VTSS_EACL_INTR_ENA                   VTSS_IOREG(VTSS_TO_EACL,0x14bc)

/**
 * \brief
 * Configures INVLD_SOF_PTR_DISCARD_INTR interrupts
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_EACL_INTR_ENA . INVLD_SOF_PTR_DISCARD_INTR_ENA
 */
#define  VTSS_F_EACL_INTR_ENA_INVLD_SOF_PTR_DISCARD_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_INTR_ENA_INVLD_SOF_PTR_DISCARD_INTR_ENA  VTSS_BIT(1)
#define  VTSS_X_EACL_INTR_ENA_INVLD_SOF_PTR_DISCARD_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Configures VCAP_ES2_INTR interrupts
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_EACL_INTR_ENA . VCAP_ES2_INTR_ENA
 */
#define  VTSS_F_EACL_INTR_ENA_VCAP_ES2_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_INTR_ENA_VCAP_ES2_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_EACL_INTR_ENA_VCAP_ES2_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief EACL interrupt status
 *
 * \details
 * Register: \a EACL:COMMON:INTR_IDENT
 */
#define VTSS_EACL_INTR_IDENT                 VTSS_IOREG(VTSS_TO_EACL,0x14bd)

/**
 * \brief
 * Status of INVLD_SOF_PTR_DISCARD_INTR interrupts
 *
 * \details
 * 0: No interrupt
 * 1: Interrupt to CPU
 *
 * Field: ::VTSS_EACL_INTR_IDENT . INVLD_SOF_PTR_DISCARD_INTR_IDENT
 */
#define  VTSS_F_EACL_INTR_IDENT_INVLD_SOF_PTR_DISCARD_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_INTR_IDENT_INVLD_SOF_PTR_DISCARD_INTR_IDENT  VTSS_BIT(1)
#define  VTSS_X_EACL_INTR_IDENT_INVLD_SOF_PTR_DISCARD_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Status of VCAP_ES2_INTR interrupts
 *
 * \details
 * 0: No interrupt
 * 1: Interrupt to CPU
 *
 * Field: ::VTSS_EACL_INTR_IDENT . VCAP_ES2_INTR_IDENT
 */
#define  VTSS_F_EACL_INTR_IDENT_VCAP_ES2_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_INTR_IDENT_VCAP_ES2_INTR_IDENT  VTSS_BIT(0)
#define  VTSS_X_EACL_INTR_IDENT_VCAP_ES2_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a EACL:INTERFACE_MAP
 *
 * Interface mapping table to map from XQS:QMAP_VPORT_TBL:QMAP_VPORT_TBL.QMAP_VPORT_VAL to a physical/logical port number, an interface number and an ACL group
 */


/**
 * \brief Interface mapping table to map from XQS:QMAP_VPORT_TBL:QMAP_VPORT_TBL.QMAP_VPORT_VAL
 *
 * \details
 * Interface mapping table to map from
 * XQS:QMAP_VPORT_TBL:QMAP_VPORT_TBL.QMAP_VPORT_VAL to a physical/logical
 * port number, an interface number and an ACL group
 *
 * Register: \a EACL:INTERFACE_MAP:IF_MAP_TBL
 *
 * @param gi Replicator: x_FFL_CHIP_QSYS_NUM_VPORTS (??), 0-1119
 */
#define VTSS_EACL_IF_MAP_TBL(gi)             VTSS_IOREG_IX(VTSS_TO_EACL,0x800,gi,1,0,0)

/**
 * \brief
 * ACL Group Identifier.
 *
 * \details
 * Field: ::VTSS_EACL_IF_MAP_TBL . ACL_GRP_ID
 */
#define  VTSS_F_EACL_IF_MAP_TBL_ACL_GRP_ID(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EACL_IF_MAP_TBL_ACL_GRP_ID     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EACL_IF_MAP_TBL_ACL_GRP_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Virtual Interface number valid. Selects whether PHYS_PORT_NUM or
 * VIRT_IF_NUM is used for key profile selection and VCAP match. One bit
 * per lookup.
 *
 * \details
 * 0: PHYS_PORT_NUM is used for VCAP lookup and key profile selection.
 * 1: VIRT_IF_NUM is used for VCAP lookup and key profile selection.
 *
 * Field: ::VTSS_EACL_IF_MAP_TBL . VIRT_IF_NUM_VLD
 */
#define  VTSS_F_EACL_IF_MAP_TBL_VIRT_IF_NUM_VLD(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_EACL_IF_MAP_TBL_VIRT_IF_NUM_VLD     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_EACL_IF_MAP_TBL_VIRT_IF_NUM_VLD(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * Virtual Interface number.
 *
 * \details
 * Field: ::VTSS_EACL_IF_MAP_TBL . VIRT_IF_NUM
 */
#define  VTSS_F_EACL_IF_MAP_TBL_VIRT_IF_NUM(x)  VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_EACL_IF_MAP_TBL_VIRT_IF_NUM     VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_EACL_IF_MAP_TBL_VIRT_IF_NUM(x)  VTSS_EXTRACT_BITFIELD(x,7,5)

/**
 * \brief
 * Physical or logical port number.
 *
 * \details
 * Port number, either physical or logical.
 *
 * Field: ::VTSS_EACL_IF_MAP_TBL . PHYS_PORT_NUM
 */
#define  VTSS_F_EACL_IF_MAP_TBL_PHYS_PORT_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_EACL_IF_MAP_TBL_PHYS_PORT_NUM     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_EACL_IF_MAP_TBL_PHYS_PORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a EACL:ES2_KEY_SELECT_PROFILE
 *
 * VCAP_ES2 configuration per port or vitual interface.
0-29: 30 Physical ports.
30-59: 30 Virtual Interfaces.
60-67: 8 CPU ports.
 */


/**
 * \brief VCAP_IS2 key selection
 *
 * \details
 * Key selection for VCAP_ES2 lookups. Replicated per lookup.
 *
 * Register: \a EACL:ES2_KEY_SELECT_PROFILE:VCAP_ES2_KEY_SEL
 *
 * @param gi Replicator: x_FFL_EACL_NUM_PROFILES (??), 0-67
 * @param ri Replicator: x_FFL_EACL_NUM_LOOKUPS (??), 0-1
 */
#define VTSS_EACL_VCAP_ES2_KEY_SEL(gi,ri)    VTSS_IOREG_IX(VTSS_TO_EACL,0x1400,gi,2,ri,0)

/**
 * \brief
 * Applies to MAC frames.
 *
 * \details
 * 0: Use selection from ARP_KEY_SEL.
 * 1: Match against IP_7TUPLE entries.

 *
 * Field: ::VTSS_EACL_VCAP_ES2_KEY_SEL . ARP_7TUPLE_ENA
 */
#define  VTSS_F_EACL_VCAP_ES2_KEY_SEL_ARP_7TUPLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_EACL_VCAP_ES2_KEY_SEL_ARP_7TUPLE_ENA  VTSS_BIT(9)
#define  VTSS_X_EACL_VCAP_ES2_KEY_SEL_ARP_7TUPLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Applies to MAC_ETYPE frames.
 *
 * \details
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against IP_7TUPLE entries.

 *
 * Field: ::VTSS_EACL_VCAP_ES2_KEY_SEL . MAC_KEY_SEL
 */
#define  VTSS_F_EACL_VCAP_ES2_KEY_SEL_MAC_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_EACL_VCAP_ES2_KEY_SEL_MAC_KEY_SEL  VTSS_BIT(8)
#define  VTSS_X_EACL_VCAP_ES2_KEY_SEL_MAC_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Applies to IPv6 unicast and multicast frames.
 *
 * \details
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against IP_7TUPLE entries.
 * 4: Match against IP6_VID entries.
 * 5: Match against IP6_STD entries.
 * 6: Downgrade IPv6 frames to IPv4 and do key type selection according to
 * IP4_KEY_SEL.
 *
 * Field: ::VTSS_EACL_VCAP_ES2_KEY_SEL . IP6_KEY_SEL
 */
#define  VTSS_F_EACL_VCAP_ES2_KEY_SEL_IP6_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_EACL_VCAP_ES2_KEY_SEL_IP6_KEY_SEL     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_EACL_VCAP_ES2_KEY_SEL_IP6_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * Applies to IPv4 unicast and multicast frames.
 *
 * \details
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against IP_7TUPLE entries.
 * 3: Match against IP4_TCP_UDP for IPv4 TCP/UDP frames and against
 * IP4_OTHER entries for other IPv4 frames.
 * 4: Match against IP4_VID entries.
 * 5: Match against IP4_OTHER entries.
 *
 * Field: ::VTSS_EACL_VCAP_ES2_KEY_SEL . IP4_KEY_SEL
 */
#define  VTSS_F_EACL_VCAP_ES2_KEY_SEL_IP4_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_EACL_VCAP_ES2_KEY_SEL_IP4_KEY_SEL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_EACL_VCAP_ES2_KEY_SEL_IP4_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/**
 * \brief
 * Applies to ARP/RARP frames.
 *
 * \details
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against ARP entries.
 *
 * Field: ::VTSS_EACL_VCAP_ES2_KEY_SEL . ARP_KEY_SEL
 */
#define  VTSS_F_EACL_VCAP_ES2_KEY_SEL_ARP_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_VCAP_ES2_KEY_SEL_ARP_KEY_SEL  VTSS_BIT(1)
#define  VTSS_X_EACL_VCAP_ES2_KEY_SEL_ARP_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable/disable VCAP_ES2 lookups.
 *
 * \details
 * 0: No ES2 lookup for this profile.
 * 1: ES2 lookup enabled for this profile.
 *
 * Field: ::VTSS_EACL_VCAP_ES2_KEY_SEL . KEY_ENA
 */
#define  VTSS_F_EACL_VCAP_ES2_KEY_SEL_KEY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_VCAP_ES2_KEY_SEL_KEY_ENA  VTSS_BIT(0)
#define  VTSS_X_EACL_VCAP_ES2_KEY_SEL_KEY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a EACL:CNT_TBL
 *
 * VCAP_ES2 counter table
 */


/**
 * \brief VCAP_ES2 counter
 *
 * \details
 * The CNT_TBL counters count number of hits in VCAP_ES2. For each of the
 * two VCAP_ES2 lookups, a VCAP match results in the associated counter
 * being incremented using the VCAP_ES2 action CNT_ID as index.
 *
 * Register: \a EACL:CNT_TBL:ES2_CNT
 *
 * @param gi Replicator: x_FFL_EACL_NUM_CNT (??), 0-511
 */
#define VTSS_EACL_ES2_CNT(gi)                VTSS_IOREG_IX(VTSS_TO_EACL,0xe00,gi,1,0,0)

/**
 * \brief
 * VCAP_ES2 counter value.
 *
 * \details
 * Field: ::VTSS_EACL_ES2_CNT . CNT
 */
#define  VTSS_F_EACL_ES2_CNT_CNT(x)           (x)
#define  VTSS_M_EACL_ES2_CNT_CNT              0xffffffff
#define  VTSS_X_EACL_ES2_CNT_CNT(x)           (x)

/**
 * Register Group: \a EACL:POL_CFG
 *
 * Various policer controls
 */


/**
 * \brief Configuration of EACL policer rates
 *
 * \details
 * Register: \a EACL:POL_CFG:POL_EACL_RATE_CFG
 *
 * @param ri Replicator: x_FFL_EACL_POL_TOT_NUM_LB (??), 0-31
 */
#define VTSS_EACL_POL_EACL_RATE_CFG(ri)      VTSS_IOREG(VTSS_TO_EACL,0x1600 + (ri))

/**
 * \brief
 * EACL policer leaky bucket rate.Regarding unit, refer to
 * POL_UPD_INT_CFG.POL_UPD_INT.Related
 * parameters:POL_EACL_CTRL.FRAME_RATE_ENASee
 * also:EACL:POL_CFG:POL_UPD_INT_CFG.POL_UPD_INTEACL:POL_CFG:POL_EACL_CTRL.
 * FRAME_RATE_ENA
 *
 * \details
 * When POL_EACL_CTRL.FRAME_RATE_ENA is disabled, policing is performed in
 * bits per second (bps).
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 1 x <unit> bps
 * n: Rate = n x <unit> bps
 *
 * When POL_EACL_CTRL.FRAME_RATE_ENA is enabled, policing is performed in
 * frames per second (fps).
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = <unit> fps
 * n: Rate = n x <unit> fps
 *
 * Field: ::VTSS_EACL_POL_EACL_RATE_CFG . EACL_RATE
 */
#define  VTSS_F_EACL_POL_EACL_RATE_CFG_EACL_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_EACL_POL_EACL_RATE_CFG_EACL_RATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_EACL_POL_EACL_RATE_CFG_EACL_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)


/**
 * \brief Configuration of EACL policer thresholds
 *
 * \details
 * Register: \a EACL:POL_CFG:POL_EACL_THRES_CFG
 *
 * @param ri Replicator: x_FFL_EACL_POL_TOT_NUM_LB (??), 0-31
 */
#define VTSS_EACL_POL_EACL_THRES_CFG(ri)     VTSS_IOREG(VTSS_TO_EACL,0x1640 + (ri))

/**
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 8192
 * bytes.Related parameters:POL_EACL_CTRL.FRAME_RATE_ENASee
 * also:EACL:POL_CFG:POL_EACL_CTRL.FRAME_RATE_ENA
 *
 * \details
 * When POL_EACL_CTRL.FRAME_RATE_ENA is disabled burst capacity is
 * configured in steps of 8192 bytes.
 * 0: Always closed
 * 1: Burst capacity = 8192 bytes
 * n: Burst capacity = n x 8192 bytes
 * 63: Burst capacity = 516096 bytes
 *
 * When POL_EACL_CTRL.FRAME_RATE_ENA is enabled burst capacity is
 * configured in steps of 8192/2504 frames.
 * 0: Always closed
 * 1: Burst capacity = 1 x 8192/2504 frames
 * n: Burst capacity = n x 8192/2504 frames
 * 63: Burst capacity = 206 frames
 *
 * Field: ::VTSS_EACL_POL_EACL_THRES_CFG . EACL_THRES
 */
#define  VTSS_F_EACL_POL_EACL_THRES_CFG_EACL_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_EACL_POL_EACL_THRES_CFG_EACL_THRES     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_EACL_POL_EACL_THRES_CFG_EACL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Configuration of EACL policer parameters
 *
 * \details
 * Only frames with an VCAP ES2 action with POLICE_ENA=1 are subject to
 * EACL policing. The policer index is then controlled by the VCAP ES2
 * action field POLICE_IDX.
 *
 * Register: \a EACL:POL_CFG:POL_EACL_CTRL
 *
 * @param ri Replicator: x_FFL_EACL_POL_TOT_NUM_LB (??), 0-31
 */
#define VTSS_EACL_POL_EACL_CTRL(ri)          VTSS_IOREG(VTSS_TO_EACL,0x1680 + (ri))

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
 * Field: ::VTSS_EACL_POL_EACL_CTRL . DP_BYPASS_LVL
 */
#define  VTSS_F_EACL_POL_EACL_CTRL_DP_BYPASS_LVL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_EACL_POL_EACL_CTRL_DP_BYPASS_LVL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_EACL_POL_EACL_CTRL_DP_BYPASS_LVL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.Setting GAP_VALUE to 20
 * corresponds to a line-rate measurement, since on the line each frame
 * will be preceded by 12 bytes of IFG and 8 bytes of preamble.Setting
 * GAP_VALUE to 0 corresponds to a data-rate measurement.
 *
 * \details
 * 0x40: -64
 * 0x41: -63
 *    ...
 * 0x7F: -1
 * 0x00: 0
 * 0x01: 1
 *    ...
 * 0x3F: 63
 *
 * Field: ::VTSS_EACL_POL_EACL_CTRL . GAP_VALUE
 */
#define  VTSS_F_EACL_POL_EACL_CTRL_GAP_VALUE(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_EACL_POL_EACL_CTRL_GAP_VALUE     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_EACL_POL_EACL_CTRL_GAP_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * Configures the frame types to be policed by the policer. Each bit in the
 * mask enables a specific frame type.If a frame does not match any of the
 * enabled frame types, then the frame bypasses the policer (never
 * discarded and the bucket is not updated with the frame).
 *
 * \details
 * '00': Police frame
 * '01': Only frames to front ports are triggering policer and only front
 * port destinations are policed.
 * '10': Frames to CPU are triggering policer and only CPU destinations are
 * policed.
 * '11': Frames to front ports and/or CPU are triggering policer and being
 * policed.
 *
 * Field: ::VTSS_EACL_POL_EACL_CTRL . EACL_TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_EACL_POL_EACL_CTRL_EACL_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_EACL_POL_EACL_CTRL_EACL_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_EACL_POL_EACL_CTRL_EACL_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Enables frame rate mode for the EACL policer, where policer rates are
 * measured in frames per second instead of bits per second.
 *
 * \details
 * 0: Rates measured in bits per second
 * 1: Rates measured in frames per second
 *
 * Field: ::VTSS_EACL_POL_EACL_CTRL . FRAME_RATE_ENA
 */
#define  VTSS_F_EACL_POL_EACL_CTRL_FRAME_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_POL_EACL_CTRL_FRAME_RATE_ENA  VTSS_BIT(0)
#define  VTSS_X_EACL_POL_EACL_CTRL_FRAME_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Miscellaneous policer parameters
 *
 * \details
 * Register: \a EACL:POL_CFG:POL_EACL_CFG
 */
#define VTSS_EACL_POL_EACL_CFG               VTSS_IOREG(VTSS_TO_EACL,0x16c0)

/**
 * \brief
 * If set, frames that are remarked by a policer are counted as dropped.
 * I.e. the respective frames will have bit 2 or bit 3 set in the event
 * mask.Related parameters:EACL::STAT_GLOBAL_EVENT_MASK.GLOBAL_EVENT_MASK
 *
 * \details
 * 0: Marked frames will be counted as not discarded.
 * 1: Marked frames will be counted as discarded.
 *
 * Field: ::VTSS_EACL_POL_EACL_CFG . EACL_CNT_MARKED_AS_DROPPED
 */
#define  VTSS_F_EACL_POL_EACL_CFG_EACL_CNT_MARKED_AS_DROPPED(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_EACL_POL_EACL_CFG_EACL_CNT_MARKED_AS_DROPPED  VTSS_BIT(5)
#define  VTSS_X_EACL_POL_EACL_CFG_EACL_CNT_MARKED_AS_DROPPED(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If set, all EACL policer will always allow to generate a copied front
 * port copy even though the original front port copy is policed.This does
 * only apply to actions with fwd_mode set to REDIR or COPY.
 *
 * \details
 * 0: No CPU copy is done when the original FP copy is discarded.
 * 1: CPU copy is done although the original front port copy is discarded
 * due to policing.
 *
 * Field: ::VTSS_EACL_POL_EACL_CFG . EACL_ALLOW_FP_COPY
 */
#define  VTSS_F_EACL_POL_EACL_CFG_EACL_ALLOW_FP_COPY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_EACL_POL_EACL_CFG_EACL_ALLOW_FP_COPY  VTSS_BIT(4)
#define  VTSS_X_EACL_POL_EACL_CFG_EACL_ALLOW_FP_COPY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * If set, all EACL policer will always allow to generate a CPU copy even
 * though the original front port copy is policed.This does not apply to
 * packets that where directly targeted towards a CPU port.
 *
 * \details
 * 0: No CPU copy is done when the original FP copy is discarded.
 * 1: CPU copy is done although the original front port copy is discarded
 * due to policing.
 *
 * Field: ::VTSS_EACL_POL_EACL_CFG . EACL_ALLOW_CPU_COPY
 */
#define  VTSS_F_EACL_POL_EACL_CFG_EACL_ALLOW_CPU_COPY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_EACL_POL_EACL_CFG_EACL_ALLOW_CPU_COPY  VTSS_BIT(3)
#define  VTSS_X_EACL_POL_EACL_CFG_EACL_ALLOW_CPU_COPY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * If set, all EACL policer buckets are forced closed (all frames are
 * policed and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details
 * 0: Normal operation
 * 1: All EACL policer buckets are closed
 *
 * Field: ::VTSS_EACL_POL_EACL_CFG . EACL_FORCE_CLOSE
 */
#define  VTSS_F_EACL_POL_EACL_CFG_EACL_FORCE_CLOSE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_EACL_POL_EACL_CFG_EACL_FORCE_CLOSE  VTSS_BIT(2)
#define  VTSS_X_EACL_POL_EACL_CFG_EACL_FORCE_CLOSE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If set, all EACL policer buckets are forced open (no frames are policed
 * and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details
 * 0: Normal operation
 * 1: All EACL policer buckets are forced open
 *
 * Field: ::VTSS_EACL_POL_EACL_CFG . EACL_FORCE_OPEN
 */
#define  VTSS_F_EACL_POL_EACL_CFG_EACL_FORCE_OPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_POL_EACL_CFG_EACL_FORCE_OPEN  VTSS_BIT(1)
#define  VTSS_X_EACL_POL_EACL_CFG_EACL_FORCE_OPEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If set, all EACL policers are initialized and buckets are open. The bit
 * must be cleared for normal operation to resume.
 *
 * \details
 * 0: Normal operation
 * 1: Initialization
 *
 * Field: ::VTSS_EACL_POL_EACL_CFG . EACL_FORCE_INIT
 */
#define  VTSS_F_EACL_POL_EACL_CFG_EACL_FORCE_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_POL_EACL_CFG_EACL_FORCE_INIT  VTSS_BIT(0)
#define  VTSS_X_EACL_POL_EACL_CFG_EACL_FORCE_INIT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Policer update interval
 *
 * \details
 * Configure the leaky bucket update interval for the EACL policers.
 * This configuration affects the policing rate unit for these policers.
 * By setting this parameter to a clock frequency dependent value, the rate
 * unit can be kept identical/similar across different system clock
 * frequencies.
 *
 * Register: \a EACL:POL_CFG:POL_UPD_INT_CFG
 */
#define VTSS_EACL_POL_UPD_INT_CFG            VTSS_IOREG(VTSS_TO_EACL,0x16c1)

/**
 * \brief
 * This configuration will affect the policing rate unit for the EACL
 * policers. The rate unit is calculated as follows:Rate unit = SYS_CLK /
 * (POL_UPD_INT * 16) bpsRecommended value and corresponding rate unit:160
 * MHz: 400 => 25000 bps320 MHz: 800 => 25000 bpsFrame rate mode is also
 * affected be this setting. The default frame rate unit is 10fps (frames
 * per second). This is scaled according to this formula:Frame rate = 10
 * fps * (Rate unit / 25000 bps)
 *
 * \details
 * 0-31: Not allowed
 * N: Update interval

 *
 * Field: ::VTSS_EACL_POL_UPD_INT_CFG . POL_UPD_INT
 */
#define  VTSS_F_EACL_POL_UPD_INT_CFG_POL_UPD_INT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EACL_POL_UPD_INT_CFG_POL_UPD_INT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EACL_POL_UPD_INT_CFG_POL_UPD_INT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Policer diagnostic information
 *
 * \details
 * Register: \a EACL:POL_CFG:POL_EACL_STICKY
 */
#define VTSS_EACL_POL_EACL_STICKY            VTSS_IOREG(VTSS_TO_EACL,0x16c2)

/**
 * \brief
 * Set if an EACL policer is active.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details
 * 0: No event has occurred
 * 1: EACL policer is active (frames added to leaky buckets)
 *
 * Field: ::VTSS_EACL_POL_EACL_STICKY . POL_EACL_ACTIVE_STICKY
 */
#define  VTSS_F_EACL_POL_EACL_STICKY_POL_EACL_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_EACL_POL_EACL_STICKY_POL_EACL_ACTIVE_STICKY  VTSS_BIT(3)
#define  VTSS_X_EACL_POL_EACL_STICKY_POL_EACL_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if frame has been remarked due to EACL policer.Bit is cleared by
 * writing a 1 to this position.
 *
 * \details
 * 0: No event has occurred
 * 1: EACL policer drop event has occurred
 *
 * Field: ::VTSS_EACL_POL_EACL_STICKY . POL_EACL_REMARK_STICKY
 */
#define  VTSS_F_EACL_POL_EACL_STICKY_POL_EACL_REMARK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_EACL_POL_EACL_STICKY_POL_EACL_REMARK_STICKY  VTSS_BIT(2)
#define  VTSS_X_EACL_POL_EACL_STICKY_POL_EACL_REMARK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set if frame has been dropped due to EACL policer.Bit is cleared by
 * writing a 1 to this position.
 *
 * \details
 * 0: No event has occurred
 * 1: EACL policer drop event has occurred
 *
 * Field: ::VTSS_EACL_POL_EACL_STICKY . POL_EACL_DROP_STICKY
 */
#define  VTSS_F_EACL_POL_EACL_STICKY_POL_EACL_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_POL_EACL_STICKY_POL_EACL_DROP_STICKY  VTSS_BIT(1)
#define  VTSS_X_EACL_POL_EACL_STICKY_POL_EACL_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if an EACL policer has been bypassed due to a frame's DP level or
 * traffic type mask.Bit is cleared by writing a 1 to this position.
 *
 * \details
 * 0: No event has occurred
 * 1: EACL policer has been bypassed
 *
 * Field: ::VTSS_EACL_POL_EACL_STICKY . POL_EACL_BYPASS_STICKY
 */
#define  VTSS_F_EACL_POL_EACL_STICKY_POL_EACL_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_POL_EACL_STICKY_POL_EACL_BYPASS_STICKY  VTSS_BIT(0)
#define  VTSS_X_EACL_POL_EACL_STICKY_POL_EACL_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a EACL:ES2_STICKY
 *
 * Sticky diagnostic status
 */


/**
 * \brief Sticky bits register for events generated by VCAP_ES2
 *
 * \details
 * Register: \a EACL:ES2_STICKY:SEC_LOOKUP_STICKY
 *
 * @param ri Register: SEC_LOOKUP_STICKY (??), 0-1
 */
#define VTSS_EACL_SEC_LOOKUP_STICKY(ri)      VTSS_IOREG(VTSS_TO_EACL,0xc64 + (ri))

/**
 * \brief
 * This sticky bit signals an IP_7TUPLE lookup was performed.
 *
 * \details
 * Field: ::VTSS_EACL_SEC_LOOKUP_STICKY . SEC_TYPE_IP_7TUPLE_STICKY
 */
#define  VTSS_F_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP_7TUPLE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP_7TUPLE_STICKY  VTSS_BIT(7)
#define  VTSS_X_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP_7TUPLE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This sticky bit signals an IP6_VID lookup was performed.
 *
 * \details
 * Field: ::VTSS_EACL_SEC_LOOKUP_STICKY . SEC_TYPE_IP6_VID_STICKY
 */
#define  VTSS_F_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_VID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_VID_STICKY  VTSS_BIT(6)
#define  VTSS_X_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_VID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This sticky bit signals an IP6_STD lookup was performed.
 *
 * \details
 * Field: ::VTSS_EACL_SEC_LOOKUP_STICKY . SEC_TYPE_IP6_STD_STICKY
 */
#define  VTSS_F_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_STD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_STD_STICKY  VTSS_BIT(5)
#define  VTSS_X_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_STD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * This sticky bit signals an IP4_TCPUDP lookup was performed.
 *
 * \details
 * Field: ::VTSS_EACL_SEC_LOOKUP_STICKY . SEC_TYPE_IP4_TCPUDP_STICKY
 */
#define  VTSS_F_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_TCPUDP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_TCPUDP_STICKY  VTSS_BIT(4)
#define  VTSS_X_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_TCPUDP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * This sticky bit signals an IP4_VID lookup was performed.
 *
 * \details
 * Field: ::VTSS_EACL_SEC_LOOKUP_STICKY . SEC_TYPE_IP4_VID_STICKY
 */
#define  VTSS_F_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_VID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_VID_STICKY  VTSS_BIT(3)
#define  VTSS_X_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_VID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This sticky bit signals an IP4_OTHER lookup was performed.
 *
 * \details
 * Field: ::VTSS_EACL_SEC_LOOKUP_STICKY . SEC_TYPE_IP4_OTHER_STICKY
 */
#define  VTSS_F_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_OTHER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_OTHER_STICKY  VTSS_BIT(2)
#define  VTSS_X_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_OTHER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This sticky bit signals an ARP lookup was performed.
 *
 * \details
 * Field: ::VTSS_EACL_SEC_LOOKUP_STICKY . SEC_TYPE_ARP_STICKY
 */
#define  VTSS_F_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_ARP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_ARP_STICKY  VTSS_BIT(1)
#define  VTSS_X_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_ARP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This sticky bit signals a MAC_ETYPE lookup was performed.
 *
 * \details
 * Field: ::VTSS_EACL_SEC_LOOKUP_STICKY . SEC_TYPE_MAC_ETYPE_STICKY
 */
#define  VTSS_F_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_ETYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_ETYPE_STICKY  VTSS_BIT(0)
#define  VTSS_X_EACL_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_ETYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a EACL:DBG_STICKY
 *
 * Sticky registers intended for debug.
 */


/**
 * \brief Sticky bits register for events generated from policer stats fifo.
 *
 * \details
 * Register: \a EACL:DBG_STICKY:DBG_STICKY
 */
#define VTSS_EACL_DBG_STICKY                 VTSS_IOREG(VTSS_TO_EACL,0xc66)

/**
 * \brief
 * Set if the EACL stats fifo has reached the
 * SINGLE_CYCLE_FWD_STATS_FIFO_TRESH and forces the forwarding process in
 * the QSYS to slow down to forwarding to only every 2nd cycleBit is
 * cleared by writing a 1 to this position.
 *
 * \details
 * 0: No event has occurred
 * 1: EACL policer has been bypassed
 *
 * Field: ::VTSS_EACL_DBG_STICKY . POL_STATS_FIFO_OFLW_STICKY
 */
#define  VTSS_F_EACL_DBG_STICKY_POL_STATS_FIFO_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_DBG_STICKY_POL_STATS_FIFO_OFLW_STICKY  VTSS_BIT(1)
#define  VTSS_X_EACL_DBG_STICKY_POL_STATS_FIFO_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if the EACL stats fifo has reached the
 * SINGLE_CYCLE_FWD_STATS_FIFO_TRESH and forces the forwarding process in
 * the QSYS to slow down to forwarding to only every 2nd cycleBit is
 * cleared by writing a 1 to this position.
 *
 * \details
 * 0: No event has occurred
 * 1: EACL policer has been bypassed
 *
 * Field: ::VTSS_EACL_DBG_STICKY . POL_STATS_FIFO_TRESH_REACHED_STICKY
 */
#define  VTSS_F_EACL_DBG_STICKY_POL_STATS_FIFO_TRESH_REACHED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_DBG_STICKY_POL_STATS_FIFO_TRESH_REACHED_STICKY  VTSS_BIT(0)
#define  VTSS_X_EACL_DBG_STICKY_POL_STATS_FIFO_TRESH_REACHED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a EACL:FRER_MAP
 *
 * Mapping of ISDX and egress port to FRER member stream IDs.
 */


/**
 * \brief Member stream ID associated with ISDXn-PORT0.
 *
 * \details
 * Register: \a EACL:FRER_MAP:FRER_FIRST_MEMBER
 *
 * @param gi Replicator: x_FFL_CHIP_NUM_SDX (??), 0-31
 */
#define VTSS_EACL_FRER_FIRST_MEMBER(gi)      VTSS_IOREG_IX(VTSS_TO_EACL,0xc80,gi,4,0,0)

/**
 * \brief
 * The member stream ID assigned to ISDXn-PORTx is FRER_FIRST_MEMBER + x.n
 * is the FRER_MAP index, x is in 0 to 7 range.A port set to all ones will
 * not have an stream ID assigned.Related
 * parameters:EACL:FRER_MAP:FRER_EGR_PORT.FRER_EGR_PORT0EACL:FRER_MAP:FRER_
 * EGR_PORT.FRER_EGR_PORT1EACL:FRER_MAP:FRER_EGR_PORT.FRER_EGR_PORT2EACL:FR
 * ER_MAP:FRER_EGR_PORT.FRER_EGR_PORT3
 *
 * \details
 * Field: ::VTSS_EACL_FRER_FIRST_MEMBER . FRER_FIRST_MEMBER
 */
#define  VTSS_F_EACL_FRER_FIRST_MEMBER_FRER_FIRST_MEMBER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EACL_FRER_FIRST_MEMBER_FRER_FIRST_MEMBER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EACL_FRER_FIRST_MEMBER_FRER_FIRST_MEMBER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Egress ports to be assigned a member stream ID.
 *
 * \details
 * Register: \a EACL:FRER_MAP:FRER_EGR_PORT
 *
 * @param gi Replicator: x_FFL_CHIP_NUM_SDX (??), 0-31
 * @param ri Replicator: x_FFL_EACL_FRER_EGR_PORT_REGISTERS (??), 0-1
 */
#define VTSS_EACL_FRER_EGR_PORT(gi,ri)       VTSS_IOREG_IX(VTSS_TO_EACL,0xc80,gi,4,ri,1)

/**
 * \brief
 * A frame that has been assigned the same ISDX as this register address
 * and is forwarded to the egress port matching the value in this register
 * (if not set to all ones), will be assigned member stream ID
 * FRER_FIRST_MEMBER+4*replication+0. Related
 * parameters:EACL:FRER_MAP:FRER_FIRST_MEMBER.FRER_FIRST_MEMBER
 *
 * \details
 * Field: ::VTSS_EACL_FRER_EGR_PORT . FRER_EGR_PORT0
 */
#define  VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT0(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_EACL_FRER_EGR_PORT_FRER_EGR_PORT0     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_EACL_FRER_EGR_PORT_FRER_EGR_PORT0(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/**
 * \brief
 * A frame that has been assigned the same ISDX as this register address
 * and is forwarded to the egress port matching the value in this register
 * (if not set to all ones), will be assigned member stream ID
 * FRER_FIRST_MEMBER+4*replication+1.Related
 * parameters:EACL:FRER_MAP:FRER_FIRST_MEMBER.FRER_FIRST_MEMBER
 *
 * \details
 * Field: ::VTSS_EACL_FRER_EGR_PORT . FRER_EGR_PORT1
 */
#define  VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT1(x)  VTSS_ENCODE_BITFIELD(x,14,5)
#define  VTSS_M_EACL_FRER_EGR_PORT_FRER_EGR_PORT1     VTSS_ENCODE_BITMASK(14,5)
#define  VTSS_X_EACL_FRER_EGR_PORT_FRER_EGR_PORT1(x)  VTSS_EXTRACT_BITFIELD(x,14,5)

/**
 * \brief
 * A frame that has been assigned the same ISDX as this register address
 * and is forwarded to the egress port matching the value in this register
 * (if not set to all ones), will be assigned member stream ID
 * FRER_FIRST_MEMBER+4*replication+2.Related
 * parameters:EACL:FRER_MAP:FRER_FIRST_MEMBER.FRER_FIRST_MEMBER
 *
 * \details
 * Field: ::VTSS_EACL_FRER_EGR_PORT . FRER_EGR_PORT2
 */
#define  VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT2(x)  VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_EACL_FRER_EGR_PORT_FRER_EGR_PORT2     VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_EACL_FRER_EGR_PORT_FRER_EGR_PORT2(x)  VTSS_EXTRACT_BITFIELD(x,7,5)

/**
 * \brief
 * A frame that has been assigned the same ISDX as this register address
 * and is forwarded to the egress port matching the value in this register
 * (if not set to all ones), will be assigned member stream ID
 * FRER_FIRST_MEMBER+4*replication+3.Related
 * parameters:EACL:FRER_MAP:FRER_FIRST_MEMBER.FRER_FIRST_MEMBER
 *
 * \details
 * Field: ::VTSS_EACL_FRER_EGR_PORT . FRER_EGR_PORT3
 */
#define  VTSS_F_EACL_FRER_EGR_PORT_FRER_EGR_PORT3(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_EACL_FRER_EGR_PORT_FRER_EGR_PORT3     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_EACL_FRER_EGR_PORT_FRER_EGR_PORT3(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a EACL:FRER_CFG
 *
 * Not documented
 */


/**
 * \brief FRER configuration common to all streams.
 *
 * \details
 * Register: \a EACL:FRER_CFG:FRER_CFG
 */
#define VTSS_EACL_FRER_CFG                   VTSS_IOREG(VTSS_TO_EACL,0xc67)

/**
 * \brief
 *
 *	     TicksPerSecond will be the system clock frequency divided by
 * (WATCHDOG_PRESCALER*8*256).		This is the time base for
 * RESET_TICKS. 	 Value 0 disables the watchdog. 	 Recomended
 * value for TicksPerSecond is 100.	     Related parameters:
 * TicksPerSecond as defined in 802.1CB-2017
 * EACL:FRER_CFG_COMPOUND:FRER_CFG_COMPOUND.RESET_TICKS
 * EACL:FRER_CFG_MEMBER:FRER_CFG_MEMBER.RESET_TICKS
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG . WATCHDOG_PRESCALER
 */
#define  VTSS_F_EACL_FRER_CFG_WATCHDOG_PRESCALER(x)  VTSS_ENCODE_BITFIELD(x,10,16)
#define  VTSS_M_EACL_FRER_CFG_WATCHDOG_PRESCALER     VTSS_ENCODE_BITMASK(10,16)
#define  VTSS_X_EACL_FRER_CFG_WATCHDOG_PRESCALER(x)  VTSS_EXTRACT_BITFIELD(x,10,16)

/**
 * \brief
 *
 *	     Member or compound stream handle of the state to be accessed.
 *	   Related parameters:
 * EACL:FRER_STA_COMPOUND:FRER_STA_COMPOUND.SEQ_NO
 * EACL:FRER_STA_COMPOUND:FRER_STA_COMPOUND.TICKS
 * EACL:FRER_STA_COMPOUND:FRER_STA_COMPOUND.TAKE_ANY
 * EACL:FRER_STA_COMPOUND:FRER_HST_COMPOUND.HISTORY
 * EACL:FRER_STA_MEMBER:FRER_STA_MEMBER.SEQ_NO
 * EACL:FRER_STA_MEMBER:FRER_STA_MEMBER.TICKS
 * EACL:FRER_STA_MEMBER:FRER_STA_MEMBER.TAKE_ANY
 * EACL:FRER_STA_MEMBER:FRER_HST_MEMBER.HISTORY
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG . ADDR
 */
#define  VTSS_F_EACL_FRER_CFG_ADDR(x)         VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EACL_FRER_CFG_ADDR            VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EACL_FRER_CFG_ADDR(x)         VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EACL:FRER_CFG_COMPOUND
 *
 * Not documented
 */


/**
 * \brief FRER configuration for compound streams. One entry per each compound stream.
 *
 * \details
 * Register: \a EACL:FRER_CFG_COMPOUND:FRER_CFG_COMPOUND
 *
 * @param gi Replicator: x_FFL_EACL_FRER_COMPOUND_STREAMS (??), 0-127
 */
#define VTSS_EACL_FRER_CFG_COMPOUND(gi)      VTSS_IOREG_IX(VTSS_TO_EACL,0x1500,gi,1,0,0)

/**
 * \brief
 *
 *	     A Boolean value specifying whether packets with no
 * sequence_number subparameter are to be accepted.	     Should be set
 * to 1 when VECTOR_ALGORITHM is 0.	     Applies to the sequence
 * recovery function.	       Related parameters:
 * frerSeqRcvyTakeNoSequence as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_COMPOUND . TAKE_NO_SEQUENCE
 */
#define  VTSS_F_EACL_FRER_CFG_COMPOUND_TAKE_NO_SEQUENCE(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_EACL_FRER_CFG_COMPOUND_TAKE_NO_SEQUENCE  VTSS_BIT(20)
#define  VTSS_X_EACL_FRER_CFG_COMPOUND_TAKE_NO_SEQUENCE(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 *
 *	     Use Vector_Alg for sequence recovery algorithm instead of
 * Match_Alg.	       Applies to the sequence recovery function.
 * Related parameters:		frerSeqRcvyAlgorithm as defined in
 * 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_COMPOUND . VECTOR_ALGORITHM
 */
#define  VTSS_F_EACL_FRER_CFG_COMPOUND_VECTOR_ALGORITHM(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_EACL_FRER_CFG_COMPOUND_VECTOR_ALGORITHM  VTSS_BIT(19)
#define  VTSS_X_EACL_FRER_CFG_COMPOUND_VECTOR_ALGORITHM(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 *
 *	     An integer specifying how many bits of the SequenceHistory
 * variable are to be used.	     Applies to the sequence recovery
 * function.	      Related parameters:	   frerSeqRcvyHistoryLength
 * as defined in 802.1CB-2017
 *
 * \details
 *
 *	     0: Not allowed
 *	     n: History length = n+1

 *
 * Field: ::VTSS_EACL_FRER_CFG_COMPOUND . HISTORY_LENGTH
 */
#define  VTSS_F_EACL_FRER_CFG_COMPOUND_HISTORY_LENGTH(x)  VTSS_ENCODE_BITFIELD(x,14,5)
#define  VTSS_M_EACL_FRER_CFG_COMPOUND_HISTORY_LENGTH     VTSS_ENCODE_BITMASK(14,5)
#define  VTSS_X_EACL_FRER_CFG_COMPOUND_HISTORY_LENGTH(x)  VTSS_EXTRACT_BITFIELD(x,14,5)

/**
 * \brief
 *
 *	     An integer specifying after how many ticks the reset watchdog
 * should be triggered. 	 Applies to the sequence recovery function.
 *	    Related parameters: 	 frerSeqRcvyResetMSec as defined in
 * 802.1CB-2017 	 EACL:FRER_CFG:FRER_CFG.WATCHDOG_PRESCALER
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_COMPOUND . RESET_TICKS
 */
#define  VTSS_F_EACL_FRER_CFG_COMPOUND_RESET_TICKS(x)  VTSS_ENCODE_BITFIELD(x,2,12)
#define  VTSS_M_EACL_FRER_CFG_COMPOUND_RESET_TICKS     VTSS_ENCODE_BITMASK(2,12)
#define  VTSS_X_EACL_FRER_CFG_COMPOUND_RESET_TICKS(x)  VTSS_EXTRACT_BITFIELD(x,2,12)

/**
 * \brief
 *
 *	     Reset the sequence recovery function.	    Related
 * parameters:		frerSeqRcvyReset as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_COMPOUND . RESET
 */
#define  VTSS_F_EACL_FRER_CFG_COMPOUND_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_FRER_CFG_COMPOUND_RESET  VTSS_BIT(1)
#define  VTSS_X_EACL_FRER_CFG_COMPOUND_RESET(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 *
 *	     Instantiate a sequence recovery function for this compound
 * stream.	    Do not set together with generation.	  Related
 * parameters:		frerSeqRcvyStreamList as defined in 802.1CB-2017
 *	 frerSeqRcvyPortList as defined in 802.1CB-2017
 * ANA_AC:FRER_GEN:FRER_GEN.ENABLE
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_COMPOUND . ENABLE
 */
#define  VTSS_F_EACL_FRER_CFG_COMPOUND_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_FRER_CFG_COMPOUND_ENABLE  VTSS_BIT(0)
#define  VTSS_X_EACL_FRER_CFG_COMPOUND_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a EACL:FRER_CFG_MEMBER
 *
 * Not documented
 */


/**
 * \brief FRER configuration for member streams. One entry per each member stream.
 *
 * \details
 * Register: \a EACL:FRER_CFG_MEMBER:FRER_CFG_MEMBER
 *
 * @param gi Replicator: x_FFL_EACL_FRER_MEMBER_STREAMS (??), 0-255
 */
#define VTSS_EACL_FRER_CFG_MEMBER(gi)        VTSS_IOREG_IX(VTSS_TO_EACL,0xd00,gi,1,0,0)

/**
 * \brief
 *
 *	     A Boolean value specifying whether packets with no
 * sequence_number subparameter are to be accepted.	     Should be set
 * to 1 when VECTOR_ALGORITHM is 0.	     Applies to the individual
 * recovery function.	       Related parameters:
 * frerSeqRcvyTakeNoSequence as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_MEMBER . TAKE_NO_SEQUENCE
 */
#define  VTSS_F_EACL_FRER_CFG_MEMBER_TAKE_NO_SEQUENCE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_EACL_FRER_CFG_MEMBER_TAKE_NO_SEQUENCE  VTSS_BIT(29)
#define  VTSS_X_EACL_FRER_CFG_MEMBER_TAKE_NO_SEQUENCE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 *
 *	     Use Vector_Alg for sequence recovery algorithm instead of
 * Match_Alg.	       Applies to the individual recovery function.
 *  Related parameters: 	 frerSeqRcvyAlgorithm as defined in
 * 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_MEMBER . VECTOR_ALGORITHM
 */
#define  VTSS_F_EACL_FRER_CFG_MEMBER_VECTOR_ALGORITHM(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_EACL_FRER_CFG_MEMBER_VECTOR_ALGORITHM  VTSS_BIT(28)
#define  VTSS_X_EACL_FRER_CFG_MEMBER_VECTOR_ALGORITHM(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 *
 *	     An integer specifying how many bits of the SequenceHistory
 * variable are to be used.	     Applies to the individual recovery
 * function.	      Related parameters:	   frerSeqRcvyHistoryLength
 * as defined in 802.1CB-2017
 *
 * \details
 *
 *	     0: Not allowed
 *	     n: History length = n+1

 *
 * Field: ::VTSS_EACL_FRER_CFG_MEMBER . HISTORY_LENGTH
 */
#define  VTSS_F_EACL_FRER_CFG_MEMBER_HISTORY_LENGTH(x)  VTSS_ENCODE_BITFIELD(x,23,5)
#define  VTSS_M_EACL_FRER_CFG_MEMBER_HISTORY_LENGTH     VTSS_ENCODE_BITMASK(23,5)
#define  VTSS_X_EACL_FRER_CFG_MEMBER_HISTORY_LENGTH(x)  VTSS_EXTRACT_BITFIELD(x,23,5)

/**
 * \brief
 *
 *	     An integer specifying after how many ticks the reset watchdog
 * should be triggered. 	 Applies to the individual recovery
 * function.	      Related parameters:	   frerSeqRcvyResetMSec as
 * defined in 802.1CB-2017
 * EACL:FRER_CFG:FRER_CFG.WATCHDOG_PRESCALER
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_MEMBER . RESET_TICKS
 */
#define  VTSS_F_EACL_FRER_CFG_MEMBER_RESET_TICKS(x)  VTSS_ENCODE_BITFIELD(x,11,12)
#define  VTSS_M_EACL_FRER_CFG_MEMBER_RESET_TICKS     VTSS_ENCODE_BITMASK(11,12)
#define  VTSS_X_EACL_FRER_CFG_MEMBER_RESET_TICKS(x)  VTSS_EXTRACT_BITFIELD(x,11,12)

/**
 * \brief
 *
 *	     Reset the individual recovery function.	      Related
 * parameters:		frerSeqRcvyReset as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_MEMBER . RESET
 */
#define  VTSS_F_EACL_FRER_CFG_MEMBER_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_EACL_FRER_CFG_MEMBER_RESET    VTSS_BIT(10)
#define  VTSS_X_EACL_FRER_CFG_MEMBER_RESET(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 *
 *	     Instantiate an individual recovery function for this member
 * stream.	    Do not set together with generation.	  Related
 * parameters:		frerSeqRcvyStreamList as defined in 802.1CB-2017
 *	 frerSeqRcvyPortList as defined in 802.1CB-2017
 * ANA_AC:FRER_GEN:FRER_GEN.ENABLE
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_MEMBER . ENABLE
 */
#define  VTSS_F_EACL_FRER_CFG_MEMBER_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_EACL_FRER_CFG_MEMBER_ENABLE   VTSS_BIT(9)
#define  VTSS_X_EACL_FRER_CFG_MEMBER_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 *
 *	     Compound stream to which this member stream pertains.
 * Related parameters:
 * EACL:FRER_CFG_COMPOUND:FRER_CFG_COMPOUND.ENABLE
 *
 * \details
 * Field: ::VTSS_EACL_FRER_CFG_MEMBER . COMPOUND_HANDLE
 */
#define  VTSS_F_EACL_FRER_CFG_MEMBER_COMPOUND_HANDLE(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_EACL_FRER_CFG_MEMBER_COMPOUND_HANDLE     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_EACL_FRER_CFG_MEMBER_COMPOUND_HANDLE(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a EACL:FRER_STA_COMPOUND
 *
 * FRER internal state
 */


/**
 * \brief FRER internal state for compound streams
 *
 * \details
 * Register: \a EACL:FRER_STA_COMPOUND:FRER_STA_COMPOUND
 */
#define VTSS_EACL_FRER_STA_COMPOUND          VTSS_IOREG(VTSS_TO_EACL,0xc60)

/**
 * \brief
 *
 *	     RecovSeqNum as defined in 802.1CB-2017	     Related
 * parameters:		EACL:FRER_CFG:FRER_CFG.ADDR
 *
 * \details
 * Field: ::VTSS_EACL_FRER_STA_COMPOUND . SEQ_NO
 */
#define  VTSS_F_EACL_FRER_STA_COMPOUND_SEQ_NO(x)  VTSS_ENCODE_BITFIELD(x,13,16)
#define  VTSS_M_EACL_FRER_STA_COMPOUND_SEQ_NO     VTSS_ENCODE_BITMASK(13,16)
#define  VTSS_X_EACL_FRER_STA_COMPOUND_SEQ_NO(x)  VTSS_EXTRACT_BITFIELD(x,13,16)

/**
 * \brief
 *
 *	     RemainingTicks as defined in 802.1CB-2017		Related
 * parameters:		EACL:FRER_CFG:FRER_CFG.ADDR
 *
 * \details
 * Field: ::VTSS_EACL_FRER_STA_COMPOUND . TICKS
 */
#define  VTSS_F_EACL_FRER_STA_COMPOUND_TICKS(x)  VTSS_ENCODE_BITFIELD(x,1,12)
#define  VTSS_M_EACL_FRER_STA_COMPOUND_TICKS     VTSS_ENCODE_BITMASK(1,12)
#define  VTSS_X_EACL_FRER_STA_COMPOUND_TICKS(x)  VTSS_EXTRACT_BITFIELD(x,1,12)

/**
 * \brief
 *
 *	     TakeAny as defined in 802.1CB-2017 	 Related
 * parameters:		EACL:FRER_CFG:FRER_CFG.ADDR
 *
 * \details
 * Field: ::VTSS_EACL_FRER_STA_COMPOUND . TAKE_ANY
 */
#define  VTSS_F_EACL_FRER_STA_COMPOUND_TAKE_ANY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_FRER_STA_COMPOUND_TAKE_ANY  VTSS_BIT(0)
#define  VTSS_X_EACL_FRER_STA_COMPOUND_TAKE_ANY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief FRER internal state for compound streams
 *
 * \details
 * Register: \a EACL:FRER_STA_COMPOUND:FRER_HST_COMPOUND
 */
#define VTSS_EACL_FRER_HST_COMPOUND          VTSS_IOREG(VTSS_TO_EACL,0xc61)

/**
 * \brief
 *
 *	     SequenceHistory as defined in 802.1CB-2017 	 Related
 * parameters:		EACL:FRER_CFG:FRER_CFG.ADDR
 *
 * \details
 * Field: ::VTSS_EACL_FRER_HST_COMPOUND . HISTORY
 */
#define  VTSS_F_EACL_FRER_HST_COMPOUND_HISTORY(x)  (x)
#define  VTSS_M_EACL_FRER_HST_COMPOUND_HISTORY     0xffffffff
#define  VTSS_X_EACL_FRER_HST_COMPOUND_HISTORY(x)  (x)

/**
 * Register Group: \a EACL:FRER_STA_MEMBER
 *
 * Not documented
 */


/**
 * \brief FRER internal state for member streams
 *
 * \details
 * Register: \a EACL:FRER_STA_MEMBER:FRER_STA_MEMBER
 */
#define VTSS_EACL_FRER_STA_MEMBER            VTSS_IOREG(VTSS_TO_EACL,0xc62)

/**
 * \brief
 *
 *	     RecovSeqNum as defined in 802.1CB-2017	     Related
 * parameters:		EACL:FRER_CFG:FRER_CFG.ADDR
 *
 * \details
 * Field: ::VTSS_EACL_FRER_STA_MEMBER . SEQ_NO
 */
#define  VTSS_F_EACL_FRER_STA_MEMBER_SEQ_NO(x)  VTSS_ENCODE_BITFIELD(x,13,16)
#define  VTSS_M_EACL_FRER_STA_MEMBER_SEQ_NO     VTSS_ENCODE_BITMASK(13,16)
#define  VTSS_X_EACL_FRER_STA_MEMBER_SEQ_NO(x)  VTSS_EXTRACT_BITFIELD(x,13,16)

/**
 * \brief
 *
 *	     RemainingTicks as defined in 802.1CB-2017		Related
 * parameters:		EACL:FRER_CFG:FRER_CFG.ADDR
 *
 * \details
 * Field: ::VTSS_EACL_FRER_STA_MEMBER . TICKS
 */
#define  VTSS_F_EACL_FRER_STA_MEMBER_TICKS(x)  VTSS_ENCODE_BITFIELD(x,1,12)
#define  VTSS_M_EACL_FRER_STA_MEMBER_TICKS     VTSS_ENCODE_BITMASK(1,12)
#define  VTSS_X_EACL_FRER_STA_MEMBER_TICKS(x)  VTSS_EXTRACT_BITFIELD(x,1,12)

/**
 * \brief
 *
 *	     TakeAny as defined in 802.1CB-2017 	 Related
 * parameters:		EACL:FRER_CFG:FRER_CFG.ADDR
 *
 * \details
 * Field: ::VTSS_EACL_FRER_STA_MEMBER . TAKE_ANY
 */
#define  VTSS_F_EACL_FRER_STA_MEMBER_TAKE_ANY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_FRER_STA_MEMBER_TAKE_ANY  VTSS_BIT(0)
#define  VTSS_X_EACL_FRER_STA_MEMBER_TAKE_ANY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief FRER internal state for member streams
 *
 * \details
 * Register: \a EACL:FRER_STA_MEMBER:FRER_HST_MEMBER
 */
#define VTSS_EACL_FRER_HST_MEMBER            VTSS_IOREG(VTSS_TO_EACL,0xc63)

/**
 * \brief
 *
 *	     SequenceHistory as defined in 802.1CB-2017 	 Related
 * parameters:		EACL:FRER_CFG:FRER_CFG.ADDR
 *
 * \details
 * Field: ::VTSS_EACL_FRER_HST_MEMBER . HISTORY
 */
#define  VTSS_F_EACL_FRER_HST_MEMBER_HISTORY(x)  (x)
#define  VTSS_M_EACL_FRER_HST_MEMBER_HISTORY     0xffffffff
#define  VTSS_X_EACL_FRER_HST_MEMBER_HISTORY(x)  (x)

/**
 * Register Group: \a EACL:FRER_CNT_COMPOUND
 *
 * FRER counters for compound streams. One entry per each compound stream.
 */


/**
 * \brief frerCpsSeqRcvyResets
 *
 * \details
 * Register: \a EACL:FRER_CNT_COMPOUND:CNT_COMPOUND_RESETS
 *
 * @param gi Replicator: x_FFL_EACL_FRER_COMPOUND_STREAMS (??), 0-127
 */
#define VTSS_EACL_CNT_COMPOUND_RESETS(gi)    VTSS_IOREG_IX(VTSS_TO_EACL,0x1000,gi,8,0,0)

/**
 * \brief
 * frerCpsSeqRcvyResets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_COMPOUND_RESETS . CNT_RESETS
 */
#define  VTSS_F_EACL_CNT_COMPOUND_RESETS_CNT_RESETS(x)  (x)
#define  VTSS_M_EACL_CNT_COMPOUND_RESETS_CNT_RESETS     0xffffffff
#define  VTSS_X_EACL_CNT_COMPOUND_RESETS_CNT_RESETS(x)  (x)


/**
 * \brief frerCpsSeqRcvyTaglessPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_COMPOUND:CNT_COMPOUND_TAGLESS
 *
 * @param gi Replicator: x_FFL_EACL_FRER_COMPOUND_STREAMS (??), 0-127
 */
#define VTSS_EACL_CNT_COMPOUND_TAGLESS(gi)   VTSS_IOREG_IX(VTSS_TO_EACL,0x1000,gi,8,0,1)

/**
 * \brief
 * frerCpsSeqRcvyTaglessPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_COMPOUND_TAGLESS . CNT_TAGLESS
 */
#define  VTSS_F_EACL_CNT_COMPOUND_TAGLESS_CNT_TAGLESS(x)  (x)
#define  VTSS_M_EACL_CNT_COMPOUND_TAGLESS_CNT_TAGLESS     0xffffffff
#define  VTSS_X_EACL_CNT_COMPOUND_TAGLESS_CNT_TAGLESS(x)  (x)


/**
 * \brief frerCpsSeqRcvyPassedPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_COMPOUND:CNT_COMPOUND_PASSED
 *
 * @param gi Replicator: x_FFL_EACL_FRER_COMPOUND_STREAMS (??), 0-127
 */
#define VTSS_EACL_CNT_COMPOUND_PASSED(gi)    VTSS_IOREG_IX(VTSS_TO_EACL,0x1000,gi,8,0,2)

/**
 * \brief
 * frerCpsSeqRcvyPassedPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_COMPOUND_PASSED . CNT_PASSED
 */
#define  VTSS_F_EACL_CNT_COMPOUND_PASSED_CNT_PASSED(x)  (x)
#define  VTSS_M_EACL_CNT_COMPOUND_PASSED_CNT_PASSED     0xffffffff
#define  VTSS_X_EACL_CNT_COMPOUND_PASSED_CNT_PASSED(x)  (x)


/**
 * \brief frerCpsSeqRcvyDiscardedPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_COMPOUND:CNT_COMPOUND_DISCARDED
 *
 * @param gi Replicator: x_FFL_EACL_FRER_COMPOUND_STREAMS (??), 0-127
 */
#define VTSS_EACL_CNT_COMPOUND_DISCARDED(gi)  VTSS_IOREG_IX(VTSS_TO_EACL,0x1000,gi,8,0,3)

/**
 * \brief
 * frerCpsSeqRcvyDiscardedPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_COMPOUND_DISCARDED . CNT_DISCARDED
 */
#define  VTSS_F_EACL_CNT_COMPOUND_DISCARDED_CNT_DISCARDED(x)  (x)
#define  VTSS_M_EACL_CNT_COMPOUND_DISCARDED_CNT_DISCARDED     0xffffffff
#define  VTSS_X_EACL_CNT_COMPOUND_DISCARDED_CNT_DISCARDED(x)  (x)


/**
 * \brief frerCpsSeqRcvyOutOfOrderPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_COMPOUND:CNT_COMPOUND_OUTOFORDER
 *
 * @param gi Replicator: x_FFL_EACL_FRER_COMPOUND_STREAMS (??), 0-127
 */
#define VTSS_EACL_CNT_COMPOUND_OUTOFORDER(gi)  VTSS_IOREG_IX(VTSS_TO_EACL,0x1000,gi,8,0,4)

/**
 * \brief
 * frerCpsSeqRcvyOutOfOrderPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_COMPOUND_OUTOFORDER . CNT_OUTOFORDER
 */
#define  VTSS_F_EACL_CNT_COMPOUND_OUTOFORDER_CNT_OUTOFORDER(x)  (x)
#define  VTSS_M_EACL_CNT_COMPOUND_OUTOFORDER_CNT_OUTOFORDER     0xffffffff
#define  VTSS_X_EACL_CNT_COMPOUND_OUTOFORDER_CNT_OUTOFORDER(x)  (x)


/**
 * \brief frerCpsSeqRcvyRoguePackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_COMPOUND:CNT_COMPOUND_ROGUE
 *
 * @param gi Replicator: x_FFL_EACL_FRER_COMPOUND_STREAMS (??), 0-127
 */
#define VTSS_EACL_CNT_COMPOUND_ROGUE(gi)     VTSS_IOREG_IX(VTSS_TO_EACL,0x1000,gi,8,0,5)

/**
 * \brief
 * frerCpsSeqRcvyRoguePackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_COMPOUND_ROGUE . CNT_ROGUE
 */
#define  VTSS_F_EACL_CNT_COMPOUND_ROGUE_CNT_ROGUE(x)  (x)
#define  VTSS_M_EACL_CNT_COMPOUND_ROGUE_CNT_ROGUE     0xffffffff
#define  VTSS_X_EACL_CNT_COMPOUND_ROGUE_CNT_ROGUE(x)  (x)


/**
 * \brief frerCpsSeqRcvyLostPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_COMPOUND:CNT_COMPOUND_LOST
 *
 * @param gi Replicator: x_FFL_EACL_FRER_COMPOUND_STREAMS (??), 0-127
 */
#define VTSS_EACL_CNT_COMPOUND_LOST(gi)      VTSS_IOREG_IX(VTSS_TO_EACL,0x1000,gi,8,0,6)

/**
 * \brief
 * frerCpsSeqRcvyLostPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_COMPOUND_LOST . CNT_LOST
 */
#define  VTSS_F_EACL_CNT_COMPOUND_LOST_CNT_LOST(x)  (x)
#define  VTSS_M_EACL_CNT_COMPOUND_LOST_CNT_LOST     0xffffffff
#define  VTSS_X_EACL_CNT_COMPOUND_LOST_CNT_LOST(x)  (x)

/**
 * Register Group: \a EACL:FRER_CNT_MEMBER
 *
 * FRER counters for member streams. One entry per each member stream.
 */


/**
 * \brief frerCpsSeqRcvyResets
 *
 * \details
 * Register: \a EACL:FRER_CNT_MEMBER:CNT_MEMBER_RESETS
 *
 * @param gi Replicator: x_FFL_EACL_FRER_MEMBER_STREAMS (??), 0-255
 */
#define VTSS_EACL_CNT_MEMBER_RESETS(gi)      VTSS_IOREG_IX(VTSS_TO_EACL,0x0,gi,8,0,0)

/**
 * \brief
 * frerCpsSeqRcvyResets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_MEMBER_RESETS . CNT_RESETS
 */
#define  VTSS_F_EACL_CNT_MEMBER_RESETS_CNT_RESETS(x)  (x)
#define  VTSS_M_EACL_CNT_MEMBER_RESETS_CNT_RESETS     0xffffffff
#define  VTSS_X_EACL_CNT_MEMBER_RESETS_CNT_RESETS(x)  (x)


/**
 * \brief frerCpsSeqRcvyTaglessPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_MEMBER:CNT_MEMBER_TAGLESS
 *
 * @param gi Replicator: x_FFL_EACL_FRER_MEMBER_STREAMS (??), 0-255
 */
#define VTSS_EACL_CNT_MEMBER_TAGLESS(gi)     VTSS_IOREG_IX(VTSS_TO_EACL,0x0,gi,8,0,1)

/**
 * \brief
 * frerCpsSeqRcvyTaglessPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_MEMBER_TAGLESS . CNT_TAGLESS
 */
#define  VTSS_F_EACL_CNT_MEMBER_TAGLESS_CNT_TAGLESS(x)  (x)
#define  VTSS_M_EACL_CNT_MEMBER_TAGLESS_CNT_TAGLESS     0xffffffff
#define  VTSS_X_EACL_CNT_MEMBER_TAGLESS_CNT_TAGLESS(x)  (x)


/**
 * \brief frerCpsSeqRcvyPassedPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_MEMBER:CNT_MEMBER_PASSED
 *
 * @param gi Replicator: x_FFL_EACL_FRER_MEMBER_STREAMS (??), 0-255
 */
#define VTSS_EACL_CNT_MEMBER_PASSED(gi)      VTSS_IOREG_IX(VTSS_TO_EACL,0x0,gi,8,0,2)

/**
 * \brief
 * frerCpsSeqRcvyPassedPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_MEMBER_PASSED . CNT_PASSED
 */
#define  VTSS_F_EACL_CNT_MEMBER_PASSED_CNT_PASSED(x)  (x)
#define  VTSS_M_EACL_CNT_MEMBER_PASSED_CNT_PASSED     0xffffffff
#define  VTSS_X_EACL_CNT_MEMBER_PASSED_CNT_PASSED(x)  (x)


/**
 * \brief frerCpsSeqRcvyDiscardedPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_MEMBER:CNT_MEMBER_DISCARDED
 *
 * @param gi Replicator: x_FFL_EACL_FRER_MEMBER_STREAMS (??), 0-255
 */
#define VTSS_EACL_CNT_MEMBER_DISCARDED(gi)   VTSS_IOREG_IX(VTSS_TO_EACL,0x0,gi,8,0,3)

/**
 * \brief
 * frerCpsSeqRcvyDiscardedPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_MEMBER_DISCARDED . CNT_DISCARDED
 */
#define  VTSS_F_EACL_CNT_MEMBER_DISCARDED_CNT_DISCARDED(x)  (x)
#define  VTSS_M_EACL_CNT_MEMBER_DISCARDED_CNT_DISCARDED     0xffffffff
#define  VTSS_X_EACL_CNT_MEMBER_DISCARDED_CNT_DISCARDED(x)  (x)


/**
 * \brief frerCpsSeqRcvyOutOfOrderPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_MEMBER:CNT_MEMBER_OUTOFORDER
 *
 * @param gi Replicator: x_FFL_EACL_FRER_MEMBER_STREAMS (??), 0-255
 */
#define VTSS_EACL_CNT_MEMBER_OUTOFORDER(gi)  VTSS_IOREG_IX(VTSS_TO_EACL,0x0,gi,8,0,4)

/**
 * \brief
 * frerCpsSeqRcvyOutOfOrderPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_MEMBER_OUTOFORDER . CNT_OUTOFORDER
 */
#define  VTSS_F_EACL_CNT_MEMBER_OUTOFORDER_CNT_OUTOFORDER(x)  (x)
#define  VTSS_M_EACL_CNT_MEMBER_OUTOFORDER_CNT_OUTOFORDER     0xffffffff
#define  VTSS_X_EACL_CNT_MEMBER_OUTOFORDER_CNT_OUTOFORDER(x)  (x)


/**
 * \brief frerCpsSeqRcvyRoguePackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_MEMBER:CNT_MEMBER_ROGUE
 *
 * @param gi Replicator: x_FFL_EACL_FRER_MEMBER_STREAMS (??), 0-255
 */
#define VTSS_EACL_CNT_MEMBER_ROGUE(gi)       VTSS_IOREG_IX(VTSS_TO_EACL,0x0,gi,8,0,5)

/**
 * \brief
 * frerCpsSeqRcvyRoguePackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_MEMBER_ROGUE . CNT_ROGUE
 */
#define  VTSS_F_EACL_CNT_MEMBER_ROGUE_CNT_ROGUE(x)  (x)
#define  VTSS_M_EACL_CNT_MEMBER_ROGUE_CNT_ROGUE     0xffffffff
#define  VTSS_X_EACL_CNT_MEMBER_ROGUE_CNT_ROGUE(x)  (x)


/**
 * \brief frerCpsSeqRcvyLostPackets
 *
 * \details
 * Register: \a EACL:FRER_CNT_MEMBER:CNT_MEMBER_LOST
 *
 * @param gi Replicator: x_FFL_EACL_FRER_MEMBER_STREAMS (??), 0-255
 */
#define VTSS_EACL_CNT_MEMBER_LOST(gi)        VTSS_IOREG_IX(VTSS_TO_EACL,0x0,gi,8,0,6)

/**
 * \brief
 * frerCpsSeqRcvyLostPackets as defined in 802.1CB-2017
 *
 * \details
 * Field: ::VTSS_EACL_CNT_MEMBER_LOST . CNT_LOST
 */
#define  VTSS_F_EACL_CNT_MEMBER_LOST_CNT_LOST(x)  (x)
#define  VTSS_M_EACL_CNT_MEMBER_LOST_CNT_LOST     0xffffffff
#define  VTSS_X_EACL_CNT_MEMBER_LOST_CNT_LOST(x)  (x)

/**
 * Register Group: \a EACL:STAT_GLOBAL_CFG_EACL
 *
 * Common counter configuration.
 */


/**
 * \brief Common frame type configuration
 *
 * \details
 * Register: \a EACL:STAT_GLOBAL_CFG_EACL:GLOBAL_CNT_FRM_TYPE_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_EACL_GLOBAL_CNT_FRM_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_EACL,0xc68 + (ri))

/**
 * \brief
 * Configures which frames is counted in relation to FCS error and
 * configured event mask (GLOBAL_EVENT_MASK).
 *
 * \details
 *
 * "000": Frames without any event signal or FCS errored frames are
 * counted.
 * "001": Frames with unmasked (enabled) events without FCS error are
 * counted.
 * "010": Frames with unmasked (enabled) events with FCS error are counted.
 * "011": Frames with unmasked (enabled) events independent of FCS error
 * are counted.
 * "100": Frames with FCS error but with no event signal are counted.
 * "101": Frames with FCS error are unconditionally counted.
 *
 * Field: ::VTSS_EACL_GLOBAL_CNT_FRM_TYPE_CFG . GLOBAL_CFG_CNT_FRM_TYPE
 */
#define  VTSS_F_EACL_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_EACL_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_EACL_GLOBAL_CNT_FRM_TYPE_CFG_GLOBAL_CFG_CNT_FRM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Global configuration register
 *
 * \details
 * Global configuration register
 *
 * Register: \a EACL:STAT_GLOBAL_CFG_EACL:STAT_GLOBAL_CFG
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_EACL_STAT_GLOBAL_CFG(ri)        VTSS_IOREG(VTSS_TO_EACL,0xc6a + (ri))

/**
 * \brief
 * This field is to configure the counters of all flows to count the byte
 * number or the frame number.
 *
 * \details
 * '0': Count frames.
 * '1': Count bytes.
 *
 * Field: ::VTSS_EACL_STAT_GLOBAL_CFG . GLOBAL_CFG_CNT_BYTE
 */
#define  VTSS_F_EACL_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE  VTSS_BIT(0)
#define  VTSS_X_EACL_STAT_GLOBAL_CFG_GLOBAL_CFG_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Event mask for counters.
 *
 * \details
 * Register: \a EACL:STAT_GLOBAL_CFG_EACL:STAT_GLOBAL_EVENT_MASK
 *
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_EACL_STAT_GLOBAL_EVENT_MASK(ri)  VTSS_IOREG(VTSS_TO_EACL,0xc6c + (ri))

/**
 * \brief
 * This value stores the event mask which indicates the counter of all
 * flows to count certain events.
 *  If set to '1' the respective event is not filtered and can trigger the
 * counter.
 *  If set to '0' the respective event is filtered and the counter will
 * treat the frame as if no event has occurred.
 *
 *  The following events apply to ACL stat:
 *  Bit0: Count CPU traffic applicable for CPU ACL policer but not
 * discarded
 *  Bit1: Count front port traffic applicable for ACL policer but not
 * discarded
 *  Bit2: Count CPU traffic discarded by ACL policer
 *  Bit3: Count front port traffic discarded by ACL policer
 *
 * \details
 * 0: This event will not trigger counting.
 * 1: Enable counting for frames with this event.
 *
 * Field: ::VTSS_EACL_STAT_GLOBAL_EVENT_MASK . GLOBAL_EVENT_MASK
 */
#define  VTSS_F_EACL_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_EACL_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_EACL_STAT_GLOBAL_EVENT_MASK_GLOBAL_EVENT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a EACL:STAT_CNT_CFG_EACL
 *
 * Individual configuration.
 */


/**
 * \brief The counter's least significant 32 bits.
 *
 * \details
 * Register: \a EACL:STAT_CNT_CFG_EACL:STAT_LSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-31
 * @param ri Replicator: x_STAT_CNT_PER_FLW_ID (??), 0-1
 */
#define VTSS_EACL_STAT_LSB_CNT(gi,ri)        VTSS_IOREG_IX(VTSS_TO_EACL,0x1580,gi,4,ri,0)

/**
 * \brief
 * This register contains the least significant 32 bits of a counter.
 *
 * \details
 * Field: ::VTSS_EACL_STAT_LSB_CNT . LSB_CNT
 */
#define  VTSS_F_EACL_STAT_LSB_CNT_LSB_CNT(x)  (x)
#define  VTSS_M_EACL_STAT_LSB_CNT_LSB_CNT     0xffffffff
#define  VTSS_X_EACL_STAT_LSB_CNT_LSB_CNT(x)  (x)


/**
 * \brief The counter's most significant 8 bits.
 *
 * \details
 * Register: \a EACL:STAT_CNT_CFG_EACL:STAT_MSB_CNT
 *
 * @param gi Replicator: x_STAT_NUM_FLW_ID (??), 0-31
 * @param ri Replicator: x_STAT_CNT_MSB_PER_FLW_ID (??), 0-1
 */
#define VTSS_EACL_STAT_MSB_CNT(gi,ri)        VTSS_IOREG_IX(VTSS_TO_EACL,0x1580,gi,4,ri,2)

/**
 * \brief
 * The counter's most significant 8 bits.The field stores the value in the
 * counters of a flow from bit 32 to the most significant bit. Reading:The
 * MSB part of the counter is latched to a shadow register, when the LSB
 * part is read. As a result, the LSB part must always be read first, and
 * the MSB part must be read immediately after the LSB part is read.
 * Writing:The procedure for writing differs depending on counter
 * group:ANA_AC:STAT_CNT_CFG_PORT: LSB part must be written first, followed
 * by MSB part.All other counter groups: MSB part must be written first,
 * followed by LSB part.
 *
 * \details
 * Field: ::VTSS_EACL_STAT_MSB_CNT . MSB_CNT
 */
#define  VTSS_F_EACL_STAT_MSB_CNT_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EACL_STAT_MSB_CNT_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EACL_STAT_MSB_CNT_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EACL:RAM_CTRL
 *
 * Access core memory
 */


/**
 * \brief Core reset control
 *
 * \details
 * Controls reset and initialization of the switching core. Proper startup
 * sequence is:
 * - Enable memories
 * - Initialize memories
 * - Enable core
 *
 * Register: \a EACL:RAM_CTRL:RAM_INIT
 */
#define VTSS_EACL_RAM_INIT                   VTSS_IOREG(VTSS_TO_EACL,0xc6e)

/**
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete (approx. 40 us).
 *
 * \details
 * Field: ::VTSS_EACL_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_EACL_RAM_INIT_RAM_INIT(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_EACL_RAM_INIT_RAM_INIT        VTSS_BIT(1)
#define  VTSS_X_EACL_RAM_INIT_RAM_INIT(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this field is set, all memories HA_RESTART behavior will be
 * inverted. It is a backdoor for potentiel access issues.
 *
 * \details
 * Field: ::VTSS_EACL_RAM_INIT . RAM_CFG_HOOK
 */
#define  VTSS_F_EACL_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_EACL_RAM_INIT_RAM_CFG_HOOK    VTSS_BIT(0)
#define  VTSS_X_EACL_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a EACL:COREMEM
 *
 * Access core memory
 */


/**
 * \brief Address selection
 *
 * \details
 * Register: \a EACL:COREMEM:CM_ADDR
 */
#define VTSS_EACL_CM_ADDR                    VTSS_IOREG(VTSS_TO_EACL,0xc6f)

/**
 * \brief
 * Address selection for the ram debug address space.
 *
 * \details
 * Field: ::VTSS_EACL_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_EACL_CM_ADDR_CM_ADDR(x)       (x)
#define  VTSS_M_EACL_CM_ADDR_CM_ADDR          0xffffffff
#define  VTSS_X_EACL_CM_ADDR_CM_ADDR(x)       (x)


/**
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a EACL:COREMEM:CM_DATA_WR
 */
#define VTSS_EACL_CM_DATA_WR                 VTSS_IOREG(VTSS_TO_EACL,0xc70)

/**
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 bit inspection space. This register provides data to
 * be written when CM_OP is set.
 *
 * \details
 * Field: ::VTSS_EACL_CM_DATA_WR . CM_DATA_WR
 */
#define  VTSS_F_EACL_CM_DATA_WR_CM_DATA_WR(x)  (x)
#define  VTSS_M_EACL_CM_DATA_WR_CM_DATA_WR     0xffffffff
#define  VTSS_X_EACL_CM_DATA_WR_CM_DATA_WR(x)  (x)


/**
 * \brief Core memory data register for read result
 *
 * \details
 * Register: \a EACL:COREMEM:CM_DATA_RD
 */
#define VTSS_EACL_CM_DATA_RD                 VTSS_IOREG(VTSS_TO_EACL,0xc71)

/**
 * \brief
 * Read result
 *
 * \details
 * Field: ::VTSS_EACL_CM_DATA_RD . CM_DATA_RD
 */
#define  VTSS_F_EACL_CM_DATA_RD_CM_DATA_RD(x)  (x)
#define  VTSS_M_EACL_CM_DATA_RD_CM_DATA_RD     0xffffffff
#define  VTSS_X_EACL_CM_DATA_RD_CM_DATA_RD(x)  (x)


/**
 * \brief Operation to perform in core memory
 *
 * \details
 * Register: \a EACL:COREMEM:CM_OP
 */
#define VTSS_EACL_CM_OP                      VTSS_IOREG(VTSS_TO_EACL,0xc72)

/**
 * \brief
 * Ask the memory debug system to read or write a specific location. If no
 * response is received from a memory, due to timeout, or selected address
 * out of range, the state machine can be reset by issuing the 11
 * command.Field will return to 00 upon completion.
 *
 * \details
 * 00: NOP
 * 01: Read from selected address into CM_DATA_RD
 * 10: Write CM_DATA_WR into selected address
 * 11: Reset debug access
 *
 * Field: ::VTSS_EACL_CM_OP . CM_OP
 */
#define  VTSS_F_EACL_CM_OP_CM_OP(x)           VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EACL_CM_OP_CM_OP              VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EACL_CM_OP_CM_OP(x)           VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_LAGUNA_REGS_EACL_H_ */
