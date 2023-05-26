// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN8770_PRIVATE_H
#define LAN8770_PRIVATE_H

#define MEPA_RC(rc, expr) { rc = (expr); if (rc) goto error; }

#define TRUE  1
#define FALSE 0
#define EXT_PAGE 1 // extended page access
#define MMD_DEV  2 // MMD device access

#define INTR_BIT_LEN    (8)

#define T_D(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);

// Locking Macros
// The variable 'dev' is passed as macro argument to obtain callback pointers and call actual lock functions. It does not indicate locks per port.
#define MEPA_ENTER(dev) {                               \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if (dev->callout->lock_enter) {              \
        dev->callout->lock_enter(&lock);         \
    }                                                \
}

#define MEPA_EXIT(dev) {          \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if (dev->callout->lock_exit) {               \
        dev->callout->lock_exit(&lock);          \
    }                                                \
}

#define MAX_LAN8770_PHY                 9U
#define LAN8770_PHY_ID_MAX              4U
#define LAN8770_PHY_ID_MASK             (0xFFFFF0U)
#define LAN8770_PHY_ID                  (0x7C150U)
#define LAN8770_PHY_ID_LAN938X          (0x7C1A0U)
#define LAN8770_PHY_ID_LAN937X          (0x7C180U)
#define LAN8770_PHY_ID_LAN937X_TC10     (0x74180U)
#define LAN8770_PHY_EXT_BANK(addr)      ((addr >> 16) & 0x000F)
#define LAN8770_PHY_REG_ADDR(addr)      (addr & 0x00FF)

typedef struct {
    uint32_t id;
    uint8_t  model;
    uint8_t  rev;
    mepa_bool_t is_master;
    mepa_bool_t is_master_fault;
} phy_dev_info_t;

typedef struct {
    mepa_bool_t             init_done;
    mepa_bool_t             phy_aneg_dis;
    mepa_bool_t             link_status;
    mepa_port_no_t          port_no;
    mepa_port_interface_t   mac_if;
    mepa_media_interface_t  media_intf;
    mepa_conf_t             conf;
    mepa_event_t            events;
    mepa_loopback_t         loopback;
    phy_dev_info_t          dev;
    mepa_bool_t             ctx_status;
    mepa_bool_t             cdiags_start;
} phy_data_t;

#endif //LAN8770_PRIVATE_H
