// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_BOARD_POE_CTRL_H_
#define _MICROCHIP_ETHERNET_BOARD_POE_CTRL_H_

#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// PoE Controller API
//
// This API defines how to interact with one of the PoE controller supported by
// the MEBA Layer.
//
// The MEBA library can contain drivers for many different controllers. Each
// controller must support to be instantiated several times, and the controller
// implementation is not allowed to have any board assumptions (if board
// information is needed then it must be passed as private date by the 'poe.h'
// API when it create the instances).
//
// The API supports a flexible topology which allow:
// - A PoE controller per port. In this case there will be many instances of
//   this API.
// - A PoE controller to handle a group of ports.
// - A single PoE controller to handle all the ports on the board.
//
// If a group of ports is located at the same address, then they are considered
// to be _owned_ by a single controller. This is regardless of if the controller
// can do the power management or not.
//
// This API is always instantiated by the 'poe.h' API (never by the application
// directly). The 'poe.h' API will create the number of instances needed, and
// will choose the driver matching the HW. When the 'poe.h' API create the
// instances, it will also update all the meta-data in meba_poe_ctrl_inst_t.
//
// A given controller instance, only have knowledge about the ports belonging
// to the controller. This means that to apply configuration or query status on
// for a specific port, you will have to go through the controller owning the
// port.
//
// The 'poe.h' API contains wrapper functions which will search the right
// controller and forward the request.

// PoE Controller capabilities (bitmask).
// The capability allow the application to query the capabilities of a
// given board, and adapt the matching functionality.
typedef enum {
    // Signals if the controller performs the power managements.
    MEBA_POE_CTRL_CAP_POWER_MANAGEMENT = 0x1,

    // Signals if there is a hw signal to turn on/off the poe controller.
    MEBA_POE_CTRL_CAP_HW_ENABLE = 0x2,

    // Signals if the controller supports poe legacy PD detection.
    MEBA_POE_CTRL_CAP_PD_LEGACY_DETECTION = 0x4,

    // Signals that the controller can continue to deliver power even
    //     during system software reset
    MEBA_POE_CTRL_INTERRUPTIBLE_POWER = 0X8,

    // Signals if the controller is in auto class mode
    MEBA_POE_CTRL_PD_AUTO_CLASS_REQUEST = 0X10,

    // Signals if the controller supports legacy
    MEBA_POE_CTRL_LEGACY_PD_CLASS_MODE = 0X20,
} meba_poe_ctrl_cap_t;


// PoE Controller Port capabilities (bitmask).
// The capability allow the application to query the capabilities of a
// given board, and adapt the matching functionality.
typedef enum {
    // Port supports PoE.
    MEBA_POE_PORT_CAP_POE = 0x1,

    // 802.3af - Class 0-3, 2 pair
    MEBA_POE_PORT_CAP_TYPE_1 = 0x2,

    // 802.3at - Class 0-4, 2 pair
    MEBA_POE_PORT_CAP_TYPE_2 = 0x4,

    // 802.3bt - Class 0-6, 2 or 4 pair
    MEBA_POE_PORT_CAP_TYPE_3 = 0x8,

    // 802.3bt - Class 0-8+, 2 or 4-pair
    MEBA_POE_PORT_CAP_TYPE_4 = 0x10,

    // Port can be forced to emit power.
    MEBA_POE_PORT_CAP_FORCE_ON = 0x20,

    // The pair used for PoE is configurable
    MEBA_POE_PORT_CAP_2PAIR_CONTROL = 0x40,

    // Port supports PoE over 4-pairs.
    MEBA_POE_PORT_CAP_4PAIR = 0x80,

    // Allow to set power budget based on current consumption (triggered by
    // lldp).
    MEBA_POE_PORT_CAP_AUTOCLASS = 0x100,
} meba_poe_port_cap_t;


// State of the PoE chip identification.
typedef enum {
    //  PoE chipset detection in progress.
    MEBA_POE_CHIPSET_DETECTION,

    // Could not determine chipset state.
    MEBA_POE_NO_CHIPSET_FOUND,

    // PoE controller firmware is upgrading.
    MEBA_POE_FIRMWARE_UPGRADE,

    // Succesful detection of PoE chip.
    MEBA_POE_CHIPSET_FOUND,
} meba_poe_chip_state_t;


// PoE Port status as defined by 802.3.
typedef enum {
    MEBA_POE_IEEE_PORT_STATE_NOT_SUPPORTED      = 0,  // no part of rfc3621 (not to be used)
    MEBA_POE_IEEE_PORT_STATE_DISABLED           = 1,
    MEBA_POE_IEEE_PORT_STATE_SEARCHING          = 2,
    MEBA_POE_IEEE_PORT_STATE_DELIVERING_POWER   = 3,
    MEBA_POE_IEEE_PORT_STATE_FAULT              = 4,
    MEBA_POE_IEEE_PORT_STATE_TEST               = 5,
    MEBA_POE_IEEE_PORT_STATE_OTHER_FAULT        = 6
} meba_poe_ieee_port_state_t;


