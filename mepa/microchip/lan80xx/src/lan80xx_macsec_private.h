// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_LAN80XX_MACSEC_H_
#define _MEPA_LAN80XX_MACSEC_H_

#include <mepa_driver.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api/phy_macsec.h>
#include <microchip/ethernet/phy/api.h>
#include "lan80xx_macsec.h"

/* Cleartags Disable Bit position */
#define LAN80XX_CLEARTAGS_DISABLE   (1U << 4)

/* Number of actions supported: drop/forward to control/uncontrol port */
#define LAN80XX_MACSEC_ACTION_MAX   (3U)

/* Number of Directions supported: egress/ingress/none */
#define LAN80XX_MACSEC_DIRECTION_MAX (3U)

/* Maximum supported MTU for MACSEC */
#define LAN80XX_MACSEC_MTU_MAX      (32761U)

/* DMAC + ETYPE + DMAC/ETYPE */
#define LAN80XX_MACSEC_CP_RULES     ((8U) + (8U) + (2U))

/* Broadcast MAC Address */
#define LAN80XX_MAC_ADDR_BROADCAST  {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU}

/* Number of Secure Associations that M25G supports */
#define LAN80XX_MACSEC_MAX_SA       (128U)
#define LAN80XX_MACSEC_MAX_SECY     (LAN80XX_MACSEC_MAX_SA / 2U)
#define LAN80XX_MACSEC_MAX_RX_SC    (LAN80XX_MACSEC_MAX_SECY)

/* Zero MAC Address */
#define LAN80XX_MAC_ADDR_ZERO       {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}

/* Maximum replay window size supported */
#define LAN80XX_MACSEC_REPLAY_WINDOW_SIZE (0x40000000UL)

#define LAN80XX_MACSEC_THRESHOLD_EVENT_ENABLE_BIT (20U)
#define LAN80XX_MACSEC_ROLLOVER_EVENT_ENABLE_BIT  (21U)

#define LAN80XX_MACSEC_THRESHOLD_EVENT_STATUS_BIT (4U)
#define LAN80XX_MACSEC_ROLLOVER_EVENT_STATUS_BIT  (5U)
#define LAN80XX_MACSEC_SA_TRIGGER_MASK            (0xFFFFFFFFUL)
#define LAN80XX_MACSEC_FIFO_TRUNCATED_MASK        (0x00000200UL)
#define LAN80XX_MACSEC_FIFO_PKT_SIZE_MASK         (0x000001FFUL)

/* Standard MACsec Sectag location in bytes */
#define LAN80XX_MACSEC_STANDARD_SECTAG_OFFSET     (12U)
/* MAC Address length (DA + SA) in bytes */
#define LAN80XX_MAC_ADDRESS_LEN_BYTES             (12U)
/* Ether Type length in bytes */
#define LAN80XX_ETHER_TYPE_LEN_BYTES              (2U)
/* PBB Packet Authentication start in bytes */
#define LAN80XX_MACSEC_PBB_AUTH_START             (22U)
/* Length of PBB Packet header in bytes including outer MAC Addr */
#define LAN80XX_MACSEC_PBB_HEADER_BYTES           (34U)
/* Length of MPLS Header in bytes */
#define LAN80XX_MPLS_LABEL_LEN_BYTE               (4U)
/* PW Control word length in bytes */
#define LAN80XX_MPLS_PW_CTRL_WORD_LEN             (4U)
/* VLAN Tag length in bytes */
#define LAN80XX_VLAN_TAG_LEN_BYTE                 (4U)
#define LAN80XX_MACSEC_NUM_MPLS_LABEL_0           (6U)
/* Number of MPLS Label EIP-161 supports in Egress */
#define LAN80XX_MACSEC_EGR_MPLS_SUPPORT           (9U)
/* Number of MPLS Label EIP-161 supports in Ingress */
#define LAN80XX_MACSEC_INGR_MPLS_SUPPORT          (5U)

