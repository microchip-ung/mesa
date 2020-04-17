// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_VOP_MPLS_H_
#define _VTSS_FA_REGS_VOP_MPLS_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a VOP_MPLS
 *
 * The Versatile OAM MEP Processor (VOP) implements the HW support for
 * implementing OAM MEPs.
 * 
 * The HW support for implementing an OAM MEP is implemented in a sub
 * block, referred to as:
 * Versatile OAM Endpoint (VOE).
 * 
 * The VOEs can be configured for either Y.1731, MPLS-TP, or L3 OAM PDU
 * processing.
 * 
 * The VOP includes the following:
 * 
 *  * 1024 Service / Path VOEs
 *  * 65 Port VOEs
 * 
 * The VOEs can be configured for either Y.1731, MPLS-TP, or L3 OAM PDU
 * processing using the following register:
 *  * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.VOE_ENA
 * 
 * To configure VOEs configured for Y.1731, use CSR target VOP.
 * To configure VOEs configured for MPLS-TP, use CSR target VOP_MPLS.
 * To configure VOEs configured for L3 OAM, use CSR target VOP_L3.
 * 
 * For VOEs not configured for MPLS-TP, the register groups in this target
 * are invalid.
 * 
 * Note that the VOP_MPLS CSR target shares the same physical RAM as the
 * VOP CSR target. The RAM is initialized to the VOP CSR target values
 * (Y.1731 VOE).
 * Hence the initial values listed in the VOP_MPLS are not valid.
 * Prior to using a VOE configured for MPLS-TP, all registers must be
 * initialized.
 *
 ***********************************************************************/

/**
 * Register Group: \a VOP_MPLS:VOE_CONF_MPLS
 *
 * Configuration per Versatile OAM MEP Endpoint (VOE) for MPLS-TP OAM
 */


/** 
 * \brief VOE configuration common between VOE types
 *
 * \details
 * This register is identical in VOE_CONF, VOE_CONF_MPLS, and VOE_CONF_L3.
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:VOE_COMMON_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_VOE_COMMON_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,0)

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
 * Field: ::VTSS_VOP_MPLS_VOE_COMMON_CFG . UPMEP_ENA
 */
#define  VTSS_F_VOP_MPLS_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_MPLS_VOE_COMMON_CFG_UPMEP_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_MPLS_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

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
 * Field: ::VTSS_VOP_MPLS_VOE_COMMON_CFG . VOE_IS_PATH
 */
#define  VTSS_F_VOP_MPLS_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_MPLS_VOE_COMMON_CFG_VOE_IS_PATH  VTSS_BIT(12)
#define  VTSS_X_VOP_MPLS_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

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
 * Field: ::VTSS_VOP_MPLS_VOE_COMMON_CFG . PATH_VOE_ENA
 */
#define  VTSS_F_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Assigns a Path VOE to the VOE. See description in PATH_VOE_ENA.Must
 * point to a VOE in the pool of Service VOEs (0 - 1023).
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_VOE_COMMON_CFG . PATH_VOEID
 */
#define  VTSS_F_VOP_MPLS_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_ENCODE_BITFIELD(x,1,10)
#define  VTSS_M_VOP_MPLS_VOE_COMMON_CFG_PATH_VOEID     VTSS_ENCODE_BITMASK(1,10)
#define  VTSS_X_VOP_MPLS_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_EXTRACT_BITFIELD(x,1,10)

/** 
 * \brief
 * If ESDX counter control is enabled, the VOP will signal disabling of
 * ESDX counting to the REW for OAM frames.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_VOE_COMMON_CFG . ESDX_CNT_CTRL_ENA
 */
#define  VTSS_F_VOP_MPLS_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CPU extraction for the supported MPLS-TP OAM G-ACH Channel Types.
 *
 * \details
 * Configures CPU copy for the supported MPLS-TP PDU G-ACH Channel Types.
 * 
 * Configuring a PDU type for CPU extraction, will result in all valid OAM
 * PDUs of this type to extracted to the CPU.
 * 
 * The PDU will be extracted to the extraction queue configured for the
 * G-ACH Channel Type in the following registers:
 * 
 *  * VOP::CPU_EXTR_MPLS.*
 * 
 * Invalid OAM PDUs are not extracted based on the configuration in this
 * register group. OAM PDUs are considered invalid if they fail either of
 * the following checks:
 * 
 *  * Protocol Specific verification (E.g. BFD Rx / Tx verification)
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:CPU_COPY_CTRL_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_CPU_COPY_CTRL_MPLS(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,1)

/** 
 * \brief
 * This bit field contains 8 bits each of which represent one of the
 * Generic G-ACH Channel Types.If the bit representing a specific Generic
 * G-ACH Channel Type is asserted, all valid PDUs received by the VOE of
 * that type are extracted to the CPU queue configured in the following bit
 * fields: * VOP::MPLS_GENERIC_CODEPOINT.GENERIC_CODEPOINT_CPU_QU
 *
 * \details 
 * x0x: No CPU copy
 * x1x: Copy to CPU
 *
 * Field: ::VTSS_VOP_MPLS_CPU_COPY_CTRL_MPLS . GENERIC_COPY_MASK
 */
#define  VTSS_F_VOP_MPLS_CPU_COPY_CTRL_MPLS_GENERIC_COPY_MASK(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_VOP_MPLS_CPU_COPY_CTRL_MPLS_GENERIC_COPY_MASK     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_VOP_MPLS_CPU_COPY_CTRL_MPLS_GENERIC_COPY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/** 
 * \brief
 * Configures whether MPLS-TP OAM PDUs with UNKNOWN G-ACH Channel Type
 * should be extracted to the CPU.Extracted frames are extracted to the
 * default CPU queue, configured in: * VOP::CPU_EXTR_CFG.DEF_COPY_QU
 *
 * \details 
 * '0': No CPU copy
 * '1': Copy to CPU
 *
 * Field: ::VTSS_VOP_MPLS_CPU_COPY_CTRL_MPLS . UNK_CPT_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_MPLS_CPU_COPY_CTRL_MPLS_UNK_CPT_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MPLS_CPU_COPY_CTRL_MPLS_UNK_CPT_CPU_COPY_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_MPLS_CPU_COPY_CTRL_MPLS_UNK_CPT_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * If asserted all valid BFD CC PDUs received by the VOE are extracted to
 * the CPU.Extraction queue is determined by:  *
 * VOP::CPU_EXTR_MPLS.BFD_CC_CPU_QU
 *
 * \details 
 * '0': No extraction to CPU
 * '1': Extract valid BFD CC PDUs to CPU
 *
 * Field: ::VTSS_VOP_MPLS_CPU_COPY_CTRL_MPLS . BFD_CC_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_MPLS_CPU_COPY_CTRL_MPLS_BFD_CC_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_CPU_COPY_CTRL_MPLS_BFD_CC_CPU_COPY_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_CPU_COPY_CTRL_MPLS_BFD_CC_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * If asserted all valid BFD CV PDUs received by the VOE are extracted to
 * the CPU.Extraction queue is determined by:  *
 * VOP::CPU_EXTR_MPLS.BFD_CV_CPU_QU
 *
 * \details 
 * '0': No extraction to CPU
 * '1': Extract valid BFD CV frames to CPU
 *
 * Field: ::VTSS_VOP_MPLS_CPU_COPY_CTRL_MPLS . BFD_CV_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_MPLS_CPU_COPY_CTRL_MPLS_BFD_CV_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_CPU_COPY_CTRL_MPLS_BFD_CV_CPU_COPY_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_CPU_COPY_CTRL_MPLS_BFD_CV_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief OAM HW processing control
 *
 * \details
 * Configures per MPLS-TP G-ACH Channel Type if it is processed by VOE
 * hardware.
 * 
 * If an MPLS-TP OAM type is not enabled in this register, the OAM PDU will
 * not be modified by the VOE.
 * 
 * This implies that the OAM PDU is not updated.
 * 
 * However, note the following:
 *  * The Rx sticky bits will be set for a PDU, even when the HW processing
 * is not enabled.
 *  * OAM PDU can be extracted to the CPU, even when HW processing is not
 * enabled.
 *  * LM counters will be updated.
 *  * SEL / non SEL counters are updated.
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:OAM_HW_CTRL_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_OAM_HW_CTRL_MPLS(gi)   VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,2)

/** 
 * \brief
 * Enable HW processing of valid BFD CC PDUs received by the VOE in both
 * the Tx and the Rx direction.If this is disabled, no verification of the
 * YourDiscriminator is done of the incoming BFD CC PDUs. All Rx PDUs will
 * be processed as belonging to the Coordinated Mode.I.e. a BFD CC PDUs
 * will never be processed as belonging to the FEIS Session.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_OAM_HW_CTRL_MPLS . BFD_CC_ENA
 */