/**
 * \brief PoE Port status type
 */
typedef enum {
    MEBA_POE_UNKNOWN_STATE = 0,       // Unknown state.
    MEBA_POE_POWER_BUDGET_EXCEEDED,   // PoE is turned OFF due to power budget exceeded on PSE.
    MEBA_POE_NO_PD_DETECTED,          // No PD detected.
    MEBA_POE_PD_ON,                   // PSE supplying power to PD-BT through PoE.
    MEBA_POE_PD_OVERLOAD,             // PD consumes more power than the maximum limit configured on the PSE port.
    MEBA_POE_NOT_SUPPORTED,           // PoE feature is not supported.
    MEBA_POE_DISABLED,                // PoE feature is disabled on PSE.
    MEBA_POE_DISABLED_INTERFACE_SHUTDOWN, // PoE disabled due to interface shutdown
    MEBA_POE_PD_FAULT,                // PoE PD fault
    MEBA_POE_PSE_FAULT                // PoE pse fault
} meba_poe_port_state_t;


// PoE Port PD class. The value -1 means class value invalid
typedef int32_t meba_poe_port_pd_class_t;

// PoE Port PD structure
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


// Power source, see TIA-1057 table 16 or IEEE 802.3at table 33-22 (bits 5:4)
typedef enum {
    MEBA_POE_POWER_SOURCE_UNKNOWN,
    MEBA_POE_POWER_SOURCE_PRIMARY,
    MEBA_POE_POWER_SOURCE_BACKUP,
    MEBA_POE_POWER_SOURCE_RESERVED
} meba_poe_power_source_t;


// PoE Port priority.
// If the PoE controller (and/or power supply) can not deliver the
// needed power, then the port priority is used to identify what ports to
// shutdown first (and power-up last when power become available).
// Ports with low priority is shutdown first, starting with the ports with
// highest logical-port ID.
typedef enum {
    /** limit to type 3 15W . */
    MEBA_POE_PSE_PORT_TYPE3_15W = 0,
    /** limit to type 3 30W . */
    MEBA_POE_PSE_PORT_TYPE3_30W,
    /** limit to type 3 60W. */
    MEBA_POE_PSE_PORT_TYPE3_60W,
    /** limit to type 4 90W. */
    MEBA_POE_PSE_PORT_TYPE4_90W
} meba_poe_port_type_t;


/**
 * \brief Types of port power priority.
 * \details The port power priority, which determines the order in which the port will receive power.
 *          Ports with a higher priority will receive power before ports with a lower priority.
 */
typedef enum {
    /** cable length till 10 meters. */
    MEBA_POE_PORT_CABLE_LENGTH_10 = 1,
    /** cable length till 30 meters. */
    MEBA_POE_PORT_CABLE_LENGTH_30 = 3,
    /** cable length till 60 meters. */
    MEBA_POE_PORT_CABLE_LENGTH_60 = 6,
    /** cable length till 100 meters. */
    MEBA_POE_PORT_CABLE_LENGTH_100 = 10
} meba_poe_port_cable_length_t;


// PoE bt Port PM mode.
// If the PoE controller (and/or power supply) can not deliver the
// needed power, then the port priority is used to identify what ports to
// shutdown first (and power-up last when power become available).
// Ports with low priority is shutdown first, starting with the ports with
// highest logical-port ID.
typedef enum {
    /** The port power that is used for power management purposes is dynamic (Iport x Vmain). */
    MEBA_POE_BT_PORT_POWER_MANAGEMENT_DYNAMIC = 0,
    /** The port power that is used for power management purposes is port TPPL_BT. */
    MEBA_POE_BT_PORT_POWER_MANAGEMENT_STATIC,
    /** The port power that is used for power management purposes is dynamic for non LLDP/CDP/Autoclass ports and TPPL_BT for LLDP/CDP/Autoclass ports. */
    MEBA_POE_BT_PORT_POWER_MANAGEMENT_HYBRID
} meba_poe_bt_port_pm_mode_t;


// Power supply ID.
// Used to identity a given power-supply. A given system does not need to
// support all power supplies listed here.
typedef enum {
    MEBA_POE_CTRL_PSU_ALL = 0,
    MEBA_POE_CTRL_PSU_PRIMARY = 1,
    MEBA_POE_CTRL_PSU_BACKUP = 2,
} meba_poe_ctrl_psu_t;


// PoE PSE type.
typedef enum {
    MEBA_POE_PORT_PSE_TYPE_1_PSE = 2,
    MEBA_POE_PORT_PSE_TYPE_2_PSE = 0,
} meba_poe_port_pse_type_t;


