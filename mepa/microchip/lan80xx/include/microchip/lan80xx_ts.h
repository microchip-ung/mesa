// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/* PTP public header with chip specific data structures and APIs */

#ifndef LAN80XX_TS_H_
#define LAN80XX_TS_H_

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>

/**
 * \brief PHY timestamp in seconds and nanoseconds (11 bytes Timestamp)
 **/
typedef struct {
    struct {
        uint16_t    high; /**< bits 32-47 of 48-bit second */
        uint32_t    low;  /**< bits 0-31 of 48-bit second */
    } seconds;             /**< 6 bytes second part of Timestamp */
    uint32_t        nanoseconds; /**< 4 bytes nano-sec part of Timestamp */
    uint8_t         subnanoseconds; /**< 1 bytes sub-nano-sec part of Timestamp */
} phy25g_phy_timestamp_t;

/**
 * \brief parameter describing various Tx TSFIFO status.
 **/
typedef enum {
    LAN80XX_PHY_TS_FIFO_SUCCESS,  /**< FIFO read success */
    LAN80XX_PHY_TS_FIFO_OVERFLOW, /**< FIFO overflow */
} phy25g_ts_fifo_status_t;

/**
 * \brief Frame signature mask
**/
typedef u32 phy25g_ts_fifo_sig_mask_t;



/**
 * \brief Defines Tx TSFIFO signature length.
 **/
#define LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN         (11U)
#define LAN80XX_PHY_TS_SIG_SOURCE_PORT_ID_LEN     (10U)
#define LAN80XX_PHY_TS_SIG_SEQUENCE_ID_LEN        (2U)
#define LAN80XX_PHY_TS_SIG_DEST_IP_LEN            (4U)
#define LAN80XX_PHY_TS_SIG_SRC_IP_LEN             (4U)
#define LAN80XX_PHY_TS_SIG_DEST_MAC_LEN           (6U)

/**
 * \brief Defines Tx TSFIFO signature mask.
 **/
#define LAN80XX_PHY_TS_FIFO_SIG_SRC_IP            (0x01U)  /**< Src IP address: inner IP for IP-over-IP */
#define LAN80XX_PHY_TS_FIFO_SIG_DEST_IP           (0x02U)  /**< Dest IP address */
#define LAN80XX_PHY_TS_FIFO_SIG_MSG_TYPE          (0x04U)  /**< Message type */
#define LAN80XX_PHY_TS_FIFO_SIG_DOMAIN_NUM        (0x08U)  /**< Domain number */
#define LAN80XX_PHY_TS_FIFO_SIG_SOURCE_PORT_ID    (0x10U)  /**< Source port identity */
#define LAN80XX_PHY_TS_FIFO_SIG_SEQ_ID            (0x20U)  /**< PTP frame Sequence ID */
#define LAN80XX_PHY_TS_FIFO_SIG_DEST_MAC          (0x40U)  /**< Dest MAC address */

#define LAN80XX_PTP_SIGNATURE_LEN                 (28U)
/**
 * \brief Tx TSFIFO entry signature
 **/
typedef struct {
    phy25g_ts_fifo_sig_mask_t  sig_mask;  /**< valid signature fields */
    u8        msg_type;              /**< PTP message type */
    u8        domain_num;            /**< domain number in PTP message */
    u8        src_port_identity[10]; /**< source port identity in PTP message */
    u16       sequence_id;           /**< PTP message sequence ID */
    u32       dest_ip;               /**< Destination IP */
    u32       src_ip;                /**< Source IP */
    u8        dest_mac[6];           /**< Destination MAC */
    u32       dest_ipv6_addr[4]; /**< IPv6 Address */
    u32       src_ipv6_addr[4]; /**<IPv6 Mask */
} phy25g_ts_fifo_sig_t;

/**
 * \brief TSFIFO ts entry.
 **/
typedef struct {
    phy25g_ts_fifo_sig_t sig;
    phy25g_phy_timestamp_t ts;
} phy25g_ts_fifo_entry_t;


/**
 * \brief MPLS level range
 **/
typedef struct {
    u32    lower; /**< lower range value */
    u32    upper; /**< upper range value */
    u8     match_mode;/*Label match mode for the label */
} phy25g_ts_mpls_lvl_rng_t;


/** \brief MPLS per flow configuration */
typedef struct {
    BOOL                         flow_en;  /**< flow enable/disable */

    u8                           stack_depth; /**< depth of MPLS level; multiple depth match can be possible using OR */

    mepa_ts_mpls_parse_t         stack_ref_point; /**< Search direction for label matching: top to bottom or bottom to top */
    union {
        struct {
            phy25g_ts_mpls_lvl_rng_t  top; /**< Top level */
            phy25g_ts_mpls_lvl_rng_t  frst_lvl_after_top; /**< First label after the top label */
            phy25g_ts_mpls_lvl_rng_t  snd_lvl_after_top; /**< Second label after the top label */
            phy25g_ts_mpls_lvl_rng_t  thrd_lvl_after_top; /**< Third label after the top label */
        } top_down; /**< Top down configuration */
        struct {
            phy25g_ts_mpls_lvl_rng_t  end; /**< End level */
            phy25g_ts_mpls_lvl_rng_t  frst_lvl_before_end; /**< First label before the end label */
            phy25g_ts_mpls_lvl_rng_t  snd_lvl_before_end; /**< Second label before the end label */
            phy25g_ts_mpls_lvl_rng_t  thrd_lvl_before_end; /**< Third label before the end label */
        } bottom_up; /**< Bottom up configuration */
    } stack_level; /**< 4 level values; top_down or bottom_up depends on stack_ref_point */
} phy25g_ts_mpls_flow_conf_t;