/* MACsec block latency */
#define LAN80XX_MACSEC_1G_INGR_LATENCY            (88U)
#define LAN80XX_MACSEC_1G_EGR_LATENCY             (80U)
#define LAN80XX_MACSEC_10G_INGR_LATENCY           (70U)
#define LAN80XX_MACSEC_10G_EGR_LATENCY            (62U)
#define LAN80XX_MACSEC_25G_INGR_LATENCY           (70U)
#define LAN80XX_MACSEC_25G_EGR_LATENCY            (62U)

#define LAN80XX_MACSEC_CONTEX_CTRL                (0xE5880200UL)
#define LAN80XX_MACSEC_CONTEXT_UPD_CTRL           (3U)
#define LAN80XX_MACSEC_DYN_LATENCY                (5U)

#define LAN80XX_MACSEC_SEQ_NUM_THR_MASK           (1UL << 20)
#define LAN80XX_MACSEC_SEQ_NUM_ROLL_MASK          (1UL << 21)

/* Control Frame Matching */
#define LAN80XX_MACSEC_DMAC_AND_ETHTYPE_RULE_ID_END  (2U)
#define LAN80XX_MACSEC_MAX_ETHTYPE_RULE_ID_END       (10U)
#define LAN80XX_MACSEC_MAX_DMAC_RULE_ID_END          (18U)

#define LAN80XX_MACSEC_RECORD_PAGE0_CNT             (64U)



// Structure to configure Rx Secure Assosiation
typedef struct {
    mepa_bool_t                  in_use;
    mepa_bool_t                  enabled;
    u32                          record;
    mepa_macsec_sak_t            sak;
    mepa_macsec_rx_sa_status_t   status;
    mepa_macsec_rx_sa_counters_t cnt;
    mepa_macsec_ssci_t           ssci;
} phy25g_macsec_internal_rx_sa_t;

// Structure to configure Tx Secure Assosiation
typedef struct {
    mepa_bool_t                  in_use;
    mepa_bool_t                  enabled;
    u32                          record;
    mepa_bool_t                  confidentiality;
    mepa_macsec_sak_t            sak;
    mepa_macsec_tx_sa_status_t   status;
    mepa_macsec_tx_sa_counters_t cnt;
    mepa_macsec_ssci_t           ssci;
} phy25g_macsec_internal_tx_sa_t;

// Structure to configure Rx Secure Channel
typedef struct {
    mepa_bool_t                   in_use;
    mepa_macsec_sci_t             sci;
    mepa_macsec_rx_sc_status_t    status;
    mepa_macsec_rx_sc_counters_t  cnt;
    phy25g_macsec_internal_rx_sa_t  *sa[MEPA_MACSEC_SA_PER_SC_MAX];
    mepa_macsec_rx_sc_conf_t      conf;
    mepa_macsec_rx_sa_counters_t  del_rx_sa_cnt;
    u64                           in_octets_validation_disabled;
} phy25g_macsec_internal_rx_sc_t;

// Structure to configure Tx Secure Channel
typedef struct {
    mepa_bool_t                   in_use;
    mepa_macsec_tx_sc_status_t    status;
    mepa_macsec_tx_sc_counters_t  cnt;
    mepa_macsec_tx_sa_counters_t  del_tx_sa_cnt;
    phy25g_macsec_internal_tx_sa_t  *sa[MEPA_MACSEC_SA_PER_SC_MAX];
    u64                           out_octets_untagged;
} phy25g_macsec_internal_tx_sc_t;

