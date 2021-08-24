// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_MACSEC_H_
#define _VTSS_MACSEC_H_

#define VTSS_MACSEC_1G_MAX_SA_RX  VTSS_MACSEC_1G_MAX_SA
#define VTSS_MACSEC_1G_MAX_SA_TX  VTSS_MACSEC_1G_MAX_SA
#define VTSS_MACSEC_1G_MAX_SC_RX  VTSS_MACSEC_1G_MAX_SA/2     /* Min 2 RxSA per SC         */
#define VTSS_MACSEC_1G_MAX_SC_TX  VTSS_MACSEC_1G_MAX_SC_RX
#define VTSS_MACSEC_1G_MAX_SECY   VTSS_MACSEC_1G_MAX_SC_TX

#define VTSS_MACSEC_10G_MAX_SA_RX  VTSS_MACSEC_10G_MAX_SA
#define VTSS_MACSEC_10G_MAX_SA_TX  VTSS_MACSEC_10G_MAX_SA
#define VTSS_MACSEC_10G_MAX_SC_RX  VTSS_MACSEC_10G_MAX_SA/2     /* Min 2 RxSA per SC         */
#define VTSS_MACSEC_10G_MAX_SC_TX  VTSS_MACSEC_10G_MAX_SC_RX
#define VTSS_MACSEC_10G_MAX_SECY   VTSS_MACSEC_10G_MAX_SC_TX

#define VTSS_MACSEC_ACTION_MAX 3
#define VTSS_MACSEC_DIRECTION_MAX 3
#define VTSS_MACSEC_MTU_MAX    32761 /**<Maximum supported MTU for MACSEC*/
typedef struct {
    BOOL                         in_use;
    BOOL                         enabled;
    u32                          record;
    vtss_macsec_sak_t            sak;
    vtss_macsec_rx_sa_status_t   status;
    vtss_macsec_rx_sa_counters_t cnt;
    vtss_macsec_ssci_t           ssci;
} vtss_macsec_internal_rx_sa_t;

typedef struct {
    BOOL                         in_use;
    BOOL                         enabled;
    u32                          record;
    BOOL                         confidentiality;
    vtss_macsec_sak_t            sak;
    vtss_macsec_tx_sa_status_t   status;
    vtss_macsec_tx_sa_counters_t cnt;
    vtss_macsec_ssci_t           ssci;
} vtss_macsec_internal_tx_sa_t;

typedef struct {
    BOOL                         in_use;
    vtss_macsec_sci_t            sci;
    vtss_macsec_rx_sc_status_t   status;
    vtss_macsec_rx_sc_counters_t cnt;
    vtss_macsec_internal_rx_sa_t *sa[VTSS_MACSEC_SA_PER_SC_MAX];
    vtss_macsec_rx_sc_conf_t     conf;
    vtss_macsec_rx_sa_counters_t del_rx_sa_cnt;
    u64                          in_octets_validation_disabled;
} vtss_macsec_internal_rx_sc_t;

typedef struct {
    BOOL                         in_use;
    vtss_macsec_tx_sc_status_t   status;
    vtss_macsec_tx_sc_counters_t cnt;
    vtss_macsec_tx_sa_counters_t del_tx_sa_cnt;
    vtss_macsec_internal_tx_sa_t *sa[VTSS_MACSEC_SA_PER_SC_MAX];
    u64                          out_octets_untagged;
} vtss_macsec_internal_tx_sc_t;

typedef struct {
    BOOL                              in_use;
    vtss_macsec_sci_t                 sci;
    vtss_macsec_service_id_t          service_id;
    BOOL                              controlled_port_enabled;
    vtss_macsec_secy_port_counters_t  controlled_cnt;
    vtss_macsec_secy_counters_t       secy_cnt;
    vtss_macsec_secy_conf_t           conf;
    vtss_macsec_internal_rx_sc_t      *rx_sc[VTSS_MACSEC_MAX_SC_RX];
    vtss_macsec_internal_tx_sc_t      tx_sc;
    vtss_macsec_match_pattern_t       pattern[VTSS_MACSEC_ACTION_MAX][VTSS_MACSEC_DIRECTION_MAX];
    u32                               pattern_record[VTSS_MACSEC_ACTION_MAX][VTSS_MACSEC_DIRECTION_MAX];
    vtss_macsec_tag_bypass_t          tag_bypass;
} vtss_macsec_internal_secy_t;

typedef struct {
    vtss_macsec_common_counters_t          common_cnt;          // Global common port counters
    vtss_macsec_common_counters_t          common_cnt_clr_val;  // Global common port counters can not be cleared on read,
    // so software needs to keep track of counters,
    // which is why we keep track of what the hw counters are at the moment sw clear is done
    vtss_macsec_secy_port_counters_t       uncontrolled_cnt;    // Global uncontrolled port counters
    vtss_macsec_default_action_policy_t    default_action;
    vtss_macsec_control_frame_match_conf_t control_match[VTSS_MACSEC_CP_RULES];
    u32                                    egr_bypass_record[VTSS_MACSEC_CP_RULES];
    vtss_macsec_bypass_mode_t              bypass_mode;
    vtss_macsec_init_t                     init;
    BOOL                                   warm_start_reg_changed;
    vtss_macsec_mtu_t                      mtu_conf; /** Configuration of MTU */
    BOOL                                   macsec_revb;
    u16                                    mac_block_mtu; /** MAC Block MTU */
    BOOL                                   rmon_counters_clr; /** MACsec RMON counters clear flag */
    BOOL                                   spd_change_macsec_recfg; /** MACsec Reconfig flag for speed change */
    u64                                    ingr_flow_map; /** ingress flow map */
    u8                                     recfg_speed;
} vtss_macsec_internal_glb_t;


typedef struct {
    vtss_macsec_internal_secy_t         secy[VTSS_MACSEC_MAX_SECY];
    vtss_macsec_internal_rx_sc_t        rx_sc[VTSS_MACSEC_MAX_SC_RX];
    vtss_macsec_internal_rx_sa_t        rx_sa[VTSS_MACSEC_MAX_SA_RX];
    vtss_macsec_internal_tx_sa_t        tx_sa[VTSS_MACSEC_MAX_SA_TX];
    vtss_macsec_internal_glb_t          glb;
    vtss_macsec_rc_dbg_counters_t       rc_dbg_counters;
} vtss_macsec_internal_conf_t;

vtss_rc vtss_macsec_sync(struct vtss_state_s *vtss_state,
                         const vtss_port_no_t port_no);

vtss_rc vtss_debug_print_macsec(struct vtss_state_s *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t *const info);


// Returning TRUE is the port is MacSec capable
BOOL is_macsec_capable(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);

// See vtss_macsec_api.c
vtss_rc vtss_macsec_speed_conf_priv(struct vtss_state_s    *vtss_state,
                                    const  vtss_port_no_t  port_no,
                                    const  BOOL            enable,
                                    const  BOOL            speed_recfg);

vtss_rc vtss_macsec_preamble_shrink_set_priv(struct vtss_state_s        *vtss_state,
                                             const vtss_port_no_t   port_no,
                                             const BOOL             enable);

#endif /* _VTSS_MACSEC_H_ */
