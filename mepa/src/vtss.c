// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/switch/api.h>

#define MEPA_RC(expr) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) return __rc__; }
#define true 1
#define false 0

typedef struct {
    mesa_inst_t inst;
    mepa_port_no_t port_no;
    mepa_port_interface_t mac_if;
} phy_data_t;

static mepa_rc mscc_1g_delete(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    free(data);
    free(dev);
    dev = NULL;
    return MEPA_RC_OK;
}

static mepa_rc reset_phy(phy_data_t *data, mepa_reset_conf_t *conf)
{
    mepa_event_t events;

    MEPA_RC(mesa_phy_event_enable_get(data->inst, data->port_no, &events));
    MEPA_RC(mesa_phy_reset(data->inst, data->port_no, conf));
    return mesa_phy_event_enable_set(data->inst, data->port_no, events, 1);
}

static mepa_rc mscc_1g_reset(mepa_device_t *dev,
                             const mepa_reset_param_t *rst_conf)
{
    mepa_reset_conf_t conf = {};
    phy_data_t *data = (phy_data_t *)(dev->data);

    mesa_phy_reset_get(data->inst, data->port_no, &conf);
    conf.force = MESA_PHY_FORCE_RESET;
    conf.mac_if = data->mac_if;
    conf.media_if = rst_conf->media_intf;
    conf.i_cpu_en = 0;

    return reset_phy(data, &conf);
}

static mepa_rc mscc_1g_atom_reset(mepa_device_t *dev,
                                  const mepa_reset_param_t *rst_conf)
{
    mepa_reset_conf_t conf = {};
    phy_data_t *data = (phy_data_t *)(dev->data);

    mesa_phy_reset_get(data->inst, data->port_no, &conf);
    conf.force = MESA_PHY_FORCE_RESET;
    conf.mac_if = data->mac_if;
    conf.media_if = rst_conf->media_intf;
    conf.i_cpu_en = 0;

    return reset_phy(data, &conf);
}

static mepa_rc mscc_1g_poll(mepa_device_t *dev,
                            mepa_driver_status_t *status)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_port_status_t mesa_status = {};

    mepa_rc rc = mesa_phy_status_get(data->inst, data->port_no, &mesa_status);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    // fill up status
    status->link = mesa_status.link;
    status->speed = mesa_status.speed;
    status->fdx = mesa_status.fdx;
    status->aneg = mesa_status.aneg;
    status->copper = mesa_status.copper;
    status->fiber = mesa_status.fiber;

    return MEPA_RC_OK;
}

static mepa_rc mscc_1g_conf_set(mepa_device_t *dev, const mepa_driver_conf_t *config)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_phy_conf_t phy_config = {}, cur_conf;

    phy_config.mdi = MESA_PHY_MDIX_AUTO;
    if (config->admin.enable) {
        if (config->speed == MESA_SPEED_AUTO ||
            config->speed == MESA_SPEED_1G) {
            phy_config.mode = MESA_PHY_MODE_ANEG;

            phy_config.aneg.speed_2g5_fdx = config->aneg.speed_2g5_fdx;
            phy_config.aneg.speed_5g_fdx = config->aneg.speed_5g_fdx;
            phy_config.aneg.speed_10g_fdx = config->aneg.speed_10g_fdx;
            phy_config.aneg.speed_10m_hdx = config->aneg.speed_10m_hdx;
            phy_config.aneg.speed_10m_fdx = config->aneg.speed_10m_fdx;
            phy_config.aneg.speed_100m_hdx = config->aneg.speed_100m_hdx;
            phy_config.aneg.speed_100m_fdx = config->aneg.speed_100m_fdx;
            phy_config.aneg.speed_1g_fdx = config->aneg.speed_1g_fdx;
            phy_config.aneg.no_restart_aneg = config->aneg.no_restart_aneg;

            // We don't support 1G half duplex
            phy_config.aneg.speed_1g_hdx = 0;
            phy_config.aneg.symmetric_pause = config->flow_control;
            phy_config.aneg.asymmetric_pause = config->flow_control;
        } else {
            phy_config.mode = MESA_PHY_MODE_FORCED;
            phy_config.forced.speed = config->speed;
            phy_config.forced.fdx = config->fdx;
        }
    } else {
        phy_config.mode = MESA_PHY_MODE_POWER_DOWN;
    }
    phy_config.mac_if_pcs.serdes_aneg_ena = config->mac_if_aneg_ena;
    if (mesa_phy_conf_get(data->inst, data->port_no, &cur_conf) == MESA_RC_OK) {
        if (phy_config.mac_if_pcs.serdes_aneg_ena && (cur_conf.mac_if_pcs.serdes_aneg_ena != phy_config.mac_if_pcs.serdes_aneg_ena)) {
            phy_config.mac_if_pcs.aneg_restart = true;
        }
    }
    return mesa_phy_conf_set(data->inst, data->port_no, &phy_config);
}