// Structure to configure the SecY parameters
typedef struct {
    mepa_bool_t                          in_use;
    mepa_macsec_sci_t                    sci;
    mepa_macsec_service_id_t             service_id;
    mepa_bool_t                          controlled_port_enabled;
    mepa_macsec_secy_port_counters_t     controlled_cnt;
    mepa_macsec_common_counters_t        common_cnt;
    mepa_macsec_uncontrolled_counters_t  uncontrolled_cnt;
    mepa_macsec_secy_counters_t          secy_cnt;
    mepa_macsec_secy_conf_t              conf;
    phy25g_macsec_internal_rx_sc_t       *rx_sc[LAN80XX_MACSEC_MAX_RX_SC];
    phy25g_macsec_internal_tx_sc_t       tx_sc;
    mepa_macsec_match_pattern_t          pattern[LAN80XX_MACSEC_ACTION_MAX][LAN80XX_MACSEC_DIRECTION_MAX];
    u32                                  pattern_record[LAN80XX_MACSEC_ACTION_MAX][LAN80XX_MACSEC_DIRECTION_MAX];
    mepa_macsec_tag_bypass_t             tag_bypass;
} phy25g_macsec_internal_secy_t;

// Global structure for MACsec
typedef struct {
    mepa_macsec_default_action_policy_t     default_action;                          /** Action to be followed when frame is not matched */
    mepa_macsec_control_frame_match_conf_t  control_match[LAN80XX_MACSEC_CP_RULES];  /** Control frame match configuration */
    u32                                     egr_bypass_record[LAN80XX_MACSEC_CP_RULES];
    mepa_macsec_bypass_mode_t               bypass_mode;
    phy25g_macsec_egr_mode_t                egr_policy_mode;
    phy25g_macsec_cleartags_conf_t          cleartags_conf;
    mepa_bool_t                             cleartags_init_done;
    mepa_macsec_init_t                      init;
    mepa_bool_t                             warm_start_reg_changed;  /** Indicates the reg changed during warm start */
    mepa_macsec_mtu_t                       mtu_conf;                /** Configuration of MTU */
    u16                                     mac_block_mtu;           /** MAC Block MTU */
    mepa_bool_t                             rmon_counters_clr;       /** MACsec RMON counters clear flag */
    mepa_bool_t                             spd_change_macsec_recfg;
} phy25g_macsec_internal_glb_t;

// M25G MACsec capability structure
typedef struct {
    phy25g_macsec_internal_secy_t         secy[LAN80XX_MACSEC_MAX_SECY];
    phy25g_macsec_internal_rx_sc_t        rx_sc[LAN80XX_MACSEC_MAX_RX_SC];
    phy25g_macsec_internal_rx_sa_t        rx_sa[LAN80XX_MACSEC_MAX_SA];
    phy25g_macsec_internal_tx_sa_t        tx_sa[LAN80XX_MACSEC_MAX_SA];
    phy25g_macsec_internal_glb_t          glb;
    mepa_macsec_rc_dbg_counters_t         rc_dbg_counters;
} phy25g_macsec_internal_conf_t;

// Structure used to get the next inuse SecY
typedef struct {
    u32 secy_id;
    u32 next_index;
} phy25g_macsec_secy_in_use_iter_t;

mepa_bool_t lan80xx_phy_is_macsec_capable(mepa_device_t *dev);

mepa_rc lan80xx_macsec_init_set_priv(mepa_device_t *dev, const mepa_macsec_init_t *const init);

mepa_rc lan80xx_macsec_init_get_priv(mepa_device_t *dev, mepa_macsec_init_t *const init);


mepa_rc lan80xx_macsec_is_capable_priv(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_bool_t *capable);


mepa_rc lan80xx_macsec_default_action_set_priv(mepa_device_t *dev, const mepa_port_no_t port_no, const mepa_macsec_default_action_policy_t *const policy);


mepa_rc lan80xx_macsec_default_action_get_priv(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_macsec_default_action_policy_t *const policy);


mepa_rc lan80xx_macsec_secy_conf_add_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf);

mepa_rc lan80xx_macsec_secy_conf_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf);


mepa_rc lan80xx_macsec_secy_conf_del_priv(mepa_device_t *dev, const mepa_macsec_port_t port);

