// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>
#include <vtss_phy_api.h>
#include "vtss_private.h"

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

#include "common/vtss_phy_common.h"

extern mepa_ts_driver_t vtss_ts_drivers;

static vtss_inst_t vtss_inst;
static int vtss_inst_cnt;
static const mepa_callout_t *CALLOUT;

// MIIM/MMD wrapper functions
static vtss_rc miim_read(const vtss_inst_t    inst,
                         const vtss_port_no_t port_no,
                         const u8             addr,
                         u16                  *const value)
{
    return CALLOUT->miim_read(inst->callout_cxt[port_no], addr, value);
}

static vtss_rc miim_write(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          const u8             addr,
                          const u16            value)
{
    return CALLOUT->miim_write(inst->callout_cxt[port_no], addr, value);
}

static vtss_rc mmd_read(const vtss_inst_t    inst,
                        const vtss_port_no_t port_no,
                        const u8             mmd,
                        const u16            addr,
                        u16                  *const value)
{
    return CALLOUT->mmd_read(inst->callout_cxt[port_no], mmd, addr, value);
}

static vtss_rc mmd_read_inc(const vtss_inst_t    inst,
                            const vtss_port_no_t port_no,
                            const u8             mmd,
                            const u16            addr,
                            u16                  *const buf,
                            u8                   cnt)
{
    return CALLOUT->mmd_read_inc(inst->callout_cxt[port_no], mmd, addr, buf,
                                  cnt);
}

static vtss_rc mmd_write(const vtss_inst_t    inst,
                         const vtss_port_no_t port_no,
                         const u8             mmd,
                         const u16            addr,
                         const u16            value)
{
    return CALLOUT->mmd_write(inst->callout_cxt[port_no], mmd, addr, value);
}

static void lock_enter(const vtss_phy_lock_t *const lock)
{
    mepa_lock_t mepa_lock;

    if (CALLOUT->lock_enter) {
        mepa_lock.function = lock->function;
        mepa_lock.file = lock->file;
        mepa_lock.line = lock->line;
        CALLOUT->lock_enter(&mepa_lock);
    }
}

static void lock_exit(const vtss_phy_lock_t *const lock)
{
    mepa_lock_t mepa_lock;

    if (CALLOUT->lock_exit) {
        mepa_lock.function = lock->function;
        mepa_lock.file = lock->file;
        mepa_lock.line = lock->line;
        CALLOUT->lock_exit(&mepa_lock);
    }
}

static void trace_func(const vtss_phy_trace_group_t group,
                       const vtss_phy_trace_level_t level,
                       const char                   *location,
                       const int                    line,
                       const char                   *format,
                       ...)
{
    mepa_trace_data_t data = {
        .location = location,
        .line = line,
        .format = format,
    };

    va_list args;

    if (MEPA_TRACE_FUNCION) {
        // Map from VTSS to MEPA trace group/level
        data.group = (group == VTSS_PHY_TRACE_GROUP_TS ? MEPA_TRACE_GRP_TS : MEPA_TRACE_GRP_GEN);
        data.level = (level == VTSS_PHY_TRACE_LEVEL_ERROR ? MEPA_TRACE_LVL_ERROR :
                      level == VTSS_PHY_TRACE_LEVEL_INFO ? MEPA_TRACE_LVL_INFO :
                      level == VTSS_PHY_TRACE_LEVEL_DEBUG ? MEPA_TRACE_LVL_DEBUG :
                      MEPA_TRACE_LVL_NOISE);


        va_start(args, format);
        MEPA_TRACE_FUNCION(&data, args);
        va_end(args);
    }
}

static mepa_rc mscc_vtss_create(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                struct mepa_callout_cxt MEPA_SHARED_PTR *callout_cxt,
                                struct mepa_board_conf              *board_conf)
{
    vtss_phy_init_conf_t conf;

    // Check that port does not exceed PHY instance maximum
    if (board_conf->numeric_handle >= VTSS_PORTS) {
        return MEPA_RC_ERROR;
    }

