// Copyright (c) 2004-2021 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_PHY_API_PHY_H_
#define _MICROCHIP_ETHERNET_PHY_API_PHY_H_

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// Forigen pointer. MEPA only passes this pointer around, application instanting
// MEPA must define this type. If no bus-addressing data is needed, a null
// pointer can be used.
struct mepa_callout_ctx;

typedef mepa_rc (*mepa_mmd_read_t)(struct mepa_callout_ctx           *ctx,
                                   const uint8_t                      mmd,
                                   const uint16_t                     addr,
                                   uint16_t                          *const value);

typedef mepa_rc (*mepa_mmd_read_inc_t)(struct mepa_callout_ctx       *ctx,
                                       const uint8_t                  mmd,
                                       const uint16_t                 addr,
                                       uint16_t                       *const buf,
                                       uint8_t                        count);

typedef mepa_rc (*mepa_mmd_write_t)(struct mepa_callout_ctx          *ctx,
                                    const uint8_t                     mmd,
                                    const uint16_t                    addr,
                                    const uint16_t                    value);

typedef mepa_rc (*mepa_miim_read_t)(struct mepa_callout_ctx          *ctx,
                                    const uint8_t                     addr,
                                    uint16_t                         *const value);

typedef mepa_rc (*mepa_miim_write_t)(struct mepa_callout_ctx         *ctx,
                                     const uint8_t                    addr,
                                     const uint16_t                   value);

typedef void (*mepa_trace_func_t)(const mepa_trace_data_t *data, va_list args);
typedef void *(*mepa_mem_alloc_t)(struct mepa_callout_ctx *ctx, size_t size);
typedef void (*mepa_mem_free_t)(struct mepa_callout_ctx *ctx, void *ptr);

// The MEPA trace function is a single global variable. Traces will only work
// when a function is assigned to 'MEPA_TRACE_FUNCTION'.
// It is not per-instance, as it can be essential to provide tracing capability
// while creating instances.
extern mepa_trace_func_t MEPA_TRACE_FUNCTION;

// phy synchronisation callbacks passed by application
typedef void (*mepa_lock_func_t)(const mepa_lock_t *const lock);

// Address mode that is specific for mchp phy.
typedef struct mepa_callout {
    mepa_mmd_read_t        mmd_read;
    mepa_mmd_read_inc_t    mmd_read_inc;
    mepa_mmd_write_t       mmd_write;
    mepa_miim_read_t       miim_read;
    mepa_miim_write_t      miim_write;

    mepa_lock_func_t       lock_enter;
    mepa_lock_func_t       lock_exit;

    mepa_mem_alloc_t       mem_alloc;
    mepa_mem_free_t        mem_free;
} mepa_callout_t;


typedef struct mepa_board_conf {
    uint32_t                 numeric_handle;
} mepa_board_conf_t;

// Create a new MEPA instance.
//
// NOTE: 'callout' and 'callout_ctx' pointers must be considered as SHARED,
// meaning that they must remain valid until all MEPA instances are deleted.
// MEPA will use these poiner values in sub-sequence MEPA calls.
//
// The same instance of the callout should be used for all MEPA instances.
// Each PHY should have a unique callout_ctx which contains mdio address,
// controllers etc.
struct mepa_device *mepa_create(const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                struct mepa_board_conf  *conf);

mepa_rc mepa_delete(struct mepa_device *dev);

mepa_rc mepa_reset(struct mepa_device *dev,
                   const mepa_reset_param_t *rst_conf);

mepa_rc mepa_poll(struct mepa_device *dev,
                  mepa_status_t *status);

mepa_rc mepa_conf_set(struct mepa_device *dev,
                      const mepa_conf_t *conf);

mepa_rc mepa_conf_get(struct mepa_device *dev,
                      mepa_conf_t *const conf);

mepa_rc mepa_if_set(struct mepa_device *dev,
                    mepa_port_interface_t intf);

mepa_rc mepa_if_get(struct mepa_device *dev,
                    mepa_port_speed_t speed,
                    mepa_port_interface_t *intf);

mepa_rc mepa_power_set(struct mepa_device *dev,
                       mepa_power_mode_t power);

mepa_rc mepa_cable_diag_start(struct mepa_device *dev,
                              int mode);

mepa_rc mepa_cable_diag_get(struct mepa_device *dev,
                            mepa_cable_diag_result_t *result);

mepa_rc mepa_media_set(struct mepa_device *dev,
                       mepa_media_interface_t phy_media_if);

mepa_rc mepa_aneg_status_get(struct mepa_device *dev,
                             mepa_aneg_status_t *status);

mepa_rc mepa_clause22_read(struct mepa_device *dev,
                           uint32_t address,
                           uint16_t *const value);

mepa_rc mepa_clause22_write(struct mepa_device *dev,
                            uint32_t address,
                            uint16_t value);

mepa_rc mepa_clause45_read(struct mepa_device *dev,
                           uint32_t address,
                           uint16_t *const value);

mepa_rc mepa_clause45_write(struct mepa_device *dev,
                            uint32_t address,
                            uint16_t value);

mepa_rc mepa_event_enable_set(struct mepa_device *dev,
                              mepa_event_t event,
                              mesa_bool_t enable);

mepa_rc mepa_event_enable_get(struct mepa_device *dev,
                              mepa_event_t *const event);

mepa_rc mepa_event_poll(struct mepa_device *dev,
                        mepa_event_t *const ev_mask);

mepa_rc mepa_loopback_set(struct mepa_device *dev,
                          const mepa_loopback_t *loopback);

mepa_rc mepa_loopback_get(struct mepa_device *dev,
                          mepa_loopback_t *const loopback);

mepa_rc mepa_gpio_mode_set(struct mepa_device *dev,
                           const mepa_gpio_conf_t *data);

mepa_rc mepa_gpio_out_set(struct mepa_device *dev,
                          uint8_t gpio_no,
                          mepa_bool_t value);

mepa_rc mepa_gpio_in_get(struct mepa_device *dev,
                         uint8_t gpio_no,
                         mepa_bool_t *const value);

mepa_rc mepa_synce_clock_conf_set(struct mepa_device *dev,
                                  const mepa_synce_clock_conf_t *conf);

mepa_rc mepa_link_base_port(struct mepa_device *dev,
                            struct mepa_device *base_dev,
                            uint8_t packet_idx);

mepa_rc mepa_phy_info_get(struct mepa_device *dev,
                          mepa_phy_info_t *const phy_info);

#include <microchip/ethernet/hdr_end.h>
#endif
