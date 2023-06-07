// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/board/api.h>
#include "meba_generic.h"

static mepa_rc meba_dev_chk(meba_inst_t inst, mepa_port_no_t port_no)
{
    mepa_device_t *phy_dev;
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return MESA_RC_OK;
}

mepa_rc meba_phy_macsec_init_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_init_t *const macsec_init)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_init_set(inst->phy_devices[port_no], macsec_init);
}

mepa_rc meba_phy_macsec_init_get(meba_inst_t inst,mepa_port_no_t port_no, mepa_macsec_init_t *const macsec_init)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_init_get(inst->phy_devices[port_no], macsec_init);
}

mepa_rc meba_phy_macsec_secy_conf_add(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_conf_add(inst->phy_devices[port_no], port, conf);
}

mepa_rc meba_phy_macsec_secy_conf_update(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_conf_update(inst->phy_devices[port_no], port, conf);
}

mepa_rc meba_phy_macsec_secy_conf_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_conf_get(inst->phy_devices[port_no], port, conf);
}

mepa_rc meba_phy_macsec_secy_conf_del(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_conf_del(inst->phy_devices[port_no], port);
}

mepa_rc meba_phy_macsec_secy_controlled_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, const mepa_bool_t enable)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_controlled_set(inst->phy_devices[port_no], port, enable);
}

mepa_rc meba_phy_macsec_secy_controlled_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_bool_t *const enable)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_controlled_get(inst->phy_devices[port_no], port, enable);
}

mepa_rc meba_phy_macsec_secy_port_status_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_macsec_secy_port_status_t *const status)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_port_status_get(inst->phy_devices[port_no], port, status);
}

mepa_rc meba_phy_macsec_port_get_next(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t *const search_macsec_port, mepa_macsec_port_t *const found_macsec_port)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_port_get_next(inst->phy_devices[port_no], port_no, search_macsec_port, found_macsec_port);
}

mepa_rc meba_phy_macsec_rx_sc_add(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sc_add(inst->phy_devices[port_no], port, sci);
}

mepa_rc meba_phy_macsec_rx_sc_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const mepa_macsec_rx_sc_conf_t *const conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sc_update(inst->phy_devices[port_no], port, sci, conf);
}

mepa_rc meba_phy_macsec_rx_sc_get_conf(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_conf_t *const conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sc_get_conf(inst->phy_devices[port_no], port, sci, conf);
}

mepa_rc meba_phy_macsec_rx_sc_get_next(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const search_sci, mepa_macsec_sci_t *const found_sci)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sc_get_next(inst->phy_devices[port_no], port, search_sci, found_sci);
}

mepa_rc meba_phy_macsec_rx_sc_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sc_del(inst->phy_devices[port_no], port, sci);
}

mepa_rc meba_phy_macsec_rx_sc_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_status_t *const status)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sc_status_get(inst->phy_devices[port_no], port, sci, status);
}

mepa_rc meba_phy_macsec_tx_sc_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sc_set(inst->phy_devices[port_no], port);
}

mepa_rc meba_phy_macsec_tx_sc_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_tx_sc_conf_t *const conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sc_update(inst->phy_devices[port_no], port, conf);
}

mepa_rc meba_phy_macsec_tx_sc_get_conf(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_conf_t *const conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sc_get_conf(inst->phy_devices[port_no], port, conf);
}

mepa_rc meba_phy_macsec_tx_sc_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sc_del(inst->phy_devices[port_no], port);
}

mepa_rc meba_phy_macsec_tx_sc_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_status_t *const status)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sc_status_get(inst->phy_devices[port_no], port, status);
}

mepa_rc meba_phy_macsec_rx_sa_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn, const mepa_macsec_sak_t *const sak)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_set(inst->phy_devices[port_no], port, sci, an, lowest_pn, sak);
}

mepa_rc meba_phy_macsec_rx_sa_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, uint32_t *const lowest_pn, mepa_macsec_sak_t *const sak, mepa_bool_t *const active)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_get(inst->phy_devices[port_no], port, sci, an, lowest_pn, sak, active);
}

mepa_rc meba_phy_macsec_rx_sa_activate(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_activate(inst->phy_devices[port_no], port, sci, an);
}

mepa_rc meba_phy_macsec_rx_sa_disable(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_disable(inst->phy_devices[port_no], port, sci, an);
}

mepa_rc meba_phy_macsec_rx_sa_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_del(inst->phy_devices[port_no], port, sci, an);
}

mepa_rc meba_phy_macsec_rx_sa_lowest_pn_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_lowest_pn_update(inst->phy_devices[port_no], port, sci, an, lowest_pn);
}

mepa_rc meba_phy_macsec_rx_sa_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_rx_sa_status_t *const status)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_status_get(inst->phy_devices[port_no], port, sci, an, status);
}

