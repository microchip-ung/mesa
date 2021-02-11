// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT



#include <ctype.h>
#include <unistd.h>
#include <microchip/ethernet/board/api.h>
#include <microchip/ethernet/phy/api/phy.h>
#include "meba_generic.h"

/* Reset the PHY */
mepa_rc meba_phy_reset(meba_inst_t inst, mepa_port_no_t port_no,
                       const mepa_reset_param_t *rst_conf)
{
    mepa_device_t *phy_dev;

    T_I(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_reset) {
        return MESA_RC_NOT_IMPLEMENTED;
    }
    return phy_dev->drv->mepa_driver_reset(phy_dev, rst_conf);
}

/* Get the current status of the PHY. */
mepa_rc meba_phy_status_poll(meba_inst_t inst, mepa_port_no_t port_no,
                             mepa_driver_status_t *status)
{
    mepa_device_t *phy_dev;

    T_N(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_poll(phy_dev, status);
}

/* Set the configuration to the PHY. */
mepa_rc meba_phy_conf_set(meba_inst_t inst, mepa_port_no_t port_no,
                          const mepa_driver_conf_t *conf)

{
    mepa_device_t *phy_dev;
    meba_port_cap_t cap;
    meba_port_entry_t entry;
    mepa_driver_conf_t cf = *conf;

    T_D(inst, "Called");
    inst->api.meba_port_entry_get(inst, port_no, &entry);
    cap = entry.cap;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (conf->admin.enable) {
        if (conf->speed == MESA_SPEED_AUTO ||
            conf->speed == MESA_SPEED_1G) {
            memset(&cf.aneg, 0, sizeof(cf.aneg));

            /* Set Auto-negotiation parameters using board capability. */
            cf.aneg.speed_2g5_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_2_5G_FDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_2500M);
            cf.aneg.speed_5g_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_5G_FDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_5G);
            cf.aneg.speed_10g_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10G_FDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_10G);
            cf.aneg.speed_10m_hdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10M_HDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_HDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_10M);
            cf.aneg.speed_10m_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10M_FDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_FDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_10M);
            cf.aneg.speed_100m_hdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_100M_HDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_HDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_100M);
            cf.aneg.speed_100m_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_100M_FDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_FDX) &&
                !(conf->adv_dis & MEPA_ADV_DIS_100M);
            cf.aneg.speed_1g_fdx =
                ((cap & MEBA_PORT_CAP_1G_FDX) &&
                 !(conf->speed == MESA_SPEED_AUTO &&
                   conf->adv_dis & MEPA_ADV_DIS_1G));
            cf.aneg.no_restart_aneg =
                !!(conf->adv_dis & MEPA_ADV_DIS_RESTART_ANEG);
        }
    }

    return phy_dev->drv->mepa_driver_conf_set(phy_dev, &cf);
}

/* Get the PHY interface based on speed.*/
mepa_rc meba_phy_if_get(meba_inst_t inst, mepa_port_no_t port_no,
                        mepa_port_speed_t speed, mepa_port_interface_t *intf)

{
    mepa_device_t *phy_dev;

    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_if_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_if_get(phy_dev, speed, intf);
}

/* Sets the power mode.*/
mepa_rc meba_phy_power_set(meba_inst_t inst, mepa_port_no_t port_no,
                           mepa_power_mode_t power)

{
    mepa_device_t *phy_dev;

    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_power_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }
    return phy_dev->drv->mepa_driver_power_set(phy_dev, power);
}

/* Starts cable diagnostics.*/
mepa_rc meba_phy_cable_diag_start(meba_inst_t inst, mepa_port_no_t port_no, int mode)
{
    mepa_device_t *phy_dev;

    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_cable_diag_start) {
        return MESA_RC_NOT_IMPLEMENTED;
    }
    return phy_dev->drv->mepa_driver_cable_diag_start(phy_dev, mode);
}

/* Gets result of cable diagnostics.*/
mepa_rc meba_phy_cable_diag_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_cable_diag_result_t *result)

{
    mepa_device_t *phy_dev;

    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_cable_diag_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }
    return phy_dev->drv->mepa_driver_cable_diag_get(phy_dev, result);
}

/* Sets the media type in case the port is a dual media port with external phy. */
mepa_rc meba_phy_media_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_media_interface_t phy_media_if)
{
    mepa_device_t *phy_dev;

    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_media_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }
    return phy_dev->drv->mepa_driver_media_set(phy_dev, phy_media_if);
}

/* Gets Copper 1G PHY auto negotiation status. */
mepa_rc meba_phy_aneg_status_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_aneg_status_t *status)
{
    mepa_device_t *phy_dev;

    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_aneg_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_aneg_status_get(phy_dev, status);
}
