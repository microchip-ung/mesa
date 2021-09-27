// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api/phy_ts.h>

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

#define MEPA_RC(expr) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) return __rc__; }
#define true 1
#define false 0

extern mepa_ts_driver_t vtss_ts_drivers;

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
    mepa_rc rc = MEPA_RC_OK;

    if (rst_conf->reset_point == MEPA_RESET_POINT_PRE) {
        // pre reset api should be called on base port
        rc = mesa_phy_pre_reset(data->inst, data->port_no);
    } else if (rst_conf->reset_point == MEPA_RESET_POINT_POST) {
        // post reset api should be called on base port
        rc = mesa_phy_post_reset(data->inst, data->port_no);
    } else if (rst_conf->reset_point == MEPA_RESET_POINT_DEFAULT) {
        mesa_phy_reset_get(data->inst, data->port_no, &conf);
        conf.force = MESA_PHY_FORCE_RESET;
        conf.mac_if = data->mac_if;
        conf.media_if = rst_conf->media_intf;
        conf.i_cpu_en = 0;
        rc = reset_phy(data, &conf);
    }

    return rc;
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
    mesa_phy_conf_1g_t cfg_neg = {};

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

            // manual negotiation
            if (config->man_neg) {
                cfg_neg.master.cfg = true;
                cfg_neg.master.val = config->man_neg == MEPA_MANUAL_NEG_REF ? true : false;
            }
            (void)mesa_phy_conf_1g_set(data->inst, data->port_no, &cfg_neg);
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
    mesa_phy_conf_1g_t cfg_neg = {};
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

            // Get manual negotiation options
            if (mesa_phy_conf_1g_get(data->inst, data->port_no, &cfg_neg) == MESA_RC_OK) {
                conf->man_neg = !cfg_neg.master.cfg ? MEPA_MANUAL_NEG_DISABLED :
                                cfg_neg.master.val ? MEPA_MANUAL_NEG_REF : MEPA_MANUAL_NEG_CLIENT;
            }
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
static mepa_rc phy_1g_synce_clk_conf_set(mepa_device_t *dev, const mepa_synce_clock_conf_t *conf)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_clock_conf_t phy_conf = {};
    mesa_phy_recov_clk_t clk_port = conf->dst == MEPA_SYNCE_CLOCK_DST_1 ? MESA_PHY_RECOV_CLK1 : MESA_PHY_RECOV_CLK2;

    phy_conf.squelch = conf->src == MEPA_SYNCE_CLOCK_SRC_DISABLED ? MESA_PHY_CLK_SQUELCH_NONE : MESA_PHY_CLK_SQUELCH_MAX;
    phy_conf.src = conf->src == MEPA_SYNCE_CLOCK_SRC_SERDES_MEDIA ? MESA_PHY_SERDES_MEDIA :
                   conf->src == MEPA_SYNCE_CLOCK_SRC_COPPER_MEDIA ? MESA_PHY_COPPER_MEDIA : MESA_PHY_CLK_DISABLED;
    phy_conf.freq = conf->freq == MEPA_FREQ_25M ? MESA_PHY_FREQ_25M :
                    conf->freq == MEPA_FREQ_31_25M ? MESA_PHY_FREQ_3125M : MESA_PHY_FREQ_125M;

    return mesa_phy_clock_conf_set(data->inst, data->port_no, clk_port, &phy_conf);
}