mepa_rc lan80xx_macsec_secy_controlled_set_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_bool_t enable);


mepa_rc lan80xx_macsec_secy_controlled_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_bool_t *const enable);

mepa_rc lan80xx_macsec_pattern_set_priv(mepa_device_t                      *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t   action,
                                        const mepa_macsec_match_pattern_t  *const pattern);

mepa_rc lan80xx_macsec_pattern_get_priv(mepa_device_t                      *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t  action,
                                        mepa_macsec_match_pattern_t        *const pattern);


mepa_rc lan80xx_macsec_pattern_del_priv(mepa_device_t                    *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t   action);

mepa_rc lan80xx_macsec_tx_sa_set_priv(mepa_device_t *dev,
                                      const mepa_macsec_port_t port,
                                      const u16          an,
                                      const u32          next_pn,
                                      const mepa_bool_t  confidentiality,
                                      const mepa_macsec_sak_t *const sak);

mepa_rc lan80xx_macsec_tx_sa_get_priv(mepa_device_t            *dev,
                                      const mepa_macsec_port_t port,
                                      const u16                an,
                                      u32 *const               next_pn,
                                      mepa_bool_t              *const confidentiality,
                                      mepa_macsec_sak_t        *const sak,
                                      mepa_bool_t              *const active);


mepa_rc lan80xx_macsec_tx_seca_set_priv(mepa_device_t                *dev,
                                        const mepa_macsec_port_t     port,
                                        const u16                    an,
                                        const mepa_macsec_pkt_num_t  next_pn,
                                        const mepa_bool_t            confidentiality,
                                        const mepa_macsec_sak_t      *const sak,
                                        const mepa_macsec_ssci_t     *const ssci);

mepa_rc lan80xx_macsec_tx_seca_get_priv(mepa_device_t  *dev,
                                        const mepa_macsec_port_t  port,
                                        const u16                 an,
                                        mepa_macsec_pkt_num_t     *const next_pn,
                                        mepa_bool_t               *const confidentiality,
                                        mepa_macsec_sak_t         *const sak,
                                        mepa_bool_t               *const active,
                                        mepa_macsec_ssci_t        *const ssci);

mepa_rc lan80xx_macsec_rx_sa_set_priv(mepa_device_t                 *dev,
                                      const mepa_macsec_port_t      port,
                                      const mepa_macsec_sci_t       *const sci,
                                      const u16                     an,
                                      const u32                     lowest_pn,
                                      const mepa_macsec_sak_t       *const sak);

mepa_rc lan80xx_macsec_rx_sa_get_priv(mepa_device_t                 *dev,
                                      const mepa_macsec_port_t      port,
                                      const mepa_macsec_sci_t       *const sci,
                                      const u16                     an,
                                      u32                           *const lowest_pn,
                                      mepa_macsec_sak_t             *const sak,
                                      mepa_bool_t                   *const active);


mepa_rc lan80xx_macsec_rx_seca_set_priv(mepa_device_t *dev,
                                        const mepa_macsec_port_t      port,
                                        const mepa_macsec_sci_t       *const sci,
                                        const u16                     an,
                                        const mepa_macsec_pkt_num_t   lowest_pn,
                                        const mepa_macsec_sak_t       *const sak,
                                        const mepa_macsec_ssci_t      *const ssci);

mepa_rc lan80xx_macsec_rx_seca_get_priv(mepa_device_t  *dev,
                                        const mepa_macsec_port_t      port,
                                        const mepa_macsec_sci_t       *const sci,
                                        const u16                     an,
                                        mepa_macsec_pkt_num_t         *const lowest_pn,
                                        mepa_macsec_sak_t             *const sak,
                                        mepa_bool_t                   *const active,
                                        mepa_macsec_ssci_t            *const ssci);


