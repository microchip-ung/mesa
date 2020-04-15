/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef _MSCC_ETHERNET_BOARD_BASE_H_
#define _MSCC_ETHERNET_BOARD_BASE_H_

#include <stdint.h>

#include <mscc/ethernet/switch/api.h>
#include <mscc/ethernet/board/api/types.h>

/**
 * \file
 * \brief MEBA - Microsemi Ethernet Board API
 *
 * \details This API defines the board-level code implementing
 * functionality that differ depending on board characteristics.
 *
 * The areas currently defined by this API is:
 *   - Board and port capabilities
 *   - Switch API data
 *     - Port map and port count
 *     - Switch target
 *   - Board initialization
 *   - SFP support
 *   - Fan control support
 *   - Temperature sensor support
 *   - LED (and LED dimming) support
 *   - Interrupt support
 *
 * The switch application use the library to gain knowledge of the
 * board characteristics, and to perform board-specific
 * operations. Should a board not have support for a specific
 * functional group, the entire API can be omitted from the exposed
 * interface.
 *
 * A MEBA implementation will typically be implemented as a shared
 * library, which only expose the `meba_initialize()` symbol (please
 * consult the meba_initialize_t documentation for more
 * information).
 *
 * The embodying system will call this function after loading a
 * library, and provide a set of system interface functions. The MEBA
 * library should then allocate, initialize and return the MEBA
 * instance handle.
 *
 * The returned MEBA instance handle is provided to all (other) MEBA
 * API's as the first parameter.
 *
 * See \ref MEBA_LIST_OF_API_CALLS for the entrypoints which the board
 * API can expose.
 *
 * Of the above list, the following API's are considered mandatory:
 *
 * - \ref meba_capability_t
 * - \ref meba_port_entry_get_t
 *
 */

/**
 * \brief De-initialize board.
 *
 * \param inst [IN] The board instance.
 *
 * The function must de-allocate the board instance and any other
 * resources. Where required, the board hardware may also be brought
 * to a given state.
 *
 * \return none
 **/
typedef void (*meba_deinitialize_t)(meba_inst_t inst);

/**
 * \brief Retreive the board instance capabilities..
 *
 * \param inst [IN] The board instance.
 * \param cap  [IN] The capability to query for.
 *
 * \return the capability value.
 **/
typedef uint32_t (*meba_capability_t)(meba_inst_t inst, int cap);

/**
 * \brief Retreive the port map.
 *
 * \param inst        [IN] The board instance.
 * \param port_no     [IN] The port number.
 * \param port_entry  [OUT] The port entry.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_port_entry_get_t)(meba_inst_t inst,
                                         mesa_port_no_t port_no,
                                         meba_port_entry_t *entry);

/**
 * \brief Perform a reset operation.
 *
 * \param inst  [IN] The board instance.
 * \param reset [IN] The type of reset to perform

 * \return Return code.
 **/
typedef mesa_rc (*meba_reset_t)(meba_inst_t inst,
                                meba_reset_point_t reset);

/*
 * Sensor support
 */

/**
 * \brief Retrieve the value of a sensor.
 *
 * \param inst     [IN] The board instance.
 * \param type     [IN] The type of the sensor.
 * \param index    [IN] The index (number) of the sensor.
 * \param value    [OUT] The output value of the sensor.
 *
 * \return Return code. value is only defined in case of SUCCESS.
 *
 * The number of instances depend on the sensor type. The MESA_CAP
 * macro can be used to determine the instance count:
 *
 * MEBA_SENSOR_PORT_TEMP:  MESA_CAP(MEBA_CAP_BOARD_PORT_COUNT)
 * MEBA_SENSOR_BOARD_TEMP: MESA_CAP(MEBA_CAP_TEMP_SENSORS)
 *
 **/
typedef mesa_rc (*meba_sensor_get_t)(meba_inst_t inst,
                                     meba_sensor_t type,
                                     int index,
                                     int *value);