    // Check that PHY instance can be created
    if (vtss_inst_cnt == 0) {
        if (vtss_phy_inst_create(&vtss_inst) != VTSS_RC_OK ||
            vtss_phy_init_conf_get(NULL, &conf) != VTSS_RC_OK) {
            return MEPA_RC_ERROR;
        }
        CALLOUT = callout;
        conf.miim_read = miim_read;
        conf.miim_write = miim_write;
        conf.mmd_read = mmd_read;
        conf.mmd_read_inc = mmd_read_inc;
        conf.mmd_write = mmd_write;
        conf.lock_enter = lock_enter;
        conf.lock_exit = lock_exit;
        conf.trace_func = trace_func;
        (void)vtss_phy_init_conf_set(NULL, &conf);
    }

    if (vtss_phy_callout_set(NULL, board_conf->numeric_handle, callout_cxt) == MEPA_RC_OK) {
        vtss_inst_cnt++;
    } else {
        return MEPA_RC_ERROR;
    }


    return MEPA_RC_OK;
}

static mepa_rc mscc_vtss_destroy(void)
{
    if (vtss_inst_cnt) {
        vtss_inst_cnt--;
        if (vtss_inst_cnt == 0 && vtss_phy_inst_destroy(vtss_inst) != VTSS_RC_OK) {
            return MEPA_RC_ERROR;
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc mscc_1g_delete(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    free(data);
    free(dev);
    dev = NULL;
    return mscc_vtss_destroy();
}

static mepa_rc reset_phy(phy_data_t *data, vtss_phy_reset_conf_t *conf)
{
    mepa_event_t events;

    MEPA_RC(vtss_phy_event_enable_get(NULL, data->port_no, &events));
    MEPA_RC(vtss_phy_reset(NULL, data->port_no, conf));
    return vtss_phy_event_enable_set(NULL, data->port_no, events, 1);
}

static mepa_rc mscc_1g_reset(mepa_device_t *dev,
                             const mepa_reset_param_t *rst_conf)
{
    vtss_phy_reset_conf_t conf = {};
    phy_data_t *data = (phy_data_t *)(dev->data);
    mepa_rc rc = MEPA_RC_OK;

    if (rst_conf->reset_point == MEPA_RESET_POINT_PRE) {
        // pre reset api should be called on base port
        rc = vtss_phy_pre_reset(NULL, data->port_no);
    } else if (rst_conf->reset_point == MEPA_RESET_POINT_POST) {
        // post reset api should be called on base port
        rc = vtss_phy_post_reset(NULL, data->port_no);
    } else if (rst_conf->reset_point == MEPA_RESET_POINT_DEFAULT) {
        vtss_phy_reset_get(NULL, data->port_no, &conf);
        conf.force = VTSS_PHY_FORCE_RESET;
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
    vtss_phy_reset_conf_t conf = {};
    phy_data_t *data = (phy_data_t *)(dev->data);

    vtss_phy_reset_get(NULL, data->port_no, &conf);
    conf.force = VTSS_PHY_FORCE_RESET;
    conf.mac_if = data->mac_if;
    conf.media_if = rst_conf->media_intf;
    conf.i_cpu_en = 0;

    return reset_phy(data, &conf);
}

static mepa_rc mscc_1g_poll(mepa_device_t *dev,
                            mepa_status_t *status)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_port_status_t mesa_status = {};

    mepa_rc rc = vtss_phy_status_get(NULL, data->port_no, &mesa_status);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    // fill up status
    status->link = mesa_status.link;
    status->speed = mesa_status.speed;
    status->fdx = mesa_status.fdx;
    status->aneg.obey_pause = mesa_status.aneg.obey_pause;
    status->aneg.generate_pause = mesa_status.aneg.generate_pause;
    status->copper = mesa_status.copper;
    status->fiber = mesa_status.fiber;

    return MEPA_RC_OK;
}

static mepa_rc mscc_1g_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_conf_t phy_config = {}, cur_conf;
    vtss_phy_conf_1g_t cfg_neg = {};

    phy_config.mdi = VTSS_PHY_MDIX_AUTO;
    if (config->admin.enable) {
        if (config->speed == MESA_SPEED_AUTO ||
            config->speed == MESA_SPEED_1G) {
            phy_config.mode = VTSS_PHY_MODE_ANEG;

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
            (void)vtss_phy_conf_1g_set(NULL, data->port_no, &cfg_neg);
        } else {
            phy_config.mode = VTSS_PHY_MODE_FORCED;
            phy_config.forced.speed = config->speed;
            phy_config.forced.fdx = config->fdx;
        }
    } else {
        phy_config.mode = VTSS_PHY_MODE_POWER_DOWN;
    }
    phy_config.mac_if_pcs.serdes_aneg_ena = config->mac_if_aneg_ena;
    if (vtss_phy_conf_get(NULL, data->port_no, &cur_conf) == MESA_RC_OK) {
        if (phy_config.mac_if_pcs.serdes_aneg_ena && (cur_conf.mac_if_pcs.serdes_aneg_ena != phy_config.mac_if_pcs.serdes_aneg_ena)) {
            phy_config.mac_if_pcs.aneg_restart = true;
        }
    }
    return vtss_phy_conf_set(NULL, data->port_no, &phy_config);
}

static mepa_rc phy_1g_conf_get(mepa_device_t *dev, mepa_conf_t *const conf)
{
    vtss_phy_conf_t phy_conf;
    vtss_phy_conf_1g_t cfg_neg = {};
    phy_data_t *data = (phy_data_t *)dev->data;
    *conf = (const mepa_conf_t){};

    if (vtss_phy_conf_get(NULL, data->port_no, &phy_conf) == MESA_RC_OK) {
        if (phy_conf.mode == VTSS_PHY_MODE_ANEG) {
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
            if (vtss_phy_conf_1g_get(NULL, data->port_no, &cfg_neg) == MESA_RC_OK) {
                conf->man_neg = !cfg_neg.master.cfg ? MEPA_MANUAL_NEG_DISABLED :
                                cfg_neg.master.val ? MEPA_MANUAL_NEG_REF : MEPA_MANUAL_NEG_CLIENT;
            }
        } else if (phy_conf.mode == VTSS_PHY_MODE_FORCED) {
            conf->speed = phy_conf.forced.speed;
            conf->fdx = phy_conf.forced.fdx;
        }
        conf->mac_if_aneg_ena = phy_conf.mac_if_pcs.serdes_aneg_ena;
        conf->admin.enable = phy_conf.mode != VTSS_PHY_MODE_POWER_DOWN ? true : false;
    }
    return MEPA_RC_OK;
}

static mepa_rc mscc_if_set(mepa_device_t *dev,
                           mepa_port_interface_t mac_if)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    // TODO, check that the configured interface is supported!
    data->mac_if = mac_if;
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
    vtss_phy_power_conf_t power_conf = {};
    power_conf.mode = power;
    return vtss_phy_power_conf_set(NULL, data->port_no, &power_conf);
}

static mepa_rc mscc_1g_veriphy_start(mepa_device_t *dev, int mode)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return vtss_phy_veriphy_start(NULL, data->port_no, mode);
}