#define  VTSS_F_VOP_MPLS_OAM_HW_CTRL_MPLS_BFD_CC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_OAM_HW_CTRL_MPLS_BFD_CC_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_OAM_HW_CTRL_MPLS_BFD_CC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable HW processing of valid BFD CV PDUs received by the VOE in both
 * the Tx and the Rx direction.If this is disabled, no verification of the
 * YourDiscriminator is done of the incoming BFD CV PDUs. All Rx PDUs will
 * be processed as belonging to the Coordinated Mode.I.e. a BFD CV PDUs
 * will never be processed as belonging to the FEIS Session.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_OAM_HW_CTRL_MPLS . BFD_CV_ENA
 */
#define  VTSS_F_VOP_MPLS_OAM_HW_CTRL_MPLS_BFD_CV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_OAM_HW_CTRL_MPLS_BFD_CV_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_OAM_HW_CTRL_MPLS_BFD_CV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration which MPLS-TP Channel Types are counted in selected PDU counter.
 *
 * \details
 * The OAM frames processed by the VOE can be counted separately in Rx and
 * Tx direction.
 * In each direction there are two counters:
 * 
 * 1) Selected OAM counter:
 * --------------------------------------------------------
 * This counter counts all the PDU types selected for counting using the
 * OAM_CNT_SEL_MPLS register:
 * 
 *  * VOP_MPLS:VOE_STAT_MPLS:RX_CNT_SEL_OAM_MPLS
 *  * VOP_MPLS:VOE_STAT_MPLS:TX_CNT_SEL_OAM_MPLS
 * 
 * 2) NON Selected OAM counter:
 * --------------------------------------------------------
 *  * VOP_MPLS:VOE_STAT_MPLS:RX_CNT_NON_SEL_OAM_MPLS
 *  * VOP_MPLS:VOE_STAT_MPLS:TX_CNT_NON_SEL_OAM_MPLS
 * 
 * Any valid OAM PDU is counted in exactly one of the above registers.
 * 
 * I.e. as default all OAM PDUs are not selected, and they are all counted
 * in the default OAM counters: RX / TX_CNT_NON_SEL_OAM_MPLS.
 * 
 * Using this register (OAM_CNT_SEL_MPLS), PDUs can be moved to the
 * selected counters:
 * RX / TX_CNT_SEL_OAM_MPLS.
 * 
 * The selection of OAM PDUs for the selected counter is done commonly for
 * the Tx and Rx direction.
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:OAM_CNT_SEL_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_OAM_CNT_SEL_MPLS(gi)   VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,3)

/** 
 * \brief
 * Enable / disable that valid OAM PDUs with Generic G-ACH Channel Type are
 * counted as selected OAM.This bit field contains a separate bit for each
 * of the possible 8 Generic opcodes.
 *
 * \details 
 * x0x: Count as other OAM
 * x1x: Count as selected OAM
 *
 * Field: ::VTSS_VOP_MPLS_OAM_CNT_SEL_MPLS . GENERIC_CPT_CNT_SEL_MASK
 */
#define  VTSS_F_VOP_MPLS_OAM_CNT_SEL_MPLS_GENERIC_CPT_CNT_SEL_MASK(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_VOP_MPLS_OAM_CNT_SEL_MPLS_GENERIC_CPT_CNT_SEL_MASK     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_VOP_MPLS_OAM_CNT_SEL_MPLS_GENERIC_CPT_CNT_SEL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/** 
 * \brief
 * MPLS-TP OAM PDUs not recognized as either one of the PDUs with special
 * configuration or as a Generic G-ACH Channel Type, will be classified as
 * an UNKNOWN PDU.This register configures whether UNKNOWN PDUs should be
 * counted as selected OAM.
 *
 * \details 
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_MPLS_OAM_CNT_SEL_MPLS . UNK_CPT_CNT_SEL_ENA
 */
#define  VTSS_F_VOP_MPLS_OAM_CNT_SEL_MPLS_UNK_CPT_CNT_SEL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MPLS_OAM_CNT_SEL_MPLS_UNK_CPT_CNT_SEL_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_MPLS_OAM_CNT_SEL_MPLS_UNK_CPT_CNT_SEL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This register configures whether valid BFD CC PDUs are counted Selected
 * OAM or NON Selected OAM.
 *
 * \details 
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_MPLS_OAM_CNT_SEL_MPLS . BFD_CC_CNT_SEL_ENA
 */
#define  VTSS_F_VOP_MPLS_OAM_CNT_SEL_MPLS_BFD_CC_CNT_SEL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_OAM_CNT_SEL_MPLS_BFD_CC_CNT_SEL_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_OAM_CNT_SEL_MPLS_BFD_CC_CNT_SEL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This register configures whether valid BFD CV PDUs are counted Selected
 * OAM or NON Selected OAM.
 *
 * \details 
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_MPLS_OAM_CNT_SEL_MPLS . BFD_CV_CNT_SEL_ENA
 */
#define  VTSS_F_VOP_MPLS_OAM_CNT_SEL_MPLS_BFD_CV_CNT_SEL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_OAM_CNT_SEL_MPLS_BFD_CV_CNT_SEL_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_OAM_CNT_SEL_MPLS_BFD_CV_CNT_SEL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of which OAM PDUs should be counted by LM counters.
 *
 * \details
 * Default behavior is that all MPLS-TP OAM PDUs processed by a VOE will
 * not be counted as part of the LM count. 
 * 
 * Using this register (OAM_CNT_DATA_MPLS) it is possible to configure the
 * OAM PDUs separately to be counted as part of the LM count.
 * 
 * Frames are counted separately in the Rx and Tx direction.
 * 
 * The data counters are located:
 * 
 * Service VOE:
 * ---------------------
 * Egress: REW:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB.SRV_LM_CNT_LSB
 * Ingress: ANA_AC_OAM_MOD:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB.SRV_LM_CNT_LSB
 * 
 * Port VOE:
 * -------------------
 * Egress: REW:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSB
 * Ingress: ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSB

 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:OAM_CNT_DATA_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_OAM_CNT_DATA_MPLS(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,4)

/** 
 * \brief
 * Enable / disable that valid MPLS-TP OAM PDUs with Generic G-ACH Channel
 * Type are counted by the VOE LM counters.This bit field contains a
 * separate bit for each of the possible 8 Generic G-ACH Channel Types.
 *
 * \details 
 * x0x: Do NOT count generic Channel Type in LM counters.
 * x1x: DO count generic Channel Type in LM counters.
 *
 * Field: ::VTSS_VOP_MPLS_OAM_CNT_DATA_MPLS . GENERIC_CPT_CNT_DATA_MASK
 */
#define  VTSS_F_VOP_MPLS_OAM_CNT_DATA_MPLS_GENERIC_CPT_CNT_DATA_MASK(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_VOP_MPLS_OAM_CNT_DATA_MPLS_GENERIC_CPT_CNT_DATA_MASK     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_VOP_MPLS_OAM_CNT_DATA_MPLS_GENERIC_CPT_CNT_DATA_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/** 
 * \brief
 * If a PDU is received with an G-ACH Channel Type which does not match any
 * Specific G-ACH Channel Type or a Generic G-ACH Channel Type, it will be
 * processed as an UNKNOWN G-ACH Channel Type.This bit field configures if
 * OAM frames with UNKNOWN G-ACH Channel Type are counted as data in the LM
 * counters.
 *
 * \details 
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_MPLS_OAM_CNT_DATA_MPLS . UNK_CPT_CNT_DATA_ENA
 */
#define  VTSS_F_VOP_MPLS_OAM_CNT_DATA_MPLS_UNK_CPT_CNT_DATA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MPLS_OAM_CNT_DATA_MPLS_UNK_CPT_CNT_DATA_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_MPLS_OAM_CNT_DATA_MPLS_UNK_CPT_CNT_DATA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable / disable count of valid BFD CC OAM PDUs as part of the LM
 * counters.
 *
 * \details 
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_MPLS_OAM_CNT_DATA_MPLS . BFD_CC_CNT_DATA_ENA
 */
#define  VTSS_F_VOP_MPLS_OAM_CNT_DATA_MPLS_BFD_CC_CNT_DATA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_OAM_CNT_DATA_MPLS_BFD_CC_CNT_DATA_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_OAM_CNT_DATA_MPLS_BFD_CC_CNT_DATA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable / disable count of valid BFD CV OAM PDUs as part of the LM
 * counters.
 *
 * \details 
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_MPLS_OAM_CNT_DATA_MPLS . BFD_CV_CNT_DATA_ENA
 */
