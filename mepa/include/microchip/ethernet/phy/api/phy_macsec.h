// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_MACSEC_API_H_
#define _MEPA_MACSEC_API_H_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

/** \brief Port Number */
typedef uint32_t mepa_port_no_t;
typedef uint16_t mepa_macsec_vport_id_t;   /**< Virtual port Id. Corresponds to a SecY.  */
typedef uint32_t mepa_macsec_service_id_t; /**< Encapsulation service id */

typedef enum {
    MEPA_MACSEC_VALIDATE_FRAMES_DISABLED, /**< Do not perform integrity check */
    MEPA_MACSEC_VALIDATE_FRAMES_CHECK,    /**< Perform integrity check do not drop failed frames */
    MEPA_MACSEC_VALIDATE_FRAMES_STRICT    /**< Perform integrity check and drop failed frames */
} mepa_validate_frames_t;

/** \brief Values of the CipherSuite control */
typedef enum {
    MEPA_MACSEC_CIPHER_SUITE_GCM_AES_128,     /**< GCM-AES-128 cipher suite */
    MEPA_MACSEC_CIPHER_SUITE_GCM_AES_256,     /**< GCM-AES-256 cipher suite. */
    MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128, /**< GCM-AES-XPN_128 cipher suite for XPN mode. */
    MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256  /**< GCM-AES-XPN_256 cipher suite for XPN mode. */
} mepa_macsec_ciphersuite_t;

/** \brief The mepa_macsec_port_t is a unique identifier to a SecY.
 * This identifier is defined by three properties:
 *  - port_no:    A reference the physical port
 *  - service_id: A reference to a given encapsulation service. The user of the
 *                API may choose any number, this is not used in hardware, but
 *                in cases where external-virtual ports are used this is
 *                required to have a unique identifier to a given SecY.
 *  - port_id:    The port ID which used in the SCI tag.
 * */
typedef struct {
    mepa_port_no_t           port_no;    /**< Physical port no */
    mepa_macsec_service_id_t service_id; /**< Service id */
    mepa_macsec_vport_id_t   port_id;    /**< Virtual port id, the port number used in the optional SCI tag */
} mepa_macsec_port_t;

/** \brief SecY control information (802.1AE section 10.7) */
typedef struct {
    mepa_mac_t mac_addr;                    /**< Mac address of the Tx SecY */
    mepa_validate_frames_t validate_frames; /**< The validateFrames control (802.1AE section 10.7.8) */
    mepa_bool_t replay_protect;                    /**< The replayProtect control (802.1AE section 10.7.8) */
    uint32_t replay_window;                      /**< The replayWindow control (802.1AE section 10.7.8) */
    mepa_bool_t protect_frames;                    /**< The protectFrames control (802.1AE section 10.7.17) */
    mepa_bool_t always_include_sci;                /**< The alwaysIncludeSCI control (802.1AE section 10.7.17) */
    mepa_bool_t use_es;                            /**< The useES control (802.1AE section 10.7.17) */
    mepa_bool_t use_scb;                           /**< The useSCB control (802.1AE section 10.7.17) */
    mepa_macsec_ciphersuite_t current_cipher_suite; /**< The currentCipherSuite control (802.1AE section 10.7.25) */
    uint32_t confidentiality_offset;             /**< The confidentiality Offset control (802.1AE section 10.7.25), 0-64 bytes supported */
} mepa_macsec_secy_conf_t;

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

/*--------------------------------------------------------------------*/
/* MAC Security Entity (SecY) management                              */
/*--------------------------------------------------------------------*/

/** Create a SecY entity of a MACsec port
 *  The entity is created with given parameters.
 *  The controlled port is disabled by default and must be enabled before normal processing.
 *  Classification pattern must be configured to classify traffic to a SecY instance
 *
 */
mepa_rc mepa_macsec_secy_conf_add(struct mepa_device *dev,
                                  const mepa_macsec_port_t port,
                                  const mepa_macsec_secy_conf_t *const conf);
#include <microchip/ethernet/hdr_end.h>
#endif /**< _MEPA_TS_API_H_ */
