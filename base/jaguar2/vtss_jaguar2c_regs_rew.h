// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2C_REGS_REW_H_
#define _VTSS_JAGUAR2C_REGS_REW_H_


#include "vtss_jaguar2c_regs_common.h"

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
 * \brief Common Control configuration
 *
 * \details
 * Register: \a REW:COMMON:COMMON_CTRL
 */
#define VTSS_REW_COMMON_COMMON_CTRL          VTSS_IOREG(VTSS_TO_REW,0x14f00)

/** 
 * \brief
 * Used when frames are L3 forwarded to a stack port.
 * 
 * When this bit is set, the reserved fields in the VSTAX.DST field is
 * cleared

 *
 * \details 
 * 0: Keep VSTAX.DST field as received
 * 1: Clear VSTAX.DST reserved fields when L3 forwarding
 *
 * Field: ::VTSS_REW_COMMON_COMMON_CTRL . L3_CLR_VSTAX_DST_RSV
 */
#define  VTSS_F_REW_COMMON_COMMON_CTRL_L3_CLR_VSTAX_DST_RSV(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_REW_COMMON_COMMON_CTRL_L3_CLR_VSTAX_DST_RSV  VTSS_BIT(7)
#define  VTSS_X_REW_COMMON_COMMON_CTRL_L3_CLR_VSTAX_DST_RSV(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Configures own UPSID to be used for stacking.
 * 
 * This must be configured consistently across the following registers:
 * ANA_CL::UPSID_CFG.UPSID_NUM
 * ANA_AC::COMMON_VSTAX_CFG.OWN_UPSID
 * ANA_L2::VSTAX_CTRL.OWN_UPSID
 * REW::COMMON_CTRL.OWN_UPSID

 *
 * \details 
 * n: UPSID

 *
 * Field: ::VTSS_REW_COMMON_COMMON_CTRL . OWN_UPSID
 */
#define  VTSS_F_REW_COMMON_COMMON_CTRL_OWN_UPSID(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_REW_COMMON_COMMON_CTRL_OWN_UPSID     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_REW_COMMON_COMMON_CTRL_OWN_UPSID(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * Control if frames are aborted if the IFH.ENCAP.WORD16_POP_CNT field is
 * out of the supported range.
 *
 * \details 
 * 0: Keep frame
 * 1: Abort frame
 *
 * Field: ::VTSS_REW_COMMON_COMMON_CTRL . INVLD_W16_POP_CNT_FRM_ABORT
 */
#define  VTSS_F_REW_COMMON_COMMON_CTRL_INVLD_W16_POP_CNT_FRM_ABORT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_COMMON_COMMON_CTRL_INVLD_W16_POP_CNT_FRM_ABORT  VTSS_BIT(1)
#define  VTSS_X_REW_COMMON_COMMON_CTRL_INVLD_W16_POP_CNT_FRM_ABORT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When padding is required after tag removal, also the FCS will be removed
 * before zero padding and new FCS is added.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_REW_COMMON_COMMON_CTRL . FRM_CLR_PAD_ENA
 */
#define  VTSS_F_REW_COMMON_COMMON_CTRL_FRM_CLR_PAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_COMMON_CTRL_FRM_CLR_PAD_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_COMMON_CTRL_FRM_CLR_PAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Port based configuration for rewriter
 *
 * \details
 * Configuration of rewriter ports.

 *
 * Register: \a REW:COMMON:PORT_CTRL
 *
 * @param ri Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_COMMON_PORT_CTRL(ri)        VTSS_IOREG(VTSS_TO_REW,0x14f01 + (ri))

/** 
 * \brief
 * Map the configuration port to a logical port number to be used by ES0
 * keys. The port used for the lookup can be Tx-mirrored.
 * 
 * Use the unmapped port number, if the mapped value is outside port range
 * (default)

 *
 * \details 
 * 0-10: Use this port number for ES0 lookup
 * 11-15: Do not map port number
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . ES0_LPORT_NUM
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_ES0_LPORT_NUM(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_REW_COMMON_PORT_CTRL_ES0_LPORT_NUM     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_REW_COMMON_PORT_CTRL_ES0_LPORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,24,6)

/** 
 * \brief
 * Configures the extraction statistics pipeline point. Frames extracted
 * before the configured pipeline point are not counted by the ESDX
 * counters
 * 
 * Configuring the value 'REW_IN_MIP' will cause all extracted frames to be
 * counted.
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
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . XTR_STAT_PIPELINE_PT
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_XTR_STAT_PIPELINE_PT(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_REW_COMMON_PORT_CTRL_XTR_STAT_PIPELINE_PT     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_REW_COMMON_PORT_CTRL_XTR_STAT_PIPELINE_PT(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Configures the injection statistics pipeline point. Frames injected
 * after the configured pipeline point are not counted by the ESDX
 * counters.
 * 
 * Configuring the value 'REW_'VRAP will cause all injected frames to be
 * counted.

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
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . INJ_STAT_PIPELINE_PT
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_INJ_STAT_PIPELINE_PT(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_REW_COMMON_PORT_CTRL_INJ_STAT_PIPELINE_PT     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_REW_COMMON_PORT_CTRL_INJ_STAT_PIPELINE_PT(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Configure VSTAX MISC field decoding.
 * 
 * The configuration can be Tx-mirrored.
 *
 * \details 
 * 0: VSTAX MISC contains aggregation code
 * 1: VSTAX MISC contains ISDX and COSID
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . VSTAX2_MISC_ISDX_ENA
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_VSTAX2_MISC_ISDX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_REW_COMMON_PORT_CTRL_VSTAX2_MISC_ISDX_ENA  VTSS_BIT(15)
#define  VTSS_X_REW_COMMON_PORT_CTRL_VSTAX2_MISC_ISDX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * This configuration applies to VLAN tag awareness in the port VOE for
 * frames for which the rewriter is not pushing new VLAN tags or an MPLS
 * link layer. Each bit corresponds to one of the known TPIDs. If the
 * outgoing frame's outer tag contains a TPID for which
 * PORT_VOE_TPID_AWARE_DIS is set, then the port VOE sees the frame as
 * untagged.
 * 
 * The configuration  is used by the physical port and is not changed for
 * TX-Mirrored frames.
 *
 * \details 
 * Bit0: TPID = 0x8100.
 * Bit1: TPID = 0x88A8
 * Bit2: TPID = REW::TPID_CFG[0].TPID_VAL
 * Bit3: TPID = REW::TPID_CFG[1].TPID_VAL
 * Bit4: TPID = REW::TPID_CFG[2].TPID_VAL
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . PORT_VOE_TPID_AWARE_DIS
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_PORT_VOE_TPID_AWARE_DIS(x)  VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_REW_COMMON_PORT_CTRL_PORT_VOE_TPID_AWARE_DIS     VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_REW_COMMON_PORT_CTRL_PORT_VOE_TPID_AWARE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,10,5)

/** 
 * \brief
 * Default PCP value used by the OAM port VOE. This value is used for port
 * VOE counter updates when no outer Q-Tag is present in a frame.
 * 
 * The configuration is used by the physical port and is not changed for
 * TX-Mirrored frames.

 *
 * \details 
 * n: OAM default PCP value
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . PORT_VOE_DEFAULT_PCP
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_PORT_VOE_DEFAULT_PCP(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_REW_COMMON_PORT_CTRL_PORT_VOE_DEFAULT_PCP     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_REW_COMMON_PORT_CTRL_PORT_VOE_DEFAULT_PCP(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Default DEI value used by the OAM port VOE. This value is used for port
 * VOE counter updates when no outer Q-Tag is present in a frame.
 * 
 * The configuration is used by the physical port and is not changed for
 * TX-Mirrored frames.

 *
 * \details 
 * n: OAM default DEI value
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . PORT_VOE_DEFAULT_DEI
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_PORT_VOE_DEFAULT_DEI(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_COMMON_PORT_CTRL_PORT_VOE_DEFAULT_DEI  VTSS_BIT(6)
#define  VTSS_X_REW_COMMON_PORT_CTRL_PORT_VOE_DEFAULT_DEI(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Configure the rewriter IFH mode for the port.
 * 
 * The configuration  is used by the physical port and is not changed for
 * TX-Mirrored frames.
 * 
 * See ASM::PORT_CFG.INJ_FORMAT_CFG
 *
 * \details 
 * 0: Normal mode. 
 * 1: Keep IFH without modifications. Frames are not updated. IFH is kept
 * 2: Encapsulate IFH. 
 *    The frame's DMAC, SMAC and a fixed TAG with ETYPE=8880 (Vitesse) and
 * EPID=0x0009 are inserted in front of the IFH:
 *	 [FRM_DMAC][FRM_SMAC][0x8880][0x0009][IFH][FRAME]
 * 3: Encapsulate IFH using the ENCAP table
 *    Use ES0 to generate an ENCAP_ID and insert the encapsulation in front
 * of the IFH:
 *	 [ENCAP][IFH][FRAME]
 *    ES0 controlled encapsulations will be used if the ENCAP_ID action is
 * active, otherwise mode 2) is used.
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . KEEP_IFH_SEL
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_REW_COMMON_PORT_CTRL_KEEP_IFH_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Configure tagging of frames with VSTAX.GEN.FWD_MODE = VS2_FWD_GMIRROR.
 * Only active on front ports for frames using this FWD_MODE.
 * 
 * This is used to control the remote mirror tagging of frames that have
 * been mirrored from one unit in the stack to another unit.
 * 
 * The configuration  is used by the physical port and is not changed for
 * TX-Mirrored frames.
 *
 * \details 
 * 0: Always push the remote mirror tag carried VSTAX.TAG into the frame.
 * No other tags are pushed.
 * 1: Obey local port tag configuration.
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . VSTAX2_MIRROR_OBEY_WAS_TAGGED
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_VSTAX2_MIRROR_OBEY_WAS_TAGGED(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_PORT_CTRL_VSTAX2_MIRROR_OBEY_WAS_TAGGED  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_PORT_CTRL_VSTAX2_MIRROR_OBEY_WAS_TAGGED(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable padding of frames to 76 bytes.
 * 
 * If a frame is smaller than 64 bytes when all rewrites are done, the
 * frame is extended to 64 bytes to prevent under size frames leaving the
 * chip. Setting this bit will cause all frames on the port to be extended
 * to 76 bytes instead of 64 bytes. 
 * 
 * This should only optionally be enabled for stacking ports
 * (PORT_CTRL.VSTAX_HDR_ENA = 1). Setting this bit will prevent frames from
 * becoming under sized in a receiving switch, when the VStaX header is
 * removed.
 * 
 * The configuration is used by the physical port and is not changed for
 * TX-Mirrored frames.
 *
 * \details 
 * 0: Normal padding to 64 bytes
 * 1: Pad to 76 bytes
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . VSTAX_PAD_ENA
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_VSTAX_PAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_COMMON_PORT_CTRL_VSTAX_PAD_ENA  VTSS_BIT(2)
#define  VTSS_X_REW_COMMON_PORT_CTRL_VSTAX_PAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable insertion of stacking header in frame.
 * 
 * The configuration is used by the physical port and is not changed for
 * TX-Mirrored frames.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . VSTAX_HDR_ENA
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_VSTAX_HDR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_COMMON_PORT_CTRL_VSTAX_HDR_ENA  VTSS_BIT(1)
#define  VTSS_X_REW_COMMON_PORT_CTRL_VSTAX_HDR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Select logical stacking port (or stacking port group) membership
 * 
 * The configuration is used by the physical port and is not changed for
 * TX-Mirrored frames.
 *
 * \details 
 * 0: Stack A
 * 1: Stack B
 *
 * Field: ::VTSS_REW_COMMON_PORT_CTRL . VSTAX_STACK_GRP_SEL
 */
#define  VTSS_F_REW_COMMON_PORT_CTRL_VSTAX_STACK_GRP_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_PORT_CTRL_VSTAX_STACK_GRP_SEL  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_PORT_CTRL_VSTAX_STACK_GRP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configure custom TPID values
 *
 * \details
 * Register: \a REW:COMMON:TPID_CFG
 *
 * @param ri Register: TPID_CFG (??), 0-2
 */
#define VTSS_REW_COMMON_TPID_CFG(ri)         VTSS_IOREG(VTSS_TO_REW,0x14f36 + (ri))

/** 
 * \brief
 * Configure 3 custom TPID values.
 * 
 * These must be configured identically in
 * ANA_CL::VLAN_STAG_CFG.STAG_ETYPE_VAL.
 * 
 * Related parameters:
 * ANA_CL::VLAN_STAG_CFG.STAG_ETYPE_VAL
 *
 * \details 
 * n: TPID value
 *
 * Field: ::VTSS_REW_COMMON_TPID_CFG . TPID_VAL
 */
#define  VTSS_F_REW_COMMON_TPID_CFG_TPID_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_COMMON_TPID_CFG_TPID_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_COMMON_TPID_CFG_TPID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Various configuration of ES0 in rewriter module 
 *
 * \details
 * Register: \a REW:COMMON:ES0_CTRL
 */
#define VTSS_REW_COMMON_ES0_CTRL             VTSS_IOREG(VTSS_TO_REW,0x14f39)

/** 
 * \brief
 * Via ES0 it is possible to loop frames back to the Analyzer using the
 * LOOP_ENA and FWD_SEL actions. 
 * 
 * If this bit is set, a frame can only be looped once by ES0.
 *
 * \details 
 * 0: No ES0 frame loop limitation
 * 1: Allow only one loop of frame
 *
 * Field: ::VTSS_REW_COMMON_ES0_CTRL . ES0_FRM_LBK_CFG
 */
#define  VTSS_F_REW_COMMON_ES0_CTRL_ES0_FRM_LBK_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_ES0_CTRL_ES0_FRM_LBK_CFG  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_ES0_CTRL_ES0_FRM_LBK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable ES0 router mode lookup when IFH.ENCAP.RT_FWD indicates routing.
 * 
 * When enabled and IFH.FWD.DST_MODE = ENCAP and IFH.ENCAP.RT_FWD = 1, the
 * ES0 'VSI' key field is set to all 1, the VID key field is set to
 * IFH.ENCAP.GEN_IDX and ES0 lookup is always done using VID key type.
 * 
 * If IFH.ENCAP.RT_FWD does not indicate routing, the lookup is done
 * normally regardless of the ES0_BY_RT_FWD configuration.

 *
 * \details 
 * 0: Normal ES0 lookup
 * 1: Enable router mode ES0 lookup
 *
 * Field: ::VTSS_REW_COMMON_ES0_CTRL . ES0_BY_RT_FWD
 */
#define  VTSS_F_REW_COMMON_ES0_CTRL_ES0_BY_RT_FWD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_COMMON_ES0_CTRL_ES0_BY_RT_FWD  VTSS_BIT(2)
#define  VTSS_X_REW_COMMON_ES0_CTRL_ES0_BY_RT_FWD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable ES0 router mode lookup when IFH.FWD.DST_MODE indicates routing.
 * 
 * When enabled and IFH.FWD.DST_MODE = L3UC_ROUTING or IFH.FWD.DST_MODE =
 * L3MC_ROUTING, the ES0 'VSI' key is set to all 1, the VID key field is
 * set to IFH.DST.ERLEG and ES0 lookup is always done using VID key type.
 * 
 * If IFH_FWD.DST_MODE does not indicate routing, the lookup is done
 * normally regardless of the ES0_BY_RLEG configuration.

 *
 * \details 
 * 0: Normal ES0 lookup
 * 1: Enable router mode ES0 lookup
 *
 * Field: ::VTSS_REW_COMMON_ES0_CTRL . ES0_BY_RLEG
 */
#define  VTSS_F_REW_COMMON_ES0_CTRL_ES0_BY_RLEG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_COMMON_ES0_CTRL_ES0_BY_RLEG  VTSS_BIT(1)
#define  VTSS_X_REW_COMMON_ES0_CTRL_ES0_BY_RLEG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable lookup in VCAP_ES0 to control advanced frame modifications.

 *
 * \details 
 * 0: VCAP_ES0 do not control frame modifications
 * 1: VCAP_ES0 controls all frame rewrites
 *
 * Field: ::VTSS_REW_COMMON_ES0_CTRL . ES0_LU_ENA
 */
#define  VTSS_F_REW_COMMON_ES0_CTRL_ES0_LU_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_ES0_CTRL_ES0_LU_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_ES0_CTRL_ES0_LU_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CCM hit me once auto set
 *
 * \details
 * Register: \a REW:COMMON:MIP_CTRL
 */
#define VTSS_REW_COMMON_MIP_CTRL             VTSS_IOREG(VTSS_TO_REW,0x14f3a)

