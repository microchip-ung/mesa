// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_MACSEC_API_H_
#define _MEPA_MACSEC_API_H_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

#define MEPA_MACSEC_10G_MAX_SA 64     /**< 10G PHY Max SAs : 64 */
#define MEPA_MACSEC_1G_MAX_SA  16     /**< 1G PHY Max SAs : 16 */
#define MEPA_MACSEC_SA_PER_SC_MAX  4  /**< SAs per SC Max : 4 */
#define MEPA_MACSEC_SA_PER_SC_MIN  2  /**< SAs per SC Min : 2 */

#define MEPA_MACSEC_SA_PER_SC MEPA_MACSEC_SA_PER_SC_MAX /**< SAs per SCs : 4 */
#define MEPA_MACSEC_MAX_SA     MEPA_MACSEC_10G_MAX_SA   /**< 10G PHY Max SAs : 64 */
#define MEPA_MACSEC_MAX_SA_RX  MEPA_MACSEC_MAX_SA       /**< Max Rx SAs */
#define MEPA_MACSEC_MAX_SA_TX  MEPA_MACSEC_MAX_SA       /**< Max Tx SAs */
#define MEPA_MACSEC_MAX_SC_RX  MEPA_MACSEC_MAX_SA/2     /**< Max Rx SCs : 32/8 */
#define MEPA_MACSEC_MAX_SC_TX  MEPA_MACSEC_MAX_SC_RX    /**< Max Tx SCs : 32/8 */
#define MEPA_MACSEC_MAX_SECY   MEPA_MACSEC_MAX_SC_TX    /**< Max SecYs : 32/8 */

#define MEPA_MAC_BLOCK_MTU_MAX 0x2748                   /**< MAC Block Max MTU Size */


/** \brief SecY port status as defined by 802.1AE */
typedef struct {
    mepa_bool_t mac_enabled;                                  /**< MAC is enabled (802.1AE) */
    mepa_bool_t mac_operational;                              /**< MAC is operational (802.1AE) */
    mepa_bool_t oper_point_to_point_mac;                      /**< Point to point oper status (802.1AE) */
} mepa_macsec_port_status_t;

typedef struct {
    mepa_macsec_port_status_t controlled;                     /**< 802.1AE Controlled port status */
    mepa_macsec_port_status_t uncontrolled;                   /**< 802.1AE Uncontrolled port status */
    mepa_macsec_port_status_t common;                         /**< 802.1AE Common port status */
} mepa_macsec_secy_port_status_t;

/** \brief Port Number */
typedef uint32_t mepa_port_no_t;
typedef uint16_t mepa_macsec_vport_id_t;                      /**< Virtual port Id. Corresponds to a SecY.  */
typedef uint32_t mepa_macsec_service_id_t;                    /**< Encapsulation service id */

/** \brief packet number of 32-bit or 64-bit size. */
typedef union {
    uint32_t pn;                                              /**< packet number of 32 bit size. */
    uint64_t xpn;                                             /**< extended packet number of 64 bit size. */
} mepa_macsec_pkt_num_t;

typedef enum {
    MEPA_MACSEC_VALIDATE_FRAMES_DISABLED,                     /**< Do not perform integrity check */
    MEPA_MACSEC_VALIDATE_FRAMES_CHECK,                        /**< Perform integrity check do not drop failed frames */
    MEPA_MACSEC_VALIDATE_FRAMES_STRICT                        /**< Perform integrity check and drop failed frames */
} mepa_validate_frames_t;

/** \brief Values of the CipherSuite control */
typedef enum {
    MEPA_MACSEC_CIPHER_SUITE_GCM_AES_128,                     /**< GCM-AES-128 cipher suite */
    MEPA_MACSEC_CIPHER_SUITE_GCM_AES_256,                     /**< GCM-AES-256 cipher suite. */
    MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128,                 /**< GCM-AES-XPN_128 cipher suite for XPN mode. */
    MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256                  /**< GCM-AES-XPN_256 cipher suite for XPN mode. */
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
    mepa_port_no_t           port_no;                         /**< Physical port no */
    mepa_macsec_service_id_t service_id;                      /**< Service id */
    mepa_macsec_vport_id_t   port_id;                         /**< Virtual port id, the port number used in the optional SCI tag */
} mepa_macsec_port_t;

/** \brief SecY control information (802.1AE section 10.7) */
typedef struct {
    mepa_mac_t mac_addr;                                      /**< Mac address of the Tx SecY */
    mepa_validate_frames_t validate_frames;                   /**< The validateFrames control (802.1AE section 10.7.8) */
    mepa_bool_t replay_protect;                               /**< The replayProtect control (802.1AE section 10.7.8) */
    uint32_t replay_window;                                   /**< The replayWindow control (802.1AE section 10.7.8) */
    mepa_bool_t protect_frames;                               /**< The protectFrames control (802.1AE section 10.7.17) */
    mepa_bool_t always_include_sci;                           /**< The alwaysIncludeSCI control (802.1AE section 10.7.17) */
    mepa_bool_t use_es;                                       /**< The useES control (802.1AE section 10.7.17) */
    mepa_bool_t use_scb;                                      /**< The useSCB control (802.1AE section 10.7.17) */
    mepa_macsec_ciphersuite_t current_cipher_suite;           /**< The currentCipherSuite control (802.1AE section 10.7.25) */
    uint32_t confidentiality_offset;                          /**< The confidentiality Offset control (802.1AE section 10.7.25), 0-64 bytes supported */
} mepa_macsec_secy_conf_t;

/** \brief Salt for cryptographic operations */
typedef struct {
    uint8_t buf[12];                                          /**< Buffer containing 12 byte Salt for XPN. */
} mepa_macsec_salt_t;

/** \brief An 128-bit or 256-bit AES key */
typedef struct {
    uint8_t buf[32];                                          /**< Buffer containing the key */
    uint32_t len;                                             /**< Length of key in bytes (16 or 32) */
    uint8_t h_buf[16];                                        /**< Buffer containing the 128-bit AES key hash */
    mepa_macsec_salt_t salt;                                  /**< salt used for XPN */
} mepa_macsec_sak_t;

/** 8 byte Secure Channel Identifier (SCI)  */
typedef struct {
    mepa_mac_t              mac_addr;                         /**< 6 byte MAC address */
    mepa_macsec_vport_id_t  port_id;                          /**< 2 byte Port Id */
} mepa_macsec_sci_t;

/** \brief Short SCI (SSCI). Used for XPN. */
typedef struct {
    uint8_t buf[4];                                           /**< Buffer containing the 4-byte SSCI for XPN. */
} mepa_macsec_ssci_t;

/** \brief Rx SecA XPN status as defined by 802.1AE */
typedef struct {
    mepa_macsec_pkt_num_t next_pn;                            /**< Rev B Next XPN (802.1AEW) */
    mepa_macsec_pkt_num_t lowest_pn;                          /**< Rev B Lowest XPN */
} mepa_macsec_rx_sa_pn_status_t;

/** \brief Rx SA status as defined by 802.1AE */
typedef struct {
    mepa_bool_t in_use;                                       /**< In use (802.1AE)  */
    uint32_t next_pn;                                         /**< Next pn (802.1AE) */
    uint32_t lowest_pn;                                       /**< Lowest_pn (802.1AE) */
    uint32_t created_time;                                    /**< Created time (802.1AE) */
    uint32_t started_time;                                    /**< Started time (802.1AE) */
    uint32_t stopped_time;                                    /**< Stopped time (802.1AE) */
    mepa_macsec_rx_sa_pn_status_t pn_status;                  /**< Rx SecA XPN status */
} mepa_macsec_rx_sa_status_t;

/** \brief Tx SecA XPN status as defined by 802.1AE */
typedef struct {
    mepa_macsec_pkt_num_t  next_pn;                           /**< Rev B Next XPN */
} mepa_macsec_tx_sa_pn_status_t;

/** \brief Tx SA status as defined by 802.1AE */
typedef struct {
    mepa_bool_t in_use;                                       /**< In use (802.1AE)  */
    uint32_t next_pn;                                         /**< Next PN (802.1AE) */
    uint32_t created_time;                                    /**< Creation time (802.1AE)*/
    uint32_t started_time;                                    /**< Started time (802.1AE)*/
    uint32_t stopped_time;                                    /**< Stopped time (802.1AE) */
    mepa_macsec_tx_sa_pn_status_t pn_status;                  /**< Rev B Tx SecA XPN status */
} mepa_macsec_tx_sa_status_t;

/** \brief Rx SC parameters (optional) */
typedef struct {
    mepa_validate_frames_t validate_frames;                   /**< The validateFrames control (802.1AE section 10.7.8) */
    mepa_bool_t replay_protect;                               /**< The replayProtect control (802.1AE section 10.7.8) */
    uint32_t replay_window;                                   /**< The replayWindow control (802.1AE section 10.7.8) */
    uint32_t confidentiality_offset;                          /**< The confidentiality Offset control (802.1AE section 10.7.25), 0-64 bytes supported */
} mepa_macsec_rx_sc_conf_t;

