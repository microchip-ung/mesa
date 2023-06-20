// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <ctype.h>
#include <unistd.h>
#include <microchip/ethernet/board/api.h>
#include <microchip/ethernet/phy/api/phy.h>
#include <vtss_phy_api.h>
#include "meba_generic.h"

/* Reset the PHY */
mepa_rc meba_phy_reset(meba_inst_t inst, mepa_port_no_t port_no,
                       const mepa_reset_param_t *rst_conf)
{
    T_I(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    return mepa_reset(inst->phy_devices[port_no], rst_conf);
}

/* Get the current status of the PHY. */
mepa_rc meba_phy_status_poll(meba_inst_t inst, mepa_port_no_t port_no,
                             mepa_status_t *status)
{
    T_N(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    return mepa_poll(inst->phy_devices[port_no], status);
}

/* Set the configuration to the PHY. */
mepa_rc meba_phy_conf_set(meba_inst_t inst, mepa_port_no_t port_no,
                          const mepa_conf_t *conf)

{
    meba_port_cap_t cap;
    meba_port_entry_t entry;
    mepa_conf_t cf = *conf;

    T_D(inst, "Called");
    inst->api.meba_port_entry_get(inst, port_no, &entry);
    cap = entry.cap;

    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    if (cf.admin.enable) {
        if (cf.speed == MESA_SPEED_AUTO || cf.speed == MESA_SPEED_1G) {
            memset(&cf.aneg, 0, sizeof(cf.aneg));

            /* Set Auto-negotiation parameters using board capability. */
            cf.aneg.speed_2g5_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_2_5G_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_2500M);
            cf.aneg.speed_5g_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_5G_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_5G);
            cf.aneg.speed_10g_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10G_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_10G);
            cf.aneg.speed_10m_hdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10M_HDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_HDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_10M);
            cf.aneg.speed_10m_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10M_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_10M);
            cf.aneg.speed_100m_hdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_100M_HDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_HDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_100M);
            cf.aneg.speed_100m_fdx =
                conf->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_100M_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_FDX) &&
                !(cf.adv_dis & MEPA_ADV_DIS_100M);
            cf.aneg.speed_1g_fdx =
                ((cap & MEBA_PORT_CAP_1G_FDX) &&
                !(conf->speed == MESA_SPEED_AUTO &&
                  conf->adv_dis & MEPA_ADV_DIS_1G));
            cf.aneg.no_restart_aneg =
                   !!(cf.adv_dis & MEPA_ADV_DIS_RESTART_ANEG);
        }
    }

    return mepa_conf_set(inst->phy_devices[port_no], &cf);
}

