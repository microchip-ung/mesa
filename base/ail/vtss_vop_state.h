// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_OAM_STATE_H_
#define _VTSS_OAM_STATE_H_

#if defined(VTSS_FEATURE_VOP)
typedef struct {
    struct {
        vtss_chip_counter_t   rx_valid_counter;
        vtss_chip_counter_t   rx_invalid_counter;
        vtss_chip_counter_t   rx_oo_counter;
        vtss_chip_counter_t   tx_counter;
    } ccm;
    struct {
        vtss_chip_counter_t   rx_lbr_counter;
        vtss_chip_counter_t   tx_lbm_counter;
        vtss_chip_counter_t   rx_lbr_oo_counter;
#if defined(VTSS_FEATURE_VOP_V2)
        vtss_chip_counter_t   rx_lbr_crc_counter;
        vtss_chip_counter_t   tx_lbr_counter;
#endif
    } lb;
    struct {
        vtss_chip_counter_t   rx_counter;
        vtss_chip_counter_t   tx_counter;
        vtss_chip_counter_t   rx_selected_counter;
        vtss_chip_counter_t   tx_selected_counter;
#if defined(VTSS_FEATURE_VOP_V2)
        vtss_chip_counter_t   rx_discard_counter;
        vtss_chip_counter_t   tx_discard_counter;
#endif
    } voe;
} vtss_oam_voe_internal_counters_t;

typedef enum {
    VTSS_VOE_FUNCTION_OAM,
    VTSS_VOE_FUNCTION_MRP,
} vtss_voe_function_t;

typedef struct {
    vtss_oam_voe_internal_counters_t counters;       /* Chip counters for a VOE */
    u32                              tx_next_lbm_transaction_id;
    u32                              rx_lbr_transaction_id;
} vtss_voe_internal_t;

typedef struct {
    BOOL                   allocated;
    vtss_voe_function_t    function;
    vtss_port_no_t         port;
    vtss_voe_type_t        type;
    vtss_oam_direction_t   direction;
} vtss_voe_alloc_t;

#if defined(VTSS_FEATURE_VOP_V2)
typedef struct {
    BOOL                   allocated;
    vtss_port_no_t         port;
    vtss_oam_direction_t   direction;
} vtss_voi_alloc_t;
#endif

