// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief Features and options
 * \details This header file describes target features and compile-time options
 */

#ifndef _VTSS_OPTIONS_H_
#define _VTSS_OPTIONS_H_

/* ================================================================= *
 *  Features
 * ================================================================= */
#if defined(VTSS_CHIP_7546) || defined(VTSS_CHIP_7549) || defined(VTSS_CHIP_7552) || \
    defined(VTSS_CHIP_7556) || defined(VTSS_CHIP_7558)
#define VTSS_ARCH_SPARX5                         /**< Jaguar-3/SparX-5 architecture */
#endif

#if defined(VTSS_CHIP_7546TSN) || defined(VTSS_CHIP_7549TSN) || defined(VTSS_CHIP_7552TSN) || \
    defined(VTSS_CHIP_7556TSN) || defined(VTSS_CHIP_7558TSN)
#define VTSS_ARCH_SPARX5                         /**< Jaguar-3/SparX-V architecture */
#define VTSS_ARCH_S5I                            /**< SparX-5i architecture */
#endif

#if defined(VTSS_ARCH_SPARX5)
// FA-FIXME: This set must be revised
#define VTSS_FEATURE_10G                          /**< 10G ports */
#define VTSS_FEATURE_PORT_KR_IRQ                  /**< 10G/25GBase KR, 802.3ap clause 72 (training) and clause 73 (aneg). IRQ controlled */
// //#define VTSS_FEATURE_WARM_START              /**< Warm start */
#define VTSS_FEATURE_MISC                         /**< Miscellaneous */
#define VTSS_FEATURE_SERIAL_GPIO                  /**< Serial GPIO control */
#define VTSS_FEATURE_PORT_CONTROL                 /**< Port control */
//#define VTSS_FEATURE_PORT_IFH                    /**< Port IFH control */
#define VTSS_FEATURE_CLAUSE_37                    /**< IEEE 802.3 clause 37 auto-negotiation */
#define VTSS_FEATURE_EXC_COL_CONT                 /**< Excessive collision continuation */
#define VTSS_FEATURE_PORT_CNT_ETHER_LIKE          /**< Ethernet-like counters */
#define VTSS_FEATURE_PORT_CNT_BRIDGE              /**< Bridge counters */
// #define VTSS_FEATURE_VSTAX                       /**< VStaX stacking */
// #define VTSS_FEATURE_VSTAX_V2                    /**< VStaX stacking, as implemented on Jaguar2 (VStaX2/AF) */
// #define VTSS_FEATURE_PORT_MUX                    /**< Port mux between serdes blocks and ports */
#define VTSS_FEATURE_PFC                          /**< 802.1Qbb Priority Flow Control */
#define VTSS_FEATURE_QOS                          /**< QoS */
#define VTSS_FEATURE_QCL                          /**< QoS: QoS Control Lists */
#define VTSS_FEATURE_QCL_KEY_INNER_TAG            /**< QoS: QoS Control Lists has inner tag */
#define VTSS_FEATURE_QCL_KEY_DMAC                 /**< QoS: QoS Control Lists has destination MAC address */
#define VTSS_FEATURE_QCL_KEY_DIP                  /**< QoS: QoS Control Lists has destination IP address */
#define VTSS_FEATURE_QCL_MAP_ACTION               /**< QoS: QoS Control Lists has ingress map action */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL    /**< QoS: Port Policer has Drop Precedence Bypas Level support */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2  /**< QoS: Port Policer has Traffic_Type Mask version 2 support */
#define VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT       /**< QoS: Scheduler supports variable number of DWRR inputs */
#define VTSS_FEATURE_QOS_COSID_CLASSIFICATION     /**< QoS: Has COSID classification per port */
#define VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB       /**< QoS: Egress shapers has DLB support */
#define VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT        /**< Qos: Egress shapers have rate type support - line or date rate */
#define VTSS_FEATURE_QOS_WRED_V3                  /**< QoS: WRED global - per queue (0..7), per dpl (1..3), per group (0..2) */
#define VTSS_FEATURE_QOS_INGRESS_MAP              /**< QoS: Has Ingress Map Table */
#define VTSS_FEATURE_QOS_EGRESS_MAP               /**< QoS: Has Egress Map Table */
#define VTSS_FEATURE_QOS_HSCH_LEAK_LISTS          /**< QoS: Has leak lists for scheduler elements */
#define VTSS_FEATURE_QOS_POLICER_DLB             /**< DLB policers */
#define VTSS_FEATURE_QOS_CPU_PORT_SHAPER          /**< QoS: Has CPU port shaper */
#define VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER         /**< QoS: Has CPU queue shaper */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH /**< QoS: Queue has cut-through support */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB /**< QoS: Egress Queue Shapers has CRedit Based shaper support */
#define VTSS_FEATURE_QOS_TAS                      /**< QoS: Time Aware Scheduling (802.1Qbv) */
// Unused VTSS_FEATURE_QOS_ defines (they exist for backwards compatibility):
#define VTSS_FEATURE_QCL_V2                       /**< QoS: QoS Control Lists, V2 features */
#define VTSS_FEATURE_QCL_KEY_S_TAG                /**< QoS: QoS Control Lists has S tag support */
#define VTSS_FEATURE_QCL_PCP_DEI_ACTION           /**< QoS: QoS Control Lists has PCP and DEI action */
#define VTSS_FEATURE_QCL_POLICY_ACTION            /**< QoS: QoS Control Lists has policy action */
#define VTSS_FEATURE_QOS_POLICER_UC_SWITCH        /**< QoS: Unicast policer per switch */
#define VTSS_FEATURE_QOS_POLICER_MC_SWITCH        /**< QoS: Multicast policer per switch */
#define VTSS_FEATURE_QOS_POLICER_BC_SWITCH        /**< QoS: Broadcast policer per switch */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT         /**< QoS: Port Policer Extensions */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_FPS     /**< QoS: Port Policer has frame rate support */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_FC      /**< QoS: Port Policer has flow control support */
#define VTSS_FEATURE_QOS_QUEUE_POLICER            /**< QoS: Has Ingress Queue Policers */
#define VTSS_FEATURE_QOS_QUEUE_TX                 /**< QoS: Has TX Queue support */
#define VTSS_FEATURE_QOS_SCHEDULER_V2             /**< QoS: 2. version of scheduler */
#define VTSS_FEATURE_QOS_TAG_REMARK_V2            /**< QoS: 2. version of tag priority remarking */
#define VTSS_FEATURE_QOS_CLASSIFICATION_V2        /**< QoS: 2. version of classification */
#define VTSS_FEATURE_QOS_DSCP_CLASS_DP_AWARE      /**< QoS: DSCP classification is DP aware */
#define VTSS_FEATURE_QOS_DSCP_REMARK              /**< QoS: Has DSCP remarking */
#define VTSS_FEATURE_QOS_DSCP_REMARK_V2           /**< QoS: 2. version of DSCP remarking */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS     /**< QoS: Has Egress Queue Shapers */
#define VTSS_FEATURE_PACKET                       /**< CPU Rx/Tx frame configuration */
// #define VTSS_FEATURE_PACKET_TX                   /**< CPU Tx frame */
// #define VTSS_FEATURE_PACKET_RX                   /**< CPU Rx frame */
// #define VTSS_FEATURE_PACKET_GROUPING             /**< Extraction and injection occurs through extraction and injection groups rather than queues. */
// #define VTSS_FEATURE_PACKET_PORT_REG             /**< Packet registration per port */
#define VTSS_FEATURE_PACKET_PORT_REG_DISCARD      /**< Packet discard registration per port */
#define VTSS_FEATURE_PACKET_PORT_L2CP_REG         /**< Packet registration per port and L2CP */
#define VTSS_FEATURE_PACKET_PIPELINE_PT           /**< Packet Tx supports injection at specific chip pipeline points */
#define VTSS_FEATURE_LAYER2                       /**< Layer 2 (switching) */
#define VTSS_FEATURE_PVLAN                        /**< Private VLANs */
#define VTSS_FEATURE_VLAN_PORT_V2                 /**< VLAN port configuration, V2 features */
#define VTSS_FEATURE_VLAN_TX_TAG                  /**< VLAN tagging per (VID, port) */
#define VTSS_FEATURE_VLAN_SVL                     /**< Shared VLAN Learning */
#define VTSS_FEATURE_VCL_KEY_DMAC                 /**< VCL entry has destination MAC address */
#define VTSS_FEATURE_VCL_KEY_DIP                  /**< VCL entry has destination IP address */
#define VTSS_FEATURE_IPV4_MC_SIP                  /**< Source specific IPv4 multicast */
#define VTSS_FEATURE_IPV6_MC_SIP                  /**< Source specific IPv6 multicast */
#define VTSS_FEATURE_MAC_AGE_AUTO                 /**< Automatic MAC address ageing */
#define VTSS_FEATURE_MAC_CPU_QUEUE                /**< CPU queue per MAC address */
#define VTSS_FEATURE_LAYER3                       /**< Layer 3 (routing) */
#define VTSS_FEATURE_EEE                          /**< Energy Efficient Ethernet */
#define VTSS_FEATURE_FAN                          /**< Fan control */
#define VTSS_FEATURE_TEMP_SENSOR                  /**< Temperature Sensor */
#define VTSS_FEATURE_VCAP                         /**< VCAP */
#define VTSS_FEATURE_ACL                          /**< Access Control Lists */
#define VTSS_FEATURE_HACL                         /**< Hierarchical Access Control Lists */
#define VTSS_FEATURE_ACL_V2                      /**< Access Control Lists, V2 features */
#define VTSS_FEATURE_ACL_EXT_DIP                 /**< ACL extended IPv6 rule with DIP matching */
#define VTSS_FEATURE_ACL_EXT_MAC                 /**< ACL extended IPv4/IPv6 rules with MAC address matching */
#define VTSS_FEATURE_VCL                         /**< VLAN Control Lists */
#define VTSS_FEATURE_TIMESTAMP                   /**< Packet timestamp feature (for PTP) */
#define VTSS_FEATURE_TIMESTAMP_ONE_STEP          /**< ONESTEP timestamp hardware support */
#define VTSS_FEATURE_TIMESTAMP_LATENCY_COMP      /**< Ingress and egress latency compensation hardware support */
#define VTSS_FEATURE_TIMESTAMP_ORG_TIME          /**< OriginTimestamp update hardware support */
#define VTSS_FEATURE_TIMESTAMP_P2P_DELAY_COMP    /**< Peer-to-peer path delay compensation hardware support */
#define VTSS_FEATURE_TIMESTAMP_ASYMMETRY_COMP    /**< Path delay asymmetry compensation hardware support */
#define VTSS_FEATURE_PTP_RS422                   /**< Support for the RS422 serial/1PPS interface */
#define VTSS_FEATURE_DELAY_REQ_AUTO_RESP         /**< Delay_Req/Resp processing supported in hardware */
// #define VTSS_FEATURE_SYNC_ANN_AUTO_TRANSMIT      /**< Sync and Announce packet auto generation in hardware */
#define VTSS_FEATURE_NPI                         /**< NPI port */
#define VTSS_FEATURE_LED_POW_REDUC               /**< LED power reduction */
#define VTSS_FEATURE_INTERRUPTS                   /**< Port Interrupt support */
#define VTSS_FEATURE_IRQ_CONTROL                  /**< General IRQ support */
#define VTSS_FEATURE_VLAN_TRANSLATION            /**< VLAN Translation */
#define VTSS_FEATURE_SFLOW                       /**< sFlow feature    */
#define VTSS_FEATURE_MIRROR_CPU                  /**< CPU mirroring */
#define VTSS_FEATURE_SERDES_MACRO_SETTINGS       /**< Hooks for Serdes Macro configuration */
// #define VTSS_FEATURE_10GBASE_KR                  /**< KR */
#define VTSS_FEATURE_AFI_SWC                      /**< AFI */
#define VTSS_AFI_V2                               /**< AFI API version 2 */
// #if !defined(VTSS_OPT_VCORE_IV)
//   #define VTSS_OPT_VCORE_IV 1                   /**< Internal VCore-IV (ARM) CPU enabled by default */
// #endif
// #if VTSS_OPT_VCORE_IV != 0
//   #define VTSS_FEATURE_FDMA                      /**< Frame DMA */
//   #ifndef VTSS_OPT_FDMA_VER
//     #define VTSS_OPT_FDMA_VER 3                  /**< Use of VTSS_OPT_FDMA_VER is the preferred way to indicate which version of the FDMA API is required */
//   #endif
//   #if VTSS_OPT_FDMA_VER != 3
//     #error "SPARX4 only supports FDMA API v3"
//   #endif
// #endif /* VTSS_OPT_VCORE_IV != 0 */
// #if !defined(VTSS_OPT_PCIE_ACCESS) && !defined(VTSS_OPT_VRAP_ACCESS)
// #define VTSS_OPT_PCIE_ACCESS                    /**< PCIe access from external CPU */
// #endif
#define VTSS_FEATURE_CORE_CLOCK                    /**< Core Clock LC-PLL */
#define VTSS_FEATURE_XFLOW                      /**< Ingress and egress flows */
#define VTSS_FEATURE_XSTAT                      /**< Ingress and egress statistics */
#define VTSS_FEATURE_XDLB                       /**< DLB policers allocated dynamically */
#define VTSS_FEATURE_VOP                        /**< Y.1731/IEEE802.1ag OAM */
#endif /* VTSS_ARCH_SPARX5 */

