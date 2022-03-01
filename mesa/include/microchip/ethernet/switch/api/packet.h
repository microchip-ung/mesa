// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_PACKET_
#define _MICROCHIP_ETHERNET_SWITCH_API_PACKET_

#include <microchip/ethernet/switch/api/qos.h>
#include <microchip/ethernet/switch/api/vop.h>
#include <microchip/ethernet/switch/api/l2.h>
#include <microchip/ethernet/switch/api/misc.h>
#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/switch/api/afi.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/* - Transparent Clock internal types ------------------------------- */

// Enumeration type representing the various internal modes of a TC
typedef enum  {
    MESA_TOD_INTERNAL_TC_MODE_30BIT, // 30 BIT mode, reserved field
    MESA_TOD_INTERNAL_TC_MODE_32BIT, // 32 BIT mode, reserved field
    MESA_TOD_INTERNAL_TC_MODE_44BIT, // 44 BIT mode, Sub and Add
    MESA_TOD_INTERNAL_TC_MODE_48BIT, // 48 BIT mode, Sub and Add
    MESA_TOD_INTERNAL_TC_MODE_MAX,   // Invalid mode
} mesa_tod_internal_tc_mode_t;

/* - Rx frame registration ----------------------------------------- */

// NPI configuration
typedef struct {
    mesa_bool_t    enable;  // Enable NPI port
    mesa_port_no_t port_no; // Port to use as NPI - if configurable
} mesa_npi_conf_t;

// Get NPI configuration.
// conf [OUT] NPI port configuration.
mesa_rc mesa_npi_conf_get(const mesa_inst_t inst,
                          mesa_npi_conf_t   *const conf);

// Set NPI configuration.
// conf [IN]  NPI port configuration.
mesa_rc mesa_npi_conf_set(const mesa_inst_t     inst,
                          const mesa_npi_conf_t *const conf);

// CPU Rx queue NPI configuration
typedef struct {
    mesa_bool_t enable; // Enable redirect of frames to NPI port
} mesa_packet_rx_queue_npi_conf_t;

// CPU Rx queue buffer size in bytes
typedef uint32_t mesa_packet_rx_queue_size_t;

#define MESA_PACKET_RX_QUEUE_CNT 8 // Number of Rx packet queues

// CPU Rx queue configuration
typedef struct {
    mesa_packet_rx_queue_size_t     size;    // Queue size
    mesa_packet_rx_queue_npi_conf_t npi;     // NPI configuration
    mesa_packet_rx_grp_t            grp_map; // Queue to extraction group map
    mesa_packet_rate_t              rate CAP(QOS_CPU_QUEUE_SHAPER); // CPU queue packet rate
} mesa_packet_rx_queue_conf_t;

// CPU Rx packet registration
typedef struct
{
    mesa_bool_t bpdu_cpu_only;      // Redirect BPDUs (DMAC 01-80-C2-00-00-0X)
    mesa_bool_t garp_cpu_only[16];  // Redirect GARPs (DMAC 01-80-C2-00-00-2X)
    mesa_bool_t ipmc_ctrl_cpu_copy; // Copy IP MC control (DIP 224.0.0.x) to CPU
    mesa_bool_t igmp_cpu_only;      // Redirect IGMP frames to the CPU
    mesa_bool_t mld_cpu_only;       // Redirect MLD frames to the CPU
} mesa_packet_rx_reg_t;

// CPU Rx queue map
typedef struct
{
    mesa_packet_rx_queue_t bpdu_queue;        // BPDUs
    mesa_packet_rx_queue_t garp_queue;        // GARP frames
    mesa_packet_rx_queue_t learn_queue;       // Learn frames
    mesa_packet_rx_queue_t igmp_queue;        // IGMP/MLD frames
    mesa_packet_rx_queue_t ipmc_ctrl_queue;   // IP multicast control frames
    mesa_packet_rx_queue_t mac_vid_queue;     // MAC address table
    mesa_packet_rx_queue_t sflow_queue;       // SFlow-marked frames
    mesa_packet_rx_queue_t lrn_all_queue;     // Learn-all queue
    mesa_packet_rx_queue_t l3_uc_queue CAP(L3);    // L3 routing unicast queue
    mesa_packet_rx_queue_t l3_other_queue CAP(L3); // L3 routing other frames queue
} mesa_packet_rx_queue_map_t;

