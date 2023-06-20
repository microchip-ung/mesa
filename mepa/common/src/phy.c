// Copyright (c) 2004-2021 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <mepa_driver.h>
#include <microchip/ethernet/phy/api.h>

#define T_D(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);

#define PHY_FAMILIES 16
static mepa_drivers_t MEPA_phy_lib[PHY_FAMILIES] = {};
static int MEPA_init_done = 0;
mepa_trace_func_t MEPA_TRACE_FUNCTION = 0;

void MEPA_trace(mepa_trace_group_t  group,
                mepa_trace_level_t  level,
                const char         *location,
                uint32_t            line,
                const char         *format,
                ...)
{
    va_list args;
    mepa_trace_data_t data = {
        .group    = group,
        .level    = level,
        .location = location,
        .line     = line,
        .format   = format,
    };

    if (MEPA_TRACE_FUNCTION) {
        va_start(args, format);
        MEPA_TRACE_FUNCTION(&data, args);
        va_end(args);
    }
}

uint32_t mepa_phy_id_get(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                         struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx)
{
    uint32_t i;
    uint32_t phy_id = 0;
    uint16_t reg2 = 0;
    uint16_t reg3 = 0;

    // 8488, Venice and Malibu are special and does not report the PHY on the
    // normal addresses.
    uint16_t special[] = { 0x8484, 0x8487, 0x8488, 0x8489, 0x8490, 0x8491,
                           0x8254, 0x8256, 0x8257, 0x8258
                         };


    // TODO, this check would be more robust if we combine it with the values of
    // mmd=1 reg 2 and reg3 (on venice this is 0x0007 0x0400)
    if (callout->mmd_read) {
        callout->mmd_read(callout_ctx, 30, 0, &reg3);
        for (i = 0; i < sizeof(special) / sizeof(special[0]); i++) {
            if (reg3 == special[i]) {
                return reg3;
            }
        }
    }

    reg2 = 0;
    reg3 = 0;

    if (callout->miim_read) {
        callout->miim_read(callout_ctx, 2, &reg2);
        callout->miim_read(callout_ctx, 3, &reg3);
    }

    // Maybe it is a PHY responding to MMD and not MIIM
    if (callout->mmd_read && reg2 == 0 && reg3 == 0) {
        callout->mmd_read(callout_ctx, 0x1, 0x2, &reg2);
        callout->mmd_read(callout_ctx, 0x1, 0x3, &reg3);
    }

    phy_id = ((uint32_t)reg2) << 16 | reg3;

    return phy_id;
}

static size_t size_align(size_t s)
{
    if (s % 8) {
        s /= 8;
        s += 1;
        s *= 8;
    }

    return s;
}

void *mepa_mem_alloc_int(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                         struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                         size_t                                   size)
{
    void *mem;
    uint64_t *mem64;
    size_t cnt;

    if (!callout->mem_alloc) {
        T_E("No mem_alloc callout");
        return 0;
    }

    size = size_align(size);

    mem = callout->mem_alloc(callout_ctx, size);
    if (!mem) {
        T_E("Out of memory? %z", size);
        return 0;
    }

    mem64 = (uint64_t *)mem;

    size /= 8;
    for (cnt = 0; cnt < size; cnt++) {
        mem64[cnt] = 0;
    }

    return mem;
}

void mepa_mem_free_int(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                       struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                       void                                    *ptr)
{
    if (!callout->mem_free) {
        return;
    }

    callout->mem_free(callout_ctx, ptr);
}

struct mepa_device *mepa_create_int(
    mepa_driver_t *drv,
    const mepa_callout_t    MEPA_SHARED_PTR *callout,
    struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
    struct mepa_board_conf  *conf,
    int size_of_private_data)
{
    char            *mem;
    mepa_device_t   *dev;
    void            *priv;

    size_t dev_aligned = size_align(sizeof(mepa_device_t));
    size_t priv_aligned = size_align(size_of_private_data);

    mem = (char *)mepa_mem_alloc_int(callout, callout_ctx, dev_aligned + priv_aligned);
    if (!mem) {
        T_E("Alloc failed. Port: %d, size: %d", conf->numeric_handle, dev_aligned + priv_aligned);
        return NULL;
    }

    dev = (mepa_device_t *)mem;
    priv = (void *)(mem + dev_aligned);

    dev->drv = drv;
    dev->data = priv;
    dev->callout = callout;
    dev->callout_ctx = callout_ctx;
    dev->numeric_handle = conf->numeric_handle;

    T_I("mepa_device created (%d) at %p/%z, private data: %p/%z", conf->numeric_handle, dev, dev_aligned, dev->data, priv_aligned);
    return dev;
}

mepa_rc mepa_delete_int(mepa_device_t *dev)
{
    mepa_mem_free_int(dev->callout, dev->callout_ctx, dev);
    return MEPA_RC_OK;
}


struct mepa_device *mepa_create(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                struct mepa_board_conf  *conf)
{
    uint32_t phy_id = 0;
    mepa_device_t  *dev = 0;

    // Initialize all the drivers needed
    if (!MEPA_init_done) {
        // Raise conditions does not matter here. Multiple threads can do this,
        // it will waste a bit of CPU, but do no harm.
        MEPA_init_done = 1;

#if defined(MEPA_HAS_VTSS)
        MEPA_phy_lib[0] = mepa_mscc_driver_init();
        MEPA_phy_lib[1] = mepa_malibu_driver_init();
        MEPA_phy_lib[2] = mepa_venice_driver_init();
#endif

#if defined(MEPA_HAS_AQR)
        MEPA_phy_lib[3] = mepa_aqr_driver_init();
#endif

#if defined(MEPA_HAS_GPY2211)
        MEPA_phy_lib[4] = mepa_intel_driver_init();
#endif

#if defined(MEPA_HAS_LAN8814)
        MEPA_phy_lib[5] = mepa_lan8814_driver_init();
#endif

#if defined(MEPA_HAS_KSZ9031)
        MEPA_phy_lib[6] = mepa_ksz9031_driver_init();
#endif

#if defined(MEPA_HAS_LAN8770)
        MEPA_phy_lib[7] = mepa_lan8770_driver_init();
#endif
#if defined(MEPA_HAS_LAN884x)
        MEPA_phy_lib[8] = mepa_lan884x_driver_init();
#endif
        // Shall be last
#if defined(MEPA_HAS_VTSS)
        MEPA_phy_lib[9] = mepa_default_phy_driver_init();
#endif
    }

