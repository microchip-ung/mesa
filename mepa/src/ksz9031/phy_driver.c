// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <mscc/ethernet/board/api/phy_driver.h>

#include "phy_driver.h"

#define T_N(format, ...) if (phydev->address.debug_func) phydev->address.debug_func(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_D(format, ...) if (phydev->address.debug_func) phydev->address.debug_func(MEBA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(format, ...) if (phydev->address.debug_func) phydev->address.debug_func(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(format, ...) if (phydev->address.debug_func) phydev->address.debug_func(MEBA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(format, ...) if (phydev->address.debug_func) phydev->address.debug_func(MEBA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);

#define TRUE 1
#define FALSE 0

#define VTSS_FREE(_p_)                          free(_p_)
#define MSLEEP(sec)                             usleep(sec*1000)

#define KSZ_2_MESA_RC(aq_rc)                    ((aq_rc == AQ_RET_OK) ? MESA_RC_OK : MESA_RC_ERROR)

#define PHY_POLL        -1
#define PHY_IGNORE_INTERRUPT    -2

#define DUPLEX_HALF        0x00
#define DUPLEX_FULL        0x01
#define DUPLEX_UNKNOWN        0xff

#define SPEED_10        10
#define SPEED_100        100
#define SPEED_1000        1000
#define SPEED_UNKNOWN        -1

#define AUTONEG_DISABLE		0x00
#define AUTONEG_ENABLE		0x01

#define MII_BMCR		0x00	/* Basic mode control register */
#define MII_BMSR		0x01	/* Basic mode status register  */
#define MII_CTRL1000		0x09	/* 1000BASE-T control          */
#define BMCR_ISOLATE		0x0400	/* Isolate data paths from MII */
#define BMCR_ANENABLE		0x1000	/* Enable auto negotiation     */
#define BMCR_ANRESTART		0x0200	/* Auto negotiation restart    */
#define BMSR_LSTATUS		0x0004	/* Link status                 */
#define BMSR_ANEGCOMPLETE	0x0020	/* Auto-negotiation complete   */
#define BMCR_FULLDPLX		0x0100	/* Full duplex                 */
#define BMCR_SPEED1000		0x0040	/* MSB of Speed (1000)         */
#define BMCR_SPEED100		0x2000	/* Select 100Mbps              */
#define CTL1000_AS_MASTER	0x0800
#define CTL1000_ENABLE_MASTER	0x1000

#define MII_KSZ9031RN_FLP_BURST_TX_LO	3
#define MII_KSZ9031RN_FLP_BURST_TX_HI	4


typedef struct {
    unsigned autoneg;
    /* The most recently read link state */
    unsigned link;
    unsigned autoneg_complete;
    int irq;
    int speed;
    int duplex;
    int pause;
    int asym_pause;
    mscc_phy_driver_address_t address;
    mesa_chip_no_t         chip_no;
    mesa_miim_controller_t miim_controller;
    uint8_t                miim_addr;
} phy_device;

typedef struct {
    phy_device    phydev;
} priv_data_t;

//static int phy_modify(phy_device *phydev, uint32_t regnum, uint16_t mask, uint16_t set)
//{
//    return 0;
//}

static int phy_read(phy_device *phydev, uint32_t regnum)
{
    uint16_t  value;

    if (phydev->address.miim_read(NULL, phydev->chip_no, phydev->miim_controller, phydev->miim_addr, regnum, &value) != MESA_RC_OK) {
        return -1;
    }
    return value;
}

static int phy_write(phy_device *phydev, uint32_t regnum, uint16_t val)
{
    if (phydev->address.miim_write(NULL, phydev->chip_no, phydev->miim_controller, phydev->miim_addr, regnum, val) != MESA_RC_OK) {
        return -1;
    }
    return 0;
}

int phy_modify(phy_device *phydev, uint32_t regnum, uint16_t mask, uint16_t set)
{
    uint16_t  value;

    if ((value = phy_read(phydev, regnum)) < 0) {
        return -1;
    }

    value &= ~mask;
    value |= (set & mask);

    if ((value = phy_write(phydev, regnum, value)) < 0) {
        return -1;
    }
    return 0;
}

int phy_write_mmd(phy_device *phydev, int devad, uint32_t regnum, uint16_t val)
{
    if (phydev->address.mmd_write(NULL, phydev->address.port_no, devad, regnum, val) != MESA_RC_OK) {
        return -1;
    }
    return 0;
}

