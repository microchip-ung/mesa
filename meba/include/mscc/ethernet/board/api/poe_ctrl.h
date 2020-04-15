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

#ifndef _MSCC_ETHERNET_BOARD_POE_CTRL_H_
#define _MSCC_ETHERNET_BOARD_POE_CTRL_H_

#include <mscc/ethernet/board/api/types.h>
#include <mscc/ethernet/switch/api/types.h>


/**
 * \file
 * \brief PoE Controller API
 *
 * \details This API defines how to interact with one of the PoE controller
 * supported by the MEBA Layer.
 *
 * The MEBA library can contain drivers for many different controllers. Each
 * controller must support to be instantiated several times, and the controller
 * implementation is not allowed to have any board assumptions (if board
 * information is needed then it must be passed as private date by the 'poe.h'
 * API when it create the instances).
 *
 * The API supports a flexible topology which allow:
 * - A PoE controller per port. In this case there will be many instances of
 *   this API.
 * - A PoE controller to handle a group of ports.
 * - A single PoE controller to handle all the ports on the board.
 *
 * If a group of ports is located at the same address, then they are considered
 * to be _owned_ by a single controller. This is regardless of if the controller
 * can do the power management or not.
 *
 * This API is always instantiated by the 'poe.h' API (never by the application
 * directly). The 'poe.h' API will create the number of instances needed, and
 * will choose the driver matching the HW. When the 'poe.h' API create the
 * instances, it will also update all the meta-data in \ref
 * meba_poe_ctrl_inst_t.
 *
 * A given controller instance, only have knowledge about the ports belonging
 * to the controller. This means that to apply configuration or query status on
 * for a specific port, you will have to go through the controller owning the
 * port.
 *
 * The 'poe.h' API contains wrapper functions which will search the right
 * controller and forward the request.
 *
 */

/**
 * \brief PoE Controller capabilities (bitmask).
 * \details The capability allow the application to query the capabilities of a
 * given board, and adapt the matching functionality. */
typedef enum {
    /** Signals if the controller performs the power managements. */
    MEBA_POE_CTRL_CAP_POWER_MANAGEMENT = 0x1,
    /** Signals if there is a hw signal to turn on/off the poe controller. */
    MEBA_POE_CTRL_CAP_HW_ENABLE = 0x2,
    /** Signals if the controller supports poe legacy PD detection. */
    MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION = 0x4,
    /** Signals that the controller can continue to deliver power even
        during system software reset */
    MEBA_POE_CTRL_UNINTERRUPTABLE_POWER = 0X8,
} meba_poe_ctrl_cap_t;

/**
 * \brief PoE Controller Port capabilities (bitmask).
 * \details The capability allow the application to query the capabilities of a
 * given board, and adapt the matching functionality. */
typedef enum {
    /** Port supports PoE. */
    MEBA_POE_PORT_CAP_POE = 0x1,

    /** 802.3af - Class 0-3, 2 pair */
    MEBA_POE_PORT_CAP_TYPE_1 = 0x2,

    /** 802.3at - Class 0-4, 2 pair */
    MEBA_POE_PORT_CAP_TYPE_2 = 0x4,

    /** 802.3bt - Class 0-6, 2 or 4 pair */
    MEBA_POE_PORT_CAP_TYPE_3 = 0x8,

    /** 802.3bt - Class 0-8+, 2 or 4-pair */
    MEBA_POE_PORT_CAP_TYPE_4 = 0x10,

    /** Port can be forced to emit power. */
    MEBA_POE_PORT_CAP_FORCE_ON = 0x20,

    /** The pair used for PoE is configurable */
    MEBA_POE_PORT_CAP_2PAIR_CONTROL = 0x40,

    /** Port supports PoE over 4-pairs. */
    MEBA_POE_PORT_CAP_4PAIR = 0x80,

    /** Allow to set power budget based on current consumption (triggered by
     * lldp). */
    MEBA_POE_PORT_CAP_AUTOCLASS = 0x100,
} meba_poe_port_cap_t;

/** \brief State of the PoE chip identification. */
typedef enum {
    /**  PoE chipset detection in progress. */
    MEBA_POE_CHIPSET_DETECTION,

    /** Could not determine chipset state. */
    MEBA_POE_NO_CHIPSET_FOUND,

    /** PoE controller firmware is upgrading. */
    MEBA_POE_FIRMWARE_UPGRADE,

    /** Succesful detection of PoE chip. */
    MEBA_POE_CHIPSET_FOUND,
} meba_poe_chip_state_t;

