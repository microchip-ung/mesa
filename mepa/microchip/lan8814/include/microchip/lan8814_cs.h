// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// This file contains the chip specific api's and its corresponding
// data structures for lan8814

#ifndef _LAN8814_CS_H_
#define _LAN8814_CS_H_

#include <microchip/ethernet/phy/api.h>

//Data structures

/** \brief preferred Downshift count */
typedef enum {
    MEPA_PHY_DOWNSHIFT_CNT_4 = 4,
    MEPA_PHY_DOWNSHIFT_CNT_6 = 6,
} indy_downshift_conf_t;

/** \brief Represents the downshift configuration that is applied to PHY. */
typedef struct {
    mepa_bool_t dsh_enable;   /**< enable downshift for the PHY */
    indy_downshift_conf_t dsh_thr_cnt;   /** <Downshift threshold count */
} indy_phy_downshift_t;

/**
 * \brief
 * Get input of Repetetive count from the user
 *
 * \param dev      [IN]         mepa driver
 * \param rep_cnt  [IN]         repetetive count for port poll exectution per sec
 *
 * \return Return code.
 *  MEPA_RC_OK  on Sucess
 *  MEPA_RC_ERROR on Fail
 **/

/** This API mainly focues on SW Workarounds for ANEG link issue, Auto downshift
  * feature, 100fdx link issue. The user needs to provide the repetetive count
  * for the port poll execution per sec. For ex., rep_cnt = 10 this means port poll
  * API will be called by the user 10 times per sec.
  * This API needs to be called for all the ports by the application before mepa_phy_reset()
  *
  **/
mepa_rc indy_rep_count_set(mepa_device_t *dev, const uint8_t rep_cnt);

/**
 * \brief
 * Configure downshift for a particular port
 *
 * \param dev      [IN]         mepa driver
 * \param dsh  [IN]             downshift configuration parameter
 *
 * \return Return code.
 *  MEPA_RC_OK  on Sucess
 *  MEPA_RC_ERROR on Fail
 **/

/** This API is used to configure Downshift for a particular port. Once downshift configured
 * and couldn't establish link for 4 or 6 secs the speed will be downshifted from 1G to 100M.
 */

mepa_rc indy_downshift_conf_set(mepa_device_t *dev, const indy_phy_downshift_t *dsh);

#endif
