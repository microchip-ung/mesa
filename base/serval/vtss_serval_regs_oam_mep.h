// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVAL_REGS_OAM_MEP_H_
#define _VTSS_SERVAL_REGS_OAM_MEP_H_


#include "vtss_serval_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a OAM_MEP
 *
 * The Vitesse OAM MEP Processor (VOP) block implements the HW support for
 * implementing OAM MEP.
 * 
 * The VOP consists of 75 Vitesse OAM Endpoints (VOE) that each implements
 * an OAM MEP.
 * 
 * The VOP includes the following:
 * - 64 service/path VOEs
 * - 11 port VOEs
 *
 ***********************************************************************/

/**
 * Register Group: \a OAM_MEP:COMMON
 *
 * Miscellaneous configuration for OAM_MEP
 */


/** 
 * \brief Miscellaneous MEP controls
 *
 * \details
 * This register contains various settings that are global to all VOEs.
 *
 * Register: \a OAM_MEP:COMMON:MEP_CTRL
 */
#define VTSS_OAM_MEP_COMMON_MEP_CTRL         VTSS_IOREG(VTSS_TO_OAM_MEP,0x1800)

/** 
 * \brief
 * The CCM PDU does not have a dedicated register for the RxFCf counter.
 * However there is a reserved field which can be used to hold this value.
 * 
 * Asserting this field enables updating reserved field for RX CCM LM PDU
 * with Rx FCf.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_MEP_CTRL . CCM_LM_UPD_RSV_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_MEP_CTRL_CCM_LM_UPD_RSV_ENA  VTSS_BIT(14)

/** 
 * \brief
 * Down-MEP only (No effect for Up-MEP):
 * The LMR does not have any fields reserved to hold the RxFCf counter upon
 * reception of an LMR frame.
 * 
 * The VOE supports adding the RxFCf counter following the other three
 * counters in the LMR PDU. This requires extending the first TLV from 12
 * --> 16 bytes.
 * 
 * This solution is a proprietary solution, which allows forwarding the
 * RxFCf value to an external CPU.
 * 
 * Asserting this fields enables updating TLV offset to 16 and setting
 * inserting RxFcLocal after TxFcb.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_MEP_CTRL . LMR_UPD_RxFcL_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_MEP_CTRL_LMR_UPD_RXFCL_ENA  VTSS_BIT(13)

/** 
 * \brief
 * Enables or disables automated CCM scan to be used for CCM Loss of
 * Continuity (LOC) handling.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_MEP_CTRL . CCM_SCAN_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_MEP_CTRL_CCM_SCAN_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enables or disables the functionality of the VOEs in the VOP.
 * The single VOEs can still be configured even though the VOP is disabled.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_MEP_CTRL . MEP_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_MEP_CTRL_MEP_ENA  VTSS_BIT(0)

/** 
 * \brief
 * Configures the front ports to be used for external CPU or FPGA handling.
 * 
 * Ports used for OAM PDU injection or OAM PDU extraction must be asserted
 * in this portmask.
 *
 * \details 
 * 0: port is a front port
 * 1: Port is a CPU extract port.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_MEP_CTRL . EXT_CPU_PORTMASK
 */
#define  VTSS_F_OAM_MEP_COMMON_MEP_CTRL_EXT_CPU_PORTMASK(x)  VTSS_ENCODE_BITFIELD(x,2,11)
#define  VTSS_M_OAM_MEP_COMMON_MEP_CTRL_EXT_CPU_PORTMASK     VTSS_ENCODE_BITMASK(2,11)
#define  VTSS_X_OAM_MEP_COMMON_MEP_CTRL_EXT_CPU_PORTMASK(x)  VTSS_EXTRACT_BITFIELD(x,2,11)


/** 
 * \brief Configuring destination for CPU copied frames.
 *
 * \details
 * For frames which are copied to the CPU, the actual destination to where
 * such frames are forwarded is specified in this register.
 * 
 * Note:
 *   If the destination of the OAM frame is an external port
 * (*_EXT_PORT_ENA = 1), this port must be configured as an OAM extract
 * port. This is done by asserting the OAM extract port in the port mask
 * CPU_CFG_1.EXT_CPU_PORTMASK.
 * 
 * OAM frames may be forwarded to the CPU using register: OAM_CPU_COPY_CTRL
 * or because certain OAM PDUs are forwarded unconditionally to the CPU.
 * 
 * Most HW supported OAM PDUs have their own configuration, while some
 * related PDUs share a single configuration.
 * 
 * The configuration for each OAM ODU consists of two bit fields:
 * 1) *_EXT_PORT_ENA
 * Depending on the value of this bit field, the CPU copied frame is
 * forwarded to an external port (=1) or an internal CPU extraction queue
 * (=0).
 * 
 * 2) *_CPU_QU
 * In case the frame is forwarded to an internal CPU extraction queue, this
 * bit field indicates the target CPU extraction queue.
 * In case the frame is forwarded to an external, this bit field indicates
 * the number of the physical port to which the frame is forwarded.
 * 
 * OAM PDU types which do not have a specific configuration use the default
 * configuration:
 * DEF_EXT_PORT_ENA and DEF_COPY_CPU_QU
 * 
 * The details are described for each bit field.

 *
 * Register: \a OAM_MEP:COMMON:CPU_CFG
 */
#define VTSS_OAM_MEP_COMMON_CPU_CFG          VTSS_IOREG(VTSS_TO_OAM_MEP,0x1801)

/** 
 * \brief
 * This bit field is a default forwarding configuration which determines
 * where to forward OAM PDU, which do not have a specific forwarding queue.
 * 
 * Also frames extracted based on the following configuration:
 * 
 * VOE:BASIC_CTRL.CPU_HITME_ONCE_CCM_TLV
 * 
 * Will be extracted to this queue.
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by DEF_COPY_QU
 * 1: Frames are sent to front port configured by DEF_COPY_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . DEF_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_DEF_EXT_PORT_ENA  VTSS_BIT(29)

/** 
 * \brief
 * This bit field is a default forwarding configuration which determines
 * where to forward OAM PDU, which do not have a specific forwarding queue.
 * 
 * Also frames extracted based on the following configuration:
 * 
 * VOE:BASIC_CTRL.CPU_HITME_ONCE_CCM_TLV
 * 
 * Will be extracted to this queue.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . DEF_COPY_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_DEF_COPY_QU(x)  VTSS_ENCODE_BITFIELD(x,25,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_DEF_COPY_QU     VTSS_ENCODE_BITMASK(25,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_DEF_COPY_QU(x)  VTSS_EXTRACT_BITFIELD(x,25,4)

/** 
 * \brief
 * Selects whether to send an errored frame to the CPU extraction queue or
 * to a front port. See CPU_ERR_QU for details about error conditions.
 * 
 * Further this queue is used if LBR or LTR PDUs are extracted for a MIP.
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by CPU_ERR_QU
 * 1: Frames are sent to front port configured by CPU_ERR_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . CPU_ERR_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_CPU_ERR_EXT_PORT_ENA  VTSS_BIT(24)

/** 
 * \brief
 * Any errored frame which is extracted to the CPU is forwarded to the
 * destination indicated by this bit field.
 * Applicable frames are frames destined for the CPU extraction queue
 * CPU_ERR_QU due to the following configurations:
 * - CPU_HITME_ONCE_CCM_MEL_TOO_LOW
 * - CPU_COPY_CCM_MEL_TOO_LOW
 * - CPU_HITME_ONCE_MEL_TOO_LOW
 * - CPU_COPY_MEL_TOO_LOW
 * - MAC_ADDR_ERR_REDIR_ENA
 * 
 * Further this queue is used if LBR or LTR PDUs are extracted for a MIP.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . CPU_ERR_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_CPU_ERR_QU(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_CPU_ERR_QU     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_CPU_ERR_QU(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) DMR
 * 2) 1DM
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by DMR_CPU_QU
 * 1: Frames are sent to front port configured by DMR_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . DMR_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_DMR_EXT_PORT_ENA  VTSS_BIT(19)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . DMR_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_DMR_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,15,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_DMR_CPU_QU     VTSS_ENCODE_BITMASK(15,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_DMR_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,15,4)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) LMR
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by LMR_CPU_QU
 * 1: Frames are sent to front port configured by LMR_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . LMR_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_LMR_EXT_PORT_ENA  VTSS_BIT(14)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . LMR_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_LMR_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_LMR_CPU_QU     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_LMR_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) LBR
 * 
 * Also used for extracting RX TST frames (If TST frame handling is enabled
 * using VOE:OAM_FWD_CTRL.GENERIC_FWD_MASK(6))
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by LBR_CPU_QU
 * 1: Frames are sent to front port configured by LBR_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . LBR_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_LBR_EXT_PORT_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port
 * 
 * Also used for extracting RX TST frames (If TST frame handling is enabled
 * using VOE:OAM_FWD_CTRL.GENERIC_FWD_MASK(6))
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . LBR_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_LBR_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_LBR_CPU_QU     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_LBR_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) CCM-LM (I.e. CCM frame with counter values != 0)
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by CCM_LM_CPU_QU
 * 1: Frames are sent to front port configured by CCM_LM_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . CCM_LM_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_CCM_LM_EXT_PORT_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port to which CCM-LM
 * frames are extracted.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG . CCM_LM_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_CCM_LM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_CCM_LM_CPU_QU     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_CCM_LM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Configuring destination for CPU copied frames.
 *
 * \details
 * See description for CPU_CFG
 *
 * Register: \a OAM_MEP:COMMON:CPU_CFG_1
 */
#define VTSS_OAM_MEP_COMMON_CPU_CFG_1        VTSS_IOREG(VTSS_TO_OAM_MEP,0x1802)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) LTR
 * 2) LTM
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by LT_CPU_QU
 * 1: Frames are sent to front port configured by LT_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . LT_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LT_EXT_PORT_ENA  VTSS_BIT(24)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . LT_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LT_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_1_LT_CPU_QU     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_1_LT_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) DMM
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by DMM_CPU_QU
 * 1: Frames are sent to front port configured by DMM_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . DMM_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_DMM_EXT_PORT_ENA  VTSS_BIT(19)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . DMM_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_DMM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,15,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_1_DMM_CPU_QU     VTSS_ENCODE_BITMASK(15,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_1_DMM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,15,4)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) LMM
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by LMM_CPU_QU
 * 1: Frames are sent to front port configured by LMM_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . LMM_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LMM_EXT_PORT_ENA  VTSS_BIT(14)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . LMM_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LMM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_1_LMM_CPU_QU     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_1_LMM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) LBM
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by LBM_CPU_QU
 * 1: Frames are sent to front port configured by LBM_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . LBM_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LBM_EXT_PORT_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . LBM_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_LBM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_1_LBM_CPU_QU     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_1_LBM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * This bit field configures the destination for the following OAM PDUs in
 * case they are extracted to the CPU:
 * 
 * 1) CCM (I.e. CCM frame with counter values = 0)
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . CCM_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_CCM_EXT_PORT_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port to which CCM frames
 * are extracted.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CPU_CFG_1 . CCM_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_CPU_CFG_1_CCM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OAM_MEP_COMMON_CPU_CFG_1_CCM_CPU_QU     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_OAM_MEP_COMMON_CPU_CFG_1_CCM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Service policer selection
 *
 * \details
 * Register: \a OAM_MEP:COMMON:OAM_SDLB_CPU_COPY
 */
#define VTSS_OAM_MEP_COMMON_OAM_SDLB_CPU_COPY  VTSS_IOREG(VTSS_TO_OAM_MEP,0x1803)

/** 
 * \brief
 * Selected OAM frames which are forwarded to the CPU pass through this
 * register. 
 * 
 * The OAM frames for which this S-DLB is applied depend on whether the VOE
 * is configured for Down-MEP or Up-MEP.
 * 
 * Further it depends on the loopback mode configured for the VOE.
 * 
 * Description is to be updated.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_OAM_SDLB_CPU_COPY . OAM_SDLB_CPU_IDX
 */