/** \brief PoE Port status as defined by 802.3. */
typedef enum {
    /** Disabled. */
    MEBA_POE_PORT_STATE_DISABLED = 0,

    /** Searching. */
    MEBA_POE_PORT_STATE_SEARCHING = 1,

    /** Delivering power */
    MEBA_POE_PORT_STATE_DELIVERING_POWER = 2,

    /** Test */
    MEBA_POE_PORT_STATE_TEST = 4, // See rfc3621

    /** Fault */
    MEBA_POE_PORT_STATE_FAULT = 3, // See rfc3621

    /** Other fault */
    MEBA_POE_PORT_STATE_OTHER_FAULT = 5,

    /** Mode not supported. */
    MEBA_POE_PORT_STATE_NOT_SUPPORTED = 6,
} meba_poe_port_state_t;

/** \brief PoE Port PD class. The value -1 means class value invalid */
typedef int32_t meba_poe_port_pd_class_t;

/** \brief PoE Port PD structure */
typedef enum {
    MEBA_POE_PORT_PD_STRUCTURE_NOT_PERFORMED,
    MEBA_POE_PORT_PD_STRUCTURE_OPEN,
    MEBA_POE_PORT_PD_STRUCTURE_INVALID_SIGNATURE,
    MEBA_POE_PORT_PD_STRUCTURE_4P_SINGLE_IEEE,
    MEBA_POE_PORT_PD_STRUCTURE_4P_SINGLE_LEGACY,
    MEBA_POE_PORT_PD_STRUCTURE_4P_DUAL_IEEE,
    MEBA_POE_PORT_PD_STRUCTURE_2P_DUAL_4P_CANDIDATE_FALSE,
    MEBA_POE_PORT_PD_STRUCTURE_2P_IEEE,
    MEBA_POE_PORT_PD_STRUCTURE_2P_LEGACY
} meba_poe_port_pd_structure_t;

/** \brief Power source, see TIA-1057 table 16 or IEEE 802.3at table 33-22 (bits 5:4)
 */
typedef enum {
    MEBA_POE_POWER_SOURCE_UNKNOWN,
    MEBA_POE_POWER_SOURCE_PRIMARY,
    MEBA_POE_POWER_SOURCE_BACKUP,
    MEBA_POE_POWER_SOURCE_RESERVED
} meba_poe_power_source_t;

/** \brief PoE Port priority.
 * \details If the PoE controller (and/or power supply) can not deliver the
 * needed power, then the port priority is used to identify what ports to
 * shutdown first (and power-up last when power become available).
 * Ports with low priority is shutdown first, starting with the ports with
 * highest logical-port ID.
 * */
typedef enum {
    /** Critical. */
    MEBA_POE_PORT_PRIO_CRITICAL = 1,

    /** High priority. */
    MEBA_POE_PORT_PRIO_HIGH = 2,

    /** Low priority. */
    MEBA_POE_PORT_PRIO_LOW = 3,
} meba_poe_port_prio_t;

/** \brief Power supply ID.
 * \details Used to identity a given power-supply. A given system does not need
 * to support all power supplies listed here. */
typedef enum {
    /** Address all PSU. */
    MEBA_POE_CTRL_PSU_ALL = 0,

    /** Primary PSU. */
    MEBA_POE_CTRL_PSU_PRIMARY = 1,

    /** Backup PSU. */
    MEBA_POE_CTRL_PSU_BACKUP = 2,
} meba_poe_ctrl_psu_t;

/** \brief PoE PSE type. */
typedef enum {
    MEBA_POE_PORT_PSE_TYPE_1_PSE = 2,
    MEBA_POE_PORT_PSE_TYPE_2_PSE = 0,
} meba_poe_port_pse_type_t;

/** \brief PoE PSE power class */
typedef enum {
    MEBA_POE_PORT_PSE_POWER_CLASS_0     = 0,
    MEBA_POE_PORT_PSE_POWER_CLASS_1     = 1,
    MEBA_POE_PORT_PSE_POWER_CLASS_2     = 2,
    MEBA_POE_PORT_PSE_POWER_CLASS_3     = 3,
    MEBA_POE_PORT_PSE_POWER_CLASS_4     = 4,
    MEBA_POE_PORT_PSE_POWER_CLASS_ERROR = 5,
} meba_poe_port_pse_power_class_t;

