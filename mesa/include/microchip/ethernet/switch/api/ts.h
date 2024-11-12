// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// Microchip is aware that some terminology used in this technical document is
// antiquated and inappropriate. As a result of the complex nature of software
// where seemingly simple changes have unpredictable, and often far-reaching
// negative results on the software's functionality (requiring extensive
// retesting and revalidation) we are unable to make the desired changes in all
// legacy systems without compromising our product or our clients' products.


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_TS_
#define _MICROCHIP_ETHERNET_SWITCH_API_TS_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/switch/api/security.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// TS global configuration
typedef struct {
    // PTP domain number [0..MESA_CAP_TS_DOMAIN_CNT-1]
    // This is the PTP (TOD) domain for TSN features:
    // TAS - PRFP - RTE
    uint8_t  tsn_domain;
} mesa_ts_conf_t CAP(TS);

// TSN global configuration
mesa_rc mesa_ts_conf_set(const mesa_inst_t           inst,
                         const mesa_ts_conf_t *const conf)
    CAP(TS);

mesa_rc mesa_ts_conf_get(const mesa_inst_t        inst,
                         mesa_ts_conf_t    *const conf)
    CAP(TS);

/** \brief This is the max time offset adjustment that os done without setting ports in disabled state */
#define MESA_HW_TIME_MAX_FINE_ADJ   25

/**
 * \brief Set the current time in a Timestamp format.
 * \param inst [IN]     handle to an API instance.
 * \param ts [IN]       pointer to a TimeStamp structure.
 * Architecture:
 *   All
 *
 * \return Return code.
 */
mesa_rc mesa_ts_timeofday_set(const mesa_inst_t      inst,
                              const mesa_timestamp_t *const ts)
    CAP(TS);

/**
 * \brief Set the current time in a Timestamp format for a domain.
 * \param inst   [IN]   handle to an API instance.
 * \param domain [IN]   Clock domain.
 * \param ts     [IN]   pointer to a TimeStamp structure.
 * Architecture:
 *   Jaguar2: domain 0..2
 *
 * \return Return code.
 */
mesa_rc mesa_ts_domain_timeofday_set(const mesa_inst_t      inst,
                                     const uint32_t         domain,
                                     const mesa_timestamp_t *const ts)
    CAP(TS);

/**
 * \brief Set delta the current time in a Timestamp format.
 * \param inst     [IN] handle to an API instance.
 * \param ts       [IN] pointer to a TimeStamp structure.
 * \param negative [IN] True if ts is subtracted from current time, else ts is added.
 * Architecture:
 *   All
 *
 * \return Return code.
 */
mesa_rc mesa_ts_timeofday_set_delta(const mesa_inst_t      inst,
                                    const mesa_timestamp_t *ts,
                                    mesa_bool_t            negative)
    CAP(TS);

/**
 * \brief Set delta the current time in a Timestamp format.
 * \param inst     [IN] handle to an API instance.
 * \param domain   [IN] Clock domain.
 * \param ts       [IN] pointer to a TimeStamp structure.
 * \param negative [IN] True if ts is subtracted from current time, else ts is added.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_domain_timeofday_set_delta(const mesa_inst_t      inst,
                                           const uint32_t         domain,
                                           const mesa_timestamp_t *ts,
                                           mesa_bool_t            negative)
    CAP(TS);

/**
 * \brief Subtract offset from the current time.
 * \param inst [IN]     handle to an API instance.
 * \param offset [IN]   offset in ns. The offset is subtracted from current TOD
 * Architecture:
 *   All
 *
 * \return Return code.
 */
mesa_rc mesa_ts_timeofday_offset_set(const mesa_inst_t inst,
                                     const int32_t     offset)
    CAP(TS);

/**
 * \brief Subtract offset from the current time.
 * \param inst   [IN]   handle to an API instance.
 * \param domain [IN]   Clock domain.
 * \param offset [IN]   offset in ns. The offset is subtracted from current TOD
 *
 * \return Return code.
 */
mesa_rc mesa_ts_domain_timeofday_offset_set(const mesa_inst_t inst,
                                            const uint32_t    domain,
                                            const int32_t     offset)
    CAP(TS);

/**
 * \brief Do the one sec administration in the Timestamp function.
 * On Serval1:
 * Must be called after every one-second timer synchronization pulse interrupt (MEBA_EVENT_SYNC)
 *
 * This function is driving register update with parameters given by calling
 * mesa_ts_timeofday_set_delta() + mesa_ts_domain_timeofday_set_delta()
 * in order to make the TOD delta adjustment happen.
 *
 * This function is driving register update with parameters given by calling
 * mesa_ts_timeofday_offset_set()
 * in order to make the TOD offset configuration happen.
 *
 * After calling 
 * mesa_ts_timeofday_offset_set() + mesa_ts_timeofday_next_pps_set()
 * until this function is called, the functions
 * srvl_ts_timeofday_offset_set() + srvl_ts_timeofday_set() + srvl_ts_timeofday_set_delta()
 * will return error code
 *
 * \param inst [IN]     handle to an API instance.
 * \param ongoing_adjustment [OUT]  True if clock adjustment is ongoing
 *
 * \return Return code.
 *
 * Architecture:
 *  Jr1    : Maintains the clock setting process
 *  Caracal: Maintains the clock setting process
 *  Serval1: Maintains the clock setting process
 *  JR2,
 *  S5     : it must only be called when the PPS output pin is low, therefore it shall be called at least 200 microseconds after the 1PPS interrupt
 *
 * \return Return code.
 */
