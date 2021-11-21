// Copyright (c) 2004-2021 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_PHY_API_PHY_H_
#define _MICROCHIP_ETHERNET_PHY_API_PHY_H_

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// Forigen pointer. MEPA only passes this pointer around, application instanting
// MEPA must define this type. If no bus-addressing data is needed, a null
// pointer can be used.
struct mepa_callout_cxt;


typedef mepa_rc (*mmd_read_t)(struct mepa_callout_cxt           *cxt,
                              const uint8_t                      mmd,
                              const uint16_t                     addr,
                              uint16_t                          *const value);

typedef mepa_rc (*mmd_read_inc_t)(struct mepa_callout_cxt       *cxt,
                                  const uint8_t                  mmd,
                                  const uint16_t                 addr,
                                  uint16_t                       *const buf,
                                  uint8_t                        count);

typedef mepa_rc (*mmd_write_t)(struct mepa_callout_cxt          *cxt,
                               const uint8_t                     mmd,
                               const uint16_t                    addr,
                               const uint16_t                    value);

typedef mepa_rc (*miim_read_t)(struct mepa_callout_cxt          *cxt,
                               const uint8_t                     addr,
                               uint16_t                         *const value);

typedef mepa_rc (*miim_write_t)(struct mepa_callout_cxt         *cxt,
                                const uint8_t                    addr,
                                const uint16_t                   value);

// todo, add mepa_callout_cxt
typedef void (*debug_func_t)(mepa_trace_level_t                level,
                             const char                       *location,
                             uint32_t                          line_no,
                             const char                       *fmt,
                                                               ...);
// todo, add mepa_callout_cxt
typedef void (*mepa_trace_func_t)(mepa_trace_group_t                group,
                                  mepa_trace_level_t                level,
                                  const char                        *location,
                                  uint32_t                          line_no,
                                  const char                        *fmt,
                                                                    ...);
// todo, add mepa_callout_cxt
typedef void (*mepa_vtrace_func_t)(mepa_trace_group_t               group,
                                   mepa_trace_level_t               level,
                                   const char                       *location,
                                   uint32_t                         line_no,
                                   const char                       *fmt,
                                   va_list                          args);

// phy synchronisation callbacks passed by application
typedef void (*mepa_lock_func_t)(const mepa_lock_t *const lock);

// Address mode that is specific for mchp phy.
typedef struct {
    mmd_read_t              mmd_read;
    mmd_read_inc_t          mmd_read_inc;
    mmd_write_t             mmd_write;
    miim_read_t             miim_read;
    miim_write_t            miim_write;

    debug_func_t            debug_func;
    mepa_trace_func_t       trace_func;
    mepa_vtrace_func_t      vtrace_func;  // TODO, use trace_func instead
    mepa_lock_func_t        lock_enter;
    mepa_lock_func_t        lock_exit;
    // TODO, malloc
} mscc_phy_driver_address_t;

// Union that contains all the values for address mode. Enumeration
// mepa_driver_address_mode_t decides which address type to be used.
typedef union {
    mscc_phy_driver_address_t mscc_address;
} mepa_driver_address_val_t;

// Enumeration of all possible address modes.
typedef enum {
    mscc_phy_driver_address_mode,
} mepa_driver_address_mode_t;

// Main structure that contains the address mode and the address value, these
// values has to be filled up by the switch application.
typedef struct mepa_driver_address {
    mepa_driver_address_mode_t mode;
    mepa_driver_address_val_t val;
} mepa_driver_address_t;

struct mepa_device *mepa_create(const mepa_driver_address_t *addr,
                                uint32_t                     id,  // TODO, delete
                                mepa_port_interface_t        mac_if,  // TODO, not sure about this...
                                uint32_t                     numeric_handle,
                                struct mepa_callout_cxt     *callout_cxt);

mepa_rc mepa_delete(struct mepa_device *dev);

mepa_rc mepa_reset(struct mepa_device *dev,
                   const mepa_reset_param_t *rst_conf);

mepa_rc mepa_poll(struct mepa_device *dev,
                  mepa_driver_status_t *status);

mepa_rc mepa_conf_set(struct mepa_device *dev,
                      const mepa_driver_conf_t *conf);

mepa_rc mepa_conf_get(struct mepa_device *dev,
                      mepa_driver_conf_t *const conf);

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