/** \brief PoE PSE PSE Power Pair. */
typedef enum {
    MEBA_POE_PORT_PSE_POWER_DATA_PAIR = 1,
    MEBA_POE_PORT_PSE_POWER_SPARE_PAIR = 2,
    MEBA_POE_PORT_PSE_POWER_BOTH = 3,
} meba_poe_port_pse_power_pair_t;


/** \brief ID/handle used by the PoE controller to identify a given port. The
 * port map defines how to translate between the physical port, the logical port
 * and handles. The handle is suppose to be the internal ID used by the PoE
 * controller to address a given logical port. */
typedef mesa_port_no_t meba_poe_port_handle_t;

/** Power measured in milliwatt. */
typedef uint32_t mesa_poe_milliwatt_t;

/** Current measured in milliampere. */
typedef uint32_t mesa_poe_milliampere_t;

/** Voltage measured in millivolts. */
typedef uint32_t mesa_poe_millivolt_t;

/** Cable length measured in meters. */
typedef uint32_t mesa_poe_meters_t;

/** If true, legacy detect is supported */
typedef mesa_bool_t mesa_poe_legacy_detect_t;

/** Data for PoE lldp field Power Status. */
/** IEEE Std 802.3-2018. Table 79-6e. Power Status field */
typedef uint16_t mesa_poe_power_status_t;

/** Data for PoE lldp field System Setup. */
/** IEEE Std 802.3-2018. Table 79-6f. System Setup field */
typedef uint8_t mesa_poe_system_setup_t;

/** Data for PoE lldp field Autoclass. */
/** IEEE Std 802.3-2018. Table 79-6h. Autoclass field */
typedef uint8_t mesa_poe_auto_class_t;

/** \brief PoE PD power type */
/** IEEE Std 802.3-2015. Table 79-4. Power type field */
typedef enum {
    MEBA_POE_PORT_PD_POWER_TYPE2_PSE,
    MEBA_POE_PORT_PD_POWER_TYPE2_PD,
    MEBA_POE_PORT_PD_POWER_TYPE1_PSE,
    MEBA_POE_PORT_PD_POWER_TYPE1_PD,
} meba_poe_pd_power_type_t;

/** \brief PoE PD power source */
/** IEEE Std 802.3-2015. Table 79-4. Power source field */
typedef enum {
    MEBA_POE_PORT_PD_PD_POWER_SOURCE_UNKNOWN,
    MEBA_POE_PORT_PD_PD_POWER_SOURCE_PSE,
    MEBA_POE_PORT_PD_PD_POWER_SOURCE_RESERVED,
    MEBA_POE_PORT_PD_PD_POWER_SOURCE_PSE_LOCAL,
    MEBA_POE_PORT_PD_PSE_POWER_SOURCE_UNKNOWN,
    MEBA_POE_PORT_PD_PSE_POWER_SOURCE_PRIMARY,
    MEBA_POE_PORT_PD_PSE_POWER_SOURCE_BACKUP,
    MEBA_POE_PORT_PD_PSE_POWER_SOURCE_RESERVED,
} meba_poe_pd_power_source_t;

/** \brief PoE PD power priority */
/** IEEE Std 802.3-2015. Table 79-4. Power priority field */
typedef enum {
    MEBA_POE_PORT_PD_POWER_PRIORITY_UNKNOWN,
    MEBA_POE_PORT_PD_POWER_PRIORITY_CRITICAL,
    MEBA_POE_PORT_PD_POWER_PRIORITY_HIGH,
    MEBA_POE_PORT_PD_POWER_PRIORITY_LOW,
} meba_poe_pd_power_priority_t;

/** The maximum length of buffer used to hold the PoE firmware version string. */
#define MEBA_POE_VERSION_STRING_SIZE 256

/** \brief PoE global configuration */
typedef struct {
    /** PoE primary power in milliwat */
    mesa_poe_milliwatt_t        primary_max_power;

    /** PoE backup power in milliwat*/
    mesa_poe_milliwatt_t        backup_max_power;

    /** If true, legacy detect is supported */
    mesa_poe_legacy_detect_t    legacy_detect;
} meba_poe_cfg_t;