mesa_rc mesa_ts_adjtimer_one_sec(const mesa_inst_t inst,
                                 mesa_bool_t       *const ongoing_adjustment)
    CAP(TS);

/**
 * \brief Check if the clock adjustment is ongoing.
 * \param inst [IN]     handle to an API instance.
 * \param ongoing_adjustment [OUT]  True if clock adjustment is ongoing
 * Architecture:
 *  Jr1    ,
 *  Caracal,
 *  Serval1: Checks if the clock setting process is ongoing.
 *  JR2,
 *  S5     : Always returns False, as the time can be set immediately.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_ongoing_adjustment(const mesa_inst_t inst,
                                   mesa_bool_t       *const ongoing_adjustment)
    CAP(TS);

/**
 * \brief Get the current time in a Timestamp format, and the corresponding
 *        time counter.
 * \param inst [IN]     handle to an API instance
 * \param ts [OUT]      pointer to a TimeStamp structure
 * \param tc [OUT]      pointer to a time counter (internal hw format)
 * Architecture:
 *  Caracal: tc = free running clock cycle counter
 *  Ocelot:
 *  Serval:  tc = (seconds + nanoseconds).  In 16 bit fraction of nano seconds.
 *  Jaguar2: tc = free running nanoseconds counter.  In 16 bit fraction of nano seconds.
 *  SparX-5: tc = (seconds + nanoseconds + fractional nanoseconds). In 16 bit fraction of nano seconds.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_timeofday_get(const mesa_inst_t inst,
                              mesa_timestamp_t  *const ts,
                              uint64_t          *const tc)
    CAP(TS);

/**
 * \brief Get the current raw time in a Timestamp format, and the corresponding
 *        time counter. (like mesa_ts_timeofday_get but without correction for outstanding adjustments.)
 *        Used to be able to poll the time and call the onsec function in architectures that do not support interrupt.
 * \param inst [IN]     handle to an API instance
 * \param ts [OUT]      pointer to a TimeStamp structure
 * \param tc [OUT]      pointer to a time counter (internal hw format)
 * Architecture:
 *  Ocelot:
 *  Serval:  tc = (seconds + nanoseconds).  In 16 bit fraction of nano seconds.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_timeofday_raw(const mesa_inst_t inst,
                              mesa_timestamp_t  *const ts,
                              uint64_t          *const tc)
    CAP(TS_MISSING_ONE_SEC_INTERRUPT);

/**
 * \brief Get the current time in a Timestamp format, and the corresponding
 *        time counter.
 * \param inst   [IN]   handle to an API instance
 * \param domain [IN]   Clock domain.
 * \param ts     [OUT]  pointer to a TimeStamp structure
 * \param tc     [OUT]  pointer to a time counter (internal hw format)
 * Architecture:
 *  Same as mesa_ts_timeofday_get
 *
 * \return Return code.
 */
mesa_rc mesa_ts_domain_timeofday_get(const mesa_inst_t inst,
                                     const uint32_t    domain,
                                     mesa_timestamp_t  *const ts,
                                     uint64_t          *const tc)
    CAP(TS);

/**
 * \brief Get the current time in timestamp format from multiple domains simultanesouly
 *        at same instance of time. This will be useful in comparing two different clocks.
 * \param inst       [IN]   handle to an API instance.
 * \param domain_cnt [IN]   Number of supported clock domains from which timestamps must be read.
 * \param ts         [OUT]  Array containing timestamps from each clock domain at the time of execution.
 *                          Timestamps are read starting from clock domain 0.
 * Architecture:
 *  Same as mesa_ts_timeofday_get but involves multiple domains.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_multi_domain_timeofday_get(const mesa_inst_t inst,
                                           const uint32_t    domain_cnt,
                                           mesa_timestamp_t  *const ts)
    CAP(TS);

/**
 * \brief Get the time at the next 1PPS pulse edge in a Timestamp format.
 * \param inst [IN]     handle to an API instance
 * \param ts   [OUT]    pointer to a TimeStamp structure
 * Architecture:
 *  All
 *
 * \return Return code.
 */
mesa_rc mesa_ts_timeofday_next_pps_get(const mesa_inst_t inst,
                                       mesa_timestamp_t  *const ts)
    CAP(TS);

/**
 * \brief Get the time at the prev 1PPS pulse edge in a Timestamp format.
 * \param inst [IN]     handle to an API instance
 * \param ts   [OUT]    pointer to a TimeStamp structure
 * Architecture:
 *  All
 *
 * \return Return code.
 */
