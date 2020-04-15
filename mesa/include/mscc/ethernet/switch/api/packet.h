/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef _MSCC_ETHERNET_SWITCH_API_PACKET_
#define _MSCC_ETHERNET_SWITCH_API_PACKET_

#include <mscc/ethernet/switch/api/qos.h>
#include <mscc/ethernet/switch/api/vop.h>
#include <mscc/ethernet/switch/api/l2.h>
#include <mscc/ethernet/switch/api/misc.h>
#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/afi.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

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
    mesa_packet_rx_queue_t stack_queue;       // CPU-generated VStaX traffic
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

/* - Rx frames ----------------------------------------------------- */

// VStaX frame header used for reception
typedef struct
{
    mesa_bool_t        valid;   // TRUE if frame was VStaX tagged
    mesa_bool_t        sp;      // TRUE if received on super-prio
    mesa_vstax_upsid_t upsid;   // Ingress Unit Port Set ID
    mesa_port_no_t     port_no; // Ingress Unit port number (or zero)
    mesa_glag_no_t     glag_no; // Ingress GLAG (or zero)
    mesa_isdx_t        isdx;    // 12 bit ingress service index
} mesa_vstax_rx_header_t CAP(PACKET_VSTAX);

// Tag Control Information (according to IEEE 802.1Q)
typedef struct
{
    mesa_vid_t     vid;     // VLAN ID
    mesa_bool_t    cfi;     // Canonical Format Indicator
    mesa_tagprio_t tagprio; // Tag priority
} mesa_tci_t;

// System frame header describing received frame
typedef struct
{
    uint32_t               length;         // Frame length excluding CRC
    mesa_port_no_t         port_no;        // Ingress port number
    uint32_t               queue_mask;     // Bitmask of queues where received on
    mesa_bool_t            learn;          // TRUE if learn frame
    mesa_bool_t            arrived_tagged; // TRUE is frame was tagged
    mesa_tci_t             tag;            // VLAN tag from frame or port setup
    mesa_vstax_rx_header_t vstax CAP(PACKET_VSTAX); // VStaX header
} mesa_packet_rx_header_t;

// Copy a received frame from a CPU queue.
// queue_no [IN]  CPU queue number.
// header [OUT]   Frame header.
// frame [OUT]    Frame buffer.
// length [IN]    Length of frame buffer.
// Depending on chipset, queue_no may be don't care
// Actual queue(s) received on are returned in header->queue_mask as a bitmask.
// I.e. frames may be received on more than one queue at a time.
// A '1' indicates the frame was copied for the queue at the corresponding bit position).
mesa_rc mesa_packet_rx_frame_get(const mesa_inst_t            inst,
                                 const mesa_packet_rx_queue_t queue_no,
                                 mesa_packet_rx_header_t      *const header,
                                 uint8_t                      *const frame,
                                 const uint32_t               length);

// Copy a received frame from a CPU queue - with IFH.
//
// The extracted frame will be preceeded with an IFH and will have the
// frame FCS at the end. The length of the IFH and frame are returned
// separately, but are sequentially placed in the same output buffer.
// Use mesa_packet_rx_hdr_decode() to decode the IFH if necessary.
//
// data   [IN]    Data buffer.
// buflen [IN]    Length of data buffer.
// ifhlen [OUT]   Length of IFH at the start of the buffer.
// frmlen [OUT]   Length of received frame data - incl FCS.
mesa_rc mesa_packet_rx_frame_get_raw(const mesa_inst_t inst,
                                     uint8_t           *const data,
                                     const uint32_t    buflen,
                                     uint32_t          *const ifhlen,
                                     uint32_t          *const frmlen);

// Discard a received frame from a CPU queue.
// queue_no [IN]  CPU queue number.
mesa_rc mesa_packet_rx_frame_discard(const mesa_inst_t             inst,
                                     const mesa_packet_rx_queue_t  queue_no);

/* - Tx frames ----------------------------------------------------- */

// Send frame unmodified on port.
// port_no [IN]  Port number.
// frame [IN]    Frame buffer excluding room for CRC.
// length [IN]   Frame length excluding CRC.
mesa_rc mesa_packet_tx_frame_port(const mesa_inst_t    inst,
                                  const mesa_port_no_t port_no,
                                  const uint8_t        *const frame,
                                  const uint32_t       length);

// Send frame on port using egress rules.
// port_no [IN]  Port number.
// vid [IN]      VLAN ID inserted if the frame is tagged on egress.
// frame [IN]    Frame buffer excluding room for CRC.
// length [IN]   Frame length excluding CRC.
mesa_rc mesa_packet_tx_frame_port_vlan(const mesa_inst_t    inst,
                                       const mesa_port_no_t port_no,
                                       const mesa_vid_t     vid,
                                       const uint8_t        *const frame,
                                       const uint32_t       length);

// Send frame on VLAN using egress rules.
// vid [IN]     VLAN ID inserted if the frame is tagged on egress.
// frame [IN]   Frame buffer excluding room for CRC.
// length [IN]  Frame length excluding CRC.
mesa_rc mesa_packet_tx_frame_vlan(const mesa_inst_t inst,
                                  const mesa_vid_t  vid,
                                  const uint8_t     *const frame,
                                  const uint32_t    length);

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