// PoE PSE power class
typedef enum {
    MEBA_POE_PORT_PSE_POWER_CLASS_0     = 0,
    MEBA_POE_PORT_PSE_POWER_CLASS_1     = 1,
    MEBA_POE_PORT_PSE_POWER_CLASS_2     = 2,
    MEBA_POE_PORT_PSE_POWER_CLASS_3     = 3,
    MEBA_POE_PORT_PSE_POWER_CLASS_4     = 4,
    MEBA_POE_PORT_PSE_POWER_CLASS_ERROR = 5,
} meba_poe_port_pse_power_class_t;


// PoE PSE PSE Power Pair.
typedef enum {
    MEBA_POE_PORT_PSE_POWER_DATA_PAIR  = 1,
    MEBA_POE_PORT_PSE_POWER_SPARE_PAIR = 2,
    MEBA_POE_PORT_PSE_POWER_BOTH       = 3,
} meba_poe_port_pse_power_pair_t;


typedef enum {
    MEBA_POE_PORT_PSE_IEEE802_3AF_operation = 0,
    MEBA_POE_PORT_PSE_IEEE802_3AF_AT_operation,
    MEBA_POE_PORT_PSE_POH_operation
} meba_poe_port_pse_port_type_t;


// ID/handle used by the PoE controller to identify a given port. The
// port map defines how to translate between the physical port, the logical port
// and handles. The handle is suppose to be the internal ID used by the PoE
// controller to address a given logical port.
typedef mesa_port_no_t meba_poe_port_handle_t;

// Power measured in milliwatt.
typedef uint32_t mesa_poe_milliwatt_t;

// Current measured in milliampere.
typedef uint32_t mesa_poe_milliampere_t;

// Voltage measured in millivolts.
typedef uint32_t mesa_poe_millivolt_t;

// Cable length measured in meters.
typedef uint32_t mesa_poe_meters_t;

// If true, legacy detect is supported
typedef mesa_bool_t mesa_poe_legacy_detect_t;

// Data for PoE lldp field Power Status.
// IEEE Std 802.3-2018. Table 79-6e. Power Status field
typedef uint16_t mesa_poe_power_status_t;

// Data for PoE lldp field System Setup.
// IEEE Std 802.3-2018. Table 79-6f. System Setup field
typedef uint8_t mesa_poe_system_setup_t;

// Data for PoE lldp field Autoclass.
// IEEE Std 802.3-2018. Table 79-6h. Autoclass field
typedef uint8_t mesa_poe_auto_class_t;


//------ BT individual masks ------ //
typedef struct {
    uint8_t bt_ignore_high_priority;
    uint8_t bt_support_high_res_detection;
    uint8_t bt_i2c_restart_enable;
    uint8_t bt_hocpp;
    uint8_t bt_pse_powering_pse_checking;
    uint8_t bt_layer2_power_allocation_limit;
    uint8_t bt_support_lldp_half_priority;
    uint8_t bt_led_stream_type;
    uint8_t bt_blinks_at_invalid_signature;
    uint8_t bt_xSystem_OK_pin_behavior;
} meba_poe_indv_mask_bt_t;

//------ AT individual masks ------ //
typedef struct {
    uint8_t at_ignore_higher_priority;
    uint8_t at_supports_legacy_detection;
    uint8_t at_message_ready_notify;
    uint8_t at_layer2_priority_by_PD;
    uint8_t at_matrix_support_4p;
    uint8_t at_supports_backoff;
    uint8_t at_led_stream_type;
    uint8_t at_pse_powering_pse_checking;
    uint8_t at_xSystem_OK_pin_behavior;
    uint8_t at_enable_asic_refresh;
    uint8_t at_layer2_lldp_enable;
    uint8_t at_class_0_equal_af;
    uint8_t at_class_1_2_3_equal_af;
    uint8_t at_lldp_best_effort;
    uint8_t at_auto_zone2_port_activation;
    uint8_t at_hocpp_high_over_current_pulse_protection;
} meba_poe_indv_mask_at_t;


typedef struct
{
     meba_poe_indv_mask_at_t im_AT ;
     meba_poe_indv_mask_bt_t im_BT;
} poe_individual_mask_info_t;


// PoE PD power type
// IEEE Std 802.3-2015. Table 79-4. Power type field
typedef enum {
    MEBA_POE_PORT_PD_POWER_TYPE2_PSE,
    MEBA_POE_PORT_PD_POWER_TYPE2_PD,
    MEBA_POE_PORT_PD_POWER_TYPE1_PSE,
    MEBA_POE_PORT_PD_POWER_TYPE1_PD,
} meba_poe_pd_power_type_t;


// PoE PD power source
// IEEE Std 802.3-2015. Table 79-4. Power source field
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


// PoE PD power priority
// IEEE Std 802.3-2015. Table 79-4. Power priority field
typedef enum {
    MEBA_POE_PORT_PD_POWER_PRIORITY_UNKNOWN = 0,
    MEBA_POE_PORT_PD_POWER_PRIORITY_CRITICAL,
    MEBA_POE_PORT_PD_POWER_PRIORITY_HIGH,
    MEBA_POE_PORT_PD_POWER_PRIORITY_LOW,
} meba_poe_pd_power_priority_t;