mesa_rc mesa_ts_timeofday_prev_pps_get(const mesa_inst_t inst,
                                       mesa_timestamp_t  *const ts)
    CAP(TS);

/**
 * \brief Get the time at the next 1PPS pulse edge in a Timestamp format.
 * \param inst   [IN]   handle to an API instance
 * \param domain [IN]   Clock domain.
 * \param ts     [OUT]  pointer to a TimeStamp structure
 * Architecture:
 *  All
 *
 * \return Return code.
 */
mesa_rc mesa_ts_domain_timeofday_next_pps_get(const mesa_inst_t inst,
                                              const uint32_t    domain,
                                              mesa_timestamp_t  *const ts)
    CAP(TS);

/**
 * \brief Adjust the clock timer ratio.
 * \param inst [IN]     handle to an API instance.
 * \param adj [IN]      Clock ratio frequency offset in units of 0,1 ppb (parts pr billion).
 *                      ratio > 0 => clock runs faster
 *
 * \return Return code.
 */
mesa_rc mesa_ts_adjtimer_set(const mesa_inst_t inst,
                             const int32_t     adj)
    CAP(TS);

/**
* \brief get the clock timer ratio.
*
* \param inst [IN]     handle to an API instance.
* \param adj [OUT]     Clock ratio frequency offset in ppb (parts pr billion).
*                      ratio > 0 => clock runs faster
*
* \return Return code.
*/
mesa_rc mesa_ts_adjtimer_get(const mesa_inst_t inst,
                             int32_t           *const adj)
    CAP(TS);

/**
 * \brief Adjust the clock timer ratio for a domain.
 * Architecture:
 *   Jaguar2: domain 0..2
 *   Luton26, Serval1: domain 0
 *
 * \param inst   [IN]     handle to an API instance.
 * \param domain [IN]     Clock domain.
 * \param adj    [IN]     Clock ratio frequency offset in units of 0,1 ppb (parts pr billion).
 *                      ratio > 0 => clock runs faster
 *
 * \return Return code.
 */
mesa_rc mesa_ts_domain_adjtimer_set(const mesa_inst_t inst,
                                    const uint32_t    domain,
                                    const int32_t     adj)
    CAP(TS);

/**
 * \brief get the clock timer ratio for a domain.
 * Architecture:
 *   Jaguar2: domain 0..2
 *   Luton26, Serval1: domain 0
 *
 * \param inst   [IN]     handle to an API instance.
 * \param domain [IN]     Clock domain.
 * \param adj    [OUT]    Clock ratio frequency offset in units of 0,1 ppb (parts pr billion).
 *                        ratio > 0 => clock runs faster
 *
 * \return Return code.
 */
mesa_rc mesa_ts_domain_adjtimer_get(const mesa_inst_t inst,
                                    const uint32_t    domain,
                                    int32_t           *const adj)
    CAP(TS);

/**
* \brief get the clock internal timer frequency offset, compared to external clock input.
*
* \param inst [IN]     handle to an API instance.
* \param adj [OUT]     Clock ratio frequency offset in ppb (parts pr billion).
*                      ratio > 0 => internal clock runs faster than external clock
*
* \return Return code.
*/
mesa_rc mesa_ts_freq_offset_get(const mesa_inst_t inst,
                                int32_t           *const adj)
    CAP(TS);

/**
 * \brief Get the latest saved nanosec counter from the alternative clock.
 *
 * \param inst [IN]             handle to an API instance
 * \param saved [OUT]           latest saved value. In 16 bit fraction of nano seconds.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_alt_clock_saved_get(const mesa_inst_t inst,
                                    uint64_t          *const saved)
    CAP(TS_ALT_CLOCK);

/**
 * \brief Get the latest saved timeofday from the alternative clock.
 *
 * \param inst [IN]             handle to an API instance
 * \param ts   [OUT]            latest saved timeofday.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_alt_clock_saved_timeofday_get(const mesa_inst_t inst,
                                              mesa_timestamp_t  *const ts)
    CAP(TS_ALT_CLOCK);

/**
 * \brief parameter for setting the alternative  clock mode.
 */
/** \brief external clock output configuration. */
typedef struct mesa_ts_alt_clock_mode_t {
    mesa_bool_t one_pps_out; /**< Enable 1pps output */
    mesa_bool_t one_pps_in;  /**< Enable 1pps input */
    mesa_bool_t save;        /**< Save actual time counter at next 1 PPS input. This is the TOD to get using mesa_ts_alt_clock_saved_timeofday_get() function */
    mesa_bool_t load;        /**< Load actual time counter at next 1 PPS input. The TOD loaded is given by the TOD _set() functions  */
} mesa_ts_alt_clock_mode_t CAP(TS_ALT_CLOCK);