#if defined(VTSS_ARCH_S5I)
#define VTSS_FEATURE_QOS_FRAME_PREEMPTION        /**< QoS: Frame Preemption support (802.1Qbu and 802.3br) */
#define VTSS_FEATURE_SYNCE                       /**< SYNCE - L1 syncronization feature */
#define VTSS_FEATURE_FRER                        /**< IEEE 802.1CB: Frame Replication and Elimination for Reliability */
#define VTSS_FEATURE_PSFP                        /**< IEEE 802.1Qci: Per-Stream Filtering and Policing */
#elif defined(VTSS_ARCH_SPARX5)
#define VTSS_FEATURE_VLAN_COUNTERS               /**< VLAN counters are only supported for SMB devices without OAM */
#endif /* VTSS_ARCH_SPARX5_CE */

#if defined(VTSS_CHIP_SPARX_IV_44) || defined(VTSS_CHIP_SPARX_IV_52) || defined(VTSS_CHIP_SPARX_IV_80) || defined(VTSS_CHIP_SPARX_IV_90)
#define VTSS_ARCH_JAGUAR_2                     /**< Jaguar-2 architecture */
#define VTSS_ARCH_JAGUAR_2_C                   /**< Jaguar-2 revision C architecture */
#define VTSS_FEATURE_VLAN_COUNTERS             /**< VLAN counters are only supported for SMB devices without OAM */
#endif /* VTSS_CHIP_SPARX_IV */