#define  VTSS_F_VOP_MPLS_OAM_CNT_DATA_MPLS_BFD_CV_CNT_DATA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_OAM_CNT_DATA_MPLS_BFD_CV_CNT_DATA_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_OAM_CNT_DATA_MPLS_BFD_CV_CNT_DATA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief MPLS-TP BFD configuration.
 *
 * \details
 * This register contains misc. bit fields used to figure the BFD session
 * monitored by the VOE.
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_CONFIG(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,5)

/** 
 * \brief
 * If set, VOE is dedicated to processing IP BFD CC frames.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . IP_BFD_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_IP_BFD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_IP_BFD_ENA  VTSS_BIT(23)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_IP_BFD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * The VOE can accept two different G-ACH Channel Types as being valid BFD
 * CC PDUs, depending of the setting of this register.If the VOE receives a
 * MPLS-TP with the G-ACH Channel Type which is not the one configured for
 * BFD CC, the PDU will be classified as either Generic or Unknown G-ACH
 * Channel Type.I.e. if BFD_CC_RFC6428 = 1, MPLS-TP PDUs with G-ACH Channel
 * Type = 0x0007 will be classified as either Generic or UNKNOWN G-ACH
 * Channel Type.
 *
 * \details 
 * The pending on configuration of this bit field, the VOE will expect the
 * following G-ACH Channel Type for BFD CC PDUs:
 * 
 * 0: 0x0007 (RFC_5885)
 * 1: 0x0022 (RFC_6428)
 *
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_CC_RFC6428
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_CC_RFC6428(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_CC_RFC6428  VTSS_BIT(22)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_CC_RFC6428(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * The configuration of this bit field specifies the LOC timeout counter to
 * be used for LOC scan for this VOE.Every time the LOC timeout counter
 * indicated by this register causes a scan, the VOE LOC counter is
 * incremented.The LOC counter is cleared upon reception of a valid BFD
 * CC/CV PDU.The LOC counter is located in the following bit field: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_STAT.BFD_MISS_CNT
 *
 * \details 
 * 0: Indicates that the LOC counter is not incremented.
 * 1: Indicates that the LOC counter is incremented by LOC timeout counter
 * 0
 * 2: Indicates that the LOC counter is incremented by LOC timeout counter
 * 1
 * 3: Indicates that the LOC counter is incremented by LOC timeout counter
 * 2
 * 4: Indicates that the LOC counter is incremented by LOC timeout counter
 * 3
 * 5: Indicates that the LOC counter is incremented by LOC timeout counter
 * 4
 * 6: Indicates that the LOC counter is incremented by LOC timeout counter
 * 5
 * 7: Indicates that the LOC counter is incremented by LOC timeout counter
 * 6
 *
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_SCAN_PERIOD
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_SCAN_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_SCAN_PERIOD     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_SCAN_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * If enabled the VOE will update the following registers based on the
 * information received in valid BFD CC PDUs:Coordinated / NEIS: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SRC_INFO.BFD_REMOTE_STATE_SRC *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SRC_INFO.BFD_REMOTE_DIAG_SRC *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SRC_INFO.BFD_REMOTE_DM_SRCFEIS session: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SINK_INFO.BFD_REMOTE_STATE_SINK *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SINK_INFO.BFD_REMOTE_DIAG_SINK *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SINK_INFO.BFD_REMOTE_DM_SINKThe session to
 * which a BFD PDU belongs is determined as part of the BFD Rx
 * verification, based on comparing the BFD PDU Your Discriminator to the
 * values configured in the following bit fields: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_COORDINATED_MODE_ENACoordinated /
 * NEIS session: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SRC.BFD_LOCAL_DISCR_SRCFEIS
 * session: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SINK.BFD_LOCAL_DISCR_SINK
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_RX_SAMPLE_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_SAMPLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_RX_SAMPLE_ENA  VTSS_BIT(18)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_RX_SAMPLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * If enabled, the VOE will update the following fields in the outgoing
 * PDUs when transmitting BFD CC / CV PDUs * BFD.STATE * BFD.DIAG * BFD.DM
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_TX_UPDATE_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_TX_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_TX_UPDATE_ENA  VTSS_BIT(17)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_TX_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * This bit field configures whether the BFD session is running in:0:
 * Independent BFD Mode1: Coordinated BFD Mode
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_COORDINATED_MODE_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_COORDINATED_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_COORDINATED_MODE_ENA  VTSS_BIT(16)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_COORDINATED_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * If this field is asserted all incoming BFD CC PDUs will be verified in
 * HW.Deasserting this field will disable all Rx validation of BFD CC PDUs.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_RX_VERIFY_CC_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_CC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_CC_ENA  VTSS_BIT(15)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_CC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * If this field is asserted all incoming BFD CV PDUs will be verified in
 * HW.Deasserting this field will disable all Rx validation of BFD CV PDUs.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_RX_VERIFY_CV_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_CV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_CV_ENA  VTSS_BIT(14)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_CV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * If not enabled, the VERSION test will not be done as part of the BFD Rx
 * verification of BFD CC/CV PDUs.This testing will depend on the setting
 * of the following bit fields: * BFD_CC_AUTH_ENA * BFD_CV_AUTH_ENAWhen an
 * Rx PDU fails the VERSION test, the following sticky bit is asserted: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_RX_STICKY.VERSION_ERR_STICKYThe VERSION test
 * is disabled if: * BFD_RX_VERIFY_CC_ENA = 0 * BFD_RX_VERIFY_CV_ENA =
 * 0depending on the PDU type.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_RX_VERIFY_VERSION_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_VERSION_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_VERSION_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_VERSION_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * If not enabled, the MIN_LEN test will not be done as part of the BFD Rx
 * verification of BFD CC/CV PDUs.This testing will depend on the setting
 * of the following bit fields: * BFD_CC_AUTH_ENA * BFD_CV_AUTH_ENAWhen an
 * Rx PDU fails the MIN_LEN test, the following sticky bit is asserted: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_RX_STICKY.MIN_LEN_ERR_STICKYThe MIN_LEN test
 * is disabled if: * BFD_RX_VERIFY_CC_ENA = 0 * BFD_RX_VERIFY_CV_ENA =
 * 0depending on the PDU type.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_RX_VERIFY_MIN_LEN_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_MIN_LEN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_MIN_LEN_ENA  VTSS_BIT(12)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_MIN_LEN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * When disabled, the Your/My Discriminator fields of incoming BFD CC/CV
 * PDUs are not verified of BFD CC/CV PDUs.The BFD PDU is assumed to 
 * belong to the Coordinated / NEIS session.When an Rx PDU does not match
 * any of the configured discriminators, the following sticky bit is
 * asserted: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_RX_STICKY.YOUR_DISCR_ERR_STICKYThis test is
 * disabled if: * BFD_RX_VERIFY_CC_ENA = 0 * BFD_RX_VERIFY_CV_ENA =
 * 0depending on the PDU type.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_RX_VERIFY_DISCR_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_DISCR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_DISCR_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_DISCR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * When enabled, the Rx verification will verify:* Detect Mult is ZERO*
 * Multipoint asserted* Auth Bit matches configured* Demand bit is
 * asserted* F and P bits are not set in the same frame.If any of the above
 * test fails, the corresponding sticky bit is asserted
 * (VOP_MPLS:VOE_STAT_MPLS:BFD_RX_STICKY.*): * DM_ZERO_ERR_STICKY *
 * M_BIT_SET_ERR_STICKY * AUTH_MISMATCH_ERR_STICKY * D_BIT_SET_ERR_STICKY *
 * P_AND_F_BIT_SET_ERR_STICKYThe AUTH-bit testing is further dependent on
 * the following bit fields: * BFD_CC_AUTH_ENA * BFD_CV_AUTH_ENAThe FLAGS
 * test is disabled if: * BFD_RX_VERIFY_CC_ENA = 0 * BFD_RX_VERIFY_CV_ENA =
 * 0depending on the PDU type.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_RX_VERIFY_FLAGS_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_FLAGS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_FLAGS_ENA  VTSS_BIT(10)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_FLAGS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * The configuration of this bit field indicates if the incoming BFD CC
 * PDUs are expected to have the AUTH bit set.The value of the AUTH bit in
 * the incoming BFD PDUs is verified as part of the Rx verification 
 * AUTH_MISMATCH test.If this test fails, the following sticky bit is
 * asserted: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_RX_STICKY.AUTH_MISMATCH_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_CC_AUTH_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_CC_AUTH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_CC_AUTH_ENA  VTSS_BIT(9)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_CC_AUTH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * The configuration of this bit field indicates if the incoming BFD CV
 * PDUs are expected to have the AUTH bit set.The value of the AUTH bit in
 * the incoming BFD PDUs is verified as part of the Rx verification 
 * AUTH_MISMATCH test.If this test fails, the following sticky bit is
 * asserted: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_RX_STICKY.AUTH_MISMATCH_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_CV_AUTH_ENA
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_CV_AUTH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_CV_AUTH_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_CV_AUTH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * As part of the Rx verification of BFD PDUs, the BFD length field is
 * compared to the value configured in this bitfield as part of the MAX_LEN
 * test.If the MAX_LEN test fails, the frame is discarded at the following
 * sticky bit is asserted. *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_RX_STICKY.MAX_LEN_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CONFIG . BFD_MAX_LEN
 */