static mepa_rc phy_1g_conf_get(mepa_device_t *dev, mepa_driver_conf_t *const conf)
{
    mesa_phy_conf_t phy_conf;
    phy_data_t *data = (phy_data_t *)dev->data;
    *conf = (const mepa_driver_conf_t){};

    if (mesa_phy_conf_get(data->inst, data->port_no, &phy_conf) == MESA_RC_OK) {
        if (phy_conf.mode == MESA_PHY_MODE_ANEG) {
            conf->speed = MEPA_SPEED_AUTO;
            conf->flow_control = phy_conf.aneg.symmetric_pause;
            conf->aneg.speed_2g5_fdx = phy_conf.aneg.speed_2g5_fdx;
            conf->aneg.speed_5g_fdx = phy_conf.aneg.speed_5g_fdx;
            conf->aneg.speed_10g_fdx = phy_conf.aneg.speed_10g_fdx;
            conf->aneg.speed_10m_hdx = phy_conf.aneg.speed_10m_hdx;
            conf->aneg.speed_10m_fdx = phy_conf.aneg.speed_10m_fdx;
            conf->aneg.speed_100m_hdx = phy_conf.aneg.speed_100m_hdx;
            conf->aneg.speed_100m_fdx = phy_conf.aneg.speed_100m_fdx;
            conf->aneg.speed_1g_fdx = phy_conf.aneg.speed_1g_fdx;
            conf->aneg.no_restart_aneg = phy_conf.aneg.no_restart_aneg;
        } else if (phy_conf.mode == MESA_PHY_MODE_FORCED) {
            conf->speed = phy_conf.forced.speed;
            conf->fdx = phy_conf.forced.fdx;
        }
        conf->mac_if_aneg_ena = phy_conf.mac_if_pcs.serdes_aneg_ena;
        conf->admin.enable = phy_conf.mode != MESA_PHY_MODE_POWER_DOWN ? true : false;
    }
    return MEPA_RC_OK;
}
static mepa_rc mscc_1g_if_get(mepa_device_t *dev, mepa_port_speed_t speed,
                              mepa_port_interface_t *mac_if)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    *mac_if = data->mac_if;
    return MEPA_RC_OK;
}

static mepa_rc mscc_1g_power_set(mepa_device_t *dev,
                                 mepa_power_mode_t power)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_power_conf_t power_conf = {};
    power_conf.mode = power;
    return mesa_phy_power_conf_set(data->inst, data->port_no, &power_conf);
}

static mepa_rc mscc_1g_veriphy_start(mepa_device_t *dev, int mode)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_veriphy_start(data->inst, data->port_no, mode);
}

static mepa_rc mscc_1g_veriphy_get(mepa_device_t *dev,
                                   mepa_cable_diag_result_t *res)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_veriphy_result_t result;
    mepa_rc rc;

    if ((rc = mesa_phy_veriphy_get(data->inst, data->port_no, &result)) != MEPA_RC_ERROR) {
        res->link = result.link;
        memcpy(&res->status, &result.status, sizeof(res->status));
        memcpy(&res->length, &result.length, sizeof(res->length));
    }
    return rc;
}