    phy_id = mepa_phy_id_get(callout, callout_ctx);

    //if (phy_id != conf->id) {
    //    T_E("PHY IDs does not match");
    //}

    for (int i = 0; i < PHY_FAMILIES; i++) {
        //if (!MEPA_phy_lib[i]) {
        //    continue;
        //}

        if (!MEPA_phy_lib[i].count || !MEPA_phy_lib[i].phy_drv) {
            continue;
        }

        for (uint32_t j = 0; j < MEPA_phy_lib[i].count; j++) {
            mepa_driver_t *driver = &MEPA_phy_lib[i].phy_drv[j];

            if ((driver->id & driver->mask) == (phy_id & driver->mask)) {
                dev = driver->mepa_driver_probe(driver, callout, callout_ctx, conf);
                if (dev) {
                    T_I("probe completed for port %d with driver id %x phy_id %x phy_family %d j %d", conf->numeric_handle, driver->id, phy_id, i, j);
                    return dev;
                }
            }
        }
    }

    //T_I(inst, "No probing");
    return 0;
}

mepa_rc mepa_delete(struct mepa_device *dev)
{
    if (!dev || !dev->drv->mepa_driver_delete) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_delete(dev);
}

mepa_rc mepa_reset(struct mepa_device *dev,
                   const mepa_reset_param_t *rst_conf)
{
    if (!dev || !dev->drv->mepa_driver_reset) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_reset(dev, rst_conf);
}