/** \brief Rx SC status as defined by 802.1AE section 10.7 */
typedef struct {
    mepa_bool_t receiving;                                    /**< Receiving status (802.1AE) */
    uint32_t created_time;                                    /**< Created time (802.1AE) */
    uint32_t started_time;                                    /**< Started time (802.1AE) */
    uint32_t stopped_time;                                    /**< Stopped time (802.1AE) */
} mepa_macsec_rx_sc_status_t;

/** \brief Tx SC parameters (optional) */
typedef struct {
    mepa_bool_t protect_frames;                               /**< The protectFrames control (802.1AE section 10.7.17) */
    mepa_bool_t always_include_sci;                           /**< The alwaysIncludeSCI control (802.1AE section 10.7.17) */
    mepa_bool_t use_es;                                       /**< The useES control (802.1AE section 10.7.17) */
    mepa_bool_t use_scb;                                      /**< The useSCB control (802.1AE section 10.7.17) */
    uint32_t confidentiality_offset;                          /**< The confidentiality Offset control (802.1AE section 10.7.25), 0-64 bytes supported */
} mepa_macsec_tx_sc_conf_t;

/** \brief Tx SC status as defined by 802.1AE */
typedef struct {
    mepa_macsec_sci_t sci;                                    /**< SCI id (802.1AE) */
    mepa_bool_t transmitting;                                 /**< Transmitting status (802.1AE) */
    uint16_t encoding_sa;                                     /**< Encoding (802.1AE) */
    uint16_t enciphering_sa;                                  /**< Enciphering (802.1AE)  */
    uint32_t created_time;                                    /**< Created time (802.1AE) */
    uint32_t started_time;                                    /**< Started time (802.1AE) */
    uint32_t stopped_time;                                    /**< Stopped time (802.1AE) */
} mepa_macsec_tx_sc_status_t;


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

/** MACsec configuration of MTU for ingress and egress packets
 * If an egress MACsec packet that causes the MTU to be exceeded will cause the per-SA Out_Pkts_Too_Long*/
typedef struct {
    uint32_t  mtu;                                    /**< Defines the maximum packet size (in bytes) - VLAN tagged packets are allowed to be 4 bytes longer */
    mepa_bool_t drop;                                 /**< Set to TRUE in order to drop packets larger than mtu. Set to FALSE in order to allow packets larger than mtu to be transmitted (Out_Pkts_Too_Long will still count). Frames will be "dropped" by corrupting the frame's CRC. Packets with source port as the Common port or the reserved port are ingress, packets from the Controlled or Uncontrolled port are egress.*/
    mepa_bool_t vlan_unaware_en;                      /**< Set TRUE for VLAN unaware mode. Set FALSE for VLAN aware mode.*/
} mepa_macsec_mtu_t;

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

/** Create a SecY entity of a MACsec port
 * The SecY is updated with given parameters.
 * Note that the SecY must exist
 * SecY update with new parameters i.e. Replay Window size etc, it will
 * update newly create SA's only. Existing parameters i.e. Next PN and Lower PN
 * will not change. Tx/Rx SA Status Next PN and Lowest PN shows different
 * as compare with existing Tx/Rx SA Status.
 *
 */
mepa_rc mepa_macsec_secy_conf_update(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     const mepa_macsec_secy_conf_t *const conf);

/** Get the SecY entry. */
mepa_rc mepa_macsec_secy_conf_get(struct mepa_device *dev,
                                  const mepa_macsec_port_t port,
                                  mepa_macsec_secy_conf_t *const conf);

/** \brief Delete the SecY and the associated SCs/SAs */
mepa_rc mepa_macsec_secy_conf_del(struct mepa_device *dev,
                                  const mepa_macsec_port_t port);

/** \brief Enable/Disable the SecY's controlled (secure) port.
* The controlled port is disabled by default.
*/
mepa_rc mepa_macsec_secy_controlled_set(struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        const mepa_bool_t enable);

/** Get the state config of the controlled (secure) port. */
mepa_rc mepa_macsec_secy_controlled_get(struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        mepa_bool_t *const enable);

/** Get status from a SecY port, controlled, uncontrolled or common. */
mepa_rc mepa_macsec_secy_port_status_get(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         mepa_macsec_secy_port_status_t *const status);

/** Browse through available macsec ports (secy's) on a physical port
 *  Use NULL pointer to get the first port and use found ports as a search port in the next round.
*/
mepa_rc mepa_macsec_port_get_next(struct mepa_device *dev,
                                  const mepa_port_no_t port_no,
                                  const mepa_macsec_port_t *const search_macsec_port,
                                  mepa_macsec_port_t *const found_macsec_port);


/*--------------------------------------------------------------------*/
/* Receive Secure Channel (SC) management                             */
/*--------------------------------------------------------------------*/

/** Create an Rx SC object inside of the SecY. */
mepa_rc mepa_macsec_rx_sc_add(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci);

/** Instead of inheriting the configuration from the SecY the Rx SC can use its own configuration.
* RxSC update with new parameters i.e. Replay Window size etc, it will
* update newly create SA's only. Existing parameters i.e. Next PN and Lower PN
* will not change. Rx SA Status Next PN and Lowest PN shows different
* as compare with existing Rx SA Status.
*/
mepa_rc mepa_macsec_rx_sc_update(struct mepa_device *dev,
                                 const mepa_macsec_port_t port,
                                 const mepa_macsec_sci_t  *const sci,
                                 const mepa_macsec_rx_sc_conf_t *const conf);

/*Get the configuration of the SC. */
mepa_rc mepa_macsec_rx_sc_get_conf(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const mepa_macsec_sci_t *const sci,
                                   mepa_macsec_rx_sc_conf_t *const conf);

/* Browse through the Rx SCs inside of the SecY. */
mepa_rc mepa_macsec_rx_sc_get_next(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const mepa_macsec_sci_t *const search_sci,
                                   mepa_macsec_sci_t *const found_sci);


/* Delete the Rx SC and the associated SAs */
mepa_rc mepa_macsec_rx_sc_del(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci);

/* Rx SC status info */
mepa_rc mepa_macsec_rx_sc_status_get(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     const mepa_macsec_sci_t *const sci,
                                     mepa_macsec_rx_sc_status_t *const status);

/*--------------------------------------------------------------------*/
/* Transmit Secure Channel (SC) management                            */
/*--------------------------------------------------------------------*/

/** Create an Tx SC object inside of the SecY.  One TxSC is supported for each SecY.  */
mepa_rc mepa_macsec_tx_sc_set(struct mepa_device *dev,
                              const mepa_macsec_port_t port);

/** \brief Instead of inheriting the configuration from the SecY the Tx SC can use its own configuration.
 * TxSC update with new parameters i.e. Replay Window size etc, it will
 * update newly create SA's only. Existing parameters i.e. Next PN and Lower PN
 * will not change. Tx SA Status Next PN and Lowest PN shows different
 * as compare with existing Tx SA Status.
 *
 */
mepa_rc mepa_macsec_tx_sc_update(struct mepa_device *dev,
                                 const mepa_macsec_port_t port,
                                 const mepa_macsec_tx_sc_conf_t *const conf);


/** Get the SC configuration */
mepa_rc mepa_macsec_tx_sc_get_conf(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   mepa_macsec_tx_sc_conf_t *const conf);

/** \brief Delete the Tx SC object and the associated SAs */
mepa_rc mepa_macsec_tx_sc_del(struct mepa_device *dev,
                              const mepa_macsec_port_t port);


/** \brief Tx SC status */
mepa_rc mepa_macsec_tx_sc_status_get(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     mepa_macsec_tx_sc_status_t *const status);

/*--------------------------------------------------------------------*/
/* Receive Secure Association (SA) management                         */
/*--------------------------------------------------------------------*/

/** Create an Rx SA which is associated with an SC within the SecY.
 *  This SA is not enabled until mepa_macsec_rx_sa_activate() is performed. */
mepa_rc mepa_macsec_rx_sa_set(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci,
                              const uint16_t an,
                              const uint32_t lowest_pn,
                              const mepa_macsec_sak_t *const sak);

/** Get the Rx SA configuration of the active SA.

 * If SA was created before any change on parameter like Replay Widow etc. Lowest PN may appear to be consistent with newly
 * updated value, but the actual value will be according to the SA's creation time. One has to subtract the change in the
 * the value obtained from API to get the actual value. Updating parameters like Replay Window doesn't change the older SA's.
 */
mepa_rc mepa_macsec_rx_sa_get(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci,
                              const uint16_t an,
                              uint32_t *const lowest_pn,
                              mepa_macsec_sak_t *const sak,
                              mepa_bool_t *const active);