/** 
 * \brief
 * Set all CCM Hit me once bits. 
 * 
 * Cleared when the access completes.
 * 
 * Ref: REW:MIP_TBL:CCM_HMO_CTRL
 *
 * \details 
 * 0: Idle
 * 1: Initiate setting all CCM_HMO_CTRL.CCM_COPY_ONCE_ENA where
 * MIP_CCM_INTERVAL_MASK[CCM_HMO_CTRL.CCM_INTERVAL] is set
 * 
 * The bit is cleared upon completion
 *
 * Field: ::VTSS_REW_COMMON_MIP_CTRL . MIP_CCM_HMO_SET_SHOT
 */
#define  VTSS_F_REW_COMMON_MIP_CTRL_MIP_CCM_HMO_SET_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_MIP_CTRL_MIP_CCM_HMO_SET_SHOT  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_MIP_CTRL_MIP_CCM_HMO_SET_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Specifies which MIP CCM intervals that will have CCM_COPY_ONCE_ENA set.
 *
 * \details 
 * x0x: Interval is ignored
 * x1x: REW:MIP_TBL:CCM_HMO_CTRL.CCM_COPY_ONCE_ENA  is set where
 * MIP_CCM_INTERVAL_MASK[CCM_HMO_CTRL.CCM_INTERVAL] is set.
 *
 * Field: ::VTSS_REW_COMMON_MIP_CTRL . MIP_CCM_INTERVAL_MASK
 */
#define  VTSS_F_REW_COMMON_MIP_CTRL_MIP_CCM_INTERVAL_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_REW_COMMON_MIP_CTRL_MIP_CCM_INTERVAL_MASK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_REW_COMMON_MIP_CTRL_MIP_CCM_INTERVAL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Configure mirror probes
 *
 * \details
 * Related parameters:
 * ANA_AC:MIRROR_PROBE
 *
 * Register: \a REW:COMMON:MIRROR_PROBE_CFG
 *
 * @param ri Replicator: x_NUM_MIRROR_PROBES (??), 0-2
 */
#define VTSS_REW_COMMON_MIRROR_PROBE_CFG(ri)  VTSS_IOREG(VTSS_TO_REW,0x14f3b + (ri))

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
 * Field: ::VTSS_REW_COMMON_MIRROR_PROBE_CFG . MIRROR_TX_PORT
 */
#define  VTSS_F_REW_COMMON_MIRROR_PROBE_CFG_MIRROR_TX_PORT(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_REW_COMMON_MIRROR_PROBE_CFG_MIRROR_TX_PORT     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_REW_COMMON_MIRROR_PROBE_CFG_MIRROR_TX_PORT(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Select encapsulation ID to use for remote mirror frames.
 *
 * \details 
 * 0: No encapsulation
 * 1-n: Encapsulation ID n
 *
 * Field: ::VTSS_REW_COMMON_MIRROR_PROBE_CFG . REMOTE_ENCAP_ID
 */
#define  VTSS_F_REW_COMMON_MIRROR_PROBE_CFG_REMOTE_ENCAP_ID(x)  VTSS_ENCODE_BITFIELD(x,2,10)
#define  VTSS_M_REW_COMMON_MIRROR_PROBE_CFG_REMOTE_ENCAP_ID     VTSS_ENCODE_BITMASK(2,10)
#define  VTSS_X_REW_COMMON_MIRROR_PROBE_CFG_REMOTE_ENCAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,10)

/** 
 * \brief
 * Enable encapsulation of mirrored frames. One or two Q-Tags (Q-in-Q) or
 * the encapsulation table can be used.
 * 
 * In tag mode the VLAN tags will be added in the outer most position after
 * the SMAC. This will also be the case if a MPLS link layer is added to
 * the frame. The tags will then be added after LL-SMAC.
 * 
 * In encapsulation mode an entry in the ENCAP-table is used for
 * encapsulation. This will override any encapsulation selected by ES0 for
 * the frame.
 *
 * \details 
 * 0: Local mirror port. No encapsulation
 * 1: Add one VLAN tag. Configured by MIRROR_TAG_A_CFG
 * 2: Add two VLAN tags. Configured by MIRROR_TAG_A_CFG and
 * MIRROR_TAG_B_CFG
 * 3: Use ENCAP table selected by REMOTE_ENCAP_ID
 *
 * Field: ::VTSS_REW_COMMON_MIRROR_PROBE_CFG . REMOTE_MIRROR_CFG
 */
#define  VTSS_F_REW_COMMON_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_COMMON_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_COMMON_MIRROR_PROBE_CFG_REMOTE_MIRROR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Configure mirror probes
 *
 * \details
 * Configuration of mirror QTag A. Each mirror probe can be configured
 * individually.
 *
 * Register: \a REW:COMMON:MIRROR_TAG_A_CFG
 *
 * @param ri Replicator: x_NUM_MIRROR_PROBES (??), 0-2
 */
#define VTSS_REW_COMMON_MIRROR_TAG_A_CFG(ri)  VTSS_IOREG(VTSS_TO_REW,0x14f3e + (ri))

/** 
 * \brief
 * Mirror Q-tag A Tag Protocol Identifier(TPID)
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
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_A_CFG . TAG_A_TPID_SEL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_TPID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/** 
 * \brief
 * Mirror Q-tag A VID value.
 *
 * \details 
 * n: VID n
 *
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_A_CFG . TAG_A_VID_VAL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,5,12)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_VID_VAL     VTSS_ENCODE_BITMASK(5,12)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,12)

/** 
 * \brief
 * Mirror Q-tag A DEI value.
 *
 * \details 
 * 0: DEI bit = 0
 * 1: DEI bit = 1
 *
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_A_CFG . TAG_A_DEI_VAL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_DEI_VAL  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selection of mirror Q-tag A PCP value.
 *
 * \details 
 * 0: Use classified PCP
 * 1: Use TAG_A_PCP_VAL
 *
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_A_CFG . TAG_A_PCP_SEL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_PCP_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_PCP_SEL  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_PCP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Mirror Q-tag A PCP value.
 *
 * \details 
 * n: PCP n

 *
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_A_CFG . TAG_A_PCP_VAL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_PCP_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_A_CFG_TAG_A_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Configure mirror probes
 *
 * \details
 * Configuration of mirror QTag B. Each mirror probe can be configured
 * individually.
 *
 * Register: \a REW:COMMON:MIRROR_TAG_B_CFG
 *
 * @param ri Replicator: x_NUM_MIRROR_PROBES (??), 0-2
 */
#define VTSS_REW_COMMON_MIRROR_TAG_B_CFG(ri)  VTSS_IOREG(VTSS_TO_REW,0x14f41 + (ri))

/** 
 * \brief
 * Mirror Q-tag B Tag Protocol Identifier(TPID)
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
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_B_CFG . TAG_B_TPID_SEL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_TPID_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_TPID_SEL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_TPID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/** 
 * \brief
 * Mirror Q-tag B VID value.
 *
 * \details 
 * n: VID n
 *
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_B_CFG . TAG_B_VID_VAL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,5,12)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_VID_VAL     VTSS_ENCODE_BITMASK(5,12)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,12)

/** 
 * \brief
 * Mirror Q-tag B DEI value.
 *
 * \details 
 * 0: DEI bit = 0
 * 1: DEI bit = 1
 *
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_B_CFG . TAG_B_DEI_VAL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_DEI_VAL  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selection of mirror Q-tag B PCP value.
 *
 * \details 
 * 0: Use classified PCP
 * 1: Use TAG_B_PCP_VAL
 *
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_B_CFG . TAG_B_PCP_SEL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_PCP_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_PCP_SEL  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_PCP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Mirror Q-tag B PCP value.
 *
 * \details 
 * n: PCP n

 *
 * Field: ::VTSS_REW_COMMON_MIRROR_TAG_B_CFG . TAG_B_PCP_VAL
 */
#define  VTSS_F_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_PCP_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_COMMON_MIRROR_TAG_B_CFG_TAG_B_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


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
#define VTSS_REW_COMMON_DP_MAP               VTSS_IOREG(VTSS_TO_REW,0x14f44)

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
 * Field: ::VTSS_REW_COMMON_DP_MAP . DP
 */
#define  VTSS_F_REW_COMMON_DP_MAP_DP(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_REW_COMMON_DP_MAP_DP          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_REW_COMMON_DP_MAP_DP(x)       VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Remap table of DSCP values.
 *
 * \details
 * Register: \a REW:COMMON:DSCP_REMAP
 *
 * @param ri Register: DSCP_REMAP (??), 0-63
 */
#define VTSS_REW_COMMON_DSCP_REMAP(ri)       VTSS_IOREG(VTSS_TO_REW,0x14f45 + (ri))

/** 
 * \brief
 * Full one to one DSCP remapping table common for all ports.
 *
 * \details 
 * Field: ::VTSS_REW_COMMON_DSCP_REMAP . DSCP_REMAP
 */
#define  VTSS_F_REW_COMMON_DSCP_REMAP_DSCP_REMAP(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_REW_COMMON_DSCP_REMAP_DSCP_REMAP     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_REW_COMMON_DSCP_REMAP_DSCP_REMAP(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Rewriter router leg configuration.
 *
 * \details
 * Register: \a REW:COMMON:RLEG_CFG_0
 */
#define VTSS_REW_COMMON_RLEG_CFG_0           VTSS_IOREG(VTSS_TO_REW,0x14f85)

/** 
 * \brief
 * Router leg base MAC address, least significant bits.
 * 
 * In order to have different MAC addresses per router leg, the base
 * address may be incremented using VID or VMID, ref. RLEG_MAC_TYPE_SEL.
 * 
 * This must be configured consistently in ANA_L3::RLEG_CFG_0.RLEG_MAC_LSB.

 *
 * \details 
 * Bit 0: MAC address, bit 0
 * ...
 * Bit 23: MAC address, bit 23
 *
 * Field: ::VTSS_REW_COMMON_RLEG_CFG_0 . RLEG_MAC_LSB
 */
#define  VTSS_F_REW_COMMON_RLEG_CFG_0_RLEG_MAC_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_REW_COMMON_RLEG_CFG_0_RLEG_MAC_LSB     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_REW_COMMON_RLEG_CFG_0_RLEG_MAC_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief Rewriter router leg configuration.
 *
 * \details
 * Register: \a REW:COMMON:RLEG_CFG_1
 */
#define VTSS_REW_COMMON_RLEG_CFG_1           VTSS_IOREG(VTSS_TO_REW,0x14f86)

/** 
 * \brief
 * Configuration of router leg specific MAC address.
 * 
 * This must be configured consistently in
 * ANA_L3::RLEG_CFG_1.RLEG_MAC_TYPE_SEL.

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
 * Field: ::VTSS_REW_COMMON_RLEG_CFG_1 . RLEG_MAC_TYPE_SEL
 */
#define  VTSS_F_REW_COMMON_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_REW_COMMON_RLEG_CFG_1_RLEG_MAC_TYPE_SEL     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_REW_COMMON_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Router leg base MAC address, least significant bits.
 * 
 * In order to have different MAC addresses per router leg, the base
 * address may be incremented using VID or VMID, ref. RLEG_MAC_TYPE_SEL.
 * 
 * This must be configured consistently in ANA_L3::RLEG_CFG_1.RLEG_MAC_MSB.
 *
 * \details 
 * Bit 0: MAC address, bit 24
 * ...
 * Bit 23: MAC address, bit 47
 *
 * Field: ::VTSS_REW_COMMON_RLEG_CFG_1 . RLEG_MAC_MSB
 */
#define  VTSS_F_REW_COMMON_RLEG_CFG_1_RLEG_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_REW_COMMON_RLEG_CFG_1_RLEG_MAC_MSB     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_REW_COMMON_RLEG_CFG_1_RLEG_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief Control register for counter events
 *
 * \details
 * Register: \a REW:COMMON:CNT_CTRL
 */
#define VTSS_REW_COMMON_CNT_CTRL             VTSS_IOREG(VTSS_TO_REW,0x14f87)

/** 
 * \brief
 * Select from which source port events are counted.
 *
 * \details 
 * 'n': Count events from source port n
 *
 * Field: ::VTSS_REW_COMMON_CNT_CTRL . EVENT_CNT_PORT
 */
#define  VTSS_F_REW_COMMON_CNT_CTRL_EVENT_CNT_PORT(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_REW_COMMON_CNT_CTRL_EVENT_CNT_PORT     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_REW_COMMON_CNT_CTRL_EVENT_CNT_PORT(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * If set to 1 events from all ports are counted. If 0 the port is selected
 * by the 'EVENT_CNT_PORT' register
 *
 * \details 
 * 0: Count events from the port selected by 'EVENT_CNT_PORT'
 * 1: Count events from all ports
 *
 * Field: ::VTSS_REW_COMMON_CNT_CTRL . EVENT_CNT_ALL
 */
#define  VTSS_F_REW_COMMON_CNT_CTRL_EVENT_CNT_ALL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_CNT_CTRL_EVENT_CNT_ALL  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_CNT_CTRL_EVENT_CNT_ALL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Configure ESDX counting for stacking ports.
 * 
 * If this bit is set and PORT_CTRL.VSTAX_HDR_ENA=1, all counting based on
 * the ESDX value is disabled regardless of the CNT_CTRL.STAT_MODE
 * configuration.
 * 
 * Related parameters:
 * ANA_AC:PS_COMMON:COMMON_VSTAX_CFG.VSTAX2_ISDX_STAT_DIS
 *
 * \details 
 * 0: Normal ESDX statistics mode
 * 1: Disable ESDX statistics for stacking ports
 *
 * Field: ::VTSS_REW_COMMON_CNT_CTRL . VSTAX_STAT_ESDX_DIS
 */
#define  VTSS_F_REW_COMMON_CNT_CTRL_VSTAX_STAT_ESDX_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_CNT_CTRL_VSTAX_STAT_ESDX_DIS  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_CNT_CTRL_VSTAX_STAT_ESDX_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable counting of frames discarded by the REW. The QSYS abort
 * statistics counters are used.
 * 
 * This bit only enables counting of frames discarded by ES0 or the SW_MIP.
 * Frame discards done by the OAM MEP are not included.
 *
 * \details 
 * 0: Disable counting
 * 1: Enable counting
 *
 * Field: ::VTSS_REW_COMMON_CNT_CTRL . STAT_CNT_FRM_ABORT_ENA
 */
#define  VTSS_F_REW_COMMON_CNT_CTRL_STAT_CNT_FRM_ABORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_COMMON_CNT_CTRL_STAT_CNT_FRM_ABORT_ENA  VTSS_BIT(2)
#define  VTSS_X_REW_COMMON_CNT_CTRL_STAT_CNT_FRM_ABORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Configures the egress service statistics mode. The following options for
 * looking up the egress service counter set are available:
 * 
 * In mode 0 and 1 yellow frames (DE=1) are counted separately
 * In mode 2 and 3 multicast frames (DMAC bit 40 = 1) are counted
 * separately
 * 
 * Related parameters:
 * ANA_AC:PS_COMMON:MISC_CTRL.USE_VID_AS_ISDX_ENA
 *
 * \details 
 * 0: Use ESDX from ES0 if hit, otherwise ISDX
 * 1: Use ESDX from ES0 if hit, otherwise no counting
 * 2: Use ISDX (ifh.vstax.misc.isdx as index)
 * 3: Use classified VID (ifh.vstax.tag.vid)
 *
 * Field: ::VTSS_REW_COMMON_CNT_CTRL . STAT_MODE
 */
#define  VTSS_F_REW_COMMON_CNT_CTRL_STAT_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_COMMON_CNT_CTRL_STAT_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_COMMON_CNT_CTRL_STAT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Controls the common sticky event counter.
 *
 * \details
 * Register: \a REW:COMMON:STICKY_EVENT_COUNT
 */
#define VTSS_REW_COMMON_STICKY_EVENT_COUNT   VTSS_IOREG(VTSS_TO_REW,0x14f88)

/** 
 * \brief
 * Counter with number of masked events. Multiple simultaneously events are
 * counted as one.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_COUNT . STICKY_EVENT_COUNTER
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_COUNT_STICKY_EVENT_COUNTER(x)  (x)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_COUNT_STICKY_EVENT_COUNTER     0xffffffff
#define  VTSS_X_REW_COMMON_STICKY_EVENT_COUNT_STICKY_EVENT_COUNTER(x)  (x)


/** 
 * \brief Mask for the STICKY_EVENT_COUNT
 *
 * \details
 * Register: \a REW:COMMON:STICKY_EVENT_CNT_MASK_CFG
 */