mepa_rc meba_phy_macsec_rx_seca_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const mepa_macsec_pkt_num_t lowest_pn, const mepa_macsec_sak_t *const sak, const mepa_macsec_ssci_t *const ssci)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_seca_set(inst->phy_devices[port_no], port, sci, an, lowest_pn, sak, ssci);
}

mepa_rc meba_phy_macsec_rx_seca_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_pkt_num_t *const lowest_pn, mepa_macsec_sak_t *const sak, mepa_bool_t *const active, mepa_macsec_ssci_t *const ssci)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_seca_get(inst->phy_devices[port_no], port, sci, an, lowest_pn, sak, active, ssci);
}

mepa_rc meba_phy_macsec_rx_seca_lowest_pn_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const mepa_macsec_pkt_num_t lowest_pn)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_seca_lowest_pn_update(inst->phy_devices[port_no], port, sci, an, lowest_pn);
}

mepa_rc meba_phy_macsec_tx_sa_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, const uint32_t next_pn, const mepa_bool_t confidentiality, const mepa_macsec_sak_t *const sak)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sa_set(inst->phy_devices[port_no], port, an, next_pn, confidentiality, sak);
}

mepa_rc meba_phy_macsec_tx_sa_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, uint32_t *const next_pn, mepa_bool_t *const confidentiality, mepa_macsec_sak_t *const sak, mepa_bool_t *const active)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sa_get(inst->phy_devices[port_no], port, an, next_pn, confidentiality, sak, active);
}

mepa_rc meba_phy_macsec_tx_sa_activate(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sa_activate(inst->phy_devices[port_no], port, an);
}

mepa_rc meba_phy_macsec_tx_sa_disable(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sa_disable(inst->phy_devices[port_no], port, an);
}

mepa_rc meba_phy_macsec_tx_sa_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sa_del(inst->phy_devices[port_no], port, an);
}

mepa_rc meba_phy_macsec_tx_sa_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_tx_sa_status_t *const status)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sa_status_get(inst->phy_devices[port_no], port, an, status);
}

mepa_rc meba_phy_macsec_tx_seca_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, const mepa_macsec_pkt_num_t next_pn, const mepa_bool_t confidentiality, const mepa_macsec_sak_t *const sak, const mepa_macsec_ssci_t *const ssci)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_seca_set(inst->phy_devices[port_no], port, an, next_pn, confidentiality, sak, ssci);
}

mepa_rc meba_phy_macsec_tx_seca_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_pkt_num_t *const next_pn, mepa_bool_t *const confidentiality, mepa_macsec_sak_t *const sak, mepa_bool_t *const active, mepa_macsec_ssci_t *const ssci)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_seca_get(inst->phy_devices[port_no], port, an, next_pn, confidentiality, sak, active, ssci);
}

mepa_rc meba_phy_macsec_controlled_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_secy_port_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_controlled_counters_get(inst->phy_devices[port_no], port, counters);
}

mepa_rc meba_phy_macsec_uncontrolled_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_uncontrolled_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_uncontrolled_counters_get(inst->phy_devices[port_no], port_no, counters);
}

mepa_rc meba_phy_macsec_common_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_common_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_common_counters_get(inst->phy_devices[port_no], port_no, counters);
}

mepa_rc meba_phy_macsec_secy_cap_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_secy_cap_t *const cap)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_cap_get(inst->phy_devices[port_no], port_no, cap);
}

mepa_rc meba_phy_macsec_secy_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_secy_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_counters_get(inst->phy_devices[port_no], port, counters);
}

mepa_rc meba_phy_macsec_counters_update(meba_inst_t inst, const mepa_port_no_t port_no)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_counters_update(inst->phy_devices[port_no], port_no);
}

mepa_rc meba_phy_macsec_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_counters_clear(inst->phy_devices[port_no], port_no);
}

mepa_rc meba_phy_macsec_rx_sc_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sc_counters_get(inst->phy_devices[port_no], port, sci, counters);
}

mepa_rc meba_phy_macsec_tx_sc_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sc_counters_get(inst->phy_devices[port_no], port, counters);
}

mepa_rc meba_phy_macsec_tx_sa_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_tx_sa_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sa_counters_get(inst->phy_devices[port_no], port, an, counters);
}

mepa_rc meba_phy_macsec_rx_sa_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_rx_sa_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_counters_get(inst->phy_devices[port_no], port, sci, an, counters);
}

mepa_rc meba_phy_macsec_control_frame_match_conf_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_control_frame_match_conf_t *const conf, uint32_t *const rule_id)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_control_frame_match_conf_set(inst->phy_devices[port_no], port_no, conf, rule_id);
}