#if defined(VTSS_CHIP_SERVAL_2) || defined(VTSS_CHIP_LYNX_2) || defined(VTSS_CHIP_JAGUAR_2)
#define VTSS_ARCH_JAGUAR_2_C                     /**< Jaguar-2 revision C architecture */
#define VTSS_ARCH_JAGUAR_2_CE                    /**< Jaguar-2 CE architecture */
#endif /* VTSS_CHIP_JAGUAR_2 */

#if defined(VTSS_ARCH_JAGUAR_2_C)
#define VTSS_ARCH_JAGUAR_2                       /**< Jaguar-2 architecture */
#define VTSS_FEATURE_10G                         /**< 10G ports */
#define VTSS_FEATURE_PORT_KR                     /**< 10GBase KR, 802.3ap clause 72 (training) and clause 73 (aneg). JR2-C version.  */
#define VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER        /**< QoS: Has CPU queue shaper */
#endif /* VTSS_ARCH_JAGUAR_2_C */

#if defined(VTSS_CHIP_SERVAL_T) || defined(VTSS_CHIP_SERVAL_TP) || defined(VTSS_CHIP_SPARX_IV_34)
#define VTSS_ARCH_JAGUAR_2                       /**< Jaguar-2 architecture */
#define VTSS_ARCH_SERVAL_T                       /**< Serval-T architecture */
#endif /* VTSS_CHIP_SERVAL_T/SPARX_IV_34 */

#if defined(VTSS_CHIP_SERVAL_TE) || defined(VTSS_CHIP_SERVAL_TEP) || defined(VTSS_CHIP_SERVAL_2_LITE) || defined(VTSS_CHIP_SERVAL_TE10)
#define VTSS_ARCH_JAGUAR_2                       /**< Jaguar-2 architecture */
#define VTSS_ARCH_SERVAL_T                       /**< Serval-T architecture */
#define VTSS_ARCH_JAGUAR_2_CE                    /**< Jaguar-2 CE architecture */
#if defined(VTSS_CHIP_SERVAL_2_LITE) || defined(VTSS_CHIP_SERVAL_TE10)
#define VTSS_FEATURE_10G                         /**< 10G ports */
#endif /* VTSS_CHIP_SERVAL_2_LITE/SERVAL_TE10 */
#endif /* VTSS_CHIP_SERVAL_T CE variants */

#if defined(VTSS_CHIP_SERVAL_TP) || defined(VTSS_CHIP_SERVAL_TEP) || defined(VTSS_CHIP_SERVAL_TE10)
#define VTSS_FEATURE_CLOCK                     /**< Omega soft IP */
#endif /* VTSS_CHIP_SERVAL_T/TE/TE10 */