mepa_rc lan80xx_macsec_rx_sc_del_priv(mepa_device_t *dev,
                                      const mepa_macsec_port_t    port,
                                      const mepa_macsec_sci_t     *const sci);

mepa_rc lan80xx_macsec_tx_sa_del_priv(mepa_device_t  *dev,
                                      const mepa_macsec_port_t  port,
                                      const u16                 an);

mepa_rc lan80xx_macsec_tx_sa_activate_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const u16 an);



mepa_rc lan80xx_macsec_tx_sa_disable_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const u16  an);


mepa_rc lan80xx_macsec_tx_sa_status_get_priv(mepa_device_t  *dev, const mepa_macsec_port_t  port, const u16 an, mepa_macsec_tx_sa_status_t  *const status);


mepa_rc lan80xx_macsec_rx_sa_activate_priv(mepa_device_t  *dev, const mepa_macsec_port_t port, const mepa_macsec_sci_t  *const sci, const u16 an);


mepa_rc lan80xx_macsec_rx_sa_disable_priv(mepa_device_t *dev,
                                          const mepa_macsec_port_t  port,
                                          const mepa_macsec_sci_t   *const sci,
                                          const u16                 an);

mepa_rc lan80xx_macsec_rx_sa_del_priv(mepa_device_t  *dev,
                                      const mepa_macsec_port_t  port,
                                      const mepa_macsec_sci_t   *const sci,
                                      const u16                 an);

mepa_rc lan80xx_macsec_rx_sa_status_get_priv(mepa_device_t    *dev,
                                             const mepa_macsec_port_t    port,
                                             const mepa_macsec_sci_t     *const sci,
                                             const u16                   an,
                                             mepa_macsec_rx_sa_status_t  *const status);

mepa_rc lan80xx_macsec_rx_sa_lowest_pn_update_priv(mepa_device_t  *dev,
                                                   const mepa_macsec_port_t     port,
                                                   const mepa_macsec_sci_t      *const sci,
                                                   const u16                    an,
                                                   const u32                    lowest_pn);


mepa_rc lan80xx_macsec_rxsa_an_status_get_priv(mepa_device_t             *dev,
                                               const mepa_macsec_port_t  port,
                                               const mepa_macsec_sci_t   *const sci,
                                               const u16                 an,
                                               mepa_bool_t               *status);


mepa_rc lan80xx_macsec_tx_sa_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               const u16                       an,
                                               mepa_macsec_tx_sa_counters_t    *const counters);


mepa_rc lan80xx_macsec_tx_sc_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               mepa_macsec_tx_sc_counters_t    *const counters);


mepa_rc lan80xx_macsec_rx_sc_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               const mepa_macsec_sci_t         *const sci,
                                               mepa_macsec_rx_sc_counters_t    *const counters);

mepa_rc lan80xx_macsec_rx_sa_counters_get_priv(mepa_device_t                *dev,
                                               const mepa_macsec_port_t     port,
                                               const mepa_macsec_sci_t      *const sci,
                                               const u16                    an,
                                               mepa_macsec_rx_sa_counters_t *const counters);

mepa_rc lan80xx_macsec_txsc_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port);

mepa_rc lan80xx_macsec_txsa_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port,
                                                const u16  an);

mepa_rc lan80xx_macsec_rxsc_counters_clear_priv(mepa_device_t *dev,
                                                const mepa_macsec_port_t  port,
                                                const mepa_macsec_sci_t  *const sci);


mepa_rc lan80xx_macsec_rxsa_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port,
                                                const mepa_macsec_sci_t  *const sci,
                                                const u16  an);


mepa_rc lan80xx_macsec_secy_counters_get_priv(mepa_device_t                 *dev,
                                              const mepa_macsec_port_t      port,
                                              mepa_macsec_secy_counters_t   *const counters);


mepa_rc lan80xx_macsec_controlled_counters_get_priv(mepa_device_t                       *dev,
                                                    const mepa_port_no_t                port_no,
                                                    const mepa_macsec_port_t            port,
                                                    mepa_macsec_secy_port_counters_t    *const counters);


