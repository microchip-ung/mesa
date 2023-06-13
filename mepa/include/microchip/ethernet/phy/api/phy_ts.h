// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_TS_API_H_
#define _MEPA_TS_API_H_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

/** \brief  Time interval in ns 1<<16
 *   range +-2**47 ns = 140737 sec = 39 hours
 *   For example, 2.5 ns is expressed as 0x0000.0000.0002.8000
 **/
typedef int64_t mepa_timeinterval_t;

/** \brief  PHY timestamp in seconds and nanoseconds (10 bytes Timestamp) */
typedef struct {
    struct {
        uint16_t high;  /**< bits 32-47 of 48-bit second */
        uint32_t low;   /**< bits 0-31 of 48-bit second */
    } seconds;          /**< 6 bytes second part of Timestamp */
    uint32_t nanoseconds; /**< 4 bytes nano-sec part of Timestamp */
} mepa_timestamp_t;

/** \brief PPS Configuration */
typedef struct {
    uint32_t   pps_width_adj ;    /**< The value of nano second counter upto which 1PPS is held high */
    uint32_t   pps_offset;        /**< PPS pulse offset in nano seconds */
    uint32_t   pps_output_enable; /**< PPS pulse output is enabled for this port */
} mepa_ts_pps_conf_t;

/** \brief  Timestamp block clock frequencies */
typedef enum {
    MEPA_TS_CLOCK_FREQ_125M,   /**< 125 MHz */
    MEPA_TS_CLOCK_FREQ_15625M, /**< 156.25 MHz */
    MEPA_TS_CLOCK_FREQ_200M,   /**< 200 MHz */
    MEPA_TS_CLOCK_FREQ_250M,   /**< 250 MHz */
    MEPA_TS_CLOCK_FREQ_500M,   /**< 500 MHz */
    MEPA_TS_CLOCK_FREQ_MAX,    /**< MAX Freq */
} mepa_ts_clock_freq_t;

/** \brief Rx Timestamp position inside PTP frame */
typedef enum {
    MEPA_TS_RX_TIMESTAMP_POS_IN_PTP, /**< Rx timestamp in Reserved 4 bytes of PTP header */
    MEPA_TS_RX_TIMESTAMP_POS_AT_END, /**< Shrink Preamble by 4 bytes and append 4 bytes at the end of frame */
} mepa_ts_rx_timestamp_pos_t;

/** \brief  RX Timestamp length in PTP header reserved field, 30bit or 32bit */
typedef enum {
    MEPA_TS_RX_TIMESTAMP_LEN_30BIT, /**< The nanosecCounter i.e. [0..999999999] */
    MEPA_TS_RX_TIMESTAMP_LEN_32BIT, /**< nanosecCounter + secCounter*10^9 */
} mepa_ts_rx_timestamp_len_t;

/** \brief Defines Tx TSFIFO access mode. */
typedef enum {
    MEPA_TS_FIFO_MODE_NORMAL, /**< Timestamp can be read from normal CPU interface */
    MEPA_TS_FIFO_MODE_SPI,    /**< Timestamps are pushed out on the SPI interface */
} mepa_ts_fifo_mode_t;

/** \brief Length of Timestamp stored in Tx TSFIFO. */
typedef enum {
    MEPA_TS_FIFO_TIMESTAMP_LEN_4BYTE,  /**< 4 byte Tx timestamp */
    MEPA_TS_FIFO_TIMESTAMP_LEN_10BYTE, /**< 10 byte Tx timestamp */
} mepa_ts_fifo_timestamp_len_t;


/** \brief PTP Clock operational modes */
typedef enum {
    MEPA_TS_PTP_CLOCK_MODE_NONE,    /**< No active PTP clock */
    MEPA_TS_PTP_CLOCK_MODE_BC1STEP, /**< Ordinary/Boundary clock, 1 step */
    MEPA_TS_PTP_CLOCK_MODE_BC2STEP, /**< Ordinary/Boundary clock, 2 step */
    MEPA_TS_PTP_CLOCK_MODE_TC1STEP, /**< Transparent clock, 1 step */
    MEPA_TS_PTP_CLOCK_MODE_TC2STEP, /**< Transparent clock, 2 step */
} mepa_ts_ptp_clock_mode_t;

