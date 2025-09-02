// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MACSEC_H_
#define LAN80XX_MACSEC_H_

// The following .h file needed
#include <microchip/ethernet/phy/api.h>


/* Cleartags TCAM Match values */
#define LAN80XX_MACSEC_MATCH_DISABLE         (0x0000U)  /* Disable the TCAM Matching */
#define LAN80XX_MACSEC_MATCH_BVLAN_TAG       (0x0001U)  /* Match the B-Tag in PBB packet */
#define LAN80XX_MACSEC_MATCH_IVLAN_TAG       (0x0002U)  /* Match the I-Tag in PBB Packet */
#define LAN80XX_MACSEC_MATCH_CVLAN           (0x0004U)  /* Match the Outer customer VLAN ID */
#define LAN80XX_MACSEC_MATCH_MPLS_1          (0x0008U)  /* Match the MPLS label 1 */
#define LAN80XX_MACSEC_MATCH_MPLS_2          (0x0010U)  /* Match the MPLS Label 2 */



/* TCAM Policy Mode */
typedef enum {
    LAN80XX_MACSEC_EGR_POLICY_TCAM,  /* Egress TCAM Mode */
    LAN80XX_MACSEC_EGR_POLICY_HDR,   /* Egress Header Mode */
} phy25g_macsec_egr_mode_t;

/* Type of Packet */
typedef enum {
    LAN80XX_PACKET_TYPE_NONE = 0,
    LAN80XX_PACKET_TYPE_MPLS,
    LAN80XX_PACKET_TYPE_PBB,
} phy25g_packet_type;

/* Number of VLAN TAG in the PBB and EoMPLS type packet */
typedef enum {
    LAN80XX_PBB_MPLS_VLAN_TAG_NONE = 0,
    LAN80XX_PBB_MPLS_VLAN_TAG_ONE,
    LAN80XX_PBB_MPLS_VLAN_TAG_TWO,
} phy25g_clrtag_vlan_t;

/* Position of Sectag */
typedef enum {
    LAN80XX_PBB_SECTAG_AFT_CMAC, /* Sectag after Inner Customer MAC Address */
    LAN80XX_PBB_SECTAG_AFT_1TAG, /* Sectag after one VLAN tag */
    LAN80XX_PBB_SECTAG_AFT_2TAG, /* Sectag after two VLAN tag */
} phy25g_pbbmpls_sectag_t;

/* VLAN Tag Parameters */
typedef struct {
    u32     vid;
    u8      pcp;
    u8      dei;
} phy25g_vlan_t;

/* PBB Packet Parameters for TCAM Matching */
typedef struct {
    phy25g_vlan_t               btag;       /* Backbone VLAN Tag */
    phy25g_vlan_t               itag;       /* Backbone service instance tag */
    mepa_vid_t                  out_cus_vid; /* Outer customer VLAN Tag after PBB Header */
} phy25g_pbb_conf_t;

/* MPLS Packet Paramets for TCAM MAtching */
typedef struct {
    u8          mpls1_num;   /* MPLS Header number for TCAM MPLS 1 Match */
    u8          mpls2_num;   /* MPLS Header number for TCMA MPLS 2 Match */
    u32         mpls1_label; /* Value of MPLS LABEL for MPLS Header 1 */
    u32         mpls2_label; /* value of MPLS LABEL for MPLS Header 2 */
    u8          mpls1_exp;   /* Value of MPLS Experiment for MPLS Header 1 */
    u8          mpls2_exp;   /* Value of MPLS Experiment for MPLS Header 1 */
    mepa_bool_t mpls1_s;     /* Value of MPLS S bit for MPLS Header 1 */
    mepa_bool_t mpls2_s;     /* Value of MPLS S bit for MPLS Header 2 */
} phy25g_mpls_conf_t;

/* MACsec cleatags v3.5 Configuration */
typedef struct {
    phy25g_packet_type        packet_type;     /* Type of Packet */
    phy25g_pbb_conf_t         pbb_conf;        /* PBB packet parameters */
    phy25g_mpls_conf_t        mpls_conf;       /* MPLS packet parameters */
    phy25g_clrtag_vlan_t      num_tag;         /* Number of VLAN tags after PBB and EoMPLS Header */
    mepa_bool_t               is_eo_mpls;      /* The Packet is EoMPLS of Bulk-MPLS */
    phy25g_pbbmpls_sectag_t   sectag_off;      /* Position of sectag */
    u16                       num_mpls_label;  /* Number of MPLS Labels valid if Packet type is MPLS */
    mepa_bool_t               is_pw_ctrl_word; /* Whether MPLS Packet has PW Control Word */
    u32                       match;           /* TCAM Matching Rule */
} phy25g_macsec_cleartags_conf_t;