#define VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG  VTSS_IOREG(VTSS_TO_REW,0x14f89)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . INVLD_W16_POP_CNT_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_W16_POP_CNT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_W16_POP_CNT_STICKY_MASK  VTSS_BIT(16)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_W16_POP_CNT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . INVLD_POP_CNT_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_POP_CNT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_POP_CNT_STICKY_MASK  VTSS_BIT(15)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_POP_CNT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . REWRITE_OVERFLOW_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_REWRITE_OVERFLOW_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_REWRITE_OVERFLOW_STICKY_MASK  VTSS_BIT(14)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_REWRITE_OVERFLOW_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . VLAN_UNTAGGED_VID0_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAGGED_VID0_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAGGED_VID0_STICKY_MASK  VTSS_BIT(13)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAGGED_VID0_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . VLAN_PRIO_TAGGED_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_PRIO_TAGGED_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_PRIO_TAGGED_STICKY_MASK  VTSS_BIT(12)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_PRIO_TAGGED_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . IP6_MC_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP6_MC_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP6_MC_STICKY_MASK  VTSS_BIT(11)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP6_MC_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . IP4_MC_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP4_MC_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP4_MC_STICKY_MASK  VTSS_BIT(10)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP4_MC_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . IP6_UC_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP6_UC_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP6_UC_STICKY_MASK  VTSS_BIT(9)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP6_UC_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . IP4_UC_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP4_UC_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP4_UC_STICKY_MASK  VTSS_BIT(8)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_IP4_UC_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . DSCP_REMAP_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_DSCP_REMAP_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_DSCP_REMAP_STICKY_MASK  VTSS_BIT(7)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_DSCP_REMAP_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . DSCP_REPLACE_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_DSCP_REPLACE_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_DSCP_REPLACE_STICKY_MASK  VTSS_BIT(6)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_DSCP_REPLACE_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . INVLD_IFH_FOR_PTP_FRM_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_IFH_FOR_PTP_FRM_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_IFH_FOR_PTP_FRM_STICKY_MASK  VTSS_BIT(5)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_INVLD_IFH_FOR_PTP_FRM_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . LINK_LAYER_ERROR_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ERROR_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ERROR_STICKY_MASK  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ERROR_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . LINK_LAYER_ADDED_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ADDED_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ADDED_STICKY_MASK  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_LINK_LAYER_ADDED_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . VLAN_TAG_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_TAG_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_TAG_STICKY_MASK  VTSS_BIT(2)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_TAG_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . VLAN_UNTAG_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAG_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAG_STICKY_MASK  VTSS_BIT(1)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_UNTAG_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable counting of the event
 *
 * \details 
 * 0: Sticky event will not be counted
 * 1: Sticky event will be counted
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG . VLAN_POP_CNT_STICKY_MASK
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_POP_CNT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_POP_CNT_STICKY_MASK  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_CNT_MASK_CFG_VLAN_POP_CNT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Rewriter sticky bit register
 *
 * \details
 * Register: \a REW:COMMON:STICKY_EVENT
 */
#define VTSS_REW_COMMON_STICKY_EVENT         VTSS_IOREG(VTSS_TO_REW,0x14f8a)

/** 
 * \brief
 * This bit is set if an invalid 'pop_cnt' value is received in the IFH
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . INVLD_W16_POP_CNT_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_INVLD_W16_POP_CNT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_INVLD_W16_POP_CNT_STICKY  VTSS_BIT(16)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_INVLD_W16_POP_CNT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * This bit is set if an invalid 'pop_cnt' value is received in the IFH
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . INVLD_POP_CNT_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_INVLD_POP_CNT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_INVLD_POP_CNT_STICKY  VTSS_BIT(15)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_INVLD_POP_CNT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Encapsulation overflow. Mismatching pop/push operations
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . REWRITE_OVERFLOW_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_REWRITE_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_REWRITE_OVERFLOW_STICKY  VTSS_BIT(14)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_REWRITE_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Untagged frame event due to VID=0 is detected
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . VLAN_UNTAGGED_VID0_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_VLAN_UNTAGGED_VID0_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_VLAN_UNTAGGED_VID0_STICKY  VTSS_BIT(13)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_VLAN_UNTAGGED_VID0_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Priority tagged frame event is detected
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . VLAN_PRIO_TAGGED_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_VLAN_PRIO_TAGGED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_VLAN_PRIO_TAGGED_STICKY  VTSS_BIT(12)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_VLAN_PRIO_TAGGED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * This bit is set if an IP6 frame has been L3 multicast forwarded
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . IP6_MC_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_IP6_MC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_IP6_MC_STICKY  VTSS_BIT(11)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_IP6_MC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * This bit is set if an IP4 frame has been L3 multicast forwarded
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . IP4_MC_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_IP4_MC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_IP4_MC_STICKY  VTSS_BIT(10)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_IP4_MC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * This bit is set if an IP6 frame has been unicast forwarded.
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . IP6_UC_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_IP6_UC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_IP6_UC_STICKY  VTSS_BIT(9)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_IP6_UC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * This bit is set if an IP4 frame has unicast forwarded.
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . IP4_UC_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_IP4_UC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_IP4_UC_STICKY  VTSS_BIT(8)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_IP4_UC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * This bit is set if a DSCP remap event is detected
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . DSCP_REMAP_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_DSCP_REMAP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_DSCP_REMAP_STICKY  VTSS_BIT(7)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_DSCP_REMAP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This bit is set if a DSCP has been replaced event is detected
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . DSCP_REPLACE_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_DSCP_REPLACE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_DSCP_REPLACE_STICKY  VTSS_BIT(6)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_DSCP_REPLACE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * This bit is set if the IFH is not correct for PTP frames
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . INVLD_IFH_FOR_PTP_FRM_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_INVLD_IFH_FOR_PTP_FRM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_INVLD_IFH_FOR_PTP_FRM_STICKY  VTSS_BIT(5)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_INVLD_IFH_FOR_PTP_FRM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This bit is set if a frames out of the REW is missing the link layer
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . LINK_LAYER_ERROR_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_LINK_LAYER_ERROR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_LINK_LAYER_ERROR_STICKY  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_LINK_LAYER_ERROR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * This bit is set if a new link layer has been added to a frame
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . LINK_LAYER_ADDED_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_LINK_LAYER_ADDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_LINK_LAYER_ADDED_STICKY  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_LINK_LAYER_ADDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * This bit is set if a VLAN tag event is detected
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . VLAN_TAG_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_VLAN_TAG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_VLAN_TAG_STICKY  VTSS_BIT(2)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_VLAN_TAG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This bit is set if a VLAN untag event is detected
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . VLAN_UNTAG_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_VLAN_UNTAG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_VLAN_UNTAG_STICKY  VTSS_BIT(1)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_VLAN_UNTAG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This bit is set if a VLAN pop event is detected
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_STICKY_EVENT . VLAN_POP_CNT_STICKY
 */
#define  VTSS_F_REW_COMMON_STICKY_EVENT_VLAN_POP_CNT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_STICKY_EVENT_VLAN_POP_CNT_STICKY  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_STICKY_EVENT_VLAN_POP_CNT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_REW_COMMON_GCPU_CFG(ri)         VTSS_IOREG(VTSS_TO_REW,0x14f8b + (ri))

/** 
 * \brief
 * Used when GCPU frames are forwarded to a front port. 
 * 
 * Frames are sent with the IFH preserved. The IFH is encapsulated
 * according to the configuration. Setting GCPU_KEEP_IFH to a value
 * different from 0 overrides the GCPU_TAG_SEL and GCPU_DO_NOT_REW settings
 * for front ports. No other rewrites are done to the frame.
 * 
 * The GCPU_KEEP_IFH setting is not active if PORT_CTRL.KEEP_IFH_SEL is
 * different from 0 or if PORT_CTRL.VSTAX_HDR_ENA=1

 *
 * \details 
 * 0: Normal mode. 
 * 1: Keep IFH without modifications. Frames are not updated. IFH is kept
 * 2: Encapsulate IFH. 
 *    The frame's DMAC, SMAC and a fixed TAG with ETYPE=8880 (Vitesse) and
 * EPID=0x0009 are inserted in front of the IFH:
 *	 [FRM_DMAC][FRM_SMAC][0x8880][0x0009][IFH][FRAME]
 * 3: Encapsulate IFH using the ENCAP table
 *    Use ES0 to generate an ENCAP_ID and insert the encapsulation in front
 * of the IFH:
 *	 [ENCAP][IFH][FRAME]
 *    ES0 controlled encapsulations will be used if the ENCAP_ID action is
 * active, otherwise mode 2) is used.
 *
 * Field: ::VTSS_REW_COMMON_GCPU_CFG . GCPU_KEEP_IFH
 */
#define  VTSS_F_REW_COMMON_GCPU_CFG_GCPU_KEEP_IFH(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_REW_COMMON_GCPU_CFG_GCPU_KEEP_IFH     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_REW_COMMON_GCPU_CFG_GCPU_KEEP_IFH(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Used when GCPU frames are forwarded to a front port. 
 * 
 * Frame are not modified when forwarded to the GCPU expect for the
 * optional tags configured in GCPU_CFG.GCPU_TAG_SEL
 *
 * \details 
 * 0: Allow normal rewrites of GCPU frames forwarded to front ports
 * 1: Allow only addition of GCPU_TAGS to GCPU frames
 *
 * Field: ::VTSS_REW_COMMON_GCPU_CFG . GCPU_DO_NOT_REW
 */
#define  VTSS_F_REW_COMMON_GCPU_CFG_GCPU_DO_NOT_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_REW_COMMON_GCPU_CFG_GCPU_DO_NOT_REW  VTSS_BIT(19)
#define  VTSS_X_REW_COMMON_GCPU_CFG_GCPU_DO_NOT_REW(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * When a GCPU frame is forwarded to a stack port:
 * Force a change of the VSTAX.TAG to the configured values in
 * GCPU_TAG_CFG:0
 * 
 * When a GCPU frame is forwarded to a front port:
 * Optionally add one or two Q-tags to the frame. The tags are configured
 * using GCPU_TAG_CFG
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
 * Field: ::VTSS_REW_COMMON_GCPU_CFG . GCPU_TAG_SEL
 */
#define  VTSS_F_REW_COMMON_GCPU_CFG_GCPU_TAG_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_REW_COMMON_GCPU_CFG_GCPU_TAG_SEL     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_REW_COMMON_GCPU_CFG_GCPU_TAG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * Used when GCPU frames are forwarded to a stack port. 
 * 
 * Configure forward mode of GCPU frames on stack ports by selecting value
 * of VSTAX.GEN.FWD_MODE.
 *
 * \details 
 * 0: VSTAX.GEN.FWD_MODE = VS2_FWD_GCPU_UPS
 * Forward the frame to a specific unit in the stack
 * 
 * 1: VSTAX.GEN.FWD_MODE = VS2_FWD_PHYSICAL
 * Forward the frame to a specific port on a specific unit in the stack.
 *
 * Field: ::VTSS_REW_COMMON_GCPU_CFG . GCPU_FWD_MODE
 */
#define  VTSS_F_REW_COMMON_GCPU_CFG_GCPU_FWD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_COMMON_GCPU_CFG_GCPU_FWD_MODE  VTSS_BIT(16)
#define  VTSS_X_REW_COMMON_GCPU_CFG_GCPU_FWD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Used when GCPU frames are forwarded to a stack port. 
 * 
 * DST_PN to be used as destination in the VSTAX header. Set
 * VSTAX.DST.DST_PN to configured value.
 *
 * \details 
 * 0: DST_PN 0
 * 1: DST_PN 1
 * ... 
 * n: DST_PN n
 *
 * Field: ::VTSS_REW_COMMON_GCPU_CFG . GCPU_UPSPN
 */
#define  VTSS_F_REW_COMMON_GCPU_CFG_GCPU_UPSPN(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_REW_COMMON_GCPU_CFG_GCPU_UPSPN     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_REW_COMMON_GCPU_CFG_GCPU_UPSPN(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Used when GCPU frames are forwarded to a stack port. 
 * 
 * DST_UPSID to be used as destination in the VSTAX header. Set
 * VSTAX.DST.DST_UPSID to configured value.
 *
 * \details 
 * 0: DST_UPSID 0
 * 1: DST_UPSID 1
 * ... 
 * n: DST_UPSID n
 *
 * Field: ::VTSS_REW_COMMON_GCPU_CFG . GCPU_UPSID
 */
#define  VTSS_F_REW_COMMON_GCPU_CFG_GCPU_UPSID(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_REW_COMMON_GCPU_CFG_GCPU_UPSID     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_REW_COMMON_GCPU_CFG_GCPU_UPSID(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief VSTAX Configuration per logical Stacking port
 *
 * \details
 * Register: \a REW:COMMON:VSTAX_PORT_GRP_CFG
 *
 * @param ri Register: VSTAX_PORT_GRP_CFG (??), 0-1
 */
#define VTSS_REW_COMMON_VSTAX_PORT_GRP_CFG(ri)  VTSS_IOREG(VTSS_TO_REW,0x14f93 + (ri))

/** 
 * \brief
 * Link TTL value
 *
 * \details 
 * Field: ::VTSS_REW_COMMON_VSTAX_PORT_GRP_CFG . VSTAX_TTL
 */
#define  VTSS_F_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_TTL(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_TTL     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_TTL(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * Change priority for learn all frames.
 *
 * \details 
 * 0: Disable
 * 1: Enable (Learn all are send with highest priority)
 *
 * Field: ::VTSS_REW_COMMON_VSTAX_PORT_GRP_CFG . VSTAX_LRN_ALL_HP_ENA
 */
#define  VTSS_F_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_LRN_ALL_HP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_LRN_ALL_HP_ENA  VTSS_BIT(1)
#define  VTSS_X_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_LRN_ALL_HP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Control whether forwarding modes specific to VStaX AF shall be
 * translated to BF forwarding modes.
 * 
 * If set to 0, the following translation will be performed:
 * fwd_logical -> fwd_lookup
 * fwd_mc -> fwd_lookup
 * 
 * If set to 1, no translation will be performed.
 * 
 * Translation is only required for AF switches operating in a BF stack.

 *
 * \details 
 * 0: Perform fwd_mode translation.
 * 1: Do not perform fwd_mode translation.
 *
 * Field: ::VTSS_REW_COMMON_VSTAX_PORT_GRP_CFG . VSTAX_MODE
 */
#define  VTSS_F_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_MODE  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_VSTAX_PORT_GRP_CFG_VSTAX_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_REW_COMMON_GCPU_TAG_CFG(ri)     VTSS_IOREG(VTSS_TO_REW,0x14f95 + (ri))

/** 
 * \brief
 * GCPU Q-tag Tag Protocol Identifiers(TPID)
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
 * Field: ::VTSS_REW_COMMON_GCPU_TAG_CFG . TAG_TPID_SEL
 */
#define  VTSS_F_REW_COMMON_GCPU_TAG_CFG_TAG_TPID_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_REW_COMMON_GCPU_TAG_CFG_TAG_TPID_SEL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_REW_COMMON_GCPU_TAG_CFG_TAG_TPID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/** 
 * \brief
 * GCPU Q-tag VID values
 *
 * \details 
 * n: VID n
 *
 * Field: ::VTSS_REW_COMMON_GCPU_TAG_CFG . TAG_VID_VAL
 */
#define  VTSS_F_REW_COMMON_GCPU_TAG_CFG_TAG_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,5,12)
#define  VTSS_M_REW_COMMON_GCPU_TAG_CFG_TAG_VID_VAL     VTSS_ENCODE_BITMASK(5,12)
#define  VTSS_X_REW_COMMON_GCPU_TAG_CFG_TAG_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,12)

/** 
 * \brief
 * GCPU Q-tag DEI values
 *
 * \details 
 * 0: DEI bit = 0
 * 1: DEI bit = 1
 *
 * Field: ::VTSS_REW_COMMON_GCPU_TAG_CFG . TAG_DEI_VAL
 */
#define  VTSS_F_REW_COMMON_GCPU_TAG_CFG_TAG_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_GCPU_TAG_CFG_TAG_DEI_VAL  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_GCPU_TAG_CFG_TAG_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selection of GCPU Q-tag PCP values
 *
 * \details 
 * 0: Use classified PCP
 * 1: Use TAG_PCP_VAL
 *
 * Field: ::VTSS_REW_COMMON_GCPU_TAG_CFG . TAG_PCP_SEL
 */
#define  VTSS_F_REW_COMMON_GCPU_TAG_CFG_TAG_PCP_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_GCPU_TAG_CFG_TAG_PCP_SEL  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_GCPU_TAG_CFG_TAG_PCP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * GCPU Q-tag PCP values.
 *
 * \details 
 * n: PCP n

 *
 * Field: ::VTSS_REW_COMMON_GCPU_TAG_CFG . TAG_PCP_VAL
 */
