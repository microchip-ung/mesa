// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <mscc/ethernet/board/api.h>
#include "../meba_aux.h"
#include "../meba_generic.h"

typedef struct {
    mesa_inst_t inst;
    mesa_port_no_t port_no;
    mesa_port_interface_t mac_if;
} phy_data_t;

static mesa_rc mscc_1g_delete(meba_phy_device_t *dev) {
    phy_data_t *data = (phy_data_t *)dev->data;
    free(data);
    free(dev);
    dev = NULL;
    return MESA_RC_OK;
}

static mesa_rc reset_phy(phy_data_t *data, mesa_phy_reset_conf_t *conf) {
    mesa_phy_event_t events;

    MEBA_RC(mesa_phy_event_enable_get(data->inst, data->port_no, &events));
    MEBA_RC(mesa_phy_reset(data->inst, data->port_no, conf));
    return mesa_phy_event_enable_set(data->inst, data->port_no, events, true);
}

static mesa_rc mscc_1g_reset(meba_phy_device_t *dev,
                             mesa_phy_media_interface_t media_if) {
    mesa_phy_reset_conf_t conf = {};
    phy_data_t *data = (phy_data_t *)(dev->data);

    mesa_phy_reset_get(data->inst, data->port_no, &conf);
    conf.force = MESA_PHY_FORCE_RESET;
    conf.mac_if = data->mac_if;
    conf.media_if = media_if;
    conf.i_cpu_en = false;

    return reset_phy(data, &conf);
}

static mesa_rc mscc_1g_atom_reset(meba_phy_device_t *dev,
                                  mesa_phy_media_interface_t media_if) {
    mesa_phy_reset_conf_t conf = {};
    phy_data_t *data = (phy_data_t *)(dev->data);

    mesa_phy_reset_get(data->inst, data->port_no, &conf);
    conf.force = MESA_PHY_FORCE_RESET;
    conf.mac_if = data->mac_if;
    conf.media_if = media_if;
    conf.i_cpu_en = false;

    return reset_phy(data, &conf);
}

static mesa_rc mscc_1g_poll(meba_phy_device_t *dev,
                            meba_phy_driver_status_t *status) {
    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_port_status_t mesa_status = {};

    mesa_rc rc = mesa_phy_status_get(data->inst, data->port_no, &mesa_status);
    if (rc != MESA_RC_OK) return rc;

    // fill up status
    status->link = mesa_status.link;
    status->speed = mesa_status.speed;
    status->fdx = mesa_status.fdx;
    status->aneg = mesa_status.aneg;
    status->copper = mesa_status.copper;
    status->fiber = mesa_status.fiber;

    return MESA_RC_OK;
}

static mesa_rc mscc_1g_conf_set(meba_phy_device_t *dev, meba_port_cap_t cap,
                                const meba_phy_driver_conf_t *config) {
    phy_data_t *data = (phy_data_t *)dev->data;
    mesa_phy_conf_t phy_config = {};

    phy_config.mdi = MESA_PHY_MDIX_AUTO;
    if (config->admin.enable) {
        if (config->speed == MESA_SPEED_AUTO ||
            config->speed == MESA_SPEED_1G) {
            phy_config.mode = MESA_PHY_MODE_ANEG;

            phy_config.aneg.speed_2g5_fdx =
                config->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_2_5G_FDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_2500M);
            phy_config.aneg.speed_5g_fdx =
                config->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_5G_FDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_5G);
            phy_config.aneg.speed_10g_fdx =
                config->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10G_FDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_10G);
            phy_config.aneg.speed_10m_hdx =
                config->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10M_HDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_HDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_10M);
            phy_config.aneg.speed_10m_fdx =
                config->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_10M_FDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_FDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_10M);
            phy_config.aneg.speed_100m_hdx =
                config->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_100M_HDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_HDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_100M);
            phy_config.aneg.speed_100m_fdx =
                config->speed == MESA_SPEED_AUTO &&
                (cap & MEBA_PORT_CAP_100M_FDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_FDX) &&
                !(config->adv_dis & MEBA_PHY_ADV_DIS_100M);
            phy_config.aneg.speed_1g_fdx =
                ((cap & MEBA_PORT_CAP_1G_FDX) &&
                 !(config->speed == MESA_SPEED_AUTO &&
                   (config->adv_dis & MEBA_PHY_ADV_DIS_1G)));
            phy_config.aneg.no_restart_aneg =
                   !!(config->adv_dis & MEBA_PHY_ADV_DIS_RESTART_ANEG);

            // We don't support 1G half duplex
            phy_config.aneg.speed_1g_hdx = false;
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

    return mesa_phy_conf_set(data->inst, data->port_no, &phy_config);
}