mepa_rc meba_phy_macsec_control_frame_match_conf_del(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t rule_id)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_control_frame_match_conf_del(inst->phy_devices[port_no], port_no, rule_id);
}

mepa_rc meba_phy_macsec_control_frame_match_conf_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_control_frame_match_conf_t *const conf, uint32_t rule_id)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_control_frame_match_conf_get(inst->phy_devices[port_no], port_no, conf, rule_id);
}

mepa_rc meba_phy_macsec_pattern_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action, const mepa_macsec_match_pattern_t *const pattern)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_pattern_set(inst->phy_devices[port_no], port, direction, action, pattern);
}

mepa_rc meba_phy_macsec_pattern_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_pattern_del(inst->phy_devices[port_no], port, direction, action);
}

mepa_rc meba_phy_macsec_pattern_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action, mepa_macsec_match_pattern_t *const pattern)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_pattern_get(inst->phy_devices[port_no], port, direction, action, pattern);
}

mepa_rc meba_phy_macsec_default_action_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_default_action_policy_t *const policy)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_default_action_set(inst->phy_devices[port_no], port_no, policy);
}

mepa_rc meba_phy_macsec_default_action_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_default_action_policy_t *const policy)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_default_action_get(inst->phy_devices[port_no], port_no, policy);
}

mepa_rc meba_phy_macsec_bypass_mode_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_bypass_mode_t *const bypass)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_bypass_mode_set(inst->phy_devices[port_no], port_no, bypass);
}

mepa_rc meba_phy_macsec_bypass_mode_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_bypass_mode_t *const bypass)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_bypass_mode_get(inst->phy_devices[port_no], port_no, bypass);
}

mepa_rc meba_phy_macsec_bypass_tag_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_tag_bypass_t tag)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_bypass_tag_set(inst->phy_devices[port_no], port, tag);
}

mepa_rc meba_phy_macsec_bypass_tag_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tag_bypass_t *const tag)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_bypass_tag_get(inst->phy_devices[port_no], port, tag);
}


mepa_rc meba_phy_macsec_mtu_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_mtu_t *const mtu_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_mtu_set(inst->phy_devices[port_no], port_no, mtu_conf);
}

mepa_rc meba_phy_macsec_mtu_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_mtu_t *mtu_conf)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_mtu_get(inst->phy_devices[port_no], port_no, mtu_conf);
}

mepa_rc meba_phy_macsec_frame_capture_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_frame_capture_t capture)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_frame_capture_set(inst->phy_devices[port_no], port_no, capture);
}

mepa_rc meba_phy_macsec_frame_get(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t buf_length, uint32_t *const return_length, uint8_t *const frame)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_frame_get(inst->phy_devices[port_no], port_no, buf_length, return_length, frame);
}

mepa_rc meba_phy_macsec_event_enable_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_event_t ev_mask, const mepa_bool_t enable)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_event_enable_set(inst->phy_devices[port_no], port_no, ev_mask, enable);
}

mepa_rc meba_phy_macsec_event_enable_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_event_t *const ev_mask)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_event_enable_get(inst->phy_devices[port_no], port_no, ev_mask);
}

mepa_rc meba_phy_macsec_event_poll(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_event_t *const ev_mask)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_event_poll(inst->phy_devices[port_no], port_no, ev_mask);
}

mepa_rc meba_phy_macsec_event_seq_threshold_set(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t threshold)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_event_seq_threshold_set(inst->phy_devices[port_no], port_no, threshold);
}

mepa_rc meba_phy_macsec_event_seq_threshold_get(meba_inst_t inst, const mepa_port_no_t port_no, uint32_t *const threshold)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_event_seq_threshold_get(inst->phy_devices[port_no], port_no, threshold);
}

mepa_rc meba_phy_macsec_egr_intr_sa_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_port_t *const port, uint16_t *const an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_egr_intr_sa_get(inst->phy_devices[port_no], port_no, port, an);
}

mepa_rc meba_phy_macsec_csr_read(meba_inst_t inst, const mepa_port_no_t port_no, const uint16_t mmd, const uint32_t addr, uint32_t *const value)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_csr_read(inst->phy_devices[port_no], port_no, mmd, addr, value);
}

mepa_rc meba_phy_macsec_csr_write(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t mmd, const uint32_t addr, const uint32_t value)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_csr_write(inst->phy_devices[port_no], port_no, mmd, addr, value);
}

mepa_rc meba_phy_macsec_dbg_counter_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_rc_dbg_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_dbg_counter_get(inst->phy_devices[port_no], port_no, counters);
}

mepa_rc meba_phy_macsec_hmac_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_mac_counters_t *const counters, const mepa_bool_t clear)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_hmac_counters_get(inst->phy_devices[port_no], port_no, counters, clear);
}