/** Activate the SA associated with the AN.
    The reception switches from a previous SA to the SA identified by the AN.
    Note that the reception using the new SA does not necessarily begin immediately. **/
mepa_rc mepa_macsec_rx_sa_activate(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const mepa_macsec_sci_t *const sci,
                                   const uint16_t an);

/** This function disables Rx SA identified by an. Frames still in the pipeline are not discarded. */
mepa_rc mepa_macsec_rx_sa_disable(struct mepa_device *dev,
                                  const mepa_macsec_port_t port,
                                  const mepa_macsec_sci_t *const sci,
                                  const uint16_t an);


/** This function deletes Rx SA object identified by an. The Rx SA must be disabled before deleted. */
mepa_rc mepa_macsec_rx_sa_del(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const mepa_macsec_sci_t *const sci,
                              const uint16_t an);


/** Set (update) the packet number (pn) value to value in lowest_pn */
mepa_rc mepa_macsec_rx_sa_lowest_pn_update(struct mepa_device *dev,
                                           const mepa_macsec_port_t port,
                                           const mepa_macsec_sci_t *const sci,
                                           const uint16_t an,
                                           const uint32_t lowest_pn);

/** Rx SA status get
 * If SA was created before any change on parameter like Replay Widow etc. Lowest PN may appear to be consistent with newly
 * updated value, but the actual value will be according to the SA's creation time. One has to subtract the change in the
 * the value obtained from API to get the actual value. Updating parameters like Replay Window doesn't change the older SA's.
 */
mepa_rc mepa_macsec_rx_sa_status_get(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     const mepa_macsec_sci_t *const sci,
                                     const uint16_t an,
                                     mepa_macsec_rx_sa_status_t *const status);

/*--------------------------------------------------------------------*/
/* For XPN supported devices                                          */
/* Receive Secure Association (SA) management                         */
/*--------------------------------------------------------------------*/

/** Create an Rx SA which is associated with an SC within the SecY. */
mepa_rc mepa_macsec_rx_seca_set(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_sci_t *const sci,
                                const uint16_t an,
                                const mepa_macsec_pkt_num_t lowest_pn,
                                const mepa_macsec_sak_t *const sak,
                                const mepa_macsec_ssci_t *const ssci);

/** Get the Rx SA configuration of the active SA. */
mepa_rc mepa_macsec_rx_seca_get(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_sci_t *const sci,
                                const uint16_t an,
                                mepa_macsec_pkt_num_t *const lowest_pn,
                                mepa_macsec_sak_t *const sak,
                                mepa_bool_t *const active,
                                mepa_macsec_ssci_t *const ssci);



/** Update the lowest_pn packet number in 64-bit or 32-bit for Rx SA. */
mepa_rc mepa_macsec_rx_seca_lowest_pn_update(struct mepa_device *dev,
                                             const mepa_macsec_port_t port,
                                             const mepa_macsec_sci_t *const sci,
                                             const uint16_t an,
                                             const mepa_macsec_pkt_num_t lowest_pn);

/*--------------------------------------------------------------------*/
/* Transmit Secure Association (SA) management                        */
/*--------------------------------------------------------------------*/

/**Create an Tx SA which is associated with the Tx SC within the SecY.
 * This SA is not in use until mepa_macsec_tx_sa_activate() is performed.
 * If SA was created before any change in parameters like Replay Widow etc. Lowest PN may appear to be consistent with newly
 * updated value, but the actual value will be according to the SA's creation time. One has to subtract the change in the
 * the value obtained from API to get the actual value. Updating parameters like Replay Window doesn't change the older SA's.
 *
 */
mepa_rc mepa_macsec_tx_sa_set(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const uint16_t an,
                              const uint32_t next_pn,
                              const mepa_bool_t confidentiality,
                              const mepa_macsec_sak_t *const sak);


/**Get the  Tx SA configuration.*/
mepa_rc mepa_macsec_tx_sa_get(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const uint16_t an,
                              uint32_t *const next_pn,
                              mepa_bool_t *const confidentiality,
                              mepa_macsec_sak_t *const sak,
                              mepa_bool_t *const active);


/** This function switches transmission from a previous Tx SA to the Tx SA identified by an.
    Transmission using the new SA is in effect immediately.
 */
mepa_rc mepa_macsec_tx_sa_activate(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const uint16_t an);


/** This function disables Tx SA identified by an. Frames still in the pipeline are not discarded. */
mepa_rc mepa_macsec_tx_sa_disable(struct mepa_device *dev,
                                  const mepa_macsec_port_t port,
                                  const uint16_t an);


/** This function deletes Tx SA object identified by an. The Tx SA must be disabled before deleted. */
mepa_rc mepa_macsec_tx_sa_del(struct mepa_device *dev,
                              const mepa_macsec_port_t port,
                              const uint16_t an);

/**Tx SA status
 * If SA was created before any change on parameter like Replay Widow etc. Lowest PN may appear to be consistent with newly
 * updated value, but the actual value will be according to the SA's creation time. One has to subtract the change in the
 * the value obtained from API to get the actual value. Updating parameters like Replay Window doesn't change the older SA's.
 */
mepa_rc mepa_macsec_tx_sa_status_get(struct mepa_device *dev,
                                     const mepa_macsec_port_t port,
                                     const uint16_t an,
                                     mepa_macsec_tx_sa_status_t *const status);

/*--------------------------------------------------------------------*/
/* For XPN supported devices                                          */
/* Transmit Secure Association (SA) management                        */
/*--------------------------------------------------------------------*/

/** Create an Tx SA which is associated with the Tx SC within the SecY.
 * This SA is not in use until mepa_macsec_tx_sa_activate() is performed.
 */
mepa_rc mepa_macsec_tx_seca_set(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const uint16_t an,
                                const mepa_macsec_pkt_num_t next_pn,
                                const mepa_bool_t confidentiality,
                                const mepa_macsec_sak_t *const sak,
                                const mepa_macsec_ssci_t *const ssci);

/**Get the Tx SA configuration supporting 64-bit and 32-bit PN. */
mepa_rc mepa_macsec_tx_seca_get(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const uint16_t an,
                                mepa_macsec_pkt_num_t *const next_pn,
                                mepa_bool_t *const confidentiality,
                                mepa_macsec_sak_t *const sak,
                                mepa_bool_t *const active,
                                mepa_macsec_ssci_t *const ssci);


/*--------------------------------------------------------------------*/
/* SecY Counters                                                      */
/*--------------------------------------------------------------------*/
/** \brief Counter structure for common counters */
typedef struct {
    uint64_t if_in_octets;                                    /**< In octets       */
    uint64_t if_in_ucast_pkts;                                /**< In unicasts     */
    uint64_t if_in_multicast_pkts;                            /**< In multicasts   */
    uint64_t if_in_broadcast_pkts;                            /**< In broadcasts   */
    uint64_t if_in_discards;                                  /**< In discards     */
    uint64_t if_in_errors;                                    /**< In errors       */
    uint64_t if_out_octets;                                   /**< Out octets      */
    uint64_t if_out_ucast_pkts;                               /**< Out unicasts    */
    uint64_t if_out_multicast_pkts;                           /**< Out multicasts  */
    uint64_t if_out_broadcast_pkts;                           /**< Out broadcasts  */
    uint64_t if_out_errors;                                   /**< Out errors      */
} mepa_macsec_common_counters_t;

/** \brief Counter structure for uncontrolled counters */
typedef struct {
    uint64_t if_in_octets;                                    /**< In octets       */
    uint64_t if_in_ucast_pkts;                                /**< In unicasts     */
    uint64_t if_in_multicast_pkts;                            /**< In multicasts   */
    uint64_t if_in_broadcast_pkts;                            /**< In broadcasts   */
    uint64_t if_in_discards;                                  /**< In discards     */
    uint64_t if_in_errors;                                    /**< In errors       */
    uint64_t if_out_octets;                                   /**< Out octets      */
    uint64_t if_out_ucast_pkts;                               /**< Out unicasts    */
    uint64_t if_out_multicast_pkts;                           /**< Out multicasts  */
    uint64_t if_out_broadcast_pkts;                           /**< Out broadcasts  */
    uint64_t if_out_errors;                                   /**< Out errors      */
} mepa_macsec_uncontrolled_counters_t;

/** \brief Counter structure for SecY ports */
typedef struct {
    uint64_t if_in_octets;                                    /**< In octets       */
    uint64_t if_in_pkts;                                      /**< Out octets      */
    uint64_t if_in_ucast_pkts;                                /**< In unicasts   - available from Rev B */
    uint64_t if_in_multicast_pkts;                            /**< In multicasts - available from Rev B */
    uint64_t if_in_broadcast_pkts;                            /**< In broadcasts - available from Rev B */
    uint64_t if_in_discards;                                  /**< In discards     */
    uint64_t if_in_errors;                                    /**< In errors       */
    uint64_t if_out_octets;                                   /**< Out octets      */
    uint64_t if_out_pkts;                                     /**< Out packets     */
    uint64_t if_out_errors;                                   /**< Out errors      */
    uint64_t if_out_ucast_pkts;                               /**< Out unicasts   - available from Rev B */
    uint64_t if_out_multicast_pkts;                           /**< Out multicasts - available from Rev B */
    uint64_t if_out_broadcast_pkts;                           /**< Out broadcasts - available from Rev B */
} mepa_macsec_secy_port_counters_t;

