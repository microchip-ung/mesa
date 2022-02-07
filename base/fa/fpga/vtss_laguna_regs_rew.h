// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_REW_H_
#define _VTSS_LAGUNA_REGS_REW_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a REW
 *
 * Rewriter
 *
 ***********************************************************************/

/**
 * Register Group: \a REW:COMMON
 *
 * Common configuration and status for all rewriter ports
 */


/**
 * \brief UPSID(s) for local ports
 *
 * \details
 * First replication covers port number 0-31
 * Second replication covers port numbers 32-63 (if applicable)
 * etc.
 *
 * If not all OWN_UPSID replications are required in a given port
 * configuration, then any unused replications must be set to the value of
 * one of the replications in use.
 *
 * Register: \a REW:COMMON:OWN_UPSID
 */
#define VTSS_REW_OWN_UPSID                   VTSS_IOREG(VTSS_TO_REW,0x3e80)

/**
 * \brief
 * Configures own UPSID to be used for stacking.This must be configured
 * consistently across the following
 * registers:ANA_CL:COMMON:OWN_UPSIDANA_ACL:COMMON:OWN_UPSIDANA_L2:COMMON:O
 * WN_UPSIDANA_AC:PS_COMMON:OWN_UPSIDREW:COMMON:OWN_UPSID
 *
 * \details
 * Field: ::VTSS_REW_OWN_UPSID . OWN_UPSID
 */
#define  VTSS_F_REW_OWN_UPSID_OWN_UPSID(x)    VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_REW_OWN_UPSID_OWN_UPSID       VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_REW_OWN_UPSID_OWN_UPSID(x)    VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Common Control configuration
 *
 * \details
 * Register: \a REW:COMMON:COMMON_CTRL
 */
#define VTSS_REW_COMMON_CTRL                 VTSS_IOREG(VTSS_TO_REW,0x3e83)

/**
 * \brief
 * Used when frames are L3 forwarded to a stack port.When this bit is set,
 * the reserved fields in the VSTAX.DST field is cleared
 *
 * \details
 * 0: Keep VSTAX.DST field as received
 * 1: Clear VSTAX.DST reserved fields when L3 forwarding
 *
 * Field: ::VTSS_REW_COMMON_CTRL . L3_CLR_VSTAX_DST_RSV
 */
#define  VTSS_F_REW_COMMON_CTRL_L3_CLR_VSTAX_DST_RSV(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_CTRL_L3_CLR_VSTAX_DST_RSV  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_CTRL_L3_CLR_VSTAX_DST_RSV(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Control if frames are aborted if the IFH.ENCAP.WORD16_POP_CNT field is
 * out of the supported range.
 *
 * \details
 * 0: Keep frame
 * 1: Abort frame
 *
 * Field: ::VTSS_REW_COMMON_CTRL . INVLD_W16_POP_CNT_FRM_ABORT
 */
#define  VTSS_F_REW_COMMON_CTRL_INVLD_W16_POP_CNT_FRM_ABORT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_CTRL_INVLD_W16_POP_CNT_FRM_ABORT  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_CTRL_INVLD_W16_POP_CNT_FRM_ABORT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * When padding is required after tag removal, also the FCS will be removed
 * before zero padding and new FCS is added.
 *
 * \details
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_REW_COMMON_CTRL . FRM_CLR_PAD_ENA
 */
#define  VTSS_F_REW_COMMON_CTRL_FRM_CLR_PAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_COMMON_CTRL_FRM_CLR_PAD_ENA  VTSS_BIT(2)
#define  VTSS_X_REW_COMMON_CTRL_FRM_CLR_PAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable R-tag awareness.If R-tag aware, any VLAN tags before or after the
 * R-tag are parsed (maximum two VLAN tags are supported together with an
 * R-tag). If R-tag unaware, the frame's R-tag is not analyzed and the
 * frame is considered a frame with ETYPE=0xF1C1. Any VLAN tags before the
 * R-tag are still analyzed.REW:COMMON:COMMON_CTRL.ETAG_TPID_ENA must be
 * set to 0 when R-tag awareness is
 * enabled.See:ANA_CL:COMMON:RTAG_CFG.RTAG_TPID_ENA
 *
 * \details
 * Field: ::VTSS_REW_COMMON_CTRL . RTAG_TPID_ENA
 */
#define  VTSS_F_REW_COMMON_CTRL_RTAG_TPID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_COMMON_CTRL_RTAG_TPID_ENA  VTSS_BIT(1)
#define  VTSS_X_REW_COMMON_CTRL_RTAG_TPID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable E-tag awareness.If E-tag aware, the frame's E-tag is parsed and
 * E-tag information is available for E-tag rewrites.If E-tag unaware, the
 * frame's E-tag is not analyzed and the frame is considered a frame with
 * ETYPE=0x893F.REW:COMMON:COMMON_CTRL.RTAG_TPID_ENA must be set to 0 when
 * E-tag awareness is enabled.See:ANA_CL:COMMON:ETAG_CFG.ETAG_TPID_ENA
 *
 * \details
 * Field: ::VTSS_REW_COMMON_CTRL . ETAG_TPID_ENA
 */
#define  VTSS_F_REW_COMMON_CTRL_ETAG_TPID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_CTRL_ETAG_TPID_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_CTRL_ETAG_TPID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Port based configuration for rewriter
 *
 * \details
 * IFH configuration of physical rewriter ports
 *
 * Register: \a REW:COMMON:IFH_CTRL
 *
 * @param ri Replicator: x_FFL_REW_NUM_ETH_PORTS (??), 0-29
 */
#define VTSS_REW_IFH_CTRL(ri)                VTSS_IOREG(VTSS_TO_REW,0x3e84 + (ri))

/**
 * \brief
 * Configure the rewriter IFH mode for the port.The configuration  is used
 * by the physical port and is not changed for TX-Mirrored frames.See
 * ASM::PORT_CFG.INJ_FORMAT_CFG
 *
 * \details
 * 0: Normal mode.
 * 1: Keep IFH without modifications. Frames are not updated. IFH is kept
 * 2: Encapsulate IFH.
 *    The frame's DMAC, SMAC and a fixed TAG with ETYPE=8880 (Microchip)
 * and EPID=0x000E are inserted in front of the IFH:
 *	 [FRM_DMAC][FRM_SMAC][0x8880][0x000E][IFH][FRAME]
 * 3: Encapsulate IFH using the ENCAP table
 *    Use ES0 to generate an ENCAP_ID and insert the encapsulation in front
 * of the IFH:
 *	 [ENCAP][IFH][FRAME]
 *    ES0 controlled encapsulations will be used if the ENCAP_ID action is
 * active, otherwise mode 2) is used.
 *
 * Field: ::VTSS_REW_IFH_CTRL . KEEP_IFH_SEL
 */
#define  VTSS_F_REW_IFH_CTRL_KEEP_IFH_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_IFH_CTRL_KEEP_IFH_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_IFH_CTRL_KEEP_IFH_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Port based configuration for rewriter
 *
 * \details
 * IFH configuration of CPU and VD rewriter ports

 *
 * Register: \a REW:COMMON:IFH_CTRL_CPUVD
 */
#define VTSS_REW_IFH_CTRL_CPUVD              VTSS_IOREG(VTSS_TO_REW,0x3ec5)

/**
 * \brief
 * CPU and VD port IFH configuration. For normal operation the default
 * value should not be changed.See ASM::PORT_CFG.INJ_FORMAT_CFGEncoding is
 * 2 bits per port:Bits 1-0: Port 65 (CPU0)Bits 3-2: Port 66 (CPU1)Bits
 * 5-4: Port 67 (VD0)Bits 7-6: Port 68 (VD1)Bits 9-8: Port 69 (VD2)
 *
 * \details
 * 0: Normal mode.
 * 1: Keep IFH without modifications. Frames are not updated. IFH is kept
 * 2: Encapsulate IFH.
 *    The frame's DMAC, SMAC and a fixed TAG with ETYPE=8880 (Microchip)
 * and EPID=0x000E are inserted in front of the IFH:
 *	 [FRM_DMAC][FRM_SMAC][0x8880][0x000E][IFH][FRAME]
 * 3: Encapsulate IFH using the ENCAP table
 *    Use ES0 to generate an ENCAP_ID and insert the encapsulation in front
 * of the IFH:
 *	 [ENCAP][IFH][FRAME]
 *    ES0 controlled encapsulations will be used if the ENCAP_ID action is
 * active, otherwise mode 2) is used.
 *
 * Field: ::VTSS_REW_IFH_CTRL_CPUVD . KEEP_IFH_SEL_CPUVD
 */
#define  VTSS_F_REW_IFH_CTRL_CPUVD_KEEP_IFH_SEL_CPUVD(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_REW_IFH_CTRL_CPUVD_KEEP_IFH_SEL_CPUVD     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_REW_IFH_CTRL_CPUVD_KEEP_IFH_SEL_CPUVD(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief Port based configuration for rewriter
 *
 * \details
 * Configuration of rewriter ports.

 *
 * Register: \a REW:COMMON:PORT_CTRL
 *
 * @param ri Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PORT_CTRL(ri)               VTSS_IOREG(VTSS_TO_REW,0x3ec6 + (ri))

/**
 * \brief
 * Map the configuration port to a logical port number to be used by ES0
 * keys. The port used for the lookup can be Tx-mirrored.Use the unmapped
 * port number, if the mapped value is outside port range (default)
 *
 * \details
 * 0-69: Use this port number for ES0 lookup
 * 70-127: Do not map port number
 *
 * Field: ::VTSS_REW_PORT_CTRL . ES0_LPORT_NUM
 */
#define  VTSS_F_REW_PORT_CTRL_ES0_LPORT_NUM(x)  VTSS_ENCODE_BITFIELD(x,25,6)
#define  VTSS_M_REW_PORT_CTRL_ES0_LPORT_NUM     VTSS_ENCODE_BITMASK(25,6)
#define  VTSS_X_REW_PORT_CTRL_ES0_LPORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,25,6)

/**
 * \brief
 * Configures the port statistics pipeline point location. Two locations
 * can be selected:Outer: The port statistics is located after REW_VRAP.
 * All frames extracted in REW are not counted. All frames injected in REW
 * are counted.Inner: The port statistics is located before REW_IN_MIP. All
 * frames extracted in REW are counted. All frames injected in REW are not
 * counted.This configuration only affects frames that are either injected
 * or extracted in the Rewriter. Other frames are always counted by the
 * ports statistics regardless of the inner- or outer location.
 *
 * \details
 * 0: Outer location
 * 1: Inner location
 *
 * Field: ::VTSS_REW_PORT_CTRL . PORT_STAT_INNER_ENA
 */
#define  VTSS_F_REW_PORT_CTRL_PORT_STAT_INNER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_REW_PORT_CTRL_PORT_STAT_INNER_ENA  VTSS_BIT(24)
#define  VTSS_X_REW_PORT_CTRL_PORT_STAT_INNER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Configures the extraction statistics pipeline point. Frames extracted
 * before the configured pipeline point are not counted by the ESDX
 * countersConfiguring the value 'REW_IN_MIP' will cause all extracted
 * frames to be counted.
 *
 * \details
 * 0: Reserved
 * 1: REW_IN_MIP
 * 2: REW_IN_SW
 * 3: REW_IN_VOE
 * 4: REW_OU_VOE
 * 5: REW_OU_SW
 * 6: REW_OU_MIP
 * 7: REW_SAT
 * 8: REW_PORT_VOE
 * 9: REW_VRAP
 *
 * Field: ::VTSS_REW_PORT_CTRL . XTR_STAT_PIPELINE_PT
 */
#define  VTSS_F_REW_PORT_CTRL_XTR_STAT_PIPELINE_PT(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_REW_PORT_CTRL_XTR_STAT_PIPELINE_PT     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_REW_PORT_CTRL_XTR_STAT_PIPELINE_PT(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Configures the injection statistics pipeline point. Frames injected
 * after the configured pipeline point are not counted by the ESDX
 * counters.Configuring the value 'REW_'VRAP will cause all injected frames
 * to be counted.
 *
 * \details
 * 0: Reserved
 * 1: REW_IN_MIP
 * 2: REW_IN_SW
 * 3: REW_IN_VOE
 * 4: REW_OU_VOE
 * 5: REW_OU_SW
 * 6: REW_OU_MIP
 * 7: REW_SAT
 * 8: REW_PORT_VOE
 * 9: REW_VRAP
 *
 * Field: ::VTSS_REW_PORT_CTRL . INJ_STAT_PIPELINE_PT
 */
#define  VTSS_F_REW_PORT_CTRL_INJ_STAT_PIPELINE_PT(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_REW_PORT_CTRL_INJ_STAT_PIPELINE_PT     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_REW_PORT_CTRL_INJ_STAT_PIPELINE_PT(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Configure VSTAX MISC field decoding.The configuration can be
 * Tx-mirrored.
 *
 * \details
 * 0: VSTAX MISC contains aggregation code
 * 1: VSTAX MISC contains ISDX and COSID
 *
 * Field: ::VTSS_REW_PORT_CTRL . VSTAX2_MISC_ISDX_ENA
 */
#define  VTSS_F_REW_PORT_CTRL_VSTAX2_MISC_ISDX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_REW_PORT_CTRL_VSTAX2_MISC_ISDX_ENA  VTSS_BIT(15)
#define  VTSS_X_REW_PORT_CTRL_VSTAX2_MISC_ISDX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * This configuration applies to VLAN tag awareness in the port VOE for
 * frames for which the rewriter is not pushing new VLAN tags or an MPLS
 * link layer. Each bit corresponds to one of the known TPIDs. If the
 * outgoing frame's outer tag contains a TPID for which
 * PORT_VOE_TPID_AWARE_DIS is set, then the port VOE sees the frame as
 * untagged.The configuration  is used by the physical port and is not
 * changed for TX-Mirrored frames.
 *
 * \details
 * Bit0: TPID = 0x8100.
 * Bit1: TPID = 0x88A8
 * Bit2: TPID = REW::TPID_CFG[0].TPID_VAL
 * Bit3: TPID = REW::TPID_CFG[1].TPID_VAL
 * Bit4: TPID = REW::TPID_CFG[2].TPID_VAL
 *
 * Field: ::VTSS_REW_PORT_CTRL . PORT_VOE_TPID_AWARE_DIS
 */
#define  VTSS_F_REW_PORT_CTRL_PORT_VOE_TPID_AWARE_DIS(x)  VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_REW_PORT_CTRL_PORT_VOE_TPID_AWARE_DIS     VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_REW_PORT_CTRL_PORT_VOE_TPID_AWARE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,10,5)

/**
 * \brief
 * Default PCP value used by the OAM port VOE. This value is used for port
 * VOE counter updates when no outer Q-Tag is present in a frame.The
 * configuration is used by the physical port and is not changed for
 * TX-Mirrored frames.
 *
 * \details
 * n: OAM default PCP value
 *
 * Field: ::VTSS_REW_PORT_CTRL . PORT_VOE_DEFAULT_PCP
 */
#define  VTSS_F_REW_PORT_CTRL_PORT_VOE_DEFAULT_PCP(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_REW_PORT_CTRL_PORT_VOE_DEFAULT_PCP     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_REW_PORT_CTRL_PORT_VOE_DEFAULT_PCP(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/**
 * \brief
 * Default DEI value used by the OAM port VOE. This value is used for port
 * VOE counter updates when no outer Q-Tag is present in a frame.The
 * configuration is used by the physical port and is not changed for
 * TX-Mirrored frames.
 *
 * \details
 * n: OAM default DEI value
 *
 * Field: ::VTSS_REW_PORT_CTRL . PORT_VOE_DEFAULT_DEI
 */
#define  VTSS_F_REW_PORT_CTRL_PORT_VOE_DEFAULT_DEI(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_PORT_CTRL_PORT_VOE_DEFAULT_DEI  VTSS_BIT(6)
#define  VTSS_X_REW_PORT_CTRL_PORT_VOE_DEFAULT_DEI(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Configure tagging of frames with VSTAX.GEN.FWD_MODE = VS2_FWD_GMIRROR.
 * Only active on front ports for frames using this FWD_MODE.This is used
 * to control the remote mirror tagging of frames that have been mirrored
 * from one unit in the stack to another unit.The configuration  is used by
 * the physical port and is not changed for TX-Mirrored frames.
 *
 * \details
 * 0: Always push the remote mirror tag carried VSTAX.TAG into the frame.
 * No other tags are pushed.
 * 1: Obey local port tag configuration.
 *
 * Field: ::VTSS_REW_PORT_CTRL . VSTAX2_MIRROR_OBEY_WAS_TAGGED
 */
#define  VTSS_F_REW_PORT_CTRL_VSTAX2_MIRROR_OBEY_WAS_TAGGED(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_PORT_CTRL_VSTAX2_MIRROR_OBEY_WAS_TAGGED  VTSS_BIT(3)
#define  VTSS_X_REW_PORT_CTRL_VSTAX2_MIRROR_OBEY_WAS_TAGGED(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable padding of frames to 76 bytes.If a frame is smaller than 64 bytes
 * when all rewrites are done, the frame is extended to 64 bytes to prevent
 * under size frames leaving the chip. Setting this bit will cause all
 * frames on the port to be extended to 76 bytes instead of 64 bytes.
 * VSTAX_PAD_ENA must be set for stacking ports (i.e. ports with
 * PORT_CTRL.VSTAX_HDR_ENA=1).The configuration is used by the physical
 * port and is not changed for TX-Mirrored frames.Related
 * parameters:REW:COMMON:PORT_CTRL.VSTAX_HDR_ENA
 *
 * \details
 * 0: Normal padding to 64 bytes
 * 1: Pad to 76 bytes
 *
 * Field: ::VTSS_REW_PORT_CTRL . VSTAX_PAD_ENA
 */
#define  VTSS_F_REW_PORT_CTRL_VSTAX_PAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_PORT_CTRL_VSTAX_PAD_ENA   VTSS_BIT(2)
#define  VTSS_X_REW_PORT_CTRL_VSTAX_PAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable insertion of stacking header in frame.The configuration is used
 * by the physical port and is not changed for TX-Mirrored frames.For
 * stacking ports, VSTAX_PAD_ENA must also be set.Related
 * parameters:REW:COMMON:PORT_CTRL.VSTAX_PAD_ENA
 *
 * \details
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_REW_PORT_CTRL . VSTAX_HDR_ENA
 */
#define  VTSS_F_REW_PORT_CTRL_VSTAX_HDR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_PORT_CTRL_VSTAX_HDR_ENA   VTSS_BIT(1)
#define  VTSS_X_REW_PORT_CTRL_VSTAX_HDR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Select logical stacking port (or stacking port group) membershipThe
 * configuration is used by the physical port and is not changed for
 * TX-Mirrored frames.
 *
 * \details
 * 0: Stack A
 * 1: Stack B
 *
 * Field: ::VTSS_REW_PORT_CTRL . VSTAX_STACK_GRP_SEL
 */
#define  VTSS_F_REW_PORT_CTRL_VSTAX_STACK_GRP_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_PORT_CTRL_VSTAX_STACK_GRP_SEL  VTSS_BIT(0)
#define  VTSS_X_REW_PORT_CTRL_VSTAX_STACK_GRP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief IEEE 801.1BR and IEEE802.1CB configuration
 *
 * \details
 * Configuration of 802.1BR Bridge Port Extension and 802.1CB Frame
 * Replication and Elimination for Reliability (FRER) funtions in Rewriter

 *
 * Register: \a REW:COMMON:RTAG_ETAG_CTRL
 *
 * @param ri Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_RTAG_ETAG_CTRL(ri)          VTSS_IOREG(VTSS_TO_REW,0x3f0c + (ri))

/**
 * \brief
 * If set, REW pushes a HSR tag in same location as RedBox would have done.
 * Gated by RB_ENA and IFH.RB.RB_TC0.
 *
 * \details
 * Field: ::VTSS_REW_RTAG_ETAG_CTRL . RB_ADD_HSR_ENA
 */
#define  VTSS_F_REW_RTAG_ETAG_CTRL_RB_ADD_HSR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_REW_RTAG_ETAG_CTRL_RB_ADD_HSR_ENA  VTSS_BIT(11)
#define  VTSS_X_REW_RTAG_ETAG_CTRL_RB_ADD_HSR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * If set, the REW transfers Redbox specific fields from the IFH to the
 * preamble and optionally push an HSR tag if this is enabled by the IFH
 * and the RB_ADD_HSR_ENA configuration
 *
 * \details
 * 0: Don't do RB preamble and frame modifications
 * 1: Transfer Redbox IRI to preamble and enable HSR frame modifications
 *
 * Field: ::VTSS_REW_RTAG_ETAG_CTRL . RB_ENA
 */
#define  VTSS_F_REW_RTAG_ETAG_CTRL_RB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_REW_RTAG_ETAG_CTRL_RB_ENA     VTSS_BIT(10)
#define  VTSS_X_REW_RTAG_ETAG_CTRL_RB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Table to determine local ingress- and egress extension ports (L_IGR_PORT
 * and L_EGR_PORT) when operating as a 802.1BR controlling bridgeUse the
 * unmapped port number, if the mapped value is outside port range
 * (default)Logical ingress port. Mapping of IFH.SRC_PORT: L_IGR_PORT :=
 * IPE_TBL[IFH.SRC_PORT]Logical egress port. Mapping of cell bus port
 * number: L_EGR_PORT := IPE_TBL[REW.CELLBUS.PORT_NUM]
 *
 * \details
 * 0-69: Use this port number for local ingress- and egress lookups
 * 70-127: Do not map port number
 *
 * Field: ::VTSS_REW_RTAG_ETAG_CTRL . IPE_TBL
 */
#define  VTSS_F_REW_RTAG_ETAG_CTRL_IPE_TBL(x)  VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_REW_RTAG_ETAG_CTRL_IPE_TBL     VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_REW_RTAG_ETAG_CTRL_IPE_TBL(x)  VTSS_EXTRACT_BITFIELD(x,3,6)

/**
 * \brief
 * Force ES0 lookups to use ISDX keys, independently of the ISDX value and
 * IFH.ES0_ISDX_KEY_ENA
 *
 * \details
 * 0: Normal selection
 * 1: Force ISDX lookups
 * 2: Force VID lookups
 * 3: Reserved
 *
 * Field: ::VTSS_REW_RTAG_ETAG_CTRL . ES0_ISDX_KEY_ENA
 */
#define  VTSS_F_REW_RTAG_ETAG_CTRL_ES0_ISDX_KEY_ENA(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_REW_RTAG_ETAG_CTRL_ES0_ISDX_KEY_ENA     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_REW_RTAG_ETAG_CTRL_ES0_ISDX_KEY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Control 802.1BR E-TAG handling. This bit must be set to '0' to allow
 * full 802.1BR E-TAG operation.When this bit is set to '1' the ingress
 * E-TAG is kept unmodified in the frame when the IFH field
 * IFH.TAGGING.RTAG_ETAG_AVAIL is set to '1'. When
 * IFH.TAGGING.RTAG_ETAG_AVAIL is '0' no E-TAG is pushed regardless of ES0
 * configuration
 *
 * \details
 * 0: Normal mode. Allow modification and pop of ingress 801.1BR E-TAG
 * 1: The ingress E-TAG is left unchanged in the frame if present on
 * ingress
 *
 * Field: ::VTSS_REW_RTAG_ETAG_CTRL . KEEP_ETAG
 */
#define  VTSS_F_REW_RTAG_ETAG_CTRL_KEEP_ETAG(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_RTAG_ETAG_CTRL_KEEP_ETAG  VTSS_BIT(0)
#define  VTSS_X_REW_RTAG_ETAG_CTRL_KEEP_ETAG(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configure custom TPID values
 *
 * \details
 * Register: \a REW:COMMON:TPID_CFG
 *
 * @param ri Register: TPID_CFG (??), 0-2
 */
#define VTSS_REW_TPID_CFG(ri)                VTSS_IOREG(VTSS_TO_REW,0x3f52 + (ri))

/**
 * \brief
 * Configure 3 custom TPID values.These must be configured identically in
 * ANA_CL::VLAN_STAG_CFG.STAG_ETYPE_VAL.Related
 * parameters:ANA_CL::VLAN_STAG_CFG.STAG_ETYPE_VAL
 *
 * \details
 * n: TPID value
 *
 * Field: ::VTSS_REW_TPID_CFG . TPID_VAL
 */
