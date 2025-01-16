// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_SWITCH_API_CLOCK_
#define _MICROCHIP_ETHERNET_SWITCH_API_CLOCK_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h> // ALL INCLUDE ABOVE THIS LINE

// ***************************************************************************
//
//  DPLL interface
//
// ***************************************************************************

/**
 * \brief clock global enable state. Will switch off system clock for omega IP
 *if false
 **/
typedef mesa_bool_t mesa_clock_global_enable_t;

/**
 * \brief parameter describing the DPLL instance.
 *  In ES6514 Instance A = 0, Instance B = 1.
 **/
typedef uint8_t mesa_clock_dpll_inst_t;

/**
 * \brief parameter describing the DPLL selection mode.
 **/
typedef enum {
    MESA_CLOCK_SELECTION_MODE_DISABLED, /**< Controller / DPLL is disabled */
    MESA_CLOCK_SELECTION_MODE_MANUEL,   /**< Manually select an input */
    MESA_CLOCK_SELECTION_MODE_AUTOMATIC_NONREVERTIVE, /**< Automatic selection
                                                         mode non revertive */
    MESA_CLOCK_SELECTION_MODE_AUTOMATIC_REVERTIVE, /**< Automatic selection mode
                                                      revertive */
    MESA_CLOCK_SELECTION_MODE_FORCED_HOLDOVER,     /**< Manually selection mode
                                                      forced to holdover */
    MESA_CLOCK_SELECTION_MODE_FORCED_FREE_RUN,     /**< Manually selection mode
                                                      forced to free-run */
    MESA_CLOCK_SELECTION_MODE_FORCED_DCO,          /**< Selection mode Digitally
                                                      Controlled Oscillator (DCO) */
} mesa_clock_selection_mode_t CAP(CLOCK);

/**
 * \brief parameter setting up the DPLL selection mode.
 **/
typedef struct {
    mesa_clock_selection_mode_t mode; /**< selection mode */
    uint8_t clock_input;              /**< selected input id manual mode */
} mesa_clock_selection_conf_t CAP(CLOCK);

/**
 * \brief parameter describing the DPLL selectior state.
 **/
typedef enum {
    MESA_CLOCK_SELECTOR_STATE_LOCKED,   /**< the dpll is locked to an input */
    MESA_CLOCK_SELECTOR_STATE_HOLDOVER, /**< the dpll is in holdover state */
    MESA_CLOCK_SELECTOR_STATE_FREERUN,  /**< the dpll is in free-run state */
    MESA_CLOCK_SELECTOR_STATE_DCO, /**< the dpll is controlled by SW (DCO mode) */
    MESA_CLOCK_SELECTOR_STATE_REF_FAILED, /**< the selected reference failed */
    MESA_CLOCK_SELECTOR_STATE_ACQUIRING,  /**< acquiring lock to the selected
                                             reference */
} mesa_clock_selector_state_t CAP(CLOCK);

/**
 * \brief parameter describing the DPLL operation mode.
 **/
typedef enum {
    MESA_CLOCK_OPERATION_MODE_DISABLED, /**< the dpll is DISABLED */
    MESA_CLOCK_OPERATION_MODE_ENABLED,  /**< the dpll is ENABLED */
} mesa_clock_operation_mode_t CAP(CLOCK);

/**
 * \brief parameter for setting up the phase slope limiter.
 */
typedef struct mesa_clock_psl_conf_t {
    uint32_t limit_ppb; /**< maximum phase slope in ppb [1..524000], 0 Disables
                           the feature */
    mesa_bool_t phase_build_out_ena; /**< If true, limited phase information is
                                        dismissed */
    mesa_bool_t ho_based; /**< If true, slope limit is with respect to frequency
                             offset stored in holdover stack*/
} mesa_clock_psl_conf_t CAP(CLOCK);

/**
 * \brief parameter for setting the dpll configuration.
 */
typedef struct mesa_clock_dpll_conf_t {
    mesa_clock_operation_mode_t
             mode;     /**< clock operation mode. Enable / Disable */
    uint16_t holdoff;  /**< holdoff time in ms (0 => holdoff disabled); the
                          actual holdoff is in steps of 1 ms; i.e. values are
                          trunkated to 1 ms multipla HW: 16 bit*/
    uint32_t holdover; /**< holdover time in ms [0..84600]       HW:17 bit*/
    uint16_t wtr;      /**< wait-to-restore time in sec [0..720] HW:10 bit*/
} mesa_clock_dpll_conf_t CAP(CLOCK);

/**
 * \brief parameter for setting the holdover stack configuration.
 */