typedef enum {
    MEBA_POE_PD692X0_CONTROLLER_TYPE_AUTO_DETECTION = 0,
    MEBA_POE_PD69200_CONTROLLER_TYPE ,
    MEBA_POE_PD69210_CONTROLLER_TYPE ,
    MEBA_POE_PD69220_CONTROLLER_TYPE ,
    MEBA_POE_PD69200M_CONTROLLER_TYPE
} meba_poe_controller_type_t;


typedef enum {
    MEBA_POE_FIRMWARE_TYPE_AT = 0,
    MEBA_POE_FIRMWARE_TYPE_BT
} meba_poe_firmware_type_t;


typedef enum {
    MEBA_POE_SOFTWARE_POWER_TYPE_AF = 0,
    MEBA_POE_SOFTWARE_POWER_TYPE_AT,
    MEBA_POE_SOFTWARE_POWER_TYPE_BT
} meba_poe_software_power_type_t;


/**
 * \brief Types of port PoE mode
 */
typedef enum {
    /** PoE functionality is disabled. */
    MEBA_POE_MODE_DISABLED = 0,
    /** Enables PoE based on IEEE 802.3af standard,
        and provides power up to 15.4W(or 154 deciwatt) of DC power to powered device.
     */
    MEBA_POE_MODE_POE,
    /** Enabled PoE based on IEEE 802.3at standard,
        and provides power up to 30W(or 300 deciwatt) of DC power to powered device.
     */
    MEBA_POE_MODE_POE_PLUS
} meba_poe_port_mode_t;


typedef struct
{
    uint8_t  NumOfCh_HC08_Sprt ;
    uint8_t  SubContractor     ; //
    uint8_t  Year              ; // Manufacuring year
    uint8_t  Week              ; // Manufacturing week
    uint16_t PN                ; // PowerDsine part number
    uint32_t UN                ; // PowerDsine unique number
} meba_poe_serial_number_t;



// The maximum length of buffer used to hold the PoE firmware version string.
#define MEBA_POE_VERSION_STRING_SIZE 256

// PoE global configuration
typedef struct {
    // PoE primary power in watt
    uint32_t        primary_max_power_w;

    // If true, legacy detect is supported
    mesa_poe_legacy_detect_t    legacy_detect;

    // applicable only for BT sw
    uint8_t                     global_ignore_pd_auto_class_request;

    // applicable only for BT sw
    uint8_t                     global_legacy_pd_class_mode;

} meba_poe_global_cfg_t;


// PoE port configuration
typedef struct {
    // PoE Port enable, IEEE Std 802.3bt Section 30.9.1.1.1 aPSEAdminState
    mesa_bool_t                 enable;

    // PoE legacy support. When false, only features defined in 803.2bt are supported
    mesa_bool_t                 legacy_support;

    // IEEE Std 802.3bt Section 30.9.1.1.3 aPSEPowerPairs
    meba_poe_port_pse_power_pair_t  power_pairs;

    // PoE Port configured priority.
    meba_poe_pd_power_priority_t priority;

    // PoE port type3 15W 30W 60W or type4 90W
    meba_poe_port_type_t         bt_pse_port_type;

    // PoE port is in lldp mode
    mesa_bool_t                  lldp_mode;

    // PoE lldp port cablr length
    meba_poe_port_cable_length_t  cable_length;

    uint8_t   bt_en;
    uint8_t   ignored_inrush_check;  // Inrush ignored CFG1[0..3] -  BT: 0x1  Legacy: 0x2     - set by Port Operation Mode AT/BT
    uint8_t   ignore_pd_auto_class_request;                                                 //- set by AutoClass global var
    uint8_t   bt_port_pm_mode;                                                              //- meba_poe_bt_port_pm_mode_t
    uint8_t   class_error_selection;                                                        //- set by Port Operation Mode AT/BT
    uint8_t   bt_port_operation_mode;                                                       //- set by Port Operation Mode AT/BT
    uint8_t   add_power_for_port_mode_dW;
} meba_poe_port_cfg_t;


// PoE controller status.
typedef struct {

    poe_individual_mask_info_t  tPoe_individual_mask_info;

    // PoE chipset detection state.
    meba_poe_chip_state_t      chip_state;

    // Textual description of the active poe driver
    char const                 *driver_name;

    // PoE controller firmware version.
    char                        version[MEBA_POE_VERSION_STRING_SIZE];

    // PoE power source.
    meba_poe_power_source_t     poe_power_source;

    // number of PoE MCUs
    uint32_t                    operational_controller_count;

    // Total power.
    uint16_t                    total_power;

    // adc value
    uint16_t                    adc_value;

    uint8_t                     vmain_out_of_range;

    // is PoE MCU has BT or AT firmware
    mesa_bool_t                 is_bt;

    // controller type PD69200,PD69210,PD69220
    meba_poe_controller_type_t  ePoE_Controller_Type;

    // detected poe firmware type - ports mode BT or AF/AT
    meba_poe_firmware_type_t     eDetected_poe_firmware_type;

    // telemetry info from PoE MCU
    uint16_t power_consumption_w;
    uint16_t calculated_power_w;
    uint16_t available_power_w;
    uint16_t power_limit_w;
    uint8_t  power_bank;
    uint16_t vmain_voltage_dv;
    uint16_t imain_current_ma;

    uint32_t i2c_tx_error_counter;

    // poe firmware info
    uint8_t          prod_number_detected;
    uint16_t         sw_version_detected;
    uint8_t          param_number_detected;
    uint8_t          prod_number_from_file;
    uint16_t         sw_version_from_file;
    uint8_t          param_number_from_file;
    uint8_t          build_number;
    uint16_t         internal_sw_version;
    uint16_t         asic_patch_number;

    // microchip poe proprietary info
    meba_poe_serial_number_t tSN;
} meba_poe_status_t;


