// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <string.h>
#include <stdbool.h>

#include <mepa_driver.h>
#include <lan867x_private.h>
#include <lan867x_registers.h>

/* LAN867X is a Single-Port 10BASE-T1S Ethernet Phy */

#ifdef MEPA_LAN867X_STATIC_MEM
static mepa_device_t lan867x_device[MAX_LAN867X_PHY];
static phy_data_t lan867x_data[MAX_LAN867X_PHY];
#endif

// MEPA APIs
static mepa_rc lan867x_mmd_reg_read(mepa_device_t *dev, uint32_t addr, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = lan867x_mmd_reg_rd(dev, (uint8_t)LAN867X_PHY_MMD_DEVAD(addr), (uint16_t)LAN867X_PHY_REG_ADDR(addr), value);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan867x_mmd_reg_write(mepa_device_t *dev, uint32_t addr, uint16_t value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = lan867x_mmd_reg_wr(dev, (uint8_t)LAN867X_PHY_MMD_DEVAD(addr), (uint16_t)LAN867X_PHY_REG_ADDR(addr), value);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan867x_reg_read(mepa_device_t *dev, uint32_t addr, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = lan867x_miim_reg_rd(dev, (uint16_t)addr, value);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan867x_reg_write(mepa_device_t *dev, uint32_t addr, uint16_t value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = lan867x_miim_reg_wr(dev, (uint16_t)addr, value);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan867x_delete(mepa_device_t *dev)
{
    mepa_rc rc = MEPA_RC_OK;

    if (dev == NULL || dev->data == NULL)
    {
        return MEPA_RC_ERR_PARM;
    }
#ifdef MEPA_LAN867X_STATIC_MEM
    memset(dev, 0, sizeof(mepa_device_t));
    memset(&dev->data, 0, sizeof(phy_data_t));
#else
    rc = mepa_delete_int(dev);
#endif

    return rc;
}

static mepa_device_t *lan867x_probe(mepa_driver_t *drv,
                                    const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                    struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                    struct mepa_board_conf                  *conf)
{
    mepa_rc rc = MESA_RC_OK;
    phy_data_t *pdata = NULL;
    mepa_device_t *pdev = NULL;
    uint16_t val1 = 0, val2 = 0;

#ifdef MEPA_LAN867X_STATIC_MEM
    uint8_t pidx = 0;

    for(pidx = 0; pidx < MAX_LAN867X_PHY; pidx++)
    {
        if (lan867x_data[pidx].ctx_status)
        {
            continue;
        }
        pdata = &lan867x_data[pidx];
        pdev = &lan867x_device[pidx];
        pdata->t1s_cfg.plca_cfg.node_id = (pidx + 1);
        goto update;
    }
    goto error;
#else
    pdev = mepa_create_int(drv, callout, callout_ctx, conf, (int32_t)(sizeof(phy_data_t)));
    if (pdev == NULL) {
        goto error;
    }
    pdata = pdev->data;
    pdata->t1s_cfg.plca_cfg.node_id = (uint8_t)(conf->numeric_handle & 0xFFU);
#endif

#ifdef MEPA_LAN867X_STATIC_MEM
update:
#endif
    pdev->drv = drv;
    pdev->data = (void *)pdata;
    pdev->callout = callout;
    pdev->callout_ctx = callout_ctx;

    pdata->port_no = conf->numeric_handle;
    pdata->init_done = false;
    pdata->events = 0;
    pdata->mac_if = MESA_PORT_INTERFACE_MII;
    pdata->media_intf = MESA_PHY_MEDIA_IF_T1S_10FX;
    pdata->conf.man_neg = MEPA_MANUAL_NEG_REF;
    pdata->conf.admin.enable = true;
    pdata->conf.speed = MESA_SPEED_10M;
    pdata->conf.fdx = false;
    pdata->t1s_cfg.plca_cfg.node_count = 8;
    pdata->t1s_cfg.plca_cfg.plca_enable = true;
    pdata->t1s_cfg.plca_cfg.tx_oppr_timer = 32;
    pdata->t1s_cfg.plca_cfg.max_burst_cnt = 0;
    pdata->t1s_cfg.plca_cfg.burst_timer = 128;

    MEPA_RC(rc, lan867x_miim_reg_rd(pdev, LAN867X_PHY_ID0_REG, (uint16_t *)&val1));
    MEPA_RC(rc, lan867x_miim_reg_rd(pdev, LAN867X_PHY_ID1_REG, (uint16_t *)&val2));

    pdata->ctx_status = true;
    pdata->dev.id = LAN867X_OUI((uint32_t)val1, (uint32_t)val2);
    pdata->dev.model = (uint8_t)LAN867X_MODEL(val2);
    pdata->dev.rev = (uint8_t)LAN867X_REV(val2);

    T_I(MEPA_TRACE_GRP_GEN, "LAN867X driver probed for port %u  \r\n", pdata->port_no);

    return pdev;

error:
    return NULL;
}

static mepa_rc lan867x_conf_get(mepa_device_t *dev, mepa_conf_t *const config)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);

    (void)memcpy(config, &(data->conf), sizeof(mepa_conf_t));

    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc lan867x_media_get(struct mepa_device *dev, mepa_media_interface_t *media_if)
{
   phy_data_t *data = (phy_data_t *)dev->data;

   MEPA_ENTER(dev);

   *media_if = data->media_intf;

   MEPA_EXIT(dev);

   return MEPA_RC_OK;
}

static mepa_rc lan867x_if_get(struct mepa_device *dev, mepa_port_speed_t speed,
                                    mepa_port_interface_t *mac_if)
{
   phy_data_t *data = (phy_data_t *)dev->data;

   MEPA_ENTER(dev);

   *mac_if = data->mac_if;

   MEPA_EXIT(dev);

   return MEPA_RC_OK;
}
static mepa_rc lan867x_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = lan867x_phy_conf_set(dev, config);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan867x_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_ENTER(dev);

    T_I( MEPA_TRACE_GRP_GEN, "Initializing PHY! \r\n");

    MEPA_RC(rc, lan867x_init_conf(dev, data->t1s_cfg.plca_cfg));

    // Reconfigure the phy after reset
    MEPA_RC(rc, lan867x_phy_conf_set(dev, &data->conf));

error:
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan867x_poll(mepa_device_t *dev, mepa_status_t *status)
{
    MEPA_ENTER(dev);

    mepa_rc rc = lan867x_get_link_status(dev, status);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan867x_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    mepa_rc rc = MEPA_RC_ERROR;

    phy_data_t *data = (phy_data_t *)(dev->data);

    if(data->init_done)
    {
        MEPA_ENTER(dev);
        phy_info->part_number = data->dev.model;
        phy_info->revision = data->dev.rev;
        phy_info->cap = MEPA_CAP_TS_MASK_NONE;
        MEPA_EXIT(dev);
        rc = MEPA_RC_OK;
    }

    return rc;
}

static mepa_rc lan867x_debug_info(struct mepa_device *dev,
                                  const mepa_debug_print_t pr,
                                  const mepa_debug_info_t   *const info)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_t1s_plca_cfg_t *p;

    if (dev != NULL && pr != NULL && info != NULL) {
        // PHY Debugging
        switch (info->group) {
        case MEPA_DEBUG_GROUP_ALL:
        case MEPA_DEBUG_GROUP_PHY: {
            MEPA_ENTER(dev);
            data = (phy_data_t *)dev->data;
            p = &data->t1s_cfg.plca_cfg;
            pr("PLCA mode  : %s\n", p->plca_enable ? "Enabled" : "Disabled");
            pr("Node count : %u\n", p->node_count);
            pr("Node id    : %u\n", p->node_id);
            pr("TO timer   : %u\n", p->tx_oppr_timer);
            pr("Max burst  : %u\n", p->max_burst_cnt);
            pr("Burst timer: %u\n", p->burst_timer);
            rc = MEPA_RC_OK;
            MEPA_EXIT(dev);
        }
        break;
        default:
            rc = MEPA_RC_OK;
            break;
        }
    }
    return rc;
}

mepa_drivers_t mepa_lan867x_driver_init(void)
{
    mepa_drivers_t result;
    static mepa_driver_t lan867x_driver[1] = {};
    mepa_driver_t *drv = &lan867x_driver[0];

    // Device ID and Mask
    drv->id = LAN867X_PHY_ID;
    drv->mask = LAN867X_PHY_ID_MASK;

    // Driver APIs
    drv->mepa_driver_probe              = lan867x_probe;
    drv->mepa_driver_delete             = lan867x_delete;
    drv->mepa_driver_reset              = lan867x_reset;
    drv->mepa_driver_poll               = lan867x_poll;
    drv->mepa_driver_conf_set           = lan867x_conf_set;
    drv->mepa_driver_conf_get           = lan867x_conf_get;
    drv->mepa_driver_if_get             = lan867x_if_get;
    drv->mepa_driver_media_get          = lan867x_media_get;
    drv->mepa_driver_clause22_read      = lan867x_reg_read;
    drv->mepa_driver_clause22_write     = lan867x_reg_write;
    drv->mepa_driver_clause45_read      = lan867x_mmd_reg_read;
    drv->mepa_driver_clause45_write     = lan867x_mmd_reg_write;
    drv->mepa_driver_phy_info_get       = lan867x_info_get;
    drv->mepa_debug_info_dump           = lan867x_debug_info,
    drv->mepa_t1s                       = &lan867x_t1s_driver;

    result.phy_drv = &lan867x_driver[0];
    result.count = 1U;

    return result;
}