// Get the current phy port configuration
mepa_rc meba_phy_conf_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_conf_t *const  conf)
{
    T_I(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    return mepa_conf_get(inst->phy_devices[port_no], conf);
}

/* Get the PHY interface based on speed.*/
mepa_rc meba_phy_if_get(meba_inst_t inst, mepa_port_no_t port_no,
                        mepa_port_speed_t speed, mepa_port_interface_t *intf)

{
    T_I(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    return mepa_if_get(inst->phy_devices[port_no], speed, intf);
}

/* I2C Read & Write */
mepa_rc meba_phy_i2c_read(meba_inst_t inst, mepa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr,
                          const uint8_t i2c_dev_addr, const mepa_bool_t word_access, uint8_t cnt, uint8_t  *const value)
{
    T_I(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    return mepa_i2c_read(inst->phy_devices[port_no], i2c_mux, i2c_reg_addr, i2c_dev_addr, word_access, cnt, value);
}

mepa_rc meba_phy_i2c_write(meba_inst_t inst, mepa_port_no_t port_no,const uint8_t i2c_mux, const uint8_t i2c_reg_addr,
                           const uint8_t i2c_dev_addr, const mepa_bool_t word_access, uint8_t cnt, const uint8_t *const value)
{
    T_I(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    return mepa_i2c_write(inst->phy_devices[port_no], i2c_mux, i2c_reg_addr, i2c_dev_addr, word_access, cnt, value);
}

/* I2C Clock select */
mepa_rc meba_phy_i2c_clock_select(meba_inst_t inst, mepa_port_no_t port_no, const mepa_i2c_clk_select_t *clk_value)
{

    T_I(inst, "Called port %d", port_no);
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }

    return mepa_i2c_clock_select(inst->phy_devices[port_no], clk_value);
}

/* Sets the power mode.*/
mepa_rc meba_phy_power_set(meba_inst_t inst, mepa_port_no_t port_no,
                           mepa_power_mode_t power)

{
    T_D(inst, "Called");
    if((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_power_set(inst->phy_devices[port_no], power);
}

/* Starts cable diagnostics.*/
mepa_rc meba_phy_cable_diag_start(meba_inst_t inst, mepa_port_no_t port_no, int mode)
{
    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_cable_diag_start(inst->phy_devices[port_no], mode);
}

/* Gets result of cable diagnostics.*/
mepa_rc meba_phy_cable_diag_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_cable_diag_result_t *result)

{
    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_cable_diag_get(inst->phy_devices[port_no], result);
}

/* Sets the media type in case the port is a dual media port with external phy. */
mepa_rc meba_phy_media_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_media_interface_t phy_media_if)
{
    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_media_set(inst->phy_devices[port_no], phy_media_if);
}

/* Gets Copper 1G PHY auto negotiation status. */
mepa_rc meba_phy_aneg_status_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_aneg_status_t *status)
{
    T_D(inst, "Called");
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt))  {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_aneg_status_get(inst->phy_devices[port_no], status);
}

// Debug register read function using clause 22 access
mepa_rc meba_phy_clause22_read(meba_inst_t inst, mepa_port_no_t port_no, uint32_t address, uint16_t *const value)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_clause22_read(inst->phy_devices[port_no], address, value);
}

// Debug register write function using clause 22 access
mepa_rc meba_phy_clause22_write(meba_inst_t inst, mepa_port_no_t port_no, uint32_t address, uint16_t value)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_clause22_write(inst->phy_devices[port_no], address, value);
}

// Debug register read function using clause 45 access
mepa_rc meba_phy_clause45_read(meba_inst_t inst, mepa_port_no_t port_no, uint32_t address, uint16_t *const value)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_clause45_read(inst->phy_devices[port_no], address, value);
}

// Debug register write function using clause 45 access
mepa_rc meba_phy_clause45_write(meba_inst_t inst, mepa_port_no_t port_no, uint32_t address, uint16_t value)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_clause45_write(inst->phy_devices[port_no], address, value);
}

// Enable/Disable events in phy
mepa_rc meba_phy_event_enable_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_event_t event, mesa_bool_t enable)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_event_enable_set(inst->phy_devices[port_no], event, enable);
}

// Get the events enabled currently in PHY
mepa_rc meba_phy_event_enable_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_event_t *const event)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_event_enable_get(inst->phy_devices[port_no], event);
}
// Obtain the phy event status
mepa_rc meba_phy_event_poll(meba_inst_t inst, mepa_port_no_t port_no, mepa_event_t *const event)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_event_poll(inst->phy_devices[port_no], event);
}
// Apply loopback configuration. Used for debugging.
mepa_rc meba_phy_loopback_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_loopback_t *loopback)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_loopback_set(inst->phy_devices[port_no], loopback);
}
// Obtain the current loopback configuration.
mepa_rc meba_phy_loopback_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_loopback_t *const loopback)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_loopback_get(inst->phy_devices[port_no], loopback);
}

