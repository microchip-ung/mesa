/*
 Copyright (c) 2004-2022 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>

#include "os.h"
#include "gpy211.h"
#include "gpy211_common.h"
#include "registers/phy/std.h"
#include "registers/phy/phy.h"
#include "registers/phy/pmapmd.h"
#include "registers/phy/pcs.h"
#include "registers/phy/aneg.h"
#include "registers/phy/vspec2.h"

#define T_D(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);


#define TRUE 1
#define FALSE 0

#define INTL_PHY_CHIPID 0x67c9dc00

typedef struct Intl_Port {
    mepa_device_t *dev;
} Intl_Port_t;

typedef struct {
    struct gpy211_device initconf;
    struct Intl_Port port_param;
    mepa_conf_t conf;
} INTL_priv_data_t;

#define GPY211_DEVICE(dev) (&(((INTL_priv_data_t *)dev->data)->initconf))
#define INTL_PORT(dev) (&(((INTL_priv_data_t *)dev->data)->port_param))
#define PRIV_DATA(dev) ((INTL_priv_data_t *)dev->data)

static int (mdiobus_read)(void *mdiobus_data, uint16_t addr, uint32_t regnum)
{
    mepa_device_t *dev = ((Intl_Port_t *)mdiobus_data)->dev;
    uint16_t value;
    bool mmd_access = false;
    uint8_t devtype, regaddr;

    if (regnum | MII_ADDR_C45) {
        mmd_access = true;
        devtype = regnum >> 16 & 0x1f;
        regaddr = regnum & 0xffff;
    }

    if (mmd_access) {
        if (dev->callout->mmd_read(dev->callout_ctx, devtype, regaddr, &value) == MEPA_RC_OK) {
            return value;
        }
    } else {
        if (dev->callout->miim_read(dev->callout_ctx, regnum, &value) == MEPA_RC_OK) {
            return value;
        }
    }

    return -1;
}

static int (mdiobus_write)(void *mdiobus_data, uint16_t addr, uint32_t regnum, uint16_t val)
{
    mepa_device_t *dev = ((Intl_Port_t *)mdiobus_data)->dev;
    bool mmd_access = false;
    uint8_t devtype, regaddr;

    if (regnum | MII_ADDR_C45) {
        mmd_access = true;
        devtype = regnum >> 16 & 0x1f;
        regaddr = regnum & 0xffff;
    }

    if (mmd_access) {
        if (dev->callout->mmd_write(dev->callout_ctx, devtype, regaddr, val) == MEPA_RC_OK) {
            return 0;
        }
    } else {
        if (dev->callout->miim_write(dev->callout_ctx, regnum, val) == MEPA_RC_OK) {
            return 0;
        }
    }

    return -1;
}

static bool intl_mode_is_usxgmii(mepa_device_t *dev)
{
    uint16_t reg_val = 0;

    dev->callout->mmd_write(dev->callout_ctx, 0x1e, 0x0006, 0x8800);
    dev->callout->mmd_write(dev->callout_ctx, 0x1e, 0x0007, 0x00d2);
    dev->callout->mmd_read(dev->callout_ctx, 0x1e, 0x0005, &reg_val);

    return reg_val == 2 ? true : false;
}

static mesa_rc intl_if_get(mepa_device_t *dev, mesa_port_speed_t speed,
                           mesa_port_interface_t *mac_if)
{
    if (intl_mode_is_usxgmii(dev)) {
        *mac_if = MESA_PORT_INTERFACE_QXGMII;
    } else {
        *mac_if = MESA_PORT_INTERFACE_SGMII_2G5;
    }

    return MEPA_RC_OK;
}

static mesa_rc intl_phy_sgmii_conf(mepa_device_t *dev, mepa_status_t *status)
{
    int rc;
    struct gpy211_device *phy = GPY211_DEVICE(dev);
    struct gpy211_sgmii sgmii;

    sgmii.linkcfg_dir = SGMII_LINKCFG_TPI;
    sgmii.aneg_mode = SGMII_ANEG_1000BX;
    sgmii.link.autoneg = 0;
    switch (status->speed) {
    case (MESA_SPEED_2500M):
        sgmii.link.speed = 2500;
        break;
    case (MESA_SPEED_1G):
        sgmii.link.speed = 1000;
        break;
    case (MESA_SPEED_100M):
        sgmii.link.speed = 100;
        break;
    case (MESA_SPEED_10M):
        sgmii.link.speed = 10;
        break;
    default:
        return MESA_RC_ERROR;
    }

    rc = gpy2xx_sgmii_config_aneg(phy, &sgmii);

    return rc < 0 ? MESA_RC_ERROR : MESA_RC_OK;
}

static mesa_rc intl_poll(mepa_device_t *dev, mepa_status_t *status)
{
    struct gpy211_device *intel_status = GPY211_DEVICE(dev);
    bool link_change = false;

    if (gpy2xx_update_link(intel_status) < 0) {
        return MESA_RC_ERROR;
    }
    if (gpy2xx_read_status(intel_status) < 0) {
        return MESA_RC_ERROR;
    }
    if (status->link != intel_status->link.link) {
        link_change = true;
    }
    status->link = intel_status->link.link;
    if (status->link) {
        switch (intel_status->link.speed) {
        case (SPEED_1000):
            status->speed = MESA_SPEED_1G;
            break;
        case (SPEED_100):
            status->speed = MESA_SPEED_100M;
            break;
        case (SPEED_10):
            status->speed = MESA_SPEED_10M;
            break;
        case (SPEED_2500):
            status->speed = MESA_SPEED_2500M;
            break;
        default:
            T_E("not expected speed");
            break;
        }
    }
    status->fdx = intel_status->link.duplex;
    status->aneg.obey_pause = intel_status->link.pause;
    status->aneg.generate_pause = intel_status->link.pause;
    status->copper = TRUE;
    status->fiber = FALSE;
    T_D("intl_phy_status_get: link %d, speed %d  duplex %d\n", intel_status->link.link, intel_status->link.speed, intel_status->link.duplex);

    if (link_change && status->link) {
        T_D("link change");
        return(intl_phy_sgmii_conf(dev, status));
    }

    return MEPA_RC_OK;
}

static mepa_device_t *intl_probe(mepa_driver_t *drv,
                                 const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                 struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                 struct mepa_board_conf              *board_conf)
{
    mepa_device_t *dev;
    INTL_priv_data_t *priv;

    dev = mepa_create_int(drv, callout, callout_ctx, board_conf, sizeof(INTL_priv_data_t));
    if (!dev) {
        return 0;
    }

    priv = dev->data;
    struct gpy211_device *initconf = &(priv->initconf);

    priv->port_param.dev = dev;
    priv->initconf.mdiobus_read = mdiobus_read;
    priv->initconf.mdiobus_write = mdiobus_write;
    priv->initconf.mdiobus_data = (void *)&priv->port_param;
    priv->initconf.lock = NULL;

    T_D("intl_probe, enter\n");
    if (gpy2xx_init(initconf) < 0) {
        T_E("intl phy init error\n");
    }

    return dev;
}

static mesa_rc intl_delete(mepa_device_t *dev)
{
    return mepa_delete_int(dev);
}

static mesa_rc intl_reset(mepa_device_t *dev,
                          const mepa_reset_param_t *rst_conf)
{
    return MEPA_RC_OK;
}

static mesa_rc intl_conf_get(mepa_device_t *dev,
                             mepa_conf_t *const config)
{
    INTL_priv_data_t *priv = dev->data;

    *config = priv->conf;
    return MEPA_RC_OK;
}

static mesa_rc intl_conf_set(mepa_device_t *dev,
                             const mepa_conf_t *config)
{
    int rc;
    struct gpy211_device *phy = GPY211_DEVICE(dev);
    INTL_priv_data_t *priv = dev->data;

    if (!config->admin.enable) {
        // Force link down by removing all capablities
        phy->link.autoneg = 1;
        phy->link.advertising = 0;
        rc = gpy2xx_config_aneg(phy);
        return rc ? MEPA_RC_ERROR : MEPA_RC_OK;
    }

    phy->link.advertising = 0;
    if (config->aneg.speed_10m_hdx) {
        phy->link.advertising |= GPY2XX_ADVERTISED_10baseT_Half;
    }
    if (config->aneg.speed_10m_fdx) {
        phy->link.advertising |= (uint64_t)GPY2XX_ADVERTISED_10baseT_Full;
    }
    if (config->aneg.speed_100m_hdx) {
        phy->link.advertising |= GPY2XX_ADVERTISED_100baseT_Half;
    }
    if (config->aneg.speed_100m_fdx) {
        phy->link.advertising |= GPY2XX_ADVERTISED_100baseT_Full;
    }
    if (config->flow_control) {
        phy->link.advertising |=  GPY2XX_ADVERTISED_Pause;
        phy->link.advertising |=  GPY2XX_ADVERTISED_Asym_Pause;
    }
    if (config->aneg.speed_1g_hdx) {
        phy->link.advertising |= GPY2XX_ADVERTISED_1000baseT_Half;
    }
    if (config->aneg.speed_1g_fdx) {
        phy->link.advertising |= (uint64_t)GPY2XX_ADVERTISED_1000baseT_Full;
    }
    if (config->aneg.speed_2g5_fdx) {
        phy->link.advertising |= GPY2XX_ADVERTISED_2500baseT_Full;
        phy->link.advertising |= 1 << 15;
    }

    switch (config->speed) {
    case MESA_SPEED_10M:
        phy->link.speed = SPEED_10;
        break;
    case MESA_SPEED_100M:
        phy->link.speed = SPEED_100;
        break;
    case MESA_SPEED_1G:
        phy->link.speed = SPEED_1000;
        break;
    case MESA_SPEED_2500M:
        phy->link.speed = SPEED_2500;
        break;
    case MESA_SPEED_AUTO:
        /* in auto mode, link.speed is the resolved speed */
        break;
    case MESA_SPEED_UNDEFINED:
    default:
        T_E("Illegal speed");
        return MESA_RC_ERROR;
    }

    if (config->fdx) {
        phy->link.duplex = DUPLEX_FULL;
    } else {
        phy->link.duplex = DUPLEX_HALF;
    }

    if (config->speed == MESA_SPEED_AUTO) {
        phy->link.autoneg = 1;
    } else {
        phy->link.autoneg = 0;
    }

    rc = gpy2xx_config_aneg(phy);

    priv->conf = *config;

    return rc ? MEPA_RC_ERROR : MEPA_RC_OK;
}