// VLAN/VSI map
typedef struct {
    uint16_t vsi[MESA_VIDS]; // Virtual Switching Instance number
} mesa_packet_vlan_vsi_map_t;

// Get VLAN/VSI map.
// map  [OUT]  Map.
mesa_rc mesa_packet_vlan_vsi_map_get(const mesa_inst_t          inst,
                                     mesa_packet_vlan_vsi_map_t *const map);

#define MESA_PRIO_SUPER MESA_PRIO_CNT // Super priority

// VStaX frame forward mode
typedef enum
{
    MESA_VSTAX_FWD_MODE_LOOKUP     = 0, // Local lookup in all units
    MESA_VSTAX_FWD_MODE_UPSID_PORT = 2, // Physical port on UPSID
    MESA_VSTAX_FWD_MODE_CPU_UPSID  = 5, // CPU queue on UPSID
    MESA_VSTAX_FWD_MODE_CPU_ALL    = 6  // CPU queue on all UPSIDs
} mesa_vstax_fwd_mode_t CAP(PACKET_VSTAX);

// VStaX TTL value, 0-31
typedef uint32_t mesa_vstax_ttl_t CAP(PACKET_VSTAX);

#define MESA_VSTAX_TTL_PORT 0 // TTL value configured for port is used

// VStaX frame header used for transmission
typedef struct
{
    mesa_vstax_fwd_mode_t  fwd_mode;   // Frame forward mode
    mesa_vstax_ttl_t       ttl;        // TTL value or MESA_VSTAX_TTL_PORT
    mesa_prio_t            prio;       // Priority, MESA_PRIO_SUPER allowed
    mesa_vstax_upsid_t     upsid;      // Dest. unit port set: FWD_MODE_UPSID_PORT/CPU_UPSID
    mesa_tci_t             tci;        // VLAN tag information
    mesa_port_no_t         port_no;    // Dest. port: FWD_MODE_UPSID_PORT - Src. port : FWD_MODE_CPU_UPSID/ALL
    uint8_t                chip_port;  // If port_no is MESA_PORT_NO_NONE, then chip_port is used as is
    mesa_packet_rx_queue_t queue_no;   // CPU queue : FWD_MODE_CPU_UPSID/ALL
    mesa_bool_t            keep_ttl;   // Special TTL handling : FWD_MODE_CPU_ALL
    uint8_t                dp;         // 2 bits drop precedence level
} mesa_vstax_tx_header_t CAP(PACKET_VSTAX);

// Send frame on VStaX port.
// port_no [IN]  Port number.
// header [IN]   VStaX header structure.
// frame [IN]    Frame buffer excluding room for CRC.
// length [IN]   Frame length excluding CRC.
mesa_rc mesa_packet_tx_frame_vstax(const mesa_inst_t            inst,
                                   const mesa_port_no_t         port_no,
                                   const mesa_vstax_tx_header_t *const header,
                                   const uint8_t                *const frame,
                                   const uint32_t               length)
    CAP(PACKET_VSTAX);


#define MESA_VSTAX_HDR_SIZE 12 // VStaX header size

// Build 12 bytes VStaX frame header.
// port_no [IN]  Port number.
// header [IN]   VStaX header structure.
// frame [OUT]   Pointer where to write 12 bytes header in frame buffer.
mesa_rc mesa_packet_vstax_header2frame(const mesa_inst_t            inst,
                                       const mesa_port_no_t         port_no,
                                       const mesa_vstax_tx_header_t *const header,
                                       uint8_t                      *const frame)
    CAP(PACKET_VSTAX);