// CPU Rx configuration
typedef struct {
    mesa_packet_rx_queue_conf_t queue[MESA_PACKET_RX_QUEUE_CNT];      // Queue configuration
    mesa_packet_rx_reg_t        reg;                                  // Packet registration
    mesa_packet_rx_queue_map_t  map;                                  // Queue mapping
    mesa_bitrate_t              shaper_rate CAP(QOS_CPU_PORT_SHAPER); // CPU port shaper bitrate in kbps
} mesa_packet_rx_conf_t;

// Get Packet Rx configuration.
// conf [IN]  Packet Rx configuration.
mesa_rc mesa_packet_rx_conf_get(const mesa_inst_t      inst,
                                mesa_packet_rx_conf_t  *const conf);

// Set CPU Rx queue configuration.
// conf [IN]  CPU Rx queue configuration.
mesa_rc mesa_packet_rx_conf_set(const mesa_inst_t            inst,
                                const mesa_packet_rx_conf_t  *const conf);

// Get packet configuration for port.
// port_no [IN]  Port number.
// conf [OUT]    Packet port configuration structure.
mesa_rc mesa_packet_rx_port_conf_get(const mesa_inst_t          inst,
                                     const mesa_port_no_t       port_no,
                                     mesa_packet_rx_port_conf_t *const conf);

// Set packet configuration for port.
// port_no [IN]  Port number.
// conf [IN]     Packet port configuration structure.
mesa_rc mesa_packet_rx_port_conf_set(const mesa_inst_t                inst,
                                     const mesa_port_no_t             port_no,
                                     const mesa_packet_rx_port_conf_t *const conf);

/* - Tx frames ----------------------------------------------------- */

// Information about frame
typedef struct
{
    mesa_port_no_t port_no;         // Ingress port (or MESA_PORT_NO_NONE)
    mesa_vid_t     vid;             // Egress VID (or MESA_VID_NULL)
    mesa_port_no_t port_tx;         // Egress port (or MESA_PORT_NO_NONE)
    mesa_bool_t    aggr_rx_disable; // Disable aggregation Rx filtering
    mesa_bool_t    aggr_tx_disable; // Disable aggregation Tx filtering
} mesa_packet_frame_info_t;

// Initialize filter information to default values.
// info [OUT]  Frame information.
void mesa_packet_frame_info_init(mesa_packet_frame_info_t *const info);

// CPU filter
typedef enum
{
    MESA_PACKET_FILTER_DISCARD, // Discard
    MESA_PACKET_FILTER_TAGGED,  // Tagged transmission
    MESA_PACKET_FILTER_UNTAGGED // Untagged transmission
} mesa_packet_filter_t;

// Determine ingress/egress filter for frame.
// The function may be used for ingress filtering, egress filtering or both.
// info [IN]     Frame information.
// filter [OUT]  Frame filter.
mesa_rc mesa_packet_frame_filter(const mesa_inst_t               inst,
                                 const mesa_packet_frame_info_t  *const info,
                                 mesa_packet_filter_t            *const filter);

// Port info structure.
typedef struct {
    mesa_port_no_t port_no;         // Ingress port (or MESA_PORT_NO_NONE)
    mesa_vid_t     vid;             // Egress VID (or MESA_VID_NULL)
    mesa_bool_t    aggr_rx_disable; // Disable aggregation Rx filtering
    mesa_bool_t    aggr_tx_disable; // Disable aggregation Tx filtering
} mesa_packet_port_info_t;

// Initialize filter information to default values.
// info [OUT]  Frame information.
mesa_rc mesa_packet_port_info_init(mesa_packet_port_info_t *const info);

// Packet information for each port
typedef struct {
    mesa_packet_filter_t filter; // Packet filtering
    mesa_etype_t         tpid;   // Tag Ethernet Type
} mesa_packet_port_filter_t;