/** \brief PTP delay measurement method */
typedef enum {
    MEPA_TS_PTP_DELAYM_P2P, /**< Peer-to-Peer delay measurement method */
    MEPA_TS_PTP_DELAYM_E2E, /**< End-to-End delay measurement method */
} mepa_ts_ptp_delaym_type_t;

/** \brief Clock frequency ratio in scaled PartsPerBillion, defined as rate in units of ppb and multiplied by 2^16 */
/** \brief Example, 2.5 ppb is expressed as 0000 0000 0002 8000 */
typedef int64_t mepa_ts_scaled_ppb_t;

/** \brief Timestamp interrupt events */
#define MEPA_TS_INGR_ENGINE_ERR            0x01  /**< More than one engine find match */
#define MEPA_TS_INGR_RW_PREAM_ERR          0x02  /**< Preamble too short to append timestamp */
#define MEPA_TS_INGR_RW_FCS_ERR            0x04  /**< FCS error in ingress */
#define MEPA_TS_EGR_ENGINE_ERR             0x08  /**< More than one engine find match */
#define MEPA_TS_EGR_RW_FCS_ERR             0x10  /**< FCS error in egress */
#define MEPA_TS_EGR_TIMESTAMP_CAPTURED     0x20  /**< Timestamp captured in Tx TSFIFO */
#define MEPA_TS_EGR_FIFO_OVERFLOW          0x40  /**< Tx TSFIFO overflow */
#define MEPA_TS_DATA_IN_RSRVD_FIELD        0x80  /**< Data in reserved Field */
#define MEPA_TS_LTC_NEW_PPS_INTRPT         0x100 /**< New PPS pushed onto external PPS pin */
#define MEPA_TS_LTC_LOAD_SAVE_NEW_TOD      0x200 /**< New LTC value either loaded in to HW or saved into registers */

typedef uint32_t mepa_ts_event_t;   /** \brief Int events: Single event or 'OR' multiple events above */

/** \brief Timestamping Statistics. */
typedef struct {
    uint32_t    ingr_pream_shrink_err;/**< Frames with preambles too short to shrink */
    uint32_t    egr_pream_shrink_err; /**< Frames with preambles too short to shrink */
    uint32_t    ingr_fcs_err;         /**< Timestamp block received frame with FCS error in ingress */
    uint32_t    egr_fcs_err;          /**< Timestamp block received frame with FCS error in egress */
    uint32_t    ingr_frm_mod_cnt;     /**< No of frames modified by timestamp block (rewritter) in ingress */
    uint32_t    egr_frm_mod_cnt;      /**< No of frames modified by timestamp block (rewritter) in egress */
    uint32_t    ts_fifo_tx_cnt;       /**< the number of timestamps transmitted to the interface */
    uint32_t    ts_fifo_drop_cnt;     /**< Count of dropped Timestamps not enqueued to the Tx TSFIFO */
} mepa_ts_stats_t;

/** \brief Local TIME Counter Load/Save Enable commands */
typedef enum {
    MEPA_TS_CMD_LOAD,
    MEPA_TS_CMD_LOAD_ON_PPS,
    MEPA_TS_CMD_SAVE,
    MEPA_TS_ADJ_CMD_CLEAR,
} mepa_ts_ls_type_t;