// Extract 12 bytes VStaX header.
// frame [IN]    Pointer where to extract 12 bytes header from frame buffer.
// header [OUT]  VStaX header structure.
mesa_rc mesa_packet_vstax_frame2header(const mesa_inst_t      inst,
                                       const uint8_t          *const frame,
                                       mesa_vstax_rx_header_t *const header)
    CAP(PACKET_VSTAX);

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
    // Obsoleted, value ignored.
    mesa_bool_t no_wait;

    // Chip number on which this frame was extracted.
    // It is not possible to deduct from the binary extraction header
    // which device the frame was extracted. In order to be able to
    // provide a logical source port in the decoded extraction properties,
    // a chip number is required for targets made up of multiple
    // physical chips.
    //
    // Required to be set?
    // -------------------
    // Luton26: N (assumed to be 0)
    // Serval:  N (assumed to be 0)
    // Jaguar2: N (assumed to be 0)
    // Serval2: N (assumed to be 0)
    // ServalT: N (assumed to be 0)
    mesa_chip_no_t chip_no;

    // Rx queue number from which this frame was really extracted.
    // This is only needed on particular architectures, where
    // this info is not part of the extraction header.
    //
    // Required to be set?
    // -------------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    mesa_packet_rx_queue_t xtr_qu;

    // The Ethernet type of the received frame.
    //
    // This is needed in order to be able to decode
    // mesa_packet_rx_info_t::tag_type correctly.
    //
    // Required to be set?
    // -------------------
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_etype_t etype;

    // Frame checksum.
    //
    // On some architectures, the frame's FCS/CRC may be used to hold
    // additional side-band information about the frame itself.
    //
    // To be able to decode this information, the caller must therefore
    // find the end of the frame and extract the 32-bit FCS and place it
    // here.
    //
    // Required to be set?
    // -------------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y (sflow-info)
    // Serval2: Y (sflow-info)
    // ServalT: Y (sflow-info)
    uint32_t fcs;

    // Software timestamp of packet.
    //
    // This may be used by the application to S/W-wise timestamp the packet.
    //
    // The field will be copied directly to mesa_packet_rx_info_t::sw_tstamp.
    //
    // Required to be set?
    // -------------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    mesa_os_timestamp_t sw_tstamp;

    // The length of the frame from DMAC to end-of-frame excluding FCS.
    //
    // The extraction header normally doesn't include the frame length, so
    // in order to provide a structure to the application that contains all
    // meta data about any given frame, the application may fill in this member,
    // which will be copied exactly as is into mesa_packet_rx_info_t::length.
    //
    // Required to be set?
    // -------------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    uint32_t length;
} mesa_packet_rx_meta_t;

// Provides additional info on decoded extraction header.
//
// In some cases, a frame received by the CPU should be
// dropped. This cannot always be detected by just looking
// at the decoded extraction header.
//
// This enum provides the caller of mesa_packet_rx_hdr_decode()
// with a means to determine whether to drop or forward the frame
// further to the application. Whether to actually drop it is fully up
// to the application.
//
// The individual enums may be combined into a mask.
typedef enum {

    // No hints.
    MESA_PACKET_RX_HINTS_NONE = 0x00,

    // If a frame is received on a C-port with a "foreign" tag
    // (i.e. an S-tag or S-custom-tag), the frame should possibly
    // be dropped. This is indicated with this enum being member
    // of the hints flags.
    //
    // The same goes for frames received on S-ports or S-custom-ports
    // with "foreign" tags.
    //
    // Can be set by:
    // -------------------
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    MESA_PACKET_RX_HINTS_VLAN_TAG_MISMATCH = 0x01,

    // If a tagged frame is received on a port that only should
    // accept untagged frames or if an untagged frame is received
    // on a port that should only accept tagged frames, then this
    // will be set. In general, the application should not
    // drop such frames, because e.g. BPDUs are normally untagged.
    //
    // Can be set by:
    // -------------------
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    MESA_PACKET_RX_HINTS_VLAN_FRAME_MISMATCH = 0x02,

    // If a frame gets classified to a VLAN ID on a port that is not member of
    // that VID, the hints flags include this enum.
    //
    // Can be set by:
    // -------------------
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    MESA_PACKET_RX_HINTS_VID_MISMATCH = 0x04,
} mesa_packet_rx_hints_t;