/** \brief PoE port configuration */
typedef struct {
    /** PoE Port enable, IEEE Std 802.3bt Section 30.9.1.1.1 aPSEAdminState */
    mesa_bool_t                 enable;

    /** PoE legacy support. When false, only features defined in 803.2bt are supported */
    mesa_bool_t                 legacy_support;

    /** IEEE Std 802.3bt Section 30.9.1.1.3 aPSEPowerPairs */
    meba_poe_port_pse_power_pair_t  power_pairs;

    /** PoE Port configured priority. */
    meba_poe_port_prio_t        priority;

    /** PoE port is in lldp mode */
    mesa_bool_t                 lldp_mode;
} meba_poe_port_cfg_t;

/** \brief PoE controller status. */
typedef struct {
    /** PoE chipset detection state. */
    meba_poe_chip_state_t       chip_state;

    /** Textual description of the active poe driver */
    char const                 *driver_name;

    /** PoE controller firmware version. */
    char                        version[MEBA_POE_VERSION_STRING_SIZE];

    /** PoE power source. */
    meba_poe_power_source_t     source;

    /** Total power. */
    uint16_t total_power;
} meba_poe_status_t;

/** \brief PoE port pd data. */
typedef struct {
    /** PoE PD power type. */
    meba_poe_pd_power_type_t    type;

    /** PoE PD power source.*/
    meba_poe_pd_power_source_t  source;

    /** PoE PD power prio. */
    meba_poe_pd_power_priority_t prio;

    /** PoE port requested power. */
    mesa_poe_milliwatt_t        pd_requested_power;

    /** PoE port allocated power. */
    mesa_poe_milliwatt_t        pse_allocated_power;

} meba_poe_pd_data_t;

/** \brief PoE port pd version 3,4 data. */
typedef struct {
    /** PoE PD power type. */
    meba_poe_pd_power_type_t    type;

    /** PoE PD power source.*/
    meba_poe_pd_power_source_t  source;

    /** PoE PD power prio. */
    meba_poe_pd_power_priority_t prio;

    /** PoE port requested power. */
    mesa_poe_milliwatt_t        pd_requested_power_single;

    /** PoE port allocated power. */
    mesa_poe_milliwatt_t        pse_allocated_power_single;

    /** PoE port requested power on alternative a (dual signature). */
    mesa_poe_milliwatt_t        pd_requested_power_alt_a;

    /** PoE port allocated power on alternative a (dual signature). */
    mesa_poe_milliwatt_t        pse_allocated_power_alt_a;

    /** PoE port requested power on alternative b (dual signature). */
    mesa_poe_milliwatt_t        pd_requested_power_alt_b;

    /** PoE port allocated power on alternative b (dual signature). */
    mesa_poe_milliwatt_t        pse_allocated_power_alt_b;

} meba_poe_pd_bt_data_t;

/** \brief PoE port pse data. */
typedef struct {
    /** PoE port allocated power. */
    mesa_poe_milliwatt_t        pse_allocated_power;

    /** PoE port requested power. */
    mesa_poe_milliwatt_t        pd_requested_power;

    /** PoE port pse type.  */
    meba_poe_port_pse_type_t    pse_power_type;

    /** PoE port power class. */
    meba_poe_port_pse_power_class_t power_class;

    /** PoE port power pair. */
    meba_poe_port_pse_power_pair_t pse_power_pair;

    /** PoE port cable length in meters. */
    mesa_poe_meters_t           cable_len;

} meba_poe_pse_data_t;

/** \brief Power supply properties */
typedef struct {
    /** Power supply ID. */
    meba_poe_ctrl_psu_t         id;

    /** Minimum power supply capacity. */
    mesa_poe_milliwatt_t        min;

    /** Maximum effect the controller can handle. */
    mesa_poe_milliwatt_t        max;

    /** Default power supply capacity. */
    mesa_poe_milliwatt_t        def;

    /** If the system (switch) is powered by the same PSU as is used for PoE,
     * then we need to reserve the power consumed by the system. */
    mesa_poe_milliwatt_t        system_consumed;

    /** Signal if the end user is allowed to configure the PSU capacity. If set
     * to false, then the 'def - system_consumed' will be used, and the user can
     * not overwrite that. */
    mesa_bool_t                 user_configurable;
} meba_poe_psu_input_prob_t;