#define  VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_MPLS_BFD_CONFIG_BFD_MAX_LEN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_MPLS_BFD_CONFIG_BFD_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief BFD Local Discriminator (BFD_SRC)
 *
 * \details
 * The Discriminator of the Local BFD Source.
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SRC
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_LOCAL_DISCR_SRC(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,6)

/** 
 * \brief
 * See the register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_LOCAL_DISCR_SRC . BFD_LOCAL_DISCR_SRC
 */
#define  VTSS_F_VOP_MPLS_BFD_LOCAL_DISCR_SRC_BFD_LOCAL_DISCR_SRC(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_LOCAL_DISCR_SRC_BFD_LOCAL_DISCR_SRC     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_LOCAL_DISCR_SRC_BFD_LOCAL_DISCR_SRC(x)  (x)


/** 
 * \brief BFD Remote Discriminator (BFD_SRC)
 *
 * \details
 * The Discriminator of the remote BFD entity communicating with the Local
 * BFD Source
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:BFD_REMOTE_DISCR_SRC
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_REMOTE_DISCR_SRC(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,7)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_REMOTE_DISCR_SRC . BFD_REMOTE_DISCR_SRC
 */
#define  VTSS_F_VOP_MPLS_BFD_REMOTE_DISCR_SRC_BFD_REMOTE_DISCR_SRC(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_REMOTE_DISCR_SRC_BFD_REMOTE_DISCR_SRC     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_REMOTE_DISCR_SRC_BFD_REMOTE_DISCR_SRC(x)  (x)


/** 
 * \brief BFD Local Discriminator (BFD_SINK)
 *
 * \details
 * The Discriminator of the Local BFD Sink.
 * 
 * Only used if the BFD session is configured for Independent Mode:
 * 
 *  * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_COORDINATED_MODE_ENA = 0
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SINK
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_LOCAL_DISCR_SINK(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,8)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_LOCAL_DISCR_SINK . BFD_LOCAL_DISCR_SINK
 */
#define  VTSS_F_VOP_MPLS_BFD_LOCAL_DISCR_SINK_BFD_LOCAL_DISCR_SINK(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_LOCAL_DISCR_SINK_BFD_LOCAL_DISCR_SINK     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_LOCAL_DISCR_SINK_BFD_LOCAL_DISCR_SINK(x)  (x)


/** 
 * \brief BFD Remote Discriminator (BFD_SINK)
 *
 * \details
 * The Discriminator of the remote BFD entity communicating with the Local
 * BFD Sink.
 * 
 *  Only used if the BFD session is configured for Independent Mode:
 * 
 *  * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_COORDINATED_MODE_ENA = 0
 *
 * Register: \a VOP_MPLS:VOE_CONF_MPLS:BFD_REMOTE_DISCR_SINK
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_REMOTE_DISCR_SINK(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x10000,gi,16,0,9)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_REMOTE_DISCR_SINK . BFD_REMOTE_DISCR_SINK
 */
#define  VTSS_F_VOP_MPLS_BFD_REMOTE_DISCR_SINK_BFD_REMOTE_DISCR_SINK(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_REMOTE_DISCR_SINK_BFD_REMOTE_DISCR_SINK     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_REMOTE_DISCR_SINK_BFD_REMOTE_DISCR_SINK(x)  (x)

/**
 * Register Group: \a VOP_MPLS:VOE_STAT_MPLS
 *
 * Per VOE statistics and counters (MPLS-TP OAM)
 */


/** 
 * \brief Count selected OAM PDU received by the VOE.
 *
 * \details
 * All PDU types can be configured as either selected or non-selected PDUs.
 * 
 * This register counts the number of valid OAM PDUs configured as selected
 * PDU type, received by the VOE.
 * 
 * Selected OAM PDUs are configured in:
 * 
 *  * VOP_MPLS:VOE_CONF_MPLS:OAM_CNT_SEL_MPLS.*
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:RX_CNT_SEL_OAM_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_RX_CNT_SEL_OAM_MPLS(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,0)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_RX_CNT_SEL_OAM_MPLS . RX_CNT_SEL_OAM_MPLS
 */
#define  VTSS_F_VOP_MPLS_RX_CNT_SEL_OAM_MPLS_RX_CNT_SEL_OAM_MPLS(x)  (x)
#define  VTSS_M_VOP_MPLS_RX_CNT_SEL_OAM_MPLS_RX_CNT_SEL_OAM_MPLS     0xffffffff
#define  VTSS_X_VOP_MPLS_RX_CNT_SEL_OAM_MPLS_RX_CNT_SEL_OAM_MPLS(x)  (x)


/** 
 * \brief Count non-selected OAM PDU received by the VOE.
 *
 * \details
 * All PDU types can be configured as either selected or non-selected PDUs.
 * 
 * This register counts the number of valid OAM PDUs configured as
 * non-selected PDU type, received by the VOE.
 * 
 * Selected OAM PDUs are configured in: 
 * 
 *  * VOP_MPLS:VOE_CONF_MPLS:OAM_CNT_SEL_MPLS.*
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:RX_CNT_NON_SEL_OAM_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_RX_CNT_NON_SEL_OAM_MPLS(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,1)

/** 
 * \brief
 * See register description
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_RX_CNT_NON_SEL_OAM_MPLS . RX_CNT_NON_SEL_OAM_MPLS
 */
#define  VTSS_F_VOP_MPLS_RX_CNT_NON_SEL_OAM_MPLS_RX_CNT_NON_SEL_OAM_MPLS(x)  (x)
#define  VTSS_M_VOP_MPLS_RX_CNT_NON_SEL_OAM_MPLS_RX_CNT_NON_SEL_OAM_MPLS     0xffffffff
#define  VTSS_X_VOP_MPLS_RX_CNT_NON_SEL_OAM_MPLS_RX_CNT_NON_SEL_OAM_MPLS(x)  (x)


/** 
 * \brief Count selected OAM PDUs transmitted by the VOE.
 *
 * \details
 * All PDU types can be configured as either selected or non-selected PDUs.
 * 
 * This register counts the number of valid OAM PDUs configured as selected
 * PDU type, transmitted by the VOE.
 * 
 * Selected OAM PDUs are configured in: 
 * 
 *  * VOP_MPLS:VOE_CONF_MPLS:OAM_CNT_SEL_MPLS.*
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:TX_CNT_SEL_OAM_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_TX_CNT_SEL_OAM_MPLS(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,2)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_TX_CNT_SEL_OAM_MPLS . TX_CNT_SEL_OAM_MPLS
 */
#define  VTSS_F_VOP_MPLS_TX_CNT_SEL_OAM_MPLS_TX_CNT_SEL_OAM_MPLS(x)  (x)
#define  VTSS_M_VOP_MPLS_TX_CNT_SEL_OAM_MPLS_TX_CNT_SEL_OAM_MPLS     0xffffffff
#define  VTSS_X_VOP_MPLS_TX_CNT_SEL_OAM_MPLS_TX_CNT_SEL_OAM_MPLS(x)  (x)


/** 
 * \brief Count NON-selected OAM PDUs transmitted by the VOE.
 *
 * \details
 * All PDU types can be configured as either selected or non-selected PDUs.
 * 
 * This register counts the number of valid OAM PDUs configured as
 * non-selected PDU type, transmitted by the VOE.
 * 
 * Selected OAM PDUs are configured in: 
 * 
 *  * VOP_MPLS:VOE_CONF_MPLS:OAM_CNT_SEL_MPLS.*
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:TX_CNT_NON_SEL_OAM_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_TX_CNT_NON_SEL_OAM_MPLS(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,3)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_TX_CNT_NON_SEL_OAM_MPLS . TX_CNT_NON_SEL_OAM_MPLS
 */
#define  VTSS_F_VOP_MPLS_TX_CNT_NON_SEL_OAM_MPLS_TX_CNT_NON_SEL_OAM_MPLS(x)  (x)
#define  VTSS_M_VOP_MPLS_TX_CNT_NON_SEL_OAM_MPLS_TX_CNT_NON_SEL_OAM_MPLS     0xffffffff
#define  VTSS_X_VOP_MPLS_TX_CNT_NON_SEL_OAM_MPLS_TX_CNT_NON_SEL_OAM_MPLS(x)  (x)