// Decoded extraction header properties.
//
// This structure gets populated with a call to mesa_packet_rx_hdr_decode().
//
// Many decoded parameters have two fields in the structure:
// One indicating the value of the parameter (e.g. #tstamp_id),
// and another indicating if the parameter is actually decoded or not
// (e.g. #tstamp_id_decoded).
//
// The reason for having an XXX_decoded boolean for every parameter is that
// the information held in the extraction header is very different on the
// various Vitesse chips, and even on the same chip type, the information
// may be overloaded, depending on the incoming frame type.
//
// Most parameters don't have a decoded field, and in that case, they are
// always decoded.
typedef struct {
    // The #hints member is useful for applications that wish to perform
    // some kind of ingress filtering on received frames.
    // Please refer to mesa_packet_rx_hints_t for a full description.
    // Each of the enumerations can be bitwise ORed into the #hints member.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint32_t hints;

    // The length of the frame from DMAC to end-of-frame excluding FCS.
    //
    // This is a copy of mesa_packet_rx_meta_t::length.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint32_t length;

    // The logical source port on which the frame was received.
    // In a few cases, this may be MESA_PORT_NO_NONE, if the physical
    // source port is not part of the port map.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_port_no_t port_no;

    // The Global Link Aggregation Group this frame was received on.
    // MESA_GLAG_NO_NONE if not received on a GLAG (also on non-supporting
    // architectures).
    // If received on a GLAG, #port_no will contain the first
    // member port in the GLAG.
    //
    // If received on a stack port, #glag_no will always be MESA_GLAG_NO_NONE,
    // but if the sender supports it in S/W, the stack header can be filled
    // with a glag_no before it is transmitted. To obtain this glag_no on
    // the receiving side, you can find it in vstax member's glag_no member.
    //
    // Validity:
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: N
    // ServalT: N
    mesa_glag_no_t glag_no;

    // The tag type (802.1Q TPID) the frame was received with, if any.
    //
    // Not all architectures support all four enumerations
    // of the tag type.
    //
    // On all architectures, the tag stays in the frame until received by S/W.
    //
    // In general, it works like this:
    //   If a frame is received on a VLAN unaware port,
    //   #tag_type will always be set to MESA_TAG_TYPE_UNTAGGED,
    //   whether it contains a tag or not. The classified VLAN (#tag's
    //   vid member) will always be the port VID.
    //
    //   If a frame is received on a C-port, then only frames
    //   received with a C-tag are marked as MESA_TAG_TYPE_C_TAGGED.
    //   S- and S-custom-tagged frames will be marked as MESA_TAG_TYPE_UNTAGGED.
    //   but notice that the frame *may* be classified according to
    //   that tag, anyway (architecture dependent).
    //   The #hints vlan_tag_mismatch member will be set to TRUE to indicate
    //   such a condition.
    //
    //   The same goes for frames received on an S-port or S-custom-port with
    //   a "foreign" VLAN tag. The frame may on some architectures be classified
    //   to the VID in the tag, but on others be classified according to the PVID.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_tag_type_t tag_type;

    // VLAN classification information.
    //
    // Contains the classified VLAN information, as opposed to #stripped_tag,
    // which contains the actual VLAN tag as was in the frame.
    //
    // Only the .pcp, .dei, and .vid members are used.
    // Notice that this is not necessarily the classification
    // coming from a VLAN tag; it may come from normal port
    // classification.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_vlan_tag_t tag;

    // VLAN stripped tag information.
    //
    // This is obsolete and no longer set by the API, but may be used by the
    // application whenever the application's packet driver select to strip a
    // tag from a received frame, before passing it on to other parts of the
    // application.
    //
    // Opposed to #tag, #stripped_tag contains the VLAN information
    // coming directly from the frame. The classified and frame VLAN
    // information may differ due to ACL/VCAP rules that cause the
    // frame to get classified based on other properties than a possible
    // VLAN tag embedded in the frame.
    //
    // Whenever the .tpid member is non-zero, the tag was stripped from
    // the frame.
    mesa_vlan_tag_t stripped_tag;

    // CPU extraction queue mask (one bit per CPU extraction queue).
    // Each bit implies the frame was subject to CPU forwarding to the
    // specific queue.
    // The actual queue the frame was received on is given by the
    // most significant bit set in the mask.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint32_t xtr_qu_mask;

    // The frame's classified QoS class.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_prio_t cos;

    // The CoS ID (class of service, not to be confused with #cos).
    //
    // Validity:
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_cosid_t cosid;

    // Drop Precedence.
    // The frame's classified drop precedence level.
    //
    // Validity:
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_dp_level_t dp;

    // The Virtual Switching Instance this was extracted on,
    // MESA_VSI_NONE if not extracted on a VSI.
    //
    // Validity:
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint16_t vsi;

    // Set if frame has hit a rule in IS2, which copies the frame to the
    // CPU (IS2 actions CPU_COPY_ENA or HIT_ME_ONCE). #acl_idx may contain
    // the IS2 entry number.
    // For Serval, the #acl_idx contains the combined ACL_ID action of
    // the rules hit in IS2.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_bool_t acl_hit;

    // If #acl_hit is set, this value is the entry number of the rule
    // hit in IS2. If both IS2 lookups hit a rule which copy the frame
    // to the CPU, then the second lookup's entry number is used.
    //
    // For Serval, this is the combined ACL_ID action coming out of the
    // two IS2 look-ups.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    uint32_t acl_idx;

    // Software timestamp of packet.
    //
    // This is a copy of the mesa_packet_rx_meta_t::sw_tstamp field.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_os_timestamp_t sw_tstamp;

    // Two-step PTP timestamp identifier (6 bits).
    //
    // On Luton26, this field identifies an Rx timestamp and potential
    // Tx timestamps (if the PTP frame was forwarded to other ports).
    // Notice that #tstamp_id_decoded will be TRUE for all frames that
    // have hit in IS2 rule. This means that the application must make
    // additional checks that this indeed is a PTP frame before relying
    // on #tstamp_id.
    //
    // On Serval, this field identifies Tx timestamps. Rx timestamps
    // are embedded in the extraction header.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    uint32_t tstamp_id;

    // TRUE when #tstamp_id contains valid information, FALSE otherwise.
    mesa_bool_t tstamp_id_decoded;

    // The frame's ingress timestamp.
    //   This is in 16 bit fraction of nano seconds.
    //
    // Serval:
    //   Two-step PTP frames have the 32-bit Rx timestamp saved in this field.
    //
    // Validity:
    // Luton26: N
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    // SparX-5: Y
    uint64_t hw_tstamp;

    // TRUE when #hw_tstamp contains valid information, FALSE otherwise.
    mesa_bool_t hw_tstamp_decoded;

    // sFlow type. Indicates if this is copied to the CPU due to Rx or Tx SFlow, or if
    // it's not due to sFlow in the first place (MESA_SFLOW_TYPE_NONE).
    //
    // Only MESA_SFLOW_TYPE_NONE, MESA_SFLOW_TYPE_RX, and MESA_SFLOW_TYPE_TX are possible.
    //
    // Jaguar2:
    //   Note: #sflow_type's RX and TX enumerations are only reliable if
    //   ANA_AC:PS_COMMON:PS_COMMON_CFG.SFLOW_SMPL_ID_IN_STAMP_ENA is set to 1.
    //   However, #sflow_type == MESA_SFLOW_TYPE_NONE is always reliable.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_sflow_type_t sflow_type;

    // sFlow port.
    // Indicates the logical sFlow Rx or Tx port number that caused this frame to be copied to the CPU.
    // Only valid if #sflow_type != MESA_SFLOW_TYPE_NONE.
    //
    // Jaguar2:
    //   Note: This is only reliable if ANA_AC:PS_COMMON:PS_COMMON_CFG.SFLOW_SMPL_ID_IN_STAMP_ENA is set to 1.
    //   That bit must be set if Tx sFlow are enabled. If only using Rx sFlows, that bit can be cleared, and
    //   you may use the #port_no member to figure out which port caused this frame.
    //
    // Validity:
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_port_no_t sflow_port_no;

    // Various un-decodable OAM info. Decoding of the OAM info
    // field from the extraction header requires accompanying
    // frame info, and is therefore saved as an opaque type,
    // leaving it to the application to decode it based on
    // description in the datasheet.
    //
    // Serval:
    //   This corresponds to the contents of the REW_VAL field
    //   in the extraction header. oam_info_decoded = TRUE when
    //   REW_OP[2:0] == 4. Only the 32 lsbits of #oam_info are used.
    //
    // Validity:
    // Luton26: N
    // Serval:  Y
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    uint64_t oam_info;

    // TRUE when #oam_info contains valid information, FALSE otherwise.
    mesa_bool_t oam_info_decoded;

    // The N-bit ISDX from IS1 classification, or MESA_ISDX_NONE.
    //
    // Validity:
    // Luton26: N
    // Serval:  Y
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    mesa_isdx_t isdx;

    // Ingress Flow Id.
    //
    // The N-bit ISDX from IS1/CLM classification that is resolved to related ingress Flow Id, or MESA_IFLOW_ID_NONE.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_iflow_id_t iflow_id;

    // The frame's decoded VStaX header.
    // mesa_vstax_rx_header_t::valid indicates whether the frame
    // was received with a VStaX header.
    //
    // Validity:
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: N
    // ServalT: N
    mesa_vstax_rx_header_t vstax CAP(PACKET_VSTAX);
} mesa_packet_rx_info_t;

