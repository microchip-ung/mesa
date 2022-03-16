// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file vtss_packet_api.h
 * \brief Packet API
 * \details This header file describes CPU Rx/Tx packet functions.
 */

#ifndef _VTSS_PACKET_API_H_
#define _VTSS_PACKET_API_H_

#include <vtss_api.h>   /* For vtss_sflow_type_t */

#if defined(VTSS_FEATURE_PACKET)
#ifdef __cplusplus
extern "C" {
#endif

/* - Rx frame registration ----------------------------------------- */

/** \brief NPI configuration */
typedef struct {
    BOOL           enable;      /**< Enable NPI port */
    vtss_port_no_t port_no;     /**< Port to use as NPI - if configurable */
} vtss_npi_conf_t;

/**
 * \brief Get NPI configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [OUT] NPI port configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_npi_conf_get(const vtss_inst_t inst, vtss_npi_conf_t   *const conf);

/**
 * \brief Set NPI configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  NPI port configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_npi_conf_set(const vtss_inst_t     inst,
                          const vtss_npi_conf_t *const conf);

/** \brief CPU Rx queue NPI configuration */
typedef struct {
    BOOL         enable; /**< Enable redirect of frames to NPI port */
} vtss_packet_rx_queue_npi_conf_t;

/** \brief CPU Rx queue buffer size in bytes */
typedef u32 vtss_packet_rx_queue_size_t;

/** \brief CPU Rx queue configuration */
typedef struct {
    vtss_packet_rx_queue_size_t     size; /**< Queue size */
    vtss_packet_rx_queue_npi_conf_t npi;  /**< NPI configuration */
#if defined(VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER)
     vtss_packet_rate_t             rate; /**< CPU queue packet rate */
#endif
} vtss_packet_rx_queue_conf_t;

/** \brief CPU Rx packet registration */
typedef struct
{
    BOOL bpdu_cpu_only;        /**< Redirect BPDUs (DMAC 01-80-C2-00-00-0X) */
    BOOL garp_cpu_only[16];    /**< Redirect GARPs (DMAC 01-80-C2-00-00-2X) */
    BOOL ipmc_ctrl_cpu_copy;   /**< Copy IP MC control (DIP 224.0.0.x) to CPU */
    BOOL igmp_cpu_only;        /**< Redirect IGMP frames to the CPU */
    BOOL mld_cpu_only;         /**< Redirect MLD frames to the CPU */
} vtss_packet_rx_reg_t;

/** \brief CPU Rx queue map */
typedef struct
{
    vtss_packet_rx_queue_t bpdu_queue;        /**< BPDUs */
    vtss_packet_rx_queue_t garp_queue;        /**< GARP frames */
    vtss_packet_rx_queue_t learn_queue;       /**< Learn frames */
    vtss_packet_rx_queue_t igmp_queue;        /**< IGMP/MLD frames */
    vtss_packet_rx_queue_t ipmc_ctrl_queue;   /**< IP multicast control frames */
    vtss_packet_rx_queue_t mac_vid_queue;     /**< MAC address table */
    vtss_packet_rx_queue_t sflow_queue;       /**< SFlow-marked frames */
    vtss_packet_rx_queue_t lrn_all_queue;     /**< Learn-all queue */
#if defined(VTSS_FEATURE_LAYER3)
    vtss_packet_rx_queue_t l3_uc_queue;       /**< L3 routing unicast queue */
    vtss_packet_rx_queue_t l3_other_queue;    /**< L3 routing other frames queue */
#endif /* VTSS_FEATURE_LAYER3 */
} vtss_packet_rx_queue_map_t;

/** \brief CPU Rx configuration */
typedef struct {
    vtss_packet_rx_queue_conf_t queue[VTSS_PACKET_RX_QUEUE_CNT];   /**< Queue configuration */
    vtss_packet_rx_reg_t        reg;                               /**< Packet registration */
    vtss_packet_rx_queue_map_t  map;                               /**< Queue mapping */
    vtss_packet_rx_grp_t        grp_map[VTSS_PACKET_RX_QUEUE_CNT]; /**< Queue to extraction group map */
#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
    vtss_bitrate_t              shaper_rate;                       /**< CPU port shaper bitrate in kbps */
#endif /* defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER) */
} vtss_packet_rx_conf_t;

/**
 * \brief Get Packet Rx configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  Packet Rx configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_rx_conf_get(const vtss_inst_t      inst,
                                vtss_packet_rx_conf_t  *const conf);

/**
 * \brief Set CPU Rx queue configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  CPU Rx queue configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_rx_conf_set(const vtss_inst_t            inst,
                                const vtss_packet_rx_conf_t  *const conf);

/**
 * \brief Get packet configuration for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Packet port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_rx_port_conf_get(const vtss_inst_t          inst,
                                     const vtss_port_no_t       port_no,
                                     vtss_packet_rx_port_conf_t *const conf);

/**
 * \brief Set packet configuration for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Packet port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_rx_port_conf_set(const vtss_inst_t                inst,
                                     const vtss_port_no_t             port_no,
                                     const vtss_packet_rx_port_conf_t *const conf);

/* - Tx frames ----------------------------------------------------- */

/**
 * \brief Information about frame
 **/
typedef struct
{
    vtss_port_no_t port_no;         /**< Ingress port (or VTSS_PORT_NO_NONE) */
    vtss_vid_t     vid;             /**< Egress VID (or VTSS_VID_NULL) */
    vtss_port_no_t port_tx;         /**< Egress port (or VTSS_PORT_NO_NONE) */
    BOOL           aggr_rx_disable; /**< Disable aggregation Rx filtering */
    BOOL           aggr_tx_disable; /**< Disable aggregation Tx filtering */
} vtss_packet_frame_info_t;

/**
 * \brief Initialize filter information to default values.
 *
 * \param info [OUT]  Frame information.
 **/
void vtss_packet_frame_info_init(vtss_packet_frame_info_t *const info);

/**
 * \brief CPU filter
 **/
typedef enum
{
    VTSS_PACKET_FILTER_DISCARD,   /**< Discard */
    VTSS_PACKET_FILTER_TAGGED,    /**< Tagged transmission */
    VTSS_PACKET_FILTER_UNTAGGED   /**< Untagged transmission */
} vtss_packet_filter_t;

/**
 * \brief Determine ingress/egress filter for frame.
 * The function may be used for ingress filtering, egress filtering or both.
 *
 * \param inst [IN]     Target instance reference.
 * \param info [IN]     Frame information.
 * \param filter [OUT]  Frame filter.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_frame_filter(const vtss_inst_t               inst,
                                 const vtss_packet_frame_info_t  *const info,
                                 vtss_packet_filter_t            *const filter);

/** \brief Port info structure. */
typedef struct {
    vtss_port_no_t port_no;         /**< Ingress port (or VTSS_PORT_NO_NONE) */
    vtss_vid_t     vid;             /**< Egress VID (or VTSS_VID_NULL) */
    BOOL           aggr_rx_disable; /**< Disable aggregation Rx filtering */
    BOOL           aggr_tx_disable; /**< Disable aggregation Tx filtering */
} vtss_packet_port_info_t;

/**
 * \brief Initialize filter information to default values.
 *
 * \param info [OUT]  Frame information.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_port_info_init(vtss_packet_port_info_t *const info);

/** \brief Packet information for each port */
typedef struct {
    vtss_packet_filter_t filter; /**< Packet filtering */
    vtss_etype_t         tpid;   /**< Tag Ethernet Type */
} vtss_packet_port_filter_t;

/**
 * \brief Determine ingress/egress filter for frame per port.
 * The function may be used for ingress filtering, egress filtering or both.
 *
 * \param inst [IN]     Target instance reference.
 * \param info [IN]     Frame information.
 * \param filter [OUT]  Frame filter.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_port_filter_get(const vtss_inst_t             inst,
                                    const vtss_packet_port_info_t *const info,
                                    vtss_packet_port_filter_t     filter[VTSS_PORT_ARRAY_SIZE]);

/** \brief VLAN filter information */
typedef struct {
    BOOL rx_forward;                /**< Ingress forwarding enabled */
    BOOL tx_forward;                /**< Egress forwarding enabled */
    u8   vlan_discard[VTSS_VIDS/8]; /**< One bit per VLAN ID indicates whether to discard */
} vtss_packet_vlan_filter_t;

/**
 * \brief Get VLAN ingress filter per port.
 *
 * \param inst [IN]     Target instance reference.
 * \param filter [OUT]  Frame filter.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_vlan_filter_get(const vtss_inst_t         inst,
                                    vtss_packet_vlan_filter_t filter[VTSS_PORT_ARRAY_SIZE]);

/** \brief VLAN packet status */
typedef struct {
    BOOL changed; /**< VLAN information changed since last call */
} vtss_packet_vlan_status_t;

/**
 * \brief Get VLAN status.
 *
 * \param inst [IN]     Target instance reference.
 * \param status [OUT]  Status.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_vlan_status_get(const vtss_inst_t         inst,
                                    vtss_packet_vlan_status_t *const status);

#define VTSS_PRIO_SUPER VTSS_PRIO_END /**< Super priority */

/**
 * OAM types to be used when encoding an injection header.
 */
typedef enum {
    VTSS_PACKET_OAM_TYPE_NONE = 0, /**< No-op                                                      */
    VTSS_PACKET_OAM_TYPE_CCM,      /**< Continuity Check Message                                   */
    VTSS_PACKET_OAM_TYPE_CCM_LM,   /**< Continuity Check Message with Loss Measurement information */
    VTSS_PACKET_OAM_TYPE_LBM,      /**< Loopback Message                                           */
    VTSS_PACKET_OAM_TYPE_LBR,      /**< Loopback Reply                                             */
    VTSS_PACKET_OAM_TYPE_LMM,      /**< Loss Measurement Message                                   */
    VTSS_PACKET_OAM_TYPE_LMR,      /**< Loss Measurement Reply                                     */
    VTSS_PACKET_OAM_TYPE_DMM,      /**< Delay Measurement Message                                  */
    VTSS_PACKET_OAM_TYPE_DMR,      /**< Delay Measurement Reply                                    */
    VTSS_PACKET_OAM_TYPE_1DM,      /**< A.k.a. SDM, One-Way Delay Measurement                      */
    VTSS_PACKET_OAM_TYPE_LTM,      /**< Link Trace message                                         */
    VTSS_PACKET_OAM_TYPE_LTR,      /**< Link Trace Reply                                           */
    VTSS_PACKET_OAM_TYPE_GENERIC,  /**< Generic OAM type                                           */
    VTSS_PACKET_OAM_TYPE_LCK,      /**< Locked Signal                                              */
    VTSS_PACKET_OAM_TYPE_MPLS_TP_1,/**< MPLS-TP (ITU G.8113.1)                                     */
    VTSS_PACKET_OAM_TYPE_MPLS_TP_2,/**< MPLS-TP (ITU G.8113.2)                                     */
    VTSS_PACKET_OAM_TYPE_MRP_TST,  /**< MRP TST frame (IEC62439-2-2016)                            */
    VTSS_PACKET_OAM_TYPE_MRP_ITST, /**< MRP ITST frame (IEC62439-2-2016)                           */
    VTSS_PACKET_OAM_TYPE_DLR_BCN,  /**< DLR Beacon frame (CIP Networks Library Volume 2)           */
    VTSS_PACKET_OAM_TYPE_DLR_ADV,  /**< MRP Advertise frame (CIP Networks Library Volume 2)        */
} vtss_packet_oam_type_t;

/**
 * PTP actions used when encoding an injection header.
 */
typedef enum {
    VTSS_PACKET_PTP_ACTION_NONE = 0,             /**< No-op                                                   */
    VTSS_PACKET_PTP_ACTION_ONE_STEP,             /**< One-step PTP                                            */
    VTSS_PACKET_PTP_ACTION_TWO_STEP,             /**< Two-step PTP                                            */
    VTSS_PACKET_PTP_ACTION_ONE_AND_TWO_STEP,     /**< Both one- and two-step PTP                              */
    VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP,     /**< Update time-of-day in PTP frame's originTimestamp field */
    VTSS_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ, /**< Update time-of-day in PTP frame's originTimestamp field and sequence number */
    VTSS_PACKET_PTP_ACTION_AFI_NONE,             /**< Update sequence number in AFI but no PTP updates        */
} vtss_packet_ptp_action_t;

/**
 * PDU encapsulation type
 */
typedef enum {
    VTSS_PACKET_ENCAP_TYPE_NONE,  // inj_encap is not used
    VTSS_PACKET_ENCAP_TYPE_ETHER, // PDU as indicated in ptp_action or oam_type ETHERNET encapsulated (no IP)
    VTSS_PACKET_ENCAP_TYPE_IP4,   // PDU as indicated in ptp_action IPV4 encapsulated
    VTSS_PACKET_ENCAP_TYPE_IP6,   // PDU as indicated in ptp_action IPV6 encapsulated
} vtss_packet_encap_type_t;

/**
 * PDU injection encapsulation
 */
typedef struct {
    vtss_packet_encap_type_t type;         // The type of encapsulation
    u32                      tag_count;    // Number of ETHERNET tags
}vtss_packet_inj_encap_t;


/**
 * Tag type the frame was received with.
 */
typedef enum {
    VTSS_TAG_TYPE_UNTAGGED = 0,    /**< Frame was received untagged or on an unaware port or with a tag that didn't match the port type. */
    VTSS_TAG_TYPE_C_TAGGED,        /**< Frame was received with a  C-tag                  */
    VTSS_TAG_TYPE_S_TAGGED,        /**< Frame was received with an S-tag                  */
    VTSS_TAG_TYPE_S_CUSTOM_TAGGED, /**< Frame was received with a custom S-tag            */
} vtss_tag_type_t;

#define VTSS_FA_PACKET_HDR_SIZE_BYTES      40 /**< Max header size. Worst case: INJ (36 bytes for IFH + 4 bytes for VLAN tag) */
#define VTSS_JR2_PACKET_HDR_SIZE_BYTES     32 /**< Max header size. Worst case: INJ (28 bytes for IFH + 4 bytes for VLAN tag) */
#define VTSS_SVL_PACKET_HDR_SIZE_BYTES     20 /**< Max header size. Worst case: INJ (16 bytes for IFH + 4 bytes for VLAN tag) */
#define VTSS_L26_PACKET_HDR_SIZE_BYTES     16 /**< Max header size. Worst case: INJ (8 bytes for IFH + 4 for timestamp + 4 for VLAN tag) */
#define VTSS_LAN966X_PACKET_HDR_SIZE_BYTES 32 /**< Max header size. Worst case: INJ (28 bytes for IFH + 4 bytes for VLAN tag) */

// Find the largest required header size.
#if defined(VTSS_ARCH_SPARX5)
#define VTSS_PACKET_HDR_SIZE_BYTES VTSS_FA_PACKET_HDR_SIZE_BYTES /**< Maximum header size. This define is only useful if you only compile for one target. */
#elif defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_PACKET_HDR_SIZE_BYTES VTSS_JR2_PACKET_HDR_SIZE_BYTES /**< Maximum header size. This define is only useful if you only compile for one target. */
#elif defined(VTSS_ARCH_OCELOT)
#define VTSS_PACKET_HDR_SIZE_BYTES VTSS_SVL_PACKET_HDR_SIZE_BYTES /**< Maximum header size. This define is only useful if you only compile for one target. */
#elif defined(VTSS_ARCH_LUTON26)
#define VTSS_PACKET_HDR_SIZE_BYTES VTSS_L26_PACKET_HDR_SIZE_BYTES /**< Maximum header size. This define is only useful if you only compile for one target. */
#elif defined(VTSS_ARCH_LAN966X)
#define VTSS_PACKET_HDR_SIZE_BYTES VTSS_LAN966X_PACKET_HDR_SIZE_BYTES /**< Maximum header size. This define is only useful if you only compile for one target. */
#endif

#define VTSS_SVL_RX_IFH_SIZE 16 /**< Serval1 Rx IFH size is 16 bytes */
#define VTSS_L26_RX_IFH_SIZE  8 /**< Luton26 Rx IFH size is  8 bytes */
#define VTSS_JR2_RX_IFH_SIZE 28 /**< Jaguar2 Rx IFH size is 28 bytes */
#define VTSS_FA_RX_IFH_SIZE  36 /**< Fireant Rx IFH size is 36 bytes */

/**
 * \brief Input structure to vtss_packet_rx_hdr_decode().
 *
 * In order to be able to decode the side-band information coming with
 * a frame when extracting through an external CPU with extraction headers
 * enabled, a number of inputs are required.
 *
 * This structure provides this meta data.
 *
 * For future compatibility, memset() this structure to 0 prior
 * to filling it in.
 */
typedef struct {
    vtss_etype_t etype;
    u32 fcs;
    u32 length;
} vtss_packet_rx_meta_t;

/**
 * \brief Provides additional info on decoded extraction header.
 *
 * In some cases, a frame received by the CPU should be
 * dropped. This cannot always be detected by just looking
 * at the decoded extraction header.
 *
 * This enum provides the caller of vtss_packet_rx_hdr_decode()
 * with a means to determine whether to drop or forward the frame
 * further to the application. Whether to actually drop it is fully up
 * to the application.
 *
 * The individual enums may be combined into a mask.
 */
typedef enum {

    /**
     * No hints.
     */
    VTSS_PACKET_RX_HINTS_NONE = 0x00,

    /**
     * If a frame is received on a C-port with a "foreign" tag
     * (i.e. an S-tag or S-custom-tag), the frame should possibly
     * be dropped. This is indicated with this enum being member
     * of the hints flags.
     *
     * The same goes for frames received on S-ports or S-custom-ports
     * with "foreign" tags.
     *
     * <pre>
     * Can be set by:
     * -------------------
     *   Luton26: Y
     *   Serval:  Y
     *   Jaguar2: Y
     *   Serval2: Y
     *   ServalT: Y
     * </pre>
     */
    VTSS_PACKET_RX_HINTS_VLAN_TAG_MISMATCH = 0x01,

    /**
     * If a tagged frame is received on a port that only should
     * accept untagged frames or if an untagged frame is received
     * on a port that should only accept tagged frames, then this
     * will be set. In general, the application should not
     * drop such frames, because e.g. BPDUs are normally untagged.
     *
     * <pre>
     * Can be set by:
     * -------------------
     *   Luton26: Y
     *   Serval:  Y
     *   Jaguar2: Y
     *   Serval2: Y
     *   ServalT: Y
     * </pre>
     */
    VTSS_PACKET_RX_HINTS_VLAN_FRAME_MISMATCH = 0x02,

    /**
     * If a frame gets classified to a VLAN ID on a port that is not member of
     * that VID, the hints flags include this enum.
     *
     * <pre>
     * Can be set by:
     * -------------------
     *   Luton26: Y
     *   Serval:  Y
     *   Jaguar2: Y
     *   Serval2: Y
     *   ServalT: Y
     * </pre>
     */
    VTSS_PACKET_RX_HINTS_VID_MISMATCH = 0x04,
} vtss_packet_rx_hints_t;

/**
 * \brief Decoded extraction header properties.
 *
 * This structure gets populated with a call to vtss_packet_rx_hdr_decode().
 *
 * Many decoded parameters have two fields in the structure:
 * One indicating the value of the parameter (e.g. #tstamp_id),
 * and another indicating if the parameter is actually decoded or not
 * (e.g. #tstamp_id_decoded).
 *
 * The reason for having an XXX_decoded boolean for every parameter is that
 * the information held in the extraction header is very different on the
 * various Vitesse chips, and even on the same chip type, the information
 * may be overloaded, depending on the incoming frame type.
 *
 * Most parameters don't have a decoded field, and in that case, they are
 * always decoded.
 */
typedef struct {
    u32 hints;
    u32 length;
    vtss_port_no_t port_no;
    vtss_tag_type_t tag_type;
    vtss_vlan_tag_t tag;
    vtss_vlan_tag_t stripped_tag;
    u32 xtr_qu_mask;
    vtss_prio_t cos;
    vtss_cosid_t cosid;
    vtss_dp_level_t dp;
    BOOL acl_hit;
    u32 tstamp_id;
    BOOL tstamp_id_decoded;
    u64 hw_tstamp;
    BOOL hw_tstamp_decoded;
    vtss_sflow_type_t sflow_type;
    vtss_port_no_t sflow_port_no;
    vtss_iflow_id_t iflow_id;
} vtss_packet_rx_info_t;

#if defined(VTSS_FEATURE_PACKET_PIPELINE_PT)
/**
 * \brief Chip pipeline injection point.
 * Specifies where a frame is injected into the chip.
 */
typedef enum {
    VTSS_PACKET_PIPELINE_PT_NONE         =  0, /**< None                               */
    VTSS_PACKET_PIPELINE_PT_ANA_PORT_VOE =  2, /**< Analyzer port VOE MEP (up)         */
    VTSS_PACKET_PIPELINE_PT_ANA_CL       =  3, /**< Basic classification               */
    VTSS_PACKET_PIPELINE_PT_ANA_CLM      =  4, /**< Analyzer CLM (up)                  */
    VTSS_PACKET_PIPELINE_PT_ANA_OU_VOI   =  6, /**< Analyzer outer VOI (MIP) (up)      */
    VTSS_PACKET_PIPELINE_PT_ANA_OU_SW    =  7, /**< Analyzer outer software MEP (up)   */
    VTSS_PACKET_PIPELINE_PT_ANA_OU_VOE   =  9, /**< Analyzer outer VOE MEP (up)        */
    VTSS_PACKET_PIPELINE_PT_ANA_IN_VOE   = 11, /**< Analyzer inner VOE MEP (up)        */
    VTSS_PACKET_PIPELINE_PT_ANA_IN_SW    = 13, /**< Analyzer inner software MEP (up)   */
    VTSS_PACKET_PIPELINE_PT_ANA_IN_VOI   = 14, /**< Analyzer inner VOI (MIP) (up)      */
    VTSS_PACKET_PIPELINE_PT_ANA_DONE     = 16, /**< Analyzer done                      */
    VTSS_PACKET_PIPELINE_PT_REW_IN_VOI   = 17, /**< Rewriter inner VOI (MIP) (down)    */
    VTSS_PACKET_PIPELINE_PT_REW_IN_SW    = 18, /**< Rewriter inner software MEP (down) */
    VTSS_PACKET_PIPELINE_PT_REW_IN_VOE   = 19, /**< Rewriter inner VOE MEP (down)      */
    VTSS_PACKET_PIPELINE_PT_REW_OU_VOE   = 20, /**< Rewriter outer VOE MEP (down)      */
    VTSS_PACKET_PIPELINE_PT_REW_OU_SW    = 21, /**< Rewriter outer software MEP (down) */
    VTSS_PACKET_PIPELINE_PT_REW_OU_VOI   = 22, /**< Rewriter outer VOI (MIP) (down)    */
    VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE = 24  /**< Rewriter port VOE MEP (down)       */
} vtss_packet_pipeline_pt_t;
#endif /* defined(VTSS_FEATURE_PACKET_PIPELINE_PT) */

#define VTSS_ISDX_CPU_TX 1023 /**< ISDX used for CPU transmissions */

/**
 * \brief Injection Properties.
 *
 * Structural properties used to compose a binary injection header useful
 * for injection into an injection-header-enabled port on the switch.
 *
 * This structure must be initialized with vtss_packet_tx_info_init()
 * prior to calling vtss_packet_tx_hdr_encode().
 */
typedef struct {
    BOOL switch_frm;
    u64 dst_port_mask;
    vtss_port_no_t dst_port;
    vtss_vlan_tag_t tag;
    vtss_prio_t cos;
    vtss_cosid_t cosid;
    vtss_dp_level_t dp;
    vtss_packet_ptp_action_t ptp_action;
    u8                       ptp_domain;
    u8 ptp_id;
    u64 ptp_timestamp;  // Time stamp in 16 bit fraction of nano seconds.
                        // Allocate timestamp id for a two step transmission must be in the nano second part (id << 16)
                        // Sequence counter index for a PTP transmission must be in the nano second part (id << 16)
    vtss_packet_oam_type_t oam_type;
#if defined VTSS_FEATURE_PACKET_INJ_ENCAP
    vtss_packet_inj_encap_t inj_encap;
#endif
    vtss_iflow_id_t iflow_id;
    vtss_port_no_t masquerade_port;
    u32 pdu_offset; // When encap_type is not MESA_PACKET_ENCAP_NONE then pdu_offset is the ETHERNET encapsulation size
                    // When encap_type is MESA_PACKET_ENCAP_NONE then pdu_offset is the start of the PDU
    u32                       sequence_idx;
#if defined(VTSS_FEATURE_AFI_SWC)
    vtss_afi_id_t afi_id;
#endif /* defined(VTSS_FEATURE_AFI_SWC) */
#if defined(VTSS_FEATURE_PACKET_PIPELINE_PT)
    vtss_packet_pipeline_pt_t pipeline_pt;
#endif /* defined(VTSS_FEATURE_PACKET_PIPELINE_PT) */
} vtss_packet_tx_info_t;

/**
 * \brief Decode binary extraction/Rx header.
 *
 * This function is mainly useful for external CPUs that wish
 * to decode the side-band information they get on NPI ports
 * with extraction headers enabled.
 *
 * \param inst [IN]  Target instance reference.
 * \param meta [IN]  Meta info on received frame.
 * \param hdr  [IN]  Packet header (IFH)
 * \param info [OUT] Decoded extraction header.
 *
 * \return Return code. On some architectures, it is possible to detect whether the function
 *         is invoked with a valid binary extraction header, in which case the function can
 *         return an error if it's not valid. On others it can't, in which case the return
 *         code can only be different from VTSS_RC_OK if called with invalid arguments like
 *         NULL-pointers.
 **/
vtss_rc vtss_packet_rx_hdr_decode(const vtss_inst_t                  inst,
                                  const vtss_packet_rx_meta_t *const meta,
                                  const u8                           hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                        vtss_packet_rx_info_t *const info);

/**
 * \brief Compose binary injection/Tx header.
 *
 * This function is mainly useful for external CPUs that inject
 * frames into the switch core with an injection frame header.
 *
 * In a few cases, it may also be useful for an application
 * running on the internal CPU: If the frame is to be looped
 * internally on a loop port, which is set-up to accept an
 * injection header, the injection header may be encoded with
 * this function.
 *
 * The info structure is the input to the encoding, which
 * results in a binary injection header and a length.
 *
 * On many architectures, the resulting binary length is constant,
 * but on some, it may vary with the contents of info properties.
 * To overcome this, call this function twice. The first time,
 * use a NULL pointer for bin_hdr. On return, the length
 * parameter will contain the number of bytes required in
 * bin_hdr. The second time, provide a non-NULL pointer to
 * bin_hdr.
 * On successful exit, bin_hdr_len will always be updated to contain
 * the actual number of bytes required to hold the IFH.
 * If you don't want to call this function twice, you may allocate
 * an array of VTSS_PACKET_HDR_SIZE_BYTES (or VTSS_arch_PACKET_HDR_SIZE_BYTES)
 * bytes, which will be long enough to accommodate all combinations
 * of content of info. But notice that there is no guarantee that
 * the actual length of the returned data matches VTSS_arch_PACKET_HDR_SIZE_BYTES.
 *
 * \param inst        [IN]    Target instance reference.
 * \param info        [IN]    Tx header properties.
 * \param bin_hdr     [OUT]   NULL to get bin_hdr_len filled with required length in bytes. Non-NULL to get it filled in with the binary injection header.
 * \param bin_hdr_len [INOUT] If bin_hdr is NULL, the [IN]-part is not used. Instead, it will be filled with resulting
 *                            length of binary injection header in bytes. If bin_hdr is non-NULL, bin_hdr_len specifies the
 *                            number of bytes that the function may write from the beginning of bin_hdr. On exit, it will contain
 *                            the actual number of bytes.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_tx_hdr_encode(const vtss_inst_t                  inst,
                                  const vtss_packet_tx_info_t *const info,
                                        u8                    *const bin_hdr,
                                        u32                   *const bin_hdr_len);

/* Maximum Rx/Tx IFH length */
#if defined(VTSS_ARCH_SPARX5)
#define VTSS_PACKET_TX_IFH_MAX     36  /**< Tx IFH byte length (Constant) */
#define VTSS_PACKET_RX_IFH_MAX     36  /**< Rx IFH byte length (Constant) */
#elif defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_PACKET_TX_IFH_MAX     28  /**< Tx IFH byte length (Constant) */
#define VTSS_PACKET_RX_IFH_MAX     28  /**< Rx IFH byte length (Constant) */
#elif defined(VTSS_ARCH_OCELOT)
#define VTSS_PACKET_TX_IFH_MAX     16  /**< Tx IFH byte length (Constant) */
#define VTSS_PACKET_RX_IFH_MAX     16  /**< Rx IFH byte length (Constant) */
#elif defined(VTSS_ARCH_LAN966X)
#define VTSS_PACKET_TX_IFH_MAX     28  /**< Tx IFH byte length (Constant) */
#define VTSS_PACKET_RX_IFH_MAX     28  /**< Rx IFH byte length (Constant) */
#elif defined(VTSS_ARCH_LUTON26)
#define VTSS_PACKET_TX_IFH_MAX     12  /**< Tx IFH byte length (Varies: 8/12 depending on PTP) */
#define VTSS_PACKET_RX_IFH_MAX     8   /**< Rx IFH byte length */
#endif

#define VTSS_PACKET_TX_IFH_STORAGE 36  /**< Tx IFH array length (Constant) */

vtss_rc vtss_packet_tx_frame(const vtss_inst_t           inst,
                             const vtss_packet_tx_info_t *const tx_info,
                             const u8                    *const frame,
                             const u32                   length);

/**
 * \brief Initialize a Tx info structure.
 *
 * Initialize the contents of a vtss_packet_tx_info_t
 * structure.
 *
 * \param inst [IN]  Target instance reference.
 * \param info [OUT] Pointer to structure that gets initialized to defaults.
 *
 * \return VTSS_RC_OK. VTSS_RC_ERROR only if info == NULL.
 */
vtss_rc vtss_packet_tx_info_init(const vtss_inst_t                  inst,
                                       vtss_packet_tx_info_t *const info);

/* - Rx frames ----------------------------------------------------- */

vtss_rc vtss_packet_rx_frame(const vtss_inst_t inst,
                             u8                *const data,
                             const u32         buflen,
                             vtss_packet_rx_info_t *const rx_info);

/**
 * \brief Convert PHY counter values to TS count
 *
 * \param inst          [IN]  Target instance reference.
 * \param phy_cnt       [IN]  PHY counter value
 * \param ts_cnt        [OUT] TS count. This is in 16 bit fraction of nano seconds.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_phy_cnt_to_ts_cnt(const vtss_inst_t  inst,
                                      const u32          phy_cnt,
                                      u64                *ts_cnt);

/**
 * \brief Convert a ns to ts counts
 *
 * \param inst          [IN]  Target instance reference.
 * \param ns            [IN]  Nanoseconds value
 * \param ts_cnt        [OUT] TS count. This is in 16 bit fraction of nano seconds.
 *
 * \return Return code.
 **/
vtss_rc vtss_packet_ns_to_ts_cnt(const vtss_inst_t  inst,
                                 const u32          ns,
                                 u64                *ts_cnt);

/** \brief Enumeration type representing the various types of PTP messages */
typedef enum  {
    VTSS_PACKET_PTP_MESSAGE_TYPE_GENERAL,       /* General PTP packet */
    VTSS_PACKET_PTP_MESSAGE_TYPE_SYNC,          /* Sync packet */
    VTSS_PACKET_PTP_MESSAGE_TYPE_P_DELAY_RESP   /* Peer Delay Response packet */
} vtss_packet_ptp_message_type_t;

/** \brief Enumeration type representing the various internal modes of a TC */
typedef enum  {
    VTSS_PACKET_INTERNAL_TC_MODE_30BIT,         /* 30 BIT mode, reserved field */
    VTSS_PACKET_INTERNAL_TC_MODE_32BIT,         /* 32 BIT mode, reserved field */
    VTSS_PACKET_INTERNAL_TC_MODE_44BIT,         /* 44 BIT mode, Sub and Add */
    VTSS_PACKET_INTERNAL_TC_MODE_48BIT,         /* 48 BIT mode, Sub and Add */
    VTSS_PACKET_INTERNAL_TC_MODE_MAX,           /* invalid mode */
} vtss_packet_internal_tc_mode_t;

/** \brief Struct holding values used for delay compensation */
/** This is in 16 bit fraction of nano seconds. */
typedef struct {
    u64  delay_cnt;      /**< Delay compensation (forward) used in case of Sync packets. */
    u64  asymmetry_cnt;  /**< Delay asymmetry compensation used in case of Peer Delay Response packets. */
} vtss_packet_ptp_delay_comp_t;

/** \brief Struct holding time stamping related parameters */
typedef struct {
    BOOL                            ts_feature_is_PTS;  /**< Configured timestamp feature is PHY timestamping */
    vtss_packet_internal_tc_mode_t  phy_ts_mode;        /**< The mode of PHY timestamping */
    BOOL                            backplane_port;     /**< Indicates if port is a backplane port. On some platforms backplane ports default to PHY timestamping */
    vtss_packet_ptp_delay_comp_t    delay_comp;         /**< Structure holding values used for delay compensation */
} vtss_packet_timestamp_props_t;

#define VTSS_PTP_FRAME_TS_LENGTH 4 /**< Length of the PHY inserted RX time in the frame */
/**
 * \brief Get PTP timestamp from packet or from timestamp FIFO or from rx_info
 *
 * \param inst                         [IN]  Target instance reference.
 * \param frm                          [IN]  Pointer to the PHY inserted RX time in the packet
 * \param rx_info                      [IN]  RX info structure
 * \param message_type                 [IN]  Type of the PTP message
 * \param ts_props                     [IN]  Time stamping related parameters
 * \param rxTime                       [OUT] Time stamp in 16 bit fraction of nano seconds.
 * \param timestamp_ok                 [OUT] Indication that time stamp was extracted OK.
 *
 * \return Return code.
 **/
vtss_rc vtss_ptp_get_timestamp(const vtss_inst_t                   inst,
                               const u8                            frm[VTSS_PTP_FRAME_TS_LENGTH],
                               const vtss_packet_rx_info_t *const  rx_info,
                               vtss_packet_ptp_message_type_t      message_type,
                               vtss_packet_timestamp_props_t       ts_props,
                               u64                                 *rxTime,
                               BOOL                                *timestamp_ok);

#ifdef __cplusplus
}
#endif
#endif /* VTSS_FEATURE_PACKET */
#endif /* _VTSS_PACKET_API_H_ */