/**
 * genphy_restart_aneg - Enable and Restart Autonegotiation
 * @phydev: target phy_device struct
 */
static int genphy_restart_aneg(phy_device *phydev)
{
    /* Don't isolate the PHY if we're negotiating */
    return phy_modify(phydev, MII_BMCR, BMCR_ISOLATE,
              BMCR_ANENABLE | BMCR_ANRESTART);
}

/* Center KSZ9031RNX FLP timing at 16ms. */
static int center_flp_timing(phy_device *phydev)
{
    int result;

    result = phy_write_mmd(phydev, 0, MII_KSZ9031RN_FLP_BURST_TX_HI,
                   0x0006);
    if (result)
        return result;

    result = phy_write_mmd(phydev, 0, MII_KSZ9031RN_FLP_BURST_TX_LO,
                   0x1A80);
    if (result)
        return result;

    return genphy_restart_aneg(phydev);
}

/**
 * phy_polling_mode - Convenience function for testing whether polling is
 * used to detect PHY status changes
 * @phydev: the phy_device struct
 */
static inline bool phy_polling_mode(phy_device *phydev)
{
    return phydev->irq == PHY_POLL;
}

/**
 * genphy_update_link - update link status in @phydev
 * @phydev: target phy_device struct
 *
 * Description: Update the value in phydev->link to reflect the
 *   current link value.  In order to do this, we need to read
 *   the status register twice, keeping the second value.
 */
static int genphy_update_link(phy_device *phydev)
{
    int status = 0, bmcr;

    bmcr = phy_read(phydev, MII_BMCR);
    if (bmcr < 0)
        return bmcr;

    /* Autoneg is being started, therefore disregard BMSR value and
     * report link as down.
     */
    if (bmcr & BMCR_ANRESTART)
        goto done;

    /* The link state is latched low so that momentary link
     * drops can be detected. Do not double-read the status
     * in polling mode to detect such short link drops.
     */
    if (!phy_polling_mode(phydev)) {
        status = phy_read(phydev, MII_BMSR);
        if (status < 0)
            return status;
        else if (status & BMSR_LSTATUS)
            goto done;
    }

    /* Read link and autonegotiation status */
    status = phy_read(phydev, MII_BMSR);
    if (status < 0)
        return status;
done:
    phydev->link = status & BMSR_LSTATUS ? 1 : 0;
    phydev->autoneg_complete = status & BMSR_ANEGCOMPLETE ? 1 : 0;

    /* Consider the case that autoneg was started and "aneg complete"
     * bit has been reset, but "link up" bit not yet.
     */
    if (phydev->autoneg == AUTONEG_ENABLE && !phydev->autoneg_complete)
        phydev->link = 0;

    return 0;
}

static int genphy_read_status(phy_device *phydev)
{
    int err, old_link = phydev->link;

    /* Update the link, but return if there was an error */
    err = genphy_update_link(phydev);
    if (err)
        return err;

    /* why bother the PHY if nothing can have changed */
    if (phydev->autoneg == AUTONEG_ENABLE && old_link && phydev->link)
        return 0;

    phydev->speed = SPEED_UNKNOWN;
    phydev->duplex = DUPLEX_UNKNOWN;
    phydev->pause = 0;
    phydev->asym_pause = 0;

//    err = genphy_read_lpa(phydev);
//    if (err < 0)
//        return err;

//    if (phydev->autoneg == AUTONEG_ENABLE && phydev->autoneg_complete) {
//        phy_resolve_aneg_linkmode(phydev);
//    } else if (phydev->autoneg == AUTONEG_DISABLE) {
        int bmcr = phy_read(phydev, MII_BMCR);

        if (bmcr < 0)
            return bmcr;

        if (bmcr & BMCR_FULLDPLX)
            phydev->duplex = DUPLEX_FULL;
        else
            phydev->duplex = DUPLEX_HALF;

        if (bmcr & BMCR_SPEED1000)
            phydev->speed = SPEED_1000;
        else if (bmcr & BMCR_SPEED100)
            phydev->speed = SPEED_100;
        else
            phydev->speed = SPEED_10;
//    }

    return 0;
}