// Transmit frames with VStaX header, and if so, how is it specified?
typedef enum {
    // Don't send frame with VStaX header.
    MESA_PACKET_TX_VSTAX_NONE = 0,

    // Send frame with VStaX header. The header is already encoded into binary format.
    MESA_PACKET_TX_VSTAX_BIN,

    // Send frame with VStaX header. The header is in symbolic format and needs to be encoded by API.
    MESA_PACKET_TX_VSTAX_SYM
} mesa_packet_tx_vstax_t;

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
    // If FALSE, the analyzer processing is skipped for this frame,
    // and the destination port set is specified with #dst_port_mask.
    // If TRUE, the frame will be passed through the analyzer to find the
    // destination port set. The analyzer looks up the DMAC in the
    // MAC table and forwards based on its findings. The frame may therefore
    // get flooded.
    //
    // Luton26 and Serval:
    //   If #switch_frm is TRUE, the frame must have inserted a VLAN tag into the
    //   frame prior to transmission, to get it classified to the correct VLAN.
    //   There is one exception to this, namely when masquerading (see #masquerade_port),
    //   where a VLAN tag may or may not be inserted. If not inserted, the masquerade
    //   port's PVID is used for classification. In no VLAN tag is inserted by the
    //   application, this structure's #tag member's tpid must be set to 0.
    //
    // If FALSE, the destination port set must be specified with #dst_port_mask.
    //
    // Validity:
    // ------------
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    // On Luton26 + Serval: If FALSE the rewriter still uses the tag information for rewriting actions.
    mesa_bool_t switch_frm;

    // This field provides the logical destination port set onto which to send
    // the frame and may thus be used to multicast the same frame on
    // multiple front ports in one go.
    // The field is only used if #switch_frm is FALSE.
    //
    // If the frame is going to be transmitted with a VStaX header (tx_vstax_hdr is != MESA_PACKET_TX_VSTAX_NONE)
    // the dst_port_mask must have exactly one bit set, representing the stack port (A or B) to
    // transmit the frame to.
    // Also, if the frame is subject to periodic transmission through the AFI, exactly one bit
    // must be set.
    //
    // Validity:  A F
    // ----------------
    // Luton26:   Y Y
    // Serval:    Y Y
    // Jaguar2:   Y Y
    // Serval2:   Y Y
    // ServalT:   Y Y
    // SparX-5:   N N
    uint64_t dst_port_mask;

    // This field provides the logical destination port onto which to send the frame.
    // The field is only used if #switch_frm is FALSE.
    //
    // Validity:  A F
    // ----------------
    // Luton26:   N N
    // Serval:    N N
    // Jaguar2:   N N
    // Serval2:   N N
    // ServalT:   N N
    // SparX-5:   Y Y
    mesa_port_no_t dst_port;

    // On some architectures, the frame length must be specified in the injection
    // header. The length - in bytes - is the size of the frame starting from the
    // DMAC up to, but not including, the FCS/CRC.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    uint32_t frm_len;

    // VLAN tag information.
    //
    // Use of this field is architecture specific, and depends on whether
    // #switch_frm is TRUE or FALSE.
    //
    // #switch_frm == TRUE:
    //   The frame will get classified according to tag.vid, tag.dei, and tag.pcp.
    //
    //   An application that directly calls mesa_packet_tx_hdr_encode() must insert
    //   a VLAN tag into the frame with these properties, and the
    //   mesa_packet_tx_hdr_encode() function will not use #tag for anything.
    //
    // #switch_frm == FALSE:
    //   On Serval, egress ES0 lookups occur even when the rewriter is disabled.
    //   The result of the lookup may be used in e.g. the VOE to count frames.
    //   In order to get the VOE to count in the correct buckets, the #tag's
    //   pcp member must be set correctly.
    //
    //   If #tag's tpid member is non-zero, the application software must insert
    //   a tag into the frame. In this case, the chip's rewriter will be
    //   disabled, so the frame will be sent as is. The inserted tag should use
    //   all members of #tag (i.e. tag.tpid, tag.vid, tag.pcp, and tag.dei).
    //
    //   If #tag's tpid member is zero, the application should not insert a tag.
    //
    //   If tpid is zero, rewriting of the frame can now be controlled with #tag's
    //   vid member: If vid is zero, the chip's rewriter will be disabled, so the
    //   frame will be sent as is. If vid is non-zero, the vid will be inserted
    //   into the injection header's classified VID field, and the chip's rewriter
    //   will be enabled, causing the frame to potentially be rewritten by the chip.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  Y (tag.pcp when #switch_frm == FALSE).
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    mesa_vlan_tag_t tag;

    // The aggregation code that this frame will use. The 4-bit number
    // maps directly to the corresponding field in the IFH, but is
    // only set if the frame is being switched (the #switch_frm member
    // is TRUE) and the destination port number is MESA_CPU_PM_NUMBER.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    uint8_t aggr_code;

    // The QoS class that this frame will be transmitted on (egress queue number).
    // This is a number in range [0; 8].
    //
    // If you set it to '8' (or MESA_PRIO_SUPER), the frame will be transmitted
    // with super-priority, i.e. with even higher priority than the highest
    // priority achievable for normal data traffic (if supported on the platform).
    // This is not a valid setting if #switch_frm == TRUE.
    //
    // Luton26 notes:
    //   A value of '8' (super priority) will be converted to a value of '7'.
    //
    // Validity:
    // ------------
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_prio_t cos;

    // The CoS ID (class of service, not to be confused with #cos).
    // This is a number in range [0; 7].
    //
    // Validity:  A
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_cosid_t cosid;

    // Sets classified DSCP. Mainly useful when masquerading and injecting into
    // MESA_PACKET_PIPELINE_PT_ANA_CLM.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_dscp_t dscp;

    // The Virtual Switching Instance to inject this frame on.
    // Set to MESA_VSI_NONE to not use this feature.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint16_t vsi;

    // If a frame is going to be transmitted with a VStaX header, set this
    // member to a value different from MESA_PACKET_TX_VSTAX_NONE.
    //
    // When transmitting with stack header, the application may choose to
    // either provide a binary or a non-binary stack header to this function.
    // The binary, selected with #tx_vstax_hdr == MESA_PACKET_TX_VSTAX_BIN,
    // is useful if the application uses the same stack header in all frames
    // it may send. Instead of encoding it every time, it may encode it once
    // (with mesa_packet_vstax_header2frame() and copy it to the bin member of
    // #vstax everytime it needs to send a frame with that stack header.
    //
    // On the other hand, if the stack header changes from time to time,
    // the application will probably wish to use MESA_PACKET_TX_VSTAX_SYM,
    // which causes the API to encode the stack header for it.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: N
    // ServalT: N
    mesa_packet_tx_vstax_t tx_vstax_hdr;

    // Contains the VStaX header in either binary or symbolic form.
    union {
        // This is the binary version of the VStaX header to insert when the
        // frame gets transmitted on a stack port.
        // It is only used if #tx_vstax_hdr is MESA_PACKET_TX_VSTAX_BIN.
        // It may be composed with mesa_packet_vstax_header2frame()
        //
        // Validity:
        // ------------
        // Luton26: N
        // Serval:  N
        // Jaguar2: Y
        // Serval2: N
        // ServalT: N
        uint8_t bin[MESA_VSTAX_HDR_SIZE];

        // This is the symbolic version of the VStaX header to insert when the
        // frame gets transmitted on a stack port.
        // The binary version will be encoded mesa_packet_tx_hdr_encode().
        // It is only used if #tx_vstax_hdr is MESA_PACKET_TX_VSTAX_SYM.
        //
        // Validity:
        // ------------
        // Luton26: N
        // Serval:  N
        // Jaguar2: Y
        // Serval2: N
        // ServalT: N
        mesa_vstax_tx_header_t sym;
    } vstax; // Contains the VStaX header in either binary or symbolic form.

    // The frame's Precision Time Protocol action.
    // See #mesa_packet_ptp_action_t for the enumeration.
    // Ignored when #switch_frm is TRUE.
    //
    // When != MESA_PACKET_PTP_ACTION_NONE, the #ptp_timestamp and #ptp_id fields must be filled in.
    //
    // Validity:
    // ------------
    // Luton26: Y - except for enumeration MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP and MESA_PACKET_PTP_ACTION_AFI_NONE.
    // Serval:  Y - except for enumeration MESA_PACKET_PTP_ACTION_ONE_AND_TWO_STEP and MESA_PACKET_PTP_ACTION_AFI_NONE.
    // Jaguar2: Y - except for enumeration MESA_PACKET_PTP_ACTION_ONE_AND_TWO_STEP.
    // Serval2: Y - except for enumeration MESA_PACKET_PTP_ACTION_ONE_AND_TWO_STEP.
    // ServalT: Y - except for enumeration MESA_PACKET_PTP_ACTION_ONE_AND_TWO_STEP.
    mesa_packet_ptp_action_t ptp_action;

    // The frame's Precision Time Protocol TOD domain.
    // Ignored when #switch_frm is TRUE.
    //
    // Validity:
    // ------------
    // SparX-5: Y
    uint8_t                  ptp_domain;

    // The PTP identifier used for two-step PTP actions.
    // The CPU can only use from IDs 0 through 3.
    // Ignored when #switch_frm is TRUE.
    //
    // Used when #ptp_action == MESA_PACKET_PTP_ACTION_TWO_STEP.
    //
    // Validity:
    // ------------
    // Luton26: Y
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint8_t ptp_id;

    // Holds the PTP timestamp indicating when the injection started.
    // The rewriter can then calculate a residence time based on this and the
    // frame's transmission timestamp.
    // Ignored when #switch_frm is TRUE.
    // This is in 16 bit fraction of nano seconds.
    //
    // Used when #ptp_action is != MESA_PACKET_PTP_ACTION_NONE.
    //
    // Validity:  A F
    // --------------
    // Luton26: Y Y
    // Serval:  Y Y
    // Jaguar2: Y Y
    // Serval2: Y Y
    // ServalT: Y Y
    // SparX-5: Y Y
    uint64_t ptp_timestamp;

    // Latch timestamp into a switch core register when the frame
    // is transmitted. This register can then be read-out by S/W
    // to obtain the actual transmission time for that frame.
    //
    // Encoding:
    //   0: Don't latch timestamp.
    //   1: Latch timestamp into register 0.
    //   2: Latch timestamp into register 1.
    //   3: Latch timestamp into register 2.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    uint32_t latch_timestamp;

    // OAM type.
    //
    // Only used if #ptp_action is MESA_PACKET_PTP_ACTION_NONE.
    //
    // See mesa_packet_oam_type_t for a description.
    // Ignored when #switch_frm is TRUE.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_packet_oam_type_t oam_type;

    // OAM MPLS TTL.
    //
    // Only used if #oam_type is MESA_PACKET_OAM_TYPE_MPLS_TP_1 or
    // MESA_PACKET_OAM_TYPE_MPLS_TP_2.
    //
    // TTL value to use for innermost label for MPLS OAM.
    // Ignored when #switch_frm is TRUE.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint8_t oam_mpls_ttl;

    // OAM MPLS S-bit.
    //
    // Only used if #oam_type is MESA_PACKET_OAM_TYPE_MPLS_TP_1 or
    // MESA_PACKET_OAM_TYPE_MPLS_TP_2.
    //
    // Label entry S-bit value to use for innermost non-reserved label
    // for MPLS OAM.
    //
    // Only valid values are 0 and 1.
    //
    // Ignored when #switch_frm is TRUE.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint8_t oam_mpls_sbit;

    // Ingress Service Index.
    //
    // If not MESA_ISDX_NONE, it will be used in ES0
    // lookups instead of the frame's classified VID.
    // See also #isdx_dont_use.
    // Ignored when #switch_frm is TRUE.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  Y
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    mesa_isdx_t isdx;

    // Ingress Flow Id.
    //
    // If not MESA_IFLOW_ID_NONE, it will be used to resolve the related ISDX that is used in ES0
    // lookups instead of the frame's classified VID.
    // Ignored when #switch_frm is TRUE.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_iflow_id_t iflow_id;

    // When set to TRUE, #isdx is not used for ES0 lookups,
    // only for frame counting.
    //
    // Ignored when #switch_frm is TRUE or #isdx is MESA_ISDX_NONE.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Jaguar2: N
    // Serval:  Y
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    mesa_bool_t isdx_dont_use;

    // Drop Precedence.
    //
    // The frame's drop precedence level after policing.
    // Ignored when #switch_frm is TRUE.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  Y
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    mesa_dp_level_t dp;

    // Masquerade port.
    // When masquerading, the frame will be handled as if it was received by
    // the ingress port specified in #masquerade_port.
    //
    // Its value will not be used unless #switch_frm is TRUE.
    //
    // Set it to MESA_PORT_NO_NONE to disable masquerading.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  Y
    // Jaguar2: N
    // Serval2: N
    // ServalT: N
    mesa_port_no_t masquerade_port;

    // PDU offset in 8 bit word counts.
    // Used in ptp-action's to indicate the start of the PTP PDU.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    uint32_t pdu_offset;

    // Automatic Frame Injector ID.
    //
    // This field has two different meanings depending
    // on architecture.
    // Serval:
    //   The ID of a previously allocated AFI resource.
    //
    //   Set to MESA_AFI_ID_NONE if you don't want
    //   a frame injected periodically.
    //
    // Jaguar2/Serval2/ServalT:
    //   This field is really not an ID, but a kind of boolean
    //   that indicates that the frame should be captured
    //   by the switch core's AFI block upon injection.
    //   When set to MESA_AFI_ID_NONE, the frame will not be
    //   captured by the switch core, otherwise it will.
    //   Use the mesa_afi_fast_inj_frm_hijack() or
    //   mesa_afi_slow_inj_frm_hijack() functions after successful
    //   injection to further configure the frame.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  Y
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
    mesa_afi_id_t afi_id;

    // Chip pipeline injection point.
    // Specifies where a frame is injected into the chip.
    //
    // Validity:
    // ------------
    // Luton26: N
    // Serval:  N
    // Jaguar2: Y
    // Serval2: Y
    // ServalT: Y
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

