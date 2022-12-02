// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_MACSEC_API_H_
#define _MEPA_MACSEC_API_H_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

// PHY Line MAC block configuration
typedef struct {
    // Length field (Ether Type) validation is enabled by default, if set length
    // field validation will be disabled. */
    mepa_bool_t dis_length_validate;
} mepa_macsec_lmac_conf_t;

// PHY Host MAC block configuration
typedef struct {
    // Length field (Ether Type) validation is enabled by default, if set length
    // field validation will be disabled.
    mepa_bool_t dis_length_validate;
} mepa_macsec_hmac_conf_t;

// PHY MAC block configuration
typedef struct {
    // Line MAC configuration
    mepa_macsec_lmac_conf_t lmac;

    // Host MAC configuration
    mepa_macsec_hmac_conf_t hmac;
} mepa_macsec_mac_conf_t;

// PHY MACSEC block Bypass configuration
typedef enum {
    // MACSEC block bypass mode None
    MEPA_MACSEC_INIT_BYPASS_NONE,

    // Enable MACSEC block bypass mode
    MEPA_MACSEC_INIT_BYPASS_ENABLE,

    // Disable Macsec block bypass mode
    MEPA_MACSEC_INIT_BYPASS_DISABLE,
} mepa_macsec_init_bypass_t;

// MACsec init structure
typedef struct {
    // Enable the MACsec block
    mepa_bool_t enable;

    // Disable Non Matching MACsec ingress packets processing
    mepa_bool_t dis_ing_nm_macsec_en;

    // MAC block configuration
    mepa_macsec_mac_conf_t mac_conf;

    // MACSEC block Bypass configuration
    mepa_macsec_init_bypass_t bypass;
} mepa_macsec_init_t;

// MACsec Initialization //////////////////////////////////////////////////////

// Initilize the MACsec block
// When the MACsec block is disabled all frames are passed through unchanged.
// This is the default state after Phy initilization.
// When the MACsec block is enabled,  all frames are dropped until SecY (CA) is
// created.
mepa_rc mepa_macsec_init_set(struct mepa_device *dev, const
                             mepa_macsec_init_t *const macsec_init);

// Get the MACsec block init configuration
mepa_rc mepa_macsec_init_get(struct mepa_device *dev,
                             mepa_macsec_init_t *const macsec_init);

#include <microchip/ethernet/hdr_end.h>
#endif /**< _MEPA_TS_API_H_ */