mepa_rc mepa_poll(struct mepa_device *dev,
                  mepa_status_t *status)
{
    if (!dev || !dev->drv->mepa_driver_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_poll(dev, status);
}

mepa_rc mepa_conf_set(struct mepa_device *dev,
                      const mepa_conf_t *conf)
{
    if (!dev || !dev->drv->mepa_driver_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_conf_set(dev, conf);
}

mepa_rc mepa_conf_get(struct mepa_device *dev,
                      mepa_conf_t *const conf)
{
    if (!dev || !dev->drv->mepa_driver_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_conf_get(dev, conf);
}

mepa_rc mepa_if_set(struct mepa_device *dev,
                    mepa_port_interface_t intf)
{
    if (!dev || !dev->drv->mepa_driver_if_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_if_set(dev, intf);
}

mepa_rc mepa_if_get(struct mepa_device *dev,
                    mepa_port_speed_t speed,
                    mepa_port_interface_t *intf)
{
    if (!dev || !dev->drv->mepa_driver_if_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_if_get(dev, speed, intf);
}

mepa_rc mepa_power_set(struct mepa_device *dev,
                       mepa_power_mode_t power)
{
    if (!dev || !dev->drv->mepa_driver_power_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_power_set(dev, power);
}

mepa_rc mepa_cable_diag_start(struct mepa_device *dev,
                              int mode)
{
    if (!dev || !dev->drv->mepa_driver_cable_diag_start) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_cable_diag_start(dev, mode);
}

mepa_rc mepa_cable_diag_get(struct mepa_device *dev,
                            mepa_cable_diag_result_t *result)
{
    if (!dev || !dev->drv->mepa_driver_cable_diag_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_cable_diag_get(dev, result);
}

mepa_rc mepa_media_set(struct mepa_device *dev,
                       mepa_media_interface_t phy_media_if)
{
    if (!dev || !dev->drv->mepa_driver_media_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_media_set(dev, phy_media_if);
}

mepa_rc mepa_media_get(struct mepa_device *dev,
                       mepa_media_interface_t *phy_media_if)
{
    if (!dev || !dev->drv->mepa_driver_media_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_media_get(dev, phy_media_if);
}

mepa_rc mepa_aneg_status_get(struct mepa_device *dev,
                             mepa_aneg_status_t *status)
{
    if (!dev || !dev->drv->mepa_driver_aneg_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_aneg_status_get(dev, status);
}

mepa_rc mepa_clause22_read(struct mepa_device *dev,
                           uint32_t address,
                           uint16_t *const value)
{
    if (!dev || !dev->drv->mepa_driver_clause22_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_clause22_read(dev, address, value);
}

mepa_rc mepa_clause22_write(struct mepa_device *dev,
                            uint32_t address,
                            uint16_t value)
{
    if (!dev || !dev->drv->mepa_driver_clause22_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_clause22_write(dev, address, value);
}

mepa_rc mepa_clause45_read(struct mepa_device *dev,
                           uint32_t address,
                           uint16_t *const value)
{
    if (!dev || !dev->drv->mepa_driver_clause45_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_clause45_read(dev, address, value);
}

mepa_rc mepa_clause45_write(struct mepa_device *dev,
                            uint32_t address,
                            uint16_t value)
{
    if (!dev || !dev->drv->mepa_driver_clause45_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_clause45_write(dev, address, value);
}

mepa_rc mepa_event_enable_set(struct mepa_device *dev,
                              mepa_event_t event,
                              mesa_bool_t enable)
{
    if (!dev || !dev->drv->mepa_driver_event_enable_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_event_enable_set(dev, event, enable);
}

mepa_rc mepa_event_enable_get(struct mepa_device *dev,
                              mepa_event_t *const event)
{
    if (!dev || !dev->drv->mepa_driver_event_enable_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_event_enable_get(dev, event);
}

mepa_rc mepa_event_poll(struct mepa_device *dev,
                        mepa_event_t *const ev_mask)
{
    if (!dev || !dev->drv->mepa_driver_event_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_event_poll(dev, ev_mask);
}

mepa_rc mepa_loopback_set(struct mepa_device *dev,
                          const mepa_loopback_t *loopback)
{
    if (!dev || !dev->drv->mepa_driver_loopback_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_loopback_set(dev, loopback);
}

mepa_rc mepa_loopback_get(struct mepa_device *dev,
                          mepa_loopback_t *const loopback)
{
    if (!dev || !dev->drv->mepa_driver_loopback_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_loopback_get(dev, loopback);
}

mepa_rc mepa_gpio_mode_set(struct mepa_device *dev,
                           const mepa_gpio_conf_t *data)
{
    if (!dev || !dev->drv->mepa_driver_gpio_mode_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_gpio_mode_set(dev, data);
}

mepa_rc mepa_gpio_out_set(struct mepa_device *dev,
                          uint8_t gpio_no,
                          mepa_bool_t value)
{
    if (!dev || !dev->drv->mepa_driver_gpio_out_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_gpio_out_set(dev, gpio_no, value);
}

mepa_rc mepa_gpio_in_get(struct mepa_device *dev,
                         uint8_t gpio_no,
                         mepa_bool_t *const value)
{
    if (!dev || !dev->drv->mepa_driver_gpio_in_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_gpio_in_get(dev, gpio_no, value);
}

mepa_rc mepa_synce_clock_conf_set(struct mepa_device *dev,
                                  const mepa_synce_clock_conf_t *conf)
{
    if (!dev || !dev->drv->mepa_driver_synce_clock_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_synce_clock_conf_set(dev, conf);
}

mepa_rc mepa_link_base_port(struct mepa_device *dev,
                            struct mepa_device *base_dev,
                            uint8_t packet_idx)
{
    if (!dev || !dev->drv->mepa_driver_link_base_port) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_link_base_port(dev, base_dev, packet_idx);
}

mepa_rc mepa_phy_info_get(struct mepa_device *dev,
                          mepa_phy_info_t *const phy_info)
{
    if (!dev || !dev->drv->mepa_driver_phy_info_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_phy_info_get(dev, phy_info);
}

mepa_rc mepa_isolate_mode_conf(struct mepa_device *dev,
                               const mepa_bool_t iso_en)
{
    if (!dev || !dev->drv->mepa_driver_phy_info_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_isolate_mode_conf(dev, iso_en);
}

mepa_rc mepa_i2c_read(struct mepa_device  *dev,
                        const uint8_t      i2c_mux,
                        const uint8_t      i2c_reg_addr,
                        const uint8_t      i2c_dev_addr,
                        const mepa_bool_t  word_access,
                        uint8_t            cnt,
                        uint8_t  *const    value)
{
    if (!dev || !dev->drv->mepa_driver_phy_i2c_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_phy_i2c_read(dev, i2c_mux, i2c_reg_addr, i2c_dev_addr, word_access, cnt, value);
}

mepa_rc mepa_i2c_write(struct mepa_device *dev,
                        const uint8_t      i2c_mux,
                        const uint8_t      i2c_reg_addr,
                        const uint8_t      i2c_dev_addr,
                        const mepa_bool_t  word_access,
                        uint8_t            cnt,
                        const uint8_t           *value)
{
    if (!dev || !dev->drv->mepa_driver_phy_i2c_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_phy_i2c_write(dev, i2c_mux, i2c_reg_addr, i2c_dev_addr, word_access, cnt, value);
}

mepa_rc mepa_i2c_clock_select(struct mepa_device *dev, mepa_i2c_clk_select_t const *clk_value)
{

    if (!dev || !dev->drv->mepa_driver_phy_i2c_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_phy_i2c_clock_select(dev, clk_value);
}

mepa_rc mepa_ts_mode_set(struct mepa_device *dev,
                         const mepa_bool_t enable)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_mode_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_mode_set(dev, enable);
}

mepa_rc mepa_ts_mode_get(struct mepa_device *dev,
                         mepa_bool_t *const enable)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_mode_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_mode_get(dev, enable);
}

mepa_rc mepa_ts_reset(struct mepa_device *dev,
                      const mepa_ts_reset_conf_t *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_reset) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_reset(dev, conf);
}

mepa_rc mepa_ts_init_conf_set(struct mepa_device              *dev,
                              const mepa_ts_init_conf_t       *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_init_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_init_conf_set(dev, conf);
}

mepa_rc mepa_ts_init_conf_get(struct mepa_device              *dev,
                              mepa_ts_init_conf_t             *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_init_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_init_conf_get(dev, conf);
}

mepa_rc mepa_ts_ltc_ls_en(struct mepa_device                  *dev,
                          mepa_ts_ls_type_t                    const type)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_ltc_ls_en) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ltc_ls_en(dev, type);
}

mepa_rc mepa_ts_ltc_get(struct mepa_device                    *dev,
                        mepa_timestamp_t                      *const ts)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_ltc_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ltc_get(dev, ts);
}

mepa_rc mepa_ts_ltc_set(struct mepa_device                    *dev,
                        const mepa_timestamp_t                *const ts)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_ltc_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ltc_set(dev, ts);
}

mepa_rc mepa_ts_delay_asymmetry_get(struct mepa_device        *dev,
                                    mepa_timeinterval_t       *const delay)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_delay_asymmetry_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_delay_asymmetry_get(dev, delay);
}

mepa_rc mepa_ts_delay_asymmetry_set(struct mepa_device        *dev,
                                    const mepa_timeinterval_t *const delay)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_delay_asymmetry_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_delay_asymmetry_set(dev, delay);
}

mepa_rc mepa_ts_path_delay_get(struct mepa_device             *dev,
                               mepa_timeinterval_t            *const delay)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_path_delay_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_path_delay_get(dev, delay);
}

mepa_rc mepa_ts_path_delay_set(struct mepa_device *dev,
                               const mepa_timeinterval_t      *const delay)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_path_delay_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_path_delay_set(dev, delay);
}

mepa_rc mepa_ts_egress_latency_get(struct mepa_device         *dev,
                                   mepa_timeinterval_t        *const latency)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_egress_latency_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_egress_latency_get(dev, latency);
}

mepa_rc mepa_ts_egress_latency_set(struct mepa_device         *dev,
                                   const mepa_timeinterval_t  *const latency)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_egress_latency_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_egress_latency_set(dev, latency);
}

mepa_rc mepa_ts_ingress_latency_get(struct mepa_device        *dev,
                                    mepa_timeinterval_t       *const latency)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_ingress_latency_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ingress_latency_get(dev, latency);
}

mepa_rc mepa_ts_ingress_latency_set(struct mepa_device        *dev,
                                    const mepa_timeinterval_t *const latency)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_ingress_latency_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_ingress_latency_set(dev, latency);
}

mepa_rc mepa_ts_clock_rateadj_get(struct mepa_device          *dev,
                                  mepa_ts_scaled_ppb_t        *const rateadj)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_clock_rateadj_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_clock_rateadj_get(dev, rateadj);
}

mepa_rc mepa_ts_clock_rateadj_set(struct mepa_device          *dev,
                                  const mepa_ts_scaled_ppb_t  *const rateadj)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_clock_rateadj_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_clock_rateadj_set(dev, rateadj);
}

mepa_rc mepa_ts_clock_adj1ns(struct mepa_device               *dev,
                             const mepa_bool_t                 incr)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_clock_adj1ns) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_clock_adj1ns(dev, incr);
}

mepa_rc mepa_ts_pps_conf_get(struct mepa_device               *dev,
                             mepa_ts_pps_conf_t               *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_pps_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_pps_conf_get(dev, conf);
}

mepa_rc mepa_ts_pps_conf_set(struct mepa_device              *dev,
                             const mepa_ts_pps_conf_t        *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_pps_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_pps_conf_set(dev, conf);
}

mepa_rc mepa_ts_rx_classifier_conf_get(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       mepa_ts_classifier_t       *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_get(dev, flow_index, conf);
}

mepa_rc mepa_ts_tx_classifier_conf_get(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       mepa_ts_classifier_t       *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_get(dev, flow_index, conf);
}

mepa_rc mepa_ts_rx_classifier_conf_set(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       const mepa_ts_classifier_t *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_rx_classifier_conf_set(dev, flow_index, conf);
}

mepa_rc mepa_ts_tx_classifier_conf_set(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       const mepa_ts_classifier_t *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_tx_classifier_conf_set(dev, flow_index, conf);
}

mepa_rc mepa_ts_rx_clock_conf_get(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  mepa_ts_ptp_clock_conf_t        *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_rx_clock_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_rx_clock_conf_get(dev, clock_id, conf);
}

mepa_rc mepa_ts_tx_clock_conf_get(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  mepa_ts_ptp_clock_conf_t        *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_tx_clock_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_tx_clock_conf_get(dev, clock_id, conf);
}

mepa_rc mepa_ts_rx_clock_conf_set(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  const mepa_ts_ptp_clock_conf_t  *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_rx_clock_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_rx_clock_conf_set(dev, clock_id, conf);
}

mepa_rc mepa_ts_tx_clock_conf_set(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  const mepa_ts_ptp_clock_conf_t  *const conf)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_tx_clock_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_tx_clock_conf_set(dev, clock_id, conf);
}

mepa_rc mepa_ts_stats_get(struct mepa_device                    *dev,
                          mepa_ts_stats_t                       *const stat)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_stats_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_stats_get(dev, stat);
}

mepa_rc mepa_ts_event_set(struct mepa_device                      *dev,
                          const mepa_bool_t                        enable,
                          const mepa_ts_event_t                    ev_mask)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_event_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_event_set(dev, enable, ev_mask);
}

mepa_rc mepa_ts_event_get(struct mepa_device                      *dev,
                          mepa_ts_event_t                         *const ev_mask)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_event_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_event_get(dev, ev_mask);
}

mepa_rc mepa_ts_event_poll(struct mepa_device                     *dev,
                           mepa_ts_event_t                        *const status)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_event_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_event_poll(dev, status);
}

mepa_rc mepa_ts_fifo_read_install(struct mepa_device *dev, mepa_ts_fifo_read_t rd_cb)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_fifo_read_install) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    dev->drv->mepa_ts->mepa_ts_fifo_read_install(dev, rd_cb);
    return MESA_RC_OK;
}

mepa_rc mepa_ts_fifo_empty(struct mepa_device                     *dev)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_fifo_empty) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_fifo_empty(dev);
}