// Set the phy gpio mode.
mepa_rc meba_phy_gpio_mode_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_gpio_conf_t *gpio_conf)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_gpio_mode_set(inst->phy_devices[port_no], gpio_conf);
}
// Set the phy gpio pin data value.
mepa_rc meba_phy_gpio_out_set(meba_inst_t inst, mepa_port_no_t port_no, uint8_t gpio_no, mepa_bool_t enable)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_gpio_out_set(inst->phy_devices[port_no], gpio_no, enable);
}
// Get the phy gpio pin data value.
mepa_rc meba_phy_gpio_in_get(meba_inst_t inst, mepa_port_no_t port_no, uint8_t gpio_no, mepa_bool_t *const enable)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_gpio_in_get(inst->phy_devices[port_no], gpio_no, enable);
}

// Set the phy recovered clock configuration
mepa_rc meba_phy_synce_clock_conf_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_synce_clock_conf_t *conf)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_synce_clock_conf_set(inst->phy_devices[port_no], conf);
}

#define MESA_RC(expr) { mesa_rc rc = expr; if (rc != MESA_RC_OK) { return rc; } }

mepa_rc meba_port_status_get(meba_inst_t inst, mepa_port_no_t port_no, mesa_port_status_t *const status)
{
    mesa_port_conf_t      conf;
    mepa_status_t         status_mepa;
    vtss_phy_10g_id_t     id;
    vtss_phy_10g_mode_t   mode;
    vtss_phy_10g_status_t status_10g;
    meba_port_entry_t     entry;

    // Intel/ML driver uses the old link-status
    status_mepa.link = status->link;

    MESA_RC(mesa_port_conf_get(NULL, port_no, &conf));
    switch (conf.if_type) {
    case MESA_PORT_INTERFACE_SERDES:
    case MESA_PORT_INTERFACE_XAUI:
    case MESA_PORT_INTERFACE_SFI:
    case MESA_PORT_INTERFACE_QXGMII:
    case MESA_PORT_INTERFACE_SGMII_CISCO:
        // For certain interface types, switch and 10G PHY status are combined
        break;
    default:
        // Poll the PHY driver by default
        if (meba_phy_status_poll(inst, port_no, &status_mepa) == MESA_RC_OK) {
            status->link = status_mepa.link;
            status->speed = status_mepa.speed;
            status->fdx = status_mepa.fdx;
            status->aneg = status_mepa.aneg;
            status->copper = status_mepa.copper;
            status->fiber = status_mepa.fiber;
            return MESA_RC_OK;
        }
        break;
    }

    // Get switch status by default
    MESA_RC(mesa_port_status_get(NULL, port_no, status));

    // Check that it is Venice/Malibu
    if (inst->api.meba_port_entry_get(inst, port_no, &entry) != MESA_RC_OK ||
        (entry.cap & MEBA_PORT_CAP_VTSS_10G_PHY) == 0 ||
        vtss_phy_10g_id_get(NULL, port_no, &id) != MESA_RC_OK ||
        (id.family != VTSS_PHY_FAMILY_VENICE && id.family != VTSS_PHY_FAMILY_MALIBU)) {
        return MESA_RC_OK;
    }

    // If the 10G PHY is in 1G mode, combine with 10G PHY clause 37 status
    if (conf.if_type != MESA_PORT_INTERFACE_XAUI &&
        vtss_phy_10g_mode_get(NULL, port_no, &mode) == MESA_RC_OK &&
        mode.oper_mode == VTSS_PHY_1G_MODE) {
        vtss_phy_10g_clause_37_cmn_status_t c37_status;
        vtss_phy_10g_clause_37_status_t     *line = &c37_status.line;
        vtss_phy_10g_clause_37_status_t     *host = &c37_status.host;
        vtss_phy_10g_clause_37_control_t    c37_ctrl;
        vtss_phy_10g_clause_37_adv_t        *adv = &c37_ctrl.advertisement;
        vtss_phy_10g_clause_37_adv_t        *lp = &line->autoneg.partner_advertisement;

        MESA_RC(vtss_phy_10g_clause_37_status_get(NULL, port_no, &c37_status));
        if (host->link == 0 || line->link == 0) {
            // Link has been down, get current status
            MESA_RC(vtss_phy_10g_clause_37_status_get(NULL, port_no, &c37_status));
            status->link_down = 1;
        }
        if (host->link == 0 || line->link == 0) {
            // Link is down
            status->link = 0;
            return MESA_RC_OK;
        }

        MESA_RC(vtss_phy_10g_clause_37_control_get(NULL, port_no, &c37_ctrl));
        if (c37_ctrl.enable) {
            // Auto-negotiation enabled
            if (host->autoneg.complete && line->autoneg.complete && adv->fdx && lp->fdx) {
                // Auto negotiation completed for FDX, return flow control result
                status->aneg.obey_pause =
                    (adv->symmetric_pause &&
                     (lp->symmetric_pause ||
                      (adv->asymmetric_pause && lp->asymmetric_pause)) ? 1 : 0);
                status->aneg.generate_pause =
                    (lp->symmetric_pause &&
                     (adv->symmetric_pause ||
                      (adv->asymmetric_pause && lp->asymmetric_pause)) ? 1 : 0);

                // Remote fault
                if (lp->remote_fault != VTSS_PHY_10G_CLAUSE_37_RF_LINK_OK)
                    status->remote_fault = 1;
            } else {
                // Auto-negotiation failed
                status->link = 0;
            }
        }
    }

    // If the host MAC in the 10G PHY is enabled, combine with 10G PHY status
    if (vtss_phy_10g_status_get(NULL, port_no, &status_10g) == MESA_RC_OK &&
        status_10g.status == 0) {
        status->link = 0;
    }

    return MESA_RC_OK;
}

