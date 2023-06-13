// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_phy_api.h>

/**
 * \file
 * \brief PHY TimeStamping API
 * \details This header file describes PTP/OAM TimeStamping API functions
 */

#ifndef _VTSS_PHY_TS_API_H_
#define _VTSS_PHY_TS_API_H_

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \brief parameter for setting the alternative clock mode.
 */
/** \brief external clock output configuration. */
typedef struct vtss_phy_ts_alt_clock_mode_s {
    BOOL pps_ls_lpbk;       /**< output PPS is loopback to L/S input pin */
    BOOL ls_lpbk;           /**< L/S act as output pin at 1PPS */
    BOOL ls_pps_lpbk;       /**< L/S connected to PPS out */
} vtss_phy_ts_alt_clock_mode_t;

/**
 * \brief Get the latest saved nanosec counter from the alternative clock.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param saved [OUT]           latest saved value.
 *
 * \return Return code.
 */

vtss_rc vtss_phy_ts_alt_clock_saved_get(const vtss_inst_t inst,
                                        const vtss_port_no_t        port_no,
                                        u32 *const saved);

/**
 * \brief Get the alternative external clock mode.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]     port number
 * \param phy_alt_clock_mode [OUT]  alternative clock mode.
 *
 * \return Return code.
 */
vtss_rc vtss_phy_ts_alt_clock_mode_get(const vtss_inst_t inst,
                                       const vtss_port_no_t        port_no,
                                       vtss_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode);

/**
 * \brief Set the alternative clock mode.
 *  This function configures the loopbacks
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]     port number
 * \param phy_alt_clock_mode [IN]   alternative clock mode.
 *
 * \return Return code.
 */
vtss_rc vtss_phy_ts_alt_clock_mode_set(const vtss_inst_t inst,
                                       const vtss_port_no_t        port_no,
                                       const vtss_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode);

/**
 * \brief PPS Configuration
 **/
typedef struct vtss_phy_ts_pps_config_s {
    u32   pps_width_adj ;    /**< The value of nano second counter upto which 1PPS is held high*/
    u32   pps_offset;        /**< PPS pulse offset in nano seconds */
    u32   pps_output_enable; /**< PPS pulse output is enabled for this port */
} vtss_phy_ts_pps_conf_t;

/**
 * \brief  Set offset for the PPS generation.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param phy_pps_conf [IN]     pps configuration
 *
 * \return Return code.
 */
vtss_rc vtss_phy_ts_pps_conf_set(const vtss_inst_t inst,
                                 const vtss_port_no_t  port_no,
                                 const vtss_phy_ts_pps_conf_t *const phy_pps_conf);
/**
 * \brief  Get offset for the PPS generation.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param phy_pps_conf [OUT]    pps configuration
 *
 * \return Return code.
 */

vtss_rc vtss_phy_ts_pps_conf_get(const vtss_inst_t inst,
                                 const vtss_port_no_t  port_no,
                                 vtss_phy_ts_pps_conf_t *const phy_pps_conf);

/**
 * \brief Set the ingress latency.
 * \note Latency is taken as TimeInterval which is 48bit nanosec +
 *  16bit sub-nanosec though HW supports nanosec in the range 0 - 2^16.
 *
 * \param inst    [IN]      handle to an API instance
 * \param port_no [IN]      port number
 * \param latency [IN]      ingress latency
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_latency_set(const vtss_inst_t     inst,
                                        const vtss_port_no_t  port_no,
                                        const vtss_timeinterval_t    *const latency);

/**
 * \brief Get the ingress latency.
 *
 * \param inst    [IN]       handle to an API instance
 * \param port_no [IN]       port number
 * \param latency [OUT]      ingress latency
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_latency_get(const vtss_inst_t     inst,
                                        const vtss_port_no_t  port_no,
                                        vtss_timeinterval_t          *const latency);

/**
 * \brief Set the egress latency.
 * \note Latency is taken as TimeInterval which is 48bit nanosec +
 *  16bit sub-nanosec though HW supports nanosec in the range 0 - 2^16.
 *
 * \param inst    [IN]       handle to an API instance
 * \param port_no [IN]       port number
 * \param latency [IN]       egress latency
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_latency_set(const vtss_inst_t     inst,
                                       const vtss_port_no_t  port_no,
                                       const vtss_timeinterval_t    *const latency);

/**
 * \brief Get the egress latency.
 *
 * \param inst    [IN]      handle to an API instance
 * \param port_no [IN]      port number
 * \param latency [OUT]     egress latency
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_latency_get(const vtss_inst_t     inst,
                                       const vtss_port_no_t  port_no,
                                       vtss_timeinterval_t          *const latency);

/**
 * \brief Set the path delay.
 * \note Path delay is taken as TimeInterval which is 48bit nanosec +
 *  16bit sub-nanosec though HW supports nanosec in the range 0 - 2^32.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param path_delay [IN]       path delay (measured)
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_path_delay_set(const vtss_inst_t     inst,
                                   const vtss_port_no_t  port_no,
                                   const vtss_timeinterval_t    *const path_delay);

/**
 * \brief Get the path delay.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param path_delay [OUT]      path delay
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_path_delay_get(const vtss_inst_t     inst,
                                   const vtss_port_no_t  port_no,
                                   vtss_timeinterval_t          *const path_delay);

/**
 * \brief Set the delay asymmetry.
 * \note Asymmetry is taken as TimeInterval which is 48bit nanosec + 16bit
 *  sub-nanosec though HW supports scaled nanosec which is 16 bit nanosec + 
 *  16 bit sub-nanosec, i.e. the range is -2^15 (+2^15-2^-16).
 *
 * \param inst       [IN]      handle to an API instance
 * \param port_no    [IN]      port number
 * \param delay_asym [IN]      link delay asymmetry
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_delay_asymmetry_set(const vtss_inst_t    inst,
                                        const vtss_port_no_t port_no,
                                        const vtss_timeinterval_t   *const delay_asym);

/**
 * \brief Get the delay asymmetry.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param delay_asym [OUT]      link delay asymmetry
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_delay_asymmetry_get(const vtss_inst_t    inst,
                                        const vtss_port_no_t port_no,
                                        vtss_timeinterval_t         *const delay_asym);

/**
 * \brief PHY timestamp in seconds and nanoseconds (10 bytes Timestamp)
 **/
typedef struct {
    struct {
        u16    high; /**< bits 32-47 of 48-bit second */
        u32    low;  /**< bits 0-31 of 48-bit second */
    } seconds; /**< 6 bytes second part of Timestamp */
    u32        nanoseconds; /**< 4 bytes nano-sec part of Timestamp */
} vtss_phy_timestamp_t;


/**
 * \brief Set the current PTP time into the PHY.
 * \note Time to be set must be next pps time.
 *
 * \param inst    [IN]     handle to an API instance
 * \param port_no [IN]     port number
 * \param ts      [IN]     current PTP time
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ptptime_set(const vtss_inst_t           inst,
                                const vtss_port_no_t        port_no,
                                const vtss_phy_timestamp_t  *const ts);

/**
 * \brief Setting of the current PTP time into the PHY is completed.
 * \note This function should be called after the next pps after
 *  setting the next pps time.
 *
 * \param inst    [IN]     handle to an API instance.
 * \param port_no [IN]     port number
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ptptime_set_done(const vtss_inst_t     inst,
                                     const vtss_port_no_t  port_no);


/**
 * \brief Arm the local time of the PHY so that in next pps it can be read.
 * \note Once armed, in next pps it will load the local time and can be read
 *  using vtss_phy_ts_ptptime_get. Must call before get the local time of
 *  the PHY.
 *
 * \param inst    [IN]     handle to an API instance.
 * \param port_no [IN]     port number
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ptptime_arm(const vtss_inst_t     inst,
                                const vtss_port_no_t  port_no);

/**
 * \brief Get the armed PTP time from the PHY.
 *
 * \param inst    [IN]     handle to an API instance
 * \param port_no [IN]     port number
 * \param ts      [OUT]    local time in PHY
 *
 * \return Return code.  If the time has not been updated after the
 *  vtss_phy_ts_ptptime_arm function is called, it returns error.
 **/
vtss_rc vtss_phy_ts_ptptime_get(const vtss_inst_t     inst,
                                const vtss_port_no_t  port_no,
                                vtss_phy_timestamp_t  *const ts);
/**
 * \brief Get the PTP time from the PHY load registers.
 *
 * \param inst    [IN]     handle to an API instance
 * \param port_no [IN]     port number
 * \param ts      [OUT]    local time in PHY
 *
 * \return Return code.  If the time has not been updated after the
 *  vtss_phy_ts_ptptime_arm function is called, it returns error.
 **/
vtss_rc vtss_phy_ts_load_ptptime_get(const vtss_inst_t     inst,
                                     const vtss_port_no_t  port_no,
                                     vtss_phy_timestamp_t  *const ts);
/**
 * \brief PHY timestamp in seconds and nanoseconds (10 bytes Timestamp)
 **/
typedef struct {
    BOOL ip_enable;    /**< Serial ToD Input Enable */
    BOOL op_enable;    /**< Serial ToD Output Enable */
    BOOL ls_inv;       /**< Invert the polarity of Load Save */
} vtss_phy_ts_sertod_conf_t;

/**
 * \brief Set Enable/Disable Serial ToD.
 *
 * \param inst        [IN]     handle to an API instance
 * \param port_no     [IN]     port number
 * \param sertod_conf [IN]     configure Serial ToD input
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_sertod_set(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               const vtss_phy_ts_sertod_conf_t *const sertod_conf);

/**
 * \brief Get Enable/Disable Serial ToD.
 *
 * \param inst    [IN]        handle to an API instance
 * \param port_no [IN]        port number
 * \param sertod_conf [OUT]   Serial ToD configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_sertod_get(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               vtss_phy_ts_sertod_conf_t *const sertod_conf);
/**
 * \brief Set load pulse delay.
 *
 * \param inst        [IN]     handle to an API instance
 * \param port_no     [IN]     port number
 * \param delay       [IN]     delay value in nano seconds
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_loadpulse_delay_set(const vtss_inst_t inst,
                                        const vtss_port_no_t port_no,
                                        const u16 *const delay);
/**
 * \brief Get load pulse delay
 *
 * \param inst    [IN]        handle to an API instance
 * \param port_no [IN]        port number
 * \param delay   [OUT]       delay value in nano seconds
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_loadpulse_delay_get(const vtss_inst_t inst,
                                        const vtss_port_no_t port_no,
                                        u16 *const delay);

/**
 * \brief Data type defines the clock frequency ratio in scaled ppb
 * \note The frequency of the internal clock can be adjusted in units of
 * scaledPartsPerBillion, which is defined as the rate in units of ppb
 * and multiplied by 2^16 and contained in a signed 64 bit value.
 * For example, 2.5 ppb is expressed as 0000 0000 0002 8000
 **/