mepa_rc mepa_ts_fifo_get(struct mepa_device *dev, mepa_fifo_ts_entry_t ts_list[], const size_t size, uint32_t *const num)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_fifo_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_fifo_get(dev, ts_list, size, num);
}

mepa_rc mepa_ts_test_config(struct mepa_device                    *dev,
                            uint16_t                               test_id,
                            mepa_bool_t                            reg_dump)
{
    if (!dev->drv->mepa_ts) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_ts->mepa_ts_test_config) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_ts->mepa_ts_test_config(dev, test_id, reg_dump);
}

mepa_rc mepa_debug_info_dump(struct mepa_device *dev,
                             const mepa_debug_print_t pr,
                             const mepa_debug_info_t   *const info)
{
    if (!dev || !dev->drv->mepa_debug_info_dump) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_debug_info_dump(dev, pr, info);
}

mepa_rc mepa_sqi_read(struct mepa_device *dev, uint32_t *const value)
{
    if (!dev->drv->mepa_driver_sqi_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_sqi_read(dev, value);
}

mepa_rc mepa_start_of_frame_conf_set(struct mepa_device *dev, mepa_start_of_frame_conf_t *const conf)
{
    if (!dev->drv->mepa_driver_start_of_frame_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_start_of_frame_conf_set(dev, conf);
}

mepa_rc mepa_start_of_frame_conf_get(struct mepa_device *dev, mepa_start_of_frame_conf_t *const rd_val)
{
    if (!dev->drv->mepa_driver_start_of_frame_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_start_of_frame_conf_get(dev, rd_val);
}

mepa_rc mepa_framepreempt_get(struct mepa_device *dev, mepa_bool_t *const value)
{
    if (!dev->drv->mepa_driver_framepreempt_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_framepreempt_get(dev, value);
}

mepa_rc mepa_selftest_start(struct mepa_device *dev, const mepa_selftest_info_t *inf)
{
    if (!dev->drv->mepa_driver_selftest_start) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_selftest_start(dev, inf);
}

mepa_rc mepa_selftest_read(struct mepa_device *dev, mepa_selftest_info_t *const inf)
{
    if (!dev->drv->mepa_driver_selftest_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_selftest_read(dev, inf);
}

mepa_rc mepa_macsec_init_set(struct mepa_device *dev, const
                             mepa_macsec_init_t *const macsec_init)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_init_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_init_set(dev, macsec_init);
}

mepa_rc mepa_macsec_init_get(struct mepa_device *dev,
                             mepa_macsec_init_t *const macsec_init)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_init_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_init_get(dev, macsec_init);
}

mepa_rc mepa_macsec_secy_conf_add(struct mepa_device *dev,
                             const mepa_macsec_port_t port,
                             const mepa_macsec_secy_conf_t *const conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_conf_add) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_conf_add(dev, port, conf);
}

mepa_rc mepa_macsec_secy_conf_update(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     const mepa_macsec_secy_conf_t *const conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_conf_update) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_conf_update(dev, port, conf);
}

mepa_rc mepa_macsec_secy_conf_get(struct mepa_device *dev,
                                  const mepa_macsec_port_t port,
                                  mepa_macsec_secy_conf_t *const conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_conf_get(dev, port, conf);
}

mepa_rc mepa_macsec_secy_conf_del(struct mepa_device *dev,
                                  const mepa_macsec_port_t port)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_conf_del) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_conf_del(dev, port);
}