static mesa_rc intl_status_1g_get(mepa_device_t    *dev,
                                  mesa_phy_status_1g_t *status)
{
    return MEPA_RC_OK;
}

static mepa_rc intl_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy_info->cap = 0;
    phy_info->part_number = dev->drv->id;
    phy_info->revision = dev->drv->id & 0xF;
    phy_info->cap |= MEPA_CAP_SPEED_MASK_2G5;
    return MEPA_RC_OK;
}

static mepa_rc intl_miim_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    return dev->callout->miim_read(dev->callout_ctx, address, value);
}

static mepa_rc intl_miim_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    return dev->callout->miim_write(dev->callout_ctx, address, value);
}

static mepa_rc intl_mmd_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    uint16_t page_mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;

    return dev->callout->mmd_read(dev->callout_ctx, page_mmd, addr, value);
}

static mepa_rc intl_mmd_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    uint16_t page_mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;

    return dev->callout->mmd_write(dev->callout_ctx, page_mmd, addr, value);
}

static mepa_rc intl_event_enable_set(mepa_device_t *dev, mepa_event_t event,
                                     mesa_bool_t enable)
{
    uint16_t mask = 0;

    if (event == MESA_PHY_LINK_FFAIL_EV) {
        mask |= 1; // Link down IRQ
    }
    return dev->callout->mmd_write(dev->callout_ctx, 0, 25, mask);
}