#define  VTSS_F_REW_TPID_CFG_TPID_VAL(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_TPID_CFG_TPID_VAL         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_TPID_CFG_TPID_VAL(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Various configuration of ES0 in rewriter module
 *
 * \details
 * Register: \a REW:COMMON:ES0_CTRL
 */
#define VTSS_REW_ES0_CTRL                    VTSS_IOREG(VTSS_TO_REW,0x3f55)

/**
 * \brief
 * Enable ES0 router mode lookup when IFH.ENCAP.RT_FWD indicates
 * routing.When enabled and IFH.FWD.DST_MODE = ENCAP, IFH.ENCAP.RT_FWD = 1,
 * and IFH.ENCAP.ENCAP_ID_RLEG = 0, the ES0 'GVID' key field is set to all
 * 1, the XVID key field is set to IFH.ENCAP.ENCAP_ID and ES0 lookup is
 * always done using VID key type.If IFH.ENCAP.RT_FWD does not indicate
 * routing, the lookup is done normally regardless of the ES0_BY_RT_FWD
 * configuration.
 *
 * \details
 * 0: Normal ES0 lookup
 * 1: Enable router mode ES0 lookup
 *
 * Field: ::VTSS_REW_ES0_CTRL . ES0_BY_RT_FWD
 */
#define  VTSS_F_REW_ES0_CTRL_ES0_BY_RT_FWD(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_ES0_CTRL_ES0_BY_RT_FWD    VTSS_BIT(5)
#define  VTSS_X_REW_ES0_CTRL_ES0_BY_RT_FWD(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable ES0 router mode lookup when IFH.FWD.DST_MODE indicates
 * routing.When enabled and IFH.FWD.DST_MODE = L3UC_ROUTING or
 * IFH.FWD.DST_MODE = L3MC_ROUTING, the ES0 'XVID' key field is set to all
 * 1, the VID key field is set to IFH.DST.ERLEG and ES0 lookup is always
 * done using VID key type.If IFH_FWD.DST_MODE does not indicate routing,
 * the lookup is done normally regardless of the ES0_BY_RLEG configuration.
 *
 * \details
 * 0: Normal ES0 lookup
 * 1: Enable router mode ES0 lookup
 *
 * Field: ::VTSS_REW_ES0_CTRL . ES0_BY_RLEG
 */
#define  VTSS_F_REW_ES0_CTRL_ES0_BY_RLEG(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_ES0_CTRL_ES0_BY_RLEG      VTSS_BIT(4)
#define  VTSS_X_REW_ES0_CTRL_ES0_BY_RLEG(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Setting this bit disables use of the PORT_CTRL.ES0_LPORT_NUM table for
 * egress port to logical port mapping and forces use of the virtual DPORT
 * as EGR_PORT ES0 key valueCorrect virtual switch operation requires
 * ES0_DPORT_ENA to be set.
 *
 * \details
 * 0: Normal ES0_LPORT_NUM operation
 * 1: Always use DPORT from QSYS as EGR_PORT key value
 *
 * Field: ::VTSS_REW_ES0_CTRL . ES0_DPORT_ENA
 */
#define  VTSS_F_REW_ES0_CTRL_ES0_DPORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_ES0_CTRL_ES0_DPORT_ENA    VTSS_BIT(3)
#define  VTSS_X_REW_ES0_CTRL_ES0_DPORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Via ES0 it is possible to loop frames back to the Analyzer using the
 * LOOP_ENA and FWD_SEL actions. If this bit is set, a frame can only be
 * looped once by ES0.
 *
 * \details
 * 0: No ES0 frame loop limitation
 * 1: Allow only one loop of frame
 *
 * Field: ::VTSS_REW_ES0_CTRL . ES0_FRM_LBK_CFG
 */
#define  VTSS_F_REW_ES0_CTRL_ES0_FRM_LBK_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_ES0_CTRL_ES0_FRM_LBK_CFG  VTSS_BIT(2)
#define  VTSS_X_REW_ES0_CTRL_ES0_FRM_LBK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * When enabled and IFH.ENCAP.ENCAP_ID_RLEG_MODE = 3  and egress port =
 * VD2, the ES0 'XVID' key field is set to IFH.ENCAP.ENCAP_ID_RLEG
 *
 * \details
 * Field: ::VTSS_REW_ES0_CTRL . ES0_VD2_ENCAP_ID_ENA
 */
#define  VTSS_F_REW_ES0_CTRL_ES0_VD2_ENCAP_ID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_ES0_CTRL_ES0_VD2_ENCAP_ID_ENA  VTSS_BIT(1)
#define  VTSS_X_REW_ES0_CTRL_ES0_VD2_ENCAP_ID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable lookup in VCAP_ES0 to control advanced frame modifications.
 *
 * \details
 * 0: VCAP_ES0 do not control frame modifications
 * 1: VCAP_ES0 controls all frame rewrites
 *
 * Field: ::VTSS_REW_ES0_CTRL . ES0_LU_ENA
 */
#define  VTSS_F_REW_ES0_CTRL_ES0_LU_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_ES0_CTRL_ES0_LU_ENA       VTSS_BIT(0)
#define  VTSS_X_REW_ES0_CTRL_ES0_LU_ENA(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CCM hit me once auto set
 *
 * \details
 * Register: \a REW:COMMON:MIP_CTRL
 */
#define VTSS_REW_MIP_CTRL                    VTSS_IOREG(VTSS_TO_REW,0x3f56)

/**
 * \brief
 * Set all CCM Hit me once bits. Cleared when the access completes.Ref:
 * REW:MIP_TBL:CCM_HMO_CTRL
 *
 * \details
 * 0: Idle
 * 1: Initiate setting all CCM_HMO_CTRL.CCM_COPY_ONCE_ENA where
 * MIP_CCM_INTERVAL_MASK[CCM_HMO_CTRL.CCM_INTERVAL] is set
 *
 * The bit is cleared upon completion
 *
 * Field: ::VTSS_REW_MIP_CTRL . MIP_CCM_HMO_SET_SHOT
 */
#define  VTSS_F_REW_MIP_CTRL_MIP_CCM_HMO_SET_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_MIP_CTRL_MIP_CCM_HMO_SET_SHOT  VTSS_BIT(4)
#define  VTSS_X_REW_MIP_CTRL_MIP_CCM_HMO_SET_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Specifies which MIP CCM intervals that will have CCM_COPY_ONCE_ENA set.
 *
 * \details
 * x0x: Interval is ignored
 * x1x: REW:MIP_TBL:CCM_HMO_CTRL.CCM_COPY_ONCE_ENA  is set where
 * MIP_CCM_INTERVAL_MASK[CCM_HMO_CTRL.CCM_INTERVAL] is set.
 *
 * Field: ::VTSS_REW_MIP_CTRL . MIP_CCM_INTERVAL_MASK
 */
#define  VTSS_F_REW_MIP_CTRL_MIP_CCM_INTERVAL_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_REW_MIP_CTRL_MIP_CCM_INTERVAL_MASK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_REW_MIP_CTRL_MIP_CCM_INTERVAL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Configure mirror probes
 *
 * \details
 * Related parameters:
 * ANA_AC:MIRROR_PROBE
 *
 * Register: \a REW:COMMON:MIRROR_PROBE_CFG
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_MIR_PROBES (??), 0-2
 */
#define VTSS_REW_MIRROR_PROBE_CFG(ri)        VTSS_IOREG(VTSS_TO_REW,0x3f57 + (ri))

/**
 * \brief
 * The TX port for the mirror_probe (From where rewrite configuration is
 * taken)
 *
 * \details
 * 0: Port 0
 * 1: Port 1
 * . . .
 * n: Port n
 *
 * Field: ::VTSS_REW_MIRROR_PROBE_CFG . MIRROR_TX_PORT
 */
#define  VTSS_F_REW_MIRROR_PROBE_CFG_MIRROR_TX_PORT(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_REW_MIRROR_PROBE_CFG_MIRROR_TX_PORT     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_REW_MIRROR_PROBE_CFG_MIRROR_TX_PORT(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * Select encapsulation ID to use for remote mirror frames.
 *
 * \details
 * 0: No encapsulation
 * 1-n: Encapsulation ID n
 *
 * Field: ::VTSS_REW_MIRROR_PROBE_CFG . REMOTE_ENCAP_ID
 */
#define  VTSS_F_REW_MIRROR_PROBE_CFG_REMOTE_ENCAP_ID(x)  VTSS_ENCODE_BITFIELD(x,2,8)
#define  VTSS_M_REW_MIRROR_PROBE_CFG_REMOTE_ENCAP_ID     VTSS_ENCODE_BITMASK(2,8)
#define  VTSS_X_REW_MIRROR_PROBE_CFG_REMOTE_ENCAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,8)

/**
 * \brief
 * Enable encapsulation of mirrored frames. One or two Q-Tags (Q-in-Q) or
 * the encapsulation table can be used.In tag mode the VLAN tags will be
 * added in the outer most position after the SMAC. This will also be the
 * case if a MPLS link layer is added to the frame. The tags will then be
 * added after LL-SMAC.In encapsulation mode an entry in the ENCAP-table is
 * used for encapsulation. This will override any encapsulation selected by
 * ES0 for the frame.
 *
 * \details
 * 0: Local mirror port. No encapsulation
 * 1: Add one VLAN tag. Configured by MIRROR_TAG_A_CFG
 * 2: Add two VLAN tags. Configured by MIRROR_TAG_A_CFG and
 * MIRROR_TAG_B_CFG
 * 3: Use ENCAP table selected by REMOTE_ENCAP_ID
 *
 * Field: ::VTSS_REW_MIRROR_PROBE_CFG . REMOTE_MIRROR_CFG
 */
#define  VTSS_F_REW_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Configure mirror probes
 *
 * \details
 * Configuration of mirror QTag A. Each mirror probe can be configured
 * individually.
 *
 * Register: \a REW:COMMON:MIRROR_TAG_A_CFG
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_MIR_PROBES (??), 0-2
 */
#define VTSS_REW_MIRROR_TAG_A_CFG(ri)        VTSS_IOREG(VTSS_TO_REW,0x3f5a + (ri))

/**
 * \brief
 * Mirror Q-tag A Tag Protocol Identifier (TPID)
 *
 * \details
 * 0: 0x8100
 * 1: 0x88A8
 * 2: Custom1. REW::TPID_CFG[0].TPID_VAL
 * 3: Custom2. REW::TPID_CFG[1].TPID_VAL
 * 4: Custom3. REW::TPID_CFG[2].TPID_VAL
 * 5: Select via ifh.vstax.tag_type and ifh.encap.tag_tpid
 *   If ifh.encap.tag_tipd = STD_TPID:
 *     If ifh.vstax.tag_type = 0 then 0x8100 else 0x88A8
 *   If ifh.encap.tag_tipd = CUSTOM<n>:
 *     Custom<n> TPID
 * 6-7: Reserved
 *
 * Field: ::VTSS_REW_MIRROR_TAG_A_CFG . TAG_A_TPID_SEL
 */
#define  VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_REW_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_REW_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/**
 * \brief
 * Mirror Q-tag A VID value.
 *
 * \details
 * n: VID n
 *
 * Field: ::VTSS_REW_MIRROR_TAG_A_CFG . TAG_A_VID_VAL
 */
#define  VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,5,12)
#define  VTSS_M_REW_MIRROR_TAG_A_CFG_TAG_A_VID_VAL     VTSS_ENCODE_BITMASK(5,12)
#define  VTSS_X_REW_MIRROR_TAG_A_CFG_TAG_A_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,12)

/**
 * \brief
 * Mirror Q-tag A DEI value.
 *
 * \details
 * 0: DEI bit = 0
 * 1: DEI bit = 1
 *
 * Field: ::VTSS_REW_MIRROR_TAG_A_CFG . TAG_A_DEI_VAL
 */
#define  VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_MIRROR_TAG_A_CFG_TAG_A_DEI_VAL  VTSS_BIT(4)
#define  VTSS_X_REW_MIRROR_TAG_A_CFG_TAG_A_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Selection of mirror Q-tag A PCP value.
 *
 * \details
 * 0: Use classified PCP
 * 1: Use TAG_A_PCP_VAL
 *
 * Field: ::VTSS_REW_MIRROR_TAG_A_CFG . TAG_A_PCP_SEL
 */
#define  VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_PCP_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_MIRROR_TAG_A_CFG_TAG_A_PCP_SEL  VTSS_BIT(3)
#define  VTSS_X_REW_MIRROR_TAG_A_CFG_TAG_A_PCP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Mirror Q-tag A PCP value.
 *
 * \details
 * n: PCP n

 *
 * Field: ::VTSS_REW_MIRROR_TAG_A_CFG . TAG_A_PCP_VAL
 */
#define  VTSS_F_REW_MIRROR_TAG_A_CFG_TAG_A_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_MIRROR_TAG_A_CFG_TAG_A_PCP_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_MIRROR_TAG_A_CFG_TAG_A_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configure mirror probes
 *
 * \details
 * Configuration of mirror QTag B. Each mirror probe can be configured
 * individually.
 *
 * Register: \a REW:COMMON:MIRROR_TAG_B_CFG
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_MIR_PROBES (??), 0-2
 */
#define VTSS_REW_MIRROR_TAG_B_CFG(ri)        VTSS_IOREG(VTSS_TO_REW,0x3f5d + (ri))

/**
 * \brief
 * Mirror Q-tag B Tag Protocol Identifier (TPID)
 *
 * \details
 * 0: 0x8100
 * 1: 0x88A8
 * 2: Custom1. REW::TPID_CFG[0].TPID_VAL
 * 3: Custom2. REW::TPID_CFG[1].TPID_VAL
 * 4: Custom3. REW::TPID_CFG[2].TPID_VAL
 * 5: Select via ifh.vstax.tag_type and ifh.encap.tag_tpid
 *   If ifh.encap.tag_tipd = STD_TPID:
 *     If ifh.vstax.tag_type = 0 then 0x8100 else 0x88A8
 *   If ifh.encap.tag_tipd = CUSTOM<n>:
 *     Custom<n> TPID
 * 6-7: Reserved
 *
 * Field: ::VTSS_REW_MIRROR_TAG_B_CFG . TAG_B_TPID_SEL
 */
#define  VTSS_F_REW_MIRROR_TAG_B_CFG_TAG_B_TPID_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_REW_MIRROR_TAG_B_CFG_TAG_B_TPID_SEL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_REW_MIRROR_TAG_B_CFG_TAG_B_TPID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/**
 * \brief
 * Mirror Q-tag B VID value.
 *
 * \details
 * n: VID n
 *
 * Field: ::VTSS_REW_MIRROR_TAG_B_CFG . TAG_B_VID_VAL
 */
#define  VTSS_F_REW_MIRROR_TAG_B_CFG_TAG_B_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,5,12)
#define  VTSS_M_REW_MIRROR_TAG_B_CFG_TAG_B_VID_VAL     VTSS_ENCODE_BITMASK(5,12)
#define  VTSS_X_REW_MIRROR_TAG_B_CFG_TAG_B_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,12)

/**
 * \brief
 * Mirror Q-tag B DEI value.
 *
 * \details
 * 0: DEI bit = 0
 * 1: DEI bit = 1
 *
 * Field: ::VTSS_REW_MIRROR_TAG_B_CFG . TAG_B_DEI_VAL
 */
#define  VTSS_F_REW_MIRROR_TAG_B_CFG_TAG_B_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_MIRROR_TAG_B_CFG_TAG_B_DEI_VAL  VTSS_BIT(4)
#define  VTSS_X_REW_MIRROR_TAG_B_CFG_TAG_B_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Selection of mirror Q-tag B PCP value.
 *
 * \details
 * 0: Use classified PCP
 * 1: Use TAG_B_PCP_VAL
 *
 * Field: ::VTSS_REW_MIRROR_TAG_B_CFG . TAG_B_PCP_SEL
 */
#define  VTSS_F_REW_MIRROR_TAG_B_CFG_TAG_B_PCP_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_MIRROR_TAG_B_CFG_TAG_B_PCP_SEL  VTSS_BIT(3)
#define  VTSS_X_REW_MIRROR_TAG_B_CFG_TAG_B_PCP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Mirror Q-tag B PCP value.
 *
 * \details
 * n: PCP n

 *
 * Field: ::VTSS_REW_MIRROR_TAG_B_CFG . TAG_B_PCP_VAL
 */
#define  VTSS_F_REW_MIRROR_TAG_B_CFG_TAG_B_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_MIRROR_TAG_B_CFG_TAG_B_PCP_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_MIRROR_TAG_B_CFG_TAG_B_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


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
 * Register: \a REW:COMMON:DP_MAP
 */
#define VTSS_REW_DP_MAP                      VTSS_IOREG(VTSS_TO_REW,0x3f60)

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
 * Field: ::VTSS_REW_DP_MAP . DP
 */
#define  VTSS_F_REW_DP_MAP_DP(x)              VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_REW_DP_MAP_DP                 VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_REW_DP_MAP_DP(x)              VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Remap table of DSCP values.
 *
 * \details
 * Register: \a REW:COMMON:DSCP_REMAP
 *
 * @param ri Register: DSCP_REMAP (??), 0-63
 */
#define VTSS_REW_DSCP_REMAP(ri)              VTSS_IOREG(VTSS_TO_REW,0x3f61 + (ri))

/**
 * \brief
 * Full one to one DSCP remapping table common for all ports.
 *
 * \details
 * Field: ::VTSS_REW_DSCP_REMAP . DSCP_REMAP
 */
#define  VTSS_F_REW_DSCP_REMAP_DSCP_REMAP(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_REW_DSCP_REMAP_DSCP_REMAP     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_REW_DSCP_REMAP_DSCP_REMAP(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Rewriter router leg configuration.
 *
 * \details
 * Register: \a REW:COMMON:RLEG_CFG_0
 */
#define VTSS_REW_RLEG_CFG_0                  VTSS_IOREG(VTSS_TO_REW,0x3fa1)

/**
 * \brief
 * Router leg base MAC address, least significant bits.In order to have
 * different MAC addresses per router leg, the base address may be
 * incremented using VID or VMID, ref. RLEG_MAC_TYPE_SEL.This must be
 * configured consistently in ANA_L3 and possibly EACL.Related
 * parameters:ANA_L3:COMMON:RLEG_CFG_0.RLEG_MAC_LSBEACL:COMMON:RLEG_CFG_0.R
 * LEG_MAC_LSB
 *
 * \details
 * Bit 0: MAC address, bit 0
 * ...
 * Bit 23: MAC address, bit 23
 *
 * Field: ::VTSS_REW_RLEG_CFG_0 . RLEG_MAC_LSB
 */
#define  VTSS_F_REW_RLEG_CFG_0_RLEG_MAC_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_REW_RLEG_CFG_0_RLEG_MAC_LSB     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_REW_RLEG_CFG_0_RLEG_MAC_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief Rewriter router leg configuration.
 *
 * \details
 * Register: \a REW:COMMON:RLEG_CFG_1
 */
#define VTSS_REW_RLEG_CFG_1                  VTSS_IOREG(VTSS_TO_REW,0x3fa2)

/**
 * \brief
 * Configuration of router leg specific MAC address.This must be configured
 * consistently in ANA_L3 and possibly EACL.Related
 * parameters:ANA_L3:COMMON:RLEG_CFG_1.RLEG_MAC_TYPE_SELEACL:COMMON:RLEG_CF
 * G_1.RLEG_MAC_TYPE_SEL
 *
 * \details
 * 0: RLEG used to increment base MAC address:
 * RLEG_MAC = RLEG_MAC_MSB(23:0) & ((RLEG_MAC_LSB(23:0) + IFH.ERLEG) mod
 * 2**24)
 *
 * 1: EVID (VMID.RLEG_EVID) used to increment base MAC address:
 * RLEG_MAC = RLEG_MAC_MSB(23:0) & ((RLEG_MAC_LSB(23:0) + RLEG_EVID) mod
 * 2**24)
 *
 * 2: Base MAC address used for all router legs
 * RLEG_MAC = RLEG_MAC_MSB[23:0] & RLEG_MAC_LSB[23:0]
 *
 * 3: Reserved
 *
 * Field: ::VTSS_REW_RLEG_CFG_1 . RLEG_MAC_TYPE_SEL
 */
#define  VTSS_F_REW_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_REW_RLEG_CFG_1_RLEG_MAC_TYPE_SEL     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_REW_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Router leg base MAC address, least significant bits.In order to have
 * different MAC addresses per router leg, the base address may be
 * incremented using VID or VMID, ref. RLEG_MAC_TYPE_SEL.This must be
 * configured consistently in ANA_L3 and possibly EACL.Related
 * parameters:ANA_L3:COMMON:RLEG_CFG_1.RLEG_MAC_MSBEACL:COMMON:RLEG_CFG_1.R
 * LEG_MAC_MSB
 *
 * \details
 * Bit 0: MAC address, bit 24
 * ...
 * Bit 23: MAC address, bit 47
 *
 * Field: ::VTSS_REW_RLEG_CFG_1 . RLEG_MAC_MSB
 */
#define  VTSS_F_REW_RLEG_CFG_1_RLEG_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_REW_RLEG_CFG_1_RLEG_MAC_MSB     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_REW_RLEG_CFG_1_RLEG_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief Control register for counter events
 *
 * \details
 * Register: \a REW:COMMON:CNT_CTRL
 */
#define VTSS_REW_CNT_CTRL                    VTSS_IOREG(VTSS_TO_REW,0x3fa3)

/**
 * \brief
 * Select from which source port events are counted.
 *
 * \details
 * 'n': Count events from source port n
 *
 * Field: ::VTSS_REW_CNT_CTRL . EVENT_CNT_PORT
 */
#define  VTSS_F_REW_CNT_CTRL_EVENT_CNT_PORT(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_REW_CNT_CTRL_EVENT_CNT_PORT     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_REW_CNT_CTRL_EVENT_CNT_PORT(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/**
 * \brief
 * If set to 1 events from all ports are counted. If 0 the port is selected
 * by the 'EVENT_CNT_PORT' register
 *
 * \details
 * 0: Count events from the port selected by 'EVENT_CNT_PORT'
 * 1: Count events from all ports
 *
 * Field: ::VTSS_REW_CNT_CTRL . EVENT_CNT_ALL
 */
#define  VTSS_F_REW_CNT_CTRL_EVENT_CNT_ALL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_CNT_CTRL_EVENT_CNT_ALL    VTSS_BIT(4)
#define  VTSS_X_REW_CNT_CTRL_EVENT_CNT_ALL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Configure ESDX counting for stacking ports.If this bit is set and
 * PORT_CTRL.VSTAX_HDR_ENA=1, all counting based on the ESDX value is
 * disabled regardless of the CNT_CTRL.STAT_MODE configuration.Related
 * parameters:ANA_AC:PS_COMMON:COMMON_VSTAX_CFG.VSTAX2_ISDX_STAT_DIS
 *
 * \details
 * 0: Normal ESDX statistics mode
 * 1: Disable ESDX statistics for stacking ports
 *
 * Field: ::VTSS_REW_CNT_CTRL . VSTAX_STAT_ESDX_DIS
 */
#define  VTSS_F_REW_CNT_CTRL_VSTAX_STAT_ESDX_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_CNT_CTRL_VSTAX_STAT_ESDX_DIS  VTSS_BIT(3)
#define  VTSS_X_REW_CNT_CTRL_VSTAX_STAT_ESDX_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable counting of frames discarded by the REW. The QSYS abort
 * statistics counters are used.This bit only enables counting of frames
 * discarded by ES0 or the SW_MIP. Frame discards done by the OAM MEP are
 * not included.
 *
 * \details
 * 0: Disable counting
 * 1: Enable counting
 *
 * Field: ::VTSS_REW_CNT_CTRL . STAT_CNT_FRM_ABORT_ENA
 */