/** \brief SecY counters as defined by 802.1AE */
typedef struct {
    uint64_t in_pkts_untagged;                                /**< Received packets without the secTAG when secyValidateFrames is not in strict mode. NOTE: Theses packets will be counted in the uncontrolled if_in_pkts and not in the controlled if_in_pkts  */
    uint64_t in_pkts_no_tag;                                  /**< Received packets discarded without the secTAG when secyValidateFrames is in strict mode. */
    uint64_t in_pkts_bad_tag;                                 /**< Received packets discarded with an invalid secTAG or zero value PN or an invalid PN. */
    uint64_t in_pkts_unknown_sci;                             /**< Received packets with unknown SCI when secyValidateFrames is not in strict mode
                                                                 and the C bit in the SecTAG is not set. */
    uint64_t in_pkts_no_sci;                                  /**< Received packets discarded with unknown SCI when  secyValidateFrames is in strict mode
                                                                 or the C bit in the SecTAG is set. */
    uint64_t in_pkts_overrun;                                 /**< Received packets discarded because the number of receive packets exceeded the
                                                                 cryptographic performace capabilities. */
    uint64_t in_octets_validated;                             /**< Received octets validated */
    uint64_t in_octets_decrypted;                             /**< Received octets decrypted */
    uint64_t out_pkts_untagged;                               /**< Number of packets transmitted without the MAC security TAG. NOTE: Theses packets will be counted in the uncontrolled if_out_pkts and not in the controlled if_out_pkts for Rev A of macsec. From Rev B onwards, they will be counted under controlled port for successful SA lookup */
    uint64_t out_pkts_too_long;                               /**< Number of transmitted packets discarded because the packet length is larger than the interface MTU. */
    uint64_t out_octets_protected;                            /**< The number of octets integrity protected but not encrypted. */
    uint64_t out_octets_encrypted;                            /**< The number of octets integrity protected and encrypted. */
} mepa_macsec_secy_counters_t;

/* Possible values for the mepa_macsec_secy_cap_t:ciphersuite_cap */
#define MEPA_MACSEC_CAP_GCM_AES_128       0x0001              /**< GCM-AES-128 cipher suite capability */
#define MEPA_MACSEC_CAP_GCM_AES_256       0x0002              /**< GCM-AES-256 cipher suite capability */
#define MEPA_MACSEC_CAP_GCM_AES_XPN_128   0x0004              /**< GCM-AES-XPN-256 cipher suite capability (extended PN) */
#define MEPA_MACSEC_CAP_GCM_AES_XPN_256   0x0008              /**< GCM-AES-XPN-256 cipher suite capability (extended PN) */

/** \brief Capabilities as defined by 802.1AE */
typedef struct {
    uint16_t max_peer_scs;                                    /**< Max peer SCs (802.1AE) */
    uint16_t max_receive_keys;                                /**< Max Rx keys  (802.1AE) */
    uint16_t max_transmit_keys;                               /**< Max Tx keys  (802.1AE) */
    uint32_t ciphersuite_cap;                                 /**< The cipher suite capability offered by the API and chip */
} mepa_macsec_secy_cap_t;

/** Get counters from a SecY controlled (802-1AE) port.*/
mepa_rc mepa_macsec_controlled_counters_get(struct mepa_device *dev,
                                            const mepa_macsec_port_t port,
                                            mepa_macsec_secy_port_counters_t *const counters);

/** Get counters from a physical uncontrolled (802-1AE) port. */
mepa_rc mepa_macsec_uncontrolled_counters_get(struct mepa_device                   *dev,
                                              const mepa_port_no_t                port_no,
                                              mepa_macsec_uncontrolled_counters_t *const counters);

/** Get counters from a physical common (802-1AE) port. */
mepa_rc mepa_macsec_common_counters_get(struct mepa_device *dev,
                                        const mepa_port_no_t port_no,
                                        mepa_macsec_common_counters_t *const counters);


/** Get the capabilities of the SecY as define by 802.1AE. */
mepa_rc mepa_macsec_secy_cap_get(struct mepa_device *dev,
                                 const mepa_port_no_t port_no,
                                 mepa_macsec_secy_cap_t *const cap);


/**SecY counters */
mepa_rc mepa_macsec_secy_counters_get(struct mepa_device *dev,
                                      const mepa_macsec_port_t port,
                                      mepa_macsec_secy_counters_t *const counters);


/** MacSec counter update.  Keep the API internal SW counters updated.
 *  Should be called periodically, but no special requirement to interval (the chip counters are 40bit).
 */
mepa_rc mepa_macsec_counters_update(struct mepa_device *dev,
                                    const mepa_port_no_t port_no);


/** MacSec counter clear.  Clear all counters. */
mepa_rc mepa_macsec_counters_clear(struct mepa_device *dev,
                                   const mepa_port_no_t port_no);

/*--------------------------------------------------------------------*/
/* SC Counters                                                        */
/*--------------------------------------------------------------------*/
/** \brief SC Counters as defined by 802.1AE. */
typedef struct {
    // Bugzilla#12752
    uint64_t in_pkts_unchecked;                            /**< Unchecked packets (802.1AE) - Due to a chip limitation InOctetsValidated/Decrypted is not incremented. The API will not correctly count "if_in_octets" since this counter is indirectly derived from InOctetsValidated/Decrypted which per standard. Hence if_in_octets calculation of controlled port is incorrect and only the DMAC and SMAC octets are counted.*/

    uint64_t in_pkts_delayed;                              /**< Delayed packets (802.1AE) */
    uint64_t in_pkts_late;                                 /**< Late packets (802.1AE) */
    uint64_t in_pkts_ok;                                   /**< Ok packets (802.1AE) */
    uint64_t in_pkts_invalid;                              /**< Invalid packets (802.1AE) */
    uint64_t in_pkts_not_valid;                            /**< No valid packets (802.1AE) */
    uint64_t in_pkts_not_using_sa;                         /**< Packets not using SA (802.1AE) */
    uint64_t in_pkts_unused_sa;                            /**< Unused SA (802.1AE) */
    uint64_t in_octets_validated;                          /**< Received octets validated */
    uint64_t in_octets_decrypted;                          /**< Received octets decrypted */
} mepa_macsec_rx_sc_counters_t;


/** \brief Tx SC counters as defined by 802.1AE */
typedef struct {
    uint64_t out_pkts_protected;                           /**< Protected but not encrypted (802.1AE) */
    uint64_t out_pkts_encrypted;                           /**< Both protected and encrypted (802.1AE) */
    uint64_t out_octets_protected;                         /**< The number of octets integrity protected but not encrypted. */
    uint64_t out_octets_encrypted;                         /**< The number of octets integrity protected and encrypted. */
} mepa_macsec_tx_sc_counters_t;



/** RX SC counters */
mepa_rc mepa_macsec_rx_sc_counters_get(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
                                       const mepa_macsec_sci_t *const sci,
                                       mepa_macsec_rx_sc_counters_t *const counters);

/** Rx SC counters */
mepa_rc mepa_macsec_tx_sc_counters_get(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
                                       mepa_macsec_tx_sc_counters_t *const counters);

/*--------------------------------------------------------------------*/
/* SA Counters                                                        */
/*--------------------------------------------------------------------*/
/** \brief Tx SA counters as defined by 802.1AE */
typedef struct {
  uint64_t out_pkts_protected;                            /**< Protected but not encrypted (802.1AE) */
  uint64_t out_pkts_encrypted;                            /**< Both protected and encrypted (802.1AE) */
} mepa_macsec_tx_sa_counters_t;


/** \brief Rx SA counters as defined by 802.1AE */
typedef struct {
    uint64_t in_pkts_ok;                                  /**< Ok packets  (802.1AE) */
    uint64_t in_pkts_invalid;                             /**< Invalid packets (802.1AE) */
    uint64_t in_pkts_not_valid;                           /**< Not valid packets (802.1AE) */
    uint64_t in_pkts_not_using_sa;                        /**< Not using SA (802.1AE) */
    uint64_t in_pkts_unused_sa;                           /**< Unused SA (802.1AE) */

    // Bugzilla#12752
    uint64_t in_pkts_unchecked;                           /**< Unchecked packets (802.1AE) - Due to a chip limitation InOctetsValidated/Decrypted is not incremented. The API will not correctly count "if_in_octets" since this counter is indirectly derived from InOctetsValidated/Decrypted which per standard. Hence if_in_octets calculation of controlled port is incorrect and only the DMAC and SMAC octets are counted.*/

    uint64_t in_pkts_delayed;                             /**< Delayed packets (802.1AE) */
    uint64_t in_pkts_late;                                /**< Late packets (802.1AE) */
} mepa_macsec_rx_sa_counters_t;