/** \brief Clock input source */
typedef enum {
    MEPA_TS_CLOCK_SRC_EXTERNAL,   /**< External source */
    /** \brief 10G: XAUI lane 0 recovered clock, 1G: MAC RX clock (note: direction is opposite to 10G, i.e. PHY->MAC) */
    MEPA_TS_CLOCK_SRC_CLIENT_RX,
    /** \brief 10G: XAUI lane 0 recovered clock,1G: MAC TX clock (note:  direction is opposite to 10G, i.e. MAC->PHY)*/
    MEPA_TS_CLOCK_SRC_CLIENT_TX,
    MEPA_TS_CLOCK_SRC_INTERNAL,   /**< 10G: Invalid, 1G: Internal 250 MHz Clock */

    MEPA_TS_CLOCK_SRC_125MHZ_INTERNAL_SYS_PLL,
    MEPA_TS_CLOCK_SRC_125MHZ_QSGMII_REC_CLOCK,
    MEPA_TS_CLOCK_SRC_EXT_1588_REF_CLOCK,
    MEPA_TS_CLOCK_SRC_RESERVED,
    MEPA_TS_CLOCK_SRC_FROM_RX_PORT0,
    MEPA_TS_CLOCK_SRC_FROM_RX_PORT1,
    MEPA_TS_CLOCK_SRC_FROM_RX_PORT2,
    MEPA_TS_CLOCK_SRC_FROM_RX_PORT3,
} mepa_ts_clock_src_t;

/** \brief Correction Field update method */
typedef enum {
    MEPA_TS_TC_OP_MODE_A = 0, /**< RX_timestamp using reserved bytes or append at the end as defined in vtss_phy_ts_rxtimestamp_pos_t */
    MEPA_TS_TC_OP_MODE_B = 1, /**< Sub local time at ingress and add at egress from CF */
    MEPA_TS_TC_OP_MODE_C = 2, /**< Sub local time at ingress and add at egress from CF and use 48 bits in CF */
}mepa_ts_tc_op_mode_t;

/** \brief PHY timestamp unit initialization parameters */
typedef struct {
    mepa_ts_clock_freq_t          clk_freq;         /**< Reference clock frequency */
    mepa_ts_clock_src_t           clk_src;          /**< clock source */
    mepa_ts_rx_timestamp_pos_t    rx_ts_pos;        /**< Rx timestamp position */
    mepa_ts_rx_timestamp_len_t    rx_ts_len;        /**< Rx timestamp length */
    mepa_ts_fifo_mode_t           tx_fifo_mode;     /**< Tx TSFIFO access mode */
    mepa_ts_fifo_timestamp_len_t  tx_ts_len;        /**< Timestamp size in Tx TSFIFO */
    mepa_bool_t                   tx_fifo_spi_conf; /**< If Tx Timestamp can be read through SPI interface */
    mepa_bool_t                   auto_clear_ls;
    mepa_ts_tc_op_mode_t          tc_op_mode;       /**< TC operating mode */
    mepa_bool_t                   dly_req_recv_10byte_ts; /**< Store 10-byte ingress timestamp for delay request message. Used for auto delay req/response. */
    mepa_bool_t                   tx_auto_followup_ts; /**< If true, PHY will insert timestamp in follow-up message instead of generating interrupt to application. */
} mepa_ts_init_conf_t;

/** \brief PHY timestamp unit reset */
typedef struct {
    mepa_bool_t                   ltc_soft_reset; /**< Chip LTC will reset, configure through channel 0 */
    mepa_bool_t                   ltc_hard_reset; /**< Chip LTC will reset, configure through channel 0 */
    mepa_bool_t                   tsu_soft_reset; /**< Per port TSU block hard reset */
    mepa_bool_t                   tsu_hard_reset; /**< Per port TSU block hard reset */
} mepa_ts_reset_conf_t;

/** \brief PTP packet encapsuations supported */
typedef enum {
    MEPA_TS_ENCAP_NONE,
    MEPA_TS_ENCAP_ETH_PTP,
    MEPA_TS_ENCAP_ETH_IP_PTP
} mepa_ts_pkt_encap_t;

/** \brief Match PTP Packet MAC types */
typedef enum {
    MEPA_TS_ETH_ADDR_MATCH_ANY,
    MEPA_TS_ETH_ADDR_MATCH_48BIT,
    MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST,
    MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST,
} mepa_ts_mac_match_mode_t;

/** \brief PTP packet MAC selection */
typedef enum {
    MEPA_TS_ETH_MATCH_NONE,
    MEPA_TS_ETH_MATCH_DEST_ADDR,
    MEPA_TS_ETH_MATCH_SRC_ADDR,
    MEPA_TS_ETH_MATCH_SRC_OR_DEST,
} mepa_ts_mac_match_select_t;