// PoE port pd data.
typedef struct {
    // PoE PD power type.
    meba_poe_pd_power_type_t    type;

    // PoE PD power source
    meba_poe_pd_power_source_t  source;

    // PoE PD power prio.
    meba_poe_pd_power_priority_t prio;

    // PoE port requested power.
    mesa_poe_milliwatt_t        pd_requested_power_mw;

    // PoE port allocated power.
    mesa_poe_milliwatt_t        pse_allocated_power_mw;

}meba_poe_pd_data_t;



//---------------------------------------------------
//        PoE init parameters
//---------------------------------------------------


#define MAX_SW_TYPE_LEN                    3   // max char len of SNMP MIB-II SysObjID (1.3.6.1.....)
#define MAX_PORD_NAME_STR_LEN              32   // max string size of product name
#define MAX_SNMP_SYS_OID_LEN               64   // max char len of SNMP MIB-II SysObjID (1.3.6.1.....)
#define MAX_DEF_VAL_OVERRIDE_STR_LEN       200  // max str len for the entire def values to be over written
#define MAX_WEB_URL_NAME_LEN               80   // max length of WEB page url as 'view_system_status_r_sp.htm'
#define MAX_DB_SINGLE_PRM_SIZE             350  // max size that a single param can occupy in the data base


// Parameter [PROD_xyzm_POE_PORT_MAX_POWER_W] value in file products.db must match one of the enum values
typedef enum
{
    MEBA_POE_PORT_MAX_POWER_15W = 15,
    MEBA_POE_PORT_MAX_POWER_30W = 30,
    MEBA_POE_PORT_MAX_POWER_60W = 60,
    MEBA_POE_PORT_MAX_POWER_90W = 90
}meba_poe_port_max_power_t;


typedef struct   // parameters taken from DB according to PN read from PoEMCU serial number
{
    mesa_bool_t              use_poe_static_parameters              ;
    uint8_t                  Max_POE_Ch                             ; // Max number of POE channels ( 6/12/24/48) based on product det (serial number)
    uint16_t                 PwrSupply_MaxPwr                       ; // Midspan Power Supply Max-Power(Watt) - after decrementing internal power consumption ( 450 -> 430,etc )
    char                     product_name[ MAX_PORD_NAME_STR_LEN+1] ; // Product name - retrieved from DB according to product being detected
    meba_poe_software_power_type_t eMEBA_POE_SOFTWARE_POWER_TYPE    ; // AF-15W ,AT-30W ,BT-60W/90W
    meba_poe_firmware_type_t       eMEBA_POE_FIRMWARE_TYPE          ; // AF/AT ,BT
}meba_poe_init_params_t;



// PoE port pd version 3,4 data.
typedef struct {
    meba_poe_pd_power_type_t       type;
    meba_poe_pd_power_source_t     source;
    meba_poe_pd_power_priority_t   prio;
    mesa_poe_milliwatt_t           pd_requested_power_single_mw;
    mesa_poe_milliwatt_t           pse_allocated_power_single_mw;
    mesa_poe_milliwatt_t           pd_requested_power_alt_a_mw;
    mesa_poe_milliwatt_t           pse_allocated_power_alt_a_mw;
    mesa_poe_milliwatt_t           pd_requested_power_alt_b_mw;
    mesa_poe_milliwatt_t           pse_allocated_power_alt_b_mw;
} meba_poe_pd_bt_data_t;