mepa_rc meba_port_test_conf_set(meba_inst_t inst, mepa_port_no_t port_no, const mesa_port_test_conf_t *const conf)
{
    mepa_loopback_t lb = {};

    switch (conf->loopback) {
    case MESA_PORT_LB_NEAR_END:
        lb.near_end_ena = 1;
        break;
    case MESA_PORT_LB_FAR_END:
        lb.far_end_ena = 1;
        break;
    case MESA_PORT_LB_FACILITY:
        lb.mac_serdes_facility_ena = 1;
        break;
    case MESA_PORT_LB_EQUIPMENT:
        lb.mac_serdes_equip_ena = 1;
        break;
    default:
        break;
    }
    (void)meba_phy_loopback_set(inst, port_no, &lb);
    return mesa_port_test_conf_set(NULL, port_no, conf);
}

mepa_rc meba_phy_debug_info_print(const meba_inst_t         inst,
                                  const mesa_debug_printf_t pr,
                                  const mesa_debug_info_t   *const info)
{
    mepa_debug_info_t mepa_dbg;
    mepa_port_no_t    port_no;
    mepa_lock_t       mepa_lock;

    // Map from MESA to PHY info
    mepa_dbg.full = info->full;
    mepa_dbg.clear = info->clear;
    mepa_dbg.vml_format = info->vml_format;
    mepa_dbg.layer = (info->layer == MESA_DEBUG_LAYER_AIL ? MEPA_DEBUG_LAYER_AIL :
                      info->layer == MESA_DEBUG_LAYER_CIL ? MEPA_DEBUG_LAYER_CIL :
                      MEPA_DEBUG_LAYER_ALL);
    if (info->group == MESA_DEBUG_GROUP_ALL) {
        mepa_dbg.group = MEPA_DEBUG_GROUP_ALL;
    } else if (info->group == MESA_DEBUG_GROUP_PHY) {
        mepa_dbg.group = MEPA_DEBUG_GROUP_PHY;
    } else if (info->group == MESA_DEBUG_GROUP_PHY_TS) {
        mepa_dbg.group = MEPA_DEBUG_GROUP_PHY_TS;
    } else if (info->group == MESA_DEBUG_GROUP_MACSEC) {
        mepa_dbg.group = MEPA_DEBUG_GROUP_MACSEC;
    } else {
        return MESA_RC_OK;
    }

    mepa_lock.function = __FUNCTION__;
    mepa_lock.file = __FILE__;

    for (port_no = 0; port_no < inst->phy_device_cnt; port_no++) {
        if (!mesa_port_list_get(&info->port_list, port_no)) {
            continue;
        }

        if (inst->iface.lock_enter) {
            mepa_lock.line = (__LINE__ + 1);
            inst->iface.lock_enter(&mepa_lock);
        }

        pr("\nPHY %3d\n=======\n", port_no);

        if (inst->iface.lock_exit) {
            mepa_lock.line = (__LINE__ + 1);
            inst->iface.lock_exit(&mepa_lock);
        }


        (void)mepa_debug_info_dump(inst->phy_devices[port_no], pr, &mepa_dbg);
    }

    return MESA_RC_OK;
}