// Determine ingress/egress filter for frame per port.
// The function may be used for ingress filtering, egress filtering or both.
// info [IN]     Frame information.
// cnt [IN]      Number of ports.
// filter [OUT]  Frame filter.
mesa_rc mesa_packet_port_filter_get(const mesa_inst_t             inst,
                                    const mesa_packet_port_info_t *const info,
                                    const uint32_t                cnt,
                                    mesa_packet_port_filter_t     *const filter);

// VLAN filter information
typedef struct {
    mesa_bool_t    rx_forward;                // Ingress forwarding enabled
    mesa_bool_t    tx_forward;                // Egress forwarding enabled
    uint8_t        vlan_discard[MESA_VIDS/8]; // One bit per VLAN ID indicates whether to discard
} mesa_packet_vlan_filter_t;

// Get VLAN ingress filter per port.
// filter [OUT]  Frame filter.
mesa_rc mesa_packet_vlan_filter_get(const mesa_inst_t         inst,
                                    const uint32_t            cnt,
                                    mesa_packet_vlan_filter_t *const filter);

// VLAN packet status
typedef struct {
    mesa_bool_t changed; // VLAN information changed since last call
} mesa_packet_vlan_status_t;

// Get VLAN status.
// status [OUT]  Status.
mesa_rc mesa_packet_vlan_status_get(const mesa_inst_t         inst,
                                    mesa_packet_vlan_status_t *const status);

#define MESA_PRIO_SUPER MESA_PRIO_CNT // Super priority

// OAM types to be used when encoding an injection header.
typedef enum {
    MESA_PACKET_OAM_TYPE_NONE = 0,  // No-op
    MESA_PACKET_OAM_TYPE_CCM,       // Continuity Check Message
    MESA_PACKET_OAM_TYPE_CCM_LM,    // Continuity Check Message with Loss Measurement information
    MESA_PACKET_OAM_TYPE_LBM,       // Loop Back Message
    MESA_PACKET_OAM_TYPE_LBR,       // Loop Back Reply
    MESA_PACKET_OAM_TYPE_LMM,       // Loss Measurement Message
    MESA_PACKET_OAM_TYPE_LMR,       // Loss Measurement Reply
    MESA_PACKET_OAM_TYPE_DMM,       // Delay Measurement Message
    MESA_PACKET_OAM_TYPE_DMR,       // Delay Measurement Reply
    MESA_PACKET_OAM_TYPE_1DM,       // A.k.a. SDM, One-Way Delay Measurement
    MESA_PACKET_OAM_TYPE_LTM,       // Link Trace message
    MESA_PACKET_OAM_TYPE_LTR,       // Link Trace Reply
    MESA_PACKET_OAM_TYPE_GENERIC,   // Generic OAM type
    MESA_PACKET_OAM_TYPE_LCK,       // Locked Signal
    MESA_PACKET_OAM_TYPE_MPLS_TP_1, // MPLS-TP (ITU G.8113.1)
    MESA_PACKET_OAM_TYPE_MPLS_TP_2, // MPLS-TP (ITU G.8113.2)
    MESA_PACKET_OAM_TYPE_MRP_TST,   // MRP TST frame (IEC62439-2-2016)
    MESA_PACKET_OAM_TYPE_MRP_ITST,  // MRP ITST frame (IEC62439-2-2016)
    MESA_PACKET_OAM_TYPE_DLR_BCN,   // DLR Beacon frame (CIP Networks Library Volume 2)
    MESA_PACKET_OAM_TYPE_DLR_ADV,   // MRP Advertise frame (CIP Networks Library Volume 2)
} mesa_packet_oam_type_t;

// PTP actions used when encoding an injection header.
typedef enum {
    MESA_PACKET_PTP_ACTION_NONE = 0,             // No-op
    MESA_PACKET_PTP_ACTION_ONE_STEP,             // One-step PTP
    MESA_PACKET_PTP_ACTION_TWO_STEP,             // Two-step PTP
    MESA_PACKET_PTP_ACTION_ONE_AND_TWO_STEP,     // Both one- and two-step PTP
    MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP,     // Update time-of-day in PTP frame's originTimestamp field
    MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ, // Update time-of-day in PTP frame's originTimestamp field and sequence number
    MESA_PACKET_PTP_ACTION_AFI_NONE,             // Update sequence number in AFI but no PTP updates
} mesa_packet_ptp_action_t;