#define  VTSS_F_REW_CNT_CTRL_STAT_CNT_FRM_ABORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_CNT_CTRL_STAT_CNT_FRM_ABORT_ENA  VTSS_BIT(2)
#define  VTSS_X_REW_CNT_CTRL_STAT_CNT_FRM_ABORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Configures the egress service statistics mode. The following options for
 * looking up the egress service counter set are available:In mode 0 and 1
 * yellow frames (DE=1) are counted separatelyIn mode 2 and 3 multicast
 * frames (DMAC bit 40 = 1) are counted separatelyRelated
 * parameters:ANA_AC:PS_COMMON:MISC_CTRL.USE_VID_AS_ISDX_ENA
 *
 * \details
 * 0: Use ESDX from ES0 if hit, otherwise ISDX
 * 1: Use ESDX from ES0 if hit, otherwise no counting
 * 2: Use ISDX (ifh.vstax.misc.isdx as index)
 * 3: Use classified VID (ifh.vstax.tag.vid)
 *
 * Field: ::VTSS_REW_CNT_CTRL . STAT_MODE
 */
#define  VTSS_F_REW_CNT_CTRL_STAT_MODE(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_CNT_CTRL_STAT_MODE        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_CNT_CTRL_STAT_MODE(x)     VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Controls the common sticky event counter.
 *
 * \details
 * Register: \a REW:COMMON:STICKY_EVENT_COUNT
 */
#define VTSS_REW_STICKY_EVENT_COUNT          VTSS_IOREG(VTSS_TO_REW,0x3fa4)

/**
 * \brief
 * Counter with number of masked events. Multiple simultaneously events are
 * counted as one.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::VTSS_REW_STICKY_EVENT_COUNT . STICKY_EVENT_COUNTER
 */
#define  VTSS_F_REW_STICKY_EVENT_COUNT_STICKY_EVENT_COUNTER(x)  (x)
#define  VTSS_M_REW_STICKY_EVENT_COUNT_STICKY_EVENT_COUNTER     0xffffffff
#define  VTSS_X_REW_STICKY_EVENT_COUNT_STICKY_EVENT_COUNTER(x)  (x)


/**
 * \brief Mask for the STICKY_EVENT_COUNT
 *
 * \details
 * Register: \a REW:COMMON:STICKY_EVENT_CNT_MASK_CFG
 */
#define VTSS_REW_STICKY_EVENT_CNT_MASK_CFG   VTSS_IOREG(VTSS_TO_REW,0x3fa5)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . INVLD_W16_POP_CNT_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_W16_POP_CNT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_W16_POP_CNT_STICKY_MASK  VTSS_BIT(16)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_W16_POP_CNT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . INVLD_POP_CNT_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_POP_CNT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_POP_CNT_STICKY_MASK  VTSS_BIT(15)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_POP_CNT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . REWRITE_OVERFLOW_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_REWRITE_OVERFLOW_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_REWRITE_OVERFLOW_STICKY_MASK  VTSS_BIT(14)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_REWRITE_OVERFLOW_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . VLAN_UNTAGGED_VID0_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAGGED_VID0_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAGGED_VID0_STICKY_MASK  VTSS_BIT(13)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAGGED_VID0_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . VLAN_PRIO_TAGGED_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_PRIO_TAGGED_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_PRIO_TAGGED_STICKY_MASK  VTSS_BIT(12)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_PRIO_TAGGED_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . IP6_MC_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_IP6_MC_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_IP6_MC_STICKY_MASK  VTSS_BIT(11)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_IP6_MC_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . IP4_MC_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_IP4_MC_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_IP4_MC_STICKY_MASK  VTSS_BIT(10)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_IP4_MC_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . IP6_UC_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_IP6_UC_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_IP6_UC_STICKY_MASK  VTSS_BIT(9)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_IP6_UC_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . IP4_UC_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_IP4_UC_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_IP4_UC_STICKY_MASK  VTSS_BIT(8)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_IP4_UC_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . DSCP_REMAP_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_DSCP_REMAP_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_DSCP_REMAP_STICKY_MASK  VTSS_BIT(7)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_DSCP_REMAP_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . DSCP_REPLACE_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_DSCP_REPLACE_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_DSCP_REPLACE_STICKY_MASK  VTSS_BIT(6)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_DSCP_REPLACE_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . INVLD_IFH_FOR_PTP_FRM_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_IFH_FOR_PTP_FRM_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_IFH_FOR_PTP_FRM_STICKY_MASK  VTSS_BIT(5)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_INVLD_IFH_FOR_PTP_FRM_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . LINK_LAYER_ERROR_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ERROR_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ERROR_STICKY_MASK  VTSS_BIT(4)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ERROR_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . LINK_LAYER_ADDED_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ADDED_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ADDED_STICKY_MASK  VTSS_BIT(3)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ADDED_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . VLAN_TAG_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_TAG_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_TAG_STICKY_MASK  VTSS_BIT(2)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_TAG_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . VLAN_UNTAG_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAG_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAG_STICKY_MASK  VTSS_BIT(1)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAG_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable counting of the event
 *
 * \details
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_STICKY_EVENT_CNT_MASK_CFG . VLAN_POP_CNT_STICKY_MASK
 */
#define  VTSS_F_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_POP_CNT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_POP_CNT_STICKY_MASK  VTSS_BIT(0)
#define  VTSS_X_REW_STICKY_EVENT_CNT_MASK_CFG_VLAN_POP_CNT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Rewriter sticky bit register
 *
 * \details
 * Register: \a REW:COMMON:STICKY_EVENT
 */
#define VTSS_REW_STICKY_EVENT                VTSS_IOREG(VTSS_TO_REW,0x3fa6)

/**
 * \brief
 * This bit is set if an invalid 'pop_cnt' value is received in the IFH
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . INVLD_W16_POP_CNT_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_INVLD_W16_POP_CNT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_STICKY_EVENT_INVLD_W16_POP_CNT_STICKY  VTSS_BIT(16)
#define  VTSS_X_REW_STICKY_EVENT_INVLD_W16_POP_CNT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * This bit is set if an invalid 'pop_cnt' value is received in the IFH
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . INVLD_POP_CNT_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_INVLD_POP_CNT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_REW_STICKY_EVENT_INVLD_POP_CNT_STICKY  VTSS_BIT(15)
#define  VTSS_X_REW_STICKY_EVENT_INVLD_POP_CNT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Encapsulation overflow. Mismatching pop/push operations
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . REWRITE_OVERFLOW_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_REWRITE_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_REW_STICKY_EVENT_REWRITE_OVERFLOW_STICKY  VTSS_BIT(14)
#define  VTSS_X_REW_STICKY_EVENT_REWRITE_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Untagged frame event due to VID=0 is detected
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . VLAN_UNTAGGED_VID0_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_VLAN_UNTAGGED_VID0_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_REW_STICKY_EVENT_VLAN_UNTAGGED_VID0_STICKY  VTSS_BIT(13)
#define  VTSS_X_REW_STICKY_EVENT_VLAN_UNTAGGED_VID0_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Priority tagged frame event is detected
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . VLAN_PRIO_TAGGED_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_VLAN_PRIO_TAGGED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_STICKY_EVENT_VLAN_PRIO_TAGGED_STICKY  VTSS_BIT(12)
#define  VTSS_X_REW_STICKY_EVENT_VLAN_PRIO_TAGGED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * This bit is set if an IP6 frame has been L3 multicast forwarded
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . IP6_MC_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_IP6_MC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_REW_STICKY_EVENT_IP6_MC_STICKY  VTSS_BIT(11)
#define  VTSS_X_REW_STICKY_EVENT_IP6_MC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * This bit is set if an IP4 frame has been L3 multicast forwarded
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . IP4_MC_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_IP4_MC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_REW_STICKY_EVENT_IP4_MC_STICKY  VTSS_BIT(10)
#define  VTSS_X_REW_STICKY_EVENT_IP4_MC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * This bit is set if an IP6 frame has been unicast forwarded.
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . IP6_UC_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_IP6_UC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_REW_STICKY_EVENT_IP6_UC_STICKY  VTSS_BIT(9)
#define  VTSS_X_REW_STICKY_EVENT_IP6_UC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * This bit is set if an IP4 frame has unicast forwarded.
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . IP4_UC_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_IP4_UC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_REW_STICKY_EVENT_IP4_UC_STICKY  VTSS_BIT(8)
#define  VTSS_X_REW_STICKY_EVENT_IP4_UC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * This bit is set if a DSCP remap event is detected
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . DSCP_REMAP_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_DSCP_REMAP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_REW_STICKY_EVENT_DSCP_REMAP_STICKY  VTSS_BIT(7)
#define  VTSS_X_REW_STICKY_EVENT_DSCP_REMAP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This bit is set if a DSCP has been replaced event is detected
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . DSCP_REPLACE_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_DSCP_REPLACE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_STICKY_EVENT_DSCP_REPLACE_STICKY  VTSS_BIT(6)
#define  VTSS_X_REW_STICKY_EVENT_DSCP_REPLACE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This bit is set if the IFH is not correct for PTP frames
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . INVLD_IFH_FOR_PTP_FRM_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_INVLD_IFH_FOR_PTP_FRM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_STICKY_EVENT_INVLD_IFH_FOR_PTP_FRM_STICKY  VTSS_BIT(5)
#define  VTSS_X_REW_STICKY_EVENT_INVLD_IFH_FOR_PTP_FRM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * This bit is set if a frames out of the REW is missing the link layer
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . LINK_LAYER_ERROR_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_LINK_LAYER_ERROR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_STICKY_EVENT_LINK_LAYER_ERROR_STICKY  VTSS_BIT(4)
#define  VTSS_X_REW_STICKY_EVENT_LINK_LAYER_ERROR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * This bit is set if a new link layer has been added to a frame
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . LINK_LAYER_ADDED_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_LINK_LAYER_ADDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_STICKY_EVENT_LINK_LAYER_ADDED_STICKY  VTSS_BIT(3)
#define  VTSS_X_REW_STICKY_EVENT_LINK_LAYER_ADDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This bit is set if a VLAN tag event is detected
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . VLAN_TAG_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_VLAN_TAG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_STICKY_EVENT_VLAN_TAG_STICKY  VTSS_BIT(2)
#define  VTSS_X_REW_STICKY_EVENT_VLAN_TAG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This bit is set if a VLAN untag event is detected
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . VLAN_UNTAG_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_VLAN_UNTAG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_STICKY_EVENT_VLAN_UNTAG_STICKY  VTSS_BIT(1)
#define  VTSS_X_REW_STICKY_EVENT_VLAN_UNTAG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This bit is set if a VLAN pop event is detected
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_STICKY_EVENT . VLAN_POP_CNT_STICKY
 */
#define  VTSS_F_REW_STICKY_EVENT_VLAN_POP_CNT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_STICKY_EVENT_VLAN_POP_CNT_STICKY  VTSS_BIT(0)
#define  VTSS_X_REW_STICKY_EVENT_VLAN_POP_CNT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
 * Register: \a REW:COMMON:GCPU_CFG
 *
 * @param ri Register: GCPU_CFG (??), 0-7
 */
#define VTSS_REW_GCPU_CFG(ri)                VTSS_IOREG(VTSS_TO_REW,0x3fa7 + (ri))

/**
 * \brief
 * Used when GCPU frames are forwarded to a front port. Frames are sent
 * with the IFH preserved. The IFH is encapsulated according to the
 * configuration. Setting GCPU_KEEP_IFH to a value different from 0
 * overrides the GCPU_TAG_SEL and GCPU_DO_NOT_REW settings for front ports.
 * No other rewrites are done to the frame.The GCPU_KEEP_IFH setting is not
 * active if IFH_CTRL.KEEP_IFH_SEL is different from 0 or if
 * PORT_CTRL.VSTAX_HDR_ENA=1
 *
 * \details
 * 0: Normal mode.
 * 1: Keep IFH without modifications. Frames are not updated. IFH is kept
 * 2: Encapsulate IFH.
 *    The frame's DMAC, SMAC and a fixed TAG with ETYPE=8880 (Microchip)
 * and EPID=0x000E are inserted in front of the IFH:
 *	 [FRM_DMAC][FRM_SMAC][0x8880][0x000E][IFH][FRAME]
 * 3: Encapsulate IFH using the ENCAP table
 *    Use GCPU_UPSID and GCPU_UPSPN or ES0 to generate an ENCAP_ID and
 * insert the encapsulation in front of the IFH:
 *	 [ENCAP][IFH][FRAME]
 *    ENCAP_ID = 32*GCPU_UPSID+GCPU_UPSPN or ENCAP_ID action from ES0
 *    IF ENCAP_ID = 0 then the ES0 action ENCAP_ID is used to control the
 * encapsulation. If neither of these encapsulations are valid (ENCAP_ID >
 * 0) then mode 2) is used.
 *
 * Field: ::VTSS_REW_GCPU_CFG . GCPU_KEEP_IFH
 */
#define  VTSS_F_REW_GCPU_CFG_GCPU_KEEP_IFH(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_REW_GCPU_CFG_GCPU_KEEP_IFH     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_REW_GCPU_CFG_GCPU_KEEP_IFH(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * Used when GCPU frames are forwarded to a front port. Frame are not
 * modified when forwarded to the GCPU expect for the optional tags
 * configured in GCPU_CFG.GCPU_TAG_SEL
 *
 * \details
 * 0: Allow normal rewrites of GCPU frames forwarded to front ports
 * 1: Allow only addition of GCPU_TAGS to GCPU frames
 *
 * Field: ::VTSS_REW_GCPU_CFG . GCPU_DO_NOT_REW
 */
#define  VTSS_F_REW_GCPU_CFG_GCPU_DO_NOT_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_REW_GCPU_CFG_GCPU_DO_NOT_REW  VTSS_BIT(19)
#define  VTSS_X_REW_GCPU_CFG_GCPU_DO_NOT_REW(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * When a GCPU frame is forwarded to a stack port:Force a change of the
 * VSTAX.TAG to the configured values in GCPU_TAG_CFG:0When a GCPU frame is
 * forwarded to a front port:Optionally add one or two Q-tags to the frame.
 * The tags are configured using GCPU_TAG_CFG
 *
 * \details
 * 0: Normal mode. No tags are added and VSTAX.TAG is equal to the outer
 * most frame tag
 * 1: Add one tag to GCPU frames forwarded to front ports. Set VSTAX.TAG to
 * GCPU_TAG_CFG:0 for frames on a stack port
 * 2: Add two tags to GCPU frames forwarded to front ports. Set VSTAX.TAG
 * to GCPU_TAG_CFG:0 for frames on a stack port
 * 3: Reserved
 *
 * Field: ::VTSS_REW_GCPU_CFG . GCPU_TAG_SEL
 */
#define  VTSS_F_REW_GCPU_CFG_GCPU_TAG_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_REW_GCPU_CFG_GCPU_TAG_SEL     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_REW_GCPU_CFG_GCPU_TAG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/**
 * \brief
 * Used when GCPU frames are forwarded to a stack port. Configure forward
 * mode of GCPU frames on stack ports by selecting value of
 * VSTAX.GEN.FWD_MODE.
 *
 * \details
 * 0: VSTAX.GEN.FWD_MODE = VS2_FWD_GCPU_UPS
 * Forward the frame to a specific unit in the stack
 *
 * 1: VSTAX.GEN.FWD_MODE = VS2_FWD_PHYSICAL
 * Forward the frame to a specific port on a specific unit in the stack.
 *
 * Field: ::VTSS_REW_GCPU_CFG . GCPU_FWD_MODE
 */
#define  VTSS_F_REW_GCPU_CFG_GCPU_FWD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_GCPU_CFG_GCPU_FWD_MODE    VTSS_BIT(16)
#define  VTSS_X_REW_GCPU_CFG_GCPU_FWD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Used when GCPU frames are forwarded to a stack port. DST_PN to be used
 * as destination in the VSTAX header. Set VSTAX.DST.DST_PN to configured
 * value.
 *
 * \details
 * 0: DST_PN 0
 * 1: DST_PN 1
 * ...
 * n: DST_PN n
 *
 * Field: ::VTSS_REW_GCPU_CFG . GCPU_UPSPN
 */
#define  VTSS_F_REW_GCPU_CFG_GCPU_UPSPN(x)    VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_REW_GCPU_CFG_GCPU_UPSPN       VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_REW_GCPU_CFG_GCPU_UPSPN(x)    VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Used when GCPU frames are forwarded to a stack port. DST_UPSID to be
 * used as destination in the VSTAX header. Set VSTAX.DST.DST_UPSID to
 * configured value.
 *
 * \details
 * 0: DST_UPSID 0
 * 1: DST_UPSID 1
 * ...
 * n: DST_UPSID n
 *
 * Field: ::VTSS_REW_GCPU_CFG . GCPU_UPSID
 */
#define  VTSS_F_REW_GCPU_CFG_GCPU_UPSID(x)    VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_REW_GCPU_CFG_GCPU_UPSID       VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_REW_GCPU_CFG_GCPU_UPSID(x)    VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief VSTAX Configuration per logical Stacking port
 *
 * \details
 * Register: \a REW:COMMON:VSTAX_PORT_GRP_CFG
 *
 * @param ri Register: VSTAX_PORT_GRP_CFG (??), 0-1
 */
#define VTSS_REW_VSTAX_PORT_GRP_CFG(ri)      VTSS_IOREG(VTSS_TO_REW,0x3faf + (ri))

/**
 * \brief
 * Link TTL value
 *
 * \details
 * Field: ::VTSS_REW_VSTAX_PORT_GRP_CFG . VSTAX_TTL
 */
#define  VTSS_F_REW_VSTAX_PORT_GRP_CFG_VSTAX_TTL(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_REW_VSTAX_PORT_GRP_CFG_VSTAX_TTL     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_REW_VSTAX_PORT_GRP_CFG_VSTAX_TTL(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/**
 * \brief
 * Change priority for learn all frames.
 *
 * \details
 * 0: Disable
 * 1: Enable (Learn-all are sent with highest priority)
 *
 * Field: ::VTSS_REW_VSTAX_PORT_GRP_CFG . VSTAX_LRN_ALL_HP_ENA
 */
#define  VTSS_F_REW_VSTAX_PORT_GRP_CFG_VSTAX_LRN_ALL_HP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_VSTAX_PORT_GRP_CFG_VSTAX_LRN_ALL_HP_ENA  VTSS_BIT(1)
#define  VTSS_X_REW_VSTAX_PORT_GRP_CFG_VSTAX_LRN_ALL_HP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Control whether forwarding modes specific to VStaX AF shall be
 * translated to BF forwarding modes.If set to 0, the following translation
 * will be performed:fwd_logical -> fwd_lookupfwd_mc -> fwd_lookupIf set to
 * 1, no translation will be performed.Translation is only required for AF
 * switches operating in a BF stack.
 *
 * \details
 * 0: Perform fwd_mode translation.
 * 1: Do not perform fwd_mode translation.
 *
 * Field: ::VTSS_REW_VSTAX_PORT_GRP_CFG . VSTAX_MODE
 */
#define  VTSS_F_REW_VSTAX_PORT_GRP_CFG_VSTAX_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_VSTAX_PORT_GRP_CFG_VSTAX_MODE  VTSS_BIT(0)
#define  VTSS_X_REW_VSTAX_PORT_GRP_CFG_VSTAX_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configure optional GCPU tagging
 *
 * \details
 * Configuration of QTags for GCPU frames.
 *
 * GCPU frames that are forwarded to a front port can optionally have one
 * or two Qtags added. The tags will be placed in the outer most position
 * after the SMAC.
 *
 * TAG_A is the outer tag.
 * Idx0:  TAG_A, Idx1:	TAG_B.
 *
 * Register: \a REW:COMMON:GCPU_TAG_CFG
 *
 * @param ri Register: GCPU_TAG_CFG (??), 0-1
 */
#define VTSS_REW_GCPU_TAG_CFG(ri)            VTSS_IOREG(VTSS_TO_REW,0x3fb1 + (ri))

/**
 * \brief
 * GCPU Q-tag Tag Protocol Identifiers (TPID)
 *
 * \details
 * 0: 0x8100
 * 1: 0x88A8
 * 2: Custom1. REW::TPID_CFG[0].TPID_VAL
 * 3: Custom2. REW::TPID_CFG[1].TPID_VAL
 * 4: Custom3. REW::TPID_CFG[2].TPID_VAL
 * 5: Select via ifh.vstax.tag_type and ifh.encap.tag_tpid
 *   If ifh.encap.tag_tipd = STD_TPID:
 *     If ifh.vstax.tag_type = 0 then 0x8100 else 0x88A8
 *   If ifh.encap.tag_tipd = CUSTOM<n>:
 *     Custom<n> TPID
 * 6-7: Reserved
 *
 * Field: ::VTSS_REW_GCPU_TAG_CFG . TAG_TPID_SEL
 */
#define  VTSS_F_REW_GCPU_TAG_CFG_TAG_TPID_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_REW_GCPU_TAG_CFG_TAG_TPID_SEL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_REW_GCPU_TAG_CFG_TAG_TPID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/**
 * \brief
 * GCPU Q-tag VID values
 *
 * \details
 * n: VID n
 *
 * Field: ::VTSS_REW_GCPU_TAG_CFG . TAG_VID_VAL
 */
#define  VTSS_F_REW_GCPU_TAG_CFG_TAG_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,5,12)
#define  VTSS_M_REW_GCPU_TAG_CFG_TAG_VID_VAL     VTSS_ENCODE_BITMASK(5,12)
#define  VTSS_X_REW_GCPU_TAG_CFG_TAG_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,12)

/**
 * \brief
 * GCPU Q-tag DEI values
 *
 * \details
 * 0: DEI bit = 0
 * 1: DEI bit = 1
 *
 * Field: ::VTSS_REW_GCPU_TAG_CFG . TAG_DEI_VAL
 */
#define  VTSS_F_REW_GCPU_TAG_CFG_TAG_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_GCPU_TAG_CFG_TAG_DEI_VAL  VTSS_BIT(4)
#define  VTSS_X_REW_GCPU_TAG_CFG_TAG_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Selection of GCPU Q-tag PCP values
 *
 * \details
 * 0: Use classified PCP
 * 1: Use TAG_PCP_VAL
 *
 * Field: ::VTSS_REW_GCPU_TAG_CFG . TAG_PCP_SEL
 */
#define  VTSS_F_REW_GCPU_TAG_CFG_TAG_PCP_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_GCPU_TAG_CFG_TAG_PCP_SEL  VTSS_BIT(3)
#define  VTSS_X_REW_GCPU_TAG_CFG_TAG_PCP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * GCPU Q-tag PCP values.
 *
 * \details
 * n: PCP n

 *
 * Field: ::VTSS_REW_GCPU_TAG_CFG . TAG_PCP_VAL
 */
#define  VTSS_F_REW_GCPU_TAG_CFG_TAG_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_GCPU_TAG_CFG_TAG_PCP_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_GCPU_TAG_CFG_TAG_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief MIP sticky bit register
 *
 * \details
 * Event register common for all MIPs
 *
 * Register: \a REW:COMMON:MIP_STICKY_EVENT
 */
#define VTSS_REW_MIP_STICKY_EVENT            VTSS_IOREG(VTSS_TO_REW,0x3fb3)

/**
 * \brief
 * This bit is set if a CCM CPU is copied to CPU
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_MIP_STICKY_EVENT . MIP_CCM_COPY_STICKY
 */
#define  VTSS_F_REW_MIP_STICKY_EVENT_MIP_CCM_COPY_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_MIP_STICKY_EVENT_MIP_CCM_COPY_STICKY  VTSS_BIT(6)
#define  VTSS_X_REW_MIP_STICKY_EVENT_MIP_CCM_COPY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This bit is set if a LBM PDU has been redirected to the CPU
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_MIP_STICKY_EVENT . MIP_LBM_REDIR_STICKY
 */
#define  VTSS_F_REW_MIP_STICKY_EVENT_MIP_LBM_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_MIP_STICKY_EVENT_MIP_LBM_REDIR_STICKY  VTSS_BIT(5)
#define  VTSS_X_REW_MIP_STICKY_EVENT_MIP_LBM_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * This bit is set if a LTM PDU has been redirected to the CPU
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_MIP_STICKY_EVENT . MIP_LTM_REDIR_STICKY
 */