mepa_rc lan80xx_macsec_uncontrolled_counters_get_priv(mepa_device_t                       *dev,
                                                      const mepa_port_no_t                port_no,
                                                      const mepa_macsec_port_t            port,
                                                      mepa_macsec_uncontrolled_counters_t *const counters);

mepa_rc lan80xx_macsec_common_counters_get_priv(mepa_device_t                       *dev,
                                                const mepa_port_no_t                port_no,
                                                const mepa_macsec_port_t            port,
                                                mepa_macsec_common_counters_t       *const counters);


mepa_rc lan80xx_macsec_counters_update_priv(mepa_device_t  *dev,
                                            const mepa_port_no_t  port_no);

mepa_rc lan80xx_macsec_secy_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port);

mepa_rc lan80xx_macsec_uncontrolled_counters_clear_priv(mepa_device_t  *dev,
                                                        const mepa_port_no_t      port_no,
                                                        const mepa_macsec_port_t  port);

mepa_rc lan80xx_macsec_controlled_counters_clear_priv(mepa_device_t  *dev,
                                                      const mepa_port_no_t      port_no,
                                                      const mepa_macsec_port_t  port);


mepa_rc lan80xx_macsec_common_counters_clear_priv(mepa_device_t  *dev,
                                                  const mepa_port_no_t      port_no,
                                                  const mepa_macsec_port_t  port);

mepa_rc lan80xx_macsec_lmac_counters_get_priv(mepa_device_t               *dev,
                                              const mepa_port_no_t        port_no,
                                              mepa_macsec_mac_counters_t  *const counters,
                                              mepa_bool_t                 clear);

mepa_rc lan80xx_macsec_hmac_counters_get_priv(mepa_device_t               *dev,
                                              const mepa_port_no_t        port_no,
                                              mepa_macsec_mac_counters_t  *const counters,
                                              mepa_bool_t                 clear);


mepa_rc lan80xx_macsec_lmac_counters_clear_priv(mepa_device_t         *dev,
                                                const mepa_port_no_t  port_no);

mepa_rc lan80xx_macsec_hmac_counters_clear_priv(mepa_device_t      *dev,
                                                const mepa_port_no_t  port_no);

mepa_rc lan80xx_macsec_debug_counters_clear_priv(mepa_device_t          *dev,
                                                 const mepa_port_no_t   port_no);

mepa_rc lan80xx_macsec_csr_read_priv(mepa_device_t               *dev,
                                     const mepa_port_no_t        port_no,
                                     const u16                   mmd,
                                     const u32                   addr,
                                     u32                         *const value);

mepa_rc lan80xx_macsec_csr_write_priv(mepa_device_t               *dev,
                                      const mepa_port_no_t        port_no,
                                      const u32                   mmd,
                                      const u32                   addr,
                                      const u32                   value);

mepa_rc lan80xx_macsec_mtu_set_priv(mepa_device_t            *dev,
                                    const mepa_port_no_t     port_no,
                                    const mepa_macsec_mtu_t  *const mtu_conf);

mepa_rc lan80xx_macsec_mtu_get_priv(mepa_device_t           *dev,
                                    const mepa_port_no_t    port_no,
                                    mepa_macsec_mtu_t       *mtu_conf);


mepa_rc lan80xx_mac_block_mtu_set_priv(mepa_device_t         *dev,
                                       const mepa_port_no_t  port_no,
                                       const u16             mtu_value,
                                       const mepa_bool_t     mtu_tag_check);


mepa_rc lan80xx_mac_block_mtu_get_priv(mepa_device_t        *dev,
                                       const mepa_port_no_t port_no,
                                       u16                  *const mtu_value,
                                       mepa_bool_t          *const mtu_tag_check);