/** \brief PTP packet IP versions */
typedef enum {
    MEPA_TS_IP_VER_4,
    MEPA_TS_IP_VER_6,
} mepa_ts_ip_ver_t;

/** \brief PTP packet IP selection */
typedef enum {
    MEPA_TS_IP_MATCH_NONE,
    MEPA_TS_IP_MATCH_DEST,
    MEPA_TS_IP_MATCH_SRC,
    MEPA_TS_IP_MATCH_SRC_OR_DEST,
} mepa_ts_ip_match_select_t;

/** \brief IPV6 network address */
typedef struct {
    uint32_t   addr;
    uint32_t   mask;
} mepa_ipv4_network_t;

/** \brief IPV6 network address */
typedef struct {
    uint32_t     addr[4];
    uint32_t     mask[4];
} mepa_ipv6_network_t;

/** \brief IPv4/IPv6 address to be matched */
typedef union {
    mepa_ipv4_network_t ipv4;
    mepa_ipv6_network_t ipv6;
} mepa_ts_ip_network_t;

/** \brief Local TIME Counter Load/Save Enable commands */
typedef enum {
    MEPA_TS_MATCH_MODE_RANGE,
    MEPA_TS_MATCH_MODE_VALUE,
} mepa_ts_match_mode_t;

/** \brief  VSC_phy note : In VSC phys, The udp fields udp_sport_en, udp_dport_en, udp_sport, udp_dport are shared by all the flows of engine.
 *   IP header classifier configuration
 **/
typedef struct {
    mepa_ts_ip_ver_t                ip_ver;
    mepa_ts_ip_match_select_t       ip_match_mode;  /**<  match src, dest or either IP address */
    mepa_ts_ip_network_t            ip_addr;
    mepa_bool_t                     udp_sport_en;   /**<  UDP Source port check enable */
    mepa_bool_t                     udp_dport_en;   /**<  UDP Dest port check enable */
    uint16_t                        udp_sport;
    uint16_t                        udp_dport;
} mepa_ts_classifier_ip_t;

typedef struct {
    uint16_t    upper;
    uint16_t    lower;
} mepa_range_unit16_t;
typedef struct {
    uint16_t    val;
    uint16_t    mask;
} mepa_value_unit16_t;
typedef union {
    mepa_range_unit16_t      range;
    mepa_value_unit16_t      value;
} mepa_range_value_unit16_t;

typedef struct {
    mepa_ts_match_mode_t        mode;
    mepa_range_value_unit16_t   match;
} mepa_ts_match_uint16_t;

typedef struct {
    uint8_t     upper;
    uint8_t     lower;
} mepa_range_unit8_t;

typedef struct {
    uint8_t    val;
    uint8_t    mask;
} mepa_value_unit8_t;
typedef union {
    mepa_range_unit8_t      range;
    mepa_value_unit8_t      value;
} mepa_range_value_unit8_t;

typedef struct {
    mepa_ts_match_mode_t        mode;  /**< Range/Value with Mask */
    mepa_range_value_unit8_t    match; /**< values of Range/Value with Mask */
} mepa_ts_match_uint8_t;

/** \brief VSC_phy note : In VSC phys, The fields pbb_en, tpid, etype are shared by all the flows of engine. */
typedef struct {
    mepa_bool_t                 pbb_en;     /**< PBB tag present */
    uint16_t                    tpid;       /**< VLAN TPID for S or B-tag */
    uint16_t                    etype;      /**< The value of Ether type to be checked if Ethertype/length field is an Ethertype */
    uint8_t                     num_tag;    /**< No of VLAN Tags (max 2 tag) */
    mepa_ts_match_uint16_t      outer_tag;
    mepa_ts_match_uint16_t      inner_tag;
} mepa_ts_vlan_conf_t; /**< ETH configuration */