static mepa_rc phy_1g_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_type_t phy_id;
    mesa_rc rc = MESA_RC_OK;

    phy_info->cap = 0;
    rc = mesa_phy_id_get(data->inst, data->port_no, &phy_id);
    if (rc == MESA_RC_OK) {
        phy_info->part_number = phy_id.part_number;
        phy_info->revision = phy_id.revision;
        if (phy_id.part_number == MESA_PHY_TYPE_8582 || phy_id.part_number == MESA_PHY_TYPE_8584 ||
            phy_id.part_number == MESA_PHY_TYPE_8575 || phy_id.part_number == MESA_PHY_TYPE_8586) {
            phy_info->cap |= MEPA_CAP_TS_MASK_GEN_2;
        } else if (phy_id.part_number == MESA_PHY_TYPE_8574 || phy_id.part_number == MESA_PHY_TYPE_8572) {
            phy_info->cap |= MEPA_CAP_TS_MASK_GEN_1;
        } else {
            phy_info->cap |= MEPA_CAP_TS_MASK_NONE;
        }
        phy_info->cap |= MEPA_CAP_SPEED_MASK_1G;
        phy_info->ts_base_port = phy_id.phy_api_base_no;
    }
    return rc == MESA_RC_OK ? MEPA_RC_OK : MEPA_RC_ERROR;
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

static mepa_rc phy_10g_info_get(struct mepa_device *dev, mepa_phy_info_t *const phy_info)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_10g_id_t phy_id = {};
    mesa_rc rc = MESA_RC_OK;

    phy_info->cap = 0;
    rc = mesa_phy_10g_id_get(data->inst, data->port_no, &phy_id);
    if (rc == MESA_RC_OK) {
        phy_info->part_number = phy_id.part_number;
        phy_info->revision = phy_id.revision;
        if ((phy_id.part_number == 0x8488 || phy_id.part_number == 0x8487) && phy_id.revision >= 4) {
            phy_info->cap |= MEPA_CAP_TS_MASK_GEN_1;
        } else if ((phy_id.part_number == 0x8489 && !(phy_id.device_feature_status & MESA_PHY_10G_TIMESTAMP_DISABLED)) ||
            (phy_id.part_number == 0x8490 || phy_id.part_number == 0x8491) ||
            (phy_id.family == MESA_PHY_FAMILY_MALIBU)) {
            phy_info->cap |= MEPA_CAP_TS_MASK_GEN_2;
        } else {
            phy_info->cap |= MEPA_CAP_TS_MASK_NONE;
        }
        phy_info->cap |= MEPA_CAP_SPEED_MASK_10G;
        phy_info->ts_base_port = (phy_id.channel_id > 1) ? (phy_id.phy_api_base_no + 2) : phy_id.phy_api_base_no;
    }
    return rc == MESA_RC_OK ? MEPA_RC_OK : MEPA_RC_ERROR;
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

static mepa_rc vtss_ts_init_conf_set(struct mepa_device *dev, const mepa_ts_init_conf_t *const ts_init_conf)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_phy_ts_init_conf_t init_conf;


    init_conf.clk_freq = ts_init_conf->clk_freq;
    init_conf.clk_src = ts_init_conf->clk_src;
    init_conf.rx_ts_pos = ts_init_conf->rx_ts_pos;
    init_conf.rx_ts_len = ts_init_conf->rx_ts_len;
    init_conf.tx_fifo_mode = ts_init_conf->tx_fifo_mode; /**< Tx TSFIFO access mode */
    init_conf.tx_ts_len = ts_init_conf->tx_ts_len; /**< timestamp size in Tx TSFIFO */
    init_conf.tx_fifo_spi_conf = true; /**< Modify default 1588_spi configuration, applicable only on PHYs with SPI timestamp fifo support */
#if 0
    init_conf.tx_fifo_hi_clk_cycs = ; /**< Number of clock periods that the spi_clk is high */
    init_conf.tx_fifo_lo_clk_cycs; /**< Number of clock periods that the spi_clk is low */
#endif

    init_conf.xaui_sel_8487 = MESA_PHY_TS_8487_XAUI_SEL_0; /**< 8487 XAUI lane selection*/
    init_conf.tc_op_mode = MESA_PHY_TS_TC_OP_MODE_C; /**< TC operating mode */
    init_conf.auto_clear_ls = true; /**< Load and Save of LTC are auto cleared */
    init_conf.macsec_ena = false;       /**< MACsec is enabled or disabled */
    init_conf.chk_ing_modified = false;/**< True if the flag bit needs to be modified in ingress and thus in egress */
    init_conf.one_step_txfifo = false; /**< used when transmitting Delay_Req in one step mode. False when correctionfield update is used instead */