// PDU encapsulation type
typedef enum {
    MESA_PACKET_ENCAP_TYPE_NONE,  // inj_encap is not used
    MESA_PACKET_ENCAP_TYPE_ETHER, // PDU as indicated in ptp_action or oam_type ETHERNET encapsulated (no IP)
    MESA_PACKET_ENCAP_TYPE_IP4,   // PDU as indicated in ptp_action IPV4 encapsulated
    MESA_PACKET_ENCAP_TYPE_IP6,   // PDU as indicated in ptp_action IPV6 encapsulated
} mesa_packet_encap_type_t;

typedef struct {
    mesa_packet_encap_type_t type;
    uint32_t                 tag_count;    // Number of ETHERNET tags
}mesa_packet_inj_encap_t;

// Tag type the frame was received with.
typedef enum {
    MESA_TAG_TYPE_UNTAGGED = 0,    // Frame was received untagged or on an unaware port or with a tag that didn't match the port type.
    MESA_TAG_TYPE_C_TAGGED,        // Frame was received with a C-tag
    MESA_TAG_TYPE_S_TAGGED,        // Frame was received with an S-tag
    MESA_TAG_TYPE_S_CUSTOM_TAGGED, // Frame was received with a custom S-tag
} mesa_tag_type_t;

#define MESA_PACKET_HDR_SIZE_BYTES 40

// Input structure to mesa_packet_rx_hdr_decode().
//
// In order to be able to decode the side-band information coming with
// a frame when extracting through an external CPU with extraction headers
// enabled, a number of inputs are required.
//
// This structure provides this meta data.
//
// For future compatibility, memset() this structure to 0 prior to filling it in.
typedef struct {
    // The Ethernet type of the received frame, needed to decode mesa_packet_rx_info_t::tag_type correctly.
    mesa_etype_t etype;

    // Frame checksum, needed for Jaguar-2/Serval-T sFlow decoding.
    uint32_t fcs;

    // The length of the frame from DMAC to end-of-frame excluding FCS.
    uint32_t length;
} mesa_packet_rx_meta_t;

// Provides additional info on decoded extraction header.
//
// In some cases, a frame received by the CPU should be dropped. This cannot always be detected by just looking
// at the decoded extraction header.
//
// This enum provides the caller of mesa_packet_rx_hdr_decode() with a means to determine whether to drop or
// forward the frame further to the application. Whether to actually drop it is fully up to the application.
//
// The individual enums may be combined into a mask.
typedef enum {

    // No hints.
    MESA_PACKET_RX_HINTS_NONE = 0x00,

    // If a frame is received on a C-port with a "foreign" tag (i.e. an S-tag or S-custom-tag), the frame should
    // possibly be dropped. This is indicated with this enum being member of the hints flags.
    // The same goes for frames received on S-ports or S-custom-ports with "foreign" tags.
    MESA_PACKET_RX_HINTS_VLAN_TAG_MISMATCH = 0x01,

    // If a tagged frame is received on a port that only should accept untagged frames or if an untagged frame
    // is received on a port that should only accept tagged frames, then this will be set.
    // In general, the application should not drop such frames, because e.g. BPDUs are normally untagged.
    MESA_PACKET_RX_HINTS_VLAN_FRAME_MISMATCH = 0x02,

    // If a frame gets classified to a VLAN ID on a port that is not member of that VID,
    // the hints flags include this enum.
    MESA_PACKET_RX_HINTS_VID_MISMATCH = 0x04,
} mesa_packet_rx_hints_t;