#define  VTSS_F_OAM_MEP_COMMON_OAM_SDLB_CPU_COPY_OAM_SDLB_CPU_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_OAM_MEP_COMMON_OAM_SDLB_CPU_COPY_OAM_SDLB_CPU_IDX     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_OAM_MEP_COMMON_OAM_SDLB_CPU_COPY_OAM_SDLB_CPU_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Generic OAM PDU OpCodes configuration
 *
 * \details
 * Down-MEP:
 * The VOE supports eight generic OpCodes, which can be extracted to the
 * CPU or forwarded independently of other OpCodes. An OpCode which is not
 * explicitly supported and which is not configured as a generic OpCode is
 * treated as an unknown OpCode. 
 * 
 * The configuration of Generic OpCodes is global across all the VOEs.
 * 
 * The extraction and forwarding of generic OpCodes can be configured
 * individually per VOE.
 * 
 * Note that VOE.OAM_FWD_CTRL.OAM_FWD_MASK(6) is reserved for enabling TST
 * HW processing in the VOE. Hence if forwarding of Generic OpCode(6) is to
 * be used, there must not be TST frames in the frame flow to be handled by
 * the VOE.
 * 
 * Up-MEP:
 * GenericOpcode(8 - 1) is reserved for special use and cannot be used by
 * the user. Other generic OpCodes can be used to select OAM PDUs which
 * should be handled as data for SLA testing. This is intended to be used
 * for TST frames.
 *
 * Register: \a OAM_MEP:COMMON:OAM_GENERIC_CFG
 *
 * @param ri Replicator: x_NUM_OAM_MEP_OPCODES (??), 0-7
 */
#define VTSS_OAM_MEP_COMMON_OAM_GENERIC_CFG(ri)  VTSS_IOREG(VTSS_TO_OAM_MEP,0x1804 + (ri))

/** 
 * \brief
 * Configures if GENERIC_OPCODE_CPU_QU is a CPU extraction queue or a front
 * port
 *
 * \details 
 * 0: Frames are sent to CPU extraction queue configured by
 * GENERIC_OPCODE_CPU_QU
 * 1: Frames are sent to front port configured by GENERIC_OPCODE_CPU_QU.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_OAM_GENERIC_CFG . GENERIC_OPCODE_EXT_PORT_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_EXT_PORT_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Configures CPU extraction queue or external CPU port, according to the
 * configuration of bit field:
 * GENERIC_OPCODE_EXT_PORT_ENA
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_OAM_GENERIC_CFG . GENERIC_OPCODE_CPU_QU
 */
#define  VTSS_F_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Each OpCode value is handled according to the used replication index.
 * 
 * Handling is enabled by the corresponding VOE configuration:
 * VOE:OAM_CPU_COPY_CTRL:GENERIC_COPY_MASK
 * VOE:OAM_FWD_CTRL:GENERIC_FWD_MASK
 * VOE:OAM_CNT_OAM_CTRL:GENERIC_OAM_CNT_MASK
 * VOE:OAM_CNT_DATA_CTRL:GENERIC_DATA_CNT_MASK

 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_OAM_GENERIC_CFG . GENERIC_OPCODE_VAL
 */
#define  VTSS_F_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * If this bit is asserted, the DMAC check is disabled for this generic
 * OpCode, regardless of the configuration of the bit field:
 * 
 *   VOE:BASIC_CTRL.RX_DMAC_CHK_SEL
 *
 * \details 
 * 0: Perform DMAC check according to the value configured in:
 * VOE:BASIC_CTRL.RX_DMAC_CHK_SEL
 * 1: No DMAC for this Generic OpCode.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_OAM_GENERIC_CFG . GENERIC_DMAC_CHK_DIS
 */
#define  VTSS_F_OAM_MEP_COMMON_OAM_GENERIC_CFG_GENERIC_DMAC_CHK_DIS  VTSS_BIT(17)


/** 
 * \brief Configures time the the different CCM periods
 *
 * \details
 * 7 Independent timers are implemented to be used with the Loss of
 * Continuity (LOC) scan.
 * 
 * This register implements the timout period for every one of the 7 LOC
 * counters.
 * The timeout period is specified in the number of CCM base ticks between
 * every LOC timeout.
 * 
 * For configuration of the CCM base tick, see bit field:
 *  - CCM_CTRL.CCM_BASE_TICK_CNT
 * 
 * The default value for the CCM base tick is 198,4 ns, which means that
 * the LOC timer counters are incremented every 198,4 ns.
 * 
 * A VOE can be configured for LOC checking based on one of the 7 timeout
 * counters.
 * When the timeout counter configured for a VOE has timed out 3 times
 * without a CCM frame being received, the LOC interrupt is asserted.

 *
 * Register: \a OAM_MEP:COMMON:CCM_PERIOD_CFG
 *
 * @param ri Register: CCM_PERIOD_CFG (??), 0-6
 */
#define VTSS_OAM_MEP_COMMON_CCM_PERIOD_CFG(ri)  VTSS_IOREG(VTSS_TO_OAM_MEP,0x180c + (ri))


/** 
 * \brief CCM scan configuration
 *
 * \details
 * Configures CCM hardware scan

 *
 * Register: \a OAM_MEP:COMMON:CCM_CTRL
 */
#define VTSS_OAM_MEP_COMMON_CCM_CTRL         VTSS_IOREG(VTSS_TO_OAM_MEP,0x1813)

/** 
 * \brief
 * Specifies the number of system clock cycles for each CCM base time tick.
 * The current system clock of Serval is 6.4 ns (156 MHz)
 * 
 * With the current default setting (=31), the CCM base time tick occurs
 * every 198.4 ns.
 * 
 * For every CCM base time tick, the 7 LOC counters, are incremented. 
 * 
 * The Period of the 7 LOC counters are specified in register:
 *  - COMMON:CCM_PERIOD_VAL
 *
 * \details 
 * 0: Disable automatic HW scan
 * 1: One clock between interval increment
 * ...
 * n: n clock between interval increment
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CCM_CTRL . CCM_BASE_TICK_CNT
 */
#define  VTSS_F_OAM_MEP_COMMON_CCM_CTRL_CCM_BASE_TICK_CNT(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_OAM_MEP_COMMON_CCM_CTRL_CCM_BASE_TICK_CNT     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_OAM_MEP_COMMON_CCM_CTRL_CCM_BASE_TICK_CNT(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Specifies the number of clk cycle before another scan entry can be
 * attempted.
 * 
 * This can be used to space the LOC scanning of the VOEs
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_CCM_CTRL . CCM_SPACE_BETWEEN_ENTRY_SCAN
 */