mepa_rc mepa_macsec_secy_controlled_set(struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        const mepa_bool_t enable)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_controlled_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_controlled_set(dev, port, enable);

}

mepa_rc mepa_macsec_secy_controlled_get(struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        mepa_bool_t *const enable)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_controlled_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_controlled_get(dev, port, enable);

}

mepa_rc mepa_macsec_secy_port_status_get(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         mepa_macsec_secy_port_status_t *const status)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_port_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_port_status_get(dev, port, status);

}

mepa_rc mepa_macsec_port_get_next(struct mepa_device *dev,
                                  const mepa_port_no_t port_no,
                                  const mepa_macsec_port_t *const search_macsec_port,
                                  mepa_macsec_port_t *const found_macsec_port)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_port_get_next) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_port_get_next(dev, port_no, search_macsec_port, found_macsec_port);
}

mepa_rc mepa_macsec_rx_sc_add(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sc_add) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sc_add(dev, port, sci);
}

mepa_rc mepa_macsec_rx_sc_update(struct mepa_device *dev,
                                 const mepa_macsec_port_t port,
                                 const mepa_macsec_sci_t  *const sci,
                                 const mepa_macsec_rx_sc_conf_t *const conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sc_update) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sc_update(dev, port, sci, conf);
}

mepa_rc mepa_macsec_rx_sc_get_conf(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const mepa_macsec_sci_t *const sci,
                                   mepa_macsec_rx_sc_conf_t *const conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sc_get_conf) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sc_get_conf(dev, port, sci, conf);
}

mepa_rc mepa_macsec_rx_sc_get_next(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const mepa_macsec_sci_t *const search_sci,
                                   mepa_macsec_sci_t *const found_sci)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sc_get_next) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sc_get_next(dev, port, search_sci, found_sci);
}

mepa_rc mepa_macsec_rx_sc_del(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sc_del) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sc_del(dev, port, sci);
}

mepa_rc mepa_macsec_rx_sc_status_get(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     const mepa_macsec_sci_t *const sci,
                                     mepa_macsec_rx_sc_status_t *const status)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sc_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sc_status_get(dev, port, sci, status);
}

mepa_rc mepa_macsec_tx_sc_set(struct mepa_device *dev,
                              const mepa_macsec_port_t port)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sc_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sc_set(dev, port);
}

mepa_rc mepa_macsec_tx_sc_update(struct mepa_device *dev,
                                 const mepa_macsec_port_t port,
                                 const mepa_macsec_tx_sc_conf_t *const conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sc_update) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sc_update(dev, port, conf);
}

mepa_rc mepa_macsec_tx_sc_get_conf(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   mepa_macsec_tx_sc_conf_t *const conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sc_get_conf) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sc_get_conf(dev, port, conf);
}

mepa_rc mepa_macsec_tx_sc_del(struct mepa_device *dev,
                              const mepa_macsec_port_t port)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sc_del) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sc_del(dev, port);
}

mepa_rc mepa_macsec_tx_sc_status_get(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     mepa_macsec_tx_sc_status_t *const status)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sc_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sc_status_get(dev, port, status);
}

mepa_rc mepa_macsec_rx_sa_set(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci,
                              const uint16_t an,
                              const uint32_t lowest_pn,
                              const mepa_macsec_sak_t *const sak)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sa_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sa_set(dev, port, sci, an, lowest_pn, sak);
}

mepa_rc mepa_macsec_rx_sa_get(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci,
                              const uint16_t an,
                              uint32_t *const lowest_pn,
                              mepa_macsec_sak_t *const sak,
                              mepa_bool_t *const active)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sa_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sa_get(dev, port, sci, an, lowest_pn, sak, active);
}

mepa_rc mepa_macsec_rx_sa_activate(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const mepa_macsec_sci_t *const sci,
                                   const uint16_t an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sa_activate) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sa_activate(dev, port, sci, an);
}

mepa_rc mepa_macsec_rx_sa_disable(struct mepa_device *dev,
                                  const mepa_macsec_port_t port,
                                  const mepa_macsec_sci_t *const sci,
                                  const uint16_t an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sa_disable) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sa_disable(dev, port, sci, an);
}

mepa_rc mepa_macsec_rx_sa_del(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci,
                              const uint16_t an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sa_del) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sa_del(dev, port, sci, an);
}

mepa_rc mepa_macsec_rx_sa_lowest_pn_update(struct mepa_device *dev,
                                           const mepa_macsec_port_t port,
                                           const mepa_macsec_sci_t *const sci,
                                           const uint16_t an,
                                           const uint32_t lowest_pn)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sa_lowest_pn_update) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sa_lowest_pn_update(dev, port, sci, an, lowest_pn);
}

mepa_rc mepa_macsec_rx_sa_status_get(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     const mepa_macsec_sci_t *const sci,
                                     const uint16_t an,
                                     mepa_macsec_rx_sa_status_t *const status)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sa_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sa_status_get(dev, port, sci, an, status);
}

mepa_rc mepa_macsec_rx_seca_set(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_sci_t *const sci,
                                const uint16_t an,
                                const mepa_macsec_pkt_num_t lowest_pn,
                                const mepa_macsec_sak_t *const sak,
                                const mepa_macsec_ssci_t *const ssci)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_seca_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_seca_set(dev, port, sci, an, lowest_pn, sak, ssci);
}

mepa_rc mepa_macsec_rx_seca_get(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_sci_t *const sci,
                                const uint16_t an,
                                mepa_macsec_pkt_num_t *const lowest_pn,
                                mepa_macsec_sak_t *const sak,
                                mepa_bool_t *const active,
                                mepa_macsec_ssci_t *const ssci)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_seca_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_seca_get(dev, port, sci, an, lowest_pn, sak, active, ssci);
}

mepa_rc mepa_macsec_rx_seca_lowest_pn_update(struct mepa_device *dev,
                                             const mepa_macsec_port_t port,
                                             const mepa_macsec_sci_t *const sci,
                                             const uint16_t an,
                                             const mepa_macsec_pkt_num_t lowest_pn)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_seca_lowest_pn_update) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_seca_lowest_pn_update(dev, port, sci, an, lowest_pn);
}