static mepa_rc mscc_1g_media_set(mepa_device_t *dev,
                                 mepa_media_interface_t phy_media_if)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_reset_conf_t conf = {};
    mesa_phy_reset_get(data->inst, data->port_no, &conf);

    conf.mac_if = data->mac_if;
    conf.media_if = phy_media_if;

    return mesa_phy_reset(data->inst, data->port_no, &conf);
}

static mepa_device_t *mscc_1g_probe(mepa_driver_t *drv,
                                    const mepa_driver_address_t *mode)
{
    if (mode->mode != mscc_phy_driver_address_mode) {
        return NULL;
    }

    mepa_device_t *device =
        (mepa_device_t *)calloc(1, sizeof(mepa_device_t));

    if (device == NULL) {
        goto out_device;
    }

    phy_data_t *data = (phy_data_t *)calloc(1, sizeof(phy_data_t));

    if (data == NULL) {
        goto out_data;
    }

    device->drv = drv;
    data->inst = mode->val.mscc_address.inst;
    data->port_no = mode->val.mscc_address.port_no;
    data->mac_if = mode->val.mscc_address.mac_if;
    device->data = data;

    return device;

out_data:
    free(device);
out_device:
    return NULL;
}

static mepa_rc mscc_1g_status_1g_get(mepa_device_t    *dev,
                                     mepa_aneg_status_t *status) {
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_status_1g_get(data->inst, data->port_no, status);
}

static mepa_rc phy_1g_event_enable_set(mepa_device_t *dev, mepa_event_t event,
                                        mesa_bool_t enable)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_event_enable_set(data->inst, data->port_no, event, enable);
}

static mepa_rc phy_1g_event_enable_get(mepa_device_t *dev, mepa_event_t *ev_mask)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_event_enable_get(data->inst, data->port_no, ev_mask);
}

static mepa_rc phy_1g_event_poll(mepa_device_t *dev, mepa_event_t *status)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_event_poll(data->inst, data->port_no, status);
}

static mepa_rc phy_1g_loopback_set(mepa_device_t *dev, const mepa_loopback_t *loopback)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_loopback_t phy_loop = {};

    if (loopback->qsgmii_pcs_tbi_ena == true || loopback->qsgmii_pcs_gmii_ena == true ||
        loopback->qsgmii_serdes_ena == true) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    phy_loop.near_end_enable = loopback->near_end_ena;
    phy_loop.far_end_enable = loopback->far_end_ena;
    phy_loop.connector_enable = loopback->connector_ena;
    phy_loop.mac_serdes_input_enable = loopback->mac_serdes_input_ena;
    phy_loop.mac_serdes_facility_enable = loopback->mac_serdes_facility_ena;
    phy_loop.mac_serdes_equipment_enable = loopback->mac_serdes_equip_ena;
    phy_loop.media_serdes_input_enable = loopback->media_serdes_input_ena;
    phy_loop.media_serdes_facility_enable = loopback->media_serdes_facility_ena;
    phy_loop.media_serdes_equipment_enable = loopback->media_serdes_equip_ena;
    return mesa_phy_loopback_set(data->inst, data->port_no, phy_loop);
}

static mepa_rc phy_1g_loopback_get(mepa_device_t *dev, mepa_loopback_t *const loopback)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_loopback_t loop = {};
    if (mesa_phy_loopback_get(data->inst, data->port_no, &loop) == MESA_RC_OK) {
        loopback->far_end_ena = loop.far_end_enable;
        loopback->near_end_ena = loop.near_end_enable;
        loopback->connector_ena = loop.connector_enable;
        loopback->mac_serdes_input_ena = loop.mac_serdes_input_enable;
        loopback->mac_serdes_facility_ena = loop.mac_serdes_facility_enable;
        loopback->mac_serdes_equip_ena = loop.mac_serdes_equipment_enable;
        loopback->media_serdes_input_ena = loop.media_serdes_input_enable;
        loopback->media_serdes_facility_ena = loop.media_serdes_facility_enable;
        loopback->media_serdes_equip_ena = loop.media_serdes_equipment_enable;
    }
    return MEPA_RC_OK;
}