// Decoded extraction header properties.
//
// This structure gets populated with a call to mesa_packet_rx_hdr_decode().
//
// Many decoded parameters have two fields in the structure:
// One indicating the value of the parameter (e.g. #tstamp_id), and another indicating if the parameter
// is actually decoded or not (e.g. #tstamp_id_decoded).
//
// The reason for having an XXX_decoded boolean for every parameter is that the information held in the
// extraction header is very different on the various devices, and even on the same chip type, the information
// may be overloaded, depending on the incoming frame type.
//
// Most parameters don't have a decoded field, and in that case, they are always decoded.
typedef struct {
    // Hints useful for ingress filtering on received frames.
    uint32_t hints;

    // The length of the frame from DMAC to end-of-frame excluding FCS.
    uint32_t length;

    // The logical source port on which the frame was received.
    // This may be MESA_PORT_NO_NONE, if the physical source port is not a part of the port map.
    mesa_port_no_t port_no;

    // The tag type (802.1Q TPID) the frame was received with, if any.
    mesa_tag_type_t tag_type;

    // VLAN classification information, tpid field not valid.
    mesa_vlan_tag_t tag;

    // VLAN stripped tag information.
    // This is not set by the API, but may be used by the application to strip a tag from a received frame,
    // before passing it on to other parts of the application.
    mesa_vlan_tag_t stripped_tag;

    // CPU extraction queue mask (one bit per CPU extraction queue).
    uint32_t xtr_qu_mask;

    // The frame's classified QoS class.
    mesa_prio_t cos;

    // The CoS ID (class of service, not to be confused with #cos).
    mesa_cosid_t cosid;

    // Drop Precedence.
    mesa_dp_level_t dp;

    // Set if frame has hit an ACL rule copying the frame to the CPU.
    mesa_bool_t acl_hit;

    // Two-step PTP timestamp identifier (6 bits) for Luton26 and Serval.
    //
    // On Luton26, this field identifies an Rx timestamp and potential Tx timestamps.
    // On Serval, this field identifies Tx timestamps. Rx timestamps are embedded in the extraction header.
    uint32_t tstamp_id;

    // TRUE when #tstamp_id contains valid information, FALSE otherwise.
    mesa_bool_t tstamp_id_decoded;

    // The frame's ingress timestamp (not used for Luton26)
    //
    // Serval: Two-step PTP frames have the 32-bit Rx timestamp saved in this field.
    uint64_t hw_tstamp;

    // TRUE when #hw_tstamp contains valid information, FALSE otherwise.
    mesa_bool_t hw_tstamp_decoded;

    // sFlow type. Indicates if this is copied to the CPU due to Rx or Tx SFlow, or if
    // it's not due to sFlow in the first place (MESA_SFLOW_TYPE_NONE).
    mesa_sflow_type_t sflow_type;

    // sFlow port, if #sflow_type != MESA_SFLOW_TYPE_NONE.
    // Indicates the logical sFlow Rx or Tx port number that caused this frame to be copied to the CPU.
    mesa_port_no_t sflow_port_no;

    // Ingress flow ID or MESA_IFLOW_ID_NONE (not used for Luton26)
    mesa_iflow_id_t iflow_id;
} mesa_packet_rx_info_t;

// Chip pipeline injection point.
typedef enum {
    MESA_PACKET_PIPELINE_PT_NONE         =  0, // None
    MESA_PACKET_PIPELINE_PT_ANA_PORT_VOE =  2, // Analyzer port VOE MEP (up)
    MESA_PACKET_PIPELINE_PT_ANA_CL       =  3, // Basic classification
    MESA_PACKET_PIPELINE_PT_ANA_CLM      =  4, // Analyzer CLM (up)
    MESA_PACKET_PIPELINE_PT_ANA_OU_VOI   =  6, // Analyzer outer VOI (MIP) (up)
    MESA_PACKET_PIPELINE_PT_ANA_OU_SW    =  7, // Analyzer outer software MEP (up)
    MESA_PACKET_PIPELINE_PT_ANA_OU_VOE   =  9, // Analyzer outer VOE MEP (up)
    MESA_PACKET_PIPELINE_PT_ANA_IN_VOE   = 11, // Analyzer inner VOE MEP (up)
    MESA_PACKET_PIPELINE_PT_ANA_IN_SW    = 13, // Analyzer inner software MEP (up)
    MESA_PACKET_PIPELINE_PT_ANA_IN_VOI   = 14, // Analyzer inner VOI (MIP) (up)
    MESA_PACKET_PIPELINE_PT_REW_IN_VOI   = 17, // Rewriter inner VOI (MIP) (down)
    MESA_PACKET_PIPELINE_PT_REW_IN_SW    = 18, // Rewriter inner software MEP (down)
    MESA_PACKET_PIPELINE_PT_REW_IN_VOE   = 19, // Rewriter inner VOE MEP (down)
    MESA_PACKET_PIPELINE_PT_REW_OU_VOE   = 20, // Rewriter outer VOE MEP (down)
    MESA_PACKET_PIPELINE_PT_REW_OU_SW    = 21, // Rewriter outer software MEP (down)
    MESA_PACKET_PIPELINE_PT_REW_OU_VOI   = 22, // Rewriter outer VOI (MIP) (down)
    MESA_PACKET_PIPELINE_PT_REW_PORT_VOE = 24  // Rewriter port VOE MEP (down)
} mesa_packet_pipeline_pt_t;