// Maximum Tx IFH length
#define MESA_PACKET_TX_IFH_STORAGE 28  // Tx IFH byte length (Constant)

// Compiled Tx Frame Header
//
// This is a pre-compiled representation of injection properties
// similar to those given by mesa_packet_tx_hdr_encode(), but wrapped
// in the following structure. The structure is useful for
// preallocation, and can be used in combination with
// mesa_packet_tx_frame().
typedef struct {
    uint32_t length;                            // Length of compiled IFH (in bytes)
    uint32_t ifh[MESA_PACKET_TX_IFH_STORAGE/4]; // Compiled, binary IFH
} mesa_packet_tx_ifh_t;

// Compile Tx Frame Header
//
// Compile a Tx frame header suitable for use with mesa_packet_tx_frame().
//
// info [IN]  Tx header properties.
// ifh  [OUT] Compiled Tx header.
mesa_rc mesa_packet_tx_hdr_compile(const mesa_inst_t                  inst,
                                   const mesa_packet_tx_info_t *const info,
                                         mesa_packet_tx_ifh_t  *const ifh);

// Send frame unmodified on port with pre-compiled IFH.
//
// ifh [IN]      Compiled IFH
// frame [IN]    Frame buffer excluding room for CRC.
// length [IN]   Frame length excluding CRC.
mesa_rc mesa_packet_tx_frame(const mesa_inst_t          inst,
                             const mesa_packet_tx_ifh_t *const ifh,
                             const uint8_t              *const frame,
                             const uint32_t             length);