#define  VTSS_F_REW_COMMON_GCPU_TAG_CFG_TAG_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_COMMON_GCPU_TAG_CFG_TAG_PCP_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_COMMON_GCPU_TAG_CFG_TAG_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Device 10G specific HIH configuration
 *
 * \details
 * This register provides additional HIH configuration for 10G devices.
 *
 * Register: \a REW:COMMON:HIH_DEV10G_CFG
 *
 * @param ri Register: HIH_DEV10G_CFG (??), 0-3
 */
#define VTSS_REW_COMMON_HIH_DEV10G_CFG(ri)   VTSS_IOREG(VTSS_TO_REW,0x14f97 + (ri))

/** 
 * \brief
 * This register configures where the HiH is located for DEV10Gs.
 * 
 * The HiH must be placed in the frame if PTP is enabled for the port.

 *
 * \details 
 * 0: Place the HiH after frame SFD
 * 1: DEV10G::MAC_MODE_CFG.MAC_PREAMBLE_CFG controls the placement.
 *
 * Field: ::VTSS_REW_COMMON_HIH_DEV10G_CFG . HIH_LOCATION
 */
#define  VTSS_F_REW_COMMON_HIH_DEV10G_CFG_HIH_LOCATION(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_HIH_DEV10G_CFG_HIH_LOCATION  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_HIH_DEV10G_CFG_HIH_LOCATION(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Default values for transmitted HIHS
 *
 * \details
 * Register: \a REW:COMMON:HIH_DEF_CFG
 */
#define VTSS_REW_COMMON_HIH_DEF_CFG          VTSS_IOREG(VTSS_TO_REW,0x14f9b)

/** 
 * \brief
 * Default value for the LPID field in transmitted HIH's.
 *
 * \details 
 * Field: ::VTSS_REW_COMMON_HIH_DEF_CFG . HIH_DEF_LPID
 */
#define  VTSS_F_REW_COMMON_HIH_DEF_CFG_HIH_DEF_LPID(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_REW_COMMON_HIH_DEF_CFG_HIH_DEF_LPID     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_REW_COMMON_HIH_DEF_CFG_HIH_DEF_LPID(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Default value for the CL field in transmitted HIH's.
 *
 * \details 
 * Field: ::VTSS_REW_COMMON_HIH_DEF_CFG . HIH_DEF_CL
 */
#define  VTSS_F_REW_COMMON_HIH_DEF_CFG_HIH_DEF_CL(x)  VTSS_ENCODE_BITFIELD(x,8,16)
#define  VTSS_M_REW_COMMON_HIH_DEF_CFG_HIH_DEF_CL     VTSS_ENCODE_BITMASK(8,16)
#define  VTSS_X_REW_COMMON_HIH_DEF_CFG_HIH_DEF_CL(x)  VTSS_EXTRACT_BITFIELD(x,8,16)

/** 
 * \brief
 * Default value for the FLAGS field in transmitted HIH's.
 *
 * \details 
 * Field: ::VTSS_REW_COMMON_HIH_DEF_CFG . HIH_DEF_FLAGS
 */
#define  VTSS_F_REW_COMMON_HIH_DEF_CFG_HIH_DEF_FLAGS(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_REW_COMMON_HIH_DEF_CFG_HIH_DEF_FLAGS     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_REW_COMMON_HIH_DEF_CFG_HIH_DEF_FLAGS(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Default value for the CKSM field in transmitted HIH's.
 *
 * \details 
 * Field: ::VTSS_REW_COMMON_HIH_DEF_CFG . HIH_DEF_CKSM
 */
#define  VTSS_F_REW_COMMON_HIH_DEF_CFG_HIH_DEF_CKSM(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_REW_COMMON_HIH_DEF_CFG_HIH_DEF_CKSM     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_REW_COMMON_HIH_DEF_CFG_HIH_DEF_CKSM(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief MIP sticky bit register
 *
 * \details
 * Event register common for all MIPs
 *
 * Register: \a REW:COMMON:MIP_STICKY_EVENT
 */
#define VTSS_REW_COMMON_MIP_STICKY_EVENT     VTSS_IOREG(VTSS_TO_REW,0x14f9c)

/** 
 * \brief
 * This bit is set if a CCM CPU is copied to CPU
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_MIP_STICKY_EVENT . MIP_CCM_COPY_STICKY
 */
#define  VTSS_F_REW_COMMON_MIP_STICKY_EVENT_MIP_CCM_COPY_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_COMMON_MIP_STICKY_EVENT_MIP_CCM_COPY_STICKY  VTSS_BIT(6)
#define  VTSS_X_REW_COMMON_MIP_STICKY_EVENT_MIP_CCM_COPY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * This bit is set if a LBM PDU has been redirected to the CPU
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_MIP_STICKY_EVENT . MIP_LBM_REDIR_STICKY
 */
#define  VTSS_F_REW_COMMON_MIP_STICKY_EVENT_MIP_LBM_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_COMMON_MIP_STICKY_EVENT_MIP_LBM_REDIR_STICKY  VTSS_BIT(5)
#define  VTSS_X_REW_COMMON_MIP_STICKY_EVENT_MIP_LBM_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This bit is set if a LTM PDU has been redirected to the CPU
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_MIP_STICKY_EVENT . MIP_LTM_REDIR_STICKY
 */
#define  VTSS_F_REW_COMMON_MIP_STICKY_EVENT_MIP_LTM_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_REW_COMMON_MIP_STICKY_EVENT_MIP_LTM_REDIR_STICKY  VTSS_BIT(4)
#define  VTSS_X_REW_COMMON_MIP_STICKY_EVENT_MIP_LTM_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * This bit is set if a Ring APS PDU has been handled
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_MIP_STICKY_EVENT . MIP_RAPS_STICKY
 */
#define  VTSS_F_REW_COMMON_MIP_STICKY_EVENT_MIP_RAPS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_COMMON_MIP_STICKY_EVENT_MIP_RAPS_STICKY  VTSS_BIT(3)
#define  VTSS_X_REW_COMMON_MIP_STICKY_EVENT_MIP_RAPS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * This bit is set if a Generic PDU has been handled
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_MIP_STICKY_EVENT . MIP_GENERIC_STICKY
 */
#define  VTSS_F_REW_COMMON_MIP_STICKY_EVENT_MIP_GENERIC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_COMMON_MIP_STICKY_EVENT_MIP_GENERIC_STICKY  VTSS_BIT(2)
#define  VTSS_X_REW_COMMON_MIP_STICKY_EVENT_MIP_GENERIC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_REW_COMMON_MIP_STICKY_EVENT . MIP_LBM_DA_CHK_FAIL_STICKY
 */
#define  VTSS_F_REW_COMMON_MIP_STICKY_EVENT_MIP_LBM_DA_CHK_FAIL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_COMMON_MIP_STICKY_EVENT_MIP_LBM_DA_CHK_FAIL_STICKY  VTSS_BIT(1)
#define  VTSS_X_REW_COMMON_MIP_STICKY_EVENT_MIP_LBM_DA_CHK_FAIL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This bit is set if a MEL check has failed for enabled OAM frames
 *
 * \details 
 * 0: No event
 * 1: Event
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_REW_COMMON_MIP_STICKY_EVENT . MIP_MEL_CHK_FAIL_STICKY
 */
#define  VTSS_F_REW_COMMON_MIP_STICKY_EVENT_MIP_MEL_CHK_FAIL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_COMMON_MIP_STICKY_EVENT_MIP_MEL_CHK_FAIL_STICKY  VTSS_BIT(0)
#define  VTSS_X_REW_COMMON_MIP_STICKY_EVENT_MIP_MEL_CHK_FAIL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
 * @param gi Replicator: x_REW_NUM_MAP_TBL_ENTRIES (??), 0-4095
 */
#define VTSS_REW_MAP_RES_A_MAP_VAL_A(gi)     VTSS_IOREG_IX(VTSS_TO_REW,0xc000,gi,2,0,0)

/** 
 * \brief
 * Mapped OAM COLOR value
 *
 * \details 
 * n: New OAM COLOR value
 *
 * Field: ::VTSS_REW_MAP_RES_A_MAP_VAL_A . OAM_COLOR
 */
#define  VTSS_F_REW_MAP_RES_A_MAP_VAL_A_OAM_COLOR(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_MAP_RES_A_MAP_VAL_A_OAM_COLOR  VTSS_BIT(16)
#define  VTSS_X_REW_MAP_RES_A_MAP_VAL_A_OAM_COLOR(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Mapped OAM COSID value
 *
 * \details 
 * n: New OAM COSID value
 *
 * Field: ::VTSS_REW_MAP_RES_A_MAP_VAL_A . OAM_COSID
 */
#define  VTSS_F_REW_MAP_RES_A_MAP_VAL_A_OAM_COSID(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_REW_MAP_RES_A_MAP_VAL_A_OAM_COSID     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_REW_MAP_RES_A_MAP_VAL_A_OAM_COSID(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/** 
 * \brief
 * Mapped TC value
 *
 * \details 
 * n: New TC value
 *
 * Field: ::VTSS_REW_MAP_RES_A_MAP_VAL_A . TC_VAL
 */
#define  VTSS_F_REW_MAP_RES_A_MAP_VAL_A_TC_VAL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_REW_MAP_RES_A_MAP_VAL_A_TC_VAL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_REW_MAP_RES_A_MAP_VAL_A_TC_VAL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Mapped DSCP value
 *
 * \details 
 * n: New DSCP value
 *
 * Field: ::VTSS_REW_MAP_RES_A_MAP_VAL_A . DSCP_VAL
 */
#define  VTSS_F_REW_MAP_RES_A_MAP_VAL_A_DSCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_REW_MAP_RES_A_MAP_VAL_A_DSCP_VAL     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_REW_MAP_RES_A_MAP_VAL_A_DSCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Mapped DEI value
 *
 * \details 
 * n: New DEI value
 *
 * Field: ::VTSS_REW_MAP_RES_A_MAP_VAL_A . DEI_VAL
 */
#define  VTSS_F_REW_MAP_RES_A_MAP_VAL_A_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_MAP_RES_A_MAP_VAL_A_DEI_VAL  VTSS_BIT(3)
#define  VTSS_X_REW_MAP_RES_A_MAP_VAL_A_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Mapped PCP value
 *
 * \details 
 * n: New PCP value
 *
 * Field: ::VTSS_REW_MAP_RES_A_MAP_VAL_A . PCP_VAL
 */
#define  VTSS_F_REW_MAP_RES_A_MAP_VAL_A_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_MAP_RES_A_MAP_VAL_A_PCP_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_MAP_RES_A_MAP_VAL_A_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Configuration of mapping tables 0 and 1. MPLS label
 *
 * \details
 * Lookup 0 and 1 values
 *
 * Register: \a REW:MAP_RES_A:MAP_LBL_A
 *
 * @param gi Replicator: x_REW_NUM_MAP_TBL_ENTRIES (??), 0-4095
 */
#define VTSS_REW_MAP_RES_A_MAP_LBL_A(gi)     VTSS_IOREG_IX(VTSS_TO_REW,0xc000,gi,2,0,1)

/** 
 * \brief
 * Mapped MPLS label value
 *
 * \details 
 * n: Label value
 *
 * Field: ::VTSS_REW_MAP_RES_A_MAP_LBL_A . LABEL_VAL
 */
#define  VTSS_F_REW_MAP_RES_A_MAP_LBL_A_LABEL_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_REW_MAP_RES_A_MAP_LBL_A_LABEL_VAL     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_REW_MAP_RES_A_MAP_LBL_A_LABEL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

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
 * @param gi Replicator: x_REW_NUM_MAP_TBL_ENTRIES (??), 0-4095
 */
#define VTSS_REW_MAP_RES_B_MAP_VAL_B(gi)     VTSS_IOREG_IX(VTSS_TO_REW,0xe000,gi,2,0,0)

/** 
 * \brief
 * Mapped OAM COLOR value
 *
 * \details 
 * n: New OAM COLOR value
 *
 * Field: ::VTSS_REW_MAP_RES_B_MAP_VAL_B . OAM_COLOR
 */
#define  VTSS_F_REW_MAP_RES_B_MAP_VAL_B_OAM_COLOR(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_MAP_RES_B_MAP_VAL_B_OAM_COLOR  VTSS_BIT(16)
#define  VTSS_X_REW_MAP_RES_B_MAP_VAL_B_OAM_COLOR(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Mapped OAM COSID value
 *
 * \details 
 * n: New OAM COSID value
 *
 * Field: ::VTSS_REW_MAP_RES_B_MAP_VAL_B . OAM_COSID
 */
#define  VTSS_F_REW_MAP_RES_B_MAP_VAL_B_OAM_COSID(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_REW_MAP_RES_B_MAP_VAL_B_OAM_COSID     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_REW_MAP_RES_B_MAP_VAL_B_OAM_COSID(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/** 
 * \brief
 * Mapped TC value
 *
 * \details 
 * n: New TC value
 *
 * Field: ::VTSS_REW_MAP_RES_B_MAP_VAL_B . TC_VAL
 */
#define  VTSS_F_REW_MAP_RES_B_MAP_VAL_B_TC_VAL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_REW_MAP_RES_B_MAP_VAL_B_TC_VAL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_REW_MAP_RES_B_MAP_VAL_B_TC_VAL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Mapped DSCP value
 *
 * \details 
 * n: New DSCP value
 *
 * Field: ::VTSS_REW_MAP_RES_B_MAP_VAL_B . DSCP_VAL
 */
#define  VTSS_F_REW_MAP_RES_B_MAP_VAL_B_DSCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_REW_MAP_RES_B_MAP_VAL_B_DSCP_VAL     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_REW_MAP_RES_B_MAP_VAL_B_DSCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Mapped DEI value
 *
 * \details 
 * n: New DEI value
 *
 * Field: ::VTSS_REW_MAP_RES_B_MAP_VAL_B . DEI_VAL
 */
#define  VTSS_F_REW_MAP_RES_B_MAP_VAL_B_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_REW_MAP_RES_B_MAP_VAL_B_DEI_VAL  VTSS_BIT(3)
#define  VTSS_X_REW_MAP_RES_B_MAP_VAL_B_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Mapped PCP value
 *
 * \details 
 * n: New PCP value
 *
 * Field: ::VTSS_REW_MAP_RES_B_MAP_VAL_B . PCP_VAL
 */
#define  VTSS_F_REW_MAP_RES_B_MAP_VAL_B_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_MAP_RES_B_MAP_VAL_B_PCP_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_MAP_RES_B_MAP_VAL_B_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Configuration of mapping tables 2 and 3. MPLS label
 *
 * \details
 * Lookup 2 and 3 values
 *
 * Register: \a REW:MAP_RES_B:MAP_LBL_B
 *
 * @param gi Replicator: x_REW_NUM_MAP_TBL_ENTRIES (??), 0-4095
 */
#define VTSS_REW_MAP_RES_B_MAP_LBL_B(gi)     VTSS_IOREG_IX(VTSS_TO_REW,0xe000,gi,2,0,1)

/** 
 * \brief
 * Mapped MPLS label value
 *
 * \details 
 * n: Label value
 *
 * Field: ::VTSS_REW_MAP_RES_B_MAP_LBL_B . LABEL_VAL
 */
#define  VTSS_F_REW_MAP_RES_B_MAP_LBL_B_LABEL_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_REW_MAP_RES_B_MAP_LBL_B_LABEL_VAL     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_REW_MAP_RES_B_MAP_LBL_B_LABEL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

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
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_PORT_VLAN_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,0)

/** 
 * \brief
 * PCP field in the TCI.
 *
 * \details 
 * n: Port PCP value
 *
 * Field: ::VTSS_REW_PORT_PORT_VLAN_CFG . PORT_PCP
 */
#define  VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_PCP(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_PCP     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_REW_PORT_PORT_VLAN_CFG_PORT_PCP(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/** 
 * \brief
 * DEI field in the TCI.
 *
 * \details 
 * n: Port DEI value
 *
 * Field: ::VTSS_REW_PORT_PORT_VLAN_CFG . PORT_DEI
 */
#define  VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_DEI(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_DEI  VTSS_BIT(12)
#define  VTSS_X_REW_PORT_PORT_VLAN_CFG_PORT_DEI(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * VID field in the TCI.
 *
 * \details 
 * n: Port VID
 *
 * Field: ::VTSS_REW_PORT_PORT_VLAN_CFG . PORT_VID
 */
#define  VTSS_F_REW_PORT_PORT_VLAN_CFG_PORT_VID(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_REW_PORT_PORT_VLAN_CFG_PORT_VID     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_REW_PORT_PORT_VLAN_CFG_PORT_VID(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Map internal priority to tagged priority.
 *
 * \details
 * Register: \a REW:PORT:PCP_MAP_DE0
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 * @param ri Register: PCP_MAP_DE0 (??), 0-7
 */
#define VTSS_REW_PORT_PCP_MAP_DE0(gi,ri)     VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,ri,1)