static mepa_rc phy_1g_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_read(data->inst, data->port_no, address, value);
}

static mepa_rc phy_1g_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_write(data->inst, data->port_no, address, value);
}

static mepa_rc phy_1g_gpio_mode(mepa_device_t *dev, const mepa_gpio_conf_t *gpio_conf)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_gpio_mode_t gpio_mode;

    // VSC8584 has 0-13 gpios
    if (gpio_conf->gpio_no > 13) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    if (gpio_conf->mode == MEPA_GPIO_MODE_LED_DISABLE_EXTENDED) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    switch (gpio_conf->mode) {
        case MEPA_GPIO_MODE_OUT: gpio_mode = MESA_PHY_GPIO_OUT;
            break;
        case MEPA_GPIO_MODE_IN: gpio_mode = MESA_PHY_GPIO_IN;
            break;
        default: gpio_mode = MESA_PHY_GPIO_ALT_0;
            break;
    }
    if (gpio_conf->mode >= MEPA_GPIO_MODE_LED_LINK_ACTIVITY && gpio_conf->mode < MEPA_GPIO_MODE_LED_DISABLE_EXTENDED) {
        mesa_phy_led_mode_select_t mode_select;
        mode_select.number = gpio_conf->led_num == MEPA_LED0 ? MESA_PHY_LED0 : MESA_PHY_LED1;
        mode_select.mode = MESA_PHY_LED_MODE_LINK_ACTIVITY + (gpio_conf->mode - MEPA_GPIO_MODE_LED_LINK_ACTIVITY);
        mesa_phy_led_mode_set(data->inst, data->port_no, mode_select);
    }
    return mesa_phy_gpio_mode(data->inst, data->port_no, gpio_conf->gpio_no, gpio_mode);
}

static mepa_rc phy_1g_gpio_set(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t enable)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    // VSC8584 has 0-13 gpios
    if (gpio_no > 13) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    return mesa_phy_gpio_set(data->inst, data->port_no, gpio_no, enable);
}

static mepa_rc phy_1g_gpio_get(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t * const enable)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    // VSC8584 has 0-13 gpios
    if (gpio_no > 13) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    return mesa_phy_gpio_get(data->inst, data->port_no, gpio_no, enable);
}

typedef struct malibu_10g_phy_data {
    mesa_inst_t inst;
    mepa_port_no_t port_no;
    mepa_port_interface_t mac_if;
} malibu_10g_phy_data_t;

static mepa_rc phy_10g_delete(mepa_device_t *dev)
{
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)dev->data;
    free(data);
    free(dev);
    dev = NULL;
    return MEPA_RC_OK;
}

static mepa_rc malibu_10g_reset(mepa_device_t *dev,
                                const mepa_reset_param_t *rst_conf)
{
    mesa_phy_10g_mode_t oper_mode = {};
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)(dev->data);

    oper_mode.oper_mode = MESA_PHY_LAN_MODE;
    oper_mode.xfi_pol_invert = 1;
    oper_mode.polarity.host_rx = true;
    oper_mode.polarity.line_rx = true;
    oper_mode.polarity.host_tx = false;
    oper_mode.polarity.line_tx = false;
    oper_mode.is_host_wan = false;
    oper_mode.lref_for_host = false;
    oper_mode.h_clk_src.is_high_amp = true;
    oper_mode.l_clk_src.is_high_amp = true;
    oper_mode.h_media = MESA_MEDIA_TYPE_SR;
    oper_mode.l_media = MESA_MEDIA_TYPE_SR;
    oper_mode.serdes_conf.l_offset_guard = true;
    oper_mode.serdes_conf.h_offset_guard = true;

    if ((data->port_no == 25) || (data->port_no == 24)) {
        oper_mode.polarity.host_rx = false;
        oper_mode.polarity.line_rx = false;
        oper_mode.polarity.host_tx = true;
        oper_mode.polarity.line_tx = true;
    }

    return mesa_phy_10g_mode_set(data->inst, data->port_no, &oper_mode);
}