// PoE port pse data.
typedef struct {

    // IEEE Std 802.3bt Section 30.9.1.1.2 aPSEPowerPairsControlAbility
    mesa_bool_t                 power_pairs_control_ability;

    // PoE port PSE
    mesa_poe_milliwatt_t        pse_max_avail_power_mw;

    // PoE port power status. Holds the value to go into PoE lldp element: Power
    // Status
    mesa_poe_power_status_t     power_status;

    // PoE port PD class.
    mesa_poe_milliwatt_t        pse_alloc_power_alt_a_mw;

    // PoE port PD class, second pair (used for poe-bt)
    mesa_poe_milliwatt_t        pse_alloc_power_alt_b_mw;

    // PoE port PD class.
    mesa_poe_milliwatt_t        requested_power_mode_a_mw;

    // PoE port PD class, second pair (used for poe-bt)
    mesa_poe_milliwatt_t        requested_power_mode_b_mw;

    // PoE port allocated power.
    mesa_poe_milliwatt_t        pse_allocated_power_mw;

    // PoE port requested power.
    mesa_poe_milliwatt_t        pd_requested_power_mw;

    // PoE port pse type.
    meba_poe_port_pse_type_t    pse_power_type;

    // PoE port power class.
    meba_poe_port_pse_power_class_t power_class;

    // PoE port power pair.
    meba_poe_port_pse_power_pair_t pse_power_pair;

    meba_poe_port_pse_port_type_t port_type_af_at_poh;

    // PoE port cable length in meters.
    mesa_poe_meters_t           cable_len;

} meba_poe_pse_data_t;

// Power supply properties
typedef struct {
    // Power supply ID.
    meba_poe_ctrl_psu_t         id;

    // Minimum power supply capacity.
    uint32_t        min_w;

    // Maximum effect the controller can handle.
    uint32_t        max_w;

    // Default power supply capacity.
    uint32_t        def_w;

    // If the system (switch) is powered by the same PSU as is used for PoE,
    // then we need to reserve the power consumed by the system.
    uint32_t        system_consumed_w;

    // Signal if the end user is allowed to configure the PSU capacity. If set
    // to false, then the 'def - system_consumed' will be used, and the user can
    // not overwrite that.
    mesa_bool_t                 user_configurable;
} meba_poe_psu_input_prob_t;

// Port properties.
// The port property values never changes - they are defined by the board
// hardware. These values are initialized by the meba_poe_system_get_t function,
// and is exposed to the application through this interface.
typedef struct {
    // Port capabilities.
    meba_poe_port_cap_t         capabilities;

    // Max power the port can emit.
    mesa_poe_milliwatt_t        max;

    // Logical port number (application point of view).
    mesa_port_no_t              port_no;

    // ID used by the PoE controller to address a given port. The handle should
    // be useable directly by the PoE controller without further mapping.
    meba_poe_port_handle_t      handle;

    // Physical port (on the PoE chip).
    uint32_t                    phys_port_a;
    uint32_t                    phys_port_b; // For 4-pair operation
} meba_poe_port_properties_t;

struct meba_poe_ctrl_api;

// PoE Controller instance
typedef struct {
    // Function pointers.
    struct meba_poe_ctrl_api   *api;

    // Private date to be used by the driver implementation.
    void                       *private_data;

    // Name of the adapter used to communicate with PoE device (only to ease
    // debugging
    char const                 *adapter_name;

    // File handle for an adapter abstracting communication with PoE device
    int                         adapter_fd;

    // Controller capabilities.
    meba_poe_ctrl_cap_t         capabilities;

    // List of all ports controlled by this controller instance.
    meba_poe_port_properties_t *port_map;

    // Number of ports in 'port_map'.
    uint32_t                    port_map_length;

    // Number of poe ports.
    uint32_t                    port_poe_length;

    // List of all PSU inputs the controller and board can handle.
    meba_poe_psu_input_prob_t  *psu_map;

    // Number of psu inputs.
    uint32_t                    psu_map_length;

} meba_poe_ctrl_inst_t;


// PoE port status.
typedef struct {

    // PoE chipset detection state.
    meba_poe_chip_state_t       chip_state;

    // PoE port state. IEEE Std 802.3bt Section 30.9.1.1.5
    // aPSEPowerDetectionStatus
    meba_poe_ieee_port_state_t  meba_poe_ieee_port_state;

    meba_poe_port_state_t       meba_poe_port_state;

    // 0 - not valid , 1 - sspd , 2 - dspd.
    uint8_t                     pd_type_sspd_dspd;

    uint8_t                     poe_internal_port_status;

    // read configured port operation mode from 'get bt port parameters' // bt std = 0,1,2,3 legacy 0x10,0x11,0x12,0x13
    uint8_t                     bt_port_operation_mode;

    // pse type as set in port configuration
    meba_poe_port_type_t        bt_pse_port_type ;

    // read configured bt_port_pm_mode from 'get bt port parameters'
    meba_poe_bt_port_pm_mode_t  bt_port_pm_mode;

    char                        poe_port_status_description[100];

    mesa_bool_t                 is_poe_bt;

    // true when typical fault is reported when ethernet cable - link without poe power is connected
    mesa_bool_t                 is_fault_link_without_power;

    // PoE port PD class.
    meba_poe_port_pd_class_t    assigned_pd_class_a;

    // PoE port PD class, second pair (used for poe-bt)
    meba_poe_port_pd_class_t    assigned_pd_class_b;

    // PoE port PD class.
    meba_poe_port_pd_class_t    measured_pd_class_a;

    // PoE port PD class, second pair (used for poe-bt)
    meba_poe_port_pd_class_t    measured_pd_class_b;

    // PoE port PD class.
    meba_poe_port_pd_class_t    requested_pd_class_a;

    // PoE port PD class, second pair (used for poe-bt)
    meba_poe_port_pd_class_t    requested_pd_class_b;

    // PoE port system setup. Holds the value to go into PoE lldp element:
    // System Setup
    mesa_poe_system_setup_t     system_setup;

    // 4 pair vs. 2 pair, single signature vs. dual signature
    meba_poe_port_pd_structure_t pd_structure;

    // PoE port requested power.
    mesa_poe_milliwatt_t        power_requested_mw;

    mesa_poe_milliwatt_t        power_assigned_mw;

    // The power reserved for the PD. When power is allocated on basis of PD
    // class, this number will be equal to the consumed power. When LLDP is used
    // to allocated power, this will be the amount of power reserved through
    // LLDP. The value is only meaningful when the PD is on.
    mesa_poe_milliwatt_t        reserved_power_mw;

    // PoE port consumed power.
    mesa_poe_milliwatt_t        power_mw;

    // Max power measured by Autoclass Measurement.
    mesa_poe_milliwatt_t        measured_autoclass_power_mw;

    // IEEE Std 802.3-2018. Table 79-6h. Autoclass field.
    mesa_poe_auto_class_t       auto_class;

    // PoE port consumed current.
    mesa_poe_milliampere_t      current_ma;

    // PoE port measured voltage.
    mesa_poe_millivolt_t        voltage_mv;

    // PoE port PSE data.
    meba_poe_pse_data_t         pse_data;
} meba_poe_port_status_t;

