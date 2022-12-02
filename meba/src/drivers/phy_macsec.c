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