/** 
 * \brief BFD info related to the Local BFD Source session (BFD_SRC)
 *
 * \details
 * Misc. configuration related to the Local BFD Source (BFD_SRC).
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_SRC_INFO
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_SRC_INFO(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,4)

/** 
 * \brief
 * BFD State of the Local BFD_SRC.This register is configured by SW - never
 * updated by VOE.If configured to do so, the VOE will write this value
 * into all valid Tx BFD CC/CV PDUs STATE field transmitted by the
 * BFD_SRC.The VOE will update the Tx PDUs based on the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_TX_UPDATE_ENA
 *
 * \details 
 * 00 - AdminDown
 * 01 - Down
 * 10 - Init
 * 11 - Up
 *
 * Field: ::VTSS_VOP_MPLS_BFD_SRC_INFO . BFD_LOCAL_STATE_SRC
 */
#define  VTSS_F_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_STATE_SRC(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_STATE_SRC     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_STATE_SRC(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/** 
 * \brief
 * BFD State of the remote BFD entity communicating with the Local
 * BFD_SRC.If configured to do so, the VOE HW will update this bit field
 * with the value of the last valid BFD CC PDU received by the
 * BFD_SRC.Updating this bit field is enabled by the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_RX_SAMPLE_ENA
 *
 * \details 
 * 00 - AdminDown
 * 01 - Down
 * 10 - Init
 * 11 - Up
 *
 * Field: ::VTSS_VOP_MPLS_BFD_SRC_INFO . BFD_REMOTE_STATE_SRC
 */
#define  VTSS_F_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_STATE_SRC(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_STATE_SRC     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_STATE_SRC(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * BFD diagnostic code of the Local BFD_SRC.This register is configured by
 * SW - never updated by VOE.If configured to do so, the VOE will write
 * this value into all valid Tx BFD CC/CV PDUs DIAG field transmitted by
 * the BFD_SRC.The VOE will update the Tx PDUs based on the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_TX_UPDATE_ENA
 *
 * \details 
 * See RFC6428
 *
 * Field: ::VTSS_VOP_MPLS_BFD_SRC_INFO . BFD_LOCAL_DIAG_SRC
 */
#define  VTSS_F_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DIAG_SRC(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DIAG_SRC     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DIAG_SRC(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/** 
 * \brief
 * BFD diagnostic code of the remote BFD entity communicating with the
 * Local BFD_SRC.If configured to do so, the VOE HW will update this bit
 * field with the DIAG CODE value of the last valid BFD CC PDU received by
 * the BFD_SRC.Updating this bit field is enabled by the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_RX_SAMPLE_ENA
 *
 * \details 
 * See RFC6428
 *
 * Field: ::VTSS_VOP_MPLS_BFD_SRC_INFO . BFD_REMOTE_DIAG_SRC
 */
#define  VTSS_F_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DIAG_SRC(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DIAG_SRC     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DIAG_SRC(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * BFD Detect Mult of the Local BFD_SRC.This register is configured by SW -
 * never updated by VOE.If configured to do so, the VOE will write this
 * value into all valid Tx BFD CC/CV PDUs DETECT MULT field transmitted by
 * the BFD_SRC.The VOE will update the Tx PDUs based on the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_TX_UPDATE_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_SRC_INFO . BFD_LOCAL_DM_SRC
 */
#define  VTSS_F_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DM_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DM_SRC     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DM_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * BFD Detect Mult of the remote BFD entity communicating with the Local
 * BFD_SRC.If configured to do so, the VOE HW will update this bit field
 * with the Detect Mult value of the last valid BFD CC PDU received by the
 * BFD_SRC.Updating this bit field is enabled by the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_RX_SAMPLE_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_SRC_INFO . BFD_REMOTE_DM_SRC
 */
#define  VTSS_F_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DM_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DM_SRC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DM_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief BFD info related to the Local BFD Sink session (BFD_SINK)
 *
 * \details
 * Misc. configuration related to the Local BFD Sink (BFD_SINK).
 * 
 * The bit fields in this register are only used when the BFD session is
 * configured for Independent Mode:
 * 
 *  * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_COORDINATED_MODE_ENA = 0
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_SINK_INFO
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_SINK_INFO(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,5)

/** 
 * \brief
 * BFD State of the Local BFD_SINK.This register is configured by SW -
 * never updated by VOE.If configured to do so, the VOE will write this
 * value into all valid Tx BFD CC/CV PDUs STATE field of all PDUs
 * transmitted by the BFD_SINK.The VOE will update the Tx PDUs based on the
 * following configuration: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_TX_UPDATE_ENA
 *
 * \details 
 * 00 - AdminDown
 * 01 - Down
 * 10 - Init
 * 11 - Up
 *
 * Field: ::VTSS_VOP_MPLS_BFD_SINK_INFO . BFD_LOCAL_STATE_SINK
 */
#define  VTSS_F_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_STATE_SINK(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_STATE_SINK     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_STATE_SINK(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/** 
 * \brief
 * BFD State of the remote BFD entity communicating with the Local
 * BFD_SINKIf configured to do so, the VOE HW will update this bit field
 * with the value of the last valid BFD CC PDU received by the
 * BFD_SINK.Updating this bit field is enabled by the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_RX_SAMPLE_ENA
 *
 * \details 
 * 00 - AdminDown
 * 01 - Down
 * 10 - Init
 * 11 - Up
 *
 * Field: ::VTSS_VOP_MPLS_BFD_SINK_INFO . BFD_REMOTE_STATE_SINK
 */
#define  VTSS_F_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_STATE_SINK(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_STATE_SINK     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_STATE_SINK(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * BFD diagnostic code of the Local BFD_SINK.This register is configured by
 * SW - never updated by VOE.If configured to do so, the VOE will write
 * this value into all valid Tx BFD CC/CV PDUs DIAG field transmitted by
 * the BFD_SINK.The VOE will update the Tx PDUs based on the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_TX_UPDATE_ENA
 *
 * \details 
 * See RFC6428
 *
 * Field: ::VTSS_VOP_MPLS_BFD_SINK_INFO . BFD_LOCAL_DIAG_SINK
 */
#define  VTSS_F_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DIAG_SINK(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DIAG_SINK     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DIAG_SINK(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/** 
 * \brief
 * BFD diagnostic code of the remote BFD entity communicating with the
 * Local BFD_SINK.If configured to do so, the VOE HW will update this bit
 * field with the DIAG CODE value of the last valid BFD CC PDU received by
 * the BFD_SINK.Updating this bit field is enabled by the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_RX_SAMPLE_ENA
 *
 * \details 
 * See RFC6428
 *
 * Field: ::VTSS_VOP_MPLS_BFD_SINK_INFO . BFD_REMOTE_DIAG_SINK
 */
#define  VTSS_F_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DIAG_SINK(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DIAG_SINK     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DIAG_SINK(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * BFD Detect Mult of the Local BFD_SINK.This register is configured by SW
 * - never updated by VOE.If configured to do so, the VOE will write this
 * value into all valid Tx BFD CC/CV PDUs DETECT MULT field transmitted by
 * the BFD_SINK.The VOE will update the Tx PDUs based on the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_TX_UPDATE_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_SINK_INFO . BFD_LOCAL_DM_SINK
 */
#define  VTSS_F_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DM_SINK(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DM_SINK     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DM_SINK(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * BFD Detect Mult of the remote BFD entity communicating with the Local
 * BFD_SINK.If configured to do so, the VOE HW will update this bit field
 * with the Detect Mult value of the last valid BFD CC PDU received by the
 * BFD_SINK.Updating this bit field is enabled by the following
 * configuration: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_RX_SAMPLE_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_SINK_INFO . BFD_REMOTE_DM_SINK
 */
#define  VTSS_F_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DM_SINK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DM_SINK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DM_SINK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief BFD statistics
 *
 * \details
 * Register contains misc. BFD related statistics.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_STAT(gi)           VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,6)

/** 
 * \brief
 * BFD Loss of Continuity (LOC) Counter.This counter is incremented by the
 * LOC SCAN timer programmed in the following bit field: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_SCAN_PERIODThe LOC counter is
 * cleared every time a valid BFD CC/CV PDU is received.The VOE will
 * generate a LOC event when the BFD_MISS_CNT is equal to the value in the
 * relevant Detect Multiplier.Which Detect Multiplier is used depends on
 * whether the BFD session is configured for "Coordinated Mode" or
 * "Independent Mode".
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_STAT . BFD_MISS_CNT
 */
#define  VTSS_F_VOP_MPLS_BFD_STAT_BFD_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_VOP_MPLS_BFD_STAT_BFD_MISS_CNT     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_VOP_MPLS_BFD_STAT_BFD_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief Result of previous BFD testing
 *
 * \details
 * To detect changes in certain BFD states, this register stores the values
 * of the testing of the previous BFD PDU.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_RX_LAST
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_RX_LAST(gi)        VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,7)