/** \brief Port properties.
 * \details The port property values never changes - they are defined by the
 * board hardware. These values are initialized by the \ref meba_poe_system_get_t
 * function, and is exposed to the application through this interface. */
typedef struct {
    /** Port capabilities. */
    meba_poe_port_cap_t         capabilities;

    /** Max power the port can emit. */
    mesa_poe_milliwatt_t        max;

    /** Logical port number (application point of view). */
    mesa_port_no_t              port_no;

    /** ID used by the PoE controller to address a given port. The handle should
     * be useable directly by the PoE controller without further mapping. */
    meba_poe_port_handle_t      handle;

    /** Physical port (on the PoE chip). */
    uint32_t                    phys_port;
} meba_poe_port_properties_t;

struct meba_poe_ctrl_api;

/** \brief PoE Controller instance */
typedef struct {
    /** Function pointers. */
    struct meba_poe_ctrl_api   *api;

    /** Private date to be used by the driver implementation. */
    void                       *private_data;

    /** Name of the adapter used to communicate with PoE device (only to ease debugging)*/
    char const                 *adapter_name;

    /** File handle for an adapter abstracting communication with PoE device */
    int                         adapter_fd;

    /** Controller capabilities. */
    meba_poe_ctrl_cap_t         capabilities;

    /** List of all ports controlled by this controller instance. */
    meba_poe_port_properties_t *port_map;

    /** Number of ports in 'port_map'. */
    uint32_t                    port_map_length;

    /** List of all PSU inputs the controller and board can handle. */
    meba_poe_psu_input_prob_t  *psu_map;

    /** Number of psu inputs. */
    uint32_t                    psu_map_length;

} meba_poe_ctrl_inst_t;


/** \brief PoE port status. */
typedef struct {
    /** IEEE Std 802.3bt Section 30.9.1.1.2 aPSEPowerPairsControlAbility */
    mesa_bool_t                 power_pairs_control_ability;

    /** PoE chipset detection state. */
    meba_poe_chip_state_t       chip_state;

    /** PoE port state. IEEE Std 802.3bt Section 30.9.1.1.5 aPSEPowerDetectionStatus */
    meba_poe_port_state_t       state;

    /** PoE port PD class. */
    meba_poe_port_pd_class_t    assigned_pd_class_a;

    /** PoE port PD class, second pair (used for poe-bt) */
    meba_poe_port_pd_class_t    assigned_pd_class_b;

    /** PoE port PD class. */
    meba_poe_port_pd_class_t    measured_pd_class_a;

    /** PoE port PD class, second pair (used for poe-bt) */
    meba_poe_port_pd_class_t    measured_pd_class_b;

    /** PoE port PD class. */
    meba_poe_port_pd_class_t    requested_pd_class_a;

    /** PoE port PD class, second pair (used for poe-bt) */
    meba_poe_port_pd_class_t    requested_pd_class_b;

    /** PoE port PD class. */
    mesa_poe_milliwatt_t        requested_power_mode_a;

    /** PoE port PD class, second pair (used for poe-bt) */
    mesa_poe_milliwatt_t        requested_power_mode_b;

    /** PoE port PD class. */
    mesa_poe_milliwatt_t        pse_alloc_power_alt_a;

    /** PoE port PD class, second pair (used for poe-bt) */
    mesa_poe_milliwatt_t        pse_alloc_power_alt_b;

    /** PoE port PSE  */
    mesa_poe_milliwatt_t        pse_max_avail_power;

    /** PoE port power status. Holds the value to go into PoE lldp element: Power Status */
    mesa_poe_power_status_t     power_status;

    /** PoE port system setup. Holds the value to go into PoE lldp element: System Setup */
    mesa_poe_system_setup_t     system_setup;

    /** 4 pair vs. 2 pair, single signature vs. dual signature */
    meba_poe_port_pd_structure_t pd_structure;

    /** PoE port requested power. */
    mesa_poe_milliwatt_t        requested_power;

    /** The power reserved for the PD. When power is allocated on basis of PD class, this
        number will be equal to the consumed power. When LLDP is used to allocated power, this
        will be the amount of power reserved through LLDP. The value is only meaningful
        when the PD is on. */
    mesa_poe_milliwatt_t        reserved_power;

    /** PoE port consumed power. */
    mesa_poe_milliwatt_t        power;

    /** True if PD is detected to support autoclass */
    mesa_bool_t                 autoclass_support;

    /** Max power measured by Autoclass Measurement. */
    mesa_poe_milliwatt_t        measured_autoclass_power;

    /** IEEE Std 802.3-2018. Table 79-6h. Autoclass field. */
    mesa_poe_auto_class_t       auto_class;

    /** PoE port consumed current. */
    mesa_poe_milliampere_t      current;

    /** PoE port measured voltage. */
    mesa_poe_millivolt_t        voltage;

    /** PoE port PSE data. */
    meba_poe_pse_data_t         pse_data;

} meba_poe_port_status_t;