#  if 1
typedef struct {
    uint32_t   pps_pulse_width ;    /**< The value of nano second counter upto which 1PPS is held high*/
    uint32_t   pps_pulse_interval;
} phy25g_ts_pps_conf_t;
#endif

typedef enum {
    LAN80XX_PTP_SYNC_CLOCK_SELECT_LSC0,
    LAN80XX_PTP_SYNC_CLOCK_SELECT_LSC1,
    LAN80XX_PTP_SYNC_CLOCK_SELECT_LSC2,
    LAN80XX_PTP_SYNC_CLOCK_SELECT_LSC3,
    LAN80XX_PTP_ASYNC_NO_CLOCK,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK_DIV_2,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK_DIV_4,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK_DIV_5,
    LAN80XX_PTP_SYNC_L_S_REF_CLOCK_DIV_8,
} phy25g_ptp_lsc_sync_clock_t;


typedef enum {
    LAN80XX_PTP_LSC_ACTIVE_HIGH,
    LAN80XX_PTP_LSC_ACTIVE_LOW,
} phy25g_lsc_pin_polarity_t;


typedef enum {
    LAN80XX_PTP_ACTION_IMMEDIATE,
    LAN80XX_PTP_ACTION_ONE_SHOT_ON_ACTIVE_EDGE,
    LAN80XX_PTP_ACTION_RESERVED,
    LAN80XX_PTP_ACTION_CONTINUOUS,
} phy25g_pps_action_t;

typedef enum {
    LAN80XX_PTP_LSC_PIN_0,
    LAN80XX_PTP_LSC_PIN_1,
    LAN80XX_PTP_LSC_PIN_2,
    LAN80XX_PTP_LSC_PIN_3,
} phy25g_lsc_pin_sel_t;

typedef struct {
    phy25g_ptp_lsc_sync_clock_t      clk_select;
    phy25g_lsc_pin_polarity_t        pin_inv_pol;
    phy25g_pps_action_t              pin_sync_mode;//00:Load immediate 01:excute on active edge on pin 11:action repeate at next active edge.
    phy25g_lsc_pin_sel_t             lsc_select;   //LSC Pin select.
} phy25g_pps_input_conf_t;


typedef enum {
    LAN80XX_PTP_LSC_SQUARE_WAVEFORM,
    LAN80XX_PTP_LSC_1PPS,
    LAN80XX_PTP_NSEC_BIT_OUT,
} phy25g_lsc_output_sync_t;

typedef struct {
    phy25g_ptp_lsc_sync_clock_t   clk_select;         /**< Sync or Async */
    phy25g_lsc_pin_polarity_t     pin_inv_pol;
    phy25g_lsc_output_sync_t      pin_sync_mode;      /**< Waveform or 1PPS */
    uint32_t                      pps_pulse_high ;    /**< Pulse or waveform high width in NSEC*/
    uint32_t                      pps_pulse_low;      /**< Waveform low width or 1PPS Pulse start boundary in NSEC */
    phy25g_lsc_pin_sel_t          lsc_select;         /**< LSC Pin select */
} phy25g_pps_output_conf_t;


typedef struct {
    uint32_t one_sec_wait_period_cfg;
    uint32_t one_microsec_period_cfg;
} phy25g_ts_sertod_Load_period_cfg;


typedef struct {

    uint8_t      pin_select;
    mepa_bool_t  pin_inv_pol;
    uint8_t      pin_sync_mode;//immediate, one short, continuous.

    mepa_bool_t load_enable;    /**< Serial ToD Input Enable */
    mepa_bool_t store_enable;    /**< Serial ToD Output Enable */
    mepa_bool_t msb_byte_first;
    mepa_bool_t msb_bit_first;
    uint8_t     ls_unit_sel;
    phy25g_ts_sertod_Load_period_cfg Ld_period_cfg;
} phy25g_ts_sertod_input_conf_t;

typedef struct {

    uint8_t      pin_select;
    mepa_bool_t  pin_inv_pol;
    uint8_t      pin_sync_mode;//immediate, one short, continuous.

    mepa_bool_t msb_byte_first;
    mepa_bool_t msb_bit_first;
    uint32_t  pin_wfh_period;
    uint32_t  pin_wfl_period;
} phy25g_ts_sertod_output_conf_t;


typedef struct {

    uint8_t      clk_select;
    uint8_t      pin_sync_mode;//immediate, one short, continuous.
    uint8_t      epps_event_detect_adjust;
    uint8_t      lsc_select;
} phy25g_ts_epps_conf_t;