/** \brief Ethernet Header classification parameters */
typedef struct {
    mepa_ts_mac_match_mode_t    mac_match_mode;     /**< Complete 48bit MAC / Any Unicast MAC / Any Multicast MAC */
    mepa_ts_mac_match_select_t  mac_match_select;   /**< Src MAC or Dest MAC addr to be matched */
    uint8_t                     mac_addr[6];        /**< 48bit MAC addr to be matched, src or dest */
    mepa_bool_t                 vlan_check;         /**< TRUE=>verify configured VLAN tag configuration, FALSE=>parse VLAN tag if any */
    mepa_ts_vlan_conf_t         vlan_conf;          /**< VLAN configuration */
} mepa_ts_classifier_eth_t;


/** \brief PTP header classifier */
typedef struct {
    mepa_range_unit8_t          version;
    mepa_range_unit8_t          minor_version;
    mepa_ts_match_uint8_t       domain;
    mepa_ts_match_uint8_t       sdoid;
} mepa_ts_classifier_ptp_t;

/** \brief VSC_phy note : In VSC phys, all flows of engine share 2 clocks of corresponding engine. Flows [0-7] share clock-ids {0,1}, flows [8-15] share clock-ids {2,3} *  , flows [16-24] use {4,5} clocks.
 *   PTP packet classifier configuration parameters */
typedef struct {
    mepa_bool_t                     enable;
    mepa_ts_pkt_encap_t             pkt_encap_type;     /**< packet encap type: ETH/PTP, ETH/IP/PTP */
    uint16_t                        clock_id;           /**< clock id to be used by this flow. This is for validation purpose only in vsc phys. Refer VSC_phy note above. */
    mepa_ts_classifier_eth_t        eth_class_conf;
    mepa_ts_classifier_ip_t         ip_class_conf;
} mepa_ts_classifier_t;

typedef enum {
    MEPA_TS_CF_METHOD_RSVD          = 0, /**< Ingress time stored reserved bytes */
    MEPA_TS_CF_METHOD_SUB_ADD       = 1, /**< Sub local time at ingress and add at egress from CF */
    MEPA_TS_CF_METHOD_SUB_ADD_48B   = 2, /**< Sub local time at ingress and add at egress from CF and use 48 bits in CF */
} mepa_ts_cf_method_t;

/** \brief PTP Clock configuration parameters */
typedef struct {
    mepa_bool_t               enable;
    mepa_ts_classifier_ptp_t  ptp_class_conf;
    mepa_ts_ptp_clock_mode_t  clk_mode;     /**< clock mode: bc1step, bc2step, tc1step or tc2step */
    mepa_ts_ptp_delaym_type_t delaym_type;  /**< delay measurement method: P2P, E2E */
    mepa_bool_t               cf_update;    /**< correction field update for bc1step */
} mepa_ts_ptp_clock_conf_t;

/** \brief  TS FIFO signature entry */
typedef struct {
    uint8_t                     msg_type;              /**< PTP message type */
    uint8_t                     domain_num;            /**< domain number in PTP message */
    uint8_t                     src_port_identity[10]; /**< source port identity in PTP message */
    uint16_t                    sequence_id;           /**< PTP message sequence ID */
    uint16_t                    crc_src_port;          /**< 12-bit CRC of source port identity. */
    mepa_bool_t                 has_crc_src;           /**< true if the phy returns CRC-12 of source port identity in crc_src_port field. False if Source port identity is filled in src_port_identity field. Set to true for Lan8814 and false for VSC phys. */
} mepa_ts_fifo_sig_t;

/** \brief TS FIFO status */
typedef enum {
    MEPA_TS_FIFO_SUCCESS,
    MEPA_TS_FIFO_OVERFLOW,
} mepa_ts_fifo_status_t;

#define MEPA_TS_FIFO_MAX_ENTRIES 8 //In all existing phys, maximum number of FIFO entries is 8.
typedef struct {
    mepa_ts_fifo_sig_t sig;
    mepa_timestamp_t ts;
} mepa_fifo_ts_entry_t;