/** 
 * \brief
 * Map internal priority to UPRIO/PCP value in tags. This table used for DP
 * values mapped to 0 in PORT_DP_MAP.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PCP_MAP_DE0 . PCP_DE0
 */
#define  VTSS_F_REW_PORT_PCP_MAP_DE0_PCP_DE0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_PORT_PCP_MAP_DE0_PCP_DE0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_PORT_PCP_MAP_DE0_PCP_DE0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Map internal priority to tagged priority.
 *
 * \details
 * Register: \a REW:PORT:PCP_MAP_DE1
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 * @param ri Register: PCP_MAP_DE1 (??), 0-7
 */
#define VTSS_REW_PORT_PCP_MAP_DE1(gi,ri)     VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,ri,9)

/** 
 * \brief
 * Map internal priority to UPRIO/PCP value in tags. This table used for DP
 * values mapped to 1 in PORT_DP_MAP.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PCP_MAP_DE1 . PCP_DE1
 */
#define  VTSS_F_REW_PORT_PCP_MAP_DE1_PCP_DE1(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_PORT_PCP_MAP_DE1_PCP_DE1     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_PORT_PCP_MAP_DE1_PCP_DE1(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Map internal priority to tag value.
 *
 * \details
 * Register: \a REW:PORT:DEI_MAP_DE0
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 * @param ri Register: DEI_MAP_DE0 (??), 0-7
 */
#define VTSS_REW_PORT_DEI_MAP_DE0(gi,ri)     VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,ri,17)

/** 
 * \brief
 * Map internal priority to CFI/DEI value in tags. This table used for DP
 * values mapped to 0 in PORT_DP_MAP.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_DEI_MAP_DE0 . DEI_DE0
 */
#define  VTSS_F_REW_PORT_DEI_MAP_DE0_DEI_DE0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_PORT_DEI_MAP_DE0_DEI_DE0  VTSS_BIT(0)
#define  VTSS_X_REW_PORT_DEI_MAP_DE0_DEI_DE0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Map internal priority to tag value.
 *
 * \details
 * Register: \a REW:PORT:DEI_MAP_DE1
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 * @param ri Register: DEI_MAP_DE1 (??), 0-7
 */
#define VTSS_REW_PORT_DEI_MAP_DE1(gi,ri)     VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,ri,25)

/** 
 * \brief
 * Map internal priority to CFI/DEI value in tags. This table used for DP
 * values mapped to 1 in PORT_DP_MAP.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_DEI_MAP_DE1 . DEI_DE1
 */
#define  VTSS_F_REW_PORT_DEI_MAP_DE1_DEI_DE1(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_PORT_DEI_MAP_DE1_DEI_DE1  VTSS_BIT(0)
#define  VTSS_X_REW_PORT_DEI_MAP_DE1_DEI_DE1(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configure PORT tagging
 *
 * \details
 * Register: \a REW:PORT:TAG_CTRL
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_TAG_CTRL(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,33)

/** 
 * \brief
 * Control how port tags are added. If this bit is set, the IFH field
 * VSTAX.TAG.WAS_TAGGED must be '1' before a port tag is added to a frame.
 * 
 * See TAG_CTRL.TAG_CFG
 *
 * \details 
 * 0: Normal port tagging mode
 * 1: Frames are not port tagged, if VSTAX.TAG.WAS_TAGGED = '0' regardless
 * of TAG_CTRL.TAG_CFG configuration

 *
 * Field: ::VTSS_REW_PORT_TAG_CTRL . TAG_CFG_OBEY_WAS_TAGGED
 */
#define  VTSS_F_REW_PORT_TAG_CTRL_TAG_CFG_OBEY_WAS_TAGGED(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_PORT_TAG_CTRL_TAG_CFG_OBEY_WAS_TAGGED  VTSS_BIT(12)
#define  VTSS_X_REW_PORT_TAG_CTRL_TAG_CFG_OBEY_WAS_TAGGED(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Control port tagging.
 * 
 * See TAG_CTRL.TAG_CFG_OBEY_WAS_TAGGED.
 *
 * \details 
 * 0: Port tagging disabled
 * 1: Tag all frames, except when VID=PORT_VLAN_CFG.PORT_VID or VID=0
 * 2: Tag all frames, except when VID=0
 * 3: Tag all frames
 *
 * Field: ::VTSS_REW_PORT_TAG_CTRL . TAG_CFG
 */
#define  VTSS_F_REW_PORT_TAG_CTRL_TAG_CFG(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_REW_PORT_TAG_CTRL_TAG_CFG     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_REW_PORT_TAG_CTRL_TAG_CFG(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

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
 * Field: ::VTSS_REW_PORT_TAG_CTRL . TAG_TPID_CFG
 */
#define  VTSS_F_REW_PORT_TAG_CTRL_TAG_TPID_CFG(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_REW_PORT_TAG_CTRL_TAG_TPID_CFG     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_REW_PORT_TAG_CTRL_TAG_TPID_CFG(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Select VID in port tag
 *
 * \details 
 * Select VID in port tag.
 * 
 * 0: Use classified VID.
 * 1: Use PORT_VLAN_CFG.PORT_VID
 *
 * Field: ::VTSS_REW_PORT_TAG_CTRL . TAG_VID_CFG
 */
#define  VTSS_F_REW_PORT_TAG_CTRL_TAG_VID_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_PORT_TAG_CTRL_TAG_VID_CFG  VTSS_BIT(6)
#define  VTSS_X_REW_PORT_TAG_CTRL_TAG_VID_CFG(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Select PCP fields in port tag
 *
 * \details 
 * Select PCP in port tag.
 * 
 * 0: Classified PCP
 * 1: PORT_PCP
 * 2: DE and QoS mapped to PCP (PCP_MAP_DEx)
 * 3: QoS class
 * 4: DE and COSID mapped to PCP (PCP_MAP_DEx)
 * 5: COSID
 * 6: DE and classified PCP mapped to PCP (PCP_MAP_DEx)
 * 7: Reserved
 *
 * Field: ::VTSS_REW_PORT_TAG_CTRL . TAG_PCP_CFG
 */
#define  VTSS_F_REW_PORT_TAG_CTRL_TAG_PCP_CFG(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_REW_PORT_TAG_CTRL_TAG_PCP_CFG     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_REW_PORT_TAG_CTRL_TAG_PCP_CFG(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Select DEI fields in port tag
 *
 * \details 
 * Select DEI in port tag.
 * 
 * 0: Classified DEI
 * 1: PORT_DEI
 * 2: DE and QoS mapped to DEI (DEI_MAP_DEx)
 * 3: DE level (Color)
 * 4: DE and COSID mapped to DEI (DEI_MAP_DEx)
 * 5: DE and classified PCP mapped to DEI (DEI_MAP_DEx)
 * 6-7: Reserved
 *
 * Field: ::VTSS_REW_PORT_TAG_CTRL . TAG_DEI_CFG
 */
#define  VTSS_F_REW_PORT_TAG_CTRL_TAG_DEI_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_PORT_TAG_CTRL_TAG_DEI_CFG     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_PORT_TAG_CTRL_TAG_DEI_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Enable DSCP updates on the port.
 *
 * \details
 * Register: \a REW:PORT:DSCP_MAP
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_DSCP_MAP(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,34)

/** 
 * \brief
 * Update DSCP with value from Analyzer, if allowed by analyzer.
 * (IFH.QOS.UPDATE_DSCP)
 *
 * \details 
 * 0 : No update
 * 1 : Allow update of DSCP
 *
 * Field: ::VTSS_REW_PORT_DSCP_MAP . DSCP_UPDATE_ENA
 */
#define  VTSS_F_REW_PORT_DSCP_MAP_DSCP_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_PORT_DSCP_MAP_DSCP_UPDATE_ENA  VTSS_BIT(1)
#define  VTSS_X_REW_PORT_DSCP_MAP_DSCP_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable use of a shared DSCP remap table (DSCP_REMAP).
 * 
 * Map DSCP value resulting from DSCP_UPDATE_ENA and IFH.QOS.UPDATE_DSCP
 * using the common mapping table (DSCP_REMAP).
 *
 * \details 
 * 0 : No remapping.
 * 1 : Remap DSCP using DSCP remap table (DSCP_REMAP)
 *
 * Field: ::VTSS_REW_PORT_DSCP_MAP . DSCP_REMAP_ENA
 */
#define  VTSS_F_REW_PORT_DSCP_MAP_DSCP_REMAP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_PORT_DSCP_MAP_DSCP_REMAP_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_PORT_DSCP_MAP_DSCP_REMAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief 1588 configuration
 *
 * \details
 * Selects mode of port when transmitting (index 0), or receiving (index 1)
 *
 * Register: \a REW:PORT:PTP_MODE_CFG
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 * @param ri Register: PTP_MODE_CFG (??), 0-1
 */
#define VTSS_REW_PORT_PTP_MODE_CFG(gi,ri)    VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,ri,35)

/** 
 * \brief
 * PTP operation mode for frames.
 *
 * \details 
 * 0: Front port
 * 1: Backplane port using RSRV field 30 bit TS transfer
 * 2: Backplane port using RSRV field 32 bit TS transfer
 * 3: Backplane port using CF field for 44 bit TS transfer
 * 4: Backplane port using CF field for 48 bit TS transfer
 * 5: Monitor port. Frame updated to arrival stamper.
 * 6: PTP Disabled port
 *
 * Field: ::VTSS_REW_PORT_PTP_MODE_CFG . PTP_MODE_VAL
 */
#define  VTSS_F_REW_PORT_PTP_MODE_CFG_PTP_MODE_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_REW_PORT_PTP_MODE_CFG_PTP_MODE_VAL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_REW_PORT_PTP_MODE_CFG_PTP_MODE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Sets the time domain this port belongs to.

 *
 * \details 
 * Field: ::VTSS_REW_PORT_PTP_MODE_CFG . PTP_DOM_VAL
 */
#define  VTSS_F_REW_PORT_PTP_MODE_CFG_PTP_DOM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_PORT_PTP_MODE_CFG_PTP_DOM_VAL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_PORT_PTP_MODE_CFG_PTP_DOM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_MISC_CFG
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_PTP_MISC_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,37)

/** 
 * \brief
 * Set to skip update of udp checksums for IPv6 frames
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PTP_MISC_CFG . PTP_UDP6_CSUM_DIS
 */
#define  VTSS_F_REW_PORT_PTP_MISC_CFG_PTP_UDP6_CSUM_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_PORT_PTP_MISC_CFG_PTP_UDP6_CSUM_DIS  VTSS_BIT(1)
#define  VTSS_X_REW_PORT_PTP_MISC_CFG_PTP_UDP6_CSUM_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to disable clearing of checksum field in IPv4 frames
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PTP_MISC_CFG . PTP_UDP4_CSUM_DIS
 */
#define  VTSS_F_REW_PORT_PTP_MISC_CFG_PTP_UDP4_CSUM_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_PORT_PTP_MISC_CFG_PTP_UDP4_CSUM_DIS  VTSS_BIT(0)
#define  VTSS_X_REW_PORT_PTP_MISC_CFG_PTP_UDP4_CSUM_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_EDLY_CFG
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_PTP_EDLY_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,38)

/** 
 * \brief
 * Signed value to add to CF when frame is transmitted on this port. Field
 * is used if requested through the analyzer match rule. This value can be
 * used as the egress asymmetry delay for the particular PTP flow.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PTP_EDLY_CFG . PTP_EDLY_VAL
 */
#define  VTSS_F_REW_PORT_PTP_EDLY_CFG_PTP_EDLY_VAL(x)  (x)
#define  VTSS_M_REW_PORT_PTP_EDLY_CFG_PTP_EDLY_VAL     0xffffffff
#define  VTSS_X_REW_PORT_PTP_EDLY_CFG_PTP_EDLY_VAL(x)  (x)


/** 
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_IDLY1_CFG
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_PTP_IDLY1_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,39)

/** 
 * \brief
 * Signed value to add to CF when frame is received on this port. Field is
 * used if requested through the analyzer match rule. This value can be
 * used as the ingress asymmetry or ingress asymmetry+path delay for the
 * particular PTP flow.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PTP_IDLY1_CFG . PTP_IDLY1_VAL
 */
#define  VTSS_F_REW_PORT_PTP_IDLY1_CFG_PTP_IDLY1_VAL(x)  (x)
#define  VTSS_M_REW_PORT_PTP_IDLY1_CFG_PTP_IDLY1_VAL     0xffffffff
#define  VTSS_X_REW_PORT_PTP_IDLY1_CFG_PTP_IDLY1_VAL(x)  (x)


/** 
 * \brief 1588 configuration
 *
 * \details
 * Register: \a REW:PORT:PTP_IDLY2_CFG
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_PTP_IDLY2_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,40)

/** 
 * \brief
 * Signed value to add to CF when frame is received on this port. Field is
 * used if requested through the analyzer match rule. This value can be
 * used as the ingress asymmetry or ingress asymmetry+path delay for the
 * particular PTP flow.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PTP_IDLY2_CFG . PTP_IDLY2_VAL
 */
#define  VTSS_F_REW_PORT_PTP_IDLY2_CFG_PTP_IDLY2_VAL(x)  (x)
#define  VTSS_M_REW_PORT_PTP_IDLY2_CFG_PTP_IDLY2_VAL     0xffffffff
#define  VTSS_X_REW_PORT_PTP_IDLY2_CFG_PTP_IDLY2_VAL(x)  (x)


/** 
 * \brief Low 32 bits of PTP Mac Address
 *
 * \details
 * Register: \a REW:PORT:PTP_SMAC_LOW
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_PTP_SMAC_LOW(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,41)

/** 
 * \brief
 * If requested by the PTP action out of the analyzer, this MAC address can
 * be pasted into the SMAC.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PTP_SMAC_LOW . PTP_SMAC_LOW
 */
#define  VTSS_F_REW_PORT_PTP_SMAC_LOW_PTP_SMAC_LOW(x)  (x)
#define  VTSS_M_REW_PORT_PTP_SMAC_LOW_PTP_SMAC_LOW     0xffffffff
#define  VTSS_X_REW_PORT_PTP_SMAC_LOW_PTP_SMAC_LOW(x)  (x)


/** 
 * \brief High 16 bits of PTP Mac Address
 *
 * \details
 * Register: \a REW:PORT:PTP_SMAC_HIGH
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_PTP_SMAC_HIGH(gi)      VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,42)

/** 
 * \brief
 * If requested by the PTP action out of the analyzer, this MAC address can
 * be pasted into the SMAC.
 *
 * \details 
 * Field: ::VTSS_REW_PORT_PTP_SMAC_HIGH . PTP_SMAC_HIGH
 */
#define  VTSS_F_REW_PORT_PTP_SMAC_HIGH_PTP_SMAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_PORT_PTP_SMAC_HIGH_PTP_SMAC_HIGH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_PORT_PTP_SMAC_HIGH_PTP_SMAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Various Host Mode control
 *
 * \details
 * Register: \a REW:PORT:HIH_CTRL
 *
 * @param gi Replicator: x_REW_FRONT_PORTS_TXM (??), 0-52
 */
#define VTSS_REW_PORT_HIH_CTRL(gi)           VTSS_IOREG_IX(VTSS_TO_REW,0x14000,gi,64,0,43)

/** 
 * \brief
 * Set the format of the Logical Port ID (LPID)
 * 
 * (Value put into the HIH will be determined by HIH_FRM_LPID)
 *
 * \details 
 * 0: Egress port number
 * 1: Ingress port number
 *
 * Field: ::VTSS_REW_PORT_HIH_CTRL . HIH_LPID_MODE
 */
#define  VTSS_F_REW_PORT_HIH_CTRL_HIH_LPID_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_REW_PORT_HIH_CTRL_HIH_LPID_MODE  VTSS_BIT(7)
#define  VTSS_X_REW_PORT_HIH_CTRL_HIH_LPID_MODE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Enables prepending of Host Interface Header (HIH) on the port. The HiH
 * will be placed after the SFD and will be covered by the FCS. 
 * 
 * For 10G ports it is possible to place the HiH before the SFD (in the
 * preamble). See HIH_DEV10G_CFG.HIH_LOCATION

 *
 * \details 
 * 0: Disable HiH functionality
 * 1: Enable HiH insertion
 *
 * Field: ::VTSS_REW_PORT_HIH_CTRL . HIH_ENA
 */
#define  VTSS_F_REW_PORT_HIH_CTRL_HIH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_REW_PORT_HIH_CTRL_HIH_ENA     VTSS_BIT(6)
#define  VTSS_X_REW_PORT_HIH_CTRL_HIH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Configure which value goes into the HIH.LPID field.
 *
 * \details 
 * 0: Set LPID to fixed default value (HIH_DEF_CFG)
 * 1: Set LPID according egress frame (Formatted by HIH_LPID_MODE)

 *
 * Field: ::VTSS_REW_PORT_HIH_CTRL . HIH_FRM_LPID
 */
