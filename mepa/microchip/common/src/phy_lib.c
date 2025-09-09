// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <phy_lib.h>

//CL22 read register
mepa_rc phy_reg_rd(mepa_device_t *const phydev,
                   uint32_t const offset, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    *value = 0;
    if (phydev->callout->miim_read != NULL) {
        rc = phydev->callout->miim_read(phydev->callout_ctx, offset, value);
    }

    return rc;
}

//CL22 write register
mepa_rc phy_reg_wr(mepa_device_t *const phydev,
                   uint32_t const offset, uint16_t const value)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    if (phydev->callout->miim_write != NULL) {
        rc = phydev->callout->miim_write(phydev->callout_ctx, offset, value);
    }

    return rc;
}

//CL22 modify register
mepa_rc phy_reg_modify(mepa_device_t *const phydev,
                       uint32_t const offset,
                       uint16_t const mask, uint16_t const value)
{
    mepa_rc rc;
    uint16_t val = 0;

    rc = phy_reg_rd(phydev, offset, &val);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    val = (val & ~mask) | value;
    return phy_reg_wr(phydev, offset, val);
}

mepa_rc phy_reg_set_bits(mepa_device_t *const phydev,
                         uint32_t const offset, uint16_t const value)
{
    return phy_reg_modify(phydev, offset, 0, value);
}

mepa_rc phy_reg_clear_bits(mepa_device_t *const phydev,
                           uint32_t const offset, uint16_t const value)
{
    return phy_reg_modify(phydev, offset, value, 0);
}

//Device register read
mepa_rc phy_mmd_reg_rd(mepa_device_t *const phydev,
                       uint32_t const dev, uint32_t const offset,
                       uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    if ((phydev->callout->miim_read != NULL) &&
        (phydev->callout->miim_write != NULL)) {
        *value = 0;

        rc = phydev->callout->miim_write(phydev->callout_ctx, MII_MMD_CTRL,
                                         dev);
        if (rc != MEPA_RC_OK) {
            return rc;
        }

        rc = phydev->callout->miim_write(phydev->callout_ctx, MII_MMD_DATA,
                                         offset);
        if (rc != MEPA_RC_OK) {
            return rc;
        }

        rc = phydev->callout->miim_write(phydev->callout_ctx, MII_MMD_CTRL,
                                         (MMDCTRL_NO_POST_INC | dev));
        if (rc != MEPA_RC_OK) {
            return rc;
        }

        rc = phydev->callout->miim_read(phydev->callout_ctx, MII_MMD_DATA,
                                        value);
    }

    return rc;
}

//Device register write
mepa_rc phy_mmd_reg_wr(mepa_device_t *const phydev,
                       uint32_t const dev, uint32_t const offset,
                       uint16_t const value)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    if ((phydev->callout->miim_read != NULL) &&
        (phydev->callout->miim_write != NULL)) {

        rc = phydev->callout->miim_write(phydev->callout_ctx, MII_MMD_CTRL,
                                         dev);
        if (rc != MEPA_RC_OK) {
            return rc;
        }

        rc = phydev->callout->miim_write(phydev->callout_ctx, MII_MMD_DATA,
                                         offset);
        if (rc != MEPA_RC_OK) {
            return rc;
        }

        rc = phydev->callout->miim_write(phydev->callout_ctx, MII_MMD_CTRL,
                                         (MMDCTRL_NO_POST_INC | dev));
        if (rc != MEPA_RC_OK) {
            return rc;
        }

        rc = phydev->callout->miim_write(phydev->callout_ctx, MII_MMD_DATA,
                                         value);
    }

    return rc;
}

//Device register modify
mepa_rc phy_mmd_reg_modify(mepa_device_t *const phydev,
                           uint32_t const dev, uint32_t const offset,
                           uint16_t const mask, uint16_t const value)
{
    uint16_t val = 0;
    uint16_t new_val = 0;
    mepa_rc rc = MEPA_RC_OK;

    rc = phy_mmd_reg_rd(phydev, dev, offset, &val);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    new_val = (val & ~mask) | value;
    if (val != new_val) {
        rc = phy_mmd_reg_wr(phydev, dev, offset, new_val);
    }

    return rc;
}

mepa_rc phy_mmd_reg_clear_bits(mepa_device_t *const phydev,
                               uint32_t const dev, uint32_t const offset,
                               uint16_t const value)
{
    return phy_mmd_reg_modify(phydev, dev, offset, value, 0);
}

mepa_rc phy_mmd_reg_set_bits(mepa_device_t *const phydev,
                             uint32_t const dev, uint32_t const offset,
                             uint16_t const value)
{
    return phy_mmd_reg_modify(phydev, dev, offset, 0, value);
}