/** \brief PTP Sample tests */
typedef struct {
    uint8_t                         test_id;
    mepa_ts_pkt_encap_t             pkt_encap_type;     /**< packet encap type: ETH/PTP, ETH/IP/PTP */
    mepa_ts_ptp_clock_mode_t        clk_mode;           /**< clock mode: bc1step, bc2step, tc1step or tc2step */
    mepa_ts_ptp_delaym_type_t       delaym_type;        /**< delay measurement method: P2P, E2E */
} mepa_ts_sample_conf_t;

/**
 * \brief Enable/Disable the timestamp block (Mode:TSU in Bypass mode).
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [IN] Enable/Disable the timestamp block.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_mode_set(struct mepa_device                   *dev,
                         const mepa_bool_t                    enable);

/**
 * \brief Enable/Disable the timestamp block (Mode:TSU in Bypass mode).
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [OUT] Enable/Disable the timestamp block.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_mode_get(struct mepa_device                   *dev,
                         mepa_bool_t                          *const enable);

/**
 * \brief Reset the timestamp block
 *
 * \param dev   [IN] Driver instance.
 * \param reset [IN] Reset configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not support.\n
 *   MEPA_RC_OK on success.
 **/
mepa_rc mepa_ts_reset(struct mepa_device                      *dev,
                      const mepa_ts_reset_conf_t              *const reset);

