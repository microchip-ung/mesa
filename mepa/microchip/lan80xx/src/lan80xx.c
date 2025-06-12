// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <string.h>
#include <stdio.h>
#include "lan80xx_types.h"
#include "lan80xx_private.h"
#include "lan80xx_ts_private.h"
#include "lan80xx_mcu.h"

extern mepa_ts_driver_t lan80xx_ts_drivers;
extern mepa_macsec_driver_t lan80xx_macsec_drivers;

////////  MEPA API Implementation  /////

static mepa_rc lan80xx_delete(mepa_device_t *dev)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    for (u8 i = 0; i < base_data->max_port_cnt; i++) {
        if (base_data->chip_ports[i] == data->port_no) {
            base_data->other_port_dev[i] = NULL;
            break;
        }
    }
    lan80xx_mamcsec_mem_free(dev);

    T_I(MEPA_TRACE_GRP_GEN, "\n Dev to be Deleted\n");
    return mepa_delete_int(dev);
}

static mepa_device_t *lan80xx_probe(mepa_driver_t *drv,
                                    const mepa_callout_t *callout,
                                    struct mepa_callout_ctx *callout_ctx,
                                    struct mepa_board_conf *board_conf)
{
    mepa_device_t *dev;
    phy25g_phy_state_t *data;
    dev = mepa_create_int(drv, callout, callout_ctx, board_conf, sizeof(phy25g_phy_state_t));
    if (!dev) {
        return 0;
    }
    data = dev->data;
    memset(data, 0, sizeof(phy25g_phy_state_t));
    data->port_no = board_conf->numeric_handle;
    data->events = 0;

    T_I(MEPA_TRACE_GRP_GEN, "Malibu25G driver probed for port %d\n", data->port_no);
    return dev;
}

static mepa_rc lan80xx_conf_get(mepa_device_t *const dev, mepa_conf_t *const config)
{

    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && config != NULL) {
        phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
        MEPA_ENTER(dev);
        *config = data->conf;
        config->conf_25g.channel_id = data->channel_id + 1;
        config->flow_control = data->flow_control_ena;
        MEPA_EXIT(dev);
        rc = MEPA_RC_OK;
    }
    return rc;
}