/**
 * \brief Perform a port I2C transfer (for a SFP register).
 *
 * \param inst        [IN] The board instance.
 * \param port_no     [IN] The port number.
 * \param write       [IN] TRUE if this is a write, FALSE indicates READ.
 * \param i2c_addr    [IN] The I2C address of the switch port device (SFP).
 * \param addr        [IN] The SFP register address.
 * \param data        [IN/OUT] Data pointer for the transfer.
 * \param cnt         [IN] The length of the transfer (data).
 * \param word_access [IN] Whether this is a WORD or BYTE transfer.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_sfp_i2c_xfer_t)(meba_inst_t inst,
                                       mesa_port_no_t port_no,
                                       mesa_bool_t write,
                                       uint8_t i2c_addr,
                                       uint8_t addr,
                                       uint8_t *data,
                                       uint8_t cnt,
                                       mesa_bool_t word_access);

/**
 * \brief Retreive the SFP insertion state for all ports.
 *
 * \param inst    [IN] The board instance.
 * \param present [OUT] The port list will reflect which ports have a SFP detected.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_sfp_insertion_status_get_t)(meba_inst_t inst,
                                                   mesa_port_list_t *present);

/**
 * \brief Retreive the SFP status state for a port.
 *
 * \param inst    [IN] The board instance.
 * \param port_no [IN] The port number to retreive status for.
 * \param status  [OUT] The status retreived.
 *
 * \return Return code. status is only defined in case of SUCCESS.
 **/
typedef mesa_rc (*meba_sfp_status_get_t)(meba_inst_t inst,
                                         mesa_port_no_t port_no,
                                         meba_sfp_status_t *status);

/**
 * \brief Control the administrative state of a port.
 *
 * \param inst      [IN] The board instance.
 * \param port_no   [IN] The port number to configure.
 * \param state     [IN] The new port state
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_port_admin_state_set_t)(meba_inst_t inst,
                                               mesa_port_no_t port_no,
                                               const meba_port_admin_state_t *state);

/**
 * \brief Update a status LED according to provided data.
 *
 * \param inst      [IN] The board instance.
 * \param type      [IN] The LED type.
 * \param color     [IN] The LED color to set.
 *
 * \return Returns MESA_RC_ERROR if any of type or color is unsupported.
 **/
typedef mesa_rc (*meba_status_led_set_t)(meba_inst_t inst,
                                         meba_led_type_t type,
                                         meba_led_color_t color);

/**
 * \brief Update a port LED according to provided data.
 *
 * \param inst      [IN] The board instance.
 * \param port_no   [IN] The port number to update.
 * \param status    [IN] The port status.
 * \param counters  [IN] The port counters.
 * \param state     [IN] The port administrative state.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_port_led_update_t)(meba_inst_t inst,
                                          mesa_port_no_t port_no,
                                          const mesa_port_status_t *status,
                                          const mesa_port_counters_t *counters,
                                          const meba_port_admin_state_t *state);

/**
 * \brief Change port LED mode.
 *
 * \param inst [IN] The board instance.
 * \param mode [IN] The desired port LED mode. This must be < meba_capability(inst, MEBA_CAP_LED_MODES)
 *
 * If meba_capability(inst, MEBA_CAP_LED_MODES) is zero or 1, calling this API is unecessary.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_led_mode_set_t)(meba_inst_t inst, uint32_t mode);

/**
 * \brief Set LED intensity. This applies to all PHY LED's
 * controllable by the host system.
 *
 * \param inst      [IN] The board instance.
 * \param intensity [IN] The PHY LED intensity (in percent).
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_led_intensity_set_t)(meba_inst_t inst,
                                            mesa_phy_led_intensity intensity);

/**
 * \brief Get FAN parameters
 *
 * \param inst [IN] The board instance.
 * \param conf [OUT] The FAN parameters
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_fan_param_get_t)(meba_inst_t inst,
                                        meba_fan_param_t *param);

/**
 * \brief Get FAN configuration
 *
 * \param inst [IN] The board instance.
 * \param conf [OUT] The FAN config
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_fan_conf_get_t)(meba_inst_t inst,
                                       mesa_fan_conf_t *conf);

/**
 * \brief Get IRQ status (active IRQs), mask active IRQs. This
 * acts as a possible override for mesa_irq_status_get_and_mask().
 *
 * \param inst            [IN] The board instance.
 * \param status          [OUT] A bitmask of currently active IRQs.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_irq_status_get_and_mask_t)(meba_inst_t inst,
                                                  mesa_irq_status_t *status);

/**
 * \brief Control a specific IRQ
 *
 * \param inst            [IN] The board instance.
 * \param chip_irq        [IN] Chip interrupt.
 * \param enable          [IN] Enable or disable IRQ.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_irq_enable_t)(meba_inst_t inst,
                                     mesa_irq_t irq,
                                     mesa_bool_t enable);

/**
 * \brief Handle low-level chip interrupt, generating
 * generic, application-level events.
 *
 * \param inst            [IN] The board instance.
 * \param chip_irq        [IN] Chip interrupt which triggered
 * \param signal_notifier [IN] Function to deliver decoded interrupts to
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_irq_handler_t)(meba_inst_t inst,
                                      mesa_irq_t chip_irq,
                                      meba_event_signal_t signal_notifier);

/**
 * \brief Defines whether MEBA wants to control IRQ
 *
 * \param inst            [IN] The board instance.
 * \param chip_irq        [IN] Chip interrupt handled by MEBA?
 *
 * \return Returns MEBA_RC_OK if MEBA wants to control chip_irq
 **/
