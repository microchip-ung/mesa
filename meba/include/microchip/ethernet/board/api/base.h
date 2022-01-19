// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_BOARD_BASE_H_
#define _MICROCHIP_ETHERNET_BOARD_BASE_H_

#include <stdint.h>

#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// MEBA - Microsemi Ethernet Board API
//
// This API defines the board-level code implementing functionality that differ
// depending on board characteristics.
//
// The areas currently defined by this API is:
//   - Board and port capabilities
//   - Switch API data
//     - Port map and port count
//     - Switch target
//   - Board initialization
//   - SFP support
//   - Fan control support
//   - Temperature sensor support
//   - LED (and LED dimming) support
//   - Interrupt support
//
// The switch application use the library to gain knowledge of the
// board characteristics, and to perform board-specific
// operations. Should a board not have support for a specific
// functional group, the entire API can be omitted from the exposed
// interface.
//
// A MEBA implementation will typically be implemented as a shared
// library, which only expose the `meba_initialize()` symbol (please
// consult the meba_initialize_t documentation for more
// information).
//
// The embodying system will call this function after loading a
// library, and provide a set of system interface functions. The MEBA
// library should then allocate, initialize and return the MEBA
// instance handle.
//
// The returned MEBA instance handle is provided to all (other) MEBA
// API's as the first parameter.
//
// See MEBA_LIST_OF_API_CALLS for the entrypoints which the board
// API can expose.
//
// Of the above list, the following API's are considered mandatory:
// - meba_capability_t
// - meba_port_entry_get_t

// De-allocate the board instance and any other resources. Where required, the
// board hardware may also be brought to a given state.
typedef void (*meba_deinitialize_t)(struct meba_inst *inst);

// Retreive the board instance capabilities..
typedef uint32_t (*meba_capability_t)(struct meba_inst *inst, int cap);

// Retreive the port map, one port at a time
typedef mesa_rc (*meba_port_entry_get_t)(struct meba_inst *inst,
                                         mesa_port_no_t port_no,
                                         meba_port_entry_t *entry);

// Perform a reset operation, of a given type (meba_reset_point_t)
typedef mesa_rc (*meba_reset_t)(struct meba_inst *inst,
                                meba_reset_point_t reset);

// Sensor support //////////////////////////////////////////////////////////////

// Retrieve the value of a sensor.
// type     [IN]  The type of the sensor.
// index    [IN]  The index (number) of the sensor.
// value    [OUT] The output value of the sensor.
//
// The number of instances depend on the sensor type. The MESA_CAP
// macro can be used to determine the instance count:
//
// MEBA_SENSOR_PORT_TEMP:  MESA_CAP(MEBA_CAP_BOARD_PORT_COUNT)
// MEBA_SENSOR_BOARD_TEMP: MESA_CAP(MEBA_CAP_TEMP_SENSORS)
typedef mesa_rc (*meba_sensor_get_t)(struct meba_inst *inst,
                                     meba_sensor_t type,
                                     int index,
                                     int *value);

// Perform a port I2C transfer (for a SFP register).
// port_no     [IN] The port number.
// write       [IN] TRUE if this is a write, FALSE indicates READ.
// i2c_addr    [IN] The I2C address of the switch port device (SFP).
// addr        [IN] The SFP register address.
// data        [IN/OUT] Data pointer for the transfer.
// cnt         [IN] The length of the transfer (data).
// word_access [IN] Whether this is a WORD or BYTE transfer.
typedef mesa_rc (*meba_sfp_i2c_xfer_t)(struct meba_inst *inst,
                                       mesa_port_no_t port_no,
                                       mesa_bool_t write,
                                       uint8_t i2c_addr,
                                       uint8_t addr,
                                       uint8_t *data,
                                       uint8_t cnt,
                                       mesa_bool_t word_access);

// Retreive the SFP insertion state for all ports.
// present [OUT] The port list will reflect which ports have a SFP detected.
typedef mesa_rc (*meba_sfp_insertion_status_get_t)(struct meba_inst *inst,
                                                   mesa_port_list_t *present);

// Retreive the SFP status state for a port.
// port_no [IN] The port number to retreive status for.
// status  [OUT] The status retreived.
typedef mesa_rc (*meba_sfp_status_get_t)(struct meba_inst *inst,
                                         mesa_port_no_t port_no,
                                         meba_sfp_status_t *status);

// Control the administrative state of a port.
// port_no   [IN] The port number to configure.
// state     [IN] The new port state
typedef mesa_rc (*meba_port_admin_state_set_t)(
        struct meba_inst *inst,
        mesa_port_no_t port_no,
        const meba_port_admin_state_t *state);

// Update a status LED according to provided data.
// type      [IN] The LED type.
// color     [IN] The LED color to set.
typedef mesa_rc (*meba_status_led_set_t)(struct meba_inst *inst,
                                         meba_led_type_t type,
                                         meba_led_color_t color);

// Update a port LED according to provided data.
// port_no   [IN] The port number to update.
// status    [IN] The port status.
// counters  [IN] The port counters.
// state     [IN] The port administrative state.
typedef mesa_rc (*meba_port_led_update_t)(struct meba_inst *inst,
                                          mesa_port_no_t port_no,
                                          const mesa_port_status_t *status,
                                          const mesa_port_counters_t *counters,
                                          const meba_port_admin_state_t *state);

