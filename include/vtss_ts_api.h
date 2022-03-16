// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief TimeStamping API.
 * \details This header file describes PTP/OAM TimeStamping API functions and
 * associated types.
 */

#ifndef _VTSS_TS_API_H_
#define _VTSS_TS_API_H_

#include <vtss/api/types.h>
#include <vtss_security_api.h>    /* For vtss_ace_u8_t */

// ***************************************************************************
//
//  TimeStamping interface
//
// ***************************************************************************

#if defined(VTSS_FEATURE_TIMESTAMP)
#ifdef __cplusplus
extern "C" {
#endif

/** \brief Number of clock cycle counts pr sec. */
#if defined (VTSS_ARCH_OCELOT)
#define VTSS_HW_TIME_CNT_PR_SEC 1000000000 /* Serval counts ns instead of clock cycles */
/** \brief Number of nanoseconds pr clock count. */
#define VTSS_HW_TIME_NSEC_PR_CNT 1
#endif
#if defined (VTSS_ARCH_LUTON26)
#define VTSS_HW_TIME_CNT_PR_SEC 250000000 /* L26 counts clock cycles instead of ns */
/** \brief Number of nanoseconds pr clock count. */
#define VTSS_HW_TIME_NSEC_PR_CNT 4
#endif
#if defined (VTSS_ARCH_LAN966X)  /* TBD. Check/set correct value */
#define VTSS_HW_TIME_CNT_PR_SEC 1000000000
/** \brief Number of nanoseconds pr clock count. */
#define VTSS_HW_TIME_NSEC_PR_CNT 1
#define VTSS_HW_TIME_WRAP_LIMIT  0       /* time counter wrap around limit+1 */
#define VTSS_HW_TIME_MIN_ADJ_RATE  10       /* 1 ppb */
#endif

#if defined (VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#define VTSS_HW_TIME_CNT_PR_SEC 1000000000
/** \brief Number of nanoseconds pr clock count. */
#define VTSS_HW_TIME_NSEC_PR_CNT 1
/** \brief Jaguar2 nanosecond time counter wrap around value (jaguar2 time counter wraps when 0xffffffff is reached). */
#define VTSS_HW_TIME_WRAP_LIMIT  0       /* time counter wrap around limit+1 */
#endif

#if defined (VTSS_ARCH_LUTON26) || defined (VTSS_ARCH_OCELOT)
/** \brief Caracal nanosecond time counter wrap around value (Caracal time counter wraps when 0xffffffff is reached). */
#define VTSS_HW_TIME_WRAP_LIMIT  0       /* time counter wrap around limit+1 (=0 if wrap at 0xffffffff) */
#endif

#if defined (VTSS_ARCH_LUTON26)
/** \brief Luton26 minimum adjustment rate in units of 0,1 ppb. */
#define VTSS_HW_TIME_MIN_ADJ_RATE  40       /* 4 ppb */
#endif
#if defined (VTSS_ARCH_OCELOT)
/** \brief Serval minimum adjustment rate in units of 0,1 ppb. */
#define VTSS_HW_TIME_MIN_ADJ_RATE  10       /* 1 ppb */
#endif

#if defined (VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
/** \brief Jaguar 2 minimum adjustment rate in units of 0,1 ppb. */
#define VTSS_HW_TIME_MIN_ADJ_RATE  10       /* 1 ppb */
#endif

#if defined (VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
/** \brief Number of Jaguar2 PTP pins, that can be used as 1PPS or clock output/input. */
#define VTSS_TS_IO_ARRAY_SIZE       4
/** \brief Number of separate clock domains in Jaguar2 */
#define VTSS_TS_DOMAIN_ARRAY_SIZE   3
#elif defined (VTSS_ARCH_LAN966X)
/** \brief Number of LAN966X PTP pins, that can be used as 1PPS or clock output/input. */
#define VTSS_TS_IO_ARRAY_SIZE       7
/** \brief Number of separate clock domains in LAN966X */
#define VTSS_TS_DOMAIN_ARRAY_SIZE   3
#elif defined(VTSS_ARCH_OCELOT)
/** \brief Number of Ocelot PTP pins that can be used as 1 PPS or clock output/input. */
#define VTSS_TS_IO_ARRAY_SIZE       4
/** \brief Number of separate clock domains in Ocelot */
#define VTSS_TS_DOMAIN_ARRAY_SIZE   1
#else
/** \brief Number of L26 or Serval PTP pins, that can be used as 1PPS or clock output/input. */
#define VTSS_TS_IO_ARRAY_SIZE       1
/** \brief Number of separate clock domains in L26 */
#define VTSS_TS_DOMAIN_ARRAY_SIZE   1
#endif

#if defined(VTSS_ARCH_SPARX5)
/** \brief Number of Automatic Delay Response controllers in SparX-5 */
#define VTSS_TS_RESP_CTRL_ARRAY_SIZE 4
#endif

/** \brief This is the max time offset adjustment that os done without setting ports in disabled state */
#define VTSS_HW_TIME_MAX_FINE_ADJ   25

/**
 * \brief Set the current time in a Timestamp format.
 * \param inst [IN]     handle to an API instance.
 * \param ts [IN]       pointer to a TimeStamp structure.
 * Architecture:
 *   All
 *
 * \return Return code.
 */
vtss_rc vtss_ts_timeofday_set(const vtss_inst_t             inst,
                              const vtss_timestamp_t        *const ts);

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
vtss_rc vtss_ts_domain_timeofday_set(const vtss_inst_t             inst,
                                     const u32                     domain,
                                     const vtss_timestamp_t        *const ts);

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
vtss_rc vtss_ts_timeofday_set_delta(const vtss_inst_t       inst,
                                    const vtss_timestamp_t  *ts,
                                    BOOL                    negative);

/**
 * \brief Set delta the current time in a Timestamp format.
 * \param inst     [IN] handle to an API instance.
 * \param domain   [IN] Clock domain.
 * \param ts       [IN] pointer to a TimeStamp structure.
 * \param negative [IN] True if ts is subtracted from current time, else ts is added.
 *
 * \return Return code.
 */
vtss_rc vtss_ts_domain_timeofday_set_delta(const vtss_inst_t       inst,
                                           const u32               domain,
                                           const vtss_timestamp_t  *ts,
                                           BOOL                    negative);

/**
 * \brief Subtract offset from the current time.
 * \param inst [IN]     handle to an API instance.
 * \param offset [IN]   offset in ns.
 * Architecture:
 *   All
 *
 * \return Return code.
 */
vtss_rc vtss_ts_timeofday_offset_set(const vtss_inst_t          inst,
                                     const i32                  offset);

/**
 * \brief Subtract offset from the current time.
 * \param inst   [IN]   handle to an API instance.
 * \param domain [IN]   Clock domain.
 * \param offset [IN]   offset in ns.
 *
 * \return Return code.
 */
vtss_rc vtss_ts_domain_timeofday_offset_set(const vtss_inst_t          inst,
                                            const u32                  domain,
                                            const i32                  offset);

/**
 * \brief Do the one sec administration in the Timestamp function.
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
vtss_rc vtss_ts_adjtimer_one_sec(const vtss_inst_t             inst,
                                 BOOL                          *const ongoing_adjustment);

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
vtss_rc vtss_ts_ongoing_adjustment(const vtss_inst_t           inst,
                                   BOOL                        *const ongoing_adjustment);

/**
 * \brief Get the current time in a Timestamp format, and the corresponding
 *        time counter.
 * \param inst [IN]     handle to an API instance
 * \param ts [OUT]      pointer to a TimeStamp structure
 * \param tc [OUT]      pointer to a time counter (internal hw format)
 * Architecture:
 *  Caracal: tc = free running clock cycle counter
 *  Ocelot:
 *  Serval:  tc = (seconds + nanoseconds). In 16 bit fraction of nano seconds.
 *  Jaguar2: tc = free running nanoseconds counter.  In 16 bit fraction of nano seconds.
 *  SparX-5: tc = (seconds + nanoseconds + fractional nanoseconds). In 16 bit fraction of nano seconds.
 *
 * \return Return code.
 */
vtss_rc vtss_ts_timeofday_get(const vtss_inst_t             inst,
                              vtss_timestamp_t              *const ts,
                              u64                           *const tc);

/**
 * \brief Get the current raw time in a Timestamp format, and the corresponding
 *        time counter. (like vtss_ts_timeofday_get but without correction for outstanding adjustments.)
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
vtss_rc vtss_ts_timeofday_raw(const vtss_inst_t             inst,
                              vtss_timestamp_t              *const ts,
                              u64                           *const tc);

/**
 * \brief Get the current time in a Timestamp format, and the corresponding
 *        time counter.
 * \param inst   [IN]   handle to an API instance
 * \param domain [IN]   Clock domain.
 * \param ts     [OUT]  pointer to a TimeStamp structure
 * \param tc     [OUT]  pointer to a time counter (internal hw format)
 * Architecture:
 *  Same as vtss_ts_timeofday_get
 *
 * \return Return code.
 *
 * Note: This is the same function as vtss_ts_domain_timeofday_get except for no
 *       locking/unlocking of API critical region. This variant of the function
 *       assumes that locking has already been done and that the function is
 *       called from within another API function.
 */
vtss_rc _vtss_ts_domain_timeofday_get(const vtss_inst_t            inst,
                                     const u32                     domain,
                                     vtss_timestamp_t              *const ts,
                                     u64                           *const tc);

/**
 * \brief Get the current time in a Timestamp format, and the corresponding
 *        time counter.
 * \param inst   [IN]   handle to an API instance
 * \param domain [IN]   Clock domain.
 * \param ts     [OUT]  pointer to a TimeStamp structure
 * \param tc     [OUT]  pointer to a time counter (internal hw format)
 * Architecture:
 *  Same as vtss_ts_timeofday_get
 *
 * \return Return code.
 */
vtss_rc vtss_ts_domain_timeofday_get(const vtss_inst_t             inst,
                                     const u32                     domain,
                                     vtss_timestamp_t              *const ts,
                                     u64                           *const tc);

/**
 * \brief Get the time at the next 1PPS pulse edge in a Timestamp format.
 * \param inst [IN]     handle to an API instance
 * \param ts   [OUT]    pointer to a TimeStamp structure
 * Architecture:
 *  All
 *
 * \return Return code.
 */
vtss_rc vtss_ts_timeofday_next_pps_get(const vtss_inst_t             inst,
                                       vtss_timestamp_t              *const ts);

/**
 * \brief Get the time at the prev 1PPS pulse edge in a Timestamp format.
 * \param inst [IN]     handle to an API instance
 * \param ts   [OUT]    pointer to a TimeStamp structure
 * Architecture:
 *  All
 *
 * \return Return code.
 */
vtss_rc vtss_ts_timeofday_prev_pps_get(const vtss_inst_t             inst,
                                       vtss_timestamp_t              *const ts);

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
vtss_rc vtss_ts_domain_timeofday_next_pps_get(const vtss_inst_t      inst,
                                              const u32              domain,
                                              vtss_timestamp_t       *const ts);

/**
 * \brief Adjust the clock timer ratio.
 * \param inst [IN]     handle to an API instance.
 * \param adj [IN]      Clock ratio frequency offset in units of 0,1 ppb (parts pr billion).
 *                      ratio > 0 => clock runs faster
 *
 * \return Return code.
 */
vtss_rc vtss_ts_adjtimer_set(const vtss_inst_t              inst,
                             const i32                      adj);

/**
* \brief get the clock timer ratio.
*
* \param inst [IN]     handle to an API instance.
* \param adj [OUT]     Clock ratio frequency offset in ppb (parts pr billion).
*                      ratio > 0 => clock runs faster
*
* \return Return code.
*/
vtss_rc vtss_ts_adjtimer_get(const vtss_inst_t              inst,
                             i32                            *const adj);

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
vtss_rc vtss_ts_domain_adjtimer_set(const vtss_inst_t              inst,
                                    const u32                      domain,
                                    const i32                      adj);

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
vtss_rc vtss_ts_domain_adjtimer_get(const vtss_inst_t              inst,
                                    const u32                      domain,
                                    i32                            *const adj);

/**
* \brief get the clock internal timer frequency offset, compared to external clock input.
*
* \param inst [IN]     handle to an API instance.
* \param adj [OUT]     Clock ratio frequency offset in ppb (parts pr billion).
*                      ratio > 0 => internal clock runs faster than external clock
*
* \return Return code.
*/
vtss_rc vtss_ts_freq_offset_get(const vtss_inst_t           inst,
                                i32                         *const adj);

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) /* TBD_henrikb */
/**
 * \brief parameter for setting the alternative  clock mode.
 */