mepa_rc mepa_macsec_tx_sa_set(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const uint16_t an,
                              const uint32_t next_pn,
                              const mepa_bool_t confidentiality,
                              const mepa_macsec_sak_t *const sak)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sa_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sa_set(dev, port, an, next_pn, confidentiality, sak);
}

mepa_rc mepa_macsec_tx_sa_get(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const uint16_t an,
                              uint32_t *const next_pn,
                              mepa_bool_t *const confidentiality,
                              mepa_macsec_sak_t *const sak,
                              mepa_bool_t *const active)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sa_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sa_get(dev, port, an, next_pn, confidentiality, sak, active);
}

mepa_rc mepa_macsec_tx_sa_activate(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const uint16_t an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sa_activate) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sa_activate(dev, port, an);
}

mepa_rc mepa_macsec_tx_sa_disable(struct mepa_device *dev,
                                  const mepa_macsec_port_t port,
                                  const uint16_t an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sa_disable) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sa_disable(dev, port, an);
}

mepa_rc mepa_macsec_tx_sa_del(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const uint16_t an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sa_del) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sa_del(dev, port, an);
}

mepa_rc mepa_macsec_tx_sa_status_get(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     const uint16_t an,
                                     mepa_macsec_tx_sa_status_t *const status)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sa_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sa_status_get(dev, port, an, status);
}

mepa_rc mepa_macsec_tx_seca_set(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const uint16_t an,
                                const mepa_macsec_pkt_num_t next_pn,
                                const mepa_bool_t confidentiality,
                                const mepa_macsec_sak_t *const sak,
                                const mepa_macsec_ssci_t *const ssci)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_seca_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_seca_set(dev, port, an, next_pn, confidentiality, sak, ssci);
}

mepa_rc mepa_macsec_tx_seca_get(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const uint16_t an,
                                mepa_macsec_pkt_num_t *const next_pn,
                                mepa_bool_t *const confidentiality,
                                mepa_macsec_sak_t *const sak,
                                mepa_bool_t *const active,
                                mepa_macsec_ssci_t *const ssci)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_seca_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_seca_get(dev, port, an, next_pn, confidentiality, sak, active, ssci);
}

mepa_rc mepa_macsec_controlled_counters_get(struct mepa_device *dev,
                                            const mepa_macsec_port_t port,
                                            mepa_macsec_secy_port_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_controlled_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_controlled_counters_get(dev, port, counters);
}

mepa_rc mepa_macsec_uncontrolled_counters_get(struct mepa_device                   *dev,
                                              const mepa_port_no_t                port_no,
                                              mepa_macsec_uncontrolled_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_uncontrolled_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_uncontrolled_counters_get(dev, port_no, counters);
}

mepa_rc mepa_macsec_common_counters_get(struct mepa_device *dev,
                                        const mepa_port_no_t port_no,
                                        mepa_macsec_common_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_common_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_common_counters_get(dev, port_no, counters);
}

mepa_rc mepa_macsec_secy_cap_get(struct mepa_device *dev,
                                 const mepa_port_no_t port_no,
                                 mepa_macsec_secy_cap_t *const cap)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_cap_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_cap_get(dev, port_no, cap);
}

mepa_rc mepa_macsec_secy_counters_get(struct mepa_device *dev,
                                      const mepa_macsec_port_t port,
                                      mepa_macsec_secy_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_counters_get(dev, port, counters);
}

mepa_rc mepa_macsec_counters_update(struct mepa_device *dev,
                                    const mepa_port_no_t port_no)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_counters_update) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_counters_update(dev, port_no);
}

mepa_rc mepa_macsec_counters_clear(struct mepa_device *dev,
                                   const mepa_port_no_t port_no)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_counters_clear(dev, port_no);
}

mepa_rc mepa_macsec_rx_sc_counters_get(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
				       const mepa_macsec_sci_t *const sci,
                                       mepa_macsec_rx_sc_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sc_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sc_counters_get(dev, port, sci, counters);
}

mepa_rc mepa_macsec_tx_sc_counters_get(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
				       mepa_macsec_tx_sc_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sc_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sc_counters_get(dev, port, counters);
}

mepa_rc mepa_macsec_tx_sa_counters_get(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
				       const uint16_t an,
				       mepa_macsec_tx_sa_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_tx_sa_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_tx_sa_counters_get(dev, port, an, counters);
}

mepa_rc mepa_macsec_rx_sa_counters_get(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
	                               const mepa_macsec_sci_t *const sci,
				       const uint16_t an,
				       mepa_macsec_rx_sa_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rx_sa_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rx_sa_counters_get(dev, port, sci, an, counters);
}

mepa_rc mepa_macsec_control_frame_match_conf_set(struct mepa_device *dev,
                                                 const mepa_port_no_t port_no,
                                                 const mepa_macsec_control_frame_match_conf_t *const conf,
                                                 uint32_t *const rule_id)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_control_frame_match_conf_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_control_frame_match_conf_set(dev, port_no, conf, rule_id);
}

mepa_rc mepa_macsec_control_frame_match_conf_del(struct mepa_device *dev,
                                                 const mepa_port_no_t port_no,
                                                 const uint32_t rule_id)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_control_frame_match_conf_del) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_control_frame_match_conf_del(dev, port_no, rule_id);
}

mepa_rc mepa_macsec_control_frame_match_conf_get(struct mepa_device *dev,
                                                 const mepa_port_no_t port_no,
                                                 mepa_macsec_control_frame_match_conf_t *const conf,
                                                 uint32_t rule_id)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_control_frame_match_conf_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_control_frame_match_conf_get(dev, port_no, conf, rule_id);
}

mepa_rc mepa_macsec_pattern_set(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_direction_t direction,
                                const mepa_macsec_match_action_t action,
                                const mepa_macsec_match_pattern_t *const pattern)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_pattern_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_pattern_set(dev, port, direction, action, pattern);
}

mepa_rc mepa_macsec_pattern_del(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_direction_t direction,
                                const mepa_macsec_match_action_t action)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_pattern_del) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_pattern_del(dev, port, direction, action);
}

mepa_rc mepa_macsec_pattern_get(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_direction_t direction,
                                const mepa_macsec_match_action_t action,
                                mepa_macsec_match_pattern_t *const pattern)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_pattern_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_pattern_get(dev, port, direction, action, pattern);
}

