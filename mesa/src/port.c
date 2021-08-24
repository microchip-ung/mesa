// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_api.h>
#include <mesa.h>

mesa_rc mesa_conv2_vtss_port_counters_t_to_mesa_port_counters_t(const vtss_port_counters_t *in, mesa_port_counters_t *out)
{
    vtss_prio_t               prio;
    mesa_port_prio_counters_t *c;

    for (prio = 0; prio < VTSS_PRIOS; prio++) {
        c = &out->prio[prio];
        c->rx = in->prop.rx_prio[prio];
        c->tx = in->prop.tx_prio[prio];
#if defined(VTSS_ARCH_CARACAL)
        c->rx_green = in->evc.rx_green[prio];
        c->rx_yellow = in->evc.rx_yellow[prio];
        c->rx_red = in->evc.rx_red[prio];
        c->rx_green_discard = in->evc.rx_green_discard[prio];
        c->rx_yellow_discard = in->evc.rx_yellow_discard[prio];
        c->tx_green = in->evc.tx_green[prio];
        c->tx_yellow = in->evc.tx_yellow[prio];
#endif
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_port_counters_t_to_vtss_port_counters_t(const mesa_port_counters_t *in, vtss_port_counters_t *out)
{
    vtss_prio_t                     prio;
    const mesa_port_prio_counters_t *c;

    for (prio = 0; prio < VTSS_PRIOS; prio++) {
        c = &in->prio[prio];
        out->prop.rx_prio[prio] = c->rx;
        out->prop.tx_prio[prio] = c->tx;
#if defined(VTSS_ARCH_CARACAL)
        out->evc.rx_green[prio] = c->rx_green;
        out->evc.rx_yellow[prio] = c->rx_yellow;
        out->evc.rx_red[prio] = c->rx_red;
        out->evc.rx_green_discard[prio] = c->rx_green_discard;
        out->evc.rx_yellow_discard[prio] = c->rx_yellow_discard;
        out->evc.tx_green[prio] = c->tx_green;
        out->evc.tx_yellow[prio] = c->tx_yellow;
#endif
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_port_map_get(const mesa_inst_t  inst,
                          uint32_t           cnt,
                          mesa_port_map_t    *port_map)
{
    mesa_rc         rc = MESA_RC_ERROR;
    vtss_port_map_t vtss_map[VTSS_PORTS];
    vtss_port_no_t  port_no;

    if (cnt > VTSS_PORTS) {
        return MESA_RC_ERROR;
    }

    rc = vtss_port_map_get((const vtss_inst_t)inst, vtss_map);
    if (rc != VTSS_RC_OK) {
        return rc;
    }

    for (port_no = 0; port_no < cnt; port_no++) {
        mesa_conv_vtss_port_map_t_to_mesa_port_map_t(&vtss_map[port_no], &port_map[port_no]);
    }
    return rc;
}

mesa_rc mesa_port_map_set(const mesa_inst_t     inst,
                          uint32_t              cnt,
                          const mesa_port_map_t *port_map)
{
    mesa_rc         rc = MESA_RC_ERROR;
    vtss_port_map_t vtss_map[VTSS_PORTS];
    vtss_port_no_t  port_no;

    if (cnt > VTSS_PORTS) {
        return MESA_RC_ERROR;
    }

    rc = vtss_port_map_get((const vtss_inst_t)inst, vtss_map);
    if (rc != VTSS_RC_OK) {
        return rc;
    }

    for (port_no = 0; port_no < cnt; port_no++) {
        mesa_conv_mesa_port_map_t_to_vtss_port_map_t(&port_map[port_no], &vtss_map[port_no]);
    }
    return vtss_port_map_set((const vtss_inst_t)inst, vtss_map);
}

#ifndef VTSS_CHIP_10G_PHY
mesa_bool_t mesa_phy_10G_is_valid(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return FALSE;
}
#endif