#define  VTSS_F_REW_MIP_STICKY_EVENT_MIP_LTM_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_MIP_STICKY_EVENT_MIP_LTM_REDIR_STICKY  VTSS_BIT(4)
#define  VTSS_X_REW_MIP_STICKY_EVENT_MIP_LTM_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * This bit is set if a Ring APS PDU has been handled
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_MIP_STICKY_EVENT . MIP_RAPS_STICKY
 */
#define  VTSS_F_REW_MIP_STICKY_EVENT_MIP_RAPS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_MIP_STICKY_EVENT_MIP_RAPS_STICKY  VTSS_BIT(3)
#define  VTSS_X_REW_MIP_STICKY_EVENT_MIP_RAPS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This bit is set if a Generic PDU has been handled
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_MIP_STICKY_EVENT . MIP_GENERIC_STICKY
 */
#define  VTSS_F_REW_MIP_STICKY_EVENT_MIP_GENERIC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_MIP_STICKY_EVENT_MIP_GENERIC_STICKY  VTSS_BIT(2)
#define  VTSS_X_REW_MIP_STICKY_EVENT_MIP_GENERIC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This bit is set if a destination MAC address check has failed for LBM
 * frame
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_MIP_STICKY_EVENT . MIP_LBM_DA_CHK_FAIL_STICKY
 */
#define  VTSS_F_REW_MIP_STICKY_EVENT_MIP_LBM_DA_CHK_FAIL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_MIP_STICKY_EVENT_MIP_LBM_DA_CHK_FAIL_STICKY  VTSS_BIT(1)
#define  VTSS_X_REW_MIP_STICKY_EVENT_MIP_LBM_DA_CHK_FAIL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This bit is set if a MEL check has failed for enabled OAM frames
 *
 * \details
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_MIP_STICKY_EVENT . MIP_MEL_CHK_FAIL_STICKY
 */
#define  VTSS_F_REW_MIP_STICKY_EVENT_MIP_MEL_CHK_FAIL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_MIP_STICKY_EVENT_MIP_MEL_CHK_FAIL_STICKY  VTSS_BIT(0)
#define  VTSS_X_REW_MIP_STICKY_EVENT_MIP_MEL_CHK_FAIL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a REW:MAP_RES_A
 *
 * Mapping resource A
 */


/**
 * \brief Configuration of mapping tables 0 and 1
 *
 * \details
 * Lookup 0 and 1 values
 *
 * Register: \a REW:MAP_RES_A:MAP_VAL_A
 *
 * @param gi Replicator: x_FFL_REW_NUM_MAP_TBL_ENTRIES (??), 0-255
 */
#define VTSS_REW_MAP_VAL_A(gi)               VTSS_IOREG_IX(VTSS_TO_REW,0x2a00,gi,2,0,0)

/**
 * \brief
 * Mapped OAM COLOR value
 *
 * \details
 * n: New OAM COLOR value
 *
 * Field: ::VTSS_REW_MAP_VAL_A . OAM_COLOR
 */
#define  VTSS_F_REW_MAP_VAL_A_OAM_COLOR(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_MAP_VAL_A_OAM_COLOR       VTSS_BIT(16)
#define  VTSS_X_REW_MAP_VAL_A_OAM_COLOR(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Mapped OAM COSID value
 *
 * \details
 * n: New OAM COSID value
 *
 * Field: ::VTSS_REW_MAP_VAL_A . OAM_COSID
 */
#define  VTSS_F_REW_MAP_VAL_A_OAM_COSID(x)    VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_REW_MAP_VAL_A_OAM_COSID       VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_REW_MAP_VAL_A_OAM_COSID(x)    VTSS_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief
 * Mapped TC value
 *
 * \details
 * n: New TC value
 *
 * Field: ::VTSS_REW_MAP_VAL_A . TC_VAL
 */
#define  VTSS_F_REW_MAP_VAL_A_TC_VAL(x)       VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_REW_MAP_VAL_A_TC_VAL          VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_REW_MAP_VAL_A_TC_VAL(x)       VTSS_EXTRACT_BITFIELD(x,10,3)

/**
 * \brief
 * Mapped DSCP value
 *
 * \details
 * n: New DSCP value
 *
 * Field: ::VTSS_REW_MAP_VAL_A . DSCP_VAL
 */
#define  VTSS_F_REW_MAP_VAL_A_DSCP_VAL(x)     VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_REW_MAP_VAL_A_DSCP_VAL        VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_REW_MAP_VAL_A_DSCP_VAL(x)     VTSS_EXTRACT_BITFIELD(x,4,6)

/**
 * \brief
 * Mapped DEI value
 *
 * \details
 * n: New DEI value
 *
 * Field: ::VTSS_REW_MAP_VAL_A . DEI_VAL
 */
#define  VTSS_F_REW_MAP_VAL_A_DEI_VAL(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_MAP_VAL_A_DEI_VAL         VTSS_BIT(3)
#define  VTSS_X_REW_MAP_VAL_A_DEI_VAL(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Mapped PCP value
 *
 * \details
 * n: New PCP value
 *
 * Field: ::VTSS_REW_MAP_VAL_A . PCP_VAL
 */
#define  VTSS_F_REW_MAP_VAL_A_PCP_VAL(x)      VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_MAP_VAL_A_PCP_VAL         VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_MAP_VAL_A_PCP_VAL(x)      VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuration of mapping tables 0 and 1. MPLS label
 *
 * \details
 * Lookup 0 and 1 values
 *
 * Register: \a REW:MAP_RES_A:MAP_LBL_A
 *
 * @param gi Replicator: x_FFL_REW_NUM_MAP_TBL_ENTRIES (??), 0-255
 */
#define VTSS_REW_MAP_LBL_A(gi)               VTSS_IOREG_IX(VTSS_TO_REW,0x2a00,gi,2,0,1)

/**
 * \brief
 * Mapped MPLS label value
 *
 * \details
 * n: Label value
 *
 * Field: ::VTSS_REW_MAP_LBL_A . LABEL_VAL
 */
#define  VTSS_F_REW_MAP_LBL_A_LABEL_VAL(x)    VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_REW_MAP_LBL_A_LABEL_VAL       VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_REW_MAP_LBL_A_LABEL_VAL(x)    VTSS_EXTRACT_BITFIELD(x,0,20)

/**
 * Register Group: \a REW:MAP_RES_B
 *
 * Mapping resource B
 */


/**
 * \brief Configuration of mapping tables 2 and 3
 *
 * \details
 * Lookup 2 and 3 values
 *
 * Register: \a REW:MAP_RES_B:MAP_VAL_B
 *
 * @param gi Replicator: x_FFL_REW_NUM_MAP_TBL_ENTRIES (??), 0-255
 */
#define VTSS_REW_MAP_VAL_B(gi)               VTSS_IOREG_IX(VTSS_TO_REW,0x4000,gi,2,0,0)

/**
 * \brief
 * Mapped OAM COLOR value
 *
 * \details
 * n: New OAM COLOR value
 *
 * Field: ::VTSS_REW_MAP_VAL_B . OAM_COLOR
 */
#define  VTSS_F_REW_MAP_VAL_B_OAM_COLOR(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_MAP_VAL_B_OAM_COLOR       VTSS_BIT(16)
#define  VTSS_X_REW_MAP_VAL_B_OAM_COLOR(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Mapped OAM COSID value
 *
 * \details
 * n: New OAM COSID value
 *
 * Field: ::VTSS_REW_MAP_VAL_B . OAM_COSID
 */
#define  VTSS_F_REW_MAP_VAL_B_OAM_COSID(x)    VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_REW_MAP_VAL_B_OAM_COSID       VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_REW_MAP_VAL_B_OAM_COSID(x)    VTSS_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief
 * Mapped TC value
 *
 * \details
 * n: New TC value
 *
 * Field: ::VTSS_REW_MAP_VAL_B . TC_VAL
 */
#define  VTSS_F_REW_MAP_VAL_B_TC_VAL(x)       VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_REW_MAP_VAL_B_TC_VAL          VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_REW_MAP_VAL_B_TC_VAL(x)       VTSS_EXTRACT_BITFIELD(x,10,3)

/**
 * \brief
 * Mapped DSCP value
 *
 * \details
 * n: New DSCP value
 *
 * Field: ::VTSS_REW_MAP_VAL_B . DSCP_VAL
 */
#define  VTSS_F_REW_MAP_VAL_B_DSCP_VAL(x)     VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_REW_MAP_VAL_B_DSCP_VAL        VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_REW_MAP_VAL_B_DSCP_VAL(x)     VTSS_EXTRACT_BITFIELD(x,4,6)

/**
 * \brief
 * Mapped DEI value
 *
 * \details
 * n: New DEI value
 *
 * Field: ::VTSS_REW_MAP_VAL_B . DEI_VAL
 */
#define  VTSS_F_REW_MAP_VAL_B_DEI_VAL(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_MAP_VAL_B_DEI_VAL         VTSS_BIT(3)
#define  VTSS_X_REW_MAP_VAL_B_DEI_VAL(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Mapped PCP value
 *
 * \details
 * n: New PCP value
 *
 * Field: ::VTSS_REW_MAP_VAL_B . PCP_VAL
 */
#define  VTSS_F_REW_MAP_VAL_B_PCP_VAL(x)      VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_MAP_VAL_B_PCP_VAL         VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_MAP_VAL_B_PCP_VAL(x)      VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuration of mapping tables 2 and 3. MPLS label
 *
 * \details
 * Lookup 2 and 3 values
 *
 * Register: \a REW:MAP_RES_B:MAP_LBL_B
 *
 * @param gi Replicator: x_FFL_REW_NUM_MAP_TBL_ENTRIES (??), 0-255
 */
#define VTSS_REW_MAP_LBL_B(gi)               VTSS_IOREG_IX(VTSS_TO_REW,0x4000,gi,2,0,1)

/**
 * \brief
 * Mapped MPLS label value
 *
 * \details
 * n: Label value
 *
 * Field: ::VTSS_REW_MAP_LBL_B . LABEL_VAL
 */
#define  VTSS_F_REW_MAP_LBL_B_LABEL_VAL(x)    VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_REW_MAP_LBL_B_LABEL_VAL       VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_REW_MAP_LBL_B_LABEL_VAL(x)    VTSS_EXTRACT_BITFIELD(x,0,20)

/**
 * Register Group: \a REW:PORT
 *
 * Port based configuration and status for rewriter
 */


/**
 * \brief Configures per port custom values for TAGs
 *
 * \details
 * Register: \a REW:PORT:PORT_VLAN_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PORT_VLAN_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,0)

/**
 * \brief
 * PCP field in the TCI.
 *
 * \details
 * n: Port PCP value
 *
 * Field: ::VTSS_REW_PORT_VLAN_CFG . PORT_PCP
 */
#define  VTSS_F_REW_PORT_VLAN_CFG_PORT_PCP(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_REW_PORT_VLAN_CFG_PORT_PCP     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_REW_PORT_VLAN_CFG_PORT_PCP(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief
 * DEI field in the TCI.
 *
 * \details
 * n: Port DEI value
 *
 * Field: ::VTSS_REW_PORT_VLAN_CFG . PORT_DEI
 */
#define  VTSS_F_REW_PORT_VLAN_CFG_PORT_DEI(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_PORT_VLAN_CFG_PORT_DEI    VTSS_BIT(12)
#define  VTSS_X_REW_PORT_VLAN_CFG_PORT_DEI(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * VID field in the TCI.
 *
 * \details
 * n: Port VID
 *
 * Field: ::VTSS_REW_PORT_VLAN_CFG . PORT_VID
 */
#define  VTSS_F_REW_PORT_VLAN_CFG_PORT_VID(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_REW_PORT_VLAN_CFG_PORT_VID     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_REW_PORT_VLAN_CFG_PORT_VID(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief Map internal priority to tagged priority.
 *
 * \details
 * Register: \a REW:PORT:PCP_MAP_DE0
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 * @param ri Register: PCP_MAP_DE0 (??), 0-7
 */
#define VTSS_REW_PCP_MAP_DE0(gi,ri)          VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,ri,1)

/**
 * \brief
 * Map internal priority to UPRIO/PCP value in tags. This table used for DP
 * values mapped to 0 in REW::DP_MAP.DP.
 *
 * \details
 * Field: ::VTSS_REW_PCP_MAP_DE0 . PCP_DE0
 */
#define  VTSS_F_REW_PCP_MAP_DE0_PCP_DE0(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_PCP_MAP_DE0_PCP_DE0       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_PCP_MAP_DE0_PCP_DE0(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Map internal priority to tagged priority.
 *
 * \details
 * Register: \a REW:PORT:PCP_MAP_DE1
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 * @param ri Register: PCP_MAP_DE1 (??), 0-7
 */
#define VTSS_REW_PCP_MAP_DE1(gi,ri)          VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,ri,9)

/**
 * \brief
 * Map internal priority to UPRIO/PCP value in tags. This table used for DP
 * values mapped to 1 in REW::DP_MAP.DP.
 *
 * \details
 * Field: ::VTSS_REW_PCP_MAP_DE1 . PCP_DE1
 */
#define  VTSS_F_REW_PCP_MAP_DE1_PCP_DE1(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_PCP_MAP_DE1_PCP_DE1       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_PCP_MAP_DE1_PCP_DE1(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Map internal priority to tag value.
 *
 * \details
 * Register: \a REW:PORT:DEI_MAP_DE0
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 * @param ri Register: DEI_MAP_DE0 (??), 0-7
 */
#define VTSS_REW_DEI_MAP_DE0(gi,ri)          VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,ri,17)

/**
 * \brief
 * Map QoS/COSID/Classified PCP to CFI/DEI value in tags. This table used
 * for DP values mapped to 0 in REW::DP_MAP.DP.TAG_DEI_CFG controls whether
 * QoS or COSID is used for lookup in this table.Related
 * parameters:REW:PORT:TAG_CTRL.TAG_DEI_CFGREW:COMMON:DP_MAP.DP
 *
 * \details
 * Field: ::VTSS_REW_DEI_MAP_DE0 . DEI_DE0
 */
#define  VTSS_F_REW_DEI_MAP_DE0_DEI_DE0(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_DEI_MAP_DE0_DEI_DE0       VTSS_BIT(0)
#define  VTSS_X_REW_DEI_MAP_DE0_DEI_DE0(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Map internal priority to tag value.
 *
 * \details
 * Register: \a REW:PORT:DEI_MAP_DE1
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 * @param ri Register: DEI_MAP_DE1 (??), 0-7
 */
#define VTSS_REW_DEI_MAP_DE1(gi,ri)          VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,ri,25)

/**
 * \brief
 * Map QoS/COSID/Classified PCP to CFI/DEI value in tags. This table used
 * for DP values mapped to 1 in REW::DP_MAP.DP.TAG_DEI_CFG controls whether
 * QoS or COSID is used for lookup in this table.Related
 * parameters:REW:PORT:TAG_CTRL.TAG_DEI_CFGREW:COMMON:DP_MAP.DP
 *
 * \details
 * Field: ::VTSS_REW_DEI_MAP_DE1 . DEI_DE1
 */
#define  VTSS_F_REW_DEI_MAP_DE1_DEI_DE1(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_DEI_MAP_DE1_DEI_DE1       VTSS_BIT(0)
#define  VTSS_X_REW_DEI_MAP_DE1_DEI_DE1(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configure PORT tagging
 *
 * \details
 * Register: \a REW:PORT:TAG_CTRL
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_TAG_CTRL(gi)                VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,33)

/**
 * \brief
 * Control how port tags are added. If this bit is set, the IFH field
 * VSTAX.TAG.WAS_TAGGED must be '1' before a port tag is added to a
 * frame.See TAG_CTRL.TAG_CFG
 *
 * \details
 * 0: Normal port tagging mode
 * 1: Frames are not port tagged, if VSTAX.TAG.WAS_TAGGED = '0' regardless
 * of TAG_CTRL.TAG_CFG configuration

 *
 * Field: ::VTSS_REW_TAG_CTRL . TAG_CFG_OBEY_WAS_TAGGED
 */
#define  VTSS_F_REW_TAG_CTRL_TAG_CFG_OBEY_WAS_TAGGED(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_REW_TAG_CTRL_TAG_CFG_OBEY_WAS_TAGGED  VTSS_BIT(13)
#define  VTSS_X_REW_TAG_CTRL_TAG_CFG_OBEY_WAS_TAGGED(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Control port tagging.See TAG_CTRL.TAG_CFG_OBEY_WAS_TAGGED.
 *
 * \details
 * 0: Port tagging disabled
 * 1: Tag all frames, except when classified VID=PORT_VLAN_CFG.PORT_VID or
 * classified VID=0
 * 2: Tag all frames, except when classified VID=0
 * 3: Tag all frames
 *
 * Field: ::VTSS_REW_TAG_CTRL . TAG_CFG
 */
#define  VTSS_F_REW_TAG_CTRL_TAG_CFG(x)       VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_REW_TAG_CTRL_TAG_CFG          VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_REW_TAG_CTRL_TAG_CFG(x)       VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * Select Tag Protocol Identifier (TPID) for port tagging
 *
 * \details
 * 0: 0x8100
 * 1: 0x88A8
 * 2: Custom1. REW::TPID_CFG[0].TPID_VAL
 * 3: Custom2. REW::TPID_CFG[1].TPID_VAL
 * 4: Custom3. REW::TPID_CFG[2].TPID_VAL
 * 5: Select via ifh.vstax.tag_type and ifh.encap.tag_tpid
 *   If ifh.encap.tag_tipd = STD_TPID:
 *     If ifh.vstax.tag_type = 0 then 0x8100 else 0x88A8
 *   If ifh.encap.tag_tipd = CUSTOM<n>:
 *     Custom<n> TPID
 * 6-7: Reserved
 *
 * Field: ::VTSS_REW_TAG_CTRL . TAG_TPID_CFG
 */
#define  VTSS_F_REW_TAG_CTRL_TAG_TPID_CFG(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_REW_TAG_CTRL_TAG_TPID_CFG     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_REW_TAG_CTRL_TAG_TPID_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Select VID in port tag
 *
 * \details
 * Select VID in port tag.
 *
 * 0: Use XVID. This is the classified VID
 * 1: Use PORT_VLAN_CFG.PORT_VID
 * 2: Use GVID. This is the classified VID
 * 3: Reserved
 *
 * Field: ::VTSS_REW_TAG_CTRL . TAG_VID_CFG
 */
#define  VTSS_F_REW_TAG_CTRL_TAG_VID_CFG(x)   VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_REW_TAG_CTRL_TAG_VID_CFG      VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_REW_TAG_CTRL_TAG_VID_CFG(x)   VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Select PCP in port tag.0: Classified PCP: IFH.VSTAX.TAG.CL_PCP1:
 * PORT_PCP2: PCP value from PCP_MAP_DEx[IFH.VSTAX.QOS.CL_QOS]3:
 * IFH.VSTAX.QOS.CL_QOS4: PCP value from
 * PCP_MAP_DEx[IFH.VSTAX.MISC.COSID]5: IFH.VSTAX.MISC.COSID6: PCP value
 * from PCP_MAP_DEx[IFH.VSTAX.TAG.CL_PCP]7: ReservedRelated
 * parameters:REW:COMMON:DP_MAP.DPREW:PORT:PCP_MAP_DE0.PCP_DE0REW:PORT:PCP_
 * MAP_DE1.PCP_DE1REW:PORT:PORT_VLAN_CFG.PORT_PCP
 *
 * \details
 * Field: ::VTSS_REW_TAG_CTRL . TAG_PCP_CFG
 */
#define  VTSS_F_REW_TAG_CTRL_TAG_PCP_CFG(x)   VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_REW_TAG_CTRL_TAG_PCP_CFG      VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_REW_TAG_CTRL_TAG_PCP_CFG(x)   VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Select value of DEI field in port tag.0: Classified DEI:
 * IFH.VSTAX.TAG.CL_DEI1: PORT_DEI2: DEI value from
 * DEI_MAP_DEx[IFH.VSTAX.QOS.CL_QOS]3: DEI value from DP_MAP.DP4: DEI value
 * from DEI_MAP_DEx[IFH.VSTAX.MISC.COSID]5: DEI value from
 * DEI_MAP_DEx[IFH.VSTAX.TAG.CL_PCP]6-7: ReservedRelated
 * parameters:REW:COMMON:DP_MAP.DPREW:PORT:DEI_MAP_DE0.DEI_DE0REW:PORT:DEI_
 * MAP_DE1.DEI_DE1REW:PORT:PORT_VLAN_CFG.PORT_DEI
 *
 * \details
 * Field: ::VTSS_REW_TAG_CTRL . TAG_DEI_CFG
 */
#define  VTSS_F_REW_TAG_CTRL_TAG_DEI_CFG(x)   VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_TAG_CTRL_TAG_DEI_CFG      VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_TAG_CTRL_TAG_DEI_CFG(x)   VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Enable DSCP updates on the port.
 *
 * \details
 * Register: \a REW:PORT:DSCP_MAP
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_DSCP_MAP(gi)                VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,34)

/**
 * \brief
 * Control the "Selected DSCP" value.If DSCP_UPDATE_ENA=1 and
 * IFH.QOS.UPDATE_DSCP=1 then "Selected DSCP" is set to
 * IFH.QOS.DSCP.Otherwise "Selected DSCP" is set to frame DSCP."Selected
 * DSCP" is afterward potentially remapped (depending on DSCP_REMAP_ENA)
 * and written into the frame, see DSCP_REMAP_ENA.Related
 * parameters:REW:PORT:DSCP_MAP.DSCP_REMAP_ENA
 *
 * \details
 * Field: ::VTSS_REW_DSCP_MAP . DSCP_UPDATE_ENA
 */
#define  VTSS_F_REW_DSCP_MAP_DSCP_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_DSCP_MAP_DSCP_UPDATE_ENA  VTSS_BIT(1)
#define  VTSS_X_REW_DSCP_MAP_DSCP_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable use of a shared DSCP remap table (DSCP_REMAP).If DSCP_REMAP=1 and
 * IFH.QOS.TRANSP_DSCP=0, then the frame's DSCP is set to
 * DSCP_REMAP["Selected DSCP"]Otherwise the frame's DSCP is set to
 * "Selected DSCP".For a description of the algorithm used to deduct
 * "Selected DSCP" refer to DSCP_UPDATE_ENA.Related
 * parameters:REW:PORT:DSCP_MAP.DSCP_UPDATE_ENAREW:COMMON:DSCP_REMAPANA_CL:
 * PORT:QOS_CFG.DSCP_KEEP_ENA
 *
 * \details
 * Field: ::VTSS_REW_DSCP_MAP . DSCP_REMAP_ENA
 */
#define  VTSS_F_REW_DSCP_MAP_DSCP_REMAP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_DSCP_MAP_DSCP_REMAP_ENA   VTSS_BIT(0)
#define  VTSS_X_REW_DSCP_MAP_DSCP_REMAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief 1588 configuration
 *
 * \details
 * Selects mode of port when transmitting (index 0), or receiving (index 1)
 *
 * Register: \a REW:PORT:PTP_MODE_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 * @param ri Register: PTP_MODE_CFG (??), 0-1
 */
#define VTSS_REW_PTP_MODE_CFG(gi,ri)         VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,ri,35)

/**
 * \brief
 * PTP operation mode for frames.
 *
 * \details
 * 0: Front port
 * 1: Backplane port using RSRV field 30 bit TS transfer
 * 2: Backplane port using CF field for 48 bit TS transfer
 * 3: PTP Disabled port
 *
 * Field: ::VTSS_REW_PTP_MODE_CFG . PTP_MODE_VAL
 */
#define  VTSS_F_REW_PTP_MODE_CFG_PTP_MODE_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_REW_PTP_MODE_CFG_PTP_MODE_VAL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_REW_PTP_MODE_CFG_PTP_MODE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Sets the time domain this port belongs to.
 *
 * \details
 * Field: ::VTSS_REW_PTP_MODE_CFG . PTP_DOM_VAL
 */
#define  VTSS_F_REW_PTP_MODE_CFG_PTP_DOM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_PTP_MODE_CFG_PTP_DOM_VAL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_PTP_MODE_CFG_PTP_DOM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_MISC_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_MISC_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,37)

/**
 * \brief
 * Set to skip detection and indication of overflow conditions for frame
 * transmitted on this port
 *
 * \details
 * Field: ::VTSS_REW_PTP_MISC_CFG . PTP_OVFL_EGR_DIS
 */