typedef i64 vtss_phy_ts_scaled_ppb_t;

/**
 * \brief Adjust the local clock rate.
 *
 * \param inst    [IN]     handle to an API instance.
 * \param port_no [IN]     port number
 * \param adj     [IN]     Clock ratio frequency offset in units of scaled ppb
 *                         (parts pr billion). ratio > 0 => clock runs faster.
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_clock_rateadj_set(const vtss_inst_t              inst,
                                      const vtss_port_no_t           port_no,
                                      const vtss_phy_ts_scaled_ppb_t *const adj);

/**
 * \brief Get the clock rate adjustment value.
 *
 * \param inst    [IN]     handle to an API instance.
 * \param port_no [IN]     port number
 * \param adj     [OUT]    Clock ratio frequency offset in scaled ppb.
 *                         ratio > 0 => clock runs faster
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_clock_rateadj_get(const vtss_inst_t         inst,
                                      const vtss_port_no_t      port_no,
                                      vtss_phy_ts_scaled_ppb_t  *const adj);
/**
 * \brief Increment/decrement the LTC clock value by 1 ns.
 *
 * \param inst    [IN]      handle to an API instance.
 * \param port_no [IN]      port number
 * \param incr    [IN]      increment/decrement: TRUE = incr, FALSE = decr
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ptptime_adj1ns(const vtss_inst_t     inst,
                                   const vtss_port_no_t  port_no,
                                   const BOOL            incr);
/**
 * \brief Subtract offset from the current time 
 *
 * \param inst    [IN]      handle to an API instance.
 * \param port_no [IN]      port number
 * \param offset  [IN]      offset in nano seconds
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_timeofday_offset_set(const vtss_inst_t     inst,
                                         const vtss_port_no_t  port_no,
                                         const i32   offset);

/**
 * \brief parameter describing various Tx TSFIFO status.
 **/
typedef enum {
    VTSS_PHY_TS_TODADJ_INPROGRESS,  /**< ToD Adjustment is in progress */
    VTSS_PHY_TS_TODADJ_DONE,        /**< ToD Adjustment is completed */
    VTSS_PHY_TS_TODADJ_FAIL,        /**< ToD Adjustment Failed */
} vtss_phy_ts_todadj_status_t;

/**
 * \brief Return the status of the LTC time adjustment
 *
 * \param inst               [IN]  handle to an API instance.
 * \param port_no            [IN]  port number
 * \param ongoing_adjustment [OUT] LTC offset operation status 
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ongoing_adjustment(const vtss_inst_t           inst,
                                       const vtss_port_no_t        port_no,
                                       vtss_phy_ts_todadj_status_t *const ongoing_adjustment);


/**
 * \brief Frequency systhesis pulse configuration
**/

typedef struct vtss_phy_ltc_freq_synth_s {
    BOOL  enable;               /**< Enable/Disable frequency synthesis pulse */
    u8    high_duty_cycle;      /**< Number of clock cycles pulse is high */
    u8    low_duty_cycle;       /**< Number of clock cycles pulse is low */
} vtss_phy_ltc_freq_synth_t ;

/**
 * \brief Return the status of the LTC time adjustment
 *
 * \param inst               [IN]  handle to an API instance.
 * \param port_no            [IN]  port number
 * \param ltc_freq_synthesis [IN]  Frequency synthesis pulse configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ltc_freq_synth_pulse_set(const vtss_inst_t inst,
                                             const vtss_port_no_t port_no,
                                             const vtss_phy_ltc_freq_synth_t *const ltc_freq_synthesis);

/**
 * \brief Return the status of the LTC time adjustment
 *
 * \param inst               [IN]  handle to an API instance.
 * \param port_no            [IN]  port number
 * \param ltc_freq_synthesis [OUT]  Frequency synthesis pulse configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ltc_freq_synth_pulse_get(const vtss_inst_t inst,
                                             const vtss_port_no_t port_no,
                                             vtss_phy_ltc_freq_synth_t *const ltc_freq_synthesis );

/** \brief SPI daisy chain configuration */
typedef struct {
    BOOL spi_daisy_input;    /**< Enable SPI daisy-chain input port */
    BOOL spi_daisy_output;   /**< Enable SPI daisy-chain output port */
} vtss_phy_daisy_chain_conf_t;
/**
 * \brief  configure the daisy chain for TS FIFO
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param daisy_chain [IN]   daisy-chaining configuration
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_daisy_conf_set(const vtss_inst_t                   inst,
                                   const vtss_port_no_t                port_no,
                                   const vtss_phy_daisy_chain_conf_t   *const daisy_chain);

/**
 * \brief getting the daisy chain for TS FIFO
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param daisy_chain [IN]   daisy-chaining configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_daisy_conf_get(const vtss_inst_t           inst,
                                   const vtss_port_no_t        port_no,
                                   vtss_phy_daisy_chain_conf_t *const daisy_chain);

/**
 * \brief Defines Tx TSFIFO signature mask.
 **/
#define VTSS_PHY_TS_FIFO_SIG_SRC_IP          0x01  /**< Src IP address: inner IP for IP-over-IP */
#define VTSS_PHY_TS_FIFO_SIG_DEST_IP         0x02  /**< Dest IP address */

#define VTSS_PHY_TS_FIFO_SIG_MSG_TYPE        0x04  /**< Message type */
#define VTSS_PHY_TS_FIFO_SIG_DOMAIN_NUM      0x08  /**< Domain number */
#define VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID  0x10  /**< Source port identity */
#define VTSS_PHY_TS_FIFO_SIG_SEQ_ID          0x20  /**< PTP frame Sequence ID */

#define VTSS_PHY_TS_FIFO_SIG_DEST_MAC        0x40  /**< Dest MAC address */

typedef u32 vtss_phy_ts_fifo_sig_mask_t; /**< Signature mask which can be OR of multiple fields above */

/**
 * \brief Set Tx TSFIFO i.e. frame signature in Tx TSFIFO.
 * \note Ports sharing timestamp IP block use common register in analyzer to
 *  configure the signature i.e. all the ports within the timestamp IP block
 *  will have same signature in TSFIFO. In other words, to configure the
 *  signature in the FIFO, any of the ports within timestamp block can be used.
 *
 * \param inst     [IN]         handle to an API instance
 * \param port_no  [IN]         port number
 * \param sig_mask [IN]         signature mask
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_fifo_sig_set(const vtss_inst_t                 inst,
                                 const vtss_port_no_t              port_no,
                                 const vtss_phy_ts_fifo_sig_mask_t sig_mask);

/**
 * \brief Get frame signature mask in Tx TSFIFO.
 * \note As described in vtss_phy_ts_fifo_sig_set, any of the ports within
 *  IP timestamp block can be used to get the signature.
 *
 * \param inst     [IN]         handle to an API instance
 * \param port_no  [IN]         port number
 * \param sig_mask [OUT]        signature mask
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_fifo_sig_get(const vtss_inst_t            inst,
                                 const vtss_port_no_t         port_no,
                                 vtss_phy_ts_fifo_sig_mask_t  *const sig_mask);

/**
 * Following Tx TSFIFO related API are used if FIFO access mode is set as
 * PHY_TS_FIFO_MODE_NORMAL. In SPI mode, timestamps are pushed into SPI
 * interface as soon as they are available.
 **/

/**
 * \brief parameter describing various Tx TSFIFO status.
 **/
typedef enum {
    VTSS_PHY_TS_FIFO_SUCCESS,  /**< FIFO read success */
    VTSS_PHY_TS_FIFO_OVERFLOW, /**< FIFO overflow */
} vtss_phy_ts_fifo_status_t;

/**
 * \brief Read timestamp from Tx TSFIFO.
 * \note Application will call this function upon receipt of a signal for
 *  timestamp in FIFO.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_fifo_empty(const vtss_inst_t       inst,
                               const vtss_port_no_t    port_no);

/**
 * \brief Tx TSFIFO entry signature
 **/
typedef struct {
    vtss_phy_ts_fifo_sig_mask_t  sig_mask;  /**< valid signature fields */
    u8        msg_type;              /**< PTP message type */
    u8        domain_num;            /**< domain number in PTP message */
    u8        src_port_identity[10]; /**< source port identity in PTP message */
    u16       sequence_id;           /**< PTP message sequence ID */
    u32       dest_ip;               /**< Destination IP */
    u32       src_ip;                /**< Source IP */
    u8        dest_mac[6];           /**< Destination MAC */
} vtss_phy_ts_fifo_sig_t;

/** 
 * Tx TSFIFO API to access the HW TXFIFO. Application has to install the 
 * callback function which is called to push timestamp from the HW TXFIFO 
 * to the application. 
 **/

/**
 * \brief Tx TSFIFO read callback function prototype.
 *
 * inst            handle to an API instance
 * port_no         port number
 * ts              captured timestamp
 * sig             timestamp signature
 * cntxt           context to be returned in callback
 * status          FIFO read status
 **/
typedef void (*vtss_phy_ts_fifo_read)(const vtss_inst_t              inst,
                                      const vtss_port_no_t           port_no,
                                      const vtss_phy_timestamp_t     *const ts,
                                      const vtss_phy_ts_fifo_sig_t   *const sig,
                                      void                           *cntxt,
                                      const vtss_phy_ts_fifo_status_t status);

