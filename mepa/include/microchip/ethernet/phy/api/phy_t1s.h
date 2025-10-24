// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef MEPA_T1S_API_H
#define MEPA_T1S_API_H

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

/** \brief  T1S PLCA Config */
/*  IEEE-802.3-2022 30.16.1.1 */
typedef struct mepa_t1s_plca_config {
    uint8_t node_count;         /* aPLCANodeCount */
    uint8_t node_id;            /* aPLCALocalNodeID */
    mepa_bool_t plca_enable;    /* acPLCAAdminControl/aPLCAAdminState/ */
    uint8_t tx_oppr_timer;      /* aPLCATransmitOpportunityTimer */
    uint8_t max_burst_cnt;      /* aPLCAMaxBurstCount */
    uint8_t burst_timer;        /* aPLCABurstTimer */
} mepa_t1s_plca_cfg_t;


/**
 * \brief Set t1s plca configurations.
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [IN]  Set plca configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_t1s_set_plca_config(struct mepa_device *dev,
                                 const mepa_t1s_plca_cfg_t cfg);

/**
 * \brief Get t1s plca configurations.
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [OUT] Get plca configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_t1s_get_plca_config(struct mepa_device *dev,
                                 mepa_t1s_plca_cfg_t *const cfg);

#include <microchip/ethernet/hdr_end.h>
#endif /* MEPA_T1S_API_H */