mepa_rc lan80xx_macsec_dbg_update_seq_set_priv(mepa_device_t             *dev,
                                               const mepa_macsec_port_t  port,
                                               const mepa_macsec_sci_t   *const sci,
                                               u16                       an,
                                               mepa_bool_t               egr,
                                               const mepa_bool_t         disable);

mepa_rc lan80xx_macsec_frame_capture_set_priv(mepa_device_t                       *dev,
                                              const mepa_port_no_t                port_no,
                                              const mepa_macsec_frame_capture_t   capture);

mepa_rc lan80xx_macsec_frame_get_priv(mepa_device_t                 *dev,
                                      const mepa_port_no_t          port_no,
                                      const u32                     buf_length,
                                      u32                           *const frm_length,
                                      u8                            *const frame);


mepa_rc lan80xx_macsec_event_seq_threshold_set_priv(mepa_device_t         *dev,
                                                    const mepa_port_no_t  port_no,
                                                    const u32             threshold);

mepa_rc lan80xx_macsec_event_seq_threshold_get_priv(mepa_device_t         *dev,
                                                    const mepa_port_no_t  port_no,
                                                    u32                   *const threshold);


mepa_rc lan80xx_macsec_secy_cap_get_priv(mepa_device_t                 *dev,
                                         const mepa_port_no_t          port_no,
                                         mepa_macsec_secy_cap_t        *const cap);

mepa_rc lan80xx_macsec_event_enable_set_priv(mepa_device_t        *dev,
                                             const mepa_port_no_t        port_no,
                                             const mepa_macsec_event_t   ev_mask,
                                             const mepa_bool_t           enable);

mepa_rc lan80xx_macsec_event_enable_get_priv(mepa_device_t    *dev,
                                             const mepa_port_no_t   port_no,
                                             mepa_macsec_event_t    *const ev_mask);

mepa_rc lan80xx_macsec_event_poll_priv(mepa_device_t         *dev,
                                       const mepa_port_no_t  port_no,
                                       mepa_macsec_event_t  *const ev_mask);

mepa_rc lan80xx_macsec_port_get_next_priv(mepa_device_t               *dev,
                                          const mepa_port_no_t        port_no,
                                          const mepa_macsec_port_t    *const search_macsec_port,
                                          mepa_macsec_port_t          *const found_macsec_port);

mepa_rc lan80xx_macsec_egr_policy_mode_set_priv(mepa_device_t                   *dev,
                                                const mepa_port_no_t            port_no,
                                                const phy25g_macsec_egr_mode_t  egr_policy_mode,
                                                const mepa_etype_t              hdr_eth_type);


mepa_rc lan80xx_macsec_egr_policy_mode_get_priv(mepa_device_t             *dev,
                                                const mepa_port_no_t      port_no,
                                                phy25g_macsec_egr_mode_t  egr_policy_mode);

mepa_rc lan80xx_macsec_bypass_mode_set_priv(mepa_device_t                    *dev,
                                            const mepa_port_no_t             port_no,
                                            const mepa_macsec_bypass_mode_t  *const bypass);


mepa_rc lan80xx_macsec_bypass_mode_get_priv(mepa_device_t              *dev,
                                            const mepa_port_no_t       port_no,
                                            mepa_macsec_bypass_mode_t  *const bypass);

mepa_rc lan80xx_macsec_bypass_tag_set_priv(mepa_device_t                     *dev,
                                           const mepa_macsec_port_t          port,
                                           const mepa_macsec_tag_bypass_t    tag);

mepa_rc lan80xx_macsec_bypass_tag_get_priv(mepa_device_t                 *dev,
                                           const mepa_macsec_port_t      port,
                                           mepa_macsec_tag_bypass_t      *const tag);


mepa_rc lan80xx_macsec_cleartags_conf_set_priv(mepa_device_t                         *dev,
                                               const mepa_port_no_t                  port_no,
                                               const mepa_bool_t                     enable,
                                               const phy25g_macsec_cleartags_conf_t  *const conf);

