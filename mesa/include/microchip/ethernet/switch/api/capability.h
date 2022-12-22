// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_CAPABILITY_
#define _MICROCHIP_ETHERNET_SWITCH_API_CAPABILITY_

#include <stdint.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// MESA_CHIP_FAMILY, matching VTSS_CHIP_FAMILY, obsolete values 1,3,5 not shown
typedef enum {
    MESA_CHIP_FAMILY_UNKNOWN = 0, /**< Unknown */
    MESA_CHIP_FAMILY_CARACAL = 2, /**< Luton26 */
    MESA_CHIP_FAMILY_SERVAL  = 4, /**< Serval-1 */
    MESA_CHIP_FAMILY_SERVALT = 6, /**< Serval-T */
    MESA_CHIP_FAMILY_JAGUAR2 = 7, /**< Jaguar-2 */
    MESA_CHIP_FAMILY_OCELOT  = 8, /**< Ocelot/Ferret */
    MESA_CHIP_FAMILY_SPARX5  = 9, /**< SparX-5 */
    MESA_CHIP_FAMILY_LAN966X = 10,/**< LAN966X */
} mesa_chip_family_t;

typedef enum {
    MESA_CPU_TYPE_EXTERNAL,  /**< External CPU */
    MESA_CPU_TYPE_VCORE_III, /**< Internal VCore-III CPU */
} mesa_cpu_type_t;

typedef enum {
    MESA_SWITCH_BW_UNKNOWN,  /**< Unknown */
    MESA_SWITCH_BW_64,       /**< 64Gb  + NPI */
    MESA_SWITCH_BW_90,       /**< 90Gb  + NPI */
    MESA_SWITCH_BW_128,      /**< 128Gb + NPI */
    MESA_SWITCH_BW_160,      /**< 160Gb + NPI */
    MESA_SWITCH_BW_200,      /**< 200Gb + NPI */
} mesa_switch_bw_t;