/**
 * \brief Initialize the timestamp block
 *
 * \param dev  [IN]  Driver instance.
 * \param conf [IN]  Initialization parameters
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not support.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_init_conf_set(struct mepa_device              *dev,
                              const mepa_ts_init_conf_t       *const conf);

/**
 * \brief Initialize the timestamp block
 *
 * \param dev  [IN]  Driver instance.
 * \param conf [OUT] Initialization parameters.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_init_conf_get(struct mepa_device              *dev,
                              mepa_ts_init_conf_t             *const conf);

/**
 * \brief Timestamp Load/Save enable
 *
 * \param dev  [IN] Driver instance.
 * \param type [IN] LTC Load/Save Enable commands.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_ltc_ls_en(struct mepa_device                  *dev,
                          mepa_ts_ls_type_t                    const type);

/**
 * \brief Get the Local Time counter.
 *
 * \param dev [IN]  Driver instance.
 * \param ts  [OUT] PHY timestamp in seconds and nanoseconds.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_ltc_get(struct mepa_device                    *dev,
                        mepa_timestamp_t                      *const ts);

/**
 * \brief Set the Local Time counter.
 *
 * \param dev [IN]  Driver instance.
 * \param ts  [IN]  Local time counter.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_ltc_set(struct mepa_device                    *dev,
                        const mepa_timestamp_t                *const ts);

/**
 * \brief Get the delay asymmetry
 *
 * \param dev   [IN]  Driver instance.
 * \param delay [OUT] Delay asymmetry.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_delay_asymmetry_get(struct mepa_device        *dev,
                                    mepa_timeinterval_t       *const delay);

/**
 * \brief Set the delay asymmetry
 *
 * \param dev   [IN]  Driver instance.
 * \param delay [IN]  Delay asymmetry.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_delay_asymmetry_set(struct mepa_device        *dev,
                                    const mepa_timeinterval_t *const delay);

/**
 * \brief Get the path delay
 *
 * \param dev   [IN]  Driver instance.
 * \param delay [OUT] Path delay.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_path_delay_get(struct mepa_device             *dev,
                               mepa_timeinterval_t            *const delay);

/**
 * \brief Set the path delay
 *
 * \param dev   [IN]  Driver instance.
 * \param delay [IN]  Path delay.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_path_delay_set(struct mepa_device *dev,
                               const mepa_timeinterval_t      *const delay);

/**
 * \brief Get egress latency values, 48bit nanosec +16bit sub-nanosec
 *
 * \param dev     [IN]  Driver instance.
 * \param latency [OUT] Egress latency value.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_egress_latency_get(struct mepa_device         *dev,
                                   mepa_timeinterval_t        *const latency);

/**
 * \brief Set egress latency values, 48bit nanosec +16bit sub-nanosec
 *
 * \param dev     [IN] Driver instance.
 * \param latency [IN] Egress latency.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_egress_latency_set(struct mepa_device         *dev,
                                   const mepa_timeinterval_t  *const latency);

/**
 * \brief Get ingress latency values, 48bit nanosec +16bit sub-nanosec
 *
 * \param dev     [IN]  Driver instance.
 * \param latency [OUT] Ingress Latency.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_ingress_latency_get(struct mepa_device        *dev,
                                    mepa_timeinterval_t       *const latency);

/**
 * \brief Set ingress latency values, 48bit nanosec +16bit sub-nanosec
 *
 * \param dev     [IN]  Driver instance.
 * \param latency [IN]  Ingress latency.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_ingress_latency_set(struct mepa_device        *dev,
                                    const mepa_timeinterval_t *const latency);

/**
 * \brief Get the clock rate adjustment value, frequency offset in units of scaled ppb.
 *
 * \param dev     [IN]  Driver instance.
 * \param rateadj [OUT] Ingress latency.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_clock_rateadj_get(struct mepa_device          *dev,
                                  mepa_ts_scaled_ppb_t        *const rateadj);

/**
 * \brief Clock frequency ratio in scaled PartsPerBillion.
 *
 * \param dev     [IN] Driver instance.
 * \param rateadj [IN] Clock rate adjustment.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_clock_rateadj_set(struct mepa_device          *dev,
                                  const mepa_ts_scaled_ppb_t  *const rateadj);

/**
 * \brief Get Adjust LTC with one NS.
 *
 * \param dev  [IN] Driver instance.
 * \param incr [IN] Increament/Decreament.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_clock_adj1ns(struct mepa_device               *dev,
                             const mepa_bool_t                 incr);

/**
 * \brief Get PPS.
 *
 * \param dev          [IN]  Driver instance.
 * \param phy_pps_conf [OUT] PHY PPS Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_pps_conf_get(struct mepa_device               *dev,
                             mepa_ts_pps_conf_t               *const phy_pps_conf);

/**
 * \brief Set PPS.
 *
 * \param dev          [IN] Driver instance.
 * \param phy_pps_conf [IN] PHY PPS Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_pps_conf_set (struct mepa_device              *dev,
                              const mepa_ts_pps_conf_t        *const phy_pps_conf);


/**
 * \brief Get ingress PTP packet classifier configuration.
 *
 * \param dev        [IN]  Driver instance.
 * \param flow index [IN]  Flow index.
 * \param conf       [OUT] PTP packet Classifier configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_rx_classifier_conf_get(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       mepa_ts_classifier_t       *const conf);

/**
 * \brief Get egress PTP packet classifier configuration.
 *
 * \param dev        [IN]  Driver instance.
 * \param flow index [IN]  Flow index.
 * \param conf       [OUT] PTP packet Classifier configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_tx_classifier_conf_get(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       mepa_ts_classifier_t       *const conf);

/**
 * \brief Set ingress PTP packet classifier configuration.
 *
 * \param dev        [IN]  Driver instance.
 * \param flow index [IN]  Flow index.
 * \param conf       [IN]  PTP packet Classifier configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_rx_classifier_conf_set(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       const mepa_ts_classifier_t *const conf);

/**
 * \brief Set egress PTP packet classifier configuration.
 *
 * \param dev        [IN]  Driver instance.
 * \param flow index [IN]  Flow index.
 * \param conf       [IN]  PTP packet Classifier configuration.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not supported.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 *
 **/
mepa_rc mepa_ts_tx_classifier_conf_set(struct mepa_device         *dev,
                                       uint16_t                    flow_index,
                                       const mepa_ts_classifier_t *const conf);

