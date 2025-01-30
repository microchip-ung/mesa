// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_LAIKA)

vtss_rc vtss_cil_miim_read(vtss_state_t          *vtss_state,
                           vtss_miim_controller_t miim_controller,
                           u8                     miim_addr,
                           u8                     addr,
                           u16                   *value,
                           BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_miim_write(vtss_state_t          *vtss_state,
                            vtss_miim_controller_t miim_controller,
                            u8                     miim_addr,
                            u8                     addr,
                            u16                    value,
                            BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_mmd_read(vtss_state_t          *vtss_state,
                          vtss_miim_controller_t miim_controller,
                          u8                     miim_addr,
                          u8                     mmd,
                          u16                    addr,
                          u16                   *value,
                          BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_mmd_read_inc(vtss_state_t          *vtss_state,
                              vtss_miim_controller_t miim_controller,
                              u8                     miim_addr,
                              u8                     mmd,
                              u16                    addr,
                              u16                   *buf,
                              u8                     count,
                              BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_mmd_write(vtss_state_t          *vtss_state,
                           vtss_miim_controller_t miim_controller,
                           u8                     miim_addr,
                           u8                     mmd,
                           u16                    addr,
                           u16                    data,
                           BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_LAIKA */
