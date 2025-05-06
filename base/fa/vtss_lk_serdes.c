// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_LAIKA)

vtss_rc vtss_fa_port2sd(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *sd_indx, u32 *sd_type)
{
    *sd_indx = 0;
    *sd_type = FA_SERDES_TYPE_UNKNOWN;
    return VTSS_RC_OK;
}

u32 vtss_fa_port2sd_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no) { return 0; }

u32 vtss_fa_sd_lane_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no) { return 0; }

u32 vtss_to_sd6g_lane(vtss_state_t *vtss_state, u32 indx) { return 0; }

u32 vtss_to_sd10g_lane(vtss_state_t *vtss_state, u32 indx) { return 0; }

u32 vtss_to_sd_lane(vtss_state_t *vtss_state, u32 indx) { return 0; }

vtss_rc vtss_fa_sd_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_serdes_mode_t mode)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_serdes_init(vtss_state_t *vtss_state) { return VTSS_RC_OK; }

vtss_rc fa_serdes_ctle_adjust(vtss_state_t *vtss_state,
                              lmu_ss_t     *ss,
                              u32           port_no,
                              BOOL          ro,
                              u32          *vga,
                              u32          *eqr,
                              u32          *eqc)
{
    return VTSS_RC_OK;
}

vtss_rc fa_debug_chip_serdes(vtss_state_t                  *vtss_state,
                             lmu_ss_t                      *ss,
                             const vtss_debug_info_t *const info,
                             vtss_port_no_t                 port_no)
{
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_LAIKA */