#define  VTSS_F_REW_PTP_MISC_CFG_PTP_OVFL_EGR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_PTP_MISC_CFG_PTP_OVFL_EGR_DIS  VTSS_BIT(6)
#define  VTSS_X_REW_PTP_MISC_CFG_PTP_OVFL_EGR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set to skip detection and indication of overflow conditions for frames
 * received on this port
 *
 * \details
 * Field: ::VTSS_REW_PTP_MISC_CFG . PTP_OVFL_IGR_DIS
 */
#define  VTSS_F_REW_PTP_MISC_CFG_PTP_OVFL_IGR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_PTP_MISC_CFG_PTP_OVFL_IGR_DIS  VTSS_BIT(5)
#define  VTSS_X_REW_PTP_MISC_CFG_PTP_OVFL_IGR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set to skip update of udp checksums for IPv6 frames
 *
 * \details
 * Field: ::VTSS_REW_PTP_MISC_CFG . PTP_UDP6_CSUM_DIS
 */
#define  VTSS_F_REW_PTP_MISC_CFG_PTP_UDP6_CSUM_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_PTP_MISC_CFG_PTP_UDP6_CSUM_DIS  VTSS_BIT(4)
#define  VTSS_X_REW_PTP_MISC_CFG_PTP_UDP6_CSUM_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set to disable clearing of checksum field in IPv4 frames
 *
 * \details
 * Field: ::VTSS_REW_PTP_MISC_CFG . PTP_UDP4_CSUM_DIS
 */
#define  VTSS_F_REW_PTP_MISC_CFG_PTP_UDP4_CSUM_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_PTP_MISC_CFG_PTP_UDP4_CSUM_DIS  VTSS_BIT(3)
#define  VTSS_X_REW_PTP_MISC_CFG_PTP_UDP4_CSUM_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * If set, the egress device time stamp will be reduced to the nearest
 * integer nanosec value, which then will be reported through the RSRV
 * field in the outgoing PDU.
 *
 * \details
 * Field: ::VTSS_REW_PTP_MISC_CFG . PTP_RSRV_MOVEBACK
 */
#define  VTSS_F_REW_PTP_MISC_CFG_PTP_RSRV_MOVEBACK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_PTP_MISC_CFG_PTP_RSRV_MOVEBACK  VTSS_BIT(2)
#define  VTSS_X_REW_PTP_MISC_CFG_PTP_RSRV_MOVEBACK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Select the signature to use in the TS fifo. The on chip TS fifo includes
 * a 47 bit signature field, and the full ingress time stamp and source
 * port number can then be used as a signature.When an external PHY is
 * holding the fifo, the PCH header can only transfer 15 bit signature.
 *
 * \details
 * 00: 15 bits nanosec part of rx stamp
 * 01: 8 LSBs(SubNS) of rx stamp + 7 bits source port
 * 10: Bits 15:8 of nanosec, and 7 bit source port
 * 11: Bits 7:0 of PDU sequence no, and 7 bit source port.
 *
 * Field: ::VTSS_REW_PTP_MISC_CFG . PTP_SIGNATURE_SEL
 */
#define  VTSS_F_REW_PTP_MISC_CFG_PTP_SIGNATURE_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_PTP_MISC_CFG_PTP_SIGNATURE_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_PTP_MISC_CFG_PTP_SIGNATURE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_EDLY_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_EDLY_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,38)

/**
 * \brief
 * Signed value to add to CF when frame is transmitted on this port. Field
 * is used if requested through the analyzer match rule. This value can be
 * used as the egress asymmetry delay for the particular PTP flow.
 *
 * \details
 * Field: ::VTSS_REW_PTP_EDLY_CFG . PTP_EDLY_VAL
 */
#define  VTSS_F_REW_PTP_EDLY_CFG_PTP_EDLY_VAL(x)  (x)
#define  VTSS_M_REW_PTP_EDLY_CFG_PTP_EDLY_VAL     0xffffffff
#define  VTSS_X_REW_PTP_EDLY_CFG_PTP_EDLY_VAL(x)  (x)


/**
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_EDLY_CFG1
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_EDLY_CFG1(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,39)

/**
 * \brief
 * Signed value to add to CF when frame is transmitted on this port. Field
 * is used if requested through the analyzer match rule. This value can be
 * used as the egress asymmetry delay for the particular PTP flow.
 *
 * \details
 * Field: ::VTSS_REW_PTP_EDLY_CFG1 . PTP_EDLY_VAL1
 */
#define  VTSS_F_REW_PTP_EDLY_CFG1_PTP_EDLY_VAL1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_PTP_EDLY_CFG1_PTP_EDLY_VAL1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_PTP_EDLY_CFG1_PTP_EDLY_VAL1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_IDLY1_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_IDLY1_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,40)

/**
 * \brief
 * Signed value to add to CF when frame is received on this port. Field is
 * used if requested through the analyzer match rule. This value can be
 * used as the ingress asymmetry or ingress asymmetry+path delay for the
 * particular PTP flow.
 *
 * \details
 * Field: ::VTSS_REW_PTP_IDLY1_CFG . PTP_IDLY1_VAL
 */
#define  VTSS_F_REW_PTP_IDLY1_CFG_PTP_IDLY1_VAL(x)  (x)
#define  VTSS_M_REW_PTP_IDLY1_CFG_PTP_IDLY1_VAL     0xffffffff
#define  VTSS_X_REW_PTP_IDLY1_CFG_PTP_IDLY1_VAL(x)  (x)


/**
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_IDLY1_CFG1
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_IDLY1_CFG1(gi)          VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,41)

/**
 * \brief
 * Signed value to add to CF when frame is received on this port. Field is
 * used if requested through the analyzer match rule. This value can be
 * used as the ingress asymmetry or ingress asymmetry+path delay for the
 * particular PTP flow.
 *
 * \details
 * Field: ::VTSS_REW_PTP_IDLY1_CFG1 . PTP_IDLY1_VAL1
 */
#define  VTSS_F_REW_PTP_IDLY1_CFG1_PTP_IDLY1_VAL1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_PTP_IDLY1_CFG1_PTP_IDLY1_VAL1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_PTP_IDLY1_CFG1_PTP_IDLY1_VAL1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_IDLY2_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_IDLY2_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,42)

/**
 * \brief
 * Signed value to add to CF when frame is received on this port. Field is
 * used if requested through the analyzer match rule. This value can be
 * used as the ingress asymmetry or ingress asymmetry+path delay for the
 * particular PTP flow.
 *
 * \details
 * Field: ::VTSS_REW_PTP_IDLY2_CFG . PTP_IDLY2_VAL
 */
#define  VTSS_F_REW_PTP_IDLY2_CFG_PTP_IDLY2_VAL(x)  (x)
#define  VTSS_M_REW_PTP_IDLY2_CFG_PTP_IDLY2_VAL     0xffffffff
#define  VTSS_X_REW_PTP_IDLY2_CFG_PTP_IDLY2_VAL(x)  (x)


/**
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_IDLY2_CFG1
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_IDLY2_CFG1(gi)          VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,43)

/**
 * \brief
 * Signed value to add to CF when frame is received on this port. Field is
 * used if requested through the analyzer match rule. This value can be
 * used as the ingress asymmetry or ingress asymmetry+path delay for the
 * particular PTP flow.
 *
 * \details
 * Field: ::VTSS_REW_PTP_IDLY2_CFG1 . PTP_IDLY2_VAL1
 */
#define  VTSS_F_REW_PTP_IDLY2_CFG1_PTP_IDLY2_VAL1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_PTP_IDLY2_CFG1_PTP_IDLY2_VAL1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_PTP_IDLY2_CFG1_PTP_IDLY2_VAL1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Low 32 bits of PTP Mac Address
 *
 * \details
 * Register: \a REW:PORT:PTP_SMAC_LOW
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_SMAC_LOW(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,44)

/**
 * \brief
 * If requested by the PTP action out of the analyzer, this MAC address can
 * be pasted into the SMAC.
 *
 * \details
 * Field: ::VTSS_REW_PTP_SMAC_LOW . PTP_SMAC_LOW
 */
#define  VTSS_F_REW_PTP_SMAC_LOW_PTP_SMAC_LOW(x)  (x)
#define  VTSS_M_REW_PTP_SMAC_LOW_PTP_SMAC_LOW     0xffffffff
#define  VTSS_X_REW_PTP_SMAC_LOW_PTP_SMAC_LOW(x)  (x)


/**
 * \brief High 16 bits of PTP Mac Address
 *
 * \details
 * Register: \a REW:PORT:PTP_SMAC_HIGH
 *
 * @param gi Replicator: x_FFL_REW_NUM_PHYS_PORTS (??), 0-34
 */
#define VTSS_REW_PTP_SMAC_HIGH(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x2000,gi,64,0,45)

/**
 * \brief
 * If requested by the PTP action out of the analyzer, this MAC address can
 * be pasted into the SMAC.
 *
 * \details
 * Field: ::VTSS_REW_PTP_SMAC_HIGH . PTP_SMAC_HIGH
 */
#define  VTSS_F_REW_PTP_SMAC_HIGH_PTP_SMAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_PTP_SMAC_HIGH_PTP_SMAC_HIGH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_PTP_SMAC_HIGH_PTP_SMAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a REW:MIP_TBL
 *
 * MIP table
 */


/**
 * \brief MIP configuration
 *
 * \details
 * Register: \a REW:MIP_TBL:MIP_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_MIP_TBL_ENTRIES (??), 0-7
 */
#define VTSS_REW_MIP_CFG(gi)                 VTSS_IOREG_IX(VTSS_TO_REW,0x28c0,gi,8,0,0)

/**
 * \brief
 * MEL value for the MIP.
 *
 * \details
 * Field: ::VTSS_REW_MIP_CFG . MEL_VAL
 */
#define  VTSS_F_REW_MIP_CFG_MEL_VAL(x)        VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_REW_MIP_CFG_MEL_VAL           VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_REW_MIP_CFG_MEL_VAL(x)        VTSS_EXTRACT_BITFIELD(x,19,3)

/**
 * \brief
 * If set, OAM Y.1731 CCM frames with the correct encapsulation and the
 * correct MEL are copied to the CPU.
 *
 * \details
 * Field: ::VTSS_REW_MIP_CFG . CCM_COPY_ENA
 */
#define  VTSS_F_REW_MIP_CFG_CCM_COPY_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_REW_MIP_CFG_CCM_COPY_ENA      VTSS_BIT(18)
#define  VTSS_X_REW_MIP_CFG_CCM_COPY_ENA(x)   VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * If set, OAM Y.1731 LBM frames with the correct encapsulation, the
 * correct MEL, and the correct destination MAC address are redirected to
 * the CPU.
 *
 * \details
 * Field: ::VTSS_REW_MIP_CFG . LBM_REDIR_ENA
 */
#define  VTSS_F_REW_MIP_CFG_LBM_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_REW_MIP_CFG_LBM_REDIR_ENA     VTSS_BIT(17)
#define  VTSS_X_REW_MIP_CFG_LBM_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * If set, OAM Y.1731 LTM frames with the correct encapsulation and the
 * correct MEL are redirected to the CPU.
 *
 * \details
 * Field: ::VTSS_REW_MIP_CFG . LTM_REDIR_ENA
 */
#define  VTSS_F_REW_MIP_CFG_LTM_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_MIP_CFG_LTM_REDIR_ENA     VTSS_BIT(16)
#define  VTSS_X_REW_MIP_CFG_LTM_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Handling of OAM Y.1731 frames with Opcode=RAPS, correct encapsulation,
 * and correct MEL.
 *
 * \details
 *
 * 0: No handling
 * 1: Copy to CPU
 * 2: Redirect to CPU
 * 3: Discard
 *
 * Field: ::VTSS_REW_MIP_CFG . RAPS_CFG
 */
#define  VTSS_F_REW_MIP_CFG_RAPS_CFG(x)       VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_REW_MIP_CFG_RAPS_CFG          VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_REW_MIP_CFG_RAPS_CFG(x)       VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * Generic Opcode. See GENERIC_OPCODE_CFG.
 *
 * \details
 * Field: ::VTSS_REW_MIP_CFG . GENERIC_OPCODE_VAL
 */
#define  VTSS_F_REW_MIP_CFG_GENERIC_OPCODE_VAL(x)  VTSS_ENCODE_BITFIELD(x,6,8)
#define  VTSS_M_REW_MIP_CFG_GENERIC_OPCODE_VAL     VTSS_ENCODE_BITMASK(6,8)
#define  VTSS_X_REW_MIP_CFG_GENERIC_OPCODE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,6,8)

/**
 * \brief
 * Handling of OAM Y.1731 frames with Opcode=GENERIC_OPCODE_VAL, correct
 * encapsulation, and correct MEL.
 *
 * \details
 *
 * 0: No handling
 * 1: Copy to CPU
 * 2: Redirect to CPU
 * 3: Discard
 *
 * Field: ::VTSS_REW_MIP_CFG . GENERIC_OPCODE_CFG
 */
#define  VTSS_F_REW_MIP_CFG_GENERIC_OPCODE_CFG(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_REW_MIP_CFG_GENERIC_OPCODE_CFG     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_REW_MIP_CFG_GENERIC_OPCODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * CPU extraction queue when frame is forwarded to CPU.
 *
 * \details
 * Field: ::VTSS_REW_MIP_CFG . CPU_MIP_QU
 */
#define  VTSS_F_REW_MIP_CFG_CPU_MIP_QU(x)     VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_REW_MIP_CFG_CPU_MIP_QU        VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_REW_MIP_CFG_CPU_MIP_QU(x)     VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * MIP location. This influences in particular the update of loss
 * measurement statistics for MEPs.
 *
 * \details
 * 0: REW_IN_MIP
 * 1: REW_OU_MIP
 *
 * Field: ::VTSS_REW_MIP_CFG . PIPELINE_PT
 */
#define  VTSS_F_REW_MIP_CFG_PIPELINE_PT(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_MIP_CFG_PIPELINE_PT       VTSS_BIT(0)
#define  VTSS_X_REW_MIP_CFG_PIPELINE_PT(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Allows sending a single CCM frame to CPU
 *
 * \details
 * Register: \a REW:MIP_TBL:CCM_HMO_CTRL
 *
 * @param gi Replicator: x_FFL_REW_NUM_MIP_TBL_ENTRIES (??), 0-7
 */
#define VTSS_REW_CCM_HMO_CTRL(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x28c0,gi,8,0,1)

/**
 * \brief
 * Interval used for automatically setting CCM_COPY_ONCE_ENA based on
 * REW::MIP_CTRL.MIP_CCM_HMO_SET_SHOTCCM_COPY_ONCE_ENA are only set by
 * hardware if MIP_CCM_INTERVAL_MASK[CCM_HMO_CTRL.CCM_INTERVAL] is set
 *
 * \details
 * Field: ::VTSS_REW_CCM_HMO_CTRL . CCM_INTERVAL
 */
#define  VTSS_F_REW_CCM_HMO_CTRL_CCM_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_REW_CCM_HMO_CTRL_CCM_INTERVAL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_REW_CCM_HMO_CTRL_CCM_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Send the next received CCM frame to CPU. Cleared by HW when a CPU copy
 * has been send to CPU
 *
 * \details
 * Field: ::VTSS_REW_CCM_HMO_CTRL . CCM_COPY_ONCE_ENA
 */
#define  VTSS_F_REW_CCM_HMO_CTRL_CCM_COPY_ONCE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_CCM_HMO_CTRL_CCM_COPY_ONCE_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_CCM_HMO_CTRL_CCM_COPY_ONCE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Controls classified VID check
 *
 * \details
 * Register: \a REW:MIP_TBL:MIP_VID_CTRL
 *
 * @param gi Replicator: x_FFL_REW_NUM_MIP_TBL_ENTRIES (??), 0-7
 */
#define VTSS_REW_MIP_VID_CTRL(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x28c0,gi,8,0,2)

/**
 * \brief
 * Required outer VID to identify frame as MIP.
 *
 * \details
 * n: Outer VID value
 *
 * Field: ::VTSS_REW_MIP_VID_CTRL . VID_VAL
 */
#define  VTSS_F_REW_MIP_VID_CTRL_VID_VAL(x)   VTSS_ENCODE_BITFIELD(x,2,12)
#define  VTSS_M_REW_MIP_VID_CTRL_VID_VAL      VTSS_ENCODE_BITMASK(2,12)
#define  VTSS_X_REW_MIP_VID_CTRL_VID_VAL(x)   VTSS_EXTRACT_BITFIELD(x,2,12)

/**
 * \brief
 * Outer VID check. Configure how the outer frame VID is matched before a
 * frame is accepted as MIP.
 *
 * \details
 * 0: VID check is disabled. Frame is always accepted.
 * 1: Accept untagged frames. Tagged frames are not accepted.
 * 2: Accept single tagged frames with VID = VID_VAL. Untagged frames or
 * frames with multiple VLAN tags are not accepted.
 * 3: Accept untagged frames and single tagged frames with VID = VID_VAL.
 * Frames with multiple VLAN tags are not accepted.
 *
 * Field: ::VTSS_REW_MIP_VID_CTRL . VID_SEL
 */
#define  VTSS_F_REW_MIP_VID_CTRL_VID_SEL(x)   VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_MIP_VID_CTRL_VID_SEL      VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_MIP_VID_CTRL_VID_SEL(x)   VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief MAC address - bits 47:32
 *
 * \details
 * Register: \a REW:MIP_TBL:LBM_MAC_HIGH
 *
 * @param gi Replicator: x_FFL_REW_NUM_MIP_TBL_ENTRIES (??), 0-7
 */
#define VTSS_REW_LBM_MAC_HIGH(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x28c0,gi,8,0,3)

/**
 * \brief
 * Destination MAC address bits 47:32 used for LBM. If LBM_MAC_HIGH = 0 and
 * LBM_MAC_LOW = 0, the MAC address check for LBM frames is disabled.
 *
 * \details
 * Field: ::VTSS_REW_LBM_MAC_HIGH . LBM_MAC_HIGH
 */
#define  VTSS_F_REW_LBM_MAC_HIGH_LBM_MAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_LBM_MAC_HIGH_LBM_MAC_HIGH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_LBM_MAC_HIGH_LBM_MAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief MAC address configuration - bits 31:0
 *
 * \details
 * Register: \a REW:MIP_TBL:LBM_MAC_LOW
 *
 * @param gi Replicator: x_FFL_REW_NUM_MIP_TBL_ENTRIES (??), 0-7
 */
#define VTSS_REW_LBM_MAC_LOW(gi)             VTSS_IOREG_IX(VTSS_TO_REW,0x28c0,gi,8,0,4)

/**
 * \brief
 * Destination MAC address bit 31:0 used for LBM. See LBM_MAC_HIGH.
 *
 * \details
 * Field: ::VTSS_REW_LBM_MAC_LOW . LBM_MAC_LOW
 */
#define  VTSS_F_REW_LBM_MAC_LOW_LBM_MAC_LOW(x)  (x)
#define  VTSS_M_REW_LBM_MAC_LOW_LBM_MAC_LOW     0xffffffff
#define  VTSS_X_REW_LBM_MAC_LOW_LBM_MAC_LOW(x)  (x)

/**
 * Register Group: \a REW:MAC_TBL
 *
 * MAC address translation table
 */


/**
 * \brief MAC address replace configuration
 *
 * \details
 * MAC replacement configuration
 *
 * Register: \a REW:MAC_TBL:MAC_TBL_CFG
 *
 * @param gi Replicator: x_FFL_REW_MAC_TBL_ENTRY_CNT (??), 0-31
 */
#define VTSS_REW_MAC_TBL_CFG(gi)             VTSS_IOREG_IX(VTSS_TO_REW,0x2900,gi,4,0,0)

/**
 * \brief
 * Number of bits in frame's MAC counting from LSB which are not replaced
 * if replacing the MAC addressFor example, if set to 16, the 16 LSB bits
 * in the frame's MAC address are not replaced while the 32 MSB bits are
 * replaced with corresponding 32 bits from the associated MAC address.
 *
 * \details
 * Field: ::VTSS_REW_MAC_TBL_CFG . MAC_REPL_OFFSET_VAL
 */
#define  VTSS_F_REW_MAC_TBL_CFG_MAC_REPL_OFFSET_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_REW_MAC_TBL_CFG_MAC_REPL_OFFSET_VAL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_REW_MAC_TBL_CFG_MAC_REPL_OFFSET_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief EACL MAC address configuration - bits 47:32
 *
 * \details
 * MAC address bits 47:32 used for MAC address translation. See REW:MAC_TBL
 *
 * Register: \a REW:MAC_TBL:EACL_MAC_HIGH
 *
 * @param gi Replicator: x_FFL_REW_MAC_TBL_ENTRY_CNT (??), 0-31
 */
#define VTSS_REW_EACL_MAC_HIGH(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x2900,gi,4,0,1)

/**
 * \brief
 * MAC address bits 47:32 used for EACL MAC translation
 *
 * \details
 * Field: ::VTSS_REW_EACL_MAC_HIGH . EACL_MAC_HIGH
 */
#define  VTSS_F_REW_EACL_MAC_HIGH_EACL_MAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_EACL_MAC_HIGH_EACL_MAC_HIGH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_EACL_MAC_HIGH_EACL_MAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief EACL MAC address configuration - bits 31:0
 *
 * \details
 * MAC address bits 31:0 used for MAC address translation. See REW:MAC_TBL
 *
 * Register: \a REW:MAC_TBL:EACL_MAC_LOW
 *
 * @param gi Replicator: x_FFL_REW_MAC_TBL_ENTRY_CNT (??), 0-31
 */
#define VTSS_REW_EACL_MAC_LOW(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x2900,gi,4,0,2)

/**
 * \brief
 * MAC address bits 31:0 used for EACL MAC translation
 *
 * \details
 * Field: ::VTSS_REW_EACL_MAC_LOW . EACL_MAC_LOW
 */
#define  VTSS_F_REW_EACL_MAC_LOW_EACL_MAC_LOW(x)  (x)
#define  VTSS_M_REW_EACL_MAC_LOW_EACL_MAC_LOW     0xffffffff
#define  VTSS_X_REW_EACL_MAC_LOW_EACL_MAC_LOW(x)  (x)

/**
 * Register Group: \a REW:ISDX_TBL
 *
 * ISDX configuration table
 */


/**
 * \brief COSID value selection
 *
 * \details
 * The multi COSID auto update function is active if the following IFH
 * fields are set by the AFI in the injected frames:
 *
 * IFH.FWD.TS_MODE = INJ_LBK
 * IFH.TS.INJ_LBK.COS_NXT_SEL: Selects one of three multi COSID injections
 * per ISDX (0:
 * disable)
 * IFH.TS.INJ_LBK.COS_MASK[7:0] : Specifies the COSIDs to be used.
 * IFH.TS.INJ_LBK.CHG_COSID_ENA: Controls updating of IFH.VSTAX.MISC.COSID
 * IFH.TS.INJ_LBK.CHG_OUTER_PCP_ENA: Controls updating of outermost PCP
 * value
 * IFH.TS.INJ_LBK.CHG_IFH_TC_ENA: Controls updating of
 * IFH.DST.ENCAP.MPLS_TC
 * IFH.TS.INJ_LBK.CHG_IFH_PCP_ENA: Controls updating of IFH.VSTAX.TAG.UPRIO
 *
 * The multi COSID function operates differently for injected Up-MEP or
 * Down-MEP frames.
 *
 * Up-MEP frames are injected by the AFI on the VD1 port and looped back to
 * the ANA. Injected Up-MEP frames are modified when they pass through the
 * REW the first time on the VD1 port. The IFH of the looped frames will be
 * modified if enabled by the CHG-fields. The PCP of the outer most VLAN
 * tag in the ETH link layer is changed if this is enabled. The
 * IFH.TS.INJ_LBK.COS_NXT_SEL field is set to 0 to in the frame. This
 * disables further COSID updates when the frame reaches the REW again
 * after the loop back.
 *
 * Down-MEP frames are injected by the AFI on a physical port. If enabled
 * by the INJ_LBK.CHG bits the the REW will use the new COSID value for the
 * selected fields. The INJ_LBK.CHG_OUTER_PCP_ENA field has no
 * functionality in Down-MEP mode. The outer PCP value will be controlled
 * by the normal tagging configuration.

 *
 * Register: \a REW:ISDX_TBL:COS_CTRL
 *
 * @param gi Replicator: x_FFL_CHIP_NUM_SDX (??), 0-31
 * @param ri Register: COS_CTRL (??), 0-2
 */