#define  VTSS_F_REW_PORT_HIH_CTRL_HIH_FRM_LPID(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_REW_PORT_HIH_CTRL_HIH_FRM_LPID  VTSS_BIT(5)
#define  VTSS_X_REW_PORT_HIH_CTRL_HIH_FRM_LPID(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Select source of the HIH.CL field.
 *
 * \details 
 * 0: Always set HIH.CL to fixed default value = HIH_DEF_CL
 * 1: Set HIH.CL to IFH.ENCAP.HIH_CL if IFH.FWD.DST_MODE = ENCAP else 0
 * 2: Set HIH.CL to IFH.VSTAX.MISC.ISDX*4+1 if ISDX>0 else use mode 1
 * 3: Reserved
 *
 * Field: ::VTSS_REW_PORT_HIH_CTRL . HIH_FRM_CL
 */
#define  VTSS_F_REW_PORT_HIH_CTRL_HIH_FRM_CL(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_REW_PORT_HIH_CTRL_HIH_FRM_CL     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_REW_PORT_HIH_CTRL_HIH_FRM_CL(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Select the source of the HIH.FLAGS field.
 *
 * \details 
 * 0: Set HIH.FLAGS to fixed default value = HIH_DEF_FLAGS
 * 1: Set HIH.FLAGS to frame IPRIO and COLOR bits.
 * 2: Set HIH.FLAGS to frame COSID and COLOR bits.
 * 3: Reserved
 *
 * Field: ::VTSS_REW_PORT_HIH_CTRL . HIH_FRM_FLAGS
 */
#define  VTSS_F_REW_PORT_HIH_CTRL_HIH_FRM_FLAGS(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_REW_PORT_HIH_CTRL_HIH_FRM_FLAGS     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_REW_PORT_HIH_CTRL_HIH_FRM_FLAGS(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Select the source of the HIH.CKSM field.
 *
 * \details 
 * 0: Set HIH.CKSM to fixed default value (HIH_DEF_CKSM)
 * 1: Calculate HIH.CKSM according to HIH contents.
 *
 * Field: ::VTSS_REW_PORT_HIH_CTRL . HIH_AUTO_CKSM
 */
#define  VTSS_F_REW_PORT_HIH_CTRL_HIH_AUTO_CKSM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_PORT_HIH_CTRL_HIH_AUTO_CKSM  VTSS_BIT(0)
#define  VTSS_X_REW_PORT_HIH_CTRL_HIH_AUTO_CKSM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
 * @param gi Replicator: x_REW_NUM_MIP_TBL_ENTRIES (??), 0-1023
 */
#define VTSS_REW_MIP_TBL_MIP_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_REW,0x10000,gi,8,0,0)

/** 
 * \brief
 * MEL value for the MIP.
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . MEL_VAL
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_MEL_VAL(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_MEL_VAL     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_MEL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * If set, OAM Y.1731 CCM frames with the correct encapsulation and the
 * correct MEL are copied to the CPU.
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . CCM_COPY_ENA
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_CCM_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_CCM_COPY_ENA  VTSS_BIT(18)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_CCM_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * If set, OAM Y.1731 LBM frames with the correct encapsulation, the
 * correct MEL, and the correct destination MAC address are redirected to
 * the CPU.

 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . LBM_REDIR_ENA
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_LBM_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_LBM_REDIR_ENA  VTSS_BIT(17)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_LBM_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * If set, OAM Y.1731 LTM frames with the correct encapsulation and the
 * correct MEL are redirected to the CPU.
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . LTM_REDIR_ENA
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_LTM_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_LTM_REDIR_ENA  VTSS_BIT(16)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_LTM_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

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
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . RAPS_CFG
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_RAPS_CFG(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_RAPS_CFG     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_RAPS_CFG(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Generic Opcode. See GENERIC_OPCODE_CFG.
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . GENERIC_OPCODE_VAL
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_GENERIC_OPCODE_VAL(x)  VTSS_ENCODE_BITFIELD(x,6,8)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_GENERIC_OPCODE_VAL     VTSS_ENCODE_BITMASK(6,8)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_GENERIC_OPCODE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,6,8)

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
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . GENERIC_OPCODE_CFG
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_GENERIC_OPCODE_CFG(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_GENERIC_OPCODE_CFG     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_GENERIC_OPCODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * CPU extraction queue when frame is forwarded to CPU.
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . CPU_MIP_QU
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_CPU_MIP_QU(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_CPU_MIP_QU     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_CPU_MIP_QU(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * MIP location. This influences in particular the update of loss
 * measurement statistics for MEPs.
 *
 * \details 
 * 0: REW_IN_MIP
 * 1: REW_OU_MIP
 *
 * Field: ::VTSS_REW_MIP_TBL_MIP_CFG . PIPELINE_PT
 */
#define  VTSS_F_REW_MIP_TBL_MIP_CFG_PIPELINE_PT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_MIP_TBL_MIP_CFG_PIPELINE_PT  VTSS_BIT(0)
#define  VTSS_X_REW_MIP_TBL_MIP_CFG_PIPELINE_PT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Allows sending a single CCM frame to CPU
 *
 * \details
 * Register: \a REW:MIP_TBL:CCM_HMO_CTRL
 *
 * @param gi Replicator: x_REW_NUM_MIP_TBL_ENTRIES (??), 0-1023
 */
#define VTSS_REW_MIP_TBL_CCM_HMO_CTRL(gi)    VTSS_IOREG_IX(VTSS_TO_REW,0x10000,gi,8,0,1)

/** 
 * \brief
 * Interval used for automatically setting CCM_COPY_ONCE_ENA based on
 * REW::MIP_CTRL.MIP_CCM_HMO_SET_SHOT
 * 
 * CCM_COPY_ONCE_ENA are only set by hardware if
 * MIP_CCM_INTERVAL_MASK[CCM_HMO_CTRL.CCM_INTERVAL] is set
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_CCM_HMO_CTRL . CCM_INTERVAL
 */
#define  VTSS_F_REW_MIP_TBL_CCM_HMO_CTRL_CCM_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_REW_MIP_TBL_CCM_HMO_CTRL_CCM_INTERVAL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_REW_MIP_TBL_CCM_HMO_CTRL_CCM_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Send the next received CCM frame to CPU. Cleared by HW when a CPU copy
 * has been send to CPU
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_CCM_HMO_CTRL . CCM_COPY_ONCE_ENA
 */
#define  VTSS_F_REW_MIP_TBL_CCM_HMO_CTRL_CCM_COPY_ONCE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_MIP_TBL_CCM_HMO_CTRL_CCM_COPY_ONCE_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_MIP_TBL_CCM_HMO_CTRL_CCM_COPY_ONCE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Controls classified VID check
 *
 * \details
 * Register: \a REW:MIP_TBL:MIP_VID_CTRL
 *
 * @param gi Replicator: x_REW_NUM_MIP_TBL_ENTRIES (??), 0-1023
 */
#define VTSS_REW_MIP_TBL_MIP_VID_CTRL(gi)    VTSS_IOREG_IX(VTSS_TO_REW,0x10000,gi,8,0,2)

/** 
 * \brief
 * Required outer VID to identify frame as MIP.
 *
 * \details 
 * n: Outer VID value
 *
 * Field: ::VTSS_REW_MIP_TBL_MIP_VID_CTRL . VID_VAL
 */
#define  VTSS_F_REW_MIP_TBL_MIP_VID_CTRL_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,12)
#define  VTSS_M_REW_MIP_TBL_MIP_VID_CTRL_VID_VAL     VTSS_ENCODE_BITMASK(2,12)
#define  VTSS_X_REW_MIP_TBL_MIP_VID_CTRL_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,12)

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
 * Field: ::VTSS_REW_MIP_TBL_MIP_VID_CTRL . VID_SEL
 */
#define  VTSS_F_REW_MIP_TBL_MIP_VID_CTRL_VID_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_MIP_TBL_MIP_VID_CTRL_VID_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_MIP_TBL_MIP_VID_CTRL_VID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief MAC address - bits 47:32
 *
 * \details
 * Register: \a REW:MIP_TBL:LBM_MAC_HIGH
 *
 * @param gi Replicator: x_REW_NUM_MIP_TBL_ENTRIES (??), 0-1023
 */
#define VTSS_REW_MIP_TBL_LBM_MAC_HIGH(gi)    VTSS_IOREG_IX(VTSS_TO_REW,0x10000,gi,8,0,3)

/** 
 * \brief
 * Destination MAC address bits 47:32 used for LBM. If LBM_MAC_HIGH = 0 and
 * LBM_MAC_LOW = 0, the MAC address check for LBM frames is disabled.
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_LBM_MAC_HIGH . LBM_MAC_HIGH
 */
#define  VTSS_F_REW_MIP_TBL_LBM_MAC_HIGH_LBM_MAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_MIP_TBL_LBM_MAC_HIGH_LBM_MAC_HIGH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_MIP_TBL_LBM_MAC_HIGH_LBM_MAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MAC address configuration - bits 31:0
 *
 * \details
 * Register: \a REW:MIP_TBL:LBM_MAC_LOW
 *
 * @param gi Replicator: x_REW_NUM_MIP_TBL_ENTRIES (??), 0-1023
 */
#define VTSS_REW_MIP_TBL_LBM_MAC_LOW(gi)     VTSS_IOREG_IX(VTSS_TO_REW,0x10000,gi,8,0,4)

/** 
 * \brief
 * Destination MAC address bit 31:0 used for LBM. See LBM_MAC_HIGH.
 *
 * \details 
 * Field: ::VTSS_REW_MIP_TBL_LBM_MAC_LOW . LBM_MAC_LOW
 */
#define  VTSS_F_REW_MIP_TBL_LBM_MAC_LOW_LBM_MAC_LOW(x)  (x)
#define  VTSS_M_REW_MIP_TBL_LBM_MAC_LOW_LBM_MAC_LOW     0xffffffff
#define  VTSS_X_REW_MIP_TBL_LBM_MAC_LOW_LBM_MAC_LOW(x)  (x)

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
 * @param gi Replicator: x_REW_NUM_ISDX_TBL_NUMBERS (??), 0-4095
 * @param ri Register: COS_CTRL (??), 0-2
 */
#define VTSS_REW_ISDX_TBL_COS_CTRL(gi,ri)    VTSS_IOREG_IX(VTSS_TO_REW,0x8000,gi,4,ri,0)

/** 
 * \brief
 * The auto updated COSID value is determined according to the following
 * algorithm:
 * 
 * mask = IFH.TS.INJ_LBK.COS_MASK[7:0]
 * isdx = IFH.VSTAX.MISC.ISDX
 * cos_nxt_sel = IFH.TS.INJ_LBK.COS_NXT_SEL
 * if (cos_nxt_sel > 0 and isdx > 0 and mask > 0) {
 *   cos_nxt =
 * REW:ISDX_TBL:COS_CTRL[IFH.VSTAX.MISC.ISDX].COS_NXT[cos_nxt_sel-1]
 * 
 *   # Use cos_nxt to find next bit in cos_mask     
 *   for idx in 0:7 {
 *     if (mask[(idx+cos_nxt) mod 8] = '1') {
 *	 cosid_new = idx
 *	 break
 *     }
 *   }
 *   # Update next pointer
 *   REW:ISDX_TBL:COS_CTRL[IFH.VSTAX.MISC.ISDX].COS_NXT[cos_nxt_sel-1] =
 * ((cosid_new+1) mod 8)
 * }

 *
 * \details 
 * 0-7: Next COS value to use
 *
 * Field: ::VTSS_REW_ISDX_TBL_COS_CTRL . COS_NXT
 */
#define  VTSS_F_REW_ISDX_TBL_COS_CTRL_COS_NXT(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_REW_ISDX_TBL_COS_CTRL_COS_NXT     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_REW_ISDX_TBL_COS_CTRL_COS_NXT(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a REW:PTP_CTRL
 *
 * PTP Control
 */


/** 
 * \brief Configuration register for PTP stamping
 *
 * \details
 * Register: \a REW:PTP_CTRL:PTP_TWOSTEP_CTRL
 */
#define VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL   VTSS_IOREG(VTSS_TO_REW,0x14d42)

/** 
 * \brief
 * If the fifo is overflown, additional stamps will overwrite older.
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL . PTP_OVWR_ENA
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVWR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVWR_ENA  VTSS_BIT(12)
#define  VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVWR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Write one to advance the stamp queue to the next available.
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL . PTP_NXT
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT  VTSS_BIT(11)
#define  VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * The stamp queue is non empty
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL . PTP_VLD
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_VLD  VTSS_BIT(10)
#define  VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_VLD(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Current stamp is an egress stamp
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL . STAMP_TX
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_TX  VTSS_BIT(9)
#define  VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_TX(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Field contains the port number the stamp was made on
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL . STAMP_PORT
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_PORT(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_PORT     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_PORT(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * The stamp is overflown, and some stamps are lost.
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL . PTP_OVFL
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVFL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVFL  VTSS_BIT(0)
#define  VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVFL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Ingress time stamp
 *
 * \details
 * Register: \a REW:PTP_CTRL:PTP_TWOSTEP_STAMP
 */
#define VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP  VTSS_IOREG(VTSS_TO_REW,0x14d43)

/** 
 * \brief
 * Contains the 32 bit timestamp.
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP . STAMP_NSEC
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_STAMP_STAMP_NSEC(x)  (x)
#define  VTSS_M_REW_PTP_CTRL_PTP_TWOSTEP_STAMP_STAMP_NSEC     0xffffffff
#define  VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_STAMP_STAMP_NSEC(x)  (x)


/** 
 * \brief 1588 configuration
 *
 * \details
 * Selects ingress PTP mode of the CPU and virtual device ports.
 * Replication n configures port 53+n.
 *
 * Register: \a REW:PTP_CTRL:PTP_CPUVD_MODE_CFG
 *
 * @param ri Register: PTP_CPUVD_MODE_CFG (??), 0-3
 */
#define VTSS_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG(ri)  VTSS_IOREG(VTSS_TO_REW,0x14d44 + (ri))

/** 
 * \brief
 * PTP operation mode for frames.
 *
 * \details 
 * 0: Front port
 * 1: Backplane port using RSRV field 30 bit TS transfer
 * 2: Backplane port using RSRV field 32 bit TS transfer
 * 3: Backplane port using CF field for 44 bit TS transfer
 * 4: Backplane port using CF field for 48 bit TS transfer
 * 5: Monitor port. Frame updated to arrival stamper.
 * 6: PTP Disabled port
 *
 * Field: ::VTSS_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG . PTP_MODE_VAL
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG_PTP_MODE_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG_PTP_MODE_VAL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG_PTP_MODE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Sets the time domain this port belongs to.

 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG . PTP_DOM_VAL
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG_PTP_DOM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG_PTP_DOM_VAL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_PTP_CTRL_PTP_CPUVD_MODE_CFG_PTP_DOM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief PTP reserved field check
 *
 * \details
 * Register: \a REW:PTP_CTRL:PTP_RSRV_NOT_ZERO
 */
#define VTSS_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO  VTSS_IOREG(VTSS_TO_REW,0x14d48)

/** 
 * \brief
 * Register contains one bit per port being set when the port has received
 * a frame with non-zero reserved bytes field
 * 
 * This register covers ports 0-31
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO . PTP_RSRV_NOT_ZERO
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO_PTP_RSRV_NOT_ZERO(x)  (x)
#define  VTSS_M_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO_PTP_RSRV_NOT_ZERO     0xffffffff
#define  VTSS_X_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO_PTP_RSRV_NOT_ZERO(x)  (x)


/** 
 * \brief PTP reserved field check
 *
 * \details
 * Register: \a REW:PTP_CTRL:PTP_RSRV_NOT_ZERO_1
 */
#define VTSS_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO_1  VTSS_IOREG(VTSS_TO_REW,0x14d49)

/** 
 * \brief
 * This register covers ports 32-56. See PTP_RSRV_NOT_ZERO for description.
 *
 * \details 
 * Field: ::VTSS_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO_1 . PTP_RSRV_NOT_ZERO_1
 */
#define  VTSS_F_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO_1_PTP_RSRV_NOT_ZERO_1(x)  VTSS_ENCODE_BITFIELD(x,0,25)
#define  VTSS_M_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO_1_PTP_RSRV_NOT_ZERO_1     VTSS_ENCODE_BITMASK(0,25)
#define  VTSS_X_REW_PTP_CTRL_PTP_RSRV_NOT_ZERO_1_PTP_RSRV_NOT_ZERO_1(x)  VTSS_EXTRACT_BITFIELD(x,0,25)