/** Tx SA counters */
mepa_rc mepa_macsec_tx_sa_counters_get(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
                                       const uint16_t an,
                                       mepa_macsec_tx_sa_counters_t *const counters);


/** Tx SA counters */
mepa_rc mepa_macsec_rx_sa_counters_get(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
                                       const mepa_macsec_sci_t *const sci,
                                       const uint16_t an,
                                       mepa_macsec_rx_sa_counters_t *const counters);

/*--------------------------------------------------------------------*/
/* VP / Uncontrolled classification                                   */
/*--------------------------------------------------------------------*/
#define MEPA_MACSEC_MATCH_DISABLE        0x0001           /**< Disable match  */
#define MEPA_MACSEC_MATCH_DMAC           0x0002           /**< DMAC match  */
#define MEPA_MACSEC_MATCH_ETYPE          0x0004           /**< ETYPE match */
#define MEPA_MACSEC_MATCH_VLAN_ID        0x0008           /**< VLAN match  */
#define MEPA_MACSEC_MATCH_VLAN_ID_INNER  0x0010           /**< Inner VLAN match */
#define MEPA_MACSEC_MATCH_BYPASS_HDR     0x0020           /**< MPLS header match */
#define MEPA_MACSEC_MATCH_IS_CONTROL     0x0040           /**< Control frame match e.g. Ethertype 0x888E */
#define MEPA_MACSEC_MATCH_HAS_VLAN       0x0080           /**< The frame contains a VLAN tag */
#define MEPA_MACSEC_MATCH_HAS_VLAN_INNER 0x0100           /**< The frame contains an inner VLAN tag */
#define MEPA_MACSEC_MATCH_SMAC           0x0200           /**< Source MAC address  */

#define MEPA_MACSEC_MATCH_PRIORITY_LOWEST 15              /**< Lowest possible matching priority */
#define MEPA_MACSEC_MATCH_PRIORITY_LOW    12              /**< Low matching priority */
#define MEPA_MACSEC_MATCH_PRIORITY_MID     8              /**< Medium matching priority */
#define MEPA_MACSEC_MATCH_PRIORITY_HIGH    4              /**< High matching priority */
#define MEPA_MACSEC_MATCH_PRIORITY_HIGHEST 0              /**< Hihhest possible matching priority */

/** \brief MACsec control frame matching */
typedef struct {
    uint32_t            match;                            /**< Use combination of (OR): VTSS_MACSEC_MATCH_DMAC,
                                                             MEPA_MACSEC_MATCH_ETYPE */
    mepa_mac_t     dmac;                                  /**< DMAC address to match (SMAC not supported) */
    mepa_etype_t   etype;                                 /**< Ethernet type to match  */
} mepa_macsec_control_frame_match_conf_t;

/**Set the control frame matching rules.
 *  16 rules are supported for ETYPE (8 for 1G Phy).
 *   8 rules are supported for DMACs
 *   2 rules are supported for ETYPE & DMAC
 */
mepa_rc mepa_macsec_control_frame_match_conf_set(struct mepa_device *dev ,
                                                 const mepa_port_no_t port_no,
                                                 const mepa_macsec_control_frame_match_conf_t *const conf,
                                                 uint32_t *const rule_id);

/** Delete a control frame matching rule. */
mepa_rc mepa_macsec_control_frame_match_conf_del(struct mepa_device *dev,
                                                 const mepa_port_no_t port_no,
                                                 const uint32_t rule_id);

/**
 Get the control frame matching rules.
 */
mepa_rc mepa_macsec_control_frame_match_conf_get(struct mepa_device *dev,
                                                 const mepa_port_no_t port_no,
                                                 mepa_macsec_control_frame_match_conf_t *const conf,
                                                 uint32_t rule_id);

/** \brief Matching patterns,
 * When traffic is passed through the MACsec processing block, it will be match
 * against a set of rules. If non of the rules matches, it will be matched
 * against the default rules (one and only on of the default rules will always
 * match) defined in mepa_macsec_default_action_policy_t.
 *
 * The classification rules are associated with a MACsec port and an action. The
 * action is defined in mepa_macsec_match_action_t and defines if frames
 * should be dropped, forwarded to the controlled or the un-controlled port of
 * the given virtual MACsec port.
 *
 * These classification rules are used both on the ingress and the egress side.
 * On the ingress side, only tags located before the SECtag will be used.
 *
 * These rules are a limited resource, and the HW is limited to allow the same
 * amount of classification rules as concurrent SA streams. Therefore to utilize
 * the hardware 100%, they should only be used to associate traffic with the
 * controlled port of a MACsec port. In simple scenarios where a single peer is
 * connected to a single PHY, there are more then sufficiet resources to use
 * this mechanism for associate traffic with the uncontrolled port.
 *
 * Instead of using this to forward control frames to the uncontrolled port,
 * the default rules may be used to bypass those frames. This will however have
 * the following consequences:
 *  - The controlled frames will not be included in uncontrolled port
 *    counters. To get the correct counter values, the application will need to
 *    gather all the control frames, calculate the statistics and use this to
 *    compensate the uncontrolled port counters.
 *  - All frames which are classified as control frames are passed through. If
 *    the control frame matches against the ether-type, it will
 *    evaluate to true in the following three cases:
 *     * If the ether-type located directly after the source MAC address matches
 *     * If the ether-type located the first VLAN tag matches
 *     * If the ether-type located a double VLAN tag matches
 * */

typedef struct {
    /** This field is used to specify which part of the matching pattern is
     * active. If multiple fields are active, they must all match if the
     * pattern is to match.  */
    uint32_t          match;

    /** Signals if the frame has been classified as a control frame. This allow
     * to match if a frame must be classified as a control frame, or if it has
     * not be classified as a control frame. The classification is controlled
     * by the mepa_macsec_control_frame_match_conf_t struct. This field is
     * activated by setting the MEPA_MACSEC_MATCH_IS_CONTROL in "match" */
    mepa_bool_t         is_control;

    /** Signals if the frame contains a VLAN tag. This allows to match if a VLAN
     * tag must exists, and if a VLAN tag must not exists. This field is
     * activated by setting the MEPA_MACSEC_MATCH_HAS_VLAN bit in "match" */
    mepa_bool_t         has_vlan_tag;

    /** Signals if the frame contains an inner VLAN tag. This allows to match if
     * an inner VLAN tag must exists, and if an inner VLAN tag must not exists.
     * This field is activated by setting the MEPA_MACSEC_MATCH_HAS_VLAN_INNER
     * bit in "match" */
    mepa_bool_t         has_vlan_inner_tag;

    /** This field can be used to match against a parsed ether-type. This
     * field is activated by setting the MEPA_MACSEC_MATCH_ETYPE bit in "match"
     */
    mepa_etype_t etype;

    /** This field can be used to match against the VLAN id. This field is
     * activated by setting the MEPA_MACSEC_MATCH_VLAN_ID bit in "match" */
    mepa_vid_t   vid;

    /** This field can be used to match against the inner VLAN id. This field
     * is activated by setting the MEPA_MACSEC_MATCH_VLAN_ID_INNER bit in
     * "match" */
    mepa_vid_t   vid_inner;

    /** This field along with hdr_mask is used to do a binary matching of a MPLS
     * header. This is activated by setting the MEPA_MACSEC_MATCH_BYPASS_HDR bit
     * in "match" */
    uint8_t           hdr[8];

    /** Full mask set for the 'hdr' field. */
    uint8_t           hdr_mask[8];

    /** In case multiple rules matches a given frame, the rule with the highest
     * priority wins. Valid range is 0 (highest) - 15 (lowest).*/
    uint8_t           priority;

    /** This field can be used to match against the Source MAC address.  This field is
     * activated by setting the MEPA_MACSEC_MATCH_SMAC bit in "match" */
    mepa_mac_t   src_mac;

    /** This field can be used to match against the Destination MAC address.  This field is
     * activated by setting the MEPA_MACSEC_MATCH_DMAC bit in "match" */
    mepa_mac_t   dest_mac;
} mepa_macsec_match_pattern_t;

/** \brief Pattern matching actions */
typedef enum {
    /** Drop the packet */
    MEPA_MACSEC_MATCH_ACTION_DROP=0,

   /** Forward the packet to the controlled port */
    MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT=1,

    /** Forward the packet to the uncontrolled port */
    MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT=2,

    /** Number of actions - always add new actions above this line */
    MEPA_MACSEC_MATCH_ACTION_CNT = 3,
} mepa_macsec_match_action_t;


