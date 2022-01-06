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
    int i;
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

        // Shall be last
#if defined(MEPA_HAS_VTSS)
        MEPA_phy_lib[7] = mepa_default_phy_driver_init();
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

        for (int j = 0; j < MEPA_phy_lib[i].count; j++) {
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

    //PHY Module
    mepa_rc  rc = dev->drv->mepa_debug_info_dump(dev, pr, info);

    //PHY TS Module
    if (rc && dev->drv->mepa_ts->mepa_debug_info_dump) {
        rc = dev->drv->mepa_ts->mepa_debug_info_dump(dev, pr, info);
    }

    //Anyother module??
    return rc;
}