#if 0
    if (phy_id.part_number == 0x8488 || phy_id.part_number == 0x8489 || phy_id.part_number == 0x8490) {
        phy_conf.xaui_sel_8487 = MESA_PHY_TS_8487_XAUI_SEL_0; /* Required for 8488, 8489, 8490 */
    } else {
        phy_conf.xaui_sel_8487 = MESA_PHY_TS_8487_XAUI_SEL_0 | MESA_PHY_TS_8487_XAUI_SEL_1; /* Required for 8487 and 8491 */
    }

#endif

    return mesa_phy_ts_init(data->inst, data->port_no, &init_conf);
}


static mepa_rc vtss_ts_init_conf_get(mepa_device_t *dev, mepa_ts_init_conf_t *const ts_init_conf)
{
    uint16_t val = 0;
    mepa_rc rc = MESA_RC_ERROR;
    mepa_bool_t                     ts_init_done;
    mesa_phy_ts_init_conf_t         init_conf;
    phy_data_t *data = (phy_data_t *)dev->data;

    rc =  mesa_phy_ts_init_conf_get(data->inst, data->port_no, &ts_init_done, &init_conf);
    if (rc != MEPA_RC_OK) {
        return rc;
    }
    ts_init_conf->clk_src           = init_conf.clk_src;
    ts_init_conf->clk_freq          = init_conf.clk_freq;
    ts_init_conf->rx_ts_len         = init_conf.rx_ts_len;
    ts_init_conf->rx_ts_pos         = init_conf.rx_ts_pos;
    ts_init_conf->tx_fifo_mode      = init_conf.tx_fifo_mode;
    ts_init_conf->tx_fifo_spi_conf  = init_conf.tx_fifo_spi_conf;
    ts_init_conf->tx_ts_len         = init_conf.tx_ts_len;
    ts_init_conf->auto_clear_ls     = init_conf.auto_clear_ls;

    return MEPA_RC_OK;
}


static mepa_rc vtss_ts_mode_set(mepa_device_t *dev, const mepa_bool_t enable)
{
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    return mesa_phy_ts_mode_set(data->inst, data->port_no,  enable);

    return MEPA_RC_OK;
}

static mepa_rc vtss_ts_mode_get(mepa_device_t *dev, mepa_bool_t *const enable)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    return mesa_phy_ts_mode_get(data->inst, data->port_no,  enable);

    return MEPA_RC_OK;
}

static mepa_rc vtss_ts_ltc_ls_en_set(mepa_device_t *dev, const mepa_ts_ls_type_t  ls_type)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    switch (ls_type) {
    case MEPA_TS_CMD_LOAD:
        return mesa_phy_ts_ptptime_set_done(data->inst, data->port_no);
        break;
    case MEPA_TS_CMD_SAVE:
        return mesa_phy_ts_ptptime_arm(data->inst, data->port_no);
        break;
    default:
        break;
    }
    return MEPA_RC_OK;
}

static mepa_rc vtss_ts_ltc_get(mepa_device_t *dev, mepa_timestamp_t *const ts)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_phy_timestamp_t vts;
    mesa_rc rc;

    if ((rc = mesa_phy_ts_ptptime_get(data->inst, data->port_no, &vts)) == MESA_RC_OK) {
        ts->seconds.high = vts.seconds.high;
        ts->seconds.low  = vts.seconds.low;
        ts->nanoseconds  = vts.nanoseconds;
        return MEPA_RC_OK;
    } else {
        return MEPA_RC_ERROR;
    }
}

static mepa_rc vtss_ts_ltc_set(mepa_device_t *dev, const mepa_timestamp_t *const ts)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_phy_timestamp_t vts;

    vts.seconds.high = ts->seconds.high;
    vts.seconds.low = ts->seconds.low;
    vts.nanoseconds = ts->nanoseconds;
    return mesa_phy_ts_ptptime_set(data->inst, data->port_no, &vts);
}