// Get PoE controller firmware version.
// max_size [IN]  The maximum size of firmware version.
// version  [OUT] The firmware version.
typedef mesa_rc (*meba_poe_ctrl_version_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        uint32_t                        max_size,
        char                           *version);

// Firmware upgrade.
//
// This function will load/burn the 'data' to the controller. Upgrading
// firmware may (depending on the HW) take from a less than a second to many
// minutes. The PoE can not be accessed while a firmware upgrade is going on.
//
// reset [IN]  If true, the PoE controller will reset after a successful
//                    firmware load. This function must block until:
//                    - The firmware is completely loaded
//                    - The controller is reset
//                    - Communication with the controller is re-established
//                    - The controller is re-initialized
//                    After a reset, all configuration applied using this API
//                    must be applied again.
//                    If set to false, the firmware must still be loaded, but
//                    will not be effectuated until a system reset. The old
//                    firmware must continue to be running, and the system must
//                    not be interrupted.
// size  [IN]  Size of date in bytes.
// firmware [IN] Firmware to load.
typedef mesa_rc (*meba_poe_ctrl_firmware_upgrade_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        mesa_bool_t                     reset,
        uint32_t                        size,
        const char                     *firmware);

// Preparation of Firmware upgrade.
//
// This function will load/burn the 'data' to the controller. Upgrading
// firmware may (depending on the HW) take from a less than a second to many
// minutes. The PoE can not be accessed while a firmware upgrade is going on.
//
// version_check [IN]  If true, firmware is only upgradeed if the version
//                            is diffferent from the currently loaded.
// size          [IN]  Size of date in bytes.
// firmware      [IN]  Firmware to load.
typedef mesa_rc (*meba_poe_ctrl_prepare_firmware_upgrade_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        mesa_bool_t                     version_check,
        uint32_t                        size,
        const char                     *firmware);

// Get PoE port status.
typedef mesa_rc (*meba_poe_ctrl_port_status_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_port_handle_t          handle,
        meba_poe_port_status_t         *const status);

// Set a PoE port configuration.
typedef mesa_rc (*meba_poe_ctrl_port_cfg_set_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_port_handle_t          handle,
        meba_poe_port_cfg_t            *cfg);

// Set a PoE controller configuration.
typedef mesa_rc (*meba_poe_ctrl_cfg_set_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_global_cfg_t          *cfg);

// Get PoE controller status.
typedef mesa_rc (*meba_poe_ctrl_status_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_status_t              *status);


// Get PoE controller capabilities.
// status [OUT] Controller capabilities.
typedef mesa_rc (*meba_poe_ctrl_capabilities_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_ctrl_cap_t            *capabilities);

// Send a reset command to Poe controller.
typedef mesa_rc (*meba_poe_ctrl_reset_command_t)(
        const meba_poe_ctrl_inst_t     *const inst);

// Save PoE controller parameters
typedef mesa_rc (*meba_poe_ctrl_save_command_t)(
        const meba_poe_ctrl_inst_t     *const inst);

// Perform chip detection.
typedef mesa_rc (*meba_poe_ctrl_do_detection_t)(
        const meba_poe_ctrl_inst_t     *const inst);

// This function perform initialization of the controller chip
// and setting the operatinal mode to default.
typedef mesa_rc (*meba_poe_ctrl_chip_initialization_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    mesa_bool_t interruptible_power,
    int16_t     restart_cause);