#define MESA_ISDX_CPU_TX 1023 // ISDX used for CPU transmissions

// Injection Properties.
//
// Structural properties used to compose a binary injection header useful
// for injection into an injection-header-enabled port on the switch.
//
// This structure must be initialized with mesa_packet_tx_info_init()
// prior to calling mesa_packet_tx_hdr_encode().
typedef struct {
    // Switch frame option.
    // If TRUE, the device will do switching lookups to determine the destination port set.
    // The frame must then include a VLAN tag for correct classification.
    // If FALSE, the destination port set is specified with #dst_port_mask.
    mesa_bool_t switch_frm;

    // Destination port set, used if #switch_frm is FALSE (not used for SparX-5).
    uint64_t dst_port_mask;

    // Destination port, used if #switch_frm is FALSE (only used for SparX-5).
    mesa_port_no_t dst_port;

    // VLAN tag information with architecture specific functionality.
    //
    // #switch_frm == TRUE:
    //   The tag fields may be used for classification depending on the architecture.
    //
    // #switch_frm == FALSE:
    //   By default, the frame is sent without any modification on each egress port.
    //   If tag.tpid is zero and tag.vid is non-zero, frame modifications on egress will be enabled.
    mesa_vlan_tag_t tag;

    // The QoS class that this frame will be transmitted on (egress queue number).
    // If #switch_frm is FALSE, MESA_PRIO_SUPER may be used for super-priority transmission.
    mesa_prio_t cos;

    // CoS ID (not used for Luton26 and Serval)
    mesa_cosid_t cosid;

    // Drop Precedence (not used for Luton26)
    mesa_dp_level_t dp;

    // PTP action, used if #switch_frm is FALSE.
    // MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP is not used for Luton26
    // MESA_PACKET_PTP_ACTION_AFI_NONE is not used for Luton26 and Serval
    // MESA_PACKET_PTP_ACTION_ONE_AND_TWO_STEP is only used for Luton26
    mesa_packet_ptp_action_t ptp_action;

    // PTP TOD domain (only used for SparX-5).
    uint8_t ptp_domain;

    // The PTP identifier, used when #ptp_action == MESA_PACKET_PTP_ACTION_TWO_STEP.
    // The CPU can only use from IDs 0 through 3.
    uint8_t ptp_id;

    // PTP timestamp indicating when the injection started, used when #ptp_action is != MESA_PACKET_PTP_ACTION_NONE.
    // The rewriter can then calculate a residence time based on this and the frame's transmission timestamp.
    // This is in 16 bit fraction of nano seconds.
    // On Jaguar2 and Fireant:
    // Allocated timestamp id (TX FIFO) for a two step transmission must be in the nano second part (id << 16)
    // Sequence counter index for a PTP  transmission must be in the nano second part (index << 16)
    uint64_t ptp_timestamp;

    // OAM type, used if #ptp_action is MESA_PACKET_PTP_ACTION_NONE (not used for Luton26).
    mesa_packet_oam_type_t oam_type;

    // The injected PDU encapsulation.
    mesa_packet_inj_encap_t inj_encap CAP(PACKET_INJ_ENCAP);

    // Ingress flow ID used for egress lookup, if not MESA_IFLOW_ID_NONE (not used for Luton26).
    mesa_iflow_id_t iflow_id;

    // Masquerade port, used if #switch_frm is TRUE (not used for Luton26).
    // When masquerading, the frame will be handled as if it was received on the masquerade port.
    // Set to MESA_PORT_NO_NONE to disable masquerading.
    mesa_port_no_t masquerade_port;

    // PDU offset in 8 bit word counts (not used for Luton26 and Serval)
    // Used in PTP or OAM injections.
    uint32_t pdu_offset;

    // On LAN966X:
    // PTP frames are able to get automatically updated sequence numbers.
    // There are a number of sequence number update counters. The 'sequence_idx' is a pointer to a counter.
    uint32_t sequence_idx;

    // Automatic Frame Injector ID (not used for Luton26).
    // Set to MESA_AFI_ID_NONE if you don't want a frame injected periodically.
    mesa_afi_id_t afi_id;

    // Chip pipeline injection point (not used for Luton26 and Serval)
    // Specifies where a frame is injected into the chip.
    mesa_packet_pipeline_pt_t pipeline_pt;
} mesa_packet_tx_info_t;