/**
 * \brief Get ingress PTP clock configuration.
 *
 * \param dev      [IN]  Driver instance.
 * \param clock_id [IN]  Clock ID.
 * \param conf     [OUT] PTP Clock Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_rx_clock_conf_get(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  mepa_ts_ptp_clock_conf_t        *const conf);

/**
 * \brief Get egress PTP clock configuration.
 *
 * \param dev      [IN]  Driver instance.
 * \param clock_id [IN]  Clock ID.
 * \param conf     [OUT] PTP Clock Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_tx_clock_conf_get(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  mepa_ts_ptp_clock_conf_t        *const conf);

/**
 * \brief Set ingress  PTP clock configuration.
 *
 * \param dev      [IN] Driver instance.
 * \param clock_id [IN] Clock ID
 * \param conf     [IN] PTP Clock Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_rx_clock_conf_set(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  const mepa_ts_ptp_clock_conf_t  *const conf);

/**
 * \brief Set egress PTP clock configuration.
 *
 * \param dev      [IN] Driver instance.
 * \param clock_id [IN] Clock ID.
 * \param conf     [IN] PTP Clock Configuration.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_tx_clock_conf_set(struct mepa_device              *dev,
                                  uint16_t                         clock_id,
                                  const mepa_ts_ptp_clock_conf_t  *const conf);

/**
 * \brief Get statistics.
 *
 * \param dev  [IN]  Driver instance.
 * \param stat [OUT] Timestamp statistics.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_stats_get(struct mepa_device                    *dev,
                          mepa_ts_stats_t                       *const stat);

/**
 * \brief Set events
 *
 * \param dev     [IN] Driver instance.
 * \param enable  [IN] Interrupt enable.
 * \param ev_mask [IN] Timestamp interrupt events.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_event_set(struct mepa_device                      *dev,
                          const mepa_bool_t                        enable,
                          const mepa_ts_event_t                    ev_mask);

/**
 * \brief Get events.
 *
 * \param dev     [IN]  Driver instance.
 * \param ev_mask [OUT] Timestamp interrupt events.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_event_get(struct mepa_device                      *dev,
                          mepa_ts_event_t                         *const ev_mask);

/**
 * \brief Polling function for TS events.
 *
 * \param dev    [IN]  Driver instance.
 * \param status [OUT] Timestamp interrupt events status.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_event_poll(struct mepa_device                     *dev,
                           mepa_ts_event_t                        *const status);

/**
 *  \brief Get FIFO timestamp entries.
 *
 *  \param port_no [IN]  Port number.
 *  \param ts_list [IN]  PHY FIFO timestamp list.
 *  \param size    [IN]  size of ts_list passed as input argument.
 *  \param num     [OUT] Number of Timestamp entries read from FIFO.
 *
 *  \return
 *       MEPA_RC_OK on success.\n
 *       MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_fifo_get(struct mepa_device   *dev,
                         mepa_fifo_ts_entry_t ts_list[],
                         const size_t         size,
                         uint32_t             *const num);

/** \brief callback after reading the timestamp FIFO entry */
typedef void (*mepa_ts_fifo_read_t)(mepa_port_no_t              port_no,
                                    const mepa_timestamp_t      *const ts,
                                    const mepa_ts_fifo_sig_t    *const sig,
                                    const mepa_ts_fifo_status_t status);

/**
 * \brief Install the callback function which will pass FIFO timestamp to application.
 *  cntxt refers to the arguments context needed by the callback function.
 *
 * \param dev   [IN]  Driver Instance.
 * \param rd_cb [OUT] Timestamp fifo read callback installation.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_fifo_read_install(struct mepa_device                 *dev,
                                  mepa_ts_fifo_read_t                 rd_cb);

/**
 * \brief Get all FIFO timestamp entries. Usually called after receiving timestamp captured interrupt.
 *
 * \param dev      [IN] Driver instance.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_fifo_empty(struct mepa_device                     *dev);

/**
 * \brief Sample Test configurations.
 *
 * \param dev      [IN]  Driver instance.
 * \param test_id  [IN]  Test ID.
 * \param reg_dump [IN]  Get register dump.
 *
 * \return
 *   MEPA_RC_NOT_IMPLEMENTED when not support.\n
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_ts_test_config(struct mepa_device                    *dev,
                            uint16_t                               test_id,
                            mepa_bool_t                            reg_dump);

#include <microchip/ethernet/hdr_end.h>
#endif /**< _MEPA_TS_API_H_ */
