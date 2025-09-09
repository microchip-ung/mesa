// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef PHY_LIB_H
#define PHY_LIB_H

#include "phy_defines.h"

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

#endif //PHY_LIB_H