#if defined(VTSS_ARCH_JAGUAR_2)
//#define VTSS_FEATURE_WARM_START                  /**< Warm start */
#define VTSS_FEATURE_MISC                        /**< Miscellaneous */
#define VTSS_FEATURE_SERIAL_GPIO                 /**< Serial GPIO control */
#define VTSS_FEATURE_PORT_CONTROL                /**< Port control */
#define VTSS_FEATURE_PORT_IFH                    /**< Port IFH control */
#define VTSS_FEATURE_CLAUSE_37                   /**< IEEE 802.3 clause 37 auto-negotiation */
#define VTSS_FEATURE_EXC_COL_CONT                /**< Excessive collision continuation */
#define VTSS_FEATURE_PORT_CNT_ETHER_LIKE         /**< Ethernet-like counters */
#define VTSS_FEATURE_PORT_CNT_BRIDGE             /**< Bridge counters */
#define VTSS_FEATURE_VSTAX                       /**< VStaX stacking */
#define VTSS_FEATURE_VSTAX_V2                    /**< VStaX stacking, as implemented on Jaguar2 (VStaX2/AF) */
#define VTSS_FEATURE_PORT_MUX                    /**< Port mux between serdes blocks and ports */
#define VTSS_FEATURE_PFC                         /**< 802.1Qbb Priority Flow Control */
#define VTSS_FEATURE_QOS                         /**< QoS */
#define VTSS_FEATURE_QCL                         /**< QoS: QoS Control Lists */
#define VTSS_FEATURE_QCL_V2                      /**< QoS: QoS Control Lists, V2 features */
#define VTSS_FEATURE_QCL_KEY_S_TAG               /**< QoS: QoS Control Lists has S tag support */
#define VTSS_FEATURE_QCL_KEY_INNER_TAG           /**< QoS: QoS Control Lists has inner tag */
#define VTSS_FEATURE_QCL_KEY_DMAC                /**< QoS: QoS Control Lists has destination MAC address */
#define VTSS_FEATURE_QCL_KEY_DIP                 /**< QoS: QoS Control Lists has destination IP address */
#define VTSS_FEATURE_QCL_PCP_DEI_ACTION          /**< QoS: QoS Control Lists has PCP and DEI action */
#define VTSS_FEATURE_QCL_POLICY_ACTION           /**< QoS: QoS Control Lists has policy action */
#define VTSS_FEATURE_QCL_MAP_ACTION              /**< QoS: QoS Control Lists has ingress map action */
#define VTSS_FEATURE_QOS_POLICER_UC_SWITCH       /**< QoS: Unicast policer per switch */
#define VTSS_FEATURE_QOS_POLICER_MC_SWITCH       /**< QoS: Multicast policer per switch */
#define VTSS_FEATURE_QOS_POLICER_BC_SWITCH       /**< QoS: Broadcast policer per switch */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT        /**< QoS: Port Policer Extensions */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_FPS    /**< QoS: Port Policer has frame rate support */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_FC     /**< QoS: Port Policer has flow control support */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL   /**< QoS: Port Policer has Drop Precedence Bypas Level support */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2 /**< QoS: Port Policer has Traffic_Type Mask version 2 support */
#define VTSS_FEATURE_QOS_QUEUE_POLICER           /**< QoS: Has Ingress Queue Policers */
#define VTSS_FEATURE_QOS_QUEUE_TX                /**< QoS: Has TX Queue support */
#define VTSS_FEATURE_QOS_SCHEDULER_V2            /**< QoS: 2. version of scheduler */
#define VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT      /**< QoS: Scheduler supports variable number of DWRR inputs */
#define VTSS_FEATURE_QOS_TAG_REMARK_V2           /**< QoS: 2. version of tag priority remarking */
#define VTSS_FEATURE_QOS_CLASSIFICATION_V2       /**< QoS: 2. version of classification */
#define VTSS_FEATURE_QOS_COSID_CLASSIFICATION    /**< QoS: Has COSID classification per port */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS    /**< QoS: Has Egress Queue Shapers */
#define VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB      /**< QoS: Egress shapers has DLB support */
#define VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT       /**< Qos: Egress shapers have rate type support - line or date rate */
#define VTSS_FEATURE_QOS_DSCP_CLASS_DP_AWARE     /**< QoS: DSCP classification is DP aware */
#define VTSS_FEATURE_QOS_DSCP_REMARK             /**< QoS: Has DSCP remarking */
#define VTSS_FEATURE_QOS_DSCP_REMARK_V2          /**< QoS: 2. version of DSCP remarking */
#define VTSS_FEATURE_QOS_WRED_V3                 /**< QoS: WRED global - per queue (0..7), per dpl (1..3), per group (0..2) */
#define VTSS_FEATURE_QOS_INGRESS_MAP             /**< QoS: Has Ingress Map Table */
#define VTSS_FEATURE_QOS_EGRESS_MAP              /**< QoS: Has Egress Map Table */
#define VTSS_FEATURE_QOS_HSCH_LEAK_LISTS         /**< QoS: Has leak lists for scheduler elements */
#define VTSS_FEATURE_QOS_POLICER_DLB             /**< DLB policers */
#define VTSS_FEATURE_QOS_CPU_PORT_SHAPER         /**< QoS: Has CPU port shaper */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB /**< QoS: Egress Queue Shapers has CRedit Based shaper support */
#define VTSS_FEATURE_PACKET                      /**< CPU Rx/Tx frame configuration */
#define VTSS_FEATURE_PACKET_TX                   /**< CPU Tx frame */
#define VTSS_FEATURE_PACKET_RX                   /**< CPU Rx frame */
#define VTSS_FEATURE_PACKET_GROUPING             /**< Extraction and injection occurs through extraction and injection groups rather than queues. */
#define VTSS_FEATURE_PACKET_PORT_REG             /**< Packet registration per port */
#define VTSS_FEATURE_PACKET_PORT_REG_DISCARD     /**< Packet discard registration per port */
#define VTSS_FEATURE_PACKET_PORT_L2CP_REG        /**< Packet registration per port and L2CP */
#define VTSS_FEATURE_PACKET_PIPELINE_PT          /**< Packet Tx supports injection at specific chip pipeline points */
#define VTSS_FEATURE_LAYER2                      /**< Layer 2 (switching) */
#define VTSS_FEATURE_PVLAN                       /**< Private VLANs */
#define VTSS_FEATURE_VLAN_PORT_V2                /**< VLAN port configuration, V2 features */
#define VTSS_FEATURE_VLAN_TX_TAG                 /**< VLAN tagging per (VID, port) */
#define VTSS_FEATURE_VLAN_SVL                    /**< Shared VLAN Learning */
#define VTSS_FEATURE_VCL_KEY_DMAC                /**< VCL entry has destination MAC address */
#define VTSS_FEATURE_VCL_KEY_DIP                 /**< VCL entry has destination IP address */
#define VTSS_FEATURE_IPV4_MC_SIP                 /**< Source specific IPv4 multicast */
#define VTSS_FEATURE_IPV6_MC_SIP                 /**< Source specific IPv6 multicast */
#define VTSS_FEATURE_MAC_AGE_AUTO                /**< Automatic MAC address ageing */
#define VTSS_FEATURE_MAC_CPU_QUEUE               /**< CPU queue per MAC address */
#define VTSS_FEATURE_LAYER3                      /**< Layer 3 (routing) */
#define VTSS_FEATURE_EEE                         /**< Energy Efficient Ethernet */
#define VTSS_FEATURE_FAN                         /**< Fan control */
#define VTSS_FEATURE_TEMP_SENSOR                 /**< Temperature Sensor */
#define VTSS_FEATURE_VCAP                        /**< VCAP */
#define VTSS_FEATURE_ACL                         /**< Access Control Lists */
#define VTSS_FEATURE_ACL_V2                      /**< Access Control Lists, V2 features */
#define VTSS_FEATURE_ACL_EXT_DIP                 /**< ACL extended IPv6 rule with DIP matching */
#define VTSS_FEATURE_ACL_EXT_MAC                 /**< ACL extended IPv4/IPv6 rules with MAC address matching */
#define VTSS_FEATURE_VCL                         /**< VLAN Control Lists */
#define VTSS_FEATURE_TIMESTAMP                   /**< Packet timestamp feature (for PTP) */
#define VTSS_FEATURE_TIMESTAMP_ONE_STEP          /**< ONESTEP timestamp hardware support */
#define VTSS_FEATURE_TIMESTAMP_LATENCY_COMP      /**< Ingress and egress latency compensation hardware support */
#define VTSS_FEATURE_TIMESTAMP_ORG_TIME          /**< OriginTimestamp update hardware support */
#define VTSS_FEATURE_TIMESTAMP_P2P_DELAY_COMP    /**< Peer-to-peer path delay compensation hardware support */
#define VTSS_FEATURE_TIMESTAMP_ASYMMETRY_COMP    /**< Path delay asymmetry compensation hardware support */
#define VTSS_FEATURE_PTP_RS422                   /**< Support for the RS422 serial/1PPS interface */
#define VTSS_FEATURE_DELAY_REQ_AUTO_RESP         /**< Delay_Req/Resp processing supported in hardware */
#define VTSS_FEATURE_SYNC_ANN_AUTO_TRANSMIT      /**< Sync and Announce packet auto generation in hardware */
#define VTSS_FEATURE_SYNCE                       /**< SYNCE - L1 syncronization feature */
#define VTSS_FEATURE_NPI                         /**< NPI port */
#define VTSS_FEATURE_LED_POW_REDUC               /**< LED power reduction */
#define VTSS_FEATURE_INTERRUPTS                  /**< Port Interrupt support */
#define VTSS_FEATURE_IRQ_CONTROL                 /**< General IRQ support */
#define VTSS_FEATURE_VLAN_TRANSLATION            /**< VLAN Translation */
#define VTSS_FEATURE_SFLOW                       /**< sFlow feature    */
#define VTSS_FEATURE_MIRROR_CPU                  /**< CPU mirroring */
#define VTSS_FEATURE_SERDES_MACRO_SETTINGS       /**< Hooks for Serdes Macro configuration */
#if defined(VTSS_FEATURE_10G)
#define VTSS_FEATURE_10GBASE_KR                  /**< KR */
#endif /* VTSS_FEATURE_10G */
#define VTSS_FEATURE_AFI_SWC                     /**< AFI */
#define VTSS_AFI_V2                              /**< AFI API version 2 */
#if !defined(VTSS_OPT_PCIE_ACCESS) && !defined(VTSS_OPT_VRAP_ACCESS)
#define VTSS_OPT_PCIE_ACCESS                    /**< PCIe access from external CPU */
#endif
#define VTSS_FEATURE_XFLOW                      /**< Ingress and egress flows */
#define VTSS_FEATURE_XSTAT                      /**< Ingress and egress statistics */
#define VTSS_FEATURE_XDLB                       /**< DLB policers allocated dynamically */
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_ARCH_JAGUAR_2_CE)
#endif /* VTSS_ARCH_JAGUAR_2_CE */