#define VTSS_REW_COS_CTRL(gi,ri)             VTSS_IOREG_IX(VTSS_TO_REW,0x2980,gi,4,ri,0)

/**
 * \brief
 * The auto updated COSID value is determined according to the following
 * algorithm:mask = IFH.TS.INJ_LBK.COS_MASK[7:0]isdx =
 * IFH.VSTAX.MISC.ISDXcos_nxt_sel = IFH.TS.INJ_LBK.COS_NXT_SELif
 * (cos_nxt_sel > 0 and isdx > 0 and mask > 0) {  cos_nxt =
 * REW:ISDX_TBL:COS_CTRL[IFH.VSTAX.MISC.ISDX].COS_NXT[cos_nxt_sel-1]  # Use
 * cos_nxt to find next bit in cos_mask       for idx in 0:7 {	  if
 * (mask[(idx+cos_nxt) mod 8] = '1') {	    cosid_new = idx	 break	  }
 *  }  # Update next pointer
 * REW:ISDX_TBL:COS_CTRL[IFH.VSTAX.MISC.ISDX].COS_NXT[cos_nxt_sel-1] =
 * ((cosid_new+1) mod 8)}
 *
 * \details
 * 0-7: Next COS value to use
 *
 * Field: ::VTSS_REW_COS_CTRL . COS_NXT
 */
#define  VTSS_F_REW_COS_CTRL_COS_NXT(x)       VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_COS_CTRL_COS_NXT          VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_COS_CTRL_COS_NXT(x)       VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a REW:PTP_CTRL
 *
 * PTP Control
 */


/**
 * \brief PTP reserved field check
 *
 * \details
 * Register: \a REW:PTP_CTRL:PTP_RSRV_NOT_ZERO
 */
#define VTSS_REW_PTP_RSRV_NOT_ZERO           VTSS_IOREG(VTSS_TO_REW,0x3e22)

/**
 * \brief
 * Register contains one bit per port being set when the port has received
 * a frame with non-zero reserved bytes field
 *
 * \details
 * Field: ::VTSS_REW_PTP_RSRV_NOT_ZERO . PTP_RSRV_NOT_ZERO
 */
#define  VTSS_F_REW_PTP_RSRV_NOT_ZERO_PTP_RSRV_NOT_ZERO(x)  (x)
#define  VTSS_M_REW_PTP_RSRV_NOT_ZERO_PTP_RSRV_NOT_ZERO     0xffffffff
#define  VTSS_X_REW_PTP_RSRV_NOT_ZERO_PTP_RSRV_NOT_ZERO(x)  (x)


/**
 * \brief PTP reserved field check
 *
 * \details
 * Register: \a REW:PTP_CTRL:PTP_RSRV_NOT_ZERO1
 */
#define VTSS_REW_PTP_RSRV_NOT_ZERO1          VTSS_IOREG(VTSS_TO_REW,0x3e23)

/**
 * \brief
 * Register contains one bit per port being set when the port has received
 * a frame with non-zero reserved bytes field
 *
 * \details
 * Field: ::VTSS_REW_PTP_RSRV_NOT_ZERO1 . PTP_RSRV_NOT_ZERO1
 */
#define  VTSS_F_REW_PTP_RSRV_NOT_ZERO1_PTP_RSRV_NOT_ZERO1(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_PTP_RSRV_NOT_ZERO1_PTP_RSRV_NOT_ZERO1     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_PTP_RSRV_NOT_ZERO1_PTP_RSRV_NOT_ZERO1(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Ingress time stamp
 *
 * \details
 * Register: \a REW:PTP_CTRL:PTP_GEN_STAMP_FMT
 *
 * @param ri Register: PTP_GEN_STAMP_FMT (??), 0-3
 */
#define VTSS_REW_PTP_GEN_STAMP_FMT(ri)       VTSS_IOREG(VTSS_TO_REW,0x3e25 + (ri))

/**
 * \brief
 * Location of generic residence time field.
 *
 * \details
 * 0: Byte 0 within payload.
 * 1: Byte 2 within payload
 * n: Byte (n x 2) within payload

 *
 * Field: ::VTSS_REW_PTP_GEN_STAMP_FMT . RT_OFS
 */
#define  VTSS_F_REW_PTP_GEN_STAMP_FMT_RT_OFS(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_REW_PTP_GEN_STAMP_FMT_RT_OFS     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_REW_PTP_GEN_STAMP_FMT_RT_OFS(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/**
 * \brief
 * Value format for recidense time field, expressed as fixed point number
 * of nanoseconds.
 *
 * \details
 * 00: 48.16 (PTPv2 CF)
 * 01: 24.0 with overflow 6 bits in front (GOOSE)
 * 10: 16.16
 * 11: 32.0

 *
 * Field: ::VTSS_REW_PTP_GEN_STAMP_FMT . RT_FMT
 */
#define  VTSS_F_REW_PTP_GEN_STAMP_FMT_RT_FMT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_PTP_GEN_STAMP_FMT_RT_FMT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_PTP_GEN_STAMP_FMT_RT_FMT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a REW:ENCAP
 *
 * Encapsulation RAM configuration
 */


/**
 * \brief Configure format of encapsulation
 *
 * \details
 * The encapsulation table can be used to control both MPLS and and
 * IP-in-IPv4  encapsulations
 *
 * Register: \a REW:ENCAP:MPLS_ENCAP_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_MPLS_ENCAP_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,0)

/**
 * \brief
 * Configure format of table entry
 *
 * \details
 * 0: Normal (REW:ENCAP)
 * 1: IP (REW:ENCAP_IP4)
 *
 * Field: ::VTSS_REW_MPLS_ENCAP_CFG . ENCAP_TYPE
 */
#define  VTSS_F_REW_MPLS_ENCAP_CFG_ENCAP_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_MPLS_ENCAP_CFG_ENCAP_TYPE  VTSS_BIT(0)
#define  VTSS_X_REW_MPLS_ENCAP_CFG_ENCAP_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configure DMAC of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_DMAC_MSB
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_LL_DMAC_MSB(gi)             VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,1)

/**
 * \brief
 * DMAC in Link layer. 16 MSB
 *
 * \details
 * n: DMAC MSB
 *
 * Field: ::VTSS_REW_LL_DMAC_MSB . DMAC_MSB
 */
#define  VTSS_F_REW_LL_DMAC_MSB_DMAC_MSB(x)   VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_LL_DMAC_MSB_DMAC_MSB      VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_LL_DMAC_MSB_DMAC_MSB(x)   VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configure DMAC of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_DMAC_LSB
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_LL_DMAC_LSB(gi)             VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,2)

/**
 * \brief
 * DMAC in Link layer. 32 LSB
 *
 * \details
 * n: DMAC LSB
 *
 * Field: ::VTSS_REW_LL_DMAC_LSB . DMAC_LSB
 */
#define  VTSS_F_REW_LL_DMAC_LSB_DMAC_LSB(x)   (x)
#define  VTSS_M_REW_LL_DMAC_LSB_DMAC_LSB      0xffffffff
#define  VTSS_X_REW_LL_DMAC_LSB_DMAC_LSB(x)   (x)


/**
 * \brief Configure SMAC of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_SMAC_MSB
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_LL_SMAC_MSB(gi)             VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,3)

/**
 * \brief
 * SMAC in Link layer. 16 MSB
 *
 * \details
 * n: SMAC MSB
 *
 * Field: ::VTSS_REW_LL_SMAC_MSB . SMAC_MSB
 */
#define  VTSS_F_REW_LL_SMAC_MSB_SMAC_MSB(x)   VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_LL_SMAC_MSB_SMAC_MSB      VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_LL_SMAC_MSB_SMAC_MSB(x)   VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configure SMAC of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_SMAC_LSB
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_LL_SMAC_LSB(gi)             VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,4)

/**
 * \brief
 * SMAC in Link layer. 32 LSB
 *
 * \details
 * n: SMAC LSB
 *
 * Field: ::VTSS_REW_LL_SMAC_LSB . SMAC_LSB
 */
#define  VTSS_F_REW_LL_SMAC_LSB_SMAC_LSB(x)   (x)
#define  VTSS_M_REW_LL_SMAC_LSB_SMAC_LSB      0xffffffff
#define  VTSS_X_REW_LL_SMAC_LSB_SMAC_LSB(x)   (x)


/**
 * \brief Configure ETYPE of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_ETYPE
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_LL_ETYPE(gi)                VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,5)

/**
 * \brief
 * Ethertype in Link layer
 *
 * \details
 * n: Ethertype
 *
 * Field: ::VTSS_REW_LL_ETYPE . ETYPE
 */
#define  VTSS_F_REW_LL_ETYPE_ETYPE(x)         VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_LL_ETYPE_ETYPE            VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_LL_ETYPE_ETYPE(x)         VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configure MPLS label
 *
 * \details
 * Register: \a REW:ENCAP:MPLS_LABEL_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_MPLS_LABEL_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,6)

/**
 * \brief
 * Configure the number of MPLS labels to use for this encapsulation entry
 *
 * \details
 * 0: No Labels in encapsulation
 * 1: One MPLS label
 * 2: Two MPLS labels
 * 3: Three MPLS labels
 * 4: Four MPLS labels
 * 5-7: Reserved

 *
 * Field: ::VTSS_REW_MPLS_LABEL_CFG . LABEL_CNT
 */
#define  VTSS_F_REW_MPLS_LABEL_CFG_LABEL_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_REW_MPLS_LABEL_CFG_LABEL_CNT     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_REW_MPLS_LABEL_CFG_LABEL_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Configure Control Word (CW) in label stack
 *
 * \details
 * 0: No Control Word
 * 1: Add Control Word

 *
 * Field: ::VTSS_REW_MPLS_LABEL_CFG . CW_ENA
 */
#define  VTSS_F_REW_MPLS_LABEL_CFG_CW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_MPLS_LABEL_CFG_CW_ENA     VTSS_BIT(3)
#define  VTSS_X_REW_MPLS_LABEL_CFG_CW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Select source of labels number 1 to 3. The sources can be ES0 or
 * encapsulation RAM. Label 0 is always sourced from the encapsulation RAM
 *
 * \details
 * xx0: Label 1 is sourced from encapsulation RAM
 * xx1: Label 1 is sourced from ES0
 * x0x: Label 2 is sourced from encapsulation RAM
 * x1x: Label 2 is sourced from ES0
 * 0xx: Label 3 is sourced from encapsulation RAM
 * 1xx: Label 3 is sourced from ES0
 *
 * Field: ::VTSS_REW_MPLS_LABEL_CFG . LBL_SRC
 */
#define  VTSS_F_REW_MPLS_LABEL_CFG_LBL_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_MPLS_LABEL_CFG_LBL_SRC     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_MPLS_LABEL_CFG_LBL_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configure MPLS label
 *
 * \details
 * Register: \a REW:ENCAP:RSV_LABEL_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_RSV_LABEL_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,7)

/**
 * \brief
 * Configure TC-field used in the reserved label
 *
 * \details
 * 0 : Classified TC
 * 1 : RSV_LABEL_VAL.RSV_TC_VAL
 * 2-3: Reserved
 * 4: Mapped using mapping table 0, otherwise use RSV_LABEL_VAL.RSV_TC_VAL
 * 5: Mapped using mapping table 1, otherwise use mapping table 0
 * 6: Mapped using mapping table 2, otherwise use RSV_LABEL_VAL.RSV_TC_VAL
 * 7: Mapped using mapping table 3, otherwise use mapping table 2

 *
 * Field: ::VTSS_REW_RSV_LABEL_CFG . RSV_TC_SEL
 */
#define  VTSS_F_REW_RSV_LABEL_CFG_RSV_TC_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_REW_RSV_LABEL_CFG_RSV_TC_SEL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_REW_RSV_LABEL_CFG_RSV_TC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/**
 * \brief
 * Select position of the reserved label. It can be added before or after
 * the last MPLS label
 *
 * \details
 * 0: Add before last label
 * 1: Add after last label like the CW

 *
 * Field: ::VTSS_REW_RSV_LABEL_CFG . RSV_LBL_POS
 */
#define  VTSS_F_REW_RSV_LABEL_CFG_RSV_LBL_POS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_RSV_LABEL_CFG_RSV_LBL_POS  VTSS_BIT(1)
#define  VTSS_X_REW_RSV_LABEL_CFG_RSV_LBL_POS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable reserved MPLS label insertion for MPLS-OAM frames. When this bit
 * is set, an additional MPLS label is inserted if CW insertion is disabled
 * and IFH.DST.ENCAP.PDU_TYPE=OAM_MPLS_TP or IFH.DST.ENCAP.PDU_TYPE=Y1731
 * and IFH.DST.ENCAP.TYPE_AFTER_POP=CWNote: The reserved label can only be
 * inserted if a CW is not inserted for the frame.
 *
 * \details
 * 0: Disabled
 * 1: Add reserved label if allowed

 *
 * Field: ::VTSS_REW_RSV_LABEL_CFG . RSV_LBL_ENA
 */
#define  VTSS_F_REW_RSV_LABEL_CFG_RSV_LBL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_RSV_LABEL_CFG_RSV_LBL_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_RSV_LABEL_CFG_RSV_LBL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MPLS label stack Control Word
 *
 * \details
 * Register: \a REW:ENCAP:CW_VAL
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_CW_VAL(gi)                  VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,8)

/**
 * \brief
 * Control Word value. The control word is always placed after the last
 * MPLS label.
 *
 * \details
 * x: Control Word

 *
 * Field: ::VTSS_REW_CW_VAL . CW_VAL
 */
#define  VTSS_F_REW_CW_VAL_CW_VAL(x)          (x)
#define  VTSS_M_REW_CW_VAL_CW_VAL             0xffffffff
#define  VTSS_X_REW_CW_VAL_CW_VAL(x)          (x)


/**
 * \brief MPLS label stack field values
 *
 * \details
 * This register contains the MPLS label fields. Label 0 is always placed
 * closest to the link layer MAC addresses:
 *
 * [LL]
 * [LL][LBL0][CW]
 * [LL][LBL0][LBL1][CW]
 * [LL][LBL0][LBL1][LBL2][CW]
 * [LL][LBL0][LBL1][LBL2][LBL3][CW]
 *
 * The register MPLS_LABEL_CFG.LABEL_CNT controls the number of labels.
 *
 * Register: \a REW:ENCAP:LABEL_VAL
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 * @param ri Register: LABEL_VAL (??), 0-3
 */
#define VTSS_REW_LABEL_VAL(gi,ri)            VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,ri,9)

/**
 * \brief
 * Label field value in MPLS  label N
 *
 * \details
 * x: Label field value

 *
 * Field: ::VTSS_REW_LABEL_VAL . LABEL_VAL
 */
#define  VTSS_F_REW_LABEL_VAL_LABEL_VAL(x)    VTSS_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_REW_LABEL_VAL_LABEL_VAL       VTSS_ENCODE_BITMASK(12,20)
#define  VTSS_X_REW_LABEL_VAL_LABEL_VAL(x)    VTSS_EXTRACT_BITFIELD(x,12,20)

/**
 * \brief
 * TC value in MPLS label N
 *
 * \details
 * x: TC field value

 *
 * Field: ::VTSS_REW_LABEL_VAL . TC_VAL
 */
#define  VTSS_F_REW_LABEL_VAL_TC_VAL(x)       VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_REW_LABEL_VAL_TC_VAL          VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_REW_LABEL_VAL_TC_VAL(x)       VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * SBIT value in MPLS label N
 *
 * \details
 * x: SBIT field value

 *
 * Field: ::VTSS_REW_LABEL_VAL . SBIT_VAL
 */
#define  VTSS_F_REW_LABEL_VAL_SBIT_VAL(x)     VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_REW_LABEL_VAL_SBIT_VAL        VTSS_BIT(8)
#define  VTSS_X_REW_LABEL_VAL_SBIT_VAL(x)     VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * TTL value in MPLS label N
 *
 * \details
 * x: TTL field value

 *
 * Field: ::VTSS_REW_LABEL_VAL . TTL_VAL
 */
#define  VTSS_F_REW_LABEL_VAL_TTL_VAL(x)      VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_LABEL_VAL_TTL_VAL         VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_LABEL_VAL_TTL_VAL(x)      VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Reserved label field values
 *
 * \details
 * This register contains the reserved MPLS label fields. The reserved
 * label can only be added if the control word (CW) is not enabled.

 *
 * Register: \a REW:ENCAP:RSV_LABEL_VAL
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_RSV_LABEL_VAL(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,13)

/**
 * \brief
 * Label field value in the reserved MPLS label
 *
 * \details
 * x: Label field value

 *
 * Field: ::VTSS_REW_RSV_LABEL_VAL . RSV_LBL_VAL
 */
#define  VTSS_F_REW_RSV_LABEL_VAL_RSV_LBL_VAL(x)  VTSS_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_REW_RSV_LABEL_VAL_RSV_LBL_VAL     VTSS_ENCODE_BITMASK(12,20)
#define  VTSS_X_REW_RSV_LABEL_VAL_RSV_LBL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,12,20)

/**
 * \brief
 * TC value in reserved the MPLS label
 *
 * \details
 * x: TC field value

 *
 * Field: ::VTSS_REW_RSV_LABEL_VAL . RSV_TC_VAL
 */
#define  VTSS_F_REW_RSV_LABEL_VAL_RSV_TC_VAL(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_REW_RSV_LABEL_VAL_RSV_TC_VAL     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_REW_RSV_LABEL_VAL_RSV_TC_VAL(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * SBIT value in reserved the MPLS label
 *
 * \details
 * x: SBIT field value

 *
 * Field: ::VTSS_REW_RSV_LABEL_VAL . RSV_SBIT_VAL
 */
#define  VTSS_F_REW_RSV_LABEL_VAL_RSV_SBIT_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_REW_RSV_LABEL_VAL_RSV_SBIT_VAL  VTSS_BIT(8)
#define  VTSS_X_REW_RSV_LABEL_VAL_RSV_SBIT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * TTL value in reserved the MPLS label
 *
 * \details
 * x: TTL field value

 *
 * Field: ::VTSS_REW_RSV_LABEL_VAL . RSV_TTL_VAL
 */
#define  VTSS_F_REW_RSV_LABEL_VAL_RSV_TTL_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_RSV_LABEL_VAL_RSV_TTL_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_RSV_LABEL_VAL_RSV_TTL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Configure MPLS label remarking
 *
 * \details
 * The rewriter can remark certain parameters in the pushed MPLS data. The
 * following illustrates provides an overview of the available remark
 * options.
 *
 * Register: \a REW:ENCAP:MPLS_REMARK_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 * @param ri Register: MPLS_REMARK_CFG (??), 0-3
 */
#define VTSS_REW_MPLS_REMARK_CFG(gi,ri)      VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,ri,14)

/**
 * \brief
 * Configure the Label-field used in label N.
 *
 * \details
 * 0 : LABEL_VAL[N].LABEL_VAL
 * 1-3: Reserved
 * 4 : Mapped using mapping table 0
 * 5 : Mapped using mapping table 1
 * 6 : Mapped using mapping table 2
 * 7 : Mapped using mapping table 3

 *
 * Field: ::VTSS_REW_MPLS_REMARK_CFG . LBL_SEL
 */
#define  VTSS_F_REW_MPLS_REMARK_CFG_LBL_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_REW_MPLS_REMARK_CFG_LBL_SEL     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_REW_MPLS_REMARK_CFG_LBL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/**
 * \brief
 * Configure the TC-field used in label N.
 *
 * \details
 * 0 : Classified TC
 * 1 : LABEL_VAL[N].TC_VAL
 * 2-3: Reserved
 * 4: Mapped using mapping table 0, otherwise use LABEL_VAL[N].TC_VAL
 * 5: Mapped using mapping table 1, otherwise use mapping table 0
 * 6: Mapped using mapping table 2, otherwise use LABEL_VAL[N].TC_VAL
 * 7: Mapped using mapping table 3, otherwise use mapping table 2

 *
 * Field: ::VTSS_REW_MPLS_REMARK_CFG . TC_SEL
 */
#define  VTSS_F_REW_MPLS_REMARK_CFG_TC_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_REW_MPLS_REMARK_CFG_TC_SEL     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_REW_MPLS_REMARK_CFG_TC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Configure the S-bit used in label N.
 *
 * \details
 * 0: Classified SBIT (ISBIT)
 * 1: Fixed: LABEL_VAL[N].SBIT_VAL
 * 2: Mixed: Use Classified SBIT if IFH.DST.ENCAP.PDU_TYPE = OAM_MPLS_TP
 * else LABEL_VAL[N].SBIT_VAL
 * 3: Reserved
 *
 * Field: ::VTSS_REW_MPLS_REMARK_CFG . SBIT_SEL
 */
#define  VTSS_F_REW_MPLS_REMARK_CFG_SBIT_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_REW_MPLS_REMARK_CFG_SBIT_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_REW_MPLS_REMARK_CFG_SBIT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Configure the TTL-field used in label N.
 *
 * \details
 * 0: Classified TTL (ITTL)
 * 1: Fixed: LABEL_VAL[N].TTL_VAL
 * 2: Mixed: Use Classified TTL if IFH.DST.ENCAP.PDU_TYPE = OAM_MPLS_TP
 * else LABEL_VAL[N].TTL_VAL
 * 3: Reserved
 *
 * Field: ::VTSS_REW_MPLS_REMARK_CFG . TTL_SEL
 */
#define  VTSS_F_REW_MPLS_REMARK_CFG_TTL_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_MPLS_REMARK_CFG_TTL_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_MPLS_REMARK_CFG_TTL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Configure VLAN tags in MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_TAG_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_LL_TAG_CFG(gi)              VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,18)

/**
 * \brief
 * Enable IFH encapsulation mode for this entry.The frame link layer format
 * is changed to:[LL_DMAC][LL_SMAC][0x8880][0x000E]Optionally one VLAN tag
 * can be added if LL_TAG_CFG.TAG_CFG = 1[LL_DMAC][LL_SMAC][LL_TAG:0]Note:
 * The [0x8880][0x000E] fields are not pushed when LL_TAG_CFG.TAG_CFG =
 * 1None of the other encapsulation fields are used in this mode
 *
 * \details
 * 0: Normal encapsulation mode
 * 1: IFH encapsulation mode

 *
 * Field: ::VTSS_REW_LL_TAG_CFG . IFH_ENCAP_MODE
 */
#define  VTSS_F_REW_LL_TAG_CFG_IFH_ENCAP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_LL_TAG_CFG_IFH_ENCAP_MODE  VTSS_BIT(2)
#define  VTSS_X_REW_LL_TAG_CFG_IFH_ENCAP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Control VLAN tags in MPLS link layer
 *
 * \details
 * 0: No tags in link layer
 * 1: One tag after SMAC
 * 2: Two tags after SMAC
 * 3: Reserved
 *
 * Field: ::VTSS_REW_LL_TAG_CFG . TAG_CFG
 */
#define  VTSS_F_REW_LL_TAG_CFG_TAG_CFG(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_LL_TAG_CFG_TAG_CFG        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_LL_TAG_CFG_TAG_CFG(x)     VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief MPLS label stack Control Word
 *
 * \details
 * This register contains the VLAN tags
 *
 * Register: \a REW:ENCAP:LL_TAG_VAL
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 * @param ri Register: LL_TAG_VAL (??), 0-1
 */
#define VTSS_REW_LL_TAG_VAL(gi,ri)           VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,ri,19)

/**
 * \brief
 * VID value in link layer tags
 *
 * \details
 * x: VID value

 *
 * Field: ::VTSS_REW_LL_TAG_VAL . TAG_VID_VAL
 */
#define  VTSS_F_REW_LL_TAG_VAL_TAG_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_REW_LL_TAG_VAL_TAG_VID_VAL     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_REW_LL_TAG_VAL_TAG_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/**
 * \brief
 * PCP value in link layer tags
 *
 * \details
 * x: PCP value

 *
 * Field: ::VTSS_REW_LL_TAG_VAL . TAG_PCP_VAL
 */