typedef struct {
    /* CIL function pointers */
    vtss_rc (* vop_conf_set)(struct vtss_state_s *, const vtss_vop_conf_t *const);

    vtss_rc (* voe_event_active_get)(struct vtss_state_s *, u32, u32 *const);
    vtss_rc (* voe_event_mask_set)(struct vtss_state_s *, const vtss_voe_idx_t, const u32, const BOOL);
    vtss_rc (* voe_event_get)(struct vtss_state_s *, const vtss_voe_idx_t, u32 *const);

    vtss_rc (* voe_alloc)(struct vtss_state_s *, const vtss_voe_type_t, const vtss_port_no_t, const vtss_oam_direction_t, vtss_voe_idx_t *);
    vtss_rc (* voe_free)(struct vtss_state_s *, const vtss_voe_idx_t);

    vtss_rc (* voe_conf_set)(struct vtss_state_s *, const vtss_voe_idx_t, const vtss_voe_conf_t  *const);
    vtss_rc (* voe_cc_conf_set)(struct vtss_state_s *, const vtss_voe_idx_t, const vtss_voe_cc_conf_t  *const);
    vtss_rc (* voe_cc_rdi_set)(struct vtss_state_s *, const vtss_voe_idx_t, const BOOL);
    vtss_rc (* voe_cc_cpu_copy_next_set)(struct vtss_state_s *, const vtss_voe_idx_t);
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_rc (* voe_lt_conf_set)(struct vtss_state_s *, const vtss_voe_idx_t, const vtss_voe_lt_conf_t  *const);
    vtss_rc (* voe_lb_conf_set)(struct vtss_state_s *, const vtss_voe_idx_t, const vtss_voe_lb_conf_t  *const);
    vtss_rc (* voe_laps_conf_set)(struct vtss_state_s *, const vtss_voe_idx_t, const vtss_voe_laps_conf_t  *const);
#endif
    vtss_rc (* voe_status_get)(struct vtss_state_s *, const vtss_voe_idx_t, vtss_voe_status_t *const);
    vtss_rc (* voe_cc_status_get)(struct vtss_state_s *, const vtss_voe_idx_t, vtss_voe_cc_status_t *const);
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_rc (* voe_lt_status_get)(struct vtss_state_s *, const vtss_voe_idx_t, vtss_voe_lt_status_t *const);
    vtss_rc (* voe_lb_status_get)(struct vtss_state_s *, const vtss_voe_idx_t, vtss_voe_lb_status_t *const);
    vtss_rc (* voe_laps_status_get)(struct vtss_state_s *, const vtss_voe_idx_t, vtss_voe_laps_status_t *const);
#endif
    vtss_rc (* voe_counters_get)(struct vtss_state_s *, const vtss_voe_idx_t, vtss_voe_counters_t *const);
    vtss_rc (* voe_cc_counters_get)(struct vtss_state_s *, const vtss_voe_idx_t, vtss_voe_cc_counters_t *const);
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_rc (* voe_lb_counters_get)(struct vtss_state_s *, const vtss_voe_idx_t, vtss_voe_lb_counters_t *const);
#endif
    vtss_rc (* voe_counters_clear)(struct vtss_state_s *, const vtss_voe_idx_t);
    vtss_rc (* voe_cc_counters_clear)(struct vtss_state_s *, const vtss_voe_idx_t);
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_rc (* voe_lb_counters_clear)(struct vtss_state_s *, const vtss_voe_idx_t);
#endif
#if defined(VTSS_FEATURE_VOP_V2)
    vtss_rc (* voi_alloc)(struct vtss_state_s *, const vtss_port_no_t, const vtss_oam_direction_t, vtss_voi_idx_t *);
    vtss_rc (* voi_free)(struct vtss_state_s *vtss_state, const vtss_voi_idx_t);

    vtss_rc (* voi_conf_set)(struct vtss_state_s *, const vtss_voi_idx_t, const vtss_voi_conf_t *);
#endif
    /* Configuration */
    vtss_vop_conf_t       vop_conf;
    vtss_voe_alloc_t      voe_alloc_data[VTSS_VOE_CNT];
    vtss_voe_conf_t       voe_conf[VTSS_VOE_CNT];
    vtss_voe_cc_conf_t    voe_cc_conf[VTSS_VOE_CNT];
    BOOL                  voe_rdi_conf[VTSS_VOE_CNT];
#if defined(VTSS_FEATURE_VOP_CFM)
    vtss_voe_lt_conf_t    voe_lt_conf[VTSS_VOE_CNT];
    vtss_voe_lb_conf_t    voe_lb_conf[VTSS_VOE_CNT];
    vtss_voe_laps_conf_t  voe_laps_conf[VTSS_VOE_CNT];
#endif
    u32                   voe_event_mask[VTSS_VOE_CNT];
#if defined(VTSS_FEATURE_VOP_V2)
    vtss_voi_alloc_t      voi_alloc_data[VTSS_VOI_CNT];
    vtss_voi_conf_t       voi_conf[VTSS_VOI_CNT];
#endif
    /* Internal */
    vtss_voe_internal_t   voe_internal[VTSS_VOE_CNT];
    vtss_voe_idx_t        voe_poll_idx;
} vtss_oam_state_t;

vtss_rc vtss_oam_inst_create(struct vtss_state_s *vtss_state);
void vtss_oam_debug_print(struct vtss_state_s *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info);

#endif /* VTSS_FEATURE_VOP */

#endif /* _VTSS_OAM_STATE_H_ */