#if defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_FEATURE_MCE_ACT_PRIO              /**< MCE action priority class */
#define VTSS_FEATURE_VOP                       /**< Y.1731/IEEE802.1ag OAM */
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_CHIP_SPARX_III_10_UM) || defined(VTSS_CHIP_SPARX_III_17_UM) || defined(VTSS_CHIP_SPARX_III_25_UM) ||\
    defined(VTSS_CHIP_SPARX_III_10) || defined(VTSS_CHIP_SPARX_III_18) || \
    defined(VTSS_CHIP_SPARX_III_24) || defined(VTSS_CHIP_SPARX_III_26) || \
    defined(VTSS_CHIP_SPARX_III_10_01)
#define VTSS_ARCH_SPARX_III                    /**< SparX-III SME switches */
#endif /* SPARX_III */

#if defined(VTSS_CHIP_CARACAL_1) || defined(VTSS_CHIP_CARACAL_2) || defined(VTSS_CHIP_CARACAL_LITE)
#define VTSS_ARCH_CARACAL                      /**< Caracal CE switches */
#endif /* CARACAL */

#if defined(VTSS_ARCH_CARACAL) || defined(VTSS_CHIP_SPARX_III_10_01)
#define VTSS_FEATURE_QOS_POLICER_DLB           /**< DLB policers */
#define VTSS_FEATURE_EVC_POLICERS              /**< EVC/ECE policers */
#endif