/**
 * \brief Set the alternative external clock mode.
 *  This function configures the 1PPS, L/S pin usage for pin set no 0 in Serval
 *
 * \param inst [IN]             handle to an API instance
 * \param alt_clock_mode [IN]   alternative clock mode.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_alt_clock_mode_set(const mesa_inst_t              inst,
                                   const mesa_ts_alt_clock_mode_t *const alt_clock_mode)
    CAP(TS_ALT_CLOCK);

/**
 * \brief Get the alternative external clock mode.
 *
 * \param inst [IN]             handle to an API instance
 * \param alt_clock_mode [OUT]  alternative clock mode.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_alt_clock_mode_get(const mesa_inst_t        inst,
                                   mesa_ts_alt_clock_mode_t *const alt_clock_mode)
    CAP(TS_ALT_CLOCK);

/**
 * \brief Set the time at the next 1PPS pulse edge in a Timestamp format.
 * On Serval:
 * It is assumed that this function is called at the beginning of a sec.
 * Right after one-second timer synchronization pulse interrupt (MEBA_EVENT_SYNC)
 * \param inst [IN]     handle to an API instance
 * \param ts [OUT]      pointer to a TimeStamp structure
 *
 * \return Return code.
 */
mesa_rc mesa_ts_timeofday_next_pps_set(const mesa_inst_t      inst,
                                       const mesa_timestamp_t *const ts)
    CAP(TS_ALT_CLOCK);

/**
 * \brief parameter for setting the external clock mode.
 */
typedef enum  {
    MESA_TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE,       /**< Disable 1PPS input/output */
    MESA_TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT,        /**< 1PPS clock output is generated based on TOD in domain 0 */
    MESA_TS_EXT_CLOCK_MODE_ONE_PPS_INPUT,         /**< TOD in domain 0 is saved on 1PPS clock input. This is the TOD to get using _get() functions */
    MESA_TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT_INPUT,
    MESA_TS_EXT_CLOCK_MODE_MAX
} mesa_ts_ext_clock_one_pps_mode_t CAP(TS);

/**
 * \brief external clock input/output configuration.
 */ 
typedef struct mesa_ts_ext_clock_mode_t {
    mesa_ts_ext_clock_one_pps_mode_t  one_pps_mode;  /**< Select 1PPS ext clock mode */
    mesa_bool_t                       enable;        /**< True: Select clock generation on external output pin with frequency 'freq'
                                                          False: Select 1PPS on external input/output pins as indicated in 'one_pps_mode' */
    uint32_t                          freq;          /**< clock output frequency (hz [1..25.000.000]) when 'enable' == True. */
    uint32_t                          domain;        /**< clock domain in multi domain chip (0..2). */
} mesa_ts_ext_clock_mode_t CAP(TS);


/**
 * \brief Get the external clock mode.
 *  The mode depends on the hardware capability, it may be:
 *          Enable/disable external synch pulse
 *          Set clock output frequency
 *
 * \param inst [IN]             handle to an API instance
 * \param ext_clock_mode [OUT]  external clock mode.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_external_clock_mode_get(const mesa_inst_t        inst,
                                        mesa_ts_ext_clock_mode_t *const ext_clock_mode)
    CAP(TS);

/**
 * \brief Set the external clock mode.
 *  The mode depends on the hardware capability, it may be:
 *          Enable/disable external synch pulse
 *          Set clock output frequency
 *
 * \param inst [IN]             handle to an API instance
 * \param ext_clock_mode [IN]   external clock mode.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_external_clock_mode_set(const mesa_inst_t              inst,
                                        const mesa_ts_ext_clock_mode_t *const ext_clock_mode)
    CAP(TS);

/**
 * \brief parameter for setting the external io mode.
 * Architecture:
 *   Jaguar2:
 */
typedef enum  {
    MESA_TS_EXT_IO_MODE_ONE_PPS_DISABLE,     /**< Disable IO pin */
    MESA_TS_EXT_IO_MODE_ONE_PPS_OUTPUT,      /**< enable external sync pulse output */
    MESA_TS_EXT_IO_MODE_WAVEFORM_OUTPUT,     /**< enable external clock output frequency */
    MESA_TS_EXT_IO_MODE_ONE_PPS_LOAD,        /**< enable input and load time at positive edge of input signal. The TOD loaded is given by the TOD _set() functions */
    MESA_TS_EXT_IO_MODE_ONE_PPS_SAVE,        /**< enable input and save time at positive edge of input signal. This is the TOD to get using mesa_ts_saved_timeofday_get() function */
    MESA_TS_EXT_IO_MODE_MAX
} mesa_ts_ext_io_pin_cfg_t CAP(TS);

/** \brief external clock io configuration. */
typedef struct mesa_ts_ext_io_mode_s {
    mesa_ts_ext_io_pin_cfg_t    pin;    /**< Defines the io operation modefor the io pin */
    uint32_t                         domain; /**< clock domain [0..2] assigned to the IO pin */
    uint32_t                         freq;   /**< clock output frequency (hz [1..25.000.000]). only relevant in WAVEFORM _OUTPUT mode */
} mesa_ts_ext_io_mode_t CAP(TS);