/**
 * \brief Install callback to read data (signature + timestamp) from Tx TSFIFO.
 * \note Registered callback will be called for each entry in TSFIFO from
 *  vtss_phy_ts_fifo_empty function.
 *
 * \param inst  [IN]            handle to an API instance
 * \param rd_cb [IN]            read callback
 * \param cntxt [IN]            context to be returned in callback
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_fifo_read_install(const vtss_inst_t      inst,
                                      vtss_phy_ts_fifo_read  rd_cb,
                                      void                   *cntxt);

/**
 * \brief Get the fifo read callback function installed.
 *
 * \param inst  [IN]            handle to an API instance
 * \param rd_cb [OUT]           read callback
 * \param cntxt [OUT]           context
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_fifo_read_cb_get(const vtss_inst_t      inst,
                                     vtss_phy_ts_fifo_read  *rd_cb,
                                     void                   **cntxt);

#define VTSS_PHY_TS_FIFO_MAX_ENTRIES 8 //In all vsc phys, maximum number of FIFO entries is 8.
typedef struct {
    vtss_phy_ts_fifo_sig_t sig;
    vtss_phy_timestamp_t ts;
} vtss_phy_ts_fifo_entry_t;

/**
 * \brief Get FIFO timestamp entries.
 *
 * \param inst     [IN]   handle to an API instance
 * \param port_no  [IN]   port number
 * \param ts_list  [OUT]  Array to hold retrieved FIFO timestamp entries
 * \param size     [IN]   size of ts_list array passed to this function.
 * \param num      [OUT]  Number of fifo timestamp entries read.
 **/
vtss_rc vtss_phy_ts_fifo_get(const vtss_inst_t        inst,
                             const vtss_port_no_t     port_no,
                             vtss_phy_ts_fifo_entry_t ts_list[],
                             const size_t             size,
                             uint32_t                 *const num);

/**
 * Analyzer API
 **/

/**
 * \brief Analyzer supported frame encapsulation type
 **/
typedef enum {
    /* PTP encap */
    VTSS_PHY_TS_ENCAP_ETH_PTP,
    VTSS_PHY_TS_ENCAP_ETH_IP_PTP,
    VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP,
    VTSS_PHY_TS_ENCAP_ETH_ETH_PTP,
    VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP,
    VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP,
    VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP,
    VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP,
    VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP,
    /* OAM encap */
    VTSS_PHY_TS_ENCAP_ETH_OAM,
    VTSS_PHY_TS_ENCAP_ETH_ETH_OAM,
    VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM,
    VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM, /* MPLS-TP OAM */

    VTSS_PHY_TS_ENCAP_ANY, /* Timestamp all packets */
    VTSS_PHY_TS_ENCAP_ETH_GEN, /* Generic timestamping */
    VTSS_PHY_TS_ENCAP_NONE,
} vtss_phy_ts_encap_t;

/**
 *\brief Defines Analyzer engine ID
 *\note Timestamp block has 2 PTP engines and 1 OAM engine. OAM engine
 * has two sub-engines (each supports different frame encapsulation) which
 * share OAM comparator to config time stamp functionality. API will expose
 * these 2 sub-engines to the application as 2 independent engines which
 * can have common/shared time stamping functionality (we call it as action).
 * So API will provide 2 PTP and 2 OAM engines to the application to use with
 * following properties/restriction which application must remember while
 * programming an engine.
 * (1) Multi-port timestamp block can share the same engine for both the
 * ports where for each flow in the engine aplication has to mention flow belong
 * to either one of the ports or both the ports; we call it as channel map.
 * (2) Each PTP engine supports 8 flows in ETH, IP and MPLS comparators and
 * 6 actions in PTP/OAM comparator. OAM engines (2A and 2B) have total of
 * 8 flows and 6 actions. Application has to associate flows to OAM engines.
 * But OAM actions can be shared between the 2 OAM engines.
 * (3) There is one HW limitation for flow match mode (strict/non-strict).
 * For same engine ID in ingress and egress direction flow match mode must be
 * same i.e. if engine VTSS_PHY_TS_PTP_ENGINE_ID_0 in ingress is configured as
 * strict flow match then engine VTSS_PHY_TS_PTP_ENGINE_ID_0 in egress has to be
 * in strict flow match. Also OAM engine 2A and 2B can not have different flow
 * match mode i.e engine 2A and 2B for ingress and egress must have same flow
 * match mode.
 * (4) OAM engine does not support TSFIFO and it can not be used for PTP
 * application. But OAM application can use PTP engine. 
 * (5) OAM engine 2B only support OAM application with single ethernet encap
 * i.e. OAM-over-ETH
 **/
typedef enum {
    VTSS_PHY_TS_PTP_ENGINE_ID_0, /**< PTP engine 0 */
    VTSS_PHY_TS_PTP_ENGINE_ID_1, /**< PTP engine 1 */
    VTSS_PHY_TS_OAM_ENGINE_ID_2A, /**< OAM engine 2A, no PTP support */
    VTSS_PHY_TS_OAM_ENGINE_ID_2B, /**< OAM engine 2B, no PTP; only OAM-over-ETH support */
    VTSS_PHY_TS_ENGINE_ID_INVALID, /**< Invalid Engine ID */
} vtss_phy_ts_engine_t;

/**
 * \brief Flow matching within an analyzer engine.
 * \note There are two types of flow match possible:
 *  (1) Strict flow matching: A valid frame must use the same flow IDs in all
 *      comparators in the engine except the PTP and MPLS comparators.
 *  (2) A valid frame may match any enabled flow within each comparator.
 *  There is one HW restriction mentioned above for flow match mode i.e.
 *  ingress and egress for same engine ID must have same flow match.
 *  In other words there is no provision to configure strict flow match in
 *  ingress, but non-strict flow match for egress. Same restriction for OAM
 *  engine 2A and 2B and also for ingress and egress i.e. engine 2A and 2B
 *  both ingress and egress must have same flow match mode.
 *
 **/
typedef enum {
    VTSS_PHY_TS_ENG_FLOW_MATCH_ANY,    /**< match any flow in comparators */
    VTSS_PHY_TS_ENG_FLOW_MATCH_STRICT  /**< strict flow match */
} vtss_phy_ts_engine_flow_match_t;

/**
 * \brief Initialize an analyzer ingress engine for an encapsulation type.
 * \note Depending on chip type, an analyzer engine may be shared by two
 *  ports, and therefore no need to initialize separate engine for each
 *  port. If the same encapsulation is used by the two ports, both can use
 *  same engine. To initialize an engine shared by both ports, either of the
 *  ports no can be passed to this API and use flow_map within the engine to
 *  map flows to the ports.
 *
 * \param inst            [IN]   handle to an API instance
 * \param port_no         [IN]   port number
 * \param eng_id          [IN]   engine ID
 * \param encap_type      [IN]   frame encapsulation
 * \param flow_st_index   [IN]   flow start index
 * \param flow_end_index  [IN]   flow end index
 * \param flow_match_mode [IN]   flow match mode: strict/non-strict flow match
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_engine_init(const vtss_inst_t     inst,
                        const vtss_port_no_t                  port_no,
                        const vtss_phy_ts_engine_t            eng_id,
                        const vtss_phy_ts_encap_t             encap_type,
                        const u8                              flow_st_index,
                        const u8                              flow_end_index,
                        const vtss_phy_ts_engine_flow_match_t flow_match_mode);

/**
 * \brief Defines the basic engine parameters passed to the engine_init_conf_get() function
 **/
typedef struct {
    BOOL                            eng_used; /**< allocated the engine to application */
    vtss_phy_ts_encap_t             encap_type; /**< engine encapsulation */
    vtss_phy_ts_engine_flow_match_t flow_match_mode; /**< strict/non-strict flow match */
    u8                              flow_st_index; /**< start index of flow */
    u8                              flow_end_index; /**< end index of flow */
}vtss_phy_ts_eng_init_conf_t;