typedef struct mesa_clock_ho_stack_conf_t {
    uint32_t ho_post_filtering_bw; /**< holdover stack post filtering bandwidth
                                      im mHz [23 ... 1.46e9] es6514: Bugzilla
                                      #15547 [741 ... 1.46e9]*/
    uint8_t ho_qual_time_conf; /**< holdover qulification time configuration.
                                  time in s = 2^ho_qual_time_conf conf. range:
                                  [0..11] => time: [1..2048]s */
} mesa_clock_ho_stack_conf_t CAP(CLOCK);

#define MESA_CLOCK_HO_STACK_SIZE 12 /**< Size of the holdover stack */
/**
 * \brief parameter for getting the holdover stack content.
 */
typedef struct mesa_clock_ho_stack_content_t {
    uint64_t stack_value[MESA_CLOCK_HO_STACK_SIZE]; /**< HO-stack read data got
                                                       all 12 stack levels */
    uint8_t ho_sel;          /**< Select ho-value to take in hold-over state. */
    uint8_t ho_min_fill_lvl; /**< Minimum fill level before ho-stack considered
                                full */
    mesa_bool_t ho_filled;   /**< TRUE if stack is full */
} mesa_clock_ho_stack_content_t CAP(CLOCK);

/**
 * \brief parameter for setting the priority for dpll source selection
 */
typedef struct mesa_clock_priority_selector_t {
    uint8_t     priority; /**< Priority - 0 is highest */
    mesa_bool_t enable;   /**< Enable for the respective priority */
} mesa_clock_priority_selector_t CAP(CLOCK);

/**
 * \brief parameter for defining a ratio when selecting a frequency that is a
 * rational number
 */
typedef struct mesa_clock_ratio_t {
    uint32_t num; /**< numerator of a rational value */
    uint32_t den; /**< denominator of a rational value */
} mesa_clock_ratio_t CAP(CLOCK);

/**
 * \brief parameter for selecting the type of the clock input
 */
typedef enum {
    MESA_CLOCK_INPUT_TYPE_DPLL, /**< a dpll output is selected as output */
    MESA_CLOCK_INPUT_TYPE_IN, /**< a input signal is directly selected as output
                               */
    MESA_CLOCK_INPUT_TYPE_PURE_DCO, /**< output is running purely on LC-PLL plus
                                       optional DCO */
} mesa_clock_input_type_t CAP(CLOCK);

/**
 * \brief parameter for setting the clock output selector.
 */
typedef struct mesa_clock_input_selector_t {
    mesa_clock_input_type_t
        input_type;     /**< Defines if it is clock input or a DPLL outpus that
                           drives the clock output */
    uint8_t input_inst; /**< defines the clock input or DPLL instance */
} mesa_clock_input_selector_t CAP(CLOCK);

/**
 * \brief parameter for returning the dpll state.
 */
typedef struct mesa_clock_dpll_state_t {
    mesa_bool_t
        pll_freq_lock; /**< PLL is stabilized to the selected frequency */
    mesa_bool_t pll_phase_lock; /**< PLL is phase locked to incoming clock */
    mesa_bool_t
        pll_losx; /**< PLL the currently selected reference input fails */
    mesa_bool_t pll_lol;          /**< PLL loss of lock */
    mesa_bool_t pll_dig_hold_vld; /**< PLL Hold-over stack is filled with enough
                                     samples*/
} mesa_clock_dpll_state_t CAP(CLOCK);

/**
 * \brief parameter for returning the clock input state.
 */
typedef struct mesa_clock_input_state_t {
    mesa_bool_t los; /**< External Loss Of Signal */
    mesa_bool_t pfm; /**< Precise frequency out of range */
    mesa_bool_t cfm; /**< Coarse frequency out of range */
    mesa_bool_t scm; /**< Single Cycle missed */
    mesa_bool_t lol; /**< Loss of Lock */
} mesa_clock_input_state_t CAP(CLOCK);

/**
 * \brief parameter for setting the alarm enables which control the input
 * selection
 */
typedef struct mesa_clock_input_alarm_ena_t {
    mesa_bool_t los; /**< Set to TRUE when Loss Of Signal alarm should influence
                        the source selection */
    mesa_bool_t pfm; /**< Set to TRUE when Precise frequency monitor alarm
                        should influence the source selection */
    mesa_bool_t cfm; /**< Set to TRUE when Coarse frequency monitor alarm should
                        influence the source selection */
    mesa_bool_t scm; /**< Set to TRUE when Single Cycle monitor alarm should
                        influence the source selection */
    mesa_bool_t gst; /**< Set to TRUE when Guard Soak timer alarm should
                        influence the source selection */
    mesa_bool_t lol; /**< Set to TRUE when Loss of Lock alarm should influence
                        the source selection */
} mesa_clock_input_alarm_ena_t CAP(CLOCK);

