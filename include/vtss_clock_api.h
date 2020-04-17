// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief Clock API.
 * \details This header file describes Vitesse DPLL API functions and
 * associated types.
 */

#ifndef _VTSS_CLOCK_API_H_
#define _VTSS_CLOCK_API_H_

#include <vtss/api/types.h>

#if defined(VTSS_FEATURE_CLOCK)
#ifdef __cplusplus
extern "C" {
#endif

// ***************************************************************************
//
//  DPLL interface
//
// ***************************************************************************

/**
 * \brief clock global enable state. Will switch off system clock for omega IP if false
 **/
typedef BOOL vtss_clock_global_enable_t;

/**
 * \brief parameter describing the DPLL instance.
 *  In ES6514 Instance A = 0, Instance B = 1.
 **/
typedef u8 vtss_clock_dpll_inst_t;

/**
 * \brief parameter describing the DPLL selection mode.
 **/
typedef enum
{
    VTSS_CLOCK_SELECTION_MODE_DISABLED,                 /**< Controller / DPLL is disabled */
    VTSS_CLOCK_SELECTION_MODE_MANUEL,                   /**< Manually select an input */
    VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_NONREVERTIVE,   /**< Automatic selection mode non revertive */
    VTSS_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE,      /**< Automatic selection mode revertive */
    VTSS_CLOCK_SELECTION_MODE_FORCED_HOLDOVER,          /**< Manually selection mode forced to holdover */
    VTSS_CLOCK_SELECTION_MODE_FORCED_FREE_RUN,          /**< Manually selection mode forced to free-run */
    VTSS_CLOCK_SELECTION_MODE_FORCED_DCO,               /**< Selection mode Digitally Controlled Oscillator (DCO) */
} vtss_clock_selection_mode_t;

/**
 * \brief parameter setting up the DPLL selection mode.
 **/
typedef struct {
    vtss_clock_selection_mode_t mode;           /**< selection mode */
    u8                          clock_input;    /**< selected input id manual mode */
} vtss_clock_selection_conf_t;


/**
 * \brief parameter describing the DPLL selectior state.
 **/
typedef enum
{
    VTSS_CLOCK_SELECTOR_STATE_LOCKED,       /**< the dpll is locked to an input */
    VTSS_CLOCK_SELECTOR_STATE_HOLDOVER,     /**< the dpll is in holdover state */
    VTSS_CLOCK_SELECTOR_STATE_FREERUN,      /**< the dpll is in free-run state */
    VTSS_CLOCK_SELECTOR_STATE_DCO,          /**< the dpll is controlled by SW (DCO mode) */
    VTSS_CLOCK_SELECTOR_STATE_REF_FAILED,   /**< the selected reference failed */
    VTSS_CLOCK_SELECTOR_STATE_ACQUIRING,    /**< acquiring lock to the selected reference */
} vtss_clock_selector_state_t;

/**
 * \brief parameter describing the DPLL operation mode.
 **/
typedef enum
{
    VTSS_CLOCK_OPERATION_MODE_DISABLED,  /**< the dpll is DISABLED */
    VTSS_CLOCK_OPERATION_MODE_ENABLED,   /**< the dpll is ENABLED */
} vtss_clock_operation_mode_t;

//typedef enum
//{
//    VTSS_CLOCK_FILTER_BW_1MILLI_HZ, /**< the dpll filter bandwidth is 1 milli Hz */
//    VTSS_CLOCK_FILTER_BW_0_1_Hz,    /**< the dpll filter bandwidth is 0.1 Hz */
//    VTSS_CLOCK_FILTER_BW_5_HZ,      /**< the dpll filter bandwidth is 5 Hz */
//} vtss_clock_filter_bw_t;


/**
 * \brief parameter for setting up the phase slope limiter.
 */
typedef struct vtss_clock_psl_conf_t {
    u32                         limit_ppb;            /**< maximum phase slope in ppb [1..524000], 0 Disables the feature */
    BOOL                        phase_build_out_ena;  /**< If true, limited phase information is dismissed */
    BOOL                        ho_based;             /**< If true, slope limit is with respect to frequency offset stored in holdover stack*/
} vtss_clock_psl_conf_t;
  
/**
 * \brief parameter for setting the dpll configuration.
 */
typedef struct vtss_clock_dpll_conf_t {
    vtss_clock_operation_mode_t mode;       /**< clock operation mode. Enable / Disable */
    u16                         holdoff;    /**< holdoff time in ms (0 => holdoff disabled); the actual holdoff is in steps of 1 ms; i.e. values are trunkated to 1 ms multipla HW: 16 bit*/
    u32                         holdover;   /**< holdover time in ms [0..84600]       HW:17 bit*/
    u16                         wtr;        /**< wait-to-restore time in sec [0..720] HW:10 bit*/
} vtss_clock_dpll_conf_t;

/**
 * \brief parameter for setting the holdover stack configuration.
 */
typedef struct vtss_clock_ho_stack_conf_t {
    u32  ho_post_filtering_bw;    /**< holdover stack post filtering bandwidth im mHz [23 ... 1.46e9] es6514: Bugzilla #15547 [741 ... 1.46e9]*/
    u8   ho_qual_time_conf;       /**< holdover qulification time configuration. time in s = 2^ho_qual_time_conf conf. range: [0..11] => time: [1..2048]s */
} vtss_clock_ho_stack_conf_t;

#define VTSS_CLOCK_HO_STACK_SIZE 12 /**< Size of the holdover stack */
/**
 * \brief parameter for getting the holdover stack content.
 */
typedef struct vtss_clock_ho_stack_content_t {
    u64     stack_value[VTSS_CLOCK_HO_STACK_SIZE];        /**< HO-stack read data got all 12 stack levels (HO values in scaled PPB's) */
    u8      ho_sel;                 /**< Select ho-value to take in hold-over state. */
    u8      ho_min_fill_lvl;        /**< Minimum fill level before ho-stack considered full */
    BOOL    ho_filled;              /**< TRUE if stack is full */
} vtss_clock_ho_stack_content_t;

/**
 * \brief parameter for setting the priority for dpll source selection
 */
typedef struct vtss_clock_priority_selector_t {
    u8   priority;          /**< Priority - 0 is highest */
    BOOL enable;            /**< Enable for the respective priority */
} vtss_clock_priority_selector_t;

/**
 * \brief parameter for defining a ratio when selecting a frequency that is a rational number
 */
typedef struct vtss_clock_ratio_t {
    u32  num;               /**< numerator of a rational value */
    u32  den;               /**< denominator of a rational value */
} vtss_clock_ratio_t;

/**
 * \brief parameter for selecting the type of the clock input
 */
typedef enum
{
    VTSS_CLOCK_INPUT_TYPE_DPLL,     /**< a dpll output is selected as output */
    VTSS_CLOCK_INPUT_TYPE_IN,       /**< a input signal is directly selected as output */
    VTSS_CLOCK_INPUT_TYPE_PURE_DCO, /**< output is running purely on LC-PLL plus optional DCO */
} vtss_clock_input_type_t;

/**
 * \brief parameter for setting the clock output selector.
 */
typedef struct vtss_clock_input_selector_t {
    vtss_clock_input_type_t input_type;     /**< Defines if it is clock input or a DPLL outpus that drives the clock output */
    u8                      input_inst;     /**< defines the clock input or DPLL instance */
} vtss_clock_input_selector_t;

/**
 * \brief parameter for returning the dpll state.
 */
typedef struct vtss_clock_dpll_state_t {
    BOOL pll_freq_lock;     /**< PLL is stabilized to the selected frequency */
    BOOL pll_phase_lock;    /**< PLL is phase locked to incoming clock */
    BOOL pll_losx;          /**< PLL the currently selected reference input fails */
    BOOL pll_lol;           /**< PLL loss of lock */
    BOOL pll_dig_hold_vld;  /**< PLL Hold-over stack is filled with enough samples*/
} vtss_clock_dpll_state_t;

/**
 * \brief parameter for returning the clock input state.
 */
typedef struct vtss_clock_input_state_t {
    BOOL los;    /**< External Loss Of Signal */
    BOOL pfm;    /**< Precise frequency out of range */
    BOOL cfm;    /**< Coarse frequency out of range */
    BOOL scm;    /**< Single Cycle missed */
    BOOL lol;    /**< Loss of Lock */
} vtss_clock_input_state_t;

/**
 * \brief parameter for setting the alarm enables which control the input selection
 */
typedef struct vtss_clock_input_alarm_ena_t {
  BOOL los;   /**< Set to TRUE when Loss Of Signal alarm should influence the source selection */
  BOOL pfm;   /**< Set to TRUE when Precise frequency monitor alarm should influence the source selection */
  BOOL cfm;   /**< Set to TRUE when Coarse frequency monitor alarm should influence the source selection */
  BOOL scm;   /**< Set to TRUE when Single Cycle monitor alarm should influence the source selection */
  BOOL gst;   /**< Set to TRUE when Guard Soak timer alarm should influence the source selection */
  BOOL lol;   /**< Set to TRUE when Loss of Lock alarm should influence the source selection */
} vtss_clock_input_alarm_ena_t;

/**
 * \brief parameter for setting input selection parameters
 */
typedef struct vtss_clock_input_conf_t {
  BOOL                         los_active_high; /**< Set to TRUE when Loss Of Signal input is active high.*/
  vtss_clock_input_alarm_ena_t alarm_ena;       /**< Collection of alarm enables */
} vtss_clock_input_conf_t;

/**
 * \brief parameter for setting up the Coarse Frequency Monitor (CFM)
 */
typedef struct vtss_clock_cfm_conf_t {
  u32 cfm_set_ppb;      /**< Maximum frequency offset in ppb detected by the CFM before CFM alarm is issued. [0..200000] */
  u32 cfm_clr_ppb;      /**< Minimum frequency offset in ppb detected by the CFM before CFM alarm is cleared. [0..200000] */
} vtss_clock_cfm_conf_t;

/**
 * \brief parameter for setting up the Precise Frequency Monitor (PFM)
 */
typedef struct vtss_clock_pfm_conf_t {
  u32 pfm_set_ppb;      /**< Maximum frequency offset in ppb detected by the PFM before PFM alarm is issued. [0..200000] */
  u32 pfm_clr_ppb;      /**< Minimum frequency offset in ppb detected by the PFM before PFM alarm is cleared. [0..200000] */
} vtss_clock_pfm_conf_t;

/**
 * \brief parameter for setting up the GST
 */
typedef struct vtss_clock_gst_conf_t {
  u32 disqualification_time_us; /**< Disqualification time in micro seconds [1 us .. 1500s] */
  u32 qualification_time_us;    /**< Qualification time in micro seconds    [1 us .. 1500s] */
                                /**< 1/255 <= (diqualification_time_us/qualification_time_us) <= 255 */
  BOOL los;   /**< Set to TRUE when Loss Of Signal alarm should be source for GST */
  BOOL pfm;   /**< Set to TRUE when Precise frequency monitor alarm should be source for GST */
  BOOL cfm;   /**< Set to TRUE when Coarse frequency monitor alarm should be source for GST */
  BOOL scm;   /**< Set to TRUE when Single Cycle monitor alarm should be source for GST */
  BOOL lol;   /**< Set to TRUE when Loss of Lock alarm should be source for GST */
} vtss_clock_gst_conf_t;

// ***************************************************************************
//
//  Direct register access functions to be used for testing
//
// ***************************************************************************

/**
 * \brief Directly read from a HW register
 * \param inst [IN]         Handle to an API instance.
 * \param addr [IN]         Address
 * \param value [OUT]       Read value
 *
 * \return Return code.
 */
vtss_rc vtss_clock_rd(const vtss_inst_t  inst,
                      const u32          addr,
                      u32                *const value);

/**
 * \brief Directly write to a HW register
 * \param inst [IN]         Handle to an API instance.
 * \param addr [IN]         Address
 * \param value [IN]        Write value
 *
 * \return Return code.
 */
vtss_rc vtss_clock_wr(const vtss_inst_t  inst,
                      const u32          addr,
                      const u32          value);

/**
 * \brief Directly write to field(s) of a HW register (Read-Modify-Write)
 * \param inst [IN]         Handle to an API instance.
 * \param addr [IN]         Address
 * \param value [IN]        Write value
 * \param mask [IN]         Mask value, defines which bits can be changed
 *
 * \return Return code.
 */
vtss_rc vtss_clock_wrm(const vtss_inst_t  inst,
                       const u32          addr,
                       const u32          value,
                       const u32          mask);

// ***************************************************************************
//
//  Configuration API
//
// ***************************************************************************


/**
 * \brief Set global enable state
 * \param inst [IN]        Handle to an API instance.
 * \param ena [IN]         Enable/Disable flag
 *
 * \return Return code.
 */
vtss_rc vtss_clock_global_enable_set(const vtss_inst_t                 inst,
                                     const vtss_clock_global_enable_t  ena);

/**
 * \brief Get global enable state
 * \param inst [IN]        Handle to an API instance.
 * \param ena [OUT]        Enable/Disable flag
 *
 * \return Return code.
 */
vtss_rc vtss_clock_global_enable_get(const vtss_inst_t                inst,
                                     vtss_clock_global_enable_t       *ena);

/**
 * \brief Global SW Reset for the clock. Resets logic but not the configuration
 * \param inst [IN]        Handle to an API instance.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_global_sw_reset(const vtss_inst_t                 inst);

/**
 * \brief Shut down the clock HW. Called before a sw reset. Sets the Internal core clock back to default
 * \param inst [IN]        Handle to an API instance.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_shutdown(const vtss_inst_t                 inst);

/**
 * \brief Set Clock selection mode.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [IN]         Mode of clock selection and selected Clock input in manual mode [0..x].
 *
 * \return Return code.
 */
vtss_rc vtss_clock_selection_mode_set(const vtss_inst_t                 inst,
                                      const vtss_clock_dpll_inst_t      dpll,
                                      const vtss_clock_selection_conf_t *const conf);

/**
 * \brief Get Clock selection mode.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [OUT]        Mode of clock selection and selected Clock input in manual mode [0..x].
 *
 * \return Return code.
 */
vtss_rc vtss_clock_selection_mode_get(const vtss_inst_t             inst,
                                      const vtss_clock_dpll_inst_t  dpll,
                                      vtss_clock_selection_conf_t   *const conf);

/**
 * \brief Set Clock operation mode.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [IN]         Mode of clock operation.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_operation_conf_set(const vtss_inst_t                 inst,
                                      const vtss_clock_dpll_inst_t      dpll,
                                      const vtss_clock_dpll_conf_t      *const conf);

/**
 * \brief Get Clock operation mode.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [OUT]        Mode of clock operation.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_operation_conf_get(const vtss_inst_t             inst,
                                      const vtss_clock_dpll_inst_t  dpll,
                                      vtss_clock_dpll_conf_t        *const conf);

/**
 * \brief Set Holdover stack configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [IN]         configuration values
 *
 * \return Return code.
 */
vtss_rc vtss_clock_ho_stack_conf_set(const vtss_inst_t                 inst,
                                     const vtss_clock_dpll_inst_t      dpll,
                                     const vtss_clock_ho_stack_conf_t  *const conf);

/**
 * \brief Get Holdover stack configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [IN]         configuration values
 *
 * \return Return code.
 */
vtss_rc vtss_clock_ho_stack_conf_get(const vtss_inst_t                 inst,
                                     const vtss_clock_dpll_inst_t      dpll,
                                     vtss_clock_ho_stack_conf_t        *const conf);

/**
 * \brief Get Holdover stack content (for debug purpose)
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param cont [IN]         Ho stack content
 *
 * \return Return code.
 */
vtss_rc vtss_clock_ho_stack_content_get(const vtss_inst_t                 inst,
                                        const vtss_clock_dpll_inst_t      dpll,
                                        vtss_clock_ho_stack_content_t     *const cont);
/**
 * \brief Set Clock dpll frequency adjustment in DCO mode (directly influence the controller).
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param offset [IN]       Clock ratio frequency offset in units of scaled ppb (parts per billion) i.e. ppb*2**-16.
 *                          ratio > 0 => clock runs faster.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_dco_frequency_offset_set(const vtss_inst_t               inst,
                                            const vtss_clock_dpll_inst_t    dpll,
                                            const i64                       offset);

/**
 * \brief Get Clock dpll frequency adjustment in DCO mode (directly influence the controller).
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param offset [OUT]      Clock ratio frequency offset in units of scaled ppb (parts per billion) i.e. ppb*2**-16.
 *                          ratio > 0 => clock runs faster.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_dco_frequency_offset_get(const vtss_inst_t               inst,
                                            const vtss_clock_dpll_inst_t    dpll,
                                            i64                             *const offset);

/**
 * \brief Set Output Filter Bandwidth.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param bw_100uhz [IN]    Filtering bandwidth in untis of 100uHz the lowest limit is 300 uHz
 *                          A value of 0 disables the filter (Power down).
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_filter_bw_set(const vtss_inst_t                  inst,
                                        const u8                           clock_output,
                                        const u32                          bw_100uhz);

/**
 * \brief Get Output Filter Bandwidth.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param bw_100uhz [OUT]   Filtering bandwidth in untis of 100uHz
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_filter_bw_get(const vtss_inst_t                  inst,
                                        const u8                           clock_output,
                                        u32                                *bw_100uhz);

/**
 * \brief Trigger Output Filter to immediately lock to current frequency offset without low-pass filtering
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_filter_lock_fast_set(const vtss_inst_t                  inst,
                                               const u8                           clock_output);

/**
 * \brief Check if fast lock has completed.
 * \param inst [IN]             Handle to an API instance.
 * \param clock_output [IN]     Clock output port number
 * \param lock_completed [OUT]  fast lock has completed
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_filter_lock_fast_get(const vtss_inst_t                  inst,
                                               const u8                           clock_output,
                                               BOOL                               *lock_completed);
/**
 * \brief Set Output Filter Phase Slope Limiter (PSL) configuration
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param conf [IN]         configuration values
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_psl_conf_set(const vtss_inst_t                  inst,
                                       const u8                           clock_output,
                                       const vtss_clock_psl_conf_t        *const conf);

/**
 * \brief Get Output Filter Phase Slope Limiter (PSL) configuration
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param conf [OUT]        Filtering bandwidth in untis of 100uHz
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_psl_conf_get(const vtss_inst_t                  inst,
                                       const u8                           clock_output,
                                       vtss_clock_psl_conf_t              *const conf);

/**
 * \brief Set Clock dpll frequency adjustment (influence the respective output filter).
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param adj [IN]          Clock ratio frequency offset in units of scaled ppb (parts per billion) i.e. ppb*2**-16.
 *                          ratio > 0 => clock runs faster.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_adj_frequency_set(const vtss_inst_t               inst,
                                     const u8                        clock_output,
                                     const i64                       adj);

/**
 * \brief Get Clock dpll frequency adjustment (influence the respective output filter).
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param adj [OUT]         Clock ratio frequency offset in units of scaled ppb (parts pr billion) i.e. ppb*2**-16.
 *                          ratio > 0 => clock runs faster.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_adj_frequency_get(const vtss_inst_t               inst,
                                     const u8                        clock_output,
                                     i64                             *const adj);

/**
 * \brief Set Clock dpll phase adjustment.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port mask, i.e. setting bit x enables phase adjustment on output x
 * \param adj [IN]          Clock phase offset in units of scaled ns i.e. ns*2**-16.
 *                          ratio > 0 => clock phase is advanced.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_adj_phase_set(const vtss_inst_t               inst,
                                 const u8                        clock_output,
                                 const i32                       adj);

/**
 * \brief Get Clock dpll phase adjustment.
 * \param inst [IN]         Handle to an API instance.
 * \param adj_ongoing [OUT] TRUE if the phase adjust is ongoing, FALSE otherwise.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_adj_phase_get(const vtss_inst_t               inst,
                                 BOOL                            *const adj_ongoing);

/**
 * \brief Set Clock input priority.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         configuration values, Priority - 0 is highest priority 
 *
 * \return Return code.
 */
vtss_rc vtss_clock_priority_set(const vtss_inst_t                     inst,
                                const vtss_clock_dpll_inst_t          dpll,
                                const u8                              clock_input,
                                const vtss_clock_priority_selector_t  *const conf);

/**
 * \brief Get Clock input priority.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param clock_input [IN]  Clock input port number
 * \param conf [OUT]        configuration values, Priority - 0 is highest priority 
 *
 * \return Return code.
 */
vtss_rc vtss_clock_priority_get(const vtss_inst_t               inst,
                                const vtss_clock_dpll_inst_t    dpll,
                                const u8                        clock_input,
                                vtss_clock_priority_selector_t  *const conf);

/**
 * \brief Set Clock input frequency.
 * \param inst [IN]                   Handle to an API instance.
 * \param clock_input [IN]            Clock input port number
 * \param freq_khz [IN]               frequency in KHz, the frequency is rounded to the closest multiple of 8 KHz.
 *                                    freq_khz < 8 => clock input qualifier is disabled
 * \param use_internal_clock_src [IN] If TRUE, select an internally provided clock as source
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_frequency_set(const vtss_inst_t               inst,
                                       const u8                        clock_input,
                                       const u32                       freq_khz,
                                       const BOOL                      use_internal_clock_src);

/**
 * \brief Get Clock input frequency.
 * \param inst [IN]                    Handle to an API instance.
 * \param clock_input [IN]             Clock input port number
 * \param freq_khz [OUT]               frequency in KHz, freq_khz < 8 => clock input qualifier is disabled
 * \param use_internal_clock_src [OUT] An internally provided clock is used as source, if TRUE
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_frequency_get(const vtss_inst_t               inst,
                                       const u8                        clock_input,
                                       u32                             *const freq_khz,
                                       BOOL                            *const use_internal_clock_src);

/**
 * \brief Set Clock input frequency with ratio.
 * \param inst [IN]                   Handle to an API instance.
 * \param clock_input [IN]            Clock input port number
 * \param freq_khz [IN]               frequency in KHz, the frequency is rounded to the closest multiple of 8 KHz.
 *                                    freq_khz < 8 => clock input qualifier is disabled
 * \param ratio [IN]                  A ratio the freq_khz will be mutiplied with.e.g. 66/64. I order to allow rational values for the frequency
 * \param use_internal_clock_src [IN] If TRUE, select an internally provided clock as source
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_frequency_ratio_set(const vtss_inst_t               inst,
                                             const u8                        clock_input,
                                             const u32                       freq_khz,
                                             const vtss_clock_ratio_t        *const ratio,
                                             const BOOL                      use_internal_clock_src);

/**
 * \brief Get Clock input frequency with ratio.
 * \param inst [IN]                    Handle to an API instance.
 * \param clock_input [IN]             Clock input port number
 * \param freq_khz [OUT]               frequency in KHz, freq_khz < 8 => clock input qualifier is disabled
 * \param ratio [OUT]                  A ratio the freq_khz was mutiplied with.e.g. 66/64. I order to allow rational values for the frequency
 * \param use_internal_clock_src [OUT] An internally provided clock is used as source, if TRUE
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_frequency_ratio_get(const vtss_inst_t               inst,
                                             const u8                        clock_input,
                                             u32                             *const freq_khz,
                                             vtss_clock_ratio_t              *const ratio,
                                             BOOL                            *const use_internal_clock_src);

/**
 * \brief Set Clock output frequency.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param freq_khz [IN]     frequency in KHz.
 *                          freq_khz = 0 disables the clock
 * \param par_freq_khz [IN] parallel frequency in KHz. With parallel frequency the clock output of the
 *                          DF2F for the parallel data towards the core is ment.
 *                          Maximum parallel frequency is 400 MHz, minimum parallel frequency is 31.25 MHz.
 *                          Higher frequencies provide better jitter performance.
 *                          par_freq_khz = 0 disables the clock
 *
 *                          Note: Only one of the clocks can be active. Either freq_khz or par_freq_khz must be 0.
 *                          For selected frequencies there is a possibility that both clocks can be used.
 *                          The possible combinations can be looked up in DS1009-DPLL-Freq-Calc.xlsm and implemented on request.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_frequency_set(const vtss_inst_t               inst,
                                        const u8                        clock_output,
                                        const u32                       freq_khz,
                                        const u32                       par_freq_khz);

/**
 * \brief Get Clock output frequency.
 * \param inst [IN]          Handle to an API instance.
 * \param clock_output [IN]  Clock output port number
 * \param freq_khz [OUT]     frequency in KHz, freq_khz = 0, clock is disbaled
 * \param par_freq_khz [OUT] parallel frequency in KHz, par_freq_khz = 0, clock is disbaled
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_frequency_get(const vtss_inst_t               inst,
                                        const u8                        clock_output,
                                        u32                             *const freq_khz,
                                        u32                             *const par_freq_khz);

/**
 * \brief Set Clock output frequency.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param freq_khz [IN]     frequency in KHz.
 *                          freq_khz = 0 disables the clock
 * \param par_freq_khz [IN] parallel frequency in KHz. With parallel frequency the clock output of the
 *                          DF2F for the parallel data towards the core is ment.
 *                          Maximum parallel frequency is 400 MHz, minimum parallel frequency is 31.25 MHz.
 *                          Higher frequencies provide better jitter performance.
 *                          par_freq_khz = 0 disables the clock
 *
 *                          Note: Only one of the clocks can be active. Either freq_khz or par_freq_khz must be 0.
 *                          For selected frequencies there is a possibility that both clocks can be used.
 *                          The possible combinations can be looked up in DS1009-DPLL-Freq-Calc.xlsm and implemented on request.
 * \param ratio [IN]        A ratio the freq_khz will be mutiplied with.e.g. 66/64. I order to allow rational values for the frequency
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_frequency_ratio_set(const vtss_inst_t               inst,
                                              const u8                        clock_output,
                                              const u32                       freq_khz,
                                              const u32                       par_freq_khz,
                                              const vtss_clock_ratio_t        *const ratio);

/**
 * \brief Get Clock output frequency.
 * \param inst [IN]          Handle to an API instance.
 * \param clock_output [IN]  Clock output port number
 * \param freq_khz [OUT]     frequency in KHz, freq_khz = 0, clock is disbaled
 * \param par_freq_khz [OUT] parallel frequency in KHz, par_freq_khz = 0, clock is disbaled
 * \param ratio [OUT]        A ratio the freq_khz was mutiplied with.e.g. 66/64. I order to allow rational values for the frequency
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_frequency_ratio_get(const vtss_inst_t               inst,
                                              const u8                        clock_output,
                                              u32                             *const freq_khz,
                                              u32                             *const par_freq_khz,
                                              vtss_clock_ratio_t              *const ratio);

/**
 * \brief Set Clock output Voltage level.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param level_mv [IN]     Output Voltage in mV range [300..1275], 25 mV steps [Output level of es6514 is limited due to bug in a coil in the OB]
 *                          
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_level_set(const vtss_inst_t               inst,
                                    const u8                        clock_output,
                                    const u16                       level_mv);

/**
 * \brief Get Clock output Voltage level.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param level_mv [OUT]    Output Voltage in mV range [300..1275], 25 mV steps
 *                          
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_level_get(const vtss_inst_t               inst,
                                    const u8                        clock_output,
                                    u16                             *const level_mv);

/**
 * \brief Set Clock output selector.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param input [IN]     input selector.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_selector_set(const vtss_inst_t               inst,
                                       const u8                        clock_output,
                                       const vtss_clock_input_selector_t *const input);

/**
 * \brief Get Clock output selector.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param input [OUT]       input selector.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_output_selector_get(const vtss_inst_t               inst,
                                       const u8                        clock_output,
                                       vtss_clock_input_selector_t     *const input);

/**
 * \brief Set Clock input alarm configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Alarm enable for various qualifier arlarms and LOS active level
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_alarm_conf_set(const vtss_inst_t               inst,
                                        const u8                        clock_input,
                                        const vtss_clock_input_conf_t   *const conf);

/**
 * \brief Get Clock input alarm configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [OUT]        Alarm enable for various qualifier arlarms and LOS active level
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_alarm_conf_get(const vtss_inst_t               inst,
                                        const u8                        clock_input,
                                        vtss_clock_input_conf_t         *const conf);

/**
 * \brief Set Clock input Coarse Frequency Monitor configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Coarse Frequency Monitor Configurations
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_cfm_conf_set(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      const vtss_clock_cfm_conf_t  *const conf);

/**
 * \brief Get Clock input Coarse Frequency Monitor configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Coarse Frequency Monitor Configurations
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_cfm_conf_get(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      vtss_clock_cfm_conf_t        *const conf);

/**
 * \brief Set Clock input Precise Frequency Monitor configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Precise Frequency Monitor Configurations
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_pfm_conf_set(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      const vtss_clock_pfm_conf_t  *const conf);

/**
 * \brief Get Clock input Precise Frequency Monitor configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Precise Frequency Monitor Configurations
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_pfm_conf_get(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      vtss_clock_pfm_conf_t        *const conf);
/**
 * \brief Set Clock input guard soak timer configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Guard Soak Timer Configurations
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_gst_conf_set(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      const vtss_clock_gst_conf_t  *const conf);

/**
 * \brief Get Clock input guard soak timer configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [OUT]        Guard Soak Timer Configurations
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_gst_conf_get(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      vtss_clock_gst_conf_t        *const conf);

// ***************************************************************************
//
//  Status API
//
// ***************************************************************************

/**
 * \brief get Clock selector state.
 * \param inst [IN]             Handle to an API instance.
 * \param dpll [IN]             DPLL instance number [0..x].
 * \param selector_state [OUT]  selector state
 * \param clock_input [OUT]     Clock input port number - if in locked state
 *
 * \return Return code.
 */
vtss_rc vtss_clock_selector_state_get(const vtss_inst_t             inst,
                                      const vtss_clock_dpll_inst_t  dpll,
                                      vtss_clock_selector_state_t   *const selector_state,
                                      u8                            *const clock_input);

/**
 * \brief get Clock pll state.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param pll_state [OUT]   pll state
 *
 * \return Return code.
 */
vtss_rc vtss_clock_dpll_state_get(const vtss_inst_t             inst,
                                  const vtss_clock_dpll_inst_t  dpll,
                                  vtss_clock_dpll_state_t       *const pll_state);

/**
 * \brief get Clock frequency offset stored in ho stack
 * \param inst [IN]       Handle to an API instance.
 * \param dpll [IN]       DPLL instance number [0..x].
 * \param offset [OUT]    Current frequency offset stored in the holdover stack in units of scaled ppb (parts per billion) i.e. ppb*2**-16.
 *
 * \return Return code.
 */
vtss_rc vtss_clock_ho_stack_frequency_offset_get(const vtss_inst_t             inst,
                                                 const vtss_clock_dpll_inst_t  dpll,
                                                 i64                           *const offset);

/**
 * \brief get Clock input state.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param input_state [OUT] input state
 *
 * \return Return code.
 */
vtss_rc vtss_clock_input_state_get(const vtss_inst_t            inst,
                                  const u8                      clock_input,
                                  vtss_clock_input_state_t      *const input_state);

// ***************************************************************************
//
//  Event (interrupt) handling API
//
// ***************************************************************************

/**
 * \brief Define event (interrupt) types related to the Vitesse Synce Clock inputs.
 **/
#define VTSS_CLOCK_INPUT_LOS_EV     (1 << 0)  /**< External Loss Of Signal event */
#define VTSS_CLOCK_INPUT_PFM_EV     (1 << 1)  /**< Precise frequency monitor event */
#define VTSS_CLOCK_INPUT_CFM_EV     (1 << 2)  /**< Coarse frequency monitor event */
#define VTSS_CLOCK_INPUT_SCM_EV     (1 << 3)  /**< Single Cycle monitor event */
#define VTSS_CLOCK_INPUT_GST_EV     (1 << 4)  /**< Guard Soak timer event */
#define VTSS_CLOCK_INPUT_LOL_EV     (1 << 5)  /**< Loss of Lock event */
typedef u32 vtss_clock_input_event_type_t; /**< Int events: Single event or 'OR' multiple events above */

/**
 * \brief Clock input event polling function called by interrupt or periodicly
 *
 * \param inst        [IN]  Target instance reference.
 * \param clock_input [IN]  Clock input port number
 * \param ev_mask     [OUT] Event type mask of active events
 *
 * \note The \e ev_mask parameter can be either a single event_type or
 * multiple event types. If invoked by a
 * processor interrupt signal, the type of event to check for may be
 * narrowed in to specific events.
 *
 * \return Return code.
 **/
vtss_rc vtss_clock_input_event_poll(const vtss_inst_t               inst,
                                    const u8                        clock_input,
                                    vtss_clock_input_event_type_t   *const ev_mask);

/**
 * \brief Enable clock input event generation for a specific event type
 *
 * \param inst        [IN]  Target instance reference.
 * \param clock_input [IN]  Clock input port number
 * \param ev_mask     [IN]  Event type(s) to control (mask)
 * \param enable      [IN]  Enable or disable events
 *
 * \return Return code.
 **/
vtss_rc vtss_clock_input_event_enable(const vtss_inst_t                     inst,
                                      const u8                              clock_input,
                                      const vtss_clock_input_event_type_t   ev_mask,
                                      const BOOL                            enable);

/**
 * \brief Define event (interrupt) types related to the Vitesse Synce Clock dpll's.
 *
 **/
//    VTSS_CLOCK_DPLL_FREQ_LOCK_EV =      (1 << 0), /**< Loss Of Frequency lock event */
//    VTSS_CLOCK_DPLL_PH_LOCK_EV   =      (1 << 1), /**< Loss Of Phase lock event */
//    VTSS_CLOCK_DPLL_LOSX         =      (1 << 2), /**< PLL the currently selected reference input fails event */
//    VTSS_CLOCK_DPLL_LOL          =      (1 << 3), /**< PLL loss of lock event */
#define VTSS_CLOCK_DPLL_STATE_CHANGE_EV   (1 << 0) /**< State change event in EEC FSM */
typedef u32 vtss_clock_dpll_event_type_t; /**< Int events: Currently only Single event */

/**
 * \brief Clock dpll event polling function called by interrupt or periodicly
 *
 * \param inst        [IN]  Target instance reference.
 * \param dpll        [IN]  DPLL instance number [0..x].
 * \param ev_mask     [OUT] Event type mask of active events
 *
 * \note The \e ev_mask parameter can be either a single event_type or
 * multiple event types. If invoked by a
 * processor interrupt signal, the type of event to check for may be
 * narrowed in to specific events.
 *
 * \return Return code.
 **/
vtss_rc vtss_clock_dpll_event_poll(const vtss_inst_t              inst,
                                   const vtss_clock_dpll_inst_t   dpll,
                                   vtss_clock_dpll_event_type_t   *const ev_mask);

/**
 * \brief Enable clock dpll event generation for a specific event type
 *
 * \param inst        [IN]  Target instance reference.
 * \param dpll        [IN]  DPLL instance number [0..x].
 * \param ev_mask     [IN]  Event type(s) to control (mask)
 * \param enable      [IN]  Enable or disable events
 *
 * \return Return code.
 **/
vtss_rc vtss_clock_dpll_event_enable(const vtss_inst_t                  inst,
                                     const vtss_clock_dpll_inst_t       dpll,
                                     const vtss_clock_dpll_event_type_t ev_mask,
                                     const BOOL                         enable);

#ifdef __cplusplus
}
#endif
#endif /* VTSS_FEATURE_OMEGA */
#endif // _VTSS_CLOCK_API_H_


// ***************************************************************************
//
//  End of file.
//
// ***************************************************************************
