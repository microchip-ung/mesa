// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2C_REGS_ANA_AC_OAM_MOD_H_
#define _VTSS_JAGUAR2C_REGS_ANA_AC_OAM_MOD_H_


#include "vtss_jaguar2c_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a ANA_AC_OAM_MOD
 *
 * This block os part of the Vitesse OAM MEP Processor (VOP). It is directly
 * controlled by the VOP and performs all frame modification related OAM
 * functions.
 * 
 * This block is included in both the REW and the ANA_AC.
 * 
 * The HW support for implementing an OAM MEP is implemented in a sub
 * block, known as:
 * Vitesse OAM Endpoint (VOE).
 * 
 * The VOP includes the following:
 * 
 *  * 256 Service / Path VOEs
 *  * 11 Port VOEs
 *
 ***********************************************************************/

/**
 * Register Group: \a ANA_AC_OAM_MOD:VOE_SRV_LM_CNT
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
 * Register: \a ANA_AC_OAM_MOD:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB
 *
 * @param gi Replicator: x_NUM_VOE_x_NUM_PRIO (??), 0-8191
 */
#define VTSS_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x0,gi,1,0,0)

/** 
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB . SRV_LM_CNT_LSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_SRV_LM_CNT_LSB_SRV_LM_CNT_LSB(x)  (x)

/**
 * Register Group: \a ANA_AC_OAM_MOD:VOE_PORT_LM_CNT
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
 * Register: \a ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB
 *
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-423
 */
#define VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2000,gi,4,0,0)

/** 
 * \brief
 * See Register Description.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB . PORT_LM_CNT_LSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_LM_CNT_LSB_PORT_LM_CNT_LSB(x)  (x)


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
 * Register: \a ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_FRM_CNT_LSB
 *
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-423
 */
#define VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2000,gi,4,0,1)

/** 
 * \brief
 * See Register Description.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB . PORT_FRM_CNT_LSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_FRM_CNT_LSB_PORT_FRM_CNT_LSB(x)  (x)


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
 * Register: \a ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_BYTE_CNT_MSB
 *
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-423
 */
#define VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2000,gi,4,0,2)

/** 
 * \brief
 * See Register Description.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB . PORT_BYTE_CNT_MSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_MSB_PORT_BYTE_CNT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


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
 * Register: \a ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_BYTE_CNT_LSB
 *
 * @param gi Replicator: x_NUM_FRONT_PORTS_x_NUM_PRIO (??), 0-423
 */
#define VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2000,gi,4,0,3)

/** 
 * \brief
 * See Register Description.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB . PORT_BYTE_CNT_LSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_PORT_BYTE_CNT_LSB_PORT_BYTE_CNT_LSB(x)  (x)

/**
 * Register Group: \a ANA_AC_OAM_MOD:OAM_PDU_MOD_CONT
 *
 * VOE additional information
 */


/** 
 * \brief LM temp count
 *
 * \details
 * Register: \a ANA_AC_OAM_MOD:OAM_PDU_MOD_CONT:TEMP_CNT_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-109
 */
#define VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_TEMP_CNT_REG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2800,gi,8,0,0)

/** 
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_TEMP_CNT_REG . TEMP_CNT_VAL
 */
#define  VTSS_F_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_TEMP_CNT_REG_TEMP_CNT_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_TEMP_CNT_REG_TEMP_CNT_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_TEMP_CNT_REG_TEMP_CNT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Temp LM cnt
 *
 * \details
 * Register: \a ANA_AC_OAM_MOD:OAM_PDU_MOD_CONT:LM_CNT_FRAME
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-109
 */
#define VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2800,gi,8,0,1)

/** 
 * \brief
 * Determines if the current frame should be counted by the Service LM
 * counter, based on the color / mapping and possibly being killed in the
 * ingress DLB.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME . SRV_CNT_FRM
 */
#define  VTSS_F_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME_SRV_CNT_FRM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME_SRV_CNT_FRM  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME_SRV_CNT_FRM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Determines if the current frame should be counted by the Path LM
 * counter, based on the color / mapping and possibly being killed in the
 * ingress DLB.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME . PATH_CNT_FRM
 */
#define  VTSS_F_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME_PATH_CNT_FRM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME_PATH_CNT_FRM  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_LM_CNT_FRAME_PATH_CNT_FRM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Temp CCM-LM info
 *
 * \details
 * Register: \a ANA_AC_OAM_MOD:OAM_PDU_MOD_CONT:CCM_LM_INFO_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-109
 */
#define VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2800,gi,8,0,2)

/** 
 * \brief
 * Indicates whether this entry in the RAM contains valid CCM-LM sample
 * values.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG . CCM_LM_INFO_VLD
 */