/** \brief external clock output configuration. */
typedef struct vtss_ts_alt_clock_mode_t {
    BOOL one_pps_out;       /**< Enable 1pps output */
    BOOL one_pps_in;        /**< Enable 1pps input */
    BOOL save;              /**< Save actual time counter at next 1 PPS input */
    BOOL load;              /**< Load actual time counter with at next 1 PPS input */
} vtss_ts_alt_clock_mode_t;

/**
 * \brief Get the latest saved nanosec counter from the alternative clock.
 *
 * \param inst [IN]             handle to an API instance
 * \param saved [OUT]           latest saved value.  In 16 bit fraction of nano seconds.
 *
 * \return Return code.
 */
vtss_rc vtss_ts_alt_clock_saved_get(const vtss_inst_t           inst,
                                    u64    *const               saved);

#if defined(VTSS_ARCH_OCELOT)
/**
 * \brief Get the latest saved timeofday from the alternative clock.
 *
 * \param inst [IN]             handle to an API instance
 * \param ts   [OUT]            latest saved timeofday.
 *
 * \return Return code.
 */
vtss_rc vtss_ts_alt_clock_saved_timeofday_get(const vtss_inst_t     inst,
                                    vtss_timestamp_t  *const        ts);
#endif

/**
 * \brief Get the alternative external clock mode.
 *
 * \param inst [IN]             handle to an API instance
 * \param alt_clock_mode [OUT]  alternative clock mode.
 *
 * \return Return code.
 */
