// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MACSEC_API_H_
#define _VTSS_MACSEC_API_H_

#include <vtss_phy_api.h>
#include <microchip/ethernet/phy/api/phy_macsec.h>

#define VTSS_MACSEC_10G_MAX_SA MEPA_MACSEC_10G_MAX_SA
#define VTSS_MACSEC_1G_MAX_SA  MEPA_MACSEC_1G_MAX_SA
#define VTSS_MACSEC_SA_PER_SC_MAX  MEPA_MACSEC_SA_PER_SC_MAX
#define VTSS_MACSEC_SA_PER_SC_MIN  MEPA_MACSEC_SA_PER_SC_MIN

#define VTSS_MACSEC_SA_PER_SC MEPA_MACSEC_SA_PER_SC
#ifdef VTSS_CHIP_10G_PHY
#define VTSS_MACSEC_MAX_SA MEPA_MACSEC_MAX_SA
#else
#define VTSS_MACSEC_MAX_SA MEPA_MACSEC_MAX_SA
#endif
#define VTSS_MACSEC_MAX_SA_RX  MEPA_MACSEC_MAX_SA_RX
#define VTSS_MACSEC_MAX_SA_TX  MEPA_MACSEC_MAX_SA_TX
#define VTSS_MACSEC_MAX_SC_RX  MEPA_MACSEC_MAX_SC_RX
#define VTSS_MACSEC_MAX_SC_TX  MEPA_MACSEC_MAX_SC_TX
#define VTSS_MACSEC_MAX_SECY   MEPA_MACSEC_MAX_SECY