mepa_rc lan80xx_macsec_control_frame_match_conf_set_priv(mepa_device_t                                 *dev,
                                                         const mepa_port_no_t                          port_no,
                                                         const mepa_macsec_control_frame_match_conf_t *const conf,
                                                         u32                                          *const rule_id);


mepa_rc lan80xx_macsec_control_frame_match_conf_del_priv(mepa_device_t             *dev,
                                                         const mepa_port_no_t      port_no,
                                                         const u32                 rule_id);


mepa_rc lan80xx_macsec_control_frame_match_conf_get_priv(mepa_device_t                              *dev,
                                                         const mepa_port_no_t                       port_no,
                                                         mepa_macsec_control_frame_match_conf_t     *const conf,
                                                         u32                                        rule_id);

mepa_rc lan80xx_macsec_cleartags_conf_get_priv(mepa_device_t                      *dev,
                                               const mepa_port_no_t               port_no,
                                               mepa_bool_t                        enable,
                                               phy25g_macsec_cleartags_conf_t     *const conf);

mepa_rc lan80xx_macsec_inst_count_get_priv(mepa_device_t             *dev,
                                           const mepa_port_no_t      port_no,
                                           mepa_macsec_inst_count_t  *counts);


mepa_rc lan80xx_macsec_dbg_reg_dump_priv(mepa_device_t     *dev,
                                         mepa_port_no_t     port_no,
                                         mepa_debug_print_t pr);


mepa_rc lan80xx_macsec_dbg_counter_get_priv(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_macsec_rc_dbg_counters_t *const counters);

mepa_rc lan80xx_macsec_secy_conf_update_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf);

mepa_rc lan80xx_macsec_tx_sc_set_priv(mepa_device_t *dev, const mepa_macsec_port_t port);


mepa_rc lan80xx_macsec_tx_sc_update_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_tx_sc_conf_t *const conf);

mepa_rc lan80xx_macsec_tx_sc_del_priv(mepa_device_t *dev, const mepa_macsec_port_t port);

mepa_rc lan80xx_macsec_tx_sc_status_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_tx_sc_status_t *const status);

mepa_rc lan80xx_macsec_tx_sc_get_conf_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_tx_sc_conf_t *const conf);

mepa_rc lan80xx_macsec_rx_sc_add_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const mepa_macsec_sci_t  *const sci);

mepa_rc lan80xx_macsec_rx_sc_update_priv(mepa_device_t                  *dev,
                                         const mepa_macsec_port_t       port,
                                         const mepa_macsec_sci_t        *const sci,
                                         const mepa_macsec_rx_sc_conf_t *const conf);

mepa_rc lan80xx_macsec_rx_sc_get_conf_priv(mepa_device_t                  *dev,
                                           const mepa_macsec_port_t       port,
                                           const mepa_macsec_sci_t        *const sci,
                                           mepa_macsec_rx_sc_conf_t       *const conf);

mepa_rc lan80xx_macsec_rx_sc_status_get_priv(mepa_device_t *dev,
                                             const mepa_macsec_port_t        port,
                                             const mepa_macsec_sci_t         *const sci,
                                             mepa_macsec_rx_sc_status_t      *const status);


mepa_rc lan80xx_macsec_port_enable_status_get_priv(mepa_device_t *dev, const mepa_port_no_t  port_no, mepa_bool_t  *status);

mepa_rc lan80xx_macsec_event_xpn_seq_threshold_set_priv(mepa_device_t        *dev,
                                                        const mepa_port_no_t port_no,
                                                        const u64            threshold);

mepa_rc lan80xx_macsec_event_xpn_seq_threshold_get_priv(mepa_device_t        *dev,
                                                        const mepa_port_no_t port_no,
                                                        u64                  *threshold);
#endif //_MEPA_LAN80XX_MACSEC_H