static mesa_rc ksz_poll(meba_phy_device_t *dev, meba_phy_driver_status_t *status)
{
    phy_device *phydev = &((priv_data_t *)dev->data)->phydev;

    T_N("Enter  port_no %u", phydev->address.port_no);

    if (genphy_read_status(phydev)) {
        return MESA_RC_ERROR;
    }

    status->link = phydev->link;
    status->speed = (phydev->speed == SPEED_10) ? MESA_SPEED_10M : (phydev->speed == SPEED_100) ? MESA_SPEED_100M : MESA_SPEED_1G;
    status->fdx = (phydev->duplex == DUPLEX_FULL) ? 1 : 0;

    return MESA_RC_OK;
}

static mesa_rc ksz_conf_set(meba_phy_device_t             *dev,
                            meba_port_cap_t               cap,
                            const meba_phy_driver_conf_t  *config)
{
    phy_device  *phydev = &((priv_data_t *)dev->data)->phydev;

    T_D("Enter");

    return center_flp_timing(phydev);
}

static meba_phy_device_t *ksz_probe(meba_phy_driver_t                *drv,
                                    const meba_phy_driver_address_t  *mode)
{
    uint32_t         cnt;
    mesa_port_map_t  *port_map = NULL;
    mesa_port_no_t   port_no = mode->val.mscc_address.port_no;

    meba_phy_device_t *device = (meba_phy_device_t *)calloc(1, sizeof(meba_phy_device_t));
    if (device == NULL)
        return NULL;

    priv_data_t *priv = (priv_data_t *)calloc(1, sizeof(priv_data_t));
    if (priv == NULL) {
        free(device);
        return NULL;
    }

    if (mode->mode != mscc_phy_driver_address_mode) {
        free(device);
        free(priv);
        return NULL;
    }

    /* Get the MIIM access information */
    cnt = mesa_capability(NULL, MESA_CAP_PORT_CNT);
    if ((port_map = calloc(cnt, sizeof(*port_map))) == NULL) {
        free(device);
        free(priv);
        return NULL;
    }
    (void)mesa_port_map_get(NULL, cnt, port_map);

    priv->phydev.address = mode->val.mscc_address;
    priv->phydev.chip_no = port_map[port_no].chip_no;
    priv->phydev.miim_controller = port_map[port_no].miim_controller;
    priv->phydev.miim_addr = port_map[port_no].miim_addr;
    priv->phydev.irq = PHY_POLL;

    device->drv = drv;
    device->data = priv;

    return device;
}

static mesa_rc ksz_status_1g_get(meba_phy_device_t *dev, mesa_phy_status_1g_t *status)
{
    phy_device  *phydev = &((priv_data_t *)dev->data)->phydev;

    T_D("_________________Enter__________________________");

    return MESA_RC_OK;
}

static mesa_rc ksz_1g_if_get(meba_phy_device_t *dev, mesa_port_speed_t speed,
                              mesa_port_interface_t *mac_if) {

    return MESA_RC_OK;
}


static mesa_rc ksz_delete(meba_phy_device_t *dev)
{
    VTSS_FREE(dev->data);
    VTSS_FREE(dev);
    return MESA_RC_OK;
}

meba_phy_drivers_t driver_init()
{
    meba_phy_drivers_t res;
    static meba_phy_driver_t ksz_drivers[1] = {};

    ksz_drivers[0].id = 0;
    ksz_drivers[0].mask = 0;
    ksz_drivers[0].meba_phy_driver_delete = ksz_delete;
    ksz_drivers[0].meba_phy_driver_reset = NULL;
    ksz_drivers[0].meba_phy_driver_poll = ksz_poll;
    ksz_drivers[0].meba_phy_driver_conf_set = ksz_conf_set;
    ksz_drivers[0].meba_phy_driver_if_get = ksz_1g_if_get;
    ksz_drivers[0].meba_phy_driver_mt_get = NULL;
    ksz_drivers[0].meba_phy_driver_power_set = NULL;
    ksz_drivers[0].meba_phy_driver_veriphy_start = NULL;
    ksz_drivers[0].meba_phy_driver_veriphy_get = NULL;
    ksz_drivers[0].meba_phy_driver_media_set = NULL;
    ksz_drivers[0].meba_phy_driver_probe = ksz_probe;
    ksz_drivers[0].meba_phy_driver_status_1g_get = ksz_status_1g_get;

    res.phy_drv = ksz_drivers;
    res.count = 1;

    return res;
}