typedef mesa_rc (*meba_irq_requested_t)(meba_inst_t inst,
                                        mesa_irq_t chip_irq);

/**
 * \brief Enable individual interrupt events.
 *
 * When an event triggers, the individual source gets disabled.
 *
 * \param inst       [IN] The board instance.
 * \param irq        [IN] The interrupt source to control
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_event_enable_t)(meba_inst_t inst,
                                       meba_event_t event,
                                       mesa_bool_t enable);

/**
 * \brief Get RS422 HW configuration configuration
 *
 * \param inst [IN] The board instance.
 * \param conf [OUT] The RS422 config
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_ptp_rs422_conf_get_t)(meba_inst_t inst,
                                       meba_ptp_rs422_conf_t *conf);

/**
 * \brief Full list of MEBA entrypoints
 *
 * To keep the meba-wrap in same repository as the meba implementation
 * we make use of the https://en.wikipedia.org/wiki/X_Macro pattern.
 */
#define MEBA_LIST_OF_API_CALLS       \
    X(meba_deinitialize)             \
    X(meba_capability)               \
    X(meba_port_entry_get)           \
    X(meba_reset)                    \
    X(meba_sensor_get)               \
    X(meba_sfp_i2c_xfer)             \
    X(meba_sfp_insertion_status_get) \
    X(meba_sfp_status_get)           \
    X(meba_port_admin_state_set)     \
    X(meba_status_led_set)           \
    X(meba_port_led_update)          \
    X(meba_led_mode_set)             \
    X(meba_led_intensity_set)        \
    X(meba_fan_param_get)            \
    X(meba_fan_conf_get)             \
    X(meba_irq_status_get_and_mask)  \
    X(meba_irq_enable)               \
    X(meba_irq_handler)              \
    X(meba_irq_requested)            \
    X(meba_event_enable)             \
    X(meba_ptp_rs422_conf_get)

/** \brief Board functions struct */
typedef struct {
/**
 *  A macro X is created for expanding the MEBA_LIST_OF_API_CALLS macro above as:
 * 
 *    meba_deinitialize_t meba_deinitialize;
 *    meba_capability_t meba_capability;
 * 
 *    etc.
 *
 *    In this way the struct of function pointers is filled out below:
 */
#define X(name) name ## _t name;
    MEBA_LIST_OF_API_CALLS
#undef X
} meba_api_t;


#endif  // _MSCC_ETHERNET_BOARD_BASE_H_
