// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_PFE_PRIVATE_H_
#define _MEPA_PFE_PRIVATE_H_

#include <unistd.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api/phy_ts.h>

#define MEPA_RC(expr) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) return __rc__; }
#define MEPA_ASSERT(x) if((x)) { return MESA_RC_ERROR;}

#define TRUE  1
#define FALSE 0
#define EXT_PAGE 1 // extended page access
#define MMD_DEV  2 // MMD device access

#define PFE_MMD_COMMON_CTRL_REG	2
#define PFE_RXC_DLL_CTRL		76
#define PFE_TXC_DLL_CTRL		77
#define PFE_DLL_ENABLE_DELAY	0

typedef enum {
	PHY_INTERFACE_MODE_RGMII,      // Reduced gigabit media-independent interface
	PHY_INTERFACE_MODE_RGMII_ID,   // RGMII with Internal RX+TX delay
	PHY_INTERFACE_MODE_RGMII_RXID, // RGMII with Internal RX delay
	PHY_INTERFACE_MODE_RGMII_TXID, // RGMII with Internal RX delay
} phy_interface_t;

#define DISABLE_DLL_TX_BIT INDY_BIT(14)
#define	DISABLE_DLL_RX_BIT INDY_BIT(14)
#define	DISABLE_DLL_MASK INDY_BIT(14)

#define LAN8840_OPERATION_MODE_STRAP_LOW_REGISTER 3
#define LAN8840_OPERATION_MODE_STRAP_LOW_REGISTER_STRAP_RGMII_EN 1

#define T_D(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);

// Locking Macros
// The variable 'dev' is passed as macro argument to obtain callback pointers and call actual lock functions. It does not indicate locks per port.
#define MEPA_ENTER(dev) {                            \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if (dev->callout->lock_enter) {                  \
        dev->callout->lock_enter(&lock);             \
    }                                                \
}

#define MEPA_EXIT(dev) {                             \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if (dev->callout->lock_exit) {                   \
        dev->callout->lock_exit(&lock);              \
    }                                                \
}

typedef struct {
    uint8_t  model;
    uint8_t  rev;
} phy_dev_info_t;

typedef struct {
    mepa_port_no_t           port_no;
    mepa_conf_t              conf;
    mepa_event_t             events;
    mepa_loopback_t          loopback;
    phy_dev_info_t           dev;
    mepa_bool_t              link_status;
    mepa_port_speed_t        speed_status;
    mepa_bool_t              fdx_status;
} phy_data_t;

#endif