#define  VTSS_F_OAM_MEP_COMMON_CCM_CTRL_CCM_SPACE_BETWEEN_ENTRY_SCAN(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_OAM_MEP_COMMON_CCM_CTRL_CCM_SPACE_BETWEEN_ENTRY_SCAN     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_OAM_MEP_COMMON_CCM_CTRL_CCM_SPACE_BETWEEN_ENTRY_SCAN(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Specifies an instant CCM miss count increment for this type (once
 * current scan completes, which can be ensured using
 * CCM_FORCE_HW_SCAN_STOP_ENA).
 * 
 * The bit is cleared by HW when increment is complete
 *
 * \details 
 * 0: No force
 * x1x: Force one CCM miss count increment for that type
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CCM_CTRL . CCM_FORCE_HW_SCAN_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CCM_CTRL_CCM_FORCE_HW_SCAN_ENA(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_OAM_MEP_COMMON_CCM_CTRL_CCM_FORCE_HW_SCAN_ENA     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_OAM_MEP_COMMON_CCM_CTRL_CCM_FORCE_HW_SCAN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Forces stop of current CCM miss count scan.

 *
 * \details 
 * 0: No force
 * 1: Force stop of current CCM miss count scan
 * 
 * The bit is cleared by HW when scan stop is complete
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CCM_CTRL . CCM_FORCE_HW_SCAN_STOP_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_CCM_CTRL_CCM_FORCE_HW_SCAN_STOP_ENA  VTSS_BIT(0)


/** 
 * \brief CCM scan diagnostic
 *
 * \details
 * Sticky bits indicate the current status of the LOC scanning.
 *
 * Register: \a OAM_MEP:COMMON:CCM_SCAN_STICKY
 */
#define VTSS_OAM_MEP_COMMON_CCM_SCAN_STICKY  VTSS_IOREG(VTSS_TO_OAM_MEP,0x1814)

/** 
 * \brief
 * High when CCM miss count scan is ongoing.
 *
 * \details 
 * 0: No event has occured
 * 1: CCM Miss count scan ongoing.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CCM_SCAN_STICKY . CCM_SCAN_ONGOING_STATUS
 */
#define  VTSS_F_OAM_MEP_COMMON_CCM_SCAN_STICKY_CCM_SCAN_ONGOING_STATUS(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_OAM_MEP_COMMON_CCM_SCAN_STICKY_CCM_SCAN_ONGOING_STATUS     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_OAM_MEP_COMMON_CCM_SCAN_STICKY_CCM_SCAN_ONGOING_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/** 
 * \brief
 * Set when CCM_SCAN completes.
 *
 * \details 
 * 0: No event has occured
 * 1: CCM miss count scan completed
 * 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CCM_SCAN_STICKY . CCM_SCAN_COMPLETED_STICKY
 */
#define  VTSS_F_OAM_MEP_COMMON_CCM_SCAN_STICKY_CCM_SCAN_COMPLETED_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * Set when CCM_SCAN starts.
 *
 * \details 
 * 0: No event has occured
 * 1: CCM miss count scan started
 * 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CCM_SCAN_STICKY . CCM_SCAN_STARTED_STICKY
 */
#define  VTSS_F_OAM_MEP_COMMON_CCM_SCAN_STICKY_CCM_SCAN_STARTED_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Set when a CCM scan could not start because a scan is already ongoing. 
 * The confgured Period time in OMA_MEP:CCM_PERIOD must be incremented.
 *
 * \details 
 * 0: No event has occured
 * 1: Scan could not start in time
 * 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_CCM_SCAN_STICKY . CCM_SCAN_START_DELAYED_STICKY
 */
#define  VTSS_F_OAM_MEP_COMMON_CCM_SCAN_STICKY_CCM_SCAN_START_DELAYED_STICKY  VTSS_BIT(0)


/** 
 * \brief Interrupt control
 *
 * \details
 * This is the combined interrupt output from the VOP.
 * 
 * To determine the VOE source of the interrupt, read register
 * OAM_MEP::INTR.
 *
 * Register: \a OAM_MEP:COMMON:MASTER_INTR_CTRL
 */
#define VTSS_OAM_MEP_COMMON_MASTER_INTR_CTRL  VTSS_IOREG(VTSS_TO_OAM_MEP,0x1815)

/** 
 * \brief
 * Status of the combined interrupt in the VOP.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_MASTER_INTR_CTRL . OAM_MEP_INTR
 */
#define  VTSS_F_OAM_MEP_COMMON_MASTER_INTR_CTRL_OAM_MEP_INTR  VTSS_BIT(8)

/** 
 * \brief
 * Configures if OAM_MEP_INTR interrupts the CPU.
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_COMMON_MASTER_INTR_CTRL . OAM_MEP_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA  VTSS_BIT(25)


/** 
 * \brief VOE interrupt
 *
 * \details
 * Interrupt per VOE. To enable interrupts out of the VOP, see
 * MASTER_INTR_CTRL.
 *
 * Register: \a OAM_MEP:COMMON:INTR
 *
 * @param ri Replicator: x_NUM_TOTAL_VOE_DIV32_CEIL (??), 0-2
 */
#define VTSS_OAM_MEP_COMMON_INTR(ri)         VTSS_IOREG(VTSS_TO_OAM_MEP,0x1816 + (ri))


/** 
 * \brief Down-MEP or Up-MEP configuration
 *
 * \details
 * Register: \a OAM_MEP:COMMON:VOE_CFG
 *
 * @param ri Replicator: x_NUM_VOE (??), 0-63
 */
#define VTSS_OAM_MEP_COMMON_VOE_CFG(ri)      VTSS_IOREG(VTSS_TO_OAM_MEP,0x1819 + (ri))

/** 
 * \brief
 * Configure whether the VOE is implementing an Up-MEP or Down-MEP.
 *
 * \details 
 * 0: VOE implements Down-MEP
 * 1: VOE implements Up-MEP
 *
 * Field: ::VTSS_OAM_MEP_COMMON_VOE_CFG . UPMEP_VOE
 */
#define  VTSS_F_OAM_MEP_COMMON_VOE_CFG_UPMEP_VOE  VTSS_BIT(0)


/** 
 * \brief Up-MEP counter configuration
 *
 * \details
 * For Up-MEP, the LM counter values cannot be stored into the OAM frame
 * IFH and forwarded to the CPU. Instead the counter values are sampled
 * when the Rx LM OAM PDU is received by the VOE and they must be read by
 * SW. For each of the LM OAM PDUs supported, the corresponding fields in
 * this register indicate whether there is an LM counter value ready for
 * reading.
 *
 * Register: \a OAM_MEP:COMMON:UPMEP_LM_CNT_VLD
 *
 * @param ri Replicator: x_NUM_VOE (??), 0-63
 */
#define VTSS_OAM_MEP_COMMON_UPMEP_LM_CNT_VLD(ri)  VTSS_IOREG(VTSS_TO_OAM_MEP,0x1859 + (ri))

/** 
 * \brief
 * This field is asserted by the VOE HW when an Up-MEP has sampled the RX
 * LM counter and saved the value into the following register:
 * 
 * VOE:CCM_CAP_RX_FCL.CCM_CAP_RX_FCL
 * 
 * This is done in response to receiving an CCM-LM frame.
 * 
 * The field is cleared when SW reads the counter value in the above
 * register.
 * 
 * If the CPU has not cleared this bit before the next CCM-LM frame is
 * received, the VOE asserts the following sticky bit to indicate that an
 * RX_LM sample was lost:
 * 
 * VOE:UPMEP_LM_CNT_STICKY.CCM_LM_RX_CNT_STICKY
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_UPMEP_LM_CNT_VLD . CCM_LM_RX_CNT_VLD
 */
#define  VTSS_F_OAM_MEP_COMMON_UPMEP_LM_CNT_VLD_CCM_LM_RX_CNT_VLD  VTSS_BIT(2)

/** 
 * \brief
 * This field is asserted by the VOE HW when an Up-MEP has sampled the RX
 * LM counter and saved the value into the following register:
 * 
 * VOE:UPMEP_LMR_RX_LM_CNT.UPMEP_LMR_RX_LM_CNT
 * 
 * This is done in response to receiving an LMM frame.
 * 
 * The field is cleared when CPU reads the counter value in the above
 * register.
 * 
 * If the CPU has not cleared this bit before the next LMM frame is
 * received, the VOE asserts the following sticky bit to indicate that an
 * RX_LM sample was lost.
 * 
 * VOE:UPMEP_LM_CNT_STICKY.LMM_RX_CNT_STICKY
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_UPMEP_LM_CNT_VLD . LMM_RX_CNT_VLD
 */
#define  VTSS_F_OAM_MEP_COMMON_UPMEP_LM_CNT_VLD_LMM_RX_CNT_VLD  VTSS_BIT(1)

/** 
 * \brief
 * This field is asserted by the VOE HW when an Up-MEP has sampled the RX
 * LM counter and saved the value into the following register:
 * 
 * VOE:CCM_CAP_TX_FCF.CCM_CAP_TX_FCF
 * 
 * This is done in response to receiving an LMR frame.
 * 
 * The field is cleared when CPU reads the counter value in the above
 * register.
 * 
 * If the CPU has not cleared this bit before the next LMR frame is
 * received, the VOE asserts the following sticky bit to indicate that an
 * RX_LM sample was lost:
 * 
 * VOE:UPMEP_LM_CNT_STICKY.LMR_RX_CNT_STICKY

 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_UPMEP_LM_CNT_VLD . LMR_RX_CNT_VLD
 */
#define  VTSS_F_OAM_MEP_COMMON_UPMEP_LM_CNT_VLD_LMR_RX_CNT_VLD  VTSS_BIT(0)


/** 
 * \brief Path MEP configuration
 *
 * \details
 * Configures a service VOE to be part of a path VOE data flow.
 * 
 * When a path VOE is assigned to a service VOE, it causes all data on the
 * service VOE (including data and OAM PDUs) to be counted as data in the
 * path VOE's LM counters.
 *
 * Register: \a OAM_MEP:COMMON:VOE_MAP_CTRL
 *
 * @param ri Replicator: x_NUM_VOE (??), 0-63
 */
#define VTSS_OAM_MEP_COMMON_VOE_MAP_CTRL(ri)  VTSS_IOREG(VTSS_TO_OAM_MEP,0x1899 + (ri))

/** 
 * \brief
 * Configures the associated working path VOE
 * 
 * Must be enabled by PATH_VOEID_ENA.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_VOE_MAP_CTRL . PATH_VOEID
 */
#define  VTSS_F_OAM_MEP_COMMON_VOE_MAP_CTRL_PATH_VOEID(x)  VTSS_ENCODE_BITFIELD(x,7,6)
#define  VTSS_M_OAM_MEP_COMMON_VOE_MAP_CTRL_PATH_VOEID     VTSS_ENCODE_BITMASK(7,6)
#define  VTSS_X_OAM_MEP_COMMON_VOE_MAP_CTRL_PATH_VOEID(x)  VTSS_EXTRACT_BITFIELD(x,7,6)

/** 
 * \brief
 * Configures the associated PROTECT path VOE when a service is protected.
 * 
 * This is used if the associated service is protected via the IPT table
 * (ANA:IPT:IPT_CFG)
 * 
 * Must be enabled by PATH_VOEID_ENA.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_VOE_MAP_CTRL . PATH_VOEID_P
 */
#define  VTSS_F_OAM_MEP_COMMON_VOE_MAP_CTRL_PATH_VOEID_P(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_OAM_MEP_COMMON_VOE_MAP_CTRL_PATH_VOEID_P     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_OAM_MEP_COMMON_VOE_MAP_CTRL_PATH_VOEID_P(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * Configures if a service MEP is part of a path MEP data.
 *
 * \details 
 * 0: No path VOE is assigned to the service VOE
 * 1: A path VOE is assigned to the service VOE.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_VOE_MAP_CTRL . PATH_VOEID_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_VOE_MAP_CTRL_PATH_VOEID_ENA  VTSS_BIT(0)


/** 
 * \brief MEP performance counter configuration
 *
 * \details
 * Configures the LM counters per VOE.
 *
 * Register: \a OAM_MEP:COMMON:VOE_CNT_CTRL
 *
 * @param ri Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_COMMON_VOE_CNT_CTRL(ri)  VTSS_IOREG(VTSS_TO_OAM_MEP,0x18d9 + (ri))

/** 
 * \brief
 * Configures if yellow frames are included in the LM counters.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_VOE_CNT_CTRL . CNT_YELLOW_ENA
 */
#define  VTSS_F_OAM_MEP_COMMON_VOE_CNT_CTRL_CNT_YELLOW_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Configures if priorities are counted separately or as priority 7.
 * 
 * Each bit in the bit field represents a priority.
 * 
 * If a priority bit is set in the MASK, frames with the corresponding
 * priority are counted in a separate priority counter.
 * 
 * If priority bit is not set in MASK the priority is counted as priority
 * 7.
 *
 * \details 
 * 0: Priority is counted in priority 7 of the performance counters
 * 1: Priority is counted separately in the performance counters.
 *
 * Field: ::VTSS_OAM_MEP_COMMON_VOE_CNT_CTRL . PRIO_CNT_MASK
 */
#define  VTSS_F_OAM_MEP_COMMON_VOE_CNT_CTRL_PRIO_CNT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_OAM_MEP_COMMON_VOE_CNT_CTRL_PRIO_CNT_MASK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_OAM_MEP_COMMON_VOE_CNT_CTRL_PRIO_CNT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief OAM MEP multicast MAC address configuration (LSB)
 *
 * \details
 * Each VOE can be addressed using either a common multicast MAC address or
 * a VOE specific unicast MAC address.
 * 
 * This register configures the multicast address common to all the VOEs.
 * 
 * The full MAC address is a concatenation of the folliowing registers:
 * 1) COMMON:COMMON_MEP_MC_MAC_LSB
 * 2) COMMON:COMMON_MEP_MC_MAC_MSB
 * 
 * The DMAC check to be performed for each VOE is configured in
 * VOE:BASIC_CTRL.RX_DMAC_CHK_SEL.
 *
 * Register: \a OAM_MEP:COMMON:COMMON_MEP_MC_MAC_LSB
 */
#define VTSS_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_LSB  VTSS_IOREG(VTSS_TO_OAM_MEP,0x1924)

/** 
 * \brief
 * Common VOE multicast Address - LSB
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_LSB . MEP_MC_MAC_LSB
 */
#define  VTSS_F_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB(x)  VTSS_ENCODE_BITFIELD(x,3,28)
#define  VTSS_M_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB     VTSS_ENCODE_BITMASK(3,28)
#define  VTSS_X_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB(x)  VTSS_EXTRACT_BITFIELD(x,3,28)


/** 
 * \brief OAM MEP multicast MAC address configuration (MSB)
 *
 * \details
 * Common VOE multicast Address - MSB
 *
 * Register: \a OAM_MEP:COMMON:COMMON_MEP_MC_MAC_MSB
 */
#define VTSS_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_MSB  VTSS_IOREG(VTSS_TO_OAM_MEP,0x1925)

/** 
 * \brief
 * Common VOE multicast Address - MSB
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_MSB . MEP_MC_MAC_MSB
 */
#define  VTSS_F_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_OAM_MEP_COMMON_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a OAM_MEP:VOE
 *
 * Configuration per Vitesse OAM MEP Endpoints (VOE)
 */


/** 
 * \brief Configures miscellaneous parameters
 *
 * \details
 * Basic VOE configuration.
 *
 * Register: \a OAM_MEP:VOE:BASIC_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_BASIC_CTRL(gi)      VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,0)

/** 
 * \brief
 * Configures if frames failing the DMAC check should be redirected to the
 * CPU extraction queue OAM_MEP::CPU_CFG.CPU_ERR_QU.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . MAC_ADDR_ERR_REDIR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_MAC_ADDR_ERR_REDIR_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Configures the DA check performed when received from the peer MEP.
 * 
 * This check can be disabled for Generic OpCodes. 
 * See COMMON:OAM_GENERIC_CFG.GENERIC_DMAC_CHK_DIS

 *
 * \details 
 * 0: No DMAC check
 * 1: Check DMAC against MEP_UC_MAC_MSB and MEP_UC_MAC_LSB
 * 2: Check DMAC against MEP_MC_MAC_MSB and MEP_MC_MAC_LSB
 * 3: Check DMAC against either MEP_UC_MAC_MSB and MEP_UC_MAC_LSB or
 * MEP_MC_MAC_MSB and MEP_MC_MAC_LSB
 *
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . RX_DMAC_CHK_SEL
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_RX_DMAC_CHK_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_OAM_MEP_VOE_BASIC_CTRL_RX_DMAC_CHK_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_OAM_MEP_VOE_BASIC_CTRL_RX_DMAC_CHK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * 802.1ag specifies that CCM frames may have more than one TLV. 
 * 
 * This bit field allows the next CCM frame with Second TLV to CPU. 
 * (IEEE802.1AG relevant only).
 * 
 * Frames extracted to the CPU based on this setting are forwarded to CPU
 * extraction queue:
 * COMMON:CPU_CFG.DEF_EXT_PORT_ENA / 
 * COMMON:CPU_CFG.DEF_COPY_QU
 *
 * \details 
 * 0: Disable (no CPU hitme once copy)
 * 1: Enable the next CCM_PDU with a second TLV to be sent to CPU.
 * 
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . CPU_HITME_ONCE_CCM_TLV
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_CPU_HITME_ONCE_CCM_TLV  VTSS_BIT(7)

/** 
 * \brief
 * Send next CCM frame that fails the required check to CPU configured in
 * OAM_MEP::CPU_CFG.CPU_ERR_QU.
 *
 * \details 
 * 0: Disable (no CPU hitme once copy)
 * 1: Enable the next frame failing the CCM PDU check to be sent to CPU.
 * 
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . CCM_ERR_CPU_HITME_ONCE
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_CCM_ERR_CPU_HITME_ONCE  VTSS_BIT(6)

/** 
 * \brief
 * Configures if CCM frame failing the required check is sent to CPU
 * configured in OAM_MEP::CPU_CFG.CPU_ERR_QU.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . CCM_ERR_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_CCM_ERR_CPU_COPY_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Extract next CCM or CCM-LM OAM PDU frame to CPU according to
 * configuration in OAM_MEP::CCM_CFG_1.CCM_CPU_QU
 *
 * \details 
 * 0: Disable (no CPU hitme once copy)
 * 1: Enable the next frame to be sent to CPU.
 * 
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . CCM_NXT_CPU_HITME_ONCE
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_CCM_NXT_CPU_HITME_ONCE  VTSS_BIT(4)

/** 
 * \brief
 * Configures the VOE only make CPU copy of unicast DMAC addresses.
 *
 * \details 
 * 0: Allows unicast and multicast copy handling
 * 1: Allows only unicast copy handling (MIP)
 *
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . MIP_UNICAST_ONLY_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_MIP_UNICAST_ONLY_COPY_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Down-MEP only (Must be = 0 for Up-MEP)
 * Configures the VOE to be a MIP.
 *
 * \details 
 * 0: Allows MEP handling
 * 1: Enable MIP handling
 *
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . VOE_AS_MIP_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_AS_MIP_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Configures if MEP is active or not.
 *
 * \details 
 * 0: Disable MEP handling
 * 1: Enable MEP handling
 *
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . VOE_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_VOE_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Up-MEP only (Has not effect on Down-MEP)
 * Asserting this bit causes all DATA RX frames received at the Up-MEP to
 * be discarded.
 * 
 * OAM frames are unaffected by this setting and they may be looped or
 * extracted as is standard for every PDU type.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_BASIC_CTRL . UPMEP_KILL_ALL_RX
 */