vtss_rc vtss_ts_alt_clock_mode_get(const vtss_inst_t              inst,
                                   vtss_ts_alt_clock_mode_t       *const alt_clock_mode);

/**
 * \brief Set the alternative external clock mode.
 *  This function configures the 1PPS, L/S pin usage for pin set no 0 in Serval
 *
 * \param inst [IN]             handle to an API instance
 * \param alt_clock_mode [IN]   alternative clock mode.
 *
 * \return Return code.
 */
vtss_rc vtss_ts_alt_clock_mode_set(const vtss_inst_t              inst,
                                   const vtss_ts_alt_clock_mode_t *const alt_clock_mode);

/**
 * \brief Set the time at the next 1PPS pulse edge in a Timestamp format.
 * \param inst [IN]     handle to an API instance
 * \param ts [OUT]      pointer to a TimeStamp structure
 *
 * \return Return code.
 */
vtss_rc vtss_ts_timeofday_next_pps_set(const vtss_inst_t       inst,
                                       const vtss_timestamp_t  *const ts);
#endif

/**
 * \brief parameter for setting the external clock mode.
 */
typedef enum  {
    VTSS_TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE,
    VTSS_TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT,
    VTSS_TS_EXT_CLOCK_MODE_ONE_PPS_INPUT,
    VTSS_TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT_INPUT,
    VTSS_TS_EXT_CLOCK_MODE_MAX
} vtss_ts_ext_clock_one_pps_mode_t;

