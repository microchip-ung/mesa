// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef VTSS_FA_LAN969X_H
#define VTSS_FA_LAN969X_H

#define TAS_LIST_STATE_ADMIN       0U
#define TAS_LIST_STATE_ADVANCING   1U
#define TAS_LIST_STATE_PENDING     2U
#define TAS_LIST_STATE_OPERATING   3U
#define TAS_LIST_STATE_TERMINATING 4U

#define TAS_LIST_IDX_NONE    0xFFFFFFFFU
#define TAS_PROFILE_IDX_NONE 0xFFFFFFFFU
#define TAS_ENTRY_IDX_NONE   0xFFFFFFFFU

#define FA_HSCH_L0_SE(port, queue)                                                                 \
    (FA_TGT != 0) ? ((64U * port) + (8U * queue)) : LA_HSCH_L0_SE(port, queue)
#define FA_HSCH_TAS_SE(port, ot) (FA_TGT != 0) ? (5040U + 64U + port) : LA_HSCH_TAS_SE(port, ot)
#define FA_HSCH_L0_OT_SE(port)   (RT_HSCH_L0_SES - 35U + port)

#define LA_HSCH_TAS_SE(port, ot)   (((ot) != 0) ? (FA_HSCH_L0_OT_SE(port)) : (RT_HSCH_L0_SES + port))
#define LA_HSCH_L0_SE(port, queue) ((32U * port) + (4U * queue))

#if defined(VTSS_FEATURE_QOS_TAS)
u32     lan969x_tas_list_allocate(vtss_state_t *vtss_state, u32 length);
vtss_rc lan969x_tas_list_free(vtss_state_t *vtss_state, u32 list_idx);
vtss_rc lan969x_tas_current_port_conf_calc(vtss_state_t             *vtss_state,
                                           vtss_port_no_t            port_no,
                                           vtss_qos_tas_port_conf_t *current_port_conf);

vtss_rc lan969x_tas_list_start(vtss_state_t             *vtss_state,
                               const vtss_port_no_t      port_no,
                               u32                       list_idx,
                               u32                       obsolete_list_idx,
                               vtss_qos_tas_port_conf_t *port_conf,
                               u32                       startup_time);
vtss_rc lan966x_tas_frag_size_update(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);
void    tas_list_state_write(vtss_state_t *vtss_state, u32 list_idx, u32 state);
u8      tas_link_speed_calc(vtss_port_speed_t speed);
vtss_rc tas_profile_free(vtss_state_t *vtss_state, u32 profile_idx);
#endif

#endif /* VTSS_FA_LAN969X_H */