#if defined(VTSS_ARCH_SPARX_III) || defined(VTSS_ARCH_CARACAL)
#define VTSS_ARCH_LUTON26                      /**< Luton26 architecture */
#define VTSS_FEATURE_MISC                      /**< Miscellaneous */
#define VTSS_FEATURE_SERIAL_GPIO               /**< Serial GPIO control */
#define VTSS_FEATURE_PORT_CONTROL              /**< Port control */
#define VTSS_FEATURE_CLAUSE_37                 /**< IEEE 802.3 clause 37 auto-negotiation */
#define VTSS_FEATURE_EXC_COL_CONT              /**< Excessive collision continuation */
#define VTSS_FEATURE_PORT_CNT_BRIDGE           /**< Bridge counters */
#define VTSS_FEATURE_QOS                       /**< QoS */
#define VTSS_FEATURE_QCL                       /**< QoS: QoS Control Lists */
#define VTSS_FEATURE_QCL_V2                    /**< QoS: QoS Control Lists, V2 features */
#define VTSS_FEATURE_QCL_DMAC_DIP              /**< QoS: QoS Control Lists, match on either SMAC/SIP or DMAC/DIP */
#define VTSS_FEATURE_QCL_KEY_S_TAG             /**< QoS: QoS Control Lists has S tag support */
#define VTSS_FEATURE_QCL_PCP_DEI_ACTION        /**< QoS: QoS Control Lists has PCP and DEI action */
#define VTSS_FEATURE_QCL_POLICY_ACTION         /**< QoS: QoS Control Lists has policy action */
#define VTSS_FEATURE_QOS_POLICER_UC_SWITCH     /**< QoS: Unicast policer per switch */
#define VTSS_FEATURE_QOS_POLICER_MC_SWITCH     /**< QoS: Multicast policer per switch */
#define VTSS_FEATURE_QOS_POLICER_BC_SWITCH     /**< QoS: Broadcast policer per switch */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT      /**< QoS: Port Policer Extensions */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_FPS  /**< QoS: Port Policer has frame rate support */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_FC   /**< QoS: Port Policer has flow control support */
#define VTSS_FEATURE_QOS_QUEUE_POLICER         /**< QoS: Has Ingress Queue Policers */
#define VTSS_FEATURE_QOS_QUEUE_TX              /**< QoS: Has TX Queue support */
#define VTSS_FEATURE_QOS_SCHEDULER_V2          /**< QoS: 2. version of scheduler */
#define VTSS_FEATURE_QOS_TAG_REMARK_V2         /**< QoS: 2. version of tag priority remarking */
#define VTSS_FEATURE_QOS_CLASSIFICATION_V2     /**< QoS: 2. version of classification */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS  /**< QoS: Has Egress Queue Shapers */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB /**< QoS: Egress Queue Shapers has Excess Bandwidth support */
#define VTSS_FEATURE_QOS_DSCP_CLASS_DP_AWARE   /**< QoS: DSCP classification is DP aware */
#define VTSS_FEATURE_QOS_DSCP_REMARK           /**< QoS: Has DSCP remarking */
#define VTSS_FEATURE_QOS_DSCP_REMARK_V2        /**< QoS: 2. version of DSCP remarking */
#define VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE  /**< QoS: DSCP remarking is DP aware */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB /**< QoS: Egress Queue Shapers has CRedit Based shaper support */
#define VTSS_FEATURE_PACKET                    /**< CPU Rx/Tx frame configuration */
#define VTSS_FEATURE_PACKET_TX                 /**< CPU Tx frame */
#define VTSS_FEATURE_PACKET_RX                 /**< CPU Rx frame */
#define VTSS_FEATURE_PACKET_GROUPING           /**< Extraction and injection occurs through extraction and injection groups rather than queues. */
#define VTSS_FEATURE_PACKET_PORT_REG           /**< Packet registration per port */
//#define VTSS_FEATURE_PACKET_PORT_REG_DISCARD   /**< Packet discard registration per port */
//#define VTSS_FEATURE_PACKET_PORT_L2CP_REG      /**< Packet registration per port and L2CP */
#define VTSS_FEATURE_LAYER2                    /**< Layer 2 (switching) */
#define VTSS_FEATURE_PVLAN                     /**< Private VLANs */
#define VTSS_FEATURE_VLAN_PORT_V2              /**< VLAN port configuration, V2 features */
#define VTSS_FEATURE_VLAN_TX_TAG               /**< VLAN tagging per (VID, port) */
#define VTSS_FEATURE_IPV4_MC_SIP               /**< Source specific IPv4 multicast */
#define VTSS_FEATURE_IPV6_MC_SIP               /**< Source specific IPv6 multicast */
#define VTSS_FEATURE_MAC_AGE_AUTO              /**< Automatic MAC address ageing */
#define VTSS_FEATURE_MAC_CPU_QUEUE             /**< CPU queue per MAC address */
#define VTSS_FEATURE_EEE                       /**< Energy Efficient Ethernet */
#define VTSS_FEATURE_PORT_MUX                  /**< Port mux between serdes blocks and ports */
#define VTSS_FEATURE_FAN                       /**< Fan control */
#define VTSS_FEATURE_VCAP                      /**< VCAP */
#define VTSS_FEATURE_ACL                       /**< Access Control Lists */
#define VTSS_FEATURE_ACL_V2                    /**< Access Control Lists, V2 features */
#define VTSS_FEATURE_VCL                       /**< VLAN Control Lists */
#define VTSS_FEATURE_TIMESTAMP                 /**< Packet timestamp feature (for PTP) */
#define VTSS_FEATURE_TIMESTAMP_ONE_STEP        /**< ONESTEP timestamp hardware support */
#define VTSS_FEATURE_TIMESTAMP_LATENCY_COMP    /**< Ingress and egress latency compensation hardware support */
//#define VTSS_FEATURE_TIMESTAMP_P2P_DELAY_COMP  /**< Peer-to-peer path delay compensation hardware support */
//#define VTSS_FEATURE_TIMESTAMP_ASYMMETRY_COMP  /**< Path delay asymmetry compensation hardware support */
#define VTSS_MISSING_TX_TIMESTAMP_INTERRUPT    /**< Tx Timestamp interrupt is not supported in Luton26 */
#define VTSS_FEATURE_SYNCE                     /**< SYNCE - L1 syncronization feature */
#define VTSS_FEATURE_NPI                       /**< NPI port */
#define VTSS_FEATURE_IRQ_CONTROL               /**< General IRQ support */
#define VTSS_FEATURE_LED_POW_REDUC             /**< LED power reduction */
#define VTSS_FEATURE_INTERRUPTS                /**< Port Interrupt support */
#define VTSS_FEATURE_VLAN_TRANSLATION          /**< VLAN Translation */
#define VTSS_FEATURE_SFLOW                     /**< Statistical flow sampling */
#define VTSS_FEATURE_MIRROR_CPU                /**< CPU mirroring */
#define VTSS_FEATURE_SERDES_MACRO_SETTINGS     /**< Hooks for Serdes Macro configuration */
#define VTSS_FEATURE_PORT_PCS_CONF             /**< Special 1G PCS control */
#endif /* SPARX_III/CARACAL */

#if defined(VTSS_CHIP_7511) || defined(VTSS_CHIP_7512) || \
    defined(VTSS_CHIP_7513) || defined(VTSS_CHIP_7514)
#define VTSS_ARCH_OCELOT                       /**< Serval architecture */
#endif /* VTSS_CHIP_7511/7512/7513/7514 */

