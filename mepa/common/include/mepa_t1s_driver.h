// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef MEPA_T1S_DRIVER_H
#define MEPA_T1S_DRIVER_H

#include <microchip/ethernet/phy/api.h>

/**
 * \brief Set T1S PLCA configurations.
 *
 * \param dev    [IN]  Driver instance.
 * \param cfg    [IN]  Set PLCA configurations.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_driver_t1s_set_plca_config_t)(struct mepa_device *dev,
                                                 const mepa_t1s_plca_cfg_t cfg);


/**
 * \brief Get T1S PLCA configurations.
 *
 * \param dev    [IN]  Driver instance.
 * \param cfg    [OUT] Get PLCA configurations.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_driver_t1s_get_plca_config_t)(struct mepa_device *dev,
                                                 mepa_t1s_plca_cfg_t *const cfg);


/** \brief PHY T1S Driver */
typedef struct mepa_t1s_driver {
    mepa_driver_t1s_set_plca_config_t             mepa_driver_t1s_set_plca_config;
    mepa_driver_t1s_get_plca_config_t             mepa_driver_t1s_get_plca_config;
} mepa_t1s_driver_t;

#endif  /* MEPA_T1S_DRIVER_H_ */