/**
 * \brief parameter for setting input selection parameters
 */
typedef struct mesa_clock_input_conf_t {
    mesa_bool_t los_active_high; /**< Set to TRUE when Loss Of Signal input is
                                    active high.*/
    mesa_clock_input_alarm_ena_t alarm_ena; /**< Collection of alarm enables */
} mesa_clock_input_conf_t CAP(CLOCK);

/**
 * \brief parameter for setting up the Coarse Frequency Monitor (CFM)
 */
typedef struct mesa_clock_cfm_conf_t {
    uint32_t cfm_set_ppb; /**< Maximum frequency offset in ppb detected by the
                             CFM before CFM alarm is issued. [0..200000] */
    uint32_t cfm_clr_ppb; /**< Minimum frequency offset in ppb detected by the
                             CFM before CFM alarm is cleared. [0..200000] */
} mesa_clock_cfm_conf_t CAP(CLOCK);

/**
 * \brief parameter for setting up the Precise Frequency Monitor (PFM)
 */
typedef struct mesa_clock_pfm_conf_t {
    uint32_t pfm_set_ppb; /**< Maximum frequency offset in ppb detected by the
                             PFM before PFM alarm is issued. [0..200000] */
    uint32_t pfm_clr_ppb; /**< Minimum frequency offset in ppb detected by the
                             PFM before PFM alarm is cleared. [0..200000] */
} mesa_clock_pfm_conf_t CAP(CLOCK);

/**
 * \brief parameter for setting up the GST
 */
typedef struct mesa_clock_gst_conf_t {
    uint32_t disqualification_time_us; /**< Disqualification time in micro
                                          seconds [1 us .. 1500s] */
    uint32_t qualification_time_us; /**< Qualification time in micro seconds [1
                                       us .. 1500s] */
    /**< 1/255 <= (diqualification_time_us/qualification_time_us) <= 255 */
    mesa_bool_t los; /**< Set to TRUE when Loss Of Signal alarm should be source
                        for GST */
    mesa_bool_t pfm; /**< Set to TRUE when Precise frequency monitor alarm
                        should be source for GST */
    mesa_bool_t cfm; /**< Set to TRUE when Coarse frequency monitor alarm should
                        be source for GST */
    mesa_bool_t scm; /**< Set to TRUE when Single Cycle monitor alarm should be
                        source for GST */
    mesa_bool_t lol; /**< Set to TRUE when Loss of Lock alarm should be source
                        for GST */
} mesa_clock_gst_conf_t CAP(CLOCK);

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
mesa_rc mesa_clock_rd(const mesa_inst_t inst,
                      const uint32_t    addr,
                      uint32_t *const   value) CAP(CLOCK);

/**
 * \brief Directly write to a HW register
 * \param inst [IN]         Handle to an API instance.
 * \param addr [IN]         Address
 * \param value [IN]        Write value
 *
 * \return Return code.
 */
mesa_rc mesa_clock_wr(const mesa_inst_t inst,
                      const uint32_t    addr,
                      const uint32_t    value) CAP(CLOCK);

/**
 * \brief Directly write to field(s) of a HW register (Read-Modify-Write)
 * \param inst [IN]         Handle to an API instance.
 * \param addr [IN]         Address
 * \param value [IN]        Write value
 * \param mask [IN]         Mask value, defines which bits can be changed
 *
 * \return Return code.
 */
mesa_rc mesa_clock_wrm(const mesa_inst_t inst,
                       const uint32_t    addr,
                       const uint32_t    value,
                       const uint32_t    mask) CAP(CLOCK);

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
mesa_rc mesa_clock_global_enable_set(const mesa_inst_t                inst,
                                     const mesa_clock_global_enable_t ena)
    CAP(CLOCK);

/**
 * \brief Get global enable state
 * \param inst [IN]        Handle to an API instance.
 * \param ena [OUT]        Enable/Disable flag
 *
 * \return Return code.
 */
mesa_rc mesa_clock_global_enable_get(const mesa_inst_t           inst,
                                     mesa_clock_global_enable_t *ena)
    CAP(CLOCK);