#define  VTSS_F_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_INFO_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_INFO_VLD  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_INFO_VLD(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * The number of the VOE for which the LM information was received.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG . CCM_LM_VOE_IDX
 */
#define  VTSS_F_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_VOE_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_VOE_IDX     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_INFO_REG_CCM_LM_VOE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief CCM-LM sample
 *
 * \details
 * Contains the sampled value of CCM_LM.tx_fc_b from the last valid CCM_LM
 * frame.
 *
 * Register: \a ANA_AC_OAM_MOD:OAM_PDU_MOD_CONT:CCM_LM_TX_B_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-109
 */
#define VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2800,gi,8,0,3)

/** 
 * \brief
 * Contains the sampled value of CCM_LM.tx_fc_b from the last valid CCM_LM
 * frame.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG . CCM_LM_TX_B
 */
#define  VTSS_F_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG_CCM_LM_TX_B(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG_CCM_LM_TX_B     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_TX_B_REG_CCM_LM_TX_B(x)  (x)


/** 
 * \brief CCM-LM sample
 *
 * \details
 * Contains the sampled value of CCM_LM.rx_fc_b from the last valid CCM_LM
 * frame.
 *
 * Register: \a ANA_AC_OAM_MOD:OAM_PDU_MOD_CONT:CCM_LM_RX_B_REG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_FRONT_PORTS_x2 (??), 0-109
 */
#define VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_OAM_MOD,0x2800,gi,8,0,4)

/** 
 * \brief
 * Contains the sampled value of CCM_LM.rx_fc_b from the last valid CCM_LM
 * frame.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG . CCM_LM_RX_B
 */
#define  VTSS_F_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG_CCM_LM_RX_B(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG_CCM_LM_RX_B     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CCM_LM_RX_B_REG_CCM_LM_RX_B(x)  (x)

/**
 * Register Group: \a ANA_AC_OAM_MOD:PDU_MOD_CFG
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
 * Register: \a ANA_AC_OAM_MOD:PDU_MOD_CFG:DM_PTP_DOMAIN_CFG
 *
 * @param ri Replicator: x_NUM_FRONT_PORTS (??), 0-52
 */
#define VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_OAM_MOD,0x26a0 + (ri))

/** 
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG . PTP_DOMAIN
 */
#define  VTSS_F_ANA_AC_OAM_MOD_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG_PTP_DOMAIN(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_AC_OAM_MOD_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG_PTP_DOMAIN     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_AC_OAM_MOD_PDU_MOD_CFG_DM_PTP_DOMAIN_CFG_PTP_DOMAIN(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
 * Register: \a ANA_AC_OAM_MOD:PDU_MOD_CFG:RD_LAST_PORT_LM_CNT_LSB
 */
#define VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB  VTSS_IOREG(VTSS_TO_ANA_AC_OAM_MOD,0x26d5)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB . RD_LAST_PORT_LM_CNT_LSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_LM_CNT_LSB_RD_LAST_PORT_LM_CNT_LSB(x)  (x)


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
 * Register: \a ANA_AC_OAM_MOD:PDU_MOD_CFG:RD_LAST_PORT_FRM_CNT_LSB
 */
#define VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB  VTSS_IOREG(VTSS_TO_ANA_AC_OAM_MOD,0x26d6)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB . RD_LAST_PORT_FRM_CNT_LSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_FRM_CNT_LSB_RD_LAST_PORT_FRM_CNT_LSB(x)  (x)


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
 * Register: \a ANA_AC_OAM_MOD:PDU_MOD_CFG:RD_LAST_PORT_BYTE_CNT_MSB
 */
#define VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB  VTSS_IOREG(VTSS_TO_ANA_AC_OAM_MOD,0x26d7)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB . RD_LAST_PORT_BYTE_CNT_MSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_MSB_RD_LAST_PORT_BYTE_CNT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


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
 * Register: \a ANA_AC_OAM_MOD:PDU_MOD_CFG:RD_LAST_PORT_BYTE_CNT_LSB
 */
#define VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB  VTSS_IOREG(VTSS_TO_ANA_AC_OAM_MOD,0x26d8)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB . RD_LAST_PORT_BYTE_CNT_LSB
 */
#define  VTSS_F_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB(x)  (x)
#define  VTSS_M_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB     0xffffffff
#define  VTSS_X_ANA_AC_OAM_MOD_PDU_MOD_CFG_RD_LAST_PORT_BYTE_CNT_LSB_RD_LAST_PORT_BYTE_CNT_LSB(x)  (x)


#endif /* _VTSS_JAGUAR2C_REGS_ANA_AC_OAM_MOD_H_ */