mepa_rc mepa_macsec_default_action_set(struct mepa_device *dev,
                                       const mepa_port_no_t port_no,
                                       const mepa_macsec_default_action_policy_t *const policy)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_default_action_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_default_action_set(dev, port_no, policy);
}

mepa_rc mepa_macsec_default_action_get(struct mepa_device *dev,
                                       const mepa_port_no_t port_no,
                                       mepa_macsec_default_action_policy_t *const policy)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_default_action_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_default_action_get(dev, port_no, policy);
}

mepa_rc mepa_macsec_bypass_mode_set(struct mepa_device *dev,
                                    const mepa_port_no_t port_no,
                                    const mepa_macsec_bypass_mode_t *const bypass)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_bypass_mode_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_bypass_mode_set(dev, port_no, bypass);
}

mepa_rc mepa_macsec_bypass_mode_get(struct mepa_device *dev,
                                    const mepa_port_no_t port_no,
                                    mepa_macsec_bypass_mode_t *const bypass)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_bypass_mode_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_bypass_mode_get(dev, port_no, bypass);
}

mepa_rc mepa_macsec_bypass_tag_set(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const mepa_macsec_tag_bypass_t tag)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_bypass_tag_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_bypass_tag_set(dev, port, tag);
}

mepa_rc mepa_macsec_bypass_tag_get(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   mepa_macsec_tag_bypass_t *const tag)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_bypass_tag_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_bypass_tag_get(dev, port, tag);
}

mepa_rc mepa_macsec_mtu_set(struct mepa_device *dev,
                            const mepa_port_no_t port_no,
                            const mepa_macsec_mtu_t *const mtu_conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_mtu_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_mtu_set(dev, port_no, mtu_conf);
}

mepa_rc mepa_macsec_mtu_get(struct mepa_device *dev,
                            const mepa_port_no_t port_no,
                            mepa_macsec_mtu_t *mtu_conf)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_mtu_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_mtu_get(dev, port_no, mtu_conf);
}

mepa_rc mepa_macsec_frame_capture_set(struct mepa_device *dev,
                                      const mepa_port_no_t port_no,
                                      const mepa_macsec_frame_capture_t capture)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_frame_capture_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_frame_capture_set(dev, port_no, capture);
}

mepa_rc mepa_macsec_frame_get(struct mepa_device *dev,
                              const mepa_port_no_t port_no,
                              const uint32_t buf_length,
                              uint32_t *const return_length,
                              uint8_t *const frame)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_frame_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_frame_get(dev, port_no, buf_length, return_length, frame);
}

mepa_rc mepa_macsec_event_enable_set(struct mepa_device *dev,
                                     const mepa_port_no_t port_no,
                                     const mepa_macsec_event_t ev_mask,
                                     const mepa_bool_t enable)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_event_enable_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_event_enable_set(dev, port_no, ev_mask, enable);
}

mepa_rc mepa_macsec_event_enable_get(struct mepa_device *dev,
                                     const mepa_port_no_t port_no,
                                     mepa_macsec_event_t *const ev_mask)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_event_enable_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_event_enable_get(dev, port_no, ev_mask);
}

mepa_rc mepa_macsec_event_poll(struct mepa_device *dev,
                               const mepa_port_no_t port_no,
                               mepa_macsec_event_t *const ev_mask)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_event_poll) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_event_poll(dev, port_no, ev_mask);
}

mepa_rc mepa_macsec_event_seq_threshold_set(struct mepa_device *dev,
                                            const mepa_port_no_t port_no,
                                            const uint32_t threshold)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_event_seq_threshold_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_event_seq_threshold_set(dev, port_no, threshold);
}

mepa_rc mepa_macsec_event_seq_threshold_get(struct mepa_device *dev,
                                            const mepa_port_no_t port_no,
                                            uint32_t *const threshold)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_event_seq_threshold_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_event_seq_threshold_get(dev, port_no, threshold);
}

mepa_rc mepa_macsec_egr_intr_sa_get(struct mepa_device *dev,
                                    const mepa_port_no_t port_no,
                                    mepa_macsec_port_t *const port,
                                    uint16_t *const an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_egr_intr_sa_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_egr_intr_sa_get(dev, port_no, port, an);
}

mepa_rc mepa_macsec_csr_read(struct mepa_device *dev,
                             const mepa_port_no_t port_no,
                             const uint16_t mmd,
                             const uint32_t addr,
                             uint32_t *const value)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_csr_read) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_csr_read(dev, port_no, mmd, addr, value);
}

mepa_rc mepa_macsec_csr_write(struct mepa_device *dev,
                              const mepa_port_no_t port_no,
                              const uint32_t mmd,
                              const uint32_t addr,
                              const uint32_t value)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_csr_write) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_csr_write(dev, port_no, mmd, addr, value);
}

mepa_rc mepa_macsec_dbg_counter_get(struct mepa_device *dev,
                                    const mepa_port_no_t port_no,
                                    mepa_macsec_rc_dbg_counters_t *const counters)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_dbg_counter_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_dbg_counter_get(dev, port_no, counters);
}

mepa_rc mepa_macsec_hmac_counters_get(struct mepa_device *dev,
                                      const mepa_port_no_t port_no,
                                      mepa_macsec_mac_counters_t *const counters,
                                      const mepa_bool_t clear)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_hmac_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_hmac_counters_get(dev, port_no, counters, clear);
}

mepa_rc mepa_macsec_lmac_counters_get(struct mepa_device *dev,
                                      const mepa_port_no_t port_no,
                                      mepa_macsec_mac_counters_t *const counters,
                                      const mepa_bool_t clear)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_lmac_counters_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_lmac_counters_get(dev, port_no, counters, clear);
}

mepa_rc mepa_macsec_is_capable(struct mepa_device *dev,
                               const mepa_port_no_t port_no,
                               mepa_bool_t *capable)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_is_capable) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_is_capable(dev, port_no, capable);
}

mepa_rc mepa_macsec_dbg_reg_dump(struct mepa_device *dev,
                                 const mepa_port_no_t port_no,
                                 const mepa_debug_print_t pr)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_dbg_reg_dump) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_dbg_reg_dump(dev, port_no, pr);
}

mepa_rc mepa_macsec_inst_count_get(struct mepa_device *dev,
                                   const mepa_port_no_t port_no,
                                   mepa_macsec_inst_count_t *count)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_inst_count_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_inst_count_get(dev, port_no, count);
}