/** 
 * \brief
 * Contains the current LOC state.When this value is changed (by LOC timer
 * or Rx of valid BFD CC/CV) a sticky bit is asserted: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_LOC_CHANGE_STICKYAn
 * interrupt may optionally be generated: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_LOC_CHANGE_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_LAST . BFD_LOC_DEFECT
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_LAST_BFD_LOC_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_LAST_BFD_LOC_DEFECT  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_BFD_RX_LAST_BFD_LOC_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Sticky bits with interrupt capability
 *
 * \details
 * The sticky bits in this register will cause a VOE interrupt if the
 * interrupt is enabled by the corresponding enable bit field in:
 * 
 *  * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.*
 * 
 * If an interrupt is enabled, the interrupt is asserted when the
 * corresponding sticky bit is asserted.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_INTR_STICKY_MPLS(gi)   VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,8)

/** 
 * \brief
 * This sticky bit is asserted when the VOE Loss of Continuity (LOC) detect
 * state changes.The following two events will cause the assertion of this
 * sticky bit: * The BFD_MISS_CNT is increased to 2 x the session Detect
 * Mult (LOC detection). * A valid BFD CC/CV PDU is received by the VOE
 * which is in LOC state.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_LOC_CHANGE_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_LOC_CHANGE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_LOC_CHANGE_STICKY  VTSS_BIT(10)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_LOC_CHANGE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * When the BFD Source receives a valid BFD CC PDU, this sticky bit is
 * asserted if the 'Detect Mult' value in the Rx BFD CC PDU is different
 * from the previous value received.The previous value is stored in: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SRC_INFO.BFD_REMOTE_DM_SRCThis event will
 * generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_DM_CHANGE_SRC_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_DM_CHANGE_SRC_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SRC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SRC_STICKY  VTSS_BIT(9)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SRC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * When the BFD Source receives a valid BFD CC PDU, this sticky bit is
 * asserted if the 'State' value in the Rx BFD CC PDU is different from the
 * previous value received.The previous value is stored in: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SRC_INFO.BFD_REMOTE_STATE_SRCThis event will
 * generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_STATE_CHANGE_SRC_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_STATE_CHANGE_SRC_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SRC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SRC_STICKY  VTSS_BIT(8)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SRC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * When the BFD Source receives a valid BFD CC PDU, this sticky bit is
 * asserted if the 'Diag' value in the Rx BFD CC PDU is different from the
 * previous value received.The previous value is stored in: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SRC_INFO.BFD_REMOTE_DIAG_SRCThis event will
 * generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_DIAG_CHANGE_SRC_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_DIAG_CHANGE_SRC_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SRC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SRC_STICKY  VTSS_BIT(7)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SRC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * When the BFD Source receives a valid BFD CC PDU, this sticky bit is
 * asserted if the Poll Flag is asserted in the Rx BFD CC PDU.This event
 * will generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_P_SET_SRC_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_P_SET_SRC_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SRC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SRC_STICKY  VTSS_BIT(6)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SRC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * When the BFD Source receives a valid BFD CC PDU, this sticky bit is
 * asserted if the Final Flag is asserted in the Rx BFD CC PDU.This event
 * will generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_F_SET_SRC_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_F_SET_SRC_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SRC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SRC_STICKY  VTSS_BIT(5)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SRC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * When the BFD Sink receives a valid BFD CC PDU, this sticky bit is
 * asserted if the 'Detect Mult' value in the Rx BFD CC PDU is different
 * from the previous value received.The previous value is stored in: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SINK_INFO.BFD_REMOTE_DM_SINKThis event will
 * generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_DM_CHANGE_SINK_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_DM_CHANGE_SINK_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SINK_STICKY  VTSS_BIT(4)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * When the BFD Sink receives a valid BFD CC PDU, this sticky bit is
 * asserted if the 'State' value in the Rx BFD CC PDU is different from the
 * previous value received.The previous value is stored in: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SINK_INFO.BFD_REMOTE_STATE_SINKThis event
 * will generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_STATE_CHANGE_SINK_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_STATE_CHANGE_SINK_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SINK_STICKY  VTSS_BIT(3)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When the BFD Sink receives a valid BFD CC PDU, this sticky bit is
 * asserted if the 'Diag' value in the Rx BFD CC PDU is different from the
 * previous value received.The previous value is stored in: *
 * VOP_MPLS:VOE_STAT_MPLS:BFD_SINK_INFO.BFD_REMOTE_DIAG_SINKThis event will
 * generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_DIAG_CHANGE_SINK_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_DIAG_CHANGE_SINK_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SINK_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When the BFD Sink receives a valid BFD CC PDU, this sticky bit is
 * asserted if the Poll Flag is asserted in the Rx BFD CC PDU.This event
 * will generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_P_SET_SINK_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_P_SET_SINK_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SINK_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When the BFD Sink receives a valid BFD CC PDU, this sticky bit is
 * asserted if the Final Flag is asserted in the Rx BFD CC PDU.This event
 * will generate an interrupt if so enabled in: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.BFD_RX_F_SET_SINK_INT_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_STICKY_MPLS . BFD_RX_F_SET_SINK_STICKY
 */
#define  VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SINK_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Sticky bit interrupt enable
 *
 * \details
 * The bitfields in this register are interrupt enable for the
 * corresponding sticky bits in the following register:
 * 
 *  * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.*
 * 
 * If an interrupt is enabled, the interrupt is asserted when the
 * corresponding sticky bit is asserted.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_INTR_ENA_MPLS(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,9)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_LOC_CHANGE_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_LOC_CHANGE_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_LOC_CHANGE_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_LOC_CHANGE_INT_ENA  VTSS_BIT(10)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_LOC_CHANGE_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_DM_CHANGE_SRC_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_DM_CHANGE_SRC_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DM_CHANGE_SRC_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DM_CHANGE_SRC_INT_ENA  VTSS_BIT(9)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DM_CHANGE_SRC_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_STATE_CHANGE_SRC_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_STATE_CHANGE_SRC_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_STATE_CHANGE_SRC_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_STATE_CHANGE_SRC_INT_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_STATE_CHANGE_SRC_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_DIAG_CHANGE_SRC_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_DIAG_CHANGE_SRC_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DIAG_CHANGE_SRC_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DIAG_CHANGE_SRC_INT_ENA  VTSS_BIT(7)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DIAG_CHANGE_SRC_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_P_SET_SRC_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_P_SET_SRC_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_P_SET_SRC_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_P_SET_SRC_INT_ENA  VTSS_BIT(6)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_P_SET_SRC_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_F_SET_SRC_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_F_SET_SRC_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_F_SET_SRC_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_F_SET_SRC_INT_ENA  VTSS_BIT(5)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_F_SET_SRC_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_DM_CHANGE_SINK_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_DM_CHANGE_SINK_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DM_CHANGE_SINK_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DM_CHANGE_SINK_INT_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DM_CHANGE_SINK_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_STATE_CHANGE_SINK_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_STATE_CHANGE_SINK_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_STATE_CHANGE_SINK_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_STATE_CHANGE_SINK_INT_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_STATE_CHANGE_SINK_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_DIAG_CHANGE_SINK_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_DIAG_CHANGE_SINK_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DIAG_CHANGE_SINK_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DIAG_CHANGE_SINK_INT_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_DIAG_CHANGE_SINK_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_P_SET_SINK_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_P_SET_SINK_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_P_SET_SINK_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_P_SET_SINK_INT_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_P_SET_SINK_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.BFD_RX_F_SET_SINK_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_INTR_ENA_MPLS . BFD_RX_F_SET_SINK_INT_ENA
 */
#define  VTSS_F_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_F_SET_SINK_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_F_SET_SINK_INT_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_INTR_ENA_MPLS_BFD_RX_F_SET_SINK_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Rx Sticky bits
 *
 * \details
 * Sticky bits are asserted when a valid MPLS-TP OAM PDU is received by the
 * VOE.
 * 
 * The G-ACH Channel Type specific Rx sticky bits:
 * 
 *  * "xxx"_RX_STICKY
 * 
 * will be asserted even when the PDU is not enabled
 * (VOP_MPLS:VOE_CONF_MPLS:OAM_HW_CTRL_MPLS.*), to allow detecting PDU
 * types which are not expected.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:CPT_RX_STICKY_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,10)

/** 
 * \brief
 * Asserted when VOE receives a valid OAM PDU with an G-ACH Channel Type
 * which is configured as a Generic G-ACH Channel Type in the following
 * register: * VOP::MPLS_GENERIC_CODEPOINT.GENERIC_CODEPOINT_VALThere is a
 * separate bit to indicate the reception of each of the configured Generic
 * G-ACH Channel Types.
 *
 * \details 
 * x0x: No CPU copy
 * x1x: Copy to CPU
 *
 * Field: ::VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS . GENERIC_CPT_RX_STICKY_MASK
 */