#define  VTSS_F_REW_LL_TAG_VAL_TAG_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_REW_LL_TAG_VAL_TAG_PCP_VAL     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_REW_LL_TAG_VAL_TAG_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * DEI value in link layer tags
 *
 * \details
 * x: DEI value

 *
 * Field: ::VTSS_REW_LL_TAG_VAL . TAG_DEI_VAL
 */
#define  VTSS_F_REW_LL_TAG_VAL_TAG_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_LL_TAG_VAL_TAG_DEI_VAL    VTSS_BIT(0)
#define  VTSS_X_REW_LL_TAG_VAL_TAG_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * TPID of link layer VLAN tags
 *
 * \details
 * x: TPID value

 *
 * Field: ::VTSS_REW_LL_TAG_VAL . TAG_TPID
 */
#define  VTSS_F_REW_LL_TAG_VAL_TAG_TPID(x)    VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_REW_LL_TAG_VAL_TAG_TPID       VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_REW_LL_TAG_VAL_TAG_TPID(x)    VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Configure remarking of VLAN tags in MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_TAG_REMARK_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 * @param ri Register: LL_TAG_REMARK_CFG (??), 0-1
 */
#define VTSS_REW_LL_TAG_REMARK_CFG(gi,ri)    VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,ri,21)

/**
 * \brief
 * Selects VID for MPLS encapsulation tagIdx0:	TAG_A, Idx1:  TAG_B
 *
 * \details
 * 0: Classified VID + TAG_VID_VAL:n
 * 1: TAG_VID_VAL:n
 *
 * Field: ::VTSS_REW_LL_TAG_REMARK_CFG . TAG_VID_SEL
 */
#define  VTSS_F_REW_LL_TAG_REMARK_CFG_TAG_VID_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_REW_LL_TAG_REMARK_CFG_TAG_VID_SEL  VTSS_BIT(7)
#define  VTSS_X_REW_LL_TAG_REMARK_CFG_TAG_VID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Selects PCP for MPLS encapsulation tagIdx0:	TAG_A, Idx1:  TAG_B
 *
 * \details
 * 0: Classified PCP
 * 1: Encapsulation TAG_PCP_VAL:n
 * 2: Reserved
 * 3: Set to the highest CPU queue number in IFH.MISC.CPU_MASK
 * 4: Mapped using mapping table 0, otherwise use LL_TAG_VAL[N].TAG_PCP_VAL
 * 5: Mapped using mapping table 1, otherwise use mapping table 0
 * 6: Mapped using mapping table 2, otherwise use LL_TAG_VAL[N].TAG_PCP_VAL
 * 7: Mapped using mapping table 3, otherwise use mapping table 2
 *
 * Field: ::VTSS_REW_LL_TAG_REMARK_CFG . TAG_PCP_SEL
 */
#define  VTSS_F_REW_LL_TAG_REMARK_CFG_TAG_PCP_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_REW_LL_TAG_REMARK_CFG_TAG_PCP_SEL     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_REW_LL_TAG_REMARK_CFG_TAG_PCP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Selects DEI for MPLS encapsulation tagIdx0:	TAG_A, Idx1:  TAG_B
 *
 * \details
 * 0: Classified DEI
 * 1: Encapsulation TAG_DEI_VAL:n
 * 2: DP: REW::DP_MAP.DP
 * 3: Reserved
 * 4: Mapped using mapping table 0, otherwise use LL_TAG_VAL[N].TAG_DEI_VAL
 * 5: Mapped using mapping table 1, otherwise use mapping table 0
 * 6: Mapped using mapping table 2, otherwise use LL_TAG_VAL[N].TAG_DEI_VAL
 * 7: Mapped using mapping table 3, otherwise use mapping table 2
 *
 * Field: ::VTSS_REW_LL_TAG_REMARK_CFG . TAG_DEI_SEL
 */
#define  VTSS_F_REW_LL_TAG_REMARK_CFG_TAG_DEI_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_REW_LL_TAG_REMARK_CFG_TAG_DEI_SEL     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_REW_LL_TAG_REMARK_CFG_TAG_DEI_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * Selects TPID for MPLS encapsulation tagIdx0:  TAG_A, Idx1:  TAG_B
 *
 * \details
 * 0: Encapsulation LL_TAG_VAL[N].TAG_TPID
 * 1: Classified.  ANA controls via IFH:
 * If ifh.encap.tag_tipd = STD_TPID:
 *   If ifh.vstax.tag_type = 0 then 0x8100 else LL_TAG_VAL[N].TAG_TPID
 * if ifh.encap.tag_tipd > 0:
 *   Custom TPID 1 to 3 configured by  REW::TPID_CFG[N].TPID_VAL
 *
 * Field: ::VTSS_REW_LL_TAG_REMARK_CFG . TAG_TPID_SEL
 */
#define  VTSS_F_REW_LL_TAG_REMARK_CFG_TAG_TPID_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_LL_TAG_REMARK_CFG_TAG_TPID_SEL  VTSS_BIT(0)
#define  VTSS_X_REW_LL_TAG_REMARK_CFG_TAG_TPID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a REW:ENCAP_IP4
 *
 * IP-in-IPv4 encapsulation RAM configuration
 */


/**
 * \brief Configure format of encapsulation
 *
 * \details
 * The encapsulation table can be used to control both MPLS and and
 * IP-in-IPv4  encapsulations
 *
 * Register: \a REW:ENCAP_IP4:IPV4_ENCAP_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_IPV4_ENCAP_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_REW,0x3000,gi,8,0,0)

/**
 * \brief
 * Configure format of table entry
 *
 * \details
 * 0: Normal (REW:ENCAP)
 * 1: IP (REW:ENCAP_IP4)
 *
 * Field: ::VTSS_REW_IPV4_ENCAP_CFG . ENCAP_TYPE
 */
#define  VTSS_F_REW_IPV4_ENCAP_CFG_ENCAP_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_IPV4_ENCAP_CFG_ENCAP_TYPE  VTSS_BIT(0)
#define  VTSS_X_REW_IPV4_ENCAP_CFG_ENCAP_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configure IP header fields
 *
 * \details
 * Configure the outer IPv4 header of IP-in-IPv4 frames
 *
 * Register: \a REW:ENCAP_IP4:IP_HDR_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_IP_HDR_CFG(gi)              VTSS_IOREG_IX(VTSS_TO_REW,0x3000,gi,8,0,1)

/**
 * \brief
 * IPv4 ProtocolTypical values:41 for IPv6-in-IPv447 for GRE4 for
 * IPv4-in-IPv4
 *
 * \details
 * Field: ::VTSS_REW_IP_HDR_CFG . IP_PROTOCOL
 */
#define  VTSS_F_REW_IP_HDR_CFG_IP_PROTOCOL(x)  VTSS_ENCODE_BITFIELD(x,20,8)
#define  VTSS_M_REW_IP_HDR_CFG_IP_PROTOCOL     VTSS_ENCODE_BITMASK(20,8)
#define  VTSS_X_REW_IP_HDR_CFG_IP_PROTOCOL(x)  VTSS_EXTRACT_BITFIELD(x,20,8)

/**
 * \brief
 * Don't Fragment bit
 *
 * \details
 * Field: ::VTSS_REW_IP_HDR_CFG . DF
 */
#define  VTSS_F_REW_IP_HDR_CFG_DF(x)          VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_REW_IP_HDR_CFG_DF             VTSS_BIT(19)
#define  VTSS_X_REW_IP_HDR_CFG_DF(x)          VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * ECN field
 *
 * \details
 * Field: ::VTSS_REW_IP_HDR_CFG . ECN
 */
#define  VTSS_F_REW_IP_HDR_CFG_ECN(x)         VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_REW_IP_HDR_CFG_ECN            VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_REW_IP_HDR_CFG_ECN(x)         VTSS_EXTRACT_BITFIELD(x,17,2)

/**
 * \brief
 * Time to live in IP header.Note that as the frame is routed in the outer
 * IP domain, the TTL is decremented. I.e. the frame leaving the device
 * will have a TTL value one smaller than the configured TTL.
 *
 * \details
 * Field: ::VTSS_REW_IP_HDR_CFG . TTL
 */
#define  VTSS_F_REW_IP_HDR_CFG_TTL(x)         VTSS_ENCODE_BITFIELD(x,9,8)
#define  VTSS_M_REW_IP_HDR_CFG_TTL            VTSS_ENCODE_BITMASK(9,8)
#define  VTSS_X_REW_IP_HDR_CFG_TTL(x)         VTSS_EXTRACT_BITFIELD(x,9,8)

/**
 * \brief
 * Value of DSCP in the IPv4 header
 *
 * \details
 * Field: ::VTSS_REW_IP_HDR_CFG . DSCP_VAL
 */
#define  VTSS_F_REW_IP_HDR_CFG_DSCP_VAL(x)    VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_REW_IP_HDR_CFG_DSCP_VAL       VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_REW_IP_HDR_CFG_DSCP_VAL(x)    VTSS_EXTRACT_BITFIELD(x,3,6)

/**
 * \brief
 * Control value of DSCP in the IPv4 header.This can - e.g. - be used for
 * mapping DSCP of inner IP header to DSCP of outer IP header.If mapping
 * tables are used (DSCP_SEL=4-7), then an ES0 rule must be setup to
 * control the index into the mapping table (ES0 action MAP_x_IDX). The
 * parameter ES0_VD2_ENCAP_ID_ENA can be used to have ENCAP_ID be part of
 * the ES0 key.Related
 * parameters:REW:COMMON:ES0_CTRL.ES0_VD2_ENCAP_ID_ENAREW:COMMON:ES0_CTRL.E
 * S0_LU_ENA
 *
 * \details
 * 0: ifh.qos.dscp
 * 1: DSCP_VAL
 * 2-3: Reserved
 * 4: Mapped using mapping table 0
 * 5: Mapped using mapping table 1
 * 6: Mapped using mapping table 2
 * 7: Mapped using mapping table 3
 *
 * Field: ::VTSS_REW_IP_HDR_CFG . DSCP_SEL
 */
#define  VTSS_F_REW_IP_HDR_CFG_DSCP_SEL(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_IP_HDR_CFG_DSCP_SEL       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_IP_HDR_CFG_DSCP_SEL(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief GRE protocol configuration
 *
 * \details
 * GRE protocol configuration
 *
 * Register: \a REW:ENCAP_IP4:GRE_PROTOCOL_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_GRE_PROTOCOL_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_REW,0x3000,gi,8,0,2)

/**
 * \brief
 * Enable insertion of GRE header without checksum. When GRE_ENA is set to
 * 1, then PROTOCOL should be set to 47.
 *
 * \details
 * Field: ::VTSS_REW_GRE_PROTOCOL_CFG . GRE_ENA
 */
#define  VTSS_F_REW_GRE_PROTOCOL_CFG_GRE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_GRE_PROTOCOL_CFG_GRE_ENA  VTSS_BIT(16)
#define  VTSS_X_REW_GRE_PROTOCOL_CFG_GRE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * GRE Protocol Type. Normally set to:0x0800 for IPv40x86DD for IPv6
 *
 * \details
 * Field: ::VTSS_REW_GRE_PROTOCOL_CFG . GRE_PROTOCOL_TYPE
 */
#define  VTSS_F_REW_GRE_PROTOCOL_CFG_GRE_PROTOCOL_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_GRE_PROTOCOL_CFG_GRE_PROTOCOL_TYPE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_GRE_PROTOCOL_CFG_GRE_PROTOCOL_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Source IPv4 address
 *
 * \details
 * Source IPv4 address
 *
 * Register: \a REW:ENCAP_IP4:SIP_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_SIP_CFG(gi)                 VTSS_IOREG_IX(VTSS_TO_REW,0x3000,gi,8,0,3)

/**
 * \brief
 * Source IPv4 address
 *
 * \details
 * Field: ::VTSS_REW_SIP_CFG . SIP
 */
#define  VTSS_F_REW_SIP_CFG_SIP(x)            (x)
#define  VTSS_M_REW_SIP_CFG_SIP               0xffffffff
#define  VTSS_X_REW_SIP_CFG_SIP(x)            (x)


/**
 * \brief Destination IPv4 address
 *
 * \details
 * Destination IPv4 address
 *
 * Register: \a REW:ENCAP_IP4:DIP_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_DIP_CFG(gi)                 VTSS_IOREG_IX(VTSS_TO_REW,0x3000,gi,8,0,4)

/**
 * \brief
 * Destination IPv4 address
 *
 * \details
 * Field: ::VTSS_REW_DIP_CFG . DIP
 */
#define  VTSS_F_REW_DIP_CFG_DIP(x)            (x)
#define  VTSS_M_REW_DIP_CFG_DIP               0xffffffff
#define  VTSS_X_REW_DIP_CFG_DIP(x)            (x)


/**
 * \brief Ingress router leg configuration
 *
 * \details
 * Ingress router leg configuration
 *
 * Register: \a REW:ENCAP_IP4:IRLEG_CFG
 *
 * @param gi Replicator: x_FFL_REW_NUM_ENCAP_ENTRIES (??), 0-255
 */
#define VTSS_REW_IRLEG_CFG(gi)               VTSS_IOREG_IX(VTSS_TO_REW,0x3000,gi,8,0,5)

/**
 * \brief
 * Ingress router leg for next round
 *
 * \details
 * Field: ::VTSS_REW_IRLEG_CFG . IRLEG
 */
#define  VTSS_F_REW_IRLEG_CFG_IRLEG(x)        VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_REW_IRLEG_CFG_IRLEG           VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_REW_IRLEG_CFG_IRLEG(x)        VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a REW:VMID
 *
 * Egress Mapped VLAN (EVMID) configuration
 */


/**
 * \brief Rewriter router leg configuration
 *
 * \details
 * Register: \a REW:VMID:RLEG_CTRL
 *
 * @param gi Replicator: x_FFL_CHIP_RLEG_CNT (??), 0-14
 */
#define VTSS_REW_RLEG_CTRL(gi)               VTSS_IOREG_IX(VTSS_TO_REW,0x3e10,gi,1,0,0)

/**
 * \brief
 * IP-in-IPv4 ingress router leg. Used used when the outer IPv4 layer is
 * removed.
 *
 * \details
 * Field: ::VTSS_REW_RLEG_CTRL . DECAP_IRLEG
 */
#define  VTSS_F_REW_RLEG_CTRL_DECAP_IRLEG(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_REW_RLEG_CTRL_DECAP_IRLEG     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_REW_RLEG_CTRL_DECAP_IRLEG(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/**
 * \brief
 * Control the value of VSTAX.TAG.WAS_TAGGED field in the stack header for
 * frames that are L3 forwarded to a stack port.
 *
 * \details
 * 0: VSTAX.TAG.WAS_TAGGED = 0
 * 1: VSTAX.TAG.WAS_TAGGED = 1
 *
 * Field: ::VTSS_REW_RLEG_CTRL . RLEG_VSTAX2_WAS_TAGGED
 */
#define  VTSS_F_REW_RLEG_CTRL_RLEG_VSTAX2_WAS_TAGGED(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_RLEG_CTRL_RLEG_VSTAX2_WAS_TAGGED  VTSS_BIT(12)
#define  VTSS_X_REW_RLEG_CTRL_RLEG_VSTAX2_WAS_TAGGED(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * VID for egress router leg.This must be configured consistently in
 * ANA_L3:VMID:RLEG_CTRL.RLEG_EVID.
 *
 * \details
 * n: VID
 *
 * Field: ::VTSS_REW_RLEG_CTRL . RLEG_EVID
 */
#define  VTSS_F_REW_RLEG_CTRL_RLEG_EVID(x)    VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_REW_RLEG_CTRL_RLEG_EVID       VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_REW_RLEG_CTRL_RLEG_EVID(x)    VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * Register Group: \a REW:PTP_SEQ_NO
 *
 * Sequence numbers for PTP frames
 */


/**
 * \brief Sequence number configuration
 *
 * \details
 * Register: \a REW:PTP_SEQ_NO:PTP_SEQ_NO
 *
 * @param ri Replicator: x_FFL_REW_NUM_PTP_SEQ_NUMBERS (??), 0-1023
 */
#define VTSS_REW_PTP_SEQ_NO(ri)              VTSS_IOREG(VTSS_TO_REW,0x2c00 + (ri))

/**
 * \brief
 * Sequence number for the flow given by the time stamp field in IFH.
 * Sequence number will automatically increase at each transmission
 * referring to the sequence entry.
 *
 * \details
 * Field: ::VTSS_REW_PTP_SEQ_NO . PTP_SEQ_NO
 */
#define  VTSS_F_REW_PTP_SEQ_NO_PTP_SEQ_NO(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_PTP_SEQ_NO_PTP_SEQ_NO     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_PTP_SEQ_NO_PTP_SEQ_NO(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a REW:VOE_SRV_LM_CNT
 *
 * OAM Service LM counters pr. priority
 */


/**
 * \brief Service LM counters pr. priority
 *
 * \details
 * Implements the OAM VOE LM counters.
 *
 * Depending on whether the OAM_PDU_MOD block is instantiated in the REW or
 * the ANA these counters will be either egress (REW) or ingress (ANA)
 * counters.
 *
 * Y.1731 LM counters count frames and are 32 bit wide.
 *
 * Register: \a REW:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_VOE_X_NUM_PRIO (??), 0-63
 */
#define VTSS_REW_SRV_LM_CNT_LSB(gi)          VTSS_IOREG_IX(VTSS_TO_REW,0x3bc0,gi,1,0,0)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_SRV_LM_CNT_LSB . SRV_LM_CNT_LSB
 */
#define  VTSS_F_REW_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB(x)  (x)

/**
 * Register Group: \a REW:VOE_PORT_LM_CNT
 *
 * OAM LM port counters pr. priority
 */


/**
 * \brief Count selected OAM PDU received by MEP Counter
 *
 * \details
 * Implements the OAM VOE LM port counters.
 *
 * Depending on whether the OAM_PDU_MOD block is instantiated in the REW or
 * the ANA these counters will be either egress (REW) or ingress (ANA)
 * counters.
 *
 * Y.1731 LM counters count frames and are 32 bit wide.
 *
 * Whenever this RAM is read, the value of this register will be sampled
 * into the following register:
 *
 *  * ANA_AC_OAM_MOD::RD_LAST_PORT_LM_CNT_LSB.RD_LAST_PORT_LM_CNT_LSB (ANA)
 *  * REW::RD_LAST_PORT_LM_CNT_LSB.RD_LAST_PORT_LM_CNT_LSB (REW)

 *
 * Register: \a REW:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS_X_NUM_PRIO (??), 0-239
 */
#define VTSS_REW_PORT_LM_CNT_LSB(gi)         VTSS_IOREG_IX(VTSS_TO_REW,0x3800,gi,4,0,0)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_PORT_LM_CNT_LSB . PORT_LM_CNT_LSB
 */
#define  VTSS_F_REW_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB(x)  (x)


/**
 * \brief Count all the frames which pass through the Port VOE
 *
 * \details
 * This counter counts all the frames which pass though the Port VOE.
 *
 * Whenever this RAM is read, the value of this register will be sampled
 * into the following register:
 *
 *  * ANA_AC_OAM_MOD::RD_LAST_PORT_FRM_CNT_LSB.RD_LAST_PORT_FRM_CNT_LSB
 * (ANA)
 *  * REW::RD_LAST_PORT_FRM_CNT_LSB.RD_LAST_PORT_FRM_CNT_LSB (REW)
 *
 * Register: \a REW:VOE_PORT_LM_CNT:PORT_FRM_CNT_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS_X_NUM_PRIO (??), 0-239
 */
#define VTSS_REW_PORT_FRM_CNT_LSB(gi)        VTSS_IOREG_IX(VTSS_TO_REW,0x3800,gi,4,0,1)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_PORT_FRM_CNT_LSB . PORT_FRM_CNT_LSB
 */
#define  VTSS_F_REW_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB(x)  (x)


/**
 * \brief Byte count of all frames passing through the Port VOE (MSB)
 *
 * \details
 * Byte count of all frames passing through the Port VOE.
 *
 * Whenever this RAM is read, the value of this register will be sampled
 * into the following register:
 *
 *  * ANA_AC_OAM_MOD::RD_LAST_PORT_BYTE_CNT_MSB.RD_LAST_PORT_BYTE_CNT_MSB
 * (ANA)
 *  * REW::RD_LAST_PORT_BYTE_CNT_MSB.RD_LAST_PORT_BYTE_CNT_MSB (REW)

 *
 * Register: \a REW:VOE_PORT_LM_CNT:PORT_BYTE_CNT_MSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS_X_NUM_PRIO (??), 0-239
 */
#define VTSS_REW_PORT_BYTE_CNT_MSB(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x3800,gi,4,0,2)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_PORT_BYTE_CNT_MSB . PORT_BYTE_CNT_MSB
 */
#define  VTSS_F_REW_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Byte count of all frames passing through the Port VOE (LSB)
 *
 * \details
 * Byte count of all frames passing through the Port VOE.
 *
 * Whenever this RAM is read, the value of this register will be sampled
 * into the following register:
 *
 *  * ANA_AC_OAM_MOD::RD_LAST_PORT_BYTE_CNT_LSB.RD_LAST_PORT_BYTE_CNT_LSB
 * (ANA)
 *  * REW::RD_LAST_PORT_BYTE_CNT_LSB.RD_LAST_PORT_BYTE_CNT_LSB (REW)
 *
 * Register: \a REW:VOE_PORT_LM_CNT:PORT_BYTE_CNT_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS_X_NUM_PRIO (??), 0-239
 */
#define VTSS_REW_PORT_BYTE_CNT_LSB(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x3800,gi,4,0,3)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_PORT_BYTE_CNT_LSB . PORT_BYTE_CNT_LSB
 */
#define  VTSS_F_REW_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB(x)  (x)
#define  VTSS_M_REW_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB     0xffffffff
#define  VTSS_X_REW_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB(x)  (x)

/**
 * Register Group: \a REW:OAM_PDU_MOD_CONT
 *
 * VOE additional information
 */


/**
 * \brief LM temp count
 *
 * \details
 * Register: \a REW:OAM_PDU_MOD_CONT:TEMP_CNT_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CONTEXT_PORTS (??), 0-64
 */
#define VTSS_REW_TEMP_CNT_REG(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x3c00,gi,8,0,0)

/**
 * \details
 * Field: ::VTSS_REW_TEMP_CNT_REG . TEMP_CNT_VAL
 */
#define  VTSS_F_REW_TEMP_CNT_REG_TEMP_CNT_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_TEMP_CNT_REG_TEMP_CNT_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_TEMP_CNT_REG_TEMP_CNT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Temp LM cnt
 *
 * \details
 * Register: \a REW:OAM_PDU_MOD_CONT:LM_CNT_FRAME
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CONTEXT_PORTS (??), 0-64
 */
#define VTSS_REW_LM_CNT_FRAME(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x3c00,gi,8,0,1)

/**
 * \brief
 * Determines if the current frame should be counted by the Service LM
 * counter, based on the color / mapping and possibly being killed in the
 * ingress DLB.
 *
 * \details
 * Field: ::VTSS_REW_LM_CNT_FRAME . SRV_CNT_FRM
 */
#define  VTSS_F_REW_LM_CNT_FRAME_SRV_CNT_FRM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_LM_CNT_FRAME_SRV_CNT_FRM  VTSS_BIT(1)
#define  VTSS_X_REW_LM_CNT_FRAME_SRV_CNT_FRM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Determines if the current frame should be counted by the Path LM
 * counter, based on the color / mapping and possibly being killed in the
 * ingress DLB.
 *
 * \details
 * Field: ::VTSS_REW_LM_CNT_FRAME . PATH_CNT_FRM
 */
#define  VTSS_F_REW_LM_CNT_FRAME_PATH_CNT_FRM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_LM_CNT_FRAME_PATH_CNT_FRM  VTSS_BIT(0)
#define  VTSS_X_REW_LM_CNT_FRAME_PATH_CNT_FRM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Temp CCM-LM info
 *
 * \details
 * Register: \a REW:OAM_PDU_MOD_CONT:CCM_LM_INFO_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CONTEXT_PORTS (??), 0-64
 */