/**
 * Register Group: \a REW:ENCAP
 *
 * Encapsulation RAM configuration
 */


/** 
 * \brief Configure DMAC of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_DMAC_MSB
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_LL_DMAC_MSB(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,0)

/** 
 * \brief
 * DMAC in Link layer. 16 MSB
 *
 * \details 
 * n: DMAC MSB
 *
 * Field: ::VTSS_REW_ENCAP_LL_DMAC_MSB . DMAC_MSB
 */
#define  VTSS_F_REW_ENCAP_LL_DMAC_MSB_DMAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_ENCAP_LL_DMAC_MSB_DMAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_ENCAP_LL_DMAC_MSB_DMAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Configure DMAC of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_DMAC_LSB
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_LL_DMAC_LSB(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,1)

/** 
 * \brief
 * DMAC in Link layer. 32 LSB
 *
 * \details 
 * n: DMAC LSB
 *
 * Field: ::VTSS_REW_ENCAP_LL_DMAC_LSB . DMAC_LSB
 */
#define  VTSS_F_REW_ENCAP_LL_DMAC_LSB_DMAC_LSB(x)  (x)
#define  VTSS_M_REW_ENCAP_LL_DMAC_LSB_DMAC_LSB     0xffffffff
#define  VTSS_X_REW_ENCAP_LL_DMAC_LSB_DMAC_LSB(x)  (x)


/** 
 * \brief Configure SMAC of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_SMAC_MSB
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_LL_SMAC_MSB(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,2)

/** 
 * \brief
 * SMAC in Link layer. 16 MSB
 *
 * \details 
 * n: SMAC MSB
 *
 * Field: ::VTSS_REW_ENCAP_LL_SMAC_MSB . SMAC_MSB
 */
#define  VTSS_F_REW_ENCAP_LL_SMAC_MSB_SMAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_ENCAP_LL_SMAC_MSB_SMAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_ENCAP_LL_SMAC_MSB_SMAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Configure SMAC of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_SMAC_LSB
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_LL_SMAC_LSB(gi)       VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,3)

/** 
 * \brief
 * SMAC in Link layer. 32 LSB
 *
 * \details 
 * n: SMAC LSB
 *
 * Field: ::VTSS_REW_ENCAP_LL_SMAC_LSB . SMAC_LSB
 */
#define  VTSS_F_REW_ENCAP_LL_SMAC_LSB_SMAC_LSB(x)  (x)
#define  VTSS_M_REW_ENCAP_LL_SMAC_LSB_SMAC_LSB     0xffffffff
#define  VTSS_X_REW_ENCAP_LL_SMAC_LSB_SMAC_LSB(x)  (x)


/** 
 * \brief Configure ETYPE of MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_ETYPE
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_LL_ETYPE(gi)          VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,4)

/** 
 * \brief
 * Ethertype in Link layer
 *
 * \details 
 * n: Ethertype
 *
 * Field: ::VTSS_REW_ENCAP_LL_ETYPE . ETYPE
 */
#define  VTSS_F_REW_ENCAP_LL_ETYPE_ETYPE(x)   VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_ENCAP_LL_ETYPE_ETYPE      VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_ENCAP_LL_ETYPE_ETYPE(x)   VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Configure MPLS label
 *
 * \details
 * Register: \a REW:ENCAP:MPLS_LABEL_CFG
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_MPLS_LABEL_CFG(gi)    VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,5)

/** 
 * \brief
 * Configure the number of MPLS labels to use for this encapsulation entry
 *
 * \details 
 * 0: No Labels in encapsulation
 * 1: One MPLS label 
 * 2: Two MPLS labels
 * 3: Three MPLS labels

 *
 * Field: ::VTSS_REW_ENCAP_MPLS_LABEL_CFG . LABEL_CNT
 */
#define  VTSS_F_REW_ENCAP_MPLS_LABEL_CFG_LABEL_CNT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_REW_ENCAP_MPLS_LABEL_CFG_LABEL_CNT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_REW_ENCAP_MPLS_LABEL_CFG_LABEL_CNT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Configure Control Word (CW) in label stack
 *
 * \details 
 * 0: No Control Word
 * 1: Add Control Word

 *
 * Field: ::VTSS_REW_ENCAP_MPLS_LABEL_CFG . CW_ENA
 */
#define  VTSS_F_REW_ENCAP_MPLS_LABEL_CFG_CW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_ENCAP_MPLS_LABEL_CFG_CW_ENA  VTSS_BIT(1)
#define  VTSS_X_REW_ENCAP_MPLS_LABEL_CFG_CW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Select innermost label. Source can be ES0 or encapsulation RAM
 *
 * \details 
 * 0: Use label from encapsulation table
 * 1: Use label from ES0

 *
 * Field: ::VTSS_REW_ENCAP_MPLS_LABEL_CFG . INNER_LBL_SEL
 */
#define  VTSS_F_REW_ENCAP_MPLS_LABEL_CFG_INNER_LBL_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_ENCAP_MPLS_LABEL_CFG_INNER_LBL_SEL  VTSS_BIT(0)
#define  VTSS_X_REW_ENCAP_MPLS_LABEL_CFG_INNER_LBL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configure MPLS label
 *
 * \details
 * Register: \a REW:ENCAP:RSV_LABEL_CFG
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_RSV_LABEL_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,6)

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
 * Field: ::VTSS_REW_ENCAP_RSV_LABEL_CFG . RSV_TC_SEL
 */
#define  VTSS_F_REW_ENCAP_RSV_LABEL_CFG_RSV_TC_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_REW_ENCAP_RSV_LABEL_CFG_RSV_TC_SEL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_REW_ENCAP_RSV_LABEL_CFG_RSV_TC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Select position of the reserved label. It can be added before or after
 * the last MPLS label
 *
 * \details 
 * 0: Add before last label
 * 1: Add after last label like the CW

 *
 * Field: ::VTSS_REW_ENCAP_RSV_LABEL_CFG . RSV_LBL_POS
 */
#define  VTSS_F_REW_ENCAP_RSV_LABEL_CFG_RSV_LBL_POS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_ENCAP_RSV_LABEL_CFG_RSV_LBL_POS  VTSS_BIT(1)
#define  VTSS_X_REW_ENCAP_RSV_LABEL_CFG_RSV_LBL_POS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable reserved MPLS label insertion for MPLS-OAM frames. 
 * 
 * When this bit is set, an additional MPLS label is inserted if CW
 * insertion is disabled and IFH.DST.ENCAP.PDU_TYPE=OAM_MPLS_TP or
 * IFH.DST.ENCAP.PDU_TYPE=Y1731 and IFH.DST.ENCAP.TYPE_AFTER_POP=CW
 * 
 * Note: The reserved label can only be inserted if a CW is not inserted
 * for the frame.

 *
 * \details 
 * 0: Disabled
 * 1: Add reserved label if allowed

 *
 * Field: ::VTSS_REW_ENCAP_RSV_LABEL_CFG . RSV_LBL_ENA
 */
#define  VTSS_F_REW_ENCAP_RSV_LABEL_CFG_RSV_LBL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_ENCAP_RSV_LABEL_CFG_RSV_LBL_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_ENCAP_RSV_LABEL_CFG_RSV_LBL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief MPLS label stack Control Word
 *
 * \details
 * Register: \a REW:ENCAP:CW_VAL
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_CW_VAL(gi)            VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,7)

/** 
 * \brief
 * Control Word value. The control word is always placed after the last
 * MPLS label.
 *
 * \details 
 * x: Control Word

 *
 * Field: ::VTSS_REW_ENCAP_CW_VAL . CW_VAL
 */
#define  VTSS_F_REW_ENCAP_CW_VAL_CW_VAL(x)    (x)
#define  VTSS_M_REW_ENCAP_CW_VAL_CW_VAL       0xffffffff
#define  VTSS_X_REW_ENCAP_CW_VAL_CW_VAL(x)    (x)


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
 * 
 * The register MPLS_LABEL_CFG.LABEL_CNT controls the number of labels.
 *
 * Register: \a REW:ENCAP:LABEL_VAL
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 * @param ri Register: LABEL_VAL (??), 0-2
 */
#define VTSS_REW_ENCAP_LABEL_VAL(gi,ri)      VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,ri,8)

/** 
 * \brief
 * Label field value in MPLS  label N
 *
 * \details 
 * x: Label field value

 *
 * Field: ::VTSS_REW_ENCAP_LABEL_VAL . LABEL_VAL
 */
#define  VTSS_F_REW_ENCAP_LABEL_VAL_LABEL_VAL(x)  VTSS_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_REW_ENCAP_LABEL_VAL_LABEL_VAL     VTSS_ENCODE_BITMASK(12,20)
#define  VTSS_X_REW_ENCAP_LABEL_VAL_LABEL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,12,20)

/** 
 * \brief
 * TC value in MPLS label N
 *
 * \details 
 * x: TC field value

 *
 * Field: ::VTSS_REW_ENCAP_LABEL_VAL . TC_VAL
 */
#define  VTSS_F_REW_ENCAP_LABEL_VAL_TC_VAL(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_REW_ENCAP_LABEL_VAL_TC_VAL     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_REW_ENCAP_LABEL_VAL_TC_VAL(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * SBIT value in MPLS label N
 *
 * \details 
 * x: SBIT field value

 *
 * Field: ::VTSS_REW_ENCAP_LABEL_VAL . SBIT_VAL
 */
#define  VTSS_F_REW_ENCAP_LABEL_VAL_SBIT_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_REW_ENCAP_LABEL_VAL_SBIT_VAL  VTSS_BIT(8)
#define  VTSS_X_REW_ENCAP_LABEL_VAL_SBIT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * TTL value in MPLS label N
 *
 * \details 
 * x: TTL field value

 *
 * Field: ::VTSS_REW_ENCAP_LABEL_VAL . TTL_VAL
 */
#define  VTSS_F_REW_ENCAP_LABEL_VAL_TTL_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_ENCAP_LABEL_VAL_TTL_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_ENCAP_LABEL_VAL_TTL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Reserved label field values
 *
 * \details
 * This register contains the reserved MPLS label fields. The reserved
 * label can only be added if the control word (CW) is not enabled.

 *
 * Register: \a REW:ENCAP:RSV_LABEL_VAL
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_RSV_LABEL_VAL(gi)     VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,11)

/** 
 * \brief
 * Label field value in the reserved MPLS label
 *
 * \details 
 * x: Label field value

 *
 * Field: ::VTSS_REW_ENCAP_RSV_LABEL_VAL . RSV_LBL_VAL
 */
#define  VTSS_F_REW_ENCAP_RSV_LABEL_VAL_RSV_LBL_VAL(x)  VTSS_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_REW_ENCAP_RSV_LABEL_VAL_RSV_LBL_VAL     VTSS_ENCODE_BITMASK(12,20)
#define  VTSS_X_REW_ENCAP_RSV_LABEL_VAL_RSV_LBL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,12,20)

/** 
 * \brief
 * TC value in reserved the MPLS label
 *
 * \details 
 * x: TC field value

 *
 * Field: ::VTSS_REW_ENCAP_RSV_LABEL_VAL . RSV_TC_VAL
 */
#define  VTSS_F_REW_ENCAP_RSV_LABEL_VAL_RSV_TC_VAL(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_REW_ENCAP_RSV_LABEL_VAL_RSV_TC_VAL     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_REW_ENCAP_RSV_LABEL_VAL_RSV_TC_VAL(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * SBIT value in reserved the MPLS label
 *
 * \details 
 * x: SBIT field value

 *
 * Field: ::VTSS_REW_ENCAP_RSV_LABEL_VAL . RSV_SBIT_VAL
 */
#define  VTSS_F_REW_ENCAP_RSV_LABEL_VAL_RSV_SBIT_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_REW_ENCAP_RSV_LABEL_VAL_RSV_SBIT_VAL  VTSS_BIT(8)
#define  VTSS_X_REW_ENCAP_RSV_LABEL_VAL_RSV_SBIT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * TTL value in reserved the MPLS label
 *
 * \details 
 * x: TTL field value

 *
 * Field: ::VTSS_REW_ENCAP_RSV_LABEL_VAL . RSV_TTL_VAL
 */
#define  VTSS_F_REW_ENCAP_RSV_LABEL_VAL_RSV_TTL_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_ENCAP_RSV_LABEL_VAL_RSV_TTL_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_ENCAP_RSV_LABEL_VAL_RSV_TTL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


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
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 * @param ri Register: MPLS_REMARK_CFG (??), 0-2
 */
#define VTSS_REW_ENCAP_MPLS_REMARK_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,ri,12)

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
 * Field: ::VTSS_REW_ENCAP_MPLS_REMARK_CFG . LBL_SEL
 */
#define  VTSS_F_REW_ENCAP_MPLS_REMARK_CFG_LBL_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_REW_ENCAP_MPLS_REMARK_CFG_LBL_SEL     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_REW_ENCAP_MPLS_REMARK_CFG_LBL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

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
 * Field: ::VTSS_REW_ENCAP_MPLS_REMARK_CFG . TC_SEL
 */
#define  VTSS_F_REW_ENCAP_MPLS_REMARK_CFG_TC_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_REW_ENCAP_MPLS_REMARK_CFG_TC_SEL     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_REW_ENCAP_MPLS_REMARK_CFG_TC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

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
 * Field: ::VTSS_REW_ENCAP_MPLS_REMARK_CFG . SBIT_SEL
 */
#define  VTSS_F_REW_ENCAP_MPLS_REMARK_CFG_SBIT_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_REW_ENCAP_MPLS_REMARK_CFG_SBIT_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_REW_ENCAP_MPLS_REMARK_CFG_SBIT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

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
 * Field: ::VTSS_REW_ENCAP_MPLS_REMARK_CFG . TTL_SEL
 */
#define  VTSS_F_REW_ENCAP_MPLS_REMARK_CFG_TTL_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_ENCAP_MPLS_REMARK_CFG_TTL_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_ENCAP_MPLS_REMARK_CFG_TTL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Configure VLAN tags in MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_TAG_CFG
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 */
#define VTSS_REW_ENCAP_LL_TAG_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,0,15)

/** 
 * \brief
 * Enable IFH encapsulation mode for this entry.
 * 
 * The frame link layer format is changed to:
 * [LL_DMAC][LL_SMAC][0x8880][0x0009]
 * 
 * Optionally one VLAN tag can be added if LL_TAG_CFG.TAG_CFG = 1
 * [LL_DMAC][LL_SMAC][LL_TAG:0][0x8880][0x0009]
 * 
 * None of the other encapsulation fields are used in this mode

 *
 * \details 
 * 0: Normal encapsulation mode
 * 1: IFH encapsulation mode

 *
 * Field: ::VTSS_REW_ENCAP_LL_TAG_CFG . IFH_ENCAP_MODE
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_CFG_IFH_ENCAP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_REW_ENCAP_LL_TAG_CFG_IFH_ENCAP_MODE  VTSS_BIT(2)
#define  VTSS_X_REW_ENCAP_LL_TAG_CFG_IFH_ENCAP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_REW_ENCAP_LL_TAG_CFG . TAG_CFG
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_CFG_TAG_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_ENCAP_LL_TAG_CFG_TAG_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_ENCAP_LL_TAG_CFG_TAG_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief MPLS label stack Control Word
 *
 * \details
 * This register contains the VLAN tags
 *
 * Register: \a REW:ENCAP:LL_TAG_VAL
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 * @param ri Register: LL_TAG_VAL (??), 0-1
 */
#define VTSS_REW_ENCAP_LL_TAG_VAL(gi,ri)     VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,ri,16)

/** 
 * \brief
 * TPID of link layer VLAN tags
 *
 * \details 
 * x: TPID value

 *
 * Field: ::VTSS_REW_ENCAP_LL_TAG_VAL . TAG_TPID
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_VAL_TAG_TPID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_REW_ENCAP_LL_TAG_VAL_TAG_TPID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_REW_ENCAP_LL_TAG_VAL_TAG_TPID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * VID value in link layer tags
 *
 * \details 
 * x: VID value

 *
 * Field: ::VTSS_REW_ENCAP_LL_TAG_VAL . TAG_VID_VAL
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_VAL_TAG_VID_VAL(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_REW_ENCAP_LL_TAG_VAL_TAG_VID_VAL     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_REW_ENCAP_LL_TAG_VAL_TAG_VID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/** 
 * \brief
 * PCP value in link layer tags
 *
 * \details 
 * x: PCP value

 *
 * Field: ::VTSS_REW_ENCAP_LL_TAG_VAL . TAG_PCP_VAL
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_VAL_TAG_PCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_REW_ENCAP_LL_TAG_VAL_TAG_PCP_VAL     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_REW_ENCAP_LL_TAG_VAL_TAG_PCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * DEI value in link layer tags
 *
 * \details 
 * x: DEI value

 *
 * Field: ::VTSS_REW_ENCAP_LL_TAG_VAL . TAG_DEI_VAL
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_VAL_TAG_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_ENCAP_LL_TAG_VAL_TAG_DEI_VAL  VTSS_BIT(0)
#define  VTSS_X_REW_ENCAP_LL_TAG_VAL_TAG_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configure remarking of VLAN tags in MPLS link layer
 *
 * \details
 * Register: \a REW:ENCAP:LL_TAG_REMARK_CFG
 *
 * @param gi Replicator: x_REW_NUM_ENCAP_ENTRIES (??), 0-1023
 * @param ri Register: LL_TAG_REMARK_CFG (??), 0-1
 */