#define TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE      VTSS_TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE      /**< Backward compatibility */
#define TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT       VTSS_TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT       /**< Backward compatibility */
#define TS_EXT_CLOCK_MODE_ONE_PPS_INPUT        VTSS_TS_EXT_CLOCK_MODE_ONE_PPS_INPUT        /**< Backward compatibility */
#define TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT_INPUT VTSS_TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT_INPUT /**< Backward compatibility */
#define TS_EXT_CLOCK_MODE_MAX                  VTSS_TS_EXT_CLOCK_MODE_MAX                  /**< Backward compatibility */

/** \brief external clock output configuration. */
typedef struct vtss_ts_ext_clock_mode_t {
    vtss_ts_ext_clock_one_pps_mode_t   one_pps_mode;    
                            /**< Select 1pps ext clock mode:
                               input :  lock clock to 1pps input
                               output:  enable external sync pulse output
                               disable: disable 1 pps */
    BOOL enable;            /**< Select internal sync pulse (enable = false) 
                                or external sync pulse (enable = true) */
    u32  freq;              /**< clock output frequency (hz [1..25.000.000]). */
} vtss_ts_ext_clock_mode_t;


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
vtss_rc vtss_ts_external_clock_mode_get(const vtss_inst_t           inst,
                                        vtss_ts_ext_clock_mode_t    *const ext_clock_mode);

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
vtss_rc vtss_ts_external_clock_mode_set(const vtss_inst_t              inst,
                                        const vtss_ts_ext_clock_mode_t *const ext_clock_mode);

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
/**
 * \brief parameter for setting the external io mode.
 * Architecture:
 *   Jaguar2: 
 */
typedef enum  {
    VTSS_TS_EXT_IO_MODE_ONE_PPS_DISABLE,     /**< Disable IO pin */
    VTSS_TS_EXT_IO_MODE_ONE_PPS_OUTPUT,      /**< enable external sync pulse output */
    VTSS_TS_EXT_IO_MODE_WAVEFORM_OUTPUT,     /**< enable external clock output frequency */
    VTSS_TS_EXT_IO_MODE_ONE_PPS_LOAD,        /**< enable input and load time at positive edge of input signal */
    VTSS_TS_EXT_IO_MODE_ONE_PPS_SAVE,        /**< enable input and save time at positive edge of input signal */
    VTSS_TS_EXT_IO_MODE_MAX
} vtss_ts_ext_io_pin_cfg_t;