mepa_rc meba_phy_macsec_lmac_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_mac_counters_t *const counters, const mepa_bool_t clear)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_lmac_counters_get(inst->phy_devices[port_no], port_no, counters, clear);
}

mepa_rc meba_phy_macsec_is_capable(meba_inst_t inst, const mepa_port_no_t port_no, mepa_bool_t *capable)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_is_capable(inst->phy_devices[port_no], port_no, capable);
}

mepa_rc meba_phy_macsec_dbg_reg_dump(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_debug_print_t pr)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_dbg_reg_dump(inst->phy_devices[port_no], port_no, pr);
}

mepa_rc meba_phy_macsec_inst_count_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_inst_count_t *count)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_inst_count_get(inst->phy_devices[port_no], port_no, count);
}

mepa_rc meba_phy_macsec_lmac_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_lmac_counters_clear(inst->phy_devices[port_no], port_no);
}

mepa_rc meba_phy_macsec_hmac_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_hmac_counters_clear(inst->phy_devices[port_no], port_no);
}

mepa_rc meba_phy_macsec_debug_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_debug_counters_clear(inst->phy_devices[port_no], port_no);
}

mepa_rc meba_phy_macsec_common_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_common_counters_clear(inst->phy_devices[port_no], port_no);
}

mepa_rc meba_phy_macsec_uncontrolled_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_uncontrolled_counters_clear(inst->phy_devices[port_no], port_no);
}

mepa_rc meba_phy_macsec_controlled_counters_clear (meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_controlled_counters_clear(inst->phy_devices[port_no], port);
}

mepa_rc meba_phy_macsec_rxsa_counters_clear(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rxsa_counters_clear(inst->phy_devices[port_no], port, sci, an);
}

mepa_rc meba_phy_macsec_rxsc_counters_clear(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t  *const sci)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rxsc_counters_clear(inst->phy_devices[port_no], port, sci);
}

mepa_rc meba_phy_macsec_txsa_counters_clear(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t  port, const uint16_t  an)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_txsa_counters_clear(inst->phy_devices[port_no], port, an);
}

mepa_rc meba_phy_macsec_txsc_counters_clear (meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_txsc_counters_clear(inst->phy_devices[port_no], port);
}

mepa_rc meba_phy_macsec_secy_counters_clear (meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_secy_counters_clear(inst->phy_devices[port_no], port);
}

mepa_rc meba_phy_macsec_port_enable_status_get (meba_inst_t inst, const mepa_port_no_t port_no, mepa_bool_t *status)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_port_enable_status_get(inst->phy_devices[port_no], port_no, status);
}

mepa_rc meba_phy_macsec_rxsa_an_status_get (meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_bool_t *status)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rxsa_an_status_get(inst->phy_devices[port_no], port, sci, an, status);
}

mepa_rc meba_phy_mac_block_mtu_get(meba_inst_t inst, const mepa_port_no_t port_no, uint16_t *const mtu_value, mepa_bool_t *const mtu_tag_check)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_mac_block_mtu_get(inst->phy_devices[port_no], port_no, mtu_value, mtu_tag_check);
}

mepa_rc meba_phy_mac_block_mtu_set(meba_inst_t inst, const mepa_port_no_t port_no, const uint16_t mtu_value, const mepa_bool_t mtu_tag_check)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_mac_block_mtu_set(inst->phy_devices[port_no], port_no, mtu_value, mtu_tag_check);
}

mepa_rc meba_phy_macsec_fcbuf_frame_gap_comp_set(meba_inst_t inst, const mepa_port_no_t port_no, const uint8_t frm_gap)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_fcbuf_frame_gap_comp_set(inst->phy_devices[port_no], port_no, frm_gap);
}

mepa_rc meba_phy_macsec_dbg_fcb_block_reg_dump(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_debug_print_t pr)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_dbg_fcb_block_reg_dump(inst->phy_devices[port_no], port_no, pr);
}

mepa_rc meba_phy_macsec_dbg_frm_match_handling_ctrl_reg_dump(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_debug_print_t pr)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_dbg_frm_match_handling_ctrl_reg_dump(inst->phy_devices[port_no], port_no, pr);
}

#ifdef MEPA_MACSEC_FIFO_OVERFLOW_WORKAROUND
mepa_rc meba_phy_macsec_dbg_reconfig(meba_inst_t inst, const mepa_port_no_t port_no)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_dbg_reconfig(inst->phy_devices[port_no], port_no);
}
#endif

mepa_rc meba_phy_macsec_dbg_update_seq_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, uint16_t an, mepa_bool_t egr, mepa_bool_t disable)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_dbg_update_seq_set(inst->phy_devices[port_no], port, sci, an, egr, disable);
}