static mepa_rc mscc_1g_veriphy_get(mepa_device_t *dev,
                                   mepa_cable_diag_result_t *res)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    vtss_phy_veriphy_result_t result;
    mepa_rc rc;

    if ((rc = vtss_phy_veriphy_get(NULL, data->port_no, &result)) != MEPA_RC_ERROR) {
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
    vtss_phy_reset_conf_t conf = {};
    vtss_phy_reset_get(NULL, data->port_no, &conf);

    conf.mac_if = data->mac_if;
    conf.media_if = phy_media_if;

    return vtss_phy_reset(NULL, data->port_no, &conf);
}

static mepa_device_t *mscc_1g_probe(mepa_driver_t *drv,
                                    const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                    struct mepa_callout_cxt MEPA_SHARED_PTR *callout_cxt,
                                    struct mepa_board_conf              *board_conf)
{
    int i;

    if (mscc_vtss_create(callout, callout_cxt, board_conf) != MEPA_RC_OK) {
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

    vtss_phy_callout_set(NULL, board_conf->numeric_handle, callout_cxt);
    device->drv = drv;
    data->port_no = board_conf->numeric_handle;
    data->cap = PHY_CAP_1G;
    device->data = data;

    for (i = 0; i < MAX_PORTS_PER_PHY; i++) {
        data->other_dev[i] = NULL;
    }
    T_I(data, MEPA_TRACE_GRP_GEN, "probed port %d", data->port_no);
    return device;

out_data:
    free(device);
out_device:
    (void)mscc_vtss_destroy();
    return NULL;
}

static mepa_rc mscc_1g_status_1g_get(mepa_device_t    *dev,
                                     mepa_aneg_status_t *status) {
    phy_data_t *data = (phy_data_t *)(dev->data);
    mepa_rc rc;
    vtss_phy_status_1g_t vtss_status;

    rc = vtss_phy_status_1g_get(NULL, data->port_no, &vtss_status);
    status->master_cfg_fault = vtss_status.master_cfg_fault;
    status->master = vtss_status.master;
    return rc;
}

static mepa_rc phy_1g_event_enable_set(mepa_device_t *dev, mepa_event_t event,
                                        mesa_bool_t enable)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return vtss_phy_event_enable_set(NULL, data->port_no, event, enable);
}