typedef struct {

    int32_t nanoseconds; /**< 4 bytes nano-sec part of Timestamp */
    int8_t  subnanoseconds;
    uint8_t lsc_select;
} phy25g_ts_ltc_delta_adj_cfg;



/**
 * \brief Analyzer supported frame encapsulation type
 **/
typedef enum {
    /* PTP encap */
    LAN80XX_PHY_TS_ENCAP_ETH_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_IP_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_ETH_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_ETH_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_MPLS_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_NONE,
} phy25g_ts_encap_t;


typedef struct {
    u32     enable;
} phy25g_ts_tx_classifier_conf_t;





typedef void (*lan80xx_phy_ts_fifo_read)(mepa_device_t *dev,
                                         const mepa_port_no_t port_no,
                                         const phy25g_phy_timestamp_t *const ts,
                                         const phy25g_ts_fifo_sig_t   *const sig,
                                         void                           *cntxt,
                                         const phy25g_ts_fifo_status_t status);


/**
 * \brief callback of TSFIFO .
 **/

/**
 * \brief Install callback to read data (signature + timestamp) from Tx TSFIFO.
 * \note Registered callback will be called for each entry in TSFIFO from
 *  lan80xx_phy_ts_fifo_empty function.
 *
 * \param dev  [IN]             mepa driver
 * \param rd_cb [IN]            read callback
 * \param cntxt [IN]            context to be returned in callback
 *
 * \return Return code.
 **/

mepa_rc lan80xx_phy_ts_fifo_read_install( mepa_device_t *dev,
                                          lan80xx_phy_ts_fifo_read  rd_cb,
                                          void                   *cntxt);

/**
 * \brief Read timestamp from Tx TSFIFO.
 * \note Application will call this function upon receipt of a signal for
 *  timestamp in FIFO.
 *
 * \param dev [IN]             mepa driver
 * \param port_no [IN]         port number
 * \param ts_list[]            Array if ts is needed in array else can be null.
 * \param num                  index of array
 * \param callback             boolean to indicate callback is given or not
 * \return Return code.
 **/
mepa_rc lan80xx_phy_ts_fifo_empty( mepa_device_t *dev,
                                   const mepa_port_no_t    port_no,
                                   phy25g_ts_fifo_entry_t ts_list[],
                                   uint32_t                 *const num,
                                   BOOL                     callback);

mepa_rc lan80xx_phy_ts_fifo_get(mepa_device_t *dev, const mepa_port_no_t    port_no,
                                phy25g_ts_fifo_entry_t ts_list[], const size_t   size, uint32_t   *const num);

/**
 * \brief Link up latency in 1588 engine.
 * \note To set the Link up latency in the 1588 engine
 * \param dev [IN]             mepa driver
*/
mepa_rc lan80xx_linkup_delay(mepa_device_t *dev);


/**
 *brief configure TS FIFO frame signature mask.
 * \param dev[IN]                   mepa driver
 * \param port_no [IN]              port number
 * \phy25g_ts_fifo_sig_mask_t[IN]   mask for the frame signature field.
*/
mepa_rc lan80xx_phy_ts_fifo_sig_set(mepa_device_t *dev, const mepa_port_no_t  port_no,
                                    const phy25g_ts_fifo_sig_mask_t sig_mask);

/**
 * \brief configure LSC pin config for LS controller.
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \param phy25g_onepps_Input_cfg LSC pin config paramter.
*/
mepa_rc lan80xx_phy_ts_pps_input_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_pps_input_conf_t *const pin_conf);

/**
 * \brief configure serial tod input interface config .
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \param phy25g_ts_sertod_conf_t serial tod input parameter config.
*/
mepa_rc lan80xx_phy_ts_sertod_input_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_sertod_input_conf_t *const sertod_conf);


/**
 * \brief configure EPPS configuration inputs.
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \phy25g_ts_epps_conf_t   epps config paramter.
*/
mepa_rc lan80xx_phy_ts_epps_conf_set(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_epps_conf_t *const epps_conf);


/**
 * \brief configure PTP TOD Delta config .
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \phy25g_ts_ltc_delta_adj_cfg   TOD delta config paramter.
*/

mepa_rc lan80xx_phy_ts_ptptime_adj_delta(mepa_device_t  *dev, const mepa_port_no_t  port_no, phy25g_ts_ltc_delta_adj_cfg *const phy25g_ltc_tod_adj);

/**
 * \brief configure serial tod output interface config.
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \param phy25g_ts_sertod_conf_t serial tod output parameter config.
*/
mepa_rc lan80xx_phy_ts_sertod_output_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_sertod_output_conf_t *const sertod_conf);

/**
 * \brief configure LSC pin output config for LS controller.
 * * \param dev [IN]            mepa driver
 * \param port_no               port number
 * \param phy25g_onepps_Input_cfg LSC pin output config paramter.
*/
mepa_rc lan80xx_phy_ts_pps_ouput_conf_set(mepa_device_t *dev, const mepa_port_no_t  port_no, const phy25g_pps_output_conf_t *const pps_out_conf);

#endif