#define  VTSS_F_OAM_MEP_VOE_BASIC_CTRL_UPMEP_KILL_ALL_RX  VTSS_BIT(0)


/** 
 * \brief Configures handles in relation to MEL
 *
 * \details
 * VOE configuration related to MEL checking.
 *
 * Register: \a OAM_MEP:VOE:MEL_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_MEL_CTRL(gi)        VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,1)

/** 
 * \brief
 * This register configures the MEL value for the VOE. OAM PDUs with MEL
 * above this MEL_VAL are not effected. OAM PDUs with MEL equal to this
 * MEL_VAL are optionally handled by HW or copied to CPU.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_MEL_CTRL . MEL_VAL
 */
#define  VTSS_F_OAM_MEP_VOE_MEL_CTRL_MEL_VAL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_OAM_MEP_VOE_MEL_CTRL_MEL_VAL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_OAM_MEP_VOE_MEL_CTRL_MEL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/** 
 * \brief
 * When VOE is configured as an Up-MEP, it can run in two modes:
 * 
 * 1) In-service - in this configuration there is customer traffic on the
 * service. This configuration does implement HW support for loopback of
 * OAM frames.
 * 2) Loopback - in this configuration there are no costumer frames in the
 * service. This configuration implements HW loopback of OAM frames.
 * 
 * Note:
 * This bit is not used when the VOE is configured for Down-MEP
 *
 * \details 
 * 0: In-service (No HW loopback)
 * 1: Loopback (HW loopback)
 *
 * Field: ::VTSS_OAM_MEP_VOE_MEL_CTRL . UPMEP_LB
 */
#define  VTSS_F_OAM_MEP_VOE_MEL_CTRL_UPMEP_LB  VTSS_BIT(16)

/** 
 * \brief
 * For VOE configured for Up-MEP operation, this register points to the
 * front port where the Up-MEP is located.
 * For VOE configured for Down-MEP, this register is not used.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_MEL_CTRL . MEP_PORTMASK
 */
#define  VTSS_F_OAM_MEP_VOE_MEL_CTRL_MEP_PORTMASK(x)  VTSS_ENCODE_BITFIELD(x,5,11)
#define  VTSS_M_OAM_MEP_VOE_MEL_CTRL_MEP_PORTMASK     VTSS_ENCODE_BITMASK(5,11)
#define  VTSS_X_OAM_MEP_VOE_MEL_CTRL_MEP_PORTMASK(x)  VTSS_EXTRACT_BITFIELD(x,5,11)

/** 
 * \brief
 * Configures if the first OAM PDU (exclusing CCM) discarded due to a MEL
 * too low is copied to the CPU extraction queue configured in
 * OAM_MEP::CPU_CFG.CPU_ERR_QU.
 *
 * \details 
 * 0: Disable (no CPU hit me once copy)
 * 1: Enable the next frame failing the MEL check to be sent to CPU 
 * 
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_OAM_MEP_VOE_MEL_CTRL . CPU_HITME_ONCE_MEL_TOO_LOW
 */
#define  VTSS_F_OAM_MEP_VOE_MEL_CTRL_CPU_HITME_ONCE_MEL_TOO_LOW  VTSS_BIT(3)

/** 
 * \brief
 * Configures if OAM PDUs (exclusing CCM) failing the MEL check (MEL too
 * low) are copied to the CPU extraction queue configured in
 * OAM_MEP::CPU_CFG.CPU_ERR_QU.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_MEL_CTRL . CPU_COPY_MEL_TOO_LOW
 */
#define  VTSS_F_OAM_MEP_VOE_MEL_CTRL_CPU_COPY_MEL_TOO_LOW  VTSS_BIT(2)

/** 
 * \brief
 * Configures if the first OAM CCM PDU discarded due to a MEL too low is
 * copied to the CPU extraction queue configured in
 * OAM_MEP::CPU_CFG.CPU_ERR_QU.
 *
 * \details 
 * 0: Disable (no CPU hit me once copy)
 * 1: Enable the next frame failing the MEL check to be sent to CPU 
 * 
 * The bit is cleared by HW when a CPU copy has been made.
 *
 * Field: ::VTSS_OAM_MEP_VOE_MEL_CTRL . CPU_HITME_ONCE_CCM_MEL_TOO_LOW
 */
#define  VTSS_F_OAM_MEP_VOE_MEL_CTRL_CPU_HITME_ONCE_CCM_MEL_TOO_LOW  VTSS_BIT(1)

/** 
 * \brief
 * Configures if OAM CCM PDUs failing the MEL check (MEL too low) are
 * copied to the CPU extraction queue configured in
 * OAM_MEP::CPU_CFG.CPU_ERR_QU.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_MEL_CTRL . CPU_COPY_CCM_MEL_TOO_LOW
 */
#define  VTSS_F_OAM_MEP_VOE_MEL_CTRL_CPU_COPY_CCM_MEL_TOO_LOW  VTSS_BIT(0)