static mepa_rc phy_1g_event_enable_get(mepa_device_t *dev, mepa_event_t *ev_mask)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return vtss_phy_event_enable_get(NULL, data->port_no, ev_mask);
}

static mepa_rc phy_1g_event_poll(mepa_device_t *dev, mepa_event_t *status)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return vtss_phy_event_poll(NULL, data->port_no, status);
}

static mepa_rc phy_1g_loopback_set(mepa_device_t *dev, const mepa_loopback_t *loopback)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    vtss_phy_loopback_t phy_loop = {};

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
    return vtss_phy_loopback_set(NULL, data->port_no, phy_loop);
}

static mepa_rc phy_1g_loopback_get(mepa_device_t *dev, mepa_loopback_t *const loopback)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    vtss_phy_loopback_t loop = {};
    if (vtss_phy_loopback_get(NULL, data->port_no, &loop) == MESA_RC_OK) {
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
    return vtss_phy_read(NULL, data->port_no, address, value);
}

static mepa_rc phy_1g_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    return vtss_phy_write(NULL, data->port_no, address, value);
}

static mepa_rc phy_1g_gpio_mode(mepa_device_t *dev, const mepa_gpio_conf_t *gpio_conf)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    vtss_phy_gpio_mode_t gpio_mode;

    // VSC8584 has 0-13 gpios
    if (gpio_conf->gpio_no > 13) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    if (gpio_conf->mode == MEPA_GPIO_MODE_LED_DISABLE_EXTENDED) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    switch (gpio_conf->mode) {
        case MEPA_GPIO_MODE_OUT: gpio_mode = VTSS_PHY_GPIO_OUT;
            break;
        case MEPA_GPIO_MODE_IN: gpio_mode = VTSS_PHY_GPIO_IN;
            break;
        default: gpio_mode = VTSS_PHY_GPIO_ALT_0;
            break;
    }
    if (gpio_conf->mode >= MEPA_GPIO_MODE_LED_LINK_ACTIVITY && gpio_conf->mode < MEPA_GPIO_MODE_LED_DISABLE_EXTENDED) {
        vtss_phy_led_mode_select_t mode_select;
        mode_select.number = gpio_conf->led_num == MEPA_LED0 ? VTSS_PHY_LED0 : VTSS_PHY_LED1;
        mode_select.mode = VTSS_PHY_LED_MODE_LINK_ACTIVITY + (gpio_conf->mode - MEPA_GPIO_MODE_LED_LINK_ACTIVITY);
        vtss_phy_led_mode_set(NULL, data->port_no, mode_select);
    }
    return vtss_phy_gpio_mode(NULL, data->port_no, gpio_conf->gpio_no, gpio_mode);
}

static mepa_rc phy_1g_gpio_set(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t enable)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    // VSC8584 has 0-13 gpios
    if (gpio_no > 13) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    return vtss_phy_gpio_set(NULL, data->port_no, gpio_no, enable);
}

