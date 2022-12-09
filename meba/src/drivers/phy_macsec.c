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

mepa_rc meba_phy_macsec_secy_conf_add(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf)
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

mepa_rc meba_macsec_rx_sc_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sc_counters_get(inst->phy_devices[port_no], port, sci, counters);
}

mepa_rc meba_macsec_tx_sc_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sc_counters_get(inst->phy_devices[port_no], port, counters);
}

mepa_rc meba_macsec_tx_sa_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_tx_sa_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_tx_sa_counters_get(inst->phy_devices[port_no], port, an, counters);
}

mepa_rc meba_macsec_rx_sa_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_rx_sa_counters_t *const counters)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_rx_sa_counters_get(inst->phy_devices[port_no], port, sci, an, counters);
}

mepa_rc meba_macsec_control_frame_match_conf_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_control_frame_match_conf_t *const conf, uint32_t *const rule_id)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_control_frame_match_conf_set(inst->phy_devices[port_no], port_no, conf, rule_id);
}

mepa_rc meba_macsec_control_frame_match_conf_del(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t rule_id)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_control_frame_match_conf_del(inst->phy_devices[port_no], port_no, rule_id);
}

mepa_rc meba_macsec_control_frame_match_conf_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_control_frame_match_conf_t *const conf, uint32_t rule_id)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_control_frame_match_conf_get(inst->phy_devices[port_no], port_no, conf, rule_id);
}

mepa_rc meba_macsec_pattern_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action, const mepa_macsec_match_pattern_t *const pattern)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_pattern_set(inst->phy_devices[port_no], port, direction, action, pattern);
}

mepa_rc meba_macsec_pattern_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_pattern_del(inst->phy_devices[port_no], port, direction, action);
}

mepa_rc meba_macsec_pattern_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action, mepa_macsec_match_pattern_t *const pattern)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_pattern_get(inst->phy_devices[port_no], port, direction, action, pattern);
}

mepa_rc meba_macsec_default_action_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_default_action_policy_t *const policy)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_default_action_set(inst->phy_devices[port_no], port_no, policy);
}

mepa_rc meba_macsec_default_action_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_default_action_policy_t *const policy)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_default_action_get(inst->phy_devices[port_no], port_no, policy);
}

mepa_rc meba_macsec_bypass_mode_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_bypass_mode_t *const bypass)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_bypass_mode_set(inst->phy_devices[port_no], port_no, bypass);
}

mepa_rc meba_macsec_bypass_mode_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_bypass_mode_t *const bypass)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_bypass_mode_get(inst->phy_devices[port_no], port_no, bypass);
}

mepa_rc meba_macsec_bypass_tag_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_tag_bypass_t tag)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_bypass_tag_set(inst->phy_devices[port_no], port, tag);
}

mepa_rc meba_macsec_bypass_tag_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tag_bypass_t *const tag)
{
    mesa_rc rc = MESA_RC_ERROR;

    if ((rc = meba_dev_chk(inst, port_no)) != MESA_RC_OK) {
        return rc;
    }

    return mepa_macsec_bypass_tag_get(inst->phy_devices[port_no], port, tag);
}