static mesa_rc mscc_1g_if_get(meba_phy_device_t *dev, mesa_port_speed_t speed,
                              mesa_port_interface_t *mac_if) {
    phy_data_t *data = (phy_data_t *)dev->data;

    *mac_if = data->mac_if;
    return MESA_RC_OK;
}

static mesa_rc mscc_1g_power_set(meba_phy_device_t *dev,
                                 mesa_phy_power_mode_t power) {
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_power_conf_t power_conf = {};
    power_conf.mode = power;
    return mesa_phy_power_conf_set(data->inst, data->port_no, &power_conf);
}

static mesa_rc mscc_1g_veriphy_start(meba_phy_device_t *dev, int mode) {
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_veriphy_start(data->inst, data->port_no, mode);
}

static mesa_rc mscc_1g_veriphy_get(meba_phy_device_t *dev,
                                   mesa_phy_veriphy_result_t *res) {
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_veriphy_get(data->inst, data->port_no, res);
}

static mesa_rc mscc_1g_media_set(meba_phy_device_t *dev,
                                 mesa_phy_media_interface_t phy_media_if) {
    phy_data_t *data = (phy_data_t *)(dev->data);
    mesa_phy_reset_conf_t conf = {};
    mesa_phy_reset_get(data->inst, data->port_no, &conf);

    conf.mac_if = data->mac_if;
    conf.media_if = phy_media_if;

    return mesa_phy_reset(data->inst, data->port_no, &conf);
}

static meba_phy_device_t *mscc_1g_probe(meba_phy_driver_t *drv,
                                        const meba_phy_driver_address_t *mode) {
    if (mode->mode != mscc_phy_driver_address_mode) return NULL;

    meba_phy_device_t *device =
        (meba_phy_device_t *)calloc(1, sizeof(meba_phy_device_t));

    if (device == NULL) goto out_device;

    phy_data_t *data = (phy_data_t *)calloc(1, sizeof(phy_data_t));

    if (data == NULL) goto out_data;

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

static mesa_rc mscc_1g_status_1g_get(meba_phy_device_t    *dev,
                                     mesa_phy_status_1g_t *status) {
    phy_data_t *data = (phy_data_t *)(dev->data);
    return mesa_phy_status_1g_get(data->inst, data->port_no, status);
}

typedef struct malibu_10g_phy_data {
    mesa_inst_t inst;
    mesa_port_no_t port_no;
    mesa_port_interface_t mac_if;
} malibu_10g_phy_data_t;

static mesa_rc phy_10g_delete(meba_phy_device_t *dev) {
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)dev->data;
    free(data);
    free(dev);
    dev = NULL;
    return MESA_RC_OK;
}

static mesa_rc malibu_10g_reset(meba_phy_device_t *dev,
                                mesa_phy_media_interface_t intf) {
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

static mesa_rc venice_10g_reset(meba_phy_device_t *dev,
                                mesa_phy_media_interface_t intf) {
    mesa_phy_10g_mode_t oper_mode = {};
    mesa_phy_10g_id_t phy_10g_id;
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)(dev->data);
    oper_mode.oper_mode = MESA_PHY_LAN_MODE;
    if (mesa_phy_10g_id_get(PHY_INST, data->port_no, &phy_10g_id) == MESA_RC_OK) {
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


static mesa_rc phy_10g_poll(meba_phy_device_t *dev,
                               meba_phy_driver_status_t *status) {
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)(dev->data);
    mesa_port_status_t mesa_status = {};

    mesa_rc rc = mesa_port_status_get(data->inst, data->port_no, &mesa_status);
    if (rc != MESA_RC_OK) return rc;

    status->link = mesa_status.link;
    status->speed = mesa_status.speed;
    status->fdx = mesa_status.fdx;

    return MESA_RC_OK;
}

static mesa_rc phy_10g_conf_set(meba_phy_device_t *dev, meba_port_cap_t cap,
                                   const meba_phy_driver_conf_t *config) {
    malibu_10g_phy_data_t *data = (malibu_10g_phy_data_t *)dev->data;
    mesa_phy_10g_mode_t mode = {};

    if (mesa_phy_10g_mode_get(data->inst, data->port_no, &mode) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }

    mesa_port_speed_t speed =
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
                MESA_RC_OK)
                return MESA_RC_ERROR;
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
                                               &ctrl) != MESA_RC_OK)
            return MESA_RC_ERROR;

        mesa_port_clause_37_control_t port_ctrl;
        port_ctrl.enable = false;
        mesa_port_clause_37_control_set(data->inst, data->port_no, &port_ctrl);
    } else {
        mode.xaui_lane_flip = false;
        mode.oper_mode = MESA_PHY_LAN_MODE;
        if (mesa_phy_10g_mode_set(data->inst, data->port_no, &mode) !=
            MESA_RC_OK)
            return MESA_RC_ERROR;
    }

    return MESA_RC_OK;
}