// Get the phy info
mepa_rc meba_phy_info_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_phy_info_t *const phy_info)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_phy_info_get(inst->phy_devices[port_no], phy_info);
}

mepa_rc meba_isolate_mode_conf(meba_inst_t inst, mepa_port_no_t port_no,            const mepa_bool_t iso_en)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_isolate_mode_conf(inst->phy_devices[port_no], iso_en);
}

// Get the SQI value
mepa_rc meba_phy_sqi_read(meba_inst_t inst, mepa_port_no_t port_no, uint32_t *const value)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_sqi_read(inst->phy_devices[port_no], value);
}

// Set the sof parameters
mepa_rc meba_phy_start_of_frame_conf_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_start_of_frame_conf_t *const conf)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_start_of_frame_conf_set(inst->phy_devices[port_no], conf);
}

// Get the sof parameters
mepa_rc meba_phy_start_of_frame_conf_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_start_of_frame_conf_t *const conf)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_start_of_frame_conf_get(inst->phy_devices[port_no], conf);
}

// Get framepreemption
mepa_rc meba_phy_framepreempt_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_bool_t *const value)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_framepreempt_get(inst->phy_devices[port_no], value);
}

// Start PHY Self-Test
mepa_rc meba_selftest_start(meba_inst_t inst, mepa_port_no_t port_no,
                            const mepa_selftest_info_t *inf)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_selftest_start(inst->phy_devices[port_no], inf);
}

// Read PHY Self-Test Checking counters
mepa_rc meba_selftest_read(meba_inst_t inst, mepa_port_no_t port_no,
                            mepa_selftest_info_t *const inf)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_selftest_read(inst->phy_devices[port_no], inf);
}

// To Set PRBS
mepa_rc meba_prbs_set(meba_inst_t inst, mepa_port_no_t port_no,
                      mepa_phy_prbs_type_t type,
                      mepa_phy_prbs_direction_t direction,
                      mepa_phy_prbs_generator_conf_t *const prbs_conf)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_prbs_set(inst->phy_devices[port_no], type, direction, prbs_conf);
}

// To Get PRBS
mepa_rc meba_prbs_get(meba_inst_t inst, mepa_port_no_t port_no,
                      mepa_phy_prbs_type_t type,
                      mepa_phy_prbs_direction_t direction,
                      mepa_phy_prbs_generator_conf_t *const prbs_conf)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_prbs_get(inst->phy_devices[port_no], type, direction, prbs_conf);
}

// To inject errors to PRBS
mepa_rc meba_prbs_monitor_set(meba_inst_t inst, mepa_port_no_t port_no,
                              mepa_phy_prbs_monitor_conf_t *const value)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_prbs_monitor_set(inst->phy_devices[port_no], value);
}

// To Get  error status  of PRBS
mepa_rc meba_prbs_monitor_get(meba_inst_t inst, mepa_port_no_t port_no,
                              mepa_phy_prbs_monitor_conf_t *const value)
{
    if ((port_no < 0) || (port_no >= inst->phy_device_cnt)) {
        return MESA_RC_ERR_INV_PORT_BOARD;
    }
    return mepa_prbs_monitor_get(inst->phy_devices[port_no], value);
}