#define TS_EXT_IO_MODE_ONE_PPS_DISABLE VTSS_TS_EXT_IO_MODE_ONE_PPS_DISABLE /**< Backward compatibility */
#define TS_EXT_IO_MODE_ONE_PPS_OUTPUT  VTSS_TS_EXT_IO_MODE_ONE_PPS_OUTPUT  /**< Backward compatibility */
#define TS_EXT_IO_MODE_WAVEFORM_OUTPUT VTSS_TS_EXT_IO_MODE_WAVEFORM_OUTPUT /**< Backward compatibility */
#define TS_EXT_IO_MODE_ONE_PPS_LOAD    VTSS_TS_EXT_IO_MODE_ONE_PPS_LOAD    /**< Backward compatibility */
#define TS_EXT_IO_MODE_ONE_PPS_SAVE    VTSS_TS_EXT_IO_MODE_ONE_PPS_SAVE    /**< Backward compatibility */
#define TS_EXT_IO_MODE_MAX             VTSS_TS_EXT_IO_MODE_MAX             /**< Backward compatibility */

/** \brief external clock io configuration. */
typedef struct vtss_ts_ext_io_mode_s {
    vtss_ts_ext_io_pin_cfg_t    pin;    /**< Defines the io operation modefor the io pin */
    u32                         domain; /**< clock domain [0..2] assigned to the IO pin */
    u32                         freq;   /**< clock output frequency (hz [1..25.000.000]). only relevant in WAVEFORM _OUTPUT mode */
} vtss_ts_ext_io_mode_t;

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
vtss_rc vtss_ts_external_io_mode_get(const vtss_inst_t           inst,
                                     const u32                   io,
                                     vtss_ts_ext_io_mode_t       *const ext_io_mode);

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
vtss_rc vtss_ts_external_io_mode_set(const vtss_inst_t              inst,
                                     const u32                      io,
                                     const vtss_ts_ext_io_mode_t    *const ext_io_mode);

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
vtss_rc vtss_ts_saved_timeofday_get(const vtss_inst_t               inst,
                                    const u32                       io,
                                    vtss_timestamp_t                *const ts,
                                    u64                             *const tc);

/**
 * \brief Get the output pin generated clock edge offset to requested time.
 *
 * \param inst    [IN]             handle to an API instance
 * \param io      [IN]             Input/Output pin number [0..3]
 * \param offset  [OUT]            The last output clock edge was generated with this offset. Value 256 is one nano second.
 *
 * \return Return code.
 */
vtss_rc vtss_ts_output_clock_edge_offset_get(const vtss_inst_t inst,
                                             const u32         io,
                                             u32               *const offset);
#endif

/**
 * \brief Get the latest saved time counter in nanosec.
 *
 * \param inst [IN]             handle to an API instance
 * \param saved [OUT]           latest saved value. [0..999.999.999]
 *
 * \return Return code.
 */
vtss_rc vtss_ts_external_clock_saved_get(const vtss_inst_t               inst,
                                         u32                             *const saved);

/**
 * \brief Set the ingress latency.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param ingress_latency [IN]  pointer to ingress latency
 *
 * \return Return code.
 */
vtss_rc vtss_ts_ingress_latency_set(const vtss_inst_t              inst,
                                    const vtss_port_no_t           port_no,
                                    const vtss_timeinterval_t             *const ingress_latency);

/**
 * \brief Get the ingress latency.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param ingress_latency [OUT] pointer to ingress_latency
 *
 * \return Return code.
 */
vtss_rc vtss_ts_ingress_latency_get(const vtss_inst_t              inst,
                                    const vtss_port_no_t           port_no,
                                    vtss_timeinterval_t            *const ingress_latency);

/**
 * \brief Set the P2P delay.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param p2p_delay [IN]        peer-2-peer delay (measured)
 *
 * \return Return code.
 */
vtss_rc vtss_ts_p2p_delay_set(const vtss_inst_t                   inst,
                              const vtss_port_no_t                port_no,
                              const vtss_timeinterval_t           *const p2p_delay);

/**
 * \brief Get the P2P delay.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param p2p_delay [OUT]       pointer to peer-2-peer delay
 *
 * \return Return code.
 */
