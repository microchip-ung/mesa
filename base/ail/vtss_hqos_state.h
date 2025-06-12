// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_HQOS_STATE_H_
#define _VTSS_HQOS_STATE_H_

#if defined(VTSS_FEATURE_HQOS)

#define VTSS_HQOS_PORT_L0_MAX VTSS_HQOS_PORT_ENTRY_MAX
#define VTSS_HQOS_PORT_L1_MAX (VTSS_HQOS_PORT_L0_MAX / 64)
#define VTSS_HQOS_SE_NONE     0xFFFFFFFF
#define VTSS_HQOS_VPORT_NONE  0xFFFFFFFF
#define VTSS_HQOS_QSHP_NONE   0xFFFFFFFF

typedef struct {
    vtss_hqos_id_t   hqos_id;
    vtss_hqos_conf_t conf;
    u32              se;       /* The used SE */
    u32              vport;    /* The used VPORT */
    u32              qshp;     /* The used QSHP */
    u32              l1_se;    /* Connected to this L1 SE */
    u32              l1_input; /* Connected to this L1 SE input */
} vtss_hqos_l0_se_t;

typedef struct {
    u32 se;       /* The used SE */
    u32 l2_input; /* Connected to this L2 SE input */
} vtss_hqos_l1_se_t;

typedef struct {
    u32               entry_count;    // Number of entries added. An entry is in HW a L0 SE.
    u32               priority_count; // Number of priority entries added.
    vtss_hqos_l0_se_t l0_ses[VTSS_HQOS_PORT_L0_MAX];
    vtss_hqos_l1_se_t l1_ses[VTSS_HQOS_PORT_L1_MAX];
    u32               priority_l1_se; // L1 SE used for priority QGRP
    u32               unknown_l0_se;  // L0 SE and VPORT used for unknown QGRP
    u32               unknown_vport;
} vtss_hqos_hier_port_t;

typedef struct {
    vtss_hqos_port_conf_t port_conf[VTSS_PORT_ARRAY_SIZE];
    vtss_hqos_hier_port_t hier_conf[VTSS_PORT_ARRAY_SIZE];
} vtss_hqos_state_t;

vtss_rc vtss_hqos_inst_create(struct vtss_state_s *vtss_state);
vtss_rc vtss_hqos_restart_sync(struct vtss_state_s *vtss_state);
vtss_rc vtss_cil_hqos_port_conf_set(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_cil_hqos_add(struct vtss_state_s          *vtss_state,
                          const vtss_port_no_t          port_no,
                          const vtss_hqos_id_t          hqos_id,
                          const vtss_hqos_conf_t *const conf);
vtss_rc vtss_cil_hqos_del(struct vtss_state_s *vtss_state,
                          const vtss_port_no_t port_no,
                          const vtss_hqos_id_t hqos_id);
vtss_rc vtss_cil_hqos_status_get(struct vtss_state_s      *vtss_state,
                                 const vtss_port_no_t      port_no,
                                 const vtss_hqos_id_t      hqos_id,
                                 vtss_hqos_status_t *const status);

void vtss_hqos_debug_print(struct vtss_state_s           *vtss_state,
                           lmu_ss_t                      *ss,
                           const vtss_debug_info_t *const info);

#endif /* VTSS_FEATURE_HQOS */

#endif /* _VTSS_HQOS_STATE_H_ */