/**
 * \brief Get the external io mode.
 * Architecture:
 *   Jaguar2:
 *
 * \param inst [IN]             handle to an API instance
 * \param io   [IN]             Input/Output pin number [0..3]
 * \param ext_io_mode [OUT]     external clock io pin mode.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_external_io_mode_get(const mesa_inst_t     inst,
                                     const uint32_t        io,
                                     mesa_ts_ext_io_mode_t *const ext_io_mode)
    CAP(TS);

/**
 * \brief Set the external io mode.
 * Architecture:
 *   Jaguar2:
 *
 * \param inst [IN]             handle to an API instance
 * \param io   [IN]             Input/Output pin number [0..3]
 * \param ext_io_mode [IN]      external clock io pin mode.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_external_io_mode_set(const mesa_inst_t           inst,
                                     const uint32_t              io,
                                     const mesa_ts_ext_io_mode_t *const ext_io_mode)
    CAP(TS);

/**
 * \brief Get the latest saved time.
 *
 * \param inst [IN]             handle to an API instance
 * \param io   [IN]             Input/Output pin number [0..3]
 * \param ts  [OUT]             latest saved timeofday for the io pin's domain
 * \param tc  [OUT]             latest saved time counter for the io pin's domain
 *
 * \return Return code.
 */
mesa_rc mesa_ts_saved_timeofday_get(const mesa_inst_t inst,
                                    const uint32_t    io,
                                    mesa_timestamp_t  *const ts,
                                    uint64_t          *const tc)
    CAP(TS);

/**
 * \brief Get the output pin generated clock edge offset to requested time.
 *
 * \param inst    [IN]             handle to an API instance
 * \param io      [IN]             Input/Output pin number [0..3]
 * \param offset  [OUT]            The last output clock edge was generated with this offset. Value 256 is one nano second.
 *
 * \return Return code.
 */
mesa_rc mesa_ts_output_clock_edge_offset_get(const mesa_inst_t inst,
                                             const uint32_t    io,
                                             uint32_t          *const offset)
    CAP(TS);

/**
 * \brief Get the latest saved time counter in nanosec.
 *
 * \param inst [IN]             handle to an API instance
 * \param saved [OUT]           latest saved value. [0..999.999.999]
 *
 * \return Return code.
 */
/* TBD henrikb. This is not called by application and the cil pointer is not loaded on any platform */
mesa_rc mesa_ts_external_clock_saved_get(const mesa_inst_t inst,
                                         uint32_t          *const saved)
    CAP(TS);

/**
 * \brief Set the ingress latency.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param ingress_latency [IN]  pointer to ingress latency
 *
 * \return Return code.
 */
mesa_rc mesa_ts_ingress_latency_set(const mesa_inst_t         inst,
                                    const mesa_port_no_t      port_no,
                                    const mesa_timeinterval_t *const ingress_latency)
    CAP(TS);

/**
 * \brief Get the ingress latency.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param ingress_latency [OUT] pointer to ingress_latency
 *
 * \return Return code.
 */
mesa_rc mesa_ts_ingress_latency_get(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    mesa_timeinterval_t  *const ingress_latency)
    CAP(TS);

/**
 * \brief Set the P2P delay.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param p2p_delay [IN]        peer-2-peer delay (measured)
 *
 * \return Return code.
 */
mesa_rc mesa_ts_p2p_delay_set(const mesa_inst_t         inst,
                              const mesa_port_no_t      port_no,
                              const mesa_timeinterval_t *const p2p_delay)
    CAP(TS);

/**
 * \brief Get the P2P delay.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param p2p_delay [OUT]       pointer to peer-2-peer delay
 *
 * \return Return code.
 */
mesa_rc mesa_ts_p2p_delay_get(const mesa_inst_t    inst,
                              const mesa_port_no_t port_no,
                              mesa_timeinterval_t  *const p2p_delay)
    CAP(TS);


/**
 * \brief Set the egress latency.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param egress_latency [IN]   egress latency
 *
 * \return Return code.
 */
mesa_rc mesa_ts_egress_latency_set(const mesa_inst_t         inst,
                                   const mesa_port_no_t      port_no,
                                   const mesa_timeinterval_t *const egress_latency)
    CAP(TS);

/**
 * \brief Get the egress latency.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param egress_latency [OUT]  pointer to  egress latency
 *
 * \return Return code.
 */
mesa_rc mesa_ts_egress_latency_get(const mesa_inst_t    inst,
                                   const mesa_port_no_t port_no,
                                   mesa_timeinterval_t  *const egress_latency)
    CAP(TS);

/**
 * \brief Set the delay asymmetry.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param delay_asymmetry [IN]  delay asymmetry. The (signed) delay is subtracted on egress and added on ingress. 
 *
 * \return Return code.
 */
mesa_rc mesa_ts_delay_asymmetry_set(const mesa_inst_t         inst,
                                    const mesa_port_no_t      port_no,
                                    const mesa_timeinterval_t *const delay_asymmetry)
    CAP(TS);