static mepa_rc venice_10g_reset(mepa_device_t *dev,
                                const mepa_reset_param_t *rst_conf)
{
    mesa_phy_10g_mode_t oper_mode = {};
    mesa_phy_10g_id_t phy_10g_id;
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)(dev->data);
    oper_mode.oper_mode = MESA_PHY_LAN_MODE;
    if (mesa_phy_10g_id_get(0, data->port_no, &phy_10g_id) == MEPA_RC_OK) {
        if ((phy_10g_id.part_number == 0x8487) || (phy_10g_id.part_number == 0x8488)) {
            oper_mode.xfi_pol_invert = 0;
        } else {
            oper_mode.xfi_pol_invert = 1;
        }
    }
    oper_mode.l_clk_src.is_high_amp = true;
    oper_mode.l_media = MESA_MEDIA_TYPE_SR;
    return mesa_phy_10g_mode_set(data->inst, data->port_no, &oper_mode);
}


static mepa_rc phy_10g_poll(mepa_device_t *dev,
                            mepa_driver_status_t *status)
{
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)(dev->data);
    mesa_port_status_t mesa_status = {};

    mepa_rc rc = mesa_port_status_get(data->inst, data->port_no, &mesa_status);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    status->link   = mesa_status.link;
    status->speed  = mesa_status.speed;
    status->fdx    = mesa_status.fdx;
    status->aneg   = mesa_status.aneg;
    status->copper = mesa_status.copper;
    status->fiber  = mesa_status.fiber;

    return MEPA_RC_OK;
}

static mepa_rc phy_10g_conf_set(mepa_device_t *dev, const mepa_driver_conf_t *config)
{
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)dev->data;
    mesa_phy_10g_mode_t mode = {};

    if (mesa_phy_10g_mode_get(data->inst, data->port_no, &mode) != MEPA_RC_OK) {
        return MEPA_RC_ERROR;
    }

    mepa_port_speed_t speed =
        config->speed == MESA_SPEED_2500M || config->speed == MESA_SPEED_AUTO
        ? MESA_SPEED_1G
        : config->speed;

    if (speed == MESA_SPEED_1G) {
        /* Need to flip the lanes to match JR XAUI-lane-0 and 8487 XAUI-lane-0
         */
        mode.xaui_lane_flip = true;
        if (mode.oper_mode != MESA_PHY_1G_MODE) {
            mode.oper_mode = MESA_PHY_1G_MODE;
            if (mesa_phy_10g_mode_set(data->inst, data->port_no, &mode) !=
                MEPA_RC_OK) {
                return MEPA_RC_ERROR;
            }
        }

        mesa_phy_10g_clause_37_control_t ctrl = {};
        ctrl.enable = config->speed == MESA_SPEED_AUTO;
        ctrl.advertisement.fdx = 1;
        ctrl.advertisement.symmetric_pause = config->flow_control;
        ctrl.advertisement.asymmetric_pause = config->flow_control;
        ctrl.advertisement.remote_fault =
            (config->admin.enable ? MESA_PHY_10G_CLAUSE_37_RF_LINK_OK
             : MESA_PHY_10G_CLAUSE_37_RF_OFFLINE);
        ctrl.l_h = true;
        if (mesa_phy_10g_clause_37_control_set(data->inst, data->port_no,
                                               &ctrl) != MEPA_RC_OK) {
            return MEPA_RC_ERROR;
        }

        mesa_port_clause_37_control_t port_ctrl;
        port_ctrl.enable = false;
        mesa_port_clause_37_control_set(data->inst, data->port_no, &port_ctrl);
    } else {
        mode.xaui_lane_flip = false;
        mode.oper_mode = MESA_PHY_LAN_MODE;
        if (mesa_phy_10g_mode_set(data->inst, data->port_no, &mode) !=
            MEPA_RC_OK) {
            return MEPA_RC_ERROR;
        }
    }

    return MEPA_RC_OK;
}