/** 
 * \brief Configuration of CPU copy for the supported OAM PDU OpCodes
 *
 * \details
 * Configures CPU copy for the supported OAM PDU OpCodes. This CPU copy
 * functionality operates independently of OAM_FWD_CTRL
 *
 * Register: \a OAM_MEP:VOE:OAM_CPU_COPY_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,2)

/** 
 * \brief
 * Enable / disable CPU copy of Generic OpCode configured in
 * OAM_MEP::OAM_GENERIC_CFG
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . GENERIC_COPY_MASK
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_GENERIC_COPY_MASK(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_GENERIC_COPY_MASK     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_GENERIC_COPY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,8)

/** 
 * \brief
 * Configures CPU copy of all non specific and generic OpCodes
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . UNK_OPCODE_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_UNK_OPCODE_CPU_COPY_ENA  VTSS_BIT(11)

/** 
 * \brief
 * CPU copy of OAM LTM PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . LTM_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA  VTSS_BIT(10)

/** 
 * \brief
 * CPU copy of OAM LTR PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . LTR_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA  VTSS_BIT(9)

/** 
 * \brief
 * CPU copy of OAM LMM PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . LMM_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LMM_CPU_COPY_ENA  VTSS_BIT(8)

/** 
 * \brief
 * CPU copy of OAM LMR PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . LMR_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LMR_CPU_COPY_ENA  VTSS_BIT(7)

/** 
 * \brief
 * CPU copy of OAM LBM PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . LBM_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA  VTSS_BIT(6)

/** 
 * \brief
 * CPU copy of OAM LBR PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . LBR_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA  VTSS_BIT(5)

/** 
 * \brief
 * CPU copy of OAM DMM PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . DMM_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_DMM_CPU_COPY_ENA  VTSS_BIT(4)

/** 
 * \brief
 * CPU copy of OAM DMR PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . DMR_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_DMR_CPU_COPY_ENA  VTSS_BIT(3)

/** 
 * \brief
 * CPU copy of OAM 1DM PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . SM_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_SM_CPU_COPY_ENA  VTSS_BIT(2)

/** 
 * \brief
 * CPU copy of OAM CCM PDU.
 *
 * \details 
 * 0: No CPU copy
 * 1: Copy to CPU
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . CCM_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA  VTSS_BIT(1)

/** 
 * \brief
 * CPU copy of OAM CCM-LM PDU.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CPU_COPY_CTRL . CCM_LM_CPU_COPY_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CPU_COPY_CTRL_CCM_LM_CPU_COPY_ENA  VTSS_BIT(0)


/** 
 * \brief Configuration forwarding for the supported OAM PDU OpCodes
 *
 * \details
 * Configures CPU forwarding for the supported OAM PDU OpCodes. This
 * forwarding functionality operates independently of OAM_CPU_COPY_CTRL.
 * 
 * This can be used to allow forwarding of OAM PDUs which would normally be
 * stopped by the Rx or Tx MEL check.
 * 
 * The only currently know use for this is Ring PDU (OpCode: 40)
 *
 * Register: \a OAM_MEP:VOE:OAM_FWD_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_OAM_FWD_CTRL(gi)    VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,3)

/** 
 * \brief
 * Enable / disable forwarding of Generic OpCode configured in
 * OAM_MEP::OAM_GENERIC_CFG
 * 
 * Bit (6) is reserved for special purpose.
 * This bit is used to enable TST frame processing by the VOE.
 * Hence generic OpCode(6) should not be used for other purposes.
 *
 * \details 
 * 0x:x No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * x1x: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . GENERIC_FWD_MASK
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_GENERIC_FWD_MASK(x)  VTSS_ENCODE_BITFIELD(x,11,8)
#define  VTSS_M_OAM_MEP_VOE_OAM_FWD_CTRL_GENERIC_FWD_MASK     VTSS_ENCODE_BITMASK(11,8)
#define  VTSS_X_OAM_MEP_VOE_OAM_FWD_CTRL_GENERIC_FWD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,8)

/** 
 * \brief
 * Forwarding of OAM LTM PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . LTM_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_LTM_FWD_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Forwarding of OAM LTR PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . LTR_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_LTR_FWD_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Forwarding of OAM LMM PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . LMM_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_LMM_FWD_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Forwarding of OAM LMR PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . LMR_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_LMR_FWD_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Forwarding of OAM LBM PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . LBM_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_LBM_FWD_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Forwarding of OAM LBR PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . LBR_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_LBR_FWD_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Forwarding of OAM DMM PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . DMM_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_DMM_FWD_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Forwarding of OAM DMR PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . DMR_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_DMR_FWD_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Forwarding of OAM 1DM PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . SM_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_SM_FWD_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Forwarding of OAM CCM PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . CCM_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_CCM_FWD_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Forwarding of OAM CCM-LM PDU.
 *
 * \details 
 * 0: No forwarding of frames with MEL matching MEL_CTRL.MEL_VAL
 * 1: Allow forwarding
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_FWD_CTRL . CCM_LM_FWD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_FWD_CTRL_CCM_LM_FWD_ENA  VTSS_BIT(0)


/** 
 * \brief Override S-DLB for OAM frames
 *
 * \details
 * It is possible to override the SDLB for the OAM frames not counted as
 * data frames.
 * 
 * I.e. if service DLB overriding is enabled, the SDLB for OAM frames, not
 * selected to be counted as data frames by register OAM_CNT_DATA_CTRL, is
 * overwritten by the S-DLB value configured in OAM_SDLB_IDX.
 *
 * Register: \a OAM_MEP:VOE:OAM_SDLB_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_OAM_SDLB_CTRL(gi)   VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,4)

/** 
 * \brief
 * Enable overriding the S-DLB for OAM frames not counted as data frames.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_SDLB_CTRL . OAM_SDLB_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_SDLB_CTRL_OAM_SDLB_ENA  VTSS_BIT(10)

/** 
 * \brief
 * If enabled by OAM_SDLB_ENA, the S-DLB for OAM frames are overwritten by
 * this value.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_SDLB_CTRL . OAM_SDLB_IDX
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_SDLB_CTRL_OAM_SDLB_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_OAM_MEP_VOE_OAM_SDLB_CTRL_OAM_SDLB_IDX     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_OAM_MEP_VOE_OAM_SDLB_CTRL_OAM_SDLB_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Configuration whech OAM PDU are to be included in selected counter
 *
 * \details
 * The OAM frames handled by the VOE can be counted separately in Rx and Tx
 * direction.
 * In each direction there are two counters:
 * 
 * 1) Default OAM counter
 * This counter counts all the PDU types which are not selected using the
 * OAM_CNT_OAM_CTRL register:
 * 
 *  - RX_OAM_FRM_CNT
 *  - TX_OAM_FRM_CNT
 * 
 * 2) Selected OAM counter:
 * This counter counts all the PDU types selected for counting using the
 * OAM_CNT_OAM_CTRL register:
 * 
 *  - RX_SEL_OAM_CNT
 *  - TX_SEL_OAM_CNT
 * 
 * Any OAM PDU is counted in exactly one of the above registers.
 * 
 * I.e. as default all OAM PDUs are not selected, and they are all counted
 * in the default OAM counters: RX / TX _ OAM_FRM_CNT.
 * 
 * Using this register (OAM_CNT_OAM_CTRL), PDUs can be moved to the
 * selected coutners:
 * RX / TX SEL_OAM_CNT.
 * 
 * The selection of OAM PDUs for the selected counter is done commonly for
 * the Tx and Rx direction.
 *
 * Register: \a OAM_MEP:VOE:OAM_CNT_OAM_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,5)

/** 
 * \brief
 * Enable / disable count as selected OAM of Generic OpCodes per MEP per
 * generic OpCode.
 *
 * \details 
 * x0x: Count as other OAM
 * x1x: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . GENERIC_OAM_CNT_MASK
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,8)

/** 
 * \brief
 * Enable / disable count as selected OAM for all non specific and generic
 * OpCodes
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . UNK_OPCODE_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_UNK_OPCODE_OAM_CNT_ENA  VTSS_BIT(11)

/** 
 * \brief
 * Enable / disable count of OAM PDU LTM as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . LTM_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Enable / disable count of OAM PDU LTR as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . LTR_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Enable / disable count of OAM PDU LMM as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . LMM_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LMM_OAM_CNT_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable / disable count of OAM PDU LMR as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . LMR_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LMR_OAM_CNT_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Enable / disable count of OAM PDU LBM as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . LBM_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Enable / disable count of OAM PDU LBR as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . LBR_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Enable / disable count of OAM PDU DMM as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . DMM_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_DMM_OAM_CNT_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enable / disable count of OAM PDU DMR as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . DMR_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_DMR_OAM_CNT_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable / disable count of OAM PDU 1DM as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . SM_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_SM_OAM_CNT_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Enable / disable count of OAM PDU CCM as selected OAM.
 *
 * \details 
 * 0: Count as other OAM
 * 1: Count as selected OAM
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . CCM_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable / disable count of OAM PDU CCM with LM content as selected OAM.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_OAM_CTRL . CCM_LM_OAM_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_OAM_CTRL_CCM_LM_OAM_CNT_ENA  VTSS_BIT(0)


/** 
 * \brief Configuration of which OAM PDUs should be counted as data
 *
 * \details
 * Default behavior is that all OAM PDUs handled by a VOE (i.e. MEG levels
 * between OAM PDU and VOE must match) are not counted as data. This is
 * according to Y.1731
 * 
 * Using this register (OAM_CNT_DATA_CTRL) it is possible to configure the
 * OAM PDUs separately to be counted as data.
 * 
 * Frames are counted separately in the Rx and Tx direction.
 * 
 * The data counters are located:
 * 
 * Service VOE:
 * RX_VOE_PM.MEP_RX_FRM_CNT
 * TX_VOE_PM.MEP_TX_FRM_CNT
 * 
 * Port VOE:
 * PORT_PM.RX_FRM_CNT
 * PORT_PM.TX_FRM_CNT
 *
 * Register: \a OAM_MEP:VOE:OAM_CNT_DATA_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,6)

/** 
 * \brief
 * Enable / disable data count of Generic OpCodes per MEP per generic
 * OpCode.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . GENERIC_DATA_CNT_MASK
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_GENERIC_DATA_CNT_MASK(x)  VTSS_ENCODE_BITFIELD(x,11,8)
#define  VTSS_M_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_GENERIC_DATA_CNT_MASK     VTSS_ENCODE_BITMASK(11,8)
#define  VTSS_X_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_GENERIC_DATA_CNT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,8)

/** 
 * \brief
 * Configures data count of all non specific and generic OpCodes
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . UNK_OPCODE_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_UNK_OPCODE_DATA_CNT_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Enable / disable count of OAM PDU LTM as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . LTM_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_LTM_DATA_CNT_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Enable / disable count of OAM PDU LTR as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . LTR_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_LTR_DATA_CNT_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable / disable count of OAM PDU LMM as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . LMM_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_LMM_DATA_CNT_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Enable / disable count of OAM PDU LMR as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . LMR_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_LMR_DATA_CNT_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Enable / disable count of OAM PDU LBM as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . LBM_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_LBM_DATA_CNT_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Enable / disable count of OAM PDU LBR as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . LBR_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_LBR_DATA_CNT_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enable / disable count of OAM PDU DMM as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . DMM_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_DMM_DATA_CNT_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable / disable count of OAM PDU DMR as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . DMR_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_DMR_DATA_CNT_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Enable / disable count of OAM PDU 1DM as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . SM_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_SM_DATA_CNT_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable / disable count of OAM PDU CCM as data in performance counters.
 *
 * \details 
 * 0: Do not count as data
 * 1: Count as data
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_CNT_DATA_CTRL . CCM_DATA_CNT_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_CNT_DATA_CTRL_CCM_DATA_CNT_ENA  VTSS_BIT(0)


/** 
 * \brief OAM MEP MAC unicast address configuration (LSB)
 *
 * \details
 * Configures the VOE Unicast MAC address (LSB).
 * 
 * This address can be checked when frames arrive, depending on the
 * configuration of: 
 * VOE:BASIC_CTRL.RX_DMAC_CHK_SEL
 *
 * Register: \a OAM_MEP:VOE:MEP_UC_MAC_LSB
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_MEP_UC_MAC_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,7)


/** 
 * \brief OAM MEP MAC unicast address configuration (MSB)
 *
 * \details
 * Configures the VOE Unicast MAC address (MSB).
 * 
 * This address can be checked when frames arrive, depending on the
 * configuration of: 
 * VOE:BASIC_CTRL.RX_DMAC_CHK_SEL
 *
 * Register: \a OAM_MEP:VOE:MEP_UC_MAC_MSB
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_MEP_UC_MAC_MSB(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,8)

/** 
 * \brief
 * VOE Unicast MAC - LSB
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_MEP_UC_MAC_MSB . MEP_UC_MAC_MSB
 */
#define  VTSS_F_OAM_MEP_VOE_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_OAM_MEP_VOE_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_OAM_MEP_VOE_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief OAM handling configuration
 *
 * \details
 * Configures per OAM OpCode if it is handled by hardware.
 * 
 * Only OAM PDU types enabled in this register are subject to HW support in
 * the VOE.
 *
 * Register: \a OAM_MEP:VOE:OAM_HW_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_OAM_HW_CTRL(gi)     VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,9)

/** 
 * \brief
 * Configures if LMM is handled by the MEP.  If enabled LMM frames
 * applicable for the MEP are either looped or CPU redirected (based on
 * OAM_MEP:VOE:LOOPBACK_CTRL.LB_LMM_ENA).
 * 
 * Looped LMM frames are updated as:
 *    RxFCf, TxFCb updated with the associated Performance counters
 *    DMAC updated to received SMAC
 *    SMAC set to VOE MAC address (OAM_MEP:VOE:MEP_UC_MAC_MSB and
 * OAM_MEP:VOE:MEP_UC_MAC_LSB)
 *    OpCode changed to LMR.
 * 
 * CPU redirected frames are forwarded to CPU extraction queue or external
 * port configured OAM_MEP::CPU_CFG_1.LMM_CPU_QU and get RxFCf updated.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . LMM_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LMM_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Configures if LMR is handled by the MEP.  If enabled LMR frames
 * applicable for the MEP are CPU redirected to CPU extraction queue or
 * external port configured in OAM_MEP::CPU_CFG.LMR_CPU_QU.
 * 
 * Handled frames get RxFCl written into REW_VAL in the CPU extraction
 * header and optionally also extending the PDU with RxFCl after TxFCb
 * based on OAM_MEP::MEP_CTRL.LMR_UPD_RxFcL_ENA.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . LMR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LMR_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Configures if LBM is handled by the MEP.  If enabled LVM frames
 * applicable for the MEP are looped.
 * 
 * Looped LBM frames are updated as:
 *    DMAC updated to received SMAC
 *    SMAC set to VOE MAC address (OAM_MEP:VOE:MEP_UC_MAC_MSB and
 * OAM_MEP:VOE:MEP_UC_MAC_LSB)
 *    OpCode changed to LBR.
 * 
 * Also used to enable HW processing of Tx TST frames (If TST frame
 * handling is enabled using VOE:OAM_FWD_CTRL.GENERIC_FWD_MASK(6)).
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . LBM_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LBM_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Configures if LBR is handled by the MEP.  If enabled LBR frames
 * applicable for the MEP checking received PDU transaction ID.
 * 
 * Also used to enable HW processing of RX TST frames (If TST frame
 * handling is enabled using VOE:OAM_FWD_CTRL.GENERIC_FWD_MASK(6)).
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . LBR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_LBR_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Configures if DMM is handled by the MEP.  If enabled DMM frames
 * applicable for the MEP are either looped or CPU redirected (based on
 * OAM_MEP:VOE:LOOPBACK_CTRL.LB_DMM_ENA).
 * 
 * Looped DMM frames are updated as:
 *    RxTimeStampf, TxTimeStampb updated with the associated Performance
 * counters
 *    DMAC updated to received SMAC
 *    SMAC set to VOE MAC address (OAM_MEP:VOE:MEP_UC_MAC_MSB and
 * OAM_MEP:VOE:MEP_UC_MAC_LSB)
 *    OpCode changed to DMR.
 * 
 * CPU redirected frames are forwarded to CPU extraction queue or external
 * port configured OAM_MEP::CPU_CFG_1.DMM_CPU_QU and get RxTimeStampf
 * updated.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . DMM_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_DMM_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Configures if DMR is handled by the MEP.  If enabled DMR frames
 * applicable for the MEP are CPU redirected to CPU extraction queue or
 * external port configured in OAM_MEP::CPU_CFG.DMR_CPU_QU.
 * 
 * Handled frames get PDU RxTimeStampb updated..
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . DMR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_DMR_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Configures if 1DM is handled by the MEP.  If enabled 1DM frames
 * applicable for the MEP are CPU redirected to CPU extraction queue or
 * external port configured in OAM_MEP::CPU_CFG.DMR_CPU_QU.
 * 
 * Handled frames get PDU RxTimeStampb updated..
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . SDM_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_SDM_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Configures if CCM is handled by the MEP.  If enabled, CCM frames
 * applicable for the MEP are checked before being used for clearing
 * CCM_MISS_CNT.

 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . CCM_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_CCM_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Configures if CCM with LM information is handled by the MEP.  Requires
 * that CCM_ENA is also set.
 * 
 * Handled frames get RxFCl in written into REW_VAL in the CPU extraction
 * header and optionally also the reserved field in the PDU with RxFCl
 * based on OAM_MEP::MEP_CTRL.CCM_LM_UPD_RSV_ENA.
 * 
 * Handled frames get RxFCl and TxFCf stored to be used for next
 * transmitted CCM frame with LM information.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_HW_CTRL . CCM_LM_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_HW_CTRL_CCM_LM_ENA  VTSS_BIT(0)


/** 
 * \brief OAM loopback configuration
 *
 * \details
 * Configures Down-MEP loopback of OAM functions.
 * 
 * Loopback VOE functionality is not supported for Up-MEP configurations.
 * 
 * For Up-MEP the following bit fields have a special meaning:
 * - LB_ISDX[4:0]: See description of bit field.
 * - LB_ISDX_P[4:0]: See description of bit field.
 *
 * Register: \a OAM_MEP:VOE:LOOPBACK_CTRL
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_LOOPBACK_CTRL(gi)   VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,10)

/** 
 * \brief
 * Configures if LMM frames are looped or sent to CPU. 
 * 
 * Note:
 * This must not be enabled for Up-MEP configurations.
 *
 * \details 
 * 0: OAM LMM PDU is sent to CPU queue: CPU_CFG_1:LMM_CPU_QU
 * 1: OAM LMM PDU is looped to LB_PORTMASK and OpCode and MAC addresses are
 * updated).
 * 
 * Configuration is only used is OAM_HW_CTRL.LMM_ENA is set.
 *
 * Field: ::VTSS_OAM_MEP_VOE_LOOPBACK_CTRL . LB_LMM_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_LOOPBACK_CTRL_LB_LMM_ENA  VTSS_BIT(25)

/** 
 * \brief
 * Configures if DMM frames are looped or sent to CPU. 
 * 
 * Note:
 * This must not be enabled for Up-MEP configurations.
 *
 * \details 
 * 0: OAM DMM PDU is sent to CPU queue: CPU_CFG_1:LMM_CPU_QU
 * 1: OAM DMM PDU is looped to LB_PORTMASK and OpCode and MAC addresses are
 * updated).
 * 
 * Configuration is only used is OAM_HW_CTRL.DMM_ENA is set.
 *
 * Field: ::VTSS_OAM_MEP_VOE_LOOPBACK_CTRL . LB_DMM_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_LOOPBACK_CTRL_LB_DMM_ENA  VTSS_BIT(24)

/** 
 * \brief
 * Down-MEP:
 * Configures ISDX for loopback traffic.
 * 
 * Up-MEP:
 * LB_ISDX[4:0]: Contains the current value of the LM Rx sequence number. 
 * This 5 bit value is sent to the CPU in the CPU extraction header when a
 * valid OAM PDU with LM content is received in in-service mode.
 * After the value is sent to the CPU, it is incremented.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_LOOPBACK_CTRL . LB_ISDX
 */