/**
 * \brief Get PoE controller firmware version.
 *
 * \param inst     [IN]  Controller instance.
 * \param max_size [IN]  The maximum size of firmware version.
 * \param version  [OUT] The firmware version.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_version_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        uint32_t                        max_size,
        char                           *version);

/**
 * \brief Firmware upgrade.
 *
 * \details This function will load/burn the 'data' to the controller. Upgrading
 * firmware may (depending on the HW) take from a less than a second to many
 * minutes. The PoE can not be accessed while a firmware upgrade is going on.
 *
 * \param inst  [IN]  Controller instance.
 * \param reset [IN]  If true, the PoE controller will reset after a successful
 *                    firmware load. This function must block until:
 *                    - The firmware is completely loaded
 *                    - The controller is reset
 *                    - Communication with the controller is re-established
 *                    - The controller is re-initialized
 *                    After a reset, all configuration applied using this API
 *                    must be applied again.
 *                    If set to false, the firmware must still be loaded, but
 *                    will not be effectuated until a system reset. The old
 *                    firmware must continue to be running, and the system must
 *                    not be interrupted.
 * \param size  [IN]  Size of date in bytes.
 * \param firmware [IN] Firmware to load.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_firmware_upgrade_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        mesa_bool_t                     reset,
        uint32_t                        size,
        const char                     *firmware);

/**
 * \brief Preparation of Firmware upgrade.
 *
 * \details This function will load/burn the 'data' to the controller. Upgrading
 * firmware may (depending on the HW) take from a less than a second to many
 * minutes. The PoE can not be accessed while a firmware upgrade is going on.
 *
 * \param inst          [IN]  Controller instance.
 * \param version_check [IN]  If true, firmware is only upgradeed if the version
 *                            is diffferent from the currently loaded.
 * \param size          [IN]  Size of date in bytes.
 * \param firmware      [IN]  Firmware to load.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_prepare_firmware_upgrade_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        mesa_bool_t                     version_check,
        uint32_t                        size,
        const char                     *firmware);

/**
 * \brief Get PoE port status.
 *
 * \param inst   [IN]  Controller instance.
 * \param handle [IN]  Port handle
 * \param status [OUT] Port status.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_port_status_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_port_handle_t          handle,
        meba_poe_port_status_t         *const status);

/**
 * \brief Set a PoE port configuration.
 *
 * \param inst   [IN]  Controller instance.
 * \param handle [IN]  Port handle
 * \param cfg    [IN]  Port configuration.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_port_cfg_set_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_port_handle_t          handle,
        meba_poe_port_cfg_t            *cfg);

/**
 * \brief Set a PoE controller configuration.
 *
 * \param inst   [IN]  Controller instance.
 * \param cfg    [IN]  Port configuration.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_cfg_set_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_cfg_t                 *cfg);

/**
 * \brief Get PoE controller status.
 *
 * \param inst   [IN]  Controller instance.
 * \param status [OUT] Controller status.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_status_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_status_t              *status);


/**
 * \brief Get PoE controller capabilities.
 *
 * \param inst   [IN]  Controller instance.
 * \param status [OUT] Controller capabilities.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_capabilities_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_ctrl_cap_t            *capabilities);

/**
* \brief Send a reset command to Poe controller.
*
* \param inst   [IN]  Controller instance.
*
* \return error code.
*/
typedef mesa_rc (*meba_poe_ctrl_reset_command_t)(
        const meba_poe_ctrl_inst_t     *const inst);