static mepa_rc vtss_ts_clock_delay_asymmetry_get(mepa_device_t *dev, mepa_timeinterval_t *const delay_asym)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_delay_asymmetry_get(data->inst, data->port_no, delay_asym);
}

static mepa_rc vtss_ts_clock_delay_asymmetry_set(mepa_device_t *dev, const mepa_timeinterval_t *const delay_asym)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_delay_asymmetry_set(data->inst, data->port_no, delay_asym);
}

static mepa_rc vtss_ts_clock_path_delay_get(mepa_device_t *dev, mepa_timeinterval_t *const path_delay)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_path_delay_get(data->inst, data->port_no, path_delay);
}

static mepa_rc vtss_ts_clock_path_delay_set(mepa_device_t *dev, const mepa_timeinterval_t *const path_delay)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_path_delay_set(data->inst, data->port_no, path_delay);
}

static mepa_rc vtss_ts_clock_egress_latency_get(mepa_device_t *dev, mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_egress_latency_get(data->inst, data->port_no, latency);

}
static mepa_rc vtss_ts_clock_egress_latency_set(mepa_device_t *dev, const mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_egress_latency_set(data->inst, data->port_no, latency);
}

static mepa_rc vtss_ts_clock_ingress_latency_get(mepa_device_t *dev, mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_ingress_latency_get(data->inst, data->port_no, latency);
}

static mepa_rc vtss_ts_clock_ingress_latency_set(mepa_device_t *dev, const mepa_timeinterval_t *const latency)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_ingress_latency_set(data->inst, data->port_no, latency);
}

static mepa_rc vtss_ts_clock_rateadj_get(mepa_device_t *dev, mepa_ts_scaled_ppb_t *const adj)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_clock_rateadj_get(data->inst, data->port_no, adj);
}

static mepa_rc vtss_ts_clock_rateadj_set(mepa_device_t *dev, const mepa_ts_scaled_ppb_t *const adj)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_clock_rateadj_set(data->inst, data->port_no, adj);
}
static mepa_rc vtss_ts_clock_adj1ns(mepa_device_t *dev, const mepa_bool_t incr)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_ptptime_adj1ns(data->inst, data->port_no, incr);
}

static mepa_rc vtss_ts_rx_clock_conf_get (mepa_device_t *dev, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    mesa_phy_ts_engine_action_t action_conf;
    mesa_phy_ts_engine_t eng_id = 0;
    mepa_rc rc = MESA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)dev->data;
    rc =  mesa_phy_ts_ingress_engine_action_get(data->inst, data->port_no, eng_id, &action_conf);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    ptpclock_conf->delaym_type = action_conf.action.ptp_conf[0].delaym_type;
    ptpclock_conf->clk_mode  = action_conf.action.ptp_conf[0].clk_mode;
    ptpclock_conf->cf_update = action_conf.action.ptp_conf[0].cf_update;
    return rc;
}

static mepa_rc vtss_ts_tx_clock_conf_get(mepa_device_t *dev, uint16_t clock_id, mepa_ts_ptp_clock_conf_t *const ptpclock_conf)
{
    mesa_phy_ts_engine_action_t action_conf;
    mesa_phy_ts_engine_t eng_id = 0;
    mepa_rc rc = MESA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)dev->data;
    rc =  mesa_phy_ts_egress_engine_action_get(data->inst, data->port_no, eng_id, &action_conf);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    ptpclock_conf->delaym_type = action_conf.action.ptp_conf[0].delaym_type;
    ptpclock_conf->clk_mode  = action_conf.action.ptp_conf[0].clk_mode;
    ptpclock_conf->cf_update = action_conf.action.ptp_conf[0].cf_update;
    return rc;
}

static mepa_rc vtss_ts_rx_clock_conf_set(mepa_device_t *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    mesa_phy_ts_engine_action_t action_conf;
    mesa_phy_ts_engine_t eng_id = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    action_conf.action.ptp_conf[0].clk_mode = ptpclock_conf->clk_mode;
    action_conf.action.ptp_conf[0].delaym_type = ptpclock_conf->delaym_type;
    action_conf.action.ptp_conf[0].cf_update = ptpclock_conf->cf_update;

    return mesa_phy_ts_ingress_engine_action_set(data->inst, data->port_no, eng_id, &action_conf);
}