#define  VTSS_F_VOP_MPLS_CPT_RX_STICKY_MPLS_GENERIC_CPT_RX_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_GENERIC_CPT_RX_STICKY_MASK     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_VOP_MPLS_CPT_RX_STICKY_MPLS_GENERIC_CPT_RX_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/** 
 * \brief
 * Asserted when VOE receives a valid MPLS-TP OAM PDU with an G-ACH Channel
 * Type which is detected as UNKNOWN.UNKNOWN G-ACH Channel Type is used for
 * OAM PDU types which do not have dedicated HW support and which is not
 * encoded as a Generic G-ACH Channel Type.
 *
 * \details 
 * '0': No UNKNOWN PDU received.
 * '1': PDU with UNKNOWN Channel Type received.
 *
 * Field: ::VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS . UNK_CPT_RX_STICKY
 */
#define  VTSS_F_VOP_MPLS_CPT_RX_STICKY_MPLS_UNK_CPT_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_UNK_CPT_RX_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_MPLS_CPT_RX_STICKY_MPLS_UNK_CPT_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Asserted when the VOE receives a valid BFD CC PDU.
 *
 * \details 
 * '0': No Valid BFD CC PDU received
 * '1': Valid BFD CC received
 *
 * Field: ::VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS . BFD_CC_RX_STICKY
 */
#define  VTSS_F_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CC_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CC_RX_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CC_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Asserted when the VOE receives a valid BFD CV PDU
 *
 * \details 
 * '0': No Valid BFD CV PDU received
 * '1': Valid BFD CV received
 *
 * Field: ::VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS . BFD_CV_RX_STICKY
 */
#define  VTSS_F_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CV_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CV_RX_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CV_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Extraction of MPLS PDUs
 *
 * \details
 * This register contains a number of bit fields which are used to
 * configure extraction of certains MPLS PDUs, which match a given
 * criteria.
 * 
 * Note that some of the registers will extract either 'NEXT FRAME only '
 * (Hit Me Once) or 'ALL FRAMES' matching a given criteria, based on the
 * configuration of the following bitfield:
 * 
 *  * EXTRACT_HIT_ME_ONCE
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:PDU_EXTRACT_MPLS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_PDU_EXTRACT_MPLS(gi)   VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,11)

/** 
 * \brief
 * Extract the next valid BFD CC PDU received by the VOE.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_PDU_EXTRACT_MPLS . BFD_CC_RX_NEXT_GOOD_EXTR
 */
#define  VTSS_F_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CC_RX_NEXT_GOOD_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CC_RX_NEXT_GOOD_EXTR  VTSS_BIT(7)
#define  VTSS_X_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CC_RX_NEXT_GOOD_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Extract the next valid BFD CV PDU received by the VOE.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_PDU_EXTRACT_MPLS . BFD_CV_RX_NEXT_GOOD_EXTR
 */
#define  VTSS_F_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CV_RX_NEXT_GOOD_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CV_RX_NEXT_GOOD_EXTR  VTSS_BIT(6)
#define  VTSS_X_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CV_RX_NEXT_GOOD_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * The configuration of this bit field determines whether the following
 * configuration bits cause extraction of the Next Frame Only (Hit Me Once)
 * or all the Frames matching a given criteria: * BFD_RX_PARAM_CHANGE_EXTR
 * * BFD_RX_P_SET_EXTR * BFD_RX_F_SET_EXTR * BFD_RX_ERR_EXTR *
 * BFD_TX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_PDU_EXTRACT_MPLS . EXTRACT_HIT_ME_ONCE
 */
#define  VTSS_F_VOP_MPLS_PDU_EXTRACT_MPLS_EXTRACT_HIT_ME_ONCE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_EXTRACT_HIT_ME_ONCE  VTSS_BIT(5)
#define  VTSS_X_VOP_MPLS_PDU_EXTRACT_MPLS_EXTRACT_HIT_ME_ONCE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Will extract the next valid Rx BFD PDU if one of the following
 * parameters changed since the last BFD PDU belonging to the same session
 * (Coordinated / NEIS / FEIS): * BFD.DM * BFD.DIAG * BFD.STATEExtraction
 * will be done Hit Me Once or all frames depending on the following bit
 * field: * EXTRACT_HIT_ME_ONCE
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_PDU_EXTRACT_MPLS . BFD_RX_PARAM_CHANGE_EXTR
 */
#define  VTSS_F_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_PARAM_CHANGE_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_PARAM_CHANGE_EXTR  VTSS_BIT(4)
#define  VTSS_X_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_PARAM_CHANGE_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Asserting this bit will extract frames with the Poll flag set.Extraction
 * will be done Hit Me Once or all frames depending on the following bit
 * field: * EXTRACT_HIT_ME_ONCE
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_PDU_EXTRACT_MPLS . BFD_RX_P_SET_EXTR
 */
#define  VTSS_F_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_P_SET_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_P_SET_EXTR  VTSS_BIT(3)
#define  VTSS_X_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_P_SET_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Asserting this bit will extract frames with the Final flag
 * set.Extraction will be done Hit Me Once or all frames depending on the
 * following bit field: * EXTRACT_HIT_ME_ONCE
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_PDU_EXTRACT_MPLS . BFD_RX_F_SET_EXTR
 */
#define  VTSS_F_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_F_SET_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_F_SET_EXTR  VTSS_BIT(2)
#define  VTSS_X_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_F_SET_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Asserting this bit will extract BFD PDUs which fail the Rx verification
 * test.Extraction will be done Hit Me Once or all frames depending on the
 * following bit field: * EXTRACT_HIT_ME_ONCE
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_PDU_EXTRACT_MPLS . BFD_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_ERR_EXTR  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Asserting this bit will extract BFD PDUs which fail the Tx verification
 * test.Extraction will be done Hit Me Once or all frames depending on the
 * following bit field: * EXTRACT_HIT_ME_ONCE
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_PDU_EXTRACT_MPLS . BFD_TX_ERR_EXTR
 */
#define  VTSS_F_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_TX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_TX_ERR_EXTR  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_TX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief BFD Rx verification sticky bits.
 *
 * \details
 * This register contains a sticky bit for each of the tests performed as
 * part of the BFD Rx PDU validation.
 * 
 * Frames causing the sticky to be asserted will be discarded if not
 * extracted to the CPU.
 * 
 * The extraction of BFD PDUs is configured in the following register:
 * 
 *  * VOP_MPLS:VOE_STAT_MPLS:PDU_EXTRACT_MPLS.*
 * 
 * Notice that the Rx verification depends on the following registers:
 * 
 *  * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_RX_VERIFY_*
 * 
 * PDUs failing the Rx verification can optionally be extracted by
 * configuring the following bit field:
 * 
 *  * VOP_MPLS:VOE_STAT_MPLS:PDU_EXTRACT_MPLS.BFD_RX_ERR_EXTR
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_RX_STICKY
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_RX_STICKY(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,12)