static mepa_rc malibu_10g_if_get(mepa_device_t *dev,
                                 mepa_port_speed_t speed,
                                 mepa_port_interface_t *mac_if)
{
    switch (speed) {
    case MESA_SPEED_AUTO:
    case MESA_SPEED_1G:
        *mac_if = MESA_PORT_INTERFACE_SERDES;
        break;
    default:
        *mac_if = MESA_PORT_INTERFACE_SFI;
        break;
    }
    return MEPA_RC_OK;
}

static mepa_rc venice_10g_if_get(mepa_device_t *dev,
                                 mepa_port_speed_t speed,
                                 mepa_port_interface_t *mac_if)
{
    switch (speed) {
    case MESA_SPEED_AUTO:
    case MESA_SPEED_1G:
        *mac_if = MESA_PORT_INTERFACE_SERDES;
        break;
    default:
        *mac_if = MESA_PORT_INTERFACE_XAUI;
        break;
    }
    return MEPA_RC_OK;

}

static mepa_device_t *phy_10g_probe(
    mepa_driver_t *drv, const mepa_driver_address_t *mode)
{
    if (mode->mode != mscc_phy_driver_address_mode) {
        return NULL;
    }

    mepa_device_t *device =
        (mepa_device_t *)calloc(1, sizeof(mepa_device_t));

    if (device == NULL) {
        goto out_device;
    }

    malibu_10g_phy_data_t *data =
        (malibu_10g_phy_data_t *)calloc(1, sizeof(malibu_10g_phy_data_t));

    if (data == NULL) {
        goto out_data;
    }

    device->drv = drv;
    data->inst = mode->val.mscc_address.inst;
    data->port_no = mode->val.mscc_address.port_no;
    data->mac_if = mode->val.mscc_address.mac_if;
    device->data = data;

    return device;

out_data:
    free(device);
out_device:
    return NULL;
}