// Change port LED mode.
// If meba_capability(inst, MEBA_CAP_LED_MODES) is zero or 1, calling this API
// is unecessary.
//
// mode [IN] The desired port LED mode.
//           This must be < meba_capability(inst, MEBA_CAP_LED_MODES)
typedef mesa_rc (*meba_led_mode_set_t)(struct meba_inst *inst, uint32_t mode);

// Set LED intensity. This applies to all PHY LED's controllable by the host
// system.
// intensity [IN] The PHY LED intensity (in percent).
typedef mesa_rc (*meba_led_intensity_set_t)(struct meba_inst *inst,
                                            mesa_phy_led_intensity intensity);

typedef mesa_rc (*meba_fan_param_get_t)(struct meba_inst *inst,
                                        meba_fan_param_t *param);
typedef mesa_rc (*meba_fan_conf_get_t)(struct meba_inst *inst,
                                       mesa_fan_conf_t *conf);

// Get IRQ status (active IRQs), mask active IRQs. This acts as a possible
// override for mesa_irq_status_get_and_mask().
//
// status  [OUT] A bitmask of currently active IRQs.
typedef mesa_rc (*meba_irq_status_get_and_mask_t)(struct meba_inst *inst,
                                                  mesa_irq_status_t *status);

// Control a specific IRQ
// chip_irq        [IN] Chip interrupt.
// enable          [IN] Enable or disable IRQ.
typedef mesa_rc (*meba_irq_enable_t)(struct meba_inst *inst,
                                     mesa_irq_t irq,
                                     mesa_bool_t enable);

// Handle low-level chip interrupt, generating generic, application-level
// events.
//
// chip_irq        [IN] Chip interrupt which triggered
// signal_notifier [IN] Function to deliver decoded interrupts to
typedef mesa_rc (*meba_irq_handler_t)(struct meba_inst *inst,
                                      mesa_irq_t chip_irq,
                                      meba_event_signal_t signal_notifier);

// Defines whether MEBA wants to control IRQ
// chip_irq        [IN] Chip interrupt handled by MEBA?
typedef mesa_rc (*meba_irq_requested_t)(struct meba_inst *inst,
                                        mesa_irq_t chip_irq);

// Enable individual interrupt events. When an event triggers, the individual
// source gets disabled.
typedef mesa_rc (*meba_event_enable_t)(struct meba_inst *inst,
                                       meba_event_t event,
                                       mesa_bool_t enable);

// Get RS422 HW configuration configuration
// conf [OUT] The RS422 config
typedef mesa_rc (*meba_ptp_rs422_conf_get_t)(struct meba_inst *inst,
                                             meba_ptp_rs422_conf_t *conf);

// Get the GPIO information that is board specific for this GPIO functionality
typedef mesa_rc (*meba_gpio_func_info_get_t)(struct meba_inst *inst,
                                             mesa_gpio_func_t gpio_func,  mesa_gpio_func_info_t *info);

// Get the Serdes tap value for this port on this board
typedef mesa_rc (*meba_serdes_tap_get_t)(struct meba_inst *inst,
                                         mesa_port_no_t port_no, mesa_port_speed_t speed, mesa_port_serdes_tap_enum_t tap, uint32_t *value);

typedef mesa_rc (*meba_ptp_external_io_conf_get_t)(meba_inst_t inst, uint32_t io_pin,
                                                   meba_ptp_io_cap_t *const board_assignment, meba_event_t *const source_id);

typedef struct {
    meba_deinitialize_t             meba_deinitialize;
    meba_capability_t               meba_capability;
    meba_port_entry_get_t           meba_port_entry_get;
    meba_reset_t                    meba_reset;
    meba_sensor_get_t               meba_sensor_get;
    meba_sfp_i2c_xfer_t             meba_sfp_i2c_xfer;
    meba_sfp_insertion_status_get_t meba_sfp_insertion_status_get;
    meba_sfp_status_get_t           meba_sfp_status_get;
    meba_port_admin_state_set_t     meba_port_admin_state_set;
    meba_status_led_set_t           meba_status_led_set;
    meba_port_led_update_t          meba_port_led_update;
    meba_led_mode_set_t             meba_led_mode_set;
    meba_led_intensity_set_t        meba_led_intensity_set;
    meba_fan_param_get_t            meba_fan_param_get;
    meba_fan_conf_get_t             meba_fan_conf_get;
    meba_irq_status_get_and_mask_t  meba_irq_status_get_and_mask;
    meba_irq_enable_t               meba_irq_enable;
    meba_irq_handler_t              meba_irq_handler;
    meba_irq_requested_t            meba_irq_requested;
    meba_event_enable_t             meba_event_enable;
    meba_ptp_rs422_conf_get_t       meba_ptp_rs422_conf_get;
    meba_gpio_func_info_get_t       meba_gpio_func_info_get;
    meba_serdes_tap_get_t           meba_serdes_tap_get;
    meba_ptp_external_io_conf_get_t meba_ptp_external_io_conf_get;
} meba_api_t;


// Full list of MEBA entrypoints. This allows users of this API to apply the
// https://en.wikipedia.org/wiki/X_Macro pattern, if they wish to create wrapper
// functions.
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
    X(meba_ptp_rs422_conf_get)       \
    X(meba_ptp_external_io_conf_get)

#include <microchip/ethernet/board/api/hdr_end.h>
#endif  // _MICROCHIP_ETHERNET_BOARD_BASE_H_