/**
 * \brief Get the delay asymmetry.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param delay_asymmetry [OUT] pointer to  delay asymmetry
 *
 * \return Return code.
 */
mesa_rc mesa_ts_delay_asymmetry_get(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    mesa_timeinterval_t  *const delay_asymmetry)
    CAP(TS);

/**
 * \brief parameter for setting the timestamp operating mode
 */
typedef enum  {
    MESA_TS_MODE_NONE,
    MESA_TS_MODE_EXTERNAL,
    MESA_TS_MODE_INTERNAL,
    MESA_TX_MODE_MAX
} mesa_ts_mode_t CAP(TS);

typedef enum {
    MESA_TS_PCH_TX_MODE_NONE,                    /**< No PCH in transmitted frames */
    MESA_TS_PCH_TX_MODE_ENCRYPT_NONE,            /**< PCH added on transmitted frames */
    MESA_TS_PCH_TX_MODE_ENCRYPT_BIT,             /**< PCH added with encryption bit set */
    MESA_TS_PCH_TX_MODE_ENCRYPT_BIT_INVERT_SMAC, /**< PCH added with encryption bit set to inverted SMAC(40), which is then cleared.#xD */
} mesa_ts_pch_tx_mode_t CAP(PCH);

/**< Set mode for ingress timestamps, in terms of nsec.subns bit widths */
typedef enum {
    MESA_TS_PCH_RX_MODE_NONE,  /**< No PCH expected */
    MESA_TS_PCH_RX_MODE_32_0,  /**< 32.0 mode */
    MESA_TS_PCH_RX_MODE_28_4,  /**< 28.4 mode */
    MESA_TS_PCH_RX_MODE_24_8,  /**< 24.8 mode */
    MESA_TS_PCH_RX_MODE_16_16, /**< 16.16 mode */
} mesa_ts_pch_rx_mode_t CAP(PCH);

// RedBox discard mode for frames towards non-RedBox port
typedef enum {
    MESA_TS_RB_DISCARD_NONE, // No PRP role
    MESA_TS_RB_DISCARD_A,    // Discard timing flow from port A
    MESA_TS_RB_DISCARD_B,    // Discard timing flow from port B
} mesa_ts_rb_discard_t;

/** \brief Timestamp operation */
typedef struct mesa_ts_operation_mode_t {
    mesa_ts_mode_t        mode;        /**< Hardware Timestamping mode for a port(EXTERNAL or INTERNAL) */
    uint32_t              domain;      /**< Hardware timestamping domain for a port */
    mesa_ts_pch_tx_mode_t tx_pch_mode CAP(PCH); /**< PCH TX mode */
    mesa_ts_pch_rx_mode_t rx_pch_mode CAP(PCH); /**< PCH RX mode */
    uint32_t              pch_port_id CAP(PCH); /**< PCH sub-portID. */
    mesa_ts_rb_discard_t  rb_discard;  // RedBox discard mode
} mesa_ts_operation_mode_t CAP(TS);


/**
 * \brief Set the timestamping operation mode for a port.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param mode [IN]             pointer to a struct holding the operation mode
 *
 * \return Return code.
 *
 * Serval:  Used to set backplane (INTERNAL) mode/normal(EXTERNAL) mode
 * Jaguar2: Used to set backplane (INTERNAL) mode/front(EXTERNAL) mode
 * In backplane mode the internal format is determined by the internal mode (see below)
 * Other : Not used
 */
mesa_rc mesa_ts_operation_mode_set(const mesa_inst_t              inst,
                                   const mesa_port_no_t           port_no,
                                   const mesa_ts_operation_mode_t *const mode)
    CAP(TS);

/**
 * \brief Get the timestamping operation mode for a port
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param mode [OUT]            pointer to a struct holding the operation mode
 *
 * \return Return code.
 */
mesa_rc mesa_ts_operation_mode_get(const mesa_inst_t        inst,
                                   const mesa_port_no_t     port_no,
                                   mesa_ts_operation_mode_t *const mode)
    CAP(TS);

/**
 * \brief parameter for setting the internal timestamp format
 */
typedef enum  {
    MESA_TS_INTERNAL_FMT_NONE,
    MESA_TS_INTERNAL_FMT_RESERVED_LEN_30BIT,        /* Ts is stored in reservedField as 30 bit (ns only) */
    MESA_TS_INTERNAL_FMT_RESERVED_LEN_32BIT,        /* Ts is stored in reservedField as 32 bit (ns+sec*10^9) mod 2^32) */
    MESA_TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62,    /* Ts is subtracted from cf at ingress as 44 bit (ns+sec*10^9) mod 2^44), MSB is saved in cf bit 62 */
    MESA_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_3_0, /* Ts is subtracted from cf at ingress as 48 bit (ns+sec*10^9) mod 2^48), MSBs are saved in cf bit 3-0 */
    MESA_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_0,   /* Ts is subtracted from cf at ingress as 48 bit (ns+sec*10^9) mod 2^48), MSB is saved in cf bit 0 */
    MESA_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF,     /* Ts is subtracted from cf at ingress as 48 bit (ns+sec*10^9) mod 2^48) */
    MESA_TS_INTERNAL_FMT_MAX
} mesa_ts_internal_fmt_t CAP(TS);

