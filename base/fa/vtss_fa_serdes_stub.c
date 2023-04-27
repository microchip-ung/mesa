// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_fa_cil.h"

#include "vtss_fa_sd10g28_setup.h"
#include "vtss_fa_sd25g28_setup.h"

#if defined(VTSS_ARCH_LAN969X_FPGA)
vtss_rc fa_debug_serdes_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                            const vtss_port_serdes_debug_t *const conf)

{
    return VTSS_RC_OK;
}
vtss_rc fa_debug_chip_serdes(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info,
                             vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

u32 vtss_fa_sd_lane_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 indx = 0, type;

    (void)vtss_fa_port2sd(vtss_state, port_no, &indx, &type);
    if (type == FA_SERDES_TYPE_6G) {
        return indx;
    } else if (type == FA_SERDES_TYPE_10G) {
        return indx + RT_SERDES_10G_START;
    } else {
        return(indx + RT_SERDES_25G_START);
    }
}

vtss_rc vtss_fa_sd_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no,  vtss_serdes_mode_t mode)
{
    return VTSS_RC_OK;
}
u32 vtss_to_sd_lane(vtss_state_t *vtss_state, u32 indx)
{
    return VTSS_RC_OK;
}

vtss_rc fa_serdes_ctle_adjust(vtss_state_t *vtss_state, const vtss_debug_printf_t pr,
                              u32 port_no, BOOL ro, u32 *vga, u32 *eqr, u32 *eqc)
{
    return VTSS_RC_OK;
}
u32 vtss_to_dev25g(vtss_state_t *vtss_state, u32 port)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_port2sd(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *sd_indx, u32 *sd_type)
{
    vtss_port_interface_t if_type = vtss_state->port.conf[port_no].if_type;
    u32 p = VTSS_CHIP_PORT(port_no);

    switch (if_type) {
    case VTSS_PORT_INTERFACE_QSGMII:
        if (p <= 23) {
            u32 Q = (p -  p % 4) / 4;
            *sd_indx = Q;
            VTSS_N("(Q QUAD 1G SD) QSGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
        } else {
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_PORT_INTERFACE_QXGMII: /* QXGMII:    4x2G5 devices. Mode 'R'. */
        if (p >= 8 && p <= 23) {
            u32 R = (p -  p % 4) / 4;
            *sd_indx = R;
            VTSS_N("(R QUAD 2G5 SD) QXGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
        } else {
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: /* DXGMII_10G: 2x5G devices. Mode 'U'.*/
        if (p >= 8 && p <= 21) {
            int U = p <= 9 ? 2 : p <= 13 ? 3 : p <= 17 ? 4 : 5;
            *sd_indx = U;
            VTSS_N("(U DUAL 5G SD) 10USXGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
        } else {
            return VTSS_RC_ERROR;
        }
        break;
    default:
        if (p == 0 || p == 4 || p == 8 || p == 12 || p == 16 || p == 20 || p == 24) {
            *sd_indx = p / 4;
            VTSS_N("Single Serdes p:%d SD10_LANE index: %d",p, *sd_indx);
        } else if (p > 24 && p < 28)  {
            *sd_indx = 6 + p - 24;
            VTSS_N("Single Serdes p:%d SD10_LANE index: %d",p, *sd_indx);
        } else {
            return VTSS_RC_ERROR;
        }
    }

    if (sd_type != NULL) {
        *sd_type = FA_SERDES_TYPE_10G;
    }

    return VTSS_RC_OK;
}
#endif // defined(VTSS_ARCH_LAN969X_FPGA)