static mepa_rc intl_event_poll(mepa_device_t *dev, mepa_event_t *status)
{
    uint16_t value;

    dev->callout->mmd_read(dev->callout_ctx, 0, 26, &value);
    *status = (value & 0x1) ? MESA_PHY_LINK_FFAIL_EV : 0;
    return MEPA_RC_OK;
}

static mesa_rc intl_if_set(mepa_device_t *dev,
                           mesa_port_interface_t mac_if)
{
    mesa_port_interface_t int_if;

    intl_if_get(dev, 1, &int_if);

    if (mac_if == MESA_PORT_INTERFACE_SGMII) {
        mac_if = MESA_PORT_INTERFACE_SGMII_2G5;
    }
    if (mac_if != int_if) {
        T_E("Configured phy interface mode (%d) does not match phy pin strapping (%d)", mac_if, int_if);
        return MEPA_RC_ERROR;
    }

    return MEPA_RC_OK;
}



mepa_drivers_t mepa_intel_driver_init()
{
#define NR_INTL_PHY 1
    mepa_drivers_t res;
    static mepa_driver_t intl_drivers[NR_INTL_PHY] = {};

    intl_drivers[0].id = INTL_PHY_CHIPID;
    intl_drivers[0].mask = 0xffff0000;
    intl_drivers[0].mepa_driver_delete = intl_delete;
    intl_drivers[0].mepa_driver_reset = intl_reset;
    intl_drivers[0].mepa_driver_poll = intl_poll;
    intl_drivers[0].mepa_driver_conf_get = intl_conf_get;
    intl_drivers[0].mepa_driver_conf_set = intl_conf_set;
    intl_drivers[0].mepa_driver_if_get = intl_if_get;
    intl_drivers[0].mepa_driver_power_set = NULL;
    intl_drivers[0].mepa_driver_cable_diag_start = NULL;
    intl_drivers[0].mepa_driver_cable_diag_get = NULL;
    intl_drivers[0].mepa_driver_media_set = NULL;
    intl_drivers[0].mepa_driver_probe = intl_probe;
    intl_drivers[0].mepa_driver_aneg_status_get = intl_status_1g_get;
    intl_drivers[0].mepa_driver_phy_info_get = intl_info_get,
    intl_drivers[0].mepa_driver_clause22_read = intl_miim_read,
    intl_drivers[0].mepa_driver_clause22_write = intl_miim_write,
    intl_drivers[0].mepa_driver_clause45_read  = intl_mmd_read,
    intl_drivers[0].mepa_driver_clause45_write = intl_mmd_write,
    intl_drivers[0].mepa_driver_event_enable_set = intl_event_enable_set,
    intl_drivers[0].mepa_driver_event_poll = intl_event_poll,
    intl_drivers[0].mepa_driver_if_set = intl_if_set,

    res.phy_drv = intl_drivers;
    res.count = NR_INTL_PHY;

    return res;
#undef NR_INTL_PHY
}