/** \brief Hardware timestamping format mode for internal ports */
typedef struct mesa_ts_internal_mode_t {
    mesa_ts_internal_fmt_t int_fmt;    /**< Hardware Timestamping format mode for INTERNAL ports */
} mesa_ts_internal_mode_t CAP(TS);


/**
 * \brief Set the internal timestamping mode.
 * \param inst [IN]             handle to an API instance
 * \param mode [IN]             pointer to a struct holding the operation mode
 *
 * \return Return code.
 *
 * Serval: Used to set INTERNAL mode timestamping format
 * Other : Not used
 */
mesa_rc mesa_ts_internal_mode_set(const mesa_inst_t             inst,
                                  const mesa_ts_internal_mode_t *const mode)
    CAP(TS);

/**
 * \brief Get the internal timestamping mode.
 * \param inst [IN]             handle to an API instance
 * \param mode [OUT]            pointer to a struct holding the operation mode
 *
 * \return Return code.
 */
mesa_rc mesa_ts_internal_mode_get(const mesa_inst_t       inst,
                                  mesa_ts_internal_mode_t *const mode)
    CAP(TS);

/** \brief Timestamp identifier */
typedef struct mesa_ts_id_t {
    uint32_t ts_id;  /**< Timestamp identifier */
} mesa_ts_id_t CAP(TS);

/** \brief Timestamp structure */
typedef struct mesa_ts_timestamp_t {
    uint64_t ts;   /**< Timestamp value */
    uint32_t id;   /**< Timestamp identifier */
    void *context; /**< Application specific context */
    mesa_bool_t ts_valid; /**< Timestamp is valid (can be not valid if timestamp is not received */
} mesa_ts_timestamp_t CAP(TS);

/**
 * \brief Update the internal timestamp table, from HW
 * \param inst    [IN]          handle to an API instance
 *
 * \return Return code.
 */
mesa_rc mesa_tx_timestamp_update(const mesa_inst_t inst)
    CAP(TS);

/**
* \brief Get the rx FIFO timestamp for a {timestampId}
* Architecture:
*   Luton26
*
* \param inst    [IN]          handle to an API instance
* \param ts_id   [IN]          timestamp id
* \param ts     [OUT]          pointer to a struct holding the fifo timestamp
*
* \return Return code.
*/
mesa_rc mesa_rx_timestamp_get(const mesa_inst_t   inst,
                              const mesa_ts_id_t  *const ts_id,
                              mesa_ts_timestamp_t *const ts)
    CAP(TS);

/**
* \brief Release the FIFO rx timestamp id
* \param inst    [IN]          handle to an API instance
* \param ts_id   [IN]          timestamp id
*
* \return Return code.
*/
mesa_rc mesa_rx_timestamp_id_release(const mesa_inst_t  inst,
                                     const mesa_ts_id_t *const ts_id)
    CAP(TS);

/**
* \brief Get rx timestamp from a port (convert from slave time to the master time)
* Architecture:
*   Jaguar1
*
* \param inst    [IN]          handle to an API instance
* \param port_no [IN]          port number
* \param ts     [IN/OUT]       pointer to a struct holding the timestamp
*
* \return Return code.
*/
mesa_rc mesa_rx_master_timestamp_get(const mesa_inst_t    inst,
                                     const mesa_port_no_t port_no,
                                     mesa_ts_timestamp_t  *const ts)
    CAP(TS);

typedef void (*mesa_ts_timestamp_alloc_cb_t)(void *context, uint32_t port_no,
                                             mesa_ts_timestamp_t *ts);

/** \brief Timestamp allocation */
typedef struct mesa_ts_timestamp_alloc_t {
    /** Identify the ports that a timestamp id is allocated to */
    uint64_t port_mask;

    /** Application specific context used as parameter in the call-out */
    void *context;

    /** Application call-out function called when the timestamp is available */
    mesa_ts_timestamp_alloc_cb_t cb;
} mesa_ts_timestamp_alloc_t CAP(TS);

/**
 * \brief Allocate a timestamp id for a two step transmission
 * \param inst       [IN]          handle to an API instance
 * \param alloc_parm [IN]          pointer allocation parameters
 * \param ts_id      [OUT]         timestamp id
 *
 * \return Return code.
 */
mesa_rc mesa_tx_timestamp_idx_alloc(const mesa_inst_t               inst,
                                    const mesa_ts_timestamp_alloc_t *const alloc_parm,
                                    mesa_ts_id_t                    *const ts_id)
    CAP(TS);

/**
 * \brief Age the FIFO timestamps
 * \param inst    [IN]          handle to an API instance
 *
 * \return Return code.
 */
