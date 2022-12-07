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