vtss_rc vtss_ts_p2p_delay_get(const vtss_inst_t              inst,
                              const vtss_port_no_t           port_no,
                              vtss_timeinterval_t            *const p2p_delay);


/**
 * \brief Set the egress latency.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param egress_latency [IN]   egress latency
 *
 * \return Return code.
 */
vtss_rc vtss_ts_egress_latency_set(const vtss_inst_t            inst,
                                   const vtss_port_no_t         port_no,
                                   const vtss_timeinterval_t    *const egress_latency);

/**
 * \brief Get the egress latency.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param egress_latency [OUT]  pointer to  egress latency
 *
 * \return Return code.
 */
vtss_rc vtss_ts_egress_latency_get(const vtss_inst_t            inst,
                                   const vtss_port_no_t         port_no,
                                   vtss_timeinterval_t          *const egress_latency);

/**
 * \brief Set the delay asymmetry.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param delay_asymmetry [IN]  delay asymmetry. The (signed) delay is subtracted on egress and added on ingress. 
 *
 * \return Return code.
 */
vtss_rc vtss_ts_delay_asymmetry_set(const vtss_inst_t           inst,
                                   const vtss_port_no_t         port_no,
                                   const vtss_timeinterval_t    *const delay_asymmetry);

/**
 * \brief Get the delay asymmetry.
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param delay_asymmetry [OUT] pointer to  delay asymmetry
 *
 * \return Return code.
 */
vtss_rc vtss_ts_delay_asymmetry_get(const vtss_inst_t           inst,
                                   const vtss_port_no_t         port_no,
                                   vtss_timeinterval_t          *const delay_asymmetry);

/**
 * \brief parameter for setting the timestamp operating mode
 */
typedef enum  {
    VTSS_TS_MODE_NONE,
    VTSS_TS_MODE_EXTERNAL,
    VTSS_TS_MODE_INTERNAL,
    VTSS_TX_MODE_MAX
} vtss_ts_mode_t;

#define TS_MODE_NONE     VTSS_TS_MODE_NONE     /**< Backward compatibility */
#define TS_MODE_EXTERNAL VTSS_TS_MODE_EXTERNAL /**< Backward compatibility */
#define TS_MODE_INTERNAL VTSS_TS_MODE_INTERNAL /**< Backward compatibility */
#define TX_MODE_MAX      VTSS_TX_MODE_MAX      /**< Backward compatibility */

/** \brief Timestamp operation */
typedef struct vtss_ts_operation_mode_t {
    vtss_ts_mode_t mode;                /**< Hardware Timestamping mode for a port(EXTERNAL or INTERNAL) */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
    u32            domain;              /**< Hardware timestamping domain for a port */
#endif
} vtss_ts_operation_mode_t;


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
 *          In backplane mode the internal format is determined by the internal mode (see below)
 * Other : Not used
 */
vtss_rc vtss_ts_operation_mode_set(const vtss_inst_t              inst,
                                   const vtss_port_no_t           port_no,
                                   const vtss_ts_operation_mode_t *const mode);

/**
 * \brief Get the timestamping operation mode for a port
 * \param inst [IN]             handle to an API instance
 * \param port_no [IN]          port number
 * \param mode [OUT]            pointer to a struct holding the operation mode
 *
 * \return Return code.
 */
vtss_rc vtss_ts_operation_mode_get(const vtss_inst_t              inst,
                                   const vtss_port_no_t           port_no,
                                   vtss_ts_operation_mode_t       *const mode);
                                   
/**
 * \brief parameter for setting the internal timestamp format
 */
typedef enum  {
    VTSS_TS_INTERNAL_FMT_NONE,
    VTSS_TS_INTERNAL_FMT_RESERVED_LEN_30BIT,        /* Ts is stored in reservedField as 30 bit (ns only) */
    VTSS_TS_INTERNAL_FMT_RESERVED_LEN_32BIT,        /* Ts is stored in reservedField as 32 bit (ns+sec*10^9) mod 2^32) */
    VTSS_TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62,    /* Ts is subtracted from cf at ingress as 44 bit (ns+sec*10^9) mod 2^44), MSB is saved in cf bit 62 */
    VTSS_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_3_0, /* Ts is subtracted from cf at ingress as 48 bit (ns+sec*10^9) mod 2^48), MSBs are saved in cf bit 3-0 */
    VTSS_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_0,   /* Ts is subtracted from cf at ingress as 48 bit (ns+sec*10^9) mod 2^48), MSB is saved in cf bit 0 */
    VTSS_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF,     /* Ts is subtracted from cf at ingress as 48 bit (ns+sec*10^9) mod 2^48) */
    VTSS_TS_INTERNAL_FMT_MAX
} vtss_ts_internal_fmt_t;