mepa_drivers_t mepa_mscc_driver_init()
{
    static const int nr_mscc_phy = 4;
    static mepa_driver_t mscc_drivers[] = {
        {
            .id = 0x00070400,
            .mask = 0x02fffc00,
            .mepa_driver_delete = mscc_1g_delete,
            .mepa_driver_reset = mscc_1g_reset,
            .mepa_driver_poll = mscc_1g_poll,
            .mepa_driver_conf_set = mscc_1g_conf_set,
            .mepa_driver_conf_get = phy_1g_conf_get,
            .mepa_driver_if_get = mscc_1g_if_get,
            .mepa_driver_power_set = mscc_1g_power_set,
            .mepa_driver_cable_diag_start = mscc_1g_veriphy_start,
            .mepa_driver_cable_diag_get = mscc_1g_veriphy_get,
            .mepa_driver_media_set = mscc_1g_media_set,
            .mepa_driver_probe = mscc_1g_probe,
            .mepa_driver_aneg_status_get = mscc_1g_status_1g_get,
            .mepa_driver_clause22_read = phy_1g_read,
            .mepa_driver_clause22_write = phy_1g_write,
            .mepa_driver_event_enable_set = phy_1g_event_enable_set,
            .mepa_driver_event_enable_get = phy_1g_event_enable_get,
            .mepa_driver_event_poll = phy_1g_event_poll,
            .mepa_driver_loopback_set = phy_1g_loopback_set,
            .mepa_driver_loopback_get = phy_1g_loopback_get,
            .mepa_driver_gpio_mode_set = phy_1g_gpio_mode,
            .mepa_driver_gpio_out_set = phy_1g_gpio_set,
            .mepa_driver_gpio_in_get = phy_1g_gpio_get,
        },
        // Atom - QSGMII family
        {
            .id = 0x000706e0,
            .mask = 0x02ffFFe0,
            .mepa_driver_delete = mscc_1g_delete,
            .mepa_driver_reset = mscc_1g_atom_reset,
            .mepa_driver_poll = mscc_1g_poll,
            .mepa_driver_conf_set = mscc_1g_conf_set,
            .mepa_driver_conf_get = phy_1g_conf_get,
            .mepa_driver_if_get = mscc_1g_if_get,
            .mepa_driver_power_set = mscc_1g_power_set,
            .mepa_driver_cable_diag_start = mscc_1g_veriphy_start,
            .mepa_driver_cable_diag_get = mscc_1g_veriphy_get,
            .mepa_driver_media_set = mscc_1g_media_set,
            .mepa_driver_probe = mscc_1g_probe,
            .mepa_driver_aneg_status_get = mscc_1g_status_1g_get,
            .mepa_driver_clause22_read = phy_1g_read,
            .mepa_driver_clause22_write = phy_1g_write,
            .mepa_driver_event_enable_set = phy_1g_event_enable_set,
            .mepa_driver_event_enable_get = phy_1g_event_enable_get,
            .mepa_driver_event_poll = phy_1g_event_poll,
            .mepa_driver_loopback_set = phy_1g_loopback_set,
            .mepa_driver_loopback_get = phy_1g_loopback_get,
            .mepa_driver_gpio_mode_set = phy_1g_gpio_mode,
            .mepa_driver_gpio_out_set = phy_1g_gpio_set,
            .mepa_driver_gpio_in_get = phy_1g_gpio_get,
        },
        // Atom - SGMII
        {
            .id = 0x706d1,
            .mask = 0xFFffFFff,
            .mepa_driver_delete = mscc_1g_delete,
            .mepa_driver_reset = mscc_1g_reset,
            .mepa_driver_poll = mscc_1g_poll,
            .mepa_driver_conf_set = mscc_1g_conf_set,
            .mepa_driver_conf_get = phy_1g_conf_get,
            .mepa_driver_if_get = mscc_1g_if_get,
            .mepa_driver_power_set = mscc_1g_power_set,
            .mepa_driver_cable_diag_start = mscc_1g_veriphy_start,
            .mepa_driver_cable_diag_get = mscc_1g_veriphy_get,
            .mepa_driver_media_set = mscc_1g_media_set,
            .mepa_driver_probe = mscc_1g_probe,
            .mepa_driver_aneg_status_get = mscc_1g_status_1g_get,
            .mepa_driver_clause22_read = phy_1g_read,
            .mepa_driver_clause22_write = phy_1g_write,
            .mepa_driver_event_enable_set = phy_1g_event_enable_set,
            .mepa_driver_event_enable_get = phy_1g_event_enable_get,
            .mepa_driver_event_poll = phy_1g_event_poll,
            .mepa_driver_loopback_set = phy_1g_loopback_set,
            .mepa_driver_loopback_get = phy_1g_loopback_get,
            .mepa_driver_gpio_mode_set = phy_1g_gpio_mode,
            .mepa_driver_gpio_out_set = phy_1g_gpio_set,
            .mepa_driver_gpio_in_get = phy_1g_gpio_get,
        },
        {
            .id = 0x000FC400,
            .mask = 0x02fffc00,
            .mepa_driver_delete = mscc_1g_delete,
            .mepa_driver_reset = mscc_1g_reset,
            .mepa_driver_poll = mscc_1g_poll,
            .mepa_driver_conf_set = mscc_1g_conf_set,
            .mepa_driver_conf_get = phy_1g_conf_get,
            .mepa_driver_if_get = mscc_1g_if_get,
            .mepa_driver_power_set = mscc_1g_power_set,
            .mepa_driver_cable_diag_start = mscc_1g_veriphy_start,
            .mepa_driver_cable_diag_get = mscc_1g_veriphy_get,
            .mepa_driver_media_set = mscc_1g_media_set,
            .mepa_driver_probe = mscc_1g_probe,
            .mepa_driver_aneg_status_get = mscc_1g_status_1g_get,
            .mepa_driver_clause22_read = phy_1g_read,
            .mepa_driver_clause22_write = phy_1g_write,
            .mepa_driver_event_enable_set = phy_1g_event_enable_set,
            .mepa_driver_event_enable_get = phy_1g_event_enable_get,
            .mepa_driver_event_poll = phy_1g_event_poll,
            .mepa_driver_loopback_set = phy_1g_loopback_set,
            .mepa_driver_loopback_get = phy_1g_loopback_get,
            .mepa_driver_gpio_mode_set = phy_1g_gpio_mode,
            .mepa_driver_gpio_out_set = phy_1g_gpio_set,
            .mepa_driver_gpio_in_get = phy_1g_gpio_get,
        }
    };

    mepa_drivers_t result;
    result.phy_drv = mscc_drivers;
    result.count = nr_mscc_phy;

    return result;
}