mepa_rc mepa_macsec_lmac_counters_clear(struct mepa_device *dev,
                                        const mepa_port_no_t port_no)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_lmac_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_lmac_counters_clear(dev, port_no);
}

mepa_rc mepa_macsec_hmac_counters_clear(struct mepa_device *dev,
                                        const mepa_port_no_t port_no)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_hmac_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_hmac_counters_clear(dev, port_no);
}

mepa_rc mepa_macsec_debug_counters_clear(struct mepa_device *dev,
                                         const mepa_port_no_t port_no)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_debug_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_debug_counters_clear(dev, port_no);
}

mepa_rc mepa_macsec_common_counters_clear(struct mepa_device *dev,
                                          const mepa_port_no_t port_no)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_common_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_common_counters_clear(dev, port_no);
}

mepa_rc mepa_macsec_uncontrolled_counters_clear(struct mepa_device *dev,
                                                const mepa_port_no_t port_no)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_uncontrolled_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_uncontrolled_counters_clear(dev, port_no);
}

mepa_rc mepa_macsec_controlled_counters_clear(struct mepa_device *dev,
                                              const mepa_macsec_port_t port)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_controlled_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_controlled_counters_clear(dev, port);
}

mepa_rc mepa_macsec_rxsa_counters_clear(struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        const mepa_macsec_sci_t *const sci,
                                        const uint16_t an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rxsa_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rxsa_counters_clear(dev, port, sci, an);
}

mepa_rc mepa_macsec_rxsc_counters_clear(struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        const mepa_macsec_sci_t  *const sci)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rxsc_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rxsc_counters_clear(dev, port, sci);
}

mepa_rc mepa_macsec_txsa_counters_clear(struct mepa_device *dev,
                                        const mepa_macsec_port_t  port,
                                        const uint16_t  an)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_txsa_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_txsa_counters_clear(dev, port, an);
}

mepa_rc mepa_macsec_txsc_counters_clear(struct mepa_device *dev,
                                        const mepa_macsec_port_t port)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_txsc_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_txsc_counters_clear(dev, port);
}

mepa_rc mepa_macsec_secy_counters_clear(struct mepa_device *dev,
                                        const mepa_macsec_port_t port)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_secy_counters_clear) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_secy_counters_clear(dev, port);
}

mepa_rc mepa_macsec_port_enable_status_get(struct mepa_device *dev,
                                           const mepa_port_no_t port_no,
                                           mepa_bool_t *status)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_port_enable_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_port_enable_status_get(dev, port_no, status);
}

mepa_rc mepa_macsec_rxsa_an_status_get (struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        const mepa_macsec_sci_t *const sci,
                                        const uint16_t an,
                                        mepa_bool_t *status)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_rxsa_an_status_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_rxsa_an_status_get(dev, port, sci, an, status);
}

mepa_rc mepa_mac_block_mtu_get(struct mepa_device *dev,
                               const mepa_port_no_t port_no,
                               uint16_t *const mtu_value,
                               mepa_bool_t *const mtu_tag_check)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_mac_block_mtu_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_mac_block_mtu_get(dev, port_no, mtu_value, mtu_tag_check);
}

mepa_rc mepa_mac_block_mtu_set(struct mepa_device *dev,
                               const mepa_port_no_t port_no,
                               const uint16_t mtu_value,
                               const mepa_bool_t mtu_tag_check)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_mac_block_mtu_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_mac_block_mtu_set(dev, port_no, mtu_value, mtu_tag_check);
}

mepa_rc mepa_macsec_fcbuf_frame_gap_comp_set(struct mepa_device *dev,
                                             const mepa_port_no_t port_no,
                                             const uint8_t frm_gap)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_fcbuf_frame_gap_comp_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_fcbuf_frame_gap_comp_set(dev, port_no, frm_gap);
}

mepa_rc mepa_macsec_dbg_fcb_block_reg_dump(struct mepa_device *dev,
                                           const mepa_port_no_t port_no,
                                           const mepa_debug_print_t pr)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_dbg_fcb_block_reg_dump) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_dbg_fcb_block_reg_dump(dev, port_no, pr);
}

mepa_rc mepa_macsec_dbg_frm_match_handling_ctrl_reg_dump(struct mepa_device *dev,
                                                         const mepa_port_no_t port_no,
                                                         const mepa_debug_print_t pr)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_dbg_frm_match_handling_ctrl_reg_dump) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_dbg_frm_match_handling_ctrl_reg_dump(dev, port_no, pr);
}

#ifdef MEPA_MACSEC_FIFO_OVERFLOW_WORKAROUND

mepa_rc mepa_macsec_dbg_reconfig(struct mepa_device *dev,
                                 const mepa_port_no_t port_no)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_dbg_reconfig) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_dbg_reconfig(dev, port_no);
}

#endif


mepa_rc mepa_macsec_dbg_update_seq_set(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
                                       const mepa_macsec_sci_t *const sci,
                                       uint16_t an,
                                       mepa_bool_t egr,
                                       const mepa_bool_t disable)
{
    if (!dev->drv->mepa_macsec) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    if (!dev->drv->mepa_macsec->mepa_macsec_dbg_update_seq_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_macsec->mepa_macsec_dbg_update_seq_set(dev, port, sci, an, egr, disable);
}

mepa_rc mepa_prbs_set(struct mepa_device *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const prbs_conf)
{
    if (!dev->drv->mepa_driver_prbs_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_prbs_set(dev, type, direction, prbs_conf);
}

mepa_rc mepa_prbs_get(struct mepa_device *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction, mepa_phy_prbs_generator_conf_t *const prbs_conf)
{
    if (!dev->drv->mepa_driver_prbs_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_prbs_get(dev, type, direction, prbs_conf);
}

mepa_rc mepa_prbs_monitor_set(struct mepa_device *dev, mepa_phy_prbs_monitor_conf_t *const value)
{
    if (!dev->drv->mepa_driver_prbs_monitor_set) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_prbs_monitor_set(dev, value);
}

mepa_rc mepa_prbs_monitor_get(struct mepa_device *dev, mepa_phy_prbs_monitor_conf_t *const value)
{
    if (!dev->drv->mepa_driver_prbs_monitor_get) {
        return MESA_RC_NOT_IMPLEMENTED;
    }

    return dev->drv->mepa_driver_prbs_monitor_get(dev, value);
}
