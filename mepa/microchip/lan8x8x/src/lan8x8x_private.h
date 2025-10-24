// Copyright (c) 2004-2024 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN8X8X_PRIVATE_H
#define LAN8X8X_PRIVATE_H

#include <phy_lib.h>
#include "lan8x8x_registers.h"

#define LAN8X8X_NSLEEP(ns)           MEPA_NSLEEP((ns))
#define LAN8X8X_MTIMER_START(t, ms)  MEPA_MTIMER_START((t), (ms))

#define MEPA_RC(rc, expr) { { (rc) = (expr); }  if ((rc) != 0) { return rc; } }

// Locking Macros
// The variable 'dev' is passed as macro argument to obtain callback pointers and call actual lock functions. It does not indicate locks per port.
#define MEPA_ENTER(dev) {                               \
    mepa_lock_t lock;                                \
    lock.function = __func__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if ((dev)->callout->lock_enter != NULL) {        \
        (dev)->callout->lock_enter(&lock);         \
    }                                                \
}

#define MEPA_EXIT(dev) {          \
    mepa_lock_t lock;                                \
    lock.function = __func__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if ((dev)->callout->lock_exit != NULL) {         \
        (dev)->callout->lock_exit(&lock);          \
    }                                                \
}

#ifdef MEPA_lan8x8x_static_mem
#ifdef MAX_LAN8X8X_PHY
#define LAN8X8X_PHY_MAX                        MAX_LAN8X8X_PHY
#else
#define LAN8X8X_PHY_MAX                        (MEPA_lan8x8x_phy_max)
#endif
#else // MEPA_lan8x8x_static_mem
#ifdef MAX_LAN8X8X_PHY
#define LAN8X8X_PHY_MAX                        MAX_LAN8X8X_PHY
#else
#define LAN8X8X_PHY_MAX                        (1U)
#endif
#endif //MEPA_lan8x8x_static_mem

#define PHY_ID_LAN878X          (0x002216A0U)
#define PHY_ID_LAN888X          (0x002216B0U)
#define PHY_ID_MASK     (0xFFFFFFF0U)
#define IS_LAN888X(id)      (((id) & PHY_ID_MASK) == PHY_ID_LAN888X)
#define IS_LAN878X(id)      (((id) & PHY_ID_MASK) == PHY_ID_LAN878X)

#define PHY_LINKUP                  (PHY_TRUE)
#define PHY_LINKDOWN                (PHY_FALSE)

//Retrieve PHY_ID
#define GET_PHY_ID1(x)              (((x) << 2U) & 0x03FFFCU)
#define GET_PHY_ID2(x)              ((EXTRACT_BITS(x, 10U, 6U) << 18U) & 0xFFFFFFFFU)
#define GET_PHY_REV(x)              EXTRACT_BITS(x, 0U, 4U)
#define GET_PHY_MODEL(x)            EXTRACT_BITS(x, 4U, 6U)

/* Maximum supported SECYs */
//8 vPorts, 16 SAs per direction (2 SAs per vPort)
#define MCHP_MS_MAX_SECYS               8
#define MCHP_MS_MAX_FLOWS               16

/* Blackfyre ENGINEERING NOTE:
 * Blackfyre supports only 2 VLAN TAG bypass for insertion of SecTAG.
 */
#define MCHP_MS_MAX_VLANS               2

/*
 * Data structures
 */
typedef struct {
    mepa_bool_t dis_macsec;
    mepa_bool_t dis_1588;
    mepa_bool_t dis_1000;
    mepa_bool_t dis_100;
} mchp_t1_otp_cap_t;

typedef struct {
    uint32_t id;
    uint16_t  model;
    uint16_t  rev;
    mepa_bool_t is_master;
    mepa_bool_t is_master_fault;
} phy_dev_info_t;

typedef struct {
    mchp_t1_otp_cap_t       t1_cap;
    mepa_bool_t             init_done;
    mepa_bool_t             link_status;
    mepa_port_no_t          port_no;
    mepa_port_interface_t   mac_if;
    mepa_media_interface_t  media_intf;
    mepa_conf_t             conf;
    mepa_event_t            events;
    mepa_loopback_t         loopback;
    phy_dev_info_t          dev;
    mepa_bool_t             ctx_status;
    mepa_cable_diag_result_t cd_res;
    mepa_gpio_conf_t        led_conf[4];
} phy_data_t;

#endif //LAN8X8X_PRIVATE_H