#define VTSS_REW_CCM_LM_INFO_REG(gi)         VTSS_IOREG_IX(VTSS_TO_REW,0x3c00,gi,8,0,2)

/**
 * \brief
 * Indicates whether this entry in the RAM contains valid CCM-LM sample
 * values.
 *
 * \details
 * Field: ::VTSS_REW_CCM_LM_INFO_REG . CCM_LM_INFO_VLD
 */
#define  VTSS_F_REW_CCM_LM_INFO_REG_CCM_LM_INFO_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_REW_CCM_LM_INFO_REG_CCM_LM_INFO_VLD  VTSS_BIT(11)
#define  VTSS_X_REW_CCM_LM_INFO_REG_CCM_LM_INFO_VLD(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * The number of the VOE for which the LM information was received.
 *
 * \details
 * Field: ::VTSS_REW_CCM_LM_INFO_REG . CCM_LM_VOE_IDX
 */
#define  VTSS_F_REW_CCM_LM_INFO_REG_CCM_LM_VOE_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_REW_CCM_LM_INFO_REG_CCM_LM_VOE_IDX     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_REW_CCM_LM_INFO_REG_CCM_LM_VOE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief CCM-LM sample
 *
 * \details
 * Contains the sampled value of CCM_LM.tx_fc_b from the last valid CCM_LM
 * frame.
 *
 * Register: \a REW:OAM_PDU_MOD_CONT:CCM_LM_TX_B_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CONTEXT_PORTS (??), 0-64
 */
#define VTSS_REW_CCM_LM_TX_B_REG(gi)         VTSS_IOREG_IX(VTSS_TO_REW,0x3c00,gi,8,0,3)

/**
 * \brief
 * Contains the sampled value of CCM_LM.tx_fc_b from the last valid CCM_LM
 * frame.
 *
 * \details
 * Field: ::VTSS_REW_CCM_LM_TX_B_REG . CCM_LM_TX_B
 */
#define  VTSS_F_REW_CCM_LM_TX_B_REG_CCM_LM_TX_B(x)  (x)
#define  VTSS_M_REW_CCM_LM_TX_B_REG_CCM_LM_TX_B     0xffffffff
#define  VTSS_X_REW_CCM_LM_TX_B_REG_CCM_LM_TX_B(x)  (x)


/**
 * \brief CCM-LM sample
 *
 * \details
 * Contains the sampled value of CCM_LM.rx_fc_b from the last valid CCM_LM
 * frame.
 *
 * Register: \a REW:OAM_PDU_MOD_CONT:CCM_LM_RX_B_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CONTEXT_PORTS (??), 0-64
 */
#define VTSS_REW_CCM_LM_RX_B_REG(gi)         VTSS_IOREG_IX(VTSS_TO_REW,0x3c00,gi,8,0,4)

/**
 * \brief
 * Contains the sampled value of CCM_LM.rx_fc_b from the last valid CCM_LM
 * frame.
 *
 * \details
 * Field: ::VTSS_REW_CCM_LM_RX_B_REG . CCM_LM_RX_B
 */
#define  VTSS_F_REW_CCM_LM_RX_B_REG_CCM_LM_RX_B(x)  (x)
#define  VTSS_M_REW_CCM_LM_RX_B_REG_CCM_LM_RX_B     0xffffffff
#define  VTSS_X_REW_CCM_LM_RX_B_REG_CCM_LM_RX_B(x)  (x)

/**
 * Register Group: \a REW:PDU_MOD_CFG
 *
 * OAM_PDU_MOD misc. configuration
 */


/**
 * \brief Port PTP domain select
 *
 * \details
 * The Delay Measurements uses the PTP timing for updating time stamps in
 * OAM PDUs.
 *
 * For this to work, each port on the switch must be configured for which
 * PTP time domain to use.
 *
 * This is done by configuring this register.
 *
 * PTP supports 3 time domains, so the register must be configured in the
 * range 0 - 2.
 *
 * The settings must be the same in the REW and the ANA_AC instantiation of
 * the OAM_PDU_MOD block.
 *
 * Register: \a REW:PDU_MOD_CFG:DM_PTP_DOMAIN_CFG
 *
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS (??), 0-29
 */
#define VTSS_REW_DM_PTP_DOMAIN_CFG(ri)       VTSS_IOREG(VTSS_TO_REW,0x3fb4 + (ri))

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_DM_PTP_DOMAIN_CFG . PTP_DOMAIN
 */
#define  VTSS_F_REW_DM_PTP_DOMAIN_CFG_PTP_DOMAIN(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_DM_PTP_DOMAIN_CFG_PTP_DOMAIN     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_DM_PTP_DOMAIN_CFG_PTP_DOMAIN(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Offset between PTP and NTP time
 *
 * \details
 * The value of this register is added to the seconds part of PTP time
 * stamps to calculate the corresponding NTP time stamp that is used for
 * TWAMP PDUs.
 *
 * PTP uses the TAI time standard and by default uses the epoch of 00:00,
 * January 1, 1970.
 * NTP uses the UTC time standard and uses the epoch of 00:00, January 1,
 * 1900.
 *
 * Since UTC uses leap seconds and TAI does not, the number of leap seconds
 * between the NTP epoch and today must be subtracted from the offset.
 *
 * Between 1/1/1900 and 1/1/1970 there are 25567 days = 2,208,988,800
 * seconds (not including leap seconds).
 *
 * So to set this register to the correct value when PTP uses the default
 * epoch, the value must be  2,208,988,800 - leap seconds.
 *
 * Any overflow of the addition is ignored, so a negative offset can be
 * configured by representing the offset as a two's complement signed
 * integer.
 *
 * The settings must be the same in the REW and the ANA_AC instantiation of
 * the OAM_PDU_MOD block.
 *
 * Register: \a REW:PDU_MOD_CFG:PTP_NTP_OFFSET_CFG
 *
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_TOD_DOMAINS (??), 0-2
 */
#define VTSS_REW_PTP_NTP_OFFSET_CFG(ri)      VTSS_IOREG(VTSS_TO_REW,0x3ff5 + (ri))

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_PTP_NTP_OFFSET_CFG . PTP_NTP_OFFSET_CFG
 */
#define  VTSS_F_REW_PTP_NTP_OFFSET_CFG_PTP_NTP_OFFSET_CFG(x)  (x)
#define  VTSS_M_REW_PTP_NTP_OFFSET_CFG_PTP_NTP_OFFSET_CFG     0xffffffff
#define  VTSS_X_REW_PTP_NTP_OFFSET_CFG_PTP_NTP_OFFSET_CFG(x)  (x)


/**
 * \brief PORT_LM_CNT_LSB sample register.
 *
 * \details
 * Whenever either of the bit fields the following RAM are read:
 *  * ANA_AC_OAM_MOD:VOE_SRV_LM_CNT (ANA)
 *  * REW:VOE_SRV_LM_CNT (REW)
 *
 * this register will sample the value of the following bit field:
 *  * ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSB (ANA)
 *  * REW:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSB (REW)
 *
 * Register: \a REW:PDU_MOD_CFG:RD_LAST_PORT_LM_CNT_LSB
 */
#define VTSS_REW_RD_LAST_PORT_LM_CNT_LSB     VTSS_IOREG(VTSS_TO_REW,0x3ff8)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_RD_LAST_PORT_LM_CNT_LSB . RD_LAST_PORT_LM_CNT_LSB
 */
#define  VTSS_F_REW_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB(x)  (x)


/**
 * \brief PORT_NON_LM_CNT_LSB sample register.
 *
 * \details
 * Whenever either of the bit fields the following RAM are read:
 *  * ANA_AC_OAM_MOD:VOE_SRV_LM_CNT (ANA)
 *  * REW:VOE_SRV_LM_CNT (REW)
 *
 * this register will sample the value of the following bit field:
 *  * ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_FRM_CNT_LSB.PORT_FRM_CNT_LSB
 * (ANA)
 *  * REW:VOE_PORT_LM_CNT:PORT_FRM_CNT_LSB.PORT_FRM_CNT_LSB (REW)
 *
 * Register: \a REW:PDU_MOD_CFG:RD_LAST_PORT_FRM_CNT_LSB
 */
#define VTSS_REW_RD_LAST_PORT_FRM_CNT_LSB    VTSS_IOREG(VTSS_TO_REW,0x3ff9)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_RD_LAST_PORT_FRM_CNT_LSB . RD_LAST_PORT_FRM_CNT_LSB
 */
#define  VTSS_F_REW_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB(x)  (x)


/**
 * \brief PORT_BYTE_CNT_MSB sample register.
 *
 * \details
 * Whenever either of the bit fields the following RAM are read:
 *  * ANA_AC_OAM_MOD:VOE_SRV_LM_CNT (ANA)
 *  * REW:VOE_SRV_LM_CNT (REW)
 *
 * this register will sample the value of the following bit field:
 *  * ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_BYTE_CNT_MSB.PORT_BYTE_CNT_MSB
 * (ANA)
 *  * REW:VOE_PORT_LM_CNT:PORT_BYTE_CNT_MSB.PORT_BYTE_CNT_MSB (REW)
 *
 * Register: \a REW:PDU_MOD_CFG:RD_LAST_PORT_BYTE_CNT_MSB
 */
#define VTSS_REW_RD_LAST_PORT_BYTE_CNT_MSB   VTSS_IOREG(VTSS_TO_REW,0x3ffa)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_RD_LAST_PORT_BYTE_CNT_MSB . RD_LAST_PORT_BYTE_CNT_MSB
 */
#define  VTSS_F_REW_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief PORT_BYTE_CNT_LSB sample register.
 *
 * \details
 * Whenever either of the bit fields the following RAM are read:
 *  * ANA_AC_OAM_MOD:VOE_SRV_LM_CNT (ANA)
 *  * REW:VOE_SRV_LM_CNT (REW)
 *
 * this register will sample the value of the following bit field:
 *  * ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_BYTE_CNT_LSB.PORT_BYTE_CNT_LSB
 * (ANA)
 *  * REW:VOE_PORT_LM_CNT:PORT_BYTE_CNT_LSB.PORT_BYTE_CNT_LSB (REW)
 *
 * Register: \a REW:PDU_MOD_CFG:RD_LAST_PORT_BYTE_CNT_LSB
 */
#define VTSS_REW_RD_LAST_PORT_BYTE_CNT_LSB   VTSS_IOREG(VTSS_TO_REW,0x3ffb)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_REW_RD_LAST_PORT_BYTE_CNT_LSB . RD_LAST_PORT_BYTE_CNT_LSB
 */
#define  VTSS_F_REW_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB(x)  (x)
#define  VTSS_M_REW_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB     0xffffffff
#define  VTSS_X_REW_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB(x)  (x)

/**
 * Register Group: \a REW:RAM_CTRL
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
 * Register: \a REW:RAM_CTRL:RAM_INIT
 */
#define VTSS_REW_RAM_INIT                    VTSS_IOREG(VTSS_TO_REW,0x3e08)

/**
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete (approx. 40 us).
 *
 * \details
 * Field: ::VTSS_REW_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_REW_RAM_INIT_RAM_INIT(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_RAM_INIT_RAM_INIT         VTSS_BIT(1)
#define  VTSS_X_REW_RAM_INIT_RAM_INIT(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this field is set, all memories HA_RESTART behavior will be
 * inverted. It is a backdoor for potentiel access issues.
 *
 * \details
 * Field: ::VTSS_REW_RAM_INIT . RAM_CFG_HOOK
 */
#define  VTSS_F_REW_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_RAM_INIT_RAM_CFG_HOOK     VTSS_BIT(0)
#define  VTSS_X_REW_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a REW:COREMEM
 *
 * Access core memory
 */


/**
 * \brief Address selection
 *
 * \details
 * Register: \a REW:COREMEM:CM_ADDR
 */
#define VTSS_REW_CM_ADDR                     VTSS_IOREG(VTSS_TO_REW,0x3e09)

/**
 * \brief
 * Address selection for the ram debug address space.
 *
 * \details
 * Field: ::VTSS_REW_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_REW_CM_ADDR_CM_ADDR(x)        (x)
#define  VTSS_M_REW_CM_ADDR_CM_ADDR           0xffffffff
#define  VTSS_X_REW_CM_ADDR_CM_ADDR(x)        (x)


/**
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a REW:COREMEM:CM_DATA_WR
 */
#define VTSS_REW_CM_DATA_WR                  VTSS_IOREG(VTSS_TO_REW,0x3e0a)

/**
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 bit inspection space. This register provides data to
 * be written when CM_OP is set.
 *
 * \details
 * Field: ::VTSS_REW_CM_DATA_WR . CM_DATA_WR
 */
#define  VTSS_F_REW_CM_DATA_WR_CM_DATA_WR(x)  (x)
#define  VTSS_M_REW_CM_DATA_WR_CM_DATA_WR     0xffffffff
#define  VTSS_X_REW_CM_DATA_WR_CM_DATA_WR(x)  (x)


/**
 * \brief Core memory data register for read result
 *
 * \details
 * Register: \a REW:COREMEM:CM_DATA_RD
 */
#define VTSS_REW_CM_DATA_RD                  VTSS_IOREG(VTSS_TO_REW,0x3e0b)

/**
 * \brief
 * Read result
 *
 * \details
 * Field: ::VTSS_REW_CM_DATA_RD . CM_DATA_RD
 */
#define  VTSS_F_REW_CM_DATA_RD_CM_DATA_RD(x)  (x)
#define  VTSS_M_REW_CM_DATA_RD_CM_DATA_RD     0xffffffff
#define  VTSS_X_REW_CM_DATA_RD_CM_DATA_RD(x)  (x)


/**
 * \brief Operation to perform in core memory
 *
 * \details
 * Register: \a REW:COREMEM:CM_OP
 */
#define VTSS_REW_CM_OP                       VTSS_IOREG(VTSS_TO_REW,0x3e0c)

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
 * Field: ::VTSS_REW_CM_OP . CM_OP
 */
#define  VTSS_F_REW_CM_OP_CM_OP(x)            VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_CM_OP_CM_OP               VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_CM_OP_CM_OP(x)            VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a REW:GPTP_DOM
 *
 * gPTP configuration and status Registers
 */


/**
 * \brief Time stamp of latest SYNC frame
 *
 * \details
 * Register: \a REW:GPTP_DOM:GM_ITS
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_GM_ITS(gi)                  VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,0)

/**
 * \brief
 * Time stamp of latest SYNC frame.
 *
 * \details
 * Field: ::VTSS_REW_GM_ITS . GM_ITS
 */
#define  VTSS_F_REW_GM_ITS_GM_ITS(x)          (x)
#define  VTSS_M_REW_GM_ITS_GM_ITS             0xffffffff
#define  VTSS_X_REW_GM_ITS_GM_ITS(x)          (x)


/**
 * \brief Origin time from latest SYNC frame, 16 MSBs of the seconds
 *
 * \details
 * Register: \a REW:GPTP_DOM:GM_IORG_SEC_MSB
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_GM_IORG_SEC_MSB(gi)         VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,1)

/**
 * \brief
 * Origin time from latest SYNC frame, 16 MSBs of the seconds.
 *
 * \details
 * Field: ::VTSS_REW_GM_IORG_SEC_MSB . GM_IORG_SEC_MSB
 */
#define  VTSS_F_REW_GM_IORG_SEC_MSB_GM_IORG_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_GM_IORG_SEC_MSB_GM_IORG_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_GM_IORG_SEC_MSB_GM_IORG_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Origin time from latest SYNC frame, 32 LSBs of the seconds
 *
 * \details
 * Register: \a REW:GPTP_DOM:GM_IORG_SEC_LSB
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_GM_IORG_SEC_LSB(gi)         VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,2)

/**
 * \brief
 * Origin time from latest SYNC frame, 32 LSBs of the seconds.
 *
 * \details
 * Field: ::VTSS_REW_GM_IORG_SEC_LSB . GM_IORG_SEC_LSB
 */
#define  VTSS_F_REW_GM_IORG_SEC_LSB_GM_IORG_SEC_LSB(x)  (x)
#define  VTSS_M_REW_GM_IORG_SEC_LSB_GM_IORG_SEC_LSB     0xffffffff
#define  VTSS_X_REW_GM_IORG_SEC_LSB_GM_IORG_SEC_LSB(x)  (x)


/**
 * \brief Origin time from latest SYNC frame, nanoseconds part
 *
 * \details
 * Register: \a REW:GPTP_DOM:GM_IORG_NSEC
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_GM_IORG_NSEC(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,3)

/**
 * \brief
 * Origin time from latest SYNC frame, nanoseconds part.
 *
 * \details
 * Field: ::VTSS_REW_GM_IORG_NSEC . GM_IORG_NSEC
 */
#define  VTSS_F_REW_GM_IORG_NSEC_GM_IORG_NSEC(x)  (x)
#define  VTSS_M_REW_GM_IORG_NSEC_GM_IORG_NSEC     0xffffffff
#define  VTSS_X_REW_GM_IORG_NSEC_GM_IORG_NSEC(x)  (x)


/**
 * \brief CF field from latest SYNC frame, MSB
 *
 * \details
 * Register: \a REW:GPTP_DOM:GM_ICF_MSB
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_GM_ICF_MSB(gi)              VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,4)

/**
 * \brief
 * CF field from latests SYNC frame, 32 MSBs.
 *
 * \details
 * Field: ::VTSS_REW_GM_ICF_MSB . GM_ICF_MSB
 */
#define  VTSS_F_REW_GM_ICF_MSB_GM_ICF_MSB(x)  (x)
#define  VTSS_M_REW_GM_ICF_MSB_GM_ICF_MSB     0xffffffff
#define  VTSS_X_REW_GM_ICF_MSB_GM_ICF_MSB(x)  (x)


/**
 * \brief CF field from latest SYNC frame, LSB
 *
 * \details
 * Register: \a REW:GPTP_DOM:GM_ICF_LSB
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_GM_ICF_LSB(gi)              VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,5)

/**
 * \brief
 * CF field from latests SYNC frame, 32 LSBs.
 *
 * \details
 * Field: ::VTSS_REW_GM_ICF_LSB . GM_ICF_LSB
 */
#define  VTSS_F_REW_GM_ICF_LSB_GM_ICF_LSB(x)  (x)
#define  VTSS_M_REW_GM_ICF_LSB_GM_ICF_LSB     0xffffffff
#define  VTSS_X_REW_GM_ICF_LSB_GM_ICF_LSB(x)  (x)


/**
 * \brief CF rateratio update value
 *
 * \details
 * Register: \a REW:GPTP_DOM:GM_ICF_SUB
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_GM_ICF_SUB(gi)              VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,6)

/**
 * \brief
 * CF rateration update value
 *
 * \details
 * Field: ::VTSS_REW_GM_ICF_SUB . GM_ICF_SUB
 */
#define  VTSS_F_REW_GM_ICF_SUB_GM_ICF_SUB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_GM_ICF_SUB_GM_ICF_SUB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_GM_ICF_SUB_GM_ICF_SUB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Local rateratio of this domain
 *
 * \details
 * Register: \a REW:GPTP_DOM:GM_RATERATIO
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_GM_RATERATIO(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,7)

/**
 * \brief
 * Local rateratio of this domain, with unit 2**-41. Ie 100ppm encoded as
 * 100*(10**-6) / (2**-41).
 *
 * \details
 * Field: ::VTSS_REW_GM_RATERATIO . GM_RATERATIO
 */
#define  VTSS_F_REW_GM_RATERATIO_GM_RATERATIO(x)  (x)
#define  VTSS_M_REW_GM_RATERATIO_GM_RATERATIO     0xffffffff
#define  VTSS_X_REW_GM_RATERATIO_GM_RATERATIO(x)  (x)


/**
 * \brief PTP clock identifier MSB
 *
 * \details
 * Register: \a REW:GPTP_DOM:PTP_CLOCK_ID_MSB
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_PTP_CLOCK_ID_MSB(gi)        VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,8)

/**
 * \brief
 * Bits 63:32 of clockIdentifier used in portIdentity.
 *
 * \details
 * Field: ::VTSS_REW_PTP_CLOCK_ID_MSB . CLOCK_ID_MSB
 */
#define  VTSS_F_REW_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB(x)  (x)
#define  VTSS_M_REW_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB     0xffffffff
#define  VTSS_X_REW_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB(x)  (x)


/**
 * \brief PTP clock identifier LSB
 *
 * \details
 * Register: \a REW:GPTP_DOM:PTP_CLOCK_ID_LSB
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_PTP_CLOCK_ID_LSB(gi)        VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,9)

/**
 * \brief
 * Bits 31:0 of clockIdentifier used in portIdentity.
 *
 * \details
 * Field: ::VTSS_REW_PTP_CLOCK_ID_LSB . CLOCK_ID_LSB
 */
#define  VTSS_F_REW_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB(x)  (x)
#define  VTSS_M_REW_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB     0xffffffff
#define  VTSS_X_REW_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB(x)  (x)


/**
 * \brief PTP domain configuration used in sourcePortIdentity
 *
 * \details
 * Register: \a REW:GPTP_DOM:PTP_SRC_PORT_CFG
 *
 * @param gi Register: GPTP_DOM (??), 0-3
 */
#define VTSS_REW_PTP_SRC_PORT_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_REW,0x3e40,gi,16,0,10)

/**
 * \brief
 * If set, lowest 7 bits in portIdentity is taken from
 * GPTP_PORTID_CFG.GPTP_PORTID_VAL. Otherwise, portIdentity is taken from
 * PTP_SRC_PORT_CFG.PORT_NUM.
 *
 * \details
 * Field: ::VTSS_REW_PTP_SRC_PORT_CFG . PORT_NUM_SEL
 */
#define  VTSS_F_REW_PTP_SRC_PORT_CFG_PORT_NUM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_PTP_SRC_PORT_CFG_PORT_NUM_SEL  VTSS_BIT(16)
#define  VTSS_X_REW_PTP_SRC_PORT_CFG_PORT_NUM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Port number used in portIdentity.
 *
 * \details
 * Field: ::VTSS_REW_PTP_SRC_PORT_CFG . PORT_NUM
 */
#define  VTSS_F_REW_PTP_SRC_PORT_CFG_PORT_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_PTP_SRC_PORT_CFG_PORT_NUM     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_PTP_SRC_PORT_CFG_PORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a REW:GPTP_COMMON_CFG
 *
 * gPTP port configuration Registers
 */


/**
 * \brief Detected neighbor rate ratios
 *
 * \details
 * Register: \a REW:GPTP_COMMON_CFG:GPTP_NRR_CFG
 *
 * @param ri Replicator: x_PTP_CFG_NUM_PORTS (??), 0-31
 */
#define VTSS_REW_GPTP_NRR_CFG(ri)            VTSS_IOREG(VTSS_TO_REW,0x4200 + (ri))

/**
 * \brief
 * Neighbor rate ration per ingress port encoded as the GM_RATERATIO
 *
 * \details
 * Field: ::VTSS_REW_GPTP_NRR_CFG . GPTP_NRR_CFG
 */
#define  VTSS_F_REW_GPTP_NRR_CFG_GPTP_NRR_CFG(x)  (x)
#define  VTSS_M_REW_GPTP_NRR_CFG_GPTP_NRR_CFG     0xffffffff
#define  VTSS_X_REW_GPTP_NRR_CFG_GPTP_NRR_CFG(x)  (x)


/**
 * \brief Port identity per egress port
 *
 * \details
 * Register: \a REW:GPTP_COMMON_CFG:GPTP_PORTID_CFG
 *
 * @param ri Replicator: x_PTP_CFG_NUM_PORTS (??), 0-31
 */
#define VTSS_REW_GPTP_PORTID_CFG(ri)         VTSS_IOREG(VTSS_TO_REW,0x4220 + (ri))

/**
 * \brief
 * Neighbor rate ration per ingress port encoded as the GM_RATERATIO
 *
 * \details
 * Field: ::VTSS_REW_GPTP_PORTID_CFG . GPTP_PORTID_VAL
 */
#define  VTSS_F_REW_GPTP_PORTID_CFG_GPTP_PORTID_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_GPTP_PORTID_CFG_GPTP_PORTID_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_GPTP_PORTID_CFG_GPTP_PORTID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_LAGUNA_REGS_REW_H_ */