mepa_drivers_t mepa_malibu_driver_init()
{
    static const int nr_malibu_phy = 1;
    static mepa_driver_t malibu_drivers[] = {{
        .id = 0x8200,
        .mask = 0x0000FF00,
        .mepa_driver_delete = phy_10g_delete,
        .mepa_driver_reset = malibu_10g_reset,
        .mepa_driver_poll = phy_10g_poll,
        .mepa_driver_conf_set = phy_10g_conf_set,
        .mepa_driver_if_get = malibu_10g_if_get,
        .mepa_driver_power_set = NULL,
        .mepa_driver_cable_diag_start = NULL,
        .mepa_driver_cable_diag_get = NULL,
        .mepa_driver_media_set = NULL,
        .mepa_driver_probe = phy_10g_probe,
        .mepa_driver_aneg_status_get = NULL,
    }};

    mepa_drivers_t result;
    result.phy_drv = malibu_drivers;
    result.count = nr_malibu_phy;

    return result;
}

mepa_drivers_t mepa_venice_driver_init()
{
    static const int nr_venice_phy = 1;
    static mepa_driver_t venice_drivers[] = {{
        .id = 0x8400,
        .mask = 0x0000FF00,
        .mepa_driver_delete = phy_10g_delete,
        .mepa_driver_reset = venice_10g_reset,
        .mepa_driver_poll = phy_10g_poll,
        .mepa_driver_conf_set = phy_10g_conf_set,
        .mepa_driver_if_get = venice_10g_if_get,
        .mepa_driver_probe = phy_10g_probe,
    }};

    mepa_drivers_t result;
    result.phy_drv = venice_drivers;
    result.count = nr_venice_phy;

    return result;
}

mepa_drivers_t mepa_default_phy_driver_init()
{
    static const int nr_default_drivers = 1;
    static mepa_driver_t default_drivers[] = {{
        .id = 0x0,
        .mask = 0x00,
        .mepa_driver_delete = mscc_1g_delete,
        .mepa_driver_reset = mscc_1g_reset,
        .mepa_driver_poll = mscc_1g_poll,
        .mepa_driver_conf_set = mscc_1g_conf_set,
        .mepa_driver_conf_get = phy_1g_conf_get,
        .mepa_driver_if_get = mscc_1g_if_get,
        .mepa_driver_power_set = mscc_1g_power_set,
        .mepa_driver_cable_diag_start = mscc_1g_veriphy_start,
        .mepa_driver_cable_diag_get = mscc_1g_veriphy_get,
        .mepa_driver_media_set = mscc_1g_media_set,
        .mepa_driver_probe = mscc_1g_probe,
        .mepa_driver_aneg_status_get = mscc_1g_status_1g_get,
        .mepa_driver_clause22_read = phy_1g_read,
        .mepa_driver_clause22_write = phy_1g_write,
        .mepa_driver_event_enable_set = phy_1g_event_enable_set,
        .mepa_driver_event_enable_get = phy_1g_event_enable_get,
        .mepa_driver_event_poll = phy_1g_event_poll,
        .mepa_driver_loopback_set = phy_1g_loopback_set,
        .mepa_driver_loopback_get = phy_1g_loopback_get,
        .mepa_driver_gpio_mode_set = phy_1g_gpio_mode,
        .mepa_driver_gpio_out_set = phy_1g_gpio_set,
        .mepa_driver_gpio_in_get = phy_1g_gpio_get,
    }};

    mepa_drivers_t result;
    result.phy_drv = default_drivers;
    result.count = nr_default_drivers;

    return result;
}