#define  VTSS_F_OAM_MEP_VOE_LOOPBACK_CTRL_LB_ISDX(x)  VTSS_ENCODE_BITFIELD(x,14,10)
#define  VTSS_M_OAM_MEP_VOE_LOOPBACK_CTRL_LB_ISDX     VTSS_ENCODE_BITMASK(14,10)
#define  VTSS_X_OAM_MEP_VOE_LOOPBACK_CTRL_LB_ISDX(x)  VTSS_EXTRACT_BITFIELD(x,14,10)

/** 
 * \brief
 * Down-MEP:
 * Configures protected ISDX for loopback traffic.
 * 
 * Up-MEP:
 * LB_ISDX_P[4:0]: Contains the current value of the DM Rx sequence number.
 * This 5 bit value is sent to the CPU in the CPU extraction header when a
 * valid OAM PDU with DM content is received in in-service mode.
 * After the value is sent to the CPU, it is incremented.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_LOOPBACK_CTRL . LB_ISDX_P
 */
#define  VTSS_F_OAM_MEP_VOE_LOOPBACK_CTRL_LB_ISDX_P(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_OAM_MEP_VOE_LOOPBACK_CTRL_LB_ISDX_P     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_OAM_MEP_VOE_LOOPBACK_CTRL_LB_ISDX_P(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Configures protected loopback port.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_LOOPBACK_CTRL . LB_PORTNUM_P
 */
#define  VTSS_F_OAM_MEP_VOE_LOOPBACK_CTRL_LB_PORTNUM_P(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_OAM_MEP_VOE_LOOPBACK_CTRL_LB_PORTNUM_P     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_OAM_MEP_VOE_LOOPBACK_CTRL_LB_PORTNUM_P(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Count number of received LBR frames
 *
 * \details
 * Counts number of received OAM LBR PDU.
 *
 * Register: \a OAM_MEP:VOE:LBR_RX_FRM_CNT
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_LBR_RX_FRM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,11)