static mepa_rc lan80xx_restart_conf_set(struct mepa_device *dev, const mepa_restart_t restart)
{

    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    MEPA_ENTER(dev);
    data->restart_cur = restart;
    rc = lan80xx_restart_type_set(dev);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_restart_conf_get(struct mepa_device *dev, mepa_restart_t *const restart)
{

    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    MEPA_ENTER(dev);
    rc = lan80xx_warmrestart_conf_get_priv(dev);
    if (rc != MEPA_RC_ERROR) {
        *restart = data->restart_cur;
    }
    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan80xx_conf_set(struct mepa_device *dev, const mepa_conf_t *config)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_conf_set_priv(dev, config);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_poll(mepa_device_t *dev, mepa_status_t *status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    phy25g_status_t status_25g;
    MEPA_ENTER(dev);
    if (lan80xx_status_get_priv(dev, data->port_no, &status_25g) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Error in Getting PHY status");
        MEPA_EXIT(dev);
        return MEPA_RC_ERROR;
    }
    memset(status, 0, sizeof(*status));
    status->link = status_25g.phy_status;
    status->speed = (data->port_state.speed == SPEED_1G) ? MESA_SPEED_1G : (data->port_state.speed == SPEED_10G) ? MESA_SPEED_10G : MESA_SPEED_25G;
    status->fdx = 1;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_if_set(mepa_device_t *dev, mepa_port_interface_t mac_if)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    MEPA_ENTER(dev);
    data->mac_if = mac_if;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_if_get(mepa_device_t *dev, mepa_port_speed_t speed, mepa_port_interface_t *mac_if)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    MEPA_ENTER(dev);
    *mac_if = data->mac_if;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc = MEPA_RC_OK;

    if (!data->base_dev) {
        T_E(MEPA_TRACE_GRP_GEN, "base dev not assigned for port number %u\n", data->port_no);
        return MEPA_RC_ERROR;
    }

    MEPA_ENTER(dev);
    rc = lan80xx_reset_point(dev, rst_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_prbs_set(mepa_device_t *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction,
                                const mepa_phy_prbs_generator_conf_t *const prbs_conf)
{
    mepa_rc rc;

    if (prbs_conf == NULL) {
        return MEPA_RC_ERROR;
    }
    if (type >= MEPA_PHY_PRBS_TYPE_CNT || direction >= MEPA_PHY_DIRECTION_CNT) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Invalid PRBS Input \n");
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_prbs_generator_conf_set(dev, prbs_conf->enable, type, direction, prbs_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_prbs_get(mepa_device_t *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const prbs_conf)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    if (type >= MEPA_PHY_PRBS_TYPE_CNT || direction >= MEPA_PHY_DIRECTION_CNT) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Invalid PRBS Input \n");
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    if (type == MEPA_PHY_PRBS_TYPE_SERDES) {
        *prbs_conf = (direction == MEPA_PHY_DIRECTION_HOST) ? data->host_prbs_conf : data->line_prbs_conf;
    } else {
        *prbs_conf = (direction == MEPA_PHY_DIRECTION_HOST) ? data->host_pcs_prbs_conf : data->line_pcs_prbs_conf;
    }
    MEPA_EXIT(dev);
    return MEPA_RC_OK;

}

static mepa_rc lan80xx_prbs_monitor_set(mepa_device_t *dev,  const mepa_phy_prbs_monitor_conf_t *const value)
{
    mepa_rc rc;

    if (value == NULL) {
        return MEPA_RC_ERROR;
    }
    if (value->prbs_type == MEPA_PHY_PRBS_TYPE_CNT || value->prbs_direction == MEPA_PHY_DIRECTION_CNT) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Invalid PRBS Input \n");
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_prbs_monitor_conf_set(dev, value->prbs_type, value->prbs_direction, value);
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_prbs_monitor_get(mepa_device_t *dev, mepa_phy_prbs_monitor_conf_t *const value)
{
    mepa_rc rc;

    if (value == NULL) {
        return MEPA_RC_ERROR;
    }
    if (value->prbs_type == MEPA_PHY_PRBS_TYPE_CNT || value->prbs_direction == MEPA_PHY_DIRECTION_CNT) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Invalid PRBS Input \n");
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_prbs_monitor_status_get(dev, value->prbs_type, value->prbs_direction, value);
    MEPA_EXIT(dev);
    return rc;
}

/*
Address is in this format
[15:0] -> Register address
[20:16] -> Device ID (MMD device id)
[22:21] -> Port ID
[23] -> Read/Write
*/

static mepa_rc lan80xx_clause45_read(struct mepa_device *dev,
                                     uint32_t address,
                                     uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_OK;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    uint16_t page_add = (address >> 16) & 0xffff;
    uint16_t mmd = (page_add & 0x1f);
    uint16_t addr = address & 0xffff;
    uint32_t data_val;

    if (mmd) {
        rc = lan80xx_csr_rd(dev, data->port_no, mmd, 0, addr, &data_val);
        *value = (uint16_t)data_val;
    }
    MEPA_EXIT(dev);
    return rc;

}

/*
Address is in this format
[15:0] -> Register address
[20:16] -> Device ID (MMD device id)
[22:21] -> Port ID
[23] -> Read/Write
*/
static mepa_rc lan80xx_clause45_write(struct mepa_device *dev,
                                      uint32_t address, uint16_t value)
{
    mepa_rc rc = MEPA_RC_OK;
    MEPA_ENTER(dev);
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    uint16_t page_add = (address >> 16) & 0xffff;
    uint16_t mmd = (page_add & 0x1f);
    uint16_t addr = address & 0xffff;

    if (mmd) {
        rc = lan80xx_csr_wr(dev, data->port_no, mmd, 0, addr, value);
    }
    MEPA_EXIT(dev);
    return rc;

}

static uint32_t lan80xx_phy_capability(struct mepa_device *dev, uint32_t capability)
{
    uint32_t c = 0;
    MEPA_ENTER(dev);
    c = lan80xx_phy_capability_priv(dev, capability);
    MEPA_EXIT(dev);
    return c;
}

static mepa_rc lan80xx_gpio_mode_set(mepa_device_t *dev, const mepa_gpio_conf_t *gpio_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    if (gpio_conf->gpio_no >= LAN80XX_GPIO_COUNT) {
        T_E(MEPA_TRACE_GRP_GEN, "\nGPIO Pin Not Supported on port %d , expected (0 - 39)\n", data->port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    mepa_rc rc = MEPA_RC_ERROR;
    rc = lan80xx_gpio_mode_set_priv(dev, data->port_no, gpio_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_gpio_read(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t *const value)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc;
    if (gpio_no >=  LAN80XX_GPIO_COUNT) {
        T_E(MEPA_TRACE_GRP_GEN, "Invalid GPIO number");
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_gpio_read_priv(dev, data->port_no, gpio_no, value);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_gpio_write(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t value)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc;
    if (gpio_no >= LAN80XX_GPIO_COUNT) {
        T_E(MEPA_TRACE_GRP_GEN, "Invalid GPIO number");
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_gpio_write_priv(dev, data->port_no, gpio_no, value);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_phy_i2c_write(mepa_device_t *dev,
                                     const uint8_t      i2c_mux,
                                     const uint8_t      i2c_reg_addr,
                                     const uint8_t      i2c_dev_addr,
                                     const mepa_bool_t  word_access,
                                     uint8_t      cnt,
                                     const uint8_t      *const value)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc;
    MEPA_ENTER(dev);
    rc = LAN80XX_RC_COLD(lan80xx_phy_i2c_write_priv(dev, data->port_no, i2c_reg_addr, cnt, value));
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_phy_i2c_read(mepa_device_t  *dev,
                                    const uint8_t      i2c_mux,
                                    const uint8_t      i2c_reg_addr,
                                    const uint8_t      i2c_dev_addr,
                                    const mepa_bool_t  word_access,
                                    uint8_t      cnt,
                                    uint8_t *const value)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc;
    MEPA_ENTER(dev);
    rc = LAN80XX_RC_COLD(lan80xx_phy_i2c_read_priv(dev, data->port_no, i2c_reg_addr, cnt, value));
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_link_base_port(mepa_device_t *dev, mepa_device_t *base_dev, uint8_t packet_idx)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    phy25g_phy_state_t *base_data = (phy25g_phy_state_t *)base_dev->data;
    MEPA_ENTER(dev);
    T_I(MEPA_TRACE_GRP_GEN, "Linking port %d with base-port %d", data->port_no, base_data->port_no);
    data->base_dev = base_dev;
    data->packet_idx = packet_idx;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_phy_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    phy25g_phy_state_t *base_data = data->base_dev ? ((phy25g_phy_state_t *)(data->base_dev->data)) : NULL;
    MEPA_ENTER(dev);
    phy_info->part_number = data->dev.devid;
    phy_info->revision = data->dev.rev;

    /* 1588 Capability */
    if ((data->dev.devid == LAN80XX_DEV_ID_8022) || (data->dev.devid == LAN80XX_DEV_ID_8042)) {
        phy_info->cap = MEPA_CAP_TS_MASK_NONE;
    } else {
        phy_info->cap = MEPA_CAP_TS_MASK_GEN_2;
    }
    /* Speed Capability */
    if (phy_info->part_number == LAN80XX_DEV_ID_8267 || phy_info->part_number == LAN80XX_DEV_ID_8268 || phy_info->part_number == LAN80XX_DEV_ID_8264) {
        phy_info->cap |= MEPA_CAP_SPEED_MASK_10G;
    } else {
        phy_info->cap |= MEPA_CAP_SPEED_MASK_25G;
    }
    phy_info->ts_base_port = base_data ? base_data->port_no : 0;
    T_I(MEPA_TRACE_GRP_GEN, "Port no : %d Part number : %x Revision : %d Capability : %d ts_base_port : %d", data->port_no, phy_info->part_number, phy_info->revision,
        phy_info->cap, phy_info->ts_base_port);
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_loopback_set(mepa_device_t *dev, const mepa_loopback_t *loopback)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = LAN80XX_RC_COLD(lan80xx_loopback_set_priv(dev, data->port_no, loopback));
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_loopback_get(mepa_device_t *dev, mepa_loopback_t *const loopback)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    MEPA_ENTER(dev);
    memset(loopback, 0, sizeof(mepa_loopback_t));
    loopback->far_end_ena = data->port_state.loopback_conf.l2_lp;
    loopback->near_end_ena = data->port_state.loopback_conf.h2_lp;
    loopback->mac_serdes_equip_ena = data->port_state.loopback_conf.h1_lp;
    loopback->media_serdes_equip_ena = data->port_state.loopback_conf.l1_lp;
    loopback->media_serdes_facility_ena = data->port_state.loopback_conf.l5_lp;
    loopback->mac_serdes_facility_ena = data->port_state.loopback_conf.h5_lp;
    loopback->media_serdes_input_ena = data->port_state.loopback_conf.l6_lp;
    loopback->mac_serdes_input_ena = data->port_state.loopback_conf.h6_lp;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_power_set(mepa_device_t *dev, mepa_power_mode_t power)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_power_t power_status = {0};
    MEPA_ENTER(dev);
    switch (power) {
    case MESA_PHY_POWER_NOMINAL:
        power_status = LAN80XX_PHY_POWER_DISABLE;
        break;
    case MESA_PHY_POWER_ACTIPHY:
    case MESA_PHY_POWER_DYNAMIC:
    case MESA_PHY_POWER_ENABLED:
        power_status = LAN80XX_PHY_POWER_ENABLE;
        break;
    }
    T_I(MEPA_TRACE_GRP_GEN, "Port no : %d Power configuration : %d", data->port_no, power_status);
    rc = lan80xx_power_set_priv(dev, data->port_no, power_status);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_chip_temp_get(mepa_device_t *dev, i16 *const temp)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    /* Get Current Temeprature*/
    rc = lan80xx_temp_sensor_get_priv(dev, data->port_no, temp);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_debug_info_dump(mepa_device_t *dev,
                                       const mepa_debug_print_t pr,
                                       const mepa_debug_info_t   *const info)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    MEPA_ENTER(dev);
    lan80xx_pma_reg_dump(dev, data->port_no, pr);
    lan80xx_pcs_reg_dump(dev, data->port_no, pr);
    lan80xx_kr_reg_dump(dev, data->port_no, pr);
    lan80xx_gpio_glb_slice_reg_dump(dev, data->port_no, pr);
    lan80xx_mac_reg_dump(dev, data->port_no, pr);
    lan80xx_ptp_reg_dump(dev, data->port_no, pr);
    lan80xx_macsec_dbg_reg_dump_priv(dev, data->port_no, pr);
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_framepreempt_set(mepa_device_t *dev, const mepa_bool_t enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    if (data->port_state.port_mode.oper_mode == MAC_RETIMER) {
        rc = lan80xx_pmac_config(dev, data->port_no, enable);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Error in Config PMAC on Port : %d \n", data->port_no);
            MEPA_EXIT(dev);
            return MEPA_RC_ERROR;
        }
    }
    data->frame_preempt_ena = enable;
    rc = lan80xx_ptp_block_preempt_conf(dev, data->port_no, enable);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_framepreempt_get(mepa_device_t *dev, mepa_bool_t *const enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    MEPA_ENTER(dev);
    *enable = data->frame_preempt_ena;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

//  //////////////  MEPA driver_init_structure//////
mepa_bool_t lan80xx_driver_check(const mepa_device_t   *dev)
{
    if (dev->drv->id == 0x8004 || dev->drv->id == 0x8003 || dev->drv->id == 0x8002 || dev->drv->id == 0x8268 || dev->drv->id == 0x8267 || dev->drv->id == 0x8264) {
        return TRUE;
    }
    return FALSE;
}

mepa_drivers_t mepa_lan80xx_driver_init()
{
    static const int nr_lan80xx_drivers = 6;
    static mepa_driver_t lan80xx_drivers[] = {
        {
            /* LAN8044 and LAN8024*/
            .id = 0x008004,
            .mask = 0x00FF0F,
            .mepa_driver_delete = lan80xx_delete,
            .mepa_driver_reset = lan80xx_reset,
            .mepa_driver_poll = lan80xx_poll,
            .mepa_driver_probe = lan80xx_probe,
            .mepa_driver_conf_set = lan80xx_conf_set,
            .mepa_driver_conf_get = lan80xx_conf_get,
            .mepa_driver_if_get = lan80xx_if_get,
            .mepa_driver_if_set = lan80xx_if_set,
            .mepa_driver_power_set = lan80xx_power_set,
            .mepa_driver_media_set = NULL,
            .mepa_driver_media_get = NULL,
            .mepa_driver_aneg_status_get = NULL,
            .mepa_driver_clause45_read  = lan80xx_clause45_read,
            .mepa_driver_clause45_write = lan80xx_clause45_write,
            .mepa_driver_event_enable_set = NULL,
            .mepa_driver_event_enable_get = NULL,
            .mepa_driver_event_poll = NULL,
            .mepa_driver_loopback_set = lan80xx_loopback_set,
            .mepa_driver_loopback_get = lan80xx_loopback_get,
            .mepa_driver_gpio_mode_set = lan80xx_gpio_mode_set,
            .mepa_driver_gpio_out_set = lan80xx_gpio_write,
            .mepa_driver_gpio_in_get = lan80xx_gpio_read,
            .mepa_driver_link_base_port = lan80xx_link_base_port,
            .mepa_driver_synce_clock_conf_set = NULL,
            .mepa_driver_phy_i2c_read   = lan80xx_phy_i2c_read,
            .mepa_driver_phy_i2c_write   = lan80xx_phy_i2c_write,
            .mepa_driver_phy_info_get  = lan80xx_phy_info_get,
            .mepa_driver_prbs_set = lan80xx_prbs_set,
            .mepa_driver_prbs_get = lan80xx_prbs_get,
            .mepa_driver_prbs_monitor_set = lan80xx_prbs_monitor_set,
            .mepa_driver_prbs_monitor_get = lan80xx_prbs_monitor_get,
            .mepa_driver_chip_temp_get = lan80xx_chip_temp_get,
            .mepa_driver_warmrestart_conf_get = lan80xx_restart_conf_get,
            .mepa_driver_warmrestart_conf_set = lan80xx_restart_conf_set,
            .mepa_capability = lan80xx_phy_capability,
            .mepa_debug_info_dump   = lan80xx_debug_info_dump,
            .mepa_driver_framepreempt_set = lan80xx_framepreempt_set,
            .mepa_driver_framepreempt_get = lan80xx_framepreempt_get,
            .mepa_ts = &lan80xx_ts_drivers,
            .mepa_macsec = &lan80xx_macsec_drivers,
        },
        {
            /* LAN8043 and LAN8023 */
            .id = 0x008003,
            .mask = 0x00FF0F,
            .mepa_driver_delete = lan80xx_delete,
            .mepa_driver_reset = lan80xx_reset,
            .mepa_driver_poll = lan80xx_poll,
            .mepa_driver_probe = lan80xx_probe,
            .mepa_driver_conf_set = lan80xx_conf_set,
            .mepa_driver_conf_get = lan80xx_conf_get,
            .mepa_driver_if_get = lan80xx_if_get,
            .mepa_driver_if_set = lan80xx_if_set,
            .mepa_driver_power_set = lan80xx_power_set,
            .mepa_driver_media_set = NULL,
            .mepa_driver_media_get = NULL,
            .mepa_driver_aneg_status_get = NULL,
            .mepa_driver_clause45_read  = lan80xx_clause45_read,
            .mepa_driver_clause45_write = lan80xx_clause45_write,
            .mepa_driver_event_enable_set = NULL,
            .mepa_driver_event_enable_get = NULL,
            .mepa_driver_event_poll = NULL,
            .mepa_driver_loopback_set = lan80xx_loopback_set,
            .mepa_driver_loopback_get = lan80xx_loopback_get,
            .mepa_driver_gpio_mode_set = lan80xx_gpio_mode_set,
            .mepa_driver_gpio_out_set = lan80xx_gpio_write,
            .mepa_driver_gpio_in_get = lan80xx_gpio_read,
            .mepa_driver_link_base_port = lan80xx_link_base_port,
            .mepa_driver_synce_clock_conf_set = NULL,
            .mepa_driver_phy_i2c_read   = lan80xx_phy_i2c_read,
            .mepa_driver_phy_i2c_write   = lan80xx_phy_i2c_write,
            .mepa_driver_phy_info_get  = lan80xx_phy_info_get,
            .mepa_driver_prbs_set = lan80xx_prbs_set,
            .mepa_driver_prbs_get = lan80xx_prbs_get,
            .mepa_driver_prbs_monitor_set = lan80xx_prbs_monitor_set,
            .mepa_driver_prbs_monitor_get = lan80xx_prbs_monitor_get,
            .mepa_driver_warmrestart_conf_get = lan80xx_restart_conf_get,
            .mepa_driver_warmrestart_conf_set = lan80xx_restart_conf_set,
            .mepa_driver_chip_temp_get = lan80xx_chip_temp_get,
            .mepa_capability = lan80xx_phy_capability,
            .mepa_debug_info_dump    = lan80xx_debug_info_dump,
            .mepa_driver_framepreempt_set = lan80xx_framepreempt_set,
            .mepa_driver_framepreempt_get = lan80xx_framepreempt_get,
            .mepa_ts = &lan80xx_ts_drivers,
        },
        {
            /* LAN8042 and LAN8022 */
            .id = 0x008002,
            .mask = 0x00FF0F,
            .mepa_driver_delete = lan80xx_delete,
            .mepa_driver_reset = lan80xx_reset,
            .mepa_driver_poll = lan80xx_poll,
            .mepa_driver_probe = lan80xx_probe,
            .mepa_driver_conf_set = lan80xx_conf_set,
            .mepa_driver_conf_get = lan80xx_conf_get,
            .mepa_driver_if_get = lan80xx_if_get,
            .mepa_driver_if_set = lan80xx_if_set,
            .mepa_driver_power_set = lan80xx_power_set,
            .mepa_driver_media_set = NULL,
            .mepa_driver_media_get = NULL,
            .mepa_driver_aneg_status_get = NULL,
            .mepa_driver_clause45_read  = lan80xx_clause45_read,
            .mepa_driver_clause45_write = lan80xx_clause45_write,
            .mepa_driver_event_enable_set = NULL,
            .mepa_driver_event_enable_get = NULL,
            .mepa_driver_event_poll = NULL,
            .mepa_driver_loopback_set = lan80xx_loopback_set,
            .mepa_driver_loopback_get = lan80xx_loopback_get,
            .mepa_driver_gpio_mode_set = lan80xx_gpio_mode_set,
            .mepa_driver_gpio_out_set = lan80xx_gpio_write,
            .mepa_driver_gpio_in_get = lan80xx_gpio_read,
            .mepa_driver_link_base_port = lan80xx_link_base_port,
            .mepa_driver_synce_clock_conf_set = NULL,
            .mepa_driver_phy_i2c_read   = lan80xx_phy_i2c_read,
            .mepa_driver_phy_i2c_write   = lan80xx_phy_i2c_write,
            .mepa_driver_phy_info_get  = lan80xx_phy_info_get,
            .mepa_driver_prbs_set = lan80xx_prbs_set,
            .mepa_driver_prbs_get = lan80xx_prbs_get,
            .mepa_driver_prbs_monitor_set = lan80xx_prbs_monitor_set,
            .mepa_driver_prbs_monitor_get = lan80xx_prbs_monitor_get,
            .mepa_driver_warmrestart_conf_get = lan80xx_restart_conf_get,
            .mepa_driver_warmrestart_conf_set = lan80xx_restart_conf_set,
            .mepa_driver_chip_temp_get = lan80xx_chip_temp_get,
            .mepa_capability = lan80xx_phy_capability,
            .mepa_debug_info_dump    = lan80xx_debug_info_dump,
            .mepa_driver_framepreempt_set = lan80xx_framepreempt_set,
            .mepa_driver_framepreempt_get = lan80xx_framepreempt_get,
            .mepa_macsec = &lan80xx_macsec_drivers,
        },
        {
            /* LAN8268 */
            .id = 0x008268,
            .mask = 0x00FFFF,
            .mepa_driver_delete = lan80xx_delete,
            .mepa_driver_reset = lan80xx_reset,
            .mepa_driver_poll = lan80xx_poll,
            .mepa_driver_probe = lan80xx_probe,
            .mepa_driver_conf_set = lan80xx_conf_set,
            .mepa_driver_conf_get = lan80xx_conf_get,
            .mepa_driver_if_get = lan80xx_if_get,
            .mepa_driver_if_set = lan80xx_if_set,
            .mepa_driver_power_set = lan80xx_power_set,
            .mepa_driver_media_set = NULL,
            .mepa_driver_media_get = NULL,
            .mepa_driver_aneg_status_get = NULL,
            .mepa_driver_clause45_read  = lan80xx_clause45_read,
            .mepa_driver_clause45_write = lan80xx_clause45_write,
            .mepa_driver_event_enable_set = NULL,
            .mepa_driver_event_enable_get = NULL,
            .mepa_driver_event_poll = NULL,
            .mepa_driver_loopback_set = lan80xx_loopback_set,
            .mepa_driver_loopback_get = lan80xx_loopback_get,
            .mepa_driver_gpio_mode_set = lan80xx_gpio_mode_set,
            .mepa_driver_gpio_out_set = lan80xx_gpio_write,
            .mepa_driver_gpio_in_get = lan80xx_gpio_read,
            .mepa_driver_link_base_port = lan80xx_link_base_port,
            .mepa_driver_synce_clock_conf_set = NULL,
            .mepa_driver_phy_i2c_read   = lan80xx_phy_i2c_read,
            .mepa_driver_phy_i2c_write   = lan80xx_phy_i2c_write,
            .mepa_driver_phy_info_get  = lan80xx_phy_info_get,
            .mepa_driver_prbs_set = lan80xx_prbs_set,
            .mepa_driver_prbs_get = lan80xx_prbs_get,
            .mepa_driver_prbs_monitor_set = lan80xx_prbs_monitor_set,
            .mepa_driver_prbs_monitor_get = lan80xx_prbs_monitor_get,
            .mepa_driver_warmrestart_conf_get = lan80xx_restart_conf_get,
            .mepa_driver_warmrestart_conf_set = lan80xx_restart_conf_set,
            .mepa_driver_chip_temp_get = lan80xx_chip_temp_get,
            .mepa_capability = lan80xx_phy_capability,
            .mepa_debug_info_dump    = lan80xx_debug_info_dump,
            .mepa_driver_framepreempt_set = lan80xx_framepreempt_set,
            .mepa_driver_framepreempt_get = lan80xx_framepreempt_get,
            .mepa_ts = &lan80xx_ts_drivers,
            .mepa_macsec = &lan80xx_macsec_drivers,
        },
        {
            /* LAN8267 */
            .id = 0x008267,
            .mask = 0x00FFFF,
            .mepa_driver_delete = lan80xx_delete,
            .mepa_driver_reset = lan80xx_reset,
            .mepa_driver_poll = lan80xx_poll,
            .mepa_driver_probe = lan80xx_probe,
            .mepa_driver_conf_set = lan80xx_conf_set,
            .mepa_driver_conf_get = lan80xx_conf_get,
            .mepa_driver_if_get = lan80xx_if_get,
            .mepa_driver_if_set = lan80xx_if_set,
            .mepa_driver_power_set = lan80xx_power_set,
            .mepa_driver_media_set = NULL,
            .mepa_driver_media_get = NULL,
            .mepa_driver_aneg_status_get = NULL,
            .mepa_driver_clause45_read  = lan80xx_clause45_read,
            .mepa_driver_clause45_write = lan80xx_clause45_write,
            .mepa_driver_event_enable_set = NULL,
            .mepa_driver_event_enable_get = NULL,
            .mepa_driver_event_poll = NULL,
            .mepa_driver_loopback_set = lan80xx_loopback_set,
            .mepa_driver_loopback_get = lan80xx_loopback_get,
            .mepa_driver_gpio_mode_set = lan80xx_gpio_mode_set,
            .mepa_driver_gpio_out_set = lan80xx_gpio_write,
            .mepa_driver_gpio_in_get = lan80xx_gpio_read,
            .mepa_driver_link_base_port = lan80xx_link_base_port,
            .mepa_driver_synce_clock_conf_set = NULL,
            .mepa_driver_phy_i2c_read   = lan80xx_phy_i2c_read,
            .mepa_driver_phy_i2c_write   = lan80xx_phy_i2c_write,
            .mepa_driver_phy_info_get  = lan80xx_phy_info_get,
            .mepa_driver_prbs_set = lan80xx_prbs_set,
            .mepa_driver_prbs_get = lan80xx_prbs_get,
            .mepa_driver_prbs_monitor_set = lan80xx_prbs_monitor_set,
            .mepa_driver_prbs_monitor_get = lan80xx_prbs_monitor_get,
            .mepa_driver_warmrestart_conf_get = lan80xx_restart_conf_get,
            .mepa_driver_warmrestart_conf_set = lan80xx_restart_conf_set,
            .mepa_driver_chip_temp_get = lan80xx_chip_temp_get,
            .mepa_capability = lan80xx_phy_capability,
            .mepa_debug_info_dump    = lan80xx_debug_info_dump,
            .mepa_driver_framepreempt_set = lan80xx_framepreempt_set,
            .mepa_driver_framepreempt_get = lan80xx_framepreempt_get,
            .mepa_ts = &lan80xx_ts_drivers,
        },
        {
            /* LAN8264 */
            .id = 0x008264,
            .mask = 0x00FFFF,
            .mepa_driver_delete = lan80xx_delete,
            .mepa_driver_reset = lan80xx_reset,
            .mepa_driver_poll = lan80xx_poll,
            .mepa_driver_probe = lan80xx_probe,
            .mepa_driver_conf_set = lan80xx_conf_set,
            .mepa_driver_conf_get = lan80xx_conf_get,
            .mepa_driver_if_get = lan80xx_if_get,
            .mepa_driver_if_set = lan80xx_if_set,
            .mepa_driver_power_set = lan80xx_power_set,
            .mepa_driver_media_set = NULL,
            .mepa_driver_media_get = NULL,
            .mepa_driver_aneg_status_get = NULL,
            .mepa_driver_clause45_read  = lan80xx_clause45_read,
            .mepa_driver_clause45_write = lan80xx_clause45_write,
            .mepa_driver_event_enable_set = NULL,
            .mepa_driver_event_enable_get = NULL,
            .mepa_driver_event_poll = NULL,
            .mepa_driver_loopback_set = lan80xx_loopback_set,
            .mepa_driver_loopback_get = lan80xx_loopback_get,
            .mepa_driver_gpio_mode_set = lan80xx_gpio_mode_set,
            .mepa_driver_gpio_out_set = lan80xx_gpio_write,
            .mepa_driver_gpio_in_get = lan80xx_gpio_read,
            .mepa_driver_link_base_port = lan80xx_link_base_port,
            .mepa_driver_synce_clock_conf_set = NULL,
            .mepa_driver_phy_i2c_read   = lan80xx_phy_i2c_read,
            .mepa_driver_phy_i2c_write   = lan80xx_phy_i2c_write,
            .mepa_driver_phy_info_get  = lan80xx_phy_info_get,
            .mepa_driver_prbs_set = lan80xx_prbs_set,
            .mepa_driver_prbs_get = lan80xx_prbs_get,
            .mepa_driver_prbs_monitor_set = lan80xx_prbs_monitor_set,
            .mepa_driver_prbs_monitor_get = lan80xx_prbs_monitor_get,
            .mepa_driver_warmrestart_conf_get = lan80xx_restart_conf_get,
            .mepa_driver_warmrestart_conf_set = lan80xx_restart_conf_set,
            .mepa_driver_chip_temp_get = lan80xx_chip_temp_get,
            .mepa_capability = lan80xx_phy_capability,
            .mepa_debug_info_dump    = lan80xx_debug_info_dump,
            .mepa_driver_framepreempt_set = lan80xx_framepreempt_set,
            .mepa_driver_framepreempt_get = lan80xx_framepreempt_get,
            .mepa_ts = &lan80xx_ts_drivers,
            .mepa_macsec = &lan80xx_macsec_drivers,
        },
    };

    mepa_drivers_t result;
    result.phy_drv = lan80xx_drivers;
    result.count = nr_lan80xx_drivers;

    return result;
}
