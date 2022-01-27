// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_MRP_STATE_H_
#define _VTSS_MRP_STATE_H_

#if defined(VTSS_FEATURE_MRP)
typedef struct {
    vtss_chip_counter_t tst_rx_count;
    vtss_chip_counter_t itst_rx_count;
} vtss_mrp_internal_counters_t;

typedef struct {
    vtss_mrp_conf_t          conf;
    vtss_mrp_ring_state_t    ring_state;
    vtss_mrp_ring_state_t    in_ring_state;
    vtss_mrp_tst_loc_conf_t  tst_loc_conf;
    vtss_mrp_tst_copy_conf_t tst_copy_conf;
    u32                      event_mask;
    vtss_mrp_port_state_t    p_port_state;
    vtss_mrp_port_state_t    s_port_state;
    vtss_mrp_port_state_t    i_port_state;
    vtss_mrp_best_mrm_t      best_mrm;

    /* Internals */
    BOOL active;
    u32  tst_loc_idx;   /* The allocated LOC timer index */
    u32  itst_loc_idx;   /* The allocated Interconnect LOC timer index */
    u32  ring_transitions;   /* Number op ring state transitions from closed to open */
    u32  in_ring_transitions;   /* Number op interconnected ring state transitions from closed to open */
    vtss_mrp_internal_counters_t p_counters;       /* P port chip counters */
    vtss_mrp_internal_counters_t s_counters;       /* S port chip counters */
    vtss_mrp_internal_counters_t i_counters;       /* I port chip counters */
} vtss_mrp_data_t;

typedef struct {
    /* CIL function pointers */
    vtss_rc (* mrp_add)(struct vtss_state_s *, const vtss_mrp_idx_t, const vtss_mrp_conf_t *const);
    vtss_rc (* mrp_del)(struct vtss_state_s *, const vtss_mrp_idx_t);
    vtss_rc (* mrp_primary_port_set)(struct vtss_state_s *, const vtss_mrp_idx_t, vtss_port_no_t);
    vtss_rc (* mrp_ring_role_set)(struct vtss_state_s *, const vtss_mrp_idx_t, const vtss_mrp_ring_role_t);
    vtss_rc (* mrp_ring_state_set)(struct vtss_state_s *, const vtss_mrp_idx_t, const vtss_mrp_ring_state_t);
    vtss_rc (* mrp_port_state_set)(struct vtss_state_s *, const vtss_mrp_idx_t, const vtss_port_no_t, const vtss_mrp_port_state_t);
    vtss_rc (* mrp_in_ring_state_set)(struct vtss_state_s *, const vtss_mrp_idx_t, const vtss_mrp_ring_state_t);
    vtss_rc (* mrp_best_mrm_set)(struct vtss_state_s *, const vtss_mrp_idx_t, const vtss_mrp_best_mrm_t *const);
    vtss_rc (* mrp_tst_loc_conf_set)(struct vtss_state_s *, const vtss_mrp_idx_t, const vtss_mrp_tst_loc_conf_t *const);
    vtss_rc (* mrp_tst_hitme_once)(struct vtss_state_s *, const vtss_mrp_idx_t);
    vtss_rc (* mrp_itst_hitme_once)(struct vtss_state_s *, const vtss_mrp_idx_t);
    vtss_rc (* mrp_tst_copy_conf_set)(struct vtss_state_s *, const vtss_mrp_idx_t, const vtss_mrp_tst_copy_conf_t *const);
    vtss_rc (* mrp_status_get)(struct vtss_state_s *, const vtss_mrp_idx_t, vtss_mrp_status_t *const);
    vtss_rc (* mrp_counters_get)(struct vtss_state_s *, const vtss_mrp_idx_t, vtss_mrp_counters_t *const);
    vtss_rc (* mrp_counters_clear)(struct vtss_state_s *, const vtss_mrp_idx_t);
    vtss_rc (* mrp_event_mask_set)(struct vtss_state_s *, const vtss_mrp_idx_t, const u32, const BOOL);
    vtss_rc (* mrp_event_get)(struct vtss_state_s *, const vtss_mrp_idx_t, vtss_mrp_event_t *const);

    /* Internal MRP data */
    u32             mrp_poll_idx;  /* The one second MRP poll index */
    vtss_mrp_data_t data[VTSS_MRP_CNT];
} vtss_mrp_state_t;

vtss_rc vtss_mrp_inst_create(struct vtss_state_s *vtss_state);
void vtss_mrp_debug_print(struct vtss_state_s        *vtss_state,
                          const vtss_debug_printf_t  pr,
                          const vtss_debug_info_t    *const info);

#endif /* VTSS_FEATURE_MRP */

#endif /* _VTSS_MRP_STATE_H_ */