/** 
 * \brief Configuration of expected transaction ID 
 *
 * \details
 * Configures expected transaction ID of the next RX LBR frame.
 * 
 * This value is checked against the value in the next RX LBR frame, if LBR
 * function is enabled for the VOE.
 * 
 * In case of an error, the following sticky bit is asserted:
 * VOE:OAM_RX_STICKY.LBR_TRANSID_ERR_STICKY.
 *
 * Register: \a OAM_MEP:VOE:LBR_RX_TRANSID_CFG
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_LBR_RX_TRANSID_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,12)


/** 
 * \brief Configuration of Tx transaction ID update
 *
 * \details
 * If set, the transaction id is updated for LBM frames transmitted from
 * this VOE.
 * This can be used to avoid overwriting the Tx ID for externally generated
 * LBM frames.
 *
 * Register: \a OAM_MEP:VOE:LBM_TX_TRANSID_UPDATE
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_LBM_TX_TRANSID_UPDATE(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,13)

/** 
 * \brief
 * If set, the transaction id is updated for LBM frames transmitted from
 * this VOE.
 * This can be used to avoid overwriting the Tx ID for externally generated
 * LBM frames.
 * 
 * Note:
 * Also used to update TX TST frames (If TST frames are enabled using
 * VOE:OAM_FWD_CTRL.GENERIC_FWD_MASK(6))).
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_LBM_TX_TRANSID_UPDATE . LBM_TRANSID_UPDATE_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_LBM_TX_TRANSID_UPDATE_LBM_TRANSID_UPDATE_ENA  VTSS_BIT(0)


/** 
 * \brief Configuration of transmitted transaction ID 
 *
 * \details
 * Configures transmitted transaction ID for LBM.
 * 
 * LBM Tx frames are updated with this value if LBM_TRANSID_UPDATE_ENA is
 * set.
 *
 * Register: \a OAM_MEP:VOE:LBM_TX_TRANSID_CFG
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_LBM_TX_TRANSID_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,14)


/** 
 * \brief Miscellaneous CCM configuration
 *
 * \details
 * Misc configuration for CCM frame handling.
 *
 * Register: \a OAM_MEP:VOE:CCM_CFG
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_CCM_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,15)

/** 
 * \brief
 * Down-MEP only (Not supported for Up-MEP
 * VOE can insert LM information into CCM frames injected by internal or
 * external CPU.
 * 
 * The insertion of LM information into CCM frames occurs based on a LOC
 * timeout counter.
 * 
 * This bit field configures which of the 7 LOC timeout counters to use for
 * LM insertion.
 * This configuration does not affect the CCM PDU period field.
 * 
 * When the selected LOC timeout counter times out, LM information is
 * inserted into the next CCM frame transmitted by the VOE.
 * 
 * Note that the rate at which LM infornation is inserted is twice the rate
 * indicated by the PERIOD_VAL of the selected timeout counter.
 * 
 * I.e. if the CCM_PERIOD_CFG.CCM_PERIOD_VAL of the selected timeout
 * counter is set to 10 ms, LM information is inserted every 5 ms.
 *
 * \details 
 * 0: Disable automatic insertion of loss measurements in OAM CCM PDU
 * n: Automatic insertion of loss measurements in next OAM CCM PDU when the
 * corresponding OAM_MEP::CCM_PERIOD_CFG occurs.
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_LM_PERIOD
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_LM_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_OAM_MEP_VOE_CCM_CFG_CCM_LM_PERIOD     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_OAM_MEP_VOE_CCM_CFG_CCM_LM_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * Down-MEP only (Not supported for Up-MEP
 * Indicate that CCM_LM info is inserted into next CCM Tx frame.
 * 
 * Automatically set by hardware every time CCM_LM_PERIOD has occured.
 * 
 * Can also be forced by SW writing a 1 to this register.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_LM_INSERT_NXT
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_LM_INSERT_NXT  VTSS_BIT(23)

/** 
 * \brief
 * Configures auto increment of CCM SEQ (upon use).
 * This is only valid if CCM_SEQ_UPD_ENA = 1
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_SEQ_INCR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_SEQ_INCR_ENA  VTSS_BIT(22)

/** 
 * \brief
 * If asserted (=1), the sequence number is updated for CCM frames
 * transmitted from this VOE.
 * This can be used to avoid overwriting the Tx ID for externally generated
 * LBM frames.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_SEQ_UPD_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_SEQ_UPD_ENA  VTSS_BIT(21)

/** 
 * \brief
 * Enables checking the incoming CCM sequence number.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_RX_SEQ_CHK_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_RX_SEQ_CHK_ENA  VTSS_BIT(20)

/** 
 * \brief
 * Specifies the RDI to be transmitted in the next CCM frame.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_TX_RDI
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_TX_RDI  VTSS_BIT(19)

/** 
 * \brief
 * Specifies the number of CCM half periods has passed without CCM messages
 * received from the peer MEP.
 * 
 * Cleared by HW when receiving a CCM message from the peer associated with
 * MEP.
 * 
 * Can be configured to periodically increment CCM miss count via HW
 * configured by VOP::CCM_CTRL.
 *
 * \details 
 * n<7: No Loss of continuity
 * n==7: Loss of continuity
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_MISS_CNT
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_OAM_MEP_VOE_CCM_CFG_CCM_MISS_CNT     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_OAM_MEP_VOE_CCM_CFG_CCM_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Configures expected CCM priority.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_PRIO
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_PRIO(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_OAM_MEP_VOE_CCM_CFG_CCM_PRIO     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_OAM_MEP_VOE_CCM_CFG_CCM_PRIO(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/** 
 * \brief
 * Configures expected CCM period.
 * 
 * The PERIOD fields of the incoming CCM frames are checked against this
 * value.
 * 
 * Further the configuration of this bit field specifies the LOC timeout
 * counter to be used for LOC scan for this VOE.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_PERIOD
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_OAM_MEP_VOE_CCM_CFG_CCM_PERIOD     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_OAM_MEP_VOE_CCM_CFG_CCM_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Configures CCM MEG ID check.
 *
 * \details 
 * 0: No MEGID check
 * 1: Check MEG ID
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_MEGID_CHK_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEGID_CHK_ENA  VTSS_BIT(9)

/** 
 * \brief
 * If this bit is asserted, the value of the MEP ID in incoming CCM frames
 * are verified against the value programmed in:
 * 
 * VOE:CCM_MEPID_CFG.CCM_MEPID
 * 
 * Errors in the incoming MEP ID are reported in the following error bit:
 * 
 * VOE:CCM_CFG.CCM_MEPID_ERR
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_MEPID_CHK_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEPID_CHK_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Status of period check for the latest received CCM frame.
 *
 * \details 
 * 0: No non zero period err
 * 1: Non zero period err detected
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_PERIOD_ERR
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_PERIOD_ERR  VTSS_BIT(7)

/** 
 * \brief
 * Status of latest priority check done for CCM frames
 *
 * \details 
 * 0: No priority err
 * 1: Priority err detected
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_PRIO_ERR
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_PRIO_ERR  VTSS_BIT(6)

/** 
 * \brief
 * Status of latest Zero period check
 *
 * \details 
 * 0: No Zero period err
 * 1: Zero period err detected
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_ZERO_PERIOD_ERR
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_ZERO_PERIOD_ERR  VTSS_BIT(5)

/** 
 * \brief
 * Specifies the RDI received in the latest CCM messages received from the
 * peer MEP.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_RX_RDI
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_RX_RDI  VTSS_BIT(4)

/** 
 * \brief
 * Status of current Loss of Continuity interrupt.
 *
 * \details 
 * 0: No loss of continuity
 * 1: Loss of continuity defect persist
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_LOC_DEFECT
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_LOC_DEFECT  VTSS_BIT(3)

/** 
 * \brief
 * Status of latest MEPID check, checking the MEPID of the incoming CCM
 * frame against the value programmed in: 
 * 
 * VOE:CCM_MEPID_CFG.CCM_MEPID
 * 
 * MEP ID check is enabled by setting: 
 * 
 * VOE:CCM_CFG.CCM_MEPID_CHK_ENA = 1
 *
 * \details 
 * 0: No MEPID err
 * 1: MEPID err detected
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_MEPID_ERR
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEPID_ERR  VTSS_BIT(2)

/** 
 * \brief
 * Status of latest MEGID check, validating incoming CCM MEGID against the
 * value configured in: 
 * 
 * VOE:CCM_MEGID_CFG.CCM_MEGID.
 * 
 * MEGID checking is enabled by:
 * 
 * VOE:CCM_CFG.CCM_MEGID_CHK_ENA = 1
 *
 * \details 
 * 0: No MEGID err
 * 1: MEGID err detected
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . CCM_MEGID_ERR
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_CCM_MEGID_ERR  VTSS_BIT(1)

/** 
 * \brief
 * Status of latest MEL check
 *
 * \details 
 * 0: No MEL err
 * 1: MEL err detected
 *
 * Field: ::VTSS_OAM_MEP_VOE_CCM_CFG . OAM_MEL_ERR
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_CFG_OAM_MEL_ERR  VTSS_BIT(0)


/** 
 * \brief Count number of received good CCM frames
 *
 * \details
 * Counts number of received OAM CCM PDU that passes requred ingress check 
 * and therefore clear the CCM miss counter.
 *
 * Register: \a OAM_MEP:VOE:CCM_RX_VLD_FC_CNT
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_CCM_RX_VLD_FC_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,16)


/** 
 * \brief Count number of received invalid CCM frames
 *
 * \details
 * Counts number of received OAM CCM PDU that fails requred ingress check
 * and therefore doesn't clear the CCM miss counter.
 *
 * Register: \a OAM_MEP:VOE:CCM_RX_INVLD_FC_CNT
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_CCM_RX_INVLD_FC_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,17)


/** 
 * \brief Latest received CCM_TX_FCf value
 *
 * \details
 * Register use differs when used for Up-MEP and Down-MEP:
 * Down-MEP:
 *   Latest received CCM_TX_FCf value.
 *   Value is used by VOE for writing outgoing CCM-LM frames (TxFCf)
 * 
 * Up-MEP:
 *   Value of RX_LM frame counter sampled when the latest LMM frame was
 * received.
 *   Value must be read by the CPU.
 *   When the register value is written, the VOE asserts the valid bit:
 * 
 *     UPMEP_LM_CNT_VLD.LMM_RX_CNT_VLD
 * 
 *   Reading the register from CPU clears the valid bit.
 * 
 *   If the register has not been read by the CPU, when a new sample
 * arrives, the following sticky bit is asserted:
 * 
 *     UPMEP_LM_CNT_STICKY.CCM_LMM_RX_CNT_STICKY
 *
 * Register: \a OAM_MEP:VOE:CCM_CAP_TX_FCf
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_CCM_CAP_TX_FCF(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,18)


/** 
 * \brief Latest RX_FCl counter value
 *
 * \details
 * Register use differs when used for Up-MEP and Down-MEP:
 * Down-MEP:
 *   Value of RX frame counter sampled when the latest CCM-LM frame was
 * received.
 *   Value is used by VOE for writing outgoing CCM-LM frames (RxFCf)
 * 
 * Up-MEP:
 *   Value of RX_LM frame counter sampled when the latest CCM-LM frame was
 * received.
 *   Value must be read by the CPU.
 *   When the register value is written, the VOE asserts the valid bit:
 *   UPMEP_LM_CNT_VLD.CCM_LM_RX_CNT_VLD
 * 
 *   Reading the register from CPU clears the valid bit.
 * 
 *   If the register has not been read by the CPU, when a new sample
 * arrives, the following sticky bit is asserted:
 * 
 *   UPMEP_LM_CNT_STICKY.CCM_LM_RX_CNT_STICKY

 *
 * Register: \a OAM_MEP:VOE:CCM_CAP_RX_FCl
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_CCM_CAP_RX_FCL(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,19)


/** 
 * \brief Up-MEP Rx loss measurement frame counter
 *
 * \details
 * Register used for Up-MEP only:
 *   Value of RX_LM frame counter sampled when the latest LMR frame was
 * received.
 *   Value must be read by the CPU.
 *   When the register value is written, the VOE asserts the valid bit:
 * 
 *     UPMEP_LM_CNT_VLD.LMR_RX_CNT_VLD
 * 
 *   Reading the register from CPU clears the valid bit.
 * 
 *   If the register has not been read by the CPU, when a new sample
 * arrives, the following sticky bit is asserted:
 * 
 *     UPMEP_LM_CNT_STICKY.CCM_LMR_RX_CNT_STICKY
 *
 * Register: \a OAM_MEP:VOE:UPMEP_LMR_RX_LM_CNT
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_UPMEP_LMR_RX_LM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,20)


/** 
 * \brief Configuration of CCM Sequence number
 *
 * \details
 * Configures CCM Sequence number to be inserted into the next CCM or
 * CCM-LM frame.
 *
 * Register: \a OAM_MEP:VOE:CCM_TX_SEQ_CFG
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_CCM_TX_SEQ_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,21)


/** 
 * \brief Configuration of expected CCM Sequence number
 *
 * \details
 * Down-MEP:
 * Configures the expected value of the Sequence number for the next CCM
 * frame.
 * 
 * The value is updated every time a CCM frame is received.
 * The value is updated with the CCM sequence number plus 1.
 * 
 * The value is verified if the RX CCM Sequence number check is enabled:
 * 
 * VOE:CCM_CFG.CCM_RX_SEQ_CHK_ENA = 1
 * 
 * If the received Sequence Number is not as expected, the following sticky
 * bit is asserted:
 * CCM_RX_SEQ_ERR_STICKY
 * 
 * 
 * Up-MEP:
 * For Up-MEP, only the lower 16 bit of the RX CCM SEQ is verified.
 * 
 * The remaining bits contain the RX_LM_SN for the latest received LM frame
 * as follows:
 * 
 * [20:16] contains RX_LM_SN for latest CCM-LM received.
 * Note: Corresponds to the LM sample in: CCM_CAP_RX_FCL
 * 
 * [25:21] contains RX_LM_SN for latest: LMR received (only in in-service
 * mode).
 * Note: Corresponds to the LM sample in: UPMEP_LMR_RX_LM_CNT
 * 
 * [30:26] contains RX_LM_SN for latest: LMM received 
 * Note: Corresponds to the LM sample in: CCM_CAP_TX_FCF
 *
 * Register: \a OAM_MEP:VOE:CCM_RX_SEQ_CFG
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_CCM_RX_SEQ_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,22)


/** 
 * \brief Configuration of CCM MEPID
 *
 * \details
 * Configures MEP ID value to be verified against incoming CCM frames.
 *
 * Register: \a OAM_MEP:VOE:CCM_MEPID_CFG
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_CCM_MEPID_CFG(gi)   VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,23)

/** 
 * \brief
 * Configures CCM MEP ID value for this VOE.
 * 
 * If CCM MEP ID checking is enabled (CCM_MEPID_CHK_ENA = 1), the MEP ID of
 * incoming CCM frames are verified againse the value configured in
 * CCM_MEPID.
 * 
 * If the received value differs from the value configured in MEP ID, the
 * incoming CCM frame is discarded (No LOC update) and the error is
 * signalled using the following error bit:
 * 
 * VOE:CCM_CFG.CCM_MEPID_ERR
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_CCM_MEPID_CFG . CCM_MEPID
 */
#define  VTSS_F_OAM_MEP_VOE_CCM_MEPID_CFG_CCM_MEPID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_OAM_MEP_VOE_CCM_MEPID_CFG_CCM_MEPID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_OAM_MEP_VOE_CCM_MEPID_CFG_CCM_MEPID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Configuration of CCM MEGID
 *
 * \details
 * Configures 48 byte MEG ID (lowest replication index correspond to MSB)
 * to verified in incoming CCM frames.
 *
 * Register: \a OAM_MEP:VOE:CCM_MEGID_CFG
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 * @param ri Register: CCM_MEGID_CFG (??), 0-11
 */
#define VTSS_OAM_MEP_VOE_CCM_MEGID_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,ri,24)


