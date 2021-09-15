/*
 Copyright (c) 2004-2021 Microsemi Corporation "Microsemi".

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

#include "os.h"
#include "gpy211.h"
#include "gpy211_common.h"
#include "registers/phy/std.h"
#include "registers/phy/phy.h"
#include "registers/phy/pmapmd.h"
#include "registers/phy/pcs.h"
#include "registers/phy/aneg.h"
#include "registers/phy/vspec2.h"

#define T_D(format, ...) if (data->debug_func) data->debug_func(MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(format, ...) if (data->debug_func) data->debug_func(MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(format, ...) if (data->debug_func) data->debug_func(MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(format, ...) if (data->debug_func) data->debug_func(MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);

#define TRUE 1
#define FALSE 0

#define VTSS_FREE(_p_)                          free(_p_)

#define INTL_PHY_CHIPID 0x67c9dc00

typedef struct Intl_Port {
    mscc_phy_driver_address_t mscc;
} Intl_Port_t;

typedef struct{
    struct gpy211_device initconf;
    struct Intl_Port port_param;
    debug_func_t           debug_func;
    struct meba_inst       *meba_inst;  // WHY IS THIS NEEDED?
    //mesa_port_list_t phy_diag_done;
    //mesa_port_list_t phy_shutdown;
} INTL_priv_data_t;

#define GPY211_DEVICE(dev) (&(((INTL_priv_data_t *)dev->data)->initconf))
#define INTL_PORT(dev) (&(((INTL_priv_data_t *)dev->data)->port_param))
#define PRIV_DATA(dev) ((INTL_priv_data_t *)dev->data)

static int (mdiobus_read)(void *mdiobus_data, u16 addr, u32 regnum)
{
    mscc_phy_driver_address_t *mscc = &((Intl_Port_t *)mdiobus_data)->mscc;
    u16 value;
    bool mmd_access = false;
    uint8_t devtype, regaddr;

    if (regnum | MII_ADDR_C45) {
        mmd_access=true;
        devtype = regnum >>16 & 0x1f;
        regaddr = regnum & 0xffff;
    }

    if (mmd_access) {
        if (mscc->mmd_read(mscc->inst, mscc->port_no, devtype, regaddr, &value) == MEPA_RC_OK) {
            return value;
        }
    } else {
        if (mscc->port_miim_read(mscc->inst, mscc->port_no, regnum, &value) == MEPA_RC_OK) {
            return value;
        }
    }

    return -1;
}

static int (mdiobus_write)(void *mdiobus_data, u16 addr, u32 regnum, u16 val)
{
    mscc_phy_driver_address_t *mscc = &((Intl_Port_t *)mdiobus_data)->mscc;
    bool mmd_access = false;
    uint8_t devtype, regaddr;

    if (regnum | MII_ADDR_C45) {
        mmd_access=true;
        devtype = regnum >>16 & 0x1f;
        regaddr = regnum & 0xffff;
    }

    if (mmd_access) {
        if (mscc->mmd_write(mscc->inst, mscc->port_no, devtype, regaddr, val) == MEPA_RC_OK) {
            return 0;
        }
    } else {
        if (mscc->port_miim_write(mscc->inst, mscc->port_no, regnum, val) == MEPA_RC_OK) {
            return 0;
        }
    }

    return -1;
}

static mesa_rc intl_if_get(mepa_device_t *dev, mesa_port_speed_t speed,
                          mesa_port_interface_t *mac_if)
{
    *mac_if = MESA_PORT_INTERFACE_SGMII_2G5;

    return MEPA_RC_OK;
}

void intl_phy_sgmii_conf(mepa_driver_status_t *status, mscc_phy_driver_address_t *mscc)
{
    uint16_t reg_val = 0;

    reg_val |= (status->fdx ? 1 : 0) << 8;
    switch(status->speed){
        case(MESA_SPEED_2500M): reg_val |= (1 << 13 | 1 << 6); break;
        case(MESA_SPEED_1G): reg_val |= (0 << 13 | 1 << 6); break;
        case(MESA_SPEED_100M): reg_val |= (1 << 13 | 0 << 6); break;
        case(MESA_SPEED_10M): reg_val |= (0 << 13 | 0 << 6); break;
        default:
            return;
    }
    reg_val |= 1 << 1;
    mscc->mmd_write(NULL, mscc->port_no, 0x1e, 0x8, reg_val);
}

static mesa_rc intl_poll(mepa_device_t *dev, mepa_driver_status_t *status)
{
    struct gpy211_device *intel_status = GPY211_DEVICE(dev);
    struct Intl_Port *port_param = INTL_PORT(dev);
    INTL_priv_data_t *data = PRIV_DATA(dev);
    bool link_change = false;

    if (gpy2xx_update_link(intel_status) < 0)
        return MESA_RC_ERROR;
    if (gpy2xx_read_status(intel_status) < 0)
        return MESA_RC_ERROR;
    if (status->link != intel_status->link.link)
        link_change = true;
    status->link = intel_status->link.link;
    if (status->link) {
        switch(intel_status->link.speed) {
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
        intl_phy_sgmii_conf(status, &port_param->mscc);
    }

    return MEPA_RC_OK;
}

static mepa_device_t *intl_probe(mepa_driver_t *drv,
                                  const mepa_driver_address_t *mode)
{
    mepa_device_t *device = (mepa_device_t *)calloc(1, sizeof(mepa_device_t));
    if (device == NULL)
        return NULL;

    INTL_priv_data_t *priv = (INTL_priv_data_t *)calloc(1, sizeof(INTL_priv_data_t));
    if (priv == NULL) {
        free(device);
        return NULL;
    }
    struct gpy211_device *initconf = &(priv->initconf);

    if (mode->mode != mscc_phy_driver_address_mode) {
        free(device);
        free(priv);
        return NULL;
    }

    device->drv = drv;
    priv->port_param.mscc = mode->val.mscc_address;
    priv->debug_func = mode->val.mscc_address.debug_func;
    priv->meba_inst = mode->val.mscc_address.meba_inst;
    priv->initconf.mdiobus_read = mdiobus_read;
    priv->initconf.mdiobus_write = mdiobus_write;
    priv->initconf.mdiobus_data = (void *)&priv->port_param;
    priv->initconf.lock = NULL;
    device->data = priv;

    INTL_priv_data_t *data = PRIV_DATA(device);
    T_D("intl_probe, enter\n");

    if (gpy2xx_init(initconf) < 0)
        T_E("intl phy init error\n");

    return device;
}

static mesa_rc intl_delete(mepa_device_t *dev)
{
    INTL_priv_data_t *data = (INTL_priv_data_t *)dev->data;

    VTSS_FREE(data);
    VTSS_FREE(dev);
    return MEPA_RC_OK;
}

static mesa_rc intl_reset(mepa_device_t *dev,
                          const mepa_reset_param_t *rst_conf)
{
    return MEPA_RC_OK;
}

static mesa_rc intl_conf_set(mepa_device_t *dev,
                                const mepa_driver_conf_t *config)
{
    return MEPA_RC_OK;
}

static mesa_rc intl_status_1g_get(mepa_device_t    *dev,
                                  mesa_phy_status_1g_t *status)
{
    return MEPA_RC_OK;
}

mepa_drivers_t mepa_intel_driver_init()
{
#define NR_INTL_PHY 1
    mepa_drivers_t res;
    static mepa_driver_t intl_drivers[NR_INTL_PHY] = {};

    intl_drivers[0].id = INTL_PHY_CHIPID;
    intl_drivers[0].mask = 0xffffffff;
    intl_drivers[0].mepa_driver_delete = intl_delete;
    intl_drivers[0].mepa_driver_reset = intl_reset;
    intl_drivers[0].mepa_driver_poll = intl_poll;
    intl_drivers[0].mepa_driver_conf_set = intl_conf_set;
    intl_drivers[0].mepa_driver_if_get = intl_if_get;
    intl_drivers[0].mepa_driver_power_set = NULL;
    intl_drivers[0].mepa_driver_cable_diag_start = NULL;
    intl_drivers[0].mepa_driver_cable_diag_get = NULL;
    intl_drivers[0].mepa_driver_media_set = NULL;
    intl_drivers[0].mepa_driver_probe = intl_probe;
    intl_drivers[0].mepa_driver_aneg_status_get = intl_status_1g_get;

    res.phy_drv = intl_drivers;
    res.count = NR_INTL_PHY;

    return res;
#undef NR_INTL_PHY
}