#define TS_INTERNAL_FMT_NONE                      VTSS_TS_INTERNAL_FMT_NONE                      /**< Backward compatibility */
#define TS_INTERNAL_FMT_RESERVED_LEN_30BIT        VTSS_TS_INTERNAL_FMT_RESERVED_LEN_30BIT        /**< Backward compatibility */
#define TS_INTERNAL_FMT_RESERVED_LEN_32BIT        VTSS_TS_INTERNAL_FMT_RESERVED_LEN_32BIT        /**< Backward compatibility */
#define TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62    VTSS_TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62    /**< Backward compatibility */
#define TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_3_0 VTSS_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_3_0 /**< Backward compatibility */
#define TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_0   VTSS_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_0   /**< Backward compatibility */
#define TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF     VTSS_TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF     /**< Backward compatibility */
#define TX_INTERNAL_FMT_MAX                       VTSS_TS_INTERNAL_FMT_MAX                       /**< Backward compatibility */

/** \brief Hardware timestamping format mode for internal ports */
typedef struct vtss_ts_internal_mode_t {
    vtss_ts_internal_fmt_t int_fmt;    /**< Hardware Timestamping format mode for INTERNAL ports */
} vtss_ts_internal_mode_t;


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
vtss_rc vtss_ts_internal_mode_set(const vtss_inst_t              inst,
                                   const vtss_ts_internal_mode_t *const mode);

/**
 * \brief Get the internal timestamping mode.
 * \param inst [IN]             handle to an API instance
 * \param mode [OUT]            pointer to a struct holding the operation mode
 *
 * \return Return code.
 */
vtss_rc vtss_ts_internal_mode_get(const vtss_inst_t              inst,
                                  vtss_ts_internal_mode_t        *const mode);

/** \brief Timestamp identifier */
typedef struct vtss_ts_id_t {
    u32                 ts_id;  /**< Timestamp identifier */
} vtss_ts_id_t;

/** \brief Timestamp structure */
typedef struct vtss_ts_timestamp_t {
    u64 ts;                     /**< Timestamp value (tc in 16 bit fraction of nano seconds) */
    u32 id;                     /**< Timestamp identifier */
    void * context;             /**< Application specific context */
    BOOL ts_valid;              /**< Timestamp is valid (can be not valid if timestamp is not received */
} vtss_ts_timestamp_t;

/**
 * \brief Update the internal timestamp table, from HW
 * \param inst    [IN]          handle to an API instance
 *
 * \return Return code.
 */
vtss_rc vtss_tx_timestamp_update(const vtss_inst_t              inst);

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
vtss_rc vtss_rx_timestamp_get(const vtss_inst_t              inst,
                              const vtss_ts_id_t             *const ts_id,
                              vtss_ts_timestamp_t            *const ts);

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
* 
* Note: This is the same function as vtss_rx_timestamp_get except for no
*       locking/unlocking of API critical region. This variant of the function
*       assumes that locking has already been done and that the function is
*       called from within another API function.
*/
vtss_rc _vtss_rx_timestamp_get(const vtss_inst_t              inst,
                               const vtss_ts_id_t             *const ts_id,
                               vtss_ts_timestamp_t            *const ts);

/**
* \brief Release the FIFO rx timestamp id 
* \param inst    [IN]          handle to an API instance
* \param ts_id   [IN]          timestamp id
*
* \return Return code.
*/
vtss_rc vtss_rx_timestamp_id_release(const vtss_inst_t              inst,
                                     const vtss_ts_id_t             *const ts_id);

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
vtss_rc vtss_rx_master_timestamp_get(const vtss_inst_t              inst,
                                     const vtss_port_no_t           port_no,
                                     vtss_ts_timestamp_t            *const ts);

/** \brief Timestamp allocation callback */
typedef void (*vtss_ts_timestamp_alloc_cb_t)(void *context, u32 port_no,
                                             vtss_ts_timestamp_t *ts);

/** \brief Timestamp allocation */
typedef struct vtss_ts_timestamp_alloc_t {
    /** Identify the ports that a timestamp id is allocated to */
    uint64_t port_mask;

    /** Application specific context used as parameter in the call-out */
    void * context;

    /** Application call-out function called when the timestamp is available */
    vtss_ts_timestamp_alloc_cb_t cb;
} vtss_ts_timestamp_alloc_t;
/**
 * \brief Allocate a timestamp id for a two step transmission
 * \param inst       [IN]          handle to an API instance
 * \param alloc_parm [IN]          pointer allocation parameters
 * \param ts_id      [OUT]         timestamp id
 *
 * \return Return code.
 */
