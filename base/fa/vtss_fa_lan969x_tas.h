// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_LAN969X_H_
#define _VTSS_FA_LAN969X_H_

#define TAS_LIST_STATE_ADMIN       0
#define TAS_LIST_STATE_ADVANCING   1
#define TAS_LIST_STATE_PENDING     2
#define TAS_LIST_STATE_OPERATING   3
#define TAS_LIST_STATE_TERMINATING 4

#define TAS_LIST_IDX_NONE    0xFFFFFFFF
#define TAS_PROFILE_IDX_NONE 0xFFFFFFFF
#define TAS_ENTRY_IDX_NONE   0xFFFFFFFF

#define FA_HSCH_L0_SE(port, queue) FA_TGT ? ((64 * port) + (8 * queue)) : LA_HSCH_L0_SE(port, queue)
#define FA_HSCH_TAS_SE(port, ot) FA_TGT ? (5040 + 64 + port) : LA_HSCH_TAS_SE(port, ot)
#define FA_HSCH_L0_OT_SE(port) (RT_HSCH_L0_SES - 35 + port)

#define LA_HSCH_TAS_SE(port, ot) ((ot) ? (FA_HSCH_L0_OT_SE(port)) : (RT_HSCH_L0_SES + port))
#define LA_HSCH_L0_SE(port, queue) ((32 * port) + (4 * queue))

#if defined(VTSS_FEATURE_QOS_TAS)
u32 lan969x_tas_list_allocate(vtss_state_t *vtss_state,  u32 length);
vtss_rc lan969x_tas_list_free(vtss_state_t *vtss_state,  u32 list_idx);
vtss_rc lan969x_tas_current_port_conf_calc(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_qos_tas_port_conf_t *current_port_conf);

vtss_rc lan969x_tas_list_start(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                               u32 list_idx, u32 obsolete_list_idx,
                               vtss_qos_tas_port_conf_t *port_conf, u32 startup_time);
vtss_rc lan966x_tas_frag_size_update(struct vtss_state_s   *vtss_state,
                                     const vtss_port_no_t  port_no);
void tas_list_state_write(vtss_state_t *vtss_state, u32 list_idx, u32 state);
u8 tas_link_speed_calc(vtss_port_speed_t speed);
vtss_rc tas_profile_free(vtss_state_t *vtss_state,  u32 profile_idx);
#endif

#endif /* _VTSS_FA_LAN969X_H_ */