typedef enum {
    // Miscellaneous
    MESA_CAP_MISC_GPIO_CNT = 0,             /**< Number of GPIOs */
    MESA_CAP_MISC_SGPIO_CNT,                /**< Number of SGPIO groups */
    MESA_CAP_MISC_PORT_GPIO,                /**< Port GPIO */
    MESA_CAP_MISC_INTERRUPTS,               /**< Interrupts */
    MESA_CAP_MISC_IRQ_CONTROL,              /**< IRQ control */
    MESA_CAP_MISC_FAN,                      /**< Fan control */
    MESA_CAP_MISC_CHIP_FAMILY,              /**< Chip family */
    MESA_CAP_MISC_CPU_TYPE,                 /**< CPU type */
    MESA_CAP_MISC_DAC_CONTROLS_LOCAL_OSC,   /**< Local oscillator is controlled by DAC */
    MESA_CAP_MISC_SWITCH_BW,                /**< Max switching Bandwidth in Gbps */
    MESA_CAP_MISC_SGPIO_MAP,                /**< SGPIO to Signal detect map */

    // Port
    MESA_CAP_PORT_CNT = 100,                /**< Maximum number of ports */
    MESA_CAP_PORT_PFC,                      /**< 802.1Qbb Priority Flow Control */
    MESA_CAP_PORT_FRAME_LENGTH_MAX,         /**< Maximum frame length */
    MESA_CAP_PORT_CNT_ETHER_LIKE,           /**< Ethernet-like counters */
    MESA_CAP_PORT_CNT_EVC,                  /**< Port EVC counters */
    MESA_CAP_PORT_MIIM_CTRL_CNT,            /**< Number of MIIM controllers */
    MESA_CAP_PORT_BW,                       /**< Internal bandwidth per port */
    MESA_CAP_PORT_IFH,                      /**< Port IFH */
    MESA_CAP_PORT_INJ_HDR,                  /**< Port injection header */
    MESA_CAP_PORT_XTR_HDR,                  /**< Port extraction header */
    MESA_CAP_PORT_10G,                      /**< 10Gbps port */
    MESA_CAP_PORT_MUX,                      /**< Port multiplexer */
    MESA_CAP_PORT_MUX_AUTO,                 /**< Port multiplexer auto mode */
    MESA_CAP_PORT_QS_CONF,                  /**< Port queue system configuration */
    MESA_CAP_PORT_10GBASE_KR_V3,            /**< Basic 802.3ap Backplane Ethernet (JR2, Sparx-5) */
    MESA_CAP_PORT_KR,                       /**< Basic 802.3ap Backplane Ethernet (JR2, Sparx-5) */
    MESA_CAP_PORT_KR_IRQ,                   /**< Advanced IRQ controlled Backplane Ethernet (Sparx-5) */
    MESA_CAP_PORT_CNT_PTP_PHYS_AND_VIRT,    /**< Number of PTP ports counting physical and virtual ports */
    MESA_CAP_PORT_LAST_FRAME_LEN_THRESHOLD, /**< The max length of the frames counted in the last range of the frame counter group */
    MESA_CAP_PORT_PCS_CONF,                 /**< Specific control of the 1G PCS */

    // Packet
    MESA_CAP_PACKET_RX_QUEUE_CNT = 200,     /**< Number of Rx packet queues */
    MESA_CAP_PACKET_RX_GRP_CNT,             /**< Number of Rx packet groups */
    MESA_CAP_PACKET_TX_GRP_CNT,             /**< Number of Tx packet groups */
    MESA_CAP_PACKET_HDR_SIZE,               /**< Header size in bytes */
    MESA_CAP_PACKET_RX_IFH_SIZE,            /**< Rx IFH size in bytes */
    MESA_CAP_PACKET_TX_IFH_SIZE,            /**< Tx IFH size in bytes */
    MESA_CAP_PACKET_PORT_L2CP_REG,          /**< Port L2CP registration */
    MESA_CAP_PACKET_PORT_IPMC,              /**< Port IP multicast registration */
    MESA_CAP_PACKET_VSTAX,                  /**< VStaX header format */
    MESA_CAP_PACKET_IFH_EPID,               /**< IFH EPID number */
    MESA_CAP_PACKET_FCS_DATA,               /**< Data in FCS field, e.g. SFlow */
    MESA_CAP_PACKET_MASQ_PORT,              /**< Masquerade port support */
    MESA_CAP_PACKET_INS_TAG,                /**< Insert of tag used internally */
    MESA_CAP_PACKET_PTP_ACTION,             /**< PTP legal action mask */
    MESA_CAP_PACKET_AUTO_TAGGING,           /**< Indicates that switch can do tagging automatically at egress without need for using FDMA */
    MESA_CAP_PACKET_INJ_ENCAP,              /**< Packet Tx supports injection with specific encapsulation */

    // AFI
    MESA_CAP_AFI_V1 = 300,                  /**< AFI version 1 */
    MESA_CAP_AFI_V2,                        /**< AFI version 2 */
    MESA_CAP_AFI_SLOT_CNT,                  /**< Number of AFI flows */
    MESA_CAP_AFI_SLOW_INJ_CNT,              /**< Maximum number of simultaneous slow injections */
    MESA_CAP_AFI_SLOW_INJ_FPH_MAX,          /**< Maximum number of frames per hour supported by slow injections */
    MESA_CAP_AFI_FAST_INJ_CNT,              /**< Maximum number of simultaneous fast injections */
    MESA_CAP_AFI_FAST_INJ_KBPS_MIN,         /**< Minimum rate in kbps (including IFG and preamble) */
    MESA_CAP_AFI_FAST_INJ_KBPS_MAX,         /**< Maximum rate in kbps (including IFG and preamble) */
    MESA_CAP_AFI_FAST_INJ_FRM_CNT,          /**< Maximum number of frames in fast injection sequence */

    // Layer 2
    MESA_CAP_L2_MAC_ADDR_CNT = 400,         /**< Number of MAC addresses */
    MESA_CAP_L2_AGGR_CNT,                   /**< Number of link aggregations */
    MESA_CAP_L2_PVLAN_CNT,                  /**< Number of PVLANs */
    MESA_CAP_L2_SRID_CNT,                   /**< Number of Seamless Redundancy IDs */
    MESA_CAP_L2_SVL_FID_CNT,                /**< Number of Shared VLAN Learning FIDs */
    MESA_CAP_L2_VLAN_COUNTERS,              /**< Counters per VLAN */
    MESA_CAP_L2_VCAP_PORT_CONF,             /**< VCAP port configuration */
    MESA_CAP_L2_MIRROR_TAG,                 /**< Mirror tag */
    MESA_CAP_L2_IPV4_MC_SIP,                /**< SSM for IPv4 (IGMPv3) */
    MESA_CAP_L2_IPV6_MC_SIP,                /**< SSM for IPv6 (MLDv2) */
    MESA_CAP_L2_SFLOW_TESTED,               /**< SFLOW tested (internal purposes) */
    MESA_CAP_L2_MSTP_HW,                    /**< MSTP table hardware support */
    MESA_CAP_L2_SFLOW_SAMPLE_RATE_MAX,      /**< Maximum allowed sampling rate for sFlow */
    MESA_CAP_L2_XFLOW,                      /**< Ingress and egress flows */
    MESA_CAP_L2_XSTAT,                      /**< Ingress and egress statistics */
    MESA_CAP_L2_XDLB,                       /**< DLB policers allocated dynamically */
    MESA_CAP_L2_TPID_AWARE,                 /**< Full VLAN awareness */
    MESA_CAP_L2_FRER,                       /**< FRER */
    MESA_CAP_L2_FRER_MSTREAM_CNT,           /**< Number of FRER Member Streams */
    MESA_CAP_L2_FRER_CSTREAM_CNT,           /**< Number of FRER Compound Streams */
    MESA_CAP_L2_PSFP,                       /**< PSFP */
    MESA_CAP_L2_PSFP_GATE_CNT,              /**< Number of PSFP gates */
    MESA_CAP_L2_PSFP_FILTER_CNT,            /**< Number of PSFP filters */
    MESA_CAP_L2_VCL_KEY_DMAC,               /**< VCL key DMAC support */
    MESA_CAP_L2_VCL_KEY_DIP,                /**< VCL key DIP support */
    MESA_CAP_L2_FRER_IFLOW_POP,             /**< FRER R-tag popping per ingress flow */
    MESA_CAP_L2_RCL,                        /**< Real-time Control List */
    MESA_CAP_L2_MAC_INDEX_TABLE,            /**< Index-based MAC address table */

    // Layer 3
    MESA_CAP_L3 = 500,                      /**< Layer 3 switching */
    MESA_CAP_L3_RLEG_CNT,                   /**< Number of router legs */
    MESA_CAP_L3_LPM_CNT,                    /**< Number of LPM entries */
    MESA_CAP_L3_ARP_CNT,                    /**< Number of ARP entries */

    // QoS
    MESA_CAP_QOS_PRIO_CNT = 600,            /**< Number of priority classes */
    MESA_CAP_QOS_QUEUE_CNT,                 /**< Number of port queues */
    MESA_CAP_QOS_DPL_CNT,                   /**< Number of drop precedence levels */
    MESA_CAP_QOS_PORT_POLICER_CNT,          /**< Number of port policers */
    MESA_CAP_QOS_WRED_GROUP_CNT,            /**< Number of WRED groups */
    MESA_CAP_QOS_TAS,                       /**< Time Aware Scheduling (802.1Qbv) supported */
    MESA_CAP_QOS_TAS_GCE_CNT,               /**< Maximum supported number of Time Aware Scheduling (802.1Qbv) gate control entries */
    MESA_CAP_QOS_TAS_CT_MIN,                /**< Minimum supported Gate CycleTime in nS */
    MESA_CAP_QOS_TAS_CT_MAX,                /**< Maximum supported Gate CycleTime in nS */
    MESA_CAP_QOS_TAS_MAX_SDU_MIN,           /**< Minimum supported MAX SDU size */
    MESA_CAP_QOS_TAS_MAX_SDU_MAX,           /**< Maximum supported MAX SDU size */
    MESA_CAP_QOS_TAS_HOLD_REL_MAC_RESTRICT, /**< Hold and Release MAC operations are restricted. All opened Hold queues must be express. All opened release queues must be preemptable. */
    MESA_CAP_QOS_INGRESS_MAP_CNT,           /**< Number of QoS ingress map entries */
    MESA_CAP_QOS_EGRESS_MAP_CNT,            /**< Number of QoS egress map entries */
    MESA_CAP_QOS_COSID_CLASSIFICATION,      /**< COSID classification */
    MESA_CAP_QOS_SCHEDULER_CNT_DWRR,        /**< Number of queues in DWRR mode */
    MESA_CAP_QOS_CPU_PORT_SHAPER,           /**< CPU port shaper */
    MESA_CAP_QOS_WRED,                      /**< WRED */
    MESA_CAP_QOS_DLB_CM,                    /**< DLB policer Color Mode */
    MESA_CAP_QOS_EGRESS_SHAPERS_RT,         /**< Egress shaper rate type support */
    MESA_CAP_QOS_EGRESS_SHAPER_FRAME,       /**< Egress shaper frame rate type support */
    MESA_CAP_QOS_EGRESS_SHAPERS_DLB,        /**< Egress shaper DLB support */
    MESA_CAP_QOS_PORT_POLICER_EXT_DPBL,     /**< Drop Precedence Bypass Level */
    MESA_CAP_QOS_PORT_POLICER_EXT_TTM,      /**< Traffic type mask */
    MESA_CAP_QOS_EGRESS_QUEUE_SHAPERS_EB,   /**< Queue shaper excess bandwidth */
    MESA_CAP_QOS_EGRESS_QUEUE_SHAPERS_CRB,  /**< Queue shaper credit based */
    MESA_CAP_QOS_EGRESS_QUEUE_CUT_THROUGH,  /**< Queue shaper cut through */
    MESA_CAP_QOS_DSCP_REMARK_DP_AWARE,      /**< DSCP remarking DP aware */
    MESA_CAP_QOS_QCL_KEY_TYPE,              /**< QCL key type */
    MESA_CAP_QOS_QCL_DMAC_DIP,              /**< QCL DMAC/DIP matching (default SMAC/SIP) */
    MESA_CAP_QOS_QCL_KEY_DMAC,              /**< QCL key DMAC support */
    MESA_CAP_QOS_QCL_KEY_DIP,               /**< QCL key DIP support */
    MESA_CAP_QOS_QCL_KEY_INNER_TAG,         /**< QCL key inner tag support */
    MESA_CAP_QOS_SHAPER_CALIBRATE,          /**< Shaper calibration */
    MESA_CAP_QOS_FRAME_PREEMPTION,          /**< 802.1Qbu and 802.3br (Frame Preemption) */
    MESA_CAP_QOS_PORT_POLICER_BIT_RATE_MIN,
    MESA_CAP_QOS_PORT_POLICER_BIT_RATE_MAX,
    MESA_CAP_QOS_PORT_POLICER_BIT_BURST_MIN,
    MESA_CAP_QOS_PORT_POLICER_BIT_BURST_MAX,
    MESA_CAP_QOS_PORT_POLICER_FRAME_RATE_MIN,
    MESA_CAP_QOS_PORT_POLICER_FRAME_RATE_MAX,
    MESA_CAP_QOS_PORT_POLICER_FRAME_BURST_MIN,
    MESA_CAP_QOS_PORT_POLICER_FRAME_BURST_MAX,
    MESA_CAP_QOS_QUEUE_POLICER_BIT_RATE_MIN,
    MESA_CAP_QOS_QUEUE_POLICER_BIT_RATE_MAX,
    MESA_CAP_QOS_QUEUE_POLICER_BIT_BURST_MIN,
    MESA_CAP_QOS_QUEUE_POLICER_BIT_BURST_MAX,
    MESA_CAP_QOS_QUEUE_POLICER_FRAME_RATE_MIN,
    MESA_CAP_QOS_QUEUE_POLICER_FRAME_RATE_MAX,
    MESA_CAP_QOS_QUEUE_POLICER_FRAME_BURST_MIN,
    MESA_CAP_QOS_QUEUE_POLICER_FRAME_BURST_MAX,
    MESA_CAP_QOS_PORT_SHAPER_BIT_RATE_MIN,
    MESA_CAP_QOS_PORT_SHAPER_BIT_RATE_MAX,
    MESA_CAP_QOS_PORT_SHAPER_BIT_BURST_MIN,
    MESA_CAP_QOS_PORT_SHAPER_BIT_BURST_MAX,
    MESA_CAP_QOS_PORT_SHAPER_FRAME_RATE_MIN,
    MESA_CAP_QOS_PORT_SHAPER_FRAME_RATE_MAX,
    MESA_CAP_QOS_PORT_SHAPER_FRAME_BURST_MIN,
    MESA_CAP_QOS_PORT_SHAPER_FRAME_BURST_MAX,
    MESA_CAP_QOS_QUEUE_SHAPER_BIT_RATE_MIN,
    MESA_CAP_QOS_QUEUE_SHAPER_BIT_RATE_MAX,
    MESA_CAP_QOS_QUEUE_SHAPER_BIT_BURST_MIN,
    MESA_CAP_QOS_QUEUE_SHAPER_BIT_BURST_MAX,
    MESA_CAP_QOS_QUEUE_SHAPER_FRAME_RATE_MIN,
    MESA_CAP_QOS_QUEUE_SHAPER_FRAME_RATE_MAX,
    MESA_CAP_QOS_QUEUE_SHAPER_FRAME_BURST_MIN,
    MESA_CAP_QOS_QUEUE_SHAPER_FRAME_BURST_MAX,
    MESA_CAP_QOS_GLOBAL_STORM_BIT_RATE_MIN,
    MESA_CAP_QOS_GLOBAL_STORM_BIT_RATE_MAX,
    MESA_CAP_QOS_GLOBAL_STORM_BIT_BURST_MIN,
    MESA_CAP_QOS_GLOBAL_STORM_BIT_BURST_MAX,
    MESA_CAP_QOS_GLOBAL_STORM_FRAME_RATE_MIN,
    MESA_CAP_QOS_GLOBAL_STORM_FRAME_RATE_MAX,
    MESA_CAP_QOS_GLOBAL_STORM_FRAME_BURST_MIN,
    MESA_CAP_QOS_GLOBAL_STORM_FRAME_BURST_MAX,
    MESA_CAP_QOS_PORT_STORM_BIT_RATE_MIN,
    MESA_CAP_QOS_PORT_STORM_BIT_RATE_MAX,
    MESA_CAP_QOS_PORT_STORM_BIT_BURST_MIN,
    MESA_CAP_QOS_PORT_STORM_BIT_BURST_MAX,
    MESA_CAP_QOS_PORT_STORM_FRAME_RATE_MIN,
    MESA_CAP_QOS_PORT_STORM_FRAME_RATE_MAX,
    MESA_CAP_QOS_PORT_STORM_FRAME_BURST_MIN,
    MESA_CAP_QOS_PORT_STORM_FRAME_BURST_MAX,
    MESA_CAP_DSCP_CNT,
    MESA_CAP_QOS_CPU_QUEUE_SHAPER,

    // Security/ACL
    MESA_CAP_ACL_POLICER_CNT = 800,         /**< Number of ACL policers */
    MESA_CAP_ACL_POLICY_CNT,                /**< Number of ACL policies */
    MESA_CAP_ACL_SIP_CNT,                   /**< Number of ACL SIP entries */
    MESA_CAP_ACL_PTP_DELAY,                 /**< ACL PTP delay control */
    MESA_CAP_ACL_PTP_ONE_AND_TWO_STEP,      /**< ACL PTP one and two step time-stamping */
    MESA_CAP_ACL_EVC_POLICER,               /**< ACL EVC policer mapping */
    MESA_CAP_ACL_CNT_LM,                    /**< ACL LM count control */
    MESA_CAP_ACL_MAC_SWAP,                  /**< ACL MAC swap */
    MESA_CAP_ACL_IFH_FLAG,                  /**< ACL IFH flag */
    MESA_CAP_ACL_KEY_LOOKUP,                /**< ACL key lookup */
    MESA_CAP_ACL_KEY_ISDX,                  /**< ACL key ISDX */
    MESA_CAP_ACL_ACE_STATUS,                /**< ACL ACE status */
    MESA_CAP_ACL_POLICER_PACKET_RATE_MAX,   /**< ACL policer packet rate maximum (pps) */
    MESA_CAP_ACL_POLICER_PACKET_RATE_GRAN,  /**< ACL policer packet rate granularity (pps) */
    MESA_CAP_ACL_POLICER_PACKET_RATE_SMALL, /**< ACL policer packet rate small range (pps) */
    MESA_CAP_ACL_POLICER_BIT_RATE_MAX,      /**< ACL policer bit rate maximum (kbps) */
    MESA_CAP_ACL_POLICER_BIT_RATE_GRAN,     /**< ACL policer bit rate granularity (kbps) */
    MESA_CAP_ACL_HACL,                      /**< Hierarchical ACLs */
    MESA_CAP_ACL_EXT_DIP,                   /**< ACL extended IPv6 rule with DIP matching */
    MESA_CAP_ACL_EXT_MAC,                   /**< ACL extended IPv4/IPv6 rules with MAC address matching */

    // EVC
    MESA_CAP_EVC_EVC_CNT = 900,             /**< Number of EVCs */
    MESA_CAP_EVC_ECE_CNT,                   /**< Number of ECEs */
    MESA_CAP_EVC_MPLS_PW_CNT,               /**< Number of MPLS Pseudo Wires per EVC */
    MESA_CAP_EVC_POLICER_CNT,               /**< Number of EVC policers */
    MESA_CAP_EVC_ENCAP_CNT,                 /**< Number of EVC encapsulations */
    MESA_CAP_EVC_L2CP_PROFILE_CNT,          /**< Number of L2CP profiles */
    MESA_CAP_EVC_NNI_LIST,                  /**< EVC NNI port list */
    MESA_CAP_EVC_LEAF_LIST,                 /**< EVC Leaf port list */
    MESA_CAP_EVC_COSID_POLICERS,            /**< EVC COSID policers */
    MESA_CAP_EVC_POLICER_BLIND,             /**< EVC colur blind policing */
    MESA_CAP_EVC_SERVAL,                    /**< EVC for Serval architecture */
    MESA_CAP_EVC_CARACAL,                   /**< EVC for Caracal architecture */
    MESA_CAP_EVC_PORT,                      /**< EVC port configuration */
    MESA_CAP_EVC_PORT_EVC,                  /**< EVC port and EVC configuration */
    MESA_CAP_EVC_ETREE,                     /**< EVC E-tree support */
    MESA_CAP_EVC_POLICY,                    /**< ACL policy number per EVC */
    MESA_CAP_EVC_ECE_ETYPE,                 /**< ECE EType match */
    MESA_CAP_EVC_ECE_LLC,                   /**< ECE LLC match */
    MESA_CAP_EVC_ECE_SNAP,                  /**< ECE SNAP match */
    MESA_CAP_EVC_ECE_DMAC,                  /**< ECE DMAC match */
    MESA_CAP_EVC_ECE_DIP,                   /**< ECE DIP match */
    MESA_CAP_EVC_ECE_INNER_TAG,             /**< ECE inner tag match */
    MESA_CAP_EVC_ECE_MASQ,                  /**< ECE masqueraded match */
    MESA_CAP_EVC_ECE_ACT_OT,                /**< ECE outer tag action */
    MESA_CAP_EVC_ECE_ACT_OT_VID,            /**< ECE outer tag VID action */
    MESA_CAP_EVC_ECE_ACT_PCP_MODE,          /**< ECE PCP mode action */
    MESA_CAP_EVC_ECE_ACT_DEI_MODE,          /**< ECE DEI mode action */
    MESA_CAP_EVC_ECE_ACT_PCP_DEI_PRES,      /**< ECE PCP/DEI preservation action */
    MESA_CAP_EVC_ECE_ACT_IT,                /**< ECE inner tag action */
    MESA_CAP_EVC_ECE_ACT_POLICER,           /**< ECE policer mapping */
    MESA_CAP_EVC_ECE_ACT_PRIO,              /**< ECE priority mapping */
    MESA_CAP_EVC_ECE_ACT_DPL,               /**< ECE DPL mapping */
    MESA_CAP_EVC_ECE_ACT_DISCARD,           /**< ECE discard action */
    MESA_CAP_EVC_COUNTERS,                  /**< EVC counters per EVC/ECE */
    MESA_CAP_EVC_COSID_COUNTERS,            /**< EVC counters per COSID */
    MESA_CAP_EVC_PORT_KEY_TYPE,             /**< EVC port key type */
    MESA_CAP_EVC_PORT_DMAC_DIP,             /**< EVC port DMAC/DIP selection */

    // MPLS
    MESA_CAP_MPLS = 1000,                   /**< MPLS support */
    MESA_CAP_MPLS_LOCAL_TC_MAP,             /**< TC QOS mapping tables are local to MPLS, not global */

    // HQoS
    MESA_CAP_HQOS_CNT = 1100,               /**< Number of HQoS entries */
    MESA_CAP_HQOS_STAT_CNT_SERVICE,         /**< Status for number of services */
    MESA_CAP_HQOS_SHAPER_RT,                /**< HQoS shaper rate type */

    // OAM
    MESA_CAP_VOP = 1200,                    /**< OAM/VOE support */
    MESA_CAP_VOP_CFM,                       /**< OAM/VOE supporting full 802.1 CFM implementation */
    MESA_CAP_VOP_V0,                        /**< OAM generation 0 (Maserati) */
    MESA_CAP_VOP_V1,                        /**< OAM generation 1 (Serval-1) */
    MESA_CAP_VOP_V2,                        /**< OAM generation 2 (Jaguar-2/Serval-T/SparX-5) */
    MESA_CAP_VOP_TAGGING,                   /**< VOE can handle different tagging by configuration of the VOE residence port */
    MESA_CAP_VOP_PATH_SERVICE_VOE_CNT,      /**< Number of possible path/service VOEs */
    MESA_CAP_VOP_PORT_VOE_CNT,              /**< Number of possible port VOEs */
    MESA_CAP_VOP_VOE_CNT,                   /**< Total count of VOEs */
    MESA_CAP_VOP_DOWN_VOI_CNT,              /**< Number of possible down VOIs */
    MESA_CAP_VOP_UP_VOI_CNT,                /**< Number of possible up VOIs */
    MESA_CAP_VOP_VOI_CNT,                   /**< Total count of VOIs */
    MESA_CAP_VOP_USED_AS_PTP_PROTOCOL,      /**< OAM is used for implementing distributed transparent clocks */
    MESA_CAP_VOP_EVENT_ARRAY_SIZE,          /**< Size in uint32_t's of VOE event mask */
    MESA_CAP_VOP_EVENT_SUPPORTED,           /**< Event mask with the events supported on a given platform */
    MESA_CAP_VOP_CCM_DEFECT,                /**< CCM Defect are calculated as described in G.8021 6.1.2 */

    // ClockModule
    MESA_CAP_CLOCK = 1300,                  /**< Clock */

    // SYNCE
    MESA_CAP_SYNCE = 1400,                  /**< Synchronization */
    MESA_CAP_SYNCE_CLK_CNT,                 /**< Number of recovered clock outputs */
    MESA_CAP_SYNCE_IN_TYPE,                 /**< Clock input type */
    MESA_CAP_SYNCE_OUT_STATION,             /**< Station clock output */
    MESA_CAP_SYNCE_ANN_AUTO_TRANSMIT,       /**< Sync and Announce packet auto generation in hardware */
    MESA_CAP_SYNCE_USE_SWITCH_SELECTOR_WITH_PHY,  /**< Indicates if switch selector shall be setup when a PHY port is selected */
    MESA_CAP_SYNCE_ALWAYS_USE_COPPER_MEDIA_CLK,   /**< Indicates that copper media recovered clock shall be used also for PHY ports */
    MESA_CAP_SYNCE_10G_DNU,                 /**< Indicates that 10G ports cannot be used as Synce source */
    MESA_CAP_SYNCE_SEPARATE_TIMING_DOMAINS, /**< Indicates that SyncE and PTP are using two separate timing domains */

    // Timestamping
    MESA_CAP_TS = 1500,                     /**< Timestamping */
    MESA_CAP_TS_LATENCY_COMP,               /**< Ingress and egress latency compensation hardware support */
    MESA_CAP_TS_ORG_TIME,                   /**< OriginTimestamp update hardware support */
    MESA_CAP_TS_P2P_DELAY_COMP,             /**< Peer-to-peer path delay compensation hardware support */
    MESA_CAP_TS_ASYMMETRY_COMP,             /**< Path delay asymmetry compensation hardware support */
    MESA_CAP_TS_HW_TIME_CNT_PR_SEC,         /**< Number of clock cycle counts pr sec */
    MESA_CAP_TS_HW_TIME_NSEC_PR_CNT,        /**< Number of nanoseconds pr clock count */
    MESA_CAP_TS_HW_TIME_WRAP_LIMIT,         /**< Time counter wrap around limit */
    MESA_CAP_TS_HW_TIME_MIN_ADJ_RATE,       /**< minimum adjustment rate in units of 0,1 ppb */
    MESA_CAP_TS_IO_CNT,                     /**< Number of pins, that can be used as 1PPS or clock output/input. */
    MESA_CAP_TS_DOMAIN_CNT,                 /**< Number of domains */
    MESA_CAP_TS_RESP_CTRL_CNT,              /**< Number of auto delay response controllers */
    MESA_CAP_TS_MISSING_INTERRUPT,          /**< Timestamp interrupts (in general) not supported */
    MESA_CAP_TS_MISSING_TX_INTERRUPT,       /**< TX timestamp interrupt not supported */
    MESA_CAP_TS_ALT_CLOCK,                  /**< Alternative clock mode */
    MESA_CAP_TS_OAM,                        /**< OAM timestamp */
    MESA_CAP_TS_DELAY_REQ_AUTO_RESP,        /**< Delay request/response processing per MESA_CAP_TS_DOMAIN_CNT number of domains. */
    MESA_CAP_TS_PTP_RS422,                  /**< RS422 Timestamp based interface supported  */
    MESA_CAP_TS_MISSING_PTP_ON_INTERNAL_PORTS,    /**< Indicates that support for PTP on internal ports is missing */
    MESA_CAP_TS_PPS_VIA_CONFIGURABLE_IO_PINS,     /**< Indicates that PPS can be configured to use an I/O pin */
    MESA_CAP_TS_PPS_MODE_OVERRULES_CLK_OUT, /**< Indicates that PPS mode (not disabled) overrules clock out enable */
    MESA_CAP_TS_PPS_OUT_OVERRULES_CLK_OUT,  /**< Indicates that PPS output (enabled) overrules clock out enable */
    MESA_CAP_TS_HAS_PTP_IO_PIN,              /**< Indicates the presence of an I/O pin for PTP */
    MESA_CAP_TS_HAS_ALT_PIN,                /**< Indicates the presence of an alternative pin for PPS */
    MESA_CAP_TS_PPS_IN_VIA_IO_PIN,          /**< Indicates the presence of IO pin for PPS input t*/
    MESA_CAP_TS_USE_EXTERNAL_INPUT_SERVO,   /**< Use an alternative servo originally implemented for Luton26 */
    MESA_CAP_TS_TOD_INTERNAL_TC_MODE,       /**< Indicates internal Timestamp capability support */
    MESA_CAP_TS_HW_FWD_P2P_1STEP,           /**< Hardware supports forwarding of 1-step TC P2P packets */
    MESA_CAP_TS_HW_FWD_E2E_1STEP_INTERNAL,  /**< Hardware supports forwarding of 1-step TC E2E packets on internal ports */
    MESA_CAP_TS_C_DTC_SUPPORTED,            /**< Indicates that concatenated distributed clocks are supported */
    MESA_CAP_TS_INTERNAL_MODE_SUPPORTED,    /**< Indicates that timestamp mode MESA_TS_MODE_INTERNAL is supported */
    MESA_CAP_TS_TWOSTEP_ALWAYS_REQUIRED,    /**< Indicates that two-step mode is always required */
    MESA_CAP_TS_INTERNAL_PORTS_REQ_TWOSTEP, /**< Transparent clock via internal ports require two-step operation */
    MESA_CAP_TS_BC_TS_COMBO_IS_SPECIAL,     /**< The combination of a BC and a TS needs to be handled as a special case */
    MESA_CAP_TS_TWOSTEP_USE_PTP_ID,         /**< Indicates if ptp_id field of packet is used for timestamp id in two-step transmission. */

    // TOD
    MESA_CAP_TOD_SAMPLES_PR_SEC,            /**< The number of times per second that the timeofday is sampled */

    // PHY
    MESA_CAP_PHY_10G = 1600,                /**< Deprecated: 10G PHY API */
    MESA_CAP_PHY_TS,                        /**< Deprecated: PHY timestamping */
    MESA_CAP_PHY_MALIBU_10G_PLUGIN_MOUNTED, /**< Deprecated: Board has a Malibu 10G PHY plugin mounted */
    MESA_CAP_PHY_TS_NUMBER_OF_ENGINES,      /**< Deprecated: Number of PHY timestamping engines */
    MESA_CAP_PHY_10GBASE_KR,                /**< Deprecated: 10G PHY support for 10GBASE-KR */

    // Switching Chip
    MESA_CAP_SOC_FAMILY = 1700,

    // PHY-MACSEC
    MESA_CAP_PHY_MACSEC = 1800,             /**< Deprecated: PHY MACSEC */
    MESA_CAP_PHY_MACSEC_SA_CNT,             /**< Deprecated: Max number of supported secure associations in a given PHY */
    MESA_CAP_PHY_MACSEC_SC_CNT,             /**< Deprecated: Max number of supported secure channels in a given PHY */
    MESA_CAP_PHY_MACSEC_SECY_CNT,           /**< Deprecated: Max number of supported SECY instances in a given PHY */

    // MEP
    MESA_CAP_MEP_LUTON26 = 1900,            /**< MEP for Luton26 */
    MESA_CAP_MEP_SERVAL,                    /**< MEP for Serval */
    MESA_CAP_MEP_JAGUAR2,                   /**< MEP for Jaguar2 */
    MESA_CAP_MEP_LBR_MCE_HW_SUPPORT,        /**< MEP has LBR MCE Hardware Support */
    MESA_CAP_MEP_TST_BITRATE_MBPS,          /**< MEP test bitrate in Mbps */
    MESA_CAP_MEP_PROP_DELAY_MEASUREMENT,    /**< MEP Proprietary Delay Measurement */

    // Hardware Protection
    MESA_CAP_HW_PROT = 2000,                /**< Hardware Protection */
    MESA_CAP_HW_PROT_MPLS,                  /**< Hardware Protection for MPLS flows */

    // Init
    MESA_CAP_INIT_CORE_CLOCK = 2100,        /**< Core Clock (LCPLL) */

    // MRP
    MESA_CAP_MRP = 2200,                    /**< Media Redundancy Protocol - IEC 62439-2 MRP */
    MESA_CAP_MRP_CNT,                       /**< Total count of MRPs */

} mesa_cap_t;

typedef struct mesa_state_s *mesa_inst_t;   /**< Opaque instance */
typedef uint32_t (*mesa_cap_callback_t)(const void *inst, int cap);
/** \brief Capability hook data */
typedef struct mesa_cap_callback_data {
    const mesa_cap_callback_t cb;        /**< Function to call */
    const void *inst;                    /**< Instance data to pass */
} mesa_cap_callback_data_t;
void mesa_cap_callback_add(mesa_inst_t inst, mesa_cap_callback_data_t *hook);
uint32_t mesa_capability(mesa_inst_t inst, int cap);
uint32_t mesa_port_cnt(mesa_inst_t inst);

#define MESA_CAP(expr) mesa_capability(NULL, expr)

#include <microchip/ethernet/hdr_end.h>
#endif  // _MICROCHIP_ETHERNET_SWITCH_API_CAPABILITY_