static mepa_rc vtss_ts_tx_clock_conf_set(mepa_device_t *dev, uint16_t clock_id, const mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{
    mesa_phy_ts_engine_action_t action_conf;
    mesa_phy_ts_engine_t eng_id = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    action_conf.action.ptp_conf[0].clk_mode = ptpclock_conf->clk_mode;
    action_conf.action.ptp_conf[0].delaym_type = ptpclock_conf->delaym_type;
    action_conf.action.ptp_conf[0].cf_update = ptpclock_conf->cf_update;

    return mesa_phy_ts_egress_engine_action_set(data->inst, data->port_no, eng_id, &action_conf);
}

static mepa_rc vtss_ts_pps_conf_get (mepa_device_t *dev, mepa_ts_pps_conf_t *const phy_pps_conf)
{

    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_phy_ts_pps_conf_t pps_conf;
    mesa_rc rc;

    if ((rc =  mesa_phy_ts_pps_conf_get(data->inst, data->port_no, &pps_conf)) == MESA_RC_OK) {
        phy_pps_conf->pps_width_adj = pps_conf.pps_width_adj;
        phy_pps_conf->pps_offset = pps_conf.pps_offset;
        phy_pps_conf->pps_output_enable = pps_conf.pps_output_enable;
        return MEPA_RC_OK;
    } else {
        return MEPA_RC_ERROR;
    }
}

static mepa_rc vtss_ts_pps_conf_set (mepa_device_t *dev, const mepa_ts_pps_conf_t *const phy_pps_conf)
{

    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_phy_ts_pps_conf_t pps_conf;

    pps_conf.pps_width_adj = phy_pps_conf->pps_width_adj;
    pps_conf.pps_offset = phy_pps_conf->pps_offset;
    pps_conf.pps_output_enable = phy_pps_conf->pps_output_enable;
    return mesa_phy_ts_pps_conf_set(data->inst, data->port_no, &pps_conf);
}

mepa_rc vtss_ts_stats_get(mepa_device_t *dev, mepa_ts_stats_t *const statistics)
{

    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_phy_ts_stats_t stats;
    mesa_rc rc;

    if ((rc = mesa_phy_ts_stats_get(data->inst, data->port_no, &stats)) == MESA_RC_OK) {
        statistics->ingr_pream_shrink_err = stats.ingr_pream_shrink_err;
        statistics->egr_pream_shrink_err = stats.egr_pream_shrink_err;
        statistics->ingr_fcs_err         = stats.ingr_fcs_err;
        statistics->egr_fcs_err          = stats.egr_fcs_err;
        statistics->ingr_frm_mod_cnt     = stats.ingr_frm_mod_cnt;
        statistics->egr_frm_mod_cnt      = stats.egr_frm_mod_cnt;
        statistics->ts_fifo_tx_cnt       = stats.ts_fifo_tx_cnt;
        statistics->ts_fifo_drop_cnt     = stats.ts_fifo_drop_cnt;
        return MEPA_RC_OK;
    } else {
        return MEPA_RC_ERROR;
    }
}

static mepa_rc vtss_ts_event_get (mepa_device_t *dev,
                                  mepa_ts_event_t *const ev_mask)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    return mesa_phy_ts_event_enable_get(data->inst, data->port_no, ev_mask);
}

static mepa_rc vtss_ts_event_set (mepa_device_t *dev, const mepa_bool_t enable, const mepa_ts_event_t ev_mask)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    return mesa_phy_ts_event_enable_set(data->inst, data->port_no, enable, ev_mask);
}

static mepa_rc vtss_ts_event_poll(mepa_device_t *dev, mepa_ts_event_t  *const status)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return mesa_phy_ts_event_poll(data->inst, data->port_no, status);

}