#define VTSS_MAC_BLOCK_MTU_MAX MEPA_MAC_BLOCK_MTU_MAX
#ifdef __cplusplus
extern "C" {
#endif
/**
 * \file
 * \brief IEEE 802.1AE MacSec API.

    This API provides an management interface to SecY entities, described on
    clause 10 of 802.1AE, (figure 10-6 gives an overview) including all
    components needed by an KaY entity (KeySec application).

    This includes:

    SecY         As defined by the 802.1AE standard, a SecY is the entity that
                 operates the MACsec protocol on a network port (Phy in this
                 context).  There may be zero or more SecY instances on any
                 physical port.  A SecY instance is associated with an Virtual
                 Port.  A SecY contains one transmit SC and zero or more receive
                 SC's. There is a receive SC for each peer entity on the LAN who
                 is a member of the connectivity association (CA). SecY's are
                 identified by their SCI (MAC, Virtual Port).

    SC           A Secure Channel (SC) represents a security relationship from
                 one member of a CA to the others. Each SC has a sequence of
                 SA's allowing for replacement of cryptographic keys without
                 terminating the SC. Each SC has at most 4 active SA's, the SA
                 within an SC is identified by its association number.  Each
                 receive SC is identified by it's SCI value in the SecTAG.
                 Receive SC's are instantiated by the Key Agreement component
                 when a remote peer joins the CA.  Transmit SC's are
                 instantiated in the same operation as when a SecY is
                 instantiated and is destroyed only when the SecY is destroyed.

    SA           SA's contain cryptographic keying material used for MACsec
                 protection and validation operations. SA's are periodically
                 updated from the MACsec Manager's KaY component. An SA is
                 identified by the SC it belongs to and its association number
                 (AN).

    Common Port: An instance of the MAC Internal Sublayer Service used by the SecY 
                 to provide transmission and reception of frames for both the controlled 
                 and uncontrolled ports.

    Controlled Port:  
                 The access point used to provide the secure MAC Service to a client 
                 of a SecY. In other words the en/decrypting port.

    Uncontrolled Port: 
                 The access point used to provide the insecure MAC Service to a client 
                 of a SecY. Typically used for EAPOL frames.


    Tag and header bypassing
    ========================

    Additionally the API provide support for external-virtual ports (port
    virtalization done outside the SECtag). This includes protecting streams
    which are encapsulated in VLAN-tag, double VLAN tag and MPLS tunnels. This
    is an extension to what is defined in IEEE 802.1AE.

    As an example consider the following frame:

      +-------------------------------+
      | DA | SA | VLAN=1000 | PAYLOAD |
      +-------------------------------+

    If this frame is transmitted on a traditional MACsec PHY, the SECtag will be
    injected directly after source MAC address. The resulting frame will look
    like this:

      +----------------------------------------------+
      | DA | SA | SECtag | VLAN=1000 | PAYLOAD | ICV |
      +----------------------------------------------+

    By using the tag and header bypassing features available in VTSS MACsec
    capable PHYs, the frames can be associated with a virtual port by setting up
    matching rules. This virtual port can be configured to skip certain TAGs in
    the MACsec processing. In this case we could configure a rule to match
    traffic on VLAN 1000, and associate this with a virtual MACsec port. This
    MACsec port can now be configured to skip the VLAN tag in its MACsec
    processing.

    If this is done, the previous frame would look like the following when it has
    been transmitted on the MACsec aware PHY.

      +----------------------------------------------+
      | DA | SA | VLAN=1000 | SECtag | PAYLOAD | ICV |
      +----------------------------------------------+

    Here the VLAN tag is not encrypted, and it is not included in the ICV
    checksum. If this frame is received on the PHY, it will find the VLAN tag,
    parse it and use this information to associate the MACsec frame with the
    given virtual MACsec port.

 */

/*--------------------------------------------------------------------*/
/* Data types.                                                        */
/*--------------------------------------------------------------------*/

/** \brief Values of the CipherSuite control */
#define VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128 MEPA_MACSEC_CIPHER_SUITE_GCM_AES_128 /**< GCM-AES-128 cipher suite */
#define VTSS_MACSEC_CIPHER_SUITE_GCM_AES_256  MEPA_MACSEC_CIPHER_SUITE_GCM_AES_256 /**< GCM-AES-256 cipher suite. */
#define VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 /**< GCM-AES-XPN_128 cipher suite for XPN mode. */
#define VTSS_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256 MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256 /**< GCM-AES-XPN_256 cipher suite for XPN mode. */

#define VTSS_MACSEC_CP_RULES   (8 + 16 + 2) /**< DMAC + ETYPE + DMAC/ETYPE */

/** \brief TBD */
#define VTSS_MACSEC_VALIDATE_FRAMES_DISABLED MEPA_MACSEC_VALIDATE_FRAMES_DISABLED /**< Do not perform integrity check */
#define VTSS_MACSEC_VALIDATE_FRAMES_CHECK MEPA_MACSEC_VALIDATE_FRAMES_CHECK /**< Perform integrity check do not drop failed frames */
#define VTSS_MACSEC_VALIDATE_FRAMES_STRICT MEPA_MACSEC_VALIDATE_FRAMES_STRICT /**< Perform integrity check and drop failed frames */

typedef mepa_port_no_t vtss_mepa_port_no_t;
typedef mepa_macsec_vport_id_t vtss_macsec_vport_id_t;   /**< Virtual port Id. Corresponds to a SecY.  */
typedef mepa_macsec_service_id_t vtss_macsec_service_id_t; /**< Encapsulation service id */
typedef mepa_macsec_port_t vtss_macsec_port_t;
typedef mepa_validate_frames_t vtss_validate_frames_t;
typedef mepa_macsec_ciphersuite_t vtss_macsec_ciphersuite_t;
typedef mepa_macsec_secy_conf_t vtss_macsec_secy_conf_t;
typedef mepa_macsec_pkt_num_t vtss_macsec_pkt_num_t;
typedef mepa_macsec_salt_t vtss_macsec_salt_t;
typedef mepa_macsec_sak_t vtss_macsec_sak_t;
typedef mepa_macsec_sci_t vtss_macsec_sci_t;
typedef mepa_macsec_ssci_t vtss_macsec_ssci_t;
typedef mepa_macsec_port_status_t vtss_macsec_port_status_t;
typedef mepa_macsec_secy_port_status_t vtss_macsec_secy_port_status_t;
typedef mepa_macsec_tx_sc_status_t vtss_macsec_tx_sc_status_t;
typedef mepa_macsec_rx_sc_status_t vtss_macsec_rx_sc_status_t;
typedef mepa_macsec_tx_sa_pn_status_t vtss_macsec_tx_sa_pn_status_t;
typedef mepa_macsec_tx_sa_status_t vtss_macsec_tx_sa_status_t;
typedef mepa_macsec_rx_sa_pn_status_t vtss_macsec_rx_sa_pn_status_t;
typedef mepa_macsec_rx_sa_status_t vtss_macsec_rx_sa_status_t;
typedef mepa_macsec_rx_sc_conf_t vtss_macsec_rx_sc_conf_t;
typedef mepa_macsec_tx_sc_conf_t vtss_macsec_tx_sc_conf_t;
typedef mepa_macsec_lmac_conf_t vtss_macsec_lmac_conf_t;
typedef mepa_macsec_hmac_conf_t vtss_macsec_hmac_conf_t;
typedef mepa_macsec_mac_conf_t vtss_macsec_mac_conf_t;
typedef mepa_macsec_init_bypass_t vtss_macsec_init_bypass_t;
typedef mepa_macsec_init_t vtss_macsec_init_t;

#define MACSEC_INIT_BYPASS_NONE    VTSS_MACSEC_INIT_BYPASS_NONE    /**< Backward compatibility */
#define MACSEC_INIT_BYPASS_ENABLE  VTSS_MACSEC_INIT_BYPASS_ENABLE  /**< Backward compatibility */
#define MACSEC_INIT_BYPASS_DISABLE VTSS_MACSEC_INIT_BYPASS_DISABLE /**< Backward compatibility */

#define VTSS_MACSEC_INIT_BYPASS_NONE MEPA_MACSEC_INIT_BYPASS_NONE
#define VTSS_MACSEC_INIT_BYPASS_ENABLE MEPA_MACSEC_INIT_BYPASS_ENABLE
#define VTSS_MACSEC_INIT_BYPASS_DISABLE MEPA_MACSEC_INIT_BYPASS_DISABLE

typedef mepa_macsec_mtu_t vtss_macsec_mtu_t;

/*--------------------------------------------------------------------*/
/* MACsec Initialization                                              */
/*--------------------------------------------------------------------*/

/** \brief Initilize the MACsec block
 *
 *  When the MACsec block is disabled all frames are passed through unchanged.  This is the default state after Phy initilization.
 *  When the MACsec block is enabled,  all frames are dropped until SecY (CA) is created.
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port_no   [IN]     VTSS-API port no.
 * \param init      [IN]     Initilize configuration.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_init_set(const vtss_inst_t                inst,
                             const vtss_port_no_t             port_no,
                             const vtss_macsec_init_t         *const init);

/** \brief Get the MACsec block init configuration
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port_no   [IN]     VTSS-API port no.
 * \param init      [OUT]    Initilize configuration.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_init_get(const vtss_inst_t                inst,
                             const vtss_port_no_t             port_no,
                             vtss_macsec_init_t               *const init);


/*--------------------------------------------------------------------*/
/* MAC Security Entity (SecY) management                              */
/*--------------------------------------------------------------------*/

/** \brief Create a SecY entity of a MACsec port
 *
 * The entity is created with given parameters.
 * NOTE: The controlled port is disabled by default and must be enabled before normal processing.
 * NOTE: Classification pattern must be configured to classify traffic to a SecY instance
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 * \param conf      [IN]     SecY configuration.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_secy_conf_add(const vtss_inst_t                 inst,
                                  const vtss_macsec_port_t          port,
                                  const vtss_macsec_secy_conf_t     *const conf);

/** \brief Create a SecY entity of a MACsec port
 *
 * The SecY is updated with given parameters.
 * Note that the SecY must exist
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 * \param conf      [IN]     SecY configuration.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 *
 * Note: SecY update with new parameters i.e. Replay Window size etc, it will
 *       update newly create SA's only. Existing parameters i.e. Next PN and Lower PN
 *       will not change. Tx/Rx SA Status Next PN and Lowest PN shows different
 *       as compare with existing Tx/Rx SA Status.
 *
 */
vtss_rc vtss_macsec_secy_conf_update(const vtss_inst_t                 inst,
                                     const vtss_macsec_port_t          port,
                                     const vtss_macsec_secy_conf_t     *const conf);


/** \brief Get the SecY entry.
 *
 * \param inst       [IN]     VTSS-API instance.
 * \param port       [IN]     MACsec port.
 * \param conf       [OUT]    SecY configuration.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if SecY does not exist.
 */
vtss_rc vtss_macsec_secy_conf_get(const vtss_inst_t         inst,
                                  const vtss_macsec_port_t  port,
                                  vtss_macsec_secy_conf_t   *const conf);

/** \brief Delete the SecY and the associated SCs/SAs
 *
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_secy_conf_del(const vtss_inst_t                 inst,
                                  const vtss_macsec_port_t          port);



/** \brief Enable/Disable the SecY's controlled (secure) port.
 *
 * The controlled port is disabled by default.
 *
 * \param inst       [IN]     VTSS-API instance.
 * \param port       [IN]     MACsec port.
 * \param enable     [IN]     Forwarding state of the port.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_secy_controlled_set(const vtss_inst_t         inst,
                                        const vtss_macsec_port_t  port,
                                        const BOOL                enable);

/** \brief Get the state config of the controlled (secure) port.
 *
 *
 * \param inst       [IN]     VTSS-API instance.
 * \param port       [IN]     MACsec port.
 * \param enable     [OUT]    Forwarding state of the port.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_secy_controlled_get(const vtss_inst_t         inst,
                                        const vtss_macsec_port_t  port,
                                        BOOL                      *const enable);

/** \brief Get status from a SecY port, controlled, uncontrolled or common.
 *
 * \param inst        [IN]     VTSS-API instance.
 * \param port        [IN]     MACsec port.
 * \param status      [OUT]    SecY port status
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_secy_port_status_get(const vtss_inst_t                 inst,
                                         const vtss_macsec_port_t          port,
                                         vtss_macsec_secy_port_status_t    *const status);


/** \brief Browse through available macsec ports (secy's) on a physical port
 *  Use NULL pointer to get the first port and use found ports as a search port in the next round.
 *
 * \param inst                [IN]     VTSS-API instance.
 * \param port_no             [IN]     VTSS-API port no.
 * \param search_macsec_port  [IN]     MACsec port to search for
 * \param found_macsec_port   [OUT]    MACsec port that comes next
 *
 * \return VTSS_RC_OK when port is found; VTSS_RC_ERROR if parameters are invalid or if the search port is not found
 */
vtss_rc vtss_macsec_port_get_next(const vtss_inst_t              inst,
                                  const vtss_port_no_t           port_no,
                                  const vtss_macsec_port_t       *const search_macsec_port,
                                  vtss_macsec_port_t             *const found_macsec_port);

/*--------------------------------------------------------------------*/
/* Receive Secure Channel (SC) management                             */
/*--------------------------------------------------------------------*/

/** \brief Create an Rx SC object inside of the SecY.
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 * \param sci       [IN]     The peer rx SCI.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or resources exhausted.
 */

vtss_rc vtss_macsec_rx_sc_add(const vtss_inst_t           inst,
                              const vtss_macsec_port_t    port,
                              const vtss_macsec_sci_t     *const sci);

/** \brief Instead of inheriting the configuration from the SecY the Rx SC can use its own configuration.  
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 * \param sci       [IN]     The peer rx SCI.
 * \param conf      [IN]     Configuration which applies to this SC.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or resources exhausted.
 *
 * Note: RxSC update with new parameters i.e. Replay Window size etc, it will
 *       update newly create SA's only. Existing parameters i.e. Next PN and Lower PN
 *       will not change. Rx SA Status Next PN and Lowest PN shows different
 *       as compare with existing Rx SA Status.
 *
 */

vtss_rc vtss_macsec_rx_sc_update(const vtss_inst_t              inst,
                                 const vtss_macsec_port_t       port,
                                 const vtss_macsec_sci_t        *const sci,
                                 const vtss_macsec_rx_sc_conf_t *const conf);

/** \brief Get the configuration of the SC.  
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 * \param sci       [IN]     The peer rx SCI.
 * \param conf      [OUT]    Configuration which applies to this SC.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or resources exhausted.
 */

vtss_rc vtss_macsec_rx_sc_get_conf(const vtss_inst_t              inst,
                                   const vtss_macsec_port_t       port,
                                   const vtss_macsec_sci_t        *const sci,
                                   vtss_macsec_rx_sc_conf_t       *const conf);


/** \brief Browse through the Rx SCs inside of the SecY.
 *
 * \param inst          [IN]     VTSS-API instance.
 * \param port          [IN]     MACsec port.
 * \param search_sci    [IN]     SCI to start the search. The next SCI will be returned.
                                 NULL pointer finds the first SCI.
 * \param found_sci     [OUT]    The next SCI.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or next SCI not found.
 */

vtss_rc vtss_macsec_rx_sc_get_next(const vtss_inst_t              inst,
                                   const vtss_macsec_port_t       port,
                                   const vtss_macsec_sci_t        *const search_sci,
                                   vtss_macsec_sci_t              *const found_sci);

/** \brief Delete the Rx SC and the associated SAs
 *
 * \param inst       [IN]     VTSS-API instance.
 * \param port       [IN]     MACsec port.
 * \param sci        [IN]     SCI to delete.

 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or SCI not found.
 */
vtss_rc vtss_macsec_rx_sc_del(const vtss_inst_t           inst,
                              const vtss_macsec_port_t    port,
                              const vtss_macsec_sci_t     *const sci);

/** \brief Rx SC status info
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port         [IN]     MACsec port.
 * \param sci          [IN]     SCI of the peer.
 * \param status       [OUT]    SC status
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_rx_sc_status_get(const vtss_inst_t               inst,
                                     const vtss_macsec_port_t        port,
                                     const vtss_macsec_sci_t         *const sci,
                                     vtss_macsec_rx_sc_status_t      *const status);


/*--------------------------------------------------------------------*/
/* Transmit Secure Channel (SC) management                            */
/*--------------------------------------------------------------------*/

/** \brief Create an Tx SC object inside of the SecY.  One TxSC is supported for each SecY.
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or resources exhausted.
 */
vtss_rc vtss_macsec_tx_sc_set(const vtss_inst_t           inst,
                              const vtss_macsec_port_t    port);

/** \brief Instead of inheriting the configuration from the SecY the Tx SC can use its own configuration.  
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 * \param conf      [IN]     Configuration which applies to this SC.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or resources exhausted.
 *
 * Note: TxSC update with new parameters i.e. Replay Window size etc, it will
 *       update newly create SA's only. Existing parameters i.e. Next PN and Lower PN
 *       will not change. Tx SA Status Next PN and Lowest PN shows different
 *       as compare with existing Tx SA Status.
 *
 */
vtss_rc vtss_macsec_tx_sc_update(const vtss_inst_t              inst,
                                 const vtss_macsec_port_t       port,
                                 const vtss_macsec_tx_sc_conf_t *const conf);


/** \brief Get the SC configuration  
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 * \param conf      [OUT]    Configuration which applies to this SC.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or resources exhausted.
 */
vtss_rc vtss_macsec_tx_sc_get_conf(const vtss_inst_t              inst,
                                   const vtss_macsec_port_t       port,
                                   vtss_macsec_tx_sc_conf_t       *const conf);

/** \brief Delete the Tx SC object and the associated SAs
 *
 * \param inst       [IN]     VTSS-API instance.
 * \param port       [IN]     MACsec port.

 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_tx_sc_del(const vtss_inst_t           inst,
                              const vtss_macsec_port_t    port);


/** \brief Tx SC status
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port         [IN]     MACsec port.
 * \param status       [OUT]    SC status
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_tx_sc_status_get(const vtss_inst_t           inst,
                                     const vtss_macsec_port_t    port,
                                     vtss_macsec_tx_sc_status_t  *const status);


/*--------------------------------------------------------------------*/
/* Receive Secure Association (SA) management                         */
/*--------------------------------------------------------------------*/

/** \brief Create an Rx SA which is associated with an SC within the SecY.
 *         This SA is not enabled until vtss_macsec_rx_sa_activate() is performed.
 *
 * \param inst        [IN]     VTSS-API instance.
 * \param port        [IN]     MACsec port.
 * \param sci         [IN]     SCI of the peer.
 * \param an          [IN]     Association number, 0-3
 * \param lowest_pn   [IN]     Lowest acceptable packet number.
 * \param sak         [IN]     The 128 or 256 bit Secure Association Key and the calculated hash value.

 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or resources exhausted.
 */
vtss_rc vtss_macsec_rx_sa_set(const vtss_inst_t             inst,
                              const vtss_macsec_port_t      port,
                              const vtss_macsec_sci_t       *const sci,
                              const u16                     an,
                              const u32                     lowest_pn,
                              const vtss_macsec_sak_t       *const sak);

/** \brief Get the Rx SA configuration of the active SA.

 *
 * \param inst       [IN]     VTSS-API instance.
 * \param port       [IN]     MACsec port.
 * \param sci        [IN]     SCI of the peer.
 * \param an         [IN]     Association number, 0-3
 * \param lowest_pn  [OUT]    Lowest acceptable packet number.
 * \param sak        [OUT]    The 128 or 256 bit Secure Association Key and the hash value.
 * \param active     [OUT]    Flag that tells if this SA is activated or not.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 *
 * Note: If SA was created before any change on parameter like Replay Widow etc. Lowest PN may appear to be consistent with newly
 *       updated value, but the actual value will be according to the SA's creation time. One has to subtract the change in the
 *       the value obtained from API to get the actual value. Updating parameters like Replay Window doesn't change the older SA's.
 *
 */
vtss_rc vtss_macsec_rx_sa_get(const vtss_inst_t             inst,
                              const vtss_macsec_port_t      port,
                              const vtss_macsec_sci_t       *const sci,
                              const u16                     an,
                              u32                           *const lowest_pn,
                              vtss_macsec_sak_t             *const sak,
                              BOOL                          *const active);


/** \brief Activate the SA associated with the AN.
           The reception switches from a previous SA to the SA identified by the AN.
           Note that the reception using the new SA does not necessarily begin immediately.
 *
 * \param inst   [IN]     VTSS-API instance.
 * \param port   [IN]     MACsec port.
 * \param sci    [IN]     SCI of the peer.
 * \param an     [IN]     Association number, 0-3
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_rx_sa_activate(const vtss_inst_t            inst,
                                   const vtss_macsec_port_t      port,
                                   const vtss_macsec_sci_t       *const sci,
                                   const u16                     an);

/** \brief This function disables Rx SA identified by an. Frames still in the pipeline are not discarded.

 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param sci             [IN]     SCI of the peer.
 * \param an              [IN]     Association number, 0-3
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid, or if the AN has not previously been set.
 */
vtss_rc vtss_macsec_rx_sa_disable(const vtss_inst_t         inst,
                                  const vtss_macsec_port_t  port,
                                  const vtss_macsec_sci_t   *const sci,
                                  const u16                 an);


/** \brief This function deletes Rx SA object identified by an. The Rx SA must be disabled before deleted.

 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param sci             [IN]     SCI of the peer.
 * \param an              [IN]     Association number, 0-3
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid, or if the AN has not previously been set.
 */
vtss_rc vtss_macsec_rx_sa_del(const vtss_inst_t         inst,
                              const vtss_macsec_port_t  port,
                              const vtss_macsec_sci_t   *const sci,
                              const u16                 an);


/** \brief Set (update) the packet number (pn) value to value in lowest_pn
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN]     MACsec port.
 * \param sci       [IN]     SCI of the peer.
 * \param an        [IN]     Association number, 0-3
 * \param lowest_pn [IN]     Lowest accepted packet number
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_rx_sa_lowest_pn_update(const vtss_inst_t            inst,
                                           const vtss_macsec_port_t     port,
                                           const vtss_macsec_sci_t      *const sci,
                                           const u16                    an,
                                           const u32                    lowest_pn);

/** \brief Rx SA status
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port         [IN]     MACsec port.
 * \param sci          [IN]     SCI of the peer.
 * \param an           [IN]     Association number, 0-3
 * \param status       [OUT]    SC status
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 * Note: If SA was created before any change on parameter like Replay Widow etc. Lowest PN may appear to be consistent with newly
 *       updated value, but the actual value will be according to the SA's creation time. One has to subtract the change in the
 *       the value obtained from API to get the actual value. Updating parameters like Replay Window doesn't change the older SA's.
 */

vtss_rc vtss_macsec_rx_sa_status_get(const vtss_inst_t           inst,
                                     const vtss_macsec_port_t    port,
                                     const vtss_macsec_sci_t     *const sci,
                                     const u16                   an,
                                     vtss_macsec_rx_sa_status_t  *const status);

/*--------------------------------------------------------------------*/
/* For XPN supported devices                                          */
/* Receive Secure Association (SA) management                         */
/*--------------------------------------------------------------------*/

/** \brief Create an Rx SA which is associated with an SC within the SecY.
 *
 * \param inst        [IN]     VTSS-API instance.
 * \param port        [IN]     MACsec port.
 * \param sci         [IN]     SCI of the peer.
 * \param an          [IN]     Association number, 0-3
 * \param lowest_pn   [IN]     Lowest acceptable packet number in 32-bit or 64-bit size.
 * \param sak         [IN]     The 128 or 256 bit Secure Association Key and the calculated hash value.
 * \param ssci        [IN]     Short SCI associated with this peer. Used for XPN only.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid or resources exhausted.
 */
vtss_rc vtss_macsec_rx_seca_set(const vtss_inst_t             inst,
                                const vtss_macsec_port_t      port,
                                const vtss_macsec_sci_t       *const sci,
                                const u16                     an,
                                const vtss_macsec_pkt_num_t   lowest_pn,
                                const vtss_macsec_sak_t       *const sak,
                                const vtss_macsec_ssci_t      *const ssci);

/** \brief Get the Rx SA configuration of the active SA.
 *
 * \param inst       [IN]     VTSS-API instance.
 * \param port       [IN]     MACsec port.
 * \param sci        [IN]     SCI of the peer.
 * \param an         [IN]     Association number, 0-3
 * \param lowest_pn  [OUT]    Lowest acceptable packet number in 32-bit or 64-bit size.
 * \param sak        [OUT]    The 128 or 256 bit Secure Association Key and the hash value.
 * \param active     [OUT]    Flag that tells if this SA is activated or not.
 * \param ssci       [OUT]    Short SCI associated with this peer.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_rx_seca_get(const vtss_inst_t             inst,
                                const vtss_macsec_port_t      port,
                                const vtss_macsec_sci_t       *const sci,
                                const u16                     an,
                                vtss_macsec_pkt_num_t         *const lowest_pn,
                                vtss_macsec_sak_t             *const sak,
                                BOOL                          *const active,
                                vtss_macsec_ssci_t            *const ssci);



/** \brief Update the lowest_pn packet number in 64-bit or 32-bit for Rx SA.
 *
 * \param inst          [IN]     VTSS-API instance.
 * \param port          [IN]     MACsec port.
 * \param sci           [IN]     SCI of the peer.
 * \param an            [IN]     Association number, 0-3
 * \param lowest_pn     [IN]     Lowest accepted packet number of 32-bit or 64-bit size
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_rx_seca_lowest_pn_update(const vtss_inst_t            inst,
                                             const vtss_macsec_port_t     port,
                                             const vtss_macsec_sci_t      *const sci,
                                             const u16                    an,
                                             const vtss_macsec_pkt_num_t  lowest_pn);

/*--------------------------------------------------------------------*/
/* Transmit Secure Association (SA) management                        */
/*--------------------------------------------------------------------*/

/** \brief Create an Tx SA which is associated with the Tx SC within the SecY.
 *         This SA is not in use until vtss_macsec_tx_sa_activate() is performed.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param an              [IN]     Association number, 0-3
 * \param next_pn         [IN]     The packet number of the first packet sent using the new SA (1 or greater)
 * \param confidentiality [IN]     If true, packets are encrypted, otherwise integrity protected only.
 * \param sak             [IN]     The 128 or 256 bit Secure Association Key and the calculated hash value.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 *
 * Note: If SA was created before any change in parameters like Replay Widow etc. Lowest PN may appear to be consistent with newly
 *       updated value, but the actual value will be according to the SA's creation time. One has to subtract the change in the
 *       the value obtained from API to get the actual value. Updating parameters like Replay Window doesn't change the older SA's.
 *
 */
vtss_rc vtss_macsec_tx_sa_set(const vtss_inst_t              inst,
                              const vtss_macsec_port_t       port,
                              const u16                      an,
                              const u32                      next_pn,
                              const BOOL                     confidentiality,
                              const vtss_macsec_sak_t        *const sak);


/** \brief Get the  Tx SA configuration.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param an              [IN]     Association number, 0-3
 * \param next_pn         [OUT]    The packet number of the first packet sent using the new SA (1 or greater)
 * \param confidentiality [OUT]    If true, packets are encrypted, otherwise integrity protected only.
 * \param sak             [OUT]    The 128 or 256 bit Secure Association Key and the hash value.
 * \param active          [OUT]    Flag that tells if this SA is activated or not.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid, or if the AN has not previously been set.
 */
vtss_rc vtss_macsec_tx_sa_get(const vtss_inst_t              inst,
                              const vtss_macsec_port_t       port,
                              const u16                      an,
                              u32                            *const next_pn,
                              BOOL                           *const confidentiality,
                              vtss_macsec_sak_t              *const sak,
                              BOOL                           *const active);


/** \brief This function switches transmission from a previous Tx SA to the Tx SA identified by an.
           Transmission using the new SA is in effect immediately.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param an              [IN]     Association number, 0-3
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid, or if the AN has not previously been set.
 */
vtss_rc vtss_macsec_tx_sa_activate(const vtss_inst_t         inst,
                                   const vtss_macsec_port_t  port,
                                   const u16                 an);


/** \brief This function disables Tx SA identified by an. Frames still in the pipeline are not discarded.

 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param an              [IN]     Association number, 0-3
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid, or if the AN has not previously been set.
 */
vtss_rc vtss_macsec_tx_sa_disable(const vtss_inst_t         inst,
                                  const vtss_macsec_port_t  port,
                                  const u16                 an);


/** \brief This function deletes Tx SA object identified by an. The Tx SA must be disabled before deleted.

 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param an              [IN]     Association number, 0-3
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid, or if the AN has not previously been set.
 */
vtss_rc vtss_macsec_tx_sa_del(const vtss_inst_t         inst,
                              const vtss_macsec_port_t  port,
                              const u16                 an);

/** \brief Tx SA status
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port         [IN]     MACsec port.
 * \param an           [IN]     Association number, 0-3
 * \param status       [OUT]    SC status
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 * Note: If SA was created before any change on parameter like Replay Widow etc. Lowest PN may appear to be consistent with newly
 *       updated value, but the actual value will be according to the SA's creation time. One has to subtract the change in the
 *       the value obtained from API to get the actual value. Updating parameters like Replay Window doesn't change the older SA's.
 */
vtss_rc vtss_macsec_tx_sa_status_get(const vtss_inst_t           inst,
                                     const vtss_macsec_port_t    port,
                                     const u16                   an,
                                     vtss_macsec_tx_sa_status_t  *const status);

/*--------------------------------------------------------------------*/
/* For XPN supported devices                                          */
/* Transmit Secure Association (SA) management                        */
/*--------------------------------------------------------------------*/

/** \brief Create an Tx SA which is associated with the Tx SC within the SecY.
 *         This SA is not in use until vtss_macsec_tx_sa_activate() is performed.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param an              [IN]     Association number, 0-3
 * \param next_pn         [IN]     The packet number of the first packet sent using the new SA (1 or greater).
 * \param confidentiality [IN]     If true, packets are encrypted, otherwise integrity protected only.
 * \param sak             [IN]     The 128 or 256 bit Secure Association Key and the calculated hash value.
 * \param ssci            [IN]     Short SCI associated with this peer. Used for XPN only.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_tx_seca_set(const vtss_inst_t              inst,
                                const vtss_macsec_port_t       port,
                                const u16                      an,
                                const vtss_macsec_pkt_num_t    next_pn,
                                const BOOL                     confidentiality,
                                const vtss_macsec_sak_t        *const sak,
                                const vtss_macsec_ssci_t       *const ssci);

/** \brief Get the Tx SA configuration supporting 64-bit and 32-bit PN.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param an              [IN]     Association number, 0-3
 * \param next_pn         [OUT]    The packet number of the first packet sent using the new SA (1 or greater)
 * \param confidentiality [OUT]    If true, packets are encrypted, otherwise integrity protected only.
 * \param sak             [OUT]    The 128 or 256 bit Secure Association Key and the hash value.
 * \param active          [OUT]    Flag that tells if this SA is activated or not.
 * \param ssci            [OUT]     Short SCI associated with this peer. Used for XPN only. 
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid, or if the AN has not previously been set.
 */
vtss_rc vtss_macsec_tx_seca_get(const vtss_inst_t              inst,
                                const vtss_macsec_port_t       port,
                                const u16                      an,
                                vtss_macsec_pkt_num_t          *const next_pn,
                                BOOL                           *const confidentiality,
                                vtss_macsec_sak_t              *const sak,
                                BOOL                           *const active,
                                vtss_macsec_ssci_t       *const ssci);


/*--------------------------------------------------------------------*/
/* SecY Counters                                                      */
/*--------------------------------------------------------------------*/
typedef mepa_macsec_common_counters_t vtss_macsec_common_counters_t;
typedef mepa_macsec_uncontrolled_counters_t vtss_macsec_uncontrolled_counters_t;
typedef mepa_macsec_secy_port_counters_t vtss_macsec_secy_port_counters_t;
typedef mepa_macsec_secy_counters_t vtss_macsec_secy_counters_t;

#define VTSS_MACSEC_CAP_GCM_AES_128       MEPA_MACSEC_CAP_GCM_AES_128
#define VTSS_MACSEC_CAP_GCM_AES_256       MEPA_MACSEC_CAP_GCM_AES_256
#define VTSS_MACSEC_CAP_GCM_AES_XPN_128   MEPA_MACSEC_CAP_GCM_AES_XPN_128
#define VTSS_MACSEC_CAP_GCM_AES_XPN_256   MEPA_MACSEC_CAP_GCM_AES_XPN_256

typedef mepa_macsec_secy_cap_t vtss_macsec_secy_cap_t;

/** \brief Get counters from a SecY controlled (802-1AE) port.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     MACsec port.
 * \param counters        [OUT]    Port counters
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */

vtss_rc vtss_macsec_controlled_counters_get(const vtss_inst_t                  inst,
                                            const vtss_macsec_port_t           port,
                                            vtss_macsec_secy_port_counters_t  *const counters);

/** \brief Get counters from a physical uncontrolled (802-1AE) port.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port_no         [IN]     VTSS-API port no.
 * \param counters        [OUT]    Global uncontrolled port counters
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_uncontrolled_counters_get(const vtss_inst_t                   inst,
                                              const vtss_port_no_t                port_no,
                                              vtss_macsec_uncontrolled_counters_t *const counters);

/** \brief Get counters from a physical common (802-1AE) port.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port_no         [IN]     VTSS-API port no.
 * \param counters        [OUT]    Global common port counters
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_common_counters_get(const vtss_inst_t               inst,
                                        const vtss_port_no_t            port_no,
                                        vtss_macsec_common_counters_t   *const counters);


/** \brief Get the capabilities of the SecY as define by 802.1AE.
 *
 * \param inst        [IN]     VTSS-API instance.
 * \param port_no     [IN]     VTSS-API port no.
 * \param cap         [OUT]    SecY capabilities
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_secy_cap_get(const vtss_inst_t             inst,
                                 const vtss_port_no_t          port_no,
                                 vtss_macsec_secy_cap_t        *const cap);


/** \brief SecY counters
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port            [IN]     VTSS-API port no.
 * \param counters        [OUT]    SecY counters 
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_secy_counters_get(const vtss_inst_t             inst,
                                      const vtss_macsec_port_t      port,
                                      vtss_macsec_secy_counters_t   *const counters);


/** \brief MacSec counter update.  Keep the API internal SW counters updated. 
 *  Should be called periodically, but no special requirement to interval (the chip counters are 40bit).
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port_no         [IN]     VTSS-API port no.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_counters_update(const vtss_inst_t     inst,
                                    const vtss_port_no_t  port_no);


/** \brief MacSec counter clear.  Clear all counters.
 *
 * \param inst            [IN]     VTSS-API instance.
 * \param port_no         [IN]     VTSS-API port no.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_counters_clear(const vtss_inst_t     inst,
                                   const vtss_port_no_t  port_no);

/*--------------------------------------------------------------------*/
/* SC Counters                                                        */
/*--------------------------------------------------------------------*/

typedef mepa_macsec_rx_sc_counters_t vtss_macsec_rx_sc_counters_t;
typedef mepa_macsec_tx_sc_counters_t vtss_macsec_tx_sc_counters_t;

/** \brief RX SC counters
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port         [IN]     MacSec port.
 * \param sci          [IN]     SCI of the peer.
 * \param counters     [OUT]    SecY counters
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid
 */
vtss_rc vtss_macsec_rx_sc_counters_get(const vtss_inst_t               inst,
                                       const vtss_macsec_port_t        port,
                                       const vtss_macsec_sci_t         *const sci,
                                       vtss_macsec_rx_sc_counters_t    *const counters);

/** \brief Rx SC counters
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port         [IN]     MacSec port.
 * \param counters     [OUT]    SC counters
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_tx_sc_counters_get(const vtss_inst_t               inst,
                                       const vtss_macsec_port_t        port,
                                       vtss_macsec_tx_sc_counters_t    *const counters);


/*--------------------------------------------------------------------*/
/* SA Counters                                                        */
/*--------------------------------------------------------------------*/
typedef mepa_macsec_tx_sa_counters_t vtss_macsec_tx_sa_counters_t;
typedef mepa_macsec_rx_sa_counters_t vtss_macsec_rx_sa_counters_t;

/** \brief Tx SA counters
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port         [IN]     MacSec port.
 * \param an           [IN]     Association number, 0-3
 * \param counters     [OUT]    SA counters
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_tx_sa_counters_get(const vtss_inst_t               inst,
                                       const vtss_macsec_port_t        port,
                                       const u16                       an,
                                       vtss_macsec_tx_sa_counters_t    *const counters);


/** \brief Tx SA counters
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port         [IN]     MacSec port.
 * \param sci          [IN]     SCI of the peer.
 * \param an           [IN]     Association number, 0-3
 * \param counters     [OUT]    SA counters
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_rx_sa_counters_get(const vtss_inst_t            inst,
                                       const vtss_macsec_port_t     port,
                                       const vtss_macsec_sci_t      *const sci,
                                       const u16                    an,
                                       vtss_macsec_rx_sa_counters_t *const counters);

/*--------------------------------------------------------------------*/
/* VP / Uncontrolled classification                                   */
/*--------------------------------------------------------------------*/
#define VTSS_MACSEC_MATCH_DISABLE        MEPA_MACSEC_MATCH_DISABLE
#define VTSS_MACSEC_MATCH_DMAC           MEPA_MACSEC_MATCH_DMAC
#define VTSS_MACSEC_MATCH_ETYPE          MEPA_MACSEC_MATCH_ETYPE
#define VTSS_MACSEC_MATCH_VLAN_ID        MEPA_MACSEC_MATCH_VLAN_ID
#define VTSS_MACSEC_MATCH_VLAN_ID_INNER  MEPA_MACSEC_MATCH_VLAN_ID_INNER
#define VTSS_MACSEC_MATCH_BYPASS_HDR     MEPA_MACSEC_MATCH_BYPASS_HDR
#define VTSS_MACSEC_MATCH_IS_CONTROL     MEPA_MACSEC_MATCH_IS_CONTROL
#define VTSS_MACSEC_MATCH_HAS_VLAN       MEPA_MACSEC_MATCH_HAS_VLAN
#define VTSS_MACSEC_MATCH_HAS_VLAN_INNER MEPA_MACSEC_MATCH_HAS_VLAN_INNER
#define VTSS_MACSEC_MATCH_SMAC           MEPA_MACSEC_MATCH_SMAC

#define VTSS_MACSEC_MATCH_PRIORITY_LOWEST MEPA_MACSEC_MATCH_PRIORITY_LOWEST
#define VTSS_MACSEC_MATCH_PRIORITY_LOW    MEPA_MACSEC_MATCH_PRIORITY_LOW
#define VTSS_MACSEC_MATCH_PRIORITY_MID     MEPA_MACSEC_MATCH_PRIORITY_MID
#define VTSS_MACSEC_MATCH_PRIORITY_HIGH    MEPA_MACSEC_MATCH_PRIORITY_HIGH
#define VTSS_MACSEC_MATCH_PRIORITY_HIGHEST MEPA_MACSEC_MATCH_PRIORITY_HIGHEST

typedef mepa_macsec_control_frame_match_conf_t vtss_macsec_control_frame_match_conf_t;

/** \brief Set the control frame matching rules.
 *  16 rules are supported for ETYPE (8 for 1G Phy).
 *   8 rules are supported for DMACs 
 *   2 rules are supported for ETYPE & DMAC
 * \param inst    [IN]     VTSS-API instance.
 * \param port_no [IN]     VTSS-API port no.
 * \param conf    [IN]     Matching configuration
 * \param rule_id [OUT]    Rule id for getting and deleting.  Can be ignored by passing NULL as a parameter.
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_control_frame_match_conf_set(const vtss_inst_t                             inst,
                                                 const vtss_port_no_t                          port_no,
                                                 const vtss_macsec_control_frame_match_conf_t *const conf,
                                                 u32                                          *const rule_id);

/** \brief Delete a control frame matching rule.
 * \param inst    [IN]     VTSS-API instance.
 * \param port_no [IN]     VTSS-API port no.
 * \param rule_id [IN]     The rule id (retrieved from vtss_macsec_control_frame_match_conf_set()).
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_control_frame_match_conf_del(const vtss_inst_t                             inst,
                                                 const vtss_port_no_t                          port_no,
                                                 const u32                                     rule_id);

/**
 * \brief Get the control frame matching rules.

 * \param inst    [IN]     VTSS-API instance.
 * \param port_no [IN]     VTSS-API port no.
 * \param conf    [OUT]    Matching configuration
 * \param rule_id [IN]     The rule id (retrieved from vtss_macsec_control_frame_match_conf_set()).

 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_control_frame_match_conf_get(const vtss_inst_t                             inst,
                                                 const vtss_port_no_t                          port_no,
                                                 vtss_macsec_control_frame_match_conf_t       *const conf,
                                                 u32                                           rule_id);

typedef mepa_macsec_match_pattern_t vtss_macsec_match_pattern_t;

#define VTSS_MACSEC_MATCH_ACTION_DROP MEPA_MACSEC_MATCH_ACTION_DROP
#define VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT
#define VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT
#define VTSS_MACSEC_MATCH_ACTION_CNT MEPA_MACSEC_MATCH_ACTION_CNT

typedef mepa_macsec_match_action_t vtss_macsec_match_action_t;

#define    VTSS_MACSEC_DIRECTION_INGRESS MEPA_MACSEC_DIRECTION_INGRESS
#define    VTSS_MACSEC_DIRECTION_EGRESS MEPA_MACSEC_DIRECTION_EGRESS
#define    VTSS_MACSEC_DIRECTION_CNT MEPA_MACSEC_DIRECTION_CNT

typedef mepa_macsec_direction_t vtss_macsec_direction_t;

/** \brief Configure the Matching pattern for a given MACsec port, for a given
 * action. Only one action may be associated with each actions. One matching
 * slot will be acquired immediately when this is called for the "DROP" or the
 * "UNCONTROLLED_PORT" actions. When matching pattern is configured for the
 * "CONTROLLED_PORT" action, HW a matching resource will be acquired for every
 * SA added.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 * \param direction [IN] Direction
 * \param action    [IN] Action
 * \param pattern   [IN] Pattern
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid,
 * or if we are out of resources.
 */
vtss_rc vtss_macsec_pattern_set(const vtss_inst_t                  inst,
                                const vtss_macsec_port_t           port,
                                const vtss_macsec_direction_t      direction,
                                const vtss_macsec_match_action_t   action,
                                const vtss_macsec_match_pattern_t *const pattern);

/** \brief   Delete a pattern matching rule.
 *
 * \param inst      [IN]     VTSS-API instance.
 * \param port      [IN] MACsec port.
 * \param direction [IN] Direction
 * \param action    [IN] Action
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_pattern_del(const vtss_inst_t                  inst,
                                const vtss_macsec_port_t           port,
                                const vtss_macsec_direction_t      direction,
                                const vtss_macsec_match_action_t   action);

/** \brief   Get the pattern matching rule.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 * \param direction [IN] Direction
 * \param action    [IN] Action.
 * \param pattern   [OUT] Pattern.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_pattern_get(const vtss_inst_t                  inst,
                                const vtss_macsec_port_t           port,
                                const vtss_macsec_direction_t      direction,
                                const vtss_macsec_match_action_t   action,
                                vtss_macsec_match_pattern_t       *const pattern);

#define VTSS_MACSEC_DEFAULT_ACTION_DROP MEPA_MACSEC_DEFAULT_ACTION_DROP
#define VTSS_MACSEC_DEFAULT_ACTION_BYPASS MEPA_MACSEC_DEFAULT_ACTION_BYPASS

typedef mepa_macsec_default_action_t vtss_macsec_default_action_t;
typedef mepa_macsec_default_action_policy_t vtss_macsec_default_action_policy_t;

/**
 * \brief   Assign default policy
 *
 * \param inst    [IN]  VTSS-API instance.
 * \param port_no [IN]  VTSS-API port no.
 * \param policy  [IN]  Policy
 *
 * \returns VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_default_action_set(const vtss_inst_t                          inst,
                                       const vtss_port_no_t                       port_no,
                                       const vtss_macsec_default_action_policy_t *const policy);

/**
 * \brief   Get default policy
 *
 * \param inst    [IN]  VTSS-API instance.
 * \param port_no [IN]  VTSS-API port no.
 * \param policy  [OUT] Policy
 *
 * \returns VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_default_action_get(const vtss_inst_t                          inst,
                                       const vtss_port_no_t                       port_no,
                                       vtss_macsec_default_action_policy_t       *const policy);


/*--------------------------------------------------------------------*/
/* Header / TAG Bypass                                                */
/*--------------------------------------------------------------------*/

#define VTSS_MACSEC_BYPASS_NONE MEPA_MACSEC_BYPASS_NONE
#define VTSS_MACSEC_BYPASS_TAG MEPA_MACSEC_BYPASS_TAG
#define VTSS_MACSEC_BYPASS_HDR MEPA_MACSEC_BYPASS_HDR

typedef mepa_macsec_bypass_t vtss_macsec_bypass_t;
typedef mepa_macsec_bypass_mode_t vtss_macsec_bypass_mode_t;

#define VTSS_MACSEC_BYPASS_TAG_ZERO MEPA_MACSEC_BYPASS_TAG_ZERO
#define VTSS_MACSEC_BYPASS_TAG_ONE MEPA_MACSEC_BYPASS_TAG_ONE
#define VTSS_MACSEC_BYPASS_TAG_TWO MEPA_MACSEC_BYPASS_TAG_TWO

typedef mepa_macsec_tag_bypass_t vtss_macsec_tag_bypass_t;


/** \brief Set header bypass mode globally for the port
 *
 * \param inst         [IN]     VTSS-API instance.
 * \param port_no      [IN]     VTSS-API port no
 * \param bypass       [IN]     The bypass mode, TAG or Header.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_bypass_mode_set(const vtss_inst_t                inst,
                                    const vtss_port_no_t             port_no,
                                    const vtss_macsec_bypass_mode_t  *const bypass);

/** \brief Get the header bypass mode
 *
 * \param inst         [IN]    VTSS-API instance.
 * \param port_no      [IN]    VTSS-API port no
 * \param bypass       [OUT]   The bypass mode, TAG or Header.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_bypass_mode_get(const vtss_inst_t          inst,
                                    const vtss_port_no_t       port_no,
                                    vtss_macsec_bypass_mode_t  *const bypass);


/** \brief Set the bypass tag mode i.e. number of Tags to bypass: 0(disable), 1 or 2 tags.
 *
 * \param inst         [IN]    VTSS-API instance.
 * \param port         [IN]    MacSec port
 * \param tag          [IN]    Number (enum) of TAGS to bypass.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_bypass_tag_set(const vtss_inst_t              inst,
                                   const vtss_macsec_port_t       port,
                                   const vtss_macsec_tag_bypass_t tag);

/** \brief Get the bypass Tag mode i.e. 0, 1 or 2 tags.
 *
 * \param inst         [IN]    VTSS-API instance.
 * \param port         [IN]    MacSec port
 * \param tag          [OUT]   Number (enum) of TAGS to bypass.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_bypass_tag_get(const vtss_inst_t             inst,
                                   const vtss_macsec_port_t      port,
                                   vtss_macsec_tag_bypass_t      *const tag);



/*--------------------------------------------------------------------*/
/* Others                                                             */
/*--------------------------------------------------------------------*/

#define VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX MEPA_MACSEC_FRAME_CAPTURE_SIZE_MAX
#define VTSS_MACSEC_FRAME_CAPTURE_DISABLE MEPA_MACSEC_FRAME_CAPTURE_DISABLE
#define VTSS_MACSEC_FRAME_CAPTURE_INGRESS MEPA_MACSEC_FRAME_CAPTURE_INGRESS
#define VTSS_MACSEC_FRAME_CAPTURE_EGRESS MEPA_MACSEC_FRAME_CAPTURE_EGRESS

typedef mepa_macsec_frame_capture_t vtss_macsec_frame_capture_t;

/** \brief Sets MTU for both ingress and egress.
 * \param inst         [IN]    VTSS-API instance.
 * \param port_no      [IN]    VTSS-API port no
 * \param mtu_conf     [IN]    New MTU configuration
 *     
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_mtu_set(const vtss_inst_t       inst,
                            const vtss_port_no_t    port_no,
                            const vtss_macsec_mtu_t *const mtu_conf);

/** \brief Gets current MTU configuration
 * \param inst         [IN]    VTSS-API instance.
 * \param port_no      [IN]    VTSS-API port no
 * \param mtu_conf     [IN]    current MTU configuration
 *     
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_mtu_get(const vtss_inst_t       inst,
                            const vtss_port_no_t    port_no,
                            vtss_macsec_mtu_t       *mtu_conf);

/** \brief Enable frame capture.  Used for test/debugging.
 *   The buffer will only capture the first frame received after capturing has been started 
 *   The procedure for frame capturing is as follow:
 *   1) Start capturing (Call vtss_macsec_frame_capture_set with VTSS_MACSEC_FRAME_CAPTURE_INGRESS/VTSS_MACSEC_FRAME_CAPTURE_EGRESS)
 *   2) Send in the frame to be captured
 *   3) Disable capturing (Call vtss_macsec_frame_capture_set with VTSS_MACSEC_FRAME_CAPTURE_DISABLE) in order to prepare for next capturing.
 *   4) Get the captured frame using vtss_macsec_frame_get.
 *
 * \param inst         [IN]    VTSS-API instance.
 * \param port_no      [IN]    VTSS-API port no
 * \param capture      [IN]    Selects  Ingress/Egress frame capture or disable capture.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_frame_capture_set(const vtss_inst_t                   inst,
                                      const vtss_port_no_t                port_no,
                                      const vtss_macsec_frame_capture_t   capture);


/** \brief Get a frame from an internal capture buffer. Used for test/debugging.
 *
 * \param inst          [IN]    VTSS-API instance.
 * \param port_no       [IN]    VTSS-API port no
 * \param buf_length    [IN]    Length of frame buffer.
 * \param return_length [OUT]   Returned length of the frame
 * \param frame         [OUT]   Frame buffer.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid, or if no frame is received.
 */
vtss_rc vtss_macsec_frame_get(const vtss_inst_t             inst,
                              const vtss_port_no_t          port_no,
                              const u32                     buf_length,
                              u32                           *const return_length,
                              u8                            *const frame);

#define VTSS_MACSEC_SEQ_NONE MEPA_MACSEC_SEQ_NONE
#define VTSS_MACSEC_SEQ_THRESHOLD_EVENT MEPA_MACSEC_SEQ_THRESHOLD_EVENT
#define VTSS_MACSEC_SEQ_ROLLOVER_EVENT MEPA_MACSEC_SEQ_ROLLOVER_EVENT
#define VTSS_MACSEC_SEQ_ALL MEPA_MACSEC_SEQ_ALL

typedef mepa_macsec_event_t vtss_macsec_event_t;


/**
 * \brief Enabling / Disabling of events
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number 
 * \param ev_mask [IN]  Mask containing events that are enabled/disabled 
 * \param enable  [IN]  Enable/disable of event
 *
 * \return Return code.
 **/

vtss_rc vtss_macsec_event_enable_set(const vtss_inst_t           inst,
                                     const vtss_port_no_t        port_no,
                                     const vtss_macsec_event_t   ev_mask,
                                     const BOOL                  enable);

/**
 * \brief Get Enabling of events
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number 
 * \param ev_mask [OUT]  Mask containing events that are enabled 
 *
 * \return Return code.
 **/

vtss_rc vtss_macsec_event_enable_get(const vtss_inst_t      inst,
                                     const vtss_port_no_t   port_no,
                                     vtss_macsec_event_t    *const ev_mask);

/**
 * \brief Polling for active events
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number 
 * \param ev_mask [OUT] Mask containing events that are active
 *
 * \return Return code.
 **/
vtss_rc vtss_macsec_event_poll(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_macsec_event_t  *const ev_mask);


/**
 * \brief Configure the SEQ threshold
 *
 * \param inst      [IN]  Target instance reference.
 * \param port_no   [IN]  Port number 
 * \param threshold [IN]  Event sequence threshold
 *
 * \return Return code.
 **/
vtss_rc vtss_macsec_event_seq_threshold_set(const vtss_inst_t     inst,
                                            const vtss_port_no_t  port_no,
                                            const u32             threshold);

/**
 * \brief Get the SEQ threshold
 *
 * \param inst      [IN]   Target instance reference.
 * \param port_no   [IN]   Port number 
 * \param threshold [OUT]  Event sequence threshold
 *
 * \return Return code.
 **/
vtss_rc vtss_macsec_event_seq_threshold_get(const vtss_inst_t     inst,
                                            const vtss_port_no_t  port_no,
                                            u32                   *const threshold);

/**
 * \brief Get the Egress Interrupt SA Active AN
 *
 * \param inst      [IN]   Target instance reference.
 * \param port_no   [IN]   Port number
 * \param port      [OUT]  MACsec port
 * \param an        [OUT]  Egress Interrupted Association number
 *
 * \return Return code.
 **/
vtss_rc vtss_macsec_egr_intr_sa_get(const vtss_inst_t    inst,
                                    const vtss_port_no_t port_no,
                                    vtss_macsec_port_t   *const port,
                                    u16                  *const an);

/**
 * \brief Chip register read
 *
 **/
vtss_rc vtss_macsec_csr_read(const vtss_inst_t           inst,
                             const vtss_port_no_t        port_no,
                             const u16                   mmd,
                             const u32                   addr,
                             u32                         *const value);



/**
 * \brief Chip register write
 *
 **/
vtss_rc vtss_macsec_csr_write(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              const u32                   mmd,
                              const u32                   addr,
                              const u32                   value);


typedef mepa_macsec_rc_dbg_counters_t vtss_macsec_rc_dbg_counters_t;

/**
 * \brief Get return code debug counters
 *
 * \param inst      [IN]   Target instance reference.
 * \param port_no   [IN]   Port number 
 * \param counters [OUT]   The Return Code Debug counters
 *
 * \return Return code.
 **/
vtss_rc vtss_macsec_dbg_counter_get(const vtss_inst_t             inst,
                                    const vtss_port_no_t          port_no,
                                    vtss_macsec_rc_dbg_counters_t *const counters);


/*--------------------------------------------------------------------*/
/* Line MAC / Host MAC / FC                                           */
/*--------------------------------------------------------------------*/

typedef mepa_macsec_mac_counters_t vtss_macsec_mac_counters_t;

/**
 * \brief Host Mac counters (To be moved)
 *
 **/
vtss_rc vtss_macsec_hmac_counters_get(const vtss_inst_t           inst,
                                      const vtss_port_no_t        port_no,
                                      vtss_macsec_mac_counters_t  *const counters,
                                      const BOOL                  clear);

/**
 * \brief Line Mac counters (To be moved)
 *
 **/
vtss_rc vtss_macsec_lmac_counters_get(const vtss_inst_t           inst,
                                      const vtss_port_no_t        port_no,
                                      vtss_macsec_mac_counters_t  *const counters,
                                      const BOOL                  clear);
/**
 * \brief Function for getting if a port is MACSEC capable 
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number 
 * \param capable [OUT] TRUE is port is macsec capable else FALSE
 *
 * \return VTSS_RC_OK if secy_id is valid, else VTSS_RC_ERROR.
 **/
vtss_rc vtss_macsec_is_capable(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               BOOL                 *capable);
/**
 * \brief Function for dump MACSEC registers  
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number 
 * \param pr [IN] Callback function to print the register values 
 *
 * \return VTSS_RC_OK if secy_id is valid, else VTSS_RC_ERROR.
 **/

vtss_rc vtss_macsec_dbg_reg_dump(const vtss_inst_t     inst,
                                 const vtss_port_no_t          port_no,
                                 const vtss_debug_printf_t     pr);

/*--------------------------------------------------------------------*/
/* Macsec SC Instance Counters structures                                */
/*--------------------------------------------------------------------*/

typedef mepa_sc_inst_count_t vtss_sc_inst_count_t;

/*--------------------------------------------------------------------*/
/* Macsec SecY Instance Counters structures                                */
/*--------------------------------------------------------------------*/

typedef mepa_secy_inst_count_t vtss_secy_inst_count_t;

/*--------------------------------------------------------------------*/
/* Macsec Instance Counters structures                                */
/*--------------------------------------------------------------------*/

typedef mepa_macsec_inst_count_t vtss_macsec_inst_count_t;

/** \brief   Get the Instances count of SecYs, Rx SCs, Tx SA and Rx SAs.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port_no   [IN]  Port number
 * \param count     [OUT] Count of Instances.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_inst_count_get(const vtss_inst_t      inst,
                                   const vtss_port_no_t   port_no,
                                vtss_macsec_inst_count_t  *count);

/** \brief Clear the RMON Line mac counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port_no   [IN]  Port number
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_lmac_counters_clear(const vtss_inst_t  inst,
                                     const vtss_port_no_t  port_no);

/** \brief Clear the RMON Host mac counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port_no   [IN]  Port number
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_hmac_counters_clear(const vtss_inst_t  inst,
                                     const vtss_port_no_t  port_no);

/** \brief Clear the Macsec Debug counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port_no   [IN] Port number
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_debug_counters_clear(const vtss_inst_t  inst,
                                      const vtss_port_no_t  port_no);

/** \brief Clear the Common counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port_no   [IN] Port number
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_common_counters_clear(const vtss_inst_t  inst,
                                       const vtss_port_no_t  port_no);

/** \brief Clear the Uncontrolled port counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port_no   [IN] Port number
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_uncontrolled_counters_clear(const vtss_inst_t  inst,
                                             const vtss_port_no_t  port_no);

/** \brief Clear the Controlled port counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_controlled_counters_clear (const vtss_inst_t  inst,
                                        const vtss_macsec_port_t  port);

/** \brief Clear the Rx SA counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 * \param sci       [IN] The rx SCI.
 * \param an        [IN] Association number, 0-3
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_rxsa_counters_clear(const vtss_inst_t  inst,
                                 const vtss_macsec_port_t  port,
                                  const vtss_macsec_sci_t  *const sci,
                                                const u16  an);

/** \brief Clear the Rx SC counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 * \param sci       [IN] The rx SCI.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_rxsc_counters_clear(const vtss_inst_t  inst,
                                 const vtss_macsec_port_t  port,
                                  const vtss_macsec_sci_t  *const sci);

/** \brief Clear the Tx SA counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 * \param an        [IN] Association number, 0-3
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_txsa_counters_clear(const vtss_inst_t  inst,
                                 const vtss_macsec_port_t  port,
                                                const u16  an);

/** \brief Clear the Tx SC counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_txsc_counters_clear (const vtss_inst_t  inst,
                                  const vtss_macsec_port_t  port);

/** \brief Clear the SecY counters.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_secy_counters_clear (const vtss_inst_t  inst,
                                  const vtss_macsec_port_t  port);

/** \brief Get the Macsec Enable Status.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port_no   [IN] Port number
 * \param status    [OUT] MACsec Enable status.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_port_enable_status_get (const vtss_inst_t  inst,
                                         const vtss_port_no_t  port_no,
                                                         BOOL  *status);

/** \brief Get the Macsec RxSA AN Status.
 *
 * \param inst      [IN] VTSS-API instance.
 * \param port      [IN] MACsec port.
 * \param sci       [IN] The Rx SCI.
 * \param an        [IN] Association number, 0-3
 * \param status    [OUT] MACsec RxSA AN status.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_rxsa_an_status_get (const vtss_inst_t        inst,
                                        const vtss_macsec_port_t port,
                                        const vtss_macsec_sci_t  *const sci,
                                        const u16                an,
                                        BOOL                     *status);

/** \brief Get MAC Block MTU and Tag Check configuration.
 *
 * \param inst          [IN] VTSS-API instance.
 * \param port_no       [IN] Port number
 * \param mtu_value     [OUT] Max MTU size .
 * \param mtu_tag_check [OUT] Length Check to consider Q-Tags.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_mac_block_mtu_get(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               u16 *const mtu_value,
                               BOOL *const mtu_tag_check);

/** \brief Set MAC Block MTU and Tag Check configuration.
 *
 * \param inst          [IN] VTSS-API instance.
 * \param port_no       [IN] Port number
 * \param mtu_value     [IN] Max MTU size .
 * \param mtu_tag_check [IN] Length Check to consider Q-Tags.
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_mac_block_mtu_set(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               const u16            mtu_value,
                               const BOOL           mtu_tag_check);

/** \brief Set frame gap compensation in FC Buffer.
 *
 * \param inst          [IN] VTSS-API instance.
 * \param port_no       [IN] Port number
 * \param frm_gap       [IN] frame gap
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_fcbuf_frame_gap_comp_set(const vtss_inst_t     inst,
                                             const vtss_port_no_t  port_no,
                                             const u8              frm_gap);

/** \brief Flow Control buffer Block Reg Dump.
 *
 * \param inst          [IN] VTSS-API instance.
 * \param port_no       [IN] Port number
 * \param pr            [IN] Callback function to print the register values 
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_dbg_fcb_block_reg_dump(const vtss_inst_t    inst,
                                           const vtss_port_no_t port_no,
                                           const vtss_debug_printf_t pr);


/** \brief Flow Control buffer Block Reg Dump.
 *
 * \param inst          [IN] VTSS-API instance.
 * \param port_no       [IN] Port number
 * \param pr            [IN] Callback function to print the register values 
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_dbg_frm_match_handling_ctrl_reg_dump(const vtss_inst_t             inst,
                                                         const vtss_port_no_t          port_no,
                                                         const vtss_debug_printf_t     pr);


#ifdef MEPA_MACSEC_FIFO_OVERFLOW_WORKAROUND
/** \brief MACsec Debug Re-configuration.
 *
 * \param inst          [IN] VTSS-API instance.
 * \param port_no       [IN] Port number
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_dbg_reconfig(const vtss_inst_t    inst,
                                 const vtss_port_no_t port_no);
#endif

/** \brief Configure MACsec Update sequence number.
 *
 * \param inst          [IN] VTSS-API instance.
 * \param port          [IN] MACsec Port
 * \param sci           [IN] SCI of the peer
 * \param an            [IN] Association number, 0-3
 * \param egr           [IN] Direction Egress/Ingress
 * \param disable       [IN] Operation 1:Disable/0:Enable
 *
 * \return VTSS_RC_OK when successful; VTSS_RC_ERROR if parameters are invalid.
 */
vtss_rc vtss_macsec_dbg_update_seq_set(const vtss_inst_t        inst,
                                       const vtss_macsec_port_t port,
                                       const vtss_macsec_sci_t  *const sci,
                                       u16                      an,
                                       BOOL                     egr,
                                       const BOOL               disable);






// ***************************************************************************
//
//  End of file.
//
// ***************************************************************************
#ifdef __cplusplus
}
#endif
#endif /* _VTSS_MACSEC_API_H_ */