/**
 * To Configure Egrees Policy mode for MACsec.
 *
 * \param dev                   [IN] mepa driver
 * \param port_no               [IN] Port Number
 * \param egr_policy_mode       [IN] Selects the egress policy mode
 * \param hdr_eth_type          [IN] Ethertype of Cleartags header -- Applicable only for "LAN80XX_MACSEC_EGR_POLICY_HDR" egr_policy_mode
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_egr_policy_mode_set(mepa_device_t                   *dev,
                                           const mepa_port_no_t            port_no,
                                           const phy25g_macsec_egr_mode_t  egr_policy_mode,
                                           const mepa_etype_t              hdr_eth_type);
/**
 * To get Egrees Policy mode configured for MACsec.
 *
 * \param dev                   [IN] mepa driver
 * \param port_no               [IN] Port Number
 * \param egr_policy_mode       [OUT] Returns the egress policy mode
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_egr_policy_mode_get(mepa_device_t             *dev,
                                           const mepa_port_no_t      port_no,
                                           phy25g_macsec_egr_mode_t  egr_policy_mode);


/**
 * Configuration to Bypass the cleartags v3.5 headers
 *
 * \param dev                   [IN] mepa driver
 * \param port_no               [IN] Port Number
 * \param enable                [IN] Enable or Disable the cleartags configuration
 * \param tags_conf             [IN] Cleartags Configuration
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_cleartags_conf_set(mepa_device_t                         *dev,
                                          const mepa_port_no_t                  port_no,
                                          const mepa_bool_t                     enable,
                                          const phy25g_macsec_cleartags_conf_t  *const conf);

/**
 * To get the cleartags configuration done
 *
 * \param dev                   [IN] mepa driver
 * \param port_no               [IN] Port Number
 * \param enable                [OUT] Cleartags Configuration enabled or not
 * \param tags_conf             [OUT] return cleartags configuration
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_cleartags_conf_get(mepa_device_t                      *dev,
                                          const mepa_port_no_t               port_no,
                                          mepa_bool_t                        enable,
                                          phy25g_macsec_cleartags_conf_t     *const conf);

/**
 * To get Uncontrolled port statistics
 *
 * \param dev                   [IN] mepa driver
 * \param port                  [IN] macsec port
 * \param counters              [OUT] Uncontrolled port statistics
 * \param tags_conf             [OUT] return cleartags configuration
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_uncontrolled_counters_get(mepa_device_t                       *dev,
                                                 const mepa_port_no_t                port_no,
                                                 const mepa_macsec_port_t            port,
                                                 mepa_macsec_uncontrolled_counters_t *const counters);

/**
 * To get controlled port statistics
 *
 * \param dev                   [IN] mepa driver
 * \param port                  [IN] macsec port
 * \param counters              [OUT] controlled port statistics
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_controlled_counters_get(mepa_device_t                       *dev,
                                               const mepa_port_no_t                port_no,
                                               const mepa_macsec_port_t            port,
                                               mepa_macsec_secy_port_counters_t    *const counters);

/**
 * To get Common port statistics
 *
 * \param dev                   [IN] mepa driver
 * \param port                  [IN] macsec port
 * \param counters              [OUT] Common port statistics
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_common_counters_get(mepa_device_t                       *dev,
                                           const mepa_port_no_t                port_no,
                                           const mepa_macsec_port_t            port,
                                           mepa_macsec_common_counters_t       *const counters);

/**
 * To clear Uncontrolled port statistics
 *
 * \param dev                   [IN] mepa driver
 * \param port                  [IN] macsec port
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_uncontrolled_counters_clear (mepa_device_t             *dev,
                                                    const mepa_port_no_t      port_no,
                                                    const mepa_macsec_port_t  port);

/**
 * To clear controlled port statistics
 *
 * \param dev                   [IN] mepa driver
 * \param port                  [IN] macsec port
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_controlled_counters_clear (mepa_device_t             *dev,
                                                  const mepa_port_no_t      port_no,
                                                  const mepa_macsec_port_t  port);

/**
 * To clear Common port statistics
 *
 * \param dev                   [IN] mepa driver
 * \param port                  [IN] macsec port
 *
 * \return Return code.
 * MEPA_RC_OK Success
 * MEPA_RC_ERROR Fail
 **/
mepa_rc lan80xx_macsec_common_counters_clear (mepa_device_t             *dev,
                                              const mepa_port_no_t      port_no,
                                              const mepa_macsec_port_t  port);



#endif