static mepa_rc phy_1g_gpio_get(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t * const enable)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    // VSC8584 has 0-13 gpios
    if (gpio_no > 13) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    return vtss_phy_gpio_get(NULL, data->port_no, gpio_no, enable);
}
static mepa_rc phy_1g_synce_clk_conf_set(mepa_device_t *dev, const mepa_synce_clock_conf_t *conf)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    vtss_phy_clock_conf_t phy_conf = {};
    vtss_phy_recov_clk_t clk_port = conf->dst == MEPA_SYNCE_CLOCK_DST_1 ? VTSS_PHY_RECOV_CLK1 : VTSS_PHY_RECOV_CLK2;

    phy_conf.squelch = conf->src == MEPA_SYNCE_CLOCK_SRC_DISABLED ? VTSS_PHY_CLK_SQUELCH_NONE : VTSS_PHY_CLK_SQUELCH_MAX;
    phy_conf.src = conf->src == MEPA_SYNCE_CLOCK_SRC_SERDES_MEDIA ? VTSS_PHY_SERDES_MEDIA :
                   conf->src == MEPA_SYNCE_CLOCK_SRC_COPPER_MEDIA ? VTSS_PHY_COPPER_MEDIA : VTSS_PHY_CLK_DISABLED;
    phy_conf.freq = conf->freq == MEPA_FREQ_25M ? VTSS_PHY_FREQ_25M :
                    conf->freq == MEPA_FREQ_31_25M ? VTSS_PHY_FREQ_3125M : VTSS_PHY_FREQ_125M;

    return vtss_phy_clock_conf_set(NULL, data->port_no, clk_port, &phy_conf);
}
// store base_dev info in dev and store dev info in base_dev.
static mepa_rc phy_1g_link_base_port(mepa_device_t *dev, mepa_device_t *base_dev, uint8_t packet_idx)
{
    phy_data_t *base_data = (phy_data_t *)(base_dev->data);
    phy_data_t *data = (phy_data_t *)(dev->data);
    mepa_device_t *other_dev;
    vtss_phy_type_t id, base_id;
    mesa_rc rc;
    int i;

    T_D(data, MEPA_TRACE_GRP_GEN, "for port %d base port linked as %d\n", data->port_no, base_data->port_no);
    data->base_dev = base_dev;
    base_data->base_dev = base_dev;
    base_data->other_dev[0] = base_dev; // needed later for comparison.
    base_data->all_phy_ports[0] = base_data->port_no;
    if (dev->drv->mepa_ts) {
        for (i = 1; i < MAX_PORTS_PER_PHY; i++) {
            if ((dev != base_dev)&& base_data->other_dev[i] == NULL) {
                base_data->other_dev[i] = dev;
                base_data->all_phy_ports[i] = data->port_no;
                break;
            }
            T_D(data, MEPA_TRACE_GRP_GEN, "base linked i %d port %d\n", i, base_data->all_phy_ports[i]);
        }
    }
    rc = vtss_phy_id_get(NULL, base_data->port_no, &base_id);
    if (rc == MESA_RC_OK && base_id.channel_id) {
        T_W(data, MEPA_TRACE_GRP_GEN, "base port channel id is not 0");
        return MEPA_RC_ERROR;
    }
    return MEPA_RC_OK;
}

static mepa_rc phy_1g_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    vtss_phy_type_t phy_id;
    mesa_rc rc = MESA_RC_OK;

    phy_info->cap = 0;
    rc = vtss_phy_id_get(NULL, data->port_no, &phy_id);
    if (rc == MESA_RC_OK) {
        phy_info->part_number = phy_id.part_number;
        phy_info->revision = phy_id.revision;
        phy_info->cap = MEPA_CAP_SPEED_MASK_1G;
        if (phy_id.part_number == VTSS_PHY_TYPE_8582 || phy_id.part_number == VTSS_PHY_TYPE_8584 ||
            phy_id.part_number == VTSS_PHY_TYPE_8575 || phy_id.part_number == VTSS_PHY_TYPE_8586) {
            phy_info->cap |= MEPA_CAP_TS_MASK_GEN_2;
        } else if (phy_id.part_number == VTSS_PHY_TYPE_8574 || phy_id.part_number == VTSS_PHY_TYPE_8572) {
            phy_info->cap |= MEPA_CAP_TS_MASK_GEN_1;
        } else {
            phy_info->cap |= MEPA_CAP_TS_MASK_NONE;
        }
        phy_info->ts_base_port = phy_id.phy_api_base_no;
    }
    return rc == MESA_RC_OK ? MEPA_RC_OK : MEPA_RC_ERROR;
}

static mepa_rc phy_10g_delete(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    free(data);
    free(dev);
    dev = NULL;
    return mscc_vtss_destroy();
}