/**
 * \brief Get the configuration parameters passed in engine_init of an
 *  analyzer ingress engine for a specific engine ID
 * \note Depending on chip type, an analyzer engine may be shared by two
 *  ports, and therefore the configuration is same for both the ports.
 *
 * \param inst        [IN]   handle to an API instance
 * \param port_no     [IN]   port number
 * \param eng_id      [IN]   engine ID
 * \param init_conf   [OUT]  config parameters in engine_init
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_ingress_engine_init_conf_get(const vtss_inst_t      inst,
                                  const vtss_port_no_t                   port_no,
                                  const vtss_phy_ts_engine_t             eng_id,
                                  vtss_phy_ts_eng_init_conf_t *const     init_conf);


/**
 * \brief Clear/release an analyzer ingress engine already initialized.
 *
 * \param inst            [IN]   handle to an API instance
 * \param port_no         [IN]   port number
 * \param eng_id          [IN]   engine ID
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_engine_clear(const vtss_inst_t  inst,
                         const vtss_port_no_t               port_no,
                         const vtss_phy_ts_engine_t         eng_id);

/**
 * \brief Initialize an analyzer egress engine for an encapsulation type.
 * \note Depending on chip type, an analyzer engine may be shared by two
 *  ports, and therefore no need to initialize separate engine for each
 *  port. If the same encapsulation is used by the two ports, both can use
 *  same engine. To initialize an engine shared by both ports, either of the
 *  ports no can be passed to this API and use flow_map within the engine to
 *  map flows to the ports.
 *
 * \param inst            [IN]   handle to an API instance
 * \param port_no         [IN]   port number
 * \param eng_id          [IN]   engine ID
 * \param encap_type      [IN]   frame encapsulation
 * \param flow_st_index   [IN]   flow start index
 * \param flow_end_index  [IN]   flow end index
 * \param flow_match_mode [IN]   flow match mode: strict/non-strict flow match
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_engine_init(const vtss_inst_t      inst,
                        const vtss_port_no_t                  port_no,
                        const vtss_phy_ts_engine_t            eng_id,
                        const vtss_phy_ts_encap_t             encap_type,
                        const u8                              flow_st_index,
                        const u8                              flow_end_index,
                        const vtss_phy_ts_engine_flow_match_t flow_match_mode);

/**
 * \brief Get the configuration parameters passed in engine_init of an
 *  analyzer egress engine for a specific engine ID
 * \note Depending on chip type, an analyzer engine may be shared by two
 *  ports, and therefore the configuration is same for both the ports.
 *
 * \param inst        [IN]   handle to an API instance
 * \param port_no     [IN]   port number
 * \param eng_id      [IN]   engine ID
 * \param init_conf   [OUT]  config parameters in engine_init
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_engine_init_conf_get(const vtss_inst_t     inst,
                                  const vtss_port_no_t                port_no,
                                  const vtss_phy_ts_engine_t          eng_id,
                                  vtss_phy_ts_eng_init_conf_t *const  init_conf);


/**
 * \brief Clear/release an analyzer egress engine already initialized.
 *
 * \param inst            [IN]   handle to an API instance
 * \param port_no         [IN]   port number
 * \param eng_id          [IN]   engine ID
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_engine_clear(const vtss_inst_t  inst,
                         const vtss_port_no_t              port_no,
                         const vtss_phy_ts_engine_t        eng_id);

/** \brief Ethernet per flow configuration */
typedef struct {
    BOOL  flow_en;  /**< flow enable/disable */

#define VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT            ((u8)0x01) /**< Full 48-bit address match */
#define VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST      ((u8)0x02) /**< Match any unicast MAC addres */
#define VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST    ((u8)0x04) /**< Match any multicast MAC addres */
    u8    addr_match_mode; /**< Multiple match can be possible using OR */
#define VTSS_PHY_TS_ETH_MATCH_DEST_ADDR      ((u8)0x00) /**< Match destination MAC address */
#define VTSS_PHY_TS_ETH_MATCH_SRC_ADDR       ((u8)0x01) /**< Match source MAC address */
#define VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST    ((u8)0x02) /**< Match source or destination MAC address */
    u8    addr_match_select; /**< src or dest addr to be matched */
    u8    mac_addr[6]; /**< addr to be matched, src or dest */

    BOOL  vlan_check; /**< TRUE=>verify configured VLAN tag configuration, FALSE=>parse VLAN tag if any, but don't check, for PBB I-tag is always checked */
    u8    num_tag; /**< No of Tags (max 2 tag), for PBB at least I-tag should be present */
#define VTSS_PHY_TS_TAG_TYPE_C    ((u8)0x01) /**< Tag type: C */
#define VTSS_PHY_TS_TAG_TYPE_S    ((u8)0x02) /**< Tag type: S */
#define VTSS_PHY_TS_TAG_TYPE_I    ((u8)0x03) /**< Tag type: I */
#define VTSS_PHY_TS_TAG_TYPE_B    ((u8)0x04) /**< Tag type: B */
    u8    outer_tag_type; /**< for PBB enabled with 2-tag, this must be B-tag */
    u8    inner_tag_type; /**< for PBB this must be I-tag; also for single tag inner_tag is used */
#define VTSS_PHY_TS_TAG_RANGE_NONE     ((u8)0x00) /**< Neither inner nor outer tag allows range config */
#define VTSS_PHY_TS_TAG_RANGE_OUTER    ((u8)0x01) /**< Outer tag allows range config */
#define VTSS_PHY_TS_TAG_RANGE_INNER    ((u8)0x02) /**< Inner tag allows range config */
    u8    tag_range_mode;  /**< for PBB no range check is allowed */
    union {
        struct {
            u16    upper; /**< Upper value for outer tag range */
            u16    lower; /**< Lower value for outer tag range */
        } range;  /**< tag in range */
        struct {
            u16    val;  /**< Value */
            u16    mask; /**< Mask */
        } value;  /**< tag in value/mask */
    } outer_tag; /**< Outer tag */
    union {
        struct {
            u16    upper; /**< Upper value for inner tag range */
            u16    lower; /**< Loower value for inner tag range */
        } range;  /**< tag in range */
        struct {
            u16    val; /**< Value */
            u16    mask; /**< Mask */
        } value;  /**< tag in value/mask */
        struct {
            u32    val;   /**< 24-bit I-tag value */
            u32    mask;  /**< 24-bit I-tag mask */
        } i_tag;  /**< I-tag in value/mask. This is applicable for PBB i.e. Eth1 comparator */
    } inner_tag; /**< Inner Tag*/
} vtss_phy_ts_eth_flow_conf_t;

/**
 * \brief Analyzer Ethernet comparator configuration options
 * \note Common options apply all the flows within the comparator. Also there
 *  are per-flow configuration.
 **/
typedef struct {
    struct {
        BOOL  pbb_en; /**< PBB tag present, not applicable for Eth2 comparator */
        u16   etype;  /**< The value of Ether type to be checked if Ethertype/length field is an Ethertype */
        u16   tpid;  /**< VLAN TPID for S or B-tag */
    } comm_opt; /**< Ethernet common config */

    vtss_phy_ts_eth_flow_conf_t flow_opt[8]; /**< Ethernet per flow config */
} vtss_phy_ts_eth_conf_t; /**< ETH configuration */

/** \brief IP per flow configuration */
typedef struct {
    BOOL  flow_en;  /**< flow enable/disable */
#define VTSS_PHY_TS_IP_MATCH_SRC          0x00 /**< Match source IP address */
#define VTSS_PHY_TS_IP_MATCH_DEST         0x01 /**< Match destination IP address */
#define VTSS_PHY_TS_IP_MATCH_SRC_OR_DEST  0x02 /**< Match source or destination IP address */
    u8    match_mode; /**< match src, dest or either IP address */
    union {
        struct {
            u32    addr; /**< IPv4 address */
            u32    mask; /**< IPv4 address mask */
        } ipv4; /**< IPv4 Address */
        struct {
            u32    addr[4]; /**< IPv6 Address */
            u32    mask[4]; /**<IPv6 Mask */
        } ipv6; /**< IPv6 Mask */
    } ip_addr;  /**< IPv4/IPv6 address to be matched */
} vtss_phy_ts_ip_flow_conf_t;

/**
 * \brief Analyzer IP comparator configuration options
 * \note Common options apply all the flows within the comparator. Also there
 *  are per flow configuration.
 **/
typedef struct {
    struct {
#define VTSS_PHY_TS_IP_VER_4    0x01 /**< Version: IPv4 */
#define VTSS_PHY_TS_IP_VER_6    0x02 /**< Version: IPv6 */
        u8    ip_mode; /**< IPv4, IPv6 */
        /**< if next protocol is not UDP, next UDP fields are not used */
        u16   sport_val; /**< UDP source port value */ 
        u16   sport_mask; /**< UDP source port mask */ 
        u16   dport_val; /**< UDP dest port value */ 
        u16   dport_mask; /**< UDP dest port mask */ 
    } comm_opt; /**< IP common config */

    vtss_phy_ts_ip_flow_conf_t flow_opt[8]; /**< IP per flow config */
} vtss_phy_ts_ip_conf_t; /**< IP configuration */

/**
 * \brief MPLS level range
 **/
typedef struct {
    u32    lower; /**< lower range value */
    u32    upper; /**< upper range value */
} vtss_phy_ts_mpls_lvl_rng_t;

/** \brief MPLS per flow configuration */
typedef struct {
    BOOL       flow_en;  /**< flow enable/disable */

#define VTSS_PHY_TS_MPLS_STACK_DEPTH_1    ((u8)0x01) /**< MPLS stack of depth 1 only allows */
#define VTSS_PHY_TS_MPLS_STACK_DEPTH_2    ((u8)0x02) /**< MPLS stack of depth 2 only allows */
#define VTSS_PHY_TS_MPLS_STACK_DEPTH_3    ((u8)0x04) /**< MPLS stack of depth 3 only allows */
#define VTSS_PHY_TS_MPLS_STACK_DEPTH_4    ((u8)0x08) /**< MPLS stack of depth 4 only allows */
    u8         stack_depth; /**< depth of MPLS level; multiple depth match can be possible using OR */

#define VTSS_PHY_TS_MPLS_STACK_REF_POINT_TOP    0x00 /**< Search starts from the top of the stack */
#define VTSS_PHY_TS_MPLS_STACK_REF_POINT_END    0x01 /**< Search starts from the end of the stack */
    u8         stack_ref_point; /**< Search direction for label matching: top to bottom or bottom to top */
    union {
        struct {
            vtss_phy_ts_mpls_lvl_rng_t  top; /**< Top level */
            vtss_phy_ts_mpls_lvl_rng_t  frst_lvl_after_top; /**< First label after the top label */
            vtss_phy_ts_mpls_lvl_rng_t  snd_lvl_after_top; /**< Second label after the top label */
            vtss_phy_ts_mpls_lvl_rng_t  thrd_lvl_after_top; /**< Third label after the top label */
        } top_down; /**< Top down configuration */
        struct {
            vtss_phy_ts_mpls_lvl_rng_t  end; /**< End level */
            vtss_phy_ts_mpls_lvl_rng_t  frst_lvl_before_end; /**< First label before the end label */
            vtss_phy_ts_mpls_lvl_rng_t  snd_lvl_before_end; /**< Second label before the end label */
            vtss_phy_ts_mpls_lvl_rng_t  thrd_lvl_before_end; /**< Third label before the end label */
            } bottom_up; /**< Bottom up configuration */
    } stack_level; /**< 4 level values; top_down or bottom_up depends on stack_ref_point */
} vtss_phy_ts_mpls_flow_conf_t;

/**
 * \brief Analyzer MPLS comparator configuration options
 **/
typedef struct {
    struct {
        BOOL           cw_en;  /**< flow uses psudowire control word or not */
    } comm_opt; /**< MPLS common config */

    vtss_phy_ts_mpls_flow_conf_t flow_opt[8]; /**< MPLS per flow config */
} vtss_phy_ts_mpls_conf_t; /**< MPLS configuration */

/**
 * \brief Analyzer ACH comparator configuration options
 * \note ACH uses the IP1 comparator for match. So IP1 and ACH can not be used
 * at the same time.
 **/
typedef struct {
    struct {
        struct {
            u8    value; /**< 4-bits version */
            u8    mask; /**< Mask */
        } version; /**< version number of the PWACH in value/mask; set mask 0 for don't care */
        struct {
            u16   value; /**< Channel type value */
            u16   mask; /**< Channel type mask */
        } channel_type; /**< PW Associated Channel Type in value/mask format */
        struct {
            u16   value; /**< Protocol Identifier Value */
            u16   mask; /**< Protocl Identifier Mask */
        } proto_id; /**< PID: identifier of payload as defined in RFC 5718, only for PTP */
    } comm_opt; /**< ACH common config */

    /* No flow config reqd for ACH */
} vtss_phy_ts_ach_conf_t; /**< ACH Configuration */

/**
 * \brief Analyzer Generic data configuration options using IP comparator
 *
 **/