#if defined(VTSS_ARCH_OCELOT)
#define VTSS_FEATURE_PORT_MUX                  /**< Port mux between serdes blocks and ports */
#define VTSS_FEATURE_VOP                       /**< Y.1731/IEEE802.1ag OAM */
#define VTSS_FEATURE_MCE_ACT_PRIO              /**< MCE action priority class */
#define VTSS_FEATURE_AFI_SWC                   /**< Switch-core-based Automatic Frame Injection */
#define VTSS_AFI_V1                            /**< AFI API version 1 */
#define VTSS_FEATURE_WARM_START                /**< Warm start */
#define VTSS_FEATURE_MISC                      /**< Miscellaneous */
#define VTSS_FEATURE_PORT_CONTROL              /**< Port control */
#define VTSS_FEATURE_PORT_IFH                  /**< Port IFH control */
#define VTSS_FEATURE_CLAUSE_37                 /**< IEEE 802.3 clause 37 auto-negotiation */
#define VTSS_FEATURE_EXC_COL_CONT              /**< Excessive collision continuation */
#define VTSS_FEATURE_PORT_CNT_BRIDGE           /**< Bridge counters */
#define VTSS_FEATURE_PFC                       /**< 802.1Qbb Priority Flow Control */
#define VTSS_FEATURE_QOS                       /**< QoS */
#define VTSS_FEATURE_QCL                       /**< QoS: QoS Control Lists */
#define VTSS_FEATURE_QCL_V2                    /**< QoS: QoS Control Lists, V2 features */
#define VTSS_FEATURE_QCL_DMAC_DIP              /**< QoS: QoS Control Lists, match on either SMAC/SIP or DMAC/DIP */
#define VTSS_FEATURE_QCL_KEY_TYPE              /**< QoS: QoS Control Lists, different key types per port */
#define VTSS_FEATURE_QCL_KEY_S_TAG             /**< QoS: QoS Control Lists has S tag support */
#define VTSS_FEATURE_QCL_KEY_INNER_TAG         /**< QoS: QoS Control Lists has inner tag */
#define VTSS_FEATURE_QCL_KEY_DMAC              /**< QoS: QoS Control Lists has destination MAC address */
#define VTSS_FEATURE_QCL_KEY_DIP               /**< QoS: QoS Control Lists has destination IP address */
#define VTSS_FEATURE_QCL_PCP_DEI_ACTION        /**< QoS: QoS Control Lists has PCP and DEI action */
#define VTSS_FEATURE_QCL_POLICY_ACTION         /**< QoS: QoS Control Lists has policy action */
#define VTSS_FEATURE_QOS_POLICER_UC_SWITCH     /**< QoS: Unicast policer per switch */
#define VTSS_FEATURE_QOS_POLICER_MC_SWITCH     /**< QoS: Multicast policer per switch */
#define VTSS_FEATURE_QOS_POLICER_BC_SWITCH     /**< QoS: Broadcast policer per switch */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT      /**< QoS: Port Policer Extensions */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_FPS  /**< QoS: Port Policer has frame rate support */
#define VTSS_FEATURE_QOS_PORT_POLICER_EXT_FC   /**< QoS: Port Policer has flow control support */
#define VTSS_FEATURE_QOS_QUEUE_TX              /**< QoS: Has TX Queue support */
#define VTSS_FEATURE_QOS_QUEUE_POLICER         /**< QoS: Has Ingress Queue Policers */
#define VTSS_FEATURE_QOS_SCHEDULER_V2          /**< QoS: 2. version of scheduler */
#define VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT    /**< QoS: Scheduler supports variable number of DWRR inputs */
#define VTSS_FEATURE_QOS_TAG_REMARK_V2         /**< QoS: 2. version of tag priority remarking */
#define VTSS_FEATURE_QOS_CLASSIFICATION_V2     /**< QoS: 2. version of classification */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS  /**< QoS: Has Egress Queue Shapers */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB /**< QoS: Egress Queue Shapers has Excess Bandwidth support */
#define VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB    /**< QoS: Egress shapers has DLB support */
#define VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT     /**< Qos: Egress shapers have rate type support - line or date rate */
#define VTSS_FEATURE_QOS_DSCP_CLASS_DP_AWARE   /**< QoS: DSCP classification is DP aware */
#define VTSS_FEATURE_QOS_DSCP_REMARK           /**< QoS: Has DSCP remarking */
#define VTSS_FEATURE_QOS_DSCP_REMARK_V2        /**< QoS: 2. version of DSCP remarking */
#define VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE  /**< QoS: DSCP remarking is DP aware */
#define VTSS_FEATURE_QOS_WRED_V2               /**< QoS: WRED global - per queue (0..7), per dpl (0..1) */
#define VTSS_FEATURE_QOS_POLICER_DLB           /**< DLB policers */
#define VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER      /**< QoS: Has CPU queue shaper */
#define VTSS_FEATURE_QOS_CPU_PORT_SHAPER       /**< QoS: Has CPU port shaper */
#define VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB /**< QoS: Egress Queue Shapers has CRedit Based shaper support */
#define VTSS_FEATURE_PACKET                    /**< CPU Rx/Tx frame configuration */
#define VTSS_FEATURE_PACKET_TX                 /**< CPU Tx frame */
#define VTSS_FEATURE_PACKET_RX                 /**< CPU Rx frame */
#define VTSS_FEATURE_PACKET_GROUPING           /**< Extraction and injection occurs through extraction and injection groups rather than queues. */
#define VTSS_FEATURE_PACKET_PORT_REG           /**< Packet registration per port */
#define VTSS_FEATURE_PACKET_PORT_REG_DISCARD   /**< Packet discard registration per port */
//#define VTSS_FEATURE_PACKET_PORT_L2CP_REG        /**< Packet registration per port and L2CP */
#define VTSS_FEATURE_LAYER2                    /**< Layer 2 (switching) */
#define VTSS_FEATURE_PVLAN                     /**< Private VLANs */
#define VTSS_FEATURE_VLAN_PORT_V2              /**< VLAN port configuration, V2 features */
#define VTSS_FEATURE_VLAN_TX_TAG               /**< VLAN tagging per (VID, port) */
#define VTSS_FEATURE_VCL_KEY_DMAC              /**< VCL entry has destination MAC address */
#define VTSS_FEATURE_VCL_KEY_DIP               /**< VCL entry has destination IP address */
#define VTSS_FEATURE_IPV4_MC_SIP               /**< Source specific IPv4 multicast */
#define VTSS_FEATURE_IPV6_MC_SIP               /**< Source specific IPv6 multicast */
#define VTSS_FEATURE_MAC_AGE_AUTO              /**< Automatic MAC address ageing */
#define VTSS_FEATURE_MAC_CPU_QUEUE             /**< CPU queue per MAC address */
#define VTSS_FEATURE_EEE                       /**< Energy Efficient Ethernet */
#define VTSS_FEATURE_VCAP                      /**< VCAP */
#define VTSS_FEATURE_ACL                       /**< Access Control Lists */
#define VTSS_FEATURE_ACL_V2                    /**< Access Control Lists, V2 features */
#define VTSS_FEATURE_ACL_EXT_DIP               /**< ACL extended IPv6 rule with DIP matching */
#define VTSS_FEATURE_VCL                       /**< VLAN Control Lists */
#define VTSS_FEATURE_NPI                       /**< NPI port */
#define VTSS_FEATURE_LED_POW_REDUC             /**< LED power reduction */
#define VTSS_FEATURE_VLAN_TRANSLATION          /**< VLAN Translation */
#define VTSS_FEATURE_SFLOW                     /**< sFlow feature    */
#define VTSS_FEATURE_MIRROR_CPU                /**< CPU mirroring */
#define VTSS_FEATURE_EVC_POLICERS              /**< EVC/ECE policers */
#define VTSS_FEATURE_IRQ_CONTROL               /**< General IRQ support */
#define VTSS_FEATURE_XFLOW                     /**< Ingress and egress flows */
#define VTSS_FEATURE_INTERRUPTS                /**< Port Interrupt support */
#define VTSS_FEATURE_SERDES_MACRO_SETTINGS     /**< Hooks for Serdes Macro configuration */
#define VTSS_FEATURE_SYNCE                     /**< SYNCE - L1 syncronization feature */
#define VTSS_FEATURE_SERIAL_GPIO               /**< Serial GPIO control */
#define VTSS_FEATURE_VLAN_SVL                  /**< Shared VLAN Learning */
#define VTSS_FEATURE_FAN                       /**< Fan control */
#define VTSS_FEATURE_PTP_RS422                 /**< Support for the RS422 serial/1PPS interface */
#define VTSS_FEATURE_TIMESTAMP                 /**< Packet timestamp feature (for PTP) */
#define VTSS_FEATURE_TIMESTAMP_ONE_STEP        /**< ONESTEP timestamp hardware support */
#define VTSS_FEATURE_TIMESTAMP_LATENCY_COMP    /**< Ingress and egress latency compensation hardwarce support */
#define VTSS_FEATURE_TIMESTAMP_ORG_TIME        /**< OriginTimestamp update hardware support */
#define VTSS_FEATURE_TIMESTAMP_P2P_DELAY_COMP  /**< Peer-to-peer path delay compensation hardware support */
#define VTSS_FEATURE_TIMESTAMP_ASYMMETRY_COMP  /**< Path delay asymmetry compensation hardware support */
#define VTSS_FEATURE_VOP_V1                    /**< Version 1 OAM implementation. Serval-1 platform */
#endif /* VTSS_ARCH_OCELOT */

