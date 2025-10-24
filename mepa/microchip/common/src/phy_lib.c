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

mepa_rc phy_mmd_reg_rd32(mepa_device_t *const dev,
                         uint8_t const devad, uint32_t const addr,
                         uint32_t *const value)
{
    mepa_rc rc;
    uint16_t data_l;
    uint16_t data_h;

    /* Read lsb first */
    rc = phy_mmd_reg_rd(dev, devad, addr, &data_l);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    rc = phy_mmd_reg_rd(dev, devad, (addr + 1UL), &data_h);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    *value = data_h;
    *value = (*value << 16U) | data_l;

    return MEPA_RC_OK;
}

mepa_rc phy_mmd_reg_wr32(mepa_device_t *const dev, uint8_t const mmd,
                         uint32_t const offset, uint32_t value)
{
    mepa_rc rc;
    uint16_t data_l = (uint16_t) (value & DEF_MASK);
    uint16_t data_h = (uint16_t) (value >> 16U);

    /* Write msb first */
    rc = phy_mmd_reg_wr(dev, mmd, (offset + 1UL), data_h);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    return phy_mmd_reg_wr(dev, mmd, offset, data_l);
}

mepa_rc phy_mmd_reg_mod32(mepa_device_t *const phydev,
                          uint8_t const dev, uint32_t const offset,
                          uint32_t const mask, uint32_t const value)
{
    uint32_t val = 0;
    uint32_t new_val = 0;
    mepa_rc rc = MEPA_RC_OK;

    rc = phy_mmd_reg_rd32(phydev, dev, offset, &val);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    new_val = (val & ~mask) | value;
    if (val != new_val) {
        rc = phy_mmd_reg_wr32(phydev, dev, offset, new_val);
    }

    return rc;
}

mepa_rc phy_mmd_reg_poll(mepa_device_t *const dev, uint8_t const devad,
                         uint16_t const addr, uint16_t match, uint16_t mask,
                         uint8_t cond, uint32_t to, uint16_t *val)
{
    mepa_bool_t timeout = PHY_FALSE;
    mepa_mtimer_t   timer = { 0 };
    uint8_t result;

    MEPA_MTIMER_START(&timer, to);

    // wait for reset to complete
    while (timeout == PHY_FALSE) {
        timeout = (MEPA_MTIMER_TIMEOUT(&timer));
        if (devad == 0U) {
            (void) phy_reg_rd(dev, addr, val);
        } else {
            (void) phy_mmd_reg_rd(dev, devad, addr, val);
        }
        result = ((*val & mask) == match) ? 1U : 0U;
        if (result == cond) {
            return MEPA_RC_OK;
        }
    }

    return MEPA_RC_INCOMPLETE;
}

mepa_rc phy_mmd_reg_poll32(mepa_device_t *const dev, uint8_t const devad,
                           uint16_t const addr, uint32_t match, uint32_t mask,
                           uint8_t cond, uint32_t to, uint32_t *val)
{
    mepa_bool_t timeout = PHY_FALSE;
    mepa_mtimer_t   timer = { 0 };
    uint8_t result;

    MEPA_MTIMER_START(&timer, to);

    // wait for reset to complete
    while (timeout == PHY_FALSE) {
        timeout = (MEPA_MTIMER_TIMEOUT(&timer));
        (void) phy_mmd_reg_rd32(dev, devad, addr, val);
        result = ((*val & mask) == match) ? 1U : 0U;
        if (result == cond) {
            return MEPA_RC_OK;
        }
    }

    return MEPA_RC_INCOMPLETE;
}

//callout print API
static void phy_dbg_pr(mepa_device_t *const dev,
                       const mepa_debug_print_t pr,
                       uint8_t mmd, uint16_t offset,
                       uint8_t bit_hi, uint8_t bit_lo,
                       const char *str, const uint8_t is_ms)
{
    if (is_ms == 0U) {
        uint16_t value = 0;
        (void) phy_mmd_reg_rd(dev, mmd, offset, &value);
        (void) pr("%-45s:\t[0X%02X].[0X%X]\t=\t0X%08X \r\n", str, mmd, offset, value);
    }

    return;
}

//Register dump
void phy_reg_dump(struct mepa_device *dev,
                  const mepa_debug_print_t pr,
                  const struct phy_reg_dbg *const regs,
                  const uint8_t reglen, const uint8_t is_ms)
{
    uint8_t i;
    uint8_t dev_id = (uint8_t)dev->drv->id;

    //Direct registers
    (void) pr("************ Register Dump for PHY-0x%x ************ \r\n", dev_id);
    (void) pr("%-45s:\tPAGE.REG\t=\tVALUE \r\n", "REG_NAME");
    for (i = 0; i < reglen; i++) {
        phy_dbg_pr(dev, pr, regs[i].mmd, regs[i].reg,
                   regs[i].bit_hi, regs[i].bit_lo,
                   regs[i].string, is_ms);
    }
}