// Decode binary extraction/Rx header.
//
// This function is mainly useful for external CPUs that wish
// to decode the side-band information they get on NPI ports
// with extraction headers enabled.
//
// meta [IN]  Meta info on received frame.
// hdr  [IN]  Packet header (IFH)
// info [OUT] Decoded extraction header.
mesa_rc mesa_packet_rx_hdr_decode(const mesa_inst_t           inst,
                                  const mesa_packet_rx_meta_t *const meta,
                                  const uint8_t               hdr[MESA_PACKET_HDR_SIZE_BYTES],
                                        mesa_packet_rx_info_t *const info);

// Compose binary injection/Tx header.
//
// This function is mainly useful for external CPUs that inject
// frames into the switch core with an injection frame header.
//
// In a few cases, it may also be useful for an application
// running on the internal CPU: If the frame is to be looped
// internally on a loop port, which is set-up to accept an
// injection header, the injection header may be encoded with
// this function.
//
// The info structure is the input to the encoding, which
// results in a binary injection header and a length.
//
// On many architectures, the resulting binary length is constant,
// but on some, it may vary with the contents of info properties.
// To overcome this, call this function twice. The first time,
// use a NULL pointer for bin_hdr. On return, the length
// parameter will contain the number of bytes required in
// bin_hdr. The second time, provide a non-NULL pointer to
// bin_hdr.
// On successful exit, bin_hdr_len will always be updated to contain
// the actual number of bytes required to hold the IFH.
// If you don't want to call this function twice, you may allocate
// an array of MESA_PACKET_HDR_SIZE_BYTES (or MESA_arch_PACKET_HDR_SIZE_BYTES)
// bytes, which will be long enough to accommodate all combinations
// of content of info. But notice that there is no guarantee that
// the actual length of the returned data matches MESA_arch_PACKET_HDR_SIZE_BYTES.
//
// info            [IN]   Tx header properties.
// bin_hdr_max_len [IN]   If bin_hdr is non-NULL, the maximum length of the binary injection header in bytes
// bin_hdr         [OUT]  NULL to get bin_hdr_len filled with required length in bytes.
//                        Non-NULL to get it filled in with the binary injection header.
// bin_hdr_len     [OUT]  If bin_hdr is NULL, the required length of binary injection header in bytes.
//                        If bin_hdr is non-NULL, the actual number of bytes.
mesa_rc mesa_packet_tx_hdr_encode(const mesa_inst_t           inst,
                                  const mesa_packet_tx_info_t *const info,
                                  const uint32_t              bin_hdr_max_len,
                                  uint8_t                     *const bin_hdr,
                                  uint32_t                    *const bin_hdr_len);

// Send frame using Tx information
//
// tx_info [IN]  Frame Tx info
// frame [IN]    Frame buffer.
// length [IN]   Frame length excluding CRC.
mesa_rc mesa_packet_tx_frame(const mesa_inst_t           inst,
                             const mesa_packet_tx_info_t *const tx_info,
                             const uint8_t               *const frame,
                             const uint32_t              length);

// Initialize a Tx info structure.
//
// Initialize the contents of a mesa_packet_tx_info_t
// structure.
//
// info [OUT] Pointer to structure that gets initialized to defaults.
mesa_rc mesa_packet_tx_info_init(const mesa_inst_t                  inst,
                                       mesa_packet_tx_info_t *const info);

/* - Rx frames ----------------------------------------------------- */

