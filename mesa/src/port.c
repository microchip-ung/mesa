/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

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
    mesa_rc         rc;
    vtss_port_map_t vtss_map[VTSS_PORTS];
    vtss_port_no_t  port_no;

    if (cnt != VTSS_PORTS) {
        return VTSS_RC_ERROR;
    }
    if ((rc = vtss_port_map_get((const vtss_inst_t)inst, vtss_map)) == VTSS_RC_OK) {
        for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
            mesa_conv_vtss_port_map_t_to_mesa_port_map_t(&vtss_map[port_no], &port_map[port_no]);
        }
    }
    return rc;
}

mesa_rc mesa_port_map_set(const mesa_inst_t     inst,
                          uint32_t              cnt,
                          const mesa_port_map_t *port_map)
{
    vtss_port_map_t vtss_map[VTSS_PORTS];
    vtss_port_no_t  port_no;

    if (cnt != VTSS_PORTS) {
        return VTSS_RC_ERROR;
    }
    for (port_no = 0; port_no < VTSS_PORTS; port_no++) {
        mesa_conv_mesa_port_map_t_to_vtss_port_map_t(&port_map[port_no], &vtss_map[port_no]);
    }
    return vtss_port_map_set((const vtss_inst_t)inst, vtss_map);
}

mesa_rc mesa_phy_patch_settings_get(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    const uint8_t        mcb_bus,
                                    uint8_t              *mcb_res,
                                    uint8_t              *cfg_buf,
                                    uint8_t              *stat_buf)
{
    *mcb_res = mcb_bus; // INOUT in VTSS API
    return vtss_phy_patch_settings_get((const vtss_inst_t)inst, port_no, mcb_res, cfg_buf, stat_buf);
}

#ifndef VTSS_CHIP_10G_PHY
mesa_bool_t mesa_phy_10G_is_valid(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return FALSE;
}
#endif