typedef struct {
    struct {
        u8    flow_offset;       /**< Offset of data pattern to match with current comparator */
        u8    next_prot_offset;  /**< Offset of data pattern to match with next comparator */
    } comm_opt; /**< Generic Matching common configuration */

    struct {
        BOOL  flow_en;          /**< Enable the flow */
        u32   data[4];          /**< Data byte pattern to match */
        u32   mask[4];          /**< Mask of the matching pattern */
    } flow_opt[8]; /**< Generic matching config per flow */
} vtss_phy_ts_gen_conf_t;

/**
 * \brief Port to flow mapping within analyzer engine.
 * \note This is applicable for multi-channel timestamp block.
 **/
#define VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0  0x01 /**< Channel-0 mapped */
#define VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1  0x02 /**< Channel-1 mapped */
typedef u8 vtss_phy_ts_engine_channel_map_t; /**< Channel-0 or channel-1 or both the channels */

/**
 * \brief PTP engine flow configuration options
 **/
typedef struct {
    vtss_phy_ts_eth_conf_t       eth1_opt;    /**< Eth-1 comparator */
    vtss_phy_ts_eth_conf_t       eth2_opt;    /**< Eth-2 comparator; for single ETH encap, Eth-1 is used */
    vtss_phy_ts_ip_conf_t        ip1_opt;     /**< IP-1 comparator */
    vtss_phy_ts_ip_conf_t        ip2_opt;     /**< IP-2 comparator; for single IP encap, IP-1 is used */
    vtss_phy_ts_mpls_conf_t      mpls_opt;    /**< MPLS comparator */
    vtss_phy_ts_ach_conf_t       ach_opt;     /**< ACH: it uses the IP1 comparator, so IP1 and ACH can not enabled simultaneously */
} vtss_phy_ts_ptp_engine_flow_conf_t;

/**
 * \brief OAM engine flow configuration options
 **/
typedef struct {
    vtss_phy_ts_eth_conf_t   eth1_opt;    /**< Eth-1 comparator */
    vtss_phy_ts_eth_conf_t   eth2_opt;    /**< Eth-2 comparator; for single ETH encap, Eth-1 is used */
    vtss_phy_ts_mpls_conf_t  mpls_opt;    /**< MPLS comparator */
    vtss_phy_ts_ach_conf_t   ach_opt;     /**< ACH: it uses the IP1 comparator, so IP1 and ACH can not enabled simultaneously */
} vtss_phy_ts_oam_engine_flow_conf_t;


/**
 * \brief Generic engine flow configuration options
 **/
typedef struct {
    vtss_phy_ts_eth_conf_t   eth1_opt;    /**< Eth-1 comparator */
    vtss_phy_ts_gen_conf_t   gen_opt;     /**< Generic : It uses IP1 comparator */
} vtss_phy_ts_generic_flow_conf_t;

/**
 * \brief Analyzer flow configuration options
 * \note Engine configuration will be parsed to know PTP or OAM flow based on
 * encapsulation type provided during engine allocation.
 **/
typedef struct {
    BOOL                              eng_mode;    /**< engine enable/disable */
    vtss_phy_ts_engine_channel_map_t  channel_map[8]; /**< maps flows to channel for multi-channel timestamp block. flow_map can be set per comparator in HW */

    union {
        vtss_phy_ts_ptp_engine_flow_conf_t ptp;       /**< PTP engine configuration */
        vtss_phy_ts_oam_engine_flow_conf_t oam;       /**< OAM engine configuration */
        vtss_phy_ts_generic_flow_conf_t    gen;       /**< Generic match configuration */
    } flow_conf; /**< PTP/OAM flow config */
} vtss_phy_ts_engine_flow_conf_t;

/**
 * \brief Configure ingress analyzer flow.
 * \note For multi-port timestamp block, either of the port can be used to
 *  configure the ingress engine, port to which frame will be matched is
 *  specified in flow-map parameter.
 *  Note that during the process of updating an engine configuration, the
 *  engine mode will be disabled and it will start processing PTP frame after
 *  config finished.
 *  Also if the local time counter is out of sync, and has to be set, then the
 *  received ptp packets must be ignored, and no ptp packets should be
 *  transmitted, but this should be controlled by the application.
 *
 * \param inst      [IN]    handle to an API instance
 * \param port_no   [IN]    port number
 * \param eng_id    [IN]    engine ID
 * \param flow_conf [IN]    pointer to engine configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_engine_conf_set(const vtss_inst_t inst,
                         const vtss_port_no_t                 port_no,
                         const vtss_phy_ts_engine_t           eng_id,
                         const vtss_phy_ts_engine_flow_conf_t *const flow_conf);

/**
 * \brief Get ingress analyzer flow.
 * \note For multi-port timestamp block, either of the port can used to get
 *  the ingress engine configuration.
 *
 * \param inst      [IN]    handle to an API instance
 * \param port_no   [IN]    port number
 * \param eng_id    [IN]    engine ID
 * \param flow_conf [OUT]   pointer to engine configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_engine_conf_get(const vtss_inst_t inst,
                             const vtss_port_no_t             port_no,
                             const vtss_phy_ts_engine_t       eng_id,
                             vtss_phy_ts_engine_flow_conf_t   *const flow_conf);

/**
 * \brief Configure egress analyzer flow.
 * \note For multi-port timestamp block, either of the port can be used to
 *  configure the ingress engine, port to which frame will be matched is
 *  specified in flow_map parameter.
 *
 * \param inst      [IN]    handle to an API instance
 * \param port_no   [IN]    port number
 * \param eng_id    [IN]    engine ID
 * \param flow_conf [IN]    pointer to engine configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_engine_conf_set(const vtss_inst_t inst,
                        const vtss_port_no_t                 port_no,
                        const vtss_phy_ts_engine_t           eng_id,
                        const vtss_phy_ts_engine_flow_conf_t *const flow_conf);

/**
 * \brief Get egress analyzer flow.
 * \note For multi-port timestamp block, either of the port can used to get
 *  the ingress engine configuration.
 *
 * \param inst      [IN]     handle to an API instance
 * \param port_no   [IN]     port number
 * \param eng_id    [IN]     engine ID
 * \param flow_conf [OUT]    pointer to engine configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_engine_conf_get(const vtss_inst_t  inst,
                           const vtss_port_no_t               port_no,
                           const vtss_phy_ts_engine_t         eng_id,
                           vtss_phy_ts_engine_flow_conf_t     *const flow_conf);


/**
 * \brief Analyzer PTP comparator configuration options
 **/
typedef struct {
    BOOL    range_en;  /**< PTP domain number in range enable/disable */
    union {
        struct {
            u8    val; /**< PTP domain number value */
            u8    mask; /**< PTP domain number mask */
        } value; /**< specific PTP domain, for don't care set mask as '0' */
        struct {
            u8    upper; /**< Ranger upper value */
            u8    lower; /**< Range lower value */
        } range; /**< PTP domain range configuration */
    } domain; /**< PTP domain number configuration */
} vtss_phy_ts_ptp_conf_t;

/**
 * \brief PTP Timestamp Engine operational modes
 * \note From the operational mode (vtss_phy_ts_ptp_clock_mode_t) and delay
 * measurement method (vtss_phy_ts_ptp_delaym_type_t) the API sets up flows
 * in the PTP comparator.
 **/
typedef enum {
    VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP, /**< Ordinary/Boundary clock, 1 step */
    VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP, /**< Ordinary/Boundary clock, 2 step */
    VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP, /**< Transparent clock, 1 step */
    VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP, /**< Transparent clock, 2 step */
    VTSS_PHY_TS_PTP_DELAY_COMP_ENGINE,  /**<  Delay Compenstaion */
} vtss_phy_ts_ptp_clock_mode_t;

/**
 * \brief PTP delay measurement method
 * \note As described above, using clock mode and delay measurement method,
 *  API sets up flows in PTP comparator.
 **/
typedef enum {
    VTSS_PHY_TS_PTP_DELAYM_P2P, /**< Peer-to-Peer delay measurement method */
    VTSS_PHY_TS_PTP_DELAYM_E2E, /**< End-to-End delay measurement method */
} vtss_phy_ts_ptp_delaym_type_t;

/**
 * \brief Analyzer PTP action configuration options
 * \note Timestamp action will be based on clock type and delay measurement method.
 **/
typedef struct {
    BOOL                          enable;   /**< PTP action active/enable or not */
    vtss_phy_ts_engine_channel_map_t channel_map;  /**< maps action to channel for multi-channel timestamp block */
    vtss_phy_ts_ptp_conf_t        ptp_conf;    /**< PTP configuration */
    vtss_phy_ts_ptp_clock_mode_t  clk_mode;    /**< clock mode: bc1step, bc2step, tc1step or tc2step */
    vtss_phy_ts_ptp_delaym_type_t delaym_type; /**< delay measurement method: P2P, E2E */
    BOOL                          cf_update; /**< correction field update for bc1step */
    BOOL                          delay_req_recieve_timestamp; /**<auto Delay_Req/Response feature */
} vtss_phy_ts_ptp_engine_action_t;

/**
 * \brief Y.1731 OAM delay messurement method
 * \note Using delay messurement method, API sets up OAM flows in OAM
 *  comparator.
 **/
typedef enum {
    VTSS_PHY_TS_Y1731_OAM_DELAYM_1DM, /**< One-Way delay messurement method */
    VTSS_PHY_TS_Y1731_OAM_DELAYM_DMM, /**< Two-Way delay messurement method */
}vtss_phy_ts_y1731_oam_delaym_type_t;

/**
 * \brief IETF MPLS ACH, OAM delay messurement method
 * \note Using delay messurement method, API sets up OAM flows in OAM
 *  comparator.
 **/
typedef enum {
    VTSS_PHY_TS_IETF_MPLS_ACH_OAM_DELAYM_DMM, /**< Two-way delay measurement method */
    VTSS_PHY_TS_IETF_MPLS_ACH_OAM_DELAYM_LDM, /**< Loss/Delay Message combined Measurement Message */
} vtss_phy_ts_ietf_mpls_ach_oam_delaym_type_t;

/**
 * \brief Analyzer OAM comparator, Y.1731 OAM Packet format configuration options
 **/
typedef struct {
    BOOL                                range_en;  /**< OAM MEG level in range enable/disable */
    vtss_phy_ts_y1731_oam_delaym_type_t delaym_type; /**< OAM delay measurement method */
    union {
        struct {
            u8    val; /**< Value */
            u8    mask; /**< Mask */
        } value; /**< specific MEG Level, for don't care set mask as '0' */
        struct {
            u8    upper; /**< Range Upper value */
            u8    lower; /**< Range lower value */
        } range; /**< Range configuration */
    } meg_level; /**< OAM MEG level config */
} vtss_phy_ts_y1731_oam_conf_t; /**< OAM match configuration */