/**
 * \brief Perform chip detection.
 *
 * \param inst   [IN]  Controller instance.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_do_detection_t)(
        const meba_poe_ctrl_inst_t     *const inst);

/**
 * \brief This function perform initialization of the controller chip
 * and setting the operatinal mode to default.
 *
 * \param inst   [IN]  Controller instance.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_chip_initialization_t)(
    const meba_poe_ctrl_inst_t     *const inst);

/**
 * \brief This function will perform synchronization of the communication
 * between the application and the PoE controller. It is used during the
 * application initialisation of the PoE driver.
 *
 * \param inst   [IN]  Controller instance.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_sync_t)(
    const meba_poe_ctrl_inst_t     *const inst);

/**
 * \brief Get PoE chipset information.
 *
 * \param inst       [IN]  Controller instance.
 * \param handle     [IN]  Port handle
 * \param chip_state [OUT] Chipset detection state.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_chipset_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_port_handle_t          handle,
        meba_poe_chip_state_t          *chip_state);

/**
 * \brief Enable debug traces.
 *
 * \param inst      [IN]  Controller instance.
 * \param trace_buf [OUT] Buffer to receive debug traces
 * \param buf_size  [IN]  Size of buffer.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_debug_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        uint8_t                        *trace_buf,
        int                             buf_size);

/**
 * \brief Get PoE port capabilities
 *
 * \param inst          [IN]  Controller instance.
 * \param handle        [IN]  Port handle
 * \param capabilities  [OUT] Port capabilities
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_port_capabilities_get_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_port_cap_t            *capabilities);

/**
 * \brief Set PoE PD configuration.
 * This function shall be called when the PoE application receives a LLDP pdu
 * with PoE information which shall be reflected in the PoE controller configuration.
 *
 * \param inst      [IN]  Controller instance.
 * \param port_no   [IN]  Port handle
 * \param pd_data   [IN]  PD data to configure.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_port_pd_data_set_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_data_t             *pd_data);

/**
 * \brief Set PoE PD configuration.
 * This function shall be called when the PoE application receives a type 3 or type 4
 * LLDp pdu with PoE information which shall be reflected in the PoE controller configuration.
 *
 * \param inst      [IN]  Controller instance.
 * \param port_no   [IN]  Port handle
 * \param pd_data   [IN]  PD data to configure.
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_port_pd_bt_data_set_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_bt_data_t          *pd_data);

/**
 * \brief Clear PoE PD configuration.
 * This function shall be called when a LLDP neighbour disappears (either due to 
 * timeout or due to link-down).
 *
 * \param inst      [IN]  Controller instance.
 * \param port_no   [IN]  Port handle
 *
 * \return error code.
 */
typedef mesa_rc (*meba_poe_ctrl_port_pd_data_clear_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle);

/** List of PoE controller APIs  */
#define MEBA_LIST_OF_POE_CTRL_CALLS                                            \
    X(meba_poe_ctrl_do_detection)                                              \
    X(meba_poe_ctrl_chip_initialization)                                       \
    X(meba_poe_ctrl_sync)                                                      \
    X(meba_poe_ctrl_version_get)                                               \
    X(meba_poe_ctrl_port_cfg_set)                                              \
    X(meba_poe_ctrl_port_status_get)                                           \
    X(meba_poe_ctrl_cfg_set)                                                   \
    X(meba_poe_ctrl_status_get)                                                \
    X(meba_poe_ctrl_reset_command)                                             \
    X(meba_poe_ctrl_chipset_get)                                               \
    X(meba_poe_ctrl_debug)                                                     \
    X(meba_poe_ctrl_firmware_upgrade)                                          \
    X(meba_poe_ctrl_prepare_firmware_upgrade)                                  \
    X(meba_poe_ctrl_port_capabilities_get)                                     \
    X(meba_poe_ctrl_port_pd_data_set)                                          \
    X(meba_poe_ctrl_port_pd_bt_data_set)                                       \
    X(meba_poe_ctrl_port_pd_data_clear)                                        \

/** \brief Board functions struct */
typedef struct meba_poe_ctrl_api {
/** \brief Fill up the struct with function pointers */
#define X(name) name##_t name;
    MEBA_LIST_OF_POE_CTRL_CALLS
#undef X
} meba_poe_ctrl_api_t;

#endif  // _MSCC_ETHERNET_BOARD_POE_CTRL_H_