/* Cu PHY API always included for switch/OTN targets */
#if defined(VTSS_FEATURE_PORT_CONTROL)
#define VTSS_CHIP_CU_PHY                       /**< Cobber PHY chip */
#endif /* VTSS_FEATURE_PORT_CONTROL */

/* 10G PHY API included if switch has 10G ports */
#if defined(VTSS_FEATURE_10G)
#define VTSS_CHIP_10G_PHY                      /**< 10Gb 848x Phy API  */
#endif

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#define VTSS_FEATURE_VOP_V2                    /**< Version 2 OAM implementation. Jaguar2 and forward */
#endif

/* ================================================================= *
 *  Options
 * ================================================================= */

#ifndef VTSS_OPT_TRACE
#define VTSS_OPT_TRACE 1 /**< Trace enabled by default */
#endif /* VTSS_OPT_TRACE */

/* VAUI equalization control, change value to 10 if PCB trace is more than 15 cm */
#if !defined(VTSS_OPT_VAUI_EQ_CTRL)
#define VTSS_OPT_VAUI_EQ_CTRL 6 /**< Default equalization control */
#endif /* VTSS_OPT_VAUI_EQ_CTRL */

#if !defined(VTSS_OPT_PORT_COUNT)
#define VTSS_OPT_PORT_COUNT 0 /**< Use all target ports by default */
#endif /* VTSS_OPT_PORT_COUNT */

#if !defined(VTSS_PHY_OPT_VERIPHY)
#define VTSS_PHY_OPT_VERIPHY 1 /**< VeriPHY enabled by default */
#endif /* VTSS_PHY_OPT_VERIPHY */

#if defined(VTSS_CHIP_CU_PHY)
#define VTSS_FEATURE_WARM_START                /**< Warm start */
#endif /* VTSS_CHIP_CU_PHY */

#if defined(VTSS_CHIP_10G_PHY)
#define VTSS_FEATURE_SYNCE_10G                 /**< SYNCE - L1 syncronization feature for 10G PHYs*/
#define VTSS_FEATURE_EDC_FW_LOAD               /**< 848x EDC firmware will get loaded at initilization */
#define VTSS_FEATURE_WIS                       /**< WAN interface sublayer functionality */
#define VTSS_FEATURE_WARM_START                /**< Warm start */
#define VTSS_ARCH_MALIBU                     /**< Used for Malibu-A PHY */
#define VTSS_ARCH_MALIBU_B                     /**< Used for Malibu-B PHY */
#define VTSS_ARCH_VENICE_C                     /**< Used for Venice-C PHY */
#endif /* VTSS_CHIP_10G_PHY */

// defining VTSS_10BASE_TE select 10BASE-Te settings. If not defined code will default to 10BASE-T .
// 10BASE-Te settings select a reduced transmit amplitude that should be right in the middle of the spec. range.
// The 10BASE-T settings will be right at the lower spec.-limit for 10BASE-T amplitude (higher than Te, but marginal to spec. the 2.2v spec.)
//#define VTSS_10BASE_TE

// defining VTSS_OPT_PHY_TIMESTAMP enables the timestamp feature in the phy's that support it, and also activates the
// TimeOfDay monitor that ensures that the PHY timestampers are in sync with the Switch Timestamper.
// The option must be defined by the user (build configuration) on the builds to boards that have a timestamp PHY mounted.
// For special timestamp PHY builds the VTSS_FEATURE_PHY_TIMESTAMP is defined in this file, i.e. the
// PHY timestamp will always be enabled on these builds.
#if !defined(VTSS_OPT_PHY_TIMESTAMP)
  #if defined(VTSS_FEATURE_PHY_TIMESTAMP)
    #define VTSS_OPT_PHY_TIMESTAMP 1 /**< Enable PHY timestamp feature */
  #endif
#endif

#if defined(VTSS_OPT_PHY_TIMESTAMP)
    #define VTSS_VIPER_B_FIFO_RESET                      /**< Viper B 1588 OOS fix */
    #define VTSS_VIPER_B_FIFO_RESET_API_CALL             /**< Viper B OOS fix taken care of within the PHY API */
#endif
// Some building script uses the feature define as an option. This is not the
// idea, but we want to have some level of backwards compatibility. If
// VTSS_OPT_PHY_MACSEC is defined, then it will control the availability for the
// MACsec feature regardless of the VTSS_FEATURE_MACSEC define.
#if defined(VTSS_OPT_PHY_MACSEC)
#  undef VTSS_FEATURE_MACSEC
#  if VTSS_OPT_PHY_MACSEC
#    define VTSS_FEATURE_MACSEC /**< Enable macsec feature */
#  endif
#elif defined(VTSS_FEATURE_MACSEC)
#  define VTSS_OPT_PHY_MACSEC 1 /**< Enable macsec feature */
#else
#  define VTSS_OPT_PHY_MACSEC 0 /**< Disable macsec feature */
#endif

#endif /* _VTSS_OPTIONS_H_ */