// This function will perform synchronization of the communication
// between the application and the PoE controller. It is used during the
// application initialisation of the PoE driver.
typedef mesa_rc (*meba_poe_ctrl_sync_t)(
    const meba_poe_ctrl_inst_t     *const inst);

// Get PoE chipset information.
// handle     [IN]  Port handle
// chip_state [OUT] Chipset detection state.
typedef mesa_rc (*meba_poe_ctrl_chipset_get_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_port_handle_t          handle,
        meba_poe_chip_state_t          *chip_state);

// Enable debug traces.
// trace_buf [OUT] Buffer to receive debug traces
// buf_size  [IN]  Size of buffer.
typedef mesa_rc (*meba_poe_ctrl_debug_t)(
        const meba_poe_ctrl_inst_t     *const inst,
        char                            *var,
        uint32_t                        str_len,
        char                            *title ,
        char                            *tx_str ,
        char                            *rx_str ,
        char                            *msg,
        int                             max_msg_len);

// Get PoE port capabilities
// handle        [IN]  Port handle
// capabilities  [OUT] Port capabilities
typedef mesa_rc (*meba_poe_ctrl_port_capabilities_get_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_port_cap_t            *capabilities);

// Set PoE PD configuration.
// This function shall be called when the PoE application receives a LLDP pdu
// with PoE information which shall be reflected in the PoE controller
// configuration.
//
// port_no   [IN]  Port handle
// pd_data   [IN]  PD data to configure.
typedef mesa_rc (*meba_poe_ctrl_port_pd_data_set_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_data_t             *pd_data);

// Set PoE PD configuration.
// This function shall be called when the PoE application receives a type 3 or
// type 4 LLDP pdu with PoE information which shall be reflected in the PoE
// controller configuration.
//
// port_no   [IN]  Port handle
// pd_data   [IN]  PD data to configure.
typedef mesa_rc (*meba_poe_ctrl_port_pd_bt_data_set_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_bt_data_t          *pd_data);

// Clear PoE PD configuration.
// This function shall be called when a LLDP neighbour disappears (either due to
// timeout or due to link-down).
//
// port_no   [IN]  Port handle
typedef mesa_rc (*meba_poe_ctrl_port_pd_data_clear_t)(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle);

// List of PoE controller APIs
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
    X(meba_poe_ctrl_save_command)                                              \
    X(meba_poe_ctrl_chipset_get)                                               \
    X(meba_poe_ctrl_debug)                                                     \
    X(meba_poe_ctrl_firmware_upgrade)                                          \
    X(meba_poe_ctrl_prepare_firmware_upgrade)                                  \
    X(meba_poe_ctrl_port_capabilities_get)                                     \
    X(meba_poe_ctrl_port_pd_data_set)                                          \
    X(meba_poe_ctrl_port_pd_bt_data_set)                                       \
    X(meba_poe_ctrl_port_pd_data_clear)                                        \

// Board functions struct
typedef struct meba_poe_ctrl_api {
    meba_poe_ctrl_do_detection_t              meba_poe_ctrl_do_detection;
    meba_poe_ctrl_chip_initialization_t       meba_poe_ctrl_chip_initialization;
    meba_poe_ctrl_sync_t                      meba_poe_ctrl_sync;
    meba_poe_ctrl_version_get_t               meba_poe_ctrl_version_get;
    meba_poe_ctrl_port_cfg_set_t              meba_poe_ctrl_port_cfg_set;
    meba_poe_ctrl_port_status_get_t           meba_poe_ctrl_port_status_get;
    meba_poe_ctrl_cfg_set_t                   meba_poe_ctrl_cfg_set;
    meba_poe_ctrl_status_get_t                meba_poe_ctrl_status_get;
    meba_poe_ctrl_reset_command_t             meba_poe_ctrl_reset_command;
    meba_poe_ctrl_save_command_t              meba_poe_ctrl_save_command;
    meba_poe_ctrl_chipset_get_t               meba_poe_ctrl_chipset_get;
    meba_poe_ctrl_debug_t                     meba_poe_ctrl_debug;
    meba_poe_ctrl_firmware_upgrade_t          meba_poe_ctrl_firmware_upgrade;
    meba_poe_ctrl_prepare_firmware_upgrade_t  meba_poe_ctrl_prepare_firmware_upgrade;
    meba_poe_ctrl_port_capabilities_get_t     meba_poe_ctrl_port_capabilities_get;
    meba_poe_ctrl_port_pd_data_set_t          meba_poe_ctrl_port_pd_data_set;
    meba_poe_ctrl_port_pd_bt_data_set_t       meba_poe_ctrl_port_pd_bt_data_set;
    meba_poe_ctrl_port_pd_data_clear_t        meba_poe_ctrl_port_pd_data_clear;
} meba_poe_ctrl_api_t;

#include <microchip/ethernet/board/api/hdr_end.h>
#endif  // _MICROCHIP_ETHERNET_BOARD_POE_CTRL_H_