/** \brief Type used to state direction  */
typedef enum {
    /** Ingress. Traffic which is received by the port. */
    MEPA_MACSEC_DIRECTION_INGRESS=0,

    /** Egress. Traffic which is transmitted on the port. */
    MEPA_MACSEC_DIRECTION_EGRESS=1,

    /** Number of directions - will always be 2 */
    MEPA_MACSEC_DIRECTION_CNT = 2,

} mepa_macsec_direction_t;

/** Configure the Matching pattern for a given MACsec port, for a given
 * action. Only one action may be associated with each actions. One matching
 * slot will be acquired immediately when this is called for the "DROP" or the
 * "UNCONTROLLED_PORT" actions. When matching pattern is configured for the
 * "CONTROLLED_PORT" action, HW a matching resource will be acquired for every
 * SA added.
 */
mepa_rc mepa_macsec_pattern_set(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_direction_t direction,
                                const mepa_macsec_match_action_t action,
                                const mepa_macsec_match_pattern_t *const pattern);

/** Delete a pattern matching rule.*/
mepa_rc mepa_macsec_pattern_del(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_direction_t direction,
                                const mepa_macsec_match_action_t action);

/** Get the pattern matching rule. */
mepa_rc mepa_macsec_pattern_get(struct mepa_device *dev,
                                const mepa_macsec_port_t port,
                                const mepa_macsec_direction_t direction,
                                const mepa_macsec_match_action_t action,
                                mepa_macsec_match_pattern_t *const pattern);


/** \brief Default matching actions */
typedef enum {
    MEPA_MACSEC_DEFAULT_ACTION_DROP   = 0,  /**< Drop frame */
    MEPA_MACSEC_DEFAULT_ACTION_BYPASS = 1,  /**< Bypass frame */
} mepa_macsec_default_action_t;

/** \brief Default policy.
 * Frames not matched by any of the MACsec patterns will be evaluated against
 * the default policy.
 */
typedef struct {
    /**  Defines action for ingress frames which are not classified as MACsec
     *   frames and not classified as control frames. */
    mepa_macsec_default_action_t ingress_non_control_and_non_macsec;

    /**  Defines action for ingress frames which are not classified as MACsec
     *   frames and are classified as control frames. */
    mepa_macsec_default_action_t ingress_control_and_non_macsec;

    /**  Defines action for ingress frames which are classified as MACsec frames
     *   and are not classified as control frames. */
    mepa_macsec_default_action_t ingress_non_control_and_macsec;

    /**  Defines action for ingress frames which are classified as MACsec frames
     *   and are classified as control frames. */
    mepa_macsec_default_action_t ingress_control_and_macsec;

    /**  Defines action for egress frames which are classified as control frames. */
    mepa_macsec_default_action_t egress_control;

    /**  Defines action for egress frames which are not classified as control frames. */
    mepa_macsec_default_action_t egress_non_control;
} mepa_macsec_default_action_policy_t;

/** Assign default policy */
mepa_rc mepa_macsec_default_action_set(struct mepa_device *dev,
                                       const mepa_port_no_t port_no,
                                       const mepa_macsec_default_action_policy_t *const policy);

/** Get default policy */
mepa_rc mepa_macsec_default_action_get(struct mepa_device *dev,
                                       const mepa_port_no_t port_no,
                                       mepa_macsec_default_action_policy_t *const policy);

/*--------------------------------------------------------------------*/
/* Header / TAG Bypass                                                */
/*--------------------------------------------------------------------*/

/** \brief  Enum for Bypass mode, Tag or Header  */
typedef enum {
    MEPA_MACSEC_BYPASS_NONE,                          /**< Disable bypass mode  */
    MEPA_MACSEC_BYPASS_TAG,                           /**< Enable TAG bypass mode  */
    MEPA_MACSEC_BYPASS_HDR,                           /**< Enable Header bypass mode */
} mepa_macsec_bypass_t;

/** \brief Structure for Bypass mode */
typedef struct {
    mepa_macsec_bypass_t  mode;                       /**< Bypass Mode, Tag bypass or Header bypass */
    uint32_t hdr_bypass_len;                          /**< (ignored for TAG bypass) Header Bypass length, possible values: 2,4,6..16 bytes.
                                                       * The bypass includes MPLS DA + MPLS SA + MPLS Etype (before frame DA/SA)
                                                       * E.g. the value '4' means 6+6+2+4=18 bytes (MPLS dmac + MPLS smac + MPLS etype + 4) */
    mepa_etype_t hdr_etype;                           /**< (ignored for TAG bypass) Header Bypass: Etype to match (at frame index 12)
                                                       * When matched, process control packets using DMAC/SMAC/Etype after the header
                                                       * If not matched process control packets using the first DMAC/SMAC/Etype (as normally done) */
} mepa_macsec_bypass_mode_t;

/** \brief Enum for number of TAGs  */
typedef enum {
    MEPA_MACSEC_BYPASS_TAG_ZERO,                      /**< Disable */
    MEPA_MACSEC_BYPASS_TAG_ONE,                       /**< Bypass 1 tag */
    MEPA_MACSEC_BYPASS_TAG_TWO,                       /**< Bypass 2 tags */
} mepa_macsec_tag_bypass_t;


/** Set header bypass mode globally for the port */
mepa_rc mepa_macsec_bypass_mode_set(struct mepa_device *dev,
                                    const mepa_port_no_t port_no,
                                    const mepa_macsec_bypass_mode_t *const bypass);

/** Get the header bypass mode */
mepa_rc mepa_macsec_bypass_mode_get(struct mepa_device *dev,
                                    const mepa_port_no_t port_no,
                                    mepa_macsec_bypass_mode_t *const bypass);


/** Set the bypass tag mode i.e. number of Tags to bypass: 0(disable), 1 or 2 tags.*/
mepa_rc mepa_macsec_bypass_tag_set(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   const mepa_macsec_tag_bypass_t tag);

/** Get the bypass Tag mode i.e. 0, 1 or 2 tags. */
mepa_rc mepa_macsec_bypass_tag_get(struct mepa_device *dev,
                                   const mepa_macsec_port_t port,
                                   mepa_macsec_tag_bypass_t *const tag);

/*--------------------------------------------------------------------*/
/* Others                                                             */
/*--------------------------------------------------------------------*/

#define MEPA_MACSEC_FRAME_CAPTURE_SIZE_MAX 504 /**< The maximum frame size supported for MACSEC capturing */

/** \brief Enum for frame capturing  */
typedef enum {
    MEPA_MACSEC_FRAME_CAPTURE_DISABLE,               /**< Disable frame capturing */
    MEPA_MACSEC_FRAME_CAPTURE_INGRESS,               /**< Enable ingress frame capturing */
    MEPA_MACSEC_FRAME_CAPTURE_EGRESS,                /**< Enable egress frame capturing */
} mepa_macsec_frame_capture_t;

/** Sets MTU for both ingress and egress. */
mepa_rc mepa_macsec_mtu_set(struct mepa_device *dev,
                            const mepa_port_no_t port_no,
                            const mepa_macsec_mtu_t *const mtu_conf);

/** Gets current MTU configuration */
mepa_rc mepa_macsec_mtu_get(struct mepa_device *dev,
                            const mepa_port_no_t port_no,
                            mepa_macsec_mtu_t *mtu_conf);

/** Enable frame capture.  Used for test/debugging.
 *   The buffer will only capture the first frame received after capturing has been started
 *   The procedure for frame capturing is as follow:
 *   1) Start capturing (Call mepa_macsec_frame_capture_set with MEPA_MACSEC_FRAME_CAPTURE_INGRESS/MEPA_MACSEC_FRAME_CAPTURE_EGRESS)
 *   2) Send in the frame to be captured
 *   3) Disable capturing (Call mepa_macsec_frame_capture_set with MEPA_MACSEC_FRAME_CAPTURE_DISABLE) in order to prepare for next capturing.
 *   4) Get the captured frame using mepa_macsec_frame_get.
 *
 */

mepa_rc mepa_macsec_frame_capture_set(struct mepa_device *dev,
                                      const mepa_port_no_t port_no,
                                      const mepa_macsec_frame_capture_t capture);

/** Get a frame from an internal capture buffer. Used for test/debugging. */
mepa_rc mepa_macsec_frame_get(struct mepa_device *dev,
                              const mepa_port_no_t port_no,
                              const uint32_t buf_length,
                              uint32_t *const return_length,
                              uint8_t *const frame);

/** \brief Enum for events  */
typedef enum {
    MEPA_MACSEC_SEQ_NONE  = 0x0,
    MEPA_MACSEC_SEQ_THRESHOLD_EVENT = 0x1,
    MEPA_MACSEC_SEQ_ROLLOVER_EVENT  = 0x2,
    MEPA_MACSEC_SEQ_ALL   = 0x3
} mepa_macsec_event_t;


/**
 * Enabling / Disabling of events
 **/