static mepa_rc malibu_10g_reset(mepa_device_t *dev,
                                const mepa_reset_param_t *rst_conf)
{
    vtss_phy_10g_mode_t oper_mode = {};
    phy_data_t *data = (phy_data_t *)(dev->data);

    oper_mode.oper_mode = VTSS_PHY_LAN_MODE;
    oper_mode.xfi_pol_invert = 1;
    oper_mode.polarity.host_rx = true;
    oper_mode.polarity.line_rx = true;
    oper_mode.polarity.host_tx = false;
    oper_mode.polarity.line_tx = false;
    oper_mode.is_host_wan = false;
    oper_mode.lref_for_host = false;
    oper_mode.h_clk_src.is_high_amp = true;
    oper_mode.l_clk_src.is_high_amp = true;
    oper_mode.h_media = VTSS_MEDIA_TYPE_SR;
    oper_mode.l_media = VTSS_MEDIA_TYPE_SR;
    oper_mode.serdes_conf.l_offset_guard = true;
    oper_mode.serdes_conf.h_offset_guard = true;

    if ((data->port_no == 25) || (data->port_no == 24)) {
        oper_mode.polarity.host_rx = false;
        oper_mode.polarity.line_rx = false;
        oper_mode.polarity.host_tx = true;
        oper_mode.polarity.line_tx = true;
    }

    return vtss_phy_10g_mode_set(NULL, data->port_no, &oper_mode);
}

static mepa_rc venice_10g_reset(mepa_device_t *dev,
                                const mepa_reset_param_t *rst_conf)
{
    vtss_phy_10g_mode_t oper_mode = {};
    vtss_phy_10g_id_t phy_10g_id;
    phy_data_t *data = (phy_data_t *)(dev->data);

    oper_mode.oper_mode = VTSS_PHY_LAN_MODE;
    if (vtss_phy_10g_id_get(0, data->port_no, &phy_10g_id) == MEPA_RC_OK) {
        if ((phy_10g_id.part_number == 0x8487) || (phy_10g_id.part_number == 0x8488)) {
            oper_mode.xfi_pol_invert = 0;
        } else {
            oper_mode.xfi_pol_invert = 1;
        }
    }
    oper_mode.l_clk_src.is_high_amp = true;
    oper_mode.l_media = VTSS_MEDIA_TYPE_SR;
    return vtss_phy_10g_mode_set(NULL, data->port_no, &oper_mode);
}


static mepa_rc phy_10g_poll(mepa_device_t *dev,
                            mepa_status_t *status)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_10g_status_t status_10g;

    if (vtss_phy_10g_status_get(NULL, data->port_no, &status_10g) != VTSS_RC_OK) {
        return MEPA_RC_ERROR;
    }
    memset(status, 0, sizeof(*status));
    status->link = status_10g.status;
    return MEPA_RC_OK;
}