/** 
 * \brief
 * Sticky bit is asserted when a frame is discarded because the
 * BFD_CC/CV.VERSION field does not match the value configured in the
 * following register: * VOP::VERSION_CTRL_MPLS.BFD_VERSION

 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . VERSION_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_VERSION_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_VERSION_ERR_STICKY  VTSS_BIT(9)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_VERSION_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Sticky bit asserted if an incoming BFD frame fails the MIN_LEN
 * test.MIN_LEN test will discard incoming BFD frames based on the value of
 * the AUTH bit and the LENGTH field in the BFD PDU:AUTH = 0: Discard PDU
 * if LENGTH < 24 bytesAUTH = 1: Discard PDU if LENGTH < 26 bytes
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . MIN_LEN_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_MIN_LEN_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_MIN_LEN_ERR_STICKY  VTSS_BIT(8)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_MIN_LEN_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Sticky bit asserted if an incoming BFD frame fails the MAX_LEN test.The
 * MAX_LEN will discard incoming BFD PDUs if the LENGTH field in the BFD
 * PDU is larger than the configured MAX_LEN: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_MAX_LEN
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . MAX_LEN_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_MAX_LEN_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_MAX_LEN_ERR_STICKY  VTSS_BIT(7)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_MAX_LEN_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Sticky bit asserted if an incoming Rx BFD PDU fails the DM_ZERO
 * test:Incoming Rx BFD PDUs are discarded if the Detect Mult field is
 * ZERO.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . DM_ZERO_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_DM_ZERO_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_DM_ZERO_ERR_STICKY  VTSS_BIT(6)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_DM_ZERO_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Sticky bit asserted if an incoming BFD PDU fails the M_BIT_SET
 * test.Incoming Rx BFD PDUs are discarded if the M bit is set.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . M_BIT_SET_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_M_BIT_SET_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_M_BIT_SET_ERR_STICKY  VTSS_BIT(5)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_M_BIT_SET_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Sticky bit asserted if an incoming Rx BFD PDU is discarded because it
 * fails the MY_DISCR verification.The MY_DISCR test will match the My
 * Discriminator field in the Rx BFD PDU, based on which session the BFD
 * PDU belongs to. Coordinated or NEIS session: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_REMOTE_DISCR_SRC.BFD_REMOTE_DISCR_SRCFEIS
 * session: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_REMOTE_DISCR_SINK.BFD_REMOTE_DISCR_SINKThe
 * session is determined based on matching the BFD PDU Your Discriminator
 * against the following values: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SRC.BFD_LOCAL_DISCR_SRC *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SINK.BFD_LOCAL_DISCR_SINK 
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . MY_DISCR_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_MY_DISCR_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_MY_DISCR_ERR_STICKY  VTSS_BIT(4)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_MY_DISCR_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Sticky bit asserted if an incoming BFD PDU fails the YOUR_DISCR test.The
 * YOUR_DISCR test will match the Your Discriminator field of the Rx BFD
 * PDU against the values configured in the following registers, to
 * determine which session the BFD PDU belongs to:Coordinated or NEIS
 * session: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SRC.BFD_LOCAL_DISCR_SRCFEIS
 * session: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SINK.BFD_LOCAL_DISCR_SINKThe
 * match will depend on the configuration of the following bit field: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_COORDINATED_MODE_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . YOUR_DISCR_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_YOUR_DISCR_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_YOUR_DISCR_ERR_STICKY  VTSS_BIT(3)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_YOUR_DISCR_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Sticky bit asserted if an incoming BFD PDU fails the AUTH_MISMATCH
 * test.The VOE is configured with the expected value of the incoming BFD
 * PDUs:BFD CC: * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_CC_AUTH_ENABFD CV:
 * * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_CV_AUTH_ENAThe AUTH_MISMATCH
 * test will fail if the incoming BFD PDUs AUTH bit does not match the
 * configured value.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . AUTH_MISMATCH_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_AUTH_MISMATCH_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_AUTH_MISMATCH_ERR_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_AUTH_MISMATCH_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Sticky bit is asserted if an Rx BFD PDU fails the D_BIT_SET test.Frames
 * failing this test are discarded.The D_BIT_SET test will fail if a BFD
 * PDU is received with the D bit = 1.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . D_BIT_SET_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_D_BIT_SET_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_D_BIT_SET_ERR_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_D_BIT_SET_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Sticky bit is asserted if an Rx BFD PDU fails the P_AND_F_BIT_SET
 * test.Frames failing this test are discarded.The P_AND_F_BIT_SET fails if
 * a BFD PDU is received with both the Poll Flag = 1 and the Final flag = 1 
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_RX_STICKY . P_AND_F_BIT_SET_ERR_STICKY
 */
#define  VTSS_F_VOP_MPLS_BFD_RX_STICKY_P_AND_F_BIT_SET_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_BFD_RX_STICKY_P_AND_F_BIT_SET_ERR_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_BFD_RX_STICKY_P_AND_F_BIT_SET_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief BFD Tx verification sticky bits.
 *
 * \details
 * This register contains sticky bits indicating the different Tx errors
 * detected by the VOE.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_TX_STICKY
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_TX_STICKY(gi)      VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,13)

/** 
 * \brief
 * Sticky bit asserted if a BFD PDU is transmitted by a VOE and the VOE is
 * configured to update the BFD PDU: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_TX_UPDATE_ENAand the Tx BFD PDU My
 * Discriminator value does not match any of the configured BFD
 * Discriminator Values:Coordinated or NEIS session: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SRC.BFD_LOCAL_DISCR_SRCFEIS
 * session: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_LOCAL_DISCR_SINK.BFD_LOCAL_DISCR_SINKThe type
 * of session must be configured using the following bit field: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_COORDINATED_MODE_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_TX_STICKY . TX_MY_DISCR_MISMATCH
 */
#define  VTSS_F_VOP_MPLS_BFD_TX_STICKY_TX_MY_DISCR_MISMATCH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_MPLS_BFD_TX_STICKY_TX_MY_DISCR_MISMATCH  VTSS_BIT(0)
#define  VTSS_X_VOP_MPLS_BFD_TX_STICKY_TX_MY_DISCR_MISMATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Valid BFD CC Tx count.
 *
 * \details
 * The number of BFD CC PDUs transmitted by the VOE.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_CC_TX_CNT_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_CC_TX_CNT_REG(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,14)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CC_TX_CNT_REG . BFD_CC_TX_CNT
 */
#define  VTSS_F_VOP_MPLS_BFD_CC_TX_CNT_REG_BFD_CC_TX_CNT(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_CC_TX_CNT_REG_BFD_CC_TX_CNT     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_CC_TX_CNT_REG_BFD_CC_TX_CNT(x)  (x)


/** 
 * \brief Valid BFD CV Tx count.
 *
 * \details
 * The number of BFD CV PDUs transmitted by the VOE.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_CV_TX_CNT_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_CV_TX_CNT_REG(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,15)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CV_TX_CNT_REG . BFD_CV_TX_CNT
 */
#define  VTSS_F_VOP_MPLS_BFD_CV_TX_CNT_REG_BFD_CV_TX_CNT(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_CV_TX_CNT_REG_BFD_CV_TX_CNT     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_CV_TX_CNT_REG_BFD_CV_TX_CNT(x)  (x)


/** 
 * \brief Valid BFD CC Rx count.
 *
 * \details
 * The number of valid BFD CC PDUs received by the VOE.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_CC_RX_VLD_CNT_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_CC_RX_VLD_CNT_REG(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,16)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CC_RX_VLD_CNT_REG . BFD_CC_RX_VLD_CNT
 */
#define  VTSS_F_VOP_MPLS_BFD_CC_RX_VLD_CNT_REG_BFD_CC_RX_VLD_CNT(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_CC_RX_VLD_CNT_REG_BFD_CC_RX_VLD_CNT     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_CC_RX_VLD_CNT_REG_BFD_CC_RX_VLD_CNT(x)  (x)


/** 
 * \brief Valid BFD CV Rx count.
 *
 * \details
 * The number of valid BFD CV PDUs received by the VOE.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_CV_RX_VLD_CNT_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_CV_RX_VLD_CNT_REG(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,17)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CV_RX_VLD_CNT_REG . BFD_CV_RX_VLD_CNT
 */
#define  VTSS_F_VOP_MPLS_BFD_CV_RX_VLD_CNT_REG_BFD_CV_RX_VLD_CNT(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_CV_RX_VLD_CNT_REG_BFD_CV_RX_VLD_CNT     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_CV_RX_VLD_CNT_REG_BFD_CV_RX_VLD_CNT(x)  (x)


/** 
 * \brief Invalid BFD CC Rx count.
 *
 * \details
 * The number of invalid BFD CC PDUs received by the VOE. Invalid PDUs are
 * Rx BFD CC PDUs which are discarded due to failing the BFD Rx
 * verification.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_CC_RX_INVLD_CNT_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_CC_RX_INVLD_CNT_REG(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,18)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CC_RX_INVLD_CNT_REG . BFD_CC_RX_INVLD_CNT
 */
#define  VTSS_F_VOP_MPLS_BFD_CC_RX_INVLD_CNT_REG_BFD_CC_RX_INVLD_CNT(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_CC_RX_INVLD_CNT_REG_BFD_CC_RX_INVLD_CNT     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_CC_RX_INVLD_CNT_REG_BFD_CC_RX_INVLD_CNT(x)  (x)


/** 
 * \brief Invalid BFD CV Rx count.
 *
 * \details
 * The number of invalid BFD CV PDUs received by the VOE. Invalid PDUs are
 * Rx BFD CV PDUs which are discarded due to failing the BFD Rx
 * verification.
 *
 * Register: \a VOP_MPLS:VOE_STAT_MPLS:BFD_CV_RX_INVLD_CNT_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_MPLS_BFD_CV_RX_INVLD_CNT_REG(gi)  VTSS_IOREG_IX(VTSS_TO_VOP_MPLS,0x0,gi,32,0,19)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_MPLS_BFD_CV_RX_INVLD_CNT_REG . BFD_CV_RX_INVLD_CNT
 */
#define  VTSS_F_VOP_MPLS_BFD_CV_RX_INVLD_CNT_REG_BFD_CV_RX_INVLD_CNT(x)  (x)
#define  VTSS_M_VOP_MPLS_BFD_CV_RX_INVLD_CNT_REG_BFD_CV_RX_INVLD_CNT     0xffffffff
#define  VTSS_X_VOP_MPLS_BFD_CV_RX_INVLD_CNT_REG_BFD_CV_RX_INVLD_CNT(x)  (x)


#endif /* _VTSS_FA_REGS_VOP_MPLS_H_ */