/**
 * \brief Analyzer OAM comparator, IETF MPLS ACH OAM Supported Timestamp Format
 * \note PTP Timestamp Format is Supported.
 **/
typedef enum {
    VTSS_PHY_TS_IETF_MPLS_ACH_OAM_TS_FORMAT_PTP = 0x3, /**< PTP - TimeStamp Format */
} vtss_phy_ts_ietf_mpls_ach_oam_ts_format_t;

/**
 * \brief Analyzer OAM comparator, IETF MPLS ACH OAM Packet format configuration options
 **/
typedef struct {
    vtss_phy_ts_ietf_mpls_ach_oam_delaym_type_t delaym_type; /**< OAM delay measurement method */
    vtss_phy_ts_ietf_mpls_ach_oam_ts_format_t   ts_format;   /**< OAM DM Timestamp format */
    u8    ds;      /**< DSCP value, that corresponds to a traffic class being measured. */
} vtss_phy_ts_ietf_mpls_ach_oam_conf_t;

/**
 * \brief OAM Action configuration options
 * \note Timestamp action will be based on OAM delay measurement method.
 **/
typedef struct {
    BOOL                             enable;      /**< OAM action active/enable or not */
    BOOL                             y1731_en;    /**< Y.1731 Message Format Enabled/Disable */
    vtss_phy_ts_engine_channel_map_t channel_map; /**< maps action to channel for multi-channel timestamp block */
    u8                               version;     /**< Protocol Version; only 0 is supported */
    union {
            vtss_phy_ts_y1731_oam_conf_t          y1731_oam_conf; /**< Y.1731 OAM configuration */
            vtss_phy_ts_ietf_mpls_ach_oam_conf_t  ietf_oam_conf; /**< IETF OAM configuration */
    } oam_conf; /**< OAM action config */
} vtss_phy_ts_oam_engine_action_t;

/**
 * \brief Timestamp format to be configured in action configuration
 */
typedef enum {
    VTSS_PHY_TS_4_BYTE, /**< Nano second timestamp */
    VTSS_PHY_TS_10_BYTE /**< 10 byte timestamp */
} vtss_phy_ts_action_format;

/**
 * \brief Generic Action configuration option
 */
typedef struct {
    BOOL                             enable; /**< Generic action active/enable or not */
    vtss_phy_ts_engine_channel_map_t channel_map; /**< maps action to channel for multi-channel timestamp block */
    u8                               flow_id; /**< Flow id to be associated with this action */
    u32                              data[2];/**< Matching data pattern */
    u32                              mask[2];/**< Mask for the matching pattern */
    vtss_phy_ts_action_format        ts_type; /**< Timestamp type 4-byte or 10 byte timestamp */
    u32                              ts_offset; /**< Timestamp offset */
} vtss_phy_ts_generic_action_t;

/**
 * \brief Engine Action configuration options
 * \note Number of PTP actions in a engine depends on clock mode and delay
 * method, like TC1Step and P2P, it requires 3 ingress rules to be added into
 * PTP flows. There are total 6 flows in PTP and OAM comparator. For each
 * frame type that needs to be timestamped requires one rule (i.e 1 flow).
 * So application should decide the number of actions accordingly. For OAM
 * only 2DM needs 2 flows, others needs 1 flow. The number of PTP/OAM actions
 * config here is the maximum number, application should decide how many are
 * valid for a engine based on clock mode and delay method. 
 **/
typedef struct {
    BOOL  action_ptp;  /**< is the action for PTP or OAM */
    BOOL  action_gen;  /**< generic action or not */
    union {
        vtss_phy_ts_ptp_engine_action_t   ptp_conf[2]; /**< Max 2 PTP action per engine */
        vtss_phy_ts_oam_engine_action_t   oam_conf[6]; /**< Max 6 OAM action per engine */
        vtss_phy_ts_generic_action_t      gen_conf[6]; /**< Max 6 Generic action per engine */
    } action; /**< PTP/OAM action config */
} vtss_phy_ts_engine_action_t;

/**
 * \brief Configure ingress analyzer engine action.
 * \note For multi-port timestamp block, either of the port can be used to
 *  configure the ingress engine.
 *  Note that during the process of updating an engine configuration, the
 *  engine mode will be disabled and it will start processing frame after
 *  config finished.
 *
 * \param inst        [IN]    handle to an API instance
 * \param port_no     [IN]    port number
 * \param eng_id      [IN]    engine ID
 * \param action_conf [IN]    action associated with the engine
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_engine_action_set(const vtss_inst_t inst,
                              const vtss_port_no_t              port_no,
                              const vtss_phy_ts_engine_t        eng_id,
                              const vtss_phy_ts_engine_action_t *const action_conf);

/**
 * \brief Get ingress analyzer engine action.
 *  For multi-port timestamp block, either of the port can be used to get
 *  the ingress engine.
 *
 * \param inst        [IN]    handle to an API instance
 * \param port_no     [IN]    port number
 * \param eng_id      [IN]    engine ID
 * \param action_conf [OUT]   action associated with the engine
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_engine_action_get(const vtss_inst_t inst,
                               const vtss_port_no_t             port_no,
                               const vtss_phy_ts_engine_t       eng_id,
                               vtss_phy_ts_engine_action_t      *const action_conf);

/**
 * \brief Configure egress analyzer engine action.
 * \note For multi-port timestamp block, either of the port can be used to
 *  configure the ingress engine.
 *  Note that during the process of updating an engine configuration, the
 *  engine mode will be disabled and it will start processing frame after
 *  config finished.
 *
 * \param inst        [IN]    handle to an API instance
 * \param port_no     [IN]    port number
 * \param eng_id      [IN]    engine ID
 * \param action_conf [IN]    action associated with the engine
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_engine_action_set(const vtss_inst_t inst,
                          const vtss_port_no_t                 port_no,
                          const vtss_phy_ts_engine_t           eng_id,
                          const vtss_phy_ts_engine_action_t    *const action_conf);

/**
 * \brief Get egress analyzer engine action.
 *  For multi-port timestamp block, either of the port can be used to get
 *  the ingress engine.
 *
 * \param inst        [IN]    handle to an API instance
 * \param port_no     [IN]    port number
 * \param eng_id      [IN]    engine ID
 * \param action_conf [OUT]   action associated with the engine
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_engine_action_get(const vtss_inst_t inst,
                                const vtss_port_no_t           port_no,
                                const vtss_phy_ts_engine_t     eng_id,
                                vtss_phy_ts_engine_action_t    *const action_conf);

/**
 * \brief Timestamp interrupt events
 **/
#define VTSS_PHY_TS_INGR_ENGINE_ERR            0x01  /**< More than one engine find match */
#define VTSS_PHY_TS_INGR_RW_PREAM_ERR          0x02  /**< Preamble too short to append timestamp */
#define VTSS_PHY_TS_INGR_RW_FCS_ERR            0x04  /**< FCS error in ingress */
#define VTSS_PHY_TS_EGR_ENGINE_ERR             0x08  /**< More than one engine find match */
#define VTSS_PHY_TS_EGR_RW_FCS_ERR             0x10  /**< FCS error in egress */
#define VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED     0x20  /**< Timestamp captured in Tx TSFIFO */
#define VTSS_PHY_TS_EGR_FIFO_OVERFLOW          0x40  /**< Tx TSFIFO overflow */
#define VTSS_PHY_TS_DATA_IN_RSRVD_FIELD        0x80  /**< Data in reserved Field */
#define VTSS_PHY_TS_LTC_NEW_PPS_INTRPT         0x100 /**< New PPS pushed onto external PPS pin*/
#define VTSS_PHY_TS_LTC_LOAD_SAVE_NEW_TOD      0x200 /**< New LTC value either loaded in to HW or saved into registers*/

typedef u32 vtss_phy_ts_event_t; /**< Int events: Single event or 'OR' multiple events above */

/**
 * \brief Enabling / Disabling of events
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param enable  [IN]   Enable or disable events
 * \param ev_mask [IN]   Event type(s) to control (mask)
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_event_enable_set(const vtss_inst_t         inst,
                                     const vtss_port_no_t      port_no,
                                     const BOOL                enable,
                                     const vtss_phy_ts_event_t ev_mask);

/**
 * \brief Get Enabling of events
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number 
 * \param ev_mask [OUT]  Mask containing events that are enabled 
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_event_enable_get(const vtss_inst_t     inst,
                                     const vtss_port_no_t  port_no,
                                     vtss_phy_ts_event_t   *const ev_mask);



/**
 * \brief Polling function called at by interrupt or periodically
 * \note Interrupt status will be cleared on read
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param status  [OUT]  Event status, bit set indicates corresponding
 *                       event/interrupt has detected
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_event_poll(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_phy_ts_event_t   *const status);


/**
 * \brief Timestamping Statistics.
 * \note Use vtss_phy_ts_stats_get() to retrieve current statistics.
 **/
typedef struct {
    u32    ingr_pream_shrink_err; /**< Frames with preambles too short to shrink */
    u32    egr_pream_shrink_err;  /**< Frames with preambles too short to shrink */
    u32    ingr_fcs_err;          /**< Timestamp block received frame with FCS error in ingress */
    u32    egr_fcs_err;           /**< Timestamp block received frame with FCS error in egress */
    u32    ingr_frm_mod_cnt;      /**< No of frames modified by timestamp block (rewritter) in ingress */
    u32    egr_frm_mod_cnt;       /**< No of frames modified by timestamp block (rewritter) in egress */
    u32    ts_fifo_tx_cnt;        /**< the number of timestamps transmitted to the interface */
    u32    ts_fifo_drop_cnt;      /**< Count of dropped Timestamps not enqueued to the Tx TSFIFO */
} vtss_phy_ts_stats_t;