static mepa_rc phy_10g_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    vtss_phy_10g_mode_t mode = {};

    if (vtss_phy_10g_mode_get(NULL, data->port_no, &mode) != MEPA_RC_OK) {
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
        if (mode.oper_mode != VTSS_PHY_1G_MODE) {
            mode.oper_mode = VTSS_PHY_1G_MODE;
            if (vtss_phy_10g_mode_set(NULL, data->port_no, &mode) !=
                MEPA_RC_OK) {
                return MEPA_RC_ERROR;
            }
        }

        vtss_phy_10g_clause_37_control_t ctrl = {};
        ctrl.enable = config->speed == MESA_SPEED_AUTO;
        ctrl.advertisement.fdx = 1;
        ctrl.advertisement.symmetric_pause = config->flow_control;
        ctrl.advertisement.asymmetric_pause = config->flow_control;
        ctrl.advertisement.remote_fault =
            (config->admin.enable ? VTSS_PHY_10G_CLAUSE_37_RF_LINK_OK
             : VTSS_PHY_10G_CLAUSE_37_RF_OFFLINE);
        ctrl.l_h = true;
        if (vtss_phy_10g_clause_37_control_set(NULL, data->port_no,
                                               &ctrl) != MEPA_RC_OK) {
            return MEPA_RC_ERROR;
        }
    } else {
        mode.xaui_lane_flip = false;
        mode.oper_mode = VTSS_PHY_LAN_MODE;
        if (vtss_phy_10g_mode_set(NULL, data->port_no, &mode) !=
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
    vtss_phy_10g_id_t phy_id = {};
    mesa_rc rc = MESA_RC_OK;

    phy_info->cap = 0;
    rc = vtss_phy_10g_id_get(NULL, data->port_no, &phy_id);
    if (rc == MESA_RC_OK) {
        phy_info->part_number = phy_id.part_number;
        phy_info->revision = phy_id.revision;
        phy_info->cap = MEPA_CAP_SPEED_MASK_10G;
        if ((phy_id.part_number == 0x8488 || phy_id.part_number == 0x8487) && phy_id.revision >= 4) {
            phy_info->cap |= MEPA_CAP_TS_MASK_GEN_1;
        } else if ((phy_id.part_number == 0x8489 && !(phy_id.device_feature_status & VTSS_PHY_10G_TIMESTAMP_DISABLED)) ||
            (phy_id.part_number == 0x8490 || phy_id.part_number == 0x8491) ||
            (phy_id.family == VTSS_PHY_FAMILY_MALIBU)) {
            phy_info->cap |= MEPA_CAP_TS_MASK_GEN_2;
        } else {
            phy_info->cap |= MEPA_CAP_TS_MASK_NONE;
        }
        phy_info->ts_base_port = (phy_id.channel_id > 1) ? (phy_id.phy_api_base_no + 2) : phy_id.phy_api_base_no;
    }
    return rc == MESA_RC_OK ? MEPA_RC_OK : MEPA_RC_ERROR;
}

static mepa_device_t *phy_10g_probe(mepa_driver_t *drv,
                                    const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                    struct mepa_callout_cxt MEPA_SHARED_PTR *callout_cxt,
                                    struct mepa_board_conf              *board_conf)
{

    if (mscc_vtss_create(callout, callout_cxt, board_conf) != MEPA_RC_OK) {
        return NULL;
    }

    mepa_device_t *device =
        (mepa_device_t *)calloc(1, sizeof(mepa_device_t));

    if (device == NULL) {
        goto out_device;
    }

    phy_data_t *data = (phy_data_t *)calloc(1, sizeof(*data));

    if (data == NULL) {
        goto out_data;
    }

    device->drv = drv;
    data->port_no = board_conf->numeric_handle;
    data->cap = PHY_CAP_10G;
    device->data = data;

    return device;

out_data:
    free(device);
out_device:
    (void)mscc_vtss_destroy();
    return NULL;
}

mepa_drivers_t mepa_mscc_driver_init()
{
    static const int nr_mscc_phy = 5;
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
            .mepa_driver_if_set = mscc_if_set,
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
             // Tesla
            .id = 0x000704a0,
            .mask = 0xfffffff0,
            .mepa_driver_delete = mscc_1g_delete,
            .mepa_driver_reset = mscc_1g_reset,
            .mepa_driver_poll = mscc_1g_poll,
            .mepa_driver_conf_set = mscc_1g_conf_set,
            .mepa_driver_conf_get = phy_1g_conf_get,
            .mepa_driver_if_set = mscc_if_set,
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
            .mepa_driver_link_base_port = phy_1g_link_base_port,
            .mepa_driver_phy_info_get = phy_1g_info_get,
            .mepa_ts = &vtss_ts_drivers,
        },
        {
             // Viper
            .id = 0x000707c0,
            .mask = 0xfffffff0,
            .mepa_driver_delete = mscc_1g_delete,
            .mepa_driver_reset = mscc_1g_reset,
            .mepa_driver_poll = mscc_1g_poll,
            .mepa_driver_conf_set = mscc_1g_conf_set,
            .mepa_driver_conf_get = phy_1g_conf_get,
            .mepa_driver_if_set = mscc_if_set,
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
            .mepa_driver_link_base_port = phy_1g_link_base_port,
            .mepa_driver_phy_info_get = phy_1g_info_get,
            .mepa_ts = &vtss_ts_drivers,
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
            .mepa_driver_if_set = mscc_if_set,
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
            .mepa_driver_link_base_port = phy_1g_link_base_port,
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
            .mepa_driver_if_set = mscc_if_set,
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
            .mepa_driver_if_set = mscc_if_set,
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
        .mepa_driver_if_set = mscc_if_set,
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
        .mepa_driver_if_set = mscc_if_set,
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
