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

#if defined(VTSS_FEATURE_MACSEC)

#define RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }

mesa_rc mesa_macsec_port_inst_dump(const mesa_inst_t           inst,
                                   const mesa_port_no_t        port_no,
                                   uint32_t                    max,
                                   uint32_t                    *cnt,
                                   mesa_macsec_port_sc_data_t  *data) {
    uint32_t i = 0;
    vtss_macsec_inst_count_t vd = {};
    mesa_macsec_port_sc_data_t *d = data;

    *cnt = 0;

    RC(vtss_macsec_inst_count_get((const vtss_inst_t)inst, port_no, &vd));

    memset(data, 0, sizeof(*data) * max);

    for (uint32_t i_secy = 0; i_secy < vd.no_secy; ++i_secy) {
        mesa_macsec_vport_id_t vport = vd.secy_vport[i_secy];
        const vtss_secy_inst_count_t *v_secy = &vd.secy_inst_count[i_secy];

        // Check if the given SECY has a TX/SC, and check if we have space for
        // it
        if (v_secy->no_txsc == 1 && i < max) {
            d->valid = 1;
            d->port.port_no = port_no;
            d->port.port_id = vport;
            d->direction = MESA_MACSEC_DIRECTION_EGRESS;
            d->sc_id = v_secy->txsc_id;
            RC(mesa_conv_vtss_macsec_sci_t_to_mesa_macsec_sci_t(&v_secy->tx_sci, &d->sci));
            RC(mesa_conv_vtss_sc_inst_count_t_to_mesa_sc_inst_count_t(&v_secy->txsc_inst_count, &d->sa_ids));
            ++i, ++d;
        }

        for (uint32_t i_sc = 0; i_sc < v_secy->no_rxsc; ++i_sc) {
            if (i >= max) continue;

            d->valid = 1;
            d->port.port_no = port_no;
            d->port.port_id = vport;
            d->direction = MESA_MACSEC_DIRECTION_INGRESS;
            d->sc_id = v_secy->rxsc_id[i_sc];
            RC(mesa_conv_vtss_macsec_sci_t_to_mesa_macsec_sci_t(&v_secy->rx_sci[i_sc], &d->sci));
            RC(mesa_conv_vtss_sc_inst_count_t_to_mesa_sc_inst_count_t(&v_secy->rxsc_inst_count[i_sc], &d->sa_ids));
            ++i, ++d;
        }
    }

    *cnt = i;
    return MESA_RC_OK;
}

#else  // if defined(VTSS_FEATURE_MACSEC)

mesa_rc mesa_macsec_port_inst_dump(const mesa_inst_t           inst,
                                   const mesa_port_no_t        port_no,
                                   uint32_t                    max,
                                   uint32_t                    *cnt,
                                   mesa_macsec_port_sc_data_t  *data) {
    *cnt = 0;
    return MESA_RC_ERROR;
}

#endif  // if defined(VTSS_FEATURE_MACSEC)

