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

    T_N(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if(!phy_dev || !phy_dev->drv->mepa_driver_poll) {
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

    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if(!phy_dev || !phy_dev->drv->mepa_driver_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (cf.admin.enable) {
        if (cf.speed == MESA_SPEED_AUTO || cf.speed == MESA_SPEED_1G) {
            memset(&cf.aneg, 0, sizeof(cf.aneg));

            if (cf.speed == MESA_SPEED_1G) {
                cf.adv_dis |= MEPA_ADV_DIS_10M;
                cf.adv_dis |= MEPA_ADV_DIS_100M;
                cf.adv_dis |= MEPA_ADV_DIS_HDX;
            }

            /* Set Auto-negotiation parameters using board capability. */
            cf.aneg.speed_2g5_fdx =
                (cap & MEBA_PORT_CAP_2_5G_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_2500M);
            cf.aneg.speed_5g_fdx =
                (cap & MEBA_PORT_CAP_5G_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_5G);
            cf.aneg.speed_10g_fdx =
                (cap & MEBA_PORT_CAP_10G_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_10G);
            cf.aneg.speed_10m_hdx =
                (cap & MEBA_PORT_CAP_10M_HDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_HDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_10M);
            cf.aneg.speed_10m_fdx =
                (cap & MEBA_PORT_CAP_10M_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_10M);
            cf.aneg.speed_100m_hdx =
                (cap & MEBA_PORT_CAP_100M_HDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_HDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_100M);
            cf.aneg.speed_100m_fdx =
                (cap & MEBA_PORT_CAP_100M_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_100M);
            cf.aneg.speed_1g_fdx =
                ((cap & MEBA_PORT_CAP_1G_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_1G));
            cf.aneg.no_restart_aneg =
                   !!(cf.adv_dis & MEPA_ADV_DIS_RESTART_ANEG);
        }
    }

    return phy_dev->drv->mepa_driver_conf_set(phy_dev, &cf);
}

// Get the current phy port configuration
mepa_rc meba_phy_conf_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_driver_conf_t *const  conf)
{
    mepa_device_t *phy_dev;

    T_I(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if(!phy_dev || !phy_dev->drv->mepa_driver_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_conf_get(phy_dev, conf);
}

/* Get the PHY interface based on speed.*/
mepa_rc meba_phy_if_get(meba_inst_t inst, mepa_port_no_t port_no,
                        mepa_port_speed_t speed, mepa_port_interface_t *intf)

{
    mepa_device_t *phy_dev;

    T_I(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if(!phy_dev || !phy_dev->drv->mepa_driver_if_get) {
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
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if(!phy_dev || !phy_dev->drv->mepa_driver_power_set) {
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

// Debug register read function using clause 22 access
mepa_rc meba_phy_clause22_read(meba_inst_t inst, mepa_port_no_t port_no, uint32_t address, uint16_t *const value)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_clause22_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_clause22_read(phy_dev, address, value);
}

// Debug register write function using clause 22 access
mepa_rc meba_phy_clause22_write(meba_inst_t inst, mepa_port_no_t port_no, uint32_t address, uint16_t value)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_clause22_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_clause22_write(phy_dev, address, value);
}

// Debug register read function using clause 45 access
mepa_rc meba_phy_clause45_read(meba_inst_t inst, mepa_port_no_t port_no, uint32_t address, uint16_t *const value)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_clause45_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_clause45_read(phy_dev, address, value);
}

// Debug register write function using clause 45 access
mepa_rc meba_phy_clause45_write(meba_inst_t inst, mepa_port_no_t port_no, uint32_t address, uint16_t value)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_clause45_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_clause45_write(phy_dev, address, value);
}

// Enable/Disable events in phy
mepa_rc meba_phy_event_enable_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_event_t event, mesa_bool_t enable)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_event_enable_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_event_enable_set(phy_dev, event, enable);
}

// Get the events enabled currently in PHY
mepa_rc meba_phy_event_enable_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_event_t *const event)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_event_enable_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_event_enable_get(phy_dev, event);
}
// Obtain the phy event status
mepa_rc meba_phy_event_poll(meba_inst_t inst, mepa_port_no_t port_no, mepa_event_t *const event)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_event_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_event_poll(phy_dev, event);
}
// Apply loopback configuration. Used for debugging.
mepa_rc meba_phy_loopback_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_loopback_t *loopback)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_loopback_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_loopback_set(phy_dev, loopback);
}
// Obtain the current loopback configuration.
mepa_rc meba_phy_loopback_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_loopback_t *const loopback)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_loopback_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_loopback_get(phy_dev, loopback);
}

// Set the phy gpio mode.
mepa_rc meba_phy_gpio_mode_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_gpio_conf_t *gpio_conf)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_gpio_mode_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_gpio_mode_set(phy_dev, gpio_conf);
}
// Set the phy gpio pin data value.
mepa_rc meba_phy_gpio_out_set(meba_inst_t inst, mepa_port_no_t port_no, uint8_t gpio_no, mepa_bool_t enable)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_gpio_out_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_gpio_out_set(phy_dev, gpio_no, enable);
}
// Get the phy gpio pin data value.
mepa_rc meba_phy_gpio_in_get(meba_inst_t inst, mepa_port_no_t port_no, uint8_t gpio_no, mepa_bool_t *const enable)
{
    mepa_device_t *phy_dev;

    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    phy_dev = inst->phy_devices[port_no];
    if (!phy_dev || !phy_dev->drv->mepa_driver_gpio_in_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return phy_dev->drv->mepa_driver_gpio_in_get(phy_dev, gpio_no, enable);
}