mesa_rc mesa_timestamp_age(const mesa_inst_t inst)
    CAP(TS);

/**
* \brief Signal port status change (used to detect and compensate for the internal ingress and egress latencies)
* \param inst    [IN]          handle to an API instance
* \param port_no [IN]          port number
*
* \return Return code.
*/
mesa_rc mesa_ts_status_change(const mesa_inst_t    inst,
                              const mesa_port_no_t port_no)
    CAP(TS);


/**
 * \brief parameter for setting auto response behavior pr domain
 * Jaguar2: bitMask = 0x3F
 * Fireant: bitMask = 0x7F
 * ptp_port_individual TRUE:
 *     DelayResponce portIdentity.portNumber = (ptp_port_msb & ~bitMask) | ((API Port number) & bitMask)
 * ptp_port_individual FALSE:
 *     DelayResponce portIdentity.portNumber = ptp_port_msb
 */
typedef struct mesa_ts_autoresp_dom_cfg_s {
    mesa_bool_t         ptp_port_individual; /**< Influencing on DelayResponce portIdentity.portNumber calculation as described above */
    uint16_t            ptp_port_msb;        /**< Contributing to DelayResponce portIdentity.portNumber as described above */
    mesa_clock_identity clock_identity;      /**< DelayResponce portIdentity.clockIdentity. */
    mesa_ace_u8_t       flag_field_update;   /**< DelayResponce flagField byte 0. Bits in .value with .mask bit set, is written to DelayResponce */
} mesa_ts_autoresp_dom_cfg_t CAP(TS_DELAY_REQ_AUTO_RESP);

/**
 * \brief Set auto response behavior pr. domain.
 * \param inst    [IN]          handle to an API instance
 * \param domain  [IN]          ptp domain number [0..MESA_CAP_TS_DOMAIN_CNT-1]
 * \param cfg     [IN]          domain configuration for auto response feature
 *
 * \return Return code.
 */
mesa_rc mesa_ts_autoresp_dom_cfg_set(const mesa_inst_t                inst,
                                     const uint8_t                    domain,
                                     const mesa_ts_autoresp_dom_cfg_t *const cfg)
    CAP(TS_DELAY_REQ_AUTO_RESP);

/**
 * \brief Get auto response behavior pr. domain.
 * \param inst    [IN]          handle to an API instance
 * \param domain  [IN]          ptp domain number [0..MESA_CAP_TS_DOMAIN_CNT-1]
 * \param cfg     [OUT]         domain configuration for auto response feature
 *
 * \return Return code.
 */
mesa_rc mesa_ts_autoresp_dom_cfg_get(const mesa_inst_t          inst,
                                     const uint8_t              domain,
                                     mesa_ts_autoresp_dom_cfg_t *const cfg)
    CAP(TS_DELAY_REQ_AUTO_RESP);

/**
 * \brief Set the source mac address used in auto Delay_Req/Resp
 * \param inst    [IN]          handle to an API instance
 * \param port_no [IN]          port number
 * \param smac    [IN]          port mac configuration for auto response feature
 *
 * \return Return code.
 */
mesa_rc mesa_ts_smac_set(const mesa_inst_t    inst,
                         const mesa_port_no_t port_no,
                         const mesa_mac_t     *const smac)
    CAP(TS_DELAY_REQ_AUTO_RESP);

/**
 * \brief Get the source mac address used in auto Delay_Req/Resp
 * \param inst    [IN]          handle to an API instance
 * \param port_no [IN]          port number
 * \param smac   [OUT]          port mac configuration for auto response feature
 *
 * \return Return code.
 */
mesa_rc mesa_ts_smac_get(const mesa_inst_t    inst,
                         const mesa_port_no_t port_no,
                         mesa_mac_t           *const smac)
    CAP(TS_DELAY_REQ_AUTO_RESP);

/**
 * \brief Set auto response behavior pr. domain.
 * \param inst    [IN]          handle to an API instance
 * \param sec_cntr[IN]          sequence counter number [0..255]. See mesa_packet_tx_info_t.sequence_idx and
 *                              mesa_packet_tx_info_t.ptp_timestamp.
 * \param cnt_val [OUT]         actual value of the sequence counter
 *
 * \return Return code.
 */
mesa_rc mesa_ts_seq_cnt_get(const mesa_inst_t                inst,
                            const uint32_t                   sec_cntr,
                            uint16_t *const                  cnt_val)
    CAP(TS);

/**
 * \brief Parameter for internal timestamping capability.
 */
typedef enum  {
    MESA_TS_TOD_INTERNAL_TC_MODE_30BIT = 0x1,
    MESA_TS_TOD_INTERNAL_TC_MODE_32BIT = 0x2,
    MESA_TS_TOD_INTERNAL_TC_MODE_44BIT = 0x4,
    MESA_TS_TOD_INTERNAL_TC_MODE_48BIT = 0x8,
} mesa_ts_tod_internal_tc_mode_t CAP(TS);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_TS_
