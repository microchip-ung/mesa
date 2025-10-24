// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef PHY_LIB_H
#define PHY_LIB_H

#include "phy_defines.h"

struct phy_reg_dbg {
    const char *string;
    u8 mmd;
    u16 reg;
    u8 bit_hi;
    u8 bit_lo;
    u8 is_32bit;
};

mepa_rc phy_reg_rd(mepa_device_t *const phydev,
                   uint32_t const offset, uint16_t *const value);

mepa_rc phy_reg_wr(mepa_device_t *const phydev,
                   uint32_t const offset, uint16_t const value);

mepa_rc phy_reg_modify(mepa_device_t *const phydev,
                       uint32_t const offset, uint16_t const mask,
                       uint16_t const value);

mepa_rc phy_reg_set_bits(mepa_device_t *const phydev,
                         uint32_t const offset, uint16_t const value);

mepa_rc phy_reg_clear_bits(mepa_device_t *const phydev,
                           uint32_t const offset, uint16_t const value);

mepa_rc phy_mmd_reg_rd(mepa_device_t *const phydev,
                       uint32_t const dev, uint32_t const offset,
                       uint16_t *const value);

mepa_rc phy_mmd_reg_wr(mepa_device_t *const phydev,
                       uint32_t const dev, uint32_t const offset,
                       uint16_t const value);

mepa_rc phy_mmd_reg_modify(mepa_device_t *const phydev,
                           uint32_t const dev, uint32_t const offset,
                           uint16_t const mask, uint16_t const value);

mepa_rc phy_mmd_reg_clear_bits(mepa_device_t *const phydev,
                               uint32_t const dev, uint32_t const offset,
                               uint16_t const value);

mepa_rc phy_mmd_reg_set_bits(mepa_device_t *const phydev,
                             uint32_t const dev, uint32_t const offset,
                             uint16_t const value);

mepa_rc phy_mmd_reg_wr32(mepa_device_t *const dev, uint8_t const mmd,
                         uint32_t const offset, uint32_t value);

mepa_rc phy_mmd_reg_rd32(mepa_device_t *const dev, uint8_t const devad,
                         uint32_t const addr,
                         uint32_t *const value);

mepa_rc phy_mmd_reg_poll(mepa_device_t *const dev, uint8_t const devad,
                         uint16_t const addr, uint16_t match, uint16_t mask,
                         uint8_t cond, uint32_t to, uint16_t *val);

mepa_rc phy_mmd_reg_poll32(mepa_device_t *const dev, uint8_t const devad,
                           uint16_t const addr, uint32_t match, uint32_t mask,
                           uint8_t cond, uint32_t to, uint32_t *val);

mepa_rc phy_mmd_reg_mod32(mepa_device_t *const phydev,
                          uint8_t const dev, uint32_t const offset,
                          uint32_t const mask, uint32_t const value);

void phy_reg_dump(struct mepa_device *dev,
                  const mepa_debug_print_t pr,
                  const struct phy_reg_dbg *const regs,
                  const uint8_t reglen, const uint8_t is_ms);
#endif //PHY_LIB_H