/**
 * \brief Get Timestamp statistics.
 *
 * \param inst       [IN]        handle to an API instance
 * \param port_no    [IN]        port number
 * \param statistics [OUT]       pointer to statistics structure
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_stats_get(const vtss_inst_t     inst,
                              const vtss_port_no_t  port_no,
                              vtss_phy_ts_stats_t   *const statistics);

/**
 * \brief Get the correction field overflow status in ingress and egress.
 *
 * \param inst          [IN]    handle to an API instance
 * \param port_no       [IN]    port number
 * \param ingr_overflow [OUT]   ingress overflow status (enable/disable)
 * \param egr_overflow  [OUT]   egress overflow status (enable/disable)
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_correction_overflow_get(
                        const vtss_inst_t     inst,
                        const vtss_port_no_t  port_no,
                        BOOL                  *const ingr_overflow,
                        BOOL                  *const egr_overflow);

/**
 * \brief Enable/disable timestamp block.
 * \note Disabling the timestamp block will 'BYPASS' the block.
 *
 * \param inst    [IN]     handle to an API instance
 * \param port_no [IN]     port number
 * \param enable  [IN]     enable/disable parameter
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_mode_set(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             const BOOL            enable);

/**
 * \brief Get timestamp block status i.e. enable/disable.
 *
 * \param inst    [IN]     handle to an API instance
 * \param port_no [IN]     port number
 * \param enable  [OUT]    enable/disable parameter
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_mode_get(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             BOOL                  *const enable);

/**
 * \brief Timestamp block clock frequencies
 **/
typedef enum {
    VTSS_PHY_TS_CLOCK_FREQ_125M,   /**< 125 MHz */
    VTSS_PHY_TS_CLOCK_FREQ_15625M, /**< 156.25 MHz */
    VTSS_PHY_TS_CLOCK_FREQ_200M,   /**< 200 MHz */
    VTSS_PHY_TS_CLOCK_FREQ_250M,   /**< 250 MHz */
    VTSS_PHY_TS_CLOCK_FREQ_500M,   /**< 500 MHz */
    VTSS_PHY_TS_CLOCK_FREQ_MAX,    /**< MAX Freq */
} vtss_phy_ts_clockfreq_t;

/**
 * \brief Clock input source
 * \note Valid Clock Sorces:
 *  Malibu: Only External clock source(i.e., 0) is valid, as none of the other clock sources will provide 161.13MHz due to hardware limitation.
 *  Venice: Clock sources External, Host(Client) recovered Tx and Rx clock sources(i.e., 0, 1 and 2) are valid.
 **/
typedef enum {
    VTSS_PHY_TS_CLOCK_SRC_EXTERNAL,   /**< External source */
    VTSS_PHY_TS_CLOCK_SRC_CLIENT_RX,  /**< 10G: XAUI lane 0 recovered clock, */
                                      /**< 1G: MAC RX clock (note: direction is opposite to 10G, i.e. PHY->MAC) */
    VTSS_PHY_TS_CLOCK_SRC_CLIENT_TX,  /**< 10G: XAUI lane 0 recovered clock, */
                                      /**< 1G: MAC TX clock (note:  direction is opposite to 10G, i.e. MAC->PHY)  */
    VTSS_PHY_TS_CLOCK_SRC_LINE_RX,    /**< Received line clock */
    VTSS_PHY_TS_CLOCK_SRC_LINE_TX,    /**< transmitted line clock */
    VTSS_PHY_TS_CLOCK_SRC_INTERNAL,   /**< 10G: Invalid, 1G: Internal 250 MHz Clock */
} vtss_phy_ts_clock_src_t;


/**
 * \brief defines Rx Timestamp position inside PTP frame.
 * \note There are two options to put Rx timestamp in PTP frame:
 *  (a) Rx timestamp in Reserved 4 bytes of PTP header.
 *  (b) Shrink Preamble by 4 bytes and append 4 bytes at the end of frame.
 *      In this case Ethernet CRC will be overwritten by Rx timestamp
 *      and a new CRC will be appended after timestamp
 *  Also note that Rx Timestamp position must be same for all the ports in
 *  the system; otherwsie in ingress timestamp will be put in one position
 *  based on that port config whereas egress extract the time from different
 *  position as par that port config.
 **/
typedef enum {
    VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP, /**< 4 reserved bytes in PTP header */
    VTSS_PHY_TS_RX_TIMESTAMP_POS_AT_END, /**< 4 bytes appended at the end */
} vtss_phy_ts_rxtimestamp_pos_t;

/**
 * \brief Defines RX Timestamp format i.e. 30bit or 32bit Rx timestamp.
 * \note 30bit mode: The value in the reserved field is simply the nanosecCounter
 *              i.e. [0..999999999]
 *  32bit mode: The value in the reserved field is a 32 bit value and equals:
 *              (nanosecCounter + secCounter*10^9) mod 2^32
 **/
typedef enum {
    VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT, /**< 30 bit Rx timestamp */
    VTSS_PHY_TS_RX_TIMESTAMP_LEN_32BIT, /**< 32 bit Rx timestamp */
} vtss_phy_ts_rxtimestamp_len_t;

/**
 * \brief Defines Tx TSFIFO access mode.
 **/
typedef enum {
    VTSS_PHY_TS_FIFO_MODE_NORMAL, /**< in this mode, timestamp can be read from normal CPU interface */
    VTSS_PHY_TS_FIFO_MODE_SPI,    /**< Timestamps are pushed out on the SPI interface */
} vtss_phy_ts_fifo_mode_t;

/**
 * \brief Defines 4 bytes vs. the default 10 bytes Timestamp stored in Tx TSFIFO.
 **/
typedef enum {
    VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE,  /**< 4 byte Tx timestamp */
    VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE, /**< 10 byte Tx timestamp */
} vtss_phy_ts_fifo_timestamp_len_t;

/**
 * \brief defines the Transparent Clock Operating Mode.
 * \note There are two Modes TC can work:
 *  (a) Mode A: called SUB and ADD Mode where the local time is subtracted
 *      from the correction field at ingress and added at egress port.
 *  (b) Mode B: also called SUB_ADD Mode which uses reserve bytes (or append
 *      at the end of frame by replacing CRC) in PTP header to write
 *      RX_timestamp.
 *  (c) Mode C: also called 48-bit Mode. This mode uses 48-bits of the CF. 
 *      This mode is similar to Mode A. At ingress local time is subtracted 
 *      from CF and local time is added at egress. 
 *  Also note that TC operating Mode must be same for all the ports in
 *  the system.
 **/
typedef enum {
    VTSS_PHY_TS_TC_OP_MODE_A = 1, /**< Sub local time at ingress and add at egress from CF */
    VTSS_PHY_TS_TC_OP_MODE_B = 0, /**< RX_timestamp using reserved bytes or append at the end as defined in vtss_phy_ts_rxtimestamp_pos_t */
    VTSS_PHY_TS_TC_OP_MODE_C = 2, /**< Sub local time at ingress and add at egress from CF and use 48 bits in CF */
} vtss_phy_ts_tc_op_mode_t;

/**
 * \brief Define the Channel selection for 8487.
 **/
#define  VTSS_PHY_TS_8487_XAUI_SEL_0 0x01  /**< Select XAUI Lane - 0 */
#define  VTSS_PHY_TS_8487_XAUI_SEL_1 0x02 /**< Select XAUI Lane - 1 */
typedef u32 vtss_phy_ts_8487_xaui_sel_t; /**< XAUI Lane-0 or Lane-1 or both */

/**
 * \brief Defines the initial parameters to be passed to init function
 **/
typedef struct {
    vtss_phy_ts_clockfreq_t           clk_freq;  /**< reference clock frequency */
    vtss_phy_ts_clock_src_t           clk_src;   /**< clock source          */
    vtss_phy_ts_rxtimestamp_pos_t     rx_ts_pos; /**< Rx timestamp position */
    vtss_phy_ts_rxtimestamp_len_t     rx_ts_len; /**< Rx timestamp length */
    vtss_phy_ts_fifo_mode_t           tx_fifo_mode; /**< Tx TSFIFO access mode */
    vtss_phy_ts_fifo_timestamp_len_t  tx_ts_len; /**< timestamp size in Tx TSFIFO */
    BOOL                              tx_fifo_spi_conf; /**< Modify default 1588_spi configuration, applicable only on PHYs with SPI timestamp fifo support */
    u8                                tx_fifo_hi_clk_cycs; /**< Number of clock periods that the spi_clk is high */
    u8                                tx_fifo_lo_clk_cycs; /**< Number of clock periods that the spi_clk is low */
    vtss_phy_ts_8487_xaui_sel_t       xaui_sel_8487; /**< 8487 XAUI lane selection*/
#if defined (VTSS_SW_OPTION_REMOTE_TS_PHY)
    BOOL                              remote_phy;    /**< TRUE if the phy is remote */
#endif /* VTSS_SW_OPTION_REMOTE_TS_PHY */
    vtss_phy_ts_tc_op_mode_t          tc_op_mode; /**< TC operating mode */
    BOOL                              auto_clear_ls; /**< Load and Save of LTC are auto cleared */
    BOOL                              macsec_ena;       /**< MACsec is enabled or disabled */
    BOOL                              chk_ing_modified;/**< True if the flag bit needs to be modified in ingress and thus in egress */
    BOOL                              one_step_txfifo; /**< used when transmitting Delay_Req in one step mode. FALSE when correctionfield update is used instead */
} vtss_phy_ts_init_conf_t;