mepa_rc mepa_macsec_event_enable_set(struct mepa_device *dev,
                                     const mepa_port_no_t port_no,
                                     const mepa_macsec_event_t ev_mask,
                                     const mepa_bool_t enable);

/**
 * Get Enabling of events
 **/
mepa_rc mepa_macsec_event_enable_get(struct mepa_device *dev,
                                     const mepa_port_no_t port_no,
                                     mepa_macsec_event_t *const ev_mask);

/**
 * Polling for active events
 **/
mepa_rc mepa_macsec_event_poll(struct mepa_device *dev,
                               const mepa_port_no_t port_no,
                               mepa_macsec_event_t *const ev_mask);


/**
 * Configure the SEQ threshold
 **/
mepa_rc mepa_macsec_event_seq_threshold_set(struct mepa_device *dev,
                                            const mepa_port_no_t port_no,
                                            const uint32_t threshold);

/**
 * Get the SEQ threshold
 **/
mepa_rc mepa_macsec_event_seq_threshold_get(struct mepa_device *dev,
                                            const mepa_port_no_t port_no,
                                            uint32_t *const threshold);

/**
 * Get the Egress Interrupt SA Active AN
 **/
mepa_rc mepa_macsec_egr_intr_sa_get(struct mepa_device *dev,
                                    const mepa_port_no_t port_no,
                                    mepa_macsec_port_t *const port,
                                    uint16_t *const an);

/**
 * \brief Chip register read
 *
 **/
mepa_rc mepa_macsec_csr_read(struct mepa_device *dev,
                             const mepa_port_no_t port_no,
                             const uint16_t mmd,
                             const uint32_t addr,
                             uint32_t *const value);
/**
 * \brief Chip register write
 *
 **/
mepa_rc mepa_macsec_csr_write(struct mepa_device *dev,
                              const mepa_port_no_t port_no,
                              const uint32_t mmd,
                              const uint32_t addr,
                              const uint32_t value);

/** \brief Debug counters for counting the number error return codes.  */
typedef struct {
    uint32_t invalid_sci_macaddr;     /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_INVALID_SCI_MACADDR*/
    uint32_t macsec_not_enabled;      /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_NOT_ENABLED*/
    uint32_t secy_already_in_use;     /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_SECY_ALREADY_IN_USE*/
    uint32_t no_secy_found;           /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_NO_SECY_FOUND*/
    uint32_t no_secy_vacency;         /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_NO_SECY_VACANCY*/
    uint32_t invalid_validate_frm;    /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_INVALID_VALIDATE_FRM*/
    uint32_t invalid_hdr_bypass_len;  /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN*/
    uint32_t sc_not_found;            /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_SC_NOT_FOUND*/
    uint32_t could_not_prg_sa_match;  /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH*/
    uint32_t could_not_prg_sa_flow;   /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW*/
    uint32_t could_not_ena_sa;        /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA*/
    uint32_t could_not_set_sa;        /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_SET_SA*/
    uint32_t no_ctrl_frm_match;       /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH*/
    uint32_t could_not_set_pattern;   /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN*/
    uint32_t timeout_issue;           /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_TIMEOUT_ISSUE*/
    uint32_t could_not_empty_egress;  /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS*/
    uint32_t an_not_created;          /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_AN_NOT_CREATED*/
    uint32_t could_not_empty_ingress; /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS*/
    uint32_t tx_sc_not_exist;         /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_TX_SC_NOT_EXIST*/
    uint32_t could_not_disable_sa;    /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA*/
    uint32_t could_not_del_rx_sa;     /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA*/
    uint32_t could_not_del_tx_sa;     /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA*/
    uint32_t pattern_not_set;         /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_PATTERN_NOT_SET*/
    uint32_t hw_resource_exhusted;    /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED*/
    uint32_t sci_already_exist;       /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_SCI_ALREADY_EXISTS*/
    uint32_t sc_resource_not_found;   /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND*/
    uint32_t rx_an_already_in_use;    /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE*/
    uint32_t empty_record;            /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_EMPTY_RECORD*/
    uint32_t could_not_prg_xform;     /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM*/
    uint32_t could_not_toggle_sa;     /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA*/
    uint32_t tx_an_already_in_use;    /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE*/
    uint32_t all_available_sa_in_use; /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE*/
    uint32_t match_disable;           /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_MATCH_DISABLE*/
    uint32_t all_cp_rules_in_use;     /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE*/
    uint32_t pattern_prio_not_valid;  /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID*/
    uint32_t buffer_too_small;        /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_BUFFER_TOO_SMALL*/
    uint32_t frm_too_long;            /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_FRAME_TOO_LONG*/
    uint32_t frm_truncated;           /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_FRAME_TRUNCATED*/
    uint32_t phy_powered_down;        /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_PHY_POWERED_DOWN*/
    uint32_t phy_not_macsec_capable;  /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE*/
    uint32_t an_not_exist;            /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_AN_NOT_EXIST*/
    uint32_t no_pattern_cfg;          /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_NO_PATTERN_CFG*/
    uint32_t unexpected_speed;        /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_UNEXPECT_SPEED*/
    uint32_t max_mtu;                 /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_MAX_MTU*/
    uint32_t unexpected_cp_mode;      /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_UNEXPECT_CP_MODE*/
    uint32_t could_not_disable_an;    /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN*/
    uint32_t rule_out_of_range;       /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_RULE_OUT_OF_RANGE*/
    uint32_t rule_not_exit;           /**< Number of errors happen with error code MEPA_RC_ERR_MACSEC_RULE_NOT_EXIT*/
    uint32_t csr_read;                /**< Number of errors happen with error code MEPA_RC_ERR_CSR_READ*/
    uint32_t csr_write;               /**< Number of errors happen with error code MEPA_RC_ERR_CSR_WRITE*/
    uint32_t unknown_rc_code;         /**< Number of errors happen with unknown error code*/
} mepa_macsec_rc_dbg_counters_t;

/**
 * Get return code debug counters
**/
mepa_rc mepa_macsec_dbg_counter_get(struct mepa_device *dev,
                                    const mepa_port_no_t port_no,
                                    mepa_macsec_rc_dbg_counters_t *const counters);


#define deb_counter_get mepa_macsec_dbg_counter_get /**< Backward compatibility */

/*--------------------------------------------------------------------*/
/* Line MAC / Host MAC / FC                                           */
/*--------------------------------------------------------------------*/

/** \brief Host/Line Mac Counters */
typedef struct {
    /* Rx RMON counters */
    uint64_t if_rx_octets;           /**< In octets       */
    uint64_t if_rx_in_bytes;         /**< In bytes        */
    uint32_t if_rx_pause_pkts;       /**< In pause        */
    uint32_t if_rx_ucast_pkts;       /**< In unicasts     */
    uint32_t if_rx_multicast_pkts;   /**< In multicasts   */
    uint32_t if_rx_broadcast_pkts;   /**< In broadcasts   */
    uint32_t if_rx_discards;         /**< In discards     */
    uint32_t if_rx_errors;           /**< In errors       */

    uint64_t if_rx_StatsPkts;        /**< In All Pkt cnts    */
    uint32_t if_rx_CRCAlignErrors;   /**< In CRC errors      */
    uint32_t if_rx_UndersizePkts;    /**< In Undersize pkts  */
    uint32_t if_rx_OversizePkts;     /**< In Oversize pkts   */
    uint32_t if_rx_Fragments;        /**< In Fragments       */
    uint32_t if_rx_Jabbers;          /**< In Jabbers         */
    uint32_t if_rx_Pkts64Octets;         /**< In Pkts64Octets         */
    uint32_t if_rx_Pkts65to127Octets;    /**< In Pkts65to127Octets    */
    uint32_t if_rx_Pkts128to255Octets;   /**< In Pkts128to255Octets   */
    uint32_t if_rx_Pkts256to511Octets;   /**< In Pkts256to511Octets   */
    uint32_t if_rx_Pkts512to1023Octets;  /**< In Pkts512to1023Octets  */
    uint32_t if_rx_Pkts1024to1518Octets; /**< In Pkts1024to1518Octets */
    uint32_t if_rx_Pkts1519toMaxOctets;  /**< In Pkts1519toMaxOctets  */

    /* Tx RMON counters */
    uint64_t if_tx_octets;           /**< Out octets      */
    uint32_t if_tx_pause_pkts;       /**< Out pause       */
    uint32_t if_tx_ucast_pkts;       /**< Out unicasts    */
    uint32_t if_tx_multicast_pkts;   /**< Out multicasts  */
    uint32_t if_tx_broadcast_pkts;   /**< Out broadcasts  */
    uint32_t if_tx_errors;           /**< Out errors      */

    uint32_t if_tx_DropEvents;            /**< Out _DropEvents          */
    uint64_t if_tx_StatsPkts;             /**< Out StatsPkts            */
    uint32_t if_tx_Collisions;            /**< Out Collisions           */
    uint32_t if_tx_Pkts64Octets;          /**< Out Pkts64Octets         */
    uint32_t if_tx_Pkts65to127Octets;     /**< Out Pkts65to127Octets    */
    uint32_t if_tx_Pkts128to255Octets;    /**< Out Pkts128to255Octets   */
    uint32_t if_tx_Pkts256to511Octets;    /**< Out Pkts256to511Octets   */
    uint32_t if_tx_Pkts512to1023Octets;   /**< Out Pkts512to1023Octets  */
    uint32_t if_tx_Pkts1024to1518Octets;  /**< Out Pkts1024to1518Octets */
    uint32_t if_tx_Pkts1519toMaxOctets;   /**< Out Pkts1519toMaxOctets  */
} mepa_macsec_mac_counters_t;