/**
 * \brief Global SW Reset for the clock. Resets logic but not the configuration
 * \param inst [IN]        Handle to an API instance.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_global_sw_reset(const mesa_inst_t inst) CAP(CLOCK);

/**
 * \brief Shut down the clock HW. Called before a sw reset. Sets the Internal
 * core clock back to default
 * \param inst [IN]        Handle to an API instance.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_shutdown(const mesa_inst_t inst) CAP(CLOCK);

/**
 * \brief Set Clock selection mode.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [IN]         Mode of clock selection and selected Clock input in
 * manual mode [0..x].
 *
 * \return Return code.
 */
mesa_rc mesa_clock_selection_mode_set(const mesa_inst_t            inst,
                                      const mesa_clock_dpll_inst_t dpll,
                                      const mesa_clock_selection_conf_t
                                          *const conf) CAP(CLOCK);

/**
 * \brief Get Clock selection mode.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [OUT]        Mode of clock selection and selected Clock input in
 * manual mode [0..x].
 *
 * \return Return code.
 */
mesa_rc mesa_clock_selection_mode_get(const mesa_inst_t                  inst,
                                      const mesa_clock_dpll_inst_t       dpll,
                                      mesa_clock_selection_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Set Clock operation mode.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [IN]         Mode of clock operation.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_operation_conf_set(const mesa_inst_t                   inst,
                                      const mesa_clock_dpll_inst_t        dpll,
                                      const mesa_clock_dpll_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Get Clock operation mode.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [OUT]        Mode of clock operation.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_operation_conf_get(const mesa_inst_t             inst,
                                      const mesa_clock_dpll_inst_t  dpll,
                                      mesa_clock_dpll_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Set Holdover stack configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [IN]         configuration values
 *
 * \return Return code.
 */
mesa_rc mesa_clock_ho_stack_conf_set(const mesa_inst_t            inst,
                                     const mesa_clock_dpll_inst_t dpll,
                                     const mesa_clock_ho_stack_conf_t
                                         *const conf) CAP(CLOCK);

/**
 * \brief Get Holdover stack configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param conf [IN]         configuration values
 *
 * \return Return code.
 */
mesa_rc mesa_clock_ho_stack_conf_get(const mesa_inst_t                 inst,
                                     const mesa_clock_dpll_inst_t      dpll,
                                     mesa_clock_ho_stack_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Get Holdover stack content (for debug purpose)
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param cont [IN]         Ho stack content
 *
 * \return Return code.
 */
mesa_rc mesa_clock_ho_stack_content_get(const mesa_inst_t            inst,
                                        const mesa_clock_dpll_inst_t dpll,
                                        mesa_clock_ho_stack_content_t
                                            *const cont) CAP(CLOCK);

/**
 * \brief Set Clock dpll frequency adjustment in DCO mode (directly influence
 * the controller).
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param offset [IN]       Clock ratio frequency offset in units of scaled ppb
 * (parts per billion) i.e. ppb*2**-16. ratio > 0 => clock runs faster.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_dco_frequency_offset_set(const mesa_inst_t            inst,
                                            const mesa_clock_dpll_inst_t dpll,
                                            const int64_t offset) CAP(CLOCK);

/**
 * \brief Get Clock dpll frequency adjustment in DCO mode (directly influence
 * the controller).
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param offset [OUT]      Clock ratio frequency offset in units of scaled ppb
 * (parts per billion) i.e. ppb*2**-16. ratio > 0 => clock runs faster.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_dco_frequency_offset_get(const mesa_inst_t            inst,
                                            const mesa_clock_dpll_inst_t dpll,
                                            int64_t *const offset) CAP(CLOCK);

/**
 * \brief Set Output Filter Bandwidth.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param bw_100uhz [IN]    Filtering bandwidth in untis of 100uHz the lowest
 * limit is 300 uHz A value of 0 disables the filter (Power down).
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_filter_bw_set(const mesa_inst_t inst,
                                        const uint8_t     clock_output,
                                        const uint32_t    bw_100uhz) CAP(CLOCK);

/**
 * \brief Get Output Filter Bandwidth.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param bw_100uhz [OUT]   Filtering bandwidth in untis of 100uHz
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_filter_bw_get(const mesa_inst_t inst,
                                        const uint8_t     clock_output,
                                        uint32_t         *bw_100uhz) CAP(CLOCK);

/**
 * \brief Trigger Output Filter to immediately lock to current frequency offset
 * without low-pass filtering
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_filter_lock_fast_set(const mesa_inst_t inst,
                                               const uint8_t     clock_output)
    CAP(CLOCK);

/**
 * \brief Check if fast lock has completed.
 * \param inst [IN]             Handle to an API instance.
 * \param clock_output [IN]     Clock output port number
 * \param lock_completed [OUT]  fast lock has completed
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_filter_lock_fast_get(const mesa_inst_t inst,
                                               const uint8_t     clock_output,
                                               mesa_bool_t      *lock_completed)
    CAP(CLOCK);

/**
 * \brief Set Output Filter Phase Slope Limiter (PSL) configuration
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param conf [IN]         configuration values
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_psl_conf_set(const mesa_inst_t inst,
                                       const uint8_t     clock_output,
                                       const mesa_clock_psl_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Get Output Filter Phase Slope Limiter (PSL) configuration
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param conf [OUT]        Filtering bandwidth in untis of 100uHz
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_psl_conf_get(const mesa_inst_t inst,
                                       const uint8_t     clock_output,
                                       mesa_clock_psl_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Set Clock dpll frequency adjustment (influence the respective output
 * filter).
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param adj [IN]          Clock ratio frequency offset in units of scaled ppb
 * (parts per billion) i.e. ppb*2**-16. ratio > 0 => clock runs faster.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_adj_frequency_set(const mesa_inst_t inst,
                                     const uint8_t     clock_output,
                                     const int64_t     adj) CAP(CLOCK);

/**
 * \brief Get Clock dpll frequency adjustment (influence the respective output
 * filter).
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param adj [OUT]         Clock ratio frequency offset in units of scaled ppb
 * (parts pr billion) i.e. ppb*2**-16. ratio > 0 => clock runs faster.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_adj_frequency_get(const mesa_inst_t inst,
                                     const uint8_t     clock_output,
                                     int64_t *const    adj) CAP(CLOCK);

/**
 * \brief Set Clock dpll phase adjustment.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port mask, i.e. setting bit x enables
 * phase adjustment on output x
 * \param adj [IN]          Clock phase offset in units of scaled ns i.e.
 * ns*2**-16. ratio > 0 => clock phase is advanced.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_adj_phase_set(const mesa_inst_t inst,
                                 const uint8_t     clock_output,
                                 const int32_t     adj) CAP(CLOCK);

/**
 * \brief Get Clock dpll phase adjustment.
 * \param inst [IN]         Handle to an API instance.
 * \param adj_ongoing [OUT] TRUE if the phase adjust is ongoing, FALSE otherwise.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_adj_phase_get(const mesa_inst_t  inst,
                                 mesa_bool_t *const adj_ongoing) CAP(CLOCK);

/**
 * \brief Set Clock input priority.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         configuration values, Priority - 0 is highest
 * priority
 *
 * \return Return code.
 */
mesa_rc mesa_clock_priority_set(const mesa_inst_t            inst,
                                const mesa_clock_dpll_inst_t dpll,
                                const uint8_t                clock_input,
                                const mesa_clock_priority_selector_t *const conf)
    CAP(CLOCK);

/**
 * \brief Get Clock input priority.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param clock_input [IN]  Clock input port number
 * \param conf [OUT]        configuration values, Priority - 0 is highest
 * priority
 *
 * \return Return code.
 */
mesa_rc mesa_clock_priority_get(const mesa_inst_t            inst,
                                const mesa_clock_dpll_inst_t dpll,
                                const uint8_t                clock_input,
                                mesa_clock_priority_selector_t *const conf)
    CAP(CLOCK);

/**
 * \brief Set Clock input frequency.
 * \param inst [IN]                   Handle to an API instance.
 * \param clock_input [IN]            Clock input port number
 * \param freq_khz [IN]               frequency in KHz, the frequency is rounded
 * to the closest multiple of 8 KHz. freq_khz < 8 => clock input qualifier is
 * disabled
 * \param use_internal_clock_src [IN] If TRUE, select an internally provided
 * clock as source
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_frequency_set(const mesa_inst_t inst,
                                       const uint8_t     clock_input,
                                       const uint32_t    freq_khz,
                                       const mesa_bool_t use_internal_clock_src)
    CAP(CLOCK);

/**
 * \brief Get Clock input frequency.
 * \param inst [IN]                    Handle to an API instance.
 * \param clock_input [IN]             Clock input port number
 * \param freq_khz [OUT]               frequency in KHz, freq_khz < 8 => clock
 * input qualifier is disabled
 * \param use_internal_clock_src [OUT] An internally provided clock is used as
 * source, if TRUE
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_frequency_get(const mesa_inst_t inst,
                                       const uint8_t     clock_input,
                                       uint32_t *const   freq_khz,
                                       mesa_bool_t *const use_internal_clock_src)
    CAP(CLOCK);

/**
 * \brief Set Clock input frequency with ratio.
 * \param inst [IN]                   Handle to an API instance.
 * \param clock_input [IN]            Clock input port number
 * \param freq_khz [IN]               frequency in KHz, the frequency is rounded
 * to the closest multiple of 8 KHz. freq_khz < 8 => clock input qualifier is
 * disabled
 * \param ratio [IN]                  A ratio the freq_khz will be mutiplied
 * with.e.g. 66/64. I order to allow rational values for the frequency
 * \param use_internal_clock_src [IN] If TRUE, select an internally provided
 * clock as source
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_frequency_ratio_set(const mesa_inst_t inst,
                                             const uint8_t     clock_input,
                                             const uint32_t    freq_khz,
                                             const mesa_clock_ratio_t
                                                 *const ratio,
                                             const mesa_bool_t
                                                 use_internal_clock_src)
    CAP(CLOCK);

/**
 * \brief Get Clock input frequency with ratio.
 * \param inst [IN]                    Handle to an API instance.
 * \param clock_input [IN]             Clock input port number
 * \param freq_khz [OUT]               frequency in KHz, freq_khz < 8 => clock
 * input qualifier is disabled
 * \param ratio [OUT]                  A ratio the freq_khz was mutiplied
 * with.e.g. 66/64. I order to allow rational values for the frequency
 * \param use_internal_clock_src [OUT] An internally provided clock is used as
 * source, if TRUE
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_frequency_ratio_get(const mesa_inst_t inst,
                                             const uint8_t     clock_input,
                                             uint32_t *const   freq_khz,
                                             mesa_clock_ratio_t *const ratio,
                                             mesa_bool_t
                                                 *const use_internal_clock_src)
    CAP(CLOCK);

/**
 * \brief Set Clock output frequency.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param freq_khz [IN]     frequency in KHz.
 *                          freq_khz = 0 disables the clock
 * \param par_freq_khz [IN] parallel frequency in KHz. With parallel frequency
 * the clock output of the DF2F for the parallel data towards the core is ment.
 *                          Maximum parallel frequency is 400 MHz, minimum
 * parallel frequency is 31.25 MHz. Higher frequencies provide better jitter
 * performance. par_freq_khz = 0 disables the clock
 *
 *                          Note: Only one of the clocks can be active. Either
 * freq_khz or par_freq_khz must be 0. For selected frequencies there is a
 * possibility that both clocks can be used. The possible combinations can be
 * looked up in DS1009-DPLL-Freq-Calc.xlsm and implemented on request.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_frequency_set(const mesa_inst_t inst,
                                        const uint8_t     clock_output,
                                        const uint32_t    freq_khz,
                                        const uint32_t par_freq_khz) CAP(CLOCK);

/**
 * \brief Get Clock output frequency.
 * \param inst [IN]          Handle to an API instance.
 * \param clock_output [IN]  Clock output port number
 * \param freq_khz [OUT]     frequency in KHz, freq_khz = 0, clock is disbaled
 * \param par_freq_khz [OUT] parallel frequency in KHz, par_freq_khz = 0, clock
 * is disbaled
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_frequency_get(const mesa_inst_t inst,
                                        const uint8_t     clock_output,
                                        uint32_t *const   freq_khz,
                                        uint32_t *const   par_freq_khz)
    CAP(CLOCK);

/**
 * \brief Set Clock output frequency.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param freq_khz [IN]     frequency in KHz.
 *                          freq_khz = 0 disables the clock
 * \param par_freq_khz [IN] parallel frequency in KHz. With parallel frequency
 * the clock output of the DF2F for the parallel data towards the core is ment.
 *                          Maximum parallel frequency is 400 MHz, minimum
 * parallel frequency is 31.25 MHz. Higher frequencies provide better jitter
 * performance. par_freq_khz = 0 disables the clock
 *
 *                          Note: Only one of the clocks can be active. Either
 * freq_khz or par_freq_khz must be 0. For selected frequencies there is a
 * possibility that both clocks can be used. The possible combinations can be
 * looked up in DS1009-DPLL-Freq-Calc.xlsm and implemented on request.
 * \param ratio [IN]        A ratio the freq_khz will be mutiplied with.e.g.
 * 66/64. I order to allow rational values for the frequency
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_frequency_ratio_set(const mesa_inst_t inst,
                                              const uint8_t     clock_output,
                                              const uint32_t    freq_khz,
                                              const uint32_t    par_freq_khz,
                                              const mesa_clock_ratio_t
                                                  *const ratio) CAP(CLOCK);

/**
 * \brief Get Clock output frequency.
 * \param inst [IN]          Handle to an API instance.
 * \param clock_output [IN]  Clock output port number
 * \param freq_khz [OUT]     frequency in KHz, freq_khz = 0, clock is disbaled
 * \param par_freq_khz [OUT] parallel frequency in KHz, par_freq_khz = 0, clock
 * is disbaled
 * \param ratio [OUT]        A ratio the freq_khz was mutiplied with.e.g. 66/64.
 * I order to allow rational values for the frequency
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_frequency_ratio_get(const mesa_inst_t inst,
                                              const uint8_t     clock_output,
                                              uint32_t *const   freq_khz,
                                              uint32_t *const   par_freq_khz,
                                              mesa_clock_ratio_t *const ratio)
    CAP(CLOCK);

/**
 * \brief Set Clock output Voltage level.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param level_mv [IN]     Output Voltage in mV range [300..1275], 25 mV steps
 * [Output level of es6514 is limited due to bug in a coil in the OB]
 *
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_level_set(const mesa_inst_t inst,
                                    const uint8_t     clock_output,
                                    const uint16_t    level_mv) CAP(CLOCK);

/**
 * \brief Get Clock output Voltage level.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param level_mv [OUT]    Output Voltage in mV range [300..1275], 25 mV steps
 *
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_level_get(const mesa_inst_t inst,
                                    const uint8_t     clock_output,
                                    uint16_t *const   level_mv) CAP(CLOCK);

/**
 * \brief Set Clock output selector.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param input [IN]     input selector.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_selector_set(const mesa_inst_t inst,
                                       const uint8_t     clock_output,
                                       const mesa_clock_input_selector_t
                                           *const input) CAP(CLOCK);

/**
 * \brief Get Clock output selector.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_output [IN] Clock output port number
 * \param input [OUT]       input selector.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_output_selector_get(const mesa_inst_t inst,
                                       const uint8_t     clock_output,
                                       mesa_clock_input_selector_t *const input)
    CAP(CLOCK);

/**
 * \brief Set Clock input alarm configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Alarm enable for various qualifier arlarms and LOS
 * active level
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_alarm_conf_set(const mesa_inst_t inst,
                                        const uint8_t     clock_input,
                                        const mesa_clock_input_conf_t
                                            *const conf) CAP(CLOCK);

/**
 * \brief Get Clock input alarm configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [OUT]        Alarm enable for various qualifier arlarms and LOS
 * active level
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_alarm_conf_get(const mesa_inst_t inst,
                                        const uint8_t     clock_input,
                                        mesa_clock_input_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Set Clock input Coarse Frequency Monitor configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Coarse Frequency Monitor Configurations
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_cfm_conf_set(const mesa_inst_t inst,
                                      const uint8_t     clock_input,
                                      const mesa_clock_cfm_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Get Clock input Coarse Frequency Monitor configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Coarse Frequency Monitor Configurations
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_cfm_conf_get(const mesa_inst_t            inst,
                                      const uint8_t                clock_input,
                                      mesa_clock_cfm_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Set Clock input Precise Frequency Monitor configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Precise Frequency Monitor Configurations
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_pfm_conf_set(const mesa_inst_t inst,
                                      const uint8_t     clock_input,
                                      const mesa_clock_pfm_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Get Clock input Precise Frequency Monitor configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Precise Frequency Monitor Configurations
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_pfm_conf_get(const mesa_inst_t            inst,
                                      const uint8_t                clock_input,
                                      mesa_clock_pfm_conf_t *const conf)
    CAP(CLOCK);
/**
 * \brief Set Clock input guard soak timer configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [IN]         Guard Soak Timer Configurations
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_gst_conf_set(const mesa_inst_t inst,
                                      const uint8_t     clock_input,
                                      const mesa_clock_gst_conf_t *const conf)
    CAP(CLOCK);

/**
 * \brief Get Clock input guard soak timer configuration.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param conf [OUT]        Guard Soak Timer Configurations
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_gst_conf_get(const mesa_inst_t            inst,
                                      const uint8_t                clock_input,
                                      mesa_clock_gst_conf_t *const conf)
    CAP(CLOCK);

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
mesa_rc mesa_clock_selector_state_get(const mesa_inst_t            inst,
                                      const mesa_clock_dpll_inst_t dpll,
                                      mesa_clock_selector_state_t
                                          *const     selector_state,
                                      uint8_t *const clock_input) CAP(CLOCK);

/**
 * \brief get Clock pll state.
 * \param inst [IN]         Handle to an API instance.
 * \param dpll [IN]         DPLL instance number [0..x].
 * \param pll_state [OUT]   pll state
 *
 * \return Return code.
 */
mesa_rc mesa_clock_dpll_state_get(const mesa_inst_t              inst,
                                  const mesa_clock_dpll_inst_t   dpll,
                                  mesa_clock_dpll_state_t *const pll_state)
    CAP(CLOCK);

/**
 * \brief get Clock frequency offset stored in ho stack
 * \param inst [IN]       Handle to an API instance.
 * \param dpll [IN]       DPLL instance number [0..x].
 * \param offset [OUT]    Current frequency offset stored in the holdover stack
 * in units of scaled ppb (parts per billion) i.e. ppb*2**-16.
 *
 * \return Return code.
 */
mesa_rc mesa_clock_ho_stack_frequency_offset_get(const mesa_inst_t inst,
                                                 const mesa_clock_dpll_inst_t
                                                                dpll,
                                                 int64_t *const offset)
    CAP(CLOCK);

/**
 * \brief get Clock input state.
 * \param inst [IN]         Handle to an API instance.
 * \param clock_input [IN]  Clock input port number
 * \param input_state [OUT] input state
 *
 * \return Return code.
 */
mesa_rc mesa_clock_input_state_get(const mesa_inst_t               inst,
                                   const uint8_t                   clock_input,
                                   mesa_clock_input_state_t *const input_state)
    CAP(CLOCK);

// ***************************************************************************
//
//  Event (interrupt) handling API
//
// ***************************************************************************

/**
 * \brief Define event (interrupt) types related to the Vitesse Synce Clock
 *inputs.
 **/
#define MESA_CLOCK_INPUT_LOS_EV (1 << 0) /**< External Loss Of Signal event */
#define MESA_CLOCK_INPUT_PFM_EV (1 << 1) /**< Precise frequency monitor event */
#define MESA_CLOCK_INPUT_CFM_EV (1 << 2) /**< Coarse frequency monitor event */
#define MESA_CLOCK_INPUT_SCM_EV (1 << 3) /**< Single Cycle monitor event */
#define MESA_CLOCK_INPUT_GST_EV (1 << 4) /**< Guard Soak timer event */
#define MESA_CLOCK_INPUT_LOL_EV (1 << 5) /**< Loss of Lock event */
typedef uint32_t mesa_clock_input_event_type_t; /**< Int events: Single event or
                                                   'OR' multiple events above */

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
mesa_rc mesa_clock_input_event_poll(const mesa_inst_t inst,
                                    const uint8_t     clock_input,
                                    mesa_clock_input_event_type_t *const ev_mask)
    CAP(CLOCK);

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
mesa_rc mesa_clock_input_event_enable(const mesa_inst_t inst,
                                      const uint8_t     clock_input,
                                      const mesa_clock_input_event_type_t
                                                        ev_mask,
                                      const mesa_bool_t enable) CAP(CLOCK);

/**
 * \brief Define event (interrupt) types related to the Vitesse Synce Clock
 *dpll's.
 *
 **/
//    MESA_CLOCK_DPLL_FREQ_LOCK_EV =      (1 << 0), /**< Loss Of Frequency lock
//    event */ MESA_CLOCK_DPLL_PH_LOCK_EV   =      (1 << 1), /**< Loss Of Phase
//    lock event */ MESA_CLOCK_DPLL_LOSX         =      (1 << 2), /**< PLL the
//    currently selected reference input fails event */ MESA_CLOCK_DPLL_LOL = (1
//    << 3), /**< PLL loss of lock event */
#define MESA_CLOCK_DPLL_STATE_CHANGE_EV                                        \
    (1 << 0) /**< State change event in EEC FSM */
typedef uint32_t mesa_clock_dpll_event_type_t; /**< Int events: Currently only
                                                  Single event */

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
mesa_rc mesa_clock_dpll_event_poll(const mesa_inst_t                   inst,
                                   const mesa_clock_dpll_inst_t        dpll,
                                   mesa_clock_dpll_event_type_t *const ev_mask)
    CAP(CLOCK);

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
mesa_rc mesa_clock_dpll_event_enable(const mesa_inst_t                  inst,
                                     const mesa_clock_dpll_inst_t       dpll,
                                     const mesa_clock_dpll_event_type_t ev_mask,
                                     const mesa_bool_t enable) CAP(CLOCK);

#include <microchip/ethernet/hdr_end.h> // ALL INCLUDE ABOVE THIS LINE
#endif                                  // _MICROCHIP_ETHERNET_SWITCH_API_CLOCK_