/**
 * \brief Init timestamp block
 * \note Init has to be called for each port in the time stamp block.
 *
 * \param inst    [IN]     Target instance reference
 * \param port_no [IN]     Port number
 * \param conf    [IN]     Init config parameters
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_init(const vtss_inst_t               inst,
                         const vtss_port_no_t            port_no,
                         const  vtss_phy_ts_init_conf_t  *const conf);


/**
 * \brief Get the timestamp init config parameters
 *
 * \param inst      [IN]     Target instance reference
 * \param port_no   [IN]     Port number
 * \param init_done [OUT]    Timestamp init done or not for the port
 * \param conf      [OUT]    Init config parameters
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_init_conf_get(const vtss_inst_t     inst,
                         const vtss_port_no_t           port_no,
                         BOOL  *const                   init_done,
                         vtss_phy_ts_init_conf_t        *const conf);

#ifdef VTSS_FEATURE_PTP_DELAY_COMP_ENGINE
/**
 * \brief Init timestamp block
 * \note Init has to be called for each port in the delay compensation engine.
 *
 * \param inst    [IN]     Target instance reference
 * \param port_no [IN]     Port number
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_dce_init(const vtss_inst_t inst,
                          const vtss_port_no_t port_no);

/**
 * \brief Set the delay compensation for ingress path.
 * \note Delay compensation is taken as TimeInterval which is 48bit nanosec + 16bit
 *  sub-nanosec though HW supports scaled nanosec which is 16 bit nanosec +
 *  16 bit sub-nanosec, i.e. the range is -2^15 (+2^15-2^-16).
 *
 * \param inst       [IN]      handle to an API instance
 * \param port_no    [IN]      port number
 * \param delay_comp [IN]      ingress delay 
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_ingress_delay_comp_set(const vtss_inst_t     inst,
                                           const vtss_port_no_t  port_no,
                                           const vtss_timeinterval_t    *const delay_comp);
/**
 * \brief Get delay compensation for ingress path.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param delay_comp [OUT]      ingress delay 
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_ingress_delay_comp_get(const vtss_inst_t     inst,
                                           const vtss_port_no_t  port_no,
                                           vtss_timeinterval_t          *const delay_comp);

/**
 * \brief Set the delay compensation for egress path.
 * \note Delay compensation is taken as TimeInterval which is 48bit nanosec + 16bit
 *  sub-nanosec though HW supports scaled nanosec which is 16 bit nanosec +
 *  16 bit sub-nanosec, i.e. the range is -2^15 (+2^15-2^-16).
 *
 * \param inst       [IN]      handle to an API instance
 * \param port_no    [IN]      port number
 * \param delay_comp [IN]      egress delay 
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_egress_delay_comp_set(const vtss_inst_t     inst,
                                          const vtss_port_no_t  port_no,
                                          const vtss_timeinterval_t    *const delay_comp);
/**
 * \brief Get delay compensation for egress path.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param delay_comp [OUT]      egress delay 
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_egress_delay_comp_get(const vtss_inst_t     inst,
                                          const vtss_port_no_t  port_no,
                                          vtss_timeinterval_t          *const delay_comp);
#endif /*  VTSS_FEATURE_PTP_DELAY_COMP_ENGINE */

/**
 * \brief enum for n-phase samplers
**/
typedef enum {
    VTSS_PHY_TS_NPHASE_PPS_O,    /**< N-Phase sampler for PPS_O */
    VTSS_PHY_TS_NPHASE_PPS_RI,   /**< N-Phase sampler for PPS_RI */
    VTSS_PHY_TS_NPHASE_EGR_SOF,  /**< N-Phase sampler for egress SOF */
    VTSS_PHY_TS_NPHASE_ING_SOF,  /**< N-Phase sampler for ingress SOF */
    VTSS_PHY_TS_NPHASE_LS,       /**< N-Phase sampler for Load/Save */
    VTSS_PHY_TS_NPHASE_MAX,      /**< Max N-Phase samplers */
} vtss_phy_ts_nphase_sampler_t;

/**
 * \brief n-phase status
**/
typedef struct {
    BOOL enable;      /**< Enabled status*/
    BOOL CALIB_ERR;   /**< Calibration error */
    BOOL CALIB_DONE;  /**< Calibration done */
} vtss_phy_ts_nphase_status_t;

/**
 * \brief Get N-Phase sampler status.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param sampler    [IN]       N-Phase sampler type
 * \param status     [OUT]      status 
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_nphase_status_get(const vtss_inst_t     inst,
                                      const vtss_port_no_t  port_no,
                                      vtss_phy_ts_nphase_sampler_t sampler,
                                      vtss_phy_ts_nphase_status_t *const status);
/**
 * \brief 1588 block reset
 **/

#define VTSS_PHY_TS_INGR_DATAPATH_RESET         0x01  /**< chip's ingress data path in the 1588 processing block */
#define VTSS_PHY_TS_EGR_DATAPATH_RESET          0x02  /**< chip's egress data path in the 1588 processing block */
#define VTSS_PHY_TS_INGR_LTC1_RESET             0x04  /**< Ingress LTC clock domain logic for this channel */
#define VTSS_PHY_TS_EGR_LTC2_RESET              0x08  /**< Egress LTC clock domain logic for this channel*/
#define VTSS_PHY_TS_EGR_FIFO_RESET              0x10  /**< Egress FIFO reset */

#if defined(VTSS_PHY_TS_SPI_CLK_THRU_PPS0)
/**
 * \brief Enable/disable New SPI mode for 8574-15 (Rev A & Rev B) that uses
 *  PPS0 pin as the new SPI_CLK.
 * \note This will activate the New SPI bus while enabled. User must 
 *  make note of the following:
 *  (1) SPI mode to access TS_FIFO has to be mentioned in vtss_phy_ts_init.
 *  (2) Both the ports of a block must have same configuration in terms of
 *      FIFO access mode i.e. MDIO, Old SPI Mode or New SPI mode. Also Old
 *      and New SPI cannot be mixed between blocks of a chip and both the
 *      blocks must be in same SPI mode i.e. both must be either Old SPI
 *      or New SPI.
 *  (3) This must be the last step after all the config done for both the
 *      ports of the block.
 *  (4) This is required/supported for 8574-15 RevA and RevB, not for 
 *      8487/8488-15.
 *
 * \param inst    [IN]     Target instance reference
 * \param port_no [IN]     Port number
 * \param enable  [IN]     enable/disable of New SPI. If tx_fifo_mode is
 *                         VTSS_PHY_TS_FIFO_MODE_SPI:
 *                         disable => SPI is in Old SPI Mode
 *                         enable => SPI in New SPI Mode
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_new_spi_mode_set(const vtss_inst_t          inst,
                                     const vtss_port_no_t       port_no,
                                     const BOOL                 enable);

/**
 * \brief Get New SPI mode for 8574-15 (Rev A & Rev B) described above
 *
 * \param inst    [IN]     Target instance reference
 * \param port_no [IN]     Port number
 * \param mode    [OUT]    Status of new SPI mode
 *                         disable => SPI is in Old SPI Mode
 *                         enable => SPI in New SPI Mode
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_new_spi_mode_get(const vtss_inst_t       inst,
                                     const vtss_port_no_t    port_no,
                                     BOOL                    *const mode);
#endif /* VTSS_PHY_TS_SPI_CLK_THRU_PPS0 */

/**
 * \brief Update the PHY timestamping block to predict the correct latency.
 * \note This function should be called when changing the PHY oper mode. Eg:LAN to WAN 
 * The application must configure the Latency values corresponding to the active mode.
 *
 * \param inst    [IN]     Target instance reference
 * \param port_no [IN]     Port number
 *
 * \return Return code.
 **/
vtss_rc vtss_phy_ts_phy_oper_mode_change(const vtss_inst_t          inst,
                                         const vtss_port_no_t       port_no);

/**
 * \brief Set the the 1588 block CSR registers.
 *
 * \param inst         [IN]      handle to an API instance
 * \param port_no      [IN]      port number
 * \param blk_id       [IN]      1588 CSR block Index [0-7]
 * \param csr_address  [IN]      1588 CSR block Register Offset [0x00 - 0x7f]
 * \param value        [IN]      32 bit value
 *
 * \return Return code.
 **/

extern vtss_rc vtss_phy_1588_csr_reg_write(const vtss_inst_t inst,
                                           const vtss_port_no_t port_no,
                                           const u32 blk_id,
                                           const u16 csr_address,
                                           const u32 *const value);

/**
 * \brief get the the 1588 block CSR registers.
 *
 * \param inst         [IN]      handle to an API instance
 * \param port_no      [IN]      port number
 * \param blk_id       [IN]      1588 CSR block Index [0-7]
 * \param csr_address  [IN]      1588 CSR block Register Offset [0x00 - 0x7f]
 * \param value        [OUT]     32 bit value
 *
 * \return Return code.
 **/

extern vtss_rc vtss_phy_1588_csr_reg_read(const vtss_inst_t inst,
                                          const vtss_port_no_t port_no,
                                          const u32 blk_id,
                                          const u16 csr_address,
                                          u32 *const value);


/**
 * \brief Defines the params for FIFO SYNC function
 **/
typedef struct {
    BOOL    detect_only;                        /**< TS FIFO OOS Detect only, no recovery, Only for Tesla */
    vtss_phy_ts_engine_t eng_recov;             /**< Main Engine used for recovery, Only for Tesla*/
    vtss_phy_ts_engine_t eng_minE;              /**< Mini-E Engine used for recovery, Only for Tesla */
    BOOL      skip_rev_check;                 /**< To force execution, regardless of revision */
} vtss_phy_ts_fifo_conf_t;


/**
 *\brief Viper 1588 FIFO reset
 *
 *\param inst      [IN]  Target instance reference.
 *\param port_no   [IN]  Port number.
 *\param fifo_conf [IN] FIFO algorithm Operation mode.
 *
 *\return Return Code.
 **/


vtss_rc vtss_phy_ts_viper_fifo_reset(const vtss_inst_t               inst,
                                     const vtss_port_no_t            port_no,
                                     const vtss_phy_ts_fifo_conf_t *fifo_conf);


/**
 * \brief PTP Event Message TYPES.
 * \note  4 Types of Event messages.
 *
 **/

typedef enum {
    VTSS_PHY_TS_PTP_MESSAGE_TYPE_SYNC,
    VTSS_PHY_TS_PTP_MESSAGE_TYPE_DELAY_REQ,
    VTSS_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_REQ_MSG,
    VTSS_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_RESP_MSG,
} vtss_phy_ts_ptp_message_type_t;

/**
 * \brief Clear Correction field for specified PTP message type.
 *
 * \param inst         [IN]      handle to an API instance
 * \param port_no      [IN]      port number
 * \param ingress      [IN]      TRUE if Ingress elses Egress
 * \param eng_id       [IN]      1588 Engine ID
 * \param act_id       [IN]      1588 Action ID
 * \param msgtype      [IN]      PTP Message Type
 *
 * \return Return code.
 **/

vtss_rc vtss_phy_ts_flow_clear_cf_set(const vtss_inst_t                     inst,
		                      const vtss_port_no_t                  port_no,
		                      BOOL                                  ingress,
		                      const vtss_phy_ts_engine_t            eng_id,
		                      u8                                    act_id,
		                      const vtss_phy_ts_ptp_message_type_t  msgtype);

#ifdef __cplusplus
}
#endif
#endif /* VTSS_OPT_PHY_TIMESTAMP */