/**
 * Host Mac counters (To be moved)
 *
 **/
mepa_rc mepa_macsec_hmac_counters_get(struct mepa_device *dev,
                                      const mepa_port_no_t port_no,
                                      mepa_macsec_mac_counters_t *const counters,
                                      const mepa_bool_t clear);

/**
 * Line Mac counters (To be moved)
 *
 **/
mepa_rc mepa_macsec_lmac_counters_get(struct mepa_device *dev,
                                      const mepa_port_no_t port_no,
                                      mepa_macsec_mac_counters_t *const counters,
                                      const mepa_bool_t clear);
/**
 * Function for getting if a port is MACSEC capable
 **/
mepa_rc mepa_macsec_is_capable(struct mepa_device *dev,
                               const mepa_port_no_t port_no,
                               mepa_bool_t *capable);
/**
 * Function for dump MACSEC registers
 **/

mepa_rc mepa_macsec_dbg_reg_dump(struct mepa_device *dev,
                                 const mepa_port_no_t port_no,
                                 const mepa_debug_print_t pr);

/*--------------------------------------------------------------------*/
/* Macsec SC Instance Counters structures                                */
/*--------------------------------------------------------------------*/

/** \brief No. of  Tx SA or Rx SA Information */
typedef struct {
    uint8_t no_sa;                              /**< No. of SAs configured */
    uint8_t sa_id[MEPA_MACSEC_SA_PER_SC_MAX];   /**< Configured SA ids */
} mepa_sc_inst_count_t;

/*--------------------------------------------------------------------*/
/* Macsec SecY Instance Counters structures                                */
/*--------------------------------------------------------------------*/

/** \brief No. of  Tx SC and Rx SC Information */
typedef struct {
    uint8_t no_txsc;                            /**< No. of Tx SCs configured */
    uint8_t txsc_id;                            /**< Configured Tx SC ids */
    mepa_macsec_sci_t tx_sci;              /**< Tx SCI */
    mepa_sc_inst_count_t txsc_inst_count;  /**< Tx SC Instances */
    uint8_t no_rxsc;                            /**< No. of Rx SCs configured */
    uint8_t rxsc_id[MEPA_MACSEC_MAX_SC_RX];     /**< Configured Rx SC ids */
    mepa_macsec_sci_t rx_sci[MEPA_MACSEC_MAX_SC_RX];             /**< Rx SCIs */
    mepa_sc_inst_count_t rxsc_inst_count[MEPA_MACSEC_MAX_SC_RX]; /**< Rx SCs Instances */
} mepa_secy_inst_count_t;

/*--------------------------------------------------------------------*/
/* Macsec Instance Counters structures                                */
/*--------------------------------------------------------------------*/

/** \brief No. of  SecYs, Virtual Port Information */
typedef struct {
    uint8_t no_secy;                       /**< No. of SecYs configured */
    uint8_t secy_vport[MEPA_MACSEC_MAX_SECY]; /**< Configured SecY virtual port */
    mepa_secy_inst_count_t secy_inst_count[MEPA_MACSEC_MAX_SECY]; /**< SecY Instances */
} mepa_macsec_inst_count_t;

/** Get the Instances count of SecYs, Rx SCs, Tx SA and Rx SAs.
 *
 */
mepa_rc mepa_macsec_inst_count_get(struct mepa_device *dev,
                                   const mepa_port_no_t   port_no,
                                   mepa_macsec_inst_count_t *count);

/** Clear the RMON Line mac counters.
 */
mepa_rc mepa_macsec_lmac_counters_clear(struct mepa_device *dev,
                                        const mepa_port_no_t port_no);

/** Clear the RMON Host mac counters.
 */
mepa_rc mepa_macsec_hmac_counters_clear(struct mepa_device *dev,
                                        const mepa_port_no_t port_no);

/** Clear the Macsec Debug counters.
 */
mepa_rc mepa_macsec_debug_counters_clear(struct mepa_device *dev,
                                         const mepa_port_no_t port_no);

/**Clear the Common counters.
 */
mepa_rc mepa_macsec_common_counters_clear(struct mepa_device *dev,
                                          const mepa_port_no_t port_no);

/** Clear the Uncontrolled port counters.
 */
mepa_rc mepa_macsec_uncontrolled_counters_clear(struct mepa_device *dev,
                                                const mepa_port_no_t port_no);

/** Clear the Controlled port counters.
 */
mepa_rc mepa_macsec_controlled_counters_clear (struct mepa_device *dev,
                                               const mepa_macsec_port_t port);

/**Clear the Rx SA counters.
 */
mepa_rc mepa_macsec_rxsa_counters_clear(struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        const mepa_macsec_sci_t *const sci,
                                        const uint16_t an);

/** Clear the Rx SC counters. */
mepa_rc mepa_macsec_rxsc_counters_clear(struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        const mepa_macsec_sci_t  *const sci);

/** Clear the Tx SA counters. */
mepa_rc mepa_macsec_txsa_counters_clear(struct mepa_device *dev,
                                        const mepa_macsec_port_t  port,
                                        const uint16_t  an);

/** Clear the Tx SC counters. */
mepa_rc mepa_macsec_txsc_counters_clear (struct mepa_device *dev,
                                         const mepa_macsec_port_t port);

/** Clear the SecY counters. */
mepa_rc mepa_macsec_secy_counters_clear (struct mepa_device *dev,
                                         const mepa_macsec_port_t port);

/** Get the Macsec Enable Status. */
mepa_rc mepa_macsec_port_enable_status_get (struct mepa_device *dev,
                                            const mepa_port_no_t port_no,
                                            mepa_bool_t *status);

/** Get the Macsec RxSA AN Status. */
mepa_rc mepa_macsec_rxsa_an_status_get (struct mepa_device *dev,
                                        const mepa_macsec_port_t port,
                                        const mepa_macsec_sci_t *const sci,
                                        const uint16_t an,
                                        mepa_bool_t *status);

/** Get MAC Block MTU and Tag Check configuration. */
mepa_rc mepa_mac_block_mtu_get(struct mepa_device *dev,
                               const mepa_port_no_t port_no,
                               uint16_t *const mtu_value,
                               mepa_bool_t *const mtu_tag_check);

/** Set MAC Block MTU and Tag Check configuration. */
mepa_rc mepa_mac_block_mtu_set(struct mepa_device *dev,
                               const mepa_port_no_t port_no,
                               const uint16_t mtu_value,
                               const mepa_bool_t mtu_tag_check);

/** Set frame gap compensation in FC Buffer. */
mepa_rc mepa_macsec_fcbuf_frame_gap_comp_set(struct mepa_device *dev,
                                             const mepa_port_no_t port_no,
                                             const uint8_t frm_gap);

/** Flow Control buffer Block Reg Dump. */
mepa_rc mepa_macsec_dbg_fcb_block_reg_dump(struct mepa_device *dev,
                                           const mepa_port_no_t port_no,
                                           const mepa_debug_print_t pr);


/** Flow Control buffer Block Reg Dump. */
mepa_rc mepa_macsec_dbg_frm_match_handling_ctrl_reg_dump(struct mepa_device *dev,
                                                         const mepa_port_no_t port_no,
                                                         const mepa_debug_print_t pr);


#ifdef MEPA_MACSEC_FIFO_OVERFLOW_WORKAROUND
/** MACsec Debug Re-configuration.
 *
 */
mepa_rc mepa_macsec_dbg_reconfig(struct mepa_device *dev,
                                 const mepa_port_no_t port_no);
#endif

/** Configure MACsec Update sequence number.
 *
 */
mepa_rc mepa_macsec_dbg_update_seq_set(struct mepa_device *dev,
                                       const mepa_macsec_port_t port,
                                       const mepa_macsec_sci_t *const sci,
                                       uint16_t an,
                                       mepa_bool_t egr,
                                       const mepa_bool_t disable);


// ***************************************************************************
//
//  End of file.
//
// ***************************************************************************


#include <microchip/ethernet/hdr_end.h>
#endif /**< _MEPA_TS_API_H_ */