#define VTSS_REW_ENCAP_LL_TAG_REMARK_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_REW,0x0,gi,32,ri,18)

/** 
 * \brief
 * Selects VID for MPLS encapsulation tag
 * Idx0:  TAG_A, Idx1:	TAG_B

 *
 * \details 
 * 0: Classified VID + TAG_VID_VAL:n
 * 1: TAG_VID_VAL:n
 *
 * Field: ::VTSS_REW_ENCAP_LL_TAG_REMARK_CFG . TAG_VID_SEL
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_VID_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_VID_SEL  VTSS_BIT(7)
#define  VTSS_X_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_VID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Selects PCP for MPLS encapsulation tag
 * Idx0:  TAG_A, Idx1:	TAG_B

 *
 * \details 
 * 0: Classified PCP 
 * 1: Encapsulation TAG_PCP_VAL:n
 * 2-3: Reserved
 * 4: Mapped using mapping table 0, otherwise use LL_TAG_VAL[N].TAG_PCP_VAL
 * 5: Mapped using mapping table 1, otherwise use mapping table 0
 * 6: Mapped using mapping table 2, otherwise use LL_TAG_VAL[N].TAG_PCP_VAL
 * 7: Mapped using mapping table 3, otherwise use mapping table 2
 *
 * Field: ::VTSS_REW_ENCAP_LL_TAG_REMARK_CFG . TAG_PCP_SEL
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_PCP_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_PCP_SEL     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_PCP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Selects DEI for MPLS encapsulation tag
 * Idx0:  TAG_A, Idx1:	TAG_B

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
 * Field: ::VTSS_REW_ENCAP_LL_TAG_REMARK_CFG . TAG_DEI_SEL
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_DEI_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_DEI_SEL     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_DEI_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * Selects TPID for MPLS encapsulation tag
 * Idx0:  TAG_A, Idx1:	TAG_B
 *
 * \details 
 * 0: Encapsulation LL_TAG_VAL[N].TAG_TPID
 * 1: Classified.  ANA controls via IFH:
 * If ifh.encap.tag_tipd = STD_TPID: 
 *   If ifh.vstax.tag_type = 0 then 0x8100 else LL_TAG_VAL[N].TAG_TPID
 * if ifh.encap.tag_tipd > 0: 
 *   Custom TPID 1 to 3 configured by  REW::TPID_CFG[N].TPID_VAL
 *
 * Field: ::VTSS_REW_ENCAP_LL_TAG_REMARK_CFG . TAG_TPID_SEL
 */
#define  VTSS_F_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_TPID_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_TPID_SEL  VTSS_BIT(0)
#define  VTSS_X_REW_ENCAP_LL_TAG_REMARK_CFG_TAG_TPID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
 * @param gi Replicator: x_REW_NUM_VMID (??), 0-127
 */
#define VTSS_REW_VMID_RLEG_CTRL(gi)          VTSS_IOREG_IX(VTSS_TO_REW,0x14d80,gi,1,0,0)

/** 
 * \brief
 * Control the value of VSTAX.TAG.WAS_TAGGED field in the stack header for
 * frames that are L3 forwarded to a stack port.

 *
 * \details 
 * 0: VSTAX.TAG.WAS_TAGGED = 0
 * 1: VSTAX.TAG.WAS_TAGGED = 1
 *
 * Field: ::VTSS_REW_VMID_RLEG_CTRL . RLEG_VSTAX2_WAS_TAGGED
 */
#define  VTSS_F_REW_VMID_RLEG_CTRL_RLEG_VSTAX2_WAS_TAGGED(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_REW_VMID_RLEG_CTRL_RLEG_VSTAX2_WAS_TAGGED  VTSS_BIT(12)
#define  VTSS_X_REW_VMID_RLEG_CTRL_RLEG_VSTAX2_WAS_TAGGED(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * VID for egress router leg.
 * 
 * This must be configured consistently in ANA_L3:VMID:RLEG_CTRL.RLEG_EVID.
 *
 * \details 
 * n: VID
 *
 * Field: ::VTSS_REW_VMID_RLEG_CTRL . RLEG_EVID
 */
#define  VTSS_F_REW_VMID_RLEG_CTRL_RLEG_EVID(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_REW_VMID_RLEG_CTRL_RLEG_EVID     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_REW_VMID_RLEG_CTRL_RLEG_EVID(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

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
 * @param ri Replicator: x_REW_NUM_PTP_SEQ_NUMBERS (??), 0-255
 */
#define VTSS_REW_PTP_SEQ_NO_PTP_SEQ_NO(ri)   VTSS_IOREG(VTSS_TO_REW,0x14e00 + (ri))

/** 
 * \brief
 * Sequence number for the flow given by the timestamp field in IFH.
 * Sequence number will automatically increase at each transmission
 * referring to the sequence entry.
 *
 * \details 
 * Field: ::VTSS_REW_PTP_SEQ_NO_PTP_SEQ_NO . PTP_SEQ_NO
 */
#define  VTSS_F_REW_PTP_SEQ_NO_PTP_SEQ_NO_PTP_SEQ_NO(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_PTP_SEQ_NO_PTP_SEQ_NO_PTP_SEQ_NO     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_PTP_SEQ_NO_PTP_SEQ_NO_PTP_SEQ_NO(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * @param gi Replicator: x_NUM_VOE_x_NUM_PRIO (??), 0-8191
 */
#define VTSS_REW_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x12000,gi,1,0,0)

/** 
 * \details 
 * Field: ::VTSS_REW_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB . SRV_LM_CNT_LSB
 */
#define  VTSS_F_REW_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB(x)  (x)

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
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-423
 */
#define VTSS_REW_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15000,gi,4,0,0)

/** 
 * \brief
 * See Register Description.
 *
 * \details 
 * Field: ::VTSS_REW_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB . PORT_LM_CNT_LSB
 */
#define  VTSS_F_REW_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB(x)  (x)


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
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-423
 */
#define VTSS_REW_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15000,gi,4,0,1)

/** 
 * \brief
 * See Register Description.
 *
 * \details 
 * Field: ::VTSS_REW_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB . PORT_FRM_CNT_LSB
 */
#define  VTSS_F_REW_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB(x)  (x)


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
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-423
 */
#define VTSS_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15000,gi,4,0,2)

/** 
 * \brief
 * See Register Description.
 *
 * \details 
 * Field: ::VTSS_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB . PORT_BYTE_CNT_MSB
 */
#define  VTSS_F_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


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
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-423
 */
#define VTSS_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15000,gi,4,0,3)

/** 
 * \brief
 * See Register Description.
 *
 * \details 
 * Field: ::VTSS_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB . PORT_BYTE_CNT_LSB
 */
#define  VTSS_F_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB(x)  (x)
#define  VTSS_M_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB     0xffffffff
#define  VTSS_X_REW_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB(x)  (x)

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
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-105
 */
#define VTSS_REW_OAM_PDU_MOD_CONT_TEMP_CNT_REG(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15800,gi,8,0,0)

/** 
 * \details 
 * Field: ::VTSS_REW_OAM_PDU_MOD_CONT_TEMP_CNT_REG . TEMP_CNT_VAL
 */
#define  VTSS_F_REW_OAM_PDU_MOD_CONT_TEMP_CNT_REG_TEMP_CNT_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_REW_OAM_PDU_MOD_CONT_TEMP_CNT_REG_TEMP_CNT_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_REW_OAM_PDU_MOD_CONT_TEMP_CNT_REG_TEMP_CNT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Temp LM cnt
 *
 * \details
 * Register: \a REW:OAM_PDU_MOD_CONT:LM_CNT_FRAME
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-105
 */
#define VTSS_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15800,gi,8,0,1)

/** 
 * \brief
 * Determines if the current frame should be counted by the Service LM
 * counter, based on the color / mapping and possibly being killed in the
 * ingress DLB.
 *
 * \details 
 * Field: ::VTSS_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME . SRV_CNT_FRM
 */
#define  VTSS_F_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME_SRV_CNT_FRM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME_SRV_CNT_FRM  VTSS_BIT(1)
#define  VTSS_X_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME_SRV_CNT_FRM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Determines if the current frame should be counted by the Path LM
 * counter, based on the color / mapping and possibly being killed in the
 * ingress DLB.
 *
 * \details 
 * Field: ::VTSS_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME . PATH_CNT_FRM
 */
#define  VTSS_F_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME_PATH_CNT_FRM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME_PATH_CNT_FRM  VTSS_BIT(0)
#define  VTSS_X_REW_OAM_PDU_MOD_CONT_LM_CNT_FRAME_PATH_CNT_FRM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Temp CCM-LM info
 *
 * \details
 * Register: \a REW:OAM_PDU_MOD_CONT:CCM_LM_INFO_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-105
 */
#define VTSS_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15800,gi,8,0,2)

/** 
 * \brief
 * Indicates whether this entry in the RAM contains valid CCM-LM sample
 * values.
 *
 * \details 
 * Field: ::VTSS_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG . CCM_LM_INFO_VLD
 */
#define  VTSS_F_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_INFO_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_INFO_VLD  VTSS_BIT(11)
#define  VTSS_X_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_INFO_VLD(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * The number of the VOE for which the LM information was received.
 *
 * \details 
 * Field: ::VTSS_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG . CCM_LM_VOE_IDX
 */
#define  VTSS_F_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_VOE_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_VOE_IDX     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_REW_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_VOE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief CCM-LM sample
 *
 * \details
 * Contains the sampled value of CCM_LM.tx_fc_b from the last valid CCM_LM
 * frame.
 *
 * Register: \a REW:OAM_PDU_MOD_CONT:CCM_LM_TX_B_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-105
 */
#define VTSS_REW_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15800,gi,8,0,3)

/** 
 * \brief
 * Contains the sampled value of CCM_LM.tx_fc_b from the last valid CCM_LM
 * frame.
 *
 * \details 
 * Field: ::VTSS_REW_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG . CCM_LM_TX_B
 */
#define  VTSS_F_REW_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG_CCM_LM_TX_B(x)  (x)
#define  VTSS_M_REW_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG_CCM_LM_TX_B     0xffffffff
#define  VTSS_X_REW_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG_CCM_LM_TX_B(x)  (x)


/** 
 * \brief CCM-LM sample
 *
 * \details
 * Contains the sampled value of CCM_LM.rx_fc_b from the last valid CCM_LM
 * frame.
 *
 * Register: \a REW:OAM_PDU_MOD_CONT:CCM_LM_RX_B_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-105
 */
#define VTSS_REW_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG(gi)  VTSS_IOREG_IX(VTSS_TO_REW,0x15800,gi,8,0,4)

/** 
 * \brief
 * Contains the sampled value of CCM_LM.rx_fc_b from the last valid CCM_LM
 * frame.
 *
 * \details 
 * Field: ::VTSS_REW_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG . CCM_LM_RX_B
 */
#define  VTSS_F_REW_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG_CCM_LM_RX_B(x)  (x)
#define  VTSS_M_REW_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG_CCM_LM_RX_B     0xffffffff
#define  VTSS_X_REW_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG_CCM_LM_RX_B(x)  (x)

/**
 * Register Group: \a REW:PDU_MOD_CFG
 *
 * OAM_PDU_MOD misc. configuration
 */


/** 
 * \brief Port PTP domain select
 *
 * \details
 * Jaguar2-R supports three PTP time domains.
 * 
 * The Delay Measurements (Y.1731) uses the PTP timing for updating the DM
 * PDUs.
 * 
 * For this to work, each port on the switch must be configured for which
 * PTP timedomain to use.
 * 
 * This is done by configuring this register.
 * 
 * The settings must be the same in the REW and the ANA_AC instatiation of
 * the OAM_PDU_MOD block.
 *
 * Register: \a REW:PDU_MOD_CFG:DM_PTP_DOMAIN_CFG
 *
 * @param ri Replicator: x_NUM_FRONT_PORTS (??), 0-52
 */
#define VTSS_REW_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG(ri)  VTSS_IOREG(VTSS_TO_REW,0x14f9d + (ri))

/** 
 * \details 
 * Field: ::VTSS_REW_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG . PTP_DOMAIN
 */
#define  VTSS_F_REW_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG_PTP_DOMAIN(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_REW_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG_PTP_DOMAIN     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_REW_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG_PTP_DOMAIN(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define VTSS_REW_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB  VTSS_IOREG(VTSS_TO_REW,0x14fd2)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_REW_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB . RD_LAST_PORT_LM_CNT_LSB
 */
#define  VTSS_F_REW_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB(x)  (x)


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
#define VTSS_REW_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB  VTSS_IOREG(VTSS_TO_REW,0x14fd3)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_REW_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB . RD_LAST_PORT_FRM_CNT_LSB
 */
#define  VTSS_F_REW_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB(x)  (x)
#define  VTSS_M_REW_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB     0xffffffff
#define  VTSS_X_REW_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB(x)  (x)


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
#define VTSS_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB  VTSS_IOREG(VTSS_TO_REW,0x14fd4)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB . RD_LAST_PORT_BYTE_CNT_MSB
 */
#define  VTSS_F_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


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
#define VTSS_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB  VTSS_IOREG(VTSS_TO_REW,0x14fd5)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB . RD_LAST_PORT_BYTE_CNT_LSB
 */
#define  VTSS_F_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB(x)  (x)
#define  VTSS_M_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB     0xffffffff
#define  VTSS_X_REW_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB(x)  (x)

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
#define VTSS_REW_RAM_CTRL_RAM_INIT           VTSS_IOREG(VTSS_TO_REW,0x14d4a)

/** 
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete ( approx. 40 us).
 *
 * \details 
 * Field: ::VTSS_REW_RAM_CTRL_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_REW_RAM_CTRL_RAM_INIT_RAM_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_REW_RAM_CTRL_RAM_INIT_RAM_INIT  VTSS_BIT(1)
#define  VTSS_X_REW_RAM_CTRL_RAM_INIT_RAM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Core memory controllers are enabled when this field is set.
 *
 * \details 
 * Field: ::VTSS_REW_RAM_CTRL_RAM_INIT . RAM_ENA
 */
#define  VTSS_F_REW_RAM_CTRL_RAM_INIT_RAM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_REW_RAM_CTRL_RAM_INIT_RAM_ENA  VTSS_BIT(0)
#define  VTSS_X_REW_RAM_CTRL_RAM_INIT_RAM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
#define VTSS_REW_COREMEM_CM_ADDR             VTSS_IOREG(VTSS_TO_REW,0x14d40)

/** 
 * \brief
 * Refer to cmid.xls in the AS1000, misc_docs folder.
 *
 * \details 
 * Field: ::VTSS_REW_COREMEM_CM_ADDR . CM_ID
 */
#define  VTSS_F_REW_COREMEM_CM_ADDR_CM_ID(x)  VTSS_ENCODE_BITFIELD(x,22,8)
#define  VTSS_M_REW_COREMEM_CM_ADDR_CM_ID     VTSS_ENCODE_BITMASK(22,8)
#define  VTSS_X_REW_COREMEM_CM_ADDR_CM_ID(x)  VTSS_EXTRACT_BITFIELD(x,22,8)

/** 
 * \brief
 * Address selection within selected core memory (CMID register). Address
 * is automatically advanced at every data access.
 *
 * \details 
 * Field: ::VTSS_REW_COREMEM_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_REW_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_REW_COREMEM_CM_ADDR_CM_ADDR     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_REW_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,22)


/** 
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a REW:COREMEM:CM_DATA
 */
#define VTSS_REW_COREMEM_CM_DATA             VTSS_IOREG(VTSS_TO_REW,0x14d41)

/** 
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 BIT inspection space.
 *
 * \details 
 * Field: ::VTSS_REW_COREMEM_CM_DATA . CM_DATA
 */
#define  VTSS_F_REW_COREMEM_CM_DATA_CM_DATA(x)  (x)
#define  VTSS_M_REW_COREMEM_CM_DATA_CM_DATA     0xffffffff
#define  VTSS_X_REW_COREMEM_CM_DATA_CM_DATA(x)  (x)


#endif /* _VTSS_JAGUAR2C_REGS_REW_H_ */