mepa_ts_driver_t vtss_ts_drivers = {
    .mepa_ts_init_conf_get          = vtss_ts_init_conf_get,
    .mepa_ts_init_conf_set          = vtss_ts_init_conf_set,
    .mepa_ts_mode_get               = vtss_ts_mode_get,
    .mepa_ts_mode_set               = vtss_ts_mode_set,
    .mepa_ts_ltc_ls_en              = vtss_ts_ltc_ls_en_set,
    .mepa_ts_ltc_get                = vtss_ts_ltc_get,
    .mepa_ts_ltc_set                = vtss_ts_ltc_set,
    .mepa_ts_clock_rateadj_get      = vtss_ts_clock_rateadj_get,
    .mepa_ts_clock_rateadj_set      = vtss_ts_clock_rateadj_set,
    .mepa_ts_clock_adj1ns           = vtss_ts_clock_adj1ns,
    .mepa_ts_delay_asymmetry_get    = vtss_ts_clock_delay_asymmetry_get,
    .mepa_ts_delay_asymmetry_set    = vtss_ts_clock_delay_asymmetry_set,
    .mepa_ts_path_delay_get         = vtss_ts_clock_path_delay_get,
    .mepa_ts_path_delay_set         = vtss_ts_clock_path_delay_set,
    .mepa_ts_egress_latency_get     = vtss_ts_clock_egress_latency_get,
    .mepa_ts_egress_latency_set     = vtss_ts_clock_egress_latency_set,
    .mepa_ts_ingress_latency_get    = vtss_ts_clock_ingress_latency_get,
    .mepa_ts_ingress_latency_set    = vtss_ts_clock_ingress_latency_set,
    .mepa_ts_rx_clock_conf_get      = vtss_ts_rx_clock_conf_get,
    .mepa_ts_tx_clock_conf_get      = vtss_ts_tx_clock_conf_get,
    .mepa_ts_rx_clock_conf_set      = vtss_ts_rx_clock_conf_set,
    .mepa_ts_tx_clock_conf_set      = vtss_ts_tx_clock_conf_set,
    .mepa_ts_pps_conf_get           = vtss_ts_pps_conf_get,
    .mepa_ts_pps_conf_set           = vtss_ts_pps_conf_set,
    .mepa_ts_stats_get              = vtss_ts_stats_get,
    .mepa_ts_event_get              = vtss_ts_event_get,
    .mepa_ts_event_set              = vtss_ts_event_set,
    .mepa_ts_event_poll             = vtss_ts_event_poll,
};

mepa_drivers_t mepa_mscc_driver_init()
{
    static const int nr_mscc_phy = 3;
    static mepa_driver_t mscc_drivers[] = {
        {
            // VTSS Atom PHY
            .id = 0x000706e0,
            .mask = 0xffffffe0,
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
            .mepa_driver_synce_clock_conf_set = phy_1g_synce_clk_conf_set,
            .mepa_driver_phy_info_get = phy_1g_info_get,
        },
        {
            // VTSS (all other models)
            .id = 0x00070400,
            .mask = 0xfffffc00,
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
            .mepa_driver_synce_clock_conf_set = phy_1g_synce_clk_conf_set,
            .mepa_driver_phy_info_get = phy_1g_info_get,
        },
        {
            // Cicada (all models)
            .id = 0x000FC400,
            .mask = 0xfffffc00,
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
            .mepa_driver_synce_clock_conf_set = phy_1g_synce_clk_conf_set,
            .mepa_driver_phy_info_get = phy_1g_info_get,
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
            .mepa_driver_phy_info_get = phy_10g_info_get,
            .mepa_ts = &vtss_ts_drivers,
        }
    };

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
        .mepa_driver_phy_info_get = phy_10g_info_get,
        .mepa_ts = &vtss_ts_drivers,
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
        .mepa_driver_synce_clock_conf_set = phy_1g_synce_clk_conf_set,
        .mepa_driver_phy_info_get = phy_1g_info_get,
    }};

    mepa_drivers_t result;
    result.phy_drv = default_drivers;
    result.count = nr_default_drivers;

    return result;
}
