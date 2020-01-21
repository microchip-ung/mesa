// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_MAS_CIL_H_
#define _VTSS_MAS_CIL_H_

/* Use relative DWORD addresses for registers - must be first */
#define VTSS_IOADDR(t,o) ((((t) - VTSS_IO_ORIGIN1_OFFSET) >> 2) + (o))
#define VTSS_IOREG(t,o)  (VTSS_IOADDR(t,o))

#include "vtss_api.h"

#if defined(VTSS_ARCH_LAN966X)
#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#include "../ail/vtss_state.h"
#include "../ail/vtss_common.h"
#include "../ail/vtss_util.h"
#include "vtss_lan966x.h"

vtss_rc vtss_lan966x_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_afi_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

#endif /* VTSS_ARCH_LAN966X */
#endif /* _VTSS_MAS_CIL_H_ */
