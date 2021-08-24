// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_PHY_TS_
#define _MICROCHIP_ETHERNET_SWITCH_API_PHY_TS_

#include <microchip/ethernet/common.h>
#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/**
 * \brief parameter for setting the alternative clock mode.
 */
/** \brief external clock output configuration. */
typedef struct mesa_phy_ts_alt_clock_mode_s {
    mesa_bool_t pps_ls_lpbk; /**< output PPS is loopback to L/S input pin */
    mesa_bool_t ls_lpbk;     /**< L/S act as output pin at 1PPS */
    mesa_bool_t ls_pps_lpbk; /**< L/S connected to PPS out */
} mesa_phy_ts_alt_clock_mode_t CAP(PHY_TS);

/**
 * \brief Get the latest saved nanosec counter from the alternative clock.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param saved [OUT]           latest saved value.
 *
 * \return Return code.
 */

mesa_rc mesa_phy_ts_alt_clock_saved_get(const mesa_inst_t    inst,
                                        const mesa_port_no_t port_no,
                                        uint32_t             *const saved)
    CAP(PHY_TS);

/**
 * \brief Get the alternative external clock mode.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]     port number
 * \param phy_alt_clock_mode [OUT]  alternative clock mode.
 *
 * \return Return code.
 */
mesa_rc mesa_phy_ts_alt_clock_mode_get(const mesa_inst_t            inst,
                                       const mesa_port_no_t         port_no,
                                       mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_alt_clock_mode_set(const mesa_inst_t                  inst,
                                       const mesa_port_no_t               port_no,
                                       const mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
    CAP(PHY_TS);


/**
 * \brief  Set offset for the PPS generation.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param phy_pps_conf [IN]     pps configuration
 *
 * \return Return code.
 */
mesa_rc mesa_phy_ts_pps_conf_set(const mesa_inst_t            inst,
                                 const mesa_port_no_t         port_no,
                                 const mesa_phy_ts_pps_conf_t *const phy_pps_conf)
    CAP(PHY_TS);
/**
 * \brief  Get offset for the PPS generation.
 *
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param phy_pps_conf [OUT]    pps configuration
 *
 * \return Return code.
 */

mesa_rc mesa_phy_ts_pps_conf_get(const mesa_inst_t      inst,
                                 const mesa_port_no_t   port_no,
                                 mesa_phy_ts_pps_conf_t *const phy_pps_conf)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_ingress_latency_set(const mesa_inst_t         inst,
                                        const mesa_port_no_t      port_no,
                                        const mesa_timeinterval_t *const latency)
    CAP(PHY_TS);

/**
 * \brief Get the ingress latency.
 *
 * \param inst    [IN]       handle to an API instance
 * \param port_no [IN]       port number
 * \param latency [OUT]      ingress latency
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_ingress_latency_get(const mesa_inst_t    inst,
                                        const mesa_port_no_t port_no,
                                        mesa_timeinterval_t  *const latency)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_egress_latency_set(const mesa_inst_t         inst,
                                       const mesa_port_no_t      port_no,
                                       const mesa_timeinterval_t *const latency)
    CAP(PHY_TS);

/**
 * \brief Get the egress latency.
 *
 * \param inst    [IN]      handle to an API instance
 * \param port_no [IN]      port number
 * \param latency [OUT]     egress latency
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_egress_latency_get(const mesa_inst_t    inst,
                                       const mesa_port_no_t port_no,
                                       mesa_timeinterval_t  *const latency)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_path_delay_set(const mesa_inst_t         inst,
                                   const mesa_port_no_t      port_no,
                                   const mesa_timeinterval_t *const path_delay)
    CAP(PHY_TS);

/**
 * \brief Get the path delay.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param path_delay [OUT]      path delay
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_path_delay_get(const mesa_inst_t    inst,
                                   const mesa_port_no_t port_no,
                                   mesa_timeinterval_t  *const path_delay)
    CAP(PHY_TS);

/**
 * \brief Set the delay asymmetry.
 * \note Asymmetry is taken as TimeInterval which is 48bit nanosec + 16bit
 *  sub-nanosec though HW supports scaled nanosec which is 16 bit nanosec +
 *  16 bit sub-nanosec, i.e. the range is  -2^15 (+2^15-2^-16).
 *
 * \param inst       [IN]      handle to an API instance
 * \param port_no    [IN]      port number
 * \param delay_asym [IN]      link delay asymmetry
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_delay_asymmetry_set(const mesa_inst_t         inst,
                                        const mesa_port_no_t      port_no,
                                        const mesa_timeinterval_t *const delay_asym)
    CAP(PHY_TS);

/**
 * \brief Get the delay asymmetry.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param delay_asym [OUT]      link delay asymmetry
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_delay_asymmetry_get(const mesa_inst_t    inst,
                                        const mesa_port_no_t port_no,
                                        mesa_timeinterval_t  *const delay_asym)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_ptptime_set(const mesa_inst_t          inst,
                                const mesa_port_no_t       port_no,
                                const mesa_phy_timestamp_t *const ts)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_ptptime_set_done(const mesa_inst_t    inst,
                                     const mesa_port_no_t port_no)
    CAP(PHY_TS);


/**
 * \brief Arm the local time of the PHY so that in next pps it can be read.
 * \note Once armed, in next pps it will load the local time and can be read
 *  using mesa_phy_ts_ptptime_get. Must call before get the local time of
 *  the PHY.
 *
 * \param inst    [IN]     handle to an API instance.
 * \param port_no [IN]     port number
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_ptptime_arm(const mesa_inst_t    inst,
                                const mesa_port_no_t port_no)
    CAP(PHY_TS);

/**
 * \brief Get the armed PTP time from the PHY.
 *
 * \param inst    [IN]     handle to an API instance
 * \param port_no [IN]     port number
 * \param ts      [OUT]    local time in PHY
 *
 * \return Return code.  If the time has not been updated after the
 *  mesa_phy_ts_ptptime_arm function is called, it returns error.
 **/
mesa_rc mesa_phy_ts_ptptime_get(const mesa_inst_t    inst,
                                const mesa_port_no_t port_no,
                                mesa_phy_timestamp_t *const ts)
    CAP(PHY_TS);

/**
 * \brief Get the PTP time from the PHY load registers.
 *
 * \param inst    [IN]     handle to an API instance
 * \param port_no [IN]     port number
 * \param ts      [OUT]    local time in PHY
 *
 * \return Return code.  If the time has not been updated after the
 *  mesa_phy_ts_ptptime_arm function is called, it returns error.
 **/
mesa_rc mesa_phy_ts_load_ptptime_get(const mesa_inst_t    inst,
                                     const mesa_port_no_t port_no,
                                     mesa_phy_timestamp_t *const ts)
    CAP(PHY_TS);

/**
 * \brief PHY timestamp in seconds and nanoseconds (10 bytes Timestamp)
 **/
typedef struct {
    mesa_bool_t ip_enable; /**< Serial ToD Input Enable */
    mesa_bool_t op_enable; /**< Serial ToD Output Enable */
    mesa_bool_t ls_inv;    /**< Invert the polarity of Load Save */
} mesa_phy_ts_sertod_conf_t CAP(PHY_TS);

/**
 * \brief Set Enable/Disable Serial ToD.
 *
 * \param inst        [IN]     handle to an API instance
 * \param port_no     [IN]     port number
 * \param sertod_conf [IN]     configure Serial ToD input
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_sertod_set(const mesa_inst_t               inst,
                               const mesa_port_no_t            port_no,
                               const mesa_phy_ts_sertod_conf_t *const sertod_conf)
    CAP(PHY_TS);

/**
 * \brief Get Enable/Disable Serial ToD.
 *
 * \param inst    [IN]        handle to an API instance
 * \param port_no [IN]        port number
 * \param sertod_conf [OUT]   Serial ToD configuration
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_sertod_get(const mesa_inst_t         inst,
                               const mesa_port_no_t      port_no,
                               mesa_phy_ts_sertod_conf_t *const sertod_conf)
    CAP(PHY_TS);

/**
 * \brief Set load pulse delay.
 *
 * \param inst        [IN]     handle to an API instance
 * \param port_no     [IN]     port number
 * \param delay       [IN]     delay value in nano seconds
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_loadpulse_delay_set(const mesa_inst_t    inst,
                                        const mesa_port_no_t port_no,
                                        const uint16_t       *const delay)
    CAP(PHY_TS);

/**
 * \brief Get load pulse delay
 *
 * \param inst    [IN]        handle to an API instance
 * \param port_no [IN]        port number
 * \param delay   [OUT]       delay value in nano seconds
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_loadpulse_delay_get(const mesa_inst_t    inst,
                                        const mesa_port_no_t port_no,
                                        uint16_t             *const delay)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_clock_rateadj_set(const mesa_inst_t              inst,
                                      const mesa_port_no_t           port_no,
                                      const mesa_phy_ts_scaled_ppb_t *const adj)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_clock_rateadj_get(const mesa_inst_t        inst,
                                      const mesa_port_no_t     port_no,
                                      mesa_phy_ts_scaled_ppb_t *const adj)
    CAP(PHY_TS);

/**
 * \brief Adjust ppm of the local clock rate .
 *
 * \param inst    [IN]     handle to an API instance.
 * \param port_no [IN]     port number
 * \param adj     [IN]     Clock ratio frequency offset in units of scaled ppb
 *                         (parts per billion). ratio > 0 => clock runs faster.
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_clock_rateadj_ppm_set(const mesa_inst_t              inst,
                                          const mesa_port_no_t           port_no,
                                          const mesa_phy_ts_scaled_ppb_t *const adj)
    CAP(PHY_TS);

/**
 * \brief Get the clock rate ppm adjustment value.
 *
 * \param inst    [IN]     handle to an API instance.
 * \param port_no [IN]     port number
 * \param adj     [OUT]    Clock ratio frequency offset in scaled ppb.
 *                         ratio > 0 => clock runs faster
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_clock_rateadj_ppm_get(const mesa_inst_t        inst,
                                          const mesa_port_no_t     port_no,
                                          mesa_phy_ts_scaled_ppb_t *const adj)
    CAP(PHY_TS);

/**
 * \brief Increment/decrement the LTC clock value by 1 ns.
 *
 * \param inst    [IN]      handle to an API instance.
 * \param port_no [IN]      port number
 * \param incr    [IN]      increment/decrement: TRUE = incr, FALSE = decr
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_ptptime_adj1ns(const mesa_inst_t    inst,
                                   const mesa_port_no_t port_no,
                                   const mesa_bool_t    incr)
    CAP(PHY_TS);

/**
 * \brief Subtract offset from the current time
 *
 * \param inst    [IN]      handle to an API instance.
 * \param port_no [IN]      port number
 * \param offset  [IN]      offset in nano seconds
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_timeofday_offset_set(const mesa_inst_t    inst,
                                         const mesa_port_no_t port_no,
                                         const int32_t        offset)
    CAP(PHY_TS);

/**
 * \brief parameter describing various Tx TSFIFO status.
 **/
typedef enum {
    MESA_PHY_TS_TODADJ_INPROGRESS, /**< ToD Adjustment is in progress */
    MESA_PHY_TS_TODADJ_DONE,       /**< ToD Adjustment is completed */
    MESA_PHY_TS_TODADJ_FAIL,       /**< ToD Adjustment Failed */
} mesa_phy_ts_todadj_status_t CAP(PHY_TS);

/**
 * \brief Return the status of the LTC time adjustment
 *
 * \param inst               [IN]  handle to an API instance.
 * \param port_no            [IN]  port number
 * \param ongoing_adjustment [OUT] LTC offset operation status
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_ongoing_adjustment(const mesa_inst_t           inst,
                                       const mesa_port_no_t        port_no,
                                       mesa_phy_ts_todadj_status_t *const ongoing_adjustment)
    CAP(PHY_TS);

/**
 * \brief Frequency systhesis pulse configuration
**/

typedef struct mesa_phy_ltc_freq_synth_s {
    mesa_bool_t  enable;          /**< Enable/Disable frequency synthesis pulse */
    uint8_t      high_duty_cycle; /**< Number of clock cycles pulse is high */
    uint8_t      low_duty_cycle;  /**< Number of clock cycles pulse is low */
} mesa_phy_ltc_freq_synth_t CAP(PHY_TS);

/**
 * \brief Return the status of the LTC time adjustment
 *
 * \param inst               [IN]  handle to an API instance.
 * \param port_no            [IN]  port number
 * \param ltc_freq_synthesis [IN]  Frequency synthesis pulse configuration
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_set(const mesa_inst_t               inst,
                                             const mesa_port_no_t            port_no,
                                             const mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
    CAP(PHY_TS);

/**
 * \brief Return the status of the LTC time adjustment
 *
 * \param inst               [IN]  handle to an API instance.
 * \param port_no            [IN]  port number
 * \param ltc_freq_synthesis [OUT]  Frequency synthesis pulse configuration
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_get(const mesa_inst_t         inst,
                                             const mesa_port_no_t      port_no,
                                             mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis )
    CAP(PHY_TS);

/** \brief SPI daisy chain configuration */
typedef struct {
    mesa_bool_t spi_daisy_input;  /**< Enable SPI daisy-chain input port */
    mesa_bool_t spi_daisy_output; /**< Enable SPI daisy-chain output port */
} mesa_phy_daisy_chain_conf_t CAP(PHY_TS);
/**
 * \brief  configure the daisy chain for TS FIFO
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param daisy_chain [IN]   daisy-chaining configuration
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_daisy_conf_set(const mesa_inst_t                 inst,
                                const mesa_port_no_t              port_no,
                                const mesa_phy_daisy_chain_conf_t *const daisy_chain)
    CAP(PHY_TS);

/**
 * \brief getting the daisy chain for TS FIFO
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param daisy_chain [IN]   daisy-chaining configuration
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_daisy_conf_get(const mesa_inst_t           inst,
                                const mesa_port_no_t        port_no,
                                mesa_phy_daisy_chain_conf_t *const daisy_chain)
    CAP(PHY_TS);

/**
 * \brief Defines Tx TSFIFO signature mask.
 **/
#define MESA_PHY_TS_FIFO_SIG_SRC_IP          0x01  /**< Src IP address: inner IP for IP-over-IP */
#define MESA_PHY_TS_FIFO_SIG_DEST_IP         0x02  /**< Dest IP address */

#define MESA_PHY_TS_FIFO_SIG_MSG_TYPE        0x04  /**< Message type */
#define MESA_PHY_TS_FIFO_SIG_DOMAIN_NUM      0x08  /**< Domain number */
#define MESA_PHY_TS_FIFO_SIG_SOURCE_PORT_ID  0x10  /**< Source port identity */
#define MESA_PHY_TS_FIFO_SIG_SEQ_ID          0x20  /**< PTP frame Sequence ID */

#define MESA_PHY_TS_FIFO_SIG_DEST_MAC        0x40  /**< Dest MAC address */

typedef uint32_t mesa_phy_ts_fifo_sig_mask_t CAP(PHY_TS); /**< Signature mask which can be OR of multiple fields above */

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
mesa_rc mesa_phy_ts_fifo_sig_set(const mesa_inst_t                 inst,
                                 const mesa_port_no_t              port_no,
                                 const mesa_phy_ts_fifo_sig_mask_t sig_mask)
    CAP(PHY_TS);

/**
 * \brief Get frame signature mask in Tx TSFIFO.
 * \note As described in mesa_phy_ts_fifo_sig_set, any of the ports within
 *  IP timestamp block can be used to get the signature.
 *
 * \param inst     [IN]         handle to an API instance
 * \param port_no  [IN]         port number
 * \param sig_mask [OUT]        signature mask
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_fifo_sig_get(const mesa_inst_t           inst,
                                 const mesa_port_no_t        port_no,
                                 mesa_phy_ts_fifo_sig_mask_t *const sig_mask)
    CAP(PHY_TS);

/**
 * Following Tx TSFIFO related API are used if FIFO access mode is set as
 * PHY_TS_FIFO_MODE_NORMAL. In SPI mode, timestamps are pushed into SPI
 * interface as soon as they are available.
 **/

/**
 * \brief parameter describing various Tx TSFIFO status.
 **/
typedef enum {
    MESA_PHY_TS_FIFO_SUCCESS,  /**< FIFO read success */
    MESA_PHY_TS_FIFO_OVERFLOW, /**< FIFO overflow */
} mesa_phy_ts_fifo_status_t CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_fifo_empty(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no)
    CAP(PHY_TS);

/**
 * \brief Tx TSFIFO entry signature
 **/
typedef struct {
    mesa_phy_ts_fifo_sig_mask_t sig_mask;              /**< valid signature fields */
    uint8_t                     msg_type;              /**< PTP message type */
    uint8_t                     domain_num;            /**< domain number in PTP message */
    uint8_t                     src_port_identity[10]; /**< source port identity in PTP message */
    uint16_t                    sequence_id;           /**< PTP message sequence ID */
    uint32_t                    dest_ip;               /**< Destination IP */
    uint32_t                    src_ip;                /**< Source IP */
    uint8_t                     dest_mac[6];           /**< Destination MAC */
} mesa_phy_ts_fifo_sig_t CAP(PHY_TS);

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
typedef void (*mesa_phy_ts_fifo_read)(const mesa_inst_t              inst,
                                      const mesa_port_no_t           port_no,
                                      const mesa_phy_timestamp_t     *const ts,
                                      const mesa_phy_ts_fifo_sig_t   *const sig,
                                      void                           *cntxt,
                                      const mesa_phy_ts_fifo_status_t status)
    CAP(PHY_TS);

/**
 * \brief Install callback to read data (signature + timestamp) from Tx TSFIFO.
 * \note Registered callback will be called for each entry in TSFIFO from
 *  mesa_phy_ts_fifo_empty function.
 *
 * \param inst  [IN]            handle to an API instance
 * \param rd_cb [IN]            read callback
 * \param cntxt [IN]            context to be returned in callback
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_fifo_read_install(const mesa_inst_t     inst,
                                      mesa_phy_ts_fifo_read rd_cb,
                                      void                  *cntxt)
    CAP(PHY_TS);

/**
 * \brief Get the fifo read callback function installed.
 *
 * \param inst  [IN]            handle to an API instance
 * \param rd_cb [OUT]           read callback
 * \param cntxt [OUT]           context
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_fifo_read_cb_get(const mesa_inst_t     inst,
                                     mesa_phy_ts_fifo_read *rd_cb,
                                     void                  **cntxt)
    CAP(PHY_TS);

/**
 * Analyzer API
 **/

/**
 * \brief Analyzer supported frame encapsulation type
 **/
typedef enum {
    /* PTP encap */
    MESA_PHY_TS_ENCAP_ETH_PTP,
    MESA_PHY_TS_ENCAP_ETH_IP_PTP,
    MESA_PHY_TS_ENCAP_ETH_IP_IP_PTP,
    MESA_PHY_TS_ENCAP_ETH_ETH_PTP,
    MESA_PHY_TS_ENCAP_ETH_ETH_IP_PTP,
    MESA_PHY_TS_ENCAP_ETH_MPLS_IP_PTP,
    MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP,
    MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP,
    MESA_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP,
    /* OAM encap */
    MESA_PHY_TS_ENCAP_ETH_OAM,
    MESA_PHY_TS_ENCAP_ETH_ETH_OAM,
    MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM,
    MESA_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM, /* MPLS-TP OAM */

    MESA_PHY_TS_ENCAP_ANY, /* Timestamp all packets */
    MESA_PHY_TS_ENCAP_ETH_GEN, /* Generic timestamping */
    MESA_PHY_TS_ENCAP_NONE,
} mesa_phy_ts_encap_t CAP(PHY_TS);

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
 * same i.e. if engine MESA_PHY_TS_PTP_ENGINE_ID_0 in ingress is configured as
 * strict flow match then engine MESA_PHY_TS_PTP_ENGINE_ID_0 in egress has to be
 * in strict flow match. Also OAM engine 2A and 2B can not have different flow
 * match mode i.e engine 2A and 2B for ingress and egress must have same flow
 * match mode.
 * (4) OAM engine does not support TSFIFO and it can not be used for PTP
 * application. But OAM application can use PTP engine.
 * (5) OAM engine 2B only support OAM application with single ethernet encap
 * i.e. OAM-over-ETH
 **/
typedef enum {
    MESA_PHY_TS_PTP_ENGINE_ID_0, /**< PTP engine 0 */
    MESA_PHY_TS_PTP_ENGINE_ID_1, /**< PTP engine 1 */
    MESA_PHY_TS_OAM_ENGINE_ID_2A, /**< OAM engine 2A, no PTP support */
    MESA_PHY_TS_OAM_ENGINE_ID_2B, /**< OAM engine 2B, no PTP; only OAM-over-ETH support */
    MESA_PHY_TS_ENGINE_ID_INVALID, /**< Invalid Engine ID */
} mesa_phy_ts_engine_t CAP(PHY_TS);

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
    MESA_PHY_TS_ENG_FLOW_MATCH_ANY,    /**< match any flow in comparators */
    MESA_PHY_TS_ENG_FLOW_MATCH_STRICT  /**< strict flow match */
} mesa_phy_ts_engine_flow_match_t CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_ingress_engine_init(const mesa_inst_t                     inst,
                                        const mesa_port_no_t                  port_no,
                                        const mesa_phy_ts_engine_t            eng_id,
                                        const mesa_phy_ts_encap_t             encap_type,
                                        const uint8_t                         flow_st_index,
                                        const uint8_t                         flow_end_index,
                                        const mesa_phy_ts_engine_flow_match_t flow_match_mode)
    CAP(PHY_TS);

/**
 * \brief Defines the basic engine parameters passed to the engine_init_conf_get() function
 **/
typedef struct {
    mesa_bool_t                     eng_used; /**< allocated the engine to application */
    mesa_phy_ts_encap_t             encap_type; /**< engine encapsulation */
    mesa_phy_ts_engine_flow_match_t flow_match_mode; /**< strict/non-strict flow match */
    uint8_t                         flow_st_index; /**< start index of flow */
    uint8_t                         flow_end_index; /**< end index of flow */
}mesa_phy_ts_eng_init_conf_t CAP(PHY_TS);



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

mesa_rc mesa_phy_ts_ingress_engine_init_conf_get(const mesa_inst_t           inst,
                                                 const mesa_port_no_t        port_no,
                                                 const mesa_phy_ts_engine_t  eng_id,
                                                 mesa_phy_ts_eng_init_conf_t *const init_conf)
    CAP(PHY_TS);


/**
 * \brief Clear/release an analyzer ingress engine already initialized.
 *
 * \param inst            [IN]   handle to an API instance
 * \param port_no         [IN]   port number
 * \param eng_id          [IN]   engine ID
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_ingress_engine_clear(const mesa_inst_t          inst,
                                         const mesa_port_no_t       port_no,
                                         const mesa_phy_ts_engine_t eng_id)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_egress_engine_init(const mesa_inst_t                     inst,
                                       const mesa_port_no_t                  port_no,
                                       const mesa_phy_ts_engine_t            eng_id,
                                       const mesa_phy_ts_encap_t             encap_type,
                                       const uint8_t                         flow_st_index,
                                       const uint8_t                         flow_end_index,
                                       const mesa_phy_ts_engine_flow_match_t flow_match_mode)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_egress_engine_init_conf_get(const mesa_inst_t           inst,
                                                const mesa_port_no_t        port_no,
                                                const mesa_phy_ts_engine_t  eng_id,
                                                mesa_phy_ts_eng_init_conf_t *const init_conf)
    CAP(PHY_TS);


/**
 * \brief Clear/release an analyzer egress engine already initialized.
 *
 * \param inst            [IN]   handle to an API instance
 * \param port_no         [IN]   port number
 * \param eng_id          [IN]   engine ID
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_egress_engine_clear(const mesa_inst_t          inst,
                                        const mesa_port_no_t       port_no,
                                        const mesa_phy_ts_engine_t eng_id)
    CAP(PHY_TS);

/** \brief Ethernet per flow configuration */
typedef struct {
    mesa_bool_t  flow_en;  /**< flow enable/disable */

#define MESA_PHY_TS_ETH_ADDR_MATCH_48BIT            ((uint8_t)0x01) /**< Full 48-bit address match */
#define MESA_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST      ((uint8_t)0x02) /**< Match any unicast MAC addres */
#define MESA_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST    ((uint8_t)0x04) /**< Match any multicast MAC addres */
    uint8_t      addr_match_mode; /**< Multiple match can be possible using OR */
#define MESA_PHY_TS_ETH_MATCH_DEST_ADDR      ((uint8_t)0x00) /**< Match destination MAC address */
#define MESA_PHY_TS_ETH_MATCH_SRC_ADDR       ((uint8_t)0x01) /**< Match source MAC address */
#define MESA_PHY_TS_ETH_MATCH_SRC_OR_DEST    ((uint8_t)0x02) /**< Match source or destination MAC address */
    uint8_t      addr_match_select; /**< src or dest addr to be matched */
    uint8_t      mac_addr[6]; /**< addr to be matched, src or dest */

    mesa_bool_t  vlan_check; /**< TRUE=>verify configured VLAN tag configuration, FALSE=>parse VLAN tag if any, but don't check, for PBB I-tag is always checked */
    uint8_t      num_tag; /**< No of Tags (max 2 tag), for PBB at least I-tag should be present */
#define MESA_PHY_TS_TAG_TYPE_C    ((uint8_t)0x01) /**< Tag type: C */
#define MESA_PHY_TS_TAG_TYPE_S    ((uint8_t)0x02) /**< Tag type: S */
#define MESA_PHY_TS_TAG_TYPE_I    ((uint8_t)0x03) /**< Tag type: I */
#define MESA_PHY_TS_TAG_TYPE_B    ((uint8_t)0x04) /**< Tag type: B */
    uint8_t      outer_tag_type; /**< for PBB enabled with 2-tag, this must be B-tag */
    uint8_t      inner_tag_type; /**< for PBB this must be I-tag; also for single tag inner_tag is used */
#define MESA_PHY_TS_TAG_RANGE_NONE     ((uint8_t)0x00) /**< Neither inner nor outer tag allows range config */
#define MESA_PHY_TS_TAG_RANGE_OUTER    ((uint8_t)0x01) /**< Outer tag allows range config */
#define MESA_PHY_TS_TAG_RANGE_INNER    ((uint8_t)0x02) /**< Inner tag allows range config */
    uint8_t      tag_range_mode;  /**< for PBB no range check is allowed */
    union {
        struct {
            uint16_t    upper; /**< Upper value for outer tag range */
            uint16_t    lower; /**< Lower value for outer tag range */
        } range;  /**< tag in range */
        struct {
            uint16_t    val;  /**< Value */
            uint16_t    mask; /**< Mask */
        } value;  /**< tag in value/mask */
    } outer_tag; /**< Outer tag */
    union {
        struct {
            uint16_t    upper; /**< Upper value for inner tag range */
            uint16_t    lower; /**< Loower value for inner tag range */
        } range;  /**< tag in range */
        struct {
            uint16_t    val; /**< Value */
            uint16_t    mask; /**< Mask */
        } value;  /**< tag in value/mask */
        struct {
            uint32_t    val;   /**< 24-bit I-tag value */
            uint32_t    mask;  /**< 24-bit I-tag mask */
        } i_tag;  /**< I-tag in value/mask. This is applicable for PBB i.e. Eth1 comparator */
    } inner_tag; /**< Inner Tag*/
} mesa_phy_ts_eth_flow_conf_t; /**< Ethernet per flow config */

/**
 * \brief Analyzer Ethernet comparator configuration options
 * \note Common options apply all the flows within the comparator. Also there
 *  are per-flow configuration.
 **/
typedef struct {
    struct {
        mesa_bool_t  pbb_en; /**< PBB tag present, not applicable for Eth2 comparator */
        uint16_t     etype;  /**< The value of Ether type to be checked if Ethertype/length field is an Ethertype */
        uint16_t     tpid;   /**< VLAN TPID for S or B-tag */
    } comm_opt; /**< Ethernet common config */

    mesa_phy_ts_eth_flow_conf_t flow_opt[8]; /**< Ethernet per flow config */
} mesa_phy_ts_eth_conf_t CAP(PHY_TS); /**< ETH configuration */

/**< \brief IP per flow configuration */
typedef struct {
    mesa_bool_t  flow_en;  /**< flow enable/disable */
#define MESA_PHY_TS_IP_MATCH_SRC          0x00 /**< Match source IP address */
#define MESA_PHY_TS_IP_MATCH_DEST         0x01 /**< Match destination IP address */
#define MESA_PHY_TS_IP_MATCH_SRC_OR_DEST  0x02 /**< Match source or destination IP address */
    uint8_t    match_mode; /**< match src, dest or either IP address */
    union {
        struct {
            uint32_t    addr; /**< IPv4 address */
            uint32_t    mask; /**< IPv4 address mask */
        } ipv4; /**< IPv4 Address */
        struct {
            uint32_t    addr[4]; /**< IPv6 Address */
            uint32_t    mask[4]; /**<IPv6 Mask */
        } ipv6; /**< IPv6 Mask */
    } ip_addr;  /**< IPv4/IPv6 address to be matched */
} mesa_phy_ts_ip_flow_conf_t;

/**
 * \brief Analyzer IP comparator configuration options
 * \note Common options apply all the flows within the comparator. Also there
 *  are per flow configuration.
 **/
typedef struct {
    struct {
#define MESA_PHY_TS_IP_VER_4    0x01 /**< Version: IPv4 */
#define MESA_PHY_TS_IP_VER_6    0x02 /**< Version: IPv6 */
        uint8_t    ip_mode; /**< IPv4, IPv6 */
        /**< if next protocol is not UDP, next UDP fields are not used */
        uint16_t   sport_val; /**< UDP source port value */
        uint16_t   sport_mask; /**< UDP source port mask */
        uint16_t   dport_val; /**< UDP dest port value */
        uint16_t   dport_mask; /**< UDP dest port mask */
    } comm_opt; /**< IP common config */

    mesa_phy_ts_ip_flow_conf_t flow_opt[8]; /**< IP per flow config */
} mesa_phy_ts_ip_conf_t CAP(PHY_TS); /**< IP configuration */

/**
 * \brief MPLS level range
 **/
typedef struct {
    uint32_t    lower; /**< lower range value */
    uint32_t    upper; /**< upper range value */
} mesa_phy_ts_mpls_lvl_rng_t CAP(PHY_TS);

/**< \brief MPLS per flow configuration */
typedef struct {
    mesa_bool_t     flow_en;  /**< flow enable/disable */

#define MESA_PHY_TS_MPLS_STACK_DEPTH_1    ((uint8_t)0x01) /**< MPLS stack of depth 1 only allows */
#define MESA_PHY_TS_MPLS_STACK_DEPTH_2    ((uint8_t)0x02) /**< MPLS stack of depth 2 only allows */
#define MESA_PHY_TS_MPLS_STACK_DEPTH_3    ((uint8_t)0x04) /**< MPLS stack of depth 3 only allows */
#define MESA_PHY_TS_MPLS_STACK_DEPTH_4    ((uint8_t)0x08) /**< MPLS stack of depth 4 only allows */
    uint8_t         stack_depth; /**< depth of MPLS level; multiple depth match can be possible using OR */

#define MESA_PHY_TS_MPLS_STACK_REF_POINT_TOP    0x00 /**< Search starts from the top of the stack */
#define MESA_PHY_TS_MPLS_STACK_REF_POINT_END    0x01 /**< Search starts from the end of the stack */
    uint8_t         stack_ref_point; /**< Search direction for label matching: top to bottom or bottom to top */
    union {
        struct {
            mesa_phy_ts_mpls_lvl_rng_t  top; /**< Top level */
            mesa_phy_ts_mpls_lvl_rng_t  frst_lvl_after_top; /**< First label after the top label */
            mesa_phy_ts_mpls_lvl_rng_t  snd_lvl_after_top; /**< Second label after the top label */
            mesa_phy_ts_mpls_lvl_rng_t  thrd_lvl_after_top; /**< Third label after the top label */
        } top_down; /**< Top down configuration */
        struct {
            mesa_phy_ts_mpls_lvl_rng_t  end; /**< End level */
            mesa_phy_ts_mpls_lvl_rng_t  frst_lvl_before_end; /**< First label before the end label */
            mesa_phy_ts_mpls_lvl_rng_t  snd_lvl_before_end; /**< Second label before the end label */
            mesa_phy_ts_mpls_lvl_rng_t  thrd_lvl_before_end; /**< Third label before the end label */
        } bottom_up; /**< Bottom up configuration */
    } stack_level; /**< 4 level values; top_down or bottom_up depends on stack_ref_point */
} mesa_phy_ts_mpls_flow_conf_t;

/**
 * \brief Analyzer MPLS comparator configuration options
 **/
typedef struct {
    struct {
        mesa_bool_t           cw_en;  /**< flow uses psudowire control word or not */
    } comm_opt; /**< MPLS common config */

    mesa_phy_ts_mpls_flow_conf_t flow_opt[8]; /**< MPLS per flow config */
} mesa_phy_ts_mpls_conf_t CAP(PHY_TS); /**< MPLS configuration */

/**
 * \brief Analyzer ACH comparator configuration options
 * \note ACH uses the IP1 comparator for match. So IP1 and ACH can not be used
 * at the same time.
 **/
typedef struct {
    struct {
        struct {
            uint8_t    value; /**< 4-bits version */
            uint8_t    mask; /**< Mask */
        } version; /**< version number of the PWACH in value/mask; set mask 0 for don't care */
        struct {
            uint16_t   value; /**< Channel type value */
            uint16_t   mask; /**< Channel type mask */
        } channel_type; /**< PW Associated Channel Type in value/mask format */
        struct {
            uint16_t   value; /**< Protocol Identifier Value */
            uint16_t   mask; /**< Protocl Identifier Mask */
        } proto_id; /**< PID: identifier of payload as defined in RFC 5718, only for PTP */
    } comm_opt; /**< ACH common config */

    /* No flow config reqd for ACH */
} mesa_phy_ts_ach_conf_t CAP(PHY_TS); /**< ACH Configuration */

/**
 * \brief Analyzer Generic data configuration options using IP comparator
 *
 **/
typedef struct {
    struct {
        uint8_t    flow_offset;       /**< Offset of data pattern to match with current comparator */
        uint8_t    next_prot_offset;  /**< Offset of data pattern to match with next comparator */
    } comm_opt; /**< Generic Matching common configuration */

    struct {
        mesa_bool_t  flow_en;          /**< Enable the flow */
        uint32_t     data[4];          /**< Data byte pattern to match */
        uint32_t     mask[4];          /**< Mask of the matching pattern */
    } flow_opt[8]; /**< Generic matching config per flow */
} mesa_phy_ts_gen_conf_t CAP(PHY_TS);

/**
 * \brief Port to flow mapping within analyzer engine.
 * \note This is applicable for multi-channel timestamp block.
 **/
#define MESA_PHY_TS_ENG_FLOW_VALID_FOR_CH0  0x01 /**< Channel-0 mapped */
#define MESA_PHY_TS_ENG_FLOW_VALID_FOR_CH1  0x02 /**< Channel-1 mapped */
typedef uint8_t mesa_phy_ts_engine_channel_map_t CAP(PHY_TS); /**< Channel-0 or channel-1 or both the channels */

/**
 * \brief PTP engine flow configuration options
 **/
typedef struct {
    mesa_phy_ts_eth_conf_t  eth1_opt; /**< Eth-1 comparator */
    mesa_phy_ts_eth_conf_t  eth2_opt; /**< Eth-2 comparator; for single ETH encap, Eth-1 is used */
    mesa_phy_ts_ip_conf_t   ip1_opt;  /**< IP-1 comparator */
    mesa_phy_ts_ip_conf_t   ip2_opt;  /**< IP-2 comparator; for single IP encap, IP-1 is used */
    mesa_phy_ts_mpls_conf_t mpls_opt; /**< MPLS comparator */
    mesa_phy_ts_ach_conf_t  ach_opt;  /**< ACH: it uses the IP1 comparator, so IP1 and ACH can not enabled simultaneously */
} mesa_phy_ts_ptp_engine_flow_conf_t CAP(PHY_TS);

/**
 * \brief OAM engine flow configuration options
 **/
typedef struct {
    mesa_phy_ts_eth_conf_t  eth1_opt; /**< Eth-1 comparator */
    mesa_phy_ts_eth_conf_t  eth2_opt; /**< Eth-2 comparator; for single ETH encap, Eth-1 is used */
    mesa_phy_ts_mpls_conf_t mpls_opt; /**< MPLS comparator */
    mesa_phy_ts_ach_conf_t  ach_opt;  /**< ACH: it uses the IP1 comparator, so IP1 and ACH can not enabled simultaneously */
} mesa_phy_ts_oam_engine_flow_conf_t CAP(PHY_TS);


/**
 * \brief Generic engine flow configuration options
 **/
typedef struct {
    mesa_phy_ts_eth_conf_t eth1_opt; /**< Eth-1 comparator */
    mesa_phy_ts_gen_conf_t gen_opt;  /**< Generic : It uses IP1 comparator */
} mesa_phy_ts_generic_flow_conf_t CAP(PHY_TS);

/**
 * \brief Analyzer flow configuration options
 * \note Engine configuration will be parsed to know PTP or OAM flow based on
 * encapsulation type provided during engine allocation.
 **/
typedef struct {
    mesa_bool_t                       eng_mode;    /**< engine enable/disable */
    mesa_phy_ts_engine_channel_map_t  channel_map[8]; /**< maps flows to channel for multi-channel timestamp block. flow_map can be set per comparator in HW */

    union {
        mesa_phy_ts_ptp_engine_flow_conf_t ptp;       /**< PTP engine configuration */
        mesa_phy_ts_oam_engine_flow_conf_t oam;       /**< OAM engine configuration */
        mesa_phy_ts_generic_flow_conf_t    gen;       /**< Generic match configuration */
    } flow_conf; /**< PTP/OAM flow config */
} mesa_phy_ts_engine_flow_conf_t CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_ingress_engine_conf_set(const mesa_inst_t                    inst,
                                            const mesa_port_no_t                 port_no,
                                            const mesa_phy_ts_engine_t           eng_id,
                                            const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_ingress_engine_conf_get(const mesa_inst_t              inst,
                                            const mesa_port_no_t           port_no,
                                            const mesa_phy_ts_engine_t     eng_id,
                                            mesa_phy_ts_engine_flow_conf_t *const flow_conf)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_egress_engine_conf_set(const mesa_inst_t                    inst,
                                           const mesa_port_no_t                 port_no,
                                           const mesa_phy_ts_engine_t           eng_id,
                                           const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_egress_engine_conf_get(const mesa_inst_t              inst,
                                           const mesa_port_no_t           port_no,
                                           const mesa_phy_ts_engine_t     eng_id,
                                           mesa_phy_ts_engine_flow_conf_t *const flow_conf)
    CAP(PHY_TS);


/**
 * \brief Analyzer PTP comparator configuration options
 **/
typedef struct {
    mesa_bool_t range_en;  /**< PTP domain number in range enable/disable */
    union {
        struct {
            uint8_t    val; /**< PTP domain number value */
            uint8_t    mask; /**< PTP domain number mask */
        } value; /**< specific PTP domain, for don't care set mask as '0' */
        struct {
            uint8_t    upper; /**< Ranger upper value */
            uint8_t    lower; /**< Range lower value */
        } range; /**< PTP domain range configuration */
    } domain; /**< PTP domain number configuration */
} mesa_phy_ts_ptp_conf_t CAP(PHY_TS);

/**
 * \brief Analyzer PTP action configuration options
 * \note Timestamp action will be based on clock type and delay measurement method.
 **/
typedef struct {
    mesa_bool_t                      enable;   /**< PTP action active/enable or not */
    mesa_phy_ts_engine_channel_map_t channel_map;  /**< maps action to channel for multi-channel timestamp block */
    mesa_phy_ts_ptp_conf_t           ptp_conf;    /**< PTP configuration */
    mesa_phy_ts_ptp_clock_mode_t     clk_mode;    /**< clock mode: bc1step, bc2step, tc1step or tc2step */
    mesa_phy_ts_ptp_delaym_type_t    delaym_type; /**< delay measurement method: P2P, E2E */
    mesa_bool_t                      cf_update; /**< correction field update for bc1step */
    mesa_bool_t                      delay_req_recieve_timestamp; /**<auto Delay_Req/Response feature */
} mesa_phy_ts_ptp_engine_action_t CAP(PHY_TS);

/**
 * \brief Y.1731 OAM delay messurement method
 * \note Using delay messurement method, API sets up OAM flows in OAM
 *  comparator.
 **/
typedef enum {
    MESA_PHY_TS_Y1731_OAM_DELAYM_1DM, /**< One-Way delay messurement method */
    MESA_PHY_TS_Y1731_OAM_DELAYM_DMM, /**< Two-Way delay messurement method */
}mesa_phy_ts_y1731_oam_delaym_type_t CAP(PHY_TS);

/**
 * \brief IETF MPLS ACH, OAM delay messurement method
 * \note Using delay messurement method, API sets up OAM flows in OAM
 *  comparator.
 **/
typedef enum {
    MESA_PHY_TS_IETF_MPLS_ACH_OAM_DELAYM_DMM, /**< Two-way delay measurement method */
    MESA_PHY_TS_IETF_MPLS_ACH_OAM_DELAYM_LDM, /**< Loss/Delay Message combined Measurement Message */
} mesa_phy_ts_ietf_mpls_ach_oam_delaym_type_t CAP(PHY_TS);

/**
 * \brief Analyzer OAM comparator, Y.1731 OAM Packet format configuration options
 **/
typedef struct {
    mesa_bool_t range_en;  /**< OAM MEG level in range enable/disable */
    mesa_phy_ts_y1731_oam_delaym_type_t delaym_type; /**< OAM delay measurement method */
    union {
        struct {
            uint8_t    val; /**< Value */
            uint8_t    mask; /**< Mask */
        } value; /**< specific MEG Level, for don't care set mask as '0' */
        struct {
            uint8_t    upper; /**< Range Upper value */
            uint8_t    lower; /**< Range lower value */
        } range; /**< Range configuration */
    } meg_level; /**< OAM MEG level config */
} mesa_phy_ts_y1731_oam_conf_t CAP(PHY_TS); /**< OAM match configuration */

/**
 * \brief Analyzer OAM comparator, IETF MPLS ACH OAM Supported Timestamp Format
 * \note PTP Timestamp Format is Supported.
 **/
typedef enum {
    MESA_PHY_TS_IETF_MPLS_ACH_OAM_TS_FORMAT_PTP = 0x3, /**< PTP - TimeStamp Format */
} mesa_phy_ts_ietf_mpls_ach_oam_ts_format_t CAP(PHY_TS);

/**
 * \brief Analyzer OAM comparator, IETF MPLS ACH OAM Packet format configuration options
 **/
typedef struct {
    mesa_phy_ts_ietf_mpls_ach_oam_delaym_type_t delaym_type; /**< OAM delay measurement method */
    mesa_phy_ts_ietf_mpls_ach_oam_ts_format_t   ts_format;   /**< OAM DM Timestamp format */
    uint8_t    ds;      /**< DSCP value, that corresponds to a traffic class being measured. */
} mesa_phy_ts_ietf_mpls_ach_oam_conf_t CAP(PHY_TS);

/**
 * \brief OAM Action configuration options
 * \note Timestamp action will be based on OAM delay measurement method.
 **/
typedef struct {
    mesa_bool_t                      enable;      /**< OAM action active/enable or not */
    mesa_bool_t                      y1731_en;    /**< Y.1731 Message Format Enabled/Disable */
    mesa_phy_ts_engine_channel_map_t channel_map; /**< maps action to channel for multi-channel timestamp block */
    uint8_t                          version;     /**< Protocol Version; only 0 is supported */
    union {
            mesa_phy_ts_y1731_oam_conf_t          y1731_oam_conf; /**< Y.1731 OAM configuration */
            mesa_phy_ts_ietf_mpls_ach_oam_conf_t  ietf_oam_conf; /**< IETF OAM configuration */
    } oam_conf; /**< OAM action config */
} mesa_phy_ts_oam_engine_action_t CAP(PHY_TS);

/**
 * \brief Timestamp format to be configured in action configuration
 */
typedef enum {
    MESA_PHY_TS_4_BYTE, /**< Nano second timestamp */
    MESA_PHY_TS_10_BYTE /**< 10 byte timestamp */
} mesa_phy_ts_action_format CAP(PHY_TS);

/**
 * \brief Generic Action configuration option
 */
typedef struct {
    mesa_bool_t                      enable;      /**< Generic action active/enable or not */
    mesa_phy_ts_engine_channel_map_t channel_map; /**< maps action to channel for multi-channel timestamp block */
    uint8_t                          flow_id;     /**< Flow id to be associated with this action */
    uint32_t                         data[2];     /**< Matching data pattern */
    uint32_t                         mask[2];     /**< Mask for the matching pattern */
    mesa_phy_ts_action_format        ts_type;     /**< Timestamp type 4-byte or 10 byte timestamp */
    uint32_t                         ts_offset;   /**< Timestamp offset */
} mesa_phy_ts_generic_action_t CAP(PHY_TS);

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
    mesa_bool_t  action_ptp;  /**< is the action for PTP or OAM */
    mesa_bool_t  action_gen;  /**< generic action or not */
    union {
        mesa_phy_ts_ptp_engine_action_t ptp_conf[2]; /**< Max 2 PTP action per engine */
        mesa_phy_ts_oam_engine_action_t oam_conf[6]; /**< Max 6 OAM action per engine */
        mesa_phy_ts_generic_action_t    gen_conf[6]; /**< Max 6 Generic action per engine */
    } action; /**< PTP/OAM action config */
} mesa_phy_ts_engine_action_t CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_ingress_engine_action_set(const mesa_inst_t                 inst,
                                              const mesa_port_no_t              port_no,
                                              const mesa_phy_ts_engine_t        eng_id,
                                              const mesa_phy_ts_engine_action_t *const action_conf)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_ingress_engine_action_get(const mesa_inst_t           inst,
                                              const mesa_port_no_t        port_no,
                                              const mesa_phy_ts_engine_t  eng_id,
                                              mesa_phy_ts_engine_action_t *const action_conf)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_egress_engine_action_set(const mesa_inst_t                 inst,
                                             const mesa_port_no_t              port_no,
                                             const mesa_phy_ts_engine_t        eng_id,
                                             const mesa_phy_ts_engine_action_t *const action_conf)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_egress_engine_action_get(const mesa_inst_t           inst,
                                             const mesa_port_no_t        port_no,
                                             const mesa_phy_ts_engine_t  eng_id,
                                             mesa_phy_ts_engine_action_t *const action_conf)
    CAP(PHY_TS);

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

mesa_rc mesa_phy_ts_event_enable_set(const mesa_inst_t         inst,
                                     const mesa_port_no_t      port_no,
                                     const mesa_bool_t         enable,
                                     const mesa_phy_ts_event_t ev_mask)
    CAP(PHY_TS);

/**
 * \brief Get Enabling of events
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number
 * \param ev_mask [OUT]  Mask containing events that are enabled
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_ts_event_enable_get(const mesa_inst_t    inst,
                                     const mesa_port_no_t port_no,
                                     mesa_phy_ts_event_t  *const ev_mask)
    CAP(PHY_TS);



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

mesa_rc mesa_phy_ts_event_poll(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               mesa_phy_ts_event_t  *const status)
    CAP(PHY_TS);

/**
 * \brief Get Timestamp statistics.
 *
 * \param inst       [IN]        handle to an API instance
 * \param port_no    [IN]        port number
 * \param statistics [OUT]       pointer to statistics structure
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_stats_get(const mesa_inst_t    inst,
                              const mesa_port_no_t port_no,
                              mesa_phy_ts_stats_t  *const statistics)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_correction_overflow_get(const mesa_inst_t    inst,
                                            const mesa_port_no_t port_no,
                                            mesa_bool_t          *const ingr_overflow,
                                            mesa_bool_t          *const egr_overflow)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_mode_set(const mesa_inst_t    inst,
                             const mesa_port_no_t port_no,
                             const mesa_bool_t    enable)
    CAP(PHY_TS);

/**
 * \brief Get timestamp block status i.e. enable/disable.
 *
 * \param inst    [IN]     handle to an API instance
 * \param port_no [IN]     port number
 * \param enable  [OUT]    enable/disable parameter
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_mode_get(const mesa_inst_t    inst,
                             const mesa_port_no_t port_no,
                             mesa_bool_t          *const enable)
    CAP(PHY_TS);


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
    MESA_PHY_TS_TC_OP_MODE_A = 1, /**< Sub local time at ingress and add at egress from CF */
    MESA_PHY_TS_TC_OP_MODE_B = 0, /**< RX_timestamp using reserved bytes or append at the end as defined in mesa_phy_ts_rxtimestamp_pos_t */
    MESA_PHY_TS_TC_OP_MODE_C = 2, /**< Sub local time at ingress and add at egress from CF and use 48 bits in CF */
} mesa_phy_ts_tc_op_mode_t CAP(PHY_TS);

/**
 * \brief Define the Channel selection for 8487.
 **/
#define  MESA_PHY_TS_8487_XAUI_SEL_0 0x01  /**< Select XAUI Lane - 0 */
#define  MESA_PHY_TS_8487_XAUI_SEL_1 0x02 /**< Select XAUI Lane - 1 */
typedef uint32_t mesa_phy_ts_8487_xaui_sel_t CAP(PHY_TS); /**< XAUI Lane-0 or Lane-1 or both */

/**
 * \brief Defines the initial parameters to be passed to init function
 **/
typedef struct {
    mesa_phy_ts_clockfreq_t           clk_freq;  /**< reference clock frequency */
    mesa_phy_ts_clock_src_t           clk_src;   /**< clock source          */
    mesa_phy_ts_rxtimestamp_pos_t     rx_ts_pos; /**< Rx timestamp position */
    mesa_phy_ts_rxtimestamp_len_t     rx_ts_len; /**< Rx timestamp length */
    mesa_phy_ts_fifo_mode_t           tx_fifo_mode; /**< Tx TSFIFO access mode */
    mesa_phy_ts_fifo_timestamp_len_t  tx_ts_len; /**< timestamp size in Tx TSFIFO */
    mesa_bool_t                       tx_fifo_spi_conf; /**< Modify default 1588_spi configuration, applicable only on PHYs with SPI timestamp fifo support */
    uint8_t                           tx_fifo_hi_clk_cycs; /**< Number of clock periods that the spi_clk is high */
    uint8_t                           tx_fifo_lo_clk_cycs; /**< Number of clock periods that the spi_clk is low */
    mesa_phy_ts_8487_xaui_sel_t       xaui_sel_8487 CAP(PHY_10G); /**< 8487 XAUI lane selection*/
    mesa_phy_ts_tc_op_mode_t          tc_op_mode; /**< TC operating mode */
    mesa_bool_t                       auto_clear_ls; /**< Load and Save of LTC are auto cleared */
    mesa_bool_t                       macsec_ena;       /**< MACsec is enabled or disabled */
    mesa_bool_t                       chk_ing_modified;/**< True if the flag bit needs to be modified in ingress and thus in egress */
    mesa_bool_t                       one_step_txfifo; /**< used when transmitting Delay_Req in one step mode. FALSE when correctionfield update is used instead */
} mesa_phy_ts_init_conf_t CAP(PHY_TS);

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

mesa_rc mesa_phy_ts_init(const mesa_inst_t              inst,
                         const mesa_port_no_t           port_no,
                         const  mesa_phy_ts_init_conf_t *const conf)
    CAP(PHY_TS);


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

mesa_rc mesa_phy_ts_init_conf_get(const mesa_inst_t       inst,
                                  const mesa_port_no_t    port_no,
                                  mesa_bool_t             *const init_done,
                                  mesa_phy_ts_init_conf_t *const conf)
    CAP(PHY_TS);

/**
 * \brief enum for n-phase samplers
**/
typedef enum {
    MESA_PHY_TS_NPHASE_PPS_O,    /**< N-Phase sampler for PPS_O */
    MESA_PHY_TS_NPHASE_PPS_RI,   /**< N-Phase sampler for PPS_RI */
    MESA_PHY_TS_NPHASE_EGR_SOF,  /**< N-Phase sampler for egress SOF */
    MESA_PHY_TS_NPHASE_ING_SOF,  /**< N-Phase sampler for ingress SOF */
    MESA_PHY_TS_NPHASE_LS,       /**< N-Phase sampler for Load/Save */
    MESA_PHY_TS_NPHASE_MAX,      /**< Max N-Phase samplers */
} mesa_phy_ts_nphase_sampler_t CAP(PHY_TS);

/**
 * \brief n-phase status
**/
typedef struct {
    mesa_bool_t enable;      /**< Enabled status*/
    mesa_bool_t CALIB_ERR;   /**< Calibration error */
    mesa_bool_t CALIB_DONE;  /**< Calibration done */
} mesa_phy_ts_nphase_status_t CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_nphase_status_get(const mesa_inst_t            inst,
                                      const mesa_port_no_t         port_no,
                                      mesa_phy_ts_nphase_sampler_t sampler,
                                      mesa_phy_ts_nphase_status_t  *const status)
    CAP(PHY_TS);

/**
 * \brief Enable N-Phase sampler.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param sampler    [IN]       N-Phase sampler type
 * \param enable     [IN]       enable/disable N-Phase sampler
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_hiacc_set(const mesa_inst_t            inst,
                              const mesa_port_no_t         port_no,
                              mesa_phy_ts_nphase_sampler_t sampler,
                              const mesa_bool_t            enable)
    CAP(PHY_TS);

/**
 * \brief N-Phase sampler status get.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param sampler    [IN]       N-Phase sampler type
 * \param enable     [OUT]      enable/disable N-Phase sampler
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_hiacc_get(const mesa_inst_t            inst,
                              const mesa_port_no_t         port_no,
                              mesa_phy_ts_nphase_sampler_t sampler,
                              mesa_bool_t                  const *enable)
    CAP(PHY_TS);

/**
 * \brief 1588 block reset
 **/

#define MESA_PHY_TS_INGR_DATAPATH_RESET         0x01  /**< chip's ingress data path in the 1588 processing block */
#define MESA_PHY_TS_EGR_DATAPATH_RESET          0x02  /**< chip's egress data path in the 1588 processing block */
#define MESA_PHY_TS_INGR_LTC1_RESET             0x04  /**< Ingress LTC clock domain logic for this channel */
#define MESA_PHY_TS_EGR_LTC2_RESET              0x08  /**< Egress LTC clock domain logic for this channel*/
#define MESA_PHY_TS_EGR_FIFO_RESET              0x10  /**< Egress FIFO reset */

typedef uint32_t mesa_phy_ts_soft_reset_t CAP(PHY_TS); /**< Reset blocks: Single or 'OR' multiple above */
/**
 * \brief  reset 1588 block.
 *
 * \param inst       [IN]       handle to an API instance
 * \param port_no    [IN]       port number
 * \param ts_reset   [IN]       1588 block reset
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_ts_block_soft_reset(const mesa_inst_t              inst,
                                     const mesa_port_no_t           port_no,
                                     const mesa_phy_ts_soft_reset_t ts_reset)
    CAP(PHY_TS);

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
mesa_rc mesa_phy_ts_phy_oper_mode_change(const mesa_inst_t    inst,
                                         const mesa_port_no_t port_no)
    CAP(PHY_TS);

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

mesa_rc mesa_phy_1588_csr_reg_write(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    const uint32_t       blk_id,
                                    const uint16_t       csr_address,
                                    const uint32_t       *const value)
    CAP(PHY_TS);

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

mesa_rc mesa_phy_1588_csr_reg_read(const mesa_inst_t    inst,
                                   const mesa_port_no_t port_no,
                                   const uint32_t       blk_id,
                                   const uint16_t       csr_address,
                                   uint32_t             *const value)
    CAP(PHY_TS);

/**
 * \brief Defines the params for FIFO SYNC function
 **/
typedef struct {
    mesa_bool_t          detect_only;                        /**< TS FIFO OOS Detect only, no recovery, Only for Tesla */
    mesa_phy_ts_engine_t eng_recov;             /**< Main Engine used for recovery, Only for Tesla*/
    mesa_phy_ts_engine_t eng_minE;              /**< Mini-E Engine used for recovery, Only for Tesla */
    mesa_bool_t          skip_rev_check;                 /**< To force execution, regardless of revision */
} mesa_phy_ts_fifo_conf_t CAP(PHY_TS);


/**
 *\brief Viper 1588 FIFO reset
 *
 *\param inst      [IN]  Target instance reference.
 *\param port_no   [IN]  Port number.
 *\param fifo_conf [IN] FIFO algorithm Operation mode.
 *
 *\return Return Code.
 **/


mesa_rc mesa_phy_ts_viper_fifo_reset(const mesa_inst_t               inst,
                                     const mesa_port_no_t            port_no,
                                     const mesa_phy_ts_fifo_conf_t *fifo_conf)
    CAP(PHY_TS);

/**
 * \brief PTP Event Message TYPES.
 * \note  4 Types of Event messages.
 *
 **/
typedef enum {
    MESA_PHY_TS_PTP_MESSAGE_TYPE_SYNC,
    MESA_PHY_TS_PTP_MESSAGE_TYPE_DELAY_REQ,
    MESA_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_REQ,
    MESA_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_RESP,
} mesa_phy_ts_ptp_message_type_t CAP(PHY_TS);

/**
 * \brief Clear Correction field for specified PTP message type.
 *
 * \param inst         [IN]      handle to an API instance
 * \param port_no      [IN]      port number
 * \param ingress      [IN]      TRUE if Ingress elses Egress
 * \param gng_id       [IN]      1588 Engine ID
 * \param act_id       [IN]      1588 Action ID
 * \param msgtype      [IN]      PTP Message Type
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_ts_flow_clear_cf_set(const mesa_inst_t                     inst,
                                      const mesa_port_no_t                  port_no,
                                      mesa_bool_t                           ingress,
                                      const mesa_phy_ts_engine_t            eng_id,
                                      uint8_t                               act_id,
                                      const mesa_phy_ts_ptp_message_type_t  msgtype)

    CAP(PHY_TS);
#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_PHY_TS_