// Initialize a Tx info structure.
//
// Initialize the contents of a mesa_packet_tx_info_t
// structure.
//
// info [OUT] Pointer to structure that gets initialized to defaults.
mesa_rc mesa_packet_tx_info_init(const mesa_inst_t                  inst,
                                       mesa_packet_tx_info_t *const info);

// The packet DMA configuration.
typedef struct {
    mesa_bool_t dma_enable[MESA_QUEUE_ARRAY_SIZE]; // Enable the given queues for DMA
} mesa_packet_dma_conf_t;

// Retreive packet DMA configuration.
//
// conf [OUT] Packet DMA configuration structure.
mesa_rc mesa_packet_dma_conf_get(const mesa_inst_t      inst,
                                 mesa_packet_dma_conf_t *const conf);

// Set packet DMA configuration.
//
// Zero or more packet queues may be enabled for DMA extraction.
// If a queue is enabled for DMA, it can be extracted/injected on the
// DMA interface of the system. Otherwise, the queues are enabled for
// register-based extraction/injection.
//
// conf [OUT] Packet DMA configuration structure.
mesa_rc mesa_packet_dma_conf_set(const mesa_inst_t            inst,
                                 const mesa_packet_dma_conf_t *const conf);

// Retreive the register offset for extration/injection DMA.
//
// One or more queues should be enabled for DMA before using the register offset.
// The returned offset is for the status register, which is the
// last register location in the DMA window. (Whole) Data word can be
// written by selecting the approprate register offsets before this
// offset, such that the status offset if the last word written/read.
//
// extraction [IN]
// offset     [OUT] Offset (32-bit word offset) for the DMA status register.
mesa_rc mesa_packet_dma_offset(const mesa_inst_t inst,
                               mesa_bool_t extraction,
                               uint32_t *offset);

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

#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_PACKET_