/** 
 * \brief Indicate reception of OpCode
 *
 * \details
 * Sticky bits are asserted when OAM PDU of specified type is received at
 * the correct MEL level and when the DMAC is valid for this VOE.
 *
 * Register: \a OAM_MEP:VOE:OAM_RX_STICKY
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_OAM_RX_STICKY(gi)   VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,36)

/** 
 * \brief
 * Rx reception Generic Opcodes per MEP per generic OpCode.
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . GENERIC_RX_STICKY_MASK
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_GENERIC_RX_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(x,17,8)
#define  VTSS_M_OAM_MEP_VOE_OAM_RX_STICKY_GENERIC_RX_STICKY_MASK     VTSS_ENCODE_BITMASK(17,8)
#define  VTSS_X_OAM_MEP_VOE_OAM_RX_STICKY_GENERIC_RX_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,8)

/** 
 * \brief
 * Asserted when receiving an OAM PDU with an OpCode which is a dedicated
 * or configured as a generic OpCodes
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . UNK_OPCODE_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY  VTSS_BIT(16)

/** 
 * \brief
 * Asserted when receiving an LTM PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . LTM_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LTM_RX_STICKY  VTSS_BIT(15)

/** 
 * \brief
 * Asserted when receiving an LTR PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . LTR_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LTR_RX_STICKY  VTSS_BIT(14)

/** 
 * \brief
 * Asserted when receiving an LMM PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . LMM_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LMM_RX_STICKY  VTSS_BIT(13)

/** 
 * \brief
 * Asserted when receiving an LMR PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . LMR_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LMR_RX_STICKY  VTSS_BIT(12)

/** 
 * \brief
 * Asserted when receiving an LBM PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . LBM_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBM_RX_STICKY  VTSS_BIT(11)

/** 
 * \brief
 * Asserted when receiving an LBR PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . LBR_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBR_RX_STICKY  VTSS_BIT(10)

/** 
 * \brief
 * Asserted when receiving an DMM PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . DMM_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_DMM_RX_STICKY  VTSS_BIT(9)

/** 
 * \brief
 * Asserted when receiving an DMR PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . DMR_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_DMR_RX_STICKY  VTSS_BIT(8)

/** 
 * \brief
 * Asserted when receiving an SM PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . SM_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_SM_RX_STICKY  VTSS_BIT(7)

/** 
 * \brief
 * Asserted when receiving an CCM or CCM-LM PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . CCM_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_RX_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * Asserted when receiving an CCM-LM PDU
 *
 * \details 
 * 0: No PDU received
 * 1: PDU with specified OpCode received
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . CCM_LM_RX_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_LM_RX_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * LBR TRANSACTION ID error check detected
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . LBR_TRANSID_ERR_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * CCM PDU received sequence error detected
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . CCM_RX_SEQ_ERR_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * OAM traffic received with MEL larger than this MEP MEL
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . OAM_AS_DATA_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_OAM_AS_DATA_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * OAM_MEP is discarding frame in egress lookup due to OAM MEL <= VOE_MEL
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . MEP_EGR_BLOCK_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_MEP_EGR_BLOCK_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Indicate incorrect MAC address received.
 *
 * \details 
 * 0: No event
 * 1: MAC addr err occured
 *
 * Field: ::VTSS_OAM_MEP_VOE_OAM_RX_STICKY . MAC_ADDR_ERR_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_OAM_RX_STICKY_MAC_ADDR_ERR_STICKY  VTSS_BIT(0)


/** 
 * \brief CCM sticky status indications
 *
 * \details
 * Group of sticky bits asserted based in checking different CCM field
 * values against the configured values.
 * 
 * Sticky bits are updated when the state of the check changes.
 * I.e. the sticky bits are asserted both when an error is asserted and
 * when it is deasserted.
 *
 * Register: \a OAM_MEP:VOE:STICKY
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_STICKY(gi)          VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,37)

/** 
 * \brief
 * Indicate change in the status of the PERIOD check of incoming CCM frames
 * against the value programmed in CCM_PERIOD.
 *
 * \details 
 * 0: No event
 * 1: Changed non zero Period occured
 *
 * Field: ::VTSS_OAM_MEP_VOE_STICKY . CCM_PERIOD_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_STICKY_CCM_PERIOD_STICKY  VTSS_BIT(7)

/** 
 * \brief
 * Indicate change in the status of the PRIORITY check of incoming CCM
 * frames against the value programmed in CCM_PRIO.
 *
 * \details 
 * 0: No event
 * 1: Changed CCM Priority occured
 *
 * Field: ::VTSS_OAM_MEP_VOE_STICKY . CCM_PRIO_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_STICKY_CCM_PRIO_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * Indicate change in reception of frames with zero period.
 * 
 * (According to G.8081 CCM CCM frames with PERIOD = 0 is an illegal
 * value.)
 *
 * \details 
 * 0: No event
 * 1: Changed Zero Period occured
 *
 * Field: ::VTSS_OAM_MEP_VOE_STICKY . CCM_ZERO_PERIOD_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_STICKY_CCM_ZERO_PERIOD_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * Indicate RDI changed value in latest CCM frame
 * 
 * Clear this bit to receive new RX RDI up/down interrupts for this MEP.
 *
 * \details 
 * 0: No event
 * 1: Changed RDI occured
 *
 * Field: ::VTSS_OAM_MEP_VOE_STICKY . CCM_RX_RDI_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_STICKY_CCM_RX_RDI_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * Indicate changed Loss of Continuity (LOC) state
 * 
 * Clear this bit to receive new up/down interrupts for this MEP.
 *
 * \details 
 * 0: LOC has not changed state
 * 1: Changed LOC state (LOC is indicated based on whether CCM_MISS_CNT is
 * less than 7)
 *
 * Field: ::VTSS_OAM_MEP_VOE_STICKY . CCM_LOC_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_STICKY_CCM_LOC_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * Indicate a change in the staus of the CCM MEPID checking of incoming CCM
 * frames against the value programmed in:
 * 
 * VOE:CCM_MEPID
 *
 * \details 
 * 0: No event
 * 1: PDU with changed MEPID seen
 *
 * Field: ::VTSS_OAM_MEP_VOE_STICKY . CCM_MEPID_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_STICKY_CCM_MEPID_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * Indicate a change in the staus of the CCM MEGID checking of incoming CCM
 * frames against the value programmed in:
 * 
 * VOE:CCM_MEGID_CFG.CCM_MEGID
 * 
 * MEG ID check is enabled by setting: 
 * 
 * VOE:CCM_CFG.CCM_MEGID_CHK_ENA = 1
 *
 * \details 
 * 0: No event
 * 1: PDU with changed MEGID seen
 *
 * Field: ::VTSS_OAM_MEP_VOE_STICKY . CCM_MEGID_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_STICKY_CCM_MEGID_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Indicate unexpected MEL.
 *
 * \details 
 * 0: No event
 * 1: PDU with unexpected MEL seen
 *
 * Field: ::VTSS_OAM_MEP_VOE_STICKY . OAM_MEL_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_STICKY_OAM_MEL_STICKY  VTSS_BIT(0)


/** 
 * \brief Up-MEP loss measurement sticky indications
 *
 * \details
 * UPMEP only:
 * If the Up-MEP RX counter samples, based on LM frame reception has not
 * been read by the CPU prior to reception of the next LM frame, a sticky
 * bit is asserted in this register.
 *
 * Register: \a OAM_MEP:VOE:UPMEP_LM_CNT_STICKY
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_UPMEP_LM_CNT_STICKY(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,38)

/** 
 * \brief
 * Up-MEP only.
 * Asserted if a CCM-LM frame is received and the corresponding sample
 * valid flag, has not been cleared by the CPU.
 * 
 * Sample valid: CCM_LM_RX_CNT_VLD 
 * 
 * Assertion of this sticky bit indicates that an RX_LM sample was
 * overwritten by the VOE before it was read by the CPU.
 * 
 * The valid flag is cleared by reading the RX LM sample value in:
 * CCM_CAP_RX_FCl
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_UPMEP_LM_CNT_STICKY . CCM_LM_RX_CNT_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_UPMEP_LM_CNT_STICKY_CCM_LM_RX_CNT_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * Up-MEP only.
 * Asserted if a LMM frame is received and the corresponding sample valid
 * flag, has not been cleared by the CPU.
 * 
 * Sample valid: LMM_RX_CNT_VLD 
 * 
 * Assertion of this sticky bit indicates that an RX_LM sample was
 * overwritten by the VOE before it was read by the CPU.
 * 
 * The valid flag is cleared by reading the RX LM sample value in:
 * CCM_CAP_TX_FCf
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_UPMEP_LM_CNT_STICKY . LMM_RX_CNT_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_UPMEP_LM_CNT_STICKY_LMM_RX_CNT_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Up-MEP only.
 * Asserted if a LMM frame is received and the corresponding sample valid
 * flag, has not been cleared by the CPU.
 * 
 * Sample valid: LMR_RX_CNT_VLD 
 * 
 * Assertion of this sticky bit indicates that an RX_LM sample was
 * overwritten by the VOE before it was read by the CPU.
 * 
 * The valid flag is cleared by reading the RX LM sample value in:
 * UPMEP_LMR_RX_LM_CNT
 *
 * \details 
 * Field: ::VTSS_OAM_MEP_VOE_UPMEP_LM_CNT_STICKY . LMR_RX_CNT_STICKY
 */
#define  VTSS_F_OAM_MEP_VOE_UPMEP_LM_CNT_STICKY_LMR_RX_CNT_STICKY  VTSS_BIT(0)


/** 
 * \brief Configures interrupt sources
 *
 * \details
 * Configures which sources should cause interrupts. 
 * 
 * Status of interrupt sources can be found in OAM_MEP:VOE:STICKY. 
 * 
 * Interrupting VOE can be found in OAM_MEP::INTR.
 *
 * Register: \a OAM_MEP:VOE:INTR_ENA
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_INTR_ENA(gi)        VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,39)

/** 
 * \brief
 * Configures interrupt based on CCM_PERIOD_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_VOE_INTR_ENA . CCM_PERIOD_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_INTR_ENA_CCM_PERIOD_INTR_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Configures interrupt based on CCM_PRIO_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_VOE_INTR_ENA . CCM_PRIO_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_INTR_ENA_CCM_PRIO_INTR_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Configures interrupt based on CCM_ZERO_PERIOD_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_VOE_INTR_ENA . CCM_ZERO_PERIOD_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_INTR_ENA_CCM_ZERO_PERIOD_INTR_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Configures interrupt based on CCM_RX_RDI_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_VOE_INTR_ENA . CCM_RX_RDI_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_INTR_ENA_CCM_RX_RDI_INTR_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Configures interrupt based on CCM_LOC_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_VOE_INTR_ENA . CCM_LOC_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_INTR_ENA_CCM_LOC_INTR_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Configures interrupt based on CCM_MEPID_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_VOE_INTR_ENA . CCM_MEPID_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_INTR_ENA_CCM_MEPID_INTR_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Configures interrupt based on CCM_MEGID_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_VOE_INTR_ENA . CCM_MEGID_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_INTR_ENA_CCM_MEGID_INTR_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Configures interrupt based on OAM_MEL_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_OAM_MEP_VOE_INTR_ENA . OAM_MEL_INTR_ENA
 */
#define  VTSS_F_OAM_MEP_VOE_INTR_ENA_OAM_MEL_INTR_ENA  VTSS_BIT(0)


/** 
 * \brief Count selected OAM PDU received by VOE
 *
 * \details
 * Count selected OAM PDU received MEP.
 * 
 * Selected OAM PDUs are configured in VOE:OAM_CNT_OAM_CTRL.*
 *
 * Register: \a OAM_MEP:VOE:RX_SEL_OAM_CNT
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_RX_SEL_OAM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,40)


/** 
 * \brief Count non-selected OAM PDU received by VOE
 *
 * \details
 * Count non-selected OAM frames received by VOE
 * 
 * Selected OAM PDUs are configured in VOE:OAM_CNT_OAM_CTRL.*
 *
 * Register: \a OAM_MEP:VOE:RX_OAM_FRM_CNT
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_RX_OAM_FRM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,41)


/** 
 * \brief Count selected OAM PDU transmitted by VOE
 *
 * \details
 * Count selected OAM PDU transmitted VOE.
 * 
 * Selected OAM PDUs are configured in VOE:OAM_CNT_OAM_CTRL.*
 *
 * Register: \a OAM_MEP:VOE:TX_SEL_OAM_CNT
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_TX_SEL_OAM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,42)


/** 
 * \brief Count non-selected OAM PDU transmitted by VOE
 *
 * \details
 * Count non-selected OAM frames transmitted by VOE.
 * 
 * Selected OAM PDUs are configured in VOE:OAM_CNT_OAM_CTRL.*
 *
 * Register: \a OAM_MEP:VOE:TX_OAM_FRM_CNT
 *
 * @param gi Replicator: x_NUM_TOTAL_VOE (??), 0-74
 */
#define VTSS_OAM_MEP_VOE_TX_OAM_FRM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x0,gi,64,0,43)

/**
 * Register Group: \a OAM_MEP:PORT_PM
 *
 * Performance counters per port VOE per priority
 */


/** 
 * \brief Rx port MEP frame counters
 *
 * \details
 * Register: \a OAM_MEP:PORT_PM:PORT_RX_FRM_CNT
 *
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-87
 */
#define VTSS_OAM_MEP_PORT_PM_PORT_RX_FRM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x1300,gi,2,0,0)


/** 
 * \brief Tx port MEP frame counters
 *
 * \details
 * Register: \a OAM_MEP:PORT_PM:PORT_TX_FRM_CNT
 *
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-87
 */
#define VTSS_OAM_MEP_PORT_PM_PORT_TX_FRM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x1300,gi,2,0,1)

/**
 * Register Group: \a OAM_MEP:RX_VOE_PM
 *
 * RX performance counters per service VOE per priority
 */


/** 
 * \brief Rx service MEP frame counters
 *
 * \details
 * Register: \a OAM_MEP:RX_VOE_PM:MEP_RX_FRM_CNT
 *
 * @param gi Replicator: x_NUM_VOE_x_NUM_PRIO (??), 0-511
 */
#define VTSS_OAM_MEP_RX_VOE_PM_MEP_RX_FRM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x1400,gi,1,0,0)

/**
 * Register Group: \a OAM_MEP:TX_VOE_PM
 *
 * Tx performance counters per service VOE per priority
 */


/** 
 * \brief Tx service MEP frame counters
 *
 * \details
 * Register: \a OAM_MEP:TX_VOE_PM:MEP_TX_FRM_CNT
 *
 * @param gi Replicator: x_NUM_VOE_x_NUM_PRIO (??), 0-511
 */
#define VTSS_OAM_MEP_TX_VOE_PM_MEP_TX_FRM_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_OAM_MEP,0x1600,gi,1,0,0)


#endif /* _VTSS_SERVAL_REGS_OAM_MEP_H_ */