vtss_rc vtss_tx_timestamp_idx_alloc(const vtss_inst_t               inst,
                                    const vtss_ts_timestamp_alloc_t *const alloc_parm,
                                    vtss_ts_id_t                    *const ts_id);

/**
 * \brief Age the FIFO timestamps
 * \param inst    [IN]          handle to an API instance
 *
 * \return Return code.
 */
vtss_rc vtss_timestamp_age(const vtss_inst_t              inst);

/**
* \brief Signal port status change (used to detect and compensate for the internal ingress and egress latencies)
* \param inst    [IN]          handle to an API instance
* \param port_no [IN]          port number
*
* \return Return code.
*/
vtss_rc vtss_ts_status_change(const vtss_inst_t      inst,
                              const vtss_port_no_t   port_no);

#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
/**
 * \brief parameter for setting auto response behaviour pr domain
 */
typedef struct vtss_ts_autoresp_dom_cfg_s {
    BOOL                        ptp_port_individual;/**< TRUE => PortIdentity = ptp_port_msb || ptp_port_lsb, FALSE => PortIdentity = ptp_port_msb */
    u16                         ptp_port_msb;       /**< ptp port number most significant bits 15:6 */
    vtss_clock_identity         clock_identity;     /**< ptp clock identity */
    vtss_ace_u8_t               flag_field_update;  /**< flag field [0] update value and mask */

} vtss_ts_autoresp_dom_cfg_t;

/**
 * \brief Set auto response behaviour pr. domain.
 * \param inst    [IN]          handle to an API instance
 * \param domain  [IN]          ptp domain number [0..VTSS_TS_DOMAIN_ARRAY_SIZE-1]
 * \param cfg     [IN]          domain configuration for autoresponse feature
 *
 * \return Return code.
 */
vtss_rc vtss_ts_autoresp_dom_cfg_set(const vtss_inst_t                  inst,
                                     const u8                           domain,
                                     const vtss_ts_autoresp_dom_cfg_t   *const cfg);

/**
 * \brief Get auto response behaviour pr. domain.
 * \param inst    [IN]          handle to an API instance
 * \param domain  [IN]          ptp domain number [0..VTSS_TS_DOMAIN_ARRAY_SIZE-1]
 * \param cfg     [OUT]         domain configuration for autoresponse feature
 *
 * \return Return code.
 */
vtss_rc vtss_ts_autoresp_dom_cfg_get(const vtss_inst_t                  inst,
                                     const u8                           domain,
                                     vtss_ts_autoresp_dom_cfg_t         *const cfg);

/**
 * \brief Set the source mac address used in autp Delay_Req/Resp
 * \param inst    [IN]          handle to an API instance
 * \param port_no [IN]          port number
 * \param smac    [IN]          port mac configuration for autoresponse feature
 *
 * \return Return code.
 */
vtss_rc vtss_ts_smac_set(const vtss_inst_t    inst,
                         const vtss_port_no_t port_no,
                         const vtss_mac_t  *const smac);

/**
 * \brief Get the source mac address used in autp Delay_Req/Resp
 * \param inst    [IN]          handle to an API instance
 * \param port_no [IN]          port number
 * \param smac   [OUT]          port mac configuration for autoresponse feature
 *
 * \return Return code.
 */
vtss_rc vtss_ts_smac_get(const vtss_inst_t    inst,
                         const vtss_port_no_t port_no,
                         vtss_mac_t  *const smac);

#endif /* VTSS_FEATURE_DELAY_REQ_AUTO_RESP */

/**
 * \brief Read sequence counter from AFI.
 * \param inst     [IN]          handle to an API instance
 * \param sec_cntr [IN]          sequence counter number [0..255]
 * \param cnt_val  [OUT]         actual value of the sequence counter
 *
 * \return Return code.
 */
vtss_rc vtss_ts_seq_cnt_get(const vtss_inst_t                inst,
                            const u32                        sec_cntr,
                            u16 *const                       cnt_val);

#ifdef __cplusplus
}
#endif
#endif /* VTSS_FEATURE_TIMESTAMP */
#endif // _VTSS_TS_API_H_

// ***************************************************************************
//
//  End of file.
//
// ***************************************************************************