static mesa_rc malibu_10g_if_get(meba_phy_device_t *dev,
                                 mesa_port_speed_t speed,
                                 mesa_port_interface_t *mac_if) {
    switch (speed) {
        case MESA_SPEED_AUTO:
        case MESA_SPEED_1G:
            *mac_if = MESA_PORT_INTERFACE_SERDES;
            break;
        default:
            *mac_if = MESA_PORT_INTERFACE_SFI;
            break;
    }
    return MESA_RC_OK;
}

static mesa_rc venice_10g_if_get(meba_phy_device_t *dev,
                                 mesa_port_speed_t speed,
                                 mesa_port_interface_t *mac_if) {
    switch (speed) {
        case MESA_SPEED_AUTO:
        case MESA_SPEED_1G:
            *mac_if = MESA_PORT_INTERFACE_SERDES;
            break;
        default:
            *mac_if = MESA_PORT_INTERFACE_XAUI;
            break;
    }
    return MESA_RC_OK;

}
static mesa_rc phy_10g_mt_get(meba_phy_device_t *dev,
                              mesa_sd10g_media_type_t *mt) {
    *mt = MESA_SD10G_MEDIA_SR;
    return MESA_RC_OK;
}

static meba_phy_device_t *phy_10g_probe(
    meba_phy_driver_t *drv, const meba_phy_driver_address_t *mode) {
    if (mode->mode != mscc_phy_driver_address_mode) return NULL;

    meba_phy_device_t *device =
        (meba_phy_device_t *)calloc(1, sizeof(meba_phy_device_t));

    if (device == NULL) goto out_device;

    malibu_10g_phy_data_t *data =
        (malibu_10g_phy_data_t *)calloc(1, sizeof(malibu_10g_phy_data_t));

    if (data == NULL) goto out_data;

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

meba_phy_drivers_t meba_mscc_driver_init() {
    static const int nr_mscc_phy = 4;
    static meba_phy_driver_t mscc_drivers[] = {
        {
            .id = 0x00070400,
            .mask = 0x02fffc00,
            .meba_phy_driver_delete = mscc_1g_delete,
            .meba_phy_driver_reset = mscc_1g_reset,
            .meba_phy_driver_poll = mscc_1g_poll,
            .meba_phy_driver_conf_set = mscc_1g_conf_set,
            .meba_phy_driver_if_get = mscc_1g_if_get,
            .meba_phy_driver_mt_get = NULL,
            .meba_phy_driver_power_set = mscc_1g_power_set,
            .meba_phy_driver_veriphy_start = mscc_1g_veriphy_start,
            .meba_phy_driver_veriphy_get = mscc_1g_veriphy_get,
            .meba_phy_driver_media_set = mscc_1g_media_set,
            .meba_phy_driver_probe = mscc_1g_probe,
            .meba_phy_driver_status_1g_get = mscc_1g_status_1g_get,
        },
        // Atom - QSGMII family
        {
            .id = 0x000706e0,
            .mask = 0x02ffFFe0,
            .meba_phy_driver_delete = mscc_1g_delete,
            .meba_phy_driver_reset = mscc_1g_atom_reset,
            .meba_phy_driver_poll = mscc_1g_poll,
            .meba_phy_driver_conf_set = mscc_1g_conf_set,
            .meba_phy_driver_if_get = mscc_1g_if_get,
            .meba_phy_driver_mt_get = NULL,
            .meba_phy_driver_power_set = mscc_1g_power_set,
            .meba_phy_driver_veriphy_start = mscc_1g_veriphy_start,
            .meba_phy_driver_veriphy_get = mscc_1g_veriphy_get,
            .meba_phy_driver_media_set = mscc_1g_media_set,
            .meba_phy_driver_probe = mscc_1g_probe,
            .meba_phy_driver_status_1g_get = mscc_1g_status_1g_get,
        },
        // Atom - SGMII
        {
            .id = 0x706d1,
            .mask = 0xFFffFFff,
            .meba_phy_driver_delete = mscc_1g_delete,
            .meba_phy_driver_reset = mscc_1g_reset,
            .meba_phy_driver_poll = mscc_1g_poll,
            .meba_phy_driver_conf_set = mscc_1g_conf_set,
            .meba_phy_driver_if_get = mscc_1g_if_get,
            .meba_phy_driver_mt_get = NULL,
            .meba_phy_driver_power_set = mscc_1g_power_set,
            .meba_phy_driver_veriphy_start = mscc_1g_veriphy_start,
            .meba_phy_driver_veriphy_get = mscc_1g_veriphy_get,
            .meba_phy_driver_media_set = mscc_1g_media_set,
            .meba_phy_driver_probe = mscc_1g_probe,
            .meba_phy_driver_status_1g_get = mscc_1g_status_1g_get,
        },
        {
            .id = 0x000FC400,
            .mask = 0x02fffc00,
            .meba_phy_driver_delete = mscc_1g_delete,
            .meba_phy_driver_reset = mscc_1g_reset,
            .meba_phy_driver_poll = mscc_1g_poll,
            .meba_phy_driver_conf_set = mscc_1g_conf_set,
            .meba_phy_driver_if_get = mscc_1g_if_get,
            .meba_phy_driver_mt_get = NULL,
            .meba_phy_driver_power_set = mscc_1g_power_set,
            .meba_phy_driver_veriphy_start = mscc_1g_veriphy_start,
            .meba_phy_driver_veriphy_get = mscc_1g_veriphy_get,
            .meba_phy_driver_media_set = mscc_1g_media_set,
            .meba_phy_driver_probe = mscc_1g_probe,
            .meba_phy_driver_status_1g_get = mscc_1g_status_1g_get,
        }};

    meba_phy_drivers_t result;
    result.phy_drv = mscc_drivers;
    result.count = nr_mscc_phy;

    return result;
}

meba_phy_drivers_t meba_malibu_driver_init() {
    static const int nr_malibu_phy = 1;
    static meba_phy_driver_t malibu_drivers[] = {{
        .id = 0x8200,
        .mask = 0x0000FF00,
        .meba_phy_driver_delete = phy_10g_delete,
        .meba_phy_driver_reset = malibu_10g_reset,
        .meba_phy_driver_poll = phy_10g_poll,
        .meba_phy_driver_conf_set = phy_10g_conf_set,
        .meba_phy_driver_if_get = malibu_10g_if_get,
        .meba_phy_driver_mt_get = phy_10g_mt_get,
        .meba_phy_driver_power_set = NULL,
        .meba_phy_driver_veriphy_start = NULL,
        .meba_phy_driver_veriphy_get = NULL,
        .meba_phy_driver_media_set = NULL,
        .meba_phy_driver_probe = phy_10g_probe,
        .meba_phy_driver_status_1g_get = NULL,
    }};

    meba_phy_drivers_t result;
    result.phy_drv = malibu_drivers;
    result.count = nr_malibu_phy;

    return result;
}

meba_phy_drivers_t meba_venice_driver_init() {
    static const int nr_venice_phy = 1;
    static meba_phy_driver_t venice_drivers[] = {{
        .id = 0x8400,
        .mask = 0x0000FF00,
        .meba_phy_driver_delete = phy_10g_delete,
        .meba_phy_driver_reset = venice_10g_reset,
        .meba_phy_driver_poll = phy_10g_poll,
        .meba_phy_driver_conf_set = phy_10g_conf_set,
        .meba_phy_driver_if_get = venice_10g_if_get,
        .meba_phy_driver_mt_get = phy_10g_mt_get,
        .meba_phy_driver_power_set = NULL,
        .meba_phy_driver_veriphy_start =NULL,
        .meba_phy_driver_veriphy_get =NULL,
        .meba_phy_driver_media_set = NULL,
        .meba_phy_driver_probe = phy_10g_probe,
        .meba_phy_driver_status_1g_get = NULL,
    }};

    meba_phy_drivers_t result;
    result.phy_drv = venice_drivers;
    result.count = nr_venice_phy;

    return result;
}

meba_phy_drivers_t meba_default_phy_driver_init() {
    static const int nr_default_drivers = 1;
    static meba_phy_driver_t default_drivers[] = {{
        .id = 0x0,
        .mask = 0x00,
        .meba_phy_driver_delete = mscc_1g_delete,
        .meba_phy_driver_reset = mscc_1g_reset,
        .meba_phy_driver_poll = mscc_1g_poll,
        .meba_phy_driver_conf_set = mscc_1g_conf_set,
        .meba_phy_driver_if_get = mscc_1g_if_get,
        .meba_phy_driver_mt_get = NULL,
        .meba_phy_driver_power_set = mscc_1g_power_set,
        .meba_phy_driver_veriphy_start = mscc_1g_veriphy_start,
        .meba_phy_driver_veriphy_get = mscc_1g_veriphy_get,
        .meba_phy_driver_media_set = mscc_1g_media_set,
        .meba_phy_driver_probe = mscc_1g_probe,
        .meba_phy_driver_status_1g_get = mscc_1g_status_1g_get,
    }};

    meba_phy_drivers_t result;
    result.phy_drv = default_drivers;
    result.count = nr_default_drivers;

    return result;
}