// Get received frame
//
// data   [OUT]   Data buffer.
// buflen [IN]    Length of data buffer.
// rx_info [OUT]  Rx frame information
mesa_rc mesa_packet_rx_frame(const mesa_inst_t     inst,
                             uint8_t               *const data,
                             const uint32_t        buflen,
                             mesa_packet_rx_info_t *const rx_info);

// Convert PHY counter values to TS count
//
// phy_cnt       [IN]  PHY counter value
// ts_cnt        [OUT] TS count. This is in 16 bit fraction of nano seconds.
mesa_rc mesa_packet_phy_cnt_to_ts_cnt(const mesa_inst_t  inst,
                                      const uint32_t     phy_cnt,
                                      uint64_t           *ts_cnt);

// Convert a ns value to a TS (time stamper) count value
//
// ns            [IN]  Nanoseconds value
// ts_cnt        [OUT] TS count. This is in 16 bit fraction of nano seconds.
mesa_rc mesa_packet_ns_to_ts_cnt(const mesa_inst_t  inst,
                                 const uint32_t     ns,
                                 uint64_t           *ts_cnt);

// Enumeration type representing the various types of PTP messages
typedef enum  {
    MESA_PACKET_PTP_MESSAGE_TYPE_GENERAL,     // General PTP packet
    MESA_PACKET_PTP_MESSAGE_TYPE_SYNC,        // Sync packet
    MESA_PACKET_PTP_MESSAGE_TYPE_P_DELAY_RESP // Peer Delay Response packet
} mesa_packet_ptp_message_type_t;

// Enumeration type representing the various internal modes of a TC
typedef enum  {
    MESA_PACKET_INTERNAL_TC_MODE_30BIT, // 30 BIT mode, reserved field
    MESA_PACKET_INTERNAL_TC_MODE_32BIT, // 32 BIT mode, reserved field
    MESA_PACKET_INTERNAL_TC_MODE_44BIT, // 44 BIT mode, Sub and Add
    MESA_PACKET_INTERNAL_TC_MODE_48BIT, // 48 BIT mode, Sub and Add
    MESA_PACKET_INTERNAL_TC_MODE_MAX,   // invalid mode
} mesa_packet_internal_tc_mode_t;

// Struct holding values used for delay compensation
// This is in 16 bit fraction of nano seconds.
typedef struct {
    uint64_t  delay_cnt;      // Delay compensation (forward) used in case of Sync packets
    uint64_t  asymmetry_cnt;  // Delay asymmetry compensation used in case of Peer Delay Response packets
} mesa_packet_ptp_delay_comp_t;

// Struct holding time stamping related parameters
typedef struct {
    mesa_bool_t                     ts_feature_is_PTS; // Configured timestamp feature is PHY timestamping
    mesa_packet_internal_tc_mode_t  phy_ts_mode;       // The mode of PHY timestamping
    mesa_bool_t                     backplane_port;    // Indicates if port is a backplane port. On some platforms backplane ports default to PHY timestamping
    mesa_packet_ptp_delay_comp_t    delay_comp;        // Structure holding values used for delay compensation
} mesa_packet_timestamp_props_t;

#define MESA_PTP_FRAME_TS_LENGTH 4 // Length of the PHY inserted RX time in the frame

// Get PTP timestamp from packet or from timestamp FIFO or from rx_info
//
// frm                          [IN]  Pointer to the PHY inserted RX time in the packet
// rx_info                      [IN]  RX info structure
// message_type                 [IN]  Type of the PTP message
// ts_props                     [IN]  Time stamping related parameters
// rxTime                       [OUT] Time stamp in 16 bit fraction of nano seconds.
// timestamp_ok                 [OUT] Indication that time stamp was extracted OK.
mesa_rc mesa_ptp_get_timestamp(const mesa_inst_t                   inst,
                               const uint8_t                       frm[MESA_PTP_FRAME_TS_LENGTH],
                               const mesa_packet_rx_info_t *const  rx_info,
                               mesa_packet_ptp_message_type_t      message_type,
                               mesa_packet_timestamp_props_t       ts_props,  
                               uint64_t                            *rxTime,
                               mesa_bool_t                         *timestamp_ok);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_PACKET_
