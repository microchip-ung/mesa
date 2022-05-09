// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PACKET_STATE_H_
#define _VTSS_PACKET_STATE_H_

#if defined(VTSS_FEATURE_PACKET)

#define VTSS_VSTAX_HDR_SIZE 12 /**< VStaX header size */
#define VTSS_PACKET_TX_IFH_STORAGE 36

typedef struct {
    u32 length;                            /**< Length of compiled IFH (in bytes) */
    u32 ifh[VTSS_PACKET_TX_IFH_STORAGE/4]; /**< Compiled, binary IFH   */
} vtss_packet_tx_ifh_t;

typedef struct {
    /* CIL function pointers */
    vtss_rc (*rx_conf_set)(struct vtss_state_s *vtss_state);
    vtss_rc (*rx_frame)(struct vtss_state_s *vtss_state,
                        u8                  *const data,
                        const u32           buflen,
                        vtss_packet_rx_info_t *const rx_info);
    vtss_rc (*tx_frame_ifh)(struct vtss_state_s *vtss_state,
                            const vtss_packet_tx_ifh_t *const ifh,
                            const u8              *const frame,
                            const u32             length);
    vtss_rc (*rx_hdr_decode)(const struct vtss_state_s   *const state,
                             const vtss_packet_rx_meta_t *const meta,
                             const u8                     hdr[VTSS_PACKET_HDR_SIZE_BYTES],
                                   vtss_packet_rx_info_t *const info);
    vtss_rc (*tx_hdr_encode)(struct vtss_state_s   *const state,
                             const vtss_packet_tx_info_t *const info,
                                   u8                    *const bin_hdr,
                                   u32                   *const bin_hdr_len);

    vtss_rc (*npi_conf_set)(struct vtss_state_s *vtss_state, const vtss_npi_conf_t *const conf);
    vtss_rc (*packet_phy_cnt_to_ts_cnt)(struct vtss_state_s *vtss_state,
                                        u32 phy_cnt,
                                        u64 *ts_cnt);
    vtss_rc (*packet_ns_to_ts_cnt)(struct vtss_state_s *vtss_state,
                                   u32                 ns,
                                   u64                 *ts_cnt);
    vtss_rc (*ptp_get_timestamp)(struct vtss_state_s             *vtss_state,
                                 const u8                        *const frm,
                                 const vtss_packet_rx_info_t     *const rx_info,
                                 vtss_packet_ptp_message_type_t  message_type,
                                 vtss_packet_timestamp_props_t   ts_props,
                                 u64                             *rxTime,
                                 BOOL                            *timestamp_ok);

    /* Configuration/state */
    BOOL                       manual_mode; // Manual injection/extraction
    u32                        rx_queue_count;
    vtss_packet_rx_conf_t      rx_conf;
    vtss_packet_rx_port_conf_t rx_port_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_npi_conf_t            npi_conf;
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    // Desired redirect port for a given Rx queue.
    vtss_phys_port_no_t        default_qu_redirect[VTSS_PACKET_RX_QUEUE_CNT];
#endif

    /* RX IFH Size */
    unsigned int               rx_ifh_size;
} vtss_packet_state_t;

vtss_rc vtss_packet_inst_create(struct vtss_state_s *vtss_state);
vtss_rc vtss_cmn_logical_to_chip_port_mask(const struct vtss_state_s *const state,
                                                 u64                 logical_port_mask,
                                                 u64                 *chip_port_mask,
                                                 vtss_chip_no_t      *chip_no,
                                                 vtss_port_no_t      *stack_port_no,
                                                 u32                 *port_cnt,
                                                 vtss_port_no_t      *port_no);

vtss_port_no_t vtss_cmn_chip_to_logical_port(const struct vtss_state_s       *const state,
                                             const vtss_chip_no_t      chip_no,
                                             const vtss_phys_port_no_t chip_port);

vtss_rc vtss_cmn_packet_hints_update(const struct vtss_state_s          *const state,
                                     const vtss_trace_group_t           trc_grp,
                                     const vtss_etype_t                 etype,
                                           vtss_packet_rx_info_t *const info);

#if VTSS_OPT_DEBUG_PRINT
void vtss_packet_debug_print(struct vtss_state_s *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info);
#endif
#endif /* VTSS_FEATURE_PACKET */

#endif /* _VTSS_PACKET_STATE_H_ */
